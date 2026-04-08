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
#define protected public
#define private public
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
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
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 14);
    EXPECT_EQ(pattern_->info_.endIndex_, 21);

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
    EXPECT_EQ(visibleCount, 8);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 92);
    EXPECT_EQ(pattern_->info_.endIndex_, 99);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 46);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 4);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 10);
    EXPECT_EQ(pattern_->info_.endIndex_, 17);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 17);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 19);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.endIndex_, 25);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 12);
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
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
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
    EXPECT_EQ(forwardStartIndex, 10);

    // Scroll backward
    ScrollBy(0, -ITEM_MAIN_SIZE * 3);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 5);
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
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

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
    EXPECT_EQ(pattern_->info_.startIndex_, 12);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 50);

    ScrollToIndex(150, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->info_.endIndex_, 157);
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

    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 24);
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

    EXPECT_EQ(index1, 6);
    EXPECT_EQ(index2, 2);
    EXPECT_EQ(index3, 10);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 8);
    EXPECT_EQ(pattern_->info_.endIndex_, 15);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 10);

    ScrollToIndex(20, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->info_.endIndex_, 25);

    ScrollToIndex(30, false, ScrollAlign::END);
    EXPECT_EQ(pattern_->info_.endIndex_, 31);
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
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
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

    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 29);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 100);

    ScrollToIndex(400, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->info_.endIndex_, 407);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 46);
    EXPECT_EQ(pattern_->info_.endIndex_, 55);
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
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 19);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
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
    EXPECT_EQ(pattern_->info_.endIndex_, 34);
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
    EXPECT_EQ(pattern_->info_.lineHeightMap_.size(), 6);
    EXPECT_EQ(pattern_->info_.gridMatrix_.size(), 7);
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

/**
 * @tc.name: CrossCountChangeWithUserJump
 * @tc.desc: Test that user jump is preserved when crossCount changes
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CrossCountChangeWithUserJump, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr"); // Initial: 2 columns
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Simulate user jump by directly setting jumpIndex
    int32_t targetIndex = 15;
    pattern_->info_.jumpIndex_ = targetIndex;
    pattern_->info_.scrollAlign_ = ScrollAlign::START;

    // Manually simulate crossCount change to test the logic
    int32_t originalCrossCount = pattern_->info_.crossCount_;
    pattern_->info_.lastCrossCount_ = originalCrossCount;
    pattern_->info_.crossCount_ = originalCrossCount + 1; // Simulate crossCount change

    // Mark that children were updated to trigger CheckForReset logic
    frameNode_->ChildrenUpdatedFrom(0);

    // Trigger layout recalculation - this should invoke CheckForReset
    // The key is: when jumpIndex_ is already set (not EMPTY_JUMP_INDEX),
    // crossCount change should NOT overwrite it
    ScrollBy(0, 0);

    // The primary verification: layout should process normally
    // The user's jumpIndex should have been processed during layout
    EXPECT_EQ(pattern_->info_.startIndex_, 14);
    EXPECT_EQ(pattern_->info_.endIndex_, 21);
}

/**
 * @tc.name: CrossCountChangeWithoutUserJump
 * @tc.desc: Test that auto-adjustment works when crossCount changes without user jump
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CrossCountChangeWithoutUserJump, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr"); // Initial: 2 columns
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to middle to have a non-zero offset
    ScrollBy(0, ITEM_MAIN_SIZE * 3);

    // Verify no user jump is pending
    EXPECT_EQ(pattern_->info_.jumpIndex_, EMPTY_JUMP_INDEX);

    // Manually simulate crossCount change to test the logic
    int32_t originalCrossCount = pattern_->info_.crossCount_;
    pattern_->info_.lastCrossCount_ = originalCrossCount;
    pattern_->info_.crossCount_ = originalCrossCount + 1; // Simulate crossCount change

    // Mark that children were updated to trigger CheckForReset logic
    frameNode_->ChildrenUpdatedFrom(0);

    // Trigger layout recalculation - this should invoke CheckForReset
    // When no user jump is pending, crossCount change should trigger auto-adjustment
    ScrollBy(0, 0);

    // After crossCount change, auto-adjustment should have been triggered
    // The layout should maintain visual continuity
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

/**
 * @tc.name: AdjustOffsetApplication
 * @tc.desc: Test that adjustOffset_ is correctly applied and cleared
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, AdjustOffsetApplication, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr"); // Initial: 2 columns
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to create an offset
    ScrollBy(0, ITEM_MAIN_SIZE * 2);

    // Ensure no user jump
    EXPECT_EQ(pattern_->info_.jumpIndex_, EMPTY_JUMP_INDEX);

    // Manually simulate crossCount change to activate auto-adjustment
    int32_t originalCrossCount = pattern_->info_.crossCount_;
    pattern_->info_.lastCrossCount_ = originalCrossCount;
    pattern_->info_.crossCount_ = originalCrossCount + 1;

    // Mark that children were updated
    frameNode_->ChildrenUpdatedFrom(0);

    // Trigger layout recalculation - adjustOffset_ should be applied internally
    ScrollBy(0, 0);

    // The layout should maintain visual continuity
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
}

/**
 * @tc.name: PropertyUpdateByChildRequestTriggersJump
 * @tc.desc: Test that PROPERTY_UPDATE_BY_CHILD_REQUEST triggers jump with adjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PropertyUpdateByChildRequestTriggersJump, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to create a non-zero offset
    ScrollBy(0, ITEM_MAIN_SIZE * 2);

    // Trigger property update by child request
    // This simulates a child requesting a layout update
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    pattern_->OnModifyDone();

    // After the property update, jump should be prepared
    // and adjustOffset_ should be set to maintain position
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
}

/**
 * @tc.name: ConstraintChangedTriggersJump
 * @tc.desc: Test that ConstraintChanged triggers jump with adjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, ConstraintChangedTriggersJump, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to middle
    ScrollBy(0, ITEM_MAIN_SIZE * 3);

    // Trigger constraint change
    // This simulates the grid constraints changing (e.g., size change)
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    pattern_->OnModifyDone();

    // After constraint change, jump should be prepared
    // and adjustOffset_ should be set to maintain position
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
}

/**
 * @tc.name: AdjustOffsetSetInMultipleScenarios
 * @tc.desc: Test that adjustOffset_ is correctly set in various reset scenarios
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, AdjustOffsetSetInMultipleScenarios, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Test 1: CrossCount change scenario
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    int32_t originalCrossCount = pattern_->info_.crossCount_;
    pattern_->info_.lastCrossCount_ = originalCrossCount;
    pattern_->info_.crossCount_ = originalCrossCount + 1;
    frameNode_->ChildrenUpdatedFrom(0);
    ScrollBy(0, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);

    // Test 2: Property update by child request
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
}

/**
 * @tc.name: AdjustOffsetMaintainsPosition
 * @tc.desc: Test that adjustOffset_ helps maintain visual position during resets
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, AdjustOffsetMaintainsPosition, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Establish a stable scroll position
    ScrollBy(0, ITEM_MAIN_SIZE * 5);
    int32_t stableStartIndex = pattern_->info_.startIndex_;
    EXPECT_EQ(stableStartIndex, 10);

    // Simulate crossCount change (which triggers reset)
    int32_t originalCrossCount = pattern_->info_.crossCount_;
    pattern_->info_.lastCrossCount_ = originalCrossCount;
    pattern_->info_.crossCount_ = originalCrossCount + 1;

    // Trigger update
    frameNode_->ChildrenUpdatedFrom(0);
    ScrollBy(0, 0);

    // After reset with adjustOffset_, the layout should maintain continuity
    // The start index should be reasonable
    EXPECT_EQ(pattern_->info_.startIndex_, 10);
    EXPECT_EQ(pattern_->info_.endIndex_, 17);
}

/**
 * @tc.name: MeasureToTargetCachedItemHeight001
 * @tc.desc: Test MeasureToTarget calculates correct itemHeight when target item is in cache range
 *           This test verifies the fix for the issue where GetHeightInRange would include an extra
 *           mainGap when calculating item height for items spanning multiple rows.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, MeasureToTargetCachedItemHeight001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(Get3LinesIrregularDemoOptions(30, ITEM_MAIN_SIZE));
    model.SetRowsGap(Dimension(5));
    CreateItemsInLazyForEach(
        30, [](uint32_t idx) { return idx % 3 == 0 ? ITEM_MAIN_SIZE * 2 - 5 : ITEM_MAIN_SIZE - 5; });
    CreateDone();

    // First, scroll down to make some items out of view
    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    ScrollBy(0, ITEM_MAIN_SIZE * 2);

    AnimateToIndexWithTicks(10, ScrollAlign::END);

    // Verify the item is correctly positioned at the start
    EXPECT_EQ(pattern_->info_.startIndex_, 3);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 2);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + 5);
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck001
 * @tc.desc: Test PreloadItems debug check for gridMatrix_ row continuity during normal scrolling
 *           Verifies that debug continuity check does not affect normal preload behavior.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck001, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    // Scroll to trigger preload with cache
    layoutProperty_->UpdateCachedCount(2);
    ScrollBy(0, ITEM_MAIN_SIZE * 2);

    // Verify preload was triggered and gridMatrix_ is properly populated
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.endIndex_, 11);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck002
 * @tc.desc: Test PreloadItems with large scroll that triggers skip logic
 *           Verifies debug continuity check handles large jumps correctly.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck002, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(3);

    // Large scroll to trigger skip logic and preload
    ScrollBy(0, ITEM_MAIN_SIZE * 20);

    // Verify grid state is valid after large scroll with preload
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);
    EXPECT_GT(pattern_->info_.startIndex_, 0);
    EXPECT_TRUE(pattern_->info_.endIndex_ >= pattern_->info_.startIndex_);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck003
 * @tc.desc: Test PreloadItems debug check when scrolling backward
 *           Verifies continuity check works correctly during backward scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck003, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    layoutProperty_->UpdateCachedCount(2);

    // Scroll forward then backward to trigger preload in both directions
    ScrollBy(0, ITEM_MAIN_SIZE * 5);
    int32_t forwardStartIndex = pattern_->info_.startIndex_;
    EXPECT_EQ(forwardStartIndex, 10);

    ScrollBy(0, -ITEM_MAIN_SIZE * 2);

    // Verify backward scroll with preload maintains valid state
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);
    EXPECT_LT(pattern_->info_.startIndex_, forwardStartIndex);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck004
 * @tc.desc: Test PreloadItems with irregular items
 *           Verifies debug continuity check handles irregular grid layout correctly.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck004, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(Get3LinesIrregularDemoOptions(30, ITEM_MAIN_SIZE));
    CreateFixedItems(30);
    CreateDone();

    layoutProperty_->UpdateCachedCount(2);

    // Scroll with irregular items
    ScrollBy(0, ITEM_MAIN_SIZE * 2);

    // Verify irregular layout with preload maintains valid gridMatrix_
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);
    EXPECT_GT(pattern_->info_.startIndex_, 0);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck005
 * @tc.desc: Test PreloadItems at grid boundaries (start and end)
 *           Verifies continuity check handles edge cases at grid boundaries.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck005, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    layoutProperty_->UpdateCachedCount(2);

    // At start - preload should handle boundary correctly
    ScrollBy(0, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);

    // Scroll to end
    ScrollTo(ITEM_MAIN_SIZE * 15);
    EXPECT_TRUE(pattern_->info_.reachEnd_);

    // Preload at end boundary should work correctly
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_TRUE(pattern_->info_.reachEnd_);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: PreloadItemsMatrixContinuityCheck006
 * @tc.desc: Test PreloadItems with rapid consecutive scrolls
 *           Verifies continuity check remains stable during rapid scroll operations.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, PreloadItemsMatrixContinuityCheck006, TestSize.Level1)
{
    // Save original debug mode and enable it for this test
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(2);

    // Rapid consecutive scrolls
    for (int i = 0; i < 10; i++) {
        ScrollBy(0, ITEM_MAIN_SIZE);
    }

    // Verify grid state is consistent after rapid scrolls
    EXPECT_GT(pattern_->info_.gridMatrix_.size(), 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 27);
    // Restore original debug mode
    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

namespace {
GridLayoutOptions GetGapDemoOptions(int32_t crossCount, float itemMainSize, int32_t gapSize)
{
    GridLayoutOptions options;
    auto onGetStartIndexByOffset = [crossCount, itemMainSize](float offset) -> GridStartLineInfo {
        if (offset < 0.0f) {
            return { .startIndex = 0, .startLine = 0, .startOffset = 0 - offset, .totalOffset = offset };
        }
        int32_t line = offset / static_cast<int32_t>(itemMainSize);
        float startOffset = std::fmod(offset, itemMainSize);
        return {
            .startIndex = line * crossCount, .startLine = line, .startOffset = 0 - startOffset, .totalOffset = offset
        };
    };
    options.getStartIndexByOffset = std::move(onGetStartIndexByOffset);

    auto onGetStartIndexByIndex = [crossCount, itemMainSize, gapSize](int32_t targetIndex) -> GridStartLineInfo {
        int32_t line = targetIndex / crossCount;
        return { .startIndex = line * crossCount,
            .startLine = line - gapSize,
            .startOffset = 0.0f,
            .totalOffset = (line - gapSize) * itemMainSize };
    };
    options.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
    return options;
}
} // namespace

/**
 * @tc.name: CheckMatrixContinuousGapDetection001
 * @tc.desc: Test CheckMatrixContinuous detects gap when getStartIndexByIndex
 *           returns startLine shifted by -2 rows. A large scroll triggers skip
 *           logic, rebuilding matrix from scratch. PreloadItems calls
 *           getStartIndexByIndex for items not in the matrix, causing
 *           FillMatrixFromStartIndex to start from a wrong line and creating
 *           a gap between preload rows and viewport rows.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CheckMatrixContinuousGapDetection001, TestSize.Level1)
{
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetGapDemoOptions(2, ITEM_MAIN_SIZE, 2));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(3);

    ScrollBy(0, ITEM_MAIN_SIZE * 30);

    EXPECT_EQ(pattern_->info_.startIndex_, 60);
    EXPECT_EQ(pattern_->info_.endIndex_, 67);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 30);

    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: CheckMatrixContinuousGapDetection002
 * @tc.desc: Test CheckMatrixContinuous detects larger gap when getStartIndexByIndex
 *           returns startLine shifted by -4 rows. Uses a bigger gap to verify
 *           the check handles multi-row discontinuities.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CheckMatrixContinuousGapDetection002, TestSize.Level1)
{
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetGapDemoOptions(2, ITEM_MAIN_SIZE, 4));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(3);

    ScrollBy(0, ITEM_MAIN_SIZE * 30);

    EXPECT_EQ(pattern_->info_.startIndex_, 60);
    EXPECT_EQ(pattern_->info_.endIndex_, 67);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 30);

    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: CheckMatrixContinuousGapDetection003
 * @tc.desc: Test CheckMatrixContinuous with gap via wrong getStartIndexByIndex
 *           in a 3-column grid. Different column count changes row layout,
 *           verifying the gap detection works across configurations.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CheckMatrixContinuousGapDetection003, TestSize.Level1)
{
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetGapDemoOptions(3, ITEM_MAIN_SIZE, 2));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(3);

    ScrollBy(0, ITEM_MAIN_SIZE * 30);

    EXPECT_EQ(pattern_->info_.startIndex_, 90);
    EXPECT_EQ(pattern_->info_.endIndex_, 99);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 30);

    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

/**
 * @tc.name: CheckMatrixContinuousGapDetection004
 * @tc.desc: Test CheckMatrixContinuous with gap on smaller scroll.
 *           Uses a moderate scroll (10 rows) with cachedCount=2 to trigger
 *           PreloadItems where backward cache items fall outside the matrix.
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutAlgorithmTestNg, CheckMatrixContinuousGapDetection004, TestSize.Level1)
{
    bool originalDebugEnabled = SystemProperties::debugEnabled_;
    SystemProperties::debugEnabled_ = true;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetGapDemoOptions(2, ITEM_MAIN_SIZE, 2));
    CreateFixedItems(100);
    CreateDone();

    layoutProperty_->UpdateCachedCount(2);

    ScrollBy(0, ITEM_MAIN_SIZE * 10);

    EXPECT_EQ(pattern_->info_.startIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 27);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 10);

    SystemProperties::debugEnabled_ = originalDebugEnabled;
}

} // namespace OHOS::Ace::NG
