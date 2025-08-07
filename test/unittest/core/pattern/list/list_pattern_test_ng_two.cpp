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

#include <memory>

#include "gtest/gtest.h"
#include "list_test_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListPatternTwoTestNg : public ListTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ListPatternTwoTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListPatternTwoTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListPatternTwoTestNg::SetUp()
{
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

void ListPatternTwoTestNg::TearDown()
{
    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: CalcAlignForFocusToGroupItem
 * @tc.desc: Test ListPattern CalcAlignForFocusToGroupItem
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, CalcAlignForFocusToGroupItem, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set moveStep to -2 and step to NONE
     * @tc.expected: The result of calling the function return ScrollAlign::START
     */
    auto result = listPattern->CalcAlignForFocusToGroupItem(-2, FocusStep::NONE);
    EXPECT_EQ(result, ScrollAlign::START);

    /**
     * @tc.steps: step3. Set moveStep to 2 and step to UP
     * @tc.expected: The result of calling the function return ScrollAlign::START
     */
    result = listPattern->CalcAlignForFocusToGroupItem(2, FocusStep::UP);
    EXPECT_EQ(result, ScrollAlign::END);
}

/**
 * @tc.name: CalcNextIndexInGroup_001
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, CalcNextIndexInGroup_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set itemEndIndex of ListItemGroupPara to 2
     * and hasFooter of ListItemGroupPara to true
     */
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.itemEndIndex = 2;
    nextListItemGroupPara.hasFooter = true;

    /**
     * @tc.steps: step3. Set nextIndex to 2 and curIndex to 1
     * and Set moveStep to -1 and curIndexInGroup to 2
     * @tc.expected: The result of calling the function return 2
     */
    auto result = listPattern->CalcNextIndexInGroup(2, 1, 2, -1, nextListItemGroupPara);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: CalcNextIndexInGroup_002
 * @tc.desc: Test ListPattern CalcNextIndexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, CalcNextIndexInGroup_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set itemEndIndex of ListItemGroupPara to 2
     * and hasHeader of ListItemGroupPara to false
     */
    ListItemGroupPara nextListItemGroupPara;
    nextListItemGroupPara.itemEndIndex = 2;
    nextListItemGroupPara.hasHeader = false;

    /**
     * @tc.steps: step3. Set nextIndex to 2 and curIndex to 1
     * and Set moveStep to 1 and curIndexInGroup to 2
     * @tc.expected: The result of calling the function return 0
     */
    auto result = listPattern->CalcNextIndexInGroup(2, 1, 2, 1, nextListItemGroupPara);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ScrollListItemGroupForFocus
 * @tc.desc: Test ListPattern ScrollListItemGroupForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, ScrollListItemGroupForFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(node, nullptr);
    WeakPtr<FrameNode> weakFrameNode = std::move(node);
    listNode->focusHub_ = AceType::MakeRefPtr<FocusHub>(weakFrameNode);

    /**
     * @tc.steps: step2. Set pipeline
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: step3. Set nextIndexInGroup to 2
     * @tc.expected: The result of calling the function return true and nextIndexInGroup to be -1
     */
    int32_t nextIndexInGroup = 2;
    auto result = listPattern->ScrollListItemGroupForFocus(3, 2, nextIndexInGroup, 1, 1, FocusStep::NONE, true);
    listNode->context_ = nullptr;
    EXPECT_EQ(nextIndexInGroup, -1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollToItemInGroup001
 * @tc.desc: Test ListPattern ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, ScrollToItemInGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set isScrollEnd_ of listPattern to false
     * and scrollAlign_ of listPattern to START
     */
    listPattern->isScrollEnd_ = false;
    listPattern->scrollAlign_ = ScrollAlign::START;

    /**
     * @tc.steps: step3. Set index to 1 and IndexInGroup to 1
     * and Set smooth to false and align to AUTO
     * @tc.expected: The isScrollEnd_ of listPattern to true
     */
    listPattern->ScrollToItemInGroup(1, 1, false, ScrollAlign::AUTO);
    EXPECT_TRUE(listPattern->isScrollEnd_);
}

/**
 * @tc.name: RefreshLanesItemRange001
 * @tc.desc: Test ListPattern RefreshLanesItemRange
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, RefreshLanesItemRange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);
    listNode->childrenUpdatedFrom_ = -2;

    /**
     * @tc.steps: step2. Set lanesItemRange_ of listPattern
     */
    listPattern->lanesItemRange_ = { { -4, -3 }, { -3, 1 }, { -2, 5 } };

    /**
     * @tc.steps: step3. Call the RefreshLanesItemRange function
     * @tc.expected: The value of the -3 key of the lanesItemRange_ be -3
     * and the value of the lanesItemRange_ -2 key is removed
     */
    listPattern->RefreshLanesItemRange();
    EXPECT_EQ(listPattern->lanesItemRange_[-3], -3);
    EXPECT_EQ(listPattern->lanesItemRange_.count(-2), 0);
}

/**
 * @tc.name: NotifyDataChange001
 * @tc.desc: Test ListPattern NotifyDataChange
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, NotifyDataChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set value of focusIndex_ to -2 and itemPosition_
     * Set maintainVisibleContentPosition_ of listPattern to true
     */
    listPattern->focusIndex_ = -2;
    listPattern->maintainVisibleContentPosition_ = true;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };

    /**
     * @tc.steps: step3. set count to 0 and index to -3
     * @tc.expected: The value of focusIndex_ to be 0
     */
    listPattern->NotifyDataChange(-3, 0);
    EXPECT_EQ(listPattern->focusIndex_.value(), 0);
}

/**
 * @tc.name: NotifyDataChange002
 * @tc.desc: Test ListPattern NotifyDataChange
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, NotifyDataChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set value of focusIndex_ to -2 and itemPosition_
     * Set maintainVisibleContentPosition_ of listPattern to true
     */
    listPattern->focusIndex_ = -2;
    listPattern->maintainVisibleContentPosition_ = true;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };

    /**
     * @tc.steps: step3. set count to 0 and index to -1
     * @tc.expected: The value of focusIndex_ to be -2
     */
    listPattern->NotifyDataChange(-1, 0);
    EXPECT_EQ(listPattern->focusIndex_.value(), -2);
}

/**
 * @tc.name: NotifyDataChange003
 * @tc.desc: Test ListPattern NotifyDataChange
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, NotifyDataChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set value of focusIndex_ to 2 and itemPosition_
     * Set maintainVisibleContentPosition_ of listPattern to true
     * and set isBackToTopRunning_ and useTotalOffset_ to true
     */
    listPattern->focusIndex_ = 2;
    listPattern->maintainVisibleContentPosition_ = true;
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    listPattern->isBackToTopRunning_ = true;
    listPattern->useTotalOffset_ = true;

    /**
     * @tc.steps: step3. set count to 4 and index to 0
     * @tc.expected: The value of focusIndex_ to be 6 and useTotalOffset_ to false
     */
    listPattern->NotifyDataChange(0, 4);
    EXPECT_EQ(listPattern->focusIndex_.value(), 6);
    EXPECT_FALSE(listPattern->useTotalOffset_);
}

/**
 * @tc.name: CheckDataChangeOutOfStart
 * @tc.desc: Test ListPattern CheckDataChangeOutOfStart
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, CheckDataChangeOutOfStart, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set isStackFromEnd_ of listPattern to true
     */
    listPattern->isStackFromEnd_ = true;

    /**
     * @tc.steps: step3. set count to 2, index to 1, startIndex to 0 and endIndex to 6
     * @tc.expected: The result of calling the function return false
     */
    auto result = listPattern->CheckDataChangeOutOfStart(1, 2, 0, 6);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutItemInGroupForFocus001
 * @tc.desc: Test ListPattern LayoutItemInGroupForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, LayoutItemInGroupForFocus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: step2. Set scrollAlign_ of listPattern to NONE
     * set displayEndIndex and displayStartIndex to 4 and itemPosition_
     * set IsLayout function to return false
     */
    ListItemGroupPara listItemGroupPara;
    listItemGroupPara.displayStartIndex = 4;
    listItemGroupPara.displayEndIndex = 4;
    listPattern->itemPosition_[1] = { 2, 2.0f, 4.0f, true };
    listPattern->scrollAlign_ = ScrollAlign::NONE;

    /**
     * @tc.steps: step3. set indexInList to 2, nextIndexInGroup to 3, curIndexInGroup to 2 and maxListItemIndex to 4
     * @tc.expected: The result of calling the function return false and scrollAlign_ to be END
     */
    auto result = listPattern->LayoutItemInGroupForFocus(2, 3, 2, listItemGroupPara, 4);
    listNode->context_ = nullptr;
    EXPECT_EQ(listPattern->scrollAlign_, ScrollAlign::END);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: LayoutItemInGroupForFocus002
 * @tc.desc: Test ListPattern LayoutItemInGroupForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, LayoutItemInGroupForFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, listPattern);
    ASSERT_NE(listNode, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    listNode->context_ = AceType::RawPtr(context);
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: step2. Set displayEndIndex and displayStartIndex to 2 and itemPosition_
     * set IsLayout function to return true
     */
    ListItemGroupPara listItemGroupPara;
    listItemGroupPara.displayStartIndex = 2;
    listItemGroupPara.displayEndIndex = 2;
    listPattern->itemPosition_[1] = { 2, 2.0f, 4.0f, false };

    /**
     * @tc.steps: step3. set indexInList to 1, nextIndexInGroup to 3, curIndexInGroup to 4 and maxListItemIndex to 4
     * @tc.expected: The result of calling the function return true
     */
    auto result = listPattern->LayoutItemInGroupForFocus(1, 3, 4, listItemGroupPara, 4);
    listNode->context_ = nullptr;
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetNextMoveStepForMultiLanes001
 * @tc.desc: Test ListPattern GetNextMoveStepForMultiLanes
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetNextMoveStepForMultiLanes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndex to 3
     */
    int32_t nextIndex = 3;

    /**
     * @tc.steps: step3. Set the currIndex to 2, focusStep to NONE and isVertical to true
     * @tc.expected: The result of calling the function return -1 and nextIndex is unchanged
     */
    auto result = listPattern->GetNextMoveStepForMultiLanes(2, FocusStep::NONE, true, nextIndex);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GetNextMoveStepForMultiLanes002
 * @tc.desc: Test ListPattern GetNextMoveStepForMultiLanes
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetNextMoveStepForMultiLanes002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndex to 3 and lanes_ of listPattern to 2
     * Set the second element of the itemPosition and cachedItemPosition
     */
    int32_t nextIndex = 3;
    listPattern->lanes_ = 2;
    listPattern->itemPosition_[2] = { 2, 2.0f, 4.0f, false };
    listPattern->cachedItemPosition_[2] = { 3, 4.0f, 6.0f, false };

    /**
     * @tc.steps: step3. Set the currIndex to 2, focusStep to DOWN and isVertical to true
     * @tc.expected: The result of calling the function return 2 and nextIndex to be 4
     */
    auto result = listPattern->GetNextMoveStepForMultiLanes(2, FocusStep::DOWN, true, nextIndex);
    EXPECT_EQ(nextIndex, 4);
    EXPECT_EQ(result, 2);
}

/**
 * @tc.name: GetNextMoveStepForMultiLanes003
 * @tc.desc: Test ListPattern GetNextMoveStepForMultiLanes
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetNextMoveStepForMultiLanes003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set nextIndex to 3 and lanes_ of listPattern to 2
     * Set the second element of the itemPosition and the third element of the cachedItemPosition
     */
    int32_t nextIndex = 3;
    listPattern->lanes_ = 2;
    listPattern->itemPosition_[2] = { 2, 2.0f, 4.0f, false };
    listPattern->cachedItemPosition_[3] = { 3, 4.0f, 6.0f, true };

    /**
     * @tc.steps: step3. Set the currIndex to 2, focusStep to RIGHT and isVertical to false
     * @tc.expected: The result of calling the function return 1 and nextIndex to be curIndex + 1
     */
    auto result = listPattern->GetNextMoveStepForMultiLanes(2, FocusStep::RIGHT, false, nextIndex);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: HandleIndexToBounds
 * @tc.desc: Test static HandleIndexToBounds
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, HandleIndexToBounds, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set maxListItemIndex_ of listPattern to 2
     */
    listPattern->maxListItemIndex_ = 2;

    /**
     * @tc.steps: step3. Set nextIndex to 3 and loopFlag to true
     * @tc.expected: The nextIndex to be maxListItemIndex_ and loopFlag to be false
     */
    int32_t nextIndex = 3;
    bool loopFlag = true;
    listPattern->HandleIndexToBounds(nextIndex, loopFlag);
    EXPECT_EQ(nextIndex, 2);
    EXPECT_FALSE(loopFlag);
}

/**
 * @tc.name: GetCrossAxisNextIndex
 * @tc.desc: Test static GetCrossAxisNextIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetCrossAxisNextIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set focusWrapMode_ of listPattern to DEFAULT
     */
    listPattern->focusWrapMode_ = FocusWrapMode::DEFAULT;

    /**
     * @tc.steps: step3. Call the GetCrossAxisNextIndex function
     * @tc.expected: The result return 3
     */
    auto result = listPattern->GetCrossAxisNextIndex(1, true, 2, FocusStep::NONE);
    EXPECT_EQ(result, 3);
}

/**
 * @tc.name: GetPosition001
 * @tc.desc: Test static GetPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set the second element of the itemPosition and cachedItemPosition
     */
    listPattern->itemPosition_[2] = { 2, 2.0f, 4.0f, false };
    listPattern->cachedItemPosition_[2] = { 3, 4.0f, 6.0f, true };

    /**
     * @tc.steps: step3. Set index to 3
     * @tc.expected: The result return nullptr
     */
    auto result = listPattern->GetPosition(3);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetPosition002
 * @tc.desc: Test static GetPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set the second element of the itemPosition
     * and set the third element of the cachedItemPosition
     */
    listPattern->itemPosition_[2] = { 2, 2.0f, 4.0f, false };
    listPattern->cachedItemPosition_[3] = { 3, 4.0f, 6.0f, true };

    /**
     * @tc.steps: step3. Set index to 3
     * @tc.expected: The result->id return 3
     */
    auto result = listPattern->GetPosition(3);
    EXPECT_EQ(result->id, 3);
}

/**
 * @tc.name: NextPositionBlocksMove001
 * @tc.desc: Test static NextPositionBlocksMove
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, NextPositionBlocksMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set all element of curPos
     * and set the nextPos to nullptr
     */
    ListItemInfo curPos = { 2, 2.0f, 4.0f, false };

    /**
     * @tc.steps: step3. Set isVertical to false
     * @tc.expected: The result return false
     */
    auto result = listPattern->NextPositionBlocksMove(&curPos, nullptr, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NextPositionBlocksMove002
 * @tc.desc: Test static NextPositionBlocksMove
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, NextPositionBlocksMove002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set all element of curPos
     * and set the isGroup of the nextPos to true
     */
    ListItemInfo curPos = { 2, 2.0f, 4.0f, false };
    ListItemInfo nextPos = { 3, 4.0f, 6.0f, true };

    /**
     * @tc.steps: step3. Set isVertical to true
     * @tc.expected: The result return true
     */
    auto result = listPattern->NextPositionBlocksMove(&curPos, &nextPos, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AdjustNextIndexForEdgeRow001
 * @tc.desc: Test static AdjustNextIndexForEdgeRow
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, AdjustNextIndexForEdgeRow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set the maxListItemIndex_ of listPattern to 2
     * and set the lanes_ of listPattern to 2
     */
    listPattern->maxListItemIndex_ = 2;
    listPattern->lanes_ = 2;

    /**
     * @tc.steps: step3. Set nextIndex to 4, moveStep to 2 and curIndex to 2
     * @tc.expected: The result return 4
     */
    auto result = listPattern->AdjustNextIndexForEdgeRow(4, 2, 2);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: AdjustNextIndexForEdgeRow002
 * @tc.desc: Test static AdjustNextIndexForEdgeRow
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, AdjustNextIndexForEdgeRow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set the maxListItemIndex_ of listPattern to 6
     * and set the lanes_ of listPattern to 1
     */
    listPattern->maxListItemIndex_ = 6;
    listPattern->lanes_ = 1;

    /**
     * @tc.steps: step3. Set nextIndex to 6, moveStep to 2 and curIndex to 4
     * @tc.expected: The result return 6
     */
    auto result = listPattern->AdjustNextIndexForEdgeRow(6, 2, 4);
    EXPECT_EQ(result, 6);
}

/**
 * @tc.name: SetFocusWrapMode
 * @tc.desc: Test static SetFocusWrapMode
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetFocusWrapMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    int32_t number = 6;
    FocusWrapMode focusWrapMode = static_cast<FocusWrapMode>(number);

    /**
     * @tc.steps: Set focusWrapMode_ to WRAP_WITH_ARROW
     */
    listPattern->focusWrapMode_ = FocusWrapMode::WRAP_WITH_ARROW;

    /**
     * @tc.steps: step3. Set focusWrapMode is not equal to DEFAULT and WRAP_WITH_ARROW
     * @tc.expected: The focusWrapMode_ of listPattern to be DEFAULT
     */
    listPattern->SetFocusWrapMode(focusWrapMode);
    EXPECT_EQ(listPattern->focusWrapMode_, FocusWrapMode::DEFAULT);
}

/**
 * @tc.name: HandleTargetIndex
 * @tc.desc: Test ListPattern HandleTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, HandleTargetIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->layoutProperty_ = layoutProperty;
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: Set crossMatchChild_ of listPattern to true
     * and set propertyChangeFlag_ to PROPERTY_UPDATE_NORMAL
     */
    listPattern->frameNode_.Upgrade()->layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);
    listPattern->crossMatchChild_ = true;

    /**
     * @tc.steps: step3. Calling the HandleTargetIndex function
     * @tc.expected: the propertyChangeFlag_ to be PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT and result return true
     */
    auto result = listPattern->HandleTargetIndex(true);
    EXPECT_EQ(listNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalculateTargetPos_topOffset_equal_bottomOffset
 * @tc.desc: Test ListPattern CalculateTargetPos
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, CalculateTargetPos_topOffset_equal_bottomOffset, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    listNode->layoutProperty_ = layoutProperty;
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: Set contentMainSize_ of listPattern to 2.0f
     */
    listPattern->contentMainSize_ = 2.0f;

    /**
     * @tc.steps: step3. Set startPos to 2.0f and endPos to 4.0f
     * @tc.expected: The result of this function returns the difference between endPos and contentMainSize_
     */
    auto result = listPattern->CalculateTargetPos(2.0f, 4.0f);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: UpdateCurrentOffset_IsOutOfBoundary
 * @tc.desc: Test ListPattern UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, UpdateCurrentOffset_IsOutOfBoundary, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->layoutProperty_ = layoutProperty;
    listPattern->frameNode_ = listNode;

    /**
     * @tc.steps: Change the value of the list member variable to make the IsOutOfBoundary function return true
     */
    listPattern->jumpIndex_ = std::nullopt;
    listPattern->targetIndex_ = std::nullopt;
    listPattern->isStackFromEnd_ = false;
    listPattern->startIndex_ = 0;
    listPattern->startMainPos_ = 18.0f;
    listPattern->endMainPos_ = 20.0f;
    listPattern->currentDelta_ = 2.0f;
    listPattern->contentStartOffset_ = 4.0f;
    listPattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    listPattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };
    listPattern->frameNode_.Upgrade()->layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);
    listPattern->crossMatchChild_ = true;

    /**
     * @tc.steps: step3. Set offset to 2.0f and source to SCROLL_FROM_JUMP
     * @tc.expected: The result of this function returns false and propertyChangeFlag_ to be
     * PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT
     */
    auto result = listPattern->UpdateCurrentOffset(2.0f, SCROLL_FROM_JUMP);
    EXPECT_EQ(listNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollToSnapIndex_ScrollSnapAlign_NONE
 * @tc.desc: Test ListPattern ScrollToSnapIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, ScrollToSnapIndex_ScrollSnapAlign_NONE, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: Set startIndex_ of listPattern to 2
     */
    listPattern->startIndex_ = 2;

    /**
     * @tc.steps: step3. Set snapDirection to FORWARD and scrollSnapAlign to NONE
     * @tc.expected: The result of this function returns false
     */
    auto result = listPattern->ScrollToSnapIndex(SnapDirection::FORWARD, ScrollSnapAlign::NONE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnColorModeChange00
 * @tc.desc: Test ListPattern OnColorModeChange
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, OnColorModeChange00, TestSize.Level1)
{
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step1. Construct the objects for test
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(listNode, nullptr);

    /**
     * @tc.steps: Test
     */
    listPattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    auto paintProperty = listPattern->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_NE(paintProperty->GetScrollBarProperty(), nullptr);

    paintProperty = listPattern->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->ResetScrollBarProperty();
    listPattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetScrollBarProperty(), nullptr);

    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetChainAnimationToPosMap
 * @tc.desc: Test ListPattern SetChainAnimationToPosMap
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetChainAnimationToPosMap, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set posMap_ of pattern to a new ListPositionMap
     * and create a ChainAnimation and ChainAnimationNode
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE);
    listNode->context_ = AceType::RawPtr(context);
    pattern->posMap_ = AceType::MakeRefPtr<ListPositionMap>();
    RefPtr<ChainAnimation> chainAnimation =
        AceType::MakeRefPtr<ChainAnimation>(0.0f, 10.0f, 5.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    chainAnimation->controlIndex_ = 0;
    chainAnimation->nodes_.clear();
    RefPtr<ChainAnimationNode> node = AceType::MakeRefPtr<ChainAnimationNode>(
        1, 4.0f, 6.0f, 2.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    node->spring_->currentPosition_ = 2.0;
    node->SetDelta(4.0f, 4.0f, 6.0f);
    chainAnimation->nodes_[1] = node;
    pattern->chainAnimation_ = chainAnimation;

    /**
     * @tc.steps: step3. Calling SetChainAnimationToPosMap and chainOffsetCallback function
     * @tc.expected: The result of chainOffsetCallback function returns 2.0f
     */
    pattern->SetChainAnimationToPosMap();
    auto chainOffsetCallback = pattern->posMap_->chainOffsetFunc_;
    auto result = chainOffsetCallback(1);
    listNode->context_ = nullptr;
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: GetChainDelta
 * @tc.desc: Test ListPattern GetChainDelta
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, GetChainDelta, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set PixelRoundMode to PIXEL_ROUND_ON_LAYOUT_FINISH
     * and create a ChainAnimation and ChainAnimationNode
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_ON_LAYOUT_FINISH);
    listNode->context_ = AceType::RawPtr(context);
    RefPtr<ChainAnimation> chainAnimation =
        AceType::MakeRefPtr<ChainAnimation>(0.0f, 10.0f, 5.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    chainAnimation->controlIndex_ = 0;
    chainAnimation->nodes_.clear();
    RefPtr<ChainAnimationNode> node = AceType::MakeRefPtr<ChainAnimationNode>(
        1, 4.0f, 6.0f, 2.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    node->spring_->currentPosition_ = 2.0;
    node->SetDelta(4.0f, 4.0f, 6.0f);
    chainAnimation->nodes_[1] = node;
    pattern->chainAnimation_ = chainAnimation;

    /**
     * @tc.steps: step3. Calling GetChainDelta function
     * @tc.expected: The result of GetChainDelta function returns 2.0f
     */
    auto result = pattern->GetChainDelta(1);
    listNode->context_ = nullptr;
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: SetChainAnimationLayoutAlgorithm_pipeline
 * @tc.desc: Test ListPattern SetChainAnimationLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetChainAnimationLayoutAlgorithm_pipeline, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(layoutProperty);
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(1);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a ChainAnimation and ChainAnimationNode
     */
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE);
    listNode->context_ = AceType::RawPtr(context);
    RefPtr<ChainAnimation> chainAnimation =
        AceType::MakeRefPtr<ChainAnimation>(0.0f, 10.0f, 5.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    chainAnimation->controlIndex_ = 0;
    chainAnimation->nodes_.clear();
    RefPtr<ChainAnimationNode> node = AceType::MakeRefPtr<ChainAnimationNode>(
        1, 4.0f, 6.0f, 2.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    node->spring_->currentPosition_ = 2.0;
    node->SetDelta(4.0f, 4.0f, 6.0f);
    chainAnimation->nodes_[1] = node;
    pattern->chainAnimation_ = chainAnimation;

    /**
     * @tc.steps: step3. Calling SetChainAnimationLayoutAlgorithm function
     * @tc.expected: The chainInterval_ of listLayoutAlgorithm returns 20.0f
     */
    pattern->SetChainAnimationLayoutAlgorithm(listLayoutAlgorithm, listLayoutProperty);
    listNode->context_ = nullptr;
    EXPECT_EQ(listLayoutAlgorithm->chainInterval_, 20.0f);
}

/**
 * @tc.name: SetEdgeEffectCallback_SetTrailingCallback
 * @tc.desc: Test ListPattern SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetEdgeEffectCallback_SetTrailingCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a scrollEffect and set pattern member variables
     */
    pattern->isStackFromEnd_ = true;
    pattern->startIndex_ = 0;
    pattern->startMainPos_ = 0.0f;
    pattern->endMainPos_ = 20.0f;
    pattern->contentStartOffset_ = 0.0f;
    pattern->contentEndOffset_ = 20.0f;
    pattern->contentMainSize_ = 50.0f;
    RefPtr<ScrollEdgeEffect> scrollEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);

    /**
     * @tc.steps: step3. Calling SetEdgeEffectCallback function
     * @tc.expected: The result of trailingCallback function returns 10.0f
     */
    pattern->SetEdgeEffectCallback(scrollEffect);
    auto trailingCallback = scrollEffect->trailingCallback_;
    auto result = trailingCallback();
    EXPECT_EQ(result, 10.0f);
}

/**
 * @tc.name: SetEdgeEffectCallback_SetinitTrailingCallback
 * @tc.desc: Test ListPattern SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetEdgeEffectCallback_SetinitTrailingCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a scrollEffect and set pattern member variables
     */
    pattern->isStackFromEnd_ = true;
    pattern->startIndex_ = 0;
    pattern->startMainPos_ = 0.0f;
    pattern->endMainPos_ = 20.0f;
    pattern->contentStartOffset_ = 0.0f;
    pattern->contentEndOffset_ = 20.0f;
    pattern->contentMainSize_ = 60.0f;
    RefPtr<ScrollEdgeEffect> scrollEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);

    /**
     * @tc.steps: step3. Calling SetEdgeEffectCallback function
     * @tc.expected: The result of trailingCallback function returns 20.0f
     */
    pattern->SetEdgeEffectCallback(scrollEffect);
    auto initTrailingCallback = scrollEffect->initTrailingCallback_;
    auto result = initTrailingCallback();
    EXPECT_EQ(result, 20.0f);
}

/**
 * @tc.name: InitOnKeyEvent
 * @tc.desc: Test ListPattern InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, InitOnKeyEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a FocusHub and set the KeyEvent
     */
    auto focusHub = listNode->GetOrCreateFocusHub();
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_PAGE_DOWN;

    /**
     * @tc.steps: step3. Calling InitOnKeyEvent and onKey function
     * @tc.expected: The result of onKey function returns true
     */
    pattern->InitOnKeyEvent(focusHub);
    auto onKey = focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT];
    ASSERT_NE(onKey, nullptr);
    auto result = onKey(event);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnKeyEvent_IsFocusStepKey
 * @tc.desc: Test ListPattern OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, OnKeyEvent_IsFocusStepKey, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a FocusHub and set the KeyEvent
     * and set focusIndex, groupFocusIndex and startIndex
     */
    pattern->SetFocusIndex(1);
    pattern->SetGroupFocusIndex(2);
    pattern->startIndex_ = 4;
    auto focusHub = listNode->GetOrCreateFocusHub();
    focusHub->SetCurrentFocus(true);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->focusManager_ = AceType::MakeRefPtr<FocusManager>(context);
    listNode->context_ = AceType::RawPtr(context);

    /**
     * @tc.steps: step3. Calling InitOnKeyEvent and onKey function
     * @tc.expected: The result of onKey function returns false
     */
    pattern->InitOnKeyEvent(focusHub);
    auto onKey = focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT];
    ASSERT_NE(onKey, nullptr);
    auto result = onKey(event);
    listNode->context_ = nullptr;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetChainAnimationCallback_SetAnimationCallback
 * @tc.desc: Test ListPattern SetChainAnimationCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTwoTestNg, SetChainAnimationCallback_SetAnimationCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto listNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 0, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listNode->SetLayoutProperty(layoutProperty);
    auto pattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a chainAnimation and set crossMatchChild_ to false
     * and set PropertyChangeFlag to PROPERTY_UPDATE_NORMAL
     */
    RefPtr<ChainAnimation> chainAnimation =
        AceType::MakeRefPtr<ChainAnimation>(0.0f, 10.0f, 5.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    chainAnimation->controlIndex_ = 0;
    chainAnimation->nodes_.clear();
    RefPtr<ChainAnimationNode> node = AceType::MakeRefPtr<ChainAnimationNode>(
        1, 4.0f, 6.0f, 2.0f, AceType::MakeRefPtr<SpringProperty>(2.0, 4.0, 6.0));
    node->spring_->currentPosition_ = 2.0;
    node->SetDelta(4.0f, 4.0f, 6.0f);
    chainAnimation->nodes_[1] = node;
    pattern->chainAnimation_ = chainAnimation;
    RefPtr<ScrollSpringEffect> scrollEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    pattern->scrollEffect_ = scrollEffect;
    listNode->layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);
    pattern->crossMatchChild_ = true;

    /**
     * @tc.steps: step3. Calling SetChainAnimationCallback and animationCallback function
     * @tc.expected: The PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT
     */
    pattern->SetChainAnimationCallback();
    auto animationCallback = pattern->chainAnimation_->animationCallback_;
    animationCallback();
    EXPECT_EQ(listNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}
} // namespace OHOS::Ace::NG