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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_EVENT_HUB_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_EVENT_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using MovingPhotoEventFunc = std::function<void()>;

class MovingPhotoEventHub : public EventHub {
    DECLARE_ACE_TYPE(MovingPhotoEventHub, EventHub)

public:
    MovingPhotoEventHub() = default;
    ~MovingPhotoEventHub() override = default;

    void SetOnComplete(MovingPhotoEventFunc&& onComplete)
    {
        onComplete_ = std::move(onComplete);
    }

    MovingPhotoEventFunc GetOnComplete()
    {
        return onComplete_;
    }

    void FireCompleteEvent()
    {
        if (onComplete_) {
            onComplete_();
        }
    }

    void SetOnStart(MovingPhotoEventFunc&& onStart)
    {
        onStart_ = std ::move(onStart);
    }

    MovingPhotoEventFunc GetOnStart()
    {
        return onStart_;
    }

    void FireStartEvent()
    {
        if (onStart_) {
            auto onStart = onStart_;
            onStart();
        }
    }

    void SetOnPause(MovingPhotoEventFunc&& onPause)
    {
        onPause_ = std ::move(onPause);
    }

    void FirePauseEvent()
    {
        if (onPause_) {
            auto onPause = onPause_;
            onPause();
        }
    }

    void SetOnStop(MovingPhotoEventFunc&& onStop)
    {
        onStop_ = std ::move(onStop);
    }

    MovingPhotoEventFunc GetOnStop()
    {
        return onStop_;
    }

    void FireStopEvent()
    {
        if (onStop_) {
            auto onStop = onStop_;
            onStop();
        }
    }

    void SetOnFinish(MovingPhotoEventFunc&& onFinish)
    {
        onFinish_ = std ::move(onFinish);
    }

    MovingPhotoEventFunc GetOnFinish()
    {
        return onFinish_;
    }

    void FireFinishEvent()
    {
        if (onFinish_) {
            auto onFinish = onFinish_;
            onFinish();
        }
    }

    void SetOnError(MovingPhotoEventFunc&& onError)
    {
        onError_ = std ::move(onError);
    }

    MovingPhotoEventFunc GetOnError()
    {
        return onError_;
    }

    void FireErrorEvent()
    {
        if (onError_) {
            auto onError = onError_;
            onError();
        }
    }

private:
    MovingPhotoEventFunc onComplete_;
    MovingPhotoEventFunc onStart_;
    MovingPhotoEventFunc onStop_;
    MovingPhotoEventFunc onPause_;
    MovingPhotoEventFunc onFinish_;
    MovingPhotoEventFunc onError_;
};

} // namespace OHOS::Ace::NG

#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_EVENT_HUB_H
