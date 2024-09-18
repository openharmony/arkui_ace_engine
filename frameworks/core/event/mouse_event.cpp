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

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
bool HoverEventTarget::HandleHoverEvent(bool isHovered, const MouseEvent& event)
{
    if (!onHoverEventCallback_) {
        return false;
    }
    HoverInfo hoverInfo;
    hoverInfo.SetTimeStamp(event.time);
    hoverInfo.SetDeviceId(event.deviceId);
    hoverInfo.SetSourceDevice(event.sourceType);
    hoverInfo.SetSourceTool(event.sourceTool);
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    hoverInfo.SetPressedKeyCodes(event.pressedKeyCodes_);
    onHoverEventCallback_(isHovered, hoverInfo);
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
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    onPenHoverEventCallback_(isHovered, hoverInfo);
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
    hoverInfo.SetActionType(ConvertAccessibilityHoverAction(event.type));
    hoverInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    onAccessibilityHoverCallback_(isHovered, hoverInfo);
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
} // namespace OHOS::Ace
