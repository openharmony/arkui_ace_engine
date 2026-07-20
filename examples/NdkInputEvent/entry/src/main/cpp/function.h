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

#ifndef NDKINPUTEVENT_FUNCTION_H
#define NDKINPUTEVENT_FUNCTION_H

#include "infos.h"
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <hilog/log.h>

namespace NativeXComponentSample {

// 触摸事件操作处理函数
void TouchEventOperator(ArkUI_UIInputEvent* inputEvent, ArkUI_NodeHandle* button)
{
    auto sourceType = OH_ArkUI_UIInputEvent_GetSourceType(inputEvent);
    switch (sourceType) {
        case UI_INPUT_EVENT_SOURCE_TYPE_TOUCH_SCREEN: {
            TouchScreenEventOperator(inputEvent, button);
            break;
        }
        case UI_INPUT_EVENT_SOURCE_TYPE_MOUSE:
        case UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN:
        default: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "TouchEvent is only dispatched in touchscreen scenarios!");
            break;
        }
    }
}

// 鼠标事件操作处理函数
void MouseEventOperator(ArkUI_UIInputEvent* inputEvent, ArkUI_NodeHandle *button)
{
    if (OH_ArkUI_UIInputEvent_GetToolType(inputEvent) == UI_INPUT_EVENT_TOOL_TYPE_MOUSE) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "ARKUI_UIINPUTEVENT_TYPE_MOUSE EventReceiver");
        auto action = OH_ArkUI_MouseEvent_GetMouseAction(inputEvent);
        auto mouseButton = OH_ArkUI_MouseEvent_GetMouseButton(inputEvent);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "MOUSE BUTTON %{public}d", mouseButton);
        if (action == UI_MOUSE_EVENT_ACTION_PRESS && mouseButton == UI_MOUSE_EVENT_BUTTON_MIDDLE) {
            return;
        }
        switch (action) {
            case UI_MOUSE_EVENT_ACTION_PRESS: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_MOUSE_EVENT_ACTION_PRESS EventReceiver");
                SetBackgroundColor(*button, 0xFFFF0000);
                break;
            }
            case UI_MOUSE_EVENT_ACTION_MOVE: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_MOUSE_EVENT_ACTION_MOVE EventReceiver");
                g_ss.str("");
                auto rawDeltaX = OH_ArkUI_MouseEvent_GetRawDeltaX(inputEvent);
                auto rawDeltaY = OH_ArkUI_MouseEvent_GetRawDeltaY(inputEvent);
                g_ss << "rawDeltaX: " << rawDeltaX << std::endl << "rawDeltaY: " << rawDeltaY << std::endl;
                SetText(infoText, g_ss.str().c_str(), TEXT_FONT_SIZE_20);
                break;
            }
            case UI_MOUSE_EVENT_ACTION_RELEASE: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_MOUSE_EVENT_ACTION_RELEASE EventReceiver");
                SetBackgroundColor(*button, 0xFF0000FF);
                SetBackgroundColor(column1, 0xFFF6F6F6);
                break;
            }
            case UI_MOUSE_EVENT_ACTION_CANCEL: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_MOUSE_EVENT_ACTION_CANCEL EventReceiver");
                break;
            }
            case UI_MOUSE_EVENT_ACTION_UNKNOWN: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_MOUSE_EVENT_ACTION_UNKNOWN EventReceiver");
                break;
            }
            default: {
                break;
            }
        }
    }
}

// 键盘事件操作处理函数
void KeyEventOperator(ArkUI_UIInputEvent* inputEvent)
{
    SetText(titleText, "");
    SetText(infoText, "");
    auto type = OH_ArkUI_KeyEvent_GetType(inputEvent);
    switch (type) {
        case ARKUI_KEY_EVENT_DOWN: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_KEY_EVENT_DOWN EventReceiver");
            int32_t pressedKeyCodes[BUTTON_LENGTH] = {};
            int32_t length = BUTTON_LENGTH;
            OH_ArkUI_UIInputEvent_GetPressedKeys(inputEvent, pressedKeyCodes, &length);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "pressedKeyCodes = %{public}d", pressedKeyCodes[0]);
            auto deviceId = OH_ArkUI_UIInputEvent_GetDeviceId(inputEvent);
            uint64_t keys = 0;
            OH_ArkUI_UIInputEvent_GetModifierKeyStates(inputEvent, &keys);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "deviceId = %{public}d, keys = %{public}lu", deviceId, keys);
            break;
        }
        case ARKUI_KEY_EVENT_UP: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_KEY_EVENT_UP EventReceiver");
            break;
        }
        case ARKUI_KEY_EVENT_LONG_PRESS: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_KEY_EVENT_LONG_PRESS EventReceiver");
            break;
        }
        case ARKUI_KEY_EVENT_CLICK: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_KEY_EVENT_CLICK EventReceiver");
            break;
        }
        case ARKUI_KEY_EVENT_UNKNOWN:
        default: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_KEY_EVENT_UNKNOWN EventReceiver");
            break;
        }
    }
}

// 按钮1事件接收器，注册触摸、鼠标、悬停和键盘事件
void Bt1EventReceiver(ArkUI_NodeHandle& button)
{
    nodeAPI->registerNodeEvent(button, NODE_TOUCH_EVENT, 1, &button);
    nodeAPI->registerNodeEvent(button, NODE_ON_MOUSE, 1, &button);
    nodeAPI->registerNodeEvent(button, NODE_ON_HOVER_EVENT, 1, &button);
    nodeAPI->registerNodeEvent(button, NODE_ON_KEY_EVENT, 1, &button);
    nodeAPI->addNodeEventReceiver(button, [](ArkUI_NodeEvent *event) {
        auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
        auto eventType = OH_ArkUI_UIInputEvent_GetType(inputEvent);
        ArkUI_NodeHandle *button = (ArkUI_NodeHandle *)OH_ArkUI_NodeEvent_GetUserData(event);
        if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_ON_HOVER_EVENT) {
            auto isHovered = OH_ArkUI_HoverEvent_IsHovered(inputEvent);
            if (isHovered) {
                SetBackgroundColor(*button, 0xFF009F40);
            } else {
                SetBackgroundColor(*button, 0xFF0000FF);
            }
        } else if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_ON_FOCUS_AXIS) {
            OH_ArkUI_FocusAxisEvent_SetStopPropagation(inputEvent, true);
            auto abs_x = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_X);
            auto abs_y = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Y);
            auto abs_z = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Z);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "abs_x/abs_y/abs_z = %{public}f/%{public}f/%{public}f", abs_x, abs_y, abs_z);
        }
        if (eventType == ARKUI_UIINPUTEVENT_TYPE_TOUCH) {
            TouchEventOperator(inputEvent, button);
        } else if (eventType == ARKUI_UIINPUTEVENT_TYPE_MOUSE) {
            auto action = OH_ArkUI_MouseEvent_GetMouseAction(inputEvent);
            // 鼠标按键数
            int32_t pressedButtons[BUTTON_LENGTH] = {};
            int32_t length;
            OH_ArkUI_MouseEvent_GetPressedButtons(inputEvent, pressedButtons, &length);
            g_ss.str("");
            g_ss << "pressedButtonCount: " << length << std::endl << "pressedButtons:" << std::endl;
            for (int i = 0; i < length; i++) {
                g_ss << g_mouseButtonNames[pressedButtons[i]] << std::endl;
            }
            SetText(titleText, g_ss.str().c_str(), TEXT_FONT_SIZE_20);
            MouseEventOperator(inputEvent, button);
        } else if (eventType == ARKUI_UIINPUTEVENT_TYPE_KEY) {
            KeyEventOperator(inputEvent);
        } else if (eventType == ARKUI_UIINPUTEVENT_TYPE_UNKNOWN) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "UNKNOWN UIINPUTEVENT!");
        }
    });
}

// 扩展触摸事件操作处理函数
void ExtraTouchEventOperator(ArkUI_UIInputEvent* inputEvent, ArkUI_NodeHandle* button)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "ARKUI_UIINPUTEVENT_TYPE_TOUCH EventReceiver");
    OH_ArkUI_PointerEvent_SetStopPropagation(inputEvent, true);
    SetText(titleText, "");
    SetText(infoText, "");
    auto type = OH_ArkUI_UIInputEvent_GetToolType(inputEvent);
    auto count = OH_ArkUI_PointerEvent_GetPointerCount(inputEvent);
    switch (OH_ArkUI_UIInputEvent_GetAction(inputEvent)) {
        case UI_TOUCH_EVENT_ACTION_DOWN: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_DOWN EventReceiver");
            SetBackgroundColor(*button, 0xFFFF0000);
            break;
        }
        case UI_TOUCH_EVENT_ACTION_MOVE: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_MOVE EventReceiver");
            if (type == UI_INPUT_EVENT_TOOL_TYPE_PEN) {
                ShowTiltInfos(inputEvent);
            }
            break;
        }
        case UI_TOUCH_EVENT_ACTION_UP: {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "UI_TOUCH_EVENT_ACTION_UP EventReceiver");
            SetBackgroundColor(*button, 0xFF0000FF);
            SetBackgroundColor(column1, 0xFFFFFFFF);
            break;
        }
        default: {
            break;
        }
    }
}

// 轴事件操作处理函数
void AxisEventOperator(ArkUI_UIInputEvent* inputEvent)
{
    SetText(titleText, "");
    auto toolType = OH_ArkUI_UIInputEvent_GetToolType(inputEvent);
    if (toolType == UI_INPUT_EVENT_TOOL_TYPE_MOUSE) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
            "ARKUI_UIINPUTEVENT_TYPE_AXIS EventReceiver");
        OH_ArkUI_AxisEvent_SetPropagation(inputEvent, false);
        auto action = OH_ArkUI_AxisEvent_GetAxisAction(inputEvent);
        switch (action) {
            case UI_AXIS_EVENT_ACTION_BEGIN: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_BEGIN EventReceiver");
                break;
            }
            case UI_AXIS_EVENT_ACTION_UPDATE: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_UPDATE EventReceiver");
                ShowAxisInfos(inputEvent);
                break;
            }
            case UI_AXIS_EVENT_ACTION_END: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_END EventReceiver");
                SetBackgroundColor(column1, 0xFFF6F6F6);
                break;
            }
            case UI_AXIS_EVENT_ACTION_CANCEL: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_CANCEL EventReceiver");
                break;
            }
            case UI_AXIS_EVENT_ACTION_NONE: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_NONE EventReceiver");
                break;
            }
            default: {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                    "UI_AXIS_EVENT_ACTION_UNKNOWN EventReceiver");
                break;
            }
        }
    }
}

// 按钮2事件接收器，注册触摸、轴和焦点轴事件
void Bt2EventReceiver(ArkUI_NodeHandle& button)
{
    nodeAPI->registerNodeEvent(button, NODE_TOUCH_EVENT, 1, &button);
    nodeAPI->registerNodeEvent(button, NODE_ON_AXIS, 1, &button);
    nodeAPI->registerNodeEvent(button, NODE_ON_FOCUS_AXIS, 1, &button);
    nodeAPI->addNodeEventReceiver(button, [](ArkUI_NodeEvent *event) {
        auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
        auto eventType = OH_ArkUI_UIInputEvent_GetType(inputEvent);
        ArkUI_NodeHandle *button = (ArkUI_NodeHandle *)OH_ArkUI_NodeEvent_GetUserData(event);
        if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_ON_FOCUS_AXIS) {
            OH_ArkUI_FocusAxisEvent_SetStopPropagation(inputEvent, true);
            auto abs_x = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_X);
            auto abs_y = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Y);
            auto abs_z = OH_ArkUI_FocusAxisEvent_GetAxisValue(inputEvent, UI_FOCUS_AXIS_EVENT_ABS_Z);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "abs_x/abs_y/abs_z = %{public}f/%{public}f/%{public}f", abs_x, abs_y, abs_z);
        }
        if (eventType == ARKUI_UIINPUTEVENT_TYPE_TOUCH) {
            ExtraTouchEventOperator(inputEvent, button);
        } else if (eventType == ARKUI_UIINPUTEVENT_TYPE_AXIS) {
            AxisEventOperator(inputEvent);
        } else if (eventType == ARKUI_UIINPUTEVENT_TYPE_UNKNOWN) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "UNKNOWN UIINPUTEVENT!");
        }
    });
}

// 触摸拦截测试接收器
void TitTestReceiver(ArkUI_NodeHandle& node, const char* str, bool test = false)
{
    if (test) {
        nodeAPI->registerNodeEvent(node, NODE_ON_TOUCH_INTERCEPT, 1, (void *)str);
        nodeAPI->addNodeEventReceiver(node, [](ArkUI_NodeEvent *event) {
            auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
            if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_ON_TOUCH_INTERCEPT) {
                HitTestMode mode = static_cast<HitTestMode>(g_hitTestModes[g_hitIdx]);
                OH_ArkUI_PointerEvent_SetInterceptHitTestMode(inputEvent, mode);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest", "nodeTest hit!");
            }
        });
        return;
    }
    nodeAPI->registerNodeEvent(node, NODE_TOUCH_EVENT, 1, (void *)str);
    nodeAPI->addNodeEventReceiver(node, [](ArkUI_NodeEvent *event) {
        char *str = (char *)OH_ArkUI_NodeEvent_GetUserData(event);
        if (std::string(str) == "nodeParent") {
            auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
            OH_ArkUI_PointerEvent_SetStopPropagation(inputEvent, true);
        }
        if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_TOUCH_EVENT) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "inputTest",
                "%{public}s hit!", str);
        }
    });
}

// 切换按钮接收器，用于切换触摸测试模式
void SwitchBtReceiver(ArkUI_NodeHandle& button)
{
    nodeAPI->registerNodeEvent(button, NODE_ON_CLICK_EVENT, 1, &button);
    nodeAPI->addNodeEventReceiver(button, [](ArkUI_NodeEvent *event) {
        auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
        ArkUI_NodeHandle *button = (ArkUI_NodeHandle *)OH_ArkUI_NodeEvent_GetUserData(event);
        int32_t length = 6;
        g_hitIdx = (g_hitIdx + 1) % length;
        g_ss.str("");
        g_ss << "触摸测试模式: " << g_hitTestNames[g_hitIdx];
        SetButtonLabel(*button, g_ss.str().c_str());
    });
}

// 说明接收器，显示说明文本
void ExplainReceiver(ArkUI_NodeHandle& button)
{
    nodeAPI->registerNodeEvent(button, NODE_ON_CLICK_EVENT, 1, nullptr);
    nodeAPI->addNodeEventReceiver(button, [](ArkUI_NodeEvent *event) {
        SetText(infoText, g_explain.c_str());
    });
}

// 触摸拦截测试模块，创建测试节点树
void TitTestModule()
{
    auto nodeParent = nodeAPI->createNode(ARKUI_NODE_STACK);
    SetWidthPercent(nodeParent, 1);
    SetHeight(nodeParent, SIZE_100);
    SetBorderWidth(nodeParent, BORDER_WIDTH_1);
    SetBorderStyle(nodeParent, ARKUI_BORDER_STYLE_DASHED, DEFAULT_RADIUS);
    TitTestReceiver(nodeParent, "nodeParent");

    auto nodeBro = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidthPercent(nodeBro, 1);
    SetHeight(nodeBro, SIZE_100);
    nodeAPI->addChild(nodeParent, nodeBro);
    TitTestReceiver(nodeBro, "nodeBro");

    auto nodeTest = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidthPercent(nodeTest, 1);
    SetHeight(nodeTest, SIZE_100);
    nodeAPI->addChild(nodeParent, nodeTest);
    TitTestReceiver(nodeTest, "nodeTest", true);

    auto nodeSon = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetWidthPercent(nodeSon, 1);
    SetHeight(nodeSon, SIZE_100);
    SetRowJustifyContent(nodeSon, ARKUI_FLEX_ALIGNMENT_SPACE_BETWEEN);
    TitTestReceiver(nodeSon, "nodeSon");
    nodeAPI->addChild(nodeTest, nodeSon);

    nodeAPI->addChild(column1, nodeParent);
}

// 按钮模块，创建测试按钮
void ButtonModule()
{
    static auto button1 = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetId(button1, "bt");
    SetButtonLabel(button1, "测试按钮1");
    SetWidthPercent(button1, 1);
    SetHeight(button1, SIZE_100);
    SetBackgroundColor(button1, 0xFF0000FF);
    ArkUI_NumberValue enable[] = {1};
    ArkUI_AttributeItem focusableItem = {enable, 1};
    nodeAPI->setAttribute(button1, NODE_FOCUSABLE, &focusableItem);
    Bt1EventReceiver(button1);
    nodeAPI->addChild(column1, button1);

    auto blank1 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetHeight(blank1, BLANK_10);
    nodeAPI->addChild(column1, blank1);

    static auto button2 = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetId(button2, "bt2");
    SetButtonLabel(button2, "测试按钮2");
    SetWidthPercent(button2, 1);
    SetHeight(button2, SIZE_100);
    SetBackgroundColor(button2, 0xFF0000FF);
    nodeAPI->setAttribute(button2, NODE_FOCUSABLE, &focusableItem);
    Bt2EventReceiver(button2);
    nodeAPI->addChild(column1, button2);
    
    auto blank2 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetHeight(blank2, BLANK_10);
    nodeAPI->addChild(column1, blank2);
    
    TitTestModule();
    
    auto row = nodeAPI->createNode(ARKUI_NODE_ROW);
    SetWidthPercent(row, 1);
    SetHeight(row, SIZE_80);
    SetRowJustifyContent(row, ARKUI_FLEX_ALIGNMENT_SPACE_AROUND);
    SetHitTestMode(row, ARKUI_HIT_TEST_MODE_BLOCK_HIERARCHY);
    nodeAPI->addChild(column1, row);
    
    button3 = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetId(button3, "bt3");
    SetButtonLabel(button3, "点击查看说明");
    SetWidthPercent(button3, BUTTON_WIDTH_S);
    SetHeight(button3, SIZE_50);
    ExplainReceiver(button3);
    nodeAPI->addChild(row, button3);
    
    static auto button4 = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    SetId(button4, "bt4");
    SetButtonLabel(button4, "触摸测试模式：Default");
    SetWidthPercent(button4, BUTTON_WIDTH_L);
    SetHeight(button4, SIZE_50);
    SwitchBtReceiver(button4);
    nodeAPI->addChild(row, button4);
}

// 背景事件接收器
void BgEventReceiver(ArkUI_NodeHandle& node)
{
    nodeAPI->registerNodeEvent(node, NODE_TOUCH_EVENT, 1, &node);
    nodeAPI->registerNodeEvent(node, NODE_ON_AXIS, 1, &node);
    nodeAPI->registerNodeEvent(node, NODE_ON_FOCUS_AXIS, 1, &node);
    nodeAPI->addNodeEventReceiver(node, [](ArkUI_NodeEvent *event) {
        ArkUI_NodeHandle *node = (ArkUI_NodeHandle *)OH_ArkUI_NodeEvent_GetUserData(event);
        SetBackgroundColor(*node, 0xFFFFFF00);
    });
}

// 第一个主模块，创建完整的UI界面
void FirstModule(ArkUI_NodeHandle &root)
{
    column1 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetId(column1, "bg");
    SetWidthPercent(column1, 1);
    SetHeightPercent(column1, 1);
    SetColumnJustifyContent(column1, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column1, ARKUI_HORIZONTAL_ALIGNMENT_CENTER);
    SetPadding(column1, BLANK_10);
    BgEventReceiver(column1);

    ButtonModule();

    titleText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetId(titleText, "title");
    SetWidthPercent(titleText, 1);
    SetPadding(titleText, BLANK_10);
    nodeAPI->addChild(column1, titleText);

    infoText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetId(infoText, "info");
    SetText(infoText, g_explain.c_str());
    SetWidthPercent(infoText, 1);
    SetPadding(infoText, BLANK_10);
    nodeAPI->addChild(column1, infoText);

    nodeAPI->addChild(root, column1);
}

} // namespace NativeXComponentSample

#endif // NDKINPUTEVENT_FUNCTION_H