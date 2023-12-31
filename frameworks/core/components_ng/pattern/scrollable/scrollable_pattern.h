/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double NEW_FRICTION = 0.7;
constexpr double MAX_VELOCITY = 800000.0;
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
    ScrollablePattern() = default;
    ScrollablePattern(EdgeEffect edgeEffect, bool alwaysEnabled);

    ~ScrollablePattern()
    {
        UnRegister2DragDropManager();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    // scrollable
    Axis GetAxis() const override
    {
        return axis_;
    }

    virtual bool IsReverse() const
    {
        return false;
    };

    virtual bool ShouldDelayChildPressedState() const override
    {
        return true;
    }

    void RegisterScrollingListener(const RefPtr<ScrollingListener> listener) override;
    void FireAndCleanScrollingListener() override;

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
        return IsAtTop() || IsAtBottom();
    }

    virtual bool IsOutOfBoundary(bool useCurrentDelta = true)
    {
        return false;
    }

    void AddScrollEvent();
    RefPtr<ScrollableEvent> GetScrollableEvent()
    {
        return scrollableEvent_;
    }
    virtual bool OnScrollCallback(float offset, int32_t source);
    virtual void OnScrollStartCallback();
    virtual void FireOnScrollStart();
    bool ScrollableIdle()
    {
        return !scrollableEvent_ || scrollableEvent_->Idle();
    }
    void SetScrollEnable(bool enable)
    {
        CHECK_NULL_VOID(scrollableEvent_);
        scrollableEvent_->SetEnabled(enable);
        if (!enable) {
            scrollableEvent_->SetAxis(Axis::NONE);
        } else {
            scrollableEvent_->SetAxis(axis_);
        }
    }

    RefPtr<GestureEventHub> GetGestureHub();
    RefPtr<InputEventHub> GetInputHub();

    // edgeEffect
    const RefPtr<ScrollEdgeEffect>& GetScrollEdgeEffect() const
    {
        return scrollEffect_;
    }
    bool HandleEdgeEffect(float offset, int32_t source, const SizeF& size, bool reverse = false);
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

    void SetScrollFrameBeginCallback(const ScrollFrameBeginCallback& scrollFrameBeginCallback)
    {
        // Previous: Set to Scrollable and called in HandleScroll
        // Now: HandleScroll moved to base class, directly store and call scrollFrameBeginCallback_ here
        scrollFrameBeginCallback_ = scrollFrameBeginCallback;
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

    void SetNestedScroll(const NestedScrollOptions& nestedOpt);
    void GetParentNavigation();
    void GetParentModalSheet();

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

    void StopAnimate();
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
    void PlaySpringAnimation(float position, float velocity, float mass, float stiffness, float damping);
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
    virtual void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth);
    bool CanOverScroll(int32_t source)
    {
        return (IsScrollableSpringEffect() && source != SCROLL_FROM_AXIS && source != SCROLL_FROM_BAR &&
            source != SCROLL_FROM_NONE && IsScrollable() && (!ScrollableIdle() || animateOverScroll_));
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

    virtual void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START) {}

    virtual void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);

    void SetPositionController(RefPtr<ScrollableController> control)
    {
        positionController_ = control;
        if (control) {
            control->SetScrollPattern(AceType::WeakClaim(this));
        }
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

protected:
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

    virtual void OnScrollStop(const OnScrollStopEvent& onScrollStop);

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

private:
    virtual void OnScrollEndCallback() {};

    void RegisterScrollBarEventTask();
    bool OnScrollPosition(double& offset, int32_t source);
    void SetParentScrollable();
    void ProcessNavBarReactOnStart();
    float ProcessNavBarReactOnUpdate(float offset);
    void ProcessNavBarReactOnEnd();
    void InitSpringOffsetProperty();
    void InitCurveOffsetProperty(float position);
    void StopAnimation(std::shared_ptr<AnimationUtils::Animation> animation);
    void InitOption(AnimationOption &option, float duration, const RefPtr<Curve>& curve);

    void OnAttachToFrameNode() override;
    void AttachAnimatableProperty(RefPtr<Scrollable> scrollable);

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
    void HandleDragEnd(const GestureEvent& info);
    void SelectWithScroll();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    float GetOutOfScrollableOffset() const;
    virtual float GetOffsetWithLimit(float offset) const;
    void LimitMouseEndOffset();
    void UpdateBorderRadius();

    /******************************************************************************
     * NestableScrollContainer implementations
     */
    ScrollResult HandleScroll(float offset, int32_t source, NestedState state = NestedState::GESTURE) override;
    bool HandleScrollVelocity(float velocity) override;

    void OnScrollEndRecursive(const std::optional<float>& velocity) override;
    void OnScrollStartRecursive(float position) override;

    ScrollResult HandleScrollParentFirst(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollSelfFirst(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollSelfOnly(float& offset, int32_t source, NestedState state);
    ScrollResult HandleScrollParallel(float& offset, int32_t source, NestedState state);

    void ExecuteScrollFrameBegin(float& mainDelta, ScrollState state);

    void SetCanOverScroll(bool val);
    bool GetCanOverScroll() const;

    void OnScrollEnd();
    void ProcessSpringEffect(float velocity);
    void SetEdgeEffect(EdgeEffect edgeEffect);

    // Scrollable::UpdateScrollPosition
    bool HandleScrollImpl(float offset, int32_t source);
    void NotifyMoved(bool value);

    WeakPtr<NestableScrollContainer> parent_;
    ScrollFrameBeginCallback scrollFrameBeginCallback_;
    /*
     *  End of NestableScrollContainer implementations
     *******************************************************************************/

    bool HandleOverScroll(float velocity);

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

    Axis axis_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<RefreshCoordination> refreshCoordination_;
    int32_t scrollSource_ = SCROLL_FROM_NONE;
    // scrollBar
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<NG::ScrollBarProxy> scrollBarProxy_;
    RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
    float barOffset_ = 0.0f;
    float estimatedHeight_ = 0.0f;
    bool isReactInParentMovement_ = false;
    bool isRefreshInReactive_ = false;
    bool isSheetInReactive_ = false;
    bool isCoordEventNeedSpring_ = true;
    double scrollBarOutBoundaryExtent_ = 0.0;
    double friction_ = 0.0;
    double maxFlingVelocity_ = MAX_VELOCITY;
    // scroller
    RefPtr<Animator> animator_;
    bool scrollAbort_ = false;
    bool animateOverScroll_ = false;

    NestedScrollOptions nestedScroll_;

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

    RefPtr<NodeAnimatablePropertyFloat> springOffsetProperty_;
    RefPtr<NodeAnimatablePropertyFloat> curveOffsetProperty_;
    std::shared_ptr<AnimationUtils::Animation> springAnimation_;
    std::shared_ptr<AnimationUtils::Animation> curveAnimation_;
    std::chrono::high_resolution_clock::time_point lastTime_;
    bool isAnimationStop_ = true; // graphic animation flag
    float currentVelocity_ = 0.0f;
    float lastPosition_ = 0.0f;
    float finalPosition_ = 0.0f;
    uint32_t runningAnimationCount_ = 0;

    RefPtr<Animator> hotzoneAnimator_;
    float lastHonezoneOffsetPct_ = 0.0f;
    RefPtr<BezierVariableVelocityMotion> velocityMotion_;
    void UnRegister2DragDropManager();
    float IsInHotZone(const PointF& point);
    void HotZoneScroll(const float offset);
    void StopHotzoneScroll();
    void HandleHotZone(const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent);
    void HandleMoveEventInComp(const PointF& point);
    void HandleLeaveHotzoneEvent();
    bool isVertical() const;
    void AddHotZoneSenceInterface(SceneStatus scene);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
