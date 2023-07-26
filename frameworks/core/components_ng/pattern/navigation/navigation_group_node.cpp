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

#include "core/components_ng/pattern/navigation/navigation_group_node.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/common/container.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
    AceType::MakeRefPtr<InterpolatingSpring>(18.0f, 1.0f, 324.0f, 36.0f);
} // namespace
RefPtr<NavigationGroupNode> NavigationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN_NOLOG(!frameNode, AceType::DynamicCast<NavigationGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(tag, nodeId, pattern);
    navigationGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navigationGroupNode);
    return navigationGroupNode;
}

void NavigationGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto navBar = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBar);
    auto contentNode = navBar->GetNavBarContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(
            V2::NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navBar->SetNavBarContentNode(contentNode);
        auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        navBar->AddChild(contentNode);
    }
    contentNode->AddChild(child);
}

void NavigationGroupNode::AddNavDestinationToNavigation()
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto navDestinationNodes = pattern->GetAllNavDestinationNodes();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
    // let navBarNode lose focus
    if (navDestinationNodes.size() == 1 && navBarNode) {
        auto navBarContentNode = navBarNode->GetNavBarContentNode();
        CHECK_NULL_VOID(navBarContentNode);
        auto focusHub = AceType::DynamicCast<FrameNode>(navBarContentNode)->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetParentFocusable(false);
        focusHub->LostFocus();
    }
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    CHECK_NULL_VOID(navigationNode);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    auto navigationStack = pattern->GetNavigationStack();
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    for (auto iter = navDestinationNodes.begin(); iter != navDestinationNodes.end(); ++iter) {
        const auto& childNode = *iter;
        auto uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        CHECK_NULL_VOID(navDestination);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        navDestinationPattern->SetName(childNode.first);
        navDestinationPattern->SetNavDestinationNode(uiNode);
        auto navDestinationContext = AceType::DynamicCast<FrameNode>(navDestination)->GetRenderContext();
        CHECK_NULL_VOID(navDestinationContext);
        if (!(navDestinationContext->GetBackgroundColor().has_value())) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto theme = pipelineContext->GetTheme<AppTheme>();
            navDestinationContext->UpdateBackgroundColor(theme->GetBackgroundColor());
        }
        if (!(navigationContentNode->GetChildren().empty() &&
                navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT)) {
            // add backButton except for the first level page in SPLIT mode
            SetBackButtonVisible(navDestination);
            if (!(navDestination->GetNavDestinationBackButtonEvent())) {
                SetBackButtonEvent(navDestination);
            }
        }
        navigationContentNode->AddChild(navDestination);
    }
}

void NavigationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    FrameNode::ToJsonValue(json);
    auto navBarNode = DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->ToJsonValue(json);
}

RefPtr<UINode> NavigationGroupNode::GetNavDestinationNode(RefPtr<UINode> uiNode)
{
    if (!uiNode) {
        return nullptr;
    }
    // create NavDestinationNode from uiNode stored in NavigationStack
    while (uiNode) {
        if (AceType::DynamicCast<FrameNode>(uiNode) && uiNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            // this is a navDesination node
            return AceType::DynamicCast<NavDestinationGroupNode>(uiNode);
        }
        if (AceType::DynamicCast<UINode>(uiNode)) {
            // this is an UINode, go deep further for navDestination node
            auto children = uiNode->GetChildren();
            uiNode = children.front();
            continue;
        }
    }
    // this is an invalid node, just display blank content
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto stackLayoutProperty = frameNode->GetLayoutProperty();
    stackLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    uiNode = AceType::DynamicCast<UINode>(frameNode);
    return uiNode;
}

void NavigationGroupNode::AddBackButtonIconToNavDestination(const RefPtr<UINode>& navDestinationNode)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
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

void NavigationGroupNode::SetBackButtonVisible(const RefPtr<UINode>& navDestinationNode)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
    CHECK_NULL_VOID(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
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

void NavigationGroupNode::SetBackButtonEvent(
    const RefPtr<UINode>& navDestinationNode, const RefPtr<NavRouterPattern>& navRouterPattern)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    CHECK_NULL_VOID(navigationNode);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
    AddBackButtonIconToNavDestination(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent = [navDestination, navigation = navigationNode, navRouterPattern](GestureEvent& /*info*/) {
        // the one before navdestination in the stack
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto onBackPressed = eventHub->GetOnBackPressedEvent();
        bool isOverride = false;
        if (onBackPressed != nullptr) {
            isOverride = eventHub->FireOnBackPressedEvent();
        }
        auto destinationContent = navDestination->GetContentNode();
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        NavRouteMode mode = NavRouteMode::PUSH;
        if (navRouterPattern) {
            mode = navRouterPattern->GetNavRouteMode();
        }
        if (destinationContent) {
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            CHECK_NULL_VOID(shallowBuilder);
            shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            destinationContent->Clean();
        }
        if (isOverride) {
            LOGI("this onBackButtonPressed event returns false");
            return;
        }
        auto layoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto navigationPattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        auto navDestinationNode = navDestinationPattern->GetNavDestinationNode();
        auto preNavDestinationNode =
            navigationPattern->GetPreNavDestination(navDestinationPattern->GetName(), navDestinationNode);
        auto preNavDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(preNavDestinationNode));
        if (navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
            if (preNavDestination) {
                navigation->BackToPreNavDestination(preNavDestinationNode, navDestination, navRouterPattern);
                navigation->SetOnStateChangeFalse(preNavDestination, navDestination, true);
                layoutProperty->UpdateDestinationChange(true);
                return;
            }
            navigation->BackToNavBar(navDestination);
            navigation->SetOnStateChangeFalse(navDestination, navDestination, true);
            layoutProperty->UpdateDestinationChange(false);
            return;
        }

        if (navigationPattern->GetNavigationMode() == NavigationMode::SPLIT) {
            if (preNavDestination) {
                navigation->BackToPreNavDestination(preNavDestinationNode, navDestination, navRouterPattern);
                navigation->SetOnStateChangeFalse(preNavDestination, navDestination, true);
                layoutProperty->UpdateDestinationChange(false);
                navigation->MarkModifyDone();
                return;
            }
        }
    }; // backButton event

    navDestination->SetNavDestinationBackButtonEvent(onBackButtonEvent);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(onBackButtonEvent));
    if (!backButtonEventHub->GetGestureEventHub()) {
        return;
    }
    backButtonEventHub->GetOrCreateGestureEventHub()->AddClickEvent(clickEvent);
}

void NavigationGroupNode::BackToNavBar(const RefPtr<UINode>& navDestinationNode)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
    auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
    if (titleBarNode || destinationTitleBarNode) {
        TitleTransitionOutAnimation(titleBarNode, destinationTitleBarNode);
    }
    if (backButtonNode) {
        BackButtonAnimation(backButtonNode, false);
    }
    // let navBarNode request focus
    auto navBarContentNode = navBarNode->GetNavBarContentNode();
    CHECK_NULL_VOID(navBarContentNode);
    auto focusHub = AceType::DynamicCast<FrameNode>(navBarContentNode)->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetParentFocusable(true);
    focusHub->RequestFocus();

    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    NavTransitionOutAnimation(navBarNode, navDestination, navigationContentNode);
}

void NavigationGroupNode::BackToPreNavDestination(const RefPtr<UINode>& preNavDestinationNode,
    const RefPtr<UINode>& navDestinationNode, const RefPtr<NavRouterPattern>& navRouterPattern)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    if (navigationNode->GetIsOnAnimation()) {
        LOGI("navigation is on animation");
        return;
    }
    auto preNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(preNavDestinationNode));
    CHECK_NULL_VOID(preNavDestination);
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);

    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    if (navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::STACK) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
        CHECK_NULL_VOID(navDestination);
        auto preDestinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(preNavDestination->GetTitleBarNode());
        auto destinationTitleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
        if (preDestinationTitleBarNode || destinationTitleBarNode) {
            TitleTransitionOutAnimation(preDestinationTitleBarNode, destinationTitleBarNode);
        }
        auto backButtonNode = AceType::DynamicCast<FrameNode>(destinationTitleBarNode->GetBackButton());
        if (backButtonNode) {
            BackButtonAnimation(backButtonNode, false);
        }
        NavTransitionBackToPreAnimation(preNavDestination, navDestination, navigationContentNode);
    }
    navigationContentNode->AddChild(preNavDestination);
    if (navigationLayoutProperty->GetNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT) {
        navigationContentNode->MarkModifyDone();
        navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navDestinationPattern = preNavDestination->GetPattern<NavDestinationPattern>();
    auto navRouteMode = NavRouteMode::REPLACE;
    RefPtr<RouteInfo> routeInfo;
    if (navRouterPattern) {
        routeInfo = navDestinationPattern->GetRouteInfo();
    }
    auto name = navDestinationPattern->GetName();
    if (routeInfo) {
        navigationPattern->AddNavDestinationNode(name, preNavDestinationNode, navRouteMode, routeInfo);
    } else {
        navigationPattern->AddNavDestinationNode(name, preNavDestinationNode, navRouteMode);
    }
}

void NavigationGroupNode::NavTransitionInAnimation(
    const RefPtr<FrameNode>& transitionOutNode, const RefPtr<FrameNode>& navDestination)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
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
                    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                    LOGI("navigation animation end");
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
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
            transitionOutNodeContext->OnTransformTranslateUpdate({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f, 0.0f });
            transitionInNodeContext->ClipWithRRect(
                RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
            transitionInNodeContext->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());
    MaskAnimation(transitionOutNodeContext);
}

void NavigationGroupNode::NavTransitionOutAnimation(const RefPtr<FrameNode>& navBarNode,
    const RefPtr<FrameNode>& navDestination, const RefPtr<FrameNode>& navigationContentNode)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
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
    auto navDestinationContext = navDestination->GetRenderContext();
    CHECK_NULL_VOID(navDestinationContext);

    auto node = AceType::DynamicCast<FrameNode>(navigationNode);
    auto size = node->GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();

    auto navigationPattern = AceType::DynamicCast<NavigationGroupNode>(navigationNode)->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    option.SetOnFinishEvent(
        [navigationContentWK = WeakClaim(RawPtr(navigationContentNode)),
            navDestinationWK = WeakClaim(RawPtr(navDestination)),
            navigationPatternWK = WeakClaim(RawPtr(navigationPattern)),
            navigationNodeWK = WeakClaim(RawPtr(navigationNode)), id = Container::CurrentId(), nodeHeight] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [navigationContentWK, navDestinationWK, navigationPatternWK, navigationNodeWK, id, nodeHeight]() {
                    auto navigationContentNode = navigationContentWK.Upgrade();
                    auto navDestination = navDestinationWK.Upgrade();
                    auto navigationNode = navigationNodeWK.Upgrade();
                    auto navigationPattern = navigationPatternWK.Upgrade();
                    CHECK_NULL_VOID(navigationNode && navigationContentNode);
                    navDestination->GetRenderContext()->OnTransformTranslateUpdate({ 0.0f, 0.0f, 0.0f });
                    navDestination->GetRenderContext()->ClipWithRRect(
                        RectF(0.0f, 0.0f, Infinity<float>(), nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                    ContainerScope scope(id);
                    navigationPattern->RemoveNavDestination();
                    navigationContentNode->MarkModifyDone();
                    navigationNode->MarkModifyDone();
                    navigationContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                    navigationNode->SetIsOnAnimation(false);
                    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                    LOGI("navigation animation end");
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
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
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

void NavigationGroupNode::NavTransitionBackToPreAnimation(const RefPtr<FrameNode>& preDestination,
    const RefPtr<FrameNode>& curNavDestination, const RefPtr<FrameNode>& navigationContentNode)
{
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
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
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                LOGI("navigation animation end");
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
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
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
    preDestinationContext->SetActualForegroundColor(MASK_COLOR);
    AnimationUtils::Animate(
        maskOption, [preDestinationContext]() { preDestinationContext->SetActualForegroundColor(DEFAULT_MASK_COLOR); });
}

void NavigationGroupNode::TitleTransitionInAnimation(
    const RefPtr<FrameNode>& titleBarNode, const RefPtr<FrameNode>& destinationTitleBarNode)
{
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    auto transitionOutNodeContext = titleBarNode->GetRenderContext();
    auto transitionInNodeContext = destinationTitleBarNode->GetRenderContext();
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
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

void NavigationGroupNode::TitleTransitionOutAnimation(
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
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
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

void NavigationGroupNode::BackButtonAnimation(const RefPtr<FrameNode>& backButtonNode, bool isTransitionIn)
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
            [backButtonNodeWK = WeakClaim(RawPtr(backButtonNode)),
                backButtonNodeContextWK = WeakClaim(RawPtr(backButtonNodeContext)), id = Container::CurrentId()] {
                ContainerScope scope(id);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID_NOLOG(context);
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_VOID_NOLOG(taskExecutor);
                // animation finish event should be posted to UI thread.
                taskExecutor->PostTask(
                    [backButtonNodeWK, backButtonNodeContextWK, id]() {
                        auto backButtonNodeContext = backButtonNodeContextWK.Upgrade();
                        auto backButtonNode = backButtonNodeWK.Upgrade();
                        CHECK_NULL_VOID(backButtonNodeContext);
                        ContainerScope scope(id);
                        backButtonNodeContext->UpdateOpacity(1.0);
                        auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
                        CHECK_NULL_VOID(backButtonLayoutProperty);
                        backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
                    },
                    TaskExecutor::TaskType::UI);
            });
        backButtonNodeContext->OpacityAnimation(transitionOption, 1.0, 0.0);
    }
}

void NavigationGroupNode::MaskAnimation(const RefPtr<RenderContext>& transitionOutNodeContext)
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
    transitionOutNodeContext->SetActualForegroundColor(DEFAULT_MASK_COLOR);
    AnimationUtils::Animate(
        maskOption, [transitionOutNodeContext]() { transitionOutNodeContext->SetActualForegroundColor(MASK_COLOR); },
        maskOption.GetOnFinishEvent());
}

void NavigationGroupNode::TitleOpacityAnimation(const RefPtr<RenderContext>& transitionOutNodeContext)
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

void NavigationGroupNode::SetOnStateChangeFalse(
    const RefPtr<UINode>& preNavDestinationNode, const RefPtr<UINode>& navDestinationNode, bool isBackButton)
{
    auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNavDestinationNode);
    CHECK_NULL_VOID(preNavDestination);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationNode);
    CHECK_NULL_VOID(navDestination);
    if (!isBackButton && navDestination == preNavDestination) {
        return;
    }
    auto navigationNode = AceType::WeakClaim(this).Upgrade();
    CHECK_NULL_VOID(navigationNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navBarContentNode = navBarNode->GetNavBarContentNode();
    CHECK_NULL_VOID(navBarContentNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);

    auto navDestinationPattern = preNavDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    if (isBackButton && preNavDestination) {
        auto eventHub = preNavDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireChangeEvent(true);
    }

    auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireChangeEvent(false);
}
} // namespace OHOS::Ace::NG
