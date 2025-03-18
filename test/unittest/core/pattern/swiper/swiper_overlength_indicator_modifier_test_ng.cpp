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
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/swiper/swiper_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
class SwiperOverLengthIndicatorModifierTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, SwiperOverLengthIndicatorGetContentModifier001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    paintMethod->SetMaxDisplayCount(7);
    auto geometryNode = frameNode_->GetGeometryNode();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     *
     * @tc.steps: step3. call GetContentModifier.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    auto overLengthModifier = AceType::DynamicCast<OverlengthDotIndicatorModifier>(ptrModifier);
    ASSERT_NE(overLengthModifier, nullptr);
    EXPECT_EQ(overLengthModifier->maxDisplayCount_, 7);
    EXPECT_FALSE(overLengthModifier->isHover_);
    EXPECT_FALSE(overLengthModifier->isPressed_);
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test OverlengthDotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX = { 20.f };
    LinearVector<float> normalItemHalfSizes = { 20.f, 20.f, 20.f, 20.f };

    dotIndicatorModifier.UpdateShrinkPaintProperty(OffsetF(50.0, 60.0), normalItemHalfSizes, { 1.f, 1.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 20.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 20.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 20.f);
    EXPECT_EQ(dotIndicatorModifier.longPointLeftCenterX_->Get(), 1.f);
    EXPECT_EQ(dotIndicatorModifier.longPointRightCenterX_->Get(), 1.f);

    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    LinearVector<float> normalItemHalfSizesSecond = { 20.f, 25.f, 20.f, 15.f };
    dotIndicatorModifier.longPointLeftAnimEnd_ = false;
    dotIndicatorModifier.UpdateShrinkPaintProperty(OffsetF(50.0, 60.0), normalItemHalfSizesSecond, { 2.f, 2.f });
    dotIndicatorModifier.maxDisplayCount_ = 7;
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 25.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 15.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 25.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 15.f);
    EXPECT_EQ(dotIndicatorModifier.longPointLeftCenterX_->Get(), 1.f);
    EXPECT_EQ(dotIndicatorModifier.longPointRightCenterX_->Get(), 1.f);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    LinearVector<float> normalItemHalfSizes = { 3.f, 3.f, 3.f, 3.f };
    dotIndicatorModifier.CalcAnimationEndCenterX(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.moveDirection_, OverlongIndicatorMove::NONE);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorWidth_.size(), 1);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorHeight_.size(), 1);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorWidth_.size(), 1);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorHeight_.size(), 1);

    dotIndicatorModifier.SetMaxDisplayCount(7);
    dotIndicatorModifier.SetRealItemCount(15);
    dotIndicatorModifier.animationStartIndex_ = 4;
    dotIndicatorModifier.animationEndIndex_ = 5;
    dotIndicatorModifier.currentSelectedIndex_ = 4;
    dotIndicatorModifier.targetSelectedIndex_ = 4;
    dotIndicatorModifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    dotIndicatorModifier.gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    dotIndicatorModifier.CalcAnimationEndCenterX(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.moveDirection_, OverlongIndicatorMove::MOVE_BACKWARD);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorWidth_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationStartIndicatorWidth_[0], 2.f);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorHeight_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationStartIndicatorHeight_[0], 2.f);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorWidth_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationEndIndicatorWidth_[0], 2.f);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorHeight_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationEndIndicatorHeight_[0], 2.f);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    dotIndicatorModifier.longPointLeftCenterMoveRate_ = 0.6f;
    dotIndicatorModifier.longPointRightCenterMoveRate_ = 0.4f;
    dotIndicatorModifier.blackPointCenterMoveRate_ = 0.7f;
    dotIndicatorModifier.overlongSelectedEndCenterX_ = { 2.f, 2.f };
    dotIndicatorModifier.overlongSelectedStartCenterX_ = { 1.f, 1.f };
    dotIndicatorModifier.currentSelectedIndex_ = 0;
    dotIndicatorModifier.targetSelectedIndex_ = 1;
    LinearVector<float> animationEndCenterX = { 20.f, 25.f };
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX = { 10.f, 25.f };
    dotIndicatorModifier.animationStartCenterX_ = animationStartCenterX;
    LinearVector<float> normalItemHalfSizes = { 20.f, 20.f, 20.f, 20.f };
    dotIndicatorModifier.UpdateSelectedCenterXOnDrag(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.first, 1.4f);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.second, 1.6f);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 1);

    dotIndicatorModifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    dotIndicatorModifier.UpdateSelectedCenterXOnDrag(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.first, 1.3f);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.second, 1.2f);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    dotIndicatorModifier.blackPointCenterMoveRate_ = 0.7f;
    dotIndicatorModifier.currentSelectedIndex_ = 0;
    dotIndicatorModifier.targetSelectedIndex_ = 1;
    LinearVector<float> animationEndCenterX = { 20.f, 25.f };
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX = { 10.f, 25.f };
    dotIndicatorModifier.animationStartCenterX_ = animationStartCenterX;
    dotIndicatorModifier.UpdateUnselectedCenterXOnDrag();
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 1);
    EXPECT_EQ(dotIndicatorModifier.animationEndCenterX_[0], 13.0f);
    EXPECT_EQ(dotIndicatorModifier.animationEndCenterX_[1], 25.f);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.animationEndIndex_ = 1;
    dotIndicatorModifier.turnPageRate_ = 0.f;
    auto animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 1);

    dotIndicatorModifier.turnPageRate_ = 0.5f;
    animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 1);

    dotIndicatorModifier.animationStartIndex_ = 0;
    dotIndicatorModifier.realItemCount_ = 2;
    animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 0);

    dotIndicatorModifier.animationStartIndex_ = 1;
    animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 1);

    dotIndicatorModifier.realItemCount_ = 3;
    animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 2);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.maxDisplayCount_ = 3;
    dotIndicatorModifier.isSelectedColorAnimEnd_ = true;
    LinearVector<float> itemHalfSizes = { 20.f, 20.f };
    dotIndicatorModifier.PlayBlackPointsAnimation(itemHalfSizes);
    EXPECT_FALSE(dotIndicatorModifier.isSelectedColorAnimEnd_);

    dotIndicatorModifier.maxDisplayCount_ = 6;
    LinearVector<float> animationEndCenterX = { 20.f, 25.f, 30.f, 35.f, 40.f, 45.f };
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX = { 10.f, 15.f, 20.f, 25.f, 30.f, 35.f };
    dotIndicatorModifier.animationStartCenterX_ = animationStartCenterX;
    LinearVector<float> animationStartIndicatorWidth = { 5.f, 10.f, 20.f, 20.f, 10.f, 5.f };
    dotIndicatorModifier.animationStartIndicatorWidth_ = animationStartIndicatorWidth;
    dotIndicatorModifier.animationStartIndicatorHeight_ = animationStartIndicatorWidth;
    dotIndicatorModifier.unselectedIndicatorWidth_->Set(animationStartIndicatorWidth);
    dotIndicatorModifier.unselectedIndicatorHeight_->Set(animationStartIndicatorWidth);
    dotIndicatorModifier.targetSelectedIndex_ = 3;
    dotIndicatorModifier.animationStartIndex_ = 1;
    dotIndicatorModifier.animationEndIndex_ = 2;
    dotIndicatorModifier.PlayBlackPointsAnimation(itemHalfSizes);
    EXPECT_FALSE(dotIndicatorModifier.isSelectedColorAnimEnd_);
    EXPECT_TRUE(dotIndicatorModifier.isTouchBottomLoop_);
    EXPECT_EQ(dotIndicatorModifier.firstPointOpacity_->Get(), UINT8_MAX);
    EXPECT_EQ(dotIndicatorModifier.vectorBlackPointCenterX_->Get().size(), 6);
    EXPECT_EQ(dotIndicatorModifier.unselectedIndicatorWidth_->Get().size(), 0);
    EXPECT_EQ(dotIndicatorModifier.animationStartCenterX_.size(), 6);
    EXPECT_EQ(dotIndicatorModifier.unselectedIndicatorHeight_->Get().size(), 0);
    EXPECT_EQ(dotIndicatorModifier.newPointOpacity_->Get(), 0);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier007, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    LinearVector<float> itemHalfSizes = { 20.f, 20.f };
    GestureState gestureState = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    TouchBottomTypeLoop touchBottomTypeLoop = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    OffsetF margin = OffsetF(20.f, 25.f);
    dotIndicatorModifier.PlayIndicatorAnimation(margin, itemHalfSizes, gestureState, touchBottomTypeLoop);
    EXPECT_FALSE(dotIndicatorModifier.longPointRightAnimEnd_);

    dotIndicatorModifier.StopAnimation(true);
    EXPECT_TRUE(dotIndicatorModifier.longPointLeftAnimEnd_);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier008, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.maxDisplayCount_ = 5;
    dotIndicatorModifier.realItemCount_ = 7;
    dotIndicatorModifier.InitOverlongStatus(3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);
    EXPECT_EQ(dotIndicatorModifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT);

    dotIndicatorModifier.maxDisplayCount_ = 5;
    dotIndicatorModifier.realItemCount_ = 6;
    dotIndicatorModifier.InitOverlongStatus(3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);
    EXPECT_EQ(dotIndicatorModifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);

    dotIndicatorModifier.maxDisplayCount_ = 5;
    dotIndicatorModifier.realItemCount_ = 5;
    dotIndicatorModifier.InitOverlongStatus(3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 3);
    EXPECT_EQ(dotIndicatorModifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);

    dotIndicatorModifier.maxDisplayCount_ = 5;
    dotIndicatorModifier.realItemCount_ = 4;
    dotIndicatorModifier.InitOverlongStatus(3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 4);
    EXPECT_EQ(dotIndicatorModifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier009, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.targetSelectedIndex_ = 0;
    dotIndicatorModifier.CalcTargetSelectedIndex(1, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 0);

    dotIndicatorModifier.maxDisplayCount_ = 9;
    dotIndicatorModifier.realItemCount_ = 15;
    dotIndicatorModifier.currentSelectedIndex_ = 2;
    dotIndicatorModifier.CalcTargetSelectedIndex(2, 3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 3);

    dotIndicatorModifier.currentSelectedIndex_ = 3;
    dotIndicatorModifier.CalcTargetSelectedIndex(3, 4);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 4);

    dotIndicatorModifier.currentSelectedIndex_ = 6;
    dotIndicatorModifier.CalcTargetSelectedIndex(6, 7);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 6);

    dotIndicatorModifier.currentSelectedIndex_ = 6;
    dotIndicatorModifier.CalcTargetSelectedIndex(11, 12);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 6);

    dotIndicatorModifier.CalcTargetSelectedIndex(12, 13);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 7);

    dotIndicatorModifier.CalcTargetSelectedIndex(13, 14);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 8);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier010
 * @tc.desc: Test the GetTouchBottomCenterX method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier attributes and ContentProperty attributes
     * @tc.expected: attributes set successfully
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.longPointLeftCenterX = 50.0f;
    contentProperty.longPointRightCenterX = 150.0f;
    contentProperty.vectorBlackPointCenterX = { 100.0f, 200.0f, 300.0f };
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorModifier->SetIsHorizontalAndRTL(false);
    indicatorModifier->SetRealItemCount(3);
    indicatorModifier->SetMaxDisplayCount(3);
    float radius = (contentProperty.longPointRightCenterX - contentProperty.longPointLeftCenterX) * 0.5f;

    /**
     * @tc.steps: step2. Set AnimationState STAGE_SHRINKT_TO_BLACK_POINT and isLeftTouchBottom
     * @tc.expected: Verify the result and result should be as expected
     */
    indicatorModifier->SetCurrentIndex(2);
    indicatorModifier->isCustomSize_ = false;
    indicatorModifier->animationState_ = TouchBottomAnimationStage::STAGE_SHRINKT_TO_BLACK_POINT;
    auto result = indicatorModifier->GetTouchBottomCenterX(contentProperty);
    EXPECT_NEAR(result.first, contentProperty.vectorBlackPointCenterX[0] - radius, 0.001f);
    EXPECT_NEAR(result.second, contentProperty.vectorBlackPointCenterX[0] + radius, 0.001f);

    /**
     * @tc.steps: step3. Set IsCustomSize true and Call GetTouchBottomCenterX method
     * @tc.expected: Verify the result
     */
    indicatorModifier->SetCurrentIndex(0);
    indicatorModifier->isCustomSize_ = true;
    indicatorModifier->animationState_ = TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT;
    result = indicatorModifier->GetTouchBottomCenterX(contentProperty);
    EXPECT_NEAR(result.first, contentProperty.longPointLeftCenterX, 0.001f);
    EXPECT_NEAR(result.second, contentProperty.longPointRightCenterX, 0.001f);

    /**
     * @tc.steps: step4. Set AnimationState STAGE_EXPAND_TO_LONG_POINT and isLeftTouchBottom
     * @tc.expected: Verify the result and result should be as expected
     */
    indicatorModifier->SetCurrentIndex(2);
    indicatorModifier->isCustomSize_ = false;
    indicatorModifier->animationState_ = TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT;
    result = indicatorModifier->GetTouchBottomCenterX(contentProperty);
    auto first = contentProperty.vectorBlackPointCenterX[indicatorModifier->maxDisplayCount_ - 1] - radius;
    auto second = contentProperty.vectorBlackPointCenterX[indicatorModifier->maxDisplayCount_ - 1] + radius;
    EXPECT_NEAR(result.first, first, 0.001f);
    EXPECT_NEAR(result.second, second, 0.001f);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier011
 * @tc.desc: Test the PaintBlackPoint method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier attributes and ContentProperty attributes
     * @tc.expected: attributes set successfully
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 100.0f, 200.0f, 300.0f };
    auto vXSize = contentProperty.vectorBlackPointCenterX.size();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).Times(vXSize * 2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).Times(vXSize * 2).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(vXSize);
    DrawingContext context { canvas, 100.f, 100.f };
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    /**
     * @tc.steps: step2. Set NearEqual(width, height) and isCustomSize_ true
     * @tc.expected: Verify the result and result should be as expected
     */
    contentProperty.unselectedIndicatorWidth = { 100.0f, 200.0f, 300.0f };
    contentProperty.unselectedIndicatorHeight = { 100.0f, 200.0f, 300.0f };
    indicatorModifier->isCustomSize_ = true;
    indicatorModifier->PaintBlackPoint(context, contentProperty);

    /**
     * @tc.steps: step3. Set NearEqual(width, height) and isCustomSize_ false
     * @tc.expected: Verify the result and result should be as expected
     */
    contentProperty.unselectedIndicatorWidth = { 100.0f, 200.0f, 300.0f };
    contentProperty.unselectedIndicatorHeight = { 100.0f, 200.0f, 300.0f };
    indicatorModifier->isCustomSize_ = false;
    indicatorModifier->PaintBlackPoint(context, contentProperty);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier012
 * @tc.desc: Test the UpdateUnselectedCenterXOnDrag method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier and ContentProperty parmameters
     * @tc.expected: attributes set successfully
     */
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorModifier->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    indicatorModifier->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    indicatorModifier->turnPageRate_ = -1.0f;
    indicatorModifier->animationStartIndicatorWidth_ = { 1.0f };
    indicatorModifier->animationEndIndicatorWidth_ = { 2.0f };
    indicatorModifier->animationStartIndicatorHeight_ = { 3.0f };
    indicatorModifier->animationEndIndicatorHeight_ = { 4.0f };
    indicatorModifier->animationStartCenterX_ = { 5.0f };
    indicatorModifier->animationEndCenterX_ = { 6.0f };
    /**
     * @tc.steps: step2. Call UpdateUnselectedCenterXOnDrag
     * @tc.expected: Verify the result and result should be as expected
     */
    auto widthStart = indicatorModifier->animationStartIndicatorWidth_[0];
    auto widthEnd = indicatorModifier->animationEndIndicatorWidth_[0];
    auto heightStart = indicatorModifier->animationStartIndicatorHeight_[0];
    auto heightEnd = indicatorModifier->animationEndIndicatorHeight_[0];
    auto CenterXStart = indicatorModifier->animationStartCenterX_[0];
    auto CenterXEnd = indicatorModifier->animationEndCenterX_[0];
    float expectMoveRate = 1.0f;
    auto expectWidth = widthStart + (widthEnd - widthStart) * expectMoveRate;
    auto expectHeight = heightStart + (heightEnd - heightStart) * expectMoveRate;
    auto expectCenterX = CenterXStart + (CenterXEnd - CenterXStart) * expectMoveRate;
    indicatorModifier->UpdateUnselectedCenterXOnDrag();
    EXPECT_NEAR(expectWidth, indicatorModifier->animationEndIndicatorWidth_[0], 0.001f);
    EXPECT_NEAR(expectHeight, indicatorModifier->animationEndIndicatorHeight_[0], 0.001f);
    EXPECT_NEAR(expectCenterX, indicatorModifier->animationEndCenterX_[0], 0.001f);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier013
 * @tc.desc: Test CalcTargetStatusOnAllPointMoveBackward method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier and parameters
     * @tc.expected: parameters set successfully
     */
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorModifier->isSwiperTouchDown_ = true;
    indicatorModifier->maxDisplayCount_ = 2;
    indicatorModifier->targetSelectedIndex_ = 1;
    const LinearVector<float> itemHalfSizes = { 5.0f, 7.0f };
    indicatorModifier->targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    indicatorModifier->animationStartCenterX_ = { 50.0f, 80.0f, 110.0f, 140.0f, 170.0f };
    indicatorModifier->animationStartIndicatorWidth_ = { 20.0f, 20.0f, 20.0f, 20.0f, 20.0f };
    indicatorModifier->animationStartIndicatorHeight_ = { 20.0f, 20.0f, 20.0f, 20.0f, 20.0f };
    indicatorModifier->animationEndCenterX_ = { 60.0f, 90.0f, 110.0f, 140.0f, 170.0f };
    indicatorModifier->animationEndIndicatorWidth_ = { 60.0f, 90.0f, 110.0f, 140.0f, 170.0f };
    indicatorModifier->animationEndIndicatorHeight_ = { 60.0f, 90.0f, 110.0f, 140.0f, 170.0f };

    /**
     * @tc.steps: step2. Call UpdateUnselectedCenterXOnDrag
     * @tc.expected: Verify the result and result should be as expected
     */
    indicatorModifier->turnPageRate_ = -1.0f;
    indicatorModifier->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    indicatorModifier->CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    float expectMoveRate = 1.0f;
    auto firstPointOpacity = static_cast<uint8_t>(UINT8_MAX * (1.0f - expectMoveRate));
    EXPECT_EQ(indicatorModifier->firstPointOpacity_->Get(), firstPointOpacity);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier014
 * @tc.desc: Test InitOverlongSelectedIndex method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier and parameters
     * @tc.expected: parameters set successfully
     */
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    int32_t thirdPointIndex = 2;
    int32_t secondPointIndex = 1;
    int32_t maxDisplayCount = 5;
    int32_t realItemCount = 10;
    indicatorModifier->maxDisplayCount_ = maxDisplayCount;
    indicatorModifier->realItemCount_ = realItemCount;

    /**
     * @tc.steps: step2. Call InitOverlongSelectedIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    int32_t pageIndex = 1;
    indicatorModifier->InitOverlongSelectedIndex(pageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, pageIndex);

    /**
     * @tc.steps: step3. Call InitOverlongSelectedIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    pageIndex = 7;
    indicatorModifier->InitOverlongSelectedIndex(pageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, maxDisplayCount - 1 - thirdPointIndex);

    /**
     * @tc.steps: step4. Call InitOverlongSelectedIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    pageIndex = 8;
    indicatorModifier->InitOverlongSelectedIndex(pageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, maxDisplayCount - 1 - secondPointIndex);

    /**
     * @tc.steps: step5. Call InitOverlongSelectedIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    pageIndex = 9;
    indicatorModifier->InitOverlongSelectedIndex(pageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, maxDisplayCount - 1);
}

/**
 * @tc.name: OverlengthDotIndicatorModifier015
 * @tc.desc: Test CalcTargetOverlongStatus method with various cases
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorModifier and parameters
     * @tc.expected: parameters set successfully
     */
    auto indicatorModifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    int32_t maxDisplayCount = 5;
    int32_t realItemCount = 10;
    indicatorModifier->maxDisplayCount_ = maxDisplayCount;
    indicatorModifier->realItemCount_ = realItemCount;
    indicatorModifier->currentSelectedIndex_ = 2;
    /**
     * @tc.steps: step2. Call CalcTargetOverlongStatus with currentPageIndex == targetPageIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    int32_t currentPageIndex = 9;
    int32_t targetPageIndex = 0;
    indicatorModifier->currentOverlongType_ = OverlongType::NONE;
    indicatorModifier->CalcTargetOverlongStatus(currentPageIndex, targetPageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, 0);
    EXPECT_EQ(indicatorModifier->targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);

    /**
     * @tc.steps: step3. Call CalcTargetOverlongStatus with currentPageIndex < targetPageIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    currentPageIndex = 0;
    targetPageIndex = 9;
    indicatorModifier->currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    indicatorModifier->CalcTargetOverlongStatus(currentPageIndex, targetPageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, maxDisplayCount - 1);
    EXPECT_EQ(indicatorModifier->targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);

    /**
     * @tc.steps: step4. Call CalcTargetOverlongStatus with currentPageIndex > targetPageIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    indicatorModifier->currentSelectedIndex_ = 2;
    currentPageIndex = 3;
    targetPageIndex = 4;
    indicatorModifier->currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    indicatorModifier->CalcTargetOverlongStatus(currentPageIndex, targetPageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, 2);

    /**
     * @tc.steps: step4. Call CalcTargetOverlongStatus with currentPageIndex < targetPageIndex
     * @tc.expected: Verify the result and result should be as expected
     */
    indicatorModifier->currentSelectedIndex_ = 2;
    currentPageIndex = 4;
    targetPageIndex = 3;
    indicatorModifier->currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    indicatorModifier->CalcTargetOverlongStatus(currentPageIndex, targetPageIndex);
    EXPECT_EQ(indicatorModifier->targetSelectedIndex_, 2);
}

/**
 * @tc.name: SwiperOverLengthIndicatorGetContentModifier016
 * @tc.desc: Test PaintNormalIndicator method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, SwiperOverLengthIndicatorGetContentModifier016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorPaintMethod and parameters
     * @tc.expected: parameters set successfully
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    auto geometryNode = frameNode_->GetGeometryNode();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     * @tc.steps: step2. call PaintNormalIndicator and modifier isHover_ = true.
     */
    modifier->isHover_ = true;
    modifier->longPointLeftAnimEnd_ = false;
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_NEAR(0.0f, paintMethod->longPointCenterX_.first, 0.001f);
    EXPECT_NEAR(0.0f, paintMethod->longPointCenterX_.second, 0.001f);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_);
    /**
     *
     * @tc.steps: step3. call PaintNormalIndicator and modifier isHover_ = false.
     */
    modifier->isHover_ = false;
    modifier->isPressed_ = true;
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_NEAR(0.0f, paintMethod->longPointCenterX_.first, 0.001f);
    EXPECT_NEAR(0.0f, paintMethod->longPointCenterX_.second, 0.001f);
}

/**
 * @tc.name: SwiperOverLengthIndicatorGetContentModifier017
 * @tc.desc: Test CalculatePointCenterX method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, SwiperOverLengthIndicatorGetContentModifier017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorPaintMethod and parameters
     * @tc.expected: parameters set successfully
     */
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    paintMethod->SetMaxDisplayCount(3);
    int32_t itemCount = 5;
    paintMethod->itemCount_ = itemCount;
    paintMethod->IsCustomSizeValue_ = false;
    float space = 0;
    float margin = 0;
    float padding = 0;
    int32_t index = 0;
    LinearVector<float> itemHalfSizes = { 20.f, 20.f, 20.f, 20.f };
    /**
     * @tc.steps: step2. call PaintNormalIndicator and turnPageRate_ is positive.
     */
    paintMethod->turnPageRate_ = -1;
    auto value = paintMethod->CalculatePointCenterX(itemHalfSizes, margin, padding, space, index);
    EXPECT_NEAR(20.0f, value.first, 0.001f);
    EXPECT_NEAR(60.0f, value.second, 0.001f);
    /**
     * @tc.steps: step3. call PaintNormalIndicator and turnPageRate_ is unpositive.
     */
    paintMethod->turnPageRate_ = 1;
    value = paintMethod->CalculatePointCenterX(itemHalfSizes, margin, padding, space, index);
    EXPECT_NEAR(20.0f, value.first, 0.001f);
    EXPECT_NEAR(60.0f, value.second, 0.001f);
}

/**
 * @tc.name: SwiperOverLengthIndicatorGetContentModifier018
 * @tc.desc: Test CalculatePointCenterX method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, SwiperOverLengthIndicatorGetContentModifier018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set OverlengthDotIndicatorPaintMethod and parameters
     */
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    paintMethod->SetMaxDisplayCount(5);
    paintMethod->itemCount_ = 6;
    paintMethod->realItemCount_ = 10;
    DotIndicatorPaintMethod::StarAndEndPointCenter starAndEndPointCenter { 10.0f, 20.0f, 30.0f, 40.0f };
    LinearVector<float> startVectorBlackPointCenterX = { 1.0f, 2.0f, 3.0f };
    LinearVector<float> endVectorBlackPointCenterX = { 4.0f, 5.0f, 6.0f };
    Dimension indicatorOffsetUnit = 18.0_vp;
    /**
     * @tc.steps: step2. Call CalculatePointCenterX with currentIndex_ > (maxDisplayCount_ - NUM_3) and currentIndex_ <
     * realItemCount_ - NUM_2
     * @tc.expected: Validate the results of CalculatePointCenterX
     */
    paintMethod->currentIndex_ = 5;
    paintMethod->isPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto [blackPointCenterMoveRate, longPointLeftCenterMoveRate, longPointRightCenterMoveRate] =
        paintMethod->GetMoveRate();
    auto result = paintMethod->CalculatePointCenterX(
        starAndEndPointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
    EXPECT_FALSE(paintMethod->vectorBlackPointBegCenterX_.empty());
    EXPECT_NEAR(paintMethod->vectorBlackPointBegCenterX_[2],
        startVectorBlackPointCenterX[2] -
            (paintMethod->currentIndex_ - (paintMethod->maxDisplayCount_ - 3)) * (indicatorOffsetUnit.ConvertToPx()) +
            (endVectorBlackPointCenterX[2] - startVectorBlackPointCenterX[2]) * blackPointCenterMoveRate,
        0.001f);
    /**
     * @tc.steps: step3. Call CalculatePointCenterX with currentIndex_ > (maxDisplayCount_ - NUM_3)
     * @tc.expected: Validate the results of CalculatePointCenterX
     */
    paintMethod->currentIndex_ = 9;
    paintMethod->isPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto [blackPointCenterMoveRateSecond, longPointLeftCenterMoveRateSecond, longPointRightCenterMoveRateSecond] =
        paintMethod->GetMoveRate();
    result = paintMethod->CalculatePointCenterX(
        starAndEndPointCenter, startVectorBlackPointCenterX, endVectorBlackPointCenterX);
    EXPECT_FALSE(paintMethod->vectorBlackPointBegCenterX_.empty());
    EXPECT_NEAR(paintMethod->vectorBlackPointBegCenterX_[2],
        startVectorBlackPointCenterX[2] -
            (paintMethod->realItemCount_ - paintMethod->maxDisplayCount_) * (indicatorOffsetUnit.ConvertToPx()) +
            (endVectorBlackPointCenterX[2] - startVectorBlackPointCenterX[2]) * blackPointCenterMoveRateSecond,
        0.001f);
}

/**
 * @tc.name: StopAnimation001
 * @tc.desc: Test StopAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, StopAnimation001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    LinearVector<float> itemHalfSizes = { 20.f, 20.f };
    GestureState gestureState = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    TouchBottomTypeLoop touchBottomTypeLoop = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    OffsetF margin = OffsetF(20.f, 25.f);
    EXPECT_TRUE(dotIndicatorModifier.blackPointsAnimEnd_);
    dotIndicatorModifier.PlayIndicatorAnimation(margin, itemHalfSizes, gestureState, touchBottomTypeLoop);
    EXPECT_FALSE(dotIndicatorModifier.blackPointsAnimEnd_);
    dotIndicatorModifier.StopAnimation(true);
    EXPECT_FALSE(dotIndicatorModifier.blackPointsAnimEnd_);
}

/**
 * @tc.name: ChangeIndex001
 * @tc.desc: Test change index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, ChangeIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    SwiperParameters swiperParameters;
    swiperParameters.maxDisplayCountVal = std::make_optional<int32_t>(6);
    model.SetDotIndicatorStyle(swiperParameters);
    CreateSwiperItems(10);
    CreateSwiperDone();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = indicatorPattern->overlongDotIndicatorModifier_;
    FlushUITasks();
    EXPECT_EQ(modifier->currentSelectedIndex_, 0);
    EXPECT_EQ(modifier->currentOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);

    layoutProperty_->UpdateIndex(5);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_EQ(modifier->currentSelectedIndex_, 3);
    EXPECT_EQ(modifier->currentOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcRealPadding001
 * @tc.desc: Test CalcRealPadding
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, CalcRealPadding001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    SwiperParameters swiperParameters;
    swiperParameters.maxDisplayCountVal = std::make_optional<int32_t>(6);
    model.SetDotIndicatorStyle(swiperParameters);
    CreateSwiperItems(10);
    CreateSwiperDone();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = indicatorPattern->overlongDotIndicatorModifier_;
    FlushUITasks();
    EXPECT_EQ(modifier->currentSelectedIndex_, 0);
    EXPECT_EQ(modifier->currentOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);

    modifier->isBindIndicator_ = false;
    auto unselectedIndicatorRadius = 10.0f;
    auto selectedIndicatorRadius = 20.0f;
    auto overlongType = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    auto realPadding = modifier->CalcRealPadding(unselectedIndicatorRadius, selectedIndicatorRadius, overlongType);
    auto realPaddingVp = Dimension(realPadding, DimensionUnit::PX).ConvertToVp();
    EXPECT_EQ(realPaddingVp, 12);

    modifier->isBindIndicator_ = true;
    realPadding = modifier->CalcRealPadding(unselectedIndicatorRadius, selectedIndicatorRadius, overlongType);
    overlongType = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    auto newRealPadding = modifier->CalcRealPadding(unselectedIndicatorRadius, selectedIndicatorRadius, overlongType);
    EXPECT_EQ(realPadding, newRealPadding);

    overlongType = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    newRealPadding = modifier->CalcRealPadding(unselectedIndicatorRadius, selectedIndicatorRadius, overlongType);
    EXPECT_GT(newRealPadding, realPadding);
}

/**
 * @tc.name: CalculateNormalMarginr001
 * @tc.desc: Test CalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, CalculateNormalMarginr001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    SwiperParameters swiperParameters;
    swiperParameters.maxDisplayCountVal = std::make_optional<int32_t>(6);
    model.SetDotIndicatorStyle(swiperParameters);
    CreateSwiperItems(10);
    CreateSwiperDone();

    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);

    LinearVector<float> itemHalfSizes = { 20.f, 20.f, 20.f, 20.f };
    auto indicatorGeometryNode = indicatorNode_->GetGeometryNode();
    CHECK_NULL_VOID(indicatorGeometryNode);
    auto frameSize = indicatorGeometryNode->GetFrameSize();
    auto displayCount = 1;
    auto indicatorDotItemSpace = Dimension(8.0f, DimensionUnit::PX);
    auto ignoreSize = false;
    paintMethod->maxDisplayCount_ = 6;
    paintMethod->isBindIndicator_ = true;
    paintMethod->CalculateNormalMargin(itemHalfSizes, frameSize, displayCount, indicatorDotItemSpace, ignoreSize);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);

    paintMethod->isBindIndicator_ = false;
    paintMethod->maxDisplayCount_ = 0;
    paintMethod->CalculateNormalMargin(itemHalfSizes, frameSize, displayCount, indicatorDotItemSpace, ignoreSize);
    EXPECT_NE(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_NE(paintMethod->normalMargin_.GetY(), 0);

    paintMethod->isBindIndicator_ = true;
    paintMethod->maxDisplayCount_ = 0;
    paintMethod->CalculateNormalMargin(itemHalfSizes, frameSize, displayCount, indicatorDotItemSpace, ignoreSize);
    EXPECT_NE(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_NE(paintMethod->normalMargin_.GetY(), 0);
}
} // namespace OHOS::Ace::NG