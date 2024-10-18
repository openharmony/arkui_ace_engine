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

#include "component_test/component_test_manager_impl.h"

#include <mutex>
#include <shared_mutex>
#include <unordered_map>

#include "adapter/preview/entrance/ace_container.h"

namespace OHOS::Ace::ComponentTest {

RefPtr<ComponentTestManagerImpl> ComponentTestManagerImpl::instance = nullptr;
std::mutex ComponentTestManagerImpl::mtx_;

RefPtr<ComponentTestManagerImpl> ComponentTestManagerImpl::Get()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (instance == nullptr) {
        instance = new ComponentTestManagerImpl();
    }
    return instance;
}

RefPtr<ComponentTestManagerImpl> ComponentTestManagerImpl::GetInitialized()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (instance == nullptr) {
        instance = new ComponentTestManagerImpl();
    }
    if (!instance->initialized_) {
        auto container = OHOS::Ace::Container::GetContainer(Platform::ACE_INSTANCE_ID);
        if (container) {
            auto taskExecutor = container->GetTaskExecutor();
            if (taskExecutor) {
                instance->Initialize(taskExecutor);
            }
        }
    }
    return instance;
}

ComponentTestManagerImpl::ComponentTestManagerImpl()
{
    initialized_ = false;
}

void ComponentTestManagerImpl::Initialize(RefPtr<TaskExecutor> taskExecutor)
{
    idleWatcher_ = AceType::MakeRefPtr<IdleWatcher>(taskExecutor);
    testTaskScheduler_.Initialize(idleWatcher_, taskExecutor);
    testResultRecorder_.Initialize(testConfig.GetOut());
    initialized_ = true;
}

void ComponentTestManagerImpl::Destroy()
{
    testTaskScheduler_.Destroy();
    idleWatcher_->Destroy();
}

void ComponentTestManagerImpl::PostUITask(
    std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data, uint32_t delay)
{
    return testTaskScheduler_.PushTask(std::move(task), std::move(onFinish), TaskExecutor::TaskType::UI, data, delay);
}

void ComponentTestManagerImpl::PostJSTask(
    std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data, uint32_t delay)
{
    return testTaskScheduler_.PushTask(std::move(task), std::move(onFinish), TaskExecutor::TaskType::JS, data, delay);
}

void ComponentTestManagerImpl::SetTestCaseAttribute(TestCaseAttribute attribute)
{
    testResultRecorder_.SetTestCaseAttribute(attribute);
}

void ComponentTestManagerImpl::Record(std::string info, std::string position, Result result)
{
    testResultRecorder_.Record(info, position, result);
}

void ComponentTestManagerImpl::Finish()
{
    testResultRecorder_.Finish();
}

void ComponentTestManagerImpl::ClaimLongOperation()
{
    idleWatcher_->ClaimLongOperation();
}

void ComponentTestManagerImpl::LongOperationComplete()
{
    idleWatcher_->LongOperationComplete();
}

void ComponentTestManagerImpl::RequestContinuousIdleStatusNotification(IdleNotifycallback&& notifycallback)
{
    idleWatcher_->RequestContinuousIdleStatusNotification(std::move(notifycallback));
}

} // namespace OHOS::Ace::ComponentTest
