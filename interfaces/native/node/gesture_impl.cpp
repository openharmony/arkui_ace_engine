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


#include "node_model.h"
#include "gesture_impl.h"

#include "core/gestures/gesture_event.h"
#include "interfaces/native/event/ui_input_event_impl.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_GestureRecognizer {
    int32_t type = -1;
    ArkUIGesture* gesture = nullptr;
    void* extraData = nullptr;
    void* attachNode = nullptr;
    bool capi = true;
    void* recognizer = nullptr;
    ArkUIGestureEventTargetInfo targetInfo = {};
};

struct ArkUI_GestureEventTargetInfo {
    void* uiNode = nullptr;
};

#ifdef __cplusplus
};

// the ArkUI_GestureEvent struct actually same as ArkUIAPIEventGestureAsyncEvent;
struct ArkUI_GestureEvent {
    ArkUIAPIEventGestureAsyncEvent eventData;
    void* attachNode;
};

struct ArkUI_GestureInterruptInfo {
    ArkUIGestureInterruptInfo interruptData;
};

struct ArkUI_ParallelInnerGestureEvent {
    ArkUIGestureRecognizer* current = nullptr;
    ArkUIGestureRecognizer** responseLinkRecognizer = nullptr;
    void* userData = nullptr;
    int32_t count;
};

#endif


ArkUI_GestureEventActionType OH_ArkUI_GestureEvent_GetActionType(const ArkUI_GestureEvent* event)
{
    ArkUI_GestureEventActionType ret;
    switch (event->eventData.subKind) {
        case ON_ACTION:
        case ON_ACTION_START:
            ret = GESTURE_EVENT_ACTION_ACCEPT;
            break;
        case ON_ACTION_UPDATE:
            ret = GESTURE_EVENT_ACTION_UPDATE;
            break;
        case ON_ACTION_END:
            ret = GESTURE_EVENT_ACTION_END;
            break;
        case ON_ACTION_CANCEL:
            ret = GESTURE_EVENT_ACTION_CANCEL;
            break;
        default:
            ret = GESTURE_EVENT_ACTION_ACCEPT;
            break;
    }
    return ret;
}

const ArkUI_UIInputEvent* OH_ArkUI_GestureEvent_GetRawInputEvent(const ArkUI_GestureEvent* event)
{
    if (!event) {
        return nullptr;
    }
    return reinterpret_cast<ArkUI_UIInputEvent*>(event->eventData.rawPointerEvent);
}

int32_t OH_ArkUI_LongPress_GetRepeatCount(const ArkUI_GestureEvent* event)
{
    return event->eventData.repeat;
}

float OH_ArkUI_PanGesture_GetVelocity(const ArkUI_GestureEvent* event)
{
    return event->eventData.velocity;
}

float OH_ArkUI_PanGesture_GetVelocityX(const ArkUI_GestureEvent* event)
{
    return event->eventData.velocityX;
}

float OH_ArkUI_PanGesture_GetVelocityY(const ArkUI_GestureEvent* event)
{
    return event->eventData.velocityY;
}

float OH_ArkUI_PanGesture_GetOffsetX(const ArkUI_GestureEvent* event)
{
    return event->eventData.x;
}

float OH_ArkUI_PanGesture_GetOffsetY(const ArkUI_GestureEvent* event)
{
    return event->eventData.y;
}

float OH_ArkUI_SwipeGesture_GetAngle(const ArkUI_GestureEvent* event)
{
    return event->eventData.angle;
}

float OH_ArkUI_SwipeGesture_GetVelocity(const ArkUI_GestureEvent* event)
{
    return event->eventData.speed;
}

float OH_ArkUI_RotationGesture_GetAngle(const ArkUI_GestureEvent* event)
{
    return event->eventData.angle;
}

float OH_ArkUI_PinchGesture_GetScale(const ArkUI_GestureEvent* event)
{
    return event->eventData.scale;
}

float OH_ArkUI_PinchGesture_GetCenterX(const ArkUI_GestureEvent* event)
{
    return event->eventData.pinchCenterX;
}

float OH_ArkUI_PinchGesture_GetCenterY(const ArkUI_GestureEvent* event)
{
    return event->eventData.pinchCenterY;
}

ArkUI_NodeHandle OH_ArkUI_GestureEvent_GetNode(const ArkUI_GestureEvent* event)
{
    if (!event) {
        return nullptr;
    }
    return reinterpret_cast<ArkUI_NodeHandle>(event->attachNode);
}

bool OH_ArkUI_GestureInterruptInfo_GetSystemFlag(const ArkUI_GestureInterruptInfo* event)
{
    return event->interruptData.isSystemGesture;
}

ArkUI_GestureRecognizer* OH_ArkUI_GestureInterruptInfo_GetRecognizer(const ArkUI_GestureInterruptInfo* event)
{
    return reinterpret_cast<ArkUI_GestureRecognizer *>(event->interruptData.userData);
}

ArkUI_GestureEvent* OH_ArkUI_GestureInterruptInfo_GetGestureEvent(const ArkUI_GestureInterruptInfo* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    ArkUI_GestureEvent* gestureEvent = reinterpret_cast<ArkUI_GestureEvent*>(event->interruptData.gestureEvent);
    CHECK_NULL_RETURN(gestureEvent, nullptr);

    ArkUI_UIInputEvent* uiEvent = reinterpret_cast<ArkUI_UIInputEvent*>(event->interruptData.inputEvent);
    gestureEvent->eventData.rawPointerEvent = uiEvent;

    auto* gestureRecognizer = reinterpret_cast<ArkUI_GestureRecognizer*>(event->interruptData.userData);
    CHECK_NULL_RETURN(gestureRecognizer, nullptr);
    gestureEvent->attachNode = gestureRecognizer->attachNode;
    return gestureEvent;
}

int32_t OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(const ArkUI_GestureInterruptInfo* event)
{
    if (event->interruptData.isSystemGesture) {
        return event->interruptData.systemRecognizerType;
    }
    return -1;
}

int32_t OH_ArkUI_GetResponseRecognizersFromInterruptInfo(
    const ArkUI_GestureInterruptInfo* event, ArkUI_GestureRecognizerHandleArray* responseChain, int32_t* count)
{
    CHECK_NULL_RETURN(responseChain, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(count, ARKUI_ERROR_CODE_PARAM_INVALID);
    *responseChain = reinterpret_cast<ArkUI_GestureRecognizer**>(event->interruptData.responseLinkRecognizer);
    *count = event->interruptData.count;
    return 0;
}

int32_t OH_ArkUI_SetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer, bool enabled)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->setGestureRecognizerEnabled(gestureRecognizer, enabled);
}

int32_t OH_ArkUI_SetGestureRecognizerLimitFingerCount(ArkUI_GestureRecognizer* recognizer, bool limitFingerCount)
{
    auto* gesture = reinterpret_cast<ArkUIGesture*>(recognizer->gesture);
    if (!gesture) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->setGestureRecognizerLimitFingerCount(gesture, limitFingerCount);
}

bool OH_ArkUI_GetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return false;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->getGestureRecognizerEnabled(gestureRecognizer);
}

int32_t OH_ArkUI_GetGestureRecognizerState(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureRecognizerState* state)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUIGestureRecognizerState recognizerState;
    auto result =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->getGestureRecognizerState(
            gestureRecognizer, &recognizerState);
    *state = static_cast<ArkUI_GestureRecognizerState>(recognizerState);
    return result;
}

int32_t OH_ArkUI_GetGestureEventTargetInfo(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventTargetInfo** info)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *info = reinterpret_cast<ArkUI_GestureEventTargetInfo*>(&gestureRecognizer->targetInfo);
    return 0;
}

int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(ArkUI_GestureEventTargetInfo* info, bool* ret)
{
    auto* targetInfo = reinterpret_cast<ArkUIGestureEventTargetInfo*>(info);
    if (!targetInfo) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->gestureEventTargetInfoIsScrollBegin(targetInfo, ret);
}

int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(ArkUI_GestureEventTargetInfo* info, bool* ret)
{
    auto* targetInfo = reinterpret_cast<ArkUIGestureEventTargetInfo*>(info);
    if (!targetInfo) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->gestureEventTargetInfoIsScrollEnd(targetInfo, ret);
}

int32_t OH_ArkUI_GetPanGestureDirectionMask(
    ArkUI_GestureRecognizer* recognizer, ArkUI_GestureDirectionMask* directionMask)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUIGestureDirection direction = ArkUIGestureDirection::ArkUI_GESTURE_DIRECTION_ALL;
    auto result =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->getPanGestureDirectionMask(
            gestureRecognizer, &direction);
    *directionMask = static_cast<ArkUI_GestureDirectionMask>(direction);
    return result;
}

bool OH_ArkUI_IsBuiltInGesture(ArkUI_GestureRecognizer* recognizer)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return false;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->isBuiltInGesture(
        gestureRecognizer);
}

int32_t OH_ArkUI_GetGestureTag(ArkUI_GestureRecognizer* recognizer, char* buffer, int32_t bufferSize, int32_t* result)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->getGestureTag(
        gestureRecognizer, buffer, bufferSize, result);
}

int32_t OH_ArkUI_GetGestureBindNodeId(ArkUI_GestureRecognizer* recognizer, char* nodeId, int32_t size, int32_t* result)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->getGestureBindNodeId(
        gestureRecognizer, nodeId, size, result);
}

bool OH_ArkUI_IsGestureRecognizerValid(ArkUI_GestureRecognizer* recognizer)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer) {
        return false;
    }
    return OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->isGestureRecognizerValid(
        gestureRecognizer);
}

void* OH_ArkUI_ParallelInnerGestureEvent_GetUserData(ArkUI_ParallelInnerGestureEvent* event)
{
    return event->userData;
}

ArkUI_GestureRecognizer* OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer(ArkUI_ParallelInnerGestureEvent* event)
{
    return reinterpret_cast<ArkUI_GestureRecognizer*>(event->current);
}

int32_t OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(
    ArkUI_ParallelInnerGestureEvent* event, ArkUI_GestureRecognizerHandleArray* array, int32_t* size)
{
    CHECK_NULL_RETURN(array, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(size, ARKUI_ERROR_CODE_PARAM_INVALID);
    *array = reinterpret_cast<ArkUI_GestureRecognizer**>(event->responseLinkRecognizer);
    *size = event->count;
    return 0;
}

int32_t OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(
    ArkUI_GestureRecognizer* recognizer, ArkUI_GestureRecognizerDisposeNotifyCallback callback, void* userData)
{
    auto* gestureRecognizer = reinterpret_cast<ArkUIGestureRecognizer*>(recognizer);
    if (!gestureRecognizer || gestureRecognizer->capi) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto disposeCallback = reinterpret_cast<void (*)(ArkUIGestureRecognizer * recognizer, void* userData)>(callback);
    OHOS::Ace::NodeModel::GetFullImpl()
        ->getNodeModifiers()
        ->getGestureModifier()
        ->setArkUIGestureRecognizerDisposeNotify(gestureRecognizer, userData, disposeCallback);
    return 0;
}

namespace OHOS::Ace::GestureModel {

constexpr int32_t DEFAULT_PAN_FINGERS = 1;
constexpr int32_t MAX_PAN_FINGERS = 10;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0f;
constexpr double DEFAULT_SWIPE_SPEED = 100.0f;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr int32_t DEFAULT_TAP_FINGERS = 1;
constexpr int32_t MAX_TAP_FINGERS = 10;

struct GestureInnerData {
    void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParam);
    void* extraParam;
    void* gesture;
};

ArkUI_GestureRecognizer* CreateTapGesture(int32_t count, int32_t fingers)
{
    count = std::max(count, DEFAULT_TAP_COUNT);
    fingers = std::clamp(fingers, DEFAULT_TAP_FINGERS, MAX_TAP_FINGERS);
    auto* ndkGesture = new ArkUI_GestureRecognizer{ TAP_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createTapGesture(
        count, fingers, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreateTapGestureWithDistanceThreshold(
    int32_t count, int32_t fingers, double distanceThreshold)
{
    count = std::max(count, DEFAULT_TAP_COUNT);
    fingers = std::clamp(fingers, DEFAULT_TAP_FINGERS, MAX_TAP_FINGERS);
    auto* ndkGesture = new ArkUI_GestureRecognizer{ TAP_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->
        createTapGestureWithDistanceThreshold(count, fingers, distanceThreshold, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreateLongPressGesture(int32_t fingers, bool repeatResult, int32_t duration)
{
    auto* ndkGesture = new ArkUI_GestureRecognizer{ LONG_PRESS_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createLongPressGesture(fingers,
        repeatResult, duration, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreatePinchGesture(int32_t fingers, double distance)
{
    if (LessOrEqual(distance, 0.0f)) {
        distance = DEFAULT_PINCH_DISTANCE;
    }
    double distanceNum = OHOS::Ace::NodeModel::GetFullImpl()->getBasicAPI()->convertLengthMetricsUnit(
        distance, static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_PX), static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_VP));
    auto* ndkGesture = new ArkUI_GestureRecognizer{ PINCH_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createPinchGesture(fingers,
        distanceNum, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreateRotationGesture(int32_t fingers, double angle)
{
    auto* ndkGesture = new ArkUI_GestureRecognizer{ ROTATION_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createRotationGesture(fingers,
        angle, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreateSwipeGesture(
    int32_t fingers, ArkUI_GestureDirectionMask directions, double speed)
{
    if (LessOrEqual(speed, 0.0f)) {
        speed = DEFAULT_SWIPE_SPEED;
    }
    double speedNum = OHOS::Ace::NodeModel::GetFullImpl()->getBasicAPI()->convertLengthMetricsUnit(
        speed, static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_PX), static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_VP));
    auto* ndkGesture = new ArkUI_GestureRecognizer{ SWIPE_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createSwipeGesture(fingers,
        directions, speedNum, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

ArkUI_GestureRecognizer* CreatePanGesture(int32_t fingersNum, ArkUI_GestureDirectionMask mask, double distanceNum)
{
    int32_t fingers = DEFAULT_PAN_FINGERS;
    if (fingersNum < DEFAULT_PAN_FINGERS || fingersNum > MAX_PAN_FINGERS) {
        fingers = DEFAULT_PAN_FINGERS;
    } else {
        fingers = fingersNum;
    }
    auto* ndkGesture = new ArkUI_GestureRecognizer{ PAN_GESTURE, nullptr, nullptr, nullptr };
    auto* gesture = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createPanGesture(
        fingers, mask, distanceNum, false, ndkGesture);
    ndkGesture->gesture = gesture;
    return ndkGesture;
}

void DisposeGesture(ArkUI_GestureRecognizer* recognizer)
{
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->dispose(recognizer->gesture);
    delete reinterpret_cast<GestureInnerData*>(recognizer->extraData);
    recognizer->extraData = nullptr;
    delete recognizer;
    recognizer = nullptr;
}

int32_t SetGestureEventTarget(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask mask,
    void* extraParam, void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParam))
{
    // 手势事件通过通用的异步事件接口进行处理。(HandleGestureEvent)
    // 把回调函数和上下文都封装到内部结构体中。
    if (recognizer->extraData) {
        delete reinterpret_cast<GestureInnerData*>(recognizer->extraData);
        recognizer->extraData = nullptr;
    }
    recognizer->extraData = new GestureInnerData { targetReceiver, extraParam, recognizer };
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->registerGestureEvent(
        recognizer->gesture, mask, recognizer->extraData);
    return 0;
}

int32_t AddGestureToNode(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority priorityNum,
    ArkUI_GestureMask mask)
{
    recognizer->attachNode = node;
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->addGestureToNode(
        node->uiNodeHandle, recognizer->gesture, priorityNum, mask);
    recognizer->targetInfo.uiNode = reinterpret_cast<void*>(node->uiNodeHandle);
    return 0;
}

int32_t RemoveGestureFromNode(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer)
{
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->removeGestureFromNode(
        node->uiNodeHandle, recognizer->gesture);
    recognizer->targetInfo.uiNode = nullptr;
    return 0;
}

ArkUI_GestureRecognizerType GetGestureType(ArkUI_GestureRecognizer* recognizer)
{
    return static_cast<ArkUI_GestureRecognizerType>(recognizer->type);
}

ArkUI_GestureRecognizer* CreateGroupGesture(ArkUI_GroupGestureMode gestureMode)
{
    auto* gesture =
        OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->createGestureGroup(gestureMode);
    return new ArkUI_GestureRecognizer { GROUP_GESTURE, gesture, nullptr };
}

int32_t AddChildGesture(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child)
{
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->addGestureToGestureGroup(
        group->gesture, child->gesture);
    return 0;
}

int32_t RemoveChildGesture(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child)
{
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->removeGestureFromGestureGroup(
        group->gesture, child->gesture);
    return 0;
}

void HandleGestureEvent(ArkUINodeEvent* event)
{
    if (event == nullptr) {
        return;
    }
    auto* extraData = reinterpret_cast<GestureInnerData*>(event->extraParam);
    if (extraData == nullptr) {
        return;
    }
    ArkUI_GestureEvent* gestureEvent = reinterpret_cast<ArkUI_GestureEvent *>(&event->gestureAsyncEvent);
    if (gestureEvent == nullptr || extraData->targetReceiver == nullptr) {
        return;
    }
    ArkUI_UIInputEvent uiEvent;
    if (gestureEvent->eventData.inputEventType == static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_MOUSE)) {
        uiEvent.eventTypeId = C_MOUSE_EVENT_ID;
        uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_MOUSE;
    } else if (gestureEvent->eventData.inputEventType == static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_AXIS)) {
        uiEvent.eventTypeId = C_AXIS_EVENT_ID;
        uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
    } else {
        uiEvent.eventTypeId = C_TOUCH_EVENT_ID;
        uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
    }
    uiEvent.inputEvent = gestureEvent->eventData.rawPointerEvent;
    gestureEvent->eventData.rawPointerEvent = &uiEvent;
    if (extraData->gesture) {
        ArkUI_GestureRecognizer* recognizer = reinterpret_cast<ArkUI_GestureRecognizer*>(extraData->gesture);
        gestureEvent->attachNode = recognizer->attachNode;
    }
    extraData->targetReceiver(gestureEvent, extraData->extraParam);
}

int32_t SetGestureInterrupterToNode(
    ArkUI_NodeHandle node,  ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info))
{
    auto callback = reinterpret_cast<int32_t (*)(ArkUIGestureInterruptInfo*)>(interrupter);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->setGestureInterrupterToNode(
        node->uiNodeHandle, callback);
    return 0;
}

int32_t SetInnerGestureParallelTo(ArkUI_NodeHandle node, void* userData,
    ArkUI_GestureRecognizer* (*parallelInnerGesture)(ArkUI_ParallelInnerGestureEvent* event))
{
    auto callback =
        reinterpret_cast<ArkUIGestureRecognizer* (*)(ArkUIParallelInnerGestureEvent * current)>(parallelInnerGesture);
    OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers()->getGestureModifier()->setInnerGestureParallelTo(
        node->uiNodeHandle, userData, callback);
    return 0;
}

}; // namespace OHOS::Ace::GestureModel