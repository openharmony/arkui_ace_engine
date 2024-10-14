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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_TOUCH_EVENT_H

#include <list>
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

static const int32_t TOUCH_TOOL_BASE_ID = 100;

enum class TouchType : size_t {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    PULL_DOWN,
    PULL_UP,
    PULL_MOVE,
    PULL_IN_WINDOW,
    PULL_OUT_WINDOW,
    HOVER_ENTER,
    HOVER_MOVE,
    HOVER_EXIT,
    HOVER_CANCEL,
    PROXIMITY_IN,
    PROXIMITY_OUT,
    UNKNOWN,
};

struct TouchPoint final {
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    TimeStamp downTime;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    bool isPressed = false;
    int32_t originalId = 0;
};

/**
 * @brief TouchEvent contains the active change point and a list of all touch points.
 */
struct TouchEvent final : public UIInputEvent {
    ~TouchEvent() = default;
    // the active changed point info
    // The ID is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t postEventNodeId = 0;
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    TouchType type = TouchType::UNKNOWN;
    TouchType pullType = TouchType::UNKNOWN;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    int64_t deviceId = 0;
    int32_t targetDisplayId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    int32_t touchEventId = 0;
    bool isInterpolated = false;
    bool isMouseTouchTest = false;
    bool isFalsified = false;

    // all points on the touch screen.
    std::vector<TouchPoint> pointers;
    std::shared_ptr<MMI::PointerEvent> pointerEvent { nullptr };
    // historical points
    std::vector<TouchEvent> history;
    std::vector<KeyCode> pressedKeyCodes_;

    std::list<std::string> childTouchTestList;

    // Coordinates relative to the upper-left corner of the current component
    float localX = 0.0f;
    float localY = 0.0f;
    int32_t originalId = 0;
    bool isInjected = false;
    bool isPrivacyMode = false;

    // Save historical touch point slope.
    float inputXDeltaSlope = 0.0f;
    float inputYDeltaSlope = 0.0f;

    TouchEvent() {}

    TouchEvent& SetId(int32_t id)
    {
        this->id = id;
        return *this;
    }

    TouchEvent& SetX(float x)
    {
        this->x = x;
        return *this;
    }

    TouchEvent& SetY(float y)
    {
        this->y = y;
        return *this;
    }

    TouchEvent& SetScreenX(float screenX)
    {
        this->screenX = screenX;
        return *this;
    }

    TouchEvent& SetScreenY(float screenY)
    {
        this->screenY = screenY;
        return *this;
    }

    TouchEvent& SetTime(TimeStamp time)
    {
        this->time = time;
        return *this;
    }

    TimeStamp GetTimeStamp() const
    {
        return this->time;
    }

    TouchEvent& SetType(TouchType type)
    {
        this->type = type;
        return *this;
    }

    TouchEvent& SetPullType(TouchType pullType)
    {
        this->pullType = pullType;
        return *this;
    }

    TouchEvent& SetSize(double size)
    {
        this->size = size;
        return *this;
    }

    TouchEvent& SetForce(float force)
    {
        this->force = force;
        return *this;
    }

    TouchEvent& SetTiltX(std::optional<float> tiltX)
    {
        this->tiltX = tiltX;
        return *this;
    }

    TouchEvent& SetTiltY(std::optional<float> tiltY)
    {
        this->tiltY = tiltY;
        return *this;
    }

    TouchEvent& SetDeviceId(int64_t deviceId)
    {
        this->deviceId = deviceId;
        return *this;
    }

    TouchEvent& SetTargetDisplayId(int32_t targetDisplayId)
    {
        this->targetDisplayId = targetDisplayId;
        return *this;
    }

    TouchEvent& SetSourceType(SourceType sourceType)
    {
        this->sourceType = sourceType;
        return *this;
    }

    TouchEvent& SetSourceTool(SourceTool sourceTool)
    {
        this->sourceTool = sourceTool;
        return *this;
    }

    TouchEvent& SetTouchEventId(int32_t touchEventId)
    {
        this->touchEventId = touchEventId;
        return *this;
    }

    TouchEvent& SetIsInterpolated(bool isInterpolated)
    {
        this->isInterpolated = isInterpolated;
        return *this;
    }

    TouchEvent& SetPointers(std::vector<TouchPoint> pointers)
    {
        this->pointers = std::move(pointers);
        return *this;
    }

    TouchEvent& SetPointerEvent(std::shared_ptr<MMI::PointerEvent> pointerEvent)
    {
        this->pointerEvent = std::move(pointerEvent);
        return *this;
    }

    TouchEvent& SetOriginalId(int32_t originalId)
    {
        this->originalId = originalId;
        return *this;
    }

    TouchEvent& SetIsInjected(bool isInjected)
    {
        this->isInjected = isInjected;
        return *this;
    }

    TouchEvent& SetInputXDeltaSlope(float inputXDeltaSlope)
    {
        this->inputXDeltaSlope = inputXDeltaSlope;
        return *this;
    }

    TouchEvent& SetInputYDeltaSlope(float inputYDeltaSlope)
    {
        this->inputYDeltaSlope = inputYDeltaSlope;
        return *this;
    }

    TouchEvent& SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        this->pressedKeyCodes_ = pressedKeyCodes;
        return *this;
    }

    TouchEvent CloneWith(float scale) const
    {
        return CloneWith(scale, 0.0f, 0.0f, std::nullopt);
    }

    TouchEvent CloneWith(float scale, float offsetX, float offsetY, std::optional<int32_t> pointId) const
    {
        TouchEvent event;
        event.id = pointId.has_value() ? pointId.value() : id;
        event.x = (x - offsetX) / scale;
        event.y = (y - offsetY) / scale;
        event.screenX = (screenX - offsetX) / scale;
        event.screenY = (screenY - offsetY) / scale;
        event.type = type;
        event.pullType = pullType;
        event.time = time;
        event.size = size;
        event.force = force;
        event.tiltX = tiltX;
        event.tiltY = tiltY;
        event.deviceId = deviceId;
        event.targetDisplayId = targetDisplayId;
        event.sourceType = sourceType;
        event.sourceTool = sourceTool;
        event.touchEventId = touchEventId;
        event.isInterpolated = isInterpolated;
        event.pointers = std::move(pointers);
        event.pointerEvent = std::move(pointerEvent);
        event.originalId = originalId;
        event.pressedKeyCodes_ = pressedKeyCodes_;
        event.isInjected = isInjected;
        event.isPrivacyMode = isPrivacyMode;
        event.inputXDeltaSlope = inputXDeltaSlope;
        event.inputYDeltaSlope = inputYDeltaSlope;
        return event;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("id", id);
        json->Put("x", x);
        json->Put("y", y);
        json->Put("sx", screenX);
        json->Put("sy", screenY);
        json->Put("ty", static_cast<int32_t>(type));
        int64_t timeValue = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()).count();
        json->Put("ti", timeValue);
        json->Put("si", size);
        json->Put("f", force);
        int32_t hasTiltX = tiltX.has_value() ? 1 : 0;
        json->Put("hx", hasTiltX);
        if (hasTiltX) {
            json->Put("tx", tiltX.value());
        }
        int32_t hasTiltY = tiltY.has_value() ? 1 : 0;
        json->Put("hy", hasTiltY);
        if (tiltY.has_value()) {
            json->Put("ty", tiltY.value());
        }
        json->Put("d", deviceId);
        json->Put("sty", static_cast<int32_t>(sourceType));
        json->Put("sto", static_cast<int32_t>(sourceTool));
    }

    void FromJson(const std::unique_ptr<JsonValue>& json)
    {
        id = json->GetInt("id");
        x = json->GetDouble("x");
        y = json->GetDouble("y");
        screenX = json->GetDouble("sx");
        screenY = json->GetDouble("sy");
        type = static_cast<TouchType>(json->GetInt("ty"));
        int64_t timeValue = json->GetInt64("ti");
        time = TimeStamp(std::chrono::nanoseconds(timeValue));
        size = json->GetDouble("si");
        force = json->GetDouble("f");
        int32_t hasTiltX = json->GetInt("hx");
        int32_t hasTiltY = json->GetInt("hy");
        if (hasTiltX) {
            tiltX = json->GetDouble("tx");
        }
        if (hasTiltY) {
            tiltY = json->GetDouble("ty");
        }
        deviceId = json->GetInt64("d");
        sourceType = static_cast<SourceType>(json->GetInt("sty"));
        sourceTool = static_cast<SourceTool>(json->GetInt("sto"));
    }

    Offset GetOffset() const
    {
        return Offset(x, y);
    }

    Offset GetScreenOffset() const
    {
        return Offset(screenX, screenY);
    }

    void CovertId()
    {
        if ((sourceType == SourceType::TOUCH) && (sourceTool == SourceTool::PEN)) {
            id = id + TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
            originalId = TOUCH_TOOL_BASE_ID + static_cast<int32_t>(sourceTool);
        }
    }

    TouchEvent CreateScalePoint(float scale) const
    {
        if (NearZero(scale)) {
            return CloneWith(1);
        }
        auto temp = pointers;
        std::for_each(temp.begin(), temp.end(), [scale](auto&& point) {
            point.x = point.x / scale;
            point.y = point.y / scale;
            point.screenX = point.screenX / scale;
            point.screenY = point.screenY / scale;
        });
        return CloneWith(scale);
    }

    TouchEvent UpdateScalePoint(float scale, float offsetX, float offsetY, int32_t pointId) const
    {
        auto temp = pointers;
        if (NearZero(scale)) {
            std::for_each(temp.begin(), temp.end(), [offsetX, offsetY](auto&& point) {
                point.x = point.x - offsetX;
                point.y = point.y - offsetY;
                point.screenX = point.screenX - offsetX;
                point.screenY = point.screenY - offsetY;
            });
            return CloneWith(1, offsetX, offsetY, pointId);
        }

        std::for_each(temp.begin(), temp.end(), [scale, offsetX, offsetY](auto&& point) {
            point.x = (point.x - offsetX) / scale;
            point.y = (point.y - offsetY) / scale;
            point.screenX = (point.screenX - offsetX) / scale;
            point.screenY = (point.screenY - offsetY) / scale;
        });
        return CloneWith(scale, offsetX, offsetY, pointId);
    }

    TouchEvent UpdatePointers() const
    {
        TouchPoint point { .id = id,
            .x = x,
            .y = y,
            .screenX = screenX,
            .screenY = screenY,
            .downTime = time,
            .size = size,
            .force = force,
            .isPressed = (type == TouchType::DOWN) };
        TouchEvent event;
        event.SetId(id)
            .SetX(x)
            .SetY(y)
            .SetScreenX(screenX)
            .SetScreenY(screenY)
            .SetType(type)
            .SetTime(time)
            .SetSize(size)
            .SetForce(force)
            .SetDeviceId(deviceId)
            .SetTargetDisplayId(targetDisplayId)
            .SetSourceType(sourceType)
            .SetIsInterpolated(isInterpolated)
            .SetPointerEvent(pointerEvent)
            .SetOriginalId(originalId);
        event.pointers.emplace_back(std::move(point));
        return event;
    }

    bool IsPenHoverEvent() const
    {
        return sourceTool == SourceTool::PEN && (type == TouchType::PROXIMITY_IN ||
        type == TouchType::PROXIMITY_OUT || (type == TouchType::MOVE && NearZero(force)));
    }
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
    SourceType sourceType = SourceType::NONE;

    SourceType hitTestType = SourceType::TOUCH;

    InputEventType inputEventType = InputEventType::TOUCH_SCREEN;

    TouchEvent touchEvent;

    std::list<std::string> childTouchTestList;

    // use to dump event tree
    NG::EventTreeType touchTestType = NG::EventTreeType::TOUCH;
};

class TouchCallBackInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchCallBackInfo, BaseEventInfo);

public:
    explicit TouchCallBackInfo(TouchType type) : BaseEventInfo("onTouchEvent"), touchType_(type) {}
    ~TouchCallBackInfo() override = default;

    void SetScreenX(float screenX)
    {
        screenX_ = screenX;
    }
    float GetScreenX() const
    {
        return screenX_;
    }
    void SetScreenY(float screenY)
    {
        screenY_ = screenY;
    }
    float GetScreenY() const
    {
        return screenY_;
    }
    void SetLocalX(float localX)
    {
        localX_ = localX;
    }
    float GetLocalX() const
    {
        return localX_;
    }
    void SetLocalY(float localY)
    {
        localY_ = localY;
    }
    float GetLocalY() const
    {
        return localY_;
    }
    void SetTouchType(TouchType type)
    {
        touchType_ = type;
    }
    TouchType GetTouchType() const
    {
        return touchType_;
    }
    void SetTimeStamp(const TimeStamp& time)
    {
        time_ = time;
    }
    TimeStamp GetTimeStamp() const
    {
        return time_;
    }

private:
    float screenX_ = 0.0f;
    float screenY_ = 0.0f;
    float localX_ = 0.0f;
    float localY_ = 0.0f;
    TouchType touchType_ = TouchType::UNKNOWN;
    TimeStamp time_;
};

class TouchLocationInfo : public BaseEventInfo {
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

    TouchLocationInfo& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        return *this;
    }
    TouchLocationInfo& SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
        return *this;
    }

    TouchLocationInfo& SetScreenLocation(const Offset& screenLocation)
    {
        screenLocation_ = screenLocation;
        return *this;
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

    void SetSize(double size)
    {
        size_ = size;
    }

    double GetSize() const
    {
        return size_;
    }

    void SetTouchDeviceId(int64_t deviceId)
    {
        touchDeviceId_ = deviceId;
    }

    int64_t GetTouchDeviceId() const
    {
        return touchDeviceId_;
    }

    TouchType GetTouchType() const
    {
        return touchType_;
    }
    void SetTouchType(TouchType type)
    {
        touchType_ = type;
    }

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

    // finger touch size
    double size_ = 0.0;

    // input device id
    int64_t touchDeviceId_ = 0;

    // touch type
    TouchType touchType_ = TouchType::UNKNOWN;
};

using GetEventTargetImpl = std::function<std::optional<EventTarget>()>;

struct StateRecord {
    std::string procedure;
    std::string state;
    std::string disposal;
    int64_t timestamp = 0;

    StateRecord(const std::string& procedure, const std::string& state, const std::string& disposal,
        int64_t timestamp):procedure(procedure), state(state), disposal(disposal), timestamp(timestamp)
    {}

    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
    {
        std::stringstream oss;
        oss << "procedure: " << procedure;
        if (!state.empty()) {
            oss << ", " << "state: " << state << ", "
                << "disposal: " << disposal;
        }
        oss << ", " << "timestamp: " << ConvertTimestampToStr(timestamp);
        dumpList.emplace_back(std::make_pair(depth, oss.str()));
    }

    void Dump(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("procedure", procedure.c_str());
        if (!state.empty()) {
            json->Put("state", state.c_str());
            json->Put("disposal", disposal.c_str());
        }
        json->Put("timestamp",  ConvertTimestampToStr(timestamp).c_str());
    }
};

struct GestureSnapshot : public virtual AceType {
    DECLARE_ACE_TYPE(GestureSnapshot, AceType);

public:
    void AddProcedure(const std::string& procedure, const std::string& state, const std::string& disposal,
        int64_t timestamp)
    {
        if (timestamp == 0) {
            timestamp = GetCurrentTimestamp();
        }
        stateHistory.emplace_back(StateRecord(procedure, state, disposal, timestamp));
    }

    bool CheckNeedAddMove(const std::string& state, const std::string& disposal)
    {
        return stateHistory.empty() ||
            stateHistory.back().state != state || stateHistory.back().disposal != disposal;
    }

    void Dump(std::list<std::pair<int32_t, std::string>>& dumpList, int32_t depth) const
    {
        std::stringstream oss;
        oss << "frameNodeId: " << nodeId << ", "
            << "type: " << type << ", "
            << "depth: " << this->depth << ", "
            << std::hex
            << "id: 0x" << id << ", "
            << "parentId: 0x" << parentId;
        if (!customInfo.empty()) {
            oss << ", " << "customInfo: " << customInfo;
        }
        dumpList.emplace_back(std::make_pair(depth + this->depth, oss.str()));
        dumpList.emplace_back(std::make_pair(depth + 1 + this->depth, "stateHistory:"));
        for (const auto& state : stateHistory) {
            state.Dump(dumpList, depth + 1 + 1 + this->depth);
        }
    }

    static std::string TransTouchType(TouchType type)
    {
        switch (type) {
            case TouchType::DOWN:
                return "TouchDown";
            case TouchType::MOVE:
                return "TouchMove";
            case TouchType::UP:
                return "TouchUp";
            case TouchType::CANCEL:
                return "TouchCancel";
            default:
                return std::string("Type:").append(std::to_string(static_cast<int32_t>(type)));
        }
    }

    std::tuple<std::string, std::string> GetIds() const
    {
        std::stringstream oss;
        oss << "0x" << std::hex << id;
        std::string idStr = oss.str();
        oss.str("");
        oss << "0x" << std::hex << parentId;
        std::string parentIdStr = oss.str();
        return std::make_tuple(idStr, parentIdStr);
    }

    void Dump(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("frameNodeId", nodeId);
        json->Put("type", type.c_str());
        auto result = GetIds();
        json->Put("id", std::get<0>(result).c_str());
        json->Put("parentId", std::get<1>(result).c_str());
        json->Put("depth", this->depth);
        if (!customInfo.empty()) {
            json->Put("customInfo", customInfo.c_str());
        }
        std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
        for (const auto& state : stateHistory) {
            std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
            state.Dump(child);
            children->Put(child);
        }
        json->Put("stateHistory", children);
    }

    int32_t nodeId = -1;
    std::string type;
    uint64_t id = 0;
    uint64_t parentId = 0;
    int32_t depth = 0;
    std::string customInfo;
    std::list<StateRecord> stateHistory;
};

class ACE_EXPORT TouchEventTarget : public virtual AceType {
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

    void SetTouchRestrict(const TouchRestrict& touchRestrict)
    {
        touchRestrict_ = touchRestrict;
    }

    void SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl)
    {
        getEventTargetImpl_ = getEventTargetImpl;
    }

    std::optional<EventTarget> GetEventTarget() const
    {
        if (getEventTargetImpl_) {
            return getEventTargetImpl_();
        }
        return std::nullopt;
    }

    // Coordinate offset is used to calculate the local location of the touch point in the render node.
    void SetCoordinateOffset(const Offset& coordinateOffset)
    {
        coordinateOffset_ = coordinateOffset;
    }

    // Gets the coordinate offset to calculate the local location of the touch point by manually.
    const Offset& GetCoordinateOffset() const
    {
        return coordinateOffset_;
    }

    void SetSubPipelineGlobalOffset(const Offset& subPipelineGlobalOffset, float viewScale)
    {
        subPipelineGlobalOffset_ = subPipelineGlobalOffset;
        viewScale_ = viewScale;
    }

    bool DispatchMultiContainerEvent(const TouchEvent& point)
    {
#ifdef OHOS_STANDARD_SYSTEM
        if (!subPipelineGlobalOffset_.IsZero()) {
            auto multiContainerPoint = point.UpdateScalePoint(
                viewScale_, subPipelineGlobalOffset_.GetX(), subPipelineGlobalOffset_.GetY(), point.id);
            return DispatchEvent(multiContainerPoint);
        }
#endif
        return DispatchEvent(point);
    }

    bool HandleMultiContainerEvent(const TouchEvent& point)
    {
#ifdef OHOS_STANDARD_SYSTEM
        if (!subPipelineGlobalOffset_.IsZero()) {
            auto multiContainerPoint = point.UpdateScalePoint(
                viewScale_, subPipelineGlobalOffset_.GetX(), subPipelineGlobalOffset_.GetY(), point.id);
            return HandleEvent(multiContainerPoint);
        }
#endif
        return HandleEvent(point);
    }

    std::string GetNodeName() const
    {
        return nodeName_;
    }

    void SetNodeId(int id)
    {
        if (nodeId_ != -1) {
            return;
        }
        nodeId_ = id;
    }

    int32_t GetNodeId() const
    {
        return nodeId_;
    }

    virtual void AttachFrameNode(const WeakPtr<NG::FrameNode>& node)
    {
        if (!(node_.Invalid())) {
            return;
        }
        node_ = node;
    }

    WeakPtr<NG::FrameNode> GetAttachedNode() const
    {
        return node_;
    }

    virtual RefPtr<GestureSnapshot> Dump() const
    {
        RefPtr<GestureSnapshot> info = AceType::MakeRefPtr<GestureSnapshot>();
        info->type = GetTypeName();
        info->id = reinterpret_cast<uintptr_t>(this);
        return info;
    }

    void SetTargetComponent(const RefPtr<NG::TargetComponent>& targetComponent)
    {
        if (!targetComponent_) {
            targetComponent_ = targetComponent;
        }
    }

    RefPtr<NG::TargetComponent> GetTargetComponent()
    {
        return targetComponent_;
    }

    void SetIsPostEventResult(bool isPostEventResult)
    {
        isPostEventResult_ = isPostEventResult;
    }

    bool IsPostEventResult() const
    {
        return isPostEventResult_;
    }

private:
    virtual bool ShouldResponse() { return true; };

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

    void AddTouchLocationInfo(TouchLocationInfo&& info)
    {
        touches_.emplace_back(info);
    }
    void AddChangedTouchLocationInfo(TouchLocationInfo&& info)
    {
        changedTouches_.emplace_back(info);
    }
    void AddHistoryLocationInfo(TouchLocationInfo&& info)
    {
        history_.emplace_back(std::move(info));
    }

    const std::list<TouchLocationInfo>& GetTouches() const
    {
        return touches_;
    }
    const std::list<TouchLocationInfo>& GetChangedTouches() const
    {
        return changedTouches_;
    }
    const std::list<TouchLocationInfo>& GetHistory() const
    {
        return history_;
    }
    void AddHistoryPointerEvent(const std::shared_ptr<MMI::PointerEvent>& info)
    {
        historyPointerEvent_.emplace_back(info);
    }
    const std::list<std::shared_ptr<MMI::PointerEvent>>& GetHistoryPointerEvent() const
    {
        return historyPointerEvent_;
    }
    void SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
    {
        pointerEvent_ = pointerEvent;
    }
    const std::shared_ptr<MMI::PointerEvent>& GetPointerEvent() const
    {
        return pointerEvent_;
    }

    void SetTouchEventsEnd(bool isTouchEventsEnd)
    {
        isTouchEventsEnd_ = isTouchEventsEnd;
    }

    bool GetTouchEventsEnd() const
    {
        return isTouchEventsEnd_;
    }

    TouchEvent ConvertToTouchEvent() const
    {
        TouchEvent touchEvent;
        if (!changedTouches_.empty()) {
            touchEvent.x = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetX());
            touchEvent.y = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetY());
            touchEvent.screenX = static_cast<float>(changedTouches_.front().GetScreenLocation().GetX());
            touchEvent.screenY = static_cast<float>(changedTouches_.front().GetScreenLocation().GetY());
            touchEvent.localX = static_cast<float>(changedTouches_.front().GetLocalLocation().GetX());
            touchEvent.localY = static_cast<float>(changedTouches_.front().GetLocalLocation().GetY());
            touchEvent.id = changedTouches_.front().GetFingerId();
            touchEvent.force = changedTouches_.front().GetForce();
            touchEvent.type = changedTouches_.front().GetTouchType();
            touchEvent.tiltX = changedTouches_.front().GetTiltX();
            touchEvent.tiltY = changedTouches_.front().GetTiltY();
        }
        touchEvent.time = timeStamp_;
        return touchEvent;
    }
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
};

class NativeEmbeadTouchInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(NativeEmbeadTouchInfo, BaseEventInfo);

public:
    NativeEmbeadTouchInfo(const std::string& embedId,
        const TouchEventInfo& touchEventInfo,
        const RefPtr<GestureEventResult>& result)
        : BaseEventInfo("NativeEmbeadTouchInfo"), embedId_(embedId), touchEvent_(touchEventInfo), result_(result) {}
    ~NativeEmbeadTouchInfo() override = default;

    const std::string& GetEmbedId() const
    {
        return embedId_;
    }

    const TouchEventInfo& GetTouchEventInfo() const
    {
        return touchEvent_;
    }
    const RefPtr<GestureEventResult>& GetResult() const
    {
        return result_;
    }
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
