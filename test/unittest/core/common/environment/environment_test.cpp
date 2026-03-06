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
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
// namespace
class EnvironmentTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() override
    {
        EnvironmentProxy::GetInstance()->SetDelegate(nullptr);
    }
    void TearDown() override
    {
        EnvironmentProxy::GetInstance()->SetDelegate(nullptr);
    }
};

namespace {
class TestEnvironment final : public Environment {
    DECLARE_ACE_TYPE(TestEnvironment, Environment);

public:
    TestEnvironment(const RefPtr<TaskExecutor>& taskExecutor, std::string accessibilityEnabled)
        : Environment(taskExecutor), accessibilityEnabled_(std::move(accessibilityEnabled))
    {}

    std::string GetAccessibilityEnabled() override
    {
        return accessibilityEnabled_;
    }

private:
    std::string accessibilityEnabled_;
};

class SpyEnvironmentProxyImpl final : public EnvironmentInterface {
public:
    explicit SpyEnvironmentProxyImpl(std::string accessibilityEnabled)
        : accessibilityEnabled_(std::move(accessibilityEnabled))
    {}
    ~SpyEnvironmentProxyImpl() override = default;

    RefPtr<Environment> GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        callCount_++;
        lastTaskExecutor_ = taskExecutor;
        return AceType::MakeRefPtr<TestEnvironment>(taskExecutor, accessibilityEnabled_);
    }

    int32_t GetCallCount() const
    {
        return callCount_;
    }

    RefPtr<TaskExecutor> GetLastTaskExecutor() const
    {
        return lastTaskExecutor_;
    }

private:
    std::string accessibilityEnabled_;
    mutable int32_t callCount_ = 0;
    mutable RefPtr<TaskExecutor> lastTaskExecutor_;
};

class DtorCountingEnvironmentProxyImpl final : public EnvironmentInterface {
public:
    DtorCountingEnvironmentProxyImpl(int32_t* dtorCount, std::string accessibilityEnabled)
        : dtorCount_(dtorCount), accessibilityEnabled_(std::move(accessibilityEnabled))
    {}

    ~DtorCountingEnvironmentProxyImpl() override
    {
        if (dtorCount_) {
            (*dtorCount_)++;
        }
    }

    RefPtr<Environment> GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        return AceType::MakeRefPtr<TestEnvironment>(taskExecutor, accessibilityEnabled_);
    }

private:
    int32_t* dtorCount_ = nullptr;
    std::string accessibilityEnabled_;
};

class NullEnvironmentProxyImpl final : public EnvironmentInterface {
public:
    ~NullEnvironmentProxyImpl() override = default;

    RefPtr<Environment> GetEnvironment(const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        (void)taskExecutor;
        return nullptr;
    }
};
} // namespace

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

/**
 * @tc.name: CastToEnvironmentTest004
 * @tc.desc: Test delegate receives task executor.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set delegate with spy implementation.
     */
    auto spyDelegate = std::make_unique<SpyEnvironmentProxyImpl>("enabled");
    auto* spyDelegateRaw = spyDelegate.get();
    EnvironmentProxy::GetInstance()->SetDelegate(std::move(spyDelegate));

    /**
     * @tc.steps: step2. Call GetEnvironment with non-null TaskExecutor.
     * @tc.expected: step2. Delegate is called once and receives same executor.
     */
    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    auto environment = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);
    EXPECT_NE(environment, nullptr);
    EXPECT_EQ(environment->GetAccessibilityEnabled(), "enabled");
    EXPECT_EQ(spyDelegateRaw->GetCallCount(), 1);
    EXPECT_EQ(spyDelegateRaw->GetLastTaskExecutor(), taskExecutor);
}

/**
 * @tc.name: CastToEnvironmentTest005
 * @tc.desc: Test delegate replacement and destruction.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest005, TestSize.Level1)
{
    int32_t dtorCount = 0;
    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);

    /**
     * @tc.steps: step1. Set first delegate.
     * @tc.expected: step1. Return value matches first delegate.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(
        std::make_unique<DtorCountingEnvironmentProxyImpl>(&dtorCount, "first"));
    auto env1 = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);
    EXPECT_NE(env1, nullptr);
    EXPECT_EQ(env1->GetAccessibilityEnabled(), "first");
    EXPECT_EQ(dtorCount, 0);

    /**
     * @tc.steps: step2. Replace delegate.
     * @tc.expected: step2. Old delegate is destroyed and new delegate takes effect.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(
        std::make_unique<DtorCountingEnvironmentProxyImpl>(&dtorCount, "second"));
    EXPECT_EQ(dtorCount, 1);
    auto env2 = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);
    EXPECT_NE(env2, nullptr);
    EXPECT_EQ(env2->GetAccessibilityEnabled(), "second");

    /**
     * @tc.steps: step3. Clear delegate.
     * @tc.expected: step3. Delegate is destroyed.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(nullptr);
    EXPECT_EQ(dtorCount, 2);
}

/**
 * @tc.name: CastToEnvironmentTest006
 * @tc.desc: Test delegate returning nullptr environment.
 * @tc.type: FUNC
 */
HWTEST_F(EnvironmentTest, CastToEnvironmentTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set delegate that returns nullptr.
     * @tc.expected: step1. GetEnvironment returns nullptr.
     */
    EnvironmentProxy::GetInstance()->SetDelegate(std::make_unique<NullEnvironmentProxyImpl>());
    RefPtr<TaskExecutor> taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    auto environment = EnvironmentProxy::GetInstance()->GetEnvironment(taskExecutor);
    EXPECT_EQ(environment, nullptr);
}
} // namespace OHOS::Ace
