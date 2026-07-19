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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_CONTROLLER_ASYNC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_CONTROLLER_ASYNC_H

#include <functional>
#include <string>
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/video/video_utils.h"

namespace OHOS::Ace {

class VideoControllerAsync : public virtual AceType {
    DECLARE_ACE_TYPE(VideoControllerAsync, AceType);

public:
    using AsyncCommandCallback = std::function<void(bool success, const std::string& reason)>;
    using StartImpl = std::function<void(AsyncCommandCallback&&)>;
    using PauseImpl = std::function<void(AsyncCommandCallback&&)>;
    using StopImpl = std::function<void(AsyncCommandCallback&&)>;
    using ResetImpl = std::function<void(AsyncCommandCallback&&)>;
    using SeekToImpl = std::function<void(float, SeekMode)>;
    using RequestFullscreenImpl = std::function<void(bool)>;
    using ExitFullscreenImpl = std::function<void()>;

    VideoControllerAsync();
    ~VideoControllerAsync() override;

    void Start(AsyncCommandCallback&& callback);
    void Pause(AsyncCommandCallback&& callback);
    void Stop(AsyncCommandCallback&& callback);
    void Reset(AsyncCommandCallback&& callback);
    void SeekTo(float time, SeekMode seekMode);
    void RequestFullscreen(bool landscape);
    void ExitFullscreen();

    void SetStartImpl(StartImpl&& startImpl);
    void SetPauseImpl(PauseImpl&& pauseImpl);
    void SetStopImpl(StopImpl&& stopImpl);
    void SetResetImpl(ResetImpl&& resetImpl);
    void SetSeekToImpl(SeekToImpl&& seekToImpl);
    void SetRequestFullscreenImpl(RequestFullscreenImpl&& requestFullscreenImpl);
    void SetExitFullscreenImpl(ExitFullscreenImpl&& exitFullscreenImpl);

    virtual void Clear();
    bool IsBound() const;

private:
    static void ReportNullPattern(const char* method, AsyncCommandCallback&& callback);
    static void ReportNullPattern(const char* method);

    StartImpl startImpl_;
    PauseImpl pauseImpl_;
    StopImpl stopImpl_;
    ResetImpl resetImpl_;
    SeekToImpl seekToImpl_;
    RequestFullscreenImpl requestFullscreenImpl_;
    ExitFullscreenImpl exitFullscreenImpl_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_CONTROLLER_ASYNC_H
