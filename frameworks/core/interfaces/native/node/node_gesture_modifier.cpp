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

#include "core/interfaces/native/node/node_gesture_modifier.h"
#include <securec.h>

#include "base/error/error_code.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
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

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t MAX_POINTS = 10;
}
ArkUIGesture* createPanGesture(ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 distance, void* userData)
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
    auto panGestureObject = AceType::MakeRefPtr<PanGesture>(fingers, panDirection, distance);
    panGestureObject->SetUserData(userData);
    panGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(panGestureObject));
}

ArkUIGesture* createTapGesture(ArkUI_Int32 count, ArkUI_Int32 fingers, void* userData)
{
    auto tapGestureObject = AceType::MakeRefPtr<TapGesture>(count, fingers, std::numeric_limits<double>::infinity());
    tapGestureObject->SetUserData(userData);
    tapGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(tapGestureObject));
}

ArkUIGesture* createTapGestureWithDistanceThreshold(
    ArkUI_Int32 count, ArkUI_Int32 fingers, double distanceThreshold, void* userData)
{
    distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
    auto tapGestureObject = AceType::MakeRefPtr<TapGesture>(count, fingers, distanceThreshold);
    tapGestureObject->SetUserData(userData);
    tapGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(tapGestureObject));
}

ArkUIGesture* createLongPressGesture(ArkUI_Int32 fingers, bool repeat, ArkUI_Int32 duration, void* userData)
{
    auto longPressGestureObject = AceType::MakeRefPtr<LongPressGesture>(fingers, repeat, duration);
    longPressGestureObject->SetUserData(userData);
    longPressGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(longPressGestureObject));
}

ArkUIGesture* createPinchGesture(ArkUI_Int32 fingers, ArkUI_Float64 distance, void* userData)
{
    auto pinchGestureObject = AceType::MakeRefPtr<PinchGesture>(fingers, distance);
    pinchGestureObject->SetUserData(userData);
    pinchGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(pinchGestureObject));
}

ArkUIGesture* createRotationGesture(ArkUI_Int32 fingers, ArkUI_Float64 angle, void* userData)
{
    auto rotationGestureObject = AceType::MakeRefPtr<RotationGesture>(fingers, angle);
    rotationGestureObject->SetUserData(userData);
    rotationGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(rotationGestureObject));
}

ArkUIGesture* createSwipeGesture(ArkUI_Int32 fingers, ArkUI_Int32 directions, ArkUI_Float64 speed, void* userData)
{
    SwipeDirection swipeDirection{SwipeDirection::NONE};
    if (static_cast<uint32_t>(directions) & ArkUI_GESTURE_DIRECTION_HORIZONTAL) {
        swipeDirection.type = SwipeDirection::HORIZONTAL;
    }
    if (static_cast<uint32_t>(directions) & ArkUI_GESTURE_DIRECTION_VERTICAL) {
        swipeDirection.type += SwipeDirection::VERTICAL;
    }
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingers, swipeDirection, speed);
    swipeGestureObject->SetUserData(userData);
    swipeGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(swipeGestureObject));
}

ArkUIGesture* createSwipeGestureByModifier(ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 speed)
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
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingers, swipeDirection, speed);
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
        points[i].contactAreaWidth = touchPoint.size;
        points[i].contactAreaHeight = touchPoint.size;
        points[i].pressure = touchPoint.force;
        points[i].tiltX = touchPoint.tiltX.value_or(0.0f);
        points[i].tiltY = touchPoint.tiltY.value_or(0.0f);
        points[i].pressedTime = touchPoint.downTime.time_since_epoch().count();
        points[i].toolType = static_cast<int32_t>(touchPoint.sourceTool);
        i++;
        fingureIterator++;
    }
}

void ConvertIMMEventToTouchEvent(GestureEvent& info, ArkUITouchEvent& touchEvent,
    std::array<ArkUITouchPoint, MAX_POINTS>& points)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    auto tempTouchEvent = NG::ConvertToTouchEvent(info.GetPointerEvent());
    touchEvent.action = static_cast<int32_t>(tempTouchEvent.type);
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
        touchEvent.actionTouchPoint.toolType = touchEvent.touchPointes[0].toolType;
    }
    touchEvent.touchPointSize = tempTouchEvent.pointers.size() < MAX_POINTS ?
    tempTouchEvent.pointers.size() : MAX_POINTS;
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
    switch (info.GetInputEventType()) {
        case InputEventType::TOUCH_SCREEN :
            ret.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_TOUCH);
            break;
        case InputEventType::MOUSE_BUTTON:
            ret.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_MOUSE);
            break;
        case InputEventType::AXIS :
            ret.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_AXIS);
            break;
        default:
            break;
    }
}

void GetBaseGestureEvent(ArkUIAPIEventGestureAsyncEvent* ret, ArkUITouchEvent& rawInputEvent,
    const std::shared_ptr<BaseGestureEvent>& info)
{
    rawInputEvent.sourceType = static_cast<ArkUI_Int32>(info->GetSourceDevice());
    rawInputEvent.timeStamp = info->GetTimeStamp().time_since_epoch().count();
    rawInputEvent.actionTouchPoint.tiltX = info->GetTiltX().value_or(0.0f);
    rawInputEvent.actionTouchPoint.tiltY = info->GetTiltY().value_or(0.0f);
    rawInputEvent.actionTouchPoint.toolType = static_cast<ArkUI_Int32>(info->GetSourceTool());
    rawInputEvent.actionTouchPoint.pressure = info->GetForce();
    std::array<ArkUITouchPoint, MAX_POINTS> points;
    auto fingerList = info->GetFingerList();
    auto fingureIterator = std::begin(fingerList);
    for (size_t i = 0; i < fingerList.size(); i++) {
        points[i].id = fingureIterator->fingerId_;
        points[i].windowX = fingureIterator->globalLocation_.GetX();
        points[i].windowY = fingureIterator->globalLocation_.GetY();
        points[i].nodeX = fingureIterator->localLocation_.GetX();
        points[i].nodeY = fingureIterator->localLocation_.GetY();
        points[i].tiltX = rawInputEvent.actionTouchPoint.tiltX;
        points[i].tiltY = rawInputEvent.actionTouchPoint.tiltY;
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

void setCancelActionFunc(Gesture* gestureRef, void* extraParam)
{
    auto onActionCancel = [extraParam]() {
        ArkUINodeEvent eventData;
        eventData.kind = GESTURE_ASYNC_EVENT;
        eventData.nodeId = 0;
        eventData.extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
        eventData.gestureAsyncEvent.subKind = ON_ACTION_CANCEL;
        SendArkUISyncEvent(&eventData);
    };
    gestureRef->SetOnActionCancelId(onActionCancel);
}

void ConvertIMMEventToMouseEvent(GestureEvent& info, ArkUIMouseEvent& mouseEvent)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    MouseEvent tempMouseEvent;
    NG::ConvertToMouseEvent(tempMouseEvent, info.GetPointerEvent());
    auto fingureBegin = std::begin(info.GetFingerList());
    auto fingureEnd = std::end(info.GetFingerList());
    mouseEvent.action = static_cast<int32_t>(tempMouseEvent.action);
    mouseEvent.sourceType = static_cast<int32_t>(tempMouseEvent.sourceType);
    mouseEvent.timeStamp = tempMouseEvent.time.time_since_epoch().count();
    mouseEvent.actionTouchPoint.pressure = 0.0f;
    mouseEvent.actionTouchPoint.nodeX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetX();
    mouseEvent.actionTouchPoint.nodeY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->localLocation_.GetY();
    mouseEvent.actionTouchPoint.windowX = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetX();
    mouseEvent.actionTouchPoint.windowY = fingureBegin == fingureEnd ? 0.0f : fingureBegin->globalLocation_.GetY();
    mouseEvent.actionTouchPoint.screenX = tempMouseEvent.screenX;
    mouseEvent.actionTouchPoint.screenY = tempMouseEvent.screenY;
    mouseEvent.actionTouchPoint.toolType = static_cast<int32_t>(tempMouseEvent.sourceTool);
}

void ConvertIMMEventToAxisEvent(GestureEvent& info, ArkUIAxisEvent& axisEvent)
{
    CHECK_NULL_VOID(info.GetPointerEvent());
    AxisEvent tempAxisEvent;
    NG::ConvertToAxisEvent(tempAxisEvent, info.GetPointerEvent());
    auto fingureBegin = std::begin(info.GetFingerList());
    auto fingureEnd = std::end(info.GetFingerList());
    axisEvent.action = static_cast<int32_t>(tempAxisEvent.action);
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
    axisEvent.actionTouchPoint.toolType = static_cast<int32_t>(tempAxisEvent.sourceTool);
}

void SendGestureEvent(GestureEvent& info, int32_t eventKind, void* extraParam)
{
    ArkUINodeEvent eventData;
    eventData.kind = GESTURE_ASYNC_EVENT;
    eventData.nodeId = 0;
    eventData.extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
    eventData.gestureAsyncEvent.subKind = eventKind;
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
        setCancelActionFunc(gestureRef, extraParam);
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

void setGestureInterrupterToNode(
    ArkUINodeHandle node, ArkUI_Int32 (*interrupter)(ArkUIGestureInterruptInfo* interrupterInfo))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto onGestureRecognizerJudgeBegin = [frameNode, interrupter](const std::shared_ptr<BaseGestureEvent>& info,
                                   const RefPtr<NG::NGGestureRecognizer>& current,
                                   const std::list<RefPtr<NG::NGGestureRecognizer>>& others) -> GestureJudgeResult {
        ArkUIAPIEventGestureAsyncEvent gestureEvent;
        ArkUITouchEvent rawInputEvent;
        GetBaseGestureEvent(&gestureEvent, rawInputEvent, info);
        auto gestureInfo = current->GetGestureInfo();
        CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
        GetUniqueGestureEvent(&gestureEvent, gestureInfo->GetRecognizerType(), info);
        ArkUIGestureInterruptInfo interruptInfo;
        interruptInfo.isSystemGesture = gestureInfo->IsSystemGesture();
        interruptInfo.systemRecognizerType = static_cast<ArkUI_Int32>(gestureInfo->GetType());
        interruptInfo.event = &gestureEvent;
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
        ArkUI_UIInputEvent inputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID,
            &rawInputEvent };
        ArkUIGestureEvent arkUIGestureEvent { gestureEvent, nullptr };
        interruptInfo.inputEvent = &inputEvent;
        interruptInfo.gestureEvent = &arkUIGestureEvent;
        auto result = interrupter(&interruptInfo);
        delete[] othersRecognizer;
        return static_cast<GestureJudgeResult>(result);
    };
    ViewAbstract::SetOnGestureRecognizerJudgeBegin(frameNode, std::move(onGestureRecognizerJudgeBegin));
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
    constexpr auto lineBegin = __LINE__; // don't move this line
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
        .setInnerGestureParallelTo = setInnerGestureParallelTo,
        .setGestureRecognizerEnabled = setGestureRecognizerEnabled,
        .getGestureRecognizerEnabled = getGestureRecognizerEnabled,
        .getGestureRecognizerState = getGestureRecognizerState,
        .gestureEventTargetInfoIsScrollBegin = gestureEventTargetInfoIsScrollBegin,
        .gestureEventTargetInfoIsScrollEnd = gestureEventTargetInfoIsScrollEnd,
        .getPanGestureDirectionMask = getPanGestureDirectionMask,
        .isBuiltInGesture = isBuiltInGesture,
        .getGestureTag = getGestureTag,
        .getGestureBindNodeId = getGestureBindNodeId,
        .isGestureRecognizerValid = isGestureRecognizerValid,
        .setArkUIGestureRecognizerDisposeNotify = setArkUIGestureRecognizerDisposeNotify,
        .addGestureToGestureGroupWithRefCountDecrease = addGestureToGestureGroupWithRefCountDecrease,
        .addGestureToNodeWithRefCountDecrease = addGestureToNodeWithRefCountDecrease,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIGestureModifier* GetCJUIGestureModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
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
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
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
    arkUIGestureRecognizer->type = static_cast<int32_t>(gestureInfo->GetRecognizerType());
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
