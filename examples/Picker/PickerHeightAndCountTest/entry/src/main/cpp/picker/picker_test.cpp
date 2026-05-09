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

#include "picker_test.h"

#include "../manager/plugin_manager.h"

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <cstdint>
#include <string>

namespace PickerHeightAndCountCapi {
namespace {
constexpr int ON_CLICK_DISPLAYED_ITEM_COUNT_3 = 7001;
constexpr int ON_CLICK_DISPLAYED_ITEM_COUNT_8 = 7002;
constexpr int ON_CLICK_DISPLAYED_ITEM_COUNT_100 = 7003;
constexpr int ON_CLICK_RESET_DISPLAYED_ITEM_COUNT = 7004;
constexpr int ON_CLICK_ITEM_HEIGHT_50 = 7011;
constexpr int ON_CLICK_ITEM_HEIGHT_10 = 7012;
constexpr int ON_CLICK_ITEM_HEIGHT_120 = 7013;
constexpr int ON_CLICK_RESET_ITEM_HEIGHT = 7014;
constexpr int ON_CLICK_ITEM_HEIGHT_40 = 7015;
constexpr int ON_CLICK_ITEM_HEIGHT_64 = 7016;

// NODE_PICKER_DISPLAYED_ITEM_COUNT probe values; behavior matches ETS normalizeDisplayedItemCount.
constexpr int32_t K_DISPLAYED_ITEM_COUNT_VALID_ODD = 3;
// Even count in-range: product layer normalizes to the next odd (8 -> 9).
constexpr int32_t K_DISPLAYED_ITEM_COUNT_EVEN_EIGHT_NORMALIZES_TO_NINE = 8;
// Outside [2, 9]: expect clamp to default (7).
constexpr int32_t K_DISPLAYED_ITEM_COUNT_OUT_OF_RANGE = 100;

// NODE_PICKER_ITEM_HEIGHT probe values (vp); align with ETS itemHeight bounds / default 40vp.
constexpr float K_ITEM_HEIGHT_VALID_MID = 50.0f;
constexpr float K_ITEM_HEIGHT_TOO_LOW_FOR_CLAMP = 10.0f; // below valid range -> default 40
constexpr float K_ITEM_HEIGHT_TOO_HIGH_FOR_CLAMP = 120.0f; // above valid range -> default 40
constexpr float K_ITEM_HEIGHT_DEFAULT_VP = 40.0f;
constexpr float K_ITEM_HEIGHT_UPPER_BOUND_VP = 64.0f;
constexpr int32_t K_PICKER_ITEM_VALUE_START = 1;
constexpr int32_t K_PICKER_ITEM_VALUE_END = 20;

ArkUI_NodeHandle gPicker = nullptr;
ArkUI_NodeHandle gDisplayResult = nullptr;
ArkUI_NodeHandle gHeightResult = nullptr;

void SetText(ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle textNode, const std::string& text)
{
    ArkUI_AttributeItem textItem = {.string = text.c_str()};
    nodeAPI->setAttribute(textNode, NODE_TEXT_CONTENT, &textItem);
}

ArkUI_NodeHandle CreateTextNode(ArkUI_NativeNodeAPI_1* nodeAPI, const std::string& text, float size = 14.0f)
{
    auto textNode = nodeAPI->createNode(ARKUI_NODE_TEXT);
    ArkUI_AttributeItem textItem = {.string = text.c_str()};
    nodeAPI->setAttribute(textNode, NODE_TEXT_CONTENT, &textItem);
    ArkUI_NumberValue fontSize[] = {{.f32 = size}};
    ArkUI_AttributeItem sizeItem = {fontSize, 1};
    nodeAPI->setAttribute(textNode, NODE_FONT_SIZE, &sizeItem);
    ArkUI_NumberValue marginValue[] = {{.f32 = static_cast<float>(DEFAULT_MARGIN)}};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    nodeAPI->setAttribute(textNode, NODE_MARGIN, &marginItem);
    return textNode;
}

ArkUI_NodeHandle CreateButtonNode(ArkUI_NativeNodeAPI_1* nodeAPI, const char* label)
{
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_AttributeItem textItem = {.string = label};
    nodeAPI->setAttribute(button, NODE_BUTTON_LABEL, &textItem);
    ArkUI_NumberValue width[] = {{.f32 = 210.0f}};
    ArkUI_AttributeItem widthItem = {width, 1};
    nodeAPI->setAttribute(button, NODE_WIDTH, &widthItem);
    ArkUI_NumberValue marginValue[] = {{.f32 = static_cast<float>(DEFAULT_MARGIN)}};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    nodeAPI->setAttribute(button, NODE_MARGIN, &marginItem);
    return button;
}

void UpdateDisplayedItemCountResult(ArkUI_NativeNodeAPI_1* nodeAPI)
{
    auto attr = nodeAPI->getAttribute(gPicker, NODE_PICKER_DISPLAYED_ITEM_COUNT);
    int32_t value = attr && attr->size > 0 ? attr->value[0].i32 : -1;
    SetText(nodeAPI, gDisplayResult, "displayedItemCount(CAPI): " + std::to_string(value));
}

void UpdateItemHeightResult(ArkUI_NativeNodeAPI_1* nodeAPI)
{
    auto attr = nodeAPI->getAttribute(gPicker, NODE_PICKER_ITEM_HEIGHT);
    float value = attr && attr->size > 0 ? attr->value[0].f32 : -1.0f;
    SetText(nodeAPI, gHeightResult, "itemHeight(CAPI): " + std::to_string(value));
}

void SetDisplayedItemCount(ArkUI_NativeNodeAPI_1* nodeAPI, int32_t value)
{
    ArkUI_NumberValue values[] = {{.i32 = value}};
    ArkUI_AttributeItem item = {values, 1};
    nodeAPI->setAttribute(gPicker, NODE_PICKER_DISPLAYED_ITEM_COUNT, &item);
    UpdateDisplayedItemCountResult(nodeAPI);
}

void SetItemHeight(ArkUI_NativeNodeAPI_1* nodeAPI, float value)
{
    ArkUI_NumberValue values[] = {{.f32 = value}};
    ArkUI_AttributeItem item = {values, 1};
    nodeAPI->setAttribute(gPicker, NODE_PICKER_ITEM_HEIGHT, &item);
    UpdateItemHeightResult(nodeAPI);
}

void OnEventReceive(ArkUI_NodeEvent* event)
{
    if (event == nullptr || gPicker == nullptr) {
        return;
    }
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    if (nodeAPI == nullptr) {
        return;
    }

    switch (OH_ArkUI_NodeEvent_GetTargetId(event)) {
        case ON_CLICK_DISPLAYED_ITEM_COUNT_3:
            SetDisplayedItemCount(nodeAPI, K_DISPLAYED_ITEM_COUNT_VALID_ODD);
            break;
        case ON_CLICK_DISPLAYED_ITEM_COUNT_8:
            SetDisplayedItemCount(nodeAPI, K_DISPLAYED_ITEM_COUNT_EVEN_EIGHT_NORMALIZES_TO_NINE);
            break;
        case ON_CLICK_DISPLAYED_ITEM_COUNT_100:
            SetDisplayedItemCount(nodeAPI, K_DISPLAYED_ITEM_COUNT_OUT_OF_RANGE);
            break;
        case ON_CLICK_ITEM_HEIGHT_50:
            SetItemHeight(nodeAPI, K_ITEM_HEIGHT_VALID_MID);
            break;
        case ON_CLICK_ITEM_HEIGHT_10:
            SetItemHeight(nodeAPI, K_ITEM_HEIGHT_TOO_LOW_FOR_CLAMP);
            break;
        case ON_CLICK_ITEM_HEIGHT_120:
            SetItemHeight(nodeAPI, K_ITEM_HEIGHT_TOO_HIGH_FOR_CLAMP);
            break;
        case ON_CLICK_ITEM_HEIGHT_40:
            SetItemHeight(nodeAPI, K_ITEM_HEIGHT_DEFAULT_VP);
            break;
        case ON_CLICK_ITEM_HEIGHT_64:
            SetItemHeight(nodeAPI, K_ITEM_HEIGHT_UPPER_BOUND_VP);
            break;
        case ON_CLICK_RESET_DISPLAYED_ITEM_COUNT:
            nodeAPI->resetAttribute(gPicker, NODE_PICKER_DISPLAYED_ITEM_COUNT);
            UpdateDisplayedItemCountResult(nodeAPI);
            break;
        case ON_CLICK_RESET_ITEM_HEIGHT:
            nodeAPI->resetAttribute(gPicker, NODE_PICKER_ITEM_HEIGHT);
            UpdateItemHeightResult(nodeAPI);
            break;
        default:
            break;
    }
}

ArkUI_NodeHandle CreateColumnNode(ArkUI_NativeNodeAPI_1* nodeAPI)
{
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    ArkUI_NumberValue width[] = {{.f32 = DEFAULT_WIDTH}};
    ArkUI_AttributeItem widthItem = {width, 1};
    ArkUI_NumberValue height[] = {{.f32 = DEFAULT_HEIGHT}};
    ArkUI_AttributeItem heightItem = {height, 1};
    nodeAPI->setAttribute(column, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(column, NODE_HEIGHT, &heightItem);
    return column;
}

ArkUI_NodeHandle CreatePickerNode(ArkUI_NativeNodeAPI_1* nodeAPI)
{
    auto picker = nodeAPI->createNode(ARKUI_NODE_PICKER);
    ArkUI_NumberValue width[] = {{.f32 = DEFAULT_WIDTH}};
    ArkUI_AttributeItem widthItem = {width, 1};
    ArkUI_NumberValue pickerHeight[] = {{.f32 = 240.0f}};
    ArkUI_AttributeItem pickerHeightItem = {pickerHeight, 1};
    nodeAPI->setAttribute(picker, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(picker, NODE_HEIGHT, &pickerHeightItem);
    for (int32_t i = K_PICKER_ITEM_VALUE_START; i <= K_PICKER_ITEM_VALUE_END; i++) {
        auto textNode = nodeAPI->createNode(ARKUI_NODE_TEXT);
        std::string text = std::to_string(i);
        ArkUI_AttributeItem textItem = {.string = text.c_str()};
        nodeAPI->setAttribute(textNode, NODE_TEXT_CONTENT, &textItem);
        nodeAPI->addChild(picker, textNode);
    }
    return picker;
}

struct PickerControls {
    ArkUI_NodeHandle displayButton3 = nullptr;
    ArkUI_NodeHandle displayButton8 = nullptr;
    ArkUI_NodeHandle displayButton100 = nullptr;
    ArkUI_NodeHandle resetDisplayButton = nullptr;
    ArkUI_NodeHandle heightButton50 = nullptr;
    ArkUI_NodeHandle heightButton10 = nullptr;
    ArkUI_NodeHandle heightButton120 = nullptr;
    ArkUI_NodeHandle heightButton40 = nullptr;
    ArkUI_NodeHandle heightButton64 = nullptr;
    ArkUI_NodeHandle resetHeightButton = nullptr;
};

PickerControls CreatePickerControls(ArkUI_NativeNodeAPI_1* nodeAPI)
{
    PickerControls controls;
    controls.displayButton3 = CreateButtonNode(nodeAPI, "displayedItemCount=3 (正常)");
    controls.displayButton8 = CreateButtonNode(nodeAPI, "displayedItemCount=8 (偶数->9)");
    controls.displayButton100 = CreateButtonNode(nodeAPI, "displayedItemCount=100 (越界->7)");
    controls.resetDisplayButton = CreateButtonNode(nodeAPI, "reset displayedItemCount");
    controls.heightButton50 = CreateButtonNode(nodeAPI, "itemHeight=50 (正常)");
    controls.heightButton10 = CreateButtonNode(nodeAPI, "itemHeight=10 (越界->40)");
    controls.heightButton120 = CreateButtonNode(nodeAPI, "itemHeight=120 (越界->40)");
    controls.heightButton40 = CreateButtonNode(nodeAPI, "itemHeight=40 (边界)");
    controls.heightButton64 = CreateButtonNode(nodeAPI, "itemHeight=64 (边界)");
    controls.resetHeightButton = CreateButtonNode(nodeAPI, "reset itemHeight");
    return controls;
}

void AddChildrenToColumn(ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle column, const PickerControls& controls)
{
    nodeAPI->addChild(column, gPicker);
    nodeAPI->addChild(column, gDisplayResult);
    nodeAPI->addChild(column, gHeightResult);
    nodeAPI->addChild(column, controls.displayButton3);
    nodeAPI->addChild(column, controls.displayButton8);
    nodeAPI->addChild(column, controls.displayButton100);
    nodeAPI->addChild(column, controls.resetDisplayButton);
    nodeAPI->addChild(column, controls.heightButton50);
    nodeAPI->addChild(column, controls.heightButton10);
    nodeAPI->addChild(column, controls.heightButton120);
    nodeAPI->addChild(column, controls.heightButton40);
    nodeAPI->addChild(column, controls.heightButton64);
    nodeAPI->addChild(column, controls.resetHeightButton);
}

void RegisterControlEvents(ArkUI_NativeNodeAPI_1* nodeAPI, const PickerControls& controls)
{
    nodeAPI->registerNodeEventReceiver(&OnEventReceive);
    nodeAPI->registerNodeEvent(controls.displayButton3, NODE_ON_CLICK, ON_CLICK_DISPLAYED_ITEM_COUNT_3, nullptr);
    nodeAPI->registerNodeEvent(controls.displayButton8, NODE_ON_CLICK, ON_CLICK_DISPLAYED_ITEM_COUNT_8, nullptr);
    nodeAPI->registerNodeEvent(controls.displayButton100, NODE_ON_CLICK, ON_CLICK_DISPLAYED_ITEM_COUNT_100, nullptr);
    nodeAPI->registerNodeEvent(
        controls.resetDisplayButton, NODE_ON_CLICK, ON_CLICK_RESET_DISPLAYED_ITEM_COUNT, nullptr);
    nodeAPI->registerNodeEvent(controls.heightButton50, NODE_ON_CLICK, ON_CLICK_ITEM_HEIGHT_50, nullptr);
    nodeAPI->registerNodeEvent(controls.heightButton10, NODE_ON_CLICK, ON_CLICK_ITEM_HEIGHT_10, nullptr);
    nodeAPI->registerNodeEvent(controls.heightButton120, NODE_ON_CLICK, ON_CLICK_ITEM_HEIGHT_120, nullptr);
    nodeAPI->registerNodeEvent(controls.heightButton40, NODE_ON_CLICK, ON_CLICK_ITEM_HEIGHT_40, nullptr);
    nodeAPI->registerNodeEvent(controls.heightButton64, NODE_ON_CLICK, ON_CLICK_ITEM_HEIGHT_64, nullptr);
    nodeAPI->registerNodeEvent(controls.resetHeightButton, NODE_ON_CLICK, ON_CLICK_RESET_ITEM_HEIGHT, nullptr);
}
} // namespace

napi_value PickerTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if (env == nullptr || info == nullptr) {
        return nullptr;
    }

    char xComponentID[PARAM_64] = {0};
    napi_value args[PARAM_1] = {nullptr};
    size_t argc = PARAM_1;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    napi_get_value_string_utf8(env, args[0], xComponentID, PARAM_64, nullptr);

    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    if (nodeAPI == nullptr) {
        return nullptr;
    }

    auto column = CreateColumnNode(nodeAPI);
    gPicker = CreatePickerNode(nodeAPI);
    gDisplayResult = CreateTextNode(nodeAPI, "displayedItemCount(CAPI): 7");
    gHeightResult = CreateTextNode(nodeAPI, "itemHeight(CAPI): 40.000000");
    auto controls = CreatePickerControls(nodeAPI);
    AddChildrenToColumn(nodeAPI, column, controls);
    RegisterControlEvents(nodeAPI, controls);

    std::string id(xComponentID);
    OH_NativeXComponent_AttachNativeRootNode(PluginManager::GetInstance()->GetNativeXComponent(id), column);
    return nullptr;
}
} // namespace PickerHeightAndCountCapi
