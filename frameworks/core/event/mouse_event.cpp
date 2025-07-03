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

#include "core/event/mouse_event.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/offset.h"
#include "base/input_manager/input_manager.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
bool HoverEventTarget::HandleHoverEvent(bool isHovered, const MouseEvent& event)
{
    if (!onHoverEventCallback_) {
        return false;
    }
    ACE_SCOPED_TRACE("HandleHoverEvent node:%d/%s isHovered:%d", GetNodeId(), GetNodeName().c_str(), isHovered);
    lastHoverState_ = isHovered;
    HoverInfo hoverInfo;
    auto node = GetAttachedNode().Upgrade();
    if (node) {
        NG::PointF localPoint(event.x, event.y);
        NG::NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false, isPostEventResult_);
        auto localX = static_cast<float>(localPoint.GetX());
        auto localY = static_cast<float>(localPoint.GetY());
        hoverInfo.SetLocalLocation(Offset(localX, localY));
    }
    hoverInfo.SetTimeStamp(event.time);
    hoverInfo.SetDeviceId(event.deviceId);
    hoverInfo.SetSourceDevice(event.sourceType);
    hoverInfo.SetSourceTool(event.sourceTool);
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    hoverInfo.SetPressedKeyCodes(event.pressedKeyCodes_);
    hoverInfo.SetMouseAction(event.action);
    hoverInfo.SetTargetDisplayId(event.targetDisplayId);
    // onHoverEventCallback_ may be overwritten in its invoke so we copy it first
    auto onHoverEventCallback = onHoverEventCallback_;
    onHoverEventCallback(isHovered, hoverInfo);
    return !hoverInfo.IsStopPropagation();
}

bool HoverEventTarget::HandlePenHoverEvent(bool isHovered, const TouchEvent& event)
{
    if (!onPenHoverEventCallback_) {
        return false;
    }
    HoverInfo hoverInfo;
    hoverInfo.SetTimeStamp(event.time);
    hoverInfo.SetDeviceId(event.deviceId);
    hoverInfo.SetSourceDevice(event.sourceType);
    hoverInfo.SetSourceTool(event.sourceTool);
    if (event.tiltX.has_value()) {
        hoverInfo.SetTiltX(event.tiltX.value_or(0.0f));
    }
    if (event.tiltY.has_value()) {
        hoverInfo.SetTiltY(event.tiltY.value_or(0.0f));
    }
    if (event.rollAngle.has_value()) {
        hoverInfo.SetRollAngle(event.rollAngle.value_or(0.0f));
    }
    NG::PointF lastLocalPoint(event.x, event.y);
    NG::NGGestureRecognizer::Transform(lastLocalPoint, GetAttachedNode(), false,
        isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    hoverInfo.SetLocalLocation(Offset(localX, localY));
    hoverInfo.SetGlobalLocation(Offset(event.x, event.y));
    hoverInfo.SetScreenLocation(Offset(event.screenX, event.screenY));
    hoverInfo.SetGlobalDisplayLocation(Offset(event.globalDisplayX, event.globalDisplayY));
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    hoverInfo.SetTargetDisplayId(event.targetDisplayId);
    // onPenHoverEventCallback_ may be overwritten in its invoke so we copy it first
    auto onPenHoverEventCallback = onPenHoverEventCallback_;
    onPenHoverEventCallback(isHovered, hoverInfo);
    return !hoverInfo.IsStopPropagation();
}

bool HoverEventTarget::HandlePenHoverMoveEvent(const TouchEvent& event)
{
    if (!onPenHoverMoveEventCallback_) {
        return false;
    }
    HoverInfo hoverInfo;
    hoverInfo.SetTimeStamp(event.time);
    hoverInfo.SetDeviceId(event.deviceId);
    hoverInfo.SetSourceDevice(event.sourceType);
    hoverInfo.SetSourceTool(event.sourceTool);
    if (event.tiltX.has_value()) {
        hoverInfo.SetTiltX(event.tiltX.value_or(0.0f));
    }
    if (event.tiltY.has_value()) {
        hoverInfo.SetTiltY(event.tiltY.value_or(0.0f));
    }
    if (event.rollAngle.has_value()) {
        hoverInfo.SetRollAngle(event.rollAngle.value_or(0.0f));
    }
    NG::PointF lastLocalPoint(event.x, event.y);
    NG::NGGestureRecognizer::Transform(lastLocalPoint, GetAttachedNode(), false,
        isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    hoverInfo.SetLocalLocation(Offset(localX, localY));
    hoverInfo.SetGlobalLocation(Offset(event.x, event.y));
    hoverInfo.SetScreenLocation(Offset(event.screenX, event.screenY));
    hoverInfo.SetGlobalDisplayLocation(Offset(event.globalDisplayX, event.globalDisplayY));
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    hoverInfo.SetTargetDisplayId(event.targetDisplayId);
    // onPenHoverMoveEventCallback_ may be overwritten in its invoke so we copy it first
    auto onPenHoverMoveEventCallback = onPenHoverMoveEventCallback_;
    onPenHoverMoveEventCallback(hoverInfo);
    return !hoverInfo.IsStopPropagation();
}

void HoverEventTarget::HandleAccessibilityHoverEvent(bool isHovered, const TouchEvent& event)
{
    if (!onAccessibilityHoverCallback_) {
        return;
    }
    AccessibilityHoverInfo hoverInfo;
    hoverInfo.SetTimeStamp(event.time);
    hoverInfo.SetDeviceId(event.deviceId);
    hoverInfo.SetSourceDevice(event.sourceType);
    hoverInfo.SetSourceTool(event.sourceTool);
    hoverInfo.SetPressedKeyCodes(event.pressedKeyCodes_);
    NG::PointF lastLocalPoint(event.x, event.y);
    NG::NGGestureRecognizer::Transform(lastLocalPoint, GetAttachedNode(), false,
        isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    hoverInfo.SetLocalLocation(Offset(localX, localY));
    hoverInfo.SetGlobalLocation(Offset(event.x, event.y));
    hoverInfo.SetScreenLocation(Offset(event.screenX, event.screenY));
    hoverInfo.SetGlobalDisplayLocation(Offset(event.globalDisplayX, event.globalDisplayY));
    hoverInfo.SetActionType(ConvertAccessibilityHoverAction(event.type));
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    hoverInfo.SetTargetDisplayId(event.targetDisplayId);
    // onAccessibilityHoverCallback_ may be overwritten in its invoke so we copy it first
    auto onAccessibilityHoverCallback = onAccessibilityHoverCallback_;
    onAccessibilityHoverCallback(isHovered, hoverInfo);
}

AccessibilityHoverAction HoverEventTarget::ConvertAccessibilityHoverAction(TouchType type)
{
    switch (type) {
        case TouchType::HOVER_ENTER:
            return AccessibilityHoverAction::HOVER_ENTER;
        case TouchType::HOVER_MOVE:
            return AccessibilityHoverAction::HOVER_MOVE;
        case TouchType::HOVER_EXIT:
            return AccessibilityHoverAction::HOVER_EXIT;
        case TouchType::HOVER_CANCEL:
            return AccessibilityHoverAction::HOVER_CANCEL;
        case TouchType::DOWN:
        case TouchType::UP:
        case TouchType::MOVE:
        case TouchType::CANCEL:
        case TouchType::PULL_DOWN:
        case TouchType::PULL_UP:
        case TouchType::PULL_MOVE:
        case TouchType::PULL_IN_WINDOW:
        case TouchType::PULL_OUT_WINDOW:
        case TouchType::PROXIMITY_IN:
        case TouchType::PROXIMITY_OUT:
        case TouchType::UNKNOWN:
            return AccessibilityHoverAction::UNKNOWN;
    }
}

bool MouseEventTarget::HandleMouseEvent(const MouseEvent& event)
{
    if (!onMouseCallback_) {
        return false;
    }
    MouseInfo info;
    info.SetPointerEvent(event.GetMouseEventPointerEvent());
    info.SetButton(event.button);
    info.SetAction(event.action);
    info.SetPullAction(event.pullAction);
    info.SetGlobalLocation(event.GetOffset());
    NG::PointF localPoint(event.x, event.y);
    bool needPostEvent = isPostEventResult_ || event.passThrough;
    NG::NGGestureRecognizer::Transform(
        localPoint, GetAttachedNode(), false, needPostEvent, event.postEventNodeId);
    auto localX = static_cast<float>(localPoint.GetX());
    auto localY = static_cast<float>(localPoint.GetY());
    info.SetLocalLocation(Offset(localX, localY));
    info.SetScreenLocation(event.GetScreenOffset());
    info.SetGlobalDisplayLocation(event.GetGlobalDisplayOffset());
    info.SetTimeStamp(event.time);
    info.SetDeviceId(event.deviceId);
    info.SetTargetDisplayId(event.targetDisplayId);
    info.SetSourceDevice(event.sourceType);
    info.SetSourceTool(event.sourceTool);
    info.SetTarget(GetEventTarget().value_or(EventTarget()));
    info.SetPressedKeyCodes(event.pressedKeyCodes_);
    info.SetRawDeltaX(event.rawDeltaX);
    info.SetRawDeltaY(event.rawDeltaY);
    info.SetPressedButtons(event.pressedButtonsArray);
    // onMouseCallback_ may be overwritten in its invoke so we copy it first
    auto onMouseCallback = onMouseCallback_;
    onMouseCallback(info);
    return info.IsStopPropagation();
}
std::shared_ptr<MMI::PointerEvent> MouseEvent::GetMouseEventPointerEvent() const
{
    return InputManager::CreatePointerEvent(pointerEvent);
}

MouseEvent MouseEvent::operator-(const Offset& offset) const
{
    MouseEvent mouseEvent;
    mouseEvent.x = x - offset.GetX();
    mouseEvent.x = x - offset.GetX();
    mouseEvent.y = y - offset.GetY();
    mouseEvent.z = z;
    mouseEvent.deltaX = deltaX;
    mouseEvent.deltaY = deltaY;
    mouseEvent.deltaZ = deltaZ;
    mouseEvent.scrollX = scrollX;
    mouseEvent.scrollY = scrollY;
    mouseEvent.scrollZ = scrollZ;
    mouseEvent.screenX = screenX - offset.GetX();
    mouseEvent.screenY = screenY - offset.GetY();
    mouseEvent.globalDisplayX = globalDisplayX - offset.GetX();
    mouseEvent.globalDisplayY = globalDisplayY - offset.GetY();
    mouseEvent.action = action;
    mouseEvent.button = button;
    mouseEvent.pressedButtons = pressedButtons;
    mouseEvent.time = time;
    mouseEvent.deviceId = deviceId;
    mouseEvent.targetDisplayId = targetDisplayId;
    mouseEvent.sourceType = sourceType;
    mouseEvent.sourceTool = sourceTool;
    mouseEvent.pointerEvent = pointerEvent;
    mouseEvent.originalId = originalId;
    mouseEvent.pressedKeyCodes_ = pressedKeyCodes_;
    mouseEvent.isInjected = isInjected;
    mouseEvent.isPrivacyMode = isPrivacyMode;
    mouseEvent.rawDeltaX = rawDeltaX;
    mouseEvent.rawDeltaY = rawDeltaY;
    mouseEvent.pressedButtonsArray = pressedButtonsArray;
    return mouseEvent;
}

const std::string& NativeEmbeadMouseInfo::GetEmbedId() const
{
    return embedId_;
}

const MouseInfo& NativeEmbeadMouseInfo::GetMouseEventInfo() const
{
    return mouseEvent_;
}
const RefPtr<MouseEventResult>& NativeEmbeadMouseInfo::GetResult() const
{
    return result_;
}
} // namespace OHOS::Ace
