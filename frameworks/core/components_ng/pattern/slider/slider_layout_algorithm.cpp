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

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BUBBLE_TO_CIRCLE_CENTER_DISTANCE = 20.0_vp;
} // namespace

std::optional<SizeF> SliderLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(sliderLayoutProperty, std::nullopt);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, std::nullopt);

    float width = contentConstraint.selfIdealSize.Width().value_or(contentConstraint.maxSize.Width());
    float height = contentConstraint.selfIdealSize.Height().value_or(contentConstraint.maxSize.Height());

    Dimension themeTrackThickness = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                                            SliderModel::SliderMode::OUTSET
                                        ? theme->GetOutsetTrackThickness()
                                        : theme->GetInsetTrackThickness();
    trackThickness_ =
        static_cast<float>(sliderLayoutProperty->GetThickness().value_or(themeTrackThickness).ConvertToPx());
    float scaleValue = trackThickness_ / static_cast<float>(themeTrackThickness.ConvertToPx());
    Dimension themeBlockSize = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                                       SliderModel::SliderMode::OUTSET
                                   ? theme->GetOutsetBlockSize()
                                   : theme->GetInsetBlockSize();
    blockDiameter_ = scaleValue * static_cast<float>(themeBlockSize.ConvertToPx());
    Dimension themeBlockHotSize = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET) ==
                                          SliderModel::SliderMode::OUTSET
                                      ? theme->GetOutsetBlockHotSize()
                                      : theme->GetInsetBlockHotSize();
    float blockHotDiameter = scaleValue * static_cast<float>(themeBlockHotSize.ConvertToPx());

    float sliderWidth = trackThickness_;
    sliderWidth = std::max(sliderWidth, blockHotDiameter);
    sliderWidth = std::max(sliderWidth, blockDiameter_);
    Axis direction = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    sliderWidth = std::clamp(sliderWidth, 0.0f, direction == Axis::HORIZONTAL ? height : width);
    float sliderLength = direction == Axis::HORIZONTAL ? width : height;
    return direction == Axis::HORIZONTAL ? SizeF(sliderLength, sliderWidth) : SizeF(sliderWidth, sliderLength);
}

void SliderLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    CHECK_NULL_VOID_NOLOG(bubbleFlag_);
    auto bubbleWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(bubbleWrapper);
    auto bubbleSize = bubbleWrapper->GetGeometryNode()->GetFrameSize();
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(sliderLayoutProperty);

    if (sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        float offsetX = circleCenter_.GetX() - bubbleSize.Width() / 2;
        float offsetY = circleCenter_.GetY() - static_cast<float>(BUBBLE_TO_CIRCLE_CENTER_DISTANCE.ConvertToPx()) -
                        bubbleSize.Height();
        bubbleWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(offsetX, offsetY));
    } else {
        float offsetY = circleCenter_.GetY() - bubbleSize.Height() / 2;
        float offsetX = circleCenter_.GetX() - static_cast<float>(BUBBLE_TO_CIRCLE_CENTER_DISTANCE.ConvertToPx()) -
                        bubbleSize.Width();
        bubbleWrapper->GetGeometryNode()->SetMarginFrameOffset(OffsetF(offsetX, offsetY));
    }
}

} // namespace OHOS::Ace::NG
