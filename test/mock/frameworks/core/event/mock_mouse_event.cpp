/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace {
bool HoverEventTarget::HandleHoverEvent(bool isHovered, const MouseEvent& event)
{
    return false;
}

bool HoverEventTarget::HandlePenHoverEvent(bool isHovered, const TouchEvent& event)
{
    return false;
}

bool HoverEventTarget::HandlePenHoverMoveEvent(const TouchEvent& event)
{
    return false;
}

void HoverEventTarget::HandleAccessibilityHoverEvent(bool isHovered, const TouchEvent& event)
{
}

AccessibilityHoverAction HoverEventTarget::ConvertAccessibilityHoverAction(TouchType type)
{
    return AccessibilityHoverAction::UNKNOWN;
}

bool MouseEventTarget::HandleMouseEvent(const MouseEvent& event)
{
    return false;
}
MouseHistoricalPoint MouseEventTarget::CreateMouseHistoricalPoint(const MouseEvent& event, bool needPostEvent) const
{
    return {};
}
std::shared_ptr<MMI::PointerEvent> MouseEvent::GetMouseEventPointerEvent() const
{
    return nullptr;
}

MouseEvent MouseEvent::operator-(const Offset& offset) const
{
    MouseEvent mouseEvent;
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
    mouseEvent.isRightButtonEventFromDoulbeTap = isRightButtonEventFromDoulbeTap;
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

MouseEvent MouseInfo::ConvertToMouseEvent() const
{
    return {};
}

void HoverEffectTarget::SetHoverNode(const WeakPtr<NG::FrameNode>& node)
{
    hoverNode_ = node;
}

WeakPtr<NG::FrameNode> HoverEffectTarget::GetHoverNode() const
{
    return hoverNode_;
}

MouseEvent MouseEvent::CloneWith(float scale) const
{
    return {};
}

MouseEvent MouseEvent::CreateScaleEvent(float scale) const
{
    return {};
}

TouchEvent MouseEvent::CreateTouchPoint() const
{
    return {};
}
} // namespace OHOS::Ace
