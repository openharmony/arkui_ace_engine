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

#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"

namespace OHOS::Ace::NG {
class GridIrregularFillerTest : public GridTestNg {};

/**
 * @tc.name: LayoutRangeSolver::AddNextRow001
 * @tc.desc: Test LayoutRangeSolver::AddNextRow
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, AddNextRow001, TestSize.Level1)
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
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },  // 0 | 1 | 2
        { 1, { { 0, 0 }, { 1, 3 }, { 2, -3 } } }, // 0 | 3 | 3
    };
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 30.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.AddNextRows(5.0f, 0);
    EXPECT_EQ(res.first, 2);
    EXPECT_EQ(res.second, 80.0f + 5.0f * 2);
}

/**
 * @tc.name: LayoutRangeSolver::AddNextRows002
 * @tc.desc: Test LayoutRangeSolver::AddNextRows
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, AddNextRows002, TestSize.Level1)
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
        { 0, { { 0, 0 }, { 0, 1 }, { 2, 2 } } },  // 0 | 1 | 2
        { 1, { { 0, 0 }, { 1, 3 }, { 2, -3 } } }, // 0 | 3 | 3
        { 2, { { 0, 0 } } },                      // 0 | x | x
    };
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 60.0f }, { 2, 40.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    auto res = solver.AddNextRows(5.0f, 0);
    EXPECT_EQ(res.first, 3);
    EXPECT_EQ(res.second, 165.0f);

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
HWTEST_F(GridIrregularFillerTest, SolveForward001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo2());
    });

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_2;
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 40.0f }, { 2, 40.0f }, { 3, 10.0f }, { 4, 50.0f }, { 5, 70.0f } };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.currentOffset_ = 0.0f;
    info.startMainLineIndex_ = 3;
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
 * @tc.name: LayoutRangeSolver::CheckMultiRow001
 * @tc.desc: Test LayoutRangeSolver::CheckMultiRow
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, CheckMultiRow001, TestSize.Level1)
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
        { 1, { { 0, 3 }, { 1, -3 }, { 2, -3 } } },  // 3 | 3 | 3
        { 2, { { 0, -3 }, { 1, -3 }, { 2, -3 } } }, // 3 | 3 | 3
    };

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));
    EXPECT_EQ(solver.CheckMultiRow(2), std::make_pair(1, 3));

    EXPECT_EQ(solver.CheckMultiRow(0), std::make_pair(0, 0));
    EXPECT_EQ(solver.CheckMultiRow(1), std::make_pair(1, 3));
}

/**
 * @tc.name: LayoutRangeSolver::SolveBackward001
 * @tc.desc: Test LayoutRangeSolver::SolveBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, SolveBackward001, TestSize.Level1)
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
HWTEST_F(GridIrregularFillerTest, SolveBackward002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo10());
    });

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
HWTEST_F(GridIrregularFillerTest, SolveOverScroll001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo12());
    });

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
HWTEST_F(GridIrregularFillerTest, SolveOverScroll002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo12());
    });

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
 * @tc.name: LayoutRangeSolver::Solve001
 * @tc.desc: Test LayoutRangeSolver::FindStartingRow when matrix is empty.
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Solve001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
