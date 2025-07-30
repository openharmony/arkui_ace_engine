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

#include "arkcompiler/runtime_core/static_core/plugins/ets/runtime/napi/ets_napi.h"
#include "interfaces/inner_api/ace/constants.h"

#include "base/subwindow/subwindow_manager.h"
#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "bridge/arkts_frontend/ani_context_module.h"
#include "bridge/arkts_frontend/entry/arkts_entry_loader.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
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
    "Larkui/ArkUIEntry/Application;",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;ZLstd/core/String;Larkui/UserView/UserView;Larkui/UserView/EntryPoint;"
    ":Larkui/ArkUIEntry/Application;",
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

std::string GetErrorProperty(ani_env* aniEnv, ani_error aniError, const char* property)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "called");
    std::string propertyValue;
    ani_status status = ANI_ERROR;
    ani_type errorType = nullptr;
    if ((status = aniEnv->Object_GetType(aniError, &errorType)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Object_GetType failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_method getterMethod = nullptr;
    if ((status = aniEnv->Class_FindGetter(static_cast<ani_class>(errorType), property, &getterMethod)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Class_FindGetter failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_ref aniRef = nullptr;
    if ((status = aniEnv->Object_CallMethod_Ref(aniError, getterMethod, &aniRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Object_CallMethod_Ref failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_string aniString = reinterpret_cast<ani_string>(aniRef);
    ani_size sz {};
    if ((status = aniEnv->String_GetUTF8Size(aniString, &sz)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "String_GetUTF8Size failed, status : %{public}d", status);
        return propertyValue;
    }
    propertyValue.resize(sz + 1);
    if ((status = aniEnv->String_GetUTF8SubString(
        aniString, 0, sz, propertyValue.data(), propertyValue.size(), &sz))!= ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "String_GetUTF8SubString failed, status : %{public}d", status);
        return propertyValue;
    }
    propertyValue.resize(sz);
    return propertyValue;
}

void RunArkoalaEventLoop(ani_env* env, ani_ref app)
{
    ani_boolean errorExists;
    env->ExistUnhandledError(&errorExists);
    ani_status status;
    ani_class appClass;
    if ((status = env->FindClass(KOALA_APP_INFO.className, &appClass)) != ANI_OK) {
        ani_error aniError;
        env->GetUnhandledError(&aniError);
        env->ResetError();
        std::string errorMsg = GetErrorProperty(env, aniError, "message");
        std::string errorName = GetErrorProperty(env, aniError, "name");
        std::string errorStack = GetErrorProperty(env, aniError, "stack");
        LOGE("[%{public}s] Cannot load main class %{public}s, status: %{public}d, \nerrorMsg: %{public}s, \nerrorName: "
             "%{public}s, \nerrorStack: %{public}s",
            __func__, KOALA_APP_INFO.className, status, errorMsg.c_str(), errorName.c_str(), errorStack.c_str());
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

ArktsFrontend::ArktsFrontend(void* runtime)
{
    auto* env = reinterpret_cast<ani_env*>(runtime);
    if (!env) {
        LOGW("ArktsFrontend AniEnv is invalid!");
        return;
    }
    type_ = FrontendType::ARK_TS;
    env->GetVM(&vm_);
}

ani_object LegacyLoadPage(ani_env* env)
{
    do {
        ani_status state;
        ani_ref linkerRef;
        if ((state = static_cast<ani_status>(ArktsAniUtils::GetNearestNonBootRuntimeLinker(env, linkerRef))) !=
            ANI_OK) {
            LOGE("Get getNearestNonBootRuntimeLinker failed, %{public}d", state);
            break;
        }

        std::string entryPath = "entry/src/main/ets/pages/Index/ComExampleTrivialApplication";
        ani_string entryClassStr;
        env->String_NewUTF8(entryPath.c_str(), entryPath.length(), &entryClassStr);
        ani_class entryClass = nullptr;
        ani_ref entryClassRef = nullptr;

        ani_class cls = nullptr;
        if ((state = env->FindClass("Lstd/core/RuntimeLinker;", &cls)) != ANI_OK) {
            LOGE("FindClass RuntimeLinker failed, %{public}d", state);
            break;
        }

        ani_method loadClassMethod;
        if ((state = env->Class_FindMethod(cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;",
                 &loadClassMethod)) != ANI_OK) {
            LOGE("Class_FindMethod loadClass failed, %{public}d", state);
            break;
        }

        ani_object isInit;
        if ((state = static_cast<ani_status>(ArktsAniUtils::CreateAniBoolean(env, false, isInit))) != ANI_OK) {
            LOGE("Create Boolean object failed, %{public}d", state);
            break;
        }

        if ((state = env->Object_CallMethod_Ref(
                 (ani_object)linkerRef, loadClassMethod, &entryClassRef, entryClassStr, isInit)) != ANI_OK) {
            LOGE("Object_CallMethod_Ref loadClassMethod failed");
            ani_error errorInfo;
            env->GetUnhandledError(&errorInfo);
            env->ResetError();
            break;
        }
        entryClass = static_cast<ani_class>(entryClassRef);

        ani_method entryMethod = nullptr;
        if (env->Class_FindMethod(entryClass, "<ctor>", ":V", &entryMethod) != ANI_OK) {
            LOGE("Class_FindMethod ctor failed");
            break;
        }

        ani_object entryObject = nullptr;
        if (env->Object_New(entryClass, entryMethod, &entryObject) != ANI_OK) {
            LOGE("Object_New AbcRuntimeLinker failed");
            break;
        }
        return entryObject;
    } while (false);
    return nullptr;
}

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    auto* env_ = ArktsAniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env_, UIContentErrorCode::INVALID_URL);

    ani_class appClass;
    EntryLoader entryLoader(url, env_);

    pageRouterManager_ = NG::PageRouterManagerFactory::CreateManager();

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

    ani_string aniUrl;
    env_->String_NewUTF8(url.c_str(), url.size(), &aniUrl);
    ani_string aniParams;
    env_->String_NewUTF8(params.c_str(), params.size(), &aniParams);

    ani_ref appLocal;
    ani_ref optionalEntry;
    env_->GetUndefined(&optionalEntry);
    auto entryPointObj = entryLoader.GetPageEntryObj();
    auto legacyEntryPointObj = LegacyLoadPage(env_);
    std::string moduleName = Container::Current()->GetModuleName();
    ani_string module;
    env_->String_NewUTF8(moduleName.c_str(), moduleName.size(), &module);
    if (env_->Class_CallStaticMethod_Ref(appClass, create, &appLocal, aniUrl, aniParams, false, module,
            legacyEntryPointObj ? legacyEntryPointObj : optionalEntry,
            entryPointObj ? entryPointObj : optionalEntry) != ANI_OK) {
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
    if (accessibilityManager_) {
        accessibilityManager_->SetPipelineContext(context);
        accessibilityManager_->InitializeCallback();
    }
}

bool ArktsFrontend::OnBackPressed()
{
    CHECK_NULL_RETURN(pageRouterManager_, false);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (pagePattern->OnBackPressed()) {
        return true;
    }
    return pageRouterManager_->Pop();
}

void ArktsFrontend::OnShow()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnShow();
}

void ArktsFrontend::OnHide()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnHide();
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
    CHECK_NULL_VOID(vm_);
    auto* env = ArktsAniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    env->GlobalReference_Delete(app_);
    app_ = nullptr;
}

ani_object ArktsFrontend::CallGetUIContextFunc()
{
    ani_object result = nullptr;
    ani_status status;

    auto* env = ArktsAniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, result);

    ani_class uiContextClass;
    if ((status = env->FindClass("L@ohos/arkui/UIContext/UIContext;", &uiContextClass)) != ANI_OK) {
        LOGE("FindClass UIContext failed, %{public}d", status);
        return result;
    }
    ani_method uiContextClassCtor;
    if ((status = env->Class_FindMethod(uiContextClass, "<ctor>", "I:V", &uiContextClassCtor)) != ANI_OK) {
        LOGE("Class_FindMethod UIContext ctor failed, %{public}d", status);
        return result;
    }
    ani_int instanceId = 100000;
    if ((status = env->Object_New(uiContextClass, uiContextClassCtor, &result, instanceId)) != ANI_OK) {
        LOGE("New UIContext object failed, %{public}d", status);
        return result;
    }
    return result;
}

void* ArktsFrontend::GetEnv()
{
    return ArktsAniUtils::GetAniEnv(vm_);
}

void* ArktsFrontend::preloadArkTSRuntime = nullptr;
void ArktsFrontend::PreloadAceModule(void* aniEnv)
{
    ArktsFrontend::preloadArkTSRuntime = aniEnv;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceArkTSModule(void* aniEnv)
{
    ArktsFrontend::PreloadAceModule(aniEnv);
}

void ArktsFrontend::SetAniContext(int32_t instanceId, ani_ref* context)
{
    std::shared_ptr<ani_ref> shared_ptr(context);
    Framework::AniContextModule::AddAniContext(instanceId, shared_ptr);
}
} // namespace OHOS::Ace
