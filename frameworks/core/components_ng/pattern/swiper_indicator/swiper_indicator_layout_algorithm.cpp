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

#include <algorithm>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension INDICATOR_WIDTH = 8.0_vp;
constexpr Dimension INDICATOR_PADDING_TOP_DEFAULT = 9.0_vp;

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
    auto stackNode = frameNode->GetParent();
    CHECK_NULL_VOID(stackNode);

    auto swiperNode = DynamicCast<FrameNode>(stackNode->GetChildren().front());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    auto itemCount = swiperPattern->TotalCount();
    auto axis = swiperPattern->GetDirection();

    auto paintProperty = frameNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    float sizeHeigth = 0.0f;
    float sizeWidth = 0.0f;
    auto size = paintProperty->GetSize();
    if (size.has_value()) {
        sizeHeigth = static_cast<float>(size->ConvertToPx() + INDICATOR_PADDING_TOP_DEFAULT.ConvertToPx() * 2);
        sizeWidth = static_cast<float>(paintProperty->GetSize()->ConvertToPx());
    }

    auto indicatorWidth = static_cast<float>((sizeWidth + INDICATOR_WIDTH.ConvertToPx()) * itemCount);
    SizeF frameSize = { -1.0f, -1.0f };
    do {
        if (axis == Axis::VERTICAL) {
            frameSize.SetSizeT(SizeF { sizeHeigth, indicatorWidth });
            if (frameSize.IsNonNegative()) {
                break;
            }
        } else {
            frameSize.SetSizeT(SizeF { indicatorWidth, sizeHeigth });
        }
        frameSize.Constrain(minSize, maxSize);
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void SwiperIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto stackNode = frameNode->GetParent();
    CHECK_NULL_VOID(stackNode);
    auto swiperNode = DynamicCast<FrameNode>(stackNode->GetChildren().front());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto axis = swiperPattern->GetDirection();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = frameNode->GetPaintProperty<SwiperIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& maxSize = layoutConstraint->maxSize;

    float sizeWidth = 0.0f;
    if (paintProperty->GetSize().has_value()) {
        sizeWidth = static_cast<float>(paintProperty->GetSize()->ConvertToPx());
    }
    auto left = layoutProperty->GetLeft();
    auto right = layoutProperty->GetRight();
    auto top = layoutProperty->GetTop();
    auto bottom = layoutProperty->GetBottom();
    auto indicatorPaddingX = Dimension(0.0);
    auto indicatorPaddingY = Dimension(0.0);
    if (left.has_value()) {
        indicatorPaddingX = Dimension(left.value());
    } else if (right.has_value()) {
        indicatorPaddingX = Dimension(maxSize.Width() - right->Value());
    }
    if (top.has_value()) {
        indicatorPaddingY = Dimension(top->Value());
    } else if (bottom.has_value()) {
        indicatorPaddingY = Dimension(maxSize.Height() - bottom->Value());
    }
    auto currentOffset = axis == Axis::HORIZONTAL ? OffsetF(static_cast<float>(indicatorPaddingX.ConvertToPx()),
                                                        static_cast<float>(indicatorPaddingY.ConvertToPx()))
                                                  : OffsetF(static_cast<float>(indicatorPaddingY.ConvertToPx()),
                                                        static_cast<float>(indicatorPaddingX.ConvertToPx()));

    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
}
} // namespace OHOS::Ace::NG
