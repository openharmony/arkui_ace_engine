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

namespace OHOS::Ace::NG {

namespace {} // namespace

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
    Create([](ListModelNG model) { CreateItem(20); });
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
     * @tc.cases: List at top, ScrollTo index:6, index:6 item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    Create([](ListModelNG model) { CreateItem(20); });
    int32_t index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * index)); // 600.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER,
                              ITEM_HEIGHT * index - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 250.f
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, ITEM_HEIGHT * index)); // 600.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER,
                              ITEM_HEIGHT * index - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 250.f
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, 0.f));
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
    Create([](ListModelNG model) { CreateItem(20); });
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
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: List at top, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    Create([](ListModelNG model) { CreateItem(20); });
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 12); // 1200.f
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
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
    Create([](ListModelNG model) { CreateItem(20); });
    pattern_->ScrollTo(ITEM_HEIGHT * 8);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 8);
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
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: List at bottom, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    Create([](ListModelNG model) { CreateItem(20); });
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 12); // 1200.f
    EXPECT_TRUE(pattern_->IsAtBottom());
    float scrollableDistance = pattern_->GetScrollableDistance(); // 1200.f
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
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
    Create([](ListModelNG model) { CreateItem(20); });
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
    Create([](ListModelNG model) {
        model.SetSpace(Dimension(SPACE)); // 10.f
        CreateItem(20);
    });
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 12 + SPACE * 19); // 1200.f + 190.f
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
     * @tc.cases: Set lanes, ScrollTo index:17, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(20);
    });
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 2); // 200.f
    int32_t index = 17;
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
    Create([](ListModelNG model) {
        CreateGroupWithSetting(5, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); // each group height:530.f
    });
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
HWTEST_F(ListScrollerTestNg, DISABLED_ScrollToIndex011, TestSize.Level1)
{
    int32_t itemNumber = 20;
    Create([itemNumber](ListModelNG model) { CreateItem(itemNumber); });
    EXPECT_EQ(frameNode_->GetChildren().size(), itemNumber);
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 12); // 1200.f

    /**
     * @tc.steps: step1. Scroll to finally listItem.
     * @tc.expected: check whether the properties is correct.
     */
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
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
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 13); // 1300.f

    /**
     * @tc.steps: step3. Scroll to finally listItem.
     * @tc.expected: check whether the properties is correct.
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, ITEM_HEIGHT * 24); // 2400.f
    EXPECT_TRUE(pattern_->IsAtTop());
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    int32_t index = 1;
    int32_t indexInGroup = 1;
    float groupHeight = GROUP_LINE_NUMBER * ITEM_HEIGHT; // 400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START,
                                    groupHeight * index + ITEM_HEIGHT * indexInGroup)); // 500.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    ITEM_HEIGHT * (indexInGroup + 0.5))); // 150.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START,
                                    groupHeight * index + ITEM_HEIGHT * indexInGroup)); // 500.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    ITEM_HEIGHT * (indexInGroup + 0.5))); // 150.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    float groupHeight = GROUP_LINE_NUMBER * ITEM_HEIGHT; // 400.f
    int32_t index = 3;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + ITEM_HEIGHT * indexInGroup; // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
    int32_t indexInGroup = 3;
    float scrollableDistance = pattern_->GetScrollableDistance(); // 2400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, scrollableDistance));
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    pattern_->ScrollTo(ITEM_HEIGHT * 8);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 8);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
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
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 24);
    EXPECT_TRUE(pattern_->IsAtBottom());
    int32_t index = ListLayoutAlgorithm::LAST_ITEM;
    int32_t indexInGroup = 3;
    float scrollableDistance = pattern_->GetScrollableDistance(); // 2400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, scrollableDistance));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, scrollableDistance));
}

/**
 * @tc.name: ScrollToItemInGroup007
 * @tc.desc: Test ScrollToItemInGroup with ListItemGroup and indexInGroup invalid
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ScrollToItemInGroup007, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo invalid index:4 indexInGroup:-2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    Create([](ListModelNG model) { CreateGroup(8); }); // each group height is 400.f
    int32_t index = 4;
    int32_t indexInGroup = -2;
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO, 0.f));
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
    Create([](ListModelNG model) {
        model.SetSpace(Dimension(SPACE)); // 10.f
        CreateGroupWithSetting(8, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); // each group height:530.f
    });
    float groupHeight = ITEM_HEIGHT * 4 + GROUP_HEADER_LEN * 2 + SPACE * 3; // 530.f
    EXPECT_EQ(pattern_->GetScrollableDistance(), groupHeight * 8 + SPACE * 7 - LIST_HEIGHT); // 3510.f
    int32_t index = 4;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + GROUP_HEADER_LEN
                                  + (ITEM_HEIGHT + SPACE) * indexInGroup - SPACE; // 2380.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 2380.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 2030.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance)); // 2380.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 2030.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - LIST_HEIGHT + ITEM_HEIGHT)); // 1680.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
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
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateGroupWithSetting(8, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); // each group height:310.f
    });
    float groupHeight = ITEM_HEIGHT * 2 + GROUP_HEADER_LEN * 2 + SPACE; // 310.f
    EXPECT_EQ(pattern_->GetScrollableDistance(), groupHeight * 8 - LIST_HEIGHT); // 1680.f
    int32_t index = 4;
    int32_t indexInGroup = 2;
    float scrollToStartDistance = groupHeight * index + GROUP_HEADER_LEN + ITEM_HEIGHT + SPACE; // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::START, scrollToStartDistance)); // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, false, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::START, scrollToStartDistance));  // 1400.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::CENTER,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2)); // 1050.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::END,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
    EXPECT_TRUE(ScrollToItemInGroup(index, indexInGroup, true, ScrollAlign::AUTO,
                                    scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT))); // 700.f
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController001, TestSize.Level1)
{
    const int32_t itemNumber = 20;
    Create([itemNumber](ListModelNG model) { CreateItem(itemNumber); });
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
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT * VIEW_LINE_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEW_LINE_NUMBER) * ITEM_HEIGHT));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->JumpTo(1, false, ScrollAlign::START, 0);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));
    controller->JumpTo(0, false, ScrollAlign::NONE, 0);
    EXPECT_TRUE(IsEqualTotalOffset(0));

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
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController function with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController002, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    Create([itemNumber](ListModelNG model) {
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(itemNumber, Axis::HORIZONTAL);
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    controller->ScrollBy(-ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH * VIEW_LINE_NUMBER));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualTotalOffset((itemNumber - VIEW_LINE_NUMBER) * ITEM_WIDTH));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_WIDTH));
    controller->JumpTo(0, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step6. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_FALSE(controller->IsAtEnd());
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, PositionController003, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) { model.SetListDirection(Axis::NONE); });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::NONE);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    /**
     * @tc.steps: step2. Test others
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_FALSE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
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
    int32_t itemNumber = 6;
    Create([=](ListModelNG model) {
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
    });
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
    int32_t itemNumber = 3;
    Create([=](ListModelNG model) {
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
        model.SetSpace(Dimension(SPACE));
    });
    auto controller = AceType::MakeRefPtr<ListPositionController>();
    pattern_->SetPositionController(controller);
    EXPECT_EQ(GetALLItem().size(), 6);
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

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. has no listItem
     */
    Create([](ListModelNG model) {});
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. unscrollable List
     */
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step3. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateWithItem([](ListModelNG model) {});
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step4. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER); });
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), -350.f);
    UpdateCurrentOffset(-ITEM_HEIGHT * 8, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), 450.f);
}

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event001, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger](Dimension offset, ScrollState state) { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnScroll(event); });

    /**
     * @tc.steps: step1. Cover condition that GetMinPlatformVersion() >= 10  && scrollStop_ && !GetScrollAbort()
     */
    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Cover condition that onScroll && !NearZero(finalOffset)
     */
    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // SetMinPlatformVersion
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // set back
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
}

/**
 * @tc.name: Event002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event002, TestSize.Level1)
{
    int32_t startIndex;
    int32_t endIndex;
    int32_t centerIndex;
    auto event = [&startIndex, &endIndex, &centerIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
        centerIndex = center;
    };
    CreateWithItem([event](ListModelNG model) { model.SetOnScrollIndex(event); });

    ScrollDown();
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 8);
    EXPECT_EQ(centerIndex, 4);

    ScrollDown();
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 9);
    EXPECT_EQ(centerIndex, 5);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnReachStart(event); });

    /**
     * @tc.steps: step1. list first init will trigger ReachStart.
     */
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    isTrigger = false;
    ScrollDown();
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step3. Scroll up half item.
     */
    UpdateCurrentOffset(ITEM_HEIGHT / 2.0f);

    /**
     * @tc.steps: step4. Scroll up to start
     */
    isTrigger = false;
    ScrollUp(2);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    CreateWithItem([event](ListModelNG model) { model.SetOnReachEnd(event); });

    /**
     * @tc.steps: step1. Scroll down to end
     */
    ScrollDown(3);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event005, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    CreateWithItem([scrollStart, scrollStop](ListModelNG model) {
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
        model.SetOnScrollStart(scrollStart);
        model.SetOnScrollStop(scrollStop);
    });

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);

    isScrollStopCalled = false;
    pattern_->OnScrollEndCallback();
    pattern_->SetScrollAbort(true);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Event006, TestSize.Level1)
{
    auto event = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    CreateWithItem([event](ListModelNG model) { model.SetOnScrollFrameBegin(event); });

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    auto scrollable = scrollableEvent->GetScrollable();
    EXPECT_NE(scrollable->callback_, nullptr);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern002, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});

    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(0, 0, nullptr, false);
    EXPECT_NE(pattern_->curveAnimation_, nullptr);
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern005, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        model.SetChainAnimation(true);
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
        CreateItemWithSwipe(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    });

    // Set swiperItem_ to list pattern
    DragSwiperItem(0, 1.f);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_TRUE(pattern_->AnimateStoped());
    double offset = 100.0;
    pattern_->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_FALSE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_FALSE(pattern_->scrollAbort_);
    EXPECT_TRUE(IsEqualTotalOffset(0));
    EXPECT_TRUE(pattern_->AnimateStoped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_HEIGHT);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();

    pattern_->OnScrollCallback(850.f, SCROLL_FROM_START);
    EXPECT_EQ(pattern_->chainAnimation_->GetControlIndex(), 7);
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern012, TestSize.Level1)
{
    // test ScrollToNode
    CreateWithItem([](ListModelNG model) {});
    auto listItem = GetChildFrameNode(frameNode_, 8);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    Create([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);
    CreateWithItem([](ListModelNG model) {});
    EXPECT_EQ(pattern_->GetTotalHeight(), TOTAL_LINE_NUMBER * ITEM_HEIGHT);

    // test ToJsonValue/FromJson
    CreateWithItem([](ListModelNG model) {});
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json);
    EXPECT_EQ(json->GetBool("multiSelectable"), false);
    EXPECT_EQ(json->GetInt("startIndex"), 0);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 0.0);
    EXPECT_EQ(json->GetDouble("friction"), DEFAULT_FRICTION);
    pattern_->FromJson(json);
    EXPECT_TRUE(IsEqualTotalOffset(0));
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
    Create([=](ListModelNG model) {
        CreateItemWithSize(itemNumber, itemSize);
        model.SetListDirection(Axis::VERTICAL);
        model.SetScrollBar(DisplayMode::OFF);
    });

    /**
     * @tc.steps: step2. swipe forward 3 listItem
     */
    pattern_->ScrollTo(3 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
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
    pattern_->ScrollTo(LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(1), Rect(0, 0, LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, Pattern014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::NONE, true);
    });

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
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::FADE, false);
    });

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
    /**
     * @tc.steps: step1. create List
     */
    int32_t itemNumber = 20;
    Create([=](ListModelNG model) {
        CreateItem(itemNumber);
        model.SetScrollBar(DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });

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
 * @tc.name: ListPattern_UpdateScrollSnap001
 * @tc.desc: Test UpdateScrollSnap.
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerTestNg, ListPattern_UpdateScrollSnap001, TestSize.Level1)
{
    CreateWithItem([](ListModelNG model) {});
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->UpdateScrollSnap();
    EXPECT_TRUE(pattern_->predictSnapOffset_.has_value());

    pattern_->StopAnimate();
    pattern_->UpdateScrollSnap();
    EXPECT_EQ(pattern_->predictSnapOffset_.value(), 0.0);
}
} // namespace OHOS::Ace::NG
