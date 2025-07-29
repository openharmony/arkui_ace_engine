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
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

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
    ASSERT_NE(padding, nullptr);

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

/**
 * @tc.name: UpdateBubbleSizeTest001
 * @tc.desc: UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleSizeTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->autoCollapse_ = true;
    pattern->currentListData_ = std::vector<std::string>(INDEXER_BUBBLE_MAXSIZE_COLLAPSED_API_TWELVE - 1, "item");
    pattern->UpdateBubbleSize();

    const float expectedHeight =
        (BUBBLE_ITEM_SIZE + BUBBLE_DIVIDER_SIZE) * (pattern->currentListData_.size() + 1) + BUBBLE_DIVIDER_SIZE;
    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;

    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), BUBBLE_BOX_SIZE, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), expectedHeight, 0.01);
}

/**
 * @tc.name: UpdateBubbleSizeTest002
 * @tc.desc: UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleSizeTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->autoCollapse_ = false;
    pattern->currentListData_ = std::vector<std::string>(INDEXER_BUBBLE_MAXSIZE + 5, "item");

    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;

    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), BUBBLE_BOX_SIZE, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), BUBBLE_COLUMN_MAX_SIZE, 0.01);
}

/**
 * @tc.name: UpdateBubbleSizeTest003
 * @tc.desc: UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleSizeTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->autoCollapse_ = true;
    pattern->currentListData_ = std::vector<std::string>(INDEXER_BUBBLE_MAXSIZE_COLLAPSED - 2, "item");
    pattern->UpdateBubbleSize();

    int32_t expectedItems =
        std::min<int32_t>(static_cast<int32_t>(pattern->currentListData_.size()), INDEXER_BUBBLE_MAXSIZE_COLLAPSED);

    float expectedHeight = BUBBLE_BOX_SIZE * (expectedItems + 1);
    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;

    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), BUBBLE_BOX_SIZE, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), expectedHeight, 0.01);
}

/**
 * @tc.name: UpdateBubbleSizeTest004
 * @tc.desc: UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleSizeTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->autoCollapse_ = false;
    pattern->currentListData_ = std::vector<std::string>(INDEXER_BUBBLE_MAXSIZE + 3, "item");
    pattern->UpdateBubbleSize();

    int32_t expectedItems = INDEXER_BUBBLE_MAXSIZE;
    auto expectedHeight = BUBBLE_BOX_SIZE * (expectedItems + 1);
    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), BUBBLE_BOX_SIZE, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), expectedHeight, 0.01);
}

/**
 * @tc.name: UpdateBubbleLetterViewTest001
 * @tc.desc: UpdateBubbleLetterView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterViewTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = indexNode->GetPaintProperty<IndexerPaintProperty>();
    paintProperty->UpdatePopupItemBorderRadius(Dimension(10.0));
    paintProperty->UpdatePopupTitleBackground(Color::BLUE);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->currentListData_ = { "A", "B" };
    pattern->UpdateBubbleLetterView(false);

    auto letterNode = pattern->GetLetterNode();
    auto renderContext = letterNode->GetRenderContext();
    auto layoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();

    auto bubbleSize = Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx();
    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;

    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), bubbleSize, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), bubbleSize, 0.01);
    EXPECT_EQ(renderContext->GetBorderRadius()->radiusTopLeft, Dimension(10.0));
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::BLUE);
}

/**
 * @tc.name: UpdateBubbleLetterViewTest002
 * @tc.desc: UpdateBubbleLetterView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterViewTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->UpdateBubbleLetterView(true);

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto renderContext = letterNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto layoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<IndexerTheme>();
    ASSERT_NE(theme, nullptr);

    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto calcSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_NEAR(calcSize->Width()->GetDimension().ConvertToPx(), bubbleSize, 0.01);
    EXPECT_NEAR(calcSize->Height()->GetDimension().ConvertToPx(), bubbleSize, 0.01);

    auto& borderWidth = layoutProperty->GetBorderWidthProperty();
    EXPECT_EQ(borderWidth->bottomDimen, Dimension(INDEXER_LIST_DIVIDER));
    EXPECT_EQ(renderContext->GetBorderColor()->bottomColor, theme->GetPopupSeparateColor());
}

/**
 * @tc.name: UpdateBubbleLetterViewTest003
 * @tc.desc: Test UpdateBubbleLetterView with API version < 12 without divider
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterViewTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->UpdateBubbleLetterView(false);

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto layoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto& borderWidth = layoutProperty->GetBorderWidthProperty();
    EXPECT_EQ(borderWidth->leftDimen, Dimension(0.0));
    EXPECT_EQ(borderWidth->rightDimen, Dimension(0.0));
    EXPECT_EQ(borderWidth->topDimen, Dimension(0.0));
    EXPECT_EQ(borderWidth->bottomDimen, Dimension(0.0));
}

/**
 * @tc.name: UpdateBubbleLetterViewTest004
 * @tc.desc: Test UpdateBubbleLetterView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterViewTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto theme = MockPipelineContext::GetCurrent()->GetTheme<IndexerTheme>();
    ASSERT_NE(theme, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_ = {};
    pattern->UpdateBubbleLetterView(false);

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto renderContext = letterNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    EXPECT_EQ(renderContext->GetBackgroundColor(), Color(POPUP_TITLE_BG_COLOR_SINGLE));
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest001
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->selected_ = 5;
    pattern->fullArrayValue_ = { "A", "B", "C", "D", "E", "F", "G" };

    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto textLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    std::u16string defaultValue = u"A";
    std::u16string value = u"F";

    auto result = textLayoutProperty->GetContentValue(defaultValue);
    EXPECT_EQ(result, value);
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest002
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto LayoutProperty = indexNode->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(pattern, nullptr);

    TextStyle customFont;
    customFont.SetFontSize(Dimension(20));
    customFont.SetFontWeight(FontWeight::BOLD);
    customFont.SetFontFamilies({ "CustomFontFamily" });
    LayoutProperty->UpdatePopupFont(customFont);

    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto textLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_EQ(textLayoutProperty->GetFontSize(), Dimension(20));
    EXPECT_EQ(textLayoutProperty->GetFontWeight(), FontWeight::BOLD);
    EXPECT_EQ(textLayoutProperty->GetFontFamily().has_value(), true);
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest003
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto letterNode = pattern->GetLetterNode();
    ASSERT_NE(letterNode, nullptr);

    auto textLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto result = textLayoutProperty->GetFontFamily().has_value();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest004
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->autoCollapse_ = false;
    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto stackNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetFirstChild());
    auto stackProp = stackNode->GetLayoutProperty<StackLayoutProperty>();

    auto expectedWidth = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto expectedHeight = Dimension(BUBBLE_ITEM_SIZE + BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto stackSize = stackProp->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(stackSize->Width()->GetDimension().ConvertToPx(), expectedWidth);
    EXPECT_EQ(stackSize->Height()->GetDimension().ConvertToPx(), expectedHeight);

    auto expectedPadding = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto& padding = stackProp->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);

    EXPECT_EQ(padding->left->GetDimension().ConvertToPx(), expectedPadding);
    EXPECT_EQ(padding->right->GetDimension().ConvertToPx(), expectedPadding);
    EXPECT_EQ(padding->top->GetDimension().ConvertToPx(), expectedPadding);
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest005
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest005, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto stackNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetFirstChild());
    auto originalSize = stackNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->autoCollapse_ = false;
    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto newSize = stackNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(originalSize->Width(), newSize->Width());
    EXPECT_EQ(originalSize->Height(), newSize->Height());
}

/**
 * @tc.name: UpdateBubbleLetterStackAndLetterTextViewTest006
 * @tc.desc: UpdateBubbleLetterStackAndLetterTextView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleLetterStackAndLetterTextViewTest006, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto stackNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetFirstChild());
    auto originalSize = stackNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->autoCollapse_ = true;
    pattern->UpdateBubbleLetterStackAndLetterTextView();

    auto newSize = stackNode->GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(originalSize->Width(), newSize->Width());
    EXPECT_EQ(originalSize->Height(), newSize->Height());
}

/**
 * @tc.name: UpdateBubbleListViewTest001
 * @tc.desc: UpdateBubbleListView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleListViewTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
    pattern->currentListData_ = { "Item1", "Item2", "Item3" };
    pattern->autoCollapse_ = false;
    pattern->UpdateBubbleListView();

    auto listNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetLastChild()->GetFirstChild());
    ASSERT_NE(listNode, nullptr);

    auto listPattern = AceType::DynamicCast<ListPattern>(listNode->GetPattern());
    ASSERT_NE(listPattern, nullptr);

    EXPECT_FALSE(listPattern->GetNeedLinked());

    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(listLayoutProperty, nullptr);

    V2::ItemDivider defaultValue = { .startMargin = 0.0_vp, .strokeWidth = 0.0_vp, .endMargin = 0.0_vp };
    auto divider = listLayoutProperty->GetDividerValue(defaultValue);

    EXPECT_EQ(divider.strokeWidth.Value(), INDEXER_LIST_DIVIDER);
    EXPECT_EQ(divider.color, pattern->GetContext()->GetTheme<IndexerTheme>()->GetPopupSeparateColor());

    auto listPaintProperty = listNode->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(listPaintProperty, nullptr);

    EXPECT_EQ(listPaintProperty->GetScrollBarMode(), DisplayMode::OFF);
    EXPECT_FALSE(listPaintProperty->GetFadingEdge());

    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(listNode->GetRenderContext());
    ASSERT_NE(mockRenderContext, nullptr);

    EXPECT_CALL(*mockRenderContext, SetClipToBounds(true));
}

/**
 * @tc.name: UpdateBubbleListViewTest002
 * @tc.desc: UpdateBubbleListView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleListViewTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_.clear();
    pattern->autoCollapse_ = false;
    pattern->UpdateBubbleListView();

    auto listNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetLastChild()->GetFirstChild());
    ASSERT_NE(listNode, nullptr);

    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(listLayoutProperty, nullptr);

    V2::ItemDivider defaultValue = { .startMargin = 0.0_vp, .strokeWidth = 0.0_vp, .endMargin = 0.0_vp };
    auto divider = listLayoutProperty->GetDividerValue(defaultValue);

    EXPECT_EQ(divider.strokeWidth.Value(), BUBBLE_DIVIDER_SIZE);
    EXPECT_EQ(divider.strokeWidth.Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: UpdateBubbleListViewTest003
 * @tc.desc: UpdateBubbleListView
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, UpdateBubbleListViewTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    pattern->currentListData_ = { "Item1", "Item2", "Item3" };
    pattern->autoCollapse_ = true;
    pattern->UpdateBubbleListView();

    auto listNode = AceType::DynamicCast<FrameNode>(pattern->popupNode_->GetLastChild()->GetFirstChild());
    ASSERT_NE(listNode, nullptr);

    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(listLayoutProperty, nullptr);

    auto& padding = listLayoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);

    auto listPadding = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();

    EXPECT_EQ(padding->left.value(), CalcLength(listPadding));
    EXPECT_EQ(padding->right.value(), CalcLength(listPadding));
    EXPECT_EQ(padding->top.value(), CalcLength(0));
    EXPECT_EQ(padding->bottom.value(), CalcLength(0));
}

/**
 * @tc.name: MeasureArcTest001
 * @tc.desc: MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, MeasureArcTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);

    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);

    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);

    arcindexerLayoutAlgorithm->itemSize_ = 10.f;
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 4;
    arcindexerLayoutAlgorithm->stepAngle_ = 100.0f;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->stepAngle_, 90.0f);
}

/**
 * @tc.name: MeasureArcTest002
 * @tc.desc: MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, MeasureArcTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);

    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);

    arcindexerLayoutAlgorithm->itemSize_ = 10.f;
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 3;
    arcindexerLayoutAlgorithm->stepAngle_ = 100.0f;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->stepAngle_, 300.0f);
}

/**
 * @tc.name: MeasureArcTest003
 * @tc.desc: MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, MeasureArcTest003, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);

    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);

    arcindexerLayoutAlgorithm->itemSize_ = 10.f;
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 5;
    arcindexerLayoutAlgorithm->stepAngle_ = 50.0f;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->stepAngle_, -100.0f);
}

/**
 * @tc.name: MeasureArcTest004
 * @tc.desc: MeasureArc
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, MeasureArcTest004, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ArcIndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);

    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    layoutWrapper->GetGeometryNode()->GetFrameSize().SetWidth(100.0f);
    layoutWrapper->GetGeometryNode()->GetFrameSize().SetHeight(50.0f);
    auto arcindexerLayoutAlgorithm = AceType::DynamicCast<ArcIndexerLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    EXPECT_NE(arcindexerLayoutAlgorithm, nullptr);

    arcindexerLayoutAlgorithm->itemSize_ = 10.f;
    auto layoutProperty = frameNode->GetLayoutProperty<ArcIndexerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->propAutoCollapse_ = false;
    arcindexerLayoutAlgorithm->fullCount_ = 3;
    arcindexerLayoutAlgorithm->stepAngle_ = 50.0f;
    arcindexerLayoutAlgorithm->MeasureArc(layoutWrapper);
    EXPECT_EQ(arcindexerLayoutAlgorithm->stepAngle_, -50.0f);
}

/**
 * @tc.name: CalcBubbleListSizeTest001
 * @tc.desc: CalcBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CalcBubbleListSizeTest001, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t popupSize = 3;
    int32_t maxItemsSize = 5;
    pattern->autoCollapse_ = false;

    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto bubbleHeight = Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx();
    auto bubbleDivider = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto expectedWidth = CalcLength(bubbleSize);
    auto expectedHeight = CalcLength((bubbleHeight + bubbleDivider) * popupSize - bubbleDivider);

    auto result = pattern->CalcBubbleListSize(popupSize, maxItemsSize);
    EXPECT_EQ(result.Width(), expectedWidth);
    EXPECT_EQ(result.Height(), expectedHeight);
}

/**
 * @tc.name: CalcBubbleListSizeTest002
 * @tc.desc: CalcBubbleListSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, CalcBubbleListSizeTest002, TestSize.Level1)
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    CHECK_NULL_VOID(element);

    auto indexNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(indexNode, nullptr);

    auto pattern = indexNode->GetPattern<IndexerPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t popupSize = 8;
    int32_t maxItemsSize = 5;
    pattern->autoCollapse_ = true;

    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto expectedWidth = CalcLength(bubbleSize);
    auto expectedHeight = CalcLength(Dimension(BUBBLE_COLLAPSE_LIST_MAX_SIZE, DimensionUnit::VP).ConvertToPx());

    auto result = pattern->CalcBubbleListSize(popupSize, maxItemsSize);

    EXPECT_EQ(result.Width(), expectedWidth);
    EXPECT_EQ(result.Height(), expectedHeight);
}
} // namespace OHOS::Ace::NG