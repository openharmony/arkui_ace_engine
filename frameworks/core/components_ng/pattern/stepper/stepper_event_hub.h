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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

using RoutineCallbackEvent = std::function<void()>;
using IndexCallbackEvent = std::function<void(int32_t, int32_t)>;
using IndexChangeEvent = std::function<void(int32_t)>;

class StepperEventHub : public EventHub {
    DECLARE_ACE_TYPE(StepperEventHub, EventHub)

public:
    StepperEventHub() = default;
    ~StepperEventHub() override = default;

    void SetFinishEvent(RoutineCallbackEvent&& finishEvent)
    {
        finishEvent_ = finishEvent;
    }
    void SetSkipEvent(RoutineCallbackEvent&& skipEvent)
    {
        skipEvent_ = skipEvent;
    }
    void SetChangeEvent(IndexCallbackEvent&& changeEvent)
    {
        changeEvent_ = changeEvent;
    }
    void SetNextEvent(IndexCallbackEvent&& nextEvent)
    {
        nextEvent_ = nextEvent;
    }
    void SetPreviousEvent(IndexCallbackEvent&& previousEvent)
    {
        previousEvent_ = previousEvent;
    }

    void FireFinishEvent(int32_t index) const
    {
        if (finishEvent_) {
            finishEvent_();
        }
        RecordEvent(Recorder::EventType::STEPPER_FINISH, index);
    }
    void FireSkipEvent(int32_t index) const
    {
        if (skipEvent_) {
            skipEvent_();
        }
        RecordEvent(Recorder::EventType::STEPPER_SKIP, index);
    }
    void FireChangeEvent(int32_t prevIndex, int32_t index) const
    {
        if (onChangeEvent_) {
            onChangeEvent_(index);
        }
        if (changeEvent_) {
            changeEvent_(prevIndex, index);
        }
    }
    void FireNextEvent(int32_t index, int32_t pendingIndex) const
    {
        if (nextEvent_) {
            nextEvent_(index, pendingIndex);
        }
        RecordEvent(Recorder::EventType::STEPPER_NEXT, index);
    }
    void FirePreviousEvent(int32_t index, int32_t pendingIndex) const
    {
        if (previousEvent_) {
            previousEvent_(index, pendingIndex);
        }
        RecordEvent(Recorder::EventType::STEPPER_PREVIOUS, index);
    }
    void SetOnChangeEvent(IndexChangeEvent&& onChangeEvent)
    {
        onChangeEvent_ = onChangeEvent;
    }

private:
    void RecordEvent(Recorder::EventType eventType, int32_t index) const
    {
        if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            return;
        }
        Recorder::EventParamsBuilder builder;
        auto host = GetFrameNode();
        if (host) {
            builder.SetId(host->GetInspectorIdValue(""))
                .SetType(host->GetHostTag())
                .SetHost(host)
                .SetDescription(host->GetAutoEventParamValue(""));
        }
        builder.SetEventType(eventType).SetIndex(index);
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }

    RoutineCallbackEvent finishEvent_;
    RoutineCallbackEvent skipEvent_;
    IndexCallbackEvent changeEvent_;
    IndexCallbackEvent nextEvent_;
    IndexCallbackEvent previousEvent_;
    IndexChangeEvent onChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(StepperEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_EVENT_HUB_H
