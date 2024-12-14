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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components/swiper/swiper_component.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DRAG_DELTA = 400.0f;
} // namespace

class SwiperEventTestNg : public SwiperTestNg {
public:
    void HandleDrag(GestureEvent info);
    void HandleDragStart(GestureEvent info);
    void HandleDragUpdate(GestureEvent info);
    void HandleDragEnd(GestureEvent info);
    void HandleDragCancel();
    void MockPaintRect(const RefPtr<FrameNode>& frameNode);
    GestureEvent CreateDragInfo(bool moveDirection);
};

void SwiperEventTestNg::HandleDrag(GestureEvent info)
{
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
    FlushUITasks();
}

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
    info.SetMainDelta(moveDirection ? -DRAG_DELTA : DRAG_DELTA);
    info.SetMainVelocity(moveDirection ? -2000.f : 2000.f);
    return info;
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: HandleDrag with AXIS and MOUSE, will trigger ShowPrevious or ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateDefaultSwiper();
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);

    /**
     * @tc.steps: step1. Drag to right
     * @tc.expected: Trigger ShowPrevious
     */
    info.SetMainDelta(10.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), -1);

    /**
     * @tc.steps: step2. Drag to left
     * @tc.expected: Trigger ShowNext
     */
    info.SetMainDelta(-10.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step3. Drag not move
     * @tc.expected: CurrentIndex not changed
     */
    info.SetMainDelta(0.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: HandleDrag to cancel or drag outOfHotRegion, will not change CurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    CreateDefaultSwiper();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragCancel
     * @tc.expected: targetIndex_ not changed
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragCancel();
    EXPECT_FALSE(pattern_->targetIndex_);
}

/**
 * @tc.name: HandleDrag003
 * @tc.desc: HandleDrag left out of boundary, CurrentIndex changed because loop:true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    CreateDefaultSwiper();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX not more than SWIPER_WIDTH
     */
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), SWIPER_WIDTH);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change CurrentIndex by MainVelocity direction
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), -1);
}

/**
 * @tc.name: HandleDrag004
 * @tc.desc: HandleDrag right out of boundary, CurrentIndex changed because loop:true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set HotRegion and drag in it
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: Item(index:3) OffsetX is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 3), -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: Item(index:3) OffsetX not more than SWIPER_WIDTH
     */
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 3), -SWIPER_WIDTH);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change CurrentIndex by MainVelocity direction
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 4);
}

/**
 * @tc.name: HandleDrag005
 * @tc.desc: HandleDrag out of left boundary, but loop false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false, set HotRegion and drag in it
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX < dragDelta because spring friction
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_LT(GetChildX(frameNode_, 0), DRAG_DELTA);
    EXPECT_GT(GetChildX(frameNode_, 0), 0.f);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX < dragDelta because spring friction
     */
    float preDelta = GetChildX(frameNode_, 0);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_LT(GetChildX(frameNode_, 0), DRAG_DELTA * 2);
    EXPECT_GT(GetChildX(frameNode_, 0), preDelta);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change still 0
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleDrag006
 * @tc.desc: HandleDrag out of right boundary, but loop false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop false, set HotRegion and drag in it
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX < dragDelta because spring friction
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_LT(GetChildX(frameNode_, 3), 0.f);
    EXPECT_GT(GetChildX(frameNode_, 3), -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) > SWIPER_WIDTH
     * @tc.expected: Item(index:0) OffsetX < dragDelta because spring friction
     */
    float preDelta = GetChildX(frameNode_, 3);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_LT(GetChildX(frameNode_, 3), preDelta);
    EXPECT_GT(GetChildX(frameNode_, 3), -DRAG_DELTA * 2);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Change still 3
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 3);
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::FADE);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: fadeOffset_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->fadeOffset_, DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragEnd
     */
    HandleDragEnd(info);
    FlushUITasks();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::FADE);
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH
     * @tc.expected: fadeOffset_ is equal to dragDelta
     */
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->fadeOffset_, -DRAG_DELTA);

    /**
     * @tc.steps: step3. HandleDragEnd
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: HandleDrag009
 * @tc.desc: HandleDrag with DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag009, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Drag to right
     * @tc.expected: Swipe to last page
     */
    GestureEvent info = CreateDragInfo(false);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), -2);

    /**
     * @tc.steps: step2. Drag to left
     * @tc.expected: Swipe to first page
     */
    info = CreateDragInfo(true);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleDrag010
 * @tc.desc: HandleDrag to left with different drag distances and velocities
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag010, TestSize.Level1)
{
    // HandleDragUpdate abs(delta) > SWIPER_WIDTH / 2 and velocity > threshold included in the HandleDrag003 case
    /**
     * @tc.steps: step1. HandleDragUpdate abs(delta) > SWIPER_WIDTH / 2 and velocity < threshold
     * @tc.expected: Item index is equal to -1
     */
    CreateDefaultSwiper();
    MockPaintRect(frameNode_);
    GestureEvent info = CreateDragInfo(false);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    info.SetMainVelocity(0);
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), -1);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH / 2 and velocity > threshold
     * @tc.expected: Item index is equal to -1
     */
    CreateDefaultSwiper();
    MockPaintRect(frameNode_);
    info = CreateDragInfo(false);
    info.SetMainDelta(DRAG_DELTA / 2);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), -1);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) < SWIPER_WIDTH / 2 and velocity < threshold
     * @tc.expected: Item index is equal to 0
     */
    CreateDefaultSwiper();
    MockPaintRect(frameNode_);
    info = CreateDragInfo(false);
    info.SetMainDelta(DRAG_DELTA / 2);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    info.SetMainVelocity(0);
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: HandleDrag011
 * @tc.desc: HandleDrag to right with different drag distances and velocities
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag011, TestSize.Level1)
{
    // HandleDragUpdate abs(delta) > SWIPER_WIDTH / 2 and velocity > threshold included in the HandleDrag004 case
    /**
     * @tc.steps: step1. HandleDragUpdate abs(delta) > SWIPER_WIDTH / 2 and velocity < threshold
     * @tc.expected: Item index is equal to 4
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    info.SetMainVelocity(0);
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 4);

    /**
     * @tc.steps: step2. HandleDragUpdate abs(delta) < SWIPER_WIDTH / 2 and velocity > threshold
     * @tc.expected: Item index is equal to 4
     */
    model = CreateSwiper();
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);
    info = CreateDragInfo(true);
    info.SetMainDelta(-DRAG_DELTA / 2);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 4);

    /**
     * @tc.steps: step3. HandleDragUpdate abs(delta) < SWIPER_WIDTH / 2 and velocity < threshold
     * @tc.expected: Item index is equal to 3
     */
    model = CreateSwiper();
    model.SetIndex(3);
    CreateSwiperItems();
    CreateSwiperDone();
    MockPaintRect(frameNode_);
    info = CreateDragInfo(true);
    info.SetMainDelta(-DRAG_DELTA / 2);
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    info.SetMainVelocity(0);
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 3);
}

/**
 * @tc.name: SwiperPatternHandleScroll001
 * @tc.desc: test HandleScroll SELF_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
     * @tc.steps: step1. Create swiperNode.
     */
    CreateSwiper();
    CreateSwiperDone();
    layoutProperty_->UpdateLoop(false);
    paintProperty_->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 4.5f);
    // three level nesting
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 4.5f);
}

/**
 * @tc.name: SwiperPatternHandleScroll006
 * @tc.desc: test HandleScroll from child animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll006, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    // during animation
    pattern_->targetIndex_ = 1;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);
    pattern_->targetIndex_.reset();

    pattern_->fadeAnimation_ = AnimationUtils::StartAnimation({}, [&]() {});
    pattern_->fadeAnimationIsRunning_ = true;
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    // fade animation doesn't affect scrolling
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll007
 * @tc.desc: test HandleScroll from child mouse scroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll007, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);

    // showPrevious
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5);

    // showNext
    res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, -5);
}

/**
 * @tc.name: SwiperPatternHandleScroll008
 * @tc.desc: test HandleScroll triggering event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll008, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    int32_t callCount = 0;
    eventHub_->SetGestureSwipeEvent([&](int32_t index, const AnimationCallbackInfo& info) { ++callCount; });
    pattern_->OnScrollStartRecursive(pattern_, 0.0f, 0.0f);
    pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-2.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(callCount, 3);
}

/**
 * @tc.name: SwiperPatternHandleScroll009
 * @tc.desc: test HandleScroll called by CHILD_SCROLL when edge is reached. Should pass offset back to child.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiperNode.
     */
    CreateSwiper();
    CreateSwiperDone();
    layoutProperty_->UpdateLoop(false);
    /**
     * @tc.steps: step2. alignment Right to left (RTL),state != NestedState::GESTURE.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(pattern_->IsHorizontalAndRightToLeft(), true);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 4.5f);
}

/**
 * @tc.name: SwiperPatternHandleScrollMultiChildren001
 * @tc.desc: test HandleScroll with multiple scrollable children
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollMultiChildren001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->OnScrollStartRecursive(pattern_, 0.0f, 0.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);

    // second child calling
    pattern_->OnScrollStartRecursive(pattern_, 0.0f, 0.0f);

    // first child ending
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);

    // second child scrolling
    pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    pattern_->OnScrollEndRecursive(std::nullopt);

    // self scroll
    pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_FALSE(pattern_->childScrolling_);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity001
 * @tc.desc: test HandleScrollVelocity self handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    pattern_->childScrolling_ = true;
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
    EXPECT_FALSE(pattern_->childScrolling_);

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
    SwiperModelNG model = CreateSwiper();
    model.SetEdgeEffect(EdgeEffect::NONE);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->childScrolling_ = true;

    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
    EXPECT_FALSE(pattern_->childScrolling_);
    // shouldn't be passed parent
    pattern_->nestedScroll_ = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->HandleDragEnd(5.0f);

    pattern_->nestedScroll_ = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    EXPECT_TRUE(pattern_->nestedScroll_.NeedParent(true));
    EXPECT_FALSE(pattern_->nestedScroll_.NeedParent(false));
    mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(0);
    pattern_->parent_ = mockScroll;
    pattern_->HandleDragEnd(5.0f);

    pattern_->UpdateCurrentOffset(-5.0f);
    pattern_->MarkDirtyNodeSelf();
    FlushUITasks();
    pattern_->HandleDragEnd(-5.0f);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity003
 * @tc.desc: test HandleScrollVelocity pass to parent and parent doesn't consume
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity003, TestSize.Level1)
{
    CreateDefaultSwiper();
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
    pattern_->childScrolling_ = true;
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);
    EXPECT_FALSE(pattern_->childScrolling_);

    // change EdgeEffect to Spring and redo
    // should consume velocity
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    mockScroll.Reset();
    mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));

    pattern_->parent_ = mockScroll;
    pattern_->childScrolling_ = true;
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(pattern_->childScrolling_);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity004
 * @tc.desc: test HandleScrollVelocity self handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetEdgeEffect(EdgeEffect::NONE);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    /**
     * @tc.steps: step1. alignment Right to left (RTL).
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(pattern_->IsHorizontalAndRightToLeft(), true);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisableSwipe(true);
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator no touch bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
    CreateDefaultSwiper();
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
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperFunc002, TestSize.Level1)
{
    CreateDefaultSwiper();
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
 * @tc.name: SwiperPatternOnVisibleChange003
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnVisibleChange003, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->isWindowShow_ = false;

    /**
     * @tc.cases: call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->isInit_ = true;
    pattern_->OnVisibleChange(true);
    EXPECT_TRUE(pattern_->isInit_);
}

/**
 * @tc.name: OnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, OnIndexChange001, TestSize.Level1)
{
    bool isTrigger = false;
    auto onChangeEvent = [&isTrigger](const BaseEventInfo* info) { isTrigger = true; };
    SwiperModelNG model = CreateSwiper();
    model.SetOnChangeEvent(std::move(onChangeEvent));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Call ShowNext
     * @tc.expected: Trigger onChangeEvent
     */
    ShowNext();
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Trigger onChangeEvent
     */
    isTrigger = false;
    ShowPrevious();
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step3. Call ChangeIndex
     * @tc.expected: Trigger onChangeEvent
     */
    isTrigger = false;
    ChangeIndex(3);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: OnScrollStartEnd001
 * @tc.desc: test OnScrollStartRecursive/OnScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, OnScrollStartEnd001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
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

    /**
     * @tc.steps: step1. Scroll start
     */
    pattern_->OnScrollStartRecursive(pattern_, 5.0f, 0.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 3);

    /**
     * @tc.steps: step2. Scroll end
     */
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);

    /**
     * @tc.steps: step3. Scroll end when AnimationRunning
     * @tc.expected: Can not HandleDragEnd
     */
    pattern_->targetIndex_ = 1;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);
}

/**
 * @tc.name: OnScrollStartEnd002
 * @tc.desc: test OnScrollStartRecursive/OnScrollEndRecursive when DisableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, OnScrollStartEnd002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisableSwipe(true);
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->isDragging_ = false;
    pattern_->currentIndex_ = 3;
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    /**
     * @tc.steps: step1. Scroll start
     * @tc.expected: Can not start because of DisableSwipe
     */
    pattern_->OnScrollStartRecursive(pattern_, 5.0f, 0.0f);
    EXPECT_FALSE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    /**
     * @tc.steps: step2. Scroll end
     */
    EXPECT_CALL(*mockScroll, OnScrollEndRecursive).Times(0);
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(0);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);
}

/**
 * @tc.name: OnChange001
 * @tc.desc: Test OnChange event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, OnChange001, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnChange(std::move(onChange));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNext();
    EXPECT_EQ(currentIndex, 1);

    /**
     * @tc.steps: step2. Show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPrevious();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: OnAnimation001
 * @tc.desc: Test OnAnimationStart OnAnimationEnd event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, OnAnimation001, TestSize.Level1)
{
    bool isAnimationStart = false;
    auto onAnimationStart = [&isAnimationStart](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isAnimationStart = true;
    };
    bool isAnimationEnd = false;
    auto onAnimationEnd = [&isAnimationEnd](
                              int32_t index, const AnimationCallbackInfo& info) { isAnimationEnd = true; };
    SwiperModelNG model = CreateSwiper();
    model.SetOnAnimationStart(std::move(onAnimationStart));
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: Animation event will be called
     */
    ShowNext();
    EXPECT_TRUE(isAnimationStart);
    EXPECT_TRUE(isAnimationEnd);
}

/**
 * @tc.name: UpdateSwiperPanEvent001
 * @tc.desc: Test UpdateSwiperPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, UpdateSwiperPanEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DisableSwipe default is false
     * @tc.expected: Has panEvent_
     */
    CreateDefaultSwiper();
    EXPECT_FALSE(pattern_->IsDisableSwipe());
    EXPECT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step2. Set DisableSwip to true
     * @tc.expected: Has no panEvent_
     */
    layoutProperty_->UpdateDisableSwipe(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step3. When is dragging
     * @tc.expected: Stop dragging
     */
    CreateDefaultSwiper();
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    EXPECT_TRUE(pattern_->isTouchDown_);
    layoutProperty_->UpdateDisableSwipe(true);
    frameNode_->MarkModifyDone();
    EXPECT_FALSE(pattern_->isTouchDown_);
}

/**
 * @tc.name: MouseAxisEventWithPageFlipMode001
 * @tc.desc: PageFlipMode property test with CONTINUOUS mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, AttrPageFlipModeTest001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    // default mode is PageFlipMode::CONTINUOUS(0)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-10.f);
    auto panEvent = frameNode_->GetEventHub<EventHub>()->gestureEventHub_->panEventActuator_->panEvents_.front();
    panEvent->actionStart_(info);
    EXPECT_TRUE(pattern_->isFirstAxisAction_);
    panEvent->actionUpdate_(info);
    EXPECT_FALSE(pattern_->isFirstAxisAction_);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    pattern_->propertyAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 2);
}

/**
 * @tc.name: MouseAxisEventWithPageFlipMode002
 * @tc.desc: PageFlipMode property test with SINGLE mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, AttrPageFlipModeTest002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetPageFlipMode(1);
    CreateSwiperItems();
    CreateSwiperDone();
    // mode is PageFlipMode::SINGLE(0)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 1);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-10.f);
    auto panEvent = frameNode_->GetEventHub<EventHub>()->gestureEventHub_->panEventActuator_->panEvents_.front();
    panEvent->actionStart_(info);
    EXPECT_TRUE(pattern_->isFirstAxisAction_);
    // axis update event will flip page, and isFirstAxisAction_ will be marked
    panEvent->actionUpdate_(info);
    EXPECT_FALSE(pattern_->isFirstAxisAction_);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    // propertyAnimation running will block page flipping
    pattern_->propertyAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    // frameAnimation running will block page flipping
    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->translateAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: MarginIgnoreBlankDragTest001
 * @tc.desc: Test Swiper IgnoreBlank with drag. When totalcount equal to displaycount, ignoreBlankOffset_ will be 0.f.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, MarginIgnoreBlankDragTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop false, totalcount equal to displaycount.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), true);
    model.SetNextMargin(Dimension(0.f), true);
    model.SetDisplayCount(4);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);

    /**
     * @tc.steps: step2. drag over end.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);

    info.SetMainDelta(-SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);

    /**
     * @tc.steps: step3. drag over start.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    info.SetMainDelta(SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);
}

/**
 * @tc.name: MarginIgnoreBlankDragTest002
 * @tc.desc: Test Swiper IgnoreBlank with drag.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, MarginIgnoreBlankDragTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop false, index = 1.
     * @tc.expected: ignoreBlankOffset_ will be NEXT_MARGIN.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNextMargin(Dimension(NEXT_MARGIN), true);
    model.SetDisplayCount(3);
    model.SetIndex(1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->ignoreBlankOffset_, NEXT_MARGIN);

    /**
     * @tc.steps: step2. drag over start.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);
}
} // namespace OHOS::Ace::NG
