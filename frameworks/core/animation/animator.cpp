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

#include "base/log/jank_frame_report.h"
#include "core/common/container.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr float MAX_TIME = 1000000000.0f;

int32_t g_controllerId = 0;
int32_t AllocControllerId()
{
    return ++g_controllerId;
}

} // namespace

// Static Functions.
float Animator::scale_ = 1.0f;

void Animator::SetDurationScale(float scale)
{
    if (scale < 0.0f) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "Invalid scale value: %{public}f, keep same", scale);
        return;
    }
    scale_ = scale;
}

float Animator::GetAnimationScale() const
{
#ifdef OHOS_STANDARD_SYSTEM
    // if rosen is enabled, animationScale should be set on Rosen.
    return allowRunningAsynchronously_ ? 1.0 : SystemProperties::GetAnimationScale();
#else
    return scale_;
#endif
}

// Public Functions.
Animator::Animator(const char* name)
{
    controllerId_ = AllocControllerId();
    if (name != nullptr) {
        animatorName_ = name;
    }
}

Animator::Animator(const WeakPtr<PipelineBase>& context, const char* name)
{
    controllerId_ = AllocControllerId();
    AttachScheduler(context);
    if (name != nullptr) {
        animatorName_ = name;
    }
}

Animator::~Animator()
{
    CHECK_RUN_ON(UI);
    // Clear all listeners first to make its destruction silently.
    ClearAllListeners();
    ClearInterpolators();
    if (!IsStopped()) {
        Stop();
    }
}

void Animator::AttachScheduler(const WeakPtr<PipelineBase>& context)
{
    auto&& callback = [weak = AceType::WeakClaim(this)](uint64_t duration) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->OnFrame(duration);
    };
    scheduler_ = SchedulerBuilder::Build(callback, context);
}

bool Animator::AttachSchedulerOnContainer()
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    if (!Container::CheckRunOnThreadByThreadId(currentId, false)) {
        auto localContainerId = ContainerScope::CurrentLocalId();
        if (localContainerId > 0 && Container::CheckRunOnThreadByThreadId(localContainerId, false)) {
            currentId = localContainerId;
        } else {
            return false;
        }
    }
    ContainerScope scope(currentId);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "animator binds to context %{public}d, id:%{public}d", pipeline->GetInstanceId(),
        GetId());
    AttachScheduler(pipeline);
    return true;
}

bool Animator::HasScheduler() const
{
    return scheduler_ != nullptr;
}

bool Animator::SetExpectedFrameRateRange(const FrameRateRange& frameRateRange)
{
    if (HasScheduler() && frameRateRange.IsValid()) {
        scheduler_->SetExpectedFrameRateRange(frameRateRange);
        return true;
    }

    return false;
}

void Animator::AddInterpolator(const RefPtr<Interpolator>& animation)
{
    CHECK_RUN_ON(UI);
    if (animation) {
        interpolators_.emplace_back(animation);
    }
}

void Animator::RemoveInterpolator(const RefPtr<Interpolator>& animation)
{
    CHECK_RUN_ON(UI);
    interpolators_.remove(animation);
}

void Animator::ClearInterpolators()
{
    CHECK_RUN_ON(UI);
    interpolators_.clear();
}

void Animator::AddProxyController(const RefPtr<Animator>& proxy)
{
    CHECK_RUN_ON(UI);
    if (!proxy) {
        return;
    }
    if (RawPtr(proxy) != this) {
        proxyControllers_.emplace_back(proxy);
        proxy->Copy(Claim(this));
        proxy->scheduler_.Reset();
    }
}

void Animator::RemoveProxyController(const RefPtr<Animator>& proxy)
{
    CHECK_RUN_ON(UI);
    proxyControllers_.remove(proxy);
}

void Animator::ClearProxyControllers()
{
    CHECK_RUN_ON(UI);
    proxyControllers_.clear();
}

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
    if ((status_ == Status::RUNNING) || (status_ == Status::PAUSED)) {
        return elapsedTime_ < startDelay_;
    } else {
        return false;
    }
}

int32_t Animator::GetDuration() const
{
    return duration_;
}

void Animator::SetDuration(int32_t duration)
{
    CHECK_RUN_ON(UI);
    if (duration < 0) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "invalid duration time, keep the old. id: %{public}d", controllerId_);
        return;
    }
    if ((status_ == Status::RUNNING || status_ == Status::PAUSED) && duration != 0) {
        // Need to update elapsedTime when animation running or paused.
        elapsedTime_ = (duration_ / duration) * elapsedTime_;
    }
    duration_ = duration;
    for (auto& controller : proxyControllers_) {
        controller->SetDuration(duration);
    }
}

bool Animator::SetIteration(int32_t iteration)
{
    CHECK_RUN_ON(UI);
    if (iteration_ == iteration) {
        return true;
    }
    if ((iteration < 0) && (iteration != ANIMATION_REPEAT_INFINITE)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "invalid iteration: %{public}d. id: %{public}d", iteration, controllerId_);
        return false;
    }
    // if status is not idle, finish current animation and init animation
    if (status_ != Status::IDLE) {
        Finish();
    }
    UpdateIteration(iteration);
    repeatTimesLeft_ = repeatTimes_;
    isOddRound_ = true;
    for (auto& controller : proxyControllers_) {
        controller->SetIteration(iteration);
    }
    return true;
}

int32_t Animator::GetIteration() const
{
    return iteration_;
}

void Animator::SetStartDelay(int32_t startDelay)
{
    CHECK_RUN_ON(UI);
    startDelay_ = startDelay;
    for (auto& controller : proxyControllers_) {
        controller->SetStartDelay(startDelay);
    }
}

void Animator::SetFillMode(FillMode fillMode)
{
    CHECK_RUN_ON(UI);
    fillMode_ = fillMode;
    for (auto& controller : proxyControllers_) {
        controller->SetFillMode(fillMode);
    }
}

FillMode Animator::GetFillMode() const
{
    return fillMode_;
}

void Animator::SetTempo(float tempo)
{
    CHECK_RUN_ON(UI);
    if (tempo < 0.0f) {
        return;
    }
    if (NearZero(tempo)) {
        scaledStartDelay_ = 0;
        scaledDuration_ = 0;
    }
    tempo_ = tempo;
}

void Animator::ApplyOption(const AnimationOption& option)
{
    SetDuration(option.GetDuration());
    SetStartDelay(option.GetDelay());
    SetIteration(option.GetIteration());
    SetTempo(option.GetTempo());
    SetAnimationDirection(option.GetAnimationDirection());
}

void Animator::SetAnimationDirection(AnimationDirection direction)
{
    CHECK_RUN_ON(UI);
    direction_ = direction;
    for (auto& controller : proxyControllers_) {
        controller->SetAnimationDirection(direction);
    }
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
    if (direction_ == AnimationDirection::NORMAL) {
        return isReverse_;
    }
    if (direction_ == AnimationDirection::REVERSE) {
        return !isReverse_;
    }
    // for Alternate and Alternate_Reverse
    bool oddRoundDirectionNormal = direction_ == AnimationDirection::ALTERNATE;
    if (isOddRound_ != oddRoundDirectionNormal) {
        // if isOddRound is different from oddRoundDirectionNormal, same with AnimationDirection::REVERSE
        return !isReverse_;
    }
    return isReverse_;
}

void Animator::UpdatePlayedTime(int32_t playedTime, bool checkReverse)
{
    if (playedTime < 0 || playedTime > duration_) {
        return;
    }
    if (startDelay_ != 0 || motion_) {
        // Unsupported UpdatePlayedTime when startDelay or motion
        return;
    }
    if (!checkReverse) {
        // only support go forward.
        isReverse_ = false;
        isCurDirection_ = false;
    }
    float scale = GetAnimationScale();
    if (!NearZero(tempo_)) {
        int32_t scaledPlayedTime = playedTime * scale / tempo_;
        elapsedTime_ = scaledPlayedTime;
    }
}

int64_t Animator::GetPlayedTime() const
{
    return elapsedTime_;
}

void Animator::TriggerFrame(int32_t playedTime, bool checkReverse)
{
    CHECK_RUN_ON(UI);
    if (playedTime < 0 || playedTime > duration_) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "TriggerFrame failed. Invalid playedTime:%{public}d, id:%{public}d",
            playedTime, controllerId_);
        return;
    }
    if (startDelay_ != 0 || motion_) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "Unsupported TriggerFrame when startDelay or motion, id:%{public}d",
            controllerId_);
        return;
    }
    UpdatePlayedTime(playedTime, checkReverse);
    UpdateScaledTime();
    NotifyPrepareListener();
    NotifyInterpolator(elapsedTime_);
}

void Animator::PlayMotion(const RefPtr<Motion>& motion)
{
    CHECK_RUN_ON(UI);
    if (!motion) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "PlayMotion failed, motion is null. id:%{public}d", controllerId_);
        return;
    }
    interpolators_.clear();
    isReverse_ = false;
    motion_ = motion;
    StartInner(false);
}

void Animator::Play()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    motion_ = nullptr;
    StartInner(false);
}

void Animator::Reverse()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    motion_ = nullptr;
    ToggleDirection();
    StartInner(true);
}

void Animator::Forward()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (isReverse_) {
        ToggleDirection();
    }
    Play();
}

void Animator::Backward()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (isReverse_) {
        ToggleDirection();
    }
    Reverse();
}

void Animator::Pause()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (status_ == Status::PAUSED) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "Already paused, do not need pause again. id: %{public}d", controllerId_);
        return;
    }
    if (status_ == Status::IDLE) {
        Play();
    }
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
    if (needFrameJankReport_) {
        JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_ANIMATOR);
    }
    status_ = Status::PAUSED;
    asyncTrace_ = nullptr;
    StatusListenable::NotifyPauseListener();
    for (auto& controller : proxyControllers_) {
        controller->Pause();
    }
}

void Animator::Resume()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (status_ == Status::RUNNING) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "Already running, do not need resume again. id: %{public}d", controllerId_);
        return;
    }
    if (scheduler_ && !scheduler_->IsActive()) {
        scheduler_->Start();
    }
    if (needFrameJankReport_) {
        JankFrameReport::GetInstance().SetFrameJankFlag(JANK_RUNNING_ANIMATOR);
    }
    status_ = Status::RUNNING;
    if (!motion_) {
        asyncTrace_ = std::make_shared<AceAsyncScopedTrace>(animatorName_.c_str());
    } else {
        if (motion_->GetMotionType() == "friction") {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>((animatorName_ + ": friction").c_str());
        } else if (motion_->GetMotionType() == "spring") {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>((animatorName_ + ": spring").c_str());
        } else {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>(animatorName_.c_str());
        }
    }
    isResume_ = true;
    StatusListenable::NotifyResumeListener();
    for (auto& controller : proxyControllers_) {
        controller->Resume();
    }
}

void Animator::Stop()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (status_ == Status::STOPPED) {
        return;
    }
    if (needFrameJankReport_) {
        JankFrameReport::GetInstance().ClearFrameJankFlag(JANK_RUNNING_ANIMATOR);
    }

    elapsedTime_ = 0;
    repeatTimesLeft_ = repeatTimes_;
    isOddRound_ = true;
    isBothBackwards = false;
    UpdateScaledTime();
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
    status_ = Status::STOPPED;
    asyncTrace_ = nullptr;
    if (animatorName_.find("ohos.animator") != std::string::npos) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "animator stop, id:%{public}d", GetId());
    }
    StatusListenable::NotifyStopListener();
    for (auto& controller : proxyControllers_) {
        controller->Stop();
    }
}

void Animator::Finish()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (status_ == Status::STOPPED) {
        return;
    }
    if (motion_) {
        // Notify motion with big time to let motion end in final state.
        motion_->OnTimestampChanged(MAX_TIME, 0.0f, false);
        Stop();
        return;
    }
    repeatTimesLeft_ = 0;
    UpdateScaledTime();
    OnFrame(((int64_t)scaledStartDelay_) + scaledDuration_);
}

void Animator::Cancel()
{
    CHECK_RUN_ON(UI);
    if (iteration_ == 0) {
        return;
    }
    if (status_ == Status::IDLE) {
        TAG_LOGD(AceLogTag::ACE_ANIMATION, "Already in idle, do not need cancel again. id: %{public}d", controllerId_);
        return;
    }
    status_ = Status::IDLE;
    elapsedTime_ = 0;
    repeatTimesLeft_ = repeatTimes_;
    isOddRound_ = true;
    UpdateScaledTime();
    NotifyPrepareListener();
    float normalizedTime = GetNormalizedTime(0.0f, true);
    auto interpolators = interpolators_;
    for (auto& interpolator : interpolators) {
        interpolator->OnInitNotify(normalizedTime, isReverse_);
    }
    if (motion_) {
        // Notify motion with big time to let motion end in final state.
        motion_->OnTimestampChanged(MAX_TIME, 0.0f, false);
    }
    if (scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
    asyncTrace_ = nullptr;
    NotifyIdleListener();
}

int32_t Animator::GetId() const
{
    return controllerId_;
}

// Private Functions.
void Animator::OnFrame(int64_t duration)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE_FLAG(iteration_ == ANIMATION_REPEAT_INFINITE, "onFrame %s, iteration -1, id %d",
        animatorName_.c_str(), controllerId_);
    // notify child first
    for (auto& controller : proxyControllers_) {
        controller->OnFrame(duration);
    }
    if (elapsedTime_ > 0 && duration > INT64_MAX - elapsedTime_) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "duration is too big, skip it. id:%{public}d", controllerId_);
        return;
    }
    elapsedTime_ += duration;
    UpdateScaledTime();
    // skip delay time
    if (elapsedTime_ < scaledStartDelay_) {
        if ((fillMode_ == FillMode::BACKWARDS || fillMode_ == FillMode::BOTH) && !isBothBackwards) {
            auto interpolators = interpolators_;
            for (const auto& interpolator : interpolators) {
                interpolator->OnNormalizedTimestampChanged(isCurDirection_ ? 1.0f : 0.0f, isReverse_);
            }
            isBothBackwards = true;
        }
        return;
    }
    JankFrameReport::GetInstance().RecordFrameUpdate();
    NotifyPrepareListener();
    // get playedTime
    auto playedTime = elapsedTime_ - scaledStartDelay_;
    // make playedTime in range 0 ~ INT32_MAX(max duration value)
    playedTime = std::clamp<int64_t>(playedTime, 0L, (int64_t)INT32_MAX);
    if (!motion_) {
        NotifyInterpolator(playedTime);
    } else {
        NotifyMotion(playedTime);
    }
}

void Animator::NotifyInterpolator(int32_t playedTime)
{
    CHECK_RUN_ON(UI);
    bool needStop = false;
    bool notifyRepeat = false;
    // do not notify user when handling playedTime, because users may be change duration or repeat times in callback.
    // if they change this parameter, it will take effect next tick.
    if (playedTime >= scaledDuration_) {
        notifyRepeat = true;
        auto isAlternateDirection =
            (direction_ == AnimationDirection::ALTERNATE) || (direction_ == AnimationDirection::ALTERNATE_REVERSE);
        if ((scaledDuration_ == 0) && isAlternateDirection && (iteration_ % 2 == 0)) {
            isCurDirection_ = !isCurDirection_;
        }
        // make playedTime in range 0 ~ INTERPOLATE_DURATION_MAX
        needStop = repeatTimesLeft_ == 0 || (scaledDuration_ == 0 && repeatTimesLeft_ != ANIMATION_REPEAT_INFINITE);
        if (needStop) {
            repeatTimesLeft_ = 0;
        } else {
            auto playedLoops = GetPlayedLoopsAndRemaining(playedTime);
            if (repeatTimesLeft_ != ANIMATION_REPEAT_INFINITE) {
                needStop = UpdateRepeatTimesLeftAndCheckFinished(playedLoops);
            }
            if (isAlternateDirection) {
                isCurDirection_ = !isCurDirection_;
            }
            // use 2 to check whether playedLoops is Odd.
            isOddRound_ = playedLoops % 2 == 0 ? isOddRound_ : !isOddRound_;
        }

        // after the above branches, playedTime in range 0 ~ INTERPOLATE_DURATION_MAX
        // make elapsedTime_ in range 0 ~ scaledStartDelay_ + INTERPOLATE_DURATION_MAX
        elapsedTime_ = playedTime + scaledStartDelay_;
    }

    float normalizedTime = GetNormalizedTime(playedTime, needStop);
    // all calculation above is done, we can notify user from now.
    // users can change controller's configuration, and it will take effect next tick.
    if (notifyRepeat && !needStop) {
        // notify repeat before on timestamp changed.
        StatusListenable::NotifyRepeatListener();
    }
    auto interpolators = interpolators_;
    for (const auto& interpolator : interpolators) {
        if (needStop && (fillMode_ == FillMode::NONE || fillMode_ == FillMode::BACKWARDS)) {
            // notify init value set by user.
            interpolator->OnInitNotify(normalizedTime, isReverse_);
        } else {
            // interpolate animation accept normalized time.
            interpolator->OnNormalizedTimestampChanged(normalizedTime, isReverse_);
        }
    }
    if (needStop && (!IsStopped())) {
        // notify stop after on timestamp changed.
        Stop();
    }
}

void Animator::NotifyMotion(int32_t playedTime)
{
    CHECK_RUN_ON(UI);
    // motion do not have normalized time, because no exact duration in motion.
    // just pass actual time to motion, normalized time always zero.
    motion_->OnTimestampChanged(playedTime, 0.0f, false);
    if (motion_->IsCompleted()) {
        Stop();
    }
}

void Animator::StartInner(bool alwaysNotify)
{
    CHECK_RUN_ON(UI);
    if (status_ == Status::RUNNING) {
        if (toggleDirectionPending_) {
            toggleDirectionPending_ = false;
            isCurDirection_ = !isCurDirection_;
        }

        if (alwaysNotify) {
            StatusListenable::NotifyStartListener();
            for (auto& controller : proxyControllers_) {
                controller->StartInner(alwaysNotify);
            }
        }
        return;
    }
    toggleDirectionPending_ = false;
    if (scheduler_ && !scheduler_->IsActive()) {
        if (!StartAsync()) {
            scheduler_->Start();
        }
    }
    StatusListenable::NotifyStartListener();
    if (needFrameJankReport_) {
        JankFrameReport::GetInstance().SetFrameJankFlag(JANK_RUNNING_ANIMATOR);
    }
    status_ = Status::RUNNING;
    if (!motion_) {
        asyncTrace_ = std::make_shared<AceAsyncScopedTrace>(animatorName_.c_str());
    } else {
        if (motion_->GetMotionType() == "friction") {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>((animatorName_ + ": friction").c_str());
        } else if (motion_->GetMotionType() == "spring") {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>((animatorName_ + ": spring").c_str());
        } else {
            asyncTrace_ = std::make_shared<AceAsyncScopedTrace>(animatorName_.c_str());
        }
    }
    isCurDirection_ = GetInitAnimationDirection();
    for (auto& controller : proxyControllers_) {
        controller->StartInner(alwaysNotify);
    }
}

AnimationOption Animator::GetAnimationOption()
{
    AnimationOption option;
    option.SetDuration(duration_ * GetAnimationScale());
    option.SetDelay(startDelay_ * GetAnimationScale());
    option.SetIteration(iteration_);
    option.SetTempo(tempo_);
    option.SetFillMode(fillMode_);

    AnimationDirection direction = direction_;
    if (GetInitAnimationDirection()) {
        switch (direction_) {
            case AnimationDirection::NORMAL:
                direction = AnimationDirection::REVERSE;
                break;
            case AnimationDirection::ALTERNATE:
                direction = AnimationDirection::ALTERNATE_REVERSE;
                break;
            case AnimationDirection::REVERSE:
                direction = AnimationDirection::NORMAL;
                break;
            case AnimationDirection::ALTERNATE_REVERSE:
                direction = AnimationDirection::ALTERNATE;
                break;
            default:
                direction = AnimationDirection::NORMAL;
                break;
        }
    }

    option.SetAnimationDirection(direction);
    return option;
}

bool Animator::IsSupportedRunningAsynchronously()
{
    for (const auto& animation : interpolators_) {
        if (!animation->IsSupportedRunningAsynchronously()) {
            return false;
        }
    }

    return true;
}

bool Animator::StartAsync()
{
    if (!SystemProperties::GetRosenBackendEnabled()) {
        return false;
    }

    if (!allowRunningAsynchronously_) {
        return false;
    }

    if (interpolators_.empty()) {
        return false;
    }

    if (!IsSupportedRunningAsynchronously()) {
        TAG_LOGW(
            AceLogTag::ACE_ANIMATION, "not support running asynchronously, controller id: %{public}d", controllerId_);
        return false;
    }
    if (scheduler_) {
        auto context = scheduler_->GetContext().Upgrade();
        if (context && !context->IsRebuildFinished()) {
            context->SetBuildAfterCallback([weak = AceType::WeakClaim(this)]() {
                auto controller = weak.Upgrade();
                if (controller != nullptr) {
                    controller->StartInnerAsync();
                }
            });
            return true;
        }
    }
    StartInnerAsync();
    return true;
}

bool Animator::StartInnerAsync()
{
    auto prepareCallback = [weak = AceType::WeakClaim(this)]() -> void {
        auto controller = weak.Upgrade();
        if (controller != nullptr) {
            controller->NotifyPrepareListener();
        }
    };

    auto stopCallback = [weak = AceType::WeakClaim(this), id = Container::CurrentIdSafely()]() -> void {
        ContainerScope scope(id);
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->StopInnerAsync();
    };

    auto animations = std::move(interpolators_);
    auto option = GetAnimationOption();
    asyncRunningAnimationCount_ = 0;
    for (const auto& animation : animations) {
        if (animation->RunAsync(scheduler_, option, prepareCallback, stopCallback)) {
            asyncRunningAnimationCount_++;
        }
    }
    return true;
}

void Animator::StopInnerAsync()
{
    if (--asyncRunningAnimationCount_ > 0) {
        return;
    }

    if (status_ != Status::STOPPED && (!HasScheduler() || !scheduler_->IsActive())) {
        Stop();
    }
}

int32_t Animator::GetPlayedLoopsAndRemaining(int32_t& playedTime)
{
    // when duration equals 0, played loop equals INT32_MAX, and playedTime remains unchanged.
    int32_t playedLoop = INT32_MAX;
    if (scaledDuration_ != 0) {
        // in order to make playedTime in range of 0 ~ INTERPOLATE_DURATION_MAX, calc elapsed loop between two vsyncs
        playedLoop = std::clamp(playedTime / scaledDuration_, 0, INT32_MAX);
        playedTime = playedTime % scaledDuration_;
    }
    return playedLoop;
}

bool Animator::UpdateRepeatTimesLeftAndCheckFinished(int32_t playedLoops)
{
    // get the remaining repeatTimesLeft_
    repeatTimesLeft_ -= playedLoops;
    if (playedLoops > 1) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION,
            "too long time between neighbor vsync, elapsed loop count: %{public}d. id: %{public}d", playedLoops,
            controllerId_);
    }
    if (repeatTimesLeft_ < 0) {
        return true;
    }
    return false;
}

void Animator::ToggleDirection()
{
    isReverse_ = !isReverse_;
    // if toggleDirectionPending_ is true, it will be cleared in StartInner
    toggleDirectionPending_ = !toggleDirectionPending_;
    if (status_ == Status::IDLE || status_ == Status::STOPPED) {
        return;
    }
    if (repeatTimes_ == ANIMATION_REPEAT_INFINITE) {
        elapsedTime_ = (scaledStartDelay_ + scaledDuration_ - elapsedTime_) + scaledStartDelay_;
        // duration is infinite, can not reverse time related params.
        return;
    }
    repeatTimesLeft_ = repeatTimes_ - repeatTimesLeft_;
    elapsedTime_ = (scaledStartDelay_ + scaledDuration_ - elapsedTime_) + scaledStartDelay_;
}

float Animator::GetNormalizedTime(float playedTime, bool needStop) const
{
    float normalizedTime = 0.0f;
    if (needStop) {
        switch (fillMode_) {
            case FillMode::FORWARDS:
                // Fall through.
            case FillMode::BOTH:
                normalizedTime = 1.0f;
                break;
            case FillMode::NONE:
                // Fall through.
            case FillMode::BACKWARDS:
                normalizedTime = 0.0f;
                break;
            default:
                normalizedTime = 1.0f;
                break;
        }
    } else {
        normalizedTime = scaledDuration_ == 0 ? 1.0f : (1.0f * playedTime) / scaledDuration_;
    }
    return isCurDirection_ ? 1.0f - normalizedTime : normalizedTime;
}

void Animator::UpdateScaledTime()
{
    float scale = GetAnimationScale();
    if (!NearZero(tempo_)) {
        scaledDuration_ = duration_ * scale / tempo_;
        scaledStartDelay_ = startDelay_ * scale / tempo_;
    }
}

void Animator::UpdateIteration(int32_t iteration)
{
    iteration_ = iteration;
    if (iteration <= 0 && iteration != ANIMATION_REPEAT_INFINITE) {
        repeatTimes_ = 0;
    } else if (iteration == ANIMATION_REPEAT_INFINITE) {
        repeatTimes_ = ANIMATION_REPEAT_INFINITE;
    } else {
        repeatTimes_ = iteration - 1;
    }
}

void Animator::Copy(const RefPtr<Animator>& controller)
{
    if (!controller) {
        return;
    }
    fillMode_ = controller->fillMode_;
    direction_ = controller->direction_;
    isCurDirection_ = controller->isCurDirection_;
    isOddRound_ = controller->isOddRound_;
    toggleDirectionPending_ = controller->toggleDirectionPending_;
    duration_ = controller->duration_;
    elapsedTime_ = controller->elapsedTime_;
    startDelay_ = controller->startDelay_;
    repeatTimes_ = controller->repeatTimes_;
    iteration_ = controller->iteration_;
    repeatTimesLeft_ = controller->repeatTimesLeft_;
    isReverse_ = controller->isReverse_;
    isResume_ = controller->isResume_;
    status_ = controller->status_;
    scaledDuration_ = controller->scaledDuration_;
    scaledStartDelay_ = controller->scaledStartDelay_;
}

void Animator::ResetIsReverse()
{
    isReverse_ = false;
}

bool Animator::PrintVsyncInfoIfNeed() const
{
    CHECK_NULL_RETURN(scheduler_, false);
    return scheduler_->PrintVsyncInfoIfNeed();
}

} // namespace OHOS::Ace
