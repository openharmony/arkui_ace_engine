/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/scroll/scrollable.h"

#include <chrono>

#include "base/log/ace_trace.h"
#include "base/log/frame_report.h"
#include "base/log/log.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/time_util.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {
namespace {

constexpr double SPRING_SCROLL_MASS = 0.5;
constexpr double SPRING_SCROLL_STIFFNESS = 100.0;
constexpr double SPRING_SCROLL_DAMPING = 15.55635;
const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
#ifndef WEARABLE_PRODUCT
constexpr double FRICTION = 0.6;
constexpr double VELOCITY_SCALE = 1.0;
constexpr double MAX_VELOCITY = 800000.0;
constexpr double MIN_VELOCITY = -800000.0;
constexpr double ADJUSTABLE_VELOCITY = 3000.0;
#else
constexpr double DISTANCE_EPSILON = 1.0;
constexpr double FRICTION = 0.9;
constexpr double VELOCITY_SCALE = 0.8;
constexpr double MAX_VELOCITY = 5000.0;
constexpr double MIN_VELOCITY = -5000.0;
constexpr double ADJUSTABLE_VELOCITY = 0.0;
#endif

#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif

} // namespace

// Static Functions.
double Scrollable::sFriction_ = FRICTION;
double Scrollable::sVelocityScale_ = VELOCITY_SCALE;

void Scrollable::SetVelocityScale(double sVelocityScale)
{
    if (LessOrEqual(sVelocityScale, 0.0)) {
        LOGW("Invalid velocity scale: %{public}lf", sVelocityScale);
        return;
    }
    sVelocityScale_ = sVelocityScale;
}

void Scrollable::SetFriction(double sFriction)
{
    if (LessOrEqual(sFriction, 0.0)) {
        LOGW("Invalid friction value: %{public}lf", sFriction);
        return;
    }
    sFriction_ = sFriction;
}

Scrollable::~Scrollable()
{
    // If animation still runs, force stop it.
    controller_->Stop();
    springController_->Stop();
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
    panRecognizer_ =
        AceType::MakeRefPtr<PanRecognizer>(context, DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE);

    panRecognizer_->SetOnActionStart([weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            // Send event to accessibility when scroll start.
            auto context = scroll->GetContext().Upgrade();
            if (context) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->nodeId_;
                scrollEvent.eventType = "scrollstart";
                context->SendEventToAccessibility(scrollEvent);
            }
            scroll->HandleDragStart(info);
        }
    });
    panRecognizer_->SetOnActionUpdate([weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleDragUpdate(info);
        }
    });
    panRecognizer_->SetOnActionEnd([weakScroll = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleDragEnd(info);
            // Send event to accessibility when scroll stop.
            auto context = scroll->GetContext().Upgrade();
            if (context && scroll->IsStopped()) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->nodeId_;
                scrollEvent.eventType = "scrollend";
                context->SendEventToAccessibility(scrollEvent);
            }
        }
    });
    panRecognizer_->SetOnActionCancel([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (!scroll) {
            return;
        }
        if (scroll->dragCancelCallback_) {
            scroll->dragCancelCallback_();
        }
    });

    // use RawRecognizer to receive next touch down event to stop animation.
    rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();

    rawRecognizer_->SetOnTouchDown([weakScroll = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleTouchDown();
        }
    });
    rawRecognizer_->SetOnTouchUp([weakScroll = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->HandleTouchUp();
        }
    });

    controller_ = AceType::MakeRefPtr<Animator>(context);
    springController_ = AceType::MakeRefPtr<Animator>(context);

    spring_ = GetDefaultOverSpringProperty();
    available_ = true;
}

void Scrollable::HandleTouchDown()
{
    LOGD("handle touch down");
    isTouching_ = true;

    if (outBoundaryCallback_ && !outBoundaryCallback_()) {
        return;
    }
    // If animation still runs, first stop it.
    springController_->Stop();
    if (!controller_->IsStopped()) {
        controller_->Stop();
    } else {
        // Resets values.
        currentPos_ = 0.0;
    }
}

void Scrollable::HandleTouchUp()
{
    LOGD("handle touch up");
    isTouching_ = false;
    if (outBoundaryCallback_ && !outBoundaryCallback_()) {
        return;
    }
    if (springController_->IsStopped() && scrollOverCallback_) {
        LOGD("need scroll to boundary");
        ProcessScrollOverCallback(0.0);
    }
}

bool Scrollable::IsAnimationNotRunning() const
{
    return !isTouching_ && !controller_->IsRunning() && !springController_->IsRunning();
}

bool Scrollable::Idle() const
{
    return !isTouching_ && controller_->IsStopped() && springController_->IsStopped();
}

bool Scrollable::IsStopped() const
{
    return (!springController_ || (springController_->IsStopped())) && (!controller_ || (controller_->IsStopped()));
}

void Scrollable::StopScrollable()
{
    if (controller_) {
        controller_->Stop();
    }
    if (springController_) {
        springController_->Stop();
    }
}

void Scrollable::HandleDragStart(const OHOS::Ace::GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
    const auto dragPositionInMainAxis =
        axis_ == Axis::VERTICAL ? info.GetGlobalLocation().GetY() : info.GetGlobalLocation().GetX();
    LOGD("HandleDragStart. LocalLocation: %{public}s, GlobalLocation: %{public}s",
        info.GetLocalLocation().ToString().c_str(), info.GetGlobalLocation().ToString().c_str());
#ifdef OHOS_PLATFORM
    // Increase the cpu frequency when sliding start.
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (!moved_ || increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        LOGI("HandleDragStart increase cpu frequency, moved_ = %{public}d", moved_);
        startIncreaseTime_ = currentTime;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    UpdateScrollPosition(dragPositionInMainAxis, SCROLL_FROM_START);
    RelatedEventStart();
    auto node = scrollableNode_.Upgrade();
    if (node) {
        node->DispatchCancelPressAnimation();
    }
}

void Scrollable::HandleDragUpdate(const GestureEvent& info)
{
    ACE_FUNCTION_TRACE();
    if (!springController_->IsStopped() || !controller_->IsStopped()) {
        // If animation still runs, first stop it.
        isDragUpdateStop_ = true;
        controller_->Stop();
        springController_->Stop();
        currentPos_ = 0.0;
    }
#ifdef OHOS_PLATFORM
    // Handle the case where you keep sliding past limit time(4s).
    auto currentTime = GetSysTimestamp();
    auto increaseCpuTime = currentTime - startIncreaseTime_;
    if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
        LOGI("HandleDragUpdate increase cpu frequency, moved_ = %{public}d", moved_);
        startIncreaseTime_ = currentTime;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginListFling();
        }
    }
#endif
    LOGD("handle drag update, offset is %{public}lf", info.GetMainDelta());
    auto mainDelta = info.GetMainDelta();
    if (RelatedScrollEventPrepare(Offset(0.0, mainDelta))) {
        return;
    }
    ExecuteScrollBegin(mainDelta);
    auto source = info.GetSourceDevice() == SourceType::MOUSE ? SCROLL_FROM_AXIS : SCROLL_FROM_UPDATE;
    moved_ = UpdateScrollPosition(mainDelta, source);
}

void Scrollable::HandleDragEnd(const GestureEvent& info)
{
    LOGD("handle drag end, position is %{public}lf and %{public}lf, velocity is %{public}lf",
        info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY(), info.GetMainVelocity());
    controller_->ClearAllListeners();
    springController_->ClearAllListeners();
    isDragUpdateStop_ = false;
    touchUp_ = false;
    scrollPause_ = false;
    double correctVelocity = std::clamp(info.GetMainVelocity(), MIN_VELOCITY + slipFactor_, MAX_VELOCITY - slipFactor_);
    correctVelocity = correctVelocity * sVelocityScale_;
    currentVelocity_ = correctVelocity;
    if (dragEndCallback_) {
        dragEndCallback_();
    }
    RelatedEventEnd();
    if (outBoundaryCallback_ && outBoundaryCallback_() && scrollOverCallback_) {
        ProcessScrollOverCallback(correctVelocity);
    } else {
        double mainPosition = GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()));
        LOGD("[scrollMotion]position(%{public}lf), velocity(%{public}lf)", mainPosition, correctVelocity);
        if (motion_) {
            motion_->Reset(sFriction_, mainPosition, correctVelocity);
        } else {
            motion_ = AceType::MakeRefPtr<FrictionMotion>(sFriction_, mainPosition, correctVelocity);
            motion_->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
                auto scroll = weakScroll.Upgrade();
                if (scroll) {
                    scroll->ProcessScrollMotion(value);
                }
            });
        }

        // change motion param when list item need to be center of screen on watch
        FixScrollMotion(mainPosition);

        // Resets values.
        currentPos_ = mainPosition;
        currentVelocity_ = 0.0;

        // Starts motion.
        controller_->ClearStopListeners();
        controller_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto scroll = weak.Upgrade();
            if (scroll) {
                scroll->ProcessScrollMotionStop();
                // Send event to accessibility when scroll stop.
                auto context = scroll->GetContext().Upgrade();
                if (context && scroll->Idle()) {
                    AccessibilityEvent scrollEvent;
                    scrollEvent.nodeId = scroll->nodeId_;
                    scrollEvent.eventType = "scrollend";
                    context->SendEventToAccessibility(scrollEvent);
                }
            }
        });
        controller_->PlayMotion(motion_);
    }
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

void Scrollable::FixScrollMotion(double position)
{
#ifdef WEARABLE_PRODUCT
    if (motion_ && needCenterFix_ && watchFixCallback_) {
        double finalPoisition = watchFixCallback_(motion_->GetFinalPosition(), position);
        LOGD("final position before fix(%{public}lf), need to fix to position(%{public}lf)",
            motion_->GetFinalPosition(), finalPoisition);
        if (!NearEqual(finalPoisition, motion_->GetFinalPosition(), DISTANCE_EPSILON)) {
            double velocity = motion_->GetVelocityByFinalPosition(finalPoisition);
            motion_->Reset(sFriction_, position, velocity);

            // fix again when velocity is less than velocity threshold
            if (!NearEqual(finalPoisition, motion_->GetFinalPosition(), DISTANCE_EPSILON)) {
                velocity = motion_->GetVelocityByFinalPosition(finalPoisition, 0.0);
                motion_->Reset(sFriction_, position, velocity, 0.0);
            }
            LOGD("final position after fix (%{public}lf), ", motion_->GetFinalPosition());
        }
    }
#endif
};

void Scrollable::StartSpringMotion(
    double mainPosition, double mainVelocity, const ExtentPair& extent, const ExtentPair& initExtent)
{
    LOGD("[scroll] position(%{public}lf), mainVelocity(%{public}lf), minExtent(%{public}lf), maxExtent(%{public}lf), "
         "initMinExtent(%{public}lf), initMaxExtent(%{public}lf",
        mainPosition, mainVelocity, extent.Leading(), extent.Trailing(), initExtent.Leading(), initExtent.Trailing());
    scrollMotion_ = AceType::MakeRefPtr<ScrollMotion>(mainPosition, mainVelocity, extent, initExtent, spring_);
    if (!scrollMotion_->IsValid()) {
        LOGE("scrollMotion is invalid, no available spring motion.");
        return;
    }
    scrollMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double position) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->ProcessSpringMotion(position);
        }
    });
    currentPos_ = mainPosition;
    springController_->ClearStopListeners();
    springController_->PlayMotion(scrollMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto scroll = weak.Upgrade();
        if (scroll) {
            if (scroll->moved_ && scroll->scrollEndCallback_) {
                scroll->scrollEndCallback_();
            }
            scroll->currentVelocity_ = 0.0;
            if (scroll->isTouching_ || scroll->isDragUpdateStop_) {
                return;
            }
            scroll->moved_ = false;
#ifdef OHOS_PLATFORM
            LOGI("springController stop increase cpu frequency");
            ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
            if (FrameReport::GetInstance().GetEnable()) {
                FrameReport::GetInstance().EndListFling();
            }
#endif
            if (scroll->scrollEnd_) {
                scroll->scrollEnd_();
            }
            // Send event to accessibility when scroll stop.
            auto context = scroll->GetContext().Upgrade();
            if (context) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->nodeId_;
                scrollEvent.eventType = "scrollend";
                context->SendEventToAccessibility(scrollEvent);
            }
        }
    });
}

void Scrollable::ProcessScrollMotionStop()
{
    if (!scrollPause_ && moved_ && scrollEndCallback_) {
        scrollEndCallback_();
    }

    // spring effect special process
    if (scrollPause_ && scrollOverCallback_) {
        scrollPause_ = false;
        ProcessScrollOverCallback(currentVelocity_);
    } else {
        currentVelocity_ = 0.0;
        if (isDragUpdateStop_) {
            return;
        }
        moved_ = false;
#ifdef OHOS_PLATFORM
        LOGI("controller stop increase cpu frequency");
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndListFling();
        }
#endif
        if (scrollEnd_) {
            scrollEnd_();
        }
    }
}

void Scrollable::ProcessSpringMotion(double position)
{
    LOGD("[scroll] currentPos_(%{public}lf), position(%{public}lf)", currentPos_, position);
    currentVelocity_ = scrollMotion_->GetCurrentVelocity();
    if (NearEqual(currentPos_, position)) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION_SPRING);
    } else {
        if (!UpdateScrollPosition(position - currentPos_, SCROLL_FROM_ANIMATION_SPRING)) {
            springController_->Stop();
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
    currentVelocity_ = motion_->GetCurrentVelocity();
    LOGD("[scrolling] position(%{public}lf), currentVelocity_(%{public}lf)", position, currentVelocity_);
    if ((NearEqual(currentPos_, position))) {
        UpdateScrollPosition(0.0, SCROLL_FROM_ANIMATION);
    } else {
        // UpdateScrollPosition return false, means reach to scroll limit.
        auto mainDelta = position - currentPos_;
        ExecuteScrollBegin(mainDelta);
        if (!UpdateScrollPosition(mainDelta, SCROLL_FROM_ANIMATION)) {
            controller_->Stop();
        } else if (!touchUp_) {
            if (scrollTouchUpCallback_) {
                scrollTouchUpCallback_();
            }
            touchUp_ = true;
        }
    }
    currentPos_ = position;

    // spring effect special process
    if (outBoundaryCallback_ && outBoundaryCallback_()) {
        scrollPause_ = true;
        controller_->Stop();
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
    if (outBoundaryCallback_ && !outBoundaryCallback_()) {
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

void Scrollable::SetSlipFactor(double SlipFactor)
{
    slipFactor_ = std::clamp(SlipFactor, -ADJUSTABLE_VELOCITY, ADJUSTABLE_VELOCITY);
}

const RefPtr<SpringProperty>& Scrollable::GetDefaultOverSpringProperty()
{
    return DEFAULT_OVER_SPRING_PROPERTY;
}

} // namespace OHOS::Ace
