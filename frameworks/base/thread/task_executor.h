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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_THREAD_TASK_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_THREAD_TASK_EXECUTOR_H

#include <cstdint>
#include <functional>

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/noncopyable.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace {

// 1. Must be consistent with AppExecFwk::EventQueue::Priority.
// 2. Do not use this ability arbitrarily.
enum class PriorityType : int32_t {
    // The highest priority queue, should be distributed until the tasks in the queue are completed.
    VIP = 0,
    // Event that should be distributed at once if possible.
    IMMEDIATE,
    // High priority event, sorted by handle time, should be distributed before low priority event.
    HIGH,
    // Normal event, sorted by handle time.
    LOW,
    // Event that should be distributed only if no other event right now.
    IDLE,
};

class TaskExecutor : public AceType {
    DECLARE_ACE_TYPE(TaskExecutor, AceType);
    ACE_DISALLOW_COPY_AND_MOVE(TaskExecutor);

public:
    using Task = std::function<void()>;
    using CancelableTask = CancelableCallback<void()>;

    static constexpr int32_t TASK_TYPE_SIZE = 7;
    enum class TaskType : uint32_t {
        PLATFORM = 0,
        UI,
        IO,
        GPU,
        JS,
        BACKGROUND,
        UNKNOWN,
    };

    ~TaskExecutor() override = default;

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(
        Task&& task, TaskType type, const std::string& name, PriorityType priorityType = PriorityType::LOW) const
    {
        return PostDelayedTask(std::move(task), type, 0, name, priorityType);
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostTask(const Task& task, TaskType type, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const
    {
        return PostDelayedTask(task, type, 0, name, priorityType);
    }

    /**
     * Post a task to the specified thread with a trace id.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param id The id to trace the task.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTaskWithTraceId(Task&& task, TaskType type, int32_t id, const std::string& name) const
    {
        Task wrappedTask = WrapTaskWithTraceId(std::move(task), id);
        return PostDelayedTask(std::move(wrappedTask), type, 0, name);
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param id The id to trace the task.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostTaskWithTraceId(const Task& task, TaskType type, int32_t id, const std::string& name) const
    {
        Task wrappedTask = WrapTaskWithTraceId(Task(task), id);
        return PostDelayedTask(std::move(wrappedTask), type, 0, name);
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const
    {
        if (delayTime > 0 && type == TaskType::BACKGROUND) {
            return false;
        }
        return OnPostTask(std::move(task), type, delayTime, name, priorityType);
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(const Task& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const
    {
        return PostDelayedTask(Task(task), type, delayTime, name, priorityType);
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(
        Task&& task, TaskType type, const std::string& name, PriorityType priorityType = PriorityType::IMMEDIATE) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            task();
            return true;
        }
        return PostTaskAndWait(CancelableTask(std::move(task)), type, name, 0ms, priorityType);
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param timeoutMs Timeout in milliseconds before task execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTaskTimeout(const Task& task, TaskType type, uint32_t timeoutMs, const std::string& name) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            task();
            return true;
        }
        return PostTaskAndWait(
            CancelableTask(std::move(task)), type, name, std::chrono::milliseconds(timeoutMs));
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const Task& task, TaskType type, const std::string& name) const
    {
        return PostSyncTask(Task(task), type, name);
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(CancelableTask&& task, TaskType type, const std::string& name) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            CancelableTask avatar(task);
            task();
            return avatar.WaitUntilComplete();
        }
        return PostTaskAndWait(std::move(task), type, name, 0ms);
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const CancelableTask& task, TaskType type, const std::string& name) const
    {
        return PostSyncTask(CancelableTask(task), type, name);
    }

    /**
     * The task use PostDelayedTask will new an object TraceId, when use
     * RemoveTask will cause memory overflow.
     * Post a delayed task without traceId to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTaskWithoutTraceId(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const
    {
        if (delayTime > 0 && type == TaskType::BACKGROUND) {
            return false;
        }
        return OnPostTaskWithoutTraceId(std::move(task), type, delayTime, name, priorityType);
    }

    virtual void AddTaskObserver(Task&& callback) = 0;
    virtual void RemoveTaskObserver() = 0;
    virtual bool WillRunOnCurrentThread(TaskType type) const = 0;
    virtual void RemoveTask(TaskType type, const std::string &name) = 0;

    virtual int32_t GetTid(TaskType type)
    {
        return 0;
    }

    virtual uint32_t GetTotalTaskNum(TaskType type)
    {
        return 0;
    }

    static PriorityType GetPriorityTypeWithCheck(
        PriorityType priorityType, PriorityType defaultPriority = PriorityType::LOW)
    {
        // Temporary interface, used to control whether priority adjustment takes effect.
        return SystemProperties::GetTaskPriorityAdjustmentEnable() ? priorityType : defaultPriority;
    }

protected:
    TaskExecutor() = default;

    virtual bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const = 0;
    virtual Task WrapTaskWithTraceId(Task&& task, int32_t id) const = 0;
    virtual bool OnPostTaskWithoutTraceId(Task&& task, TaskType type, uint32_t delayTime, const std::string& name,
        PriorityType priorityType = PriorityType::LOW) const = 0;

#ifdef ACE_DEBUG
    virtual bool OnPreSyncTask(TaskType type) const
    {
        return true;
    }
    virtual void OnPostSyncTask() const {}
#endif

private:
    bool PostTaskAndWait(CancelableTask&& task, TaskType type, const std::string& name,
        std::chrono::milliseconds timeoutMs = 0ms, PriorityType priorityType = PriorityType::IMMEDIATE) const
    {
#ifdef ACE_DEBUG
        bool result = false;
        if (OnPreSyncTask(type)) {
            result = OnPostTask(Task(task), type, 0, name, priorityType) && task.WaitUntilComplete(timeoutMs);
            OnPostSyncTask();
        }
        return result;
#else
        return OnPostTask(Task(task), type, 0, name, priorityType) && task.WaitUntilComplete(timeoutMs);
#endif
    }
};

class TaskWrapper {
public:
    virtual bool WillRunOnCurrentThread() = 0;
    virtual void Call(const TaskExecutor::Task& task) = 0;

    virtual ~TaskWrapper() = default;
};

class SingleTaskExecutor final {
public:
    using Task = TaskExecutor::Task;
    using CancelableTask = TaskExecutor::CancelableTask;
    using TaskType = TaskExecutor::TaskType;

    SingleTaskExecutor(RefPtr<TaskExecutor>&& taskExecutor, TaskType type)
        : taskExecutor_(std::move(taskExecutor)), type_(type)
    {}
    SingleTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor, TaskType type)
        : taskExecutor_(taskExecutor), type_(type)
    {}
    ~SingleTaskExecutor() = default;

    static SingleTaskExecutor Make(RefPtr<TaskExecutor>&& taskExecutor, TaskType type)
    {
        return SingleTaskExecutor(std::move(taskExecutor), type);
    }

    static SingleTaskExecutor Make(const RefPtr<TaskExecutor>& taskExecutor, TaskType type)
    {
        return SingleTaskExecutor(taskExecutor, type);
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(Task&& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostTask(std::move(task), type_, name) : false;
    }

    /**
     * Post a task to the specified thread with priority.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @param priorityType Priority of the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(Task&& task, const std::string& name, PriorityType priorityType) const
    {
        return taskExecutor_ ? taskExecutor_->PostTask(std::move(task), type_, name, priorityType) : false;
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(const Task& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostTask(task, type_, name) : false;
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(Task&& task, uint32_t delayTime, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostDelayedTask(std::move(task), type_, delayTime, name) : false;
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @param name Name of the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(const Task& task, uint32_t delayTime, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostDelayedTask(task, type_, delayTime, name) : false;
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(Task&& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(std::move(task), type_, name) : false;
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const Task& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(task, type_, name) : false;
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(CancelableTask&& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(std::move(task), type_, name) : false;
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param name Name of the task.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const CancelableTask& task, const std::string& name) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(task, type_, name) : false;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    bool IsRunOnCurrentThread() const
    {
        return taskExecutor_ ? taskExecutor_->WillRunOnCurrentThread(type_) : false;
    }

private:
    RefPtr<TaskExecutor> taskExecutor_;
    TaskExecutor::TaskType type_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_THREAD_TASK_EXECUTOR_H
