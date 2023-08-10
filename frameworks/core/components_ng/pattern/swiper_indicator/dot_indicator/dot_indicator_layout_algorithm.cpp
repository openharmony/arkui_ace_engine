/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;
} // namespace
void DotIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto itemCount = swiperPattern->TotalCount();
    auto direction = swiperPattern->GetDirection();

    auto paintProperty = frameNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);

    // Diameter of a single indicator circle, item or selected-item width and height
    auto userItemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto userItemHeight = paintProperty->GetItemHeightValue(theme->GetSize()).ConvertToPx();
    auto userSelectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    auto userSelectedItemHeight = paintProperty->GetSelectedItemHeightValue(theme->GetSize()).ConvertToPx();
    if (LessNotEqual(userItemWidth, 0.0) ||LessNotEqual(userItemHeight, 0.0) ||
        LessNotEqual(userSelectedItemWidth, 0.0) || LessNotEqual(userSelectedItemHeight, 0.0)) {
        userItemWidth = theme->GetSize().ConvertToPx();
        userItemHeight = theme->GetSize().ConvertToPx();
        userSelectedItemWidth = theme->GetSize().ConvertToPx();
        userSelectedItemHeight = theme->GetSize().ConvertToPx();
    }
    auto indicatorPadding = INDICATOR_PADDING_HOVER;

    // To the size of the hover after the layout, in order to prevent the components after the hover draw boundaries
    userItemWidth *= INDICATOR_ZOOM_IN_SCALE;
    userItemHeight *= INDICATOR_ZOOM_IN_SCALE;
    userSelectedItemWidth *= INDICATOR_ZOOM_IN_SCALE;
    userSelectedItemHeight *= INDICATOR_ZOOM_IN_SCALE;

    // The width and height of the entire indicator.
    auto indicatorHeight = static_cast<float>(((userItemHeight > userSelectedItemHeight) ?
        userItemHeight : userSelectedItemHeight) + indicatorPadding.ConvertToPx() * 2);
    auto indicatorWidth = static_cast<float>(indicatorPadding.ConvertToPx() * 2 +
        ((userItemWidth + INDICATOR_ITEM_SPACE.ConvertToPx()) * (itemCount - 1)) + userSelectedItemWidth);

    if (direction == Axis::HORIZONTAL) {
        indicatorWidth_ = indicatorWidth;
        indicatorHeight_ = indicatorHeight;
    } else {
        indicatorWidth_ = indicatorHeight;
        indicatorHeight_ = indicatorWidth;
    }

    SizeF frameSize = { -1.0f, -1.0f };
    do {
        frameSize.SetSizeT(SizeF { indicatorWidth_, indicatorHeight_ });
        if (frameSize.IsNonNegative()) {
            break;
        }
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void DotIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_VOID(swiperNode);

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto direction = swiperPattern->GetDirection();
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty();
    CHECK_NULL_VOID(swiperLayoutProperty);
    const auto& swiperPaddingProperty = swiperLayoutProperty->GetPaddingProperty();
    float swiperPaddingLeft = 0.0f;
    float swiperPaddingRight = 0.0f;
    float swiperPaddingTop = 0.0f;
    float swiperPaddingBottom = 0.0f;
    if (swiperPaddingProperty != nullptr) {
        swiperPaddingLeft =
            static_cast<float>(swiperPaddingProperty->left.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingRight =
            static_cast<float>(swiperPaddingProperty->right.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingTop =
            static_cast<float>(swiperPaddingProperty->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
        swiperPaddingBottom =
            static_cast<float>(swiperPaddingProperty->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx());
    }
    const auto& borderWidthProperty = swiperLayoutProperty->GetBorderWidthProperty();
    double borderWidthLeft = 0.0f;
    double borderWidthRight = 0.0f;
    double borderWidthTop = 0.0f;
    double borderWidthBottom = 0.0f;
    if (borderWidthProperty != nullptr) {
        borderWidthLeft = borderWidthProperty->leftDimen.value_or(Dimension(0.0, DimensionUnit::PX)).ConvertToPx();
        borderWidthRight = borderWidthProperty->rightDimen.value_or(Dimension(0.0, DimensionUnit::PX)).ConvertToPx();
        borderWidthTop = borderWidthProperty->topDimen.value_or(Dimension(0.0, DimensionUnit::PX)).ConvertToPx();  
        borderWidthBottom = borderWidthProperty->bottomDimen.value_or(Dimension(0.0, DimensionUnit::PX)).ConvertToPx();
    }
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    auto left = layoutProperty->GetLeft();
    auto right = layoutProperty->GetRight();
    auto top = layoutProperty->GetTop();
    auto bottom = layoutProperty->GetBottom();

    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto swiperWidth = layoutConstraint->parentIdealSize.Width().value();
    auto swiperHeight = layoutConstraint->parentIdealSize.Height().value();

    Offset position;
    if (left.has_value() && !NearZero(left.value().Value())) {
        auto leftValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, left.value());
        position.SetX(leftValue + swiperPaddingLeft + borderWidthLeft);
    } else if (right.has_value() && !NearZero(right.value().Value())) {
        auto rightValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, right.value());
        position.SetX(swiperWidth - indicatorWidth_ - rightValue - swiperPaddingRight - borderWidthRight);
    } else {
        if (direction == Axis::HORIZONTAL) {
            position.SetX((swiperWidth - swiperPaddingRight - borderWidthRight + swiperPaddingLeft + borderWidthLeft - indicatorWidth_) * 0.5f);
        } else {
            position.SetX(swiperWidth - indicatorWidth_ - swiperPaddingRight - borderWidthRight);
        }
    }
    if (top.has_value() && !NearZero(top.value().Value())) {
        auto topValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, top.value());
        position.SetY(topValue + swiperPaddingTop + borderWidthTop);
    } else if (bottom.has_value() && !NearZero(bottom.value().Value())) {
        auto bottomValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, bottom.value());
        position.SetY(swiperHeight - indicatorHeight_ - bottomValue - swiperPaddingBottom - borderWidthBottom);
    } else {
        if (direction == Axis::HORIZONTAL) {
            position.SetY(swiperHeight - indicatorHeight_ - swiperPaddingBottom - borderWidthBottom);
        } else {
            position.SetY((swiperHeight - swiperPaddingBottom - borderWidthBottom + swiperPaddingTop + borderWidthTop - indicatorHeight_) * 0.5f);
        }
    }
    auto currentOffset = OffsetF {static_cast<float>(position.GetX()), static_cast<float>(position.GetY())};
    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
}

double DotIndicatorLayoutAlgorithm::GetValidEdgeLength(
    float swiperLength, float indicatorLength, const Dimension& edge)
{
    double edgeLength = edge.Unit() == DimensionUnit::PERCENT ? swiperLength * edge.Value() : edge.ConvertToPx();
    if (!NearZero(edgeLength) && edgeLength > swiperLength - indicatorLength) {
        edgeLength = swiperLength - indicatorLength;
    }
    if (edgeLength < 0.0) {
        edgeLength = 0.0;
    }
    return edgeLength;
}
} // namespace OHOS::Ace::NG
