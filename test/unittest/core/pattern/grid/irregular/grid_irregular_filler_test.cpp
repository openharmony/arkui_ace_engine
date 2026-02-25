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
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"

namespace OHOS::Ace::NG {
class GridIrregularFillerTest : public GridTestNg {};

/**
 * @tc.name: IrregularFiller::AdvancePos001
 * @tc.desc: Test IrregularFiller::AdvancePos
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, AdvancePos001, TestSize.Level1)
{
    // empty matrix
    GridLayoutInfo info;
    info.crossCount_ = 2;
    GridIrregularFiller filler(&info, nullptr);
    EXPECT_FALSE(filler.AdvancePos());

    filler.posX_ = 1;
    filler.posY_ = 0;
    EXPECT_FALSE(filler.AdvancePos());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 1);

    // init matrix
    info.gridMatrix_[0][0] = 1;
    info.gridMatrix_[0][1] = -1;
    info.gridMatrix_[1][0] = -1;
    EXPECT_FALSE(filler.AdvancePos());
    EXPECT_EQ(filler.posX_, 1);
    EXPECT_EQ(filler.posY_, 1);

    // reset pos and make [1][1] available
    filler.posX_ = 0;
    filler.posY_ = 1;
    info.gridMatrix_[1][1] = -1;
    EXPECT_TRUE(filler.AdvancePos());
}

/**
 * @tc.name: IrregularFiller::FindNextItem001
 * @tc.desc: Test IrregularFiller::FindNextItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FindNextItem001, TestSize.Level1)
{
    // empty matrix
    GridLayoutInfo info;
    info.crossCount_ = 2;
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_FALSE(filler.FindNextItem(0));
    }

    info.gridMatrix_[0][0] = 1;
    info.gridMatrix_[0][1] = 2;
    info.gridMatrix_[1][0] = 3;
    info.gridMatrix_[1][1] = -1;
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_TRUE(filler.FindNextItem(1));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(2));
        EXPECT_EQ(filler.posX_, 1);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(3));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 1);

        EXPECT_FALSE(filler.FindNextItem(4));
    }

    info.gridMatrix_[0][1] = -1;
    info.gridMatrix_[1][0] = 2;
    info.gridMatrix_[1].erase(1);
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_TRUE(filler.FindNextItem(1));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 0);

        EXPECT_TRUE(filler.FindNextItem(2));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 1);

        EXPECT_FALSE(filler.FindNextItem(3));
        EXPECT_EQ(filler.posX_, 1);
        EXPECT_EQ(filler.posY_, 1);
    }
}

/**
 * @tc.name: IrregularFiller::FindNextItem002
 * @tc.desc: Test IrregularFiller::FindNextItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FindNextItem002, TestSize.Level1)
{
    // 0 | 1 | 2 | 3 | 4
    // 0 | 5 | 2 | 3 | 4
    // 7 | 5 | 6 | 6 | 8
    // 7 | 9 | 6 | 6 | 8
    GridLayoutInfo info;
    info.crossCount_ = 5;

    info.gridMatrix_[0][0] = 0;
    info.gridMatrix_[0][1] = 1;
    info.gridMatrix_[0][2] = 2;
    info.gridMatrix_[0][3] = 3;
    info.gridMatrix_[0][4] = 4;

    info.gridMatrix_[1][0] = 0;
    info.gridMatrix_[1][1] = 5;
    info.gridMatrix_[1][2] = -2;
    info.gridMatrix_[1][3] = -3;
    info.gridMatrix_[1][4] = -4;

    info.gridMatrix_[2][0] = 7;
    info.gridMatrix_[2][1] = -5;
    info.gridMatrix_[2][2] = 6;
    info.gridMatrix_[2][3] = -6;
    info.gridMatrix_[2][4] = 8;

    info.gridMatrix_[3][0] = -7;
    info.gridMatrix_[3][1] = 9;
    info.gridMatrix_[3][2] = -6;
    info.gridMatrix_[3][3] = -6;
    info.gridMatrix_[3][4] = -8;
    {
        GridIrregularFiller filler(&info, nullptr);

        EXPECT_TRUE(filler.FindNextItem(0));

        EXPECT_TRUE(filler.FindNextItem(1));

        EXPECT_TRUE(filler.FindNextItem(2));

        EXPECT_TRUE(filler.FindNextItem(3));

        EXPECT_TRUE(filler.FindNextItem(4));

        EXPECT_TRUE(filler.FindNextItem(5));
        EXPECT_EQ(filler.posX_, 1);
        EXPECT_EQ(filler.posY_, 1);

        EXPECT_TRUE(filler.FindNextItem(6));
        EXPECT_EQ(filler.posX_, 2);
        EXPECT_EQ(filler.posY_, 2);

        // Find item index at position before last item
        EXPECT_TRUE(filler.FindNextItem(7));
        EXPECT_EQ(filler.posX_, 0);
        EXPECT_EQ(filler.posY_, 2);

        EXPECT_TRUE(filler.FindNextItem(8));
        EXPECT_EQ(filler.posX_, 4);
        EXPECT_EQ(filler.posY_, 2);

        EXPECT_TRUE(filler.FindNextItem(9));
    }
}

/**
 * @tc.name: IrregularFiller::UpdateLength001
 * @tc.desc: Test IrregularFiller::UpdateLength
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, UpdateLength001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_[0] = 50.0f;
    info.lineHeightMap_[1] = 30.0f;

    GridIrregularFiller filler(&info, nullptr);
    float len = -5.0f;
    int32_t row = 0;
    EXPECT_TRUE(filler.UpdateLength(len, 50.0f, row, 2, 5.0f));
    EXPECT_EQ(len, 50.0f);

    len = -5.0f;
    row = 0;
    EXPECT_FALSE(filler.UpdateLength(len, 100.0f, row, 2, 5.0f));
    EXPECT_EQ(len, 85.0f);

    info.lineHeightMap_[2] = 50.0f;
    row = 2;
    EXPECT_TRUE(filler.UpdateLength(len, 100.0f, row, 3, 10.0f));
    EXPECT_EQ(len, 85.0f + 50.0f + 10.0f);

    len = 85.0f;
    row = 2;
    EXPECT_FALSE(filler.UpdateLength(len, 200.0f, row, 3, 10.0f));
    EXPECT_EQ(len, 85.0f + 50.0f + 10.0f);
}

/**
 * @tc.name: IrregularFiller::FillOne001
 * @tc.desc: Test IrregularFiller::FillOne
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillOne001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0, // [2 x 1]
        1, // [1 x 2]
        2  // [2 x 1]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 1) {
            return { .rows = 2, .columns = 1 };
        }
        return { .rows = 1, .columns = 2 };
    };

    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(option);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    filler.FillOne(0);
    EXPECT_EQ(info.gridMatrix_.at(0).at(0), 0);
    EXPECT_EQ(info.gridMatrix_.at(0).at(1), 0);
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 0);

    filler.FillOne(1);
    EXPECT_EQ(info.gridMatrix_.at(1).at(0), 1);
    EXPECT_EQ(info.gridMatrix_.at(1).size(), 1);
    EXPECT_EQ(info.gridMatrix_.at(2).at(0), -1);
    EXPECT_EQ(info.gridMatrix_.at(2).size(), 1);
    EXPECT_TRUE(info.gridMatrix_.find(3) == info.gridMatrix_.end());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 1);

    filler.FillOne(2);
    EXPECT_EQ(info.gridMatrix_.at(3).at(0), 2);
    EXPECT_EQ(info.gridMatrix_.at(3).at(1), -2);
    EXPECT_TRUE(info.gridMatrix_.find(4) == info.gridMatrix_.end());
    EXPECT_EQ(filler.posX_, 0);
    EXPECT_EQ(filler.posY_, 3);
}

/**
 * @tc.name: IrregularFiller::FillOne002
 * @tc.desc: Test IrregularFiller::FillOne with 3 columns
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillOne002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo10());
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    for (int i = 0; i < 8; ++i) {
        filler.FillOne(i);
    }

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_10);
}

/**
 * @tc.name: IrregularFiller::MeasureItem001
 * @tc.desc: Test IrregularFiller::MeasureItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, MeasureItem001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize { return { .columns = 1, .rows = 2 }; };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(10);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 4;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    info.endIndex_ = 0;

    GridIrregularFiller::FillParameters params {
        .crossLens = { 50.0f, 50.0f, 100.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f
    };
    filler.MeasureItem(params, 0, 0, 0, false);

    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    auto child = frameNode_->GetChildByIndex(0);
    ASSERT_TRUE(child);
    auto constraint = *child->GetGeometryNode()->GetParentLayoutConstraint();
    EXPECT_EQ(constraint.maxSize.Width(), 50.0f);
    EXPECT_EQ(*constraint.parentIdealSize.Width(), 50.0f);
    EXPECT_EQ(constraint.percentReference.Width(), 50.0f);
}

/**
 * @tc.name: IrregularFiller::MeasureItem002
 * @tc.desc: Test IrregularFiller::MeasureItem
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, MeasureItem002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = {
        0,
    };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(10);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 4;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    info.endIndex_ = 0;
    filler.posY_ = 0;

    GridIrregularFiller::FillParameters params {
        .crossLens = { 50.0f, 50.0f, 100.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f
    };
    filler.MeasureItem(params, 0, 0, 0, false);

    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) == info.lineHeightMap_.end());
    auto child = frameNode_->GetChildByIndex(0);
    ASSERT_TRUE(child);
    auto constraint = *child->GetGeometryNode()->GetParentLayoutConstraint();
    EXPECT_EQ(constraint.maxSize.Width(), 315.0f);
    EXPECT_EQ(*constraint.parentIdealSize.Width(), 315.0f);
    EXPECT_EQ(constraint.percentReference.Width(), 315.0f);
}

/**
 * @tc.name: IrregularFiller::Fill001
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Fill001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo9());
    CreateGridItems(10, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 10;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    auto res = filler.Fill({ .crossLens = { 50.0f, 50.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1000.0f, 0);

    EXPECT_EQ(res.length, 6.0f);

    EXPECT_EQ(res.endIndex, 9);
    EXPECT_EQ(res.endMainLineIndex, 6);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_9);
}

/**
 * @tc.name: IrregularFiller::Fill002
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Fill002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo11());
    CreateGridItems(10, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 10;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    auto res = filler.Fill({ .crossLens = { 50.0f, 50.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1000.0f, 0);

    EXPECT_EQ(res.length, 6.0f);

    EXPECT_EQ(res.endIndex, 9);
    EXPECT_EQ(res.endMainLineIndex, 6);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);

    // call Fill on an already filled matrix
    res = filler.Fill({ .crossLens = { 50.0f, 50.0f, 100.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1000.0f, 0);

    EXPECT_EQ(res.length, 6.0f);

    EXPECT_EQ(res.endIndex, 9);
    EXPECT_EQ(res.endMainLineIndex, 6);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_11);
}

/**
 * @tc.name: IrregularFiller::Fill003
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Fill003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetWidth(CalcLength(480.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    CreateGridItems(11, 120.0f, 200.0f);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.childrenCount_ = 11;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    auto res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 600.0f, 0);

    EXPECT_EQ(res.length, 602.0f);

    EXPECT_EQ(res.endIndex, 3);
    EXPECT_EQ(res.endMainLineIndex, 5);

    res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1000.0f, 2);

    EXPECT_EQ(res.length, 1004.0f);

    EXPECT_EQ(res.endIndex, 8);
    EXPECT_EQ(res.endMainLineIndex, 10);

    res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1000.0f, 7);

    EXPECT_EQ(res.length, 803.0f);

    EXPECT_EQ(res.endIndex, 10);
    EXPECT_EQ(res.endMainLineIndex, 11);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);
}

/**
 * @tc.name: IrregularFiller::Fill004
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Fill004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetWidth(CalcLength(480.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetLayoutOptions(GetOptionDemo2());
    CreateGridItems(8, 120.0f, 200.0f);
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    auto res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 300.0f, 0);

    EXPECT_EQ(res.length, 401.0f);

    EXPECT_EQ(res.endIndex, 3);
    EXPECT_EQ(res.endMainLineIndex, 2);

    // call Fill on an already filled matrix
    res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 500.0f, 2);

    EXPECT_EQ(res.length, 602.0f);

    EXPECT_EQ(res.endIndex, 7);
    EXPECT_EQ(res.endMainLineIndex, 4);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_2);
}

/**
 * @tc.name: IrregularFiller::Fill005
 * @tc.desc: Test IrregularFiller::Fill
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, Fill005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetWidth(CalcLength(480.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetLayoutOptions(GetOptionDemo10());
    CreateGridItems(8, 120.0f, 200.0f);
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;
    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    auto res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1500.0f, 0);

    EXPECT_EQ(res.length, 1104.5f);

    EXPECT_EQ(res.endIndex, 7);
    EXPECT_EQ(res.endMainLineIndex, 5);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_10);

    // call Fill on an already filled matrix
    res = filler.Fill({ .crossLens = { 50.0f, 50.0f }, .crossGap = 5.0f, .mainGap = 1.0f }, 1500.0f, 3);

    EXPECT_EQ(res.length, 501.5f);

    EXPECT_EQ(res.endIndex, 7);
    EXPECT_EQ(res.endMainLineIndex, 5);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_10);
}

/**
 * @tc.name: GridIrregularLayout::FillMatrixOnly001
 * @tc.desc: Test GridIrregularFiller::FillMatrixOnly
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixOnly001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    CreateFixedItems(7);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    // partially filled
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } }, // 0 | 0 | 1
    };
    info.childrenCount_ = 7;

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    EXPECT_EQ(filler.FillMatrixOnly(6), 4);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_8);
}

/**
 * @tc.name: GridIrregularLayout::MeasureBackward001
 * @tc.desc: Test GridIrregularFiller::MeasureBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, MeasureBackward001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = MATRIX_DEMO_8;
    info.crossCount_ = 3;

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    CreateGridItems(10, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    float len = filler.MeasureBackward({ { 50.0f, 50.0f, 50.0f }, 5.0f, 5.0f }, 1000.0f, 5);

    EXPECT_EQ(len, 30.0f);
    EXPECT_EQ(info.lineHeightMap_.size(), 6);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixByLine001
 * @tc.desc: Test GridIrregularFiller::FillMatrixByLine
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixByLine001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo2());
    CreateFixedItems(8);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 8;
    info.gridMatrix_ = MATRIX_DEMO_2;

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    int32_t idx = filler.FillMatrixByLine(0, 3);
    EXPECT_EQ(idx, 4);

    idx = filler.FillMatrixByLine(3, 10);
    EXPECT_EQ(idx, 7);

    info.gridMatrix_.clear();
    idx = filler.FillMatrixByLine(0, 3);
    EXPECT_EQ(idx, 4);
    idx = filler.FillMatrixByLine(2, 5);
    EXPECT_EQ(idx, 7);
    idx = filler.FillMatrixByLine(5, 5);
    EXPECT_EQ(idx, 7);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_2);

    info.gridMatrix_.clear();
    idx = filler.FillMatrixByLine(0, 10);
    EXPECT_EQ(idx, 7);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_2);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixByLine002
 * @tc.desc: Test GridIrregularFiller::FillMatrixByLine
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixByLine002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    CreateFixedItems(11);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.childrenCount_ = 11;
    info.gridMatrix_ = MATRIX_DEMO_5;

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    int32_t idx = filler.FillMatrixByLine(2, 4);
    EXPECT_EQ(idx, 4);

    idx = filler.FillMatrixByLine(3, 10);
    EXPECT_EQ(idx, 9);

    idx = filler.FillMatrixByLine(4, 8);
    EXPECT_EQ(idx, 7);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);

    info.gridMatrix_.clear();
    idx = filler.FillMatrixByLine(5, 13);
    EXPECT_EQ(idx, 10);
    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);
}

/**
 * @tc.name: GridIrregularFiller::FillToTarget
 * @tc.desc: Test GridIrregularFiller::FillToTarget with illegal startLine
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillToTarget001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    CreateFixedItems(11);
    CreateDone();

    GridIrregularFiller::FillParameters params {
        .crossLens = { 120.0f, 120.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.childrenCount_ = 11;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    filler.FillToTarget(params, 5, -1);
    auto iter = info.gridMatrix_.begin();
    EXPECT_NE(iter, info.gridMatrix_.end());
    EXPECT_EQ(iter->first, 0);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixFromStartIndex001
 * @tc.desc: Test GridIrregularFiller::FillMatrixFromStartIndex with targetIdx out of bounds
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixFromStartIndex001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo5());
    CreateFixedItems(11);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.childrenCount_ = 11;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    filler.FillMatrixFromStartIndex(0, 0, 20);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_5);
    EXPECT_EQ(filler.posY_, 11);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixFromStartIndex002
 * @tc.desc: Test GridIrregularFiller::FillMatrixFromStartIndex with partially filled matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixFromStartIndex002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(GetOptionDemo8());
    CreateFixedItems(7);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 7;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },
    };

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));
    filler.FillMatrixFromStartIndex(0, 1, 6);

    EXPECT_EQ(info.gridMatrix_, MATRIX_DEMO_8);
    EXPECT_EQ(filler.posY_, 4);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixFromStartIndexWithMeasure001
 * @tc.desc: Test GridIrregularFiller::FillMatrixFromStartIndexWithMeasure with multi-row target item
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixFromStartIndexWithMeasure001, TestSize.Level1)
{
    // Grid config: 3 columns
    // item0: (row0, col0) 1x1
    // item1: (row0, col1) 1x1
    // item2: (row0, col2) 1x1
    // item3: (row1, col0) 2x2  [occupies row1-2, col0-1]
    // item4: (row1, col2) 1x1
    // item5: (row2, col2) 1x1  <- key test point
    GridLayoutOptions option;
    option.irregularIndexes = {
        3, // [2 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 3) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(7); // Create 7 items (0-6)
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 7;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // Call FillMatrixFromStartIndexWithMeasure, starting from index 0, target is index 3
    float height = filler.FillMatrixFromStartIndexWithMeasure(params, 0, 0, 3);

    // Verify gridMatrix_ contains all necessary rows
    EXPECT_TRUE(info.gridMatrix_.find(0) != info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(1) != info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(2) != info.gridMatrix_.end());

    // Verify lineHeightMap_ contains all rows occupied by item3 (row1 and row2)
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(2) != info.lineHeightMap_.end());

    // Verify returned height equals expected value (100 + 100 = 200)
    EXPECT_EQ(height, 200.0f);
}

/**
 * @tc.name: GridIrregularFiller::FillMatrixFromStartIndexWithMeasure002
 * @tc.desc: Test GridIrregularFiller::FillMatrixFromStartIndexWithMeasure with multiple multi-row items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillMatrixFromStartIndexWithMeasure002, TestSize.Level1)
{
    // Grid config: 4 columns
    // item3: (row1, col0) 2x2  [occupies row1-2, col0-1]
    // item4: (row1, col2) 2x2  [occupies row1-2, col2-3]
    // item5: (row3, col0) 1x1
    GridLayoutOptions option;
    option.irregularIndexes = {
        3, // [2 x 2]
        4, // [2 x 2]
    };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 3 || index == 4) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(6); // Create 6 items (0-5)
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 4;
    info.childrenCount_ = 6;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // Call FillMatrixFromStartIndexWithMeasure, starting from index 0, target is index 3
    float height = filler.FillMatrixFromStartIndexWithMeasure(params, 0, 0, 3);

    // Verify gridMatrix_ contains all necessary rows
    EXPECT_TRUE(info.gridMatrix_.find(0) != info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(1) != info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(2) != info.gridMatrix_.end());

    // Verify lineHeightMap_ contains all rows occupied by item3 (row1 and row2)
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(2) != info.lineHeightMap_.end());

    // Verify returned height equals expected value (50 + 50 = 100)
    EXPECT_EQ(height, 100.0f);
}

/**
 * @tc.name: GridIrregularFiller::FillAndMeasureUntilIndex001
 * @tc.desc: Test GridIrregularFiller::FillAndMeasureUntilIndex with regular items
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillAndMeasureUntilIndex001, TestSize.Level1)
{
    // Grid config: 3 columns
    // item0-5: All regular 1x1 items
    GridLayoutOptions option;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(6); // Create 6 items (0-5)
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 6;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // Test: Fill and measure from index 0 to index 3
    int32_t targetLine = -1;
    int32_t lastIdx = filler.FillAndMeasureUntilIndex(params, 0, 3, targetLine);

    // Verify return value
    EXPECT_EQ(lastIdx, 3);

    // Verify targetLine was recorded
    EXPECT_EQ(targetLine, 1); // Index 3 should be at row 1 (0-based: row0=[0,1,2], row1=[3,4,5])

    // Verify lineHeightMap_ contains measured rows
    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());

    // Verify correct number of rows measured
    EXPECT_EQ(info.lineHeightMap_.size(), 2); // row 0 and row 1
}

/**
 * @tc.name: GridIrregularFiller::FillAndMeasureUntilIndex002
 * @tc.desc: Test GridIrregularFiller::FillAndMeasureUntilIndex with multi-row item
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillAndMeasureUntilIndex002, TestSize.Level1)
{
    // Grid config: 3 columns
    // item3: 2x2 item (occupies row1-2, col0-1)
    GridLayoutOptions option;
    option.irregularIndexes = { 3 };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 3) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(7);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 7;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // Test: Fill and measure from index 0 to index 3 (the 2x2 item)
    int32_t targetLine = -1;
    int32_t lastIdx = filler.FillAndMeasureUntilIndex(params, 0, 3, targetLine);

    // Verify return value
    EXPECT_EQ(lastIdx, 3);

    // Verify targetLine was recorded (item3 at row1)
    EXPECT_EQ(targetLine, 1);

    // Verify lineHeightMap_ contains measured rows
    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(2) != info.lineHeightMap_.end());

    // Verify correct number of rows measured
    EXPECT_EQ(info.lineHeightMap_.size(), 3);
}

/**
 * @tc.name: GridIrregularFiller::FillAndMeasureUntilLine001
 * @tc.desc: Test GridIrregularFiller::FillAndMeasureUntilLine to complete rows
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillAndMeasureUntilLine001, TestSize.Level1)
{
    // Grid config: 3 columns
    // item3: 2x2 item (occupies row1-2, col0-1)
    // After measuring up to index 3, we need to measure item5 at row2,col2
    GridLayoutOptions option;
    option.irregularIndexes = { 3 };
    auto onGetIrregularSizeByIndex = [](int32_t index) -> GridItemSize {
        if (index == 3) {
            return { .rows = 2, .columns = 2 };
        }
        return { .rows = 1, .columns = 1 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(7);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 7;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // First, fill and measure up to index 3
    int32_t targetLine = -1;
    filler.FillAndMeasureUntilIndex(params, 0, 3, targetLine);

    // Then, continue filling until row 3 (which means completing rows 0-2)
    int32_t lastIdx = filler.FillAndMeasureUntilLine(params, 4, 3);

    // Verify we filled up to index 6 (all items 0-6)
    EXPECT_EQ(lastIdx, 6);

    // Verify posY_ reached target row
    EXPECT_EQ(filler.posY_, 3);

    // Verify all rows 0-3 have heights
    EXPECT_TRUE(info.lineHeightMap_.find(0) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(1) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(2) != info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(3) != info.lineHeightMap_.end());

    // Verify correct number of rows measured
    EXPECT_EQ(info.lineHeightMap_.size(), 4);
}

/**
 * @tc.name: GridIrregularFiller::FillAndMeasureUntilLine002
 * @tc.desc: Test GridIrregularFiller::FillAndMeasureUntilLine with boundary conditions
 * @tc.type: FUNC
 */
HWTEST_F(GridIrregularFillerTest, FillAndMeasureUntilLine002, TestSize.Level1)
{
    // Grid config: 3 columns, all regular items
    GridLayoutOptions option;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    CreateFixedItems(6);
    CreateDone();

    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.childrenCount_ = 6;
    info.gridMatrix_ = {};

    GridIrregularFiller filler(&info, AceType::RawPtr(frameNode_));

    GridIrregularFiller::FillParameters params {
        .crossLens = { 100.0f, 100.0f, 100.0f }, .crossGap = 0.0f, .mainGap = 0.0f
    };

    // Test: Fill from index 0 until reaching row 2
    int32_t lastIdx = filler.FillAndMeasureUntilLine(params, 0, 2);

    // Verify we filled all 6 items (row0: 0,1,2; row1: 3,4,5)
    EXPECT_EQ(lastIdx, 5);

    // Verify posY_ is at row 1 (didn't reach row 2)
    EXPECT_EQ(filler.posY_, 1);

    // Verify correct number of rows measured (row 0 and row 1)
    EXPECT_EQ(info.lineHeightMap_.size(), 2);
}
} // namespace OHOS::Ace::NG