/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/linear_indicator/linear_indicator_controller.h"

#include "core/components_ng/pattern/linear_indicator/linear_indicator_pattern.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

const float LinearIndicatorController::END_VALUE = 100.0f;
const std::string LinearIndicatorController::LINEAR_INDICATOR_ANIMATION_NAME = "linear_indicator_animation";
const std::string LinearIndicatorController::LINEAR_INDICATOR_INTERVAL_NAME = "linear_indicator_interval";
const int32_t LinearIndicatorController::ANIMATION_TIME_MIN = 1;

LinearIndicatorControllerData::LinearIndicatorControllerData()
    : progressAnimation_(nullptr), animationTag_(0), ProgressInterval_(),
      totalAnimationTime_(LinearIndicatorController::ANIMATION_TIME_MIN), totalIntervalTime_(0), isLoop_(true)
{
    InitData();
}

void LinearIndicatorControllerData::InitData()
{
    state_ = LinearIndicatorControllerDataState::STOP;
    index_ = 0;
    value_ = .0f;
    intervalConsumeTime_ = 0;
    intervalStart_ = std::chrono::system_clock::time_point();
}

int32_t LinearIndicatorController::GetProgressSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    return host->GetChildren().size();
}

RefPtr<FrameNode> LinearIndicatorController::GetProgressNode(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
}

void LinearIndicatorController::InitProgressValue()
{
    LOGI("LinearIndicator: Initialize all progress bars.");
    int32_t size = GetProgressSize();
    int32_t index = animationData_.Index();
    for (int32_t i = 0; i < size; ++i) {
        float value = .0f;
        if (i < index) {
            value = END_VALUE;
        } else if (i == index) {
            value = animationData_.Value();
        }
        SetProgressComponentValue(i, value);
    }
}

bool LinearIndicatorController::SetProgressComponentValue(int32_t index, float value)
{
    RefPtr<FrameNode> progressNode = GetProgressNode(index);
    CHECK_NULL_RETURN(progressNode, false);
    RefPtr<ProgressPaintProperty> paintProperty = progressNode->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    paintProperty->UpdateValue(value);
    progressNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void LinearIndicatorController::SetProgressValue(float value)
{
    if (!animationData_.IsRuning()) {
        return;
    }
    if (SetProgressComponentValue(animationData_.Index(), value)) {
        animationData_.SetValue(value);
        if (changeCallback_) {
            changeCallback_(animationData_.Index(), value);
        }
        return;
    }
    LOGE("LinearIndicator: Failed to set progress.");
    StopAnimation(LinearIndicatorControllerDataState::ANIMATION_PAUSE);
    animationData_.SetIndexAndValue(0, .0f);
    StartProgressAnimation();
}

void LinearIndicatorController::ProgreAnimationStart()
{
    LOGI("LinearIndicator: Callback for the start of the animation.");
    if (animationData_.Index() == 0) {
        InitProgressValue();
    }
}

void LinearIndicatorController::StartProgressInterval(int32_t intervalTime)
{
    LOGI("LinearIndicator: Start the interval task.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    animationData_.ProgressInterval().Cancel();
    auto weak = AceType::WeakClaim(this);
    animationData_.ProgressInterval().Reset([weak] {
        auto control = weak.Upgrade();
        CHECK_NULL_VOID(control);
        LOGI("LinearIndicator: Interval task execution completed.");
        control->StartProgressAnimation();
    });
    taskExecutor->PostDelayedTask(
        animationData_.ProgressInterval(), TaskExecutor::TaskType::UI, intervalTime, LINEAR_INDICATOR_INTERVAL_NAME);
    animationData_.SetState(LinearIndicatorControllerDataState::INTERVAL);
    animationData_.UpdateIntervalStart(animationData_.TotalIntervalTime() - intervalTime);
}

void LinearIndicatorController::ProgreAnimationEnd()
{
    if (animationData_.IsPause()) {
        return;
    }
    animationData_.ProgressAnimationAndClear();
    if (!animationData_.IsRuning()) {
        return;
    }
    LOGI("LinearIndicator: Callback at the end of the animation.");
    int32_t index = animationData_.UpdateIndex();
    int32_t progressSize = GetProgressSize();
    if (progressSize == 0) {
        animationData_.SetIndex(0);
        animationData_.SetState(LinearIndicatorControllerDataState::STOP);
        return;
    }
    if (index >= progressSize) {
        animationData_.SetIndex(0);
        if (!animationData_.IsLoop()) {
            animationData_.SetState(LinearIndicatorControllerDataState::STOP);
            return;
        }
    }
    StartProgressInterval(animationData_.TotalIntervalTime());
}

void LinearIndicatorController::StartProgressAnimation()
{
    if (animationData_.IsProgressAnimation()) {
        return;
    }
    LOGI("LinearIndicator: Start an animation session.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto weak = AceType::WeakClaim(this);
    host->CreateAnimatablePropertyFloat(LINEAR_INDICATOR_ANIMATION_NAME, 0, [weak](float value) {
        auto control = weak.Upgrade();
        CHECK_NULL_VOID(control);
        control->SetProgressValue(value);
    });

    host->UpdateAnimatablePropertyFloat(LINEAR_INDICATOR_ANIMATION_NAME, animationData_.Value());

    float end = END_VALUE;
    int32_t animationTime = animationData_.TotalAnimationTime() * (end - animationData_.Value()) / end;
    AnimationOption option;
    option.SetDuration(animationTime);
    option.SetCurve(Curves::LINEAR);

    int32_t animationTag = animationData_.UpdateAnimationTag();
    animationData_.SetProgressAnimation(AnimationUtils::StartAnimation(
        option,
        [weak]() {
            auto control = weak.Upgrade();
            CHECK_NULL_VOID(control);
            auto host = control->GetHost();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(LINEAR_INDICATOR_ANIMATION_NAME, END_VALUE);
            control->ProgreAnimationStart();
        },
        [weak, animationTag]() {
            auto control = weak.Upgrade();
            CHECK_NULL_VOID(control);
            if (control->animationData_.AnimationTag() != animationTag) {
                return;
            }
            control->ProgreAnimationEnd();
        }));
    animationData_.SetState(LinearIndicatorControllerDataState::ANIMATION);
}

void LinearIndicatorController::PlayingUpdateTime(int32_t animationTime, int32_t intervalTime)
{
    if (!animationData_.IsRuning()) {
        return;
    }
    if (animationData_.IsTimeEqually(animationTime, intervalTime)) {
        return;
    }
    if (animationData_.State() == LinearIndicatorControllerDataState::INTERVAL) {
        if (animationData_.IsIntervalTimeEqually(intervalTime)) {
            animationData_.SetTotalAnimationTime(animationTime);
        } else {
            animationData_.ProgressInterval().Cancel();
            animationData_.SetTime(animationTime, intervalTime);
            int32_t consumeTime = animationData_.IntervalCurrentConsumeTime();
            if (consumeTime >= intervalTime) {
                StartProgressAnimation();
            } else {
                StartProgressInterval(intervalTime - consumeTime);
            }
        }
    } else {
        if (animationData_.IsAnimationTimeEqually(animationTime)) {
            animationData_.SetTotalIntervalTime(intervalTime);
        } else {
            StopAnimation(LinearIndicatorControllerDataState::ANIMATION_PAUSE);
            animationData_.SetValue(RecalcProgressValue(animationTime));
            animationData_.SetTime(animationTime, intervalTime);
            StartProgressAnimation();
        }
    }
}

void LinearIndicatorController::Start(int32_t animationTime, int32_t intervalTime)
{
    if (animationTime < ANIMATION_TIME_MIN) {
        animationTime = ANIMATION_TIME_MIN;
    }
    if (intervalTime < 0) {
        intervalTime = 0;
    }
    if (animationData_.IsRuning()) {
        LOGI("LinearIndicator: Update the time of the running animation.");
        PlayingUpdateTime(animationTime, intervalTime);
    } else if (animationData_.IsPause()) {
        LOGI("LinearIndicator: Pause state starts the animation.");
        if (animationData_.State() == LinearIndicatorControllerDataState::INTERVAL_PAUSE) {
            animationData_.SetTime(animationTime, intervalTime);
            int32_t consumeTime = animationData_.IntervalConsumeTime();
            if (consumeTime >= intervalTime) {
                LOGI("LinearIndicator: Interval task execution completes, starts progress bar animation.");
                StartProgressAnimation();
            } else {
                StartProgressInterval(intervalTime - consumeTime);
            }
        } else {
            animationData_.SetValue(RecalcProgressValue(animationTime));
            animationData_.SetTime(animationTime, intervalTime);
            StartProgressAnimation();
        }
    } else {
        LOGI("LinearIndicator: Start animation.");
        animationData_.SetTime(animationTime, intervalTime);
        StartProgressAnimation();
    }
}

void LinearIndicatorController::Pause()
{
    if (!animationData_.IsRuning()) {
        return;
    }
    LOGI("LinearIndicator: Pause the animation.");
    if (animationData_.State() == LinearIndicatorControllerDataState::INTERVAL) {
        animationData_.SetState(LinearIndicatorControllerDataState::INTERVAL_PAUSE);
        animationData_.ProgressInterval().Cancel();
        return;
    }
    StopAnimation(LinearIndicatorControllerDataState::ANIMATION_PAUSE);
}

void LinearIndicatorController::Stop()
{
    LOGI("LinearIndicator: Stop the animation.");
    if (animationData_.IsRuning()) {
        if (animationData_.State() == LinearIndicatorControllerDataState::INTERVAL) {
            animationData_.ProgressInterval().Cancel();
        } else {
            StopAnimation(LinearIndicatorControllerDataState::STOP);
        }
    }
    if ((animationData_.Index() != 0) || (!NearZero(animationData_.Value()))) {
        if (changeCallback_) {
            changeCallback_(0, .0f);
        }
    }
    animationData_.InitData();
    InitProgressValue();
}

void LinearIndicatorController::SetProgress(int32_t index, float value)
{
    if (animationData_.Index() == index && animationData_.Value() == value) {
        return;
    }
    int32_t progressSize = GetProgressSize();
    if (progressSize == 0) {
        animationData_.InitData();
        LOGE("LinearIndicator: The number of progress bars is 0.");
        return;
    }
    if (index < 0 || index >= progressSize) {
        LOGE("LinearIndicator: The index value is incorrect.");
        return;
    }
    if (value < 0 || value > END_VALUE) {
        LOGE("LinearIndicator: The progress value is incorrect.");
        return;
    }
    if (changeCallback_) {
        changeCallback_(index, value);
    }
    bool isRuning = animationData_.IsRuning();
    bool isPause = animationData_.IsPause();
    if (isRuning) {
        LOGI("LinearIndicator: Animation to cancel.");
        if (animationData_.State() == LinearIndicatorControllerDataState::INTERVAL) {
            animationData_.ProgressInterval().Cancel();
        } else {
            StopAnimation(LinearIndicatorControllerDataState::ANIMATION_PAUSE);
        }
    }
    animationData_.SetIndexAndValue(index, value);
    InitProgressValue();
    if (isRuning) {
        LOGI("LinearIndicator: Restart the animation.");
        StartProgressAnimation();
    } else if (isPause) {
        animationData_.SetState(LinearIndicatorControllerDataState::ANIMATION_PAUSE);
    }
}

RefPtr<FrameNode> LinearIndicatorController::GetHost() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

void LinearIndicatorController::StopAnimation(LinearIndicatorControllerDataState state)
{
    animationData_.SetState(state);
    AnimationUtils::StopAnimation(animationData_.ProgressAnimationAndClear());
}

void LinearIndicatorController::UpdateProgressSize(int32_t size)
{
    if (animationData_.Index() >= size) {
        SetProgress(size - 1, END_VALUE);
    }
}

float LinearIndicatorController::RecalcProgressValue(int32_t newAnimationTime)
{
    if (newAnimationTime == 0) {
        return END_VALUE;
    }
    int32_t oldAnimationTime = animationData_.TotalAnimationTime();
    float oldValue = animationData_.Value();
    return std::clamp(oldAnimationTime * oldValue / newAnimationTime, .0f, END_VALUE);
}

} // namespace OHOS::Ace::NG
