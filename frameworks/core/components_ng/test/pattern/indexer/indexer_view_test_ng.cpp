/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::vector<std::string> CREATE_ARRAY_VALUE = {"A", "B", "C", "D", "E", "F", "G", "H",
    "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
const std::vector<std::string> EMPTY_ARRAY_VALUE = {};
constexpr int32_t CREATE_SELECTED_VALUE = 0;
constexpr int32_t SELECTED_VALUE = 0;
constexpr int32_t SPECIAL_SELECTED_VALUE = -1;
constexpr Color COLOR_VALUE = Color(0x00000000);
const TextStyle SELECTED_FONT_VALUE = TextStyle();
const TextStyle POPUP_FONT_VALUE = TextStyle();
const TextStyle FONT_VALUE = TextStyle();
constexpr Dimension ITEM_SIZE_VALUE = Dimension(24.0, DimensionUnit::PX);
constexpr Dimension SPECIAL_ITEM_SIZE_VALUE = Dimension(-1, DimensionUnit::PX);
constexpr AlignStyle ALIGN_STYLE_VALUE = AlignStyle::LEFT;
constexpr float POPUP_POSITIONX_VALUE = -96.0f;
constexpr float POPUP_POSITIONY_VALUE = 48.0f;
constexpr Dimension FONT_SIZE_VALUE = Dimension(24.0, DimensionUnit::VP);
constexpr FontWeight FONT_WEIGHT_VALUE = FontWeight::MEDIUM;
constexpr Dimension SPACE_VALUE = Dimension(50.0, DimensionUnit::PX);
constexpr Dimension SPACE_INVALID_VALUE = Dimension(-1, DimensionUnit::PX);
} // namespace

struct TestProperty {
    std::optional<Color> colorValue = std::nullopt;
    std::optional<Color> selectedColorValue = std::nullopt;
    std::optional<Color> popupColorValue = std::nullopt;
    std::optional<Color> selectedBackgroundColorValue = std::nullopt;
    std::optional<Color> popupBackgroundColorValue = std::nullopt;
    std::optional<bool> usingPopupValue = std::nullopt;
    std::optional<TextStyle> selectedFontValue = std::nullopt;
    std::optional<TextStyle> popupFontValue = std::nullopt;
    std::optional<TextStyle> fontValue = std::nullopt;
    std::optional<Dimension> itemSizeValue = std::nullopt;
    std::optional<AlignStyle> alignStyleValue = std::nullopt;
    std::optional<int32_t> selectedValue = std::nullopt;
    std::optional<float> popupPositionXValue = std::nullopt;
    std::optional<float> popupPositionYValue = std::nullopt;
    std::optional<Color> popupSelectedColorValue = std::nullopt;
    std::optional<Color> popupUnselectedColorValue = std::nullopt;
    std::optional<Color> popupItemBackgroundValue = std::nullopt;
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<FontWeight> fontWeightValue = std::nullopt;
    std::optional<Dimension> popupHorizontalSpaceValue = std::nullopt;
};

class IndexerViewTestNg : public testing::Test {
public:
    static RefPtr<FrameNode> CreateIndexerParagraph(const std::vector<std::string>& createArray,
        int32_t createSelected, const TestProperty& testProperty);
    static void SetIndexerProperty(IndexerView& indexerView, const TestProperty& testProperty);
    static void SetBubbleProperty(IndexerView& indexerView, const TestProperty& testProperty);
};

void IndexerViewTestNg::SetIndexerProperty(IndexerView& indexerView, const TestProperty& testProperty)
{
    if (testProperty.colorValue.has_value()) {
        indexerView.SetColor(testProperty.colorValue.value());
    }
    if (testProperty.selectedColorValue.has_value()) {
        indexerView.SetSelectedColor(testProperty.selectedColorValue.value());
    }
    if (testProperty.selectedBackgroundColorValue.has_value()) {
        indexerView.SetSelectedBackgroundColor(testProperty.selectedBackgroundColorValue.value());
    }
    if (testProperty.selectedFontValue.has_value()) {
        indexerView.SetSelectedFont(testProperty.selectedFontValue.value());
    }
    if (testProperty.fontValue.has_value()) {
        indexerView.SetFont(testProperty.fontValue.value());
    }
    if (testProperty.itemSizeValue.has_value()) {
        indexerView.SetItemSize(testProperty.itemSizeValue.value());
    }
    if (testProperty.selectedValue.has_value()) {
        indexerView.SetSelected(testProperty.selectedValue.value());
    }
}

void IndexerViewTestNg::SetBubbleProperty(IndexerView& indexerView, const TestProperty& testProperty)
{
    if (testProperty.popupColorValue.has_value()) {
        indexerView.SetPopupColor(testProperty.popupColorValue.value());
    }
    if (testProperty.popupBackgroundColorValue.has_value()) {
        indexerView.SetPopupBackground(testProperty.popupBackgroundColorValue.value());
    }
    if (testProperty.usingPopupValue.has_value()) {
        indexerView.SetUsingPopup(testProperty.usingPopupValue.value());
    }
    if (testProperty.popupFontValue.has_value()) {
        indexerView.SetPopupFont(testProperty.popupFontValue.value());
    }
    if (testProperty.alignStyleValue.has_value()) {
        indexerView.SetAlignStyle(testProperty.alignStyleValue.value());
    }
    if (testProperty.popupPositionXValue.has_value()) {
        indexerView.SetPopupPositionX(testProperty.popupPositionXValue.value());
    }
    if (testProperty.popupPositionYValue.has_value()) {
        indexerView.SetPopupPositionY(testProperty.popupPositionYValue.value());
    }
    if (testProperty.popupSelectedColorValue.has_value()) {
        indexerView.SetPopupSelectedColor(testProperty.popupSelectedColorValue.value());
    }
    if (testProperty.popupUnselectedColorValue.has_value()) {
        indexerView.SetPopupUnselectedColor(testProperty.popupUnselectedColorValue.value());
    }
    if (testProperty.popupItemBackgroundValue.has_value()) {
        indexerView.SetPopupItemBackground(testProperty.popupItemBackgroundValue.value());
    }
    if (testProperty.fontSizeValue.has_value()) {
        indexerView.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        indexerView.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.popupHorizontalSpaceValue.has_value()) {
        indexerView.SetPopupHorizontalSpace(testProperty.popupHorizontalSpaceValue.value());
    }
}

RefPtr<FrameNode> IndexerViewTestNg::CreateIndexerParagraph(
    const std::vector<std::string>& createArray, int32_t createSelected, const TestProperty& testProperty)
{
    IndexerView indexerView;
    indexerView.Create(createArray, createSelected);
    SetIndexerProperty(indexerView, testProperty);
    SetBubbleProperty(indexerView, testProperty);

    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

/**
 * @tc.name: IndexerViewTest001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerViewTestNg, IndexerViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.colorValue = std::make_optional(COLOR_VALUE);
    testProperty.selectedColorValue = std::make_optional(COLOR_VALUE);
    testProperty.popupColorValue = std::make_optional(COLOR_VALUE);
    testProperty.selectedBackgroundColorValue = std::make_optional(COLOR_VALUE);
    testProperty.popupBackgroundColorValue = std::make_optional(COLOR_VALUE);
    testProperty.usingPopupValue = std::make_optional(true);
    testProperty.selectedFontValue = std::make_optional(SELECTED_FONT_VALUE);
    testProperty.popupFontValue = std::make_optional(POPUP_FONT_VALUE);
    testProperty.fontValue = std::make_optional(FONT_VALUE);
    testProperty.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty.alignStyleValue = std::make_optional(ALIGN_STYLE_VALUE);
    testProperty.selectedValue = std::make_optional(SELECTED_VALUE);
    testProperty.popupPositionXValue = std::make_optional(POPUP_POSITIONX_VALUE);
    testProperty.popupPositionYValue = std::make_optional(POPUP_POSITIONY_VALUE);

    /**
     * @tc.steps: step2. create indexer frameNode and get indexerLayoutProperty.
     * @tc.expected: step2. get indexerLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    ASSERT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. compare indexer properties and expected value.
     * @tc.expected: step3. indexer properties equals expected value.
     */
    EXPECT_EQ(indexerLayoutProperty->GetArrayValue().value(), CREATE_ARRAY_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetColor().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedColor().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetPopupBackground().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetUsingPopup().value(), true);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedFont().value(), SELECTED_FONT_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupFont().value(), POPUP_FONT_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetFont().value(), FONT_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetItemSize().value(), ITEM_SIZE_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetAlignStyle().value(), ALIGN_STYLE_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), SELECTED_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionX().value(), POPUP_POSITIONX_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionY().value(), POPUP_POSITIONY_VALUE);
}

/**
 * @tc.name: IndexerViewTest002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerViewTestNg, IndexerViewTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.selectedValue = std::make_optional(SPECIAL_SELECTED_VALUE);
    testProperty.itemSizeValue = std::make_optional(SPECIAL_ITEM_SIZE_VALUE);

    /**
     * @tc.steps: step2. create indexer frameNode and get indexerLayoutProperty.
     * @tc.expected: step2. get indexerLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    ASSERT_NE(indexerLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. compare indexer properties and expected value.
     * @tc.expected: step3. indexer properties equals expected value.
     */
    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), 0);
    EXPECT_EQ(indexerLayoutProperty->GetItemSize().value(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerViewTest003
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerViewTestNg, IndexerViewTest003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.popupSelectedColorValue = std::make_optional(COLOR_VALUE);
    testProperty.popupUnselectedColorValue = std::make_optional(COLOR_VALUE);
    testProperty.popupItemBackgroundValue = std::make_optional(COLOR_VALUE);
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.popupHorizontalSpaceValue = std::make_optional(SPACE_VALUE);

    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    ASSERT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    EXPECT_EQ(paintProperty->GetPopupSelectedColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetPopupUnselectedColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetPopupItemBackground().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetFontSize().value(), FONT_SIZE_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetFontWeight().value(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(paintProperty->GetPopupHorizontalSpace().value(), SPACE_VALUE);
}

/**
 * @tc.name: IndexerViewTest004
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerViewTestNg, IndexerViewTest004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.popupHorizontalSpaceValue = std::make_optional(SPACE_INVALID_VALUE);

    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    ASSERT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetPopupHorizontalSpace().has_value(), false);
}

/**
 * @tc.name: IndexerViewTest005
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerViewTestNg, IndexerViewTest005, TestSize.Level1)
{
    std::optional<Color> invalidColor = std::nullopt;
    Dimension invalidFontSize;
    IndexerView indexerView;
    indexerView.Create(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE);
    indexerView.SetPopupSelectedColor(invalidColor);
    indexerView.SetPopupUnselectedColor(invalidColor);
    indexerView.SetPopupItemBackground(invalidColor);
    indexerView.SetFontSize(invalidFontSize);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    ASSERT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    EXPECT_FALSE(paintProperty->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty->GetPopupItemBackground().has_value());
    EXPECT_FALSE(indexerLayoutProperty->GetFontSize().has_value());
}
} // namespace OHOS::Ace::NG
