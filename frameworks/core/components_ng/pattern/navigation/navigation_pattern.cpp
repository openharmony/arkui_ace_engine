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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void RemoveChildByIndex(const RefPtr<UINode>& parent, int32_t index)
{
    auto iter = parent->GetChildren().begin();
    std::advance(iter, index);
    parent->RemoveChild(*iter);
}

void BuildTitleAndSubtitle(
    const RefPtr<NavigationGroupNode>& navigationGroupNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (!navigationGroupNode->GetTitle() && !navigationGroupNode->GetSubtitle()) {
        return;
    }
    if (navigationGroupNode->GetTitle() && navigationGroupNode->HasTitleNodeOperation()) {
        if (navigationGroupNode->GetTitleNodeOperationValue() != ChildNodeOperation::NONE) {
            if (navigationGroupNode->GetTitleNodeOperationValue() == ChildNodeOperation::REPLACE &&
                navigationGroupNode->HasTitleIndex()) {
                RemoveChildByIndex(titleBarNode, navigationGroupNode->GetTitleIndexValue());
            }
            titleBarNode->UpdateTitleIndex(static_cast<int32_t>(titleBarNode->GetChildren().size()));
            titleBarNode->AddChild(navigationGroupNode->GetTitle());
        }
    }
    if (navigationGroupNode->GetSubtitle() && navigationGroupNode->HasSubtitleNodeOperation()) {
        if (navigationGroupNode->GetSubtitleNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (navigationGroupNode->GetTitleNodeOperationValue() == ChildNodeOperation::REPLACE &&
            navigationGroupNode->HasSubtitleIndex()) {
            RemoveChildByIndex(titleBarNode, navigationGroupNode->GetSubtitleIndexValue());
        }
        titleBarNode->UpdateSubtitleIndex(static_cast<int32_t>(titleBarNode->GetChildren().size()));
        titleBarNode->AddChild(navigationGroupNode->GetSubtitle());
    }
}

void BuildMenu(const RefPtr<NavigationGroupNode>& navigationGroupNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (navigationGroupNode->GetMenu() && navigationGroupNode->HasMenuNodeOperation()) {
        if (navigationGroupNode->GetMenuNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (navigationGroupNode->GetMenuNodeOperationValue() == ChildNodeOperation::REPLACE &&
            navigationGroupNode->HasMenuIndex()) {
            RemoveChildByIndex(titleBarNode, navigationGroupNode->GetMenuIndexValue());
        }
        titleBarNode->UpdateMenuIndex(static_cast<int32_t>(titleBarNode->GetChildren().size()));
        titleBarNode->AddChild(navigationGroupNode->GetMenu());
    }
}

void BuildTitleBar(const RefPtr<NavigationGroupNode>& navigationGroupNode, const RefPtr<TitleBarNode>& titleBarNode,
    RefPtr<NavigationLayoutProperty>& navigationLayoutProperty)
{
    if (!navigationGroupNode->GetTitleBarNode() || !navigationGroupNode->HasTitleBarIndex()) {
        return;
    }
    do {
        if (!navigationGroupNode->HasBackButtonNodeOperation() ||
            navigationLayoutProperty->GetTitleModeValue() != NavigationTitleMode::MINI ||
            navigationGroupNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::NONE) {
            break;
        }
        if (navigationGroupNode->GetBackButtonNodeOperationValue() == ChildNodeOperation::REMOVE) {
            RemoveChildByIndex(titleBarNode, navigationGroupNode->GetTitleBarIndexValue());
            titleBarNode->ResetBackButtonIndex();
            break;
        }
        // TODO: fix error for update condition when add or delete child
        titleBarNode->UpdateBackButtonIndex(static_cast<int32_t>(titleBarNode->GetChildren().size()));
        titleBarNode->AddChild(navigationGroupNode->GetBackButton());
    } while (false);
    auto titleBarProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarProperty);
    titleBarProperty->UpdateTitleMode(navigationLayoutProperty->GetTitleModeValue());
    if (navigationLayoutProperty->HasHideTitleBar()) {
        titleBarProperty->UpdateHideTitleBar(navigationLayoutProperty->GetHideTitleBarValue());
    }
    BuildTitleAndSubtitle(navigationGroupNode, titleBarNode);
    BuildMenu(navigationGroupNode, titleBarNode);
}

void MountTitleBar(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    if (!hostNode->GetTitle() && !hostNode->GetSubtitle() && !hostNode->GetMenu() &&
        navigationLayoutProperty->GetTitleModeValue() != NavigationTitleMode::MINI) {
        return;
    }
    if (!hostNode->HasTitleBarIndex()) {
        int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>(V2::TITLE_BAR_ETS_TAG, nodeId);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        if (navigationLayoutProperty->HasHideBackButton()) {
            titleBarLayoutProperty->UpdateHideBackButton(navigationLayoutProperty->GetHideBackButtonValue());
        }
        hostNode->SetTitleBarNode(titleBarNode);
        hostNode->UpdateTitleBarIndex(static_cast<int32_t>(hostNode->GetChildren().size()));
        hostNode->AddChild(titleBarNode);
    }
    BuildTitleBar(hostNode, AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode()), navigationLayoutProperty);
}

void MountToolBar(const RefPtr<NavigationGroupNode>& hostNode)
{
    if (hostNode->GetToolBarNode() && hostNode->HasToolBarNodeOperation()) {
        if (hostNode->GetToolBarNodeOperationValue() == ChildNodeOperation::NONE) {
            return;
        }
        if (hostNode->GetToolBarNodeOperationValue() == ChildNodeOperation::REPLACE &&
            hostNode->HasToolBarIndex()) {
            RemoveChildByIndex(hostNode, hostNode->GetToolBarIndexValue());
        }
        auto node = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarNode());
        CHECK_NULL_VOID(node);
        hostNode->UpdateToolBarIndex(static_cast<int32_t>(hostNode->GetChildren().size()));
        hostNode->AddChild(hostNode->GetToolBarNode());
    }
}
} // namespace

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto navigationLayoutAlgorithm =
        DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(navigationLayoutAlgorithm, false);
    // TODO: add scroll effect to title and subtitle
    lastScrollDistance_ = navigationLayoutAlgorithm->GetLastScrollDistance();
    return false;
}

void NavigationPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountTitleBar(hostNode);
    MountToolBar(hostNode);
}

void NavigationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
}

} // namespace OHOS::Ace::NG