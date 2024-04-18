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

#include "base/geometry/dimension.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/common/container.h"
#include "core/common/manager_interface.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {

constexpr int32_t NAVIMODE_CHANGE_ANIMATION_DURATION = 250;
constexpr int32_t OPACITY_ANIMATION_DURATION_APPEAR = 150;
constexpr int32_t OPACITY_ANIMATION_DURATION_DISAPPEAR = 250;
constexpr int32_t EMPTY_DESTINATION_CHILD_SIZE = 1;
constexpr Dimension DEFAULT_DRAG_REGION = 12.0_vp;
constexpr float DEFAULT_HALF = 2.0f;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
constexpr int32_t PAGE_NODES = 1000;
constexpr int32_t PAGE_DEPTH = 300;
namespace {
constexpr static int32_t PLATFORM_VERSION_TEN = 10;

void BuildNavDestinationInfoFromContext(const std::string& navigationId, NavDestinationState state,
    const RefPtr<NavDestinationContext>& context, bool isFrom, std::optional<NavDestinationInfo>& info)
{
    if (!context) {
        info.reset();
        return;
    }

    int32_t index = isFrom ? context->GetPreIndex() : context->GetIndex();
    std::string navDestinationId = std::to_string(context->GetNavDestinationId());
    std::string name;
    napi_value param = nullptr;
    auto pathInfo = context->GetNavPathInfo();
    if (pathInfo) {
        name = pathInfo->GetName();
        param = pathInfo->GetParamObj();
    }
    info = std::make_optional<NavDestinationInfo>(navigationId, name, state, index, param, navDestinationId);
}
} // namespace

NavigationPattern::NavigationPattern()
{
    navigationController_ = std::make_shared<InnerNavigationController>(WeakClaim(this), Container::CurrentId());
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

    auto theme = NavigationGetTheme();
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        pipelineContext->AddWindowFocusChangedCallback(host->GetId());
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = {.type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL};
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
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
    // !!! Do not add operations about NavPathStack here, see @SyncWithJsStackIfNeeded
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    navBarNode->MarkModifyDone();

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

    auto layoutProperty = hostNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto&& opts = layoutProperty->GetSafeAreaExpandOpts();
    if (opts && opts->Expansive()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Navigation SafArea expand as %{public}s", opts->ToString().c_str());

        navBarNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        navBarNode->MarkModifyDone();

        auto navigationContentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_VOID(navigationContentNode);
        navigationContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        navigationContentNode->MarkModifyDone();

        auto dividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetDividerNode());
        CHECK_NULL_VOID(dividerNode);
        dividerNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        dividerNode->MarkModifyDone();
    }
}

void NavigationPattern::SyncWithJsStackIfNeeded()
{
    if (!needSyncWithJsStack_) {
        return;
    }
    CHECK_NULL_VOID(navigationStack_);
    needSyncWithJsStack_ = false;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "sync with js stack");
    preTopNavPath_ = navigationStack_->GetPreTopNavPath();
    preStackSize_ = navigationStack_->PreSize();
    preContext_ = nullptr;
    if (preTopNavPath_.has_value()) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath_->second));
        if (preDestination) {
            auto pattern = AceType::DynamicCast<NavDestinationPattern>(preDestination->GetPattern());
            preContext_ = pattern->GetNavDestinationContext();
            if (preContext_) {
                preContext_->SetPreIndex(preStackSize_ - 1);
            }
        }
    }
    UpdateNavPathList();
    auto newTopNavPath = navigationStack_->GetTopNavPath();
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (preTopNavPath_ != newTopNavPath || replaceValue == 1) {
        isReplace_ = replaceValue != 0;
        UpdateIsAnimation(preTopNavPath_);
        lastPreIndex_ = 0;
        if (preTopNavPath_.has_value()) {
            lastPreIndex_ = navigationStack_->FindIndex(preTopNavPath_->first,
            preTopNavPath_->second, true);
        }
        FireInterceptionEvent(true, newTopNavPath);
        if (needSyncWithJsStack_) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "sync with js stack in before interception");
            UpdateNavPathList();
            needSyncWithJsStack_ = false;
        }
    }
    RefreshNavDestination();
}

void NavigationPattern::UpdateNavPathList()
{
    CHECK_NULL_VOID(navigationStack_);
    auto pathNames = navigationStack_->GetAllPathName();
    auto indexes = navigationStack_->GetAllPathIndex();
    auto cacheNodes = navigationStack_->GetAllCacheNodes();
    NavPathList navPathList;
    for (size_t i = 0; i < pathNames.size(); ++i) {
        auto pathName = pathNames[i];
        auto index = static_cast<int32_t>(indexes[i]);
        RefPtr<UINode> uiNode = nullptr;
        if ((i == (navigationStack_->Size() - 1)) && addByNavRouter_) {
            addByNavRouter_ = false;
            uiNode = navigationStack_->Get();
        } else {
            uiNode = navigationStack_->Get(index);
        }
        if (uiNode) {
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "find in list, navigation stack reserve node, "
                "old index: %{public}d, index: %{public}d, name: %{public}s.",
                index, static_cast<int32_t>(i), pathName.c_str());
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            continue;
        }
        uiNode = navigationStack_->GetFromCacheNode(cacheNodes, pathName);
        if (uiNode) {
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "find in cached node, navigation stack reserve node, "
                "index: %{public}d, name: %{public}s.", static_cast<int32_t>(i), pathName.c_str());
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            navigationStack_->RemoveCacheNode(cacheNodes, pathName, uiNode);
            continue;
        }
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "find in nowhere, navigation stack create new node, "
            "index: %{public}d, name: %{public}s.", static_cast<int32_t>(i), pathName.c_str());
        uiNode = GenerateUINodeByIndex(static_cast<int32_t>(i));
        navPathList.emplace_back(std::make_pair(pathName, uiNode));
    }
    navigationStack_->ClearPreBuildNodeList();
    navigationStack_->SetNavPathList(navPathList);
    navigationStack_->InitNavPathIndex(pathNames);
}

void NavigationPattern::RefreshNavDestination()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto preTopNavPath = std::move(preTopNavPath_);
    auto& navPathList = navigationStack_->GetAllNavDestinationNodes();
    hostNode->UpdateNavDestinationNodeWithoutMarkDirty(
        preTopNavPath.has_value() ? preTopNavPath->second : nullptr, navigationModeChange_);
    auto newTopNavPath = navigationStack_->GetTopNavPath();
    std::string navDestinationName = "";
    CheckTopNavPathChange(preTopNavPath, newTopNavPath);

    /* if first navDestination is removed, the new one will be refreshed */
    if (!navPathList.empty()) {
        auto firstNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(navPathList.front().second));
        CHECK_NULL_VOID(firstNavDesNode);
        firstNavDesNode->MarkModifyDone();
    }

    if (newTopNavPath.has_value()) {
        navDestinationName = newTopNavPath->first;
    }
    pipeline->AddPredictTask([weak = WeakClaim(this), weakNode = WeakPtr<FrameNode>(hostNode),
        navDestinationName](int64_t deadline, bool canUseLongPredictTask) {
            auto navigationPattern = weak.Upgrade();
            CHECK_NULL_VOID(navigationPattern);
            auto navigationNode = weakNode.Upgrade();
            CHECK_NULL_VOID(navigationNode);
            int32_t count = 0;
            int32_t depth = 0;
            navigationNode->GetPageNodeCountAndDepth(&count, &depth);
            navigationPattern->PerformanceEventReport(count, depth, navDestinationName);
        });
}

void NavigationPattern::CheckTopNavPathChange(
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath)
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
#if defined(ENABLE_STANDARD_INPUT)
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textfieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textfieldManager) {
        textfieldManager->ProcessNavKeyboard();
    }
#endif

    isChanged_ = true;
    UpdateIsAnimation(preTopNavPath);
    isReplace_ = replaceValue != 0;
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
    bool isPopPage = false;
    if (preTopNavPath.has_value()) {
        // pre page is not in the current stack
        lastPreIndex = navigationStack_->FindIndex(preTopNavPath->first, preTopNavPath->second, true);
        isPopPage |= lastPreIndex == -1;
        preTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath->second));
    }
    RefPtr<NavDestinationGroupNode> newTopNavDestination;
    if (newTopNavPath.has_value()) {
        newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second));
        if (newTopNavDestination) {
            auto navDestinationPattern = newTopNavDestination->GetPattern<NavDestinationPattern>();
            auto navDestinationFocusView = AceType::DynamicCast<FocusView>(navDestinationPattern);
            CHECK_NULL_VOID(navDestinationFocusView);
            navDestinationFocusView->SetIsViewRootScopeFocused(false);
            navDestinationFocusView->FocusViewShow();
        } else {
            // back to navBar case
            auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
            CHECK_NULL_VOID(navBarNode);
            auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(
                hostNode->GetLayoutProperty());
            if (!navigationLayoutProperty->GetHideNavBarValue(false)) {
                navBarNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
                navBarNode->SetJSViewActive(true);
            }
            auto stageManager = context->GetStageManager();
            if (stageManager != nullptr) {
                RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
                CHECK_NULL_VOID(pageNode);
                auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
                CHECK_NULL_VOID(pagePattern);
                auto pageInfo = pagePattern->GetPageInfo();
                NotifyPageShow(pageInfo->GetPageUrl());
            }
            navBarNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
            auto navBarFocusView = navBarNode->GetPattern<FocusView>();
            CHECK_NULL_VOID(navBarFocusView);
            navBarFocusView->SetIsViewRootScopeFocused(false);
            navBarFocusView->FocusViewShow();
        }
    }
    bool isShow = false;
    bool isDialog =
        (preTopNavDestination && preTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG) ||
        (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG);
    if (preTopNavDestination && isDialog) {
        auto lastStandardIndex = hostNode->GetLastStandardIndex();
        isShow = (lastPreIndex != -1) && (lastPreIndex >= lastStandardIndex);
        hostNode->SetNeedSetInvisible(lastStandardIndex >= 0);
        if (lastStandardIndex < 0) {
            auto navBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarNode());
            auto layoutProperty = navBarNode->GetLayoutProperty();
            layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
            navBarNode->SetJSViewActive(true);
        }
    }
    bool disableAllAnimation = navigationStack_->GetDisableAnimation();
    bool animated = navigationStack_->GetAnimatedValue();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "transition start, disableAllAnimation: %{public}d, animated: %{public}d, isPopPage: %{public}d",
        disableAllAnimation, animated, isPopPage);
    if (isDialog && !isCustomAnimation_) {
        // dialog navDestination no need transition animation.
        StartTransition(preTopNavDestination, newTopNavDestination, false, isPopPage, isShow);
        hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return;
    }
    if (disableAllAnimation || !animated) {
        // transition without animation need to run before layout for geometryTransition.
        StartTransition(preTopNavDestination, newTopNavDestination, false, isPopPage);
        navigationStack_->UpdateAnimatedValue(true);
    } else {
        // before the animation of navDes replacing, update the zIndex of the previous navDes node
        UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination);
        // transition with animation need to run after layout task
        StartTransition(preTopNavDestination, newTopNavDestination, true, isPopPage);
    }
    hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

int32_t NavigationPattern::FireNavDestinationStateChange(NavDestinationLifecycle lifecycle)
{
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    auto errIndex = static_cast<int32_t>(navDestinationNodes.size());
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, errIndex);
    NotifyDialogChange(lifecycle, false, true);
    return hostNode->GetLastStandardIndex();
}

void NavigationPattern::FireNavigationStateChange(const RefPtr<UINode>& node, bool isShow)
{
    if (isShow) {
        NavigationPattern::FireNavigationLifecycleChange(node, NavDestinationLifecycle::ON_SHOW);
        return;
    }
    NavigationPattern::FireNavigationLifecycleChange(node, NavDestinationLifecycle::ON_HIDE);
}

void NavigationPattern::FireNavigationInner(const RefPtr<UINode>& node, bool isOnShow)
{
    CHECK_NULL_VOID(node);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(node);
    if (!navigationNode) {
        NavigationPattern::FireNavigationChange(node, isOnShow, false);
        return;
    }
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    CHECK_NULL_VOID(navigationPattern->navigationStack_);
    const auto& navDestinationNodes = navigationPattern->navigationStack_->GetAllNavDestinationNodes();
    auto lastStandardIndex = navigationNode->GetLastStandardIndex();
    int32_t standardIndex = lastStandardIndex >= 0 ? lastStandardIndex : 0;
    int32_t start = standardIndex;
    int32_t end = navigationPattern->navigationStack_->Size();
    if (isOnShow) {
        for (int32_t index = start; index < end; index++) {
            const auto& curPath = navDestinationNodes[index];
            auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                navigationNode->GetNavDestinationNode(curPath.second));
            if (!curDestination || !curDestination->GetLayoutProperty()) {
                continue;
            }
            auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto property = curDestination->GetLayoutProperty();
            if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
                !curDestination->IsActive() || navDestinationPattern->GetIsOnShow() == isOnShow) {
                continue;
            }
            auto eventHub = curDestination->GetEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            auto param = Recorder::EventRecorder::Get().IsPageRecordEnable() ?
            navigationPattern->navigationStack_->GetRouteParam() : "";
            eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
            navDestinationPattern->SetIsOnShow(true);
            NavigationPattern::FireNavigationChange(curDestination, true, false);
        }
        return;
    }
    navigationPattern->SyncWithJsStackIfNeeded();
    for (int32_t index = end - 1; index >= 0 && index >= start; index--) {
        const auto& curPath = navDestinationNodes[index];
        auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationNode->GetNavDestinationNode(curPath.second));
        if (!curDestination || !curDestination->GetLayoutProperty()) {
            continue;
        }
        auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto property = curDestination->GetLayoutProperty();
        if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
            !curDestination->IsActive() || navDestinationPattern->GetIsOnShow() == isOnShow) {
            continue;
        }
        auto eventHub = curDestination->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
        navDestinationPattern->SetIsOnShow(false);
        NavigationPattern::FireNavigationChange(curDestination, false, false);
    }
}

void NavigationPattern::FireNavigationChange(const RefPtr<UINode>& node, bool isOnShow, bool isFirst)
{
    CHECK_NULL_VOID(node);
    if (isFirst) {
        FireNavigationInner(node, isOnShow);
        return;
    }
    const auto& children = node->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        FireNavigationInner(child, isOnShow);
    }
}

void NavigationPattern::FireNavigationLifecycleChange(const RefPtr<UINode>& node, NavDestinationLifecycle lifecycle)
{
    CHECK_NULL_VOID(node);
    const auto& children = node->GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto navigation = AceType::DynamicCast<NavigationGroupNode>(child);
        if (navigation) {
            auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigation->GetPattern());
            CHECK_NULL_VOID(navigationPattern);
            auto standardIndex = navigationPattern->FireNavDestinationStateChange(lifecycle);
            const auto& navDestinationNodes = navigationPattern->navigationStack_->GetAllNavDestinationNodes();
            if (standardIndex == static_cast<int32_t>(navDestinationNodes.size())) {
                NavigationPattern::FireNavigationLifecycleChange(child, lifecycle);
                continue;
            }
            for (int32_t index = static_cast<int32_t>(navDestinationNodes.size()) - 1;
                 index >= 0 && index >= standardIndex; index--) {
                const auto& curPath = navDestinationNodes[index];
                // Ignore node from navigation to navdestination in node tree, start from navdestination node directly.
                NavigationPattern::FireNavigationLifecycleChange(curPath.second, lifecycle);
            }
        } else {
            NavigationPattern::FireNavigationLifecycleChange(child, lifecycle);
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
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_POP);
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            if (preTopNavDestination->GetContentNode()) {
                preTopNavDestination->GetContentNode()->Clean(false, true);
            }
            parent->RemoveChild(preTopNavDestination, true);
            auto preTopNavDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(preTopNavDestinationPattern);
            preTopNavDestinationPattern->SetCustomNode(nullptr);
            parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            preTopNavDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
            DealTransitionVisibility(preTopNavDestination, needVisible, false);
        }
        navigationNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CHANGE);
        return;
    }

    // navBar push navDestination
    if (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::STANDARD &&
        navigationMode_ == NavigationMode::STACK) {
        auto navBar = AceType::DynamicCast<NavBarNode>(navBarNode);
        if (navBar) {
            navBar->SetTransitionType(PageTransitionType::EXIT_PUSH);
        }
        newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
        DealTransitionVisibility(navBarNode, false, true);
        navigationNode->SetNeedSetInvisible(true);
    }

    // navDestination pop to navBar
    if (preTopNavDestination) {
        auto parent = preTopNavDestination->GetParent();
        CHECK_NULL_VOID(parent);
        if (preTopNavDestination->GetContentNode()) {
            preTopNavDestination->GetContentNode()->Clean(false, true);
        }
        parent->RemoveChild(preTopNavDestination, true);
        auto preTopNavDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(preTopNavDestinationPattern);
        preTopNavDestinationPattern->SetCustomNode(nullptr);
        navigationNode->SetNeedSetInvisible(false);
        auto navBar = AceType::DynamicCast<NavBarNode>(navBarNode);
        if (navBar) {
            navBar->SetTransitionType(PageTransitionType::ENTER_POP);
        }
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
            auto preTopNavDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(preTopNavDestinationPattern);
            preTopNavDestinationPattern->SetCustomNode(nullptr);
            parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    // fire navigation stack navigation mode change event
    navigationStack_->FireNavigationModeChange(navigationMode_);
}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    if (navigationModeChange_) {
        if (NavigationMode::STACK == navigationMode_) {
            auto newTopNavPath = navigationStack_->GetTopNavPath();
            if (newTopNavPath.has_value()) {
                auto newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                    NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second));
                CHECK_NULL_RETURN(newTopNavDestination, false);
                auto navDestinationFocusView = newTopNavDestination->GetPattern<FocusView>();
                CHECK_NULL_RETURN(navDestinationFocusView, false);
                navDestinationFocusView->SetIsViewRootScopeFocused(false);
                navDestinationFocusView->FocusViewShow();
            }
        }
        AbortAnimation(hostNode);
    }
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
                auto curTopNavPath = navigationStack->GetTopNavPath();
                if (curTopNavPath.has_value()) {
                    // considering backButton visibility
                    auto curTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                        NavigationGroupNode::GetNavDestinationNode(curTopNavPath->second));
                    pattern->UpdateContextRect(curTopNavDestination, navigationGroupNode);
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
                    navBarNode->SetJSViewActive(false);
                } else {
                    navBarNode->GetRenderContext()->UpdateOpacity(1.0f);
                    navBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                    navBarNode->SetJSViewActive(true);
                }
                auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetContentNode());
                CHECK_NULL_VOID(navigationContentNode);
                auto navDestinationNode =
                    AceType::DynamicCast<NavDestinationGroupNode>(navigationContentNode->GetLastChild());
                CHECK_NULL_VOID(navDestinationNode);
                auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
                auto navDestinationFocusHub = navDestinationNode->GetFocusHub();
                CHECK_NULL_VOID(navDestinationFocusHub);
                auto defaultFocusHub = navDestinationFocusHub->GetChildFocusNodeByType(FocusNodeType::DEFAULT);
                if (!defaultFocusHub && navDestinationNode->GetChildren().size() <= EMPTY_DESTINATION_CHILD_SIZE &&
                    navDestinationPattern->GetBackButtonState()) {
                    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
                    CHECK_NULL_VOID(titleBarNode);
                    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
                    backButtonNode->GetOrCreateFocusHub()->SetIsDefaultFocus(true);
                    auto navigation = pattern->GetHost();
                    CHECK_NULL_VOID(navigation);
                    auto navigationFocusHub = navigation->GetFocusHub();
                    CHECK_NULL_VOID(navigationFocusHub);
                    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
                    if (navigationFocusHub->IsCurrentFocus() && navDestinationFocusView) {
                        navDestinationFocusView->SetIsViewRootScopeFocused(false);
                        navDestinationFocusView->FocusViewShow();
                    }
                }
            },
            TaskExecutor::TaskType::UI);
    }
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    CHECK_NULL_RETURN(navigationLayoutProperty, false);
    UpdateTitleModeChangeEventHub(hostNode);
    AddDividerHotZoneRect();
    ifNeedInit_ = false;
    return false;
}

void NavigationPattern::AbortAnimation(RefPtr<NavigationGroupNode>& hostNode)
{
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "Aborting navigation animations");
    if (!hostNode->GetPushAnimations().empty()) {
        auto pushAnimations = hostNode->GetPushAnimations();
        for (const auto& animation : pushAnimations) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
    }
    if (!hostNode->GetPopAnimations().empty()) {
        auto popAnimations = hostNode->GetPopAnimations();
        for (const auto& animation : popAnimations) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
    }
    hostNode->CleanPushAnimations();
    hostNode->CleanPopAnimations();
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
        curDestination->GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
        return;
    }
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);
    navBarNode->SetJSViewActive(true);
    if (!curDestination->IsOnAnimation()) {
        curDestination->GetRenderContext()->UpdateTranslateInXY(OffsetF { 0.0f, 0.0f });
        curDestination->GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
        navBarNode->GetEventHub<EventHub>()->SetEnabledInternal(true);
        auto titleBarNode = DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
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
    return navigationStack_->CreateNodeByIndex(index, parentNode_);
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
    if (!isDividerDraggable_) {
        return;
    }
    isInDividerDrag_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    mouseStyle->SetPointerStyle(static_cast<int32_t>(windowId), MouseFormat::RESIZE_LEFT_RIGHT);
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
    if (!isDividerDraggable_) {
        return;
    }
    isInDividerDrag_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    mouseStyle->SetPointerStyle(static_cast<int32_t>(windowId), MouseFormat::DEFAULT);
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
    if (isInDividerDrag_) {
        return;
    }
    MouseFormat format = isHover ? MouseFormat::RESIZE_LEFT_RIGHT : MouseFormat::DEFAULT;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t currentPointerStyle = 0;
    mouseStyle->GetPointerStyle(static_cast<int32_t>(windowId), currentPointerStyle);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto userSetMinNavBarWidthValue = layoutProperty->GetMinNavBarWidthValue(Dimension(0.0));
    auto userSetMaxNavBarWidthValue = layoutProperty->GetMaxNavBarWidthValue(Dimension(0.0));
    bool navBarWidthRangeEqual = userSetMinNavBarWidthValue.Value() >= userSetMaxNavBarWidthValue.Value();
    if ((userSetNavBarWidthFlag_ && !userSetNavBarRangeFlag_) || (userSetNavBarRangeFlag_ && navBarWidthRangeEqual)) {
        isDividerDraggable_ = false;
        return;
    }
    isDividerDraggable_ = true;
    if (currentPointerStyle != static_cast<int32_t>(format)) {
        mouseStyle->SetPointerStyle(static_cast<int32_t>(windowId), format);
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

void NavigationPattern::AddDividerHotZoneRect()
{
    if (realDividerWidth_ <= 0.0f) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarNode());
    CHECK_NULL_VOID(navBarNode);
    auto geometryNode = navBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(-DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneOffset.SetY(DEFAULT_DIVIDER_START_MARGIN.ConvertToPx());
    SizeF hotZoneSize;
    hotZoneSize.SetWidth(realDividerWidth_ + DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM *
                                                 DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneSize.SetHeight(geometryNode->GetFrameSize().Height());
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

    auto dragRectOffset = geometryNode->GetMarginFrameOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_REGION.ConvertToPx());
    dragRect_.SetOffset(dragRectOffset);
    if (navigationMode_ == NavigationMode::STACK) {
        dragRect_.SetSize(SizeF(0.0f, 0.0f));
    } else {
        dragRect_.SetSize(SizeF(DEFAULT_DRAG_REGION.ConvertToPx() * DEFAULT_HALF + realDividerWidth_,
            geometryNode->GetFrameSize().Height()));
    }

    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragRect_.Width(), DimensionUnit::PX),
        Dimension(dragRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dividerGestureHub->SetResponseRegion(responseRegion);
}

void NavigationPattern::NotifyDialogChange(NavDestinationLifecycle lifecycle, bool isNavigationChanged,
    bool isFromStandardIndex)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    int32_t lastStandardIndex = hostNode->GetLastStandardIndex();
    int32_t standardIndex = lastStandardIndex >= 0 ? lastStandardIndex : 0;
    int32_t start = isFromStandardIndex ? standardIndex : 0;
    int32_t end = isFromStandardIndex ? navigationStack_->Size() : standardIndex;
    bool isShow = lifecycle == NavDestinationLifecycle::ON_SHOW;
    if (isShow) {
        for (int32_t index = start; index < end; index++) {
            NotifyDestinationLifecycle(navDestinationNodes[index].second, lifecycle, true);
        }
    } else {
        for (int32_t index = end - 1; index >= 0 && index >= start; index--) {
            NotifyDestinationLifecycle(navDestinationNodes[index].second, lifecycle, true);
        }
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
    proxy->SetFinishTransitionEvent([weakPattern = WeakClaim(this), preTopNavDestination, newTopNavDestination, proxy,
                                        isPopPage, endCallBack = navigationTransition.endCallback](bool isSuccess) {
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
            (preTopNavDestination && !newTopNavDestination)) {
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
            preDestinationPattern->SetCustomNode(nullptr);
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
            node->SetJSViewActive(false);
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

void NavigationPattern::SetNavigationStack(const RefPtr<NavigationStack>& navigationStack)
{
    if (navigationStack_) {
        navigationStack_->SetOnStateChangedCallback(nullptr);
    }
    navigationStack_ = navigationStack;
    if (navigationStack_) {
        navigationStack_->SetNavigationNode(GetHost());
        WeakPtr<NavigationPattern> weakPattern = WeakClaim(this);
        auto id = Container::CurrentId();
        auto callback = [weakPattern, id]() {
            ContainerScope scope(id);
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->NeedSyncWithJsStackMarked()) {
                return;
            }

            pattern->MarkNeedSyncWithJsStack();
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            context->AddBuildFinishCallBack([weakPattern]() {
                auto pattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->SyncWithJsStackIfNeeded();
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode();
            });
            context->RequestFrame();
        };
        navigationStack_->SetOnStateChangedCallback(callback);
    }
}

RefPtr<NavigationPattern> NavigationPattern::GetParentNavigationPattern()
{
    RefPtr<UINode> node = GetHost();
    CHECK_NULL_RETURN(node, nullptr);
    node = node->GetParent();
    while (node) {
        if (node->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            break;
        }
        node = node->GetParent();
    }
    auto groupNode = AceType::DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_RETURN(groupNode, nullptr);
    return AceType::DynamicCast<NavigationPattern>(groupNode->GetPattern());
}

void NavigationPattern::AttachNavigationStackToParent()
{
    CHECK_NULL_VOID(navigationStack_);
    auto parentPattern = GetParentNavigationPattern();
    CHECK_NULL_VOID(parentPattern);
    auto parentStack = parentPattern->GetNavigationStack();
    if (parentStack) {
        navigationStack_->OnAttachToParent(parentStack);
    }
}

void NavigationPattern::DetachNavigationStackFromParent()
{
    if (navigationStack_) {
        navigationStack_->OnDetachFromParent();
    }
}

void NavigationPattern::DealTransitionVisibility(const RefPtr<FrameNode>& node, bool isVisible, bool isNavBar)
{
    auto renderContext = node->GetRenderContext();
    if (!renderContext->HasDisappearTransition()) {
        auto layoutProperty = node->GetLayoutProperty();
        layoutProperty->UpdateVisibility(isVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
        node->SetJSViewActive(isVisible);
        return;
    }
    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(isVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE, true);
    renderContext->SetTransitionOutCallback([weakNode = WeakPtr<FrameNode>(node), isVisible, isNavBar] {
        auto curNode = weakNode.Upgrade();
        CHECK_NULL_VOID(curNode);
        if (isNavBar) {
            auto navBarNode = AceType::DynamicCast<NavBarNode>(curNode);
            if (navBarNode->GetTransitionType() != PageTransitionType::EXIT_PUSH) {
                return;
            }
        } else {
            auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            if (navDestinationNode->GetTransitionType() != PageTransitionType::EXIT_PUSH) {
                return;
            }
        }
        curNode->SetJSViewActive(isVisible);
    });
}

void NavigationPattern::AddToDumpManager()
{
    auto node = GetHost();
    auto context = PipelineContext::GetCurrentContext();
    if (!node || !context) {
        return;
    }
    auto mgr = context->GetNavigationManager();
    if (!mgr) {
        return;
    }
    auto callback = [weakPattern = WeakClaim(this)](int depth) {
        auto pattern = weakPattern.Upgrade();
        if (!pattern) {
            return;
        }
        const auto& stack = pattern->GetNavigationStack();
        if (!stack) {
            return;
        }
        auto infos = stack->DumpStackInfo();
        for (const auto& info : infos) {
            DumpLog::GetInstance().Print(depth, info);
        }
    };
    mgr->AddNavigationDumpCallback(node->GetId(), node->GetDepth(), callback);
}

void NavigationPattern::RemoveFromDumpManager()
{
    auto node = GetHost();
    auto context = PipelineContext::GetCurrentContext();
    if (!node || !context) {
        return;
    }
    auto mgr = context->GetNavigationManager();
    if (mgr) {
        mgr->RemoveNavigationDumpCallback(node->GetId(), node->GetDepth());
    }
}

void NavigationPattern::FireInterceptionEvent(bool isBefore,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopPath)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    RefPtr<NavDestinationContext> to;
    if (newTopPath.has_value()) {
        auto topDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetNavDestinationNode(newTopPath->second));
        if (topDestination) {
            auto pattern = AceType::DynamicCast<NavDestinationPattern>(topDestination->GetPattern());
            to = pattern->GetNavDestinationContext();
        }
    }
    NavigationOperation operation;
    if (isReplace_ != 0) {
        operation = NavigationOperation::REPLACE;
    } else {
        operation = lastPreIndex_ == -1 ? NavigationOperation::POP : NavigationOperation::PUSH;
    }
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    // mode is split and stack size is one,don't need to do animation.
    if ((layoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT
        || navigationMode_ == NavigationMode::SPLIT) && !preContext_) {
        isAnimated_ = false;
    }
    navigationStack_->FireNavigationInterception(isBefore, preContext_, to, operation,
        isAnimated_);

    if (!isBefore) {
        NotifyNavDestinationSwitch(preContext_, to, operation);
    }
}

void NavigationPattern::UpdateIsAnimation(const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath)
{
    auto disAbleAnimation = navigationStack_->GetDisableAnimation();
    auto animated = navigationStack_->GetAnimatedValue();
    // current animation flag is false
    if (disAbleAnimation || !animated) {
        isAnimated_ = false;
        return;
    }
    // check is dialog mode
    bool isDialog = false;
    if (preTopNavPath.has_value()) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath->second));
        if (preDestination) {
            isDialog |= preDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG;
        }
    }
    auto topNode = navigationStack_->Get();
    if (topNode) {
        auto newTopDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(topNode));
        if (newTopDestination) {
            isDialog |= newTopDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG;
        }
    }
    if (!isDialog) {
        isAnimated_ = true;
        return;
    }
    isAnimated_ = isCustomAnimation_;
}

void NavigationPattern::NotifyNavDestinationSwitch(const RefPtr<NavDestinationContext>& from,
    const RefPtr<NavDestinationContext>& to, NavigationOperation operation)
{
    auto host = GetHost();
    if (!host) {
        return;
    }

    std::string navigationId = host->GetInspectorIdValue("");
    std::optional<NavDestinationInfo> fromInfo;
    std::optional<NavDestinationInfo> toInfo;
    BuildNavDestinationInfoFromContext(navigationId, NavDestinationState::ON_HIDDEN, from, true, fromInfo);
    BuildNavDestinationInfoFromContext(navigationId, NavDestinationState::ON_SHOWN, to, false, toInfo);
    UIObserverHandler::GetInstance().NotifyNavDestinationSwitch(
        std::move(fromInfo), std::move(toInfo), operation);
}

void NavigationPattern::StartTransition(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination,
    bool isAnimated, bool isPopPage, bool isNeedVisible)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationManager = pipeline->GetNavigationManager();
    navigationManager->FireNavigationUpdateCallback();
    if (!isAnimated) {
        FireShowAndHideLifecycle(preDestination, topDestination, isPopPage);
        TransitionWithOutAnimation(preDestination, topDestination, isPopPage, isNeedVisible);
        return;
    }
    pipeline->AddAfterLayoutTask([weakNavigation = WeakClaim(this),
        weakPreDestination = WeakPtr<NavDestinationGroupNode>(preDestination),
        weakTopDestination = WeakPtr<NavDestinationGroupNode>(topDestination),
        isPopPage, isAnimated, isNeedVisible]() {
        auto navigationPattern = AceType::DynamicCast<NavigationPattern>(weakNavigation.Upgrade());
        CHECK_NULL_VOID(navigationPattern);
        auto preDestination = weakPreDestination.Upgrade();
        auto topDestination = weakTopDestination.Upgrade();
        navigationPattern->FireShowAndHideLifecycle(preDestination, topDestination, isPopPage);
        navigationPattern->TransitionWithAnimation(preDestination, topDestination, isPopPage);
    });
}

void NavigationPattern::NotifyDestinationLifecycle(const RefPtr<UINode>& uiNode,
    NavDestinationLifecycle lifecycle, bool isNavigationChanged)
{
    auto curDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
    CHECK_NULL_VOID(curDestination);
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    if ((navDestinationPattern->GetIsOnShow() && lifecycle == NavDestinationLifecycle::ON_SHOW) ||
        (!navDestinationPattern->GetIsOnShow() && lifecycle == NavDestinationLifecycle::ON_HIDE)) {
        return;
    }
    auto eventHub = curDestination->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (isNavigationChanged) {
        NavigationPattern::FireNavigationLifecycleChange(curDestination, lifecycle);
    }
    if (lifecycle == NavDestinationLifecycle::ON_SHOW) {
        auto param = Recorder::EventRecorder::Get().IsPageRecordEnable() ?
            navigationStack_->GetRouteParam() : "";
        eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
        NotifyPageShow(navDestinationPattern->GetName());
        navDestinationPattern->SetIsOnShow(true);
        return;
    }
    if (lifecycle == NavDestinationLifecycle::ON_HIDE) {
        eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
        NotifyPageHide(navDestinationPattern->GetName());
        navDestinationPattern->SetIsOnShow(false);
    }
}

void NavigationPattern::PerformanceEventReport(int32_t nodeCount, int32_t depth, const std::string& navDestinationName)
{
    if (nodeCount >= PAGE_NODES) {
        EventReport::ReportPageNodeOverflow(navDestinationName, nodeCount, PAGE_NODES);
    }
    if (depth >= PAGE_DEPTH) {
        EventReport::ReportPageDepthOverflow(navDestinationName, depth, PAGE_DEPTH);
    }
}

void NavigationPattern::FireShowAndHideLifecycle(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination, bool isPopPage)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    // don't move position hide lifecycle is from top to end
    if (preDestination) {
        auto lastStandardIndex = hostNode->GetLastStandardIndex();
        if (isPopPage || lastStandardIndex > preDestination->GetIndex()) {
            NotifyDestinationLifecycle(preDestination,
                NavDestinationLifecycle::ON_HIDE, true);
        }
    }
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_HIDE);
    NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, false, true);
    FireInterceptionEvent(false, navigationStack_->GetTopNavPath());
}
} // namespace OHOS::Ace::NG
