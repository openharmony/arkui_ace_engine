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

#include "adapter/preview/external/flutter/platform_task_runner_adapter.h"

#include "flutter/fml/time/time_point.h"
namespace flutter {

PlatformTaskRunnerAdapter::PlatformTaskRunnerAdapter(bool useCurrentEventRunner) : fml::TaskRunner(nullptr) {}

void PlatformTaskRunnerAdapter::PostTask(fml::closure task)
{
    MainEventLoop::GetInstance().PostTask(std::move(task), fml::TimePoint::Now());
}

void PlatformTaskRunnerAdapter::PostTaskForTime(fml::closure task, fml::TimePoint target_time)
{
    MainEventLoop::GetInstance().PostTask(std::move(task), target_time);
}

void PlatformTaskRunnerAdapter::PostDelayedTask(fml::closure task, fml::TimeDelta delay)
{
    MainEventLoop::GetInstance().PostTask(std::move(task), fml::TimePoint::Now() + delay);
}

bool PlatformTaskRunnerAdapter::RunsTasksOnCurrentThread()
{
    return MainEventLoop::GetInstance().RunsTasksOnCurrentThread();
}

fml::TaskQueueId PlatformTaskRunnerAdapter::GetTaskQueueId()
{
    return fml::_kUnmerged;
}

fml::RefPtr<fml::TaskRunner> PlatformTaskRunnerAdapter::CurrentTaskRunner(bool useCurrentEventRunner)
{
    static fml::RefPtr<fml::TaskRunner> taskRunner_ =
        fml::MakeRefCounted<PlatformTaskRunnerAdapter>(useCurrentEventRunner);
    return taskRunner_;
}

} // namespace flutter
