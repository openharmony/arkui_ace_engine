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
#include "base/geometry/dimension.h"
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
const std::vector<std::string> EMPTY_ARRAY_VALUE = {};
constexpr int32_t CREATE_SELECTED_VALUE = 0;
constexpr int32_t SELECTED_VALUE = 0;
constexpr int32_t SPECIAL_SELECTED_VALUE = -1;
constexpr int32_t COMMON_SELECTED_VALUE = 1;
constexpr int32_t LARGE_SELECTED_VALUE = 100;
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
    std::optional<Dimension> popupPositionXValue = std::nullopt;
    std::optional<Dimension> popupPositionYValue = std::nullopt;
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
 * @tc.name: IndexerViewTest001
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerViewTest001, TestSize.Level1)
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
    testProperty.popupPositionXValue = std::make_optional(Dimension(POPUP_POSITIONX_VALUE, DimensionUnit::VP));
    testProperty.popupPositionYValue = std::make_optional(Dimension(POPUP_POSITIONY_VALUE, DimensionUnit::VP));

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
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionX().value(), Dimension(POPUP_POSITIONX_VALUE, DimensionUnit::VP));
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionY().value(), Dimension(POPUP_POSITIONY_VALUE, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerViewTest002
 * @tc.desc: Test special value properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerViewTest002, TestSize.Level1)
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
 * @tc.name: IndexerPattern001
 * @tc.desc: Test indexer pattern onModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern001, TestSize.Level1)
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
 * @tc.name: IndexerPattern002
 * @tc.desc: Test indexer pattern onModifyDone function, special cases
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     * @tc.steps: case1: indexer is empty, not selected
     */
    TestProperty testProperty1;
    RefPtr<FrameNode> frameNode1 = CreateIndexerParagraph(EMPTY_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<IndexerPattern> indexerPattern1 = AceType::DynamicCast<IndexerPattern>(frameNode1->GetPattern());
    EXPECT_NE(indexerPattern1, nullptr);
    
    indexerPattern1->OnModifyDone();
    EXPECT_EQ(indexerPattern1->itemCount_, 0);

    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     * @tc.steps: case2: indexer is not empty, selected == storedSelected
     */
    TestProperty testProperty2;
    testProperty2.selectedValue = std::make_optional(SELECTED_VALUE);
    RefPtr<FrameNode> frameNode2 = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty2);
    EXPECT_NE(frameNode2, nullptr);
    RefPtr<IndexerPattern> indexerPattern2 = AceType::DynamicCast<IndexerPattern>(frameNode2->GetPattern());
    EXPECT_NE(indexerPattern2, nullptr);
    
    indexerPattern2->OnModifyDone();
    EXPECT_EQ(indexerPattern2->selected_, 0);

    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     * @tc.steps: case3: indexer is not empty, selected != storedSelected, selected > itemCount
     */
    TestProperty testProperty3;
    testProperty3.selectedValue = std::make_optional(LARGE_SELECTED_VALUE);
    RefPtr<FrameNode> frameNode3 = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty3);
    EXPECT_NE(frameNode3, nullptr);
    RefPtr<IndexerPattern> indexerPattern3 = AceType::DynamicCast<IndexerPattern>(frameNode3->GetPattern());
    EXPECT_NE(indexerPattern3, nullptr);
    
    indexerPattern3->OnModifyDone();
    EXPECT_EQ(indexerPattern3->selected_, 0);

    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     * @tc.steps: case4: set gesture
     */
    frameNode3->GetOrCreateGestureEventHub();
    indexerPattern3->OnModifyDone();
    EXPECT_EQ(indexerPattern3->selected_, 0);
    EXPECT_NE(frameNode3->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: IndexerPattern003
 * @tc.desc: Test indexer pattern OnDirtyLayoutWrapperSwap function. include special value.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern003, TestSize.Level1)
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
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = ITEM_SIZE_RENDER;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;

    /**
     * @tc.steps: step3. call indexerPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.steps: case1: skipMeasure and skipLayout
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->itemSizeRender_, 0);

    /**
     * @tc.steps: step3. call indexerPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.steps: case2: !skipMeasure and !skipLayout
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->selected_, CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerPattern->itemSizeRender_, ITEM_SIZE_RENDER);

    /**
     * @tc.steps: step3. call indexerPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.steps: case3: skipMeasure and !skipLayout
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->selected_, CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerPattern->itemSizeRender_, ITEM_SIZE_RENDER);

    /**
     * @tc.steps: step3. call indexerPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.steps: case4: !skipMeasure and skipLayout
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = true;
    indexerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(indexerPattern->selected_, CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerPattern->itemSizeRender_, ITEM_SIZE_RENDER);
}

/**
 * @tc.name: IndexerPattern004
 * @tc.desc: Test indexer pattern InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case1: no panEvent
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);
    indexerPattern->panEvent_ = nullptr;

    RefPtr<GestureEventHub> gestureEvent = frameNode->GetOrCreateGestureEventHub();
    indexerPattern->InitPanEvent(gestureEvent);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);

    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case2: have panEvent
     * @tc.expected: step2. get indexerPattern success.
     */
    indexerPattern->InitPanEvent(gestureEvent);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);
    
    /**
     * @tc.steps: step3. carry actions.
     * @tc.steps: case1: AXIS, mainDelta is 0
     * @tc.expected: step3. get indexerPattern success.
     */
    GestureEvent gestureEvent1;
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = 0;
    indexerPattern->panEvent_->actionStart_(gestureEvent1);
    indexerPattern->panEvent_->actionUpdate_(gestureEvent1);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);

    /**
     * @tc.steps: step3. carry actions.
     * @tc.steps: case2: AXIS, mainDelta is 1
     * @tc.expected: step3. get indexerPattern success.
     */
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = 1;
    indexerPattern->panEvent_->actionStart_(gestureEvent1);
    indexerPattern->panEvent_->actionUpdate_(gestureEvent1);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);

    /**
     * @tc.steps: step3. carry actions.
     * @tc.steps: case3: AXIS, mainDelta is -1
     * @tc.expected: step3. get indexerPattern success.
     */
    gestureEvent1.inputEventType_ = InputEventType::AXIS;
    gestureEvent1.mainDelta_ = -1;
    indexerPattern->panEvent_->actionStart_(gestureEvent1);
    indexerPattern->panEvent_->actionUpdate_(gestureEvent1);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);

    /**
     * @tc.steps: step3. carry actions.
     * @tc.steps: case4: KEYBOARD
     * @tc.expected: step3. get indexerPattern success.
     */
    gestureEvent1.inputEventType_ = InputEventType::KEYBOARD;
    indexerPattern->panEvent_->actionStart_(gestureEvent1);
    indexerPattern->panEvent_->actionUpdate_(gestureEvent1);
    EXPECT_NE(indexerPattern->panEvent_, nullptr);
}

/**
 * @tc.name: IndexerPattern005
 * @tc.desc: Test indexer pattern OnChildHover function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case1: isHover
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);

    indexerPattern->OnChildHover(COMMON_SELECTED_VALUE, true);
    EXPECT_EQ(indexerPattern->childHoverIndex_, COMMON_SELECTED_VALUE);
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case2: !isHover
     * @tc.expected: step2. get indexerPattern success.
     */
    indexerPattern->OnChildHover(COMMON_SELECTED_VALUE, false);
    EXPECT_EQ(indexerPattern->childHoverIndex_, -1);
}

/**
 * @tc.name: IndexerPattern006
 * @tc.desc: Test indexer pattern InitInputEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case1: isInputEventRegisted_ = false
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);

    indexerPattern->isInputEventRegisted_ = false;
    indexerPattern->InitInputEvent();
    EXPECT_EQ(indexerPattern->isInputEventRegisted_, true);
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case2: isInputEventRegisted_ = true
     * @tc.expected: step2. get indexerPattern success.
     */
    indexerPattern->InitInputEvent();
    EXPECT_EQ(indexerPattern->isInputEventRegisted_, true);
}

/**
 * @tc.name: IndexerPattern007
 * @tc.desc: Test indexer pattern InitChildInputEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    
    /**
     * @tc.steps: step2. create indexer frameNode, get indexerPattern and indexerWrapper.
     * @tc.steps: case1: isInputEventRegisted_ = false
     * @tc.expected: step2. get indexerPattern success.
     */
    RefPtr<FrameNode> frameNode = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<IndexerPattern> indexerPattern = AceType::DynamicCast<IndexerPattern>(frameNode->GetPattern());
    EXPECT_NE(indexerPattern, nullptr);

    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->InitChildInputEvent();
    EXPECT_EQ(indexerPattern->itemCount_, static_cast<int32_t>(CREATE_ARRAY_VALUE.size()));
}

/**
 * @tc.name: IndexerPattern008
 * @tc.desc: Test indexer pattern MoveIndexByOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern008, TestSize.Level1)
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
     * @tc.steps: case1: itemSizeRender is 0, return
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->itemSizeRender_ = 0;
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET));
    EXPECT_EQ(indexerPattern->childPressIndex_, -1);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.steps: case2: itemSizeRender is 1, itemCount is 0, return
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->itemSizeRender_ = 1;
    indexerPattern->itemCount_ = 0;
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET));
    EXPECT_EQ(indexerPattern->childPressIndex_, -1);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.steps: case3: itemSizeRender > 0, itemCount > 0, isRepeatCalled true, next != child
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->itemSizeRender_ = ITEM_SIZE_RENDER;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET));
    int32_t expectedIndex = static_cast<int32_t>(MOVE_INDEX_OFFSET / ITEM_SIZE_RENDER);
    EXPECT_EQ(expectedIndex, indexerPattern->childPressIndex_);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.steps: case4: itemSizeRender > 0, itemCount > 0, isRepeatCalled true, next == child
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->MoveIndexByOffset(Offset(0, 0));
    EXPECT_EQ(indexerPattern->childPressIndex_, 0);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.steps: case5: itemSizeRender > 0, itemCount > 0, isRepeatCalled false, next == child
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->MoveIndexByOffset(Offset(0, 0));
    EXPECT_EQ(indexerPattern->childPressIndex_, 0);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexByOffset function, compare result.
     * @tc.steps: case5: itemSizeRender > 0, itemCount > 0, isRepeatCalled false, next != child
     * @tc.expected: step3. MoveIndexByOffset success and result correct.
     */
    indexerPattern->MoveIndexByOffset(Offset(0, MOVE_INDEX_OFFSET));
    EXPECT_EQ(expectedIndex, indexerPattern->childPressIndex_);
}

/**
 * @tc.name: IndexerPattern009
 * @tc.desc: Test indexer pattern KeyIndexByStep function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern009, TestSize.Level1)
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
     * @tc.steps: step3. call indexerPattern KeyIndexByStep function, compare result.
     * @tc.expected: step3. KeyIndexByStep success and result correct.
     */
    bool result = false;
    indexerPattern->itemCount_ = 0;
    result = indexerPattern->KeyIndexByStep(MOVE_INDEX_STEP);
    EXPECT_EQ(result, false);

    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->selected_ = COMMON_SELECTED_VALUE;
    result = indexerPattern->KeyIndexByStep(MOVE_INDEX_STEP);
    EXPECT_EQ(indexerPattern->selected_, COMMON_SELECTED_VALUE + MOVE_INDEX_STEP);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IndexerPattern010
 * @tc.desc: Test indexer pattern GetSkipChildIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern010, TestSize.Level1)
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
     * @tc.steps: step3. call indexerPattern GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected < 0
     * @tc.expected: step3. GetSkipChildIndex success and result correct.
     */
    indexerPattern->selected_ = 0;
    auto result = indexerPattern->GetSkipChildIndex(-1);
    EXPECT_EQ(result, -1);

    /**
     * @tc.steps: step3. call indexerPattern GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected > 0, nextSelected < itemCount
     * @tc.expected: step3. GetSkipChildIndex success and result correct.
     */
    indexerPattern->selected_ = 0;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    result = indexerPattern->GetSkipChildIndex(1);
    EXPECT_EQ(result, 1);

    /**
     * @tc.steps: step3. call indexerPattern GetSkipChildIndex function, compare result.
     * @tc.steps: case1: nextSelected > itemCount
     * @tc.expected: step3. GetSkipChildIndex success and result correct.
     */
    indexerPattern->selected_ = 0;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    result = indexerPattern->GetSkipChildIndex(indexerPattern->itemCount_ + 1);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: IndexerPattern011
 * @tc.desc: Test indexer pattern MoveIndexByStep function. include special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern011, TestSize.Level1)
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
    indexerPattern->selected_ = COMMON_SELECTED_VALUE;
    result = indexerPattern->MoveIndexByStep(MOVE_INDEX_STEP);
    EXPECT_EQ(indexerPattern->selected_, COMMON_SELECTED_VALUE + MOVE_INDEX_STEP);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: IndexerPattern012
 * @tc.desc: Test indexer pattern MoveIndexBySearch function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern012, TestSize.Level1)
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
     * @tc.steps: case1: search Move_index_search
     * @tc.expected: step3. MoveIndexBySearch success and result correct.
     */
    indexerPattern->MoveIndexBySearch(CREATE_ARRAY_VALUE[MOVE_INDEX_SEARCH]);
    EXPECT_EQ(indexerPattern->selected_, MOVE_INDEX_SEARCH);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexBySearch function, compare result.
     * @tc.steps: case2: search Move_index_search + 1
     * @tc.expected: step3. MoveIndexBySearch success and result correct.
     */
    indexerPattern->MoveIndexBySearch(CREATE_ARRAY_VALUE[MOVE_INDEX_SEARCH + 1]);
    EXPECT_EQ(indexerPattern->selected_, MOVE_INDEX_SEARCH + 1);

    /**
     * @tc.steps: step3. call indexerPattern MoveIndexBySearch function, compare result.
     * @tc.steps: case2: search Move_index_search - 1
     * @tc.expected: step3. MoveIndexBySearch success and result correct.
     */
    indexerPattern->MoveIndexBySearch(CREATE_ARRAY_VALUE[MOVE_INDEX_SEARCH - 1]);
    EXPECT_EQ(indexerPattern->selected_, MOVE_INDEX_SEARCH - 1);
}

/**
 * @tc.name: IndexerPattern013
 * @tc.desc: Test indexer pattern InitOnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern013, TestSize.Level1)
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
 * @tc.name: IndexerPattern014
 * @tc.desc: Test indexer pattern OnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern014, TestSize.Level1)
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

    keyEvent = KeyEvent(KeyCode::KEY_1, KeyAction::DOWN);
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    keyEvent = KeyEvent(KeyCode::KEY_B, KeyAction::DOWN);
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    keyEvent = KeyEvent(KeyCode::KEY_B, KeyAction::DOWN);
    keyEvent.pressedCodes = {KeyCode::KEY_A, KeyCode::KEY_B};
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    keyEvent = KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN);
    keyEvent.pressedCodes = {KeyCode::KEY_A, KeyCode::KEY_B};
    result = indexerPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: IndexerPattern015
 * @tc.desc: Test indexer pattern ApplyIndexChange function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPattern015, TestSize.Level1)
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
    auto indexerEventHub = frameNode->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    
    /**
     * @tc.steps: step3. call indexerPattern ApplyIndexChange function, compare result.
     * @tc.steps: case1: have onSelected, onRequestPopupData, onPopupSelected, selected < 0
     * @tc.expected: step3. OnKeyEvent success and result correct.
     */
    indexerEventHub->SetOnSelected([](int32_t) {});
    indexerEventHub->SetOnRequestPopupData([](int32_t) {return std::vector<std::string>();});
    indexerEventHub->SetOnPopupSelected([](int32_t) {});
    indexerPattern->selected_ = -1;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->ApplyIndexChanged();
    EXPECT_EQ(indexerPattern->selected_, -1);

    /**
     * @tc.steps: step3. call indexerPattern ApplyIndexChange function, compare result.
     * @tc.steps: case2: have onSelected, onRequestPopupData, onPopupSelected, selected = 1
     * @tc.expected: step3. OnKeyEvent success and result correct.
     */
    indexerPattern->selected_ = 1;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->ApplyIndexChanged();
    EXPECT_EQ(indexerPattern->selected_, 1);

    /**
     * @tc.steps: step3. call indexerPattern ApplyIndexChange function, compare result.
     * @tc.steps: case3: have onSelected, onRequestPopupData, onPopupSelected, selected > size
     * @tc.expected: step3. OnKeyEvent success and result correct.
     */
    indexerPattern->selected_ = CREATE_ARRAY_VALUE.size() + 1;
    indexerPattern->itemCount_ = CREATE_ARRAY_VALUE.size();
    indexerPattern->ApplyIndexChanged();
    EXPECT_NE(indexerPattern->selected_, 1);
}

/**
 * @tc.name: IndexerAlgorithmTest001
 * @tc.desc: Test indexer algorithm Measure function and Layout function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerAlgorithmTest001, TestSize.Level1)
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
        EXPECT_EQ(childFrameOffset.GetY(), 0);
    }
}

/**
 * @tc.name: IndexerAlgorithmTest002
 * @tc.desc: Test indexer algorithm Measure function and Layout function, using special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerAlgorithmTest002, TestSize.Level1)
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

/**
 * @tc.name: IndexerAlgorithmTest003
 * @tc.desc: Test indexer algorithm Layout function, using special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.popupPositionXValue = std::make_optional(Dimension(POPUP_POSITIONX_VALUE, DimensionUnit::VP));
    testProperty.popupPositionYValue = std::make_optional(Dimension(POPUP_POSITIONY_VALUE, DimensionUnit::VP));

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
    geometryNode->SetFrameSize(SizeF(1, 1));
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    
    /**
     * @tc.steps: step4. call indexerLayoutAlgorithm layout function, compare result.
     * @tc.expected: step4. layout success.
     */
    IndexerLayoutAlgorithm indexerLayoutAlgorithm = IndexerLayoutAlgorithm(0);
    
    indexerLayoutAlgorithm.itemSize_ = 0;
    indexerLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);

    indexerLayoutAlgorithm.itemSize_ = CREATE_ARRAY_VALUE.size();
    indexerLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);
    indexerLayoutAlgorithm.Layout(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);
}

/**
 * @tc.name: IndexerAlgorithmTest004
 * @tc.desc: Test indexer algorithm Measure function, using special case.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty;
    testProperty.popupPositionXValue = std::make_optional(Dimension(POPUP_POSITIONX_VALUE, DimensionUnit::VP));
    testProperty.popupPositionYValue = std::make_optional(Dimension(POPUP_POSITIONY_VALUE, DimensionUnit::VP));
    testProperty.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty.usingPopupValue = false;

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
    IndexerLayoutAlgorithm indexerLayoutAlgorithm = IndexerLayoutAlgorithm(0);

    /**
     * @tc.steps: step4. call indexerLayoutAlgorithm measure function, compare result.
     * @tc.steps: case1: no idealSize
     * @tc.expected: step4. layout success.
     */
    indexerLayoutAlgorithm.Measure(&layoutWrapper);
    EXPECT_EQ(indexerLayoutAlgorithm.itemSizeRender_, 0);

    /**
     * @tc.steps: step1. create testProperty and set properties of indexer.
     */
    TestProperty testProperty1;
    testProperty1.popupPositionXValue = std::make_optional(Dimension(POPUP_POSITIONX_VALUE, DimensionUnit::VP));
    testProperty1.popupPositionYValue = std::make_optional(Dimension(POPUP_POSITIONY_VALUE, DimensionUnit::VP));
    testProperty1.itemSizeValue = std::make_optional(ITEM_SIZE_VALUE);
    testProperty1.usingPopupValue = true;

    /**
     * @tc.steps: step2. create indexer frameNode and get indexerLayoutProperty.
     * @tc.expected: step2. get indexerLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode1 = CreateIndexerParagraph(CREATE_ARRAY_VALUE, CREATE_SELECTED_VALUE, testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode1, nullptr);
    RefPtr<LayoutProperty> layoutProperty1 = frameNode1->GetLayoutProperty();
    EXPECT_NE(layoutProperty1, nullptr);
    LayoutWrapper layoutWrapper1 = LayoutWrapper(frameNode1, geometryNode1, layoutProperty1);
    IndexerLayoutAlgorithm indexerLayoutAlgorithm1 = IndexerLayoutAlgorithm(0);

    /**
     * @tc.steps: step4. call indexerLayoutAlgorithm measure function, compare result.
     * @tc.steps: case1: no idealSize
     * @tc.expected: step4. layout success.
     */
    indexerLayoutAlgorithm1.Measure(&layoutWrapper1);
    EXPECT_EQ(indexerLayoutAlgorithm1.itemSizeRender_, 0);
}
} // namespace OHOS::Ace::NG

