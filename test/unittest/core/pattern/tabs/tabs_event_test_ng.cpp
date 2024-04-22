/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabsEventTestNg : public TabsTestNg {
public:
};

void FocusTest(const RefPtr<TabBarLayoutProperty>& tabBarLayoutProperty, const RefPtr<TabBarPattern>& tabBarPattern)
{
    KeyEvent event;
    event.action = KeyAction::DOWN;

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_TAB;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    event.code = KeyCode::KEY_DPAD_DOWN;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_UP;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
}

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
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: OnChange001
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change swiper index
     * @tc.expected: OnChangeEvent was triggered
     */
    bool isTrigger = false;
    auto event = [&isTrigger](const BaseEventInfo* info) { isTrigger = true; };
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnChangeEvent(event);
    });
    SwipeToWithoutAnimation(1);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Swap OnChangeEvent
     * @tc.expected: OnChangeEvent was swaped
     */
    bool isTrigger2 = false;
    auto event2 = [&isTrigger2](const BaseEventInfo* info) { isTrigger2 = true; };
    pattern_->SetOnIndexChangeEvent(std::move(event2));
    SwipeToWithoutAnimation(2);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 2);
    EXPECT_TRUE(isTrigger2);
}

/**
 * @tc.name: OnChange002
 * @tc.desc: Test Tabs event
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, OnChange002, TestSize.Level1)
{
    /**
     * @tc.cases: Change swiper index by click tabBarItem
     * @tc.expected: OnChangeEvent was triggered
     */
    bool isTrigger = false;
    auto event = [&isTrigger](const BaseEventInfo* info) { isTrigger = true; };
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnChangeEvent(event);
    });
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(isTrigger);
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
    bool isTrigger = false;
    auto event = [&isTrigger](const BaseEventInfo* info) { isTrigger = true; };
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnTabBarClick(event);
    });
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(isTrigger);
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
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnContentWillChange(event);
    });
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
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
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnContentWillChange(event);
    });
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
    EXPECT_TRUE(isTrigger);
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
    auto endEvent = [&isEndTrigger](int32_t index, const AnimationCallbackInfo& info) {
        isEndTrigger = true;
    };
    CreateWithItem([=](TabsModelNG model) {
        model.SetAnimationDuration(1000.f); // open animation
        model.SetOnAnimationStart(startEvent);
        model.SetOnAnimationEnd(endEvent);
    });
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
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
    auto endEvent = [&isEndTrigger](int32_t index, const AnimationCallbackInfo& info) {
        isEndTrigger = true;
    };
    bool isStartTrigger2 = false;
    auto startEvent2 = [&isStartTrigger2](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isStartTrigger2 = true;
    };
    bool isEndTrigger2 = false;
    auto endEvent2 = [&isEndTrigger2](int32_t index, const AnimationCallbackInfo& info) {
        isEndTrigger2 = true;
    };
    CreateWithItem([=](TabsModelNG model) {
        model.SetAnimationDuration(1000.f); // open animation
        model.SetOnAnimationStart(startEvent);
        model.SetOnAnimationEnd(endEvent);
    });
    pattern_->SetAnimationStartEvent(std::move(startEvent2));
    pattern_->SetAnimationEndEvent(std::move(endEvent2));
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
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
    CreateWithItem([](TabsModelNG model) {});
    GestureEvent info;
    info.SetLocalLocation(Offset(200.f, 30.f));
    info.SetSourceDevice(SourceType::KEYBOARD);
    tabBarPattern_->HandleClick(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
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
    Create([](TabsModelNG model) {}); // empty item
    ClickTo(Offset(200.f, 30.f));
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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {}, 0);
    });
    ClickTo(Offset(200.f, 30.f));
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
    CreateWithItem([](TabsModelNG model) {
        model.SetTabBarMode(TabBarMode::SCROLLABLE);
        model.SetIsVertical(false);
    });
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->GetSpringProperty();
    scrollable->isSpringAnimationStop_ = false;
    ClickTo(Offset(200.f, 30.f)); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });
    
    ClickTo(Offset(400.f, 30.f)); // click second tabBarItem
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicatorValue(), 1);
}

/**
 * @tc.name: HandleMouseTouch001
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty items
     * @tc.expected: hoverIndex_ has no value
     */
    Create([](TabsModelNG model) {});
    MouseTo(MouseAction::MOVE, Offset(100.f, 30.f), true);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
}

/**
 * @tc.name: HandleMouseTouch002
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Move mouse from outside to the tabBarItem(index:0,1) and move to outside
     */
    CreateWithItemWithoutBuilder([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Move mouse to outside
     * @tc.expected: hoverIndex_ has no value
     */
    MouseTo(MouseAction::MOVE, Offset(-1.f, 1.f), false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());

    /**
     * @tc.steps: step3. Move mouse to tabs but not on the tabBar
     * @tc.expected: hoverIndex_ has no value
     */
    MouseTo(MouseAction::WINDOW_ENTER, Offset(100.f, 100.f), false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.steps: step4. Move mouse to tabBarItem(index:0)
     * @tc.expected: hoverIndex_ is 0, BackgroundColor change to hover color
     */
    MouseTo(MouseAction::MOVE, Offset(100.f, 30.f), true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 0);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::RED);

    /**
     * @tc.steps: step5. Move mouse to tabBarItem(index:1)
     * @tc.expected: hoverIndex_ is 0, BackgroundColor change to hover color
     */
    MouseTo(MouseAction::MOVE, Offset(200.f, 30.f), true);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::RED);

    /**
     * @tc.steps: step6. Move mouse to outside
     * @tc.expected: hoverIndex_ is 0, BackgroundColor change to hover color
     */
    MouseTo(MouseAction::WINDOW_LEAVE, Offset(200.f, 100.f), false);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: HandleMouseTouch003
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. hover tabBarItem(index:0), touch down and touch up
     */
    CreateWithItemWithoutBuilder([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:0)
     * @tc.expected: touchingIndex_ is 0, BackgroundColor change to press color
     */
    MouseTo(MouseAction::MOVE, Offset(100.f, 30.f), true);
    TouchTo(TouchType::DOWN, Offset(100.f, 30.f));
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 0);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::GREEN);

    /**
     * @tc.steps: step3. Touch up tabBarItem(index:0)
     * @tc.expected: touchingIndex_ is 0, BackgroundColor change to hover color
     */
    TouchTo(TouchType::UP, Offset(100.f, 30.f));
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::RED);
}

/**
 * @tc.name: HandleMouseTouch004
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch down tabBarItem(index:0) than move to tabBarItem(index:1) and touch up
     */
    // tabItem0(touch down) -> tabItem1(touch up)
    CreateWithItemWithoutBuilder([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:0) and move to tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:0) BackgroundColor is press color, tabBarItem(index:1) not change
     */
    MouseTo(MouseAction::MOVE, Offset(100.f, 30.f), true);
    TouchTo(TouchType::DOWN, Offset(100.f, 30.f));
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::GREEN);

    MouseTo(MouseAction::MOVE, Offset(200.f, 30.f), true);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 0);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::GREEN);

    /**
     * @tc.steps: step3. Touch up tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:1) BackgroundColor is hover color
     */
    TouchTo(TouchType::UP, Offset(200.f, 30.f));
    EXPECT_FALSE(tabBarPattern_->touchingIndex_.has_value());
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 0)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::RED);
}

/**
 * @tc.name: HandleMouseTouch005
 * @tc.desc: Test HandleMouseEvent and HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, HandleMouseTouch005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch down tabBarItem(index:1) than move to outside and touch cancel
     */
    // tabItem1(touch down) -> outside(touch cancel)
    CreateWithItemWithoutBuilder([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Hover and Touch down tabBarItem(index:1)
     * @tc.expected: tabBarItem(index:1) BackgroundColor is press color
     */
    MouseTo(MouseAction::MOVE, Offset(200.f, 30.f), true);
    TouchTo(TouchType::DOWN, Offset(200.f, 30.f));
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::GREEN);

    /**
     * @tc.steps: step3. Move to tabs but not on tabBar
     * @tc.expected: tabBarItem(index:1) BackgroundColor is TRANSPARENT color
     */
    MouseTo(MouseAction::WINDOW_LEAVE, Offset(200.f, 100.f), false);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 1);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.steps: step5. Continue move to outside
     */
    MouseTo(MouseAction::MOVE, Offset(TABS_WIDTH + 1.f, 1.f), false);
    EXPECT_EQ(tabBarPattern_->touchingIndex_, 1);
    EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);

    /**
     * @tc.steps: step6. Touch cancel
     */
    TouchTo(TouchType::CANCEL, Offset(TABS_WIDTH + 1.f, 1.f));
    EXPECT_FALSE(tabBarPattern_->touchingIndex_.has_value());
    EXPECT_EQ(GetChildFrameNode(tabBarNode_, 1)->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: SetOnContentWillChangeTest001
 * @tc.desc: test onContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnContentWillChangeTest001, TestSize.Level1)
{
    auto callback = [](int32_t currentIndex, int32_t comingIndex) -> bool { return true; };
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnContentWillChange(std::move(callback));
    });
    EXPECT_TRUE(pattern_->GetInterceptStatus());

    auto ret = pattern_->OnContentWillChange(CURRENT_INDEX, BEGIN_INDEX);
    EXPECT_TRUE(ret.value());
    EXPECT_TRUE(swiperPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(swiperPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(BEGIN_INDEX));
    EXPECT_TRUE(tabBarPattern_->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX));
}

/**
 * @tc.name: SetOnContentWillChangeTest002
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnContentWillChangeTest002, TestSize.Level1)
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
    TabsModelNG model;
    model.Create(BarPosition::START, 1, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    bool isShow = false;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = true
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_TRUE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = false
     */
    auto callback = parentNode->GetPattern<PagePattern>()->onHiddenChange_;
    ASSERT_NE(callback, nullptr);
    callback(false);
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step5. callback.
     * @tc.expected: isShow = true
     */
    callback(true);
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: SetOnContentWillChangeTest003
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnContentWillChangeTest003, TestSize.Level1)
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
    TabsModelNG model;
    model.Create(BarPosition::START, 1, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    bool isShow = false;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow]() { isShow = true; };
        std::function<void()> hideEvent = [&isShow]() { isShow = false; };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();

    /**
     * @tc.steps: step3. callback.
     * @tc.expected: isShow = false
     */
    auto callback =
        parentNode->GetPattern<NavDestinationPattern>()->GetEventHub<NavDestinationEventHub>()->onHiddenChange_;
    ASSERT_NE(callback, nullptr);
    callback(false);
    EXPECT_FALSE(isShow);

    /**
     * @tc.steps: step4. callback.
     * @tc.expected: isShow = true
     */
    callback(true);
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: SetOnContentWillChangeTest004
 * @tc.desc: test OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnContentWillChangeTest004, TestSize.Level1)
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
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    int isShow = 0;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        std::function<void()> hideEvent = [&isShow, index]() { isShow &= ~(1 << index); };
        model.SetOnWillShow(std::move(showEvent));
        model.SetOnWillHide(std::move(hideEvent));
    });

    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperController_ = swiperPattern_->GetSwiperController();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 1.
     * @tc.expected: isShow = 0b0010
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 2);

    /**
     * @tc.steps: step6. SwipeTo 3.
     * @tc.expected: isShow = 0b1000
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 8);
}

/**
 * @tc.name: SetOnContentWillChangeTest005
 * @tc.desc: test the middle tabcontents does not trigger OnWillShow and OnWillHide
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnContentWillChangeTest005, TestSize.Level1)
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
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));

    int isShow = 0;
    CreateItem(TABCONTENT_NUMBER, [&isShow](TabContentModelNG model, int32_t index) {
        std::function<void()> showEvent = [&isShow, index]() { isShow |= 1 << index; };
        model.SetOnWillShow(std::move(showEvent));
    });

    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->Pop();
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperController_ = swiperPattern_->GetSwiperController();

    /**
     * @tc.steps: step3. first display.
     * @tc.expected: isShow = 0b0001
     */
    FlushLayoutTask(frameNode_);
    ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(isShow, 1);

    /**
     * @tc.steps: step4. SwipeTo 3.
     * @tc.expected: The middle tabcontents does not trigger OnWillShow.
                    isShow = 0b1001
     */
    swiperController_->SwipeTo(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(isShow, 9);
}

/**
 * @tc.name: TabBarPatternHandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleMouseEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->HandleMouseEvent(info);
        }
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent002
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleMouseEvent002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarNode_->Clean(false, false);

    /**
     * @tc.steps: step2. Test function GetBottomTabBarImageSizeAndOffset.
     * @tc.expected: Related function runs ok.
     */
    auto info = MouseInfo();
    int32_t nodeId = 1;
    tabBarPattern_->HandleMouseEvent(info);
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }

    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->HandleMouseEvent(info);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleMouseEvent003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    auto info = MouseInfo();
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    Offset s1(0.2, 0.2);
    Offset s2(0.3, 0.3);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    info.SetLocalLocation(s1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3 };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleMouseEvent(info);
        info.SetLocalLocation(s2);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarLayoutProperty_->UpdateIndicator(2);
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleTouchEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern_->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: TabBarPatternHandleHoverEvent001
 * @tc.desc: test HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleHoverEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    bool isHover = true;
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverEvent.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleHoverEvent(isHover);
                isHover = false;
                tabBarPattern_->hoverIndex_ = {};
            }
            tabBarPattern_->hoverIndex_ = hoverIndex_test;
        }
        isHover = true;
        tabBarPattern_->hoverIndex_ = {};
    }

    isHover = false;
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = {};
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern_->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleHoverEvent(isHover);
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarPatternHandleHoverOnEvent001
 * @tc.desc: test HandleHoverOnEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleHoverOnEvent001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);
    tabBarPattern_->tabItemOffsets_.emplace_back(c2);
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverOnEvent.
     * @tc.expected: Related functions run ok.
     */
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern_->hoverIndex_ = hoverIndex_test;
    tabBarPattern_->touchingIndex_ = {};
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern_->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleHoverOnEvent(0);
        tabBarPattern_->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent002
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});

    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    KeyCode code = KeyCode::KEY_CLEAR;
    KeyAction action = KeyAction::CLICK;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);

    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->OnKeyEvent(event);
                event.action = KeyAction::DOWN;
                event.code = KeyCode::KEY_DPAD_LEFT;
            }
            event.code = KeyCode::KEY_DPAD_UP;
        }
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->OnKeyEvent(event);
                event.code = KeyCode::KEY_DPAD_RIGHT;
            }
            event.code = KeyCode::KEY_DPAD_DOWN;
        }
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    event.code = KeyCode::KEY_TAB;
    tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->OnKeyEvent(event);
        tabBarPattern_->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(-2);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleTouchEvent002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
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
    CreateWithItem([](TabsModelNG model) {});
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
 * @tc.name: TabBarPatternInitOnKeyEvent001
 * @tc.desc: test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    auto focusHub = tabBarNode_->GetOrCreateFocusHub();
    auto event = KeyEvent();
    auto paintRect = RoundRect();
    tabBarPattern_->InitOnKeyEvent(focusHub);
    focusHub->ProcessOnKeyEventInternal(event);
    focusHub->getInnerFocusRectFunc_(paintRect);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent004
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleMouseEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    tabBarPattern_->hoverIndex_.emplace(1);
    tabBarPattern_->tabItemOffsets_ = { c1, c2, c3, c4 };
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    IndicatorStyle indicatorStyle3;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    indicatorStyle3.color = Color::BLUE;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
        TabBarStyle::NOSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2, indicatorStyle3 };

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->HandleMouseEvent(info);
            info.SetLocalLocation(s2);
            ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 2);
            tabBarPattern_->hoverIndex_.reset();
        }
        tabBarPattern_->hoverIndex_.emplace(1);
        tabBarPattern_->touchingIndex_.emplace(1);
    }

    Offset s3(0.2, 0.2);
    info.SetLocalLocation(s3);
    ASSERT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    info.SetAction(MouseAction::MOVE);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleMouseEvent(info);
                tabBarPattern_->touchingIndex_.reset();
                tabBarPattern_->hoverIndex_ = 1;
            }
            tabBarPattern_->hoverIndex_.reset();
        }
        tabBarPattern_->hoverIndex_.emplace(0);
        info.SetAction(MouseAction::WINDOW_ENTER);
    }

    info.SetAction(MouseAction::WINDOW_LEAVE);
    tabBarPattern_->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent003
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    KeyCode code = KeyCode::KEY_DPAD_LEFT;
    KeyAction action = KeyAction::DOWN;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarLayoutProperty_->UpdateIndicator(1);
    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    tabBarPattern_->OnKeyEvent(event);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternHandleTouchEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(1.0f, 1.0f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchEvent(touchLocationInfo);
        touchLocationInfo.SetLocalLocation(Offset(-1.0f, -1.0f));
    }
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 3);
    tabBarPattern_->touchingIndex_ = 1;
    touchLocationInfo.SetTouchType(TouchType::UP);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleTouchEvent(touchLocationInfo);
                tabBarPattern_->touchingIndex_ = 1;
                touchLocationInfo.SetTouchType(TouchType::CANCEL);
            }
            touchLocationInfo.SetTouchType(TouchType::DOWN);
        }
        tabBarPattern_->touchingIndex_.reset();
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent004
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent004, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    });
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE);
    tabBarPattern_->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern_->OnKeyEvent(event));

    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern_->OnKeyEvent(event));

    layoutProperty_->UpdateTabBarPosition(BarPosition::START);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent005
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent005, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent006
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent006, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern_->SetFirstFocus(true);
    FocusTest(tabBarLayoutProperty_, tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent007
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternOnKeyEvent007, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::NOSTYLE);
        }, 1);
    }, BarPosition::END);

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    layoutProperty_->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->isFocusActive_ = false;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));

    pipeline->isFocusActive_ = true;
    event.code = KeyCode::KEY_A;
    tabBarPattern_->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));
}

/**
 * @tc.name: SetOnChangeEvent002.
 * @tc.desc: Test the SetOnChangeEvent function in the TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, SetOnChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) {
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step2. set different conditions and invoke SetOnChangeEvent.
     * @tc.expected: step2. related function is called.
     */
    pattern_->onIndexChangeEvent_ = nullptr;
    pattern_->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    swiperPattern_->FireChangeEvent();
    tabBarPattern_->isMaskAnimationByCreate_ = true;
    swiperPattern_->FireChangeEvent();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    swiperPattern_->FireChangeEvent();
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    swiperPattern_->FireChangeEvent();
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(Axis::HORIZONTAL), Axis::HORIZONTAL);
    tabBarPattern_->changeByClick_ = true;
    swiperPattern_->FireChangeEvent();
    pattern_->SetOnTabBarClickEvent([](const BaseEventInfo* info) {});
    auto onTabBarClickEvent = pattern_->GetTabBarClickEvent();
    (*onTabBarClickEvent)(1);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent001
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitTurnPageRateEvent001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

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
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent002
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabBarPatternInitTurnPageRateEvent002, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);

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
}
} // namespace OHOS::Ace::NG
