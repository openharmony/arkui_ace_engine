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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SCHEDULER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SCHEDULER_H

#include <functional>

#include "core/animation/schedule_task.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class Scheduler : public ScheduleTask {
    DECLARE_ACE_TYPE(Scheduler, ScheduleTask);

public:
    using OnFrameCallback = std::function<void(uint64_t)>;

    Scheduler(OnFrameCallback&& callback, const WeakPtr<PipelineContext>& context)
        : callback_(std::move(callback)), context_(context)
    {}

    Scheduler() = delete;

    ~Scheduler() override
    {
        if (IsActive()) {
            Stop();
        }
    }

    void OnFrame(uint64_t nanoTimestamp) override;

    void Start();

    void Stop();

    bool IsActive() const
    {
        return isRunning_;
    }

private:
    int32_t scheduleId_ = 0;
    bool isRunning_ = false;
    uint64_t startupTimestamp_ = 0;
    OnFrameCallback callback_ = nullptr;
    WeakPtr<PipelineContext> context_;
};

class SchedulerBuilder {
public:
    static RefPtr<Scheduler> Build(Scheduler::OnFrameCallback&& callback, const WeakPtr<PipelineContext>& context)
    {
        return AceType::MakeRefPtr<Scheduler>(std::move(callback), context);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_SCHEDULER_H
