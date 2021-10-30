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
#include <pthread.h>
#include <unistd.h>

#ifdef ACE_DEBUG
#include <sys/prctl.h>
#endif

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

#ifdef ACE_DEBUG
    FillTaskTypeTable(TaskType::PLATFORM);
#endif
}

void FlutterTaskExecutor::InitJsThread(bool newThread)
{
    if (newThread) {
        jsThread_ = std::make_unique<fml::Thread>(GenJsThreadName());
        jsRunner_ = jsThread_->GetTaskRunner();
    } else {
        jsRunner_ = uiRunner_;
    }

#ifdef ACE_DEBUG
    PostTaskToTaskRunner(
        jsRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::JS); }, 0);
#endif
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

#ifdef ACE_DEBUG
    PostTaskToTaskRunner(
        uiRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::UI); }, 0);
    PostTaskToTaskRunner(
        ioRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::IO); }, 0);
    PostTaskToTaskRunner(
        gpuRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::GPU); }, 0);
#endif
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

#ifdef ACE_DEBUG
static const char* TaskTypeToString(TaskExecutor::TaskType type)
{
    switch (type) {
        case TaskExecutor::TaskType::PLATFORM:
            return "PLATFORM";
        case TaskExecutor::TaskType::UI:
            return "UI";
        case TaskExecutor::TaskType::IO:
            return "IO";
        case TaskExecutor::TaskType::GPU:
            return "GPU";
        case TaskExecutor::TaskType::JS:
            return "JS";
        case TaskExecutor::TaskType::BACKGROUND:
            return "BACKGROUND";
        case TaskExecutor::TaskType::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

thread_local TaskExecutor::TaskType FlutterTaskExecutor::localTaskType = TaskExecutor::TaskType::UNKNOWN;

bool FlutterTaskExecutor::OnPreSyncTask(TaskType type) const
{
    std::lock_guard<std::mutex> lock(tableMutex_);
    auto it = taskTypeTable_.find(type);
    // when task type not filled, just skip
    if (it == taskTypeTable_.end()) {
        return true;
    }

    auto itSync = syncTaskTable_.find(it->second.threadId);
    while (itSync != syncTaskTable_.end()) {
        if (itSync->second == std::this_thread::get_id()) {
            DumpDeadSyncTask(localTaskType, type);
            ACE_DCHECK(itSync->second != std::this_thread::get_id() && "DEAD LOCK HAPPENED !!!");
            return false;
        }

        itSync = syncTaskTable_.find(itSync->second);
    }

    syncTaskTable_.emplace(std::this_thread::get_id(), it->second.threadId);
    return true;
}

void FlutterTaskExecutor::OnPostSyncTask() const
{
    std::lock_guard<std::mutex> lock(tableMutex_);
    syncTaskTable_.erase(std::this_thread::get_id());
}

void FlutterTaskExecutor::DumpDeadSyncTask(TaskType from, TaskType to) const
{
    auto itFrom = taskTypeTable_.find(from);
    auto itTo = taskTypeTable_.find(to);

    ACE_DCHECK(itFrom != taskTypeTable_.end());
    ACE_DCHECK(itTo != taskTypeTable_.end());

    LOGE("DEAD LOCK HAPPEN: %{public}s(%{public}d, %{public}s) -> %{public}s(%{public}d, %{public}s)",
        TaskTypeToString(from), itFrom->second.tid, itFrom->second.threadName.c_str(),
        TaskTypeToString(to), itTo->second.tid, itTo->second.threadName.c_str());
}

void FlutterTaskExecutor::FillTaskTypeTable(TaskType type)
{
    constexpr size_t MAX_THREAD_NAME_SIZE = 32;
    char threadNameBuf[MAX_THREAD_NAME_SIZE] = {0};
    const char *threadName = threadNameBuf;
    if (prctl(PR_GET_NAME, threadNameBuf) < 0) {
        threadName = "unknown";
    }
    localTaskType = type;
    ThreadInfo info = {
        .threadId = std::this_thread::get_id(),
        .tid = gettid(),
        .threadName = threadName,
    };

    std::lock_guard<std::mutex> lock(tableMutex_);
    taskTypeTable_.emplace(type, info);
}

void FlutterTaskExecutor::FillTaskTypeTable(const WeakPtr<FlutterTaskExecutor>& weak, TaskType type)
{
    auto taskExecutor = weak.Upgrade();
    if (taskExecutor) {
        taskExecutor->FillTaskTypeTable(type);
    }
}
#endif

} // namespace OHOS::Ace
