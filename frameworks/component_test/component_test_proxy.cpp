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

#include "component_test/component_test_proxy.h"

#include "component_test/test_config.h"

#include "adapter/preview/entrance/ace_container.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::ComponentTest {

RefPtr<ComponentTestManager> ComponentTestManagerProxy::GetCurrentComponentTestManager()
{
    return ComponentTestManagerImpl::GetInitialized();
}

void ComponentTestManagerProxy::PostUITask(
    std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data, uint32_t delay)
{
    return GetCurrentComponentTestManager()->PostUITask(std::move(task), std::move(onFinish), data, delay);
}

void ComponentTestManagerProxy::PostJSTask(
    std::function<void(void*)>&& task, std::function<void(void*)>&& onFinish, void* data, uint32_t delay)
{
    return GetCurrentComponentTestManager()->PostJSTask(std::move(task), std::move(onFinish), data, delay);
}

void ComponentTestManagerProxy::SetTestCaseAttribute(TestCaseAttribute attribute)
{
    return ComponentTestManagerImpl::Get()->SetTestCaseAttribute(attribute);
}

void ComponentTestManagerProxy::Record(std::string info, std::string position, Result result)
{
    GetCurrentComponentTestManager()->Record(info, position, result);
}

void ComponentTestManagerProxy::Finish()
{
    GetCurrentComponentTestManager()->Finish();
}

void ComponentTestManagerProxy::ClaimLongOperation()
{
    GetCurrentComponentTestManager()->ClaimLongOperation();
}

void ComponentTestManagerProxy::LongOperationComplete()
{
    GetCurrentComponentTestManager()->LongOperationComplete();
}

void ComponentTestManagerProxy::RequestContinuousIdleStatusNotification(IdleNotifycallback&& notifycallback)
{
    GetCurrentComponentTestManager()->RequestContinuousIdleStatusNotification(std::move(notifycallback));
}

std::string ComponentTestManagerProxy::GetTestConfigPage()
{
    return ComponentTestManagerImpl::Get()->testConfig.GetPage();
}

bool ComponentTestManagerProxy::IsComponentTestEnabled()
{
    return ComponentTestManagerImpl::Get()->testConfig.IsComponentTestEnabled();
}
} // namespace OHOS::Ace::ComponentTest
