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
namespace {
constexpr float BAR_WIDTH = 10.f;
} // namespace

class ScrolleBarTestNg : public ScrollTestNg {
public:
    void CreateWithBar();
    void ClickBar(Offset point);
};

void ScrolleBarTestNg::CreateWithBar()
{
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    });
    scrollBar_ = pattern_->GetScrollBar();
}

void ScrolleBarTestNg::ClickBar(Offset point)
{
    GestureEvent info;
    info.SetLocalLocation(point);
    pattern_->HandleClickEvent(info); // will trigger CheckBarDirection
}

/**
 * @tc.name: ClickBar001
 * @tc.desc: Test CheckBarDirection by HandleClickEvent, component will scroll by click bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ClickBar001, TestSize.Level1)
{
    CreateWithBar();
    EXPECT_TRUE(IsEqual(scrollBar_->GetTouchRegion(), Rect(470.f, 0.f, 10.f, 640.f)));
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
 * @tc.name: HandleDrag001
 * @tc.desc: Test handleDrag
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, HandleDrag001, TestSize.Level1)
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
HWTEST_F(ScrolleBarTestNg, OnCollectTouchTarget001, TestSize.Level1)
{
    CreateWithBar();
    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    pattern_->scrollableEvent_->BarCollectTouchTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode_, nullptr);
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, HandleDragUpdate001, TestSize.Level1)
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
 * @tc.name: ScrollBarAnimation001
 * @tc.desc: Test ScrollBar Hover Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBarAnimation001, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    const Offset downInBar = Offset(SCROLL_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(SCROLL_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;

    /**
     * @tc.steps: step1. Axis::NONE
     * @tc.expected: scrollBar->NeedPaint() is false and scrollBarOverlayModifier is nullptr.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    EXPECT_FALSE(scrollBar->NeedPaint());
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    EXPECT_EQ(scrollBarOverlayModifier, nullptr);

    /**
     * @tc.steps: step2. Axis::Vertical, test grow animation.
     * @tc.expected: scrollBarOverlayModifier->hoverAnimatingType_ is HoverAnimationType::GROW and the width of.
     * scrollBar is DEFAULT_ACTIVE_WIDTH
     */
    CreateWithContent();
    paint = pattern_->CreateNodePaintMethod();
    scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    scrollBar = scrollPaint->scrollBar_.Upgrade();
    scrollBar->SetTouchWidth(Dimension(DEFAULT_TOUCH_WIDTH, DimensionUnit::VP));
    scrollBar->SetActiveWidth(Dimension(DEFAULT_ACTIVE_WIDTH, DimensionUnit::VP));
    scrollBar->SetInactiveWidth(Dimension(DEFAULT_INACTIVE_WIDTH, DimensionUnit::VP));
    scrollBar->SetNormalWidth(Dimension(DEFAULT_NORMAL_WIDTH, DimensionUnit::VP));
    EXPECT_TRUE(scrollBar->NeedPaint());
    modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    EXPECT_CALL(canvas, AttachBrush).WillOnce(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush).WillOnce(ReturnRef(canvas));
    DrawingContext drawingContext = { canvas, SCROLL_WIDTH, SCROLL_HEIGHT };
    scrollBarOverlayModifier->onDraw(drawingContext);
    Touch(TouchType::DOWN, downInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::GROW);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->hoverAnimatingType_, HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_ACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step3. Axis::Vertical, test shrink animation.
     * @tc.expected: scrollBarOverlayModifier->hoverAnimatingType_ is HoverAnimationType::SHRINK and the width of
     * scrollBar is DEFAULT_INACTIVE_WIDTH.
     */
    Touch(TouchType::UP, upInBar, SourceType::TOUCH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::SHRINK);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->hoverAnimatingType_, HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetActiveRect().Width(), DEFAULT_INACTIVE_WIDTH);
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
}

/**
 * @tc.name: ScrollBarAnimation002
 * @tc.desc: Test ScrollBar Opacity Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBarAnimation002, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    /**
     * @tc.steps: step1. DisplayMode::ON
     * @tc.expected: the opacity of scrollBarOverlayModifier is UINT8_MAX and opacityAnimatingType_ is
     * OpacityAnimationType::NONE.
     */
    CreateWithContent();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::ON);
    EXPECT_TRUE(scrollBar->NeedPaint());
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->GetOpacity(), UINT8_MAX);
    EXPECT_NE(scrollBarOverlayModifier->opacityAnimation_, nullptr);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. DisplayMode::AUTO
     * @tc.expected: opacityAnimatingType_ is OpacityAnimationType::NONE.
     */
    pattern_->SetScrollBar(DisplayMode::AUTO);
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::AUTO);
    EXPECT_TRUE(scrollBar->NeedPaint());
    ASSERT_NE(scrollBarOverlayModifier, nullptr);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::NONE);

    /**
     * @tc.steps: step3. play appear animation.
     * @tc.expected: opacityAnimatingType_ is OpacityAnimationType::NONE.
     */
    scrollBar->PlayScrollBarAppearAnimation();
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_EQ(scrollBarOverlayModifier->opacityAnimatingType_, OpacityAnimationType::NONE);

    /**
     * @tc.steps: step4. DisplayMode::OFF
     * @tc.expected: scrollBar->NeedPaint() is false.
     */
    pattern_->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(pattern_->scrollBar_, nullptr);
}

/**
 * @tc.name: ScrollBarAnimation003
 * @tc.desc: Test ScrollBar Adapt Animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBarAnimation003, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);

    CreateWithContent();
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto scrollBar = scrollPaint->scrollBar_.Upgrade();
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    pattern_->SetScrollBar(DisplayMode::ON);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_FLOAT_EQ(scrollBar->GetActiveRect().Height(), SCROLL_HEIGHT * VIEW_LINE_NUMBER / TOTAL_LINE_NUMBER);

    /**
     * @tc.steps: step1. change scrollBar height.
     * @tc.expected: scrollBar->needAdaptAnimation_ is true.
     */
    scrollBar->UpdateScrollBarRegion(Offset::Zero(), Size(480.0, 800.0), Offset::Zero(), 1080.0f);
    scrollPaint->UpdateOverlayModifier(&paintWrapper);
    EXPECT_TRUE(NearEqual(scrollBar->GetActiveRect().Height(), 592.592f));
    EXPECT_TRUE(scrollBar->needAdaptAnimation_);
}

/**
 * @tc.name: ScrollBarAnimation004
 * @tc.desc: Test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBarAnimation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. BarWidth is 0
     * @tc.expected: Not draw bar
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(0.f));
    });
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(0);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    auto paint = pattern_->CreateNodePaintMethod();
    auto scrollPaint = AceType::DynamicCast<ScrollPaintMethod>(paint);
    auto modifier = scrollPaint->GetOverlayModifier(&paintWrapper);
    auto scrollBarOverlayModifier = AceType::DynamicCast<ScrollBarOverlayModifier>(modifier);
    DrawingContext drawingContext = { canvas, SCROLL_WIDTH, SCROLL_HEIGHT };
    scrollBarOverlayModifier->onDraw(drawingContext);

    /**
     * @tc.steps: step1. No scrollBar
     * @tc.expected: Not draw bar
     */
    paintProperty_->UpdateScrollBarMode(DisplayMode::OFF);
    FlushLayoutTask(frameNode_);
    scrollBarOverlayModifier->onDraw(drawingContext);
}

/**
 * @tc.name: ScrollBar001
 * @tc.desc: Test UpdateScrollBarRegion function in ScrollBar under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBar001, TestSize.Level1)
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
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, Rect(0.0, -9900.0, NORMAL_WIDTH, 10000.0)));

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
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, Rect(-9899.0, 100.0, 9999.0, 0.0)));

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
    EXPECT_TRUE(IsEqual(scrollBar->touchRegion_, Rect(100.0, -9899.0, 0.0, 9999.0)));

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
HWTEST_F(ScrolleBarTestNg, ScrollBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Touch in bar
     * @tc.expected: touchAnimator_ is take effect
     */
    // pattern_->GetScrollBar()->touchRegion_ == Rect (710.00, 0.00) - [10.00 x 946.67]
    const float barWidth = 10.f;
    CreateWithContent([barWidth](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(barWidth)); });
    auto scrollBar = pattern_->GetScrollBar();
    const Offset downInBar = Offset(SCROLL_WIDTH - 1.f, 0.f);
    const Offset moveInBar = Offset(SCROLL_WIDTH - 1.f, 10.f);
    const Offset upInBar = moveInBar;
    const Offset upOutBar = Offset(SCROLL_WIDTH - barWidth - 1.f, 10.f);

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
    CreateWithContent([barWidth](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(barWidth)); });
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
 * @tc.name: ScrollBar003
 * @tc.desc: Test bar rect
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBar003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test Bar in VERTICAL
     * @tc.expected: Verify bar rect
     */
    const float barWidth = 10.f;
    const float ratio = static_cast<float>(VIEW_LINE_NUMBER) / TOTAL_LINE_NUMBER;
    CreateWithContent([barWidth](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(barWidth)); });
    auto scrollBar = pattern_->GetScrollBar();

    Rect rect = scrollBar->touchRegion_;
    Rect expectRect = Rect(SCROLL_WIDTH - barWidth, 0.f, barWidth, SCROLL_HEIGHT * ratio);
    EXPECT_TRUE(IsEqual(rect, expectRect));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    rect = scrollBar->touchRegion_;
    expectRect = Rect(SCROLL_WIDTH - barWidth, ITEM_HEIGHT * ratio, barWidth, SCROLL_HEIGHT * ratio);
    EXPECT_TRUE(IsEqual(rect, expectRect));

    /**
     * @tc.steps: step2. Test Bar in HORIZONTAL
     * @tc.expected: Verify bar rect
     */
    CreateWithContent([barWidth](ScrollModelNG model) {
        model.SetAxis(Axis::HORIZONTAL);
        model.SetScrollBarWidth(Dimension(barWidth));
    });
    scrollBar = pattern_->GetScrollBar();

    rect = scrollBar->touchRegion_;
    expectRect = Rect(0.f, SCROLL_HEIGHT - barWidth, SCROLL_WIDTH * ratio, barWidth);
    EXPECT_TRUE(IsEqual(rect, expectRect));

    UpdateCurrentOffset(-ITEM_WIDTH);
    rect = scrollBar->touchRegion_;
    expectRect = Rect(ITEM_WIDTH * ratio, SCROLL_HEIGHT - barWidth, SCROLL_WIDTH * ratio, barWidth);
    EXPECT_TRUE(IsEqual(rect, expectRect));
}

/**
 * @tc.name: ScrollBar004
 * @tc.desc: Test ScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBar004, TestSize.Level1)
{
    const float barWidth = 10.f;
    CreateWithContent([barWidth](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(barWidth)); });
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
HWTEST_F(ScrolleBarTestNg, ScrollBar005, TestSize.Level1)
{
    CreateWithContent();
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
    EXPECT_EQ(scrollBar->startReservedHeight_, Dimension(14.5))
        << "startReservedHeight_: " << scrollBar->startReservedHeight_.ConvertToPx();
    EXPECT_EQ(scrollBar->endReservedHeight_, Dimension(14.5))
        << "endReservedHeight_: " << scrollBar->endReservedHeight_.ConvertToPx();

    borderRadiusProperty.radiusBottomLeft = std::make_optional<Dimension>(radius);
    borderRadiusProperty.radiusBottomRight = std::make_optional<Dimension>(radius);
    scrollBar->SetHostBorderRadius(borderRadiusProperty);
    scrollBar->SetPadding(Edge(1, 1, 1, 1));
    scrollBar->SetPositionMode(PositionMode::BOTTOM);
    scrollBar->SetNormalWidth(Dimension(6)); // call CalcReservedHeight;
    EXPECT_EQ(scrollBar->startReservedHeight_, Dimension(11.25))
        << "startReservedHeight_: " << scrollBar->startReservedHeight_.ConvertToPx();
    EXPECT_EQ(scrollBar->endReservedHeight_, Dimension(11.25))
        << "endReservedHeight_: " << scrollBar->endReservedHeight_.ConvertToPx();
}

/**
 * @tc.name: ScrollBar006
 * @tc.desc: Test scrollbar width
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBar006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set bar width
     * @tc.expected: It will be default
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int>(DisplayMode::ON)); });
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step2. Set bar width less than bar height
     * @tc.expected: It will be the value that was set
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(10));
    });
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), 10);

    /**
     * @tc.steps: step3. Set bar width greater than SCROLL_HEIGHT
     * @tc.expected: It will be default
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(SCROLL_HEIGHT + 1));
    });
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), NORMAL_WIDTH);

    /**
     * @tc.steps: step4. Set bar width greater than SCROLL_HEIGHT
     * @tc.expected: The bar width will be the value that was set, and bar height will be equal to bar width
     */
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(SCROLL_HEIGHT - 1));
    });
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Width(), SCROLL_HEIGHT - 1);
    EXPECT_EQ(pattern_->scrollBar_->activeRect_.Height(), SCROLL_HEIGHT - 1);
}

/**
 * @tc.name: ScrollBar007
 * @tc.desc: when IsPressed is true, can not trigger scrollstart event
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ScrollBar007, TestSize.Level1)
{
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
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
    });

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
HWTEST_F(ScrolleBarTestNg, ScrollBar008, TestSize.Level1)
{
    bool isTrigger = false;
    CreateWithContent([&isTrigger](ScrollModelNG model) {
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
    });

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
HWTEST_F(ScrolleBarTestNg, ScrollBar009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll model and set the width, height
     * @tc.expected: Check the scrollBar property value.
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int32_t>(DisplayMode::ON)); });

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
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test attribute about scrollBar,
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, AttrScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: AUTO
     */
    CreateWithContent();
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Auto");

    /**
     * @tc.steps: step2. Text set value: OFF
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int>(DisplayMode::OFF)); });
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.Off");

    /**
     * @tc.steps: step3. Text set value: ON
     */
    CreateWithContent([](ScrollModelNG model) { model.SetDisplayMode(static_cast<int>(DisplayMode::ON)); });
    EXPECT_EQ(paintProperty_->GetBarStateString(), "BarState.On");
}

/**
 * @tc.name: AttrScrollBarColorWidth001
 * @tc.desc: Test attribute about scrollBarColor/scrollBarWidth,
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, AttrScrollBarColorWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: [color:foregroundColor_, width: 4]
     */
    CreateWithContent();
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    EXPECT_EQ(paintProperty_->GetBarColor(), scrollBarTheme->GetForegroundColor());
    EXPECT_EQ(paintProperty_->GetBarWidth(), scrollBarTheme->GetNormalWidth());

    /**
     * @tc.steps: step2. Text set value: Color::RED
     */
    CreateWithContent([](ScrollModelNG model) { model.SetScrollBarColor(Color::RED); });
    EXPECT_EQ(paintProperty_->GetBarColor(), Color::RED);

    /**
     * @tc.steps: step3. Text set width value: Dimension(10)
     */
    CreateWithContent([](ScrollModelNG model) { model.SetScrollBarWidth(Dimension(10)); });
    EXPECT_EQ(paintProperty_->GetBarWidth(), Dimension(10));
}
} // namespace OHOS::Ace::NG
