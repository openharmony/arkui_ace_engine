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

namespace OHOS::Ace::NG {
class ListControllerTestNg : public ListTestNg, public testing::WithParamInterface<bool> {};

/**
 * @tc.name: ScrollToIndex_Align001
 * @tc.desc: Test ScrollToIndex with ScrollAlign::START
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::START;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-500.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll with invalid index
    ScrollToIndex(-100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));
    ScrollToIndex(100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align002
 * @tc.desc: Test ScrollToIndex with ScrollAlign::CENTER
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align002, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::CENTER;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-350.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(0));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align003
 * @tc.desc: Test ScrollToIndex with ScrollAlign::END
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align003, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::END;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(0));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align004
 * @tc.desc: Test ScrollToIndex with ScrollAlign::AUTO
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align004, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align005
 * @tc.desc: Test ScrollToIndex with ScrollAlign::START
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetStackFromEnd(true);
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::START;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-500.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll with invalid index
    ScrollToIndex(-100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));
    ScrollToIndex(100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align006
 * @tc.desc: Test ScrollToIndex with ScrollAlign::CENTER
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetStackFromEnd(true);
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::CENTER;
    ScrollToIndex(0, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(150));
    } else {
        EXPECT_TRUE(TickPosition(0));
    }
    

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(50));
    } else {
        EXPECT_TRUE(TickPosition(0));
    }
    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-350.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(0));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align007
 * @tc.desc: Test ScrollToIndex with ScrollAlign::END
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align007, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetStackFromEnd(true);
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::END;
    ScrollToIndex(0, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(300));
    } else {
        EXPECT_TRUE(TickPosition(0));
    }

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(200));
    } else {
        EXPECT_TRUE(TickPosition(0));
    }

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(0));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align008
 * @tc.desc: Test ScrollToIndex with ScrollAlign::AUTO
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Align008, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the middle item in view
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the item out of view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item
    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Space001
 * @tc.desc: Test ScrollToIndex with space
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Space001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    CreateListItems();
    CreateDone();

    // ScrollAlign::START
    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-110.0f));

    // ScrollAlign::CENTER
    ScrollToIndex(5, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-400.0f));

    // ScrollAlign::END
    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-250.0f));

    // ScrollAlign::AUTO
    ScrollToIndex(8, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-580.0f));
}

/**
 * @tc.name: ScrollToIndex_Lanes001
 * @tc.desc: Test ScrollToIndex with lanes
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_Lanes001, TestSize.Level1)
{
    const int32_t lanes = 2;
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    CreateListItems(TOTAL_ITEM_NUMBER * lanes);
    CreateDone();

    bool smooth = GetParam();
    ScrollToIndex(2, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-100.0f));

    ScrollToIndex(9, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-250.0f));

    ScrollToIndex(10, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-200.0f));

    ScrollToIndex(16, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-500.0f));
}

/**
 * @tc.name: ScrollToIndex_ContentOffset001
 * @tc.desc: Test ScrollToIndex with ContentStartOffset/ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_ContentOffset001, TestSize.Level1)
{
    float offset = 25.0f;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(offset);
    model.SetContentEndOffset(offset);
    CreateListItems();
    CreateDone();

    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-75.0f));

    ScrollToIndex(5, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-350.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-225.0f));

    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-225.0f));
    } else {
        EXPECT_TRUE(TickPosition(-625.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_AddItem001
 * @tc.desc: Test ScrollToIndex when add item to list
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_AddItem001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Add listItem and scroll to the Item.
     * @tc.expected: Has itemNumber+1 child number.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), TOTAL_ITEM_NUMBER);
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);
    AddListItem();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetChildren().size(), TOTAL_ITEM_NUMBER + 1);
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE + ITEM_MAIN_SIZE);

    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-100.0f));

    ScrollToIndex(5, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-350.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-200.0f));

    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-200.0f));
    } else {
        EXPECT_TRUE(TickPosition(-700.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_ExtraOffset001
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_ExtraOffset001, TestSize.Level1)
{
    CreateList();
    CreateListItems(20);
    CreateDone();
    bool smooth = GetParam();
    float extraOffset = -200.0f;
    ScrollToIndex(1, smooth, ScrollAlign::START, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(0));

    ScrollToIndex(18, smooth, ScrollAlign::START, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-1600.0f));

    ScrollToIndex(18, smooth, ScrollAlign::END, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-1300.0f));

    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    FlushUITasks();
    if (smooth) {
        EXPECT_TRUE(TickPosition(-1300.0f));
    } else {
        EXPECT_TRUE(TickPosition(-1400.0f));
    }

    extraOffset = 200.0f;
    ScrollToIndex(1, smooth, ScrollAlign::START, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-300.0f));

    ScrollToIndex(1, smooth, ScrollAlign::END, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(0));

    ScrollToIndex(18, smooth, ScrollAlign::END, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-1600.0f));

    ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-1600.0f));
}

/**
 * @tc.name: ScrollToIndex_ListItemGroup001
 * @tc.desc: Test ScrollToIndex with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToIndex_ListItemGroup001, TestSize.Level1)
{
    CreateList();
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone();

    // groupHeight: 310
    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-310.0f));

    ScrollToIndex(3, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-885.0f));

    ScrollToIndex(3, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-840.0f));

    ScrollToIndex(4, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-1150.0f));
}

/**
 * @tc.name: JumpToItemInGroup_Align001
 * @tc.desc: Test JumpToItemInGroup with ScrollAlign::START
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Align001, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(5);
    CreateDone();

    // groupHeight: 200
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::START;
    JumpToItemInGroup(0, 0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    JumpToItemInGroup(3, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-600.0f));

    JumpToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 0, smooth, align);
    EXPECT_TRUE(TickPosition(-600.0f));

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    JumpToItemInGroup(-100, -100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    JumpToItemInGroup(100, 100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // NONE equal to START
    align = ScrollAlign::NONE;
    JumpToItemInGroup(3, 1, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }
}

/**
 * @tc.name: JumpToItemInGroup_Align002
 * @tc.desc: Test JumpToItemInGroup with ScrollAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Align002, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(5);
    CreateDone();

    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::CENTER;
    JumpToItemInGroup(0, 0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(3, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-550.0f));

    JumpToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 0, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-550.0f));
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
    }

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: JumpToItemInGroup_Align003
 * @tc.desc: Test JumpToItemInGroup with ScrollAlign::END
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Align003, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(5);
    CreateDone();

    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::END;
    JumpToItemInGroup(0, 0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(3, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-400.0f));

    JumpToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 0, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-400.0f));
    } else {
        EXPECT_TRUE(TickPosition(-500.0f));
    }

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: JumpToItemInGroup_Align004
 * @tc.desc: Test JumpToItemInGroup with ScrollAlign::AUTO
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Align004, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(5);
    CreateDone();

    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::AUTO;
    JumpToItemInGroup(0, 0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(0, 1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(3, 1, smooth, align);
    EXPECT_TRUE(TickPosition(-400.0f));

    JumpToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 0, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-400.0f));
    } else {
        EXPECT_TRUE(TickPosition(-500.0f));
    }

    JumpToItemInGroup(0, 1, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-400.0f));
    } else {
        EXPECT_TRUE(TickPosition(-100.0f));
    }
}

/**
 * @tc.name: JumpToItemInGroup_Space001
 * @tc.desc: Test JumpToItemInGroup with space
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Space001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 1190);

    // groupHeight: 310
    bool smooth = GetParam();
    JumpToItemInGroup(0, 1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-160.0f));

    JumpToItemInGroup(3, 1, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-970.0f));

    JumpToItemInGroup(3, 1, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-820.0f));

    JumpToItemInGroup(5, 0, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-820.0f));
}

/**
 * @tc.name: JumpToItemInGroup_Lanes001
 * @tc.desc: Test JumpToItemInGroup with lanes
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, JumpToItemInGroup_Lanes001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateListItemGroups(10);
    CreateDone();

    bool smooth = GetParam();
    JumpToItemInGroup(0, 1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(0));

    JumpToItemInGroup(6, 1, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-450.0f));

    JumpToItemInGroup(6, 1, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-300.0f));

    JumpToItemInGroup(9, 0, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-600.0f));
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, AnimateTo001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(CONTENT_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test AnimateTo in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, AnimateTo002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), HORIZONTAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(10000.0f), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-HORIZONTAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo003
 * @tc.desc: Test AnimateTo in Horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, AnimateTo003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), HORIZONTAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(10000.0f), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-HORIZONTAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollBy001
 * @tc.desc: Test ScrollBy
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollBy001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ScrollBy the position
     * @tc.expected: ScrollBy the position
     */
    bool smooth = GetParam();
    ScrollBy(0, ITEM_MAIN_SIZE, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. ScrollBy the position over the scroll
     * @tc.expected: ScrollBy the bottom, can not over scroll
     */
    ScrollBy(0, CONTENT_MAIN_SIZE, smooth);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. ScrollBy the position 0
     * @tc.expected: Not scroll
     */
    ScrollBy(0, 0, smooth);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step4. ScrollBy the position to top
     * @tc.expected: ScrollBy the top
     */
    ScrollBy(0, -CONTENT_MAIN_SIZE, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test List model ng ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollToEdge001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. ScrollToEdge to bottom
     * @tc.expected: Scroll to bottom
     */
    bool smooth = GetParam();
    model.ScrollToEdge(AceType::RawPtr(frameNode_), ScrollEdgeType::SCROLL_BOTTOM, smooth);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. ScrollToEdge to Top in Axis::NONE
     * @tc.expected: Can not scroll
     */
    pattern_->axis_ = Axis::NONE;
    model.ScrollToEdge(AceType::RawPtr(frameNode_), ScrollEdgeType::SCROLL_TOP, smooth);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ScrollPage
 * @tc.type: FUNC
 */
HWTEST_P(ListControllerTestNg, ScrollPage001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ScrollPage down
     * @tc.expected: Scroll down
     */
    bool smooth = GetParam();
    ScrollPage(false, smooth);
    EXPECT_TRUE(TickPosition(-HEIGHT));

    /**
     * @tc.steps: step2. ScrollPage up
     * @tc.expected: Scroll up
     */
    ScrollPage(true, smooth);
    EXPECT_TRUE(TickPosition(0));
}

INSTANTIATE_TEST_SUITE_P(Smooth, ListControllerTestNg, testing::Bool());

/**
 * @tc.name: AnimateTo004
 * @tc.desc: Test AnimateTo with duration animation
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, AnimateTo004, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(CONTENT_MAIN_SIZE), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo005
 * @tc.desc: Test AnimateTo with duration animation, canOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, AnimateTo005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can over scroll
     */
    bool canOverScroll = true;
    MockAnimationManager::GetInstance().SetTicks(5);
    AnimateTo(Dimension(1000.0f), 1000.0f, Curves::EASE, false, canOverScroll);
    EXPECT_TRUE(TickPosition(-200.0f));
    EXPECT_TRUE(TickPosition(-400.0f));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-800.0f)); // Tick doesn't advance new animations created within the same tick
    EXPECT_TRUE(TickPosition(-760.0f));
    EXPECT_TRUE(TickPosition(-720.0f));
    EXPECT_TRUE(TickPosition(-680.0f));
    EXPECT_TRUE(TickPosition(-640.0f));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: ScrollBy002
 * @tc.desc: Test List model ng SetScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, ScrollBy002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    const double x = 1.0;
    const double y = 2.0;
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, y);
    FlushUITasks();
    EXPECT_TRUE(Position(-y));
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, 0.0);
    EXPECT_TRUE(Position(-y));
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, ScrollToEdge002, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 200.0f);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, 200.0f);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test Fling
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, Fling001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. Fling, the flingVelocity greater than 0
     * @tc.expected: Scroll down
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float finalPosition = 100.0f;
    const float flingVelocity = finalPosition * FRICTION * FRICTION_SCALE;
    Fling(flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(-finalPosition));

    /**
     * @tc.steps: step2. Fling, the flingVelocity less than 0
     * @tc.expected: Scroll up
     */
    Fling(-flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: GetInfo001
 * @tc.desc: Test non-action GetCurrentOffset/GetScrollDirection/IsAtEnd/GetItemRect/GetItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, GetInfo001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset()));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(0, 0, WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_EQ(pattern_->GetItemIndex(100000, -100000), -1);
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(1, 1), 0));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect())); // no group

    /**
     * @tc.steps: step1. AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, ITEM_MAIN_SIZE)));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(1, 1), 1));

    /**
     * @tc.steps: step2. AnimateTo bottom
     */
    AnimateTo(Dimension(CONTENT_MAIN_SIZE), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, VERTICAL_SCROLLABLE_DISTANCE)));
    EXPECT_TRUE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(1, 1), 6));
}

/**
 * @tc.name: GetInfo002
 * @tc.desc: Test GetItemIndexInGroup in ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, GetInfo002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Get invalid group item index.
     * @tc.expected: Return {-1, -1, -1} when input invalid group x and y.
     */
    ScrollTo(ITEM_MAIN_SIZE * 2);
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndexInGroup(100000, -100000), { -1, -1, -1 }));

    /**
     * @tc.steps: step2. Get valid group item index.
     * @tc.expected: Return actual index when input valid group x and y.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndexInGroup(WIDTH * 0.9, ITEM_MAIN_SIZE * 0.9), { 0, 1, 2 }));
}

/**
 * @tc.name: GetInfo003
 * @tc.desc: Test GetItemIndexInGroup in ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListControllerTestNg, GetInfo003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. Get invalid group item Rect.
     * @tc.expected: Return 0 when input invalid group index.
     */
    ScrollTo(ITEM_MAIN_SIZE * 2);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(-1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(2, -1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, TOTAL_ITEM_NUMBER), Rect()));

    /**
     * @tc.steps: step2. Get valid group item Rect.
     * @tc.expected: Return actual Rect when input valid group index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, 2), Rect(0, 0, WIDTH, ITEM_MAIN_SIZE)));

    /**
     * @tc.steps: step3. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, -200.0f, WIDTH, 700.0f)));
}
} // namespace OHOS::Ace::NG
