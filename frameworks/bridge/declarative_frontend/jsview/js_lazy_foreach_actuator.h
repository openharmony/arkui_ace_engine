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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_ACTUATOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_ACTUATOR_H

#include <functional>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_data_change_listener.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"

namespace OHOS::Ace::Framework {

using ItemKeyGenerator = std::function<std::string(const JSRef<JSVal>&, size_t)>;

template<class... T>
JSRef<JSVal> CallJSFunction(const JSRef<JSFunc>& func, const JSRef<JSObject>& obj, T&&... args)
{
    JSRef<JSVal> params[] = { ConvertToJSValue(std::forward<T>(args))... };
    return func->Call(obj, ArraySize(params), params);
}

class JSLazyForEachActuator : public LazyForEachActuator {
    DECLARE_ACE_TYPE(JSLazyForEachActuator, LazyForEachActuator);

public:
    JSLazyForEachActuator() = default;
    ~JSLazyForEachActuator() override
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
        JSRef<JSObject> listenerObj = listenerProxyObj_.Lock();
        if (listenerObj.IsEmpty() || unregisterListenerFunc_.IsEmpty()) {
            return;
        }

        JSRef<JSVal> args[] = { listenerObj };
        unregisterListenerFunc_->Call(dataSourceObj_, ArraySize(args), args);
    }

    int32_t GetTotalIndexCount()
    {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, 0);
        if (totalCountFunc_.IsEmpty()) {
            return 0;
        }

        int32_t value = 0;
        if (!ConvertFromJSValue(totalCountFunc_->Call(dataSourceObj_), value)) {
            return 0;
        }
        if (value < 0) {
            return 0;
        }
        return value;
    }

    void RegisterListener(const RefPtr<V2::DataChangeListener>& listener)
    {
        if (!listener) {
            return;
        }

        auto listenerProxy = listenerProxy_.Upgrade();
        if (listenerProxy) {
            listenerProxy->AddListener(listener);
            return;
        }

        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
        if (registerListenerFunc_.IsEmpty()) {
            return;
        }

        JSRef<JSObject> listenerObj = JSClass<JSDataChangeListener>::NewInstance();
        auto* unwrapObj = listenerObj->Unwrap<JSDataChangeListener>();
        if (unwrapObj == nullptr) {
            return;
        }
        listenerProxy = Referenced::Claim(unwrapObj);
        listenerProxy->AddListener(listener);
        listenerProxyObj_ = listenerObj;
        listenerProxy_ = listenerProxy;

        JSRef<JSVal> args[] = { listenerObj };
        registerListenerFunc_->Call(dataSourceObj_, ArraySize(args), args);
    }

    void UnregisterListener(V2::DataChangeListener* listener)
    {
        if (!listener) {
            return;
        }

        auto listenerProxy = listenerProxy_.Upgrade();
        if (listenerProxy) {
            listenerProxy->RemoveListener(Referenced::WeakClaim(listener));
        }
    }

    void SetJSExecutionContext(const JSExecutionContext& context)
    {
        executionContext_ = context;
    }

    void SetParentViewObj(const JSRef<JSObject>& parentViewObj)
    {
        AceType* aceType = parentViewObj->Unwrap<AceType>();
        CHECK_NULL_VOID(aceType);
        std::string typeName = AceType::TypeName(aceType);
        if (typeName != "JSBaseNode") {
            parentView_ = parentViewObj->Unwrap<JSView>();
        }
    }

    void SetDataSourceObj(const JSRef<JSObject>& dataSourceObj)
    {
        dataSourceObj_ = dataSourceObj;
        totalCountFunc_ = GetFunctionFromObject(dataSourceObj, "totalCount");
        getDataFunc_ = GetFunctionFromObject(dataSourceObj, "getData");
        registerListenerFunc_ = GetFunctionFromObject(dataSourceObj, "registerDataChangeListener");
        unregisterListenerFunc_ = GetFunctionFromObject(dataSourceObj, "unregisterDataChangeListener");
    }

    void SetItemGenerator(const JSRef<JSFunc>& itemGenFunc, ItemKeyGenerator&& keyGenFunc)
    {
        itemGenFunc_ = itemGenFunc;
        keyGenFunc_ = std::move(keyGenFunc);
    }

    void SetUpdateChangedNodeFlag(const bool updateChangedNodeFlag)
    {
        updateChangedNodeFlag_ = updateChangedNodeFlag;
    }

    void ReleaseChildGroupByComposedId(const std::string& composedId)
    {
        if (parentView_ != nullptr) {
            parentView_->RemoveChildGroupById(composedId);
        }
    }

private:
    inline JSRef<JSFunc> GetFunctionFromObject(const JSRef<JSObject>& obj, const char* funcName)
    {
        JSRef<JSVal> jsVal = obj->GetProperty(funcName);
        if (jsVal->IsFunction()) {
            return JSRef<JSFunc>::Cast(jsVal);
        }
        return JSRef<JSFunc>();
    }

protected:
    JSExecutionContext executionContext_;
    JSView* parentView_ = nullptr;
    JSRef<JSObject> dataSourceObj_;
    JSRef<JSFunc> totalCountFunc_;
    JSRef<JSFunc> getDataFunc_;
    JSRef<JSFunc> registerListenerFunc_;
    JSRef<JSFunc> unregisterListenerFunc_;
    JSRef<JSFunc> itemGenFunc_;
    ItemKeyGenerator keyGenFunc_;
    bool updateChangedNodeFlag_ = false;

    JSWeak<JSObject> listenerProxyObj_;
    WeakPtr<JSDataChangeListener> listenerProxy_;
    RefPtr<V2::DataChangeListener> defaultListener_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAZY_FOREACH_ACTUATOR_H
