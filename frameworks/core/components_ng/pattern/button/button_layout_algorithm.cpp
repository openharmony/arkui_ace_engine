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

#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ButtonLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

// Called to perform measure current render node.
void ButtonLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper)
{
    auto buttonLayoutProperty = DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(buttonLayoutProperty);

    if (buttonLayoutProperty->GetType().value_or(ButtonType::CAPSULE) == ButtonType::CIRCLE) {
        MeasureCircleButton(layoutWrapper);
    } else {
        BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto left = static_cast<float>(buttonTheme->GetPadding().Left().ConvertToPx());
    auto right = static_cast<float>(buttonTheme->GetPadding().Right().ConvertToPx());
    layoutWrapper->GetGeometryNode()->SetFrameSize(
        SizeF { left + layoutWrapper->GetGeometryNode()->GetFrameSize().Width() + right,
            layoutWrapper->GetGeometryNode()->GetFrameSize().Height() });
}

void ButtonLayoutAlgorithm::MeasureCircleButton(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    const auto& width = layoutConstraint->selfIdealSize.Width();
    const auto& height = layoutConstraint->selfIdealSize.Height();
    const auto& radius = frameNode->GetRenderContext()->GetBorderRadius();
    SizeF frameSize = { -1, -1 };
    do {
        if (layoutConstraint->selfIdealSize.AtLeastOneValid() || radius.has_value()) {
            if (radius.has_value()) {
                auto radiusTopMax = std::max(radius->radiusTopLeft, radius->radiusTopRight);
                auto radiusBottomMax = std::max(radius->radiusBottomLeft, radius->radiusBottomRight);
                auto radiusMax = std::max(radiusTopMax, radiusBottomMax);
                auto rrectRadius = radiusMax->ConvertToPx();
                frameSize.SetSizeT(SizeF { static_cast<float>(rrectRadius * 2), static_cast<float>(rrectRadius * 2) });
                break;
            }
            if (!width) {
                frameSize.SetSizeT(SizeF { height.value(), height.value() });
                if (frameSize.IsNonNegative()) {
                    break;
                }
            } else if (!height) {
                frameSize.SetSizeT(SizeF { width.value(), width.value() });
                if (frameSize.IsNonNegative()) {
                    break;
                }
            } else {
                auto minLength = std::min(width, height);
                frameSize.SetSizeT(SizeF { minLength.value(), minLength.value() });
                if (frameSize.IsNonNegative()) {
                    break;
                }
            }
        } else {
            UpdateFrameSizeUsingChild(layoutWrapper, frameSize);
            if (frameSize.IsNonNegative()) {
                break;
            }
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void ButtonLayoutAlgorithm::UpdateFrameSizeUsingChild(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto childFrame = SizeF(-1, -1);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        childFrame = childFrame > childSize ? childFrame : childSize;
    }
    childFrame.Constrain(minSize, maxSize);
    auto lenght = std::sqrt(std::pow(childFrame.Height(), 2) + std::pow(childFrame.Width(), 2));
    childFrame.SetHeight(static_cast<float>(lenght));
    childFrame.SetWidth(static_cast<float>(lenght));
    AddPaddingToSize(padding, childFrame);
    frameSize.UpdateIllegalSizeWithCheck(childFrame);
}
} // namespace OHOS::Ace::NG
