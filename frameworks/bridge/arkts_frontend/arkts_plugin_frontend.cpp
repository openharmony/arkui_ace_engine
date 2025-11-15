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
#include "bridge/arkts_frontend/arkts_plugin_frontend.h"

#include <ani.h>

#include "interfaces/inner_api/ace/constants.h"
#include "bridge/arkts_frontend/entry/arkts_entry_loader.h"
#include "core/pipeline/pipeline_context.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace {
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

class KoalaApp {
public:
    KoalaApp(const KoalaApp&) = delete;
    KoalaApp& operator=(const KoalaApp&) = delete;
    
    static KoalaApp& GetInstance()
    {
        static KoalaApp instance;
        return instance;
    }
    
    ani_class GetKoalaAppCls(ani_env* env)
    {
        std::call_once(clsOnceFlag_, [this, env]() {
            ani_class appClass;
            ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return);
            if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(appClass), &globalClsRef)) {
                LOGE("ArktsPluginFrontend Create Global reference failed!");
            }
        });
        if (globalClsRef == nullptr) {
            LOGE("ArktsPluginFrontend get Global reference failed!");
            return nullptr;
        }
        auto cls = static_cast<ani_class>(globalClsRef);
        return cls;
    }
    ani_method GetEnterMethod(ani_env* env)
    {
        std::call_once(enterOnceFlag_, [this, env]() {
            auto cls = GetKoalaAppCls(env);
            if (cls == nullptr) {
                LOGE("ArktsPluginFrontend get Global reference failed!");
                return;
            }
            ANI_CALL(env, Class_FindMethod(cls, KOALA_APP_INFO.enterMethodName,
                KOALA_APP_INFO.enterMethodSig, &enter), return);
        });
        if (enter == nullptr) {
            LOGE("ArktsPluginFrontend get Global enter method failed!");
            return nullptr;
        }
        return enter;
    }
    ani_method GetCheckCallbacksMethod(ani_env* env)
    {
        std::call_once(checkCallbacksOnceFlag_, [this, env]() {
            auto cls = GetKoalaAppCls(env);
            if (cls == nullptr) {
                LOGE("ArktsPluginFrontend get Global reference failed!");
                return;
            }
            ANI_CALL(env, Class_FindMethod(cls, KOALA_APP_INFO.checkCallbackMethodName,
                KOALA_APP_INFO.checkCallbackEventMethodSig, &checkCallbacks), return);
        });
        if (checkCallbacks == nullptr) {
            LOGE("ArktsPluginFrontend get Global checkCallbacks method failed!");
            return nullptr;
        }
        return checkCallbacks;
    }
private:
    KoalaApp() = default;
    ~KoalaApp() = default;
    ani_ref globalClsRef {};
    ani_method enter {};
    ani_method checkCallbacks {};
    std::once_flag clsOnceFlag_;
    std::once_flag enterOnceFlag_;
    std::once_flag checkCallbacksOnceFlag_;
};

void RunArkoalaEventLoop(ani_env* env, ani_ref app)
{
    ani_method enter = KoalaApp::GetInstance().GetEnterMethod(env);
    CHECK_NULL_VOID(enter);
    ani_int arg0 = 0;
    ani_int arg1 = 0;
    ani_boolean result;
    ANI_CALL(env, Object_CallMethod_Boolean(
        static_cast<ani_object>(app), enter, &result, arg0, arg1, nullptr), return);
}

// fire all arkoala callbacks at the tail of vsync (PipelineContext::FlushVsync)
void FireAllArkoalaAsyncEvents(ani_env* env, ani_ref app)
{
    ani_method checkCallbacks = KoalaApp::GetInstance().GetCheckCallbacksMethod(env);
    CHECK_NULL_VOID(checkCallbacks);
    ANI_CALL(env, Object_CallMethod_Void(static_cast<ani_object>(app), checkCallbacks), return);
}
} // namespace

ArktsPluginFrontend::ArktsPluginFrontend(void* runtime)
{
    auto* env = reinterpret_cast<ani_env*>(runtime);
    if (!env) {
        LOGW("ArktsPluginFrontend AniEnv is invalid!");
        return;
    }
    type_ = FrontendType::ARK_TS;
    env->GetVM(&vm_);
}

UIContentErrorCode ArktsPluginFrontend::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    return UIContentErrorCode::NO_ERRORS;
}

UIContentErrorCode ArktsPluginFrontend::RunPage(const std::string& url, const std::string& params)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, UIContentErrorCode::INVALID_URL);

    std::vector<uint8_t> abcContent;
    if (!Framework::GetAssetContentImpl(assetManager_, "ets/modules_static.abc", abcContent)) {
        LOGE("GetAssetContent fail: ets/modules_static.abc");
        return UIContentErrorCode::INVALID_URL;
    }

    ani_class appClass{};
    ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return UIContentErrorCode::INVALID_URL);

    ani_static_method create;
    ANI_CALL(env, Class_FindStaticMethod(appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig,
        &create), return UIContentErrorCode::INVALID_URL);

    auto endsWith = [](const std::string& str, const char* suffix) -> bool {
        auto len = strlen(suffix);
        return str.length() >= len && strcmp(&str[str.length() - len], suffix) == 0;
    };

    std::string appUrl;
    if (endsWith(url, ".js") || endsWith(url, ".ts")) {
        appUrl = url.substr(0, url.length() - strlen(".js"));
    } else if (endsWith(url, ".ets")) {
        appUrl = url.substr(0, url.length() - strlen(".ets"));
    } else {
        appUrl = url;
    }

    ani_string aniUrl{};
    env->String_NewUTF8(appUrl.c_str(), appUrl.size(), &aniUrl);

    ani_string aniParams{};
    env->String_NewUTF8(params.c_str(), params.size(), &aniParams);

    NG::EntryLoader entryLoader {env, abcContent};
    if (!entryLoader) {
        return UIContentErrorCode::INVALID_URL;
    }

    std::string entryPath = pluginModuleName_ + "/src/main/ets/" + appUrl + "/__EntryWrapper";
    ani_object entryPointObj = entryLoader.GetPageEntryObj(entryPath);

    std::string legacyEntryPath = pluginModuleName_ + "/src/main/ets/" + appUrl + "/ComExampleTrivialApplication";
    ani_object legacyEntryPointObj = entryPointObj ? nullptr : entryLoader.GetPageEntryObj(legacyEntryPath);

    ani_string module{};
    env->String_NewUTF8(pluginModuleName_.c_str(), pluginModuleName_.size(), &module);

    ani_ref appLocal{};
    ANI_CALL(env, Class_CallStaticMethod_Ref(appClass, create, &appLocal, aniUrl, aniParams, false, module,
        legacyEntryPointObj, entryPointObj), return UIContentErrorCode::INVALID_URL);

    env->GlobalReference_Create(appLocal, &app_);

    ani_method start;
    ANI_CALL(env, Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start),
        return UIContentErrorCode::INVALID_URL);

    ani_long result;
    ANI_CALL(env, Object_CallMethod_Long(static_cast<ani_object>(app_), start, &result, ANI_TRUE),
        return UIContentErrorCode::INVALID_URL);

    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    pipeline_->SetVsyncListener([vm = vm_, app = app_]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        RunArkoalaEventLoop(env, app);
    });
    // register one hook method to pipeline, which will be called at the tail of vsync
    pipeline_->SetAsyncEventsHookListener([vm = vm_, app = app_]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        FireAllArkoalaAsyncEvents(env, app);
    });

    return UIContentErrorCode::NO_ERRORS;
}

void ArktsPluginFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    pipeline_ = DynamicCast<PipelineContext>(context);
    if (accessibilityManager_) {
        accessibilityManager_->SetPipelineContext(context);
        accessibilityManager_->InitializeCallback();
    }
}

void ArktsPluginFrontend::Destroy()
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    env->GlobalReference_Delete(app_);
    app_ = nullptr;
}

extern "C" ACE_FORCE_EXPORT PluginFrontend* OHOS_ACE_CreateArktsPluginFrontend(void* runtime) {
    if (!runtime) {
        LOGE("runtime is nullptr.");
        return nullptr;
    }
    return new ArktsPluginFrontend(runtime);
}
} // namespace OHOS::Ace
