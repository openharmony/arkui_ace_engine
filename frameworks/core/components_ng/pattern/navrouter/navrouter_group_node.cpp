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

#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
RefPtr<NavRouterGroupNode> NavRouterGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN_NOLOG(!frameNode, AceType::DynamicCast<NavRouterGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navRouterGroupNode = AceType::MakeRefPtr<NavRouterGroupNode>(tag, nodeId, pattern);
    navRouterGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navRouterGroupNode);
    return navRouterGroupNode;
}

void NavRouterGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(child);
    if (navDestination) {
        SetNavDestinationNode(navDestination);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto navRouterPattern = GetPattern<NavRouterPattern>();
        CHECK_NULL_VOID(navRouterPattern);
        navRouterPattern->SetNavDestination(navDestinationPattern->GetName());
        auto navDestinationNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(navDestinationNode);
        auto navDestinationEventHub =
            AceType::DynamicCast<NavDestinationEventHub>(navDestinationNode->GetEventHub<EventHub>());
        CHECK_NULL_VOID(navDestinationEventHub);
        auto eventHub = GetEventHub<NavRouterEventHub>();
        CHECK_NULL_VOID(eventHub);
        navDestinationEventHub->SetOnStateChange(eventHub->GetOnStateChange());
        return;
    }
    UINode::AddChild(child);
}

void NavRouterGroupNode::DeleteChildFromGroup(int32_t slot)
{
    UINode::RemoveChildAtIndex(slot);
}

void NavRouterGroupNode::OnDetachFromMainTree(bool recursive)
{
    FrameNode::OnDetachFromMainTree(recursive);
}

void NavRouterGroupNode::OnAttachToMainTree(bool recursive)
{
    if (!UseOffscreenProcess()) {
        ProcessDestinationChangeEvent();
    }
    FrameNode::OnAttachToMainTree(recursive);
}

void NavRouterGroupNode::OnOffscreenProcess(bool recursive)
{
    ProcessDestinationChangeEvent();
    FrameNode::OnOffscreenProcess(recursive);
}

void NavRouterGroupNode::ProcessDestinationChangeEvent()
{
    auto parent = GetParent();
    while (parent) {
        auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
        if (navigationNode) {
            break;
        }
        parent = parent->GetParent();
    }
    SetDestinationChangeEvent(parent);
}

void NavRouterGroupNode::SetDestinationChangeEvent(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto onDestinationChange = [weak = WeakClaim(this), navigation = navigationNode]() {
        auto navRouter = weak.Upgrade();
        CHECK_NULL_VOID(navRouter);
        auto layoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto navigationPattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        navRouter->AddNavDestinationToNavigation(navigation);
    };
    auto eventHub = GetEventHub<NavRouterEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestinationChange(std::move(onDestinationChange));
}

void NavRouterGroupNode::AddNavDestinationToNavigation(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    // get the navDestination under NavRouter
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    // do nothing if this navDestination is already at the top
    if (navDestination && navigationPattern->GetNavDestinationNode() == navDestination) {
        LOGW("this navDestination is displaying");
        return;
    }

    auto parentNode = GetParent();
    while (parentNode) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(parentNode);
        if (navBarNode) {
            break;
        }
        parentNode = parentNode->GetParent();
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(parentNode);
    // deal with split mode without user provided navigation stack
    if (navBarNode && navigationPattern->GetNavigationMode() == NavigationMode::SPLIT &&
        !navigationPattern->GetNavigationStackProvided()) {
        navigationPattern->CleanStack();
    }

    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    std::string name;
    auto navRouteMode = navRouterPattern->GetNavRouteMode();
    if (!navDestination && routeInfo) {
        // create navDestination with routeInfo
        name = routeInfo->GetName();
        auto uiNode = navigationStack->CreateNodeByRouteInfo(routeInfo);
        navigationPattern->AddNavDestinationNode(name, uiNode, navRouteMode, routeInfo);
    } else if (navDestination) {
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        name = navDestinationPattern->GetName();
        navigationPattern->RemoveIfNeeded(name, navDestination);
        navigationPattern->AddNavDestinationNode(navRouterPattern->GetNavDestination(), navDestination, navRouteMode);
    }
    CHECK_NULL_VOID(navDestination);
    // the one at the top of the stack
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    if (currentNavDestination && currentNavDestination != navDestination) {
        auto destinationContent = currentNavDestination->GetContentNode();
        if (destinationContent && (navRouteMode != NavRouteMode::PUSH)) {
            auto navDestinationPattern = currentNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            CHECK_NULL_VOID(shallowBuilder);
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            destinationContent->Clean();
        }
    }

    // when js navigationStack is provided, modifyDone will be called by state manager.
    if (!navigationPattern->GetNavigationStackProvided()) {
        navigationNode->MarkModifyDone();
        navigationNode->MarkDirtyNode();
    }
}

bool NavRouterGroupNode::CleanNodeInNavigation(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_RETURN(navigationNode, false);

    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_RETURN(navRouterPattern, false);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, false);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        navigationPattern->GetNavDestinationNode(navRouterPattern->GetNavDestination()));
    CHECK_NULL_RETURN(navDestination, false);
    auto navigationContentNode = navigationNode->GetContentNode();
    CHECK_NULL_RETURN(navigationContentNode, false);

    const auto& children = navigationContentNode->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        const auto& childNode = *iter;
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(childNode);
        if (navDestinationNode == navDestination) {
            navigationContentNode->RemoveChild(navDestinationNode);
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG
