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

namespace OHOS::Ace::NG {

namespace {} // namespace

class SwiperIndicatorTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperIndicatorOnAttachToFrameNodeTest001
 * @tc.desc: Test SwiperIndicator OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorOnAttachToFrameNodeTest001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnAttachToFrameNode();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
}

/**
 * @tc.name: SwiperIndicatorOnModifyDone001
 * @tc.desc: Test SwiperIndicator OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_FALSE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
    config.frameSizeChange = true;
    EXPECT_TRUE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: SwiperIndicatorHandleClick001
 * @tc.desc: Test SwiperIndicator HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    indicatorPattern->HandleClick(info);
}

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorUpdateContentModifier003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: SwiperIndicatorCalculateNormalMargin001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorCalculateNormalMargin001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorCalculatePointCenterX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorUpdateBackgroundX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
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
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 30.00));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
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
 * @tc.name: SwiperIndicatorHandleClick002
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorHandleClick002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(10, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10, DimensionUnit::PX));
    indicatorPattern->mouseClickIndex_ = 5;
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->currentIndex_ = 10;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is true.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperIndicatorHandleClick003
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));
    pattern_->indicatorDoingAnimation_ = true;

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is false.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperInitIndicator001
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperInitIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator002
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperInitIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto layoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_->GetLastChild is 1.
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild(), 1);
}

/**
 * @tc.name: SwiperInitIndicator005
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperInitIndicator005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    CreateWithItem([swiperParameters](SwiperModelNG model) { model.SetDotIndicatorStyle(swiperParameters); });
    ASSERT_EQ(pattern_->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);
    CreateWithItem([digitalParameters](SwiperModelNG model) { model.SetDigitIndicatorStyle(digitalParameters); });
    ASSERT_EQ(pattern_->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
    auto children = hostNode->GetChildren();
    EXPECT_FALSE(children.empty());
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, DotIndicatorModifier001, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorTestNg, DotIndicatorModifier002, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorTestNg, DotIndicatorModifier003, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorTestNg, DotIndicatorModifier004, TestSize.Level1)
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
HWTEST_F(SwiperIndicatorTestNg, DotIndicatorModifier005, TestSize.Level1)
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
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation001
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternPlayIndicatorTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->indicatorId_.reset();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                break;
            }
            pattern_->indicatorId_ = 1;
        }
    }
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    pattern_->PlayIndicatorTranslateAnimation(0.1f);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperInitIndicator006
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperInitIndicator006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg002
 * @tc.desc: HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    indicatorPattern->isPressed_ = true;
    indicatorPattern->HandleTouchEvent(touchEventInfo);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg003
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg004
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator001
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_.reset();
    float additionalOffset = 0.1f;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDragUpdate001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternHandleLongDragUpdate001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternCheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternCheckIsTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = -5;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation003
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternPlayIndicatorTranslateAnimation003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.clear();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlayIndicatorTranslateAnimation(translate);
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    pattern_->PlayIndicatorTranslateAnimation(translate);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDrag001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternHandleLongDrag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));

    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));
}

/**
 * @tc.name: SwiperIndicatorPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternHandleDragEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->HandleDragEnd(1.0f);
    paintProperty_->UpdateAutoPlay(true);
    indicatorPattern->HandleDragEnd(1.0f);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex001
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetMouseClickIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    indicatorPattern->GetMouseClickIndex();
    paintProperty->UpdateIsCustomSize(true);
    indicatorPattern->GetMouseClickIndex();
    ASSERT_TRUE(paintProperty->GetIsCustomSizeValue(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0010
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0010, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    paintProperty_->UpdateAutoPlay(true);
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0011
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0011, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0012
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0012, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0013
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0013, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = HoverInfo();
    auto info1 = MouseInfo();
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::NONE);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
    indicatorPattern->mouseEvent_->onMouseCallback_(info1);
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0014
 * @tc.desc: HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0014, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->isRepeatClicked_ = true;
    auto info = GestureEvent();
    indicatorPattern->HandleMouseClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0015
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0015, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->isHover_ = true;
    layoutProperty_->UpdateHoverShow(true);
    pattern_->isAtHotRegion_ = false;
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0016
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0016, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(20.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(10.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0017
 * @tc.desc: InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0017, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    TouchEventInfo touchEventInfo("down");
    indicatorPattern->touchEvent_ = nullptr;
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    indicatorPattern->InitTouchEvent(gestureHub);
    indicatorPattern->touchEvent_->callback_(touchEventInfo);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator002
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    float additionalOffset = -1.0f;
    indicatorPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(3, SwiperItemInfo { 1.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 2.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation004
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternPlayIndicatorTranslateAnimation004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    float translate = 0.1f;
    pattern_->swiperController_->SetTurnPageRateCallback(nullptr);

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                pattern_->swiperController_->SetTurnPageRateCallback(nullptr);
                continue;
            }
            pattern_->swiperController_->SetTurnPageRateCallback([](int32_t, float) {});
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    }
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0018
 * @tc.desc: HandleTouchClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0018, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = GestureEvent();
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(5.0f);
    indicatorPattern->HandleTouchClick(info);
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(500.0f);
    indicatorPattern->HandleTouchClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0019
 * @tc.desc: UpdateTextContentSub
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0019, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);

    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern_->currentFirstIndex_ = -2;
    layoutProperty_->UpdateIndex(1);
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0020
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0020, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = 0;
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
    layoutProperty_->UpdateLoop(false);
    ASSERT_FALSE(layoutProperty_->GetLoop().value_or(true));
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(2.0f);
    indicatorPattern->dragStartPoint_.SetX(1.0f);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0021
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0021, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::MOUSE);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: PlayIndicatorAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, PlayIndicatorAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, PaintUnselectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
 * @tc.name: SwiperIndicatorPaintHoverIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPaintHoverIndicator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: SwiperIndicatorCalculatePointCenterX002
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorCalculatePointCenterX002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodClipPadding001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodPaintFade001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
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
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(1), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: AdjustPointCenterXForTouchBottom
 * @tc.desc: adjust long point centerX for touch bottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, AdjustPointCenterXForTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
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
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter
 * @tc.desc: get long point animation state second center
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetLongPointAnimationStateSecondCenter001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
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
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, PlayLongPointAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, PlayLongPointAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, StopAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, UpdateLongPointDilateRatio001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, UpdateDilatePaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
HWTEST_F(SwiperIndicatorTestNg, UpdateShrinkPaintProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
 * @tc.name: GetLongPointAnimationStateSecondCenter002
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetLongPointAnimationStateSecondCenter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });

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

    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: GetMoveRate001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetMoveRate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodPaintFade002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodGetOverlayDrawFunction001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodPaintFade003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
HWTEST_F(SwiperIndicatorTestNg, SwiperPaintMethodPaintFade004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
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
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetContentDrawFunction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
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
} // namespace OHOS::Ace::NG
