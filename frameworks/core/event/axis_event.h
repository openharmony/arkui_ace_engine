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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H

#include <list>
#include <utility>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_constants.h"
#include "core/event/ace_events.h"
#include "ui/event/axis_event.h"

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

struct AxisEvent final : public PointerEvent {
    ~AxisEvent() = default;
    int32_t id = 0;

    double verticalAxis = 0.0;
    double horizontalAxis = 0.0;
    double pinchAxisScale = 0.0;
    double rotateAxisAngle = 0.0;
    bool isRotationEvent = false;
    AxisAction action = AxisAction::NONE;
    int64_t deviceId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::shared_ptr<const MMI::PointerEvent> pointerEvent;
    int32_t touchEventId = 0;
    std::vector<KeyCode> pressedCodes;

    // Coordinates relative to the upper-left corner of the current component
    float localX = 0.0;
    float localY = 0.0;

    int32_t targetDisplayId = 0;
    int32_t originalId = 0;
    bool isInjected = false;
    float targetPositionX = 0.0;
    float targetPositionY = 0.0;
    float targetGlobalPositionX = 0.0;
    float targetGlobalPositionY = 0.0;
    float width = 0.0;
    float height = 0.0;
    uint64_t modifierKeyState = 0;

    int32_t scrollStep = 0;
    uint32_t axes = 0;

    AxisEvent()
    {
        eventType = UIInputEventType::AXIS;
    }
    AxisEvent(int32_t id, float x, float y, float screenX, float screenY, double globalDisplayX, double globalDisplayY,
        double verticalAxis, double horizontalAxis, double pinchAxisScale, double rotateAxisAngle, bool isRotationEvent,
        AxisAction action, TimeStamp timestamp, int64_t deviceId, SourceType sourceType, SourceTool sourceTool,
        std::shared_ptr<const MMI::PointerEvent> pointerEvent, std::vector<KeyCode> pressedCodes,
        int32_t targetDisplayId, int32_t originalId, bool isInjected, int32_t scrollStep, uint32_t axes)
        : PointerEvent(x, y, screenX, screenY, globalDisplayX, globalDisplayY, timestamp), id(id),
          verticalAxis(verticalAxis), horizontalAxis(horizontalAxis), pinchAxisScale(pinchAxisScale),
          rotateAxisAngle(rotateAxisAngle), isRotationEvent(isRotationEvent), action(action), deviceId(deviceId),
          sourceType(sourceType), sourceTool(sourceTool), pointerEvent(std::move(pointerEvent)),
          pressedCodes(pressedCodes), targetDisplayId(targetDisplayId), originalId(originalId), isInjected(isInjected),
          scrollStep(scrollStep), axes(axes)
    {
        eventType = UIInputEventType::AXIS;
    }

    AxisEvent CreateScaleEvent(float scale) const;
    AxisEvent CloneWith(float scale) const;
    Offset GetOffset() const;
    Offset GetScreenOffset() const;
    Offset GetGlobalDisplayOffset() const;
    int32_t GetTargetDisplayId() const;
    AxisDirection GetDirection() const;
    static bool IsDirectionUp(AxisDirection direction);
    static bool IsDirectionDown(AxisDirection direction);
    static bool IsDirectionLeft(AxisDirection direction);
    static bool IsDirectionRight(AxisDirection direction);
    Offset ConvertToOffset(bool isShiftKeyPressed = false, bool hasDifferentDirectionGesture = false) const;
    // MMI has the different direction, need to check truth direction.
    std::pair<float, float> ConvertToSummationAxisValue(const AxisEvent& event) const;
    bool HasKey(KeyCode expectCode) const;
};

class AxisInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(AxisInfo, BaseEventInfo);

public:
    AxisInfo() : BaseEventInfo("onAxis") {}
    AxisInfo(const AxisEvent& event, const Offset& localLocation, const EventTarget& target);
    ~AxisInfo() override = default;
    void SetAction(AxisAction action);
    AxisAction GetAction() const;
    int32_t GetScrollStep() const;
    void SetRotateAxisAngle(float angle);
    float GetRotateAxisAngle() const;
    void SetIsRotationEvent(bool rotationFlag);
    bool GetIsRotationEvent() const;
    bool HasAxis(AxisType axis);
    uint32_t GetAxes() const;
    AxisInfo& SetGlobalLocation(const Offset& globalLocation);
    AxisInfo& SetLocalLocation(const Offset& localLocation);
    AxisInfo& SetScreenLocation(const Offset& screenLocation);
    AxisInfo& SetGlobalDisplayLocation(const Offset& globalDisplayLocation);
    const Offset& GetGlobalDisplayLocation() const;
    const Offset& GetScreenLocation() const;
    const Offset& GetLocalLocation() const;
    const Offset& GetGlobalLocation() const;
    AxisEvent ConvertToAxisEvent() const;

private:
    AxisAction action_ = AxisAction::NONE;
    int32_t scrollStep_ = 0;
    uint32_t axes_ = 0;
    float rotateAxisAngle_ = 0.0;
    bool isRotationEvent_ = false;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
    Offset screenLocation_;
    // The location where the touch point touches the screen when there are multiple screens.
    Offset globalDisplayLocation_;
};

class CoastingAxisInfo {
public:
    CoastingAxisInfo() = default;
    ~CoastingAxisInfo() = default;

    const TimeStamp& GetTimeStamp() const
    {
        return timeStamp_;
    }
    void SetTimeStamp(const TimeStamp& timeStamp)
    {
        timeStamp_ = timeStamp;
    }
    void SetPhase(CoastingAxisPhase phase)
    {
        phase_ = phase;
    }
    CoastingAxisPhase GetPhase() const
    {
        return phase_;
    }
    bool IsStopPropagation() const
    {
        return stopPropagation_;
    }
    void SetStopPropagation(bool stopPropagation)
    {
        stopPropagation_ = stopPropagation;
    }
    float GetHorizontalAxis() const
    {
        return horizontalAxis_;
    }
    float GetVerticalAxis() const
    {
        return verticalAxis_;
    }
    void SetHorizontalAxis(float axis)
    {
        horizontalAxis_ = axis;
    }
    void SetVerticalAxis(float axis)
    {
        verticalAxis_ = axis;
    }

private:
    TimeStamp timeStamp_;
    float horizontalAxis_ = 0.0;
    float verticalAxis_ = 0.0;
    CoastingAxisPhase phase_ = CoastingAxisPhase::NONE;
    bool stopPropagation_ = true;
};

using OnAxisEventFunc = std::function<void(AxisInfo&)>;
using OnCoastingAxisEventFunc = std::function<void(CoastingAxisInfo&)>;
using GetEventTargetImpl = std::function<std::optional<EventTarget>()>;

class AxisEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(AxisEventTarget, AceType);

public:
    AxisEventTarget() = default;
    AxisEventTarget(std::string frameName) : frameName_(std::move(frameName)) {}
    AxisEventTarget(std::string frameName, int32_t frameId) : frameName_(std::move(frameName)), frameId_(frameId) {}
    ~AxisEventTarget() override = default;
    void SetOnAxisCallback(const OnAxisEventFunc& onAxisCallback);
    void SetCoordinateOffset(const NG::OffsetF& coordinateOffset);
    void SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl);
    std::optional<EventTarget> GetEventTarget() const;
    void SetFrameName(const std::string& frameName);
    std::string GetFrameName() const;
    bool HandleAxisEvent(const AxisEvent& event);
    virtual void HandleEvent(const AxisEvent& event) {}
    int32_t GetFrameId() const
    {
        return frameId_;
    }
    void SetOnCoastingAxisCallback(OnCoastingAxisEventFunc&& onCoastingAxisCallback);
    bool HandleCoastingAxisEvent(CoastingAxisInfo& info);

private:
    OnAxisEventFunc onAxisCallback_;
    OnCoastingAxisEventFunc onCoastingAxisCallback_;
    NG::OffsetF coordinateOffset_;
    GetEventTargetImpl getEventTargetImpl_;
    std::string frameName_ = "Unknown";
    int32_t frameId_ = 0;
};

class AxisEventChecker final {
public:
    // check if we are receiving axis event in correct sequence
    // for generic axis event, the correct sequence is begin/update.../end
    // for other axis event, just update, so no need to check
    // return true for no error, false for wrong sequence situation
    bool IsAxisEventSequenceCorrect(const AxisEvent& event);
    AxisAction GetPreAction() const;
private:
    bool IsGenericAxisEventSequenceCorrect(const AxisEvent& event);
    AxisAction preActionOld_ = AxisAction::NONE;
    AxisAction preActionNew_ = AxisAction::NONE;
};

using AxisTestResult = std::list<RefPtr<AxisEventTarget>>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H