/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef SWIPE_AND_PINCH_EXCLUSIVE_GESTURE_H
#define SWIPE_AND_PINCH_EXCLUSIVE_GESTURE_H

// [Start swipe_and_pinch_exclusive_gesture]
// SwipeAndPinchExclusiveGesture.h
#include <arkui/native_animate.h>
#include <arkui/native_gesture.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <arkui/native_node_napi.h>
#include <hilog/log.h>
#include "Common.h"
#include "Function.h"
// [StartExclude swipe_and_pinch_exclusive_gesture]
namespace NativeModule {
// [EndExclude swipe_and_pinch_exclusive_gesture]

// [StartExclude swipe_and_pinch_exclusive_gesture]
ArkUI_NodeHandle CreateExclusiveGestureColumn()
{
    if (!nodeAPI) {
        return nullptr;
    }
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);

    // 创建节点
    ArkUI_NumberValue value[] = { { .u32 = 0xff112233 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(column, NODE_BACKGROUND_COLOR, &item);
    ArkUI_NumberValue widthValue[] = { { WIDTH_SIZE } };
    ArkUI_AttributeItem width = { widthValue, ITEM_SIZE_ONE };
    nodeAPI->setAttribute(column, NODE_WIDTH, &width);
    ArkUI_NumberValue heightValue[] = { { HEIGHT_SIZE } };
    ArkUI_AttributeItem height = { heightValue, ITEM_SIZE_ONE };
    nodeAPI->setAttribute(column, NODE_HEIGHT, &height);
    return column;
}

void CreatePanGesture(ArkUI_NativeGestureAPI_1* gestureApi, ArkUI_GestureRecognizerHandle groupGesture,
    ArkUI_NodeHandle column)
{
    // 创建滑动手势
    auto panGesture = gestureApi->createPanGesture(FINGERS_NUM, GESTURE_DIRECTION_VERTICAL, DURATION_NUM);
    if (gestureApi->getGestureType) {
        ArkUI_GestureRecognizerType type = gestureApi->getGestureType(panGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog panGesture, ArkUI_GestureRecognizerType %{public}d", type);
    }
    // 给滑动手势绑定回调
    auto onActionCallBackPan = [](ArkUI_GestureEvent* event, void* extraParam) {
        ArkUI_GestureEventActionType actionType = OH_ArkUI_GestureEvent_GetActionType(event);

        float velocity = OH_ArkUI_PanGesture_GetVelocity(event);
        float velocityX = OH_ArkUI_PanGesture_GetVelocityX(event);
        float velocityY = OH_ArkUI_PanGesture_GetVelocityY(event);
        float offsetX = OH_ArkUI_PanGesture_GetOffsetX(event);
        float offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
        float scale = OH_ArkUI_PinchGesture_GetScale(event);
        float centerX = OH_ArkUI_PinchGesture_GetCenterX(event);
        float centerY = OH_ArkUI_PinchGesture_GetCenterY(event);
        float angle = OH_ArkUI_SwipeGesture_GetAngle(event);
        float velocityS = OH_ArkUI_SwipeGesture_GetVelocity(event);
        float angleR = OH_ArkUI_RotationGesture_GetAngle(event);
        float repeat = OH_ArkUI_LongPress_GetRepeatCount(event);

        // 通过日志查看
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, panGesture callback actionType: %{public}d, "
            "velocity %{public}f,velocityX %{public}f; "
            "velocityY %{public}f, offsetX %{public}f, offsetY %{public}f, scale %{public}fcenterX "
            "%{public}f centerY"
            " %{public}f angle %{public}f velocityS %{public}f angleR %{public}f repeat %{public}f",
            actionType, velocity, velocityX, velocityY, offsetX, offsetY, scale, centerX, centerY, angle, velocityS,
            angleR, repeat);
    };
    gestureApi->setGestureEventTarget(panGesture,
        GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE | GESTURE_EVENT_ACTION_END |
            GESTURE_EVENT_ACTION_CANCEL,
        column, onActionCallBackPan);
    // 将滑动手势添加到手势组
    if (gestureApi->addChildGesture) {
        gestureApi->addChildGesture(groupGesture, panGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, addChildGesture panGesture");
    }
}

void CreatePinchGesture(ArkUI_NativeGestureAPI_1* gestureApi, ArkUI_GestureRecognizerHandle groupGesture,
    ArkUI_NodeHandle column)
{
    // 创建捏合手势
    auto pinchGesture = gestureApi->createPinchGesture(0, 0);
    if (gestureApi->getGestureType) {
        ArkUI_GestureRecognizerType type = gestureApi->getGestureType(pinchGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog pinchGesture, "
            "ArkUI_GestureRecognizerType %{public}d",
            type);
    }
    // 给捏合手势绑定回调
    auto onActionCallBack = [](ArkUI_GestureEvent* event, void* extraParam) {
        ArkUI_GestureEventActionType actionType = OH_ArkUI_GestureEvent_GetActionType(event);

        float velocity = OH_ArkUI_PanGesture_GetVelocity(event);
        float velocityX = OH_ArkUI_PanGesture_GetVelocityX(event);
        float velocityY = OH_ArkUI_PanGesture_GetVelocityY(event);
        float offsetX = OH_ArkUI_PanGesture_GetOffsetX(event);
        float offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
        float scale = OH_ArkUI_PinchGesture_GetScale(event);
        float centerX = OH_ArkUI_PinchGesture_GetCenterX(event);
        float centerY = OH_ArkUI_PinchGesture_GetCenterY(event);
        float angle = OH_ArkUI_SwipeGesture_GetAngle(event);
        float velocityS = OH_ArkUI_SwipeGesture_GetVelocity(event);
        float angleR = OH_ArkUI_RotationGesture_GetAngle(event);
        float repeat = OH_ArkUI_LongPress_GetRepeatCount(event);

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, pinchGesture callback actionType: %{public}d, "
            "velocity %{public}f,velocityX %{public}f; "
            "velocityY %{public}f, offsetX %{public}f, offsetY %{public}f, scale %{public}fcenterX "
            "%{public}f centerY"
            " %{public}f angle %{public}f velocityS %{public}f angleR %{public}f repeat %{public}f",
            actionType, velocity, velocityX, velocityY, offsetX, offsetY, scale, centerX, centerY, angle, velocityS,
            angleR, repeat);
        ArkUI_NumberValue value[] = { { .f32 = scale }, { .f32 = scale } };
        ArkUI_AttributeItem item = { value, ITEM_SIZE_TWO };
        auto column = reinterpret_cast<ArkUI_NodeHandle>(extraParam);
        nodeAPI->setAttribute(column, NODE_SCALE, &item);
    };
    gestureApi->setGestureEventTarget(pinchGesture,
        GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE | GESTURE_EVENT_ACTION_END |
            GESTURE_EVENT_ACTION_CANCEL,
        column, onActionCallBack);
    // 将捏合手势添加到手势组
    if (gestureApi->addChildGesture) {
        gestureApi->addChildGesture(groupGesture, pinchGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, addChildGesture pinchGesture");
    }
}
// [EndExclude swipe_and_pinch_exclusive_gesture]

ArkUI_NodeHandle SwipeAndPinchExclusiveGesture()
{
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto column = CreateExclusiveGestureColumn();
    if (column == nullptr) {
        return nullptr;
    }

    // 判断是否支持创建手势
    auto gestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
    if (gestureApi->createGroupGesture) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, createGroupGesture api exist");
    } else {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog, createGroupGesture api not exist");
    }
    auto groupGesture = gestureApi->createGroupGesture(ArkUI_GroupGestureMode::EXCLUSIVE_GROUP);

    CreatePanGesture(gestureApi, groupGesture, column);
    CreatePinchGesture(gestureApi, groupGesture, column);

    // 将手势组设置到组件上
    gestureApi->addGestureToNode(column, groupGesture, PRIORITY, NORMAL_GESTURE_MASK);
    return column;
}
// [End swipe_and_pinch_exclusive_gesture]
} // namespace NativeModule
#endif // SWIPE_AND_PINCH_EXCLUSIVE_GESTURE_H
