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

#include "core/components_ng/pattern/button/button_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ButtonLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    const auto& selfLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    isNeedToSetDefaultHeight_ = buttonLayoutProperty->HasLabel() &&
                                buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) != ButtonType::CIRCLE &&
                                selfLayoutConstraint && !selfLayoutConstraint->selfIdealSize.Height().has_value();
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (buttonLayoutProperty->HasLabel() &&
        buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CIRCLE) {
        layoutConstraint.maxSize = HandleLabelCircleButtonConstraint(layoutWrapper).value_or(SizeF());
    }
    if (isNeedToSetDefaultHeight_) {
        auto defaultHeight = buttonTheme->GetHeight().ConvertToPx();
        auto maxHeight = selfLayoutConstraint->maxSize.Height();
        layoutConstraint.maxSize.SetHeight(maxHeight > defaultHeight ? defaultHeight : maxHeight);
        layoutConstraint.percentReference.SetHeight(maxHeight > defaultHeight ? defaultHeight : maxHeight);
    }

    // If the button has label, according to whether the font size is set to do the corresponding expansion button, font
    // reduction, truncation and other operations.
    if (buttonLayoutProperty->HasLabel()) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_VOID(childWrapper);
        auto childConstraint = layoutWrapper->GetLayoutProperty()->GetContentLayoutConstraint();
        childWrapper->Measure(childConstraint);
        childSize_ = childWrapper->GetGeometryNode()->GetContentSize();
        if (buttonLayoutProperty->HasFontSize()) {
            // Fonsize is set. When the font height is larger than the button height, make the button fit the font
            // height.
            if (GreatOrEqual(childSize_.Height(), layoutConstraint.maxSize.Height())) {
                layoutConstraint.maxSize.SetHeight(childSize_.Height());
            }
        } else {
            // Fonsize is not set. When the font width is greater than the button width, dynamically change the font
            // size to no less than 9sp.
            if (GreatOrEqual(childSize_.Width(), layoutConstraint.maxSize.Width())) {
                auto textLayoutProperty = DynamicCast<TextLayoutProperty>(childWrapper->GetLayoutProperty());
                textLayoutProperty->UpdateAdaptMaxFontSize(
                    buttonLayoutProperty->GetMaxFontSize().value_or(buttonTheme->GetMaxFontSize()));
                textLayoutProperty->UpdateAdaptMinFontSize(
                    buttonLayoutProperty->GetMinFontSize().value_or(buttonTheme->GetMinFontSize()));
                childWrapper->Measure(layoutConstraint);
                childSize_ = childWrapper->GetGeometryNode()->GetContentSize();
            }
        }
    }
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

// If the ButtonType is CIRCLE, then omit text by the smaller edge.
std::optional<SizeF> ButtonLayoutAlgorithm::HandleLabelCircleButtonConstraint(LayoutWrapper* layoutWrapper)
{
    SizeF constraintSize;
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(buttonLayoutProperty, constraintSize);
    const auto& selfLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, constraintSize);
    const auto& padding = buttonLayoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(padding, constraintSize);
    auto top = padding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto bottom = padding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto left = padding->left.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto right = padding->right.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto defaultHeight = buttonTheme->GetHeight().ConvertToPx();
    if (layoutConstraint.parentIdealSize.IsNull()) {
        // Width and height are not set.
        auto width = defaultHeight - left - right;
        auto height = defaultHeight - top - bottom;
        auto minLength = std::min(width, height);
        constraintSize.SetSizeT(SizeF(minLength, minLength));
    } else if (layoutConstraint.parentIdealSize.Width().has_value() &&
               !layoutConstraint.parentIdealSize.Height().has_value()) {
        // Only width is set.
        auto minLength = layoutConstraint.parentIdealSize.Width().value();
        constraintSize.SetSizeT(SizeF(minLength, minLength));
    } else if (layoutConstraint.parentIdealSize.Height().has_value() &&
               !layoutConstraint.parentIdealSize.Width().has_value()) {
        // Only height is set.
        auto minLength = layoutConstraint.parentIdealSize.Height().value();
        constraintSize.SetSizeT(SizeF(minLength - left - right, minLength));
    } else {
        // Both width and height are set.
        auto buttonWidth = selfLayoutConstraint->selfIdealSize.Width().value();
        auto buttonHeight = selfLayoutConstraint->selfIdealSize.Height().value();
        auto minbuttonLength = std::min(buttonWidth, buttonHeight);
        auto minLength = std::min(minbuttonLength - left - right, layoutConstraint.maxSize.Height() - top - bottom);
        constraintSize.SetSizeT(SizeF(minLength, minLength));
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, constraintSize);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, constraintSize);
    if (renderContext->HasBorderRadius() && layoutConstraint.parentIdealSize.IsNull()) {
        auto radius = GetFirstValidRadius(renderContext->GetBorderRadius().value()).ConvertToPx();
        auto minLength = std::min(2 * radius - left - right, 2 * radius - top - bottom);
        constraintSize.SetSizeT(SizeF(minLength, minLength));
    }
    return constraintSize;
}

// Called to perform measure current render node.
void ButtonLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper)
{
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    if (buttonLayoutProperty->HasLabel() &&
        buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CIRCLE) {
        HandleLabelCircleButtonFrameSize(layoutConstraint, frameSize);
    }
    const auto& padding = buttonLayoutProperty->GetPaddingProperty();
    if (isNeedToSetDefaultHeight_ && padding) {
        auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        auto defaultHeight = static_cast<float>(buttonTheme->GetHeight().ConvertToPx());
        auto layoutContraint = buttonLayoutProperty->GetLayoutConstraint();
        CHECK_NULL_VOID(layoutContraint);
        auto maxHeight = layoutContraint->maxSize.Height();
        auto topPadding = padding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
        auto bottomPadding = padding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
        auto actualHeight = static_cast<float>(childSize_.Height() + topPadding + bottomPadding);
        actualHeight = std::min(actualHeight, maxHeight);
        frameSize.SetHeight(maxHeight > defaultHeight ? std::max(defaultHeight, actualHeight) : maxHeight);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
    }
    // Determine if the button needs to fit the font size.
    if (buttonLayoutProperty->HasLabel() && buttonLayoutProperty->HasFontSize() && padding) {
        auto topPadding = padding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
        auto bottomPadding = padding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
        if (GreatOrEqual(childSize_.Height() + topPadding + bottomPadding, frameSize.Height())) {
            frameSize = SizeF(frameSize.Width(), childSize_.Height() + topPadding + bottomPadding);

            layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
        }
    }
    Dimension radius;
    auto renderContext = host->GetRenderContext();
    if (buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CIRCLE) {
        auto minSize = std::min(frameSize.Height(), frameSize.Width());
        if (buttonLayoutProperty->HasBorderRadius() && layoutConstraint.parentIdealSize.IsNull()) {
            minSize = GetFirstValidRadius(buttonLayoutProperty->GetBorderRadius().value()).ConvertToPx() * 2;
        }
        radius.SetValue(minSize / 2.0);
        BorderRadiusProperty borderRadius { radius, radius, radius, radius };
        renderContext->UpdateBorderRadius(borderRadius);
        MeasureCircleButton(layoutWrapper);
    } else if (buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CAPSULE) {
        radius.SetValue(frameSize.Height() / 2.0);
        renderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    } else {
        auto normalRadius =
            buttonLayoutProperty->GetBorderRadiusValue(BorderRadiusProperty({ 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp }));
        renderContext->UpdateBorderRadius(normalRadius);
    }
}

void ButtonLayoutAlgorithm::HandleLabelCircleButtonFrameSize(
    const LayoutConstraintF& layoutConstraint, SizeF& frameSize)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto defaultHeight = buttonTheme->GetHeight().ConvertToPx();
    float minLength = 0.0f;
    if (layoutConstraint.parentIdealSize.IsNull()) {
        minLength = defaultHeight;
    } else if (layoutConstraint.parentIdealSize.Width().has_value() &&
               !layoutConstraint.parentIdealSize.Height().has_value()) {
        minLength = frameSize.Width();
    } else if (layoutConstraint.parentIdealSize.Height().has_value() &&
               !layoutConstraint.parentIdealSize.Width().has_value()) {
        minLength = frameSize.Height();
    } else {
        minLength = std::min(frameSize.Width(), frameSize.Height());
    }
    frameSize.SetWidth(minLength);
    frameSize.SetHeight(minLength);
}

void ButtonLayoutAlgorithm::MeasureCircleButton(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    const auto& radius = frameNode->GetRenderContext()->GetBorderRadius();
    SizeF frameSize = { -1, -1 };

    if (radius.has_value()) {
        auto radiusTopMax = std::max(radius->radiusTopLeft, radius->radiusTopRight);
        auto radiusBottomMax = std::max(radius->radiusBottomLeft, radius->radiusBottomRight);
        auto radiusMax = std::max(radiusTopMax, radiusBottomMax);
        auto rrectRadius = radiusMax->ConvertToPx();
        frameSize.SetSizeT(SizeF { static_cast<float>(rrectRadius * 2), static_cast<float>(rrectRadius * 2) });
    }
    frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

Dimension ButtonLayoutAlgorithm::GetFirstValidRadius(const BorderRadiusProperty& borderRadius)
{
    if (borderRadius.radiusTopLeft.has_value()) {
        return borderRadius.radiusTopLeft.value();
    }
    if (borderRadius.radiusTopRight.has_value()) {
        return borderRadius.radiusTopRight.value();
    }
    if (borderRadius.radiusBottomLeft.has_value()) {
        return borderRadius.radiusBottomLeft.value();
    }
    if (borderRadius.radiusBottomRight.has_value()) {
        return borderRadius.radiusBottomRight.value();
    }
    return 0.0_vp;
}
} // namespace OHOS::Ace::NG
