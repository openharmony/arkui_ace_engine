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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_NG_H

#include <functional>

#include "base/geometry/dimension.h"
#include "core/animation/animator.h"
#include "core/animation/friction_motion.h"
#include "core/animation/scroll_motion.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/raw_recognizer.h"
#include "core/gestures/timeout_recognizer.h"

namespace OHOS::Ace::NG {
enum class NestedState {
    GESTURE = 0,
    CHILD_SCROLL,
    CHILD_OVER_SCROLL,
};

struct OverScrollOffset {
    double start;
    double end;
};

struct ScrollResult {
    double remain;
    bool reachEdge;
};

using ScrollEventCallback = std::function<void()>;
using OutBoundaryCallback = std::function<bool()>;
using ScrollOverCallback = std::function<void(double velocity)>;
using WatchFixCallback = std::function<double(double final, double current)>;
using ScrollBeginCallback = std::function<ScrollInfo(Dimension, Dimension)>;
using ScrollFrameBeginCallback = std::function<ScrollFrameResult(Dimension, ScrollState)>;
using DragEndForRefreshCallback = std::function<void()>;
using DragCancelRefreshCallback = std::function<void()>;
using MouseLeftButtonScroll = std::function<bool()>;
using ScrollSnapCallback = std::function<bool(double targetOffset, double velocity)>;
using ContinuousSlidingCallback = std::function<double()>;
using CalePredictSnapOffsetCallback =
    std::function<std::optional<float>(float delta, float dragDistance, float velocity)>;
using NeedScrollSnapToSideCallback = std::function<bool(float delta)>;
using NestableScrollCallback = std::function<ScrollResult(float, int32_t, NestedState)>;
using DragFRCSceneCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;
using ScrollMotionFRCSceneCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;

class Scrollable : public TouchEventTarget {
    DECLARE_ACE_TYPE(Scrollable, TouchEventTarget);

public:
    Scrollable() = default;
    Scrollable(ScrollPositionCallback&& callback, Axis axis);
    Scrollable(const ScrollPositionCallback& callback, Axis axis);
    ~Scrollable() override;

    static void SetVelocityScale(double sVelocityScale);
    static void SetFriction(double sFriction);

    void Initialize(const WeakPtr<PipelineBase>& context);

    bool IsMotionStop() const
    {
        return isSpringAnimationStop_  &&
               isFrictionAnimationStop_ && !moved_;
    }

    bool IsSpringMotionRunning() const
    {
        return !isSpringAnimationStop_ ;
    }

    bool IsDragging() const
    {
        return isTouching_ && !isFrictionAnimationStop_;
    }

    void SetAxis(Axis axis);

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
        if (panRecognizerNG_) {
            panRecognizerNG_->SetCoordinateOffset(offset);
        }
    }

    void OnCollectTouchTarget(TouchTestResult& result)
    {
        if (panRecognizerNG_) {
            result.emplace_back(panRecognizerNG_);
        }
    }

    void SetDragTouchRestrict(const TouchRestrict& touchRestrict)
    {
        if (panRecognizerNG_) {
            panRecognizerNG_->SetTouchRestrict(touchRestrict);
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

    void SetUnstaticFriction(double friction)
    {
        friction_ = friction;
    }

    void HandleTouchDown();
    void HandleTouchUp();
    void HandleTouchCancel();
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);
    void HandleScrollEnd(const std::optional<float>& velocity);
    bool HandleOverScroll(double velocity);
    ScrollResult HandleScroll(double offset, int32_t source, NestedState state);

    void SetMoved(bool value)
    {
        moved_ = value;
    }
    void SetCanOverScroll(bool value)
    {
        canOverScroll_ = value;
    }
    bool CanOverScroll() const
    {
        return canOverScroll_;
    }

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
        return true;
    }
    bool HandleEvent(const AxisEvent& event) override
    {
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

    void OnAnimateStop();
    void ProcessScrollSnapStop();
    void StartSpringMotion(
        double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent);

    void UpdateScrollSnapStartOffset(double offset);
    void StartScrollSnapMotion(float predictSnapOffset, float scrollSnapVelocity);
    void UpdateScrollSnapEndWithOffset(double offset);

    bool IsAnimationNotRunning() const;

    bool Idle() const;

    bool IsStopped() const;

    bool IsSpringStopped() const;

    bool IsSnapStopped() const;

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

    void ChangeMoveStatus(bool flag)
    {
        moved_ = flag;
    }

    void SetOnScrollBegin(const ScrollBeginCallback& scrollBeginCallback)
    {
        scrollBeginCallback_ = scrollBeginCallback;
    }

    void SetOnContinuousSliding(const ContinuousSlidingCallback& continuousSlidingCallback)
    {
        continuousSlidingCallback_ = continuousSlidingCallback;
    }

    void SetHandleScrollCallback(NestableScrollCallback&& func)
    {
        handleScrollCallback_ = std::move(func);
    }
    void SetOverScrollCallback(std::function<bool(float)>&& func)
    {
        overScrollCallback_ = std::move(func);
    }
    void StartScrollAnimation(float mainPosition, float velocity);
    void SetOnScrollStartRec(std::function<void(float)>&& func)
    {
        onScrollStartRec_ = std::move(func);
    }
    void SetOnScrollEndRec(std::function<void(const std::optional<float>&)>&& func)
    {
        onScrollEndRec_ = std::move(func);
    }

    void SetEdgeEffect(EdgeEffect effect)
    {
        edgeEffect_ = effect;
    }

    void SetOnScrollSnapCallback(const ScrollSnapCallback& scrollSnapCallback)
    {
        scrollSnapCallback_ = scrollSnapCallback;
    }
    void SetContinuousDragStatus(bool status)
    {
        continuousDragStatus_ = status;
    }
    void IncreaseContinueDragCount()
    {
        dragCount_++;
    }
    void ResetContinueDragCount()
    {
        dragCount_ = 1;
    }
    void SetDragStartPosition(double position)
    {
        dragStartPosition_ = position;
    }
    void SetDragEndPosition(double position)
    {
        dragEndPosition_ = position;
    }
    double GetDragOffset()
    {
        return dragEndPosition_ - dragStartPosition_;
    }

    void SetCalePredictSnapOffsetCallback(CalePredictSnapOffsetCallback&& calePredictSnapOffsetCallback)
    {
        calePredictSnapOffsetCallback_ = std::move(calePredictSnapOffsetCallback);
    }

    void SetNeedScrollSnapToSideCallback(NeedScrollSnapToSideCallback&& needScrollSnapToSideCallback)
    {
        needScrollSnapToSideCallback_ = std::move(needScrollSnapToSideCallback);
    }

    void ProcessScrollSnapSpringMotion(float scrollSnapDelta, float scrollSnapVelocity);

    void StopSnapController()
    {
        if (!isSnapAnimationStop_) {
            StopSnapAnimation();
        }
    }

    double GetCurrentPos() const
    {
        return currentPos_;
    }

    bool GetNeedScrollSnapChange() const
    {
        return needScrollSnapChange_;
    }

    void AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd)
    {
        actionEnd_ = std::move(actionEnd);
    }

    bool GetIsDragging() const
    {
        return isDragging_;
    }

    void SetDragFRCSceneCallback(DragFRCSceneCallback&& dragFRCSceneCallback)
    {
        dragFRCSceneCallback_ = std::move(dragFRCSceneCallback);
    }

    void SetScrollMotionFRCSceneCallback(ScrollMotionFRCSceneCallback&& scrollMotionFRCSceneCallback)
    {
        scrollMotionFRCSceneCallback_ = std::move(scrollMotionFRCSceneCallback);
    }

    float GetFinalPosition()
    {
        return finalPosition_;
    }

    float GetSnapFinalPosition()
    {
        return endPos_;
    }

    void SetMaxFlingVelocity(double max)
    {
        maxFlingVelocity_ = max;
    }

    void StopFrictionAnimation();
    void StopSpringAnimation();
    void StopSnapAnimation();

    RefPtr<NodeAnimatablePropertyFloat> GetFrictionProperty();
    RefPtr<NodeAnimatablePropertyFloat> GetSpringProperty();
    RefPtr<NodeAnimatablePropertyFloat> GetSnapProperty();

private:
    bool UpdateScrollPosition(double offset, int32_t source) const;
    void ProcessSpringMotion(double position);
    void ProcessScrollMotion(double position);
    void ProcessScrollSnapMotion(double position);
    void FixScrollMotion(float position, float initVelocity);
    void ExecuteScrollBegin(double& mainDelta);
    double ComputeCap(int dragCount);
    double GetGain(double delta);
    void SetDelayedTask();
    float GetFrictionVelocityByFinalPosition(float final, float position, float signum, float friction,
        float threshold = DEFAULT_MULTIPLIER);

    /**
     * @brief Checks if the scroll event is caused by a mouse wheel.
     *
     * @param info The GestureEvent containing the scroll event information.
     * @return true if the scroll event is caused by a mouse wheel, false otherwise.
     */
    static inline bool IsMouseWheelScroll(const GestureEvent& info);

    ScrollPositionCallback callback_;
    ScrollEventCallback scrollEnd_;
    ScrollEventCallback scrollEndCallback_;
    ScrollEventCallback scrollTouchUpCallback_;
    ScrollOverCallback scrollOverCallback_;       // scroll motion controller when edge set to spring
    ScrollOverCallback notifyScrollOverCallback_; // scroll motion controller when edge set to spring
    OutBoundaryCallback outBoundaryCallback_;     // whether out of boundary check when edge set to spring

    WatchFixCallback watchFixCallback_;
    ScrollBeginCallback scrollBeginCallback_;
    ScrollSnapCallback scrollSnapCallback_;
    DragEndForRefreshCallback dragEndCallback_;
    DragCancelRefreshCallback dragCancelCallback_;
    ContinuousSlidingCallback continuousSlidingCallback_;
    Axis axis_;
    // used for ng structure.
    RefPtr<NG::PanRecognizer> panRecognizerNG_;

    WeakPtr<PipelineBase> context_;
    double currentPos_ = 0.0;
    double currentVelocity_ = 0.0;
    double maxFlingVelocity_ = 0.0;
    bool scrollPause_ = false;
    bool touchUp_ = false;
    bool moved_ = false;
    bool isTouching_ = false;
    bool isDragging_ = false;
    bool available_ = true;
    bool needCenterFix_ = false;
    bool isDragUpdateStop_ = false;
    int32_t nodeId_ = 0;
    double slipFactor_ = 0.0;
    static std::optional<double> sFriction_;
    static std::optional<double> sVelocityScale_;
    bool continuousDragStatus_ = false;
    CancelableCallback<void()> task_;
    int32_t dragCount_ = 0;
    double lastPos_ = 0.0;
    double dragStartPosition_ = 0.0;
    double dragEndPosition_ = 0.0;
    double lastVelocity_ = 0.0;
    double friction_ = -1.0;
    double velocityScale_ = 0.0;
#ifdef OHOS_PLATFORM
    int64_t startIncreaseTime_ = 0;
#endif

    // ScrollablePattern::HandleScroll
    NestableScrollCallback handleScrollCallback_;
    // ScrollablePattern::HandleOverScroll
    std::function<bool(float)> overScrollCallback_;
    // ScrollablePattern::onScrollStartRecursive
    std::function<void(float)> onScrollStartRec_;
    // ScrollablePattern::onScrollEndRecursive
    std::function<void(const std::optional<float>&)> onScrollEndRec_;

    EdgeEffect edgeEffect_ = EdgeEffect::NONE;
    bool canOverScroll_ = true;

    // scrollSnap
    bool needScrollSnapChange_ = false;
    CalePredictSnapOffsetCallback calePredictSnapOffsetCallback_;
    NeedScrollSnapToSideCallback needScrollSnapToSideCallback_;
    GestureEventFunc actionEnd_;

    DragFRCSceneCallback dragFRCSceneCallback_;
    ScrollMotionFRCSceneCallback scrollMotionFRCSceneCallback_;

    std::chrono::high_resolution_clock::time_point lastTime_;
    RefPtr<NodeAnimatablePropertyFloat> frictionOffsetProperty_;
    float finalPosition_ = 0.0f;
    float lastPosition_ = 0.0f;
    float initVelocity_ = 0.0f;
    float frictionVelocity_ = 0.0f;
    bool isFrictionAnimationStop_ = true;

    RefPtr<NodeAnimatablePropertyFloat> springOffsetProperty_;
    bool isSpringAnimationStop_ = true;
    bool skipRestartSpring_ = false;
    uint32_t updateSnapAnimationCount_ = 0;
    uint32_t springAnimationCount_ = 0;

    RefPtr<NodeAnimatablePropertyFloat> snapOffsetProperty_;
    bool isSnapAnimationStop_ = true;
    bool isSnapScrollAnimationStop_ = true;
    float snapVelocity_ = 0.0f;
    float endPos_ = 0.0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_NG_H
