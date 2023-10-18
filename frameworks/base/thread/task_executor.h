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

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

namespace OHOS::Ace {
struct Caller final {
#if __has_builtin(__builtin_FILE)
    Caller(std::string file = __builtin_FILE(), int line = __builtin_LINE(), std::string func = __builtin_FUNCTION())
        : file_(file), line_(line), func_(func)
    {
        if (!file_.empty()) {
            size_t split = file_.find_last_of("/\\");
            if (split == std::string::npos) {
                split = 0;
            }
            caller_ = std::string("[" + file_.substr(split + 1) + "(" + func_ + ":" + std::to_string(line_) + ")]");
        }
    }
#else
    Caller() {
    }
#endif

    std::string file_;
    int32_t line_ = 0;
    std::string func_;
    std::string caller_ = "[]";
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
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(Task&& task, TaskType type, const Caller& caller = {}) const
    {
        return PostDelayedTask(std::move(task), type, 0, caller);
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostTask(const Task& task, TaskType type, const Caller& caller = {}) const
    {
        return PostDelayedTask(task, type, 0, caller);
    }

    /**
     * Post a task to the specified thread with a trace id.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param id The id to trace the task.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTaskWithTraceId(Task&& task, TaskType type, int32_t id, const Caller& caller = {}) const
    {
        Task wrappedTask = WrapTaskWithTraceId(std::move(task), id);
        return PostDelayedTask(std::move(wrappedTask), type, 0, caller);
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param id The id to trace the task.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostTaskWithTraceId(const Task& task, TaskType type, int32_t id, const Caller& caller = {}) const
    {
        Task wrappedTask = WrapTaskWithTraceId(Task(task), id);
        return PostDelayedTask(std::move(wrappedTask), type, 0, caller);
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(Task&& task, TaskType type, uint32_t delayTime, const Caller& caller = {}) const
    {
        if (delayTime > 0 && type == TaskType::BACKGROUND) {
            return false;
        }
        return OnPostTask(std::move(task), type, delayTime, caller.caller_);
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(const Task& task, TaskType type, uint32_t delayTime, const Caller& caller = {}) const
    {
        return PostDelayedTask(Task(task), type, delayTime, caller);
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(Task&& task, TaskType type, const Caller& caller = {}) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            task();
            return true;
        }
        return PostTaskAndWait(CancelableTask(std::move(task)), type, 0ms, caller.caller_);
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @param timeoutMs Timeout in milliseconds before task execution.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTaskTimeout(const Task& task, TaskType type, uint32_t timeoutMs, const Caller& caller = {}) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            task();
            return true;
        }
        return PostTaskAndWait(
            CancelableTask(std::move(task)), type, std::chrono::milliseconds(timeoutMs), caller.caller_);
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const Task& task, TaskType type, const Caller& caller = {}) const
    {
        return PostSyncTask(Task(task), type, caller);
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(CancelableTask&& task, TaskType type, const Caller& caller = {}) const
    {
        if (!task || type == TaskType::BACKGROUND) {
            return false;
        } else if (WillRunOnCurrentThread(type)) {
            CancelableTask avatar(task);
            task();
            return avatar.WaitUntilComplete();
        }
        return PostTaskAndWait(std::move(task), type, 0ms, caller.caller_);
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @param type FrontendType of task, used to specify the thread.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const CancelableTask& task, TaskType type, const Caller& caller = {}) const
    {
        return PostSyncTask(CancelableTask(task), type, caller);
    }

    virtual void AddTaskObserver(Task&& callback) = 0;
    virtual void RemoveTaskObserver() = 0;
    virtual bool WillRunOnCurrentThread(TaskType type) const = 0;

    virtual int32_t GetTid(TaskType type)
    {
        return 0;
    }

    virtual uint32_t GetTotalTaskNum(TaskType type)
    {
        return 0;
    }

protected:
    TaskExecutor() = default;

    virtual bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime, const std::string& callerInfo) const = 0;
    virtual Task WrapTaskWithTraceId(Task&& task, int32_t id) const = 0;

#ifdef ACE_DEBUG
    virtual bool OnPreSyncTask(TaskType type) const
    {
        return true;
    }
    virtual void OnPostSyncTask() const {}
#endif

private:
    bool PostTaskAndWait(CancelableTask&& task, TaskType type, std::chrono::milliseconds timeoutMs = 0ms,
        const std::string& callerInfo = {}) const
    {
#ifdef ACE_DEBUG
        bool result = false;
        if (OnPreSyncTask(type)) {
            result = OnPostTask(Task(task), type, 0, callerInfo) && task.WaitUntilComplete(timeoutMs);
            OnPostSyncTask();
        }
        return result;
#else
        return OnPostTask(Task(task), type, 0, callerInfo) && task.WaitUntilComplete(timeoutMs);
#endif
    }
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
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(Task&& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostTask(std::move(task), type_, caller) : false;
    }

    /**
     * Post a task to the specified thread.
     *
     * @param task Task which need execution.
     * @return Returns 'true' whether task has been post successfully.
     */
    bool PostTask(const Task& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostTask(task, type_, caller) : false;
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(Task&& task, uint32_t delayTime, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostDelayedTask(std::move(task), type_, delayTime, caller) : false;
    }

    /**
     * Post a delayed task to the specified thread.
     * Never allow to post a background delayed task.
     *
     * @param task Task which need execution.
     * @param delayTime Wait a period of time in milliseconds before execution.
     * @return Returns 'true' if task has been posted successfully.
     */
    bool PostDelayedTask(const Task& task, uint32_t delayTime, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostDelayedTask(task, type_, delayTime, caller) : false;
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(Task&& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(std::move(task), type_, caller) : false;
    }

    /**
     * Post a task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const Task& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(task, type_, caller) : false;
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(CancelableTask&& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(std::move(task), type_, caller) : false;
    }

    /**
     * Post a cancelable task to the specified thread and wait until finished executing.
     * Never allow to post a background synchronous task.
     *
     * @param task Task which need execution.
     * @return Returns 'true' whether task has been executed.
     */
    bool PostSyncTask(const CancelableTask& task, const Caller& caller = {}) const
    {
        return taskExecutor_ ? taskExecutor_->PostSyncTask(task, type_, caller) : false;
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
