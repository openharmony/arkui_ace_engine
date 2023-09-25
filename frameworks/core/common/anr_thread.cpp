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

#include "anr_thread.h"

#include "flutter/fml/thread.h"

namespace OHOS::Ace {

namespace {
std::unique_ptr<fml::Thread> g_anrThread;
} // namespace

void AnrThread::Start()
{
    if (!g_anrThread) {
        g_anrThread = std::make_unique<fml::Thread>("anr");
    }
}

void AnrThread::Stop()
{
    g_anrThread.reset();
}

bool AnrThread::PostTaskToTaskRunner(Task&& task, uint32_t delayTime)
{
    if (!g_anrThread || !task) {
        return false;
    }

    auto anrTaskRunner = g_anrThread->GetTaskRunner();
    if (delayTime > 0) {
        anrTaskRunner->PostDelayedTask(std::move(task), fml::TimeDelta::FromSeconds(delayTime), {});
    } else {
        anrTaskRunner->PostTask(std::move(task), {});
    }
    return true;
}
} // namespace OHOS::Ace
