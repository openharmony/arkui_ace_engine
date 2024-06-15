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
#include "base/log/dump_log.h"


namespace OHOS::Ace::NG {
namespace {
constexpr float BAR_WIDTH = 10.f;
} // namespace

class ScrollBarTestNg : public ScrollTestNg {
public:
    void CreateWithBar();
    void ClickBar(Offset point);
    void UpdateOverlayModifier(RefPtr<PaintWrapper> paintWrapper);
    void onDraw(RefPtr<PaintWrapper> paintWrapper, bool needDraw = true);
};

void ScrollBarTestNg::CreateWithBar()
{
    ScrollModelNG model = CreateScroll();
    model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
    model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    scrollBar_ = pattern_->GetScrollBar();
}

void ScrollBarTestNg::ClickBar(Offset point)
{
    GestureEvent info;
    info.SetLocalLocation(point);
    pattern_->HandleClickEvent(info); // will trigger CheckBarDirection
}

void ScrollBarTestNg::UpdateOverlayModifier(RefPtr<PaintWrapper> paintWrapper)
{
    auto paintMethod = AceType::DynamicCast<ScrollPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

void ScrollBarTestNg::onDraw(RefPtr<PaintWrapper> paintWrapper, bool needDraw)
{
    auto paintMethod = AceType::DynamicCast<ScrollPaintMethod>(paintWrapper->nodePaintImpl_);
    auto modifier = paintMethod->GetOverlayModifier(nullptr);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    Testing::MockCanvas canvas;
    // if has barWidth and barHeight, need draw bar
    if (needDraw) {
        EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
        EXPECT_CALL(canvas, AttachBrush).WillOnce(ReturnRef(canvas));
        EXPECT_CALL(canvas, DetachBrush).WillOnce(ReturnRef(canvas));
    } else {
        EXPECT_CALL(canvas, DrawRoundRect(_)).Times(0);
    }
    DrawingContext drawingContext = { canvas, SCROLL_WIDTH, SCROLL_HEIGHT };
    UpdateOverlayModifier(paintWrapper);
    scrollBarOverlayModifier->onDraw(drawingContext);
}

/**
 * @tc.name: ClickBar001
 * @tc.desc: Test CheckBarDirection by HandleClickEvent, component will scroll by click bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ClickBar001, TestSize.Level1)
{
    CreateWithBar();
    EXPECT_TRUE(IsEqual(scrollBar_->GetTouchRegion(),
        Rect(SCROLL_WIDTH - BAR_WIDTH, 0.f, BAR_WIDTH, SCROLL_HEIGHT * VIEW_ITEM_NUMBER / TOTAL_ITEM_NUMBER)));
    const float pointInBarX = scrollBar_->GetTouchRegion().Left() + BAR_WIDTH / 2;
    pattern_->isMousePressed_ = true;

    /**
     * @tc.steps: step1. Click not in bar
     * @tc.expected: Not scroll
     */
    ClickBar(Offset::Zero());
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));

    /**
     * @tc.steps: step2. Click in bar
     * @tc.expected: Not scroll
     */
    ClickBar(Offset(pointInBarX, 10.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));

    /**
     * @tc.steps: step3. Click below bar
     * @tc.expected: Scroll page down
     */
    ClickBar(Offset(pointInBarX, 700.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, SCROLL_HEIGHT)); // 800.f

    /**
     * @tc.steps: step4. Scroll down and Click above bar
     * @tc.expected: Scroll page up
     */
    ScrollTo(ITEM_HEIGHT);
    ClickBar(Offset(pointInBarX, 1.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, ITEM_HEIGHT - SCROLL_HEIGHT)); // -700.f
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, HandleLongPress001, TestSize.Level1)
{
    CreateWithBar();
    auto scrollBar = pattern_->GetScrollBar();
    const float pointInBarX = scrollBar->GetTouchRegion().Left() + BAR_WIDTH / 2;

    /**
     * @tc.steps: step1. LongPress not in bar
     * @tc.expected: Not scroll
     */
    Mouse(Offset::Zero(), MouseButton::LEFT_BUTTON, MouseAction::PRESS);
    scrollBar->HandleLongPress(false);
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));

    /**
     * @tc.steps: step2. LongPress in bar
     * @tc.expected: Not scroll
     */
    Mouse(Offset(pointInBarX, 10.f), MouseButton::LEFT_BUTTON, MouseAction::PRESS);
    scrollBar->HandleLongPress(false);
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Test handleDrag
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, HandleDrag001, TestSize.Level1)
{
    CreateWithBar();
    auto HandleDragStart = *(scrollBar_->panRecognizer_->onActionStart_);
    auto HandleDragUpdate = *(scrollBar_->panRecognizer_->onActionUpdate_);
    auto HandleDragEnd = *(scrollBar_->panRecognizer_->onActionEnd_);

    /**
     * @tc.steps: step1. HandleDrag with Velocity
     * @tc.expected: PlayMotion
     */
    GestureEvent info;
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);

    HandleDragUpdate(info);
    info.SetMainVelocity(1000.f);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsRunning());

    /**
     * @tc.steps: step2. HandleDrag with Velocity again
     * @tc.expected: trigger ProcessFrictionMotion and PlayMotion
     */
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);

    HandleDragUpdate(info);
    info.SetMainVelocity(1000.f);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsRunning());
    scrollBar_->ProcessFrictionMotion(10.f);
    EXPECT_EQ(scrollBar_->frictionPosition_, 10.f);

    /**
     * @tc.steps: step3. HandleDragStart with Velocity:0 or InputEventType::AXIS
     * @tc.expected: Not PlayMotion
     */
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());

    HandleDragUpdate(info);
    info.SetMainVelocity(0.f);
    HandleDragEnd(info);
    EXPECT_FALSE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());

    info.SetMainVelocity(1000.f);
    info.SetInputEventType(InputEventType::AXIS);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());
}

/**
 * @tc.name: OnCollectTouchTarget001
 * @tc.desc: Test OnCollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, OnCollectTouchTarget001, TestSize.Level1)
{
    CreateWithBar();
    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    TouchTestResult responseLinkResult;
    pattern_->scrollableEvent_->BarCollectTouchTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, HandleDragUpdate001, TestSize.Level1)
{
    CreateWithBar();
    GestureEvent info;
    info.SetMainDelta(10);
    scrollBar_->SetReverse(false);
    scrollBar_->HandleDragUpdate(info);
    EXPECT_EQ(info.GetMainDelta(), 10);
    scrollBar_->SetReverse(true);
    scrollBar_->HandleDragUpdate(info);
    EXPECT_NE(info.GetMainDelta(), -100);
}

/**
 * @tc.name: TouchScrollBarEffect001
 * @tc.desc: Test Touch ScrollBar Effect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, TouchScrollBarEffect001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();
    const Offset downInBar = Offset(SCROLL_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(SCROLL_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;

    /**
     * @tc.steps: step1. TouchDown the scrollBar
     * @tc.expected: Show active effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_ACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step2. TouchMove the scrollBar
     * @tc.expected: Show active effect
     */
    Touch(TouchType::DOWN, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_ACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::APPEAR);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. TouchUp the scrollBar
     * @tc.expected: Show inActive effect
     */
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_INACTIVE_WIDTH);
    scrollBar->ScheduleDisappearDelayTask(); // delayed task
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::DISAPPEAR);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Test onDraw func
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, onDraw001, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();

    /**
     * @tc.steps: step1. Has barWidth and barHeight
     * @tc.expected: Draw ScrollBar
     */
    onDraw(paintWrapper);

    /**
     * @tc.steps: step2. No barWidth
     * @tc.expected: No Draw ScrollBar
     */
    scrollBar->SetNormalWidth(Dimension(0));
    onDraw(paintWrapper, false);

    /**
     * @tc.steps: step3. No barHeight
     * @tc.expected: No Draw ScrollBar
     */
    scrollBar->SetNormalWidth(Dimension(10.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(0.f));
    FlushLayoutTask(frameNode_);
    onDraw(paintWrapper, false);
}

/**
 * @tc.name: Position001
 * @tc.desc: Test scrollBar position in diff Axis
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, Position001, TestSize.Level1)
{
    const float barWidth = 10.f;
    const float ratio = static_cast<float>(VIEW_ITEM_NUMBER) / TOTAL_ITEM_NUMBER;
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarWidth(Dimension(barWidth));
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto paintMethod = AceType::DynamicCast<ScrollPaintMethod>(paintWrapper->nodePaintImpl_);
    auto scrollBar = pattern_->GetScrollBar();
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();

    /**
     * @tc.steps: step1. Axis::VERTICAL
     * @tc.expected: ScrollBar at RIGHT
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);
    Rect expectRect = Rect(SCROLL_WIDTH - barWidth, 0.f, barWidth, SCROLL_HEIGHT * ratio);
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, expectRect));

    /**
     * @tc.steps: step2. Scroll some distance in VERTICAL
     * @tc.expected: The ScrollBar touchRegion_ offset has changed
     */
    ScrollTo(ITEM_HEIGHT);
    expectRect.SetTop(ITEM_HEIGHT * ratio);
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, expectRect));

    /**
     * @tc.steps: step3. Change direction to Axis::HORIZONTAL
     * @tc.expected: ScrollBar at BOTTOM
     */
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent(TOTAL_ITEM_NUMBER);
    paintWrapper = CreateDone(frameNode_);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);
    expectRect = Rect(0.f, SCROLL_HEIGHT - barWidth, SCROLL_WIDTH * ratio, barWidth);
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, expectRect));

    /**
     * @tc.steps: step4. Scroll some distance in HORIZONTAL
     * @tc.expected: The ScrollBar touchRegion_ offset has changed
     */
    ScrollTo(ITEM_WIDTH);
    expectRect.SetLeft(ITEM_WIDTH * ratio);
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, expectRect));

    /**
     * @tc.steps: step5. Change PositionMode to RIGHT
     * @tc.expected: ScrollBar at RIGHT
     */
    scrollBar->SetPositionMode(PositionMode::RIGHT);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);
}

/**
 * @tc.name: Opacity001
 * @tc.desc: Test ScrollBar Opacity Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, Opacity001, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();

    /**
     * @tc.steps: step1. DisplayMode::AUTO
     * @tc.expected: scrollBar is default hide
     */
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 0);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. DisplayMode::ON
     * @tc.expected: Always show scrollBar
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::ON);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.On");
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step3. DisplayMode::OFF
     * @tc.expected: No scrollBar
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::OFF);
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");
    EXPECT_EQ(pattern_->scrollBar_, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), 0);
}

/**
 * @tc.name: AdaptAnimation001
 * @tc.desc: Test ScrollBar Adapt Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, AdaptAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();
    auto scrollBarOverlayModifier = pattern_->GetScrollBarOverlayModifier();

    /**
     * @tc.steps: step1. Change Scroll height.
     * @tc.expected: The ScrollBar heigth self-adapt
     */
    scrollBarOverlayModifier->StopAdaptAnimation();
    EXPECT_EQ(scrollBarOverlayModifier->adaptAnimation_, nullptr);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SCROLL_HEIGHT - 10.f));
    FlushLayoutTask(frameNode_);
    UpdateOverlayModifier(paintWrapper);
    EXPECT_TRUE(scrollBar->needAdaptAnimation_);
    scrollBarOverlayModifier->StopAdaptAnimation();
    EXPECT_NE(scrollBarOverlayModifier->adaptAnimation_, nullptr);
}

/**
 * @tc.name: ScrollBar001
 * @tc.desc: Test UpdateScrollBarRegion function in ScrollBar under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When the ShapeMode is RECT and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step1. Check whether relevant parameters are correct.
     */
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    ASSERT_NE(scrollBar, nullptr);
    scrollBar->shapeMode_ = ShapeMode::RECT;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    auto barRect = Rect(0.0, 0.0, NORMAL_WIDTH, 100.0) + Offset::Zero();
    EXPECT_TRUE(IsEqual(scrollBar->barRect_, barRect));
    EXPECT_TRUE(IsEqual(scrollBar->activeRect_, Rect(0.0, -9900.0, NORMAL_WIDTH, 10000.0)));
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, Rect(0.0, -9900.0, NORMAL_WIDTH + DEFAULT_TOUCH_WIDTH, 10000.0)));

    /**
     * @tc.steps: step2. When the ShapeMode is RECT and DisplayMode is BOTTOM, verify the UpdateScrollBarRegion
     *            function.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::BOTTOM;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    barRect = Rect(0.0, 100.0 - NORMAL_WIDTH, 100.0, NORMAL_WIDTH) + Offset::Zero();
    EXPECT_TRUE(IsEqual(scrollBar->barRect_, barRect));
    EXPECT_TRUE(IsEqual(scrollBar->activeRect_, Rect(-9899.0, 100.0 - NORMAL_WIDTH, 9999.0, NORMAL_WIDTH)));
    EXPECT_TRUE(IsEqual(
        scrollBar->touchRegion_, Rect(-9899.0, 100.0 - DEFAULT_TOUCH_WIDTH, 9999.0, DEFAULT_TOUCH_WIDTH)));

    /**
     * @tc.steps: step3. When the ShapeMode is RECT and DisplayMode is RIGHT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    barRect = Rect(100.0 - NORMAL_WIDTH, 0.0, NORMAL_WIDTH, 100.0) + Offset::Zero();
    EXPECT_TRUE(IsEqual(scrollBar->barRect_, barRect));
    EXPECT_TRUE(IsEqual(scrollBar->activeRect_, Rect(100.0 - NORMAL_WIDTH, -9899.0, NORMAL_WIDTH, 9999.0)));
    EXPECT_TRUE(IsEqual(
        scrollBar->touchRegion_, Rect(100.0 - DEFAULT_TOUCH_WIDTH, -9899.0, DEFAULT_TOUCH_WIDTH, 9999.0)));

    /**
     * @tc.steps: step4. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->shapeMode_ = ShapeMode::ROUND;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 150);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -6000);

    /**
     * @tc.steps: step5. When the ShapeMode is ROUND and DisplayMode is RIGHT, verify the UpdateScrollBarRegion
     *                   function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 30);
    EXPECT_EQ(scrollBar->trickSweepAngle_, 6000);

    /**
     * @tc.steps: step6. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->bottomAngle_ = 50.f;
    scrollBar->topAngle_ = 100.0;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(100.0, 100.0), Offset(1.f, 1.f), 200.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, -155);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -10);
}

/**
 * @tc.name: ScrollBar002
 * @tc.desc: Test SetGestureEvent() / SetMouseEvent() / SetHoverEvent()
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar002, TestSize.Level1)
{
    // pattern_->GetScrollBar()->touchRegion_ == Rect (710.00, 0.00) - [10.00 x 946.67]
    const float barWidth = 10.f;
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarWidth(Dimension(barWidth));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();
    const Offset downInBar = Offset(SCROLL_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(SCROLL_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;
    const Offset upOutBar = Offset(SCROLL_WIDTH - barWidth - 1.f, 10.f);

    /**
     * @tc.steps: step1. Touch in bar
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step2. Touch in bar and up out of bar
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upOutBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step3. Touch in bar with SourceType::MOUSE
     * @tc.expected: touchAnimator_ is take effect
     */
    Touch(TouchType::DOWN, downInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::MOUSE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::MOUSE);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step4. Touch in bar with SourceType::TOUCH_PAD
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH_PAD);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step5. Touch out of bar
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Touch(TouchType::DOWN, Offset::Zero(), SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step6. Touch in bar and scrollBar->IsHover() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::MOVE, moveInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsPressed());
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsPressed());

    /**
     * @tc.steps: step7. Mouse in bar and move out of bar (out->in->in->out)
     * @tc.expected: touchAnimator_ is take effect
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetScrollBarWidth(Dimension(barWidth));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    scrollBar = pattern_->GetScrollBar();
    const Offset moveOutBar = Offset(SCROLL_WIDTH - barWidth - 1.f, 0.f);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    EXPECT_TRUE(scrollBar->IsHover());
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    Mouse(moveInBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsHover());

    /**
     * @tc.steps: step8. (out->in->in->out) and scrollBar->IsPressed() is true
     * @tc.expected: touchAnimator_ is not take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetPressed(true);
    Mouse(moveOutBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());
    Mouse(moveInBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveInBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_TRUE(scrollBar->IsHover());
    Mouse(moveOutBar);
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    EXPECT_FALSE(scrollBar->IsHover());

    /**
     * @tc.steps: step9. Mouse in bar and move out of component containing bar
     * @tc.expected: HoverAnimation is take effect
     */
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    Hover(true);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(false);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    scrollBar->SetPressed(true);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    scrollBar->SetHover(true);
    scrollBar->SetPressed(false);
    Hover(false);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    EXPECT_FALSE(scrollBar->IsHover());
}

/**
 * @tc.name: ScrollBar004
 * @tc.desc: Test ScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar004, TestSize.Level1)
{
    const float barWidth = 10.f;
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarWidth(Dimension(barWidth));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarRectRegion(Point(0, 0)));
    scrollBar->FlushBarWidth();

    scrollBar->SetDisplayMode(DisplayMode::OFF);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(Point(0, 0)));
    EXPECT_FALSE(scrollBar->InBarRectRegion(Point(0, 0)));

    scrollBar->SetPositionMode(PositionMode::LEFT);
    scrollBar->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar->touchRegion_.Height(), 20.f);
    scrollBar->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar->touchRegion_.Top(), 30.f);

    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar->touchRegion_.Width(), 20.f);
    scrollBar->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar->touchRegion_.Left(), 30.f);

    scrollBar->SetPositionMode(PositionMode::RIGHT);
    scrollBar->UpdateActiveRectSize(20.f);
    EXPECT_EQ(scrollBar->touchRegion_.Width(), 20.f);
    scrollBar->UpdateActiveRectOffset(30.f);
    EXPECT_EQ(scrollBar->touchRegion_.Left(), 30.f);
}

/**
 * @tc.name: ScrollBar005
 * @tc.desc: Test CalcReservedHeight()
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar005, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto scrollBar = pattern_->GetScrollBar();

    scrollBar->SetPositionMode(PositionMode::LEFT);
    scrollBar->SetNormalWidth(Dimension(1)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->endReservedHeight_.Value(), 0);

    BorderRadiusProperty borderRadiusProperty;
    float radius = 13.f;
    borderRadiusProperty.radiusTopRight = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar->SetHostBorderRadius(borderRadiusProperty);
    scrollBar->SetPadding(Edge(1, 1, 1, 1));
    scrollBar->SetPositionMode(PositionMode::RIGHT);
    scrollBar->SetNormalWidth(Dimension(2)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_.ConvertToPx(), 14.5);
    EXPECT_EQ(scrollBar->endReservedHeight_.ConvertToPx(), 14.5);

    borderRadiusProperty.radiusBottomLeft = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar->SetHostBorderRadius(borderRadiusProperty);
    scrollBar->SetPadding(Edge(1, 1, 1, 1));
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->SetNormalWidth(Dimension(6)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_.ConvertToPx(), 11.25);
    EXPECT_EQ(scrollBar->endReservedHeight_.ConvertToPx(), 11.25);
}

/**
 * @tc.name: ScrollBarWidth001
 * @tc.desc: Test scrollbar width
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set bar width
     * @tc.expected: It will be default
     */
    ScrollModelNG model = CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step2. Set bar width less than bar height
     * @tc.expected: It will be the value that was set
     */
    model = CreateScroll();
    model.SetScrollBarWidth(Dimension(10));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), 10);

    /**
     * @tc.steps: step3. Set bar width greater than SCROLL_HEIGHT
     * @tc.expected: It will be default
     */
    model = CreateScroll();
    model.SetScrollBarWidth(Dimension(SCROLL_HEIGHT + 1));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step4. Set bar width greater than SCROLL_HEIGHT
     * @tc.expected: The bar width will be the value that was set, and bar height will be equal to bar width
     */
    model = CreateScroll();
    model.SetScrollBarWidth(Dimension(SCROLL_HEIGHT - 1));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), SCROLL_HEIGHT - 1);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Height(), SCROLL_HEIGHT - 1);
}

/**
 * @tc.name: ScrollBar007
 * @tc.desc: when IsPressed is true, can not trigger scrollstart event
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar007, TestSize.Level1)
{
    bool isTrigger = false;
    ScrollModelNG model = CreateScroll();
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollStart(std::move(event));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. when scrollbar IsPressed() is false
     * @tc.expected: can trigger snap scrollstart event
     */
    auto scrollBar = pattern_->GetScrollBar();
    pattern_->ScrollTo(5.f);
    pattern_->scrollableEvent_ = nullptr; // make ScrollableIdle() true
    scrollBar->SetPressed(false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: ScrollBar008
 * @tc.desc: when IsPressed is false, can trigger scrollstart event
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar008, TestSize.Level1)
{
    bool isTrigger = false;
    ScrollModelNG model = CreateScroll();
    Dimension intervalSize = Dimension(10.f);
    std::vector<Dimension> snapPaginations = {
        Dimension(10.f),
        Dimension(20.f),
        Dimension(30.f),
    };
    std::pair<bool, bool> enableSnapToSide = { true, true };
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    OnScrollStartEvent event = [&isTrigger]() { isTrigger = true; };
    model.SetOnScrollStart(std::move(event));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. when scrollbar IsPressed() is true
     * @tc.expected: can not trigger snap scrollstart event
     */
    auto scrollBar = pattern_->GetScrollBar();
    pattern_->ScrollTo(5.f);
    pattern_->scrollableEvent_ = nullptr; // make ScrollableIdle() true
    scrollBar->SetPressed(true);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: ScrollBar009
 * @tc.desc: Test scrollbar width.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBar009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model and set the width, height
     * @tc.expected: Check the scrollBar property value.
     */
    ScrollModelNG model = CreateScroll();
    model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    pattern_->CreateScrollBarOverlayModifier();
    auto barRect = scrollBar->GetBarRect();
    auto activeRect = scrollBar->GetActiveRect();
    EXPECT_FLOAT_EQ(barRect.x_ + barRect.width_, SCROLL_WIDTH);
    EXPECT_FLOAT_EQ(activeRect.x_ + activeRect.width_, SCROLL_WIDTH);
    EXPECT_FLOAT_EQ(barRect.height_, SCROLL_HEIGHT);

    /**
     * @tc.steps: step1.set the width
     * @tc.expected: Check the scrollBar property value.
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(300.f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(500.f));
    FlushLayoutTask(frameNode_);

    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->layoutAlgorithm_->SetNeedMeasure();
    layoutWrapper->layoutAlgorithm_->SetNeedLayout();
    auto layoutAlgorithm = AceType::MakeRefPtr<ScrollLayoutAlgorithm>(pattern_->currentOffset_);
    layoutWrapper->layoutAlgorithm_->SetLayoutAlgorithm(layoutAlgorithm);
    auto childLayoutConstraint = layoutProperty_->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = { 300.f, 625.0f };
    auto colNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(colNode, nullptr);
    RefPtr<LayoutWrapperNode> colLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(colNode, colNode->GetGeometryNode(), colNode->GetLayoutProperty());
    colLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    colLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(300.f), CalcLength(62.5f)));
    layoutWrapper->AppendChild(colLayoutWrapper);

    DirtySwapConfig config;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    auto paint = AceType::MakeRefPtr<ScrollPaintMethod>();
    paint->SetScrollBar(scrollBar);
    paint->SetScrollBarOverlayModifier(pattern_->GetScrollBarOverlayModifier());
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    paint->UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));

    barRect = scrollBar->GetBarRect();
    activeRect = scrollBar->GetActiveRect();
    EXPECT_FLOAT_EQ(barRect.x_ + barRect.width_, 300.f);
    EXPECT_FLOAT_EQ(activeRect.x_ + activeRect.width_, 300.f);
    EXPECT_FLOAT_EQ(barRect.height_, 500.f);
    EXPECT_FLOAT_EQ(pattern_->scrollBarOverlayModifier_->barX_->Get(), 296.f);
}

/**
 * @tc.name: AttrScrollBarColorWidth001
 * @tc.desc: Test attribute about scrollBarColor/scrollBarWidth,
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, AttrScrollBarColorWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: [color:foregroundColor_, width: 4]
     */
    CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    EXPECT_EQ(paintProperty_->GetBarColor(), scrollBarTheme->GetForegroundColor());
    EXPECT_EQ(paintProperty_->GetBarWidth(), scrollBarTheme->GetNormalWidth());

    /**
     * @tc.steps: step2. Text set value: Color::RED
     */
    ScrollModelNG model = CreateScroll();
    model.SetScrollBarColor(Color::RED);
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(paintProperty_->GetBarColor(), Color::RED);

    /**
     * @tc.steps: step3. Text set width value: Dimension(10)
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetScrollBarWidth(Dimension(10));
    CreateContent(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(paintProperty_->GetBarWidth(), Dimension(10));
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test DumpAdvanceInfo001
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    auto scrollBar = pattern_->GetScrollBar();

    scrollBar->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[7], "shapeMode: RECT\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[8], "positionMode: RIGHT\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[10], "axis: VERTICAL\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[11], "panDirection: VERTICAL\n");

    DumpLog::GetInstance().description_.clear();
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    scrollBar->SetPositionMode(PositionMode::LEFT);
    scrollBar->SetAxis(Axis::NONE);
    PanDirection panDirection;
    panDirection.type = 0;
    scrollBar->panRecognizer_->direction_ = panDirection;
    scrollBar->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[7], "shapeMode: ROUND\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[8], "positionMode: LEFT\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[10], "axis: NONE\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[11], "panDirection: NONE\n");

    DumpLog::GetInstance().description_.clear();
    scrollBar->SetShapeMode(ShapeMode::DEFAULT);
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->SetAxis(Axis::HORIZONTAL);
    panDirection.type = 3;
    scrollBar->panRecognizer_->direction_ = panDirection;
    scrollBar->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[7], "shapeMode: DEFAULT\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[8], "positionMode: BOTTOM\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[10], "axis: HORIZONTAL\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[11], "panDirection: HORIZONTAL\n");

    DumpLog::GetInstance().description_.clear();
    scrollBar->SetAxis(Axis::FREE);
    panDirection.type = 15;
    scrollBar->panRecognizer_->direction_ = panDirection;
    scrollBar->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[10], "axis: FREE\n");
    EXPECT_EQ(DumpLog::GetInstance().description_[11], "panDirection: FREE\n");

    DumpLog::GetInstance().description_.clear();
    scrollBar->panRecognizer_ = nullptr;
    scrollBar->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_[11], "panDirection is null\n");
}
} // namespace OHOS::Ace::NG
