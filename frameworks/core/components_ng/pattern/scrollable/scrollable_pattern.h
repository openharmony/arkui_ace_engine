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
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
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
    const RefPtr<GestureEventHub>& GetGestureHub();
    const RefPtr<InputEventHub>& GetInputHub();

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

    float GetCurrentPosition() const
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

    bool IsScrollBarPressed() const
    {
        if (scrollBar_) {
            return scrollBar_->IsPressed();
        }
        return false;
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

protected:
    RefPtr<ScrollBar> GetScrollBar() const
    {
        return scrollBar_;
    }
    RefPtr<NG::ScrollBarProxy> GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }
    void SetScrollBarDriving(bool Driving)
    {
        if (scrollBar_) {
            scrollBar_->SetDriving(Driving);
        }
    }
    void UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset);

private:
    void DraggedDownScrollEndProcess();
    void RegisterScrollBarEventTask();
    void OnScrollEnd();
    bool OnScrollPosition(double offset, int32_t source);
    void SetParentScrollable();

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

    NestedScrollOptions nestedScroll_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
