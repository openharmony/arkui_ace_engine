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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_PLAYER_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_PLAYER_CALLBACK_H

#include "base/log/log.h"

#include "core/common/container_scope.h"
#include "core/components/video/video_utils.h"
#include "media_errors.h"
#include "player.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t MILLISECONDS_TO_SECONDS = 1000;

PlaybackStatus ConvertToPlaybackStatus(int32_t status)
{
    PlaybackStatus result = PlaybackStatus::NONE;
    switch (status) {
        case OHOS::Media::PLAYER_STATE_ERROR:
            result = PlaybackStatus::ERROR;
            break;
        case OHOS::Media::PLAYER_IDLE:
            result = PlaybackStatus::IDLE;
            break;
        case OHOS::Media::PLAYER_INITIALIZED:
            result = PlaybackStatus::INITIALIZED;
            break;
        case OHOS::Media::PLAYER_PREPARED:
            result = PlaybackStatus::PREPARED;
            break;
        case OHOS::Media::PLAYER_STARTED:
            result = PlaybackStatus::STARTED;
            break;
        case OHOS::Media::PLAYER_PAUSED:
            result = PlaybackStatus::PAUSED;
            break;
        case OHOS::Media::PLAYER_STOPPED:
            result = PlaybackStatus::STOPPED;
            break;
        case OHOS::Media::PLAYER_PLAYBACK_COMPLETE:
            result = PlaybackStatus::PLAYBACK_COMPLETE;
            break;
        default:
            LOGE("status is not supported");
            break;
    }
    return result;
}

} // namespace

struct MediaPlayerCallback : public Media::PlayerCallback {
public:
    using PositionUpdatedEvent = std::function<void(uint32_t)>;
    using SeekDoneEvent = std::function<void(uint32_t)>;
    using StateChangedEvent = std::function<void(PlaybackStatus)>;
    using CommonEvent = std::function<void()>;
    using VideoErrorEvent = std::function<void(int32_t code, const std::string& message)>;

    MediaPlayerCallback() = default;
    explicit MediaPlayerCallback(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    ~MediaPlayerCallback() = default;

    // Above api9
    void OnError(int32_t errorCode, const std::string &errorMsg) override
    {
        LOGE("OnError callback, errorCode: %{public}d, error message: %{public}s", errorCode, errorMsg.c_str());
        ContainerScope scope(instanceId_);
        if (errorEvent_) {
            errorEvent_();
        }
    }

    void OnInfo(Media::PlayerOnInfoType type, int32_t extra, const Media::Format &InfoBody = {}) override
    {
        ContainerScope scope(instanceId_);
        switch (type) {
            case OHOS::Media::INFO_TYPE_SEEKDONE:
                if (seekDoneEvent_) {
                    seekDoneEvent_(extra / MILLISECONDS_TO_SECONDS);
                } else if (positionUpdatedEvent_) {
                    positionUpdatedEvent_(extra / MILLISECONDS_TO_SECONDS);
                }
                break;
            case OHOS::Media::INFO_TYPE_EOS:
                if (endOfStreamEvent_) {
                    endOfStreamEvent_();
                }
                break;
            case OHOS::Media::INFO_TYPE_STATE_CHANGE:
                PrintState(static_cast<OHOS::Media::PlayerStates>(extra));
                if (stateChangedEvent_) {
                    stateChangedEvent_(ConvertToPlaybackStatus(extra));
                }
                break;
            case OHOS::Media::INFO_TYPE_POSITION_UPDATE:
                if (positionUpdatedEvent_) {
                    positionUpdatedEvent_(extra / MILLISECONDS_TO_SECONDS);
                }
                break;
            case OHOS::Media::INFO_TYPE_RESOLUTION_CHANGE:
                if (resolutionChangeEvent_) {
                    resolutionChangeEvent_();
                }
                break;
            case OHOS::Media::INFO_TYPE_MESSAGE:
                if (extra == Media::PlayerMessageType::PLAYER_INFO_VIDEO_RENDERING_START) {
                    if (startRenderFrameEvent_) {
                        startRenderFrameEvent_();
                    }
                }
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

    void SetEndOfStreamEvent(CommonEvent&& endOfStreamEvent)
    {
        endOfStreamEvent_ = std::move(endOfStreamEvent);
    }

    void SetStateChangedEvent(StateChangedEvent&& stateChangedEvent)
    {
        stateChangedEvent_ = std::move(stateChangedEvent);
    }

    void SetErrorEvent(CommonEvent&& errorEvent)
    {
        errorEvent_ = std::move(errorEvent);
    }

    virtual void SetErrorEvent(VideoErrorEvent&& errorEvent) {}

    void SetResolutionChangeEvent(CommonEvent&& resolutionChangeEvent)
    {
        resolutionChangeEvent_ = std::move(resolutionChangeEvent);
    }

    void SetStartRenderFrameEvent(CommonEvent&& startRenderFrameEvent)
    {
        startRenderFrameEvent_ = std::move(startRenderFrameEvent);
    }

    void SetSeekDoneEvent(SeekDoneEvent&& seekDoneEvent)
    {
        seekDoneEvent_ = std::move(seekDoneEvent);
    }

private:
    PositionUpdatedEvent positionUpdatedEvent_;
    SeekDoneEvent seekDoneEvent_;
    CommonEvent endOfStreamEvent_;
    StateChangedEvent stateChangedEvent_;
    CommonEvent errorEvent_;
    CommonEvent resolutionChangeEvent_;
    CommonEvent startRenderFrameEvent_;
    int32_t instanceId_ = -1;
};

struct VideoMediaPlayerCallback : public MediaPlayerCallback {
public:
    using VideoErrorEvent = std::function<void(int32_t code, const std::string& message)>;

    VideoMediaPlayerCallback() = default;
    explicit VideoMediaPlayerCallback(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    ~VideoMediaPlayerCallback() = default;

    // Above api9
    void OnError(int32_t errorCode, const std::string& errorMsg) override
    {
        auto newCode = OHOS::Media::MSErrorToExtErrorAPI9(static_cast<Media::MediaServiceErrCode>(errorCode));
        auto newMsg = OHOS::Media::MSExtAVErrorToString(newCode) + errorMsg;
        ContainerScope scope(instanceId_);
        if (errorEvent_) {
            errorEvent_(newCode, newMsg);
        }
    }

    void SetErrorEvent(VideoErrorEvent&& errorEvent) override
    {
        errorEvent_ = std::move(errorEvent);
    }

private:
    VideoErrorEvent errorEvent_;
    int32_t instanceId_ = -1;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_PLAYER_CALLBACK_H
