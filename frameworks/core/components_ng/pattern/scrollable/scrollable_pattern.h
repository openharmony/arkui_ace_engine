/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_PATTERN_H

#include <cmath>
#include <vector>

#include "base/geometry/axis.h"
#include "core/animation/select_motion.h"
#include "core/animation/spring_curve.h"
#include "core/animation/bezier_variable_velocity_motion.h"
#include "core/animation/velocity_motion.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/scrollable/refresh_coordination.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/event/mouse_event.h"
#include "core/components_ng/event/scrollable_event.h"
namespace OHOS::Ace::NG {
class InspectorFilter;
#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double API11_FRICTION = 0.7;
constexpr double API12_FRICTION = 0.75;
constexpr double MAX_VELOCITY = 9000.0;
#else
constexpr double FRICTION = 0.9;
constexpr double MAX_VELOCITY = 5000.0;
#endif
enum class ModalSheetCoordinationMode : char {
    UNKNOWN = 0,
    SHEET_SCROLL = 1,
    SCROLLABLE_SCROLL = 2,
};
class ScrollablePattern : public NestableScrollContainer {
    DECLARE_ACE_TYPE(ScrollablePattern, NestableScrollContainer);

public:
    ScrollablePattern();
    ScrollablePattern(EdgeEffect edgeEffect, bool alwaysEnabled);

    ~ScrollablePattern()
    {
        UnRegister2DragDropManager();
        if (scrollBarProxy_) {
            scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
        }
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void OnWindowHide() override;

    // scrollable
    Axis GetAxis() const override
    {
        return axis_;
    }

    virtual bool IsReverse() const
    {
        if (GetAxis() != Axis::HORIZONTAL) {
            return false;
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto layoutProperty = host->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, false);
        auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
        return (layoutDirection == TextDirection::RTL);
    };

    virtual bool ShouldDelayChildPressedState() const override
    {
        return true;
    }

    void RegisterScrollingListener(const RefPtr<ScrollingListener> listener) override;
    void FireAndCleanScrollingListener() override;
    void CleanScrollingListener() override;

    void SetAxis(Axis axis);
    virtual bool UpdateCurrentOffset(float delta, int32_t source) = 0;
    virtual bool IsScrollable() const
    {
        return false;
    }
    virtual bool IsAtTop() const = 0;
    virtual bool IsAtBottom() const = 0;
    virtual bool OutBoundaryCallback()
    {
        return IsOutOfBoundary();
    }

    virtual bool IsOutOfBoundary(bool useCurrentDelta = true)
    {
        return false;
    }

    virtual void OnTouchDown(const TouchEventInfo& info);

    void AddScrollEvent();
    RefPtr<ScrollableEvent> GetScrollableEvent()
    {
        return scrollableEvent_;
    }
    virtual bool OnScrollCallback(float offset, int32_t source);
    virtual void OnScrollStartCallback();
    virtual void FireOnScrollStart();
    virtual void FireOnReachStart(const OnReachEvent& onReachStart) {}
    virtual void FireOnReachEnd(const OnReachEvent& onReachEnd) {}
    bool ScrollableIdle()
    {
        return !scrollableEvent_ || scrollableEvent_->Idle();
    }
    void SetScrollEnabled(bool enabled)
    {
        CHECK_NULL_VOID(scrollableEvent_);
        scrollableEvent_->SetEnabled(enabled);
        if (!enabled) {
            scrollableEvent_->SetAxis(Axis::NONE);
        } else {
            scrollableEvent_->SetAxis(axis_);
        }
        if (scrollBarProxy_) {
            scrollBarProxy_->SetScrollEnabled(enabled, AceType::WeakClaim(this));
        }
    }

    bool GetScrollEnabled() const
    {
        CHECK_NULL_RETURN(scrollableEvent_, false);
        return scrollableEvent_->GetEnabled();
    }

    RefPtr<GestureEventHub> GetGestureHub();
    RefPtr<InputEventHub> GetInputHub();

    // edgeEffect
    const RefPtr<ScrollEdgeEffect>& GetScrollEdgeEffect() const
    {
        return scrollEffect_;
    }
    bool HandleEdgeEffect(float offset, int32_t source, const SizeF& size);
    void HandleFadeEffect(float offset, int32_t source, const SizeF& size,
        bool isNotPositiveScrollableDistance);
    virtual void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) {}
    bool IsRestrictBoundary()
    {
        return !scrollEffect_ || scrollEffect_->IsRestrictBoundary();
    }

    // scrollBar
    virtual void UpdateScrollBarOffset() = 0;
    void SetScrollBar(const std::unique_ptr<ScrollBarProperty>& property);
    void SetScrollBar(DisplayMode displayMode);
    void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy);
    void CreateScrollBarOverlayModifier();

    float GetScrollableDistance() const
    {
        return estimatedHeight_;
    }

    float GetBarOffset() const
    {
        return barOffset_;
    }

    double GetScrollBarOutBoundaryExtent() const
    {
        return scrollBarOutBoundaryExtent_;
    }

    void SetScrollBarOutBoundaryExtent(float scrollBarOutBoundaryExtent)
    {
        scrollBarOutBoundaryExtent_ = scrollBarOutBoundaryExtent;
    }

    void HandleScrollBarOutBoundary(float scrollBarOutBoundaryExtent);

    double GetMainSize(const SizeF& size) const
    {
        return axis_ == Axis::HORIZONTAL ? size.Width() : size.Height();
    }

    bool IsScrollableStopped() const
    {
        CHECK_NULL_RETURN(scrollableEvent_, true);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, true);
        return scrollable->IsStopped();
    }

    bool GetIsDragging() const
    {
        CHECK_NULL_RETURN(scrollableEvent_, false);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, false);
        return scrollable->GetIsDragging();
    }

    void StopScrollable()
    {
        CHECK_NULL_VOID(scrollableEvent_);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID(scrollable);
        scrollable->StopScrollable();
    }

    void StartScrollSnapMotion(float scrollSnapDelta, float scrollSnapVelocity)
    {
        CHECK_NULL_VOID(scrollableEvent_);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID(scrollable);
        scrollable->ProcessScrollSnapSpringMotion(scrollSnapDelta, scrollSnapVelocity);
    }

    bool IsScrollableSpringEffect() const
    {
        CHECK_NULL_RETURN(scrollEffect_, false);
        return scrollEffect_->IsSpringEffect();
    }

    void SetCoordEventNeedSpringEffect(bool IsCoordEventNeedSpring)
    {
        isCoordEventNeedSpring_ = IsCoordEventNeedSpring;
    }

    void GetParentNavigation();
    void GetParentModalSheet();

    /**
     * @brief Return the portion of delta that's in overScroll range.
     *
     * @param delta incoming offset change.
     * @return the portion of delta in overScroll range. Both top overScroll and bottom overScroll.
     */
    virtual OverScrollOffset GetOverScrollOffset(double delta) const
    {
        return { 0, 0 };
    }

    virtual bool OnScrollSnapCallback(double targetOffset, double velocity)
    {
        return false;
    }

    void StartScrollBarAnimatorByProxy()
    {
        if (scrollBarProxy_) {
            scrollBarProxy_->StartScrollBarAnimator();
        }
    }

    void StopScrollBarAnimatorByProxy()
    {
        if (scrollBarProxy_) {
            scrollBarProxy_->StopScrollBarAnimator();
        }
    }

    void SetFriction(double friction);

    double GetFriction() const
    {
        return friction_;
    }

    void SetMaxFlingVelocity(double max);

    double GetMaxFlingVelocity() const
    {
        CHECK_NULL_RETURN(scrollableEvent_, 0.0);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, 0.0);
        return scrollable->GetMaxFlingVelocity();
    }

    virtual void StopAnimate();

    bool AnimateRunning() const
    {
        return (animator_ && animator_->IsRunning()) || !isAnimationStop_;
    }
    bool AnimateStoped() const
    {
        return (!animator_ || animator_->IsStopped()) && isAnimationStop_;
    }

    void AbortScrollAnimator()
    {
        if (animator_ && !animator_->IsStopped()) {
            scrollAbort_ = true;
            animator_->Stop();
        }
        if (!isAnimationStop_) {
            scrollAbort_ = true;
            StopAnimation(springAnimation_);
            StopAnimation(curveAnimation_);
        }
    }
    bool GetScrollAbort() const
    {
        return scrollAbort_;
    }
    void SetScrollAbort(bool abort)
    {
        scrollAbort_ = abort;
    }
    void PlaySpringAnimation(float position, float velocity, float mass, float stiffness, float damping,
                            bool useTotalOffset = true);
    void PlayCurveAnimation(float position, float duration, const RefPtr<Curve>& curve, bool canOverScroll);
    virtual float GetTotalOffset() const
    {
        return 0.0f;
    }
    // main size of all children
    virtual float GetTotalHeight() const
    {
        return 0.0f;
    }
    virtual void OnAnimateStop() {}
    virtual void ScrollTo(float position);
    virtual void AnimateTo(
        float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false,
        bool useTotalOffset = true);
    virtual bool CanOverScroll(int32_t source)
    {
        auto canOverScroll = (IsScrollableSpringEffect() && source != SCROLL_FROM_AXIS && source != SCROLL_FROM_BAR &&
            IsScrollable() && (!ScrollableIdle() || animateOverScroll_ || animateCanOverScroll_));
        if (canOverScroll != lastCanOverScroll_) {
            lastCanOverScroll_ = canOverScroll;
            AddScrollableFrameInfo(source);
        }
        return canOverScroll;
    }
    void MarkSelectedItems();
    bool ShouldSelectScrollBeStopped();
    void UpdateMouseStart(float offset);

    // scrollSnap
    virtual std::optional<float> CalePredictSnapOffset(float delta, float dragDistance, float velocity)
    {
        std::optional<float> predictSnapPosition;
        return predictSnapPosition;
    }

    virtual bool NeedScrollSnapToSide(float delta)
    {
        return false;
    }

    void SetScrollSource(int32_t scrollSource)
    {
        if (scrollSource == SCROLL_FROM_JUMP || scrollSource == SCROLL_FROM_FOCUS_JUMP) {
            if (scrollBar_ && scrollBar_->IsScrollable() && scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(UINT8_MAX);
                scrollBar_->ScheduleDisappearDelayTask();
            }
            StopScrollBarAnimatorByProxy();
            StartScrollBarAnimatorByProxy();
        }
        if (scrollSource == SCROLL_FROM_NONE) {
            if (lastScrollSource_ != scrollSource_) {
                AddScrollableFrameInfo(scrollSource_);
            }
            lastScrollSource_ = scrollSource_;
        }
        scrollSource_ = scrollSource;
    }

    int32_t GetScrollSource() const
    {
        return scrollSource_;
    }

    float GetCurrentVelocity() const
    {
        return currentVelocity_;
    }

    ScrollState GetScrollState() const;

    static ScrollState GetScrollState(int32_t scrollSource);

    static ScrollSource ConvertScrollSource(int32_t source);

    static float CalculateFriction(float gamma)
    {
        constexpr float RATIO = 1.848f;
        if (GreatOrEqual(gamma, 1.0)) {
            gamma = 1.0f;
        }
        return exp(-RATIO * gamma);
    }
    virtual float GetMainContentSize() const;

    virtual bool SupportScrollToIndex() const
    {
        return true;
    }

    virtual ScrollAlign GetDefaultScrollAlign() const
    {
        return ScrollAlign::START;
    }

    virtual void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START,
        std::optional<float> extraOffset = std::nullopt)
    {}

    void SetExtraOffset(std::optional<float> extraOffset)
    {
        extraOffset_ = extraOffset;
    }

    const std::optional<float>& GetExtraOffset() const
    {
        return extraOffset_;
    }

    void ResetExtraOffset()
    {
        extraOffset_.reset();
    }

    virtual void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);

    virtual ScrollEdgeType GetScrollEdgeType() const
    {
        return ScrollEdgeType::SCROLL_NONE;
    }

    virtual void SetScrollEdgeType(ScrollEdgeType scrollEdgeType) {}

    virtual void Fling(double flingVelocity);

    void SetPositionController(RefPtr<ScrollableController> control)
    {
        positionController_ = control;
        if (control) {
            control->SetScrollPattern(AceType::WeakClaim(this));
        }
    }

    RefPtr<ScrollableController> GetOrCreatePositionController()
    {
        if (!positionController_) {
            auto controller = AceType::MakeRefPtr<NG::ScrollableController>();
            SetPositionController(controller);
        }
        return positionController_;
    }

    virtual Rect GetItemRect(int32_t index) const
    {
        return Rect();
    };

    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
    {
        edgeEffect_ = edgeEffect;
        edgeEffectAlwaysEnabled_ = alwaysEnabled;
    }

    EdgeEffect GetEdgeEffect()
    {
        return edgeEffect_;
    }

    bool GetAlwaysEnabled() const
    {
        return edgeEffectAlwaysEnabled_;
    }

    void SetAlwaysEnabled(bool alwaysEnabled)
    {
        edgeEffectAlwaysEnabled_ = alwaysEnabled;
    }

    bool IsScrollableAnimationNotRunning()
    {
        if (scrollableEvent_) {
            auto scrollable = scrollableEvent_->GetScrollable();
            if (scrollable) {
                return scrollable->IsAnimationNotRunning();
            }
            return false;
        }
        return false;
    }

    float GetFinalPosition() const
    {
        return finalPosition_;
    }
    void HandleOnDragStatusCallback(
        const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent) override;

    bool IsScrollableSpringMotionRunning()
    {
        CHECK_NULL_RETURN(scrollableEvent_, false);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, false);
        return scrollable->IsSpringMotionRunning();
    }

    virtual bool IsScrollSnap()
    {
        // When setting snap or enablePaging in scroll, the PARENT_FIRST in nestedScroll_ is invalid
        return false;
    }

    void SetNeedLinked(bool needLinked)
    {
        needLinked_ = needLinked;
    }

    void SetAnimateCanOverScroll(bool animateCanOverScroll)
    {
        bool isScrollable = !(IsAtBottom() && IsAtTop() && !GetAlwaysEnabled());
        animateCanOverScroll_ = isScrollable && animateCanOverScroll;
    }

    virtual std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems()
    {
        std::vector<RefPtr<FrameNode>> children;
        return children;
    }
    void InitScrollBarGestureEvent();

    void ScrollPage(
        bool reverse, bool smooth = false, AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL);

    void PrintOffsetLog(AceLogTag tag, int32_t id, double finalOffset);

    void CheckRestartSpring(bool sizeDiminished, bool needNestedScrolling = true);

    Axis GetScrollablePanDirection()
    {
        CHECK_NULL_RETURN(scrollableEvent_, Axis::NONE);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, Axis::NONE);
        return scrollable->GetPanDirection();
    }

    void AddEventsFiredInfo(ScrollableEventType eventType);

    void AddScrollableFrameInfo(int32_t scrollSource);

    void GetEdgeEffectDumpInfo();

    void GetAxisDumpInfo();

    void GetPanDirectionDumpInfo();
    
    void GetPaintPropertyDumpInfo();

    void GetEventDumpInfo();

    void DumpAdvanceInfo() override;

    void SetScrollToSafeAreaHelper(bool isScrollToSafeAreaHelper)
    {
        isScrollToSafeAreaHelper_ = isScrollToSafeAreaHelper;
    }

    bool IsScrollToSafeAreaHelper() const
    {
        return isScrollToSafeAreaHelper_;
    }

    virtual std::pair<std::function<bool(float)>, Axis> GetScrollOffsetAbility()
    {
        return { nullptr, Axis::NONE };
    }

    virtual std::function<bool(int32_t)> GetScrollIndexAbility()
    {
        return nullptr;
    }

    void ScrollAtFixedVelocity(float velocity);

    PositionMode GetPositionMode();

    void HandleMoveEventInComp(const PointF& point);
    void HandleLeaveHotzoneEvent();
    void SetHotZoneScrollCallback(std::function<void(void)>&& func)
    {
        hotZoneScrollCallback_ = func;
    }

    virtual void SetAccessibilityAction();

    void SetUseTotalOffset(bool useTotalOffset)
    {
        useTotalOffset_ = useTotalOffset;
    }

    bool GetNestedScrolling() const
    {
        CHECK_NULL_RETURN(scrollableEvent_, false);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN(scrollable, false);
        return scrollable->GetNestedScrolling();
    }

protected:
    void SuggestOpIncGroup(bool flag);
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    virtual DisplayMode GetDefaultScrollBarDisplayMode() const
    {
        return DisplayMode::AUTO;
    }
    RefPtr<ScrollBar> GetScrollBar() const
    {
        return scrollBar_;
    }
    RefPtr<NG::ScrollBarProxy> GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }
    void UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset);

    EdgeEffect GetEdgeEffect() const;
    void SetEdgeEffect()
    {
        SetEdgeEffect(edgeEffect_);
    }

    virtual void FireOnScroll(float finalOffset, OnScrollEvent& onScroll) const;

    void FireObserverOnTouch(const TouchEventInfo& info);
    void FireObserverOnPanActionEnd(GestureEvent& info);
    void FireObserverOnReachStart();
    void FireObserverOnReachEnd();
    void FireObserverOnScrollStart();
    void FireObserverOnScrollStop();
    void FireObserverOnDidScroll(float finalOffset);

    virtual void OnScrollStop(const OnScrollStopEvent& onScrollStop);

    float FireOnWillScroll(float offset) const;

    // select with mouse
    struct ItemSelectedStatus {
        std::function<void(bool)> onSelected;
        std::function<void(bool)> selectChangeEvent;
        RectF rect;
        bool selected = false;
        void FireSelectChangeEvent(bool isSelected)
        {
            if (selected == isSelected) {
                return;
            }
            selected = isSelected;
            if (onSelected) {
                onSelected(isSelected);
            }
            if (selectChangeEvent) {
                selectChangeEvent(isSelected);
            }
        }
    };
    void InitMouseEvent();
    void UninitMouseEvent();
    void DrawSelectedZone(const RectF& selectedZone);
    void ClearSelectedZone();
    bool multiSelectable_ = false;
    bool isMouseEventInit_ = false;
    OffsetF mouseStartOffset_;
    float totalOffsetOfMousePressed_ = 0.0f;
    std::unordered_map<int32_t, ItemSelectedStatus> itemToBeSelected_;
    bool animateOverScroll_ = false;
    bool animateCanOverScroll_ = false;
    bool lastCanOverScroll_ = false;

    RefPtr<ScrollBarOverlayModifier> GetScrollBarOverlayModifier() const
    {
        return scrollBarOverlayModifier_;
    }

    void SetScrollBarOverlayModifier(RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier)
    {
        scrollBarOverlayModifier_ = scrollBarOverlayModifier;
    }
    // just for hold ScrollableController
    RefPtr<ScrollableController> positionController_;

    bool scrollStop_ = false;

    // for onReachStart of the first layout
    bool isInitialized_ = false;

    void Register2DragDropManager();

    void SetScrollOriginChild(const WeakPtr<NestableScrollContainer>& scrollOriginChild)
    {
        scrollOriginChild_ = scrollOriginChild;
    }

    RefPtr<NestableScrollContainer> GetScrollOriginChild()
    {
        return scrollOriginChild_.Upgrade();
    }

    void SetCanOverScroll(bool val);
    bool GetCanOverScroll() const;

    void CheckScrollBarOff();

private:
    virtual void OnScrollEndCallback() {};

    void RegisterScrollBarEventTask();
    bool OnScrollPosition(double& offset, int32_t source);
    void ProcessNavBarReactOnStart();
    float ProcessNavBarReactOnUpdate(float offset);
    void ProcessNavBarReactOnEnd();
    void InitSpringOffsetProperty();
    void InitCurveOffsetProperty();
    void OnAnimateFinish();
    void StopAnimation(std::shared_ptr<AnimationUtils::Animation> animation);
    void PauseAnimation(std::shared_ptr<AnimationUtils::Animation> animation);
    void InitOption(AnimationOption &option, float duration, const RefPtr<Curve>& curve);
    float GetScrollDelta(float offset, bool& stopAnimation);

    void OnAttachToFrameNode() override;
    void AttachAnimatableProperty(RefPtr<Scrollable> scrollable);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void RegisterWindowStateChangedCallback();

    // select with mouse
    virtual void MultiSelectWithoutKeyboard(const RectF& selectedZone) {};
    virtual void ClearMultiSelect() {};
    virtual bool IsItemSelected(const GestureEvent& info)
    {
        return false;
    }
    void ClearInvisibleItemsSelectedStatus();
    void HandleInvisibleItemsSelectedStatus(const RectF& selectedZone);
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd();
    void SelectWithScroll();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    float GetOutOfScrollableOffset() const;
    virtual float GetOffsetWithLimit(float offset) const;
    void LimitMouseEndOffset();
    void UpdateBorderRadius();

    /******************************************************************************
     * NestableScrollContainer implementations
     */
    ScrollResult HandleScroll(
        float offset, int32_t source, NestedState state = NestedState::GESTURE, float velocity = 0.f) override;
    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;

    void RemainVelocityToChild(float remainVelocity) override;
    bool NestedScrollOutOfBoundary() override
    {
        return OutBoundaryCallback();
    }
    void UpdateNestedScrollVelocity(float offset, NestedState state);
    float GetNestedScrollVelocity();

    void OnScrollEndRecursive(const std::optional<float>& velocity) override;
    void OnScrollEndRecursiveInner(const std::optional<float>& velocity);
    void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity = 0.f) override;
    void OnScrollStartRecursiveInner(WeakPtr<NestableScrollContainer> child, float position, float velocity = 0.f);
    void OnScrollDragEndRecursive() override;
    void StopScrollAnimation() override;

    ScrollResult HandleScrollParentFirst(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollSelfFirst(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollSelfOnly(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollParallel(float& offset, int32_t source, NestedState state);
    bool HandleOutBoundary(float& offset, int32_t source, NestedState state, ScrollResult& result);
    bool HandleSelfOutBoundary(float& offset, int32_t source, const float backOverOffset, float oppositeOverOffset);

    void ExecuteScrollFrameBegin(float& mainDelta, ScrollState state);

    void OnScrollEnd();
    void ProcessSpringEffect(float velocity, bool needRestart = false);
    void SetEdgeEffect(EdgeEffect edgeEffect);

    // Scrollable::UpdateScrollPosition
    bool HandleScrollImpl(float offset, int32_t source);
    void NotifyMoved(bool value);

    /*
     *  End of NestableScrollContainer implementations
     *******************************************************************************/

    bool HandleOverScroll(float velocity);
    bool HandleScrollableOverScroll(float velocity);

    void CreateRefreshCoordination()
    {
        if (!refreshCoordination_) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(host);
        }
    }
    float GetVelocity() const;
    bool NeedSplitScroll(OverScrollOffset& overOffsets, int32_t source);
    RefreshCoordinationMode CoordinateWithRefresh(double& offset, int32_t source, bool isAtTop);
    bool CoordinateWithNavigation(double& offset, int32_t source, bool isAtTop);
    void NotifyFRCSceneInfo(const std::string& scene, double velocity, SceneStatus sceneStatus);
    ModalSheetCoordinationMode CoordinateWithSheet(double& offset, int32_t source, bool isAtTop);
    bool NeedCoordinateScrollWithNavigation(double offset, int32_t source, const OverScrollOffset& overOffsets);
    void SetUiDvsyncSwitch(bool on);
    void SetNestedScrolling(bool nestedScrolling);

    Axis axis_ = Axis::VERTICAL;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<RefreshCoordination> refreshCoordination_;
    int32_t scrollSource_ = SCROLL_FROM_NONE;
    int32_t lastScrollSource_ = SCROLL_FROM_NONE;
    // scrollBar
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<NG::ScrollBarProxy> scrollBarProxy_;
    RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
    float barOffset_ = 0.0f;
    float estimatedHeight_ = 0.0f;
    bool isReactInParentMovement_ = false;
    bool isRefreshInReactive_ = false; // true if Refresh component is ready to receive scroll offset.
    bool isSheetInReactive_ = false;
    bool isCoordEventNeedSpring_ = true;
    double scrollBarOutBoundaryExtent_ = 0.0;
    double friction_ = 0.0;
    double maxFlingVelocity_ = MAX_VELOCITY;
    // scroller
    RefPtr<Animator> animator_;
    bool scrollAbort_ = false;
    bool isAnimateOverScroll_ = false;
    bool isScrollToSafeAreaHelper_ = true;
    bool inScrollingStatus_ = false;
    bool switchOnStatus_ = false;

    // select with mouse
    enum SelectDirection { SELECT_DOWN, SELECT_UP, SELECT_NONE };
    SelectDirection selectDirection_ = SELECT_NONE;
    bool mousePressed_ = false;
    bool canMultiSelect_ = false;
    OffsetF mouseEndOffset_;
    OffsetF mousePressOffset_;
    OffsetF lastMouseStart_;
    GestureEvent lastMouseMove_;
    RefPtr<SelectMotion> selectMotion_;
    RefPtr<PanEvent> boxSelectPanEvent_;

    RefPtr<NavBarPattern> navBarPattern_;
    RefPtr<SheetPresentationPattern> sheetPattern_;
    std::vector<RefPtr<ScrollingListener>> scrollingListener_;

    EdgeEffect edgeEffect_ = EdgeEffect::NONE;
    bool edgeEffectAlwaysEnabled_ = false;
    bool needLinked_ = true;

    RefPtr<NodeAnimatablePropertyFloat> springOffsetProperty_;
    RefPtr<NodeAnimatablePropertyFloat> curveOffsetProperty_;
    std::shared_ptr<AnimationUtils::Animation> springAnimation_;
    std::shared_ptr<AnimationUtils::Animation> curveAnimation_;
    uint64_t lastVsyncTime_ = 0;
    bool isAnimationStop_ = true; // graphic animation flag
    float currentVelocity_ = 0.0f;
    float lastPosition_ = 0.0f;
    float finalPosition_ = 0.0f;
    bool useTotalOffset_ = true;
    bool animateToTraceFlag_ = false;
    std::optional<float> extraOffset_;

    RefPtr<Animator> hotzoneAnimator_;
    float lastHonezoneOffsetPct_ = 0.0f;
    RefPtr<BezierVariableVelocityMotion> velocityMotion_;
    RefPtr<VelocityMotion> fixedVelocityMotion_;
    std::function<void(void)> hotZoneScrollCallback_;
    void UnRegister2DragDropManager();
    float IsInHotZone(const PointF& point);
    void HotZoneScroll(const float offset);
    void StopHotzoneScroll();
    void HandleHotZone(const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent);
    bool isVertical() const;
    RefPtr<ClickRecognizer> clickRecognizer_;
    Offset locationInfo_;
    WeakPtr<NestableScrollContainer> scrollOriginChild_;
    float nestedScrollVelocity_ = 0.0f;
    uint64_t nestedScrollTimestamp_ = 0;

    // dump info
    std::list<ScrollableEventsFiredInfo> eventsFiredInfos_;
    std::list<ScrollableFrameInfo> scrollableFrameInfos_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
