/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MEDIA_PLAYER_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MEDIA_PLAYER_CALLBACK_H

#include "base/log/log.h"

#include "foundation/multimedia/media_standard/interfaces/innerkits/native/media/include/player.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;

} // namespace

struct MediaPlayerCallback : public Media::PlayerCallback {

public:
    using PositionUpdatedEvent = std::function<void(uint32_t)>;
    using EndOfStreamEvent = std::function<void()>;
    using StateChangedEvent = std::function<void(bool)>;

    MediaPlayerCallback() = default;
    ~MediaPlayerCallback() = default;

    void OnError(int32_t errorType, int32_t errorCode) override
    {
        LOGE("OnError callback, errorType: %{public}d, errorCode: %{public}d", errorType, errorCode);
    }

    void OnEndOfStream(bool isLooping) override
    {
        (void)isLooping;
        LOGI("OnEndOfStream callback");
        if (endOfStreamEvent_ != nullptr) {
            endOfStreamEvent_();
        }
    }

    void OnStateChanged(OHOS::Media::PlayerStates state) override
    {
        LOGI("OnStateChanged callback");
        PrintState(state);
        if (stateChangedEvent_ != nullptr) {
            stateChangedEvent_(state == OHOS::Media::PLAYER_STARTED);
        }
    }

    void OnSeekDone(uint64_t currentPosition) override
    {
        LOGI("OnSeekDone callback");
        if (positionUpdatedEvent_ != nullptr && currentPosition != 0) {
            positionUpdatedEvent_(currentPosition / MILLISECONDS_TO_SECONDS);
        }
    }

    void OnPositionUpdated(uint64_t position) override
    {
        if (positionUpdatedEvent_ != nullptr && position != 0) {
            positionUpdatedEvent_(position / MILLISECONDS_TO_SECONDS);
        }
    }

    void OnMessage(int32_t type, int32_t extra) override
    {
        (void)extra;
        LOGI("OnMessage callback type: %{public}d", type);
    }

    void PrintState(OHOS::Media::PlayerStates state) const
    {
        switch (state) {
            case OHOS::Media::PLAYER_STOPPED:
                LOGI("State: Stopped");
                break;
            case OHOS::Media::PLAYER_PREPARED:
                LOGI("State: Buffering");
                break;
            case OHOS::Media::PLAYER_PAUSED:
                LOGI("State: Paused");
                break;
            case OHOS::Media::PLAYER_STARTED:
                LOGI("State: Playing");
                break;
            default:
                LOGI("Invalid state");
                break;
        }
    }

    void SetPositionUpdatedEvent(PositionUpdatedEvent&& positionUpdatedEvent)
    {
        positionUpdatedEvent_ = std::move(positionUpdatedEvent);
    }

    void SetEndOfStreamEvent(EndOfStreamEvent&& endOfStreamEvent)
    {
        endOfStreamEvent_ = std::move(endOfStreamEvent);
    }

    void SetStateChangedEvent(StateChangedEvent&& stateChangedEvent)
    {
        stateChangedEvent_ = std::move(stateChangedEvent);
    }

private:
    PositionUpdatedEvent positionUpdatedEvent_;
    EndOfStreamEvent endOfStreamEvent_;
    StateChangedEvent stateChangedEvent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_MEDIA_PLAYER_CALLBACK_H
