/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/render_node/render_node_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void RenderNodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == "RenderNode" || child->GetHostTag() == V2::CUSTOM_FRAME_NODE_ETS_TAG) {
            child->Measure(std::nullopt);
        } else if (child->GetLayoutProperty() && child->GetLayoutProperty()->GetParentLayoutConstraint().has_value()) {
            child->Measure(child->GetLayoutProperty()->GetParentLayoutConstraint());
        } else {
            LayoutConstraintF layoutConstraint;
            layoutConstraint.maxSize = SizeF(0, 0);
            layoutConstraint.UpdateParentIdealSizeWithCheck({ 0, 0 });
            layoutConstraint.UpdateSelfMarginSizeWithCheck({ 0, 0 });
            child->Measure(layoutConstraint);
        }
    }
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint();
    OptionalSizeF frameSize;
    if (layoutConstraint && layoutConstraint->selfIdealSize && layoutConstraint->selfIdealSize->IsValid()) {
        auto selfIdealSize = layoutConstraint->selfIdealSize;
        frameSize.UpdateSizeWithCheck(
            OptionalSizeF(selfIdealSize->Width().value_or(CalcLength(0)).GetDimension().ConvertToPx(),
                selfIdealSize->Height().value_or(CalcLength(0)).GetDimension().ConvertToPx()));
    }
    frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

std::optional<SizeF> RenderNodeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    OptionalSizeF contentSize;
    // Use idea size first if it is valid.
    contentSize.UpdateSizeWithCheck(contentConstraint.selfIdealSize);
    if (contentSize.IsValid()) {
        return contentSize.ConvertToSizeT();
    }
    // wrap content case use min size default.
    contentSize.UpdateIllegalSizeWithCheck(contentConstraint.minSize);
    return contentSize.ConvertToSizeT();
}

void RenderNodeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto align = Alignment::TOP_LEFT;
    if (layoutWrapper->GetLayoutProperty() && layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        SizeF childSize = child->GetGeometryNode()->GetFrameSize();
        auto translate = Alignment::GetAlignPosition(size, childSize, align);
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align);
        content->SetOffset(translate);
    }

    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}
} // namespace OHOS::Ace::NG
