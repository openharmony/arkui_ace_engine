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
} // namespace OHOS::Ace::NG