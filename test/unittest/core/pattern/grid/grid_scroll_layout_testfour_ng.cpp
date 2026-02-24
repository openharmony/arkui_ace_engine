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
class GridScrollLayoutTestFourNg : public GridTestNg {
public:
    void UpdateLayoutInfo();
    RefPtr<GridPaintMethod> UpdateOverlayModifier();
    RefPtr<GridPaintMethod> UpdateContentModifier();
    void SimulateScrollGesture(float mainVelocity, float mainDelta);
};

void GridScrollLayoutTestFourNg::UpdateLayoutInfo()
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

RefPtr<GridPaintMethod> GridScrollLayoutTestFourNg::UpdateOverlayModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

RefPtr<GridPaintMethod> GridScrollLayoutTestFourNg::UpdateContentModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<GridPaintMethod> paintMethod = AceType::DynamicCast<GridPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

void GridScrollLayoutTestFourNg::SimulateScrollGesture(float mainVelocity, float mainDelta)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    info.SetMainDelta(mainDelta);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
}

/**
 * @tc.name: TestOffsetAfterSpring001
 * @tc.desc: Test Grid prevOffset_ equals currentOffset_ after spring
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, TestGridOffsetAfterSpring001, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(1);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetColumnsGap(Dimension(10));
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    model.SetLayoutOptions(option);
    CreateFixedItems(40);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    SimulateScrollGesture(-200.f, -200.f);
    EXPECT_TRUE(pattern_->IsAtBottom());


    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(pattern_->info_.prevOffset_, pattern_->info_.currentOffset_);
}

/**
 * @tc.name: SpringAnimationTest009
 * @tc.desc: Test Grid change height during spring animation. Grid becomes unscrollable.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest009, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);

    bool isScrollStopCalled = false;
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    model.SetOnScrollStop(scrollStop);
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    SimulateScrollGesture(-1200.f, -200.f);

    /**
     * @tc.steps: step2. increase grid height to be larger than the content during animation
     * @tc.expected: scrollable_ is false and currentOffset_ is 0
     */
    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT * 2))));
    FlushUITasks();
    EXPECT_FALSE(pattern_->scrollable_);
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(isScrollStopCalled);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: SpringAnimationTest010
 * @tc.desc: Test GridItem change height during spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest010, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    GridLayoutOptions option;
    option.irregularIndexes = { 0, 3 };
    model.SetLayoutOptions(option);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(1, 100);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 80);
    CreateFixedHeightItems(1, 800);
    CreateFixedHeightItems(1, 30);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());
    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    SimulateScrollGesture(-200.f, -200.f);
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -646.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease gridItem height during animation
     * @tc.expected: currentOffset will not change with the gridItem height
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 3)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(500)));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -238.2085);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -130);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: SpringAnimationTest011
 * @tc.desc: Test GridItem change height during spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest011, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 800);
    CreateFixedHeightItems(1, 50);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());
    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */
    SimulateScrollGesture(-200.f, -200.f);
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -666.41699);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease gridItem height during animation
     * @tc.expected: currentOffset will not change with the gridItem height
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 1)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(100)));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 91.791504);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: SpringAnimationTest012
 * @tc.desc: Test GridItem height change during spring animation when mainLength >= 0.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest012, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 50);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Scroll to top and simulate a small scrolling gesture.
     * @tc.expected: Grid currentOffset is non-negative, spring animation triggered.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    SimulateScrollGesture(200.f, 200.f);

    /**
     * @tc.steps: step2. Verify currentOffset is non-negative before height change.
     * @tc.expected: currentOffset should be >= 0.
     */
    float offsetBeforeHeightChange = pattern_->info_.currentOffset_;
    EXPECT_TRUE(offsetBeforeHeightChange >= 0.0f);

    /**
     * @tc.steps: step3. Play spring animation and change gridItem height during animation.
     * @tc.expected: currentOffset will not be adjusted by deltaHeight when mainLength >= 0.
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 1)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(100)));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 108.2085);

    /**
     * @tc.steps: step4. Verify offset behavior with non-negative mainLength.
     * @tc.expected: currentOffset should not have the special adjustment applied.
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest013
 * @tc.desc: Test GridItem height change during spring animation when mainLength < 0.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest013, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(3);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 800);
    CreateFixedHeightItems(1, 50);
    CreateFixedHeightItems(1, 50);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Simulate a scrolling gesture at bottom.
     * @tc.expected: Grid trigger spring animation with negative currentOffset.
     */
    SimulateScrollGesture(-200.f, -200.f);

    /**
     * @tc.steps: step2. Verify currentOffset is negative (mainLength < 0).
     * @tc.expected: currentOffset should be < 0, enabling special deltaHeight adjustment.
     */
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, -716.41699);

    /**
     * @tc.steps: step3. Play spring animation frame by frame, decrease gridItem height during animation.
     * @tc.expected: currentOffset will be adjusted by deltaHeight since mainLength < 0.
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 1)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(100)));
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 5.7219849);

    /**
     * @tc.steps: step4. Continue animation and verify offset adjustment behavior.
     * @tc.expected: currentOffset changes as expected with negative mainLength logic.
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 77.860962);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: SpringAnimationTest014
 * @tc.desc: Test GridItem height decrease during spring animation with mainLength > 0.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest014, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    /**
     * Create 4 items with height 40 and 1 item with height 80
     * Total height = 4*40 + 80 = 240
     * Grid height = 400 (default)
     */
    CreateFixedHeightItems(4, 40);
    CreateFixedHeightItems(1, 80);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step1. Simulate a downward scrolling gesture at bottom (pull down).
     * @tc.expected: Grid trigger spring animation with negative currentOffset.
     */
    SimulateScrollGesture(-20.f, -200.f);

    float initialOffset = pattern_->info_.currentOffset_;
    EXPECT_TRUE(initialOffset < 0.0f);

    /**
     * @tc.steps: step2. Play spring animation and decrease last gridItem height from 80 to 50.
     * @tc.expected: When measuring the last item, deltaHeight = 80 - 50 = 30 > 0,
     *             but mainLength > 0 at that point, so currentOffset should not be adjusted.
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 4)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(50)));
    FlushUITasks();

    /**
     * @tc.steps: step3. Verify that currentOffset follows normal spring animation behavior.
     * @tc.expected: currentOffset should not have the special deltaHeight adjustment applied
     *             because mainLength > 0 when measuring the last item.
     */
    float offsetAfterHeightChange = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(offsetAfterHeightChange, -28.208504);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    float finalOffset = pattern_->info_.currentOffset_;
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    /**
     * @tc.steps: step4. Verify currentOffset behavior.
     * @tc.expected: currentOffset should gradually return to 0 through normal spring animation,
     *             without the special adjustment that would occur if mainLength < 0.
     */
    EXPECT_FLOAT_EQ(finalOffset, 0);
}

/**
 * @tc.name: SpringAnimationTest015
 * @tc.desc: Test GridItem height change when spring animation is NOT running.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest015, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    /**
     * Create items: 50 + 50 + 50 = 150 total height
     * Grid height = 400 (default), content doesn't fill viewport
     * No spring animation will be triggered
     */
    CreateFixedHeightItems(3, 50);
    CreateDone();

    /**
     * @tc.steps: step1. Verify grid is at top with no offset.
     * @tc.expected: currentOffset should be 0, no spring animation running.
     */
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0.0f);

    /**
     * @tc.steps: step2. Decrease middle gridItem height from 50 to 30.
     * @tc.expected: deltaHeight = 50 - 30 = 20 > 0, but isScrollableSpringMotionRunning = false,
     *             so the special compensation branch should NOT be executed.
     */
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 1)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(30)));
    FlushUITasks();

    /**
     * @tc.steps: step3. Verify currentOffset remains 0 without any special adjustment.
     * @tc.expected: currentOffset should still be 0, indicating no special deltaHeight
     *             compensation was applied (since spring animation was not running).
     */
    float offsetAfterHeightChange = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(offsetAfterHeightChange, 0.0f);
}

/**
 * @tc.name: SpringAnimationTest016
 * @tc.desc: Test last GridItem height change, all items out of view during spring animation at bottom edge.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SpringAnimationTest016, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    /**
     * Create 3 items with height 50, then 1 item with height 800
     * Total height = 50 + 50 + 50 + 800 = 950
     * Grid height = 400 (default), so scrollable
     */
    CreateFixedHeightItems(3, 50);
    CreateFixedHeightItems(1, 800);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll to bottom.
     * @tc.expected: Grid should be at bottom.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Simulate an upward scrolling gesture at bottom to trigger spring animation.
     * @tc.expected: Grid trigger spring animation with negative currentOffset.
     */
    SimulateScrollGesture(-200.f, -200.f);

    float initialOffset = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(initialOffset, -616.41699);

    /**
     * @tc.steps: step3. Play spring animation and decrease last gridItem height from 800 to 100.
     * @tc.expected: currentOffset should adjust based on deltaHeight during spring animation.
     */
    MockAnimationManager::GetInstance().Tick();
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 3)
            ->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(100)));
    FlushUITasks();

    float offsetAfterHeightChange = pattern_->info_.currentOffset_;
    EXPECT_FLOAT_EQ(offsetAfterHeightChange, -8.2084961);

    /**
     * @tc.steps: step4. Verify spring animation completes.
     * @tc.expected: currentOffset should return to 0 after animation completes.
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    float finalOffset = pattern_->info_.currentOffset_;
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    EXPECT_FLOAT_EQ(finalOffset, 0);
}

/**
 * @tc.name: TestIrregularGridWithScrollToIndex001
 * @tc.desc: Test Irregular Grid with columnStart Measure when scroll to index
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, TestIrregularGridWithScrollToIndex001, TestSize.Level1)
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
 * @tc.name: TestScrollToIndexCenter001
 * @tc.desc: Test Grid Measure when scroll to index 0 in center
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, TestScrollToIndexCenter001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedHeightItems(6, 100);
    CreateDone();

    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 3);
    ScrollToIndex(0, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 3);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 3);
}

/**
 * @tc.name: TestIrregularGridMeasureForward001
 * @tc.desc: Test Irregular Grid with optional Measure forward
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, TestIrregularGridMeasureForward001, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, TestLayoutColumn001, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount001, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount002, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount003, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount004, TestSize.Level1)
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

HWTEST_F(GridScrollLayoutTestFourNg, isFadingBottomTest001, TestSize.Level1) {
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

HWTEST_F(GridScrollLayoutTestFourNg, isFadingBottomTest002, TestSize.Level1) {
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
HWTEST_F(GridScrollLayoutTestFourNg, FadingEdge001, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, FadingEdge002, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, IsPredictOutOfCacheRange001, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, IsPredictOutOfCacheRange002, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, IsPredictOutOfCacheRange003, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, IsPredictOutOfCacheRange004, TestSize.Level1)
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
HWTEST_F(GridScrollLayoutTestFourNg, IsPredictOutOfCacheRange005, TestSize.Level1)
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

HWTEST_F(GridScrollLayoutTestFourNg, UpdateCurrentOffset001, TestSize.Level1)
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
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(10);
    CreateDone();
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(0.0f));
    PaddingProperty padding = { CalcLength(2), CalcLength(4), CalcLength(6), CalcLength(8) };
    layoutProperty_->UpdatePadding(padding);
    FlushUITasks();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    pattern_->info_.offsetEnd_ = true;
    pattern_->UpdateCurrentOffset(-10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->info_.currentOffset_, -10.f);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(10);
    CreateDone();
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(0.0f));
    PaddingProperty padding = { CalcLength(2), CalcLength(4), CalcLength(6), CalcLength(8) };
    layoutProperty_->UpdatePadding(padding);
    FlushUITasks();
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    pattern_->UpdateCurrentOffset(10.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->info_.currentOffset_, 10.f);
}
/**
 * @tc.name: Test GetTotalOffset
 * @tc.desc: Test GetTotalOffset when updating an item's height in the viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, GetTotalOffsetTest001, TestSize.Level1)
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

/**
 * @tc.name: Test Skip large offset
 * @tc.desc: Test OnScrollIndex with big cachedCount by skip large offset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, SkipLargeOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(16, false);
    CreateFixedItems(100);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 90);
    EXPECT_EQ(pattern_->info_.endIndex_, 99);

    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 15);
    EXPECT_EQ(pattern_->info_.endIndex_, 26);
}
} // namespace OHOS::Ace::NG