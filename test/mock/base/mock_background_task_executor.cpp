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

#include "base/thread/background_task_executor.h"

namespace OHOS::Ace {
BackgroundTaskExecutor& BackgroundTaskExecutor::GetInstance()
{
    static BackgroundTaskExecutor instance;
    return instance;
}

BackgroundTaskExecutor::BackgroundTaskExecutor() = default;

BackgroundTaskExecutor::~BackgroundTaskExecutor() {}

bool BackgroundTaskExecutor::PostTask(Task&& task, BgTaskPriority priority)
{
    currentThreadNum_++;
    maxThreadNum_++;
    running_ = true;
    purgeFlags_++;
    return true;
}

bool BackgroundTaskExecutor::PostTask(const Task& task, BgTaskPriority priority)
{
    return true;
}

void BackgroundTaskExecutor::StartNewThreads(size_t num) {}

void BackgroundTaskExecutor::ThreadLoop(uint32_t threadNo) {}

void BackgroundTaskExecutor::TriggerGarbageCollection() {}
} // namespace OHOS::Ace
