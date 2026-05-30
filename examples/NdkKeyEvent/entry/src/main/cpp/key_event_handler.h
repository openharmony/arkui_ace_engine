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

#ifndef KEY_EVENT_HANDLER_H
#define KEY_EVENT_HANDLER_H

#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <arkui/ui_input_event.h>
#include <string>


namespace KeyEventSample {

// 按键事件回调数据结构
struct KeyEventCallbackData {
    ArkUI_NodeHandle buttonNode;   // Button节点引用
    std::string originalLabel;     // 原始标签文本
    std::string currentLabel;      // 当前标签文本
    int eventCount;                // 事件计数
    ArkUI_NodeEventType eventType; // 事件类型
};

class KeyEventHandler {
public:
    static KeyEventHandler* GetInstance();

    // 初始化按键事件处理器
    void Initialize();

    // 创建带有按键事件的UI组件
    ArkUI_NodeHandle CreateKeyEventNode();

    // 创建Button组件并设置按键事件
    ArkUI_NodeHandle CreateKeyEventButton(const std::string& label, ArkUI_NodeEventType eventType);

    // 创建事件冒泡和消费演示场景
    ArkUI_NodeHandle CreateEventPropagationDemo();

    // 全局事件接收器
    static void GlobalEventReceiver(ArkUI_NodeEvent* event);

    // 按键事件处理函数（通过userdata获取回调信息）
    static void HandleKeyEventWithUserData(ArkUI_NodeEvent* event);

    // 更新Button标签
    static void UpdateButtonLabel(KeyEventCallbackData* callbackData, const ArkUI_UIInputEvent* inputEvent);

    // 处理Button点击事件（请求焦点）
    static void OnButtonClick(ArkUI_NodeEvent* event);

    // 更新Button的焦点状态显示
    static void UpdateButtonFocusState(ArkUI_NodeHandle buttonNode, bool hasFocus);

    // API示例函数
    static void DemoKeyEventSetConsumed(const ArkUI_UIInputEvent* event);
    static void DemoKeyEventStopPropagation(const ArkUI_UIInputEvent* event);

    // 更新父容器事件反馈
    static void UpdateParentContainerEventFeedback(ArkUI_NodeHandle containerNode, bool eventReceived);

    // 获取按键信息的字符串表示
    std::string GetKeyEventInfo(const ArkUI_UIInputEvent* event);
    std::string GetKeyCodeName(int32_t keyCode);
    std::string GetKeyEventTypeName(int32_t eventType);

    // 更新UI显示
    void UpdateKeyEventDisplay(const std::string& info);

    // 获取显示节点
    ArkUI_NodeHandle GetDisplayNode()
    {
        return displayNode_;
    }
    
    static ArkUI_ContextHandle context_;
    
private:
    KeyEventHandler() = default;
    ~KeyEventHandler() = default;

    static KeyEventHandler* instance_;
    ArkUI_NodeHandle displayNode_;
    std::string lastKeyEventInfo_;
};

} // namespace KeyEventSample

#endif // KEY_EVENT_HANDLER_H
