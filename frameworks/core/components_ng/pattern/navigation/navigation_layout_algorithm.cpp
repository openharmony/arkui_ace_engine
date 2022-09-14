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

#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void MeasureTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasTitleBarIndex()) {
        return;
    }
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetTitleBarIndexValue());
    CHECK_NULL_VOID(titleBarWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (navigationLayoutProperty->HasHideTitleBar() && navigationLayoutProperty->GetHideTitleBarValue()) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBarWrapper->Measure(constraint);
        return;
    }
    constraint.selfIdealSize = OptionalSizeF(SINGLE_PAGE_MAXIMUM_WIDTH, TITLEBAR_HEIGHT);
    titleBarWrapper->Measure(constraint);
}

void MeasureToolBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasToolBarIndex()) {
        return;
    }
    auto toolBarWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetToolBarIndexValue());
    CHECK_NULL_VOID(toolBarWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    if (navigationLayoutProperty->HasHideToolBar() && navigationLayoutProperty->GetHideToolBarValue()) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        toolBarWrapper->Measure(constraint);
        return;
    }
    constraint.selfIdealSize = OptionalSizeF(SINGLE_PAGE_MAXIMUM_WIDTH, TOOLBAR_HEIGHT);
    toolBarWrapper->Measure(constraint);
}

void MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasContentIndex()) {
        LOGW("Content area is empty");
        return;
    }
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetContentIndexValue());
    CHECK_NULL_VOID(contentWrapper);
    auto constraint = navigationLayoutProperty->CreateChildConstraint();
    auto contentSize = constraint.maxSize;
    // shrink content height when user did not set hide or user set hide false
    if (!navigationLayoutProperty->HasHideTitleBar() || !navigationLayoutProperty->GetHideTitleBarValue()) {
        contentSize.SetHeight(contentSize.Height() - TITLEBAR_HEIGHT);
    }
    if (!navigationLayoutProperty->HasHideToolBar() || !navigationLayoutProperty->GetHideToolBarValue()) {
        contentSize.SetHeight(contentSize.Height() - TOOLBAR_HEIGHT);
    }
    constraint.maxSize = contentSize;
    contentWrapper->Measure(constraint);
}

void LayoutTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasTitleBarIndex()) {
        return;
    }
    if (navigationLayoutProperty->HasHideTitleBar() && navigationLayoutProperty->GetHideTitleBarValue()) {
        return;
    }
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetTitleBarIndexValue());
    CHECK_NULL_VOID(titleBarWrapper);
    auto geometryNode = titleBarWrapper->GetGeometryNode();
    auto parentOffset = geometryNode->GetParentGlobalOffset() + geometryNode->GetFrameOffset();
    titleBarWrapper->Layout(parentOffset);
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasContentIndex()) {
        return;
    }
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetContentIndexValue());
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    auto parentOffset = geometryNode->GetParentGlobalOffset() + geometryNode->GetFrameOffset();
    auto contentOffset = geometryNode->GetFrameOffset();
    if (!navigationLayoutProperty->HasHideTitleBar() || !navigationLayoutProperty->GetHideTitleBarValue()) {
        contentOffset.SetY(TITLEBAR_HEIGHT);
    }
    geometryNode->SetFrameOffset(contentOffset);
    contentWrapper->Layout(parentOffset);
}

void LayoutToolBar(LayoutWrapper* layoutWrapper, const RefPtr<NavigationGroupNode>& hostNode,
    const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!hostNode->HasToolBarIndex()) {
        return;
    }
    if (navigationLayoutProperty->HasHideToolBar() && navigationLayoutProperty->GetHideToolBarValue()) {
        return;
    }
    auto toolBarWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetToolBarIndexValue());
    CHECK_NULL_VOID(toolBarWrapper);
    auto geometryNode = toolBarWrapper->GetGeometryNode();
    auto parentOffset = geometryNode->GetParentGlobalOffset() + geometryNode->GetFrameOffset();
    auto toolBarOffsetY = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - TOOLBAR_HEIGHT;
    auto toolBarOffset = OffsetT<float>(parentOffset.GetX(), toolBarOffsetY);
    geometryNode->SetFrameOffset(toolBarOffset);
    toolBarWrapper->Layout(parentOffset);
}
} // namespace

void NavigationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    const auto& constraint = navigationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    MeasureTitleBar(layoutWrapper, hostNode, navigationLayoutProperty);
    MeasureContentChild(layoutWrapper, hostNode, navigationLayoutProperty);
    MeasureToolBar(layoutWrapper, hostNode, navigationLayoutProperty);
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void NavigationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navigationLayoutProperty);
    LayoutTitleBar(layoutWrapper, hostNode, navigationLayoutProperty);
    LayoutContent(layoutWrapper, hostNode, navigationLayoutProperty);
    LayoutToolBar(layoutWrapper, hostNode, navigationLayoutProperty);
}

} // namespace OHOS::Ace::NG
