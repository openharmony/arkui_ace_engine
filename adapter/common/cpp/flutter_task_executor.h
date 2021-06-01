/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_CPP_FLUTTER_TASK_EXECUTOR_H
#define FOUNDATION_ACE_ADAPTER_CPP_FLUTTER_TASK_EXECUTOR_H

#include "flutter/common/task_runners.h"
#include "flutter/fml/thread.h"

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

class ACE_EXPORT FlutterTaskExecutor final : public TaskExecutor {
    DECLARE_ACE_TYPE(FlutterTaskExecutor, TaskExecutor);

public:
    ~FlutterTaskExecutor() final;
    // Must call this method on platform thread
    void InitPlatformThread();
    void InitJsThread(bool newThread = true);
    void InitOtherThreads(const flutter::TaskRunners& taskRunners);

    void AddTaskObserver(Task&& callback) override;
    void RemoveTaskObserver() override;
    bool WillRunOnCurrentThread(TaskType type) const final;

private:
    bool OnPostTask(Task&& task, TaskType type, uint32_t delayTime) const final;

    std::unique_ptr<fml::Thread> jsThread_;

    fml::RefPtr<fml::TaskRunner> platformRunner_;
    fml::RefPtr<fml::TaskRunner> uiRunner_;
    fml::RefPtr<fml::TaskRunner> ioRunner_;
    fml::RefPtr<fml::TaskRunner> jsRunner_;
    fml::RefPtr<fml::TaskRunner> gpuRunner_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_CPP_FLUTTER_TASK_EXECUTOR_H
