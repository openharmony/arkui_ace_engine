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

namespace OHOS::Ace::NG {
class GridCustomLayoutTestNg : public GridTestNg {};

/**
 * @tc.name: InitializedMeasure
 * @tc.desc: Test Grid custom layout algorithm initial measure
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, InitializedMeasure, TestSize.Level1)
{
    int32_t crossCount = 2;
    GridLayoutOptions options;
    auto onGetStartIndexByOffset = [crossCount](float offset) -> GridStartLineInfo {
        int32_t line = offset / static_cast<int32_t>(ITEM_MAIN_SIZE);
        float startOffset = std::fmod(offset, ITEM_MAIN_SIZE);
        return { .startIndex = line * crossCount, .startLine = line, .startOffset = startOffset };
    };
    options.getStartIndexByOffset = std::move(onGetStartIndexByOffset);

    auto onGetStartIndexByIndex = [crossCount](int32_t targetIndex) -> GridStartLineInfo {
        int32_t line = targetIndex / crossCount;
        return { .startIndex = line * crossCount, .startLine = line };
    };
    options.getStartIndexByIndex = std::move(onGetStartIndexByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(options);
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: ScrollByBackward001
 * @tc.desc: Test Grid custom layout algorithm with scroll by
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollByBackward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();

    ScrollBy(0, ITEM_MAIN_SIZE / 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 4);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);

    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 4);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 6);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50);
}

/**
 * @tc.name: ScrollByBackward002
 * @tc.desc: Test Grid custom layout algorithm with scroll by large Offset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollByBackward002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollBy(0, HEIGHT * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 8);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 11);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

    ScrollBy(0, HEIGHT * 3);
    EXPECT_EQ(pattern_->info_.startIndex_, 40);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 23);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: ScrollToBackward001
 * @tc.desc: Test Grid custom layout algorithm with scroll To
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, ScrollToBackward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollTo(HEIGHT * 2);
    EXPECT_EQ(pattern_->info_.startIndex_, 16);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 8);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 11);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);

    ScrollTo(HEIGHT * 5);
    EXPECT_EQ(pattern_->info_.startIndex_, 40);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 20);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 23);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
}

/**
 * @tc.name: UpdateCurrentOffset
 * @tc.desc: Test Grid custom layout algorithm with updateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, UpdateCurrentOffset, TestSize.Level1)
{
    int32_t crossCount = 2;
    auto onScrollbarUpdate = [crossCount](int32_t index,
                                 Dimension offset) -> std::pair<std::optional<float>, std::optional<float>> {
        return { index / crossCount * ITEM_MAIN_SIZE - offset.Value(), ITEM_MAIN_SIZE / crossCount * ITEM_MAIN_SIZE };
    };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(crossCount, ITEM_MAIN_SIZE));
    model.SetOnScrollBarUpdate(std::move(onScrollbarUpdate));
    CreateFixedItems(50);
    CreateDone();
    for (int32_t i = 1; i < 15; ++i) {
        UpdateCurrentOffset(-30.0f, SCROLL_FROM_UPDATE);
        EXPECT_EQ(pattern_->GetTotalOffset(), 30.f * i);
    }
}

/**
 * @tc.name: UpdateCrossCount
 * @tc.desc: Test Grid custom layout algorithm with crossCount updated
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, UpdateCrossCount, TestSize.Level1)
{
    int32_t crossCount = 2;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(crossCount, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 42);
    EXPECT_EQ(pattern_->info_.endIndex_, 49);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 2100.f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    layoutProperty_->UpdateLayoutOptions(GetRegularDemoOptions(4, ITEM_MAIN_SIZE));
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 36);
    EXPECT_EQ(pattern_->info_.endIndex_, 49);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 900.f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    layoutProperty_->UpdateLayoutOptions(GetRegularDemoOptions(3, ITEM_MAIN_SIZE));
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 36);
    EXPECT_EQ(pattern_->info_.endIndex_, 47);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.totalOffset_, 1200.f);
}

/**
 * @tc.name: FillBackward_GridMatrixAndLineHeightMapSize_001
 * @tc.desc: Test FillBackward verifies gridMatrix_ and lineHeightMap_ size relationship.
 *              DESIGN RATIONALE:
 *              - gridMatrix_ is always 1 larger than lineHeightMap_ (lookahead strategy)
 *              - FillOne() pre-creates the next line in gridMatrix_ before MeasureItem()
 *              - When targetLen is reached, the pre-created line remains (lookahead)
 *              - This optimization enables fast scrolling without re-measurement
 *
 *              HEIGHT=400, ITEM_MAIN_SIZE=100, ROW_GAP=5
 *              Each line = 105px (100 + 5 gap)
 *              Viewport needs: 400 / 105 ≈ 3.81 → 4 lines
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, FillBackward_GridMatrixAndLineHeightMapSize_001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(ROW_GAP));
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Initial state: lines 0-3 (4 lines measured)
    // lineHeightMap_ has 4 entries (lines 0-3)
    // gridMatrix_ has 5 entries (lines 0-4, includes 1 lookahead line)
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 5);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.lineHeightMap_.size()), 4);

    // Scroll up by one line height (105px)
    // After scroll: lines 1-4 visible (4 lines)
    // lineHeightMap_ has 5 entries (lines 0-4)
    // gridMatrix_ has 6 entries (lines 0-5, includes 1 lookahead line)
    ScrollBy(0, ITEM_MAIN_SIZE + ROW_GAP);

    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 4);
    // gridMatrix = lineHeightMap + 1 (lookahead optimization)
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 6);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.lineHeightMap_.size()), 5);
}

/**
 * @tc.name: FillBackward_GridMatrixAndLineHeightMapSize_002
 * @tc.desc: Test FillBackward with larger scroll distance.
 *              DESIGN RATIONALE:
 *              - gridMatrix_ = lineHeightMap_ + 1 (lookahead optimization)
 *              - Pre-allocated line enables fast forward scrolling
 *
 *              HEIGHT=400, ITEM_MAIN_SIZE=100, ROW_GAP=5
 *              Each line = 105px, Viewport needs 4 lines
 *              Scroll by HEIGHT (400px) ≈ 3.81 lines
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, FillBackward_GridMatrixAndLineHeightMapSize_002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(ROW_GAP));
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(100);
    CreateDone();

    // Initial: 4 measured lines (lines 0-3)
    // lineHeightMap_ has 4 entries (lines 0-3)
    // gridMatrix_ has 5 entries (lines 0-4, includes 1 lookahead line)
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 3);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 5);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.lineHeightMap_.size()), 4);

    // Scroll up by HEIGHT (400px)
    // 400 / 105 ≈ 3.81 → scroll to line 4
    // After scroll: lines 4-7 visible (4 lines)
    // lineHeightMap_ has 8 entries (lines 0-7, measured lines)
    // gridMatrix_ has 9 entries (lines 0-8, includes 1 lookahead line)
    ScrollBy(0, HEIGHT);

    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 3);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 7);
    // gridMatrix = lineHeightMap + 1 (lookahead optimization)
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 9);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.lineHeightMap_.size()), 8);
}

/**
 * @tc.name: FillBackward_GridMatrixAndLineHeightMapSize_003
 * @tc.desc: Test FillBackward with multiple small scrolls.
 *              DESIGN RATIONALE:
 *              - gridMatrix_ = lineHeightMap_ + 1 (lookahead optimization)
 *              - Each scroll triggers FillBackward to extend gridMatrix_
 *
 *              HEIGHT=400, ITEM_MAIN_SIZE=100, ROW_GAP=5
 *              Each scroll = 50px, 5 scrolls = 250px total
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomLayoutTestNg, FillBackward_GridMatrixAndLineHeightMapSize_003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(ROW_GAP));
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(50);
    CreateDone();

    // Initial: lines 0-3 (4 lines)
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 5);

    // 5 scrolls of 50px each = 250px total
    // 250 / 105 ≈ 2.38 → scroll to line 2
    // After scrolls: lines 2-6 visible (5 lines)
    // lineHeightMap_ has 7 entries (lines 0-6)
    // gridMatrix_ has 8 entries (lines 0-7, includes 1 lookahead line)
    for (int32_t i = 0; i < 5; ++i) {
        ScrollBy(0, ITEM_MAIN_SIZE / 2);
    }

    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 2);
    EXPECT_EQ(pattern_->info_.endMainLineIndex_, 6);
    // gridMatrix = lineHeightMap + 1 (lookahead optimization)
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.gridMatrix_.size()), 8);
    EXPECT_EQ(static_cast<int32_t>(pattern_->info_.lineHeightMap_.size()), 7);
}
} // namespace OHOS::Ace::NG