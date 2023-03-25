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

#include "gtest/gtest.h"
#include "mock_environment.h"

#include "core/common/environment/environment.h"
#include "core/common/environment/environment_interface.h"
#include "core/common/environment/environment_proxy.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
// namespace
class EnvironmentTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CastToEnvironmentTest001
 * @tc.desc: Test cast to environment.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetInstance first.
     * @tc.expected: step1. The return value is not null.
     */
    EnvironmentProxy* firstResult = EnvironmentProxy::GetInstance();
    EXPECT_NE(firstResult, nullptr);
    /**
     * @tc.steps: step2. Call GetInstance second.
     * @tc.expected: step2. The return value is same with first.
     */
    EnvironmentProxy* secondResult = EnvironmentProxy::GetInstance();
    EXPECT_EQ(secondResult, firstResult);
}

/**
 * @tc.name: CastToEnvironmentTest002
 * @tc.desc: Test cast to environment.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input delegate is null.
     * @tc.expected: step1. The return environment is null.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(nullptr);
    RefPtr<TaskExecutor> taskExecutor;
    RefPtr<Environment> environment = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);

    EXPECT_EQ(environment, nullptr);
}

/**
 * @tc.name: CastToEnvironmentTest003
 * @tc.desc: Test cast to environment.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Input delegate is not null.
     * @tc.expected: step1. Return expected results.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(std::make_unique<MockEnvironmentProxyImpl>());
    RefPtr<TaskExecutor> taskExecutor;
    RefPtr<Environment> environment = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);
    EXPECT_NE(environment, nullptr);

    std::string value = environment->GetAccessibilityEnabled();
    EXPECT_EQ(value, RET_TEST);
}
} // namespace OHOS::Ace
