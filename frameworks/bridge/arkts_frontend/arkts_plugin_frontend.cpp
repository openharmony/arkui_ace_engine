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
#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "bridge/arkts_frontend/entry/arkts_entry_loader.h"
#include "core/pipeline/pipeline_context.h"

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

void RunArkoalaEventLoop(ani_env* env, ani_ref app)
{
    ani_class appClass;
    ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return);

    ani_method enter = nullptr;
    ANI_CALL(env, Class_FindMethod(
        appClass, KOALA_APP_INFO.enterMethodName, KOALA_APP_INFO.enterMethodSig, &enter), return);

    ani_int arg0 = 0;
    ani_int arg1 = 0;
    ani_boolean result;
    ANI_CALL(env, Object_CallMethod_Boolean(
        static_cast<ani_object>(app), enter, &result, arg0, arg1, nullptr), return);
}
} // namespace

UIContentErrorCode ArktsPluginFrontend::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    return UIContentErrorCode::NO_ERRORS;
}

UIContentErrorCode ArktsPluginFrontend::RunPage(const std::string& url, const std::string& params)
{
    std::vector<uint8_t> abcContent;
    if (!Framework::GetAssetContentImpl(assetManager_, "ets/modules_static.abc", abcContent)) {
        LOGE("GetAssetContent fail: ets/modules_static.abc");
        return UIContentErrorCode::INVALID_URL;
    }

    ani_class appClass{};
    ANI_CALL(env_, FindClass(KOALA_APP_INFO.className, &appClass), return UIContentErrorCode::INVALID_URL);

    ani_static_method create;
    ANI_CALL(env_, Class_FindStaticMethod(appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig,
        &create), return UIContentErrorCode::INVALID_URL);

    std::string appUrl = url.substr(0, url.rfind(".js"));

    ani_string aniUrl{};
    env_->String_NewUTF8(appUrl.c_str(), appUrl.size(), &aniUrl);

    ani_string aniParams{};
    env_->String_NewUTF8(params.c_str(), params.size(), &aniParams);

    NG::EntryLoader entryLoader {env_, abcContent};
    if (!entryLoader) {
        return UIContentErrorCode::INVALID_URL;
    }

    std::string entryPath = pluginModuleName_ + "/src/main/ets/" + appUrl + "/__EntryWrapper";
    ani_object entryPointObj = entryLoader.GetPageEntryObj(entryPath);

    std::string legacyEntryPath = pluginModuleName_ + "/src/main/ets/" + appUrl + "/ComExampleTrivialApplication";
    ani_object legacyEntryPointObj = entryPointObj ? nullptr : entryLoader.GetPageEntryObj(legacyEntryPath);

    ani_string module{};
    env_->String_NewUTF8(pluginModuleName_.c_str(), pluginModuleName_.size(), &module);

    ani_ref appLocal{};
    ANI_CALL(env_, Class_CallStaticMethod_Ref(appClass, create, &appLocal, aniUrl, aniParams, false, module,
        legacyEntryPointObj, entryPointObj), return UIContentErrorCode::INVALID_URL);

    env_->GlobalReference_Create(appLocal, &app_);

    ani_method start;
    ANI_CALL(env_, Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start),
        return UIContentErrorCode::INVALID_URL);

    ani_long result;
    ANI_CALL(env_, Object_CallMethod_Long(static_cast<ani_object>(app_), start, &result),
        return UIContentErrorCode::INVALID_URL);

    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    pipeline_->SetVsyncListener([env = env_, app = app_]() { RunArkoalaEventLoop(env, app); });

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
    CHECK_NULL_VOID(env_);
    env_->GlobalReference_Delete(app_);
}

} // namespace OHOS::Ace
