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

#include "adapter/preview/entrance/flutter_task_executor.h"

#include "base/log/log.h"
#include "base/thread/background_task_executor.h"

namespace OHOS::Ace {
namespace {

inline std::string GenJsThreadName()
{
    static std::atomic<uint32_t> instanceCount { 1 };
    return std::string("jsThread-") + std::to_string(instanceCount.fetch_add(1, std::memory_order_relaxed));
}

bool PostTaskToTaskRunner(const fml::RefPtr<fml::TaskRunner>& taskRunner, TaskExecutor::Task&& task, uint32_t delayTime)
{
    if (!taskRunner || !task) {
        return false;
    }

    if (delayTime > 0) {
        taskRunner->PostDelayedTask(std::move(task), fml::TimeDelta::FromMilliseconds(delayTime));
    } else {
        taskRunner->PostTask(std::move(task));
    }
    return true;
}

} // namespace

FlutterTaskExecutor::FlutterTaskExecutor(const flutter::TaskRunners& taskRunners)
{
    jsThread_ = std::make_unique<fml::Thread>(GenJsThreadName());
    jsRunner_ = jsThread_->GetTaskRunner();

    platformRunner_ = taskRunners.GetPlatformTaskRunner();
    uiRunner_ = taskRunners.GetUITaskRunner();
    ioRunner_ = taskRunners.GetIOTaskRunner();
    gpuRunner_ = taskRunners.GetGPUTaskRunner();
}

bool FlutterTaskExecutor::OnPostTask(Task&& task, TaskType type, uint32_t delayTime) const
{
    switch (type) {
        case TaskType::PLATFORM:
            return PostTaskToTaskRunner(platformRunner_, std::move(task), delayTime);
        case TaskType::UI:
            return PostTaskToTaskRunner(uiRunner_, std::move(task), delayTime);
        case TaskType::IO:
            return PostTaskToTaskRunner(ioRunner_, std::move(task), delayTime);
        case TaskType::GPU:
            return PostTaskToTaskRunner(gpuRunner_, std::move(task), delayTime);
        case TaskType::JS:
            return PostTaskToTaskRunner(jsRunner_, std::move(task), delayTime);
        case TaskType::BACKGROUND:
            // Ignore delay time
            return BackgroundTaskExecutor::GetInstance().PostTask(std::move(task));
        default:
            return false;
    }
}

bool FlutterTaskExecutor::WillRunOnCurrentThread(TaskType type) const
{
    switch (type) {
        case TaskType::PLATFORM:
            return platformRunner_ ? platformRunner_->RunsTasksOnCurrentThread() : false;
        case TaskType::UI:
            return uiRunner_ ? uiRunner_->RunsTasksOnCurrentThread() : false;
        case TaskType::IO:
            return ioRunner_ ? ioRunner_->RunsTasksOnCurrentThread() : false;
        case TaskType::GPU:
            return gpuRunner_ ? gpuRunner_->RunsTasksOnCurrentThread() : false;
        case TaskType::JS:
            return jsRunner_ ? jsRunner_->RunsTasksOnCurrentThread() : false;
        case TaskType::BACKGROUND:
            // Always return false for background tasks.
            return false;
        default:
            return false;
    }
}

void FlutterTaskExecutor::DestroyJsThread()
{
    jsThread_.reset();
}

} // namespace OHOS::Ace
