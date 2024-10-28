/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_security_ui_extension.h"

#include <functional>
#include <string>
#include "want_params.h"

#include "base/log/ace_scoring_log.h"
#include "base/want/want_wrap.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "interfaces/include/ws_common.h"

namespace OHOS::Ace::Framework {
namespace {
    constexpr int ARGC_TWO = 2;
    const CalcDimension SECURITY_UEC_MIN_WIDTH(10.0f, DimensionUnit::VP);
    const CalcDimension SECURITY_UEC_MIN_HEIGHT(10.0f, DimensionUnit::VP);
}
void JSSecurityUIExtensionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecurityUIExtensionProxy>::Declare("SecurityUIExtensionProxy");
    JSClass<JSSecurityUIExtensionProxy>::CustomMethod("send", &JSSecurityUIExtensionProxy::Send);
    JSClass<JSSecurityUIExtensionProxy>::CustomMethod("sendSync", &JSSecurityUIExtensionProxy::SendSync);
    JSClass<JSSecurityUIExtensionProxy>::CustomMethod("on", &JSSecurityUIExtensionProxy::On);
    JSClass<JSSecurityUIExtensionProxy>::CustomMethod("off", &JSSecurityUIExtensionProxy::Off);
    JSClass<JSSecurityUIExtensionProxy>::Bind(
        globalObj, &JSSecurityUIExtensionProxy::Constructor, &JSSecurityUIExtensionProxy::Destructor);
}

void JSSecurityUIExtensionProxy::Constructor(const JSCallbackInfo& info)
{
    auto uiExtensionProxy = Referenced::MakeRefPtr<JSSecurityUIExtensionProxy>();
    uiExtensionProxy->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(uiExtensionProxy));
}

void JSSecurityUIExtensionProxy::Destructor(JSSecurityUIExtensionProxy* uiExtensionProxy)
{
    if (uiExtensionProxy != nullptr) {
        uiExtensionProxy->DecRefCount();
    }
}

void JSSecurityUIExtensionProxy::Send(const JSCallbackInfo& info)
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
    auto wantParams = WantParamsWrap::CreateWantWrap(
        reinterpret_cast<napi_env>(nativeEngine), nativeValue);
    if (proxy_) {
        proxy_->SendData(wantParams);
    }
}

void JSSecurityUIExtensionProxy::SendSync(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    panda::Local<JsiValue> value = info[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scopeNapi(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    auto wantParams = WantParamsWrap::CreateWantWrap(
        reinterpret_cast<napi_env>(nativeEngine), nativeValue);
    if (proxy_) {
        AAFwk::WantParams reWantParams;
        int32_t sendCode = proxy_->SendDataSync(wantParams, reWantParams);
        if (sendCode != 0) {
            std::string errMsg;
            if (sendCode == ERROR_CODE_UIEXTENSION_NOT_REGISTER_SYNC_CALLBACK) {
                errMsg = "No callback has been registered to process synchronous data transferring.";
            } else if (sendCode == ERROR_CODE_UIEXTENSION_TRANSFER_DATA_FAILED) {
                errMsg = "Transferring data failed.";
            } else {
                errMsg = "Unknown error.";
            }
            JSException::Throw(sendCode, errMsg.c_str());
            return;
        }
        auto execCtx = info.GetExecutionContext();
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto reNativeWantParams = WantWrap::ConvertParamsToNativeValue(
            reWantParams, reinterpret_cast<napi_env>(nativeEngine));
        auto reWantParamsJSVal =
            Framework::JsConverter::ConvertNapiValueToJsVal(reNativeWantParams);
        info.SetReturnValue(reWantParamsJSVal);
    }
}

SecurityCallbackFuncPairList::const_iterator JSSecurityUIExtensionProxy::FindCbList(
    napi_env env, napi_value cb, SecurityCallbackFuncPairList& callbackFuncPairList)
{
    return std::find_if(callbackFuncPairList.begin(), callbackFuncPairList.end(),
        [env, cb](const auto& item) -> bool {
        bool result = false;
        napi_value refItem;
        napi_get_reference_value(env, item.first, &refItem);
        napi_strict_equals(env, refItem, cb, &result);
        return result;
    });
}

void JSSecurityUIExtensionProxy::AddCallbackToList(
    napi_env env, napi_value cb, napi_handle_scope scope, RegisterType type,
    const std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onFunc)
{
    if (type == RegisterType::SYNC) {
        auto iter = FindCbList(env, cb, onSyncOnCallbackList_);
        if (iter == onSyncOnCallbackList_.end()) {
            napi_ref ref = nullptr;
            napi_create_reference(env, cb, 1, &ref);
            onSyncOnCallbackList_.emplace_back(ref, onFunc);
        }
    } else if (type == RegisterType::ASYNC) {
        auto iter = FindCbList(env, cb, onAsyncOnCallbackList_);
        if (iter == onAsyncOnCallbackList_.end()) {
            napi_ref ref = nullptr;
            napi_create_reference(env, cb, 1, &ref);
            onAsyncOnCallbackList_.emplace_back(ref, onFunc);
        }
    }
    napi_close_handle_scope(env, scope);
}

void JSSecurityUIExtensionProxy::DeleteCallbackFromList(
    int argc, napi_env env, napi_value cb, RegisterType type)
{
    if (argc == 1) {
        if (type == RegisterType::SYNC) {
            for (const auto& item : onSyncOnCallbackList_) {
                napi_delete_reference(env, item.first);
            }
            onSyncOnCallbackList_.clear();
        } else if (type == RegisterType::ASYNC) {
            for (const auto& item : onAsyncOnCallbackList_) {
                napi_delete_reference(env, item.first);
            }
            onAsyncOnCallbackList_.clear();
        }
    } else if (argc == ARGC_TWO) {
        if (type == RegisterType::SYNC) {
            auto iter = FindCbList(env, cb, onSyncOnCallbackList_);
            if (iter != onSyncOnCallbackList_.end()) {
                napi_delete_reference(env, iter->first);
                onSyncOnCallbackList_.erase(iter);
            }
        } else if (type == RegisterType::ASYNC) {
            auto iter = FindCbList(env, cb, onAsyncOnCallbackList_);
            if (iter != onAsyncOnCallbackList_.end()) {
                napi_delete_reference(env, iter->first);
                onAsyncOnCallbackList_.erase(iter);
            }
        }
    }
}

std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>> JSSecurityUIExtensionProxy::GetOnFuncList(
    RegisterType type)
{
    std::list<std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>> reList;
    if (type == RegisterType::SYNC) {
        for (const auto& item : onSyncOnCallbackList_) {
            reList.emplace_back(item.second);
        }
    } else if (type == RegisterType::ASYNC) {
        for (const auto& item : onAsyncOnCallbackList_) {
            reList.emplace_back(item.second);
        }
    }
    return reList;
}

RegisterType JSSecurityUIExtensionProxy::GetRegisterType(const std::string& strType)
{
    RegisterType type = RegisterType::UNKNOWN;
    static constexpr char syncType[] = "syncReceiverRegister";
    static constexpr char asyncType[] = "asyncReceiverRegister";
    if (strType.compare(syncType) == 0) {
        type = RegisterType::SYNC;
    } else if (strType.compare(asyncType) == 0) {
        type = RegisterType::ASYNC;
    }
    return type;
}

bool NeedCheckComponentSize()
{
    std::string type =
        UIExtensionModel::GetInstance()->GetUiExtensionType(NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
    if (type.empty()) {
        return true;
    }
    const std::unordered_set<std::string> noNeedCheckExtensionType = { "sysPicker/photoPicker" };
    return noNeedCheckExtensionType.find(type) == noNeedCheckExtensionType.end();
}

void CreateInstanceAndSet(NG::UIExtensionConfig& config)
{
    UIExtensionModel::GetInstance()->Create(config);
    ViewAbstractModel::GetInstance()->SetMinWidth(SECURITY_UEC_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetMinHeight(SECURITY_UEC_MIN_HEIGHT);
    if (!NeedCheckComponentSize()) {
        LOGI("No need check size due to extension type is special");
        return;
    }
    ViewAbstractModel::GetInstance()->SetWidth(SECURITY_UEC_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetHeight(SECURITY_UEC_MIN_HEIGHT);
}

bool JSSecurityUIExtensionProxy::CanTurnOn(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() || !info[1]->IsFunction()) {
        return false;
    }
    const RegisterType registerType = GetRegisterType(info[0]->ToString());
    return registerType != RegisterType::UNKNOWN;
}

void JSSecurityUIExtensionProxy::On(const JSCallbackInfo& info)
{
    if (!CanTurnOn(info)) {
        return;
    }
    const RegisterType registerType = GetRegisterType(info[0]->ToString());
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(
        NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    auto instanceId = ContainerScope::CurrentId();
    auto onOnFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
        instanceId, node = frameNode] (const RefPtr<NG::SecurityUIExtensionProxy>& session) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            JSRef<JSObject> contextObj = JSClass<JSSecurityUIExtensionProxy>::NewInstance();
            RefPtr<JSSecurityUIExtensionProxy> proxy =
                Referenced::Claim(contextObj->Unwrap<JSSecurityUIExtensionProxy>());
            CHECK_NULL_VOID(proxy);
            proxy->SetInstanceId(instanceId);
            proxy->SetProxy(session);
            auto param = JSRef<JSVal>::Cast(contextObj);
            func->ExecuteJS(1, &param);
        };

    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scopeNapi(env);
    panda::Local<JsiValue> value = info[1].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value cb = nativeEngine->ValueToNapiValue(valueWrapper);
    napi_handle_scope napiScope = nullptr;
    napi_open_handle_scope(env, &napiScope);
    CHECK_NULL_VOID(napiScope);
    std::lock_guard<std::mutex> lock(callbackLisLock_);
    AddCallbackToList(env, cb, napiScope, registerType, std::move(onOnFunc));
    auto pattern = proxy_->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto onFuncList = GetOnFuncList(registerType);
    if (registerType == RegisterType::SYNC) {
        pattern->SetSyncCallbacks(std::move(onFuncList));
    } else if (registerType == RegisterType::ASYNC) {
        pattern->SetAsyncCallbacks(std::move(onFuncList));
    }
}

void JSSecurityUIExtensionProxy::Off(const JSCallbackInfo& info)
{
    if (!info[0]->IsString()) {
        return;
    }
    const RegisterType registerType = GetRegisterType(info[0]->ToString());
    if (registerType == RegisterType::UNKNOWN) {
        return;
    }

    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scopeNapi(env);
    napi_value cb = nullptr;
    if (info[1]->IsFunction()) {
        panda::Local<JsiValue> value = info[1].Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        cb = nativeEngine->ValueToNapiValue(valueWrapper);
    }

    std::lock_guard<std::mutex> lock(callbackLisLock_);
    DeleteCallbackFromList(info.Length(), env, cb, registerType);
    auto pattern = proxy_->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto onFuncList = GetOnFuncList(registerType);
    if (registerType == RegisterType::SYNC) {
        pattern->SetSyncCallbacks(std::move(onFuncList));
    } else if (registerType == RegisterType::ASYNC) {
        pattern->SetAsyncCallbacks(std::move(onFuncList));
    }
}

void JSSecurityUIExtensionProxy::SetInstanceId(int32_t instanceId)
{
    instanceId_ = instanceId;
}

void JSSecurityUIExtensionProxy::SetProxy(
    const RefPtr<NG::SecurityUIExtensionProxy>& proxy)
{
    proxy_ = proxy;
}

void JSSecurityUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecurityUIExtension>::Declare("SecurityUIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSecurityUIExtension>::StaticMethod("create", &JSSecurityUIExtension::Create, opt);
    JSClass<JSSecurityUIExtension>::StaticMethod("onRemoteReady", &JSSecurityUIExtension::OnRemoteReady);
    JSClass<JSSecurityUIExtension>::StaticMethod("onReceive", &JSSecurityUIExtension::OnReceive);
    JSClass<JSSecurityUIExtension>::StaticMethod("onError", &JSSecurityUIExtension::OnError);
    JSClass<JSSecurityUIExtension>::StaticMethod("onTerminated", &JSSecurityUIExtension::OnTerminated);
    JSClass<JSSecurityUIExtension>::StaticMethod("width", &JSSecurityUIExtension::JsWidth);
    JSClass<JSSecurityUIExtension>::StaticMethod("height", &JSSecurityUIExtension::JsHeight);
    JSClass<JSSecurityUIExtension>::StaticMethod("backgroundColor", &JSViewAbstract::JsBackgroundColor);
    JSClass<JSSecurityUIExtension>::Bind(globalObj);
}

CalcDimension JSSecurityUIExtension::GetSizeValue(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], value)) {
        return -1.0;
    }
    return value;
}

void JSSecurityUIExtension::JsWidth(const JSCallbackInfo& info)
{
    CalcDimension value = GetSizeValue(info);
    if (NeedCheckComponentSize() && LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    JSViewAbstract::JsWidth(info);
}

void JSSecurityUIExtension::JsHeight(const JSCallbackInfo& info)
{
    CalcDimension value = GetSizeValue(info);
    if (NeedCheckComponentSize() && LessNotEqual(value.Value(), 0.0)) {
        return;
    }
    JSViewAbstract::JsHeight(info);
}

void JSSecurityUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    NG::UIExtensionConfig config;
    config.sessionType = NG::SessionType::SECURITY_UI_EXTENSION_ABILITY;
    auto wantObj = JSRef<JSObject>::Cast(info[0]);
    RefPtr<OHOS::Ace::WantWrap> want = CreateWantWrapFromNapiValue(wantObj);
    if (want == nullptr) {
        TAG_LOGI(AceLogTag::ACE_SECURITYUIEXTENSION, "want is nullptr");
        return;
    }

    config.wantWrap = want;
    RefPtr<NG::FrameNode> placeholderNode = nullptr;
    if (info.Length() > 1 && info[1]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[1]);
        JSRef<JSVal> transferringCallerValue = obj->GetProperty("isTransferringCaller");
        if (transferringCallerValue->IsBoolean()) {
            config.transferringCaller = transferringCallerValue->ToBoolean();
        }
        JSRef<JSVal> enableDensityDPI = obj->GetProperty("dpiFollowStrategy");
        if (enableDensityDPI->IsNumber()) {
            config.densityDpi = (enableDensityDPI->ToNumber<int32_t>())==0 ? true : false;
        }
        do {
            JSRef<JSVal> componentContent = obj->GetProperty("placeholder");
            if (!componentContent->IsObject()) {
                break;
            }
            auto componentContentObj = JSRef<JSObject>::Cast(componentContent);
            JSRef<JSVal> builderNode = componentContentObj->GetProperty("builderNode_");
            if (!builderNode->IsObject()) {
                break;
            }
            auto builderNodeObj = JSRef<JSObject>::Cast(builderNode);
            JSRef<JSVal> nodePtr = builderNodeObj->GetProperty("nodePtr_");
            if (nodePtr.IsEmpty()) {
                break;
            }
            const auto* vm = nodePtr->GetEcmaVM();
            auto* node = nodePtr->GetLocalHandle()->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
            if (!frameNode) {
                break;
            }
            config.placeholderNode = AceType::Claim(frameNode);
        } while (false);
    }
    CreateInstanceAndSet(config);
}

void JSSecurityUIExtension::OnRemoteReady(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode =
        AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(
        JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRemoteReady = [execCtx = info.GetExecutionContext(),
        func = std::move(jsFunc), instanceId, node = frameNode]
            (const RefPtr<NG::SecurityUIExtensionProxy>& session) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            JSRef<JSObject> contextObj = JSClass<JSSecurityUIExtensionProxy>::NewInstance();
            RefPtr<JSSecurityUIExtensionProxy> proxy =
                Referenced::Claim(contextObj->Unwrap<JSSecurityUIExtensionProxy>());
            CHECK_NULL_VOID(proxy);
            proxy->SetInstanceId(instanceId);
            proxy->SetProxy(session);
            auto returnValue = JSRef<JSVal>::Cast(contextObj);
            func->ExecuteJS(1, &returnValue);
        };
    UIExtensionModel::GetInstance()->SetSecurityOnRemoteReady(std::move(onRemoteReady));
}

void JSSecurityUIExtension::OnReceive(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode =
        AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onReceive = [execCtx = info.GetExecutionContext(),
        func = std::move(jsFunc), instanceId, node = frameNode]
            (const AAFwk::WantParams& wantParams) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("SecurityUIExtensionComponent.UIExtensionDataSession.onReceive");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            auto engine = EngineHelper::GetCurrentEngine();
            CHECK_NULL_VOID(engine);
            NativeEngine* nativeEngine = engine->GetNativeEngine();
            CHECK_NULL_VOID(nativeEngine);
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            auto nativeWantParams = WantWrap::ConvertParamsToNativeValue(wantParams, env);
            auto wantParamsJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWantParams);
            func->ExecuteJS(1, &wantParamsJSVal);
        };
    UIExtensionModel::GetInstance()->SetOnReceive(
        std::move(onReceive), NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
}

void JSSecurityUIExtension::OnError(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode =
        AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
        instanceId, node = frameNode] (int32_t code, const std::string& name, const std::string& message) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("SecurityUIExtensionComponent.onError");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            obj->SetProperty<int32_t>("code", code);
            obj->SetProperty<std::string>("name", name);
            obj->SetProperty<std::string>("message", message);
            auto returnValue = JSRef<JSVal>::Cast(obj);
            func->ExecuteJS(1, &returnValue);
        };
    UIExtensionModel::GetInstance()->SetOnError(
        std::move(onError), NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
}

void JSSecurityUIExtension::OnTerminated(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode =
        AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onTerminated = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
        instanceId, node = frameNode] (int32_t code, const RefPtr<WantWrap>& wantWrap) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("SecurityUIExtensionComponent.onTerminated");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            auto engine = EngineHelper::GetCurrentEngine();
            CHECK_NULL_VOID(engine);
            NativeEngine* nativeEngine = engine->GetNativeEngine();
            CHECK_NULL_VOID(nativeEngine);
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            obj->SetProperty<int32_t>("code", code);
            if (wantWrap) {
                auto nativeWant = WantWrap::ConvertToNativeValue(
                    wantWrap->GetWant(), reinterpret_cast<napi_env>(nativeEngine));
                auto wantJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWant);
                obj->SetPropertyObject("want", wantJSVal);
            }
            auto returnValue = JSRef<JSVal>::Cast(obj);
            func->ExecuteJS(1, &returnValue);
        };
    UIExtensionModel::GetInstance()->SetOnTerminated(
        std::move(onTerminated), NG::SessionType::SECURITY_UI_EXTENSION_ABILITY);
}
} // namespace OHOS::Ace::Framework
