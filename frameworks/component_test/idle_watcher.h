/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_COMPONENT_TEST_IDLE_WATCHER_H
#define OHOS_ACE_COMPONENT_TEST_IDLE_WATCHER_H

#include <functional>
#include <mutex>
#include <vector>

#include "component_test/pipeline_status.h"

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/task_runner_adapter.h"

namespace OHOS::Ace::ComponentTest {
using IdleNotifycallback = std::function<void()>;

#define CONTINUOUS_IDLE_TIME 5

class IdleMonitorThread : public AceType {
public:
    static RefPtr<IdleMonitorThread> Create();
    void Stop();
    void SetIdleNotifycallback(IdleNotifycallback);
    void SetTaskExecutor(RefPtr<TaskExecutor>);
    void PostInitializeTask();

private:
    RefPtr<TaskRunnerAdapter> thread;
    IdleNotifycallback callback_;
    RefPtr<TaskExecutor> taskExecutor_;
    void VsyncCountFirstCheck();
    void VsyncCountSecondCheck();
    void PostCheckTask(std::function<void()>&&, uint32_t);
};

class IdleWatcher : public AceType {
public:
    IdleWatcher(RefPtr<TaskExecutor> taskExecutor);
    void RequestNextIdleStatusNotification(IdleNotifycallback&& notifycallback, bool haveUIChange = false);
    void RequestContinuousIdleStatusNotification(IdleNotifycallback&& continuousIdleCallback);
    void ClaimLongOperation();
    void LongOperationComplete();

private:
    std::vector<IdleNotifycallback> pendingIdleObservers_;
    IdleNotifycallback continuousIdleCallback_;
    std::mutex observersMutex_;
    RefPtr<IdleMonitorThread> idleMonitorThread_;
    bool keepingIdle_;
    void TriggerIdleNotification();
    void Destroy();
    friend class ComponentTestManagerImpl;
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_IDLE_WATCHER_H
