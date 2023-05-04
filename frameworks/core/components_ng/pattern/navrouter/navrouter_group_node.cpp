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
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
    auto parent = GetParent();
    while (parent) {
        if (CleanNodeInNavigation(parent)) {
            return;
        }
        parent = parent->GetParent();
    }
}

void NavRouterGroupNode::OnAttachToMainTree(bool recursive)
{
    FrameNode::OnAttachToMainTree(recursive);
    auto parent = GetParent();
    while (parent) {
        auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
        if (navigationNode) {
            break;
        }
        parent = parent->GetParent();
    }
    SetDestinationChangeEvent(parent);
    SetBackButtonEvent(parent);
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
        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
            layoutProperty->UpdateDestinationChange(true);
        }
        navRouter->AddNavDestinationToNavigation(navigation);
    };
    auto eventHub = GetEventHub<NavRouterEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestinationChange(std::move(onDestinationChange));
}

void NavRouterGroupNode::AddBackButtonIconToNavDestination(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
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
        navDestination->MarkModifyDone();
    }
}

void NavRouterGroupNode::SetBackButtonEvent(const RefPtr<UINode>& parent)
{
    AddBackButtonIconToNavDestination(parent);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    // navdestination under navrouter
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto onBackButtonEvent = [navDestination = navDestination, navigation = navigationNode,
                                 navigationPattern = navigationPattern, navRouterPattern = navRouterPattern,
                                 weak = WeakClaim(this)](GestureEvent& /*info*/) {
        // the one before navdestination in the stack
        auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationPattern->GetPreNavDestination(navRouterPattern->GetNavDestination()));
        auto navRouter = weak.Upgrade();
        CHECK_NULL_VOID(navRouter);
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto onBackPressed = eventHub->GetOnBackPressedEvent();
        bool isOverride = false;
        if (onBackPressed != nullptr) {
            isOverride = eventHub->FireOnBackPressedEvent();
        }
        auto destinationContent = navDestination->GetContentNode();
        if (destinationContent) {
            auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            CHECK_NULL_VOID(shallowBuilder);
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            auto mode = navRouterPattern->GetNavRouteMode();
            if (mode == NavRouteMode::PUSH_WITH_RECREATE || mode == NavRouteMode::REPLACE) {
                destinationContent->Clean();
            }
        }
        if (isOverride) {
            LOGI("this onBackButtonPressed event returns false");
            return;
        }
        auto layoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
            if (preNavDestination) {
                navRouter->BackToPreNavDestination(preNavDestination, navigation);
                navRouter->SetOnStateChangeFalse(navDestination, navigation, true);
                layoutProperty->UpdateDestinationChange(true);
                return;
            }
            navRouter->BackToNavBar(navigation);
            navRouter->SetOnStateChangeFalse(navDestination, navigation, true);
            layoutProperty->UpdateDestinationChange(false);
            return;
        }

        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
            if (preNavDestination) {
                navRouter->BackToPreNavDestination(preNavDestination, navigation);
                navRouter->SetOnStateChangeFalse(navDestination, navigation, true);
                layoutProperty->UpdateDestinationChange(false);
                return;
            }
        }
        navigation->MarkModifyDone();
    }; // backButton event

    navDestination->SetNavDestinationBackButtonEvent(onBackButtonEvent);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(onBackButtonEvent));
    if (backButtonEventHub->GetGestureEventHub()) {
        return;
    }
    backButtonEventHub->GetOrCreateGestureEventHub()->AddClickEvent(clickEvent);
}

void NavRouterGroupNode::AddNavDestinationToNavigation(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    // the navDestination under Navrouter
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    auto navigationStack = navigationPattern->GetNavigationStack();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    std::string name;
    bool withRouteInfo = false;
    if (!navDestination && routeInfo) {
        // create NavRouter with routerInfo
        name = routeInfo->GetName();
        withRouteInfo = true;
        auto uiNode = navigationStack->CreateNodeByRouteInfo(routeInfo);
        navDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
    }
    CHECK_NULL_VOID(navDestination);
    // the one at the top of the stack
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    if (currentNavDestination && currentNavDestination != navDestination) {
        auto destinationContent = currentNavDestination->GetContentNode();
        if (destinationContent) {
            auto navDestinationPattern = currentNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            CHECK_NULL_VOID(shallowBuilder);
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            destinationContent->Clean();
        }
        SetOnStateChangeFalse(currentNavDestination, parent);
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
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navRouteMode = navRouterPattern->GetNavRouteMode();
    if (navBarNode && navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
        navigationContentNode->AddChild(navDestination);
        if (withRouteInfo) {
            navigationPattern->AddNavDestinationNode(name, navDestination, navRouteMode, routeInfo);
        } else {
            navigationPattern->AddNavDestinationNode(
                navRouterPattern->GetNavDestination(), navDestination, navRouteMode);
        }

        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnShownEvent();
        navigationNode->MarkModifyDone();
        navigationNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    SetBackButtonVisible(navDestination);
    navigationContentNode->AddChild(navDestination);
    if (withRouteInfo) {
        navigationPattern->AddNavDestinationNode(name, navDestination, navRouteMode, routeInfo);
    } else {
        navigationPattern->AddNavDestinationNode(navRouterPattern->GetNavDestination(), navDestination, navRouteMode);
    }
    auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    navigationNode->MarkModifyDone();
    navigationNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavRouterGroupNode::SetOnStateChangeFalse(
    const RefPtr<UINode>& preNavDestination, const RefPtr<UINode>& navigation, bool isBackButton)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarContentNode = navBarNode->GetNavBarContentNode();
    CHECK_NULL_VOID(navBarContentNode);
    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        navigationPattern->GetNavDestinationNode(navRouterPattern->GetNavDestination()));
    CHECK_NULL_VOID(navDestination);
    if (!isBackButton && navDestination == preNavDestination) {
        return;
    }

    auto newDestiantion = AceType::DynamicCast<NavDestinationGroupNode>(
        navigationPattern->GetPreNavDestination(navRouterPattern->GetNavDestination()));
    if (isBackButton && newDestiantion) {
        auto newEventHub = newDestiantion->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(newEventHub);
        newEventHub->FireChangeEvent(true);
        newEventHub->FireOnShownEvent();
    }

    auto preNavDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNavDestination);
    CHECK_NULL_VOID(preNavDestinationNode);
    auto eventHub = preNavDestinationNode->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireChangeEvent(false);
    eventHub->FireOnHiddenEvent();
}

void NavRouterGroupNode::BackToNavBar(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    navigationContentNode->Clean();
    navigationContentNode->MarkModifyDone();
    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavRouterGroupNode::BackToPreNavDestination(
    const RefPtr<UINode>& preNavDestination, const RefPtr<UINode>& navigation)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNavDestination);
    CHECK_NULL_VOID(navDestination);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    navigationContentNode->AddChild(navDestination);
    navigationContentNode->MarkModifyDone();
    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
            navigationContentNode->RemoveChildAtIndex(navDestinationNode);
            return true;
        }
    }
    return false;
}

void NavRouterGroupNode::SetBackButtonVisible(const RefPtr<UINode>& navDestination)
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestination);
    CHECK_NULL_VOID(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    backButtonNode->MarkModifyDone();
}
} // namespace OHOS::Ace::NG
