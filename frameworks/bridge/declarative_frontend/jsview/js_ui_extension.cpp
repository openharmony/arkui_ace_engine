/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_ui_extension.h"

#include <functional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "base/want/want_wrap.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<UIExtensionModel> UIExtensionModel::instance_ = nullptr;
std::mutex UIExtensionModel::mutex_;

UIExtensionModel* UIExtensionModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::UIExtensionModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::UIExtensionModelNG());
            } else {
                return nullptr;
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSUIExtensionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtensionProxy>::Declare("UIExtensionProxy ");
    JSClass<JSUIExtensionProxy>::CustomMethod("send", &JSUIExtensionProxy::Send);
    JSClass<JSUIExtensionProxy>::Bind(globalObj, &JSUIExtensionProxy::Constructor, &JSUIExtensionProxy::Destructor);
}

void JSUIExtensionProxy::Constructor(const JSCallbackInfo& info)
{
    auto uiExtensionProxy = Referenced::MakeRefPtr<JSUIExtensionProxy>();
    uiExtensionProxy->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(uiExtensionProxy));
}

void JSUIExtensionProxy::Destructor(JSUIExtensionProxy* uiExtensionProxy)
{
    if (uiExtensionProxy != nullptr) {
        uiExtensionProxy->DecRefCount();
    }
}

void JSUIExtensionProxy::Send(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    panda::Local<JsiValue> value = info[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scopeNapi(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    
    auto wantParams = WantParamsWrap::CreateWantWrap(reinterpret_cast<napi_env>(nativeEngine), nativeValue);
    if (proxy_) {
        proxy_->SendData(wantParams);
    }
}

void JSUIExtensionProxy::SetInstanceId(int32_t instanceId)
{
    instanceId_ = instanceId;
}

void JSUIExtensionProxy::SetProxy(const RefPtr<NG::UIExtensionProxy>& proxy)
{
    proxy_ = proxy;
}

void JSUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtension>::Declare("UIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUIExtension>::StaticMethod("create", &JSUIExtension::Create, opt);
    JSClass<JSUIExtension>::StaticMethod("onRemoteReady", &JSUIExtension::OnRemoteReady);
    JSClass<JSUIExtension>::StaticMethod("onReceive", &JSUIExtension::OnReceive);
    JSClass<JSUIExtension>::StaticMethod("onRelease", &JSUIExtension::OnRelease);
    JSClass<JSUIExtension>::StaticMethod("onResult", &JSUIExtension::OnResult);
    JSClass<JSUIExtension>::StaticMethod("onError", &JSUIExtension::OnError);
    JSClass<JSUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto wantObj = JSRef<JSObject>::Cast(info[0]);
    RefPtr<OHOS::Ace::WantWrap> want = CreateWantWrapFromNapiValue(wantObj);
    UIExtensionModel::GetInstance()->Create(want);
}

void JSUIExtension::OnRemoteReady(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRemoteReady = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId]
        (const RefPtr<NG::UIExtensionProxy>& session) {
        ContainerScope scope(instanceId);
        JSRef<JSObject> contextObj = JSClass<JSUIExtensionProxy>::NewInstance();
        RefPtr<JSUIExtensionProxy> proxy = Referenced::Claim(contextObj->Unwrap<JSUIExtensionProxy>());
        proxy->SetInstanceId(instanceId);
        proxy->SetProxy(session);
        auto returnValue = JSRef<JSVal>::Cast(contextObj);
        func->ExecuteJS(1, &returnValue);
    };
    UIExtensionModel::GetInstance()->SetOnRemoteReady(std::move(onRemoteReady));
}

void JSUIExtension::OnReceive(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onReceive = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId]
        (const AAFwk::WantParams& wantParams) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("UIExtensionComponent.UIExtensionDataSession.onReceive");
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        auto env = reinterpret_cast<napi_env>(nativeEngine);
        auto nativeWantParams = WantWrap::ConvertParamsToNativeValue(wantParams, env);
        auto wantParamsJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWantParams);
        func->ExecuteJS(1, &wantParamsJSVal);
    };
    UIExtensionModel::GetInstance()->SetOnReceive(std::move(onReceive));
}

void JSUIExtension::OnRelease(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRelease = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId](int32_t releaseCode) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("UIExtensionComponent.onRelease");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(releaseCode));
        func->ExecuteJS(1, &newJSVal);
    };
    UIExtensionModel::GetInstance()->SetOnRelease(std::move(onRelease));
}

void JSUIExtension::OnResult(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onResult = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId]
        (int32_t code, const AAFwk::Want& want) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onResult");
            auto engine = EngineHelper::GetCurrentEngine();
            CHECK_NULL_VOID(engine);
            NativeEngine* nativeEngine = engine->GetNativeEngine();
            CHECK_NULL_VOID(nativeEngine);
            auto nativeWant = WantWrap::ConvertToNativeValue(want, reinterpret_cast<napi_env>(nativeEngine));
            auto wantJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWant);
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            obj->SetProperty<int32_t>("code", code);
            obj->SetPropertyObject("want", wantJSVal);
            auto returnValue = JSRef<JSVal>::Cast(obj);
            func->ExecuteJS(1, &returnValue);
        };
    UIExtensionModel::GetInstance()->SetOnResult(std::move(onResult));
}

void JSUIExtension::OnError(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId]
        (int32_t code, const std::string& name, const std::string& message) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onError");
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            obj->SetProperty<int32_t>("code", code);
            obj->SetProperty<std::string>("name", name);
            obj->SetProperty<std::string>("message", message);
            auto returnValue = JSRef<JSVal>::Cast(obj);
            func->ExecuteJS(1, &returnValue);
        };
    UIExtensionModel::GetInstance()->SetOnError(std::move(onError));
}
} // namespace OHOS::Ace::Framework
