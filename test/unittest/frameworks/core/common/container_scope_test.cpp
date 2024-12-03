/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "vector"

#include "core/common/container_scope.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int32_t INSTANCE_ID_PLATFORM = -2;
constexpr int32_t INSTANCE_ID_UNDEFINED = -1;
constexpr int32_t TEST_INSTANCE_ID_CONTAINER = 100000;
constexpr int32_t TEST_INSTANCE_ID_SUB_CONTAINER = 1000000;
const std::vector<int32_t> TEST_CONTAINERS = { 100000, 100001, 100002, 100003 };
} // namespace

class ContainerScopeTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        ContainerScope::UpdateCurrent(INSTANCE_ID_PLATFORM);
    }
    static void TearDownTestSuite()
    {
        ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
        ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
        ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ContainerScopeTest001
 * @tc.desc: CurrentId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId from initial env
     * @tc.expected: CurrentId equals the value in initial env
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_PLATFORM);

    /**
     * @tc.steps: step2. Update currentId and get it
     * @tc.expected: CurrentId equals updated value
     */
    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_CONTAINER);

    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_SUB_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step3. restore currentId to default value
     */
    ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest002
 * @tc.desc: Constructor & Destructor
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Call constructor of ContainerScope
     */
    ContainerScope scope(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Get currentId
     * @tc.expected: CurrentId equals value in constructor
     */
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. Call destructor of ContainerScope
     */
    scope.~ContainerScope();

    /**
     * @tc.steps: step5. Get currentId
     * @tc.expected: CurrentId equals default value
     */
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest003
 * @tc.desc: Test for containerSet
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId
     * @tc.expected: CurrentId equals default value
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Add containers to containerSet
     * @tc.expected: ContainerCount equals length of TEST_CONTAINERS
     */
    for (auto& container : TEST_CONTAINERS) {
        ContainerScope::Add(container);
    }
    EXPECT_EQ(ContainerScope::ContainerCount(), static_cast<int32_t>(TEST_CONTAINERS.size()));

    /**
     * @tc.steps: step3. Get defaultId
     * @tc.expected: DefaultId equals last member in containerSet
     */
    EXPECT_EQ(ContainerScope::DefaultId(), *TEST_CONTAINERS.rbegin());

    /**
     * @tc.steps: step4. Remove containers from containerSet
     * @tc.expected: ContainerCount equals 0
     */
    for (auto& container : TEST_CONTAINERS) {
        ContainerScope::Remove(container);
    }
    EXPECT_EQ(ContainerScope::ContainerCount(), 0);

    /**
     * @tc.steps: step5. Get currentId
     * @tc.expected: CurrentId equals default value
     */
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest004
 * @tc.desc: DefaultId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get defaultId while containerCount equals 0
     * @tc.expected: DefaultId equals INSTANCE_ID_UNDEFINED
     */
    EXPECT_EQ(ContainerScope::DefaultId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Add containers to containerSet then get defaultId
     * @tc.expected: DefaultId equals last member of TEST_CONTAINERS
     */
    for (auto& container : TEST_CONTAINERS) {
        ContainerScope::Add(container);
    }
    EXPECT_EQ(ContainerScope::DefaultId(), *TEST_CONTAINERS.rbegin());

    /**
     * @tc.steps: step3. Remove containers from containerSet
     */
    for (auto& container : TEST_CONTAINERS) {
        ContainerScope::Remove(container);
    }
}

/**
 * @tc.name: ContainerScopeTest005
 * @tc.desc: SingletonId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get singletonId while containerCount equals 0
     * @tc.expected: SingletonId equals INSTANCE_ID_UNDEFINED
     */
    EXPECT_EQ(ContainerScope::SingletonId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Add two containers to containerSet
     * @tc.expected: SingletonId equals INSTANCE_ID_UNDEFINED
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::SingletonId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step3. Remove a container from containerSet
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step4. Check singletonId
     * @tc.expected: SingletonId equals the only value in containerSet
     */
    EXPECT_EQ(ContainerScope::SingletonId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step5. Clear containerSet
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::ContainerCount(), 0);
}

/**
 * @tc.name: ContainerScopeTest006
 * @tc.desc: RecentActiveId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Update recent active id
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Check recent active id
     * @tc.expected: RecentActiveId equals updated value
     */
    EXPECT_EQ(ContainerScope::RecentActiveId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step1. Clear recent active id
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest007
 * @tc.desc: RecentForegroundId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Update foreground active id
     */
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Check recent foreground id
     * @tc.expected: RecentActiveId equals updated value
     */
    EXPECT_EQ(ContainerScope::RecentForegroundId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step1. Clear recent foreground id
     */
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest008
 * @tc.desc: CurrentIdWithReason
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Update current id
     * @tc.expected: reason is SCOPE
     */
    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::SCOPE);

    /**
     * @tc.steps: step2. Update current id to default
     * @tc.expected: reason is UNDEFINED
     */
    ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::UNDEFINED);

    /**
     * @tc.steps: step3. Add one container to containerSet
     * @tc.expected: reason is SINGLETON
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::SINGLETON);

    /**
     * @tc.steps: step4. Add another container to containerSet
     * @tc.expected: reason is DEFAULT
     */
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::DEFAULT);

    /**
     * @tc.steps: step4. Update recent active id
     * @tc.expected: reason is ACTIVE
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::ACTIVE);

    /**
     * @tc.steps: step5. Clear recent active id then Update recent foreground id
     * @tc.expected: reason is FOREGROUND
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::CurrentIdWithReason().second, InstanceIdGenReason::FOREGROUND);

    /**
     * @tc.steps: step5. Clear set value
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest009
 * @tc.desc: RemoveAndCheck
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add containers to containerSet and update active/foreground id
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Check active/foreground/singleton id and containerCount
     */
    EXPECT_EQ(ContainerScope::ContainerCount(), 1);
    EXPECT_EQ(ContainerScope::SingletonId(), TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentActiveId(), TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Call RemoveAndCheck and check step2 again
     */
    ContainerScope::RemoveAndCheck(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::ContainerCount(), 0);
    EXPECT_EQ(ContainerScope::SingletonId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::RecentActiveId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), INSTANCE_ID_UNDEFINED);
}

} // namespace OHOS::Ace
