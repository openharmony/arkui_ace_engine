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
#define protected public
#define private public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "core/animation/cubic_curve.h"
#include "core/common/ace_application_info.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_modifier.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "interfaces/inner_api/ui_session/param_config.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr bool IS_OFF = false;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
constexpr float POINT_RADIUS = 30.0f;
// GetSwitchWidth() returns content width minus content height.
constexpr float SWITCH_TRAVEL = SWITCH_WIDTH - SWITCH_HEIGHT;
// Default animation duration returned by GetDuration() when none is set.
constexpr int32_t DEFAULT_ANIM_DURATION = 200;
constexpr int32_t CUSTOM_ANIM_DURATION = 500;
constexpr float CONTENT_OFFSET_X = 15.0f;
constexpr float CONTENT_OFFSET_Y = 25.0f;
constexpr float NEGATIVE_OFFSET = -5.0f; // less than zero, out of boundary
constexpr float ZERO_OFFSET = 0.0f;      // left boundary, still in boundary
constexpr float IN_RANGE_OFFSET = 40.0f; // within [0, SWITCH_TRAVEL]
constexpr float EXCEED_OFFSET = 60.0f;   // greater than SWITCH_TRAVEL, out of boundary
constexpr float CUBIC_X0 = 0.0f;
constexpr float CUBIC_Y0 = 0.0f;
constexpr float CUBIC_X1 = 0.0f;
constexpr float CUBIC_Y1 = 1.0f;

// Paint property test colors and dimensions.
const Color TEST_SELECTED_COLOR = Color(0xFF0000FF);   // blue
const Color TEST_POINT_COLOR = Color(0xFF00FF00);      // green
const Color TEST_UNSELECTED_COLOR = Color(0xFFFF0000); // red
constexpr double TEST_POINT_RADIUS_VP = 12.0;
constexpr double TEST_TRACK_RADIUS_VP = 8.0;

// Layout algorithm ratio-driven sizing constants.
// SwitchTheme::ratio_ is a const default of 1.8f, so expected sizes are derived from it.
constexpr float DEFAULT_RATIO = 1.8f;
constexpr float LAYOUT_FRAME_HEIGHT = 50.0f;
constexpr float LAYOUT_FRAME_WIDTH_NARROW = 50.0f;  // smaller than height * ratio
constexpr float LAYOUT_FRAME_WIDTH_WIDE = 200.0f;   // larger than height * ratio
constexpr float LAYOUT_FRAME_WIDTH_EQUAL = LAYOUT_FRAME_HEIGHT * DEFAULT_RATIO; // 90
constexpr float EXPECTED_NARROW_HEIGHT = LAYOUT_FRAME_WIDTH_NARROW / DEFAULT_RATIO;
constexpr float EXPECTED_WIDE_WIDTH = LAYOUT_FRAME_HEIGHT * DEFAULT_RATIO;

// SwitchModifier value constants.
constexpr float MODIFIER_TRACK_RADIUS = 18.0f;
constexpr int32_t DEFAULT_BUILDER_ID = -1;
} // namespace

class ToggleSwitchPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateSwitchNode(bool isOn);
    static RefPtr<SwitchPattern> GetPattern(const RefPtr<FrameNode>& node);
    static RefPtr<SwitchTheme> SetupThemeManager();
    static RefPtr<SwitchModifier> GetSwitchModifier(const RefPtr<FrameNode>& node);
};

void ToggleSwitchPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ToggleSwitchPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> ToggleSwitchPatternTestNg::CreateSwitchNode(bool isOn)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, isOn);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    if (switchFrameNode) {
        switchFrameNode->MarkModifyDone();
    }
    return switchFrameNode;
}

RefPtr<SwitchPattern> ToggleSwitchPatternTestNg::GetPattern(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return AceType::DynamicCast<SwitchPattern>(node->GetPattern());
}

RefPtr<SwitchTheme> ToggleSwitchPatternTestNg::SetupThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = Dimension(SWITCH_WIDTH);
    switchTheme->height_ = Dimension(SWITCH_HEIGHT);
    switchTheme->hotZoneHorizontalPadding_ = Dimension(0.0);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));
    return switchTheme;
}

RefPtr<SwitchModifier> ToggleSwitchPatternTestNg::GetSwitchModifier(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto pattern = GetPattern(node);
    CHECK_NULL_RETURN(pattern, nullptr);
    SetupThemeManager();
    pattern->paintMethod_ = AceType::MakeRefPtr<SwitchPaintMethod>();
    auto renderContext = node->GetRenderContext();
    auto geometryNode = node->GetGeometryNode();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto modifier = pattern->paintMethod_->GetContentModifier(paintWrapper);
    return AceType::DynamicCast<SwitchModifier>(modifier);
}

// ============================================================
// GetDuration tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_GetDuration_Default
 * @tc.desc: Test GetDuration returns the default duration when no animation duration is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetDuration_Default, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // No animation duration configured, the default value should be returned.
    EXPECT_EQ(pattern->GetDuration(), DEFAULT_ANIM_DURATION);
}

/**
 * @tc.name: SwitchPatternTest_GetDuration_Custom
 * @tc.desc: Test GetDuration returns the user-configured duration when it is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetDuration_Custom, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateDuration(CUSTOM_ANIM_DURATION);
    EXPECT_EQ(pattern->GetDuration(), CUSTOM_ANIM_DURATION);
}

// ============================================================
// GetCurve tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_GetCurve_NotSet
 * @tc.desc: Test GetCurve returns nullptr when no animation curve is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetCurve_NotSet, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // No curve configured, GetCurve should fall back to nullptr.
    EXPECT_EQ(pattern->GetCurve(), nullptr);
}

/**
 * @tc.name: SwitchPatternTest_GetCurve_Set
 * @tc.desc: Test GetCurve returns the user-configured curve when it is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetCurve_Set, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    RefPtr<Curve> expectedCurve = AceType::MakeRefPtr<CubicCurve>(CUBIC_X0, CUBIC_Y0, CUBIC_X1, CUBIC_Y1);
    paintProperty->UpdateCurve(expectedCurve);
    EXPECT_EQ(pattern->GetCurve(), expectedCurve);
}

// ============================================================
// GetSwitchWidth / GetSwitchContentOffsetX tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_GetSwitchWidth
 * @tc.desc: Test GetSwitchWidth returns content width minus content height.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetSwitchWidth, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    // The travel distance of the knob equals content width minus content height.
    EXPECT_FLOAT_EQ(pattern->GetSwitchWidth(), SWITCH_TRAVEL);
}

/**
 * @tc.name: SwitchPatternTest_GetSwitchContentOffsetX
 * @tc.desc: Test GetSwitchContentOffsetX returns the content offset X coordinate.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetSwitchContentOffsetX, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_X, CONTENT_OFFSET_Y));
    EXPECT_FLOAT_EQ(pattern->GetSwitchContentOffsetX(), CONTENT_OFFSET_X);
}

// ============================================================
// IsOutOfBoundary tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_IsOutOfBoundary_Negative
 * @tc.desc: Test IsOutOfBoundary returns true when the offset is negative.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_IsOutOfBoundary_Negative, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    // A negative offset is always out of boundary.
    EXPECT_TRUE(pattern->IsOutOfBoundary(NEGATIVE_OFFSET));
}

/**
 * @tc.name: SwitchPatternTest_IsOutOfBoundary_ExceedsWidth
 * @tc.desc: Test IsOutOfBoundary returns true when the offset exceeds the switch width.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_IsOutOfBoundary_ExceedsWidth, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    // An offset greater than the switch travel is out of boundary.
    EXPECT_TRUE(pattern->IsOutOfBoundary(EXCEED_OFFSET));
}

/**
 * @tc.name: SwitchPatternTest_IsOutOfBoundary_InRange
 * @tc.desc: Test IsOutOfBoundary returns false when the offset is within the valid range,
 *           including the left (zero) and right (equals travel) boundaries.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_IsOutOfBoundary_InRange, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = switchNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    // Offsets within [0, travel] (boundaries included) are not out of boundary.
    EXPECT_FALSE(pattern->IsOutOfBoundary(ZERO_OFFSET));
    EXPECT_FALSE(pattern->IsOutOfBoundary(IN_RANGE_OFFSET));
    // Equals the travel distance: the check uses a strict greater-than, so it stays in range.
    EXPECT_FALSE(pattern->IsOutOfBoundary(SWITCH_TRAVEL));
}

// ============================================================
// DumpSimplifyInfoOnlyForParamConfig tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_DumpSimplify_WithInteractionInfo
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig writes the isOn value when interactionInfo is enabled.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_DumpSimplify_WithInteractionInfo, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_ON);

    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.interactionInfo = true;
    pattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    EXPECT_EQ(json->GetValue("isOn")->GetString(), "true");
}

/**
 * @tc.name: SwitchPatternTest_DumpSimplify_WithoutInteractionInfo
 * @tc.desc: Test DumpSimplifyInfoOnlyForParamConfig skips writing isOn when interactionInfo is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_DumpSimplify_WithoutInteractionInfo, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_ON);

    std::shared_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    ParamConfig config;
    config.interactionInfo = false;
    pattern->DumpSimplifyInfoOnlyForParamConfig(json, config);
    // isOn should not be written when interactionInfo is disabled.
    EXPECT_EQ(json->ToString(), "{}");
}

// ============================================================
// MarkIsSelected tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_MarkIsSelected_DifferentState
 * @tc.desc: Test MarkIsSelected flips the checked state when the target differs from the current state.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_MarkIsSelected_DifferentState, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_OFF);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // Created as off, so the current checked state is false.
    EXPECT_FALSE(pattern->IsChecked());
    // Selecting when currently off should flip the checked state to on.
    pattern->MarkIsSelected(IS_ON);
    EXPECT_TRUE(pattern->IsChecked());
}

// ============================================================
// SwitchPattern capability / simple getter tests
// ============================================================

/**
 * @tc.name: SwitchPatternTest_IsEnableMatchParent
 * @tc.desc: Test IsEnableMatchParent returns true so the switch can match its parent in layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_IsEnableMatchParent, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: SwitchPatternTest_IsEnableFix
 * @tc.desc: Test IsEnableFix returns true so the switch supports fix-sized layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_IsEnableFix, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsEnableFix());
}

/**
 * @tc.name: SwitchPatternTest_UseContentModifier_DefaultFalse
 * @tc.desc: Test UseContentModifier returns false when no content modifier builder is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_UseContentModifier_DefaultFalse, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // Without a builder callback, no content modifier node is built.
    EXPECT_FALSE(pattern->UseContentModifier());
}

/**
 * @tc.name: SwitchPatternTest_GetBuilderId_Default
 * @tc.desc: Test GetBuilderId returns the default invalid id when no builder node is attached.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_GetBuilderId_Default, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // No content modifier node has been built, so the builder id stays at its default.
    EXPECT_EQ(pattern->GetBuilderId(), DEFAULT_BUILDER_ID);
}

/**
 * @tc.name: SwitchPatternTest_SetShowHoverEffect
 * @tc.desc: Test SetShowHoverEffect updates the hover effect flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_SetShowHoverEffect, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // Default hover effect is enabled.
    EXPECT_TRUE(pattern->showHoverEffect_);
    pattern->SetShowHoverEffect(IS_OFF);
    EXPECT_FALSE(pattern->showHoverEffect_);
}

/**
 * @tc.name: SwitchPatternTest_SetIsUserSetResponseRegion
 * @tc.desc: Test SetIsUserSetResponseRegion updates the user-set response region flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_SetIsUserSetResponseRegion, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // By default the response region is not user-configured.
    EXPECT_FALSE(pattern->isUserSetResponseRegion_);
    pattern->SetIsUserSetResponseRegion(IS_ON);
    EXPECT_TRUE(pattern->isUserSetResponseRegion_);
}

/**
 * @tc.name: SwitchPatternTest_SetIsUserSetMargin
 * @tc.desc: Test SetIsUserSetMargin updates the user-set margin flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPatternTest_SetIsUserSetMargin, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    // By default the margin is not user-configured.
    EXPECT_FALSE(pattern->isUserSetMargin_);
    pattern->SetIsUserSetMargin(IS_ON);
    EXPECT_TRUE(pattern->isUserSetMargin_);
}

// ============================================================
// SwitchPaintProperty::Clone tests
// ============================================================

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesIsOn
 * @tc.desc: Test Clone preserves the IsOn value of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesIsOn, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_OFF);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_ON);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(cloned->GetIsOnValue(IS_OFF));
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesSelectedColor
 * @tc.desc: Test Clone preserves the SelectedColor of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesSelectedColor, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedColor(TEST_SELECTED_COLOR);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasSelectedColor());
    EXPECT_EQ(cloned->GetSelectedColor().value(), TEST_SELECTED_COLOR);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesSwitchPointColor
 * @tc.desc: Test Clone preserves the SwitchPointColor of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesSwitchPointColor, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSwitchPointColor(TEST_POINT_COLOR);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasSwitchPointColor());
    EXPECT_EQ(cloned->GetSwitchPointColor().value(), TEST_POINT_COLOR);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesUnselectedColor
 * @tc.desc: Test Clone preserves the UnselectedColor of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesUnselectedColor, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateUnselectedColor(TEST_UNSELECTED_COLOR);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasUnselectedColor());
    EXPECT_EQ(cloned->GetUnselectedColor().value(), TEST_UNSELECTED_COLOR);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesPointRadius
 * @tc.desc: Test Clone preserves the PointRadius of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesPointRadius, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    Dimension radius(TEST_POINT_RADIUS_VP);
    paintProperty->UpdatePointRadius(radius);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasPointRadius());
    EXPECT_EQ(cloned->GetPointRadius().value(), radius);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesTrackBorderRadius
 * @tc.desc: Test Clone preserves the TrackBorderRadius of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesTrackBorderRadius, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    Dimension radius(TEST_TRACK_RADIUS_VP);
    paintProperty->UpdateTrackBorderRadius(radius);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasTrackBorderRadius());
    EXPECT_EQ(cloned->GetTrackBorderRadius().value(), radius);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesDuration
 * @tc.desc: Test Clone preserves the animation Duration of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesDuration, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateDuration(CUSTOM_ANIM_DURATION);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasDuration());
    EXPECT_EQ(cloned->GetDuration().value(), CUSTOM_ANIM_DURATION);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_PreservesCurve
 * @tc.desc: Test Clone preserves the animation Curve of the source paint property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_PreservesCurve, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    RefPtr<Curve> expectedCurve = AceType::MakeRefPtr<CubicCurve>(CUBIC_X0, CUBIC_Y0, CUBIC_X1, CUBIC_Y1);
    paintProperty->UpdateCurve(expectedCurve);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->HasCurve());
    EXPECT_EQ(cloned->GetCurve().value(), expectedCurve);
}

/**
 * @tc.name: SwitchPaintProperty_Clone_Independent
 * @tc.desc: Test the cloned paint property does not change when the source is modified after cloning.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Clone_Independent, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_OFF);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_ON);
    auto cloned = AceType::DynamicCast<SwitchPaintProperty>(paintProperty->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(cloned->GetIsOnValue(IS_OFF));
    // Mutate the source after cloning; the clone must keep the value captured at clone time.
    paintProperty->UpdateIsOn(IS_OFF);
    EXPECT_TRUE(cloned->GetIsOnValue(IS_OFF));
}

// ============================================================
// SwitchPaintProperty::Reset tests
// ============================================================

/**
 * @tc.name: SwitchPaintProperty_Reset_ClearsIsOn
 * @tc.desc: Test Reset clears the IsOn flag so HasIsOn becomes false.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Reset_ClearsIsOn, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    ASSERT_TRUE(paintProperty->HasIsOn());
    paintProperty->Reset();
    EXPECT_FALSE(paintProperty->HasIsOn());
}

/**
 * @tc.name: SwitchPaintProperty_Reset_ClearsParagraphProperties
 * @tc.desc: Test Reset clears color and dimension paragraph properties.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_Reset_ClearsParagraphProperties, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateSelectedColor(TEST_SELECTED_COLOR);
    paintProperty->UpdateSwitchPointColor(TEST_POINT_COLOR);
    paintProperty->UpdatePointRadius(Dimension(TEST_POINT_RADIUS_VP));
    paintProperty->UpdateTrackBorderRadius(Dimension(TEST_TRACK_RADIUS_VP));
    paintProperty->Reset();
    EXPECT_FALSE(paintProperty->HasSelectedColor());
    EXPECT_FALSE(paintProperty->HasSwitchPointColor());
    EXPECT_FALSE(paintProperty->HasPointRadius());
    EXPECT_FALSE(paintProperty->HasTrackBorderRadius());
}

// ============================================================
// SwitchPaintProperty::ToJsonValue tests
// ============================================================

/**
 * @tc.name: SwitchPaintProperty_ToJsonValue_IsOnTrue
 * @tc.desc: Test ToJsonValue serializes isOn as "true" and emits the toggle type.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_ToJsonValue_IsOnTrue, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_ON);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("isOn")->GetString(), "true");
    EXPECT_EQ(json->GetValue("type")->GetString(), "ToggleType.Switch");
}

/**
 * @tc.name: SwitchPaintProperty_ToJsonValue_IsOnFalse
 * @tc.desc: Test ToJsonValue serializes isOn as "false" when the switch is off.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_ToJsonValue_IsOnFalse, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_OFF);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(IS_OFF);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("isOn")->GetString(), "false");
}

/**
 * @tc.name: SwitchPaintProperty_ToJsonValue_PointRadiusSet
 * @tc.desc: Test ToJsonValue emits the user-configured pointRadius when it is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_ToJsonValue_PointRadiusSet, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    Dimension radius(TEST_POINT_RADIUS_VP);
    paintProperty->UpdatePointRadius(radius);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
    // The serialized value should match the configured radius exactly.
    EXPECT_EQ(json->GetValue("pointRadius")->GetString(), radius.ToString());
}

/**
 * @tc.name: SwitchPaintProperty_ToJsonValue_PointRadiusDefault
 * @tc.desc: Test ToJsonValue emits a default pointRadius derived from the theme when none is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_ToJsonValue_PointRadiusDefault, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    // CreateSwitchNode configures a point radius; clear it so the default-radius branch is exercised.
    paintProperty->ResetPointRadius();
    ASSERT_FALSE(paintProperty->HasPointRadius());

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
    // When pointRadius is not set, a default value is still emitted.
    auto serialized = json->ToString();
    EXPECT_NE(serialized.find("pointRadius"), std::string::npos);
}

/**
 * @tc.name: SwitchPaintProperty_ToJsonValue_TrackBorderRadiusSet
 * @tc.desc: Test ToJsonValue emits the user-configured trackBorderRadius when it is set.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchPaintProperty_ToJsonValue_TrackBorderRadiusSet, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto pattern = GetPattern(switchNode);
    ASSERT_NE(pattern, nullptr);
    SetupThemeManager();
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    Dimension radius(TEST_TRACK_RADIUS_VP);
    paintProperty->UpdateTrackBorderRadius(radius);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("trackBorderRadius")->GetString(), radius.ToString());
}

// ============================================================
// SwitchLayoutAlgorithm::CalcHeightAndWidth tests
// ============================================================

/**
 * @tc.name: SwitchLayoutTest_CalcHeightAndWidth_ApiTwelvePassthrough
 * @tc.desc: Test CalcHeightAndWidth returns the ideal size directly on API twelve and above.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchLayoutTest_CalcHeightAndWidth_ApiTwelvePassthrough, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    SetupThemeManager();

    SwitchLayoutAlgorithm algorithm;
    float height = 0.0f;
    float width = 0.0f;
    // On API twelve and above the ideal frame size is used without ratio adjustment.
    algorithm.CalcHeightAndWidth(
        switchNode, height, width, LAYOUT_FRAME_HEIGHT, LAYOUT_FRAME_WIDTH_WIDE);
    EXPECT_FLOAT_EQ(width, LAYOUT_FRAME_WIDTH_WIDE);
    EXPECT_FLOAT_EQ(height, LAYOUT_FRAME_HEIGHT);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: SwitchLayoutTest_CalcHeightAndWidth_NarrowBranch
 * @tc.desc: Test CalcHeightAndWidth shrinks height by the ratio when width is smaller than height * ratio.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchLayoutTest_CalcHeightAndWidth_NarrowBranch, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    // SetupThemeManager provides a SwitchTheme whose ratio_ keeps its const default.
    SetupThemeManager();

    SwitchLayoutAlgorithm algorithm;
    float height = 0.0f;
    float width = 0.0f;
    // Narrow frame: keep width, derive height as width / ratio.
    algorithm.CalcHeightAndWidth(switchNode, height, width, LAYOUT_FRAME_HEIGHT, LAYOUT_FRAME_WIDTH_NARROW);
    EXPECT_FLOAT_EQ(width, LAYOUT_FRAME_WIDTH_NARROW);
    EXPECT_FLOAT_EQ(height, EXPECTED_NARROW_HEIGHT);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: SwitchLayoutTest_CalcHeightAndWidth_WideBranch
 * @tc.desc: Test CalcHeightAndWidth derives width from height by the ratio when width is larger than height * ratio.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchLayoutTest_CalcHeightAndWidth_WideBranch, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    // SetupThemeManager provides a SwitchTheme whose ratio_ keeps its const default.
    SetupThemeManager();

    SwitchLayoutAlgorithm algorithm;
    float height = 0.0f;
    float width = 0.0f;
    // Wide frame: keep height, derive width as height * ratio.
    algorithm.CalcHeightAndWidth(switchNode, height, width, LAYOUT_FRAME_HEIGHT, LAYOUT_FRAME_WIDTH_WIDE);
    EXPECT_FLOAT_EQ(height, LAYOUT_FRAME_HEIGHT);
    EXPECT_FLOAT_EQ(width, EXPECTED_WIDE_WIDTH);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: SwitchLayoutTest_CalcHeightAndWidth_EqualBranch
 * @tc.desc: Test CalcHeightAndWidth keeps both dimensions when width equals height * ratio.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchLayoutTest_CalcHeightAndWidth_EqualBranch, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    // SetupThemeManager provides a SwitchTheme whose ratio_ keeps its const default.
    SetupThemeManager();

    SwitchLayoutAlgorithm algorithm;
    float height = 0.0f;
    float width = 0.0f;
    // Balanced frame: both dimensions are kept as provided.
    algorithm.CalcHeightAndWidth(switchNode, height, width, LAYOUT_FRAME_HEIGHT, LAYOUT_FRAME_WIDTH_EQUAL);
    EXPECT_FLOAT_EQ(width, LAYOUT_FRAME_WIDTH_EQUAL);
    EXPECT_FLOAT_EQ(height, LAYOUT_FRAME_HEIGHT);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

// ============================================================
// SwitchModifier getter/setter tests
// ============================================================

/**
 * @tc.name: SwitchModifierTest_SetActualTrackRadius_GetTrackRadius
 * @tc.desc: Test SetActualTrackRadius updates the value returned by GetTrackRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchModifierTest_SetActualTrackRadius_GetTrackRadius, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto modifier = GetSwitchModifier(switchNode);
    ASSERT_NE(modifier, nullptr);
    modifier->SetActualTrackRadius(MODIFIER_TRACK_RADIUS);
    EXPECT_FLOAT_EQ(modifier->GetTrackRadius(), MODIFIER_TRACK_RADIUS);
}

/**
 * @tc.name: SwitchModifierTest_SetHasSystemMaterial_GetHasSystemMaterial
 * @tc.desc: Test SetHasSystemMaterial toggles the value returned by GetHasSystemMaterial.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchModifierTest_SetHasSystemMaterial_GetHasSystemMaterial, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto modifier = GetSwitchModifier(switchNode);
    ASSERT_NE(modifier, nullptr);
    EXPECT_FALSE(modifier->GetHasSystemMaterial());
    modifier->SetHasSystemMaterial(IS_ON);
    EXPECT_TRUE(modifier->GetHasSystemMaterial());
}

/**
 * @tc.name: SwitchModifierTest_SetShowHoverEffect
 * @tc.desc: Test SetShowHoverEffect updates the internal hover effect flag.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchPatternTestNg, SwitchModifierTest_SetShowHoverEffect, TestSize.Level1)
{
    auto switchNode = CreateSwitchNode(IS_ON);
    ASSERT_NE(switchNode, nullptr);
    auto modifier = GetSwitchModifier(switchNode);
    ASSERT_NE(modifier, nullptr);
    // Default hover effect is enabled.
    EXPECT_TRUE(modifier->showHoverEffect_);
    modifier->SetShowHoverEffect(IS_OFF);
    EXPECT_FALSE(modifier->showHoverEffect_);
}
} // namespace OHOS::Ace::NG
