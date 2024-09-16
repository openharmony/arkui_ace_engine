/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "component_test/test_task_scheduler.h"

#include "core/common/task_runner_adapter.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace::ComponentTest {

void TestTaskScheduler::Initialize(RefPtr<IdleWatcher> idleWatcher, RefPtr<TaskExecutor> taskExecutor)
{
    idleWatcher_ = idleWatcher;
    taskExecutor_ = taskExecutor;
    if (!testTaskSchedulerThread_) {
        testTaskSchedulerThread_ = TaskRunnerAdapterFactory::Create(false, "TestTaskScheduler");
    }
}

void TestTaskScheduler::Destroy()
{
    if (testTaskSchedulerThread_) {
        testTaskSchedulerThread_.Reset();
    }
}

void TestTaskScheduler::PushTask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish,
    TaskExecutor::TaskType taskType, void* data, uint32_t delay)
{
    std::function<void()> task_;
    std::function<void()> finish_;
    if (onFinish) {
        finish_ = [this, onFinish = std::move(onFinish), taskType, data]() {
            idleWatcher_->RequestNextIdleStatusNotification([this, onFinish = std::move(onFinish), taskType, data]() {
                taskExecutor_->PostTask([data, onFinish = move(onFinish)]() { onFinish(data); }, taskType, {});
            });
        };
    } else {
        finish_ = []() {};
    }
    if (task) {
        task_ = [data, task = std::move(task), finish = std::move(finish_)]() {
            task(data);
            finish();
        };
    } else {
        task_ = [finish = std::move(finish_)]() { finish(); };
    }

    testTaskSchedulerThread_->PostDelayedTask(
        [this, task = std::move(task_), taskType]() {
            idleWatcher_->RequestNextIdleStatusNotification(
                [this, task = std::move(task), taskType]() {
                    taskExecutor_->PostTask([task = std::move(task)]() { task(); }, taskType, {});
                },
                true);
        },
        delay, {});
}
} // namespace OHOS::Ace::ComponentTest
