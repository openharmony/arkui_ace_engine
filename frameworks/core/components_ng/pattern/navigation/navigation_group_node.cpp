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
#include "core/components_ng/pattern/button/button_layout_property.h"
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
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF = 0.5;
constexpr double PARENT_PAGE_OFFSET = 0.2;
constexpr double PARENT_TITLE_OFFSET = 0.02;
constexpr float REMOVE_CLIP_SIZE = 10000.0f;
constexpr int32_t MASK_DURATION = 350;
constexpr int32_t OPACITY_TITLE_OUT_DELAY = 17;
constexpr int32_t OPACITY_TITLE_IN_DELAY = 33;
constexpr int32_t OPACITY_TITLE_DURATION = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DELAY = 150;
constexpr int32_t OPACITY_BACKBUTTON_IN_DURATION = 200;
constexpr int32_t OPACITY_BACKBUTTON_OUT_DURATION = 67;
constexpr int32_t DEFAULT_ANIMATION_DURATION = 450;
constexpr int32_t DEFAULT_REPLACE_DURATION = 150;
const RefPtr<InterpolatingSpring> springCurve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<CubicCurve> replaceCurve = AceType::MakeRefPtr<CubicCurve>(0.33, 0.0, 0.67, 1.0);
} // namespace
RefPtr<NavigationGroupNode> NavigationGroupNode::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<NavigationGroupNode>(frameNode));
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    auto navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(tag, nodeId, pattern);
    navigationGroupNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(navigationGroupNode);
    return navigationGroupNode;
}

NavigationGroupNode::~NavigationGroupNode()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(pagePattern->GetPageInfo());
    int32_t pageId = pagePattern->GetPageInfo()->GetPageId();
    context->RemoveNavigationStateCallback(pageId, GetId());
    context->DeleteNavigationNode(curId_);
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
        navBar->AddChild(contentNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            auto navBarContentNode = AceType::DynamicCast<FrameNode>(contentNode);
            SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM};
            navBarContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
        }
    }
    contentNode->AddChild(child);
}

void NavigationGroupNode::UpdateNavDestinationNodeWithoutMarkDirty(const RefPtr<UINode>& remainChild, bool modeChange)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    const auto& navDestinationNodes = pattern->GetAllNavDestinationNodes();

    auto navigationContentNode = AceType::DynamicCast<FrameNode>(GetContentNode());
    CHECK_NULL_VOID(navigationContentNode);
    bool hasChanged = false;
    int32_t slot = 0;
    UpdateLastStandardIndex();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "last standard page index is %{public}d", lastStandardIndex_);
    for (uint32_t i = 0; i != navDestinationNodes.size(); ++i) {
        const auto& childNode = navDestinationNodes[i];
        const auto& uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        if (navDestination == nullptr) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get destination node failed");
            return;
        }
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        navDestinationPattern->SetName(childNode.first);
        navDestinationPattern->SetNavDestinationNode(uiNode);
        SetBackButtonEvent(navDestination);
        navDestination->SetIndex(i);
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        if (!eventHub->GetOnStateChange()) {
            auto onStateChangeMap = pattern->GetOnStateChangeMap();
            auto iter = onStateChangeMap.find(uiNode->GetId());
            if (iter != onStateChangeMap.end()) {
                eventHub->SetOnStateChange(iter->second);
                pattern->DeleteOnStateChangeItem(iter->first);
            }
        }
        hasChanged =
            UpdateNavDestinationVisibility(navDestination, remainChild, i, navDestinationNodes.size());
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
            if (navDestination->IsOnAnimation()) {
                // The NavDestination in the animation needs to be cleaned in the animation onfinish callback.
                ++slot;
                continue;
            }
            // remove content child
            auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "remove child: %{public}s", navDestinationPattern->GetName().c_str());
            if (navDestinationPattern->GetIsOnShow()) {
                eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
                navDestinationPattern->SetIsOnShow(false);
                NavigationPattern::FireNavigationStateChange(navDestination, false);
            }
            auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
            if (shallowBuilder) {
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            }
            if (navDestination->GetContentNode()) {
                navDestination->GetContentNode()->Clean();
            }
            navigationContentNode->RemoveChild(navDestination, true);
            hasChanged = true;
        } else {
            // remain the last child for pop animation
            navDestination->MovePosition(slot);
            ++slot;
        }
    }
    if (modeChange) {
        navigationContentNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } else if (hasChanged) {
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
    CHECK_NULL_RETURN(uiNode, nullptr);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get navDestination node failed: id: %{public}d, %{public}s",
        uiNode->GetId(), uiNode->GetTag().c_str());
    return nullptr;
}

void NavigationGroupNode::SetBackButtonEvent(const RefPtr<NavDestinationGroupNode>& navDestination)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent = [navDestinationWeak = WeakPtr<NavDestinationGroupNode>(navDestination),
                                 navigationWeak = WeakClaim(this)](GestureEvent& /*info*/) -> bool {
        auto navDestination = navDestinationWeak.Upgrade();
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "click navigation back button");
        CHECK_NULL_RETURN(navDestination, false);
        auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        auto isOverride = eventHub->GetOnBackPressedEvent();
        auto result = false;
        if (isOverride) {
            result = eventHub->FireOnBackPressedEvent();
        }
        if (result) {
            return true;
        }
        auto navigation = navigationWeak.Upgrade();
        CHECK_NULL_RETURN(navigation, false);
        // if set hideNavBar and stack size is one, return false
        auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(navigation->GetLayoutProperty());
        auto pattern = AceType::DynamicCast<NavigationPattern>(navigation->GetPattern());
        auto stack = pattern->GetNavigationStack();
        CHECK_NULL_RETURN(stack, false);
        if (navigationLayoutProperty->GetHideNavBarValue(false) && stack->Size() <= 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "set hideNavBar and stack size is no more than one");
            return false;
        }
        const auto& children = navigation->GetContentNode()->GetChildren();
        auto isLastChild = children.size() == 1;
        if (isOverride) {
            result = navigation->HandleBack(navDestination, isLastChild, true);
        } else {
            result = navigation->HandleBack(navDestination, isLastChild, false);
        }
        // when js navigationStack is provided, modifyDone will be called by state manager.
        auto navigationPattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_RETURN(navigationPattern, false);
        if (!navigationPattern->GetNavigationStackProvided()) {
            navigation->MarkModifyDone();
            navigation->MarkDirtyNode();
        }

        return result;
    }; // backButton event

    navDestination->SetNavDestinationBackButtonEvent(onBackButtonEvent);
    backButtonEventHub->GetOrCreateGestureEventHub()->SetUserOnClick(onBackButtonEvent);
}

bool NavigationGroupNode::CheckCanHandleBack()
{
    auto navigation = AceType::WeakClaim(this).Upgrade();
    CHECK_NULL_RETURN(navigation, false);
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, false);

    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_RETURN(navigationStack, false);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navigationStack->Get()));
    if (!navDestination) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't find destination node to process back press");
        return false;
    }
    auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination consume back button event: %{public}s",
        navDestinationPattern->GetName().c_str());
    GestureEvent gestureEvent;
    return navDestination->GetNavDestinationBackButtonEvent()(gestureEvent);
}

bool NavigationGroupNode::HandleBack(const RefPtr<FrameNode>& node, bool isLastChild, bool isOverride)
{
    auto navigationPattern = GetPattern<NavigationPattern>();
    if (!isOverride && !isLastChild) {
        navigationPattern->RemoveNavDestination();
        return true;
    }
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
    CHECK_NULL_RETURN(navDestination, false);

    auto mode = navigationPattern->GetNavigationMode();
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    if (isLastChild && (mode == NavigationMode::SPLIT ||
                           (mode == NavigationMode::STACK && layoutProperty->GetHideNavBar().value_or(false)))) {
        return false;
    }

    navigationPattern->RemoveNavDestination();
    return true;
}

void NavigationGroupNode::TransitionWithPop(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    CHECK_NULL_VOID(preNode);

    auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(preNavDestination);
    preNavDestination->SetTransitionType(PageTransitionType::EXIT_POP);

    /* obtain preTitle, preBackIcon and preFrameSize of preNavDestination */
    auto preTitleNode = AceType::DynamicCast<TitleBarNode>(preNavDestination->GetTitleBarNode());
    CHECK_NULL_VOID(preTitleNode);
    auto preBackIcon = AceType::DynamicCast<FrameNode>(preTitleNode->GetBackButton());
    CHECK_NULL_VOID(preBackIcon);

    auto preFrameSize = preNode->GetGeometryNode()->GetFrameSize();
    RefPtr<TitleBarNode> curTitleNode;
    if (curNode) {
        if (isNavBar) {
            auto navBarNode = AceType::DynamicCast<NavBarNode>(curNode);
            CHECK_NULL_VOID(navBarNode);
            navBarNode->SetTransitionType(PageTransitionType::ENTER_POP);
            curTitleNode = navBarNode ? AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode()) : nullptr;
        } else {
            auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            CHECK_NULL_VOID(curNavDestination);
            curNavDestination->SetTransitionType(PageTransitionType::ENTER_POP);
            curTitleNode =
                curNavDestination ? AceType::DynamicCast<TitleBarNode>(curNavDestination->GetTitleBarNode()) : nullptr;
        }
        CHECK_NULL_VOID(curTitleNode);
    }

    /* create animation finish callback */
    AnimationFinishCallback callback = [weakPreNode = WeakPtr<NavDestinationGroupNode>(preNavDestination),
        weakPreTitle = WeakPtr<TitleBarNode>(preTitleNode),
        weakPreBackIcon = WeakPtr<FrameNode>(preBackIcon),
        weakNavigation = WeakClaim(this),
        id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            // animation finish event should be posted to UI thread
            auto onFinishCallback = [weakPreNode, weakPreTitle, weakNavigation, weakPreBackIcon]() {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation pop animation end");
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
                auto navigation = weakNavigation.Upgrade();
                if (navigation) {
                    navigation->isOnAnimation_ = false;
                    navigation->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
                }
                auto preNavDesNode = weakPreNode.Upgrade();
                CHECK_NULL_VOID(preNavDesNode);
                if (preNavDesNode->GetTransitionType() != PageTransitionType::EXIT_POP) {
                    // has another transition, just return
                    return;
                }
                auto preNavDesPattern = preNavDesNode->GetPattern<NavDestinationPattern>();
                CHECK_NULL_VOID(preNavDesPattern);
                // NavRouter will restore the preNavDesNode and needs to set the initial state after the animation ends.
                auto shallowBuilder = preNavDesPattern->GetShallowBuilder();
                if (shallowBuilder) {
                    shallowBuilder->MarkIsExecuteDeepRenderDone(false);
                }
                preNavDesNode->SetIsOnAnimation(false);
                preNavDesNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
                preNavDesNode->GetRenderContext()->ClipWithRRect(RectF(0.0f, 0.0f, REMOVE_CLIP_SIZE, REMOVE_CLIP_SIZE),
                    RadiusF(EdgeF(0.0f, 0.0f)));
                preNavDesNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                auto preTitleNode = weakPreTitle.Upgrade();
                if (preTitleNode) {
                    preTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                }

                auto parent = preNavDesNode->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(preNavDesNode);
                parent->RebuildRenderContextTree();
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                context->MarkNeedFlushMouseEvent();
                context->RequestFrame();
            };
            taskExecutor->PostTask(onFinishCallback, TaskExecutor::TaskType::UI);
        };

    /* set initial status of animation */
    preNode->GetEventHub<EventHub>()->SetEnabledInternal(false);
    preNode->GetRenderContext()->ClipWithRRect(RectF(0.0f, 0.0f, preFrameSize.Width(), REMOVE_CLIP_SIZE),
        RadiusF(EdgeF(0.0f, 0.0f)));
    preNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    preTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    preNavDestination->SetIsOnAnimation(true);

    if (curNode) {
        auto curFrameSize = curNode->GetGeometryNode()->GetFrameSize();
        curNode->GetRenderContext()->ClipWithRRect(
            RectF(0.0f, 0.0f, REMOVE_CLIP_SIZE, REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
        curNode->GetRenderContext()->UpdateTranslateInXY({ -curFrameSize.Width() * PARENT_PAGE_OFFSET, 0.0f });
        curTitleNode->GetRenderContext()->UpdateTranslateInXY({ curFrameSize.Width() * PARENT_TITLE_OFFSET, 0.0f });
    }

    /* start transition animation */
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        callback);
    AnimationUtils::Animate(option, [preNode, preTitleNode, preFrameSize, curNode, curTitleNode]() {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation pop animation start");
        /* preNode */
        preNode->GetRenderContext()->ClipWithRRect(
            RectF(preFrameSize.Width() * HALF, 0.0f, preFrameSize.Width(), REMOVE_CLIP_SIZE),
            RadiusF(EdgeF(0.0f, 0.0f)));
        preNode->GetRenderContext()->UpdateTranslateInXY({ preFrameSize.Width() * HALF, 0.0f });
        preTitleNode->GetRenderContext()->UpdateTranslateInXY({ preFrameSize.Width() * HALF, 0.0f });

        /* curNode */
        if (curNode) {
            curNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
            curTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        }
    }, option.GetOnFinishEvent());

    /* opacity for title and backIcon */
    TitleOpacityAnimation(preTitleNode, true);
    BackButtonAnimation(preBackIcon, false);

    /* mask animation */
    if (curNode) {
        AnimationOption maskOption = CreateAnimationOption(Curves::FRICTION, FillMode::FORWARDS, MASK_DURATION,
            nullptr);
        curNode->GetRenderContext()->SetActualForegroundColor(MASK_COLOR);
        AnimationUtils::Animate(
            maskOption, [curNode]() { curNode->GetRenderContext()->SetActualForegroundColor(DEFAULT_MASK_COLOR); });
    }

    // clear this flag for navBar layout only
    if (isNavBar) {
        SetNeedSetInvisible(false);
    }
    isOnAnimation_ = true;
}

void NavigationGroupNode::TransitionWithPush(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    CHECK_NULL_VOID(preNode);
    CHECK_NULL_VOID(curNode);

    RefPtr<FrameNode> preTitleNode;
    if (isNavBar) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(preNode);
        navBarNode->SetTransitionType(PageTransitionType::EXIT_PUSH);
        preTitleNode = navBarNode ? AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode()) : nullptr;
    } else {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        navDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
        preTitleNode = navDestination ? AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode()) : nullptr;
    }
    CHECK_NULL_VOID(preTitleNode);

    auto mode = GetNavigationMode();
    auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
    CHECK_NULL_VOID(curNavDestination);
    curNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
    auto curTitleNode = AceType::DynamicCast<TitleBarNode>(curNavDestination->GetTitleBarNode());
    CHECK_NULL_VOID(curTitleNode);

    auto preFrameSize = preNode->GetGeometryNode()->GetFrameSize();
    auto curFrameSize = curNode->GetGeometryNode()->GetFrameSize();

    /* Create animation callback */
    AnimationFinishCallback callback = [weakPreNode = WeakPtr<FrameNode>(preNode),
        weakPreTitle = WeakPtr<FrameNode>(preTitleNode),
        weakNavigation = WeakClaim(this),
        weakCurNode = WeakPtr<FrameNode>(curNode),
        isNavBar, id = Container::CurrentId()] {
            ContainerScope scope(id);
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            // animation finish event should be posted to UI thread
            auto onFinishCallback = [weakPreNode, weakPreTitle, weakCurNode, weakNavigation, isNavBar] {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation push animation end");
                auto navigation = weakNavigation.Upgrade();
                CHECK_NULL_VOID(navigation);
                auto preNode = weakPreNode.Upgrade();
                CHECK_NULL_VOID(preNode);
                auto preTitle = weakPreTitle.Upgrade();
                if (preTitle) {
                    preTitle->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                }
                preNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
                preNode->GetRenderContext()->SetActualForegroundColor(DEFAULT_MASK_COLOR);
                bool needSetInvisible = false;
                if (isNavBar) {
                    needSetInvisible = AceType::DynamicCast<NavBarNode>(preNode)->GetTransitionType() ==
                        PageTransitionType::EXIT_PUSH;
                    // store this flag for navBar layout only
                    navigation->SetNeedSetInvisible(needSetInvisible);
                } else {
                    needSetInvisible = AceType::DynamicCast<NavDestinationGroupNode>(preNode)->GetTransitionType() ==
                                        PageTransitionType::EXIT_PUSH;
                }
                // for the case, the navBar form EXIT_PUSH to push during animation
                if (needSetInvisible) {
                    if (!isNavBar) {
                        preNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                        preNode->SetActive(false);
                    } else {
                        // navigation mode could be transformed to split mode in the process of animation and
                        // navBar will be invisible only under the stack mode
                        if (navigation->GetNavigationMode() == NavigationMode::STACK) {
                            preNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                            preNode->SetActive(false);
                            navigation->NotifyPageHide();
                        }
                    }
                }

                navigation->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
                auto curNode = weakCurNode.Upgrade();
                CHECK_NULL_VOID(curNode);
                if (AceType::DynamicCast<NavDestinationGroupNode>(curNode)->GetTransitionType() !=
                    PageTransitionType::ENTER_PUSH) {
                    return;
                }
                navigation->isOnAnimation_ = false;
                curNode->GetRenderContext()->ClipWithRRect(
                    RectF(0.0f, 0.0f, REMOVE_CLIP_SIZE, REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
            };
            taskExecutor->PostTask(onFinishCallback, TaskExecutor::TaskType::UI);
        };

    /* set initial status of animation */
    /* preNode */
    preNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    preTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    /* curNode */
    curNode->GetRenderContext()->ClipWithRRect(
        RectF(curFrameSize.Width() * HALF, 0.0f, curFrameSize.Width(), REMOVE_CLIP_SIZE),
        RadiusF(EdgeF(0.0f, 0.0f)));
    curNode->GetRenderContext()->UpdateTranslateInXY({ curFrameSize.Width() * HALF, 0.0f });
    curTitleNode->GetRenderContext()->UpdateTranslateInXY({ curFrameSize.Width() * HALF, 0.0f });

    /* start transition animation */
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        callback);
    AnimationUtils::Animate(option, [preNode, preTitleNode, curNode, curTitleNode, preFrameSize, curFrameSize,
        mode]() {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation push animation start");
        // preNode
        preNode->GetRenderContext()->UpdateTranslateInXY({ -preFrameSize.Width() * PARENT_PAGE_OFFSET, 0.0f });
        preTitleNode->GetRenderContext()->UpdateTranslateInXY({ preFrameSize.Width() * PARENT_TITLE_OFFSET, 0.0f });
        // curNode
        curNode->GetRenderContext()->ClipWithRRect(
            RectF(0.0f, 0.0f, curFrameSize.Width(), REMOVE_CLIP_SIZE), RadiusF(EdgeF(0.0f, 0.0f)));
        curNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
        curTitleNode->GetRenderContext()->UpdateTranslateInXY({ 0.0f, 0.0f });
    }, option.GetOnFinishEvent());
    MaskAnimation(preNode->GetRenderContext());

    // title opacity
    TitleOpacityAnimation(curTitleNode, false);
    // backIcon opacity
    auto backIcon = AceType::DynamicCast<FrameNode>(curTitleNode->GetBackButton());
    BackButtonAnimation(backIcon, true);
    isOnAnimation_ = true;
}

void NavigationGroupNode::BackButtonAnimation(const RefPtr<FrameNode>& backButtonNode, bool isTransitionIn)
{
    CHECK_NULL_VOID(backButtonNode);
    AnimationOption transitionOption;
    transitionOption.SetCurve(Curves::SHARP);
    auto backButtonNodeContext = backButtonNode->GetRenderContext();
    CHECK_NULL_VOID(backButtonNodeContext);
    if (isTransitionIn) {
        transitionOption.SetDelay(OPACITY_BACKBUTTON_IN_DELAY);
        transitionOption.SetDuration(OPACITY_BACKBUTTON_IN_DURATION);
        backButtonNodeContext->OpacityAnimation(transitionOption, 0.0, 1.0);
    } else {
        transitionOption.SetDuration(OPACITY_BACKBUTTON_OUT_DURATION);
        // recover after transition animation.
        transitionOption.SetOnFinishEvent([backButtonNodeContext]() {
            backButtonNodeContext->UpdateOpacity(1.0);
            backButtonNodeContext->SetOpacity(1.0f);
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
    transitionOutNodeContext->SetActualForegroundColor(DEFAULT_MASK_COLOR);
    AnimationUtils::Animate(
        maskOption, [transitionOutNodeContext]() { transitionOutNodeContext->SetActualForegroundColor(MASK_COLOR); },
        maskOption.GetOnFinishEvent());
}

void NavigationGroupNode::TitleOpacityAnimation(const RefPtr<FrameNode>& node, bool isTransitionOut)
{
    auto titleNode = AceType::DynamicCast<TitleBarNode>(node);
    CHECK_NULL_VOID(titleNode);
    auto titleRenderContext = titleNode->GetRenderContext();
    CHECK_NULL_VOID(titleRenderContext);
    AnimationOption opacityOption;
    opacityOption.SetCurve(Curves::SHARP);
    opacityOption.SetDuration(OPACITY_TITLE_DURATION);
    if (isTransitionOut) {
        opacityOption.SetDelay(OPACITY_TITLE_OUT_DELAY);
        // recover after transition animation.
        opacityOption.SetOnFinishEvent([titleRenderContext]() {
            titleRenderContext->UpdateOpacity(1.0);
            titleRenderContext->SetOpacity(1.0f);
        });
        titleRenderContext->OpacityAnimation(opacityOption, 1.0, 0.0);
    } else {
        opacityOption.SetDelay(OPACITY_TITLE_IN_DELAY);
        titleRenderContext->OpacityAnimation(opacityOption, 0.0, 1.0);
    }
}

void NavigationGroupNode::TransitionWithReplace(
    const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode, bool isNavBar)
{
    CHECK_NULL_VOID(preNode);
    CHECK_NULL_VOID(curNode);
    AnimationOption option;
    option.SetCurve(replaceCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_REPLACE_DURATION);
    option.SetOnFinishEvent([weakPreNode = WeakPtr<FrameNode>(preNode), weakNavigation = WeakClaim(this),
                                id = Container::CurrentId(), isNavBar]() {
        ContainerScope scope(id);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [weakPreNode, weakNavigation, isNavBar]() {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
                auto preNode = weakPreNode.Upgrade();
                CHECK_NULL_VOID(preNode);
                auto navigationNode = weakNavigation.Upgrade();
                CHECK_NULL_VOID(navigationNode);
                navigationNode->isOnAnimation_ = false;
                navigationNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
                navigationNode->DealNavigationExit(preNode, isNavBar);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                context->MarkNeedFlushMouseEvent();
            },
            TaskExecutor::TaskType::UI);
    });
    preNode->GetEventHub<EventHub>()->SetEnabledInternal(false);
    curNode->GetRenderContext()->UpdateOpacity(0.0f);
    if (!isNavBar) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        if (navDestination) {
            navDestination->SetIsOnAnimation(true);
        }
    }
    AnimationUtils::Animate(
        option,
        [curNode]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            curNode->GetRenderContext()->UpdateOpacity(1.0f);
        },
        option.GetOnFinishEvent());
    isOnAnimation_ = true;
}

void NavigationGroupNode::OnInspectorIdUpdate(const std::string& id)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddOrReplaceNavigationNode(id, WeakClaim(this));
    curId_ = id;
}

void NavigationGroupNode::DealNavigationExit(const RefPtr<FrameNode>& preNode, bool isNavBar, bool isAnimated)
{
    CHECK_NULL_VOID(preNode);
    if (preNode->GetEventHub<EventHub>()) {
        preNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
    }
    if (isNavBar && isAnimated) {
        SetNeedSetInvisible(true);
        return;
    }
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(navDestinationNode);
    navDestinationNode->SetIsOnAnimation(false);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    if (shallowBuilder) {
        shallowBuilder->MarkIsExecuteDeepRenderDone(false);
    }
    // remove old navdestination node
    if (navDestinationNode->GetContentNode()) {
        navDestinationNode->GetContentNode()->Clean();
    }
    auto parent = AceType::DynamicCast<FrameNode>(preNode->GetParent());
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(preNode);
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavigationGroupNode::NotifyPageHide()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto pageInfo = pagePattern->GetPageInfo();
    CHECK_NULL_VOID(pageInfo);
    pageUrlChecker->NotifyPageHide(pageInfo->GetPageUrl());
}

void NavigationGroupNode::UpdateLastStandardIndex()
{
    // remove the impact of last standard index
    lastStandardIndex_ = -1;
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    const auto& navDestinationNodes = navigationStack->GetAllNavDestinationNodes();
    if (navDestinationNodes.size() == 0) {
        return;
    }
    for (int32_t index = static_cast<int32_t>(navDestinationNodes.size()) - 1; index >= 0; index--) {
        const auto& curPath = navDestinationNodes[index];
        const auto& uiNode = curPath.second;
        if (!uiNode) {
            continue;
        }
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        if (navDestinationNode && navDestinationNode->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
            lastStandardIndex_ = index;
            return;
        }
    }
}

bool NavigationGroupNode::UpdateNavDestinationVisibility(const RefPtr<NavDestinationGroupNode>& navDestination,
    const RefPtr<UINode>& remainChild, int32_t index, size_t destinationSize)
{
    auto eventHub = navDestination->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (index == static_cast<int32_t>(destinationSize) - 1) {
        // process shallow builder
        navDestination->ProcessShallowBuilder();
        navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE, true);
        navDestination->SetActive(true);
        navDestination->GetEventHub<EventHub>()->SetEnabledInternal(true);
        // for the navDestination at the top, FireChangeEvent
        eventHub->FireChangeEvent(true);
        bool hasChanged = CheckNeedMeasure(navDestination->GetLayoutProperty()->GetPropertyChangeFlag());
        if (!hasChanged && NavigationLayoutAlgorithm::IsAutoHeight(GetLayoutProperty<NavigationLayoutProperty>())) {
            hasChanged = true;
        }
        return hasChanged;
    }
    if (index < lastStandardIndex_) {
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
        if (navDestination->GetPattern<NavDestinationPattern>()->GetNavDestinationNode() != remainChild &&
            !navDestination->IsOnAnimation()) {
            if (pattern && pattern->GetIsOnShow()) {
                // fire hidden event
                eventHub->FireOnHiddenEvent(pattern->GetName());
                eventHub->FireChangeEvent(false);
                pattern->SetIsOnShow(false);
                NavigationPattern::FireNavigationStateChange(navDestination, false);
            }
            navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
            navDestination->SetActive(false);
        }
        return false;
    }
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
    if (navDestination->GetPattern<NavDestinationPattern>()->GetNavDestinationNode() != remainChild &&
        !navDestination->IsOnAnimation()) {
        navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        navDestination->SetActive(true);
    }
    return false;
}

AnimationOption NavigationGroupNode::CreateAnimationOption(const RefPtr<Curve>& curve, FillMode mode,
    int32_t duration, const AnimationFinishCallback& callback)
{
    AnimationOption option;
    option.SetCurve(curve);
    option.SetFillMode(mode);
    option.SetDuration(duration);
    if (callback != nullptr) {
        option.SetOnFinishEvent(callback);
    }
    return option;
}

NavigationMode NavigationGroupNode::GetNavigationMode()
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_RETURN(navigationPattern, NavigationMode::AUTO);
    return navigationPattern->GetNavigationMode();
}

void NavigationGroupNode::OnDetachFromMainTree(bool recursive)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    if (pattern) {
        pattern->DetachNavigationStackFromParent();
    }

    GroupNode::OnDetachFromMainTree(recursive);
}

void NavigationGroupNode::OnAttachToMainTree(bool recursive)
{
    GroupNode::OnAttachToMainTree(recursive);

    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    if (pattern) {
        pattern->AttachNavigationStackToParent();
    }
}
} // namespace OHOS::Ace::NG
