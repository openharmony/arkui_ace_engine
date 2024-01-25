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

#include "core/components_ng/pattern/scrollable/scrollable.h"

#include <chrono>

#include "base/log/ace_trace.h"
#include "base/log/frame_report.h"
#include "base/log/jank_frame_report.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/layout_inspector.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::NG {
namespace {

constexpr double CAP_COEFFICIENT = 0.45;
constexpr int32_t FIRST_THRESHOLD = 5;
constexpr int32_t SECOND_THRESHOLD = 10;
constexpr double CAP_FIXED_VALUE = 16.0;
constexpr uint32_t DRAG_INTERVAL_TIME = 900;

#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double NEW_FRICTION = 0.7;
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
constexpr float FRICTION_VELOCITY_THRESHOLD = 42.0f;
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

void Scrollable::SetFriction(double sFriction)
{
    if (LessOrEqual(sFriction, 0.0)) {
        return;
    }
    sFriction_ = sFriction;
}

Scrollable::Scrollable()
{
    friction_ = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_FRICTION : FRICTION;
    velocityScale_ =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::Scrollable(ScrollPositionCallback&& callback, Axis axis) : callback_(std::move(callback)), axis_(axis)
{
    friction_ = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_FRICTION : FRICTION;
    velocityScale_ =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::Scrollable(const ScrollPositionCallback& callback, Axis axis) : callback_(callback), axis_(axis)
{
    friction_ = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_FRICTION : FRICTION;
    velocityScale_ =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
}

Scrollable::~Scrollable()
{
    // If animation still runs, force stop it.
    StopFrictionAnimation();
    StopSpringAnimation();
    StopSnapAnimation();
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

    auto actionEnd = [weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleDragEnd(info);
            if (scroll->actionEnd_) {
                auto gestureEvent = info;
                scroll->actionEnd_(gestureEvent);
            }
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
    if (isDragging_) {
        return;
    }
    isTouching_ = false;
    if (outBoundaryCallback_ && !outBoundaryCallback_()) {
        if (isSnapScrollAnimationStop_ && scrollSnapCallback_) {
            scrollSnapCallback_(0.0, 0.0);
        }
        return;
    }
    if (isSpringAnimationStop_ && scrollOverCallback_) {
        ProcessScrollOverCallback(0.0);
    }
}

void Scrollable::HandleTouchCancel()
{
    isTouching_ = false;
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
        && isSnapAnimationStop_ && isSnapScrollAnimationStop_;
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
    ACE_FUNCTION_TRACE();
    if (info.GetSourceTool() == SourceTool::TOUCHPAD) {
        isTouching_ = true;
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
    const auto dragPositionInMainAxis =
        axis_ == Axis::VERTICAL ? info.GetGlobalLocation().GetY() : info.GetGlobalLocation().GetX();
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Scroll drag start, localLocation: %{public}s, globalLocation: %{public}s",
        info.GetLocalLocation().ToString().c_str(), info.GetGlobalLocation().ToString().c_str());
#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding start.
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (!moved_ || increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        startIncreaseTime_ = currentTime;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
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
        moved_ = UpdateScrollPosition(offset, source);
        canOverScroll_ = false;
        return { 0, false };
    }
    // call NestableScrollContainer::HandleScroll
    return handleScrollCallback_(static_cast<float>(offset), source, state);
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
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
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    auto mainDelta = info.GetMainDelta();
    mainDelta = Round(mainDelta);
    JankFrameReport::GetInstance().RecordFrameUpdate();
    auto source = IsMouseWheelScroll(info) ? SCROLL_FROM_AXIS : SCROLL_FROM_UPDATE;
    HandleScroll(mainDelta, source, NestedState::GESTURE);
}

void Scrollable::HandleDragEnd(const GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
    // avoid no render frame when drag end
    HandleDragUpdate(info);

    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Scroll drag end, position is %{public}lf and %{public}lf, "
        "velocity is %{public}lf",
        info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY(), info.GetMainVelocity());
    if (dragFRCSceneCallback_) {
        dragFRCSceneCallback_(info.GetMainVelocity(), NG::SceneStatus::END);
    }
    isTouching_ = false;
    isDragUpdateStop_ = false;
    touchUp_ = false;
    scrollPause_ = false;
    lastVelocity_ = info.GetMainVelocity();
    double correctVelocity = info.GetMainVelocity();
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    correctVelocity = correctVelocity * sVelocityScale_.value_or(velocityScale_) * GetGain(GetDragOffset());
    // Apply max fling velocity limit, it must be calculated after all fling velocity gain.
    correctVelocity = std::clamp(correctVelocity, -maxFlingVelocity_ + slipFactor_, maxFlingVelocity_ - slipFactor_);
    currentVelocity_ = correctVelocity;

    lastPos_ = GetDragOffset();
    JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_SCROLL);
    if (dragEndCallback_) {
        dragEndCallback_();
    }
    double mainPosition = GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()));
    mainPosition = Round(mainPosition);
    if (!moved_ || IsMouseWheelScroll(info)) {
        if (calePredictSnapOffsetCallback_) {
            std::optional<float> predictSnapOffset = calePredictSnapOffsetCallback_(0.0f, 0.0f, 0.0f);
            if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
                currentPos_ = mainPosition;
                ProcessScrollSnapSpringMotion(predictSnapOffset.value(), correctVelocity);
                return;
            }
        }
        HandleScrollEnd(correctVelocity);
        currentVelocity_ = 0.0;
#ifdef OHOS_PLATFORM
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
    } else if (!Container::IsCurrentUseNewPipeline() && outBoundaryCallback_ && outBoundaryCallback_() &&
               scrollOverCallback_) {
        ResetContinueDragCount();
        ProcessScrollOverCallback(correctVelocity);
    } else if (canOverScroll_) {
        ResetContinueDragCount();
        HandleOverScroll(correctVelocity);
    } else {
        StartScrollAnimation(mainPosition, correctVelocity);
    }
    SetDelayedTask();
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
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The position of scroll motion is %{public}lf, velocity is %{public}lf",
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
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
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
    ACE_DEBUG_SCOPED_TRACE(
        "Scrollable start friction animation, start:%f, end:%f, vel:%f", mainPosition, finalPosition_, initVelocity_);
    frictionOffsetProperty_->AnimateWithVelocity(option, finalPosition_, initVelocity_,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->isFrictionAnimationStop_ = true;
            ACE_DEBUG_SCOPED_TRACE("Scrollable friction animation finish");
            scroll->ProcessScrollMotionStop(true);
    });
    isFrictionAnimationStop_ = false;
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
    taskExecutor.PostDelayedTask(task_, DRAG_INTERVAL_TIME);
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
        return gain;
    }
    auto screenHeight = continuousSlidingCallback_();
    if (delta == 0 || screenHeight == 0) {
        return gain;
    }
    if (dragCount_ >= FIRST_THRESHOLD && dragCount_ < SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            return gain;
        }
        cap = ComputeCap(dragCount_);
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1))) ? cap :
            std::abs(delta) / screenHeight * (dragCount_ - 1);
    } else if (dragCount_ >= SECOND_THRESHOLD) {
        if (Negative(lastPos_ / delta)) {
            ResetContinueDragCount();
            return gain;
        }
        cap = CAP_FIXED_VALUE;
        gain = (LessNotEqual(cap, std::abs(delta) / screenHeight * (dragCount_ - 1))) ? cap :
            std::abs(delta) / screenHeight * (dragCount_ - 1);
    }
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
    snapOffsetProperty_->AnimateWithVelocity(option, endPos_, scrollSnapVelocity,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            if (scroll->updateSnapAnimationCount_ == 0) {
                scroll->isSnapScrollAnimationStop_ = true;
                scroll->ProcessScrollSnapStop();
            }
    });
    isSnapScrollAnimationStop_ = false;
}

void Scrollable::ProcessScrollSnapSpringMotion(float scrollSnapDelta, float scrollSnapVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The snap delta of scroll motion is %{public}f, "
        "The snap velocity of scroll motion is %{public}f",
        scrollSnapDelta, scrollSnapVelocity);
    endPos_ = currentPos_ + scrollSnapDelta;
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
            scroll->ProcessScrollMotionStop(false);
    });
    isSnapAnimationStop_ = false;
}

void Scrollable::UpdateScrollSnapStartOffset(double offset)
{
    UpdateScrollSnapEndWithOffset(offset);
}

void Scrollable::ProcessScrollSnapMotion(double position)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}lf, position is %{public}lf",
        currentPos_, position);
    currentVelocity_ = snapVelocity_;
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION_SPRING);
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
    if (moved_) {
        HandleScrollEnd(std::nullopt);
    }
    currentVelocity_ = 0.0;
    if (isTouching_ || isDragUpdateStop_) {
        return;
    }
    moved_ = false;
#ifdef OHOS_PLATFORM
    ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
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
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}lf, mainVelocity is %{public}lf, minExtent is "
        "%{public}lf, maxExtent is %{public}lf, initMinExtent is %{public}lf, initMaxExtent is %{public}lf",
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
    ACE_DEBUG_SCOPED_TRACE(
        "Scrollable start spring animation, start:%f, end:%f, vel:%f", mainPosition, finalPosition_, mainVelocity);
    springOffsetProperty_->AnimateWithVelocity(option, finalPosition_, mainVelocity,
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto scroll = weak.Upgrade();
            CHECK_NULL_VOID(scroll);
            scroll->springAnimationCount_--;
            // avoid current animation being interrupted by the prev animation's finish callback
            if (scroll->springAnimationCount_ > 0) {
                return;
            }
            ACE_DEBUG_SCOPED_TRACE("Scrollable spring animation finish");
            scroll->isSpringAnimationStop_ = true;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
    });
    ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
    isSpringAnimationStop_ = false;
    skipRestartSpring_ = false;
}

void Scrollable::UpdateSpringMotion(
    double mainPosition, const ExtentPair& extent, const ExtentPair& initExtent)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}lf, minExtent is "
        "%{public}lf, maxExtent is %{public}lf, initMinExtent is %{public}lf, initMaxExtent is %{public}lf",
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

    finalPosition_ = finalPosition_ + (finalPosition - mainPosition) - (finalPosition_ - currentPos_);
    springAnimationCount_++;
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    springOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    ACE_DEBUG_SCOPED_TRACE(
        "Scrollable update spring animation, start:%f, end:%f", mainPosition, finalPosition_);
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
            ACE_DEBUG_SCOPED_TRACE("Scrollable spring animation finish");
            scroll->isSpringAnimationStop_ = true;
            scroll->currentVelocity_ = 0.0;
            scroll->OnAnimateStop();
    });
    
    ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
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
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
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
    position = Round(position);
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "Current Pos is %{public}lf, position is %{public}lf",
        currentPos_, position);
    auto context = OHOS::Ace::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    uint64_t diff = currentVsync - lastVsyncTime_;
    if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
        currentVelocity_ = (position - currentPos_) / diff * MILLOS_PER_NANO_SECONDS;
    }
    lastVsyncTime_ = currentVsync;
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION_SPRING);
    } else {
        moved_ = UpdateScrollPosition(position - currentPos_, SCROLL_FROM_ANIMATION_SPRING);
        if (!moved_) {
            StopSpringAnimation();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = position;
}

void Scrollable::ProcessScrollMotion(double position)
{
    position = Round(position);
    currentVelocity_ = frictionVelocity_;
    if (needScrollSnapToSideCallback_) {
        needScrollSnapChange_ = needScrollSnapToSideCallback_(position - currentPos_);
    }
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "position is %{public}lf, currentVelocity_ is %{public}lf, "
        "needScrollSnapChange_ is %{public}u",
        position, currentVelocity_, needScrollSnapChange_);
    if ((NearEqual(currentPos_, position))) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
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
    }
    currentPos_ = position;

    // spring effect special process
    if ((IsSnapStopped() && canOverScroll_) || needScrollSnapChange_ ||
        (!Container::IsCurrentUseNewPipeline() && outBoundaryCallback_ && outBoundaryCallback_())) {
        scrollPause_ = true;
        skipRestartSpring_ = true;
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
        if (!scroll->isSpringAnimationStop_) {
            if (NearEqual(scroll->finalPosition_, position, SPRING_ACCURACY)) {
                scroll->ProcessSpringMotion(scroll->finalPosition_);
                scroll->StopSpringAnimation();
            } else {
                scroll->ProcessSpringMotion(position);
            }
        }
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
                scroll->ProcessScrollMotion(scroll->endPos_);
            }
            scroll->StopSnapAnimation();
        } else {
            if (!scroll->isSnapScrollAnimationStop_) {
                scroll->ProcessScrollSnapMotion(position);
            } else if (!scroll->isSnapAnimationStop_) {
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
        ACE_DEBUG_SCOPED_TRACE("Scrollable stop friction animation");
        isFrictionAnimationStop_ = true;
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                scroll->frictionOffsetProperty_->Set(0.0f);
            },
            nullptr);
    }
}

void Scrollable::StopSpringAnimation()
{
    if (!isSpringAnimationStop_) {
        ACE_DEBUG_SCOPED_TRACE("Scrollable stop spring animation");
        isSpringAnimationStop_ = true;
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = AceType::WeakClaim(this)]() {
                auto scroll = weak.Upgrade();
                CHECK_NULL_VOID(scroll);
                //avoid top edge spring can not stop
                scroll->springOffsetProperty_->Set(scroll->currentPos_);
            },
            nullptr);
        OnAnimateStop();
    }
    currentVelocity_ = 0.0;
}

void Scrollable::StopSnapAnimation()
{
    if (!isSnapAnimationStop_ || !isSnapScrollAnimationStop_) {
        ACE_DEBUG_SCOPED_TRACE("Scrollable stop snap animation");
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
                scroll->snapOffsetProperty_->Set(0.0f);
            },
            nullptr);
    }
}

inline bool Scrollable::IsMouseWheelScroll(const GestureEvent& info)
{
    return info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() != SourceTool::TOUCHPAD;
}

void Scrollable::OnCollectTouchTarget(
    TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent)
{
    if (panRecognizerNG_) {
        panRecognizerNG_->AssignNodeId(frameNode->GetId());
        panRecognizerNG_->AttachFrameNode(frameNode);
        panRecognizerNG_->SetTargetComponent(targetComponent);
        panRecognizerNG_->SetIsSystemGesture(true);
        result.emplace_back(panRecognizerNG_);
    }
}
} // namespace OHOS::Ace::NG
