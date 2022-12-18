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

#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"

namespace OHOS::Ace::NG {

namespace {

void MountNavBar(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (navigationLayoutProperty->GetHideNavBar().value_or(false)) {
        navBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        eventHub->FireNavBarStateChangeEvent(false);
    } else {
        navBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        eventHub->FireNavBarStateChangeEvent(true);
    }
    navBarNode->MarkModifyDone();
}

}

void NavigationPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountNavBar(hostNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->MarkModifyDone();
}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto navigationLayoutAlgorithm =
        DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(navigationLayoutAlgorithm, false);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    CHECK_NULL_RETURN(navigationLayoutProperty, false);
    navigationLayoutProperty->UpdateNavigationMode(navigationLayoutAlgorithm->GetNavigationMode());
    return false;
}

} // namespace OHOS::Ace::NG