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

#include "datepicker_test.h"
#include "../manager/plugin_manager.h"
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <string>

namespace ArkUIDatePickerCApiDemo {

#define ON_CLICK_EVENT_ID_01 6101
#define ON_CLICK_EVENT_ID_02 6102
#define ON_CLICK_EVENT_ID_03 6103

#define BUTTON_LUNAR 1
#define BUTTON_CAN_LOOP 2
#define BUTTON_MODE 3

std::vector<int> g_loopValues = {1, 0, -1};
int g_loopIndex = 0;
int g_modeCount = 3;
bool g_isLunar = false;
int g_mode = 0;

void SetAttributeInt32(ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle node,
    ArkUI_NodeAttributeType attr, int32_t value)
{
    ArkUI_NumberValue val[] = {{.i32 = value}};
    ArkUI_AttributeItem item = {val, sizeof(val) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(node, attr, &item);
}

void UpdateButtonLabel(ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle parent,
    int32_t childIndex, const char* text)
{
    auto button = nodeAPI->getChildAt(parent, childIndex);
    ArkUI_AttributeItem text_item = {nullptr, 0};
    text_item.string = text;
    nodeAPI->setAttribute(button, NODE_BUTTON_LABEL, &text_item);
}

static void OnEventReceive(ArkUI_NodeEvent *event)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "ButtonFontScaleTest", "OnEventReceive");
    if (!event) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ButtonFontScaleTest", "OnEventReceive: event is null");
        return;
    }

    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto nodeHandler = OH_ArkUI_NodeEvent_GetNodeHandle(event);
    auto column = nodeAPI->getParent(nodeHandler);
    auto test_datePicker = nodeAPI->getChildAt(column, 0);

    switch (OH_ArkUI_NodeEvent_GetTargetId(event)) {
        case ON_CLICK_EVENT_ID_01: {
            g_isLunar = !g_isLunar;
            SetAttributeInt32(nodeAPI, test_datePicker, NODE_DATE_PICKER_LUNAR, g_isLunar);
            UpdateButtonLabel(nodeAPI, column, BUTTON_LUNAR, g_isLunar ? "切换为公历" : "切换为农历");
            break;
        }
        case ON_CLICK_EVENT_ID_02: {
            g_loopIndex = (g_loopIndex + 1) % g_loopValues.size();
            SetAttributeInt32(nodeAPI, test_datePicker, NODE_DATE_PICKER_CAN_LOOP, g_loopValues[g_loopIndex]);
            UpdateButtonLabel(nodeAPI, column, BUTTON_CAN_LOOP,
                              g_loopIndex == 0   ? "切换循环:true"
                              : g_loopIndex == 1 ? "切换循环:false"
                                                 : "切换循环:异常");
            break;
        }
        case ON_CLICK_EVENT_ID_03: {
            g_mode = (g_mode + 1) % g_modeCount;
            SetAttributeInt32(nodeAPI, test_datePicker, NODE_DATE_PICKER_MODE, g_mode);
            UpdateButtonLabel(nodeAPI, column, BUTTON_MODE,
                              g_mode == 0   ? "切换为年月模式"
                              : g_mode == 1 ? "切换为月日模式"
                                            : "切换为年月日模式");
            break;
        }
        default:
            return;
    }
}

ArkUI_NodeHandle createButton(ArkUI_NativeNodeAPI_1 *nodeAPI, const char *text)
{
    auto btn = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue height_value1[] = {{.f32 = 50}};
    ArkUI_AttributeItem height_item1 = {height_value1, sizeof(height_value1) / sizeof(ArkUI_NumberValue)};
    ArkUI_NumberValue width_value1[] = {{.f32 = 150}};
    ArkUI_AttributeItem width_item1 = {width_value1, sizeof(width_value1) / sizeof(ArkUI_NumberValue)};

    nodeAPI->setAttribute(btn, NODE_WIDTH, &width_item1);
    nodeAPI->setAttribute(btn, NODE_HEIGHT, &height_item1);

    ArkUI_AttributeItem textItem = {.string = text};
    nodeAPI->setAttribute(btn, NODE_BUTTON_LABEL, &textItem);

    ArkUI_NumberValue marginVal[] = {{.f32 = DEFAULT_MARGIN}};
    ArkUI_AttributeItem marginItem = {marginVal, 1};
    nodeAPI->setAttribute(btn, NODE_MARGIN, &marginItem);
    return btn;
};

napi_value DatePickerTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    // 参数校验和初始化
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "DatePickerTest", "CreateNativeNode");
    if (!env || !info) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "DatePickerTest", "Invalid env or info");
        return nullptr;
    }

    // 获取XComponentID
    char xComponentID[PARAM_64] = {0};
    napi_value args[PARAM_1] = {nullptr};
    size_t argc = PARAM_1;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    napi_get_value_string_utf8(env, args[0], xComponentID, PARAM_64, nullptr);

    // 创建节点API实例
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto datePicker = nodeAPI->createNode(ARKUI_NODE_DATE_PICKER);
    auto buttons = {createButton(nodeAPI, "切换为农历"), createButton(nodeAPI, "切换循环:true"),
                    createButton(nodeAPI, "切换为年月模式")};

    // 配置日期选择器
    ArkUI_NumberValue modeVal[] = {{.i32 = ARKUI_DATEPICKER_MODE_DATE}};
    ArkUI_AttributeItem modeItem = {modeVal, 1};
    nodeAPI->setAttribute(datePicker, NODE_DATE_PICKER_MODE, &modeItem);

    ArkUI_AttributeItem selected = {.string = "2024-01-01"};
    ArkUI_AttributeItem start = {.string = "2024-01-01"};
    ArkUI_AttributeItem end = {.string = "2025-12-31"};
    nodeAPI->setAttribute(datePicker, NODE_DATE_PICKER_SELECTED, &selected);
    nodeAPI->setAttribute(datePicker, NODE_DATE_PICKER_START, &start);
    nodeAPI->setAttribute(datePicker, NODE_DATE_PICKER_END, &end);

    // 组装节点树
    nodeAPI->addChild(column, datePicker);
    for (auto btn : buttons) {
        nodeAPI->addChild(column, btn);
    }

    // 注册事件
    nodeAPI->registerNodeEventReceiver(&OnEventReceive);
    int eventId = ON_CLICK_EVENT_ID_01;
    for (auto btn : buttons) {
        nodeAPI->registerNodeEvent(btn, NODE_ON_CLICK, eventId++, nullptr);
    }

    // 挂载到XComponent
    std::string id(xComponentID);
    OH_NativeXComponent_AttachNativeRootNode(PluginManager::GetInstance()->GetNativeXComponent(id), column);
    return nullptr;
}
} // namespace ArkUIDatePickerCApiDemo
