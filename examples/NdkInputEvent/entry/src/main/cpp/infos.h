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

#ifndef NDKINPUTEVENT_INFOS_H
#define NDKINPUTEVENT_INFOS_H

#include "common.h"
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <sstream>
#include <hilog/log.h>

#define DEFAULT_WIDTH 200.0
#define DEFAULT_HEIGHT 200.0
#define DEFAULT_BG_COLOR 0xFFFFFFFF
#define DEFAULT_BORDER_WIDTH 0.0
#define BORDER_WIDTH_1 1.0
#define DEFAULT_MARGIN 5.0
#define DEFAULT_BORDER_COLOR 0xFF000000
#define DEFAULT_RADIUS 10.0

#define SIZE_100 100
#define SIZE_300 300
#define BLANK_10 10.0

#define DEFAULT_TEXT_FONT_SIZE 12
#define TEXT_FONT_SIZE_15 15
#define TEXT_FONT_SIZE_20 20

#define BUTTON_LENGTH 10
#define MAX_LENGTH 128

namespace NativeXComponentSample {

// 示例说明文本
std::string g_explain = "通过本示例可以测试输入事件C-API的各项功能。\n"
    "1、测试按钮1：通过手指点击该按钮可测试触摸事件；\n"
    "      在触摸事件中通过克隆事件分发到背景，验证克隆事件相关接口的能力；\n"
    "      通过鼠标移动、点击可以测试鼠标事件和鼠标悬停事件。\n"
    "2、测试按钮2：通过鼠标滚轮或触控屏可以测试轴事件；\n"
    "      通过手写笔工具获取触控事件中的操作角度；\n"
    "      通过本按钮可以验证事件冒泡的接口的相关能力。\n"
    "3、测试框：点击测试框验证触摸测试接口的能力，点击按钮可切换模式。\n"
    "4、连接键盘可以测试按键事件，但需要首先按Tab键使界面获焦，之后可以通过日志观察按键事件的相关信息。";

// ArkUI修饰键枚举
enum ArkUIModifierKeyName {
    ARKUI_MODIFIER_KEY_CTRL = 1 << 0,  // Ctrl 键
    ARKUI_MODIFIER_KEY_SHIFT = 1 << 1, // Shift 键
    ARKUI_MODIFIER_KEY_ALT = 1 << 2,   // Alt 键
    ARKUI_MODIFIER_KEY_FN = 1 << 3     // Fn 键（如适用）
};
// 触摸测试模式名称数组
std::string g_hitTestNames[] = { "Default", "Block", "Transparent", "None", "Hierarchy", "Descendants" };
// 触摸测试模式值数组
int32_t g_hitTestModes[] = { HTM_DEFAULT, HTM_BLOCK, HTM_TRANSPARENT, HTM_NONE, HTM_BLOCK_HIERARCHY,
    HTM_BLOCK_DESCENDANTS };
// 当前触摸测试模式索引
int g_hitIdx = 0;
// 鼠标按钮名称数组
std::string g_mouseButtonNames[] = { "MOUSE_BUTTON_NONE", "MOUSE_BUTTON_LEFT", "MOUSE_BUTTON_RIGHT",
    "MOUSE_BUTTON_MIDDLE", "MOUSE_BUTTON_BACK", "MOUSE_BUTTON_FORWARD" };

// 全局字符串流，用于格式化输出
std::stringstream g_ss;

// 主列容器
ArkUI_NodeHandle column1;
// 信息文本节点
ArkUI_NodeHandle infoText = nullptr;
// 标题文本节点
ArkUI_NodeHandle titleText = nullptr;
// 按钮3节点
ArkUI_NodeHandle button3 = nullptr;

// 打印多点触控历史信息
void PrintMultiHistoryInfos(ArkUI_UIInputEvent* inputEvent, uint32_t pointerIndex)
{
    auto size = OH_ArkUI_PointerEvent_GetHistorySize(inputEvent);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
        "%{public}d: historySize = %{public}d", pointerIndex, size);
    for (int historyIndex = 0; historyIndex < size; historyIndex++) {
        auto time = OH_ArkUI_PointerEvent_GetHistoryEventTime(inputEvent, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyEventTime = %{public}ld", time);
        auto pointerCount = OH_ArkUI_PointerEvent_GetHistoryPointerCount(inputEvent, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyPointerCount = %{public}d", pointerCount);
        auto pointerId = OH_ArkUI_PointerEvent_GetHistoryPointerId(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyPointerId = %{public}d", pointerId);
        auto historyX = OH_ArkUI_PointerEvent_GetHistoryX(inputEvent, pointerIndex, historyIndex);
        auto historyY = OH_ArkUI_PointerEvent_GetHistoryY(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyX/Y = %{public}f/%{public}f", historyX, historyY);
        auto historyWindowX = OH_ArkUI_PointerEvent_GetHistoryWindowX(inputEvent, pointerIndex, historyIndex);
        auto historyWindowY = OH_ArkUI_PointerEvent_GetHistoryWindowY(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyWindowX/Y = %{public}f/%{public}f", historyWindowX, historyWindowY);
        auto historyDisplayX = OH_ArkUI_PointerEvent_GetHistoryDisplayX(inputEvent, pointerIndex, historyIndex);
        auto historyDisplayY = OH_ArkUI_PointerEvent_GetHistoryDisplayY(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyDisplayX/Y = %{public}f/%{public}f", historyDisplayX, historyDisplayY);
        auto historyGlobalDisplayX = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(inputEvent,
            pointerIndex, historyIndex);
        auto historyGlobalDisplayY = OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(inputEvent,
            pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyGlobalDisplayX/Y = %{public}f/%{public}f", historyGlobalDisplayX, historyGlobalDisplayY);
        auto historyPressure = OH_ArkUI_PointerEvent_GetHistoryPressure(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyPressure = %{public}f", historyPressure);
        auto historyTouchAreaWidth = OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(inputEvent,
            pointerIndex, historyIndex);
        auto historyTouchAreaHeight = OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(inputEvent,
            pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyTouchAreaWidth/Height = %{public}f/%{public}f", historyTouchAreaWidth, historyTouchAreaHeight);
    }
}

// 显示多点触控信息
void ShowMultiInfos(ArkUI_UIInputEvent* inputEvent)
{
    g_ss.str("");
    uint32_t pointerIndex = 0;
    OH_ArkUI_PointerEvent_GetChangedPointerId(inputEvent, &pointerIndex);
    g_ss << "pointerIndex: " << pointerIndex << std::endl;
    auto id = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, pointerIndex);
    g_ss << "pointerId: " << id << std::endl;
    auto pressedTime = OH_ArkUI_PointerEvent_GetPressedTimeByIndex(inputEvent, pointerIndex);
    g_ss << "pressedTime: " << pressedTime << std::endl;
    auto x = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, pointerIndex);
    auto y = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, pointerIndex);
    g_ss << "x/y: " << x << "/" << y << std::endl;
    auto windowX = OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, pointerIndex);
    auto windowY = OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, pointerIndex);
    g_ss << "windowX/Y: " << windowX << "/" << windowY << std::endl;
    auto displayX = OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, pointerIndex);
    auto displayY = OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, pointerIndex);
    g_ss << "displayX/Y: " << displayX << "/" << displayY << std::endl;
    auto globalDisplayX = OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(inputEvent, pointerIndex);
    auto globalDisplayY = OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(inputEvent, pointerIndex);
    g_ss << "globalDisplayX/Y: " << globalDisplayX << "/" << globalDisplayY << std::endl;
    auto pressure = OH_ArkUI_PointerEvent_GetPressure(inputEvent, pointerIndex);
    g_ss << "pressure: " << pressure << std::endl;
    ArkUI_InteractionHand hand;
    OH_ArkUI_PointerEvent_GetInteractionHandByIndex(inputEvent, pointerIndex, &hand);
    if (hand == ARKUI_EVENT_HAND_LEFT) {
        g_ss << "hand: LEFT" << std::endl;
    } else if (hand == ARKUI_EVENT_HAND_RIGHT) {
        g_ss << "hand: RIGHT" << std::endl;
    } else if (hand == ARKUI_EVENT_HAND_NONE) {
        g_ss << "hand: NONE" << std::endl;
    }
    auto touchAreaWidth = OH_ArkUI_PointerEvent_GetTouchAreaWidth(inputEvent, pointerIndex);
    auto touchAreaHeight = OH_ArkUI_PointerEvent_GetTouchAreaHeight(inputEvent, pointerIndex);
    g_ss << "touchAreaWidth/Height: " << touchAreaWidth << "/" << touchAreaHeight << std::endl;
    SetText(infoText, g_ss.str().c_str(), TEXT_FONT_SIZE_15);
    PrintMultiHistoryInfos(inputEvent, pointerIndex);
}

// 显示简单位置信息
void ShowSimplePosInfo(ArkUI_UIInputEvent *inputEvent)
{
    auto x = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y = OH_ArkUI_PointerEvent_GetY(inputEvent);
    g_ss << "x/y: " << x << "/" << y << std::endl;
    auto windowX = OH_ArkUI_PointerEvent_GetWindowX(inputEvent);
    auto windowY = OH_ArkUI_PointerEvent_GetWindowY(inputEvent);
    g_ss << "windowX/Y: " << windowX << "/" << windowY << std::endl;
    auto displayX = OH_ArkUI_PointerEvent_GetDisplayX(inputEvent);
    auto displayY = OH_ArkUI_PointerEvent_GetDisplayY(inputEvent);
    g_ss << "displayX/Y: " << displayX << "/" << displayY << std::endl;
    auto globalDisplayX = OH_ArkUI_PointerEvent_GetGlobalDisplayX(inputEvent);
    auto globalDisplayY = OH_ArkUI_PointerEvent_GetGlobalDisplayY(inputEvent);
    g_ss << "globalDisplayX/Y: " << globalDisplayX << "/" << globalDisplayY << std::endl;
}

// 显示简单目标信息
void ShowSimpleTarInfo(ArkUI_UIInputEvent *inputEvent)
{
    auto targetWidth = OH_ArkUI_UIInputEvent_GetEventTargetWidth(inputEvent);
    g_ss << "targetWidth: " << targetWidth << std::endl;
    auto targetHeight = OH_ArkUI_UIInputEvent_GetEventTargetHeight(inputEvent);
    g_ss << "targetHeight: " << targetHeight << std::endl;
    auto positionX = OH_ArkUI_UIInputEvent_GetEventTargetPositionX(inputEvent);
    auto positionY = OH_ArkUI_UIInputEvent_GetEventTargetPositionY(inputEvent);
    g_ss << "targetPositionX/Y: " << positionX << "/" << positionY << std::endl;
    auto globalPositionX = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(inputEvent);
    auto globalPositionY = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(inputEvent);
    g_ss << "targetGlobalPositionX/Y: " << globalPositionX << "/" << globalPositionY << std::endl;
}

// 显示简单事件信息
void ShowSimpleInfo(ArkUI_UIInputEvent* inputEvent)
{
    g_ss.str("");
    auto displayId = OH_ArkUI_UIInputEvent_GetTargetDisplayId(inputEvent);
    g_ss << "displayId: " << displayId << std::endl;
    auto eventTime = OH_ArkUI_UIInputEvent_GetEventTime(inputEvent);
    g_ss << "eventTime: " << eventTime << std::endl;
    // 触摸事件位置信息
    ShowSimplePosInfo(inputEvent);
    // 手指触摸事件显示信息
    auto type = OH_ArkUI_UIInputEvent_GetToolType(inputEvent);
    if (type == UI_INPUT_EVENT_TOOL_TYPE_FINGER) {
        ArkUI_InteractionHand hand;
        OH_ArkUI_PointerEvent_GetInteractionHand(inputEvent, &hand);
        if (hand == ARKUI_EVENT_HAND_LEFT) {
            g_ss << "hand: LEFT" << std::endl;
        } else if (hand == ARKUI_EVENT_HAND_RIGHT) {
            g_ss << "hand: RIGHT" << std::endl;
        } else {
            g_ss << "hand: NONE" << std::endl;
        }
    } else if (type == UI_INPUT_EVENT_TOOL_TYPE_PEN) {
        double rollAngle = 0;
        OH_ArkUI_PointerEvent_GetRollAngle(inputEvent, &rollAngle);
        g_ss << "rollAngle: " << rollAngle << std::endl;
    }
    // 命中组件信息
    ShowSimpleTarInfo(inputEvent);
    SetText(infoText, g_ss.str().c_str(), TEXT_FONT_SIZE_15);
}

// 打印克隆事件信息
void PrintClonedEventInfos(ArkUI_UIInputEvent* inputEvent, ArkUI_UIInputEvent* clonedEvent)
{
    float x = 0;
    float y = 0;
    OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(clonedEvent, x, y);
    OH_ArkUI_PointerEvent_SetClonedEventActionType(clonedEvent, UI_TOUCH_EVENT_ACTION_DOWN);
    OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(clonedEvent, 0);
    if (OH_ArkUI_UIInputEvent_GetLatestStatus() == ARKUI_ERROR_CODE_NO_ERROR) {
        // 此前接口调用无误，执行克隆事件分发
        int ret = OH_ArkUI_PointerEvent_PostClonedEvent(column1, clonedEvent);
        if (ret == ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "inputTest",
                         "The event is not cloned event!");
        } else if (ret == ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "inputTest",
                         "The component status abnormal!");
        } else if (ret == ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "inputTest",
                         "No component hit to respond to the event!");
        }
    }
}

// 打印多点克隆事件信息
void PrintMultiClonedEventInfos(ArkUI_UIInputEvent* clonedEvent)
{
    float x = 0;
    float y = 0;
    OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(clonedEvent, x, y, 0);
    OH_ArkUI_PointerEvent_SetClonedEventActionType(clonedEvent, UI_TOUCH_EVENT_ACTION_DOWN);
    OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(clonedEvent, 0, 0);
    if (OH_ArkUI_UIInputEvent_GetLatestStatus() == ARKUI_ERROR_CODE_NO_ERROR) {
        // 此前接口调用无误，执行克隆事件分发
        OH_ArkUI_PointerEvent_PostClonedEvent(column1, clonedEvent);
    }
}

// 显示倾斜角度信息
void ShowTiltInfos(ArkUI_UIInputEvent* inputEvent)
{
    g_ss.str("");
    uint32_t pointerIndex = 0;
    OH_ArkUI_PointerEvent_GetChangedPointerId(inputEvent, &pointerIndex);
    g_ss << "pointerIndex: " << pointerIndex << std::endl;
    auto id = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, pointerIndex);
    g_ss << "pointerId: " << id << std::endl;
    auto tiltX = OH_ArkUI_PointerEvent_GetTiltX(inputEvent, pointerIndex);
    auto tiltY = OH_ArkUI_PointerEvent_GetTiltY(inputEvent, pointerIndex);
    g_ss << "tiltX/Y: " << tiltX << "/" << tiltY << std::endl;
    SetText(infoText, g_ss.str().c_str(), TEXT_FONT_SIZE_15);
    // 日志输出原始Tilt信息
    auto size = OH_ArkUI_PointerEvent_GetHistorySize(inputEvent);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
        "%{public}d: historySize = %{public}d", pointerIndex, size);
    for (int historyIndex = 0; historyIndex < size; historyIndex++) {
        auto pointerCount = OH_ArkUI_PointerEvent_GetHistoryPointerCount(inputEvent, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyPointerCount = %{public}d", pointerCount);
        auto pointerId = OH_ArkUI_PointerEvent_GetHistoryPointerId(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyPointerId = %{public}d", pointerId);
        auto historyTiltX = OH_ArkUI_PointerEvent_GetHistoryTiltX(inputEvent, pointerIndex, historyIndex);
        auto historyTiltY = OH_ArkUI_PointerEvent_GetHistoryTiltY(inputEvent, pointerIndex, historyIndex);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "historyTiltX/Y = %{public}f/%{public}f", historyTiltX, historyTiltY);
    }
}

// 显示轴事件信息
void ShowAxisInfos(ArkUI_UIInputEvent* inputEvent)
{
    g_ss.str("");
    auto toolType = OH_ArkUI_UIInputEvent_GetToolType(inputEvent);
    switch (toolType) {
        case UI_INPUT_EVENT_TOOL_TYPE_MOUSE: {
            auto scrollStep = OH_ArkUI_AxisEvent_GetScrollStep(inputEvent);
            g_ss << "scrollStep: " << scrollStep << std::endl;
            auto verticalAxisValue = OH_ArkUI_AxisEvent_GetVerticalAxisValue(inputEvent);
            g_ss << "verticalAxisValue: " << verticalAxisValue << std::endl;
            break;
        }
        case UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD: {
            auto verticalAxisValue = OH_ArkUI_AxisEvent_GetVerticalAxisValue(inputEvent);
            g_ss << "verticalAxisValue: " << verticalAxisValue << std::endl;
            auto horizontalAxisValue = OH_ArkUI_AxisEvent_GetHorizontalAxisValue(inputEvent);
            g_ss << "horizontalAxisValue: " << horizontalAxisValue << std::endl;
            auto pinchAxisScaleValue = OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(inputEvent);
            g_ss << "pinchAxisScaleValue: " << pinchAxisScaleValue << std::endl;
            break;
        }
        default: {
            break;
        }
    }
    SetText(infoText, g_ss.str().c_str(), TEXT_FONT_SIZE_20);
}

// 触控屏事件操作处理函数
void TouchScreenEventOperator(ArkUI_UIInputEvent* inputEvent, ArkUI_NodeHandle* button)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_UIINPUTEVENT_TYPE_TOUCH EventReceiver");
    auto count = OH_ArkUI_PointerEvent_GetPointerCount(inputEvent);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "pointerCount = %{public}d", count);
    OH_ArkUI_PointerEvent_SetStopPropagation(inputEvent, true);
    ArkUI_UIInputEvent* clonedEvent = nullptr;
    OH_ArkUI_PointerEvent_CreateClonedEvent(inputEvent, &clonedEvent);
    switch (OH_ArkUI_UIInputEvent_GetAction(inputEvent)) {
        case UI_TOUCH_EVENT_ACTION_DOWN: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_DOWN EventReceiver");
            SetText(titleText, "");
            if (count == 1) {
                SetBackgroundColor(*button, 0xFFFF0000);
                PrintClonedEventInfos(inputEvent, clonedEvent);
            } else if (count > 1) {
                SetBackgroundColor(*button, 0xFF932F60);
                PrintMultiClonedEventInfos(clonedEvent);
            }
            break;
        }
        case UI_TOUCH_EVENT_ACTION_MOVE: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_MOVE EventReceiver");
            if (count == 1) {
                ShowSimpleInfo(inputEvent);
            } else if (count > 1) {
                ShowMultiInfos(inputEvent);
            }
            break;
        }
        case UI_TOUCH_EVENT_ACTION_UP: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_UP EventReceiver");
            SetBackgroundColor(*button, 0xFF0000FF);
            SetBackgroundColor(column1, 0xFFF6F6F6);
            OH_ArkUI_PointerEvent_DestroyClonedEvent(clonedEvent);
            break;
        }
        case UI_TOUCH_EVENT_ACTION_CANCEL: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "UI_TOUCH_EVENT_ACTION_CANCEL EventReceiver");
            break;
        }
        default: {
            break;
        }
    }
}

} // namespace NativeXComponentSample

#endif //NDKINPUTEVENT_INFOS_H
