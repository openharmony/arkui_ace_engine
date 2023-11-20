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

#include "adapter/preview/osal/task/task_runner_adapter_impl.h"

#include "jsapp/rich/external/EventHandler.h"

namespace OHOS::Ace {
void TaskRunnerAdapterImpl::PostTask(std::function<void()> task, const std::string& caller)
{
    OHOS::AppExecFwk::EventHandler::PostTask(std::move(task));
}

void TaskRunnerAdapterImpl::PostTaskForTime(std::function<void()> task, uint32_t targetTime, const std::string& caller)
{
    OHOS::AppExecFwk::EventHandler::PostTask(std::move(task), targetTime);
}

void TaskRunnerAdapterImpl::PostDelayedTask(std::function<void()> task, uint32_t delay, const std::string& caller)
{
    OHOS::AppExecFwk::EventHandler::PostTask(std::move(task), delay);
}

bool TaskRunnerAdapterImpl::RunsTasksOnCurrentThread()
{
    return OHOS::AppExecFwk::EventHandler::IsCurrentRunnerThread();
}

void TaskRunnerAdapterImpl::Initialize(bool useCurrentEventRunner, const std::string& name) {}
} // namespace OHOS::Ace
