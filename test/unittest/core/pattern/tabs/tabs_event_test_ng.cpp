/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"

#include "base/error/error_code.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabsEventTestNg : public TabsTestNg {
public:
    AssertionResult VerifyBackgroundColor(int32_t itemIndex, Color expectColor)
    {
        Color actualColor = GetChildFrameNode(tabBarNode_, itemIndex)->GetRenderContext()->GetBackgroundColor().value();
        if (NearEqual(actualColor, expectColor)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actualColor.ToString() << " Expected: " << expectColor.ToString();
    }
};

/**
 * @tc.name: TabsController001
 * @tc.desc: Test Tabs controller
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabsController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Show first tabContent by default
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step2. SwipeTo second tabContent
     * @tc.expected: Show second tabContent
     */
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);

    /**
     * @tc.steps: step3. SwipeTo same tabContent
     * @tc.expected: Show second tabContent
     */
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);

    /**
     * @tc.steps: step4. SwipeTo index that greater than maxIndex
     * @tc.expected: Show first tabContent
     */
    SwipeToWithoutAnimation(TABCONTENT_NUMBER);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step5. SwipeTo index that less than zero
     * @tc.expected: Show first tabContent
     */
    SwipeToWithoutAnimation(-1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: OnTabBarClick001
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Click tabBar
     * @tc.expected: OnTabBarClick was triggered
     */
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnTabBarClick(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: OnContentWillChange001
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnContentWillChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Click tabBar
     * @tc.expected: OnTabBarClick was triggered
     */
    bool isTrigger = false;
    auto event = [&isTrigger](int32_t, int32_t) {
        isTrigger = true;
        return true;
    };
    TabsModelNG model = CreateTabs();
    model.SetOnContentWillChange(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: OnContentWillChange002
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnContentWillChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Click tabBar, event return false
     * @tc.expected: OnTabBarClick was triggered, but do not swipe
     */
    bool isTrigger = false;
    auto event = [&isTrigger](int32_t, int32_t) {
        isTrigger = true;
        return false;
    };
    TabsModelNG model = CreateTabs();
    model.SetOnContentWillChange(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: OnContentWillChange003
 * @tc.desc: test onContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnContentWillChange003, TestSize.Level1)
{
    auto callback = [](int32_t currentIndex, int32_t comingIndex) -> bool { return true; };
    TabsModelNG model = CreateTabs();
    model.SetOnContentWillChange(std::move(callback));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(pattern_->GetInterceptStatus());

    auto ret = pattern_->OnContentWillChange(CURRENT_INDEX, BEGIN_INDEX);
    EXPECT_TRUE(ret.value());
    EXPECT_TRUE(swiperPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(swiperPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
}

/**
 * @tc.name: onAnimationStartEnd001
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, onAnimationStartEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Swipe with animation
     * @tc.expected: animation event was triggered
     */
    bool isStartTrigger = false;
    auto startEvent = [&isStartTrigger](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isStartTrigger = true;
    };
    bool isEndTrigger = false;
    auto endEvent = [&isEndTrigger](int32_t index, const AnimationCallbackInfo& info) { isEndTrigger = true; };
    TabsModelNG model = CreateTabs();
    model.SetAnimationDuration(1000.f); // open animation
    model.SetOnAnimationStart(startEvent);
    model.SetOnAnimationEnd(endEvent);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(isStartTrigger);
    EXPECT_TRUE(isEndTrigger);
    SwipeToWithoutAnimation(1);
}

/**
 * @tc.name: onAnimationStartEnd002
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, onAnimationStartEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Swap event
     * @tc.expected: event was swaped
     */
    bool isStartTrigger = false;
    auto startEvent = [&isStartTrigger](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isStartTrigger = true;
    };
    bool isEndTrigger = false;
    auto endEvent = [&isEndTrigger](int32_t index, const AnimationCallbackInfo& info) { isEndTrigger = true; };
    bool isStartTrigger2 = false;
    auto startEvent2 = [&isStartTrigger2](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isStartTrigger2 = true;
    };
    bool isEndTrigger2 = false;
    auto endEvent2 = [&isEndTrigger2](int32_t index, const AnimationCallbackInfo& info) { isEndTrigger2 = true; };
    TabsModelNG model = CreateTabs();
    model.SetAnimationDuration(1000.f); // open animation
    model.SetOnAnimationStart(startEvent);
    model.SetOnAnimationEnd(endEvent);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    pattern_->SetAnimationStartEvent(std::move(startEvent2));
    pattern_->SetAnimationEndEvent(std::move(endEvent2));
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_FALSE(isStartTrigger);
    EXPECT_FALSE(isEndTrigger);
    EXPECT_TRUE(isStartTrigger2);
    EXPECT_TRUE(isEndTrigger2);
}

/**
 * @tc.name: HandleClick001
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When SourceType::KEYBOARD
     * @tc.expected: Can not swipe
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    GestureEvent info;
    info.SetLocalLocation(Offset(200.f, 30.f));
    info.SetSourceDevice(SourceType::KEYBOARD);
    tabBarPattern_->HandleClick(info.GetSourceDevice(), 1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
}

/**
 * @tc.name: HandleClick002
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleClick002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has no item
     * @tc.expected: Can not swipe
     */
    TabsModelNG model = CreateTabs();
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleClick003
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleClick003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When only one item
     * @tc.expected: Can not swipe
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    HandleClick(Offset(200.f, 30.f), 1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleClick004
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleClick004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When SpringAnimation is not stoped
     * @tc.expected: Stop SpringAnimation
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->GetSpringProperty();
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(scrollable->IsSpringStopped());
}

/**
 * @tc.name: HandleClick005
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleClick005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. HandleSubTabBarClick
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    HandleClick(Offset(400.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicatorValue(), 1);
}

/**
 * @tc.name: HandleMouseTouch001
 * @tc.desc: Hover on the tabBar when empty items, hoverIndex_ is null
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty items and hove tabBar
     * @tc.expected: hoverIndex_ has no value
     */
    TabsModelNG model = CreateTabs();
    CreateTabsDone(model);
    HandleMouseEvent(MouseAction::MOVE, Offset(100.f, 30.f));
    HandleHoverEvent(true);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
}

/**
 * @tc.name: HandleMouseTouch0021
 * @tc.desc: Move mouse from left to right on the tabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(2);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Move mouse at outside
     * @tc.expected: hoverIndex_ has no value
     */
    const float inTabBarItemY = 30.f;
    HandleMouseEvent(MouseAction::MOVE, Offset(-1.f, inTabBarItemY));
    HandleHoverEvent(false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());

    /**
     * @tc.steps: step2. Move mouse to tabBarItem(index:0)
     * @tc.expected: hoverIndex_ is 0, change color
     */
    HandleMouseEvent(MouseAction::WINDOW_ENTER, Offset(180.f, inTabBarItemY));
    HandleHoverEvent(true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 0);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::RED));

    /**
     * @tc.steps: step3. Still in tabBarItem(index:0)
     * @tc.expected: Not change
     */
    HandleMouseEvent(MouseAction::WINDOW_ENTER, Offset(200.f, inTabBarItemY));
    HandleHoverEvent(true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 0);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::RED));

    /**
     * @tc.steps: step4. Move mouse to tabBarItem(index:1)
     * @tc.expected: hoverIndex_ is 1, change color
     */
    HandleMouseEvent(MouseAction::MOVE, Offset(540.f, inTabBarItemY));
    HandleHoverEvent(true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::TRANSPARENT));
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::RED));

    /**
     * @tc.steps: step5. Move mouse to outside
     * @tc.expected: hoverIndex_ has no value, change color
     */
    HandleMouseEvent(MouseAction::WINDOW_LEAVE, Offset(TABS_WIDTH + 1.f, inTabBarItemY));
    HandleHoverEvent(false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::TRANSPARENT));
}

/**
 * @tc.name: HandleMouseTouch003
 * @tc.desc: Move mouse from top to bottom on the tabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(2);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Move mouse at outside
     * @tc.expected: hoverIndex_ has no value
     */
    const float mouseX = 180.f;
    HandleMouseEvent(MouseAction::MOVE, Offset(mouseX, -1.f));
    HandleHoverEvent(false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());

    /**
     * @tc.steps: step2. Move mouse to tabBarItem(index:0)
     * @tc.expected: hoverIndex_ is 0, change color
     */
    const float inTabBarItemY = 30.f;
    HandleMouseEvent(MouseAction::WINDOW_ENTER, Offset(mouseX, inTabBarItemY));
    HandleHoverEvent(true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 0);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::RED));

    /**
     * @tc.steps: step3. Move mouse to outside
     * @tc.expected: hoverIndex_ has no value, change color
     */
    HandleMouseEvent(MouseAction::WINDOW_LEAVE, Offset(mouseX, 100.f));
    HandleHoverEvent(false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::TRANSPARENT));
}

/**
 * @tc.name: HandleMouseTouch004
 * @tc.desc: hover tabBarItem, touch down and touch up
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(2);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Hover and Touch down at outSide
     * @tc.expected: touchingIndex_ has no value
     */
    const float inTabBarItemY = 30.f;
    HandleMouseEvent(MouseAction::MOVE, Offset(-1.f, inTabBarItemY));
    HandleHoverEvent(true);
    HandleTouchEvent(TouchType::DOWN, Offset(-1.f, inTabBarItemY));
    EXPECT_FALSE(tabBarPattern_->touchingIndex_.has_value());

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:0)
     * @tc.expected: touchingIndex_ is 0, BackgroundColor change to press color
     */
    HandleMouseEvent(MouseAction::MOVE, Offset(180.f, inTabBarItemY));
    HandleHoverEvent(true);
    HandleTouchEvent(TouchType::DOWN, Offset(180.f, inTabBarItemY));
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 0);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::GREEN));

    /**
     * @tc.steps: step3. Touch up tabBarItem(index:0)
     * @tc.expected: touchingIndex_ is 0, BackgroundColor change to hover color
     */
    HandleTouchEvent(TouchType::UP, Offset(180.f, inTabBarItemY));
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::RED));
}

/**
 * @tc.name: HandleMouseTouch005
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch down tabBarItem(index:0) than move to tabBarItem(index:1) and touch up
     */
    // tabItem0(touch down) -> tabItem1(touch up)
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:0) and move to tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:0) BackgroundColor is press color, tabBarItem(index:1) not change
     */
    HandleMouseEvent(MouseAction::MOVE, Offset(100.f, 30.f));
    HandleHoverEvent(true);
    HandleTouchEvent(TouchType::DOWN, Offset(100.f, 30.f));
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::GREEN));

    HandleMouseEvent(MouseAction::MOVE, Offset(200.f, 30.f));
    HandleHoverEvent(true);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 0);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::GREEN));

    /**
     * @tc.steps: step3. Touch up tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:1) BackgroundColor is hover color
     */
    HandleTouchEvent(TouchType::UP, Offset(200.f, 30.f));
    EXPECT_FALSE(tabBarPattern_->touchingIndex_.has_value());
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::TRANSPARENT));
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::RED));
}

/**
 * @tc.name: HandleMouseTouch006
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch down tabBarItem(index:1) than move to outside and touch cancel
     */
    // tabItem1(touch down) -> outside(touch cancel)
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:1) BackgroundColor is press color
     */
    HandleMouseEvent(MouseAction::MOVE, Offset(200.f, 30.f));
    HandleHoverEvent(true);
    HandleTouchEvent(TouchType::DOWN, Offset(200.f, 30.f));
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::GREEN));

    /**
     * @tc.steps: step3. Move to tabs but not on tabBar
     * @tc.expected: tabBarItem(index:1) BackgroundColor is TRANSPARENT color
     */
    HandleMouseEvent(MouseAction::WINDOW_LEAVE, Offset(200.f, 100.f));
    HandleHoverEvent(false);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 1);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::TRANSPARENT));

    /**
     * @tc.steps: step5. Continue move to outside
     */
    HandleMouseEvent(MouseAction::MOVE, Offset(TABS_WIDTH + 1.f, 1.f));
    HandleHoverEvent(false);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 1);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::TRANSPARENT));

    /**
     * @tc.steps: step6. Touch cancel
     */
    HandleTouchEvent(TouchType::CANCEL, Offset(TABS_WIDTH + 1.f, 1.f));
    EXPECT_FALSE(tabBarPattern_->touchingIndex_.has_value());
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::TRANSPARENT));
}

/**
 * @tc.name: OnWillShowAndOnWillHideTest001
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnWillShowAndOnWillHideTest001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create parent node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto parentNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model = CreateTabs(BarPosition::START, 1);
    bool isShow = false;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        tabContentModel.SetOnWillShow(std::move(showEvent));
        tabContentModel.SetOnWillHide(std::move(hideEvent));
        tabContentModel.Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = true
     */
    EXPECT_TRUE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = false
     */
    auto callback = parentNode->GetPattern<PagePattern>()->onHiddenChange_;
    EXPECT_FALSE(callback.empty());
    for (auto& OnHiddenChangeInfo : callback) {
        if (OnHiddenChangeInfo.second) {
            auto OnHiddenChange = OnHiddenChangeInfo.second;
            OnHiddenChange(false);
        }
    }
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step5. callback.
     * @tc.expected: isShow = true
     */
    for (auto& OnHiddenChangeInfo : callback) {
        if (OnHiddenChangeInfo.second) {
            auto OnHiddenChange = OnHiddenChangeInfo.second;
            OnHiddenChange(true);
        }
    }
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: OnWillShowAndOnWillHideTest002
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnWillShowAndOnWillHideTest002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create parent node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto parentNode = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, AceType::MakeRefPtr<NavDestinationPattern>());
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model = CreateTabs(BarPosition::START, 1);
    bool isShow = false;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        tabContentModel.SetOnWillShow(std::move(showEvent));
        tabContentModel.SetOnWillHide(std::move(hideEvent));
        tabContentModel.Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    model.Pop();
    CreateDone();

    /**
     * @tc.steps: step3. callback.
     * @tc.expected: isShow = false
     */
    auto callback =
        parentNode->GetPattern<NavDestinationPattern>()->GetEventHub<NavDestinationEventHub>()->onHiddenChange_;
    EXPECT_FALSE(callback.empty());
    for (auto& OnHiddenChangeInfo : callback) {
        if (OnHiddenChangeInfo.second) {
            auto OnHiddenChange = OnHiddenChangeInfo.second;
            OnHiddenChange(false);
        }
    }
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = true
     */
    for (auto& OnHiddenChangeInfo : callback) {
        if (OnHiddenChangeInfo.second) {
            auto OnHiddenChange = OnHiddenChangeInfo.second;
            OnHiddenChange(true);
        }
    }
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: OnWillShowAndOnWillHideTest003
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnWillShowAndOnWillHideTest003, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create parentNode
     */
    auto parentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model = CreateTabs();
    int isShow = 0;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        std::function<void()> hideEvent = [&isShow, index]() { isShow &= ~(1 << index); };
        tabContentModel.SetOnWillShow(std::move(showEvent));
        tabContentModel.SetOnWillHide(std::move(hideEvent));
        tabContentModel.Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 1.
     * @tc.expected: isShow = 0b0010
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(isShow, 2);

    /**
     * @tc.steps: step6. SwipeTo 3.
     * @tc.expected: isShow = 0b1000
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(isShow, 8);
}

/**
 * @tc.name: OnWillShowAndOnWillHideTest004
 * @tc.desc: test the middle tabcontents does not trigger OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnWillShowAndOnWillHideTest004, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create parentNode
     */
    auto parentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ViewStackProcessor::GetInstance()->Push(parentNode);

    /**
     * @tc.steps: steps2. Create tabs
     */
    TabsModelNG model = CreateTabs();
    int isShow = 0;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        tabContentModel.SetOnWillShow(std::move(showEvent));
        tabContentModel.Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 3.
     * @tc.expected: The middle tabcontents does not trigger OnWillShow.
                    isShow = 0b1001
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(isShow, 9);
}

/**
 * @tc.name: OnWillShowAndOnWillHideTest005
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnWillShowAndOnWillHideTest005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabs
     */
    TabsModelNG model = CreateTabs();
    auto isShowCount = 0;
    auto isHideCount = 0;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        std::function<void()> showEvent = [&isShowCount]() { isShowCount++; };
        std::function<void()> hideEvent = [&isHideCount]() { isHideCount++; };
        tabContentModel.SetOnWillShow(std::move(showEvent));
        tabContentModel.SetOnWillHide(std::move(hideEvent));
        tabContentModel.Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. first display.
     * @tc.expected: isShowCount and isHideCount equal to 0.
     */
    EXPECT_EQ(isShowCount, 1);
    EXPECT_EQ(isHideCount, 0);

    /**
     * @tc.steps: step3. SwipeTo 2.
     * @tc.expected: isShowCount and isHideCount equal to 1.
     */
    swiperController_->SwipeTo(2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(isShowCount, 2);
    EXPECT_EQ(isHideCount, 1);

    /**
     * @tc.steps: step4. SwipeToWithoutAnimation 3.
     * @tc.expected: isShowCount and isHideCount equal to 2.
     */
    swiperController_->SwipeToWithoutAnimation(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushUITasks();
    EXPECT_EQ(isShowCount, 3);
    EXPECT_EQ(isHideCount, 2);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleTouchEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleTouchEvent002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: TabBarPatternInitHoverEvent001
 * @tc.desc: test InitHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitHoverEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->hoverEvent_ = nullptr;
    tabBarPattern_->mouseEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->InitHoverEvent();
    tabBarPattern_->InitMouseEvent();
    ASSERT_NE(tabBarPattern_->hoverEvent_, nullptr);
    ASSERT_NE(tabBarPattern_->mouseEvent_, nullptr);
    tabBarPattern_->hoverEvent_->onHoverCallback_(true);
    auto info = MouseInfo();
    tabBarPattern_->mouseEvent_->onMouseCallback_(info);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent001
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitTurnPageRateEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern_->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent002
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitTurnPageRateEvent002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern_->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern_->turnPageRate_ = 2.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = 1.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = 0.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern_->turnPageRate_ = -1.0f;
    (*(tabBarPattern_->animationEndEvent_))(testswipingIndex, info);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabsControllerPreloadItems001
 * @tc.desc: test preloadItems
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabsControllerPreloadItems001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Init preload items callback.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t code = ERROR_CODE_NO_ERROR;
    auto onPreloadFinish = [&code](int32_t errorCode, std::string message) { code = errorCode; };

    /**
     * @tc.steps: steps2. Set preload items to different value
     * @tc.expected: steps2. Check errorCode
     */
    std::set<int32_t> indexSet;
    swiperController_->SetPreloadFinishCallback(onPreloadFinish);
    swiperController_->PreloadItems(indexSet);
    EXPECT_EQ(code, ERROR_CODE_PARAM_INVALID);

    code = ERROR_CODE_NO_ERROR;
    indexSet.insert(1);
    swiperController_->SetPreloadFinishCallback(onPreloadFinish);
    swiperController_->PreloadItems(indexSet);
    EXPECT_EQ(code, ERROR_CODE_NO_ERROR);

    indexSet.insert(-1);
    swiperController_->SetPreloadFinishCallback(onPreloadFinish);
    swiperController_->PreloadItems(indexSet);
    EXPECT_EQ(code, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SetOnIndexChangeEvent001
 * @tc.desc: Test SetOnIndexChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnIndexChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.cases: Change swiper index by click tabBarItem
     * @tc.expected: OnChangeEvent was triggered
     */
    int32_t currentIndex;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChangeEvent(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SetOnIndexChangeEvent002
 * @tc.desc: Test SetOnIndexChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnIndexChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change swiper index
     * @tc.expected: OnChangeEvent was triggered
     */
    int32_t currentIndex;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChangeEvent(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 1);

    /**
     * @tc.steps: step2. Swap OnChangeEvent
     * @tc.expected: OnChangeEvent was swap
     */
    int32_t currentIndex2;
    auto event2 = [&currentIndex2](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex2 = tabInfo->GetIndex();
    };
    pattern_->SetOnIndexChangeEvent(std::move(event2));
    SwipeToWithoutAnimation(2);
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(currentIndex2, 2);
}

/**
 * @tc.name: SetOnIndexChangeEvent003
 * @tc.desc: test SetOnChangeEvent, event will not be triggered when IsMaskAnimationExecuted
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnIndexChangeEvent003, TestSize.Level1)
{
    /**
     * @tc.cases: Change swiper index by click tabBarItem
     * @tc.expected: OnChangeEvent was triggered
     */
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChangeEvent(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->SetMaskAnimationExecuted(true);
    FlushUITasks();
    EXPECT_TRUE(tabBarPattern_->IsMaskAnimationExecuted());

    HandleClick(Offset(200.f, 30.f), 1); // click second tabBarItem
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SetOnChangeEvent001
 * @tc.desc: test SetOnChangeEvent, event will be triggered when index change
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnChangeEvent001, TestSize.Level1)
{
    int32_t currentIndex;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChange(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Change swiper index
     * @tc.expected: Event was triggered
     */
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 1);

    SwipeToWithoutAnimation(3);
    EXPECT_EQ(currentIndex, 3);
}

/**
 * @tc.name: SetOnChangeEvent002
 * @tc.desc: test SetOnChangeEvent, swap event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnChangeEvent002, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChange(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Swap event
     * @tc.expected: Event was swap
     */
    bool currentIndex2;
    auto event2 = [&currentIndex2](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex2 = tabInfo->GetIndex();
    };
    pattern_->SetOnChangeEvent(std::move(event2));
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(currentIndex2, 1);
}

/**
 * @tc.name: SetOnChangeEvent003
 * @tc.desc: test SetOnChangeEvent, event will not be triggered when IsMaskAnimationExecuted
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnChangeEvent003, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnChange(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. IsMaskAnimationExecuted
     * @tc.expected: Event was not triggered
     */
    tabBarPattern_->SetMaskAnimationExecuted(true);
    FlushUITasks();
    EXPECT_TRUE(tabBarPattern_->IsMaskAnimationExecuted());

    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 0);

    SwipeToWithoutAnimation(3);
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: ObserverTestNg001
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, ObserverTestNg001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. Init tabContent state update callback the swipe to 1
     * @tc.expected: steps2. Check state value.
     */
    UIObserverHandler::TabContentStateHandleFunc func = [](const TabContentInfo& info) {
        if (info.index == 0) {
            EXPECT_EQ(info.state, TabContentState::ON_HIDE);
        } else if (info.index == 1) {
            EXPECT_EQ(info.state, TabContentState::ON_SHOW);
        }
    };
    UIObserverHandler::GetInstance().SetHandleTabContentStateUpdateFunc(func);

    swiperController_->SwipeTo(1);
    FlushUITasks();
    UIObserverHandler::GetInstance().SetHandleTabContentStateUpdateFunc(nullptr);
}

/**
 * @tc.name: SetOnUnselectedEvent001
 * @tc.desc: test SetOnUnselectedEvent, event will be triggered when index unselected
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnUnselectedEvent001, TestSize.Level1)
{
    int32_t currentIndex;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnUnselected(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Change swiper index
     * @tc.expected: Event was triggered
     */
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 0);

    SwipeToWithoutAnimation(3);
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: SetOnUnselectedEvent002
 * @tc.desc: test SetOnUnselectedEvent, swap event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnUnselectedEvent002, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnUnselected(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Swap event
     * @tc.expected: Event was swap
     */
    bool currentIndex2;
    auto event2 = [&currentIndex2](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex2 = tabInfo->GetIndex();
    };
    pattern_->SetOnUnselectedEvent(std::move(event2));
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 0);
    EXPECT_EQ(currentIndex2, 0);
    SwipeToWithoutAnimation(3);
    EXPECT_EQ(currentIndex2, 1);
}

/**
 * @tc.name: SetOnSelectedEvent001
 * @tc.desc: test SetOnSelectedEvent, event will be triggered when index selected
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnSelectedEvent001, TestSize.Level1)
{
    int32_t currentIndex;
    auto event = [&currentIndex](const BaseEventInfo* info) {
        const auto* tabInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        currentIndex = tabInfo->GetIndex();
    };
    TabsModelNG model = CreateTabs();
    model.SetOnSelected(event);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Change swiper index to 1
     * @tc.expected: currentIndex is 1
     */
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(currentIndex, 1);

    /**
     * @tc.steps: step2. Change swiper index to 3
     * @tc.expected: currentIndex is 3
     */
    SwipeToWithoutAnimation(3);
    EXPECT_EQ(currentIndex, 3);
}

/**
 * @tc.name: OnAppearAndOnDisappearTest001
 * @tc.desc: test OnAppear and OnDisappear
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnAppearAndOnDisappearTest001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabs
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    CreateTabsDone(model);

    auto isOnAppear = false;
    auto isOnDisappear = false;
    std::function<void()> appearEvent = [&isOnAppear]() { isOnAppear = true; };
    std::function<void()> disappearEvent = [&isOnDisappear]() { isOnDisappear = true; };
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto eventHub = tabContentFrameNode->GetEventHub<EventHub>();
    eventHub->SetOnAppear(std::move(appearEvent));
    eventHub->SetOnDisappear(std::move(disappearEvent));
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    EXPECT_FALSE(isOnAppear);
    EXPECT_FALSE(isOnDisappear);

    /**
     * @tc.steps: step2. trigger OnAttachToMainTree.
     * @tc.expected: isOnAppear is true.
     */
    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_TRUE(isOnAppear);
    EXPECT_FALSE(isOnDisappear);

    /**
     * @tc.steps: step3. trigger OnDetachFromMainTree.
     * @tc.expected: isOnDisappear is true.
     */
    tabContentFrameNode->OnDetachFromMainTree(true, pipeline);
    EXPECT_TRUE(isOnAppear);
    EXPECT_TRUE(isOnDisappear);
}
} // namespace OHOS::Ace::NG
