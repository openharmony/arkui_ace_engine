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

#include "napi/native_api.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_animate.h>
#include <arkui/native_gesture.h>
#include <arkui/native_interface.h>
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <cstdio>
#include <hilog/log.h>
#include <iostream>
#include <string>

#include "manager.h"


namespace NativeXComponentSample {
Manager Manager::manager_;

Manager::~Manager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "~Manager");
    for (auto iter = nativeXComponentMap_.begin(); iter != nativeXComponentMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            iter->second = nullptr;
        }
    }
    nativeXComponentMap_.clear();

    for (auto iter = containerMap_.begin(); iter != containerMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    containerMap_.clear();
}

static ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
static ArkUI_NativeGestureAPI_1 *gestureApi = nullptr;
static const int NUM_2 = 2;
static const int COLUMN_SIZE = 600;
static double g_moveSize = 200.0;


void SetTextAttribute(ArkUI_NodeHandle &node, const char *str)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {150};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = {120};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_NumberValue colorValue[] = {{.u32 = 0xFF2FF3FF}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    ArkUI_AttributeItem text_valueItem = {.string = str};
    ArkUI_NumberValue borderWidthValue[] = {1};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_WIDTH, &borderWidthItem);
    nodeAPI->setAttribute(node, NODE_TEXT_CONTENT, &text_valueItem);
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
}

void SetColumnAttribute(ArkUI_NodeHandle &node, float width, float height, unsigned int color)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {width};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = {height};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_NumberValue colorValue[] = {{.u32 = color}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
}

void Manager::CreateNode(ArkUI_NodeHandle &textShow2)
{
    ArkUI_NumberValue widthValue[] = {200};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = {150};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_NumberValue colorValue[] = {{.u32 = 0xF2F2F3F0}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    ArkUI_AttributeItem text_valueItem = {.string = "output"};
    ArkUI_NumberValue borderWidthValue[] = {1};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(textShow2, NODE_BORDER_WIDTH, &borderWidthItem);
    nodeAPI->setAttribute(textShow2, NODE_TEXT_CONTENT, &text_valueItem);
    nodeAPI->setAttribute(textShow2, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(textShow2, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(textShow2, NODE_BACKGROUND_COLOR, &colorItem);
    ArkUI_AttributeItem textShow2_valueItem = {.string = ""};
    nodeAPI->setAttribute(textShow2, NODE_TEXT_CONTENT, &textShow2_valueItem);
    manager_.textShow2_ = textShow2;
}

void Manager::SetClearButtonAttribute(ArkUI_NodeHandle &node)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {100};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = {50};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_AttributeItem text_valueItem = {.string = "Clear output"};
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(node, NODE_BUTTON_LABEL, &text_valueItem);
    if (!gestureApi) {
        return;
    }
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = ""};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column1 tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(node, tapGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

void SetRowAttribute(ArkUI_NodeHandle &node)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {300};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = {120};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_NumberValue colorValue[] = {{.u32 = 0xFF2FF3FF}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    ArkUI_NumberValue borderWidthValue[] = {1};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
    nodeAPI->setAttribute(node, NODE_BORDER_WIDTH, &borderWidthItem);
}

ArkUI_GestureInterruptResult ProcessDifferentGesture(int32_t type, ArkUI_GestureRecognizer* recognizer)
{
    // 判断手势类型
    switch (type) {
        case ArkUI_GestureRecognizerType::TAP_GESTURE: {
            double distanceThreshold = 0;
            OH_ArkUI_GetGestureParam_distanceThreshold(recognizer, &distanceThreshold);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback distanceThreshold %{public}lf", distanceThreshold);
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
        }
        case ArkUI_GestureRecognizerType::LONG_PRESS_GESTURE: {
            bool repeat = false;
            OH_ArkUI_GetGestureParam_repeat(recognizer, &repeat);
            int duration = false;
            OH_ArkUI_GetGestureParam_duration(recognizer, &duration);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback repeat %{public}d duration %{public}d", repeat, duration);
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        }
        case ArkUI_GestureRecognizerType::PAN_GESTURE: {
            ArkUI_GestureDirectionMask direction = ArkUI_GestureDirection::GESTURE_DIRECTION_NONE;
            OH_ArkUI_GetGestureParam_DirectMask(recognizer, &direction);
            double distance = 0.0;
            OH_ArkUI_GetGestureParam_distance(recognizer, &distance);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback direction %{public}d distance %{public}lf", direction, distance);
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
        }
        case ArkUI_GestureRecognizerType::PINCH_GESTURE:
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        case ArkUI_GestureRecognizerType::ROTATION_GESTURE: {
            double angle = 0.0;
            OH_ArkUI_GetGestureParam_angle(recognizer, &angle);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback angle %{public}lf", angle);
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        }
        case ArkUI_GestureRecognizerType::SWIPE_GESTURE: {
            double speed = 0.0;
            OH_ArkUI_GetGestureParam_speed(recognizer, &speed);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback speed %{public}lf", speed);
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        }
        case ArkUI_GestureRecognizerType::CLICK_GESTURE:
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        case ArkUI_GestureRecognizerType::DRAG_DROP:
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
    }
    return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
}

// 绑定单一点击手势
void Manager::SetTapGesture(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column1 tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, tapGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定单一移动手势
void Manager::SetPanGestureWithDirection(ArkUI_NodeHandle &column, ArkUI_GestureDirection direction)
{
    if (!gestureApi) {
        return;
    }
    auto panGesture = gestureApi->createPanGesture(1, direction, 1);
    // 设置手势限定手指数
    OH_ArkUI_SetGestureRecognizerLimitFingerCount(panGesture, true);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        panGesture,
        ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_ACCEPT |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_UPDATE |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_END |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_CANCEL,
        nullptr, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "panGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column2 panGesture is called");
            // 获取手势回调信息
            auto rawInputEvent = OH_ArkUI_GestureEvent_GetRawInputEvent(event);
            auto action = OH_ArkUI_UIInputEvent_GetAction(rawInputEvent);
            auto node = OH_ArkUI_GestureEvent_GetNode(event);
            auto childSize = nodeAPI->getTotalChildCount(node);
            auto actionType = OH_ArkUI_GestureEvent_GetActionType(event);
            auto offsetX = OH_ArkUI_PanGesture_GetOffsetX(event);
            auto offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
            auto velocityX = OH_ArkUI_PanGesture_GetVelocityX(event);
            auto velocityY = OH_ArkUI_PanGesture_GetVelocityY(event);
            auto velocity = OH_ArkUI_PanGesture_GetVelocity(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column2 panGesture is called rawEvent action %{public}d childSize %{public}d actionType "
                         "%{public}d, offsetX "
                         "%{public}f, offsetY %{public}f, "
                         "velocityX %{public}f, velocityY %{public}f, velocity %{public}f",
                         action, childSize, actionType, offsetX, offsetY, velocityX, velocityY, velocity);
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, panGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定单一长按手势
void Manager::SetLongPressGesture(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto longPressGesture = gestureApi->createLongPressGesture(1, true, 500);
    OH_ArkUI_LongPressGesture_SetAllowableMovement(longPressGesture, g_moveSize);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "longPressGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column longPressGesture is called");
            // 获取手势回调信息
            auto repeat = OH_ArkUI_LongPress_GetRepeatCount(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column longPressGesture is called repeat %{public}d", repeat);
        });
    double* allowableMovement;
    OH_ArkUI_LongPressGesture_GetAllowableMovement(longPressGesture, allowableMovement);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                 "column longPressGesture allow movement %{public}f", allowableMovement);
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, longPressGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定单一捏合手势
void Manager::SetPinchGesture(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto pinchGesture = gestureApi->createPinchGesture(2, 5);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        pinchGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "pinchGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column longPressGesture is called");
            // 获取手势回调信息
            auto scale = OH_ArkUI_PinchGesture_GetScale(event);
            auto pinchCenterX = OH_ArkUI_PinchGesture_GetCenterX(event);
            auto pinchCenterY = OH_ArkUI_PinchGesture_GetCenterY(event);
            OH_LOG_Print(
                LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "column longPressGesture is called scale %{public}f pinchCenterX %{public}f pinchCenterY %{public}f",
                scale, pinchCenterX, pinchCenterY);
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, pinchGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定单一旋转手势
void Manager::SetRotationGesture(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto rotationGesture = gestureApi->createRotationGesture(2, 10);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        rotationGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "rotationGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column rotationGesture is called");
            // 获取手势回调信息
            auto angle = OH_ArkUI_RotationGesture_GetAngle(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column rotationGesture is called angle %{public}f", angle);
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, rotationGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定单一快滑手势
void Manager::SetSwipeGesture(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto swipeGesture = gestureApi->createSwipeGesture(1, ArkUI_GestureDirection::GESTURE_DIRECTION_HORIZONTAL, 100);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        swipeGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "swipeGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column swipeGesture is called");
            // 获取手势回调信息
            auto angle = OH_ArkUI_SwipeGesture_GetAngle(event);
            auto velocity = OH_ArkUI_SwipeGesture_GetVelocity(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column swipeGesture is called angle %{public}f velocity %{public}f", angle, velocity);
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, swipeGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定带移动阈值的点击手势
void Manager::SetTapGestureWithDistance(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto tapGesture = gestureApi->createTapGestureWithDistanceThreshold(1, 1, 10);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "createTapGestureWithDistanceThreshold is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "createTapGestureWithDistanceThreshold tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, tapGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定手势组
void Manager::CreateGestureGroup(ArkUI_NodeHandle &column, ArkUI_GroupGestureMode mode)
{
    if (!gestureApi) {
        return;
    }
    auto group = gestureApi->createGroupGesture(mode);
    auto longPressGesture = gestureApi->createLongPressGesture(1, true, 500);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "longPressGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column longPressGesture is called");
            auto repeat = OH_ArkUI_LongPress_GetRepeatCount(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column longPressGesture is called repeat %{public}d", repeat);
        });
    auto panGesture = gestureApi->createPanGesture(1, ArkUI_GestureDirection::GESTURE_DIRECTION_HORIZONTAL, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        panGesture,
        ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_ACCEPT |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_UPDATE |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_END |
            ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_CANCEL,
        nullptr, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "panGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column2 panGesture is called");
            auto rawInputEvent = OH_ArkUI_GestureEvent_GetRawInputEvent(event);
            auto action = OH_ArkUI_UIInputEvent_GetAction(rawInputEvent);
            auto node = OH_ArkUI_GestureEvent_GetNode(event);
            auto childSize = nodeAPI->getTotalChildCount(node);
            auto actionType = OH_ArkUI_GestureEvent_GetActionType(event);
            auto offsetX = OH_ArkUI_PanGesture_GetOffsetX(event);
            auto offsetY = OH_ArkUI_PanGesture_GetOffsetY(event);
            auto velocityX = OH_ArkUI_PanGesture_GetVelocityX(event);
            auto velocityY = OH_ArkUI_PanGesture_GetVelocityY(event);
            auto velocity = OH_ArkUI_PanGesture_GetVelocity(event);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                         "column2 panGesture is called rawEvent action %{public}d childSize %{public}d actionType "
                         "%{public}d, offsetX "
                         "%{public}f, offsetY %{public}f, "
                         "velocityX %{public}f, velocityY %{public}f, velocity %{public}f",
                         action, childSize, actionType, offsetX, offsetY, velocityX, velocityY, velocity);
        });
    auto tapGesture = gestureApi->createTapGestureWithDistanceThreshold(1, 1, 10);
    // 给手势组添加子手势
    gestureApi->addChildGesture(group, tapGesture);
    gestureApi->addChildGesture(group, longPressGesture);
    gestureApi->addChildGesture(group, panGesture);
    // 给手势组删除子手势
    gestureApi->removeChildGesture(group, tapGesture);
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, group, ArkUI_GesturePriority::NORMAL, ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 设置事件响应设置
void Manager::CreateGestureWithMask(ArkUI_NodeHandle &column, ArkUI_GestureMask mask)
{
    if (!gestureApi) {
        return;
    }
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column1 tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, tapGesture, ArkUI_GesturePriority::NORMAL, mask);
}

// 设置手势绑定的优先级
void Manager::CreateGestureWithPriority(ArkUI_NodeHandle &node, ArkUI_GesturePriority priority)
{
    if (!gestureApi) {
        return;
    }
    nodeAPI->registerNodeEvent(node, NODE_ON_CLICK_EVENT, 0, nullptr);
    nodeAPI->addNodeEventReceiver(node, [](ArkUI_NodeEvent *event) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "node onClick is called");
    });
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "node tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(node, tapGesture, priority, ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

// 绑定多种手势组成的手势组
void Manager::SetMultiGesture(ArkUI_NodeHandle &node)
{
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    auto group = gestureApi->createGroupGesture(ArkUI_GroupGestureMode::EXCLUSIVE_GROUP);
    auto longPressGesture = gestureApi->createLongPressGesture(1, true, 500);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "longPressGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    auto panGesture = gestureApi->createPanGesture(1, ArkUI_GestureDirection::GESTURE_DIRECTION_HORIZONTAL, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(panGesture, ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_ACCEPT, nullptr,
        [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "panGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    auto pinchGesture = gestureApi->createPinchGesture(2, 5);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        pinchGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "pinchGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    auto rotationGesture = gestureApi->createRotationGesture(2, 10);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        rotationGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "rotationGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    auto swipeGesture = gestureApi->createSwipeGesture(1, ArkUI_GestureDirection::GESTURE_DIRECTION_HORIZONTAL, 100);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        swipeGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "swipeGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        });
    gestureApi->addChildGesture(group, tapGesture);
    gestureApi->addChildGesture(group, longPressGesture);
    gestureApi->addChildGesture(group, panGesture);
    gestureApi->addChildGesture(group, pinchGesture);
    gestureApi->addChildGesture(group, rotationGesture);
    gestureApi->addChildGesture(group, swipeGesture);
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(node, group, ArkUI_GesturePriority::NORMAL, ArkUI_GestureMask::NORMAL_GESTURE_MASK);
    // 获取手势类型
    auto type = gestureApi->getGestureType(group);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "gesture type is %{public}d", type);
}

// 绑定自定义手势判定回调
void Manager::SetGestureJudgeBegin(ArkUI_NodeHandle node)
{
    SetMultiGesture(node);
    auto onGestureJudgeBeginCallback = [](ArkUI_GestureInterruptInfo *info)-> ArkUI_GestureInterruptResult {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "onGestureJudgeBeginCallback triggered");
        // 获取自定义手势判定回调中的信息
        auto isSystem = OH_ArkUI_GestureInterruptInfo_GetSystemFlag(info);
        auto event = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(info);
        auto offsetX = OH_ArkUI_PanGesture_GetOffsetX(event);
        auto recognizer = OH_ArkUI_GestureInterruptInfo_GetRecognizer(info);
        auto systemRecognizerType = OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(info);
        auto type = gestureApi->getGestureType(recognizer);
        int fingers = 0;
        OH_ArkUI_GetGestureParam_FingerCount(recognizer, &fingers);
        bool limitFingerCount = false;
        OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, &limitFingerCount);
        char *tag = (char *)malloc(sizeof(char) * NUM_2);
        if (!tag) {
            return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_REJECT;
        }
        tag[0] = '\0';
        int result = 0;
        OH_ArkUI_GetGestureTag(recognizer, tag, NUM_2, &result);
        if (tag[0] == '\0') {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "onGestureJudgeBeginCallback gesture tag is empty");
        }
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
            "onGestureJudgeBeginCallback isSystem %{public}d offsetX %{public}f fingers %{public}d "
            "limitFingerCount %{public}d tag %{public}s systemRecognizerType %{public}d",
            isSystem, offsetX, fingers, limitFingerCount, tag, systemRecognizerType);
        ArkUI_TouchRecognizerHandleArray recognizers;
        int recognizerSize = 0;
        // 获取本次手势响应链中的触摸事件数组
        OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(info, &recognizers, &recognizerSize);
        if (recognizerSize > 0) {
            auto current = recognizers[0];
            auto node = OH_ArkUI_TouchRecognizer_GetNodeHandle(current);
            // 给对应的触摸识别器发送cancel，中断后续事件发送
            OH_ArkUI_TouchRecognizer_CancelTouch(current, info);
        }
        return ProcessDifferentGesture(type, recognizer);
    };
    gestureApi->setGestureInterrupterToNode(node, onGestureJudgeBeginCallback);
    nodeAPI->registerNodeEvent(node, NODE_TOUCH_EVENT, 0, nullptr);
    nodeAPI->addNodeEventReceiver(node, [](ArkUI_NodeEvent *event) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "node touch is called");
    });
}

// 设置移动手势的距离阈值表
void Manager::SetPanGestureWithDistanceMap(ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    auto panGesture = gestureApi->createPanGesture(1, ArkUI_GestureDirection::GESTURE_DIRECTION_ALL, 1);
    int toolTypes[2] = {UI_INPUT_EVENT_TOOL_TYPE_FINGER, UI_INPUT_EVENT_TOOL_TYPE_PEN};
    double distanceArray[2] = {1.0, 5};
    OH_ArkUI_PanGesture_SetDistanceMap(panGesture, NUM_2, toolTypes, distanceArray);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(panGesture, ArkUI_GestureEventActionType::GESTURE_EVENT_ACTION_ACCEPT, nullptr,
        [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "panGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                "column2 panGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(column, panGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
    auto onGestureJudgeBeginCallback = [](ArkUI_GestureInterruptInfo *info) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "onGestureJudgeBeginCallback triggered");
        auto recognizer = OH_ArkUI_GestureInterruptInfo_GetRecognizer(info);
        auto type = OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(info);
        switch (type) {
            case ArkUI_GestureRecognizerType::PAN_GESTURE: {
                ArkUI_GestureDirectionMask direction = ArkUI_GestureDirection::GESTURE_DIRECTION_NONE;
                OH_ArkUI_GetGestureParam_DirectMask(recognizer, &direction);
                double distanceByMap = 0.0;
                // 根据输入设备类型获取移动阈值
                auto errorCode =
                    OH_ArkUI_PanGesture_GetDistanceByToolType(recognizer, UI_INPUT_EVENT_TOOL_TYPE_PEN, &distanceByMap);
                if (errorCode == ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED) {
                    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "not support the recognizer type");
                }
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest",
                    "onGestureJudgeBeginCallback distance %{public}lf", distanceByMap);
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
            }
            default:
                return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
        };
    };
    gestureApi->setGestureInterrupterToNode(column, onGestureJudgeBeginCallback);
}

// 测试手势删除和销毁
void Manager::TestGestureRemove(ArkUI_NodeHandle node)
{
    if (!gestureApi) {
        return;
    }
    auto tapGesture = gestureApi->createTapGesture(1, 1);
    // 给手势绑定回调
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, node, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "gestureTest", "column1 tapGesture is called");
        });
    // 将手势绑定到组件上
    gestureApi->addGestureToNode(node, tapGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
    gestureApi->removeGestureFromNode(node, tapGesture);
    gestureApi->dispose(tapGesture);
}

void CreateSimpleGesture(ArkUI_NodeHandle list)
{
    auto childRow1 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow1);
    auto text1 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text1, "TapGesture");
    auto text2 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text2, "LongPressGesture");
    auto childRow2 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow2);
    auto text3 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text3, "PanGesture");
    auto text4 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text4, "PinchGesture");
    auto childRow3 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow3);
    auto text5 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text5, "RotationGesture");
    auto text6 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text6, "SwipeGesture");
    nodeAPI->addChild(childRow1, text1);
    nodeAPI->addChild(childRow1, text2);
    nodeAPI->addChild(list, childRow1);
    nodeAPI->addChild(childRow2, text3);
    nodeAPI->addChild(childRow2, text4);
    nodeAPI->addChild(list, childRow2);
    nodeAPI->addChild(childRow3, text5);
    nodeAPI->addChild(childRow3, text6);
    nodeAPI->addChild(list, childRow3);
    Manager::SetTapGesture(text1);
    Manager::SetLongPressGesture(text2);
    Manager::SetPanGestureWithDirection(text3, ArkUI_GestureDirection::GESTURE_DIRECTION_ALL);
    Manager::SetPinchGesture(text4);
    Manager::SetRotationGesture(text5);
    Manager::SetSwipeGesture(text6);
}

void CreateDifferentDirectionPanGesture(ArkUI_NodeHandle list)
{
    auto childRow4 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow4);
    auto text7 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text7, "TapGestureWithDistance");
    auto text8 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text8, "Pan-Horizontal");
    auto childRow5 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow5);
    auto text9 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text9, "Pan-Vertical");
    auto text10 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text10, "Pan-Left");
    auto childRow6 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow6);
    auto text11 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text11, "Pan-Right");
    auto text12 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text12, "Pan-Up");
    auto childRow7 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow7);
    auto text13 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text13, "Pan-Down");
    auto text14 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text14, "Pan-None");
    nodeAPI->addChild(childRow4, text7);
    nodeAPI->addChild(childRow4, text8);
    nodeAPI->addChild(list, childRow4);
    nodeAPI->addChild(childRow5, text9);
    nodeAPI->addChild(childRow5, text10);
    nodeAPI->addChild(list, childRow5);
    nodeAPI->addChild(childRow6, text11);
    nodeAPI->addChild(childRow6, text12);
    nodeAPI->addChild(list, childRow6);
    nodeAPI->addChild(childRow7, text13);
    nodeAPI->addChild(childRow7, text14);
    nodeAPI->addChild(list, childRow7);
    Manager::SetTapGestureWithDistance(text7);
    // 设置不同方向的移动手势
    Manager::SetPanGestureWithDirection(text8, ArkUI_GestureDirection::GESTURE_DIRECTION_HORIZONTAL);
    Manager::SetPanGestureWithDirection(text9, ArkUI_GestureDirection::GESTURE_DIRECTION_VERTICAL);
    Manager::SetPanGestureWithDirection(text10, ArkUI_GestureDirection::GESTURE_DIRECTION_LEFT);
    Manager::SetPanGestureWithDirection(text11, ArkUI_GestureDirection::GESTURE_DIRECTION_RIGHT);
    Manager::SetPanGestureWithDirection(text12, ArkUI_GestureDirection::GESTURE_DIRECTION_UP);
    Manager::SetPanGestureWithDirection(text13, ArkUI_GestureDirection::GESTURE_DIRECTION_DOWN);
    Manager::SetPanGestureWithDirection(text14, ArkUI_GestureDirection::GESTURE_DIRECTION_NONE);
}

void CreateGestureGroupByMode(ArkUI_NodeHandle list)
{
    auto childRow8 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow8);
    auto text15 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text15, "Group-Sequence");
    auto text16 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text16, "Group-Exclusive");
    auto childRow9 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow9);
    auto text17 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text17, "Group-Parallel");
    auto text18 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text18, "NORMAL_GESTURE_MASK");
    auto childRow10 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow10);
    auto text19 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text19, "IGNORE_INTERNAL_GESTURE_MASK");
    auto text20 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text20, "Priority-Normal");
    auto childRow11 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow11);
    auto text21 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text21, "Priority-Parallel");
    auto text22 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text22, "Priority-Priority");
    nodeAPI->addChild(childRow8, text15);
    nodeAPI->addChild(childRow8, text16);
    nodeAPI->addChild(list, childRow8);
    nodeAPI->addChild(childRow9, text17);
    nodeAPI->addChild(childRow9, text18);
    nodeAPI->addChild(list, childRow9);
    nodeAPI->addChild(childRow10, text19);
    nodeAPI->addChild(childRow10, text20);
    nodeAPI->addChild(list, childRow10);
    nodeAPI->addChild(childRow11, text21);
    nodeAPI->addChild(childRow11, text22);
    nodeAPI->addChild(list, childRow11);
    // 绑定顺序手势组
    Manager::CreateGestureGroup(text15, ArkUI_GroupGestureMode::SEQUENTIAL_GROUP);
    // 绑定互斥手势组
    Manager::CreateGestureGroup(text16, ArkUI_GroupGestureMode::EXCLUSIVE_GROUP);
    // 绑定并行手势组
    Manager::CreateGestureGroup(text17, ArkUI_GroupGestureMode::PARALLEL_GROUP);
    // 设置普通响应的手势
    Manager::CreateGestureWithMask(text18, ArkUI_GestureMask::NORMAL_GESTURE_MASK);
    // 设置忽略子组件响应的手势
    Manager::CreateGestureWithMask(text19, ArkUI_GestureMask::IGNORE_INTERNAL_GESTURE_MASK);
    // 绑定普通优先级的手势
    Manager::CreateGestureWithPriority(text20, ArkUI_GesturePriority::NORMAL);
    // 绑定并行优先级的手势
    Manager::CreateGestureWithPriority(text21, ArkUI_GesturePriority::PARALLEL);
    // 绑定高优先级的手势
    Manager::CreateGestureWithPriority(text22, ArkUI_GesturePriority::PRIORITY);
}

// 给每个Text绑定对应的手势和回调，通过日志观测行为
void BindingGesture(napi_env env, napi_value arg, OH_NativeXComponent *component)
{
    float columnWidth = 300;
    float columnHeight = 800;
    unsigned int columnColor = 0xFEF5F5F5;
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetColumnAttribute(column, columnWidth, columnHeight, columnColor);
    auto textShow2 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    Manager::CreateNode(textShow2);
    nodeAPI->addChild(column, textShow2);
    auto buttonClear = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    Manager::SetClearButtonAttribute(buttonClear);
    nodeAPI->addChild(column, buttonClear);
    auto list = nodeAPI->createNode(ARKUI_NODE_LIST);
    columnHeight = COLUMN_SIZE;
    SetColumnAttribute(list, columnWidth, columnHeight, columnColor);
    nodeAPI->addChild(column, list);
    CreateSimpleGesture(list);
    CreateDifferentDirectionPanGesture(list);
    CreateGestureGroupByMode(list);
    auto childRow12 = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetRowAttribute(childRow12);
    auto text23 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text23, "JudgeBeginTest");
    auto text24 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text24, "PanGestureWithDistanceMap");
    auto text25 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text25, "TestGestureRemove");
    nodeAPI->addChild(childRow12, text23);
    nodeAPI->addChild(childRow12, text24);
    nodeAPI->addChild(list, childRow12);
    nodeAPI->addChild(list, text25);
    OH_NativeXComponent_AttachNativeRootNode(component, column);
    Manager::SetGestureJudgeBegin(text23);
    Manager::SetPanGestureWithDistanceMap(text24);
    Manager::TestGestureRemove(text25);
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }

    if (argCnt < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_GESTURE, ArkUI_NativeGestureAPI_1, gestureApi);

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            BindingGesture(env, args[1], component);
        }
    }
    return nullptr;
}

napi_value Manager::UpdateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode env or info is null");
        return nullptr;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "UpdateNativeNode  1111");

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "CreateNativeNode %{public}s", idStr);

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }

    if ((env == nullptr) || (info == nullptr || component == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }
    return nullptr;
}

napi_value Manager::GetContext(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    int64_t value;
    if (napi_get_value_int64(env, args[0], &value) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }

    return exports;
}

void Manager::Export(napi_env env, napi_value exports)
{
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: env or exports is null");
        return;
    }

    napi_value exportInstance = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_get_named_property fail");
        return;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_unwrap fail");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager",
                     "Export: OH_NativeXComponent_GetXComponentId fail");
        return;
    }

    std::string id(idStr);
    auto manager = Manager::GetInstance();
    if ((manager != nullptr) && (nativeXComponent != nullptr)) {
        manager->SetNativeXComponent(id, nativeXComponent);
    }
}

void Manager::SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }

    if (nativeXComponentMap_.find(id) == nativeXComponentMap_.end()) {
        nativeXComponentMap_[id] = nativeXComponent;
        return;
    }

    if (nativeXComponentMap_[id] != nativeXComponent) {
        OH_NativeXComponent *tmp = nativeXComponentMap_[id];
        tmp = nullptr;
        nativeXComponentMap_[id] = nativeXComponent;
    }
}

OH_NativeXComponent *Manager::GetNativeXComponent(const std::string &id) { return nativeXComponentMap_[id]; }
} // namespace NativeXComponentSample