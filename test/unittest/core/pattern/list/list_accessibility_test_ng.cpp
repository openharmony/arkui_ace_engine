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
class ListAccessibilityTestNg : public ListTestNg {
protected:
    void TearDown() override;
    void GetList() override;

    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};

void ListAccessibilityTestNg::TearDown()
{
    ListTestNg::TearDown();
    accessibilityProperty_ = nullptr;
}

void ListAccessibilityTestNg::GetList()
{
    ListTestNg::GetList();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func at different position
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scrollable List
     */
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 3);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_ITEM_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 4);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction at different position
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, AccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scroll to Top.
     */
    CreateList();
    CreateListItems();
    CreateDone();
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    ScrollTo(ITEM_MAIN_SIZE);
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_FORWARD, AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test List AccessibilityProperty in unScrollable List
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, AccessibilityProperty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create unScrollable List
     */
    CreateList();
    CreateListItems(2);
    CreateDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 2);

    /**
     * @tc.steps: step2. Actions is 0
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. Could not scrollPage
     */
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, AccessibilityProperty004, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    auto itemAccessibilityProperty = GetChildAccessibilityProperty<ListItemAccessibilityProperty>(frameNode_, 0);
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    itemAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SELECT, AceAction::ACTION_CLEAR_SELECTION };
    EXPECT_EQ(itemAccessibilityProperty->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: AccessibilityProperty005
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, AccessibilityProperty005, TestSize.Level1)
{
    CreateList();
    CreateGroupWithSetting(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    auto groupAccessibilityProperty = GetChildAccessibilityProperty<ListItemGroupAccessibilityProperty>(frameNode_, 0);
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 1);

    groupAccessibilityProperty = GetChildAccessibilityProperty<ListItemGroupAccessibilityProperty>(frameNode_, 3);
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), -1);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), -1);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ListItem AccessibilityPerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateList();
    CreateListItems(2);
    CreateDone();
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, 0);
    auto listItemAccessibilityProperty = GetChildAccessibilityProperty<ListItemAccessibilityProperty>(frameNode_, 0);

    /**
     * @tc.steps: step1. When listItem is unSelectable
     * @tc.expected: Could not be selected
     */
    listItemPattern->SetSelectable(false);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When listItem is Selectable
     * @tc.expected: Could be selected
     */
    listItemPattern->SetSelectable(true);
    listItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(listItemPattern->IsSelected());
    listItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(listItemPattern->IsSelected());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: List AccessibilityPerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When list is Scrollable
     * @tc.expected: Could scrollPage
     */
    CreateList();
    CreateListItems();
    CreateDone();
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(-HEIGHT));

    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(0));
}
} // namespace OHOS::Ace::NG
