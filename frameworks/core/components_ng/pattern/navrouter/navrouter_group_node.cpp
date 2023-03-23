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
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
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

void NavRouterGroupNode::OnDetachFromMainTree()
{
    FrameNode::OnDetachFromMainTree();
    auto parent = GetParent();
    while (parent) {
        if (CleanNodeInNavigation(parent)) {
            return;
        }
        parent = parent->GetParent();
    }
}

void NavRouterGroupNode::OnAttachToMainTree()
{
    FrameNode::OnAttachToMainTree();
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
    InitNavigationContent(parent);
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

void NavRouterGroupNode::InitNavigationContent(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (navigationNode->IsFirstNavDestination() &&
        layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
        AddNavDestinationToNavigation(parent);
        auto eventHub = GetEventHub<NavRouterEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireChangeEvent(true);
        navigationNode->MarkIsFirstNavDestination(false);
    }
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
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent = [navDestination = navDestination,
        navigation = navigationNode, weak = WeakClaim(this)](GestureEvent& /*info*/) {
        auto navRouter = weak.Upgrade();
        CHECK_NULL_VOID(navRouter);
        auto layoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);

        auto destinationContent = navDestination->GetContentNode();
        if (destinationContent) {
            auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            CHECK_NULL_VOID(shallowBuilder);
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            destinationContent->Clean();
        }

        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
            if (navDestination->GetPreNode()) {
                navRouter->BackToPreNavDestination(navDestination->GetPreNode(), navigation);
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
            if (navDestination->GetPreNode()) {
                navRouter->BackToPreNavDestination(navDestination->GetPreNode(), navigation);
                navRouter->SetOnStateChangeFalse(navDestination, navigation, true);
                layoutProperty->UpdateDestinationChange(false);
                return;
            }
        }
        navigation->MarkModifyDone();
    };
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
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    const auto& children = navigationContentNode->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        const auto& childNode = *iter;
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(childNode);
        if (navDestinationNode && navDestinationNode != navDestination) {
            auto destinationContent = navDestinationNode->GetContentNode();
            if (destinationContent) {
                auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
                CHECK_NULL_VOID(navDestinationPattern);
                auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
                CHECK_NULL_VOID(shallowBuilder);
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
                destinationContent->Clean();
            }
            navDestination->SetPreNode(navDestinationNode);
            SetOnStateChangeFalse(navDestinationNode, parent);
            break;
        }
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
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (navBarNode && layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
        navigationContentNode->Clean();
        navigationContentNode->AddChild(navDestination);
        navigationContentNode->MarkModifyDone();
        navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    SetBackButtonVisible(navDestination);
    navigationContentNode->Clean();
    navigationContentNode->AddChild(navDestination);
    navigationContentNode->MarkModifyDone();
    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);
    if (!isBackButton && navDestination == preNavDestination) {
        return;
    }

    if (isBackButton) {
        auto newDestiantion = AceType::DynamicCast<FrameNode>(navDestination->GetPreNode());
        CHECK_NULL_VOID(newDestiantion);
        auto newEventHub = newDestiantion->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(newEventHub);
        newEventHub->FireChangeEvent(true);
    }

    auto preNavDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNavDestination);
    CHECK_NULL_VOID(preNavDestinationNode);
    auto eventHub = preNavDestinationNode->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireChangeEvent(false);
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
    navigationContentNode->Clean();
    navigationContentNode->AddChild(navDestination);
    navigationContentNode->MarkModifyDone();
    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool NavRouterGroupNode::CleanNodeInNavigation(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_RETURN(navigationNode, false);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
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
