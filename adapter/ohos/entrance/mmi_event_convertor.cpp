/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/mmi_event_convertor.h"

#include <memory>

#include "pointer_event.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::Platform {

SourceTool GetSourceTool(int32_t orgToolType)
{
    switch (orgToolType) {
        case OHOS::MMI::PointerEvent::TOOL_TYPE_FINGER:
            return SourceTool::FINGER;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_PEN:
            return SourceTool::PEN;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_RUBBER:
            return SourceTool::RUBBER;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_BRUSH:
            return SourceTool::BRUSH;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_PENCIL:
            return SourceTool::PENCIL;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_AIRBRUSH:
            return SourceTool::AIRBRUSH;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_MOUSE:
            return SourceTool::MOUSE;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_LENS:
            return SourceTool::LENS;
        case OHOS::MMI::PointerEvent::TOOL_TYPE_TOUCHPAD:
            return SourceTool::TOUCHPAD;
        default:
            LOGW("unknown tool type");
            return SourceTool::UNKNOWN;
    }
}

TouchPoint ConvertTouchPoint(const MMI::PointerEvent::PointerItem& pointerItem)
{
    TouchPoint touchPoint;
    // just get the max of width and height
    touchPoint.size = std::max(pointerItem.GetWidth(), pointerItem.GetHeight()) / 2.0;
    touchPoint.id = pointerItem.GetPointerId();
    touchPoint.downTime = TimeStamp(std::chrono::microseconds(pointerItem.GetDownTime()));
    touchPoint.x = pointerItem.GetWindowX();
    touchPoint.y = pointerItem.GetWindowY();
    touchPoint.screenX = pointerItem.GetDisplayX();
    touchPoint.screenY = pointerItem.GetDisplayY();
    touchPoint.isPressed = pointerItem.IsPressed();
    touchPoint.force = static_cast<float>(pointerItem.GetPressure());
    touchPoint.tiltX = pointerItem.GetTiltX();
    touchPoint.tiltY = pointerItem.GetTiltY();
    touchPoint.sourceTool = GetSourceTool(pointerItem.GetToolType());
    return touchPoint;
}

void UpdateTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, TouchEvent& touchEvent)
{
    auto ids = pointerEvent->GetPointerIds();
    for (auto&& id : ids) {
        MMI::PointerEvent::PointerItem item;
        bool ret = pointerEvent->GetPointerItem(id, item);
        if (!ret) {
            LOGE("get pointer item failed.");
            continue;
        }
        auto touchPoint = ConvertTouchPoint(item);
        touchEvent.pointers.emplace_back(std::move(touchPoint));
    }
    touchEvent.CovertId();
}

TouchEvent ConvertTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    int32_t pointerID = pointerEvent->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    bool ret = pointerEvent->GetPointerItem(pointerID, item);
    if (!ret) {
        LOGE("get pointer item failed.");
        return TouchEvent();
    }
    auto touchPoint = ConvertTouchPoint(item);
    std::chrono::microseconds microseconds(pointerEvent->GetActionTime());
    TimeStamp time(microseconds);
    TouchEvent event { touchPoint.id, touchPoint.x, touchPoint.y, touchPoint.screenX, touchPoint.screenY,
        TouchType::UNKNOWN, TouchType::UNKNOWN, time, touchPoint.size, touchPoint.force, touchPoint.tiltX,
        touchPoint.tiltY, pointerEvent->GetDeviceId(), pointerEvent->GetTargetDisplayId(), SourceType::NONE,
        touchPoint.sourceTool };
    event.pointerEvent = pointerEvent;
#ifdef SECURITY_COMPONENT_ENABLE
    event.enhanceData = pointerEvent->GetEnhanceData();
#endif
    int32_t orgDevice = pointerEvent->GetSourceType();
    GetEventDevice(orgDevice, event);
    int32_t orgAction = pointerEvent->GetPointerAction();
    switch (orgAction) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_CANCEL:
            event.type = TouchType::CANCEL;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN:
            event.type = TouchType::DOWN;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE:
            event.type = TouchType::MOVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_UP:
            event.type = TouchType::UP;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_DOWN:
            event.type = TouchType::PULL_DOWN;
            event.pullType = TouchType::PULL_DOWN;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE:
            event.type = TouchType::PULL_MOVE;
            event.pullType = TouchType::PULL_MOVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP:
            event.type = TouchType::PULL_UP;
            event.pullType = TouchType::PULL_UP;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW:
            event.type = TouchType::PULL_IN_WINDOW;
            event.pullType = TouchType::PULL_IN_WINDOW;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW:
            event.type = TouchType::PULL_OUT_WINDOW;
            event.pullType = TouchType::PULL_OUT_WINDOW;
            break;
        default:
            LOGW("unknown type");
            break;
    }
    UpdateTouchEvent(pointerEvent, event);
    return event;
}

void GetMouseEventAction(int32_t action, MouseEvent& events, bool isScenceBoardWindow)
{
    switch (action) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN:
            events.action = MouseAction::PRESS;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_UP:
            events.action = MouseAction::RELEASE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW:
            events.action = MouseAction::WINDOW_ENTER;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW:
            events.action = MouseAction::WINDOW_LEAVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE:
            events.action = MouseAction::MOVE;
            break;
#ifdef ENABLE_DRAG_FRAMEWORK
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_DOWN:
            events.action = MouseAction::PRESS;
            if (isScenceBoardWindow) {
                events.pullAction = MouseAction::PULL_DOWN;
            }
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE:
            events.action = MouseAction::MOVE;
            if (isScenceBoardWindow) {
                events.pullAction = MouseAction::PULL_MOVE;
            }
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP:
            events.action = MouseAction::RELEASE;
            if (isScenceBoardWindow) {
                events.pullAction = MouseAction::PULL_UP;
            }
            break;
#endif // ENABLE_DRAG_FRAMEWORK
        default:
            events.action = MouseAction::NONE;
            break;
    }
}

void GetMouseEventButton(int32_t button, MouseEvent& events)
{
    switch (button) {
        case OHOS::MMI::PointerEvent::MOUSE_BUTTON_LEFT:
            events.button = MouseButton::LEFT_BUTTON;
            break;
        case OHOS::MMI::PointerEvent::MOUSE_BUTTON_RIGHT:
            events.button = MouseButton::RIGHT_BUTTON;
            break;
        case OHOS::MMI::PointerEvent::MOUSE_BUTTON_MIDDLE:
            events.button = MouseButton::MIDDLE_BUTTON;
            break;
        case OHOS::MMI::PointerEvent::MOUSE_BUTTON_SIDE:
            events.button = MouseButton::BACK_BUTTON;
            break;
        case OHOS::MMI::PointerEvent::MOUSE_BUTTON_EXTRA:
            events.button = MouseButton::FORWARD_BUTTON;
            break;
        default:
            events.button = MouseButton::NONE_BUTTON;
            break;
    }
}

void ConvertMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    MouseEvent& events, bool isScenceBoardWindow)
{
    int32_t pointerID = pointerEvent->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    bool ret = pointerEvent->GetPointerItem(pointerID, item);
    if (!ret) {
        LOGE("get pointer: %{public}d item failed.", pointerID);
        return;
    }
    events.id = pointerID;
    events.x = item.GetWindowX();
    events.y = item.GetWindowY();
    events.screenX = item.GetDisplayX();
    events.screenY = item.GetDisplayY();
    int32_t orgAction = pointerEvent->GetPointerAction();
    GetMouseEventAction(orgAction, events, isScenceBoardWindow);
    int32_t orgButton = pointerEvent->GetButtonId();
    GetMouseEventButton(orgButton, events);
    int32_t orgDevice = pointerEvent->GetSourceType();
    GetEventDevice(orgDevice, events);
    events.targetDisplayId = pointerEvent->GetTargetDisplayId();

    std::set<int32_t> pressedSet = pointerEvent->GetPressedButtons();
    uint32_t pressedButtons = 0;
    if (pressedSet.find(OHOS::MMI::PointerEvent::MOUSE_BUTTON_LEFT) != pressedSet.end()) {
        pressedButtons &= static_cast<uint32_t>(MouseButton::LEFT_BUTTON);
    }
    if (pressedSet.find(OHOS::MMI::PointerEvent::MOUSE_BUTTON_RIGHT) != pressedSet.end()) {
        pressedButtons &= static_cast<uint32_t>(MouseButton::RIGHT_BUTTON);
    }
    if (pressedSet.find(OHOS::MMI::PointerEvent::MOUSE_BUTTON_MIDDLE) != pressedSet.end()) {
        pressedButtons &= static_cast<uint32_t>(MouseButton::MIDDLE_BUTTON);
    }
    events.pressedButtons = static_cast<int32_t>(pressedButtons);

    std::chrono::microseconds microseconds(pointerEvent->GetActionTime());
    TimeStamp time(microseconds);
    events.time = time;
    events.pointerEvent = pointerEvent;
#ifdef SECURITY_COMPONENT_ENABLE
    events.enhanceData = pointerEvent->GetEnhanceData();
#endif
    LOGD("ConvertMouseEvent: id: %{public}d (x,y): (%{public}f,%{public}f). Button: %{public}d. Action: %{public}d. "
         "DeviceType: %{public}d. PressedButton: %{public}d. Time: %{public}lld",
        events.id, events.x, events.y, events.button, events.action, events.sourceType, events.pressedButtons,
        (long long)pointerEvent->GetActionTime());
}

void GetAxisEventAction(int32_t action, AxisEvent& event)
{
    switch (action) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN:
            event.action = AxisAction::BEGIN;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE:
            event.action = AxisAction::UPDATE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_AXIS_END:
            event.action = AxisAction::END;
            break;
        default:
            event.action = AxisAction::NONE;
            break;
    }
}

void ConvertAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, AxisEvent& event)
{
    int32_t pointerID = pointerEvent->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    bool ret = pointerEvent->GetPointerItem(pointerID, item);
    if (!ret) {
        LOGE("get pointer: %{public}d item failed.", pointerID);
        return;
    }

    event.id = item.GetPointerId();
    event.x = static_cast<float>(item.GetWindowX());
    event.y = static_cast<float>(item.GetWindowY());
    event.screenX = static_cast<float>(item.GetDisplayX());
    event.screenY = static_cast<float>(item.GetDisplayY());
    event.horizontalAxis = pointerEvent->GetAxisValue(OHOS::MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL);
    event.verticalAxis = pointerEvent->GetAxisValue(OHOS::MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL);
    event.pinchAxisScale = pointerEvent->GetAxisValue(OHOS::MMI::PointerEvent::AxisType::AXIS_TYPE_PINCH);
    int32_t orgAction = pointerEvent->GetPointerAction();
    GetAxisEventAction(orgAction, event);
    int32_t orgDevice = pointerEvent->GetSourceType();
    GetEventDevice(orgDevice, event);
    event.sourceTool = GetSourceTool(item.GetToolType());
    event.pointerEvent = pointerEvent;

    std::chrono::microseconds microseconds(pointerEvent->GetActionTime());
    TimeStamp time(microseconds);
    event.time = time;
    LOGD("ConvertAxisEvent: id: %{public}d, (x,y): (%{public}f,%{public}f). HorizontalAxis: %{public}f. VerticalAxis: "
         "%{public}f. "
         "Action: %{public}d. SourceType: %{public}d. ToolType: %{public}d. Time: %{public}lld",
        event.id, event.x, event.y, event.horizontalAxis, event.verticalAxis, event.action, event.sourceType,
        event.sourceTool, (long long)pointerEvent->GetActionTime());
}

void ConvertKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, KeyEvent& event)
{
    event.rawKeyEvent = keyEvent;
    event.code = static_cast<KeyCode>(keyEvent->GetKeyCode());
    event.keyIntention = static_cast<KeyIntention>(keyEvent->GetKeyIntention());
    if (keyEvent->GetKeyAction() == OHOS::MMI::KeyEvent::KEY_ACTION_UP) {
        event.action = KeyAction::UP;
    } else if (keyEvent->GetKeyAction() == OHOS::MMI::KeyEvent::KEY_ACTION_DOWN) {
        event.action = KeyAction::DOWN;
    } else {
        event.action = KeyAction::UNKNOWN;
    }
    std::chrono::microseconds microseconds(keyEvent->GetActionTime());
    TimeStamp time(microseconds);
    event.timeStamp = time;
    event.key = MMI::KeyEvent::KeyCodeToString(keyEvent->GetKeyCode());
    event.deviceId = keyEvent->GetDeviceId();
    event.sourceType = SourceType::KEYBOARD;
    std::string pressedKeyStr = "Pressed Keys: ";
    for (const auto& curCode : keyEvent->GetPressedKeys()) {
        pressedKeyStr += (std::to_string(curCode) + " ");
        event.pressedCodes.emplace_back(static_cast<KeyCode>(curCode));
    }
    LOGD("ConvertKeyEvent: KeyCode: %{private}d. KeyAction: %{public}d. PressedCodes: %{private}s. Time: %{public}lld",
        event.code, event.action, pressedKeyStr.c_str(), (long long)(keyEvent->GetActionTime()));
}

void LogPointInfo(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("point source: %{public}d", pointerEvent->GetSourceType());
        auto actionId = pointerEvent->GetPointerId();
        MMI::PointerEvent::PointerItem item;
        if (pointerEvent->GetPointerItem(actionId, item)) {
            LOGI("action point info: id: %{public}d, x: %{public}d, y: %{public}d, action: %{public}d, pressure: "
                "%{public}f, tiltX: %{public}f, tiltY: %{public}f",
                actionId, item.GetWindowX(), item.GetWindowY(), pointerEvent->GetPointerAction(), item.GetPressure(),
                item.GetTiltX(), item.GetTiltY());
        }
        auto ids = pointerEvent->GetPointerIds();
        for (auto&& id : ids) {
            MMI::PointerEvent::PointerItem item;
            if (pointerEvent->GetPointerItem(id, item)) {
                LOGI("all point info: id: %{public}d, x: %{public}d, y: %{public}d, isPressed: %{public}d, pressure: "
                     "%{public}f, tiltX: %{public}f, tiltY: %{public}f",
                    actionId, item.GetWindowX(), item.GetWindowY(), item.IsPressed(), item.GetPressure(),
                    item.GetTiltX(), item.GetTiltY());
            }
        }
    }
}

void CalculatePointerEvent(
    const NG::OffsetF& offsetF, const std::shared_ptr<MMI::PointerEvent>& point, const NG::VectorF& scale)
{
    CHECK_NULL_VOID(point);
    int32_t pointerId = point->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    bool ret = point->GetPointerItem(pointerId, item);
    if (ret) {
        float xRelative = item.GetWindowX() - offsetF.GetX();
        float yRelative = item.GetWindowY() - offsetF.GetY();
        float xBeforeScale = NearZero(scale.x) ? xRelative : xRelative / scale.x;
        float yBeforeScale = NearZero(scale.y) ? yRelative : yRelative / scale.y;

        item.SetWindowX(static_cast<int32_t>(xBeforeScale));
        item.SetWindowY(static_cast<int32_t>(yBeforeScale));
        point->UpdatePointerItem(pointerId, item);
    }
}

void CalculateWindowCoordinate(const NG::OffsetF& offsetF, const std::shared_ptr<MMI::PointerEvent>& point,
    const NG::VectorF& scale, const int32_t udegree)
{
    CHECK_NULL_VOID(point);
    int32_t pointerId = point->GetPointerId();
    MMI::PointerEvent::PointerItem item;
    bool ret = point->GetPointerItem(pointerId, item);
    if (ret) {
        float xRelative = item.GetDisplayX();
        float yRelative = item.GetDisplayY();
        float windowX = xRelative;
        float windowY = yRelative;
        int32_t deviceWidth = SystemProperties::GetDeviceWidth();
        int32_t deviceHeight = SystemProperties::GetDeviceHeight();

        if (udegree == 0) {
            windowX = xRelative - offsetF.GetX();
            windowY = yRelative - offsetF.GetY();
        }
        if (udegree == 90) {
            windowX = yRelative - offsetF.GetX();
            windowY = deviceWidth - offsetF.GetY() - xRelative;
        }
        if (udegree == 180) {
            windowX = deviceWidth - offsetF.GetX() - xRelative;
            windowY = deviceHeight - offsetF.GetY() - yRelative;
        }
        if (udegree == 270) {
            windowX = deviceHeight - offsetF.GetX() - yRelative;
            windowY = xRelative - offsetF.GetY();
        }

        windowX = NearZero(scale.x) ? windowX : windowX / scale.x;
        windowY = NearZero(scale.y) ? windowY : windowY / scale.y;

        item.SetWindowX(static_cast<int32_t>(windowX));
        item.SetWindowY(static_cast<int32_t>(windowY));
        point->UpdatePointerItem(pointerId, item);
    }
}
} // namespace OHOS::Ace::Platform
