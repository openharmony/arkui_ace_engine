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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_AXIS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_AXIS_EVENT_H

#include "core/event/non_pointer_event.h"
#include "core/components_ng/event/event_constants.h"

namespace OHOS::Ace::NG {

struct NonPointerAxisEvent final : public NonPointerEvent {
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
    ~NonPointerAxisEvent() = default;
    NonPointerAxisEvent()
    {
        eventType = UIInputEventType::NON_POINTER_AXIS;
    }

    NonPointerAxisEvent& SetId(int32_t id)
    {
        this->id = id;
        return *this;
    }

    NonPointerAxisEvent& SetAction(AxisAction action)
    {
        this->action = action;
        return *this;
    }

    NonPointerAxisEvent& SetSourceTool(SourceTool sourceTool)
    {
        this->sourceTool = sourceTool;
        return *this;
    }

    NonPointerAxisEvent& SetPointerEvent(std::shared_ptr<MMI::PointerEvent> pointerEvent)
    {
        this->pointerEvent = std::move(pointerEvent);
        return *this;
    }

    NonPointerAxisEvent& SetTouchEventId(int32_t touchEventId)
    {
        this->touchEventId = touchEventId;
        return *this;
    }

    NonPointerAxisEvent& SetPressedKeyCodes(const std::vector<KeyCode>& pressedCodes)
    {
        this->pressedCodes = pressedCodes;
        return *this;
    }

    NonPointerAxisEvent& SetTargetDisplayId(int32_t targetDisplayId)
    {
        this->targetDisplayId = targetDisplayId;
        return *this;
    }

    NonPointerAxisEvent& SetOriginalId(int32_t originalId)
    {
        this->originalId = originalId;
        return *this;
    }

    NonPointerAxisEvent& SetAbsXValue(float absXValue)
    {
        this->absXValue = absXValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsYValue(float absYValue)
    {
        this->absYValue = absYValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsZValue(float absZValue)
    {
        this->absZValue = absZValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsRzValue(float absRzValue)
    {
        this->absRzValue = absRzValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsHat0XValue(float absHat0XValue)
    {
        this->absHat0XValue = absHat0XValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsHat0YValue(float absHat0YValue)
    {
        this->absHat0YValue = absHat0YValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsBrakeValue(float absBrakeValue)
    {
        this->absBrakeValue = absBrakeValue;
        return *this;
    }

    NonPointerAxisEvent& SetAbsGasValue(float absGasValue)
    {
        this->absGasValue = absGasValue;
        return *this;
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_AXIS_EVENT_H
