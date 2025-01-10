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
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension INDICATOR_ITEM_SPACE = 8.0_vp;
} // namespace
void DotIndicatorLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorPattern = frameNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto direction = indicatorPattern->GetDirection();
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
    if (LessNotEqual(userItemWidth, 0.0) || LessNotEqual(userItemHeight, 0.0) ||
        LessNotEqual(userSelectedItemWidth, 0.0) || LessNotEqual(userSelectedItemHeight, 0.0)) {
        userItemWidth = theme->GetSize().ConvertToPx();
        userItemHeight = theme->GetSize().ConvertToPx();
        userSelectedItemWidth = theme->GetSize().ConvertToPx();
        userSelectedItemHeight = theme->GetSize().ConvertToPx();
    }

    // To the size of the hover after the layout, in order to prevent the components after the hover draw boundaries
    float indicatorScale = theme->GetIndicatorScale();
    userItemWidth *= indicatorScale;
    userItemHeight *= indicatorScale;
    userSelectedItemWidth *= indicatorScale;
    userSelectedItemHeight *= indicatorScale;

    // The width and height of the entire indicator.
    Dimension indicatorHeightPadding = theme->GetIndicatorBgHeight();
    auto indicatorHeight =
        static_cast<float>(((userItemHeight > userSelectedItemHeight) ?
            userItemHeight : userSelectedItemHeight) + indicatorHeightPadding.ConvertToPx() * 2);
    auto allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ + 1);
    if (paintProperty->GetIsCustomSizeValue(false)) {
        allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ - 1) + userSelectedItemWidth;
    }
    auto allPointSpaceSum = static_cast<float>(INDICATOR_ITEM_SPACE.ConvertToPx()) * (indicatorDisplayCount_ - 1);
    auto paddingSide = theme->GetIndicatorPaddingDot().ConvertToPx();
    auto indicatorWidth = paddingSide + allPointDiameterSum + allPointSpaceSum + paddingSide;

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

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(frameSize);
}

void DotIndicatorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto indicatorPattern = frameNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    OffsetF currentOffset = OffsetF(0.0f, 0.0f);
    auto needSet = indicatorPattern->GetDotCurrentOffset(currentOffset, indicatorWidth_, indicatorHeight_);
    if (needSet) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->SetMarginFrameOffset(currentOffset);
    }
}

double DotIndicatorLayoutAlgorithm::GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge)
{
    return SwiperIndicatorUtils::GetValidEdgeLength(swiperLength, indicatorLength, edge);
}
} // namespace OHOS::Ace::NG
