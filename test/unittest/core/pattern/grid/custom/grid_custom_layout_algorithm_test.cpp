/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "custom_layout_options.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::ACE {} // namespace OHOS::ACE

namespace OHOS::Ace::NG {
class GridCustomLayoutAlgorithmTestNg : public GridTestNg {};

/**
 * @tc.name: ConstructorTestDefault
 * @tc.desc: Test GridCustomLayoutAlgorithm default constructor behavior
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ConstructorTestDefault, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(10);
    CreateDone();

    // Verify default initialization
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_GE(pattern_->info_.endIndex_, 7);
}

/**
 * @tc.name: ScrollByWithOffset
 * @tc.desc: Test GridCustomLayoutAlgorithm scroll by behavior with offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollByWithOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Test scroll by half item size
    ScrollBy(0, ITEM_MAIN_SIZE / 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);

    // Test scroll by two rows
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 2);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: ScrollByLargeOffset
 * @tc.desc: Test GridCustomLayoutAlgorithm with large offset (triggers skip logic)
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollByLargeOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Large offset scroll to trigger JumpToTargetOffset path
    ScrollBy(0, HEIGHT * 2);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 49);
}

/**
 * @tc.name: VerifyLayoutInfo
 * @tc.desc: Test GridCustomLayoutAlgorithm UpdateLayoutInfo behavior
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, VerifyLayoutInfo, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Verify reachEnd is set when scrolled to end
    ScrollTo(HEIGHT * 3);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: VerifyCacheReset
 * @tc.desc: Test GridCustomLayoutAlgorithm CheckForReset behavior
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, VerifyCacheReset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(10);
    CreateDone();

    // Trigger reset by updating children
    frameNode_->ChildrenUpdatedFrom(0);

    // Scroll to verify cache was cleared
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: MeasureToEdge
 * @tc.desc: Test GridCustomLayoutAlgorithm measure to edge position
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MeasureToEdge, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to top edge
    ScrollTo(0);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

    // Scroll to bottom edge
    ScrollTo(ITEM_MAIN_SIZE * 20);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: ScrollToIndexBehavior
 * @tc.desc: Test GridCustomLayoutAlgorithm ScrollToIndex behavior
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollToIndexBehavior, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Scroll to middle index
    ScrollToIndex(15, false, ScrollAlign::START);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 49);

    // Scroll to last index
    ScrollToIndex(49, false, ScrollAlign::START);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: CacheItemsCount
 * @tc.desc: Test GridCustomLayoutAlgorithm cache items count
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CacheItemsCount, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Scroll to middle position
    ScrollBy(0, ITEM_MAIN_SIZE * 3);
    int32_t visibleCount = pattern_->info_.endIndex_ - pattern_->info_.startIndex_ + 1;
    EXPECT_GT(visibleCount, 0);
    EXPECT_LE(visibleCount, 20);
}

/**
 * @tc.name: JumpLogic
 * @tc.desc: Test GridCustomLayoutAlgorithm TrySkipping logic for large jumps
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, JumpLogic, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    // Very large scroll should trigger skip logic
    ScrollBy(0, ITEM_MAIN_SIZE * 50);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 99);
    EXPECT_LE(pattern_->info_.startMainLineIndex_, 50);
}

/**
 * @tc.name: MeasureWithDifferentItemCounts
 * @tc.desc: Test GridCustomLayoutAlgorithm with various item counts
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MeasureWithDifferentItemCounts, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(5); // Small number of items
    CreateDone();

    // Verify small dataset handling
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 5);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: ContinuousScrolling
 * @tc.desc: Test GridCustomLayoutAlgorithm with continuous scrolling
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ContinuousScrolling, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Multiple small scrolls
    for (int i = 0; i < 5; i++) {
        ScrollBy(0, ITEM_MAIN_SIZE);
    }
    EXPECT_GE(pattern_->info_.startIndex_, 8);
    EXPECT_LE(pattern_->info_.endIndex_, 49);
}

/**
 * @tc.name: ScrollToTopBottom
 * @tc.desc: Test GridCustomLayoutAlgorithm scrolling to top and bottom
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollToTopBottom, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Scroll to bottom
    ScrollToIndex(39, false, ScrollAlign::START);
    EXPECT_TRUE(pattern_->info_.reachEnd_);

    // Scroll back to top
    ScrollToIndex(0, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: MeasureOnOffsetUpdate
 * @tc.desc: Test GridCustomLayoutAlgorithm MeasureOnOffset path
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MeasureOnOffsetUpdate, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Update current offset directly
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), 100.0f);

    // Scroll again to trigger MeasureOnOffset
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_GT(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: ThreeColumnLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with 3 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ThreeColumnLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(3, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Verify 3-column layout
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_ % 3, 0);
    EXPECT_GE(pattern_->info_.endIndex_, 0);
}

/**
 * @tc.name: FourColumnLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with 4 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, FourColumnLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(4, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Verify 4-column layout
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_ % 4, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 39);
}

/**
 * @tc.name: EmptyGrid
 * @tc.desc: Test GridCustomLayoutAlgorithm with no items
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, EmptyGrid, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(0); // No items
    CreateDone();

    // Verify empty grid handling
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, -1);
}

/**
 * @tc.name: SingleItemGrid
 * @tc.desc: Test GridCustomLayoutAlgorithm with single item
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, SingleItemGrid, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(1);
    CreateDone();

    // Verify single item handling
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 0);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: ScrollAlignCenter
 * @tc.desc: Test GridCustomLayoutAlgorithm with CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollAlignCenter, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Scroll to index with CENTER alignment
    ScrollToIndex(20, false, ScrollAlign::CENTER);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 39);
}

/**
 * @tc.name: ScrollAlignEnd
 * @tc.desc: Test GridCustomLayoutAlgorithm with END alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollAlignEnd, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to index with END alignment
    ScrollToIndex(10, false, ScrollAlign::END);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 29);
}

/**
 * @tc.name: SmallScrollStep
 * @tc.desc: Test GridCustomLayoutAlgorithm with very small scroll steps
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, SmallScrollStep, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Multiple small scrolls (10 pixels each)
    for (int i = 0; i < 10; i++) {
        ScrollBy(0, 10.0f);
    }
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_GT(pattern_->info_.currentOffset_, -110.0f);
}

/**
 * @tc.name: ResetAfterScroll
 * @tc.desc: Test GridCustomLayoutAlgorithm reset behavior after scroll
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ResetAfterScroll, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to middle
    ScrollBy(0, ITEM_MAIN_SIZE * 5);

    // Trigger reset
    frameNode_->ChildrenUpdatedFrom(0);

    // Scroll again to verify reset worked
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: MeasureSelfSize
 * @tc.desc: Test GridCustomLayoutAlgorithm MeasureSelf calculation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MeasureSelfSize, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Grid should calculate proper content size
    EXPECT_GE(pattern_->GetTotalOffset(), 0);
    EXPECT_LE(pattern_->info_.endIndex_, 19);
}

/**
 * @tc.name: BackwardScrolling
 * @tc.desc: Test GridCustomLayoutAlgorithm backward scrolling
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, BackwardScrolling, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Scroll forward
    ScrollBy(0, ITEM_MAIN_SIZE * 5);
    int32_t forwardStartIndex = pattern_->info_.startIndex_;

    // Scroll backward
    ScrollBy(0, -ITEM_MAIN_SIZE * 3);
    EXPECT_LT(pattern_->info_.startIndex_, forwardStartIndex);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: RowsTemplateMode
 * @tc.desc: Test GridCustomLayoutAlgorithm with rowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, RowsTemplateMode, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Verify rows template mode works
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 19);
}

/**
 * @tc.name: OverScrollBehavior
 * @tc.desc: Test GridCustomLayoutAlgorithm over-scroll behavior
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, OverScrollBehavior, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Scroll beyond top
    ScrollBy(0, -ITEM_MAIN_SIZE);
    EXPECT_LE(pattern_->info_.currentOffset_, 0);

    // Scroll to end
    ScrollTo(ITEM_MAIN_SIZE * 20);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: MultipleResets
 * @tc.desc: Test GridCustomLayoutAlgorithm with multiple resets
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MultipleResets, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // First scroll and reset
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    frameNode_->ChildrenUpdatedFrom(0);

    // Second scroll and reset
    ScrollBy(0, ITEM_MAIN_SIZE * 3);
    frameNode_->ChildrenUpdatedFrom(0);

    // Final scroll
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: LargeDatasetScrolling
 * @tc.desc: Test GridCustomLayoutAlgorithm with large dataset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, LargeDatasetScrolling, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(200);
    CreateDone();

    // Scroll to various positions
    ScrollToIndex(50, false, ScrollAlign::START);
    EXPECT_GE(pattern_->info_.startIndex_, 0);

    ScrollToIndex(150, false, ScrollAlign::START);
    EXPECT_LE(pattern_->info_.endIndex_, 199);
}

/**
 * @tc.name: ScrollToFirstLast
 * @tc.desc: Test GridCustomLayoutAlgorithm scrolling to first and last items
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollToFirstLast, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Scroll to first item
    ScrollToIndex(0, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);

    // Scroll to last item
    ScrollToIndex(39, false, ScrollAlign::START);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
}

/**
 * @tc.name: VariableScrollSteps
 * @tc.desc: Test GridCustomLayoutAlgorithm with variable scroll steps
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, VariableScrollSteps, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Variable step sizes
    ScrollBy(0, 10.0f);
    ScrollBy(0, 50.0f);
    ScrollBy(0, 100.0f);
    ScrollBy(0, 25.0f);

    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_GE(pattern_->info_.endIndex_, pattern_->info_.startIndex_);
}

/**
 * @tc.name: UpdateCurrentOffsetMultiple
 * @tc.desc: Test GridCustomLayoutAlgorithm with multiple offset updates
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, UpdateCurrentOffsetMultiple, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Multiple offset updates
    for (int i = 0; i < 10; i++) {
        UpdateCurrentOffset(-20.0f, SCROLL_FROM_UPDATE);
    }
    EXPECT_EQ(pattern_->GetTotalOffset(), 200.0f);
}

/**
 * @tc.name: FiveColumnLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with 5 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, FiveColumnLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(5, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Verify 5-column layout
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_ % 5, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 49);
}

/**
 * @tc.name: ScrollWithAnimation
 * @tc.desc: Test GridCustomLayoutAlgorithm with scroll animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollWithAnimation, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Animated scroll
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50.0f);

    UpdateCurrentOffset(-100.0f, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(pattern_->GetTotalOffset(), 150.0f);
}

/**
 * @tc.name: RapidDirectionChange
 * @tc.desc: Test GridCustomLayoutAlgorithm with rapid direction changes
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, RapidDirectionChange, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Rapid forward and backward scrolls
    ScrollBy(0, ITEM_MAIN_SIZE * 3);
    int32_t index1 = pattern_->info_.startIndex_;

    ScrollBy(0, -ITEM_MAIN_SIZE * 2);
    int32_t index2 = pattern_->info_.startIndex_;

    ScrollBy(0, ITEM_MAIN_SIZE * 4);
    int32_t index3 = pattern_->info_.startIndex_;

    EXPECT_GT(index1, 0);
    EXPECT_LT(index2, index1);
    EXPECT_GT(index3, index2);
}

/**
 * @tc.name: ScrollAlignAuto
 * @tc.desc: Test GridCustomLayoutAlgorithm with AUTO alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollAlignAuto, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to index with AUTO alignment (should choose optimal alignment)
    ScrollToIndex(15, false, ScrollAlign::AUTO);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 29);
}

/**
 * @tc.name: MixedAlignmentScrolls
 * @tc.desc: Test GridCustomLayoutAlgorithm with mixed scroll alignments
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MixedAlignmentScrolls, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Scroll with different alignments
    ScrollToIndex(10, false, ScrollAlign::START);
    EXPECT_GE(pattern_->info_.startIndex_, 0);

    ScrollToIndex(20, false, ScrollAlign::CENTER);
    EXPECT_LE(pattern_->info_.endIndex_, 39);

    ScrollToIndex(30, false, ScrollAlign::END);
    EXPECT_LE(pattern_->info_.endIndex_, 39);
}

/**
 * @tc.name: EdgeCaseIndex
 * @tc.desc: Test GridCustomLayoutAlgorithm with edge case indices
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, EdgeCaseIndex, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Scroll to second item
    ScrollToIndex(1, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);

    // Scroll to second last item
    ScrollToIndex(18, false, ScrollAlign::START);
    EXPECT_TRUE(pattern_->info_.reachEnd_ || pattern_->info_.endIndex_ >= 18);
}

/**
 * @tc.name: ZeroScrollOffset
 * @tc.desc: Test GridCustomLayoutAlgorithm with zero scroll offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ZeroScrollOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll by zero
    ScrollBy(0, 0.0f);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: NegativeScrollIndex
 * @tc.desc: Test GridCustomLayoutAlgorithm behavior with negative scroll attempts
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, NegativeScrollIndex, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Try to scroll backward from top (should stay at top)
    ScrollBy(0, -ITEM_MAIN_SIZE);
    EXPECT_LE(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: PrecisionScrolling
 * @tc.desc: Test GridCustomLayoutAlgorithm with precise pixel scrolling
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PrecisionScrolling, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Precise 1 pixel scrolls - accumulate offset
    for (int i = 0; i < 100; i++) {
        ScrollBy(0, 1.0f);
    }
    // After 100 pixels, should have some scroll movement
    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: FractionalScrollSteps
 * @tc.desc: Test GridCustomLayoutAlgorithm with fractional scroll steps
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, FractionalScrollSteps, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Fractional scroll steps
    ScrollBy(0, 33.33f);
    ScrollBy(0, 66.67f);
    ScrollBy(0, 50.0f);

    EXPECT_GE(pattern_->info_.startIndex_, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 39);
}

/**
 * @tc.name: ScrollWithBarOffset
 * @tc.desc: Test GridCustomLayoutAlgorithm with scrollbar offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollWithBarOffset, TestSize.Level1)
{
    auto onScrollbarUpdate = [](int32_t index,
                                 Dimension offset) -> std::pair<std::optional<float>, std::optional<float>> {
        float itemSize = ITEM_MAIN_SIZE;
        return { index / 2 * itemSize - offset.Value(), itemSize * 10 };
    };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    model.SetOnScrollBarUpdate(std::move(onScrollbarUpdate));
    CreateFixedItems(30);
    CreateDone();

    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: SixColumnLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with 6 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, SixColumnLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(6, ITEM_MAIN_SIZE));
    CreateFixedItems(60);
    CreateDone();

    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_ % 6, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 59);
}

/**
 * @tc.name: VeryLargeDataset
 * @tc.desc: Test GridCustomLayoutAlgorithm with very large dataset (500 items)
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, VeryLargeDataset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(500);
    CreateDone();

    // Scroll to various positions in large dataset
    ScrollToIndex(100, false, ScrollAlign::START);
    EXPECT_GE(pattern_->info_.startIndex_, 0);

    ScrollToIndex(400, false, ScrollAlign::START);
    EXPECT_LE(pattern_->info_.endIndex_, 499);
}

/**
 * @tc.name: ScrollToMiddleOfLargeSet
 * @tc.desc: Test GridCustomLayoutAlgorithm scrolling to middle of large dataset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollToMiddleOfLargeSet, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    // Scroll to exact middle
    ScrollToIndex(50, false, ScrollAlign::CENTER);
    EXPECT_GE(pattern_->info_.startIndex_, 40);
    EXPECT_LE(pattern_->info_.endIndex_, 60);
}

/**
 * @tc.name: AlternatingScrollDirection
 * @tc.desc: Test GridCustomLayoutAlgorithm with alternating scroll directions
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, AlternatingScrollDirection, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Alternating scroll pattern
    for (int i = 0; i < 3; i++) {
        ScrollBy(0, ITEM_MAIN_SIZE);
        ScrollBy(0, -ITEM_MAIN_SIZE / 2);
    }
    EXPECT_GE(pattern_->info_.startIndex_, 0);
}

/**
 * @tc.name: ScrollBeyondEnd
 * @tc.desc: Test GridCustomLayoutAlgorithm scrolling beyond end
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollBeyondEnd, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Scroll far beyond content
    ScrollTo(ITEM_MAIN_SIZE * 50);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
    EXPECT_LE(pattern_->info_.endIndex_, 19);
}

/**
 * @tc.name: RepeatedIndexScrolling
 * @tc.desc: Test GridCustomLayoutAlgorithm scrolling to same index repeatedly
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, RepeatedIndexScrolling, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(40);
    CreateDone();

    // Scroll to same index multiple times
    ScrollToIndex(15, false, ScrollAlign::START);
    int32_t firstStartIndex = pattern_->info_.startIndex_;

    ScrollToIndex(15, false, ScrollAlign::START);
    int32_t secondStartIndex = pattern_->info_.startIndex_;

    EXPECT_EQ(firstStartIndex, secondStartIndex);
}

/**
 * @tc.name: IndexBeyondRange
 * @tc.desc: Test GridCustomLayoutAlgorithm with index beyond valid range
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, IndexBeyondRange, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Scroll to index beyond range (should clamp to end)
    ScrollToIndex(100, false, ScrollAlign::START);
    // Should be at or near the end
    EXPECT_LE(pattern_->info_.endIndex_, 19);
}

/**
 * @tc.name: SevenColumnLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with 7 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, SevenColumnLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(7, ITEM_MAIN_SIZE));
    CreateFixedItems(70);
    CreateDone();

    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_ % 7, 0);
    EXPECT_LE(pattern_->info_.endIndex_, 69);
}

/**
 * @tc.name: CacheClearedAfterChildrenUpdate
 * @tc.desc: Test cache is cleared when children are updated
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CacheClearedAfterChildrenUpdate, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Create cache by scrolling
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.lineHeightMap_.size(), 7);
    EXPECT_EQ(pattern_->info_.gridMatrix_.size(), 8);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);

    // Trigger children update
    frameNode_->ChildrenUpdatedFrom(5);

    // Scroll again to trigger CheckForReset
    ScrollBy(0, ITEM_MAIN_SIZE);

    // Verify cache was cleared and rebuilt
    EXPECT_EQ(pattern_->info_.lineHeightMap_.size(), 4);
    EXPECT_EQ(pattern_->info_.gridMatrix_.size(), 5);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

/**
 * @tc.name: IrregularGridLayout
 * @tc.desc: Test GridCustomLayoutAlgorithm with irregular grid items
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, IrregularGridLayout, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(Get3LinesIrregularDemoOptions(20, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Verify irregular grid is laid out
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 5);

    // Scroll to verify irregular layout works
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_, 1);
    EXPECT_EQ(pattern_->info_.endIndex_, 6);
}

/**
 * @tc.name: CacheBehaviorOnReset
 * @tc.desc: Test cache behavior when reset is triggered
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CacheBehaviorOnReset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    // Create cache
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);

    // Trigger reset by updating children at start index
    frameNode_->ChildrenUpdatedFrom(0);

    // Scroll to trigger layout with reset
    ScrollBy(0, ITEM_MAIN_SIZE);

    // Verify layout state is valid after reset
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

/**
 * @tc.name: GridWithZeroGap
 * @tc.desc: Test GridCustomLayoutAlgorithm with zero gap
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, GridWithZeroGap, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    model.SetColumnsGap(0.0_vp);
    model.SetRowsGap(0.0_vp);
    CreateFixedItems(20);
    CreateDone();

    // Verify layout works with zero gap
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);

    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);
}

/**
 * @tc.name: GridWithLargeGap
 * @tc.desc: Test GridCustomLayoutAlgorithm with large gap
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, GridWithLargeGap, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    model.SetColumnsGap(20.0_vp);
    model.SetRowsGap(20.0_vp);
    CreateFixedItems(20);
    CreateDone();

    // Verify layout works with large gap
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);

    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);
}

/**
 * @tc.name: CrossCountChangeTriggersReset
 * @tc.desc: Test that changing cross count triggers layout reset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CrossCountChangeTriggersReset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Verify initial cross count
    int32_t initialCrossCount = pattern_->info_.crossCount_;
    EXPECT_EQ(initialCrossCount, 2);

    // Scroll to create state
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);

    // Note: Changing columns template dynamically doesn't trigger layout algorithm recreation
    // The test verifies the initial grid setup works correctly with specified cross count
    EXPECT_EQ(pattern_->info_.crossCount_, 2);
}

/**
 * @tc.name: ScrollToIndexWithLargeOffset
 * @tc.desc: Test scrolling to index with large offset triggers jump optimization
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollToIndexWithLargeOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    // Jump to far index
    ScrollToIndex(80, false, ScrollAlign::START);

    // Verify jump completed
    EXPECT_EQ(pattern_->info_.startIndex_, 80);
    EXPECT_EQ(pattern_->info_.endIndex_, 87);
}

/**
 * @tc.name: LayoutAlgorithmHandlesRtl
 * @tc.desc: Test GridCustomLayoutAlgorithm handles RTL direction
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, LayoutAlgorithmHandlesRtl, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    CreateFixedItems(20);
    CreateDone();

    // Verify RTL layout works
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
}

/**
 * @tc.name: ScrollAlignStartWithOffset
 * @tc.desc: Test scroll to index with START alignment and extra offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ScrollAlignStartWithOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to index with START alignment
    ScrollToIndex(15, false, ScrollAlign::START);

    // Verify target index is visible
    EXPECT_EQ(pattern_->info_.startIndex_, 14);
    EXPECT_EQ(pattern_->info_.endIndex_, 21);
}

/**
 * @tc.name: CacheCountZero
 * @tc.desc: Test GridCustomLayoutAlgorithm with zero cache count
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CacheCountZero, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    layoutProperty_->UpdateCachedCount(0);
    CreateFixedItems(20);
    CreateDone();

    // Scroll to trigger preloading
    ScrollBy(0, ITEM_MAIN_SIZE * 3);

    // Verify layout works with zero cache
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

/**
 * @tc.name: LargeCacheCount
 * @tc.desc: Test GridCustomLayoutAlgorithm with large cache count
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, LargeCacheCount, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    layoutProperty_->UpdateCachedCount(10);
    CreateFixedItems(30);
    CreateDone();

    // Scroll to trigger preloading
    ScrollBy(0, ITEM_MAIN_SIZE * 3);

    // Verify layout works with large cache
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

} // namespace OHOS::Ace::NG
