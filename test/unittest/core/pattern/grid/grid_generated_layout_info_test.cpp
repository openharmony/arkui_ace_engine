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

#include "gtest/gtest.h"

#define private public
#include "test/unittest/core/pattern/grid/irregular/irregular_matrices.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class GridLayoutInfoGeneratedTest : public testing::Test {
public:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: GridLayoutInfo::GetItemIndexByPosition001
 * @tc.desc: Test GetItemIndexByPosition returns position when not found in map
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetItemIndexByPosition001, TestSize.Level1)
{
    GridLayoutInfo info;
    // Empty map
    EXPECT_EQ(info.GetItemIndexByPosition(5), 5);
    EXPECT_EQ(info.GetItemIndexByPosition(0), 0);
    EXPECT_EQ(info.GetItemIndexByPosition(-1), -1);
}

/**
 * @tc.name: GridLayoutInfo::GetItemIndexByPosition002
 * @tc.desc: Test GetItemIndexByPosition returns mapped value
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetItemIndexByPosition002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.positionItemIndexMap_[0] = 10;
    info.positionItemIndexMap_[5] = 15;
    info.positionItemIndexMap_[10] = 20;

    EXPECT_EQ(info.GetItemIndexByPosition(0), 10);
    EXPECT_EQ(info.GetItemIndexByPosition(5), 15);
    EXPECT_EQ(info.GetItemIndexByPosition(10), 20);
    // Not in map
    EXPECT_EQ(info.GetItemIndexByPosition(3), 3);
}

/**
 * @tc.name: GridLayoutInfo::GetPositionByItemIndex001
 * @tc.desc: Test GetPositionByItemIndex with empty map
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetPositionByItemIndex001, TestSize.Level1)
{
    GridLayoutInfo info;
    // Empty map - returns itemIndex as position
    EXPECT_EQ(info.GetPositionByItemIndex(5), 5);
    EXPECT_EQ(info.GetPositionByItemIndex(0), 0);
    EXPECT_EQ(info.GetPositionByItemIndex(-1), -1);
}

/**
 * @tc.name: GridLayoutInfo::GetPositionByItemIndex002
 * @tc.desc: Test GetPositionByItemIndex finds item in map
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetPositionByItemIndex002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.positionItemIndexMap_[0] = 10;
    info.positionItemIndexMap_[5] = 15;
    info.positionItemIndexMap_[10] = 20;

    EXPECT_EQ(info.GetPositionByItemIndex(10), 0);
    EXPECT_EQ(info.GetPositionByItemIndex(15), 5);
    EXPECT_EQ(info.GetPositionByItemIndex(20), 10);
    // Not in map
    EXPECT_EQ(info.GetPositionByItemIndex(25), 25);
}

/**
 * @tc.name: GridLayoutInfo::GetOriginalIndex001
 * @tc.desc: Test GetOriginalIndex returns currentMovingItemPosition
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetOriginalIndex001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.currentMovingItemPosition_ = -1;
    EXPECT_EQ(info.GetOriginalIndex(), -1);

    info.currentMovingItemPosition_ = 5;
    EXPECT_EQ(info.GetOriginalIndex(), 5);

    info.currentMovingItemPosition_ = 10;
    EXPECT_EQ(info.GetOriginalIndex(), 10);
}

/**
 * @tc.name: GridLayoutInfo::ClearDragState001
 * @tc.desc: Test ClearDragState resets all drag-related state
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearDragState001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.positionItemIndexMap_[0] = 10;
    info.positionItemIndexMap_[5] = 15;
    info.currentMovingItemPosition_ = 7;
    info.currentRect_.SetRect(10.0f, 20.0f, 30.0f, 40.0f);

    info.ClearDragState();

    EXPECT_TRUE(info.positionItemIndexMap_.empty());
    EXPECT_EQ(info.currentMovingItemPosition_, -1);
    EXPECT_EQ(info.currentRect_.Left(), 0.0f);
    EXPECT_EQ(info.currentRect_.Top(), 0.0f);
    EXPECT_EQ(info.currentRect_.Width(), 0.0f);
    EXPECT_EQ(info.currentRect_.Height(), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::MoveItemsBack001
 * @tc.desc: Test MoveItemsBack with crossCount == 0 returns early
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, MoveItemsBack001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 0;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.startIndex_ = 0;
    info.startMainLineIndex_ = 0;

    // Should return early due to crossCount_ == 0
    info.MoveItemsBack(0, 2, 5);

    // GridMatrix should be unchanged
    EXPECT_EQ(info.gridMatrix_[0][0], 0);
    EXPECT_EQ(info.gridMatrix_[0][1], 1);
}

/**
 * @tc.name: GridLayoutInfo::MoveItemsBack002
 * @tc.desc: Test MoveItemsBack moves items backward correctly
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, MoveItemsBack002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.startIndex_ = 0;
    info.startMainLineIndex_ = 0;
    info.childrenCount_ = 6;

    info.MoveItemsBack(1, 3, 10);

    EXPECT_EQ(info.currentMovingItemPosition_, 1);
    EXPECT_EQ(info.gridMatrix_[0][1], 10);
    EXPECT_EQ(info.gridMatrix_[1][0], 1);
    EXPECT_EQ(info.gridMatrix_[1][1], 2);
    EXPECT_EQ(info.positionItemIndexMap_[1], 10);
    EXPECT_EQ(info.positionItemIndexMap_[3], 2);
}

/**
 * @tc.name: GridLayoutInfo::MoveItemsForward001
 * @tc.desc: Test MoveItemsForward with crossCount == 0 returns early
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, MoveItemsForward001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 0;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.startIndex_ = 0;
    info.startMainLineIndex_ = 0;

    // Should return early due to crossCount_ == 0
    info.MoveItemsForward(0, 2, 5);

    // GridMatrix should be unchanged
    EXPECT_EQ(info.gridMatrix_[0][0], 0);
    EXPECT_EQ(info.gridMatrix_[0][1], 1);
}

/**
 * @tc.name: GridLayoutInfo::MoveItemsForward002
 * @tc.desc: Test MoveItemsForward moves items forward correctly
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, MoveItemsForward002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.startIndex_ = 0;
    info.startMainLineIndex_ = 0;
    info.childrenCount_ = 6;

    info.MoveItemsForward(1, 3, 10);

    EXPECT_EQ(info.currentMovingItemPosition_, 3);
    EXPECT_EQ(info.gridMatrix_[0][1], 2);
    EXPECT_EQ(info.gridMatrix_[1][0], 3);
    EXPECT_EQ(info.gridMatrix_[1][1], 10);
    EXPECT_EQ(info.gridMatrix_[2][0], 4);
    EXPECT_EQ(info.positionItemIndexMap_[1], 2);
    EXPECT_EQ(info.positionItemIndexMap_[2], 3);
    EXPECT_EQ(info.positionItemIndexMap_[3], 10);
}

/**
 * @tc.name: GridLayoutInfo::UpdateEndLine001
 * @tc.desc: Test UpdateEndLine when mainSize >= lastMainSize
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateEndLine001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.lastMainSize_ = 300.0f;

    // mainSize >= lastMainSize_, should return early
    info.UpdateEndLine(400.0f, 0.0f);

    EXPECT_EQ(info.endMainLineIndex_, 3);
}

/**
 * @tc.name: GridLayoutInfo::UpdateEndLine002
 * @tc.desc: Test UpdateEndLine reduces endMainLineIndex when size decreases
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateEndLine002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = 3;
    info.lastMainSize_ = 500.0f;

    info.UpdateEndLine(250.0f, 10.0f);

    // Should reduce endMainLineIndex_ to fit the new size
    EXPECT_LE(info.endMainLineIndex_, 3);
}

/**
 * @tc.name: GridLayoutInfo::IsOutOfStart001
 * @tc.desc: Test IsOutOfStart with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, IsOutOfStart001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.reachStart_ = false;
    info.currentOffset_ = 10.0f;
    info.contentStartOffset_ = 5.0f;
    EXPECT_FALSE(info.IsOutOfStart());

    info.reachStart_ = true;
    info.currentOffset_ = 10.0f;
    info.contentStartOffset_ = 5.0f;
    EXPECT_TRUE(info.IsOutOfStart());

    info.reachStart_ = true;
    info.currentOffset_ = 3.0f;
    info.contentStartOffset_ = 5.0f;
    EXPECT_FALSE(info.IsOutOfStart());
}

/**
 * @tc.name: GridLayoutInfo::IsOutOfEndIrregular001
 * @tc.desc: Test IsOutOfEnd with irregular mode and negative distance
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, IsOutOfEndIrregular001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.reachStart_ = false;
    info.currentOffset_ = 10.0f;
    info.totalHeightOfItemsInView_ = 100.0f;
    info.lastMainSize_ = 200.0f;
    info.lineHeightMap_ = { { 0, 100.0f } };
    info.endIndex_ = 0;
    info.childrenCount_ = 1;
    info.endMainLineIndex_ = 0;

    // Negative distance means out of end
    EXPECT_TRUE(info.IsOutOfEnd(10.0f, true));
}

/**
 * @tc.name: GridLayoutInfo::GetIrregularOffset001
 * @tc.desc: Test GetIrregularOffset with empty lineHeightMap
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetIrregularOffset001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_.clear();
    info.childrenCount_ = 10;

    EXPECT_EQ(info.GetIrregularOffset(5.0f), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetIrregularOffset002
 * @tc.desc: Test GetIrregularOffset with zero childrenCount
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetIrregularOffset002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.childrenCount_ = 0;

    EXPECT_EQ(info.GetIrregularOffset(5.0f), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetIrregularHeight001
 * @tc.desc: Test GetIrregularHeight with empty lineHeightMap
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetIrregularHeight001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_.clear();
    info.childrenCount_ = 10;

    EXPECT_EQ(info.GetIrregularHeight(5.0f), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetIrregularHeight002
 * @tc.desc: Test GetIrregularHeight with zero childrenCount
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetIrregularHeight002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.childrenCount_ = 0;

    EXPECT_EQ(info.GetIrregularHeight(5.0f), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::SkipRegularLines001
 * @tc.desc: Test SkipRegularLines with non-positive lineHeight
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, SkipRegularLines001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.currentOffset_ = 100.0f;
    info.startIndex_ = 10;
    info.crossCount_ = 2;
    int32_t initialStartIndex = info.startIndex_;

    info.SkipRegularLines(true, -5.0f, 0.0f);

    // Should return early due to non-positive lineHeight
    EXPECT_EQ(info.startIndex_, initialStartIndex);
}

/**
 * @tc.name: GridLayoutInfo::SkipRegularLines002
 * @tc.desc: Test SkipRegularLines in forward direction
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, SkipRegularLines002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.currentOffset_ = 1000.0f;
    info.startIndex_ = 10;
    info.crossCount_ = 2;
    info.childrenCount_ = 20;

    info.SkipRegularLines(true, 10.0f, 50.0f);

    // Should skip lines forward (reset startIndex to 0 in forward case)
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.currentOffset_, 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::SkipRegularLines003
 * @tc.desc: Test SkipRegularLines backward
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, SkipRegularLines003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.currentOffset_ = 1000.0f;
    info.startIndex_ = 15;
    info.crossCount_ = 2;
    info.childrenCount_ = 20;

    info.SkipRegularLines(false, 10.0f, 50.0f);

    // Should skip lines backward
    EXPECT_LT(info.startIndex_, 15);
    EXPECT_NE(info.currentOffset_, 1000.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetCurrentLineHeight001
 * @tc.desc: Test GetCurrentLineHeight returns height from current line
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetCurrentLineHeight001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 200.0f }, { 2, 150.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.startMainLineIndex_ = 1;

    EXPECT_EQ(info.GetCurrentLineHeight(), 200.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetCurrentLineHeight002
 * @tc.desc: Test GetCurrentLineHeight returns first available line when current line not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetCurrentLineHeight002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 5, 100.0f }, { 10, 200.0f } };
    info.gridMatrix_ = {
        { 5, { { 0, 0 }, { 1, 1 } } },
    };
    info.startMainLineIndex_ = 3;

    // Should return first available line height
    EXPECT_EQ(info.GetCurrentLineHeight(), 100.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetCurrentLineHeight003
 * @tc.desc: Test GetCurrentLineHeight returns 0.0f when no valid line found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetCurrentLineHeight003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_.clear();
    info.gridMatrix_.clear();
    info.startMainLineIndex_ = 0;

    EXPECT_EQ(info.GetCurrentLineHeight(), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetLineIndexByIndex001
 * @tc.desc: Test GetLineIndexByIndex finds item in matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetLineIndexByIndex001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };

    int32_t targetLineIndex = -1;
    EXPECT_TRUE(info.GetLineIndexByIndex(3, targetLineIndex));
    EXPECT_EQ(targetLineIndex, 1);

    EXPECT_TRUE(info.GetLineIndexByIndex(5, targetLineIndex));
    EXPECT_EQ(targetLineIndex, 2);
}

/**
 * @tc.name: GridLayoutInfo::GetLineIndexByIndex002
 * @tc.desc: Test GetLineIndexByIndex returns false when item not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetLineIndexByIndex002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };

    int32_t targetLineIndex = -1;
    EXPECT_FALSE(info.GetLineIndexByIndex(10, targetLineIndex));
    EXPECT_EQ(targetLineIndex, -1);

    EXPECT_FALSE(info.GetLineIndexByIndex(-1, targetLineIndex));
}

/**
 * @tc.name: GridLayoutInfo::GetTotalHeightFromZeroIndex001
 * @tc.desc: Test GetTotalHeightFromZeroIndex calculates cumulative height
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetTotalHeightFromZeroIndex001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = {
        { 0, 100.0f },
        { 1, 150.0f },
        { 2, 200.0f },
        { 3, 250.0f },
    };

    // Should sum heights of lines before targetLineIndex
    EXPECT_EQ(info.GetTotalHeightFromZeroIndex(2, 10.0f), 270.0f); // 100+10+150+10
    EXPECT_EQ(info.GetTotalHeightFromZeroIndex(3, 10.0f), 480.0f); // 100+10+150+10+200+10
}

/**
 * @tc.name: GridLayoutInfo::GetTotalHeightFromZeroIndex002
 * @tc.desc: Test GetTotalHeightFromZeroIndex with targetLineIndex <= first line
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetTotalHeightFromZeroIndex002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = {
        { 5, 100.0f },
        { 6, 150.0f },
    };

    EXPECT_EQ(info.GetTotalHeightFromZeroIndex(5, 10.0f), 0.0f);
    EXPECT_EQ(info.GetTotalHeightFromZeroIndex(3, 10.0f), 0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetAnimatePosIrregular001
 * @tc.desc: Test GetAnimatePosIrregular with LAST_ITEM target
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetAnimatePosIrregular001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.childrenCount_ = 10;
    info.lastMainSize_ = 500.0f;
    info.contentStartOffset_ = 0.0f;
    info.contentEndOffset_ = 0.0f;

    float result = info.GetAnimatePosIrregular(-1 /* LAST_ITEM */, 1, ScrollAlign::START, 10.0f);

    // Should use last item (index 9 for childrenCount_ = 10)
    // Since item not in matrix, returns special value
    EXPECT_EQ(result, -1.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetAnimatePosIrregular002
 * @tc.desc: Test GetAnimatePosIrregular with START alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetAnimatePosIrregular002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.lastMainSize_ = 500.0f;
    info.contentStartOffset_ = 0.0f;

    float result = info.GetAnimatePosIrregular(2, 1, ScrollAlign::START, 10.0f);

    // Should return position to scroll item 2 to start
    EXPECT_FLOAT_EQ(result, 110.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetAnimatePosIrregular003
 * @tc.desc: Test GetAnimatePosIrregular with CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetAnimatePosIrregular003, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.lastMainSize_ = 500.0f;
    info.contentStartOffset_ = 0.0f;

    float result = info.GetAnimatePosIrregular(2, 1, ScrollAlign::CENTER, 10.0f);

    // Should center the item (1 line height = 100, centered in 500)
    // GetTotalHeightFromZeroIndex(0, 10) = 0 (line 0 is not < 0)
    // offset = 0, center = 0
    // res = 0 + 0 - 250 = -250
    // max(-250, -0) = -0
    EXPECT_FLOAT_EQ(result, -0.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetAnimatePosIrregular004
 * @tc.desc: Test GetAnimatePosIrregular with END alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetAnimatePosIrregular004, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    info.lastMainSize_ = 500.0f;
    info.contentStartOffset_ = 0.0f;
    info.contentEndOffset_ = 0.0f;

    float result = info.GetAnimatePosIrregular(2, 1, ScrollAlign::END, 10.0f);

    // Should align item end to viewport end
    // GetTotalHeightFromZeroIndex(2, 10) = 100+10+100+10 = 220
    // res = 220 - 10 - 500 + 0 = -290
    float expected = -290.0f;
    EXPECT_FLOAT_EQ(result, std::max(expected, -0.0f));
}

/**
 * @tc.name: GridLayoutInfo::GetAnimatePosIrregular005
 * @tc.desc: Test GetAnimatePosIrregular when item not in matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetAnimatePosIrregular005, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f } };
    info.contentStartOffset_ = 0.0f;

    float result = info.GetAnimatePosIrregular(10, 1, ScrollAlign::START, 10.0f);

    // Item not in matrix, returns special value
    EXPECT_EQ(result, -1.0f - info.contentStartOffset_);
}

/**
 * @tc.name: GridLayoutInfo::GetItemPos001
 * @tc.desc: Test GetItemPos returns position of item in matrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetItemPos001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 3;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
    };

    auto pos = info.GetItemPos(3);
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 1);

    pos = info.GetItemPos(5);
    EXPECT_EQ(pos.first, 2);
    EXPECT_EQ(pos.second, 1);
}

/**
 * @tc.name: GridLayoutInfo::GetItemPos002
 * @tc.desc: Test GetItemPos returns -1,-1 when item not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetItemPos002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
    };

    auto pos = info.GetItemPos(10);
    EXPECT_EQ(pos.first, -1);
    EXPECT_EQ(pos.second, -1);
}

/**
 * @tc.name: GridLayoutInfo::FindEndIdx001
 * @tc.desc: Test FindEndIdx returns empty result when line not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindEndIdx001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
    };

    auto result = info.FindEndIdx(5);
    EXPECT_EQ(result.itemIdx, -1);
    EXPECT_EQ(result.y, -1);
    EXPECT_EQ(result.x, -1);
}

/**
 * @tc.name: GridLayoutInfo::FindEndIdx002
 * @tc.desc: Test FindEndIdx searches backwards from endLine
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindEndIdx002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, -5 } } },
    };

    auto result = info.FindEndIdx(2);
    EXPECT_EQ(result.itemIdx, 4);
    EXPECT_EQ(result.y, 2);
    EXPECT_EQ(result.x, 0);
}

/**
 * @tc.name: GridLayoutInfo::ClearMapsToEnd001
 * @tc.desc: Test ClearMapsToEnd removes lines from index onwards
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearMapsToEnd001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
        { 3, { { 0, 6 }, { 1, 7 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };

    info.ClearMapsToEnd(2);

    // Lines 2 and 3 should be removed
    EXPECT_EQ(info.gridMatrix_.size(), 2);
    EXPECT_TRUE(info.gridMatrix_.find(2) == info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(3) == info.gridMatrix_.end());
    EXPECT_EQ(info.lineHeightMap_.size(), 2);
}

/**
 * @tc.name: GridLayoutInfo::ClearMapsFromStart001
 * @tc.desc: Test ClearMapsFromStart removes lines before index
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearMapsFromStart001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
        { 3, { { 0, 6 }, { 1, 7 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };

    info.ClearMapsFromStart(2);

    // Lines 0 and 1 should be removed
    EXPECT_EQ(info.gridMatrix_.size(), 2);
    EXPECT_TRUE(info.gridMatrix_.find(0) == info.gridMatrix_.end());
    EXPECT_TRUE(info.gridMatrix_.find(1) == info.gridMatrix_.end());
    EXPECT_EQ(info.lineHeightMap_.size(), 2);
}

/**
 * @tc.name: GridLayoutInfo::ClearHeightsToEnd001
 * @tc.desc: Test ClearHeightsToEnd removes heights from index onwards
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearHeightsToEnd001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };

    info.ClearHeightsToEnd(2);

    EXPECT_EQ(info.lineHeightMap_.size(), 2);
    EXPECT_TRUE(info.lineHeightMap_.find(2) == info.lineHeightMap_.end());
    EXPECT_TRUE(info.lineHeightMap_.find(3) == info.lineHeightMap_.end());
}

/**
 * @tc.name: GridLayoutInfo::ClearMatrixToEnd001
 * @tc.desc: Test ClearMatrixToEnd removes cells with index >= idx
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearMatrixToEnd001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 } } },
        { 1, { { 0, 3 }, { 1, 4 }, { 2, 5 } } },
        { 2, { { 0, 6 }, { 1, 7 }, { 2, 8 } } },
    };

    info.ClearMatrixToEnd(5, 1);

    // Items >= 5 should be removed
    EXPECT_EQ(info.gridMatrix_[0].size(), 3);
    EXPECT_EQ(info.gridMatrix_[1].size(), 2);
    EXPECT_TRUE(info.gridMatrix_[2].empty());
}

/**
 * @tc.name: GridLayoutInfo::GetDistanceToBottom001
 * @tc.desc: Test GetDistanceToBottom with empty lineHeightMap
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetDistanceToBottom001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_.clear();
    info.endIndex_ = 5;
    info.childrenCount_ = 10;
    info.currentOffset_ = 10.0f;
    info.totalHeightOfItemsInView_ = 100.0f;
    info.contentEndOffset_ = 0.0f;

    // Empty map returns infinity
    EXPECT_EQ(info.GetDistanceToBottom(200.0f, 100.0f, 10.0f), LayoutInfinity<float>());
}

/**
 * @tc.name: GridLayoutInfo::GetDistanceToBottom002
 * @tc.desc: Test GetDistanceToBottom when endIndex < last child
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetDistanceToBottom002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f } };
    info.endIndex_ = 5;
    info.childrenCount_ = 10;
    info.endMainLineIndex_ = 0;
    info.currentOffset_ = 10.0f;
    info.totalHeightOfItemsInView_ = 100.0f;
    info.contentEndOffset_ = 0.0f;

    // Not at end, returns infinity
    EXPECT_EQ(info.GetDistanceToBottom(200.0f, 100.0f, 10.0f), LayoutInfinity<float>());
}

/**
 * @tc.name: GridLayoutInfo::ClearHeightsFromMatrix001
 * @tc.desc: Test ClearHeightsFromMatrix removes heights from index
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, ClearHeightsFromMatrix001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };

    info.ClearHeightsFromMatrix(1);

    // Should keep lines 0 and 1 but remove lines >= 2
    EXPECT_EQ(info.lineHeightMap_.size(), 2);
    EXPECT_NE(info.lineHeightMap_.find(0), info.lineHeightMap_.end());
    EXPECT_NE(info.lineHeightMap_.find(1), info.lineHeightMap_.end());
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexForExtralOffset001
 * @tc.desc: Test UpdateStartIndexForExtralOffset with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateStartIndexForExtralOffset001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.startMainLineIndex_ = 0;
    info.currentOffset_ = -50.0f;
    info.startIndex_ = 0;

    info.UpdateStartIndexForExtralOffset(10.0f, 200.0f);

    // With currentOffset_ = -50, lineHeightMap_[0] = 100, mainGap = 10
    // currentEndOffset = -50 + 100 + 10 = 60
    // !Positive(60) is false, so startMainLineIndex_ remains 0
    EXPECT_EQ(info.startMainLineIndex_, 0);
}

/**
 * @tc.name: GridLayoutInfo::UpdateStartIndexForExtralOffset002
 * @tc.desc: Test UpdateStartIndexForExtralOffset with positive offset
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateStartIndexForExtralOffset002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    info.startMainLineIndex_ = 1;
    info.currentOffset_ = 50.0f;
    info.startIndex_ = 2;

    info.UpdateStartIndexForExtralOffset(10.0f, 200.0f);

    // With currentOffset_ = 50, preLineHeight = 100, mainGap = 10
    // preItemCurrentOffset = 50 - 100 - 10 = -60
    // Positive(-60) is false, so while loop doesn't execute
    // startMainLineIndex_ remains 1
    EXPECT_EQ(info.startMainLineIndex_, 1);
}

/**
 * @tc.name: GridLayoutInfo::PrepareJumpToBottom001
 * @tc.desc: Test PrepareJumpToBottom sets jumpIndex for scrolling
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, PrepareJumpToBottom001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };

    info.PrepareJumpToBottom();

    EXPECT_EQ(info.jumpIndex_, 4);
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
}

/**
 * @tc.name: GridLayoutInfo::PrepareJumpToBottom002
 * @tc.desc: Test PrepareJumpToBottom with empty gridMatrix
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, PrepareJumpToBottom002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_.clear();

    info.PrepareJumpToBottom();

    EXPECT_EQ(info.jumpIndex_, -1); // LAST_ITEM
    EXPECT_EQ(info.scrollAlign_, ScrollAlign::END);
}

/**
 * @tc.name: GridLayoutInfo::UpdateDefaultCachedCount001
 * @tc.desc: Test UpdateDefaultCachedCount with crossCount == 0
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateDefaultCachedCount001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 0;
    info.endIndex_ = 5;
    info.startIndex_ = 0;
    info.defCachedCount_ = 5;

    info.UpdateDefaultCachedCount();

    // Should return early, count unchanged
    EXPECT_EQ(info.defCachedCount_, 5);
}

/**
 * @tc.name: GridLayoutInfo::UpdateDefaultCachedCount002
 * @tc.desc: Test UpdateDefaultCachedCount calculates cache count
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, UpdateDefaultCachedCount002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.crossCount_ = 2;
    info.endIndex_ = 5;
    info.startIndex_ = 0;
    info.defCachedCount_ = 2;

    info.UpdateDefaultCachedCount();

    // (6/2) = 3 lines, should update cached count
    EXPECT_GE(info.defCachedCount_, 2);
}

/**
 * @tc.name: GridLayoutInfo::FindInMatrixByMainIndexAndCrossIndex001
 * @tc.desc: Test FindInMatrixByMainIndexAndCrossIndex returns item
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindInMatrixByMainIndexAndCrossIndex001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 10 }, { 1, 11 }, { 2, 12 } } },
        { 1, { { 0, 20 }, { 1, 21 }, { 2, 22 } } },
    };

    EXPECT_EQ(info.FindInMatrixByMainIndexAndCrossIndex(0, 1), 11);
    EXPECT_EQ(info.FindInMatrixByMainIndexAndCrossIndex(1, 2), 22);
}

/**
 * @tc.name: GridLayoutInfo::FindInMatrixByMainIndexAndCrossIndex002
 * @tc.desc: Test FindInMatrixByMainIndexAndCrossIndex returns -1 when not found
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindInMatrixByMainIndexAndCrossIndex002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.gridMatrix_ = {
        { 0, { { 0, 10 }, { 1, 11 } } },
    };

    EXPECT_EQ(info.FindInMatrixByMainIndexAndCrossIndex(5, 0), -1);
    EXPECT_EQ(info.FindInMatrixByMainIndexAndCrossIndex(0, 5), -1);
}

/**
 * @tc.name: GridLayoutInfo::HeightSumSmaller001
 * @tc.desc: Test HeightSumSmaller with total height less than other
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, HeightSumSmaller001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };

    // Total = 100+10+100+10+100+10 = 330 < 500
    EXPECT_TRUE(info.HeightSumSmaller(500.0f, 10.0f));
}

/**
 * @tc.name: GridLayoutInfo::HeightSumSmaller002
 * @tc.desc: Test HeightSumSmaller with total height greater than other
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, HeightSumSmaller002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };

    // Total = 330 > 300, should return false at some point
    EXPECT_FALSE(info.HeightSumSmaller(200.0f, 10.0f));
}

/**
 * @tc.name: GridLayoutInfo::FindItemCenter001
 * @tc.desc: Test FindItemCenter finds center line and offset
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindItemCenter001, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };

    auto [centerLine, offset] = info.FindItemCenter(0, 2, 10.0f);

    // GetHeightInRange(0, 2, 10) = 100+10+100+10 = 220
    // halfLen = (220-10)/2 = 105
    // Line 0: len+100+10 = 110, 110 < 105 is false, exit loop
    // Returns {0, 105-0} = {0, 105}
    EXPECT_EQ(centerLine, 0);
    EXPECT_FLOAT_EQ(offset, 105.0f);
}

/**
 * @tc.name: GridLayoutInfo::FindItemCenter002
 * @tc.desc: Test FindItemCenter with odd line count
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, FindItemCenter002, TestSize.Level1)
{
    GridLayoutInfo info;
    info.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f }, { 3, 100.0f } };

    auto [centerLine, offset] = info.FindItemCenter(0, 3, 10.0f);

    // GetHeightInRange(0, 3, 10) = 100+10+100+10+100+10 = 330
    // halfLen = (330-10)/2 = 160
    // Loop: line 0: len=110, LessNotEqual(110, 160)=true, continue
    //       line 1: len=220, LessNotEqual(220, 160)=false, exit
    // Return {1, 160-110} = {1, 50}
    EXPECT_EQ(centerLine, 1);
    EXPECT_FLOAT_EQ(offset, 50.0f);
}

/**
 * @tc.name: GridLayoutInfo::GetGridItemAnimatePos001
 * @tc.desc: Test GetGridItemAnimatePos with START alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetGridItemAnimatePos001, TestSize.Level1)
{
    GridLayoutInfo currentInfo;
    GridLayoutInfo targetInfo;
    targetInfo.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    targetInfo.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    currentInfo.startMainLineIndex_ = 0;
    currentInfo.endMainLineIndex_ = 2;
    currentInfo.contentStartOffset_ = 0.0f;
    currentInfo.lastMainSize_ = 500.0f;

    float targetPos = 0.0f;
    bool result = targetInfo.GetGridItemAnimatePos(currentInfo, 2, ScrollAlign::START, 10.0f, targetPos);

    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(targetPos, 110.0f); // Line 0 height + gap = 100+10
}

/**
 * @tc.name: GridLayoutInfo::GetGridItemAnimatePos002
 * @tc.desc: Test GetGridItemAnimatePos with CENTER alignment
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetGridItemAnimatePos002, TestSize.Level1)
{
    GridLayoutInfo currentInfo;
    GridLayoutInfo targetInfo;
    targetInfo.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f }, { 2, 100.0f } };
    targetInfo.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
        { 2, { { 0, 4 }, { 1, 5 } } },
    };
    currentInfo.startMainLineIndex_ = 0;
    currentInfo.endMainLineIndex_ = 2;
    currentInfo.lastMainSize_ = 500.0f;

    float targetPos = 0.0f;
    bool result = targetInfo.GetGridItemAnimatePos(currentInfo, 2, ScrollAlign::CENTER, 10.0f, targetPos);

    EXPECT_TRUE(result);
    // Should center item at line 1 (100 height, centered in 500)
    // targetPos = GetTotalHeightFromZeroIndex(1, 10) = 100+10 = 110
    // targetPos -= ((500 - 100) * 0.5) = 110 - 200 = -90
    float expected = -90.0f;
    EXPECT_FLOAT_EQ(targetPos, expected);
}

/**
 * @tc.name: GridLayoutInfo::GetGridItemAnimatePos003
 * @tc.desc: Test GetGridItemAnimatePos returns false when target not in range
 * @tc.type: FUNC
 */
HWTEST_F(GridLayoutInfoGeneratedTest, GetGridItemAnimatePos003, TestSize.Level1)
{
    GridLayoutInfo currentInfo;
    GridLayoutInfo targetInfo;
    targetInfo.lineHeightMap_ = { { 0, 100.0f }, { 1, 100.0f } };
    targetInfo.gridMatrix_ = {
        { 0, { { 0, 0 }, { 1, 1 } } },
        { 1, { { 0, 2 }, { 1, 3 } } },
    };

    float targetPos = 0.0f;
    bool result = targetInfo.GetGridItemAnimatePos(currentInfo, 10, ScrollAlign::START, 10.0f, targetPos);

    EXPECT_FALSE(result);
}

} // namespace OHOS::Ace::NG
