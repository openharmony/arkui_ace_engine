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

#include "core/components_ng/pattern/video/video_controller_async.h"

#include <utility>

#include "base/log/log.h"

namespace OHOS::Ace {

VideoControllerAsync::VideoControllerAsync() = default;

VideoControllerAsync::~VideoControllerAsync() = default;

void VideoControllerAsync::Start(AsyncCommandCallback&& callback)
{
    if (!startImpl_) {
        ReportNullPattern("Start", std::move(callback));
        return;
    }
    startImpl_(std::move(callback));
}

void VideoControllerAsync::Pause(AsyncCommandCallback&& callback)
{
    if (!pauseImpl_) {
        ReportNullPattern("Pause", std::move(callback));
        return;
    }
    pauseImpl_(std::move(callback));
}

void VideoControllerAsync::Stop(AsyncCommandCallback&& callback)
{
    if (!stopImpl_) {
        ReportNullPattern("Stop", std::move(callback));
        return;
    }
    stopImpl_(std::move(callback));
}

void VideoControllerAsync::Reset(AsyncCommandCallback&& callback)
{
    if (!resetImpl_) {
        ReportNullPattern("Reset", std::move(callback));
        return;
    }
    resetImpl_(std::move(callback));
}

void VideoControllerAsync::SeekTo(float time, SeekMode seekMode)
{
    if (!seekToImpl_) {
        ReportNullPattern("SeekTo");
        return;
    }
    seekToImpl_(time, seekMode);
}

void VideoControllerAsync::RequestFullscreen(bool landscape)
{
    if (!requestFullscreenImpl_) {
        ReportNullPattern("RequestFullscreen");
        return;
    }
    requestFullscreenImpl_(landscape);
}

void VideoControllerAsync::ExitFullscreen()
{
    if (!exitFullscreenImpl_) {
        ReportNullPattern("ExitFullscreen");
        return;
    }
    exitFullscreenImpl_();
}

void VideoControllerAsync::SetStartImpl(StartImpl&& startImpl)
{
    startImpl_ = std::move(startImpl);
}

void VideoControllerAsync::SetPauseImpl(PauseImpl&& pauseImpl)
{
    pauseImpl_ = std::move(pauseImpl);
}

void VideoControllerAsync::SetStopImpl(StopImpl&& stopImpl)
{
    stopImpl_ = std::move(stopImpl);
}

void VideoControllerAsync::SetResetImpl(ResetImpl&& resetImpl)
{
    resetImpl_ = std::move(resetImpl);
}

void VideoControllerAsync::SetSeekToImpl(SeekToImpl&& seekToImpl)
{
    seekToImpl_ = std::move(seekToImpl);
}

void VideoControllerAsync::SetRequestFullscreenImpl(RequestFullscreenImpl&& requestFullscreenImpl)
{
    requestFullscreenImpl_ = std::move(requestFullscreenImpl);
}

void VideoControllerAsync::SetExitFullscreenImpl(ExitFullscreenImpl&& exitFullscreenImpl)
{
    exitFullscreenImpl_ = std::move(exitFullscreenImpl);
}

void VideoControllerAsync::Clear()
{
    startImpl_ = nullptr;
    pauseImpl_ = nullptr;
    stopImpl_ = nullptr;
    resetImpl_ = nullptr;
    seekToImpl_ = nullptr;
    requestFullscreenImpl_ = nullptr;
    exitFullscreenImpl_ = nullptr;
}

bool VideoControllerAsync::IsBound() const
{
    return startImpl_ || pauseImpl_ || stopImpl_ || resetImpl_ || seekToImpl_ || requestFullscreenImpl_ ||
           exitFullscreenImpl_;
}

void VideoControllerAsync::ReportNullPattern(const char* method, AsyncCommandCallback&& callback)
{
    TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::%{public}s: pattern is null", method);
    if (callback) {
        callback(false, "pattern is null");
    }
}

void VideoControllerAsync::ReportNullPattern(const char* method)
{
    TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::%{public}s: pattern is null", method);
}

} // namespace OHOS::Ace
