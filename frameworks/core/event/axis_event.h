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

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

constexpr double MOUSE_WHEEL_DEGREES = 15.0;
constexpr double DP_PER_LINE_DESKTOP = 40.0;
constexpr Dimension LINE_HEIGHT_DESKTOP = 21.0_vp;
constexpr int32_t LINE_NUMBER_DESKTOP = 3;
constexpr int32_t DP_PER_LINE_PHONE = 64;
constexpr int32_t LINE_NUMBER_PHONE = 1;

enum class AxisDirection : int32_t {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8,
    UP_LEFT = 5,
    UP_RIGHT = 9,
    DOWN_LEFT = 6,
    DOWN_RIGHT = 10,
};

enum class AxisAction : int32_t {
    NONE = 0,
    BEGIN,
    UPDATE,
    END,
    CANCEL,
};

struct AxisEvent final {
    int32_t id = 0;
    float x = 0.0;
    float y = 0.0;
    float screenX = 0.0;
    float screenY = 0.0;
    double verticalAxis = 0.0;
    double horizontalAxis = 0.0;
    double pinchAxisScale = 0.0;
    AxisAction action;
    TimeStamp time;
    int64_t deviceId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::shared_ptr<MMI::PointerEvent> pointerEvent;

    AxisEvent CreateScaleEvent(float scale) const
    {
        if (NearZero(scale)) {
            return { .id = id,
                .x = x,
                .y = y,
                .screenX = screenX,
                .screenY = screenY,
                .verticalAxis = verticalAxis,
                .horizontalAxis = horizontalAxis,
                .pinchAxisScale = pinchAxisScale,
                .action = action,
                .time = time,
                .deviceId = deviceId,
                .sourceType = sourceType,
                .sourceTool = sourceTool,
                .pointerEvent = pointerEvent };
        }
        return { .id = id,
            .x = x / scale,
            .y = y / scale,
            .screenX = screenX / scale,
            .screenY = screenY / scale,
            .verticalAxis = verticalAxis,
            .horizontalAxis = horizontalAxis,
            .pinchAxisScale = pinchAxisScale,
            .action = action,
            .time = time,
            .deviceId = deviceId,
            .sourceType = sourceType,
            .sourceTool = sourceTool,
            .pointerEvent = pointerEvent };
    }

    Offset GetOffset() const
    {
        return Offset(x, y);
    }

    Offset GetScreenOffset() const
    {
        return Offset(screenX, screenY);
    }

    AxisDirection GetDirection() const
    {
        uint32_t verticalFlag = 0;
        uint32_t horizontalFlag = 0;
        if (LessNotEqual(verticalAxis, 0.0)) {
            verticalFlag = static_cast<uint32_t>(AxisDirection::UP);
        } else if (GreatNotEqual(verticalAxis, 0.0)) {
            verticalFlag = static_cast<uint32_t>(AxisDirection::DOWN);
        }
        if (LessNotEqual(horizontalAxis, 0.0)) {
            horizontalFlag = static_cast<uint32_t>(AxisDirection::LEFT);
        } else if (GreatNotEqual(horizontalAxis, 0.0)) {
            horizontalFlag = static_cast<uint32_t>(AxisDirection::RIGHT);
        }
        return static_cast<AxisDirection>(verticalFlag | horizontalFlag);
    }
    static bool IsDirectionUp(AxisDirection direction)
    {
        return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::UP));
    }
    static bool IsDirectionDown(AxisDirection direction)
    {
        return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::DOWN));
    }
    static bool IsDirectionLeft(AxisDirection direction)
    {
        return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::LEFT));
    }
    static bool IsDirectionRight(AxisDirection direction)
    {
        return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::RIGHT));
    }
};

class AxisInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(AxisInfo, BaseEventInfo);

public:
    AxisInfo() : BaseEventInfo("onAxis") {}
    AxisInfo(const AxisEvent& event, const Offset& localLocation, const EventTarget& target) : BaseEventInfo("onAxis")
    {
        action_ = event.action;
        verticalAxis_ = static_cast<float>(event.verticalAxis);
        horizontalAxis_ = static_cast<float>(event.horizontalAxis);
        pinchAxisScale_ = static_cast<float>(event.pinchAxisScale);
        globalLocation_ = event.GetOffset();
        localLocation_ = localLocation;
        screenLocation_ = Offset();
        SetTimeStamp(event.time);
        SetDeviceId(event.deviceId);
        SetSourceDevice(event.sourceType);
        SetTarget(target);
    }
    ~AxisInfo() override = default;

    void SetAction(AxisAction action)
    {
        action_ = action;
    }

    AxisAction GetAction() const
    {
        return action_;
    }

    void SetVerticalAxis(float axis)
    {
        verticalAxis_ = axis;
    }

    float GetVerticalAxis() const
    {
        return verticalAxis_;
    }

    void SetHorizontalAxis(float axis)
    {
        horizontalAxis_ = axis;
    }

    float GetHorizontalAxis() const
    {
        return horizontalAxis_;
    }

    void SetPinchAxisScale(float scale)
    {
        pinchAxisScale_ = scale;
    }

    float GetPinchAxisScale() const
    {
        return pinchAxisScale_;
    }

    AxisInfo& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        return *this;
    }
    AxisInfo& SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
        return *this;
    }

    AxisInfo& SetScreenLocation(const Offset& screenLocation)
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

private:
    AxisAction action_ = AxisAction::NONE;
    float verticalAxis_ = 0.0;
    float horizontalAxis_ = 0.0;
    float pinchAxisScale_ = 0.0;
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

    void SetOnAxisCallback(const OnAxisEventFunc& onAxisCallback)
    {
        onAxisCallback_ = onAxisCallback;
    }

    void SetCoordinateOffset(const NG::OffsetF& coordinateOffset)
    {
        coordinateOffset_ = coordinateOffset;
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

    void SetFrameName(const std::string& frameName)
    {
        frameName_ = frameName;
    }

    std::string GetFrameName() const
    {
        return frameName_;
    }

    bool HandleAxisEvent(const AxisEvent& event)
    {
        if (!onAxisCallback_) {
            return false;
        }
        Offset localLocation = Offset(
            event.GetOffset().GetX() - coordinateOffset_.GetX(), event.GetOffset().GetY() - coordinateOffset_.GetY());
        AxisInfo info = AxisInfo(event, localLocation, GetEventTarget().value_or(EventTarget()));
        LOGD("HandleAxisEvent: Node: %{public}s, Action: %{public}d, HorizontalAxis: %{public}f, VeriticalAxis: "
             "%{public}f, PinchAxis: %{public}f",
            frameName_.c_str(), info.GetAction(), info.GetHorizontalAxis(), info.GetVerticalAxis(),
            info.GetPinchAxisScale());
        onAxisCallback_(info);
        return true;
    }

    virtual void HandleEvent(const AxisEvent& event) {}

private:
    OnAxisEventFunc onAxisCallback_;
    NG::OffsetF coordinateOffset_;
    GetEventTargetImpl getEventTargetImpl_;
    std::string frameName_ = "Unknown";
};

using AxisTestResult = std::list<RefPtr<AxisEventTarget>>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H