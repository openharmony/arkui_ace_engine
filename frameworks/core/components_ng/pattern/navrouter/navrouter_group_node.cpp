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
#include "core/common/container.h"
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
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF = 0.5;
constexpr double PARENT_PAGE_OFFSET = 0.2;
constexpr double PARENT_TITLE_OFFSET = 0.02;
constexpr int32_t MASK_DURATION = 350;
constexpr int32_t OPACITY_TITLE_OUT_DELAY = 17;
constexpr int32_t OPACITY_TITLE_IN_DELAY = 33;
constexpr int32_t OPACITY_TITLE_DURATION = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DELAY = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DURATION = 200;
constexpr int32_t OPACITY_BACKBUTTON_OUT_DURATION = 67;
constexpr int32_t DEFAULT_ANIMATION_DURATION = 400;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
const Color DEFAULT_MASK_COLOR = Color::FromARGB(0, 0, 0, 0);
const RefPtr<InterpolatingSpring> interpolatingSpringCurve =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
} // namespace
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
    auto weak = WeakClaim(this);
    auto navRouter = weak.Upgrade();
    CHECK_NULL_VOID(navRouter);
    auto onBackButtonEvent = [navDestination = navDestination, navigation = navigationNode, navRouter = navRouter](
                                 GestureEvent& /*info*/) {
        // the one before navdestination in the stack
        auto navRouterPattern = navRouter->GetPattern<NavRouterPattern>();
        CHECK_NULL_VOID(navRouterPattern);
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
        auto navigationPattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationPattern->GetPreNavDestination(navRouterPattern->GetNavDestination()));
        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
            if (preNavDestination) {
                navRouter->BackToPreNavDestination(preNavDestination, navigation, navRouterPattern);
                navRouter->SetOnStateChangeFalse(navDestination, navDestination, navigation, true);
                layoutProperty->UpdateDestinationChange(true);
                return;
            }
            navRouter->BackToNavBar(navigation);
            navRouter->SetOnStateChangeFalse(navDestination, navDestination, navigation, true);
            layoutProperty->UpdateDestinationChange(false);
            return;
        }

        if (layoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
            if (preNavDestination) {
                navRouter->BackToPreNavDestination(preNavDestination, navigation, navRouterPattern);
                navRouter->SetOnStateChangeFalse(navDestination, navDestination, navigation, true);
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
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    // get the navDestination under NavRouter
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    auto navigationStack = navigationPattern->GetNavigationStack();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    std::string name;
    bool withRouteInfo = false;
    if (!navDestination && routeInfo) {
        // create navDestination with routerInfo
        name = routeInfo->GetName();
        withRouteInfo = true;
        auto uiNode = navigationStack->CreateNodeByRouteInfo(routeInfo);
        navDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
        CHECK_NULL_VOID(navDestination);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        navDestinationPattern->SetName(name);
        navDestinationPattern->SetRouteInfo(routeInfo);
        navRouterPattern->SetNavDestination(name);
    } else if (navDestination) {
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        name = navDestinationPattern->GetName();
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
        SetOnStateChangeFalse(currentNavDestination, navDestination, parent);
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
    if (navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) != NavigationMode::SPLIT) {
        SetBackButtonVisible(navDestination);
    }
    if (navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
        if (navBarNode) {
            auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
            auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
            auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
            if (titleBarNode || destinationTitleBarNode) {
                TitleTransitionInAnimation(navigationNode, titleBarNode, destinationTitleBarNode);
            }
            if (backButtonNode) {
                BackButtonAnimation(backButtonNode, true);
            }
            NavTransitionInAnimation(navigationNode, navBarNode, navDestination);
        } else {
            // stack. More than one destination
            currentNavDestination =
                AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
            CHECK_NULL_VOID(currentNavDestination);
            auto curNavTitleBarNode = AceType::DynamicCast<TitleBarNode>(currentNavDestination->GetTitleBarNode());
            auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
            auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
            if (curNavTitleBarNode || destinationTitleBarNode) {
                TitleTransitionInAnimation(navigationNode, curNavTitleBarNode, destinationTitleBarNode);
            }
            if (backButtonNode) {
                BackButtonAnimation(backButtonNode, true);
            }
            NavTransitionInAnimation(navigationNode, currentNavDestination, navDestination);
        }
    }
    // remove if this navDestinationNode is already in the NavigationStack and not at the top, which will be later
    // modified by NavRouteMode
    navigationPattern->RemoveIfNeeded(name, navDestination);

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

void NavRouterGroupNode::SetOnStateChangeFalse(const RefPtr<UINode>& preNavDestination,
    const RefPtr<UINode>& navDestination, const RefPtr<UINode>& navigation, bool isBackButton)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarContentNode = navBarNode->GetNavBarContentNode();
    CHECK_NULL_VOID(navBarContentNode);
    if (!isBackButton && navDestination == preNavDestination) {
        return;
    }

    auto navRouterPattern = GetPattern<NavRouterPattern>();
    CHECK_NULL_VOID(navRouterPattern);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
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
}

void NavRouterGroupNode::BackToNavBar(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_VOID(navigationNode);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(navDestination);

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
    if (titleBarNode || destinationTitleBarNode) {
        TitleTransitionOutAnimation(navigationNode, titleBarNode, destinationTitleBarNode);
    }
    if (backButtonNode) {
        BackButtonAnimation(backButtonNode, false);
    }
    NavTransitionOutAnimation(navigationNode, navBarNode, navigationContentNode);
    auto navigationPattern = AceType::DynamicCast<NavigationGroupNode>(navigationNode)->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->RemoveNavDestination();
}

void NavRouterGroupNode::BackToPreNavDestination(const RefPtr<UINode>& preNavDestination,
    const RefPtr<UINode>& navigation, const RefPtr<NavRouterPattern>& navRouterPattern)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNavDestination);
    CHECK_NULL_VOID(navDestination);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);

    auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode());
    CHECK_NULL_VOID(curNavDestination);
    auto preDestinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(curNavDestination->GetTitleBarNode());
    if (preDestinationTitleBarNode || destinationTitleBarNode) {
        TitleTransitionOutAnimation(navigationNode, preDestinationTitleBarNode, destinationTitleBarNode);
    }
    auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
    if (backButtonNode) {
        BackButtonAnimation(backButtonNode, false);
    }
    NavTransitionBackToPreAnimation(navigationNode, navDestination, curNavDestination, navigationContentNode);

    navigationContentNode->AddChild(navDestination);
    auto navigationPattern = AceType::DynamicCast<NavigationGroupNode>(navigation)->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    auto routeInfo = navDestinationPattern->GetRouteInfo();
    auto navRouteMode = NavRouteMode::REPLACE;
    if (routeInfo) {
        auto name = routeInfo->GetName();
        navigationPattern->AddNavDestinationNode(name, navDestination, navRouteMode, routeInfo);
    } else {
        auto name = navDestinationPattern->GetName();
        navigationPattern->AddNavDestinationNode(name, navDestination, navRouteMode);
    }
}

bool NavRouterGroupNode::CleanNodeInNavigation(const RefPtr<UINode>& parent)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
    CHECK_NULL_RETURN(navigationNode, false);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return false;
    }
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

void NavRouterGroupNode::NavTransitionInAnimation(const RefPtr<FrameNode>& navigation,
    const RefPtr<FrameNode>& transitionOutNode, const RefPtr<FrameNode>& navDestination)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    auto transitionOutNodeContext = transitionOutNode->GetRenderContext();
    auto transitionInNodeContext = navDestination->GetRenderContext();
    CHECK_NULL_VOID(transitionOutNodeContext && transitionInNodeContext);
    auto size = navigationNode->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();
    option.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakClaim(RawPtr(transitionOutNodeContext)),
            navigationNodeWK = WeakClaim(RawPtr(navigationNode)), navDestinationWK = WeakClaim(RawPtr(navDestination)),
            id = Container::CurrentId(), nodeHeight] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, navigationNodeWK, navDestinationWK, id, nodeHeight]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    auto navigationNode = navigationNodeWK.Upgrade();
                    auto navDestination = navDestinationWK.Upgrade();
                    ContainerScope scope(id);
                    if (transitionOutNodeContext) {
                        transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                    }
                    if (navDestination) {
                        navDestination->GetRenderContext()->ClipWithRRect(
                            RectF(0.0f, 0.0f, Infinity<float>(), nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                    }
                    navigationNode->SetIsOnAnimation(false);
                },
                TaskExecutor::TaskType::UI);
        });

    transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    transitionInNodeContext->ClipWithRRect(
        RectF(nodeWidth * HALF, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
    transitionInNodeContext->OnTransformTranslateUpdate({ nodeWidth * HALF, 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [transitionOutNodeContext, transitionInNodeContext, nodeWidth, nodeHeight, navigationNode]() {
            navigationNode->SetIsOnAnimation(true);
            transitionOutNodeContext->OnTransformTranslateUpdate({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f, 0.0f });
            transitionInNodeContext->ClipWithRRect(
                RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
            transitionInNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());
    MaskAnimation(transitionOutNodeContext);
}

void NavRouterGroupNode::MaskAnimation(const RefPtr<RenderContext>& transitionOutNodeContext)
{
    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    maskOption.SetFillMode(FillMode::FORWARDS);
    maskOption.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakClaim(RawPtr(transitionOutNodeContext)), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, id]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    ContainerScope scope(id);
                    if (transitionOutNodeContext) {
                        transitionOutNodeContext->SetActualForegroundColor(DEFAULT_MASK_COLOR);
                    }
                },
                TaskExecutor::TaskType::UI);
        });
    AnimationUtils::Animate(
        maskOption, [transitionOutNodeContext]() { transitionOutNodeContext->SetActualForegroundColor(MASK_COLOR); },
        maskOption.GetOnFinishEvent());
}

void NavRouterGroupNode::TitleTransitionInAnimation(const RefPtr<FrameNode>& navigationNode,
    const RefPtr<FrameNode>& titleBarNode, const RefPtr<FrameNode>& destinationTitleBarNode)
{
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    auto transitionOutNodeContext = titleBarNode->GetRenderContext();
    auto transitionInNodeContext = destinationTitleBarNode->GetRenderContext();
    auto size = navigationNode->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();

    option.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakClaim(RawPtr(transitionOutNodeContext)), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, id]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    CHECK_NULL_VOID(transitionOutNodeContext);
                    ContainerScope scope(id);
                    transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                },
                TaskExecutor::TaskType::UI);
        });
    if (transitionOutNodeContext) {
        transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    }
    if (transitionInNodeContext) {
        transitionInNodeContext->OnTransformTranslateUpdate({ nodeWidth * HALF, 0.0f, 0.0f });
    }
    AnimationUtils::Animate(
        option,
        [transitionOutNodeContext, transitionInNodeContext, nodeWidth]() {
            if (transitionOutNodeContext) {
                transitionOutNodeContext->OnTransformTranslateUpdate({ nodeWidth * PARENT_TITLE_OFFSET, 0.0f, 0.0f });
            }
            if (transitionInNodeContext) {
                transitionInNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());

    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDelay(OPACITY_TITLE_IN_DELAY);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    opacityOption.SetFillMode(FillMode::FORWARDS);
    transitionInNodeContext->OpacityAnimation(opacityOption, 0.0f, 1.0f);
}

void NavRouterGroupNode::NavTransitionOutAnimation(const RefPtr<UINode>& navigation,
    const RefPtr<FrameNode>& navBarNode, const RefPtr<FrameNode>& navigationContentNode)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto navigationContext = navBarNode->GetRenderContext();
    CHECK_NULL_VOID(navigationContext);
    auto navDestinationContext = navigationContentNode->GetRenderContext();
    CHECK_NULL_VOID(navDestinationContext);

    auto node = AceType::DynamicCast<FrameNode>(navigationNode);
    auto size = node->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();

    option.SetOnFinishEvent(
        [navigationContentWK = WeakClaim(RawPtr(navigationContentNode)),
            navigationNodeWK = WeakClaim(RawPtr(navigationNode)), id = Container::CurrentId(), nodeHeight] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [navigationContentWK, navigationNodeWK, id, nodeHeight]() {
                    auto navigationContentNode = navigationContentWK.Upgrade();
                    auto navigationNode = navigationNodeWK.Upgrade();
                    CHECK_NULL_VOID(navigationNode && navigationContentNode);
                    navigationContentNode->GetRenderContext()->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                    navigationContentNode->GetRenderContext()->ClipWithRRect(
                        RectF(0.0f, 0.0f, Infinity<float>(), nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                    ContainerScope scope(id);
                    navigationContentNode->MarkModifyDone();
                    navigationNode->MarkModifyDone();
                    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                    navigationNode->SetIsOnAnimation(false);
                },
                TaskExecutor::TaskType::UI);
        });

    navDestinationContext->ClipWithRRect(RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
    navDestinationContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    navigationContext->OnTransformTranslateUpdate({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [navDestinationContext, navigationContext, nodeWidth, nodeHeight, navigationNode]() {
            navigationNode->SetIsOnAnimation(true);
            if (navDestinationContext) {
                navDestinationContext->ClipWithRRect(
                    RectF(nodeWidth * HALF, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                navDestinationContext->OnTransformTranslateUpdate({ nodeWidth * HALF, 0.0f, 0.0f });
            }
            if (navigationContext) {
                navigationContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());

    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    maskOption.SetFillMode(FillMode::FORWARDS);
    navigationContext->SetActualForegroundColor(MASK_COLOR);
    AnimationUtils::Animate(
        maskOption, [navigationContext]() { navigationContext->SetActualForegroundColor(DEFAULT_MASK_COLOR); });
}

void NavRouterGroupNode::NavTransitionBackToPreAnimation(const RefPtr<UINode>& navigation,
    const RefPtr<FrameNode>& preDestination, const RefPtr<FrameNode>& curNavDestination,
    const RefPtr<FrameNode>& navigationContentNode)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigation);
    CHECK_NULL_VOID(navigationNode);
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto preDestinationContext = preDestination->GetRenderContext();
    CHECK_NULL_VOID(preDestinationContext);
    auto navDestinationContext = curNavDestination->GetRenderContext();
    CHECK_NULL_VOID(navDestinationContext);

    auto node = AceType::DynamicCast<FrameNode>(navigationNode);
    auto size = node->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();

    option.SetOnFinishEvent([id = Container::CurrentId(), navigationNodeWK = WeakClaim(RawPtr(navigationNode)),
                                curNavDestinationWK = WeakClaim(RawPtr(curNavDestination)),
                                navigationContentNodeWK = WeakClaim(RawPtr(navigationContentNode)), nodeHeight] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        // animation finish event should be posted to UI thread.
        taskExecutor->PostTask(
            [curNavDestinationWK, navigationContentNodeWK, navigationNodeWK, id, nodeHeight]() {
                auto curNavDestination = curNavDestinationWK.Upgrade();
                auto navigationContentNode = navigationContentNodeWK.Upgrade();
                auto navigationNode = navigationNodeWK.Upgrade();
                CHECK_NULL_VOID(navigationNode && curNavDestination && navigationContentNode);
                curNavDestination->GetRenderContext()->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                curNavDestination->GetRenderContext()->ClipWithRRect(
                    RectF(0.0f, 0.0f, Infinity<float>(), nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                ContainerScope scope(id);
                navigationContentNode->MarkModifyDone();
                navigationNode->MarkModifyDone();
                navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                navigationNode->SetIsOnAnimation(false);
            },
            TaskExecutor::TaskType::UI);
    });

    navDestinationContext->ClipWithRRect(RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
    navDestinationContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    preDestinationContext->OnTransformTranslateUpdate({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [navDestinationContext, preDestinationContext, nodeWidth, nodeHeight, navigationNode]() {
            navigationNode->SetIsOnAnimation(true);
            if (navDestinationContext) {
                navDestinationContext->ClipWithRRect(
                    RectF(nodeWidth * HALF, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                navDestinationContext->OnTransformTranslateUpdate({ nodeWidth * HALF, 0.0f, 0.0f });
            }
            if (preDestinationContext) {
                preDestinationContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());

    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    maskOption.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(
        maskOption, [preDestinationContext]() { preDestinationContext->SetActualForegroundColor(DEFAULT_MASK_COLOR); });
}

void NavRouterGroupNode::TitleTransitionOutAnimation(const RefPtr<FrameNode>& navigationNode,
    const RefPtr<FrameNode>& titleBarNode, const RefPtr<FrameNode>& destinationTitleBarNode)
{
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    auto transitionOutNodeContext = destinationTitleBarNode->GetRenderContext();
    CHECK_NULL_VOID(transitionOutNodeContext);
    auto transitionInNodeContext = titleBarNode->GetRenderContext();
    CHECK_NULL_VOID(transitionInNodeContext);
    auto size = navigationNode->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();

    option.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakClaim(RawPtr(transitionOutNodeContext)), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, id]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    CHECK_NULL_VOID(transitionOutNodeContext);
                    ContainerScope scope(id);
                    transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                },
                TaskExecutor::TaskType::UI);
        });

    transitionOutNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
    transitionInNodeContext->OnTransformTranslateUpdate({ nodeWidth * PARENT_TITLE_OFFSET, 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [transitionOutNodeContext, transitionInNodeContext, nodeWidth]() {
            transitionOutNodeContext->OnTransformTranslateUpdate({ nodeWidth * HALF, 0.0f, 0.0f });
            transitionInNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());
    TitleOpacityAnimation(transitionOutNodeContext);
}

void NavRouterGroupNode::TitleOpacityAnimation(const RefPtr<RenderContext>& transitionOutNodeContext)
{
    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDelay(OPACITY_TITLE_OUT_DELAY);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    opacityOption.SetFillMode(FillMode::FORWARDS);
    opacityOption.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakClaim(RawPtr(transitionOutNodeContext)), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, id]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    CHECK_NULL_VOID(transitionOutNodeContext);
                    ContainerScope scope(id);
                    transitionOutNodeContext->UpdateOpacity(1.0);
                },
                TaskExecutor::TaskType::UI);
        });
    transitionOutNodeContext->OpacityAnimation(opacityOption, 1.0, 0.0);
}

void NavRouterGroupNode::BackButtonAnimation(const RefPtr<FrameNode>& backButtonNode, bool isTransitionIn)
{
    AnimationOption transitionOption;
    transitionOption.SetCurve(Curves::SHARP);
    transitionOption.SetFillMode(FillMode::FORWARDS);
    auto backButtonNodeContext = backButtonNode->GetRenderContext();
    CHECK_NULL_VOID(backButtonNodeContext);
    if (isTransitionIn) {
        transitionOption.SetDelay(OPACITY_BACKBUTTON_IN_DELAY);
        transitionOption.SetDuration(OPACITY_BACKBUTTON_IN_DURATION);
        backButtonNodeContext->OpacityAnimation(transitionOption, 0.0, 1.0);
    } else {
        transitionOption.SetDuration(OPACITY_BACKBUTTON_OUT_DURATION);
        transitionOption.SetOnFinishEvent(
            [backButtonNodeContextWK = WeakClaim(RawPtr(backButtonNodeContext)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID_NOLOG(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID_NOLOG(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [backButtonNodeContextWK, id]() {
                        auto backButtonNodeContext = backButtonNodeContextWK.Upgrade();
                        CHECK_NULL_VOID(backButtonNodeContext);
                        ContainerScope scope(id);
                        backButtonNodeContext->UpdateOpacity(1.0);
                    },
                    TaskExecutor::TaskType::UI);
            });
        backButtonNodeContext->OpacityAnimation(transitionOption, 1.0, 0.0);
    }
}

} // namespace OHOS::Ace::NG
