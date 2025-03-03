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

#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {
const Point IN_ACTIVE_BAR_POINT = Point(238.f, 80.f);
const Offset IN_ACTIVE_BAR_OFFSET = Offset(238.f, 80.f);
const float VERTICAL_RATIO = HEIGHT / CONTENT_MAIN_SIZE;
const float ARC_LIST_ITER_SCALE = 0.92f;
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color(0XFFFFFF00);

namespace {} // namespace
class ArcScrollBarTestNg : public ScrollTestNg {
public:
    void FlushUITasks(const RefPtr<FrameNode>& frameNode);
    void DragScrollBarStart(GestureEvent& gesture);
    void DragScrollBarUpdate(GestureEvent& gesture);
    void DragScrollBarEnd(GestureEvent& gesture);
    void DragScrollBarAction(Offset startOffset, float dragDelta, float velocity = 0);
};

void ArcScrollBarTestNg::FlushUITasks(const RefPtr<FrameNode>& frameNode)
{
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
}

void ArcScrollBarTestNg::DragScrollBarStart(GestureEvent& gesture)
{
    gesture.SetSourceTool(SourceTool::FINGER);
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    auto HandleDragStart = *(scrollBar_->panRecognizer_->onActionStart_);
    HandleDragStart(gesture);
}

void ArcScrollBarTestNg::DragScrollBarUpdate(GestureEvent& gesture)
{
    float dragDelta = gesture.GetMainDelta();
    Axis axis = ScrollTestNg::pattern_->GetAxis();
    Offset deltaOffset = axis == Axis::VERTICAL ? Offset(0, dragDelta) : Offset(dragDelta, 0);
    gesture.SetGlobalPoint(gesture.GetGlobalPoint() + deltaOffset);
    gesture.SetGlobalLocation(gesture.GetGlobalLocation() + deltaOffset);
    gesture.SetLocalLocation(gesture.GetLocalLocation() + deltaOffset);
    double velocity = dragDelta > 0 ? DRAG_VELOCITY : -DRAG_VELOCITY;
    gesture.SetMainVelocity(velocity);
    auto HandleDragUpdate = *(scrollBar_->panRecognizer_->onActionUpdate_);
    HandleDragUpdate(gesture);
    FlushUITasks(ScrollTestNg::frameNode_);
}

void ArcScrollBarTestNg::DragScrollBarEnd(GestureEvent& gesture)
{
    gesture.SetMainDelta(0);
    gesture.SetGlobalPoint(gesture.GetGlobalPoint());
    gesture.SetGlobalLocation(gesture.GetGlobalLocation());
    gesture.SetLocalLocation(gesture.GetLocalLocation());
    auto HandleDragEnd = *(scrollBar_->panRecognizer_->onActionEnd_);
    HandleDragEnd(gesture);
    FlushUITasks(ScrollTestNg::frameNode_);
}

void ArcScrollBarTestNg::DragScrollBarAction(Offset startOffset, float dragDelta, float velocity)
{
    GestureEvent gesture;
    gesture.SetGlobalPoint(Point() + startOffset);
    gesture.SetGlobalLocation(startOffset);
    gesture.SetLocalLocation(startOffset);
    DragScrollBarStart(gesture);

    gesture.SetMainDelta(dragDelta);
    DragScrollBarUpdate(gesture);

    gesture.SetMainVelocity(velocity);
    DragScrollBarEnd(gesture);
}

/**
 * @tc.name: ArcScrollBarTestNg001
 * @tc.desc: Test handleDrag
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag
     * @tc.expected: Scroll with drag
     */
    float dragDelta = 10;
    DragScrollBarAction(IN_ACTIVE_BAR_OFFSET, dragDelta);
    float expectOffset = -dragDelta / VERTICAL_RATIO;
    EXPECT_TRUE(Position(expectOffset));

    /**
     * @tc.steps: step2. Drag end with velocity
     * @tc.expected: Continue scroll after end
     */
    DragScrollBarAction(IN_ACTIVE_BAR_OFFSET + Offset(0, expectOffset), dragDelta, 10);
    EXPECT_LT(GetChildY(frameNode_, 0), expectOffset * 2);
    EXPECT_LT(ScrollTestNg::pattern_->GetCurrentPosition(), dragDelta * 2);
}

/**
 * @tc.name: ArcScrollBarTestNg002
 * @tc.desc: Test handleDrag in RTL layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag
     * @tc.expected: Scroll with drag
     */
    float dragDelta = 10;
    DragScrollBarAction(Offset(2, 80), dragDelta);
    float expectOffset = -dragDelta / VERTICAL_RATIO;
    EXPECT_TRUE(Position(expectOffset));

    /**
     * @tc.steps: step2. Drag end with velocity
     * @tc.expected: Continue scroll after end
     */
    DragScrollBarAction(Offset(2, 80) + Offset(0, expectOffset), dragDelta, 10);
    EXPECT_LT(GetChildY(ScrollTestNg::frameNode_, 0), expectOffset * 2);
    EXPECT_LT(ScrollTestNg::pattern_->GetCurrentPosition(), dragDelta * 2);
}

/**
 * @tc.name: ArcScrollBarTestNg003
 * @tc.desc: Test InBarTouchRegion/InBarHoverRegion/InBarRectRegion
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg003, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    EXPECT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step1. NeedPaint and ShapeMode::ROUND
     */
    scrollBar->SetDisplayMode(DisplayMode::ON);
    scrollBar->SetShapeMode(ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBar->GetShapeMode(), ShapeMode::ROUND);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar->InBarRectRegion(IN_ACTIVE_BAR_POINT));

    /**
     * @tc.steps: step2. !NeedPaint and ShapeMode::RECT
     */
    scrollBar->SetDisplayMode(DisplayMode::OFF);
    scrollBar->SetShapeMode(ShapeMode::RECT);
    EXPECT_FALSE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBar->GetShapeMode(), ShapeMode::RECT);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar->InBarHoverRegion(IN_ACTIVE_BAR_POINT));
    EXPECT_FALSE(scrollBar->InBarRectRegion(IN_ACTIVE_BAR_POINT));
}

/**
 * @tc.name: ArcScrollBarTestNg004
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg004, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Arc_list at top, call SetBarRegion/SetRoundTrickRegion
     */
    Offset paintOffset_(5, 15);
    Size size { 10, 10 };
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    EXPECT_NE(scrollBar, nullptr);
    scrollBar->SetBarRegion(paintOffset_, size);
    scrollBar->SetRoundTrickRegion(paintOffset_, size, paintOffset_, 5.0);
    EXPECT_EQ(scrollBar->centerDeviation_, 2);
    EXPECT_LT(scrollBar->trickStartAngle_, 2);
}

/**
 * @tc.name: ArcScrollBarTestNg005
 * @tc.desc: Test HandleDragUpdate when child height less than scroll height
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg005, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    GestureEvent info;
    info.SetMainDelta(10.f);
    pattern_->HandleDragUpdate(info);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->currentOffset_, 0);
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->isDriving_);
    EXPECT_EQ(scrollBar->CalcPatternOffset(ARC_LIST_ITER_SCALE), 0.92f);

    info.SetMainDelta(10.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleDragUpdate(info);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    scrollBar->PlayScrollBarAppearAnimation();
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::AUTO);
}

/**
 * @tc.name: ArcScrollBarTestNg006
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg006, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    ArcScrollBarOverlayModifier modifier;
    auto hoverType = HoverAnimationType::NONE;
    /**
     * @tc.steps: step1. Create modifier, call onDraw/DrawArc/DrawBackgroundArc
     */
    RSCanvas canvas;
    DrawingContext context { canvas, 240.f, 400.f };
    modifier.onDraw(context);
    modifier.DrawArc(context);
    modifier.DrawBackgroundArc(context);
    EXPECT_EQ(modifier.lastMainModeHeight_, 0.0f);
    EXPECT_EQ(modifier.lastMainModeOffset_, 0.0f);
    EXPECT_EQ(modifier.positionMode_, PositionMode::RIGHT);
    EXPECT_EQ(modifier.hoverAnimatingType_, hoverType);
    EXPECT_TRUE(modifier.isNavDestinationShow_);
}

/**
 * @tc.name: ArcScrollBarTestNg007
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg007, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Create modifer, call StartArcBarAnimation
     * @tc.expected: expect backgroundStrokeWidth_->Get() is 5
     */
    bool needAdaptAnimation = true;
    Point centerPoint(1, 1);
    float radius = 5;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier modifer;
    modifer.StartArcBarAnimation(HoverAnimationType::GROW,
        OpacityAnimationType::APPEAR, needAdaptAnimation, arcBarRect, arcBarRect);
    EXPECT_EQ(modifer.backgroundStrokeWidth_->Get(), 5);
    EXPECT_EQ(modifer.backgroundCurveRadius_->Get(), 5);
    EXPECT_EQ(modifer.backgroundStartAngle_->Get(), 5);
    EXPECT_EQ(modifer.backgroundSweepAngle_->Get(), 5);
}

/**
 * @tc.name: ArcScrollBarTestNg008
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg008, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Create arcmodifer, call StartHoverAnimation and HoverAnimationType is GROW
     */
    Point centerPoint(1, 1);
    float radius = 20;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier arcmodifer;
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::GROW);
    arcmodifer.SetBackgroundBarColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    arcmodifer.SetCurveCenter(centerPoint);
    EXPECT_EQ(arcmodifer.backgroundStrokeWidth_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundCurveRadius_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundStartAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundSweepAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetX(), 1);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetY(), 1);
}

/**
 * @tc.name: ArcScrollBarTestNg009
 * @tc.desc: Test CalcReservedHeight
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg009, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    EXPECT_NE(scrollBar, nullptr);

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
    EXPECT_EQ(scrollBar->startReservedHeight_.ConvertToPx(), 0);
    EXPECT_EQ(scrollBar->endReservedHeight_.ConvertToPx(), 0);
}

/**
 * @tc.name: ArcScrollBarTestNg010
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg010, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Create modifer, call SetBackgroundArcRect
     * @tc.expected: expect backgroundStrokeWidth_->Get() is 20.f
     */
    Point centerPoint(3, 3);
    ArcRound arcBarRect(centerPoint, 10.f, 10.f, 20.f, 20.f);
    ArcScrollBarOverlayModifier modifer;
    modifer.SetBackgroundArcRect(arcBarRect);
    EXPECT_EQ(modifer.backgroundStrokeWidth_->Get(), 20.f);
    EXPECT_EQ(modifer.backgroundCurveRadius_->Get(), 10.f);
    EXPECT_EQ(modifer.backgroundStartAngle_->Get(), 10.f);
    EXPECT_EQ(modifer.backgroundSweepAngle_->Get(), 20.f);

    /**
     * @tc.steps: step1. Create modifer, call SetArcRect
     * @tc.expected: expect curveCenter_->Get() is 3
     */
    modifer.SetArcRect(arcBarRect);
    EXPECT_EQ(modifer.strokeWidth_->Get(), 20.f);
    EXPECT_EQ(modifer.curveRadius_->Get(), 10.f);
    EXPECT_EQ(modifer.curveCenter_->Get().GetX(), 3);
    EXPECT_EQ(modifer.curveCenter_->Get().GetY(), 3);
    EXPECT_EQ(modifer.startAngle_->Get(), 10.f);
    EXPECT_EQ(modifer.sweepAngle_->Get(), 20.f);
}

/**
 * @tc.name: ArcScrollBarTestNg011
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg011, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. ScrollBar at top, call SetBarRegion/SetRoundTrickRegion
     */
    Offset paintOffset_(5, 15);
    Size size { 10, 10 };
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    EXPECT_NE(scrollBar, nullptr);
    scrollBar->SetBarRegion(paintOffset_, size);
    scrollBar->SetRoundTrickRegion(paintOffset_, size, paintOffset_, 5.0);
    EXPECT_EQ(scrollBar->centerDeviation_, 2);
    EXPECT_LT(scrollBar->trickStartAngle_, 2);
    scrollBar->SetActiveWidth(scrollBar->normalWidth_);
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->SetBarRegion(paintOffset_, size);
    EXPECT_NE(scrollBar->arcAarRect_.startAngle_, 0.0);
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->SetBarRegion(paintOffset_, size);
    EXPECT_NE(scrollBar->arcAarRect_.startAngle_, 0.0);

    scrollBar->SetRoundTrickRegion(100.0, 0.0, 0.0, 0.0, 0.0, size);
    EXPECT_EQ(scrollBar->arcHoverRegion_.startAngle_, scrollBar->arcActiveRect_.startAngle_);

    scrollBar->SetRoundTrickRegion(10.001, 0.0, 0.0, 0.0, 0.0, size);
    EXPECT_EQ(scrollBar->arcHoverRegion_.startAngle_, scrollBar->arcActiveRect_.startAngle_);
}

/**
 * @tc.name: ArcScrollBarTestNg012
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg012, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    ArcScrollBarOverlayModifier modifier;
    auto hoverType = HoverAnimationType::NONE;
    /**
     * @tc.steps: step1. Create modifier, call onDraw/DrawArc/DrawBackgroundArc
     */
    RSCanvas canvas;
    DrawingContext context { canvas, 240.f, 400.f };
    modifier.onDraw(context);
    modifier.DrawArc(context);
    modifier.DrawBackgroundArc(context);
    EXPECT_EQ(modifier.lastMainModeHeight_, 0.0f);
    EXPECT_EQ(modifier.lastMainModeOffset_, 0.0f);
    EXPECT_EQ(modifier.positionMode_, PositionMode::RIGHT);
    EXPECT_EQ(modifier.hoverAnimatingType_, hoverType);
    EXPECT_TRUE(modifier.isNavDestinationShow_);

    modifier.backgroundBarColor_ = nullptr;
    ContainerScope::UpdateCurrent(-1);
    modifier.DrawBackgroundArc(context);
    EXPECT_EQ(modifier.hoverAnimatingType_, HoverAnimationType::NONE);

    modifier.onDraw(context);
    EXPECT_EQ(modifier.hoverAnimatingType_, HoverAnimationType::NONE);

    modifier.backgroundCurveRadius_ = nullptr;
    modifier.onDraw(context);
    EXPECT_NE(modifier.curveRadius_, 0.0f);

    modifier.backgroundStrokeWidth_ = nullptr;
    modifier.onDraw(context);
    EXPECT_NE(modifier.strokeWidth_, 0.0f);

    modifier.backgroundSweepAngle_ = nullptr;
    modifier.onDraw(context);
    EXPECT_NE(modifier.sweepAngle_, 0.0f);

    modifier.backgroundStartAngle_ = nullptr;
    modifier.onDraw(context);
    EXPECT_NE(modifier.startAngle_, 0.0f);

    modifier.curveRadius_ = nullptr;
    modifier.onDraw(context);
    EXPECT_EQ(modifier.backgroundCurveRadius_, 0.0f);

    modifier.sweepAngle_ = nullptr;
    modifier.onDraw(context);
    EXPECT_EQ(modifier.backgroundSweepAngle_, 0.0f);

    modifier.startAngle_ = nullptr;
    modifier.onDraw(context);
    EXPECT_EQ(modifier.backgroundStartAngle_, 0.0f);

    modifier.curveCenter_ = nullptr;
    modifier.onDraw(context);
    EXPECT_EQ(modifier.backgroundStartAngle_, 0.0f);

    modifier.strokeWidth_ = nullptr;
    modifier.onDraw(context);
    EXPECT_EQ(modifier.backgroundStrokeWidth_, 0.0f);
}

/**
 * @tc.name: ArcScrollBarTestNg013
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg013, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Create modifer, call StartArcBarAnimation
     * @tc.expected: expect backgroundStrokeWidth_->Get() is 5
     */
    bool needAdaptAnimation = true;
    Point centerPoint(1, 1);
    float radius = 5;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier modifer;
    modifer.StartArcBarAnimation(HoverAnimationType::GROW,
        OpacityAnimationType::APPEAR, needAdaptAnimation, arcBarRect, arcBarRect);
    EXPECT_EQ(modifer.backgroundStrokeWidth_->Get(), 5);
    EXPECT_EQ(modifer.backgroundCurveRadius_->Get(), 5);
    EXPECT_EQ(modifer.backgroundStartAngle_->Get(), 5);
    EXPECT_EQ(modifer.backgroundSweepAngle_->Get(), 5);
    modifer.SetScrollable(true);
    modifer.StartArcBarAnimation(HoverAnimationType::NONE,
        OpacityAnimationType::APPEAR, true, arcBarRect, arcBarRect);
    EXPECT_EQ(modifer.backgroundStrokeWidth_->Get(), 5);
}

/**
 * @tc.name: ArcScrollBarTestNg014
 * @tc.desc: Test ArcScrollTest
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarTestNg, ArcScrollBarTestNg014, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    /**
     * @tc.steps: step1. Create arcmodifer, call StartHoverAnimation and HoverAnimationType is GROW
     */
    Point centerPoint(1, 1);
    float radius = 20;
    ArcRound arcBarRect(centerPoint, radius, radius, radius, radius);
    ArcScrollBarOverlayModifier arcmodifer;
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::GROW);
    arcmodifer.SetBackgroundBarColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    arcmodifer.SetCurveCenter(centerPoint);
    EXPECT_EQ(arcmodifer.backgroundStrokeWidth_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundCurveRadius_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundStartAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.backgroundSweepAngle_->Get(), 20);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetX(), 1);
    EXPECT_EQ(arcmodifer.curveCenter_->Get().GetY(), 1);

    arcmodifer.curveCenter_ = nullptr;
    arcmodifer.SetCurveCenter(centerPoint);
    EXPECT_NE(arcmodifer.backgroundCurveRadius_->Get(), 0);

    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::NONE);
    EXPECT_NE(arcmodifer.hoverAnimatingType_, HoverAnimationType::NONE);
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, arcmodifer.hoverAnimatingType_);
    EXPECT_EQ(arcmodifer.hoverAnimatingType_, HoverAnimationType::GROW);
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::GROW);
    EXPECT_EQ(arcmodifer.hoverAnimatingType_, HoverAnimationType::GROW);
    arcmodifer.StartHoverAnimation(arcBarRect, arcBarRect, HoverAnimationType::SHRINK);
    EXPECT_EQ(arcmodifer.hoverAnimatingType_, HoverAnimationType::SHRINK);

    arcmodifer.backgroundBarColor_ = nullptr;
    arcmodifer.SetBackgroundBarColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    EXPECT_EQ(arcmodifer.hoverAnimatingType_, HoverAnimationType::SHRINK);
}

} // namespace OHOS::Ace::NG
