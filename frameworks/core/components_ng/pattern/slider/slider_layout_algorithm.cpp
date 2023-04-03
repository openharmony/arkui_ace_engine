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

#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5f;
bool JudgeTrackness(Axis direction, float blockDiameter, float trackThickness, float width, float height)
{
    if (direction == Axis::HORIZONTAL) {
        return blockDiameter > height || trackThickness > height;
    }
    return blockDiameter > width || trackThickness > width;
}
} // namespace

std::optional<SizeF> SliderLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(sliderLayoutProperty, std::nullopt);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, std::nullopt);

    float width = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    float height = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());

    Axis direction = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    if (direction == Axis::HORIZONTAL && GreaterOrEqualToInfinity(width)) {
        width = static_cast<float>(theme->GetLayoutMaxLength().ConvertToPx());
    }
    if (direction == Axis::VERTICAL && GreaterOrEqualToInfinity(height)) {
        height = static_cast<float>(theme->GetLayoutMaxLength().ConvertToPx());
    }
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    Dimension themeTrackThickness = sliderMode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetTrackThickness()
                                                                                  : theme->GetInsetTrackThickness();
    trackThickness_ =
        static_cast<float>(sliderLayoutProperty->GetThickness().value_or(themeTrackThickness).ConvertToPx());
    // this scaleValue ensure that the size ratio of the block and trackThickness is consistent
    float scaleValue = trackThickness_ / static_cast<float>(themeTrackThickness.ConvertToPx());
    Dimension themeBlockSize =
        sliderMode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetBlockSize() : theme->GetInsetBlockSize();
    blockDiameter_ = scaleValue * static_cast<float>(themeBlockSize.ConvertToPx());
    // trackThickness and blockDiameter will get from theme when they are greater than slider component height or width
    if (JudgeTrackness(direction, blockDiameter_, trackThickness_, width, height)) {
        trackThickness_ = static_cast<float>(themeTrackThickness.ConvertToPx());
        scaleValue = 1.0;
        blockDiameter_ = static_cast<float>(themeBlockSize.ConvertToPx());
    }
    Dimension themeBlockHotSize =
        sliderMode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetBlockHotSize() : theme->GetInsetBlockHotSize();
    Dimension hotBlockShadowWidth = sliderMode == SliderModel::SliderMode::OUTSET ?
                                        theme->GetOutsetHotBlockShadowWidth() :
                                        theme->GetInsetHotBlockShadowWidth();
    blockHotSize_ = scaleValue * static_cast<float>(themeBlockHotSize.ConvertToPx());
    auto sliderWidth = static_cast<float>(theme->GetMeasureContentDefaultWidth().ConvertToPx());
    sliderWidth = std::max(sliderWidth, trackThickness_);
    sliderWidth = std::max(sliderWidth, blockHotSize_);
    sliderWidth = std::max(sliderWidth, blockDiameter_ + static_cast<float>(hotBlockShadowWidth.ConvertToPx()) / HALF);
    sliderWidth = std::clamp(sliderWidth, 0.0f, direction == Axis::HORIZONTAL ? height : width);
    float sliderLength = direction == Axis::HORIZONTAL ? width : height;
    return direction == Axis::HORIZONTAL ? SizeF(sliderLength, sliderWidth) : SizeF(sliderWidth, sliderLength);
}
} // namespace OHOS::Ace::NG
