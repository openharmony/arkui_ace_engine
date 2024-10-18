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


#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

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
        VideoModel::GetInstance()->Create(controller->GetController());
        VideoModel::GetInstance()->SetSrc(src, "", "");
        VideoModel::GetInstance()->SetProgressRate(progressRate);
        VideoModel::GetInstance()->SetPosterSourceInfo(preview, "", "");
    } else {
        LOGE("video controller id is invalid");
    }
}

void FfiOHOSAceFrameworkVideoMuted(bool muted)
{
    VideoModel::GetInstance()->SetMuted(muted);
}

void FfiOHOSAceFrameworkVideoAutoPlay(bool autoPlay)
{
    VideoModel::GetInstance()->SetAutoPlay(autoPlay);
}

void FfiOHOSAceFrameworkVideoControls(bool controls)
{
    VideoModel::GetInstance()->SetControls(controls);
}

void FfiOHOSAceFrameworkVideoObjectFit(int32_t objectFit)
{
    VideoModel::GetInstance()->SetObjectFit(static_cast<ImageFit>(objectFit));
}

void FfiOHOSAceFrameworkVideoLoop(bool loop)
{
    VideoModel::GetInstance()->SetLoop(loop);
}

void FfiOHOSAceFrameworkVideoOnStart(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    VideoModel::GetInstance()->SetOnStart(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnPause(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    VideoModel::GetInstance()->SetOnPause(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnFinish(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    VideoModel::GetInstance()->SetOnFinish(std::move(func));
}

void FfiOHOSAceFrameworkVideoOnError(void (*callback)(const char* value))
{
    auto func = [ffiCallback = CJLambda::Create(callback)](const std::string& param) { ffiCallback(param.c_str()); };
    VideoModel::GetInstance()->SetOnError(std::move(func));
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
    VideoModel::GetInstance()->SetOnPrepared(std::move(func));
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
    VideoModel::GetInstance()->SetOnSeeking(std::move(func));
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
    VideoModel::GetInstance()->SetOnSeeked(std::move(func));
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
    VideoModel::GetInstance()->SetOnUpdate(std::move(func));
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
    VideoModel::GetInstance()->SetOnFullScreenChange(std::move(func));
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