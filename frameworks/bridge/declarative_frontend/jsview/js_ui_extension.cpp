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
#include "want_params.h"

#include "base/log/ace_scoring_log.h"
#include "base/want/want_wrap.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "interfaces/include/ws_common.h"

namespace OHOS::Ace {
UIExtensionModel* UIExtensionModel::GetInstance()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("Get UIExtensionModel in non NewPipeline.");
    }
    static NG::UIExtensionModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const char UI_EXTENSION_PLACEHOLDER_TYPE_UNDEFINED[] = "UNDEFINED";
const char UI_EXTENSION_PLACEHOLDER_TYPE_ROTATION[] = "ROTATION";
const char UI_EXTENSION_PLACEHOLDER_TYPE_FOLD_TO_EXPAND[] = "FOLD_TO_EXPAND";

void JSUIExtensionProxy::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtensionProxy>::Declare("UIExtensionProxy ");
    JSClass<JSUIExtensionProxy>::CustomMethod("send", &JSUIExtensionProxy::Send);
    JSClass<JSUIExtensionProxy>::CustomMethod("sendSync", &JSUIExtensionProxy::SendSync);
    JSClass<JSUIExtensionProxy>::CustomMethod("on", &JSUIExtensionProxy::On);
    JSClass<JSUIExtensionProxy>::CustomMethod("off", &JSUIExtensionProxy::Off);
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

void JSUIExtensionProxy::SendSync(const JSCallbackInfo& info)
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
    auto wantParams = WantParamsWrap::CreateWantWrap(reinterpret_cast<napi_env>(nativeEngine), nativeValue);
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
        auto reNativeWantParams =
            WantWrap::ConvertParamsToNativeValue(reWantParams, reinterpret_cast<napi_env>(nativeEngine));
        auto reWantParamsJSVal = Framework::JsConverter::ConvertNapiValueToJsVal(reNativeWantParams);
        info.SetReturnValue(reWantParamsJSVal);
    }
}

CallbackFuncPairList::const_iterator JSUIExtensionProxy::FindCbList(napi_env env, napi_value cb,
    CallbackFuncPairList& callbackFuncPairList)
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

void JSUIExtensionProxy::AddCallbackToList(napi_env env, napi_value cb,
    napi_handle_scope scope, RegisterType type,
    const std::function<void(const RefPtr<NG::UIExtensionProxy>&)>&& onFunc)
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

void JSUIExtensionProxy::DeleteCallbackFromList(int argc, napi_env env, napi_value cb, RegisterType type)
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
    } else if (argc == 2) {
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

std::list<std::function<void(const RefPtr<NG::UIExtensionProxy>&)>> JSUIExtensionProxy::GetOnFuncList(
    RegisterType type)
{
    std::list<std::function<void(const RefPtr<NG::UIExtensionProxy>&)>> reList;
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

RegisterType JSUIExtensionProxy::GetRegisterType(const std::string& strType)
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

void JSUIExtensionProxy::On(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() || !info[1]->IsFunction()) {
        return;
    }
    const RegisterType registerType = GetRegisterType(info[0]->ToString());
    if (registerType == RegisterType::UNKNOWN) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    auto instanceId = ContainerScope::CurrentId();
    auto onOnFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (const RefPtr<NG::UIExtensionProxy>& session) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        JSRef<JSObject> contextObj = JSClass<JSUIExtensionProxy>::NewInstance();
        RefPtr<JSUIExtensionProxy> proxy = Referenced::Claim(contextObj->Unwrap<JSUIExtensionProxy>());
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

void JSUIExtensionProxy::Off(const JSCallbackInfo& info)
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
    JSClass<JSUIExtension>::StaticMethod("onTerminated", &JSUIExtension::OnTerminated);
    JSClass<JSUIExtension>::StaticMethod("onDrawReady", &JSUIExtension::OnDrawReady);
    JSClass<JSUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::ResolveAreaPlaceholderParams(const JSRef<JSObject>& obj,
    std::map<NG::PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap)
{
    static const std::map<std::string, NG::PlaceholderType> placeholderTypeTable = {
        { UI_EXTENSION_PLACEHOLDER_TYPE_UNDEFINED, NG::PlaceholderType::UNDEFINED },
        { UI_EXTENSION_PLACEHOLDER_TYPE_ROTATION, NG::PlaceholderType::ROTATION },
        { UI_EXTENSION_PLACEHOLDER_TYPE_FOLD_TO_EXPAND, NG::PlaceholderType::FOLD_TO_EXPAND }
    };
    do {
        JSRef<JSVal> componentContentMap = obj->GetProperty("areaChangePlaceholder");
        if (!componentContentMap->IsObject()) {
            break;
        }
        auto contentMapObj = JSRef<JSObject>::Cast(componentContentMap);
        for (auto [strName, type] : placeholderTypeTable) {
            JSRef<JSVal> typeContent = contentMapObj->GetProperty(strName.c_str());
            if (!typeContent->IsObject()) {
                continue;
            }
            auto componentContentObj = JSRef<JSObject>::Cast(typeContent);
            JSRef<JSVal> builderNode = componentContentObj->GetProperty("builderNode_");
            if (!builderNode->IsObject()) {
                continue;
            }
            auto builderNodeObj = JSRef<JSObject>::Cast(builderNode);
            JSRef<JSVal> nodePtr = builderNodeObj->GetProperty("nodePtr_");
            if (nodePtr.IsEmpty()) {
                continue;
            }
            const auto* vm = nodePtr->GetEcmaVM();
            if (!(nodePtr->GetLocalHandle()->IsNativePointer(vm))) {
                continue;
            }
            auto* node = nodePtr->GetLocalHandle()->ToNativePointer(vm)->Value();
            auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
            if (!frameNode) {
                continue;
            }
            RefPtr<NG::FrameNode> placeholderNode = AceType::Claim(frameNode);
            placeholderMap.insert({type, placeholderNode});
        }
    } while (false);
}

namespace {
void InsertPlaceholderObj(JsiRef<JsiObject>& obj,
    std::map<NG::PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap)
{
    do {
        RefPtr<NG::FrameNode> placeholderNode = nullptr;
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
        if (!(nodePtr->GetLocalHandle()->IsNativePointer(vm))) {
            break;
        }
        auto* node = nodePtr->GetLocalHandle()->ToNativePointer(vm)->Value();
        auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
        if (!frameNode) {
            break;
        }
        placeholderNode = AceType::Claim(frameNode);
        placeholderMap.insert({NG::PlaceholderType::INITIAL, placeholderNode});
    } while (false);
}
} // namespace

void JSUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto wantObj = JSRef<JSObject>::Cast(info[0]);
    RefPtr<OHOS::Ace::WantWrap> want = CreateWantWrapFromNapiValue(wantObj);

    bool transferringCaller = false;
    bool densityDpi = false;
    bool windowModeStrategy = false;
    std::map<NG::PlaceholderType, RefPtr<NG::FrameNode>> placeholderMap;
    if (info.Length() > 1 && info[1]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[1]);
        JSRef<JSVal> transferringCallerValue = obj->GetProperty("isTransferringCaller");
        if (transferringCallerValue->IsBoolean()) {
            transferringCaller = transferringCallerValue->ToBoolean();
        }
        JSRef<JSVal> enableDensityDPI = obj->GetProperty("dpiFollowStrategy");
        if (enableDensityDPI->IsNumber()) {
            densityDpi = (enableDensityDPI->ToNumber<int32_t>())==0 ? true : false;
        }
        JSRef<JSVal> windowModeStrategyValue = obj->GetProperty("windowModeFollowStrategy");
        if (windowModeStrategyValue->IsNumber()) {
            windowModeStrategy = (windowModeStrategyValue->ToNumber<int32_t>()) == 0 ? true : false;
        }
        InsertPlaceholderObj(obj, placeholderMap);
        ResolveAreaPlaceholderParams(obj, placeholderMap);
    }
    UIExtensionModel::GetInstance()->Create(want, placeholderMap, transferringCaller, densityDpi, windowModeStrategy);
}

void JSUIExtension::OnRemoteReady(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRemoteReady = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (const RefPtr<NG::UIExtensionProxy>& session) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        JSRef<JSObject> contextObj = JSClass<JSUIExtensionProxy>::NewInstance();
        RefPtr<JSUIExtensionProxy> proxy = Referenced::Claim(contextObj->Unwrap<JSUIExtensionProxy>());
        CHECK_NULL_VOID(proxy);
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onReceive = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (const AAFwk::WantParams& wantParams) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("UIExtensionComponent.UIExtensionDataSession.onReceive");
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
    UIExtensionModel::GetInstance()->SetOnReceive(std::move(onReceive));
}

void JSUIExtension::OnRelease(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRelease = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (int32_t releaseCode) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("UIExtensionComponent.onRelease");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onResult = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (int32_t code, const AAFwk::Want& want) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onResult");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        (int32_t code, const std::string& name, const std::string& message) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onError");
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
    UIExtensionModel::GetInstance()->SetOnError(std::move(onError));
}

void JSUIExtension::OnTerminated(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onTerminated = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                            int32_t code, const RefPtr<WantWrap>& wantWrap) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("EmbeddedComponent.onTerminated");
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
            auto nativeWant =
                WantWrap::ConvertToNativeValue(wantWrap->GetWant(), reinterpret_cast<napi_env>(nativeEngine));
            auto wantJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWant);
            obj->SetPropertyObject("want", wantJSVal);
        }
        auto returnValue = JSRef<JSVal>::Cast(obj);
        func->ExecuteJS(1, &returnValue);
    };
    UIExtensionModel::GetInstance()->SetOnTerminated(std::move(onTerminated));
}

void JSUIExtension::OnDrawReady(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onDrawReady = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode]
        () {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onDrawReady");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            auto newJSVal = JSRef<JSVal>::Make();
            func->ExecuteJS(1, &newJSVal);
    };
    UIExtensionModel::GetInstance()->SetOnDrawReady(std::move(onDrawReady));
}
} // namespace OHOS::Ace::Framework
