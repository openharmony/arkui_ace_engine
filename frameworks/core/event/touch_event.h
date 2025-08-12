/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H

#include <utility>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/utils/time_util.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components_ng/event/target_component.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"

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
    int32_t operatingHand = 0;
    int32_t width;
    int32_t height;

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
};

namespace Platform {
ACE_FORCE_EXPORT Offset GetTouchEventOriginOffset(const TouchEvent& event);
ACE_FORCE_EXPORT TimeStamp GetTouchEventOriginTimeStamp(const TouchEvent& event);
ACE_FORCE_EXPORT void UpdatePressedKeyCodes(std::vector<KeyCode>& pressedKeyCodes);
} // namespace Platform

struct TouchRestrict final {
    static constexpr uint32_t NONE = 0x00000000;
    static constexpr uint32_t CLICK = 0x00000001;
    static constexpr uint32_t LONG_PRESS = 0x00000010;
    static constexpr uint32_t SWIPE_LEFT = 0x00000100;
    static constexpr uint32_t SWIPE_RIGHT = 0x00000200;
    static constexpr uint32_t SWIPE_UP = 0x00000400;
    static constexpr uint32_t SWIPE_DOWN = 0x00000800;
    static constexpr uint32_t SWIPE = 0x00000F00;
    static constexpr uint32_t SWIPE_VERTICAL = 0x0000C00;   // Vertical
    static constexpr uint32_t SWIPE_HORIZONTAL = 0x0000300; // Horizontal
    static constexpr uint32_t TOUCH = 0xFFFFFFFF;
    uint32_t forbiddenType = NONE;

    void UpdateForbiddenType(uint32_t gestureType)
    {
        forbiddenType |= gestureType;
    }
    TouchEvent touchEvent = {};
    std::list<std::string> childTouchTestList = {};
    SourceType sourceType = SourceType::NONE;
    SourceType hitTestType = SourceType::TOUCH;
    InputEventType inputEventType = InputEventType::TOUCH_SCREEN;
    // use to dump event tree
    NG::EventTreeType touchTestType = NG::EventTreeType::TOUCH;
};

class TouchCallBackInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchCallBackInfo, BaseEventInfo);

public:
    explicit TouchCallBackInfo(TouchType type) : BaseEventInfo("onTouchEvent"), touchType_(type) {}
    ~TouchCallBackInfo() override = default;

    void SetScreenX(float screenX);
    float GetScreenX() const;
    void SetScreenY(float screenY);
    float GetScreenY() const;
    void SetGlobalDisplayX(double globalDisplayX);
    double GetGlobalDisplayX() const;
    void SetGlobalDisplayY(double globalDisplayY);
    double GetGlobalDisplayY() const;
    void SetLocalX(float localX);
    float GetLocalX() const;
    void SetLocalY(float localY);
    float GetLocalY() const;
    void SetTouchType(TouchType type);
    TouchType GetTouchType() const;
    void SetTimeStamp(const TimeStamp& time);
    TimeStamp GetTimeStamp() const;

private:
    double globalDisplayX_ = 0.0;
    double globalDisplayY_ = 0.0;
    float screenX_ = 0.0f;
    float screenY_ = 0.0f;
    float localX_ = 0.0f;
    float localY_ = 0.0f;
    TouchType touchType_ = TouchType::UNKNOWN;
    TimeStamp time_;
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

using GetEventTargetImpl = std::function<std::optional<EventTarget>()>;

struct StateRecord {
    std::string procedure;
    std::string extraInfo;
    std::string state;
    std::string disposal;
    int64_t timestamp = 0;

    StateRecord(const std::string& procedure, const std::string& extraInfo, const std::string& state,
        const std::string& disposal, int64_t timestamp) : procedure(procedure), extraInfo(extraInfo),
        state(state), disposal(disposal), timestamp(timestamp)
    {}
    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    void Dump(std::unique_ptr<JsonValue>& json) const;
};

struct GestureSnapshot : public virtual AceType {
    DECLARE_ACE_TYPE(GestureSnapshot, AceType);

public:
    void AddProcedure(const std::string& procedure, const std::string& extraInfo,
        const std::string& state, const std::string& disposal, int64_t timestamp);
    bool CheckNeedAddMove(const std::string& state, const std::string& disposal);
    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const;
    static std::string TransTouchType(TouchType type);
    static std::string TransAxisType(AxisAction action);
    std::tuple<std::string, std::string> GetIds() const;
    void Dump(std::unique_ptr<JsonValue>& json) const;

    int32_t nodeId = -1;
    std::string type;
    uint64_t id = 0;
    uint64_t parentId = 0;
    int32_t depth = 0;
    std::string customInfo;
    std::list<StateRecord> stateHistory;
};

class ACE_FORCE_EXPORT TouchEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(TouchEventTarget, AceType);

public:
    TouchEventTarget() = default;
    TouchEventTarget(std::string nodeName, int32_t nodeId) : nodeName_(std::move(nodeName)), nodeId_(nodeId) {}
    ~TouchEventTarget() override = default;

    // if return false means need to stop event dispatch.
    virtual bool DispatchEvent(const TouchEvent& point) = 0;
    // if return false means need to stop event bubbling.
    virtual bool HandleEvent(const TouchEvent& point) = 0;
    virtual bool HandleEvent(const AxisEvent& event)
    {
        return true;
    }
    virtual void OnFlushTouchEventsBegin() {}
    virtual void OnFlushTouchEventsEnd() {}
    virtual Axis GetAxisDirection()
    {
        return direction_;
    }
    void SetTouchRestrict(const TouchRestrict& touchRestrict);
    void SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl);
    std::optional<EventTarget> GetEventTarget() const;
    // Coordinate offset is used to calculate the local location of the touch point in the render node.
    void SetCoordinateOffset(const Offset& coordinateOffset);
    // Gets the coordinate offset to calculate the local location of the touch point by manually.
    const Offset& GetCoordinateOffset() const;
    void SetSubPipelineGlobalOffset(const Offset& subPipelineGlobalOffset, float viewScale);
    bool DispatchMultiContainerEvent(const TouchEvent& point);
    bool HandleMultiContainerEvent(const TouchEvent& point);
    std::string GetNodeName() const;
    void SetNodeId(int id);
    int32_t GetNodeId() const;
    virtual void AttachFrameNode(const WeakPtr<NG::FrameNode>& node);
    WeakPtr<NG::FrameNode> GetAttachedNode() const;
    virtual RefPtr<GestureSnapshot> Dump() const;
    void SetTargetComponent(const RefPtr<NG::TargetComponent>& targetComponent);
    RefPtr<NG::TargetComponent> GetTargetComponent();
    void SetIsPostEventResult(bool isPostEventResult);
    bool IsPostEventResult() const;

private:
    virtual bool ShouldResponse()
    {
        return true;
    };

protected:
    Offset coordinateOffset_;
    GetEventTargetImpl getEventTargetImpl_;
    TouchRestrict touchRestrict_ { TouchRestrict::NONE };
    Offset subPipelineGlobalOffset_;
    float viewScale_ = 1.0f;
    std::string nodeName_ = "NULL";
    int32_t nodeId_ = -1;
    WeakPtr<NG::FrameNode> node_ = nullptr;
    Axis direction_ = Axis::NONE;
    RefPtr<NG::TargetComponent> targetComponent_;
    bool isPostEventResult_ = false;
    std::optional<TimeStamp> firstInputTime_;
};

using TouchTestResult = std::list<RefPtr<TouchEventTarget>>;
using ResponseLinkResult = std::list<RefPtr<NG::NGGestureRecognizer>>;

class TouchEventInfo : public BaseEventInfo {
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

class ACE_EXPORT GestureEventResult : public AceType {
    DECLARE_ACE_TYPE(GestureEventResult, AceType)

public:
    GestureEventResult() = default;
    ~GestureEventResult() = default;

    virtual void SetGestureEventResult(bool result) = 0;
    virtual void SetGestureEventResult(bool result, bool stopPropagation) = 0;
};

class NativeEmbeadTouchInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(NativeEmbeadTouchInfo, BaseEventInfo);

public:
    NativeEmbeadTouchInfo(
        const std::string& embedId, const TouchEventInfo& touchEventInfo, const RefPtr<GestureEventResult>& result)
        : BaseEventInfo("NativeEmbeadTouchInfo"), embedId_(embedId), touchEvent_(touchEventInfo), result_(result)
    {}
    ~NativeEmbeadTouchInfo() override = default;
    const std::string& GetEmbedId() const;
    const TouchEventInfo& GetTouchEventInfo() const;
    const RefPtr<GestureEventResult>& GetResult() const;

private:
    std::string embedId_;
    TouchEventInfo touchEvent_;
    RefPtr<GestureEventResult> result_;
};

using TouchEventFunc = std::function<void(TouchEventInfo&)>;
using OnTouchEventCallback = std::function<void(const TouchEventInfo&)>;
using CatchTouchEventCallback = std::function<void()>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H
