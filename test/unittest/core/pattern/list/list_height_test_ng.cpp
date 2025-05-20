/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_height_offset_calculator.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListHeightTestNg : public TestNG {
public:
};

/**
 * @tc.name: CalculateListItemGroup001
 * @tc.desc: Test ListHeightOffsetCalculator CalculateListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, CalculateListItemGroup001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.currentIndex_ = 2;
    listHeightOffsetCalculator.estimateHeight_ = 2.0f;
    listHeightOffsetCalculator.spaceWidth_ = 2.0f;
    listHeightOffsetCalculator.startIndex_ = 3;
    listHeightOffsetCalculator.currLane_ = 1;
    listHeightOffsetCalculator.syncPosMap_ = true;
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->posMap_[2] = { 2.0f, 6.0f, true };
    listHeightOffsetCalculator.posMap_ = listPositionMap;
    listHeightOffsetCalculator.CalculateListItemGroup(listItemGroupPattern);
    EXPECT_EQ(listHeightOffsetCalculator.currLane_, 0);
    EXPECT_EQ(listHeightOffsetCalculator.posMap_->posMap_[2].mainPos, 4.0f);
}

/**
 * @tc.name: CalculateListItemGroup002
 * @tc.desc: Test ListHeightOffsetCalculator CalculateListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, CalculateListItemGroup002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.currentIndex_ = 2;
    listHeightOffsetCalculator.estimateHeight_ = 2.0f;
    listHeightOffsetCalculator.spaceWidth_ = 2.0f;
    listHeightOffsetCalculator.startIndex_ = 3;
    listHeightOffsetCalculator.currLane_ = 1;
    listHeightOffsetCalculator.syncPosMap_ = true;
    listHeightOffsetCalculator.posMap_ = nullptr;
    listHeightOffsetCalculator.CalculateListItemGroup(listItemGroupPattern);
    EXPECT_EQ(listHeightOffsetCalculator.currLane_, 0);
    EXPECT_EQ(listHeightOffsetCalculator.currentIndex_, 3);
}

/**
 * @tc.name: CalculateListItemGroup003
 * @tc.desc: Test ListHeightOffsetCalculator CalculateListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, CalculateListItemGroup003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.currentIndex_ = 2;
    listHeightOffsetCalculator.estimateHeight_ = 2.0f;
    listHeightOffsetCalculator.spaceWidth_ = 2.0f;
    listHeightOffsetCalculator.startIndex_ = 3;
    listHeightOffsetCalculator.currLane_ = 1;
    listHeightOffsetCalculator.syncPosMap_ = false;
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    listPositionMap->posMap_[2] = { 2.0f, 6.0f, true };
    listHeightOffsetCalculator.posMap_ = listPositionMap;
    listHeightOffsetCalculator.CalculateListItemGroup(listItemGroupPattern);
    EXPECT_EQ(listHeightOffsetCalculator.currentIndex_, 3);
    EXPECT_EQ(listHeightOffsetCalculator.posMap_->posMap_[2].mainPos, 2.0f);
}

/**
 * @tc.name: CalculateListItemGroup004
 * @tc.desc: Test ListHeightOffsetCalculator CalculateListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, CalculateListItemGroup004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.currentIndex_ = 2;
    listHeightOffsetCalculator.estimateHeight_ = 2.0f;
    listHeightOffsetCalculator.spaceWidth_ = 2.0f;
    listHeightOffsetCalculator.startIndex_ = 3;
    listHeightOffsetCalculator.currLane_ = -1;
    listHeightOffsetCalculator.currRowHeight_ = 2.0f;
    listHeightOffsetCalculator.syncPosMap_ = false;
    listHeightOffsetCalculator.posMap_ = nullptr;
    listHeightOffsetCalculator.CalculateListItemGroup(listItemGroupPattern);
    EXPECT_NE(listHeightOffsetCalculator.currLane_, 0);
    EXPECT_NE(listHeightOffsetCalculator.currRowHeight_, 0.0f);
}

/**
 * @tc.name: CalculatePosMapNode001
 * @tc.desc: Test ListHeightOffsetCalculator CalculatePosMapNode
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, CalculatePosMapNode001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.currentIndex_ = 2;
    listHeightOffsetCalculator.currLane_ = 0;
    listHeightOffsetCalculator.estimateHeight_ = 2.0f;
    listHeightOffsetCalculator.spaceWidth_ = 2.0f;
    listHeightOffsetCalculator.startIndex_ = 2;
    listHeightOffsetCalculator.currRowHeight_ = 2.0f;
    listHeightOffsetCalculator.targetPos_ = std::make_pair(1.0f, 2.0f);
    listHeightOffsetCalculator.posMap_ = nullptr;
    listHeightOffsetCalculator.CalculatePosMapNode();
    EXPECT_EQ(listHeightOffsetCalculator.estimateOffset_, 3.0f);
    EXPECT_NE(listHeightOffsetCalculator.totalItemCount_, 1.0f);
}

/**
 * @tc.name: GetPosMapStartIndex001
 * @tc.desc: Test ListHeightOffsetCalculator GetPosMapStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, GetPosMapStartIndex001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.posMap_ = nullptr;
    auto result = listHeightOffsetCalculator.GetPosMapStartIndex();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetPosMapEndIndex001
 * @tc.desc: Test ListHeightOffsetCalculator GetPosMapEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, GetPosMapEndIndex001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.posMap_ = nullptr;
    auto result = listHeightOffsetCalculator.GetPosMapEndIndex();
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetLazyForEachIndexAverageHeight001
 * @tc.desc: Test ListHeightOffsetCalculator GetLazyForEachIndexAverageHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListHeightTestNg, GetLazyForEachIndexAverageHeight001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<UINode> node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(node, nullptr);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    auto itemPosition = listLayoutAlgorithm->GetItemPosition();
    ListHeightOffsetCalculator listHeightOffsetCalculator(itemPosition, 2.0f, 2, Axis::VERTICAL, 2);
    listHeightOffsetCalculator.estimateItemHeight_ = 2.0f;
    listHeightOffsetCalculator.posMap_ = nullptr;
    bool hasGroup = false;
    listHeightOffsetCalculator.GetLazyForEachIndexAverageHeight(node, 1, 2, hasGroup);
    EXPECT_FALSE(hasGroup);
    EXPECT_EQ(listHeightOffsetCalculator.estimateItemHeight_, 2.0f);
}
} // namespace OHOS::Ace::NG