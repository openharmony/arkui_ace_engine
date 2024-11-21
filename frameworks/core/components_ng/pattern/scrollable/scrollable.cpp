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

#include "core/components_ng/pattern/scrollable/scrollable.h"

#include <chrono>

#include "base/log/ace_trace.h"
#include "base/log/frame_report.h"
#include "base/log/jank_frame_report.h"
#include "base/log/log.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "base/ressched/ressched_report.h"
#include "core/common/layout_inspector.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr double CAP_COEFFICIENT = 0.45;
constexpr int32_t FIRST_THRESHOLD = 4;
constexpr int32_t SECOND_THRESHOLD = 10;
constexpr double CAP_FIXED_VALUE = 16.0;
constexpr uint32_t DRAG_INTERVAL_TIME = 900;

#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double API11_FRICTION = 0.7;
constexpr double API12_FRICTION = 0.75;
constexpr double VELOCITY_SCALE = 1.0;
constexpr double NEW_VELOCITY_SCALE = 1.5;
constexpr double ADJUSTABLE_VELOCITY = 3000.0;
#else
constexpr double DISTANCE_EPSILON = 1.0;
constexpr double FRICTION = 0.9;
constexpr double VELOCITY_SCALE = 0.8;
constexpr double ADJUSTABLE_VELOCITY = 0.0;
#endif
constexpr float FRICTION_SCALE = -4.2f;
constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
constexpr uint64_t MILLOS_PER_NANO_SECONDS = 1000 * 1000 * 1000;
constexpr uint64_t MIN_DIFF_VSYNC = 1000 * 1000; // min is 1ms
constexpr float DEFAULT_THRESHOLD = 0.75f;
constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
constexpr float DEFAULT_SPRING_DAMP = 0.99f;
constexpr uint32_t MAX_VSYNC_DIFF_TIME = 100 * 1000 * 1000; // max 100 ms
constexpr float FRICTION_VELOCITY_THRESHOLD = 120.0f;
constexpr float SPRING_ACCURACY = 0.1;
#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif

} // namespace

// Static Functions.
std::optional<double> Scrollable::sFriction_ = std::nullopt;
std::optional<double> Scrollable::sVelocityScale_ = std::nullopt;

void Scrollable::SetVelocityScale(double sVelocityScale)
{
    if (LessOrEqual(sVelocityScale, 0.0)) {
        return;
    }
    sVelocityScale_ = sVelocityScale;
}

double Scrollable::GetVelocityScale()
{
    return Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ?
        NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

void Scrollable::SetFriction(double sFriction)
{
    if (LessOrEqual(sFriction, 0.0)) {
        return;
    }
    sFriction_ = sFriction;
}

Scrollable::Scrollable()
{
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? API11_FRICTION : FRICTION;
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? API12_FRICTION : friction_;
    velocityScale_ =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::Scrollable(ScrollPositionCallback&& callback, Axis axis) : callback_(std::move(callback)), axis_(axis)
{
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? API11_FRICTION : FRICTION;
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? API12_FRICTION : friction_;
    velocityScale_ =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::Scrollable(const ScrollPositionCallback& callback, Axis axis) : callback_(callback), axis_(axis)
{
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? API11_FRICTION : FRICTION;
    friction_ = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? API12_FRICTION : friction_;
    velocityScale_ =
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::~Scrollable()
{
    // If animation still runs, force stop it.
    StopFrictionAnimation();
    StopSpringAnimation();
    StopSnapAnimation();
}

void Scrollable::Initialize(PipelineContext* context)
{
    auto weakContext = WeakClaim(context);
    Initialize(weakContext);
}

void Scrollable::Initialize(const WeakPtr<PipelineBase>& context)
{
    context_ = context;
    PanDirection panDirection;
    if (axis_ == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }

    auto actionStart = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->isDragging_ = true;
            scroll->HandleDragStart(info);
        }
    };

    auto actionUpdate = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleDragUpdate(info);
        }
    };

    auto actionEnd = [weakScroll = AceType::WeakClaim(this)](GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleDragEnd(info);
            if (scroll->panActionEndEvents_.empty()) {
                scroll->isDragging_ = false;
                return;
            }
            std::for_each(scroll->panActionEndEvents_.begin(), scroll->panActionEndEvents_.end(),
                [info](GestureEventFunc& event) {
                    auto gestureInfo = info;
                    event(gestureInfo);
                });
            scroll->isDragging_ = false;
        }
    };

    auto actionCancel = [weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (!scroll) {
            return;
        }
        if (scroll->dragCancelCallback_) {
            scroll->dragCancelCallback_();
        }
        GestureEvent info;
        scroll->HandleDragEnd(info);
        if (scroll->panActionEndEvents_.empty()) {
            scroll->isDragging_ = false;
            return;
        }
        std::for_each(scroll->panActionEndEvents_.begin(), scroll->panActionEndEvents_.end(),
            [info](GestureEventFunc& event) {
                auto gestureInfo = info;
                event(gestureInfo);
            });
        scroll->isDragging_ = false;
    };

    if (Container::IsCurrentUseNewPipeline()) {
        panRecognizerNG_ = AceType::MakeRefPtr<NG::PanRecognizer>(
            DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE.ConvertToPx());
        panRecognizerNG_->SetIsAllowMouse(false);
        panRecognizerNG_->SetOnActionStart(actionStart);
        panRecognizerNG_->SetOnActionUpdate(actionUpdate);
        panRecognizerNG_->SetOnActionEnd(actionEnd);
        panRecognizerNG_->SetOnActionCancel(actionCancel);
    }
    available_ = true;
}

void Scrollable::SetAxis(Axis axis)
{
    axis_ = axis;
    PanDirection panDirection;
    if (axis_ == Axis::NONE) {
        panDirection.type = PanDirection::NONE;
    } else if (axis_ == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }
    if (panRecognizerNG_) {
        panRecognizerNG_->SetDirection(panDirection);
    }
}

void Scrollable::HandleTouchDown()
{
    isTouching_ = true;
    // If animation still runs, first stop it.
    ACE_SCOPED_TRACE("HandleTouchDown, panDirection:%u, id:%d, tag:%s", GetPanDirection(), nodeId_, nodeTag_.c_str());
    StopSpringAnimation();
    if (!isFrictionAnimationStop_) {
        StopFrictionAnimation();
    } else if (!isSnapAnimationStop_ || !isSnapScrollAnimationStop_) {
        StopSnapAnimation();
    } else {
        // Resets values.
        currentPos_ = 0.0;
    }
}

void Scrollable::HandleTouchUp()
{
    // Two fingers are alternately drag, one finger is released without triggering spring animation.
    ACE_SCOPED_TRACE("HandleTouchUp, isDragging_:%u, nestedScrolling_:%u id:%d, tag:%s",
        isDragging_, nestedScrolling_, nodeId_, nodeTag_.c_str());
    if (isDragging_) {
        return;
    }
    isTouching_ = false;
    if (nestedScrolling_) {
        return;
    }
    // outBoundaryCallback_ is only set in ScrollablePattern::SetEdgeEffect and when the edge effect is spring
    if (outBoundaryCallback_ && outBoundaryCallback_()) {
        if (isSpringAnimationStop_ && scrollOverCallback_) {
            if (onScrollStartRec_) {
                onScrollStartRec_(static_cast<float>(axis_));
            }
            ProcessScrollOverCallback(0.0);
        }
        return;
    }
    if (isSnapScrollAnimationStop_ && scrollSnapCallback_) {
        scrollSnapCallback_(0.0, 0.0);
    }
}

void Scrollable::HandleTouchCancel()
{
    isTouching_ = false;
    ACE_SCOPED_TRACE("HandleTouchCancel, id:%d, tag:%s", nodeId_, nodeTag_.c_str());
    if (isSpringAnimationStop_ && scrollOverCallback_) {
        ProcessScrollOverCallback(0.0);
    }
}

bool Scrollable::IsAnimationNotRunning() const
{
    return !isTouching_ && isFrictionAnimationStop_ && isSpringAnimationStop_
        && isSnapAnimationStop_ && isSnapScrollAnimationStop_;
}

bool Scrollable::Idle() const
{
    return !isTouching_ && isFrictionAnimationStop_ && isSpringAnimationStop_
        && isSnapAnimationStop_ && isSnapScrollAnimationStop_ && !nestedScrolling_;
}

bool Scrollable::IsStopped() const
{
    return isSpringAnimationStop_ && isFrictionAnimationStop_
        && isSnapAnimationStop_ && isSnapScrollAnimationStop_;
}

bool Scrollable::IsSpringStopped() const
{
    return isSpringAnimationStop_;
}

bool Scrollable::IsSnapStopped() const
{
    return isSnapAnimationStop_;
}

void Scrollable::StopScrollable()
{
    if (!isFrictionAnimationStop_) {
        StopFrictionAnimation();
    }
    if (!isSpringAnimationStop_) {
        StopSpringAnimation();
    }
    if (!isSnapAnimationStop_ || !isSnapScrollAnimationStop_) {
        StopSnapAnimation();
    }
}

void Scrollable::HandleScrollEnd(const std::optional<float>& velocity)
{
    // priority:
    //  1. onScrollEndRec_ (would internally call onScrollEnd)
    //  2. scrollEndCallback_
    if (onScrollEndRec_) {
        onScrollEndRec_(velocity);
        return;
    }
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
}

void Scrollable::HandleDragStart(const OHOS::Ace::GestureEvent& info)
{
    ACE_SCOPED_TRACE("HandleDragStart, id:%d, tag:%s", nodeId_, nodeTag_.c_str());
    if (info.GetSourceTool() == SourceTool::TOUCHPAD) {
        HandleTouchDown();
    }
    currentVelocity_ = info.GetMainVelocity();
    if (dragFRCSceneCallback_) {
        dragFRCSceneCallback_(currentVelocity_, NG::SceneStatus::START);
    }
    if (continuousDragStatus_) {
        IncreaseContinueDragCount();
        task_.Cancel();
    }
    SetDragStartPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    const double dragPositionInMainAxis =
        axis_ == Axis::VERTICAL ? info.GetGlobalLocation().GetY() : info.GetGlobalLocation().GetX();
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Scroll drag start, id:%{public}d, tag:%{public}s", nodeId_, nodeTag_.c_str());
    
    skipRestartSpring_ = false; // reset flags. Extract method if more flags need to be reset

#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding start.
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (!moved_ || increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        startIncreaseTime_ = currentTime;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    JankFrameReport::GetInstance().SetFrameJankFlag(JANK_RUNNING_SCROLL);
    if (onScrollStartRec_) {
        onScrollStartRec_(static_cast<float>(dragPositionInMainAxis));
    }
}

ScrollResult Scrollable::HandleScroll(double offset, int32_t source, NestedState state)
{
    if (!handleScrollCallback_) {
        ExecuteScrollBegin(offset);
        canOverScroll_ = false;
        moved_ = UpdateScrollPosition(offset, source);
        return { 0, false };
    }
    // call NestableScrollContainer::HandleScroll
    return handleScrollCallback_(static_cast<float>(offset), source, state);
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
    currentVelocity_ = info.GetMainVelocity();
    if (dragFRCSceneCallback_) {
        dragFRCSceneCallback_(currentVelocity_, NG::SceneStatus::RUNNING);
    }
    if (!NearZero(info.GetMainVelocity()) && dragCount_ >= FIRST_THRESHOLD) {
        if (Negative(lastVelocity_ / info.GetMainVelocity())) {
            ResetContinueDragCount();
        }
    }
    if (!isSpringAnimationStop_ || !isFrictionAnimationStop_ ||
        !isSnapAnimationStop_ || !isSnapScrollAnimationStop_) {
        // If animation still runs, first stop it.
        isDragUpdateStop_ = true;
        StopFrictionAnimation();
        StopSpringAnimation();
        StopSnapAnimation();
        currentPos_ = 0.0;
    }
#ifdef OHOS_PLATFORM
    // Handle the case where you keep sliding past limit time(4s).
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        startIncreaseTime_ = currentTime;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    auto mainDelta = info.GetMainDelta();
    auto source = IsMouseWheelScroll(info) ? SCROLL_FROM_AXIS : SCROLL_FROM_UPDATE;
    ACE_SCOPED_TRACE(
        "HandleDragUpdate, mainDelta:%f, source:%d, id:%d, tag:%s", mainDelta, source, nodeId_, nodeTag_.c_str());
    if (isReverseCallback_ && isReverseCallback_()) {
        mainDelta = Round(-mainDelta);
    } else {
        mainDelta = Round(mainDelta);
    }
    JankFrameReport::GetInstance().RecordFrameUpdate();
    HandleScroll(mainDelta, source, NestedState::GESTURE);
}

void Scrollable::LayoutDirectionEst(double& correctVelocity)
{
    if (isReverseCallback_ && isReverseCallback_()) {
        correctVelocity = -correctVelocity * sVelocityScale_.value_or(velocityScale_) * GetGain(GetDragOffset());
    } else {
        correctVelocity = correctVelocity * sVelocityScale_.value_or(velocityScale_) * GetGain(GetDragOffset());
    }
}

void Scrollable::HandleDragEnd(const GestureEvent& info)
{
    // avoid no render frame when drag end
    HandleDragUpdate(info);

    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Scroll drag end, velocity is %{public}f id:%{public}d, tag:%{public}s",
        info.GetMainVelocity(), nodeId_, nodeTag_.c_str());
    if (dragFRCSceneCallback_) {
        dragFRCSceneCallback_(info.GetMainVelocity(), NG::SceneStatus::END);
    }
    isDragUpdateStop_ = false;
    touchUp_ = false;
    scrollPause_ = false;
    lastVelocity_ = GetPanDirection() == Axis::NONE ? 0.0 : info.GetMainVelocity();
    double gestureVelocity = GetPanDirection() == Axis::NONE ? 0.0 : info.GetMainVelocity();
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    LayoutDirectionEst(gestureVelocity);
    // Apply max fling velocity limit, it must be calculated after all fling velocity gain.
    currentVelocity_ = std::clamp(gestureVelocity, -maxFlingVelocity_ + slipFactor_, maxFlingVelocity_ - slipFactor_);

    lastPos_ = GetDragOffset();
    JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_SCROLL);
    double mainPosition = GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()));
    mainPosition = Round(mainPosition);
    ACE_SCOPED_TRACE("HandleDragEnd, mainPosition:%f, gestureVelocity:%f, currentVelocity:%f, moved_:%u "
                     "canOverScroll_:%u, id:%d, tag:%s",
        mainPosition, gestureVelocity, currentVelocity_, moved_, canOverScroll_, nodeId_, nodeTag_.c_str());
    if (!moved_ || IsMouseWheelScroll(info)) {
        if (calePredictSnapOffsetCallback_) {
            std::optional<float> predictSnapOffset = calePredictSnapOffsetCallback_(0.0f, 0.0f, 0.0f);
            if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
                currentPos_ = mainPosition;
                ProcessScrollSnapSpringMotion(predictSnapOffset.value(), currentVelocity_);
                isTouching_ = false;
                return;
            }
        }
        HandleScrollEnd(currentVelocity_);
        currentVelocity_ = 0.0;
#ifdef OHOS_PLATFORM
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
    } else if (!Container::IsCurrentUseNewPipeline() && outBoundaryCallback_ && outBoundaryCallback_() &&
               scrollOverCallback_) {
        ResetContinueDragCount();
        ProcessScrollOverCallback(currentVelocity_);
    } else if (canOverScroll_) {
        ResetContinueDragCount();
        HandleOverScroll(currentVelocity_);
    } else {
        StartScrollAnimation(mainPosition, currentVelocity_);
    }
    SetDelayedTask();
    if (dragEndCallback_) {
        dragEndCallback_();
    }
    isTouching_ = false;
}

void Scrollable::StartScrollAnimation(float mainPosition, float correctVelocity)
{
    if (!isSpringAnimationStop_) {
        StopSpringAnimation();
    }
    if (!frictionOffsetProperty_) {
        GetFrictionProperty();
    }
    StopSnapController();
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The position of scroll motion is %{public}f, velocity is %{public}f",
        mainPosition, correctVelocity);
    float friction = sFriction_.value_or(friction_);
    initVelocity_ = correctVelocity;
    finalPosition_ = mainPosition + correctVelocity / (friction * -FRICTION_SCALE);

    if (calePredictSnapOffsetCallback_) {
        std::optional<float> predictSnapOffset =
          calePredictSnapOffsetCallback_(GetFinalPosition() - mainPosition, GetDragOffset(), correctVelocity);
        if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
            currentPos_ = mainPosition;
            ProcessScrollSnapSpringMotion(predictSnapOffset.value(), correctVelocity);
            return;
        }
    }
    if (scrollSnapCallback_ && scrollSnapCallback_(GetFinalPosition() - mainPosition, correctVelocity)) {
        currentVelocity_ = 0.0;
        return;
    }
    if (NearZero(correctVelocity, FRICTION_VELOCITY_THRESHOLD)) {
        HandleScrollEnd(correctVelocity);
        currentVelocity_ = 0.0;
#ifdef OHOS_PLATFORM
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
        return;
    }
    // change motion param when list item need to be center of screen on watch
    FixScrollMotion(mainPosition, correctVelocity);
    // Resets values.
    currentPos_ = mainPosition;
    currentVelocity_ = 0.0;
    lastPosition_ = currentPos_;
    frictionVelocity_ = initVelocity_;
    frictionOffsetProperty_->Set(mainPosition);
    float response = fabs(2 * M_PI / (FRICTION_SCALE * friction));
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, 1.0f, 0.0f);
    AnimationOption option;
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    frictionOffsetProperty_->SetThresholdType(ThresholdType::LAYOUT);
    frictionOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable friction animation start, start:%f, end:%f, vel:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, initVelocity_, nodeId_, nodeTag_.c_str());
    frictionOffsetProperty_->AnimateWithVelocity(
        option, finalPosition_, initVelocity_, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->isFrictionAnimationStop_ = true;
            ACE_SCOPED_TRACE(
                "Scrollable friction animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            scroll->ProcessScrollMotionStop(true);
        });
    isFrictionAnimationStop_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    lastVsyncTime_ = context->GetVsyncTime();
}

void Scrollable::SetDelayedTask()
{
    SetContinuousDragStatus(true);
    auto context = OHOS::Ace::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    task_.Reset([weak = WeakClaim(this)] {
        auto drag = weak.Upgrade();
        if (drag) {
            drag->ResetContinueDragCount();
            drag->SetContinuousDragStatus(false);
        }
    });
    taskExecutor.PostDelayedTask(task_, DRAG_INTERVAL_TIME, "ArkUIScrollDragInterval");
}

void Scrollable::MarkNeedFlushAnimationStartTime()
{
    auto context = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushAnimationStartTime();
}

double Scrollable::ComputeCap(int dragCount)
{
    if (dragCount < FIRST_THRESHOLD) {
        return 1.0;
    }
    auto cap = ComputeCap(dragCount - 1) + CAP_COEFFICIENT * (dragCount - 1);
    return cap;
}

double Scrollable::GetGain(double delta)
{
    auto cap = 1.0;
    auto gain = 1.0;
    if (!continuousSlidingCallback_) {
        preGain_ = gain;
        return gain;
    }
    auto screenHeight = continuousSlidingCallback_();
    if (delta == 0 || screenHeight == 0) {
        preGain_ = gain;
        return gain;
    }
    if (dragCount_ >= FIRST_THRESHOLD && dragCount_ < SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            preGain_ = gain;
            return gain;
        }
        cap = CAP_COEFFICIENT * (dragCount_ - 1);
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1))) ? preGain_ + cap :
            preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1);
    } else if (dragCount_ >= SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            preGain_ = gain;
            return gain;
        }
        cap = CAP_FIXED_VALUE;
        gain = (LessNotEqual(cap, preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1))) ? cap :
            preGain_ + std::abs(delta) / screenHeight * (dragCount_ - 1);
    }
    preGain_ = gain;
    return gain;
}

void Scrollable::ExecuteScrollBegin(double& mainDelta)
{
    auto context = context_.Upgrade();
    if (!scrollBeginCallback_ || !context) {
        return;
    }

    ScrollInfo scrollInfo;
    if (axis_ == Axis::VERTICAL) {
        scrollInfo = scrollBeginCallback_(0.0_vp, Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP));
        mainDelta = context->NormalizeToPx(scrollInfo.dy);
    } else if (axis_ == Axis::HORIZONTAL) {
        scrollInfo = scrollBeginCallback_(Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP), 0.0_vp);
        mainDelta = context->NormalizeToPx(scrollInfo.dx);
    }
}

float Scrollable::GetFrictionVelocityByFinalPosition(float final, float position, float friction,
    float signum, float threshold)
{
    return DEFAULT_THRESHOLD * threshold * signum - (final - position) * friction;
}

void Scrollable::FixScrollMotion(float position, float initVelocity)
{
#ifdef WEARABLE_PRODUCT
    float signum = 0.0;
    if (!NearZero(initVelocity)) {
        signum = GreatNotEqual(initVelocity, 0.0) ? 1.0 : -1.0;
    }
    if (frictionOffsetProperty_ && needCenterFix_ && watchFixCallback_) {
        float finalPosition = watchFixCallback_(GetFinalPosition(), position);
        if (!NearEqual(finalPosition, GetFinalPosition(), DISTANCE_EPSILON)) {
            float friction = sFriction_.value_or(friction_);
            float velocity = GetFrictionVelocityByFinalPosition(finalPosition, position, friction, signum);

            // fix again when velocity is less than velocity threshold
            if (!NearEqual(finalPosition, GetFinalPosition(), DISTANCE_EPSILON)) {
                velocity = GetFrictionVelocityByFinalPosition(finalPosition, position, friction, signum, 0.0f);
            }
            initVelocity_ = velocity;
            finalPosition_ = mainPosition + initVelocity_ / (friction * -FRICTION_SCALE);
        }
    }
#endif
}

void Scrollable::StartScrollSnapMotion(float predictSnapOffset, float scrollSnapVelocity)
{
    endPos_ = currentPos_ + predictSnapOffset;
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        GetSnapProperty();
    }
    snapOffsetProperty_->Set(currentPos_);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("List snap animation start, start:%f, end:%f, vel:%f, id:%d", currentPos_, endPos_,
        scrollSnapVelocity, nodeId_);
    updateSnapAnimationCount_++;
    snapOffsetProperty_->AnimateWithVelocity(option, endPos_, scrollSnapVelocity,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            ACE_SCOPED_TRACE("List snap animation finish, id:%d", scroll->nodeId_);
            scroll->updateSnapAnimationCount_--;
            if (scroll->updateSnapAnimationCount_ == 0) {
                scroll->isSnapScrollAnimationStop_ = true;
                scroll->ProcessScrollSnapStop();
            }
    });
    isSnapScrollAnimationStop_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    lastVsyncTime_ = context->GetVsyncTime();
}

void Scrollable::ProcessScrollSnapSpringMotion(float scrollSnapDelta, float scrollSnapVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The snap delta of scroll motion is %{public}f, "
        "The snap velocity of scroll motion is %{public}f",
        scrollSnapDelta, scrollSnapVelocity);
    endPos_ = currentPos_ + scrollSnapDelta;
    ACE_SCOPED_TRACE("Scroll snap animation start, start:%f, end:%f, vel:%f, id:%d", currentPos_, endPos_,
        scrollSnapVelocity, nodeId_);
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        GetSnapProperty();
    }
    snapOffsetProperty_->Set(currentPos_);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    snapOffsetProperty_->AnimateWithVelocity(option, endPos_, scrollSnapVelocity,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->isSnapAnimationStop_ = true;
            ACE_SCOPED_TRACE("Scroll snap animation finish, id:%d", scroll->nodeId_);
            scroll->ProcessScrollMotionStop(false);
    });
    isSnapAnimationStop_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    lastVsyncTime_ = context->GetVsyncTime();
}

void Scrollable::UpdateScrollSnapStartOffset(double offset)
{
    UpdateScrollSnapEndWithOffset(offset);
}

void Scrollable::ProcessScrollSnapMotion(double position)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}f, position is %{public}f",
        currentPos_, position);
    currentVelocity_ = snapVelocity_;
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        auto mainDelta = position - currentPos_;
        HandleScroll(mainDelta, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
        if (!moved_ && !isSnapScrollAnimationStop_) {
            StopSnapAnimation();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = position;
    if (outBoundaryCallback_ && outBoundaryCallback_()  && !isSnapScrollAnimationStop_) {
        scrollPause_ = true;
        skipRestartSpring_ = true;
        MarkNeedFlushAnimationStartTime();
        StopSnapAnimation();
    }
}

void Scrollable::ProcessScrollSnapStop()
{
    if (scrollPause_) {
        scrollPause_ = false;
        HandleOverScroll(currentVelocity_);
    } else {
        OnAnimateStop();
    }
}

void Scrollable::OnAnimateStop()
{
    HandleScrollEnd(std::nullopt);
    currentVelocity_ = 0.0;
    if (isTouching_ || isDragUpdateStop_) {
        return;
    }
    moved_ = false;
#ifdef OHOS_PLATFORM
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndListFling();
    }
#endif
    if (scrollEnd_) {
        scrollEnd_();
    }
#if !defined(PREVIEW)
    LayoutInspector::SupportInspector();
#endif
}

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}f, mainVelocity is %{public}f, minExtent is "
        "%{public}f, maxExtent is %{public}f, initMinExtent is %{public}f, initMaxExtent is %{public}f",
        mainPosition, mainVelocity, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    if (!isSpringAnimationStop_ || (skipRestartSpring_ && NearEqual(mainVelocity, 0.0f, 0.001f))) {
        return;
    }
    currentPos_ = mainPosition;
    if (mainPosition > initExtent.Trailing() || NearEqual(mainPosition, initExtent.Trailing(), 0.01f)) {
        finalPosition_ = extent.Trailing();
    } else if (mainPosition <  initExtent.Leading() || NearEqual(mainPosition, initExtent.Leading(), 0.01f)) {
        finalPosition_ = extent.Leading();
    } else {
        return;
    }

    if (!springOffsetProperty_) {
        GetSpringProperty();
    }
    springAnimationCount_++;
    springOffsetProperty_->Set(mainPosition);
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    springOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable spring animation start, start:%f, end:%f, vel:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, mainVelocity, nodeId_, nodeTag_.c_str());
    lastVsyncTime_ = static_cast<uint64_t>(GetSysTimestamp());
    springOffsetProperty_->AnimateWithVelocity(
        option, finalPosition_, mainVelocity, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springAnimationCount_--;
            ACE_SCOPED_TRACE(
                "Scrollable spring animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            // avoid current animation being interrupted by the prev animation's finish callback
            // and triggering onScrollStop when spring animation turns to friction animation.
            if (scroll->springAnimationCount_ > 0 || scroll->scrollPause_) {
                return;
            }
            scroll->isSpringAnimationStop_ = true;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
        });
    isSpringAnimationStop_ = false;
    skipRestartSpring_ = false;
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
}

void Scrollable::UpdateSpringMotion(
    double mainPosition, const ExtentPair& extent, const ExtentPair& initExtent)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}f, minExtent is "
        "%{public}f, maxExtent is %{public}f, initMinExtent is %{public}f, initMaxExtent is %{public}f",
        mainPosition, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    if (isSpringAnimationStop_) {
        return;
    }
    float finalPosition = 0.0f;
    if (mainPosition > initExtent.Trailing() || NearEqual(mainPosition, initExtent.Trailing())) {
        finalPosition = extent.Trailing();
    } else if (mainPosition <  initExtent.Leading() || NearEqual(mainPosition, initExtent.Leading())) {
        finalPosition = extent.Leading();
    } else {
        return;
    }

    finalPosition = finalPosition_ + (finalPosition - mainPosition) - (finalPosition_ - currentPos_);
    if (NearEqual(finalPosition, finalPosition_, SPRING_ACCURACY)) {
        return;
    }
    finalPosition_ = finalPosition;
    springAnimationCount_++;
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    springOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_SCOPED_TRACE("Scrollable spring animation update, start:%f, end:%f, id:%d, tag:%s", mainPosition,
        finalPosition_, nodeId_, nodeTag_.c_str());
    AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springOffsetProperty_->Set(scroll->finalPosition_);
            scroll->isSpringAnimationStop_ = false;
        },
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springAnimationCount_--;
            // avoid current animation being interrupted by the prev animation's finish callback
            if (scroll->springAnimationCount_ > 0) {
                return;
            }
            ACE_SCOPED_TRACE(
                "Scrollable updated spring animation finish, id:%d, tag:%s", scroll->nodeId_, scroll->nodeTag_.c_str());
            scroll->isSpringAnimationStop_ = true;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
    });
    isSpringAnimationStop_ = false;
    skipRestartSpring_ = false;
}

void Scrollable::ProcessScrollMotionStop(bool stopFriction)
{
    if (needScrollSnapChange_ && calePredictSnapOffsetCallback_ && frictionOffsetProperty_) {
        needScrollSnapChange_ = false;
        auto predictSnapOffset = calePredictSnapOffsetCallback_(GetFinalPosition() - currentPos_, 0.0f, 0.0f);
        if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
            ProcessScrollSnapSpringMotion(predictSnapOffset.value(), currentVelocity_);
            return;
        }
    }
    // spring effect special process
    if (scrollPause_) {
        scrollPause_ = false;
        HandleOverScroll(currentVelocity_);
    } else {
        if (isDragUpdateStop_) {
            return;
        }
        moved_ = false;
        HandleScrollEnd(std::nullopt);
#ifdef OHOS_PLATFORM
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
        if (scrollEnd_) {
            scrollEnd_();
        }
        currentVelocity_ = 0.0;
#if !defined(PREVIEW)
        LayoutInspector::SupportInspector();
#endif
    }
}

void Scrollable::ProcessSpringMotion(double position)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}f, position is %{public}f",
        currentPos_, position);
    auto context = OHOS::Ace::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    uint64_t diff = currentVsync - lastVsyncTime_;
    if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
        currentVelocity_ = (position - currentPos_) / diff * MILLOS_PER_NANO_SECONDS;
    }
    lastVsyncTime_ = currentVsync;
    if (LessOrEqual(std::abs(currentPos_ - position), 1)) {
        // trace stop at OnScrollStop
        if (!isFadingAway_) {
            AceAsyncTraceBegin(0, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") + nodeTag_).c_str());
        }
    }
    auto distance = currentPos_ - finalPosition_;
    auto nextDistance = position - finalPosition_;
    isFadingAway_ = GreatNotEqual(std::abs(nextDistance), std::abs(distance));
    auto delta = position - currentPos_;
    if (distance * nextDistance < 0) {
        double currentVelocity = currentVelocity_;
        scrollPause_ = true;
        MarkNeedFlushAnimationStartTime();
        StopSpringAnimation();
        ACE_SCOPED_TRACE("change direction in spring animation and start fling animation, distance:%f, "
                            "nextDistance:%f, nodeId:%d, tag:%s",
            distance, nextDistance, nodeId_, nodeTag_.c_str());
        // only handle offsets that are out of bounds
        delta = finalPosition_ - currentPos_;
        // remainVelocityCallback_ will pass the velocity to the child component
        if (!remainVelocityCallback_ || !remainVelocityCallback_(currentVelocity)) {
            StartScrollAnimation(position, currentVelocity);
        }
    }
    moved_ = UpdateScrollPosition(delta, SCROLL_FROM_ANIMATION_SPRING);
    if (!moved_) {
        StopSpringAnimation();
    } else if (!touchUp_) {
        if (scrollTouchUpCallback_) {
            scrollTouchUpCallback_();
        }
        touchUp_ = true;
    }
    currentPos_ = position;
}

void Scrollable::ProcessScrollMotion(double position)
{
    currentVelocity_ = frictionVelocity_;
    if (needScrollSnapToSideCallback_) {
        needScrollSnapChange_ = needScrollSnapToSideCallback_(position - currentPos_);
    }
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}f, currentVelocity_ is %{public}f, "
        "needScrollSnapChange_ is %{public}u",
        position, currentVelocity_, needScrollSnapChange_);
    if (LessOrEqual(std::abs(currentPos_ - position), 1)) {
        // trace stop at OnScrollStop
        AceAsyncTraceBegin(0, (TRAILING_ANIMATION + std::to_string(nodeId_) + std::string(" ") + nodeTag_).c_str());
    }
    // UpdateScrollPosition return false, means reach to scroll limit.
    auto mainDelta = position - currentPos_;
    HandleScroll(mainDelta, SCROLL_FROM_ANIMATION, NestedState::GESTURE);
    if (!moved_) {
        StopFrictionAnimation();
    } else if (!touchUp_) {
        if (scrollTouchUpCallback_) {
            scrollTouchUpCallback_();
        }
        touchUp_ = true;
    }
    currentPos_ = position;

    // spring effect special process
    if ((IsSnapStopped() && canOverScroll_) || needScrollSnapChange_ ||
        (!Container::IsCurrentUseNewPipeline() && outBoundaryCallback_ && outBoundaryCallback_())) {
        ACE_SCOPED_TRACE("scrollPause set true to stop ProcessScrollMotion, canOverScroll:%u, needScrollSnapChange:%u, "
            "nodeId:%d, tag:%s", canOverScroll_, needScrollSnapChange_, nodeId_, nodeTag_.c_str());
        scrollPause_ = true;
        skipRestartSpring_ = true;
        MarkNeedFlushAnimationStartTime();
        StopFrictionAnimation();
    }
}

bool Scrollable::UpdateScrollPosition(const double offset, int32_t source) const
{
    bool ret = true;
    if (callback_) {
        ret = callback_(offset, source);
    }
    return ret;
}

void Scrollable::ProcessScrollOverCallback(double velocity)
{
    if (outBoundaryCallback_ && !outBoundaryCallback_() && !canOverScroll_) {
        return;
    }
    // In the case of chain animation enabled, you need to switch the control point first,
    // and then correct the offset value in notification process
    if (notifyScrollOverCallback_) {
        notifyScrollOverCallback_(velocity);
    }
    // then use corrected offset to make scroll motion.
    if (scrollOverCallback_) {
        scrollOverCallback_(velocity);
    }
}

bool Scrollable::HandleOverScroll(double velocity)
{
    if (!overScrollCallback_) {
        if (edgeEffect_ == EdgeEffect::SPRING) {
            ProcessScrollOverCallback(velocity);
            return true;
        }
        if (scrollEndCallback_) {
            scrollEndCallback_();
        }
        return false;
    }
    // call NestableScrollContainer::HandleOverScroll
    return overScrollCallback_(velocity);
}

void Scrollable::SetSlipFactor(double SlipFactor)
{
    slipFactor_ = std::clamp(SlipFactor, -ADJUSTABLE_VELOCITY, ADJUSTABLE_VELOCITY);
}

void Scrollable::UpdateScrollSnapEndWithOffset(double offset)
{
    if (!isSnapScrollAnimationStop_) {
        AnimationOption option;
        option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
        auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
        option.SetCurve(curve);
        if (!snapOffsetProperty_) {
            GetSnapProperty();
        }
        updateSnapAnimationCount_++;
        endPos_ -= offset;
        snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->snapOffsetProperty_->Set(scroll->endPos_);
                scroll->isSnapScrollAnimationStop_ = false;
            },
            [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
                ContainerScope scope(id);
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->updateSnapAnimationCount_--;
                // avoid current animation being interrupted by the prev animation's finish callback
                if (scroll->updateSnapAnimationCount_ == 0) {
                    scroll->isSnapScrollAnimationStop_ = true;
                    scroll->ProcessScrollSnapStop();
                }
        });
        isSnapScrollAnimationStop_ = false;
    }
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetFrictionProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->isFrictionAnimationStop_ || scroll->isTouching_) {
            return;
        }
        scroll->isSnapAnimation_ = false;
        scroll->ProcessScrollMotion(position);
        if (NearEqual(scroll->finalPosition_, position, 1.0)) {
            scroll->StopFrictionAnimation();
        }
        auto context = OHOS::Ace::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        uint64_t currentVsync = context->GetVsyncTime();
        uint64_t diff = currentVsync - scroll->lastVsyncTime_;
        if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
            scroll->frictionVelocity_ = (position - scroll->lastPosition_) / diff * MILLOS_PER_NANO_SECONDS;
            if (NearZero(scroll->frictionVelocity_, FRICTION_VELOCITY_THRESHOLD)) {
                scroll->StopFrictionAnimation();
                ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
            }
        }
        scroll->lastVsyncTime_ = currentVsync;
        scroll->lastPosition_ = position;
    };
    frictionOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    return frictionOffsetProperty_;
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSpringProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->isSpringAnimationStop_) {
            return;
        }
        if (!NearEqual(scroll->finalPosition_, position, SPRING_ACCURACY)) {
            scroll->ProcessSpringMotion(position);
            return;
        }
        /*
         * In order to prevent accumulation errors, the current position is re obtained to ensure that
         * the last frame can accurately stop at the top and bottom positions.
         */
        if (scroll->currentPositionCallback_) {
            double currPos = scroll->currentPositionCallback_();
            if (NearEqual(currPos, scroll->currentPos_, 0.5)) {
                scroll->currentPos_ = currPos;
            }
        }
        scroll->ProcessSpringMotion(scroll->finalPosition_);
        scroll->StopSpringAnimation();
    };
    springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    return springOffsetProperty_;
}

RefPtr<NodeAnimatablePropertyFloat> Scrollable::GetSnapProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        if (scroll->isSnapScrollAnimationStop_ && scroll->isSnapAnimationStop_) {
            return;
        }
        auto context = OHOS::Ace::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        uint64_t currentVsync = context->GetVsyncTime();
        uint64_t diff = currentVsync - scroll->lastVsyncTime_;
        if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
            scroll->snapVelocity_ = (position - scroll->currentPos_) / diff * MILLOS_PER_NANO_SECONDS;
        }
        scroll->lastVsyncTime_ = currentVsync;
        if (NearEqual(scroll->endPos_, position, SPRING_ACCURACY)) {
            if (!scroll->isSnapScrollAnimationStop_) {
                scroll->ProcessScrollSnapMotion(scroll->endPos_);
            } else if (!scroll->isSnapAnimationStop_) {
                scroll->isSnapAnimation_ = true;
                scroll->ProcessScrollMotion(scroll->endPos_);
            }
            scroll->StopSnapAnimation();
        } else {
            if (!scroll->isSnapScrollAnimationStop_) {
                scroll->ProcessScrollSnapMotion(position);
            } else if (!scroll->isSnapAnimationStop_) {
                scroll->isSnapAnimation_ = true;
                scroll->ProcessScrollMotion(position);
            }
        }
    };
    snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    return snapOffsetProperty_;
}

void Scrollable::StopFrictionAnimation()
{
    if (!isFrictionAnimationStop_) {
        ACE_SCOPED_TRACE("StopFrictionAnimation, id:%d, tag:%s", nodeId_, nodeTag_.c_str());
        isFrictionAnimationStop_ = true;
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->frictionOffsetProperty_->Set(scroll->currentPos_);
            },
            nullptr);
    }
}

void Scrollable::StopSpringAnimation(bool reachFinalPosition)
{
    if (!isSpringAnimationStop_) {
        ACE_SCOPED_TRACE(
            "StopSpringAnimation, reachFinalPosition:%u, id:%d, tag:%s", reachFinalPosition, nodeId_, nodeTag_.c_str());
        isSpringAnimationStop_ = true;
        isFadingAway_ = false;
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this), reachFinalPosition]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                if (reachFinalPosition) {
                    // ensure that the spring animation is restored to its final position.
                    scroll->ProcessSpringMotion(scroll->finalPosition_);
                    // use non final position to stop animation, otherwise the animation cannot be stoped.
                    scroll->springOffsetProperty_->Set(scroll->finalPosition_ - 1.f);
                } else {
                    // avoid top edge spring can not stop
                    scroll->springOffsetProperty_->Set(scroll->currentPos_);
                }
            },
            nullptr);
    }
    currentVelocity_ = 0.0;
}

void Scrollable::StopSnapAnimation()
{
    if (!isSnapAnimationStop_ || !isSnapScrollAnimationStop_) {
        ACE_SCOPED_TRACE("StopSnapAnimation, isSnapAnimationStop_:%u, isSnapScrollAnimationStop_:%u, id:%d, tag:%s",
            isSnapAnimationStop_, isSnapScrollAnimationStop_, nodeId_, nodeTag_.c_str());
        isSnapAnimationStop_ = true;
        isSnapScrollAnimationStop_ = true;
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->snapOffsetProperty_->Set(scroll->currentPos_);
            },
            nullptr);
    }
}

inline bool Scrollable::IsMouseWheelScroll(const GestureEvent& info)
{
    return info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() != SourceTool::TOUCHPAD;
}

void Scrollable::OnCollectTouchTarget(TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    if (panRecognizerNG_) {
        panRecognizerNG_->SetNodeId(frameNode->GetId());
        panRecognizerNG_->AttachFrameNode(frameNode);
        panRecognizerNG_->SetTargetComponent(targetComponent);
        panRecognizerNG_->SetIsSystemGesture(true);
        panRecognizerNG_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        result.emplace_back(panRecognizerNG_);
        responseLinkResult.emplace_back(panRecognizerNG_);
    }
}
} // namespace OHOS::Ace::NG
