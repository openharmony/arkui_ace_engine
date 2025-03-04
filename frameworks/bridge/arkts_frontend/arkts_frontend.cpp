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

#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace {
namespace {
constexpr char BUNDLE_INSTALL_PATH[] = "/data/storage/el1/bundle/";
constexpr char MERGE_ABC_PATH[] = "/ets/modules_static.abc";
} // namespace

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
    "L@koalaui/arkts-arkui/Application/Application;",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZL@koalaui/arkts-arkui/UserView/UserView;:L@koalaui/arkts-arkui/Application/Application;",
    "start",
    ":J",
    "enter",
    "II:Z",
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

// void RunArkoalaEventLoop(EtsEnv& env, ets_object app)
// {
//     ets_class appClass = env.FindClass(KOALA_APP_INFO.className);
//     if (!appClass) {
//         LOGE("Cannot load main class %s\n", KOALA_APP_INFO.className);
//         return;
//     }
//     ets_method enter = env.Getp_method(appClass, KOALA_APP_INFO.enterMethodName, nullptr /*appInfo->enterMethodSig */);
//     if (!enter) {
//         LOGE("Cannot find enter method %s", KOALA_APP_INFO.enterMethodName);
//         TryEmitError(env);
//         return;
//     }
//     auto terminate = env.CallBooleanMethod((ets_object)(app), (ets_method)(enter), (ets_int)0, (ets_int)0);
//     TryEmitError(env);
//     if (terminate) {
//         exit(0);
//     }
// }
} // namespace

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    ani_class appClass;
    if (env_->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
        LOGE("Cannot load main class %{public}s", KOALA_APP_INFO.className);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_static_method create;
    if (env_->Class_FindStaticMethod(appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig, &create) !=
        ANI_OK) {
        LOGE("Cannot find create method %{public}s", KOALA_APP_INFO.createMethodName);
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    // Find app class
    ani_class clsArray = nullptr;
    if (env_->FindClass("Lfixarray/GetPathArray;", &clsArray) != ANI_OK) {
        LOGE("FindClass failed");
        return UIContentErrorCode::INVALID_URL;
    };
    ani_static_method methodArray;
    if (env_->Class_FindStaticMethod(clsArray, "getPathArray", "Lstd/core/String;:[Lstd/core/String;", &methodArray) !=
        ANI_OK) {
        LOGE("Class_FindStaticMethod failed");
        return UIContentErrorCode::INVALID_URL;
    };
    const std::string moduleName = "entry";
    std::string modulePath = BUNDLE_INSTALL_PATH + moduleName + MERGE_ABC_PATH;
    ani_string abcPath;
    if (env_->String_NewUTF8(modulePath.c_str(), modulePath.length(), &abcPath) != ANI_OK) {
        LOGE("abilityPath String_NewUTF8 failed");
    };
    ani_ref refArray = nullptr;
    if (env_->Class_CallStaticMethod_Ref(clsArray, methodArray, &refArray, abcPath) != ANI_OK) {
        LOGE("Class_CallStaticMethod_Ref failed");
        return UIContentErrorCode::INVALID_URL;
    };
    ani_class cls = nullptr;
    if (env_->FindClass("Lstd/core/AbcRuntimeLinker;", &cls) != ANI_OK) {
        LOGE("FindClass AbcRuntimeLinker failed");
        return UIContentErrorCode::INVALID_URL;
    }
    ani_ref undefined_ref;
    if (env_->GetUndefined(&undefined_ref) != ANI_OK) {
        LOGE("GetUndefined failed");
        return UIContentErrorCode::INVALID_URL;
    }
    ani_method method = nullptr;
    if (env_->Class_FindMethod(cls, "<ctor>", "Lstd/core/RuntimeLinker;[Lstd/core/String;:V", &method) != ANI_OK) {
        LOGE("Class_FindMethod ctor failed");
        return UIContentErrorCode::INVALID_URL;
    }
    ani_object object = nullptr;
    if (env_->Object_New(cls, method, &object, undefined_ref, refArray) != ANI_OK) {
        LOGE("Object_New AbcRuntimeLinker failed");
        return UIContentErrorCode::INVALID_URL;
    }
    ani_method loadClassMethod = nullptr;
    if (env_->Class_FindMethod(cls, "loadClass", "Lstd/core/String;Z:Lstd/core/Class;", &loadClassMethod) != ANI_OK) {
        LOGE("Class_FindMethod loadClass failed");
        return UIContentErrorCode::INVALID_URL;
    }

    std::string entryPath = "entry/src/main/ets/pages/Index/ComExampleTrivialApplication";
    ani_string entryClassStr;
    env_->String_NewUTF8(entryPath.c_str(), entryPath.length(), &entryClassStr);

    ani_class entryClass = nullptr;
    ani_ref entryClassRef = nullptr;
    if (env_->Object_CallMethod_Ref(object, loadClassMethod, &entryClassRef, entryClassStr) != ANI_OK) {
        LOGE("Object_CallMethod_Ref loadClassMethod failed");
        return UIContentErrorCode::INVALID_URL;
    } else {
        entryClass = static_cast<ani_class>(entryClassRef);
    }

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

    std::string appUrl = "ComExampleTrivialApplication"; // TODO: use passed in url and params
    std::string appParams = "ArkTSLoaderParam";

    ani_string aniUrl;
    env_->String_NewUTF8(appUrl.c_str(), appUrl.size(), &aniUrl);
    ani_string aniParams;
    env_->String_NewUTF8(appParams.c_str(), appParams.size(), &aniParams);

    ani_ref app;
    if (env_->Class_CallStaticMethod_Ref(appClass, create, &app, aniUrl, aniParams, false, entryObject) != ANI_OK) {
        LOGE("createApplication returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_method start;
    if (env_->Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start) !=
        ANI_OK) {
        LOGE("find start method returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_long result;
    if (env_->Object_CallMethod_Long(static_cast<ani_object>(app), start, &result) != ANI_OK) {
        LOGE("call start method returned null");
        // TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }

    // TODO: init event loop
    // CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    // pipeline_->SetVsyncListener([env = env_, app]() { RunArkoalaEventLoop(*env, app); });

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
} // namespace OHOS::Ace
