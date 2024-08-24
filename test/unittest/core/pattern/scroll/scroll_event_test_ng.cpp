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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ScrollEventTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: Event001
 * @tc.desc: Test RegisterScrollEventTask
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Event001, TestSize.Level1)
{
    auto event1 = [](Dimension, ScrollState) { return ScrollFrameResult(); };
    auto event2 = [](Dimension, Dimension) { return ScrollInfo(); };
    ScrollModelNG model = CreateScroll();
    model.SetOnScrollFrameBegin(event1);
    model.SetOnScrollBegin(event2);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. When set event
     * @tc.expected: scrollableEvent would has event that setted
     */
    ASSERT_NE(eventHub_->GetOnScrollFrameBegin(), nullptr);
    ASSERT_NE(eventHub_->GetScrollBeginEvent(), nullptr);
}

/**
 * @tc.name: OnScrollEvent001
 * @tc.desc: Test attribute about onScroll in VERTICAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollEvent001, TestSize.Level1)
{
    float scrollY = -1.f;
    NG::ScrollEvent event = [&scrollY](Dimension, Dimension y) { scrollY = y.ConvertToPx(); };
    ScrollModelNG model = CreateScroll();
    model.SetOnScroll(std::move(event));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Trigger event by OnScrollCallback
     * @tc.expected: ScrollEvent was triggered
     */
    pattern_->OnScrollCallback(-CONTENT_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    EXPECT_EQ(scrollY, VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step2. Trigger event by ScrollToEdge
     * @tc.expected: ScrollEvent was triggered
     */
    scrollY = -1.f;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(scrollY, -VERTICAL_SCROLLABLE_DISTANCE);
}

/**
 * @tc.name: OnScrollEvent002
 * @tc.desc: Test attribute about onScroll in HORIZONTAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollEvent002, TestSize.Level1)
{
    float scrollX = -1.f;
    NG::ScrollEvent event = [&scrollX](Dimension x, Dimension) { scrollX = x.ConvertToPx(); };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    model.SetOnScroll(std::move(event));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Trigger event by OnScrollCallback
     * @tc.expected: ScrollEvent was triggered
     */
    pattern_->OnScrollCallback(-600.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(scrollX, 600.f);

    /**
     * @tc.steps: step2. Trigger event by ScrollToEdge
     * @tc.expected: ScrollEvent was triggered
     */
    scrollX = -1.f;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(scrollX, -600.f);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge, check offset
     * @tc.expected: offset is equal to GetTotalOffset
     */
    auto scrollOffSet = accessibilityProperty_->GetScrollOffSet();
    EXPECT_EQ(scrollOffSet, pattern_->GetTotalOffset());
}

/**
 * @tc.name: Event003
 * @tc.desc: Test attribute about onScrollEdge,
 * Event is triggered while scroll to edge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Event003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isTrigger = false;
    ScrollModelNG model = CreateScroll();
    NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };
    model.SetOnScrollEdge(std::move(event));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-600.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. Test event in HORIZONTAL
     */
    ClearOldNodes();
    isTrigger = false;
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    NG::ScrollEdgeEvent event2 = [&isTrigger](ScrollEdge) { isTrigger = true; };
    model.SetOnScrollEdge(std::move(event2));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-CONTENT_MAIN_SIZE * 2, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test attribute about onScrollStart and onScrollStop and onScrollEnd,
 * Event is triggered while scrolling start
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Event004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test onScrollStart event in VERTICAL
     */
    bool isTrigger = false;
    ScrollModelNG model = CreateScroll();
    OnScrollStartEvent startEvent = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollStart(std::move(startEvent));
    OnScrollStopEvent stopEvent = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollStop(std::move(stopEvent));
    ScrollEndEvent endEvent = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollEnd(std::move(endEvent));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step2. Trigger onScrollStart event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-600.f, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger onScrollStart event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(isTrigger);
    pattern_->isAnimationStop_ = true; // Stop ScrollToEdge animation

    /**
     * @tc.steps: step4. Trigger onScrollStop / onScrollEnd event
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->OnScrollEndCallback(); // Trigger onScrollEnd, set scrollStop_ = true;
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    FlushLayoutTask(frameNode_); // Trigger onScrollStop
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step5. Set scrollAbort_ to true
     * @tc.expected: onScrollStop would not be trigger
     */
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    pattern_->AnimateTo(600.f, 1.f, Curves::LINEAR, false);
    EXPECT_TRUE(pattern_->GetScrollAbort());

    isTrigger = false;
    pattern_->OnScrollEndCallback(); // Trigger onScrollEnd, set scrollStop_ = true;
    EXPECT_TRUE(isTrigger);
    isTrigger = false;
    FlushLayoutTask(frameNode_); // Trigger onScrollStop
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Test attribute about onReachStart/onReachEnd,
 * Event is triggered while scroll to edge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Event005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     * @tc.expected: reachStart is true on first layout
     */
    bool reachStart = false;
    bool reachEnd = false;
    ScrollModelNG model = CreateScroll();
    auto reachStartEvent = [&reachStart]() { reachStart = true; };
    model.SetOnReachStart(std::move(reachStartEvent));
    auto reachEndEvent = [&reachEnd]() { reachEnd = true; };
    model.SetOnReachEnd(std::move(reachEndEvent));
    CreateContent();
    CreateDone();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(reachStart);
    EXPECT_TRUE(pattern_->isInitialized_);

    /**
     * @tc.steps: step2. Trigger event by ScrollTo
     * @tc.expected: reachEnd is true
     */
    ScrollTo(CONTENT_MAIN_SIZE);
    EXPECT_TRUE(reachEnd);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: reachStart is true
     */
    reachStart = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(reachStart);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test animate scroll func about event
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Event006, TestSize.Level1)
{
    bool isStartTrigger = false;
    bool isStopTrigger = false;
    ScrollModelNG model = CreateScroll();
    OnScrollStartEvent startEvent = [&isStartTrigger]() { isStartTrigger = true; };
    OnScrollStopEvent stopEvent = [&isStopTrigger]() { isStopTrigger = true; };
    model.SetOnScrollStart(std::move(startEvent));
    model.SetOnScrollStop(std::move(stopEvent));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Scroll with animate by run ScrollToEdge
     * @tc.expected: onScrollStart would not be trigger
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(isStartTrigger);

    /**
     * @tc.steps: step1. When animte stop
     * @tc.expected: onScrollStop would not be trigger
     */
    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    // when out of scrollable distance, will trigger animator stop
    pattern_->UpdateCurrentOffset(-1, SCROLL_FROM_ANIMATION_CONTROLLER);
    if (pattern_->IsAtBottom()) {
        pattern_->StopAnimation(pattern_->springAnimation_);
    }
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isStopTrigger);
}

/**
 * @tc.name: SetGestureEvent001
 * @tc.desc: Test GestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SetGestureEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar, touchEvent_
     * @tc.expected: touchEvent_ is initialized correctly
     */
    CreateScroll();
    CreateContent();
    CreateDone();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto touchCallback = [](const TouchEventInfo& info) {};
    RefPtr<TouchEventImpl> touchEvent_ = AccessibilityManager::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    scrollBar->SetGestureEvent();
    EXPECT_NE(touchEvent_, nullptr);
}

/**
 * @tc.name: SetSetMouseEvent001
 * @tc.desc: Test SetMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SetMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar, mouseEvent_
     * @tc.expected: mouseEvent_ is initialized correctly
     */
    CreateScroll();
    CreateContent();
    CreateDone();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto mouseTask = [](MouseInfo& info) {};
    RefPtr<InputEvent> mouseEvent_ = AccessibilityManager::MakeRefPtr<InputEvent>(std::move(mouseTask));
    scrollBar->SetMouseEvent();
    EXPECT_NE(mouseEvent_, nullptr);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test attribute about onWillScroll and onDidScroll in VERTICAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
{
    float willOffsetY = -1.f;
    float didOffsetY = -1.f;
    auto willEvent = [&willOffsetY](Dimension x, Dimension y, ScrollState, ScrollSource) {
        willOffsetY = y.ConvertToPx();
        TwoDimensionScrollResult result;
        result.xOffset = x;
        result.yOffset = y;
        return result;
    };
    auto didEvent = [&didOffsetY](Dimension, Dimension y, ScrollState) { didOffsetY = y.ConvertToPx(); };
    ScrollModelNG model = CreateScroll();
    model.SetOnWillScroll(std::move(willEvent));
    model.SetOnDidScroll(std::move(didEvent));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Trigger event by OnScrollCallback
     * @tc.expected: WillScrollEvent and DisScrollEvent are both triggered
     */
    pattern_->OnScrollCallback(-600.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetY, VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetY, VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step2. Trigger event by ScrollToEdge
     * @tc.expected: WillScrollEvent and DisScrollEvent are both triggered
     */
    willOffsetY = -1.f;
    didOffsetY = -1.f;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetY, -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetY, -VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step3. Scroll 0 distance
     * @tc.expected: No trigger DisScrollEvent
     */
    willOffsetY = -1.f;
    didOffsetY = -1.f;
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetY, 0.f);
    EXPECT_EQ(didOffsetY, -1.f);

    /**
     * @tc.steps: step4. Scroll 0 distance with SCROLL
     * @tc.expected: Trigger DisScrollEvent
     */
    willOffsetY = -1.f;
    didOffsetY = -1.f;
    pattern_->scrollStop_ = true;
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetY, 0.f);
    EXPECT_EQ(didOffsetY, 0.f);

    /**
     * @tc.steps: step5. Scroll 0 distance with IDLE
     * @tc.expected: No trigger onScrollStop and DisScrollEvent
     */
    willOffsetY = -1.f;
    didOffsetY = -1.f;
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_FOCUS_JUMP);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetY, 0.f);
    EXPECT_EQ(didOffsetY, -1.f);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test attribute about onWillScroll and onDidScroll in HORIZONTAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, onWillScrollAndOnDidScroll002, TestSize.Level1)
{
    float willOffsetX = -1.f;
    float didOffsetX = -1.f;
    auto willEvent = [&willOffsetX](Dimension x, Dimension y, ScrollState, ScrollSource) {
        willOffsetX = x.ConvertToPx();
        TwoDimensionScrollResult result;
        result.xOffset = x;
        result.yOffset = y;
        return result;
    };
    auto didEvent = [&didOffsetX](Dimension x, Dimension, ScrollState) { didOffsetX = x.ConvertToPx(); };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    model.SetOnWillScroll(std::move(willEvent));
    model.SetOnDidScroll(std::move(didEvent));
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-600.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetX, VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetX, VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step2. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    willOffsetX = -1.f;
    didOffsetX = -1.f;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(willOffsetX, -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetX, -VERTICAL_SCROLLABLE_DISTANCE);
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test OnScrollCallback that has no effect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Axis::NONE and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::NONE);
    CreateContent();
    CreateDone();
    EXPECT_FALSE(OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. animator_ is running and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateScroll();
    CreateContent();
    CreateDone();
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    EXPECT_FALSE(OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE));
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: Test OnScrollCallback about trigger FireOnScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. no animator and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    bool isTrigger = false;
    ScrollModelNG model = CreateScroll();
    OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollStart(std::move(event));
    CreateContent();
    CreateDone();
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. animator is Stopped and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    isTrigger = false;
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Stop();
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. animator is running and SCROLL_FROM_START
     * @tc.expected: because of scrollAbort_ is true, would not trigger event, and animator stop()
     */
    isTrigger = false;
    pattern_->animator_->Resume();
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    auto onScrollCallback = scrollable->callback_;
    onScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->animator_->IsStopped());
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: OnScrollCallback003
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ bigger than 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is two of ITEM_MAIN_SIZE
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateDone();
    float scrollableDistance = VERTICAL_SCROLLABLE_DISTANCE;
    EXPECT_EQ(pattern_->scrollableDistance_, scrollableDistance);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), -1);

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), -2);

    /**
     * @tc.steps: step4. Continue scroll up
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetTotalOffset(), -3);

    /**
     * @tc.steps: step5. Scroll down
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetTotalOffset(), -2);

    /**
     * @tc.steps: step6. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(pattern_->GetTotalOffset(), scrollableDistance);

    /**
     * @tc.steps: step7. scroll to below of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), (scrollableDistance + 1));

    /**
     * @tc.steps: step8. Continue scroll down
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), (scrollableDistance + 2));

    /**
     * @tc.steps: step9. Continue scroll down
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), scrollableDistance + 3);

    /**
     * @tc.steps: step10. Scroll up
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), scrollableDistance + 2);

    /**
     * @tc.steps: step11. scroll to middle of content
     * @tc.expected: friction is not effected
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1);
}

/**
 * @tc.name: OnScrollCallback004
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ is 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is not bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is 0
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(SCROLL_HEIGHT);
    CreateDone();
    EXPECT_EQ(pattern_->scrollableDistance_, 0);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), -1);

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), -2);

    /**
     * @tc.steps: step4. Continue scroll up
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetTotalOffset(), -3);

    /**
     * @tc.steps: step5. Scroll down
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetTotalOffset(), -2);

    /**
     * @tc.steps: step6. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step7. scroll to below of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1);

    /**
     * @tc.steps: step8. Continue scroll down
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetTotalOffset(), 2);

    /**
     * @tc.steps: step9. Continue scroll down
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), 3);

    /**
     * @tc.steps: step10. Scroll up
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetTotalOffset(), 2);
}

/**
 * @tc.name: OnScrollCallback005
 * @tc.desc: Test AdjustOffset that return
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollCallback005, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. The delta is 0
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step2. The source is SCROLL_FROM_ANIMATION
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. The source is SCROLL_FROM_ANIMATION_SPRING
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE * 2);

    /**
     * @tc.steps: step4. The viewPortLength_ is 0
     * @tc.expected: AdjustOffset return
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateDone();
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
}
} // namespace OHOS::Ace::NG
