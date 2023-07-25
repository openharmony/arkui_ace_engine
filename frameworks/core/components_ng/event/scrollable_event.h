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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_H

#include <list>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HTMBLOCK_VELOCITY = 20;
}

class GestureEventHub;

using BarCollectTouchTargetCallback = std::function<void(const OffsetF&, const GetEventTargetImpl&, TouchTestResult&)>;
using InBarRegionCallback = std::function<bool(const PointF&, SourceType source)>;

class ScrollableEvent : public AceType {
    DECLARE_ACE_TYPE(ScrollableEvent, AceType)
public:
    explicit ScrollableEvent(Axis axis) : axis_(axis) {};
    ~ScrollableEvent() override = default;

    void SetScrollPositionCallback(ScrollPositionCallback&& callback)
    {
        if (!callback) {
            return;
        }
        callback_ = std::move(callback);
    }

    const ScrollPositionCallback& GetScrollPositionCallback() const
    {
        return callback_;
    }

    void SetScrollBeginCallback(ScrollBeginCallback&& scrollBeginCallback)
    {
        scrollBeginCallback_ = std::move(scrollBeginCallback);
        if (scrollable_) {
            scrollable_->SetOnScrollBegin(scrollBeginCallback_);
        }
    }

    const ScrollBeginCallback& GetScrollBeginCallback() const
    {
        return scrollBeginCallback_;
    }

    void SetScrollFrameBeginCallback(ScrollFrameBeginCallback&& scrollFrameBeginCallback)
    {
        scrollFrameBeginCallback_ = std::move(scrollFrameBeginCallback);
        if (scrollable_) {
            scrollable_->SetOnScrollFrameBegin(scrollFrameBeginCallback_);
        }
    }

    const ScrollFrameBeginCallback& GetScrollFrameBeginCallback() const
    {
        return scrollFrameBeginCallback_;
    }

    void SetScrollEndCallback(ScrollEndCallback&& scrollEndCallback)
    {
        if (!scrollEndCallback) {
            return;
        }
        scrollEndCallback_ = std::move(scrollEndCallback);
    }

    const ScrollEndCallback& GetScrollEndCallback() const
    {
        return scrollEndCallback_;
    }

    void SetOutBoundaryCallback(OutBoundaryCallback&& outBoundaryCallback)
    {
        if (!outBoundaryCallback) {
            return;
        }
        outBoundaryCallback_ = std::move(outBoundaryCallback);
    }

    const OutBoundaryCallback& GetOutBoundaryCallback() const
    {
        return outBoundaryCallback_;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
        if (scrollable_) {
            scrollable_->SetAxis(axis);
        }
    }

    void SetScrollable(const RefPtr<Scrollable>& scrollable)
    {
        scrollable_ = scrollable;
    }

    const RefPtr<Scrollable>& GetScrollable() const
    {
        return scrollable_;
    }

    void SetEnabled(bool enable)
    {
        enable_ = enable;
    }

    bool GetEnable() const
    {
        return enable_;
    }

    bool Idle() const
    {
        if (scrollable_) {
            return scrollable_->Idle();
        }
        return true;
    }

    bool IsHitTestBlock() const
    {
        if (scrollable_ && !scrollable_->Idle()) {
            return std::abs(scrollable_->GetCurrentVelocity()) > SystemProperties::Vp2Px(HTMBLOCK_VELOCITY);
        }
        return false;
    }

    void SetFriction(double friction)
    {
        friction_ = friction;
        if (scrollable_) {
            scrollable_->SetUnstaticFriction(friction_);
        }
    }

    double GetFriction() const
    {
        return friction_;
    }

    void SetBarCollectTouchTargetCallback(const BarCollectTouchTargetCallback&& barCollectTouchTarget)
    {
        barCollectTouchTarget_ = std::move(barCollectTouchTarget);
    }

    void SetInBarRegionCallback(const InBarRegionCallback&& inBarRegionCallback)
    {
        inBarRegionCallback_ = std::move(inBarRegionCallback);
    }

    bool InBarRegion(const PointF& localPoint, SourceType source) const
    {
        return inBarRegionCallback_ && barCollectTouchTarget_ && inBarRegionCallback_(localPoint, source);
    }

    void BarCollectTouchTarget(const OffsetF& coordinateOffset,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
    {
        if (barCollectTouchTarget_) {
            barCollectTouchTarget_(coordinateOffset, getEventTargetImpl, result);
        }
    }

private:
    ScrollPositionCallback callback_;
    ScrollBeginCallback scrollBeginCallback_;
    ScrollFrameBeginCallback scrollFrameBeginCallback_;
    ScrollEndCallback scrollEndCallback_;
    OutBoundaryCallback outBoundaryCallback_;

    Axis axis_ = Axis::VERTICAL;
    bool enable_ = true;
    RefPtr<Scrollable> scrollable_;
    BarCollectTouchTargetCallback barCollectTouchTarget_;
    InBarRegionCallback inBarRegionCallback_;
    double friction_ = -1.0;
};

class ScrollableActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(ScrollableActuator, GestureEventActuator)
public:
    explicit ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~ScrollableActuator() override = default;

    void AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        scrollableEvents_[scrollableEvent->GetAxis()] = scrollableEvent;
        if (scrollableEvent && !scrollableEvent->GetScrollable()) {
            InitializeScrollable(scrollableEvent);
        }
    }

    void RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        scrollableEvents_.erase(scrollableEvent->GetAxis());
    }

    void AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& effect);
    bool RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& effect);

    void CollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const PointF& localPoint)
    {
        for (const auto& [axis, event] : scrollableEvents_) {
            if (!event || !event->GetEnable()) {
                continue;
            }
            if (event->InBarRegion(localPoint, touchRestrict.sourceType)) {
                event->BarCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
            } else {
                const auto& scrollable = event->GetScrollable();
                scrollable->SetGetEventTargetImpl(getEventTargetImpl);
                scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
                scrollable->OnCollectTouchTarget(result);
            }
        }
    }

    bool IsHitTestBlock() const;

private:
    void InitializeScrollable(RefPtr<ScrollableEvent> event);

    std::unordered_map<Axis, RefPtr<ScrollableEvent>> scrollableEvents_;
    std::unordered_map<Axis, RefPtr<ScrollEdgeEffect>> scrollEffects_;
    WeakPtr<GestureEventHub> gestureEventHub_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_HUB_H
