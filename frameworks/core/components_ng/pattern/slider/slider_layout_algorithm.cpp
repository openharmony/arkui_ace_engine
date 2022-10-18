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

#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"

#include <algorithm>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

std::optional<SizeF> SliderLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(sliderLayoutProperty, std::nullopt);

    float width = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    float height = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());

    if (sliderLayoutProperty->HasThickness()) {
        trackThickness_ = static_cast<float>(sliderLayoutProperty->GetThickness().value().ConvertToPx());
    } else {
        trackThickness_ = static_cast<float>(
            sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                    SliderModel::SliderMode::OUTSET
                ? sliderLayoutProperty->GetOutsetTrackThickness().value_or(DEFAULT_SLIDER_HEIGHT_DP).ConvertToPx()
                : sliderLayoutProperty->GetInsetTrackThickness().value_or(DEFAULT_SLIDER_HEIGHT_DP).ConvertToPx());
    }
    float blockHotSize = static_cast<float>(
        sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                SliderModel::SliderMode::OUTSET
            ? sliderLayoutProperty->GetOutsetBlockHotSize().value_or(DEFAULT_PRESS_DIAMETER).ConvertToPx()
            : sliderLayoutProperty->GetInsetBlockHotSize().value_or(DEFAULT_PRESS_DIAMETER).ConvertToPx());
    float blockSize = static_cast<float>(
        sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                SliderModel::SliderMode::OUTSET
            ? sliderLayoutProperty->GetOutsetBlockSize().value_or(DEFAULT_HOVER_DIAMETER).ConvertToPx()
            : sliderLayoutProperty->GetInsetBlockSize().value_or(DEFAULT_HOVER_DIAMETER).ConvertToPx());

    float sliderWidth = trackThickness_;
    float blockSizeRatio = blockHotSize / blockSize;
    if (sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
        SliderModel::SliderMode::OUTSET) {
        blockSize = trackThickness_ * DEFAULT_THICKNESS_ENLARGES_BLOCKSIZE_RATIO;
        blockHotSize = blockSize * blockSizeRatio;
    } else {
        blockSize = std::min(trackThickness_, blockSize);
        blockHotSize = blockSize * blockSizeRatio;
    }
    blockDiameter_ = blockSize;
    blockHotDiameter_ = blockHotSize;

    sliderWidth = std::max(sliderWidth, blockHotSize);
    sliderWidth = std::max(sliderWidth, blockSize);
    Axis direction = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    sliderWidth = std::clamp(sliderWidth, 0.0f, direction == Axis::HORIZONTAL ? height : width);
    float sliderLength = direction == Axis::HORIZONTAL ? width : height;
    sliderLength = GreatOrEqual(sliderLength, BORDER_BLANK.ConvertToPx())
                       ? sliderLength - static_cast<float>(BORDER_BLANK.ConvertToPx())
                       : EXTREMELY_SMALL_SLIDER_LENGTH;
    return direction == Axis::HORIZONTAL ? SizeF(sliderLength, sliderWidth) : SizeF(sliderWidth, sliderLength);
}

} // namespace OHOS::Ace::NG