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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H

#include "base/memory/referenced.h"
#include "base/system_bar/system_bar_style.h"
#include "base/utils/utils.h"
#include "core/common/autofill/auto_fill_trigger_state_holder.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class NavDestinationPattern : public NavDestinationPatternBase, public AutoFillTriggerStateHolder {
    DECLARE_ACE_TYPE(NavDestinationPattern, NavDestinationPatternBase, AutoFillTriggerStateHolder);

public:
    explicit NavDestinationPattern(const RefPtr<ShallowBuilder>& shallowBuilder);
    NavDestinationPattern();
    ~NavDestinationPattern() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<NavDestinationLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layout = MakeRefPtr<NavDestinationLayoutAlgorithm>();
        layout->SetIsShown(isOnShow_);
        return layout;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NavDestinationEventHub>();
    }

    void OnActive() override;

    void OnModifyDone() override;

    const RefPtr<ShallowBuilder>& GetShallowBuilder() const
    {
        return shallowBuilder_;
    }

    void SetName(const std::string& name)
    {
        name_ = name;
        auto eventHub = GetOrCreateEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetName(name);
    }

    const std::string& GetName()
    {
        return name_;
    }

    void SetNavPathInfo(const RefPtr<NavPathInfo>& pathInfo)
    {
        if (!navDestinationContext_) {
            return;
        }
        auto oldInfo = navDestinationContext_->GetNavPathInfo();
        if (oldInfo) {
            oldInfo->UpdateNavPathInfo(pathInfo);
        } else {
            navDestinationContext_->SetNavPathInfo(pathInfo);
        }
    }

    RefPtr<NavPathInfo> GetNavPathInfo() const
    {
        return navDestinationContext_ ? navDestinationContext_->GetNavPathInfo() : nullptr;
    }

    void SetNavigationStack(const WeakPtr<NavigationStack>& stack)
    {
        if (navDestinationContext_) {
            navDestinationContext_->SetNavigationStack(stack);
        }
    }

    WeakPtr<NavigationStack> GetNavigationStack() const
    {
        return navDestinationContext_ ? navDestinationContext_->GetNavigationStack() : nullptr;
    }

    void SetIndex(int32_t index)
    {
        if (navDestinationContext_) {
            navDestinationContext_->SetIndex(index);
        }
    }

    void SetNavDestinationContext(const RefPtr<NavDestinationContext>& context)
    {
        navDestinationContext_ = context;
        if (navDestinationContext_) {
            navDestinationContext_->SetNavDestinationPattern(WeakClaim(this));
            navDestinationContext_->SetNavDestinationId(navDestinationId_);
        }
    }

    RefPtr<NavDestinationContext> GetNavDestinationContext() const
    {
        return navDestinationContext_;
    }

    void SetCustomNode(const RefPtr<UINode>& customNode)
    {
        customNode_ = customNode;
    }

    RefPtr<UINode> GetCustomNode()
    {
        return customNode_;
    }

    void SetIsOnShow(bool isOnShow)
    {
        isOnShow_ = isOnShow;
    }

    bool GetIsOnShow()
    {
        return isOnShow_;
    }

    bool GetBackButtonState();

    NavDestinationState GetNavDestinationState() const
    {
        auto eventHub = GetOrCreateEventHub<NavDestinationEventHub>();
        CHECK_NULL_RETURN(eventHub, NavDestinationState::NONE);
        auto state = eventHub->GetState();
        return state;
    }

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}

    uint64_t GetNavDestinationId() const
    {
        return navDestinationId_;
    }

    void OnDetachFromMainTree() override
    {
        backupStyle_.reset();
        currStyle_.reset();
    }

    bool OverlayOnBackPressed();

    void CreateOverlayManager(bool isShow)
    {
        if (!overlayManager_ && isShow) {
            overlayManager_ = MakeRefPtr<OverlayManager>(GetHost());
        }
    }

    const RefPtr<OverlayManager>& GetOverlayManager()
    {
        return overlayManager_;
    }

    void DeleteOverlayManager()
    {
        overlayManager_.Reset();
    }

    int32_t GetTitlebarZIndex() const;

    void SetNavigationId(const std::string& id)
    {
        inspectorId_ = id;
    }

    std::string GetNavigationId() const
    {
        return inspectorId_;
    }

    void SetIsUserDefinedBgColor(bool isUserDefinedBgColor)
    {
        isUserDefinedBgColor_ = isUserDefinedBgColor;
    }

    bool IsUserDefinedBgColor() const
    {
        return isUserDefinedBgColor_;
    }

    void OnLanguageConfigurationUpdate() override;

    bool NeedIgnoreKeyboard();

    void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style);
    const std::optional<RefPtr<SystemBarStyle>>& GetBackupStyle() const
    {
        return backupStyle_;
    }
    const std::optional<RefPtr<SystemBarStyle>>& GetCurrentStyle() const
    {
        return currStyle_;
    }

    void OnWindowHide() override;

    const RefPtr<NavDestinationScrollableProcessor>& GetScrollableProcessor() const
    {
        return scrollableProcessor_;
    }
    void SetScrollableProcessor(const RefPtr<NavDestinationScrollableProcessor>& processor)
    {
        scrollableProcessor_ = processor;
    }
    /**
     * Respond to the scrolling events of the internal scrolling components of NavDestination,
     * and hide part of the titleBar&toolBar( translate up or down in Y axis ), while changing
     * the opacity of the titleBar&toolBar.
     */
    void UpdateTitleAndToolBarHiddenOffset(float offset);
    // show titleBar&toolBar immediately.
    void ShowTitleAndToolBar();
    // cancel the delayed task if we have started, which will show titleBar&toolBar in the feature time.
    void CancelShowTitleAndToolBarTask();
    // Restore the titleBar&toolBar to its original position (hide or show state).
    void ResetTitleAndToolBarState();
    
    void OnCoordScrollStart() override;
    float OnCoordScrollUpdate(float offset, float currentOffset) override;
    void OnCoordScrollEnd() override;
    void UpdateBackgroundColor();
    bool NeedCoordWithScroll() override
    {
        return IsNeedHandleScroll();
    }

    bool IsNeedHandleScroll() const override
    {
        auto eventHub = GetOrCreateEventHub<NavDestinationEventHub>();
        if (eventHub && eventHub->HasOnCoordScrollStartAction()) {
            return true;
        }
        return false;
    }
    
    float GetTitleBarHeightLessThanMaxBarHeight() const override
    {
        return 0.0;
    }
    
    bool CanCoordScrollUp(float offset) const override
    {
        return IsNeedHandleScroll();
    }

    void SetIsActive(bool isActive)
    {
        isActive_ = isActive;
    }

    bool IsActive() const
    {
        return isActive_;
    }

private:
    struct HideBarOnSwipeContext {
        CancelableCallback<void()> showBarTask;
        bool isBarShowing = false;
        bool isBarHiding = false;
    };
    HideBarOnSwipeContext& GetSwipeContext(bool isTitle)
    {
        return isTitle ? titleBarSwipeContext_ : toolBarSwipeContext_;
    }
    RefPtr<FrameNode> GetBarNode(const RefPtr<NavDestinationNodeBase>& nodeBase, bool isTitle);
    bool EnableTitleBarSwipe(const RefPtr<NavDestinationNodeBase>& nodeBase);
    bool EnableToolBarSwipe(const RefPtr<NavDestinationNodeBase>& nodeBase);
    void UpdateBarHiddenOffset(const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<FrameNode>& barNode, float offset, bool isTitle);
    void StartHideOrShowBarInner(const RefPtr<NavDestinationNodeBase>& nodeBase,
        float barHeight, float curTranslate, bool isTitle, bool isHide);
    void StopHideBarIfNeeded(float curTranslate, bool isTitle);
    void PostShowBarDelayedTask(bool isTitle);
    void ResetBarState(const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<FrameNode>& barNode, bool isTitle);

    void UpdateNameIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode);
    void UpdateBackgroundColorIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode);
    void MountTitleBar(
        RefPtr<NavDestinationGroupNode>& hostNode, bool& needRunTitleBarAnimation);
    void OnFontScaleConfigurationUpdate() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void CloseLongPressDialog();
    void CheckIfOrientationChanged();
    void StopAnimation();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void CheckIfStatusBarConfigChanged();
    void CheckIfNavigationIndicatorConfigChagned();

    RefPtr<ShallowBuilder> shallowBuilder_;
    std::string name_;
    std::string inspectorId_;
    RefPtr<NavDestinationContext> navDestinationContext_;
    RefPtr<UINode> customNode_;
    RefPtr<OverlayManager> overlayManager_;
    bool isOnShow_ = false;
    bool isActive_ = false;
    bool isUserDefinedBgColor_ = false;
    bool isRightToLeft_ = false;
    uint64_t navDestinationId_ = 0;

    std::optional<RefPtr<SystemBarStyle>> backupStyle_;
    std::optional<RefPtr<SystemBarStyle>> currStyle_;

    RefPtr<NavDestinationScrollableProcessor> scrollableProcessor_;
    HideBarOnSwipeContext titleBarSwipeContext_;
    HideBarOnSwipeContext toolBarSwipeContext_;
    bool isFirstTimeCheckOrientation_ = true;
    bool isFirstTimeCheckStatusBarConfig_ = true;
    bool isFirstTimeCheckNavigationIndicatorConfig_ = true;
    RefPtr<TouchEventImpl> touchListener_ = nullptr;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_PATTERN_H
