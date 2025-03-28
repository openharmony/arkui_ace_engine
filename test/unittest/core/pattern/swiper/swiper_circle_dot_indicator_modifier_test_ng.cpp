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

#include <gtest/gtest.h>

#include "swiper_test_ng.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "core/components_ng/pattern/swiper/swiper_paint_method.h"

namespace OHOS::Ace::NG {
class CircleDotIndicatorModifierTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: GetArcPoint001
 * @tc.desc: Test GetArcPoint
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetArcPoint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    modifier->axis_ = Axis::HORIZONTAL;
    modifier->GetArcPoint(contentProperty);
    auto a = modifier->GetArcPoint(contentProperty);
    EXPECT_EQ(a.first.GetX(), 0.0f);
}

/**
 * @tc.name: GetArcPoint001
 * @tc.desc: Test GetArcPoint
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetArcPoint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    modifier->axis_ = Axis::VERTICAL;
    modifier->GetArcPoint(contentProperty);
    auto a = modifier->GetArcPoint(contentProperty);
    EXPECT_EQ(a.first.GetX(), 0.0f);
}

/**
 * @tc.name: PaintBackground001
 * @tc.desc: Test PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackground001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    for (int i = 0; i < 20; i++) {
        vectorBlackPointAngle.push_back(20.0f);
    }
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::START;
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintBackground(context, contentProperty);
}

/**
 * @tc.name: PaintBackground002
 * @tc.desc: Test PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackground002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::NONE;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintBackground(context, contentProperty);
}

/**
 * @tc.name: PaintBackground003
 * @tc.desc: Test PaintBackground
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackground003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle = vectorBlackPointAngle;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::START;
    modifier->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    modifier->PaintBackground(context, contentProperty);
}

/**
 * @tc.name: PaintBackgroundSetAngle001
 * @tc.desc: Test PaintBackgroundSetAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackgroundSetAngle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float backgroundOffset = 10;
    float startAngle = 0;
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::NONE;
    modifier->currentIndex_ = 1;
    modifier->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    modifier->PaintBackgroundSetAngle(itemSize, backgroundOffset, startAngle);
    EXPECT_EQ(startAngle, 10.0f);
}

/**
 * @tc.name: PaintBackgroundSetAngle002
 * @tc.desc: Test PaintBackgroundSetAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackgroundSetAngle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float backgroundOffset = 10;
    float startAngle = 0;
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::NONE;
    modifier->currentIndex_ = 100;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintBackgroundSetAngle(itemSize, backgroundOffset, startAngle);
    EXPECT_EQ(startAngle, 0.0f);
}

/**
 * @tc.name: PaintBackgroundSetAngle003
 * @tc.desc: Test PaintBackgroundSetAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackgroundSetAngle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float backgroundOffset = 10;
    float startAngle = 0;
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::NONE;
    modifier->currentIndex_ = 1;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintBackgroundSetAngle(itemSize, backgroundOffset, startAngle);
    EXPECT_EQ(startAngle, -10.0f);
}

/**
 * @tc.name: PaintBackgroundSetAngle004
 * @tc.desc: Test PaintBackgroundSetAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintBackgroundSetAngle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float backgroundOffset = 10;
    float startAngle = 0;
    modifier->axis_ = Axis::VERTICAL;
    modifier->touchBottomType_ = TouchBottomType::START;
    modifier->currentIndex_ = 1;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintBackgroundSetAngle(itemSize, backgroundOffset, startAngle);
    EXPECT_EQ(startAngle, 0.0f);
}

/**
 * @tc.name: GetAllPointArcAngle001
 * @tc.desc: Test GetAllPointArcAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetAllPointArcAngle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float dotPaddingAngle = 10.0f;
    float dotActivePaddingAngle = 10.0f;
    float dotActiveAngle = 10.0f;
    modifier->currentIndex_ = -100;
    auto result = modifier->GetAllPointArcAngle(itemSize, dotPaddingAngle, dotActivePaddingAngle, dotActiveAngle);
    EXPECT_EQ(result, 170);
}

/**
 * @tc.name: GetAllPointArcAngle002
 * @tc.desc: Test GetAllPointArcAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetAllPointArcAngle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float dotPaddingAngle = 10.0f;
    float dotActivePaddingAngle = 10.0f;
    float dotActiveAngle = 10.0f;
    modifier->currentIndex_ = 0;
    auto result = modifier->GetAllPointArcAngle(itemSize, dotPaddingAngle, dotActivePaddingAngle, dotActiveAngle);
    EXPECT_EQ(result, 175);
}

/**
 * @tc.name: GetAllPointArcAngle003
 * @tc.desc: Test GetAllPointArcAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetAllPointArcAngle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 20;
    float dotPaddingAngle = 10.0f;
    float dotActivePaddingAngle = 10.0f;
    float dotActiveAngle = 10.0f;
    modifier->currentIndex_ = 19;
    auto result = modifier->GetAllPointArcAngle(itemSize, dotPaddingAngle, dotActivePaddingAngle, dotActiveAngle);
    EXPECT_EQ(result, 175);
}

/**
 * @tc.name: GetAllPointArcAngle004
 * @tc.desc: Test GetAllPointArcAngle
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetAllPointArcAngle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    int32_t itemSize = 0;
    float dotPaddingAngle = 10.0f;
    float dotActivePaddingAngle = 10.0f;
    float dotActiveAngle = 10.0f;
    modifier->currentIndex_ = 0;
    auto result = modifier->GetAllPointArcAngle(itemSize, dotPaddingAngle, dotActivePaddingAngle, dotActiveAngle);
    EXPECT_EQ(result, 10);
}

/**
 * @tc.name: GetMaskColor001
 * @tc.desc: Test GetMaskColor
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetMaskColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    modifier->currentIndex_ = 0;
    auto result = modifier->GetMaskColor();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: GetMaskColor002
 * @tc.desc: Test GetMaskColor
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, GetMaskColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    modifier->currentIndex_ = 0;
    modifier->maskColor_.ClearColors();
    auto srcGradientColors = modifier->maskColor_.GetColors();
    auto result = modifier->GetMaskColor();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: PaintIndicatorMask001
 * @tc.desc: Test PaintIndicatorMask
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintIndicatorMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).Times(AtLeast(1)).WillRepeatedly(ReturnRef(canvas));
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintIndicatorMask(context, contentProperty);
}

/**
 * @tc.name: PaintIndicatorMask002
 * @tc.desc: Test PaintIndicatorMask
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintIndicatorMask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).Times(AtLeast(1)).WillRepeatedly(ReturnRef(canvas));
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintIndicatorMask(context, contentProperty);
}

/**
 * @tc.name: PaintIndicatorMask003
 * @tc.desc: Test PaintIndicatorMask
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintIndicatorMask003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).Times(AtLeast(1)).WillRepeatedly(ReturnRef(canvas));
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    modifier->PaintIndicatorMask(context, contentProperty);
}

/**
 * @tc.name: PaintIndicatorMask004
 * @tc.desc: Test PaintIndicatorMask
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintUnselectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    RSCanvas canvas;
    float itemAngle = 20.0f;
    float itemRadius = 20.0f;
    LinearColor indicatorColor;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(canvas, itemAngle, itemRadius, contentProperty, indicatorColor);
}

/**
 * @tc.name: PaintUnselectedIndicator002
 * @tc.desc: Test PaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintUnselectedIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    RSCanvas canvas;
    float itemAngle = 20.0f;
    float itemRadius = 20.0f;
    LinearColor indicatorColor;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(canvas, itemAngle, itemRadius, contentProperty, indicatorColor);
}

/**
 * @tc.name: PaintUnselectedIndicator003
 * @tc.desc: Test PaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintUnselectedIndicator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    RSCanvas canvas;
    float itemAngle = 20.0f;
    float itemRadius = 20.0f;
    LinearColor indicatorColor;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    modifier->PaintUnselectedIndicator(canvas, itemAngle, itemRadius, contentProperty, indicatorColor);
}

/**
 * @tc.name: PaintUnselectedIndicator004
 * @tc.desc: Test PaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, UpdateShrinkPaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.push_back(20.0f);
    vectorBlackPointRadius.push_back(20.0f);
    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(
        normalItemHalfSizes, vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PaintUnselectedIndicator005
 * @tc.desc: Test PaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, UpdateShrinkPaintProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.push_back(20.0f);
    vectorBlackPointRadius.push_back(20.0f);
    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(
        normalItemHalfSizes, vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PaintUnselectedIndicator006
 * @tc.desc: Test PaintUnselectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, UpdateShrinkPaintProperty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.push_back(20.0f);
    vectorBlackPointRadius.push_back(20.0f);
    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->isFirstPaintLongPoint_ = false;
    modifier->UpdateShrinkPaintProperty(
        normalItemHalfSizes, vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PaintSelectedIndicator001
 * @tc.desc: Test PaintSelectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintSelectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointAngle.clear();
    contentProperty.dotPaddingAngle = 20.0f;
    RSCanvas canvas;
    modifier->currentIndex_ = 0;
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintSelectedIndicator(canvas, contentProperty);
    EXPECT_EQ(contentProperty.vectorBlackPointAngle.size(), 0);
}

/**
 * @tc.name: PaintSelectedIndicator002
 * @tc.desc: Test PaintSelectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintSelectedIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.dotPaddingAngle = 20.0f;
    RSCanvas canvas;
    modifier->isFirstPaintLongPoint_ = false;
    modifier->axis_ = Axis::VERTICAL;
    modifier->arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    modifier->PaintSelectedIndicator(canvas, contentProperty);
    EXPECT_NE(contentProperty.vectorBlackPointAngle.size(), 0);
}

/**
 * @tc.name: PaintSelectedIndicator003
 * @tc.desc: Test PaintSelectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintSelectedIndicator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.dotActiveStartAngle = 20.0f;
    RSCanvas canvas;
    modifier->isFirstPaintLongPoint_ = true;
    modifier->axis_ = Axis::HORIZONTAL;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->firstDotActiveStartAngle_ = 10.0f;
    modifier->PaintSelectedIndicator(canvas, contentProperty);
    EXPECT_TRUE(modifier->isFirstPaintLongPoint_);
}

/**
 * @tc.name: PaintSelectedIndicator004
 * @tc.desc: Test PaintSelectedIndicator
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PaintSelectedIndicator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    CircleDotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointAngle.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.vectorBlackPointRadius.push_back(20.0f);
    contentProperty.dotActiveStartAngle = 20.0f;
    RSCanvas canvas;
    modifier->isFirstPaintLongPoint_ = true;
    modifier->axis_ = Axis::HORIZONTAL;
    modifier->arcDirection_ = SwiperArcDirection::THREE_CLOCK_DIRECTION;
    modifier->firstDotActiveStartAngle_ = 40.0f;
    modifier->PaintSelectedIndicator(canvas, contentProperty);
    EXPECT_TRUE(modifier->isFirstPaintLongPoint_);
}

/**
 * @tc.name: UpdateDilatePaintProperty001
 * @tc.desc: Test UpdateDilatePaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, UpdateDilatePaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.push_back(20.0f);
    vectorBlackPointRadius.push_back(20.0f);
    LinearVector<float> hoverItemSizes;
    hoverItemSizes.emplace_back(20.f);
    hoverItemSizes.emplace_back(20.f);
    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    modifier->isFirstPaintLongPoint_ = true;
    modifier->axis_ = Axis::HORIZONTAL;
    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(
        hoverItemSizes, vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: UpdateDilatePaintProperty002
 * @tc.desc: Test UpdateDilatePaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, UpdateDilatePaintProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    LinearVector<float> vectorBlackPointRadius;
    vectorBlackPointRadius.push_back(20.0f);
    vectorBlackPointRadius.push_back(20.0f);
    LinearVector<float> hoverItemSizes;
    hoverItemSizes.emplace_back(20.f);
    hoverItemSizes.emplace_back(20.f);
    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    vectorBlackPointAngle.emplace_back(3.f);
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(
        hoverItemSizes, vectorBlackPointAngle, vectorBlackPointRadius, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PlayLongPointAnimation001
 * @tc.desc: Test PlayLongPointAnimation
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PlayLongPointAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();

    /**
     * @tc.steps: step2. call PlayLongPointAnimation.
     */
    const std::pair<float, float> longPointAngle = { 0.0f, 0.0f };
    GestureState gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(20.f);
    vectorBlackPointAngle.emplace_back(20.f);
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->PlayLongPointAnimation(longPointAngle, gestureState, vectorBlackPointAngle);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ || modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PlayLongPointAnimation002
 * @tc.desc: Test PlayLongPointAnimation
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PlayLongPointAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();

    /**
     * @tc.steps: step2. call PlayLongPointAnimation.
     */
    const std::pair<float, float> longPointAngle = { 0.0f, 0.0f };
    GestureState gestureState = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(20.f);
    vectorBlackPointAngle.emplace_back(20.f);
    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = true;
    modifier->PlayLongPointAnimation(longPointAngle, gestureState, vectorBlackPointAngle);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ || modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PlayLongPointAnimation003
 * @tc.desc: Test PlayLongPointAnimation
 * @tc.type: FUNC
 */
HWTEST_F(CircleDotIndicatorModifierTestNg, PlayLongPointAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();

    /**
     * @tc.steps: step2. call PlayLongPointAnimation.
     */
    const std::pair<float, float> longPointAngle = { 0.0f, 0.0f };
    GestureState gestureState = GestureState::GESTURE_STATE_INIT;
    LinearVector<float> vectorBlackPointAngle;
    vectorBlackPointAngle.emplace_back(20.f);
    vectorBlackPointAngle.emplace_back(20.f);
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->PlayLongPointAnimation(longPointAngle, gestureState, vectorBlackPointAngle);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ || modifier->longPointRightAnimEnd_);
}
} // namespace OHOS::Ace::NG