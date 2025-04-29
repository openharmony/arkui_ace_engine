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

#include "core/common/task_runners.h"

namespace OHOS::Ace {
TaskRunners::TaskRunners(const std::string& label, const RefPtr<TaskRunnerAdapter>& platform,
    const RefPtr<TaskRunnerAdapter>& gpu, const RefPtr<TaskRunnerAdapter>& ui, const RefPtr<TaskRunnerAdapter>& io)
    : label_(label), platform_(platform), gpu_(gpu), ui_(ui), io_(io)
{}

RefPtr<TaskRunnerAdapter> TaskRunners::GetPlatformTaskRunner() const
{
    return platform_;
}

RefPtr<TaskRunnerAdapter> TaskRunners::GetUITaskRunner() const
{
    return ui_;
}

RefPtr<TaskRunnerAdapter> TaskRunners::GetIOTaskRunner() const
{
    return io_;
}

RefPtr<TaskRunnerAdapter> TaskRunners::GetGPUTaskRunner() const
{
    return gpu_;
}

const std::string& TaskRunners::GetLabel() const
{
    return label_;
}

bool TaskRunners::IsValid() const
{
    return platform_ && gpu_ && ui_ && io_;
}
} // namespace OHOS::Ace
