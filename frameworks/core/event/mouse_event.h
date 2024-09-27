/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/mousestyle/mouse_style.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

class MouseInfo;
constexpr int32_t MOUSE_PRESS_LEFT = 1;
static const int32_t MOUSE_BASE_ID = 1000;

using OnMouseEventFunc = std::function<void(MouseInfo& info)>;

enum class MouseAction : int32_t {
    NONE = 0,
    PRESS = 1,
    RELEASE = 2,
    MOVE = 3,
    WINDOW_ENTER = 4,
    WINDOW_LEAVE = 5,
    HOVER,
    HOVER_ENTER,
    HOVER_MOVE,
    HOVER_EXIT,
    PULL_DOWN,
    PULL_MOVE,
    PULL_UP,
    CANCEL
};

enum class AccessibilityHoverAction : int32_t {
    UNKNOWN = -1,
    HOVER_ENTER,
    HOVER_MOVE,
    HOVER_EXIT,
    HOVER_CANCEL
};

enum class MouseState : int32_t {
    NONE = 0,
    HOVER = 1,
};

enum class MouseButton : int32_t {
    NONE_BUTTON = 0,
    LEFT_BUTTON = 1,
    RIGHT_BUTTON = 2,
    MIDDLE_BUTTON = 4,
    BACK_BUTTON = 8,
    FORWARD_BUTTON = 16,
    SIDE_BUTTON = 32,
    EXTRA_BUTTON = 64,
    TASK_BUTTON = 128,
};

enum class HoverEffectType : int32_t {
    NONE,
    OPACITY,
    SCALE,
    BOARD,
    AUTO,
    UNKNOWN,
};

struct MouseEvent final {
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float deltaZ = 0.0f;
    float scrollX = 0.0f;
    float scrollY = 0.0f;
    float scrollZ = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    MouseAction action = MouseAction::NONE;
    MouseAction pullAction = MouseAction::NONE;
    MouseButton button = MouseButton::NONE_BUTTON;
    int32_t pressedButtons = 0; // combined by MouseButtons
    TimeStamp time;
    int64_t deviceId = 0;
    int32_t targetDisplayId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::shared_ptr<MMI::PointerEvent> pointerEvent;
    int32_t touchEventId = 0;
    int32_t originalId = 0;
    std::vector<KeyCode> pressedKeyCodes_;
    std::vector<MouseEvent> history;
    bool isInjected = false;
    bool isPrivacyMode = false;

    Offset GetOffset() const
    {
        return Offset(x, y);
    }

    Offset GetScreenOffset() const
    {
        return Offset(screenX, screenY);
    }

    int32_t GetId() const
    {
        if (pressedButtons > 0) {
            return pressedButtons + MOUSE_BASE_ID;
        } else {
            return (int32_t)button + MOUSE_BASE_ID;
        }
    }

    int32_t GetPointerId(int32_t pointerId) const
    {
        if (pressedButtons > 0) {
            return pressedButtons + MOUSE_BASE_ID + pointerId;
        }
        return static_cast<int32_t>(button) + MOUSE_BASE_ID + pointerId;
    }

    MouseEvent CloneWith(float scale) const
    {
        return {.id = id,
            .x = x / scale,
            .y = y / scale,
            .z = z / scale,
            .deltaX = deltaX / scale,
            .deltaY = deltaY / scale,
            .deltaZ = deltaZ / scale,
            .scrollX = scrollX / scale,
            .scrollY = scrollY / scale,
            .scrollZ = scrollZ / scale,
            .screenX = screenX / scale,
            .screenY = screenY / scale,
            .action = action,
            .pullAction = pullAction,
            .button = button,
            .pressedButtons = pressedButtons,
            .time = time,
            .deviceId = deviceId,
            .targetDisplayId = targetDisplayId,
            .sourceType = sourceType,
            .sourceTool = sourceTool,
            .pointerEvent = pointerEvent,
            .originalId = originalId,
            .pressedKeyCodes_ = pressedKeyCodes_,
            .isInjected = isInjected,
            .isPrivacyMode = isPrivacyMode
        };
    }

    MouseEvent CreateScaleEvent(float scale) const
    {
        if (NearZero(scale)) {
            return CloneWith(1);
        }
        return CloneWith(scale);
    }

    TouchEvent CreateTouchPoint() const
    {
        TouchType type = TouchType::UNKNOWN;
        if (action == MouseAction::PRESS) {
            type = TouchType::DOWN;
        } else if (action == MouseAction::RELEASE) {
            type = TouchType::UP;
        } else if (action == MouseAction::MOVE) {
            type = TouchType::MOVE;
        } else if (action == MouseAction::CANCEL) {
            type = TouchType::CANCEL;
        } else {
            type = TouchType::UNKNOWN;
        }
        int32_t pointId = id;
        if (sourceType == SourceType::MOUSE) {
            pointId = GetPointerId(pointId);
        }
        auto pointOriginalId = sourceType == SourceType::MOUSE ? GetId() : originalId;
        TouchPoint point { .id = pointId,
            .x = x,
            .y = y,
            .screenX = screenX,
            .screenY = screenY,
            .downTime = time,
            .size = 0.0,
            .isPressed = (type == TouchType::DOWN),
            .originalId = pointOriginalId };
        TouchEvent event;
        event.SetId(pointId)
            .SetX(x)
            .SetY(y)
            .SetScreenX(screenX)
            .SetScreenY(screenY)
            .SetType(type)
            .SetTime(time)
            .SetSize(0.0)
            .SetDeviceId(deviceId)
            .SetTargetDisplayId(targetDisplayId)
            .SetSourceType(sourceType)
            .SetSourceTool(sourceTool)
            .SetPointerEvent(pointerEvent)
            .SetTouchEventId(touchEventId)
            .SetOriginalId(pointOriginalId)
            .SetIsInjected(isInjected);
        event.isPrivacyMode = isPrivacyMode;
        event.pointers.emplace_back(std::move(point));
        event.pressedKeyCodes_ = pressedKeyCodes_;
        return event;
    }

    MouseEvent operator-(const Offset& offset) const
    {
        return { .x = x - offset.GetX(),
            .y = y - offset.GetY(),
            .z = z,
            .deltaX = deltaX,
            .deltaY = deltaY,
            .deltaZ = deltaZ,
            .scrollX = scrollX,
            .scrollY = scrollY,
            .scrollZ = scrollZ,
            .screenX = screenX - offset.GetX(),
            .screenY = screenY - offset.GetY(),
            .action = action,
            .button = button,
            .pressedButtons = pressedButtons,
            .time = time,
            .deviceId = deviceId,
            .targetDisplayId = targetDisplayId,
            .sourceType = sourceType,
            .sourceTool = sourceTool,
            .pointerEvent = pointerEvent,
            .originalId = originalId,
            .pressedKeyCodes_ = pressedKeyCodes_,
            .isInjected = isInjected,
            .isPrivacyMode = isPrivacyMode
        };
    }
};

class MouseInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(MouseInfo, BaseEventInfo);

public:
    MouseInfo() : BaseEventInfo("onMouse") {}
    ~MouseInfo() override = default;

    void SetButton(MouseButton button)
    {
        button_ = button;
    }

    MouseButton GetButton() const
    {
        return button_;
    }

    void SetAction(MouseAction action)
    {
        action_ = action;
    }

    MouseAction GetAction() const
    {
        return action_;
    }

    void SetPullAction(MouseAction pullAction)
    {
        pullAction_ = pullAction;
    }

    MouseAction GetPullAction() const
    {
        return pullAction_;
    }

    MouseInfo& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        return *this;
    }
    MouseInfo& SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
        return *this;
    }

    MouseInfo& SetScreenLocation(const Offset& screenLocation)
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

    void SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
    {
        pointerEvent_ = pointerEvent;
    }
    const std::shared_ptr<MMI::PointerEvent> GetPointerEvent() const
    {
        return pointerEvent_;
    }

private:
    std::shared_ptr<MMI::PointerEvent> pointerEvent_;
    MouseButton button_ = MouseButton::NONE_BUTTON;
    MouseAction action_ = MouseAction::NONE;
    MouseAction pullAction_ = MouseAction::NONE;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
    Offset screenLocation_;
};

using HoverEffectFunc = std::function<void(bool)>;

class HoverInfo;
class HoverInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(HoverInfo, BaseEventInfo);

public:
    HoverInfo() : BaseEventInfo("onHover") {}
    ~HoverInfo() override = default;
};

class AccessibilityHoverInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(AccessibilityHoverInfo, BaseEventInfo);

public:
    AccessibilityHoverInfo() : BaseEventInfo("onAccessibilityHover") {}
    ~AccessibilityHoverInfo() override = default;

    AccessibilityHoverInfo& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        return *this;
    }
    AccessibilityHoverInfo& SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
        return *this;
    }

    AccessibilityHoverInfo& SetScreenLocation(const Offset& screenLocation)
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

    AccessibilityHoverAction GetActionType() const
    {
        return actionType_;
    }

    void SetActionType(AccessibilityHoverAction type)
    {
        actionType_ = type;
    }

private:
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;

    Offset screenLocation_;

    // touch type
    AccessibilityHoverAction actionType_ = AccessibilityHoverAction::UNKNOWN;
};

using OnHoverFunc = std::function<void(bool, HoverInfo& info)>;
using OnHoverEventFunc = std::function<void(bool)>;

using OnAccessibilityHoverFunc = std::function<void(bool, AccessibilityHoverInfo& info)>;

class MouseEventTarget : public virtual TouchEventTarget {
    DECLARE_ACE_TYPE(MouseEventTarget, TouchEventTarget);

public:
    MouseEventTarget(const std::string& nodeName, int32_t nodeId) : TouchEventTarget(nodeName, nodeId) {}
    ~MouseEventTarget() override = default;

    void SetCallback(const OnMouseEventFunc& onMouseCallback)
    {
        onMouseCallback_ = onMouseCallback;
    }

    bool HandleMouseEvent(const MouseEvent& event)
    {
        if (!onMouseCallback_) {
            return false;
        }
        MouseInfo info;
        info.SetPointerEvent(event.pointerEvent);
        info.SetButton(event.button);
        info.SetAction(event.action);
        info.SetPullAction(event.pullAction);
        info.SetGlobalLocation(event.GetOffset());
        Offset localLocation = Offset(
            event.GetOffset().GetX() - coordinateOffset_.GetX(), event.GetOffset().GetY() - coordinateOffset_.GetY());
        info.SetLocalLocation(localLocation);
        info.SetScreenLocation(event.GetScreenOffset());
        info.SetTimeStamp(event.time);
        info.SetDeviceId(event.deviceId);
        info.SetTargetDisplayId(event.targetDisplayId);
        info.SetSourceDevice(event.sourceType);
        info.SetSourceTool(event.sourceTool);
        info.SetTarget(GetEventTarget().value_or(EventTarget()));
        info.SetPressedKeyCodes(event.pressedKeyCodes_);
        onMouseCallback_(info);
        return info.IsStopPropagation();
    }

    bool DispatchEvent(const TouchEvent& point) override
    {
        return false;
    }
    // if return false means need to stop event bubbling.
    bool HandleEvent(const TouchEvent& point) override
    {
        return false;
    }

private:
    OnMouseEventFunc onMouseCallback_;
};

class HoverEventTarget : public virtual TouchEventTarget {
    DECLARE_ACE_TYPE(HoverEventTarget, TouchEventTarget);

public:
    HoverEventTarget(const std::string& nodeName, int32_t nodeId) : TouchEventTarget(nodeName, nodeId) {}
    ~HoverEventTarget() override = default;

    void SetCallback(const OnHoverEventFunc& onHoverCallback)
    {
        onHoverCallback_ = onHoverCallback;
    }
    void SetCallback(const OnHoverFunc& onHoverEventCallback)
    {
        onHoverEventCallback_ = onHoverEventCallback;
    }

    void SetAccessibilityHoverCallback(const OnAccessibilityHoverFunc& onAccessibilityHoverCallback)
    {
        onAccessibilityHoverCallback_ = onAccessibilityHoverCallback;
    }

    void SetPenHoverCallback(const OnHoverFunc& onPenHoverEventCallback)
    {
        onPenHoverEventCallback_ = onPenHoverEventCallback;
    }

    bool HandleHoverEvent(bool isHovered, const MouseEvent& event);

    void HandleAccessibilityHoverEvent(bool isHovered, const TouchEvent& event);

    bool HandlePenHoverEvent(bool isHovered, const TouchEvent& event);

    bool IsAccessibilityHoverTarget()
    {
        return onAccessibilityHoverCallback_ != nullptr;
    }

    bool IsPenHoverTarget() const
    {
        return onPenHoverEventCallback_ != nullptr;
    }

    bool HandleHoverEvent(bool isHovered)
    {
        if (!onHoverCallback_) {
            return false;
        }
        onHoverCallback_(isHovered);
        return true;
    }

    bool DispatchEvent(const TouchEvent& point) override
    {
        return false;
    }
    bool HandleEvent(const TouchEvent& point) override
    {
        return false;
    }

    AccessibilityHoverAction ConvertAccessibilityHoverAction(TouchType type);

private:
    OnHoverEventFunc onHoverCallback_;
    OnHoverFunc onHoverEventCallback_;
    OnAccessibilityHoverFunc onAccessibilityHoverCallback_;
    OnHoverFunc onPenHoverEventCallback_;
};

class HoverEffectTarget : public virtual TouchEventTarget {
    DECLARE_ACE_TYPE(HoverEffectTarget, TouchEventTarget);

public:
    HoverEffectTarget(const std::string& nodeName, int32_t nodeId) : TouchEventTarget(nodeName, nodeId) {}
    ~HoverEffectTarget() override = default;

    void SetHoverNode(const WeakPtr<NG::FrameNode>& node)
    {
        hoverNode_ = node;
    }
    WeakPtr<NG::FrameNode> GetHoverNode() const
    {
        return hoverNode_;
    }

    bool DispatchEvent(const TouchEvent& point) override
    {
        return false;
    }
    // if return false means need to stop event bubbling.
    bool HandleEvent(const TouchEvent& point) override
    {
        return false;
    }

private:
    WeakPtr<NG::FrameNode> hoverNode_;
};

using MouseTestResult = std::list<RefPtr<MouseEventTarget>>;
using HoverTestResult = std::list<RefPtr<HoverEventTarget>>;

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H
