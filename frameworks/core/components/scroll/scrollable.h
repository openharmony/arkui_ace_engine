/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_H

#include <functional>

#include "base/geometry/dimension.h"
#include "core/animation/animator.h"
#include "core/animation/friction_motion.h"
#include "core/animation/scroll_motion.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/pan_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/gestures/timeout_recognizer.h"
#include "core/pipeline/base/related_node.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

struct ScrollInfo {
    Dimension dx;
    Dimension dy;

    bool operator==(const ScrollInfo& scrollInfo) const
    {
        return dx == scrollInfo.dx && dy == scrollInfo.dy;
    }
};

constexpr int32_t SCROLL_FROM_NONE = 0;
constexpr int32_t SCROLL_FROM_UPDATE = 1;
constexpr int32_t SCROLL_FROM_ANIMATION = 2;
constexpr int32_t SCROLL_FROM_JUMP = 3;
constexpr int32_t SCROLL_FROM_ANIMATION_SPRING = 4;
constexpr int32_t SCROLL_FROM_CHILD = 5;
constexpr int32_t SCROLL_FROM_BAR = 6;
constexpr int32_t SCROLL_FROM_FOCUS_JUMP = 7;
constexpr int32_t SCROLL_FROM_ROTATE = 8;
constexpr int32_t SCROLL_FROM_INDEXER = 9;
constexpr int32_t SCROLL_FROM_START = 10; // from drag start
constexpr int32_t SCROLL_FROM_AXIS = 11;

using ScrollPositionCallback = std::function<bool(double, int32_t source)>;
using ScrollEventCallback = std::function<void()>;
using OutBoundaryCallback = std::function<bool()>;
using ScrollOverCallback = std::function<void(double velocity)>;
using WatchFixCallback = std::function<double(double final, double current)>;
using ScrollBeginCallback = std::function<ScrollInfo(Dimension, Dimension)>;
using DragEndForRefreshCallback = std::function<void()>;
using DragCancelRefreshCallback = std::function<void()>;

class Scrollable : public TouchEventTarget, public RelatedChild {
    DECLARE_ACE_TYPE(Scrollable, TouchEventTarget);

public:
    Scrollable() = default;
    Scrollable(ScrollPositionCallback&& callback, Axis axis) : callback_(std::move(callback)), axis_(axis) {}
    Scrollable(const ScrollPositionCallback& callback, Axis axis) : callback_(callback), axis_(axis) {}
    ~Scrollable() override;

    static void SetVelocityScale(double sVelocityScale);
    static void SetFriction(double sFriction);

    void Initialize(const WeakPtr<PipelineBase>& context);

    bool IsMotionStop() const
    {
        return (springController_ ? (!springController_->IsRunning()) : true) &&
               (controller_ ? (!controller_->IsRunning()) : true) && !moved_;
    }

    bool IsSpringMotionRunning() const
    {
        return springController_ ? springController_->IsRunning() : false;
    }

    bool IsDragging() const
    {
        return isTouching_ && controller_->IsRunning();
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    void SetScrollableNode(const WeakPtr<RenderNode>& node)
    {
        scrollableNode_ = node;
    }

    double GetMainOffset(const Offset& offset) const
    {
        return axis_ == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    }

    double GetMainSize(const Size& size) const
    {
        return axis_ == Axis::HORIZONTAL ? size.Width() : size.Height();
    }

    void SetCallback(const ScrollPositionCallback& callback)
    {
        callback_ = callback;
    }

    void SetCoordinateOffset(const Offset& offset) const
    {
        if (panRecognizer_) {
            panRecognizer_->SetCoordinateOffset(offset);
        }

        if (rawRecognizer_) {
            rawRecognizer_->SetCoordinateOffset(offset);
        }
    }

    void SetDragTouchRestrict(const TouchRestrict& touchRestrict)
    {
        if (panRecognizer_) {
            panRecognizer_->SetTouchRestrict(touchRestrict);
        }
    }

    void SetScrollEndCallback(const ScrollEventCallback& scrollEndCallback)
    {
        scrollEndCallback_ = scrollEndCallback;
    }

    void SetScrollTouchUpCallback(const ScrollEventCallback& scrollTouchUpCallback)
    {
        scrollTouchUpCallback_ = scrollTouchUpCallback;
    }

    void HandleTouchDown();
    void HandleTouchUp();
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);

    void ProcessScrollMotionStop();

    bool DispatchEvent(const TouchEvent& point) override
    {
        return true;
    }
    bool HandleEvent(const TouchEvent& event) override
    {
        if (!available_) {
            return true;
        }
        if (panRecognizer_) {
            panRecognizer_->HandleEvent(event);
        }
        if (rawRecognizer_) {
            return rawRecognizer_->HandleEvent(event);
        }
        return true;
    }
    bool HandleEvent(const AxisEvent& event) override
    {
        if (panRecognizer_) {
            return panRecognizer_->HandleEvent(event);
        }
        return false;
    }

    void SetScrollEnd(const ScrollEventCallback& scrollEnd)
    {
        scrollEnd_ = scrollEnd;
    }

    void SetScrollOverCallBack(const ScrollOverCallback& scrollOverCallback)
    {
        scrollOverCallback_ = scrollOverCallback;
    }

    void SetNotifyScrollOverCallBack(const ScrollOverCallback& scrollOverCallback)
    {
        notifyScrollOverCallback_ = scrollOverCallback;
    }

    void SetOutBoundaryCallback(const OutBoundaryCallback& outBoundaryCallback)
    {
        outBoundaryCallback_ = outBoundaryCallback;
    }

    void SetDragEndCallback(const DragEndForRefreshCallback& dragEndCallback)
    {
        dragEndCallback_ = dragEndCallback;
    }

    void SetDragCancelCallback(const DragCancelRefreshCallback& dragCancelCallback)
    {
        dragCancelCallback_ = dragCancelCallback;
    }

    const DragEndForRefreshCallback& GetDragEndCallback() const
    {
        return dragEndCallback_;
    }

    const DragCancelRefreshCallback& GetDragCancelCallback() const
    {
        return dragCancelCallback_;
    }

    void SetWatchFixCallback(const WatchFixCallback& watchFixCallback)
    {
        watchFixCallback_ = watchFixCallback;
    }

    void MarkNeedCenterFix(bool needFix)
    {
        needCenterFix_ = needFix;
    }

    double GetCurrentVelocity() const
    {
        return currentVelocity_;
    };

    void StartSpringMotion(
        double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent);

    bool IsAnimationNotRunning() const;

    bool Idle() const;

    bool IsStopped() const;

    void StopScrollable();

    bool Available() const
    {
        return available_;
    }

    void MarkAvailable(bool available)
    {
        available_ = available;
    }

    WeakPtr<PipelineBase> GetContext() const
    {
        return context_;
    }

    void SetNodeId(int32_t nodeId)
    {
        nodeId_ = nodeId;
    }

    void ProcessScrollOverCallback(double velocity);

    void SetSlipFactor(double SlipFactor);

    void SetOverSpringProperty(const RefPtr<SpringProperty>& property)
    {
        if (property && property->IsValid()) {
            spring_ = property;
        }
    }

    void ChangeMoveStatus(bool flag)
    {
        moved_ = flag;
    }

    static const RefPtr<SpringProperty>& GetDefaultOverSpringProperty();

    RefPtr<PanRecognizer> GetPanRecognizer() const
    {
        return panRecognizer_;
    }

    void SetOnScrollBegin(const ScrollBeginCallback& scrollBeginCallback)
    {
        scrollBeginCallback_ = scrollBeginCallback;
    }

    void OnFlushTouchEventsBegin() override;
    void OnFlushTouchEventsEnd() override;

private:
    bool UpdateScrollPosition(double offset, int32_t source) const;
    void ProcessSpringMotion(double position);
    void ProcessScrollMotion(double position);
    void FixScrollMotion(double position);
    void ExecuteScrollBegin(double& mainDelta);

    ScrollPositionCallback callback_;
    ScrollEventCallback scrollEnd_;
    ScrollEventCallback scrollEndCallback_;
    ScrollEventCallback scrollTouchUpCallback_;
    ScrollOverCallback scrollOverCallback_;       // scroll motion controller when edge set to spring
    ScrollOverCallback notifyScrollOverCallback_; // scroll motion controller when edge set to spring
    OutBoundaryCallback outBoundaryCallback_;     // whether out of boundary check when edge set to spring

    WatchFixCallback watchFixCallback_;
    ScrollBeginCallback scrollBeginCallback_;
    DragEndForRefreshCallback dragEndCallback_;
    DragCancelRefreshCallback dragCancelCallback_;
    Axis axis_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<Animator> controller_;
    RefPtr<Animator> springController_;
    RefPtr<FrictionMotion> motion_;
    RefPtr<ScrollMotion> scrollMotion_;
    RefPtr<SpringProperty> spring_;
    WeakPtr<PipelineBase> context_;
    WeakPtr<RenderNode> scrollableNode_;
    double currentPos_ = 0.0;
    double currentVelocity_ = 0.0;
    bool scrollPause_ = false;
    bool touchUp_ = false;
    bool moved_ = false;
    bool isTouching_ = false;
    bool available_ = true;
    bool needCenterFix_ = false;
    bool isDragUpdateStop_ = false;
    int32_t nodeId_ = 0;
    double slipFactor_ = 0.0;
    static double sFriction_;
    static double sVelocityScale_;
#ifdef OHOS_PLATFORM
    int64_t startIncreaseTime_ = 0;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_H
