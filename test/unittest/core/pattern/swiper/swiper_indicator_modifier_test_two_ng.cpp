/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorModifierTestTwoNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperPaintMethodPaintFade004
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, SwiperPaintMethodPaintFade004, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(paintWrapper.paintProperty_, nullptr);
    auto frameSize = paintWrapper.GetGeometryNode()->GetFrameSize();
    /**
     * @tc.steps: step2. call PaintFade whith setting mainDelta_ and width.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 3000.0f;
    float testnumber = 2000.0f;
    frameSize.SetWidth(testnumber);
    EXPECT_EQ(frameSize.width_, testnumber);
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_TRUE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);

    /**
     * @tc.steps: step3. call PaintFade whith setting mainDelta_ and width in different confidions.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.mainDelta_ = -3000.0f;
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.axis_ = Axis::VERTICAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    frameSize.SetWidth(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade005
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, SwiperPaintMethodPaintFade005, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(1);
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(1);
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call PaintFade to count the number of calling ClipRect.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 1.0f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
}

/**
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, GetContentDrawFunction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Calling the switchPaintMethod1. GetContentDrawFunction (&paintWrapper) interface
     * @tc.expected: paintFunc not empty
     */
    auto paintFunc = swiperPaintMethod1.GetContentDrawFunction(&paintWrapper);
    EXPECT_NE(paintFunc, nullptr);
}

/**
 * @tc.name: PlayIndicatorAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, PlayIndicatorAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    TouchBottomTypeLoop touchBottomTypeLoop;
    touchBottomTypeLoop = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    /**
     * @tc.steps: step2. Construct parameters to call PlayIndicator Animation
     * @tc.expected: IsTouchBottomLoop_ Equal to false
     */
    modifier->PlayIndicatorAnimation(vectorBlackPointCenterX, longPointCenterX, gestureState, touchBottomTypeLoop);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);
}

/**
 * @tc.name: PaintUnselectedIndicator001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, PaintUnselectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the PaintUnselectedIndicator interface
     * @tc.expected: modifier->isCustomSize_ is false
     */
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(20.0f);
    itemHalfSizes.push_back(20.0f);

    RSCanvas canvas;
    auto offset = OffsetF(0.1f, 0.2f);
    bool currentIndexFlag = false;
    modifier->isCustomSize_ = false;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(modifier->isCustomSize_ == false);

    currentIndexFlag = true;
    modifier->isCustomSize_ = true;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(currentIndexFlag == true);

    currentIndexFlag = true;
    modifier->isCustomSize_ = false;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(currentIndexFlag);
}

/**
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, PlayLongPointAnimation001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };

    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);

    longPointCenterX.emplace_back(1.0f, 1.0f);
    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);
}

/**
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, PlayLongPointAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };

    /**
     * @tc.steps: step1.clear longPointCenterX Calling the PlayLongPointAnimation interface
     * @tc.expected: longPointCenterX is empty.
     */
    longPointCenterX.clear();
    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(longPointCenterX.empty());

    /**
     * @tc.steps: step2.GestureState:: Gesture_ DATE_ RELEASE_ Assign the value of Left to gastureState
     * @tc.expected: Satisfying the condition GestureState==GestureState:: GESTURE_ DATE_ RELEASE_ Left
     */
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    modifier->PlayLongPointAnimation(
        longPointCenterX, gestureState, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(gestureState == GestureState::GESTURE_STATE_RELEASE_LEFT);
}

/**
 * @tc.name: StopAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, StopAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the StopAnimation interface
     * @tc.expected: LongPointLeftAnimEnd_ And longPointRightAnimEnd_ To be true
     */
    modifier->StopAnimation();
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: UpdateLongPointDilateRatio001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, UpdateLongPointDilateRatio001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Call the UpdateLongPointDilateRatio interface to convert longPointIsHover_ Set to false
     * @tc.expected: LongPointIsHover_ Equal to true
     */
    modifier->longPointIsHover_ = true;
    modifier->UpdateLongPointDilateRatio();
    EXPECT_TRUE(modifier->longPointIsHover_);
}

/**
 * @tc.name: UpdateDilatePaintProperty001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, UpdateDilatePaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the UpdateDilatePaintProperty interface
     * @tc.expected: modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_ Condition is true
     */
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);

    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: UpdateShrinkPaintProperty002
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, UpdateShrinkPaintProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the UpdateShrinkPaintProperty interface
     * @tc.expected: Modifier ->longPointLeftAnimEnd_&& Modifier ->longPointRightAnimEnd_ Condition is false
     */
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);

    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    auto offset = OffsetF(0.1f, 0.2f);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: DotIndicatorModifier007
 * @tc.desc: Test PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 100.0f, 200.0f, 300.0f };
    LinearVector<float> itemHalfSizes = { 20.f, 30.f, 40.f, 50.f };

    contentProperty.itemHalfSizes = itemHalfSizes;
    DotIndicatorModifier dotIndicatorModifier;
    contentProperty.backgroundColor.colorValue_.value = 0xff000000;
    dotIndicatorModifier.backgroundWidthDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10.0f);
    dotIndicatorModifier.backgroundHeightDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20.0f);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).Times(AtLeast(1)).WillRepeatedly(ReturnRef(canvas));
    /**
     * @tc.steps: step2.Call PaintBackground
     * @tc.expected: The PaintBackground executed successfuly
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.PaintBackground(context, contentProperty);
}

/**
 * @tc.name: DotIndicatorModifier008
 * @tc.desc: Test GetTouchBottomCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    DotIndicatorModifier dotIndicatorModifier;
    contentProperty.longPointLeftCenterX = 10.0f;
    contentProperty.longPointRightCenterX = 30.0f;
    contentProperty.vectorBlackPointCenterX = { 40.0f, 50.0f, 60.0f };
    dotIndicatorModifier.isCustomSize_ = false;
    dotIndicatorModifier.currentIndex_ = 2;
    float radius = (contentProperty.longPointRightCenterX - contentProperty.longPointLeftCenterX) / 2.0f;
    /**
     * @tc.steps: step2.Call GetTouchBottomCenterX with STAGE_SHRINKT_TO_BLACK_POINT && isLeftTouchBottom
     * @tc.expected: The GetTouchBottomCenterX executed successfuly
     */
    dotIndicatorModifier.animationState_ = TouchBottomAnimationStage::STAGE_SHRINKT_TO_BLACK_POINT;
    auto result = dotIndicatorModifier.GetTouchBottomCenterX(contentProperty);
    EXPECT_NEAR(result.first, contentProperty.vectorBlackPointCenterX[0] - radius, 0.001f);
    EXPECT_NEAR(result.second, contentProperty.vectorBlackPointCenterX[0] + radius, 0.001f);
    /**
     * @tc.steps: step3.Call GetTouchBottomCenterX with TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT &&
     * isLeftTouchBottom
     * @tc.expected: The GetTouchBottomCenterX executed successfuly
     */
    dotIndicatorModifier.animationState_ = TouchBottomAnimationStage::STAGE_EXPAND_TO_LONG_POINT;
    result = dotIndicatorModifier.GetTouchBottomCenterX(contentProperty);
    EXPECT_NEAR(result.first, contentProperty.vectorBlackPointCenterX[2] - radius, 0.001f);
    EXPECT_NEAR(result.second, contentProperty.vectorBlackPointCenterX[2] + radius, 0.001f);
}

/**
 * @tc.name: DotIndicatorModifier009
 * @tc.desc: Test UpdateLongPointDilateRatio
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call the UpdateLongPointDilateRatio interface to convert longPointIsHover_ Set to false
     * @tc.expected: LongPointIsHover_ Equal to false
     */
    DotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.longPointIsHover_ = false;
    dotIndicatorModifier.UpdateLongPointDilateRatio();
    EXPECT_FALSE(dotIndicatorModifier.longPointIsHover_);
}

/**
 * @tc.name: DotIndicatorModifier010
 * @tc.desc: Test StopAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call the StopAnimation with ifImmediately false
     * @tc.expected: ifNeedFinishCallback_ Equal to false
     */
    DotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.ifNeedFinishCallback_ = false;
    dotIndicatorModifier.StopAnimation(true);
    EXPECT_FALSE(dotIndicatorModifier.ifNeedFinishCallback_);
}

/**
 * @tc.name: DotIndicatorModifier011
 * @tc.desc: Test GetLoopTranslateDuration
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call the GetLoopTranslateDuration
     * @tc.expected: result Equal to defaultTouchBottomAnimationDuration
     */
    DotIndicatorModifier dotIndicatorModifier;
    int32_t defaultTouchBottomAnimationDuration = 200;
    dotIndicatorModifier.headCurve_ = AceType::MakeRefPtr<InterpolatingSpring>(0.1f, 0.1f, 0.1f, 0.1f);
    auto result = dotIndicatorModifier.GetLoopTranslateDuration();
    EXPECT_EQ(result, defaultTouchBottomAnimationDuration);
}

/**
 * @tc.name: DotIndicatorModifier012
 * @tc.desc: Test GetLoopOpacityDuration
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call the GetLoopTranslateDuration
     * @tc.expected: result Equal to defaultOpacityAnimationDuration
     */
    DotIndicatorModifier dotIndicatorModifier;
    int32_t defaultOpacityAnimationDuration = 100;
    dotIndicatorModifier.headCurve_ = AceType::MakeRefPtr<InterpolatingSpring>(0.1f, 0.1f, 0.1f, 0.1f);
    auto result = dotIndicatorModifier.GetLoopOpacityDuration();
    EXPECT_EQ(result, defaultOpacityAnimationDuration);
}

/**
 * @tc.name: DotIndicatorModifier013
 * @tc.desc: Test PaintBackground and GetTouchBottomCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier013, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointCenterX;
    for (float i = 0.0f; i <= 300.0f ; i += 10.0f) {
        vectorBlackPointCenterX.emplace_back(i);
    }
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX;
    LinearVector<float> itemHalfSizes = { 20.f, 30.f, 40.f, 50.f };

    contentProperty.itemHalfSizes = itemHalfSizes;
    DotIndicatorModifier dotIndicatorModifier;
    contentProperty.backgroundColor.colorValue_.value = 0xff000000;
    dotIndicatorModifier.backgroundWidthDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1.225f);
    dotIndicatorModifier.backgroundHeightDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.8f);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AtLeast(1));
    EXPECT_CALL(canvas, DetachBrush()).Times(AtLeast(1)).WillRepeatedly(ReturnRef(canvas));
    /**
     * @tc.steps: step2.Call PaintBackground
     * @tc.expected: The PaintBackground executed successfuly
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.PaintBackground(context, contentProperty);

    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.PaintBackground(context, contentProperty);

    /**
     * @tc.steps: step3.Call vectorBlackPointCenterX.size is 0
     * @tc.expected: The PaintBackground executed successfuly
     */
    vectorBlackPointCenterX.clear();
    contentProperty.vectorBlackPointCenterX = vectorBlackPointCenterX;
    dotIndicatorModifier.PaintBackground(context, contentProperty);
}

/**
 * @tc.name: DotIndicatorModifier014
 * @tc.desc: Test CalCBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, DotIndicatorModifier014, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier dotIndicatorModifier;
    dotIndicatorModifier.longPointDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0f);
    dotIndicatorModifier.indicatorPadding_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10.0f);
    dotIndicatorModifier.indicatorMargin_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(5.0f, 5.0f));

    /**
     * @tc.steps: step2.Call CalCBoundsRect when vectorBlackPointCenterX_ is null
     */
    LinearVector<float> itemHalfSizes = {};
    dotIndicatorModifier.itemHalfSizes_ = AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(itemHalfSizes);
    auto result = dotIndicatorModifier.CalCBoundsRect();
    float rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, 0.0f);

    itemHalfSizes = { 15.0f, 20.0f, 25.0f, 30.0f };
    dotIndicatorModifier.itemHalfSizes_ = AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(itemHalfSizes);
    result = dotIndicatorModifier.CalCBoundsRect();
    rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, 0.0f);

    /**
     * @tc.steps: step3.Call CalCBoundsRect when vectorBlackPointCenterX_ is not null
     */
    dotIndicatorModifier.vectorBlackPointCenterX_ =
        AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float> { 100.0f, 200.0f, 300.0f });
    itemHalfSizes = {};
    dotIndicatorModifier.itemHalfSizes_ = AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(itemHalfSizes);
    result = dotIndicatorModifier.CalCBoundsRect();
    rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, 0.0f);

    itemHalfSizes = { 15.0f, 20.0f, 25.0f, 30.0f };
    dotIndicatorModifier.itemHalfSizes_ = AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(itemHalfSizes);
    result = dotIndicatorModifier.CalCBoundsRect();
    rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, 0.0f);

    /**
     * @tc.steps: step4.Call CalCBoundsRect when axis_ is Axis::VERTICAL
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    result = dotIndicatorModifier.CalCBoundsRect();
    rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, -30.0f);

    /**
     * @tc.steps: step5.Call CalCBoundsRect when targetVectorBlackPointCenterX_ is not null
     */
    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.targetVectorBlackPointCenterX_ = { 120.0f, 220.0f, 320.0f };
    result = dotIndicatorModifier.CalCBoundsRect();
    rectLeft = std::get<0>(result);
    EXPECT_EQ(rectLeft, 0.0f);
}

/**
 * @tc.name: CircleDotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set parameters.
     */
    CircleDotIndicatorModifier circleDotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawArc(_, _, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Restore()).Times(AnyNumber());
    circleDotIndicatorModifier.SetAxis(Axis::HORIZONTAL);
    circleDotIndicatorModifier.SetArcDirection(SwiperArcDirection::THREE_CLOCK_DIRECTION);
    circleDotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);

    /**
     * @tc.steps: step2. call onDraw.
     */
    circleDotIndicatorModifier.onDraw(context);
    EXPECT_EQ(circleDotIndicatorModifier.axis_, Axis::HORIZONTAL);
    EXPECT_EQ(circleDotIndicatorModifier.arcDirection_, SwiperArcDirection::THREE_CLOCK_DIRECTION);

    /**
     * @tc.steps: step3. set parameters.
     */
    circleDotIndicatorModifier.SetAxis(Axis::VERTICAL);
    circleDotIndicatorModifier.SetArcDirection(SwiperArcDirection::SIX_CLOCK_DIRECTION);
    circleDotIndicatorModifier.UpdateBackgroundColor(Color::RED);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.emplace_back(2.5f);
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    circleDotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, vectorBlackPointRadius,
                                                        {0.f, 0.f});

    /**
     * @tc.steps: step4. call onDraw.
     */
    circleDotIndicatorModifier.onDraw(context);
    EXPECT_EQ(circleDotIndicatorModifier.axis_, Axis::VERTICAL);
    EXPECT_EQ(circleDotIndicatorModifier.arcDirection_, SwiperArcDirection::SIX_CLOCK_DIRECTION);

    /**
     * @tc.steps: step5. set parameters.
     */
    circleDotIndicatorModifier.SetArcDirection(SwiperArcDirection::NINE_CLOCK_DIRECTION);
    circleDotIndicatorModifier.UpdateNormalToPressPaintProperty(itemHalfSizes, vectorBlackPointCenterX,
                                                                vectorBlackPointRadius, {0.f, 0.f});

    /**
     * @tc.steps: step6. call onDraw.
     */
    circleDotIndicatorModifier.onDraw(context);
    EXPECT_EQ(circleDotIndicatorModifier.arcDirection_, SwiperArcDirection::NINE_CLOCK_DIRECTION);
}

/**
 * @tc.name: CircleDotPlayIndicatorAnimation001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotPlayIndicatorAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    vectorBlackPointAngle.push_back(20.0f);
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.emplace_back(2.5f);
    vectorBlackPointRadius.emplace_back(2.5f);
    std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;

    /**
     * @tc.steps: step2. call PlayIndicatorAnimation.
     */
    modifier->PlayIndicatorAnimation(vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX, gestureState);
    longPointCenterX = { 1.0f, 1.0f };
    modifier->PlayIndicatorAnimation(vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX, gestureState);
    EXPECT_EQ(modifier->longPointLeftAnimEnd_, true);
}

/**
 * @tc.name: CircleDotIndicatorUpdateContentModifier001
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorUpdateContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->circleDotIndicatorModifier_->SetIsPressed(true);
    paintMethod->isLongPressed_ = true;

    /**
     * @tc.steps: step2. call UpdateContentModifier.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    paintMethod->circleDotIndicatorModifier_->SetIsPressed(false);
    paintMethod->isLongPressed_ = true;
    paintMethod->UpdateContentModifier(&paintWrapper);
    paintMethod->isLongPressed_ = false;
    paintMethod->UpdateContentModifier(&paintWrapper);
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->isLongPressed_ = false;
    paintMethod->UpdateContentModifier(&paintWrapper);
    paintMethod->circleDotIndicatorModifier_->SetIsPressed(true);
    paintMethod->isLongPressed_ = false;
    paintMethod->UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->axis_, Axis::HORIZONTAL);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->arcDirection_, SwiperArcDirection::SIX_CLOCK_DIRECTION);
}

/**
 * @tc.name: CircleDotIndicatorPaintNormalIndicator001
 * @tc.desc: Test CircleDotIndicatorPaintMethod PaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(500.f, 500.f));
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateContainerColor(Color::BLUE);
    paintProperty->UpdateArcDirection(SwiperArcDirection::NINE_CLOCK_DIRECTION);
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateSelectedColor(Color::GREEN);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->CalculateLongPointCenterAngle(&paintWrapper, false);
    paintMethod->circleDotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step2. call PaintNormalIndicator.
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->isPressed_, true);

    paintMethod->circleDotIndicatorModifier_->SetIsPressed(false);
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->isPressed_, false);
}

/**
 * @tc.name: CircleDotIndicatorPaintUnselectedIndicator001
 * @tc.desc: Test CircleDotIndicatorPaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorPaintUnselectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(20.0f);
    itemHalfSizes.push_back(20.0f);

    RSCanvas canvas;
    float itemAngle = -1.2f;
    float itemRadius = 2.5f;
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    /**
     * @tc.steps: step2. Call PaintUnselectedIndicator.
     */
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(
        canvas, itemAngle, itemRadius, contentProperty, LinearColor(Color::TRANSPARENT));
    EXPECT_EQ(modifier->arcDirection_, SwiperArcDirection::SIX_CLOCK_DIRECTION);

    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(
        canvas, itemAngle, itemRadius, contentProperty, LinearColor(Color::TRANSPARENT));
    EXPECT_EQ(modifier->arcDirection_, SwiperArcDirection::THREE_CLOCK_DIRECTION);

    modifier->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(
        canvas, itemAngle, itemRadius, contentProperty, LinearColor(Color::TRANSPARENT));
    EXPECT_EQ(modifier->arcDirection_, SwiperArcDirection::NINE_CLOCK_DIRECTION);
}

/**
 * @tc.name: CircleDotIndicatorCalculatePointAngle001
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorCalculatePointAngle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod->itemCount_ = 1;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    vectorBlackPointAngle.push_back(20.0f);
    paintMethod->vectorBlackPointAngle_ = vectorBlackPointAngle;
    LinearVector<float> itemSizes;
    itemSizes.emplace_back(20.f);
    itemSizes.emplace_back(20.f);

    /**
     * @tc.steps: step2. Call CalculatePointAngle.
     */
    paintMethod->CalculatePointAngle(itemSizes, 0);
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_.size(), 1);
}

/**
 * @tc.name: CircleDotIndicatorGetHalfIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetHalfIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorGetHalfIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->itemCount_ = 2;

    /**
     * @tc.steps: step2. Call GetHalfIndex.
     */
    EXPECT_EQ(paintMethod->GetHalfIndex(), 0);
    paintMethod->itemCount_ = 3;
    EXPECT_EQ(paintMethod->GetHalfIndex(), 1);
}

/**
 * @tc.name: CircleDotIndicatorGetLongPointAngle001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetLongPointAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorGetLongPointAngle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->CreateCircleDotIndicatorPaintMethod(pattern_);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    LinearVector<float> itemSizes;
    itemSizes.emplace_back(20.f);
    itemSizes.emplace_back(20.f);
    int32_t indicatorStartIndex = 0;

    /**
     * @tc.steps: step2. Call GetLongPointAngle.
     */
    paintMethod->GetLongPointAngle(itemSizes, 0, indicatorStartIndex);
    EXPECT_EQ(paintMethod->arcDirection_, SwiperArcDirection::THREE_CLOCK_DIRECTION);
    paintMethod->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    paintMethod->GetLongPointAngle(itemSizes, 0, indicatorStartIndex);
    EXPECT_EQ(paintMethod->arcDirection_, SwiperArcDirection::NINE_CLOCK_DIRECTION);
}

/**
 * @tc.name: CircleDotIndicatorGetBlackPointAngle001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetBlackPointAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorGetBlackPointAngle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->CreateCircleDotIndicatorPaintMethod(pattern_);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod->itemCount_ = 16;
    LinearVector<float> itemSizes;
    itemSizes.emplace_back(2.5f); // ITEM_SHRINK_RADIUS
    itemSizes.emplace_back(2.5f); // SLECTED_ITEM_SHRINK_RADIUS
    itemSizes.emplace_back(8.0f); // ONTAINER_SHRINK_RADIUS
    itemSizes.emplace_back(5.0f); // ITEM_SHRINK_PADDING
    itemSizes.emplace_back(7.0f); // SELECTED_ITEM_SHRINK_PADDING
    itemSizes.emplace_back(4.0f); // ACTIVE_ITEM_SHRINK_ANGLE
    itemSizes.emplace_back(4.5f); // ITEM_SHRINK_MINOR_PADDING
    itemSizes.emplace_back(4.0f); // ITEM_SHRINK_MINI_PADDING

    /**
     * @tc.steps: step2. Call GetBlackPointAngle.
     */
    int32_t indicatorStartIndex = 0;
    LinearVector<float> vectorBlackPointAngle = {};
    vectorBlackPointAngle.resize(paintMethod->itemCount_);
    for (int32_t i = 0; i < paintMethod->itemCount_; ++i) {
        float offset = paintMethod->CalculateBlackPointRotateAngle(indicatorStartIndex, i);
        vectorBlackPointAngle[i] = paintMethod->GetBlackPointAngle(itemSizes, i, 0, offset);
    }
    EXPECT_EQ(vectorBlackPointAngle[0], 35);
    EXPECT_EQ(vectorBlackPointAngle[1], 28);
    EXPECT_EQ(vectorBlackPointAngle[2], 23);
    EXPECT_EQ(vectorBlackPointAngle[3], 18);
    EXPECT_EQ(vectorBlackPointAngle[4], 13);
    EXPECT_EQ(vectorBlackPointAngle[5], 8);
    EXPECT_EQ(vectorBlackPointAngle[6], 3);
    EXPECT_EQ(vectorBlackPointAngle[7], -2);
    EXPECT_EQ(vectorBlackPointAngle[8], -7);
    EXPECT_EQ(vectorBlackPointAngle[9], -12);
    EXPECT_EQ(vectorBlackPointAngle[10], -17);
    EXPECT_EQ(vectorBlackPointAngle[11], -22);
    EXPECT_EQ(vectorBlackPointAngle[12], -27);
    EXPECT_EQ(vectorBlackPointAngle[13], -32);
    EXPECT_EQ(vectorBlackPointAngle[14], -37);
    EXPECT_EQ(vectorBlackPointAngle[15], -40.5);
}

/**
 * @tc.name: CircleDotIndicatorGetIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorGetIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->CreateCircleDotIndicatorPaintMethod(pattern_);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod->nextValidIndex_ = 1;
    paintMethod->turnPageRate_ = 0.5f;

    /**
     * @tc.steps: step2. Call GetIndex.
     */
    EXPECT_EQ(paintMethod->GetIndex(2).first, paintMethod->currentIndexActual_);
    paintMethod->nextValidIndex_ = -1;
    EXPECT_EQ(paintMethod->GetIndex(0).first, 0);
    paintMethod->turnPageRate_ = 0.0f;
    EXPECT_EQ(paintMethod->GetIndex(-1).first, -1);
    paintMethod->itemCount_ = 1;
    EXPECT_EQ(paintMethod->GetIndex(0).first, 0);
}

/**
 * @tc.name: CircleDotIndicatorGetStartAndEndIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetStartAndEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorGetStartAndEndIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->CreateCircleDotIndicatorPaintMethod(pattern_);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    RefPtr<CircleDotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;

    /**
     * @tc.steps: step2. Call GetStartAndEndIndex.
     */
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(0).first, 0);
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(0).first, 0);
    paintMethod->nextValidIndex_ = 1;
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(-1).first, -1);
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    paintMethod->GetStartAndEndIndex(0);
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(0).first, -1);
}

/**
 * @tc.name: CircleDotIndicatorSetFunctions001
 * @tc.desc: Test CircleDotIndicatorPaintMethod Set Functions
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, CircleDotIndicatorSetFunctions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::ARC_DOT);
    auto indicatorpaintMethod = indicatorPattern->CreateCircleDotIndicatorPaintMethod(pattern_);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(indicatorPattern->CreateNodePaintMethod());

    /**
     * @tc.steps: step2. Call Set Functions.
     */
    indicatorpaintMethod->SetCurrentIndex(1);
    EXPECT_EQ(indicatorpaintMethod->currentIndex_, 1);
    indicatorpaintMethod->SetItemCount(1);
    EXPECT_EQ(indicatorpaintMethod->itemCount_, 1);
    paintMethod->SetAxis(Axis::HORIZONTAL);
    EXPECT_EQ(paintMethod->GetAxis(), Axis::HORIZONTAL);
    paintMethod->SetIsLongPressed(true);
    EXPECT_EQ(paintMethod->isLongPressed_, true);
    paintMethod->SetTurnPageRate(1.0f);
    EXPECT_EQ(paintMethod->turnPageRate_, 1.0f);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_LEFT);
    EXPECT_EQ(paintMethod->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);
    paintMethod->SetTouchBottomTypeLoop(TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    EXPECT_EQ(paintMethod->touchBottomTypeLoop_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
    paintMethod->SetMouseClickIndex(1);
    EXPECT_EQ(paintMethod->mouseClickIndex_, 1);
    paintMethod->SetPointAnimationStage(PointAnimationStage::STATE_EXPAND_TO_LONG_POINT);
    EXPECT_EQ(paintMethod->pointAnimationStage_, PointAnimationStage::STATE_EXPAND_TO_LONG_POINT);
    paintMethod->SetCurrentIndexActual(1);
    EXPECT_EQ(paintMethod->currentIndexActual_, 1);
    paintMethod->SetNextValidIndex(1);
    EXPECT_EQ(paintMethod->nextValidIndex_, 1);
}

/**
 * @tc.name: UpdateContentProperty001
 * @tc.desc: Test UpdateContentProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestTwoNg, UpdateContentProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indicator modifier.
     */
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    modifier->itemHalfSizes_->Set({ 0.0f, 0.0f, 0.0f, 0.0f });
    modifier->indicatorMargin_->Set({ 0.0f, 0.0f });
    modifier->longPointLeftCenterX_->Set(0.0f);
    modifier->longPointRightCenterX_->Set(0.0f);

    auto contentProperty = modifier->UpdateContentProperty();
    EXPECT_EQ(contentProperty.itemHalfSizes, modifier->itemHalfSizes_->Get());
    EXPECT_EQ(contentProperty.indicatorMargin, modifier->indicatorMargin_->Get());
    EXPECT_EQ(contentProperty.longPointLeftCenterX, modifier->longPointLeftCenterX_->Get());
    EXPECT_EQ(contentProperty.longPointRightCenterX, modifier->longPointRightCenterX_->Get());
    /**
     * @tc.steps: step2. update targetContentProperty_ and check result.
     */
    LinearVector<float> itemHalfSizes = { 1.0f, 1.0f, 1.0f, 1.0f };
    OffsetF indicatorMargin = { 1.0f, 1.0f };
    float longPointLeftCenterX = 1.0f;
    float longPointRightCenterX = 1.0f;
    modifier->targetContentProperty_.itemHalfSizes = itemHalfSizes;
    modifier->targetContentProperty_.indicatorMargin = indicatorMargin;
    modifier->targetContentProperty_.longPointLeftCenterX = longPointLeftCenterX;
    modifier->targetContentProperty_.longPointRightCenterX = longPointRightCenterX;
    contentProperty = modifier->UpdateContentProperty();
    EXPECT_EQ(contentProperty.itemHalfSizes, itemHalfSizes);
    EXPECT_EQ(contentProperty.indicatorMargin, indicatorMargin);
    EXPECT_EQ(contentProperty.longPointLeftCenterX, longPointLeftCenterX);
    EXPECT_EQ(contentProperty.longPointRightCenterX, longPointRightCenterX);
}
} // namespace OHOS::Ace::NG
