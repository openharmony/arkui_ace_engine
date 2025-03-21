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
#include "bridge/arkts_frontend/arkts_frontend.h"

#include <ani.h>

#include "interfaces/inner_api/ace/constants.h"
#include "arkcompiler/runtime_core/static_core/plugins/ets/runtime/napi/ets_napi.h"

#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace {
UIContentErrorCode ArktsFrontend::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    return UIContentErrorCode::NO_ERRORS;
}

namespace {
/* copied from arkcompiler_ets_frontend vmloader.cc*/
struct AppInfo {
    const char* className;
    const char* createMethodName;
    const char* createMethodSig;
    const char* startMethodName;
    const char* startMethodSig;
    const char* enterMethodName;
    const char* enterMethodSig;
    const char* emitEventMethodName;
    const char* emitEventMethodSig;
};
/* copied from arkcompiler_ets_frontend vmloader.cc*/
const AppInfo KOALA_APP_INFO = {
    "L@koalaui/arkts-arkui/ArkUIEntry/Application;",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZL@koalaui/arkts-arkui/UserView/UserView;:L@koalaui/arkts-arkui/ArkUIEntry/Application;",
    "start",
    ":J",
    "enter",
    "IIJ:Z",
    "emitEvent",
    "IIII:V",
};

// void TryEmitError(EtsEnv& env)
// {
//     if (env.ErrorCheck()) {
//         env.ErrorDescribe();
//         env.ErrorClear();
//     }
// }

void RunArkoalaEventLoop(ani_env* env, ani_ref app)
{
    ani_class appClass;
    if (env->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
        LOGE("[%{public}s] Cannot load main class %{}s", __func__, KOALA_APP_INFO.className);
        return;
    }
 
    ani_method enter = nullptr;
    if (env->Class_FindMethod(appClass, KOALA_APP_INFO.enterMethodName, KOALA_APP_INFO.enterMethodSig, &enter) !=
        ANI_OK) {
        LOGE("[%{public}s] Cannot find enter method %{public}s", __func__, KOALA_APP_INFO.enterMethodName);
        // TryEmitError(env);
        return;
    }
 
    ani_int arg0 = 0;
    ani_int arg1 = 0;
    ani_boolean result;
    if (env->Object_CallMethod_Boolean(static_cast<ani_object>(app), enter, &result, arg0, arg1, nullptr) != ANI_OK) {
        LOGE("[%{public}s] Call enter method failed", __func__);
        return;
    }
    // auto terminate = env.CallBooleanMethod((ets_object)(app), (ets_method)(enter), (ets_int)0, (ets_int)0);
    // TryEmitError(env);
    // if (terminate) {
    //     exit(0);
    // }
}
} // namespace

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    ani_class appClass;
    if (env_->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
        LOGE("Cannot load main class %{public}s", KOALA_APP_INFO.className);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_static_method create;
    if (env_->Class_FindStaticMethod(
            appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig, &create) != ANI_OK) {
        LOGE("Cannot find create method %{public}s", KOALA_APP_INFO.createMethodName);
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    std::string appUrl = "ComExampleTrivialApplication"; // TODO: use passed in url and params
    std::string appParams = "ArkTSLoaderParam";

    ani_status state;
    ani_ref linkerRef;
    if ((state = static_cast<ani_status>(ArktsAniUtils::GetNearestNonBootRuntimeLinker(env_, linkerRef))) != ANI_OK) {
        LOGE("Get getNearestNonBootRuntimeLinker failed, %{public}d", state);
        return UIContentErrorCode::INVALID_URL;
    }

    std::string entryPath = "entry/src/main/ets/pages/Index/ComExampleTrivialApplication";
    ani_string entryClassStr;
    env_->String_NewUTF8(entryPath.c_str(), entryPath.length(), &entryClassStr);
    ani_class entryClass = nullptr;
    ani_ref entryClassRef = nullptr;

    ani_class cls = nullptr;
    if ((state = env_->FindClass("Lstd/core/RuntimeLinker;", &cls)) != ANI_OK) {
        LOGE("FindClass RuntimeLinker failed, %{public}d", state);
        return UIContentErrorCode::INVALID_URL;
    }
    ani_method loadClassMethod;
    if ((state = env_->Class_FindMethod(
             cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;", &loadClassMethod)) != ANI_OK) {
        LOGE("Class_FindMethod loadClass failed, %{public}d", state);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_object isInit;
    if ((state = static_cast<ani_status>(ArktsAniUtils::CreateAniBoolean(env_, false, isInit))) != ANI_OK) {
        LOGE("Create Boolean object failed, %{public}d", state);
        return UIContentErrorCode::INVALID_URL;
    }

    if ((state = env_->Object_CallMethod_Ref(
             (ani_object)linkerRef, loadClassMethod, &entryClassRef, entryClassStr, isInit)) != ANI_OK) {
        LOGE("Object_CallMethod_Ref loadClassMethod failed");
        return UIContentErrorCode::INVALID_URL;
    }
    entryClass = static_cast<ani_class>(entryClassRef);

    ani_method entryMethod = nullptr;
    if (env_->Class_FindMethod(entryClass, "<ctor>", ":V", &entryMethod) != ANI_OK) {
        LOGE("Class_FindMethod ctor failed");
        return UIContentErrorCode::INVALID_URL;
    }

    ani_object entryObject = nullptr;
    if (env_->Object_New(entryClass, entryMethod, &entryObject) != ANI_OK) {
        LOGE("Object_New AbcRuntimeLinker failed");
        return UIContentErrorCode::INVALID_URL;
    }
    // end find app class

    ani_string aniUrl;
    env_->String_NewUTF8(appUrl.c_str(), appUrl.size(), &aniUrl);
    ani_string aniParams;
    env_->String_NewUTF8(appParams.c_str(), appParams.size(), &aniParams);

    ani_ref appLocal;
    if (env_->Class_CallStaticMethod_Ref(appClass, create, &appLocal, aniUrl, aniParams, false, entryObject) !=
        ANI_OK) {
        LOGE("createApplication returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    env_->GlobalReference_Create(appLocal, &app_);

    ani_method start;
    if (env_->Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start) !=
        ANI_OK) {
        LOGE("find start method returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_long result;
    if (env_->Object_CallMethod_Long(static_cast<ani_object>(app_), start, &result) != ANI_OK) {
        LOGE("call start method returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    // TODO: init event loop
    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    pipeline_->SetVsyncListener([env = env_, app = app_]() { RunArkoalaEventLoop(env, app); });

    return UIContentErrorCode::NO_ERRORS;
}

void ArktsFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    pipeline_ = DynamicCast<NG::PipelineContext>(context);
}

void* ArktsFrontend::GetShared(int32_t id)
{
    int32_t currentInstance = id;
    if (currentInstance >= MIN_SUBCONTAINER_ID && currentInstance < MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = SubwindowManager::GetInstance()->GetParentContainerId(currentInstance);
    }
    auto it = storageMap_.find(currentInstance);
    if (it == storageMap_.end()) {
        LOGW("LocalStorage with ID %{public}d not found!", currentInstance);
        return nullptr;
    }
    return it->second;
}

void ArktsFrontend::Destroy()
{
    CHECK_NULL_VOID(env_);
    env_->GlobalReference_Delete(app_);
}
} // namespace OHOS::Ace
