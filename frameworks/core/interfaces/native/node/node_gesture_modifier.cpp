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
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/rotation_gesture.h"
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

ArkUIGesture* createPanGesture(ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 distance)
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
    panGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(panGestureObject));
}

ArkUIGesture* createTapGesture(ArkUI_Int32 count, ArkUI_Int32 fingers)
{
    auto tapGestureObject = AceType::MakeRefPtr<TapGesture>(count, fingers);
    tapGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(tapGestureObject));
}

ArkUIGesture* createLongPressGesture(ArkUI_Int32 fingers, bool repeat, ArkUI_Int32 duration)
{
    auto longPressGestureObject = AceType::MakeRefPtr<LongPressGesture>(fingers, repeat, duration);
    longPressGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(longPressGestureObject));
}

ArkUIGesture* createPinchGesture(ArkUI_Int32 fingers, ArkUI_Float64 distance)
{
    auto pinchGestureObject = AceType::MakeRefPtr<PinchGesture>(fingers, distance);
    pinchGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(pinchGestureObject));
}

ArkUIGesture* createRotationGesture(ArkUI_Int32 fingers, ArkUI_Float64 angle)
{
    auto rotationGestureObject = AceType::MakeRefPtr<RotationGesture>(fingers, angle);
    rotationGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(rotationGestureObject));
}

ArkUIGesture* createSwipeGesture(ArkUI_Int32 fingers, ArkUI_Int32 directions, ArkUI_Float64 speed)
{
    SwipeDirection swipeDirection{SwipeDirection::NONE};
    if (directions & ArkUI_GESTURE_DIRECTION_HORIZONTAL) {
        swipeDirection.type = SwipeDirection::HORIZONTAL;
    }
    if (directions & ArkUI_GESTURE_DIRECTION_VERTICAL) {
        swipeDirection.type = SwipeDirection::VERTICAL;
    }
    auto swipeGestureObject = AceType::MakeRefPtr<SwipeGesture>(fingers, swipeDirection, speed);
    swipeGestureObject->IncRefCount();
    return reinterpret_cast<ArkUIGesture*>(AceType::RawPtr(swipeGestureObject));
}

void dispose(ArkUIGesture* recognizer)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(recognizer);
    gestureRef->DecRefCount();
}

ArkUIAPIEventGestureAsyncEvent getGestureEvent(GestureEvent& info)
{
    ArkUIAPIEventGestureAsyncEvent ret;
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
    return ret;
}

void setCancelActionFunc(Gesture* gestureRef, void* extraParam)
{
    auto onActionCancel = [extraParam]() {
        ArkUINodeEvent *eventData = new ArkUINodeEvent();
        eventData->kind = GESTURE_ASYNC_EVENT;
        eventData->nodeId = 0;
        eventData->extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
        eventData->gestureAsyncEvent.subKind = ON_ACTION_CANCEL;
        SendArkUIAsyncEvent(eventData);
    };
    gestureRef->SetOnActionCancelId(onActionCancel);
}

void registerGestureEvent(ArkUIGesture* gesture, ArkUI_Uint32 actionTypeMask, void* extraParam)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(gesture);
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_ACCEPT) {
        auto onActionAccept = [extraParam](GestureEvent& info) {
            ArkUINodeEvent *eventData = new ArkUINodeEvent();
            eventData->kind = GESTURE_ASYNC_EVENT;
            eventData->nodeId = 0;
            eventData->extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
            eventData->gestureAsyncEvent = getGestureEvent(info);
            eventData->gestureAsyncEvent.subKind = ON_ACTION_START;
            SendArkUIAsyncEvent(eventData);
        };
        gestureRef->SetOnActionId(onActionAccept);
        gestureRef->SetOnActionStartId(onActionAccept);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_UPDATE) {
        auto onActionUpdate = [extraParam](GestureEvent& info) {
            ArkUINodeEvent *eventData = new ArkUINodeEvent();
            eventData->kind = GESTURE_ASYNC_EVENT;
            eventData->nodeId = 0;
            eventData->extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
            eventData->gestureAsyncEvent = getGestureEvent(info);
            eventData->gestureAsyncEvent.subKind = ON_ACTION_UPDATE;
            SendArkUIAsyncEvent(eventData);
        };
        gestureRef->SetOnActionUpdateId(onActionUpdate);
    }
    if (actionTypeMask & ARKUI_GESTURE_EVENT_ACTION_END) {
        auto onActionEnd = [extraParam](GestureEvent& info) {
            ArkUINodeEvent *eventData = new ArkUINodeEvent();
            eventData->kind = GESTURE_ASYNC_EVENT;
            eventData->nodeId = 0;
            eventData->extraParam = reinterpret_cast<ArkUI_Int64>(extraParam);
            eventData->gestureAsyncEvent = getGestureEvent(info);
            eventData->gestureAsyncEvent.subKind = ON_ACTION_END;
            SendArkUIAsyncEvent(eventData);
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


void removeGestureFromNode(ArkUINodeHandle node, ArkUIGesture* gesture)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto gesturePtr = Referenced::Claim(reinterpret_cast<Gesture*>(gesture));
    gestureHub->RemoveGesture(gesturePtr);
}

namespace NodeModifier {
const ArkUIGestureModifier* GetGestureModifier()
{
    static const ArkUIGestureModifier modifier = {
        createTapGesture,
        createLongPressGesture,
        createPanGesture,
        createPinchGesture,
        createRotationGesture,
        createSwipeGesture,
        dispose,
        registerGestureEvent,
        addGestureToNode,
        removeGestureFromNode,
        };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
