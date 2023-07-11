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

#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"

#include <algorithm>

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_component.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFALT_RING_DIAMETER = 72.0_vp;
const Dimension DEFALT_CAPSULE_WIDTH = 28.0_vp;
} // namespace
ProgressLayoutAlgorithm::ProgressLayoutAlgorithm() = default;

std::optional<SizeF> ProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    auto progressLayoutProperty = DynamicCast<ProgressLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(progressLayoutProperty, std::nullopt);
    type_ = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
    strokeWidth_ = progressLayoutProperty->GetStrokeWidth()
                       .value_or(progressTheme ? progressTheme->GetTrackThickness() : Dimension(strokeWidth_))
                       .ConvertToPx();
    float diameter =
        progressTheme ? progressTheme->GetRingDiameter().ConvertToPx() : DEFALT_RING_DIAMETER.ConvertToPx();
    float width_ = progressTheme ? progressTheme->GetTrackWidth().ConvertToPx() : contentConstraint.maxSize.Width();
    if (contentConstraint.selfIdealSize.Width()) {
        width_ = contentConstraint.selfIdealSize.Width().value();
    }
    float height_ = strokeWidth_;
    if (contentConstraint.selfIdealSize.Height()) {
        height_ = contentConstraint.selfIdealSize.Height().value();
    }
    if (type_ == ProgressType::RING || type_ == ProgressType::SCALE || type_ == ProgressType::MOON) {
        if (!contentConstraint.selfIdealSize.Width() && !contentConstraint.selfIdealSize.Height()) {
            width_ = diameter;
            height_ = width_;
        }
        if (contentConstraint.selfIdealSize.Width() && !contentConstraint.selfIdealSize.Height()) {
            height_ = width_;
        }
        if (contentConstraint.selfIdealSize.Height() && !contentConstraint.selfIdealSize.Width()) {
            width_ = height_;
        }
        if (contentConstraint.selfIdealSize.Height() && contentConstraint.selfIdealSize.Width()) {
            width_ = std::min(width_, height_);
            height_ = width_;
        }
    }
    if (type_ == ProgressType::CAPSULE) {
        if (!contentConstraint.selfIdealSize.Width()) {
            width_ = contentConstraint.percentReference.Width();
        }
        if (!contentConstraint.selfIdealSize.Height()) {
            height_ = contentConstraint.parentIdealSize.Height().value_or(GetChildHeight(layoutWrapper, width_));
        }
    }
    height_ = std::min(height_, static_cast<float>(contentConstraint.percentReference.Height()));
    width_ = std::min(width_, static_cast<float>(contentConstraint.percentReference.Width()));
    if (type_ == ProgressType::LINEAR) {
        if (width_ >= height_) {
            height_ = std::min(height_, strokeWidth_);
        } else {
            width_ = std::min(width_, strokeWidth_);
        }
    }
    LOGD("ProgressLayoutAlgorithm::Type:%{public}d MeasureContent: width_: %{public}fl ,height_: %{public}fl", type_,
        width_, height_);
    return SizeF(width_, height_);
}

ProgressType ProgressLayoutAlgorithm::GetType() const
{
    return type_;
}

float ProgressLayoutAlgorithm::GetStrokeWidth() const
{
    return strokeWidth_;
}

float ProgressLayoutAlgorithm::GetChildHeight(LayoutWrapper* layoutWrapper, float width) const
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, DEFALT_CAPSULE_WIDTH.ConvertToPx());
    auto paintProperty = host->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, DEFALT_CAPSULE_WIDTH.ConvertToPx());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, DEFALT_CAPSULE_WIDTH.ConvertToPx());
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    Dimension margin = progressTheme->GetTextMargin();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(childWrapper, DEFALT_CAPSULE_WIDTH.ConvertToPx());
    auto layoutProperty = AceType::DynamicCast<ProgressLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, DEFALT_CAPSULE_WIDTH.ConvertToPx());

    auto childLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(childLayoutProperty, DEFALT_CAPSULE_WIDTH.ConvertToPx());
    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(width);
    childWrapper->Measure(childConstraint);
    auto childSize = childWrapper->GetGeometryNode()->GetContentSize();
    if (childSize.Width() > (width - 2 * margin.ConvertToPx())) {
        CalcSize defaultCalcSize((CalcLength(width - 2 * margin.ConvertToPx())), std::nullopt);
        childLayoutProperty->UpdateUserDefinedIdealSize(defaultCalcSize);
    } else {
        CalcSize defaultCalcSize((CalcLength(childSize.Width())), std::nullopt);
        childLayoutProperty->UpdateUserDefinedIdealSize(defaultCalcSize);
    }
    float childHeight =
        paintProperty->GetTextSize().value_or(progressTheme->GetTextSize()).ConvertToPx() + 2 * margin.ConvertToPx();
    return childHeight;
}
} // namespace OHOS::Ace::NG
