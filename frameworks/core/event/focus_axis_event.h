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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_FOCUS_AXIS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_FOCUS_AXIS_EVENT_H

#include "core/event/non_pointer_event.h"
#include "core/components_ng/event/event_constants.h"

namespace OHOS::Ace::NG {

struct FocusAxisEvent final : public NonPointerEvent {
    int32_t id = 0;
    AxisAction action = AxisAction::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::shared_ptr<MMI::PointerEvent> pointerEvent;
    int32_t touchEventId = 0;
    std::vector<KeyCode> pressedCodes;
    int32_t targetDisplayId = 0;
    int32_t originalId = 0;
    float absXValue = 0.0f;
    float absYValue = 0.0f;
    float absZValue = 0.0f;
    float absRzValue = 0.0f;
    float absHat0XValue = 0.0f;
    float absHat0YValue = 0.0f;
    float absBrakeValue = 0.0f;
    float absGasValue = 0.0f;
    ~FocusAxisEvent() = default;
    FocusAxisEvent()
    {
        eventType = UIInputEventType::FOCUS_AXIS;
    }

    FocusAxisEvent& SetId(int32_t id)
    {
        this->id = id;
        return *this;
    }

    FocusAxisEvent& SetAction(AxisAction action)
    {
        this->action = action;
        return *this;
    }

    FocusAxisEvent& SetSourceTool(SourceTool sourceTool)
    {
        this->sourceTool = sourceTool;
        return *this;
    }

    FocusAxisEvent& SetPointerEvent(std::shared_ptr<MMI::PointerEvent> pointerEvent)
    {
        this->pointerEvent = std::move(pointerEvent);
        return *this;
    }

    FocusAxisEvent& SetTouchEventId(int32_t touchEventId)
    {
        this->touchEventId = touchEventId;
        return *this;
    }

    FocusAxisEvent& SetPressedKeyCodes(const std::vector<KeyCode>& pressedCodes)
    {
        this->pressedCodes = pressedCodes;
        return *this;
    }

    FocusAxisEvent& SetTargetDisplayId(int32_t targetDisplayId)
    {
        this->targetDisplayId = targetDisplayId;
        return *this;
    }

    FocusAxisEvent& SetOriginalId(int32_t originalId)
    {
        this->originalId = originalId;
        return *this;
    }

    FocusAxisEvent& SetAbsXValue(float absXValue)
    {
        this->absXValue = absXValue;
        return *this;
    }

    FocusAxisEvent& SetAbsYValue(float absYValue)
    {
        this->absYValue = absYValue;
        return *this;
    }

    FocusAxisEvent& SetAbsZValue(float absZValue)
    {
        this->absZValue = absZValue;
        return *this;
    }

    FocusAxisEvent& SetAbsRzValue(float absRzValue)
    {
        this->absRzValue = absRzValue;
        return *this;
    }

    FocusAxisEvent& SetAbsHat0XValue(float absHat0XValue)
    {
        this->absHat0XValue = absHat0XValue;
        return *this;
    }

    FocusAxisEvent& SetAbsHat0YValue(float absHat0YValue)
    {
        this->absHat0YValue = absHat0YValue;
        return *this;
    }

    FocusAxisEvent& SetAbsBrakeValue(float absBrakeValue)
    {
        this->absBrakeValue = absBrakeValue;
        return *this;
    }

    FocusAxisEvent& SetAbsGasValue(float absGasValue)
    {
        this->absGasValue = absGasValue;
        return *this;
    }
};

class ACE_EXPORT FocusAxisEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FocusAxisEventInfo, BaseEventInfo)

public:
    explicit FocusAxisEventInfo(const FocusAxisEvent& event) : BaseEventInfo("focusAxisEvent")
    {
        absXValue = event.absXValue;
        absYValue = event.absYValue;
        absZValue = event.absZValue;
        absRzValue = event.absRzValue;
        absHat0XValue = event.absHat0XValue;
        absHat0YValue = event.absHat0YValue;
        absBrakeValue = event.absBrakeValue;
        absGasValue = event.absGasValue;
        timeStamp_ = event.time;
        sourceTool_ = event.sourceTool;
        deviceType_ = event.sourceType;
        deviceId_ = event.deviceId;
        pressedKeyCodes_ = event.pressedCodes;
    };
    ~FocusAxisEventInfo() override = default;

    float GetAbsXValue() const
    {
        return absXValue;
    }

    float GetAbsYValue() const
    {
        return absYValue;
    }

    float GetAbsZValue() const
    {
        return absZValue;
    }

    float GetAbsRzValue() const
    {
        return absRzValue;
    }

    float GetAbsHat0XValue() const
    {
        return absHat0XValue;
    }

    float GetAbsHat0YValue() const
    {
        return absHat0YValue;
    }

    float GetAbsBrakeValue() const
    {
        return absBrakeValue;
    }

    float GetAbsGasValue() const
    {
        return absGasValue;
    }

private:
    float absXValue = 0.0f;
    float absYValue = 0.0f;
    float absZValue = 0.0f;
    float absRzValue = 0.0f;
    float absHat0XValue = 0.0f;
    float absHat0YValue = 0.0f;
    float absBrakeValue = 0.0f;
    float absGasValue = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_FOCUS_AXIS_EVENT_H
