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

#include "core/components_ng/pattern/slider/slider_pattern.h"
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

RefPtr<SliderTheme> GetTheme()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<SliderTheme>();
}
} // namespace

SizeF SliderLayoutAlgorithm::CalculateHotSize(
    LayoutWrapper* layoutWrapper, const SizeF& blockSize, float themeBlockHotSize)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, SizeF());
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(sliderLayoutProperty, SizeF());
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    SizeF blockHotSize = blockSize;
    if (sliderMode == SliderModel::SliderMode::NONE) {
        auto hotSize = std::max(themeBlockHotSize, trackThickness_);
        blockHotSize = SizeF(hotSize, hotSize);
    } else {
        if (LessNotEqual(blockHotSize.Width(), themeBlockHotSize)) {
            blockHotSize.SetWidth(themeBlockHotSize);
        }
        if (LessNotEqual(blockHotSize.Height(), themeBlockHotSize)) {
            blockHotSize.SetHeight(themeBlockHotSize);
        }
    }
    return blockHotSize;
}

std::optional<SizeF> SliderLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            frameNode->GetGeometryNode()->ResetContent();
        } else {
            frameNode->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(sliderLayoutProperty, std::nullopt);
    auto theme = GetTheme();
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

    Dimension themeTrackThickness;
    Dimension themeBlockSize;
    Dimension hotBlockShadowWidth;
    Dimension themeBlockHotSize;
    GetStyleThemeValue(layoutWrapper, themeTrackThickness, themeBlockSize, hotBlockShadowWidth, themeBlockHotSize);
    auto thickness = sliderLayoutProperty->GetThickness().value_or(themeTrackThickness);
    trackThickness_ =
        static_cast<float>(thickness.Unit() == DimensionUnit::PERCENT
                               ? thickness.ConvertToPxWithSize(direction == Axis::HORIZONTAL ? height : width)
                               : thickness.ConvertToPx());
    // this scaleValue ensure that the size ratio of the block and trackThickness is consistent
    float scaleValue = trackThickness_ / static_cast<float>(themeTrackThickness.ConvertToPx());
    auto blockDiameter = scaleValue * static_cast<float>(themeBlockSize.ConvertToPx());
    // trackThickness and blockDiameter will get from theme when they are greater than slider component height or width
    if (JudgeTrackness(direction, blockDiameter, trackThickness_, width, height)) {
        trackThickness_ = static_cast<float>(themeTrackThickness.ConvertToPx());
        scaleValue = 1.0;
        blockDiameter = static_cast<float>(themeBlockSize.ConvertToPx());
    }
    blockSize_ = sliderLayoutProperty->GetBlockSizeValue(SizeF(blockDiameter, blockDiameter));
    blockHotSize_ = CalculateHotSize(layoutWrapper, blockSize_, static_cast<float>(themeBlockHotSize.ConvertToPx()));
    auto mode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    auto sliderWidth = CalculateSliderWidth(width, height, direction, hotBlockShadowWidth, mode);
    float sliderLength = direction == Axis::HORIZONTAL ? width : height;
    return direction == Axis::HORIZONTAL ? SizeF(sliderLength, sliderWidth) : SizeF(sliderWidth, sliderLength);
}

float SliderLayoutAlgorithm::CalculateSliderWidth(
    float width, float height, Axis direction, const Dimension& hotBlockShadowWidth, SliderModel::SliderMode mode)
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto blockWidth = direction == Axis::HORIZONTAL ? blockSize_.Height() : blockSize_.Width();
    auto blockHotWidth = direction == Axis::HORIZONTAL ? blockHotSize_.Height() : blockHotSize_.Width();
    auto sliderWidth = static_cast<float>(theme->GetMeasureContentDefaultWidth().ConvertToPx());
    sliderWidth = std::max(sliderWidth, trackThickness_);
    if (mode == SliderModel::SliderMode::OUTSET) {
        sliderWidth = std::max(sliderWidth, blockHotWidth);
        sliderWidth = std::max(sliderWidth, blockWidth + static_cast<float>(hotBlockShadowWidth.ConvertToPx()) / HALF);
    }
    sliderWidth = std::clamp(sliderWidth, 0.0f, direction == Axis::HORIZONTAL ? height : width);
    return sliderWidth;
}

void SliderLayoutAlgorithm::GetStyleThemeValue(LayoutWrapper* layoutWrapper, Dimension& themeTrackThickness,
    Dimension& themeBlockSize, Dimension& hotBlockShadowWidth, Dimension& themeBlockHotSize)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto sliderLayoutProperty = DynamicCast<SliderLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        themeTrackThickness = theme->GetOutsetTrackThickness();
        themeBlockSize = theme->GetOutsetBlockSize();
        hotBlockShadowWidth = theme->GetOutsetHotBlockShadowWidth();
        themeBlockHotSize = theme->GetOutsetBlockHotSize();
    } else if (sliderMode == SliderModel::SliderMode::INSET) {
        themeTrackThickness = theme->GetInsetTrackThickness();
        themeBlockSize = theme->GetInsetBlockSize();
        hotBlockShadowWidth = theme->GetInsetHotBlockShadowWidth();
        themeBlockHotSize = theme->GetInsetBlockHotSize();
    } else {
        themeTrackThickness = theme->GetNoneTrackThickness();
        themeBlockSize = Dimension(0);
        hotBlockShadowWidth = Dimension(0);
        themeBlockHotSize = theme->GetNoneBlockHotSize();
    }
}

void SliderLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->UseContentModifier()) {
        layoutConstraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(blockSize_.Width(), blockSize_.Height()));
    }
    if (layoutWrapper->GetTotalChildCount() != 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(0);
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

void SliderLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<SliderPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    if (pattern->UseContentModifier()) {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }
    PerformLayout(layoutWrapper);
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }

    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);

    auto contentRect = layoutWrapper->GetGeometryNode()->GetContentRect();
    auto axis = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    auto paintReverse = sliderLayoutProperty->GetReverseValue(false);
    auto direction = sliderLayoutProperty->GetLayoutDirection();
    if (axis == Axis::HORIZONTAL) {
        auto isRTL = direction == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft()
                                                      : direction == TextDirection::RTL;
        paintReverse = isRTL ? !paintReverse : paintReverse;
    }
    auto mode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    Dimension hotBlockShadowWidth = mode == SliderModel::SliderMode::OUTSET ? theme->GetOutsetHotBlockShadowWidth()
                                                                            : theme->GetInsetHotBlockShadowWidth();
    auto length = axis == Axis::HORIZONTAL ? contentRect.Width() : contentRect.Height();
    float BlockShadowWidth = static_cast<float>(hotBlockShadowWidth.ConvertToPx());
    auto blockSize = axis == Axis::HORIZONTAL ? blockSize_.Width() : blockSize_.Height();
    auto borderBlank = std::max(trackThickness_, blockSize + BlockShadowWidth / HALF);
    auto sliderLength = length >= borderBlank ? length - borderBlank : 1;
    borderBlank = (length - sliderLength) * HALF;
    auto selectOffset = borderBlank + pattern->GetValueRatio() * sliderLength;

    CalculateBlockOffset(layoutWrapper, contentRect, selectOffset, axis, paintReverse);
}

void SliderLayoutAlgorithm::CalculateBlockOffset(
    LayoutWrapper* layoutWrapper, const RectF& contentRect, float selectOffset, Axis axis, bool reverse)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<SliderPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    auto child = children.front();
    auto childSize_ = child->GetGeometryNode()->GetMarginFrameSize();
    OffsetF circleCenter;
    auto animatableBlockCenter = pattern->GetAnimatableBlockCenter();
    if (animatableBlockCenter.has_value()) {
        circleCenter = animatableBlockCenter.value();
    } else {
        if (!reverse) {
            if (axis == Axis::HORIZONTAL) {
                circleCenter.SetX(selectOffset);
                circleCenter.SetY(contentRect.Height() * HALF);
            } else {
                circleCenter.SetX(contentRect.Width() * HALF);
                circleCenter.SetY(selectOffset);
            }
        } else {
            if (axis == Axis::HORIZONTAL) {
                circleCenter.SetX(contentRect.Width() - selectOffset);
                circleCenter.SetY(contentRect.Height() * HALF);
            } else {
                circleCenter.SetX(contentRect.Width() * HALF);
                circleCenter.SetY(contentRect.Height() - selectOffset);
            }
        }
        circleCenter += OffsetF(contentRect.GetX(), contentRect.GetY());
    }

    OffsetF imageNodeOffset(
        circleCenter.GetX() - childSize_.Width() * HALF, circleCenter.GetY() - childSize_.Height() * HALF);

    child->GetGeometryNode()->SetMarginFrameOffset(imageNodeOffset);
    child->Layout();
}

} // namespace OHOS::Ace::NG
