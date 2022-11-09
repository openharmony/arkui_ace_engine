/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#define private public

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::vector<std::string> CREATE_ARRAY_VALUE = {"A", "B", "C", "D", "E", "F", "G", "H",
    "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
const int32_t CREATE_SELECTED_VALUE = 0;
const Color COLOR_VALUE = Color::RED;
const Color SELECTED_COLOR_VALUE = Color::RED;
const Color POPUP_COLOR_VALUE = Color::RED;
const Color SELECTED_BACKGROUND_COLOR_VALUE = Color::WHITE;
const Color POPUP_BACKGROUND_COLOR_VALUE = Color::WHITE;
const bool USING_POPUP_VALUE = true;
const TextStyle SELECTED_FONT_VALUE = TextStyle();
const TextStyle POPUP_FONT_VALUE = TextStyle();
const TextStyle FONT_VALUE = TextStyle();
const Dimension ITEM_SIZE_VALUE = Dimension(24.0, DimensionUnit::PX);
const AlignStyle ALIGN_STYLE_VALUE = AlignStyle::LEFT;
const int32_t SELECTED_VALUE = 0;
const float POPUP_POSITIONX_VALUE = -96.0f;
const float POPUP_POSITIONY_VALUE = 48.0f;

const Dimension SPECIAL_ITEM_SIZE_VALUE = Dimension(-1, DimensionUnit::PX);
const int32_t SPECIAL_SELECTED_VALUE = -1;
const int32_t COMMON_SELECTED_VALUE = 1;
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
};

class IndexerPatternTestNg : public testing::Test {
public:
    static RefPtr<FrameNode> CreateIndexerParagraph(const std::vector<std::string> createArray,
        const int32_t createSelected, const TestProperty& testProperty);
};

RefPtr<FrameNode> IndexerPatternTestNg::CreateIndexerParagraph(
    const std::vector<std::string> createArray, const int32_t createSelected, const TestProperty& testProperty)
{
    IndexerView indexerView;
    indexerView.Create(createArray, createSelected);
    if (testProperty.colorValue.has_value()) {
        indexerView.SetColor(testProperty.colorValue.value());
    }
    if (testProperty.selectedColorValue.has_value()) {
        indexerView.SetSelectedColor(testProperty.selectedColorValue.value());
    }
    if (testProperty.popupColorValue.has_value()) {
        indexerView.SetPopupColor(testProperty.popupColorValue.value());
    }
    if (testProperty.selectedBackgroundColorValue.has_value()) {
        indexerView.SetSelectedBackgroundColor(testProperty.selectedBackgroundColorValue.value());
    }
    if (testProperty.popupBackgroundColorValue.has_value()) {
        indexerView.SetPopupBackground(testProperty.popupBackgroundColorValue.value());
    }
    if (testProperty.usingPopupValue.has_value()) {
        indexerView.SetUsingPopup(testProperty.usingPopupValue.value());
    }
    if (testProperty.selectedFontValue.has_value()) {
        indexerView.SetSelectedFont(testProperty.selectedFontValue.value());
    }
    if (testProperty.popupFontValue.has_value()) {
        indexerView.SetPopupFont(testProperty.popupFontValue.value());
    }
    if (testProperty.fontValue.has_value()) {
        indexerView.SetFont(testProperty.fontValue.value());
    }
    if (testProperty.itemSizeValue.has_value()) {
        indexerView.SetItemSize(testProperty.itemSizeValue.value());
    }
    if (testProperty.alignStyleValue.has_value()) {
        indexerView.SetAlignStyle(testProperty.alignStyleValue.value());
    }
    if (testProperty.selectedValue.has_value()) {
        indexerView.SetSelected(testProperty.selectedValue.value());
    }
    if (testProperty.popupPositionXValue.has_value()) {
        indexerView.SetPopupPositionX(testProperty.popupPositionXValue.value());
    }
    if (testProperty.popupPositionYValue.has_value()) {
        indexerView.SetPopupPositionY(testProperty.popupPositionYValue.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: IndexerFrameNodeCreator001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.colorValue = std::make_optional(COLOR_VALUE);
    testProperty.selectedColorValue = std::make_optional(SELECTED_COLOR_VALUE);
    testProperty.popupColorValue = std::make_optional(POPUP_COLOR_VALUE);
    testProperty.selectedBackgroundColorValue = std::make_optional(SELECTED_BACKGROUND_COLOR_VALUE);
    testProperty.popupBackgroundColorValue = std::make_optional(POPUP_BACKGROUND_COLOR_VALUE);
    testProperty.usingPopupValue = std::make_optional(USING_POPUP_VALUE);
    testProperty.selectedFontValue = std::make_optional(SELECTED_FONT_VALUE);
    testProperty.popupFontValue = std::make_optional(POPUP_FONT_VALUE);
    testProperty.fontValue = std::make_optional(FONT_VALUE);
    testProperty.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty.alignStyleValue = std::make_optional(ALIGN_STYLE_VALUE);
    testProperty.selectedValue = std::make_optional(SELECTED_VALUE);
    testProperty.popupPositionXValue = std::make_optional(POPUP_POSITIONX_VALUE);
    testProperty.popupPositionYValue = std::make_optional(POPUP_POSITIONY_VALUE);

    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    EXPECT_NE(indexerLayoutProperty, nullptr);

    EXPECT_EQ(indexerLayoutProperty->GetArrayValue().value(), CREATE_ARRAY_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetColor().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedColor().value(), SELECTED_COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupColor().value(), POPUP_COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedBackgroundColor().value(), SELECTED_BACKGROUND_COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupBackground().value(), POPUP_BACKGROUND_COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetUsingPopup().value(), USING_POPUP_VALUE);
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
 * @tc.name: IndexerFrameNodeCreator002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.selectedValue = std::make_optional(SPECIAL_SELECTED_VALUE);
    testProperty.itemSizeValue = std::make_optional(SPECIAL_ITEM_SIZE_VALUE);

    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    EXPECT_NE(indexerLayoutProperty, nullptr);

    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), 0);
    EXPECT_EQ(indexerLayoutProperty->GetItemSize().value(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerFrameNodeCreator003
 * @tc.desc: Test indexer algorithm Measure function and Layout function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty.usingPopupValue = std::make_optional(USING_POPUP_VALUE);

    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    
    int32_t itemCount = CREATE_ARRAY_VALUE.size();
    for (int32_t index = 0; index < itemCount; index++) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
        EXPECT_NE(childFrameNode, nullptr);
        auto childGeometryNode = childFrameNode->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(childFrameNode,
            childGeometryNode, childLayoutProperty);
        EXPECT_NE(childLayoutWrapper, nullptr);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }
    
    IndexerLayoutAlgorithm indexerLayoutAlgorithm = IndexerLayoutAlgorithm();
    indexerLayoutAlgorithm.Measure(&layoutWrapper);
    indexerLayoutAlgorithm.Layout(&layoutWrapper);

    for (int32_t index = 0; index < itemCount; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        EXPECT_NE(childWrapper, nullptr);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        OffsetF childFrameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(childFrameOffset.GetX(), 0);
        EXPECT_EQ(childFrameOffset.GetY(), index * ITEM_SIZE_VALUE.Value());
    }
}

/**
 * @tc.name: IndexerFrameNodeCreator004
 * @tc.desc: Test indexer pattern onModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.usingPopupValue = std::make_optional(USING_POPUP_VALUE);
    testProperty.selectedValue = std::make_optional(COMMON_SELECTED_VALUE);
    testProperty.colorValue = std::make_optional(COLOR_VALUE);
    testProperty.selectedColorValue = std::make_optional(SELECTED_COLOR_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);

    indexerPattern->OnModifyDone();

    int32_t itemCount = CREATE_ARRAY_VALUE.size();
    for (int32_t index = 0; index < itemCount; index++) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
        EXPECT_NE(childFrameNode, nullptr);
        if (index == COMMON_SELECTED_VALUE) {
            auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childFrameNode->GetLayoutProperty());
            EXPECT_NE(childLayoutProperty, nullptr);
            EXPECT_EQ(childLayoutProperty->GetTextColor().value(), SELECTED_COLOR_VALUE);
        } else {
            auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childFrameNode->GetLayoutProperty());
            EXPECT_NE(childLayoutProperty, nullptr);
            EXPECT_EQ(childLayoutProperty->GetTextColor().value(), COLOR_VALUE);
        }
    }
}
} // namespace OHOS::Ace::NG

