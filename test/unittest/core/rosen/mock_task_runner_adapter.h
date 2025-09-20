/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_MOCK_TASK_RUNNER_ADAPTER_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_MOCK_TASK_RUNNER_ADAPTER_H

#include "core/common/task_runner_adapter.h"

namespace OHOS::Ace {
class MockTaskRunnerAdapter : public TaskRunnerAdapter {
    DECLARE_ACE_TYPE(MockTaskRunnerAdapter, TaskRunnerAdapter);

public:
    MockTaskRunnerAdapter() = default;
    ~MockTaskRunnerAdapter() = default;

    void PostTask(std::function<void()> task, const std::string& name, PriorityType priorityType = PriorityType::LOW)
    {
        task();
    }

    bool RunsTasksOnCurrentThread() override
    {
        return true;
    };
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_MOCK_TASK_RUNNER_ADAPTER_H
