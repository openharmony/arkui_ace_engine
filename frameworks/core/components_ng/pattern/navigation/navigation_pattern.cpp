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
#include <string>

#include "base/log/dump_log.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/perfmonitor/perf_constants.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {

constexpr int32_t NAVIMODE_CHANGE_ANIMATION_DURATION = 250;
constexpr int32_t OPACITY_ANIMATION_DURATION_APPEAR = 150;
constexpr int32_t OPACITY_ANIMATION_DURATION_DISAPPEAR = 250;
constexpr int32_t EMPTY_DESTINATION_CHILD_SIZE = 1;
constexpr Dimension DEFAULT_DRAG_REGION = 12.0_vp;
constexpr float DEFAULT_HALF = 2.0f;

namespace {

constexpr static int32_t PLATFORM_VERSION_TEN = 10;

} // namespace

NavigationPattern::NavigationPattern()
{
    navigationController_ = std::make_shared<InnerNavigationController>(WeakClaim(this));
}

RefPtr<RenderContext> NavigationPattern::GetTitleBarRenderContext()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, nullptr);
    if (contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) {
        auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
        CHECK_NULL_RETURN(navBarNode, nullptr);
        auto renderContext = navBarNode->GetRenderContext();
        return renderContext;
    } else {
        auto renderContext = contentNode->GetRenderContext();
        return renderContext;
    }
}

void NavigationPattern::DoAnimation(NavigationMode usrNavigationMode)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    layoutProperty->UpdateNavigationMode(navigationMode_);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    AnimationOption option = AnimationOption();
    option.SetDuration(NAVIMODE_CHANGE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationOption optionAlpha = AnimationOption();
    optionAlpha.SetCurve(Curves::SHARP);
    optionAlpha.SetFillMode(FillMode::FORWARDS);
    auto renderContext = GetTitleBarRenderContext();
    CHECK_NULL_VOID(renderContext);

    std::function<void()> finishCallback = [optionAlpha, renderContext, hostNode]() {
        renderContext->OpacityAnimation(optionAlpha, 0, 1);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    context->OpenImplicitAnimation(option, option.GetCurve(), finishCallback);
    layoutProperty->UpdateNavigationMode(usrNavigationMode);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    if (usrNavigationMode == NavigationMode::STACK || navigationMode_ == NavigationMode::SPLIT) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_DISAPPEAR);
        renderContext->OpacityAnimation(optionAlpha, 1, 0);
    } else if (usrNavigationMode == NavigationMode::SPLIT || navigationMode_ == NavigationMode::STACK) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_APPEAR);
        renderContext->OpacityAnimation(optionAlpha, 0, 1);
    }
    context->CloseImplicitAnimation();
    navigationMode_ = usrNavigationMode;
}

void NavigationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowStateChangedCallback(host->GetId());
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    CHECK_NULL_VOID(pagePattern->GetPageInfo());
    int32_t pageId = pagePattern->GetPageInfo()->GetPageId();

    // when use router,  onShowCallback will be called when page show
    std::function<void()> onShowCallback = [weakNavigationNode = WeakPtr<NavigationGroupNode>(navigationNode),
        pageId]() {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto navigationNode = weakNavigationNode.Upgrade();
        CHECK_NULL_VOID(navigationNode);
        pipelineContext->AddWindowStateChangedCallback(navigationNode->GetId());
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CHECK_NULL_VOID(navigationPattern->navigationStack_);
        navigationPattern->NotifyDialogChange(true, false);
    };
    pipelineContext->AddNavigationStateCallback(pageId, navigationNode->GetId(), onShowCallback, true);
    // when use router,  onShowCallback will be called when page hide
    std::function<void()> onHideCallback = [weakNavigationNode = WeakPtr<NavigationGroupNode>(navigationNode),
        pageId]() {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto navigationNode = weakNavigationNode.Upgrade();
        CHECK_NULL_VOID(navigationNode);
        pipelineContext->RemoveWindowStateChangedCallback(navigationNode->GetId());
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
        CHECK_NULL_VOID(navigationPattern);
        CHECK_NULL_VOID(navigationPattern->navigationStack_);
        navigationPattern->NotifyDialogChange(false, false);
    };
    pipelineContext->AddNavigationStateCallback(pageId, navigationNode->GetId(), onHideCallback, false);
    auto theme = NavigationGetTheme();
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }
    SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL};
    host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
}

void NavigationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void NavigationPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->MarkModifyDone();
    CHECK_NULL_VOID(navigationStack_);
    auto preTopNavPath = navigationStack_->GetPreTopNavPath();
    auto pathNames = navigationStack_->GetAllPathName();
    auto preSize = navigationStack_->PreSize();
    auto cacheNodes = navigationStack_->GetAllCacheNodes();
    NavPathList navPathList;
    auto replaceValue = navigationStack_->GetReplaceValue();
    for (size_t i = 0; i < pathNames.size(); ++i) {
        auto pathName = pathNames[i];
        RefPtr<UINode> uiNode = navigationStack_->Get(pathName);
        auto isSameWithLast = preTopNavPath && (replaceValue == 1) && (uiNode == preTopNavPath->second)
            && (preTopNavPath->first == pathName);
        if (uiNode) {
            navigationStack_->RemoveInNavPathList(pathName, uiNode);
            navigationStack_->RemoveInPreNavPathList(pathName, uiNode);
            if (isSameWithLast) {
                uiNode = GenerateUINodeByIndex(static_cast<int32_t>(i));
            }
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            continue;
        }
        uiNode = navigationStack_->GetFromPreBackup(pathName);
        if (uiNode) {
            navigationStack_->RemoveInPreNavPathList(pathName, uiNode);
            if (isSameWithLast) {
                uiNode = GenerateUINodeByIndex(static_cast<int32_t>(i));
            }
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            continue;
        }
        uiNode = navigationStack_->GetFromCacheNode(cacheNodes, pathName);
        if (uiNode) {
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            navigationStack_->RemoveCacheNode(cacheNodes, pathName, uiNode);
            continue;
        }
        uiNode = GenerateUINodeByIndex(static_cast<int32_t>(i));
        navPathList.emplace_back(std::make_pair(pathName, uiNode));
    }

    navigationStack_->SetNavPathList(navPathList);
    hostNode->UpdateNavDestinationNodeWithoutMarkDirty(
        preTopNavPath.has_value() ? preTopNavPath->second : nullptr, navigationModeChange_);
    auto newTopNavPath = navigationStack_->GetTopNavPath();
    auto size = navigationStack_->Size();
    CheckTopNavPathChange(preTopNavPath, newTopNavPath, preSize > size);

    /* if first navDestination is removed, the new one will be refreshed */
    if (!navPathList.empty()) {
        auto firstNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(navPathList.front().second));
        CHECK_NULL_VOID(firstNavDesNode);
        firstNavDesNode->MarkModifyDone();
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto currentPlatformVersion = pipeline->GetMinPlatformVersion();

    if (currentPlatformVersion >= PLATFORM_VERSION_TEN) {
        auto dividerNode = GetDividerNode();
        CHECK_NULL_VOID(dividerNode);
        auto gestureHub = dividerNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        InitDragEvent(gestureHub);
        auto inputHub = dividerNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        InitDividerMouseEvent(inputHub);
    }
}

void NavigationPattern::CheckTopNavPathChange(
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath, bool isPopPage)
{
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (preTopNavPath == newTopNavPath && replaceValue != 1) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "page is not change. don't transition");
        if (currentProxy_) {
            currentProxy_->SetIsSuccess(false);
        }
        return;
    }

    // close keyboard
#if defined (ENABLE_STANDARD_INPUT)
    if (Container::CurrentId() == CONTAINER_ID_DIVIDE_SIZE) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Nav notNeedSoftKeyboard.");
        FocusHub::NavCloseKeyboard();
    }
#endif

    isChanged_ = true;
    if (replaceValue == 1) {
        const int32_t replaceAnimation = 2;
        navigationStack_->UpdateReplaceValue(replaceAnimation);
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto contentNode = hostNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    // fire onHidden and lostFocus event
    RefPtr<NavDestinationGroupNode> preTopNavDestination;
    int32_t lastPreIndex = -1;
    if (preTopNavPath.has_value()) {
        // pre page is not in the current stack
        lastPreIndex = navigationStack_->FindIndex(preTopNavPath->first, preTopNavPath->second, true);
        isPopPage |= lastPreIndex == -1;
        preTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath->second));
        if (preTopNavDestination) {
            auto navDestinationPattern =
                AceType::DynamicCast<NavDestinationPattern>(preTopNavDestination->GetPattern());
            CHECK_NULL_VOID(navDestinationPattern);
            if (navDestinationPattern->GetIsOnShow()) {
                auto eventHub = preTopNavDestination->GetEventHub<NavDestinationEventHub>();
                CHECK_NULL_VOID(eventHub);
                NotifyPageHide(preTopNavPath->first);
            }
            auto focusHub = preTopNavDestination->GetOrCreateFocusHub();
            focusHub->SetParentFocusable(false);
            focusHub->LostFocus();
        }
    } else {
        // navBar to new top page case
        auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        auto focusHub = navBarNode->GetOrCreateFocusHub();
        focusHub->LostFocus();
    }
    RefPtr<NavDestinationGroupNode> newTopNavDestination;
    // fire onShown and requestFocus Event
    if (newTopNavPath.has_value()) {
        newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second));
        if (newTopNavDestination) {
            auto navDestinationPattern =
                AceType::DynamicCast<NavDestinationPattern>(newTopNavDestination->GetPattern());
            CHECK_NULL_VOID(navDestinationPattern);
            if (!navDestinationPattern->GetIsOnShow()) {
                NotifyPageShow(newTopNavPath->first);
            }
            auto focusHub = newTopNavDestination->GetOrCreateFocusHub();
            context->AddAfterLayoutTask([focusHub]() {
                focusHub->SetParentFocusable(true);
                focusHub->RequestFocus();
            });
        }
    } else {
        // back to navBar case
        auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
        CHECK_NULL_VOID(navBarNode);
        navBarNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        navBarNode->SetActive(true);
        auto stageManager = context->GetStageManager();
        if (stageManager != nullptr) {
            RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
            CHECK_NULL_VOID(pageNode);
            auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
            if (pagePattern != nullptr) {
                auto pageInfo = pagePattern->GetPageInfo();
                NotifyPageShow(pageInfo->GetPageUrl());
            }
        }
        navBarNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
        auto focusHub = navBarNode->GetOrCreateFocusHub();
        focusHub->RequestFocus();
    }
    bool isShow = false;
    bool isDialog =
        (preTopNavDestination && preTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG) ||
        (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG);
    if (preTopNavDestination) {
        if (isDialog) {
            auto lastStandardIndex = hostNode->GetLastStandardIndex();
            isShow = (lastPreIndex != -1) && (lastPreIndex >= lastStandardIndex);
            hostNode->SetNeedSetInvisible(lastStandardIndex >= 0);
        }
        auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(preTopNavDestination->GetPattern());
        CHECK_NULL_VOID(navDestinationPattern);
        if (navDestinationPattern->GetIsOnShow() && !isShow) {
            auto eventHub = preTopNavDestination->GetEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            NotifyPageHide(preTopNavPath->first);
            eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
            navDestinationPattern->SetIsOnShow(false);
            // The navigations in NavDestination should be fired the hidden event
            NavigationPattern::FireNavigationStateChange(preTopNavDestination, false);
        }
    }
    bool disableAllAnimation = navigationStack_->GetDisableAnimation();
    bool animated = navigationStack_->GetAnimatedValue();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "transition start, disableAllAnimation: %{public}d, animated: %{public}d, isPopPage: %{public}d",
        disableAllAnimation, animated, isPopPage);
    if (isDialog) {
        // dialog navDestination no need transition animation.
        TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, isShow);
        hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return;
    }
    if (disableAllAnimation || !animated) {
        // transition without animation need to run before layout for geometryTransition.
        TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
        navigationStack_->UpdateAnimatedValue(true);
    } else {
        // before the animation of navDes replacing, update the zIndex of the previous navDes node
        UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination);
        // transition with animation need to run after layout task
        context->AddAfterLayoutTask(
            [preTopNavDestination, newTopNavDestination, isPopPage, weakNavigationPattern = WeakClaim(this)]() {
                auto navigationPattern = weakNavigationPattern.Upgrade();
                CHECK_NULL_VOID(navigationPattern);
                navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
            });
    }
    hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

int32_t NavigationPattern::FireNavDestinationStateChange(bool isShow)
{
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    auto errIndex = static_cast<int32_t>(navDestinationNodes.size());
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, errIndex);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, errIndex);
    int32_t standardIndex = hostNode->GetLastStandardIndex();
    auto id = GetHost()->GetId();
    for (int32_t index = static_cast<int32_t>(navDestinationNodes.size()) - 1; index >= 0 && index >= standardIndex;
         index--) {
        const auto& curPath = navDestinationNodes[index];
        auto curDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetNavDestinationNode(curPath.second));
        if (!curDestination) {
            continue;
        }
        auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_RETURN(navDestinationPattern, errIndex);
        if (navDestinationPattern->GetIsOnShow() == isShow) {
            continue;
        }
        auto eventHub = curDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_RETURN(eventHub, errIndex);
        if (isShow) {
            NotifyPageShow(curPath.first);
            auto param = Recorder::EventRecorder::Get().IsPageRecordEnable() ? navigationStack_->GetRouteParam() : "";
            eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
            navDestinationPattern->SetIsOnShow(true);
            // The change from hiding to showing of top page means the navigation return to screen,
            // so add window state callback again.
            pipeline->AddWindowStateChangedCallback(id);
        } else {
            NotifyPageHide(curPath.first);
            eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
            navDestinationPattern->SetIsOnShow(false);
            // The change from showing to hiding of top page means the navigation leaves from screen,
            // so remove window state callback.
            pipeline->RemoveWindowStateChangedCallback(id);
        }
    }
    return standardIndex;
}

void NavigationPattern::FireNavigationStateChange(const RefPtr<UINode>& node, bool show)
{
    CHECK_NULL_VOID(node);
    const auto& children = node->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;

        auto navigation = AceType::DynamicCast<NavigationGroupNode>(child);
        if (navigation) {
            auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigation->GetPattern());
            CHECK_NULL_VOID(navigationPattern);
            auto standardIndex = navigationPattern->FireNavDestinationStateChange(show);
            const auto& navDestinationNodes = navigationPattern->navigationStack_->GetAllNavDestinationNodes();
            if (standardIndex == static_cast<int32_t>(navDestinationNodes.size())) {
                NavigationPattern::FireNavigationStateChange(child, show);
                continue;
            }
            for (int32_t index = static_cast<int32_t>(navDestinationNodes.size()) - 1;
                 index >= 0 && index >= standardIndex; index--) {
                const auto& curPath = navDestinationNodes[index];
                // Ignore node from navigation to navdestination in node tree, start from navdestination node directly.
                NavigationPattern::FireNavigationStateChange(curPath.second, show);
            }
        } else {
            NavigationPattern::FireNavigationStateChange(child, show);
        }
    }
}

void NavigationPattern::NotifyPageHide(const std::string& pageName)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    pageUrlChecker->NotifyPageHide(pageName);
}

void NavigationPattern::NotifyPageShow(const std::string& pageName)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    pageUrlChecker->NotifyPageShow(pageName);
}

void NavigationPattern::TransitionWithOutAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool needVisible)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    // replace
    auto replaceVal = navigationStack_->GetReplaceValue();
    if (replaceVal != 0) {
        if (newTopNavDestination && preTopNavDestination) {
            navigationNode->DealNavigationExit(preTopNavDestination, false, false);
        } else if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
            navigationNode->DealNavigationExit(navBarNode, true, false);
        }
        navigationNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
        navigationStack_->UpdateReplaceValue(0);
        return;
    }

    // navDestination push/pop navDestination
    if (newTopNavDestination && preTopNavDestination) {
        if (isPopPage) {
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            if (preTopNavDestination->GetContentNode()) {
                preTopNavDestination->GetContentNode()->Clean(false, true);
            }
            parent->RemoveChild(preTopNavDestination, true);
            parent->RebuildRenderContextTree();
            pipeline->RequestFrame();
        } else {
            auto layoutProperty = preTopNavDestination->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateVisibility(needVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE, true);
        }
        navigationNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
        return;
    }

    // navBar push navDestination
    if (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::STANDARD &&
        navigationMode_ == NavigationMode::STACK) {
        auto layoutProperty = navBarNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    }

    // navDestination pop to navBar
    if (preTopNavDestination) {
        auto parent = preTopNavDestination->GetParent();
        CHECK_NULL_VOID(parent);
        if (preTopNavDestination->GetContentNode()) {
            preTopNavDestination->GetContentNode()->Clean(false, true);
        }
        parent->RemoveChild(preTopNavDestination, true);
        parent->RebuildRenderContextTree();
        pipeline->RequestFrame();
    }
    navigationNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
}

void NavigationPattern::TransitionWithAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetHideNavBarValue(false) && (!newTopNavDestination || !preTopNavDestination)) {
        // hide navBarNode and need to do animation with navBarNode
        if (preTopNavDestination) {
            // remove preTopNavDestination node in pop
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            if (preTopNavDestination->GetContentNode()) {
                preTopNavDestination->GetContentNode()->Clean();
            }
            parent->RemoveChild(preTopNavDestination);
            parent->RebuildRenderContextTree();
            pipeline->RequestFrame();
        }
        return;
    }
    if (isCustomAnimation_ && TriggerCustomAnimation(preTopNavDestination, newTopNavDestination, isPopPage)) {
        return;
    }

    // replace
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (replaceValue != 0) {
        if (newTopNavDestination && preTopNavDestination) {
            navigationNode->TransitionWithReplace(preTopNavDestination, newTopNavDestination, false);
        } else if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
            navigationNode->TransitionWithReplace(navBarNode, newTopNavDestination, true);
        }
        navigationStack_->UpdateReplaceValue(0);
        return;
    }

    // navDestination push/pop navDestination
    if (newTopNavDestination && preTopNavDestination) {
        if (isPopPage) {
            navigationNode->TransitionWithPop(preTopNavDestination, newTopNavDestination);
        } else {
            navigationNode->TransitionWithPush(preTopNavDestination, newTopNavDestination);
        }
        return;
    }

    // navBar push navDestination
    if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
        navigationNode->TransitionWithPush(navBarNode, newTopNavDestination, true);
        return;
    }

    // navDestination pop to navBar
    if (preTopNavDestination) {
        if (navigationMode_ == NavigationMode::SPLIT) {
            navigationNode->TransitionWithPop(preTopNavDestination, nullptr);
        }
        if (navigationMode_ == NavigationMode::STACK) {
            navigationNode->TransitionWithPop(preTopNavDestination, navBarNode, true);
        }
    }
}

void NavigationPattern::OnVisibleChange(bool isVisible)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireNavBarStateChangeEvent(isVisible);
}

void NavigationPattern::OnNavBarStateChange(bool modeChange)
{
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visibilityValue = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    if (visibilityValue != VisibleType::VISIBLE) {
        return;
    }

    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto currentNavigationMode = GetNavigationMode();

    if (modeChange) {
        if (currentNavigationMode == NavigationMode::SPLIT) {
            if (layoutProperty->GetHideNavBarValue(false)) {
                eventHub->FireNavBarStateChangeEvent(false);
            } else {
                eventHub->FireNavBarStateChangeEvent(true);
            }
        } else {
            if (navigationStack_->Empty() && !layoutProperty->GetHideNavBarValue(false)) {
                eventHub->FireNavBarStateChangeEvent(true);
            } else {
                eventHub->FireNavBarStateChangeEvent(false);
            }
        }
        SetNavBarVisibilityChange(false);
        return;
    }

    if (GetNavBarVisibilityChange()) {
        if (!layoutProperty->GetHideNavBarValue(false)) {
            eventHub->FireNavBarStateChangeEvent(true);
        } else {
            eventHub->FireNavBarStateChangeEvent(false);
        }
        SetNavBarVisibilityChange(false);
        return;
    }

    // STACK mode, check navigationStack
    if (navigationStack_->Empty()) {
        eventHub->FireNavBarStateChangeEvent(true);
    } else {
        eventHub->FireNavBarStateChangeEvent(false);
    }
}

void NavigationPattern::OnNavigationModeChange(bool modeChange)
{
    if (!modeChange) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireNavigationModeChangeEvent(navigationMode_);
}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto navigationLayoutAlgorithm =
        DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(navigationLayoutAlgorithm, false);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto oldMode = navigationMode_;
    navigationMode_ = navigationLayoutAlgorithm->GetNavigationMode();
    OnNavBarStateChange(oldMode != navigationMode_);
    OnNavigationModeChange(oldMode != navigationMode_);
    auto context = PipelineContext::GetCurrentContext();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this), navigationStackWeak = WeakPtr<NavigationStack>(navigationStack_),
                navigationWeak = WeakPtr<NavigationGroupNode>(hostNode)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto navigationGroupNode = navigationWeak.Upgrade();
                CHECK_NULL_VOID(navigationGroupNode);
                auto navigationLayoutProperty =
                    AceType::DynamicCast<NavigationLayoutProperty>(navigationGroupNode->GetLayoutProperty());
                CHECK_NULL_VOID(navigationLayoutProperty);
                auto navigationStack = navigationStackWeak.Upgrade();
                CHECK_NULL_VOID(navigationStack);
                auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetContentNode());
                CHECK_NULL_VOID(navigationContentNode);
                auto navDestinationNode =
                    AceType::DynamicCast<NavDestinationGroupNode>(navigationContentNode->GetLastChild());
                CHECK_NULL_VOID(navDestinationNode);
                auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
                auto curTopNavPath = navigationStack->GetTopNavPath();
                if (curTopNavPath.has_value()) {
                    // considering backButton visibility
                    auto curTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                        NavigationGroupNode::GetNavDestinationNode(curTopNavPath->second));
                    pattern->UpdateContextRect(curTopNavDestination, navigationGroupNode);
                    if (pattern->isChanged_ && curTopNavDestination) {
                        pattern->NotifyDialogChange(true, true);
                        pattern->isChanged_ = false;
                    }
                }
                // considering navBar visibility
                auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
                CHECK_NULL_VOID(navBarNode);
                auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
                CHECK_NULL_VOID(navBarLayoutProperty);
                bool isSetInvisible =
                    (navigationGroupNode->GetNeedSetInvisible() && navigationStack->Size() != 0) ? true : false;
                if (navigationLayoutProperty->GetHideNavBar().value_or(false) ||
                    (pattern->GetNavigationMode() == NavigationMode::STACK && isSetInvisible)) {
                    navBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
                    navBarNode->SetActive(false);
                } else {
                    navBarNode->GetRenderContext()->UpdateOpacity(1.0f);
                    navBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                    navBarNode->SetActive(true);
                }
                if (navDestinationNode->GetChildren().size() <= EMPTY_DESTINATION_CHILD_SIZE &&
                    navDestinationPattern->GetBackButtonState()) {
                    auto focusHub = navDestinationNode->GetOrCreateFocusHub();
                    focusHub->SetFocusable(true);
                    focusHub->SetParentFocusable(true);
                    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
                    CHECK_NULL_VOID(titleBarNode);
                    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
                    backButtonNode->GetOrCreateFocusHub()->SetIsDefaultFocus(true);
                    focusHub->RequestFocusWithDefaultFocusFirstly();
                }
            },
            TaskExecutor::TaskType::UI);
    }
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    CHECK_NULL_RETURN(navigationLayoutProperty, false);

    UpdateTitleModeChangeEventHub(hostNode);
    AddDividerHotZoneRect(navigationLayoutAlgorithm);
    ifNeedInit_ = false;
    return false;
}

void NavigationPattern::UpdateContextRect(
    const RefPtr<NavDestinationGroupNode>& curDestination, const RefPtr<NavigationGroupNode>& hostNode)
{
    CHECK_NULL_VOID(curDestination);
    CHECK_NULL_VOID(hostNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);

    if (navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        curDestination->GetRenderContext()->SetActualForegroundColor(DEFAULT_MASK_COLOR);
        return;
    }
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    navBarProperty->UpdateVisibility(navigationLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE));
    navBarNode->SetActive(navigationLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE);
    if (!curDestination->IsOnAnimation()) {
        curDestination->GetRenderContext()->UpdateTranslateInXY(OffsetF { 0.0f, 0.0f });
        curDestination->GetRenderContext()->SetActualForegroundColor(DEFAULT_MASK_COLOR);
        navBarNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
        auto titleNode = AceType::DynamicCast<FrameNode>(navBarNode->GetTitle());
        CHECK_NULL_VOID(titleNode);
        titleNode->GetRenderContext()->UpdateTranslateInXY(OffsetF { 0.0f, 0.0f });
    }
}

bool NavigationPattern::UpdateTitleModeChangeEventHub(const RefPtr<NavigationGroupNode>& hostNode)
{
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, false);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, false);
    auto eventHub = hostNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
        auto titleBarPattern = AceType::DynamicCast<TitleBarPattern>(titleBarNode->GetPattern());
        CHECK_NULL_RETURN(titleBarPattern, false);
        NavigationTitleMode titleMode = titleBarPattern->GetNavigationTitleMode();
        if (titleMode != NavigationTitleMode::FREE && titleMode_ != titleMode) {
            NavigationTitleModeChangeEvent navigationTitleModeChange(titleMode == NavigationTitleMode::MINI);
            eventHub->FireChangeEvent(&navigationTitleModeChange);
            titleMode_ = titleMode;
        }
    }
    return true;
}

RefPtr<UINode> NavigationPattern::GenerateUINodeByIndex(int32_t index)
{
    return navigationStack_->CreateNodeByIndex(index);
}

void NavigationPattern::InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(inputHub);
    CHECK_NULL_VOID(!hoverEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void NavigationPattern::HandleDragStart()
{
    preNavBarWidth_ = realNavBarWidth_;
}

void NavigationPattern::HandleDragUpdate(float xOffset)
{
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameWidth = frameSize.Width();
    auto constraint = navigationLayoutProperty->GetLayoutConstraint();
    auto parentSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);

    float minNavBarWidthPx = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    float maxNavBarWidthPx = maxNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    float minContentWidthPx = minContentWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());

    auto navigationPosition = navigationLayoutProperty->GetNavBarPosition().value_or(NavBarPosition::START);
    bool isNavBarStart = navigationPosition == NavBarPosition::START;
    auto navBarLine = preNavBarWidth_ + (isNavBarStart ? xOffset : -xOffset);
    float currentNavBarWidth = realNavBarWidth_;

    if (maxNavBarWidthPx + dividerWidth + minContentWidthPx > frameWidth) {
        maxNavBarWidthPx = frameWidth - minContentWidthPx - dividerWidth;
    }
    navBarLine = std::min(navBarLine, maxNavBarWidthPx);

    if (userSetMinContentFlag_ && !userSetNavBarRangeFlag_) {
        if (minContentWidthPx >= frameWidth) {
            realNavBarWidth_ = 0.0f;
        } else if (navBarLine + dividerWidth + minContentWidthPx <= frameWidth) {
            realNavBarWidth_ = navBarLine;
        } else {
            realNavBarWidth_ = frameWidth - minContentWidthPx - dividerWidth;
        }
    } else {
        realDividerWidth_ = dividerWidth;
        float remainingSpace = frameWidth - navBarLine - dividerWidth;
        if (remainingSpace >= minContentWidthPx) {
            realNavBarWidth_ = navBarLine;
        } else if (remainingSpace < minContentWidthPx && navBarLine > minNavBarWidthPx) {
            realNavBarWidth_ = frameWidth - minContentWidthPx - dividerWidth;
        } else {
            realNavBarWidth_ = minNavBarWidthPx;
        }
    }
    realNavBarWidth_ = std::min(realNavBarWidth_, frameWidth);
    realNavBarWidth_ = std::min(realNavBarWidth_, maxNavBarWidthPx);
    realNavBarWidth_ = std::max(realNavBarWidth_, minNavBarWidthPx);

    // MEASURE
    if (realNavBarWidth_ != currentNavBarWidth) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

void NavigationPattern::HandleDragEnd()
{
    preNavBarWidth_ = realNavBarWidth_;
}

void NavigationPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!dragEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    dragEvent_ = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    gestureHub->SetDragEvent(dragEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void NavigationPattern::OnHover(bool isHover)
{
    MouseFormat format = isHover ? MouseFormat::RESIZE_LEFT_RIGHT : MouseFormat::DEFAULT;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t currentPointerStyle = 0;
    mouseStyle->GetPointerStyle(windowId, currentPointerStyle);
    auto defaultValue = Dimension(0.0);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto userSetMinNavBarWidthValue = layoutProperty->GetMinNavBarWidthValue(defaultValue);
    auto userSetMaxNavBarWidthValue = layoutProperty->GetMaxNavBarWidthValue(defaultValue);
    if (userSetNavBarRangeFlag_ && userSetMinNavBarWidthValue == userSetMaxNavBarWidthValue) {
        return;
    }
    if (currentPointerStyle != static_cast<int32_t>(format)) {
        mouseStyle->SetPointerStyle(windowId, format);
    }
}

RefPtr<FrameNode> NavigationPattern::GetDividerNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    CHECK_NULL_RETURN(dividerFrameNode, nullptr);
    return dividerFrameNode;
}

void NavigationPattern::AddDividerHotZoneRect(const RefPtr<NavigationLayoutAlgorithm>& layoutAlgorithm)
{
    CHECK_NULL_VOID(layoutAlgorithm);
    if (realDividerWidth_ <= 0.0f) {
        return;
    }
    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(-DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneOffset.SetY(DEFAULT_DIVIDER_START_MARGIN.ConvertToPx());
    SizeF hotZoneSize;
    hotZoneSize.SetWidth(realDividerWidth_ + DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM *
                                                 DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneSize.SetHeight(layoutAlgorithm->GetRealNavBarHeight());
    DimensionRect hotZoneRegion;
    if (navigationMode_ == NavigationMode::STACK) {
        hotZoneRegion.SetSize(DimensionSize(Dimension(0.0f), Dimension(0.0f)));
    } else {
        hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize.Width()), Dimension(hotZoneSize.Height())));
    }
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));

    std::vector<DimensionRect> mouseRegion;
    mouseRegion.emplace_back(hotZoneRegion);

    auto dividerFrameNode = GetDividerNode();
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerGestureHub = dividerFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    dividerGestureHub->SetMouseResponseRegion(mouseRegion);

    auto dragRectOffset = layoutAlgorithm->GetNavBarOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_REGION.ConvertToPx());
    dragRect_.SetOffset(dragRectOffset);
    if (navigationMode_ == NavigationMode::STACK) {
        dragRect_.SetSize(SizeF(0.0f, 0.0f));
    } else {
        dragRect_.SetSize(SizeF(DEFAULT_DRAG_REGION.ConvertToPx() * DEFAULT_HALF + realDividerWidth_,
            layoutAlgorithm->GetRealNavBarHeight()));
    }

    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragRect_.Width(), DimensionUnit::PX),
        Dimension(dragRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dividerGestureHub->MarkResponseRegion(true);
    dividerGestureHub->SetResponseRegion(responseRegion);
}

void NavigationPattern::OnWindowHide()
{
    auto curTopNavPath = navigationStack_->GetTopNavPath();
    CHECK_NULL_VOID(curTopNavPath.has_value());
    CHECK_NULL_VOID(curTopNavPath->second);
    auto curTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(curTopNavPath->second));
    CHECK_NULL_VOID(curTopNavDestination);
    auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(curTopNavDestination->GetPattern());
    CHECK_NULL_VOID(navDestinationPattern);
    CHECK_NULL_VOID(navDestinationPattern->GetIsOnShow());
    auto eventHub = curTopNavDestination->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    NotifyPageHide(curTopNavPath->first);
    NotifyDialogChange(false, true);
}

void NavigationPattern::OnWindowShow()
{
    auto curTopNavPath = navigationStack_->GetTopNavPath();
    CHECK_NULL_VOID(curTopNavPath.has_value());
    CHECK_NULL_VOID(curTopNavPath->second);
    auto curTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(curTopNavPath->second));
    CHECK_NULL_VOID(curTopNavDestination);
    auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(curTopNavDestination->GetPattern());
    CHECK_NULL_VOID(navDestinationPattern);
    CHECK_NULL_VOID(!(navDestinationPattern->GetIsOnShow()));
    auto eventHub = curTopNavDestination->GetEventHub<NavDestinationEventHub>();
    NotifyPageShow(curTopNavPath->first);
    NotifyDialogChange(true, true);
}

void NavigationPattern::NotifyDialogChange(bool isShow, bool isNavigationChanged)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    int32_t standardIndex = hostNode->GetLastStandardIndex();
    for (int32_t index = static_cast<int32_t>(navDestinationNodes.size()) - 1; index >= 0 && index >= standardIndex;
         index--) {
        const auto& curPath = navDestinationNodes[index];
        auto curDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetNavDestinationNode(curPath.second));
        if (!curDestination) {
            continue;
        }
        auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        if (navDestinationPattern->GetIsOnShow() == isShow) {
            continue;
        }
        auto eventHub = curDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        if (isShow) {
            if (isNavigationChanged) {
                NavigationPattern::FireNavigationStateChange(curDestination, true);
            }
            auto param = Recorder::EventRecorder::Get().IsPageRecordEnable() ? navigationStack_->GetRouteParam() : "";
            eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
        } else {
            if (isNavigationChanged) {
                NavigationPattern::FireNavigationStateChange(curDestination, false);
            }
            eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
        }
        navDestinationPattern->SetIsOnShow(isShow);
    }
}

void NavigationPattern::DumpInfo()
{
    if (!navigationStack_) {
        return;
    }
    DumpLog::GetInstance().AddDesc(std::string("size").append(std::to_string(navigationStack_->Size())));
}

bool NavigationPattern::TriggerCustomAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    if ((!preTopNavDestination && !newTopNavDestination) || !onTransition_) {
        return false;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    hostNode->SetIsOnAnimation(true);
    if (!newTopNavDestination) {
        // pop animation with top navDestination, recover navBar visible tag
        hostNode->SetNeedSetInvisible(false);
    }
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    proxy->SetPreDestination(preTopNavDestination);
    proxy->SetTopDestination(newTopNavDestination);
    proxy->SetIsSuccess(true);
    currentProxy_ = proxy;
    auto navigationTransition = ExecuteTransition(preTopNavDestination, newTopNavDestination, isPopPage);
    if (!navigationTransition.isValid) {
        return false;
    }
    auto transition = navigationTransition.transition;
    proxy->SetFinishTransitionEvent([weakPattern = WeakClaim(this), preTopNavDestination, newTopNavDestination,
                                    proxy, isPopPage, endCallBack = navigationTransition.endCallback](bool isSuccess) {
        auto navigationPattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(navigationPattern);
        if (proxy != nullptr && proxy->GetIsFinished()) {
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "custom animation has finished");
            return;
        }
        if (endCallBack) {
            // current transition end doesn't has failed
            endCallBack(isSuccess);
        }
        navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
        if (proxy != nullptr) {
            proxy->SetIsFinished(true);
        }
    });
    transition(proxy);
    auto timeout = navigationTransition.timeout;
    // post timeout task
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, true);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, true);
    taskExecutor->PostDelayedTask(
        [weakProxy = WeakPtr<NavigationTransitionProxy>(proxy)] {
            auto transitionProxy = weakProxy.Upgrade();
            CHECK_NULL_VOID(transitionProxy);
            transitionProxy->FireFinishCallback();
        },
        TaskExecutor::TaskType::UI, timeout);
    RefPtr<EventHub> eventHub;
    if (!preTopNavDestination && navigationMode_ == NavigationMode::STACK) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_RETURN(hostNode, true);
        auto navBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarNode());
        CHECK_NULL_RETURN(navBarNode, true);
        eventHub = navBarNode->GetEventHub<EventHub>();
    }
    if (preTopNavDestination) {
        eventHub = preTopNavDestination->GetEventHub<EventHub>();
    }
    CHECK_NULL_RETURN(eventHub, true);
    eventHub->SetEnabledInternal(false);
    return true;
}

void NavigationPattern::OnCustomAnimationFinish(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    if (!preTopNavDestination && !newTopNavDestination) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "preDestination and topDestination is invalid");
        return;
    }
    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
    auto replaceValue = navigationStack_->GetReplaceValue();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    hostNode->SetIsOnAnimation(false);
    hostNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
    do {
        if (replaceValue != 0) {
            hostNode->DealNavigationExit(preTopNavDestination, preTopNavDestination == nullptr);
            navigationStack_->UpdateReplaceValue(0);
            break;
        }
        if ((newTopNavDestination && preTopNavDestination && isPopPage) ||
            (preTopNavDestination && !newTopNavDestination && navigationMode_ == NavigationMode::STACK)) {
            PageTransitionType preNodeTransitionType = preTopNavDestination->GetTransitionType();
            if (preNodeTransitionType != PageTransitionType::EXIT_POP) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "previous destination node is executing another transition");
                return;
            }
            auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(preDestinationPattern);
            auto shallowBuilder = preDestinationPattern->GetShallowBuilder();
            if (shallowBuilder) {
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            }
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            parent->RemoveChild(preTopNavDestination);
            parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            break;
        }
        if ((newTopNavDestination && preTopNavDestination && !isPopPage) ||
            (!preTopNavDestination && newTopNavDestination && navigationMode_ == NavigationMode::STACK)) {
            hostNode->SetNeedSetInvisible(true);
            RefPtr<FrameNode> node;
            PageTransitionType preNodeTransitionType;
            if (preTopNavDestination) {
                preNodeTransitionType = preTopNavDestination->GetTransitionType();
                node = preTopNavDestination;
            } else {
                // pre destination is nullptr, preNode is navBarNode
                auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
                CHECK_NULL_VOID(navBarNode);
                preNodeTransitionType = navBarNode->GetTransitionType();
                node = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarNode());
                CHECK_NULL_VOID(node);
            }
            if (preNodeTransitionType != PageTransitionType::EXIT_PUSH) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "previous destination node is executing another transition");
                return;
            }
            auto property = node->GetLayoutProperty();
            property->UpdateVisibility(VisibleType::INVISIBLE);
            node->SetActive(false);
            if (!preTopNavDestination) {
                hostNode->NotifyPageHide();
            }
            // recover event hub
            auto eventHub = node->GetEventHub<EventHub>();
            if (eventHub) {
                eventHub->SetEnabledInternal(true);
            }
        }
    } while (0);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushMouseEvent();
}

NavigationTransition NavigationPattern::ExecuteTransition(const RefPtr<NavDestinationGroupNode>& preTopDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    NavigationTransition navigationTransition;
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, navigationTransition);
    NavigationOperation operation;
    NavContentInfo preInfo = currentProxy_->GetPreDestination();
    NavContentInfo topInfo = currentProxy_->GetTopDestination();
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (replaceValue != 0) {
        operation = NavigationOperation::REPLACE;
        // recover replace tag
        navigationStack_->UpdateReplaceValue(0);
    } else if (!preTopDestination) {
        preInfo.index = -1;
        operation = NavigationOperation::PUSH;
        // if animated with navBarNode, recover navBar visibility
        hostNode->SetNeedSetInvisible(false);
    } else if (!newTopNavDestination) {
        operation = NavigationOperation::POP;
    } else if (isPopPage) {
        operation = NavigationOperation::POP;
    } else {
        operation = NavigationOperation::PUSH;
    }

    /* set transition animation flag fro navBarNode or navDestinationNode */
    if (operation == NavigationOperation::PUSH) {
        if (preTopDestination != nullptr) {
            preTopDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
        } else {
            // preTopDestination is nullptr, previous node is navBar node
            auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
            CHECK_NULL_RETURN(navBarNode, navigationTransition);
            navBarNode->SetTransitionType(PageTransitionType::EXIT_PUSH);
        }

        if (newTopNavDestination != nullptr) {
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
        }
    }
    if (operation == NavigationOperation::POP) {
        if (preTopDestination != nullptr) {
            preTopDestination->SetTransitionType(PageTransitionType::EXIT_POP);
        }
        if (newTopNavDestination != nullptr) {
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_POP);
        } else {
            // newTopNavDestination is nullptr, current node is navBar node
            auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
            CHECK_NULL_RETURN(navBarNode, navigationTransition);
            navBarNode->SetTransitionType(PageTransitionType::ENTER_POP);
        }
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "custom animation start: operation: %{public}d", operation);
    return onTransition_(preInfo, topInfo, operation);
}

void NavigationPattern::OnColorConfigurationUpdate()
{
    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    dividerNode->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
}

void NavigationPattern::UpdatePreNavDesZIndex(const RefPtr<FrameNode> &preTopNavDestination,
    const RefPtr<FrameNode> &newTopNavDestination)
{
    auto replaceVal = navigationStack_->GetReplaceValue();
    if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        auto navigationContentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_VOID(navigationContentNode);
        auto newDesNodeContext = newTopNavDestination->GetRenderContext();
        CHECK_NULL_VOID(newDesNodeContext);
        std::optional<int32_t> newNodeZIndex = newDesNodeContext->GetZIndex();
        auto preDesNodeContext = preTopNavDestination->GetRenderContext();
        CHECK_NULL_VOID(preDesNodeContext);
        preDesNodeContext->UpdateZIndex(newNodeZIndex.value_or(0) - 1);
        navigationContentNode->RebuildRenderContextTree();
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->RequestFrame();
    }
}
} // namespace OHOS::Ace::NG
