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

// [Start normal_text_list_example]
// NormalTextListExample.h
// 文本列表示例。

#ifndef MYAPPLICATION_NORMALTEXTLISTEXAMPLE_H
#define MYAPPLICATION_NORMALTEXTLISTEXAMPLE_H

#include "ArkUIBaseNode.h"
#include "ArkUIListItemNode.h"
#include "ArkUIListNode.h"
#include "ArkUITextNode.h"
#include <hilog/log.h>

const unsigned int LOG_PRINT_DOMAIN = 0xF811;
const unsigned int LOOP_SIZE = 30;
const unsigned int FONT_SIZE = 16;
const unsigned int HEIGHT_SIZE = 200;
const float PERCENT_WIDTH_1 = 1;
const float PERCENT_HEIGHT_1 = 1;

namespace NativeModule {

// [StartExclude normal_text_list_example]
std::shared_ptr<ArkUIListNode> CreateListContainer()
{
    // 创建组件并挂载
    // 1：创建List组件。
    auto list = std::make_shared<ArkUIListNode>();
    list->SetPercentWidth(PERCENT_WIDTH_1);
    list->SetPercentHeight(PERCENT_HEIGHT_1);
    return list;
}

std::shared_ptr<ArkUITextNode> CreateListItemText(int32_t index)
{
    auto textNode = std::make_shared<ArkUITextNode>();
    textNode->SetTextContent(std::to_string(index));
    textNode->SetFontSize(FONT_SIZE);
    textNode->SetPercentWidth(PERCENT_WIDTH_1);
    textNode->SetHeight(HEIGHT_SIZE);
    textNode->SetBackgroundColor(0xFFfffacd);
    textNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
    return textNode;
}

void LogListItemEventMetadata(ArkUI_UIInputEvent *inputEvent, ArkUI_NodeEventType eventType,
    ArkUI_NodeComponentEvent *componentEvent, ArkUI_NodeHandle nodeHandle)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                 "NdkAddInteractionEvent_eventInfo inputEvent = %{public}p", inputEvent);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                 "NdkAddInteractionEvent_eventInfo eventType = %{public}d", eventType);
    // 获取组件事件中的数字类型数据
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                 "NdkAddInteractionEvent_eventInfo componentEvent = %{public}p", componentEvent);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                 "NdkAddInteractionEvent_eventInfo nodeHandle = %{public}p", nodeHandle);
}

void LogClickEventDetails(ArkUI_UIInputEvent *inputEvent)
{
    // 触发点击事件所进行的操作，从基础事件获取事件信息
    auto x = OH_ArkUI_PointerEvent_GetX(inputEvent);
    auto y = OH_ArkUI_PointerEvent_GetY(inputEvent);
    auto displayX = OH_ArkUI_PointerEvent_GetDisplayX(inputEvent);
    auto displayY = OH_ArkUI_PointerEvent_GetDisplayY(inputEvent);
    auto windowX = OH_ArkUI_PointerEvent_GetWindowX(inputEvent);
    auto windowY = OH_ArkUI_PointerEvent_GetWindowY(inputEvent);
    auto pointerCount = OH_ArkUI_PointerEvent_GetPointerCount(inputEvent);
    auto xByIndex = OH_ArkUI_PointerEvent_GetXByIndex(inputEvent, 0);
    auto yByIndex = OH_ArkUI_PointerEvent_GetYByIndex(inputEvent, 0);
    auto displayXByIndex = OH_ArkUI_PointerEvent_GetDisplayXByIndex(inputEvent, 0);
    auto displayYByIndex = OH_ArkUI_PointerEvent_GetDisplayYByIndex(inputEvent, 0);
    auto windowXByIndex = OH_ArkUI_PointerEvent_GetWindowXByIndex(inputEvent, 0);
    auto windowYByIndex = OH_ArkUI_PointerEvent_GetWindowYByIndex(inputEvent, 0);
    auto pointerId = OH_ArkUI_PointerEvent_GetPointerId(inputEvent, 0);
    auto pressure = OH_ArkUI_PointerEvent_GetPressure(inputEvent, 0);
    auto action = OH_ArkUI_UIInputEvent_GetAction(inputEvent);
    auto eventTime = OH_ArkUI_UIInputEvent_GetEventTime(inputEvent);
    auto sourceType = OH_ArkUI_UIInputEvent_GetSourceType(inputEvent);
    auto type = OH_ArkUI_UIInputEvent_GetType(inputEvent);
    std::string eventInfo =
        "x: " + std::to_string(x) + ", y: " + std::to_string(y) +
        ", displayX: " + std::to_string(displayX) + ", displayY: " + std::to_string(displayY) +
        ", windowX: " + std::to_string(windowX) + ", windowY: " + std::to_string(windowY) +
        ", pointerCount: " + std::to_string(pointerCount) + ", xByIndex: " + std::to_string(xByIndex) +
        ", yByIndex: " + std::to_string(yByIndex) +
        ", displayXByIndex: " + std::to_string(displayXByIndex) +
        ", displayYByIndex: " + std::to_string(displayYByIndex) +
        ", windowXByIndex: " + std::to_string(windowXByIndex) +
        ", windowYByIndex: " + std::to_string(windowYByIndex) +
        ", pointerId: " + std::to_string(pointerId) + ", pressure: " + std::to_string(pressure) +
        ", action: " + std::to_string(action) + ", eventTime: " + std::to_string(eventTime) +
        ", sourceType: " + std::to_string(sourceType) + ", type: " + std::to_string(type);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "[Sample_NdkAddInteractionEvent]",
                 "NdkAddInteractionEvent_eventInfoOfCommonEvent eventInfo = %{public}s",
                 eventInfo.c_str());
}

void OnListItemClick(ArkUI_NodeEvent *event)
{
    // 从组件事件中获取基础事件对象
    auto *inputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
    if (inputEvent == nullptr) {
        return;
    }
    // 从组件事件获取事件类型
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    auto componentEvent = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
    // 获取触发该事件的组件对象
    auto nodeHandle = OH_ArkUI_NodeEvent_GetNodeHandle(event);
    if (nodeHandle == nullptr) {
        return;
    }
    LogListItemEventMetadata(inputEvent, eventType, componentEvent, nodeHandle);
    // 根据eventType来区分事件类型，进行差异化处理，其他获取事件信息的接口也可类似方式来进行差异化的处理
    if (eventType == NODE_ON_CLICK_EVENT) {
        LogClickEventDetails(inputEvent);
    }
}

std::shared_ptr<ArkUIListItemNode> CreateListItem(int32_t index)
{
    // 2：创建ListItem子组件并挂载到List上。
    auto listItem = std::make_shared<ArkUIListItemNode>();
    auto textNode = CreateListItemText(index);
    listItem->AddChild(textNode);
    // 列表项注册点击事件。
    listItem->RegisterOnClick(OnListItemClick);
    return listItem;
}

void RegisterListEvents(const std::shared_ptr<ArkUIListNode> &list)
{
    // 3：注册List相关监听事件.
    list->RegisterOnScrollIndex([](int32_t index) { OH_LOG_INFO(LOG_APP, "on list scroll index: %{public}d", index); });
    // 4: 注册挂载事件。
    list->RegisterOnAppear([]() { OH_LOG_INFO(LOG_APP, "on list mount to tree"); });
    // 5: 注册卸载事件。
    list->RegisterOnDisappear([]() { OH_LOG_INFO(LOG_APP, "on list unmount from tree"); });
}
// [EndExclude normal_text_list_example]

std::shared_ptr<ArkUIBaseNode> CreateTextListExample()
{
    auto list = CreateListContainer();
    for (int32_t i = 0; i < LOOP_SIZE; ++i) {
        list->AddChild(CreateListItem(i));
    }
    RegisterListEvents(list);
    return list;
}
} // namespace NativeModule

#endif // MYAPPLICATION_NORMALTEXTLISTEXAMPLE_H
// [End normal_text_list_example]
