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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_BUILDER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_BUILDER_H

#include <functional>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_actuator.h"
#include "bridge/declarative_frontend/jsview/js_view.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"

namespace OHOS::Ace::Framework {

class JSLazyForEachBuilder : public NG::LazyForEachBuilder, public JSLazyForEachActuator {
    DECLARE_ACE_TYPE(JSLazyForEachBuilder, NG::LazyForEachBuilder, JSLazyForEachActuator);

public:
    JSLazyForEachBuilder() = default;
    ~JSLazyForEachBuilder() override = default;

    int32_t OnGetTotalCount() override
    {
        return GetTotalIndexCount();
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

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) override
    {
        std::pair<std::string, RefPtr<NG::UINode>> info;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, info);
        if (getDataFunc_.IsEmpty()) {
            return info;
        }

        JSRef<JSVal> params[2];
        params[0] = CallJSFunction(getDataFunc_, dataSourceObj_, index);
        params[1] = JSRef<JSVal>::Make(ToJSValue(index));
        std::string key = keyGenFunc_(params[0], index);
        auto cachedIter = cachedItems.find(key);
        if (cachedIter != cachedItems.end()) {
            info.first = key;
            info.second = cachedIter->second.second;
            cachedItems.erase(cachedIter);
            return info;
        }

        NG::ScopedViewStackProcessor scopedViewStackProcessor;
        auto* viewStack = NG::ViewStackProcessor::GetInstance();
        if (parentView_) {
            parentView_->MarkLazyForEachProcess(key);
        }
        viewStack->PushKey(key);
        itemGenFunc_->Call(JSRef<JSObject>(), 2, params);
        viewStack->PopKey();
        if (parentView_) {
            parentView_->ResetLazyForEachProcess();
        }
        info.first = key;
        info.second = viewStack->Finish();
        return info;
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

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_BUILDER_H
