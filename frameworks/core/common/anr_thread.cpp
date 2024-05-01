/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstring>
#include "anr_thread.h"

#include "core/common/task_runner_adapter.h"
#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {

namespace {
RefPtr<TaskRunnerAdapter> g_anrThread;
} // namespace

void AnrThread::Start()
{
    if (!g_anrThread) {
        g_anrThread = TaskRunnerAdapterFactory::Create(false, "anr");
    }
}

void AnrThread::Stop()
{
    g_anrThread.Reset();
}

bool AnrThread::PostTaskToTaskRunner(Task&& task, uint32_t delayTime, const std::string& name)
{
    if (!g_anrThread || !task) {
        return false;
    }

    if (delayTime > 0) {
        g_anrThread->PostDelayedTask(std::move(task), delayTime, name);
    } else {
        g_anrThread->PostTask(std::move(task), name);
    }
    return true;
}
} // namespace OHOS::Ace
