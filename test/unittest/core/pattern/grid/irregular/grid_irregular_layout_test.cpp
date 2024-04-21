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

#include "gtest/gtest.h"
#include "irregular_matrices.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
class GridIrregularLayoutTest : public GridTestNg {};

/**
 * @tc.name: LayoutRangeSolver::AddNextRow001
 * @tc.desc: Test LayoutRangeSolver::AddNextRow
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, AddNextRow001, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, AddNextRows002, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, SolveForward001, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, CheckMultiRow001, TestSize.Level1)
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
    EXPECT_EQ(solver.CheckMultiRow(2), 2);

    EXPECT_EQ(solver.CheckMultiRow(0), 1);
    EXPECT_EQ(solver.CheckMultiRow(1), 1);
}

/**
 * @tc.name: LayoutRangeSolver::SolveBackward001
 * @tc.desc: Test LayoutRangeSolver::SolveBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, SolveBackward001, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, SolveBackward002, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, SolveOverScroll001, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, SolveOverScroll002, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, Solve001, TestSize.Level1)
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
HWTEST_F(GridIrregularLayoutTest, LayoutChildren001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateFixedItem(10);
    });

    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF { .left = 5.0f, .top = 3.0f });

    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 0, 0 }, { 2, 1 } } }, // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, 3 }, { 2, 4 } } }, // 2 | 3 | 4
        { 2, { { 0, 5 }, { 1, 6 }, { 2, 7 } } }, // 5 | 6 | 7
        { 3, { { 0, 8 }, { 1, -8 } } },          // 8 | 8 | x
        { 4, { { 0, 9 }, { 1, -9 } } },          // 9 | 9 | x
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
 * @tc.desc: Test GridIrregularLayout::Measure with offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo11());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateItem(10, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->gridLayoutInfo_.currentOffset_ = 0.0f;
    algorithm->gridLayoutInfo_.childrenCount_ = 10;
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

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);

    algorithm->gridLayoutInfo_.currentOffset_ = 5.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 9);
}

/**
 * @tc.name: GridIrregularLayout::Measure002
 * @tc.desc: Test GridIrregularLayout::Measure with offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo5());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(11);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->gridLayoutInfo_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 11;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(610.0f, 600.0f));
    std::vector<float> cmp = { 302.5f, 302.5f };
    EXPECT_EQ(algorithm->crossLens_, cmp);
    EXPECT_EQ(algorithm->mainGap_, 1.0f);
    EXPECT_EQ(algorithm->crossGap_, 5.0f);
    EXPECT_EQ(info.crossCount_, 2);

    EXPECT_EQ(info.lineHeightMap_.at(0), 200.0f);
    for (int i = 0; i < 9; ++i) {
        info.currentOffset_ -= 20.0f;
        algorithm->Measure(AceType::RawPtr(frameNode_));
        EXPECT_EQ(info.currentOffset_, (i + 1) * -20.0f);
        EXPECT_EQ(info.startMainLineIndex_, 0);
        EXPECT_EQ(info.endMainLineIndex_, 6);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 4);
    }

    info.currentOffset_ -= 20.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, 1.0f); // 1.0f is mainGap
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(info.endIndex_, 4);
    EXPECT_EQ(info.startIndex_, 2);
}

/**
 * @tc.name: GridIrregularLayout::Measure003
 * @tc.desc: Test GridIrregularLayout::Measure with offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo5());
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(11);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->gridLayoutInfo_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 11;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    info.currentOffset_ = -401.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.startMainLineIndex_, 2);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.currentOffset_, 1.0f);

    info.currentOffset_ = -200.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, 1.0f);
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 8);
    EXPECT_EQ(info.startIndex_, 4);
    EXPECT_EQ(info.endIndex_, 7);

    info.startMainLineIndex_ = 2;
    info.startIndex_ = 3;
    info.currentOffset_ = -201.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 8);
    EXPECT_EQ(info.startIndex_, 4);
    EXPECT_EQ(info.endIndex_, 7);
    std::map<int, int> lineCmp = { { 0, -5 }, { 1, 7 } };
    EXPECT_EQ(info.gridMatrix_.at(8), lineCmp);
}

/**
 * @tc.name: GridIrregularLayout::Measure004
 * @tc.desc: Test GridIrregularLayout::Measure with overScroll disabled
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure004, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo2());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(8);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->overScroll_ = false;
    auto& info = algorithm->gridLayoutInfo_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 8;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    EXPECT_EQ(info.lineHeightMap_.at(0), 99.5f);
    for (int i = -2; i < 3; ++i) {
        info.currentOffset_ = i * 1.0f;
        algorithm->Measure(AceType::RawPtr(frameNode_));
        if (i > 0) {
            EXPECT_EQ(info.currentOffset_, 0.0f);
        } else {
            EXPECT_EQ(info.currentOffset_, i * 1.0f);
        }
        EXPECT_EQ(info.startMainLineIndex_, 0);
        EXPECT_EQ(info.endMainLineIndex_, 3);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 4);
    }

    info.startMainLineIndex_ = 0;
    info.startIndex_ = 0;
    info.currentOffset_ = -1000.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, -303.5f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 7);
    std::map<int32_t, float> EXPECTED_MAP = { { 0, 99.5 }, { 1, 99.5 }, { 2, 200.0f }, { 3, 200.0f }, { 4, 200.0f },
        { 5, 99.5f } };
    EXPECT_EQ(info.lineHeightMap_, EXPECTED_MAP);
}

/**
 * @tc.name: GridIrregularLayout::Measure005
 * @tc.desc: Test GridIrregularLayout::Measure with mainSize > content
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure005, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo2());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(8);
        ViewAbstract::SetWidth(CalcLength(610.0f));
        ViewAbstract::SetHeight(CalcLength(1000.0f));
    });
    auto& info = pattern_->gridLayoutInfo_;
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_2);
    EXPECT_EQ(info.GetTotalLineHeight(1.0f), 903.5f);
}

/**
 * @tc.name: GridIrregularLayout::MeasureJump001
 * @tc.desc: Test GridIrregularLayout::Measure with jump index
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, MeasureJump001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo11());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(10);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->gridLayoutInfo_;
    info.jumpIndex_ = 7;
    info.scrollAlign_ = ScrollAlign::AUTO;
    info.childrenCount_ = 10;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    std::vector<float> cmp = { 200.0f, 200.0f, 200.0f };
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 610.0f);
    EXPECT_EQ(algorithm->crossLens_, cmp);

    EXPECT_EQ(algorithm->mainGap_, 1.0f);
    EXPECT_EQ(algorithm->crossGap_, 5.0f);

    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(info.jumpIndex_, EMPTY_JUMP_INDEX);
    EXPECT_EQ(info.endIndex_, 9);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);

    info.jumpIndex_ = 6;
    info.scrollAlign_ = ScrollAlign::END;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.jumpIndex_, EMPTY_JUMP_INDEX);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.endIndex_, 6);
}

/**
 * @tc.name: GridIrregularLayout::MeasureTarget001
 * @tc.desc: Test GridIrregularLayout::Measure with target index
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, MeasureTarget001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo5());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(11);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->gridLayoutInfo_;
    info.childrenCount_ = 11;

    info.targetIndex_ = 10;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    EXPECT_EQ(info.crossCount_, 2);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.endIndex_, 3);
    EXPECT_EQ(info.lineHeightMap_.size(), 12);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);

    info.lineHeightMap_.erase(info.lineHeightMap_.begin(), info.lineHeightMap_.find(7));
    info.startIndex_ = 5;
    info.startMainLineIndex_ = 7;
    info.endIndex_ = 10;
    info.endMainLineIndex_ = 11;

    info.targetIndex_ = 2;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);
    EXPECT_EQ(info.lineHeightMap_.size(), 11);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.startIndex_, 5);
    EXPECT_EQ(info.startMainLineIndex_, 7);
}

/**
 * @tc.name: GridIrregularLayout::TestReset001
 * @tc.desc: Test changing crossCount to an existing matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TestReset001, TestSize.Level1)
{
    GridLayoutInfo oldInfo;
    oldInfo.crossCount_ = 2;
    oldInfo.childrenCount_ = 12;
    // simulate reset after template change
    oldInfo.gridMatrix_.clear();
    oldInfo.currentOffset_ = -10.0f;
    oldInfo.startMainLineIndex_ = 2;
    oldInfo.startIndex_ = 3;
    oldInfo.endMainLineIndex_ = 7;
    oldInfo.endIndex_ = 11;
    oldInfo.lineHeightMap_ = {
        { 0, 50.0f },
        { 1, 50.0f },
        { 2, 50.0f },
        { 3, 50.0f },
        { 4, 50.0f },
        { 5, 50.0f },
        { 6, 50.0f },
        { 7, 50.0f },
    };
    // changing cross count, should jump to the current startIndex
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo6());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(12);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 1000.0f }, .percentReference = { 610.0f, 1000.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->overScroll_ = true;
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    algo->Measure(AceType::RawPtr(frameNode_));

    const auto& info = algo->gridLayoutInfo_;
    EXPECT_EQ(info.childrenCount_, 12);
    EXPECT_EQ(info.crossCount_, 3);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_6_VARIATION);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.endIndex_, 11);
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.currentOffset_, -10.0f);
}

/**
 * @tc.name: GridIrregularLayout::TestReset002
 * @tc.desc: Test IrregularLayout::CheckForReset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TestReset002, TestSize.Level1)
{
    GridLayoutInfo oldInfo;
    oldInfo.crossCount_ = 2;
    // matrix has been cleared
    oldInfo.gridMatrix_ = {};
    oldInfo.currentOffset_ = -70.0f;
    oldInfo.startMainLineIndex_ = 3;
    oldInfo.startIndex_ = 5;
    oldInfo.endMainLineIndex_ = 7;
    oldInfo.endIndex_ = 10;
    oldInfo.crossCount_ = 3;
    oldInfo.lineHeightMap_ = {
        { 0, 50.0f },
    };
    // changing children count
    Create([](GridModelNG model) { model.SetColumnsTemplate("1fr 1fr 1fr"); });
    oldInfo.childrenCount_ = 8;
    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    algo->CheckForReset(3);

    const auto& info = algo->gridLayoutInfo_;
    EXPECT_TRUE(info.gridMatrix_.empty());
    EXPECT_TRUE(info.lineHeightMap_.empty());
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
}

/**
 * @tc.name: GridIrregularLayout::TestReset003
 * @tc.desc: Test IrregularLayout::CheckForReset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TestReset003, TestSize.Level1)
{
    GridLayoutInfo oldInfo;
    // matrix has been cleared
    oldInfo.gridMatrix_ = MATRIX_DEMO_1;
    oldInfo.currentOffset_ = -20.0f;
    oldInfo.startMainLineIndex_ = 3;
    oldInfo.startIndex_ = 5;
    oldInfo.endMainLineIndex_ = 6;
    oldInfo.endIndex_ = 10;
    oldInfo.crossCount_ = 3;
    oldInfo.lineHeightMap_ = {
        { 0, 50.0f },
        { 1, 50.0f },
        { 2, 50.0f },
        { 3, 50.0f },
        { 4, 50.0f },
        { 5, 50.0f },
        { 6, 50.0f },
    };
    // changing children count
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo1());
    });
    oldInfo.childrenCount_ = 11;
    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    frameNode_->childrenUpdatedFrom_ = 5;
    algo->CheckForReset(3);

    const auto& info = algo->gridLayoutInfo_;
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.jumpIndex_, 5);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(algo->postJumpOffset_, -20.0f);
    EXPECT_EQ(info.lineHeightMap_.size(), 3);
    const decltype(GridLayoutInfo::gridMatrix_) cmp = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },   // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -2 }, { 2, -1 } } }, // 2 | 2 | 1
        { 2, { { 0, 3 }, { 1, 4 }, { 2, -1 } } },  // 3 | 4 | 1
    };
    EXPECT_EQ(info.gridMatrix_, cmp);
}

/**
 * @tc.name: GridIrregularLayout::TestReset004
 * @tc.desc: Test measuring by child request (child update)
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TestReset004, TestSize.Level1)
{
    GridLayoutInfo oldInfo;
    oldInfo.crossCount_ = 3;
    oldInfo.childrenCount_ = 8;
    oldInfo.gridMatrix_ = MATRIX_DEMO_10;
    oldInfo.currentOffset_ = -1.0f;
    oldInfo.startMainLineIndex_ = 1;
    oldInfo.startIndex_ = 2;
    oldInfo.endMainLineIndex_ = 5;
    oldInfo.endIndex_ = 7;
    oldInfo.lineHeightMap_ = {
        { 0, 50.0f },
        { 1, 50.0f },
        { 2, 50.0f },
        { 3, 50.0f },
        { 4, 50.0f },
        { 5, 50.0f },
        { 6, 50.0f },
        { 7, 50.0f },
    };
    // changing cross count, should jump to the current startIndex
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo10());
        model.SetColumnsGap(Dimension { 5.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateFixedItem(8);
    });
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);
    frameNode_->GetLayoutProperty()->propertyChangeFlag_ = PROPERTY_UPDATE_BY_CHILD_REQUEST;

    algo->Measure(AceType::RawPtr(frameNode_));

    // item height updated to 200.0f
    auto& info = algo->gridLayoutInfo_;
    EXPECT_EQ(info.childrenCount_, 8);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_10);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    EXPECT_EQ(info.currentOffset_, -1.0f);

    // offset upwards after reset
    info.currentOffset_ = 50.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, -151.0f);
}

/**
 * @tc.name: GridIrregularLayout::Layout001
 * @tc.desc: Test GridIrregularLayout::Layout
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Layout001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        CreateFixedItem(10);
    });
    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF { .left = 1.0f, .top = 1.0f });
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF { 200.0f, 500.0f });
    frameNode_->GetGeometryNode()->SetContentSize(SizeF { 200.0f, 500.0f });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->crossLens_ = { 50.0f, 50.0f, 50.0f };
    auto& info = algorithm->gridLayoutInfo_;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },  // 0 | 0 | 0
        { 1, { { 0, 2 }, { 1, 3 }, { 2, 4 } } },  // 2 | 3 | 4
        { 2, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },  // 5 | 6 | 7
        { 3, { { 0, 8 }, { 1, -6 }, { 2, 9 } } }, // 8 | 6 | 9
    };
    info.lineHeightMap_ = { { 0, 20.0f }, { 1, 20.0f }, { 2, 10.0f }, { 3, 15.0f } };
    info.childrenCount_ = 10;
    info.crossCount_ = 3;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 0;
    info.endIndex_ = 9;
    info.currentOffset_ = 10.0f;
    algorithm->Layout(AceType::RawPtr(frameNode_));
    algorithm->UpdateLayoutInfo();

    EXPECT_TRUE(info.reachStart_);
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_TRUE(info.offsetEnd_);
}
/**
 * @tc.name: GridIrregularLayout::FindJumpLineIndex001
 * @tc.desc: Test GridLayoutRangeFinder::FindJumpLineIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, FindJumpLineIndex001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo1());
    });

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algo->gridLayoutInfo_;
    info.childrenCount_ = 11;
    info.crossCount_ = 3;

    info.scrollAlign_ = ScrollAlign::END;
    EXPECT_EQ(algo->FindJumpLineIdx(5), 6);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_1);

    info.scrollAlign_ = ScrollAlign::CENTER;
    EXPECT_EQ(algo->FindJumpLineIdx(5), 3);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_1);

    info.gridMatrix_.clear();
    info.scrollAlign_ = ScrollAlign::START;
    EXPECT_EQ(algo->FindJumpLineIdx(10), 5);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_1);

    info.startIndex_ = 2;
    info.endIndex_ = 7;
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 4;
    EXPECT_EQ(algo->FindJumpLineIdx(6), 3);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_1);
}

/**
 * @tc.name: GridIrregularLayout::FindRangeOnJump001
 * @tc.desc: Test GridLayoutRangeFinder::FindRangeOnJump
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, FindRangeOnJump001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f }, { 5, 75.0f },
        { 6, 10.0f } };
    info.gridMatrix_ = MATRIX_DEMO_1;

    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo1());
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
 * @tc.name: GridIrregularLayout::FindRangeOnJump002
 * @tc.desc: Test GridLayoutRangeFinder::FindRangeOnJump special endIndex (endIndex not on the last line).
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, FindRangeOnJump002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f }, { 5, 75.0f } };
    info.gridMatrix_ = MATRIX_DEMO_8;

    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo8());
    });
    frameNode_->GetGeometryNode()->SetContentSize({ 500.0f, 250.0f });

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.scrollAlign_ = ScrollAlign::END;
    auto res = solver.FindRangeOnJump(5, 5.0f);
    EXPECT_EQ(res.startRow, 1);
    EXPECT_EQ(res.pos, -125.0f);
    EXPECT_EQ(res.endIdx, 6);
    EXPECT_EQ(res.endRow, 5);
}

/**
 * @tc.name: GridIrregularLayout::SolveForwardForEndIdx001
 * @tc.desc: Test GridLayoutRangeFinder::SolveForwardForEndIdx
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, SolveForwardForEndIdx001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 100.0f }, { 2, 50.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },    // 0 | 0 | 1
        { 1, { { 0, 2 }, { 1, -2 }, { 2, -2 } } },  // 2 | 2 | 2
        { 2, { { 0, -2 }, { 1, -2 }, { 2, -2 } } }, // 2 | 2 | 2
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },    // 3 | 4 | 5
        { 4, { { 0, 6 }, { 1, -6 }, { 2, -5 } } },  // 6 | 6 | 5
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

namespace {
void CheckAlignStart(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
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
}

void CheckAlignCenter(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
    // can't align center with idx 0
    info.scrollAlign_ = ScrollAlign::CENTER;
    int32_t idx = 0;
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
}

void CheckAlignEnd(const RefPtr<GridIrregularLayoutAlgorithm>& algorithm, GridLayoutInfo& info)
{
    // can't align end with idx 1 and len 200.0f
    info.scrollAlign_ = ScrollAlign::END;
    int32_t idx = 1;
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
}
} // namespace

/**
 * @tc.name: GridIrregularLayout::PrepareLineHeights001
 * @tc.desc: Test GridIrregularLayout::PrepareLineHeights001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, PrepareLineHeights001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions({});
        CreateFixedItem(15);
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
    info.childrenCount_ = 15;

    CheckAlignStart(algorithm, info);
    CheckAlignCenter(algorithm, info);
    CheckAlignEnd(algorithm, info);

    EXPECT_EQ(cmp, info.gridMatrix_);
    EXPECT_EQ(cmpH, info.lineHeightMap_);
}

/**
 * @tc.name: GridIrregularLayout::SkipLines001
 * @tc.desc: Test GridIrregularLayout::SkipLines001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, SkipLines001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo1());
    });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->gridLayoutInfo_;
    info.crossCount_ = 3;
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f } };
    info.gridMatrix_ = MATRIX_DEMO_1;
    info.childrenCount_ = 11;

    info.currentOffset_ = -500.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 5);
    info.currentOffset_ = -900.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 9);
    info.currentOffset_ = -1500.0f;
    EXPECT_EQ(algorithm->SkipLinesForward(), 10);

    info.lineHeightMap_ = { { 3, 200.0f }, { 4, 200.0f } };
    info.startIndex_ = 5;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;

    info.currentOffset_ = 400.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 2);

    info.currentOffset_ = 800.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 0);

    info.currentOffset_ = 1500.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 0);
}

/**
 * @tc.name: GridIrregularLayout::SkipLines002
 * @tc.desc: Test GridIrregularLayout::SkipLines backward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, SkipLines002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo11());
    });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->gridLayoutInfo_;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_11;
    info.childrenCount_ = 10;

    info.lineHeightMap_ = { { 4, 300.0f }, { 5, 300.0f }, { 6, 300.0f } };
    info.startIndex_ = 7;
    info.startMainLineIndex_ = 6;
    info.endMainLineIndex_ = 6;
    info.endIndex_ = 9;

    info.currentOffset_ = 700.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 3);

    info.currentOffset_ = 1300.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 0);

    info.currentOffset_ = 1600.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 0);
}

/**
 * @tc.name: GridIrregularLayout::TrySkipping001
 * @tc.desc: Test GridIrregularLayout::TrySkipping001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TrySkipping001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo2());
        CreateFixedItem(8);
    });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 200.0f, 200.0f, 200.0f };

    auto& info = algorithm->gridLayoutInfo_;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;

    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 200.0f }, { 2, 200.0f } };
    info.gridMatrix_ = MATRIX_DEMO_2;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 1;

    info.currentOffset_ = -50.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = -300.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = -800.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = -801.0f;
    EXPECT_TRUE(algorithm->TrySkipping(300.0f));
    EXPECT_EQ(info.startIndex_, 5);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);

    info.scrollAlign_ = ScrollAlign::NONE;
    info.lineHeightMap_ = { { 3, 200.0f }, { 4, 200.0f } };
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 4;
    info.endIndex_ = 7;

    info.currentOffset_ = 50.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = 300.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = 800.0f;
    EXPECT_FALSE(algorithm->TrySkipping(300.0f));
    info.currentOffset_ = 801.0f;
    EXPECT_TRUE(algorithm->TrySkipping(300.0f));
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
}

/**
 * @tc.name: GridIrregularLayout::TransformAutoScrollAlign001
 * @tc.desc: Test IrregularLayout::TransformAutoScrollAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TransformAutoScrollAlign001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo8());
    });

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algo->gridLayoutInfo_;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 300.0f }, { 2, 30.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = MATRIX_DEMO_8;
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
}

/**
 * @tc.name: GridIrregularLayout::TransformAutoScrollAlign002
 * @tc.desc: Test IrregularLayout::TransformAutoScrollAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TransformAutoScrollAlign002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo8());
    });

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algo->gridLayoutInfo_;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 300.0f }, { 2, 30.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = MATRIX_DEMO_8;
    algo->mainGap_ = 5.0f;

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
 * @tc.name: GridIrregularLayout::Integrated001
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Integrated001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo8());
        model.SetColumnsGap(Dimension { 5.0f });
        CreateFixedItem(7);
        model.SetEdgeEffect(EdgeEffect::NONE, true);
    });
    const std::map<int32_t, float> HEIGHT_MAP = { { 0, 200.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 200.0f },
        { 4, 200.0f }, { 5, 200.0f / 3 } };
    auto& info = pattern_->gridLayoutInfo_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 4);
    EXPECT_EQ(info.lineHeightMap_, HEIGHT_MAP);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_8);

    UpdateCurrentOffset(-200.0f);
    EXPECT_FLOAT_EQ(info.currentOffset_, -200.0f / 3);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_TRUE(info.hasBigItem_);
}

/**
 * @tc.name: GridIrregularLayout::Integrated002
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Integrated002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo13());
        model.SetColumnsGap(Dimension { 5.0f });
        CreateItem(1, -2, 300.0f);
        CreateItem(1, -2, 100.0f);
        CreateItem(1, -2, 200.0f);
        CreateItem(1, -2, 600.0f);
        CreateItem(5, -2, 100.0f);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        ViewAbstract::SetHeight(CalcLength(300.0f));
    });
    auto& info = pattern_->gridLayoutInfo_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 2);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(-5.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 2);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    UpdateCurrentOffset(3.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 2);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    for (int i = 0; i < 5; ++i) {
        UpdateCurrentOffset(3.0f);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 0);
    }
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 2);
    EXPECT_TRUE(info.reachStart_);
}

/**
 * @tc.name: GridIrregularLayout::GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, GetOverScrollOffset001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo13());
        model.SetColumnsGap(Dimension { 5.0f });
        CreateItem(1, -2, 300.0f);
        CreateItem(1, -2, 100.0f);
        CreateItem(1, -2, 200.0f);
        CreateItem(1, -2, 600.0f);
        CreateItem(5, -2, 100.0f);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        ViewAbstract::SetHeight(CalcLength(300.0f));
    });
    auto& info = pattern_->gridLayoutInfo_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(-200.0f);
    UpdateCurrentOffset(-200.0f);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info.endIndex_, 8);

    UpdateCurrentOffset(-150.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.startMainLineIndex_, 5);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    UpdateCurrentOffset(-50.0f);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(pattern_->GetOverScrollOffset(-50).end, -50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(-10).end, -10.0f);
    EXPECT_EQ(
        info.GetDistanceToBottom(info.lastMainSize_, info.totalHeightOfItemsInView_, pattern_->GetMainGap()), 0.0f);
    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(60).end, 50.0f);
    EXPECT_EQ(pattern_->GetOverScrollOffset(20).end, 20.0f);
}

/**
 * @tc.name: GridIrregularLayout::Gaps001
 * @tc.desc: Test changing gaps
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Gaps001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo6());
        model.SetColumnsGap(Dimension { 1.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateItem(12, -2, 200.0f);
    });

    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 240.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 402.0f);

    layoutProperty_->UpdateColumnsGap(Dimension { 5.0f });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 242.5f);
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 237.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 402.0f);

    layoutProperty_->UpdateRowsGap(Dimension { 3.0f });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 242.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 406.0f);
}

/**
 * @tc.name: GridIrregularLayout::Width001
 * @tc.desc: Test width priority of gridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Width001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo6());
        model.SetColumnsGap(Dimension { 1.0f });
        model.SetRowsGap(Dimension { 1.0f });
        CreateItem(12, 300.0f, 200.0f);
    });

    FlushLayoutTask(frameNode_);
    for (int32_t i = 0; i < 6; i++) {
        EXPECT_EQ(GetChildSize(frameNode_, i).Width(), 300.0f);
    }
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 300.0f);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll001
 * @tc.desc: Test overScroll disabled with long item
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, OverScroll001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo12());
        model.SetColumnsGap(Dimension { 1.0f });
        model.SetEdgeEffect(EdgeEffect::NONE, true);
        CreateItem(1, -2, 600.0f);
        CreateItem(1, -2, 300.0f);
        CreateItem(1, -2, 1800.0f);
        CreateItem(4, -2, 300.0f);
    });

    FlushLayoutTask(frameNode_);
    UpdateCurrentOffset(-450.0f);
    auto& info = pattern_->gridLayoutInfo_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_12);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, -450.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(200.0f);
    EXPECT_EQ(info.currentOffset_, -250.0f);
    EXPECT_EQ(info.startIndex_, 0);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info.currentOffset_, -550.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(200.0f);
    EXPECT_EQ(info.currentOffset_, -350.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.currentOffset_, -350.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll002
 * @tc.desc: Test overScroll until completely out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, OverScroll002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo13());
        model.SetColumnsGap(Dimension { 5.0f });
        CreateItem(1, -2, 300.0f);
        CreateItem(1, -2, 100.0f);
        CreateItem(1, -2, 200.0f);
        CreateItem(1, -2, 600.0f);
        CreateItem(5, -2, 100.0f);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        ViewAbstract::SetHeight(CalcLength(300.0f));
    });
    auto& info = pattern_->gridLayoutInfo_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(200.0f);
        EXPECT_EQ(info.startMainLineIndex_, 0);
        EXPECT_GT(info.currentOffset_, 0.0f);
    }
}

/**
 * @tc.name: GridIrregularLayout::OverScroll003
 * @tc.desc: Test overScroll until completely out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, OverScroll003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(GetOptionDemo13());
        model.SetColumnsGap(Dimension { 5.0f });
        CreateItem(1, -2, 300.0f);
        CreateItem(1, -2, 100.0f);
        CreateItem(1, -2, 200.0f);
        CreateItem(1, -2, 600.0f);
        CreateItem(5, -2, 100.0f);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        ViewAbstract::SetHeight(CalcLength(300.0f));
    });
    auto& info = pattern_->gridLayoutInfo_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    // first move to end
    for (int i = 0; i < 4; ++i) {
        UpdateCurrentOffset(-200.0f);
    }
    EXPECT_EQ(info.currentOffset_, -300.0f);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    EXPECT_TRUE(info.offsetEnd_);
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-200.0f);
        EXPECT_LT(info.currentOffset_, -499.9f);
        EXPECT_EQ(info.startMainLineIndex_, 5);
        EXPECT_EQ(info.startIndex_, 3);
        EXPECT_EQ(info.endMainLineIndex_, 10);
        EXPECT_EQ(info.endIndex_, 8);
    }
}

namespace {
const decltype(GridLayoutInfo::lineHeightMap_) cmp = { { 0, ITEM_HEIGHT }, { 1, ITEM_HEIGHT }, { 2, ITEM_HEIGHT },
    { 3, ITEM_HEIGHT }, { 6, ITEM_HEIGHT }, { 7, ITEM_HEIGHT }, { 8, ITEM_HEIGHT }, { 9, ITEM_HEIGHT } };
}
/**
 * @tc.name: GetEndOffset000
 * @tc.desc: Test scrolling past limits
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, GetEndOffset000, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions({});
        CreateFixedItem(20, GridItemStyle::NONE);
    });

    int32_t targetIndex = 19;
    auto& info = pattern_->gridLayoutInfo_;
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->ScrollToIndex(targetIndex, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    for (int i = 0; i < 10; ++i) {
        UpdateCurrentOffset(-10000.0f);
    }
    EXPECT_EQ(info.lineHeightMap_, cmp);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_LT(info.currentOffset_, -15000.0f);
}

/**
 * @tc.name: GetEndOffset001
 * @tc.desc: Test GetEndOffset with updated offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, GetEndOffset001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetLayoutOptions({});
        CreateFixedItem(20, GridItemStyle::NONE);
    });

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, false, align);
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->gridLayoutInfo_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    info.currentOffset_ -= 1000.0f;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-2000.0f);
    EXPECT_TRUE(info.synced_);
    EXPECT_EQ(info.lineHeightMap_, cmp);
    EXPECT_EQ(info.currentOffset_, -400.0f);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    // last item should match up with the bottom again
    EXPECT_EQ(pattern_->GetEndOffset(), GRID_HEIGHT - ITEM_HEIGHT);
}
} // namespace OHOS::Ace::NG
