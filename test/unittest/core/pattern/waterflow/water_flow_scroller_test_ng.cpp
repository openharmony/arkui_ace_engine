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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "water_flow_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

namespace OHOS::Ace::NG {
class WaterFlowScrollerTestNg : public WaterFlowTestNg {};

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. When itemStart_ and scroll up
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(ITEM_MAIN_SIZE);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step3. Continue scroll down
     * @tc.expected: can scroll and IsAtEnd.
     */
    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    EXPECT_TRUE(IsAtEnd());

    /**
     * @tc.steps: step4. Continue scroll down
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));

    /**
     * @tc.steps: step5. When offsetEnd_ and scroll up
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(ITEM_MAIN_SIZE);
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT + ITEM_MAIN_SIZE));
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0 endIndex_ = 10.
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 10);
    EXPECT_TRUE(pattern_->layoutInfo_->itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: startIndex_ = 1 endIndex_ = 13.
     */
    UpdateCurrentOffset(-200 * ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 13);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step3. scroll down
     * @tc.expected: startIndex_ = 11 endIndex_ = 19.
     */
    UpdateCurrentOffset(-500000.f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 11);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step4. scroll up
     * @tc.expected: startIndex_ = 7 endIndex_ = 19.
     */
    UpdateCurrentOffset(200 * ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, PositionController001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. Test ScrollPage and IsAtEnd
     */
    auto controller = pattern_->positionController_;
    controller->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATER_FLOW_HEIGHT);
    EXPECT_TRUE(controller->IsAtEnd());
    controller->ScrollPage(true, false);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), 0);
    EXPECT_FALSE(controller->IsAtEnd());

    /**
     * @tc.steps: step2. Test JumpTo func.
     */
    controller->ScrollToIndex(2, false, ScrollAlign::START, std::nullopt);
    EXPECT_EQ(pattern_->layoutInfo_->jumpIndex_, 2);
    controller->ScrollToIndex(0, false, ScrollAlign::START, std::nullopt);
    EXPECT_EQ(pattern_->layoutInfo_->jumpIndex_, 0);
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, PositionController002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Test ScrollBy
     */
    ScrollBy(0, ITEM_MAIN_SIZE);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController ScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, PositionController003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. Test ScrollToEdge
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(Position(0));
    ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true);
    EXPECT_TRUE(Position(0));
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20 * 20;
} // namespace
/**
 * @tc.name: PositionController004
 * @tc.desc: Test PositionController ScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, PositionController004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushUITasks();
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: onScroll001
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScroll001, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScroll(onScroll);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. finger moves up
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(scrollOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(scrollState, ScrollState::SCROLL);

    /**
     * @tc.steps: step2. fling
     * @tc.expected: Trigger onScroll with FLING state
     */
    UpdateCurrentOffset(-1, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(scrollOffset.Value(), 1);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    /**
     * @tc.steps: step3. stop
     * @tc.expected: Trigger onScroll with IDLE state
     */
    pattern_->OnAnimateStop();
    FlushUITasks();
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScroll002
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScroll002, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScroll(onScroll);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(ITEM_MAIN_SIZE);
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScrollIndex001
 * @tc.desc: Test onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, onScrollIndex001, TestSize.Level1)
{
    int32_t firstIndex = -1;
    int32_t lastIndex = -1;
    auto onScrollIndex = [&firstIndex, &lastIndex](int32_t first, int32_t last) {
        firstIndex = first;
        lastIndex = last;
    };
    // 10 items total, 8 items showed
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScrollIndex(onScrollIndex);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step0. event on first layout
     * @tc.expected: Trigger onScrollIndex
     */
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step1. finger move up, offset less than one item height
     * @tc.expected: last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE / 2);
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step2. finger move up, offset more than one item height
     * @tc.expected: first and last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(firstIndex, 1);
    EXPECT_EQ(lastIndex, 6);
}

/**
 * @tc.name: OnScrollStart001
 * @tc.desc: Verify onScrollStart and onScrollStop event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScrollStart001, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScrollStart(scrollStart);
    model.SetOnScrollStop(scrollStop);
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. pan start
     * @tc.expected: trigger onScrollStart
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    /**
     * @tc.steps: step2. OnScrollEnd
     * @tc.expected: trigger onScrollStop
     */
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: WaterFlowPositionController_ScrollPage001
 * @tc.desc: Test ScrollPage.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, WaterFlowPositionController_ScrollPage001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ScrollPage is called.
     */
    pattern_->SetAxis(Axis::VERTICAL);
    controller->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATER_FLOW_HEIGHT);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_TRUE(controller->IsAtEnd());

    pattern_->SetAxis(Axis::NONE);
    controller->ScrollPage(false, false);
    FlushUITasks();
    EXPECT_TRUE(Position(-WATER_FLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), 0);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test WaterFlow ScrollToIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();
    pattern_->ScrollToIndex(20, true);
    // Item 20 doesn't exist
    EXPECT_EQ(pattern_->targetIndex_, std::nullopt);
}

/**
 * @tc.name: SpringAnimation001
 * @tc.desc: Test WaterFlow spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, SpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    auto model = CreateWaterFlow();
    CreateWaterFlowItems();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateDone();
    GestureEvent gesture;
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gesture.SetMainVelocity(10.0f);
    gesture.SetMainDelta(10.0f);
    gesture.SetGlobalLocation(Offset(1.0f, 1.0f));
    gesture.SetGlobalPoint(Point(1.0f, 1.0f));
    gesture.SetLocalLocation(Offset(1.0f, 1.0f));
    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    ASSERT_TRUE(scrollable);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);

    // scroll up
    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 9.3941307);

    MockAnimationManager::GetInstance().SetTicks(2);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 18.252581);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 9.1262903);

    // interrupt animation
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);
    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 17.99958);

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 26.394173);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 13.197086);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: Refresh001
 * @tc.desc: Test WaterFlow nested in refresh.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, Refresh001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG refreshModel;
    refreshModel.Create();
    auto refreshNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());

    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(3);
    CreateDone();

    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(100.f);
    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    ASSERT_TRUE(scrollable);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(refreshNode->GetGeometryNode()->GetFrameOffset().GetY(), 0.f);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameOffset().GetY(), 0.f);
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 100);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(refreshNode->GetGeometryNode()->GetFrameOffset().GetY(), 0.f);
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.ToString(), "153.53px"); // friction
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);

    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.ToString(), "191.83px");
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    ScrollToIndex(3, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0);

    ScrollToIndex(15, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -1100);

    ScrollToIndex(LAST_ITEM, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -1500);

    ScrollToIndex(0, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0);

    ScrollToIndex(15, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -500);

    ScrollToIndex(7, false, ScrollAlign::CENTER);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -200);

    ScrollToIndex(14, false, ScrollAlign::END);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -300);

    ScrollToIndex(2, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -100);
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    pattern_->ScrollToIndex(3, true, ScrollAlign::START);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::END);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, -400.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::AUTO);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 500.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::CENTER);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 800.f);

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 11);
    ScrollToIndex(3, true, ScrollAlign::AUTO);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 4)->IsActive());

    ScrollPage(false, false);
    EXPECT_LT(pattern_->layoutInfo_->Offset(), 0.f);

    ScrollToIndex(3, true, ScrollAlign::AUTO);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);

    ScrollToIndex(29, true, ScrollAlign::START);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 29)->IsActive());
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 2100.f);
    EXPECT_FALSE(pattern_->AnimateStoped());
    MockAnimationManager::GetInstance().Tick();
    // because animation finishes in 1 tick, AnimateStoped status becomes true again
    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 29);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 29)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 29), 600.0f);
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test WaterFlow scroll during focus change
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, Focus001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFocusableWaterFlowItems(30);
    CreateDone();

    auto next = pattern_->GetNextFocusNode(FocusStep::DOWN, GetChildFocusHub(frameNode_, 5)).Upgrade();
    auto cmp = GetChildFocusHub(frameNode_, 6);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));

    cmp = GetChildFocusHub(frameNode_, 4);
    next = pattern_->GetNextFocusNode(FocusStep::UP, GetChildFocusHub(frameNode_, 5)).Upgrade();
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    auto info = pattern_->layoutInfo_;

    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);

    next = pattern_->GetNextFocusNode(FocusStep::LEFT, GetChildFocusHub(frameNode_, 0)).Upgrade();
    EXPECT_FALSE(next);

    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);
    next = pattern_->GetNextFocusNode(FocusStep::RIGHT, GetChildFocusHub(frameNode_, 10)).Upgrade();
    EXPECT_EQ(GetChildRect(frameNode_, 11).Bottom(), WATER_FLOW_HEIGHT);
    cmp = GetChildFocusHub(frameNode_, 11);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    next = pattern_->GetNextFocusNode(FocusStep::LEFT, GetChildFocusHub(frameNode_, 29)).Upgrade();
    cmp = GetChildFocusHub(frameNode_, 28);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    next = pattern_->GetNextFocusNode(FocusStep::DOWN_END, GetChildFocusHub(frameNode_, 29)).Upgrade();
    EXPECT_FALSE(next);

    EXPECT_EQ(info->startIndex_, 19);
    next = pattern_->GetNextFocusNode(FocusStep::UP_END, GetChildFocusHub(frameNode_, info->startIndex_)).Upgrade();
    cmp = GetChildFocusHub(frameNode_, 18);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    EXPECT_EQ(GetChildY(frameNode_, 18), 0.0f);
}

/**
 * @tc.name: Focus002
 * @tc.desc: Test GetScrollIndexAbility
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, Focus002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFocusableWaterFlowItems(30);
    CreateDone();
    auto eventHub = frameNode_->GetOrCreateEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    focusHub->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step1. ScrollToEdge SCROLL_BOTTOM false
     * @tc.expected: scroll to bottom
     */
    focusHub->FocusToHeadOrTailChild(false);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetBeginIndex(), 19);
    EXPECT_EQ(pattern_->GetEndIndex(), 29);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, false);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);

    /**
     * @tc.steps: step1. ScrollToEdge SCROLL_TOP false
     * @tc.expected: scroll to top
     */
    focusHub->FocusToHeadOrTailChild(true);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetBeginIndex(), 0);
    EXPECT_EQ(pattern_->GetEndIndex(), 10);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, true);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);

    /**
     * @tc.steps: step1. ScrollToIndex 29 false ScrollAlign::AUTO
     * @tc.expected: scroll to bottom
     */
    auto scrollIndexAbility = pattern_->GetScrollIndexAbility();
    EXPECT_TRUE(scrollIndexAbility(29));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetBeginIndex(), 19);
    EXPECT_EQ(pattern_->GetEndIndex(), 29);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, false);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);

    /**
     * @tc.steps: step1. ScrollToIndex 0 false ScrollAlign::AUTO
     * @tc.expected: scroll to top
     */
    EXPECT_TRUE(scrollIndexAbility(0));
    FlushUITasks();
    EXPECT_EQ(pattern_->GetBeginIndex(), 0);
    EXPECT_EQ(pattern_->GetEndIndex(), 10);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, true);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
}

/**
 * @tc.name: ReachStart001
 * @tc.desc: Test ReachStart
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ReachStart001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::NONE, false);
    bool reached = false;
    model.SetOnReachStart([&reached]() { reached = true; });
    CreateWaterFlowItems(30);
    CreateDone();

    ScrollToIndex(29, false, ScrollAlign::START);

    reached = false;
    UpdateCurrentOffset(Infinity<float>());
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_TRUE(reached);
    FlushUITasks();

    reached = false;
    UpdateCurrentOffset(-5.0f);
    EXPECT_FALSE(reached);
    EXPECT_EQ(GetChildY(frameNode_, 0), -5.0f);
    reached = false;
    UpdateCurrentOffset(6.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_TRUE(reached);
}

/**
 * @tc.name: ScrollPage002
 * @tc.desc: Test ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollPage002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::NONE, false);
    CreateWaterFlowItems(30);
    CreateDone();

    MockAnimationManager::GetInstance().SetTicks(1);
    pattern_->ScrollPage(false, true);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    const auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->Offset(), -800.0f);

    ScrollToIndex(29, false, ScrollAlign::START);
    EXPECT_EQ(info->startIndex_, 25);
    EXPECT_EQ(GetChildY(frameNode_, 25), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 29), 600.0f);

    pattern_->ScrollPage(true, true, AccessibilityScrollType::SCROLL_HALF);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 25), 400.0f);

    ScrollableController controller;
    controller.SetScrollPattern(pattern_);
    controller.ScrollPage(true, true);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(info->startIndex_, 17);
    EXPECT_EQ(info->endIndex_, 21);
}

/**
 * @tc.name: ReachStart002
 * @tc.desc: Test WaterFlow reach start in spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ReachStart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    MockAnimationManager::GetInstance().SetTicks(1);
    auto model = CreateWaterFlow();
    CreateWaterFlowItems(50);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    int32_t reached = 0;
    model.SetOnReachStart([&reached]() { ++reached; });
    CreateDone();
    EXPECT_EQ(reached, 1);
    UpdateCurrentOffset(-100.0f);

    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    ASSERT_TRUE(scrollable);
    GestureEvent info;
    info.SetMainVelocity(1000.f);
    info.SetMainDelta(10.f);
    scrollable->isDragging_ = true;
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    scrollable->HandleDragEnd(info);
    scrollable->isDragging_ = false;
    FlushUITasks();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::FRICTION);
    // friction animation
    MockAnimationManager::GetInstance().TickByVelocity(200.0f);
    FlushUITasks();
    EXPECT_EQ(reached, 2);

    // transitioned to spring animation
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::SPRING);
    MockAnimationManager::GetInstance().TickByVelocity(50.0f);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(reached, 3);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
}

/**
 * @tc.name: ReachEnd001
 * @tc.desc: Test WaterFlow reach emd in spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ReachEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    MockAnimationManager::GetInstance().SetTicks(1);
    auto model = CreateWaterFlow();
    CreateWaterFlowItems(20);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    int32_t reached = 0;
    model.SetOnReachEnd([&reached]() { ++reached; });
    CreateDone();

    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    ASSERT_TRUE(scrollable);
    GestureEvent info;
    info.SetMainVelocity(-1000.f);
    info.SetMainDelta(-10.f);
    scrollable->isDragging_ = true;
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    scrollable->HandleDragEnd(info);
    scrollable->isDragging_ = false;
    FlushUITasks();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::FRICTION);
    // friction animation
    MockAnimationManager::GetInstance().TickByVelocity(-2500.0f);
    FlushUITasks();
    EXPECT_EQ(reached, 1);

    // transitioned to spring animation
    MockAnimationManager::GetInstance().TickByVelocity(-50.0f);
    FlushUITasks();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::SPRING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(reached, 2);
    EXPECT_NEAR(GetChildRect(frameNode_, 19).Bottom(), WATER_FLOW_HEIGHT, 0.01f);
}

/**
 * @tc.name: ReachEnd002
 * @tc.desc: Test the OnReachEnd event when the repeatDifference is different.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ReachEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the OnReachEnd event.
     */
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    auto model = CreateWaterFlow();
    model.SetOnReachEnd(event);
    CreateWaterFlowItems(20);
    model.SetColumnsTemplate("1fr 1fr");
    CreateDone();
    EXPECT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->repeatDifference_, 0);

    /**
     * @tc.steps: step2. Scroll down to end
     * @tc.expected: the OnReachEnd event can be triggered.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;

    /**
     * @tc.steps: step3. Modify the repeatDifference_ of WaterFlow.
     * @tc.expected: the OnReachEnd event can not be triggered.
     */
    pattern_->layoutInfo_->repeatDifference_ = 1;
    pattern_->FireOnReachEnd(event, nullptr);
    EXPECT_FALSE(pattern_->layoutInfo_->repeatDifference_ == 0);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: ScrollAnimation001
 * @tc.desc: Test ScrollToIndex with animation.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollAnimation001, TestSize.Level1)
{
    MockAnimationManager::GetInstance().SetTicks(1);
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(2, true);
    CreateItemsInRepeat(50, [](int32_t i) { return 100.0f; });
    CreateDone();

    ScrollToIndex(48, true, ScrollAlign::START);
    MockAnimationManager::GetInstance().Tick();
    pattern_->isAnimationStop_ = false; // animation ended in 1 tick, need to set manually
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 49);
    for (int i = pattern_->layoutInfo_->startIndex_; i <= 49; i++) {
        ASSERT_TRUE(GetChildFrameNode(frameNode_, i));
    }

    ScrollToIndex(0, true, ScrollAlign::START);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 15);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    for (int i = pattern_->layoutInfo_->startIndex_; i <= 15; i++) {
        ASSERT_TRUE(GetChildFrameNode(frameNode_, i));
    }
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
}

/**
 * @tc.name: SetEffectEdge001
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, SetEffectEdge001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    CreateWaterFlowItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::START);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();

    scrollable->HandleTouchDown();
    UpdateCurrentOffset(-100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);
    UpdateCurrentOffset(200);
    ASSERT_TRUE(Positive(GetChildY(frameNode_, 0)));
}

/**
 * @tc.name: SetEffectEdge002
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, SetEffectEdge002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateWaterFlowItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::END);

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    UpdateCurrentOffset(100);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    UpdateCurrentOffset(-200);
    ASSERT_TRUE(Negative(GetChildY(frameNode_, 0)));
}

/**
 * @tc.name: SetEffectEdge003
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, SetEffectEdge003, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateWaterFlowItems(20);
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::START);

    GestureEvent gesture;
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gesture.SetMainVelocity(-1000.0f);
    gesture.SetMainDelta(-100.0f);

    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);

    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -53.526146);

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -153.52615);

    const auto& info = pattern_->layoutInfo_;
    MockAnimationManager::GetInstance().TickByVelocity(-8000.0f);
    FlushUITasks();
    EXPECT_EQ(info->endIndex_, 19);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 19), 600);
}

/**
 * @tc.name: SetEffectEdge004
 * @tc.desc: Test SetEffectEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, SetEffectEdge004, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateWaterFlowItems(20);
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::END);
    CreateDone();
    EXPECT_EQ(pattern_->GetEffectEdge(), EffectEdge::END);
    UpdateCurrentOffset(-200);

    GestureEvent gesture;
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gesture.SetMainVelocity(1000.0f);
    gesture.SetMainDelta(20.0f);

    auto scrollable = pattern_->GetScrollableEvent()->scrollable_;
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);
    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -37.300961);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -17.300961);

    MockAnimationManager::GetInstance().TickByVelocity(1000.0f);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);
}
} // namespace OHOS::Ace::NG
