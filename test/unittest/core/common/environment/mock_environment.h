/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#ifndef FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_ENVIRONMENT_MOCK_ENVIRONMENT_H
#define FRAMEWORKS_CORE_COMMON_TEST_UNITTEST_ENVIRONMENT_MOCK_ENVIRONMENT_H

#include "core/common/environment/environment.h"
#include "core/common/environment/environment_interface.h"
#include "core/common/environment/environment_proxy.h"

namespace OHOS::Ace {
const std::string RET_TEST = "true";

class MockEnvironmentImpl : public Environment {
public:
    explicit MockEnvironmentImpl(const RefPtr<TaskExecutor>& taskExecutor);
    ~MockEnvironmentImpl() override = default;

    std::string GetAccessibilityEnabled() override;
};

MockEnvironmentImpl::MockEnvironmentImpl(const RefPtr<TaskExecutor>& taskExecutor) : Environment(taskExecutor) {}

std::string MockEnvironmentImpl::GetAccessibilityEnabled()
{
    return  RET_TEST;
}

class MockEnvironmentProxyImpl final : public EnvironmentInterface {
public:
    MockEnvironmentProxyImpl() = default;
    ~MockEnvironmentProxyImpl() override = default;

    RefPtr<Environment> GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const override;

    ACE_DISALLOW_COPY_AND_MOVE(MockEnvironmentProxyImpl);
};

RefPtr<Environment> MockEnvironmentProxyImpl::GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const
{
    return AceType::MakeRefPtr<MockEnvironmentImpl>(taskExecutor);
}
} // namespace OHOS::Ace
#endif