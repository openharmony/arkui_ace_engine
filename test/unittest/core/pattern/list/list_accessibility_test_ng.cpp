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

#include "core/animation/velocity_motion.h"
#include "core/components_ng/pattern/list/list_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_accessibility_property.h"

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

/**
 * @tc.name: ListA11ySourceUserSwipe001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="user" for swipe gesture
 *           (SCROLL_FROM_UPDATE) in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceUserSwipe001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Perform drag action (SCROLL_FROM_UPDATE) to trigger user scroll.
     * @tc.expected: SCROLL_END event with scrollSource="user" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    DragAction(frameNode_, Offset(0, HEIGHT / 2), -ITEM_MAIN_SIZE, 0);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "user");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: ListA11ySourceApiAnimateTo001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for AnimateTo in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceApiAnimateTo001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger non-smooth AnimateTo to scroll.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }

    /**
     * @tc.steps: step2. Trigger smooth AnimateTo to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        AnimateTo(Dimension(ITEM_MAIN_SIZE * 2), 1000.0f, nullptr, true);
        TickToFinish();
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }
}

/**
 * @tc.name: ListA11ySourceApiScrollToIndex001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for ScrollToIndex in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceApiScrollToIndex001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger non-smooth ScrollToIndex to scroll.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        ScrollToIndex(5, false, ScrollAlign::CENTER);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }

    /**
     * @tc.steps: step2. Trigger smooth ScrollToIndex to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        ScrollToIndex(10, false, ScrollAlign::CENTER);
        TickToFinish();
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }
}

/**
 * @tc.name: ListA11ySourceApiScrollToEdge001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for ScrollToEdge in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceApiScrollToEdge001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger non-smooth ScrollToEdge to scroll.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }

    /**
     * @tc.steps: step2. Trigger smooth ScrollToEdge to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
        EXPECT_TRUE(pattern_->fixedVelocityMotion_);
        EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
        int32_t offsetTime = OFFSET_TIME;
        for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
            pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
            offsetTime = offsetTime + OFFSET_TIME;
            FlushUITasks(frameNode_);
        }
        EXPECT_TRUE(pattern_->IsAtTop());
        // Manually driving OnTimestampChanged does not trigger the animation's finish callback,
        // so OnAnimateStop is called to set scrollStop_=true, then flush layout
        // to trigger OnScrollStop->SCROLL_END.
        pattern_->OnAnimateStop();
        FlushUITasks(frameNode_);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }
}

/**
 * @tc.name: ListA11ySourceApiScrollPage001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for smooth ScrollPage in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceApiScrollPage001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger smooth ScrollPage to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    ScrollPage(false, true);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: ListA11ySourceApiScrollToItemInGroup001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for ScrollToItemInGroup in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceApiScrollToItemInGroup001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateGroupWithSetting(GROUP_NUMBER, V2::ListItemGroupStyle::NONE);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger non-smooth ScrollToItemInGroup to scroll.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        JumpToItemInGroup(1, 0, false, ScrollAlign::START);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }

    /**
     * @tc.steps: step2. Trigger smooth ScrollToItemInGroup to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    {
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        JumpToItemInGroup(2, 0, true, ScrollAlign::CENTER);
        TickToFinish();
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }
}

/**
 * @tc.name: ListA11ySourceAccessibilityForward001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="accessibility" for
 *           ActActionScrollForward in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceAccessibilityForward001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger ActActionScrollForward.
     * @tc.expected: SCROLL_END event with scrollSource="accessibility" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    accessibilityProperty_->ActActionScrollForward();
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "accessibility");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: ListA11ySourceAccessibilityBackward001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="accessibility" for
 *           ActActionScrollBackward in List.
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceAccessibilityBackward001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger ActActionScrollBackward.
     * @tc.expected: SCROLL_END event with scrollSource="accessibility" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    accessibilityProperty_->ActActionScrollBackward();
    TickToFinish();
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "accessibility");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: ListA11ySourceScrollOffsetAbility001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"] for GetScrollOffsetAbility in List.
 *           scrollable=true expects "accessibility", scrollable=false expects "user".
 * @tc.type: FUNC
 */
HWTEST_F(ListAccessibilityTestNg, ListA11ySourceScrollOffsetAbility001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. GetScrollOffsetAbility(scrollable=true) triggers scroll via scrollFunc.
     * @tc.expected: SCROLL_END event with scrollSource="accessibility" is fired.
     */
    {
        auto scrollOffsetAbility = pattern_->GetScrollOffsetAbility(true);
        ASSERT_TRUE(scrollOffsetAbility.scrollFunc);
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        EXPECT_TRUE(scrollOffsetAbility.scrollFunc(-ITEM_MAIN_SIZE));
        FlushUITasks(frameNode_);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "accessibility");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }

    /**
     * @tc.steps: step2. GetScrollOffsetAbility(scrollable=false) triggers scroll via scrollFunc.
     * @tc.expected: SCROLL_END event with scrollSource="user" is fired.
     */
    {
        auto scrollOffsetAbility = pattern_->GetScrollOffsetAbility(false);
        ASSERT_TRUE(scrollOffsetAbility.scrollFunc);
        auto captured = CaptureSendAccessibilityEventInfo(pipeline);
        EXPECT_TRUE(scrollOffsetAbility.scrollFunc(-ITEM_MAIN_SIZE));
        FlushUITasks(frameNode_);
        EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
        EXPECT_EQ(captured->extraEventInfo["scrollSource"], "user");
        EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
    }
}
} // namespace OHOS::Ace::NG
