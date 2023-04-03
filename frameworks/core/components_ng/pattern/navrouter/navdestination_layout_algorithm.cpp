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

#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
float MeasureTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size)
{
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBarWrapper->Measure(constraint);
        return 0.0f;
    }

    if (hostNode->GetSubtitle()) {
        constraint.selfIdealSize = OptionalSizeF(
            size.Width(), static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
        titleBarWrapper->Measure(constraint);
        return static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }

    constraint.selfIdealSize = OptionalSizeF(size.Width(),
        static_cast<float>(
            navDestinationLayoutProperty->GetTitleBarHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT).ConvertToPx()));
    titleBarWrapper->Measure(constraint);
    return static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
}

void MeasureContentChild(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size,
    float titleBarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(size.Width(), size.Height() - titleBarHeight);
    contentWrapper->Measure(constraint);
}

float LayoutTitleBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty)
{
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        return 0.0f;
    }
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(titleBarWrapper, 0.0f);
    auto geometryNode = titleBarWrapper->GetGeometryNode();
    auto titleBarOffset = OffsetT<float>(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(titleBarOffset);
    titleBarWrapper->Layout();
    return geometryNode->GetFrameSize().Height();
}

void LayoutContent(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, float titlebarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetContentNode()->GetId());
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(contentWrapper);
    auto geometryNode = contentWrapper->GetGeometryNode();
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        auto contentOffset = OffsetT<float>(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        contentWrapper->Layout();
        return;
    }

    auto contentOffset = OffsetT<float>(geometryNode->GetFrameOffset().GetX(), titlebarHeight);
    geometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();
}

} // namespace

void NavDestinationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    const auto& constraint = navDestinationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    float titleBarHeight = MeasureTitleBar(layoutWrapper, hostNode, navDestinationLayoutProperty, size);
    MeasureContentChild(layoutWrapper, hostNode, navDestinationLayoutProperty, size, titleBarHeight);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void NavDestinationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);

    float titlebarHeight = LayoutTitleBar(layoutWrapper, hostNode, navDestinationLayoutProperty);
    LayoutContent(layoutWrapper, hostNode, navDestinationLayoutProperty, titlebarHeight);
}

} // namespace OHOS::Ace::NG