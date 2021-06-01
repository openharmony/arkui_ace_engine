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

#include "adapter/common/cpp/flutter_task_executor.h"

#include <cerrno>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef FML_EMBEDDER_ONLY
#undef FML_EMBEDDER_ONLY
#define FML_EMBEDDER_ONLY
#endif
#include "flutter/fml/message_loop.h"
#include "flutter/shell/platform/ohos/platform_task_runner_adapter.h"

#include "base/log/log.h"
#include "base/thread/background_task_executor.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t GPU_THREAD_PRIORITY = -10;
constexpr int32_t UI_THREAD_PRIORITY = -8;

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

void SetThreadPriority(int32_t priority)
{
    if (setpriority(PRIO_PROCESS, gettid(), priority) < 0) {
        LOGW("Failed to set thread priority, errno = %{private}d", errno);
    }
}

} // namespace

FlutterTaskExecutor::~FlutterTaskExecutor()
{
    // To guarantee the jsThread released in platform thread
    auto rawPtr = jsThread_.release();
    PostTaskToTaskRunner(
        platformRunner_, [rawPtr] { std::unique_ptr<fml::Thread> jsThread(rawPtr); }, 0);
}

void FlutterTaskExecutor::InitPlatformThread()
{
    platformRunner_ = flutter::PlatformTaskRunnerAdapter::CurrentTaskRunner();
}

void FlutterTaskExecutor::InitJsThread(bool newThread)
{
    if (newThread) {
        jsThread_ = std::make_unique<fml::Thread>(GenJsThreadName());
        jsRunner_ = jsThread_->GetTaskRunner();
    } else {
        jsRunner_ = uiRunner_;
    }
}

void FlutterTaskExecutor::InitOtherThreads(const flutter::TaskRunners& taskRunners)
{
    uiRunner_ = taskRunners.GetUITaskRunner();
    ioRunner_ = taskRunners.GetIOTaskRunner();
    gpuRunner_ = taskRunners.GetGPUTaskRunner();

    PostTaskToTaskRunner(
        uiRunner_, [] { SetThreadPriority(UI_THREAD_PRIORITY); }, 0);
    PostTaskToTaskRunner(
        gpuRunner_, [] { SetThreadPriority(GPU_THREAD_PRIORITY); }, 0);
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

void FlutterTaskExecutor::AddTaskObserver(Task&& callback)
{
    fml::MessageLoop::GetCurrent().AddTaskObserver(reinterpret_cast<intptr_t>(this), std::move(callback));
}

void FlutterTaskExecutor::RemoveTaskObserver()
{
    fml::MessageLoop::GetCurrent().RemoveTaskObserver(reinterpret_cast<intptr_t>(this));
}

} // namespace OHOS::Ace
