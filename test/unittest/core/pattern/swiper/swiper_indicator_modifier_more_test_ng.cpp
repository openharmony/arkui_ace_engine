/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
class SwiperIndicatorModifierMoreTestNg : public SwiperTestNg {
public:
};

 /**
 * @tc.name: PaintContent001
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.longPointLeftCenterX = 20.0f;
    contentProperty.longPointRightCenterX = 30.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_FALSE(NearZero(contentProperty.longPointLeftCenterX));
    EXPECT_FALSE(NearZero(contentProperty.longPointRightCenterX));
}

/**
 * @tc.name: PaintContent002
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.longPointLeftCenterX = 0.0f;
    contentProperty.longPointRightCenterX = 30.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_TRUE(NearZero(contentProperty.longPointLeftCenterX));
    EXPECT_FALSE(NearZero(contentProperty.longPointRightCenterX));
}

/**
 * @tc.name: PaintContent003
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.longPointLeftCenterX = 0.0f;
    contentProperty.longPointRightCenterX = 0.0f;
    LinearVector<float> itemHalfSizes = { 20.f, 30.f, 40.f, 50.f };
    contentProperty.itemHalfSizes = itemHalfSizes;
    DotIndicatorModifier dotIndicatorModifier;
    contentProperty.backgroundColor.colorValue_.value = 0xff000000;
    dotIndicatorModifier.backgroundWidthDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10.0f);
    dotIndicatorModifier.backgroundHeightDilateRatio_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20.0f);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    /**
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_TRUE(NearZero(contentProperty.longPointLeftCenterX));
    EXPECT_TRUE(NearZero(contentProperty.longPointRightCenterX));
}

/**
 * @tc.name: PaintContent004
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 10.0f };
    contentProperty.longPointLeftCenterX = 10.0f;
    contentProperty.longPointRightCenterX = 20.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.currentIndex_ = 0;
    dotIndicatorModifier.isTouchBottomLoop_ = false;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_NE(contentProperty.vectorBlackPointCenterX.size(), 0);
}

/**
 * @tc.name: PaintContent005
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 10.0f };
    contentProperty.longPointLeftCenterX = 10.0f;
    contentProperty.longPointRightCenterX = 20.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.currentIndex_ = 0;
    dotIndicatorModifier.isTouchBottomLoop_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_NE(contentProperty.vectorBlackPointCenterX.size(), 0);
}

/**
 * @tc.name: PaintContent006
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 10.0f, 20.0f };
    contentProperty.longPointLeftCenterX = 10.0f;
    contentProperty.longPointRightCenterX = 20.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.currentIndex_ = 1;
    dotIndicatorModifier.isTouchBottomLoop_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_NE(contentProperty.vectorBlackPointCenterX.size(), 0);
}

/**
 * @tc.name: PaintContent007
 * @tc.desc: Test PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PaintContent007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Create dotIndicatorModifier and ContentProperty attributes
     */
    DotIndicatorModifier::ContentProperty contentProperty;
    contentProperty.vectorBlackPointCenterX = { 10.0f };
    contentProperty.longPointLeftCenterX = 10.0f;
    contentProperty.longPointRightCenterX = 20.0f;
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
     * @tc.steps: step2.Call PaintContent
     * @tc.expected: The PaintContent executed successfully
     */
    dotIndicatorModifier.axis_ = Axis::HORIZONTAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.currentIndex_ = 1;
    dotIndicatorModifier.isTouchBottomLoop_ = true;
    dotIndicatorModifier.PaintContent(context, contentProperty);
    dotIndicatorModifier.PaintContent(context, contentProperty);
    EXPECT_NE(contentProperty.vectorBlackPointCenterX.size(), 0);
}

/**
 * @tc.name: GetMoveRate002
 * @tc.desc: Test DotIndicatorPaintMethod GetMoveRate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, GetMoveRate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    paintMethod->isPressed_ = true;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->GetMoveRate();
    EXPECT_FALSE(paintMethod->isPressed_ &&
                 paintMethod->touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX003
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, SwiperIndicatorCalculatePointCenterX003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->turnPageRate_ = 110.0f;
    paintMethod->IsCustomSizeValue_ = false;
    paintMethod->isHorizontalAndRightToLeft_ = true;
    auto result = paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

/**
 * @tc.name: CalculateHoverIndex001
 * @tc.desc: Test DotIndicatorPaintMethod CalculateHoverIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, CalculateHoverIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step2. call CalculateHoverIndex.
     * @tc.expected: run success
     */
    paintMethod->vectorBlackPointCenterX_.push_back(20.0f);
    paintMethod->axis_ = Axis::HORIZONTAL;
    paintMethod->isHover_ = true;
    paintMethod->hoverIndex_ = 10;
    paintMethod->centerY_ = 0;
    paintMethod->hoverPoint_ = { 0.0f, 0.0f };
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    paintMethod->CalculateHoverIndex(itemHalfSizes);
    EXPECT_NE(paintMethod->hoverIndex_, 0);
}

/**
 * @tc.name: CalculateHoverIndex002
 * @tc.desc: Test DotIndicatorPaintMethod CalculateHoverIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, CalculateHoverIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step2. call CalculateHoverIndex.
     * @tc.expected: run success
     */
    paintMethod->vectorBlackPointCenterX_.push_back(20.0f);
    paintMethod->axis_ = Axis::HORIZONTAL;
    paintMethod->isHover_ = true;
    paintMethod->hoverIndex_ = 10;
    paintMethod->centerY_ = 0;
    paintMethod->hoverPoint_ = { 20.0f, 0.0f };
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    paintMethod->CalculateHoverIndex(itemHalfSizes);
    EXPECT_EQ(paintMethod->hoverIndex_, 0);
}

/**
 * @tc.name: isHoverPoint
 * @tc.desc: Test DotIndicatorPaintMethod isHoverPoint
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, isHoverPoint, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step2. call isHoverPoint.
     * @tc.expected: run success
     */
    paintMethod->vectorBlackPointCenterX_.push_back(20.0f);
    paintMethod->axis_ = Axis::HORIZONTAL;
    paintMethod->isHover_ = true;
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->centerY_ = 0;
    paintMethod->hoverPoint_ = { 20.0f, 0.0f };
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    itemHalfSizes.push_back(0.0f);
    OffsetF leftCenter = { 20.0f, 0.0f };
    OffsetF rightCenter = { 20.0f, 0.0f };
    auto result = paintMethod->isHoverPoint(paintMethod->hoverPoint_, leftCenter, rightCenter, itemHalfSizes);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SwiperIndicatorUpdateBackgroundX002
 * @tc.desc: Test DotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, SwiperIndicatorUpdateBackgroundX002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->touchBottomType_ = TouchBottomType::NONE;
    paintMethod->itemCount_ = 10;
    /**
     * @tc.steps: step3. call UpdateBackground.
     * @tc.expected: run success
     */
    paintMethod->UpdateBackground(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorUpdateBackgroundX003
 * @tc.desc: Test DotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, SwiperIndicatorUpdateBackgroundX003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->touchBottomType_ = TouchBottomType::START;
    paintMethod->itemCount_ = 10;
    /**
     * @tc.steps: step3. call UpdateBackground.
     * @tc.expected: run success
     */
    paintMethod->UpdateBackground(&paintWrapper);
}

/**
 * @tc.name: UpdateAllPointCenterXAnimation001
 * @tc.desc: Test DotIndicatorModifier UpdateAllPointCenterXAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, UpdateAllPointCenterXAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX = { 10.0f };
    std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    modifier->longPointLeftAnimEnd_ = false;
    GestureState gestureState = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    /**
     * @tc.steps: step3. call UpdateAllPointCenterXAnimation.
     * @tc.expected: run success
     */
    modifier->UpdateAllPointCenterXAnimation(gestureState, vectorBlackPointCenterX, longPointCenterX);
}

/**
 * @tc.name: UpdateAllPointCenterXAnimation002
 * @tc.desc: Test DotIndicatorModifier UpdateAllPointCenterXAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, UpdateAllPointCenterXAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX = { 10.0f };
    std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    GestureState gestureState = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    /**
     * @tc.steps: step3. call UpdateAllPointCenterXAnimation.
     * @tc.expected: run success
     */
    modifier->UpdateAllPointCenterXAnimation(gestureState, vectorBlackPointCenterX, longPointCenterX);
}

/**
 * @tc.name: UpdateTouchBottomAnimation
 * @tc.desc: Test DotIndicatorModifier UpdateTouchBottomAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, UpdateTouchBottomAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX = { 10.0f };
    std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    modifier->touchBottomType_ = TouchBottomType::NONE;
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    TouchBottomType touchBottomType = TouchBottomType::START;
    /**
     * @tc.steps: step3. call UpdateTouchBottomAnimation.
     * @tc.expected: run success
     */
    modifier->UpdateTouchBottomAnimation(touchBottomType, vectorBlackPointCenterX, longPointCenterX, 10.0f);
    EXPECT_EQ(modifier->touchBottomType_, TouchBottomType::START);
}

/**
 * @tc.name: PlayTouchBottomAnimation
 * @tc.desc: Test DotIndicatorModifier PlayTouchBottomAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PlayTouchBottomAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX = {};
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };
    modifier->touchBottomType_ = TouchBottomType::START;
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    TouchBottomTypeLoop touchBottomTypeLoop = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    /**
     * @tc.steps: step3. call PlayTouchBottomAnimation.
     * @tc.expected: run success
     */
    modifier->PlayTouchBottomAnimation(longPointCenterX, touchBottomTypeLoop, vectorBlackPointCenterX);
    EXPECT_EQ(modifier->touchBottomType_, TouchBottomType::START);
}

/**
 * @tc.name: PlayLongPointAnimation003
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PlayLongPointAnimation003, TestSize.Level1)
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
    modifier->longPointLeftAnimEnd_ = false;
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    modifier->PlayLongPointAnimation(
        longPointCenterX, gestureState, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(gestureState == GestureState::GESTURE_STATE_RELEASE_LEFT);
}

/**
 * @tc.name: PlayLongPointAnimation004
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, PlayLongPointAnimation004, TestSize.Level1)
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
    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->userSetSwiperCurve_ = AceType::MakeRefPtr<InterpolatingSpring>(0.1f, 0.1f, 0.1f, 0.1f);
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    modifier->PlayLongPointAnimation(
        longPointCenterX, gestureState, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(gestureState == GestureState::GESTURE_STATE_RELEASE_LEFT);
}

/**
 * @tc.name: GetTailCurve001
 * @tc.desc: Test DotIndicatorModifier GetTailCurve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, GetTailCurve001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    modifier->currentIndex_ = 3;
    modifier->currentIndexActual_ = 0;
    /**
     * @tc.steps: step3. call GetTailCurve.
     * @tc.expected: run success
     */
    auto result = modifier->GetTailCurve();
    EXPECT_EQ(result->stiffness_, 128);
    EXPECT_EQ(result->damping_, 18);
}

/**
 * @tc.name: GetTailCurve002
 * @tc.desc: Test DotIndicatorModifier GetTailCurve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, GetTailCurve002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    modifier->currentIndex_ = 4;
    modifier->currentIndexActual_ = 0;
    /**
     * @tc.steps: step3. call GetTailCurve.
     * @tc.expected: run success
     */
    auto result = modifier->GetTailCurve();
    EXPECT_EQ(result->stiffness_, 128);
    EXPECT_EQ(result->damping_, 20);
}

/**
 * @tc.name: GetTailCurve003
 * @tc.desc: Test DotIndicatorModifier GetTailCurve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierMoreTestNg, GetTailCurve003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    modifier->currentIndex_ = 5;
    modifier->currentIndexActual_ = 0;
    /**
     * @tc.steps: step3. call GetTailCurve.
     * @tc.expected: run success
     */
    auto result = modifier->GetTailCurve();
    EXPECT_EQ(result->stiffness_, 148);
    EXPECT_EQ(result->damping_, 28);
}
} // namespace OHOS::Ace::NG