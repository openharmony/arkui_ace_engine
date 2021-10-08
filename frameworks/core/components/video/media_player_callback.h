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

    void OnError(Media::PlayerErrorType errorType, int32_t errorCode) override
    {
        LOGE("OnError callback, errorType: %{public}d, errorCode: %{public}d", errorType, errorCode);
    }

    virtual void OnInfo(Media::PlayerOnInfoType type, int32_t extra, const Media::Format &InfoBody = {}) override
    {
        switch (type) {
            case OHOS::Media::INFO_TYPE_SEEKDONE:
                LOGI("OnSeekDone callback");
                if (positionUpdatedEvent_ != nullptr) {
                    positionUpdatedEvent_(extra / MILLISECONDS_TO_SECONDS);
                }
                break;
            case OHOS::Media::INFO_TYPE_EOS:
                LOGI("OnEndOfStream callback");
                if (endOfStreamEvent_ != nullptr) {
                    endOfStreamEvent_();
                }
                break;
            case OHOS::Media::INFO_TYPE_STATE_CHANGE:
                LOGI("OnStateChanged callback");
                PrintState(static_cast<OHOS::Media::PlayerStates>(extra));
                if (stateChangedEvent_ != nullptr) {
                    stateChangedEvent_(extra == OHOS::Media::PLAYER_STARTED);
                }
                break;
            case OHOS::Media::INFO_TYPE_POSITION_UPDATE:
                if (positionUpdatedEvent_ != nullptr) {
                    positionUpdatedEvent_(extra / MILLISECONDS_TO_SECONDS);
                }
                break;
            case OHOS::Media::INFO_TYPE_MESSAGE:
                LOGI("OnMessage callback type: %{public}d", extra);
                break;
            default:
                break;
            }
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
