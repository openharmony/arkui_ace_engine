/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO::add to theme
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_HOVER = 12.0_vp;
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33f;

} // namespace

void SwiperIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;

    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto itemCount = swiperPattern->TotalCount();
    auto direction = swiperPattern->GetDirection();

    auto paintProperty = frameNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    // Diameter of a single indicator circle.
    auto userSize = paintProperty->GetSizeValue(theme->GetSize()).ConvertToPx();
    if (LessNotEqual(userSize, 0.0)) {
        userSize = theme->GetSize().ConvertToPx();
    }

    auto indicatorPadding = INDICATOR_PADDING_HOVER;
    // To the size of the hover after the layout, in order to prevent the components after the hover draw boundaries
    userSize *= INDICATOR_ZOOM_IN_SCALE;

    // Length of a selected indicator round rect.
    auto selectedSize = userSize * 2.0f;

    // The width and height of the entire indicator.
    auto indicatorHeight = static_cast<float>(userSize + indicatorPadding.ConvertToPx() * 2);
    auto indicatorWidth = static_cast<float>(
        (indicatorPadding.ConvertToPx() * 2 + (userSize + INDICATOR_ITEM_SPACE.ConvertToPx()) * (itemCount - 1)) +
        selectedSize);

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
        frameSize.Constrain(minSize, maxSize);
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void SwiperIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
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
    if (left.has_value()) {
        auto leftValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, Dimension(left->Value()));
        position.SetX(leftValue + swiperPaddingLeft);
    } else if (right.has_value()) {
        auto rightValue = GetValidEdgeLength(swiperWidth, indicatorWidth_, Dimension(right->Value()));
        position.SetX(swiperWidth - indicatorWidth_ - rightValue - swiperPaddingRight);
    } else {
        position.SetX(direction == Axis::HORIZONTAL
                          ? (swiperWidth - swiperPaddingRight + swiperPaddingLeft - indicatorWidth_) * 0.5f
                          : swiperWidth - indicatorWidth_ - swiperPaddingRight);
    }
    if (top.has_value()) {
        auto topValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, Dimension(top->Value()));
        position.SetY(topValue + swiperPaddingTop);
    } else if (bottom.has_value()) {
        auto bottomValue = GetValidEdgeLength(swiperHeight, indicatorHeight_, Dimension(bottom->Value()));
        position.SetY(swiperHeight - indicatorHeight_ - bottomValue - swiperPaddingBottom);
    } else {
        if (direction == Axis::HORIZONTAL) {
            position.SetY(swiperHeight - indicatorHeight_ - swiperPaddingBottom);
        } else {
            position.SetY((swiperHeight - swiperPaddingBottom + swiperPaddingTop - indicatorHeight_) * 0.5f);
        }
    }
    auto currentOffset = OffsetF { static_cast<float>(position.GetX()), static_cast<float>(position.GetY()) };
    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
}

double SwiperIndicatorLayoutAlgorithm::GetValidEdgeLength(
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
