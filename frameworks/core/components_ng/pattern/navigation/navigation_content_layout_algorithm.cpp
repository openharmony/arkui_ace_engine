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

#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"

#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void UpdatePropertyIfNeedForceMeasure(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    CHECK_NULL_VOID(navDestinationNode);
    if (!navDestinationNode->NeedForceMeasure()) {
        return;
    }
    navDestinationNode->SetNeedForceMeasure(false);
    auto property = navDestinationNode->GetLayoutProperty();
    if (property) {
        property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleProperty = titleBarNode->GetLayoutProperty();
    if (titleProperty) {
        titleProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
}

void NavigationContentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto childSize = layoutWrapper->GetTotalChildCount();
    std::list<RefPtr<LayoutWrapper>> children;
    if (childSize == 0) {
        layoutConstraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    } else {
        for (auto index = 0; index < childSize; index++) {
            auto child = layoutWrapper->GetOrCreateChildByIndex(index);
            auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(child->GetHostNode());
            if (!navDestinationNode) {
                continue;
            }
            if (!navDestinationNode->IsVisible()) {
                continue;
            }
            UpdatePropertyIfNeedForceMeasure(navDestinationNode);
            child->Measure(layoutConstraint);
            children.emplace_back(child);
        }
    }
    PerformMeasureSelfWithChildList(layoutWrapper, { children });
}

void NavigationContentLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild(false)) {
        auto childNode = child->GetHostNode();
        if (childNode && childNode->IsVisible()) {
            SizeF childSize = child->GetGeometryNode()->GetMarginFrameSize();
            auto translate = Alignment::GetAlignPosition(size, childSize, align) + paddingOffset;
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
            child->Layout();
        }
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

} // namespace OHOS::Ace::NG
