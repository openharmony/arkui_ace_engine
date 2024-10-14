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

#include "core/animation/scheduler.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

void Scheduler::Start()
{
    if (isRunning_) {
        LOGW("Already running, no need to start again.");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Start failed, context is null.");
        return;
    }
    isRunning_ = true;
    startupTimestamp_ = context->GetTimeFromExternalTimer();
    scheduleId_ = static_cast<int32_t>(context->AddScheduleTask(AceType::Claim(this)));

    displaySync_->RegisterOnFrameWithTimestamp([weak = WeakClaim(this)] (uint64_t nanoTimestamp) {
        auto scheduler = weak.Upgrade();
        CHECK_NULL_VOID(scheduler);
        scheduler->OnFrame(nanoTimestamp);
    });
    displaySync_->AddToPipeline(context_);
}

void Scheduler::Stop()
{
    if (!isRunning_) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Stop failed, context is null.");
        return;
    }
    isRunning_ = false;
    context->RemoveScheduleTask(scheduleId_);
    displaySync_->DelFromPipeline(context_);
    scheduleId_ = 0;
}

void Scheduler::SetExpectedFrameRateRange(const FrameRateRange& frameRateRange)
{
    displaySync_->SetExpectedFrameRateRange(frameRateRange);
}

void Scheduler::OnFrame(uint64_t nanoTimestamp)
{
    if (!isRunning_) {
        return;
    }

    // Refresh the startup time every frame.
    uint64_t elapsedTimeMs = 0;
    if (nanoTimestamp > startupTimestamp_) {
        static const uint64_t milliToNano = 1000000;
        elapsedTimeMs = (nanoTimestamp - startupTimestamp_) / milliToNano;
        startupTimestamp_ += elapsedTimeMs * milliToNano;
    }

    // Consume previous schedule as default.
    scheduleId_ = 0;
    if (callback_) {
        // Need to convert nanoseconds to milliseconds
        callback_(elapsedTimeMs);
    }

    // Schedule next frame task.
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Schedule next frame task failed, context is null.");
        return;
    }
    if (IsActive()) {
        scheduleId_ = static_cast<int32_t>(context->AddScheduleTask(AceType::Claim(this)));
    }
}

bool Scheduler::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()> propertyCallback, const std::function<void()>& finishCallBack)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("Failed to animate asynchronously, context is null!");
        return false;
    }

    return context->Animate(option, curve, propertyCallback, finishCallBack);
}

void Scheduler::OpenImplicitAnimation(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& finishCallBack)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("Failed to open implicit animation, context is null!");
        return;
    }

    return context->OpenImplicitAnimation(option, curve, finishCallBack);
}

bool Scheduler::CloseImplicitAnimation()
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("Failed to close implicit animation, context is null!");
        return false;
    }

    return context->CloseImplicitAnimation();
}

void Scheduler::AddKeyFrame(
    float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("Failed to add keyframe, context is null!");
        return;
    }

    return context->AddKeyFrame(fraction, curve, propertyCallback);
}

void Scheduler::AddKeyFrame(float fraction, const std::function<void()>& propertyCallback)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("Failed to add keyframe, context is null!");
        return;
    }

    return context->AddKeyFrame(fraction, propertyCallback);
}

bool Scheduler::PrintVsyncInfoIfNeed() const
{
    auto pipeline = context_.Upgrade();
    CHECK_NULL_RETURN(pipeline, false);
    if (pipeline->PrintVsyncInfoIfNeed()) {
        return true;
    }
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    const uint32_t delay = 3000; // unit: ms
    // check vsync info after delay time.
    taskExecutor->PostDelayedTask(
        [weakContext = context_]() {
            auto pipeline = weakContext.Upgrade();
            CHECK_NULL_VOID(pipeline);
            pipeline->PrintVsyncInfoIfNeed();
        },
        TaskExecutor::TaskType::UI, delay, "ArkUIAnimationPrintVsyncInfo");
    return false;
}

} // namespace OHOS::Ace
