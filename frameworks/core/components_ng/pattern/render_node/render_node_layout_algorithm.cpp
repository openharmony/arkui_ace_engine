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

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
void RenderNodeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childLayoutConstraint);
    }

    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;

    OptionalSizeF frameSize;
    frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
    if (!frameSize.IsValid()) {
        if (layoutConstraint->selfIdealSize.Width()) {
            frameSize.ConstrainFloat(minSize, maxSize, false, true);
        } else if (layoutConstraint->selfIdealSize.Height()) {
            frameSize.ConstrainFloat(minSize, maxSize, true, true);
        } else {
            frameSize.Constrain(minSize, maxSize, true);
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void RenderNodeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto align = Alignment::TOP_LEFT;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
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
