/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_EVENT_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using VideoEventCallback = std::function<void(const std::string&)>;

class VideoEventHub : public EventHub {
    DECLARE_ACE_TYPE(VideoEventHub, EventHub)

public:
    VideoEventHub() = default;
    ~VideoEventHub() override = default;

    void SetOnStart(VideoEventCallback&& onStart)
    {
        onStart_ = std ::move(onStart);
    }
    void FireStartEvent(const std::string& param)
    {
        if (onStart_) {
            // onStart_ may be overwritten in its invoke so we copy it first
            auto onStart = onStart_;
            onStart(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_START, param);
    }

    void SetOnPause(VideoEventCallback&& onPause)
    {
        onPause_ = std ::move(onPause);
    }
    void FirePauseEvent(const std::string& param)
    {
        if (onPause_) {
            // onPause_ may be overwritten in its invoke so we copy it first
            auto onPause = onPause_;
            onPause(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_PAUSE, param);
    }

    void SetOnFinish(VideoEventCallback&& onFinish)
    {
        onFinish_ = std ::move(onFinish);
    }
    void FireFinishEvent(const std::string& param)
    {
        if (onFinish_) {
            // onFinish_ may be overwritten in its invoke so we copy it first
            auto onFinish = onFinish_;
            onFinish(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_FINISH, param);
    }

    void SetOnError(VideoEventCallback&& onError)
    {
        onError_ = std ::move(onError);
    }
    void FireErrorEvent(const std::string& param)
    {
        if (onError_) {
            // onError_ may be overwritten in its invoke so we copy it first
            auto onError = onError_;
            onError(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_ERROR, param);
    }

    void SetOnPrepared(VideoEventCallback&& onPrepared)
    {
        onPrepared_ = std ::move(onPrepared);
    }
    void FirePreparedEvent(const std::string& param)
    {
        if (onPrepared_) {
            // onPrepared_ may be overwritten in its invoke so we copy it first
            auto onPrepared = onPrepared_;
            onPrepared(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_PREPARED, param);
    }

    void SetOnSeeking(VideoEventCallback&& onSeeking)
    {
        onSeeking_ = std ::move(onSeeking);
    }
    void FireSeekingEvent(const std::string& param)
    {
        if (onSeeking_) {
            // onSeeking_ may be overwritten in its invoke so we copy it first
            auto onSeeking = onSeeking_;
            onSeeking(param);
        }
    }

    void SetOnSeeked(VideoEventCallback&& onSeeked)
    {
        onSeeked_ = std ::move(onSeeked);
    }
    void FireSeekedEvent(const std::string& param)
    {
        if (onSeeked_) {
            // onSeeked_ may be overwritten in its invoke so we copy it first
            auto onSeeked = onSeeked_;
            onSeeked(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_SEEKED, param);
    }

    void SetOnUpdate(VideoEventCallback&& onUpdate)
    {
        onUpdate_ = std ::move(onUpdate);
    }
    void FireUpdateEvent(const std::string& param)
    {
        if (onUpdate_) {
            // onUpdate_ may be overwritten in its invoke so we copy it first
            auto onUpdate = onUpdate_;
            onUpdate(param);
        }
    }

    void SetOnStop(VideoEventCallback&& onStop)
    {
        onStop_ = std ::move(onStop);
    }
    void FireStopEvent(const std::string& param)
    {
        if (onStop_) {
            // onStop_ may be overwritten in its invoke so we copy it first
            auto onStop = onStop_;
            onStop(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_STOP, param);
    }

    void SetOnFullScreenChange(VideoEventCallback&& onFullScreenChange)
    {
        onFullScreenChange_ = std ::move(onFullScreenChange);
    }
    void FireFullScreenChangeEvent(const std::string& param)
    {
        if (onFullScreenChange_) {
            // onFullScreenChange_ may be overwritten in its invoke so we copy it first
            auto onFullScreenChange = onFullScreenChange_;
            onFullScreenChange(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_SCREEN_CHANGE, param);
    }

    void SetInspectorId(const std::string& inspectorId)
    {
        inspectorId_ = inspectorId;
    }

private:
    void RecorderOnEvent(Recorder::EventType eventType, const std::string& param) const
    {
        if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            return;
        }
        Recorder::EventParamsBuilder builder;
        builder.SetId(inspectorId_);
        auto host = GetFrameNode();
        if (host) {
            builder.SetType(host->GetHostTag()).SetDescription(host->GetAutoEventParamValue(""));
        }
        builder.SetEventType(eventType).SetText(param);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }

    VideoEventCallback onStart_;
    VideoEventCallback onPause_;
    VideoEventCallback onFinish_;
    VideoEventCallback onError_;
    VideoEventCallback onPrepared_;
    VideoEventCallback onSeeking_;
    VideoEventCallback onSeeked_;
    VideoEventCallback onUpdate_;
    VideoEventCallback onStop_;
    VideoEventCallback onFullScreenChange_;
    std::string inspectorId_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_EVENT_HUB_H
