/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H

#include <algorithm>
#include <functional>
#include <list>

#include "base/log/log.h"
#include "core/components/video/video_utils.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace {
class VideoController : public virtual AceType {
    DECLARE_ACE_TYPE(VideoController, AceType);

public:
    using StartImpl = std::function<void()>;
    using PauseImpl = std::function<void()>;
    using StopImpl = std::function<void()>;
    using SeekToImpl = std::function<void(float, SeekMode)>;
    using RequestFullscreenImpl = std::function<void(bool)>;
    using ExitFullscreenImpl = std::function<void(bool)>;
    using ResetImpl = std::function<void()>;

    void Start()
    {
        if (startImpl_) {
            startImpl_();
        }
    }

    void Pause()
    {
        if (pauseImpl_) {
            pauseImpl_();
        }
    }

    void Reset()
    {
        if (resetImpl_) {
            resetImpl_();
        }
    }

    void Stop()
    {
        if (stopImpl_) {
            stopImpl_();
        }
    }

    void SeekTo(float pos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC)
    {
        if (seekToImpl_) {
            seekToImpl_(pos, seekMode);
        }
    }

    void RequestFullscreen(bool isPortrait)
    {
        if (requestFullscreenImpl_) {
            requestFullscreenImpl_(isPortrait);
        }
    }

    void ExitFullscreen(bool isSync)
    {
        if (exitFullscreenImpl_) {
            exitFullscreenImpl_(isSync);
        }
    }

    void SetResetImpl(ResetImpl&& resetImpl)
    {
        resetImpl_ = std::move(resetImpl);
    }

    void SetStartImpl(StartImpl&& startImpl)
    {
        startImpl_ = std::move(startImpl);
    }

    void SetPausetImpl(PauseImpl&& pauseImpl)
    {
        pauseImpl_ = std::move(pauseImpl);
    }

    void SetStopImpl(StopImpl&& stopImpl)
    {
        stopImpl_ = std::move(stopImpl);
    }

    void SetSeekToImpl(SeekToImpl&& seekToImpl)
    {
        seekToImpl_ = std::move(seekToImpl);
    }

    void SetRequestFullscreenImpl(RequestFullscreenImpl&& requestFullscreenImpl)
    {
        requestFullscreenImpl_ = std::move(requestFullscreenImpl);
    }

    void SetExitFullscreenImpl(ExitFullscreenImpl&& exitFullscreenImpl)
    {
        exitFullscreenImpl_ = std::move(exitFullscreenImpl);
    }

private:
    StartImpl startImpl_;
    PauseImpl pauseImpl_;
    StopImpl stopImpl_;
    SeekToImpl seekToImpl_;
    RequestFullscreenImpl requestFullscreenImpl_;
    ExitFullscreenImpl exitFullscreenImpl_;
    ResetImpl resetImpl_;
};

class VideoControllerV2 : public virtual AceType {
    DECLARE_ACE_TYPE(VideoControllerV2, AceType);

public:
    void Start()
    {
        for (const auto& item : controllers_) {
            item->Start();
        }
    }

    void Pause()
    {
        for (const auto& item : controllers_) {
            item->Pause();
        }
    }

    void Reset()
    {
        for (const auto& item : controllers_) {
            item->Reset();
        }
    }

    void Stop()
    {
        for (const auto& item : controllers_) {
            item->Stop();
        }
    }

    void SeekTo(float pos, SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC)
    {
        for (const auto& item : controllers_) {
            item->SeekTo(pos, seekMode);
        }
    }

    void RequestFullscreen(bool isPortrait)
    {
        for (const auto& item : controllers_) {
            item->RequestFullscreen(isPortrait);
        }
    }

    void ExitFullscreen(bool isSync)
    {
        for (const auto& item : controllers_) {
            item->ExitFullscreen(isSync);
        }
    }

    void AddVideoController(const RefPtr<VideoController>& videoController)
    {
        auto it = std::find(controllers_.begin(), controllers_.end(), videoController);
        if (it != controllers_.end()) {
            LOGW("Controller is already existed");
            return;
        }

        controllers_.emplace_back(videoController);
    }

    void RemoveVideoController(const RefPtr<VideoController>& videoController)
    {
        if (videoController) {
            controllers_.remove(videoController);
        }
    }

    void Clear()
    {
        controllers_.clear();
    }

private:
    std::list<RefPtr<VideoController>> controllers_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_CONTROLLER_V2_H
