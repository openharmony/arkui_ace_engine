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

class ScrolleEventTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: Event001
 * @tc.desc: Test RegisterScrollEventTask
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, Event001, TestSize.Level1)
{
    auto event1 = [](Dimension, ScrollState) { return ScrollFrameResult(); };
    auto event2 = [](Dimension, Dimension) { return ScrollInfo(); };
    CreateWithContent([event1, event2](ScrollModelNG model) {
        model.SetOnScrollFrameBegin(event1);
        model.SetOnScrollBegin(event2);
    });

    /**
     * @tc.steps: step1. When set event
     * @tc.expected: scrollableEvent would has event that setted
     */
    ASSERT_NE(eventHub_->GetOnScrollFrameBegin(), nullptr);
    ASSERT_NE(eventHub_->GetScrollBeginEvent(), nullptr);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test attribute about onScroll,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, Event002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };
        model.SetOnScroll(std::move(event));
    });

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-ITEM_HEIGHT * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
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
    isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };
        model.SetAxis(Axis::HORIZONTAL);
        model.SetOnScroll(std::move(event));
    });

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->OnScrollCallback(-ITEM_WIDTH * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step6. Trigger event by ScrollToEdge,check offset
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
HWTEST_F(ScrolleEventTestNg, Event003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };
        model.SetOnScrollEdge(std::move(event));
    });

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-ITEM_HEIGHT * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
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
    isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEdgeEvent event = [&isTrigger](ScrollEdge) { isTrigger = true; };
        model.SetAxis(Axis::HORIZONTAL);
        model.SetOnScrollEdge(std::move(event));
    });

    /**
     * @tc.steps: step5. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-ITEM_WIDTH * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
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
HWTEST_F(ScrolleEventTestNg, Event004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test onScrollStart event in VERTICAL
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        OnScrollStartEvent startEvent = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollStart(std::move(startEvent));
        OnScrollStopEvent stopEvent = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollStop(std::move(stopEvent));
        ScrollEndEvent endEvent = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollEnd(std::move(endEvent));
    });

    /**
     * @tc.steps: step2. Trigger onScrollStart event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-ITEM_HEIGHT * TOTAL_LINE_NUMBER, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Trigger onScrollStart event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isTrigger = false;
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(isTrigger);

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
    pattern_->AnimateTo(ITEM_HEIGHT * TOTAL_LINE_NUMBER, 1.f, Curves::LINEAR, false);
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
HWTEST_F(ScrolleEventTestNg, Event005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     * @tc.expected: reachStart is true on first layout
     */
    bool reachStart = false;
    bool reachEnd = false;
    CreateWithContent([&reachStart, &reachEnd](ScrollModelNG model) {
        auto reachStartEvent = [&reachStart]() { reachStart = true; };
        model.SetOnReachStart(std::move(reachStartEvent));
        auto reachEndEvent = [&reachEnd]() { reachEnd = true; };
        model.SetOnReachEnd(std::move(reachEndEvent));
    });
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(reachStart);
    EXPECT_TRUE(pattern_->isInitialized_);

    /**
     * @tc.steps: step2. Trigger event by UpdateCurrentOffset
     * @tc.expected: reachEnd is true
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT * TOTAL_LINE_NUMBER - SCROLL_HEIGHT));
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
HWTEST_F(ScrolleEventTestNg, Event006, TestSize.Level1)
{
    bool isStartTrigger = false;
    bool isStopTrigger = false;
    CreateWithContent([&isStartTrigger, &isStopTrigger](ScrollModelNG model) {
        OnScrollStartEvent startEvent = [&isStartTrigger]() { isStartTrigger = true; };
        OnScrollStopEvent stopEvent = [&isStopTrigger]() { isStopTrigger = true; };
        model.SetOnScrollStart(std::move(startEvent));
        model.SetOnScrollStop(std::move(stopEvent));
    });

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
HWTEST_F(ScrolleEventTestNg, SetGestureEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar, touchEvent_
     * @tc.expected: touchEvent_ is initialized correctly
     */
    CreateWithContent();
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
HWTEST_F(ScrolleEventTestNg, SetMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar, mouseEvent_
     * @tc.expected: mouseEvent_ is initialized correctly
     */
    CreateWithContent();
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
 * @tc.desc: Test attribute about onWillScroll and onDidScroll,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in VERTICAL
     */
    bool isWillScrollTrigger = false;
    bool isDidScrollTrigger = false;
    Dimension willOffsetX;
    Dimension willOffsetY;
    Dimension didOffsetX;
    Dimension didOffsetY;
    auto willEvent = [&isWillScrollTrigger, &willOffsetX, &willOffsetY](
                         Dimension offsetX, Dimension offsetY, ScrollState state, ScrollSource source) {
        isWillScrollTrigger = true;
        willOffsetX = offsetX;
        willOffsetY = offsetY;
        TwoDimensionScrollResult result;
        result.xOffset = offsetX;
        result.yOffset = offsetY;
        return result;
    };
    auto didEvent = [&isDidScrollTrigger, &didOffsetX, &didOffsetY](
                        Dimension offsetX, Dimension offsetY, ScrollState state) {
        isDidScrollTrigger = true;
        didOffsetX = offsetX;
        didOffsetY = offsetY;
    };
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        NG::ScrollEvent event = [&isTrigger](Dimension, Dimension) { isTrigger = true; };
        model.SetOnScroll(std::move(event));
    });
    eventHub_->SetOnWillScrollEvent(std::move(willEvent));
    eventHub_->SetOnDidScrollEvent(std::move(didEvent));

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    pattern_->OnScrollCallback(-ITEM_HEIGHT * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);

    EXPECT_TRUE(isTrigger);
    EXPECT_TRUE(isWillScrollTrigger);
    EXPECT_TRUE(isDidScrollTrigger);
    EXPECT_EQ(willOffsetY.Value(), ITEM_HEIGHT * 2);
    EXPECT_EQ(didOffsetY.Value(), ITEM_HEIGHT * 2);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isWillScrollTrigger = false;
    isDidScrollTrigger = false;
    willOffsetY.Reset();
    didOffsetY.Reset();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);
    EXPECT_TRUE(isWillScrollTrigger);
    EXPECT_TRUE(isDidScrollTrigger);
    EXPECT_EQ(willOffsetY.Value(), -ITEM_HEIGHT * 2);
    EXPECT_EQ(didOffsetY.Value(), -ITEM_HEIGHT * 2);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test attribute about onWillScroll and onDidScroll,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, onWillScrollAndOnDidScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test event in HORIZONTAL
     */
    bool isWillScrollTrigger = false;
    bool isDidScrollTrigger = false;
    Dimension willOffsetX;
    Dimension willOffsetY;
    Dimension didOffsetX;
    Dimension didOffsetY;
    auto willEvent = [&isWillScrollTrigger, &willOffsetX, &willOffsetY](
                         Dimension offsetX, Dimension offsetY, ScrollState state, ScrollSource source) {
        isWillScrollTrigger = true;
        willOffsetX = offsetX;
        willOffsetY = offsetY;
        TwoDimensionScrollResult result;
        result.xOffset = offsetX;
        result.yOffset = offsetY;
        return result;
    };
    auto didEvent = [&isDidScrollTrigger, &didOffsetX, &didOffsetY](
                        Dimension offsetX, Dimension offsetY, ScrollState state) {
        isDidScrollTrigger = true;
        didOffsetX = offsetX;
        didOffsetY = offsetY;
    };
    CreateWithContent([](ScrollModelNG model) {
        model.SetAxis(Axis::HORIZONTAL);
    });
    eventHub_->SetOnWillScrollEvent(std::move(willEvent));
    eventHub_->SetOnDidScrollEvent(std::move(didEvent));

    /**
     * @tc.steps: step2. Trigger event by OnScrollCallback
     * @tc.expected: isTrigger is true
     */
    isWillScrollTrigger = false;
    isDidScrollTrigger = false;
    willOffsetX.Reset();
    didOffsetX.Reset();
    pattern_->OnScrollCallback(-ITEM_WIDTH * TOTAL_LINE_NUMBER, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillScrollTrigger);
    EXPECT_TRUE(isDidScrollTrigger);
    EXPECT_EQ(willOffsetX.Value(), ITEM_WIDTH * 2);
    EXPECT_EQ(didOffsetX.Value(), ITEM_WIDTH * 2);

    /**
     * @tc.steps: step3. Trigger event by ScrollToEdge
     * @tc.expected: isTrigger is true
     */
    isWillScrollTrigger = false;
    isDidScrollTrigger = false;
    willOffsetX.Reset();
    didOffsetX.Reset();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillScrollTrigger);
    EXPECT_TRUE(isDidScrollTrigger);
    EXPECT_EQ(willOffsetX.Value(), -ITEM_WIDTH * 2);
    EXPECT_EQ(didOffsetX.Value(), -ITEM_WIDTH * 2);
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test OnScrollCallback that has no effect
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, OnScrollCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Axis::NONE and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    EXPECT_FALSE(OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. animator_ is running and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateWithContent();
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Resume();
    EXPECT_FALSE(OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_UPDATE));
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: Test OnScrollCallback about trigger FireOnScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, OnScrollCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. no animator and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
        OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
        model.SetOnScrollStart(std::move(event));
    });
    OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. animator is Stopped and SCROLL_FROM_START
     * @tc.expected: Trigger FireOnScrollStart()
     */
    isTrigger = false;
    pattern_->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    pattern_->animator_->Stop();
    OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. animator is running and SCROLL_FROM_START
     * @tc.expected: because of scrollAbort_ is true, would not trigger event, and animator stop()
     */
    isTrigger = false;
    pattern_->animator_->Resume();
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    auto onScrollCallback = scrollable->callback_;
    onScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->animator_->IsStopped());
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: OnScrollCallback003
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ bigger than 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, OnScrollCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is two of ITEM_HEIGHT
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    float scrollableDistance = ITEM_HEIGHT * 2;
    EXPECT_EQ(pattern_->scrollableDistance_, scrollableDistance);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 1);

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 2);

    /**
     * @tc.steps: step4. Continue scroll up
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetCurrentPosition(), 3);

    /**
     * @tc.steps: step5. Scroll down
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetCurrentPosition(), 2);

    /**
     * @tc.steps: step6. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -scrollableDistance);

    /**
     * @tc.steps: step7. scroll to below of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -(scrollableDistance + 1));

    /**
     * @tc.steps: step8. Continue scroll down
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -(scrollableDistance + 2));

    /**
     * @tc.steps: step9. Continue scroll down
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetCurrentPosition(), -(scrollableDistance + 3));

    /**
     * @tc.steps: step10. Scroll up
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetCurrentPosition(), -(scrollableDistance + 2));

    /**
     * @tc.steps: step11. scroll to middle of content
     * @tc.expected: friction is not effected
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0);
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -1);
}

/**
 * @tc.name: OnScrollCallback004
 * @tc.desc: Test OnScrollCallback about AdjustOffset/UpdateCurrentOffset when scrollableDistance_ is 0
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, OnScrollCallback004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the content that total size is not bigger than Scroll Component
     * @tc.expected: The scrollableDistance_ is 0
     */
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateContent(VIEW_LINE_NUMBER);
    });
    EXPECT_EQ(pattern_->scrollableDistance_, 0);

    /**
     * @tc.steps: step2. scroll to above of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 1);

    /**
     * @tc.steps: step3. Continue scroll up
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 2);

    /**
     * @tc.steps: step4. Continue scroll up
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetCurrentPosition(), 3);

    /**
     * @tc.steps: step5. Scroll down
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_LT(pattern_->GetCurrentPosition(), 2);

    /**
     * @tc.steps: step6. Scroll to bottom for test other condition
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0);

    /**
     * @tc.steps: step7. scroll to below of content
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -1);

    /**
     * @tc.steps: step8. Continue scroll down
     * @tc.expected: friction is effected, but is 1
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetCurrentPosition(), -2);

    /**
     * @tc.steps: step9. Continue scroll down
     * @tc.expected: friction is effected
     */
    pattern_->OnScrollCallback(-1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetCurrentPosition(), -3);

    /**
     * @tc.steps: step10. Scroll up
     * @tc.expected: friction is not effected
     */
    pattern_->OnScrollCallback(1, SCROLL_FROM_UPDATE);
    EXPECT_GT(pattern_->GetCurrentPosition(), -2);
}

/**
 * @tc.name: OnScrollCallback005
 * @tc.desc: Test AdjustOffset that return
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEventTestNg, OnScrollCallback005, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });

    /**
     * @tc.steps: step1. The delta is 0
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(0, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step2. The source is SCROLL_FROM_ANIMATION
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));

    /**
     * @tc.steps: step3. The source is SCROLL_FROM_ANIMATION_SPRING
     * @tc.expected: AdjustOffset return
     */
    OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT * 2));

    /**
     * @tc.steps: step4. The viewPortLength_ is 0
     * @tc.expected: AdjustOffset return
     */
    ScrollModelNG model;
    model.Create();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    GetInstance();
    FlushLayoutTask(frameNode_);
    OnScrollCallback(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));
}
} // namespace OHOS::Ace::NG
