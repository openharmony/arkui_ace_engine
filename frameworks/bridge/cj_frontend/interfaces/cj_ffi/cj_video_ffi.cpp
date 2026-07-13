/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "cj_video_ffi.h"

#include <cstdlib>

#include "core/common/dynamic_module_helper.h"

#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
OHOS::Ace::VideoModel* GetVideoModel()
{
    static auto* model = []() {
        auto* module = OHOS::Ace::DynamicModuleHelper::GetInstance().GetDynamicModule("Video");
        if (module == nullptr) {
            LOGF_ABORT("Cannot get Video dynamicModule");
        }
        auto* dynamicModel = reinterpret_cast<OHOS::Ace::VideoModel*>(module->GetModel());
        if (dynamicModel == nullptr) {
            LOGF_ABORT("Cannot get VideoModel from dynamicModule");
        }
        return dynamicModel;
    }();
    return model;
}
} // namespace

namespace OHOS::Ace::Framework {
NativeVideoController::NativeVideoController() : FFIData()
{
    RefPtr<VideoControllerV2> controller = AceType::MakeRefPtr<VideoControllerV2>();
    SetController(controller);
    LOGI("NativeVideoController constructed: %{public}" PRId64, GetID());
}

void NativeVideoController::Start()
{
    if (videoController_) {
        videoController_->Start();
    }
}

void NativeVideoController::Pause()
{
    if (videoController_) {
        videoController_->Pause();
    }
}

void NativeVideoController::Stop()
{
    if (videoController_) {
        videoController_->Stop();
    }
}

void NativeVideoController::Reset()
{
    if (videoController_) {
        videoController_->Reset();
    }
}
void NativeVideoController::SetCurrentTime(int32_t time, int32_t seekMode)
{
    double value = (double)time;
    SeekMode mode = static_cast<SeekMode>(seekMode);
    if (videoController_) {
        videoController_->SeekTo(value, mode);
    }
}

void NativeVideoController::RequestFullscreen(bool fullScreen)
{
    if (videoController_) {
        videoController_->RequestFullscreen(fullScreen);
    }
}

void NativeVideoController::ExitFullscreen()
{
    if (videoController_) {
        videoController_->ExitFullscreen(false);
    }
}
} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkVideoCreate(const char* src, double progressRate, const char* preview, int64_t controllerId)
{
    auto controller = FFIData::GetData<NativeVideoController>(controllerId);
    if (controller) {
        GetVideoModel()->Create(controller->GetController());
        GetVideoModel()->SetSrc(src, "", "");
        GetVideoModel()->SetProgressRate(progressRate);
        GetVideoModel()->SetPosterSourceInfo(preview, "", "");
    } else {
        LOGE("video controller id is invalid");
    }
}

void FfiOHOSAceFrameworkVideoMuted(bool muted)
{
    GetVideoModel()->SetMuted(muted);
}

void FfiOHOSAceFrameworkVideoAutoPlay(bool autoPlay)
{
    GetVideoModel()->SetAutoPlay(autoPlay);
}

void FfiOHOSAceFrameworkVideoControls(bool controls)
{
    GetVideoModel()->SetControls(controls);
}

void FfiOHOSAceFrameworkVideoObjectFit(int32_t objectFit)
{
    GetVideoModel()->SetObjectFit(static_cast<ImageFit>(objectFit));
}

void FfiOHOSAceFrameworkVideoLoop(bool loop)
{
    GetVideoModel()->SetLoop(loop);
}

void FfiOHOSAceFrameworkVideoEnableAnalyzer(bool enable)
{
    GetVideoModel()->EnableAnalyzer(enable);
}

void FfiOHOSAceFrameworkVideoOnStart(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    GetVideoModel()->SetOnStart(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnPause(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    GetVideoModel()->SetOnPause(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnFinish(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    GetVideoModel()->SetOnFinish(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnError(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    GetVideoModel()->SetOnError(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnStop(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    GetVideoModel()->SetOnStop(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnPrepared(void (*callback)(int32_t value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (!json || !json->IsValid()) {
            LOGE("json is invalid");
            return;
        }
        auto res = json->GetValue("duration")->GetInt();
        ffiCallback(res);
    };
    GetVideoModel()->SetOnPrepared(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnSeeking(void (*callback)(int32_t value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (!json || !json->IsValid()) {
            LOGE("json is invalid");
            return;
        }
        auto res = json->GetValue("time")->GetInt();
        ffiCallback(res);
    };
    GetVideoModel()->SetOnSeeking(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnSeeked(void (*callback)(int32_t value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (!json || !json->IsValid()) {
            LOGE("json is invalid");
            return;
        }
        auto res = json->GetValue("time")->GetInt();
        ffiCallback(res);
    };
    GetVideoModel()->SetOnSeeked(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnUpdate(void (*callback)(int32_t value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (!json || !json->IsValid()) {
            LOGE("json is invalid");
            return;
        }
        auto res = json->GetValue("time")->GetInt();
        ffiCallback(res);
    };
    GetVideoModel()->SetOnUpdate(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnFullscreenChange(void (*callback)(bool value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) {
        auto json = JsonUtil::ParseJsonString(param);
        if (!json || !json->IsValid()) {
            LOGE("json is invalid");
            return;
        }
        auto res = json->GetValue("fullscreen")->GetBool();
        ffiCallback(res);
    };
    GetVideoModel()->SetOnFullScreenChange(std::move(func));
}

int64_t FfiOHOSAceFrameworkVideoControllerCreate()
{
    auto controller = FFIData::Create<NativeVideoController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkVideoControllerStart(int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->Start();
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerPause(int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->Pause();
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerStop(int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->Stop();
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerReset(int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->Reset();
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerSetCurrentTime(int32_t time, int32_t seekMode, int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->SetCurrentTime(time, seekMode);
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerRequestFullscreen(bool fullScreen, int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->RequestFullscreen(fullScreen);
    } else {
        LOGE("invalid video controller id");
    }
}

void FfiOHOSAceFrameworkVideoControllerExitFullscreen(int64_t selfID)
{
    auto self = FFIData::GetData<NativeVideoController>(selfID);
    if (self) {
        self->ExitFullscreen();
    } else {
        LOGE("invalid video controller id");
    }
}
}
