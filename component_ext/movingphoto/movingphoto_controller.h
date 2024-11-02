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
    DECLARE_ACE_TYPE(MovingPhotoController, AceType)

public:
    MovingPhotoController() = default;
    ~MovingPhotoController() override = default;

    using StartPlaybackImpl = std::function<void()>;
    using StopPlaybackImpl = std::function<void()>;
    using RefreshMovingPhotoImpl = std::function<void()>;

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

private:
    StartPlaybackImpl startPlaybackImpl_;
    StopPlaybackImpl stopPlaybackImpl_;
    RefreshMovingPhotoImpl refreshMovingPhotoImpl_;
};

} // namespace OHOS::Ace::NG
 
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_CONTROLLER_H