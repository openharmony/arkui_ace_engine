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

#include "key_event_handler.h"

#include <arkui/native_interface.h>
#include <arkui/native_interface_focus.h>
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>
#include <sstream>

#include "container.h"

namespace KeyEventSample {
const int32_t NUMBER_ZERO = 0;
const int32_t NUMBER_ONE = 1;
const int32_t NUMBER_TWO = 2;
const int32_t NUMBER_THREE = 3;
const int32_t NUMBER_FOUR = 4;
const int32_t NUMBER_FIVE = 5;
const int32_t NUMBER_TEN = 10;

static ArkUI_NativeNodeAPI_1* g_nodeAPI = nullptr;
ArkUI_ContextHandle KeyEventHandler::context_ = nullptr;
KeyEventHandler* KeyEventHandler::instance_ = nullptr;

ArkUI_NodeHandle keyEventButton = nullptr;
ArkUI_NodeHandle preIMEButton = nullptr;
ArkUI_NodeHandle dispatchButton = nullptr;

KeyEventHandler* KeyEventHandler::GetInstance()
{
    if (instance_ == nullptr) {
        instance_ = new KeyEventHandler();
    }
    return instance_;
}

ArkUI_NativeNodeAPI_1* OH_ArkUI_NodeAPI_GetAPI()
{
    if (g_nodeAPI) {
        return g_nodeAPI;
    } else {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
        return g_nodeAPI;
    }
}

// 通用UI属性设置工具函数
namespace UIUtils {
void SetNodeSize(ArkUI_NodeHandle node, float width, float height)
{
    ArkUI_NumberValue widthValue = { .f32 = width };
    ArkUI_AttributeItem widthItem = { .value = &widthValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_WIDTH, &widthItem);

    ArkUI_NumberValue heightValue = { .f32 = height };
    ArkUI_AttributeItem heightItem = { .value = &heightValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_HEIGHT, &heightItem);
}

void SetNodeBackgroundColor(ArkUI_NodeHandle node, uint32_t color)
{
    ArkUI_NumberValue bgColorValue = { .u32 = color };
    ArkUI_AttributeItem bgColorItem = { .value = &bgColorValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_BACKGROUND_COLOR, &bgColorItem);
}

void SetNodeBorderRadius(ArkUI_NodeHandle node, float radius)
{
    ArkUI_NumberValue borderRadius = { .f32 = radius };
    ArkUI_AttributeItem radiusItem = { .value = &borderRadius, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_BORDER_RADIUS, &radiusItem);
}

void SetNodePadding(ArkUI_NodeHandle node, float padding)
{
    ArkUI_NumberValue paddingValue = { .f32 = padding };
    ArkUI_AttributeItem paddingItem = { .value = &paddingValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_PADDING, &paddingItem);
}

void SetNodeBorder(ArkUI_NodeHandle node, float width, uint32_t color)
{
    ArkUI_NumberValue borderWidth = { .f32 = width };
    ArkUI_AttributeItem borderWidthItem = { .value = &borderWidth, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_BORDER_WIDTH, &borderWidthItem);

    ArkUI_NumberValue borderColorValue = { .u32 = color };
    ArkUI_AttributeItem borderColorItem = { .value = &borderColorValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_BORDER_COLOR, &borderColorItem);
}

void SetNodeFocusable(ArkUI_NodeHandle node, bool focusable)
{
    ArkUI_NumberValue focusableValue = { .i32 = focusable ? 1 : 0 };
    ArkUI_AttributeItem focusableItem = { .value = &focusableValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(node, NODE_FOCUSABLE, &focusableItem);
}

ArkUI_NodeHandle CreateSpacer(float height)
{
    ArkUI_NodeHandle spacer = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_STACK);
    if (spacer) {
        ArkUI_NumberValue spacerHeight = { .f32 = height };
        ArkUI_AttributeItem spacerHeightItem = { .value = &spacerHeight, .size = 1 };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(spacer, NODE_HEIGHT, &spacerHeightItem);
    }
    return spacer;
}

ArkUI_NodeHandle CreateTextNode(const std::string& text, float fontSize, uint32_t color)
{
    ArkUI_NodeHandle textNode = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_TEXT);
    if (textNode) {
        ArkUI_AttributeItem textItem = { .string = text.c_str() };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(textNode, NODE_TEXT_CONTENT, &textItem);

        ArkUI_NumberValue fontSizeValue = { .f32 = fontSize };
        ArkUI_AttributeItem fontSizeItem = { .value = &fontSizeValue, .size = 1 };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(textNode, NODE_FONT_SIZE, &fontSizeItem);

        ArkUI_NumberValue colorValue = { .u32 = color };
        ArkUI_AttributeItem colorItem = { .value = &colorValue, .size = 1 };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(textNode, NODE_FONT_COLOR, &colorItem);
    }
    return textNode;
}
} // namespace UIUtils

ArkUI_NodeHandle CreateTitleText()
{
    return UIUtils::CreateTextNode("Key Event Sample", 22.0f, 0xFF2E5BBA);
}

void SetRootColumnAttribute(ArkUI_NodeHandle& columnNode)
{
    // 设置Column的基本样式
    UIUtils::SetNodeSize(columnNode, 350.0f, 500.0f);
    UIUtils::SetNodeBackgroundColor(columnNode, 0xFFF8F9FA);
    UIUtils::SetNodeBorderRadius(columnNode, 16.0f);
    UIUtils::SetNodePadding(columnNode, 20.0f);

    // 创建并添加标题文本
    ArkUI_NodeHandle titleNode = CreateTitleText();
    if (titleNode) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(columnNode, titleNode);
    }

    // 添加间距
    ArkUI_NodeHandle spacer = UIUtils::CreateSpacer(20.0f);
    if (spacer) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(columnNode, spacer);
    }
}

ArkUI_NodeHandle CreateOuterColumnTitle()
{
    return UIUtils::CreateTextNode("Event Propagation Demo", 16.0f, 0xFF2E7D32);
}

void SetOuterColumnAttribute(ArkUI_NodeHandle& outerColumn)
{
    // 设置外层Column基本样式
    UIUtils::SetNodeSize(outerColumn, 300.0f, 120.0f);
    UIUtils::SetNodeBackgroundColor(outerColumn, 0xFFE8F5E8);
    UIUtils::SetNodeBorderRadius(outerColumn, 8.0f);
    UIUtils::SetNodeBorder(outerColumn, 2.0f, 0xFF4CAF50);
    UIUtils::SetNodePadding(outerColumn, 10.0f);
    UIUtils::SetNodeFocusable(outerColumn, true);

    // 设置ID
    ArkUI_AttributeItem idItem = { .string = "parentColumn" };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(outerColumn, NODE_ID, &idItem);

    // 创建并添加标题文本
    ArkUI_NodeHandle titleNode = CreateOuterColumnTitle();
    if (titleNode) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(outerColumn, titleNode);
    }
}

void KeyEventHandler::Initialize()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Initialize begins");

    // 创建显示节点
    displayNode_ = UIUtils::CreateTextNode("Click buttons below to test key events...", 14.0f, 0xFF666666);
}

ArkUI_NodeHandle CreateButtonsContainer()
{
    ArkUI_NodeHandle columnNode = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_COLUMN);
    if (!columnNode) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Failed to create column node");
        return nullptr;
    }

    SetRootColumnAttribute(columnNode);
    return columnNode;
}

void AddButtonWithSpacer(ArkUI_NodeHandle container, ArkUI_NodeHandle button, const std::string& buttonId)
{
    if (button) {
        ArkUI_AttributeItem idItem = { .string = buttonId.c_str() };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(button, NODE_ID, &idItem);
        OH_ArkUI_NodeAPI_GetAPI()->addChild(container, button);

        // 添加间距
        ArkUI_NodeHandle spacer = UIUtils::CreateSpacer(12.0f);
        if (spacer) {
            OH_ArkUI_NodeAPI_GetAPI()->addChild(container, spacer);
        }
    }
}

ArkUI_NodeHandle KeyEventHandler::CreateKeyEventNode()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Creating key event node");

    // 创建主容器
    ArkUI_NodeHandle columnNode = CreateButtonsContainer();
    if (!columnNode) {
        return nullptr;
    }
    KeyEventHandler::context_ = OH_ArkUI_GetContextByNode(columnNode);
    
    // 创建三个Button，分别对应三个事件类型
    keyEventButton = CreateKeyEventButton("Key Event (Click to Focus)", NODE_ON_KEY_EVENT);
    AddButtonWithSpacer(columnNode, keyEventButton, "Button1");

    preIMEButton = CreateKeyEventButton("Pre-IME Event (Click to Focus)", NODE_ON_KEY_PRE_IME);
    AddButtonWithSpacer(columnNode, preIMEButton, "Button2");

    dispatchButton = CreateKeyEventButton("Dispatch Event (Click to Focus)", NODE_DISPATCH_KEY_EVENT);
    AddButtonWithSpacer(columnNode, dispatchButton, "Button3");

    // 添加事件冒泡和消费演示场景
    ArkUI_NodeHandle propagationDemo = CreateEventPropagationDemo();
    if (propagationDemo) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(columnNode, propagationDemo);
    }

    // 添加最终间距和显示节点
    ArkUI_NodeHandle finalSpacer = UIUtils::CreateSpacer(20.0f);
    if (finalSpacer) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(columnNode, finalSpacer);
    }

    if (displayNode_) {
        OH_ArkUI_NodeAPI_GetAPI()->addChild(columnNode, displayNode_);
    }

    return columnNode;
}

void SetButtonStyle(ArkUI_NodeHandle buttonNode, const std::string& label)
{
    UIUtils::SetNodeSize(buttonNode, 300.0f, 48.0f);
    UIUtils::SetNodeBackgroundColor(buttonNode, 0xFF4A90E2);
    UIUtils::SetNodeBorderRadius(buttonNode, 8.0f);
    UIUtils::SetNodeFocusable(buttonNode, true);

    // 设置Button文本
    ArkUI_AttributeItem labelItem = { .string = label.c_str() };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(buttonNode, NODE_BUTTON_LABEL, &labelItem);
}

KeyEventCallbackData* CreateCallbackData(
    ArkUI_NodeHandle buttonNode, const std::string& label, ArkUI_NodeEventType eventType)
{
    KeyEventCallbackData* callbackData = new KeyEventCallbackData();
    callbackData->buttonNode = buttonNode;
    callbackData->originalLabel = label;
    callbackData->currentLabel = label;
    callbackData->eventCount = 0;
    callbackData->eventType = eventType;
    return callbackData;
}

void RegisterButtonEvents(
    ArkUI_NodeHandle buttonNode, KeyEventCallbackData* callbackData, ArkUI_NodeEventType eventType)
{
    // 注册全局事件接收器（只需要注册一次）
    static bool receiverRegistered = false;
    if (!receiverRegistered) {
        OH_ArkUI_NodeAPI_GetAPI()->registerNodeEventReceiver(KeyEventHandler::GlobalEventReceiver);
        receiverRegistered = true;
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Global event receiver registered");
    }

    // 注册各种事件
    int32_t result1 = OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(buttonNode, eventType, 0, callbackData);
    int32_t result2 = OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(buttonNode, NODE_ON_CLICK, 1, callbackData);
    int32_t result3 = OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(buttonNode, NODE_ON_FOCUS, 2, callbackData);
    int32_t result4 = OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(buttonNode, NODE_ON_BLUR, 3, callbackData);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
        "Event registration results - Key:%{public}d, Click:%{public}d, Focus:%{public}d, Blur:%{public}d", result1,
        result2, result3, result4);
}

ArkUI_NodeHandle KeyEventHandler::CreateKeyEventButton(const std::string& label, ArkUI_NodeEventType eventType)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Creating button with label: %{public}s",
        label.c_str());

    // 创建Button节点
    ArkUI_NodeHandle buttonNode = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_BUTTON);
    if (!buttonNode) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Failed to create button node");
        return nullptr;
    }

    // 设置按钮样式
    SetButtonStyle(buttonNode, label);

    // 创建回调数据
    KeyEventCallbackData* callbackData = CreateCallbackData(buttonNode, label, eventType);

    // 注册事件
    RegisterButtonEvents(buttonNode, callbackData, eventType);

    return buttonNode;
}

ArkUI_NodeHandle CreateChildButton()
{
    ArkUI_NodeHandle childButton = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_BUTTON);
    if (childButton) {
        UIUtils::SetNodeSize(childButton, 250.0f, 40.0f);
        UIUtils::SetNodeBackgroundColor(childButton, 0xFFFF9800);
        UIUtils::SetNodeBorderRadius(childButton, 6.0f);
        UIUtils::SetNodeFocusable(childButton, true);

        ArkUI_AttributeItem btnLabelItem = { .string = "Child Button (ESC=Consume, F1=StopProp)" };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(childButton, NODE_BUTTON_LABEL, &btnLabelItem);

        ArkUI_AttributeItem idItem = { .string = "Button4" };
        OH_ArkUI_NodeAPI_GetAPI()->setAttribute(childButton, NODE_ID, &idItem);
    }
    return childButton;
}

void RegisterChildButtonEvents(ArkUI_NodeHandle childButton)
{
    KeyEventCallbackData* childCallbackData =
        CreateCallbackData(childButton, "Child Button (ESC=Consume, F1=StopProp)", NODE_ON_KEY_EVENT);

    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(childButton, NODE_ON_KEY_EVENT, NUMBER_ZERO, childCallbackData);
    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(childButton, NODE_ON_CLICK, NUMBER_ONE, childCallbackData);
    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(childButton, NODE_ON_FOCUS, NUMBER_TWO, childCallbackData);
    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(childButton, NODE_ON_BLUR, NUMBER_THREE, childCallbackData);
}

void RegisterParentContainerEvents(ArkUI_NodeHandle outerColumn)
{
    KeyEventCallbackData* parentCallbackData =
        CreateCallbackData(outerColumn, "Parent Column Container", NODE_ON_KEY_EVENT);

    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(outerColumn, NODE_ON_KEY_EVENT, NUMBER_ZERO, parentCallbackData);
    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(outerColumn, NODE_ON_FOCUS, NUMBER_TWO, parentCallbackData);
    OH_ArkUI_NodeAPI_GetAPI()->registerNodeEvent(outerColumn, NODE_ON_BLUR, NUMBER_THREE, parentCallbackData);
}

ArkUI_NodeHandle KeyEventHandler::CreateEventPropagationDemo()
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Creating event propagation demo");

    // 创建外层Column容器
    ArkUI_NodeHandle outerColumn = OH_ArkUI_NodeAPI_GetAPI()->createNode(ARKUI_NODE_COLUMN);
    if (!outerColumn) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Failed to create outer column node");
        return nullptr;
    }

    SetOuterColumnAttribute(outerColumn);

    // 创建并配置子Button
    ArkUI_NodeHandle childButton = CreateChildButton();
    if (childButton) {
        RegisterChildButtonEvents(childButton);
        OH_ArkUI_NodeAPI_GetAPI()->addChild(outerColumn, childButton);
    }

    // 注册父容器事件
    RegisterParentContainerEvents(outerColumn);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Event propagation demo created successfully");

    return outerColumn;
}

void KeyEventHandler::GlobalEventReceiver(ArkUI_NodeEvent* event)
{
    if (!event) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "GlobalEventReceiver: Event is null");
        return;
    }
    OH_ArkUI_FocusActivate(KeyEventHandler::context_, false, false);
    ArkUI_NodeEventType eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
        "GlobalEventReceiver: eventType=%{public}d, targetId=%{public}d", eventType,
        OH_ArkUI_NodeEvent_GetTargetId(event));

    void* userData = OH_ArkUI_NodeEvent_GetUserData(event);
    if (!userData) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_PRINT_DOMAIN, "KeyEventHandler", "No user data found");
        return;
    }
    
    KeyEventCallbackData* callbackData = static_cast<KeyEventCallbackData*>(userData);

    // 根据事件类型分发处理
    switch (eventType) {
        case NODE_ON_CLICK:
            OnButtonClick(event);
            break;
        case NODE_ON_FOCUS:
            UpdateButtonFocusState(callbackData->buttonNode, true);
            break;
        case NODE_ON_BLUR:
            UpdateButtonFocusState(callbackData->buttonNode, false);
            break;
        default:
            // 处理按键事件
            if (eventType == callbackData->eventType && callbackData->buttonNode != dispatchButton) {
                HandleKeyEventWithUserData(event);
            } else if (eventType == callbackData->eventType && callbackData->buttonNode == dispatchButton) {
                ArkUI_NumberValue focusValue = { .i32 = 1 };
                ArkUI_AttributeItem focusItem = { .value = &focusValue, .size = 1 };
                OH_ArkUI_NodeAPI_GetAPI()->setAttribute(keyEventButton, NODE_FOCUS_STATUS, &focusItem);
                OH_ArkUI_KeyEvent_Dispatch(keyEventButton, OH_ArkUI_NodeEvent_GetInputEvent(event));
            }
            break;
    }
}

bool ProcessChildButtonKeyEvent(KeyEventCallbackData* callbackData, const ArkUI_UIInputEvent* inputEvent)
{
    int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(inputEvent);
    if (keyCode == ArkUI_KeyCode::ARKUI_KEYCODE_ESCAPE) { // ESC键 - 演示SetConsumed
        KeyEventHandler::DemoKeyEventSetConsumed(inputEvent);
        OH_LOG_Print(
            LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Child Button: ESC key pressed - Event CONSUMED");
        return true;                                         // 事件已消费，停止后续处理
    } else if (keyCode == ArkUI_KeyCode::ARKUI_KEYCODE_F1) { // F1键 - 演示StopPropagation
        KeyEventHandler::DemoKeyEventStopPropagation(inputEvent);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Child Button: F1 key pressed - Event propagation STOPPED");
        return true; // 事件传播已停止，停止后续处理
    } else {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Child Button: Normal key pressed - Event will propagate to parent");
        return false; // 继续正常处理
    }
}

void ProcessParentContainerKeyEvent(KeyEventCallbackData* callbackData)
{
    // 父容器的按键事件处理 - 更改颜色以显示收到事件
    KeyEventHandler::UpdateParentContainerEventFeedback(callbackData->buttonNode, true);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
        "Parent Container received key event - child did not consume/stop it");

    // 延迟恢复原始颜色
    static int resetCounter = 0;
    resetCounter++;
    if (resetCounter > NUMBER_TEN) {
        resetCounter = 0;
    }
}

std::string GetEventTypeDisplayName(ArkUI_NodeEventType eventType)
{
    switch (eventType) {
        case NODE_ON_KEY_EVENT:
            return "KEY EVENT";
        case NODE_ON_KEY_PRE_IME:
            return "PRE-IME EVENT";
        case NODE_DISPATCH_KEY_EVENT:
            return "DISPATCH EVENT";
        default:
            return "UNKNOWN EVENT";
    }
}

std::string CreateEventInfo(KeyEventCallbackData* callbackData, const ArkUI_UIInputEvent* inputEvent)
{
    KeyEventHandler* instance = KeyEventHandler::GetInstance();
    if (!instance) {
        return "Instance not available";
    }

    std::string eventTypeName = GetEventTypeDisplayName(callbackData->eventType);
    std::string info = instance->GetKeyEventInfo(inputEvent);

    // 如果是事件冒泡演示，添加额外信息
    if (callbackData->originalLabel.find("Child Button") != std::string::npos ||
        callbackData->originalLabel.find("Parent Column") != std::string::npos) {
        int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(inputEvent);
        std::string componentType =
            callbackData->originalLabel.find("Child Button") != std::string::npos ? "Child" : "Parent";

        if (keyCode == ArkUI_KeyCode::ARKUI_KEYCODE_ESCAPE) {
            info += " ESC键被" + componentType + "处理-SetConsumed(true)";
        } else if (keyCode == ArkUI_KeyCode::ARKUI_KEYCODE_F1) {
            info += " F1键被" + componentType + "处理-StopPropagation(true)";
        } else {
            info += " 普通按键被" + componentType + "处理-正常传播";
        }
    }

    return eventTypeName + ":\n" + info + " API调用完成-查看日志详情!";
}

void KeyEventHandler::HandleKeyEventWithUserData(ArkUI_NodeEvent* event)
{
    if (!event) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "HandleKeyEventWithUserData: Event is null");
        return;
    }

    void* userData = OH_ArkUI_NodeEvent_GetUserData(event);
    if (!userData) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "User data is null");
        return;
    }

    KeyEventCallbackData* callbackData = static_cast<KeyEventCallbackData*>(userData);
    const ArkUI_UIInputEvent* inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);

    if (inputEvent) {
        // 检查是否是事件冒泡演示组件
        if (callbackData->originalLabel.find("Child Button") != std::string::npos) {
            bool shouldStop = ProcessChildButtonKeyEvent(callbackData, inputEvent);
            // 无论事件是否被消费/阻止传播，都要更新Child Button的标签和颜色以显示收到事件
            UpdateButtonLabel(callbackData, inputEvent);
            if (shouldStop) {
                // 如果事件被消费或阻止传播，在更新标签后返回，不传播到父容器
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
                    "Child button key event consumed/stopped - updated button but stopping propagation");
                return;
            }
        } else if (callbackData->originalLabel.find("Parent Column") != std::string::npos) {
            ProcessParentContainerKeyEvent(callbackData);
            // 更新Button标签
            UpdateButtonLabel(callbackData, inputEvent);
        } else {
            // 普通按钮的处理
            UpdateButtonLabel(callbackData, inputEvent);
        }

        // 同时更新全局显示
        KeyEventHandler* instance = GetInstance();
        if (instance) {
            std::string displayText = CreateEventInfo(callbackData, inputEvent);
            instance->UpdateKeyEventDisplay(displayText);
        }
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
        "Key event handled with user data and API demos completed");
}

std::string CreateButtonLabelText(KeyEventCallbackData* callbackData, const ArkUI_UIInputEvent* inputEvent)
{
    std::ostringstream oss;
    oss << callbackData->originalLabel;
    oss << " [" << callbackData->eventCount << "]";

    KeyEventHandler* instance = KeyEventHandler::GetInstance();
    if (instance) {
        int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(inputEvent);
        ArkUI_KeyEventType eventType = OH_ArkUI_KeyEvent_GetType(inputEvent);

        std::string keyName = instance->GetKeyCodeName(keyCode);
        std::string typeName = instance->GetKeyEventTypeName(static_cast<int32_t>(eventType));
        oss << " " << keyName << "(" << typeName << ")";
    }

    return oss.str();
}

void UpdateButtonVisualFeedback(ArkUI_NodeHandle buttonNode, const std::string& originalLabel)
{
    // 所有按钮收到按键事件时都变色，以便用户清楚看到事件传播现象
    if (originalLabel.find("Child Button") != std::string::npos) {
        // Child Button
        UIUtils::SetNodeBackgroundColor(buttonNode, 0xFF008D3A); // 深绿色背景
        UIUtils::SetNodeBorder(buttonNode, 3.0f, 0xFFE57373);    // 红色边框
    } else if (originalLabel.find("Parent Column") != std::string::npos) {
        // Parent Column 通过专门的函数处理，这里不处理
        // UpdateParentContainerEventFeedback 函数会处理父容器的变色
    } else {
        // 普通按钮变为绿色
        UIUtils::SetNodeBackgroundColor(buttonNode, 0xFF008D3A); // 深绿色背景
        UIUtils::SetNodeBorder(buttonNode, 3.0f, 0xFFE57373);    // 红色边框
    }
}

void KeyEventHandler::UpdateButtonLabel(KeyEventCallbackData* callbackData, const ArkUI_UIInputEvent* inputEvent)
{
    if (!callbackData || !inputEvent) {
        return;
    }

    // 增加事件计数
    callbackData->eventCount++;

    // 创建新的标签文本
    callbackData->currentLabel = CreateButtonLabelText(callbackData, inputEvent);

    // 更新Button的标签
    ArkUI_AttributeItem labelItem = { .string = callbackData->currentLabel.c_str() };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(callbackData->buttonNode, NODE_BUTTON_LABEL, &labelItem);

    // 更新Button颜色
    UpdateButtonVisualFeedback(callbackData->buttonNode, callbackData->originalLabel);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Button label updated: %{public}s",
        callbackData->currentLabel.c_str());
}

std::string GetBasicKeyEventInfo(const ArkUI_UIInputEvent* event)
{
    std::ostringstream oss;

    int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(event);
    ArkUI_KeyEventType eventType = OH_ArkUI_KeyEvent_GetType(event);

    KeyEventHandler* instance = KeyEventHandler::GetInstance();
    if (instance) {
        std::string keyName = instance->GetKeyCodeName(keyCode);
        std::string typeName = instance->GetKeyEventTypeName(static_cast<int32_t>(eventType));

        oss << "Key:" << keyName << "(" << keyCode << ") ";
        oss << "\nType:" << typeName << " ";
    }

    return oss.str();
}

std::string GetKeySourceInfo(const ArkUI_UIInputEvent* event)
{
    ArkUI_KeySourceType sourceType = OH_ArkUI_KeyEvent_GetKeySource(event);
    std::string sourceName;
    switch (sourceType) {
        case ARKUI_KEY_SOURCE_TYPE_KEYBOARD:
            sourceName = "KEYBOARD";
            break;
        case ARKUI_KEY_SOURCE_TYPE_MOUSE:
            sourceName = "MOUSE";
            break;
        case ARKUI_KEY_SOURCE_TYPE_JOYSTICK:
            sourceName = "JOYSTICK";
            break;
        default:
            sourceName = "UNK";
            break;
    }
    return "/Source:" + sourceName + "\n";
}

std::string GetKeyTextAndUnicodeInfo(const ArkUI_UIInputEvent* event)
{
    std::ostringstream oss;

    // 获取按键文本
    const char* keyText = OH_ArkUI_KeyEvent_GetKeyText(event);
    if (keyText && strlen(keyText) > 0) {
        oss << "KeyText:" << keyText << " ";
    }
    oss << "\n";

    // 获取Unicode值
    uint32_t unicode = OH_ArkUI_KeyEvent_GetUnicode(event);
    oss << "Unicode:0x" << std::hex << unicode << std::dec << " ";
    oss << "\n";

    return oss.str();
}

std::string GetKeyIntentionInfo(const ArkUI_UIInputEvent* event)
{
    std::ostringstream oss;

    ArkUI_KeyIntension intention = OH_ArkUI_KeyEvent_GetKeyIntensionCode(event);
    if (intention != ARKUI_KEY_INTENSION_UNKNOWN) {
        oss << "意图:" << static_cast<int>(intention) << " ";
    }
    oss << "\n";

    return oss.str();
}

std::string GetLockKeysInfo(const ArkUI_UIInputEvent* event)
{
    std::ostringstream oss;

    bool numLock = false;
    bool capsLock = false;
    bool scrollLock = false;
    ArkUI_ErrorCode result1 = OH_ArkUI_KeyEvent_IsNumLockOn(event, &numLock);
    ArkUI_ErrorCode result2 = OH_ArkUI_KeyEvent_IsCapsLockOn(event, &capsLock);
    ArkUI_ErrorCode result3 = OH_ArkUI_KeyEvent_IsScrollLockOn(event, &scrollLock);

    oss << "Locks: ";
    if (result1 == ARKUI_ERROR_CODE_NO_ERROR) {
        oss << "Num" << (numLock ? "✓" : "✗") << " ";
    }
    if (result2 == ARKUI_ERROR_CODE_NO_ERROR) {
        oss << "Caps" << (capsLock ? "✓" : "✗") << " ";
    }
    if (result3 == ARKUI_ERROR_CODE_NO_ERROR) {
        oss << "Scroll" << (scrollLock ? "✓" : "✗");
    }
    oss << "\n";

    return oss.str();
}

std::string KeyEventHandler::GetKeyEventInfo(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        return "Invalid event";
    }

    std::ostringstream oss;

    // 使用Native Key Event API获取按键信息
    try {
        oss << GetBasicKeyEventInfo(event);
        oss << GetKeySourceInfo(event);
        oss << GetKeyTextAndUnicodeInfo(event);
        oss << GetKeyIntentionInfo(event);
        oss << GetLockKeysInfo(event);
    } catch (...) {
        // 如果API调用失败，返回基本信息
        oss << "Key Event Detected\n";
    }

    return oss.str();
}

std::string KeyEventHandler::GetKeyCodeName(int32_t keyCode)
{
    // 简化版本的按键码名称映射
    switch (keyCode) {
        case ArkUI_KeyCode::ARKUI_KEYCODE_0:
            return "KEY_0";
        case ArkUI_KeyCode::ARKUI_KEYCODE_1:
            return "KEY_1";
        case ArkUI_KeyCode::ARKUI_KEYCODE_2:
            return "KEY_2";
        case ArkUI_KeyCode::ARKUI_KEYCODE_3:
            return "KEY_3";
        case ArkUI_KeyCode::ARKUI_KEYCODE_4:
            return "KEY_4";
        case ArkUI_KeyCode::ARKUI_KEYCODE_5:
            return "KEY_5";
        case ArkUI_KeyCode::ARKUI_KEYCODE_6:
            return "KEY_6";
        case ArkUI_KeyCode::ARKUI_KEYCODE_7:
            return "KEY_7";
        case ArkUI_KeyCode::ARKUI_KEYCODE_8:
            return "KEY_8";
        case ArkUI_KeyCode::ARKUI_KEYCODE_9:
            return "KEY_9";
        case ArkUI_KeyCode::ARKUI_KEYCODE_A:
            return "KEY_A";
        case ArkUI_KeyCode::ARKUI_KEYCODE_B:
            return "KEY_B";
        case ArkUI_KeyCode::ARKUI_KEYCODE_C:
            return "KEY_C";
        case ArkUI_KeyCode::ARKUI_KEYCODE_D:
            return "KEY_D";
        case ArkUI_KeyCode::ARKUI_KEYCODE_SPACE:
            return "SPACE";
        case ArkUI_KeyCode::ARKUI_KEYCODE_ENTER:
            return "ENTER";
        case ArkUI_KeyCode::ARKUI_KEYCODE_DEL:
            return "BACKSPACE";
        case ArkUI_KeyCode::ARKUI_KEYCODE_ESCAPE:
            return "ESCAPE";
        default:
            return "OTHER";
    }
}

std::string KeyEventHandler::GetKeyEventTypeName(int32_t eventType)
{
    switch (eventType) {
        case ArkUI_KeyEventType::ARKUI_KEY_EVENT_DOWN:
            return "KEY_DOWN";
        case ArkUI_KeyEventType::ARKUI_KEY_EVENT_UP:
            return "KEY_UP";
        case ArkUI_KeyEventType::ARKUI_KEY_EVENT_LONG_PRESS:
            return "KEY_LONG_PRESS";
        case ArkUI_KeyEventType::ARKUI_KEY_EVENT_CLICK:
            return "KEY_CLICK";
        default:
            return "UNKNOWN_TYPE";
    }
}

void KeyEventHandler::UpdateKeyEventDisplay(const std::string& info)
{
    if (!displayNode_) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Display node is null");
        return;
    }

    lastKeyEventInfo_ = info;

    // 更新文本内容
    ArkUI_AttributeItem item = { .string = info.c_str() };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(displayNode_, NODE_TEXT_CONTENT, &item);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Display updated: %{public}s", info.c_str());
}

std::string GetClickDisplayText(KeyEventCallbackData* callbackData)
{
    if (callbackData->originalLabel.find("Child Button") != std::string::npos) {
        return "Event Propagation Demo Focused!\n\n"
               "按键事件测试:\n"
               "• 按ESC键：调用SetConsumed(true)消费事件\n"
               "• 按F1键：调用StopPropagation(true)阻止冒泡\n"
               "• 按其他键：正常事件传播\n"
               "查看日志了解详细API调用信息";
    } else if (callbackData->originalLabel.find("Parent Column") != std::string::npos) {
        return "Parent Container Focused!\n\n"
               "父容器接收到按键事件时会显示:\n"
               "• 事件是否被子组件消费\n"
               "• 事件是否被阻止冒泡\n"
               "• 完整的按键信息";
    } else {
        // 普通事件按钮的显示信息
        std::string eventTypeName = GetEventTypeDisplayName(callbackData->eventType);
        return eventTypeName + " Button Focused!\n\nPress any key to test the event...";
    }
}

void KeyEventHandler::OnButtonClick(ArkUI_NodeEvent* event)
{
    if (!event) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "OnButtonClick: Event is null");
        return;
    }

    void* userData = OH_ArkUI_NodeEvent_GetUserData(event);
    if (!userData) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "OnButtonClick: User data is null");
        return;
    }

    KeyEventCallbackData* callbackData = static_cast<KeyEventCallbackData*>(userData);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Button clicked, requesting focus");

    // 主动请求焦点
    ArkUI_NumberValue focusValue = { .i32 = 1 };
    ArkUI_AttributeItem focusItem = { .value = &focusValue, .size = 1 };
    OH_ArkUI_NodeAPI_GetAPI()->setAttribute(callbackData->buttonNode, NODE_FOCUS_STATUS, &focusItem);

    // 更新显示信息
    KeyEventHandler* instance = GetInstance();
    if (instance) {
        std::string displayText = GetClickDisplayText(callbackData);
        instance->UpdateKeyEventDisplay(displayText);
    }
}

void KeyEventHandler::UpdateButtonFocusState(ArkUI_NodeHandle buttonNode, bool hasFocus)
{
    if (!buttonNode) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "UpdateButtonFocusState: Button node is null");
        return;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Button focus state changed: %{public}s",
        hasFocus ? "focused" : "blurred");

    // 根据焦点状态更新Button的视觉效果
    if (hasFocus) {
        // 获得焦点时的样式 - 更亮的蓝色和边框
        UIUtils::SetNodeBackgroundColor(buttonNode, 0xFF2E86DE);
        UIUtils::SetNodeBorder(buttonNode, 2.0f, 0xFF1B4F9C);
    } else {
        // 失去焦点时的样式 - 恢复原始颜色
        UIUtils::SetNodeBackgroundColor(buttonNode, 0xFF4A90E2);
        UIUtils::SetNodeBorder(buttonNode, 0.0f, 0x00000000); // 移除边框
    }
}

void KeyEventHandler::DemoKeyEventSetConsumed(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "DemoKeyEventSetConsumed: Event is null");
        return;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Demo: OH_ArkUI_KeyEvent_SetConsumed");

    // 演示OH_ArkUI_KeyEvent_SetConsumed API的使用
    try {
        int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(event);
        ArkUI_KeyEventType eventType = OH_ArkUI_KeyEvent_GetType(event);

        // 设置事件为已消费状态 - ESC键触发此演示
        OH_ArkUI_KeyEvent_SetConsumed(event, true);

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Key event consumed - KeyCode: %{public}d (ESC)", keyCode);

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Event marked as consumed, preventing further propagation");

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Event consumption status set for Type: %{public}d", eventType);
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Failed to set event consumed status");
    }
}

void KeyEventHandler::DemoKeyEventStopPropagation(const ArkUI_UIInputEvent* event)
{
    if (!event) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "DemoKeyEventStopPropagation: Event is null");
        return;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Demo: OH_ArkUI_KeyEvent_StopPropagation");

    // 演示OH_ArkUI_KeyEvent_StopPropagation API的使用
    try {
        int32_t keyCode = OH_ArkUI_KeyEvent_GetKeyCode(event);
        ArkUI_KeyEventType eventType = OH_ArkUI_KeyEvent_GetType(event);

        // 阻止事件冒泡 - F1键触发此演示
        OH_ArkUI_KeyEvent_StopPropagation(event, true);

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Event propagation stopped for F1 Key - KeyCode: %{public}d", keyCode);

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "F1 key event blocked from bubbling up to parent components");

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Propagation control applied for event Type: %{public}d", eventType);
    } catch (...) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler", "Failed to control event propagation");
    }
}

void KeyEventHandler::UpdateParentContainerEventFeedback(ArkUI_NodeHandle containerNode, bool eventReceived)
{
    if (!containerNode) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "UpdateParentContainerEventFeedback: Container node is null");
        return;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
        "Updating parent container visual feedback: %{public}s", eventReceived ? "event received" : "reset");

    if (eventReceived) {
        // 父容器收到按键事件时 - 变为绿色表示事件传播到了父级
        UIUtils::SetNodeBackgroundColor(containerNode, 0xFF008D3A); // 深绿色背景
        UIUtils::SetNodeBorder(containerNode, 3.0f, 0xFFE57373);    // 红色边框

        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler",
            "Parent container highlighted - key event propagated!");
    } else {
        // 恢复原始样式 - 浅绿色表示正常状态
        UIUtils::SetNodeBackgroundColor(containerNode, 0xFFE8F5E8);
        UIUtils::SetNodeBorder(containerNode, 2.0f, 0xFF4CAF50); // 绿色边框

        OH_LOG_Print(
            LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "KeyEventHandler", "Parent container restored to normal state");
    }
}

} // namespace KeyEventSample
