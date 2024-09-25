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
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
class ScrollEventTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: ScrollEvent001
 * @tc.desc: Test attribute about onScroll in VERTICAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollEvent001, TestSize.Level1)
{
    float scrollY;
    bool isToEdge = false;
    bool isReachStart = false;
    bool isReachEnd = false;
    NG::ScrollEvent onScrollEvent = [&scrollY](Dimension, Dimension y) { scrollY = y.ConvertToPx(); };
    NG::ScrollEdgeEvent scrollEdgeEvent = [&isToEdge](ScrollEdge) { isToEdge = true; };
    auto reachStartEvent = [&isReachStart]() { isReachStart = true; };
    auto reachEndEvent = [&isReachEnd]() { isReachEnd = true; };
    ScrollModelNG model = CreateScroll();
    model.SetOnScroll(std::move(onScrollEvent));
    model.SetOnScrollEdge(std::move(scrollEdgeEvent));
    model.SetOnReachStart(std::move(reachStartEvent));
    model.SetOnReachEnd(std::move(reachEndEvent));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger reachStartEvent init
     */
    EXPECT_TRUE(isReachStart);

    /**
     * @tc.steps: step2. ScrollTo ITEM_MAIN_SIZE
     * @tc.expected: Trigger onScrollEvent
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(scrollY, ITEM_MAIN_SIZE);
    EXPECT_FALSE(isToEdge);

    /**
     * @tc.steps: step3. ScrollTo bottom
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachEndEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(scrollY, VERTICAL_SCROLLABLE_DISTANCE - ITEM_MAIN_SIZE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachEnd);

    /**
     * @tc.steps: step4. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    isToEdge = false;
    isReachStart = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(scrollY, -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachStart);
}

/**
 * @tc.name: ScrollEvent002
 * @tc.desc: Test attribute about onScroll in HORIZONTAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollEvent002, TestSize.Level1)
{
    float scrollX;
    bool isToEdge = false;
    bool isReachStart = false;
    bool isReachEnd = false;
    NG::ScrollEvent onScrollEvent = [&scrollX](Dimension x, Dimension) { scrollX = x.ConvertToPx(); };
    NG::ScrollEdgeEvent scrollEdgeEvent = [&isToEdge](ScrollEdge) { isToEdge = true; };
    auto reachStartEvent = [&isReachStart]() { isReachStart = true; };
    auto reachEndEvent = [&isReachEnd]() { isReachEnd = true; };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    model.SetOnScroll(std::move(onScrollEvent));
    model.SetOnScrollEdge(std::move(scrollEdgeEvent));
    model.SetOnReachStart(std::move(reachStartEvent));
    model.SetOnReachEnd(std::move(reachEndEvent));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger reachStartEvent init
     */
    EXPECT_TRUE(isReachStart);

    /**
     * @tc.steps: step2. ScrollTo ITEM_MAIN_SIZE
     * @tc.expected: Trigger onScrollEvent
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(scrollX, ITEM_MAIN_SIZE);
    EXPECT_FALSE(isToEdge);

    /**
     * @tc.steps: step2. ScrollTo bottom
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachEndEvent
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(scrollX, HORIZONTAL_SCROLLABLE_DISTANCE - ITEM_MAIN_SIZE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachEnd);

    /**
     * @tc.steps: step3. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    isToEdge = false;
    isReachStart = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(scrollX, -HORIZONTAL_SCROLLABLE_DISTANCE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachStart);
}

/**
 * @tc.name: ScrollEvent003
 * @tc.desc: Test attribute about onScrollStart and onScrollStop and onScrollEnd,
 * Event is triggered while scrolling start
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test onScrollStart event in VERTICAL
     */
    bool isStart = false;
    bool isStop = false;
    bool isEnd = false;
    OnScrollStartEvent startEvent = [&isStart]() { isStart = true; };
    OnScrollStopEvent stopEvent = [&isStop]() { isStop = true; };
    ScrollEndEvent endEvent = [&isEnd]() { isEnd = true; };
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetOnScrollStart(std::move(startEvent));
    model.SetOnScrollStop(std::move(stopEvent));
    model.SetOnScrollEnd(std::move(endEvent));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. DragStart
     */
    GestureEvent gesture;
    DragStart(gesture);
    EXPECT_TRUE(isStart);

    /**
     * @tc.steps: step2. DragUpdate over top
     * @tc.expected: Scroll with drag
     */
    const float dragDelta = 10.f;
    gesture.SetMainDelta(dragDelta);
    DragUpdate(gesture);
    EXPECT_EQ(GetChildY(frameNode_, 0), dragDelta);

    /**
     * @tc.steps: step3. DragEnd
     * @tc.expected: Scroll back with animation
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    gesture.SetMainVelocity(DRAG_VELOCITY);
    DragEnd(gesture);
    EXPECT_EQ(GetChildY(frameNode_, 0), dragDelta);
    EXPECT_TRUE(VerifyTickPosition(dragDelta / TICK));
    EXPECT_TRUE(VerifyTickPosition(0));
    EXPECT_TRUE(isEnd);
    EXPECT_TRUE(isStop);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test attribute about onWillScroll and onDidScroll in VERTICAL Layout,
 * Event is triggered while scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
{
    float willOffsetY;
    float didOffsetY;
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
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger event by ScrollToEdge
     * @tc.expected: WillScrollEvent and DisScrollEvent are both triggered
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(willOffsetY, VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetY, VERTICAL_SCROLLABLE_DISTANCE);
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
    CreateScrollDone();

    /**
     * @tc.steps: step1. Trigger event by ScrollToEdge
     * @tc.expected: WillScrollEvent and DisScrollEvent are both triggered
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(willOffsetX, HORIZONTAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetX, HORIZONTAL_SCROLLABLE_DISTANCE);
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
    CreateScrollDone();
    EXPECT_FALSE(OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step2. animator_ is running and SCROLL_FROM_UPDATE
     * @tc.expected: Do nothing
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
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
    CreateScrollDone();
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
    CreateScrollDone();
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
    EXPECT_GT(pattern_->GetTotalOffset(), -2);

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
    EXPECT_LT(pattern_->GetTotalOffset(), (scrollableDistance + 2));

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
    CreateScrollDone();
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
    EXPECT_GT(pattern_->GetTotalOffset(), -2);

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
    EXPECT_LT(pattern_->GetTotalOffset(), 2);

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
    CreateScrollDone();

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
    CreateScrollDone();
    OnScrollCallback(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
}
} // namespace OHOS::Ace::NG
