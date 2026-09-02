/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "irregular_matrices.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"

namespace OHOS::Ace::NG {
class GridLayoutRangeTest : public GridTestNg {};

/**
 * @tc.name: LayoutRangeSolver::SolveForward001
 * @tc.desc: Test LayoutRangeSolver::SolveForward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveForward001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_2;
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 40.0f }, { 2, 40.0f }, { 3, 10.0f }, { 4, 50.0f }, { 5, 70.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.currentOffset_ = 0.0f;
    info.startMainLineIndex_ = 3;
    info.startIndex_ = 4;
    auto res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 3);
    EXPECT_EQ(res.idx, 4);
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

    info.currentOffset_ = -9.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 3);
    EXPECT_EQ(res.pos, -9.0f);

    for (int i = 0; i < 3; ++i) {
        info.currentOffset_ = -10.0f - i * 1.0f;
        info.startMainLineIndex_ = 3;
        res = solver.FindStartingRow(1.0f);
        EXPECT_EQ(res.row, 4);
        EXPECT_EQ(res.idx, 5);
        EXPECT_EQ(res.pos, 1.0f - i * 1.0f);
    }

    info.currentOffset_ = -110.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 4);
    EXPECT_EQ(res.pos, -99.0f);
}

/**
 * @tc.name: LayoutRangeSolver::SolveForward002
 * @tc.desc: Test SolveForward when lineHeightMap_ front rows are cleared but gridMatrix_ retains
 *           multi-row items spanning those rows, preventing iterator underflow crash at line 175.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveForward002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 3 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 3, .columns = 3 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    // gridMatrix_ records item 3 starting at row 1, spanning rows 1-3.
    // lineHeightMap_ only has row 3+ (rows 0-2 were cleared, e.g. by ClearHeightsToEnd),
    // so row 3 is lineHeightMap_.begin().
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.axis_ = Axis::VERTICAL;
    info.gridMatrix_ = {
        { 1, { { 0, 3 }, { 1, -3 }, { 2, -3 } } },
        { 2, { { 0, -3 }, { 1, -3 }, { 2, -3 } } },
        { 3, { { 0, -3 }, { 1, -3 }, { 2, -3 } } },
    };
    info.lineHeightMap_ = { { 3, 40.0f }, { 4, 50.0f } };

    info.currentOffset_ = -10.0f;
    info.startMainLineIndex_ = 3;
    info.startIndex_ = 4;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // Before fix: --it at line 175 goes before lineHeightMap_.begin(), causing
    // invalid iterator dereference crash. CheckMultiRow(3) returns startRow=1,
    // so the loop tries to decrement it twice from begin().
    // After fix: begin() guard breaks the loop, no crash.
    auto res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 1);
    EXPECT_EQ(res.idx, 3);
    EXPECT_EQ(res.pos, -10.0f);
}

/**
 * @tc.name: LayoutRangeSolver::CheckMultiRow001
 * @tc.desc: Test LayoutRangeSolver::CheckMultiRow
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow001, TestSize.Level1)
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, -1 }, { 2, 2 } } },   // 0 | 0 | 2
        { 1, { { 0, 3 }, { 1, -3 }, { 2, -3 } } },  // 3 | 3 | 3
        { 2, { { 0, -3 }, { 1, -3 }, { 2, -3 } } }, // 3 | 3 | 3
    };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    EXPECT_EQ(solver.CheckMultiRow(2), std::make_pair(1, 3));

    EXPECT_EQ(solver.CheckMultiRow(0), std::make_pair(0, 0));
    EXPECT_EQ(solver.CheckMultiRow(1), std::make_pair(1, 3));
}

/**
 * @tc.name: LayoutRangeSolver::CheckMultiRow002
 * @tc.desc: Test LayoutRangeSolver::CheckMultiRow
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        1, // [1 x 2]
        2, // [1 x 0]
        3, // [1 x -1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        if (index == 2) {
            return { .rows = 1, .columns =0 };
        }
        return { .rows = 1, .columns = -1 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 2 }, { 2, 5 } } },  // 0 | 2 | 5
        { 1, { { 0, 1 }, { 1, 3 }, { 2, 6 } } },  // 1 | 3 | 6
        { 2, { { 0, -1 }, { 1, 4 }, { 2, 7 } } }, // 1 | 4 | 7
    };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    EXPECT_EQ(solver.CheckMultiRow(0), std::make_pair(0, 0));
    EXPECT_EQ(solver.CheckMultiRow(1), std::make_pair(1, 1));
}

/**
 * @tc.name: LayoutRangeSolver::SolveBackward001
 * @tc.desc: Test LayoutRangeSolver::SolveBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveBackward001, TestSize.Level1)
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, 0 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, 3 }, { 2, -3 } } },  // 2 | 3 | 3
        { 2, { { 0, 4 }, { 1, -3 }, { 2, -3 } } }, // 4 | 3 | 3
        { 3, { { 0, -4 }, { 1, 5 } } },            // 4 | 5 | x
        { 4, { { 0, 6 }, { 1, -6 }, { 2, 7 } } },  // 6 | 6 | 7
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
 * @tc.name: LayoutRangeSolver::SolveBackward002
 * @tc.desc: Test LayoutRangeSolver::SolveBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveBackward002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo10());
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_10;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 30.0f }, { 2, 40.0f }, { 3, 30.0f }, { 4, 50.0f } };

    info.currentOffset_ = 20.0f;
    info.startMainLineIndex_ = 3;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, -60.0f);
    EXPECT_EQ(res.row, 1);

    info.currentOffset_ = 6.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, -74.0f);
    EXPECT_EQ(res.row, 1);

    info.currentOffset_ = 5.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, 5.0f);
    EXPECT_EQ(res.row, 3);

    info.currentOffset_ = 4.0f;
    info.startMainLineIndex_ = 3;
    res = solver.FindStartingRow(5.0f);
    EXPECT_EQ(res.pos, 4.0f);
    EXPECT_EQ(res.row, 3);
}

/**
 * @tc.name: LayoutRangeSolver::SolveOverScroll001
 * @tc.desc: Test LayoutRangeSolver with overScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveOverScroll001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_12;
    info.lineHeightMap_ = { { 0, 10.0f }, { 1, 10.0f }, { 2, 10.0f }, { 3, 10.0f }, { 4, 10.0f }, { 5, 10.0f },
        { 6, 10.0f } };

    float offset = -50.0f;
    info.currentOffset_ = offset;
    info.startMainLineIndex_ = 1;
    info.startIndex_ = 2;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    for (int i = 0; i < 10; ++i) {
        auto res = solver.FindStartingRow(0.0f);
        // can't scroll further if all items are already above viewport
        EXPECT_EQ(res.pos, offset);
        EXPECT_EQ(res.row, 1);
        offset -= 10.0f;
        info.currentOffset_ = offset;
    }
}

/**
 * @tc.name: LayoutRangeSolver::SolveOverScroll002
 * @tc.desc: Test LayoutRangeSolver with overScroll upwards
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveOverScroll002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_12;
    info.lineHeightMap_ = { { 0, 10.0f }, { 1, 10.0f }, { 2, 10.0f }, { 3, 10.0f }, { 4, 10.0f }, { 5, 10.0f },
        { 6, 10.0f } };

    float offset = 0.0f;
    info.currentOffset_ = offset;
    info.startMainLineIndex_ = 0;
    info.startIndex_ = 0;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    for (int i = 0; i < 10; ++i) {
        auto res = solver.FindStartingRow(0.0f);
        EXPECT_EQ(res.pos, offset);
        EXPECT_EQ(res.row, 0);
        offset += 10.0f;
        info.currentOffset_ = offset;
    }
}

/**
 * @tc.name: ScrollItem001
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, ScrollItem001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 10.0f });
    constexpr float itemHeight = 250.0f;
    CreateFixedHeightItems(1, itemHeight * 2 + 10.0f);
    CreateFixedHeightItems(1, itemHeight);
    CreateFixedHeightItems(1, itemHeight * 2 + 10.0f);
    CreateFixedHeightItems(19, itemHeight);
    CreateFixedHeightItems(1, itemHeight * 6 + 50.0f);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();
    const auto& info = pattern_->info_;

    ScrollToIndex(88, false, ScrollAlign::AUTO);
    EXPECT_EQ(info.startIndex_, 85);
    EXPECT_EQ(info.endIndex_, 90);
    ScrollToIndex(2, false, ScrollAlign::CENTER);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.endIndex_, 2);
}

/**
 * @tc.name: ScrollItem002
 * @tc.desc: Test scroll to center of long item
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, ScrollItem002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 10.0f });
    constexpr float itemHeight = 150.0f;
    CreateFixedHeightItems(1, itemHeight * 2 + 10.0f);
    CreateFixedHeightItems(1, itemHeight);
    CreateFixedHeightItems(1, itemHeight * 2 + 10.0f);
    CreateFixedHeightItems(19, itemHeight);
    CreateFixedHeightItems(1, itemHeight * 6 + 50.0f);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();
    const auto& info = pattern_->info_;

    ScrollToIndex(22, false, ScrollAlign::CENTER, 0.0f);
    EXPECT_EQ(info.startIndex_, 22);
    EXPECT_EQ(info.endIndex_, 26);
    for (int i = info.startIndex_; i <= info.endIndex_; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
    EXPECT_EQ(GetChildY(frameNode_, 22), -275.0f);
}

/**
 * @tc.name: LayoutRangeSolver::Solve001
 * @tc.desc: Test LayoutRangeSolver::FindStartingRow when matrix is empty.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Solve001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateDone();

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
 * @tc.name: HorizontalOverScroll001
 * @tc.desc: Test horizontal and overScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Horizontal001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetRowsGap(Dimension { 1.0f });
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedWidthItems(1, 910.0f);
    CreateFixedWidthItems(1, 300.0f);
    CreateFixedWidthItems(20, 605.0f);
    CreateFixedWidthItems(8, 300.0f);
    CreateDone();

    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(FLT_MAX);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, -1);
    for (int i = 0; i < 5; ++i) {
        EXPECT_FALSE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
}

/**
 * @tc.name: ChangeTemplate001
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, ChangeTemplate001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 20.0f });
    constexpr float itemHeight = 390;
    CreateFixedHeightItems(22, itemHeight);
    CreateFixedHeightItems(1, (itemHeight + 20.0f) * 6);
    CreateFixedHeightItems(7, itemHeight);
    CreateFixedHeightItems(1, 100);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 29);
    EXPECT_EQ(info.endIndex_, 30);
    EXPECT_EQ(info.currentOffset_, 10.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 29), 10.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 28);
    EXPECT_EQ(info.endIndex_, 30);
    EXPECT_EQ(info.currentOffset_, 10.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 28), 10.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 29), 10.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    // startIdx changed, but currentOffset_ is maintained. So Item 28 no longer in range
    EXPECT_EQ(info.startIndex_, 22);
    EXPECT_EQ(info.endIndex_, 29);
    EXPECT_EQ(info.currentOffset_, -1230.0f);
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump to irregular item with extra offset
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Jump001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 20.0f });
    constexpr float itemHeight = 150.0f;
    CreateFixedHeightItems(22, itemHeight);
    CreateFixedHeightItems(1, (itemHeight + 20.0f) * 6);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();
    ScrollToIndex(22, false, ScrollAlign::AUTO, itemHeight);
    const auto& info = pattern_->info_;
    EXPECT_EQ(GetChildRect(frameNode_, 22).Bottom(), HEIGHT - itemHeight);
    EXPECT_EQ(info.startIndex_, 22);

    ScrollToIndex(88, false, ScrollAlign::AUTO, itemHeight);
    EXPECT_EQ(info.startIndex_, 85);
    EXPECT_EQ(info.endIndex_, 93);
    for (int i = 85; i <= 93; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
    }
    EXPECT_EQ(GetChildY(frameNode_, 91), 270.0f);
}

/**
 * @tc.name: MeasureToTarget001
 * @tc.desc: Test measure to target
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, MeasureToTarget001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 20.0f });
    constexpr float itemHeight = 390.0f;
    CreateFixedHeightItems(22, itemHeight);
    CreateFixedHeightItems(1, (itemHeight + 20.0f) * 6);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();
    pattern_->ScrollToIndex(23, true);
    EXPECT_EQ(pattern_->targetIndex_, 23);
    FlushUITasks();
    const auto& info = pattern_->info_;
    for (int i = 0; i < 24; ++i) {
        auto it = info.FindInMatrix(i);
        EXPECT_NE(it, info.gridMatrix_.end());
        bool found = false;
        for (auto item : it->second) {
            if (item.second == i) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
    EXPECT_FLOAT_EQ(info.GetAnimatePosIrregular(23, HEIGHT, ScrollAlign::AUTO, 20.0f), 5750.0f);
}

/**
 * @tc.name: MeasureToTarget002
 * @tc.desc: Test measure to target
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, MeasureToTarget002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 20.0f });
    constexpr float itemHeight = 150.0f;
    CreateFixedHeightItems(22, itemHeight);
    CreateFixedHeightItems(1, (itemHeight + 20.0f) * 6);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 91);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    ScrollToIndex(22, true, ScrollAlign::AUTO);
    EXPECT_TRUE(pattern_->AnimateToTargetImpl(ScrollAlign::AUTO, nullptr));
    const float offset = info.GetAnimatePosIrregular(22, HEIGHT, ScrollAlign::AUTO, 20.0f);
    UpdateCurrentOffset(pattern_->GetTotalOffset() - offset);

    EXPECT_TRUE(NearEqual(GetChildY(frameNode_, 22), 0.0f));
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 22)->IsActive());

    ScrollToIndex(22, true, ScrollAlign::AUTO);
    EXPECT_EQ(info.GetAnimatePosIrregular(22, HEIGHT, ScrollAlign::AUTO, 20.0f), -1.0f);
    pattern_->extraOffset_ = 0.0f;
    EXPECT_FALSE(pattern_->AnimateToTargetImpl(ScrollAlign::AUTO, nullptr));
}

/**
 * @tc.name: Cache001
 * @tc.desc: Test Grid preload items
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Cache001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) { return 100; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetLayoutOptions({});
    model.SetCachedCount(2); // 2 lines
    CreateDone();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 50);
    EXPECT_EQ(frameNode_->GetChildren().size(), 1);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 11);
    const std::list<int32_t> preloadList = { 12, 13, 14, 15, 16, 17 };
    for (const int32_t i : preloadList) {
        EXPECT_FALSE(frameNode_->GetChildByIndex(i));
    }
    CheckPreloadListEqual(preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(pattern_->preloadItemList_.empty());
    constexpr float itemWidth = (WIDTH - 20.0f) / 3.0f;
    for (const int32_t i : preloadList) {
        EXPECT_TRUE(frameNode_->GetChildByIndex(i));
        EXPECT_EQ(GetChildWidth(frameNode_, i), itemWidth);
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100);
    }

    // re-layout to trigger cache item layout
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 12), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 13), itemWidth + 10.0f);
    EXPECT_EQ(GetChildX(frameNode_, 14), (itemWidth + 10.0f) * 2);
    EXPECT_EQ(GetChildX(frameNode_, 15), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 16), itemWidth + 10.0f);
    EXPECT_EQ(GetChildX(frameNode_, 17), (itemWidth + 10.0f) * 2);
    EXPECT_EQ(GetChildY(frameNode_, 12), 440.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 440.0f);
    EXPECT_EQ(GetChildY(frameNode_, 14), 440.0f);
    EXPECT_EQ(GetChildY(frameNode_, 15), 550.0f);
    EXPECT_EQ(GetChildY(frameNode_, 16), 550.0f);
    EXPECT_EQ(GetChildY(frameNode_, 17), 550.0f);
    ScrollToIndex(49, false, ScrollAlign::AUTO);
    EXPECT_EQ(info.startIndex_, 39);
    const std::list<int32_t> preloadList2 = { 38, 37, 36, 35, 34, 33 };
    CheckPreloadListEqual(preloadList2);
    const int64_t time = GetSysTimestamp();
    PipelineContext::GetCurrentContext()->OnIdle(time - 1);
    // no time to execute
    CheckPreloadListEqual(preloadList2);
}

/**
 * @tc.name: Cache002
 * @tc.desc: Test Grid preload items
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Cache002, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) {
        if (idx == 0 || idx == 2) {
            return 210.0f;
        }
        if (idx == 22) {
            return 650.0f;
        }
        return 100.0f;
    });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetCachedCount(3); // 2 lines
    CreateDone();
    ScrollToIndex(20, false, ScrollAlign::END);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.currentOffset_, -30.0f);
    EXPECT_EQ(info.startIndex_, 9);
    EXPECT_EQ(info.endIndex_, 20);
    const std::list<int32_t> preloadList = { 8, 21, 7, 22, 6, 23, 5, 24, 4, 25, 3, 26, 27, 28, 29 };
    for (const int32_t i : preloadList) {
        EXPECT_FALSE(frameNode_->GetChildByIndex(i));
    }
    CheckPreloadListEqual(preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_EQ(GetChildHeight(frameNode_, 22), 650.0f);

    // re-layout to trigger cache item layout
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 8), -140.0f);
    EXPECT_EQ(GetChildY(frameNode_, 7), -140.0f);
    EXPECT_EQ(GetChildY(frameNode_, 6), -140.0f);
    EXPECT_EQ(GetChildY(frameNode_, 22), 410.0f);
    EXPECT_EQ(GetChildY(frameNode_, 23), 520.0f);
    EXPECT_EQ(GetChildY(frameNode_, 24), 630.0f);
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test grid dragged item
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Drag001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 10.0f });
    model.SetRowsGap(Dimension { 20.0f });
    model.SetEditable(true);
    constexpr float itemHeight = 150.0f;
    CreateFixedHeightItems(22, itemHeight);
    CreateFixedHeightItems(1, itemHeight * 5 + 100.0f);
    CreateFixedHeightItems(77, itemHeight);
    CreateDone();

    ScrollToIndex(21, false, ScrollAlign::START);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 2)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 2), 340.0f);
    EXPECT_EQ(GetChildY(frameNode_, 24), 340.0f);
    GestureEvent event;
    event.SetGlobalPoint(Point(5.0f, 350.0f));
    eventHub_->HandleOnItemDragStart(event);
    EXPECT_EQ(eventHub_->draggedIndex_, 24);
}

/**
 * @tc.name: ScrollEnabled001
 * @tc.desc: Test Grid scrollable_
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, ScrollEnabled001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    model.SetLayoutOptions(GetOptionDemo17());
    CreateFixedHeightItems(2, 500.0f);
    CreateFixedHeightItems(5, 250.0f);
    CreateDone();

    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-200.0f);
        EXPECT_TRUE(pattern_->scrollable_);
    }
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test Grid changing focus
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Focus001, TestSize.Level1)
{
    auto model = CreateRepeatGrid(50, [](uint32_t idx) { return 100; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    const auto options = GetOptionDemo14();
    model.SetLayoutOptions(options);
    model.SetCachedCount(1);
    CreateDone();
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-100);
        for (int i = pattern_->info_.startIndex_; i <= pattern_->info_.endIndex_; ++i) {
            bool hasInfo = GetChildPattern<GridItemPattern>(frameNode_, i)->GetIrregularItemInfo().has_value();
            if (options.irregularIndexes.count(i)) {
                EXPECT_TRUE(hasInfo);
            } else {
                EXPECT_FALSE(hasInfo);
            }
        }
    }
}

/**
 * @tc.name: Focus002
 * @tc.desc: Test Grid changing focus
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, Focus002, TestSize.Level1)
{
    auto model = CreateRepeatGrid(50, [](uint32_t idx) {
        if (idx == 0 || idx == 2) {
            return 400.0f;
        }
        if (idx == 22) {
            return 1200.0f;
        }
        return 200.0f;
    });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    const auto options = GetOptionDemo14();
    model.SetLayoutOptions(options);
    model.SetCachedCount(1);
    CreateDone();

    auto algo = pattern_->GetScopeFocusAlgorithm();
    auto curFocus = GetChildFocusHub(frameNode_, 0);
    EXPECT_TRUE(curFocus->IsFocusable());
    for (int i = 1; i < 50; ++i) {
        WeakPtr<FocusHub> next;
        algo.getNextFocusNode(FocusStep::TAB, curFocus, next);
        ASSERT_TRUE(next.Upgrade());
        next.Upgrade()->RequestFocusImmediately();
        EXPECT_EQ(i, frameNode_->GetChildTrueIndex(next.Upgrade()->GetFrameNode()));
        EXPECT_EQ(pattern_->focusHandler_.focusIndex_, i);
        curFocus = next.Upgrade();
    }
    for (int i = 48; i >= 0; --i) {
        WeakPtr<FocusHub> next;
        algo.getNextFocusNode(FocusStep::SHIFT_TAB, curFocus, next);
        ASSERT_TRUE(next.Upgrade());
        next.Upgrade()->RequestFocusImmediately();
        EXPECT_EQ(i, frameNode_->GetChildTrueIndex(next.Upgrade()->GetFrameNode()));
        EXPECT_EQ(pattern_->focusHandler_.focusIndex_, i);
        curFocus = next.Upgrade();
    }
}

/**
 * @tc.name: CheckMultiRow003
 * @tc.desc: Test CheckMultiRow with sparse gridMatrix (missing columns)
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow003, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 3 };  // Item 3 is multi-row
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 2, .columns = 2 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    // Sparse matrix: row 1 is missing column 1
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 1 }, { 1, 2 } } },      // Row 0: complete {1, 2}
        { 1, { { 0, -3 } } },                // Row 1: column 1 is MISSING!
        { 2, { { 0, -3 }, { 1, -3 } } },     // Row 2: complete {-3, -3}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // Before fix: CRASH (at(1).at(1) throws std::out_of_range)
    // After fix: should safely return without crash
    auto result = solver.CheckMultiRow(2);
    EXPECT_EQ(result, std::make_pair(0, 3));
}

/**
 * @tc.name: CheckMultiRow004
 * @tc.desc: Test CheckMultiRow with empty row
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow004, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2 };  // Item 2 is multi-row
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 2, .columns = 1 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    // Middle row is completely empty
    GridLayoutInfo info;
    info.crossCount_ = 1;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },  // Row 0: {0, 1}
        { 1, {} },                         // Row 1: EMPTY!
        { 2, { { 0, -2 } } },             // Row 2: {-2}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // Before fix: CRASH when accessing empty row
    // After fix: should safely stop traversal
    auto result = solver.CheckMultiRow(2);
    EXPECT_EQ(result, std::make_pair(1, 2));
}

/**
 * @tc.name: CheckMultiRow005
 * @tc.desc: Test CheckMultiRow with multiple sparse rows
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow005, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 5, 8 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 5) {
            return { .rows = 3, .columns = 2 };
        }
        return { .rows = 2, .columns = 2 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    // Multi-row sparse matrix with multiple missing columns
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },           // Row 0: complete
        { 1, { { 0, -5 }, { 2, 3 } } },                     // Row 1: column 1 is MISSING
        { 2, { { 0, -5 }, { 1, -5 }, { 2, -5 } } },       // Row 2: complete
        { 3, { { 0, 4 }, { 2, 5 } } },                     // Row 3: column 1 is MISSING
        { 4, { { 0, -8 }, { 1, -8 }, { 2, 6 } } },       // Row 4: complete
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // Starting from row 4, should traverse upward to find item 8's start row
    // Should safely handle missing columns in between
    auto result = solver.CheckMultiRow(4);
    EXPECT_EQ(result, std::make_pair(3, 8));
}

/**
 * @tc.name: GetOverScrollOffset002
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridTestNg, GetOverScrollOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(8);

    CreateDone();
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, -ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: CheckMultiRow006
 * @tc.desc: Test CheckMultiRow when colIt->second < 0 and previous column doesn't exist
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow006, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 2, .columns = 1 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 1 }, { 1, 2 } } },      // Row 0: {1, 2}
        { 1, { { 1, -2 } } },                // Row 1: column 0 is MISSING!
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result = solver.CheckMultiRow(1);
    EXPECT_EQ(result, std::make_pair(0, 2));
}

/**
 * @tc.name: CheckMultiRow007
 * @tc.desc: Test CheckMultiRow when colIt->second < 0 and previous column has different item
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow007, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2, 3 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 1 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 } } },  // Row 0: {1, 2, 3}
        { 1, { { 0, -2 }, { 1, 4 } } },          // Row 1: {-2, 4}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result = solver.CheckMultiRow(1);
    EXPECT_EQ(result, std::make_pair(0, 2));
}

/**
 * @tc.name: CheckMultiRow008
 * @tc.desc: Test CheckMultiRow when current row contains the start item
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow008, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 1, .columns = 2 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },          // Row 0: {0, 1}
        { 1, { { 0, 2 }, { 1, -2 }, { 2, 3 } } },  // Row 1: {2, -2, 3}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result = solver.CheckMultiRow(1);
    EXPECT_EQ(result, std::make_pair(1, 2));
}

/**
 * @tc.name: CheckMultiRow009
 * @tc.desc: Test CheckMultiRow with multiple multi-row items in same row
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow009, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2, 5, 8 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 2) {
            return { .rows = 3, .columns = 1 };
        }
        if (index == 5) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 2, .columns = 1 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },          // Row 0: {0, 1, 2}
        { 1, { { 0, 3 }, { 1, 4 }, { 2, -2 } } },          // Row 1: {3, 4, -2}
        { 2, { { 0, 5 }, { 1, 6 }, { 2, -2 } } },       // Row 2: {5, 6, -2}
        { 3, { { 0, -5 }, { 1, 7 }, { 2, 8 } } },        // Row 3: {-5, 7, 8}
        { 4, { { 0, 9 }, { 1, -8 } } },                  // Row 4: {9, -8}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result1 = solver.CheckMultiRow(2);
    EXPECT_EQ(result1, std::make_pair(0, 2));

    auto result2 = solver.CheckMultiRow(1);
    EXPECT_EQ(result2, std::make_pair(0, 2));

    auto result3 = solver.CheckMultiRow(4);
    EXPECT_EQ(result3, std::make_pair(3, 8));
}

/**
 * @tc.name: CheckMultiRow010
 * @tc.desc: Test CheckMultiRow with sparse matrix and item spanning multiple rows
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow010, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 3 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 2, .columns = 3 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },          // Row 0: {0, 1, 2}
        { 1, { { 0, 3 }, { 1, -3 }, { 2, -3 } } },        // Row 1: {3, -3, -3}
        { 2, { { 0, -3 }, { 1, -3 }, { 2, -3 } } },       // Row 2: {-3, -3, -3}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result1 = solver.CheckMultiRow(1);
    EXPECT_EQ(result1, std::make_pair(1, 3));

    auto result2 = solver.CheckMultiRow(2);
    EXPECT_EQ(result2, std::make_pair(1, 3));
}

/**
 * @tc.name: CheckMultiRow011
 * @tc.desc: Test CheckMultiRow when multi-row item starts at column 0 and c=0
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, CheckMultiRow011, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 2 };
    option.getSizeByIndex = [](int32_t index) -> GridItemSize {
        return { .rows = 2, .columns = 2 };
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 2 }, { 1, -2 } } },                  // Row 0: {2, -2}
        { 1, { { 0, -2 }, { 1, -2 } } },                  // Row 1: {-2, -2}
    };
    info.axis_ = Axis::VERTICAL;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto result = solver.CheckMultiRow(1);
    EXPECT_EQ(result, std::make_pair(0, 2));
}

/**
 * @tc.name: LayoutRangeSolver::FindStartingRowExtensionGuard001
 * @tc.desc: M-1 regression: with the start extension active, FindStartingRow must verify the
 *           whole SolveBackward span before augmenting the target length. A missing
 *           lineHeightMap_ entry inside the span must NOT make the visible range silently
 *           jump back to row 0 / item 0 (SolveBackward's {0,0,0} return).
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, FindStartingRowExtensionGuard001, TestSize.Level1)
{
    GridLayoutOptions option;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 2, { { 0, 4 }, { 1, 5 } } },
        { 3, { { 0, 6 }, { 1, 7 } } },
    };
    // rows 0-1 missing from lineHeightMap_ (e.g. heights cleared while matrix retained)
    info.lineHeightMap_ = { { 2, 40.0f }, { 3, 10.0f } };
    info.startMainLineIndex_ = 3;
    info.startIndex_ = 6;
    info.startFixOffset_ = 100.0f; // extension span reaches past the gap at row 1

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // currentOffset_ == 0: the guard must reject the extension branch (the old
    // code only checked row2 exists; SolveBackward returned {0,0,0} when it hit
    // the missing row1, jumping the view back to item 0) and fall back to the
    // original near-zero behavior.
    info.currentOffset_ = 0.0f;
    auto res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 3) << "guard must fall back to the original near-zero behavior";
    EXPECT_EQ(res.idx, 6);
    EXPECT_EQ(res.pos, 0.0f);

    // currentOffset_ > 0 (top blank): the extension walk crosses the gap, so
    // fall back to the baseline SolveBackward(5) (walks row2 only:
    // len = 1 + 40 + 1 = 42 > 5 stops before the gap).
    info.currentOffset_ = 5.0f;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 2) << "guard must fall back to the baseline SolveBackward span";
    EXPECT_EQ(res.idx, 4);
    // Baseline semantics: row2 top = targetLen - len + mainGap = 5 - 42 + 1 = -36 (partly above the viewport)
    EXPECT_EQ(res.pos, -36.0f);

    // Contrast: with all heights present the extension branch engages
    // (SolveBackward reaches row0, pos corrected by -startFixOffset_).
    info.gridMatrix_[0] = { { 0, 0 }, { 1, 1 } };
    info.gridMatrix_[1] = { { 0, 2 }, { 1, 3 } };
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 30.0f }, { 2, 40.0f }, { 3, 10.0f } };
    info.currentOffset_ = 0.0f;
    res = solver.FindStartingRow(1.0f);
    EXPECT_EQ(res.row, 0) << "extension branch must engage when the span is complete";
    EXPECT_EQ(res.idx, 0);
    // SolveBackward: len sums to 94 (1 + 41 + 31 + 21), pos evaluates to -93
    EXPECT_EQ(res.pos, -93.0f);
}

/**
 * @tc.name: LayoutRangeSolver::SolveForwardWithExtensionMissingMatrix001
 * @tc.desc: M-2 regression: SolveForwardWithExtension must not feed CheckMultiRow's {-1,-1}
 *           (gridMatrix_ row missing while lineHeightMap_ has the row) into the multi-row
 *           backtrack loop, which would subtract all heights above and leak startRow = -1.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveForwardWithExtensionMissingMatrix001, TestSize.Level1)
{
    GridLayoutOptions option;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    // matrix non-empty but row 3 missing; lineHeightMap_ only has row 3
    info.gridMatrix_ = { { 5, { { 0, 10 } } } };
    info.lineHeightMap_ = { { 3, 40.0f } };
    info.startMainLineIndex_ = 3;
    info.startIndex_ = 6;
    info.startFixOffset_ = 100.0f;
    info.currentOffset_ = -10.0f;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    auto res = solver.FindStartingRow(1.0f);
    EXPECT_GE(res.row, 0) << "startRow must not leak CheckMultiRow's -1";
    EXPECT_GE(res.idx, 0) << "startIdx must not leak CheckMultiRow's -1";
    // SkipLinesAboveView stays at row 3 (bottom 31 >= 0), the walk-back stops
    // at begin(), and CheckMultiRow(3) returns {-1,-1}: degrade to row 3
    // itself without multi-row backtrack.
    EXPECT_EQ(res.row, 3);
    EXPECT_EQ(res.idx, 6);
    EXPECT_EQ(res.pos, -10.0f) << "pos must stay walk-adjusted, not extreme negative";
}

/**
 * @tc.name: LayoutRangeSolver::SolveForwardForEndIdxDiscontinuousHeights001
 * @tc.desc: SolveForwardForEndIdx must walk consecutive line numbers and stop at the first
 *           missing lineHeightMap_ entry. After a bottom-edge jump (FillMatrixOnly fills the
 *           whole matrix but only view heights are measured) followed by a top-edge jump,
 *           lineHeightMap_ is discontinuous (e.g. {6,7} ∪ {16..20}). Map-order iteration
 *           silently skips the hole, treats stale far-away lines as adjacent and returns an
 *           end line inside the unmeasured range (which then collapses the active range in
 *           UpdateLayoutInfo's height validity check).
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutRangeTest, SolveForwardForEndIdxDiscontinuousHeights001, TestSize.Level1)
{
    GridLayoutOptions option;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 6, { { 0, 10 }, { 1, 11 } } },
        { 7, { { 0, 12 }, { 1, 13 } } },
        { 8, { { 0, 14 }, { 1, 15 } } },
        { 16, { { 0, 32 }, { 1, 33 } } },
        { 17, { { 0, 34 }, { 1, 35 } } },
        { 18, { { 0, 36 }, { 1, 37 } } },
    };
    // rows 8-15 unmeasured: the hole between the re-measured top range and the
    // stale bottom-edge range
    info.lineHeightMap_ = { { 6, 100.0f }, { 7, 100.0f }, { 16, 100.0f }, { 17, 100.0f }, { 18, 100.0f } };
    info.startMainLineIndex_ = 6;
    info.startIndex_ = 10;
    info.startFixOffset_ = 100.0f;
    info.endFixOffset_ = 100.0f;
    info.currentOffset_ = 0.0f;

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    // Extension-inflated target (view end bound = mainSize + endFix): the walk
    // must stop at the hole (row 7), not jump to the stale row 16.
    auto [endLine, endIdx] = solver.SolveForwardForEndIdx(20.0f, 300.0f, 6);
    EXPECT_EQ(endLine, 7) << "walk must stop at the first missing line, not jump the hole";
    EXPECT_EQ(endIdx, 13);

    // Small target: row 6 alone exceeds it, so the walk adds nothing further.
    std::tie(endLine, endIdx) = solver.SolveForwardForEndIdx(20.0f, 100.0f, 6);
    EXPECT_EQ(endLine, 6);
    EXPECT_EQ(endIdx, 11);

    // Contrast: with the map consecutive through row 8, the same target keeps
    // the original accumulate-while-fits semantics (row 8 crosses 300).
    info.lineHeightMap_[8] = 100.0f;
    std::tie(endLine, endIdx) = solver.SolveForwardForEndIdx(20.0f, 300.0f, 6);
    EXPECT_EQ(endLine, 8) << "consecutive map must keep the original walk semantics";
    EXPECT_EQ(endIdx, 15);
}
} // namespace OHOS::Ace::NG
