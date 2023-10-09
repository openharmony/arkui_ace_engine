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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_PLATFORM_TASK_RUNNER_ADAPTER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_PLATFORM_TASK_RUNNER_ADAPTER_H

#include "flutter/fml/message_loop_impl.h"
#include "flutter/fml/message_loop_task_queues.h"

namespace flutter {

class PlatformTaskRunnerAdapter : public fml::TaskRunner {
public:
    explicit PlatformTaskRunnerAdapter(bool useCurrentEventRunner);
    ~PlatformTaskRunnerAdapter() = default;
    void PostTask(fml::closure task, const std::string& caller) override;
    void PostTaskForTime(fml::closure task, fml::TimePoint target_time, const std::string& caller) override;
    void PostDelayedTask(fml::closure task, fml::TimeDelta delay, const std::string& caller) override;
    bool RunsTasksOnCurrentThread() override;
    fml::TaskQueueId GetTaskQueueId() override;
    static fml::RefPtr<fml::TaskRunner> CurrentTaskRunner(bool useCurrentEventRunner = false);
};

} // namespace flutter

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_EVENT_LOOP_PLATFORM_TASK_RUNNER_ADAPTER_H
