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

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"

namespace OHOS::Ace::NG {
class GridIrregularLayoutTest : public GridTestNg {};

/**
 * @tc.name: GridIrregularLayout::LayoutChildren001
 * @tc.desc: Test GridIrregularLayout::LayoutChildren
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, LayoutChildren001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();

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
    algorithm->crossLens_ = { 25.0f, 25.0f, 50.0f };
    algorithm->crossGap_ = 5.0f;
    algorithm->mainGap_ = 1.0f;
    algorithm->LayoutChildren(0.0f, 0);

    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(5, 3)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 1), OffsetF(65, 3)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 2), OffsetF(5, 24)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 3), OffsetF(35, 24)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 4), OffsetF(65, 24)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 5), OffsetF(5, 45)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 6), OffsetF(35, 45)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 7), OffsetF(65, 45)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 8), OffsetF(5, 56)));
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 9), OffsetF(5, 72)));
}

/**
 * @tc.name: GridIrregularLayout::Measure001
 * @tc.desc: Test GridIrregularLayout::Measure with offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo11());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateGridItems(10, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 610.0f, 600.0f }, .percentReference = { 610.0f, 600.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->info_.currentOffset_ = 0.0f;
    algorithm->info_.childrenCount_ = 10;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    std::vector<float> cmp = { 200.0f, 200.0f, 200.0f };
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 610.0f);
    EXPECT_EQ(algorithm->crossLens_, cmp);

    const auto& info = algorithm->info_;
    EXPECT_EQ(algorithm->mainGap_, 1.0f);
    EXPECT_EQ(algorithm->crossGap_, 5.0f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 9);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);

    algorithm->info_.currentOffset_ = 5.0f;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(11);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->info_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 11;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(310.0f, 300.0f));
    std::vector<float> cmp = { 152.5f, 152.5f };
    EXPECT_EQ(algorithm->crossLens_, cmp);
    EXPECT_EQ(algorithm->mainGap_, 1.0f);
    EXPECT_EQ(algorithm->crossGap_, 5.0f);
    EXPECT_EQ(info.crossCount_, 2);

    EXPECT_EQ(info.lineHeightMap_.at(0), 100);
    for (int i = 0; i < 9; ++i) {
        info.currentOffset_ -= 10.0f;
        algorithm->Measure(AceType::RawPtr(frameNode_));
        EXPECT_EQ(info.currentOffset_, (i + 1) * -10.0f);
        EXPECT_EQ(info.startMainLineIndex_, 0);
        EXPECT_EQ(info.endMainLineIndex_, 6);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 4);
    }

    info.currentOffset_ -= 10.0f;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(11);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->info_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 11;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    info.currentOffset_ = -201.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.startMainLineIndex_, 2);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.currentOffset_, 1.0f);

    info.currentOffset_ = -100.0f;
    algorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, 1.0f);
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 8);
    EXPECT_EQ(info.startIndex_, 4);
    EXPECT_EQ(info.endIndex_, 7);

    info.startMainLineIndex_ = 2;
    info.startIndex_ = 3;
    info.currentOffset_ = -101.0f;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(8);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->overScroll_ = false;
    auto& info = algorithm->info_;
    info.currentOffset_ = 0.0f;
    info.childrenCount_ = 8;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    EXPECT_EQ(info.lineHeightMap_.at(0), 49.5f);
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
    EXPECT_EQ(info.currentOffset_, -153.5f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.startIndex_, 1);
    EXPECT_EQ(info.endIndex_, 7);
    std::map<int32_t, float> EXPECTED_MAP = { { 0, 49.5 }, { 1, 49.5 }, { 2, 100.0f }, { 3, 100.0f }, { 4, 100.0f },
        { 5, 49.5f } };
    EXPECT_EQ(info.lineHeightMap_, EXPECTED_MAP);
}

/**
 * @tc.name: GridIrregularLayout::Measure005
 * @tc.desc: Test GridIrregularLayout::Measure with mainSize > content
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Measure005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(8);
    ViewAbstract::SetWidth(CalcLength(610.0f));
    ViewAbstract::SetHeight(CalcLength(1000.0f));
    CreateDone();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_2);
    EXPECT_EQ(info.GetTotalLineHeight(1.0f), 453.5f);
}

/**
 * @tc.name: GridIrregularLayout::MeasureJump001
 * @tc.desc: Test GridIrregularLayout::Measure with jump index
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, MeasureJump001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo11());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(10);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;
    frameNode_->isConstraintNotChanged_ = true;
    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->info_;
    info.jumpIndex_ = 7;
    info.scrollAlign_ = ScrollAlign::AUTO;
    info.childrenCount_ = 10;
    algorithm->Measure(AceType::RawPtr(frameNode_));

    std::vector<float> cmp = { 100.0f, 100.0f, 100.0f };
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 310.0f);
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(11);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    auto& info = algorithm->info_;
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
        { 0, 25.0f },
        { 1, 25.0f },
        { 2, 25.0f },
        { 3, 25.0f },
        { 4, 25.0f },
        { 5, 25.0f },
        { 6, 25.0f },
        { 7, 25.0f },
    };
    // changing cross count, should jump to the current startIndex
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(12);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 500.0f }, .percentReference = { 310.0f, 500.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->overScroll_ = true;
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    algo->Measure(AceType::RawPtr(frameNode_));

    const auto& info = algo->info_;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateDone();
    oldInfo.childrenCount_ = 8;
    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    algo->CheckForReset();

    const auto& info = algo->info_;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo1());
    CreateDone();
    oldInfo.childrenCount_ = 11;
    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    frameNode_->childrenUpdatedFrom_ = 5;
    algo->CheckForReset();

    const auto& info = algo->info_;
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
        { 0, 25.0f },
        { 1, 25.0f },
        { 2, 25.0f },
        { 3, 25.0f },
        { 4, 25.0f },
        { 5, 25.0f },
        { 6, 25.0f },
        { 7, 25.0f },
    };
    // changing cross count, should jump to the current startIndex
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo10());
    model.SetColumnsGap(Dimension { 5.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateFixedItems(8);
    CreateDone();
    LayoutConstraintF constraint { .maxSize = { 310.0f, 300.0f }, .percentReference = { 310.0f, 300.0f } };
    layoutProperty_->layoutConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(oldInfo);
    algo->wrapper_ = AceType::RawPtr(frameNode_);
    frameNode_->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_BY_CHILD_REQUEST);

    algo->Measure(AceType::RawPtr(frameNode_));

    // item height updated to 200.0f
    auto& info = algo->info_;
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
    EXPECT_EQ(info.currentOffset_, -51.0f);
}

/**
 * @tc.name: GridIrregularLayout::Layout001
 * @tc.desc: Test GridIrregularLayout::Layout
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Layout001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(PaddingPropertyF { .left = 1.0f, .top = 1.0f });
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF { 200.0f, 500.0f });
    frameNode_->GetGeometryNode()->SetContentSize(SizeF { 200.0f, 500.0f });

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->crossLens_ = { 50.0f, 50.0f, 50.0f };
    auto& info = algorithm->info_;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo1());
    CreateDone();

    auto algo = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algo->info_;
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

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo1());
    CreateDone();
    frameNode_->GetGeometryNode()->SetContentSize({ 500.0f, 250.0f });

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.scrollAlign_ = ScrollAlign::START;
    auto res = solver.FindRangeOnJump(3, 2, 5.0f);
    EXPECT_EQ(res.startRow, 0);
    EXPECT_EQ(res.pos, -160.0f);
    EXPECT_EQ(res.endIdx, 10);
    EXPECT_EQ(res.endRow, 5);

    info.scrollAlign_ = ScrollAlign::CENTER;
    res = solver.FindRangeOnJump(8, 4, 5.0f);
    EXPECT_EQ(res.startRow, 0);
    EXPECT_EQ(res.pos, -185.0f);
    EXPECT_EQ(res.endIdx, 10);
    EXPECT_EQ(res.endRow, 5);

    info.scrollAlign_ = ScrollAlign::END;
    res = solver.FindRangeOnJump(8, 4, 5.0f);
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

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    CreateDone();
    frameNode_->GetGeometryNode()->SetContentSize({ 500.0f, 250.0f });

    GridLayoutRangeSolver solver(&info, AceType::RawPtr(frameNode_));

    info.scrollAlign_ = ScrollAlign::END;
    auto res = solver.FindRangeOnJump(5, 5, 5.0f);
    EXPECT_EQ(res.startRow, 1);
    EXPECT_EQ(res.pos, -125.0f);
    EXPECT_EQ(res.endIdx, 6);
    EXPECT_EQ(res.endRow, 5);
}

/**
 * @tc.name: GridIrregularLayout::JumpCenter001
 * @tc.desc: Test jumping with align center
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, JumpCenter001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetRowsGap(Dimension { 5.0f });
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 305.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 925.0f);
    CreateFixedHeightItems(4, 150.0f);
    CreateDone();
    pattern_->ScrollToIndex(2, false, ScrollAlign::CENTER);
    FlushUITasks();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(GetChildY(frameNode_, 2), -262.5f);
}

/**
 * @tc.name: GridIrregularLayout::TargetPos001
 * @tc.desc: Test calculate target position
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TargetPos001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetRowsGap(Dimension { 5.0f });
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 305.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 925.0f);
    CreateFixedHeightItems(4, 150.0f);
    CreateDone();

    pattern_->ScrollToIndex(2, true, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 417.5f);

    UpdateCurrentOffset(-200.0f);

    pattern_->ScrollToIndex(1, true, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);

    pattern_->ScrollToIndex(0, true, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);

    UpdateCurrentOffset(-100.0f);

    pattern_->ScrollToIndex(6, true, ScrollAlign::END);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 215.0f);

    pattern_->ScrollToIndex(2, true, ScrollAlign::END);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 680.0f);
}

/**
 * @tc.name: GridIrregularLayout::TargetPos002
 * @tc.desc: Test calculate target position
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TargetPos002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo10());
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(3, 150.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);

    pattern_->ScrollToIndex(0, true, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);

    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0)->GetCollectionItemInfo().row, 0);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0)->GetCollectionItemInfo().column, 0);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 1)->GetCollectionItemInfo().row, 0);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 1)->GetCollectionItemInfo().column, 1);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 2)->GetCollectionItemInfo().row, 1);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 2)->GetCollectionItemInfo().column, 0);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 3)->GetCollectionItemInfo().row, 1);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 3)->GetCollectionItemInfo().column, 1);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 4)->GetCollectionItemInfo().row, 2);
    EXPECT_EQ(
        GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 4)->GetCollectionItemInfo().column, 0);
}

/**
 * @tc.name: GridIrregularLayout::JumpAuto001
 * @tc.desc: Test jumping to irregular item with align center
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, JumpAuto001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetRowsGap(Dimension { 5.0f });
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 305.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 925.0f);
    CreateFixedHeightItems(4, 150.0f);
    CreateDone();

    pattern_->ScrollToIndex(2, false, ScrollAlign::AUTO);
    FlushUITasks();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(GetChildY(frameNode_, 2), -525.0f);

    // shouldn't move
    pattern_->ScrollToIndex(2, false, ScrollAlign::AUTO);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 2), -525.0f);

    pattern_->ScrollToIndex(2, false, ScrollAlign::START);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.0f);

    pattern_->ScrollToIndex(2, false, ScrollAlign::AUTO);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.0f);
}

/**
 * @tc.name: GridIrregularLayout::ToEdge001
 * @tc.desc: Test jumping to bottom edge
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, ToEdge001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 900.0f);
    CreateFixedHeightItems(4, 150.0f);
    CreateDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.currentOffset_, -500.0f);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(GetChildY(frameNode_, 2), -500.0f);
    for (int i = 0; i < 20; ++i) {
        UpdateCurrentOffset(100.0f);
    }
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
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

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateDone();

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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(15);
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 1.0f, 1.0f, 1.0f };
    auto& info = algorithm->info_;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo1());
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->info_;
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
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);

    info.currentOffset_ = 1500.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);
}

/**
 * @tc.name: GridIrregularLayout::SkipLines002
 * @tc.desc: Test GridIrregularLayout::SkipLines backward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, SkipLines002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo11());
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);

    auto& info = algorithm->info_;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_11;
    info.childrenCount_ = 10;

    info.lineHeightMap_ = { { 4, 300.0f }, { 5, 300.0f }, { 6, 300.0f } };
    info.startIndex_ = 7;
    info.startMainLineIndex_ = 6;
    info.endMainLineIndex_ = 6;
    info.endIndex_ = 9;

    info.currentOffset_ = 700.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 5);

    info.currentOffset_ = 1300.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 2);

    info.currentOffset_ = 1600.0f;
    EXPECT_EQ(algorithm->SkipLinesBackward(), 1);
}

/**
 * @tc.name: GridIrregularLayout::TrySkipping001
 * @tc.desc: Test GridIrregularLayout::TrySkipping001
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TrySkipping001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    CreateFixedItems(8);
    CreateDone();

    auto algorithm = AceType::MakeRefPtr<GridIrregularLayoutAlgorithm>(GridLayoutInfo {});
    algorithm->wrapper_ = AceType::RawPtr(frameNode_);
    algorithm->crossLens_ = { 100.0f, 100.0f, 100.0f };

    auto& info = algorithm->info_;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;

    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    info.gridMatrix_ = MATRIX_DEMO_2;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 1;

    info.currentOffset_ = -25.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -150.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -400.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = -401.0f;
    EXPECT_TRUE(algorithm->TrySkipping(150.0f));
    EXPECT_EQ(info.startIndex_, 5);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);

    info.scrollAlign_ = ScrollAlign::NONE;
    info.lineHeightMap_ = { { 3, 100.0f }, { 4, 100.0f } };
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 4;
    info.endIndex_ = 7;

    info.currentOffset_ = 25.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 150.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 400.0f;
    EXPECT_FALSE(algorithm->TrySkipping(150.0f));
    info.currentOffset_ = 401.0f;
    EXPECT_TRUE(algorithm->TrySkipping(150.0f));
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::START);
}

/**
 * @tc.name: GridIrregularLayout::Integrated001
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Integrated001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedItems(7);
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateDone();
    const std::map<int32_t, float> HEIGHT_MAP = { { 0, 100.0f }, { 1, 50.0f }, { 2, 50.0f }, { 3, 100.0f },
        { 4, 100.0f }, { 5, 100.0f / 3 } };
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 4);
    EXPECT_EQ(info.lineHeightMap_, HEIGHT_MAP);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_8);

    UpdateCurrentOffset(-100.0f);
    EXPECT_FLOAT_EQ(info.currentOffset_, -100.0f / 3);
    EXPECT_EQ(info.endIndex_, 6);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_FLOAT_EQ(info.GetIrregularHeight(0.0f), 400 + 100.0f / 3);
    EXPECT_FLOAT_EQ(info.GetIrregularOffset(0.0f), 100.0f / 3);
}

/**
 * @tc.name: GridIrregularLayout::Integrated002
 * @tc.desc: Test full layout process
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Integrated002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
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
 * @tc.name: GridIrregularLayout::Integrated003
 * @tc.desc: Test large offset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Integrated003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetColumnsGap(Dimension { 5.0f });
    for (int i = 0; i < 500; ++i) {
        CreateGridItems(1, -2, rand() % 1000);
    }
    CreateDone();

    bool pos = true;
    for (int i = 0; i < 100; ++i) {
        float offset = 1000.0f + (rand() % 9000);
        if (!pos) {
            offset = -offset;
        }
        pos = !pos;
        UpdateCurrentOffset(offset);
    }
    const auto& info = pattern_->info_;
    EXPECT_TRUE(info.endMainLineIndex_ >= info.startMainLineIndex_);
    EXPECT_TRUE(info.startIndex_ <= info.endIndex_);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    for (int i = 0; i < 100; ++i) {
        float offset = 1000.0f + (rand() % 9000);
        if (!pos) {
            offset = -offset;
        }
        pos = !pos;
        UpdateCurrentOffset(offset);
    }
    EXPECT_TRUE(info.endMainLineIndex_ >= info.startMainLineIndex_);
    EXPECT_TRUE(info.startIndex_ <= info.endIndex_);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    for (int i = 0; i < 100; ++i) {
        float offset = 1000.0f + (rand() % 9000);
        if (!pos) {
            offset = -offset;
        }
        pos = !pos;
        UpdateCurrentOffset(offset);
    }
    EXPECT_TRUE(info.endMainLineIndex_ >= info.startMainLineIndex_);
    EXPECT_TRUE(info.startIndex_ <= info.endIndex_);
}

/**
 * @tc.name: GridIrregularLayout::GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, GetOverScrollOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    EXPECT_TRUE(pattern_->irregular_);
    auto& info = pattern_->info_;
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    UpdateCurrentOffset(-200.0f);
    // only items 0~2 are known
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1500.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 200.0f);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1100.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 400.0f);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1100.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 600.0f);
    EXPECT_EQ(info.endIndex_, 8);

    UpdateCurrentOffset(-150.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.startMainLineIndex_, 5);
    EXPECT_EQ(info.endMainLineIndex_, 10);
    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 800.0f);
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateGridItems(12, -2, 100.0f);
    CreateDone();

    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 120.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 202.0f);

    layoutProperty_->UpdateColumnsGap(Dimension { 5.0f });
    FlushUITasks();
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 122.5f);
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 117.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 202.0f);

    layoutProperty_->UpdateRowsGap(Dimension { 3.0f });
    FlushUITasks();
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), 122.5f);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), 206.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange001
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TemplateChange001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 10.0f });
    CreateFixedHeightItems(12, 250.0f);
    CreateDone();
    const auto& info = pattern_->info_;
    // only know 3 items
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 8 * 250.0f + 7 * 10.0f);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(info.GetIrregularOffset(10.0f), 110.0f + 6 * 260.0f);
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 8 * 250.0f + 7 * 10.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 9);
    EXPECT_EQ(info.endIndex_, 11);
    EXPECT_EQ(info.currentOffset_, -110.0f);
    EXPECT_EQ(info.startMainLineIndex_, 4);
    EXPECT_EQ(info.endMainLineIndex_, 5);
    EXPECT_EQ(info.GetIrregularOffset(10.0f), 110.0f + 4 * 260.0f);
    EXPECT_EQ(info.GetIrregularHeight(10.0f), 6 * 250.0f + 5 * 10.0f);

    for (int i = 0; i < 20; ++i) {
        UpdateCurrentOffset(100.0f);
    }
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange002
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TemplateChange002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 910.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 605.0f);
    CreateFixedHeightItems(1, 1825.0f);
    CreateFixedHeightItems(5, 300.0f);
    CreateDone();
    const auto& info = pattern_->info_;
    // only know 1 item
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 27 * 300.0f + 26 * 5.0f);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_TRUE(info.offsetEnd_);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.endIndex_, 8);
    EXPECT_EQ(info.GetIrregularOffset(5.0f), 11 * 300.0f + 10 * 5.0f - GRID_HEIGHT);
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 11 * 300.0f + 10 * 5.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 8);
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.GetIrregularOffset(5.0f), 3 * 305.f - info.currentOffset_);
    EXPECT_EQ(info.GetIrregularHeight(5.0f), 9 * 300.0f + 8 * 5.0f);
}

/**
 * @tc.name: GridIrregularLayout::TemplateChange003
 * @tc.desc: Test changing template
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, TemplateChange003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    CreateFixedHeightItems(1, 450.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 900.0f);
    CreateFixedHeightItems(5, 150.0f);
    CreateDone();
    pattern_->ScrollToIndex(3, false, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 3), -250.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    pattern_->ScrollToIndex(3, true, ScrollAlign::CENTER);
    FlushUITasks();
    pattern_->finalPosition_ = Infinity<float>();
    // finalPosition shouldn't be set because targetPos = current pos
    EXPECT_EQ(pattern_->finalPosition_, Infinity<float>());
}

/**
 * @tc.name: DeleteItem001
 * @tc.desc: Test removing item from end
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, DeleteItem001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 910.0f);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 605.0f);
    CreateFixedHeightItems(1, 1825.0f);
    CreateFixedHeightItems(5, 300.0f);
    ViewAbstract::SetHeight(CalcLength(200.0f));
    CreateDone();
    const auto& info = pattern_->info_;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_TRUE(info.offsetEnd_);
    for (int i = 0; i < 6; ++i) {
        frameNode_->RemoveChildAtIndex(3);
    }
    frameNode_->ChildrenUpdatedFrom(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 4);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.currentOffset_, -405.0f);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_13_AFTER_DELETE);
    EXPECT_TRUE(info.offsetEnd_);

    frameNode_->RemoveChildAtIndex(2);
    frameNode_->ChildrenUpdatedFrom(2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    FlushUITasks();
    EXPECT_EQ(info.startMainLineIndex_, 3);
    EXPECT_EQ(info.endMainLineIndex_, 3);
    EXPECT_EQ(info.currentOffset_, -100.0f);
}

/**
 * @tc.name: GridIrregularLayout::Width001
 * @tc.desc: Test width priority of gridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Width001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo6());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetRowsGap(Dimension { 1.0f });
    CreateGridItems(12, 150.0f, 100.0f);
    CreateDone();

    FlushUITasks();
    for (int32_t i = 0; i < 6; i++) {
        EXPECT_EQ(GetChildSize(frameNode_, i).Width(), 150.0f);
    }
    EXPECT_EQ(GetChildSize(frameNode_, 1).Width(), 150.0f);
}

/**
 * @tc.name: Horizontal001
 * @tc.desc: Test horizontal layout
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Horizontal001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetRowsGap(Dimension { 1.0f });
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedWidthItems(1, 910.0f);
    CreateFixedWidthItems(1, 300.0f);
    CreateFixedWidthItems(20, 605.0f);
    CreateFixedWidthItems(8, 300.0f);
    CreateDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    layoutProperty_->UpdateRowsTemplate("1fr 1fr 1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    // print all content of gridMatrix_
    auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_14_HORIZONTAL);
    for (int i = 0; i < 200; ++i) {
        UpdateCurrentOffset(50.0f);
    }
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: ConstraintChange001
 * @tc.desc: Test width update
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, ConstraintChange001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo14());
    model.SetRowsGap(Dimension { 1.0f });
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedWidthItems(1, 460.0f);
    CreateFixedWidthItems(1, 150.0f);
    CreateFixedWidthItems(20, 305.0f);
    CreateFixedWidthItems(8, 150.0f);
    CreateDone();
    EXPECT_EQ(GetChildSize(frameNode_, 0).Height(), 199.5f);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(200.0f)));
    FlushUITasks();
    EXPECT_EQ(GetChildSize(frameNode_, 0).Height(), 99.5f);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll001
 * @tc.desc: Test overScroll disabled with long item
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, OverScroll001, TestSize.Level1)
{
    // GridItem's own ideal size has higher priority
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo12());
    model.SetColumnsGap(Dimension { 1.0f });
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 900.0f);
    CreateGridItems(4, -2, 150.0f);
    CreateDone();

    FlushUITasks();
    UpdateCurrentOffset(-225.0f);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_12);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, -225.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(info.currentOffset_, -125.0f);
    EXPECT_EQ(info.startIndex_, 0);

    UpdateCurrentOffset(-150.0f);
    EXPECT_EQ(info.currentOffset_, -275.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(info.currentOffset_, -175.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);

    UpdateCurrentOffset(-150.0f);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.currentOffset_, -175.0f);
    EXPECT_FALSE(info.offsetEnd_);
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_EQ(info.GetIrregularHeight(0.0f), 1050.0f);
    EXPECT_EQ(info.GetIrregularOffset(0.0f), 325.0f);
}

/**
 * @tc.name: GridIrregularLayout::OverScroll002
 * @tc.desc: Test overScroll until completely out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, OverScroll002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo13());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateFixedHeightItems(1, 200.0f);
    CreateFixedHeightItems(1, 600.0f);
    CreateGridItems(5, -2, 100.0f);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ViewAbstract::SetHeight(CalcLength(300.0f));
    CreateDone();
    auto& info = pattern_->info_;
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
const decltype(GridLayoutInfo::lineHeightMap_) cmp = { { 0, ITEM_MAIN_SIZE }, { 1, ITEM_MAIN_SIZE },
    { 2, ITEM_MAIN_SIZE }, { 3, ITEM_MAIN_SIZE }, { 6, ITEM_MAIN_SIZE }, { 7, ITEM_MAIN_SIZE }, { 8, ITEM_MAIN_SIZE },
    { 9, ITEM_MAIN_SIZE } };
}
/**
 * @tc.name: GetEndOffset000
 * @tc.desc: Test scrolling past limits
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, GetEndOffset000, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    auto& info = pattern_->info_;
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->ScrollToIndex(targetIndex, false, ScrollAlign::END);
    FlushUITasks();
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, false, align);
    FlushUITasks();
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    info.currentOffset_ -= 500.0f;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-1000.0f);
    EXPECT_TRUE(info.synced_);
    EXPECT_EQ(info.lineHeightMap_, cmp);
    EXPECT_EQ(info.currentOffset_, -200.0f);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    // last item should match up with the bottom again
    EXPECT_EQ(pattern_->GetEndOffset(), GRID_HEIGHT - ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Test deleting items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Delete001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo15());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(5, -2, 50.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(9, -2, 50.0f);
    CreateDone();

    pattern_->ScrollToIndex(9, false, ScrollAlign::CENTER);
    FlushUITasks();
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_15);

    frameNode_->RemoveChildAtIndex(9);
    layoutProperty_->UpdateLayoutOptions(GetOptionDemo16());
    frameNode_->ChildrenUpdatedFrom(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 14);

    pattern_->ScrollToIndex(0, false, ScrollAlign::CENTER);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 13);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);

    frameNode_->ChildrenUpdatedFrom(9);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 13);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_16);
}

/**
 * @tc.name: Add001
 * @tc.desc: Test adding items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Add001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo15());
    model.SetColumnsGap(Dimension { 5.0f });
    CreateFixedHeightItems(1, 150.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(5, -2, 50.0f);
    CreateFixedHeightItems(1, 100.0f);
    CreateGridItems(9, -2, 50.0f);
    CreateDone();

    pattern_->ScrollToIndex(9, false, ScrollAlign::CENTER);
    FlushUITasks();
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 16);

    AddFixedHeightItems(5, 50.0f);
    frameNode_->ChildrenUpdatedFrom(17);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 16);

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_EQ(info.startIndex_, 3);
    EXPECT_EQ(info.endIndex_, 21);
}

/**
 * @tc.name: Stretch001
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Stretch001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        1, // [1 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);

    CreateAdaptChildSizeGridItems(1);
    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(2);
    CreateFixedHeightItems(1, 150);

    CreateDone();
    FlushUITasks();

    auto childRect0 = pattern_->GetItemRect(0);
    EXPECT_EQ(childRect0.Height(), 0);

    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);

    auto childRect3 = pattern_->GetItemRect(3);
    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect3.Height(), childRect4.Height());
}

/**
 * @tc.name: Stretch002
 * @tc.desc: Test Grid AlignItems STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, Stretch002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 2]
        3, // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 2 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetAlignItems(GridItemAlignment::STRETCH);
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);

    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(2);
    CreateFixedHeightItems(1, 150);
    CreateAdaptChildSizeGridItems(1);

    CreateDone();
    FlushUITasks();

    auto childRect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(childRect1.Height(), 0);

    auto childRect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(childRect2.Height(), 0);

    auto childRect4 = pattern_->GetItemRect(4);
    EXPECT_EQ(childRect4.Height(), 0);
}
} // namespace OHOS::Ace::NG
