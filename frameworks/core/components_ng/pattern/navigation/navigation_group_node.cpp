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
#include "base/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
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
#include "core/components_ng/render/render_context.h"
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

void NavigationGroupNode::UpdateNavDestinationNodeWithoutMarkDirty(const RefPtr<UINode>& remainChild)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    const auto& navDestinationNodes = pattern->GetAllNavDestinationNodes();

    auto navigationContentNode = AceType::DynamicCast<FrameNode>(GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    bool hasChanged = false;
    int32_t slot = 0;
    for (size_t i = 0; i != navDestinationNodes.size(); ++i) {
        const auto& childNode = navDestinationNodes[i];
        const auto& uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        CHECK_NULL_VOID(navDestination);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        navDestinationPattern->SetName(childNode.first);
        navDestinationPattern->SetNavDestinationNode(uiNode);
        SetBackButtonVisible(navDestination);
        SetBackButtonEvent(navDestination);
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        if (i == navDestinationNodes.size() - 1) {
            // process shallow builder
            navDestination->ProcessShallowBuilder();
            navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            navDestination->GetEventHub<EventHub>()->SetEnabledInternal(true);
            // for the navDestination at the top, FireChangeEvent
            eventHub->FireChangeEvent(true);
            hasChanged = CheckNeedMeasure(navDestination->GetLayoutProperty()->GetPropertyChangeFlag());
        } else {
            eventHub->FireChangeEvent(false);
        }
        int32_t childIndex = navigationContentNode->GetChildIndex(navDestination);
        if (childIndex < 0) {
            navigationContentNode->AddChild(navDestination, slot);
            hasChanged = true;
        } else if (childIndex != slot) {
            navDestination->MovePosition(slot);
            hasChanged = true;
        }
        slot++;
    }

    while (static_cast<size_t>(slot) < navigationContentNode->GetChildren().size()) {
        // delete useless nodes that are not at the top
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContentNode->GetLastChild());
        if (!navDestination) {
            navigationContentNode->RemoveChild(navigationContentNode->GetLastChild());
            hasChanged = true;
            continue;
        }
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        if (eventHub) {
            eventHub->FireChangeEvent(false);
        }
        auto uiNode = navDestination->GetPattern<NavDestinationPattern>()->GetNavDestinationNode();
        if (uiNode != remainChild) {
            // remove content child
            auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            if (shallowBuilder) {
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            }
            navDestination->GetContentNode()->Clean();
            navigationContentNode->RemoveChild(navDestination, true);
            hasChanged = true;
        } else {
            // remain the last child for pop animation
            navDestination->MovePosition(slot);
            ++slot;
        }
    }
    if (hasChanged) {
        navigationContentNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
}

void NavigationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    FrameNode::ToJsonValue(json);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
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
        if (uiNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            // this is a navDestination node
            return uiNode;
        }
        if (AceType::DynamicCast<UINode>(uiNode)) {
            // this is an UINode, go deep further for navDestination node
            auto children = uiNode->GetChildren();
            uiNode = children.front();
            continue;
        }
    }
    return nullptr;
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

void NavigationGroupNode::SetBackButtonVisible(const RefPtr<UINode>& navDestinationNode, bool isVisible)
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
    if (isVisible) {
        backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
    }
    backButtonNode->MarkModifyDone();
    navDestination->UpdateTitleFontSize(isVisible);
}

void NavigationGroupNode::SetBackButtonEvent(
    const RefPtr<NavDestinationGroupNode>& navDestination, const RefPtr<NavRouterPattern>& navRouterPattern)
{
    AddBackButtonIconToNavDestination(navDestination);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent =
        [navDestinationWeak = WeakPtr<NavDestinationGroupNode>(navDestination), navigationWeak = WeakClaim(this),
            navRouterPatternWeak = WeakPtr<NavRouterPattern>(navRouterPattern)](GestureEvent& /*info*/) {
            // the one before navDestination in the stack
            auto navDestination = navDestinationWeak.Upgrade();
            CHECK_NULL_VOID(navDestination);
            auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            auto onBackPressed = eventHub->GetOnBackPressedEvent();
            bool isOverride = false;
            if (onBackPressed != nullptr) {
                isOverride = eventHub->FireOnBackPressedEvent();
            }
            if (isOverride) {
                LOGI("this onBackButtonPressed event returns false");
                return;
            }
            auto navigation = navigationWeak.Upgrade();
            CHECK_NULL_VOID(navigation);
            if (navigation->isOnAnimation_) {
                LOGI("animation is ongoing");
                return;
            }
            auto navigationPattern = navigation->GetPattern<NavigationPattern>();
            CHECK_NULL_VOID(navigationPattern);
            auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            auto preNavDestinationNode =
                navigationPattern->GetPreNavDestination(navDestinationPattern->GetName(), navDestination);
            auto preNavDestination =
                AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(preNavDestinationNode));

            navigationPattern->RemoveNavDestination();
            // when js navigationStack is provided, modifyDone will be called by state manager.
            if (!navigationPattern->GetNavigationStackProvided()) {
                navigation->MarkModifyDone();
                navigation->MarkDirtyNode();
            }
        }; // backButton event

    navDestination->SetNavDestinationBackButtonEvent(onBackButtonEvent);
    backButtonEventHub->GetOrCreateGestureEventHub()->SetUserOnClick(onBackButtonEvent);
}

RefPtr<FrameNode> NavigationGroupNode::GetNavDestinationNodeToHandleBack()
{
    auto pattern = GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    const auto& children = contentNode_->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    auto mode = pattern->GetNavigationMode();
    if (mode == NavigationMode::SPLIT) {
        if (children.size() == 1) {
            return nullptr;
        }
        return AceType::DynamicCast<NavDestinationGroupNode>(children.back());
    }
    return AceType::DynamicCast<NavDestinationGroupNode>(children.back());
}

void NavigationGroupNode::ExitTransitionWithPop(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto size = GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();

    RefPtr<TitleBarNode> titleNode;
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
    CHECK_NULL_VOID(navDestination);
    navDestination->SetTransitionType(PageTransitionType::EXIT_POP);
    titleNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleNode);

    option.SetOnFinishEvent(
        [weakNode = WeakPtr<NavDestinationGroupNode>(navDestination), weakTitle = WeakPtr<TitleBarNode>(titleNode),
            weakNavigation = WeakClaim(this), id = Container::CurrentId(), nodeWidth, nodeHeight] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            // animation finish event should be posted to UI thread
            taskExecutor->PostTask(
                [weakNode, weakTitle, weakNavigation, nodeWidth, nodeHeight]() {
                    LOGI("navigation animation end");
                    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                    auto navigation = weakNavigation.Upgrade();
                    if (navigation) {
                        navigation->isOnAnimation_ = false;
                    }
                    auto node = weakNode.Upgrade();
                    CHECK_NULL_VOID(node);
                    if (node->GetTransitionType() != PageTransitionType::EXIT_POP) {
                        // has another transition, just return
                        return;
                    }
                    auto title = weakTitle.Upgrade();
                    if (title) {
                        title->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                    }
                    node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                    node->GetRenderContext()->ClipWithRRect(
                        RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
                    auto navDestinationPattern = node->GetPattern<NavDestinationPattern>();
                    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
                    if (shallowBuilder) {
                        shallowBuilder->MarkIsExecuteDeepRenderDone(false);
                    }
                    node->GetContentNode()->Clean();
                    auto parent = node->GetParent();
                    CHECK_NULL_VOID(parent);
                    parent->RemoveChild(node);
                    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                    auto context = PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(context);
                    context->MarkNeedFlushMouseEvent();
                },
                TaskExecutor::TaskType::UI);
        });

    // content
    node->GetEventHub<EventHub>()->SetEnabledInternal(false);
    node->GetRenderContext()->ClipWithRRect(RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
    node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    // title
    titleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    AnimationUtils::Animate(
        option,
        [node, titleNode, nodeWidth, nodeHeight]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
            // content
            node->GetRenderContext()->ClipWithRRect(
                RectF(nodeWidth * HALF, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
            node->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * HALF, 0.0f });
            // title
            titleNode->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * HALF, 0.0f });
        },
        option.GetOnFinishEvent());
    TitleOpacityAnimationOut(titleNode->GetRenderContext());

    // backIcon opacity
    auto backIcon = AceType::DynamicCast<FrameNode>(titleNode->GetBackButton());
    if (backIcon) {
        BackButtonAnimation(backIcon, false);
    }

    isOnAnimation_ = true;
}

void NavigationGroupNode::ExitTransitionWithPush(const RefPtr<FrameNode>& node, bool isNavBar)
{
    CHECK_NULL_VOID(node);
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto size = GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();

    RefPtr<FrameNode> titleNode;
    if (isNavBar) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(node);
        navBarNode->SetTransitionType(PageTransitionType::EXIT_PUSH);
        titleNode = navBarNode ? AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode()) : nullptr;
    } else {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
        navDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
        titleNode = navDestination ? AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode()) : nullptr;
    }
    CHECK_NULL_VOID(titleNode);

    option.SetOnFinishEvent([weakNode = WeakPtr<FrameNode>(node), weakTitle = WeakPtr<FrameNode>(titleNode),
                                weakNavigation = WeakClaim(this), isNavBar, id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        // animation finish event should be posted to UI thread
        taskExecutor->PostTask(
            [weakNode, weakTitle, weakNavigation, isNavBar]() {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                LOGI("navigation animation end");
                auto navigation = weakNavigation.Upgrade();
                if (navigation) {
                    navigation->isOnAnimation_ = false;
                }
                auto title = weakTitle.Upgrade();
                if (title) {
                    title->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                }
                auto node = weakNode.Upgrade();
                CHECK_NULL_VOID(node);
                bool needSetInVisible = false;
                if (isNavBar) {
                    needSetInVisible =
                        AceType::DynamicCast<NavBarNode>(node)->GetTransitionType() == PageTransitionType::EXIT_PUSH;
                } else {
                    needSetInVisible = AceType::DynamicCast<NavDestinationGroupNode>(node)->GetTransitionType() ==
                                       PageTransitionType::EXIT_PUSH;
                }
                // for the case, the navBar form EXIT_PUSH to push  during animation
                if (needSetInVisible) {
                    node->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                }
                node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
            },
            TaskExecutor::TaskType::UI);
    });
    node->GetEventHub<EventHub>()->SetEnabledInternal(false);
    node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    titleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });

    AnimationUtils::Animate(
        option,
        [node, titleNode, nodeWidth]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
            node->GetRenderContext()->UpdateTranslateInXY({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f });
            titleNode->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * PARENT_TITLE_OFFSET, 0.0f });
        },
        option.GetOnFinishEvent());
    MaskAnimation(node->GetRenderContext());
    isOnAnimation_ = true;
}

void NavigationGroupNode::EnterTransitionWithPush(const RefPtr<FrameNode>& node, bool isNavBar)
{
    CHECK_NULL_VOID(node);
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto size = GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();
    auto nodeHeight = size.Height();

    RefPtr<TitleBarNode> titleNode;
    if (isNavBar) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(node);
        navBarNode->SetTransitionType(PageTransitionType::ENTER_PUSH);
        titleNode = navBarNode ? AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode()) : nullptr;
    } else {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
        navDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
        titleNode = navDestination ? AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode()) : nullptr;
    }
    CHECK_NULL_VOID(titleNode);

    option.SetOnFinishEvent([weakNavigation = WeakClaim(this), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        // animation finish event should be posted to UI thread.
        taskExecutor->PostTask(
            [weakNavigation]() {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                LOGI("navigation animation end");
                auto navigation = weakNavigation.Upgrade();
                CHECK_NULL_VOID(navigation);
                navigation->isOnAnimation_ = false;
            },
            TaskExecutor::TaskType::UI);
    });

    // content
    node->GetRenderContext()->ClipWithRRect(
        RectF(nodeWidth * HALF, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
    node->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * HALF, 0.0f });
    // title
    titleNode->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * HALF, 0.0f });
    AnimationUtils::Animate(
        option,
        [node, titleNode, nodeWidth, nodeHeight]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
            // content
            node->GetRenderContext()->ClipWithRRect(
                RectF(0.0f, 0.0f, nodeWidth, nodeHeight), RadiusF(EdgeF(0.0f, 0.0f)));
            node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
            // title
            titleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());
    // title opacity
    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDelay(OPACITY_TITLE_IN_DELAY);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    opacityOption.SetFillMode(FillMode::FORWARDS);
    titleNode->GetRenderContext()->OpacityAnimation(opacityOption, 0.0f, 1.0f);

    // backIcon opacity
    auto backIcon = AceType::DynamicCast<FrameNode>(titleNode->GetBackButton());
    if (backIcon) {
        BackButtonAnimation(backIcon, true);
    }

    isOnAnimation_ = true;
}

void NavigationGroupNode::EnterTransitionWithPop(const RefPtr<FrameNode>& node, bool isNavBar)
{
    CHECK_NULL_VOID(node);
    AnimationOption option;
    option.SetCurve(interpolatingSpringCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    auto size = GetGeometryNode()->GetFrameSize();
    auto nodeWidth = size.Width();

    RefPtr<TitleBarNode> titleNode;
    if (isNavBar) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(node);
        navBarNode->SetTransitionType(PageTransitionType::ENTER_POP);
        titleNode = navBarNode ? AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode()) : nullptr;
    } else {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
        navDestination->SetTransitionType(PageTransitionType::ENTER_POP);
        titleNode = navDestination ? AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode()) : nullptr;
    }
    CHECK_NULL_VOID(titleNode);

    option.SetOnFinishEvent([weakNavigation = WeakClaim(this), id = Container::CurrentId()] {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        // animation finish event should be posted to UI thread.
        taskExecutor->PostTask(
            [weakNavigation]() {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
                LOGI("navigation animation end");
                auto navigation = weakNavigation.Upgrade();
                CHECK_NULL_VOID(navigation);
                navigation->isOnAnimation_ = false;
            },
            TaskExecutor::TaskType::UI);
    });

    // content
    node->GetRenderContext()->UpdateTranslateInXY({ -nodeWidth * PARENT_PAGE_OFFSET, 0.0f });
    // title
    titleNode->GetRenderContext()->UpdateTranslateInXY({ nodeWidth * PARENT_TITLE_OFFSET, 0.0f });
    AnimationUtils::Animate(
        option,
        [node, titleNode]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            LOGI("navigation animation start");
            node->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
            titleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());

    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    maskOption.SetFillMode(FillMode::FORWARDS);
    node->GetRenderContext()->SetActualForegroundColor(MASK_COLOR);
    AnimationUtils::Animate(
        maskOption, [node]() { node->GetRenderContext()->SetActualForegroundColor(DEFAULT_MASK_COLOR); });
    isOnAnimation_ = true;
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
                        CHECK_NULL_VOID_NOLOG(backButtonNodeContext);
                        ContainerScope scope(id);
                        backButtonNodeContext->UpdateOpacity(1.0);
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
        [transitionOutNodeContextWK = WeakPtr<RenderContext>(transitionOutNodeContext), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID_NOLOG(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID_NOLOG(taskExecutor);
            taskExecutor->PostTask(
                [transitionOutNodeContextWK]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
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

void NavigationGroupNode::TitleOpacityAnimationOut(const RefPtr<RenderContext>& transitionOutNodeContext)
{
    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDelay(OPACITY_TITLE_OUT_DELAY);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    opacityOption.SetFillMode(FillMode::FORWARDS);
    opacityOption.SetOnFinishEvent(
        [transitionOutNodeContextWK = WeakPtr<RenderContext>(transitionOutNodeContext), id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            // animation finish event should be posted to UI thread.
            taskExecutor->PostTask(
                [transitionOutNodeContextWK, id]() {
                    auto transitionOutNodeContext = transitionOutNodeContextWK.Upgrade();
                    CHECK_NULL_VOID_NOLOG(transitionOutNodeContext);
                    transitionOutNodeContext->UpdateOpacity(1.0);
                },
                TaskExecutor::TaskType::UI);
        });
    transitionOutNodeContext->OpacityAnimation(opacityOption, 1.0, 0.0);
    transitionOutNodeContext->UpdateOpacity(0.0);
}
} // namespace OHOS::Ace::NG
