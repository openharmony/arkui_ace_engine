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
#include "core/components_ng/render/paint_wrapper.h"
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/common/text_field_manager_ng.h"

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
    pattern_->info_.gridMatrix_ = {
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

/**
 * @tc.name: CachedCount005
 * @tc.desc: Test CalculateStartCachedCount with multiple irregular indexes
 *           Verify fix: correct order of iter-- and *iter (originally L359 undefined behavior)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(3, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 5, 8, 12, 14 };
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startMainLineIndex_ = 6;
    pattern_->info_.endMainLineIndex_ = 8;
    pattern_->info_.startIndex_ = 18;
    pattern_->info_.endIndex_ = 26;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 3);
    EXPECT_GE(cacheStart, 0);
}

/**
 * @tc.name: CachedCount006
 * @tc.desc: Test CalculateEndCachedCount with multiple irregular indexes
 *           Verify fix: correct order of iter++ and *iter (originally L418 undefined behavior)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount006, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(3, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 12, 15, 18, 20 };
    model.SetLayoutOptions(option);
    CreateFixedItems(50);
    CreateDone();

    pattern_->info_.startMainLineIndex_ = 2;
    pattern_->info_.endMainLineIndex_ = 4;
    pattern_->info_.startIndex_ = 6;
    pattern_->info_.endIndex_ = 14;
    pattern_->info_.childrenCount_ = 50;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 3);
    EXPECT_GE(cacheEnd, 0);
}

/**
 * @tc.name: CachedCount007
 * @tc.desc: Test both methods with consecutive irregular indexes at boundary
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount007, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 9, 10, 11, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(20);
    CreateDone();

    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 5;
    pattern_->info_.startIndex_ = 6;
    pattern_->info_.endIndex_ = 10;
    pattern_->info_.childrenCount_ = 20;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    EXPECT_GE(cacheStart, 0);
    EXPECT_GE(cacheEnd, 0);
}

/**
 * @tc.name: CachedCount008
 * @tc.desc: Test CalculateStartCachedCount when bottom is completely out of bounds.
 *           All content scrolled above the viewport: startMainLineIndex_ > endMainLineIndex_
 *           and endMainLineIndex_ >= 0. startIndex_ is stale, so the method must use
 *           GetChildrenCount() instead of startIndex_.
 *           Note: the state below is synthetic for branch coverage — the runtime produces
 *           startMainLineIndex_ = endMainLineIndex_ + 1 with startIndex_ stale at the first
 *           item of the last measured line. The expected 35 is therefore a guard value, not
 *           a realistic cache size (a real cachedCount=2 window spans ~6 items).
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount008, TestSize.Level1)
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

    // Bottom out of bounds (synthetic: runtime yields startMainLineIndex_ = endMainLineIndex_ + 1
    // and startIndex_ = first item of the last measured line; +2 and 18 here force the
    // gridMatrix branch with a wide gap):
    // startMainLineIndex_ (6) > endMainLineIndex_ (4), both >= 0
    pattern_->info_.startMainLineIndex_ = 6;
    pattern_->info_.endMainLineIndex_ = 4;
    // startIndex_ is stale (18), not GetChildrenCount() (50)
    pattern_->info_.startIndex_ = 18;
    pattern_->info_.endIndex_ = 17;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.gridMatrix_ = {
        { 3, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
        { 4, { { 0, 15 }, { 1, 16 }, { 2, 17 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // startMainLineIndex_ - cachedCount = 6 - 2 = 4, found in gridMatrix_
    // index = 15 (first item in line 4)
    // effectiveStartIndex = GetChildrenCount() = 50 (bottom out-of-bounds)
    // return effectiveStartIndex - index = 50 - 15 = 35
    EXPECT_EQ(cacheStart, 35);
}

/**
 * @tc.name: CachedCount009
 * @tc.desc: Test CalculateEndCachedCount when top is completely out of bounds.
 *           endMainLineIndex_ < 0 (all content pushed below viewport via top overscroll).
 *           endIndex_ is stale, so the method must use -1 as effective end (index + 1)
 *           instead of stale endIndex_.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount009, TestSize.Level1)
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

    // Top out of bounds: endMainLineIndex_ < 0
    pattern_->info_.startMainLineIndex_ = 0;
    pattern_->info_.endMainLineIndex_ = -1;
    pattern_->info_.startIndex_ = 0;
    // endIndex_ is stale (7), active range should be [-1, -1]
    pattern_->info_.endIndex_ = 7;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // endMainLineIndex_ + cachedCount = -1 + 2 = 1, found in gridMatrix_
    // index = 5 (last item in line 1)
    // effectiveEndIndex = -1 (top out-of-bounds)
    // return index - effectiveEndIndex = 5 - (-1) = 6
    EXPECT_EQ(cacheEnd, 6);
}

/**
 * @tc.name: CachedCount010
 * @tc.desc: Test CalculateEndCachedCount when both line indices are -1 (non-inverted negative range).
 *           This can occur in an initial/empty state. The effectiveEndIndex condition
 *           (startMainLineIndex_ > endMainLineIndex_) must evaluate to false (-1 > -1 == false),
 *           so effectiveEndIndex stays as endIndex_ (3). The method should use the normal
 *           path: index - effectiveEndIndex.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount010, TestSize.Level1)
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

    // Both indices -1: NOT an inverted range (-1 is not greater than -1)
    // effectiveEndIndex = endIndex_ = 3 (condition false)
    pattern_->info_.startMainLineIndex_ = -1;
    pattern_->info_.endMainLineIndex_ = -1;
    pattern_->info_.startIndex_ = 0;
    pattern_->info_.endIndex_ = 3;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // endMainLineIndex_ + cachedCount = -1 + 2 = 1, found in gridMatrix_
    // index = 5 (last item in line 1)
    // Not inverted (-1 > -1 is false) → effectiveEndIndex = endIndex_ = 3
    // return index - effectiveEndIndex = 5 - 3 = 2
    EXPECT_EQ(cacheEnd, 2);
}

/**
 * @tc.name: CachedCount011
 * @tc.desc: Test CalculateEndCachedCount with a normal (non-inverted) positive range.
 *           startMainLineIndex_ (3) <= endMainLineIndex_ (5), endMainLineIndex_ >= 0.
 *           effectiveEndIndex stays as endIndex_ (11); the normal path index - effectiveEndIndex
 *           should be used.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount011, TestSize.Level1)
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

    // Normal range: start (3) <= end (5), both >= 0 — no overscroll
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 5;
    pattern_->info_.startIndex_ = 6;
    pattern_->info_.endIndex_ = 11;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.gridMatrix_ = {
        { 5, { { 0, 12 }, { 1, 13 }, { 2, 14 } } },
        { 7, { { 0, 21 }, { 1, 22 }, { 2, 23 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // endMainLineIndex_ + cachedCount = 5 + 2 = 7, found in gridMatrix_
    // index = 23 (last item in line 7)
    // Not inverted (3 > 5 is false) → effectiveEndIndex = endIndex_ = 11
    // return index - effectiveEndIndex = 23 - 11 = 12
    EXPECT_EQ(cacheEnd, 12);
}

/**
 * @tc.name: CachedCount012
 * @tc.desc: Test CalculateStartCachedCount with a normal (non-inverted) positive range.
 *           startMainLineIndex_ (3) <= endMainLineIndex_ (5), endMainLineIndex_ >= 0.
 *           effectiveStartIndex stays as startIndex_ (6); the normal path
 *           effectiveStartIndex - index should be used.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount012, TestSize.Level1)
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

    // Normal range: start (3) <= end (5), both >= 0 — no overscroll
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 5;
    pattern_->info_.startIndex_ = 6;
    pattern_->info_.endIndex_ = 11;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.gridMatrix_ = {
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
        { 3, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // startMainLineIndex_ - cachedCount = 3 - 2 = 1, found in gridMatrix_
    // index = 3 (first item in line 1)
    // Not inverted (3 > 5 is false) → effectiveStartIndex = startIndex_ = 6
    // return effectiveStartIndex - index = 6 - 3 = 3
    EXPECT_EQ(cacheStart, 3);
}

/**
 * @tc.name: CachedCount013
 * @tc.desc: Test CalculateStartCachedCount when bottom is completely out of bounds
 *           with few children, triggering the early-return path
 *           (startMainLineIndex_ - cachedCount <= 0). Three columns, two children,
 *           child 0 occupies a full row, cachedCount=2.
 *           startMainLineIndex_ (2) > endMainLineIndex_ (1), both >= 0.
 *           effectiveStartIndex = GetChildrenCount() = 2; min(2, start=6) = 2.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount013, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0 };
    model.SetLayoutOptions(option);
    CreateFixedItems(2);
    CreateDone();

    // Bottom out of bounds with few children: startMainLineIndex_ (2) > endMainLineIndex_ (1)
    pattern_->info_.startMainLineIndex_ = 2;
    pattern_->info_.endMainLineIndex_ = 1;
    pattern_->info_.startIndex_ = 1; // stale
    pattern_->info_.endIndex_ = 1;
    pattern_->info_.childrenCount_ = 2;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // startMainLineIndex_ - cachedCount = 2 - 2 = 0 <= 0 → early return path
    // effectiveStartIndex = GetChildrenCount() = 2 (bottom out-of-bounds)
    // return min(effectiveStartIndex, start) = min(2, 6) = 2
    EXPECT_EQ(cacheStart, 2);
}

/**
 * @tc.name: CachedCount014
 * @tc.desc: Test CalculateEndCachedCount when top is completely out of bounds
 *           with few children. Three columns, two children, child 0 occupies
 *           a full row, cachedCount=2. startMainLineIndex_ (0) > endMainLineIndex_ (-1),
 *           endMainLineIndex_ < 0 → effectiveEndIndex = -1. The gridMatrix path
 *           (find(endMainLineIndex_ + cachedCount) = find(1)) returns the last
 *           item of line 1 (1) minus (-1) = 2.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount014, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0 };
    model.SetLayoutOptions(option);
    CreateFixedItems(2);
    CreateDone();

    // Top out of bounds with few children: endMainLineIndex_ < 0
    pattern_->info_.startMainLineIndex_ = 0;
    pattern_->info_.endMainLineIndex_ = -1;
    pattern_->info_.startIndex_ = 0; // stale
    pattern_->info_.endIndex_ = 0;
    pattern_->info_.childrenCount_ = 2;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // effectiveEndIndex = -1 (top out-of-bounds), remaining = 2 - 1 - (-1) = 2
    // matrix find(-1 + 2 = 1) → line 1, last item = 1 → return 1 - (-1) = 2
    EXPECT_EQ(cacheEnd, 2);
}

/**
 * @tc.name: CachedCount015
 * @tc.desc: Test CalculateStartCachedCount with few children but a normal
 *           (non-inverted) range, triggering the early-return path
 *           (startMainLineIndex_ - cachedCount <= 0). effectiveStartIndex stays
 *           as startIndex_ (1); min(1, start=6) = 1 is returned.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount015, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0 };
    model.SetLayoutOptions(option);
    CreateFixedItems(2);
    CreateDone();

    // Normal range with few children: start (1) <= end (2), both >= 0 — no overscroll
    pattern_->info_.startMainLineIndex_ = 1;
    pattern_->info_.endMainLineIndex_ = 2;
    pattern_->info_.startIndex_ = 1;
    pattern_->info_.endIndex_ = 1;
    pattern_->info_.childrenCount_ = 2;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // startMainLineIndex_ - cachedCount = 1 - 2 = -1 <= 0 → early return path
    // Not inverted (1 > 2 is false) → effectiveStartIndex = startIndex_ = 1
    // return min(effectiveStartIndex, start) = min(1, 6) = 1
    EXPECT_EQ(cacheStart, 1);
}

/**
 * @tc.name: CachedCount016
 * @tc.desc: Test CalculateEndCachedCount with few children but a normal
 *           (non-inverted) range. No overscroll, endIndex_ = 1 is the last
 *           item: remaining = 2 - 1 - 1 = 0. gridMatrix misses line
 *           endMainLineIndex_ + cachedCount (find(3)), and endIndex_ (1) >=
 *           lastIrregularIndex (0), so the method returns
 *           min(window, remaining) = min(6, 0) = 0.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount016, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0 };
    model.SetLayoutOptions(option);
    CreateFixedItems(2);
    CreateDone();

    // Normal range with few children: start (0) <= end (1), both >= 0 — no overscroll
    pattern_->info_.startMainLineIndex_ = 0;
    pattern_->info_.endMainLineIndex_ = 1;
    pattern_->info_.startIndex_ = 0;
    pattern_->info_.endIndex_ = 1;
    pattern_->info_.childrenCount_ = 2;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // effectiveEndIndex = 1, remaining = 2 - 1 - 1 = 0
    // matrix find(1 + 2 = 3) → miss; 1 >= lastIrregularIndex (0)
    // → return min(window = 6, remaining = 0) = 0
    EXPECT_EQ(cacheEnd, 0);
}

/**
 * @tc.name: CachedCount017
 * @tc.desc: Test CalculateStartCachedCount fallthrough path (gridMatrix miss) in
 *           bottom out-of-bounds scenario. With irregularIndexes = {0,3,6,9,12},
 *           cachedCount=2, crossCount=3, childrenCount=30:
 *           effectiveStartIndex = 30 (GetChildrenCount). lower_bound(30) returns
 *           end(), iter != begin, --iter points to 12, diff = 30-12-1 = 17 >= (2-0)*3=6,
 *           return (2-0)*3+0 = 6. With the stale startIndex_ (7),
 *           the result would differ — proving the effective value is used.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount017, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 3, 6, 9, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Bottom out of bounds: startMainLineIndex_ (5) > endMainLineIndex_ (3)
    pattern_->info_.startMainLineIndex_ = 5;
    pattern_->info_.endMainLineIndex_ = 3;
    pattern_->info_.startIndex_ = 7; // stale
    pattern_->info_.endIndex_ = 6;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 3 (startMainLineIndex_ - cachedCount = 3)
    // so the gridMatrix path is skipped and the fallthrough path is reached
    pattern_->info_.gridMatrix_ = {
        { 5, { { 0, 15 }, { 1, 16 }, { 2, 17 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // effectiveStartIndex = GetChildrenCount() = 30 (bottom out-of-bounds)
    // lower_bound(30) on {0,3,6,9,12} → end(), iter != begin, --iter → 12
    // diff = 30 - 12 - 1 = 17 >= (2-0)*3=6 → return (2-0)*3+0 = 6
    EXPECT_EQ(cacheStart, 6);
}

/**
 * @tc.name: CachedCount018
 * @tc.desc: Test CalculateEndCachedCount fallthrough path (gridMatrix miss) in
 *           top out-of-bounds scenario. With irregularIndexes = {0,10},
 *           cachedCount=2, crossCount=3, childrenCount=30:
 *           effectiveEndIndex = -1. upper_bound(-1) returns iterator to 0,
 *           diff = 0 - (-1) - 1 = 0. Computation yields 4. With the stale
 *           endIndex_ (7), the result would be 5 — proving the effective value is used.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount018, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 10 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Top out of bounds: endMainLineIndex_ < 0
    pattern_->info_.startMainLineIndex_ = 0;
    pattern_->info_.endMainLineIndex_ = -1;
    pattern_->info_.startIndex_ = 0;
    pattern_->info_.endIndex_ = 7; // stale
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 1 (endMainLineIndex_ + cachedCount = -1 + 2 = 1)
    // so the gridMatrix path is skipped and the fallthrough path is reached.
    // Line 0 is irregular item 0's full row: every cross slot maps to item 0
    // (CheckGridPlaced records crossSpan = crossCount items this way).
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // effectiveEndIndex = -1 (top out-of-bounds)
    // Real layout: line0={0} (full row), line1={1,2,3}, line2={4,5,6}, line3={7,8,9},
    // line4={10} (full row). The 2-line window from the content start holds 4 items.
    // upper_bound(-1) on {0,10} → points to 0
    // diff = 0 - (-1) - 1 = 0 → consume anchor {0}: sum=1, lineCount=1
    // advance: diff = 0+10-1 = 9 → 9 >= (2-1)*3=3 → return (2-1)*3+1 = 4
    // (with the stale endIndex_ = 7 the walk would start at 7 and return 3,
    // proving the effective value is used)
    EXPECT_EQ(cacheEnd, 4);
}

/**
 * @tc.name: CachedCount019
 * @tc.desc: Test CalculateStartCachedCount fallthrough path when effectiveStartIndex
 *           is exactly an irregular index. With irregularIndexes = {0,6,12},
 *           cachedCount=2, crossCount=3, childrenCount=30:
 *           effectiveStartIndex = 6. lower_bound(6) returns iterator to 6,
 *           iter != begin, --iter points to 0. diff = 6 - 0 - 1 = 5.
 *           The regular block {1..5} occupies exactly 2 lines (the whole budget),
 *           so the walk terminates inside the block and returns sum + diff = 5,
 *           matching the gridMatrix reference (first item of line 1 is 1, 6 - 1 = 5).
 * @tc.type: FUNC
 */
 
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount019, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Normal range, fallthrough path: gridMatrix miss on target line.
    // Real layout: line0={0}, line1={1,2,3}, line2={4,5}, line3={6} (full row),
    // line4={7,8,9}. Viewport = lines 3-4, items 6..9.
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 4;
    // effectiveStartIndex = startIndex_ = 6 (exactly an irregular index)
    pattern_->info_.startIndex_ = 6;
    pattern_->info_.endIndex_ = 9;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 1 (startMainLineIndex_ - cachedCount = 3-2=1).
    // Line 3 is irregular item 6's full row: every cross slot maps to item 6.
    pattern_->info_.gridMatrix_ = {
        { 3, { { 0, 6 }, { 1, 6 }, { 2, 6 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // lower_bound(6) on {0,6,12} → 6, iter != begin, --iter → 0
    // diff = 6 - 0 - 1 = 5, budget = 2: 5 < 6 and 5 > (2-1)*3 = 3 (block fills the budget)
    // → return sum + diff = 0 + 5 = 5 (gridMatrix reference: 6 - 1 = 5)
    EXPECT_EQ(cacheStart, 5);
}

/**
 * @tc.name: CachedCount020
 * @tc.desc: Test CalculateStartCachedCount fallthrough path when effectiveStartIndex
 *           falls between two irregular indexes (not an exact match).
 *           irregularIndexes = {0,6,12}, effectiveStartIndex = 10 (the first item
 *           of its line; startIndex_ is always a line-first item, see
 *           GridLayoutInfo::UpdateStartIndex).
 *           lower_bound(10) → 12, iter != begin, --iter → 6,
 *           diff = 10-6-1 = 3 (block {7,8,9}, exactly one full line).
 *           Note: this is a normal (non-overscroll) grid state. The backward-walk
 *           anchoring on the closest irregular below the start index applies here too;
 *           the previous implementation only anchored on exact irregular matches and
 *           estimated 6 for this state.
 *           The block consumes 1 line and together with irregular 6's own line it
 *           exhausts the 2-line budget: sum = 3 + 1 = 4, exactly matching the
 *           gridMatrix reference (first item of line 3 is 6, 10 - 6 = 4).
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount020, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Real layout (numbers below are item indexes on each grid line):
    //   line 0 : 0      (irregular, occupies a full row)
    //   line 1 : 1 2 3
    //   line 2 : 4 5
    //   line 3 : 6      (irregular, occupies a full row)
    //   line 4 : 7 8 9
    //   line 5 : 10 11
    //   line 6 : 12     (irregular, occupies a full row)
    //   Viewport: lines 5-6, i.e. items 10..12
    pattern_->info_.startMainLineIndex_ = 5;
    pattern_->info_.endMainLineIndex_ = 6;
    // effectiveStartIndex = 10 (first item of line 5, between irregulars 6 and 12)
    pattern_->info_.startIndex_ = 10;
    pattern_->info_.endIndex_ = 12;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 3 (5-2=3)
    pattern_->info_.gridMatrix_ = {
        { 4, { { 0, 7 }, { 1, 8 }, { 2, 9 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // lower_bound(10) on {0,6,12} → 12, iter != begin, --iter → 6
    // diff = 10 - 6 - 1 = 3 (block {7,8,9} = exactly one full line), budget = 2:
    // 3 < 6 and 3 <= (2-1)*3 = 3 → consume block + anchor: sum = 3 + 1 = 4, lineCount = 2
    // → return 4 (gridMatrix reference: first item of line 3 is 6, 10 - 6 = 4)
    EXPECT_EQ(cacheStart, 4);
}

/**
 * @tc.name: CachedCount021
 * @tc.desc: Test CalculateStartCachedCount fallthrough path when effectiveStartIndex
 *           is before the first irregular index. With irregularIndexes = {12,20},
 *           crossCount = 3, cachedCount = 2: effectiveStartIndex = 9 (the first item
 *           of line 3; items 0..11 are all regular, packed 3 per line).
 *           The branch requires startMainLineIndex_ > cachedCount (otherwise the
 *           startMainLineIndex_ - cachedCount <= 0 early return fires first), so with
 *           crossCount = 3 the start index must be >= (cachedCount+1)*crossCount = 9
 *           and the first irregular index must be larger — hence 12, not a smaller
 *           first irregular. The method returns start = cachedCount * crossCount = 6,
 *           which is exact: lines 1-2 above the viewport hold {3,4,5} and {6,7,8}.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount021, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 12, 20 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Real layout: line0={0,1,2}, line1={3,4,5}, line2={6,7,8}, line3={9,10,11},
    // line4={12} (full row). Viewport = lines 3-4, items 9..12.
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 4;
    // effectiveStartIndex = 9 (first item of line 3, before first irregular index 12)
    pattern_->info_.startIndex_ = 9;
    pattern_->info_.endIndex_ = 12;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 1 (3-2=1)
    pattern_->info_.gridMatrix_ = {
        { 3, { { 0, 9 }, { 1, 10 }, { 2, 11 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // startMainLineIndex_ - cachedCount = 3 - 2 = 1 > 0; matrix find(1) → miss
    // effectiveStartIndex(9) <= firstIrregularIndex(12) → return start = 2*3 = 6
    // (exact: the 2 lines above hold {3,4,5} and {6,7,8} = 6 regular items)
    EXPECT_EQ(cacheStart, 6);
}

/**
 * @tc.name: CachedCount022
 * @tc.desc: Test CalculateEndCachedCount fallthrough path when effectiveEndIndex
 *           is exactly an irregular index. irregularIndexes = {0,6,12},
 *           effectiveEndIndex = 6. upper_bound(6) → 12, iter points to 12.
 *           diff = 12 - 6 - 1 = 5. The regular block {7..11} occupies exactly
 *           2 lines (the whole budget), so the walk terminates inside the block
 *           and returns sum + diff = 5, matching the gridMatrix reference
 *           (last item of line 5 is 11, 11 - 6 = 5).
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount022, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Real layout (numbers below are item indexes on each grid line):
    //   line 0 : 0      (irregular, occupies a full row)
    //   line 1 : 1 2 3
    //   line 2 : 4 5
    //   line 3 : 6      (irregular, occupies a full row)
    //   line 4 : 7 8 9
    //   line 5 : 10 11
    //   Viewport: lines 2-3, i.e. items 4..6
    pattern_->info_.startMainLineIndex_ = 2;
    pattern_->info_.endMainLineIndex_ = 3;
    pattern_->info_.startIndex_ = 4;
    // effectiveEndIndex = 6 (exactly an irregular index, sole item of the end line)
    pattern_->info_.endIndex_ = 6;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    // gridMatrix_ does NOT contain line 5 (endMainLineIndex_ + cachedCount = 3+2=5).
    // Line 3 is irregular item 6's full row: every cross slot maps to item 6.
    pattern_->info_.gridMatrix_ = {
        { 3, { { 0, 6 }, { 1, 6 }, { 2, 6 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // effectiveEndIndex(6) < lastIrregularIndex(12) → fallthrough
    // upper_bound(6) on {0,6,12} → 12
    // diff = 12 - 6 - 1 = 5, budget = 2: 5 < 6 and 5 > (2-1)*3 = 3 (block fills the budget)
    // → return sum + diff = 0 + 5 = 5 (gridMatrix reference: 11 - 6 = 5)
    EXPECT_EQ(cacheEnd, 5);
}

/**
 * @tc.name: CachedCount023
 * @tc.desc: Test CalculateStartCachedCountByIrregular when iter == begin().
 *           This branch is a defensive guard: after lower_bound returns begin,
 *           there is no irregular item before effectiveStartIndex to anchor
 *           the calculation, so return the default start (cachedCount * crossCount).
 *           In normal flow the caller guards effectiveStartIndex <= firstIrregularIndex,
 *           but the helper is called directly here to exercise the defensive path.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount023, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // Call helper directly with effectiveStartIndex = 0.
    // lower_bound(0) on {0,6,12} → begin() → return start = 2*3 = 6
    auto cacheStart = algo->CalculateStartCachedCountByIrregular(option, 2, 0);
    EXPECT_EQ(cacheStart, 6);
}

/**
 * @tc.name: CachedCount024
 * @tc.desc: Test CalculateEndCachedCountByIrregular when iter == end().
 *           This branch is a defensive guard: after upper_bound returns end,
 *           there is no irregular item after effectiveEndIndex, so return the
 *           default end (cachedCount * crossCount).
 *           In normal flow the caller guards effectiveEndIndex >= lastIrregularIndex,
 *           but the helper is called directly here to exercise the defensive path.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount024, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // Call helper directly with effectiveEndIndex = 20 (past all irregular indexes).
    // upper_bound(20) on {0,6,12} → end() → return end = 2*3 = 6
    auto cacheEnd = algo->CalculateEndCachedCountByIrregular(option, 2, 20);
    EXPECT_EQ(cacheEnd, 6);
}

/**
 * @tc.name: CachedCount025
 * @tc.desc: Test CalculateStartCachedCount bottom-overscroll branch
 *           (effectiveStartIndex = GetChildrenCount()) reaching the fallthrough
 *           path via CalculateStartCachedCountByIrregular, where effectiveStartIndex
 *           exceeds all irregular indexes. lower_bound returns end(), --iter → 12,
 *           diff = 30 - 12 - 1 = 17 >= (2-0)*3 = 6 → return 6.
 *           This specifically covers the combination of branch 1 (overscroll)
 *           with the fallthrough irregular computation path.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount025, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 3, 6, 9, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    // Bottom out of bounds: startMainLineIndex_ (5) > endMainLineIndex_ (3)
    pattern_->info_.startMainLineIndex_ = 5;
    pattern_->info_.endMainLineIndex_ = 3;
    pattern_->info_.startIndex_ = 7; // stale
    pattern_->info_.endIndex_ = 6;
    pattern_->info_.childrenCount_ = 30;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {};
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheStart = algo->CalculateStartCachedCount(option, 2);
    // effectiveStartIndex = GetChildrenCount() = 30 (branch 1: overscroll)
    // > firstIrregularIndex(0) → fallthrough to CalculateStartCachedCountByIrregular
    // lower_bound(30) on {0,3,6,9,12} → end(), iter != begin, --iter → 12
    // diff = 30 - 12 - 1 = 17 >= (2-0)*3=6 → return (2-0)*3+0 = 6
    EXPECT_EQ(cacheStart, 6);
}

/**
 * @tc.name: CachedCount026
 * @tc.desc: Test CalculateEndCachedCount when the viewport ends at the last
 *           item. The cache count must be the number of items remaining after
 *           the effective end (0), not startIndex_ (48). Regression test: the
 *           early return previously returned startIndex_.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount026, TestSize.Level1)
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

    // Viewport ends at the last item (endIndex_ = 49)
    pattern_->info_.startMainLineIndex_ = 16;
    pattern_->info_.endMainLineIndex_ = 16;
    pattern_->info_.startIndex_ = 48;
    pattern_->info_.endIndex_ = 49;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {
        { 16, { { 0, 48 }, { 1, 49 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // matrix find(16 + 2 = 18) → miss; effectiveEndIndex(49) >= lastIrregularIndex(12)
    // → return min(window = 6, remaining = 50 - 1 - 49 = 0) = 0
    EXPECT_EQ(cacheEnd, 0);
}

/**
 * @tc.name: CachedCount027
 * @tc.desc: Test CalculateEndCachedCount when a long viewport ends at the last
 *           item far from startIndex_. The previous guard (startIndex_ +
 *           cachedCount) missed this case and the fallthrough returned the full
 *           window (6) although no items remain after the end. With the
 *           remaining clamp the method must return 0.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount027, TestSize.Level1)
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

    // Long viewport: items 10..49 visible, gridMatrix lacks line 18
    pattern_->info_.startMainLineIndex_ = 4;
    pattern_->info_.endMainLineIndex_ = 16;
    pattern_->info_.startIndex_ = 10;
    pattern_->info_.endIndex_ = 49;
    pattern_->info_.childrenCount_ = 50;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
    };
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // matrix find(16 + 2 = 18) → miss; effectiveEndIndex(49) >= lastIrregularIndex(12)
    // → return min(window = 6, remaining = 50 - 1 - 49 = 0) = 0
    EXPECT_EQ(cacheEnd, 0);
}

/**
 * @tc.name: CachedCount028
 * @tc.desc: Test CalculateEndCachedCount when the items remaining after the end
 *           (4) are fewer than a full cache window (6). The tail after the end
 *           has no irregular indexes, so the method returns
 *           min(window, remaining) = min(6, 4) = 4. The previous fallthrough
 *           returned the full window (6).
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount028, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 1, 2 };
    model.SetLayoutOptions(option);
    CreateFixedItems(20);
    CreateDone();

    // Items 16..19 remain after the end, gridMatrix is empty (miss on line 7)
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 5;
    pattern_->info_.startIndex_ = 9;
    pattern_->info_.endIndex_ = 15;
    pattern_->info_.childrenCount_ = 20;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {};
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // matrix find(5 + 2 = 7) → miss; effectiveEndIndex(15) >= lastIrregularIndex(2)
    // → return min(window = 6, remaining = 20 - 1 - 15 = 4) = 4
    EXPECT_EQ(cacheEnd, 4);
}

/**
 * @tc.name: CachedCount029
 * @tc.desc: Test CalculateStartCachedCountByIrregular line accounting for a block
 *           that is not a multiple of crossCount. irregularIndexes = {0,6,12},
 *           cachedCount = 2, crossCount = 3, effectiveStartIndex = 8. The block
 *           {7} between irregular 6 and the start index occupies 1 line
 *           (ceil(1/3) = 1); together with irregular 6's own line it exhausts
 *           the 2-line budget: return 2. Regression test: integer division made
 *           ceil(1/3) = 0, the line budget was under-consumed and the walk
 *           returned 4 by counting items below irregular 0 (outside the window).
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount029, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 6, 12 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // anchor = 6, diff = 8 - 6 - 1 = 1, budget = 2
    // block {7}: (1 + 3 - 1) / 3 = 1 line, plus anchor line → lineCount = 2, sum = 1 + 1 = 2
    auto cacheStart = algo->CalculateStartCachedCountByIrregular(option, 2, 8);
    EXPECT_EQ(cacheStart, 2);
}

/**
 * @tc.name: CachedCount030
 * @tc.desc: Test CalculateStartCachedCountByIrregular counts the anchor irregular
 *           item itself when its line is consumed. irregularIndexes = {0,2},
 *           cachedCount = 2, crossCount = 3, effectiveStartIndex = 6. Layout:
 *           line0={0}, line1={1}, line2={2}, line3={3,4,5}, line4={6,7,8}.
 *           The 2-line window above line4 holds {3,4,5} and {2}: return 4
 *           (gridMatrix reference: first item of line 2 is 2, 6 - 2 = 4).
 *           Regression test: the walk previously returned 3, dropping the
 *           anchor irregular item 2 while still consuming its line.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount030, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 2 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // anchor = 2, diff = 6 - 2 - 1 = 3, budget = 2
    // block {3,4,5}: (3 + 2) / 3 = 1 line, plus anchor line → lineCount = 2
    // sum = 3 + 1 = 4 (block items + anchor irregular 2)
    auto cacheStart = algo->CalculateStartCachedCountByIrregular(option, 2, 6);
    EXPECT_EQ(cacheStart, 4);
}

/**
 * @tc.name: CachedCount031
 * @tc.desc: Test CalculateStartCachedCountByIrregular when the block alone fills
 *           the remaining line budget exactly ((budget-1)*crossCount < diff <
 *           budget*crossCount). irregularIndexes = {0,4}, cachedCount = 2,
 *           crossCount = 3, effectiveStartIndex = 9. Layout: line0={0},
 *           line1={1,2,3}, line2={4}, line3={5,6,7}, line4={8,9,10}. The block
 *           {5,6,7,8} occupies exactly 2 lines: return sum + diff = 4.
 *           Regression test: this case previously consumed nothing and returned 3,
 *           counting items {1,2,3} below irregular 0, outside the cache window.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount031, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 4 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // anchor = 4, diff = 9 - 4 - 1 = 4, budget = 2
    // 4 < 6 and 4 > (2-1)*3 = 3 → block fills the budget exactly → return 0 + 4 = 4
    auto cacheStart = algo->CalculateStartCachedCountByIrregular(option, 2, 9);
    EXPECT_EQ(cacheStart, 4);
}

/**
 * @tc.name: CachedCount032
 * @tc.desc: Test CalculateEndCachedCountByIrregular counts the anchor irregular
 *           item itself when its line is consumed. irregularIndexes = {2},
 *           cachedCount = 2, crossCount = 3, effectiveEndIndex = 0. The block
 *           {1} occupies 1 line and together with irregular 2's own line it
 *           exhausts the 2-line budget: return 2. Regression test: the walk
 *           previously returned 1, dropping the anchor irregular item 2.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount032, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 2 };
    model.SetLayoutOptions(option);
    CreateFixedItems(30);
    CreateDone();

    pattern_->info_.crossCount_ = 3;
    pattern_->info_.childrenCount_ = 30;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    // anchor = 2, diff = 2 - 0 - 1 = 1, budget = 2
    // block {1}: (1 + 2) / 3 = 1 line, plus anchor line → lineCount = 2, sum = 1 + 1 = 2
    auto cacheEnd = algo->CalculateEndCachedCountByIrregular(option, 2, 0);
    EXPECT_EQ(cacheEnd, 2);
}

/**
 * @tc.name: CachedCount033
 * @tc.desc: Test CalculateEndCachedCount when irregular indexes occupy the tail
 *           region. An irregular item occupies a whole line by itself, so a
 *           cachedCount-line window can hold fewer items than
 *           cachedCount * crossCount. With irregularIndexes = {0,16,17},
 *           crossCount = 3, cachedCount = 2, childrenCount = 21, endIndex_ = 15:
 *           layout is line0={0}, line1..5={1,2,3}..{13,14,15}, line6={16},
 *           line7={17}, line8={18,19,20}. The 2-line window after the end line
 *           (line5) holds only {16},{17} = 2 items, although 5 items remain
 *           after the end (16..20) and the full-line window size is 6.
 *           The method must route through the irregular walk and clamp at the
 *           remaining: 2. Regression test: the full-line window shortcut
 *           previously returned the remaining 5, over-caching by 3.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestFourNg, CachedCount033, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, false);
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 16, 17 };
    model.SetLayoutOptions(option);
    CreateFixedItems(21);
    CreateDone();

    // Irregulars 16 and 17 occupy the tail region after endIndex_ = 15
    pattern_->info_.startMainLineIndex_ = 3;
    pattern_->info_.endMainLineIndex_ = 5;
    pattern_->info_.startIndex_ = 9;
    pattern_->info_.endIndex_ = 15;
    pattern_->info_.childrenCount_ = 21;
    pattern_->info_.crossCount_ = 3;
    pattern_->info_.gridMatrix_ = {};
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    auto cacheEnd = algo->CalculateEndCachedCount(option, 2);
    // matrix find(5 + 2 = 7) → miss; effectiveEndIndex(15) < lastIrregularIndex(17)
    // → walk: {16} (1 line) + {17} (1 line) exhausts the 2-line budget → 2
    // clamped at remaining = 21 - 1 - 15 = 5 → 2 (true window: lines 6-7 hold 2 items)
    EXPECT_EQ(cacheEnd, 2);
}

HWTEST_F(GridScrollLayoutTestFourNg, isFadingBottomTest001, TestSize.Level1)
{
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

HWTEST_F(GridScrollLayoutTestFourNg, isFadingBottomTest002, TestSize.Level1)
{
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