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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DRAG_DELTA = 400.0f;
} // namespace

class SwiperEventTestNg : public SwiperTestNg {
public:
    void HandleDragStart(GestureEvent info);
    void HandleDragUpdate(GestureEvent info);
    void HandleDragEnd(GestureEvent info);
    void HandleDragCancel();
    void MockPaintRect(const RefPtr<FrameNode>& frameNode);
    GestureEvent CreateDragInfo(bool moveDirection);
};

void SwiperEventTestNg::HandleDragStart(GestureEvent info)
{
    pattern_->panEvent_->GetActionStartEventFunc()(info);
}

void SwiperEventTestNg::HandleDragUpdate(GestureEvent info)
{
    pattern_->panEvent_->GetActionUpdateEventFunc()(info);
}

void SwiperEventTestNg::HandleDragEnd(GestureEvent info)
{
    pattern_->panEvent_->GetActionEndEventFunc()(info);
}

void SwiperEventTestNg::HandleDragCancel()
{
    pattern_->panEvent_->GetActionCancelEventFunc()();
}

void SwiperEventTestNg::MockPaintRect(const RefPtr<FrameNode>& frameNode)
{
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode->renderContext_);
    mockRenderContext->paintRect_ = RectF(0.f, 0.f, SWIPER_WIDTH, SWIPER_HEIGHT);
}

GestureEvent SwiperEventTestNg::CreateDragInfo(bool moveDirection)
{
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::TOUCHPAD);
    info.SetGlobalLocation(Offset(100.f, 100.f));
    if (moveDirection) {
        // drag to right item
        info.SetMainDelta(-DRAG_DELTA);
        info.SetMainVelocity(-2000.f);
    } else {
        // drag to left item
        info.SetMainDelta(DRAG_DELTA);
        info.SetMainVelocity(2000.f);
    }
    return info;
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: HandleDrag with AXIS and MOUSE, will trigger ShowPrevious or ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);

    /**
     * @tc.steps: step1. SetMainDelta > 0
     * @tc.expected: Trigger ShowPrevious
     */
    info.SetMainDelta(10.f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. SetMainDelta < 0
     * @tc.expected: Trigger ShowNext
     */
    info.SetMainDelta(-10.f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step3. SetMainDelta == 0
     * @tc.expected: CurrentIndex not changed
     */
    info.SetMainDelta(0.f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: HandleDrag to cancel, will not change targetIndex_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {});
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragCancel
     * @tc.expected: targetIndex_ not changed
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragCancel();
    EXPECT_EQ(pattern_->targetIndex_, 0);
}

/**
 * @tc.name: HandleDrag003
 * @tc.desc: HandleDrag left out of boundary, targetIndex_ changed because loop:true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {});
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: currentDelta_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->currentDelta_, -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: currentDelta_ not more than SWIPER_WIDTH
     */
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->currentDelta_, -SWIPER_WIDTH);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change targetIndex_ by MainVelocity direction
     */
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->targetIndex_, -1);
}

/**
 * @tc.name: HandleDrag004
 * @tc.desc: HandleDrag right out of boundary, targetIndex_ changed because loop:true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndex(3);
    });
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: currentDelta_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->currentDelta_, DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: currentDelta_ not more than SWIPER_WIDTH
     */
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->currentDelta_, SWIPER_WIDTH);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change targetIndex_ by MainVelocity direction
     */
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->targetIndex_, 4);
}

/**
 * @tc.name: HandleDrag005
 * @tc.desc: HandleDrag left out of boundary, but loop false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false, set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
    });
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: currentDelta_ < dragDelta because spring friction
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_LT(pattern_->currentDelta_, 0.f);
    EXPECT_GT(pattern_->currentDelta_, -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: currentDelta_ < dragDelta because spring friction
     */
    float preDelta = pattern_->currentDelta_;
    HandleDragUpdate(info);
    EXPECT_LT(pattern_->currentDelta_, preDelta);
    EXPECT_GT(pattern_->currentDelta_, -DRAG_DELTA * 2);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change still 0
     */
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->targetIndex_, 0);
}

/**
 * @tc.name: HandleDrag006
 * @tc.desc: HandleDrag right out of boundary, but loop false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false, set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetIndex(3);
    });
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: currentDelta_ < dragDelta because spring friction
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_GT(pattern_->currentDelta_, 0.f);
    EXPECT_LT(pattern_->currentDelta_, DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: currentDelta_ < dragDelta because spring friction
     */
    float preDelta = pattern_->currentDelta_;
    HandleDragUpdate(info);
    EXPECT_GT(pattern_->currentDelta_, preDelta);
    EXPECT_LT(pattern_->currentDelta_, DRAG_DELTA * 2);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change still 3
     */
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->targetIndex_, 3);
}

/**
 * @tc.name: HandleDrag007
 * @tc.desc: HandleDrag left out of boundary, but loop false and EdgeEffect::FADE
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false and EdgeEffect::FADE, set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::FADE);
    });
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: fadeOffset_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->fadeOffset_, DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragEnd
     */
    HandleDragEnd(info);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: HandleDrag008
 * @tc.desc: HandleDrag right out of boundary, but loop false and EdgeEffect::FADE
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false and EdgeEffect::FADE, set HotRegion and drag in it
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::FADE);
        model.SetIndex(3);
    });
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: fadeOffset_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->fadeOffset_, -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragEnd
     */
    HandleDragEnd(info);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: SwiperPatternTriggerEventOnFinish001
 * @tc.desc: TriggerEventOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternTriggerEventOnFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t nextIndex = 1;
    pattern_->preTargetIndex_ = 1;
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call TriggerEventOnFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerEventOnFinish(nextIndex);
            if (i == 1) {
                break;
            }
            nextIndex = 2;
            pattern_->isFinishAnimation_ = true;
        }
        pattern_->isFinishAnimation_ = false;
    }
}

/**
 * @tc.name: SwiperPatternHandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = MouseInfo();
    layoutProperty_->UpdateShowIndicator(true);

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleMouseEvent(info);
        layoutProperty_->UpdateShowIndicator(false);
    }
}

/**
 * @tc.name: PanEvent001
 * @tc.desc: PanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, PanEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    auto actionEnd = pattern_->panEvent_->GetActionEndEventFunc();
    auto actionCancel = pattern_->panEvent_->GetActionCancelEventFunc();

    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(10.f);
    actionStart(info);
    actionUpdate(info);
    actionEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    info.SetMainDelta(-10.f);
    actionStart(info);
    actionUpdate(info);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    actionEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperPatternInitHoverMouseEvent001
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternInitHoverMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    eventHub_->AttachHost(frameNode_);
    pattern_->hoverEvent_ = nullptr;
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
    pattern_->mouseEvent_->onMouseCallback_(info);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
}

/**
 * @tc.name: SwiperPatternHandleTouchDown001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchDown001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = true;

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    pattern_->HandleTouchDown(touchLocationInfo);
}

/**
 * @tc.name: SwiperPatternHandleScroll001
 * @tc.desc: test HandleScroll SELF_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
    EXPECT_FALSE(res.reachEdge);

    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisableSwipe(true);
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 5.0f);
    EXPECT_TRUE(res.reachEdge);
}

/**
 * @tc.name: SwiperPatternHandleScroll002
 * @tc.desc: test HandleScroll SELF_FIRST but scrolling within boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll).Times(0);
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll003
 * @tc.desc: test HandleScroll SELF_FIRST while scrolling out of boundary and EdgeEffect doesn't consume extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(res.remain, 5.0f);
    EXPECT_TRUE(res.reachEdge);
}

/**
 * @tc.name: SwiperPatternHandleScroll004
 * @tc.desc: test HandleScroll SELF_FIRST and scrolling out of boundary and EdgeEffect consumes extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll005
 * @tc.desc: test HandleScroll called by CHILD_SCROLL when edge is reached. Should pass offset back to child.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto swiperNode = FrameNode::CreateFrameNode("Swiper", 0, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    swiperPattern->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    swiperPattern->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });
    auto res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 4.5f);
    // three level nesting
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    swiperPattern->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    swiperPattern->SetNestedScroll(nestedOpt);
    res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 4.5f);
}

/**
 * @tc.name: SwiperPatternHandleScroll006
 * @tc.desc: test HandleScroll from child animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    // during animation
    pattern_->targetIndex_ = 1;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll007
 * @tc.desc: test HandleScroll from child mouse scroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll007, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);

    // showPrevious
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);

    // showNext
    res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll008
 * @tc.desc: test HandleScroll triggering event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll008, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    int32_t callCount = 0;
    eventHub_->SetGestureSwipeEvent([&](int32_t index, const AnimationCallbackInfo& info) {
        ++callCount;
    });
    pattern_->OnScrollStartRecursive(0.0f);
    pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-2.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(callCount, 3);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity001
 * @tc.desc: test HandleScrollVelocity self handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);

    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisableSwipe(true);
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity002
 * @tc.desc: test HandleScrollVelocity pass to parent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);

    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity003
 * @tc.desc: test HandleScrollVelocity pass to parent and parent doesn't consume
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);

    // change EdgeEffect to Spring and redo
    // should consume velocity
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    mockScroll.Reset();
    mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));

    pattern_->parent_ = mockScroll;
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator no touch bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 1;
    pattern_->currentIndex_ = 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: HandleTouchBottomLoop002
 * @tc.desc: test Swiper indicator touch left bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: HandleTouchBottomLoop003
 * @tc.desc: test Swiper indicator touch right bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperInit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
}

/**
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperInit002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_, FocusType::DISABLE, false);
    pattern_->InitOnKeyEvent(focusHub);
    KeyEvent event = KeyEvent();
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(event));
}

/**
 * @tc.name: SwiperFunc001
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperFunc001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    KeyEvent event = KeyEvent();
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
}

/**
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperFunc002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool isVisible = false;
    pattern_->OnVisibleChange(isVisible);
    pattern_->isInit_ = false;
    pattern_->OnWindowHide();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern_->isVisible_);
    isVisible = true;
    pattern_->OnWindowShow();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_TRUE(pattern_->isVisible_);
    pattern_->isVisibleArea_ = true;
    pattern_->OnWindowShow();
}

/**
 * @tc.name: SwiperFunc003
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperFunc003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
}

/**
 * @tc.name: SwiperPatternOnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnIndexChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    ASSERT_EQ(pattern_->TotalCount(), 6);
    pattern_->oldIndex_ = 1;
    layoutProperty_->UpdateIndex(2);

    /**
     * @tc.steps: step3. call OnIndexChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnIndexChange();
}

/**
 * @tc.name: SwiperPatternOnVisibleChange001
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnVisibleChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isInit_ = false;
    pattern_->isWindowShow_ = false;

    /**
     * @tc.steps: step2. call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnVisibleChange(true);
}

/**
 * @tc.name: SwiperPatternOnScrollStart001
 * @tc.desc: test OnScrollStartRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnScrollStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);

    EXPECT_CALL(*mockScroll, OnScrollStartRecursive).Times(1);
    EXPECT_CALL(*mockScroll, GetAxis).Times(1).WillOnce(Return(Axis::HORIZONTAL));
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->isDragging_ = false;
    pattern_->currentIndex_ = 3;
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    pattern_->OnScrollStartRecursive(5.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 3);
}

/**
 * @tc.name: SwiperPatternOnScrollEnd001
 * @tc.desc: test OnScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnScrollEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, OnScrollEndRecursive).Times(1);
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);

    pattern_->NotifyParentScrollEnd();
}
} // namespace OHOS::Ace::NG
