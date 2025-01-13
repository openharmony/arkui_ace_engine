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

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {
struct UIInputEvent {
    virtual ~UIInputEvent() = default;
    TimeStamp time;
    UIInputEventType eventType = UIInputEventType::NONE;
};

struct PointerEvent : public UIInputEvent {
    virtual ~PointerEvent() = default;
    explicit PointerEvent(float x = {}, float y = {}, float screenX = {},
        float screenY = {}, TimeStamp time = {})
        :x(x), y(y), screenX(screenX), screenY(screenY)
    {
        this->time = time;
    }
    float x = {};
    float y = {};
    float screenX = {};
    float screenY = {};
};

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

    AxisEvent()
    {
        eventType = UIInputEventType::AXIS;
    }

    AxisEvent(int32_t id, float x, float y, float screenX, float screenY, double verticalAxis, double horizontalAxis,
        double pinchAxisScale, double rotateAxisAngle, bool isRotationEvent, AxisAction action, TimeStamp timestamp,
        int64_t deviceId, SourceType sourceType, SourceTool sourceTool,
        std::shared_ptr<const MMI::PointerEvent> pointerEvent, std::vector<KeyCode> pressedCodes,
        int32_t targetDisplayId, int32_t originalId, bool isInjected)
        : PointerEvent(x, y, screenX, screenY, timestamp), id(id), verticalAxis(verticalAxis),
          horizontalAxis(horizontalAxis), pinchAxisScale(pinchAxisScale), rotateAxisAngle(rotateAxisAngle),
          isRotationEvent(isRotationEvent), action(action), deviceId(deviceId), sourceType(sourceType),
          sourceTool(sourceTool), pointerEvent(std::move(pointerEvent)), pressedCodes(pressedCodes),
          targetDisplayId(targetDisplayId), originalId(originalId), isInjected(isInjected)
    {
        eventType = UIInputEventType::AXIS;
    }

    AxisEvent CreateScaleEvent(float scale) const;
    Offset GetOffset() const;
    Offset GetScreenOffset() const;
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
    void SetVerticalAxis(float axis);
    float GetVerticalAxis() const;
    void SetHorizontalAxis(float axis);
    float GetHorizontalAxis() const;
    void SetPinchAxisScale(float scale);
    float GetPinchAxisScale() const;
    void SetRotateAxisAngle(float angle);
    float GetRotateAxisAngle() const;
    void SetIsRotationEvent(bool rotationFlag);
    bool GetIsRotationEvent() const;
    AxisInfo& SetGlobalLocation(const Offset& globalLocation);
    AxisInfo& SetLocalLocation(const Offset& localLocation);
    AxisInfo& SetScreenLocation(const Offset& screenLocation);
    const Offset& GetScreenLocation() const;
    const Offset& GetLocalLocation() const;
    const Offset& GetGlobalLocation() const;
    AxisEvent ConvertToAxisEvent() const;

private:
    AxisAction action_ = AxisAction::NONE;
    float verticalAxis_ = 0.0;
    float horizontalAxis_ = 0.0;
    float pinchAxisScale_ = 0.0;
    float rotateAxisAngle_ = 0.0;
    bool isRotationEvent_ = false;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
    Offset screenLocation_;
};

using OnAxisEventFunc = std::function<void(AxisInfo&)>;
using GetEventTargetImpl = std::function<std::optional<EventTarget>()>;

class AxisEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(AxisEventTarget, AceType);

public:
    AxisEventTarget() = default;
    AxisEventTarget(std::string frameName) : frameName_(std::move(frameName)) {}
    ~AxisEventTarget() override = default;
    void SetOnAxisCallback(const OnAxisEventFunc& onAxisCallback);
    void SetCoordinateOffset(const NG::OffsetF& coordinateOffset);
    void SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl);
    std::optional<EventTarget> GetEventTarget() const;
    void SetFrameName(const std::string& frameName);
    std::string GetFrameName() const;
    bool HandleAxisEvent(const AxisEvent& event);
    virtual void HandleEvent(const AxisEvent& event) {}

private:
    OnAxisEventFunc onAxisCallback_;
    NG::OffsetF coordinateOffset_;
    GetEventTargetImpl getEventTargetImpl_;
    std::string frameName_ = "Unknown";
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