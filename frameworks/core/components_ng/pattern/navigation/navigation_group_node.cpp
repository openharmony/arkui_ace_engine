/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/log/ace_checker.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"

#if !defined(ACE_UNITTEST)
#include "core/components_ng/base/transparent_node_detector.h"
#endif

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MASK_DURATION = 350;
constexpr int32_t DEFAULT_ANIMATION_DURATION = 450;
constexpr int32_t DEFAULT_REPLACE_DURATION = 150;
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t RELEASE_JSCHILD_DELAY_TIME = 50;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
const RefPtr<InterpolatingSpring> springCurve = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
const RefPtr<CubicCurve> replaceCurve = AceType::MakeRefPtr<CubicCurve>(0.33, 0.0, 0.67, 1.0);

void ExitWindow(PipelineContext* context)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsUIExtensionWindow()) {
        container->TerminateUIExtension();
    } else {
        auto windowManager = context->GetWindowManager();
        CHECK_NULL_VOID(windowManager);
        windowManager->WindowPerformBack();
    }
}

void UpdateTransitionAnimationId(const RefPtr<FrameNode>& node, int32_t id)
{
    auto navDestinationBaseNode = AceType::DynamicCast<NavDestinationNodeBase>(node);
    CHECK_NULL_VOID(navDestinationBaseNode);
    navDestinationBaseNode->UpdateAnimationId(id);
}

int32_t TriggerNavDestinationTransition(const RefPtr<NavDestinationGroupNode>& navDestination,
    NavigationOperation operation, bool isEnter)
{
    CHECK_NULL_RETURN(navDestination, INVALID_ANIMATION_ID);
    return navDestination->DoTransition(operation, isEnter);
}
} // namespace
class InspectorFilter;

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
    auto navigationPattern = GetPattern<NavigationPattern>();
    const auto& navDestinationNodes = navigationPattern->GetAllNavDestinationNodes();
    for (auto iter : navDestinationNodes) {
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(iter.second));
        if (navDestinationNode) {
            navDestinationNode->GetPattern<NavDestinationPattern>()->SetCustomNode(nullptr);
        }
    }
    auto context = GetContextWithCheck();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(pagePattern->GetPageInfo());
    int32_t pageId = pagePattern->GetPageInfo()->GetPageId();
    context->RemoveNavigationNode(pageId, GetId());
    context->DeleteNavigationNode(curId_);
}

void NavigationGroupNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(pattern);
    auto navBar = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBar);
    auto contentNode = navBar->GetContentNode();
    if (!contentNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        contentNode = FrameNode::GetOrCreateFrameNode(
            V2::NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navBar->SetContentNode(contentNode);
        navBar->AddChild(contentNode);

        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            auto navBarContentNode = AceType::DynamicCast<FrameNode>(contentNode);
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
                .edges = SAFE_AREA_EDGE_ALL };
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
    int32_t beforeLastStandardIndex = lastStandardIndex_;
    auto preLastStandardNode = AceType::DynamicCast<NavDestinationGroupNode>(
        navigationContentNode->GetChildAtIndex(beforeLastStandardIndex));
    if (pattern->GetIsPreForceSetList()) {
        // if page is force set, some node may not on the tree, so we need get page from preNavPathList.
        auto preNodes = pattern->GetAllNavDestinationNodesPrev();
        if (beforeLastStandardIndex < preNodes.size() && beforeLastStandardIndex >= 0) {
            preLastStandardNode = AceType::DynamicCast<NavDestinationGroupNode>(
                NavigationGroupNode::GetNavDestinationNode(preNodes[beforeLastStandardIndex].second.Upgrade()));
        }
    }

    //save preLastStandardIndex_ before update and check whether standard page changed
    preLastStandardIndex_ = lastStandardIndex_;
    UpdateLastStandardIndex();

    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "last standard page index is %{public}d", lastStandardIndex_);
    if (!ReorderNavDestination(navDestinationNodes, navigationContentNode, slot, hasChanged)) {
        return;
    }

    for (uint32_t index = 0; index < navDestinationNodes.size(); index++) {
        const auto& childNode = navDestinationNodes[index];
        const auto& uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        hasChanged = (UpdateNavDestinationVisibility(navDestination, remainChild, index,
            navDestinationNodes.size(), preLastStandardNode) || hasChanged);
    }

    RemoveRedundantNavDestination(
        navigationContentNode, remainChild, static_cast<int32_t>(slot), hasChanged, preLastStandardNode);
    if (modeChange) {
        navigationContentNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } else if (hasChanged) {
        navigationContentNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
}

bool NavigationGroupNode::ReorderNavDestination(
    const std::vector<std::pair<std::string, RefPtr<UINode>>>& navDestinationNodes,
    RefPtr<FrameNode>& navigationContentNode, int32_t& slot, bool& hasChanged)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_RETURN(pattern, false);
    for (uint32_t i = 0; i != navDestinationNodes.size(); ++i) {
        const auto& childNode = navDestinationNodes[i];
        const auto& uiNode = childNode.second;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(GetNavDestinationNode(uiNode));
        if (navDestination == nullptr) {
            if (pattern->GetNavigationStack()->IsFromRecovery(i) || pattern->GetNavigationStack()->GetIsForceSet(i)) {
                continue;
            }
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "get destination node failed");
            return false;
        }
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(navDestinationPattern, false);
        navDestinationPattern->SetName(childNode.first);
        navDestinationPattern->SetCustomNode(uiNode);
        navDestinationPattern->SetIndex(static_cast<int32_t>(i));
        SetBackButtonEvent(navDestination);
        navDestination->SetIndex(i);
        auto eventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
        if (eventHub && !eventHub->GetOnStateChange()) {
            auto onStateChangeMap = pattern->GetOnStateChangeMap();
            auto iter = onStateChangeMap.find(uiNode->GetId());
            if (iter != onStateChangeMap.end()) {
                eventHub->SetOnStateChange(iter->second);
                pattern->DeleteOnStateChangeItem(iter->first);
            }
        }
        int32_t childIndex = navigationContentNode->GetChildIndex(navDestination);
        if (childIndex < 0) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "mountToParent navdestinationId:%{public}d, slot:%{public}d",
                navDestination->GetId(), slot);
            navDestination->MountToParent(navigationContentNode, slot);
            hasChanged = true;
        } else if (childIndex != slot) {
            navDestination->MovePosition(slot);
            hasChanged = true;
        }
        slot++;
    }
    return true;
}

void NavigationGroupNode::RemoveRedundantNavDestination(RefPtr<FrameNode>& navigationContentNode,
    const RefPtr<UINode>& remainChild, int32_t slot, bool& hasChanged,
    const RefPtr<NavDestinationGroupNode>& preLastStandardNode)
{
    auto pattern = GetPattern<NavigationPattern>();
    RefPtr<UINode> maxAnimatingDestination = nullptr;
    RefPtr<UINode> remainDestination = GetNavDestinationNode(remainChild);
    RefPtr<UINode> curTopDestination = navigationContentNode->GetChildAtIndex(slot - 1);
    // record remove destination size
    int32_t removeSize = 0;
    bool hideNodesFinish = false;
    // record animating destination size
    int32_t animatingSize = 0;
    int32_t remainNodeIndex = pattern->IsCurTopNewInstance() ? slot - 1 : slot;
    while (slot + removeSize + animatingSize < static_cast<int32_t>(navigationContentNode->GetChildren().size())) {
        // delete useless nodes that are not at the top
        int32_t candidateIndex = static_cast<int32_t>(navigationContentNode->GetChildren().size()) - 1 - animatingSize;
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationContentNode->GetChildAtIndex(candidateIndex));
        if (!navDestination) {
            navigationContentNode->RemoveChildAtIndex(candidateIndex);
            hasChanged = true;
            continue;
        }
        navDestination->SetInCurrentStack(false);
        auto eventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
        if (eventHub) {
            eventHub->FireChangeEvent(false);
        }
        if (navDestination == remainDestination) {
            if (pattern->IsCurTopNewInstance()) {
                // remain the last child for push animation, and this child
                // will be remove in push's animation finish callback
                navDestination->SetNeedRemoveInPush(true);
                remainNodeIndex = slot - 1;
                navDestination->MovePosition(remainNodeIndex);
            } else {
                // remain the last child for pop animation
                remainNodeIndex = slot;
                navDestination->MovePosition(slot);
            }
            ++slot;
            continue;
        }
        // The NavDestination in the EXIT animation needs to be cleaned in the animation onfinish callback.
        if (navDestination->IsOnAnimation()) {
            if (navDestination->GetTransitionType() == PageTransitionType::EXIT_POP) {
                ++animatingSize;
                continue;
            }
            if (navDestination->NeedRemoveInPush()) {
                if (maxAnimatingDestination == nullptr) {
                    maxAnimatingDestination = navDestination;
                }
                ++animatingSize;
                continue;
            }
        }
        // remove content child
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "remove child: %{public}s", navDestinationPattern->GetName().c_str());
        if (navDestination->GetIndex() >= preLastStandardIndex_ && !hideNodesFinish) {
            if (navDestination->GetNavDestinationMode() == NavDestinationMode::STANDARD
                && preLastStandardNode != navDestination) {
                hideNodesFinish = true;
                DealRemoveDestination(navDestination);
                hasChanged = true;
                continue;
            }
            hideNodes_.emplace_back(std::make_pair(navDestination, true));
            navDestination->SetCanReused(false);
            removeSize++;
            // move current destination position to navigation stack size + remove navDestination nodes
            if (remainNodeIndex >= 0) {
                navDestination->MovePosition(remainNodeIndex);
            }
            continue;
        }
        DealRemoveDestination(navDestination);
        hasChanged = true;
    }
    if (pattern->IsCurTopNewInstance()) {
        ReorderAnimatingDestination(
            navigationContentNode, maxAnimatingDestination, remainDestination, curTopDestination);
    }
}

void NavigationGroupNode::ReorderAnimatingDestination(RefPtr<FrameNode>& navigationContentNode,
    RefPtr<UINode>& maxAnimatingDestination, RefPtr<UINode>& remainDestination, RefPtr<UINode>& curTopDestination)
{
    auto maxAnimatingIndex = navigationContentNode->GetChildIndex(maxAnimatingDestination);
    if (maxAnimatingIndex != -1 && remainDestination) {
        remainDestination->MovePosition(maxAnimatingIndex + 1);
    }
    auto remainIndex = navigationContentNode->GetChildIndex(remainDestination);
    if (remainIndex != -1 && curTopDestination) {
        curTopDestination->MovePosition(remainIndex + 1);
    }
}

void NavigationGroupNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    FrameNode::ToJsonValue(json, filter);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    if (titleBarNode) {
        std::string title = NavigationTitleUtil::GetTitleString(titleBarNode,
            navBarNode->GetPrevTitleIsCustomValue(false));
        std::string subtitle = NavigationTitleUtil::GetSubtitleString(titleBarNode);
        json->PutExtAttr("title", title.c_str(), filter);
        json->PutExtAttr("subtitle", subtitle.c_str(), filter);
    }
    json->PutExtAttr("menus", navBarNode->GetBarItemsString(true).c_str(), filter);
    json->PutExtAttr("toolBar", navBarNode->GetBarItemsString(false).c_str(), filter);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    json->PutExtAttr("titleMode", navBarLayoutProperty->GetTitleModeString().c_str(), filter);
    json->PutExtAttr("hideBackButton", navBarLayoutProperty->GetHideBackButtonValue(false), filter);
    json->PutExtAttr("hideTitleBar", navBarLayoutProperty->GetHideTitleBarValue(false), filter);
    json->PutExtAttr("hideToolBar", navBarLayoutProperty->GetHideToolBarValue(false), filter);
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
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetCustomBackButton());
    if (!backButtonNode) {
        backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    }
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonEventHub = backButtonNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(backButtonEventHub);
    auto onBackButtonEvent = [navDestinationWeak = WeakPtr<NavDestinationGroupNode>(navDestination),
                                 navigationWeak = WeakClaim(this)](GestureEvent& /*info*/) -> bool {
        auto navDestination = navDestinationWeak.Upgrade();
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "click navigation back button");
        CHECK_NULL_RETURN(navDestination, false);
        auto eventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        eventHub->SetState(NavDestinationState::ON_BACKPRESS);
        auto navdestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        UIObserverHandler::GetInstance().NotifyNavigationStateChange(
            navdestinationPattern, NavDestinationState::ON_BACKPRESS);
        auto isOverride = eventHub->GetOnBackPressedEvent();
        auto result = false;
        if (isOverride) {
            result = eventHub->FireOnBackPressedEvent();
        }
        auto navigation = navigationWeak.Upgrade();
        CHECK_NULL_RETURN(navigation, false);
        navigation->CheckIsNeedForceExitWindow(result);
        if (result) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation user onBackPress return true");
            return true;
        }
        // if set hideNavBar and stack size is one, return false
        auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(navigation->GetLayoutProperty());
        CHECK_NULL_RETURN(navigationLayoutProperty, false);
        auto pattern = AceType::DynamicCast<NavigationPattern>(navigation->GetPattern());
        CHECK_NULL_RETURN(pattern, false);
        auto stack = pattern->GetNavigationStack();
        CHECK_NULL_RETURN(stack, false);
        if (navigationLayoutProperty->GetHideNavBarValue(false) && stack->GetSize() <= 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "set hideNavBar and stack size is no more than one");
            return false;
        }
        auto isLastChild = stack->Size() == 1;
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

RefPtr<FrameNode> NavigationGroupNode::GetTopDestination()
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_RETURN(pattern, nullptr);
    auto navigationStack = pattern->GetNavigationStack();
    CHECK_NULL_RETURN(navigationStack, nullptr);
    auto topNavdestination = AceType::DynamicCast<FrameNode>(GetNavDestinationNode(navigationStack->Get()));
    return topNavdestination;
}

bool NavigationGroupNode::CheckCanHandleBack(bool& isEntry)
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
    if (!navigationPattern->IsFinishInteractiveAnimation()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't handle back press during interactive animation");
        return true;
    }
    auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
    if (navDestinationPattern->OverlayOnBackPressed()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination's ovelay consume backPressed event: %{public}s",
            navDestinationPattern->GetName().c_str());
        return true;
    }
    auto navDestinationContext = navDestinationPattern->GetNavDestinationContext();
    CHECK_NULL_RETURN(navDestinationContext, false);
    auto navPathInfo = navDestinationContext->GetNavPathInfo();
    CHECK_NULL_RETURN(navPathInfo, false);
    auto isPathEntry = navPathInfo->GetIsEntry();
    if (isPathEntry) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s is entry navDestination, do not consume backPressed event",
            navDestinationPattern->GetName().c_str());
        navPathInfo->SetIsEntry(false);
        auto index = navDestinationContext->GetIndex();
        navigationStack->SetIsEntryByIndex(index, false);
        isEntry = true;
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination consume back button event: %{public}s",
        navDestinationPattern->GetName().c_str());
    GestureEvent gestureEvent;
    return navDestination->GetNavDestinationBackButtonEvent()(gestureEvent);
}

void NavigationGroupNode::CheckIsNeedForceExitWindow(bool result)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (!context->GetInstallationFree() || !result) {
        // if is not atommic service and result is false, don't process.
        return;
    }
    
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto isHasParentNavigation = navigationPattern->GetParentNavigationPattern();
    auto navigationStack = navigationPattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    int32_t pageSize =
        stageManager->GetStageNode() ? static_cast<int32_t>(stageManager->GetStageNode()->GetChildren().size()) : 0;
    if (navigationStack->GetSize() != 1 || isHasParentNavigation || !overlayManager->IsModalEmpty() || pageSize != 1) {
        return;
    }
    
    /*
    * when stack size is one, there four situations.
    * 1.split mode, navbar visible.
    * 2.split mode, navbar invisible.
    * 3.stack mode, navbar visible.
    * 4.stack mode, navbar invisible.
    * Only the third situation don't need to be intercepted
    */
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool isSplitMode = GetNavigationMode() == NavigationMode::SPLIT;
    bool isLastNavdesNeedIntercept = isSplitMode || layoutProperty->GetHideNavBar().value_or(false);
    if (!isLastNavdesNeedIntercept) {
        return;
    }
    ExitWindow(context);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navdestination onbackpress intercepted, exit window.");
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

RefPtr<NavigationManager> NavigationGroupNode::FetchNavigationManager()
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_RETURN(navigationManager, nullptr);
    return navigationManager;
}

void NavigationGroupNode::ConfigureNavigationWithAnimation(
    const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode)
{
    auto navigationManager = FetchNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    if (!navigationManager->HasCacheNavigationNodeEnable()) {
        return;
    }
    navigationManager->SetNavNodeInTransition(curNode, preNode);
    navigationManager->SetIsNavigationOnAnimation(true);
}

void NavigationGroupNode::ResetTransitionAnimationNodeState(
    const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode)
{
    auto navigationManager = FetchNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    if (!navigationManager->HasCacheNavigationNodeEnable()) {
        return;
    }
    auto curNavDestContentFrameNode = navigationManager->GetNavDestContentFrameNode(curNode);
    if (curNavDestContentFrameNode) {
        navigationManager->UpdateAnimationCachedRenderGroup(curNavDestContentFrameNode, false);
        navigationManager->SetCurNodeAnimationCached(false);
        navigationManager->SetCurrentNodeNeverSet(true);
    }
    auto preNavDestContentFrameNode = navigationManager->GetNavDestContentFrameNode(preNode);
    if (preNavDestContentFrameNode) {
        navigationManager->UpdateAnimationCachedRenderGroup(preNavDestContentFrameNode, false);
        navigationManager->SetPreNodeAnimationCached(false);
        navigationManager->SetPreNodeNeverSet(true);
    }
    navigationManager->SetNavNodeInTransition(nullptr, nullptr);
    navigationManager->SetIsNavigationOnAnimation(false);
}

void NavigationGroupNode::CreateAnimationWithPop(const TransitionUnitInfo& preInfo, const TransitionUnitInfo& curInfo,
    const AnimationFinishCallback finishCallback, bool isNavBar)
{
    auto pattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    // this function has been override for different device type
    auto preNode = preInfo.transitionNode;
    auto curNode = curInfo.transitionNode;
    auto preUseCustomTransition = preInfo.isUseCustomTransition;
    auto curUseCustomTransition = curInfo.isUseCustomTransition;
    CHECK_NULL_VOID(preNode);
    auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(preNavDestination);
    if (!preUseCustomTransition) {
        preNavDestination->InitSystemTransitionPop(false);
    }
    if (curNode) {
        if (isNavBar) {
            auto navbarNode = AceType::DynamicCast<NavBarNode>(curNode);
            CHECK_NULL_VOID(navbarNode);
            navbarNode->InitSystemTransitionPop();
        } else {
            auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            CHECK_NULL_VOID(curNavDestination);
            if (!curUseCustomTransition) {
                curNavDestination->InitSystemTransitionPop(true);
            }
        }
    }
    // start transition animation
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        finishCallback);
    pattern->OnStartOneTransitionAnimation();
    auto newPopAnimation = AnimationUtils::StartAnimation(option, [
        this, preNode, curNode, isNavBar, preUseCustomTransition, curUseCustomTransition]() {
            ACE_SCOPED_TRACE_COMMERCIAL("Navigation page pop transition start");
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation pop animation start: animationId: %{public}d",
                static_cast<int32_t>(animationId_));

            // ENTER_POP nodes animation
            if (curNode) {
                if (isNavBar) {
                    auto curNavBar = AceType::DynamicCast<NavBarNode>(curNode);
                    CHECK_NULL_VOID(curNavBar);
                    curNavBar->StartSystemTransitionPop();
                } else if (!curUseCustomTransition) {
                    auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                    CHECK_NULL_VOID(curNavDestination);
                    curNavDestination->StartSystemTransitionPop(true);
                }
            }
            // EXIT_POP nodes finish animation
            auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
            CHECK_NULL_VOID(preNavDestination);
            if (!preUseCustomTransition) {
                preNavDestination->StartSystemTransitionPop(false);
            }
    }, option.GetOnFinishEvent());
    if (newPopAnimation) {
        popAnimations_.emplace_back(newPopAnimation);
    }
    if (!preUseCustomTransition) {
        auto titleOpacityAnimation = preNavDestination->TitleOpacityAnimation(false);
        if (titleOpacityAnimation) {
            popAnimations_.emplace_back(titleOpacityAnimation);
        }
        auto backButtonAnimation = preNavDestination->BackButtonAnimation(false);
        if (backButtonAnimation) {
            popAnimations_.emplace_back(backButtonAnimation);
        }
    }
    if (!curUseCustomTransition) {
        auto maskAnimation = MaskAnimation(curNode, true);
        if (maskAnimation) {
            popAnimations_.emplace_back(maskAnimation);
        }
    }
    ConfigureNavigationWithAnimation(preNode, curNode);
}

void NavigationGroupNode::TransitionWithPop(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    CHECK_NULL_VOID(preNode);
    /* create animation finish callback */
    CleanPopAnimations();
    // update animation id
    auto popAnimationId = MakeUniqueAnimationId();
    UpdateTransitionAnimationId(preNode, popAnimationId);
    UpdateTransitionAnimationId(curNode, popAnimationId);
    /* handle NavDestination CustomTransition, animationId of navDestination will be updated accordingly */
    int32_t preAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(preNode), NavigationOperation::POP, false);
    auto preUseCustomTransition = true;
    if (preAnimationId == INVALID_ANIMATION_ID) {
        preAnimationId = popAnimationId;
        preUseCustomTransition = false;
    }
    auto curUseCustomTransition = true;
    int32_t curAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(curNode), NavigationOperation::POP, true);
    if (curAnimationId == INVALID_ANIMATION_ID) {
        curAnimationId = popAnimationId;
        curUseCustomTransition = false;
    }
    if (preUseCustomTransition && curUseCustomTransition) {
        return;
    }
    std::function<void()> onFinish = [weakPreNode = WeakPtr<FrameNode>(preNode), preUseCustomTransition,
        weakCurNode = WeakPtr<FrameNode>(curNode), weakNavigation = WeakClaim(this), preAnimationId, curAnimationId] {
            ACE_SCOPED_TRACE_COMMERCIAL("Navigation page pop transition end");
            TAG_LOGI(AceLogTag::ACE_NAVIGATION,
                "navigation pop animation end, pre node animationId: %{public}d", preAnimationId);
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            navigation->isOnAnimation_ = false;
            auto id = navigation->GetTopDestination() ? navigation->GetTopDestination()->GetAccessibilityId() : -1;
            navigation->OnAccessibilityEvent(
                AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
            navigation->CleanPopAnimations();
            auto preNavDesNode = weakPreNode.Upgrade();
            CHECK_NULL_VOID(preNavDesNode);
            auto preNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(preNavDesNode);
            CHECK_NULL_VOID(preNavdestination);
            auto curNavDesNode = weakCurNode.Upgrade();
            navigation->ResetTransitionAnimationNodeState(preNavDesNode, curNavDesNode);
            if (preNavdestination->IsInDestroying()) {
                preNavdestination->SetDestroying(false, false);
            }
            if (!preUseCustomTransition && preNavdestination->SystemTransitionPopCallback(preAnimationId)) {
                // return true means need to remove the poped navdestination
                auto parent = preNavDesNode->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(preNavDesNode);
                parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            }
            auto context = navigation->GetContextWithCheck();
            CHECK_NULL_VOID(context);
            context->MarkNeedFlushMouseEvent();
            context->UpdateOcclusionCullingStatus(false, nullptr);
        };
    AnimationFinishCallback callback = [onFinishCb = std::move(onFinish), weakNavigation = WeakClaim(this)]() {
        auto navigation = weakNavigation.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(navigation);
        auto pattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    TransitionUnitInfo preInfo(preNode, preUseCustomTransition, preAnimationId);
    TransitionUnitInfo curInfo(curNode, curUseCustomTransition, curAnimationId);
    CreateAnimationWithPop(preInfo, curInfo, callback, isNavBar);
    // remove jschild when pop page animation begin
    RemoveJsChildImmediately(preNode, preUseCustomTransition, preAnimationId);

    // clear this flag for navBar layout only
    if (isNavBar) {
        SetNeedSetInvisible(false);
    }
    isOnAnimation_ = true;
    auto context = GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->UpdateOcclusionCullingStatus(true, preNode);
}

void NavigationGroupNode::RemoveJsChildImmediately(const RefPtr<FrameNode>& preNode, bool preUseCustomTransition,
    int32_t preAnimationId)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }

    auto preNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(preNavdestination);

    if (preUseCustomTransition || !preNavdestination->CheckTransitionPop(preAnimationId)) {
        return;
    }

    if (preNode->HasSkipNode()) {
        return;
    }

    auto removeJsFun = [weakPreNode = WeakPtr<FrameNode>(preNode)]() {
        auto preNavDesNode = weakPreNode.Upgrade();
        CHECK_NULL_VOID(preNavDesNode);
        preNavDesNode->SetDestroying();
    };
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(removeJsFun, TaskExecutor::TaskType::UI,
        RELEASE_JSCHILD_DELAY_TIME, "ArkUIRemoveJsChild");
}

void NavigationGroupNode::CreateAnimationWithPush(const TransitionUnitInfo& preInfo, const TransitionUnitInfo& curInfo,
    const AnimationFinishCallback finishCallback, bool isNavBar)
{
    auto pattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto preNode = preInfo.transitionNode;
    auto curNode = curInfo.transitionNode;
    auto preUseCustomTransition = preInfo.isUseCustomTransition;
    auto curUseCustomTransition = curInfo.isUseCustomTransition;
    // this function has been override for different device type
    if (isNavBar) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(preNode);
        CHECK_NULL_VOID(navBarNode);
        navBarNode->SystemTransitionPushAction(true);
    } else {
        if (preNode) {
            auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
            CHECK_NULL_VOID(navDestination);
            if (!preUseCustomTransition) {
                navDestination->InitSystemTransitionPush(false);
            }
        }
    }
    if (curNode) {
        auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
        CHECK_NULL_VOID(curNavDestination);
        if (!curUseCustomTransition) {
            curNavDestination->InitSystemTransitionPush(true);
        }
    }
    
    // start transition animation
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        finishCallback);
    pattern->OnStartOneTransitionAnimation();
    auto newPushAnimation = AnimationUtils::StartAnimation(option, [
        preNode, curNode, isNavBar, preUseCustomTransition, curUseCustomTransition]() {
            ACE_SCOPED_TRACE_COMMERCIAL("Navigation page push transition start");
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation push animation start");
            if (isNavBar) {
                auto navBarNode = AceType::DynamicCast<NavBarNode>(preNode);
                CHECK_NULL_VOID(navBarNode);
                navBarNode->StartSystemTransitionPush();
            } else {
                if (preNode && !preUseCustomTransition) {
                    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
                    CHECK_NULL_VOID(navDestination);
                    navDestination->StartSystemTransitionPush(false);
                }
            }
            // curNode
            if (curNode && !curUseCustomTransition) {
                auto curNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                CHECK_NULL_VOID(curNavdestination);
                curNavdestination->StartSystemTransitionPush(true);
            }
    }, option.GetOnFinishEvent());
    if (newPushAnimation) {
        pushAnimations_.emplace_back(newPushAnimation);
    }
    if (!preUseCustomTransition) {
        auto maskAnimation = MaskAnimation(preNode, false);
        if (maskAnimation) {
            pushAnimations_.emplace_back(maskAnimation);
        }
    }
    if (!curUseCustomTransition) {
        CHECK_NULL_VOID(curNode);
        auto curNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
        CHECK_NULL_VOID(curNavdestination);
        // title opacity
        auto titleOpacityAnimation = curNavdestination->TitleOpacityAnimation(true);
        if (titleOpacityAnimation) {
            pushAnimations_.emplace_back(titleOpacityAnimation);
        }
        // backIcon opacity
        auto backButtonAnimation = curNavdestination->BackButtonAnimation(true);
        if (backButtonAnimation) {
            pushAnimations_.emplace_back(backButtonAnimation);
        }
    }
    if (preNode) {
        preNode->SetNodeFreeze(true);
    }
    ConfigureNavigationWithAnimation(preNode, curNode);
}

RefPtr<FrameNode> NavigationGroupNode::TransitionAnimationIsValid(
    const RefPtr<FrameNode>& node, bool isNavBar, bool isUseNavDestCustomTransition)
{
    if (isNavBar || isUseNavDestCustomTransition) {
        return node;
    }
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(node);
    if (destination && destination->GetSystemTransitionType() == NavigationSystemTransitionType::NONE) {
        return nullptr;
    }
    return node;
}

void NavigationGroupNode::TransitionWithPush(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    CHECK_NULL_VOID(preNode);
    CHECK_NULL_VOID(curNode);

    // Create animation callback
    CleanPushAnimations();
    auto pushAnimationId = MakeUniqueAnimationId();
    UpdateTransitionAnimationId(preNode, pushAnimationId);
    UpdateTransitionAnimationId(curNode, pushAnimationId);
    /* handle NavDestination CustomTransition, animationId of navDestination will be updated accordingly */
    int32_t preAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(preNode), NavigationOperation::PUSH, false);
    auto preUseCustomTransition = true;
    if (preAnimationId == INVALID_ANIMATION_ID) {
        preAnimationId = pushAnimationId;
        preUseCustomTransition = false;
    }
    auto curUseCustomTransition = true;
    int32_t curAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(curNode), NavigationOperation::PUSH, true);
    if (curAnimationId == INVALID_ANIMATION_ID) {
        curAnimationId = pushAnimationId;
        curUseCustomTransition = false;
    }
    if (preUseCustomTransition && curUseCustomTransition) {
        return;
    }
    std::function<void()> onFinish = [weakPreNode = WeakPtr<FrameNode>(preNode), preUseCustomTransition,
        weakCurNode = WeakPtr<FrameNode>(curNode), curUseCustomTransition, weakNavigation = WeakClaim(this),
        isNavBar, preAnimationId, curAnimationId] {
            ACE_SCOPED_TRACE_COMMERCIAL("Navigation page push transition end");
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation push animation end");
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            auto preNode = weakPreNode.Upgrade();
            while (preNode) {
                preNode->SetNodeFreeze(false);
                preNode->GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
                if (!navigation->CheckAnimationIdValid(preNode, preAnimationId)) {
                    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "pre node is doing another animation, skip handling.");
                    break;
                }
                if (isNavBar) {
                    auto navbar = AceType::DynamicCast<NavBarNode>(preNode);
                    CHECK_NULL_VOID(navbar);
                    navbar->SystemTransitionPushAction(false);
                    bool needSetInvisible = navbar->GetTransitionType() == PageTransitionType::EXIT_PUSH;
                    navigation->SetNeedSetInvisible(needSetInvisible);
                    bool isInvisible = navbar->IsNodeInvisible(navigation);
                    if (needSetInvisible && isInvisible) {
                        preNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                        preNode->SetJSViewActive(false);
                        navigation->NotifyPageHide();
                    }
                    navbar->GetRenderContext()->SetOpacity(1.0f);
                } else {
                    auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
                    CHECK_NULL_VOID(preDestination);
                    if (preUseCustomTransition) {
                        // no need handle pre node here. it will be handled in its custom transition callback.
                        break;
                    }
                    if (preDestination->NeedRemoveInPush()) {
                        navigation->hideNodes_.emplace_back(std::make_pair(preDestination, true));
                        break;
                    }
                    preDestination->SystemTransitionPushCallback(false, preAnimationId);
                    preDestination->GetRenderContext()->SetOpacity(1.0f);
                }
                break;
            }
            auto curNode = weakCurNode.Upgrade();
            if (curNode) {
                auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                CHECK_NULL_VOID(curNavDestination);
                if (!curUseCustomTransition) {
                    navigation->ResetTransitionAnimationNodeState(preNode, curNode);
                    curNavDestination->SystemTransitionPushCallback(true, curAnimationId);
                }
            }
            navigation->RemoveDialogDestination();
            auto id = navigation->GetTopDestination() ? navigation->GetTopDestination()->GetAccessibilityId() : -1;
            navigation->OnAccessibilityEvent(
                AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
            navigation->isOnAnimation_ = false;
            navigation->CleanPushAnimations();
            auto pattern = navigation->GetPattern<NavigationPattern>();
            pattern->CheckContentNeedMeasure(navigation);
            auto context = navigation->GetContextWithCheck();
            CHECK_NULL_VOID(context);
            context->UpdateOcclusionCullingStatus(false, nullptr);
        };

    AnimationFinishCallback callback = [onFinishCb = std::move(onFinish), weakNavigation = WeakClaim(this)]() {
        auto navigation = weakNavigation.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(navigation);
        auto pattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    auto preNodeNew = TransitionAnimationIsValid(preNode, isNavBar, preUseCustomTransition);
    auto curNodeNew = TransitionAnimationIsValid(curNode, isNavBar, curUseCustomTransition);
    if (preNodeNew != nullptr || curNodeNew != nullptr) {
        TransitionUnitInfo preInfo(preNodeNew, preUseCustomTransition, preAnimationId);
        TransitionUnitInfo curInfo(curNodeNew, curUseCustomTransition, curAnimationId);
        CreateAnimationWithPush(preInfo, curInfo, callback, isNavBar);
    }

    isOnAnimation_ = true;
    auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
    CHECK_NULL_VOID(curNavDestination);
    if (AceChecker::IsPerformanceCheckEnabled()) {
        int64_t startTime = GetSysTimestamp();
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(GetContextWithCheck());
        CHECK_NULL_VOID(pipeline);
        // After completing layout tasks at all nodes on the page, perform performance testing and management
        pipeline->AddAfterLayoutTask([weakNav = WeakClaim(this), weakNode = WeakPtr<FrameNode>(curNode), startTime,
                                         path = curNavDestination->GetNavDestinationPathInfo()]() {
            auto navigation = weakNav.Upgrade();
            CHECK_NULL_VOID(navigation);
            auto curNode = weakNode.Upgrade();
            int64_t endTime = GetSysTimestamp();
            CHECK_NULL_VOID(curNode);
            PerformanceCheckNodeMap nodeMap;
            curNode->GetPerformanceCheckData(nodeMap);
            AceScopedPerformanceCheck::RecordPerformanceCheckData(nodeMap, endTime - startTime, path);
        });
    }
#if !defined(ACE_UNITTEST)
    TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(curNode,
        curNavDestination->GetNavDestinationPathInfo());
#endif
    auto context = GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->UpdateOcclusionCullingStatus(true, curNode);
}

std::shared_ptr<AnimationUtils::Animation> NavigationGroupNode::MaskAnimation(const RefPtr<FrameNode>& node,
    bool isTransitionIn)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(node);
    if (navDestination && navDestination->TransitionContentInValid()) {
        return nullptr;
    }
    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    maskOption.SetFillMode(FillMode::FORWARDS);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    if (isTransitionIn) {
        renderContext->SetActualForegroundColor(MASK_COLOR);
        return AnimationUtils::StartAnimation(
            maskOption, [weakRender = WeakPtr<RenderContext>(renderContext)]() {
                auto context = weakRender.Upgrade();
                CHECK_NULL_VOID(context);
                context->SetActualForegroundColor(Color::TRANSPARENT);
            });
    }
    renderContext->SetActualForegroundColor(Color::TRANSPARENT);
    return AnimationUtils::StartAnimation(
        maskOption, [weakRender = WeakPtr<RenderContext>(renderContext)]() {
            auto context = weakRender.Upgrade();
            CHECK_NULL_VOID(context);
            context->SetActualForegroundColor(MASK_COLOR);
        });
}

void NavigationGroupNode::TransitionWithReplace(
    const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode, bool isNavBar)
{
    CHECK_NULL_VOID(preNode);
    CHECK_NULL_VOID(curNode);
    auto replaceAnimationId = MakeUniqueAnimationId();
    UpdateTransitionAnimationId(preNode, replaceAnimationId);
    UpdateTransitionAnimationId(curNode, replaceAnimationId);
    /* handle NavDestination CustomTransition, animationId of navDestination will be updated accordingly */
    int32_t preAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(preNode), NavigationOperation::REPLACE, false);
    auto preUseCustomTransition = true;
    if (preAnimationId == INVALID_ANIMATION_ID) {
        preAnimationId = replaceAnimationId;
        preUseCustomTransition = false;
    }
    int32_t curAnimationId = TriggerNavDestinationTransition(
        DynamicCast<NavDestinationGroupNode>(curNode), NavigationOperation::REPLACE, true);
    auto curUseCustomTransition = true;
    if (curAnimationId != INVALID_ANIMATION_ID) {
        curAnimationId = replaceAnimationId;
        curUseCustomTransition = false;
    }
    if (preUseCustomTransition && curUseCustomTransition) {
        return;
    }
    std::function<void()> onFinish = [weakPreNode = WeakPtr<FrameNode>(preNode),
        weakNavigation = WeakClaim(this), isNavBar, preAnimationId, curAnimationId,
        weakCurNode = WeakPtr<FrameNode>(curNode), preUseCustomTransition]() {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation replace animation end");
        ACE_SCOPED_TRACE_COMMERCIAL("Navigation page replace transition end");
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
        auto preNode = weakPreNode.Upgrade();
        CHECK_NULL_VOID(preNode);
        auto navigationNode = weakNavigation.Upgrade();
        CHECK_NULL_VOID(navigationNode);
        navigationNode->isOnAnimation_ = false;
        auto id = navigationNode->GetTopDestination() ? navigationNode->GetTopDestination()->GetAccessibilityId() : -1;
        navigationNode->OnAccessibilityEvent(
            AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
        preNode->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
        if (!navigationNode->CheckAnimationIdValid(preNode, preAnimationId)) {
            return;
        }
        if (!preUseCustomTransition) {
            navigationNode->DealNavigationExit(preNode, isNavBar);
        }
        auto curNode = weakCurNode.Upgrade();
        navigationNode->ResetTransitionAnimationNodeState(preNode, curNode);
        auto context = navigationNode->GetContextWithCheck();
        CHECK_NULL_VOID(context);
        context->MarkNeedFlushMouseEvent();
    };
    AnimationFinishCallback callback = [onFinishCb = std::move(onFinish), weakNavigation = WeakClaim(this)]() {
        auto navigation = weakNavigation.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(navigation);
        auto pattern = navigation->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    AnimationOption option;
    option.SetCurve(replaceCurve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(DEFAULT_REPLACE_DURATION);
    option.SetOnFinishEvent(callback);

    preNode->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(false);
    auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
    if (curNavDestination && curNavDestination->IsNeedContentTransition() && !curUseCustomTransition) {
        curNode->GetRenderContext()->UpdateOpacity(0.0f);
    }
    if (!isNavBar) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        if (navDestination && !curUseCustomTransition) {
            navDestination->SetIsOnAnimation(true);
        }
    }
    auto pattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->OnStartOneTransitionAnimation();
    AnimationUtils::Animate(
        option,
        [curNode, curUseCustomTransition]() {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation replace animation start");
            ACE_SCOPED_TRACE_COMMERCIAL("Navigation page replace transition start");
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            if (curNavDestination && curNavDestination->IsNeedContentTransition() && !curUseCustomTransition) {
                curNode->GetRenderContext()->UpdateOpacity(1.0f);
            }
        },
        option.GetOnFinishEvent());
    isOnAnimation_ = true;
    ConfigureNavigationWithAnimation(preNode, curNode);
}

void NavigationGroupNode::OnInspectorIdUpdate(const std::string& id)
{
    auto context = GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->AddOrReplaceNavigationNode(id, WeakClaim(this));
    curId_ = id;
}

void NavigationGroupNode::DealNavigationExit(const RefPtr<FrameNode>& preNode, bool isNavBar, bool isAnimated)
{
    CHECK_NULL_VOID(preNode);
    if (preNode->GetOrCreateEventHub<EventHub>()) {
        preNode->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
    }
    if (isNavBar && isAnimated) {
        SetNeedSetInvisible(true);
        return;
    }
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(navDestinationNode);
    navDestinationNode->SetIsOnAnimation(false);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto stack = navigationPattern->GetNavigationStack();
    bool isInStack = stack->FindIndex(navDestinationPattern->GetName(),
        navDestinationPattern->GetCustomNode(), true) != -1;
    if (isInStack) {
        RemoveDialogDestination(true);
        auto preContext = navDestinationNode->GetRenderContext();
        CHECK_NULL_VOID(preContext);
        preContext->UpdateZIndex(0);
        return;
    }
    navDestinationNode->CleanContent();
    auto parent = AceType::DynamicCast<FrameNode>(preNode->GetParent());
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(preNode);
    RemoveDialogDestination(true);
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavigationGroupNode::NotifyPageHide()
{
    auto context = GetContextWithCheck();
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
    const RefPtr<UINode>& remainChild, int32_t index, size_t destinationSize, const RefPtr<UINode>& preLastStandardNode)
{
    CHECK_NULL_RETURN(navDestination, false);
    auto eventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (index == static_cast<int32_t>(destinationSize) - 1) {
        // process shallow builder
        navDestination->ProcessShallowBuilder();
        navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE, true);
        navDestination->SetJSViewActive(true);
        navDestination->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
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
        if (navDestination->IsOnAnimation()) {
            return false;
        }
        if (!pattern || !pattern->GetIsOnShow()) {
            // push more than one standard navDestination, need to set invisible below newTopDestination
            auto navDestinationLayoutProperty = navDestination->GetLayoutProperty();
            CHECK_NULL_RETURN(navDestinationLayoutProperty, false);
            navDestinationLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
            navDestination->SetJSViewActive(false);
            return false;
        }
        eventHub->FireChangeEvent(false);
        if (pattern->GetCustomNode() != remainChild) {
            if (navDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG ||
                navDestination == AceType::DynamicCast<NavDestinationGroupNode>(preLastStandardNode)) {
                hideNodes_.insert(hideNodes_.begin(), std::pair(navDestination, false));
            } else {
                navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
                auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
                pattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_WILL_HIDE);
                pattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_HIDE);
            }
        }
        return false;
    }
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
    if (navDestination->GetPattern<NavDestinationPattern>()->GetCustomNode() != remainChild &&
        !navDestination->IsOnAnimation()) {
        navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        navDestination->SetJSViewActive(true);
    }
    return false;
}

NavigationMode NavigationGroupNode::GetNavigationMode()
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_RETURN(navigationPattern, NavigationMode::AUTO);
    return navigationPattern->GetNavigationMode();
}

void NavigationGroupNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    if (pattern) {
        pattern->DetachNavigationStackFromParent();
        pattern->RemoveFromDumpManager();
    }
    GroupNode::OnDetachFromMainTree(recursive, context);
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    if (navigationManager) {
        navigationManager->RemoveNavigation(GetId());
    }
}

bool NavigationGroupNode::FindNavigationParent(const std::string& parentName)
{
    auto parent = GetParent();
    while (parent) {
        if (parent->GetTag() == parentName) {
            AddDestinationNode(parent);
            return true;
        }
        parent = parent->GetParent();
    }
    return parent != nullptr;
}

void NavigationGroupNode::AddDestinationNode(const RefPtr<UINode>& parent)
{
    auto destinationNode = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    if (destinationNode) {
        parentDestinationNode_ = destinationNode;
    }
}

void NavigationGroupNode::OnAttachToMainTree(bool recursive)
{
    GroupNode::OnAttachToMainTree(recursive);

    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    if (pattern) {
        pattern->AttachNavigationStackToParent();
        pattern->AddToDumpManager();
    }
    RefPtr<UINode> parentCustomNode;
    bool findParentNode = false;
    auto curNode = GetParent();
    while (curNode) {
        auto curTag = curNode->GetTag();
        // check parentCustomNode is nullptr, to avoid parentCustomNode re-assignment
        if (!parentCustomNode && curTag == V2::JS_VIEW_ETS_TAG) {
            parentCustomNode = curNode;
        }
        if (!findParentNode) {
            findParentNode = CheckNeedUpdateParentNode(curNode);
        }
        if (parentCustomNode && findParentNode) {
            break;
        }
        curNode = curNode->GetParent();
    }
    if (parentCustomNode) {
        pattern->SetParentCustomNode(parentCustomNode);
    } else {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "parent custom node is nullptr");
    }
    if (!findParentNode) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "current navigation has no parent page");
    }
    auto pipelineContext = GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    bool findNavdestination = FindNavigationParent(V2::NAVDESTINATION_VIEW_ETS_TAG);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(pagePattern->GetPageInfo());
    int32_t pageId = pagePattern->GetPageInfo()->GetPageId();
    if (!findNavdestination) {
        pipelineContext->AddNavigationNode(pageId, WeakClaim(this));
    }
}

bool NavigationGroupNode::CheckNeedUpdateParentNode(const RefPtr<UINode>& curNode)
{
    // only the first time need to be assigned
    CHECK_NULL_RETURN(curNode, false);
    bool isFindParent = false;
    auto curTag = curNode->GetTag();
    RefPtr<UINode> parentNode;
    do {
        if (curTag == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            auto curParent = curNode->GetParent();
            // check whether current destination is redirected throut transition
            if (curParent && curParent->GetTag() == V2::NAVIGATION_CONTENT_ETS_TAG) {
                parentNode = curNode;
                isFindParent = true;
            }
            break;
        }
        if (curTag == V2::PAGE_ETS_TAG || curTag == V2::MODAL_PAGE_TAG ||
            curTag == V2::SHEET_PAGE_TAG) {
            // check current navigation is in modal page, sheet page and page,
            // dialog and overlay is not need recorded
            parentNode = curNode;
            isFindParent = true;
            break;
        }
        if (curTag == V2::NAVBAR_ETS_TAG) {
            // if navigation is under navBar node. don't need to record relationShip
            isFindParent = true;
        }
    } while (0);
    if (!isFindParent || !parentNode) {
        return isFindParent;
    }
    auto pipelineContext = GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, true);
    auto navigationManager = pipelineContext->GetNavigationManager();
    CHECK_NULL_RETURN(navigationManager, true);
    // update navigation manager map <parentId, std::vector<navigationId>>
    navigationManager->AddNavigation(parentNode->GetId(), GetId());
    return true;
}

void NavigationGroupNode::FireHideNodeChange(NavDestinationLifecycle lifecycle)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    for (auto iter = hideNodes_.begin(); iter != hideNodes_.end(); ++iter) {
        auto navDestination = iter->first;
        if (!navDestination) {
            continue;
        }
        if (lifecycle == NavDestinationLifecycle::ON_WILL_DISAPPEAR) {
            if (iter->second) {
                navigationPattern->NotifyDestinationLifecycle(
                    navDestination, NavDestinationLifecycle::ON_WILL_DISAPPEAR);
            }
            continue;
        }
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
        if (!pattern->GetIsOnShow()) {
            continue;
        }
        if (lifecycle == NavDestinationLifecycle::ON_WILL_HIDE) {
            navigationPattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_WILL_HIDE);
            continue;
        }
        if (lifecycle == NavDestinationLifecycle::ON_HIDE) {
            navigationPattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_HIDE);
        }
    }
}

void NavigationGroupNode::RemoveDialogDestination(bool isReplace, bool isTriggerByInteractiveCancel)
{
    for (auto iter = hideNodes_.begin(); iter != hideNodes_.end(); iter++) {
        auto navDestination = iter->first;
        if (!navDestination) {
            continue;
        }
        if (!iter->second) {
            auto type = navDestination->GetTransitionType();
            bool isEnterPage = (type == PageTransitionType::ENTER_PUSH || type == PageTransitionType::ENTER_POP);
            if (!isTriggerByInteractiveCancel && isEnterPage) {
                // if tigger by interactive animation, The transition type is incorrect, ignore this case.
                continue;
            }
            // navDestination node don't need to remove, update visibility invisible
            navDestination->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
            navDestination->SetJSViewActive(false);
            if (!isReplace) {
                continue;
            }
            auto context = navDestination->GetRenderContext();
            if (!context) {
                continue;
            }
            context->UpdateZIndex(0);
            continue;
        }
        auto parent = navDestination->GetParent();
        if (!parent) {
            continue;
        }
        auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(navDestination->GetPattern());
        if (!navDestinationPattern) {
            continue;
        }
        navDestination->CleanContent();
        parent->RemoveChild(navDestination);
    }
    hideNodes_.clear();
}

void NavigationGroupNode::DealRemoveDestination(const RefPtr<NavDestinationGroupNode>& navDestination)
{
    // remove content child
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    auto pattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    if (navDestinationPattern->GetIsOnShow()) {
        pattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_WILL_HIDE);
        pattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_HIDE);
        navDestinationPattern->SetIsOnShow(false);
    }
    pattern->NotifyDestinationLifecycle(navDestination, NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    navDestination->CleanContent();
    contentNode_->RemoveChild(navDestination, true);
}

void NavigationGroupNode::CreateAnimationWithDialogPop(const AnimationFinishCallback callback,
    const std::vector<WeakPtr<FrameNode>> preNavList,
    const std::vector<WeakPtr<FrameNode>> curNavList)
{
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    // start transition animation
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        callback);
    navigationPattern->OnStartOneTransitionAnimation();
    auto newPopAnimation = AnimationUtils::StartAnimation(option, [
       weakNavigation = WeakClaim(this), curNavList, preNavList]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog pop animation start");

            // do preNode transition
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            for (auto iter: preNavList) {
                auto preNode = iter.Upgrade();
                CHECK_NULL_VOID(preNode);
                auto preNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
                if (preNavDesNode) {
                    preNavDesNode->StartSystemTransitionPop(false);
                }
            }

            // do currentNode transition
            for (auto iter: curNavList) {
                auto curNode = iter.Upgrade();
                CHECK_NULL_VOID(curNode);
                if (curNode->GetTag() == V2::NAVBAR_ETS_TAG) {
                    auto curNavbar = AceType::DynamicCast<NavBarNode>(curNode);
                    CHECK_NULL_VOID(curNavbar);
                    curNavbar->StartSystemTransitionPop();
                } else {
                    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                    CHECK_NULL_VOID(curDestination);
                    curDestination->StartSystemTransitionPop(true);
                }
            }
    }, option.GetOnFinishEvent());
    if (newPopAnimation) {
        popAnimations_.emplace_back(newPopAnimation);
    }
    isOnAnimation_ = true;
}

void NavigationGroupNode::TransitionWithDialogPop(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    CHECK_NULL_VOID(preNode);
    std::vector<WeakPtr<FrameNode>> preNavList;
    InitPopPreList(preNode, preNavList);
    std::vector<WeakPtr<FrameNode>> curNavList;
    bool isNavbarNeedAnimation = lastStandardIndex_ == -1 || isNavBar;
    InitPopCurList(curNode, curNavList, isNavbarNeedAnimation);

    /* create animation finish callback */
    CleanPopAnimations();
    std::function<void()> onFinish = [preNavList, weakNavigation = WeakClaim(this), weakCurNode = WeakPtr(curNode)] {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog pop animation end TransitionWithDialogPop");
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            navigation->isOnAnimation_ = false;
            navigation->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
            navigation->CleanPopAnimations();
            for (auto iter = preNavList.rbegin(); iter != preNavList.rend(); ++iter) {
                auto preNode = (*iter).Upgrade();
                if (!preNode) {
                    continue;
                }
                auto preNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
                CHECK_NULL_VOID(preNavDesNode);
                auto pattern = navigation->GetPattern<NavigationPattern>();
                CHECK_NULL_VOID(pattern);
                bool isIncurStack = pattern->FindInCurStack(preNode);
                if (preNavDesNode->SystemTransitionPopCallback(preNavDesNode->GetAnimationId(), !isIncurStack)) {
                    auto parent = preNavDesNode->GetParent();
                    CHECK_NULL_VOID(parent);
                    if (!isIncurStack) {
                        parent->RemoveChild(preNavDesNode);
                    }
                }
                navigation->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
            }
            navigation->RemoveDialogDestination();
            auto context = navigation->GetContextWithCheck();
            CHECK_NULL_VOID(context);
            context->MarkNeedFlushMouseEvent();
        };
    AnimationFinishCallback callback = [onFinishCb = std::move(onFinish), weak = WeakPtr(navigationPattern)]() {
        auto pattern = weak.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    CreateAnimationWithDialogPop(callback, preNavList, curNavList);
}

void NavigationGroupNode::CreateAnimationWithDialogPush(const AnimationFinishCallback callback,
    const std::vector<WeakPtr<FrameNode>> prevNavList, const std::vector<WeakPtr<FrameNode>> curNavList)
{
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    // start transition animation
    AnimationOption option = CreateAnimationOption(springCurve, FillMode::FORWARDS, DEFAULT_ANIMATION_DURATION,
        callback);
    navigationPattern->OnStartOneTransitionAnimation();
    auto newPushAnimation = AnimationUtils::StartAnimation(option,
        [weakNavigation = WeakClaim(this), prevNavList, curNavList]() {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog push animation start");
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);

            // preNode do EXIT PUSH animation
            for (auto iter : prevNavList) {
                auto preNode = iter.Upgrade();
                CHECK_NULL_VOID(preNode);
                if (preNode->GetTag() == V2::NAVBAR_ETS_TAG &&
                    navigation->GetNavigationMode() == NavigationMode::STACK) {
                    auto navBarNode = AceType::DynamicCast<NavBarNode>(preNode);
                    CHECK_NULL_VOID(navBarNode);
                    navBarNode->StartSystemTransitionPush();
                } else {
                    auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
                    CHECK_NULL_VOID(preDestination);
                    preDestination->StartSystemTransitionPush(false);
                }
            }
            // curNode do ENTER PUSH animation
            for (auto iter : curNavList) {
                auto curNode = iter.Upgrade();
                CHECK_NULL_VOID(curNode);
                auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                if (curDestination) {
                    curDestination->StartSystemTransitionPush(true);
                }
            }
    }, option.GetOnFinishEvent());
    if (newPushAnimation) {
        pushAnimations_.emplace_back(newPushAnimation);
    }
    isOnAnimation_ = true;
}

void NavigationGroupNode::PreNodeFinishCallback(const RefPtr<FrameNode>& preNode)
{
    CHECK_NULL_VOID(preNode);
    if (preNode->GetTag() == V2::NAVBAR_ETS_TAG) {
        auto preNavbar = AceType::DynamicCast<NavBarNode>(preNode);
        CHECK_NULL_VOID(preNavbar);
        preNavbar->SystemTransitionPushAction(false);
        bool needSetInvisible = preNavbar->GetTransitionType() == PageTransitionType::EXIT_PUSH;
        SetNeedSetInvisible(needSetInvisible);
        if (needSetInvisible && GetNavigationMode() == NavigationMode::STACK) {
            auto property = preNavbar->GetLayoutProperty();
            CHECK_NULL_VOID(property);
            property->UpdateVisibility(VisibleType::INVISIBLE);
            preNavbar->SetJSViewActive(false);
            NotifyPageHide();
        }
        return;
    }
    if (preNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        if (preDestination && preDestination->NeedRemoveInPush()) {
            hideNodes_.emplace_back(std::make_pair(preDestination, true));
        }
        preDestination->SystemTransitionPushCallback(false, preDestination->GetAnimationId());
    }
}

void NavigationGroupNode::TransitionWithDialogPush(const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode,
    bool isNavBar)
{
    if (!preNode || !curNode) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "dialog push animation terminated");
        return;
    }

    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    CleanPushAnimations();

    // initialization
    bool isNavbarNeedAnimation = preLastStandardIndex_ == -1 || isNavBar;
    std::vector<WeakPtr<FrameNode>> prevNavList;
    InitPushPreList(preNode, prevNavList, isNavbarNeedAnimation);
    std::vector<WeakPtr<FrameNode>> curNavList;
    InitPushCurList(curNode, curNavList);
    std::function<void()> onFinish =
        [weakNavigation = WeakClaim(this), prevNavList, curNavList, weakCurNode = WeakPtr(curNode)] {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog push animation end");
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            for (auto iter : prevNavList) {
                auto preNode = iter.Upgrade();
                if (!preNode) {
                    continue;
                }
                navigation->PreNodeFinishCallback(preNode);
            }
            for (auto iter : curNavList) {
                auto curNode = iter.Upgrade();
                if (!curNode) {
                    continue;
                }
                auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
                CHECK_NULL_VOID(curNavDestination);
                curNavDestination->SystemTransitionPushCallback(true, curNavDestination->GetAnimationId());
            }
            navigation->RemoveDialogDestination();
            navigation->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
            navigation->isOnAnimation_ = false;
            navigation->CleanPushAnimations();
        };
    AnimationFinishCallback callback = [onFinishCb = std::move(onFinish), weak = WeakPtr(navigationPattern)]() {
        auto pattern = weak.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    if (preNode) {
        auto renderContext = preNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->RemoveClipWithRRect();
    }
    CreateAnimationWithDialogPush(callback, prevNavList, curNavList);
}

void NavigationGroupNode::StartDialogtransition(const RefPtr<FrameNode>& preNode,
    const RefPtr<FrameNode>& curNode, bool isTransitionIn)
{
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    const float defaultAmplitudePx = 0.005f;
    curve->UpdateMinimumAmplitudeRatio(defaultAmplitudePx);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    if (isTransitionIn) {
        DialogTransitionPushAnimation(preNode, curNode, option);
        TriggerNavDestinationTransition(
            DynamicCast<NavDestinationGroupNode>(preNode), NavigationOperation::PUSH, false);
    } else {
        DialogTransitionPopAnimation(preNode, curNode, option);
        TriggerNavDestinationTransition(
            DynamicCast<NavDestinationGroupNode>(curNode), NavigationOperation::POP, true);
    }
}

void NavigationGroupNode::DialogTransitionPushAnimation(const RefPtr<FrameNode>& preNode,
    const RefPtr<FrameNode>& curNode, AnimationOption option)
{
    CHECK_NULL_VOID(curNode);
    auto curNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
    CHECK_NULL_VOID(curNavdestination);
    int32_t end = curNavdestination->GetIndex();
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    const auto& navDestinationNodesCur = navigationPattern->GetAllNavDestinationNodes();
    int32_t start = 0;
    if (preNode && preNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto navdestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        CHECK_NULL_VOID(navdestination);
        start = navdestination->GetIndex() + 1;
        auto renderContext = preNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->RemoveClipWithRRect();
    }
    // find the nodes need to do upward ENTER translation
    std::vector<WeakPtr<NavDestinationGroupNode>> curNavList;
    for (int32_t index = start; index <= end; index++) {
        auto navdestination = GetNavDestinationNode(navDestinationNodesCur[index].second);
        CHECK_NULL_VOID(navdestination);
        auto curNode = AceType::DynamicCast<FrameNode>(navdestination);
        CHECK_NULL_VOID(curNode);
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
        CHECK_NULL_VOID(navDestination);
        if (TriggerNavDestinationTransition(navDestination, NavigationOperation::PUSH, true) == INVALID_ANIMATION_ID) {
            navDestination->InitDialogTransition(false);
            curNavList.emplace_back(WeakPtr<NavDestinationGroupNode>(navDestination));
        }
    }
    CleanPushAnimations();
    std::function<void()> onFinish = [weakNavigation = WeakClaim(this), weakCurNode = WeakPtr<FrameNode>(curNode),
                                      weakPreNode = WeakPtr<FrameNode>(preNode)] {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog push animation end");
        auto navigation = weakNavigation.Upgrade();
        CHECK_NULL_VOID(navigation);
        auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(weakPreNode.Upgrade());
        if (preNavDestination && preNavDestination->NeedRemoveInPush()) {
            navigation->hideNodes_.emplace_back(std::make_pair(preNavDestination, true));
        }
        navigation->RemoveDialogDestination();
        navigation->CleanPushAnimations();
        auto curNode = weakCurNode.Upgrade();
        auto preNode = weakPreNode.Upgrade();
        navigation->ResetTransitionAnimationNodeState(preNode, curNode);
    };
    auto finishWrapper = [onFinishCb = std::move(onFinish), weak = WeakPtr(navigationPattern)]() {
        auto pattern = weak.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    option.SetOnFinishEvent(finishWrapper);
    navigationPattern->OnStartOneTransitionAnimation();
    auto newPushAnimation = AnimationUtils::StartAnimation(option,
        [curNavList]() {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation dialog push animation start");
            for (auto iter: curNavList) {
                auto curNode = iter.Upgrade();
                if (curNode) {
                    curNode->InitDialogTransition(true);
                }
            }
        },
    option.GetOnFinishEvent());
    if (newPushAnimation) {
        pushAnimations_.emplace_back(newPushAnimation);
    }
    ConfigureNavigationWithAnimation(preNode, curNode);
}

std::vector<WeakPtr<NavDestinationGroupNode>> NavigationGroupNode::FindNodesPoped(
    const RefPtr<FrameNode>& preNode, const RefPtr<FrameNode>& curNode)
{
    std::vector<WeakPtr<NavDestinationGroupNode>> preNavList;
    auto preNavdestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_RETURN(preNavdestinationNode, preNavList);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_RETURN(navigationPattern, preNavList);
    const auto& navDestinationNodesPre = navigationPattern->GetAllNavDestinationNodesPrev();
    int32_t start = 0;
    if (curNode && curNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto curNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
        CHECK_NULL_RETURN(curNavdestination, preNavList);
        start = preLastStandardIndex_ + 1;
    }
    // find the nodes need to do downward EXIT translation
    auto stack = navigationPattern->GetNavigationStack();
    int32_t size = static_cast<int32_t>(navDestinationNodesPre.size());
    for (int32_t index = start; index < size; index++) {
        auto node = GetNavDestinationNode(navDestinationNodesPre[index].second.Upgrade());
        if (!node) {
            continue;
        }
        auto preNode = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_RETURN(preNode, preNavList);
        auto preNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        CHECK_NULL_RETURN(preNavDesNode, preNavList);
        bool isInCurStack = stack->FindIndex(navDestinationNodesPre[index].first,
            navDestinationNodesPre[index].second.Upgrade(), true) != -1;
        if (!isInCurStack) {
            // this node not in current stack should do animation.
            if (TriggerNavDestinationTransition(preNavDesNode, NavigationOperation::POP, false)
                == INVALID_ANIMATION_ID) {
                // has no custom transition or system transition, so do default animation.
                preNavDesNode->InitDialogTransition(true);
                preNavList.emplace_back(WeakPtr<NavDestinationGroupNode>(preNavDesNode));
            }
        } else {
            // update visbility when this node is under the last standard page
            if (preNavDesNode->GetIndex() < lastStandardIndex_) {
                preNavDesNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
            }
        }
    }
    return preNavList;
}

void NavigationGroupNode::DialogTransitionPopAnimation(const RefPtr<FrameNode>& preNode,
    const RefPtr<FrameNode>& curNode, AnimationOption option)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto preNavList = FindNodesPoped(preNode, curNode);
    CleanPopAnimations();
    std::function<void()> onFinish =
        [preNavList, weakNavigation = WeakClaim(this), weakCurNode = WeakPtr<FrameNode>(curNode),
         weakPreNode = WeakPtr<FrameNode>(preNode)] {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "dialog transition pop animation end");
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            auto curNode = weakCurNode.Upgrade();
            auto preNode = weakPreNode.Upgrade();
            navigation->ResetTransitionAnimationNodeState(preNode, curNode);
            for (auto iter: preNavList) {
                auto preNode = iter.Upgrade();
                CHECK_NULL_VOID(preNode);
                auto parent = preNode->GetParent();
                CHECK_NULL_VOID(parent);
                
                auto pattern = navigation->GetPattern<NavigationPattern>();
                bool isIncurStack = pattern->FindInCurStack(preNode);
                if (!isIncurStack) {
                    parent->RemoveChild(preNode);
                    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                }
            }
            navigation->RemoveDialogDestination();
            auto context = navigation->GetContextWithCheck();
            CHECK_NULL_VOID(context);
            context->MarkNeedFlushMouseEvent();
            navigation->CleanPopAnimations();
        };
    auto finishWrapper = [onFinishCb = std::move(onFinish), weak = WeakPtr(navigationPattern)]() {
        auto pattern = weak.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    option.SetOnFinishEvent(finishWrapper);

    navigationPattern->OnStartOneTransitionAnimation();
    auto newPopAnimation = AnimationUtils::StartAnimation(
        option, [weakNavigation = WeakClaim(this), preNavList]() {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "dialog transition pop animation start");
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            for (auto iter: preNavList) {
                auto preNode = iter.Upgrade();
                CHECK_NULL_VOID(preNode);
                preNode->InitDialogTransition(false);
            }
    }, option.GetOnFinishEvent());
    if (newPopAnimation) {
        popAnimations_.emplace_back(newPopAnimation);
    }
    ConfigureNavigationWithAnimation(preNode, curNode);
}

void NavigationGroupNode::InitPopPreList(const RefPtr<FrameNode>& preNode, std::vector<WeakPtr<FrameNode>>& preNavList)
{
    // find all the nodes need to do EXIT_POP
    int32_t preStartIndex = preLastStandardIndex_;
    if (preStartIndex == -1) {
        // eg. clear + push page1
        preStartIndex = 0;
    }
    auto preNavdestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    CHECK_NULL_VOID(preNavdestinationNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    const auto& preNavDestinationNodes = navigationPattern->GetAllNavDestinationNodesPrev();

    // find the nodes need to do EXIT_POP
    for (int32_t index = preStartIndex; index < static_cast<int32_t>(preNavDestinationNodes.size()); index++) {
        auto node = GetNavDestinationNode(preNavDestinationNodes[index].second.Upgrade());
        CHECK_NULL_VOID(node);
        auto preNode = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(preNode);
        auto preNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        if (preNavDestination && TriggerNavDestinationTransition(
            preNavDestination, NavigationOperation::POP, false) == INVALID_ANIMATION_ID) {
            preNavDestination->InitSystemTransitionPop(false);
            preNavList.emplace_back(WeakPtr<FrameNode>(preNode));
        }
    }
}

void NavigationGroupNode::InitPopCurList(const RefPtr<FrameNode>& curNode, std::vector<WeakPtr<FrameNode>>& curNavList,
    bool isNavbarNeedAnimation)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto curNavdestionNodes = navigationPattern->GetAllNavDestinationNodes();
    auto curStartIndex = lastStandardIndex_;

    // navBar + D or navBar should be in animation
    if (isNavbarNeedAnimation) {
        curStartIndex = 0;
    }
    // if navBar should be in animation, do initialization and visibility should be true
    if (isNavbarNeedAnimation && navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        auto preNode = AceType::DynamicCast<FrameNode>(GetNavBarNode());
        if (preNode) {
            auto navBarNode = AceType::DynamicCast<NavBarNode>(preNode);
            CHECK_NULL_VOID(navBarNode);
            navBarNode->InitSystemTransitionPop();
            curNavList.emplace_back(WeakPtr<FrameNode>(preNode));
            SetNeedSetInvisible(false);
        }
    }
    int32_t size = static_cast<int32_t>(curNavdestionNodes.size());
    if (size == 0) {
        return;
    }
    // find the nodes need to do ENTER_POP
    for (int32_t index = curStartIndex; index < size; index++) {
        auto node = GetNavDestinationNode(curNavdestionNodes[index].second);
        CHECK_NULL_VOID(node);
        auto curNode = AceType::DynamicCast<FrameNode>(node);
        if (curNode) {
            auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            if (navDestination && TriggerNavDestinationTransition(
                navDestination, NavigationOperation::POP, true) == INVALID_ANIMATION_ID) {
                navDestination->InitSystemTransitionPop(true);
                curNavList.emplace_back(WeakPtr<FrameNode>(curNode));
            }
        }
    }
}

void NavigationGroupNode::InitPushPreList(const RefPtr<FrameNode>& preNode,
    std::vector<WeakPtr<FrameNode>>& prevNavList, bool isNavbarNeedAnimation)
{
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto stack = navigationPattern->GetNavigationStack();
    auto& preNavdestinationNodes = navigationPattern->GetAllNavDestinationNodesPrev();
    auto preStartIndex = preLastStandardIndex_;

    // find the pre last standard index, if there is no pre standard or pre node is single navbar
    if (isNavbarNeedAnimation) {
        preStartIndex = 0;
    }
    // if pre node is nav bar or one of preNodes is nav bar and only stack with navbar's animation
    if (isNavbarNeedAnimation&& navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        auto preNode = AceType::DynamicCast<FrameNode>(GetNavBarNode());
        CHECK_NULL_VOID(preNode);
        auto preNavbar = AceType::DynamicCast<NavBarNode>(preNode);
        if (preNavbar) {
            SetNeedSetInvisible(false);
            preNavbar->SystemTransitionPushAction(true);
            prevNavList.emplace_back(WeakPtr<FrameNode>(preNode));
        }
    }
    int32_t size = static_cast<int32_t>(preNavdestinationNodes.size());
    if (size == 0) {
        return;
    }
    // find the nodes need to do EXIT_PUSH
    for (int32_t index = preStartIndex; index < size; index++) {
        auto node = GetNavDestinationNode(preNavdestinationNodes[index].second.Upgrade());
        CHECK_NULL_VOID(node);
        auto preNode = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(preNode);
        auto preNavdestination = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
        if (preNavdestination && TriggerNavDestinationTransition(
            preNavdestination, NavigationOperation::PUSH, false) == INVALID_ANIMATION_ID) {
            preNavdestination->InitSystemTransitionPush(false);
            prevNavList.emplace_back(WeakPtr<FrameNode>(preNode));
        }
    }
}

void NavigationGroupNode::InitPushCurList(const RefPtr<FrameNode>& curNode, std::vector<WeakPtr<FrameNode>>& curNavList)
{
    // find the nodes need to do ENTER_PUSH
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(GetPattern());
    CHECK_NULL_VOID(navigationPattern);
    auto curNavdestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
    CHECK_NULL_VOID(curNavdestinationNode);
    auto curEndIndex = curNavdestinationNode->GetIndex();
    auto curStartIndex = lastStandardIndex_;
    auto stack = navigationPattern->GetNavigationStack();
    for (int32_t index = curStartIndex; index <= curEndIndex; index++) {
        auto node = GetNavDestinationNode(stack->Get(index));
        CHECK_NULL_VOID(node);
        auto curNode = AceType::DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(curNode);
        auto curNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
        if (curNavDestination && TriggerNavDestinationTransition(
            curNavDestination, NavigationOperation::PUSH, true) == INVALID_ANIMATION_ID) {
            curNavDestination->InitSystemTransitionPush(true);
            curNavList.emplace_back(WeakPtr<FrameNode>(curNode));
        }
    }
}

AnimationOption NavigationGroupNode::CreateAnimationOption(const RefPtr<Curve>& curve, FillMode mode,
    int32_t duration, const NavigationGroupNode::AnimationFinishCallback& callback)
{
    AnimationOption option;
    option.SetCurve(curve);
    option.SetFillMode(mode);
    option.SetDuration(duration);
    option.SetOnFinishEvent(callback);
    return option;
}

bool NavigationGroupNode::CheckAnimationIdValid(const RefPtr<FrameNode>& curNode, const int32_t animationId)
{
    auto navDestinationBaseNode = AceType::DynamicCast<NavDestinationNodeBase>(curNode);
    CHECK_NULL_RETURN(navDestinationBaseNode, false);
    auto result = navDestinationBaseNode->GetAnimationId() == animationId;
    if (!result) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "animation id is invalid");
    }
    return result;
}

std::string NavigationGroupNode::ToDumpString()
{
    std::string dumpString;
    auto navigationPattern = GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navigationPattern, dumpString);
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(navigationLayoutProperty, dumpString);
    NavigationMode usrSetMode = navigationLayoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO);
    NavigationMode actualMode = navigationPattern->GetNavigationMode();
    std::string mode;
    switch (usrSetMode) {
        case NavigationMode::STACK:
            mode = "STACK";
            break;
        case NavigationMode::SPLIT:
            mode = "SPLIT";
            break;
        case NavigationMode::AUTO:
            mode = (actualMode == NavigationMode::STACK) ? "AUTO(STACK)" : "AUTO(SPLIT)";
            break;
        default:
            mode = "INVALID";
            break;
    }
    dumpString.append("|-> Navigation ID: ");
    dumpString.append(std::to_string(GetId()));
    dumpString.append(", Depth: ");
    dumpString.append(std::to_string(GetDepth()));
    dumpString.append(", Mode: \"");
    dumpString.append(mode);
    dumpString.append("\", NavDestinations:");
    return dumpString;
}

void NavigationGroupNode::ResetSystemAnimationProperties(const RefPtr<FrameNode>& navDestinationNode)
{
    auto navDestination = DynamicCast<NavDestinationGroupNode>(navDestinationNode);
    CHECK_NULL_VOID(navDestination);
    auto renderContext = navDestination->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    // update navDestination's translateXY
    renderContext->UpdateTranslateInXY({ 0.0f, 0.0f });
    auto titleBarNode = AceType::DynamicCast<FrameNode>(navDestination->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarRenderContext = titleBarNode->GetRenderContext();
    CHECK_NULL_VOID(titleBarRenderContext);
    // update titleBar's translateXY
    titleBarRenderContext->UpdateTranslateInXY({ 0.0f, 0.0f });
}
} // namespace OHOS::Ace::NG
