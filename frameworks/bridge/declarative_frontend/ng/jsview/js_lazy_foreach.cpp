/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "frameworks/bridge/declarative_frontend/jsview/bindings/js_lazy_foreach_binding.h"

namespace OHOS::Ace::Framework {

namespace {

enum {
    PARAM_VIEW_ID = 0,
    PARAM_PARENT_VIEW,
    PARAM_DATA_SOURCE,
    PARAM_ITEM_GENERATOR,
    PARAM_KEY_GENERATOR,

    MIN_PARAM_SIZE = PARAM_KEY_GENERATOR,
    MAX_PARAM_SIZE,
};

template<class... T>
JSRef<JSVal> CallJSFunction(const JSRef<JSFunc>& func, const JSRef<JSObject>& obj, T&&... args)
{
    JSRef<JSVal> params[] = { ConvertToJSValue(std::forward<T>(args))... };
    return func->Call(obj, ArraySize(params), params);
}

bool ParseAndVerifyParams(const JSCallbackInfo& info, JSRef<JSVal> (&params)[MAX_PARAM_SIZE])
{
    if (info.Length() < MIN_PARAM_SIZE) {
        return false;
    }

    if (!info[PARAM_VIEW_ID]->IsNumber() && !info[PARAM_VIEW_ID]->IsString()) {
        return false;
    }
    if (!info[PARAM_PARENT_VIEW]->IsObject()) {
        return false;
    }
    if (!info[PARAM_DATA_SOURCE]->IsObject()) {
        return false;
    }
    if (!info[PARAM_ITEM_GENERATOR]->IsFunction()) {
        return false;
    }
    if (info.Length() > MIN_PARAM_SIZE && !info[PARAM_KEY_GENERATOR]->IsFunction()) {
        return false;
    }

    for (int32_t idx = PARAM_VIEW_ID; idx < std::min(info.Length(), static_cast<int32_t>(MAX_PARAM_SIZE)); ++idx) {
        params[idx] = info[idx];
    }
    return true;
}

} // namespace

class JSLazyForEachBuilder : public NG::LazyForEachBuilder, public JSLazyForEachActuator {
    DECLARE_ACE_TYPE(JSLazyForEachBuilder, NG::LazyForEachBuilder, JSLazyForEachActuator);

public:
    JSLazyForEachBuilder() = default;
    ~JSLazyForEachBuilder() override = default;

    int32_t OnGetTotalCount() override
    {
        return GetTotalIndexCount();
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, const std::unordered_map<std::string, RefPtr<NG::UINode>>& cachedItems) override
    {
        std::pair<std::string, RefPtr<NG::UINode>> info;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, info);
        if (getDataFunc_.IsEmpty()) {
            return info;
        }

        JSRef<JSVal> result = CallJSFunction(getDataFunc_, dataSourceObj_, index);
        std::string key = keyGenFunc_(result, index);

        auto cachedIter = cachedItems.find(key);
        if (cachedIter != cachedItems.end()) {
            info.first = key;
            info.second = cachedIter->second;
            return info;
        }

        auto* viewStack = NG::ViewStackProcessor::GetInstance();
        if (parentView_) {
            parentView_->MarkLazyForEachProcess(key);
        }
        viewStack->PushKey(key);
        itemGenFunc_->Call(JSRef<JSObject>(), 1, &result);
        viewStack->PopKey();
        if (parentView_) {
            parentView_->ResetLazyForEachProcess();
        }
        info.first = key;
        info.second = viewStack->Finish();
        return info;
    }

    void OnExpandChildrenOnInitialInNG() override
    {
        auto totalIndex = GetTotalIndexCount();
        auto* stack = NG::ViewStackProcessor::GetInstance();
        JSRef<JSVal> params[2];
        for (auto index = 0; index < totalIndex; index++) {
            params[0] = CallJSFunction(getDataFunc_, dataSourceObj_, index);
            params[1] = JSRef<JSVal>::Make(ToJSValue(index));
            std::string key = keyGenFunc_(params[0], index);
            stack->PushKey(key);
            itemGenFunc_->Call(JSRef<JSObject>(), 2, params);
            stack->PopKey();
        }
    }

    void ReleaseChildGroupById(const std::string& id) override
    {
        JSLazyForEachActuator::ReleaseChildGroupByComposedId(id);
    }

    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override
    {
        JSLazyForEachActuator::RegisterListener(listener);
    }

    void UnregisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override
    {
        JSLazyForEachActuator::UnregisterListener(listener);
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSLazyForEachBuilder);
};

void JSLazyForEach::Create(const JSCallbackInfo& info)
{
    JSRef<JSVal> params[MAX_PARAM_SIZE];
    if (!ParseAndVerifyParams(info, params)) {
        LOGE("Invalid arguments for LazyForEach");
        return;
    }

    std::string viewId = params[PARAM_VIEW_ID]->ToString();
    JSRef<JSObject> parentViewObj = JSRef<JSObject>::Cast(params[PARAM_PARENT_VIEW]);
    JSRef<JSObject> dataSourceObj = JSRef<JSObject>::Cast(params[PARAM_DATA_SOURCE]);
    JSRef<JSFunc> itemGenerator = JSRef<JSFunc>::Cast(params[PARAM_ITEM_GENERATOR]);
    ItemKeyGenerator keyGenFunc;
    if (params[PARAM_KEY_GENERATOR]->IsUndefined()) {
        keyGenFunc = [viewId](const JSRef<JSVal>&, size_t index) { return viewId + "-" + std::to_string(index); };
    } else {
        keyGenFunc = [viewId, keyGenerator = JSRef<JSFunc>::Cast(params[PARAM_KEY_GENERATOR])](
                         const JSRef<JSVal>& jsVal, size_t index) {
            JSRef<JSVal> params[] = { jsVal };
            auto key = keyGenerator->Call(JSRef<JSObject>(), ArraySize(params), params);
            return viewId + "-" + (key->IsString() || key->IsNumber() ? key->ToString() : std::to_string(index));
        };
    }

    auto builder = AceType::MakeRefPtr<JSLazyForEachBuilder>();
    builder->SetJSExecutionContext(info.GetExecutionContext());
    builder->SetParentViewObj(parentViewObj);
    builder->SetDataSourceObj(dataSourceObj);
    builder->SetItemGenerator(itemGenerator, std::move(keyGenFunc));
    NG::LazyForEach::Create(builder);
}

void JSLazyForEach::Pop() {}

} // namespace OHOS::Ace::Framework
