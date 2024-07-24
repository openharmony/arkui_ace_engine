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

#ifndef OHOS_ACE_COMPONENT_TEST_MANAGER_IMPL_H
#define OHOS_ACE_COMPONENT_TEST_MANAGER_IMPL_H

#include <mutex>
#include <shared_mutex>
#include <unordered_map>

#include "component_test/component_test_manager.h"
#include "component_test/test_config.h"

#include "base/thread/task_executor.h"

namespace OHOS::Ace::ComponentTest {

class ComponentTestManagerImpl : public ComponentTestManager {
public:
    static RefPtr<ComponentTestManagerImpl> Get();
    static RefPtr<ComponentTestManagerImpl> GetInitialized();
    void Destroy();
    void PostUITask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data = nullptr,
        uint32_t delay = 0) override;
    void PostJSTask(std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data = nullptr,
        uint32_t delay = 0) override;
    void SetTestCaseAttribute(TestCaseAttribute attribute) override;
    void Record(std::string info, std::string position, Result result) override;
    void Finish() override;
    void ClaimLongOperation() override;
    void LongOperationComplete() override;
    void RequestContinuousIdleStatusNotification(IdleNotifycallback&& notifycallback) override;
    ~ComponentTestManagerImpl() override
    {
        Destroy();
    }

    PipelineStatusHolder pipelineStatusHolder;
    TestConfig testConfig;

private:
    static std::mutex mtx_;
    ComponentTestManagerImpl();
    void Initialize(RefPtr<TaskExecutor> taskExecutor);
    static RefPtr<ComponentTestManagerImpl> instance;
    RefPtr<IdleWatcher> idleWatcher_;
    TestTaskScheduler testTaskScheduler_;
    RefPtr<TaskExecutor> taskExecutor_;
    TestResultRecorder testResultRecorder_;
    bool initialized_;
};
} // namespace OHOS::Ace::ComponentTest

#endif // OHOS_ACE_COMPONENT_TEST_MANAGER_IMPL_H
