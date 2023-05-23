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

#include "core/common/flutter/flutter_thread_model.h"

#include <memory>

#ifdef FML_EMBEDDER_ONLY
#undef FML_EMBEDDER_ONLY
#define FML_EMBEDDER_ONLY
#endif

#include "common/task_runners.h"
#include "flutter/fml/message_loop.h"
#if defined(OHOS_PLATFORM) || defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "flutter/shell/platform/ohos/platform_task_runner_adapter.h"
#elif defined(PREVIEW)
#include "adapter/preview/external/flutter/platform_task_runner_adapter.h"
#endif
#include "shell/common/thread_host.h"

#include "base/log/log.h"

namespace OHOS::Ace {
std::unique_ptr<FlutterThreadModel> FlutterThreadModel::CreateThreadModel(
    bool useCurrentEventRunner, bool hasUiThread, bool hasGpuThread)
{
    // Create threads
    static size_t sCount = 1;
    auto threadLabel = std::to_string(sCount++);
    uint64_t typeMask = 0;

    if (hasUiThread) {
        typeMask |= flutter::ThreadHost::Type::UI;
    }
    if (hasGpuThread) {
        typeMask |= flutter::ThreadHost::Type::GPU;
    }
    flutter::ThreadHost threadHost = { threadLabel, typeMask };

    // Create Taskrunners
    fml::MessageLoop::EnsureInitializedForCurrentThread();
    fml::RefPtr<fml::TaskRunner> gpuRunner;
    fml::RefPtr<fml::TaskRunner> uiRunner;
    
#if defined(OHOS_PLATFORM) || defined(PREVIEW)
    fml::RefPtr<fml::TaskRunner> platformRunner =
        flutter::PlatformTaskRunnerAdapter::CurrentTaskRunner(useCurrentEventRunner);
#else
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    fml::RefPtr<fml::TaskRunner> platformRunner;
    if (hasUiThread) {
        platformRunner = fml::MessageLoop::GetCurrent().GetTaskRunner();
    } else {
        LOGI("FlutterThreadModel create platfrom thread by eventhandler.");
        platformRunner = flutter::PlatformTaskRunnerAdapter::CurrentTaskRunner(useCurrentEventRunner);
    }
#else
    fml::RefPtr<fml::TaskRunner> platformRunner;
    platformRunner = fml::MessageLoop::GetCurrent().GetTaskRunner();
#endif
#endif

    if (hasUiThread) {
        uiRunner = threadHost.ui_thread->GetTaskRunner();
    } else {
        uiRunner = platformRunner;
    }
    if (hasGpuThread) {
        gpuRunner = threadHost.gpu_thread->GetTaskRunner();
    } else {
        gpuRunner = uiRunner;
    }

    flutter::TaskRunners taskRunners(threadLabel, // label
        platformRunner,                           // platform
        gpuRunner,                                // gpu
        uiRunner,                                 // ui
        uiRunner                                  // io
    );

    return std::make_unique<FlutterThreadModel>(std::move(threadHost), std::move(taskRunners));
}

FlutterThreadModel::FlutterThreadModel(flutter::ThreadHost threadHost, flutter::TaskRunners taskRunners)
    : threadHost_(std::move(threadHost)), taskRunners_(std::move(taskRunners))
{}
} // namespace OHOS::Ace
