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
#include "bridge/arkts_frontend/arkts_dynamic_frontend.h"

#include <ani.h>

#include "interfaces/inner_api/ace/constants.h"
#include "bridge/arkts_frontend/entry/arkts_entry_loader.h"
#include "core/pipeline/pipeline_context.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace {
namespace {
const std::string DC_ETS = "/ets/";
const std::string ENTRY_PREFIX = "/src/main/ets/";
const std::string ENTRY_SUFFIX = "/__EntryWrapper";
const std::string USERVIEW_SUFFIX = "/ComExampleTrivialApplication";
constexpr char BUNDLE_INSTALL_PATH[] = "/data/storage/el1/bundle/";
constexpr char MERGE_ABC_PATH[] = "/ets/modules_static.abc";
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
    const char* checkCallbackMethodName;
    const char* checkCallbackEventMethodSig;
};
/* copied from arkcompiler_ets_frontend vmloader.cc*/
const AppInfo KOALA_APP_INFO = {
    "arkui.ArkUIEntry.Application",
    "createApplication",
    "C{std.core.String}C{std.core.String}zC{std.core.String}C{arkui.UserView.UserView}"
    "C{arkui.component.customComponent.EntryPoint}:C{arkui.ArkUIEntry.Application}",
    "start",
    "z:l",
    "enter",
    "iil:z",
    "emitEvent",
    "iiii:",
    "checkCallbacks",
    ":",
};

std::string GetErrorProperty(ani_env* aniEnv, ani_error aniError, const char* property)
{
    TAG_LOGD(AceLogTag::ACE_DYNAMIC_COMPONENT, "called");
    std::string propertyValue;
    ani_status status = ANI_ERROR;
    ani_type errorType = nullptr;
    if ((status = aniEnv->Object_GetType(aniError, &errorType)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "Object_GetType failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_method getterMethod = nullptr;
    if ((status = aniEnv->Class_FindGetter(static_cast<ani_class>(errorType), property, &getterMethod)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "Class_FindGetter failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_ref aniRef = nullptr;
    if ((status = aniEnv->Object_CallMethod_Ref(aniError, getterMethod, &aniRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "Object_CallMethod_Ref failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_string aniString = reinterpret_cast<ani_string>(aniRef);
    ani_size sz {};
    if ((status = aniEnv->String_GetUTF8Size(aniString, &sz)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "String_GetUTF8Size failed, status : %{public}d", status);
        return propertyValue;
    }
    propertyValue.resize(sz + 1);
    if ((status = aniEnv->String_GetUTF8SubString(
        aniString, 0, sz, propertyValue.data(), propertyValue.size(), &sz))!= ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "String_GetUTF8SubString failed, status : %{public}d", status);
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
        return;
    }

    ani_int arg0 = 0;
    ani_int arg1 = 0;
    ani_boolean result;
    if (env->Object_CallMethod_Boolean(static_cast<ani_object>(app), enter, &result, arg0, arg1, nullptr) != ANI_OK) {
        LOGE("[%{public}s] Call enter method failed", __func__);
        return;
    }
}

// fire all arkoala callbacks at the tail of vsync (PipelineContext::FlushVsync)
void FireAllArkoalaAsyncEvents(ani_env* env, ani_ref app)
{
    ani_class appClass;
    ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return);

    ani_method checkCallbacks = nullptr;
    ANI_CALL(env,
        Class_FindMethod(appClass, KOALA_APP_INFO.checkCallbackMethodName, KOALA_APP_INFO.checkCallbackEventMethodSig,
            &checkCallbacks),
        return);

    ANI_CALL(env, Object_CallMethod_Void(static_cast<ani_object>(app), checkCallbacks), return);
}

void GetUrlByDcEntryPoint(
    const std::string& bundleName, const std::string& moduleName,
    const std::string& entryPoint, std::string& url)
{
    std::string prefix;
    prefix.append(bundleName).append("/").append(moduleName).append(DC_ETS);
    if (prefix.size() > entryPoint.size()) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT,
            "prefix: %{public}s dayu entryPoint: %{public}s", prefix.c_str(), entryPoint.c_str());
        return;
    }
    url = entryPoint.substr(prefix.size());
}
} // namespace

ArktsDynamicFrontend::ArktsDynamicFrontend(void* runtime): ArktsFrontend(runtime)
{}

void ArktsDynamicFrontend::Destroy()
{
    if (globalLinkObj_) {
        auto* env = Ani::AniUtils::GetAniEnv(vm_);
        if (env) {
            env->GlobalReference_Delete(reinterpret_cast<ani_object>(globalLinkObj_));
        }
    }
    ArktsFrontend::Destroy();
}

UIContentErrorCode ArktsDynamicFrontend::RunDynamicPage(
    const std::string& content, const std::string& params, const std::string& entryPoint)
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "RunDynamicPage start content: %{public}s, params: %{public}s,"
        " entryPoint: %{public}s", content.c_str(), params.c_str(), entryPoint.c_str());
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, UIContentErrorCode::INVALID_URL);
    if (pageRouterManager_ == nullptr) {
        pageRouterManager_ = NG::PageRouterManagerFactory::CreateManager();
    }

    std::vector<uint8_t> abcContent;
    if (!Framework::GetAssetContentImpl(assetManager_, "ets/modules_static.abc", abcContent)) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "GetAssetContent fail: ets/modules_static.abc");
        return UIContentErrorCode::INVALID_URL;
    }

    ani_class appClass{};
    ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return UIContentErrorCode::INVALID_URL);

    ani_static_method create;
    ANI_CALL(env, Class_FindStaticMethod(appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig,
        &create), return UIContentErrorCode::INVALID_URL);

    std::string appUrlStr;
    GetUrlByDcEntryPoint(bundleName_, moduleName_, entryPoint, appUrlStr);

    ani_string aniUrl{};
    env->String_NewUTF8(appUrlStr.c_str(), appUrlStr.size(), &aniUrl);

    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "RunDynamicPage bundleName: %{public}s, moduleName: %{public}s,"
        " appUrl: %{public}s", bundleName_.c_str(), moduleName_.c_str(), appUrlStr.c_str());

    ani_string aniParams{};
    env->String_NewUTF8(params.c_str(), params.size(), &aniParams);

    std::string moduleAbcPath = BUNDLE_INSTALL_PATH + moduleName_ + MERGE_ABC_PATH;
    NG::EntryLoader entryLoader {env, moduleAbcPath};

    std::string entryPath = moduleName_ + ENTRY_PREFIX + appUrlStr + ENTRY_SUFFIX;
    ani_object entryPointObj = entryLoader.GetPageEntryObj(entryPath);

    std::string legacyEntryPath = moduleName_ + ENTRY_PREFIX + appUrlStr + USERVIEW_SUFFIX;
    ani_object legacyEntryPointObj = entryLoader.GetPageEntryObj(legacyEntryPath);

    ani_string module{};
    env->String_NewUTF8(moduleName_.c_str(), moduleName_.size(), &module);
    ani_ref optionalEntry;
    env->GetUndefined(&optionalEntry);

    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "RunDynamicPage entryPath: %{public}s, legacyEntryPath: %{public}s,",
        entryPath.c_str(), legacyEntryPath.c_str());

    ani_ref appLocal{};
    ANI_CALL(env, Class_CallStaticMethod_Ref(
        appClass, create, &appLocal, aniUrl, aniParams, false, module,
        legacyEntryPointObj ? legacyEntryPointObj : optionalEntry,
        entryPointObj ? entryPointObj : optionalEntry), return UIContentErrorCode::INVALID_URL);

    env->GlobalReference_Create(appLocal, &app_);
    auto linkObj = entryLoader.GetLinkObj();
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(linkObj), &globalLinkObj_);

    ani_method start;
    ANI_CALL(env, Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start),
        return UIContentErrorCode::INVALID_URL);

    ani_long result;
    ANI_CALL(env, Object_CallMethod_Long(static_cast<ani_object>(app_), start, &result, ANI_FALSE),
        return UIContentErrorCode::INVALID_URL);

    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    auto inId = pipeline_->GetInstanceId();
    pipeline_->SetVsyncListener([vm = vm_, app = app_, inId]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        if (env == nullptr) {
            TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "RunArkoalaEventLoop GetAniEnv failed");
            return;
        }

        RunArkoalaEventLoop(env, app);
    });
    // register one hook method to pipeline, which will be called at the tail of vsync
    pipeline_->SetAsyncEventsHookListener([vm = vm_, app = app_]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        if (env == nullptr) {
            TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "FireAllArkoalaAsyncEvents GetAniEnv failed");
            return;
        }

        FireAllArkoalaAsyncEvents(env, app);
    });

    return UIContentErrorCode::NO_ERRORS;
}

extern "C" ACE_FORCE_EXPORT Frontend* OHOS_ACE_CreatArkTsDynamicFrontend(void* runtime) {
    if (!runtime) {
        LOGE("runtime is nullptr.");
        return nullptr;
    }
    return static_cast<Frontend*>(new ArktsDynamicFrontend(runtime));
}
} // namespace OHOS::Ace
