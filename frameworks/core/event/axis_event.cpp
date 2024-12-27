/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/event/axis_event.h"

#include "base/input_manager/input_manager.h"

namespace OHOS::Ace {
AxisEvent AxisEvent::CreateScaleEvent(float scale) const
{
    if (NearZero(scale)) {
        return { id, x, y, screenX, screenY, verticalAxis, horizontalAxis, pinchAxisScale, rotateAxisAngle,
            isRotationEvent, action, time, deviceId, sourceType, sourceTool, pointerEvent, pressedCodes,
            targetDisplayId, originalId, isInjected };
    }
    return { id, x / scale, y / scale, screenX / scale, screenY / scale, verticalAxis, horizontalAxis, pinchAxisScale,
        rotateAxisAngle, isRotationEvent, action, time, deviceId, sourceType, sourceTool, pointerEvent, pressedCodes,
        targetDisplayId, originalId, isInjected };
}

Offset AxisEvent::GetOffset() const
{
    return Offset(x, y);
}

Offset AxisEvent::GetScreenOffset() const
{
    return Offset(screenX, screenY);
}

AxisDirection AxisEvent::GetDirection() const
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
bool AxisEvent::IsDirectionUp(AxisDirection direction)
{
    return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::UP));
}
bool AxisEvent::IsDirectionDown(AxisDirection direction)
{
    return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::DOWN));
}
bool AxisEvent::IsDirectionLeft(AxisDirection direction)
{
    return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::LEFT));
}
bool AxisEvent::IsDirectionRight(AxisDirection direction)
{
    return (static_cast<uint32_t>(direction) & static_cast<uint32_t>(AxisDirection::RIGHT));
}

Offset AxisEvent::ConvertToOffset(bool isShiftKeyPressed, bool hasDifferentDirectionGesture) const
{
    Offset result;
    if (sourceTool == SourceTool::MOUSE) {
        // Axis event is made by mouse.
        if (isShiftKeyPressed) {
            result = Offset(-verticalAxis, -horizontalAxis);
        } else {
            if (hasDifferentDirectionGesture) {
                result = Offset(-horizontalAxis, -verticalAxis);
            } else {
                result = Offset(-verticalAxis, -verticalAxis);
            }
        }
        return result * (LINE_HEIGHT_DESKTOP / MOUSE_WHEEL_DEGREES).ConvertToPx();
    }
    // Axis event is made by others. Include touch-pad.
    result = Offset(-horizontalAxis, -verticalAxis);
    return result;
}

// MMI has the different direction, need to check truth direction.
std::pair<float, float> AxisEvent::ConvertToSummationAxisValue(const AxisEvent& event) const
{
    return std::make_pair(event.horizontalAxis - horizontalAxis, event.verticalAxis - verticalAxis);
}

bool AxisEvent::HasKey(KeyCode expectCode) const
{
    auto curPressedCode = pressedCodes.rbegin();
    while (curPressedCode != pressedCodes.rend()) {
        if (expectCode == *curPressedCode) {
            return true;
        }
        ++curPressedCode;
    }
    return false;
}

AxisInfo::AxisInfo(const AxisEvent& event, const Offset& localLocation, const EventTarget& target)
    : BaseEventInfo("onAxis")
{
    action_ = event.action;
    verticalAxis_ = static_cast<float>(event.verticalAxis);
    horizontalAxis_ = static_cast<float>(event.horizontalAxis);
    pinchAxisScale_ = static_cast<float>(event.pinchAxisScale);
    rotateAxisAngle_ = static_cast<float>(event.rotateAxisAngle);
    isRotationEvent_ = event.isRotationEvent;
    globalLocation_ = event.GetOffset();
    localLocation_ = localLocation;
    screenLocation_ = Offset();
    SetTimeStamp(event.time);
    SetDeviceId(event.deviceId);
    SetSourceDevice(event.sourceType);
    SetTarget(target);
}

void AxisInfo::SetAction(AxisAction action)
{
    action_ = action;
}

AxisAction AxisInfo::GetAction() const
{
    return action_;
}

void AxisInfo::SetVerticalAxis(float axis)
{
    verticalAxis_ = axis;
}

float AxisInfo::GetVerticalAxis() const
{
    return verticalAxis_;
}

void AxisInfo::SetHorizontalAxis(float axis)
{
    horizontalAxis_ = axis;
}

float AxisInfo::GetHorizontalAxis() const
{
    return horizontalAxis_;
}

void AxisInfo::SetPinchAxisScale(float scale)
{
    pinchAxisScale_ = scale;
}

float AxisInfo::GetPinchAxisScale() const
{
    return pinchAxisScale_;
}

void AxisInfo::SetRotateAxisAngle(float angle)
{
    rotateAxisAngle_ = angle;
}

float AxisInfo::GetRotateAxisAngle() const
{
    return rotateAxisAngle_;
}

void AxisInfo::SetIsRotationEvent(bool rotationFlag)
{
    isRotationEvent_ = rotationFlag;
}

bool AxisInfo::GetIsRotationEvent() const
{
    return isRotationEvent_;
}

AxisInfo& AxisInfo::SetGlobalLocation(const Offset& globalLocation)
{
    globalLocation_ = globalLocation;
    return *this;
}
AxisInfo& AxisInfo::SetLocalLocation(const Offset& localLocation)
{
    localLocation_ = localLocation;
    return *this;
}

AxisInfo& AxisInfo::SetScreenLocation(const Offset& screenLocation)
{
    screenLocation_ = screenLocation;
    return *this;
}

const Offset& AxisInfo::GetScreenLocation() const
{
    return screenLocation_;
}

const Offset& AxisInfo::GetLocalLocation() const
{
    return localLocation_;
}
const Offset& AxisInfo::GetGlobalLocation() const
{
    return globalLocation_;
}

AxisEvent AxisInfo::ConvertToAxisEvent() const
{
    AxisEvent axisEvent;
    axisEvent.x = static_cast<float>(globalLocation_.GetX());
    axisEvent.y = static_cast<float>(globalLocation_.GetY());
    axisEvent.screenX = static_cast<float>(screenLocation_.GetX());
    axisEvent.screenY = static_cast<float>(screenLocation_.GetY());
    axisEvent.horizontalAxis = horizontalAxis_;
    axisEvent.verticalAxis = verticalAxis_;
    axisEvent.pinchAxisScale = pinchAxisScale_;
    axisEvent.rotateAxisAngle = rotateAxisAngle_;
    axisEvent.time = timeStamp_;
    axisEvent.localX = static_cast<float>(localLocation_.GetX());
    axisEvent.localY = static_cast<float>(localLocation_.GetY());
    return axisEvent;
}

void AxisEventTarget::SetOnAxisCallback(const OnAxisEventFunc& onAxisCallback)
{
    onAxisCallback_ = onAxisCallback;
}

void AxisEventTarget::SetCoordinateOffset(const NG::OffsetF& coordinateOffset)
{
    coordinateOffset_ = coordinateOffset;
}

void AxisEventTarget::SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl)
{
    getEventTargetImpl_ = getEventTargetImpl;
}

std::optional<EventTarget> AxisEventTarget::GetEventTarget() const
{
    if (getEventTargetImpl_) {
        return getEventTargetImpl_();
    }
    return std::nullopt;
}

void AxisEventTarget::SetFrameName(const std::string& frameName)
{
    frameName_ = frameName;
}

std::string AxisEventTarget::GetFrameName() const
{
    return frameName_;
}

bool AxisEventTarget::HandleAxisEvent(const AxisEvent& event)
{
    if (!onAxisCallback_) {
        return false;
    }
    Offset localLocation = Offset(
        event.GetOffset().GetX() - coordinateOffset_.GetX(), event.GetOffset().GetY() - coordinateOffset_.GetY());
    AxisInfo info = AxisInfo(event, localLocation, GetEventTarget().value_or(EventTarget()));
    info.SetScreenLocation(Offset(event.screenX, event.screenY));
    onAxisCallback_(info);
    return true;
}

bool AxisEventChecker::IsAxisEventSequenceCorrect(const AxisEvent& event)
{
    if (event.sourceType == SourceType::MOUSE) { // wheel on mouse or touch pad
        return IsGenericAxisEventSequenceCorrect(event);
    }

    // no check for other axis event, for example the axis event generated by joystick
    return true;
}

AxisAction AxisEventChecker::GetPreAction() const
{
    return preActionOld_;
}

bool AxisEventChecker::IsGenericAxisEventSequenceCorrect(const AxisEvent& event)
{
    preActionOld_ = preActionNew_;
    preActionNew_ = event.action;

    switch (event.action) {
        case AxisAction::BEGIN:
            // received begin but have not received end or cancel for pre event
            return preActionOld_ == AxisAction::NONE;
        case AxisAction::UPDATE:
            // received update but have not received
            return preActionOld_ == AxisAction::BEGIN || preActionOld_ == AxisAction::UPDATE;
        case AxisAction::END:
        case AxisAction::CANCEL:
            // received end or cancel
            preActionNew_ = AxisAction::NONE;
            return preActionOld_ == AxisAction::BEGIN || preActionOld_ == AxisAction::UPDATE;
        default:
            return false;
    }
}

} // namespace OHOS::Ace