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

#include "base/geometry/axis.h"
#include "core/animation/select_motion.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace::NG {
#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
#else
constexpr double FRICTION = 0.9;
#endif
class ScrollablePattern : public Pattern {
    DECLARE_ACE_TYPE(ScrollablePattern, Pattern);

public:
    bool IsAtomicNode() const override
    {
        return false;
    }

    // scrollable
    Axis GetAxis() const
    {
        return axis_;
    }
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
    void AddScrollEvent();
    RefPtr<ScrollableEvent> GetScrollableEvent()
    {
        return scrollableEvent_;
    }
    virtual bool OnScrollCallback(float offset, int32_t source);
    virtual void OnScrollEndCallback() {};
    bool ScrollableIdle()
    {
        return !scrollableEvent_ || scrollableEvent_->Idle();
    }
    void SetScrollEnable(bool enable)
    {
        CHECK_NULL_VOID_NOLOG(scrollableEvent_);
        scrollableEvent_->SetEnabled(enable);
    }
    void SetScrollableAxis(Axis axis);
    RefPtr<GestureEventHub> GetGestureHub();
    RefPtr<InputEventHub> GetInputHub();

    // edgeEffect
    const RefPtr<ScrollEdgeEffect>& GetScrollEdgeEffect() const
    {
        return scrollEffect_;
    }
    void SetEdgeEffect(EdgeEffect edgeEffect);
    void AddScrollEdgeEffect(RefPtr<ScrollEdgeEffect> edgeEffect);
    bool HandleEdgeEffect(float offset, int32_t source, const SizeF& size);
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

    void SetScrollBarOutBoundaryExtent(double scrollBarOutBoundaryExtent)
    {
        scrollBarOutBoundaryExtent_ = scrollBarOutBoundaryExtent;
    }

    double GetMainSize(const SizeF& size) const
    {
        return axis_ == Axis::HORIZONTAL ? size.Width() : size.Height();
    }

    void SetCoordinationEvent(RefPtr<ScrollableCoordinationEvent> coordinationEvent)
    {
        coordinationEvent_ = coordinationEvent;
    }

    bool IsScrollableStopped() const
    {
        CHECK_NULL_RETURN_NOLOG(scrollableEvent_, true);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_RETURN_NOLOG(scrollable, true);
        return scrollable->IsStopped();
    }

    void StopScrollable()
    {
        CHECK_NULL_VOID_NOLOG(scrollableEvent_);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID_NOLOG(scrollable);
        scrollable->StopScrollable();
    }

    void StartScrollSnapMotion(float scrollSnapDelta, float scrollSnapVelocity)
    {
        CHECK_NULL_VOID_NOLOG(scrollableEvent_);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID_NOLOG(scrollable);
        scrollable->ProcessScrollSnapSpringMotion(scrollSnapDelta, scrollSnapVelocity);
    }

    bool IsScrollableSpringEffect() const
    {
        CHECK_NULL_RETURN_NOLOG(scrollEffect_, false);
        return scrollEffect_->IsSpringEffect();
    }

    void SetParentDraggedDown(bool isDraggedDown)
    {
        isDraggedDown_ = isDraggedDown;
    }

    void SetCoordEventNeedSpringEffect(bool IsCoordEventNeedSpring)
    {
        isCoordEventNeedSpring_ = IsCoordEventNeedSpring;
    }

    void SetCoordEventNeedMoveUp(bool isCoordEventNeedMoveUp)
    {
        isCoordEventNeedMoveUp_ = isCoordEventNeedMoveUp;
    }
    
    void SetNestedScroll(const NestedScrollOptions& nestedOpt);
    RefPtr<ScrollablePattern> GetParentScrollable();
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

    void StopAnimate();
    bool AnimateRunning() const
    {
        return animator_ && animator_->IsRunning();
    }
    bool AnimateStoped() const
    {
        return !animator_ || animator_->IsStopped();
    }
    void AbortScrollAnimator()
    {
        if (animator_ && !animator_->IsStopped()) {
            scrollAbort_ = true;
            animator_->Stop();
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
            IsScrollable() && (!ScrollableIdle() || animateOverScroll_));
    }
    void MarkSelectedItems();
    bool ShouldSelectScrollBeStopped();

    // scrollSnap
    virtual std::optional<float> CalePredictSnapOffset(float delta)
    {
        std::optional<float> predictSnapPosition;
        return predictSnapPosition;
    }

    virtual bool NeedScrollSnapToSide(float delta)
    {
        return false;
    }

protected:
    RefPtr<ScrollBar> GetScrollBar() const
    {
        return scrollBar_;
    }
    RefPtr<NG::ScrollBarProxy> GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }
    void UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset);

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

private:
    void DraggedDownScrollEndProcess();
    void RegisterScrollBarEventTask();
    void OnScrollEnd();
    bool OnScrollPosition(double offset, int32_t source);
    void SetParentScrollable();

    void OnAttachToFrameNode() override;

    // select with mouse
    virtual void MultiSelectWithoutKeyboard(const RectF& selectedZone) {};
    virtual void ClearMultiSelect() {};
    virtual bool IsItemSelected(const MouseInfo& info)
    {
        return false;
    }
    void ClearInvisibleItemsSelectedStatus();
    void HandleInvisibleItemsSelectedStatus(const RectF& selectedZone);
    void HandleMouseEventWithoutKeyboard(const MouseInfo& info);
    void OnMouseRelease();
    void SelectWithScroll();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    float GetOutOfScrollableOffset() const;

    Axis axis_;
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<ScrollableCoordinationEvent> coordinationEvent_;
    // scrollBar
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<NG::ScrollBarProxy> scrollBarProxy_;
    float barOffset_ = 0.0f;
    float estimatedHeight_ = 0.0f;
    bool isReactInParentMovement_ = false;
    double scrollBarOutBoundaryExtent_ = 0.0;
    bool isDraggedDown_ = false;
    bool isCoordEventNeedSpring_ = true;
    bool isCoordEventNeedMoveUp_ = false;
    double friction_ = FRICTION;
    // scroller
    RefPtr<Animator> animator_;
    RefPtr<SpringMotion> springMotion_;
    bool scrollAbort_ = false;
    bool animateOverScroll_ = false;

    NestedScrollOptions nestedScroll_;

    // select with mouse
    bool mousePressed_ = false;
    OffsetF mouseEndOffset_;
    OffsetF mousePressOffset_;
    MouseInfo lastMouseMove_;
    RefPtr<SelectMotion> selectMotion_;
    RefPtr<InputEvent> mouseEvent_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
