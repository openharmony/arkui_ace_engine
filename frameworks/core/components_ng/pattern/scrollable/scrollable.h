/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "base/utils/system_properties.h"
#include "core/animation/animator.h"
#include "core/animation/friction_motion.h"
#include "core/animation/scroll_motion.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scrollable/axis/axis_animator.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/raw_recognizer.h"
#include "core/gestures/timeout_recognizer.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#include "core/common/vibrator/vibrator_utils.h"
#endif

namespace OHOS::Ace::NG {
enum class NestedState {
    GESTURE = 0,
    CHILD_SCROLL,
    CHILD_OVER_SCROLL,
    CHILD_CHECK_OVER_SCROLL,
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
using ContinuousSlidingCallback = std::function<double()>;
using StartSnapAnimationCallback = std::function<bool(SnapAnimationOptions)>;
using NeedScrollSnapToSideCallback = std::function<bool(float delta)>;
using NestableScrollCallback = std::function<ScrollResult(float, int32_t, NestedState)>;
using DragFRCSceneCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;
using IsReverseCallback = std::function<bool()>;
using RemainVelocityCallback = std::function<bool(float)>;
using GetSnapTypeCallback = std::function<SnapType()>;
using FixScrollParamCallback = std::function<void(float mainPos, float& correctVelocity, float& finalPos)>;

class FrameNode;
class PipelineContext;

class Scrollable : public TouchEventTarget {
    DECLARE_ACE_TYPE(Scrollable, TouchEventTarget);

public:
    Scrollable() = default;
    Scrollable(ScrollPositionCallback&& callback, Axis axis) : callback_(std::move(callback)), axis_(axis) {}
    Scrollable(const ScrollPositionCallback& callback, Axis axis) : callback_(callback), axis_(axis) {}
    ~Scrollable() override;

    enum class AnimationState {
        SPRING,
        SNAP,
        FRICTION,
        TRANSITION, // in between two animations, i.e. from friction to spring
        IDLE,
    };

    static double GetVelocityScale();

    void Initialize(const RefPtr<FrameNode>& host);

    void InitAxisAnimator();
#ifdef SUPPORT_DIGITAL_CROWN
    void ListenDigitalCrownEvent(const RefPtr<FrameNode>& frameNode);
    void SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
    {
        crownSensitivity_ = sensitivity;
    }
#endif
    bool IsMotionStop() const
    {
        return state_ != AnimationState::SPRING && state_ != AnimationState::FRICTION && !moved_;
    }

    bool IsSpringMotionRunning() const
    {
        return state_ == AnimationState::SPRING;
    }

    bool IsDragging() const
    {
        return isTouching_ && state_ == AnimationState::FRICTION;
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

    void OnCollectTouchTarget(TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
        const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult);

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

    void SetUnstaticFriction(double friction)
    {
        friction_ = friction > 0.0 ? friction : -1.0;
    }

    double GetFriction() const
    {
        double friction = friction_;
        if (friction == -1.0) {
            double ret = SystemProperties::GetSrollableFriction();
            friction = !NearZero(ret) ? ret : defaultFriction_;
        }
        return friction;
    }

    float GetRatio() const
    {
        return ratio_;
    }

    void SetUnstaticVelocityScale(double scale)
    {
        flingVelocityScale_ = scale;
        springVelocityScale_ = scale;
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
    void ProcessAxisUpdateEvent(float mainDelta, bool fromScrollBar = false);
    void ProcessAxisEndEvent();
    void LayoutDirectionEst(double correctVelocity, double velocityScale, bool isScrollFromTouchPad);
    void ReportToDragFRCScene(double velocity, NG::SceneStatus sceneStatus);

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

    void SetRemainVelocityCallback(const RemainVelocityCallback& remainVelocityCallback)
    {
        remainVelocityCallback_ = remainVelocityCallback;
    }

    void SetScrollOverCallBack(const ScrollOverCallback& scrollOverCallback)
    {
        scrollOverCallback_ = scrollOverCallback;
    }

    void SetNotifyScrollOverCallBack(const ScrollOverCallback& scrollOverCallback)
    {
        notifyScrollOverCallback_ = scrollOverCallback;
    }

    void SetCurrentPositionCallback(const std::function<double()>& currentPositionCallback)
    {
        currentPositionCallback_ = currentPositionCallback;
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

    void SetIsReverseCallback(const IsReverseCallback& isReverseCallback)
    {
        isReverseCallback_ = isReverseCallback;
    }

    void OnAnimateStop();
    void ProcessScrollSnapStop();
    void StartSpringMotion(
        double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent);
    void UpdateSpringMotion(double mainPosition, const ExtentPair& extent, const ExtentPair& initExtent);

    void UpdateScrollSnapStartOffset(double offset);
    void StartListSnapAnimation(float predictSnapOffset, float scrollSnapVelocity, bool fromScrollBar);
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

    WeakPtr<PipelineContext> GetContext() const
    {
        return context_;
    }

    void SetNodeId(int32_t nodeId)
    {
        nodeId_ = nodeId;
    }

    int32_t GetNodeId()
    {
        return nodeId_;
    }

    void SetNodeTag(const std::string& nodeTag)
    {
        nodeTag_ = nodeTag;
    }

    const std::string& GetNodeTag() const
    {
        return nodeTag_;
    }

    void ProcessScrollOverCallback(double velocity);

    void SetSlipFactor(double SlipFactor);

    void SetOnScrollBegin(const ScrollBeginCallback& scrollBeginCallback)
    {
        scrollBeginCallback_ = scrollBeginCallback;
    }

    void SetOnContinuousSliding(const ContinuousSlidingCallback& continuousSlidingCallback)
    {
        continuousSlidingCallback_ = continuousSlidingCallback;
    }

    void SetGetSnapTypeCallback(const GetSnapTypeCallback& getSnapTypeCallback)
    {
        getSnapTypeCallback_ = getSnapTypeCallback;
    }

    std::optional<float> GetPredictSnapOffset() const;

    void SetHandleScrollCallback(NestableScrollCallback&& func)
    {
        handleScrollCallback_ = std::move(func);
    }
    void SetOverScrollCallback(std::function<bool(float)>&& func)
    {
        overScrollCallback_ = std::move(func);
    }
    void StartScrollAnimation(float mainPosition, float velocity, bool isScrollFromTouchPad = false);
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

    void SetStartSnapAnimationCallback(const StartSnapAnimationCallback& startSnapAnimationCallback)
    {
        startSnapAnimationCallback_ = startSnapAnimationCallback;
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

    void SetNeedScrollSnapToSideCallback(NeedScrollSnapToSideCallback&& needScrollSnapToSideCallback)
    {
        needScrollSnapToSideCallback_ = std::move(needScrollSnapToSideCallback);
    }

    void StartScrollSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity, bool fromScrollBar);

    void StopSnapController()
    {
        if (state_ == AnimationState::SNAP) {
            StopSnapAnimation();
        }
    }

    bool IsSnapAnimationRunning()
    {
        return state_ == AnimationState::SNAP;
    }

    bool IsAxisAnimationRunning()
    {
        return axisAnimator_ && axisAnimator_->IsRunning();
    }

    double GetCurrentPos() const
    {
        return currentPos_;
    }

    void SetCurrentPos(float currentPos)
    {
        currentPos_ = currentPos;
    }

    bool GetNeedScrollSnapChange() const
    {
        return needScrollSnapChange_;
    }

    void AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd)
    {
        AddPanActionEndEvent(std::move(actionEnd));
    }

    bool GetIsDragging() const
    {
        return isDragging_;
    }

    void SetDragFRCSceneCallback(DragFRCSceneCallback&& dragFRCSceneCallback)
    {
        dragFRCSceneCallback_ = std::move(dragFRCSceneCallback);
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
        double density = PipelineBase::GetCurrentDensity();
        maxFlingVelocity_ = max * density;
    }

    double GetMaxFlingVelocity() const
    {
        return maxFlingVelocity_;
    }

    void RegisterFixScrollParamCallback(const FixScrollParamCallback& callback)
    {
        fixScrollParamCallback_ = callback;
    }

    void StopFrictionAnimation();
    void StopSpringAnimation(bool reachFinalPosition = false);
    void StopSnapAnimation();
    void StopAxisAnimation();

    void AttachAnimatableProperty(const RefPtr<NodeAnimatablePropertyFloat>& property);
    RefPtr<NodeAnimatablePropertyFloat> GetFrictionProperty();
    RefPtr<NodeAnimatablePropertyFloat> GetSpringProperty();
    RefPtr<NodeAnimatablePropertyFloat> GetSnapProperty();

    Axis GetPanDirection() const
    {
        CHECK_NULL_RETURN(panRecognizerNG_, Axis::NONE);
        return panRecognizerNG_->GetAxisDirection();
    }

    void SetNestedScrolling(bool nestedScrolling)
    {
        nestedScrolling_ = nestedScrolling;
    }

    bool GetNestedScrolling() const
    {
        return nestedScrolling_;
    }

#ifdef SUPPORT_DIGITAL_CROWN
    bool GetCrownEventDragging() const
    {
        return isCrownEventDragging_;
    }

    void SetCrownEventDragging(bool draging)
    {
        isCrownEventDragging_ = draging;
    }

    void SetReachBoundary(bool flag)
    {
        reachBoundary_ = flag;
    }
#endif

    void SetOverScrollOffsetCallback(std::function<double()> overScrollOffsetCallback)
    {
        overScrollOffsetCallback_ = overScrollOffsetCallback;
    }

    void AddPanActionEndEvent(GestureEventFunc&& event)
    {
        panActionEndEvents_.emplace_back(event);
    }

    SnapType GetSnapType()
    {
        CHECK_NULL_RETURN(getSnapTypeCallback_, SnapType::NONE_SNAP);
        return getSnapTypeCallback_();
    }

    void ResetSnapDirection()
    {
        snapDirection_ = SnapDirection::NONE;
    }

private:
    void InitPanRecognizerNG();
    void SetOnActionStart();
    void SetOnActionUpdate();
    void SetOnActionEnd();
    void SetOnActionCancel();
    bool UpdateScrollPosition(double offset, int32_t source) const;
    void ProcessSpringMotion(double position);
    void ProcessScrollMotion(double position, int32_t source = SCROLL_FROM_ANIMATION);
    void ProcessListSnapMotion(double position);
    void TriggerFrictionAnimation(float mainPosition, float friction, float correctVelocity);
    void FixScrollMotion(float position, float initVelocity);
    void ExecuteScrollBegin(double& mainDelta);
    double ComputeCap(int dragCount);
    double GetGain(double delta);
    void SetDelayedTask();
    void MarkNeedFlushAnimationStartTime();
    float GetFrictionVelocityByFinalPosition(
        float final, float position, float signum, float friction, float threshold = DEFAULT_MULTIPLIER);
    void InitFriction(double friction);
    void CalcOverScrollVelocity();

#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownEvent(const CrownEvent& event, const OffsetF& center);
    void HandleCrownActionBegin(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info);
    void HandleCrownActionUpdate(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info);
    void HandleCrownActionEnd(const TimeStamp& timeStamp, double mainDelta, GestureEvent& info);
    void HandleCrownActionCancel(GestureEvent& info);
    double GetCrownRotatePx(const CrownEvent& event) const;
    void UpdateCrownVelocity(const TimeStamp& timeStamp, double mainDelta, bool end);
    void StartVibrateFeedback();
#endif

    /**
     * @brief Checks if the scroll event is caused by a mouse wheel.
     *
     * @param info The GestureEvent containing the scroll event information.
     * @return true if the scroll event is caused by a mouse wheel, false otherwise.
     */
    static inline bool IsMouseWheelScroll(const GestureEvent& info);

    ScrollPositionCallback callback_;
    ScrollEventCallback scrollEndCallback_;
    ScrollOverCallback scrollOverCallback_;       // scroll motion controller when edge set to spring
    ScrollOverCallback notifyScrollOverCallback_; // scroll motion controller when edge set to spring
    OutBoundaryCallback outBoundaryCallback_;     // whether out of boundary check when edge set to spring
    std::function<double()> currentPositionCallback_;
    IsReverseCallback isReverseCallback_;

    WatchFixCallback watchFixCallback_;
    ScrollBeginCallback scrollBeginCallback_;
    DragEndForRefreshCallback dragEndCallback_;
    DragCancelRefreshCallback dragCancelCallback_;
    ContinuousSlidingCallback continuousSlidingCallback_;
    GetSnapTypeCallback getSnapTypeCallback_;
    Axis axis_ = Axis::VERTICAL;
    // used for ng structure.
    RefPtr<NG::PanRecognizer> panRecognizerNG_;

    WeakPtr<FrameNode> weakHost_;
    WeakPtr<PipelineContext> context_;
    double currentPos_ = 0.0;
    double currentVelocity_ = 0.0;
    double maxFlingVelocity_ = 0.0;
    bool scrollPause_ = false;
    bool moved_ = false;
    bool isTouching_ = false;
    bool isDragging_ = false;
    bool available_ = true;
    bool needCenterFix_ = false;
    bool isDragUpdateStop_ = false;
    bool isFadingAway_ = false;
    bool isCrownDragging_ = false;
    // The accessibilityId of UINode
    int32_t nodeId_ = 0;
    // The tag of UINode
    std::string nodeTag_ = "Scrollable";
    double slipFactor_ = 0.0;
    bool continuousDragStatus_ = false;
    CancelableCallback<void()> task_;
    int32_t dragCount_ = 0;
    double lastPos_ = 0.0;
    double dragStartPosition_ = 0.0;
    double dragEndPosition_ = 0.0;
    double lastGestureVelocity_ = 0.0;
    double friction_ = -1.0;
    double preGain_ = 1.0;
#ifdef OHOS_PLATFORM
    int64_t startIncreaseTime_ = 0;
#endif

    // ScrollablePattern::HandleScroll
    NestableScrollCallback handleScrollCallback_;
    // ScrollablePattern::HandleOverScroll
    std::function<bool(float)> overScrollCallback_;
    // ScrollablePattern::onScrollStartRecursiveInner
    std::function<void(float)> onScrollStartRec_;
    // ScrollablePattern::onScrollEndRecursiveInner
    std::function<void(const std::optional<float>&)> onScrollEndRec_;
    // ScrollablePattern::RemainVelocityToChild
    RemainVelocityCallback remainVelocityCallback_;

    EdgeEffect edgeEffect_ = EdgeEffect::NONE;
    bool canOverScroll_ = true;

    // scrollSnap
    bool needScrollSnapChange_ = false;
    StartSnapAnimationCallback startSnapAnimationCallback_;
    NeedScrollSnapToSideCallback needScrollSnapToSideCallback_;
    std::list<GestureEventFunc> panActionEndEvents_;

    DragFRCSceneCallback dragFRCSceneCallback_;
    FixScrollParamCallback fixScrollParamCallback_;
    uint64_t lastVsyncTime_ = 0;
    uint64_t lastAxisVsyncTime_ = 0; // only used in mouse wheel scenes
    AnimationState state_ = AnimationState::IDLE;
    RefPtr<NodeAnimatablePropertyFloat> frictionOffsetProperty_;
    float finalPosition_ = 0.0f;
    float lastPosition_ = 0.0f;
    float initVelocity_ = 0.0f;
    float frictionVelocity_ = 0.0f;
    double lastMainDelta_ = 0.0;

    RefPtr<NodeAnimatablePropertyFloat> springOffsetProperty_;
    bool skipRestartSpring_ = false; // set to true when need to skip repeated spring animation
    uint32_t updateSnapAnimationCount_ = 0;
    uint32_t springAnimationCount_ = 0;
    double flingVelocityScale_ = 1.5;
    double springVelocityScale_ = 1.5;
    double defaultFriction_ = 0;
    float ratio_ = 1.848f;
    float springResponse_ = 0.416f;
    float touchPadVelocityScaleRate_ = 1.0f;
    std::function<double()> overScrollOffsetCallback_;

    RefPtr<NodeAnimatablePropertyFloat> snapOffsetProperty_;
    bool snapAnimationFromScrollBar_ = false;
    float snapVelocity_ = 0.0f;
    float endPos_ = 0.0;
    bool nestedScrolling_ = false;
    float axisSnapDistance_ = 0.f;
    SnapDirection snapDirection_ = SnapDirection::NONE;

    RefPtr<AxisAnimator> axisAnimator_;
#ifdef SUPPORT_DIGITAL_CROWN
    CrownSensitivity crownSensitivity_ = CrownSensitivity::MEDIUM;
    VelocityTracker crownVelocityTracker_;
    Offset accumulativeCrownPx_;
    bool isCrownEventDragging_ = false;

    int crownEventNum_ = 0;
    bool reachBoundary_ = false;
    CancelableCallback<void()> crownTask_;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLLABLE_NG_H
