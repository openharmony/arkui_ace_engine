/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/distortion_component/distortion_component_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

void DistortionComponentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(0, 0));
        return;
    }
    auto contentNode = children.front();
    if (!contentNode) {
        return;
    }

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto childConstraint = layoutProperty->CreateChildConstraint();
    contentNode->Measure(childConstraint);

    // When the child component of distortionContent has a size,
    // distortionContent and distortionComponent should be the same size as the child.
    auto contentChildren = contentNode->GetAllChildrenWithBuild();
    if (!contentChildren.empty() && contentChildren.front()) {
        auto geoNode = contentChildren.front()->GetGeometryNode();
        CHECK_NULL_VOID(geoNode);
        SizeF childSize(geoNode->GetFrameSize().Width(), geoNode->GetFrameSize().Height());
        contentNode->GetGeometryNode()->SetFrameSize(childSize);
    }

    //Determine the content and wrapper size.
    auto contentSize = contentNode->GetGeometryNode()->GetMarginFrameSize();
    SizeF frameSize;
    frameSize.SetWidth(layoutConstraint->selfIdealSize.Width().value_or(contentSize.Width()));
    frameSize.SetHeight(layoutConstraint->selfIdealSize.Height().value_or(contentSize.Height()));
    frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    contentNode->GetGeometryNode()->SetFrameSize(frameSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

void DistortionComponentLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto paddingOffset = OffsetF(0.0, 0.0);
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    auto contentNode = children.front();
    if (contentNode) {
        contentNode->GetGeometryNode()->SetMarginFrameOffset(paddingOffset);
        contentNode->Layout();
    }
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        content->SetOffset(paddingOffset);
    }
}

} // namespace OHOS::Ace::NG
