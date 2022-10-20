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
    auto navBarContentNode = navBarNode->GetNavBarContentNode();
    CHECK_NULL_VOID(navBarContentNode);
    for (const auto& child : navBarContentNode->GetChildren()) {
        AddBackButtonIconToNavDestination(child, hostNode);
    }
}

void NavigationPattern::AddBackButtonIconToNavDestination(const RefPtr<UINode>& child,
    const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navRouter = AceType::DynamicCast<NavRouterGroupNode>(child);
    CHECK_NULL_VOID(navRouter);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navRouter->GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    auto navDestinationLayoutProperty = navDestination->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);

    // back button icon
    if (navigationLayoutProperty->HasNoPixMap()) {
        if (navigationLayoutProperty->HasImageSource()) {
            navDestinationLayoutProperty->UpdateImageSource(navigationLayoutProperty->GetImageSourceValue());
        }
        if (navigationLayoutProperty->HasPixelMap()) {
            navDestinationLayoutProperty->UpdatePixelMap(navigationLayoutProperty->GetPixelMapValue());
        }
        navDestinationLayoutProperty->UpdateNoPixMap(navigationLayoutProperty->GetNoPixMapValue());
    }
    navDestination->MarkModifyDone();
}

} // namespace OHOS::Ace::NG