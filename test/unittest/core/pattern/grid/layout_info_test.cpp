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
#include "core/components_ng/pattern/grid/grid_layout_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class GridLayoutInfoTest : public testing::Test {};

namespace {
const decltype(GridLayoutInfo::gridMatrix_) MATRIX_DEMO_1 = {
    { 0, { { 0, 0 }, { 1, 1 } } },
    { 1, { { 0, 2 }, { 1, -1 } } },
    { 2, { { 0, 3 }, { 1, 4 } } },
    { 3, { { 0, 5 }, { 1, -1 } } },
    { 4, { { 0, 6 }, { 1, 7 } } },
    { 5, { { 0, 8 }, { 1, 9 } } },
    { 6, { { 0, 10 }, { 1, -1 } } },
    { 7, { { 0, 11 } } },
};
}
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
    info.gridMatrix_ = MATRIX_DEMO_1;

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
        { 0, { { 0, 0 }, { 1, -1 }, { 2, -1 } } },
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

    info.gridMatrix_ = MATRIX_DEMO_1;
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

namespace {
const decltype(GridLayoutInfo::gridMatrix_) MATRIX_DEMO_2 = {
    { 0, { { 1, 0 }, { 2, 0 } } },
    { 1, { { 0, 1 }, { 1, 0 }, { 2, 0 } } },
    { 2, { { 0, 2 }, { 1, 3 }, { 2, 4 } } },
    { 3, { { 0, 5 }, { 1, 6 }, { 2, 7 } } },
    { 4, { { 0, 8 }, { 1, 8 }, { 1, 7 } } },
    { 5, { { 0, 8 }, { 1, 8 }, { 2, 9 } } },
    { 6, { { 0, 8 }, { 1, 8 }, { 2, 10 } } },
    { 7, { { 0, 8 }, { 1, 8 }, { 2, 11 } } },
    { 8, { { 0, 8 }, { 1, 8 }, { 2, 12 } } },
    { 9, { { 0, 8 }, { 1, 8 }, { 2, 13 } } },
    { 10, { { 0, 8 }, { 1, 8 }, { 2, 14 } } },
    { 11, { { 0, 15 }, { 1, 16 }, { 2, 17 } } },
    { 12, { { 0, 18 }, { 1, 19 } } },
    { 13, { { 0, 20 }, { 1, 20 }, { 2, 21 } } },
    { 14, { { 0, 20 }, { 1, 20 }, { 2, 22 } } },
    { 15, { { 0, 23 }, { 1, 24 }, { 2, 25 } } },
    { 16, { { 0, 26 }, { 1, 27 }, { 2, 28 } } },
    { 17, { { 0, 29 }, { 1, 30 } } },
    { 18, { { 0, 31 }, { 1, 31 } } },
    { 19, { { 0, 31 }, { 1, 31 } } },
};
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

    info.gridMatrix_ = MATRIX_DEMO_2;
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

    info.gridMatrix_ = MATRIX_DEMO_2;

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

    info.gridMatrix_ = MATRIX_DEMO_2;

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

    info.gridMatrix_ = MATRIX_DEMO_2;

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
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, -1 } } },
        { 2, { { 0, 3 }, { 1, 4 } } },
        { 3, { { 0, 5 }, { 1, -1 } } },
        { 4, { { 0, 6 }, { 1, 7 } } },
        { 5, { { 0, 8 }, { 1, 9 } } },
        { 6, { { 0, 10 }, { 1, -1 } } },
        { 7, { { 0, 11 } } },
    };

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
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, -1 } } },
        { 1, { { 0, 2 }, { 1, 3 }, { 2, 4 } } },
        { 2, { { 0, 5 }, { 1, 6 }, { 2, -1 } } },
        { 3, { { 0, 7 }, { 1, -1 }, { 2, 9 } } },
    };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    EXPECT_EQ(info.FindItemInRange(5), 2);
    EXPECT_EQ(info.FindItemInRange(7), 3);
    EXPECT_EQ(info.FindItemInRange(3), 1);
    EXPECT_EQ(info.FindItemInRange(10), -1);

    info.gridMatrix_.clear();
    EXPECT_EQ(info.FindItemInRange(7), -1);
}

/**
 * @tc.name: UpdateStartIdxToLastItem001
 * @tc.desc: Test GridLayoutInfo::UpdateStartIdxToLastItem
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoTest, UpdateStartIdxToLastItem001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, -1 }, { 2, -1 } } },
        { 1, { { 0, 2 }, { 1, 3 }, { 2, -1 } } },
        { 2, { { 0, 5 }, { 1, -1 }, { 2, -1 } } },
        { 3, { { 0, 7 }, { 1, -1 }, { 2, -1 } } },
    };
    info.UpdateStartIdxToLastItem();
    EXPECT_EQ(info.startIndex_, 7);
    EXPECT_EQ(info.startMainLineIndex_, 3);

    info.gridMatrix_.clear();
    info.UpdateStartIdxToLastItem();
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.startMainLineIndex_, 0);
}
} // namespace OHOS::Ace::NG
