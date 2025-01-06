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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_PATTERN_H

#include "base/memory/referenced.h"
#include "base/system_bar/system_bar_style.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/inner_navigation_controller.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

using namespace Framework;
using OnNavigationAnimation = std::function<NavigationTransition(RefPtr<NavDestinationContext>,
        RefPtr<NavDestinationContext>, NavigationOperation)>;
class NavigationPattern : public Pattern {
    DECLARE_ACE_TYPE(NavigationPattern, Pattern);

public:
    NavigationPattern();
    ~NavigationPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavigationLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavigationEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<NavigationLayoutAlgorithm>();
        layoutAlgorithm->SetRealNavBarWidth(realNavBarWidth_);
        layoutAlgorithm->SetIfNeedInit(ifNeedInit_);
        return layoutAlgorithm;
    }

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void OnWindowHide() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void BeforeSyncGeometryProperties(const DirtySwapConfig& /* config */) override;

    void OnLanguageConfigurationUpdate() override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { false, true, ScopeType::FLEX };
    }

    void SetNavDestination(std::function<void(std::string)>&& builder)
    {
        builder_ = std::move(builder);
    }

    NavigationMode GetNavigationMode() const
    {
        return navigationMode_;
    }

    void SetNavigationMode(NavigationMode navigationMode)
    {
        navigationMode_ = navigationMode;
    }

    bool JudgeFoldStateChangeAndUpdateState();

    void SetNavigationStack(const RefPtr<NavigationStack>& navigationStack);

    const RefPtr<NavigationStack>& GetNavigationStack()
    {
        return navigationStack_;
    }

    // use for navRouter case
    void AddNavDestinationNode(const std::string& name, const RefPtr<UINode>& navDestinationNode)
    {
        addByNavRouter_ = true;
        navigationStack_->Add(name, navDestinationNode);
    }

    void AddNavDestinationNode(const std::string& name, const RefPtr<UINode>& navDestinationNode, NavRouteMode mode)
    {
        addByNavRouter_ = true;
        navigationStack_->Add(name, navDestinationNode, mode);
    }

    void AddNavDestinationNode(const std::string& name, const RefPtr<UINode>& navDestinationNode, NavRouteMode mode,
        const RefPtr<RouteInfo>& routeInfo)
    {
        addByNavRouter_ = true;
        navigationStack_->Add(name, navDestinationNode, mode, routeInfo);
    }

    RefPtr<UINode> GetNavDestinationNode(const std::string& name)
    {
        RefPtr<UINode> uiNode;
        int32_t index;
        navigationStack_->Get(name, uiNode, index);
        return uiNode;
    }

    RefPtr<UINode> GetNavDestinationNode()
    {
        // get NavDestinationNode from the stack top
        return navigationStack_->Get();
    }

    RefPtr<UINode> GetPreNavDestination(const std::string& name, const RefPtr<UINode>& navDestinationNode)
    {
        return navigationStack_->GetPre(name, navDestinationNode);
    }

    const std::vector<std::pair<std::string, RefPtr<UINode>>>& GetAllNavDestinationNodes()
    {
        return navigationStack_->GetAllNavDestinationNodes();
    }

    void RemoveIfNeeded(const std::string& name, const RefPtr<UINode>& navDestinationNode)
    {
        navigationStack_->Remove(name, navDestinationNode);
    }

    void RemoveNavDestination()
    {
        navigationStack_->Remove();
    }

    void InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub);

    void CleanStack()
    {
        navigationStack_->RemoveAll();
    }

    void UpdateAnimatedValue(bool animated)
    {
        navigationStack_->UpdateAnimatedValue(animated);
    }

    void SetNavigationStackProvided(bool provided)
    {
        navigationStackProvided_ = provided;
    }

    bool GetNavigationStackProvided() const
    {
        return navigationStackProvided_;
    }

    void SetNavBarVisibilityChange(bool isChange)
    {
        navBarVisibilityChange_ = isChange;
    }

    bool GetNavBarVisibilityChange() const
    {
        return navBarVisibilityChange_;
    }

    void OnVisibleChange(bool isVisible) override;

    void OnColorConfigurationUpdate() override;
    void AddDragBarHotZoneRect();

    Dimension GetMinNavBarWidthValue() const
    {
        return minNavBarWidthValue_;
    }
    void SetMinNavBarWidthValue(Dimension minNavBarWidthValue)
    {
        minNavBarWidthValue_ = minNavBarWidthValue;
    }

    Dimension GetMaxNavBarWidthValue() const
    {
        return maxNavBarWidthValue_;
    }
    void SetMaxNavBarWidthValue(Dimension maxNavBarWidthValue)
    {
        maxNavBarWidthValue_ = maxNavBarWidthValue;
    }

    Dimension GetMinContentWidthValue() const
    {
        return minContentWidthValue_;
    }

    void SetMinContentWidthValue(Dimension minContentWidthValue)
    {
        minContentWidthValue_ = minContentWidthValue;
    }

    bool GetUserSetNavBarRangeFlag() const
    {
        return userSetNavBarRangeFlag_;
    }

    void SetUserSetNavBarRangeFlag(bool userSetNavBarRangeFlag)
    {
        userSetNavBarRangeFlag_ = userSetNavBarRangeFlag;
    }

    bool GetUserSetMinContentFlag() const
    {
        return userSetMinContentFlag_;
    }

    void SetUserSetMinContentFlag(bool userSetMinContentFlag)
    {
        userSetMinContentFlag_ = userSetMinContentFlag;
    }

    bool GetUserSetNavBarWidthFlag() const
    {
        return userSetNavBarWidthFlag_;
    }

    void SetUserSetNavBarWidthFlag(bool userSetNavBarWidthFlag)
    {
        userSetNavBarWidthFlag_ = userSetNavBarWidthFlag;
    }

    void SetInitNavBarWidth(const Dimension& initNavBarWidth)
    {
        realNavBarWidth_ = static_cast<float>(initNavBarWidth.ConvertToPx());
        initNavBarWidthValue_ = initNavBarWidth;
    }

    Dimension GetInitNavBarWidth() const
    {
        return initNavBarWidthValue_;
    }

    void SetIfNeedInit(bool ifNeedInit)
    {
        ifNeedInit_ = ifNeedInit;
    }

    void UpdateContextRect(
        const RefPtr<NavDestinationGroupNode>& curDestination, const RefPtr<NavigationGroupNode>& navigation);

    bool GetNavigationModeChange() const
    {
        return navigationModeChange_;
    }

    void SetNavigationModeChange(bool modeChange)
    {
        navigationModeChange_ = modeChange;
    }

    void AddOnStateChangeItem(int32_t nodeId, std::function<void(bool)> callback)
    {
        onStateChangeMap_.emplace(nodeId, callback);
    }

    void DeleteOnStateChangeItem(int32_t nodeId)
    {
        onStateChangeMap_.erase(nodeId);
    }

    const std::shared_ptr<NavigationController>& GetNavigationController() const
    {
        return navigationController_;
    }

    const std::map<int32_t, std::function<void(bool)>>& GetOnStateChangeMap()
    {
        return onStateChangeMap_;
    }

    void OnNavigationModeChange(bool modeChange);

    void OnNavBarStateChange(bool modeChange);

    static void FireNavigationChange(const RefPtr<UINode>& node, bool isShow, bool isFirst);

    static void FireNavigationInner(const RefPtr<UINode>& node, bool isShow);

    static void FireNavigationStateChange(const RefPtr<UINode>& node, bool isShow);

    static void FireNavigationLifecycleChange(const RefPtr<UINode>& node, NavDestinationLifecycle lifecycle);

    static bool CheckParentDestinationIsOnhide(const RefPtr<NavDestinationGroupNode>& destinationNode);
    static bool CheckDestinationIsPush(const RefPtr<NavDestinationGroupNode>& destinationNode);
    static void NotifyPerfMonitorPageMsg(const std::string& pageName);

    // type: will_show + on_show, will_hide + on_hide, hide, show, willShow, willHide
    void NotifyDialogChange(NavDestinationLifecycle lifecycle, bool isFromStandard);
    void NotifyPageHide(const std::string& pageName);
    void CheckContentNeedMeasure(const RefPtr<FrameNode>& node);
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void SetIsCustomAnimation(bool isCustom)
    {
        isCustomAnimation_ = isCustom;
    }

    void SetNavigationTransition(const OnNavigationAnimation navigationAnimation)
    {
        auto currentProxy = GetTopNavigationProxy();
        if (currentProxy && !currentProxy->GetIsFinished()) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "not support to update callback during animation");
            return;
        }
        onTransition_ = std::move(navigationAnimation);
    }

    bool NeedSyncWithJsStackMarked() const
    {
        return needSyncWithJsStack_;
    }

    void MarkNeedSyncWithJsStack()
    {
        needSyncWithJsStack_ = true;
    }

    void SyncWithJsStackIfNeeded();

    void AttachNavigationStackToParent();
    void DetachNavigationStackFromParent();

    void AddToDumpManager();
    void RemoveFromDumpManager();

    void NotifyDestinationLifecycle(const RefPtr<UINode>& destinationNode,
        NavDestinationLifecycle lifecycle);
    void AbortAnimation(RefPtr<NavigationGroupNode>& hostNode);

    void SetParentCustomNode(const RefPtr<UINode>& parentNode)
    {
        parentNode_ = parentNode;
    }

    WeakPtr<UINode> GetParentCustomNode() const
    {
        return parentNode_;
    }

    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style);

    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    bool IsFullPageNavigation() const
    {
        return isFullPageNavigation_;
    }

    bool IsTopNavDestination(const RefPtr<UINode>& node) const;
    void TryRestoreSystemBarStyle(const RefPtr<WindowManager>& windowManager);

    bool IsFinishInteractiveAnimation() const
    {
        return isFinishInteractiveAnimation_;
    }

    const RefPtr<NavigationTransitionProxy> GetTopNavigationProxy() const
    {
        return proxyList_.empty() ? nullptr : proxyList_.back();
    }

    RefPtr<NavigationTransitionProxy> GetProxyById(uint64_t id) const;

    void RemoveProxyById(uint64_t id);

    bool IsCurTopNewInstance() const
    {
        return isCurTopNewInstance_;
    }

    const std::vector<std::pair<std::string, WeakPtr<UINode>>>& GetAllNavDestinationNodesPrev()
    {
        return navigationStack_->GetAllNavDestinationNodesPrev();
    }

    void DialogAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool isNeedVisible);

    bool IsLastStdChange();
    void ReplaceAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination);
    void TransitionWithDialogAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage);
    void FollowStdNavdestinationAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage);

    std::unique_ptr<JsonValue> GetNavdestinationJsonArray();
    void RestoreJsStackIfNeeded();

    RefPtr<FrameNode> GetNavBasePageNode() const
    {
        return pageNode_.Upgrade();
    }

    RefPtr<FrameNode> GetDragBarNode() const;
    void BuildDragBar();
    void InitDragBarEvent();
    void ClearDragBarEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown();
    void HandleTouchUp();

    void SetEnableDragBar(bool enabled)
    {
        enableDragBar_ = enabled;
    }

    bool GetEnableDragBar() const
    {
        return enableDragBar_;
    }

    void SetNavigationSize(const SizeF& size)
    {
        navigationSize_ = size;
    }
    const SizeF& GetNavigationSize() const
    {
        return navigationSize_;
    }

    bool GetIsInDividerDrag() const
    {
        return isInDividerDrag_;
    }

private:
    void UpdateIsFullPageNavigation(const RefPtr<FrameNode>& host);
    void UpdateSystemBarStyleOnFullPageStateChange(const RefPtr<WindowManager>& windowManager);
    void UpdateSystemBarStyleOnTopNavPathChange(
        const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath);
    void UpdateSystemBarStyleWithTopNavPath(const RefPtr<WindowManager>& windowManager,
        const std::optional<std::pair<std::string, RefPtr<UINode>>>& topNavPath);
    void UpdateSystemBarStyleOnPageVisibilityChange(bool show);
    void RegisterPageVisibilityChangeCallback();
    bool ApplyTopNavPathSystemBarStyleOrRestore(const RefPtr<WindowManager>& windowManager,
        const std::optional<std::pair<std::string, RefPtr<UINode>>>& topNavPath);
    void InitPageNode(const RefPtr<FrameNode>& host);
    void InitFoldState();

    void CheckTopNavPathChange(const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath,
        const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath,
        int32_t preLastStandardIndex = -1);
    void TransitionWithAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool isNeedVisible = false);
    bool TriggerCustomAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage);

    void OnCustomAnimationFinish(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage);
    void TransitionWithOutAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool needVisible = false);
    NavigationTransition ExecuteTransition(const RefPtr<NavDestinationGroupNode>& preTopDestination,
        const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage);
    RefPtr<RenderContext> GetTitleBarRenderContext();
    void DoAnimation(NavigationMode usrNavigationMode);
    void RecoveryToLastStack(const RefPtr<NavDestinationGroupNode>& preTopDestination,
        const RefPtr<NavDestinationGroupNode>& newTopDestination);
    bool GenerateUINodeByIndex(int32_t index, RefPtr<UINode>& node);
    int32_t GenerateUINodeFromRecovery(int32_t lastStandardIndex, NavPathList& navPathList);
    void DoNavbarHideAnimation(const RefPtr<NavigationGroupNode>& hostNode);
    RefPtr<FrameNode> GetDividerNode() const;
    void FireInterceptionEvent(bool isBefore,
        const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath);
    void InitDividerPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitDragBarPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart();
    void HandleDragUpdate(float xOffset);
    void HandleDragEnd();
    void OnHover(bool isHover);
    float GetPaintRectHeight(const RefPtr<FrameNode>& node)
    {
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, 0.0f);
        return renderContext->GetPaintRectWithoutTransform().Height();
    }
    void AddDividerHotZoneRect();
    void RangeCalculation(
        const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavigationLayoutProperty>& navigationLayoutProperty);
    bool UpdateTitleModeChangeEventHub(const RefPtr<NavigationGroupNode>& hostNode);
    void FireNavBarWidthChangeEvent(const RefPtr<LayoutWrapper>& layoutWrapper);
    void NotifyPageShow(const std::string& pageName);
    void ProcessPageShowEvent();
    int32_t FireNavDestinationStateChange(NavDestinationLifecycle lifecycle);
    void UpdatePreNavDesZIndex(const RefPtr<FrameNode> &preTopNavDestination,
        const RefPtr<FrameNode> &newTopNavDestination, int32_t preLastStandardIndex = -1);
    void UpdateNavPathList();
    void RefreshNavDestination();
    RefPtr<NavigationPattern> GetParentNavigationPattern();
    void DealTransitionVisibility(const RefPtr<FrameNode>& node, bool isVisible, bool isNavBar);
    void NotifyNavDestinationSwitch(const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation);

    void UpdateIsAnimation(const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath);
    void StartTransition(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination,
    bool isAnimated, bool isPopPage, bool isNeedVisible = false);
    void ProcessAutoSave(const RefPtr<FrameNode>& node);

    void FireShowAndHideLifecycle(const RefPtr<NavDestinationGroupNode>& preDestination,
        const RefPtr<NavDestinationGroupNode>& topDestination, bool isPopPage, bool isAnimated);
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void RefreshFocusToDestination();

    void PerformanceEventReport(int32_t nodeCount, int32_t depth, const std::string& navDestinationName);
    void StartDefaultAnimation(const RefPtr<NavDestinationGroupNode>& preTopDestination,
        const RefPtr<NavDestinationGroupNode>& topDestination,
        bool isPopPage, bool isNeedInVisible = false);
    bool ExecuteAddAnimation(const RefPtr<NavDestinationGroupNode>& preTopDestination,
        const RefPtr<NavDestinationGroupNode>& topDestination,
        bool isPopPage, const RefPtr<NavigationTransitionProxy>& proxy,
        NavigationTransition navigationTransition);
    bool GetIsFocusable(const RefPtr<FrameNode>& frameNode);
    void GetOrCreateNavDestinationUINode();
    void CloseLongPressDialog();

    void CreateDragBarNode(const RefPtr<NavigationGroupNode>& navigationGroupNode);
    RefPtr<FrameNode> CreateDragBarItemNode();
    void SetMouseStyle(MouseFormat format);

    void RegisterContainerModalButtonsRectChangeListener(const RefPtr<FrameNode>& hostNode);
    void UnregisterContainerModalButtonsRectChangeListener(const RefPtr<FrameNode>& hostNode);
    virtual void MarkAllNavDestinationDirtyIfNeeded(const RefPtr<FrameNode>& hostNode);

    NavigationMode navigationMode_ = NavigationMode::AUTO;
    std::function<void(std::string)> builder_;
    RefPtr<NavigationStack> navigationStack_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<PanEvent> dragBarPanEvent_;
    std::vector<RefPtr<NavigationTransitionProxy>> proxyList_;
    RectF dragRect_;
    RectF dragBarRect_;
    WeakPtr<FrameNode> pageNode_;
    bool isFullPageNavigation_ = false;
    std::optional<RefPtr<SystemBarStyle>> backupStyle_;
    std::optional<RefPtr<SystemBarStyle>> currStyle_;
    bool addByNavRouter_ = false;
    bool ifNeedInit_ = true;
    float preNavBarWidth_ = 0.0f;
    float realNavBarWidth_ = DEFAULT_NAV_BAR_WIDTH.ConvertToPx();
    float realDividerWidth_ = 2.0f;
    bool navigationStackProvided_ = false;
    bool navBarVisibilityChange_ = false;
    bool userSetNavBarRangeFlag_ = false;
    bool userSetMinContentFlag_ = false;
    bool userSetNavBarWidthFlag_ = false;
    bool isChanged_ = false; // check navigation top page is change
    Dimension initNavBarWidthValue_ = DEFAULT_NAV_BAR_WIDTH;
    Dimension minNavBarWidthValue_ = 0.0_vp;
    Dimension maxNavBarWidthValue_ = 0.0_vp;
    Dimension minContentWidthValue_ = 0.0_vp;
    NavigationTitleMode titleMode_ = NavigationTitleMode::FREE;
    bool navigationModeChange_ = false;
    bool isCustomAnimation_ = false; // custom animation
    bool isInDividerDrag_ = false;
    bool isDividerDraggable_ = true;
    bool isAnimated_ = false;
#if defined(ENABLE_NAV_SPLIT_MODE)
    bool isBackPage_ = false;
#endif
    FoldStatus currentFoldStatus_ = FoldStatus::UNKNOWN;  // only used for mode-switch animation
    bool isReplace_ = false;
    bool isFinishInteractiveAnimation_ = true;
    int32_t lastPreIndex_ = false;
    std::shared_ptr<NavigationController> navigationController_;
    std::map<int32_t, std::function<void(bool)>> onStateChangeMap_;
    OnNavigationAnimation onTransition_;
    bool needSyncWithJsStack_ = false;
    std::optional<std::pair<std::string, RefPtr<UINode>>> preTopNavPath_;
    RefPtr<NavDestinationContext> preContext_;
    WeakPtr<UINode> parentNode_;
    int32_t preStackSize_ = 0;
    bool isRightToLeft_ = false;
    bool isCurTopNewInstance_ = false;
    RefPtr<TouchEventImpl> touchEvent_;
    bool enableDragBar_ = false;
    SizeF navigationSize_;
    std::optional<NavBarPosition> preNavBarPosition_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_PATTERN_H
