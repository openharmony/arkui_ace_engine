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

#include "grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class GridLayoutTestNg : public GridTestNg {
public:
    void UpdateLayoutInfo();
    void UpdateLayoutWrapper(RefPtr<FrameNode>& frameNode, float width = GRID_WIDTH, float height = GRID_HEIGHT);
};

void GridLayoutTestNg::UpdateLayoutInfo()
{
    GetInstance();
    FlushLayoutTask(frameNode_);
    pattern_->gridLayoutInfo_.lineHeightMap_[0] = ITEM_HEIGHT;
    pattern_->gridLayoutInfo_.gridMatrix_[0][0] = 0;
    pattern_->gridLayoutInfo_.gridMatrix_[0][1] = 1;
    pattern_->gridLayoutInfo_.gridMatrix_[1][0] = 0;
    pattern_->gridLayoutInfo_.gridMatrix_[1][1] = 1;
}

void GridLayoutTestNg::UpdateLayoutWrapper(RefPtr<FrameNode>& frameNode, float width, float height)
{
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { GRID_WIDTH, GRID_HEIGHT };
    LayoutConstraint.percentReference = { GRID_WIDTH, GRID_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, height };
    LayoutConstraint.maxSize = { width, GRID_HEIGHT };
    frameNode->Measure(LayoutConstraint);
    frameNode->Layout();
}

/**
 * @tc.name: GridPaintMethodTest001
 * @tc.desc: Test grid paint method GetForegroundDrawFunction function
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridPaintMethodTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(10);
    });
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    drawFunction(rsCanvas);
    paintMethod = nullptr;
    drawFunction(rsCanvas);

    /**
     * @tc.steps: step1. When EdgeEffect::SPRING
     * @tc.expected: CreateNodePaintMethod would not trigger SetEdgeEffect
     */
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_EQ(paintMethod->edgeEffect_.Upgrade(), nullptr);

    /**
     * @tc.steps: step2. When EdgeEffect::FADE
     * @tc.expected: CreateNodePaintMethod would trigger SetEdgeEffect
     */
    pattern_->SetEdgeEffect(EdgeEffect::FADE);
    paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_NE(paintMethod->edgeEffect_.Upgrade(), nullptr);
}

/**
 * @tc.name: ScrollLayout001
 * @tc.desc: Test UpdateOffsetOnVirtualKeyboardHeightChange
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, ScrollLayout001, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, GRID_HEIGHT + ITEM_HEIGHT);
    textFieldManager->SetClickPosition(clickPosition);

    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetMaxCount(2);
        CreateColItem(18);
    });
    const float smallerHeight = GRID_HEIGHT - ITEM_HEIGHT;
    RectF gridRect(0.f, 0.f, GRID_WIDTH, smallerHeight);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->rect_ = gridRect;

    /**
     * @tc.steps: step1. Change to smaller mainSize
     * @tc.expected: The mainSize is correct
     */
    auto gridFocus = frameNode_->GetOrCreateFocusHub();
    gridFocus->RequestFocusImmediately();
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, smallerHeight);
    float gridHeight = frameNode_->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_FLOAT_EQ(gridHeight, smallerHeight);
}

/**
 * @tc.name: ScrollLayout002
 * @tc.desc: Test UpdateOffsetOnVirtualKeyboardHeightChange that currentOffset wuold not change
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, ScrollLayout002, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, 100.f);
    textFieldManager->SetClickPosition(clickPosition);

    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetMaxCount(2);
        CreateColItem(18);
    });

    /**
     * @tc.steps: step1. While axis_ == Axis::HORIZONTAL
     * @tc.expected: currentOffset_ would not change
     */
    pattern_->gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
    const float smallerHeight = GRID_HEIGHT - ITEM_HEIGHT;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, smallerHeight);
    float currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step2. While Grid !IsCurrentFocus()
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);

    /**
     * @tc.steps: step3. While clickPosition is in Grid
     * @tc.expected: currentOffset_ would not change
     */
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, GRID_HEIGHT); // reset Grid height
    pattern_->gridLayoutInfo_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    UpdateLayoutWrapper(frameNode_, GRID_WIDTH, smallerHeight);
    currentOffset = pattern_->gridLayoutInfo_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0.f);
}

/**
 * @tc.name: AdaptiveLayout001
 * @tc.desc: Test property AdaptiveLayout
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, AdaptiveLayout001, TestSize.Level1)
{
    float itemWidth = 100.f;
    Create([itemWidth](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetEditable(true);
        model.SetCellLength(ITEM_HEIGHT);
        model.SetMinCount(4);
        model.SetMaxCount(2);
        CreateItem(10, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. While the before set minCount > maxCount
     * @tc.expected: would let minCount = 1, maxCount = Infinity;
     */
    int32_t colsNumber = 4; // 4 * 100(itemWidth) < 480(gridWidth)
    for (int32_t index = 0; index < 10; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * itemWidth;
        float offsetY = floor(index / colsNumber) * ITEM_HEIGHT;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: GridScrollTest001
 * @tc.desc: Test FireOnScrollBarUpdate Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
            std::optional<float> horizontalOffset = offset.ConvertToPx();
            std::optional<float> verticalOffset = offset.ConvertToPx();
            return std::make_pair(horizontalOffset, verticalOffset);
        };
        model.SetRowsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
        model.SetOnScrollBarUpdate(std::move(scrollFunc));
        CreateBigItem(1, 1, 1, 2);
        CreateColItem(2);
    });
    Dimension offset(1.0);
    auto fireOnScroll = eventHub_->FireOnScrollBarUpdate(1.0, offset);
    EXPECT_FLOAT_EQ(fireOnScroll.first.value(), 1.0f);
    EXPECT_FLOAT_EQ(fireOnScroll.second.value(), 1.0f);
}

/**
 * @tc.name: GridScrollTest002
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto ret = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(100, 100), 0, 1, 0);
    EXPECT_EQ(ret.GetY(), 100.f - ITEM_HEIGHT);
    EXPECT_EQ(ret.GetX(), 100.f);
}

/**
 * @tc.name: GridScrollTest003
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    CreateColItem(10);
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto ret = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(0, 100), 1, 1, 0);
    EXPECT_EQ(ret.GetY(), 100.0f);
    EXPECT_EQ(ret.GetX(), 0.0f);
}

/**
 * @tc.name: GridScrollTest004
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create girdItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(GRID_WIDTH));
    ViewAbstract::SetHeight(CalcLength(GRID_HEIGHT));
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->gridLayoutInfo_, 2, 0);
    auto ret1 = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(0, 100), 1, 1, 0);
    EXPECT_EQ(ret1.GetY(), 100.0f);
    EXPECT_EQ(ret1.GetX(), 0.0f);
}

/**
 * @tc.name: GridScrollTest005
 * @tc.desc: Test AdjustRowColSpan Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest005, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        itemModel.SetRowStart(NULL_VALUE);
        itemModel.SetRowEnd(NULL_VALUE);
        itemModel.SetColumnStart(NULL_VALUE);
        itemModel.SetColumnEnd(NULL_VALUE);
        ViewStackProcessor::GetInstance()->Pop();
    });
    auto layoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 0);
    EXPECT_EQ(layoutProperty->GetRowStart(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetRowEnd(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetColumnStart(), NULL_VALUE);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), NULL_VALUE);
}

/**
 * @tc.name: GetTotalHeight001
 * @tc.desc: Test GetTotalHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GetTotalHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(10);
    });
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_HEIGHT * 3);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(20);
    });
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_HEIGHT * 5);
}

/**
 * @tc.name: GetAverageHeight001
 * @tc.desc: Test GetAverageHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GetAverageHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(10);
    });
    EXPECT_EQ(pattern_->GetAverageHeight(), 60);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(20);
    });
    EXPECT_EQ(pattern_->GetAverageHeight(), 50);
}

/**
 * @tc.name: GridItemDisableEventTest001
 * @tc.desc: GirdItem disable event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridItemDisableEventTest001, TestSize.Level1)
{
    Create([](GridModelNG model) { CreateColItem(10, GridItemStyle::PLAIN); });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemEventHub = GetChildEventHub<GridItemEventHub>(frameNode_, 0);
    EXPECT_FALSE(gridItemPattern->enableOpacity_.has_value());
    gridItemEventHub->SetEnabled(false);
    gridItemPattern->InitDisableStyle();
    gridItemEventHub->SetEnabled(true);
    gridItemPattern->InitDisableStyle();
    EXPECT_FALSE(gridItemPattern->enableOpacity_.has_value());
}

/**
 * @tc.name: GridItemGetInnerFocusPaintRectTest001
 * @tc.desc: GirdItem GetInnerFocusPaintRect test.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridItemGetInnerFocusPaintRectTest001, TestSize.Level1)
{
    Create([](GridModelNG model) { CreateColItem(10); });
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step1. Set paintRect when grid item does not have border radius.
     * @tc.expected: Focus border radius is equal to 4.0_vp.
     */
    RoundRect paintRect;
    gridItemPattern->GetInnerFocusPaintRect(paintRect);
    EdgeF radius = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    float expectRadius = GRIDITEM_FOCUS_INTERVAL.ConvertToPx();
    EXPECT_EQ(radius.x, expectRadius);
    EXPECT_EQ(radius.y, expectRadius);

    /**
     * @tc.steps: step2. Set paintRect when grid item has border radius.
     * @tc.expected: Focus border radius is equal to 11.0_vp.
     */
    auto renderContext = gridItemNode->GetRenderContext();
    renderContext->UpdateBorderRadius({ BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS });
    gridItemPattern->GetInnerFocusPaintRect(paintRect);
    radius = paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    expectRadius = (GRIDITEM_FOCUS_INTERVAL + BORDER_RADIUS).ConvertToPx();
    EXPECT_EQ(radius.x, expectRadius);
    EXPECT_EQ(radius.y, expectRadius);
}

/**
 * @tc.name: GridScrollWithOptions001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize;
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateColItem(10);
    });

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    layoutAlgorithm->GetTargetIndexInfoWithBenchMark(AccessibilityManager::RawPtr(frameNode_), false, 5);
    EXPECT_EQ(layoutAlgorithm->gridLayoutInfo_.startMainLineIndex_, 1);
}

/**
 * @tc.name: GridScrollWithOptions002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    Create([option](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    layoutAlgorithm->GetTargetIndexInfoWithBenchMark(AccessibilityManager::RawPtr(frameNode_), false, 5);
    EXPECT_EQ(layoutAlgorithm->gridLayoutInfo_.startMainLineIndex_, 5);
}

/**
 * @tc.name: GridScrollWithOptions003
 * @tc.desc: change grid columns after scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions003, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });
    pattern_->UpdateStartIndex(3);
    FlushLayoutTask(frameNode_);
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    FlushLayoutTask(frameNode_);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(0, 2));
}

/**
 * @tc.name: GridScrollWithOptions004
 * @tc.desc: change grid columns after scroll, first line has empty position
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions004, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });
    pattern_->UpdateStartIndex(3);
    FlushLayoutTask(frameNode_);
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    FlushLayoutTask(frameNode_);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(0, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(2, option, 1), std::make_pair(3, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(1, option, 1), std::make_pair(1, 2));
}

/**
 * @tc.name: GridScrollWithOptions005
 * @tc.desc: second line full
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions005, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(3, option, 1), std::make_pair(2, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(2, option, 1), std::make_pair(0, 2));
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(1, option, 1), std::make_pair(1, 2));
}

/**
 * @tc.name: GridScrollWithOptions006
 * @tc.desc: first irregular item in new line
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollWithOptions006, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 3, 4, 5 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_EQ(layoutAlgorithm->GetCrossStartAndSpanWithUserFunction(4, option, 1), std::make_pair(2, 2));
}

/**
 * @tc.name: SearchIrregularFocusableChildInScroll001
 * @tc.desc: Test the function when the gridItem cannot be focused
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SearchIrregularFocusableChildInScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in scroll grid.
     */
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    Create([option](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can not find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SearchIrregularFocusableChildInScroll002
 * @tc.desc: Test the function when the gridItem can be focused
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SearchIrregularFocusableChildInScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in scroll grid.
     */
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5, 0 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG gridModelNG) {
        gridModelNG.SetRowsTemplate("1fr 1fr 1fr 1fr");
        gridModelNG.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can not find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. Call the function when isLeftStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    tarCrossIndex = 0;
    pattern_->isLeftStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isLeftStep_ = false;

    /**
     * @tc.steps: step4. Call the function when isRightStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isRightStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isRightStep_ = false;

    /**
     * @tc.steps: step5. Call the function when isUpStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isUpStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isUpStep_ = false;

    /**
     * @tc.steps: step6. Call the function when isDownStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isDownStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isDownStep_ = false;

    /**
     * @tc.steps: step7. Call the function when isLeftEndStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isLeftEndStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isLeftEndStep_ = false;

    /**
     * @tc.steps: step8. Call the function when isRightEndStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isRightEndStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isRightEndStep_ = false;
}

/**
 * @tc.name: SearchIrregularFocusableChildInNormalGrid001
 * @tc.desc: Test ability of a fixed shape grid to obtain irregular shape focal item.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SearchIrregularFocusableChildInNormalGrid001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItems with irregular shape in fixed shape grid.
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, 1, 2);
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step2. Find target child with specified index parameters.
     * @tc.expected: Can find the target focus child.
     */
    int32_t tarMainIndex = 1;
    int32_t tarCrossIndex = 1;
    pattern_->isLeftStep_ = true;
    auto IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    RefPtr<FocusHub> result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isLeftStep_ = false;

    /**
     * @tc.steps: step3. Call the function when isRightStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isRightStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isRightStep_ = false;

    /**
     * @tc.steps: step4. Call the function when isUpStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isUpStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isUpStep_ = false;

    /**
     * @tc.steps: step5. Call the function when isDownStep_ is true.
     * @tc.expected: Can find the target focus child.
     */
    pattern_->isDownStep_ = true;
    IrregularFocusableChild = pattern_->SearchIrregularFocusableChild(tarMainIndex, tarCrossIndex);
    result = IrregularFocusableChild.Upgrade();
    EXPECT_NE(result, nullptr);
    pattern_->isDownStep_ = false;
}

/**
 * @tc.name: GridPattern_GetItemRect001
 * @tc.desc: Test the GetItemRect function of Grid.
 * @tc.type: FUNCgetitemre
 */
HWTEST_F(GridLayoutTestNg, GridPattern_GetItemRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Grid then slide Grid by Scroller.
     */
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 1, 3 };
    auto onGetIrregularSizeByIndex = [](int32_t index) {
        GridItemSize gridItemSize { 1, 2 };
        return gridItemSize;
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(option);
        CreateColItem(10);
    });
    pattern_->UpdateStartIndex(3, ScrollAlign::START);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid GridItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(10), Rect()));

    /**
     * @tc.steps: step3. Get valid GridItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, 0, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(4), Rect(0, ITEM_HEIGHT, GRID_WIDTH / 2, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(7), Rect(GRID_WIDTH / 2, ITEM_HEIGHT * 2, GRID_WIDTH / 2, ITEM_HEIGHT)));

    /**
     * @tc.steps: step4. Slide Grid by Scroller.
     */
    UpdateCurrentOffset(ITEM_HEIGHT + ITEM_HEIGHT / 2);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Get invalid GridItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(10), Rect()));

    /**
     * @tc.steps: step6. Get valid GridItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(0, -ITEM_HEIGHT / 2, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(0, ITEM_HEIGHT / 2, GRID_WIDTH / 2, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, ITEM_HEIGHT + ITEM_HEIGHT / 2, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(5),
        Rect(GRID_WIDTH / 2, ITEM_HEIGHT * 2 + ITEM_HEIGHT / 2, GRID_WIDTH / 2, ITEM_HEIGHT)));
}

/**
 * @tc.name: ChangeItemNumber001
 * @tc.desc: Test ChangeItemNumber
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, ChangeItemNumber001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(5);
    });

    /**
     * @tc.steps: step1. Add item
     * @tc.expected: The added item in the correct position
     */
    for (int32_t i = 0; i < 4; i++) {
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 6), OffsetF(ITEM_WIDTH * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 8), OffsetF(0, ITEM_HEIGHT * 2)));
}

/**
 * @tc.name: ItemAboveViewport001
 * @tc.desc: Test GridLayoutInfo::ItemAboveViewport
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, ItemAboveViewport001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 500.0f }, { 2, 300.0f } };
    info.crossCount_ = 2;

    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 0;
    info.endIndex_ = 5;

    info.currentOffset_ = 0.0f;
    EXPECT_FALSE(info.ItemAboveViewport(1, 5.0f));

    info.currentOffset_ = -50.0f;
    EXPECT_TRUE(info.ItemAboveViewport(1, 5.0f));

    info.currentOffset_ = -200.0f;
    EXPECT_TRUE(info.ItemAboveViewport(1, 5.0f));
    EXPECT_FALSE(info.ItemAboveViewport(2, 5.0f));

    // adding gap length
    info.currentOffset_ = -205.0f;
    EXPECT_TRUE(info.ItemAboveViewport(1, 5.0f));
    EXPECT_FALSE(info.ItemAboveViewport(2, 5.0f));

    EXPECT_TRUE(info.ItemAboveViewport(2, 0.0f));

    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 2;
    info.endIndex_ = 3;

    info.currentOffset_ = 0.0f;
    EXPECT_FALSE(info.ItemAboveViewport(2, 5.0f));

    info.currentOffset_ = -1.0f;
    EXPECT_TRUE(info.ItemAboveViewport(3, 5.0f));
}

/**
 * @tc.name: ItemBelowViewport001
 * @tc.desc: Test GridLayoutInfo::ItemBelowViewport
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, ItemBelowViewport001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, -1 } } },
    };
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 500.0f }, { 2, 300.0f } };
    info.crossCount_ = 2;

    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 0;
    info.endIndex_ = 4;

    info.currentOffset_ = 0.0f;
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 100.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 700.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 705.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 710.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 1005.0f, 5.0f));
    EXPECT_FALSE(info.ItemBelowViewport(3, 2, 1010.0f, 5.0f));

    info.currentOffset_ = -50.0f;
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 100.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 700.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 705.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 710.0f, 5.0f));
    EXPECT_TRUE(info.ItemBelowViewport(3, 2, 955.0f, 5.0f));
    EXPECT_FALSE(info.ItemBelowViewport(3, 2, 960.0f, 5.0f));
    EXPECT_FALSE(info.ItemBelowViewport(3, 2, 1005.0f, 5.0f));
    EXPECT_FALSE(info.ItemBelowViewport(3, 2, 1010.0f, 5.0f));
}

/**
 * @tc.name: UpdateGridMatrix001
 * @tc.desc: Test UpdateGridMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, UpdateGridMatrix001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 100 items
     * @tc.expected: The added item in the correct position
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateRowItem(100);
    });

    /**
     * @tc.steps: step2. Scroll To 99 item
     * @tc.expected: Scroll to the correct position,lineHeightMap_ size is 25
     */
    pattern_->ScrollToIndex(99, true, ScrollAlign::END);
    EXPECT_TRUE(IsEqual<int32_t>(pattern_->gridLayoutInfo_.lineHeightMap_.size(), 25));
}

/**
 * @tc.name: IrregularFiller::AdvancePos001
 * @tc.desc: Test IrregularFiller::AdvancePos
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, AdvancePos001, TestSize.Level1)
{
    // empty matrix
    GridLayoutInfo info;
    info.crossCount_ = 2;
    GridIrregularFiller filler(&info, nullptr);
    EXPECT_FALSE(filler.AdvancePos());

    filler.posX_ = 1;
    filler.posY_ = 0;
    EXPECT_FALSE(filler.AdvancePos());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 1);

    // init matrix
    info.gridMatrix_[0][0] = 1;
    info.gridMatrix_[0][1] = -1;
    info.gridMatrix_[1][0] = -1;
    EXPECT_FALSE(filler.AdvancePos());
    EXPECT_EQ(filler.posX_, 1);
    EXPECT_EQ(filler.posY_, 1);

    // reset pos and make [1][1] available
    filler.posX_ = 0;
    filler.posY_ = 1;
    info.gridMatrix_[1][1] = -1;
    EXPECT_TRUE(filler.AdvancePos());
}

/**
 * @tc.name: IrregularFiller::FindNextItem001
 * @tc.desc: Test IrregularFiller::FindNextItem
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, FindNextItem001, TestSize.Level1)
{
    // empty matrix
    GridLayoutInfo info;
    info.crossCount_ = 2;
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_FALSE(filler.FindNextItem(0));
    }

    info.gridMatrix_[0][0] = 1;
    info.gridMatrix_[0][1] = 2;
    info.gridMatrix_[1][0] = 3;
    info.gridMatrix_[1][1] = -1;
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_TRUE(filler.FindNextItem(1));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(2));
        EXPECT_EQ(filler.posX_, 1);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(3));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 1);

        EXPECT_FALSE(filler.FindNextItem(4));
    }

    info.gridMatrix_[0][1] = -1;
    info.gridMatrix_[1][0] = 2;
    info.gridMatrix_[1].erase(1);
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_TRUE(filler.FindNextItem(1));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(2));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 1);

        EXPECT_FALSE(filler.FindNextItem(3));
        EXPECT_EQ(filler.posX_, 1);
        EXPECT_EQ(filler.posY_, 1);
    }
}

/**
 * @tc.name: IrregularFiller::UpdateLength001
 * @tc.desc: Test IrregularFiller::UpdateLength
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, UpdateLength001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_[0] = 50.0f;
    info.lineHeightMap_[1] = 30.0f;

    GridIrregularFiller filler(&info, nullptr);
    float len = 0.0f;
    filler.UpdateLength(len, 0, 2, 5.0f);
    EXPECT_EQ(len, 85.0f);

    info.lineHeightMap_[2] = 50.0f;
    filler.UpdateLength(len, 2, 3, 10.0f);
    EXPECT_EQ(len, 85.0f + 50.0f + 10.0f);
}

/**
 * @tc.name: LayoutUtils::GetItemSize001
 * @tc.desc: Test LayoutUtils::GetItemSize
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GetItemSize001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        1, // [1 x 2]
        2  // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    auto* wrapper = AceType::RawPtr(frameNode_);

    info.crossCount_ = 2;
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).columns, 2);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).rows, 2);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).columns, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).columns, 2);

    info.axis_ = Axis::HORIZONTAL;
    // rows and columns should be flipped when horizontal
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).rows, 2);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).columns, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).columns, 2);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).rows, 2);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).columns, 1);
}

/**
 * @tc.name: LayoutUtils::GetItemSize002
 * @tc.desc: Test LayoutUtils::GetItemSize with null callback
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GetItemSize002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        1, // [1 x 2]
        2  // [2 x 1]
    };
    option.getSizeByIndex = nullptr;

    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    auto* wrapper = AceType::RawPtr(frameNode_);
    info.crossCount_ = 3;

    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 0).columns, 3);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 1).columns, 3);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).rows, 1);
    EXPECT_EQ(GridLayoutUtils::GetItemSize(&info, wrapper, 2).columns, 3);
}

/**
 * @tc.name: IrregularFiller::FillOne001
 * @tc.desc: Test IrregularFiller::FillOne
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, FillOne001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        1, // [1 x 2]
        2  // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 2;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    info.endIndex_ = 0;
    filler.FillOne();
    EXPECT_EQ(info.gridMatrix_.at(0).at(0), 0);
    EXPECT_EQ(info.gridMatrix_.at(0).at(1), -1);
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 0);

    info.endIndex_ = 1;
    filler.FillOne();
    EXPECT_EQ(info.gridMatrix_.at(1).at(0), 1);
    EXPECT_EQ(info.gridMatrix_.at(1).size(), 1);
    EXPECT_EQ(info.gridMatrix_.at(2).at(0), -1);
    EXPECT_EQ(info.gridMatrix_.at(2).size(), 1);
    EXPECT_TRUE(info.gridMatrix_.find(3) == info.gridMatrix_.end());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 1);

    info.endIndex_ = 2;
    filler.FillOne();
    EXPECT_EQ(info.gridMatrix_.at(3).at(0), 2);
    EXPECT_EQ(info.gridMatrix_.at(3).at(1), -1);
    EXPECT_TRUE(info.gridMatrix_.find(4) == info.gridMatrix_.end());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 3);
}

/**
 * @tc.name: IrregularFiller::FillOne002
 * @tc.desc: Test IrregularFiller::FillOne with 3 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, FillOne002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 1]
        1, // [2 x 1]
        2, // [1 x 1]
        3, // [2 x 2]
        4, // [1 x 1]
        5, // [1 x 1]
        6, // [1 x 2]
        7, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 6) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 0 || index == 2 || index == 5 || index == 4) {
            return { 1, 1 };
        }
        if (index == 3) {
            return { 2, 2 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    for (int i = 0; i < 8; ++i) {
        info.endIndex_ = i;
        filler.FillOne();
    }

    decltype(info.gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, -1 } } },  // 0 | 1 | 1
        { 1, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },  // 2 | 3 | 3
        { 2, { { 0, 4 }, { 1, -1 }, { 2, -1 } } }, // 4 | 3 | 3
        { 3, { { 0, 5 }, { 1, 6 } } },             // 5 | 6 | x
        { 4, { { 1, -1 } } },                      // x | 6 | x
        { 5, { { 0, 7 }, { 1, -1 } } }             // 7 | 7 | x
    };

    EXPECT_EQ(info.gridMatrix_, cmp);
}

/**
 * @tc.name: IrregularFiller::MeasureItem001
 * @tc.desc: Test IrregularFiller::MeasureItem
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, MeasureItem001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize { return { .columns = 1, .rows = 2 }; };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    GridLayoutInfo info;
    info.crossCount_ = 4;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    info.endIndex_ = 0;

    GridIrregularFiller::FillParameters params {
        .crossLens = { 50.0f, 50.0f, 100.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f
    };
    filler.MeasureItem(params, 0, 0);

    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    auto child = frameNode_->GetChildByIndex(0);
    ASSERT_TRUE(child);
    auto constraint = *child->GetGeometryNode()->GetParentLayoutConstraint();
    EXPECT_EQ(constraint.maxSize.Width(), 50.0f);
    EXPECT_EQ(*constraint.selfIdealSize.Width(), 50.0f);
    EXPECT_EQ(constraint.percentReference.Width(), 50.0f);
}

/**
 * @tc.name: IrregularFiller::MeasureItem002
 * @tc.desc: Test IrregularFiller::MeasureItem
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, MeasureItem002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,
    };
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    GridLayoutInfo info;
    info.crossCount_ = 4;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    info.endIndex_ = 0;
    filler.posY_ = 0;

    GridIrregularFiller::FillParameters params {
        .crossLens = { 50.0f, 50.0f, 100.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f
    };
    filler.MeasureItem(params, 0, 0);

    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) == info.lineHeightMap_.end());
    auto child = frameNode_->GetChildByIndex(0);
    ASSERT_TRUE(child);
    auto constraint = *child->GetGeometryNode()->GetParentLayoutConstraint();
    EXPECT_EQ(constraint.maxSize.Width(), 315.0f);
    EXPECT_EQ(*constraint.selfIdealSize.Width(), 315.0f);
    EXPECT_EQ(constraint.percentReference.Width(), 315.0f);
}

/**
 * @tc.name: IrregularFiller::Fill001
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, Fill001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 2]
        3, // [2 x 2]
        6, // [3 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 3) {
            return { 2, 2 };
        }
        return { .rows = 2, .columns = 3 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    float len = filler.Fill(
        { .crossLens = { 50.0f, 50.0f, 100.0f }, .targetLen = 1000.0f, .crossGap = 5.0f, .mainGap = 1.0f }, 0);

    EXPECT_EQ(len, 6.0f);

    EXPECT_EQ(info.endIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 6);

    decltype(info.gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },    // 0 | 1 | 2
        { 1, { { 0, -1 }, { 1, 3 }, { 2, -1 } } },  // 0 | 3 | 3
        { 2, { { 0, 4 }, { 1, -1 }, { 2, -1 } } },  // 4 | 3 | 3
        { 3, { { 0, 5 } } },                        // 5 | x | x
        { 4, { { 0, 6 }, { 1, -1 }, { 2, -1 } } },  // 6 | 6 | 6
        { 5, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 6 | 6 | 6
        { 6, { { 0, 7 }, { 1, 8 }, { 2, 9 } } }     // 7 | 8 | 9
    };

    EXPECT_EQ(info.gridMatrix_, cmp);
}

/**
 * @tc.name: LayoutRangeSolver::AddNextRow001
 * @tc.desc: Test LayoutRangeSolver::AddNextRow
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, AddNextRow001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 2]
        3, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },   // 0 | 1 | 2
        { 1, { { 0, -1 }, { 1, 3 }, { 2, -1 } } }, // 0 | 3 | 3
    };
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 30.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.AddNextRows(5.0f, 0);
    EXPECT_EQ(res.first, 2);
    EXPECT_EQ(res.second, 80.0f + 5.0f); // top line doesn't have main gap
}

/**
 * @tc.name: LayoutRangeSolver::AddNextRows002
 * @tc.desc: Test LayoutRangeSolver::AddNextRows
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, AddNextRows002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [1 x 3]
        3, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 3, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, 1 }, { 2, 2 } } },   // 0 | 1 | 2
        { 1, { { 0, -1 }, { 1, 3 }, { 2, -1 } } }, // 0 | 3 | 3
        { 2, { { 0, -1 } } },                      // 0 | x | x
    };
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 60.0f }, { 2, 40.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.AddNextRows(5.0f, 0);
    EXPECT_EQ(res.first, 3);
    EXPECT_EQ(res.second, 160.0f);

    // in real scenario, parameter rowIdx = 1 is impossible
    res = solver.AddNextRows(5.0f, 1);
    EXPECT_EQ(res.first, 1);
    EXPECT_EQ(res.second, 65.0f);

    res = solver.AddNextRows(5.0f, 2);
    EXPECT_EQ(res.first, 1);
    EXPECT_EQ(res.second, 45.0f);
}

/**
 * @tc.name: LayoutRangeSolver::SolveForward001
 * @tc.desc: Test LayoutRangeSolver::SolveForward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SolveForward001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        1, // [1 x 3]
        4, // [3 x 1]
        5, // [1 x 2]
        7, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 3, .columns = 1 };
        }
        if (index == 0) {
            return { 2, 2 };
        }
        if (index == 4) {
            return { .rows = 1, .columns = 3 };
        }
        return { .rows = 2, .columns = 1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 0 | 0 | 1
        { 2, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },   // 2 | 3 | 1
        { 3, { { 0, 4 }, { 1, -1 }, { 2, -1 } } },  // 4 | 4 | 4
        { 4, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },    // 5 | 6 | 7
        { 4, { { 0, -1 }, { 2, -1 } } },            // 5 | x | 7
    };
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 40.0f }, { 2, 40.0f }, { 3, 10.0f }, { 4, 50.0f }, { 5, 70.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.currentOffset_ = 0.0f;
    info.startMainLineIndex_ = 3;
    auto res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 3);
    EXPECT_EQ(res.pos, 0.0f);

    info.currentOffset_ = -20.0f;
    info.startMainLineIndex_ = 0;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 0);
    EXPECT_EQ(res.pos, -20.0f);

    info.currentOffset_ = -70.0f;
    info.startMainLineIndex_ = 0;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 0);
    EXPECT_EQ(res.pos, -70.0f);

    // startMainLineIndex_ == 1 || startMainLineIndex_ == 2 is impossible.
    // LayoutRangeSolver always finds the first row of irregular items.

    info.currentOffset_ = -11.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 4);
    EXPECT_EQ(res.pos, 0.0f);

    info.currentOffset_ = -10.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 3);
    EXPECT_EQ(res.pos, -10.0f);

    info.currentOffset_ = -110.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 4);
    EXPECT_EQ(res.pos, -99.0f);
}

/**
 * @tc.name: LayoutRangeSolver::CheckMultiRow001
 * @tc.desc: Test LayoutRangeSolver::CheckMultiRow
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, CheckMultiRow001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        3, // [3 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 1, .columns = 2 };
        }
        return { .rows = 2, .columns = 3 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, -1 }, { 2, 2 } } },   // 0 | 0 | 2
        { 1, { { 0, 3 }, { 1, -1 }, { 2, -1 } } },  // 3 | 3 | 3
        { 2, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 3 | 3 | 3
    };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    EXPECT_EQ(solver.CheckMultiRow(2), 2);

    EXPECT_EQ(solver.CheckMultiRow(0), 1);
    EXPECT_EQ(solver.CheckMultiRow(1), 1);
}

/**
 * @tc.name: LayoutRangeSolver::SolveBackward001
 * @tc.desc: Test LayoutRangeSolver::SolveBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SolveBackward001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        3, // [2 x 2]
        4, // [1 x 2]
        6, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 4) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 3) {
            return { 2, 2 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, -1 }, { 2, 1 } } },  // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },  // 2 | 3 | 3
        { 2, { { 0, 4 }, { 1, -1 }, { 2, -1 } } }, // 4 | 3 | 3
        { 3, { { 0, -1 }, { 1, 5 } } },            // 4 | 5 | x
        { 4, { { 0, 6 }, { 1, -1 }, { 2, 7 } } },  // 6 | 6 | 7
    };
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 30.0f }, { 2, 40.0f }, { 3, 30.0f }, { 4, 50.0f } };

    info.currentOffset_ = 20.0f;
    info.startMainLineIndex_ = 4;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, -60.0f);
    EXPECT_EQ(res.row, 2);

    info.currentOffset_ = 80.0f;
    info.startMainLineIndex_ = 4;

    res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, -35.0f);
    EXPECT_EQ(res.row, 1);

    info.currentOffset_ = 200.0f;
    info.startMainLineIndex_ = 4;

    res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, 30.0f);
    EXPECT_EQ(res.row, 0);
}

/**
 * @tc.name: LayoutRangeSolver::Solve001
 * @tc.desc: Test LayoutRangeSolver::FindStartingRow when matrix is empty.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, Solve001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions({});
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;

    info.currentOffset_ = 0.0f;
    info.startMainLineIndex_ = 0;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, 0.0f);
    EXPECT_EQ(res.row, 0);
}

/**
 * @tc.name: GridIrregularLayout::LayoutChildren001
 * @tc.desc: Test GridIrregularLayout::LayoutChildren
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, LayoutChildren001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateRowItem(10);
    });

    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF { .left = 5.0f, .top = 3.0f });

    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, -1 }, { 2, 1 } } }, // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, 3 }, { 2, 4 } } },  // 2 | 3 | 4
        { 2, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },  // 5 | 6 | 7
        { 3, { { 0, 8 }, { 1, -1 } } },           // 8 | 8 | x
        { 4, { { 0, 9 }, { 1, -1 } } },           // 9 | 9 | x
    };
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 20.0f }, { 2, 10.0f }, { 3, 15.0f }, { 4, 30.0f } };
    info.crossCount_ = 3;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 4;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(info);
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 50.0f, 50.0f, 100.0f };
    algorithm->crossGap_ = 5.0f;
    algorithm->mainGap_ = 1.0f;
    algorithm->LayoutChildren(0.0f);

    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetX(), 5.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(0)->GetGeometryNode()->GetFrameOffset().GetY(), 3.0f);
    EXPECT_EQ(frameNode_->GetChildByIndex(1)->GetGeometryNode()->GetFrameOffset(), OffsetF(115.0f, 3.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset(), OffsetF(5.0f, 24.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(3)->GetGeometryNode()->GetFrameOffset(), OffsetF(60.0f, 24.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(4)->GetGeometryNode()->GetFrameOffset(), OffsetF(115.0f, 24.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(5)->GetGeometryNode()->GetFrameOffset(), OffsetF(5.0f, 45.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(6)->GetGeometryNode()->GetFrameOffset(), OffsetF(60.0f, 45.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(7)->GetGeometryNode()->GetFrameOffset(), OffsetF(115.0f, 45.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(8)->GetGeometryNode()->GetFrameOffset(), OffsetF(5.0f, 56.0f));
    EXPECT_EQ(frameNode_->GetChildByIndex(9)->GetGeometryNode()->GetFrameOffset(), OffsetF(5.0f, 72.0f));
}

/**
 * @tc.name: GridIrregularLayout::Measure001
 * @tc.desc: Test GridIrregularLayout::Measure
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, Measure001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        3, // [1 x 2]
        4, // [1 x 2]
        6, // [3 x 2]
    };

    // 0 | 0 | 1
    // 0 | 0 | 2
    // 3 | 4 | 5
    // 3 | 4 | x
    // 6 | 6 | 6
    // 6 | 6 | 6
    // 7 | 8 | 9

    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { 2, 2 };
        }
        if (index == 6) {
            return { .rows = 2, .columns = 3 };
        }
        return { .rows = 2, .columns = 1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateRowItem(10);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->gridLayoutInfo_.currentOffset_ = 0.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    std::vector<float> cmp = { 200.0f, 200.0f, 200.0f };
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 610.0f);
    EXPECT_EQ(algorithm->crossLens_, cmp);

    const auto& info = algorithm->gridLayoutInfo_;
    EXPECT_EQ(algorithm->mainGap_, 1.0f);
    EXPECT_EQ(algorithm->crossGap_, 5.0f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 9);
}

/**
 * @tc.name: GridIrregularLayout::Layout001
 * @tc.desc: Test GridIrregularLayout::Layout
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, Layout001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateRowItem(10);
    });
    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF { .left = 1.0f, .top = 1.0f });
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF { 200.0f, 500.0f });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->crossLens_ = { 50.0f, 50.0f, 50.0f };
    auto& info = algorithm->gridLayoutInfo_;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, -1 } } }, // 0 | 0 | 0
        { 1, { { 0, 2 }, { 1, 3 }, { 2, 4 } } },   // 2 | 3 | 4
        { 2, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },   // 5 | 6 | 7
        { 3, { { 0, 8 }, { 1, -1 }, { 2, 9 } } },  // 8 | 6 | 9
    };
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 20.0f }, { 2, 10.0f }, { 3, 15.0f } };
    info.crossCount_ = 3;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 0;
    info.endIndex_ = 9;
    info.currentOffset_ = 10.0f;
    algorithm->Layout(AceType::RawPtr(frameNode_));

    EXPECT_TRUE(info.reachStart_);
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_TRUE(info.offsetEnd_);
}

/**
 * @tc.name: GridIrregularLayout::FillMatrixOnly001
 * @tc.desc: Test GridIrregularFiller::FillMatrixOnly
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, FillMatrixOnly001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        2, // [3 x 2]
        5, // [1 x 3]
        6, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 2, .columns = 3 };
        }
        if (index == 5) {
            return { .rows = 3, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    decltype(GridLayoutInfo::gridMatrix_) expected = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -1 }, { 2, -1 } } },  // 2 | 2 | 2
        { 2, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -1 }, { 2, -1 } } },  // 6 | 6 | 5
        { 5, { { 2, -1 } } }                        // x | x | 5
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateColItem(7);
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    // partially filled
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } }, // 0 | 0 | 1
    };

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    filler.FillMatrixOnly(0, 6);

    EXPECT_EQ(info.gridMatrix_, expected);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 4);
}

/**
 * @tc.name: GridIrregularLayout::MeasureBackward001
 * @tc.desc: Test GridIrregularFiller::MeasureBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, MeasureBackward001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        2, // [3 x 2]
        5, // [1 x 3]
        6, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 2, .columns = 3 };
        }
        if (index == 5) {
            return { .rows = 3, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -1 }, { 2, -1 } } },  // 2 | 2 | 2
        { 2, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -1 }, { 2, -1 } } },  // 6 | 6 | 5
        { 5, { { 2, -1 } } }                        // x | x | 5
    };
    info.crossCount_ = 3;

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    float len = filler.MeasureBackward({ { 50.0f, 50.0f, 50.0f }, 1000.0f, 5.0f, 5.0f }, 5);

    EXPECT_EQ(len, 30.0f);
    EXPECT_EQ(info.lineHeightMap_.size(), 6);
}

/**
 * @tc.name: GridIrregularLayout::FindRangeOnJump001
 * @tc.desc: Test GridLayoutRangeFinder::FindRangeOnJump
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, FindRangeOnJump001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,  // [2 x 1]
        1,  // [1 x 3]
        2,  // [2 x 1]
        5,  // [1 x 4]
        7,  // [1 x 2]
        9,  // [1 x 2]
        10, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        switch (index) {
            case 0:
                return { .columns = 2, .rows = 1 };
            case 1:
                return { .columns = 1, .rows = 3 };
            case 2:
                return { .columns = 2, .rows = 1 };
            case 5:
                return { .columns = 1, .rows = 4 };
            default:
                return { .columns = 1, .rows = 2 };
        }
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f }, { 5, 75.0f },
        { 6, 10.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -1 }, { 2, -1 } } },  // 2 | 2 | 1
        { 2, { { 0, 3 }, { 1, 4 }, { 2, -1 } } },   // 3 | 4 | 1
        { 3, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },    // 5 | 6 | 7
        { 4, { { 0, -1 }, { 1, 8 }, { 2, -1 } } },  // 5 | 8 | 7
        { 5, { { 0, -1 }, { 1, 9 }, { 2, 10 } } },  // 5 | 9 | 10
        { 6, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 5 | 9 | 10
    };

    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });
    frameNode_->GetGeometryNode()->SetContentSize({ 500.0f, 250.0f });

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.scrollAlign_ = ScrollAlign::START;
    auto res = solver.FindRangeOnJump(2, 5.0f);
    EXPECT_EQ(res.startRow, 0);
    EXPECT_EQ(res.pos, -160.0f);
    EXPECT_EQ(res.endIdx, 10);
    EXPECT_EQ(res.endRow, 5);

    info.scrollAlign_ = ScrollAlign::CENTER;
    res = solver.FindRangeOnJump(4, 5.0f);
    EXPECT_EQ(res.startRow, 0);
    EXPECT_EQ(res.pos, -185.0f);
    EXPECT_EQ(res.endIdx, 10);
    EXPECT_EQ(res.endRow, 5);

    info.scrollAlign_ = ScrollAlign::END;
    res = solver.FindRangeOnJump(4, 5.0f);
    EXPECT_EQ(res.startRow, 0);
    EXPECT_EQ(res.pos, -100.0f);
    EXPECT_EQ(res.endIdx, 8);
    EXPECT_EQ(res.endRow, 4);
}

/**
 * @tc.name: GridIrregularLayout::SolveForwardForEndIdx001
 * @tc.desc: Test GridLayoutRangeFinder::SolveForwardForEndIdx
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SolveForwardForEndIdx001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -1 }, { 2, -1 } } },  // 2 | 2 | 2
        { 2, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -1 }, { 2, -1 } } },  // 6 | 6 | 5
    };

    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions({});
    });

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto [endLineIdx, endIdx] = solver.SolveForwardForEndIdx(5.0f, 250.0f, 1);
    EXPECT_EQ(endIdx, 6);
    EXPECT_EQ(endLineIdx, 4);
}

/**
 * @tc.name: GridIrregularLayout::PrepareLineHeights001
 * @tc.desc: Test GridIrregularLayout::PrepareLineHeights001
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, PrepareLineHeights001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions({});
        CreateColItem(15);
    });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 1.0f, 1.0f, 1.0f };
    auto& info = algorithm->gridLayoutInfo_;
    // because measuring children might not generate proper heights in test, we set them manually.
    decltype(info.lineHeightMap_) cmpH = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f }, { 3, 200.0f }, { 4, 200.0f } };
    info.lineHeightMap_ = cmpH;
    decltype(info.gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
        { 2, { { 0, 6 }, { 1, 7 }, { 2, 8 } } },
        { 3, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
        { 4, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
    };
    info.gridMatrix_ = cmp;

    info.crossCount_ = 3;

    info.scrollAlign_ = ScrollAlign::START;
    int32_t idx = 0;
    algorithm->PrepareLineHeight(70.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    info.scrollAlign_ = ScrollAlign::START;
    idx = 2;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 2);

    // can't align start with idx 4
    info.scrollAlign_ = ScrollAlign::START;
    idx = 4;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);

    // can't align center with idx 0
    info.scrollAlign_ = ScrollAlign::CENTER;
    idx = 0;
    algorithm->PrepareLineHeight(350.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    // can't align center with idx 4
    info.scrollAlign_ = ScrollAlign::CENTER;
    idx = 4;
    algorithm->PrepareLineHeight(350.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);

    // align center with idx 4 and len 30.0f
    info.scrollAlign_ = ScrollAlign::CENTER;
    idx = 4;
    algorithm->PrepareLineHeight(30.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::CENTER);
    EXPECT_EQ(idx, 4);

    // can't align end with idx 1 and len 200.0f
    info.scrollAlign_ = ScrollAlign::END;
    idx = 1;
    algorithm->PrepareLineHeight(500.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    info.scrollAlign_ = ScrollAlign::END;
    idx = 3;
    algorithm->PrepareLineHeight(300.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 3);

    info.scrollAlign_ = ScrollAlign::END;
    idx = 4;
    algorithm->PrepareLineHeight(1000.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(idx, 4);

    // can't align end with len 340
    info.scrollAlign_ = ScrollAlign::END;
    idx = 4;
    algorithm->PrepareLineHeight(1040.0f, idx);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(idx, 0);

    EXPECT_EQ(cmp, info.gridMatrix_);
    EXPECT_EQ(cmpH, info.lineHeightMap_);
}

/**
 * @tc.name: GridIrregularLayout::TransformAutoScrollAlign001
 * @tc.desc: Test IrregularLayout::TransformAutoScrollAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, TransformAutoScrollAlign001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        2, // [3 x 2]
        5, // [1 x 3]
        6, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 2, .columns = 3 };
        }
        if (index == 5) {
            return { .rows = 3, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(option);
    });

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algo->gridLayoutInfo_;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 300.0f }, { 2, 30.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -1 }, { 2, -1 } } },  // 2 | 2 | 2
        { 2, { { 0, -1 }, { 1, -1 }, { 2, -1 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -1 }, { 2, -1 } } },  // 6 | 6 | 5
    };
    algo->mainGap_ = 5.0f;

    info.jumpIndex_ = 2;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 0;
    info.endIndex_ = 6;
    EXPECT_EQ(algo->TransformAutoScrollAlign(500.0f), ScrollAlign::NONE);

    info.jumpIndex_ = 0;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 3;
    info.endIndex_ = 6;
    info.currentOffset_ = -10.0f;
    EXPECT_EQ(algo->TransformAutoScrollAlign(100.0f), ScrollAlign::START);

    info.jumpIndex_ = 2;
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 2;
    info.endIndex_ = 2;
    info.currentOffset_ = -25.0f;
    EXPECT_EQ(algo->TransformAutoScrollAlign(310.0f), ScrollAlign::NONE);

    // line 3 now matches with the end of the viewport, should endMainlineIndex_ be updated to 3?
    info.currentOffset_ = -30.0f;
    info.endMainLineIndex_ = 3;
    info.endIndex_ = 5;
    EXPECT_EQ(algo->TransformAutoScrollAlign(310.0f), ScrollAlign::START);
    info.currentOffset_ = -31.0f;
    EXPECT_EQ(algo->TransformAutoScrollAlign(310.0f), ScrollAlign::START);

    info.jumpIndex_ = 0;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 3;
    info.endIndex_ = 6;
    EXPECT_EQ(algo->TransformAutoScrollAlign(100.0f), ScrollAlign::START);

    info.jumpIndex_ = 4;
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 2;
    info.endIndex_ = 6;

    info.currentOffset_ = -379.0f;
    algo->mainGap_ = 50.0f;
    EXPECT_EQ(algo->TransformAutoScrollAlign(152.0f), ScrollAlign::NONE);

    algo->mainGap_ = 5.0f;
    // emulate init
    info.lineHeightMap_.clear();
    info.gridMatrix_.clear();
    info.jumpIndex_ = 3;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 0;
    info.startIndex_ = 0;
    info.endIndex_ = -1;
    EXPECT_EQ(algo->TransformAutoScrollAlign(300.0f), ScrollAlign::END);
}

/**
 * @tc.name: GridLayout001
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateRowItem(16);
    });

    /**
     * @tc.steps: step1. call InitGridCeils
     * @tc.expected: The GetLayoutProperty is !nullptr
     */
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 4, 4);
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    algorithm->crossCount_ = 5;
    algorithm->mainCount_ = 5;
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    EXPECT_NE(pattern->GetLayoutProperty<GridLayoutProperty>(), nullptr);
}

/**
 * @tc.name: GridLayout002
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("");
        model.SetRowsTemplate("");
        CreateRowItem(16);
    });

    /**
     * @tc.steps: step1. Change to smaller mainSize
     * @tc.expected: The GetLayoutProperty is correct
     */
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 4, 4);
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    algorithm->crossCount_ = 5;
    algorithm->mainCount_ = 5;
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    EXPECT_NE(pattern->GetLayoutProperty<GridLayoutProperty>(), nullptr);
}

/**
 * @tc.name: GridLayout003
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        std::string emptyString;
        model.SetColumnsTemplate(emptyString);
        model.SetRowsTemplate(emptyString);
        CreateRowItem(16);
    });

    /**
     * @tc.steps: step1. Change to smaller mainSize
     * @tc.expected: The GetLayoutProperty is correct
     */
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 4, 4);
    algorithm->gridLayoutInfo_.currentOffset_ = 0.0f;
    auto layoutProperty = pattern->CreateLayoutProperty();
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    algorithm->crossCount_ = 5;
    algorithm->mainCount_ = 5;
    algorithm->InitGridCeils(AceType::RawPtr(frameNode_), { 0.0f, 0.0f });
    EXPECT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: GridLayout004
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout004, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. isVertical_ is true
     * @tc.expected: The curRow and curCol is correct
     */
    int32_t curRow = 0;
    int32_t curCol = 0;
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 2, 5);
    EXPECT_EQ(algorithm->crossCount_, 2);
    EXPECT_EQ(algorithm->mainCount_, 5);
    algorithm->GetNextGrid(curRow, curCol);
    EXPECT_EQ(curRow, 0);
    EXPECT_EQ(curCol, 1);
    EXPECT_TRUE(algorithm->isVertical_);
    algorithm->GetNextGrid(curRow, curCol);
    EXPECT_EQ(curRow, 1);
    EXPECT_EQ(curCol, 0);
    curRow = 1;
    curCol = 1;

    /**
     * @tc.steps: step2. isVertical_ is false
     * @tc.expected: The curRow and curCol is correct
     */
    algorithm->isVertical_ = false;
    algorithm->GetNextGrid(curRow, curCol);
    EXPECT_EQ(curRow, 2);
    EXPECT_EQ(curCol, 1);
    algorithm->GetNextGrid(curRow, curCol);
    EXPECT_EQ(curRow, 3);
    EXPECT_EQ(curCol, 1);
    curRow = 5;
    algorithm->GetNextGrid(curRow, curCol);
    EXPECT_EQ(curRow, 0);
    EXPECT_EQ(curCol, 2);
}

/**
 * @tc.name: GridLayout005
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout005, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step2.call GetItemRect
     * @tc.expected: The GetItemRect is crrect
     */
    GridItemRect retItemRect;
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 2, 5);
    auto childLayoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 0);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(childLayoutProperty, nullptr);
    algorithm->GetItemRect(layoutProperty_, childLayoutProperty, 0);
    EXPECT_EQ(retItemRect.rowStart, -1);
    EXPECT_EQ(retItemRect.rowSpan, 1);
    EXPECT_EQ(retItemRect.columnStart, -1);
    EXPECT_EQ(retItemRect.columnSpan, 1);
}

/**
 * @tc.name: GridLayout006
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridLayout006, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 6, 1, 2, 3, 4, 5 };
    option.getRectByIndex = [](int32_t index) {
        GridItemRect tmpItemRect;
        tmpItemRect.rowStart = 1;
        tmpItemRect.rowSpan = 20;
        tmpItemRect.columnStart = 1;
        tmpItemRect.columnSpan = 20;
        return tmpItemRect;
    };
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr");
        model.SetLayoutOptions(option);
        CreateRowItem(10);
    });
    pattern_->UpdateStartIndex(3);
    FlushLayoutTask(frameNode_);
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr");

    /**
     * @tc.steps: step2.call GetItemRect
     * @tc.expected: The GetItemRect is crrect
     */
    GridItemRect retItemRect;
    auto pattern = frameNode_->GetPattern<GridPattern>();
    auto algorithm = AceType::MakeRefPtr<GridLayoutAlgorithm>(GridLayoutInfo {}, 2, 5);
    auto childLayoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 0);
    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_NE(childLayoutProperty, nullptr);
    retItemRect = algorithm->GetItemRect(layoutProperty_, childLayoutProperty, 0);
    EXPECT_EQ(retItemRect.rowStart, 1);
    EXPECT_EQ(retItemRect.rowSpan, 20);
    EXPECT_EQ(retItemRect.columnStart, 1);
    EXPECT_EQ(retItemRect.columnSpan, 20);
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. create paintMethod
     */
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    paintMethod->UpdateOverlayModifier(nullptr);

    /**
     * @tc.steps: step2. call UpdateOverlayModifier
     * @tc.expected: scrollBar is nullptr
     */
    paintMethod->UpdateOverlayModifier(&paintWrapper);
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);
}

/**
 * @tc.name: UpdateOverlayModifier002
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, UpdateOverlayModifier002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. create scrollBar and paintMethod
     * @tc.expected: scrollBar is !nullptr
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    paintMethod->UpdateOverlayModifier(nullptr);
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step2. call UpdateOverlayModifier
     * @tc.expected: AnimationTyp is correct
     */
    paintMethod->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. call UpdateOverlayModifier when scrollBarOverlayModifier is seted
     * @tc.expected: AnimationTyp is correct
     */
    pattern_->CreateScrollBarOverlayModifier();
    EXPECT_EQ(pattern_->scrollBarOverlayModifier_, nullptr);
    paintMethod->SetScrollBarOverlayModifier(pattern_->GetScrollBarOverlayModifier());
    auto scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    EXPECT_EQ(scrollBarOverlayModifier, nullptr);
    paintMethod->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar = nullptr;
}

/**
 * @tc.name: UpdateOverlayModifier003
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, UpdateOverlayModifier003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. create scrollBar and paintMethod and ScrollBarOverlayModifier
     * @tc.expected: scrollBar is !nullptr
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->scrollBar_->SetScrollable(true);
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    EXPECT_TRUE(pattern_->scrollBar_->NeedPaint());
    pattern_->CreateScrollBarOverlayModifier();
    EXPECT_NE(pattern_->scrollBarOverlayModifier_, nullptr);
    paintMethod->SetScrollBarOverlayModifier(pattern_->GetScrollBarOverlayModifier());
    auto scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    EXPECT_NE(scrollBarOverlayModifier, nullptr);
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step2. call UpdateOverlayModifier
     * @tc.expected: AnimationTyp is correct
     */
    paintMethod->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. change PositionMode and call UpdateOverlayModifier
     * @tc.expected: AnimationTyp is correct
     */
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    paintMethod->UpdateOverlayModifier(&paintWrapper);
    scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar = nullptr;
}

/**
 * @tc.name: PaintEdgeEffect001
 * @tc.desc: Test grid paint method PaintEdgeEffect function
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, PaintEdgeEffect001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. init scrollBar
     * @tc.expected: scrollBar is !nullptr
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->scrollBar_->SetScrollable(true);
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
    auto paintProperty = pattern_->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty);
    EXPECT_TRUE(pattern_->scrollBar_->NeedPaint());
    pattern_->CreateScrollBarOverlayModifier();
    EXPECT_NE(pattern_->scrollBarOverlayModifier_, nullptr);
    paintMethod->SetScrollBarOverlayModifier(pattern_->GetScrollBarOverlayModifier());
    auto scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    EXPECT_NE(scrollBarOverlayModifier, nullptr);
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step2. call PaintEdgeEffect
     * @tc.expected: edgeEffect_ is !nullptr
     */
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>();
    paintMethod->SetEdgeEffect(scrollEdgeEffect);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    paintMethod->PaintEdgeEffect(nullptr, rsCanvas);
    paintMethod->PaintEdgeEffect(&paintWrapper, rsCanvas);
    EXPECT_NE(paintMethod->edgeEffect_.Upgrade(), nullptr);
}

/**
 * @tc.name: GridScrollTest006
 * @tc.desc: Test SetOnScrollBarUpdate Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridScrollTest006, TestSize.Level1)
{
    Create([](GridModelNG model) {
        ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
            std::optional<float> horizontalOffset = offset.ConvertToPx();
            std::optional<float> verticalOffset = offset.ConvertToPx();
            return std::make_pair(horizontalOffset, verticalOffset);
        };
        model.SetRowsTemplate("1fr 1fr");
        CreateColItem(2);
        model.SetGridHeight(Dimension(5));
        model.SetScrollBarMode(DisplayMode::AUTO);
        model.SetScrollBarColor("#FF0000");
        model.SetScrollBarWidth("10vp");
        model.SetIsRTL(TextDirection::LTR);

        NestedScrollOptions nestedOpt;
        model.SetNestedScroll(std::move(nestedOpt));
        ScrollToIndexFunc value;
        model.SetOnScrollToIndex(std::move(value));
    });
    auto paintProperty = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(paintProperty->GetBarStateString(), "BarState.Auto");

    auto pattern = frameNode_->GetPattern<GridPattern>();
    EXPECT_TRUE(pattern->isConfigScrollable_);
    auto eventHub = frameNode_->GetEventHub<GridEventHub>();
    EXPECT_FALSE(eventHub->onScrollToIndex_);
}

/**
 * @tc.name: GridSCroll001
 * @tc.desc: Test SetSelected Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, GridSCroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridItemModelNG object
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        itemModel.SetRowStart(NULL_VALUE);
        itemModel.SetRowEnd(NULL_VALUE);
        itemModel.SetColumnStart(NULL_VALUE);
        itemModel.SetColumnEnd(NULL_VALUE);
        ViewStackProcessor::GetInstance()->Pop();

        /**
         * @tc.steps: step2. Test Create function
         */
        std::function<void(int32_t)> deepRenderFunc = [](int32_t innerNodeId) {};
        bool isLazy = true;
        itemModel.Create(std::move(deepRenderFunc), isLazy, GridItemStyle::PLAIN);

        /**
         * @tc.steps: step3. invoke SetSelected function
         */
        itemModel.SetSelected(true);
    });

    /**
     * @tc.expected: gridItemPattern->isSelected_ is true
     */
    auto gridItemPattern = frameNode_->GetPattern<GridItemPattern>();
    EXPECT_TRUE(gridItemPattern->isSelected_);
}

/**
 * @tc.name: SupplyAllData2ZeroIndex001
 * @tc.desc: Test GridScrollLayoutAlgorithm::SupplyAllData2ZeroIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SupplyAllData2ZeroIndex001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateColItem(30);
    });

    pattern_->ScrollToIndex(20, true, ScrollAlign::END);
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lineHeightMap_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(0).at(0), 0);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(3).at(2), 11);
}

/**
 * @tc.name: SupplyAllData2ZeroIndex002
 * @tc.desc: Test GridScrollLayoutAlgorithm::SupplyAllData2ZeroIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutTestNg, SupplyAllData2ZeroIndex002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateColItem(30);
    });

    pattern_->ScrollToIndex(20, true, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    pattern_->ScrollToIndex(10, true, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lineHeightMap_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(0).at(0), 0);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(3).at(2), 11);
}
} // namespace OHOS::Ace::NG
