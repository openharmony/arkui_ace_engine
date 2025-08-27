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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_CONTROLLER_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_CONTROLLER_H

#include <functional>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class MovingPhotoController : public virtual AceType {
    DECLARE_ACE_TYPE(MovingPhotoController, AceType);

public:
    MovingPhotoController() = default;
    ~MovingPhotoController() override = default;

    using StartPlaybackImpl = std::function<void()>;
    using StopPlaybackImpl = std::function<void()>;
    using RefreshMovingPhotoImpl = std::function<void()>;
    using PauseImpl = std::function<void()>;
    using ResetImpl = std::function<void()>;
    using RestartImpl = std::function<void()>;
    using EnableTransitionImpl = std::function<void(bool)>;
    using SetPlaybackPeriodFucImpl = std::function<void(int64_t, int64_t)>;
    using EnableAutoPlayImpl = std::function<void(bool)>;
    using NotifyTransitionImpl = std::function<void()>;

    void SetStartPlaybackImpl(StartPlaybackImpl&& startPlaybackImpl)
    {
        startPlaybackImpl_ = std::move(startPlaybackImpl);
    }

    void StartPlayback()
    {
        if (startPlaybackImpl_) {
            startPlaybackImpl_();
        }
    }

    void SetStopPlaybackImpl(StopPlaybackImpl&& stopPlaybackImpl)
    {
        stopPlaybackImpl_ = std::move(stopPlaybackImpl);
    }

    void StopPlayback()
    {
        if (stopPlaybackImpl_) {
            stopPlaybackImpl_();
        }
    }

    void SetRefreshMovingPhotoImpl(RefreshMovingPhotoImpl&& refreshMovingPhotoImpl)
    {
        refreshMovingPhotoImpl_ = std::move(refreshMovingPhotoImpl);
    }

    void RefreshMovingPhoto()
    {
        if (refreshMovingPhotoImpl_) {
            refreshMovingPhotoImpl_();
        }
    }

    void SetPauseImpl(PauseImpl&& pauseImpl)
    {
        pauseImpl_ = std::move(pauseImpl);
    }

    void Pause()
    {
        if (pauseImpl_) {
            pauseImpl_();
        }
    }

    void SetResetImpl(ResetImpl&& resetImpl)
    {
        resetImpl_ = std::move(resetImpl);
    }

    void Reset()
    {
        if (resetImpl_) {
            resetImpl_();
        }
    }

    void SetRestartImpl(RestartImpl&& restartImpl)
    {
        restartImpl_ = std::move(restartImpl);
    }

    void Restart()
    {
        if (restartImpl_) {
            restartImpl_();
        }
    }

    void SetPlaybackPeriodImpl(SetPlaybackPeriodFucImpl&& setPlaybackPeriodImpl)
    {
        setPlaybackPeriodFucImpl_ = std::move(setPlaybackPeriodImpl);
    }

    void SetPlaybackPeriod(int64_t startTime, int64_t endTime)
    {
        if (setPlaybackPeriodFucImpl_) {
            setPlaybackPeriodFucImpl_(startTime, endTime);
        }
    }

    void SetEnableTransitionImpl(EnableTransitionImpl&& enableTransitionImpl)
    {
        enableTransitionImpl_ = std::move(enableTransitionImpl);
    }

    void EnableTransition(bool enabled)
    {
        if (enableTransitionImpl_) {
            enableTransitionImpl_(enabled);
        }
    }

    void SetEnableAutoPlayImpl(EnableAutoPlayImpl&& enableAutoPlayImpl)
    {
        enableAutoPlayImpl_ = std::move(enableAutoPlayImpl);
    }

    void EnableAutoPlay(bool enabled)
    {
        if (enableAutoPlayImpl_) {
            enableAutoPlayImpl_(enabled);
        }
    }

    void SetNotifyTransitionImpl(NotifyTransitionImpl&&
        notifyTransitionImpl)
    {
        notifyTransitionImpl_ = std::move(notifyTransitionImpl);
    }

    void NotifyTransition()
    {
        if (notifyTransitionImpl_) {
            notifyTransitionImpl_();
        }
    }

private:
    StartPlaybackImpl startPlaybackImpl_;
    StopPlaybackImpl stopPlaybackImpl_;
    RefreshMovingPhotoImpl refreshMovingPhotoImpl_;
    PauseImpl pauseImpl_;
    ResetImpl resetImpl_;
    RestartImpl restartImpl_;
    EnableTransitionImpl enableTransitionImpl_;
    SetPlaybackPeriodFucImpl setPlaybackPeriodFucImpl_;
    EnableAutoPlayImpl enableAutoPlayImpl_;
    NotifyTransitionImpl notifyTransitionImpl_;
};

} // namespace OHOS::Ace::NG
 
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_CONTROLLER_H