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

#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void BuildTitle(const RefPtr<NavDestinationGroupNode>& navDestinationNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_VOID_NOLOG(navDestinationNode->GetTitle());
    if (navDestinationNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navDestinationNode->GetTitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
    }
    titleBarNode->SetTitle(navDestinationNode->GetTitle());
    titleBarNode->AddChild(titleBarNode->GetTitle());
}

void BuildSubtitle(const RefPtr<NavDestinationGroupNode>& navDestinationNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (!navDestinationNode->GetSubtitle() && titleBarNode->GetSubtitle()) {
        auto subtitleNode = titleBarNode->GetSubtitle();
        titleBarNode->SetSubtitle(nullptr);
        titleBarNode->RemoveChild(subtitleNode);
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    CHECK_NULL_VOID_NOLOG(navDestinationNode->GetSubtitle());
    if (navDestinationNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
        return;
    }
    if (navDestinationNode->GetSubtitleNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
    }
    titleBarNode->SetSubtitle(navDestinationNode->GetSubtitle());
    titleBarNode->AddChild(titleBarNode->GetSubtitle());
}

void BuildTitleBar(const RefPtr<NavDestinationGroupNode>& navDestinationNode, const RefPtr<TitleBarNode>& titleBarNode,
    RefPtr<NavDestinationLayoutProperty>& navDestinationLayoutProperty)
{
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    // back button icon
    if (navDestinationLayoutProperty->HasNoPixMap()) {
        if (navDestinationLayoutProperty->HasImageSource()) {
            titleBarLayoutProperty->UpdateImageSource(navDestinationLayoutProperty->GetImageSourceValue());
        }
        if (navDestinationLayoutProperty->HasPixelMap()) {
            titleBarLayoutProperty->UpdatePixelMap(navDestinationLayoutProperty->GetPixelMapValue());
        }
        titleBarLayoutProperty->UpdateNoPixMap(navDestinationLayoutProperty->GetNoPixMapValue());
    }

    BuildTitle(navDestinationNode, titleBarNode);
    BuildSubtitle(navDestinationNode, titleBarNode);
}

void MountTitleBar(const RefPtr<NavDestinationGroupNode>& hostNode)
{
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    BuildTitleBar(hostNode, titleBarNode, navDestinationLayoutProperty);
}

} // namespace

void NavDestinationPattern::OnActive()
{
    Pattern::OnActive();
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(navDestinationContext);
    if (!(navDestinationContext->GetBackgroundColor().has_value())) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<AppTheme>();
        if (theme) {
            navDestinationContext->UpdateBackgroundColor(theme->GetBackgroundColor());
        }
    }
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    titleBarNode->MarkModifyDone();
}

void NavDestinationPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationPattern = hostNode->GetPattern<NavDestinationPattern>();
    if (navDestinationPattern->GetName().empty()) {
        if (hostNode->GetInspectorId().has_value()) {
            navDestinationPattern->SetName(hostNode->GetInspectorIdValue());
        } else {
            auto id = GetHost()->GetId();
            navDestinationPattern->SetName(std::to_string(id));
        }
    }
    MountTitleBar(hostNode);
}
} // namespace OHOS::Ace::NG
