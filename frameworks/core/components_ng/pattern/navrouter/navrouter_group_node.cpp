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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<NavRouterGroupNode> NavRouterGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<NavRouterGroupNode>(frameNode));
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
        auto navDestinationNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(navDestinationNode);
        auto navDestinationEventHub =
            AceType::DynamicCast<NavDestinationEventHub>(navDestinationNode->GetOrCreateEventHub<EventHub>());
        CHECK_NULL_VOID(navDestinationEventHub);
        auto eventHub = GetOrCreateEventHub<NavRouterEventHub>();
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

void NavRouterGroupNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    // remove node in navigation
    do {
        if (!navDestinationNode_) {
            break;
        }
        auto navigationNode = weakNavigation_.Upgrade();
        if (!navigationNode) {
            break;
        }
        auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
        auto stack = navigationPattern->GetNavigationStack();
        if (!stack) {
            break;
        }
        auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(
            DynamicCast<NavDestinationGroupNode>(navDestinationNode_)->GetPattern());
        stack->Remove(navDestinationPattern->GetName(), navDestinationNode_);
    } while (false);
    FrameNode::OnDetachFromMainTree(recursive, context);
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
            weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
            break;
        }
        parent = parent->GetParent();
    }
    auto onDestinationChange = [weak = WeakClaim(this)]() {
        auto navRouter = weak.Upgrade();
        CHECK_NULL_VOID(navRouter);
        navRouter->AddNavDestinationToNavigation();
    };
    auto eventHub = GetOrCreateEventHub<NavRouterEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestinationChange(std::move(onDestinationChange));
}

void NavRouterGroupNode::AddNavDestinationToNavigation()
{
    auto navigationNode = weakNavigation_.Upgrade();
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    // get the navDestination under NavRouter
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    // do nothing if this navDestination is already at the top
    if (navDestination && currentNavDestination == navDestination) {
        return;
    }
    // deal with split mode without user provided navigation stack
    if (navigationPattern->GetNavigationMode() == NavigationMode::SPLIT &&
        !navigationPattern->GetNavigationStackProvided()) {
        navigationPattern->CleanStack();
        navigationPattern->UpdateAnimatedValue(false);
    } else {
        navigationPattern->UpdateAnimatedValue(true);
    }

    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    std::string name;
    auto navRouteMode = navRouterPattern->GetNavRouteMode();
    if (routeInfo) {
        // create navDestination with routeInfo
        name = routeInfo->GetName();
        RefPtr<UINode> uiNode = navigationStack->GetFromCacheNode(name);
        if (uiNode == nullptr) {
            uiNode = navigationStack->CreateNodeByRouteInfo(routeInfo, navigationPattern->GetParentCustomNode());
        }

        navigationPattern->AddNavDestinationNode(name, uiNode, navRouteMode, routeInfo);
        auto navRouterEventHub = GetOrCreateEventHub<NavRouterEventHub>();
        CHECK_NULL_VOID(navRouterEventHub);
        if (uiNode) {
            navigationPattern->AddOnStateChangeItem(uiNode->GetId(), navRouterEventHub->GetOnStateChange());
        }
        navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(uiNode));
    } else if (navDestination) {
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        navDestination->SetFromNavrouterAndNoRouteInfo(true);
        auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
        if (shallowBuilder && navRouteMode != NavRouteMode::PUSH) {
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
        }
        auto destinationContent = navDestination->GetContentNode();
        if (destinationContent && navRouteMode != NavRouteMode::PUSH) {
            destinationContent->Clean();
        }
        WeakPtr<NavigationStack> stack = navigationPattern->GetNavigationStack();
        navDestinationPattern->SetNavigationStack(stack);
        name = navDestinationPattern->GetName();
        navigationPattern->AddNavDestinationNode(name, navDestination, navRouteMode);
    }
    if (navDestination) {
        navDestination->SetInCurrentStack(true);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        navDestinationPattern->SetNavigationId(navigationNode->GetInspectorId().value_or(""));
    }

    // when js navigationStack is provided, modifyDone will be called by state manager.
    if (!navigationPattern->GetNavigationStackProvided()) {
        navigationNode->MarkModifyDone();
        navigationNode->MarkDirtyNode();
    }
}
} // namespace OHOS::Ace::NG
