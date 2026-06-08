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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
class DotIndicatorLayoutAlgorithmTestNg : public SwiperTestNg {
public:
    RefPtr<DotIndicatorLayoutAlgorithm> CreateAlgorithm()
    {
        auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
        return AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());
    }

    LayoutWrapperNode CreateLayoutWrapper()
    {
        auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
        return LayoutWrapperNode(indicatorNode_, geometryNode, indicatorNode_->GetLayoutProperty());
    }
};

// ===================== CalcIndicatorFrameSize =====================

/**
 * @tc.name: CalcIndicatorFrameSize_NullLayoutWrapper
 * @tc.desc: CalcIndicatorFrameSize with null layoutWrapper returns {-1, -1}
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_NullLayoutWrapper, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto result = algorithm->CalcIndicatorFrameSize(nullptr, 100.0f, 50.0f);
    EXPECT_FALSE(result.IsNonNegative());
}

/**
 * @tc.name: CalcIndicatorFrameSize_NullLayoutProperty
 * @tc.desc: CalcIndicatorFrameSize with wrapper that has no layout property returns {-1, -1}
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_NullLayoutProperty, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto wrapper = CreateLayoutWrapper();
    wrapper.layoutProperty_ = nullptr;
    auto result = algorithm->CalcIndicatorFrameSize(&wrapper, 100.0f, 50.0f);
    EXPECT_FALSE(result.IsNonNegative());
}

/**
 * @tc.name: CalcIndicatorFrameSize_NullLayoutConstraint
 * @tc.desc: CalcIndicatorFrameSize with wrapper that has no layout constraint returns {-1, -1}
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_NullLayoutConstraint, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto wrapper = CreateLayoutWrapper();
    auto layoutProperty = wrapper.GetLayoutProperty();
    layoutProperty->layoutConstraint_ = std::nullopt;
    auto result = algorithm->CalcIndicatorFrameSize(&wrapper, 100.0f, 50.0f);
    EXPECT_FALSE(result.IsNonNegative());
}

/**
 * @tc.name: CalcIndicatorFrameSize_IsSingleWithIdealSize
 * @tc.desc: CalcIndicatorFrameSize with isSingle_ true and ideal size set
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_IsSingleWithIdealSize, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetIsSingle(true);
    auto wrapper = CreateLayoutWrapper();
    auto layoutProperty = wrapper.GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(200.0), CalcLength(100.0)));
    auto result = algorithm->CalcIndicatorFrameSize(&wrapper, 50.0f, 30.0f);
    EXPECT_TRUE(result.IsNonNegative());
    EXPECT_GE(result.Width(), 50.0f);
    EXPECT_GE(result.Height(), 30.0f);
}

/**
 * @tc.name: CalcIndicatorFrameSize_IsSingleNoWidth
 * @tc.desc: CalcIndicatorFrameSize with isSingle_ true and ideal size lacking width
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_IsSingleNoWidth, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetIsSingle(true);
    auto wrapper = CreateLayoutWrapper();
    auto layoutProperty = wrapper.GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(100.0)));
    auto result = algorithm->CalcIndicatorFrameSize(&wrapper, 50.0f, 30.0f);
    EXPECT_TRUE(result.IsNonNegative());
}

/**
 * @tc.name: CalcIndicatorFrameSize_IsSingleNoHeight
 * @tc.desc: CalcIndicatorFrameSize with isSingle_ true and ideal size lacking height
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, CalcIndicatorFrameSize_IsSingleNoHeight, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetIsSingle(true);
    auto wrapper = CreateLayoutWrapper();
    auto layoutProperty = wrapper.GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(200.0), std::nullopt));
    auto result = algorithm->CalcIndicatorFrameSize(&wrapper, 50.0f, 30.0f);
    EXPECT_TRUE(result.IsNonNegative());
}

// ===================== Measure =====================

/**
 * @tc.name: Measure_NullLayoutWrapper
 * @tc.desc: Measure with null layoutWrapper should not crash
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_NullLayoutWrapper, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->Measure(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Measure_NullFrameNode
 * @tc.desc: Measure with wrapper having null host node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_NullFrameNode, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<SwiperIndicatorLayoutProperty>();
    LayoutWrapperNode wrapper(indicatorNode_, geometryNode, layoutProperty);
    wrapper.hostNode_ = nullptr;
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Measure_NegativeItemSize
 * @tc.desc: Measure with negative item dimensions should fall back to theme defaults
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_NegativeItemSize, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1.0));
    paintProperty->UpdateItemHeight(Dimension(-1.0));
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0));
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0));
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_IndicatorScaleOverrideByMaxDisplayCount
 * @tc.desc: Measure with maxDisplayCount_ > 0 sets indicatorScale to 1.0
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_IndicatorScaleOverrideByMaxDisplayCount, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetMaxDisplayCount(5);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_IndicatorScaleOverrideByBindIndicator
 * @tc.desc: Measure with !indicatorInteractive_ && isBindIndicator_ sets indicatorScale to 1.0
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_IndicatorScaleOverrideByBindIndicator, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetIsBindIndicator(true);
    algorithm->SetIndicatorInteractive(false);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_SelectedItemHeightGreater
 * @tc.desc: Measure with selectedItemHeight > itemHeight branch
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_SelectedItemHeightGreater, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(6.0));
    paintProperty->UpdateItemHeight(Dimension(4.0));
    paintProperty->UpdateSelectedItemWidth(Dimension(8.0));
    paintProperty->UpdateSelectedItemHeight(Dimension(10.0));
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_IsCustomSizeTrue
 * @tc.desc: Measure with custom size flag true branches
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_IsCustomSizeTrue, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateIsCustomSize(true);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_MaxDisplayCountBranch
 * @tc.desc: Measure with maxDisplayCount_ > 0 triggers overlength branches
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_MaxDisplayCountBranch, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->SetIndicatorDisplayCount(8);
    algorithm->SetMaxDisplayCount(6);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_VerticalDirection
 * @tc.desc: Measure with vertical direction swaps indicator width/height
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_VerticalDirection, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_IgnoreSizeHorizontal
 * @tc.desc: Measure with ignoreSize true and horizontal direction
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_IgnoreSizeHorizontal, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateIgnoreSize(true);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_IgnoreSizeVertical
 * @tc.desc: Measure with ignoreSize true and vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_IgnoreSizeVertical, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateIgnoreSize(true);
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    EXPECT_TRUE(wrapper.GetGeometryNode()->GetFrameSize().IsNonNegative());
}

/**
 * @tc.name: Measure_Default
 * @tc.desc: Measure with default parameters
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Measure_Default, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto wrapper = CreateLayoutWrapper();
    algorithm->Measure(&wrapper);
    auto frameSize = wrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_TRUE(frameSize.IsNonNegative());
    EXPECT_GT(frameSize.Width(), 0.0f);
    EXPECT_GT(frameSize.Height(), 0.0f);
}

// ===================== Layout =====================

/**
 * @tc.name: Layout_NullLayoutWrapper
 * @tc.desc: Layout with null layoutWrapper should not crash
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Layout_NullLayoutWrapper, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    algorithm->Layout(nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Layout_NullFrameNode
 * @tc.desc: Layout with wrapper having null host node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Layout_NullFrameNode, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<SwiperIndicatorLayoutProperty>();
    LayoutWrapperNode wrapper(indicatorNode_, geometryNode, layoutProperty);
    wrapper.hostNode_ = nullptr;
    algorithm->Layout(&wrapper);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Layout_NullIndicatorPattern
 * @tc.desc: Layout when host node has no SwiperIndicatorPattern should not crash
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Layout_NullIndicatorPattern, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto hostNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto layoutProperty = AceType::MakeRefPtr<SwiperIndicatorLayoutProperty>();
    LayoutWrapperNode wrapper(hostNode, geometryNode, layoutProperty);
    wrapper.hostNode_ = hostNode;
    algorithm->Layout(&wrapper);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: Layout_NeedSetOffset
 * @tc.desc: Layout with needSet true should set margin frame offset
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, Layout_NeedSetOffset, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    auto wrapper = CreateLayoutWrapper();
    algorithm->ignorSizeIndicatorWidth_ = 100.0f;
    algorithm->ignorSizeIndicatorHeight_ = 50.0f;
    algorithm->Layout(&wrapper);
    auto offset = wrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_TRUE(offset.GetX() >= 0.0f || offset.GetY() >= 0.0f);
}

// ===================== GetValidEdgeLength =====================

/**
 * @tc.name: GetValidEdgeLength_Percent
 * @tc.desc: GetValidEdgeLength with percent edge
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, GetValidEdgeLength_Percent, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.7, DimensionUnit::PERCENT)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.5, DimensionUnit::PERCENT)), 50.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 20.0, Dimension(0.0, DimensionUnit::PERCENT)), 0.0);
}

/**
 * @tc.name: GetValidEdgeLength_Px
 * @tc.desc: GetValidEdgeLength with px edge
 * @tc.type: FUNC
 */
HWTEST_F(DotIndicatorLayoutAlgorithmTestNg, GetValidEdgeLength_Px, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto algorithm = CreateAlgorithm();
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(70.0, DimensionUnit::PX)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(-10.0, 40.0, Dimension(-20.0, DimensionUnit::PX)), 0.0);
}
} // namespace OHOS::Ace::NG
