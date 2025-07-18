/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"
#include "ui/base/geometry/dimension.h"

#include "core/components_ng/pattern/scroll/free_scroll_controller.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/event/touch_event.h"
#include "core/gestures/velocity.h"
// keep below to enable #ifdef private public
#include "test/mock/core/render/mock_render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float X = -3000;
constexpr float Y = -3000;
constexpr float CONTENT_W = 2000;
constexpr float CONTENT_H = 2000;
constexpr float SMALL_CONTENT_W = 100;
constexpr float SMALL_CONTENT_H = 50;
constexpr float DELTA_X = 100.0f;
constexpr float DELTA_Y = 100.0f;
constexpr float LARGE_DELTA_X = 2000.0f;
constexpr float LARGE_DELTA_Y = 2000.0f;
constexpr float VELOCITY_X = 1000.0f;
constexpr float VELOCITY_Y = 1000.0f;
} // namespace
using State = FreeScrollController::State;

class FreeScrollTest : public ScrollTestNg {
public:
    static void SetUpTestSuite()
    {
        ScrollTestNg::SetUpTestSuite();
        MockAnimationManager::Enable(true);
    }
    static void TearDownTestSuite()
    {
        ScrollTestNg::TearDownTestSuite();
        MockAnimationManager::Enable(false);
    }
    void TearDown() override
    {
        ScrollTestNg::TearDown();
        MockAnimationManager::GetInstance().Reset();
    }

    static GestureEvent MakePanGesture(const Offset& delta, const Velocity& velocity = Velocity())
    {
        GestureEvent gesture;
        gesture.SetSourceTool(SourceTool::FINGER);
        gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
        gesture.SetGlobalPoint(Point(1, 1));
        gesture.SetGlobalLocation({ 1, 1 });
        gesture.SetLocalLocation({ 1, 1 });
        gesture.SetDelta(delta);
        gesture.SetVelocity(velocity);
        return gesture;
    }

    static GestureEvent MakeMouseScrollGesture(const Offset& delta)
    {
        GestureEvent gesture;
        gesture.SetSourceTool(SourceTool::MOUSE);
        gesture.SetInputEventType(InputEventType::AXIS);
        gesture.SetDelta(delta);
        return gesture;
    }

    void ActionStart(GestureEvent& event)
    {
        const auto& controller = pattern_->freeScroll_;
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionStart_);
        auto&& func = *(controller->freePanGesture_->onActionStart_);
        func(event);
    }

    void ActionUpdate(GestureEvent& event)
    {
        const auto& controller = pattern_->freeScroll_;
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);
        auto&& func = *(controller->freePanGesture_->onActionUpdate_);
        func(event);
        FlushUITasks(frameNode_);
    }

    void ActionEnd(GestureEvent& event)
    {
        const auto& controller = pattern_->freeScroll_;
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionEnd_);
        auto&& func = *(controller->freePanGesture_->onActionEnd_);
        func(event);
    }

    void PanStart(const Offset& delta)
    {
        auto gesture = MakePanGesture(delta);
        ActionStart(gesture);
    }

    void PanUpdate(const Offset& delta)
    {
        auto gesture = MakePanGesture(delta);
        ActionUpdate(gesture);
    }

    void PanEnd(const Offset& delta, const Offset& velocity)
    {
        auto gesture = MakePanGesture(delta, Velocity(velocity));
        ActionEnd(gesture);
    }

    void MouseScrollStart()
    {
        auto gesture = MakeMouseScrollGesture({});
        ActionStart(gesture);
    }

    void MouseScrollUpdate(const Offset& delta)
    {
        auto gesture = MakeMouseScrollGesture(delta);
        ActionUpdate(gesture);
    }

    void MouseScrollEnd()
    {
        auto gesture = MakeMouseScrollGesture({});
        ActionEnd(gesture);
    }

    static TouchEventInfo MakeTouchEvent(TouchType type, const Offset& offset)
    {
        TouchEventInfo gesture("touch");
        TouchLocationInfo info(0);
        info.SetTouchType(type);
        info.SetLocalLocation(offset);
        info.SetGlobalLocation(offset);
        gesture.AddTouchLocationInfo(std::move(info));
        return gesture;
    }
    void TouchDown()
    {
        auto gesture = MakeTouchEvent(TouchType::DOWN, { 1, 1 });
        const auto& controller = pattern_->freeScroll_;
        ASSERT_TRUE(controller && controller->freeTouch_);
        controller->freeTouch_->GetTouchEventCallback()(gesture);
    }

    void TouchUp()
    {
        auto gesture = MakeTouchEvent(TouchType::UP, { 1, 1 });
        const auto& controller = pattern_->freeScroll_;
        ASSERT_TRUE(controller && controller->freeTouch_);
        controller->freeTouch_->GetTouchEventCallback()(gesture);
    }
};

/**
 * @tc.name: RecognizerOverride001
 * @tc.desc: Test gesture recognizer override when axis == FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, RecognizerOverride001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller->freePanGesture_);
    EXPECT_EQ(controller->freePanGesture_->GetRecognizerType(), GestureTypeName::PAN_GESTURE);
    EXPECT_TRUE(controller->freePanGesture_->IsSystemGesture());

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    ASSERT_TRUE(scrollHandler);
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link, 1);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), controller->freePanGesture_);
    EXPECT_EQ(*res.begin(), controller->freePanGesture_);
    ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);

    ScrollModelNG::SetScrollEnabled(frameNode_.GetRawPtr(), false);
    FlushUITasks(frameNode_);
    res.clear();
    link.clear();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link, 1);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), controller->freePanGesture_);
    EXPECT_EQ(*res.begin(), controller->freePanGesture_);
    EXPECT_FALSE(controller->freePanGesture_->IsEnabled());
}

/**
 * @tc.name: GestureJudge001
 * @tc.desc: Test GestureJudge
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, GestureJudge001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller->freePanGesture_);
    ASSERT_TRUE(controller->freePanGesture_->sysJudge_);
    std::vector<KeyCode> keys1 = { KeyCode::KEY_CTRL_LEFT };
    std::vector<KeyCode> keys2 = { KeyCode::KEY_CTRL_RIGHT };
    auto info = std::make_shared<PanGestureEvent>();
    info->SetPressedKeyCodes(keys1);
    RefPtr<GestureInfo> gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    gestureInfo->SetInputEventType(InputEventType::AXIS);
    auto res = controller->freePanGesture_->sysJudge_(gestureInfo, info);
    EXPECT_EQ(res, GestureJudgeResult::REJECT);

    info->SetPressedKeyCodes(keys2);
    res = controller->freePanGesture_->sysJudge_(gestureInfo, info);
    EXPECT_EQ(res, GestureJudgeResult::REJECT);

    gestureInfo->SetInputEventType(InputEventType::TOUCH_SCREEN);
    res = controller->freePanGesture_->sysJudge_(gestureInfo, info);
    EXPECT_EQ(res, GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test child constraint with Axis::FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Measure001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    ViewAbstract::SetWidth(CalcLength(1.0f));
    ViewAbstract::SetHeight(CalcLength(1.0f));
    ColumnModelNG col;
    col.Create(Dimension(0), nullptr, "");
    CreateContentChild(1);
    CreateScrollDone();
    EXPECT_EQ(GetChildSize(frameNode_, 0), SizeF(1, ITEM_MAIN_SIZE));
}

/**
 * @tc.name: FreeScroll001
 * @tc.desc: Test Scroll with Axis::FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, FreeScroll001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    PanUpdate({ -DELTA_X, -DELTA_Y });
    EXPECT_EQ(GetChildX(frameNode_, 0), -DELTA_X);
    EXPECT_EQ(GetChildY(frameNode_, 0), -DELTA_Y);
}

/**
 * @tc.name: FreeScroll001
 * @tc.desc: Test scroll enabled
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, EnableScroll001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ WIDTH, HEIGHT * 2 });
    CreateScrollDone();
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF());
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
    PanUpdate({ -DELTA_X, -DELTA_Y });
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, -DELTA_Y));
    EXPECT_FALSE(pattern_->scrollBar2d_->horizontal_->NeedPaint());
    EXPECT_TRUE(pattern_->scrollBar2d_->vertical_->NeedPaint());
    EXPECT_EQ(pattern_->scrollBar2d_->painter_->horizontal_->GetOpacity(), 0);
    EXPECT_NE(pattern_->scrollBar2d_->painter_->vertical_->GetOpacity(), 0);
}

/**
 * @tc.name: InitialOffset001
 * @tc.desc: Test Scroll with Axis::FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, InitialOffset001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetInitialOffset({ CalcDimension(0.5, DimensionUnit::PERCENT), CalcDimension(DELTA_Y) });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    EXPECT_EQ(GetChildX(frameNode_, 0), -WIDTH / 2);
    EXPECT_EQ(GetChildY(frameNode_, 0), -DELTA_Y);

    PanUpdate({ -DELTA_X, -DELTA_Y });
    EXPECT_EQ(GetChildX(frameNode_, 0), -WIDTH / 2 - DELTA_X);
    EXPECT_EQ(GetChildY(frameNode_, 0), -DELTA_Y * 2);
}

/**
 * @tc.name: Properties001
 * @tc.desc: check property values with Axis::Free (main axis should be horizontal)
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Properties001)
{
    constexpr float contentWidth = 1000;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ contentWidth, CONTENT_H });
    CreateScrollDone();

    EXPECT_EQ(pattern_->scrollableDistance_, contentWidth - WIDTH);
    EXPECT_EQ(pattern_->viewPortLength_, WIDTH);
}

/**
 * @tc.name: ModeChange001
 * @tc.desc: Test Scroll axis change
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ModeChange001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link, 1);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), controller->freePanGesture_);
    EXPECT_EQ(*res.begin(), controller->freePanGesture_);
    ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);

    res.clear();
    link.clear();

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    ASSERT_FALSE(pattern_->freeScroll_);
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link, 1);
    EXPECT_EQ(link.size(), 1);
    ASSERT_EQ(*link.begin(), scrollHandler->GetScrollable()->panRecognizerNG_);
}

/**
 * @tc.name: ModeChange002
 * @tc.desc: Test offset reset
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ModeChange002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);
    pattern_->currentOffset_ = 20.0f;

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    ASSERT_FALSE(controller);
    ASSERT_EQ(pattern_->currentOffset_, 0);
}

/**
 * @tc.name: OverScroll001
 * @tc.desc: Test overScroll
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, OverScroll001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);
    controller->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);

    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(X, Y));

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::NONE, true, EffectEdge::ALL);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(WIDTH - CONTENT_W, HEIGHT - CONTENT_H).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::START);
    controller->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(WIDTH - CONTENT_W, Y).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::END);
    controller->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(X, Y));
}

/**
 * @tc.name: OverScroll002
 * @tc.desc: Test overScroll when content is smaller than viewport
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, OverScroll002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ SMALL_CONTENT_W, SMALL_CONTENT_H });
    CreateScrollDone();
    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);
    controller->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);

    constexpr float alignX = (WIDTH - SMALL_CONTENT_W) / 2;
    constexpr float alignY = (HEIGHT - SMALL_CONTENT_H) / 2;

    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(X + alignX, Y + alignY).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::FADE, true, EffectEdge::ALL);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::START);
    controller->offset_->Set(OffsetF { X, -Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY - Y).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::END);
    controller->offset_->Set(OffsetF { -X, -Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY - Y).ToString());
}

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo animation interrupt
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollTo001)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ -DELTA_X, -DELTA_Y });
    PanEnd({}, { -VELOCITY_X, -VELOCITY_Y });
    EXPECT_EQ(pattern_->freeScroll_->state_, State::FLING);

    pattern_->freeScroll_->ScrollTo(OffsetF(-DELTA_X, -DELTA_Y), {});
    // destination reached immediately, previous animation is stopped
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
}

/**
 * @tc.name: Touch001
 * @tc.desc: Test multiple touch
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Touch001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    TouchDown();
    PanStart({});
    PanUpdate({ DELTA_X, DELTA_Y });
    auto&& controller = pattern_->freeScroll_;
    EXPECT_EQ(controller->state_, State::DRAG);
    TouchDown();                                // second finger down
    EXPECT_EQ(controller->state_, State::DRAG); // should not change state
    PanUpdate({ DELTA_X, DELTA_Y });
    EXPECT_EQ(controller->state_, State::DRAG); // should not change state
    TouchUp();                                  // first finger up
    EXPECT_EQ(controller->state_, State::DRAG); // should not change state
    TouchUp();                                  // second finger up
    PanEnd({ DELTA_X, DELTA_Y }, { VELOCITY_X, VELOCITY_Y });
    EXPECT_EQ(controller->state_, State::FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, 0)); // bounced back to boundary
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, State::IDLE);
}

/**
 * @tc.name: MouseWheel001
 * @tc.desc: Test wheel scroll shouldn't start fling animation
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, MouseWheel001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    MouseScrollStart();
    auto& freeScroll = *pattern_->freeScroll_;
    EXPECT_EQ(freeScroll.state_, State::DRAG);
    MouseScrollUpdate({ 0, -DELTA_Y });
    EXPECT_EQ(freeScroll.state_, State::DRAG);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, -DELTA_Y));
    EXPECT_TRUE(freeScroll.mouseWheelScrollIsVertical_);
    MouseScrollEnd();
    EXPECT_EQ(freeScroll.state_, State::IDLE);
    ASSERT_TRUE(freeScroll.axisAnimator_);
    EXPECT_TRUE(freeScroll.axisAnimator_->IsRunning());
    MouseScrollStart();
    EXPECT_TRUE(freeScroll.axisAnimator_->IsRunning()); // next mouse event shouldn't stop animation
    PanStart({});
    EXPECT_FALSE(freeScroll.axisAnimator_->IsRunning()); // drag event should stop animation
}

/**
 * @tc.name: MouseWheel002
 * @tc.desc: Test wheel scroll frame callback
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, MouseWheel002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    auto& freeScroll = *pattern_->freeScroll_;
    MouseScrollStart();
    MouseScrollUpdate({ 0, -DELTA_Y });
    freeScroll.HandleAxisAnimationFrame(-DELTA_Y / 2);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, -DELTA_Y / 2));
    freeScroll.HandleAxisAnimationFrame(-DELTA_Y);
    MouseScrollUpdate({ 0, -DELTA_Y });
    EXPECT_EQ(freeScroll.axisAnimator_->GetAxisScrollMotion()->GetFinalPosition(), -DELTA_Y * 2);
    MouseScrollEnd();
    MouseScrollStart();
    MouseScrollUpdate({ -DELTA_X, 0 });
    MouseScrollEnd();
    EXPECT_TRUE(freeScroll.axisAnimator_->IsRunning());
    freeScroll.HandleAxisAnimationFrame(-DELTA_X);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(-DELTA_X, -DELTA_Y));

    freeScroll.ScrollTo({LARGE_DELTA_X, LARGE_DELTA_Y}, std::nullopt); // start a scroll animation
    freeScroll.HandleAxisAnimationFrame(-DELTA_X); // should be ignored
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(-DELTA_X, -DELTA_Y));
    MockAnimationManager::GetInstance().Reset();
}

/**
 * @tc.name: Animation001
 * @tc.desc: Test normal animation with Axis::FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Animation001)
{
    constexpr float friction = 0.5f;
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetFriction(friction);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ DELTA_X, DELTA_Y });
    EXPECT_LT(GetChildOffset(frameNode_, 0).GetX(), DELTA_X);
    EXPECT_LT(GetChildOffset(frameNode_, 0).GetY(), DELTA_Y);

    PanEnd({ DELTA_X, DELTA_Y }, { VELOCITY_X, VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, 0)); // bounced back to boundary

    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    auto controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller);
    EXPECT_EQ(controller->state_, State::IDLE);
    PanStart({});
    PanUpdate({ -DELTA_X, DELTA_Y });
    EXPECT_EQ(controller->state_, State::DRAG);
    PanEnd({ -DELTA_X, DELTA_Y }, { -VELOCITY_X, VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, State::FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    ASSERT_TRUE(pattern_->freeScroll_);
    EXPECT_LT(GetChildX(frameNode_, 0), -DELTA_X); // triggered high response spring
    EXPECT_EQ(GetChildY(frameNode_, 0), 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, State::IDLE);

    constexpr float friction2 = 0.8f;
    ScrollModelNG::SetFriction(frameNode_.GetRawPtr(), friction2);
    PanEnd({}, { 0, -VELOCITY_Y });
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), -VELOCITY_Y * FLING_SCALE_K / (friction2 * -FRICTION_SCALE));
}

/**
 * @tc.name: Animation002
 * @tc.desc: Test animation interrupted by touch
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Animation002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ DELTA_X, DELTA_Y });
    EXPECT_LT(GetChildOffset(frameNode_, 0).GetX(), DELTA_X);
    EXPECT_LT(GetChildOffset(frameNode_, 0).GetY(), DELTA_Y);

    PanEnd({ DELTA_X, DELTA_Y }, { VELOCITY_X, VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().TickByVelocity(
        OffsetF(VELOCITY_X, VELOCITY_Y)); // simulate scrolling out of bounds
    FlushUITasks(frameNode_);
    EXPECT_GT(GetChildX(frameNode_, 0), VELOCITY_X);
    EXPECT_GT(GetChildY(frameNode_, 0), VELOCITY_Y);

    auto controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller);
    EXPECT_EQ(controller->state_, State::FLING);

    TouchDown();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, State::IDLE);
    TouchUp();
    EXPECT_EQ(controller->state_, State::FLING);
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, 0));
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, State::IDLE);
}

/**
 * @tc.name: Animation003
 * @tc.desc: Test animation with end overScroll
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Animation003)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetInitialOffset({ CalcDimension(CONTENT_W), CalcDimension(CONTENT_H) });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    EXPECT_EQ(GetChildX(frameNode_, 0), -CONTENT_W);
    EXPECT_EQ(GetChildY(frameNode_, 0), -CONTENT_H);
    PanStart({});
    PanUpdate({ -LARGE_DELTA_X, -LARGE_DELTA_Y });
    EXPECT_LT(GetChildX(frameNode_, 0), -CONTENT_W);
    EXPECT_LT(GetChildY(frameNode_, 0), -CONTENT_H);
    EXPECT_GT(GetChildX(frameNode_, 0), -CONTENT_W - LARGE_DELTA_X);
    EXPECT_GT(GetChildY(frameNode_, 0), -CONTENT_H - LARGE_DELTA_Y);
    PanEnd({ -LARGE_DELTA_X, -LARGE_DELTA_Y }, { -VELOCITY_X, -VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    ASSERT_TRUE(pattern_->freeScroll_);
    EXPECT_EQ(GetChildX(frameNode_, 0), WIDTH - CONTENT_W);
    EXPECT_EQ(GetChildY(frameNode_, 0), HEIGHT - CONTENT_H);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: Animation004
 * @tc.desc: Test switching friction during animation
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Animation004)
{
    constexpr float friction = 0.8f;
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetFriction(friction);
    model.SetInitialOffset({ CalcDimension(DELTA_X), CalcDimension(DELTA_Y) });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ DELTA_X - 1, DELTA_Y - 1 });
    MockAnimationManager::GetInstance().SetTicks(2);
    PanEnd({ -LARGE_DELTA_X, -LARGE_DELTA_Y }, { VELOCITY_X, VELOCITY_Y });
    EXPECT_EQ(pattern_->freeScroll_->state_, State::FLING);
    EXPECT_EQ(pattern_->freeScroll_->offset_->GetStagingValue().GetX(),
        -1 + VELOCITY_X * FLING_SCALE_K / (friction * -FRICTION_SCALE));
    MockAnimationManager::GetInstance().Tick(); // switched to high-friction spring motion after reaching edge
    EXPECT_EQ(pattern_->freeScroll_->state_, State::BOUNCE);
    EXPECT_EQ(pattern_->freeScroll_->offset_->GetStagingValue(), OffsetF());
    FlushUITasks(frameNode_);
    EXPECT_GT(GetChildX(frameNode_, 0), 0);
    EXPECT_GT(GetChildY(frameNode_, 0), 0);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
}

/**
 * @tc.name: Events001
 * @tc.desc: Test scroll events
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Event001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    static bool scrollBegun = false;
    model.SetOnScrollStart([]() { scrollBegun = true; });
    model.SetOnScrollStop([]() { scrollBegun = false; });
    static int32_t willScrollCalled = 0;
    model.SetOnWillScroll(
        [](const Dimension& xOffset, const Dimension& yOffset, ScrollState state, ScrollSource source) {
            if (willScrollCalled == 0) {
                EXPECT_EQ(xOffset.Unit(), DimensionUnit::VP);
                EXPECT_EQ(yOffset.Unit(), DimensionUnit::VP);
                EXPECT_EQ(xOffset.Value(), DELTA_X);
                EXPECT_EQ(yOffset.Value(), DELTA_Y);
                EXPECT_EQ(state, ScrollState::SCROLL);
                EXPECT_EQ(source, ScrollSource::DRAG);
            } else {
                EXPECT_EQ(state, ScrollState::FLING);
            }
            ++willScrollCalled;
            return TwoDimensionScrollResult { .xOffset = Dimension(DELTA_X), .yOffset = 0.0_vp };
        });
    static int32_t didScroll = 0;
    model.SetOnDidScroll([](const Dimension& xOffset, const Dimension& yOffset, ScrollState state) {
        if (didScroll == 0) {
            EXPECT_EQ(xOffset.Value(), DELTA_X);
            EXPECT_EQ(yOffset.Value(), 0.0f);
            EXPECT_EQ(state, ScrollState::SCROLL);
        } else {
            EXPECT_EQ(state, ScrollState::IDLE);
        }
        ++didScroll;
    });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    EXPECT_TRUE(scrollBegun);
    PanUpdate({ -DELTA_X, -DELTA_Y });
    EXPECT_EQ(GetChildX(frameNode_, 0), -DELTA_X);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(didScroll, 1);
    EXPECT_EQ(willScrollCalled, 1);

    PanEnd({ -DELTA_X, -DELTA_Y }, { -VELOCITY_X, -VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(willScrollCalled, 2);
    FlushUITasks(frameNode_);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
    EXPECT_FALSE(scrollBegun);
}

/**
 * @tc.name: Events002
 * @tc.desc: Test double callback behavior
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Event002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    static int32_t scrollBegun = 0;
    static int32_t scrollStop = 0;
    static int32_t willScrollCalled = 0;
    static int32_t didScroll = 0;

    auto onScrollStart = []() { ++scrollBegun; };
    auto onScrollStop = []() { ++scrollStop; };
    auto onDidScroll = [](const Dimension& xOffset, const Dimension& yOffset, ScrollState state) { ++didScroll; };

    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnDidScroll(onDidScroll);
    model.SetOnWillScroll(
        [](const Dimension& xOffset, const Dimension& yOffset, ScrollState state, ScrollSource source) {
            ++willScrollCalled;
            return TwoDimensionScrollResult { .xOffset = xOffset * 2, .yOffset = yOffset * 2 };
        });

    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    ViewAbstract::SetJSFrameNodeOnScrollWillScroll(frameNode_.GetRawPtr(),
        [](const Dimension& xOffset, const Dimension& yOffset, ScrollState state, ScrollSource source) {
            EXPECT_EQ(xOffset.Unit(), DimensionUnit::VP);
            EXPECT_EQ(willScrollCalled % 2, 1);
            if (willScrollCalled == 1) {
                EXPECT_EQ(xOffset.Value(), DELTA_X * 2); // should receive offset already modified by onWillScroll
                EXPECT_EQ(yOffset.Value(), DELTA_Y * 2);
                EXPECT_EQ(state, ScrollState::SCROLL);
                EXPECT_EQ(source, ScrollSource::DRAG);
            }
            ++willScrollCalled;
            return TwoDimensionScrollResult { .xOffset = 0.0_vp, .yOffset = 0.0_vp }; // should take precedence
        });
    ViewAbstract::SetJSFrameNodeOnScrollDidScroll(frameNode_.GetRawPtr(), onDidScroll);
    ViewAbstract::SetJSFrameNodeOnScrollStart(frameNode_.GetRawPtr(), onScrollStart);
    ViewAbstract::SetJSFrameNodeOnScrollStop(frameNode_.GetRawPtr(), onScrollStop);

    PanStart({});
    EXPECT_EQ(scrollBegun, 2);
    PanUpdate({ -DELTA_X, -DELTA_Y });
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF {});
    EXPECT_EQ(didScroll, 0); // position didn't change, so no trigger
    EXPECT_EQ(willScrollCalled, 2);

    PanEnd({ -DELTA_X, -DELTA_Y }, { -VELOCITY_X, -VELOCITY_Y });
    EXPECT_EQ(scrollStop, 0);
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(willScrollCalled, 4);
    FlushUITasks(frameNode_);
    EXPECT_TRUE(Negative(GetChildX(frameNode_, 0))); // delta during animation can't be modified by onWillScroll
    EXPECT_TRUE(Negative(GetChildY(frameNode_, 0)));
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
    EXPECT_EQ(scrollStop, 2);
    EXPECT_EQ(didScroll, 2);
}

/**
 * @tc.name: Events003
 * @tc.desc: Test onReachStart disabled
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Event003)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetOnReachStart([]() { ADD_FAILURE() << "onReachStart should not be called in FreeScroll mode"; });
    model.SetOnReachEnd([]() { ADD_FAILURE() << "onReachEnd should not be called in FreeScroll mode"; });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    PanUpdate({ DELTA_X, DELTA_Y });
    pattern_->freeScroll_->SetOffset({ -CONTENT_W + WIDTH + 1, -CONTENT_H + HEIGHT + 1 });
    for (int i = 0; i < 3; ++i) {
        PanUpdate({ -DELTA_X, -DELTA_Y });
    }
    EXPECT_LT(GetChildX(frameNode_, 0), -CONTENT_W + WIDTH);
    EXPECT_LT(GetChildY(frameNode_, 0), -CONTENT_H + HEIGHT);
}

/**
 * @tc.name: Scroller001
 * @tc.desc: Test scroller interface
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Scroller001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    static int32_t willScrollCalled = 0;
    model.SetOnWillScroll(
        [](const Dimension& xOffset, const Dimension& yOffset, ScrollState state, ScrollSource source) {
            EXPECT_EQ(state, ScrollState::IDLE);
            EXPECT_EQ(source, ScrollSource::SCROLLER);
            ++willScrollCalled;
            return TwoDimensionScrollResult { .xOffset = xOffset, .yOffset = yOffset };
        });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    auto scroller = AceType::MakeRefPtr<ScrollableController>();
    scroller->SetScrollPattern(pattern_);

    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);
    controller->offset_->Set(OffsetF { X, Y });

    EXPECT_EQ(scroller->GetCurrentOffset(), Offset(-X, -Y));

    scroller->ScrollBy(DELTA_X, DELTA_X, false);
    EXPECT_EQ(
        scroller->GetCurrentOffset().ToString(), Offset(CONTENT_W - WIDTH, CONTENT_H - HEIGHT).ToString()); // clamped
    FlushUITasks();
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(-CONTENT_W + WIDTH, -CONTENT_H + HEIGHT));
    EXPECT_EQ(willScrollCalled, 2);

    scroller->ScrollBy(-DELTA_X, -DELTA_Y, false);
    FlushUITasks();
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(-CONTENT_W + WIDTH + DELTA_X, -CONTENT_H + HEIGHT + DELTA_Y));
    EXPECT_EQ(willScrollCalled, 3);
}

/**
 * @tc.name: Scroller002
 * @tc.desc: Test scroller interface
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Scroller002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    auto scroller = AceType::MakeRefPtr<ScrollableController>();
    scroller->SetScrollPattern(pattern_);

    EXPECT_EQ(scroller->GetItemRect(0), Rect(0, 0, CONTENT_W, CONTENT_H));
    scroller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(-CONTENT_W + WIDTH, 0).ToString());
    scroller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 1000.0f);
    EXPECT_EQ(pattern_->freeScroll_->state_, State::EXTERNAL_FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(-CONTENT_W + WIDTH, -CONTENT_H + HEIGHT).ToString());

    const Dimension posX = 5.0_vp;
    const Dimension posY = 10.0_vp;
    scroller->FreeScrollTo({ posX, posY });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(-posX.Value(), -posY.Value()).ToString());

    const Dimension posX_2 = 500.0_vp;
    const Dimension posY_2 = -100.0_vp;
    scroller->FreeScrollTo({ posX_2, posY_2, 1000, nullptr, true });
    EXPECT_EQ(pattern_->freeScroll_->state_, State::EXTERNAL_FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(-posX_2.Value(), 0.0f).ToString());

    scroller->FreeScrollTo({ -posX, -posY });
    FlushUITasks(frameNode_); // can't overScroll by default
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF());

    scroller->FreeScrollTo({ .xOffset = -posX, .yOffset = -posY, .canOverScroll = true });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(posX.Value(), posY.Value()));
}

/**
 * @tc.name: Scroller003
 * @tc.desc: Test scroller scrollPage
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Scroller003)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    auto scroller = AceType::MakeRefPtr<ScrollableController>();
    scroller->SetScrollPattern(pattern_);

    scroller->ScrollPage(false, false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(0, -HEIGHT).ToString());

    scroller->ScrollPage(false, true);
    EXPECT_EQ(State::EXTERNAL_FLING, pattern_->freeScroll_->state_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(State::IDLE, pattern_->freeScroll_->state_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(0, -HEIGHT * 2).ToString());

    scroller->ScrollPage(true, false);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, -HEIGHT));

    scroller->ScrollPage(true, true);
    EXPECT_EQ(State::EXTERNAL_FLING, pattern_->freeScroll_->state_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(State::IDLE, pattern_->freeScroll_->state_);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(0, 0).ToString());
}

/**
 * @tc.name: Scroller004
 * @tc.desc: Test scroller interface
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Scroller004)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    auto scroller = AceType::MakeRefPtr<ScrollableController>();
    scroller->SetScrollPattern(pattern_);

    MockAnimationManager::GetInstance().SetTicks(2);

    scroller->FreeScrollTo(
        { .xOffset = Dimension(CONTENT_W), .yOffset = Dimension(CONTENT_H), .smooth = true, .canOverScroll = true });
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(-CONTENT_W, -CONTENT_H).ToString());
}

namespace {
const Dimension NORMAL_BAR_WIDTH = 4.0_vp;
} // namespace

/**
 * @tc.name: ScrollBar001
 * @tc.desc: Test scrollBar 2D
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    const auto scrollBar = pattern_->scrollBar2d_;
    ASSERT_TRUE(scrollBar);
    EXPECT_EQ(scrollBar->vertical_->GetActiveRect().ToString(), "Rect (236.00, 8.00) - [4.00 x 76.80]");
    EXPECT_EQ(scrollBar->horizontal_->GetActiveRect().ToString(), "Rect (8.00, 396.00) - [26.88 x 4.00]");
    EXPECT_EQ(scrollBar->vertical_->GetActiveWidth(), NORMAL_BAR_WIDTH * 2);
    EXPECT_EQ(scrollBar->horizontal_->GetActiveWidth(), NORMAL_BAR_WIDTH * 2);
    EXPECT_EQ(scrollBar->vertical_->GetTouchRegion().ToString(), "Rect (208.00, 8.00) - [32.00 x 76.80]");
    EXPECT_EQ(scrollBar->vertical_->GetNormalWidth(), NORMAL_BAR_WIDTH);

    const Dimension NEW_BAR_WIDTH = 10.0_vp;
    ScrollModelNG::SetScrollBarWidth(frameNode_.GetRawPtr(), NEW_BAR_WIDTH);
    pattern_->OnModifyDone();
    EXPECT_EQ(scrollBar->vertical_->GetNormalWidth(), NEW_BAR_WIDTH);

    ASSERT_TRUE(scrollBar->painter_);
    EXPECT_EQ(scrollBar->painter_->vertical_->GetHoverAnimatingType(), HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->painter_->horizontal_->GetBarColor()->Get().ToString(), "#66182431");
    EXPECT_EQ(scrollBar->vertical_->GetScrollBarMargin(), ScrollBar2D::DEFAULT_MARGIN);
}

/**
 * @tc.name: ScrollBar002
 * @tc.desc: Test scrollBar 2D
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    pattern_->FreeScrollBy({ -LARGE_DELTA_X, -LARGE_DELTA_Y });
    FlushUITasks(frameNode_);
    const auto scrollBar = pattern_->scrollBar2d_;
    ASSERT_TRUE(scrollBar);
    EXPECT_EQ(scrollBar->vertical_->GetActiveRect().ToString(), "Rect (236.00, 315.20) - [4.00 x 76.80]");
    EXPECT_EQ(scrollBar->horizontal_->GetActiveRect().ToString(), "Rect (205.12, 396.00) - [26.88 x 4.00]");

    ScrollModelNG::SetScrollBarColor(frameNode_.GetRawPtr(), Color::BLUE);
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(scrollBar->painter_->horizontal_->GetBarColor()->Get(), Color::BLUE);
}

/**
 * @tc.name: ScrollBar003
 * @tc.desc: Test scrollBar display mode
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar003)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    EXPECT_EQ(pattern_->scrollBar2d_->painter_->vertical_->GetOpacity(), UINT8_MAX);

    ScrollModelNG::SetScrollBar(frameNode_.GetRawPtr(), DisplayMode::OFF);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->scrollBar2d_->vertical_->GetDisplayMode(), DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar2d_->horizontal_->GetDisplayMode(), DisplayMode::OFF);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->scrollBar2d_->painter_->horizontal_->GetOpacity(), 0);
}

/**
 * @tc.name: ScrollBar004
 * @tc.desc: Test scrollBar touch target
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar004)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    PointF localPoint;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    const auto& actuator = frameNode_->GetOrCreateGestureEventHub()->scrollableActuator_;
    ASSERT_EQ(actuator->scrollableEvents_.size(), 1);
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult, 1);
    EXPECT_EQ(responseLinkResult.size(), 2);

    localPoint = PointF(238, 10);
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult, 1);
    EXPECT_EQ(responseLinkResult.size(), 3);
    EXPECT_EQ(responseLinkResult.front(), pattern_->scrollBar2d_->vertical_->GetPanRecognizer());

    constexpr int32_t expectedRecognizerCount = 3; // 2 from scrollBars, 1 from pan recognizer
    localPoint = PointF(10, 398);
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult, 1);
    EXPECT_EQ(responseLinkResult.size(), expectedRecognizerCount);
    EXPECT_EQ(*std::next(responseLinkResult.begin()), pattern_->scrollBar2d_->horizontal_->GetPanRecognizer());

    TouchRestrict restrict;
    restrict.sourceType = SourceType::MOUSE;
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult, 1);
    EXPECT_EQ(responseLinkResult.size(), expectedRecognizerCount);
    EXPECT_EQ(*std::next(responseLinkResult.begin()), pattern_->scrollBar2d_->horizontal_->GetPanRecognizer());
}

/**
 * @tc.name: ScrollBar005
 * @tc.desc: Test scrollBar on axis change
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar005)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::VERTICAL);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    EXPECT_TRUE(pattern_->scrollBar_);

    auto* ctx = AceType::DynamicCast<MockRenderContext>(pattern_->GetRenderContext());
    EXPECT_CALL(*ctx, RemoveOverlayModifier(Eq(pattern_->GetScrollBarOverlayModifier()))).Times(1);
    layoutProperty_->UpdateAxis(Axis::FREE);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->scrollBar2d_);
    EXPECT_FALSE(pattern_->scrollBar_);

    EXPECT_CALL(*ctx, RemoveOverlayModifier(Eq(pattern_->scrollBar2d_->GetPainter()))).Times(1);
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->scrollBar2d_);
    EXPECT_TRUE(pattern_->scrollBar_);
}

/**
 * @tc.name: ScrollBar006
 * @tc.desc: Test scrollBar appear animation
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar006)
{
    auto mockTaskExecutor = AceType::MakeRefPtr<MockScrollTaskExecutor>();
    PipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_FALSE(pattern_->scrollBar_);
    ASSERT_TRUE(pattern_->scrollBar2d_);
    const auto& verticalBar = *pattern_->scrollBar2d_->vertical_;
    const auto& horizontalBar = *pattern_->scrollBar2d_->horizontal_;
    const auto& painter = *pattern_->scrollBar2d_->painter_->horizontal_;
    mockTaskExecutor
        ->RunDelayTask(); // testing horizontal to avoid MockTaskExecutor's bug (only running last added task)
    EXPECT_EQ(horizontalBar.opacityAnimationType_, OpacityAnimationType::DISAPPEAR);
    FlushUITasks(frameNode_);
    EXPECT_EQ(painter.opacity_->Get(), 0);

    PanStart({});
    EXPECT_EQ(verticalBar.opacityAnimationType_, OpacityAnimationType::APPEAR);
    PanUpdate({ -DELTA_X, -DELTA_Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(horizontalBar.opacityAnimationType_, OpacityAnimationType::NONE);
    EXPECT_EQ(painter.opacity_->Get(), UINT8_MAX);
    PanEnd({}, {});
    mockTaskExecutor->RunDelayTask();
    EXPECT_EQ(horizontalBar.opacityAnimationType_, OpacityAnimationType::DISAPPEAR);
    FlushUITasks(frameNode_);
    EXPECT_EQ(horizontalBar.opacityAnimationType_, OpacityAnimationType::NONE);
    EXPECT_EQ(painter.opacity_->Get(), 0);
}

/**
 * @tc.name: ScrollBar007
 * @tc.desc: Test scrollBar overScroll
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollBar007)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ DELTA_X, DELTA_Y });
    auto& bar = *pattern_->scrollBar2d_->horizontal_;
    EXPECT_GT(GetChildX(frameNode_, 0), 0);
    EXPECT_GT(bar.GetOutBoundary(), 0);

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::NONE, true, EffectEdge::ALL);
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
    EXPECT_EQ(bar.GetOutBoundary(), 0);

    MockAnimationManager::GetInstance().SetTicks(2);
    PanEnd({}, { VELOCITY_X, VELOCITY_Y });
    EXPECT_EQ(pattern_->freeScroll_->state_, State::FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(bar.GetOutBoundary(), 0);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(bar.GetOutBoundary(), 0);
    EXPECT_EQ(pattern_->freeScroll_->state_, State::IDLE);
}

/**
 * @tc.name: OnScrollEdge001
 * @tc.desc: Test onScrollEdge event triggered when scrolling to each edge individually
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, OnScrollEdge001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);

    // Track triggered edges
    std::vector<ScrollEdge> triggeredEdges;
    model.SetOnScrollEdge([&triggeredEdges](ScrollEdge edge) { triggeredEdges.push_back(edge); });

    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);

    PanStart({});
    PanUpdate({ -1, 0.0f });
    // Now scroll back right to cross the LEFT edge (from negative to 0/positive)
    PanUpdate({ LARGE_DELTA_X, 0.0f }); // Scroll back right to trigger LEFT edge
    EXPECT_EQ(triggeredEdges.size(), 1);
    EXPECT_EQ(triggeredEdges.front(), ScrollEdge::LEFT);

    controller->SetOffset(OffsetF { -(CONTENT_W - WIDTH) + 1, -(CONTENT_H - HEIGHT) + 1 });
    triggeredEdges.clear();
    PanUpdate({ -LARGE_DELTA_X, -LARGE_DELTA_Y }); // Scroll left to cross RIGHT edge
    EXPECT_EQ(triggeredEdges.size(), 2);
    EXPECT_EQ(triggeredEdges.front(), ScrollEdge::RIGHT);
    EXPECT_EQ(triggeredEdges.back(), ScrollEdge::BOTTOM);

    controller->SetOffset(OffsetF { 0, -1 });
    FlushUITasks(frameNode_);
    triggeredEdges.clear();
    PanUpdate({ LARGE_DELTA_X, LARGE_DELTA_Y });
    EXPECT_EQ(triggeredEdges.size(), 1);
    EXPECT_EQ(triggeredEdges.front(), ScrollEdge::TOP);
}

/**
 * @tc.name: OnScrollEdge002
 * @tc.desc: Test onScrollEdge event
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, OnScrollEdge002)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    std::vector<ScrollEdge> triggeredEdges;
    model.SetOnScrollEdge([&triggeredEdges](ScrollEdge edge) { triggeredEdges.push_back(edge); });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    const auto& controller = pattern_->freeScroll_;
    ASSERT_TRUE(controller && controller->offset_);

    controller->SetOffset(OffsetF { -(CONTENT_W - WIDTH) + 1, -1 });
    FlushUITasks(frameNode_);
    PanStart({});
    PanUpdate({ -LARGE_DELTA_X, LARGE_DELTA_Y }); // Try to trigger TOP and RIGHT edges
    EXPECT_EQ(triggeredEdges.size(), 2);
    EXPECT_EQ(triggeredEdges.front(), ScrollEdge::RIGHT);
    EXPECT_EQ(triggeredEdges.back(), ScrollEdge::TOP);

    triggeredEdges.clear();
    controller->SetOffset(OffsetF { -1, -(CONTENT_H - HEIGHT) + 1 });
    FlushUITasks(frameNode_);
    PanEnd({ LARGE_DELTA_X, -LARGE_DELTA_Y }, { VELOCITY_X, -VELOCITY_Y }); // test edge during animation
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(triggeredEdges.size(), 2);
    EXPECT_EQ(triggeredEdges.front(), ScrollEdge::LEFT);
    EXPECT_EQ(triggeredEdges.back(), ScrollEdge::BOTTOM);
}

/**
 * @tc.name: ScrollableState001
 * @tc.desc: Test enableScroll after switching axis
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, ScrollableState001)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    model.SetScrollEnabled(false);
    CreateScrollDone();

    EXPECT_FALSE(pattern_->scrollableEvent_->GetEnabled());
    ScrollModelNG::SetAxis(frameNode_.GetRawPtr(), Axis::FREE);
    ScrollModelNG::SetScrollEnabled(frameNode_.GetRawPtr(), true);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->scrollableEvent_->GetEnabled());
}

/**
 * @tc.name: GestureReset001
 * @tc.desc: Ensure gesture->IsEnabled() is synced with scroll state
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, GestureReset001)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::FREE);
    model.SetScrollEnabled(false);
    CreateScrollDone();
    auto gesture = pattern_->freeScroll_->GetFreePanGesture();
    EXPECT_FALSE(gesture->IsEnabled());
    gesture->ResetStatusOnFinish(); // reset automatically called when a gesture finishes
    EXPECT_TRUE(gesture->IsEnabled());
    gesture = pattern_->freeScroll_->GetFreePanGesture();
    EXPECT_FALSE(gesture->IsEnabled());
}
} // namespace OHOS::Ace::NG
