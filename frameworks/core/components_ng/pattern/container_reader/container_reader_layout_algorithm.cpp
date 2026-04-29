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

#include "core/components_ng/pattern/container_reader/container_reader_layout_algorithm.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/container_reader/container_reader_pattern.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int64_t INITIAL_RENDER_DEADLINE = 0;
} // namespace

void ContainerReaderLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);

    MeasureSelf(layoutWrapper);

    auto pattern = host->GetPattern<ContainerReaderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateBreakpointValues();

    LazyBuildChildren(layoutWrapper, host);

    MeasureChildren(layoutWrapper);
}

void ContainerReaderLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    BoxLayoutAlgorithm::Layout(layoutWrapper);
}

RefPtr<FrameNode> ContainerReaderLayoutAlgorithm::CreateChildFrameNode(const RefPtr<FrameNode>& host)
{
    ScopedViewStackProcessor scopedViewStackProcessor;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        "dummyNode", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    stack->Push(frameNode);
    bool isTimeout = false;
    renderFunction_(INITIAL_RENDER_DEADLINE, isTimeout);
    renderFunction_ = nullptr;
    auto pattern = host->GetPattern<ContainerReaderPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->SetIsInitialRender(false);
    stack->Pop();
    return frameNode;
}

void ContainerReaderLayoutAlgorithm::MountChildrenToHost(
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& host, LayoutWrapper* layoutWrapper)
{
    auto layoutWrapperNode = DynamicCast<LayoutWrapperNode>(Claim(layoutWrapper));
    for (const auto& child : frameNode->GetChildren()) {
        if (!child) {
            continue;
        }
        if (buildItem_ == nullptr) {
            buildItem_ = child;
        }
        child->MountToParent(host);
        if (layoutWrapperNode) {
            child->AdjustLayoutWrapperTree(layoutWrapperNode, true, true);
        }
    }
}

void ContainerReaderLayoutAlgorithm::LazyBuildChildren(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (!renderFunction_ || !host) {
        return;
    }
    ACE_SCOPED_TRACE("ContainerReaderNode:BuildItem");
    auto frameNode = CreateChildFrameNode(host);
    CHECK_NULL_VOID(frameNode);
    MountChildrenToHost(frameNode, host, layoutWrapper);
}

void ContainerReaderLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto layoutConstraint_ = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint_.has_value());
    bool idealWidthValid = layoutConstraint_.value().selfIdealSize.Width().has_value();
    bool idealHeightValid = layoutConstraint_.value().selfIdealSize.Height().has_value();
    auto idealSize = CreateIdealSizeByPercentRef(layoutConstraint_.value(), Axis::HORIZONTAL,
        MeasureType::MATCH_PARENT);
    if (!idealWidthValid) {
        idealSize.SetWidth(
            std::min(idealSize.Width().value_or(Infinity<float>()), layoutConstraint_.value().maxSize.Width()));
        idealSize.SetWidth(std::max(idealSize.Width().value_or(0.0f), layoutConstraint_.value().minSize.Width()));
    }
    if (!idealHeightValid) {
        idealSize.SetHeight(
            std::min(idealSize.Height().value_or(Infinity<float>()), layoutConstraint_.value().maxSize.Height()));
        idealSize.SetHeight(std::max(idealSize.Height().value_or(0.0f), layoutConstraint_.value().minSize.Height()));
    }
    auto containerSize = idealSize.ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(containerSize);
}

void ContainerReaderLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto selfSize = layoutWrapper->GetGeometryNode()->GetFrameSize();

    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto contentSize = selfSize;
    MinusPaddingToNonNegativeSize(padding, contentSize);
    layoutConstraint.parentIdealSize = OptionalSizeF(contentSize.Width(), contentSize.Height());

    auto childList = layoutWrapper->GetAllChildrenWithBuild();

    for (const auto& child : childList) {
        child->Measure(layoutConstraint);
    }
}

} // namespace OHOS::Ace::NG
