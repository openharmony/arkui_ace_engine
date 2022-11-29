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
 
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
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
constexpr int32_t CREATE_SELECTED_VALUE = 0;
constexpr int32_t SELECTED_VALUE = 0;
constexpr int32_t SPECIAL_SELECTED_VALUE = -1;
constexpr int32_t COMMON_SELECTED_VALUE = 1;
constexpr int32_t MOVE_INDEX_STEP = 1;
constexpr int32_t MOVE_INDEX_SEARCH = 1;
constexpr int32_t SPECIAL_ITEM_COUNT = 0;
constexpr Color COLOR_VALUE = Color(0x00000000);
const TextStyle SELECTED_FONT_VALUE = TextStyle();
const TextStyle POPUP_FONT_VALUE = TextStyle();
const TextStyle FONT_VALUE = TextStyle();
constexpr Dimension ITEM_SIZE_VALUE = Dimension(24.0, DimensionUnit::PX);
constexpr Dimension SPECIAL_ITEM_SIZE_VALUE = Dimension(-1, DimensionUnit::PX);
constexpr AlignStyle ALIGN_STYLE_VALUE = AlignStyle::LEFT;
constexpr float POPUP_POSITIONX_VALUE = -96.0f;
constexpr float POPUP_POSITIONY_VALUE = 48.0f;
constexpr float ITEM_SIZE_RENDER = 24.0f;
constexpr float MOVE_INDEX_OFFSET = 50.0f;
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
    return AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
}

/**
 * @tc.name: IndexerFrameNodeCreator001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator001, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    EXPECT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

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
 * @tc.name: IndexerFrameNodeCreator002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator002, TestSize.Level1)
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
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<IndexerLayoutProperty> indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    EXPECT_NE(indexerLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. compare indexer properties and expected value.
     * @tc.expected: step3. indexer properties equals expected value.
     */
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
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty.usingPopupValue = std::make_optional(true);

    /**
     * @tc.steps: step2. create indexer frameNode and get indexerLayoutProperty.
     * @tc.expected: step2. get indexerLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    
    /**
     * @tc.steps: step3. create indexer child frameNode and add to indexer.
     * @tc.expected: step3. create indexer layoutWrapper success.
     */
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
    
    /**
     * @tc.steps: step4. call indexerLayoutAlgorithm measure and layout function, compare result.
     * @tc.expected: step4. measure and layout success.
     */
    IndexerLayoutAlgorithm indexerLayoutAlgorithm = IndexerLayoutAlgorithm(0);
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
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.usingPopupValue = std::make_optional(true);
    testProperty.selectedValue = std::make_optional(COMMON_SELECTED_VALUE);
    testProperty.colorValue = std::make_optional(COLOR_VALUE);
    testProperty.selectedColorValue = std::make_optional(COLOR_VALUE);
    /**
     * @tc.steps: step2. create indexer frameNode and get indexerPattern.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    /**
     * @tc.steps: step3. call indexerPattern OnModify function, compare result.
     * @tc.expected: step3. OnModify success and result correct.
     */
    indexerPattern->OnModifyDone();
    uint32_t itemCount = CREATE_ARRAY_VALUE.size();
    for (uint32_t index = 0; index < itemCount; index++) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
        EXPECT_NE(childFrameNode, nullptr);
        if (index == COMMON_SELECTED_VALUE) {
            auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childFrameNode->GetLayoutProperty());
            EXPECT_NE(childLayoutProperty, nullptr);
        } else {
            auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childFrameNode->GetLayoutProperty());
            EXPECT_NE(childLayoutProperty, nullptr);
        }
    }
}

/**
 * @tc.name: IndexerFrameNodeCreator005
 * @tc.desc: Test indexer pattern OnDirtyLayoutWrapperSwap function. include special value.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step3. call indexerPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->isInitialized_ = false;
    indexerLayoutAlgorithm->selected_ = COMMON_SELECTED_VALUE;
    indexerLayoutAlgorithm->itemSizeRender_ = ITEM_SIZE_RENDER;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->isInitialized_, false);
    EXPECT_EQ(indexerPattern->selected_, 0);
    EXPECT_EQ(indexerPattern->itemSizeRender_, 0);
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->isInitialized_, false);
    EXPECT_EQ(indexerPattern->selected_, COMMON_SELECTED_VALUE);
    EXPECT_EQ(indexerPattern->itemSizeRender_, ITEM_SIZE_RENDER);
}

/**
 * @tc.name: IndexerFrameNodeCreator006
 * @tc.desc: Test indexer pattern MoveIndexByOffset function. include special value.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    
    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->itemSizeRender_ = 0;
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET), true);
    EXPECT_EQ(indexerPattern->selected_, 0);

    indexerPattern->itemCount_ = 0;
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET), true);
    EXPECT_EQ(indexerPattern->selected_, 0);

    indexerPattern->itemSizeRender_ = ITEM_SIZE_RENDER;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET), true);
    int32_t expectedIndex = static_cast<int32_t>(MOVE_INDEX_OFFSET / ITEM_SIZE_RENDER);
    EXPECT_EQ(expectedIndex, indexerPattern->childPressIndex_);
}

/**
 * @tc.name: IndexerFrameNodeCreator007
 * @tc.desc: Test indexer pattern MoveIndexByStep function. include special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    indexerPattern->selected_ = COMMON_SELECTED_VALUE;

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByStep function, compare result.
     * @tc.expected: step3. MoveIndexByStep success and result correct.
     */
    bool result = false;
    indexerPattern->itemCount_ = 0;
    result = indexerPattern->MoveIndexByStep(MOVE_INDEX_STEP);
    EXPECT_EQ(result, false);

    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    result = indexerPattern->MoveIndexByStep(MOVE_INDEX_STEP);
    EXPECT_EQ(indexerPattern->selected_, COMMON_SELECTED_VALUE + MOVE_INDEX_STEP);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IndexerFrameNodeCreator008
 * @tc.desc: Test indexer pattern MoveIndexBySearch function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    indexerPattern->selected_ = COMMON_SELECTED_VALUE;

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexBySearch function, compare result.
     * @tc.expected: step3. MoveIndexBySearch success and result correct.
     */
    indexerPattern->MoveIndexBySearch(CREATE_ARRAY_VALUE[MOVE_INDEX_SEARCH]);
    EXPECT_EQ(indexerPattern->selected_, MOVE_INDEX_SEARCH);
}

/**
 * @tc.name: IndexerFrameNodeCreator009
 * @tc.desc: Test indexer pattern InitOnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    
    /**
     * @tc.steps: step3. call indexerPattern InitOnKeyEvent function, compare result.
     * @tc.expected: step3. InitOnKeyEvent success and result correct.
     */
    RefPtr<FocusHub> focusHub = frameNode->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    indexerPattern->InitOnKeyEvent();
    EXPECT_NE(focusHub->onKeyEventInternal_, nullptr);
}

/**
 * @tc.name: IndexerFrameNodeCreator010
 * @tc.desc: Test indexer pattern OnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    indexerPattern->selected_ = COMMON_SELECTED_VALUE;

    /**
     * @tc.steps: step3. call indexerPattern OnKeyEvent function, compare result.
     * @tc.expected: step3. OnKeyEvent success and result correct.
     */
    KeyEvent keyEvent = KeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    bool result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, true);

    keyEvent = KeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, true);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN);
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN);
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: IndexerFrameNodeCreator011
 * @tc.desc: Test indexer algorithm Measure function and Layout function, using special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerFrameNodeCreator011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;

    /**
     * @tc.steps: step2. create indexer frameNode and get indexerLayoutProperty.
     * @tc.expected: step2. get indexerLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    
    /**
     * @tc.steps: step3. create indexer child frameNode and add to indexer.
     * @tc.expected: step3. create indexer layoutWrapper success.
     */
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
    /**
     * @tc.steps: step4. call indexerLayoutAlgorithm measure function, compare result.
     * @tc.expected: step4. measure success.
     */
    IndexerLayoutAlgorithm indexerLayoutAlgorithm = IndexerLayoutAlgorithm(0);
    indexerLayoutAlgorithm.itemCount_ = SPECIAL_ITEM_COUNT;
    indexerLayoutAlgorithm.Measure(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);

    indexerLayoutAlgorithm.itemSize_ = SPECIAL_ITEM_SIZE_VALUE.Value();
    indexerLayoutAlgorithm.Measure(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);
}
} // namespace OHOS::Ace::NG

