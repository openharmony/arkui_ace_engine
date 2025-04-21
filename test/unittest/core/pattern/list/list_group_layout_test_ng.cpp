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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_position_map.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemGroupAlgorithmTestNg : public TestNG {
public:
};

/**
 * @tc.name: CheckJumpForwardForBigOffset001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset004
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset004, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset005
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset005, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 3;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    LayoutedItemInfo layoutedItemInfo { 1, 2.0f, 2, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 1.0f);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[0].endPos, 0.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset006
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset006, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 8;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 4);
    EXPECT_EQ(startPos, 3.0f);
    EXPECT_TRUE(listItemGroupLayoutAlgorithm->itemPosition_.empty());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset007
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset007, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 8;
    LayoutedItemInfo layoutedItemInfo { 3, 2.0f, 1, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 1.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset004
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset004, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset005
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset005, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 11.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    LayoutedItemInfo layoutedItemInfo { 1, 2.0f, 2, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t endIndex = 2;
    float endPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[0].startPos, -2.5f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset006
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset006, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 0.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 1.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 0.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    int32_t endIndex = 2;
    float endPos = 3.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_TRUE(listItemGroupLayoutAlgorithm->itemPosition_.empty());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset007
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset007, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 11.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    LayoutedItemInfo layoutedItemInfo { 3, 2.0f, 1, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t endIndex = 2;
    float endPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG