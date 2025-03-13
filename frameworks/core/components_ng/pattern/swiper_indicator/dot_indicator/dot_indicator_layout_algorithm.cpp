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
constexpr float SMALLEST_POINT_RATIO = 1.0f / 3.0f;
constexpr float SECOND_SMALLEST_POINT_RATIO = 2.0f / 3.0f;
constexpr int32_t OVERLONG_SMALL_COUNT = 2;
} // namespace
SizeF DotIndicatorLayoutAlgorithm::CalcIndicatorFrameSize(
    LayoutWrapper* layoutWrapper, float indicatorWidth, float indicatorHeight)
{
    SizeF frameSize = { -1.0f, -1.0f };
    CHECK_NULL_RETURN(layoutWrapper, frameSize);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, frameSize);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, frameSize);

    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (isSingle_ && calcLayoutConstraint && calcLayoutConstraint->selfIdealSize) {
        auto idealSize =
            CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
        auto width = calcLayoutConstraint->selfIdealSize->Width();
        auto height = calcLayoutConstraint->selfIdealSize->Height();
        if (width) {
            indicatorWidth_ = std::max(indicatorWidth_, idealSize.Width());
        }

        if (height) {
            indicatorHeight_ = std::max(indicatorHeight_, idealSize.Height());
        }
    }

    do {
        frameSize.SetSizeT(SizeF { indicatorWidth_, indicatorHeight_ });
        if (frameSize.IsNonNegative()) {
            break;
        }
        frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } while (false);

    return frameSize;
}

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
    if ((maxDisplayCount_ > 0 || !indicatorInteractive_) && isBindIndicator_) {
        indicatorScale = 1.0f;
    }
    userItemWidth *= indicatorScale;
    userItemHeight *= indicatorScale;
    userSelectedItemWidth *= indicatorScale;
    userSelectedItemHeight *= indicatorScale;

    // The width and height of the entire indicator.
    Dimension indicatorHeightPadding = theme->GetIndicatorBgHeight();
    auto indicatorHeight =
        static_cast<float>(((userItemHeight > userSelectedItemHeight) ?
            userItemHeight : userSelectedItemHeight) + indicatorHeightPadding.ConvertToPx() * 2);
    auto noPaddingIndicatorHeight = indicatorHeight - indicatorHeightPadding.ConvertToPx();
    auto allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ + 1);
    if (paintProperty->GetIsCustomSizeValue(false)) {
        allPointDiameterSum = userItemWidth * (indicatorDisplayCount_ - 1) + userSelectedItemWidth;
    }
    
    auto indicatorDotItemSpace = paintProperty->GetSpaceValue(theme->GetIndicatorDotItemSpace());
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (indicatorDisplayCount_ - 1);
    if (maxDisplayCount_ > 0 && isBindIndicator_) {
        allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (maxDisplayCount_ - 1);
        allPointDiameterSum = userItemWidth * (maxDisplayCount_ - OVERLONG_SMALL_COUNT - 1) + userSelectedItemWidth +
                              userItemWidth * SECOND_SMALLEST_POINT_RATIO + userItemWidth * SMALLEST_POINT_RATIO;
    }
    auto paddingSide = theme->GetIndicatorPaddingDot().ConvertToPx();
    
    auto indicatorWidth = paddingSide + allPointDiameterSum + allPointSpaceSum + paddingSide;
    auto noPaddingIndicatorWidth = indicatorWidth - paddingSide * 1.5;
    auto ignoreSize = paintProperty->GetIgnoreSizeValue(false);
    if (direction == Axis::HORIZONTAL) {
        indicatorWidth_ = indicatorWidth;
        indicatorHeight_ = indicatorHeight;
        ignorSizeIndicatorWidth_ = indicatorWidth;
        ignorSizeIndicatorHeight_ = ignoreSize ? noPaddingIndicatorHeight : indicatorHeight;
    } else {
        indicatorWidth_ = indicatorHeight;
        indicatorHeight_ = indicatorWidth;
        ignorSizeIndicatorWidth_ = indicatorHeight;
        ignorSizeIndicatorHeight_ = ignoreSize ? noPaddingIndicatorWidth : indicatorWidth;
    }

    auto frameSize = CalcIndicatorFrameSize(layoutWrapper, indicatorWidth, indicatorHeight);
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
    auto needSet = indicatorPattern->GetDotCurrentOffset(currentOffset, ignorSizeIndicatorWidth_,
        ignorSizeIndicatorHeight_);
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
