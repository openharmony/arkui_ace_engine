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
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "core/components_ng/gestures/pan_gesture.h"
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
    PanGesture *panGestureObject = new PanGesture(fingers, panDirection, distance);
    return reinterpret_cast<ArkUIGesture*>(panGestureObject);
}

void dispose(ArkUIGesture* recognizer)
{
    Gesture* gestureRef = reinterpret_cast<Gesture*>(recognizer);
    delete gestureRef;
}

ArkUIAPIEventGestureAsyncEvent getGestureEvent(GestureEvent& info)
{
    ArkUIAPIEventGestureAsyncEvent ret;
    ret.repeat = info.GetRepeat();
    ret.velocityX = info.GetVelocity().GetVelocityX();
    ret.velocityY = info.GetVelocity().GetVelocityY();
    ret.velocity = info.GetVelocity().GetVelocityValue();
    return ret;
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
}

void addGestureToNode(ArkUINodeHandle node, ArkUIGesture* gesture, ArkUI_Int32 priorityNum, ArkUI_Uint32 mask)
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
    //reference to type 'const RefPtr<NG::Gesture>' could not bind to an lvalue of type 'OHOS::Ace::NG::Gesture *'
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
    const ArkUIGestureModifier* GetGestureModifier() {
            static const ArkUIGestureModifier modifier = {
            createPanGesture,
            dispose,
            registerGestureEvent,
            addGestureToNode,
            removeGestureFromNode,
            };
            return &modifier;
    }
}
}
