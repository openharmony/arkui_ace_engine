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

#include "interfaces/inner_api/ace/constants.h"
#include "arkcompiler/runtime_core/static_core/plugins/ets/runtime/napi/ets_napi.h"

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
    "@koalaui/arkts-arkui/Application/Application",
    "createApplication",
    "Lstd/core/String;Lstd/core/String;Z:L@koalaui/arkts-arkui/Application/Application;",
    "start",
    ":J",
    "enter",
    "II:Z",
    "emitEvent",
    "IIII:V",
};

void TryEmitError(EtsEnv& env)
{
    if (env.ErrorCheck()) {
        env.ErrorDescribe();
        env.ErrorClear();
    }
}

void RunArkoalaEventLoop(EtsEnv& env, ets_object app)
{
    ets_class appClass = env.FindClass(KOALA_APP_INFO.className);
    if (!appClass) {
        LOGE("Cannot load main class %s\n", KOALA_APP_INFO.className);
        return;
    }
    ets_method enter = env.Getp_method(appClass, KOALA_APP_INFO.enterMethodName, nullptr /*appInfo->enterMethodSig */);
    if (!enter) {
        LOGE("Cannot find enter method %s", KOALA_APP_INFO.enterMethodName);
        TryEmitError(env);
        return;
    }
    auto terminate = env.CallBooleanMethod((ets_object)(app), (ets_method)(enter), (ets_int)0, (ets_int)0);
    TryEmitError(env);
    if (terminate) {
        exit(0);
    }
}
} // namespace

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    ets_class appClass = env_->FindClass(KOALA_APP_INFO.className);
    if (!appClass) {
        LOGE("Cannot load main class %s\n", KOALA_APP_INFO.className);
        return UIContentErrorCode::INVALID_URL;
    }
    ets_method create = env_->GetStaticp_method(appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig);
    if (!create) {
        LOGE("Cannot find create method %s\n", KOALA_APP_INFO.createMethodName);
        TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }
    std::string appUrl = "ComExampleTrivialApplication"; // TODO: use passed in url and params
    std::string appParams = "ArkTSLoaderParam";
    auto* app = env_->NewGlobalRef(env_->CallStaticObjectMethod(
        appClass, create, env_->NewStringUTF(appUrl.c_str()), env_->NewStringUTF(appParams.c_str()), false));
    if (!app) {
        LOGE("createApplication returned null");
        TryEmitError(*env_);
        return UIContentErrorCode::INVALID_URL;
    }
    auto* start = env_->Getp_method(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig);
    // TODO: pass app entry point!
    env_->CallLongMethod((ets_object)(app), start);

    // // init event loop
    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    pipeline_->SetVsyncListener([env = env_, app]() { RunArkoalaEventLoop(*env, app); });

    return UIContentErrorCode::NO_ERRORS;
}

void ArktsFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    pipeline_ = DynamicCast<NG::PipelineContext>(context);
}
} // namespace OHOS::Ace
