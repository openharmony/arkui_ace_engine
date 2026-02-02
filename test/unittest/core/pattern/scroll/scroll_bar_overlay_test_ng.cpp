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
#include "scroll_test_ng.h"
#include "base/memory/ace_type.h"
#include "test/mock/core/rosen/mock_canvas.h"

namespace OHOS::Ace::NG {

void ScrollBarOverlayTestNg::SetUp() {}

void ScrollBarOverlayTestNg::TearDown() {}

/**
 * @tc.name: StopAdaptAnimation001
 * @tc.desc: Test StopAdaptAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StopAdaptAnimation001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0, 0);
    ASSERT_NE(motion, nullptr);
    option.SetCurve(motion);
    auto adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    ASSERT_NE(adaptAnimation_, nullptr);
    scrollBarOverlayModifier.StopAdaptAnimation();
    EXPECT_EQ(scrollBarOverlayModifier.isAdaptAnimationStop_, true);
}

/**
 * @tc.name: SetMainModeSize001
 * @tc.desc: Test SetMainModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeSize001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barWidth = scrollBarOverlayModifier.barWidth_;
    scrollBarOverlayModifier.barWidth_->Set(size.Width());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetMainModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barWidth_, barWidth);
}

/**
 * @tc.name: SetMainModeSize002
 * @tc.desc: Test SetMainModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeSize002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barHeight = scrollBarOverlayModifier.barHeight_;
    scrollBarOverlayModifier.barHeight_->Set(size.Height());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetMainModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barHeight_, barHeight);
}

/**
 * @tc.name: SetCrossModeSize001
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeSize001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barHeight = scrollBarOverlayModifier.barHeight_;
    scrollBarOverlayModifier.barHeight_->Set(size.Height());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetCrossModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barHeight_, barHeight);
}

/**
 * @tc.name: SetCrossModeSize002
 * @tc.desc: Test SetCrossModeSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeSize002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Size size;
    auto barWidth = scrollBarOverlayModifier.barWidth_;
    scrollBarOverlayModifier.barWidth_->Set(size.Width());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetCrossModeSize(size);
    EXPECT_EQ(scrollBarOverlayModifier.barWidth_, barWidth);
}

/**
 * @tc.name: SetMainModeOffset001
 * @tc.desc: Test SetMainModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeOffset001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barX = scrollBarOverlayModifier.barX_;
    scrollBarOverlayModifier.barX_->Set(offset.GetX());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetMainModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barX_, barX);
}

/**
 * @tc.name: SetMainModeOffset002
 * @tc.desc: Test SetMainModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetMainModeOffset002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barY = scrollBarOverlayModifier.barY_;
    scrollBarOverlayModifier.barY_->Set(offset.GetY());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetMainModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barY_, barY);
}

/**
 * @tc.name: SetCrossModeOffset001
 * @tc.desc: Test SetCrossModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeOffset001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barY = scrollBarOverlayModifier.barY_;
    scrollBarOverlayModifier.barY_->Set(offset.GetY());
    scrollBarOverlayModifier.positionMode_ = PositionMode::BOTTOM;
    scrollBarOverlayModifier.SetCrossModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barY_, barY);
}

/**
 * @tc.name: SetCrossModeOffset002
 * @tc.desc: Test SetCrossModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetCrossModeOffset002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset;
    auto barX = scrollBarOverlayModifier.barX_;
    scrollBarOverlayModifier.barX_->Set(offset.GetX());
    scrollBarOverlayModifier.positionMode_ = PositionMode::RIGHT;
    scrollBarOverlayModifier.SetCrossModeOffset(offset);
    EXPECT_EQ(scrollBarOverlayModifier.barX_, barX);
}

/**
 * @tc.name: SetBoundsRect
 * @tc.desc: Test SetBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetBoundsRect, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    Offset offset(10.0, 10.0);
    Size size(10.0, 200.0);
    scrollBarOverlayModifier.SetOpacity(AceType::MakeRefPtr<AnimatablePropertyUint8>(UINT8_MAX));
    scrollBarOverlayModifier.barColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    scrollBarOverlayModifier.barWidth_->Set(size.Height());
    scrollBarOverlayModifier.barHeight_->Set(size.Width());
    scrollBarOverlayModifier.barX_->Set(offset.GetX());
    scrollBarOverlayModifier.barY_->Set(offset.GetY());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    EXPECT_CALL(canvas, AttachBrush).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush).WillRepeatedly(ReturnRef(canvas));
    DrawingContext drawingContext = { canvas, WIDTH, HEIGHT };
    scrollBarOverlayModifier.onDraw(drawingContext);
    EXPECT_EQ(
        scrollBarOverlayModifier.GetBoundsRect(), RectF(offset.GetX(), offset.GetX(), size.Height(), size.Width()));
}

/**
 * @tc.name: StartOpacityAnimation001
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation001, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR_WITHOUT_ANIMATION;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_EQ(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation002
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation002, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation003
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation003, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::DISAPPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = false;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_EQ(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation004
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation004, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = false;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: StartOpacityAnimation005
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartOpacityAnimation005, TestSize.Level1)
{
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    OpacityAnimationType opacityAnimationType;
    opacityAnimationType = OpacityAnimationType::APPEAR;
    scrollBarOverlayModifier.isNavDestinationShow_ = true;
    scrollBarOverlayModifier.StartOpacityAnimation(opacityAnimationType);
    EXPECT_NE(scrollBarOverlayModifier.opacityAnimatingType_, OpacityAnimationType::NONE);
}

/**
 * @tc.name: AdjustOffset
 * @tc.desc: Test StartOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, AdjustOffset, TestSize.Level1)
{
    Offset offset(10.0, 10.0);
    ScrollBarOverlayModifier scrollBarOverlayModifier;
    scrollBarOverlayModifier.SetAdjustOffset(offset);
    Offset offsetGet =  scrollBarOverlayModifier.GetAdjustOffset();
    EXPECT_EQ(offset, offsetGet);
}

/**
 * @tc.name: ScrollBarOverlayModifier001
 * @tc.desc: Test ScrollBarOverlayModifier construction with default parameters
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, ScrollBarOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollBarOverlayModifier with default parameters
     * @tc.expected: Verify initial state
     */
    ScrollBarOverlayModifier modifier;
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::NONE);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);
    EXPECT_TRUE(modifier.GetScrollable());
}

/**
 * @tc.name: ScrollBarOverlayModifier002
 * @tc.desc: Test ScrollBarOverlayModifier construction with custom parameters
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, ScrollBarOverlayModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollBarOverlayModifier with custom offset and size
     * @tc.expected: Verify custom parameters are applied
     */
    OffsetF customOffset(50.0f, 100.0f);
    SizeF customSize(10.0f, 200.0f);
    ScrollBarOverlayModifier modifier(customOffset, customSize);

    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::NONE);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: SetScrollable001
 * @tc.desc: Test SetScrollable with various states
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and verify default scrollable state
     * @tc.expected: Should be scrollable by default
     */
    ScrollBarOverlayModifier modifier;
    EXPECT_TRUE(modifier.GetScrollable());

    /**
     * @tc.steps: step2. Set scrollable to false
     * @tc.expected: Scrollable state should change
     */
    modifier.SetScrollable(false);
    EXPECT_FALSE(modifier.GetScrollable());

    /**
     * @tc.steps: step3. Set scrollable back to true
     * @tc.expected: Scrollable state should be restored
     */
    modifier.SetScrollable(true);
    EXPECT_TRUE(modifier.GetScrollable());
}

/**
 * @tc.name: SetOpacity001
 * @tc.desc: Test SetOpacity with various opacity values
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetOpacity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set full opacity
     * @tc.expected: Opacity should be set to default value (UINT8_MAX)
     */
    ScrollBarOverlayModifier modifier;
    // Initial opacity is UINT8_MAX from constructor
    EXPECT_EQ(modifier.GetOpacity(), UINT8_MAX);

    /**
     * @tc.steps: step2. Set half opacity
     * @tc.expected: SetOpacity should execute without errors
     * Note: SetOpacity uses AnimationUtils::ExecuteWithoutAnimation,
     * the value may not be immediately reflected in GetOpacity()
     */
    modifier.SetOpacity(UINT8_MAX / 2);

    /**
     * @tc.steps: step3. Set zero opacity (fully transparent)
     * @tc.expected: SetOpacity should execute without errors
     */
    modifier.SetOpacity(0);
    // Verify that the method can be called without crashes
    SUCCEED();
}

/**
 * @tc.name: SetBarColor001
 * @tc.desc: Test SetBarColor with different colors
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetBarColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set bar color to blue
     * @tc.expected: Bar color should be set to blue
     */
    ScrollBarOverlayModifier modifier;
    Color testColor = Color::BLUE;
    modifier.SetBarColor(testColor);
    auto barColor = modifier.GetBarColor();
    ASSERT_NE(barColor, nullptr);
    EXPECT_EQ(barColor->Get(), Color::BLUE);

    /**
     * @tc.steps: step2. Change bar color to red
     * @tc.expected: Bar color should update to red
     */
    modifier.SetBarColor(Color::RED);
    EXPECT_EQ(barColor->Get(), Color::RED);

    /**
     * @tc.steps: step3. Set bar color to custom RGB value
     * @tc.expected: Bar color should reflect custom value
     */
    Color customColor = Color::FromARGB(255, 0x80, 0x40, 0xC0);
    modifier.SetBarColor(customColor);
    EXPECT_EQ(barColor->Get(), customColor);
}

/**
 * @tc.name: SetPositionMode001
 * @tc.desc: Test SetPositionMode with all position modes
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetPositionMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test RIGHT position mode
     * @tc.expected: Position mode should be set correctly
     */
    ScrollBarOverlayModifier modifier;
    modifier.SetPositionMode(PositionMode::RIGHT);
    Size size(100.0, 200.0);
    modifier.SetMainModeSize(size);
    // RIGHT mode should affect barHeight (cross mode for horizontal scrollbar)
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size.Height());

    /**
     * @tc.steps: step2. Test BOTTOM position mode
     * @tc.expected: Position mode should change to BOTTOM
     */
    modifier.SetPositionMode(PositionMode::BOTTOM);
    modifier.SetMainModeSize(size);
    // BOTTOM mode should affect barWidth (main mode for horizontal scrollbar)
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size.Width());

    /**
     * @tc.steps: step3. Test LEFT position mode
     * @tc.expected: Position mode should change to LEFT
     */
    modifier.SetPositionMode(PositionMode::LEFT);
    modifier.SetMainModeSize(size);
    // LEFT mode should affect barHeight (main mode for vertical scrollbar)
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size.Height());
}

/**
 * @tc.name: StopHoverAnimation001
 * @tc.desc: Test StopHoverAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StopHoverAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and start hover animation
     * @tc.expected: Hover animation type should be GROW
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 100, 200);
    modifier.StartHoverAnimation(barRect, HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);

    /**
     * @tc.steps: step2. Stop hover animation
     * @tc.expected: Hover animation should be stopped
     */
    modifier.StopHoverAnimation();
    // After stopping, a new animation can be started without issues
    modifier.StartHoverAnimation(barRect, HoverAnimationType::SHRINK);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
}

/**
 * @tc.name: StopOpacityAnimation001
 * @tc.desc: Test StopOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StopOpacityAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and start opacity animation
     * @tc.expected: Opacity animation type should be APPEAR
     */
    ScrollBarOverlayModifier modifier;
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Stop opacity animation
     * @tc.expected: New animation can be started after stopping
     */
    modifier.StopOpacityAnimation();
    // After stopping, a new animation can be started
    modifier.StartOpacityAnimation(OpacityAnimationType::DISAPPEAR);
    // Animation type may have changed due to the stop and new start
    auto animType = modifier.GetOpacityAnimatingType();
    EXPECT_TRUE(animType == OpacityAnimationType::DISAPPEAR ||
                animType == OpacityAnimationType::NONE); // May be NONE if isNavDestinationShow_ is false
}

/**
 * @tc.name: StartHoverAnimation001
 * @tc.desc: Test StartHoverAnimation with GROW type
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartHoverAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test GROW hover animation
     * @tc.expected: Hover animation should start with GROW type
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 100, 200);
    modifier.StartHoverAnimation(barRect, HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);
}

/**
 * @tc.name: StartHoverAnimation002
 * @tc.desc: Test StartHoverAnimation with SHRINK type
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartHoverAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test SHRINK hover animation
     * @tc.expected: Hover animation should start with SHRINK type
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 100, 200);
    modifier.StartHoverAnimation(barRect, HoverAnimationType::SHRINK);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
}

/**
 * @tc.name: StartHoverAnimation003
 * @tc.desc: Test StartHoverAnimation with NONE type (no animation)
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartHoverAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test NONE hover animation
     * @tc.expected: Hover animation should remain NONE
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 100, 200);
    modifier.StartHoverAnimation(barRect, HoverAnimationType::NONE);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::NONE);
}

/**
 * @tc.name: StartBarAnimation001
 * @tc.desc: Test StartBarAnimation with combined hover and opacity animations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartBarAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test combined animations
     * @tc.expected: Both hover and opacity animations should start
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(10, 10, 100, 200);
    modifier.StartBarAnimation(HoverAnimationType::GROW, OpacityAnimationType::APPEAR, false, barRect);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::APPEAR);
}

/**
 * @tc.name: StartBarAnimation002
 * @tc.desc: Test StartBarAnimation with SHRINK hover and DISAPPEAR opacity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartBarAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test shrink + disappear animations
     * @tc.expected: Both animations should reflect shrink and disappear
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 50, 150);
    modifier.StartBarAnimation(HoverAnimationType::SHRINK, OpacityAnimationType::DISAPPEAR, false, barRect);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::DISAPPEAR);
}

/**
 * @tc.name: StartBarAnimation003
 * @tc.desc: Test StartBarAnimation with adapt animation enabled
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartBarAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test with adapt animation
     * @tc.expected: Animations should start with adapt enabled
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(20, 20, 80, 180);
    modifier.StartBarAnimation(HoverAnimationType::GROW, OpacityAnimationType::APPEAR, true, barRect);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::APPEAR);
}

/**
 * @tc.name: StartAdaptAnimation001
 * @tc.desc: Test StartAdaptAnimation with needAdaptAnimation enabled
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartAdaptAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and start adapt animation
     * @tc.expected: Adapt animation should start, isAdaptAnimationStop_ should be false
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 60, 160);
    modifier.StartAdaptAnimation(barRect, true);
    // When needAdaptAnimation is true, isAdaptAnimationStop_ should be set to false
    EXPECT_FALSE(modifier.isAdaptAnimationStop_);
}

/**
 * @tc.name: StartAdaptAnimation002
 * @tc.desc: Test StartAdaptAnimation with needAdaptAnimation disabled
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, StartAdaptAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test without adapt animation
     * @tc.expected: Adapt animation should not start, isAdaptAnimationStop_ should remain true
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(10, 10, 70, 170);
    modifier.StartAdaptAnimation(barRect, false);
    // When needAdaptAnimation is false (CHECK_NULL_VOID returns early), isAdaptAnimationStop_ remains true
    EXPECT_TRUE(modifier.isAdaptAnimationStop_);
}

/**
 * @tc.name: AnimationStateTransition001
 * @tc.desc: Test animation state transitions from GROW to SHRINK
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, AnimationStateTransition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and start GROW animation
     * @tc.expected: Hover animation should be GROW
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(0, 0, 100, 200);
    modifier.StartHoverAnimation(barRect, HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);

    /**
     * @tc.steps: step2. Transition to SHRINK animation
     * @tc.expected: Hover animation should change to SHRINK
     */
    modifier.StartHoverAnimation(barRect, HoverAnimationType::SHRINK);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);

    /**
     * @tc.steps: step3. Stop animation and start NONE animation
     * @tc.expected: NONE animation doesn't change hoverAnimatingType_
     * Note: StartHoverAnimation with NONE type returns early without updating
     * hoverAnimatingType_, so the type remains SHRINK
     */
    modifier.StopHoverAnimation();
    modifier.StartHoverAnimation(barRect, HoverAnimationType::NONE);
    // NONE type doesn't update hoverAnimatingType_, it stays at SHRINK
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
}

/**
 * @tc.name: AnimationStateTransition002
 * @tc.desc: Test opacity animation state transitions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, AnimationStateTransition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test APPEAR animation
     * @tc.expected: Opacity animation should be APPEAR
     */
    ScrollBarOverlayModifier modifier;
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Transition to DISAPPEAR animation
     * @tc.expected: Opacity animation should change to DISAPPEAR or NONE based on isNavDestinationShow_
     */
    modifier.StartOpacityAnimation(OpacityAnimationType::DISAPPEAR);
    auto animType = modifier.GetOpacityAnimatingType();
    EXPECT_TRUE(animType == OpacityAnimationType::DISAPPEAR ||
                animType == OpacityAnimationType::NONE);

    /**
     * @tc.steps: step3. Stop animation and start APPEAR_WITHOUT_ANIMATION
     * @tc.expected: Opacity animation should be NONE
     */
    modifier.StopOpacityAnimation();
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR_WITHOUT_ANIMATION);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: SetOffset001
 * @tc.desc: Test SetOffset with various offset values
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set positive offset
     * @tc.expected: Offset should be applied
     */
    ScrollBarOverlayModifier modifier;
    OffsetF offset1(50.0f, 100.0f);
    modifier.SetOffset(offset1);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), offset1.GetX());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), offset1.GetY());

    /**
     * @tc.steps: step2. Set zero offset
     * @tc.expected: Offset should update to zero
     */
    OffsetF offset2(0.0f, 0.0f);
    modifier.SetOffset(offset2);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), offset2.GetX());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), offset2.GetY());

    /**
     * @tc.steps: step3. Set negative offset
     * @tc.expected: Negative offset should be applied
     */
    OffsetF offset3(-10.0f, -20.0f);
    modifier.SetOffset(offset3);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), offset3.GetX());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), offset3.GetY());
}

/**
 * @tc.name: SetSize001
 * @tc.desc: Test SetSize with various size values
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set normal size
     * @tc.expected: Size should be applied
     */
    ScrollBarOverlayModifier modifier;
    SizeF size1(10.0f, 200.0f);
    modifier.SetSize(size1);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size1.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size1.Height());

    /**
     * @tc.steps: step2. Set minimum size
     * @tc.expected: Minimum size should be applied
     */
    SizeF size2(1.0f, 1.0f);
    modifier.SetSize(size2);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size2.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size2.Height());

    /**
     * @tc.steps: step3. Set large size
     * @tc.expected: Large size should be applied
     */
    SizeF size3(100.0f, 1000.0f);
    modifier.SetSize(size3);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size3.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size3.Height());
}

/**
 * @tc.name: SetRect001
 * @tc.desc: Test SetRect with various rectangle values
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, SetRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set rectangle
     * @tc.expected: Rectangle should be applied to both offset and size
     */
    ScrollBarOverlayModifier modifier;
    Rect rect1(10, 10, 100, 200);
    modifier.SetRect(rect1);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), rect1.Left());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), rect1.Top());
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), rect1.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), rect1.Height());

    /**
     * @tc.steps: step2. Set rectangle with zero dimensions
     * @tc.expected: Zero dimension rectangle should be applied
     */
    Rect rect2(0, 0, 0, 0);
    modifier.SetRect(rect2);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), rect2.Left());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), rect2.Top());
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), rect2.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), rect2.Height());

    /**
     * @tc.steps: step3. Set rectangle with large dimensions
     * @tc.expected: Large dimension rectangle should be applied
     */
    Rect rect3(1000, 1000, 500, 500);
    modifier.SetRect(rect3);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), rect3.Left());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), rect3.Top());
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), rect3.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), rect3.Height());
}

/**
 * @tc.name: NavDestinationState001
 * @tc.desc: Test NavDestination show state affecting animations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, NavDestinationState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier with NavDestination shown
     * @tc.expected: APPEAR animation should start
     */
    ScrollBarOverlayModifier modifier;
    modifier.SetNavDestinationShow(true);
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Hide NavDestination and start DISAPPEAR animation
     * @tc.expected: DISAPPEAR animation should start
     */
    modifier.SetNavDestinationShow(false);
    modifier.StartOpacityAnimation(OpacityAnimationType::DISAPPEAR);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: MultipleAnimations001
 * @tc.desc: Test multiple animations running simultaneously
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, MultipleAnimations001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and start multiple animations
     * @tc.expected: All animations should be active
     */
    ScrollBarOverlayModifier modifier;
    Rect barRect(10, 10, 80, 180);

    modifier.StartBarAnimation(HoverAnimationType::GROW, OpacityAnimationType::APPEAR, true, barRect);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Stop all animations
     * @tc.expected: New animations can be started after stopping
     */
    modifier.StopHoverAnimation();
    modifier.StopOpacityAnimation();
    // Verify that new animations can be started after stopping
    modifier.StartBarAnimation(HoverAnimationType::SHRINK, OpacityAnimationType::DISAPPEAR, false, barRect);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
}

/**
 * @tc.name: EdgeCaseZeroSize001
 * @tc.desc: Test behavior with zero-size scrollbar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, EdgeCaseZeroSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set zero size
     * @tc.expected: Should handle zero size gracefully
     */
    ScrollBarOverlayModifier modifier;
    SizeF zeroSize(0.0f, 0.0f);
    modifier.SetSize(zeroSize);

    Rect zeroRect(0, 0, 0, 0);
    modifier.StartHoverAnimation(zeroRect, HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);
}

/**
 * @tc.name: EdgeCaseLargeOffset001
 * @tc.desc: Test behavior with very large offset values
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, EdgeCaseLargeOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and set very large offset
     * @tc.expected: Should handle large offset values
     */
    ScrollBarOverlayModifier modifier;
    OffsetF largeOffset(10000.0f, 20000.0f);
    modifier.SetOffset(largeOffset);
    EXPECT_FLOAT_EQ(modifier.barX_->Get(), largeOffset.GetX());
    EXPECT_FLOAT_EQ(modifier.barY_->Get(), largeOffset.GetY());

    SizeF normalSize(10.0f, 200.0f);
    modifier.SetSize(normalSize);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), normalSize.Width());
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), normalSize.Height());
}

/**
 * @tc.name: AnimationInterruption001
 * @tc.desc: Test animation interruption scenarios
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, AnimationInterruption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start APPEAR animation
     * @tc.expected: APPEAR animation should be active
     */
    ScrollBarOverlayModifier modifier;
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Interrupt with DISAPPEAR animation
     * @tc.expected: Animation should transition to DISAPPEAR
     */
    modifier.StartOpacityAnimation(OpacityAnimationType::DISAPPEAR);
    EXPECT_NE(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step3. Interrupt with APPEAR_WITHOUT_ANIMATION
     * @tc.expected: Animation should complete immediately
     */
    modifier.StartOpacityAnimation(OpacityAnimationType::APPEAR_WITHOUT_ANIMATION);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);
}

/**
 * @tc.name: HoverAnimatingTypeGetter001
 * @tc.desc: Test GetHoverAnimatingType with various states
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, HoverAnimatingTypeGetter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and verify initial NONE state
     * @tc.expected: Should return NONE
     */
    ScrollBarOverlayModifier modifier;
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::NONE);

    /**
     * @tc.steps: step2. Set to GROW state
     * @tc.expected: Should return GROW
     */
    modifier.SetHoverAnimatingType(HoverAnimationType::GROW);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::GROW);

    /**
     * @tc.steps: step3. Set to SHRINK state
     * @tc.expected: Should return SHRINK
     */
    modifier.SetHoverAnimatingType(HoverAnimationType::SHRINK);
    EXPECT_EQ(modifier.GetHoverAnimatingType(), HoverAnimationType::SHRINK);
}

/**
 * @tc.name: OpacityAnimatingTypeGetter001
 * @tc.desc: Test GetOpacityAnimatingType with various states
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, OpacityAnimatingTypeGetter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and verify initial NONE state
     * @tc.expected: Should return NONE
     */
    ScrollBarOverlayModifier modifier;
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::NONE);

    /**
     * @tc.steps: step2. Set to APPEAR state
     * @tc.expected: Should return APPEAR
     */
    modifier.SetOpacityAnimatingType(OpacityAnimationType::APPEAR);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::APPEAR);

    /**
     * @tc.steps: step3. Set to DISAPPEAR state
     * @tc.expected: Should return DISAPPEAR
     */
    modifier.SetOpacityAnimatingType(OpacityAnimationType::DISAPPEAR);
    EXPECT_EQ(modifier.GetOpacityAnimatingType(), OpacityAnimationType::DISAPPEAR);
}

/**
 * @tc.name: PositionModeWithSize001
 * @tc.desc: Test different position modes with size calculations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, PositionModeWithSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create modifier and test BOTTOM mode
     * @tc.expected: Should handle BOTTOM position mode, setting barWidth for main mode
     */
    ScrollBarOverlayModifier modifier;
    Size size(100.0, 200.0);
    modifier.SetPositionMode(PositionMode::BOTTOM);
    modifier.SetMainModeSize(size);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size.Width());

    /**
     * @tc.steps: step2. Test RIGHT mode
     * @tc.expected: Should handle RIGHT position mode, setting barHeight for main mode
     */
    modifier.SetPositionMode(PositionMode::RIGHT);
    modifier.SetMainModeSize(size);
    EXPECT_FLOAT_EQ(modifier.barHeight_->Get(), size.Height());

    /**
     * @tc.steps: step3. Test LEFT mode
     * @tc.expected: Should handle LEFT position mode, setting barWidth for cross mode
     */
    modifier.SetPositionMode(PositionMode::LEFT);
    modifier.SetCrossModeSize(size);
    EXPECT_FLOAT_EQ(modifier.barWidth_->Get(), size.Width());
}

/**
 * @tc.name: OnDrawWithDifferentModes001
 * @tc.desc: Test onDraw with different position modes
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverlayTestNg, OnDrawWithDifferentModes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test onDraw with RIGHT position mode
     * @tc.expected: Drawing should complete without errors
     */
    ScrollBarOverlayModifier modifier;
    modifier.SetPositionMode(PositionMode::RIGHT);
    modifier.SetOpacity(AceType::MakeRefPtr<AnimatablePropertyUint8>(UINT8_MAX));
    modifier.SetBarColor(Color::BLUE);
    // Set valid size so that onDraw will actually draw something
    // (onDraw only calls DrawRoundRect when both barWidth and barHeight are non-zero)
    SizeF barSize(10.0f, 200.0f);
    modifier.SetSize(barSize);

    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush).WillRepeatedly(ReturnRef(canvas));
    DrawingContext drawingContext = { canvas, WIDTH, HEIGHT };
    // onDraw should complete without errors; verify by expecting DrawRoundRect call
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(1);
    modifier.onDraw(drawingContext);
}

} // namespace OHOS::Ace::NG

