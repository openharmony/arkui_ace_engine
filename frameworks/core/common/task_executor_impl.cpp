/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/task_executor_impl.h"

#include <cerrno>
#include <functional>
#if !defined(PREVIEW)
#ifdef OHOS_STANDARD_SYSTEM
#include <sys/prctl.h>
#endif
#include <sys/resource.h>
#endif
#include <sys/time.h>
#include <unistd.h>

#include "base/log/log.h"
#include "base/log/trace_id.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t GPU_THREAD_PRIORITY = -10;
constexpr int32_t UI_THREAD_PRIORITY = -15;

inline std::string GenJsThreadName()
{
    static std::atomic<uint32_t> instanceCount { 1 };
    return std::string("jsThread-") + std::to_string(instanceCount.fetch_add(1, std::memory_order_relaxed));
}
} // namespace

TaskExecutor::Task TaskExecutorImpl::WrapTaskWithContainer(
    TaskExecutor::Task&& task, int32_t id, std::function<void()>&& traceIdFunc) const
{
    auto wrappedTask = [originTask = std::move(task), id, traceId = TraceId::CreateTraceId(),
                           traceIdFunc = std::move(traceIdFunc)]() {
        ContainerScope scope(id);
        std::unique_ptr<TraceId> traceIdPtr(traceId);
        if (originTask && traceIdPtr) {
            traceIdPtr->SetTraceId();
            originTask();
            traceIdPtr->ClearTraceId();
        } else {
            LOGW("WrapTaskWithContainer: originTask or traceIdPtr is null.");
        }
        if (traceIdFunc) {
            traceIdFunc();
        }
    };
    return wrappedTask;
}

bool TaskExecutorImpl::PostTaskToTaskRunner(const RefPtr<TaskRunnerAdapter>& taskRunner, TaskExecutor::Task&& task,
    uint32_t delayTime, const std::string& callerInfo) const
{
    CHECK_NULL_RETURN(taskRunner, false);
    CHECK_NULL_RETURN(task, false);

    if (delayTime > 0) {
        taskRunner->PostDelayedTask(std::move(task), delayTime, callerInfo);
    } else {
        taskRunner->PostTask(std::move(task), callerInfo);
    }
    return true;
}

void TaskExecutorImpl::SetThreadPriority(int32_t priority) const
{
#if !defined(PREVIEW) and !defined(IOS_PLATFORM)
    if (setpriority(PRIO_PROCESS, gettid(), priority) < 0) {
        LOGW("Failed to set thread priority, errno = %{private}d", errno);
    }
#endif
}

TaskExecutorImpl::TaskExecutorImpl(const RefPtr<TaskExecutorImpl>& taskExecutor)
{
    jsRunner_ = TaskRunnerAdapterFactory::Create(false, GenJsThreadName());
    platformRunner_ = taskExecutor->platformRunner_;
    uiRunner_ = taskExecutor->uiRunner_;
    ioRunner_ = taskExecutor->ioRunner_;
    gpuRunner_ = taskExecutor->gpuRunner_;
}

TaskExecutorImpl::TaskExecutorImpl(const OHOS::Ace::TaskRunners& taskRunners)
{
    jsRunner_ = TaskRunnerAdapterFactory::Create(false, GenJsThreadName());

    platformRunner_ = taskRunners.GetPlatformTaskRunner();
    uiRunner_ = taskRunners.GetUITaskRunner();
    ioRunner_ = taskRunners.GetIOTaskRunner();
    gpuRunner_ = taskRunners.GetGPUTaskRunner();
}

void TaskExecutorImpl::InitPlatformThread(bool useCurrentEventRunner, bool isStageModel)
{
    platformRunner_ = TaskRunnerAdapterFactory::Create(useCurrentEventRunner, "");
    FillTaskTypeTable(TaskType::PLATFORM);
}

void TaskExecutorImpl::InitJsThread(bool newThread)
{
    if (newThread) {
        jsRunner_ = TaskRunnerAdapterFactory::Create(false, GenJsThreadName());
    } else {
        jsRunner_ = uiRunner_;
    }

    PostTaskToTaskRunner(
        jsRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::JS); }, 0);
}

void TaskExecutorImpl::InitOtherThreads(ThreadModelImpl* threadModel)
{
    if (threadModel) {
        InitOtherThreads(threadModel->GetTaskRunners());
    }
}

void TaskExecutorImpl::InitOtherThreads(const OHOS::Ace::TaskRunners& taskRunners)
{
    uiRunner_ = taskRunners.GetUITaskRunner();
    ioRunner_ = taskRunners.GetIOTaskRunner();
    gpuRunner_ = taskRunners.GetGPUTaskRunner();

    PostTaskToTaskRunner(
        uiRunner_, [this] { SetThreadPriority(UI_THREAD_PRIORITY); }, 0);
    PostTaskToTaskRunner(
        gpuRunner_, [this] { SetThreadPriority(GPU_THREAD_PRIORITY); }, 0);

    PostTaskToTaskRunner(
        uiRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::UI); }, 0);
    PostTaskToTaskRunner(
        ioRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::IO); }, 0);
    PostTaskToTaskRunner(
        gpuRunner_, [weak = AceType::WeakClaim(this)] { FillTaskTypeTable(weak, TaskType::GPU); }, 0);
}

bool TaskExecutorImpl::OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& callerInfo) const
{
    int32_t currentId = Container::CurrentId();
    auto traceIdFunc = [weak = WeakClaim(const_cast<TaskExecutorImpl*>(this)), type]() {
        auto sp = weak.Upgrade();
        if (sp) {
            sp->taskIdTable_[static_cast<uint32_t>(type)]++;
        }
    };
    TaskExecutor::Task wrappedTask =
        currentId >= 0 ? WrapTaskWithContainer(std::move(task), currentId, std::move(traceIdFunc)) : std::move(task);

    switch (type) {
        case TaskType::PLATFORM:
            return PostTaskToTaskRunner(platformRunner_, std::move(wrappedTask), delayTime);
        case TaskType::UI:
            return PostTaskToTaskRunner(uiRunner_, std::move(wrappedTask), delayTime);
        case TaskType::IO:
            return PostTaskToTaskRunner(ioRunner_, std::move(wrappedTask), delayTime);
        case TaskType::GPU:
            return PostTaskToTaskRunner(gpuRunner_, std::move(wrappedTask), delayTime);
        case TaskType::JS:
            return PostTaskToTaskRunner(jsRunner_, std::move(wrappedTask), delayTime);
        case TaskType::BACKGROUND:
            // Ignore delay time
            return BackgroundTaskExecutor::GetInstance().PostTask(std::move(wrappedTask));
        default:
            return false;
    }
}

TaskExecutor::Task TaskExecutorImpl::WrapTaskWithTraceId(Task&& task, int32_t id) const
{
    return WrapTaskWithContainer(std::move(task), id);
}

bool TaskExecutorImpl::WillRunOnCurrentThread(TaskType type) const
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

thread_local TaskExecutor::TaskType TaskExecutorImpl::localTaskType = TaskExecutor::TaskType::UNKNOWN;

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

bool TaskExecutorImpl::OnPreSyncTask(TaskType type) const
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

void TaskExecutorImpl::OnPostSyncTask() const
{
    std::lock_guard<std::mutex> lock(tableMutex_);
    syncTaskTable_.erase(std::this_thread::get_id());
}

void TaskExecutorImpl::DumpDeadSyncTask(TaskType from, TaskType to) const
{
    auto itFrom = taskTypeTable_.find(from);
    auto itTo = taskTypeTable_.find(to);

    ACE_DCHECK(itFrom != taskTypeTable_.end());
    ACE_DCHECK(itTo != taskTypeTable_.end());

    LOGE("DEAD LOCK HAPPEN: %{public}s(%{public}d, %{public}s) -> %{public}s(%{public}d, %{public}s)",
        TaskTypeToString(from), itFrom->second.tid, itFrom->second.threadName.c_str(), TaskTypeToString(to),
        itTo->second.tid, itTo->second.threadName.c_str());
}
#endif

void TaskExecutorImpl::FillTaskTypeTable(TaskType type)
{
    constexpr size_t MAX_THREAD_NAME_SIZE = 32;
    char threadNameBuf[MAX_THREAD_NAME_SIZE] = { 0 };
    const char* threadName = threadNameBuf;
#if !defined(PREVIEW) and !defined(IOS_PLATFORM)
#ifdef OHOS_STANDARD_SYSTEM
    if (prctl(PR_GET_NAME, threadNameBuf) < 0) {
        threadName = "unknown";
    }
#else
    if (pthread_getname_np(pthread_self(), threadNameBuf, sizeof(threadNameBuf)) != 0) {
        threadName = "unknown";
    }
#endif
#endif

    localTaskType = type;
    ThreadInfo info = {
        .threadId = std::this_thread::get_id(),
#if !defined(PREVIEW) and !defined(IOS_PLATFORM)
        .tid = gettid(),
#endif
        .threadName = threadName,
    };

    std::lock_guard<std::mutex> lock(tableMutex_);
    taskTypeTable_.emplace(type, info);
}

void TaskExecutorImpl::FillTaskTypeTable(const WeakPtr<TaskExecutorImpl>& weak, TaskType type)
{
    auto taskExecutor = weak.Upgrade();
    if (taskExecutor) {
        taskExecutor->FillTaskTypeTable(type);
    }
}
} // namespace OHOS::Ace
