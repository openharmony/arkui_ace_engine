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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorExtentTestNg : public SwiperTestNg {
public:
};
/**
 * @tc.name: SwiperInitIndicator007
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperInitIndicator007, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DOT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator008
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperInitIndicator008, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DIGIT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator009
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperInitIndicator009, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DOT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DIGIT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier004
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorUpdateContentModifier005
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorUpdateContentModifier006
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorUpdateContentModifier007
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier008
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier009
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier009, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier010
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier010, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier011
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier011, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier012
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier012, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorUpdateContentModifier013
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier013, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
    paintMethod->touchBottomType_ = TouchBottomType::END;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier014
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier014, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
    paintMethod->touchBottomType_ = TouchBottomType::END;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier015
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorUpdateContentModifier015, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
    paintMethod->touchBottomType_ = TouchBottomType::END;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorCalculateNormalMargin002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculateNormalMargin002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorCalculateNormalMargin003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculateNormalMargin003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorCalculateNormalMargin004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculateNormalMargin004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorCalculatePointCenterX002
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculatePointCenterX002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorCalculatePointCenterX003
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculatePointCenterX003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorCalculatePointCenterX004
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorCalculatePointCenterX004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: GetMoveRate002
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, GetMoveRate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: GetMoveRate003
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, GetMoveRate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: GetMoveRate004
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, GetMoveRate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator005
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator006
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator007
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator008
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintNormalIndicator008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintPressIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintPressIndicator004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintPressIndicator005
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintPressIndicator006
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintPressIndicator007
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintPressIndicator008
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintPressIndicator008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator004
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator005
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator006
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator007
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator008
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
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
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure003
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure004
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure005
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure006
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure007
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 32.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout003
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_TRUE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_TRUE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout005
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_TRUE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout006
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_FALSE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_FALSE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout007
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::FREE);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_FALSE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_FALSE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout008
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::NONE);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode_);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_FALSE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_FALSE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator009
 * @tc.desc: Test DotIndicatorPaintMethod::PaintHoverIndicator for specific conditions.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperIndicatorPaintHoverIndicator009, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(indicatorNode_, nullptr);
    auto wrapper = indicatorNode_->CreatePaintWrapper();
    auto paintMethod = AceType::DynamicCast<DotIndicatorPaintMethod>(wrapper->nodePaintImpl_);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->currentIndex_ = 9;
    paintMethod->totalItemCount_ = 11;
    paintMethod->itemCount_ = 11;
    paintMethod->displayCount_ = 2;
    paintMethod->isLoop_ = false;
    paintMethod->mouseClickIndex_ = 10;
    LinearVector<float> itemHalfSizes = { 5.0f, 5.0f, 10.0f, 10.0f };
    Dimension paddingSide = Dimension(5.0f);
    Dimension indicatorDotItemSpace = Dimension(8.0f);
    /**
     * @tc.expected: PaintHoverIndicator longPointCenterX_ first eq 177.0f
     */
    paintMethod->PaintHoverIndicator(itemHalfSizes, paddingSide, indicatorDotItemSpace);
    EXPECT_NEAR(paintMethod->longPointCenterX_.first, 177.0f, 0.001f);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmCalcFrameHeight0001
 * @tc.desc: Test Swiper DigitIndicatorLayoutAlgorithm::CalcFrameHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorExtentTestNg, SwiperDigitIndicatorLayoutAlgorithmCalcFrameHeight0001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = AceType::DynamicCast<DigitIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());
    float indicatorHeight = 20.0f;
    float indicatorDigitPadding = 0.0f;
    auto frameHeight = algorithm->CalcFrameHeight(indicatorNode_, indicatorHeight, indicatorDigitPadding);
    EXPECT_EQ(frameHeight, 20.0f);
}
} // namespace OHOS::Ace::NG
