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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/common_text/text_border_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/components/text_field/textfield_theme.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int DEFAULT_LENGTH = 4;
// Static mock flags for verifying setFunc invocation
static bool g_borderColorCalled = false;
static bool g_borderStyleCalled = false;
static bool g_borderRadiusCalled = false;
static bool g_borderWidthCalled = false;

static NG::BorderColorProperty g_lastBorderColors;
static NG::BorderStyleProperty g_lastBorderStyles;
static NG::BorderRadiusProperty g_lastBorderRadius;
static NG::BorderWidthProperty g_lastBorderWidth;

void MockSetBorderWidth(NG::FrameNode* frameNode, const NG::BorderWidthProperty& borderWidth)
{
    g_borderWidthCalled = true;
    g_lastBorderWidth = borderWidth;
}

void MockSetBorderColor(NG::FrameNode* frameNode, const NG::BorderColorProperty& borderColors)
{
    g_borderColorCalled = true;
    g_lastBorderColors = borderColors;
}

void MockSetBorderStyle(NG::FrameNode* frameNode, const NG::BorderStyleProperty& borderStyles)
{
    g_borderStyleCalled = true;
    g_lastBorderStyles = borderStyles;
}

void MockSetBorderRadius(NG::FrameNode* frameNode, const NG::BorderRadiusProperty& borderRadius)
{
    g_borderRadiusCalled = true;
    g_lastBorderRadius = borderRadius;
}

void ResetMockFlags()
{
    g_borderColorCalled = false;
    g_borderStyleCalled = false;
    g_borderRadiusCalled = false;
    g_borderWidthCalled = false;
}
} // namespace

class RichEditorBorderUtilsTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorBorderUtilsTestNg::SetUp()
{
    NG::MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    NG::MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textFieldTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(textFieldTheme));
    ResetMockFlags();
}

void RichEditorBorderUtilsTestNg::TearDown()
{
    NG::MockPipelineContext::TearDown();
    ResetMockFlags();
}

void RichEditorBorderUtilsTestNg::TearDownTestSuite()
{
    NG::TestNG::TearDownTestSuite();
}

/**
 * @tc.name: ConvertBorderStyle001
 * @tc.desc: Test ConvertBorderStyle with valid BorderStyle values (0-3)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ConvertBorderStyle001, TestSize.Level0)
{
    // B2: valid values -> keep original style
    EXPECT_EQ(ConvertBorderStyle(static_cast<int32_t>(BorderStyle::SOLID)), BorderStyle::SOLID);
    EXPECT_EQ(ConvertBorderStyle(static_cast<int32_t>(BorderStyle::DASHED)), BorderStyle::DASHED);
    EXPECT_EQ(ConvertBorderStyle(static_cast<int32_t>(BorderStyle::DOTTED)), BorderStyle::DOTTED);
    EXPECT_EQ(ConvertBorderStyle(static_cast<int32_t>(BorderStyle::NONE)), BorderStyle::NONE);
}

/**
 * @tc.name: ConvertBorderStyle002
 * @tc.desc: Test ConvertBorderStyle with invalid values (out of range)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ConvertBorderStyle002, TestSize.Level0)
{
    // B1: invalid values -> default to SOLID
    EXPECT_EQ(ConvertBorderStyle(-1), BorderStyle::SOLID);
    EXPECT_EQ(ConvertBorderStyle(4), BorderStyle::SOLID);
    EXPECT_EQ(ConvertBorderStyle(100), BorderStyle::SOLID);
    EXPECT_EQ(ConvertBorderStyle(-100), BorderStyle::SOLID);
}

/**
 * @tc.name: ParseBorderColor001
 * @tc.desc: Test ParseBorderColor with all null resource objects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ParseBorderColor001, TestSize.Level0)
{
    // B2,B4,B6,B8: all null -> resMap_ empty after clear
    NG::BorderColorProperty borderColors;
    ParseBorderColor(borderColors, nullptr, nullptr, nullptr, nullptr);
    EXPECT_TRUE(borderColors.resMap_.empty());
}

/**
 * @tc.name: ParseBorderColor002
 * @tc.desc: Test ParseBorderColor with all non-null resource objects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ParseBorderColor002, TestSize.Level0)
{
    // B1,B3,B5,B7: all non-null -> all 4 resources added
    NG::BorderColorProperty borderColors;
    auto topRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto rightRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto bottomRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto leftRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    ParseBorderColor(borderColors, topRes, rightRes, bottomRes, leftRes);
    EXPECT_EQ(borderColors.resMap_.size(), 4u);
}

/**
 * @tc.name: ParseBorderColor003
 * @tc.desc: Test ParseBorderColor with mixed null/non-null (top and bottom non-null, right and left null)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ParseBorderColor003, TestSize.Level0)
{
    // B1,B4,B5,B8: top+bottom non-null, right+left null
    NG::BorderColorProperty borderColors;
    auto topRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto bottomRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    ParseBorderColor(borderColors, topRes, nullptr, bottomRes, nullptr);
    EXPECT_EQ(borderColors.resMap_.size(), 2u);
}

/**
 * @tc.name: ResetBorderColorCommon001
 * @tc.desc: Test ResetBorderColorCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderColorCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ResetBorderColorCommon(nullptr, MockSetBorderColor);
    EXPECT_FALSE(g_borderColorCalled);
}

/**
 * @tc.name: ResetBorderColorCommon002
 * @tc.desc: Test ResetBorderColorCommon with valid node (setFunc called with BLACK)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderColorCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with BLACK color
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetBorderColorCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetBorderColor);
    EXPECT_TRUE(g_borderColorCalled);
    EXPECT_TRUE(g_lastBorderColors.topColor.has_value());
    EXPECT_EQ(g_lastBorderColors.topColor.value(), Color::BLACK);
}

/**
 * @tc.name: ResetBorderStyleCommon001
 * @tc.desc: Test ResetBorderStyleCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderStyleCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ResetBorderStyleCommon(nullptr, MockSetBorderStyle);
    EXPECT_FALSE(g_borderStyleCalled);
}

/**
 * @tc.name: ResetBorderStyleCommon002
 * @tc.desc: Test ResetBorderStyleCommon with valid node (setFunc called with SOLID)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderStyleCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with SOLID style
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test2", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetBorderStyleCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetBorderStyle);
    EXPECT_TRUE(g_borderStyleCalled);
    EXPECT_TRUE(g_lastBorderStyles.styleTop.has_value());
    EXPECT_EQ(g_lastBorderStyles.styleTop.value(), BorderStyle::SOLID);
}

/**
 * @tc.name: ResetBorderRadiusCommon001
 * @tc.desc: Test ResetBorderRadiusCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderRadiusCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ResetBorderRadiusCommon(nullptr, MockSetBorderRadius);
    EXPECT_FALSE(g_borderRadiusCalled);
}

/**
 * @tc.name: ResetBorderRadiusCommon002
 * @tc.desc: Test ResetBorderRadiusCommon with valid node (setFunc called with radius 0)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderRadiusCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with radius 0
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test3", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetBorderRadiusCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetBorderRadius);
    EXPECT_TRUE(g_borderRadiusCalled);
}

/**
 * @tc.name: SetBorderWidthCommon001
 * @tc.desc: Test SetBorderWidthCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUI_Float32 values[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(nullptr, values, units, DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_FALSE(g_borderWidthCalled);
}

/**
 * @tc.name: SetBorderWidthCommon002
 * @tc.desc: Test SetBorderWidthCommon with length != 4 (early return)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon002, TestSize.Level0)
{
    // B2: length != DEFAULT_LENGTH -> early return
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW1", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, 2.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units, 2,
        MockSetBorderWidth);
    EXPECT_FALSE(g_borderWidthCalled);
}

/**
 * @tc.name: SetBorderWidthCommon003
 * @tc.desc: Test SetBorderWidthCommon with all valid values and units
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon003, TestSize.Level0)
{
    // B3-B10: all 4 sides valid (value != -1 && unit != INVALID)
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW2", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_TRUE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.topDimen.value().Value(), 1.0f);
    EXPECT_TRUE(g_lastBorderWidth.rightDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.rightDimen.value().Value(), 2.0f);
    EXPECT_TRUE(g_lastBorderWidth.bottomDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.bottomDimen.value().Value(), 3.0f);
    EXPECT_TRUE(g_lastBorderWidth.leftDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.leftDimen.value().Value(), 4.0f);
}

/**
 * @tc.name: SetBorderWidthCommon004
 * @tc.desc: Test SetBorderWidthCommon with all values == -1 (no optionals set)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon004, TestSize.Level0)
{
    // B4,B7,B9,B11 FALSE: values == -1 -> optionals stay nullopt
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW3", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { -1.0f, -1.0f, -1.0f, -1.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_FALSE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.rightDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.bottomDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.leftDimen.has_value());
}

/**
 * @tc.name: SetBorderWidthCommon005
 * @tc.desc: Test SetBorderWidthCommon with INVALID units (optionals not set)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon005, TestSize.Level0)
{
    // B5,B8,B10,B11 FALSE via INVALID unit: values valid but units == INVALID
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW4", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::INVALID) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_FALSE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.rightDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.bottomDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.leftDimen.has_value());
}

/**
 * @tc.name: SetBorderWidthCommon006
 * @tc.desc: Test SetBorderWidthCommon with mixed valid/invalid values
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon006, TestSize.Level0)
{
    // Mixed: top valid, right value=-1, bottom unit=INVALID, left valid
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW5", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, -1.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_TRUE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.topDimen.value().Value(), 1.0f);
    EXPECT_FALSE(g_lastBorderWidth.rightDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.bottomDimen.has_value());
    EXPECT_TRUE(g_lastBorderWidth.leftDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.leftDimen.value().Value(), 4.0f);
}

/**
 * @tc.name: ResetBorderWidthCommon001
 * @tc.desc: Test ResetBorderWidthCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderWidthCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ResetBorderWidthCommon(nullptr, MockSetBorderWidth);
    EXPECT_FALSE(g_borderWidthCalled);
}

/**
 * @tc.name: ResetBorderWidthCommon002
 * @tc.desc: Test ResetBorderWidthCommon with valid node (setFunc called with width 0)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, ResetBorderWidthCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with width 0
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW6", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_TRUE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.topDimen.value().Value(), 0.0);
}

/**
 * @tc.name: SetBorderColorCommon001
 * @tc.desc: Test SetBorderColorCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderColorCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUI_Uint32 colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
    SetBorderColorCommon(nullptr, colors, nullptr, MockSetBorderColor);
    EXPECT_FALSE(g_borderColorCalled);
}

/**
 * @tc.name: SetBorderColorCommon002
 * @tc.desc: Test SetBorderColorCommon with valid node (setFunc called with correct colors)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderColorCommon002, TestSize.Level0)
{
    // B2: valid node, ConfigChangePerform false -> setFunc called directly
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testC1", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Uint32 colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
    SetBorderColorCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        colors, nullptr, MockSetBorderColor);
    EXPECT_TRUE(g_borderColorCalled);
    EXPECT_EQ(g_lastBorderColors.topColor.value(), Color(0xFF0000));
    EXPECT_EQ(g_lastBorderColors.rightColor.value(), Color(0x00FF00));
    EXPECT_EQ(g_lastBorderColors.bottomColor.value(), Color(0x0000FF));
    EXPECT_EQ(g_lastBorderColors.leftColor.value(), Color(0xFFFF00));
}

/**
 * @tc.name: SetBorderStyleCommon001
 * @tc.desc: Test SetBorderStyleCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderStyleCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUI_Int32 styles[] = { 0, 1, 2, 3 };
    SetBorderStyleCommon(nullptr, styles, DEFAULT_LENGTH, MockSetBorderStyle);
    EXPECT_FALSE(g_borderStyleCalled);
}

/**
 * @tc.name: SetBorderStyleCommon002
 * @tc.desc: Test SetBorderStyleCommon with length == 1 (single style path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderStyleCommon002, TestSize.Level0)
{
    // B2: length == 1 -> single-style path, setFunc called + early return
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testS1", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Int32 styles[] = { static_cast<ArkUI_Int32>(BorderStyle::DASHED) };
    SetBorderStyleCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), styles, 1,
        MockSetBorderStyle);
    EXPECT_TRUE(g_borderStyleCalled);
    EXPECT_TRUE(g_lastBorderStyles.styleTop.has_value());
    EXPECT_EQ(g_lastBorderStyles.styleTop.value(), BorderStyle::DASHED);
    // single-style path sets all sides to same value
    EXPECT_EQ(g_lastBorderStyles.styleLeft.value(), BorderStyle::DASHED);
}

/**
 * @tc.name: SetBorderStyleCommon003
 * @tc.desc: Test SetBorderStyleCommon with length == 4 (multi style path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderStyleCommon003, TestSize.Level0)
{
    // B4: length == DEFAULT_LENGTH -> multi-style path, setFunc called
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testS2", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Int32 styles[] = { static_cast<ArkUI_Int32>(BorderStyle::SOLID),
        static_cast<ArkUI_Int32>(BorderStyle::DASHED),
        static_cast<ArkUI_Int32>(BorderStyle::DOTTED),
        static_cast<ArkUI_Int32>(BorderStyle::NONE) };
    SetBorderStyleCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), styles, DEFAULT_LENGTH,
        MockSetBorderStyle);
    EXPECT_TRUE(g_borderStyleCalled);
    EXPECT_TRUE(g_lastBorderStyles.styleTop.has_value());
    EXPECT_EQ(g_lastBorderStyles.styleTop.value(), BorderStyle::SOLID);
    EXPECT_EQ(g_lastBorderStyles.styleRight.value(), BorderStyle::DASHED);
    EXPECT_EQ(g_lastBorderStyles.styleBottom.value(), BorderStyle::DOTTED);
    EXPECT_EQ(g_lastBorderStyles.styleLeft.value(), BorderStyle::NONE);
}

/**
 * @tc.name: SetBorderStyleCommon004
 * @tc.desc: Test SetBorderStyleCommon with invalid length (2) (no setFunc called)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderStyleCommon004, TestSize.Level0)
{
    // B3+B5: length == 2 (not 1, not 4) -> no setFunc called
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testS3", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Int32 styles[] = { 0, 1 };
    SetBorderStyleCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), styles, 2,
        MockSetBorderStyle);
    EXPECT_FALSE(g_borderStyleCalled);
}

/**
 * @tc.name: SetBorderStyleCommon005
 * @tc.desc: Test SetBorderStyleCommon with invalid style in single path (resets to SOLID)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderStyleCommon005, TestSize.Level0)
{
    // ConvertBorderStyle B1: invalid style value -> default to SOLID
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testS4", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Int32 styles[] = { 99 }; // out-of-range
    SetBorderStyleCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), styles, 1,
        MockSetBorderStyle);
    EXPECT_TRUE(g_borderStyleCalled);
    EXPECT_EQ(g_lastBorderStyles.styleTop.value(), BorderStyle::SOLID);
}

/**
 * @tc.name: SetBorderRadiusCommon001
 * @tc.desc: Test SetBorderRadiusCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderRadiusCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUI_Float32 values[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderRadiusCommon(nullptr, values, units, DEFAULT_LENGTH, MockSetBorderRadius);
    EXPECT_FALSE(g_borderRadiusCalled);
}

/**
 * @tc.name: SetBorderRadiusCommon002
 * @tc.desc: Test SetBorderRadiusCommon with length != 4 (early return)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderRadiusCommon002, TestSize.Level0)
{
    // B2: length != DEFAULT_LENGTH -> early return
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testR1", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, 2.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderRadiusCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units, 2,
        MockSetBorderRadius);
    EXPECT_FALSE(g_borderRadiusCalled);
}

/**
 * @tc.name: SetBorderRadiusCommon003
 * @tc.desc: Test SetBorderRadiusCommon with valid length == 4 (setFunc called)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderRadiusCommon003, TestSize.Level0)
{
    // B3: length == DEFAULT_LENGTH -> setFunc called with correct radius values
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testR2", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 2.0f, 4.0f, 6.0f, 8.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderRadiusCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderRadius);
    EXPECT_TRUE(g_borderRadiusCalled);
    EXPECT_EQ(g_lastBorderRadius.radiusTopLeft.value().Value(), 2.0f);
    EXPECT_EQ(g_lastBorderRadius.radiusTopRight.value().Value(), 4.0f);
    EXPECT_EQ(g_lastBorderRadius.radiusBottomLeft.value().Value(), 6.0f);
    EXPECT_EQ(g_lastBorderRadius.radiusBottomRight.value().Value(), 8.0f);
}

/**
 * @tc.name: SetBorderColorCommon003
 * @tc.desc: Test SetBorderColorCommon with ConfigChangePerform=true, null res (objs.empty path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderColorCommon003, TestSize.Level0)
{
    // B3: ConfigChangePerform=true, res=null -> objs.empty -> CompleteResourceObjectFromColor
    ResetMockFlags();
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testCC1",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Uint32 colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
    SetBorderColorCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        colors, nullptr, MockSetBorderColor);
    EXPECT_TRUE(g_borderColorCalled);
    EXPECT_EQ(g_lastBorderColors.topColor.value(), Color(0xFF0000));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBorderColorCommon004
 * @tc.desc: Test SetBorderColorCommon with ConfigChangePerform=true, res non-null with objects
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderColorCommon004, TestSize.Level0)
{
    // B4: ConfigChangePerform=true, res non-null -> objs not empty -> ParseBorderColor with provided objs
    ResetMockFlags();
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testCC2",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    // Create a vector of ResourceObjects to pass as res
    auto topRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto rightRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto bottomRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto leftRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    std::vector<RefPtr<ResourceObject>> objs = { topRes, rightRes, bottomRes, leftRes };
    ArkUI_Uint32 colors[] = { 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00 };
    SetBorderColorCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        colors, &objs, MockSetBorderColor);
    EXPECT_TRUE(g_borderColorCalled);
    EXPECT_EQ(g_lastBorderColors.topColor.value(), Color(0xFF0000));
    // resMap_ should have 4 entries from ParseBorderColor
    EXPECT_EQ(g_lastBorderColors.resMap_.size(), 4u);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBorderWidthCommon007
 * @tc.desc: Test SetBorderWidthCommon with VP unit (non-PX valid unit)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon007, TestSize.Level0)
{
    // Branch: value != -1 and unit == VP -> Dimension with VP unit
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW7",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 5.0f, 10.0f, 15.0f, 20.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_TRUE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_EQ(g_lastBorderWidth.topDimen.value().Unit(), DimensionUnit::VP);
    EXPECT_EQ(g_lastBorderWidth.topDimen.value().Value(), 5.0f);
}

/**
 * @tc.name: SetBorderWidthCommon008
 * @tc.desc: Test SetBorderWidthCommon with value=-1 AND unit=INVALID (both conditions false)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderWidthCommon008, TestSize.Level0)
{
    // Both conditions false simultaneously: value == -1 and unit == INVALID
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testW8",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { -1.0f, 2.0f, -1.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::PX),
        static_cast<ArkUI_Int32>(DimensionUnit::INVALID),
        static_cast<ArkUI_Int32>(DimensionUnit::PX) };
    SetBorderWidthCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderWidth);
    EXPECT_TRUE(g_borderWidthCalled);
    EXPECT_FALSE(g_lastBorderWidth.topDimen.has_value());
    EXPECT_TRUE(g_lastBorderWidth.rightDimen.has_value());
    EXPECT_FALSE(g_lastBorderWidth.bottomDimen.has_value());
    EXPECT_TRUE(g_lastBorderWidth.leftDimen.has_value());
}

/**
 * @tc.name: SetBorderRadiusCommon004
 * @tc.desc: Test SetBorderRadiusCommon with VP units (non-PX valid unit)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBorderUtilsTestNg, SetBorderRadiusCommon004, TestSize.Level0)
{
    // Radius with VP units
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testR3",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[] = { 1.0f, 2.0f, 3.0f, 4.0f };
    ArkUI_Int32 units[] = { static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP),
        static_cast<ArkUI_Int32>(DimensionUnit::VP) };
    SetBorderRadiusCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), values, units,
        DEFAULT_LENGTH, MockSetBorderRadius);
    EXPECT_TRUE(g_borderRadiusCalled);
    EXPECT_EQ(g_lastBorderRadius.radiusTopLeft.value().Unit(), DimensionUnit::VP);
    EXPECT_EQ(g_lastBorderRadius.radiusTopLeft.value().Value(), 1.0f);
}

} // namespace OHOS::Ace
