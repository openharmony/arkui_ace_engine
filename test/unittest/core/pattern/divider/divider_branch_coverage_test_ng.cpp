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
} // namespace OHOS::Ace::NG
