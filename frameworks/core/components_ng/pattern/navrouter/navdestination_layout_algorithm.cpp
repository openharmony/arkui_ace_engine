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
float MeasureTitleBar(FrameNode* frameNode, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size)
{
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBar = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_RETURN(titleBar, 0.0f);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        titleBar->Measure(constraint);
        return 0.0f;
    }

    if (hostNode->GetSubtitle()) {
        constraint.selfIdealSize = OptionalSizeF(
            size.Width(), static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
        titleBar->Measure(constraint);
        return static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }

    constraint.selfIdealSize = OptionalSizeF(size.Width(),
        static_cast<float>(
            navDestinationLayoutProperty->GetTitleBarHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT).ConvertToPx()));
    titleBar->Measure(constraint);
    return static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
}

void MeasureContentChild(FrameNode* frameNode, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, const SizeF& size,
    float titleBarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(contentNode->GetId());
    auto content = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_VOID(content);
    auto constraint = navDestinationLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(size.Width(), size.Height() - titleBarHeight);
    content->Measure(constraint);
}

float LayoutTitleBar(FrameNode* frameNode, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty)
{
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        return 0.0f;
    }
    auto titleBarNode = hostNode->GetTitleBarNode();
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto index = hostNode->GetChildIndexById(titleBarNode->GetId());
    auto titleBar = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_RETURN(titleBar, 0.0f);
    auto geometryNode = titleBar->GetGeometryNode();
    auto titleBarOffset = OffsetT<float>(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(titleBarOffset);
    titleBar->Layout();
    return geometryNode->GetFrameSize().Height();
}

void LayoutContent(FrameNode* frameNode, const RefPtr<NavDestinationGroupNode>& hostNode,
    const RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty, float titlebarHeight)
{
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetContentNode()->GetId());
    auto content = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_VOID(content);
    auto geometryNode = content->GetGeometryNode();
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        auto contentOffset = OffsetT<float>(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(contentOffset);
        content->Layout();
        return;
    }

    auto contentOffset = OffsetT<float>(geometryNode->GetFrameOffset().GetX(), titlebarHeight);
    geometryNode->SetMarginFrameOffset(contentOffset);
    content->Layout();
}

} // namespace

void NavDestinationLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(Claim(frameNode));
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    const auto& constraint = navDestinationLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto geometryNode = frameNode->GetGeometryNode();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    const auto& padding = frameNode->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);

    float titleBarHeight = MeasureTitleBar(frameNode, hostNode, navDestinationLayoutProperty, size);
    MeasureContentChild(frameNode, hostNode, navDestinationLayoutProperty, size, titleBarHeight);
    frameNode->GetGeometryNode()->SetFrameSize(size);
}

void NavDestinationLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(Claim(frameNode));
    CHECK_NULL_VOID(hostNode);
    auto navDestinationLayoutProperty =
        AceType::DynamicCast<NavDestinationLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(navDestinationLayoutProperty);

    float titlebarHeight = LayoutTitleBar(frameNode, hostNode, navDestinationLayoutProperty);
    LayoutContent(frameNode, hostNode, navDestinationLayoutProperty, titlebarHeight);
}

} // namespace OHOS::Ace::NG