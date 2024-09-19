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

#ifndef OHOS_ACE_COMPONENT_TEST_TASK_SCHEDULER_H
#define OHOS_ACE_COMPONENT_TEST_TASK_SCHEDULER_H

#include <functional>
#include <mutex>

#include "component_test/idle_watcher.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::ComponentTest {

class TestTaskScheduler {
private:
    RefPtr<IdleWatcher> idleWatcher_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<TaskRunnerAdapter> testTaskSchedulerThread_;
    TestTaskScheduler() = default;
    void Initialize(RefPtr<IdleWatcher>, RefPtr<TaskExecutor>);
    void Destroy();
    void PushTask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish,
        TaskExecutor::TaskType taskType, void* data, uint32_t delay);
    friend class ComponentTestManagerImpl;
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_TASK_SCHEDULER_H
