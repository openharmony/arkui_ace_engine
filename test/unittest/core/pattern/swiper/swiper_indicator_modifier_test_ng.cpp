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
class SwiperIndicatorModifierTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     * @tc.steps: step3. call GetContentModifier.
     */
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper);
    RefPtr<Modifier> ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    ASSERT_NE(ptrModifier, nullptr);
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isPressed_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isPressed_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorUpdateContentModifier003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;
    paintMethod->touchBottomType_ = TouchBottomType::START;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorUpdateContentModifier004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;
    paintMethod->touchBottomType_ = TouchBottomType::START;
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
    * @tc.steps: step3. call GetContentModifier.
    * @tc.expected: dotIndicatorModifier_->isPressed_ is true.
    */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier001, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
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

    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
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

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(25.f);
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(15.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesSecond, vectorBlackPointCenterX, { 0.f, 0.f });
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
}

/**
 * @tc.name: DotIndicatorModifier002
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier002, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);

    // ITEM_HALF_WIDTH != SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT > SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> normalItemHalfSizesThird;
    normalItemHalfSizesThird.emplace_back(20.f);
    normalItemHalfSizesThird.emplace_back(10.f);
    normalItemHalfSizesThird.emplace_back(30.f);
    normalItemHalfSizesThird.emplace_back(35.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesThird, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier003
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier003, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
    // call the UpdateHoverPaintProperty to set property.
    dotIndicatorModifier.UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier004
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier004, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(canvas, Save()).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.PaintMask(context);
}

/**
 * @tc.name: DotIndicatorModifier005
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier005, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::END;
    dotIndicatorModifier.onDraw(context);
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter002
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetLongPointAnimationStateSecondCenter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    LinearVector<float> longPointCenterX;
    longPointCenterX.push_back(20.0f);
    longPointCenterX.push_back(20.0f);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->UpdateNormalIndicator(longPointCenterX, &paintWrapper);
    EXPECT_TRUE(paintMethod->gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->UpdateNormalIndicator(longPointCenterX, &paintWrapper);
    EXPECT_TRUE(paintMethod->gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
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
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 342.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 342.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
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
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 202.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 202.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: paintMethod->dotIndicatorModifier_ is true.
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: itemHalfSizes_->Get()[1] is 6.65 .
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[1], 10.f * 0.5 * 1.33f));
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->PaintPressIndicator(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: itemHalfSizes_->Get()[0] is 13.30 .
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[0], 20.f * 0.5 * 1.33f));
}

/**
 * @tc.name: SwiperIndicatorCalculateNormalMargin001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorCalculateNormalMargin001, TestSize.Level1)
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
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: run success
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);

    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 347.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorCalculatePointCenterX001, TestSize.Level1)
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
    /**
     * @tc.steps: step3. call CalculatePointCenterX.
     * @tc.expected: run success
     */
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);
}

/**
 * @tc.name: SwiperIndicatorUpdateBackgroundX001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorUpdateBackgroundX001, TestSize.Level1)
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
    /**
     * @tc.steps: step3. call UpdateBackground.
     * @tc.expected: run success
     */
    paintMethod->UpdateBackground(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintHoverIndicator003, TestSize.Level1)
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
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step2. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->mouseClickIndex_ = 100;
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorPaintHoverIndicator004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
    paintMethod->dotIndicatorModifier_->SetIsPressed(false);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
    * @tc.steps: step3. call PaintHoverIndicator.
    * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
    */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX002
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperIndicatorCalculatePointCenterX002, TestSize.Level1)
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
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step2. call CalculatePointCenterX.
     * @tc.expected: run success
     */
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->turnPageRate_ = 110.0f;
    paintMethod->itemCount_ = 100;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    paintMethod->turnPageRate_ = 10.0f;
    paintMethod->itemCount_ = 10;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);

    paintMethod->turnPageRate_ = 110.0f;
    paintMethod->IsCustomSizeValue_ = false;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);
}

/**
 * @tc.name: SwiperPaintMethodClipPadding001
 * @tc.desc: ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodClipPadding001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AnyNumber());

    /**
     * @tc.steps: step2. call ClipPadding.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needClipPadding_ = true;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
    swiperPaintMethod1.needClipPadding_ = false;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_FALSE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodPaintFade001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AnyNumber());

    /**
     * @tc.steps: step2. call PaintFade whith setting needPaintFade_ and renderContext.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_TRUE(swiperPaintMethod1.needPaintFade_);
    swiperPaintMethod1.needPaintFade_ = false;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_FALSE(swiperPaintMethod1.needPaintFade_);
    paintWrapper.renderContext_ = renderContext;
    swiperPaintMethod1.needClipPadding_ = true;
    renderContext->UpdateClipEdge(false);
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    paintWrapper.renderContext_ = nullptr;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: GetStartAndEndIndex001
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetStartAndEndIndex001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.9f;

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto index = pattern_->TotalCount() - 1;
    auto expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(0, 0);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: GetStartAndEndIndex002
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetStartAndEndIndex002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.8f;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto expectVal = std::pair<int32_t, int32_t>(0, 0);
    auto index = pattern_->TotalCount() - 1;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(1, 1);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(1), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: GetIndex001
 * @tc.desc: get point start and end index when SwipeByGroup is true and isLoop_ is false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    model.SetLoop(false);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);

    auto displayIndicatorCount = pattern_->DisplayIndicatorTotalCount();
    EXPECT_EQ(displayIndicatorCount, 3);

    // change last page
    ChangeIndex(4);
    pattern_->UpdateCurrentOffset(40.0f);
    FlushUITasks();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto paintMethod = AceType::DynamicCast<DotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);

    int32_t indicatorIndex = displayIndicatorCount - 1;
    auto expectVal = std::pair<int32_t, int32_t>(indicatorIndex, indicatorIndex);
    EXPECT_EQ(paintMethod->GetIndex(indicatorIndex), expectVal);
}

/**
 * @tc.name: GetIndex002
 * @tc.desc: get point start and end index when SwipeByGroup is true and isLoop_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    model.SetLoop(true);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);

    auto displayIndicatorCount = pattern_->DisplayIndicatorTotalCount();
    EXPECT_EQ(displayIndicatorCount, 3);

    // change last page
    ChangeIndex(4);
    pattern_->UpdateCurrentOffset(40.0f);
    FlushUITasks();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto paintMethod = AceType::DynamicCast<DotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);

    int32_t indicatorIndex = displayIndicatorCount - 1;
    auto expectVal = std::pair<int32_t, int32_t>(indicatorIndex, 0);
    EXPECT_EQ(paintMethod->GetIndex(indicatorIndex), expectVal);
}

/**
 * @tc.name: AdjustPointCenterXForTouchBottom
 * @tc.desc: adjust long point centerX for touch bottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, AdjustPointCenterXForTouchBottom001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    DotIndicatorPaintMethod::StarAndEndPointCenter pointCenter;
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }

    int32_t startCurrentIndex = 0;
    int32_t endCurrentIndex = totalCount - 1;
    float selectedItemWidth = 0.0f;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[startCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[startCurrentIndex]);

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[endCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[endCurrentIndex]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    paintMethod->touchBottomPageRate_ = 0.2;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);
}

/**
 * @tc.name: AdjustPointCenterXForTouchBottomNew
 * @tc.desc: Test AdjustPointCenterXForTouchBottomNew
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, AdjustPointCenterXForTouchBottomNew001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    DotIndicatorPaintMethod::StarAndEndPointCenter pointCenter;
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }

    int32_t endCurrentIndex = totalCount - 1;
    float selectedItemWidth = 0.0f;

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    paintMethod->touchBottomPageRate_ = 0.2;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->touchBottomPageRate_ = 0;
    EXPECT_TRUE(paintMethod->AdjustPointCenterXForTouchBottomNew(pointCenter, endVectorBlackPointCenterX,
        endCurrentIndex, selectedItemWidth));

    paintMethod->touchBottomPageRate_ = 0.2;
    EXPECT_FALSE(paintMethod->AdjustPointCenterXForTouchBottomNew(pointCenter, endVectorBlackPointCenterX,
        endCurrentIndex, selectedItemWidth));
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter
 * @tc.desc: get long point animation state second center
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetLongPointAnimationStateSecondCenter001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    std::vector<std::pair<float, float>> pointCenterX;
    paintMethod->turnPageRate_ = -1.0f;

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);
}

/**
 * @tc.name: GetMoveRate001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, GetMoveRate001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Calling the GetMoveRate interface
     * @tc.expected: GestureState_ 5. After accepting, read the value of std:: get<2>(gestureState_5),
     * which is equal to std:: abs (paintMethod ->turnPageRate2)
     */
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    auto gestureState_5 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<2>(gestureState_5) == std::abs(paintMethod->turnPageRate_));

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    auto gestureState_4 = paintMethod->GetMoveRate();
    EXPECT_TRUE(
        std::get<2>(gestureState_4) == std::abs(paintMethod->turnPageRate_) + (1 - std::get<1>(gestureState_4)) * 0.5);

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    auto gestureState_3 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<1>(gestureState_3) == std::get<2>(gestureState_3));

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto gestureState_2 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<1>(gestureState_2) == std::get<2>(gestureState_2));

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto gestureState_1 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<0>(gestureState_1) == 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    auto gestureState = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<0>(gestureState) == 1);

    paintMethod->isPressed_ = true;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    paintMethod->GetMoveRate();
    EXPECT_TRUE(paintMethod->isPressed_ &&
                paintMethod->touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade002
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodPaintFade002, TestSize.Level1)
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

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 1.0f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    swiperPaintMethod1.mainDelta_ = 0.002f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 0.002f);
}

/**
 * @tc.name: SwiperPaintMethodGetOverlayDrawFunction001
 * @tc.desc: GetOverlayDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodGetOverlayDrawFunction001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    auto canvasDrawFunction = swiperPaintMethod1.GetOverlayDrawFunction(&paintWrapper);
    canvasDrawFunction(canvas);
    EXPECT_TRUE(canvasDrawFunction);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade003
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodPaintFade003, TestSize.Level1)
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

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = -1.0f;
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade004
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodPaintFade004, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, SwiperPaintMethodPaintFade005, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, GetContentDrawFunction001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, PlayIndicatorAnimation001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, PaintUnselectedIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, PlayLongPointAnimation001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, PlayLongPointAnimation002, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, StopAnimation001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, UpdateLongPointDilateRatio001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, UpdateDilatePaintProperty001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, UpdateShrinkPaintProperty002, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier007, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier008, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier009, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier010, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier011, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier012, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, DotIndicatorModifier013, TestSize.Level1)
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
}

/**
 * @tc.name: CircleDotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorModifier001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotPlayIndicatorAnimation001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorUpdateContentModifier001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorPaintNormalIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorPaintUnselectedIndicator001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorCalculatePointAngle001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorGetHalfIndex001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorGetLongPointAngle001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorGetBlackPointAngle001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorGetIndex001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorGetStartAndEndIndex001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorModifierTestNg, CircleDotIndicatorSetFunctions001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
