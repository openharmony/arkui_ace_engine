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

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_position_controller.h"

namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
} // namespace

class ListScrollerTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:0, text each ScrollAlign
     * @tc.expected: Each test list does not scroll
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_TRUE(pattern_->IsAtTop());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:2, index:2 item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(10);
    CreateDone(frameNode_);
    int32_t index = 2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * index)); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER,
                              ITEM_HEIGHT * index - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 50.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, ITEM_HEIGHT * index)); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER,
                              ITEM_HEIGHT * index - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 50.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));

    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, ITEM_HEIGHT * index));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:9, index:9 item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    int32_t index = 9;
    float scrollToStartDistance = ITEM_HEIGHT * index; // 900.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollToStartDistance)); // 900.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 550.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollToStartDistance)); // 900.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 550.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 200.f
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 16);
    int32_t index = 19; // ListLayoutAlgorithm::LAST_ITEM
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: List at middle, ScrollTo index:0, index:0 item is above the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    ScrollTo(ITEM_HEIGHT * 8);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 8);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToIndex006
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: List at bottom, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 16);
    EXPECT_TRUE(pattern_->IsAtBottom());
    float scrollableDistance = pattern_->GetScrollableDistance();
    int32_t index = 19; // ListLayoutAlgorithm::LAST_ITEM
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToIndex007
 * @tc.desc: Test ScrollToIndex invalid index(index < -1)
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo invalid index:-2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    int32_t index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToIndex008
 * @tc.desc: Test ScrollToIndex with space
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex008, TestSize.Level1)
{
    /**
     * @tc.cases: Set space, ScrollTo index:12, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE)); // 10.f
    CreateListItems(16);
    CreateDone(frameNode_);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 12 + SPACE * 15); // 1200.f + 150.f
    int32_t index = 12;
    float scrollToStartDistance = (ITEM_HEIGHT + SPACE) * index; // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollToStartDistance)); // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 970.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 620.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 620.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollToStartDistance)); // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 970.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 620.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 620.f
}

/**
 * @tc.name: ScrollToIndex009
 * @tc.desc: Test ScrollToIndex with ListItem and lanes > 1
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex009, TestSize.Level1)
{
    /**
     * @tc.cases: Set lanes, ScrollTo index:14, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    const int32_t lanes = 2;
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    CreateListItems(TOTAL_ITEM_NUMBER * lanes);
    CreateDone(frameNode_);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 2); // 200.f
    int32_t index = 8;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance)); // 200.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT)); // 100.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, ITEM_HEIGHT));
}

/**
 * @tc.name: ScrollToIndex010
 * @tc.desc: Test ScrollToIndex with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToIndex010, TestSize.Level1)
{
    /**
     * @tc.cases: Create itemGroup, ScrollTo groupIndex:3, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE); // each group height:530.f
    CreateDone(frameNode_);
    float groupHeight = ITEM_HEIGHT * 4 + GROUP_HEADER_LEN * 2 + SPACE * 3; // 530.f
    EXPECT_EQ(pattern_->GetScrollableDistance(), groupHeight * 5 - LIST_HEIGHT); // 1850.f
    int32_t index = 3;
    float scrollToStartDistance = groupHeight * index; // 1590.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollToStartDistance)); // 1590.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1455.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollToStartDistance)); // 1590.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1455.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 1320.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO,
                              scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 1320.f
}

/**
 * @tc.name: ScrollToIndex011
 * @tc.desc: Test ScrollToIndex when add item to list
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex011, TestSize.Level1)
{
    int32_t itemNumber = 20;
    CreateList();
    CreateListItems(itemNumber);
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetChildren().size(), itemNumber);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 16);

    /**
     * @tc.steps: step1. Scroll to finally listItem.
     * @tc.expected: check whether the properties is correct.
     */
    int32_t index = 19; // ListLayoutAlgorithm::LAST_ITEM
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, scrollableDistance));

    /**
     * @tc.steps: step2. Add listItem and scroll to the Item.
     * @tc.expected: Has itemNumber+1 child number.
     */
    {
        ListItemModelNG itemModel;
        itemModel.Create();
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushLayoutTask(frameNode_);
    }
    EXPECT_EQ(frameNode_->GetChildren().size(), itemNumber + 1);
    scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 17);

    /**
     * @tc.steps: step3. Scroll to finally listItem.
     * @tc.expected: check whether the properties is correct.
     */
    index = 20; //ListLayoutAlgorithm::LAST_ITEM
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToIndex012
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex012, TestSize.Level1)
{
    /**
     * @tc.cases: Set ContentStartOffset and ContentEndOffset, ScrollTo index:3
     * @tc.expected: Each test scroll the correct distance
     */
    float offset = 25.f;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(offset);
    model.SetContentEndOffset(offset);
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    int32_t index = 3;
    auto groupNode = frameNode_->GetChildByIndex(index)->GetHostNode();
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    auto groupLayoutProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    groupLayoutProperty->UpdateVisibility(VisibleType::GONE);

    float groupHeight = ITEM_HEIGHT * GROUP_ITEM_NUMBER; // 200.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, index * groupHeight - offset));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 400));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200 + offset));

    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, index * groupHeight));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, 400));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 200));
}

/**
 * @tc.name: ScrollToIndex013
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex013, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex(1, true, ScrollAlign::AUTO)
     * @tc.expected: Each test scroll the correct distance
     */
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, Dimension(1000.f));
    CreateList();
    CreateItemWithSize(4, itemSize);
    CreateDone(frameNode_);

     /**
     * @tc.cases: bottomOffset > topOffset > 0
     * @tc.expected: top Align
     */
    ScrollTo(800);
    EXPECT_EQ(pattern_->GetTotalOffset(), 800);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1000));

    /**
     * @tc.cases: bottomOffset > topOffset == 0
     * @tc.expected: top Align
     */
    ScrollTo(1000);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1000);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1000));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| < |bottomOffset|
     * @tc.expected: top Align
     */
    ScrollTo(1050);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1050);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1000));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| == |bottomOffset|
     * @tc.expected: bottom Align
     */
    ScrollTo(1300);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1300);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1600));

    /**
     * @tc.cases: bottomOffset == 0 > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1400);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1400);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1600));

    /**
     * @tc.cases: 0 > bottomOffset > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1700);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1700);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1600));
}

/**
 * @tc.name: ScrollToIndex014
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list.
     * @tc.cases: the height of listItemGroup is more than one screen
     */
    ListModelNG model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetInitialIndex(1);
    CreateGroupWithSetting(4, V2::ListItemGroupStyle::NONE, 8);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->contentStartOffset_, 50.f);
    EXPECT_EQ(pattern_->contentEndOffset_, 50.f);

    /**
     * @tc.steps: step2. scroll to the group(index:0).
     * @tc.cases: jumpIndex < StartIndex
     * @tc.expected: pattern_->GetTotalOffset() == 620.
     *     GroupHight = Header(50) + footer(50) + (item(100) + space(10))*count(8) - space(10) = 970
     *     Offset = GroupHight(970) - (ListHeight(400) - ContentEndOffset(50)) = 620
     */
    ScrollToIndex(0, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 620.f);
    auto itemHeight = GetChildFrameNode(frameNode_, 0)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_GT(itemHeight, pattern_->contentMainSize_);

    /**
     * @tc.steps: step2. scroll to group(index:1).
     * @tc.cases: jumpIndex < StartIndex
     * @tc.expected: pattern_->GetTotalOffset() == 920.f.
     *     Offset = GroupHight(970) - ContentStartOffset(50) = 920
     */
    ScrollToIndex(1, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 920.f);
    itemHeight = GetChildFrameNode(frameNode_, 1)->GetGeometryNode()->GetMarginFrameSize().Height();
    EXPECT_GT(itemHeight, pattern_->contentMainSize_);
}

/**
 * @tc.name: ScrollToIndex015
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex015, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex without animation
     * @tc.expected: GetTotalOffset is right
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    std::optional<float> extraOffset = -200.f;
    ScrollToIndex(1, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.f);
    ScrollToIndex(18, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1600.f); // 20 * ITEM_HEIGHT - LIST_HEIGHT
    ScrollToIndex(18, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1300.f); // 1600.f - ITEM_HEIGHT - 200.f
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1400.f); // 1600.f - 200.f

    extraOffset = 200.f;
    ScrollToIndex(1, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 300.f); // ITEM_HEIGHT + 200.f
    ScrollToIndex(1, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.f);
    ScrollToIndex(18, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1600.f); // 20 * ITEM_HEIGHT - LIST_HEIGHT
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1600.f); // 20 * ITEM_HEIGHT - LIST_HEIGHT
}

/**
 * @tc.name: ScrollToIndex016
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToIndex016, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex with animation
     * @tc.expected: GetFinalPosition is right
     */
    CreateList();
    CreateListItems(20);
    CreateDone(frameNode_);
    std::optional<float> extraOffset = -200.f;
    ScrollToIndex(1, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -100.f); // ITEM_HEIGHT - 200.f
    ScrollToIndex(18, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1600.f); // 20 * ITEM_HEIGHT - LIST_HEIGHT
    ScrollToIndex(18, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1300.f); // 1600.f - ITEM_HEIGHT - 200.f
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1300.f);

    extraOffset = 200.f;
    ScrollToIndex(1, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 300.f); // ITEM_HEIGHT + 200.f
    ScrollToIndex(1, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 0.f);
    ScrollToIndex(18, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1700.f); // 1600.f - ITEM_HEIGHT + 200.f
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1700.f);
}

/**
 * @tc.name: ScrollToItemInGroup001
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup001, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:0 indexInGroup:0, text each ScrollAlign
     * @tc.expected: Each test list does not scroll
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 12); // 1200.f
    EXPECT_TRUE(pattern_->IsAtTop());
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::NONE, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::NONE, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToItemInGroup002
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup002, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:1 indexInGroup:1, group is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(4);
    CreateDone(frameNode_);
    int32_t index = 1;
    int32_t indexInGroup = 1;
    float groupHeight = GROUP_ITEM_NUMBER * ITEM_HEIGHT;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START,
                                    groupHeight * index + ITEM_HEIGHT * indexInGroup)); // 300.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    ITEM_HEIGHT * (indexInGroup + 0.5))); // 150.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START,
                                    groupHeight * index + ITEM_HEIGHT * indexInGroup)); // 300.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    ITEM_HEIGHT * (indexInGroup + 0.5))); // 150.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToItemInGroup003
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup003, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:3 indexInGroup:2, group is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    float groupHeight = GROUP_ITEM_NUMBER * ITEM_HEIGHT; // 400.f
    int32_t index = 3;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + ITEM_HEIGHT * indexInGroup; // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
}

/**
 * @tc.name: ScrollToItemInGroup004
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup004, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:LAST_ITEM indexInGroup:3, group is below the view,
     *            text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
    int32_t indexInGroup = 3;
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToItemInGroup005
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup005, TestSize.Level1)
{
    /**
     * @tc.cases: List at middle, ScrollTo index:0 indexInGroup:0, group is above the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    ScrollTo(ITEM_HEIGHT * 4);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 4);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToItemInGroup006
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup006, TestSize.Level1)
{
    /**
     * @tc.cases: List at bottom, ScrollTo index:LAST_ITEM indexInGroup:3, group is in the view,
     *            text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 24);
    EXPECT_TRUE(pattern_->IsAtBottom());
    int32_t index = 7; // ListLayoutAlgorithm::LAST_ITEM
    int32_t indexInGroup = 3;
    float scrollableDistance = pattern_->GetScrollableDistance(); // 2400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToItemInGroup007
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup invalid
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup007, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo invalid index:1 indexInGroup:-2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);
    int32_t index = 1;
    int32_t indexInGroup = -2; // invalid
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));

    index = 1;
    indexInGroup = 100; // invalid
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));

    index = -2; // invalid
    indexInGroup = 2;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));

    index = 4; // invalid
    indexInGroup = 2;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
}

/**
 * @tc.name: ScrollToItemInGroup008
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup with space
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup008, TestSize.Level1)
{
    /**
     * @tc.cases: Set space, ScrollTo index:4 indexInGroup:2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE)); // 10.f
    CreateGroupWithSetting(8, V2::ListItemGroupStyle::NONE); // each group height:530.f
    CreateDone(frameNode_);
    float groupHeight = ITEM_HEIGHT * 4 + GROUP_HEADER_LEN * 2 + SPACE * 3; // 530.f
    EXPECT_EQ(pattern_->GetScrollableDistance(), groupHeight * 8 + SPACE * 7 - LIST_HEIGHT); // 3510.f
    int32_t index = 4;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + GROUP_HEADER_LEN
                                  + (ITEM_HEIGHT + SPACE) * indexInGroup - SPACE; // 2380.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 2380.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 2030.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance)); // 2380.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 2030.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
}

/**
 * @tc.name: ScrollToItemInGroup009
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup and lanes > 1
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToItemInGroup009, TestSize.Level1)
{
    /**
     * @tc.cases: Set space and lanes, ScrollTo index:4 indexInGroup:2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    CreateGroupWithSetting(8, V2::ListItemGroupStyle::NONE); // each group height:310.f
    CreateDone(frameNode_);
    float groupHeight = ITEM_HEIGHT * 2 + GROUP_HEADER_LEN * 2 + SPACE; // 310.f
    EXPECT_EQ(pattern_->GetScrollableDistance(), groupHeight * 8 - LIST_HEIGHT); // 1680.f
    int32_t index = 4;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + GROUP_HEADER_LEN + ITEM_HEIGHT + SPACE; // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance));  // 1400.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
}

/**
 * @tc.name: ScrollToItemInGroup010
 * @tc.desc: Test ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup010, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(8);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. index is -2.
     * @tc.expected: not scroll.
     */
    ScrollToItemInGroup(-2, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 400);

    /**
     * @tc.steps: step3. index is -1.
     * @tc.expected: not scroll.
     */
    ScrollToItemInGroup(ListLayoutAlgorithm::LAST_ITEM, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 1);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 400);

    /**
     * @tc.steps: step4. indexInGroup is std::nullopt.
     * @tc.expected: startIndex_ = 0 and endIndex_ = 2.
     */
    ScrollToIndex(1, true, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 300);

    /**
     * @tc.steps: step5. group within the screen.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100);
    EXPECT_EQ(pattern_->itemPosition_[1].endPos, 300);
}

/**
 * @tc.name: ScrollToItemInGroup011
 * @tc.desc: Test ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup011, TestSize.Level1)
{
    const int32_t number = 8;
    CreateList();
    CreateGroupWithItem(number);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. index is item.
     * @tc.expected: not scroll.
     */
    ScrollToItemInGroup(1, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step2. index is greater than list size.
     * @tc.expected: not scroll.
     */
    ScrollToItemInGroup(8, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);

    /**
     * @tc.steps: step3. indexInGroup is greater than item size in group.
     * @tc.expected: not scroll.
     */
    ScrollToItemInGroup(2, 4, true, ScrollAlign::START);
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
 * @tc.name: ScrollToItemInGroup012
 * @tc.desc: Test ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup012, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateGroupWithSetting(8, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);
    ScrollToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);

    ScrollToItemInGroup(2, 1, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);

    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::HEADER);
    ScrollToItemInGroup(2, 1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 2);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -110);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 510);

    ScrollToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 2);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -110);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 510);

    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    ScrollToItemInGroup(2, 1, true, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->startIndex_, 2);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -110);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, 510);

    ScrollToItemInGroup(2, 1, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -220);
    EXPECT_EQ(pattern_->itemPosition_[2].endPos, 400);
}

/**
 * @tc.name: ScrollToItemInGroup013
 * @tc.desc: Test ScrollToItemInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create list.
     */
    ListModelNG model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    CreateListItemGroups(5);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->contentStartOffset_, 50.f);
    EXPECT_EQ(pattern_->contentEndOffset_, 50.f);

    /**
     * @tc.steps: step2. scroll to the last index.
     * @tc.expected: pattern_->itemPosition_[4].endPos == 750.
     */
    ScrollToItemInGroup(4, 1, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 4);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 350);

    ScrollToItemInGroup(4, 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->endIndex_, 4);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -50);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 350);

    ScrollTo(0);
    ScrollToItemInGroup(4, 1, false, ScrollAlign::AUTO);
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
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController001, TestSize.Level1)
{
    const int32_t itemNumber = 20;
    CreateList();
    CreateListItems(itemNumber);
    CreateDone(frameNode_);
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT);
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * VIEW_ITEM_NUMBER);
    controller->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), (itemNumber - VIEW_ITEM_NUMBER) * ITEM_HEIGHT);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT);
    controller->ScrollToIndex(0, false, ScrollAlign::NONE, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step6. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_FALSE(controller->IsAtEnd());

    /**
     * @tc.steps: step7. Test AnimateTo
     */
    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, true));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, true));
    RefPtr<Curve> curve;
    std::string icurveString = "spring(7.000000,1.000000,227.000000,33.000000)";
    curve = Framework::CreateCurve(icurveString);
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
    curve = Curves::EASE_IN;
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: PositionController004
 * @tc.desc: Test GetItemRectInGroup function when set ListItemGroup space
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t itemNumber = 3;
    CreateList();
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone(frameNode_);
    auto controller = AceType::MakeRefPtr<ListPositionController>();
    pattern_->SetPositionController(controller);

    /**
     * @tc.steps: step2. Get invalid ListItemGroup Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    double groupHeight = ITEM_HEIGHT * itemNumber + GROUP_HEADER_LEN * 2 + (itemNumber - 1) * SPACE;
    EXPECT_TRUE(IsEqual(controller->GetItemRect(-1), Rect()));

    /**
     * @tc.steps: step3. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRect(0), Rect(0, 0, FILL_LENGTH.Value() * LIST_WIDTH, groupHeight)));
    /**
     * @tc.steps: step4. Get invalid ListItem Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(0, -1), Rect()));
    for (int32_t j = 0; j < itemNumber; ++j) {
        /**
         * @tc.steps: step5. Get valid ListItem Rect.
         * @tc.expected: Return actual Rect when input valid index.
         */
        double itemY = j * (ITEM_HEIGHT + SPACE) + GROUP_HEADER_LEN;
        EXPECT_TRUE(IsEqual(
            controller->GetItemRectInGroup(0, j), Rect(0, itemY, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    }
    /**
     * @tc.steps: step6. Get invalid ListItem Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(0, itemNumber), Rect()));

    /**
     * @tc.steps: step7. Get invalid ListItemGroup Rect.
     * @tc.expected: Return Rect() when input invalid index.
     */
    EXPECT_TRUE(IsEqual(controller->GetItemRect(1), Rect()));
}

/**
 * @tc.name: PositionController005
 * @tc.desc: Test GetItemRect function when set ListItemGroup space and set List Space
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 2;
    ListModelNG model = CreateList();
    ViewAbstract::SetHeight(CalcLength(800.f)); // for layout items
    model.SetSpace(Dimension(SPACE));
    CreateGroupWithSetting(groupNumber, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone(frameNode_);
    auto controller = AceType::MakeRefPtr<ListPositionController>();
    pattern_->SetPositionController(controller);
    EXPECT_EQ(GetALLItem().size(), 4);
    EXPECT_FLOAT_EQ(layoutProperty_->GetSpaceValue().Value(), SPACE);

    double groupHeight = ITEM_HEIGHT * itemNumber + GROUP_HEADER_LEN * 2 + (itemNumber - 1) * SPACE;
    for (int32_t i = 0; i < groupNumber; ++i) {
        /**
         * @tc.steps: step2. Get valid ListItemGroup Rect.
         * @tc.expected: Return actual Rect when input valid index.
         */
        double groupY = i * (groupHeight + SPACE);
        EXPECT_TRUE(
            IsEqual(controller->GetItemRect(i), Rect(0, groupY, FILL_LENGTH.Value() * LIST_WIDTH, groupHeight)));
        /**
         * @tc.steps: step3. Get invalid ListItem Rect.
         * @tc.expected: Return Rect() when input invalid index.
         */
        EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(i, -1), Rect()));
        for (int32_t j = 0; j < itemNumber; ++j) {
            /**
             * @tc.steps: step4. Get valid ListItem Rect.
             * @tc.expected: Return actual Rect when input valid index.
             */
            double itemY = groupY + j * (ITEM_HEIGHT + SPACE) + GROUP_HEADER_LEN;
            EXPECT_TRUE(IsEqual(
                controller->GetItemRectInGroup(i, j), Rect(0, itemY, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
        }
        /**
         * @tc.steps: step5. Get invalid ListItem Rect.
         * @tc.expected: Return Rect() when input invalid index.
         */
        EXPECT_TRUE(IsEqual(controller->GetItemRectInGroup(i, itemNumber), Rect()));
    }
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
    CreateDone(frameNode_);
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
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_008 = 400.f;
constexpr float OFFSET_TIME_008 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 20 *10;
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
    CreateDone(frameNode_);
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
        FlushLayoutTask(frameNode_);
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
        FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);
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
        FlushLayoutTask(frameNode_);
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
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. bottomOffset > topOffset == 0
     * expected: top Align
     */
    pattern_->ScrollTo(1000);
    FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);
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
        FlushLayoutTask(frameNode_);
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
        FlushLayoutTask(frameNode_);
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
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern002, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);

    pattern_->AnimateTo(1, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(2, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(3, 0, nullptr, false);
    EXPECT_NE(pattern_->curveAnimation_, nullptr);
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
    CreateDone(frameNode_);
    auto listItem = GetChildFrameNode(frameNode_, 5);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    ClearOldNodes();
    CreateList();
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->GetTotalHeight(), TOTAL_ITEM_NUMBER * ITEM_HEIGHT);

    // test ToJsonValue/FromJson
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
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
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. swipe forward 3 listItem
     */
    ScrollTo(3 * LIST_HEIGHT);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step3. swipe backward 2.5 listItem
     */
    pattern_->ScrollBy(-2.5 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, -LIST_HEIGHT / 2.0, LIST_WIDTH, LIST_HEIGHT)));

    /**
     * @tc.steps: step4. swipe forward 3 listItem
     */
    pattern_->ScrollBy(3 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
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
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 400));

    /**
     * @tc.cases: 0 > bottomOffset == topOffset
     * @tc.expected: top Align
     */
    ScrollTo(1200);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1200);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 400));

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
    CreateDone(frameNode_);

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
        FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);

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
        FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);

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
        FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    pattern_->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->endIndex_, 7);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    pattern_->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    pattern_->ScrollPage(false, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 400);

    pattern_->ScrollPage(true, true);
    FlushLayoutTask(frameNode_);
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
    CreateDone(frameNode_);
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
    CreateDone(frameNode_);
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
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(2, 3, { 50.f, 100.f, 200.f });
    childrenSize->ChangeData(15, 3, { 50.f, 100.f, 200.f });
    CreateListItems(2); // ITEM_HEIGHT
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(10);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(3);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(2), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(17), 200.f);

    /**
     * @tc.steps: step2. ScrollToIndex, index:3 is in the view
     */
    int32_t index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 100.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));

    /**
     * @tc.steps: step3. ScrollToIndex, index:17 is out of the view, and will scroll beyond one screen
     */
    index = 17;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1700.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1600.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1500.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1500.f));

    /**
     * @tc.steps: step4. ScrollTo, 400.f is in the view
     */
    ScrollTo(400.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400.f);

    /**
     * @tc.steps: step5. ScrollTo, 1400.f is out of the view
     */
    ScrollTo(1400.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1400.f);
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
    childrenSize->UpdateDefaultSize(200.f);
    childrenSize->ChangeData(1, 2, { 450.f, 450.f });
    childrenSize->ChangeData(4, 1, { 450.f });
    CreateListItemGroups(1);
    CreateGroupChildrenMainSize(2);
    CreateListItemGroups(1);
    CreateGroupChildrenMainSize(1);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. ScrollToIndex, index:1 is in the view
     */
    int32_t index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 225.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 250.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 200.f));

    /**
     * @tc.steps: step3. ScrollToIndex, index:4 is out of the view, and will scroll beyond one screen
     */
    index = 4;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 1300.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 1325.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 1350.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 1300.f));

    /**
     * @tc.steps: step4. ScrollToItemInGroup, index:1 is in the view
     */
    index = 1;
    int32_t indexInGroup = 2;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 350.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 250.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 150.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 150.f));

    /**
     * @tc.steps: step5. ScrollToItemInGroup, index:4 is out of the view
     */
    index = 4;
    indexInGroup = 3;
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 1350.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 1350.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 1350.f));
    EXPECT_TRUE(JumpToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 1350.f));

    /**
     * @tc.steps: step4. ScrollTo, 400.f is in the view
     */
    ScrollTo(400.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400.f);

    /**
     * @tc.steps: step5. ScrollTo, 1400.f is out of the view
     */
    ScrollTo(1400.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1350.f);
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
    childrenSize->UpdateDefaultSize(100.f);
    childrenSize->ChangeData(4, 1, { 530.f });
    childrenSize->ChangeData(5, 1, { 580.f });
    CreateListItems(4);
    CreateGroupWithSetting(1, V2::ListItemGroupStyle::NONE);
    CreateGroupWithSettingChildrenMainSize(1);
    CreateListItems(4);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(4), 530.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(5), 580.f);
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
    EXPECT_EQ(groupPattern->childrenSize_->GetChildSize(1), 50.f);
    endExpect = { 4, 3, -1 };
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. ScrollTo 540
     * @tc.expected: index:5 indexInGroup:2 height == 200
     */
    ScrollTo(540);
    EXPECT_EQ(groupPattern->childrenSize_->GetChildSize(2), 200.f);
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
    model.SetSpace(Dimension(10.f));
    model.SetLanes(2);
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(4, 1, { 200.f });
    childrenSize->ChangeData(9, 1, { 450.f });
    childrenSize->ChangeData(10, 4, { 50.f, 50.f, 200.f, 200.f });
    childrenSize->ChangeData(18, 4, { 50.f, 200.f, 50.f, 200.f });
    CreateListItems(4); // 0~3
    CreateListItemGroups(1);
    CreateListItems(4); // 5~8
    CreateGroupChildrenMainSize(1);
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(4); // 14~17
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(8);
    CreateDone(frameNode_);
    EXPECT_TRUE(JumpToItemInGroup(4, 1, false, ScrollAlign::START, 220));
    EXPECT_TRUE(JumpToItemInGroup(4, 1, false, ScrollAlign::CENTER, 70));
    EXPECT_TRUE(JumpToItemInGroup(4, 1, false, ScrollAlign::END, 0));
    EXPECT_TRUE(JumpToItemInGroup(9, 1, false, ScrollAlign::START, 650));
    EXPECT_TRUE(JumpToItemInGroup(9, 1, false, ScrollAlign::CENTER, 500));
    EXPECT_TRUE(JumpToItemInGroup(9, 1, false, ScrollAlign::END, 350));

    /**
     * @tc.steps: step2. ScrollToIndex 12 / ScrollToIndex 13
     * @tc.expected: GetTotalOffset is right
     */
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(10), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(11), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(12), 200.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(13), 200.f);
    EXPECT_TRUE(ScrollToIndex(10, false, ScrollAlign::START, 1110));
    EXPECT_TRUE(ScrollToIndex(10, false, ScrollAlign::CENTER, 935));
    EXPECT_TRUE(ScrollToIndex(10, false, ScrollAlign::END, 760));
    EXPECT_TRUE(ScrollToIndex(13, false, ScrollAlign::START, 1170));
    EXPECT_TRUE(ScrollToIndex(13, false, ScrollAlign::CENTER, 1070));
    EXPECT_TRUE(ScrollToIndex(13, false, ScrollAlign::END, 970));

    /**
     * @tc.steps: step3. ScrollToIndex 18 / ScrollToIndex 21
     * @tc.expected: GetTotalOffset is right
     */
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(18), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(19), 200.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(20), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(21), 200.f);
    EXPECT_TRUE(ScrollToIndex(18, false, ScrollAlign::START, 1600));
    EXPECT_TRUE(ScrollToIndex(18, false, ScrollAlign::CENTER, 1500));
    EXPECT_TRUE(ScrollToIndex(18, false, ScrollAlign::END, 1400));
    EXPECT_TRUE(ScrollToIndex(21, false, ScrollAlign::START, 1810));
    EXPECT_TRUE(ScrollToIndex(21, false, ScrollAlign::CENTER, 1710));
    EXPECT_TRUE(ScrollToIndex(21, false, ScrollAlign::END, 1610));
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test List model ng ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToEdge001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. ScrollToEdge to bottom
     * @tc.expected: Scroll to bottom
     */
    model.ScrollToEdge(AceType::RawPtr(frameNode_), ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2);

    /**
     * @tc.steps: step2. ScrollToEdge to Top in Axis::NONE
     * @tc.expected: Can not scroll
     */
    pattern_->axis_ = Axis::NONE;
    model.ScrollToEdge(AceType::RawPtr(frameNode_), ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2);
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
    CreateDone(frameNode_);
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
    CreateDone(frameNode_);
    const double x = 1.0;
    const double y = 2.0;
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, y);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), y);
    model.SetScrollBy(AceType::RawPtr(frameNode_), x, 0.0);
    EXPECT_EQ(pattern_->GetTotalOffset(), y);
}
} // namespace OHOS::Ace::NG
