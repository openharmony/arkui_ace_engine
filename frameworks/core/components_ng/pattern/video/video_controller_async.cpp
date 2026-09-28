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
    StartImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = startImpl_;
    }
    if (!impl) {
        ReportNullPattern("Start", std::move(callback));
        return;
    }
    impl(std::move(callback));
}

void VideoControllerAsync::Pause(AsyncCommandCallback&& callback)
{
    PauseImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = pauseImpl_;
    }
    if (!impl) {
        ReportNullPattern("Pause", std::move(callback));
        return;
    }
    impl(std::move(callback));
}

void VideoControllerAsync::Stop(AsyncCommandCallback&& callback)
{
    StopImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = stopImpl_;
    }
    if (!impl) {
        ReportNullPattern("Stop", std::move(callback));
        return;
    }
    impl(std::move(callback));
}

void VideoControllerAsync::Reset(AsyncCommandCallback&& callback)
{
    ResetImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = resetImpl_;
    }
    if (!impl) {
        ReportNullPattern("Reset", std::move(callback));
        return;
    }
    impl(std::move(callback));
}

void VideoControllerAsync::SeekTo(float time, SeekMode seekMode)
{
    SeekToImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = seekToImpl_;
    }
    if (!impl) {
        ReportNullPattern("SeekTo");
        return;
    }
    impl(time, seekMode);
}

void VideoControllerAsync::RequestFullscreen(bool landscape)
{
    RequestFullscreenImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = requestFullscreenImpl_;
    }
    if (!impl) {
        ReportNullPattern("RequestFullscreen");
        return;
    }
    impl(landscape);
}

void VideoControllerAsync::ExitFullscreen()
{
    ExitFullscreenImpl impl;
    {
        std::lock_guard<std::mutex> lock(implMutex_);
        impl = exitFullscreenImpl_;
    }
    if (!impl) {
        ReportNullPattern("ExitFullscreen");
        return;
    }
    impl();
}

void VideoControllerAsync::SetStartImpl(StartImpl&& startImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    startImpl_ = std::move(startImpl);
}

void VideoControllerAsync::SetPauseImpl(PauseImpl&& pauseImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    pauseImpl_ = std::move(pauseImpl);
}

void VideoControllerAsync::SetStopImpl(StopImpl&& stopImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    stopImpl_ = std::move(stopImpl);
}

void VideoControllerAsync::SetResetImpl(ResetImpl&& resetImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    resetImpl_ = std::move(resetImpl);
}

void VideoControllerAsync::SetSeekToImpl(SeekToImpl&& seekToImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    seekToImpl_ = std::move(seekToImpl);
}

void VideoControllerAsync::SetRequestFullscreenImpl(RequestFullscreenImpl&& requestFullscreenImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    requestFullscreenImpl_ = std::move(requestFullscreenImpl);
}

void VideoControllerAsync::SetExitFullscreenImpl(ExitFullscreenImpl&& exitFullscreenImpl)
{
    std::lock_guard<std::mutex> lock(implMutex_);
    exitFullscreenImpl_ = std::move(exitFullscreenImpl);
}

void VideoControllerAsync::Clear()
{
    std::lock_guard<std::mutex> lock(implMutex_);
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
    std::lock_guard<std::mutex> lock(implMutex_);
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
