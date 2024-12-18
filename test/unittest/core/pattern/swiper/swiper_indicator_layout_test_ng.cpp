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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorLayoutTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateLeft(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is available.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(100.00, 568.00)));
    layoutProperty->Reset();
    ASSERT_NE(layoutProperty->Clone(), nullptr);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is available.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout003
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateTop(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is available.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 100.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout005
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateBottom(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is available.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 1036.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout006
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode_, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 568.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    RefPtr<DotIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.7, DimensionUnit::PERCENT)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.5, DimensionUnit::PERCENT)), 50.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 20.0, Dimension(0.0, DimensionUnit::PERCENT)), 0.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(70.0, DimensionUnit::PX)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(-10.0, 40.0, Dimension(-20.0, DimensionUnit::PX)), 0.0);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
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
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
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
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorLayoutTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode_ children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
    auto children = hostNode->GetChildren();
    EXPECT_FALSE(children.empty());
}
} // namespace OHOS::Ace::NG
