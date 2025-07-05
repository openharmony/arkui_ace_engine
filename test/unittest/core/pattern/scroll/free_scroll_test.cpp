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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"
#include "ui/base/geometry/dimension.h"

#include "core/components_ng/pattern/scroll/free_scroll_controller.h"
#include "core/event/touch_event.h"
#include "core/gestures/velocity.h"
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

    void PanStart(const Offset& delta)
    {
        const auto& controller = pattern_->freeScroll_;
        auto gesture = MakePanGesture(delta);
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionStart_);
        auto&& func = *(controller->freePanGesture_->onActionStart_);
        func(gesture);
    }
    void PanUpdate(const Offset& delta)
    {
        const auto& controller = pattern_->freeScroll_;
        auto gesture = MakePanGesture(delta);
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);
        auto&& func = *(controller->freePanGesture_->onActionUpdate_);
        func(gesture);
    }
    void PanEnd(const Offset& delta, const Offset& velocity)
    {
        const auto& controller = pattern_->freeScroll_;
        auto gesture = MakePanGesture(delta, Velocity(velocity));
        ASSERT_TRUE(controller && controller->freePanGesture_);
        ASSERT_TRUE(controller->freePanGesture_->onActionEnd_);
        auto&& func = *(controller->freePanGesture_->onActionEnd_);
        func(gesture);
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

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    ASSERT_TRUE(scrollHandler);
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), controller->freePanGesture_);
    EXPECT_EQ(*res.begin(), controller->freePanGesture_);
    ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);

    ScrollModelNG::SetScrollEnabled(frameNode_.GetRawPtr(), false);
    FlushUITasks(frameNode_);
    res.clear();
    link.clear();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    EXPECT_NE(*link.begin(), controller->freePanGesture_);
    EXPECT_NE(*res.begin(), controller->freePanGesture_);
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

    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -DELTA_X);
    EXPECT_EQ(GetChildY(frameNode_, 0), -DELTA_Y);
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

    FlushUITasks(frameNode_);
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
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), controller->freePanGesture_);
    EXPECT_EQ(*res.begin(), controller->freePanGesture_);
    ASSERT_TRUE(controller->freePanGesture_->onActionUpdate_);

    res.clear();
    link.clear();

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    ASSERT_FALSE(pattern_->freeScroll_);
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
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
 * @tc.name: Animation001
 * @tc.desc: Test normal animation with Axis::FREE
 * @tc.type: FUNC
 */
TEST_F(FreeScrollTest, Animation001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    PanStart({});
    PanUpdate({ DELTA_X, DELTA_Y });
    FlushUITasks(frameNode_);
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
    EXPECT_EQ(controller->state_, ScrollState::IDLE);
    PanStart({});
    PanUpdate({ -DELTA_X, DELTA_Y });
    EXPECT_EQ(controller->state_, ScrollState::SCROLL);
    FlushUITasks(frameNode_);
    PanEnd({ -DELTA_X, DELTA_Y }, { -VELOCITY_X, VELOCITY_Y });
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, ScrollState::FLING);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    ASSERT_TRUE(pattern_->freeScroll_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -DELTA_X - VELOCITY_X / pattern_->freeScroll_->friction_);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, ScrollState::IDLE);
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
    FlushUITasks(frameNode_);
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
    EXPECT_EQ(controller->state_, ScrollState::FLING);

    TouchDown();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, ScrollState::IDLE);
    TouchUp();
    EXPECT_EQ(controller->state_, ScrollState::FLING);
    EXPECT_FALSE(MockAnimationManager::GetInstance().AllFinished());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0, 0));
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
    EXPECT_EQ(controller->state_, ScrollState::IDLE);
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
    FlushUITasks(frameNode_);
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
    FlushUITasks(frameNode_);
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
    EXPECT_EQ(pattern_->freeScroll_->state_, ScrollState::IDLE);
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

    scroller->ScrollBy(-DELTA_X, -DELTA_Y, false);
    FlushUITasks();
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(-CONTENT_W + WIDTH + DELTA_X, -CONTENT_H + HEIGHT + DELTA_Y));
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
    EXPECT_EQ(scrollBar->vertical_.GetActiveRect().ToString(), "Rect (236.00, 0.00) - [4.00 x 80.00]");
    EXPECT_EQ(scrollBar->horizontal_.GetActiveRect().ToString(), "Rect (0.00, 396.00) - [28.80 x 4.00]");
    EXPECT_EQ(scrollBar->vertical_.GetActiveWidth(), NORMAL_BAR_WIDTH * 2);
    EXPECT_EQ(scrollBar->horizontal_.GetActiveWidth(), NORMAL_BAR_WIDTH * 2);
    EXPECT_EQ(scrollBar->vertical_.GetTouchRegion().ToString(), "Rect (208.00, 0.00) - [32.00 x 80.00]");
    EXPECT_EQ(scrollBar->vertical_.GetNormalWidth(), NORMAL_BAR_WIDTH);

    const Dimension NEW_BAR_WIDTH = 10.0_vp;
    ScrollModelNG::SetScrollBarWidth(frameNode_.GetRawPtr(), NEW_BAR_WIDTH);
    pattern_->OnModifyDone();
    EXPECT_EQ(scrollBar->vertical_.GetNormalWidth(), NEW_BAR_WIDTH);

    ASSERT_TRUE(scrollBar->painter_);
    EXPECT_EQ(scrollBar->painter_->vertical_.GetHoverAnimatingType(), HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->painter_->horizontal_.GetBarColor()->Get().ToString(), "#66182431");
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
    EXPECT_EQ(scrollBar->vertical_.GetActiveRect().ToString(), "Rect (236.00, 320.00) - [4.00 x 80.00]");
    EXPECT_EQ(scrollBar->horizontal_.GetActiveRect().ToString(), "Rect (211.20, 396.00) - [28.80 x 4.00]");

    ScrollModelNG::SetScrollBarColor(frameNode_.GetRawPtr(), Color::BLUE);
    pattern_->OnModifyDone();
    FlushUITasks(frameNode_);
    EXPECT_EQ(scrollBar->painter_->horizontal_.GetBarColor()->Get(), Color::BLUE);
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
    EXPECT_EQ(pattern_->scrollBar2d_->painter_->vertical_.GetOpacity(), UINT8_MAX);

    ScrollModelNG::SetScrollBar(frameNode_.GetRawPtr(), DisplayMode::OFF);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->scrollBar2d_->vertical_.GetDisplayMode(), DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar2d_->horizontal_.GetDisplayMode(), DisplayMode::OFF);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->scrollBar2d_->painter_->horizontal_.GetOpacity(), 0);
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
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(responseLinkResult.size(), 2);

    localPoint = PointF(238, 5);
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(responseLinkResult.size(), 3);
    EXPECT_EQ(responseLinkResult.front(), pattern_->scrollBar2d_->vertical_.GetPanRecognizer());

    constexpr int32_t expectedRecognizerCount = 3; // 2 from scrollBars, 1 from pan recognizer
    localPoint = PointF(1, 398);
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(responseLinkResult.size(), expectedRecognizerCount);
    EXPECT_EQ(*std::next(responseLinkResult.begin()), pattern_->scrollBar2d_->horizontal_.GetPanRecognizer());

    TouchRestrict restrict;
    restrict.sourceType = SourceType::MOUSE;
    result.clear();
    responseLinkResult.clear();
    actuator->CollectTouchTarget({}, {}, {}, result, localPoint, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(responseLinkResult.size(), expectedRecognizerCount);
    EXPECT_EQ(*std::next(responseLinkResult.begin()), pattern_->scrollBar2d_->horizontal_.GetPanRecognizer());
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
} // namespace OHOS::Ace::NG
