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
#include "core/components_ng/pattern/swiper/swiper_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_paint_method.h"
namespace OHOS::Ace::NG {
namespace {
constexpr double DEAFULT_INDICATOR_WIDTH = 5.3333334922790527;
} // namespace

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
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DOT);
    });
    RefPtr<OverlengthDotIndicatorModifier> modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    RefPtr<OverlengthDotIndicatorPaintMethod> paintMethod =
        AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
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
    RefPtr<Modifier> ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    RefPtr<OverlengthDotIndicatorModifier> overLengthModifier =
        AceType::DynamicCast<OverlengthDotIndicatorModifier>(ptrModifier);
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

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

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

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(25.f);
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(15.f);
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
    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(8.f);
    normalItemHalfSizes.emplace_back(8.f);
    normalItemHalfSizes.emplace_back(16.f);
    normalItemHalfSizes.emplace_back(16.f);
    dotIndicatorModifier.CalcAnimationEndCenterX(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.moveDirection_, OverlongIndicatorMove::NONE);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorWidth_.size(), 0);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorHeight_.size(), 0);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorWidth_.size(), 0);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorHeight_.size(), 0);

    dotIndicatorModifier.SetMaxDisplayCount(7);
    dotIndicatorModifier.SetRealItemCount(15);
    dotIndicatorModifier.animationStartIndex_ = 3;
    dotIndicatorModifier.animationEndIndex_ = 4;
    dotIndicatorModifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    dotIndicatorModifier.CalcAnimationEndCenterX(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.moveDirection_, OverlongIndicatorMove::MOVE_BACKWARD);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorWidth_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationStartIndicatorWidth_[0], DEAFULT_INDICATOR_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.animationStartIndicatorHeight_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationStartIndicatorHeight_[0], DEAFULT_INDICATOR_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorWidth_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationEndIndicatorWidth_[0], DEAFULT_INDICATOR_WIDTH);
    EXPECT_EQ(dotIndicatorModifier.animationEndIndicatorHeight_.size(), 8);
    EXPECT_DOUBLE_EQ(dotIndicatorModifier.animationEndIndicatorHeight_[0], DEAFULT_INDICATOR_WIDTH);
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
    LinearVector<float> animationEndCenterX;
    animationEndCenterX.emplace_back(20.f);
    animationEndCenterX.emplace_back(25.f);
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX;
    animationStartCenterX.emplace_back(10.f);
    animationStartCenterX.emplace_back(25.f);
    dotIndicatorModifier.animationStartCenterX_ = animationStartCenterX;
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    dotIndicatorModifier.UpdateSelectedCenterXOnDrag(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.first, 1.4f);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.second, 1.6f);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 1);

    dotIndicatorModifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    dotIndicatorModifier.UpdateSelectedCenterXOnDrag(normalItemHalfSizes);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.first, 1.f);
    EXPECT_EQ(dotIndicatorModifier.overlongSelectedEndCenterX_.second, 1.f);
}

HWTEST_F(SwiperOverLengthIndicatorModifierTestNg, OverlengthDotIndicatorModifier004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    dotIndicatorModifier.blackPointCenterMoveRate_ = 0.7f;
    dotIndicatorModifier.currentSelectedIndex_ = 0;
    dotIndicatorModifier.targetSelectedIndex_ = 1;
    LinearVector<float> animationEndCenterX;
    animationEndCenterX.emplace_back(20.f);
    animationEndCenterX.emplace_back(25.f);
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX;
    animationStartCenterX.emplace_back(10.f);
    animationStartCenterX.emplace_back(25.f);
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
    dotIndicatorModifier.turnPageRate_= 0.f;
    auto animationEndIndex = dotIndicatorModifier.CalcTargetIndexOnDrag();
    EXPECT_EQ(animationEndIndex, 1);

    dotIndicatorModifier.turnPageRate_= 0.5f;
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
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(20.f);
    dotIndicatorModifier.PlayBlackPointsAnimation(itemHalfSizes);
    EXPECT_FALSE(dotIndicatorModifier.isSelectedColorAnimEnd_);

    dotIndicatorModifier.maxDisplayCount_ = 6;
    LinearVector<float> animationEndCenterX;
    animationEndCenterX.emplace_back(20.f);
    animationEndCenterX.emplace_back(25.f);
    animationEndCenterX.emplace_back(30.f);
    animationEndCenterX.emplace_back(35.f);
    animationEndCenterX.emplace_back(40.f);
    animationEndCenterX.emplace_back(45.f);
    dotIndicatorModifier.animationEndCenterX_ = animationEndCenterX;
    LinearVector<float> animationStartCenterX;
    animationStartCenterX.emplace_back(10.f);
    animationStartCenterX.emplace_back(15.f);
    animationStartCenterX.emplace_back(20.f);
    animationStartCenterX.emplace_back(25.f);
    animationStartCenterX.emplace_back(30.f);
    animationStartCenterX.emplace_back(35.f);
    dotIndicatorModifier.animationStartCenterX_ = animationStartCenterX;
    LinearVector<float> animationStartIndicatorWidth;
    animationStartIndicatorWidth.emplace_back(5.f);
    animationStartIndicatorWidth.emplace_back(10.f);
    animationStartIndicatorWidth.emplace_back(20.f);
    animationStartIndicatorWidth.emplace_back(20.f);
    animationStartIndicatorWidth.emplace_back(10.f);
    animationStartIndicatorWidth.emplace_back(5.f);
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
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(20.f);
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

    dotIndicatorModifier.maxDisplayCount_ = 5;
    dotIndicatorModifier.realItemCount_ = 4;
    dotIndicatorModifier.currentSelectedIndex_ = 2;
    dotIndicatorModifier.CalcTargetSelectedIndex(0, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);

    dotIndicatorModifier.CalcTargetSelectedIndex(0, 3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 5);

    dotIndicatorModifier.currentSelectedIndex_ = 1;
    dotIndicatorModifier.CalcTargetSelectedIndex(0, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);

    dotIndicatorModifier.CalcTargetSelectedIndex(0, 2);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 3);

    dotIndicatorModifier.CalcTargetSelectedIndex(0, 3);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 4);

    dotIndicatorModifier.currentSelectedIndex_ = 3;
    dotIndicatorModifier.CalcTargetSelectedIndex(0, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 4);

    dotIndicatorModifier.CalcTargetSelectedIndex(4, 2);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);

    dotIndicatorModifier.CalcTargetSelectedIndex(4, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 1);

    dotIndicatorModifier.CalcTargetSelectedIndex(4, 0);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 0);

    dotIndicatorModifier.currentSelectedIndex_ = 2;
    dotIndicatorModifier.CalcTargetSelectedIndex(4, 2);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, 2);

    dotIndicatorModifier.CalcTargetSelectedIndex(4, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, -1);

    dotIndicatorModifier.currentSelectedIndex_ = 1;
    dotIndicatorModifier.CalcTargetSelectedIndex(4, 1);
    EXPECT_EQ(dotIndicatorModifier.targetSelectedIndex_, -2);
}

}