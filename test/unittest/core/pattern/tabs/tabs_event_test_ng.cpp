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
} // namespace OHOS::Ace::NG
