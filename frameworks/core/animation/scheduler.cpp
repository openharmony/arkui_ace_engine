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

#include "base/log/log.h"

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
    scheduleId_ = context->AddScheduleTask(AceType::Claim(this));
}

void Scheduler::Stop()
{
    if (!isRunning_) {
        LOGD("Already stopped, no need to stop again.");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Stop failed, context is null.");
        return;
    }
    isRunning_ = false;
    context->RemoveScheduleTask(scheduleId_);
    scheduleId_ = 0;
}

void Scheduler::OnFrame(uint64_t nanoTimestamp)
{
    if (!isRunning_) {
        LOGD("Already stopped, no need to send frame event.");
        return;
    }

    // Refresh the startup time every frame.
    uint64_t elapsedTime = nanoTimestamp - startupTimestamp_;
    startupTimestamp_ = nanoTimestamp;

    // Consume previous schedule as default.
    scheduleId_ = 0;
    if (callback_) {
        // Need to convert nanoseconds to milliseconds
        callback_(elapsedTime / 1000000);
    }

    // Schedule next frame task.
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Schedule next frame task failed, context is null.");
        return;
    }
    if (IsActive()) {
        scheduleId_ = context->AddScheduleTask(AceType::Claim(this));
    }
}

} // namespace OHOS::Ace
