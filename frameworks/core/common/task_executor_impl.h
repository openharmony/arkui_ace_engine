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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_EXECUTOR_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_EXECUTOR_IMPL_H

#include <array>
#include <atomic>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "core/common/task_runner_adapter.h"
#include "core/common/thread_model_impl.h"

namespace OHOS::Ace {
class ACE_EXPORT TaskExecutorImpl final : public TaskExecutor {
    DECLARE_ACE_TYPE(TaskExecutorImpl, TaskExecutor);

public:
    explicit TaskExecutorImpl(const RefPtr<TaskExecutorImpl>& taskExecutors);
    explicit TaskExecutorImpl(const TaskRunners& taskRunners);
    explicit TaskExecutorImpl(std::shared_ptr<TaskWrapper> taskWrapper) : taskWrapper_(taskWrapper) {}
    TaskExecutorImpl() = default;
    ~TaskExecutorImpl() override {};
    void InitPlatformThread(bool useCurrentEventRunner = false, bool isStageModel = false);
    void InitJsThread(bool newThread = true);
    void InitOtherThreads(const TaskRunners& taskRunners);
    void InitOtherThreads(ThreadModelImpl* threadModel);

    void AddTaskObserver(Task&& callback) override {};
    void RemoveTaskObserver() override {};
    bool WillRunOnCurrentThread(TaskType type) const final;
    void RemoveTask(TaskType type, const std::string &name) override;

    int32_t GetTid(TaskType type) final
    {
        return taskTypeTable_[type].tid;
    }

    uint32_t GetTotalTaskNum(TaskType type) final
    {
        return taskIdTable_[static_cast<uint32_t>(type)];
    }

private:
    TaskExecutor::Task WrapTaskWithContainer(
        TaskExecutor::Task&& task, int32_t id, std::function<void()>&& traceIdFunc = nullptr) const;
    TaskExecutor::Task WrapTaskWithCustomWrapper(
        TaskExecutor::Task&& task, int32_t id, uint32_t delayTime,
        std::function<void()>&& traceIdFunc = nullptr) const;
    bool PostTaskToTaskRunner(const RefPtr<TaskRunnerAdapter>& taskRunner, TaskExecutor::Task&& task,
        uint32_t delayTime, const std::string& name, PriorityType priorityType = PriorityType::LOW) const;
    void SetThreadPriority(int32_t priority) const;
    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const final;
    Task WrapTaskWithTraceId(Task&& task, int32_t id) const final;
    void RemoveTaskFromTaskRunner(const RefPtr<TaskRunnerAdapter>& taskRunner, const std::string& name);
    bool OnPostTaskWithoutTraceId(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const final;

#ifdef ACE_DEBUG
    bool OnPreSyncTask(TaskType type) const final;
    void OnPostSyncTask() const final;

    void DumpDeadSyncTask(TaskType from, TaskType to) const;
    mutable std::unordered_map<std::thread::id, std::thread::id> syncTaskTable_;
#endif

    void FillTaskTypeTable(TaskType type);
    static void FillTaskTypeTable(const WeakPtr<TaskExecutorImpl>& weak, TaskType type);

    struct ThreadInfo {
        std::thread::id threadId;
        int32_t tid = 0;
        std::string threadName;
    };

    mutable std::mutex tableMutex_;
    std::unordered_map<TaskType, ThreadInfo> taskTypeTable_;
    mutable std::array<std::atomic<uint32_t>, TASK_TYPE_SIZE> taskIdTable_ { 0 };

    static thread_local TaskType localTaskType;

    RefPtr<TaskRunnerAdapter> platformRunner_;
    RefPtr<TaskRunnerAdapter> uiRunner_;
    RefPtr<TaskRunnerAdapter> ioRunner_;
    RefPtr<TaskRunnerAdapter> jsRunner_;
    RefPtr<TaskRunnerAdapter> gpuRunner_;

    std::shared_ptr<TaskWrapper> taskWrapper_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMMON_TASK_EXECUTOR_IMPL_H
