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

#define private public
#include "test/unittest/core/pattern/grid/irregular/irregular_matrices.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class GridLayoutInfoTest : public testing::Test {};

/**
 * @tc.name: GridLayoutInfo::GetContentHeight001
 * @tc.desc: test GetContentHeight while changing endIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentHeight001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 10.0f }, { 2, 5.0f }, { 3, 10.0f }, { 4, 5.0f }, { 5, 5.0f },
        { 6, 10.0f }, { 7, 5.0f } };
    info.gridMatrix_ = MATRIX_DEMO_3;

    GridLayoutOptions option {
        .irregularIndexes = { 2, 5, 10 },
    };

    info.crossCount_ = 2;
    info.childrenCount_ = 12;
    EXPECT_EQ(info.GetContentHeight(option, 12, 1.0f), 62.0f);
    info.childrenCount_ = 11;
    EXPECT_EQ(info.GetContentHeight(option, 11, 1.0f), 56.0f);
    info.childrenCount_ = 10;
    EXPECT_EQ(info.GetContentHeight(option, 10, 1.0f), 45.0f);
    info.childrenCount_ = 6;
    EXPECT_EQ(info.GetContentHeight(option, 6, 1.0f), 33.0f);
    info.childrenCount_ = 5;
    EXPECT_EQ(info.GetContentHeight(option, 5, 1.0f), 22.0f);
    info.childrenCount_ = 2;
    EXPECT_EQ(info.GetContentHeight(option, 2, 1.0f), 5.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetContentHeight002
 * @tc.desc: test GetContentHeight, adapted from test demo
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentHeight002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 2 }, { 2, 3 } } },
        { 2, { { 0, 4 } } },
    };

    GridLayoutOptions option {
        .irregularIndexes = { 0 },
    };

    info.childrenCount_ = 5;
    info.crossCount_ = 3;
    EXPECT_EQ(info.GetContentHeight(option, 5, 1.0f), 17.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetContentHeightBigItem001
 * @tc.desc: test GetContentHeight when hasBigItem_ == true.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentHeightBigItem001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = true;
    info.crossCount_ = 2;
    info.childrenCount_ = 12;

    info.gridMatrix_ = MATRIX_DEMO_3;
    constexpr float trueHeight = 47.0f;
    constexpr float error = trueHeight * 0.1f;

    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f }, { 3, 5.0f }, { 4, 5.0f }, { 5, 5.0f }, { 6, 5.0f },
        { 7, 5.0f } };

    EXPECT_EQ(info.GetContentHeight(1.0f), trueHeight);

    info.lineHeightMap_ = { { 4, 5.0f }, { 5, 5.0f }, { 6, 5.0f }, { 7, 5.0f } }; // total height = 47.0f
    float estimation = info.GetContentHeight(1.0f);
    EXPECT_LE(std::abs(estimation - trueHeight), error);

    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f }, { 3, 5.0f }, { 4, 5.0f }, { 5, 5.0f } };
    estimation = info.GetContentHeight(1.0f);
    EXPECT_LE(std::abs(estimation - trueHeight), error);
}

/**
 * @tc.name: GridLayoutInfo::GetContentHeightBigItem002
 * @tc.desc: test GetContentHeight when hasBigItem_ == true, adapted from test demo.
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentHeightBigItem002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = true;
    info.crossCount_ = 3;
    info.childrenCount_ = 32;

    info.gridMatrix_ = MATRIX_DEMO_4;
    // using mainGap = 5.0f and lineHeight = 100.0f
    constexpr float trueHeight = 2095.0f;
    constexpr float error = trueHeight * 0.1f;

    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f },
        { 6, 100.0f } };

    float estimation = info.GetContentHeight(5.0f);
    EXPECT_LE(std::abs(estimation - trueHeight), error);

    info.lineHeightMap_ = { { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f }, { 6, 100.0f }, { 7, 100.0f }, { 8, 100.0f },
        { 9, 100.0f }, { 10, 100.0f }, { 11, 100.0f }, { 12, 100.0f }, { 13, 100.0f }, { 14, 100.0f }, { 15, 100.0f },
        { 16, 100.0f }, { 17, 100.0f } };
    estimation = info.GetContentHeight(5.0f);
    EXPECT_LE(std::abs(estimation - trueHeight), error);

    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f },
        { 6, 100.0f }, { 7, 100.0f }, { 8, 100.0f }, { 9, 100.0f }, { 10, 100.0f }, { 11, 100.0f }, { 12, 100.0f },
        { 13, 100.0f }, { 14, 100.0f }, { 15, 100.0f }, { 16, 100.0f }, { 17, 100.0f }, { 18, 100.0f },
        { 19, 100.0f } };
    EXPECT_EQ(info.GetContentHeight(5.0f), trueHeight);
}

/**
 * @tc.name: GridLayoutInfo::GetContentOffsetBigItem001
 * @tc.desc: test GetContentOffset when hasBigItem_ == true
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentOffsetBigItem001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = true;
    info.crossCount_ = 3;
    info.childrenCount_ = 32;

    info.gridMatrix_ = MATRIX_DEMO_4;

    info.startIndex_ = 8;
    info.startMainLineIndex_ = 9;
    info.currentOffset_ = -1.0f;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f },
        { 6, 100.0f }, { 7, 100.0f }, { 8, 100.0f }, { 9, 100.0f }, { 10, 100.0f } };

    EXPECT_EQ(info.GetContentOffset(5.0f), 946.0f);

    info.startIndex_ = 26;
    info.startMainLineIndex_ = 16;
    info.currentOffset_ = -7.0f;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f },
        { 6, 100.0f }, { 7, 100.0f }, { 8, 100.0f }, { 9, 100.0f }, { 10, 100.0f }, { 11, 100.0f }, { 12, 100.0f },
        { 13, 100.0f }, { 14, 100.0f }, { 15, 100.0f }, { 16, 100.0f }, { 17, 100.0f }, { 18, 100.0f },
        { 19, 100.0f } };

    EXPECT_EQ(info.GetContentOffset(5.0f), 1687.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetContentOffsetBigItem002
 * @tc.desc: test GetContentOffset estimation when hasBigItem_ == true
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentOffsetBigItem002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = true;
    info.crossCount_ = 3;
    info.childrenCount_ = 32;

    info.gridMatrix_ = MATRIX_DEMO_4;

    info.startIndex_ = 15;
    info.startMainLineIndex_ = 11;
    info.currentOffset_ = -10.0f;
    info.lineHeightMap_ = { { 3, 100.0f }, { 4, 100.0f }, { 5, 100.0f }, { 6, 100.0f }, { 7, 100.0f }, { 8, 100.0f },
        { 9, 100.0f }, { 10, 100.0f }, { 11, 100.0f }, { 12, 100.0f }, { 13, 100.0f }, { 14, 100.0f }, { 15, 100.0f },
        { 16, 100.0f } };
    constexpr float trueOffset = 1165.0f;
    constexpr float error = trueOffset * 0.25f;
    EXPECT_LE(std::abs(info.GetContentOffset(5.0f) - trueOffset), error);
}

/**
 * @tc.name: GridLayoutInfo::GetContentOffsetBigItem003
 * @tc.desc: test GetContentOffset estimation when hasBigItem_ == true
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentOffsetBigItem003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = true;
    info.crossCount_ = 3;
    info.childrenCount_ = 32;

    info.gridMatrix_ = MATRIX_DEMO_4;

    info.startIndex_ = 20;
    info.startMainLineIndex_ = 14;
    info.currentOffset_ = -15.0f;
    // simulating layout after jump
    info.lineHeightMap_ = { { 13, 100.0f }, { 14, 100.0f }, { 15, 100.0f }, { 16, 100.0f } };
    constexpr float trueOffset = 1380.0f;
    constexpr float error = trueOffset * 0.4f;
    EXPECT_LE(std::abs(info.GetContentOffset(5.0f) - trueOffset), error);
}

/**
 * @tc.name: GridLayoutInfo::GetContentOffset001
 * @tc.desc: test GetContentOffset with irregular items
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentOffset001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 10.0f }, { 2, 5.0f }, { 3, 10.0f }, { 4, 5.0f }, { 5, 5.0f },
        { 6, 10.0f }, { 7, 5.0f } };
    info.gridMatrix_ = MATRIX_DEMO_6;

    GridLayoutOptions option {
        .irregularIndexes = { 2, 5, 10 },
    };

    info.crossCount_ = 2;
    info.childrenCount_ = 12;

    info.startIndex_ = 0;
    info.currentOffset_ = -1.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 1.0f);

    info.startIndex_ = 2;
    info.currentOffset_ = -1.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 7.0f);

    info.startIndex_ = 3;
    info.currentOffset_ = -2.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 19.0f);

    info.startIndex_ = 5;
    info.currentOffset_ = -3.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 26.0f);

    info.startIndex_ = 8;
    info.currentOffset_ = 0.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 40.0f);

    info.startIndex_ = 10;
    info.currentOffset_ = -6.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 52.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetContentOffset002
 * @tc.desc: test GetContentOffset with irregular items
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentOffset002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f }, { 3, 5.0f }, { 4, 5.0f }, { 5, 5.0f }, { 6, 5.0f } };
    info.gridMatrix_ = MATRIX_DEMO_12;

    auto option = GetOptionDemo12();

    info.crossCount_ = 3;
    info.childrenCount_ = 7;
    info.hasBigItem_ = true;

    info.startIndex_ = 0;
    info.startMainLineIndex_ = 0;
    info.currentOffset_ = -4.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 4.0f);

    info.startIndex_ = 2;
    info.startMainLineIndex_ = 1;
    info.currentOffset_ = -11.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 17.0f);

    info.currentOffset_ = -20.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 26.0f);

    info.currentOffset_ = -29.0f;
    EXPECT_EQ(info.GetContentOffset(option, 1.0f), 35.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetCurrentOffsetOfRegularGrid001
 * @tc.desc: test GetCurrentOffsetOfRegularGrid with varying lineHeights
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetCurrentOffsetOfRegularGrid001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f }, { 3, 5.0f }, { 4, 10.0f }, { 5, 10.0f },
        { 6, 10.0f } };
    info.startIndex_ = 16;
    info.startMainLineIndex_ = 5;
    info.crossCount_ = 3;

    EXPECT_EQ(info.GetCurrentOffsetOfRegularGrid(1.0f), 35.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetContentHeightRegular001
 * @tc.desc: test GetContentHeight with regular children but different line heights
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetContentHeightRegular001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.hasBigItem_ = false;
    info.lineHeightMap_ = { { 0, 5.0f }, { 1, 5.0f }, { 2, 5.0f }, { 3, 5.0f }, { 4, 10.0f }, { 5, 10.0f },
        { 6, 10.0f } };
    info.startIndex_ = 10;
    info.startMainLineIndex_ = 5;
    info.crossCount_ = 2;

    info.childrenCount_ = 14;
    EXPECT_EQ(info.GetContentHeight(1.0f), 56.0f);

    info.childrenCount_ = 13;
    EXPECT_EQ(info.GetContentHeight(1.0f), 56.0f);
}

/**
 * @tc.name: FindItemInRange001
 * @tc.desc: Test GridLayoutInfo::FindItemInRange
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FindItemInRange001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = MATRIX_DEMO_7;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    auto res = info.FindItemInRange(5);
    EXPECT_EQ(res.first, 2);
    EXPECT_EQ(res.second, 0);

    res = info.FindItemInRange(7);
    EXPECT_EQ(res.first, 3);
    EXPECT_EQ(res.second, 0);

    res = info.FindItemInRange(3);
    EXPECT_EQ(res.first, 1);
    EXPECT_EQ(res.second, 1);

    res = info.FindItemInRange(10);
    EXPECT_EQ(res.first, -1);
    EXPECT_EQ(res.second, -1);

    info.gridMatrix_.clear();
    EXPECT_EQ(info.FindItemInRange(7).first, -1);
}

/**
 * @tc.name: GetTotalHeightOfItemsInView001
 * @tc.desc: Test GridLayoutInfo::GetTotalHeightOfItemsInView
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GetTotalHeightOfItemsInView001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 0.0f }, { 2, 100.0f }, { 3, 200.0f } };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.currentOffset_ = -50.0f;
    EXPECT_EQ(info.GetTotalHeightOfItemsInView(5.0f, false), 415.0f);
    EXPECT_EQ(info.GetTotalHeightOfItemsInView(5.0f, true), 415.0f);
}

namespace {
void CheckEachIndex(const GridLayoutInfo& info, int32_t maxIdx)
{
    for (int i = 0; i <= maxIdx; ++i) {
        auto it = info.FindInMatrix(i);
        EXPECT_NE(it, info.gridMatrix_.end());
        bool foundFlag = false;
        for (auto [_, item] : it->second) {
            if (item == i) {
                foundFlag = true;
                break;
            }
        }
        EXPECT_TRUE(foundFlag);
    }
}
} // namespace

/**
 * @tc.name: FindInMatrix001
 * @tc.desc: Test GridLayoutInfo::FindInMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FindInMatrix, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 1;
    auto nullIt = info.FindInMatrix(1);
    EXPECT_EQ(nullIt, info.gridMatrix_.end());

    info.gridMatrix_ = MATRIX_DEMO_4;

    CheckEachIndex(info, 31);

    nullIt = info.FindInMatrix(32);
    EXPECT_EQ(nullIt, info.gridMatrix_.end());
}

/**
 * @tc.name: FindInMatrix002
 * @tc.desc: Test GridLayoutInfo::FindInMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FindInMatrix002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = MATRIX_DEMO_3;

    CheckEachIndex(info, 11);

    auto nullIt = info.FindInMatrix(12);
    EXPECT_EQ(nullIt, info.gridMatrix_.end());
}

/**
 * @tc.name: FindInMatrix003
 * @tc.desc: Test GridLayoutInfo::FindInMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FindInMatrix003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = MATRIX_DEMO_5;

    CheckEachIndex(info, 10);

    auto nullIt = info.FindInMatrix(11);
    EXPECT_EQ(nullIt, info.gridMatrix_.end());

    info.gridMatrix_.clear();
    EXPECT_EQ(info.FindInMatrix(0), info.gridMatrix_.end());
    EXPECT_EQ(info.FindInMatrix(1), info.gridMatrix_.end());

    info.gridMatrix_ = MATRIX_DEMO_12;
    CheckEachIndex(info, 6);
    EXPECT_EQ(info.FindInMatrix(7), info.gridMatrix_.end());
}

/**
 * @tc.name: ClearMatrixToEnd001
 * @tc.desc: Test GridLayoutInfo::ClearMatrixToEnd
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, ClearMatrixToEnd001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = MATRIX_DEMO_2;

    info.ClearMatrixToEnd(7, 4);
    const decltype(GridLayoutInfo::gridMatrix_) cmp7 = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },
        { 1, { { 0, 0 }, { 1, 0 }, { 2, -1 } } },
        { 2, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },
        { 3, { { 0, 4 }, { 1, -4 }, { 2, -4 } } },
        { 4, { { 0, 5 }, { 1, 6 } } },
        { 5, { { 0, -5 } } },
    };
    EXPECT_EQ(info.gridMatrix_, cmp7);

    info.gridMatrix_ = MATRIX_DEMO_2;
    info.ClearMatrixToEnd(6, 4);
    const decltype(GridLayoutInfo::gridMatrix_) cmp6 = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },
        { 1, { { 0, 0 }, { 1, 0 }, { 2, -1 } } },
        { 2, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },
        { 3, { { 0, 4 }, { 1, -4 }, { 2, -4 } } },
        { 4, { { 0, 5 } } },
        { 5, { { 0, -5 } } },
    };
    EXPECT_EQ(info.gridMatrix_, cmp6);

    info.gridMatrix_ = MATRIX_DEMO_2;
    info.ClearMatrixToEnd(5, 4);
    const decltype(GridLayoutInfo::gridMatrix_) cmp5 = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },
        { 1, { { 0, 0 }, { 1, 0 }, { 2, -1 } } },
        { 2, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },
        { 3, { { 0, 4 }, { 1, -4 }, { 2, -4 } } },
    };
    EXPECT_EQ(info.gridMatrix_, cmp5);

    info.gridMatrix_ = MATRIX_DEMO_2;
    info.ClearMatrixToEnd(2, 2);
    const decltype(GridLayoutInfo::gridMatrix_) cmp2 = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 1 } } },
        { 1, { { 0, 0 }, { 1, 0 }, { 2, -1 } } },
        { 2, { { 2, -1 } } },
    };
    EXPECT_EQ(info.gridMatrix_, cmp2);

    info.gridMatrix_ = MATRIX_DEMO_2;
    info.ClearMatrixToEnd(1, 0);
    const decltype(GridLayoutInfo::gridMatrix_) cmp1 = { { 0, { { 0, 0 }, { 1, 0 } } }, { 1, { { 0, 0 }, { 1, 0 } } } };
    EXPECT_EQ(info.gridMatrix_, cmp1);

    info.gridMatrix_ = MATRIX_DEMO_2;
    info.ClearMatrixToEnd(0, 0);
    const decltype(GridLayoutInfo::gridMatrix_) cmp0 = {};
    EXPECT_EQ(info.gridMatrix_, cmp0);
}

/**
 * @tc.name: OutOfEnd001
 * @tc.desc: Test GridLayoutInfo::OutOfEnd with content end padding (safeArea)
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, OutOfEnd001, TestSize.Level1)
{
    GridLayoutInfo info;

    info.childrenCount_ = 5;
    info.endIndex_ = 4;
    info.currentOffset_ = -50.0f;
    info.totalHeightOfItemsInView_ = 500.0f;
    info.lastMainSize_ = 400.0f;
    EXPECT_FALSE(info.IsOutOfEnd(0.0f, false));

    info.totalHeightOfItemsInView_ = 400.0f;
    EXPECT_TRUE(info.IsOutOfEnd(0.0f, false));

    info.contentEndPadding_ = 200.0f;
    EXPECT_FALSE(info.IsOutOfEnd(0.0f, false));
}

/**
 * @tc.name: OutOfEnd002
 * @tc.desc: Test GridLayoutInfo::OutOfEnd with different precision
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, OutOfEnd002, TestSize.Level1)
{
    GridLayoutInfo info;

    info.childrenCount_ = 5;
    info.endIndex_ = 4;
    info.contentEndPadding_ = 0.0f;
    info.currentOffset_ = -1.666626f;
    info.totalHeightOfItemsInView_ = 401.666626f;
    info.lastMainSize_ = 400.000000f;
    EXPECT_FALSE(info.IsOutOfEnd(0.0f, false));
}

/**
 * @tc.name: FindStartLineInMatrix001
 * @tc.desc: Test GridLayoutInfo::FindStartLineInMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FindStartLineInMatrix001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = MATRIX_DEMO_8;
    auto item = info.FindInMatrix(5);
    item = info.FindStartLineInMatrix(item, 5);
    EXPECT_EQ(item->first, 3);
    item = info.FindInMatrix(2);
    item = info.FindStartLineInMatrix(item, 2);
    EXPECT_EQ(item->first, 1);

    info.gridMatrix_ = MATRIX_DEMO_9;
    item = info.FindInMatrix(0);
    item = info.FindStartLineInMatrix(item, 0);
    EXPECT_EQ(item->first, 0);
    item = info.FindInMatrix(9);
    item = info.FindStartLineInMatrix(item, 9);
    EXPECT_EQ(item->first, 6);

    info.gridMatrix_ = MATRIX_DEMO_12;
    item = info.FindInMatrix(0);
    item = info.FindStartLineInMatrix(item, 0);
    EXPECT_EQ(item->first, 0);
    item = info.FindInMatrix(2);
    item = info.FindStartLineInMatrix(item, 2);
    EXPECT_EQ(item->first, 1);
}

/**
 * @tc.name: GridIrregularLayout::TransformAutoScrollAlign001
 * @tc.desc: Test IrregularLayout::TransformAutoScrollAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, TransformAutoScrollAlign001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 300.0f }, { 2, 30.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = MATRIX_DEMO_8;

    info.jumpIndex_ = 2;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 0;
    info.endIndex_ = 6;
    EXPECT_EQ(info.TransformAutoScrollAlign(2, 2, 500.0f, 5.0f), ScrollAlign::NONE);

    info.jumpIndex_ = 0;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 3;
    info.endIndex_ = 6;
    info.currentOffset_ = -10.0f;
    EXPECT_EQ(info.TransformAutoScrollAlign(0, 1, 100.0f, 5.0f), ScrollAlign::START);

    info.jumpIndex_ = 2;
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 2;
    info.endIndex_ = 2;
    info.currentOffset_ = -25.0f;
    EXPECT_EQ(info.TransformAutoScrollAlign(2, 2, 310.0f, 5.0f), ScrollAlign::NONE);
}

/**
 * @tc.name: GridIrregularLayout::TransformAutoScrollAlign002
 * @tc.desc: Test IrregularLayout::TransformAutoScrollAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, TransformAutoScrollAlign002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 50.0f }, { 1, 300.0f }, { 2, 30.0f }, { 3, 50.0f }, { 4, 80.0f } };
    info.gridMatrix_ = MATRIX_DEMO_8;

    // line 3 now matches with the end of the viewport, should endMainlineIndex_ be updated to 3?
    info.currentOffset_ = -30.0f;
    info.endMainLineIndex_ = 3;
    info.endIndex_ = 5;
    EXPECT_EQ(info.TransformAutoScrollAlign(0, 1, 310.0f, 5.0f), ScrollAlign::START);
    info.currentOffset_ = -31.0f;
    EXPECT_EQ(info.TransformAutoScrollAlign(0, 1, 310.0f, 5.0f), ScrollAlign::START);

    info.jumpIndex_ = 0;
    info.startMainLineIndex_ = 3;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 3;
    info.endIndex_ = 6;
    EXPECT_EQ(info.TransformAutoScrollAlign(0, 1, 100.0f, 5.0f), ScrollAlign::START);

    info.jumpIndex_ = 4;
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 4;
    info.startIndex_ = 2;
    info.endIndex_ = 6;

    info.currentOffset_ = -379.0f;
    EXPECT_EQ(info.TransformAutoScrollAlign(4, 1, 152.0f, 50.0f), ScrollAlign::NONE);

    // emulate init
    info.lineHeightMap_.clear();
    info.gridMatrix_.clear();
    info.jumpIndex_ = 3;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 0;
    info.startIndex_ = 0;
    info.endIndex_ = -1;
    EXPECT_EQ(info.TransformAutoScrollAlign(3, 1, 300.0f, 5.0f), ScrollAlign::END);
}

/**
 * @tc.name: ItemAboveViewport001
 * @tc.desc: Test GridLayoutInfo::ItemAboveViewport
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, ItemAboveViewport001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 500.0f }, { 2, 300.0f } };
    info.crossCount_ = 2;

    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 0;
    info.endIndex_ = 5;

    info.currentOffset_ = 0.0f;
    EXPECT_FALSE(Negative(info.GetItemTopPos(0, 5.0f)));

    info.currentOffset_ = -50.0f;
    EXPECT_TRUE(Negative(info.GetItemTopPos(0, 5.0f)));

    info.currentOffset_ = -200.0f;
    EXPECT_TRUE(Negative(info.GetItemTopPos(0, 5.0f)));
    EXPECT_FALSE(Negative(info.GetItemTopPos(1, 5.0f)));

    // adding gap length
    info.currentOffset_ = -205.0f;
    EXPECT_TRUE(Negative(info.GetItemTopPos(0, 5.0f)));
    EXPECT_FALSE(Negative(info.GetItemTopPos(1, 5.0f)));

    EXPECT_TRUE(Negative(info.GetItemTopPos(1, 0.0f)));

    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 2;
    info.endIndex_ = 3;

    info.currentOffset_ = 0.0f;
    EXPECT_FALSE(Negative(info.GetItemTopPos(1, 5.0f)));

    info.currentOffset_ = -1.0f;
    EXPECT_TRUE(Negative(info.GetItemTopPos(1, 5.0f)));
}


/**
 * @tc.name: ItemBelowViewport001
 * @tc.desc: Test GridLayoutInfo::ItemBelowViewport
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, ItemBelowViewport001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, -1 } } },
    };
    info.lineHeightMap_ = { { 0, 200.0f }, { 1, 500.0f }, { 2, 300.0f } };
    info.crossCount_ = 2;

    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 2;
    info.startIndex_ = 0;
    info.endIndex_ = 4;

    info.currentOffset_ = 0.0f;
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 100.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 700.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 705.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 710.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 1005.0f));
    EXPECT_FALSE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 1010.0f));

    info.currentOffset_ = -50.0f;
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 100.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 700.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 705.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 710.0f));
    EXPECT_TRUE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 955.0f));
    EXPECT_FALSE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 960.0f));
    EXPECT_FALSE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 1005.0f));
    EXPECT_FALSE(GreatNotEqual(info.GetItemBottomPos(1, 2, 5.0f), 1010.0f));
}

/**
 * @tc.name: SkipStartIndexByOffset001
 * @tc.desc: Test GridLayoutInfo::SkipStartIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, SkipStartIndexByOffset001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 2 }, { 2, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 }, { 2, 6 } } },
    };
    info.lineHeightMap_ = { { 0, 162.5f }, { 1, 422.16f }, { 2, 422.16f } };
    info.crossCount_ = 3;
    info.childrenCount_ = 10000;

    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 8874, 8876, 8878, 8975, 8977, 8979, 8981, 9725 };

    info.currentOffset_ = 26915.4f;
    info.prevOffset_ = -164.25f;
    info.currentHeight_ = 1396768.75f;

    info.SkipStartIndexByOffset(option, 2.f);

    EXPECT_EQ(info.startIndex_, 9675);
}

HWTEST_F(GridLayoutInfoTest, SkipStartIndexByOffset002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 1 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
    };
    info.lineHeightMap_ = { { 0, 400.f }, { 1, 400.f }, { 2, 400.f } };
    info.crossCount_ = 3;
    info.childrenCount_ = 20;
    info.lastRegularMainSize_ = 0;

    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

    info.currentOffset_ = -5000.f;
    info.prevOffset_ = -20.f;
    info.currentHeight_ = 420.f;

    info.SkipStartIndexByOffset(option, 0.f);

    EXPECT_EQ(info.startIndex_, 13);
    EXPECT_EQ(info.currentOffset_, -200.f);
    EXPECT_EQ(info.GetContentOffset(option, 0), 5400);
}

HWTEST_F(GridLayoutInfoTest, SkipStartIndexByOffset003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {};
    info.lineHeightMap_ = {};
    info.crossCount_ = 3;
    info.childrenCount_ = 20;
    info.lastRegularMainSize_ = 400;
    info.lastIrregularMainSize_ = 200;

    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 19 };

    info.currentOffset_ = -2000.f;
    info.prevOffset_ = -0.f;
    info.currentHeight_ = 0.f;

    info.SkipStartIndexByOffset(option, 0.f);

    EXPECT_EQ(info.startIndex_, 13);
    EXPECT_EQ(info.currentOffset_, -200.f);
    EXPECT_EQ(info.GetContentOffset(option, 0), 2000);
}

HWTEST_F(GridLayoutInfoTest, SkipStartIndexByOffset004, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 2 }, { 2, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 }, { 2, 6 } } },
    };
    info.lineHeightMap_ = { { 0, 200.f }, { 1, 400.f }, { 2, 400.f } };
    info.crossCount_ = 3;
    info.childrenCount_ = 20;

    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 19 };

    info.currentOffset_ = -2000.f;
    info.prevOffset_ = -0.f;
    info.currentHeight_ = 0.f;

    info.SkipStartIndexByOffset(option, 0.f);

    EXPECT_EQ(info.startIndex_, 13);
    EXPECT_EQ(info.currentOffset_, -200.f);
    EXPECT_EQ(info.GetContentOffset(option, 0), 2000);
}

HWTEST_F(GridLayoutInfoTest, CheckGridMatrix001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 1 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
    };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 1;
    EXPECT_TRUE(info.CheckGridMatrix(2));
}

HWTEST_F(GridLayoutInfoTest, CheckGridMatrix002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 3 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
    };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 3;
    EXPECT_FALSE(info.CheckGridMatrix(2));
}

HWTEST_F(GridLayoutInfoTest, CheckGridMatrix003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 3 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
    };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 1;
    info.startIndex_ = 0;
    info.endIndex_ = 3;
    EXPECT_TRUE(info.CheckGridMatrix(0));
}

HWTEST_F(GridLayoutInfoTest, CheckGridMatrix004, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 5 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 1 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 4 } } },
    };
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 1;
    info.endIndex_ = 4;
    EXPECT_FALSE(info.CheckGridMatrix(2));
}

HWTEST_F(GridLayoutInfoTest, CheckGridMatrix005, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 0 }, { 2, 5 } } },
        { 1, { { 0, 1 }, { 1, 1 }, { 2, 1 } } },
        { 2, { { 0, 2 }, { 1, 2 }, { 2, 2 } } },
        { 3, { { 0, 3 }, { 1, 4 }, { 2, 4 } } },
    };
    info.startMainLineIndex_ = 1;
    info.endMainLineIndex_ = 3;
    info.startIndex_ = 1;
    info.endIndex_ = 4;
    EXPECT_TRUE(info.CheckGridMatrix(0));
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexByStartLineTest001
 * @tc.desc: test UpdateStartIndexByStartLine with empty GridMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, UpdateStartIndexByStartLineTest001, TestSize.Level1)
{
    // gridMatrix is empty
    GridLayoutInfo info;
    info.gridMatrix_ = {};
    info.startMainLineIndex_ = 0;
    info.startIndex_ = 0;

    info.UpdateStartIndexByStartLine();

    // Assert startIndex is not update
    EXPECT_EQ(info.startIndex_, 0);
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexByStartLineTest002
 * @tc.desc: test UpdateStartIndexByStartLine with startMainLineIndex not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, UpdateStartIndexByStartLineTest002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = { { 0, { { 1, 10 }, { 2, 11 } } } };
    info.startMainLineIndex_ = 1;
    info.startIndex_ = 0;

    info.UpdateStartIndexByStartLine();

    // Assert startIndex is not update
    EXPECT_EQ(info.startIndex_, 0);
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexByStartLineTest003
 * @tc.desc: test UpdateStartIndexByStartLine with startLine not empty
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, UpdateStartIndexByStartLineTest003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = { { 0, {} }, { 1, { { 1, 10 }, { 2, 11 } } } };
    info.startMainLineIndex_ = 0;
    info.startIndex_ = 0;

    info.UpdateStartIndexByStartLine();

    // Assert startIndex is not update
    EXPECT_EQ(info.startIndex_, 0);
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexByStartLineTest004
 * @tc.desc: test UpdateStartIndexByStartLine with startLine not empty
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, UpdateStartIndexByStartLineTest004, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = { { 0, { { 1, 10 }, { 2, 11 } } }, { 1, { { 1, 12 }, { 2, 13 } } } };
    info.startMainLineIndex_ = 1;
    info.startIndex_ = 0;

    info.UpdateStartIndexByStartLine();

    // Assert startIndex is updated
    EXPECT_EQ(info.startIndex_, 12);
}

/**
 * @tc.name: GridLayoutInfo::GridMatrixEmpty_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with empty gridMatrix_
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, GridMatrixEmpty_ReturnsFalse, TestSize.Level1)
{
    GridLayoutInfo info;
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::FirstLineNotZero_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with gridMatrix_ not started from 0
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FirstLineNotZero_ReturnsFalse, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_[1] = {{0, 1}};
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::FirstLineIsEmpty_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with first line empty
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FirstLineIsEmpty_ReturnsFalse, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_[0] = {};
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::FirstItemNotZero_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with first item not zero
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, FirstItemNotZero_ReturnsFalse, TestSize.Level1) {
    GridLayoutInfo info;
    info.gridMatrix_[0] = {{0, 1}};
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::LastLineEmpty_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with last line empty
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, LastLineEmpty_ReturnsFalse, TestSize.Level1) {
    GridLayoutInfo info;
    info.gridMatrix_[0] = {{0, 0}};
    info.gridMatrix_[1] = {};
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::LineGapTooLarge_ReturnsFalse
 * @tc.desc: test IsAllItemsMeasured with more than MAX_CUMULATIVE_LINES lines
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, LineGapTooLarge_ReturnsFalse, TestSize.Level1) {
    GridLayoutInfo info;
    info.gridMatrix_[0] = {{0, 0}};
    info.gridMatrix_[101] = {{0, 101}};
    EXPECT_FALSE(info.IsAllItemsMeasured());
}

/**
 * @tc.name: GridLayoutInfo::AllConditionsMet_ReturnsTrue
 * @tc.desc: test IsAllItemsMeasured with alall conditions met
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, AllConditionsMet_ReturnsTrue, TestSize.Level1) {
    GridLayoutInfo info;
    info.gridMatrix_[0] = {{0, 0}};
    info.gridMatrix_[1] = {{0, 5}};
    info.childrenCount_ = 6;
    EXPECT_TRUE(info.IsAllItemsMeasured());
}
} // namespace OHOS::Ace::NG
