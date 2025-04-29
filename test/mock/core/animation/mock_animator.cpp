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

#include "core/animation/animator.h"

namespace OHOS::Ace {
float Animator::scale_ = 1.0f;
float MAX_TIME = 1000000000.0f;

void Animator::SetDurationScale(float scale)
{
    scale_ = scale;
}

float Animator::GetAnimationScale() const
{
    return scale_;
}

// Public Functions.
Animator::Animator(const char* name)
{
    controllerId_ = 0;
}

Animator::Animator(const WeakPtr<PipelineBase>& context, const char* name)
{
    controllerId_ = 0;
}

Animator::~Animator() {}

void Animator::AttachScheduler(const WeakPtr<PipelineBase>& context)
{
    auto&& callback = [weak = AceType::WeakClaim(this)](uint64_t duration) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->OnFrame(duration);
    };
    scheduler_ = SchedulerBuilder::Build(callback, context);
}

bool Animator::HasScheduler() const
{
    return scheduler_ != nullptr;
}

bool Animator::SetExpectedFrameRateRange(const FrameRateRange& frameRateRange)
{
    if (HasScheduler() && frameRateRange.IsValid()) {
        return true;
    }

    return false;
}

void Animator::AddInterpolator(const RefPtr<Interpolator>& animation)
{
    if (animation) {
        interpolators_.emplace_back(animation);
    }
}

void Animator::RemoveInterpolator(const RefPtr<Interpolator>& animation)
{
    interpolators_.remove(animation);
}

void Animator::ClearInterpolators()
{
    interpolators_.clear();
}

void Animator::AddProxyController(const RefPtr<Animator>& proxy) {}

void Animator::RemoveProxyController(const RefPtr<Animator>& proxy) {}

void Animator::ClearProxyControllers() {}

Animator::Status Animator::GetStatus() const
{
    return status_;
}

bool Animator::IsStopped() const
{
    return status_ == Status::STOPPED;
}

bool Animator::IsRunning() const
{
    return status_ == Status::RUNNING;
}

// When the animation is in the delayed start phase.
bool Animator::IsPending() const
{
    return false;
}

int32_t Animator::GetDuration() const
{
    return duration_;
}

void Animator::SetDuration(int32_t duration)
{
    duration_ = duration;
}

bool Animator::SetIteration(int32_t iteration)
{
    return true;
}

void Animator::SetStartDelay(int32_t startDelay)
{
    startDelay_ = startDelay;
}

void Animator::SetFillMode(FillMode fillMode)
{
    fillMode_ = fillMode;
}

void Animator::SetTempo(float tempo)
{
    scaledStartDelay_ = 0;
    scaledDuration_ = 0;
    tempo_ = tempo;
}

void Animator::ApplyOption(const AnimationOption& option) {}

void Animator::SetAnimationDirection(AnimationDirection direction)
{
    direction_ = direction;
}

void Animator::SetAllowRunningAsynchronously(bool runAsync)
{
    allowRunningAsynchronously_ = runAsync;
}

bool Animator::GetAllowRunningAsynchronously()
{
    return allowRunningAsynchronously_;
}

// return true, the animation is played backward
// return false, the animation is played forward
bool Animator::GetInitAnimationDirection()
{
    return false;
}

void Animator::UpdatePlayedTime(int32_t playedTime, bool checkReverse)
{
    isCurDirection_ = false;
}

int64_t Animator::GetPlayedTime() const
{
    return elapsedTime_;
}

void Animator::TriggerFrame(int32_t playedTime, bool checkReverse) {}

void Animator::PlayMotion(const RefPtr<Motion>& motion)
{
    isReverse_ = false;
    motion_ = motion;
    status_ = Status::RUNNING; // StartInner
    motion_->OnTimestampChanged(MAX_TIME, 0.0f, false);
}

void Animator::Play()
{
    status_ = Status::RUNNING;
}

void Animator::Reverse() {}

void Animator::Forward()
{
    Play();
}

void Animator::Backward() {}

void Animator::Pause() {}

void Animator::Resume()
{
    status_ = Status::RUNNING;
    isResume_ = true;
}

void Animator::Stop()
{
    status_ = Status::STOPPED;
    isBothBackwards = false;
    elapsedTime_ = 0;
    StatusListenable::NotifyStopListener();
}

void Animator::Finish()
{
    Stop();
}

void Animator::Cancel() {}

int32_t Animator::GetId() const
{
    return controllerId_;
}

// Private Functions.
void Animator::OnFrame(int64_t duration) {}

void Animator::NotifyInterpolator(int32_t playedTime) {}

void Animator::NotifyMotion(int32_t playedTime) {}

void Animator::StartInner(bool alwaysNotify)
{
    toggleDirectionPending_ = false;
}

AnimationOption Animator::GetAnimationOption()
{
    return AnimationOption();
}

bool Animator::IsSupportedRunningAsynchronously()
{
    return true;
}

bool Animator::StartAsync()
{
    return true;
}

bool Animator::StartInnerAsync()
{
    asyncRunningAnimationCount_ = 0;
    return true;
}

void Animator::StopInnerAsync() {}

int32_t Animator::GetPlayedLoopsAndRemaining(int32_t& playedTime)
{
    return 0;
}

bool Animator::UpdateRepeatTimesLeftAndCheckFinished(int32_t playedLoops)
{
    return false;
}

void Animator::ToggleDirection() {}

float Animator::GetNormalizedTime(float playedTime, bool needStop) const
{
    return 0.0f;
}

void Animator::UpdateScaledTime() {}

void Animator::UpdateIteration(int32_t iteration)
{
    iteration_ = iteration;
    repeatTimes_ = iteration - 1;
    repeatTimesLeft_ = repeatTimes_;
}

void Animator::Copy(const RefPtr<Animator>& controller) {}

FillMode Animator::GetFillMode() const
{
    return fillMode_;
}

int32_t Animator::GetIteration() const
{
    return iteration_;
}

bool Animator::PrintVsyncInfoIfNeed() const
{
    return false;
}
} // namespace OHOS::Ace
