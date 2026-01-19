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

#include "irregular_matrices.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"

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
    algorithm->canOverScrollStart_ = false;
    algorithm->canOverScrollEnd_ = false;
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
    EXPECT_EQ(info.lineHeightMap_.size(), 10);
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
    algo->canOverScrollStart_ = true;
    algo->canOverScrollEnd_ = true;
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
    ScrollToIndex(2, false, ScrollAlign::CENTER);
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

    ScrollToIndex(2, true, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->finalPosition_, 417.5f);

    UpdateCurrentOffset(-200.0f);

    ScrollToIndex(1, true, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);

    ScrollToIndex(0, true, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);

    UpdateCurrentOffset(-100.0f);

    ScrollToIndex(6, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->finalPosition_, 215.0f);

    ScrollToIndex(2, true, ScrollAlign::END);
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

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);

    ScrollToIndex(0, true, ScrollAlign::CENTER);
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

    ScrollToIndex(2, false, ScrollAlign::AUTO);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 1);
    EXPECT_EQ(info.endMainLineIndex_, 6);
    EXPECT_EQ(GetChildY(frameNode_, 2), -525.0f);

    // shouldn't move
    ScrollToIndex(2, false, ScrollAlign::AUTO);
    EXPECT_EQ(GetChildY(frameNode_, 2), -525.0f);

    ScrollToIndex(2, false, ScrollAlign::START);
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.0f);

    ScrollToIndex(2, false, ScrollAlign::AUTO);
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
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
 * @tc.name: ReloadWhenOverScrollFromEnd
 * @tc.desc: Test jumping to bottom edge
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularLayoutTest, ReloadWhenOverScrollFromEnd, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(10);
    GridLayoutOptions option;
    option.irregularIndexes = { 0 };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 0) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(1, 300.0f);
    CreateFixedHeightItems(2, 150.0f);
    CreateDone();

    // mock the scroll up
    GestureEvent info;
    info.SetMainVelocity(-200.f);
    info.SetMainDelta(-100.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();

    std::map<int32_t, std::map<int32_t, int32_t>>  matrix = {
        { 0, { { 0, 0 }, { 1, 0 } } },
        { 1, { { 0, 0 }, { 1, 0 } } },
        { 2, { { 0, 1 }, { 1, 2 } } },
    };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);
    // start animation
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();

    frameNode_->childrenUpdatedFrom_ = 0;
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    layoutProperty_->OnLayoutOptionsUpdate(option);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);
}
} // namespace OHOS::Ace::NG
