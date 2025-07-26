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

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
class IndexerPatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void IndexerPatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void IndexerPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: BuildArrayValueItemsTest001
 * @tc.desc: BuildArrayValueItems
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, BuildArrayValueItemsTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->BuildArrayValueItems();

    auto layoutProperty = indexNode->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto result = layoutProperty->HasActualArrayValue();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CollapseArrayValueTest001
 * @tc.desc: CollapseArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CollapseArrayValueTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->maxContentHeight_ = 32.0f;
    pattern->lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
    pattern->CollapseArrayValue();
    EXPECT_EQ(pattern->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: CollapseArrayValueTest001
 * @tc.desc: CollapseArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CollapseArrayValueTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->sharpItemCount_ = 12;
    pattern->lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
    pattern->CollapseArrayValue();
    EXPECT_EQ(pattern->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: CollapseArrayValueTest001
 * @tc.desc: CollapseArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CollapseArrayValueTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->maxContentHeight_ = 14.0f;
    pattern->fullArrayValue_ = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    auto layoutProperty = indexNode->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension value(1.0f);
    layoutProperty->UpdateItemSize(value);

    pattern->lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
    pattern->CollapseArrayValue();
    EXPECT_EQ(pattern->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
}

/**
 * @tc.name: CollapseArrayValueTest001
 * @tc.desc: CollapseArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CollapseArrayValueTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->maxContentHeight_ = 12.0f;
    pattern->fullArrayValue_ = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    auto layoutProperty = indexNode->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Dimension value(1.0f);
    layoutProperty->UpdateItemSize(value);

    pattern->lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
    pattern->CollapseArrayValue();
    EXPECT_EQ(pattern->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: GetAutoCollapseIndexTest001
 * @tc.desc: GetAutoCollapseIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, GetAutoCollapseIndexTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->fullArrayValue_ = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K" };
    pattern->sharpItemCount_ = 2;
    pattern->lastCollapsingMode_ = IndexerCollapsingMode::SEVEN;

    int32_t result1 = pattern->GetAutoCollapseIndex(2);
    EXPECT_EQ(result1, 2);
    EXPECT_EQ(pattern->collapsedIndex_, 0);

    int32_t result2 = pattern->GetAutoCollapseIndex(3);
    EXPECT_EQ(result2, 4);
    EXPECT_EQ(pattern->collapsedIndex_, 0);

    int32_t result3 = pattern->GetAutoCollapseIndex(7);
    EXPECT_EQ(result3, 14);
    EXPECT_EQ(pattern->collapsedIndex_, 0);

    int32_t result4 = pattern->GetAutoCollapseIndex(8);
    EXPECT_EQ(result4, 15);
    EXPECT_EQ(pattern->collapsedIndex_, 0);

    int32_t result5 = pattern->GetAutoCollapseIndex(9);
    EXPECT_EQ(result5, 16);
    EXPECT_EQ(pattern->collapsedIndex_, 0);

    int32_t result6 = pattern->GetAutoCollapseIndex(10);
    EXPECT_EQ(result6, 17);
    EXPECT_EQ(pattern->collapsedIndex_, 0);
}

/**
 * @tc.name: GetSkipChildIndexTest001
 * @tc.desc: GetSkipChildIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, GetSkipChildIndexTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t step = -2;
    auto result = pattern->GetSkipChildIndex(step);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetSkipChildIndexTest002
 * @tc.desc: GetSkipChildIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, GetSkipChildIndexTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t step = 2;
    auto result = pattern->GetSkipChildIndex(step);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetSkipChildIndexTest002
 * @tc.desc: GetSkipChildIndex
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, GetSkipChildIndexTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t step = 2;
    pattern->itemCount_ = 1;

    auto result = pattern->GetSkipChildIndex(step);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: UpdateNormalStyleTest001
 * @tc.desc: UpdateNormalStyle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateNormalStyleTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = indexNode->GetRenderContext();
    ASSERT_NE(pattern, nullptr);

    pattern->UpdateNormalStyle(renderContext, 0, true);

    Color defaultValue = Color::BLACK;
    auto result = renderContext->GetBackgroundColorValue(defaultValue);
    EXPECT_EQ(result, Color::TRANSPARENT);
}

/**
 * @tc.name: UpdateNormalStyleTest002
 * @tc.desc: UpdateNormalStyle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateNormalStyleTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = indexNode->GetRenderContext();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->UpdateNormalStyle(renderContext, 0, true);

    auto value = Dimension(0.0, DimensionUnit::VP);
    BorderRadiusProperty defaultValue = { value, value, value, value };
    auto result = renderContext->GetBorderRadiusValue(defaultValue);
    EXPECT_NE(result.radiusTopLeft, value);
    EXPECT_NE(result.radiusTopRight, value);
    EXPECT_NE(result.radiusBottomRight, value);
    EXPECT_NE(result.radiusBottomLeft, value);
}

/**
 * @tc.name: UpdateNormalStyleTest003
 * @tc.desc: UpdateNormalStyle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateNormalStyleTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderContext = indexNode->GetRenderContext();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN);
    pattern->UpdateNormalStyle(renderContext, 0, true);

    auto value = Dimension(8.0, DimensionUnit::VP);
    BorderRadiusProperty defaultValue = { value, value, value, value };
    auto result = renderContext->GetBorderRadiusValue(defaultValue);
    EXPECT_NE(result.radiusTopLeft, value);
    EXPECT_NE(result.radiusTopRight, value);
    EXPECT_NE(result.radiusBottomRight, value);
    EXPECT_NE(result.radiusBottomLeft, value);
}

/**
 * @tc.name: UpdateBubbleViewTest001
 * @tc.desc: UpdateBubbleView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleViewTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_ = { "1" };
    pattern->UpdateBubbleView();

    auto value = CalcLength(0.0);
    const auto& padding = layoutProperty->GetPaddingProperty();
    EXPECT_NE(padding, nullptr);
    EXPECT_EQ(padding->left, value);
    EXPECT_EQ(padding->right, value);
    EXPECT_EQ(padding->top, CalcLength(4.0));
    EXPECT_EQ(padding->bottom, value);
}

/**
 * @tc.name: UpdateBubbleViewTest002
 * @tc.desc: UpdateBubbleView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleViewTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto renderContext = pattern->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_ = { "1" };
    Dimension popupValue(16.0f, DimensionUnit::VP);
    paintProperty->UpdatePopupBorderRadius(popupValue);
    pattern->UpdateBubbleView();

    auto value = Dimension(0.0f, DimensionUnit::VP);
    BorderRadiusProperty defaultValue = { value, value, value, value };
    auto result = renderContext->GetBorderRadiusValue(defaultValue);
    EXPECT_EQ(result.radiusTopLeft, popupValue);
    EXPECT_EQ(result.radiusTopRight, popupValue);
    EXPECT_EQ(result.radiusBottomRight, popupValue);
    EXPECT_EQ(result.radiusBottomLeft, popupValue);
}

/**
 * @tc.name: UpdateBubbleViewTest003
 * @tc.desc: UpdateBubbleView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleViewTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto renderContext = pattern->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_ = { "1" };
    Dimension popupValue(28.0f, DimensionUnit::VP);
    pattern->UpdateBubbleView();

    auto value = Dimension(0.0f, DimensionUnit::VP);
    BorderRadiusProperty defaultValue = { value, value, value, value };
    auto result = renderContext->GetBorderRadiusValue(defaultValue);
    EXPECT_EQ(result.radiusTopLeft, popupValue);
    EXPECT_EQ(result.radiusTopRight, popupValue);
    EXPECT_EQ(result.radiusBottomRight, popupValue);
    EXPECT_EQ(result.radiusBottomLeft, popupValue);
}

/**
 * @tc.name: UpdateBubbleViewTest004
 * @tc.desc: UpdateBubbleView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleViewTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto renderContext = pattern->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN);
    pattern->currentListData_ = { "1" };
    Dimension popupValue(16.0f, DimensionUnit::VP);
    pattern->UpdateBubbleView();

    auto value = Dimension(0.0f, DimensionUnit::VP);
    BorderRadiusProperty defaultValue = { value, value, value, value };
    auto result = renderContext->GetBorderRadiusValue(defaultValue);
    EXPECT_EQ(result.radiusTopLeft, popupValue);
    EXPECT_EQ(result.radiusTopRight, popupValue);
    EXPECT_EQ(result.radiusBottomRight, popupValue);
    EXPECT_EQ(result.radiusBottomLeft, popupValue);
}

/**
 * @tc.name: UpdateBubbleBackgroundViewTest001
 * @tc.desc: UpdateBubbleBackgroundView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleBackgroundViewTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto renderContext = pattern->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto pipeline = indexNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    ASSERT_NE(indexerTheme, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    BlurStyleOption styleption;
    styleption.blurStyle = BlurStyle::BACKGROUND_THIN;
    paintProperty->UpdatePopupBackgroundBlurStyle(styleption);
    pattern->UpdateBubbleBackgroundView();
    auto result = paintProperty->GetPopupBackgroundBlurStyle().has_value();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: UpdateBubbleBackgroundViewTest002
 * @tc.desc: UpdateBubbleBackgroundView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleBackgroundViewTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto renderContext = pattern->popupNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto pipeline = indexNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    ASSERT_NE(indexerTheme, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->UpdateBubbleBackgroundView();
    auto result = paintProperty->GetPopupBackgroundBlurStyle().has_value();
    EXPECT_EQ(result, false);

    BlurStyleOption styleption;
    EXPECT_EQ(styleption.blurStyle, BlurStyle::COMPONENT_REGULAR);
}
} // namespace OHOS::Ace::NG