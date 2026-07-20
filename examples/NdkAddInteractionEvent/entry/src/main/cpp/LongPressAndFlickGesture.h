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

#ifndef LONG_PRESS_AND_FLICK_GESTURE_H
#define LONG_PRESS_AND_FLICK_GESTURE_H
// [Start long_press_and_flick_gesture]
// LongPressAndFlickGesture.h
#include <arkui/native_animate.h>
#include <arkui/native_gesture.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <arkui/native_node_napi.h>
#include <hilog/log.h>
#include "Common.h"
#include "Function.h"
// [StartExclude long_press_and_flick_gesture]
namespace NativeModule {
// [EndExclude long_press_and_flick_gesture]

// [StartExclude long_press_and_flick_gesture]
ArkUI_NodeHandle CreateParallelGestureColumn()
{
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);

    // 创建节点
    ArkUI_NumberValue value[] = {{.u32 = 0xff112233}};
    ArkUI_AttributeItem item = {value, ITEM_SIZE_ONE};
    nodeAPI->setAttribute(column, NODE_BACKGROUND_COLOR, &item);
    ArkUI_NumberValue widthValue[] = {{WIDTH_SIZE}};
    ArkUI_AttributeItem width = {widthValue, ITEM_SIZE_ONE};
    nodeAPI->setAttribute(column, NODE_WIDTH, &width);
    ArkUI_NumberValue heightValue[] = {{HEIGHT_SIZE}};
    ArkUI_AttributeItem height = {heightValue, ITEM_SIZE_ONE};
    nodeAPI->setAttribute(column, NODE_HEIGHT, &height);
    return column;
}

void CreateParallelLongPressGesture(ArkUI_NativeGestureAPI_1 *gestureApi, ArkUI_GestureRecognizerHandle groupGesture,
    ArkUI_NodeHandle column)
{
    // 创建长按手势
    auto longPressGesture = gestureApi->createLongPressGesture(FINGERS_NUM, true, DURATION_NUM_500);
    if (gestureApi->getGestureType) {
        ArkUI_GestureRecognizerType type = gestureApi->getGestureType(longPressGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog,ArkUI_GestureRecognizerType%{public}d", type);
    }
    // 给长按手势绑定回调
    auto onActionCallBackPanLongPress = [](ArkUI_GestureEvent *event, void *extraParam) {
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

        OH_LOG_Print(
            LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
            "NdkAddInteractionEvent_GestureSampleLog,longPressGesturecallback actionType:%{public}d,"
            "velocity%{public}f,velocityX%{public}f;"
            "velocityY%{public}f,offsetX%{public}f,offsetY%{public}f,scale%{public}f, centerX "
            "%{public}fcenterY"
            "%{public}fangle%{public}fvelocityS%{public}fangleR%{public}frepeat%{public}f",
            actionType, velocity, velocityX, velocityY, offsetX, offsetY, scale, centerX, centerY, angle, velocityS,
            angleR, repeat);
    };
    gestureApi->setGestureEventTarget(longPressGesture,
                                      GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE |
                                            GESTURE_EVENT_ACTION_CANCEL,
                                      column, onActionCallBackPanLongPress);

    // 将长按手势添加到手势组
    if (gestureApi->addChildGesture) {
        gestureApi->addChildGesture(groupGesture, longPressGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog, addChildGesture longPressGesture");
    }
}

void CreateParallelSwipeGesture(ArkUI_NativeGestureAPI_1 *gestureApi, ArkUI_GestureRecognizerHandle groupGesture,
    ArkUI_NodeHandle column)
{
    // 创建快滑手势 swipe
    auto swipeGesture = gestureApi->createSwipeGesture(FINGERS_NUM, GESTURE_DIRECTION_ALL, DURATION_NUM_100);
    if (gestureApi->getGestureType) {
        ArkUI_GestureRecognizerType type = gestureApi->getGestureType(swipeGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog, ArkUI_GestureRecognizerType %{public}d",
                     type);
    }
    // 给快滑手势绑定回调
    auto onActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {
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
                     "NdkAddInteractionEvent_GestureSampleLog, swipeGesture "
                     "callback actionType: %{public}d, velocity%{public}f,velocityX "
                     "%{public}f; "
                     "velocityY %{public}f, offsetX %{public}f, offsetY %{public}f, scale %{public}f, centerX "
                     "%{public}f centerY"
                     " %{public}f angle %{public}f velocityS %{public}f angleR %{public}f repeat %{public}f",
                     actionType, velocity, velocityX, velocityY, offsetX, offsetY, scale, centerX, centerY, angle,
                     velocityS, angleR, repeat);

        ArkUI_NumberValue value[] = {{.f32 = 0}, {.f32 = 0}, {.f32 = 0}, {.f32 = angleR}, {.f32 = 0}};
        ArkUI_AttributeItem item = {value, ITEM_SIZE_FIVE};
        auto column = reinterpret_cast<ArkUI_NodeHandle>(extraParam);
        nodeAPI->setAttribute(column, NODE_ROTATE, &item);
    };

    gestureApi->setGestureEventTarget(
        swipeGesture, GESTURE_EVENT_ACTION_ACCEPT | GESTURE_EVENT_ACTION_UPDATE | GESTURE_EVENT_ACTION_END, column,
        onActionCallBack);

    // 将快滑手势添加到手势组
    if (gestureApi->addChildGesture) {
        gestureApi->addChildGesture(groupGesture, swipeGesture);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog, addChildGesture swipeGesture");
    }
}
// [EndExclude long_press_and_flick_gesture]

ArkUI_NodeHandle LongPressAndFlickGesture()
{
    auto column = CreateParallelGestureColumn();

    // 判断是否支持创建手势
    auto gestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
    if (gestureApi->createGroupGesture) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog, createGroupGesture api exist");
    } else {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                     "NdkAddInteractionEvent_GestureSampleLog, createGroupGesture api not exist");
    }

    // 创建手势组
    auto groupGesture = gestureApi->createGroupGesture(ArkUI_GroupGestureMode::PARALLEL_GROUP);

    CreateParallelLongPressGesture(gestureApi, groupGesture, column);
    CreateParallelSwipeGesture(gestureApi, groupGesture, column);

    // 将手势组设置到组件上
    gestureApi->addGestureToNode(column, groupGesture, PRIORITY, NORMAL_GESTURE_MASK);
    return column;
}
// [End long_press_and_flick_gesture]
} // namespace NativeXComponentSample

#endif // LONG_PRESS_AND_FLICK_GESTURE_H
