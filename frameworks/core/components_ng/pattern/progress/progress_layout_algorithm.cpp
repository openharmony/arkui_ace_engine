/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension DEFALT_RING_DIAMETER = 72.0_vp;
const Dimension DEFALT_CAPSULE_WIDTH = 28.0_vp;
constexpr float ZERO_MEASURE_CONTENT_SIZE = 0.0f;
} // namespace
ProgressLayoutAlgorithm::ProgressLayoutAlgorithm() = default;

std::optional<SizeF> ProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<ProgressPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        return MeasureContentForApiNine(contentConstraint, layoutWrapper);
    }
    auto progressTheme = pipeline->GetTheme<ProgressTheme>(host->GetThemeScopeId());
    auto progressLayoutProperty = DynamicCast<ProgressLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(progressLayoutProperty, std::nullopt);
    auto layoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value() && (layoutPolicy->IsWrap() || layoutPolicy->IsFix())) {
        return SizeF(ZERO_MEASURE_CONTENT_SIZE, ZERO_MEASURE_CONTENT_SIZE);
    }
    type_ = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
    Dimension defaultThickness;
    if (progressTheme) {
        defaultThickness = (type_ == ProgressType::RING) ? Dimension(progressTheme->GetRingThickness())
                                                         : Dimension(progressTheme->GetTrackThickness());
    } else {
        defaultThickness = Dimension(strokeWidth_);
    }
    strokeWidth_ = progressLayoutProperty->GetStrokeWidth().value_or(defaultThickness).ConvertToPx();

    float diameter =
        progressTheme ? progressTheme->GetRingDiameter().ConvertToPx() : DEFALT_RING_DIAMETER.ConvertToPx();
    auto selfIdealWidth = contentConstraint.selfIdealSize.Width();
    auto selfIdealHeight = contentConstraint.selfIdealSize.Height();
    float width_ = selfIdealWidth.value_or(contentConstraint.percentReference.Width());
    float height_ = selfIdealHeight.value_or(strokeWidth_);
    if (type_ == ProgressType::RING || type_ == ProgressType::SCALE || type_ == ProgressType::MOON) {
        if (layoutPolicy.has_value()) {
            if (layoutPolicy->IsWidthMatch()) {
                selfIdealWidth = contentConstraint.parentIdealSize.Width();
            }
            if (layoutPolicy->IsHeightMatch()) {
                selfIdealHeight = contentConstraint.parentIdealSize.Height();
            }
        }
        if (!selfIdealHeight) {
            if (!selfIdealWidth) {
                width_ = diameter;
            }
            height_ = width_;
        } else {
            if (selfIdealWidth) {
                height_ = std::min(width_, height_);
            }
            width_ = height_;
        }
    } else if (type_ == ProgressType::CAPSULE) {
        if (!selfIdealWidth) {
            width_ = contentConstraint.percentReference.Width();
        }
        if (!selfIdealHeight) {
            height_ = contentConstraint.parentIdealSize.Height().value_or(GetChildHeight(layoutWrapper, width_));
        }
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, std::nullopt);
        float minSize = std::min(width_, height_);
        renderContext->UpdateBorderRadius(BorderRadiusProperty(Dimension(minSize / 2.0f)));
    } else if (type_ == ProgressType::LINEAR) {
        if (width_ >= height_) {
            height_ = std::min(height_, strokeWidth_);
        } else {
            width_ = std::min(width_, strokeWidth_);
        }
    }
    return SizeF(width_, height_);
}

std::optional<SizeF> ProgressLayoutAlgorithm::MeasureContentForApiNine(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto progressLayoutProperty = DynamicCast<ProgressLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto progressTheme = pipeline->GetTheme<ProgressTheme>(progressLayoutProperty->GetThemeScopeId());
    CHECK_NULL_RETURN(progressLayoutProperty, std::nullopt);
    type_ = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
    strokeWidth_ = progressLayoutProperty->GetStrokeWidth().
                        value_or(progressTheme ? (type_ == ProgressType::SCALE ? progressTheme->GetScaleLength() :
                            progressTheme->GetTrackThickness()): Dimension(strokeWidth_)).ConvertToPx();
    float diameter =
        progressTheme ? progressTheme->GetRingDiameter().ConvertToPx() : DEFALT_RING_DIAMETER.ConvertToPx();
    float width_ = progressTheme ? progressTheme->GetTrackWidth().ConvertToPx() : contentConstraint.maxSize.Width();
    auto selfIdealWidth = contentConstraint.selfIdealSize.Width();
    auto selfIdealHeight = contentConstraint.selfIdealSize.Height();
    if (selfIdealWidth) {
        width_ = selfIdealWidth.value();
    }
    float height_ = strokeWidth_ * 2.0f;
    if (selfIdealHeight) {
        height_ = selfIdealHeight.value();
    }
    if (type_ == ProgressType::RING || type_ == ProgressType::SCALE || type_ == ProgressType::MOON) {
        if (!selfIdealWidth && !selfIdealHeight) {
            width_ = diameter;
            height_ = width_;
        } else if (selfIdealWidth && !selfIdealHeight) {
            height_ = width_;
        } else if (selfIdealHeight && !selfIdealWidth) {
            width_ = height_;
        }
    } else if (type_ == ProgressType::CAPSULE) {
        if (!selfIdealHeight) {
            height_ = diameter;
        }
        if (!selfIdealWidth) {
            width_ = diameter;
        }
    }
    height_ = std::min(height_, static_cast<float>(contentConstraint.maxSize.Height()));
    width_ = std::min(width_, static_cast<float>(contentConstraint.maxSize.Width()));
    if (type_ == ProgressType::LINEAR) {
        strokeWidth_ = std::min(strokeWidth_, height_ / 2.0f);
        strokeWidth_ = std::min(strokeWidth_, width_ / 2.0f);
    }
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
    auto progressTheme = pipeline->GetTheme<ProgressTheme>(host->GetThemeScopeId());
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
    }
    float childHeight =
        paintProperty->GetTextSize().value_or(progressTheme->GetTextSize()).ConvertToPx() + 2 * margin.ConvertToPx();

    auto fontScale = pipeline->GetFontScale();
    if (GreatOrEqualCustomPrecision(fontScale, progressTheme->GetFontScale()) && (GetType() == ProgressType::CAPSULE)) {
        const auto& paddingProperty = layoutProperty->GetPaddingProperty();
        if (!(paddingProperty &&
                ((paddingProperty->top != std::nullopt) || (paddingProperty->bottom != std::nullopt)))) {
            childHeight = childHeight + (progressTheme->GetfontScalePadding()).ConvertToPx();
        }
    }

    return childHeight;
}
} // namespace OHOS::Ace::NG
