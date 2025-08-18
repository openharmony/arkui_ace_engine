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
    DECLARE_ACE_TYPE(VideoEventHub, EventHub);

public:
    VideoEventHub() = default;
    ~VideoEventHub() override = default;

    void SetOnStart(VideoEventCallback&& onStart)
    {
        onStart_ = std ::move(onStart);
    }
    void FireStartEvent()
    {
        auto json = JsonUtil::Create(true);
        json->Put("start", "");
        auto param = json->ToString();
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
    void FirePauseEvent()
    {
        auto json = JsonUtil::Create(true);
        json->Put("pause", "");
        auto param = json->ToString();
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
    void FireFinishEvent()
    {
        auto json = JsonUtil::Create(true);
        json->Put("finish", "");
        auto param = json->ToString();
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
    void FireErrorEvent()
    {
        auto json = JsonUtil::Create(true);
        json->Put("error", "");
        auto param = json->ToString();
        if (onError_) {
            // onError_ may be overwritten in its invoke so we copy it first
            auto onError = onError_;
            onError(param);
        }
        RecorderOnEvent(Recorder::EventType::VIDEO_ERROR, param);
    }
    void FireErrorEvent(int32_t code, const std::string& message)
    {
        auto json = JsonUtil::Create(true);
        const std::string name = "BusinessError";
        json->Put("code", code);
        json->Put("name", name.c_str());
        json->Put("message", message.c_str());
        auto param = json->ToString();

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
    void FirePreparedEvent(const double duration)
    {
        auto json = JsonUtil::Create(true);
        json->Put("duration", duration);
        auto param = json->ToString();
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
    void FireSeekingEvent(const double posTime)
    {
        auto json = JsonUtil::Create(true);
        json->Put("time", posTime);
        auto param = json->ToString();
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
    void FireSeekedEvent(const double posTime)
    {
        auto json = JsonUtil::Create(true);
        json->Put("time", posTime);
        auto param = json->ToString();
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
    void FireUpdateEvent(const double currentPos)
    {
        auto json = JsonUtil::Create(true);
        json->Put("time", currentPos);
        auto param = json->ToString();
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
    void FireStopEvent()
    {
        auto json = JsonUtil::Create(true);
        json->Put("stop", "");
        auto param = json->ToString();
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
    void FireFullScreenChangeEvent(const bool isFullScreen)
    {
        auto json = JsonUtil::Create(true);
        json->Put("fullscreen", isFullScreen);
        auto param = json->ToString();
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
            builder.SetType(host->GetHostTag()).SetHost(host).SetDescription(host->GetAutoEventParamValue(""));
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
