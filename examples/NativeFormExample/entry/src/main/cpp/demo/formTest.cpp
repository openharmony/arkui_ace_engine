/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "formTest.h"

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <cstddef>
#include <cstdint>
#include <hilog/log.h>
#include <napi/native_api.h>
#include "../common/ArkUIButtonNode.h"
#include "../common/ArkUITextNode.h"
#include "../common/ArkUIColumnNode.h"
#include "../common/ArkUICheckboxNode.h"
#include "../common/ArkUISliderNode.h"
#include "../common/ArkUIToggleNode.h"
#include "../common/ArkUIRadioNode.h"
#include "../common/ArkUIBaseNode.h"

namespace NativeNode::Form {

constexpr uint32_t MATRIX_ARRAY_SIZE = 16;
napi_ref g_callbackRef = nullptr;
napi_env g_env = nullptr;
uint32_t g_colors[] = {0xFFFEBB62, 0xffFFA0A4};
float g_stops[] = {0, 1.0};
static ArkUI_ColorStop linerGrand[] = {{g_colors, g_stops, 2}};

NodeManager& NodeManager::GetInstance()
{
    static NodeManager instance;
    return instance;
}

// [Start form_get_nodeapi]
ArkUI_NativeNodeAPI_1* NodeManager::GetNodeApi()
{
    static ArkUI_NativeNodeAPI_1* nodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    return nodeApi;
}
// [End form_get_nodeapi]
    
    
// [Start button_create]
std::shared_ptr<NativeModule::ArkUIBaseNode> CreateButtonExample()
{
    auto column = std::make_shared<NativeModule::ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    auto button = std::make_shared<NativeModule::ArkUIButtonNode>();
    button->SetButtonLabel("This is a Normal Button");
    button->SetMaxFontScale(1.0);
    // [Start button_type]
    auto circleBtn = std::make_shared<NativeModule::ArkUIButtonNode>();
    circleBtn->SetButtonLabel("Circle");
    circleBtn->SetButtonType(ARKUI_BUTTON_TYPE_CIRCLE);
    circleBtn->SetMargin(20, false);
    // [End button_type]
    column->AddChild(button);
    column->AddChild(circleBtn);
    // 将Column添加到Content中
    return column;
}
// [End button_create]
    
// [Start checkbox_create]
std::shared_ptr<NativeModule::ArkUIBaseNode> CreateCheckboxExample()
{
    auto column = std::make_shared<NativeModule::ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    auto checkbox1 = std::make_shared<NativeModule::ArkUICheckboxNode>();
    auto checkbox2 = std::make_shared<NativeModule::ArkUICheckboxNode>();
    auto checkbox3 = std::make_shared<NativeModule::ArkUICheckboxNode>();
    // [Start checkbox_group]
    auto checkboxGroup = std::make_shared<NativeModule::ArkUICheckboxGroupNode>();
    checkboxGroup->SetCheckboxGroupName("check_group");
    // [End checkbox_group]
    // [Start checkbox_properties]
    checkbox1->SetCheckboxGroup("check_group");
    checkbox1->SetSelectColor(0xFFFF0000);
    checkbox2->SetCheckboxGroup("check_group");
    checkbox2->SetUnSelectColor(0xFFFF0000);
    checkbox3->SetCheckboxGroup("check_group");
    checkbox3->SetCheckboxShape(ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE);
    checkbox1->SetCheckboxName("check_group1");
    checkbox2->SetCheckboxName("check_group2");
    checkbox3->SetCheckboxName("check_group3");
    // [End checkbox_properties]

    column->AddChild(checkboxGroup);
    column->AddChild(checkbox1);
    column->AddChild(checkbox2);
    column->AddChild(checkbox3);

    // 将Column添加到Content中
    return column;
}
// [End checkbox_create]
// [Start slider_create]
std::shared_ptr<NativeModule::ArkUIBaseNode> CreateSliderExample()
{
    auto column = std::make_shared<NativeModule::ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    // [Start slider_inset_style]
    auto sliderInSet = std::make_shared<NativeModule::ArkUISliderNode>();
    sliderInSet->SetSliderValue(50);
    sliderInSet->SetSliderStep(10);
    sliderInSet->SetSliderStyle(ARKUI_SLIDER_STYLE_IN_SET);
    sliderInSet->SetBlockColor(0xFF00FF00);
    sliderInSet->SetTrackColor(0xFFFFFF00);
    // [End slider_inset_style]
    // [Start slider_outset_style]
    auto sliderOutSet = std::make_shared<NativeModule::ArkUISliderNode>();
    sliderOutSet->SetSliderValue(50);
    sliderOutSet->SetSliderStep(10);
    sliderOutSet->SetSliderStyle(ARKUI_SLIDER_STYLE_OUT_SET);
    sliderOutSet->SetMargin(20, false);
    sliderOutSet->SetSliderDirection(ARKUI_SLIDER_DIRECTION_VERTICAL);
    sliderOutSet->SetIsReverse(true);
    sliderOutSet->SetIsShowSteps(true);
    // [End slider_outset_style]
    column->AddChild(sliderInSet);
    column->AddChild(sliderOutSet);
    return column;
}
// [End slider_create]
// [Start radio_create]
std::shared_ptr<NativeModule::ArkUIBaseNode> CreateRadioExample()
{
    auto column = std::make_shared<NativeModule::ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    auto radio1 = std::make_shared<NativeModule::ArkUIRadioNode>();
    auto radio2 = std::make_shared<NativeModule::ArkUIRadioNode>();
    auto radio3 = std::make_shared<NativeModule::ArkUIRadioNode>();
    // [Start radio_group]
    radio1->SetIsOn(true);
    radio1->SetRadioGroup("radio_group");
    radio2->SetRadioGroup("radio_group");
    radio3->SetRadioGroup("radio_group");
    // [End radio_group]
    // [Start radio_style]
    radio3->SetRadioStyle(0xFFFF0000, 0xFF00FF00, 0xFF00FFFF);
    // [End radio_style]

    column->AddChild(radio1);
    column->AddChild(radio2);
    column->AddChild(radio3);

    return column;
}
// [End radio_create]
// [Start toggle_create]
std::shared_ptr<NativeModule::ArkUIBaseNode> CreateToggleExample()
{
    auto column = std::make_shared<NativeModule::ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    auto toggle = std::make_shared<NativeModule::ArkUIToggleNode>();
    // [Start toggle_colors]
    toggle->SetSelectedColor(0xFFFF0000);
    toggle->SetUnSelectedColor(0xFF0000FF);
    toggle->SetSwitchPointColor(0xFF00FF00);
    // [End toggle_colors]
    column->AddChild(toggle);

    return column;
}
// [End toggle_create]

napi_value TransTool::InitButtonDemo(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitButtonDemo BEGIN");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitButtonDemo env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitButtonDemo napi_get_cb_info failed");
    }

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "OH_ArkUI_GetBasicNodeAPI after");
    ArkUI_NativeNodeAPI_1* nodeApi = NodeManager::GetNodeApi();
    if (nodeApi != nullptr) {
        if (nodeApi->createNode != nullptr && nodeApi->addChild != nullptr) {
            auto column = CreateButtonExample();
            TransTool::GetInstance()->SetContentHandle(nodeContentHandle);
            TransTool::GetInstance()->SetRootNode(column);
        }
    }
    return nullptr;
}
    
napi_value TransTool::InitSliderDemo(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitSliderDemo BEGIN");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitSliderDemo env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitSliderDemo napi_get_cb_info failed");
    }

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "OH_ArkUI_GetBasicNodeAPI after");
    ArkUI_NativeNodeAPI_1* nodeApi = NodeManager::GetNodeApi();
    if (nodeApi != nullptr) {
        if (nodeApi->createNode != nullptr && nodeApi->addChild != nullptr) {
            auto column = CreateSliderExample();
            TransTool::GetInstance()->SetContentHandle(nodeContentHandle);
            TransTool::GetInstance()->SetRootNode(column);    
        }
    }
    return nullptr;
}
    
napi_value TransTool::InitCheckboxDemo(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitCheckboxDemo BEGIN");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitCheckboxDemo env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitCheckboxDemo napi_get_cb_info failed");
    }

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "OH_ArkUI_GetBasicNodeAPI after");
    ArkUI_NativeNodeAPI_1* nodeApi = NodeManager::GetNodeApi();
    if (nodeApi != nullptr) {
        if (nodeApi->createNode != nullptr && nodeApi->addChild != nullptr) {
            auto column = CreateCheckboxExample();
            TransTool::GetInstance()->SetContentHandle(nodeContentHandle);
            TransTool::GetInstance()->SetRootNode(column);    
        }
    }
    return nullptr;
}
    
napi_value TransTool::InitRadioDemo(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitRadioDemo BEGIN");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitRadioDemo env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitRadioDemo napi_get_cb_info failed");
    }

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "OH_ArkUI_GetBasicNodeAPI after");
    ArkUI_NativeNodeAPI_1* nodeApi = NodeManager::GetNodeApi();
    if (nodeApi != nullptr) {
        if (nodeApi->createNode != nullptr && nodeApi->addChild != nullptr) {
            auto column = CreateRadioExample();
            TransTool::GetInstance()->SetContentHandle(nodeContentHandle);
            TransTool::GetInstance()->SetRootNode(column);    
        }
    }
    return nullptr;
}
    
napi_value TransTool::InitToggleDemo(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitToggleDemo BEGIN");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitToggleDemo env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "InitToggleDemo napi_get_cb_info failed");
    }

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "TransTool", "OH_ArkUI_GetBasicNodeAPI after");
    ArkUI_NativeNodeAPI_1* nodeApi = NodeManager::GetNodeApi();
    if (nodeApi != nullptr) {
        if (nodeApi->createNode != nullptr && nodeApi->addChild != nullptr) {
            auto column = CreateToggleExample();
            TransTool::GetInstance()->SetContentHandle(nodeContentHandle);
            TransTool::GetInstance()->SetRootNode(column);    
        }
    }
    return nullptr;
}
} // namespace NativeNode::Form