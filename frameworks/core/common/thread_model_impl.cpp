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

#include "core/common/thread_model_impl.h"

#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {
std::unique_ptr<ThreadModelImpl> ThreadModelImpl::CreateThreadModel(
    bool useCurrentEventRunner, bool hasUiThread, bool hasGpuThread)
{
    // Create threads
    static size_t sCount = 1;
    auto threadLabel = std::to_string(sCount++);
    uint64_t typeMask = 0;

    if (hasUiThread) {
        typeMask |= ThreadContainer::ThreadType::UI;
    }
    if (hasGpuThread) {
        typeMask |= ThreadContainer::ThreadType::GPU;
    }
    ThreadContainer threadContainer = { threadLabel, typeMask };

    // Create Taskrunners
    RefPtr<TaskRunnerAdapter> gpuRunner;
    RefPtr<TaskRunnerAdapter> uiRunner;

    RefPtr<TaskRunnerAdapter> platformRunner = TaskRunnerAdapterFactory::Create(useCurrentEventRunner, "");
    if (hasUiThread) {
        uiRunner = threadContainer.uiThread;
    } else {
        uiRunner = platformRunner;
    }
    if (hasGpuThread) {
        gpuRunner = threadContainer.gpuThread;
    } else {
        gpuRunner = uiRunner;
    }

    TaskRunners taskRunners(threadLabel, platformRunner, gpuRunner, uiRunner, uiRunner);

    return std::make_unique<ThreadModelImpl>(std::move(threadContainer), std::move(taskRunners));
}

const TaskRunners& ThreadModelImpl::GetTaskRunners() const
{
    return taskRunners_;
}

ThreadModelImpl::ThreadModelImpl(ThreadContainer threadContainer, TaskRunners taskRunners)
    : threadContainer_(std::move(threadContainer)), taskRunners_(std::move(taskRunners))
{}
} // namespace OHOS::Ace
