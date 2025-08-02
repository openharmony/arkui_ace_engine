/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <string>
#include <ani.h>
#include "ani_plugin_callback.h"
#include "ani_plugin_component_util.h"
#include "ani_common_want.h"
#include "ani_plugin_callback_mgr.h"
#include "base/log/log_wrapper.h"
#include "core/components/plugin/plugin_component_manager.h"
#include "ipc_skeleton.h"
#include "tokenid_kit.h"

namespace {
    const char ANI_PLUGINCOMPONENT_NS[] = "L@ohos/pluginComponent/pluginComponentManager;";
} // namespace

namespace OHOS::Ace::Ani {
using namespace OHOS::Ace;
    
static bool GetAniWantPropertyByName(ani_env* env, ani_object parameters, std::string propertyName,
    OHOS::AAFwk::Want &want)
{
    ani_ref wantAni;
    env->Object_GetPropertyByName_Ref(parameters, propertyName.c_str(), &wantAni);
    ani_boolean isUndefined = true;
    if (ANI_OK != env->Reference_IsUndefined(wantAni, &isUndefined) || isUndefined) {
        LOGE("plugin-ani GetAniWantPropertyByName %{public}s is null", propertyName.c_str());
        return false;
    }
    auto ownerWant = reinterpret_cast<ani_object>(wantAni);
    bool ret = OHOS::AppExecFwk::UnwrapWant(env, ownerWant, want);
    if (!ret) {
        LOGE("plugin-ani GetAniWantPropertyByName %{public}s error", propertyName.c_str());
    }
    return ret;
}

static bool ParsePushAndRequestParameters(ani_env* env, ACEAsyncJSCallbackInfo* asyncCallbackInfo,
    ani_object parameters)
{
    // name(string) of PushParameterForStage
    std::string name;
    if (ANI_OK != GetAniStringPropertyByName(env, parameters, "name", name)) {
        return false;
    }
    asyncCallbackInfo->jsParamList.paramList.PutStringValue("name", name);
    
    // owner(want) of PushParameterForStage
    auto ret = GetAniWantPropertyByName(env, parameters, "owner", asyncCallbackInfo->wantStage);
    if (!ret) {
        return false;
    }
    
    auto selfToken = IPCSkeleton::GetSelfTokenID();
    if (!Security::AccessToken::TokenIdKit::IsSystemAppByFullTokenID(selfToken)) {
        LOGE("plugin-ani This application is not system-app, can not use system-api");
        return false;
    }
    
    // target(want) of PushParameterForStage
    ret = GetAniWantPropertyByName(env, parameters, "target", asyncCallbackInfo->jsParamList.want);
    if (!ret) {
        return false;
    }
    
    // jsonPath?(string) of PushParameterForStage
    std::string jsonPath;
    if (ANI_OK == GetAniStringPropertyByName(env, parameters, "jsonPath", jsonPath)) {
        asyncCallbackInfo->jsParamList.paramList.PutStringValue("jsonPath", jsonPath);
    }
    
    // data(KVObject) of PushParameterForStage
    std::string data;
    if (ANI_OK != GetAniKVObjectPropertyByName(env, parameters, "data", data)) {
        return false;
    }
    asyncCallbackInfo->jsParamList.paramList.PutStringValue("data", data);
    return true;
}

static void ParsePushParameters(ani_env* env, ACEAsyncJSCallbackInfo* asyncCallbackInfo,
    ani_object pushParameters, ani_fn_object fnObj)
{
    if (!ParsePushAndRequestParameters(env, asyncCallbackInfo, pushParameters)) {
        return;
    }
    
    // extraData(KVObject) of PushParameterForStage
    std::string extraData;
    if (ANI_OK != GetAniKVObjectPropertyByName(env, pushParameters, "extraData", extraData)) {
        return;
    }
    asyncCallbackInfo->jsParamList.paramList.PutStringValue("extraData", extraData);
    
    PluginComponentManager::GetInstance()->Push(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("extraData"));
    
    std::vector<ani_ref> vec;
    ani_ref fnReturnVal;
    auto param = CreateInt(env, ani_int(0));
    vec.push_back(param);
    auto status = env->FunctionalObject_Call(fnObj, vec.size(), vec.data(), &fnReturnVal);
    if (status != ANI_OK) {
        LOGE("plugin-ani ParsePushParameters failed %{public}d", status);
    }
}

static void Push([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object pushParameters, ani_fn_object fnObj)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    ParsePushParameters(env, asyncCallbackInfo, pushParameters, fnObj);
    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

void AceRequestCompleteAsyncCallbackWork(ani_env* env, ACEAsyncJSCallbackInfo* asyncCallbackInfo)
{
    int32_t pid = IPCSkeleton::GetCallingPid();
    asyncCallbackInfo->wantStage.SetBundle("plugin" + std::to_string(pid));
    std::shared_ptr<AceJSPluginRequestParam> param = std::make_shared<AceJSPluginRequestParam>(
        asyncCallbackInfo->jsParamList.want, asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath")
    );
    bool ret = ANIPluginCallbackMgr::Instance().RegisterRequestEvent(env, asyncCallbackInfo->wantStage,
        asyncCallbackInfo->cbInfo, param);
    LOGI("plugin-ani RegisterRequestEvent result is %{public}d", ret);
    PluginComponentManager::GetInstance()->Request(asyncCallbackInfo->jsParamList.want,
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("name"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("jsonPath"),
        asyncCallbackInfo->jsParamList.paramList.GetStringValue("data"));
}

static void Request([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object requestParameters, ani_fn_object fnObj)
{
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    bool ret = ParsePushAndRequestParameters(env, asyncCallbackInfo, requestParameters);
    if (!ret) {
        LOGE("plugin-ani parse request params fail");
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    if (ANI_OK != env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef)) {
        LOGE("plugin-ani get request call back failed");
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        return;
    }
    asyncCallbackInfo->cbInfo.callback = fnObjGlobalRef;
    AceRequestCompleteAsyncCallbackWork(env, asyncCallbackInfo);
    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

static void On([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_string eventTypeAni, ani_fn_object fnObj)
{
    std::string eventType = AniStringToNativeString(env, eventTypeAni);
    if (eventType != "push" && eventType != "request") {
        LOGE("plugin-ani Unsupported event type %{public}s", eventType.c_str());
        return;
    }
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = AceCreateAsyncJSCallbackInfo(env);
    asyncCallbackInfo->jsParamList.paramList.PutStringValue("eventName", eventType);
    ani_ref fnObjGlobalRef = nullptr;
    if (ANI_OK != env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef)) {
        LOGE("plugin-ani get %{public}s call back failed", eventType.c_str());
        AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
        return;
    }
    asyncCallbackInfo->cbInfo.callback = fnObjGlobalRef;
    CallBackType eventCallbackType = CallBackType::PushEvent;
    if (eventType == "request") {
        eventCallbackType = CallBackType::RequestEvent;
    }
    int32_t pid = IPCSkeleton::GetCallingPid();
    asyncCallbackInfo->wantStage.SetBundle("plugin" + std::to_string(pid));
    ANIPluginCallbackMgr::Instance().RegisterOnEvent(env, eventCallbackType, asyncCallbackInfo->wantStage,
        asyncCallbackInfo->cbInfo);
    AceFreeAsyncJSCallbackInfo(&asyncCallbackInfo);
}

} // namespace OHOS::Ace::Ani
ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOGE("plugin-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_PLUGINCOMPONENT_NS, &ns)) {
        LOGE("plugin-ani Not found ns");
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"pushNative", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::Ani::Push)},
        ani_native_function {"requestNative", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::Ani::Request)},
        ani_native_function {"on", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::Ani::On)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        LOGE("plugin-ani Namespace_BindNativeFunctions error");
        return ANI_ERROR;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}