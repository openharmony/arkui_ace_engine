/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_TOUCH_EVENT_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_TOUCH_EVENT_H

#include <utility>

#include "ui/base/geometry/offset.h"
#include "ui/base/ace_type.h"
#include "ui/event/event_constants.h"
#include "ui/event/ace_events.h"
#include "ui/event/axis_event.h"

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace::NG {
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

struct TouchPoint final {
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    double globalDisplayX = 0.0;
    double globalDisplayY = 0.0;
    TimeStamp downTime;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    std::optional<float> rollAngle;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    bool isPressed = false;
    int32_t originalId = 0;
    int32_t width;
    int32_t height;
    int32_t operatingHand = 0;
    int32_t xReverse = 0;
    int32_t yReverse = 0;
    void CovertId();
    int32_t GetOriginalReCovertId() const;
};

/**
 * @brief TouchEvent contains the active change point and a list of all touch points.
 */
struct TouchEvent final : public PointerEvent {
    ~TouchEvent() = default;
    // historical points
    std::vector<TouchEvent> history;
    std::vector<KeyCode> pressedKeyCodes_;
    std::list<std::string> childTouchTestList;
    // all points on the touch screen.
    std::vector<TouchPoint> pointers;
    std::shared_ptr<const MMI::PointerEvent> pointerEvent { nullptr };
    double size = 0.0;
    int64_t deviceId = 0;
    uint64_t modifierKeyState = 0;
    TimeStamp pressedTime;
    TouchType type = TouchType::UNKNOWN;
    TouchType pullType = TouchType::UNKNOWN;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    std::optional<float> rollAngle;
    // the active changed point info
    // The ID is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t id = 0;
    float force = 0.0f;
    int32_t targetDisplayId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    int32_t touchEventId = 0;
    int32_t operatingHand = 0;
    // Coordinates relative to the upper-left corner of the current component
    float localX = 0.0f;
    float localY = 0.0f;
    int32_t originalId = 0;
    // Save historical touch point slope.
    float inputXDeltaSlope = 0.0f;
    float inputYDeltaSlope = 0.0f;
    int32_t width = 0;
    int32_t height = 0;
    float targetPositionX = 0.0;
    float targetPositionY = 0.0;
    float targetGlobalPositionX = 0.0;
    float targetGlobalPositionY = 0.0;
    float widthArea = 0.0;
    float heightArea = 0.0;
    bool isInterpolated = false;
    bool isMouseTouchTest = false;
    bool isFalsified = false;
    bool isInjected = false;
    bool isPrivacyMode = false;
    bool isPassThroughMode = false;
    int32_t xReverse = 0;
    int32_t yReverse = 0;
    TouchEvent()
    {
        eventType = UIInputEventType::TOUCH;
    }
    TouchEvent& SetId(int32_t id);
    TouchEvent& SetX(float x);
    TouchEvent& SetY(float y);
    TouchEvent& SetScreenX(float screenX);
    TouchEvent& SetScreenY(float screenY);
    TouchEvent& SetGlobalDisplayX(double globalDisplayX);
    TouchEvent& SetGlobalDisplayY(double globalDisplayY);
    TouchEvent& SetTime(TimeStamp time);
    TimeStamp GetTimeStamp() const;
    TouchEvent& SetType(TouchType type);
    TouchEvent& SetPullType(TouchType pullType);
    TouchEvent& SetSize(double size);
    TouchEvent& SetForce(float force);
    TouchEvent& SetTiltX(std::optional<float> tiltX);
    TouchEvent& SetTiltY(std::optional<float> tiltY);
    TouchEvent& SetRollAngle(std::optional<float> rollAngle);
    TouchEvent& SetDeviceId(int64_t deviceId);
    TouchEvent& SetTargetDisplayId(int32_t targetDisplayId);
    TouchEvent& SetSourceType(SourceType sourceType);
    TouchEvent& SetSourceTool(SourceTool sourceTool);
    TouchEvent& SetTouchEventId(int32_t touchEventId);
    TouchEvent& SetIsInterpolated(bool isInterpolated);
    TouchEvent& SetPointers(std::vector<TouchPoint> pointers);
    TouchEvent& SetPointerEvent(std::shared_ptr<const MMI::PointerEvent> pointerEvent);
    TouchEvent& SetOriginalId(int32_t originalId);
    TouchEvent& SetIsInjected(bool isInjected);
    TouchEvent& SetInputXDeltaSlope(float inputXDeltaSlope);
    TouchEvent& SetInputYDeltaSlope(float inputYDeltaSlope);
    TouchEvent& SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes);
    TouchEvent& SetIsPassThroughMode(bool isPassThroughMode);
    TouchEvent& SetPressedTime(TimeStamp pressedTime);
    TouchEvent& SetWidth(int32_t width);
    TouchEvent& SetHeight(int32_t height);
    TouchEvent& SetOperatingHand(int32_t operatingHand);
    TouchEvent& SetXReverse(int32_t xReverse);
    TouchEvent& SetYReverse(int32_t yReverse);
    TouchEvent CloneWith(float scale) const;
    TouchEvent CloneWith(float scale, float offsetX, float offsetY, std::optional<int32_t> pointId) const;
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const;
    void FromJson(const std::unique_ptr<JsonValue>& json);
    Offset GetOffset() const;
    Offset GetScreenOffset() const;
    Offset GetGlobalDisplayOffset() const;
    int32_t GetTargetDisplayId() const;
    void CovertId();
    int32_t GetOriginalReCovertId() const;
    TouchEvent CreateScalePoint(float scale) const;
    TouchEvent UpdateScalePoint(float scale, float offsetX, float offsetY, int32_t pointId) const;
    TouchEvent UpdatePointers() const;
    bool IsPenHoverEvent() const;
    std::shared_ptr<MMI::PointerEvent> GetTouchEventPointerEvent() const;
    int32_t GetEventIdentity() const;
    bool ConvertFromMouse() const;
};

class ACE_FORCE_EXPORT TouchLocationInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchLocationInfo, TypeInfoBase);

public:
    explicit TouchLocationInfo(int32_t fingerId) : BaseEventInfo("default")
    {
        fingerId_ = fingerId;
    }
    explicit TouchLocationInfo(const std::string& type, int32_t fingerId) : BaseEventInfo(type)
    {
        fingerId_ = fingerId;
    }
    ~TouchLocationInfo() override = default;
    TouchLocationInfo& SetGlobalLocation(const Offset& globalLocation);
    TouchLocationInfo& SetLocalLocation(const Offset& localLocation);
    TouchLocationInfo& SetScreenLocation(const Offset& screenLocation);
    TouchLocationInfo& SetGlobalDisplayLocation(const Offset& globalDisplayLocation);
    const Offset& GetGlobalDisplayLocation() const
    {
        return globalDisplayLocation_;
    }
    const Offset& GetScreenLocation() const
    {
        return screenLocation_;
    }
    const Offset& GetLocalLocation() const
    {
        return localLocation_;
    }
    const Offset& GetGlobalLocation() const
    {
        return globalLocation_;
    }
    int32_t GetFingerId() const
    {
        return fingerId_;
    }
    void SetSize(double size);
    double GetSize() const;
    void SetTouchDeviceId(int64_t deviceId);
    int64_t GetTouchDeviceId() const;
    TouchType GetTouchType() const
    {
        return touchType_;
    }
    void SetTouchType(TouchType type);

    void SetPressedTime(TimeStamp pressedTime);
    TimeStamp GetPressedTime() const;
    void SetWidth(int32_t width);
    int32_t GetWidth() const;
    void SetHeight(int32_t height);
    int32_t GetHeight() const;

private:
    // The finger id is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t fingerId_ = -1;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
    Offset screenLocation_;
    // The location where the touch point touches the screen when there are multiple screens.
    Offset globalDisplayLocation_;
    // finger touch size
    double size_ = 0.0;
    // input device id
    int64_t touchDeviceId_ = 0;
    // touch type
    TouchType touchType_ = TouchType::UNKNOWN;
    TimeStamp pressedTime_;
    int32_t width_ = 0;
    int32_t height_ = 0;
};

class ACE_FORCE_EXPORT TouchEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchEventInfo, BaseEventInfo);

public:
    explicit TouchEventInfo(const std::string& type) : BaseEventInfo(type) {}
    ~TouchEventInfo() override = default;
    void AddTouchLocationInfo(TouchLocationInfo&& info);
    void AddChangedTouchLocationInfo(TouchLocationInfo&& info);
    void AddHistoryLocationInfo(TouchLocationInfo&& info);
    const std::list<TouchLocationInfo>& GetTouches() const
    {
        return touches_;
    }
    const std::list<TouchLocationInfo>& GetChangedTouches() const
    {
        return changedTouches_;
    }

    // use for ArkTs1.2 interop
    void SetTouches(const std::list<TouchLocationInfo>& touches)
    {
        touches_ = touches;
    }
    void SetChangedTouches(const std::list<TouchLocationInfo>& changedTouches)
    {
        changedTouches_ = changedTouches;
    }
    const std::list<TouchLocationInfo>& GetHistory() const;
    void AddHistoryPointerEvent(const std::shared_ptr<MMI::PointerEvent>& info);
    const std::list<std::shared_ptr<MMI::PointerEvent>>& GetHistoryPointerEvent() const;
    void SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    const std::shared_ptr<MMI::PointerEvent>& GetPointerEvent() const;
    void SetTouchEventsEnd(bool isTouchEventsEnd);
    bool GetTouchEventsEnd() const;
    TouchEvent ConvertToTouchEvent() const;

private:
    std::shared_ptr<MMI::PointerEvent> pointerEvent_;
    std::list<TouchLocationInfo> touches_;
    std::list<TouchLocationInfo> changedTouches_;
    std::list<TouchLocationInfo> history_;
    std::list<std::shared_ptr<MMI::PointerEvent>> historyPointerEvent_;
    bool isTouchEventsEnd_ { false };
};

using TouchEventFunc = std::function<void(TouchEventInfo&)>;
using OnTouchEventCallback = std::function<void(const TouchEventInfo&)>;
using CatchTouchEventCallback = std::function<void()>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_TOUCH_EVENT_H
