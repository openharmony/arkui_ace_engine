/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "ipc_skeleton.h"
#include "js_plugin_callback_mgr.h"
#include "js_plugin_util.h"
#include "js_plugin_want.h"
#include "tokenid_kit.h"

#include "core/components/plugin/plugin_component_manager.h"

namespace OHOS::Ace::Napi {
constexpr int ACE_ARGS_MAX_COUNT = 10;
constexpr int ACE_ARGS_TWO = 2;
constexpr int ACE_ARGS_THREE = 3;
constexpr int ACE_PARAM0 = 0;
constexpr int ACE_PARAM1 = 1;
constexpr int ACE_PARAM2 = 2;
constexpr int NAPI_ACE_ERR_ERROR = 1;

bool UnwrapStageWantFromJS(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (!AceUnwrapWant(env, param, asyncCallbackInfo->wantStage)) {
        return false;
    }
    return true;
}

bool UnwrapOwnerWantFromJS(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsValue = AceGetPropertyValueByPropertyName(env, param, "owner", napi_object);
    if (jsValue == nullptr) {
        return false;
    }

    if (!AceUnwrapWant(env, jsValue, asyncCallbackInfo->wantStage)) {
        return false;
    }

    auto selfToken = IPCSkeleton::GetSelfTokenID();
    if (!Security::AccessToken::TokenIdKit::IsSystemAppByFullTokenID(selfToken)) {
        TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "This application is not system-app, can not use system-api");
        return false;
    }

    return true;
}

bool UnwrapWantFromJS(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsValue = AceGetPropertyValueByPropertyName(env, param, "want", napi_object);
    if (jsValue == nullptr) {
        return false;
    }

    if (!AceUnwrapWant(env, jsValue, asyncCallbackInfo->jsParamList.want)) {
        return false;
    }
    return true;
}

bool UnwrapTargetFromJS(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsValue = AceGetPropertyValueByPropertyName(env, param, "target", napi_object);
    if (jsValue == nullptr) {
        return false;
    }

    if (!AceUnwrapWant(env, jsValue, asyncCallbackInfo->jsParamList.want)) {
        return false;
    }
    return true;
}

bool UnwrapNameFromJS(napi_env env, napi_value param, const std::string& key, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsValue = AceGetPropertyValueByPropertyName(env, param, key.c_str(), napi_string);
    if (jsValue == nullptr) {
        return false;
    }

    std::string strValue = AceUnwrapStringFromJS(env, jsValue);
    asyncCallbackInfo->jsParamList.paramList.PutStringValue(key, strValue);
    return true;
}

bool UnwrapKVObjectFromJS(
    napi_env env, napi_value param, const std::string& key, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsValue = AceGetPropertyValueByPropertyName(env, param, key.c_str(), napi_object);
    if (jsValue == nullptr) {
        return false;
    }

    std::string jsonString("{}");
    bool ret = AceKVObjectToString(env, jsValue, jsonString);
    if (ret) {
        asyncCallbackInfo->jsParamList.paramList.PutStringValue(key, jsonString);
    }
    return ret;
}

bool UnwrapPushParameters(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (!AceIsTypeForNapiValue(env, param, napi_object)) {
        return false;
    }

    bool isStageModelAPI = (asyncCallbackInfo->ability == nullptr);
    if (isStageModelAPI) {
        if (!UnwrapOwnerWantFromJS(env, param, asyncCallbackInfo)) {
            return false;
        }
    }

    if (!UnwrapWantFromJS(env, param, asyncCallbackInfo) && !UnwrapTargetFromJS(env, param, asyncCallbackInfo)) {
        return false;
    }
    if (!UnwrapNameFromJS(env, param, "name", asyncCallbackInfo)) {
        return false;
    }
    if (!UnwrapKVObjectFromJS(env, param, "data", asyncCallbackInfo)) {
        return false;
    }
    if (!UnwrapKVObjectFromJS(env, param, "extraData", asyncCallbackInfo)) {
        return false;
    }

    UnwrapNameFromJS(env, param, "jsonPath", asyncCallbackInfo);
    return true;
}

bool UnwrapParamForPush(napi_env env, size_t argc, napi_value* argv, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    const size_t argcMax = ACE_ARGS_TWO;
    if (argc <= 0 || argc > argcMax) {
        return false;
    }

    if (!UnwrapPushParameters(env, argv[ACE_PARAM0], asyncCallbackInfo)) {
        return false;
    }

    if (argc == argcMax) {
        if (!AceCreateAsyncCallback(env, argv[ACE_PARAM1], asyncCallbackInfo)) {
            return false;
        }
    }
    return true;
}

void JSPushCompleteAsyncCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }
    PluginComponentManager::GetInstance()->Push(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("extraData"));

    asyncCallbackInfo->error_code = 0;
    AceCompleteAsyncCallbackWork(env, asyncCallbackInfo);
}

void JSPushCompletePromiseCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }

    PluginComponentManager::GetInstance()->Push(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("extraData"));

    asyncCallbackInfo->error_code = 0;
    AceCompletePromiseCallbackWork(env, asyncCallbackInfo);
}

napi_value NAPI_JSPushWrap(napi_env env, napi_callback_info info, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    size_t argc = ACE_ARGS_MAX_COUNT;
    napi_value args[ACE_ARGS_MAX_COUNT] = { nullptr };
    napi_value jsthis = 0;
    void* data = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &jsthis, &data));
    if (!UnwrapParamForPush(env, argc, args, asyncCallbackInfo)) {
        return nullptr;
    }

    if (asyncCallbackInfo->cbInfo.callback != nullptr) {
        JSPushCompleteAsyncCallbackWork(env, asyncCallbackInfo);
        return AceWrapVoidToJS(env);
    } else {
        napi_value promise = 0;
        NAPI_CALL(env, napi_create_promise(env, &asyncCallbackInfo->deferred, &promise));
        JSPushCompletePromiseCallbackWork(env, asyncCallbackInfo);
        return promise;
    }
}

static napi_value JSPush(napi_env env, napi_callback_info info)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    if (asyncCallbackInfo == nullptr) {
        return AceWrapVoidToJS(env);
    }

    napi_value rev = NAPI_JSPushWrap(env, info, asyncCallbackInfo);
    if (rev == nullptr) {
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        rev = AceWrapVoidToJS(env);
    }
    return rev;
}

bool UnwrapRequestParameters(napi_env env, napi_value param, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (!AceIsTypeForNapiValue(env, param, napi_object)) {
        return false;
    }

    bool isStageModelAPI = (asyncCallbackInfo->ability == nullptr);
    if (isStageModelAPI) {
        if (!UnwrapOwnerWantFromJS(env, param, asyncCallbackInfo)) {
            return false;
        }
    }

    if (!UnwrapWantFromJS(env, param, asyncCallbackInfo) && !UnwrapTargetFromJS(env, param, asyncCallbackInfo)) {
        return false;
    }
    if (!UnwrapNameFromJS(env, param, "name", asyncCallbackInfo)) {
        return false;
    }
    if (!UnwrapKVObjectFromJS(env, param, "data", asyncCallbackInfo)) {
        return false;
    }

    UnwrapNameFromJS(env, param, "jsonPath", asyncCallbackInfo);
    return true;
}

bool UnwrapParamForRequest(napi_env env, size_t argc, napi_value* argv, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (argc <= 0 || argc > ACE_ARGS_TWO) {
        return false;
    }

    if (!UnwrapRequestParameters(env, argv[ACE_PARAM0], asyncCallbackInfo)) {
        return false;
    }

    if (argc == ACE_ARGS_TWO) {
        if (!AceCreateAsyncCallback(env, argv[ACE_PARAM1], asyncCallbackInfo)) {
            return false;
        }
    }
    return true;
}

void AceRequestCompleteAsyncCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }

    if (asyncCallbackInfo->ability != nullptr) {
        std::shared_ptr<AAFwk::Want> pWant = asyncCallbackInfo->ability->GetWant();
        asyncCallbackInfo->wantStage = *pWant;
    } else {
        int32_t pid = IPCSkeleton::GetCallingPid();
        asyncCallbackInfo->wantStage.SetBundle("plugin" + std::to_string(pid));
    }

    std::shared_ptr<AceJSPluginRequestParam> param = std::make_shared<AceJSPluginRequestParam>(
        asyncCallbackInfo->jsParamList.want, asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"));
    if (param != nullptr) {
        TAG_LOGD(AceLogTag::ACE_PLUGIN_COMPONENT, "Want = %{public}s:%{public}s",
            asyncCallbackInfo->wantStage.GetElement().GetBundleName().c_str(),
            asyncCallbackInfo->wantStage.GetElement().GetAbilityName().c_str());
        bool ret = JSPluginCallbackMgr::Instance().RegisterRequestEvent(
            env, asyncCallbackInfo->wantStage, asyncCallbackInfo->cbInfo, param);
        if (ret) {
            asyncCallbackInfo->cbInfo.callback = nullptr;
        }
    }

    PluginComponentManager::GetInstance()->Request(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"));

    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

napi_value MakePluginTemplateObject(napi_env env, const PluginComponentTemplate& pluginTemplate)
{
    napi_value jsPluginTemplate = AceCreateJSObject(env);
    if (jsPluginTemplate != nullptr) {
        napi_value jsSource = AceWrapStringToJS(env, pluginTemplate.GetSource());
        napi_value jsAbility = AceWrapStringToJS(env, pluginTemplate.GetAbility());

        AceSetPropertyValueByPropertyName(env, jsPluginTemplate, "source", jsSource);
        AceSetPropertyValueByPropertyName(env, jsPluginTemplate, "ability", jsAbility);
    }
    return jsPluginTemplate;
}

napi_value MakeCallbackParamForRequest(
    napi_env env, const PluginComponentTemplate& pluginTemplate, const ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    napi_value jsObject = AceCreateJSObject(env);
    if (jsObject == nullptr) {
        return nullptr;
    }
    std::string dataTmp("{}");
    std::string extraDataTmp("{}");
    if (!asyncCallbackInfo->requestCallbackData.data.empty()) {
        dataTmp = asyncCallbackInfo->requestCallbackData.data;
    }
    if (!asyncCallbackInfo->requestCallbackData.extraData.empty()) {
        extraDataTmp = asyncCallbackInfo->requestCallbackData.extraData;
    }

    napi_value jsPluginTemplate = MakePluginTemplateObject(env, pluginTemplate);
    napi_value jsData = AceStringToKVObject(env, dataTmp);
    napi_value jsExtraData = AceStringToKVObject(env, extraDataTmp);

    if (jsData != nullptr) {
        AceSetPropertyValueByPropertyName(env, jsObject, "componentTemplate", jsPluginTemplate);
    }
    if (jsData != nullptr) {
        AceSetPropertyValueByPropertyName(env, jsObject, "data", jsData);
    }
    if (jsExtraData != nullptr) {
        AceSetPropertyValueByPropertyName(env, jsObject, "extraData", jsExtraData);
    }
    return jsObject;
}

napi_value TransferRequestCallBackData(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    PluginComponentTemplate componentTemplate;
    componentTemplate.SetSource(asyncCallbackInfo->requestCallbackData.sourceName);
    componentTemplate.SetAbility(asyncCallbackInfo->requestCallbackData.abilityName);
    napi_value jsResult = MakeCallbackParamForRequest(env, componentTemplate, asyncCallbackInfo);
    return jsResult;
}

void AceRequestPromiseAsyncCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }

    if (asyncCallbackInfo->ability != nullptr) {
        std::shared_ptr<AAFwk::Want> pWant = asyncCallbackInfo->ability->GetWant();
        asyncCallbackInfo->wantStage = *pWant;
    } else {
        int32_t pid = IPCSkeleton::GetCallingPid();
        asyncCallbackInfo->wantStage.SetBundle("plugin" + std::to_string(pid));
    }

    std::shared_ptr<AceJSPluginRequestParam> param = std::make_shared<AceJSPluginRequestParam>(
        asyncCallbackInfo->jsParamList.want, asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"));
    asyncCallbackInfo->onRequestCallbackOK = false;

    if (param != nullptr) {
        TAG_LOGD(AceLogTag::ACE_PLUGIN_COMPONENT, "Want = %{public}s:%{public}s",
            asyncCallbackInfo->wantStage.GetElement().GetBundleName().c_str(),
            asyncCallbackInfo->wantStage.GetElement().GetAbilityName().c_str());
        JSPluginCallbackMgr::Instance().RegisterRequestEvent(
            env, asyncCallbackInfo->wantStage, asyncCallbackInfo, param);
    }

    PluginComponentManager::GetInstance()->Request(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"));

    if (asyncCallbackInfo->onRequestCallbackOK) {
        asyncCallbackInfo->error_code = 0;
        napi_resolve_deferred(env, asyncCallbackInfo->deferred, TransferRequestCallBackData(env, asyncCallbackInfo));
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
    } else {
        asyncCallbackInfo->error_code = NAPI_ACE_ERR_ERROR;
        AceCompletePromiseCallbackWork(env, asyncCallbackInfo);
    }
}

napi_value NAPI_JSRequestWrap(napi_env env, napi_callback_info info, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    size_t argc = ACE_ARGS_MAX_COUNT;
    napi_value args[ACE_ARGS_MAX_COUNT] = { nullptr };
    napi_value jsthis = 0;
    void* data = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &jsthis, &data));

    if (!UnwrapParamForRequest(env, argc, args, asyncCallbackInfo)) {
        return nullptr;
    }

    if (asyncCallbackInfo->cbInfo.callback != nullptr) {
        AceRequestCompleteAsyncCallbackWork(env, asyncCallbackInfo);
        return AceWrapVoidToJS(env);
    } else {
        napi_value promise = 0;
        NAPI_CALL(env, napi_create_promise(env, &asyncCallbackInfo->deferred, &promise));
        AceRequestPromiseAsyncCallbackWork(env, asyncCallbackInfo);
        return promise;
    }
}

static napi_value JSRequest(napi_env env, napi_callback_info info)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    if (asyncCallbackInfo == nullptr) {
        return AceWrapVoidToJS(env);
    }

    napi_value rev = NAPI_JSRequestWrap(env, info, asyncCallbackInfo);
    if (rev == nullptr) {
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        rev = AceWrapVoidToJS(env);
    }
    return rev;
}

bool UnwrapParamForOn(napi_env env, size_t argc, napi_value* argv, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    const size_t argcMax = ACE_ARGS_THREE;
    if (argc > argcMax || argc < ACE_ARGS_TWO) {
        return false;
    }

    if (argc == ACE_ARGS_THREE) {
        if (!UnwrapStageWantFromJS(env, argv[ACE_PARAM0], asyncCallbackInfo)) {
            return false;
        }

        std::string eventName = AceUnwrapStringFromJS(env, argv[ACE_PARAM1]);
        if (eventName == "push" || eventName == "request") {
            asyncCallbackInfo->jsParamList.paramList.PutStringValue("eventName", eventName);
        } else {
            return false;
        }

        if (!AceCreateAsyncCallback(env, argv[ACE_PARAM2], asyncCallbackInfo)) {
            return false;
        }
    } else {
        std::string eventName = AceUnwrapStringFromJS(env, argv[ACE_PARAM0]);
        if (eventName == "push" || eventName == "request") {
            asyncCallbackInfo->jsParamList.paramList.PutStringValue("eventName", eventName);
        } else {
            return false;
        }

        if (!AceCreateAsyncCallback(env, argv[ACE_PARAM1], asyncCallbackInfo)) {
            return false;
        }
    }
    return true;
}

void AceOnCompleteAsyncCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }

    std::string eventName = asyncCallbackInfo->jsParamList.paramList.GetStringValue("eventName");
    CallBackType eventCallbackType = CallBackType::PushEvent;
    if (eventName == "request") {
        eventCallbackType = CallBackType::RequestEvent;
    }

    if (asyncCallbackInfo->ability != nullptr) {
        std::shared_ptr<AAFwk::Want> pWant = asyncCallbackInfo->ability->GetWant();
        asyncCallbackInfo->wantStage = *pWant;
    } else {
        int32_t pid = IPCSkeleton::GetCallingPid();
        asyncCallbackInfo->wantStage.SetBundle("plugin" + std::to_string(pid));
    }

    bool ret = JSPluginCallbackMgr::Instance().RegisterOnEvent(
        env, eventCallbackType, asyncCallbackInfo->wantStage, asyncCallbackInfo->cbInfo);
    if (ret) {
        asyncCallbackInfo->cbInfo.callback = nullptr;
    }
    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

napi_value NAPI_JSOnWrap(napi_env env, napi_callback_info info, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    size_t argc = ACE_ARGS_MAX_COUNT;
    napi_value args[ACE_ARGS_MAX_COUNT] = { nullptr };
    napi_value jsthis = 0;
    void* data = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &jsthis, &data));

    if (!UnwrapParamForOn(env, argc, args, asyncCallbackInfo)) {
        return nullptr;
    }

    if (asyncCallbackInfo->cbInfo.callback != nullptr) {
        AceOnCompleteAsyncCallbackWork(env, asyncCallbackInfo);
        return AceWrapVoidToJS(env);
    } else {
        return nullptr;
    }
}

static napi_value JSOn(napi_env env, napi_callback_info info)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    if (asyncCallbackInfo == nullptr) {
        return AceWrapVoidToJS(env);
    }

    napi_value rev = NAPI_JSOnWrap(env, info, asyncCallbackInfo);
    if (rev == nullptr) {
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        rev = AceWrapVoidToJS(env);
    }
    return rev;
}

bool UnwrapParamForOff(napi_env env, size_t argc, napi_value* argv, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (argc != ACE_ARGS_TWO) {
        return false;
    }

    if (!UnwrapStageWantFromJS(env, argv[ACE_PARAM0], asyncCallbackInfo)) {
        return false;
    }

    if (!AceCreateAsyncCallback(env, argv[ACE_PARAM1], asyncCallbackInfo)) {
        return false;
    }

    return true;
}

void AceOffCompleteAsyncCallbackWork(napi_env env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }

    JSPluginCallbackMgr::Instance().UnregisterCallBack(env, asyncCallbackInfo->wantStage);
    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

napi_value NAPI_JSOffWrap(napi_env env, napi_callback_info info, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    size_t argc = ACE_ARGS_MAX_COUNT;
    napi_value args[ACE_ARGS_MAX_COUNT] = { nullptr };
    napi_value jsthis = 0;
    void* data = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &jsthis, &data));

    if (!UnwrapParamForOff(env, argc, args, asyncCallbackInfo)) {
        return nullptr;
    }

    if (asyncCallbackInfo->cbInfo.callback != nullptr) {
        AceOffCompleteAsyncCallbackWork(env, asyncCallbackInfo);
        return AceWrapVoidToJS(env);
    } else {
        return nullptr;
    }
}

static napi_value JSOff(napi_env env, napi_callback_info info)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    if (asyncCallbackInfo == nullptr) {
        return AceWrapVoidToJS(env);
    }

    napi_value rev = NAPI_JSOffWrap(env, info, asyncCallbackInfo);
    if (rev == nullptr) {
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        rev = AceWrapVoidToJS(env);
    }
    return rev;
}

napi_value PluginComponentEventTypeInit(napi_env env, napi_value exports)
{
    napi_value obj = nullptr;
    napi_create_object(env, &obj);

    AceSetNamedPropertyByString(env, obj, "push", "EVENT_TYPE_PUSH");
    AceSetNamedPropertyByString(env, obj, "request", "EVENT_TYPE_REQUEST");

    napi_property_descriptor properties[] = {
        DECLARE_NAPI_PROPERTY("EventType", obj),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

napi_value PluginComponentInit(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("push", JSPush),
        DECLARE_NAPI_FUNCTION("request", JSRequest),
        DECLARE_NAPI_FUNCTION("on", JSOn),
        DECLARE_NAPI_FUNCTION("off", JSOff),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_value PluginComponentExport(napi_env env, napi_value exports)
{
    PluginComponentEventTypeInit(env, exports);
    PluginComponentInit(env, exports);
    return exports;
}

static napi_module PlugInComonentModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PluginComponentExport,
    .nm_modname = "pluginComponent",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterPluginComponent()
{
    napi_module_register(&PlugInComonentModule);
}
} // namespace OHOS::Ace::Napi
