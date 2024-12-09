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

#include "list_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/list/list_item_group_paint_method.h"

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
} // namespace

class ListScrollerTestNg : public ListTestNg {};

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Set ContentStartOffset and ContentEndOffset, ScrollTo index:3
     * @tc.expected: Each test scroll the correct distance
     */
    float offset = 25.0f;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(offset);
    model.SetContentEndOffset(offset);
    CreateListItemGroups(8);
    CreateDone();
    int32_t index = 3;
    auto groupNode = frameNode_->GetChildByIndex(index)->GetHostNode();
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    auto groupLayoutProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    groupLayoutProperty->UpdateVisibility(VisibleType::GONE);

    float groupHeight = ITEM_MAIN_SIZE * GROUP_ITEM_NUMBER; // 200.0f
    ScrollToIndex(index, true, ScrollAlign::START);
    EXPECT_TRUE(Position(-(index * groupHeight - offset)));
    ScrollToIndex(index, true, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-400.0f));
    ScrollToIndex(index, true, ScrollAlign::END);
    EXPECT_TRUE(Position(-(200 + offset)));

    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    ScrollToIndex(index, true, ScrollAlign::START);
    EXPECT_TRUE(Position(-index * groupHeight));
    ScrollToIndex(index, true, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-400.0f));
    ScrollToIndex(index, true, ScrollAlign::END);
    EXPECT_TRUE(Position(-200.0f));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex(1, true, ScrollAlign::AUTO)
     * @tc.expected: Each test scroll the correct distance
     */
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, Dimension(1000.0f));
    CreateList();
    CreateItemWithSize(4, itemSize);
    CreateDone();

    /**
     * @tc.cases: bottomOffset > topOffset > 0
     * @tc.expected: top Align
     */
    ScrollTo(800);
    EXPECT_EQ(pattern_->GetTotalOffset(), 800);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1000.0f));

    /**
     * @tc.cases: bottomOffset > topOffset == 0
     * @tc.expected: top Align
     */
    ScrollTo(1000);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1000);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1000.0f));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| < |bottomOffset|
     * @tc.expected: top Align
     */
    ScrollTo(1050);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1050);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1050.0f));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| == |bottomOffset|
     * @tc.expected: bottom Align
     */
    ScrollTo(1300);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 1300);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1600.0f));

    /**
     * @tc.cases: bottomOffset == 0 > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1400);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1400);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1600.0f));

    /**
     * @tc.cases: 0 > bottomOffset > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1700);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1700);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1600.0f));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list.
     * @tc.cases: the height of listItemGroup is more than one screen
     */
    ListModelNG model = CreateList();
    model.SetContentStartOffset(50.0f);
    model.SetContentEndOffset(50.0f);
    model.SetInitialIndex(1);
    CreateGroupWithSetting(4, V2::ListItemGroupStyle::NONE, 8);
    CreateDone();
    EXPECT_EQ(pattern_->contentStartOffset_, 50.0f);
    EXPECT_EQ(pattern_->contentEndOffset_, 50.0f);

    /**
     * @tc.steps: step2. scroll to the group(index:0).
     * @tc.cases: jumpIndex < StartIndex
     * @tc.expected: pattern_->GetTotalOffset() == 620.
     *     GroupHight = Header(50) + footer(50) + (item(100) + space(10))*count(8) - space(10) = 970
     *     Offset = GroupHight(970) - (ListHeight(400) - ContentEndOffset(50)) = 620
     */
    ScrollToIndex(0, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.0f);
    auto itemHeight = GetChildFrameNode(frameNode_, 0)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_GT(itemHeight, pattern_->contentMainSize_);

    /**
     * @tc.steps: step2. scroll to group(index:1).
     * @tc.cases: jumpIndex < StartIndex
     * @tc.expected: pattern_->GetTotalOffset() == 920.0f.
     *     Offset = GroupHight(970) - ContentStartOffset(50) = 920
     */
    ScrollToIndex(1, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 920.0f);
    itemHeight = GetChildFrameNode(frameNode_, 1)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_GT(itemHeight, pattern_->contentMainSize_);
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex without animation
     * @tc.expected: GetTotalOffset is right
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    std::optional<float> extraOffset = -200.0f;
    ScrollToIndex(1, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(18, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(18, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1300.0f));
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1400.0f));

    extraOffset = 200.0f;
    ScrollToIndex(1, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-300.0f));
    ScrollToIndex(1, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(18, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex with animation
     * @tc.expected: GetFinalPosition is right
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    std::optional<float> extraOffset = -200.0f;
    ScrollToIndex(1, true, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(18, true, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(18, true, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1300.0f));
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1300.0f));

    extraOffset = 200.0f;
    ScrollToIndex(1, true, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-300.0f));
    ScrollToIndex(1, true, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(18, true, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-1600.0f));
}

/**
 * @tc.name: ScrollToIndex006
 * @tc.desc: Test ScrollToIndex with update estimate offset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: Test ScrollToIndex with update estimate offset
     * @tc.expected: List will update Animation.
     */
    auto model = CreateList();
    model.SetInitialIndex(4);
    for (int32_t i = 0; i < 3; i++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        SetSize(Axis::VERTICAL, CalcLength(FILL_LENGTH), CalcLength(200));
        ViewStackProcessor::GetInstance()->Pop();
    }
    for (int32_t i = 0; i < 3; i++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        SetSize(Axis::VERTICAL, CalcLength(FILL_LENGTH), CalcLength(300));
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1200);

    ScrollToIndex(2, true, ScrollAlign::CENTER, 0);
    EXPECT_TRUE(Position(-600.0f));
    MockAnimationManager::GetInstance().SetTicks(4);
    ScrollToIndex(1, true, ScrollAlign::CENTER, 0);
    EXPECT_TRUE(Position(-550.0f));
    EXPECT_TRUE(Position(-500.0f));
    EXPECT_TRUE(Position(-150.0f));
    EXPECT_TRUE(Position(-137.5)); // Update Animation
    EXPECT_TRUE(Position(-125));
    EXPECT_TRUE(Position(-112.5));
    EXPECT_TRUE(Position(-100.0f));
}

/**
 * @tc.name: ScrollToIndex007
 * @tc.desc: Test ScrollTo top with update estimate offset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: Test ScrollTo top with update estimate offset
     * @tc.expected: List will scroll to top.
     */
    auto model = CreateList();
    model.SetInitialIndex(4);
    for (int32_t i = 0; i < 3; i++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        SetSize(Axis::VERTICAL, CalcLength(FILL_LENGTH), CalcLength(180));
        ViewStackProcessor::GetInstance()->Pop();
    }
    for (int32_t i = 0; i < 4; i++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        SetSize(Axis::VERTICAL, CalcLength(FILL_LENGTH), CalcLength(150));
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600); // estimate:600, real:690

    MockAnimationManager::GetInstance().SetTicks(12);
    positionController_->AnimateTo(Dimension(0), 100, nullptr, true);
    FlushUITasks();
    for (int32_t i = 0; i < 10; i++) {
        EXPECT_TRUE(Position(-550 + i * 50));
    }
    EXPECT_TRUE(Position(-140)); // estimate:50, real:140
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: JumpToItemInGroup001
 * @tc.desc: Test JumpToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup001, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(8);
    CreateDone();

    /**
     * @tc.steps: step2. index is -2.
     * @tc.expected: not scroll.
     */
    JumpToItemInGroup(-2, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 400);

    /**
     * @tc.steps: step3. index is -1.
     * @tc.expected: not scroll.
     */
    JumpToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 400);

    /**
     * @tc.steps: step4. indexInGroup is std::nullopt.
     * @tc.expected: startIndex_ = 0 and endIndex_ = 2.
     */
    ScrollToIndex(1, true, ScrollAlign::CENTER);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 300);

    /**
     * @tc.steps: step5. group within the screen.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 300);
}

/**
 * @tc.name: JumpToItemInGroup002
 * @tc.desc: Test JumpToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup002, TestSize.Level1)
{
    const int32_t number = 8;
    CreateList();
    CreateGroupWithItem(number);
    CreateDone();

    /**
     * @tc.steps: step2. index is item.
     * @tc.expected: not scroll.
     */
    JumpToItemInGroup(1, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step2. index is greater than list size.
     * @tc.expected: not scroll.
     */
    JumpToItemInGroup(8, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step3. indexInGroup is greater than item size in group.
     * @tc.expected: not scroll.
     */
    JumpToItemInGroup(2, 4, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step4. index is greater than the size in list.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(number, true, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step5. index is -1.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
}

/**
 * @tc.name: JumpToItemInGroup003
 * @tc.desc: Test JumpToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateGroupWithSetting(8, V2::ListItemGroupStyle::NONE);
    CreateDone();
    JumpToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);

    JumpToItemInGroup(2, 1, true, ScrollAlign::END);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);

    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::HEADER);
    JumpToItemInGroup(2, 1, true, ScrollAlign::START);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 90);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 0);

    JumpToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 90);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 0);

    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    JumpToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 90);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 0);

    JumpToItemInGroup(2, 1, true, ScrollAlign::END);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);
}

/**
 * @tc.name: JumpToItemInGroup004
 * @tc.desc: Test JumpToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list.
     */
    ListModelNG model = CreateList();
    model.SetContentStartOffset(50.0f);
    model.SetContentEndOffset(50.0f);
    CreateListItemGroups(5);
    CreateDone();
    EXPECT_EQ(pattern_->contentStartOffset_, 50.0f);
    EXPECT_EQ(pattern_->contentEndOffset_, 50.0f);

    /**
     * @tc.steps: step2. scroll to the last index.
     * @tc.expected: pattern_->itemPosition_[4].endPos == 750.
     */
    JumpToItemInGroup(4, 1, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 4);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 350);

    JumpToItemInGroup(4, 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 4);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 350);

    ScrollTo(0);
    JumpToItemInGroup(4, 1, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 4);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 350);

    /**
     * @tc.steps: step3. scroll to the 1st index.
     * @tc.cases: jumpIndex < StartIndex
     * @tc.expected: pattern_->GetTotalOffset() == -50.
     */
    ScrollToIndex(0, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), -50);
    auto itemHeight = GetChildFrameNode(frameNode_, 0)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_LT(itemHeight, pattern_->contentMainSize_);

    /**
     * @tc.steps: step4. scroll to the 3rd index.
     * @tc.cases: jumpIndex > EndIndex
     * @tc.expected: pattern_->GetTotalOffset() == 450.
     */
    ScrollToIndex(3, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 450);
    itemHeight = GetChildFrameNode(frameNode_, 3)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_LT(itemHeight, pattern_->contentMainSize_);
}

/**
 * @tc.name: JumpToItemInGroup005
 * @tc.desc: Test ScrollToItemInGroup With Margin
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list with margin.
     */
    ListModelNG model = CreateList();
    CreateListItemGroups(4);
    CreateDone();

    MarginProperty groupMargin = { CalcLength(10), CalcLength(10), CalcLength(0), CalcLength(10) };
    MarginProperty itemMargin = { CalcLength(5), CalcLength(5), CalcLength(0), CalcLength(5) };
    for (int i = 0; i < 4; ++i) {
        auto groupNode = GetChildFrameNode(frameNode_, i);
        for (int j = 0; j < GROUP_ITEM_NUMBER; ++j) {
            auto itemLayoutProperty = GetChildLayoutProperty<ListItemLayoutProperty>(groupNode, j);
            itemLayoutProperty->UpdateMargin(itemMargin);
        }
        auto itemGroupLayoutProperty = groupNode->GetLayoutProperty();
        itemGroupLayoutProperty->UpdateMargin(groupMargin);
    }
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 210); // GROUP_ITEM_NUMBER * (ITEM_MAIN_SIZE + 5)
    EXPECT_EQ(pattern_->GetTotalHeight(), 880);    // 4 * (210 + 10)
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 220);

    /**
     * @tc.steps: step2. JumpToItemInGroup.
     * @tc.expected: Each test scroll the correct distance.
     */
    JumpToItemInGroup(1, 1, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0);

    JumpToItemInGroup(2, 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_FLOAT_EQ(pattern_->itemPosition_[1].startPos, -72.5f);

    JumpToItemInGroup(1, 1, false, ScrollAlign::END);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 190);
}

/**
 * @tc.name: JumpToItemInGroup006
 * @tc.desc: Test ScrollToItemInGroup With Padding
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, JumpToItemInGroup006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list with padding.
     */
    ListModelNG model = CreateList();
    CreateListItemGroups(4);
    CreateDone();

    MarginProperty listPadding = { CalcLength(10), CalcLength(10), CalcLength(10), CalcLength(10) };
    MarginProperty groupPadding = { CalcLength(5), CalcLength(5), CalcLength(5), CalcLength(5) };
    layoutProperty_->UpdatePadding(listPadding);
    for (int i = 0; i < 4; ++i) {
        auto groupLayoutProperty = GetChildLayoutProperty<ListItemGroupLayoutProperty>(frameNode_, i);
        groupLayoutProperty->UpdatePadding(groupPadding);
    }
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 210); // GROUP_ITEM_NUMBER * ITEM_MAIN_SIZE + groupPadding
    EXPECT_EQ(pattern_->GetTotalHeight(), 840);    // 4 * 210
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 210);

    /**
     * @tc.steps: step2. JumpToItemInGroup.
     * @tc.expected: Each test scroll the correct distance.
     */
    JumpToItemInGroup(1, 1, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -5);

    JumpToItemInGroup(2, 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -75);

    JumpToItemInGroup(1, 1, false, ScrollAlign::END);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 175);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20 * 20;
} // namespace
/**
 * @tc.name: PositionController007
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController007, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::VERTICAL);
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_008 = 400.f;
constexpr float OFFSET_TIME_008 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 20 * 10;
} // namespace
/**
 * @tc.name: PositionController008
 * @tc.desc: Test PositionController function with ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    model.SetListDirection(Axis::VERTICAL);
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step9. index is -1.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_009 = 600.f;
constexpr float OFFSET_TIME_009 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_009 = 20 * 60;
} // namespace
/**
 * @tc.name: PositionController009
 * @tc.desc: Test PositionController function with ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    model.SetListDirection(Axis::VERTICAL);
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_009);
    offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. bottomOffset > topOffset == 0
     * expected: top Align
     */
    pattern_->ScrollTo(1000);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 1000);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_010 = 800.f;
constexpr float OFFSET_TIME_010 = 400.f;
constexpr int32_t TIME_CHANGED_COUNTS_010 = 20 * 40;
} // namespace
/**
 * @tc.name: PositionController010
 * @tc.desc: Test PositionController function with ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    model.SetListDirection(Axis::VERTICAL);
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(1, 0, nullptr, true);
    EXPECT_FALSE(pattern_->AnimateStoped());
    double offset = 100.0;
    pattern_->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_TRUE(pattern_->AnimateStoped());
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern012, TestSize.Level1)
{
    // test ScrollToNode
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto listItem = GetChildFrameNode(frameNode_, 5);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    ClearOldNodes();
    CreateList();
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.0f);
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), TOTAL_ITEM_NUMBER * ITEM_MAIN_SIZE);

    // test ToJsonValue/FromJson
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetBool("multiSelectable"), false);
    EXPECT_EQ(json->GetInt("startIndex"), 0);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 0.0);
    EXPECT_EQ(json->GetDouble("friction"), DEFAULT_FRICTION);
    pattern_->FromJson(json);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

/**
 * @tc.name: Pattern013
 * @tc.desc: Test ScrollTo and ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List and Set lanes
     */
    int32_t itemNumber = 10;
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, FILL_LENGTH);
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::VERTICAL);
    model.SetScrollBar(DisplayMode::OFF);
    CreateItemWithSize(itemNumber, itemSize);
    CreateDone();

    /**
     * @tc.steps: step2. swipe forward 3 listItem
     */
    ScrollTo(3 * LIST_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step3. swipe backward 2.5 listItem
     */
    pattern_->ScrollBy(-2.5 * LIST_HEIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, -LIST_HEIGHT / 2.0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step4. swipe forward 3 listItem
     */
    pattern_->ScrollBy(3 * LIST_HEIGHT);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, -LIST_HEIGHT / 2.0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step5. swipe backward 2.5 listItem
     */
    ScrollTo(LIST_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.cases: bottomOffset == topOffset > 0
     * @tc.expected: top Align
     */
    ScrollTo(400);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-400.0f));

    /**
     * @tc.cases: 0 > bottomOffset == topOffset
     * @tc.expected: top Align
     */
    ScrollTo(1200);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1200);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-400.0f));

    /**
     * @tc.cases: JumpIndex == StartIndex == EndIndex
     * @tc.expected: top Align
     */
    ScrollTo(800);
    ScrollToIndex(1, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400);
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern014, TestSize.Level1)
{
    int32_t itemNumber = 16;
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateListItems(itemNumber);
    CreateDone();

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushUITasks();
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: Pattern015
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern015, TestSize.Level1)
{
    int32_t itemNumber = 16;
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetEdgeEffect(EdgeEffect::FADE, false);
    CreateListItems(itemNumber);
    CreateDone();

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushUITasks();
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: Pattern016
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern016, TestSize.Level1)
{
    int32_t itemNumber = 16;
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(itemNumber);
    CreateDone();

    auto scrollBar = pattern_->GetScrollBar();
    Rect barRect = scrollBar->GetBarRect();
    Rect activeRectInit = scrollBar->GetActiveRect();
    Rect activeRectBot = Rect(LIST_WIDTH, LIST_HEIGHT - activeRectInit.Height(), 0, activeRectInit.Height());

    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_BAR_FLING };

    for (int32_t form : scrollFromVector) {
        bool isAtBottom = pattern_->IsAtBottom();
        float offset = isAtBottom ? 3 * LIST_HEIGHT : -3 * LIST_HEIGHT;
        EXPECT_TRUE(pattern_->UpdateCurrentOffset(offset, form));
        FlushUITasks();
        EXPECT_TRUE(IsEqual(scrollBar->GetBarRect(), barRect));
        if (isAtBottom) {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), 0);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectInit));
        } else {
            EXPECT_FLOAT_EQ(pattern_->GetBarOffset(), -1200);
            EXPECT_TRUE(IsEqual(scrollBar->GetActiveRect(), activeRectBot));
        }
    }
}

/**
 * @tc.name: Pattern017
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern017, TestSize.Level1)
{
    CreateList();
    CreateListItems(16);
    CreateDone();
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    pattern_->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->endIndex_, 7);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    pattern_->ScrollPage(true, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    pattern_->ScrollPage(false, true);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, 400);

    pattern_->ScrollPage(true, true);
    FlushUITasks();
    EXPECT_EQ(pattern_->finalPosition_, -400);
}

/**
 * @tc.name: PostListItemPressStyleTask_scroll001
 * @tc.desc: Test list layout with PostListItemPressStyleTask scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PostListItemPressStyleTask_scroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetDivider(ITEM_DIVIDER);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }

    auto listItemNode = GetChildFrameNode(frameNode_, 0);
    auto listItemNodeId = listItemNode->GetId();
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(listItemNode);
    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_PRESSED);
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    for (auto child : listPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_TRUE(child.second.isPressed);
        }
    }

    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_NORMAL);
    paint = pattern_->CreateNodePaintMethod();
    listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    for (auto child : listPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_FALSE(child.second.isPressed);
        }
    }
}

/**
 * @tc.name: PostListItemPressStyleTask_scroll002
 * @tc.desc: Test listItemGroup layout with PostListItemPressStyleTask scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PostListItemPressStyleTask_scroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetDivider(ITEM_DIVIDER);
    CreateListItemGroups(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    int cur = 0;
    for (auto& child : groupPattern->itemPosition_) {
        child.second.id += cur;
        cur++;
    }

    auto listItemNode = GetChildFrameNode(groupFrameNode, 0);
    auto listItemNodeId = listItemNode->GetId();
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(listItemNode);
    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_PRESSED);
    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);
    for (auto child : groupPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_TRUE(child.second.isPressed);
        }
    }

    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_NORMAL);
    paint = groupPattern->CreateNodePaintMethod();
    groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);
    for (auto child : groupPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_FALSE(child.second.isPressed);
        }
    }
}

/**
 * @tc.name: ChildrenMainSize001
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollable list, change some items height
     * @tc.expected: Items height are unequal
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_MAIN_SIZE);
    childrenSize->ChangeData(2, 3, { 50.0f, 100.0f, 200.0f });
    childrenSize->ChangeData(15, 3, { 50.0f, 100.0f, 200.0f });
    CreateListItems(2); // ITEM_MAIN_SIZE
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.0f)));
    CreateListItems(10);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.0f)));
    CreateListItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(2), 50.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(17), 200.0f);

    /**
     * @tc.steps: step2. ScrollToIndex, index:3 is in the view
     */
    int32_t index = 3;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-250.0f));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-100.0f));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0.0f));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(0.0f));

    /**
     * @tc.steps: step3. ScrollToIndex, index:17 is out of the view, and will scroll beyond one screen
     */
    index = 17;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1700.0f));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-1500.0f));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1500.0f));

    /**
     * @tc.steps: step4. ScrollTo, 400.0f is in the view
     */
    ScrollTo(400.0f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400.0f);

    /**
     * @tc.steps: step5. ScrollTo, 1400.0f is out of the view
     */
    ScrollTo(1400.0f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1400.0f);
}

/**
 * @tc.name: ChildrenMainSize002
 * @tc.desc: Test childrenMainSize layout with itemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ChildrenMainSize002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(200.0f);
    childrenSize->ChangeData(1, 2, { 450.0f, 450.0f });
    childrenSize->ChangeData(4, 1, { 450.0f });
    CreateListItemGroups(1);
    CreateGroupChildrenMainSize(2);
    CreateListItemGroups(1);
    CreateGroupChildrenMainSize(1);
    CreateDone();

    /**
     * @tc.steps: step2. ScrollToIndex, index:1 is in the view
     */
    int32_t index = 1;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-200.0f));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-225.0f));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-250.0f));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-250.0f));

    /**
     * @tc.steps: step3. ScrollToIndex, index:4 is out of the view, and will scroll beyond one screen
     */
    index = 4;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1300.0f));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1325.0f));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-1350.0f));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1350.0f));

    /**
     * @tc.steps: step4. JumpToItemInGroup, index:1 is in the view
     */
    index = 1;
    int32_t indexInGroup = 2;
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-350.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-250.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-150.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-150.0f));

    /**
     * @tc.steps: step5. JumpToItemInGroup, index:4 is out of the view
     */
    index = 4;
    indexInGroup = 3;
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1350.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1350.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-1350.0f));
    JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-1350.0f));

    /**
     * @tc.steps: step4. ScrollTo, 400.0f is in the view
     */
    ScrollTo(400.0f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400.0f);

    /**
     * @tc.steps: step5. ScrollTo, 1400.0f is out of the view
     */
    ScrollTo(1400.0f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1350.0f);
}

/**
 * @tc.name: ChildrenMainSize003
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ChildrenMainSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.cases: listItemGroup  with header and footer and space
     */
    ListItemIndex endInfo;
    auto onVisibleChange = [&endInfo](ListItemIndex start, ListItemIndex end) { endInfo = end; };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(100.0f);
    childrenSize->ChangeData(4, 1, { 530.0f });
    childrenSize->ChangeData(5, 1, { 580.0f });
    CreateListItems(4);
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE);
    CreateGroupWithSettingChildrenMainSize(1);
    CreateListItems(4);
    CreateDone();
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(4), 530.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(5), 580.0f);
    ListItemIndex endExpect = { 3, -1, -1 };
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. ScrollTo 120
     * @tc.expected: endExpect.area == footer
     */
    ScrollTo(120);
    endExpect = { 4, 1, 0 };
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. ScrollTo 300
     * @tc.expected: index:5 indexInGroup:1 height == 50
     */
    ScrollTo(300);
    auto groupPattern = frameNode_->GetChildByIndex(5)->GetHostNode()->GetPattern<ListItemGroupPattern>();
    EXPECT_EQ(groupPattern->childrenSize_->GetChildSize(1), 50.0f);
    endExpect = { 4, 3, -1 };
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. ScrollTo 540
     * @tc.expected: index:5 indexInGroup:2 height == 200
     */
    ScrollTo(540);
    EXPECT_EQ(groupPattern->childrenSize_->GetChildSize(2), 200.0f);
    endExpect = { 5, 2, -1 };
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}

/**
 * @tc.name: ChildrenMainSize004
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ChildrenMainSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list with multi lanes and space
     * @tc.expected: GetItemRect is right
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10.0f));
    model.SetLanes(2);
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_MAIN_SIZE);
    childrenSize->ChangeData(4, 1, { 200.0f });
    childrenSize->ChangeData(9, 1, { 450.0f });
    childrenSize->ChangeData(10, 4, { 50.0f, 50.0f, 200.0f, 200.0f });
    childrenSize->ChangeData(18, 4, { 50.0f, 200.0f, 50.0f, 200.0f });
    CreateListItems(4); // 0~3
    CreateListItemGroups(1);
    CreateListItems(4); // 5~8
    CreateGroupChildrenMainSize(1);
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(50.0f)));
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(200.0f)));
    CreateListItems(4); // 14~17
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.0f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.0f)));
    CreateListItems(8);
    CreateDone();
    JumpToItemInGroup(4, 1, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-220.0f));
    JumpToItemInGroup(4, 1, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-70.0f));
    JumpToItemInGroup(4, 1, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0));
    JumpToItemInGroup(9, 1, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-650.0f));
    JumpToItemInGroup(9, 1, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-500.0f));
    JumpToItemInGroup(9, 1, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-350.0f));

    /**
     * @tc.steps: step2. ScrollToIndex 12 / ScrollToIndex 13
     * @tc.expected: GetTotalOffset is right
     */
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(10), 50.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(11), 50.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(12), 200.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(13), 200.0f);
    ScrollToIndex(10, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1110.0f));
    ScrollToIndex(10, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-935.0f));
    ScrollToIndex(10, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-760.0f));
    ScrollToIndex(13, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1170.0f));
    ScrollToIndex(13, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1070.0f));
    ScrollToIndex(13, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-970.0f));

    /**
     * @tc.steps: step3. ScrollToIndex 18 / ScrollToIndex 21
     * @tc.expected: GetTotalOffset is right
     */
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(18), 50.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(19), 200.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(20), 50.0f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(21), 200.0f);
    ScrollToIndex(18, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1600.0f));
    ScrollToIndex(18, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1500.0f));
    ScrollToIndex(18, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-1400.0f));
    ScrollToIndex(21, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-1810.0f));
    ScrollToIndex(21, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-1710.0f));
    ScrollToIndex(21, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-1610.0f));
}

/**
 * @tc.name: GetScrollEnabled001
 * @tc.desc: Test List model ng GetScrollEnabled
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, GetScrollEnabled001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(model.GetScrollEnabled(AceType::RawPtr(frameNode_)), 1);
    model.SetScrollEnabled(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(model.GetScrollEnabled(AceType::RawPtr(frameNode_)), 0);
}

/**
 * @tc.name: SetScrollBy001
 * @tc.desc: Test List model ng SetScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, SetScrollBy001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    const double x = 1.0;
    const double y = 2.0;
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, y);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), y);
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, 0.0);
    EXPECT_EQ(pattern_->GetTotalOffset(), y);
}

/**
 * @tc.name: SetScrollBy002
 * @tc.desc: Test List model ng SetScrollBy before List layout
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, SetScrollBy002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    const double y = 200.f;
    model.SetScrollBy(AceType::RawPtr(frameNode_), 0, y);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), y);
}
} // namespace OHOS::Ace::NG
