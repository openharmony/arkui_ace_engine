/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller_async.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "base/memory/referenced.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/container.h"

namespace OHOS::Ace::Framework {
namespace {

const std::vector<SeekMode> SEEK_MODE = { SeekMode::SEEK_PREVIOUS_SYNC, SeekMode::SEEK_NEXT_SYNC,
    SeekMode::SEEK_CLOSEST_SYNC, SeekMode::SEEK_CLOSEST };

constexpr int32_t VIDEO_ASYNC_ERROR_CODE = 17000100;

void ReturnPromise(const JSCallbackInfo& info, napi_value result)
{
    CHECK_NULL_VOID(result);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    if (!jsPromise->IsObject()) {
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}

napi_value CreateErrorValue(napi_env env, const std::string& reason)
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(VIDEO_ASYNC_ERROR_CODE);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, reason.c_str(), reason.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

} // namespace

void JSVideoControllerAsync::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideoControllerAsync>::Declare("VideoControllerAsync");
    JSClass<JSVideoControllerAsync>::CustomMethod("start", &JSVideoControllerAsync::StartAsync);
    JSClass<JSVideoControllerAsync>::CustomMethod("pause", &JSVideoControllerAsync::PauseAsync);
    JSClass<JSVideoControllerAsync>::CustomMethod("stop", &JSVideoControllerAsync::StopAsync);
    JSClass<JSVideoControllerAsync>::CustomMethod("setCurrentTime", &JSVideoControllerAsync::SetCurrentTime);
    JSClass<JSVideoControllerAsync>::CustomMethod("requestFullscreen", &JSVideoControllerAsync::RequestFullscreen);
    JSClass<JSVideoControllerAsync>::CustomMethod("exitFullscreen", &JSVideoControllerAsync::ExitFullscreen);
    JSClass<JSVideoControllerAsync>::CustomMethod("reset", &JSVideoControllerAsync::ResetAsync);
    JSClass<JSVideoControllerAsync>::Bind(globalObj, JSVideoControllerAsync::Constructor, JSVideoControllerAsync::Destructor);
}

void JSVideoControllerAsync::Constructor(const JSCallbackInfo& args)
{
    auto videoControllerAsync = Referenced::MakeRefPtr<JSVideoControllerAsync>();
    videoControllerAsync->IncRefCount();
    WeakPtr<NG::VideoStateMachinePattern> emptyPattern;
    RefPtr<VideoControllerAsync> controller = AceType::MakeRefPtr<VideoControllerAsync>(emptyPattern);
    videoControllerAsync->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(videoControllerAsync));
}

void JSVideoControllerAsync::Destructor(JSVideoControllerAsync* videoControllerAsync)
{
    if (videoControllerAsync) {
        const auto& controller = videoControllerAsync->GetController();
        videoControllerAsync->DecRefCount();
        if (controller) {
            controller->ClearPattern();
        }
    }
}

void JSVideoControllerAsync::StartAsync(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);

    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (videoControllerAsync_) {
        auto callback = [env, deferred, taskExecutor](bool success, const std::string& reason) {
            taskExecutor->PostTask(
                [env, deferred, success, reason]() {
                    napi_handle_scope scope = nullptr;
                    auto status = napi_open_handle_scope(env, &scope);
                    if (status != napi_ok) {
                        return;
                    }
                    napi_value result = nullptr;
                    if (success) {
                        napi_get_null(env, &result);
                        napi_resolve_deferred(env, deferred, result);
                    } else {
                        napi_value error = CreateErrorValue(env, reason);
                        napi_reject_deferred(env, deferred, error);
                    }
                    napi_close_handle_scope(env, scope);
                },
                TaskExecutor::TaskType::JS, "ArkUIVideoStartResolve");
        };
        videoControllerAsync_->Start(std::move(callback));
    } else {
        taskExecutor->PostTask(
            [env, deferred]() {
                napi_handle_scope scope = nullptr;
                auto status = napi_open_handle_scope(env, &scope);
                if (status == napi_ok) {
                    napi_value result = nullptr;
                    napi_get_null(env, &result);
                    napi_resolve_deferred(env, deferred, result);
                    napi_close_handle_scope(env, scope);
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIVideoStartResolve");
    }

    ReturnPromise(args, promise);
}

void JSVideoControllerAsync::PauseAsync(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);

    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (videoControllerAsync_) {
        auto callback = [env, deferred, taskExecutor](bool success, const std::string& reason) {
            taskExecutor->PostTask(
                [env, deferred, success, reason]() {
                    napi_handle_scope scope = nullptr;
                    auto status = napi_open_handle_scope(env, &scope);
                    if (status != napi_ok) {
                        return;
                    }
                    napi_value result = nullptr;
                    if (success) {
                        napi_get_null(env, &result);
                        napi_resolve_deferred(env, deferred, result);
                    } else {
                        napi_value error = CreateErrorValue(env, reason);
                        napi_reject_deferred(env, deferred, error);
                    }
                    napi_close_handle_scope(env, scope);
                },
                TaskExecutor::TaskType::JS, "ArkUIVideoPauseResolve");
        };
        videoControllerAsync_->Pause(std::move(callback));
    } else {
        taskExecutor->PostTask(
            [env, deferred]() {
                napi_handle_scope scope = nullptr;
                auto status = napi_open_handle_scope(env, &scope);
                if (status == napi_ok) {
                    napi_value result = nullptr;
                    napi_get_null(env, &result);
                    napi_resolve_deferred(env, deferred, result);
                    napi_close_handle_scope(env, scope);
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIVideoPauseResolve");
    }

    ReturnPromise(args, promise);
}

void JSVideoControllerAsync::StopAsync(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);

    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (videoControllerAsync_) {
        auto callback = [env, deferred, taskExecutor](bool success, const std::string& reason) {
            taskExecutor->PostTask(
                [env, deferred, success, reason]() {
                    napi_handle_scope scope = nullptr;
                    auto status = napi_open_handle_scope(env, &scope);
                    if (status != napi_ok) {
                        return;
                    }
                    napi_value result = nullptr;
                    if (success) {
                        napi_get_null(env, &result);
                        napi_resolve_deferred(env, deferred, result);
                    } else {
                        napi_value error = CreateErrorValue(env, reason);
                        napi_reject_deferred(env, deferred, error);
                    }
                    napi_close_handle_scope(env, scope);
                },
                TaskExecutor::TaskType::JS, "ArkUIVideoStopResolve");
        };
        videoControllerAsync_->Stop(std::move(callback));
    } else {
        taskExecutor->PostTask(
            [env, deferred]() {
                napi_handle_scope scope = nullptr;
                auto status = napi_open_handle_scope(env, &scope);
                if (status == napi_ok) {
                    napi_value result = nullptr;
                    napi_get_null(env, &result);
                    napi_resolve_deferred(env, deferred, result);
                    napi_close_handle_scope(env, scope);
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIVideoStopResolve");
    }

    ReturnPromise(args, promise);
}

void JSVideoControllerAsync::ResetAsync(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto taskExecutor = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(taskExecutor);

    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (videoControllerAsync_) {
        auto callback = [env, deferred, taskExecutor](bool success, const std::string& reason) {
            taskExecutor->PostTask(
                [env, deferred, success, reason]() {
                    napi_handle_scope scope = nullptr;
                    auto status = napi_open_handle_scope(env, &scope);
                    if (status != napi_ok) {
                        return;
                    }
                    napi_value result = nullptr;
                    if (success) {
                        napi_get_null(env, &result);
                        napi_resolve_deferred(env, deferred, result);
                    } else {
                        napi_value error = CreateErrorValue(env, reason);
                        napi_reject_deferred(env, deferred, error);
                    }
                    napi_close_handle_scope(env, scope);
                },
                TaskExecutor::TaskType::JS, "ArkUIVideoResetResolve");
        };
        videoControllerAsync_->Reset(std::move(callback));
    } else {
        taskExecutor->PostTask(
            [env, deferred]() {
                napi_handle_scope scope = nullptr;
                auto status = napi_open_handle_scope(env, &scope);
                if (status == napi_ok) {
                    napi_value result = nullptr;
                    napi_get_null(env, &result);
                    napi_resolve_deferred(env, deferred, result);
                    napi_close_handle_scope(env, scope);
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIVideoResetResolve");
    }

    ReturnPromise(args, promise);
}

void JSVideoControllerAsync::SetCurrentTime(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    float value = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], value)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoControllerAsync set current time with invalid params");
        return;
    }

    SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC;
    if (args.Length() > 1 && args[1]->IsNumber() && args[1]->ToNumber<uint32_t>() < SEEK_MODE.size()) {
        seekMode = SEEK_MODE[args[1]->ToNumber<int32_t>()];
    }

    if (videoControllerAsync_) {
        videoControllerAsync_->SeekTo(value, seekMode);
    }
}

void JSVideoControllerAsync::RequestFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool landscape = true;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], landscape)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoControllerAsync request full screen with invalid params");
        return;
    }

    if (videoControllerAsync_) {
        videoControllerAsync_->RequestFullscreen(landscape);
    }
}

void JSVideoControllerAsync::ExitFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (videoControllerAsync_) {
        videoControllerAsync_->ExitFullscreen();
    }
}

} // namespace OHOS::Ace::Framework