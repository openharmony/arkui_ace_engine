/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class ScrollEventTestNg : public ScrollTestNg {
public:
    AssertionResult ScrollToNode(const RefPtr<FrameNode>& focusFrameNode, float expectOffset);
};

AssertionResult ScrollEventTestNg::ScrollToNode(const RefPtr<FrameNode>& focusFrameNode, float expectOffset)
{
    pattern_->ScrollToNode(focusFrameNode);
    FlushUITasks();
    return IsEqual(pattern_->GetTotalOffset(), expectOffset);
}

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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(scrollY, VERTICAL_SCROLLABLE_DISTANCE - ITEM_MAIN_SIZE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachEnd);

    /**
     * @tc.steps: step4. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    isToEdge = false;
    isReachStart = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(scrollX, HORIZONTAL_SCROLLABLE_DISTANCE - ITEM_MAIN_SIZE);
    EXPECT_TRUE(isToEdge);
    EXPECT_TRUE(isReachEnd);

    /**
     * @tc.steps: step3. ScrollTo top
     * @tc.expected: Trigger onScrollEvent/scrollEdgeEvent/reachStartEvent
     */
    isToEdge = false;
    isReachStart = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
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
    bool isStart = false;
    bool isStop = false;
    bool isEnd = false;
    OnScrollStartEvent startEvent = [&isStart]() { isStart = true; };
    OnScrollStopEvent stopEvent = [&isStop]() { isStop = true; };
    ScrollEndEvent endEvent = [&isEnd]() { isEnd = true; };
    ScrollModelNG model = CreateScroll();
    model.SetOnScrollStart(std::move(startEvent));
    model.SetOnScrollStop(std::move(stopEvent));
    model.SetOnScrollEnd(std::move(endEvent));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. DragStart
     */
    DragStart(frameNode_, Offset());
    EXPECT_TRUE(isStart);

    /**
     * @tc.steps: step2. DragUpdate
     * @tc.expected: Scroll with drag
     */
    float dragDelta = -10.f;
    DragUpdate(dragDelta);
    EXPECT_TRUE(Position(dragDelta));
    /**
     * @tc.steps: step3. DragEnd
     * @tc.expected: Continue inertial scrolling
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float velocityDelta = -100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(willOffsetX, HORIZONTAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(didOffsetX, HORIZONTAL_SCROLLABLE_DISTANCE);
}

/**
 * @tc.name: Axis001
 * @tc.desc: Test Axis::NONE, would not scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, Axis001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::NONE);
    CreateContent();
    CreateScrollDone();

    Offset startOffset = Offset();
    float dragDelta = -10.f;
    DragAction(frameNode_, startOffset, dragDelta, 0);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Handle drag not over scrollable distance
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    Offset startOffset = Offset();
    float dragDelta = -10.f;
    float velocityDelta = -200;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Handle drag in Horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDrag002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));

    Offset startOffset = Offset();
    float dragDelta = 10.f;
    float velocityDelta = 200;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-dragDelta));
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta));
}

/**
 * @tc.name: HandleDrag003
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDrag003, TestSize.Level1)
{
    double touchPosX = 150.0;
    double touchPosY = 500.0;
    float offset = 10.0f;
    float velocity = 1200.0f;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    model.SetDisplayMode(static_cast<int>(DisplayMode::OFF));
    auto scrollProxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(scrollProxy);
    CreateContent();
    CreateScrollDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);

    GestureEvent info;
    info.SetMainVelocity(velocity);
    info.SetGlobalPoint(Point(touchPosX, touchPosY));
    info.SetGlobalLocation(Offset(touchPosX, touchPosY));
    info.SetSourceTool(SourceTool::FINGER);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragStart(info);

    // Update 1 finger position.
    info.SetGlobalLocation(Offset(touchPosX, touchPosY + offset));
    info.SetGlobalPoint(Point(touchPosX, touchPosY + offset));
    info.SetMainVelocity(velocity);
    info.SetMainDelta(offset);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 10.0f);

    // Update 2 finger position.
    info.SetGlobalLocation(Offset(touchPosX, touchPosY + offset));
    info.SetGlobalPoint(Point(touchPosX, touchPosY + offset));
    info.SetMainVelocity(velocity);
    info.SetMainDelta(offset);
    pattern_->scrollableEvent_->GetScrollable()->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 20.0f);

    // Lift finger and end List sliding.
    info.SetMainVelocity(0.0);
    info.SetMainDelta(0.0);
    pattern_->scrollableEvent_->GetScrollable()->lastMainDelta_ = 0.0;
    pattern_->scrollableEvent_->GetScrollable()->HandleDragEnd(info);
    pattern_->scrollableEvent_->GetScrollable()->isDragging_ = false;
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 20.0f);
}

/**
 * @tc.name: HandleDragOverScroll001
 * @tc.desc: Handle drag over top in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. DragUpdate over top
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = 10.f;
    DragUpdate(dragDelta);
    EXPECT_TRUE(Position(dragDelta));
    DragUpdate(dragDelta);
    EXPECT_EQ(GetChildY(frameNode_, 0), dragDelta * 2);

    /**
     * @tc.steps: step2. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = GetChildY(frameNode_, 0);
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float velocityDelta = 100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition((currentOffset + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll002
 * @tc.desc: Handle drag over bottom in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. Scroll to bottom
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. DragUpdate over bottom
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = -10.f;
    DragUpdate(dragDelta);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE + dragDelta));
    DragUpdate(dragDelta);
    EXPECT_EQ(GetChildY(frameNode_, 0), -VERTICAL_SCROLLABLE_DISTANCE + dragDelta * 2);

    /**
     * @tc.steps: step3. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = GetChildY(frameNode_, 0);
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float velocityDelta = -100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition(frameNode_,
        -VERTICAL_SCROLLABLE_DISTANCE + (currentOffset + VERTICAL_SCROLLABLE_DISTANCE + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: HandleDragOverScroll003
 * @tc.desc: Handle drag over top and drag back with velocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag over the top
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragStart(frameNode_, Offset());
    DragUpdate(10);
    EXPECT_TRUE(Position(10));

    /**
     * @tc.steps: step2. Drag back and drag with velocity
     * @tc.expected: Inertial scrolling back
     */
    DragUpdate(-5);
    EXPECT_LT(GetChildY(frameNode_, 0), 10);
    EXPECT_GT(GetChildY(frameNode_, 0), 5);

    float currentOffset = GetChildY(frameNode_, 0);
    float velocityDelta = -100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickPosition(velocityDelta, 0));
    EXPECT_TRUE(TickPosition(velocityDelta + currentOffset, velocityDelta + currentOffset));
}

/**
 * @tc.name: HandleDragOverScroll004
 * @tc.desc: Handle drag over in unScrollable scroll, and set AlwaysEnabled, still can drag over
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has no scrollable distance, and AlwaysEnabled
     * @tc.expected: Still can drag over
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(HEIGHT);
    CreateScrollDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_EQ(pattern_->GetScrollableDistance(), 0);

    float dragDelta = 10.f;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(frameNode_, Offset(), dragDelta, DRAG_VELOCITY);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(DRAG_VELOCITY, dragDelta + DRAG_VELOCITY));
    EXPECT_TRUE(TickPosition((dragDelta + DRAG_VELOCITY) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll005
 * @tc.desc: Handle drag over edge in EdgeEffect::FADE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::FADE
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    DragAction(frameNode_, Offset(), -10, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: HandleDragOverScroll006
 * @tc.desc: Handle drag over edge in EdgeEffect::NONE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleDragOverScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::NONE
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    DragAction(frameNode_, Offset(), -10, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: ScrollToNode001
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollToNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ScrollToNode content child
     * @tc.expected: currentOffset_ is correct
     */
    CreateScroll();
    CreateContent();
    CreateContentChild();
    CreateScrollDone();
    EXPECT_TRUE(ScrollToNode(contentChildren_[3], 0));
    EXPECT_TRUE(ScrollToNode(contentChildren_[4], ITEM_MAIN_SIZE));
    EXPECT_TRUE(ScrollToNode(contentChildren_[5], ITEM_MAIN_SIZE * 2));
    EXPECT_TRUE(ScrollToNode(contentChildren_[3], ITEM_MAIN_SIZE * 2));
    EXPECT_TRUE(ScrollToNode(contentChildren_[0], 0));

    /**
     * @tc.steps: step2. ScrollToNode itSelf
     * @tc.expected: currentOffset_ is zero
     */
    EXPECT_TRUE(ScrollToNode(frameNode_, 0));
    EXPECT_TRUE(ScrollToNode(GetChildFrameNode(frameNode_, 0), 0));
}

/**
 * @tc.name: ScrollToNode002
 * @tc.desc: Test ScrollToNode in HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollToNode002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateContentChild();
    CreateScrollDone();
    EXPECT_TRUE(ScrollToNode(contentChildren_[3], 160.f));
    EXPECT_TRUE(ScrollToNode(contentChildren_[4], 260.f));
    EXPECT_TRUE(ScrollToNode(contentChildren_[5], 360.f));
    EXPECT_TRUE(ScrollToNode(contentChildren_[3], 300.f));
    EXPECT_TRUE(ScrollToNode(contentChildren_[0], 0));
}

/**
 * @tc.name: ScrollToNode003
 * @tc.desc: Test ScrollToNode when animate is running, can not scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, ScrollToNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Play animate
     * @tc.expected: ScrollToNode can not scroll
     */
    CreateScroll();
    CreateContent();
    CreateContentChild();
    CreateScrollDone();
    pattern_->isAnimationStop_ = false;
    EXPECT_FALSE(pattern_->AnimateStoped());
    EXPECT_TRUE(ScrollToNode(contentChildren_[8], 0.f));
}

/**
 * @tc.name: IntervalSnap001
 * @tc.desc: Test snap intervalSize ScrollSnapAlign::START
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, IntervalSnap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set intervalSize for check align edge
     * @tc.expected: Will align end when at bottom
     */
    const float intervalSize = 90; // check align start
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Scroll down less than half of intervalSize
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float halfInterval = intervalSize / 2;
    float delta = 1 - halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step3. Scroll down greater than half of intervalSize
     * @tc.expected: Scroll to next interval
     */
    delta = -halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - intervalSize) / TICK));
    EXPECT_TRUE(TickPosition(-intervalSize));

    /**
     * @tc.steps: step4. Scroll to bottom
     * @tc.expected: Align end
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step5. Scroll up a little delta
     * @tc.expected: Scroll to prev interval
     */
    float lastIntervalSize = CONTENT_MAIN_SIZE - 11 * intervalSize;
    float viewIntervalSize = 4 * intervalSize;
    float startOffset = intervalSize - (HEIGHT - viewIntervalSize - lastIntervalSize);
    delta = 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition((startOffset + delta) / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(startOffset - VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step6. Scroll up less than half of intervalSize
     * @tc.expected: Scroll back
     */
    float currentOffset = GetChildY(frameNode_, 0);
    delta = halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(delta / TICK + currentOffset));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step7. Scroll up greater than half of intervalSize
     * @tc.expected: Scroll to prev interval
     */
    delta = halfInterval + 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(intervalSize + currentOffset - (intervalSize - delta) / TICK));
    EXPECT_TRUE(TickPosition(intervalSize + currentOffset));
}

/**
 * @tc.name: IntervalSnap002
 * @tc.desc: Test snap intervalSize ScrollSnapAlign::END
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, IntervalSnap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set intervalSize for check align edge
     * @tc.expected: Will align start when at top
     */
    const float intervalSize = 90; // check align end
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::END, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll down a little delta
     * @tc.expected: Scroll to next interval
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float halfInterval = intervalSize / 2;
    const float endAlignOffset = 40;
    float delta = -1;
    ScrollBy(0, delta);
    EXPECT_TRUE(TickPosition((endAlignOffset - intervalSize + delta) / TICK));
    EXPECT_TRUE(TickPosition(endAlignOffset - intervalSize));

    /**
     * @tc.steps: step3. Scroll down less than half of intervalSize
     * @tc.expected: Scroll back
     */
    float currentOffset = GetChildY(frameNode_, 0);
    delta = 1 - halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(TickPosition(currentOffset + delta / TICK));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step4. Scroll down greater than half of intervalSize
     * @tc.expected: Scroll to next interval
     */
    delta = -halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(TickPosition(currentOffset - intervalSize + (intervalSize + delta) / TICK));
    EXPECT_TRUE(TickPosition(currentOffset - intervalSize));

    /**
     * @tc.steps: step5. Scroll to top
     * @tc.expected: Align start
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: IntervalSnap003
 * @tc.desc: Test snap intervalSize ScrollSnapAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, IntervalSnap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set intervalSize for check align edge
     * @tc.expected: Will align start/end when at top/bottom
     */
    const float intervalSize = 90;
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::CENTER, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll down a little delta
     * @tc.expected: Scroll to next interval
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float halfInterval = intervalSize / 2;
    float centerPosition = HEIGHT / 2;
    float centerOffset = halfInterval - centerPosition + 2 * intervalSize;
    float delta = -1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - centerOffset) / TICK));
    EXPECT_TRUE(TickPosition(-centerOffset));

    /**
     * @tc.steps: step3. Scroll down less than half of intervalSize
     * @tc.expected: Scroll back
     */
    float currentOffset = -centerOffset;
    delta = 1 - halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(currentOffset + delta));
    EXPECT_TRUE(TickPosition(currentOffset + delta / TICK));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step4. Scroll down greater than half of intervalSize
     * @tc.expected: Scroll to next interval
     */
    delta = -halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(currentOffset + delta));
    EXPECT_TRUE(TickPosition(currentOffset - intervalSize - delta / TICK));
    EXPECT_TRUE(TickPosition(currentOffset - intervalSize));

    /**
     * @tc.steps: step5. Scroll to bottom
     * @tc.expected: Align end
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step6. Scroll up a little delta
     * @tc.expected: Scroll to prev interval
     */
    centerOffset = halfInterval - 10;
    delta = 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition((centerOffset + delta) / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(centerOffset - VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step7. Scroll up less than half of intervalSize
     * @tc.expected: Scroll back
     */
    currentOffset = GetChildY(frameNode_, 0);
    delta = halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(delta / TICK + currentOffset));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step8. Scroll up greater than half of intervalSize
     * @tc.expected: Scroll to prev interval
     */
    delta = halfInterval + 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(intervalSize + currentOffset - (intervalSize - delta) / TICK));
    EXPECT_TRUE(TickPosition(intervalSize + currentOffset));
}

/**
 * @tc.name: IntervalSnap004
 * @tc.desc: Test snap set intervalSize percent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, IntervalSnap004, TestSize.Level1)
{
    /**
     * @tc.steps: set snap intervalSize percent
     * @tc.expected: CalcPredictSnapOffset has value
     */
    Dimension intervalSize = Dimension(0.1f, DimensionUnit::PERCENT);
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->CalcPredictSnapOffset(10.f).has_value());
}

/**
 * @tc.name: IntervalSnap005
 * @tc.desc: Test snap set snapPaginations percent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, IntervalSnap005, TestSize.Level1)
{
    /**
     * @tc.steps: set snap snapPaginations percent
     * @tc.expected: CalcPredictSnapOffset has value
     */
    Dimension intervalSize = Dimension(0.f, DimensionUnit::PERCENT);
    std::vector<Dimension> snapPaginations = { Dimension(0.1f, DimensionUnit::PERCENT),
        Dimension(0.2f, DimensionUnit::PERCENT) };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->CalcPredictSnapOffset(10.f).has_value());
}

/**
 * @tc.name: CalcPredictNextSnapOffset001
 * @tc.desc: Test CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, CalcPredictNextSnapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set intervalSize to generate snapOffsets_.
     */
    const float intervalSize = 100.f; // check align start
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    const float delta = -40.f;
    auto predictSnapOffset = pattern_->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), 0.f);

    predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, 0.f, 0.f, SnapDirection::BACKWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), -intervalSize);

    pattern_->currentOffset_ = -100.f;
    predictSnapOffset = pattern_->CalcPredictSnapOffset(-60.f, 0.f, 0.f, SnapDirection::BACKWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), -intervalSize);

    predictSnapOffset = pattern_->CalcPredictSnapOffset(-100.f, 0.f, 0.f, SnapDirection::BACKWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), -2 * intervalSize);

    predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, 0.f, 0.f, SnapDirection::FORWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), intervalSize);

    pattern_->currentOffset_ = -200.f;
    predictSnapOffset = pattern_->CalcPredictSnapOffset(60.f, 0.f, 0.f, SnapDirection::FORWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), intervalSize);

    predictSnapOffset = pattern_->CalcPredictSnapOffset(100.f, 0.f, 0.f, SnapDirection::FORWARD);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_FLOAT_EQ(predictSnapOffset.value(), 2 * intervalSize);
}

/**
 * @tc.name: SnapPaginations001
 * @tc.desc: Test snap snapPaginations ScrollSnapAlign::START
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SnapPaginations001, TestSize.Level1)
{
    float intervalSize = 0;
    const float firstPagination = 100;
    const float secondPagination = 150;
    std::vector<Dimension> snapPaginations = {
        Dimension(firstPagination),
        Dimension(secondPagination),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Scroll down less than half of first snapPaginations
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float delta = 1 - firstPagination / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll down greater than half of first snapPaginations
     * @tc.expected: Scroll to first snapPaginations
     */
    delta = -firstPagination / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - firstPagination) / TICK));
    EXPECT_TRUE(TickPosition(-firstPagination));

    /**
     * @tc.steps: step3. Scroll down less than half of second snapPaginations
     * @tc.expected: Scroll back
     */
    delta = 1 - (secondPagination - firstPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination));
    EXPECT_TRUE(TickPosition(delta / TICK - firstPagination));
    EXPECT_TRUE(TickPosition(-firstPagination));

    /**
     * @tc.steps: step4. Scroll down greater than half of second snapPaginations
     * @tc.expected: Scroll to second snapPaginations
     */
    delta = (firstPagination - secondPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination));
    EXPECT_TRUE(TickPosition((delta - firstPagination - secondPagination) / TICK));
    EXPECT_TRUE(TickPosition(-secondPagination));
}

/**
 * @tc.name: SnapPaginations002
 * @tc.desc: Test snap snapPaginations ScrollSnapAlign::END
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SnapPaginations002, TestSize.Level1)
{
    float intervalSize = 0;
    const float firstPagination = CONTENT_MAIN_SIZE - 150;
    const float secondPagination = CONTENT_MAIN_SIZE - 100;
    std::vector<Dimension> snapPaginations = {
        Dimension(firstPagination),
        Dimension(secondPagination),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::END, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step1. Scroll down less than half of first snapPaginations
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float delta = 1 - (firstPagination - HEIGHT) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll down greater than half of first snapPaginations
     * @tc.expected: Scroll to first snapPaginations
     */
    delta = (HEIGHT - firstPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(-337.5));
    EXPECT_TRUE(TickPosition(-450));

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: Align start
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: SnapPaginations003
 * @tc.desc: Test snap snapPaginations ScrollSnapAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SnapPaginations003, TestSize.Level1)
{
    float intervalSize = 0;
    const float firstPagination = 500;
    const float secondPagination = 650;
    std::vector<Dimension> snapPaginations = {
        Dimension(firstPagination),
        Dimension(secondPagination),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::CENTER, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step1. Scroll down less than half
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float delta = -24;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll down greater than half
     * @tc.expected: Scroll to first snapPaginations
     */
    delta = -25;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - 50) / TICK));
    EXPECT_TRUE(TickPosition(-50));

    /**
     * @tc.steps: step3. Scroll down less than half of second snapPaginations
     * @tc.expected: Scroll back
     */
    float currentOffset = GetChildY(frameNode_, 0);
    delta = -161.5;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(delta / TICK + currentOffset));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step4. Scroll down greater than half of second snapPaginations
     * @tc.expected: Scroll to second snapPaginations
     */
    delta = -162.5;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(-293.75));
    EXPECT_TRUE(TickPosition(-375));

    /**
     * @tc.steps: step5. Scroll to bottom
     * @tc.expected: Align end
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: SnapPaginations004
 * @tc.desc: Test snap snapPaginations:PERCENT
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SnapPaginations004, TestSize.Level1)
{
    float intervalSize = 0;
    const float firstPagination = 100;
    const float secondPagination = 150;
    std::vector<Dimension> snapPaginations = {
        Dimension(firstPagination / HEIGHT, DimensionUnit::PERCENT),
        Dimension(secondPagination / HEIGHT, DimensionUnit::PERCENT),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Scroll down less than half of first snapPaginations
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float delta = 1 - firstPagination / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll down greater than half of first snapPaginations
     * @tc.expected: Scroll to first snapPaginations
     */
    delta = -firstPagination / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - firstPagination) / TICK));
    EXPECT_TRUE(TickPosition(-firstPagination));

    /**
     * @tc.steps: step3. Scroll down less than half of second snapPaginations
     * @tc.expected: Scroll back
     */
    delta = 1 - (secondPagination - firstPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination));
    EXPECT_TRUE(TickPosition(delta / TICK - firstPagination));
    EXPECT_TRUE(TickPosition(-firstPagination));

    /**
     * @tc.steps: step4. Scroll down greater than half of second snapPaginations
     * @tc.expected: Scroll to second snapPaginations
     */
    delta = (firstPagination - secondPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination));
    EXPECT_TRUE(TickPosition((delta - firstPagination - secondPagination) / TICK));
    EXPECT_TRUE(TickPosition(-secondPagination));
}

/**
 * @tc.name: SnapPaginations005
 * @tc.desc: Test snap enableSnapToSide:false, this side will not snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SnapPaginations005, TestSize.Level1)
{
    float intervalSize = 0;
    const float firstPagination = 100;
    const float secondPagination = 150;
    const float thirdPagination = 300;
    std::vector<Dimension> snapPaginations = {
        Dimension(firstPagination),
        Dimension(secondPagination),
        Dimension(thirdPagination),
    };
    std::pair<bool, bool> enableSnapToSide = { false, false };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Scroll down greater than half of first snapPaginations
     * @tc.expected: Not continue scroll in first snapPaginations
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    float delta = -firstPagination / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta));
    EXPECT_TRUE(TickPosition(delta));

    /**
     * @tc.steps: step2. Scroll down less than half of second snapPaginations
     * @tc.expected: Scroll back
     */
    delta += 1 - (secondPagination - firstPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination / 2));
    EXPECT_TRUE(TickPosition(frameNode_, (delta + firstPagination / 2) / TICK) - firstPagination);
    EXPECT_TRUE(TickPosition(-firstPagination));

    /**
     * @tc.steps: step3. Scroll down greater than half of second snapPaginations
     * @tc.expected: Scroll to second snapPaginations
     */
    delta = (firstPagination - secondPagination) / 2;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - firstPagination));
    EXPECT_TRUE(TickPosition((delta - firstPagination - secondPagination) / TICK));
    EXPECT_TRUE(TickPosition(-secondPagination));

    /**
     * @tc.steps: step4. Scroll to bottom, than scroll up greater than half of last snapPaginations
     * @tc.expected: Not continue scroll in last snapPaginations
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    delta = thirdPagination / 2 + 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE + delta));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE + delta));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE + delta));
}

/**
 * @tc.name: EnablePaging001
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    auto viewPortLength = pattern_->GetMainContentSize();
    pattern_->scrollableDistance_ = viewPortLength * 10;
    pattern_->currentOffset_ = -viewPortLength * 5 - 10.0f;
    SizeF viewPortExtent(WIDTH, viewPortLength * 11);
    pattern_->viewPortExtent_ = viewPortExtent;
    pattern_->SetIntervalSize(Dimension(static_cast<double>(viewPortLength)));
    pattern_->CaleSnapOffsets();

    /**
     * @tc.steps: step2. dragDistance and dragSpeed less than threshold
     * @tc.expected: stay on the current page
     */
    auto dragDistance = viewPortLength * 0.5 - 1;
    auto dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD - 1;
    auto predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, dragDistance, dragSpeed, SnapDirection::NONE);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_EQ(predictSnapOffset.value(), 10.f);

    /**
     * @tc.steps: step3. dragDistance and dragSpeed larger than threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5 * 5;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD * 5;
    predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, dragDistance, dragSpeed, SnapDirection::NONE);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);

    /**
     * @tc.steps: step4. dragDistance equals threshold and dragSpeed less than threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD - 1;
    predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, dragDistance, dragSpeed, SnapDirection::NONE);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);

    /**
     * @tc.steps: step5. dragDistance less than threshold and dragSpeed equals threshold
     * @tc.expected: the absolute value of predictSnapOffset.value() less than viewPortLength
     */
    dragDistance = viewPortLength * 0.5 - 1;
    dragSpeed = SCROLL_PAGING_SPEED_THRESHOLD;
    predictSnapOffset = pattern_->CalcPredictSnapOffset(0.f, dragDistance, dragSpeed, SnapDirection::NONE);
    EXPECT_TRUE(predictSnapOffset.has_value());
    EXPECT_LT(abs(predictSnapOffset.value()), viewPortLength);
    EXPECT_GT(predictSnapOffset.value(), 0);
}

/**
 * @tc.name: EnablePaging002
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set enablePaging.
     * @tc.expected: the value of GetEnablePaging() is VALID
     */
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);
    EXPECT_EQ(pattern_->IsEnablePagingValid(), true);

    /**
     * @tc.steps: step2. Create scroll, first set enablePaging and than set snap.
     * @tc.expected: the value of IsEnablePagingValid() is false
     */
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };
    std::pair<bool, bool> enableSnapToSide = { false, false };
    auto scrollSnapAlign = ScrollSnapAlign::START;
    model = CreateScroll();
    model.SetEnablePaging(true);
    model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->IsEnablePagingValid(), false);

    /**
     * @tc.steps: step3. Create scroll, first set snap and than set enablePaging.
     * @tc.expected: the value of IsEnablePagingValid() is false
     */
    model = CreateScroll();
    model.SetScrollSnap(scrollSnapAlign, intervalSize, snapPaginations, enableSnapToSide);
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->IsEnablePagingValid(), false);

    /**
     * @tc.steps: step4. Create scroll, set enablePaging true and than set enablePaging false.
     * @tc.expected: the value of GetEnablePaging() is INVALID
     */
    model = CreateScroll();
    model.SetEnablePaging(true);
    model.SetEnablePaging(false);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::INVALID);
    EXPECT_EQ(pattern_->IsEnablePagingValid(), false);

    /**
     * @tc.steps: step5. Create scroll, set enablePaging false and than set enablePaging true.
     * @tc.expected: the value of GetEnablePaging() is VALID
     */
    model = CreateScroll();
    model.SetEnablePaging(false);
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);
    EXPECT_EQ(pattern_->IsEnablePagingValid(), true);
}

/**
 * @tc.name: EnablePaging003
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Scroll down less than half of HEIGHT
     * @tc.expected: Scroll back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float halfHeight = HEIGHT / 2;
    float delta = 1 - halfHeight;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition(delta / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll down greater than half of HEIGHT
     * @tc.expected: Scroll to next page
     */
    delta = -halfHeight;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - HEIGHT) / 2));
    EXPECT_TRUE(TickPosition(-HEIGHT));

    /**
     * @tc.steps: step3. Scroll down less than half of last page
     * @tc.expected: Scroll back
     */
    const float lastPageHeight = 200;
    const float halfLastPageHeight = lastPageHeight / 2;
    float currentOffset = -HEIGHT;
    delta = 1 - halfLastPageHeight;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition(delta / TICK + currentOffset));
    EXPECT_TRUE(TickPosition(currentOffset));

    /**
     * @tc.steps: step4. Scroll down greater than half of last page
     * @tc.expected: Scroll to next page
     */
    delta = -halfLastPageHeight;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta + currentOffset));
    EXPECT_TRUE(TickPosition((lastPageHeight + delta) / 2 - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step5. Scroll up less than half of last page
     * @tc.expected: Scroll back
     */
    delta = halfLastPageHeight;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(delta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step6. Scroll up greater than half of last page
     * @tc.expected: Scroll to prev page
     */
    delta = halfLastPageHeight + 1;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-449.5));
    EXPECT_TRUE(TickPosition(lastPageHeight - VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: EnablePaging004
 * @tc.desc: Test set snap and EnablePaging at same time
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging004, TestSize.Level1)
{
    /**
     * @tc.steps: step3. Set snap and EnablePaging at same time
     * @tc.expected: Only snap take effect
     */
    const float intervalSize = 90;
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(intervalSize), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float halfInterval = intervalSize / 2;
    float delta = -halfInterval;
    ScrollBy(0, delta);
    EXPECT_TRUE(Position(delta));
    EXPECT_TRUE(TickPosition((delta - intervalSize) / TICK));
    EXPECT_TRUE(TickPosition(-intervalSize));
}

/**
 * @tc.name: SetEffectEdge001
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SetEffectEdge001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::START);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -VERTICAL_SCROLLABLE_DISTANCE);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -VERTICAL_SCROLLABLE_DISTANCE);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);
    pattern_->UpdateCurrentOffset(100, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 100);
}

/**
 * @tc.name: SetEffectEdge002
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SetEffectEdge002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::END);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    pattern_->UpdateCurrentOffset(100, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -VERTICAL_SCROLLABLE_DISTANCE - 100);
}

/**
 * @tc.name: EnablePaging005
 * @tc.desc: Test enablePaging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set enablePaging true.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    auto viewPortLength = pattern_->GetMainContentSize();

    /**
     * @tc.steps: step2. dragSpeed larger than threshold
     * @tc.expected: Trigger snap animation only once
     */
    DragStart(frameNode_, Offset());
    DragUpdate(-10);
    DragEnd(-SCROLL_PAGING_SPEED_THRESHOLD - 1);
    EXPECT_TRUE(TickPosition(-viewPortLength));
    EXPECT_TRUE(pattern_->IsScrollableStopped());

    /**
     * @tc.steps: step3. Set the difference between the offset and the limit point to 0.01
     * @tc.expected: Not trigger snap animation
     */
    pattern_->currentOffset_ = -viewPortLength + 0.01f;
    FlushUITasks();
    EXPECT_TRUE(pattern_->IsScrollableStopped());
}

/**
 * @tc.name: EnablePaging006
 * @tc.desc: Test enablePaging amd onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, EnablePaging006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set enablePaging true.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    ScrollState state = ScrollState::IDLE;
    auto didEvent = [&state](Dimension, Dimension, ScrollState value) { state = value; };
    model.SetOnDidScroll(std::move(didEvent));
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step2. dragSpeed larger than threshold
     * @tc.expected: Trigger snap animation
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragStart(frameNode_, Offset());
    DragUpdate(-10);
    DragEnd(-SCROLL_PAGING_SPEED_THRESHOLD - 1);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(state, ScrollState::FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(state, ScrollState::IDLE);
}

/**
 * @tc.name: GetPagingOffset001
 * @tc.desc: Test GetPagingOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, GetPagingOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and set enablePaging true.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEnablePaging(true);
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step2. simulate the scene of scrolling the last page
     * @tc.expected: pagingOffset is scrollableDistance_
     */
    float contentMainSize = 900.f;
    float pageLength = 400.f;
    pattern_->lastPageLength_ = fmod(contentMainSize, pageLength);;
    pattern_->scrollableDistance_ = -(contentMainSize - pageLength);
    pattern_->viewPortLength_ = pageLength;
    pattern_->currentOffset_ = -550.f;
    EXPECT_EQ(pattern_->GetPagingOffset(0.f, 0.f, 0.f), -(contentMainSize - pageLength));
}

/**
 * @tc.name: CAPIScrollPage001
 * @tc.desc: Test CAPI ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, CAPIScrollPage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollNode
     * @tc.expected: scrollNode create successfully
     */
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. scroll to next page without animation
     */
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.f);
    pattern_->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), -HEIGHT);

    /**
     * @tc.steps: step3. scroll to previous page with animation
     */
    pattern_->ScrollPage(true, true);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.f);
}

/**
 * @tc.name: OnScrollStartStop001
 * @tc.desc: Test OnScrollStart and OnScrollStart in fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollStartStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    ScrollModelNG model = CreateScroll();
    int32_t isScrollStartCalled = 0;
    OnScrollStartEvent scrollStart = [&isScrollStartCalled]() { isScrollStartCalled++; };
    model.SetOnScrollStart(std::move(scrollStart));
    int32_t isScrollStopCalled = 0;
    int32_t stopHasStart = 0;
    OnScrollStopEvent scrollStop = [&isScrollStopCalled, &isScrollStartCalled, &stopHasStart]() {
        if (isScrollStartCalled - isScrollStopCalled == 1) {
            stopHasStart++;
        }
        isScrollStopCalled++;
    };
    model.SetOnScrollStop(std::move(scrollStop));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Trigger fling and velocity = 200.
     * @tc.expected: isScrollStopCalled should be true.
     */

    pattern_->Fling(200.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);

    /**
     * @tc.steps: step2. Trigger fling and velocity = 20.
     * @tc.expected: isScrollStopCalled should be true.
     */
    isScrollStartCalled = 0;
    isScrollStopCalled = 0;
    stopHasStart = 0;
    pattern_->Fling(20.f);
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);
}

/**
 * @tc.name: OnScrollStartStop002
 * @tc.desc: Test OnScrollStart and OnScrollStart in fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollStartStop002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    ScrollModelNG model = CreateScroll();
    int32_t isScrollStartCalled = 0;
    OnScrollStartEvent scrollStart = [&isScrollStartCalled]() { isScrollStartCalled++; };
    model.SetOnScrollStart(std::move(scrollStart));
    int32_t isScrollStopCalled = 0;
    int32_t stopHasStart = 0;
    OnScrollStopEvent scrollStop = [&isScrollStopCalled, &isScrollStartCalled, &stopHasStart]() {
        if (isScrollStartCalled - isScrollStopCalled == 1) {
            stopHasStart++;
        }
        isScrollStopCalled++;
    };
    model.SetOnScrollStop(std::move(scrollStop));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Trigger fling and velocity = 200 in fling animation.
     * @tc.expected: Trigger fling animation and isScrollStopCalled should be true.
     */
    DragStart(frameNode_, Offset());
    DragEnd(-241.f);
    pattern_->Fling(241.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 2);
    EXPECT_EQ(isScrollStopCalled, 2);
    EXPECT_EQ(stopHasStart, 2);

    /**
     * @tc.steps: step2. Trigger fling and velocity = 20 in fling animation.
     * @tc.expected: Not trigger fling animation and isScrollStopCalled should be true.
     */
    isScrollStartCalled = 0;
    isScrollStopCalled = 0;
    stopHasStart = 0;
    DragStart(frameNode_, Offset());
    DragEnd(-200.f);
    pattern_->Fling(20.f);
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);
}

/**
 * @tc.name: OnScrollStartStop003
 * @tc.desc: Test OnScrollStart and OnScrollStart in fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnScrollStartStop003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    ScrollModelNG model = CreateScroll();
    int32_t isScrollStartCalled = 0;
    OnScrollStartEvent scrollStart = [&isScrollStartCalled]() { isScrollStartCalled++; };
    model.SetOnScrollStart(std::move(scrollStart));
    int32_t isScrollStopCalled = 0;
    int32_t stopHasStart = 0;
    OnScrollStopEvent scrollStop = [&isScrollStopCalled, &isScrollStartCalled, &stopHasStart]() {
        if (isScrollStartCalled - isScrollStopCalled == 1) {
            stopHasStart++;
        }
        isScrollStopCalled++;
    };
    model.SetOnScrollStop(std::move(scrollStop));
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. Trigger fling and velocity = 200 in spring animation.
     * @tc.expected: Trigger fling animation and isScrollStopCalled should be true.
     */
    DragStart(frameNode_, Offset());
    DragUpdate(-100.f);
    DragEnd(-200.f);
    pattern_->Fling(200.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);

    /**
     * @tc.steps: step2. Trigger fling and velocity = 20 in spring animation.
     * @tc.expected: Not trigger fling animation and isScrollStopCalled should be true.
     */
    isScrollStartCalled = 0;
    isScrollStopCalled = 0;
    stopHasStart = 0;
    DragStart(frameNode_, Offset());
    DragEnd(-200.f);
    pattern_->Fling(20.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(scrollBar_->GetForegroundColor(), Color::FromString(SCROLL_BAR_COLOR));

    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManager, nullptr);
    auto theme = themeManager->GetTheme<ScrollBarTheme>();
    ASSERT_NE(theme, nullptr);
    theme->foregroundColor_ = Color::FromString("#FFFFFFFF");
    pattern_->OnColorConfigurationUpdate();
    EXPECT_EQ(scrollBar_->GetForegroundColor(), Color::FromString("#FFFFFFFF"));
}

/**
 * @tc.name: SpringFinalPosition001
 * @tc.desc: Test SpringAnimation final position
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, SpringFinalPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step2. start spring animation.
     * @tc.expected: final position is -1 when spring animation end.
     */
    Offset startOffset = Offset();
    float dragDelta = 100.f;
    float velocityDelta = -200;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta / TICK));
    EXPECT_TRUE(TickPosition(0));
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    EXPECT_EQ(scrollable->springOffsetProperty_->Get(), -1);
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: HandleCrownActionEnd001
 * @tc.desc: Test HandleCrownActionEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleCrownActionEnd001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateContent();
    CreateScrollDone();

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);
    TimeStamp ts = std::chrono::high_resolution_clock::now();
    GestureEvent info;
    scrollable->isCrownDragging_ = true;
    scrollable->isCrownEventDragging_ = true;
    scrollable->HandleCrownActionEnd(ts, 1.0, info);
    EXPECT_FALSE(scrollable->isCrownDragging_);
    scrollable->isCrownEventDragging_ = true;
    scrollable->HandleCrownActionEnd(ts, 0.0, info);
    EXPECT_TRUE(scrollable->isCrownEventDragging_);
}

/**
 * @tc.name: HandleCrownActionUpdate001
 * @tc.desc: Test HandleCrownActionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleCrownActionUpdate001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateContent();
    CreateScrollDone();

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);
    GestureEvent info;
    info.mainDelta_ = 1.0;
    mainDelta = 2.0;
    TimeStamp ts = std::chrono::high_resolution_clock::now();
    scrollable->HandleCrownActionUpdate(ts, 0.0, info);
    EXPECT_NE(info.mainDelta_, mainDelta);
    scrollable->isCrownEventDragging_ = true;
    EXPECT_EQ(info.mainDelta_, mainDelta);
}
#endif

/**
 * @tc.name: HandleCrownActionEnd001
 * @tc.desc: Test HandleCrownActionEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEventTestNg, HandleCrownActionEnd001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateContent();
    CreateScrollDone();

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);
    scrollable->isTouching_ = false;
    scrollable->HandleTouchDown(false);
    EXPECT_TRUE(scrollable->isTouching_);
    scrollable->isTouching_ = false;
    scrollable->HandleTouchDown(true);
    EXPECT_FALSE(scrollable->isTouching_);
}
} // namespace OHOS::Ace::NG
