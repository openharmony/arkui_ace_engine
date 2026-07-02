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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H

#include <optional>

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/manager/recoverable/recoverable_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/event/pan_event.h"
#include "core/animation/curve.h"

enum class FloatingBarPosition {
    CENTER = 0,
    LEFT,
    RIGHT,
};

constexpr float FLOATING_BAR_SCALE = 1.0f;
constexpr float FLOATING_BAR_SCALE_ENLARGED = 1.15f;

namespace OHOS::Ace::NG {

class TabsNode;

class TabsPattern : public Pattern, public virtual RecoverableView {
    DECLARE_ACE_TYPE(TabsPattern, Pattern, RecoverableView);

public:
    TabsPattern() = default;
    ~TabsPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsNeedPercent() const override
    {
        return true;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        ACE_UINODE_TRACE(GetHost());
        return MakeRefPtr<TabsLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

    void PerformanceCheckTabChange(
        RefPtr<OHOS::Ace::NG::TabsPattern> pattern, RefPtr<OHOS::Ace::NG::TabsNode> tabsNode, bool currentIndex);
    
    void SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& event);

    ChangeEventWithPreIndexPtr GetChangeEvent()
    {
        return onChangeEvent_;
    }

    void SetOnTabBarClickEvent(std::function<void(const BaseEventInfo*)>&& event);

    void SetAnimationStartEvent(AnimationStartEvent&& event);

    void SetAnimationEndEvent(AnimationEndEvent&& event);

    void SetOnSelectedEvent(std::function<void(const BaseEventInfo*)>&& event);

    void SetOnUnselectedEvent(std::function<void(const BaseEventInfo*)>&& event);

    void SetOnContentDidScroll(ContentDidScrollEvent&& onContentDidScroll);

    ChangeEventPtr GetTabBarClickEvent()
    {
        return onTabBarClickEvent_;
    }

    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    std::string ProvideRestoreInfo() override;

    void OnRestoreInfo(const std::string& restoreInfo) override;

    void AddInnerOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc) override;

    void RecoverInnerOnGestureRecognizerJudgeBegin() override;

    void SetOnIndexChangeEvent(std::function<void(const BaseEventInfo*)>&& event);

    ChangeEventPtr GetIndexChangeEvent()
    {
        return onIndexChangeEvent_;
    }

    bool GetIsCustomAnimation() const
    {
        return isCustomAnimation_;
    }

    void SetIsCustomAnimation(bool isCustomAnimation)
    {
        isCustomAnimation_ = isCustomAnimation;
    }

    void SetIsDisableSwipe(bool isDisableSwipe)
    {
        isDisableSwipe_ = isDisableSwipe;
    }

    void SetOnContentWillChange(std::function<bool(int32_t, int32_t)>&& callback)
    {
        callback_ = callback;
    }

    std::optional<bool> OnContentWillChange(int32_t preIndex, int32_t index) const
    {
        std::optional<bool> ret;
        if (callback_) {
            ret = callback_(preIndex, index);
        }
        return ret;
    }

    void SetInterceptStatus(bool status)
    {
        interceptStatus_ = status;
    }

    bool GetInterceptStatus() const
    {
        return interceptStatus_;
    }

    void SetAnimateMode(TabAnimateMode mode);

    TabAnimateMode GetAnimateMode() const
    {
        return animateMode_;
    }

    void SetOnBarDisplayModeChangeEvent(BarDisplayModeChangeEvent&& callback)
    {
        onBarDisplayModeChangeEvent_ = std::move(callback);
    }

    BarDisplayModeChangeEvent GetOnBarDisplayModeChangeEvent() const
    {
        return onBarDisplayModeChangeEvent_;
    }

    void SetOnSideBarChangeEvent(SideBarChangeEvent&& callback)
    {
        onSideBarChangeEvent_ = std::move(callback);
    }

    SideBarChangeEvent GetOnSideBarChangeEvent() const
    {
        return onSideBarChangeEvent_;
    }

    TabBarDisplayMode GetCurrentBarDisplayMode() const
    {
        return currentBarDisplayMode_;
    }

    SideBarStatus GetSideBarStatus() const
    {
        return sideBarStatus_;
    }

    void SetSideBarStatus(SideBarStatus status)
    {
        sideBarStatus_ = status;
    }

    float GetRealSidebarWidth() const
    {
        return realSidebarWidth_;
    }

    void SetRealSidebarWidth(float width)
    {
        realSidebarWidth_ = width;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    bool IsInAnimation() const
    {
        return inAnimation_;
    }

    bool IsAutoHide() const
    {
        return autoHide_;
    }

    void HandleChildrenUpdated(const RefPtr<FrameNode>& swiperNode, const RefPtr<FrameNode>& tabBarNode);

    void UpdateSelectedState(const RefPtr<FrameNode>& swiperNode, const RefPtr<TabBarPattern>& tabBarPattern,
        const RefPtr<TabsLayoutProperty>& tabsLayoutProperty, int index);

    void UpdateDividerStrokeWidth()
    {
        OnUpdateShowDivider();
    }
    void UpdateDividerColor()
    {
        OnUpdateShowDivider();
    }
    int32_t OnInjectionEvent(const std::string& command) override;
    void OnColorConfigurationUpdate() override;
    void OnColorModeChange(uint32_t colorMode) override;
    bool OnThemeScopeUpdate(int32_t themeScopeId) override;
    void DumpInfo() override;

    void OnWindowSizeChanged(int32_t  /*width*/, int32_t  /*height*/, WindowSizeChangeReason type) override;
    void OnAttachToMainTree() override;
    bool OnSaveData(std::string& data) override;
    void OnDetachFromMainTree() override;
    void ResetTabBarFollowHandPosition();
    void SetFloatingBarMargin(std::optional<float> floatingBarMargin)
    {
        floatingBarMargin_ = floatingBarMargin;
    }
    bool IsFloatingBar() const
    {
        return isFloatingBar_;
    }
    bool LastFloatingBar() const
    {
        return lastFloatingBar_;
    }
    void SetFloatingScaleEnabled(bool isFloatingScaleEnabled);

    void SetSidebarHeaderNode(const RefPtr<NG::UINode>& header)
    {
        sidebarHeaderNode_ = header;
    }
    RefPtr<NG::UINode> GetSidebarHeaderNode() const
    {
        return sidebarHeaderNode_;
    }
    void SetSidebarFooterNode(const RefPtr<NG::UINode>& footer)
    {
        sidebarFooterNode_ = footer;
    }
    RefPtr<NG::UINode> GetSidebarFooterNode() const
    {
        return sidebarFooterNode_;
    }
    void SetSidebarSearchableNode(const RefPtr<NG::UINode>& searchable)
    {
        sidebarSearchableNode_ = searchable;
    }
    RefPtr<NG::UINode> GetSidebarSearchableNode() const
    {
        return sidebarSearchableNode_;
    }

private:
    void OnAttachToFrameNode() override;
    void OnAfterModifyDone() override;
    void OnUpdateShowDivider();
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    void BeforeCreateLayoutWrapper() override;
    std::string GetTabBarTextByIndex(int32_t index) const;
    void UpdateSwiperDisableSwipe(bool disableSwipe);
    void SetSwiperPaddingAndBorder();
    void RecordChangeEvent(int32_t index);
    void FireTabContentStateCallback(int32_t oldIndex, int32_t nextIndex) const;
    void FireTabChangeCallback(int32_t preIndex, int32_t nextIndex);
    void FireOnBarDisplayModeChangeEvent(TabBarDisplayMode displayMode);
    void FireOnSideBarChangeEvent(bool isShow);
    void UpdateDisplayModeByBreakpoint();
    TabBarDisplayMode CalculateDisplayMode(float width, double density);
    void OnDisplayModeChanged(TabBarDisplayMode newMode);
    void InitShowAndCloseSidebarPanEvent();
    void HandleDragEndForContent(float xOffset, SidebarPosition position);
    void DoSpringAnimation();
    void UpdateAnimDir();
    void InitDividerDragEvent();
    void UpdateSidebarStatus();
    void StartSidebarTransitionAnimation(bool toShow);
    void FireOnSideBarChangeEventIfNeeded(bool isShow);
    struct SidebarSectionInfo {
        std::string sectionName;
        std::vector<int32_t> tabIndices;
    };
    std::vector<SidebarSectionInfo> ComputeSidebarSections() const;
    std::vector<int32_t> ComputeVisibleTabIndices() const;
    struct SidebarPlacementMap {
        std::vector<int32_t> fixedIndices;
        std::vector<int32_t> customizableIndices;
        std::vector<int32_t> pinnedIndices;
        std::vector<int32_t> sidebarOnlyIndices;
    };
    SidebarPlacementMap ComputeSidebarPlacementMap() const;
    void UpdateBackBlurStyle(const RefPtr<FrameNode>& tabBarNode);
    bool GetTargetIndex(const std::string& command, int32_t& targetIndex);
    // Information on TabChange event
    struct TabChangeInfo {
        int32_t index = 0;
        bool  isShow = false;
        std::optional<int32_t> lastFocusIndex;
    };
    static bool IsValidFireTabChange(const std::optional<TabChangeInfo>& lastTabChangeInfo,
        int32_t index, bool isShow);
    static bool IsNeedFireTabChange(bool isInit,
        int32_t targetIndex, int32_t currentIndex, int32_t preIndex);
    void HandleTabChangeWhenChildrenUpdated(bool isInit, int32_t tabContentNum, int32_t targetIndex);
    void UpdateIndex(const RefPtr<FrameNode>& tabsNode, const RefPtr<FrameNode>& tabBarNode,
        const RefPtr<FrameNode>& swiperNode, const RefPtr<TabsLayoutProperty>& tabsLayoutProperty);
    void InitFocusEvent();
    RefPtr<FocusHub> GetCurrentFocusNode(FocusIntension intension);
    void InitAccessibilityZIndex();

    void InitFloatingBar();
    void UpdateBgMaskNode();
    GradientColor CreatePercentGradientColor(float percent, Color color);
    void InitTouchEvent();
    void OnTouchEvent(const TouchEventInfo& info);
    void FollowHandAnimation();
    void InitTabBarTransformAttributeIfNeeded();
    void HandleOnTouchScaleAnimation();
    void HandleOnTouchDelayScaleAnimation();
    void OnFollowHandAnimationFinish();
    void ApplySystemMaterial();
    void ResetSystemMaterial();

    bool isCustomAnimation_ = false;
    bool isDisableSwipe_ = false;
    bool isInit_ = true;

    TabAnimateMode animateMode_ = TabAnimateMode::CONTENT_FIRST;
    ChangeEventWithPreIndexPtr onChangeEvent_;
    std::shared_ptr<ContentDidScrollEvent> onContentDidScroll_;
    ChangeEventPtr selectedEvent_;
    ChangeEventPtr unselectedEvent_;
    ChangeEventPtr onTabBarClickEvent_;
    ChangeEventPtr onIndexChangeEvent_;
    AnimationStartEventPtr animationStartEvent_;
    AnimationEndEventPtr animationEndEvent_;
    std::function<bool(int32_t, int32_t)> callback_;
    bool interceptStatus_ = false;
    BarPosition barPosition_ = BarPosition::END; // default accessibilityZIndex is consistent with BarPosition::END
    std::optional<TabChangeInfo> lastTabChangeInfo_;

    bool isFloatingBar_ = false;
    bool lastFloatingBar_ = false;
    FloatingBarPosition floatingBarPosition_ = FloatingBarPosition::CENTER;
    RefPtr<TouchEventImpl> touchListener_ = nullptr;
    int32_t floatTabBarFollowHandAnimationCount_ = 0;
    std::list<std::shared_ptr<AnimationUtils::Animation>> floatTabBarFollowHandAnimations_;
    std::optional<float> floatingBarMargin_ = 0.0f;
    float baseFloatingScale_ = FLOATING_BAR_SCALE;

    using BarDisplayModeChangeEvent = std::function<void(TabBarDisplayMode)>;
    using SideBarChangeEvent = std::function<void(bool)>;
    BarDisplayModeChangeEvent onBarDisplayModeChangeEvent_;
    SideBarChangeEvent onSideBarChangeEvent_;
    TabBarDisplayMode currentBarDisplayMode_ = TabBarDisplayMode::BOTTOMTABBAR;
    std::optional<WidthBreakpoint> lastWidthBreakpoint_;

    SideBarStatus sideBarStatus_ = SideBarStatus::SHOW;
    float currentOffset_ = 0.0f;
    bool inAnimation_ = false;
    bool sideBarInDragGesture_ = false;
    float currentContentDragOffset_ = 0.0f;
    float realSidebarWidth_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    bool autoHide_ = false;
    bool userSetShowSideBar_ = true;
    std::shared_ptr<AnimationUtils::Animation> springAnimation_;
    RefPtr<PanEvent> dragEventForCloseSideBar_;
    std::vector<SidebarSectionInfo> sidebarSections_;
    std::vector<int32_t> visibleTabIndices_;
    SidebarPlacementMap sidebarPlacementMap_;
    RefPtr<NG::UINode> sidebarHeaderNode_;
    RefPtr<NG::UINode> sidebarFooterNode_;
    RefPtr<NG::UINode> sidebarSearchableNode_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_PATTERN_H
