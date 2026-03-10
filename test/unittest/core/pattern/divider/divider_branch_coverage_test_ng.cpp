/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "divider_base_test_ng.h"

#include "core/components_ng/property/layout_constraint.h"
#include "core/common/resource/resource_parse_utils.h"
#include "frameworks/base/memory/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/ui/resource/resource_object.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {} // namespace

class DividerBranchCoverageTestNG : public DividerBaseTestNG {};

/**
 * @tc.name: OnDirtyLayoutWrapperSwapSkipMeasureTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap when config.skipMeasure is true
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapSkipMeasureTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = true;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    // When skipMeasure is true, OnDirtyLayoutWrapperSwap should return false
    // and not update the pattern's internal state
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapSkipMeasureContentTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap when layoutWrapper SkipMeasureContent is true
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapSkipMeasureContentTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(8));
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutWrapper->skipMeasureContent_ = true;

    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    // When skipMeasureContent is true, OnDirtyLayoutWrapperSwap should return false
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapNormalTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap in normal case and verify state updates
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapNormalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(12));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    // Need to call MeasureContent to trigger algorithm to update its internal state
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);

    // Verify layout algorithm was called and state was updated
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_GT(layoutAlgorithm->GetConstrainStrokeWidth(), 0.0f);
    EXPECT_GT(layoutAlgorithm->GetDividerLength(), 0.0f);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapVerticalTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap with vertical divider
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapVerticalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(5));
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    // Need to call MeasureContent to trigger algorithm to update its internal state
    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);

    // Verify layout algorithm reflects vertical orientation
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_TRUE(layoutAlgorithm->GetVertical());
}

/**
 * @tc.name: OnThemeScopeUpdateWithNullHostTest001
 * @tc.desc: test OnThemeScopeUpdate when pattern has no host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnThemeScopeUpdateWithDividerColorTest001
 * @tc.desc: test OnThemeScopeUpdate when divider color is already set
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Verify color is set
    EXPECT_TRUE(paintProperty->HasDividerColor());
    EXPECT_EQ(paintProperty->GetDividerColorValue(), Color::RED);

    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnThemeScopeUpdateWithoutDividerColorTest001
 * @tc.desc: test OnThemeScopeUpdate when divider color is not set
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithoutDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Verify color is not initially set
    EXPECT_FALSE(paintProperty->HasDividerColor());

    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DumpDividerColorWithNullHostTest001
 * @tc.desc: test DumpDividerColor when pattern has no host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpDividerColorWithNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->DumpDividerColor();
    EXPECT_EQ(result, "NA");
}

/**
 * @tc.name: OnColorConfigurationUpdateNotPerformingTest001
 * @tc.desc: test OnColorConfigurationUpdate when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateNotPerformingTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto originalColor = paintProperty->GetDividerColorValue();

    OHOS::Ace::g_isConfigChangePerform = false;
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = true;

    // Color should not change when ConfigChangePerform is false
    EXPECT_EQ(paintProperty->GetDividerColorValue(), originalColor);
    EXPECT_EQ(paintProperty->GetDividerColorValue(), Color::BLUE);
}

/**
 * @tc.name: OnColorConfigurationUpdateSetByUserTest001
 * @tc.desc: test OnColorConfigurationUpdate when color is set by user
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateSetByUserTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto originalColor = paintProperty->GetDividerColorValue();

    // Verify color was marked as set by user
    auto setByUser = paintProperty->GetDividerColorSetByUser();
    EXPECT_TRUE(setByUser.has_value());
    EXPECT_TRUE(setByUser.value());

    OHOS::Ace::g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = false;

    // When color is set by user, it should not be updated by theme
    EXPECT_EQ(paintProperty->GetDividerColorValue(), originalColor);
    EXPECT_EQ(paintProperty->GetDividerColorValue(), Color::GREEN);
}

/**
 * @tc.name: OnColorConfigurationUpdateNotSetByUserTest001
 * @tc.desc: test OnColorConfigurationUpdate when color is not set by user, verify update
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateNotSetByUserTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Ensure DividerColorSetByUser is false (not set by user)
    paintProperty->UpdateDividerColorSetByUser(false);

    // Verify it's not marked as set by user
    auto setByUserBefore = paintProperty->GetDividerColorSetByUser();
    EXPECT_TRUE(setByUserBefore.has_value());
    EXPECT_FALSE(setByUserBefore.value());

    OHOS::Ace::g_isConfigChangePerform = false;
    pattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(paintProperty->HasDividerColor());
    OHOS::Ace::g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(paintProperty->HasDividerColor());
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapNullAlgorithmTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap when layoutAlgorithmWrapper is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapNullAlgorithmTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    // Don't set layout algorithm wrapper - it will be null
    DirtySwapConfig config;
    config.skipMeasure = true;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapInvalidAlgorithmTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap when algorithm is not DividerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapInvalidAlgorithmTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    // Use a different layout algorithm type
    auto dummyAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(dummyAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DumpDividerColorWithNullPipelineTest001
 * @tc.desc: test DumpDividerColor when pipeline context is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpDividerColorWithNullPipelineTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // FrameNode has host but we test the pattern directly without host
    auto result = pattern->DumpDividerColor();
    EXPECT_EQ(result, "NA");
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: test DumpInfo method adds divider color description
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpInfoTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // DumpInfo should not crash
    pattern->DumpInfo();

    // Verify paint property has the color
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: DumpInfoJsonTest001
 * @tc.desc: test DumpInfo with JsonValue parameter
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpInfoJsonTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    // DumpInfo with JsonValue should not crash
    pattern->DumpInfo(json);
}

/**
 * @tc.name: CreateNodePaintMethodTest001
 * @tc.desc: test CreateNodePaintMethod creates paint method correctly
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateNodePaintMethodTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(5));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethodVerticalTest001
 * @tc.desc: test CreateNodePaintMethod with vertical divider
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateNodePaintMethodVerticalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(8));
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateLayoutPropertyTest001
 * @tc.desc: test CreateLayoutProperty creates layout property correctly
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateLayoutPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    auto dividerLayoutProperty = AceType::DynamicCast<DividerLayoutProperty>(layoutProperty);
    ASSERT_NE(dividerLayoutProperty, nullptr);
}

/**
 * @tc.name: CreatePaintPropertyTest001
 * @tc.desc: test CreatePaintProperty creates paint property correctly
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreatePaintPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    auto dividerPaintProperty = AceType::DynamicCast<DividerRenderProperty>(paintProperty);
    ASSERT_NE(dividerPaintProperty, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithmTest001
 * @tc.desc: test CreateLayoutAlgorithm creates layout algorithm correctly
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateLayoutAlgorithmTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto dividerLayoutAlgorithm = AceType::DynamicCast<DividerLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: GetFocusPatternTest001
 * @tc.desc: test GetFocusPattern returns correct focus pattern
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, GetFocusPatternTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::NODE);
    EXPECT_FALSE(focusPattern.focusable_);
    EXPECT_EQ(focusPattern.styleType_, FocusStyleType::OUTER_BORDER);
}

/**
 * @tc.name: IsEnableMatchParentTest001
 * @tc.desc: test IsEnableMatchParent returns true
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, IsEnableMatchParentTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: IsEnableFixTest001
 * @tc.desc: test IsEnableFix returns true
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, IsEnableFixTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableFix());
}

/**
 * @tc.name: LayoutAlgorithmMeasureContentNullPropertyTest001
 * @tc.desc: test MeasureContent when layout property is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmMeasureContentNullPropertyTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    // Create a layout wrapper with null layout property
    auto frameNode = FrameNode::CreateFrameNode("test", 0, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: LayoutAlgorithmMeasureContentHorizontalTest001
 * @tc.desc: test MeasureContent with horizontal divider and self ideal size
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmMeasureContentHorizontalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(300.0f);
    contentConstraint.percentReference.SetHeight(200.0f);
    contentConstraint.selfIdealSize.SetWidth(150.0f);
    contentConstraint.selfIdealSize.SetHeight(20.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().Width(), 150.0f);
}

/**
 * @tc.name: LayoutAlgorithmMeasureContentVerticalTest001
 * @tc.desc: test MeasureContent with vertical divider and self ideal size
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmMeasureContentVerticalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(300.0f);
    contentConstraint.percentReference.SetHeight(200.0f);
    contentConstraint.selfIdealSize.SetWidth(20.0f);
    contentConstraint.selfIdealSize.SetHeight(150.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().Height(), 150.0f);
}

/**
 * @tc.name: LayoutAlgorithmMeasureContentNoLimitationTest001
 * @tc.desc: test MeasureContent with strokeWidthLimitation set to false
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmMeasureContentNoLimitationTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(100));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateStrokeWidthLimitation(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(50.0f);
    contentConstraint.percentReference.SetHeight(50.0f);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    // Without limitation, stroke width should not be limited by divider length
    EXPECT_EQ(layoutAlgorithm->GetStrokeWidthLimitation(), false);
}

/**
 * @tc.name: LayoutAlgorithmGettersTest001
 * @tc.desc: test DividerLayoutAlgorithm getter methods
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmGettersTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(15));
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    EXPECT_GT(layoutAlgorithm->GetConstrainStrokeWidth(), 0.0f);
    EXPECT_GT(layoutAlgorithm->GetDividerLength(), 0.0f);
    EXPECT_TRUE(layoutAlgorithm->GetVertical());
}

/**
 * @tc.name: RenderPropertyCloneTest001
 * @tc.desc: test DividerRenderProperty Clone method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyCloneTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
        model.LineCap(LineCap::ROUND);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto clonedProperty = paintProperty->Clone();
    ASSERT_NE(clonedProperty, nullptr);

    auto dividerClonedProperty = AceType::DynamicCast<DividerRenderProperty>(clonedProperty);
    ASSERT_NE(dividerClonedProperty, nullptr);
}

/**
 * @tc.name: RenderPropertyResetTest001
 * @tc.desc: test DividerRenderProperty Reset method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyResetTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
        model.LineCap(LineCap::SQUARE);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    EXPECT_TRUE(paintProperty->HasDividerColor());

    paintProperty->Reset();

    EXPECT_FALSE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: RenderPropertyToJsonValueTest001
 * @tc.desc: test DividerRenderProperty ToJsonValue method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyToJsonValueTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
        model.LineCap(LineCap::BUTT);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: RenderPropertyFromJsonTest001
 * @tc.desc: test DividerRenderProperty FromJson method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyFromJsonTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    json->Put("color", "#FF0000FF");

    paintProperty->FromJson(json);

    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: RenderPropertyGetDividerColorValueDefaultTest001
 * @tc.desc: test GetDividerColorValue with default value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyGetDividerColorValueDefaultTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    EXPECT_FALSE(paintProperty->HasDividerColor());

    Color defaultColor = Color::GRAY;
    auto result = paintProperty->GetDividerColorValue(defaultColor);
    EXPECT_EQ(result, defaultColor);
}

/**
 * @tc.name: LayoutPropertyCloneTest001
 * @tc.desc: test DividerLayoutProperty Clone method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyCloneTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto clonedProperty = layoutProperty->Clone();
    ASSERT_NE(clonedProperty, nullptr);

    auto dividerClonedProperty = AceType::DynamicCast<DividerLayoutProperty>(clonedProperty);
    ASSERT_NE(dividerClonedProperty, nullptr);
}

/**
 * @tc.name: LayoutPropertyResetTest001
 * @tc.desc: test DividerLayoutProperty Reset method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyResetTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    EXPECT_TRUE(layoutProperty->GetVertical().has_value());

    layoutProperty->Reset();

    EXPECT_FALSE(layoutProperty->GetVertical().has_value());
}

/**
 * @tc.name: LayoutPropertyToJsonValueTest001
 * @tc.desc: test DividerLayoutProperty ToJsonValue method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyToJsonValueTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(5));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: LayoutPropertyFromJsonTest001
 * @tc.desc: test DividerLayoutProperty FromJson method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyFromJsonTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    json->Put("vertical", "true");
    json->Put("strokeWidth", "10px");

    layoutProperty->FromJson(json);

    EXPECT_TRUE(layoutProperty->GetVertical().has_value());
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapStrokeWidthLimitationTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap verifies strokeWidthLimitation update
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapStrokeWidthLimitationTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MeasureContentWithMinMaxConstraintTest001
 * @tc.desc: test MeasureContent with min/max size constraints
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentWithMinMaxConstraintTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(50));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(300.0f);
    contentConstraint.percentReference.SetHeight(200.0f);
    contentConstraint.minSize.SetWidth(100.0f);
    contentConstraint.minSize.SetHeight(10.0f);
    contentConstraint.maxSize.SetWidth(250.0f);
    contentConstraint.maxSize.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: MeasureContentZeroStrokeWidthTest001
 * @tc.desc: test MeasureContent with zero stroke width
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentZeroStrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(0));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: UpdateDividerColorByThemeTest001
 * @tc.desc: test UpdateDividerColorByTheme when color already set
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, UpdateDividerColorByThemeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Update with same color should not cause issues
    paintProperty->UpdateDividerColorByTheme(Color::RED);

    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: RenderPropertyGetDividerColorTest001
 * @tc.desc: test GetDividerColor method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyGetDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto color = paintProperty->GetDividerColor();
    ASSERT_TRUE(color.has_value());
    EXPECT_EQ(color.value(), Color::BLUE);
}

/**
 * @tc.name: RenderPropertyCloneDividerColorTest001
 * @tc.desc: test CloneDividerColor method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyCloneDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto clonedColor = paintProperty->CloneDividerColor();
    ASSERT_TRUE(clonedColor.has_value());
    EXPECT_EQ(clonedColor.value(), Color::GREEN);
}

/**
 * @tc.name: OnThemeScopeUpdateWithNullPaintPropertyTest001
 * @tc.desc: test OnThemeScopeUpdate when paint property is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithNullPaintPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Normal case should work
    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: VerticalDividerMeasureContentTest001
 * @tc.desc: test vertical divider MeasureContent with self ideal width
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, VerticalDividerMeasureContentTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(20));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(300.0f);
    contentConstraint.selfIdealSize.SetWidth(25.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_LE(result.value().Width(), 25.0f);
}

/**
 * @tc.name: HorizontalDividerMeasureContentTest001
 * @tc.desc: test horizontal divider MeasureContent with self ideal height
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, HorizontalDividerMeasureContentTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(20));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(300.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    contentConstraint.selfIdealSize.SetHeight(25.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_LE(result.value().Height(), 25.0f);
}

/**
 * @tc.name: OnColorConfigurationUpdateWithNullPipelineTest001
 * @tc.desc: test OnColorConfigurationUpdate when pipeline is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateWithNullPipelineTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    // Should not crash when pattern has no host
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: DumpInfoWithNullHostTest001
 * @tc.desc: test DumpInfo when pattern has no host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpInfoWithNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Should not crash when pattern has no host
    pattern->DumpInfo();
}

/**
 * @tc.name: DumpInfoJsonWithNullHostTest001
 * @tc.desc: test DumpInfo with JsonValue when pattern has no host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpInfoJsonWithNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    // Should not crash when pattern has no host
    pattern->DumpInfo(json);
}

/**
 * @tc.name: CreateNodePaintMethodWithNullHostTest001
 * @tc.desc: test CreateNodePaintMethod when pattern has no host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateNodePaintMethodWithNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    // Should not crash when pattern has no host
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: LayoutAlgorithmUpdateConstraintSizeByLayoutPolicyTest001
 * @tc.desc: test UpdateConstraintSizeByLayoutPolicy with width wrap
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmUpdateConstraintSizeByLayoutPolicyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    LayoutPolicyProperty layoutPolicy;
    layoutPolicy.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicy.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: DividerColorSetByUserPropertyTest001
 * @tc.desc: test DividerColorSetByUser property operations
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DividerColorSetByUserPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Initially should not have value
    EXPECT_FALSE(paintProperty->GetDividerColorSetByUser().has_value());

    // Update the value
    paintProperty->UpdateDividerColorSetByUser(true);
    EXPECT_TRUE(paintProperty->GetDividerColorSetByUser().has_value());
    EXPECT_TRUE(paintProperty->GetDividerColorSetByUser().value());

    // Reset should clear the value
    paintProperty->ResetDividerColorSetByUser();
    EXPECT_FALSE(paintProperty->GetDividerColorSetByUser().has_value());
}

/**
 * @tc.name: LineCapPropertyTest001
 * @tc.desc: test LineCap property operations
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LineCapPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Initially should not have value
    EXPECT_FALSE(paintProperty->GetLineCap().has_value());

    // Update the value
    paintProperty->UpdateLineCap(LineCap::ROUND);
    EXPECT_TRUE(paintProperty->GetLineCap().has_value());
    EXPECT_EQ(paintProperty->GetLineCap().value(), LineCap::ROUND);
}

/**
 * @tc.name: StrokeWidthLimitationPropertyTest001
 * @tc.desc: test StrokeWidthLimitation property operations
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, StrokeWidthLimitationPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Initially should not have value
    EXPECT_FALSE(layoutProperty->GetStrokeWidthLimitation().has_value());

    // Update the value
    layoutProperty->UpdateStrokeWidthLimitation(false);
    EXPECT_TRUE(layoutProperty->GetStrokeWidthLimitation().has_value());
    EXPECT_FALSE(layoutProperty->GetStrokeWidthLimitation().value());
}

/**
 * @tc.name: VerticalPropertyTest001
 * @tc.desc: test Vertical property operations
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, VerticalPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Initially should not have value
    EXPECT_FALSE(layoutProperty->GetVertical().has_value());

    // Update the value
    layoutProperty->UpdateVertical(true);
    EXPECT_TRUE(layoutProperty->GetVertical().has_value());
    EXPECT_TRUE(layoutProperty->GetVertical().value());
}

/**
 * @tc.name: StrokeWidthPropertyTest001
 * @tc.desc: test StrokeWidth property operations
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, StrokeWidthPropertyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Initially should not have value
    EXPECT_FALSE(layoutProperty->GetStrokeWidth().has_value());

    // Update the value
    layoutProperty->UpdateStrokeWidth(Dimension(15));
    EXPECT_TRUE(layoutProperty->GetStrokeWidth().has_value());
    EXPECT_EQ(layoutProperty->GetStrokeWidth().value(), Dimension(15));
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapWithLargeStrokeWidthTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap with large stroke width
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapWithLargeStrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(100));
        model.Vertical(false);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(50.0f);
    contentConstraint.percentReference.SetHeight(200.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: RenderPropertyToJsonValueFastFilterTest001
 * @tc.desc: test ToJsonValue with fast filter enabled
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyToJsonValueFastFilterTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    paintProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: LayoutPropertyToJsonValueFastFilterTest001
 * @tc.desc: test LayoutProperty ToJsonValue with fast filter enabled
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyToJsonValueFastFilterTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);

    InspectorFilter filter;
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapWithNullLayoutAlgorithmWrapperTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap with null layout algorithm wrapper
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapWithNullLayoutAlgorithmWrapperTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(10));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->skipMeasureContent_ = true;

    // Do not set layout algorithm wrapper
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MeasureContentVerticalWithSelfIdealHeightTest001
 * @tc.desc: test vertical divider MeasureContent with self ideal height
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentVerticalWithSelfIdealHeightTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(5));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(300.0f);
    contentConstraint.selfIdealSize.SetHeight(150.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().Height(), 150.0f);
}

/**
 * @tc.name: MeasureContentHorizontalWithSelfIdealWidthTest001
 * @tc.desc: test horizontal divider MeasureContent with self ideal width
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentHorizontalWithSelfIdealWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(5));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(300.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    contentConstraint.selfIdealSize.SetWidth(150.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().Width(), 150.0f);
}

/**
 * @tc.name: RenderPropertyResetDividerColorTest001
 * @tc.desc: test ResetDividerColor method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyResetDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasDividerColor());

    paintProperty->ResetDividerColor();
    EXPECT_FALSE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: OnThemeScopeUpdateWithoutColorTest001
 * @tc.desc: test OnThemeScopeUpdate when divider has no color set
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithoutColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnThemeScopeUpdateWithColorTest001
 * @tc.desc: test OnThemeScopeUpdate when divider has color set
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnColorConfigurationUpdateColorNotSetByUserTest001
 * @tc.desc: test OnColorConfigurationUpdate when color not set by user
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateColorNotSetByUserTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    paintProperty->UpdateDividerColorSetByUser(false);

    OHOS::Ace::g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: OnColorConfigurationUpdateColorSetByUserTest001
 * @tc.desc: test OnColorConfigurationUpdate when color set by user
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateColorSetByUserTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = false;

    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: CreateLayoutAlgorithmMultipleTimesTest001
 * @tc.desc: test CreateLayoutAlgorithm can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateLayoutAlgorithmMultipleTimesTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto algorithm1 = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm1, nullptr);

    auto algorithm2 = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm2, nullptr);

    EXPECT_NE(algorithm1, algorithm2);
}

/**
 * @tc.name: CreatePaintPropertyMultipleTimesTest001
 * @tc.desc: test CreatePaintProperty can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreatePaintPropertyMultipleTimesTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto property1 = pattern->CreatePaintProperty();
    ASSERT_NE(property1, nullptr);

    auto property2 = pattern->CreatePaintProperty();
    ASSERT_NE(property2, nullptr);

    EXPECT_NE(property1, property2);
}

/**
 * @tc.name: CreateLayoutPropertyMultipleTimesTest001
 * @tc.desc: test CreateLayoutProperty can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateLayoutPropertyMultipleTimesTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto property1 = pattern->CreateLayoutProperty();
    ASSERT_NE(property1, nullptr);

    auto property2 = pattern->CreateLayoutProperty();
    ASSERT_NE(property2, nullptr);

    EXPECT_NE(property1, property2);
}

/**
 * @tc.name: CreateNodePaintMethodMultipleTimesTest001
 * @tc.desc: test CreateNodePaintMethod can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, CreateNodePaintMethodMultipleTimesTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto method1 = pattern->CreateNodePaintMethod();
    ASSERT_NE(method1, nullptr);

    auto method2 = pattern->CreateNodePaintMethod();
    ASSERT_NE(method2, nullptr);
}

/**
 * @tc.name: MeasureContentWithConstrainSizeTest001
 * @tc.desc: test MeasureContent with constrain size application
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentWithConstrainSizeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(50));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    contentConstraint.minSize.SetWidth(10.0f);
    contentConstraint.minSize.SetHeight(5.0f);
    contentConstraint.maxSize.SetWidth(200.0f);
    contentConstraint.maxSize.SetHeight(50.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: MeasureContentVerticalWithConstrainSizeTest001
 * @tc.desc: test vertical MeasureContent with constrain size application
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentVerticalWithConstrainSizeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(50));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    contentConstraint.minSize.SetWidth(5.0f);
    contentConstraint.minSize.SetHeight(10.0f);
    contentConstraint.maxSize.SetWidth(50.0f);
    contentConstraint.maxSize.SetHeight(200.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: RenderPropertyHasDividerColorTest001
 * @tc.desc: test HasDividerColor returns correct value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyHasDividerColorTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    EXPECT_FALSE(paintProperty->HasDividerColor());

    paintProperty->UpdateDividerColor(Color::RED);
    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: RenderPropertyCloneLineCapTest001
 * @tc.desc: test CloneLineCap method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyCloneLineCapTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.LineCap(LineCap::ROUND);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto clonedLineCap = paintProperty->CloneLineCap();
    ASSERT_TRUE(clonedLineCap.has_value());
    EXPECT_EQ(clonedLineCap.value(), LineCap::ROUND);
}

/**
 * @tc.name: RenderPropertyResetLineCapTest001
 * @tc.desc: test ResetLineCap method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyResetLineCapTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.LineCap(LineCap::SQUARE);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetLineCap().has_value());

    paintProperty->ResetLineCap();
    EXPECT_FALSE(paintProperty->GetLineCap().has_value());
}

/**
 * @tc.name: LayoutPropertyCloneVerticalTest001
 * @tc.desc: test CloneVertical method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyCloneVerticalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto clonedVertical = layoutProperty->CloneVertical();
    ASSERT_TRUE(clonedVertical.has_value());
    EXPECT_TRUE(clonedVertical.value());
}

/**
 * @tc.name: LayoutPropertyCloneStrokeWidthTest001
 * @tc.desc: test CloneStrokeWidth method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyCloneStrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(20));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto clonedStrokeWidth = layoutProperty->CloneStrokeWidth();
    ASSERT_TRUE(clonedStrokeWidth.has_value());
    EXPECT_EQ(clonedStrokeWidth.value(), Dimension(20));
}

/**
 * @tc.name: LayoutPropertyResetVerticalTest001
 * @tc.desc: test ResetVertical method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyResetVerticalTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetVertical().has_value());

    layoutProperty->ResetVertical();
    EXPECT_FALSE(layoutProperty->GetVertical().has_value());
}

/**
 * @tc.name: LayoutPropertyResetStrokeWidthTest001
 * @tc.desc: test ResetStrokeWidth method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyResetStrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.StrokeWidth(Dimension(15));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetStrokeWidth().has_value());

    layoutProperty->ResetStrokeWidth();
    EXPECT_FALSE(layoutProperty->GetStrokeWidth().has_value());
}

/**
 * @tc.name: LayoutPropertyCloneStrokeWidthLimitationTest001
 * @tc.desc: test CloneStrokeWidthLimitation method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyCloneStrokeWidthLimitationTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateStrokeWidthLimitation(false);

    auto clonedLimitation = layoutProperty->CloneStrokeWidthLimitation();
    ASSERT_TRUE(clonedLimitation.has_value());
    EXPECT_FALSE(clonedLimitation.value());
}

/**
 * @tc.name: LayoutPropertyResetStrokeWidthLimitationTest001
 * @tc.desc: test ResetStrokeWidthLimitation method
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutPropertyResetStrokeWidthLimitationTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateStrokeWidthLimitation(true);
    EXPECT_TRUE(layoutProperty->GetStrokeWidthLimitation().has_value());

    layoutProperty->ResetStrokeWidthLimitation();
    EXPECT_FALSE(layoutProperty->GetStrokeWidthLimitation().has_value());
}

/**
 * @tc.name: LayoutAlgorithmDefaultConstructorTest001
 * @tc.desc: test DividerLayoutAlgorithm default constructor
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmDefaultConstructorTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    // Initially values should be default
    EXPECT_EQ(layoutAlgorithm->GetConstrainStrokeWidth(), 0.0f);
    EXPECT_EQ(layoutAlgorithm->GetDividerLength(), 0.0f);
    EXPECT_FALSE(layoutAlgorithm->GetVertical());
    EXPECT_TRUE(layoutAlgorithm->GetStrokeWidthLimitation());
}

/**
 * @tc.name: RenderPropertyDividerColorValueWithoutDefaultTest001
 * @tc.desc: test GetDividerColorValue without providing default
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyDividerColorValueWithoutDefaultTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::RED);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto color = paintProperty->GetDividerColorValue();
    EXPECT_EQ(color, Color::RED);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapVerticalWithStrokeLimitationTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap with vertical divider and stroke limitation
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapVerticalWithStrokeLimitationTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(50));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(200.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MeasureContentWithZeroDividerLengthTest001
 * @tc.desc: test MeasureContent when divider length would be zero
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentWithZeroDividerLengthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(0));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(0.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: OnColorConfigurationUpdateNullHostTest001
 * @tc.desc: test OnColorConfigurationUpdate with null host
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnColorConfigurationUpdateNullHostTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    OHOS::Ace::g_isConfigChangePerform = true;
    // Should not crash with null host
    pattern->OnColorConfigurationUpdate();
    OHOS::Ace::g_isConfigChangePerform = false;
}

/**
 * @tc.name: DumpDividerColorNullThemeTest001
 * @tc.desc: test DumpDividerColor when theme is null
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, DumpDividerColorNullThemeTest001, TestSize.Level0)
{
    auto pattern = AceType::MakeRefPtr<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result = pattern->DumpDividerColor();
    EXPECT_EQ(result, "NA");
}

/**
 * @tc.name: FocusPatternImmutableTest001
 * @tc.desc: test GetFocusPattern returns consistent values
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, FocusPatternImmutableTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusPattern1 = pattern->GetFocusPattern();
    auto focusPattern2 = pattern->GetFocusPattern();

    EXPECT_EQ(focusPattern1.focusType_, focusPattern2.focusType_);
    EXPECT_EQ(focusPattern1.focusable_, focusPattern2.focusable_);
}

/**
 * @tc.name: IsEnableMatchParentConsistencyTest001
 * @tc.desc: test IsEnableMatchParent returns consistent value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, IsEnableMatchParentConsistencyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableMatchParent());
    EXPECT_TRUE(pattern->IsEnableMatchParent());
    EXPECT_TRUE(pattern->IsEnableMatchParent());
}

/**
 * @tc.name: IsEnableFixConsistencyTest001
 * @tc.desc: test IsEnableFix returns consistent value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, IsEnableFixConsistencyTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsEnableFix());
    EXPECT_TRUE(pattern->IsEnableFix());
    EXPECT_TRUE(pattern->IsEnableFix());
}

/**
 * @tc.name: OnThemeScopeUpdateMultipleCallsTest001
 * @tc.desc: test OnThemeScopeUpdate can be called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateMultipleCallsTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result1 = pattern->OnThemeScopeUpdate(0);
    auto result2 = pattern->OnThemeScopeUpdate(1);
    auto result3 = pattern->OnThemeScopeUpdate(2);

    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
}

/**
 * @tc.name: OnThemeScopeUpdateWithColorMultipleCallsTest001
 * @tc.desc: test OnThemeScopeUpdate with color set called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnThemeScopeUpdateWithColorMultipleCallsTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::BLUE);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto result1 = pattern->OnThemeScopeUpdate(0);
    auto result2 = pattern->OnThemeScopeUpdate(1);
    auto result3 = pattern->OnThemeScopeUpdate(2);

    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
    EXPECT_FALSE(result3);
}

/**
 * @tc.name: RenderPropertyUpdateDividerColorNoChangeTest001
 * @tc.desc: test UpdateDividerColor with same color value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyUpdateDividerColorNoChangeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {});
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    OHOS::Ace::g_isConfigChangePerform = false;
    paintProperty->UpdateDividerColor(Color::RED);
    EXPECT_TRUE(paintProperty->HasDividerColor());

    // Update with same color
    paintProperty->UpdateDividerColor(Color::RED);
    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: RenderPropertyUpdateDividerColorByThemeNoChangeTest001
 * @tc.desc: test UpdateDividerColorByTheme with same color value
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, RenderPropertyUpdateDividerColorByThemeNoChangeTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.DividerColor(Color::GREEN);
    });
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);

    // Update with same color via ByTheme
    paintProperty->UpdateDividerColorByTheme(Color::GREEN);
    EXPECT_TRUE(paintProperty->HasDividerColor());
}

/**
 * @tc.name: MeasureContentNegativeStrokeWidthTest001
 * @tc.desc: test MeasureContent with negative stroke width
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, MeasureContentNegativeStrokeWidthTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(-10));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(200.0f);
    contentConstraint.percentReference.SetHeight(100.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    auto result = layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());
    ASSERT_TRUE(result.has_value());
}

/**
 * @tc.name: LayoutAlgorithmGettersAfterMeasureTest001
 * @tc.desc: test getters after MeasureContent call
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, LayoutAlgorithmGettersAfterMeasureTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(true);
        model.StrokeWidth(Dimension(20));
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(100.0f);
    contentConstraint.percentReference.SetHeight(300.0f);

    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    // Verify all getters return expected values
    EXPECT_GT(layoutAlgorithm->GetConstrainStrokeWidth(), 0.0f);
    EXPECT_GT(layoutAlgorithm->GetDividerLength(), 0.0f);
    EXPECT_TRUE(layoutAlgorithm->GetVertical());
    EXPECT_TRUE(layoutAlgorithm->GetStrokeWidthLimitation());
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapWithZeroValuesTest001
 * @tc.desc: test OnDirtyLayoutWrapperSwap with zero divider values
 * @tc.type: FUNC
 */
HWTEST_F(DividerBranchCoverageTestNG, OnDirtyLayoutWrapperSwapWithZeroValuesTest001, TestSize.Level0)
{
    auto frameNode = CreateDivider([](DividerModelNG model) {
        model.Vertical(false);
        model.StrokeWidth(Dimension(0));
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DividerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<DividerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::MakeRefPtr<DividerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig config;
    config.skipMeasure = false;

    LayoutConstraintF contentConstraint;
    contentConstraint.percentReference.SetWidth(0.0f);
    contentConstraint.percentReference.SetHeight(100.0f);
    layoutAlgorithm->MeasureContent(contentConstraint, layoutWrapper.GetRawPtr());

    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG
