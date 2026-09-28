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

#include "gtest/gtest.h"

#include "base/error/error_code.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "interfaces/native/native_node.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/node_extened.h"
#include "native_interface.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float BORDER_WIDTH_VALUE = 2.0f;
constexpr float BORDER_RADIUS_VALUE = 8.0f;
constexpr uint32_t BORDER_COLOR_VALUE = 0xFF0000FF;
constexpr int32_t BORDER_STYLE_SOLID = 1;
} // namespace

class CapiTextEditorTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: CAPITextEditorShowCounter001
 * @tc.desc: test SetRichEditorShowCounter / Reset / Get via C API
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorShowCounter001, TestSize.Level0)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    // Branch: item->size==0 -> ERROR_CODE_PARAM_INVALID
    ArkUI_NumberValue emptyVal[] = { { .i32 = 0 } };
    ArkUI_AttributeItem emptyItem = { emptyVal, 0 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &emptyItem), ERROR_CODE_PARAM_INVALID);
    // Branch: value[0].i32 out of range (0-1) -> ERROR_CODE_PARAM_INVALID
    ArkUI_NumberValue badOpen[] = { { .i32 = 2 } };
    ArkUI_AttributeItem badOpenItem = { badOpen, 1 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &badOpenItem), ERROR_CODE_PARAM_INVALID);
    // Branch: thresholdPercentage out of range (1-100) -> ERROR_CODE_PARAM_INVALID
    ArkUI_NumberValue badThreshold[] = { { .i32 = 1 }, { .f32 = 0.0f } };
    ArkUI_AttributeItem badThresholdItem = { badThreshold, 2 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &badThresholdItem), ERROR_CODE_PARAM_INVALID);
    // Branch: highlightBorder out of range (0-1) -> ERROR_CODE_PARAM_INVALID
    ArkUI_NumberValue badHighlight[] = { { .i32 = 1 }, { .f32 = 50.0f }, { .i32 = 2 } };
    ArkUI_AttributeItem badHighlightItem = { badHighlight, 3 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &badHighlightItem),
        ERROR_CODE_PARAM_INVALID);
    // Branch: valid params -> ERROR_CODE_NO_ERROR
    ArkUI_NumberValue validVals[] = { { .i32 = 1 }, { .f32 = 50.0f }, { .i32 = 1 } };
    ArkUI_AttributeItem validItem = { validVals, 3 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &validItem), ERROR_CODE_NO_ERROR);
    // Branch: Reset
    nodeAPI->resetAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER);
    // Branch: Get
    const auto* result = nodeAPI->getAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER);
    EXPECT_NE(result, nullptr);
    delete node;
}

/**
 * @tc.name: CAPITextEditorShowCounter002
 * @tc.desc: test SetRichEditorShowCounter with ArkUI_ShowCounterConfig object (counterTextColor/overflowColor isSet)
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorShowCounter002, TestSize.Level0)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    // Branch: config with counterTextColor.isSet=true + counterTextOverflowColor.isSet=true
    ArkUI_ShowCounterConfig config;
    config.counterTextColor.isSet = 1;
    config.counterTextColor.value = 0xFFFF0000;
    config.counterTextOverflowColor.isSet = 1;
    config.counterTextOverflowColor.value = 0xFF00FF00;
    ArkUI_NumberValue vals[] = { { .i32 = 1 }, { .f32 = 50.0f }, { .i32 = 1 } };
    ArkUI_AttributeItem item = { vals, 3 };
    item.object = &config;
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &item), ERROR_CODE_NO_ERROR);
    // Branch: config with counterTextColor.isSet=false (not set)
    config.counterTextColor.isSet = 0;
    config.counterTextOverflowColor.isSet = 0;
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &item), ERROR_CODE_NO_ERROR);
    // Branch: config with only counterTextColor.isSet=true
    config.counterTextColor.isSet = 1;
    config.counterTextColor.value = 0xFF0000FF;
    config.counterTextOverflowColor.isSet = 0;
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &item), ERROR_CODE_NO_ERROR);
    // Branch: config with only counterTextOverflowColor.isSet=true
    config.counterTextColor.isSet = 0;
    config.counterTextOverflowColor.isSet = 1;
    config.counterTextOverflowColor.value = 0xFFFFFF00;
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &item), ERROR_CODE_NO_ERROR);
    delete node;
}

/**
 * @tc.name: CAPITextEditorShowCounter003
 * @tc.desc: test SetRichEditorShowCounter boundary values, partial sizes, get-after-set/reset, and full config
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorShowCounter003, TestSize.Level0)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    auto setCounter = [&nodeAPI, &node](
        int32_t open, float threshold, int32_t highlight, int32_t size) {
        ArkUI_NumberValue vals[] = { { .i32 = open }, { .f32 = threshold }, { .i32 = highlight } };
        ArkUI_AttributeItem item = { vals, size };
        return nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &item);
    };
    // Boundary: open=0/threshold=1/threshold=100 valid, threshold=101 invalid
    EXPECT_EQ(setCounter(0, 50.0f, 1, 3), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(1, 1.0f, 1, 3), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(1, 100.0f, 1, 3), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(1, 101.0f, 1, 3), ERROR_CODE_PARAM_INVALID);
    // Boundary: highlight=0 valid, partial size=1/2, open=-1 invalid
    EXPECT_EQ(setCounter(1, 50.0f, 0, 3), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(1, 0.0f, 0, 1), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(1, 50.0f, 0, 2), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(setCounter(-1, 0.0f, 0, 1), ERROR_CODE_PARAM_INVALID);
    // Get after set with known values
    EXPECT_EQ(setCounter(1, 80.0f, 0, 3), ERROR_CODE_NO_ERROR);
    const auto* result = nodeAPI->getAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER);
    ASSERT_NE(result, nullptr);
    // Full config with both colors set + reset
    ArkUI_ShowCounterConfig config = {};
    config.counterTextColor.isSet = 1;
    config.counterTextColor.value = 0xFF333333;
    config.counterTextOverflowColor.isSet = 1;
    config.counterTextOverflowColor.value = 0xFFFF0000;
    ArkUI_NumberValue fullVals[] = { { .i32 = 1 }, { .f32 = 80.0f }, { .i32 = 1 } };
    ArkUI_AttributeItem fullItem = { fullVals, 3 };
    fullItem.object = &config;
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER, &fullItem), ERROR_CODE_NO_ERROR);
    ASSERT_NE(nodeAPI->getAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER), nullptr);
    nodeAPI->resetAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER);
    ASSERT_NE(nodeAPI->getAttribute(node, NODE_TEXT_EDITOR_SHOW_COUNTER), nullptr);
    delete node;
}

/**
 * @tc.name: CAPITextEditorBorder002
 * @tc.desc: test invalid Border params (width, radius, color, style, percent) for ARKUI_NODE_TEXT_EDITOR
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorBorder002, TestSize.Level0)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    auto expectInvalid = [&nodeAPI, &node](
        ArkUI_NodeAttributeType attr, const ArkUI_NumberValue* vals, int32_t size) {
        ArkUI_AttributeItem item = { vals, size };
        EXPECT_EQ(nodeAPI->setAttribute(node, attr, &item), ERROR_CODE_PARAM_INVALID);
    };
    // border width: size=0, negative, size=2, size=4-with-negative
    ArkUI_NumberValue zeroVal[] = { { .f32 = 1.0f } }; expectInvalid(NODE_BORDER_WIDTH, zeroVal, 0);
    ArkUI_NumberValue negVal[] = { { .f32 = -1.0f } }; expectInvalid(NODE_BORDER_WIDTH, negVal, 1);
    ArkUI_NumberValue width2[] = { { .f32 = BORDER_WIDTH_VALUE }, { .f32 = BORDER_WIDTH_VALUE } };
    expectInvalid(NODE_BORDER_WIDTH, width2, 2);
    ArkUI_NumberValue badWidth4[] = { { .f32 = 1.0f }, { .f32 = -1.0f }, { .f32 = 3.0f }, { .f32 = 4.0f } };
    expectInvalid(NODE_BORDER_WIDTH, badWidth4, 4);
    // border radius: size=0, negative, size=2, size=4-with-negative
    expectInvalid(NODE_BORDER_RADIUS, zeroVal, 0);
    ArkUI_NumberValue negRadius[] = { { .f32 = -1.0f } }; expectInvalid(NODE_BORDER_RADIUS, negRadius, 1);
    ArkUI_NumberValue radius2[] = { { .f32 = 1.0f }, { .f32 = 2.0f } };
    expectInvalid(NODE_BORDER_RADIUS, radius2, 2);
    ArkUI_NumberValue badRadius4[] = { { .f32 = 1.0f }, { .f32 = -2.0f }, { .f32 = 3.0f }, { .f32 = 4.0f } };
    expectInvalid(NODE_BORDER_RADIUS, badRadius4, 4);
    // border color: size=0, size=2
    ArkUI_NumberValue zeroColor[] = { { .u32 = 0xFF0000 } }; expectInvalid(NODE_BORDER_COLOR, zeroColor, 0);
    ArkUI_NumberValue color2[] = { { .u32 = 0xFF0000 }, { .u32 = 0x00FF00 } };
    expectInvalid(NODE_BORDER_COLOR, color2, 2);
    // border style: size=4-invalid, size=2, size=1-invalid
    ArkUI_NumberValue badStyle4[] = { { .i32 = BORDER_STYLE_SOLID }, { .i32 = 99 },
        { .i32 = BORDER_STYLE_SOLID }, { .i32 = BORDER_STYLE_SOLID } };
    expectInvalid(NODE_BORDER_STYLE, badStyle4, 4);
    ArkUI_NumberValue style2[] = { { .i32 = BORDER_STYLE_SOLID }, { .i32 = BORDER_STYLE_SOLID } };
    expectInvalid(NODE_BORDER_STYLE, style2, 2);
    ArkUI_NumberValue badStyle1[] = { { .i32 = -1 } }; expectInvalid(NODE_BORDER_STYLE, badStyle1, 1);
    // border width percent: size=0, size=4-with-negative
    expectInvalid(NODE_BORDER_WIDTH_PERCENT, zeroVal, 0);
    ArkUI_NumberValue badWidthPct4[] = { { .f32 = 1.0f }, { .f32 = -2.0f }, { .f32 = 3.0f }, { .f32 = 4.0f } };
    expectInvalid(NODE_BORDER_WIDTH_PERCENT, badWidthPct4, 4);
    // border radius percent: size=0, size=4-with-negative
    expectInvalid(NODE_BORDER_RADIUS_PERCENT, zeroVal, 0);
    ArkUI_NumberValue badRadiusPct4[] = { { .f32 = 1.0f }, { .f32 = -2.0f }, { .f32 = 3.0f }, { .f32 = 4.0f } };
    expectInvalid(NODE_BORDER_RADIUS_PERCENT, badRadiusPct4, 4);
    delete node;
}

/**
 * @tc.name: CAPITextEditorMargin001
 * @tc.desc: test SetMargin/GetMargin/ResetMargin for ARKUI_NODE_TEXT_EDITOR via C API
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorMargin001, TestSize.Level0)
{
    // B1: SetMargin with item->size == 4 (all four sides)
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    // Set margin with 4 values
    ArkUI_NumberValue marginVals[] = { { .f32 = 10.0f }, { .f32 = 20.0f }, { .f32 = 30.0f }, { .f32 = 40.0f } };
    ArkUI_AttributeItem marginItem = { marginVals, 4 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_MARGIN, &marginItem), ERROR_CODE_NO_ERROR);
    // Get and verify
    const auto* result = nodeAPI->getAttribute(node, NODE_MARGIN);
    ASSERT_NE(result, nullptr);
    delete node;
}

/**
 * @tc.name: CAPITextEditorMargin002
 * @tc.desc: test SetMargin with single value (all sides same) and Reset for ARKUI_NODE_TEXT_EDITOR
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorMargin002, TestSize.Level0)
{
    // B2: SetMargin with item->size == 1 (single value for all sides)
    // B3: ResetMargin -> all zeros
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    // Set margin with 1 value (all sides same)
    ArkUI_NumberValue singleVal[] = { { .f32 = 15.0f } };
    ArkUI_AttributeItem singleItem = { singleVal, 1 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_MARGIN, &singleItem), ERROR_CODE_NO_ERROR);
    // Get and verify
    const auto* result = nodeAPI->getAttribute(node, NODE_MARGIN);
    ASSERT_NE(result, nullptr);
    // Reset margin
    nodeAPI->resetAttribute(node, NODE_MARGIN);
    // Get after reset - should be 0
    const auto* resetResult = nodeAPI->getAttribute(node, NODE_MARGIN);
    ASSERT_NE(resetResult, nullptr);
    EXPECT_FLOAT_EQ(resetResult->value[0].f32, 0.0f);
    EXPECT_FLOAT_EQ(resetResult->value[1].f32, 0.0f);
    EXPECT_FLOAT_EQ(resetResult->value[2].f32, 0.0f);
    EXPECT_FLOAT_EQ(resetResult->value[3].f32, 0.0f);
    delete node;
}

/**
 * @tc.name: CAPITextEditorMargin003
 * @tc.desc: test SetMargin with invalid parameters for ARKUI_NODE_TEXT_EDITOR
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextEditorTestNg, CAPITextEditorMargin003, TestSize.Level0)
{
    // B4: SetMargin with invalid size (0 or 2/3) -> ERROR_CODE_PARAM_INVALID
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto node = new ArkUI_Node({ ARKUI_NODE_TEXT_EDITOR, nullptr, true });
    ASSERT_NE(node, nullptr);
    // Invalid: size == 0
    ArkUI_NumberValue emptyVals[] = { { .f32 = 0.0f } };
    ArkUI_AttributeItem emptyItem = { emptyVals, 0 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_MARGIN, &emptyItem), ERROR_CODE_PARAM_INVALID);
    // Invalid: size == 2 (not 1 or 4)
    ArkUI_NumberValue twoVals[] = { { .f32 = 1.0f }, { .f32 = 2.0f } };
    ArkUI_AttributeItem twoItem = { twoVals, 2 };
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_MARGIN, &twoItem), ERROR_CODE_PARAM_INVALID);
    // Invalid: null item
    EXPECT_EQ(nodeAPI->setAttribute(node, NODE_MARGIN, nullptr), ERROR_CODE_PARAM_INVALID);
    delete node;
}

} // namespace OHOS::Ace::NG
