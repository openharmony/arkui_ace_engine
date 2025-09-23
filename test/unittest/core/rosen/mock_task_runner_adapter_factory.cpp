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

#include "mock_task_runner_adapter.h"

#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {
RefPtr<TaskRunnerAdapter> TaskRunnerAdapterFactory::Create(bool useCurrentEventRunner, const std::string& threadName)
{
    RefPtr<TaskRunnerAdapter> taskRunnerAdapterImpl = AceType::MakeRefPtr<MockTaskRunnerAdapter>();
    return taskRunnerAdapterImpl;
}
} // namespace OHOS::Ace
