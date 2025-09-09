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

#include "foundation/arkui/ace_engine/interfaces/native/native_gesture.h"
#include "core/interfaces/native/node/node_gesture_modifier.h"
#include <securec.h>

#include "base/error/error_code.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/node/touch_event_convertor.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "interfaces/native/event/ui_input_event_impl.h"
#include "node_drag_modifier.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t MAX_POINTS = 10;
    constexpr int32_t API_TARGET_VERSION_MASK = 1000;
}
ArkUIGesture* createPanGesture(
    ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 distance, bool limitFingerCount, void* userData = nullptr)
{
    PanDirection panDirection;
    switch (direction) {
        case ArkUI_GESTURE_DIRECTION_ALL:
            panDirection.type = panDirection.ALL;
            break;
        case ArkUI_GESTURE_DIRECTION_NONE:
            panDirection.type = panDirection.NONE;
            break;
        case ArkUI_GESTURE_DIRECTION_LEFT:
            panDirection.type = panDirection.LEFT;
            break;
        case ArkUI_GESTURE_DIRECTION_RIGHT:
            panDirection.type = panDirection.RIGHT;
            break;
        case ArkUI_GESTURE_DIRECTION_HORIZONTAL:
            panDirection.type = panDirection.HORIZONTAL;
            break;
        case ArkUI_GESTURE_DIRECTION_UP:
            panDirection.type = panDirection.UP;
            break;
        case  ArkUI_GESTURE_DIRECTION_DOWN:
            panDirection.type = panDirection.DOWN;
            break;
        case ArkUI_GESTURE_DIRECTION_VERTICAL:
            panDirection.type = panDirection.VERTICAL;
            break;
        default:
            panDirection.type = panDirection.NONE;
            break;
    }
    auto panGestureObject = AceType::MakeRefPtr<PanGesture>(fingers, panDirection, distance, limitFingerCount);
    panGestureObject->SetUserData(userData);
    panGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(panGestureObject));
}

ArkUIGesture* createTapGesture(
    ArkUI_Int32 count, ArkUI_Int32 fingers, bool limitFingerCount = false, void* userData = nullptr)
{
    auto tapGestureObject = AceType::MakeRefPtr<TapGesture>(
        count, fingers, std::numeric_limits<double>::infinity(), limitFingerCount);
    tapGestureObject->SetUserData(userData);
    tapGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(tapGestureObject));
}

ArkUIGesture* createTapGestureWithDistanceThreshold(
    ArkUI_Int32 count, ArkUI_Int32 fingers, double distanceThreshold, bool limitFingerCount = false,
    void* userData = nullptr)
{
    auto distanceThresholdDimension = Dimension(distanceThreshold, DimensionUnit::VP);
    auto tapGestureObject = AceType::MakeRefPtr<TapGesture>(
        count, fingers, distanceThresholdDimension, limitFingerCount);
    tapGestureObject->SetUserData(userData);
    tapGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(tapGestureObject));
}

ArkUIGesture* createLongPressGesture(
    ArkUI_Int32 fingers, bool repeat, ArkUI_Int32 duration, bool limitFingerCount = false, void* userData = nullptr)
{
    auto longPressGestureObject = AceType::MakeRefPtr<LongPressGesture>(
        fingers, repeat, duration, false, false, limitFingerCount);
    longPressGestureObject->SetUserData(userData);
    longPressGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(longPressGestureObject));
}

ArkUIGesture* createPinchGesture(
    ArkUI_Int32 fingers, ArkUI_Float64 distance, bool limitFingerCount = false, void* userData = nullptr)
{
    auto pinchGestureObject = AceType::MakeRefPtr<PinchGesture>(fingers, distance, limitFingerCount);
    pinchGestureObject->SetUserData(userData);
    pinchGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(pinchGestureObject));
}

ArkUIGesture* createRotationGesture(
    ArkUI_Int32 fingers, ArkUI_Float64 angle, bool limitFingerCount = false, void* userData = nullptr)
{
    auto rotationGestureObject = AceType::MakeRefPtr<RotationGesture>(fingers, angle, limitFingerCount);
    rotationGestureObject->SetUserData(userData);
    rotationGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(rotationGestureObject));
}

ArkUIGesture* createSwipeGesture(
    ArkUI_Int32 fingers, ArkUI_Int32 directions, ArkUI_Float64 speed, bool limitFingerCount = false,
    void* userData = nullptr)
{
    SwipeDirection swipeDirection{SwipeDirection::NONE};
    if (static_cast<uint32_t>(directions) & ArkUI_GESTURE_DIRECTION_HORIZONTAL) {
        swipeDirection.type = SwipeDirection::HORIZONTAL;
    }
    if (static_cast<uint32_t>(directions) & ArkUI_GESTURE_DIRECTION_VERTICAL) {
        swipeDirection.type += SwipeDirection::VERTICAL;
    }
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingers, swipeDirection, speed, limitFingerCount);
    swipeGestureObject->SetUserData(userData);
    swipeGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(swipeGestureObject));
}

ArkUIGesture* createSwipeGestureByModifier(
    ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 speed, bool limitFingerCount = false)
{
    SwipeDirection swipeDirection{ SwipeDirection::NONE};
    switch (direction) {
        case ArkUI_SWIPE_GESTURE_DIRECTION_ALL:
            swipeDirection.type = SwipeDirection::ALL;
            break;
        case ArkUI_SWIPE_GESTURE_DIRECTION_NONE:
            swipeDirection.type = SwipeDirection::NONE;
            break;
        case ArkUI_SWIPE_GESTURE_DIRECTION_HORIZONTAL:
            swipeDirection.type = SwipeDirection::HORIZONTAL;
            break;
        case ArkUI_SWIPE_GESTURE_DIRECTION_VERTICAL:
            swipeDirection.type = SwipeDirection::VERTICAL;
            break;
        default:
            swipeDirection.type = SwipeDirection::NONE;
            break;
    }
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingers, swipeDirection, speed, limitFingerCount);
    swipeGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(swipeGestureObject));
}

ArkUIGesture* createGestureGroup(ArkUI_Int32 mode)
{
    auto gestureMode = static_cast<GestureMode>(mode);
    auto gestureGroupObject = AceType::MakeRefPtr<GestureGroup>(gestureMode);
    gestureGroupObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(gestureGroupObject));
}

void addGestureToGestureGroup(ArkUIGesture* group, ArkUIGesture* child)
{
    auto* gestureGroup = reinterpret_cast<GestureGroup*>(group);
    auto* childGesture = reinterpret_cast<Gesture*>(child);
    gestureGroup->AddGesture(AceType::Claim(childGesture));
}

void addGestureToGestureGroupWithRefCountDecrease(ArkUIGesture* group, ArkUIGesture* child)
{
    auto* gestureGroup = reinterpret_cast<GestureGroup*>(group);
    auto* childGesture = reinterpret_cast<Gesture*>(child);
    gestureGroup->AddGesture(AceType::Claim(childGesture));
    // Gesture ptr ref count is not decrease, so need to decrease after attach to gestureEventHub.
    childGesture->DecRefCount();
}

void removeGestureFromGestureGroup(ArkUIGesture* group, ArkUIGesture* child)
{
    auto* gestureGroup = reinterpret_cast<GestureGroup*>(group);
    auto* childGesture = reinterpret_cast<Gesture*>(child);
    gestureGroup->RemoveGesture(AceType::Claim(childGesture));
}

void dispose(ArkUIGesture* recognizer)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(recognizer);
    gestureRef->SetDisposeTag(true);
    gestureRef->DecRefCount();
}

void ConvertTouchPointsToPoints(GestureEvent& info, std::vector<TouchPoint>& touchPointes,
    std::array<ArkUITouchPoint, MAX_POINTS>& points)
{
    if (touchPointes.empty()) {
        return;
    }
    size_t i = 0;
    auto fingureIterator = std::begin(info.GetFingerList());
    auto fingureEnd = std::end(info.GetFingerList());
    for (auto& touchPoint : touchPointes) {
        if (i >= MAX_POINTS) {
            break;
        }
        points[i].id = touchPoint.id;
        points[i].nodeX = fingureIterator == fingureEnd ? 0.0f : fingureIterator->localLocation_.GetX();
        points[i].nodeY = fingureIterator == fingureEnd ? 0.0f : fingureIterator->localLocation_.GetY();
        points[i].windowX = fingureIterator == fingureEnd ? 0.0f : fingureIterator->globalLocation_.GetX();
        points[i].windowY = fingureIterator == fingureEnd ? 0.0f : fingureIterator->globalLocation_.GetY();
        points[i].screenX = touchPoint.screenX;
        points[i].screenY = touchPoint.screenY;
        points[i].globalDisplayX = touchPoint.globalDisplayX;
        points[i].globalDisplayY = touchPoint.globalDisplayY;
        points[i].contactAreaWidth = touchPoint.size;
        points[i].contactAreaHeight = touchPoint.size;
        points[i].pressure = touchPoint.force;
        points[i].tiltX = touchPoint.tiltX.value_or(0.0f);
        points[i].tiltY = touchPoint.tiltY.value_or(0.0f);
        points[i].rollAngle = touchPoint.rollAngle.value_or(0.0f);
        points[i].pressedTime = touchPoint.downTime.time_since_epoch().count();
        points[i].toolType = static_cast<int32_t>(touchPoint.sourceTool);
        points[i].operatingHand = fingureIterator == fingureEnd ? 0 : fingureIterator->operatingHand_;
        i++;
        if (fingureIterator != fingureEnd) {
            fingureIterator++;
        }
    }
}

void ConvertIMMEventToTouchEvent(GestureEvent& info, ArkUITouchEvent& touchEvent,
    std::array<ArkUITouchPoint, MAX_POINTS>& points)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    auto tempTouchEvent = NG::ConvertToTouchEvent(info.GetPointerEvent());
    const auto& targetLocalOffset = info.GetTarget().area.GetOffset();
    const auto& targetOrigin = info.GetTarget().origin;
    // width height x y globalx globaly
    touchEvent.targetPositionX = targetLocalOffset.GetX().ConvertToPx();
    touchEvent.targetPositionY = targetLocalOffset.GetY().ConvertToPx();
    touchEvent.targetGlobalPositionX = targetOrigin.GetX().ConvertToPx() + targetLocalOffset.GetX().ConvertToPx();
    touchEvent.targetGlobalPositionY = targetOrigin.GetY().ConvertToPx() + targetLocalOffset.GetY().ConvertToPx();
    touchEvent.width = info.GetTarget().area.GetWidth().ConvertToPx();
    touchEvent.height = info.GetTarget().area.GetHeight().ConvertToPx();
    // deviceid
    touchEvent.deviceId = info.GetDeviceId();
    // modifierkeystates
    touchEvent.modifierKeyState = NodeModifier::CalculateModifierKeyState(info.GetPressedKeyCodes());
    touchEvent.action = info.GetLastAction().value_or(static_cast<int32_t>(tempTouchEvent.type));
    touchEvent.sourceType = static_cast<int32_t>(tempTouchEvent.sourceType);
    touchEvent.timeStamp = tempTouchEvent.time.time_since_epoch().count();
    touchEvent.actionTouchPoint.pressure = tempTouchEvent.force;
    ConvertTouchPointsToPoints(info, tempTouchEvent.pointers, points);
    if (tempTouchEvent.pointers.size() > 0) {
        touchEvent.touchPointes = &(points[0]);
        touchEvent.actionTouchPoint.nodeX = touchEvent.touchPointes[0].nodeX;
        touchEvent.actionTouchPoint.nodeY = touchEvent.touchPointes[0].nodeY;
        touchEvent.actionTouchPoint.windowX = touchEvent.touchPointes[0].windowX;
        touchEvent.actionTouchPoint.windowY = touchEvent.touchPointes[0].windowY;
        touchEvent.actionTouchPoint.screenX = touchEvent.touchPointes[0].screenX;
        touchEvent.actionTouchPoint.screenY = touchEvent.touchPointes[0].screenY;
        touchEvent.actionTouchPoint.globalDisplayX = touchEvent.touchPointes[0].globalDisplayX;
        touchEvent.actionTouchPoint.globalDisplayY = touchEvent.touchPointes[0].globalDisplayY;
        touchEvent.actionTouchPoint.toolType = touchEvent.touchPointes[0].toolType;
        touchEvent.actionTouchPoint.operatingHand = touchEvent.touchPointes[0].operatingHand;
    }
    touchEvent.touchPointSize = tempTouchEvent.pointers.size() < MAX_POINTS ?
    tempTouchEvent.pointers.size() : MAX_POINTS;
    touchEvent.targetDisplayId = info.GetTargetDisplayId();
}

SourceTool ConvertCInputEventToolTypeToSourceTool(int32_t cInputEventToolType)
{
    switch (cInputEventToolType) {
        case static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_FINGER):
            return SourceTool::FINGER;
        case static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_PEN):
            return SourceTool::PEN;
        case static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_MOUSE):
            return SourceTool::MOUSE;
        case static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD):
            return SourceTool::TOUCHPAD;
        case static_cast<int32_t>(UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK):
            return SourceTool::JOYSTICK;
        default:
            return SourceTool::UNKNOWN;
    }
}

ArkUI_UIInputEvent_Type ConvertInputEventTypeToArkuiUIInputEventType(InputEventType type)
{
    switch (type) {
        case InputEventType::TOUCH_SCREEN:
            return ARKUI_UIINPUTEVENT_TYPE_TOUCH;
        case InputEventType::MOUSE_BUTTON:
            return ARKUI_UIINPUTEVENT_TYPE_MOUSE;
        case InputEventType::AXIS:
            return ARKUI_UIINPUTEVENT_TYPE_AXIS;
        case InputEventType::KEYBOARD:
            return ARKUI_UIINPUTEVENT_TYPE_KEY;
        default:
            return ARKUI_UIINPUTEVENT_TYPE_UNKNOWN;
    }
}

void GetGestureEvent(ArkUIAPIEventGestureAsyncEvent& ret, GestureEvent& info)
{
    ret.repeat = info.GetRepeat();
    ret.velocityX = info.GetVelocity().GetVelocityX();
    ret.velocityY = info.GetVelocity().GetVelocityY();
    ret.velocity = info.GetVelocity().GetVelocityValue();
    ret.x = info.GetOffsetX();
    ret.y = info.GetOffsetY();
    ret.angle = info.GetAngle();
    ret.scale = info.GetScale();
    ret.pinchCenterX = info.GetPinchCenter().GetX();
    ret.pinchCenterY = info.GetPinchCenter().GetY();
    ret.speed = info.GetSpeed();
    ret.source = static_cast<int32_t>(info.GetSourceDevice());
    ret.targetDisplayId = info.GetTargetDisplayId();
    ret.inputEventType = ConvertInputEventTypeToArkuiUIInputEventType(info.GetInputEventType());
}

int32_t GetPointerEventAction(InputEventType type, std::shared_ptr<MMI::PointerEvent> pointerEvent)
{
    if (type == InputEventType::AXIS) {
        CHECK_NULL_RETURN(pointerEvent, static_cast<int32_t>(AxisAction::NONE));
        return static_cast<int32_t>(NG::GetAxisEventType(pointerEvent));
    }
    if (type == InputEventType::MOUSE_BUTTON) {
        CHECK_NULL_RETURN(pointerEvent, static_cast<int32_t>(MouseAction::NONE));
        return static_cast<int32_t>(NG::GetMouseEventType(pointerEvent));
    }
    if (type == InputEventType::KEYBOARD) {
        return static_cast<int32_t>(KeyAction::DOWN);
    }
    CHECK_NULL_RETURN(pointerEvent, static_cast<int32_t>(TouchType::UNKNOWN));
    return static_cast<int32_t>(NG::GetTouchEventType(pointerEvent));
}

void GetBaseGestureEvent(ArkUIAPIEventGestureAsyncEvent* ret, ArkUITouchEvent& rawInputEvent,
    const std::shared_ptr<BaseGestureEvent>& info, std::array<ArkUITouchPoint, MAX_POINTS>& points)
{
    rawInputEvent.sourceType = static_cast<ArkUI_Int32>(info->GetSourceDevice());
    rawInputEvent.timeStamp = info->GetTimeStamp().time_since_epoch().count();
    rawInputEvent.action =
        info->GetLastAction().value_or(GetPointerEventAction(info->GetRawInputEventType(), info->GetRawInputEvent()));
    rawInputEvent.deviceId = info->GetRawInputDeviceId();
    rawInputEvent.actionTouchPoint.tiltX = info->GetTiltX().value_or(0.0f);
    rawInputEvent.actionTouchPoint.tiltY = info->GetTiltY().value_or(0.0f);
    rawInputEvent.actionTouchPoint.rollAngle = info->GetRollAngle().value_or(0.0f);
    rawInputEvent.actionTouchPoint.toolType = static_cast<ArkUI_Int32>(info->GetSourceTool());
    rawInputEvent.actionTouchPoint.pressure = info->GetForce();
    auto fingerList = info->GetFingerList();
    auto fingureIterator = std::begin(fingerList);
    rawInputEvent.targetDisplayId = info->GetTargetDisplayId();

    for (size_t i = 0; i < fingerList.size(); i++) {
        points[i].id = fingureIterator->fingerId_;
        points[i].windowX = fingureIterator->globalLocation_.GetX();
        points[i].windowY = fingureIterator->globalLocation_.GetY();
        points[i].nodeX = fingureIterator->localLocation_.GetX();
        points[i].nodeY = fingureIterator->localLocation_.GetY();
        points[i].tiltX = rawInputEvent.actionTouchPoint.tiltX;
        points[i].tiltY = rawInputEvent.actionTouchPoint.tiltY;
        points[i].rollAngle = rawInputEvent.actionTouchPoint.rollAngle;
        fingureIterator++;
    }
    rawInputEvent.touchPointes = &(points[0]);
    rawInputEvent.touchPointSize = fingerList.size();
    ret->rawPointerEvent = &rawInputEvent;
}

void GetUniqueGestureEvent(ArkUIAPIEventGestureAsyncEvent* ret, GestureTypeName typeName,
    const std::shared_ptr<BaseGestureEvent>& info)
{
    switch (typeName) {
        case OHOS::Ace::GestureTypeName::LONG_PRESS_GESTURE: {
            auto longPressGestureEvent = TypeInfoHelper::DynamicCast<LongPressGestureEvent>(info.get());
            if (longPressGestureEvent) {
                ret->repeat = longPressGestureEvent->GetRepeat();
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::PAN_GESTURE: {
            auto panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(info.get());
            if (panGestureEvent) {
                ret->x = panGestureEvent->GetOffsetX();
                ret->y = panGestureEvent->GetOffsetY();
                ret->velocityX = panGestureEvent->GetVelocity().GetVelocityX();
                ret->velocityY = panGestureEvent->GetVelocity().GetVelocityY();
                ret->velocity = panGestureEvent->GetVelocity().GetVelocityValue();
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::PINCH_GESTURE: {
            auto pinchGestureEvent = TypeInfoHelper::DynamicCast<PinchGestureEvent>(info.get());
            if (pinchGestureEvent) {
                ret->scale = pinchGestureEvent->GetScale();
                ret->pinchCenterX = pinchGestureEvent->GetPinchCenter().GetX();
                ret->pinchCenterY = pinchGestureEvent->GetPinchCenter().GetY();
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::ROTATION_GESTURE: {
            auto rotationGestureEvent = TypeInfoHelper::DynamicCast<RotationGestureEvent>(info.get());
            if (rotationGestureEvent) {
                ret->angle = rotationGestureEvent->GetAngle();
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::SWIPE_GESTURE: {
            auto swipeGestureEvent = TypeInfoHelper::DynamicCast<SwipeGestureEvent>(info.get());
            if (swipeGestureEvent) {
                ret->angle = swipeGestureEvent->GetAngle();
                ret->speed = swipeGestureEvent->GetSpeed();
            }
            break;
        }
        default:
            break;
    }
}

void ConvertIMMEventToMouseEvent(GestureEvent& info, ArkUIMouseEvent& mouseEvent)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    MouseEvent tempMouseEvent;
    NG::ConvertToMouseEvent(tempMouseEvent, info.GetPointerEvent());
    auto fingureBegin = std::begin(info.GetFingerList());
    auto fingureEnd = std::end(info.GetFingerList());
    const auto& targetLocalOffset = info.GetTarget().area.GetOffset();
    const auto& targetOrigin = info.GetTarget().origin;
    // width height x y globalx globaly
    mouseEvent.targetPositionX = targetLocalOffset.GetX().ConvertToPx();
    mouseEvent.targetPositionY = targetLocalOffset.GetY().ConvertToPx();
    mouseEvent.targetGlobalPositionX = targetOrigin.GetX().ConvertToPx() + targetLocalOffset.GetX().ConvertToPx();
    mouseEvent.targetGlobalPositionY = targetOrigin.GetY().ConvertToPx() + targetLocalOffset.GetY().ConvertToPx();
    mouseEvent.width = info.GetTarget().area.GetWidth().ConvertToPx();
    mouseEvent.height = info.GetTarget().area.GetHeight().ConvertToPx();
    // deviceid
    mouseEvent.deviceId = info.GetDeviceId();
    // modifierkeystates
    mouseEvent.modifierKeyState = NodeModifier::CalculateModifierKeyState(info.GetPressedKeyCodes());
    mouseEvent.action = info.GetLastAction().value_or(static_cast<int32_t>(tempMouseEvent.action));
    mouseEvent.sourceType = static_cast<int32_t>(tempMouseEvent.sourceType);
    mouseEvent.timeStamp = tempMouseEvent.time.time_since_epoch().count();
    mouseEvent.actionTouchPoint.pressure = 0.0f;
    mouseEvent.actionTouchPoint.nodeX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetX();
    mouseEvent.actionTouchPoint.nodeY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetY();
    mouseEvent.actionTouchPoint.windowX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetX();
    mouseEvent.actionTouchPoint.windowY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetY();
    mouseEvent.actionTouchPoint.screenX = tempMouseEvent.screenX;
    mouseEvent.actionTouchPoint.screenY = tempMouseEvent.screenY;
    mouseEvent.actionTouchPoint.globalDisplayX = tempMouseEvent.globalDisplayX;
    mouseEvent.actionTouchPoint.globalDisplayY = tempMouseEvent.globalDisplayY;
    mouseEvent.actionTouchPoint.toolType = static_cast<int32_t>(tempMouseEvent.sourceTool);
    mouseEvent.targetDisplayId = info.GetTargetDisplayId();
}

void ConvertIMMEventToAxisEvent(GestureEvent& info, ArkUIAxisEvent& axisEvent)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    AxisEvent tempAxisEvent;
    NG::ConvertToAxisEvent(tempAxisEvent, info.GetPointerEvent());
    auto fingureBegin = std::begin(info.GetFingerList());
    auto fingureEnd = std::end(info.GetFingerList());
    const auto& targetLocalOffset = info.GetTarget().area.GetOffset();
    const auto& targetOrigin = info.GetTarget().origin;
    // width height x y globalx globaly
    axisEvent.targetPositionX = targetLocalOffset.GetX().ConvertToPx();
    axisEvent.targetPositionY = targetLocalOffset.GetY().ConvertToPx();
    axisEvent.targetGlobalPositionX = targetOrigin.GetX().ConvertToPx() + targetLocalOffset.GetX().ConvertToPx();
    axisEvent.targetGlobalPositionY = targetOrigin.GetY().ConvertToPx() + targetLocalOffset.GetY().ConvertToPx();
    axisEvent.width = info.GetTarget().area.GetWidth().ConvertToPx();
    axisEvent.height = info.GetTarget().area.GetHeight().ConvertToPx();
    // deviceid
    axisEvent.deviceId = info.GetDeviceId();
    // modifierkeystates
    axisEvent.modifierKeyState = NodeModifier::CalculateModifierKeyState(info.GetPressedKeyCodes());
    axisEvent.action = info.GetLastAction().value_or(static_cast<int32_t>(tempAxisEvent.action));
    axisEvent.sourceType = static_cast<int32_t>(tempAxisEvent.sourceType);
    axisEvent.timeStamp = tempAxisEvent.time.time_since_epoch().count();
    axisEvent.horizontalAxis = tempAxisEvent.horizontalAxis;
    axisEvent.verticalAxis = tempAxisEvent.verticalAxis;
    axisEvent.pinchAxisScale = tempAxisEvent.pinchAxisScale;
    axisEvent.actionTouchPoint.nodeX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetX();
    axisEvent.actionTouchPoint.nodeY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetY();
    axisEvent.actionTouchPoint.windowX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetX();
    axisEvent.actionTouchPoint.windowY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetY();
    axisEvent.actionTouchPoint.screenX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->screenLocation_.GetX();
    axisEvent.actionTouchPoint.screenY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->screenLocation_.GetY();
    axisEvent.actionTouchPoint.globalDisplayX =
        fingureBegin == fingureEnd ? 0.0 : fingureBegin->globalDisplayLocation_.GetX();
    axisEvent.actionTouchPoint.globalDisplayY =
        fingureBegin == fingureEnd ? 0.0 : fingureBegin->globalDisplayLocation_.GetY();
    axisEvent.actionTouchPoint.toolType = static_cast<int32_t>(tempAxisEvent.sourceTool);
    axisEvent.targetDisplayId = info.GetTargetDisplayId();
}

void SendGestureEvent(GestureEvent& info, int32_t eventKind, void* extraParam)
{
    ArkUINodeEvent eventData;
    eventData.kind = GESTURE_ASYNC_EVENT;
    eventData.nodeId = 0;
    eventData.extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
    eventData.gestureAsyncEvent.subKind = eventKind;
    eventData.apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion() % API_TARGET_VERSION_MASK;
    GetGestureEvent(eventData.gestureAsyncEvent, info);
    if (info.GetInputEventType() == InputEventType::AXIS) {
        ArkUIAxisEvent rawInputEvent;
        ConvertIMMEventToAxisEvent(info, rawInputEvent);
        eventData.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
        SendArkUISyncEvent(&eventData);
        return;
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        ArkUIMouseEvent rawInputEvent;
        ConvertIMMEventToMouseEvent(info, rawInputEvent);
        eventData.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
        SendArkUISyncEvent(&eventData);
        return;
    }
    if (info.GetInputEventType() == InputEventType::KEYBOARD) {
        ArkUIKeyEvent rawInputEvent;
        // only support deviceId when trigger by key
        rawInputEvent.deviceId = info.GetDeviceId();
        eventData.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
        SendArkUISyncEvent(&eventData);
        return;
    }
    ArkUITouchEvent rawInputEvent;
    std::array<ArkUITouchPoint, MAX_POINTS> points;
    ConvertIMMEventToTouchEvent(info, rawInputEvent, points);
    eventData.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
    SendArkUISyncEvent(&eventData);
}

void registerGestureEvent(ArkUIGesture* gesture, ArkUI_Uint32 actionTypeMask, void* extraParam)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(gesture);
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_ACCEPT) {
        auto onActionAccept = [extraParam](GestureEvent& info) {
            SendGestureEvent(info, static_cast<int32_t>(ON_ACTION_START), extraParam);
        };
        gestureRef->SetOnActionId(onActionAccept);
        gestureRef->SetOnActionStartId(onActionAccept);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_UPDATE) {
        auto onActionUpdate = [extraParam](GestureEvent& info) {
            SendGestureEvent(info, static_cast<int32_t>(ON_ACTION_UPDATE), extraParam);
        };
        gestureRef->SetOnActionUpdateId(onActionUpdate);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_END) {
        auto onActionEnd = [extraParam](GestureEvent& info) {
            SendGestureEvent(info, static_cast<int32_t>(ON_ACTION_END), extraParam);
        };
        gestureRef->SetOnActionEndId(onActionEnd);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_CANCEL) {
        auto onActionCancel = [extraParam](GestureEvent& info) {
            SendGestureEvent(info, static_cast<int32_t>(ON_ACTION_CANCEL), extraParam);
        };
        gestureRef->SetOnActionCancelId(onActionCancel);
    }
}

void registerGestureEventExt(ArkUIGesture* gesture, ArkUI_Uint32 actionTypeMask,
    GestrueFunction* gestrueFunction, void* gestureData)
{
    CHECK_NULL_VOID(gestrueFunction);
    Gesture* gestureRef = reinterpret_cast<Gesture*>(gesture);
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_ACCEPT) {
        auto onActionAccept = [gestrueFunction, gestureData](GestureEvent& info) {
            gestrueFunction->acceptFunction(gestureData);
        };
        gestureRef->SetOnActionId(onActionAccept);
        gestureRef->SetOnActionStartId(onActionAccept);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_UPDATE) {
        auto onActionUpdate = [gestrueFunction, gestureData](GestureEvent& info) {
            gestrueFunction->updateFunction(gestureData);
        };
        gestureRef->SetOnActionUpdateId(onActionUpdate);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_END) {
        auto onActionEnd = [gestrueFunction, gestureData](GestureEvent& info) {
            gestrueFunction->endFunction(gestureData);
        };
        gestureRef->SetOnActionEndId(onActionEnd);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_CANCEL) {
        auto onActionCancel = [gestrueFunction, gestureData](GestureEvent& info) {
            gestrueFunction->cancelFunction(gestureData);
        };
        gestureRef->SetOnActionCancelId(onActionCancel);
    }
}

void addGestureToNode(ArkUINodeHandle node, ArkUIGesture* gesture, ArkUI_Int32 priorityNum, ArkUI_Int32 mask)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));

    GesturePriority priority = GesturePriority::Low;
    if (priorityNum > static_cast<int32_t>(GesturePriority::Begin) &&
            priorityNum < static_cast<int32_t>(GesturePriority::End)) {
        priority = static_cast<GesturePriority>(priorityNum);
    }
    gesturePtr->SetPriority(priority);

    GestureMask gestureMask = GestureMask::Normal;
    if (mask > static_cast<int32_t>(GestureMask::Begin) &&
        mask < static_cast<int32_t>(GestureMask::End)) {
        gestureMask = static_cast<GestureMask>(mask);
    }
    gesturePtr->SetGestureMask(gestureMask);
    gestureHub->AttachGesture(gesturePtr);
    GestureEventFunc clickEvent = NG::GetTapGestureEventFunc(gesturePtr);
    if (clickEvent) {
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusable(true, false);
        focusHub->SetOnClickCallback(std::move(clickEvent));
    }
}

void addGestureToNodeWithRefCountDecrease(
    ArkUINodeHandle node, ArkUIGesture* gesture, ArkUI_Int32 priorityNum, ArkUI_Int32 mask)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));

    GesturePriority priority = GesturePriority::Low;
    if (priorityNum > static_cast<int32_t>(GesturePriority::Begin) &&
            priorityNum < static_cast<int32_t>(GesturePriority::End)) {
        priority = static_cast<GesturePriority>(priorityNum);
    }
    gesturePtr->SetPriority(priority);

    GestureMask gestureMask = GestureMask::Normal;
    if (mask > static_cast<int32_t>(GestureMask::Begin) &&
        mask < static_cast<int32_t>(GestureMask::End)) {
        gestureMask = static_cast<GestureMask>(mask);
    }
    gesturePtr->SetGestureMask(gestureMask);
    gestureHub->AttachGesture(gesturePtr);
    // Gesture ptr ref count is not decrease, so need to decrease after attach to gestureEventHub.
    GestureEventFunc clickEvent = NG::GetTapGestureEventFunc(gesturePtr);
    if (clickEvent) {
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusable(true, false);
        focusHub->SetOnClickCallback(std::move(clickEvent));
    }
    gesturePtr->DecRefCount();
}

void removeGestureFromNode(ArkUINodeHandle node, ArkUIGesture* gesture)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    gestureHub->RemoveGesture(gesturePtr);
}

void removeGestureFromNodeByTag(ArkUINodeHandle node, ArkUI_CharPtr gestureTag)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    std::string tag(gestureTag);
    gestureHub->RemoveGesturesByTag(tag);
}

void clearGestures(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    gestureHub->ClearModifierGesture();
}

// <fingerid, iterator of touchTestResults in eventManager>
using TouchRecognizerTarget = std::vector<std::pair<int32_t, TouchTestResult::iterator>>;
using TouchRecognizerMap = std::map<TouchEventTarget*, TouchRecognizerTarget>;

bool IsFingerCollectedByTarget(TouchRecognizerTarget& target, int32_t fingerId)
{
    for (const auto& item : target) {
        if (item.first == fingerId) {
            return true;
        }
    }
    return false;
}

void CollectTouchEventTarget(
    TouchRecognizerMap& dict, std::list<RefPtr<TouchEventTarget>>& targets, FrameNode* borderNode, int32_t fingerId)
{
    for (auto iter = targets.begin(); iter != targets.end(); ++iter) {
        auto& target = *iter;
        if (AceType::DynamicCast<NG::NGGestureRecognizer>(target)) {
            continue;
        }
        auto targetPtr = AceType::RawPtr(target);
        if (dict.find(targetPtr) != dict.end() && IsFingerCollectedByTarget(dict[AceType::RawPtr(target)], fingerId)) {
            continue;
        }
        auto targetNode = target->GetAttachedNode().Upgrade();
        if (targetNode && targetNode == borderNode) {
            dict[targetPtr].emplace_back(fingerId, iter);
            return;
        }
        while (targetNode) {
            if (targetNode == borderNode) {
                dict[targetPtr].emplace_back(fingerId, iter);
                break;
            }
            targetNode = targetNode->GetParentFrameNode();
        }
    }
}

TouchRecognizerMap* CreateTouchRecognizers(
    FrameNode* frameNode, const std::shared_ptr<BaseGestureEvent>& info, ArkUIGestureInterruptInfo& interruptInfo)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, nullptr);
    auto& touchTestResult = eventManager->touchTestResults_;
    auto pTouchRecognizerMap = new TouchRecognizerMap;
    TouchRecognizerMap::value_type** touchRecoginers = nullptr;
    auto& touchRecognizerMap = *pTouchRecognizerMap;
    const auto& fingerList = info->GetFingerList();
    for (const auto& finger : fingerList) {
        auto& touchTargetList = touchTestResult[finger.fingerId_];
        CollectTouchEventTarget(touchRecognizerMap, touchTargetList, frameNode, finger.fingerId_);
    }
    touchRecoginers = new TouchRecognizerMap::value_type*[touchRecognizerMap.size()];
    int32_t i = 0;
    for (auto& item : touchRecognizerMap) {
        touchRecoginers[i++] = &item;
    }
    interruptInfo.touchRecognizers = reinterpret_cast<void**>(touchRecoginers);
    interruptInfo.touchRecognizerCnt = i;
    return pTouchRecognizerMap;
}

void DestroyTouchRecognizers(TouchRecognizerMap* recognizers, ArkUIGestureInterruptInfo& interruptInfo)
{
    if (recognizers) {
        delete recognizers;
    }
    if (interruptInfo.touchRecognizers) {
        delete[] reinterpret_cast<TouchRecognizerMap::value_type**>(interruptInfo.touchRecognizers);
    }
}

ArkUINodeHandle touchRecognizerGetNodeHandle(void* recognizer)
{
    auto iter = static_cast<TouchRecognizerMap::value_type*>(recognizer);
    TouchEventTarget* touchEventTarget = iter->first;
    auto frameNode = touchEventTarget->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode));
}

ArkUI_Bool touchRecognizerCancelTouch(void* recognizer)
{
    auto iter = static_cast<TouchRecognizerMap::value_type*>(recognizer);
    TouchEventTarget* touchEventTarget = iter->first;
    TouchRecognizerTarget& touchRecognizerTarget = iter->second;
    auto node = touchEventTarget->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    if (!touchRecognizerTarget.empty()) {
        eventManager->DispatchTouchCancelToRecognizer(touchEventTarget, touchRecognizerTarget);
        touchRecognizerTarget.clear();
        return true;
    }
    return false;
}

void setGestureInterrupterToNodeWithUserData(
    ArkUINodeHandle node, void* userData, ArkUI_Int32 (*interrupter)(ArkUIGestureInterruptInfo* interrupterInfo))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onGestureRecognizerJudgeBegin =
        [weak = AceType::WeakClaim(frameNode), userData, interrupter](const std::shared_ptr<BaseGestureEvent>& info,
            const RefPtr<NG::NGGestureRecognizer>& current,
            const std::list<RefPtr<NG::NGGestureRecognizer>>& others) -> GestureJudgeResult {
        auto node = weak.Upgrade();
        CHECK_NULL_RETURN(node, GestureJudgeResult::CONTINUE);
        ArkUIAPIEventGestureAsyncEvent gestureEvent;
        ArkUITouchEvent rawInputEvent;
        std::array<ArkUITouchPoint, MAX_POINTS> points;
        GetBaseGestureEvent(&gestureEvent, rawInputEvent, info, points);
        auto gestureInfo = current->GetGestureInfo();
        CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
        GetUniqueGestureEvent(&gestureEvent, gestureInfo->GetRecognizerType(), info);
        ArkUIGestureInterruptInfo interruptInfo;
        interruptInfo.isSystemGesture = gestureInfo->IsSystemGesture();
        interruptInfo.systemRecognizerType = static_cast<ArkUI_Int32>(gestureInfo->GetType());
        interruptInfo.event = &gestureEvent;
        interruptInfo.customUserData = userData;
        interruptInfo.userData = gestureInfo->GetUserData();
        ArkUIGestureRecognizer* currentArkUIGestureRecognizer = NodeModifier::CreateGestureRecognizer(current);
        interruptInfo.userData = reinterpret_cast<void*>(currentArkUIGestureRecognizer);
        auto count = static_cast<int32_t>(others.size());
        ArkUIGestureRecognizer** othersRecognizer = nullptr;
        if (count > 0) {
            othersRecognizer = new ArkUIGestureRecognizer* [count];
        }
        int32_t index = 0;
        for (const auto& item : others) {
            othersRecognizer[index] = NodeModifier::CreateGestureRecognizer(item);
            index++;
        }
        interruptInfo.responseLinkRecognizer = othersRecognizer;
        interruptInfo.count = count;
        ArkUI_UIInputEvent inputEvent { ConvertInputEventTypeToArkuiUIInputEventType(info->GetRawInputEventType()),
            C_TOUCH_EVENT_ID, &rawInputEvent };
        inputEvent.apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion() % API_TARGET_VERSION_MASK;
        ArkUIGestureEvent arkUIGestureEvent { gestureEvent, nullptr };
        interruptInfo.inputEvent = &inputEvent;
        interruptInfo.gestureEvent = &arkUIGestureEvent;
        auto touchRecognizers = CreateTouchRecognizers(AceType::RawPtr(node), info, interruptInfo);
        auto result = interrupter(&interruptInfo);
        delete[] othersRecognizer;
        DestroyTouchRecognizers(touchRecognizers, interruptInfo);
        return static_cast<GestureJudgeResult>(result);
    };
    ViewAbstract::SetOnGestureRecognizerJudgeBegin(frameNode, std::move(onGestureRecognizerJudgeBegin));
}

void setGestureInterrupterToNode(
    ArkUINodeHandle node, ArkUI_Int32 (*interrupter)(ArkUIGestureInterruptInfo* interrupterInfo))
{
    setGestureInterrupterToNodeWithUserData(node, nullptr, interrupter);
}

ArkUI_Int32 setInnerGestureParallelTo(ArkUINodeHandle node, void* userData,
    ArkUIGestureRecognizer* (*parallelInnerGesture)(ArkUIParallelInnerGestureEvent* event))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto parallelInnerGestureTo =
        [userData, parallelInnerGesture](const RefPtr<NGGestureRecognizer>& current,
            const std::vector<RefPtr<NGGestureRecognizer>>& others) -> RefPtr<NGGestureRecognizer> {
        auto* currentArkUIGestureRecognizer = NodeModifier::CreateGestureRecognizer(current);
        auto count = static_cast<int32_t>(others.size());
        ArkUIGestureRecognizer** othersArkUIGestureRecognizer = nullptr;
        if (count > 0) {
            othersArkUIGestureRecognizer = new ArkUIGestureRecognizer* [count];
        }
        for (auto index = 0; index < count; index++) {
            othersArkUIGestureRecognizer[index] = NodeModifier::CreateGestureRecognizer(others[index]);
        }
        ArkUIParallelInnerGestureEvent parallelInnerGestureEvent;
        parallelInnerGestureEvent.current = currentArkUIGestureRecognizer;
        parallelInnerGestureEvent.responseLinkRecognizer = othersArkUIGestureRecognizer;
        parallelInnerGestureEvent.userData = userData;
        parallelInnerGestureEvent.count = count;
        auto* result = parallelInnerGesture(&parallelInnerGestureEvent);
        if (!result || !result->recognizer) {
            return nullptr;
        }
        delete[] othersArkUIGestureRecognizer;
        return AceType::Claim(reinterpret_cast<NG::NGGestureRecognizer*>(result->recognizer));
    };
    ViewAbstract::SetShouldBuiltInRecognizerParallelWith(frameNode, std::move(parallelInnerGestureTo));
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 setGestureRecognizerEnabled(ArkUIGestureRecognizer* recognizer, bool enabled)
{
    auto* gestureRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(gestureRecognizer, ERROR_CODE_PARAM_INVALID);
    gestureRecognizer->SetEnabled(enabled);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 setGestureRecognizerLimitFingerCount(ArkUIGesture* gesture, bool limitFingerCount)
{
    auto gestureForLimitFinger = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    CHECK_NULL_RETURN(gestureForLimitFinger, ERROR_CODE_PARAM_INVALID);
    gestureForLimitFinger->SetLimitFingerCount(limitFingerCount);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Bool getGestureRecognizerEnabled(ArkUIGestureRecognizer* recognizer)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, false);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    return gestureRecognizer->IsEnabled();
}

ArkUI_Int32 getGestureRecognizerState(ArkUIGestureRecognizer* recognizer, ArkUIGestureRecognizerState* state)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    switch (gestureRecognizer->GetRefereeState()) {
        case NG::RefereeState::READY:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_READY;
            return ERROR_CODE_NO_ERROR;
        case NG::RefereeState::DETECTING:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_DETECTING;
            return ERROR_CODE_NO_ERROR;
        case NG::RefereeState::PENDING:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_PENDING;
            return ERROR_CODE_NO_ERROR;
        case NG::RefereeState::PENDING_BLOCKED:
        case NG::RefereeState::SUCCEED_BLOCKED:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_BLOCKED;
            return ERROR_CODE_NO_ERROR;
        case NG::RefereeState::SUCCEED:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_SUCCESSFUL;
            return ERROR_CODE_NO_ERROR;
        case NG::RefereeState::FAIL:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_FAILED;
            return ERROR_CODE_NO_ERROR;
        default:
            *state = ArkUIGestureRecognizerState::RECOGNIZER_STATE_READY;
            return ERROR_CODE_PARAM_INVALID;
    }
}

ArkUI_Int32 gestureEventTargetInfoIsScrollBegin(ArkUIGestureEventTargetInfo* info, bool* ret)
{
    auto frameNode = AceType::Claim(reinterpret_cast<NG::FrameNode*>(info->uiNode));
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto scrollablePattern = frameNode->GetPattern<NG::ScrollablePattern>();
    if (scrollablePattern) {
        *ret = scrollablePattern->IsAtTop();
        return ERROR_CODE_NO_ERROR;
    }
    auto swiperPattern = frameNode->GetPattern<NG::SwiperPattern>();
    if (swiperPattern) {
        *ret = swiperPattern->IsAtStart();
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_NON_SCROLLABLE_CONTAINER;
}

ArkUI_Int32 gestureEventTargetInfoIsScrollEnd(ArkUIGestureEventTargetInfo* info, bool* ret)
{
    auto frameNode = AceType::Claim(reinterpret_cast<NG::FrameNode*>(info->uiNode));
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto scrollablePattern = frameNode->GetPattern<NG::ScrollablePattern>();
    if (scrollablePattern) {
        *ret = scrollablePattern->IsAtBottom();
        return ERROR_CODE_NO_ERROR;
    }
    auto swiperPattern = frameNode->GetPattern<NG::SwiperPattern>();
    if (swiperPattern) {
        *ret = swiperPattern->IsAtEnd();
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_NON_SCROLLABLE_CONTAINER;
}

ArkUI_Int32 getPanGestureDirectionMask(ArkUIGestureRecognizer* recognizer, ArkUIGestureDirection* direction)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(panRecognizer, ERROR_CODE_PARAM_INVALID);
    *direction = static_cast<ArkUIGestureDirection>(panRecognizer->GetDirection().type);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getSwipeGestureDirectionMask(ArkUIGestureRecognizer* recognizer, ArkUIGestureDirection* direction)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(swipeRecognizer, ERROR_CODE_PARAM_INVALID);
    if (swipeRecognizer->GetDirection().type == SwipeDirection::HORIZONTAL) {
        *direction = static_cast<ArkUIGestureDirection>(ArkUI_GESTURE_DIRECTION_HORIZONTAL);
    } else if (swipeRecognizer->GetDirection().type == SwipeDirection::VERTICAL) {
        *direction = static_cast<ArkUIGestureDirection>(ArkUI_GESTURE_DIRECTION_VERTICAL);
    } else if (swipeRecognizer->GetDirection().type == SwipeDirection::ALL) {
        *direction = static_cast<ArkUIGestureDirection>(ArkUI_GESTURE_DIRECTION_ALL);
    } else {
        *direction = static_cast<ArkUIGestureDirection>(ArkUI_GESTURE_DIRECTION_NONE);
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getGestureFingerCount(ArkUIGestureRecognizer* recognizer, int* finger)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto multiFingersRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(multiFingersRecognizer, ERROR_CODE_PARAM_INVALID);
    *finger = static_cast<int32_t>(multiFingersRecognizer->GetFingers());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getGestureLimitFingerCount(ArkUIGestureRecognizer* recognizer, bool* isLimited)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto multiFingersRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(multiFingersRecognizer, ERROR_CODE_PARAM_INVALID);
    *isLimited = static_cast<bool>(multiFingersRecognizer->GetLimitFingerCount());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getLongPressGestureRepeat(ArkUIGestureRecognizer* recognizer, bool* isRepeat)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(longPressRecognizer, ERROR_CODE_PARAM_INVALID);
    *isRepeat = static_cast<bool>(longPressRecognizer->GetIsRepeat());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getPanGestureDistance(ArkUIGestureRecognizer* recognizer, double* distance)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(panRecognizer, ERROR_CODE_PARAM_INVALID);
    *distance = static_cast<double>(panRecognizer->GetDistance());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getPinchGestureDistance(ArkUIGestureRecognizer* recognizer, double* distance)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto pinchRecognizer = AceType::DynamicCast<PinchRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(pinchRecognizer, ERROR_CODE_PARAM_INVALID);
    *distance = RoundToMaxPrecision(static_cast<double>(pinchRecognizer->GetDistance()));
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getSwipeGestureSpeed(ArkUIGestureRecognizer* recognizer, double* speed)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto swipeRecognizer = AceType::DynamicCast<SwipeRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(swipeRecognizer, ERROR_CODE_PARAM_INVALID);
    *speed = RoundToMaxPrecision(static_cast<double>(swipeRecognizer->GetSpeed()));
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getLongPressGestureDuration(ArkUIGestureRecognizer* recognizer, int* duration)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(longPressRecognizer, ERROR_CODE_PARAM_INVALID);
    *duration = static_cast<int32_t>(longPressRecognizer->GetDuration());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getRotationGestureAngle(ArkUIGestureRecognizer* recognizer, double* angle)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto rotationRecognizer = AceType::DynamicCast<RotationRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(rotationRecognizer, ERROR_CODE_PARAM_INVALID);
    *angle = static_cast<double>(rotationRecognizer->GetAngle());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getTapGestureDistanceThreshold(ArkUIGestureRecognizer* recognizer, double* distanceThreshold)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(tapRecognizer, ERROR_CODE_PARAM_INVALID);
    *distanceThreshold = static_cast<double>(tapRecognizer->GetDistanceThreshold());
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 setDistanceMap(ArkUIGesture* gesture, int size, int* toolTypeArray, double* distanceArray)
{
    PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN,
        Dimension(DEFAULT_PAN_DISTANCE.Value(), DimensionUnit::PX) },
        { SourceTool::PEN, Dimension(DEFAULT_PEN_PAN_DISTANCE.Value(), DimensionUnit::PX) } };
    for (int i = 0; i < size; i++) {
        SourceTool st = ConvertCInputEventToolTypeToSourceTool(toolTypeArray[i]);
        if (st >= SourceTool::UNKNOWN && st <= SourceTool::JOYSTICK && GreatOrEqual(distanceArray[i], 0.0)) {
            distanceMap[st] = Dimension(distanceArray[i], DimensionUnit::PX);
        }
    }
    auto gestureForDistanceMap = Referenced::Claim(reinterpret_cast<PanGesture*>(gesture));
    CHECK_NULL_RETURN(gestureForDistanceMap, ERROR_CODE_PARAM_INVALID);
    gestureForDistanceMap->SetDistanceMap(distanceMap);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getDistanceByToolType(ArkUIGestureRecognizer* recognizer, int toolType, double* distance)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto panRecognizer = AceType::DynamicCast<PanRecognizer>(gestureRecognizer);
    CHECK_NULL_RETURN(panRecognizer, ERROR_CODE_PARAM_INVALID);
    PanDistanceMapDimension distanceMap = panRecognizer->GetDistanceMap();
    auto iter = distanceMap.find(ConvertCInputEventToolTypeToSourceTool(toolType));
    if (iter == distanceMap.end()) {
        return ERROR_CODE_PARAM_INVALID;
    }
    *distance = static_cast<double>(iter->second.ConvertToPx());
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 setPreventBegin(ArkUIGestureRecognizer* recognizer)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    gestureRecognizer->SetPreventBegin(true);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Bool isBuiltInGesture(ArkUIGestureRecognizer* recognizer)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, false);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    return gestureRecognizer->IsSystemGesture();
}

ArkUI_Int32 getGestureTag(ArkUIGestureRecognizer* recognizer, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* result)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto gestureInfo = gestureRecognizer->GetGestureInfo();
    CHECK_NULL_RETURN(gestureInfo, ERROR_CODE_PARAM_INVALID);
    auto gestureTag = gestureInfo->GetTag();
    CHECK_NULL_RETURN(gestureTag.has_value(), ERROR_CODE_PARAM_INVALID);
    auto actualSize = static_cast<int32_t>(gestureTag.value().size());
    *result = actualSize;
    if (actualSize > bufferSize - 1) {
        return ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH;
    }
    auto count = snprintf_s(buffer, bufferSize, bufferSize - 1, "%s", gestureTag.value().c_str());
    if (count < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 getGestureBindNodeId(
    ArkUIGestureRecognizer* recognizer, char* nodeId, ArkUI_Int32 size, ArkUI_Int32* result)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto attachNode = gestureRecognizer->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(attachNode, ERROR_CODE_PARAM_INVALID);
    auto inspectorId = attachNode->GetInspectorIdValue("");
    auto actualSize = static_cast<int32_t>(inspectorId.size());
    *result = actualSize;
    if (actualSize > size - 1) {
        return ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH;
    }
    auto count = snprintf_s(nodeId, size, size - 1, "%s", inspectorId.c_str());
    if (count < 0) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Bool isGestureRecognizerValid(ArkUIGestureRecognizer* recognizer)
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, false);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    return gestureRecognizer->IsInResponseLinkRecognizers();
}

ArkUI_Int32 setArkUIGestureRecognizerDisposeNotify(ArkUIGestureRecognizer* recognizer, void* userData,
    void (*callback)(ArkUIGestureRecognizer* recognizer, void* userData))
{
    auto* rawRecognizer = reinterpret_cast<NG::NGGestureRecognizer*>(recognizer->recognizer);
    CHECK_NULL_RETURN(rawRecognizer, ERROR_CODE_PARAM_INVALID);
    auto gestureRecognizer = AceType::Claim(rawRecognizer);
    auto disposeNotify = [userData, callback](void* recognizer) {
        auto* arkuiGestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
        callback(arkuiGestureRecognizer, userData);
    };
    gestureRecognizer->SetDisposeNotifyCallback(std::move(disposeNotify));
    return ERROR_CODE_NO_ERROR;
}

namespace NodeModifier {
const ArkUIGestureModifier* GetGestureModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGestureModifier modifier = {
        .createTapGesture = createTapGesture,
        .createTapGestureWithDistanceThreshold = createTapGestureWithDistanceThreshold,
        .createLongPressGesture = createLongPressGesture,
        .createPanGesture = createPanGesture,
        .createPinchGesture = createPinchGesture,
        .createRotationGesture = createRotationGesture,
        .createSwipeGesture = createSwipeGesture,
        .createSwipeGestureByModifier = createSwipeGestureByModifier,
        .createGestureGroup = createGestureGroup,
        .addGestureToGestureGroup = addGestureToGestureGroup,
        .removeGestureFromGestureGroup = removeGestureFromGestureGroup,
        .dispose = dispose,
        .registerGestureEvent = registerGestureEvent,
        .addGestureToNode = addGestureToNode,
        .removeGestureFromNode = removeGestureFromNode,
        .removeGestureFromNodeByTag = removeGestureFromNodeByTag,
        .clearGestures = clearGestures,
        .setGestureInterrupterToNode = setGestureInterrupterToNode,
        .setGestureInterrupterToNodeWithUserData = setGestureInterrupterToNodeWithUserData,
        .setInnerGestureParallelTo = setInnerGestureParallelTo,
        .setGestureRecognizerEnabled = setGestureRecognizerEnabled,
        .setGestureRecognizerLimitFingerCount = setGestureRecognizerLimitFingerCount,
        .getGestureRecognizerEnabled = getGestureRecognizerEnabled,
        .getGestureRecognizerState = getGestureRecognizerState,
        .gestureEventTargetInfoIsScrollBegin = gestureEventTargetInfoIsScrollBegin,
        .gestureEventTargetInfoIsScrollEnd = gestureEventTargetInfoIsScrollEnd,
        .getPanGestureDirectionMask = getPanGestureDirectionMask,
        .getSwipeGestureDirectionMask = getSwipeGestureDirectionMask,
        .getGestureFingerCount = getGestureFingerCount,
        .getGestureLimitFingerCount = getGestureLimitFingerCount,
        .getLongPressGestureRepeat = getLongPressGestureRepeat,
        .getPanGestureDistance = getPanGestureDistance,
        .getPinchGestureDistance = getPinchGestureDistance,
        .getSwipeGestureSpeed = getSwipeGestureSpeed,
        .getLongPressGestureDuration = getLongPressGestureDuration,
        .getRotationGestureAngle = getRotationGestureAngle,
        .getTapGestureDistanceThreshold = getTapGestureDistanceThreshold,
        .setDistanceMap = setDistanceMap,
        .getDistanceByToolType = getDistanceByToolType,
        .setPreventBegin = setPreventBegin,
        .isBuiltInGesture = isBuiltInGesture,
        .getGestureTag = getGestureTag,
        .getGestureBindNodeId = getGestureBindNodeId,
        .isGestureRecognizerValid = isGestureRecognizerValid,
        .setArkUIGestureRecognizerDisposeNotify = setArkUIGestureRecognizerDisposeNotify,
        .addGestureToGestureGroupWithRefCountDecrease = addGestureToGestureGroupWithRefCountDecrease,
        .addGestureToNodeWithRefCountDecrease = addGestureToNodeWithRefCountDecrease,
        .registerGestureEventExt = registerGestureEventExt,
        .touchRecognizerGetNodeHandle = touchRecognizerGetNodeHandle,
        .touchRecognizerCancelTouch = touchRecognizerCancelTouch,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIGestureModifier* GetCJUIGestureModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGestureModifier modifier = {
        .createTapGesture = createTapGesture,
        .createLongPressGesture = createLongPressGesture,
        .createPanGesture = createPanGesture,
        .createPinchGesture = createPinchGesture,
        .createRotationGesture = createRotationGesture,
        .createSwipeGesture = createSwipeGesture,
        .createSwipeGestureByModifier = createSwipeGestureByModifier,
        .createGestureGroup = createGestureGroup,
        .addGestureToGestureGroup = addGestureToGestureGroup,
        .removeGestureFromGestureGroup = removeGestureFromGestureGroup,
        .dispose = dispose,
        .registerGestureEvent = registerGestureEvent,
        .addGestureToNode = addGestureToNode,
        .removeGestureFromNode = removeGestureFromNode,
        .removeGestureFromNodeByTag = removeGestureFromNodeByTag,
        .clearGestures = clearGestures,
        .setGestureInterrupterToNode = setGestureInterrupterToNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

ArkUI_Int32 ConvertGestureTypeNameToArkUIType(GestureTypeName gestureTypeName)
{
    switch (gestureTypeName) {
        case GestureTypeName::TAP_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::TAP_GESTURE);
        case GestureTypeName::LONG_PRESS_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::LONG_PRESS_GESTURE);
        case GestureTypeName::PAN_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::PAN_GESTURE);
        case GestureTypeName::PINCH_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::PINCH_GESTURE);
        case GestureTypeName::SWIPE_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::SWIPE_GESTURE);
        case GestureTypeName::ROTATION_GESTURE:
            return static_cast<ArkUI_Int32>(ArkUI_GestureRecognizerType::ROTATION_GESTURE);
        default:
            return static_cast<ArkUI_Int32>(gestureTypeName);
    }
}

ArkUIGestureRecognizer* CreateGestureRecognizer(const RefPtr<NG::NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_RETURN(recognizer, nullptr);
    ArkUIGestureRecognizer* arkUIGestureRecognizer;
    auto gestureInfo = recognizer->GetGestureInfo();
    CHECK_NULL_RETURN(gestureInfo, nullptr);
    auto* userData = gestureInfo->GetUserData();
    if (userData) {
        arkUIGestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(userData);
    } else {
        arkUIGestureRecognizer = new ArkUIGestureRecognizer();
        arkUIGestureRecognizer->capi = false;
        gestureInfo->SetUserData(arkUIGestureRecognizer);
    }
    arkUIGestureRecognizer->type = ConvertGestureTypeNameToArkUIType(gestureInfo->GetRecognizerType());
    arkUIGestureRecognizer->recognizer = reinterpret_cast<void*>(AceType::RawPtr(recognizer));
    auto attachNode = recognizer->GetAttachedNode().Upgrade();
    if (attachNode) {
        arkUIGestureRecognizer->targetInfo.uiNode = reinterpret_cast<void*>(AceType::RawPtr(attachNode));
    }
    gestureInfo->SetIsCapi(arkUIGestureRecognizer->capi);
    gestureInfo->SetDisposeJSRecognizerInfoFunc([arkUIGestureRecognizer]() {
        delete arkUIGestureRecognizer;
    });
    return arkUIGestureRecognizer;
}

void GetTouchPoints(const std::shared_ptr<BaseGestureEvent>& info, std::array<ArkUITouchPoint, MAX_POINTS>& points,
    ArkUITouchEvent& rawInputEvent)
{
    CHECK_NULL_VOID(info);
    auto fingerList = info->GetFingerList();
    rawInputEvent.touchPointSize = fingerList.size();
    int32_t i = 0;
    for (const auto& fingureIterator : fingerList) {
        points[i].id = fingureIterator.fingerId_;
        points[i].nodeX = fingureIterator.localLocation_.GetX();
        points[i].nodeY = fingureIterator.localLocation_.GetY();
        points[i].windowX = fingureIterator.globalLocation_.GetX();
        points[i].windowY = fingureIterator.globalLocation_.GetY();
        points[i].screenX = fingureIterator.screenLocation_.GetX();
        points[i].screenY = fingureIterator.screenLocation_.GetY();
        points[i].globalDisplayX = fingureIterator.globalDisplayLocation_.GetX();
        points[i].globalDisplayY = fingureIterator.globalDisplayLocation_.GetY();
        points[i].operatingHand = fingureIterator.operatingHand_;
        points[i].tiltX = info->GetTiltX().value_or(0.0f);
        points[i].tiltY = info->GetTiltY().value_or(0.0f);
        points[i].toolType = static_cast<ArkUI_Int32>(info->GetSourceTool());
        points[i].rollAngle = info->GetRollAngle().value_or(0.0f);
        points[i].pressure = info->GetForce();
        points[i].pressedTime = info->GetTimeStamp().time_since_epoch().count();
        i++;
    }
    rawInputEvent.touchPointes = &(points[0]);
    if (rawInputEvent.touchPointSize > 0) {
        rawInputEvent.actionTouchPoint.nodeX = rawInputEvent.touchPointes[0].nodeX;
        rawInputEvent.actionTouchPoint.nodeY = rawInputEvent.touchPointes[0].nodeY;
        rawInputEvent.actionTouchPoint.windowX = rawInputEvent.touchPointes[0].windowX;
        rawInputEvent.actionTouchPoint.windowY = rawInputEvent.touchPointes[0].windowY;
        rawInputEvent.actionTouchPoint.screenX = rawInputEvent.touchPointes[0].screenX;
        rawInputEvent.actionTouchPoint.screenY = rawInputEvent.touchPointes[0].screenY;
        rawInputEvent.actionTouchPoint.globalDisplayX = rawInputEvent.touchPointes[0].globalDisplayX;
        rawInputEvent.actionTouchPoint.globalDisplayY = rawInputEvent.touchPointes[0].globalDisplayY;
        rawInputEvent.actionTouchPoint.operatingHand = rawInputEvent.touchPointes[0].operatingHand;
        rawInputEvent.actionTouchPoint.tiltX = rawInputEvent.touchPointes[0].tiltX;
        rawInputEvent.actionTouchPoint.tiltY = rawInputEvent.touchPointes[0].tiltY;
        rawInputEvent.actionTouchPoint.toolType = rawInputEvent.touchPointes[0].toolType;
        rawInputEvent.actionTouchPoint.rollAngle = rawInputEvent.touchPointes[0].rollAngle;
        rawInputEvent.actionTouchPoint.pressure = rawInputEvent.touchPointes[0].pressure;
        rawInputEvent.actionTouchPoint.pressedTime = rawInputEvent.touchPointes[0].pressedTime;
    }
}

void GetBaseGestureEvent(ArkUIAPIEventGestureAsyncEvent* ret, ArkUITouchEvent& rawInputEvent,
    ArkUI_UIInputEvent& inputEvent, const std::shared_ptr<BaseGestureEvent>& info,
    std::array<ArkUITouchPoint, MAX_POINTS>& points)
{
    CHECK_NULL_VOID(info);
    rawInputEvent.sourceType = static_cast<ArkUI_Int32>(info->GetSourceDevice());
    rawInputEvent.timeStamp = info->GetTimeStamp().time_since_epoch().count();
    rawInputEvent.action =
        info->GetLastAction().value_or(GetPointerEventAction(info->GetRawInputEventType(), info->GetRawInputEvent()));
    rawInputEvent.deviceId = info->GetRawInputDeviceId();
    rawInputEvent.stopPropagation = info->IsStopPropagation();
    rawInputEvent.preventDefault = info->IsPreventDefault();
    rawInputEvent.targetDisplayId = info->GetTargetDisplayId();
    const auto& targetLocalOffset = info->GetTarget().area.GetOffset();
    const auto& targetOrigin = info->GetTarget().origin;
    // width height x y globalx globaly
    rawInputEvent.targetPositionX = targetLocalOffset.GetX().ConvertToPx();
    rawInputEvent.targetPositionY = targetLocalOffset.GetY().ConvertToPx();
    rawInputEvent.targetGlobalPositionX = targetOrigin.GetX().ConvertToPx() + targetLocalOffset.GetX().ConvertToPx();
    rawInputEvent.targetGlobalPositionY = targetOrigin.GetY().ConvertToPx() + targetLocalOffset.GetY().ConvertToPx();
    rawInputEvent.width = info->GetTarget().area.GetWidth().ConvertToPx();
    rawInputEvent.height = info->GetTarget().area.GetHeight().ConvertToPx();
    GetTouchPoints(info, points, rawInputEvent);
    inputEvent.inputType = ConvertInputEventTypeToArkuiUIInputEventType(info->GetRawInputEventType());
    inputEvent.apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion() % API_TARGET_VERSION_MASK;
    inputEvent.inputEvent = &rawInputEvent;
    if (ret) {
        ret->rawPointerEvent = &inputEvent;
    }
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
