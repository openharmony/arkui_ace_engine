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

#include "tabs_test_ng.h"

#include "core/components_ng/pattern/tabs/tab_bar_item_accessibility_property.h"

namespace OHOS::Ace::NG {
class TabsAccessibilityTestNg : public TabsTestNg {};

/**
 * @tc.name: TabBarAccessibilityProperty001
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, TabBarAccessibilityProperty001, TestSize.Level1)
{
    const int32_t itemNumber = 5;
    TabsModelNG model = CreateTabs();
    ViewAbstract::SetWidth(CalcLength(BAR_ITEM_SIZE * (itemNumber - 2)));
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContentsWithBuilder(itemNumber);
    CreateTabsDone(model);
    EXPECT_TRUE(tabBarAccessibilityProperty_->IsScrollable());
    EXPECT_TRUE(tabBarPattern_->CanScroll());

    /**
     * @tc.steps: step1. TabBar at top
     */
    EXPECT_TRUE(tabBarPattern_->IsAtTop());
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());

    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step2. TabBar at middle
     */
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward(); // scroll to middle
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 1), 0);
    EXPECT_FALSE(tabBarPattern_->IsAtTop());
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());

    tabBarAccessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_FORWARD, AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. TabBar at bottom
     */
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward(); // scroll to end
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 0);
    EXPECT_FALSE(tabBarPattern_->IsAtTop());
    EXPECT_TRUE(tabBarPattern_->IsAtBottom());

    tabBarAccessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step4. Set tabs width to make unScrollable
     * @tc.expected: UnScrollable even if TabBarMode::SCROLLABLE
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(TABS_WIDTH));
    FlushUITasks();
    EXPECT_TRUE(tabBarPattern_->IsAtTop());
    EXPECT_TRUE(tabBarPattern_->IsAtBottom());

    tabBarAccessibilityProperty_->ResetSupportAction();
    expectedActions = {};
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TabBar AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.desc: Has no effect when TabBarMode is FIXED
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set TabBarMode
     * @tc.expected: TabBarMode default is FIXED, the tabBar is unScrollable
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. Check some info
     */
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), TABCONTENT_NUMBER);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), TABCONTENT_NUMBER - 1);

    ChangeIndex(1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step3. Check some info
     */
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: TabBar AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.desc: Has no effect when there is no child component
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. There is no child component
     * @tc.expected: The tabBar is unScrollable,
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabsDone(model);
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. Check some info
     */
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), -1); // default
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), -1);

    /**
     * @tc.steps: step3. Check some info
     */
    EXPECT_FALSE(tabBarPattern_->IsAtTop());
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest003
 * @tc.desc: TabBar AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, PerformActionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TabBarMode::SCROLLABLE and Set tabs width to make tabBar scrollable
     * @tc.expected: The tabBar is scrollable
     */
    const int32_t itemNumber = 5;
    const float margin = 2.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(margin);
    TabsModelNG model = CreateTabs();
    ViewAbstract::SetWidth(CalcLength(BAR_ITEM_SIZE * (itemNumber - 2)));
    model.SetScrollableBarModeOptions(option);
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContentsWithBuilder(itemNumber);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. ScrollForward, check tabBar scroll position
     * @tc.expected: Check index:2 item position, because the item is always visible
     */
    // index 0
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 22.0f);
    // index 1
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 10.0f);
    // index 2
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), -2.0f);
    // index 3
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), -2.0f);

    /**
     * @tc.steps: step3. ScrollBackward, check tabBar scroll position
     * @tc.expected: Check index:2 item position, because the item is always visible
     */
    // index 3
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 10.0f);
    // index 2
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 22.0f);
    // index 1
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 22.0f);
}

/**
 * @tc.name: PerformActionTest004
 * @tc.desc: TabBar AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.desc: Test in RTL layout
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, PerformActionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Make tabBar scrollable and Set RTL layout
     * @tc.expected: The tabBar is scrollable direction is reversed
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    const int32_t itemNumber = 5;
    const float margin = 2.0f;
    ScrollableBarModeOptions option;
    option.margin = Dimension(margin);
    TabsModelNG model = CreateTabs();
    ViewAbstract::SetWidth(CalcLength(BAR_ITEM_SIZE * (itemNumber - 2)));
    model.SetScrollableBarModeOptions(option);
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContentsWithBuilder(itemNumber);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. ScrollForward, check tabBar scroll position
     * @tc.expected: Check index:2 item position, because the item is always visible
     */
    // index 0
    EXPECT_EQ(GetChildX(tabBarNode_, 2), -2.0f);
    // index 1
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 10.0f);
    // index 2
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 22.0f);
    // index 3
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.rbegin()->first;
    tabBarAccessibilityProperty_->ActActionScrollForward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 22.0f);

    /**
     * @tc.steps: step3. ScrollBackward, check tabBar scroll position
     * @tc.expected: Check index:2 item position, because the item is always visible
     */
    // index 3
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 10.0f);
    // index 2
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), -2.0f);
    // index 1
    tabBarPattern_->accessibilityFocusIndicator_ = tabBarPattern_->visibleItemPosition_.begin()->first;
    tabBarAccessibilityProperty_->ActActionScrollBackward();
    FlushUITasks();
    EXPECT_EQ(GetChildX(tabBarNode_, 2), -2.0f);
}

/**
 * @tc.name: TabBarItemAccessibilityProperty001
 * @tc.desc: Test TabBarItemAccessibilityProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, TabBarItemAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with items.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Call ToJsonValue function.
     * @tc.expected: label is default tab bar name.
     */
    auto accessibilityProperty = GetChildAccessibilityProperty<TabBarItemAccessibilityProperty>(tabBarNode_, 0);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    accessibilityProperty->ToJsonValue(json, filter);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    EXPECT_EQ(json->GetString("label"), tabTheme->GetDefaultTabBarName());
}

/**
 * @tc.name: TabBarItemAccessibilityProperty002
 * @tc.desc: Test TabBarItemAccessibilityProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, TabBarItemAccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with builder.
     */
    TabsModelNG model = CreateTabs();
    const std::string textTest = "text_test";
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabBarItemFunc = []() {
        TextModelNG model;
        const std::u16string textU16Test = u"text_test";
        model.Create(textU16Test);
    };
    tabContentModel.SetTabBar(textTest, "", std::nullopt, std::move(tabBarItemFunc), true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Call ToJsonValue function.
     * @tc.expected: check label value.
     */
    auto accessibilityProperty = GetChildAccessibilityProperty<TabBarItemAccessibilityProperty>(tabBarNode_, 0);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    accessibilityProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("label"), textTest);
}

/**
 * @tc.name: TabsAccessibilityZIndex001
 * @tc.desc: Test ZIndex AccessibilityZIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAccessibilityTestNg, TabsAccessibilityZIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with builder.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    const std::string textTest = "text_test";
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabBarItemFunc = []() {
        TextModelNG model;
        const std::u16string textU16Test = u"text_test";
        model.Create(textU16Test);
    };
    tabContentModel.SetTabBar(textTest, "", std::nullopt, std::move(tabBarItemFunc), true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. default zIndex.
     * @tc.expected: swiper is -1, divider is -1 and tabBar is -1.
     */
    auto swiperAccessibilityProperty = swiperNode_->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_EQ(swiperAccessibilityProperty->GetAccessibilityZIndex(), -1);
    auto dividerAccessibilityProperty = dividerNode_->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_EQ(dividerAccessibilityProperty->GetAccessibilityZIndex(), -1);
    auto tabBarAccessibilityProperty = tabBarNode_->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_EQ(tabBarAccessibilityProperty->GetAccessibilityZIndex(), -1);

    /**
     * @tc.steps: step2. barPosition changes START.
     * @tc.expected: swiper is 1, divider is -1 and tabBar is 0.
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::START);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(swiperAccessibilityProperty->GetAccessibilityZIndex(), 1);
    EXPECT_EQ(dividerAccessibilityProperty->GetAccessibilityZIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty->GetAccessibilityZIndex(), 0);

    /**
     * @tc.steps: step3. barPosition changes END.
     * @tc.expected: swiper is 0, divider is -1 and tabBar is 1.
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(swiperAccessibilityProperty->GetAccessibilityZIndex(), 0);
    EXPECT_EQ(dividerAccessibilityProperty->GetAccessibilityZIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty->GetAccessibilityZIndex(), 1);
}
} // namespace OHOS::Ace::NG
