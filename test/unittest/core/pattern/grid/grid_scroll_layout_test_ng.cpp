/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {
class GridScrollLayoutTestNg : public GridTestNg {
public:
    void UpdateLayoutInfo();
    RefPtr<GridPaintMethod> UpdateOverlayModifier();
    RefPtr<GridPaintMethod> UpdateContentModifier();
};

void GridScrollLayoutTestNg::UpdateLayoutInfo()
{
    GetGrid();
    ViewStackProcessor::GetInstance()->Finish();
    FlushUITasks(frameNode_);
    pattern_->info_.lineHeightMap_[0] = ITEM_MAIN_SIZE;
    pattern_->info_.gridMatrix_[0][0] = 0;
    pattern_->info_.gridMatrix_[0][1] = 1;
    pattern_->info_.gridMatrix_[1][0] = 0;
    pattern_->info_.gridMatrix_[1][1] = 1;
}

RefPtr<GridPaintMethod> GridScrollLayoutTestNg::UpdateOverlayModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

RefPtr<GridPaintMethod> GridScrollLayoutTestNg::UpdateContentModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

/**
 * @tc.name: GridPaintMethodTest001
 * @tc.desc: Test grid paint method GetForegroundDrawFunction function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridPaintMethodTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
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
HWTEST_F(GridScrollLayoutTestNg, ScrollLayout001, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, HEIGHT + ITEM_MAIN_SIZE);
    textFieldManager->SetClickPosition(clickPosition);

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMaxCount(2);
    CreateFixedItems(18);
    CreateDone();
    const float smallerHeight = HEIGHT - ITEM_MAIN_SIZE;
    RectF gridRect(0, 0, WIDTH, smallerHeight);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->rect_ = gridRect;

    /**
     * @tc.steps: step1. Change to smaller mainSize
     * @tc.expected: The mainSize is correct
     */
    auto gridFocus = frameNode_->GetOrCreateFocusHub();
    gridFocus->RequestFocusImmediately();
    // change grid height and trigger Measure
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(smallerHeight));
    FlushUITasks();
    float gridHeight = frameNode_->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_FLOAT_EQ(gridHeight, smallerHeight);
}

/**
 * @tc.name: ScrollLayout002
 * @tc.desc: Test UpdateOffsetOnVirtualKeyboardHeightChange that currentOffset wuold not change
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ScrollLayout002, TestSize.Level1)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    const Offset clickPosition = Offset(100.f, 100.f);
    textFieldManager->SetClickPosition(clickPosition);

    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetMaxCount(2);
    CreateFixedItems(18);
    CreateDone();

    /**
     * @tc.steps: step1. While axis_ == Axis::HORIZONTAL
     * @tc.expected: currentOffset_ would not change
     */
    pattern_->info_.axis_ = Axis::HORIZONTAL;
    const float smallerHeight = HEIGHT - ITEM_MAIN_SIZE;
    // change grid height and trigger Measure
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(smallerHeight));
    FlushUITasks();
    float currentOffset = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0);

    /**
     * @tc.steps: step2. While Grid !IsCurrentFocus()
     * @tc.expected: currentOffset_ would not change
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(HEIGHT));
    FlushUITasks();
    pattern_->info_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(smallerHeight));
    FlushUITasks();
    currentOffset = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0);

    /**
     * @tc.steps: step3. While clickPosition is in Grid
     * @tc.expected: currentOffset_ would not change
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(HEIGHT));
    FlushUITasks();
    pattern_->info_.axis_ = Axis::VERTICAL;
    // change grid height and trigger Measure
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(smallerHeight));
    FlushUITasks();
    currentOffset = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(currentOffset, 0);
}

/**
 * @tc.name: GridScrollTest001
 * @tc.desc: Test FireOnScrollBarUpdate Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
        std::optional<float> horizontalOffset = offset.ConvertToPx();
        std::optional<float> verticalOffset = offset.ConvertToPx();
        return std::make_pair(horizontalOffset, verticalOffset);
    };
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    model.SetOnScrollBarUpdate(std::move(scrollFunc));
    CreateBigItem(1, 1, 1, 2);
    CreateFixedItems(2);
    CreateDone();
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
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_, 2, 0);
    ASSERT_NE(gridScrollLayoutAlgorithm, nullptr);
    auto ret = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(100, 100), 0, 1, 0);
    EXPECT_EQ(ret.GetY(), 100.f - ITEM_MAIN_SIZE);
    EXPECT_EQ(ret.GetX(), 100.f);
}

/**
 * @tc.name: GridScrollTest003
 * @tc.desc: Test CalculateLargeItemOffset Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    CreateFixedItems(10);
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_, 2, 0);
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
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create gridItem and initialize related properties.
     */
    GridModelNG model;
    model.Create(nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    UpdateLayoutInfo();
    auto gridScrollLayoutAlgorithm = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(pattern_->info_, 2, 0);
    auto ret1 = gridScrollLayoutAlgorithm->CalculateLargeItemOffset(OffsetF(0, 100), 1, 1, 0);
    EXPECT_EQ(ret1.GetY(), 100.0f);
    EXPECT_EQ(ret1.GetX(), 0.0f);
}

/**
 * @tc.name: GridScrollTest005
 * @tc.desc: Test AdjustRowColSpan Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    itemModel.SetRowStart(NULL_VALUE);
    itemModel.SetRowEnd(NULL_VALUE);
    itemModel.SetColumnStart(NULL_VALUE);
    itemModel.SetColumnEnd(NULL_VALUE);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
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
HWTEST_F(GridScrollLayoutTestNg, GetTotalHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_MAIN_SIZE * 3);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_MAIN_SIZE * 5);
}

/**
 * @tc.name: GetAverageHeight001
 * @tc.desc: Test GetAverageHeight Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetAverageHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 10 gridItem
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetAverageHeight(), 30);

    /**
     * @tc.steps: step2. Create 20 gridItem
     */
    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    EXPECT_EQ(pattern_->GetAverageHeight(), 25);
}

/**
 * @tc.name: ChangeItemNumber001
 * @tc.desc: Test ChangeItemNumber
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ChangeItemNumber001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(5);
    CreateDone();

    /**
     * @tc.steps: step1. Add item
     * @tc.expected: The added item in the correct position
     */
    for (int32_t i = 0; i < 4; i++) {
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_MAIN_SIZE)));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 6), OffsetF(120.0f, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 8), OffsetF(0, ITEM_MAIN_SIZE * 2)));
}

/**
 * @tc.name: UpdateGridMatrix001
 * @tc.desc: Test UpdateGridMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, UpdateGridMatrix001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create 100 items
     * @tc.expected: The added item in the correct position
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItems(100, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll To 99 item
     * @tc.expected: Scroll to the correct position,lineHeightMap_ size is 25
     */
    pattern_->ScrollToIndex(99, true, ScrollAlign::END);
    EXPECT_TRUE(IsEqual(pattern_->info_.lineHeightMap_.size(), 25));
}

/**
 * @tc.name: GridLayout004
 * @tc.desc: Test GridLayoutAlgorithm for coverage
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridLayout004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

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
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. call UpdateOverlayModifier
     * @tc.expected: scrollBar is nullptr
     */
    auto paintMethod = UpdateOverlayModifier();
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);
}

/**
 * @tc.name: UpdateOverlayModifier002
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, UpdateOverlayModifier002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. create scrollBar and paintMethod
     * @tc.expected: scrollBar is !nullptr
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    auto paintMethod = UpdateOverlayModifier();
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step2. call UpdateOverlayModifier
     * @tc.expected: AnimationTyp is correct
     */
    paintMethod = UpdateOverlayModifier();
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
    paintMethod = UpdateOverlayModifier();
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar = nullptr;
}

/**
 * @tc.name: UpdateOverlayModifier003
 * @tc.desc: Test grid paint method UpdateOverlayModifier function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, UpdateOverlayModifier003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. create scrollBar and paintMethod and ScrollBarOverlayModifier
     * @tc.expected: scrollBar is !nullptr
     */
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->scrollBar_->SetScrollable(true);
    auto paintMethod = AceType::DynamicCast<GridPaintMethod>(pattern_->CreateNodePaintMethod());
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
    paintMethod = UpdateOverlayModifier();
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. change PositionMode and call UpdateOverlayModifier
     * @tc.expected: AnimationTyp is correct
     */
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    paintMethod = UpdateOverlayModifier();
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
HWTEST_F(GridScrollLayoutTestNg, PaintEdgeEffect001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

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
HWTEST_F(GridScrollLayoutTestNg, GridScrollTest006, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ScrollBarUpdateFunc scrollFunc = [](int32_t index, Dimension offset) {
        std::optional<float> horizontalOffset = offset.ConvertToPx();
        std::optional<float> verticalOffset = offset.ConvertToPx();
        return std::make_pair(horizontalOffset, verticalOffset);
    };
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(2);
    model.SetGridHeight(Dimension(5));
    model.SetScrollBarMode(DisplayMode::AUTO);
    model.SetScrollBarColor("#FF0000");
    model.SetScrollBarWidth("10vp");
    model.SetIsRTL(TextDirection::LTR);

    NestedScrollOptions nestedOpt;
    model.SetNestedScroll(std::move(nestedOpt));
    ScrollToIndexFunc value;
    model.SetOnScrollToIndex(std::move(value));
    CreateDone();
    auto paintProperty = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(paintProperty->GetBarStateString(), "BarState.Auto");

    auto pattern = frameNode_->GetPattern<GridPattern>();
    EXPECT_TRUE(pattern->isConfigScrollable_);
    auto eventHub = frameNode_->GetOrCreateEventHub<GridEventHub>();
    EXPECT_FALSE(eventHub->onScrollToIndex_);
}

/**
 * @tc.name: GridScroll001
 * @tc.desc: Test SetSelected Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GridScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridItemModelNG object
     */
    GridModelNG model = CreateGrid();
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
    CreateDone();

    /**
     * @tc.expected: gridItemPattern->isSelected_ is true
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 1);
    EXPECT_TRUE(gridItemPattern->isSelected_);
}

/**
 * @tc.name: SupplyAllData2ZeroIndex001
 * @tc.desc: Test GridScrollLayoutAlgorithm::SupplyAllData2ZeroIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SupplyAllData2ZeroIndex001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateFixedItems(30);
    CreateDone();

    ScrollToIndex(20, true, ScrollAlign::END);

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
HWTEST_F(GridScrollLayoutTestNg, SupplyAllData2ZeroIndex002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateFixedItems(30);
    CreateDone();

    ScrollToIndex(20, true, ScrollAlign::START);
    ScrollToIndex(10, true, ScrollAlign::CENTER);

    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lineHeightMap_.size(), 4);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(0).at(0), 0);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().gridMatrix_.at(3).at(2), 11);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test OnModifyDone
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    CreateFixedItems(10);
    CreateDone();
    auto paintProperty = pattern_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->GetScrollableEvent());
    EXPECT_TRUE(paintProperty->GetScrollBarProperty());
    EXPECT_TRUE(frameNode_->GetFocusHub());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetScrollable());

    /**
     * @tc.steps: step2. Call OnModifyDone
     */
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->multiSelectable_);
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->GetScrollableEvent());
    EXPECT_TRUE(paintProperty->GetScrollBarProperty());
    EXPECT_TRUE(frameNode_->GetFocusHub());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetScrollable());

    /**
     * @tc.steps: step3. Change MultiSelectable and Call OnModifyDone
     */
    pattern_->SetMultiSelectable(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->multiSelectable_);
    EXPECT_FALSE(pattern_->isMouseEventInit_);
}

/**
 * @tc.name: GetEndOffset001
 * @tc.desc: Test GetEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetEndOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetEndOffset(), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: GetEndOffset002
 * @tc.desc: Test GetEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetEndOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    pattern_->SetEdgeEffect(EdgeEffect::SPRING, true);
    EXPECT_EQ(pattern_->GetEndOffset(), 0);
}

/**
 * @tc.name: GetEndOffset003
 * @tc.desc: Test GetEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetEndOffset003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    pattern_->SetEdgeEffect(EdgeEffect::SPRING, true);
    EXPECT_EQ(pattern_->GetEndOffset(), 0);
}

/**
 * @tc.name: GetVisibleSelectedItems001
 * @tc.desc: Test GetVisibleSelectedItems
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetVisibleSelectedItems001, TestSize.Level1)
{
    /**
     * @tc.cases: Set item(index:1) isSelected and call GetVisibleSelectedItems
     * @tc.expected: Has 1 item selected
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    GetChildPattern<GridItemPattern>(frameNode_, 1)->SetSelected(true);
    EXPECT_EQ(pattern_->GetVisibleSelectedItems().size(), 1);
    EXPECT_FALSE(pattern_->irregular_);
}

/**
 * @tc.name: AdaptToChildMainSize001
 * @tc.desc: Test AdaptToChildMainSize
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, AdaptToChildMainSize001, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate, not set grid height
     */
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMaxCount(4);
    CreateFixedItems(20);
    GetGrid();
    CreateDone();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lastMainSize_, 500.f);
}

/**
 * @tc.name: AdaptToChildMainSize002
 * @tc.desc: Test AdaptToChildMainSize
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, AdaptToChildMainSize002, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate, not set grid width
     */
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMaxCount(4);
    CreateFixedItems(20);
    GetGrid();
    CreateDone();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lastMainSize_, 500.f);
}

/**
 * @tc.name: ScrollLayoutRTL001
 * @tc.desc: Test Vertical Grid with Direction RTL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ScrollLayoutRTL001, TestSize.Level1)
{
    float itemWidth = 60.0f;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFixedItems(18);
    CreateDone();

    int32_t colsNumber = 4;
    for (int32_t index = 0; index < 8; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = WIDTH - index % colsNumber * itemWidth - itemWidth;
        float offsetY = floor(index / colsNumber) * ITEM_MAIN_SIZE;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_MAIN_SIZE);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: ScrollLayoutRTL002
 * @tc.desc: Test Horizontal Grid with Direction RTL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ScrollLayoutRTL002, TestSize.Level1)
{
    float itemWidth = 100.0f;
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetIsRTL(TextDirection::RTL);
    CreateFixedItems(18);
    CreateDone();

    int32_t rowsNumber = 4;
    for (int32_t index = 0; index < 8; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = WIDTH - floor(index / rowsNumber) * itemWidth - itemWidth;
        float offsetY = index % rowsNumber * ITEM_MAIN_SIZE;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_MAIN_SIZE);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: AdaptToChildMainSize005
 * @tc.desc: Test Vertical Grid with maxcount and 0 itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, AdaptToChildMainSize005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    ViewAbstract::SetHeight(CalcLength(100));
    model.SetMaxCount(1);
    CreateGridItems(1, 0, 0);
    CreateDone();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().lastMainSize_, 100);
}

/*
 * @tc.name: GetResetMode001
 * @tc.desc: Test Reset Function when have bigItem
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetResetMode001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(40);
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto* wrapper = AceType::RawPtr(frameNode_);
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, -1), std::make_pair(false, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 1), std::make_pair(true, false));

    pattern_->ScrollToIndex(30, false, ScrollAlign::START);
    layoutAlgorithm->info_.startIndex_ = 30;
    frameNode_->childrenUpdatedFrom_ = 20;
    FlushUITasks();

    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 0), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 10), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 25), std::make_pair(true, false));

    layoutAlgorithm->info_.hasBigItem_ = true;

    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 0), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 10), std::make_pair(true, false));
    EXPECT_EQ(layoutAlgorithm->GetResetMode(wrapper, 25), std::make_pair(false, true));
}

/**
 * @tc.name: LayoutWithAutoStretch002
 * @tc.desc: Test Vertical Grid Layout with auto-stretch
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, LayoutWithAutoStretch002, TestSize.Level1)
{
    float itemWidth = 40.0f;
    float itemHeight = 75.0f;
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("repeat(auto-stretch, 75)");
    model.SetRowsGap(Dimension(5));
    model.SetColumnsGap(Dimension(5));
    CreateGridItems(25, itemWidth, itemHeight);
    CreateDone();

    int32_t rowsNumber = 5;
    int32_t columnsNumber = 5;
    float realColumnsGap = 5.f;
    float realRowsGap = 6.25f;
    for (int32_t index = 0; index < 25; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index / columnsNumber * (itemWidth + realColumnsGap);
        float offsetY = index % rowsNumber * (itemHeight + realRowsGap);
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, itemHeight);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: LayoutWithAutoStretch003
 * @tc.desc: Test Horizental Grid Layout with auto-stretch
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, LayoutWithAutoStretch003, TestSize.Level1)
{
    float itemWidth = 40.0f;
    float itemHeight = 75.0f;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("repeat(auto-stretch, 40)");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateGridItems(25, itemWidth, itemHeight);
    CreateDone();

    int32_t rowsNumber = 5;
    int32_t columnsNumber = 5;
    float realColumnsGap = 10.f;
    float realRowsGap = 10.f;
    for (int32_t index = 0; index < 25; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % columnsNumber * (itemWidth + realColumnsGap);
        float offsetY = index / rowsNumber * (itemHeight + realRowsGap);
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, itemHeight);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Stretch001
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch001, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     *
     * 1 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect0.Height(), childRect1.Height());
}

/**
 * @tc.name: Stretch002
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch002, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     * 1: [0]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);
}

/**
 * @tc.name: Stretch003
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch003, TestSize.Level1)
{
    /**
     * 0: [0], [1]
     * 1: [0], [2]
     * 2: [3], [4]
     *
     * 1 and 2 will not stretch
     * 3 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(3);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Height(), childRect3.Height());
}

/**
 * @tc.name: Stretch004
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch004, TestSize.Level1)
{
    /**
     * 0: [0], [0], [1]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 1, ITEM_MAIN_SIZE, 200);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);
    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);
}

/**
 * @tc.name: Stretch005
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch005, TestSize.Level1)
{
    /**
     *  0
     * [0]
     * [1]
     *
     * 1 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr");

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect0.Width(), childRect1.Width());
}

/**
 * @tc.name: Stretch006
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch006, TestSize.Level1)
{
    /**
     *  0
     * [0]
     * [0]
     * [1]
     *
     * 1 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 0, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);
}

/**
 * @tc.name: Stretch007
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch007, TestSize.Level1)
{
    /**
     *  0    1    2
     * [0], [0], [3]
     * [1], [2], [4]
     *
     * 1 and 2 will not stretch
     * 3 will stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr");

    CreateBigItem(0, 0, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(3);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Width(), childRect3.Width());
}

/**
 * @tc.name: Stretch008
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Stretch008, TestSize.Level1)
{
    /**
     *  0    1
     * [0], [0]
     * [0], [0]
     * [1], [2]
     *
     * 1 and 2 will not stretch
     */
    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetRowsTemplate("1fr 1fr 1fr");

    CreateBigItem(0, 1, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateAdaptChildSizeGridItems(2);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Width(), 0);
    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Width(), 0);
}

/**
 * @tc.name: MarginPadding001
 * @tc.desc: Test margin/padding
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, MarginPadding001, TestSize.Level1)
{
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    auto colNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(4);
    CreateDone();

    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    PaddingProperty padding = { CalcLength(2), CalcLength(4), CalcLength(6), CalcLength(8) };
    layoutProperty_->UpdateMargin(margin);
    layoutProperty_->UpdatePadding(padding);
    auto itemLayoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 2);
    itemLayoutProperty->UpdateMargin(margin);
    itemLayoutProperty->UpdatePadding(padding);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect(), RectF(1, 5, 240, 400)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 2), RectF(3, 111, 113, 100)));
}

/**
 * @tc.name: SetEffectEdge001
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SetEffectEdge001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    CreateFixedItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::START);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    UpdateCurrentOffset(-100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    UpdateCurrentOffset(200);
    ASSERT_TRUE(Positive(GetChildY(frameNode_, 0)));
}

/**
 * @tc.name: SetEffectEdge002
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SetEffectEdge002, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateFixedItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::END);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    UpdateCurrentOffset(100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    UpdateCurrentOffset(-200);
    
    EXPECT_LE(GetChildY(frameNode_, 0), 0);
}

/**
 * @tc.name: SpringAnimationTest001
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest001, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -126.00447);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and increase grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */

    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -63.002243);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest002
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest002, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -126.00447);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -63.002243);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest003
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest003, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 279.38562);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and increase grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 139.69281);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest004
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest004, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 279.38562);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 139.69281);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest005
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest005, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(21);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -79.385628);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -89.692818);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: SpringAnimationTest006
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest006, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(-200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -79.385628);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    // the value of (currentOffset + gridMainSizeDelta) is greater than lineHeight(200), so move to next line
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -89.692818);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: SpringAnimationTest007
 * @tc.desc: Test Grid change height during spring animation. GridItem is fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest007, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(40);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1400.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 279.38562);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 139.69281);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest008
 * @tc.desc: Test Grid change height during spring animation. GridItem is not fully filled Grid.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, SpringAnimationTest008, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(40);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    GestureEvent info;
    info.SetMainVelocity(1400.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 279.38562);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: currentOffset will not change with the grid height
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 50))));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 139.69281);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: TestIrregularGridWithScrollToIndex001
 * @tc.desc: Test Irregular Grid with columnStart Measure when scroll to index
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, TestIrregularGridWithScrollToIndex001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    /**s
     * 0:  [0],  [0],  [0],  [0]
     * 1:  [1],  [1],  [1],  [1]
     * 2:  [2],  [2],  [2],  [2]
     * 3:  [3],  [3],  [4],  [4]
     * 4:  [5],  [6],  [4],  [4]
     * 5:  [7],  [8],  [9],  [9]
     * 6:  [10], [11], [12], [13]
     * 7:  [14], [14], [14], [14]
     * 8:  [15], [15], [16], [17]
     * 9:  [18], [18], [18], [18]
     */
    CreateBigItem(0, 0, 0, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(1, 1, 0, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(2, 2, 0, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(3, 3, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(3, 4, 2, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE * 2);
    CreateBigItem(4, 4, 0, 0, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(4, 4, 1, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(5, 5, 0, 0, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(5, 5, 1, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(5, 5, 2, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(6, 6, 0, 0, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(6, 6, 1, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(6, 6, 2, 2, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(6, 6, 3, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(7, 7, 0, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(8, 8, 0, 1, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(8, 8, 2, 2, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(8, 8, 3, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateBigItem(9, 9, 0, 3, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    ScrollToIndex(10, false, ScrollAlign::START);

    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE / 2, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(pattern_->info_.gridMatrix_[5].size(), 4);
}

/**
 * @tc.name: TestIrregularGridMeasureForward001
 * @tc.desc: Test Irregular Grid with optional Measure forward
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, TestIrregularGridMeasureForward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    GridLayoutOptions option;
    option.irregularIndexes = { 0, 2 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    for (int i = 0; i < 15; i++) {
        pattern_->ScrollBy(-100);
        FlushUITasks();
    }
    EXPECT_NE(pattern_->info_.gridMatrix_[0][0], pattern_->info_.gridMatrix_[1][0]);
}

/**
 * @tc.name: TestLayoutColumn001
 * @tc.desc: Test whether the Grid can be normally laid out when its child node is Column.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, TestLayoutColumn001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    GridLayoutOptions option;
    model.SetLayoutOptions(option);
    CreateColumns(30);
    CreateDone();

    int32_t colsNumber = 4;
    float itemWidth = 60;
    for (int32_t index = 0; index < 8; index++) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * itemWidth;
        float offsetY = floor(index / colsNumber) * ITEM_MAIN_SIZE;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_MAIN_SIZE);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Test Calculate CacheCount
 * @tc.desc: Test Calculate CacheCount
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, CachedCount001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    model.SetLayoutOptions({});
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto* wrapper = AceType::RawPtr(frameNode_);
    auto cache = algo->CalculateCachedCount(wrapper, 2);

    EXPECT_EQ(cache.first, 6);
    EXPECT_EQ(cache.second, 6);

    for (int32_t i = 0; i < 10; i++) {
        pattern_->ScrollBy(ITEM_MAIN_SIZE);
        FlushUITasks();
        auto cache = algo->CalculateCachedCount(wrapper, 2);
        EXPECT_EQ(cache.first, 6);
        EXPECT_EQ(cache.second, 6);
    }
}

/**
 * @tc.name: Test Calculate CacheCount
 * @tc.desc: Test Calculate CacheCount
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, CachedCount002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 1, 2, 3, 4, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_EQ(cacheStart, 0);
    EXPECT_EQ(cacheEnd, 4);

    algo->info_.startIndex_ = 1;
    algo->info_.startMainLineIndex_ = 1;
    algo->info_.endIndex_ = 4;
    algo->info_.endMainLineIndex_ = 4;
    cacheStart = algo->CalculateStartCachedCount(option, 2);
    cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_EQ(cacheStart, 1);
    EXPECT_EQ(cacheEnd, 6);

    algo->info_.startIndex_ = 4;
    algo->info_.startMainLineIndex_ = 4;
    algo->info_.endIndex_ = 11;
    algo->info_.endMainLineIndex_ = 7;
    cacheStart = algo->CalculateStartCachedCount(option, 2);
    cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_EQ(cacheStart, 2);
    EXPECT_EQ(cacheEnd, 4);
}

/**
 * @tc.name: Test Calculate CacheCount
 * @tc.desc: Test Calculate CacheCount
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, CachedCount003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 9, 10, 11, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_EQ(cacheStart, 0);
    EXPECT_EQ(cacheEnd, 2);
}

/**
 * @tc.name: Test Calculate CacheCount
 * @tc.desc: Test Calculate CacheCount
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, CachedCount004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 50 };
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startMainLineIndex_ = 1;
    pattern_->info_.endMainLineIndex_ = 3;
    pattern_->info_.startIndex_ = 9;
    pattern_->info_.endIndex_ = 17;
    pattern_->info_.gridMatrix_  = {
        { 1, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
        { 2, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
        { 3, { { 0, 15 }, { 1, 16 }, { 2, 17 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_EQ(cacheStart, 6);
    EXPECT_EQ(cacheEnd, 6);
}

HWTEST_F(GridScrollLayoutTestNg, isFadingBottomTest001, TestSize.Level1) {
    // Arrange
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    pattern->info_.lastMainSize_ = 100.0f;
    pattern->info_.contentEndPadding_ = 10.0f;
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 10;
    pattern->info_.childrenCount_ = 11;
    pattern->info_.totalHeightOfItemsInView_ = 90.0f;
    pattern->info_.currentOffset_ = 50.0f;
    pattern->info_.offsetEnd_ = false;

    // Act
    bool result = pattern->IsFadingBottom();

    // Assert
    EXPECT_TRUE(result);
}

HWTEST_F(GridScrollLayoutTestNg, isFadingBottomTest002, TestSize.Level1) {
    // Arrange
    auto pattern = AceType::MakeRefPtr<GridPattern>();
    pattern->info_.lastMainSize_ = 100.0f;
    pattern->info_.contentEndPadding_ = 10.0f;
    pattern->info_.startIndex_ = 0;
    pattern->info_.endIndex_ = 10;
    pattern->info_.childrenCount_ = 11;
    pattern->info_.totalHeightOfItemsInView_ = 110.0f;
    pattern->info_.currentOffset_ = 50.0f;
    pattern->info_.offsetEnd_ = true;

    // Act
    bool result = pattern->IsFadingBottom();

    // Assert
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FadingEdge001
 * @tc.desc: Test FadingEdge property
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, FadingEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set FadingEdge
     * @tc.expected: Would create a overlayNode attach to grid
     */
    const Dimension fadingEdgeLength = Dimension(10.0f);
    GridModelNG model = CreateGrid();
    ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_TRUE(frameNode_->GetOverlayNode());
    EXPECT_TRUE(paintProperty_->GetFadingEdge().value_or(false));
    EXPECT_EQ(paintProperty_->GetFadingEdgeLength().value(), fadingEdgeLength);

    /**
     * @tc.steps: step2. Change FadingEdge to false
     * @tc.expected: There is no fading edge
     */
    ScrollableModelNG::SetFadingEdge(AceType::RawPtr(frameNode_), false, fadingEdgeLength);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_TRUE(frameNode_->GetOverlayNode());
    EXPECT_FALSE(paintProperty_->GetFadingEdge().value_or(false));
}

/**
 * @tc.name: FadingEdge002
 * @tc.desc: Test FadingEdge property
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, FadingEdge002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set FadingEdge
     * @tc.expected: Would create a overlayNode attach to grid
     */
    const Dimension fadingEdgeLength = Dimension(10.0f);
    GridModelNG model = CreateGrid();
    ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_TRUE(frameNode_->GetOverlayNode());

    /**
     * @tc.steps: step2. The grid at top
     * @tc.expected: Fading bottom
     */
    auto paintMethod = UpdateContentModifier();
    EXPECT_FALSE(paintMethod->isFadingTop_);
    EXPECT_TRUE(paintMethod->isFadingBottom_);

    /**
     * @tc.steps: step3. The grid at middle
     * @tc.expected: Fading both
     */
    ScrollTo(100.0f);
    paintMethod = UpdateContentModifier();
    EXPECT_TRUE(paintMethod->isFadingTop_);
    EXPECT_TRUE(paintMethod->isFadingBottom_);

    /**
     * @tc.steps: step4. The grid at bottom
     * @tc.expected: Fading top
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    paintMethod = UpdateContentModifier();
    EXPECT_TRUE(paintMethod->isFadingTop_);
    EXPECT_FALSE(paintMethod->isFadingBottom_);
}

/*
 * @tc.name: Test IsPredictOutOfCacheRange
 * @tc.desc: Test Normal range with valid cache
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, IsPredictOutOfCacheRange001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startIndex_ = 10;
    pattern_->info_.endIndex_ = 20;
    pattern_->info_.defCachedCount_ = 2;
    pattern_->info_.crossCount_ = 3; // cacheCount = 2*3=6 → range [4,26]

    // Boundary checks
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(4));  // start - cacheCount
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(26)); // end + cacheCount
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(3));   // below extended range
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(27));  // above extended range
}

/**
 * @tc.name: Test IsPredictOutOfCacheRange
 * @tc.desc: Test Zero cache count (only check original range)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, IsPredictOutOfCacheRange002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetCachedCount(0, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startIndex_ = 5;
    pattern_->info_.endIndex_ = 5;
    pattern_->info_.defCachedCount_ = 0; // cacheCount = 0 → range [5,5]
    pattern_->info_.crossCount_ = 1;

    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(4)); // below
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(5)); // exact
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(6)); // above
}

/*
 * @tc.name: Test IsPredictOutOfCacheRange
 * @tc.desc: Test Normal range with valid cache.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, IsPredictOutOfCacheRange003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startIndex_ = 10;
    pattern_->info_.endIndex_ = 20;
    pattern_->info_.defCachedCount_ = 1;
    pattern_->info_.crossCount_ = 3; // cacheCount = 2*3=6 → range [7-9,21-23]

    // Boundary checks
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(10));
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(20));
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(9));
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(21));

    pattern_->info_.startIndex_ = INT32_MIN;
    pattern_->info_.endIndex_ = INT32_MAX;

    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(INT32_MIN)); // Lower bound
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(0));         // Mid value
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(INT32_MAX)); // Upper bound
}

/*
 * @tc.name: Test IsPredictOutOfCacheRange
 * @tc.desc: Test Normal range with valid cache.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, IsPredictOutOfCacheRange004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startIndex_ = INT32_MIN;
    pattern_->info_.endIndex_ = INT32_MAX - 1;
    pattern_->info_.childrenCount_ = INT32_MAX;

    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(INT32_MIN));     // Lower bound
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(0));             // Mid value
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(INT32_MAX - 1)); // Upper bound

    pattern_->info_.startIndex_ = -2;
    pattern_->info_.endIndex_ = 2;
    // cacheCount = 1*3=3 → range is [-5, -3] and [3, 5]
    pattern_->info_.defCachedCount_ = 1;
    pattern_->info_.crossCount_ = 3;

    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(-2));  // Lower bound
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(0));   // Mid value (zero)
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(2));   // Upper bound
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(-3)); // Below lower bound
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(3));  // Above upper bound

    pattern_->info_.startIndex_ = -5;
    pattern_->info_.endIndex_ = -1;
    // cacheCount = 1*3=3 → range is [-11, -6] and [0, 5]
    pattern_->info_.defCachedCount_ = 2;
    pattern_->info_.crossCount_ = 3;
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(-5));  // Lower bound
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(-3));  // Mid value
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(-1));  // Upper bound
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(-6)); // Below lower bound
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(0));  // Above upper bound
}

/*
 * @tc.name: Test IsPredictOutOfCacheRange
 * @tc.desc: Test cache range when the firstRepeatCount is less than childrenCount.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, IsPredictOutOfCacheRange005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();
    EXPECT_EQ(pattern_->info_.GetChildrenCount(), 50);

    pattern_->info_.startIndex_ = 10;
    pattern_->info_.endIndex_ = 20;
    pattern_->info_.defCachedCount_ = 1;

    // cacheCount = 1*3=3 → range is [7, 9] and [21, 23]
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.firstRepeatCount_ = 22;

    EXPECT_EQ(pattern_->info_.GetChildrenCount(), 22);
    // Boundary checks
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(20));
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(21));
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(22));
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(23));
    EXPECT_FALSE(pattern_->IsPredictOutOfCacheRange(9));
    EXPECT_TRUE(pattern_->IsPredictOutOfCacheRange(10));
}

HWTEST_F(GridScrollLayoutTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetCachedCount(0, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(1);
    CreateDone();

    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->info_.currentOffset_, -10.f);
    FlushUITasks();

    pattern_->UpdateCurrentOffset(10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->info_.currentOffset_, 10.f);
}

/**
 * @tc.name: Test GetTotalOffset
 * @tc.desc: Test GetTotalOffset when updating an item's height in the viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetTotalOffsetTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();

    pattern_->ScrollToIndex(30, false, ScrollAlign::START);
    FlushUITasks();
    auto offset = pattern_->GetTotalOffset();
    auto gridItemProp = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 29);
    EXPECT_NE(gridItemProp, nullptr);
    gridItemProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(ITEM_MAIN_SIZE + 50))));
    FlushUITasks();
    EXPECT_EQ(offset, pattern_->GetTotalOffset());
}
} // namespace OHOS::Ace::NG
