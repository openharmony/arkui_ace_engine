/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "unordered_map"

#include "core/common/container_scope.h"

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
#include "base/utils/container_scope/container_scope_diagnostics.h"
#endif

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr int32_t INSTANCE_ID_PLATFORM = -2;
constexpr int32_t INSTANCE_ID_UNDEFINED = -1;
constexpr int32_t TEST_INSTANCE_ID_CONTAINER = 100000;
constexpr int32_t TEST_INSTANCE_ID_SUB_CONTAINER = 1000000;
const std::vector<int32_t> TEST_CONTAINERS = { 100000, 100001, 100002, 100003 };
std::unordered_map<int32_t, bool> g_mockThreadCheckResult;

void MockThreadCheckResult(int32_t id, bool canRunOnCurrentThread)
{
    g_mockThreadCheckResult[id] = canRunOnCurrentThread;
}

void ClearMockThreadCheckResult()
{
    g_mockThreadCheckResult.clear();
}
} // namespace

class Container {
public:
    static bool CheckRunOnThreadByThreadId(int32_t currentId, bool defaultRes);
};

bool Container::CheckRunOnThreadByThreadId(int32_t currentId, bool defaultRes)
{
    auto iter = g_mockThreadCheckResult.find(currentId);
    if (iter != g_mockThreadCheckResult.end()) {
        return iter->second;
    }
    return defaultRes;
}

class ContainerScopeTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        ContainerScope::RegisterThreadCheckFunc(&Container::CheckRunOnThreadByThreadId);
        ContainerScope::UpdateCurrent(INSTANCE_ID_PLATFORM);
    }
    static void TearDownTestSuite()
    {
        ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
        ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
        ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    }
    void SetUp() override
    {
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
        ContainerScope::EnableTracking(true);
        ContainerScope::ClearHistory();
#endif
        ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
    }
    void TearDown() override
    {
#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
        ContainerScope::EnableTracking(false);
        ContainerScope::ClearHistory();
#endif
        ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
        ContainerScope::UpdateLocalCurrent(INSTANCE_ID_UNDEFINED);
        ContainerScope::ResetIsolatedThread();
    }
};

/**
 * @tc.name: ContainerScopeTest001
 * @tc.desc: CurrentId
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest001, TestSize.Level1)
{
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);

    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_CONTAINER);

    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_SUB_CONTAINER);
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_SUB_CONTAINER);

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

    {
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
    }
    /**
     * @tc.steps: step4. Call destructor of ContainerScope. Get currentId
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

/**
 * @tc.name: ContainerScopeTest010
 * @tc.desc: GetAllUIContexts
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get GetAllUIContexts while containerCount equals 0
     * @tc.expected: GetAllUIContexts size equals 0
     */
    EXPECT_EQ(ContainerScope::GetAllUIContexts().size(), 0);

    /**
     * @tc.steps: step2. Add two containers to containerSet
     * @tc.expected: GetAllUIContexts item equals inserted items
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    auto allUIContexts = ContainerScope::GetAllUIContexts();
    auto index = 0;
    for (auto item : allUIContexts) {
        if (index == 0) {
            EXPECT_EQ(item, TEST_INSTANCE_ID_CONTAINER);
        } else {
            EXPECT_EQ(item, TEST_INSTANCE_ID_SUB_CONTAINER);
        }
        index++;
    }
    /**
     * @tc.steps: step3. Clear containerSet
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::GetAllUIContexts().size(), 0);
}

/**
 * @tc.name: ContainerScopeTest011
 * @tc.desc: ReasonToDescription
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test SCOPE reason description
     * @tc.expected: Returns correct description for SCOPE
     */
    EXPECT_EQ(
        ContainerScope::ReasonToDescription(InstanceIdGenReason::SCOPE), "The instance is determined by the caller");

    /**
     * @tc.steps: step2. Test ACTIVE reason description
     * @tc.expected: Returns correct description for ACTIVE
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::ACTIVE),
        "No specific instance was specified, so the most recently active instance was retrieved");

    /**
     * @tc.steps: step3. Test DEFAULT reason description
     * @tc.expected: Returns correct description for DEFAULT
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::DEFAULT),
        "No specific instance was specified, using default");

    /**
     * @tc.steps: step4. Test SINGLETON reason description
     * @tc.expected: Returns correct description for SINGLETON
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::SINGLETON),
        "No specific instance was specified, return the only remaining instance");

    /**
     * @tc.steps: step5. Test FOREGROUND reason description
     * @tc.expected: Returns correct description for FOREGROUND
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::FOREGROUND),
        "No specific instance was specified, return the foreground instance");

    /**
     * @tc.steps: step6. Test UNDEFINED reason description
     * @tc.expected: Returns correct description for UNDEFINED
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::UNDEFINED), "No valid instance exists");

    /**
     * @tc.steps: step7. Test LOCAL reason description
     * @tc.expected: Returns correct description for LOCAL
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(InstanceIdGenReason::LOCAL),
        "No specific instance was specified, return the local thread instance");

    /**
     * @tc.steps: step8. Test invalid enum value (out of range)
     * @tc.expected: Returns "Unknown reason"
     */
    EXPECT_EQ(ContainerScope::ReasonToDescription(static_cast<InstanceIdGenReason>(999)), "Unknown reason");
}

/**
 * @tc.name: ContainerScopeTest012
 * @tc.desc: SafelyId - when container count is 0
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear container set
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Get SafelyId when containerCount equals 0
     * @tc.expected: SafelyId equals INSTANCE_ID_UNDEFINED
     */
    EXPECT_EQ(ContainerScope::SafelyId(), INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest013
 * @tc.desc: SafelyId - when container count is 1 (singleton)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add one container to containerSet
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Get SafelyId when containerCount equals 1
     * @tc.expected: SafelyId equals the singleton container id
     */
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Clear container set
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
}

/**
 * @tc.name: ContainerScopeTest014
 * @tc.desc: SafelyId - when container count > 1 (multiple containers)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple containers to containerSet
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Get SafelyId when no recent active/foreground
     * @tc.expected: SafelyId equals DefaultId (last container in set)
     */
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step3. Update recent active id and get SafelyId
     * @tc.expected: SafelyId equals recent active id
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. Clear recent active, update foreground and get SafelyId
     * @tc.expected: SafelyId equals recent foreground id
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step5. Clear container set
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest015
 * @tc.desc: ContainerScope constructor with enable parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Call constructor with enable = true
     */
    ContainerScope scope(TEST_INSTANCE_ID_CONTAINER, true);

    /**
     * @tc.steps: step3. Get currentId
     * @tc.expected: CurrentId equals value in constructor
     */
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. Destructor is called automatically
     * @tc.expected: CurrentId equals default value
     */
}

/**
 * @tc.name: ContainerScopeTest016
 * @tc.desc: ContainerScope constructor with enable = false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get currentId
     */
    int32_t scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Call constructor with enable = false
     */
    ContainerScope scope(TEST_INSTANCE_ID_CONTAINER, false);

    /**
     * @tc.steps: step3. Get currentId
     * @tc.expected: CurrentId still equals INSTANCE_ID_UNDEFINED (unchanged)
     */
    scopeId = ContainerScope::CurrentId();
    EXPECT_EQ(scopeId, INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest017
 * @tc.desc: SafelyId matches Container::SafelyId logic
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up: 2 containers, recent active set
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Compare SafelyId with CurrentId when recent active is set
     * @tc.expected: SafelyId should prioritize recent active
     */
    EXPECT_EQ(ContainerScope::SafelyId(), ContainerScope::RecentActiveId());
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Clear recent active, set recent foreground
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step4. Compare SafelyId with CurrentId when recent foreground is set
     * @tc.expected: SafelyId should prioritize recent foreground
     */
    EXPECT_EQ(ContainerScope::SafelyId(), ContainerScope::RecentForegroundId());
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step5. Clear all
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING

/**
 * @tc.desc: PushCurrent and PopCurrent when tracking disabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest030, TestSize.Level1)
{
    ContainerScope::EnableTracking(false);
    EXPECT_FALSE(ContainerScope::IsTrackingEnabled());

    uint64_t pushUid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 100,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    EXPECT_EQ(pushUid, 0);
    EXPECT_EQ(ContainerScope::CurrentId(), TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::GetStackHistory().size(), 0);
    EXPECT_EQ(ContainerScope::GetActiveFrames().size(), 0);

    ContainerScope::PopCurrent(0, INSTANCE_ID_UNDEFINED, "test.cpp", 200,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    EXPECT_EQ(ContainerScope::CurrentId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::GetStackHistory().size(), 0);
}

/**
 * @tc.name: ContainerScopeTest031
 * @tc.desc: PushCurrent first frame has parentUid=0 (root)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest031, TestSize.Level1)
{
    uint64_t uid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 300,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    EXPECT_NE(uid, 0);
    EXPECT_EQ(ContainerScope::CurrentId(), TEST_INSTANCE_ID_CONTAINER);

    auto activeFrames = ContainerScope::GetActiveFrames();
    EXPECT_EQ(activeFrames.size(), 1);
    EXPECT_EQ(activeFrames[0].uid, uid);
    EXPECT_EQ(activeFrames[0].parentUid, 0);
    EXPECT_EQ(activeFrames[0].newValue, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ((activeFrames[0].anomalies & FrameAnomaly::UNPAIRED_PUSH), 0u);

    ContainerScope::PopCurrent(uid, INSTANCE_ID_UNDEFINED, "test.cpp", 400,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
}

/**
 * @tc.name: ContainerScopeTest032
 * @tc.desc: PushCurrent nested frames have correct parentUid chain
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest032, TestSize.Level1)
{
    uint64_t uid1 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 500,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    uint64_t uid2 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_SUB_CONTAINER, "test.cpp", 600,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto activeFrames = ContainerScope::GetActiveFrames();
    EXPECT_EQ(activeFrames.size(), 2);
    EXPECT_EQ(activeFrames[0].uid, uid1);
    EXPECT_EQ(activeFrames[0].parentUid, 0);
    EXPECT_EQ(activeFrames[1].uid, uid2);
    EXPECT_EQ(activeFrames[1].parentUid, uid1);

    ContainerScope::PopCurrent(uid2, INSTANCE_ID_UNDEFINED, "test.cpp", 700,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    ContainerScope::PopCurrent(uid1, INSTANCE_ID_UNDEFINED, "test.cpp", 800,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
}

/**
 * @tc.name: ContainerScopeTest033
 * @tc.desc: PushCurrent with CONTAINER_INDIRECT marks UNPAIRED_PUSH anomaly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest033, TestSize.Level1)
{
    uint64_t uid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 900,
        static_cast<int32_t>(CurrentIdSourceType::CONTAINER_INDIRECT));

    EXPECT_NE(uid, 0);

    auto activeFrames = ContainerScope::GetActiveFrames();
    EXPECT_EQ(activeFrames.size(), 1);
    EXPECT_NE((activeFrames[0].anomalies & FrameAnomaly::UNPAIRED_PUSH), 0u);
    EXPECT_EQ(activeFrames[0].anomalyDetailKind, AnomalyDetailKind::CONTAINER_INIT_NO_POP);

    ContainerScope::PopCurrent(uid, INSTANCE_ID_UNDEFINED, "test.cpp", 1000,
        static_cast<int32_t>(CurrentIdSourceType::CONTAINER_INDIRECT));
}

/**
 * @tc.name: ContainerScopeTest034
 * @tc.desc: PopCurrent with uid=0 triggers StackUnderflow when activeOrder empty
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest034, TestSize.Level1)
{
    ContainerScope::PopCurrent(0, INSTANCE_ID_UNDEFINED, "test.cpp", 1100,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto history = ContainerScope::GetStackHistory();
    EXPECT_EQ(history.size(), 1);

    const auto& frame = history.back();
    EXPECT_NE((frame.anomalies & FrameAnomaly::STACK_UNDERFLOW), 0u);
    EXPECT_EQ(frame.anomalyDetailKind, AnomalyDetailKind::POP_UID_NO_MATCHING_PUSH);
    EXPECT_EQ(frame.uid, 0);
}

/**
 * @tc.name: ContainerScopeTest035
 * @tc.desc: PopCurrent with uid not found triggers StackUnderflow when activeOrder not empty
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest035, TestSize.Level1)
{
    uint64_t uid1 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 1200,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    ContainerScope::PopCurrent(99999, INSTANCE_ID_UNDEFINED, "test.cpp", 1300,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto history = ContainerScope::GetStackHistory();
    bool foundUnderflow = false;
    for (const auto& f : history) {
        if (f.uid == 99999) {
            EXPECT_NE((f.anomalies & FrameAnomaly::STACK_UNDERFLOW), 0u);
            EXPECT_EQ(f.anomalyDetailKind, AnomalyDetailKind::POP_UID_NO_MATCHING_PUSH);
            foundUnderflow = true;
        }
    }
    EXPECT_TRUE(foundUnderflow);

    ContainerScope::PopCurrent(uid1, INSTANCE_ID_UNDEFINED, "test.cpp", 1400,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
}

/**
 * @tc.name: ContainerScopeTest036
 * @tc.desc: PopCurrent normal match no anomaly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest036, TestSize.Level1)
{
    ContainerScope::UpdateCurrent(100);

    uint64_t uid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 1500,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto activeFrames = ContainerScope::GetActiveFrames();
    EXPECT_EQ(activeFrames[0].oldValue, 100);

    ContainerScope::PopCurrent(uid, 100, "test.cpp", 1600,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto history = ContainerScope::GetStackHistory();
    EXPECT_EQ(history.size(), 1);

    const auto& frame = history.back();
    EXPECT_EQ(frame.uid, uid);
    EXPECT_EQ((frame.anomalies & FrameAnomaly::STACK_UNDERFLOW), 0u);
    EXPECT_EQ((frame.anomalies & FrameAnomaly::OUT_OF_ORDER_POP), 0u);
    EXPECT_EQ((frame.anomalies & FrameAnomaly::VALUE_MISMATCH), 0u);

    EXPECT_EQ(ContainerScope::GetActiveFrames().size(), 0);
    EXPECT_TRUE(ContainerScope::IsStackBalanced());
}

/**
 * @tc.name: ContainerScopeTest037
 * @tc.desc: PopCurrent out of order triggers OUT_OF_ORDER_POP
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest037, TestSize.Level1)
{
    uint64_t uid1 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 1700,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    uint64_t uid2 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_SUB_CONTAINER, "test.cpp", 1800,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    ContainerScope::PopCurrent(uid1, INSTANCE_ID_UNDEFINED, "test.cpp", 1900,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto history = ContainerScope::GetStackHistory();
    bool foundOutOfOrder = false;
    for (const auto& f : history) {
        if (f.uid == uid1) {
            EXPECT_NE((f.anomalies & FrameAnomaly::OUT_OF_ORDER_POP), 0u);
            EXPECT_EQ(f.anomalyDetailKind, AnomalyDetailKind::OUT_OF_ORDER_POP_DYNAMIC);
            EXPECT_GE(f.skippedCount, 1u);
            EXPECT_EQ(f.expectedTopUid, uid2);
            foundOutOfOrder = true;
        }
    }
    EXPECT_TRUE(foundOutOfOrder);

    ContainerScope::PopCurrent(uid2, INSTANCE_ID_UNDEFINED, "test.cpp", 2000,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
}

/**
 * @tc.name: ContainerScopeTest038
 * @tc.desc: PopCurrent with restoreId mismatch triggers VALUE_MISMATCH
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest038, TestSize.Level1)
{
    ContainerScope::UpdateCurrent(100);

    uint64_t uid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 2100,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    ContainerScope::PopCurrent(uid, 300, "test.cpp", 2200,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    auto history = ContainerScope::GetStackHistory();
    EXPECT_EQ(history.size(), 1);

    const auto& frame = history.back();
    EXPECT_NE((frame.anomalies & FrameAnomaly::VALUE_MISMATCH), 0u);
    EXPECT_EQ(frame.anomalyDetailKind, AnomalyDetailKind::POP_VALUE_MISMATCH);
}

/**
 * @tc.name: ContainerScopeTest039
 * @tc.desc: History FIFO eviction for both matched pop and underflow
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest039, TestSize.Level1)
{
    ContainerScope::SetMaxHistorySize(1);

    uint64_t uid1 = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 2300,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    ContainerScope::PopCurrent(uid1, INSTANCE_ID_UNDEFINED, "test.cpp", 2400,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    EXPECT_EQ(ContainerScope::GetStackHistory().size(), 1);
    EXPECT_EQ(ContainerScope::GetStackHistory()[0].uid, uid1);

    ContainerScope::PopCurrent(0, INSTANCE_ID_UNDEFINED, "test.cpp", 2500,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    EXPECT_EQ(ContainerScope::GetStackHistory().size(), 1);
    EXPECT_EQ(ContainerScope::GetStackHistory()[0].uid, 0);

    ContainerScope::SetMaxHistorySize(64);
}

/**
 * @tc.name: ContainerScopeTest040
 * @tc.desc: Constructor (id, fileId, line) and (id, enable, fileId, line) variations
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest040, TestSize.Level1)
{
    auto before = ContainerScope::GetActiveFrames().size();

    {
        ContainerScope scope1(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 2600);
        EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before + 1);
    }
    EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before);
    {
        ContainerScope scope2(TEST_INSTANCE_ID_CONTAINER, true, "test.cpp", 2700);
        EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before + 1);
    }
    EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before);

    {
        ContainerScope scope3(TEST_INSTANCE_ID_CONTAINER, false, "test.cpp", 2800);
        EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before);
    }
    EXPECT_EQ(ContainerScope::GetActiveFrames().size(), before);
}

/**
 * @tc.name: ContainerScopeTest041
 * @tc.desc: ToString for all branches: root/no pop, has pop/multiple anomalies, OUT_OF_ORDER_POP_DYNAMIC
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest041, TestSize.Level1)
{
    CurrentIdStackFrame frame1;
    frame1.uid = 1;
    frame1.parentUid = 0;
    frame1.oldValue = 100;
    frame1.newValue = 200;
    frame1.pushFileId = "push.cpp";
    frame1.pushLine = 100;
    frame1.popFileId = nullptr;
    frame1.anomalies = FrameAnomaly::NONE;
    frame1.anomalyDetailKind = AnomalyDetailKind::NONE;

    std::string str1 = frame1.ToString();
    EXPECT_TRUE(str1.find("uid=1") != std::string::npos);
    EXPECT_TRUE(str1.find("parent=root") != std::string::npos);
    EXPECT_TRUE(str1.find("pop=") == std::string::npos);
    EXPECT_TRUE(str1.find("anomalies=") == std::string::npos);

    CurrentIdStackFrame frame2;
    frame2.uid = 2;
    frame2.parentUid = 1;
    frame2.popFileId = "pop.cpp";
    frame2.popLine = 200;
    frame2.anomalies = FrameAnomaly::UNPAIRED_PUSH | FrameAnomaly::STACK_UNDERFLOW | FrameAnomaly::VALUE_MISMATCH;
    frame2.anomalyDetailKind = AnomalyDetailKind::POP_VALUE_MISMATCH;

    std::string str2 = frame2.ToString();
    EXPECT_TRUE(str2.find("parent=1") != std::string::npos);
    EXPECT_TRUE(str2.find("pop=pop.cpp:200") != std::string::npos);
    EXPECT_TRUE(str2.find("UNPAIRED_PUSH") != std::string::npos);
    EXPECT_TRUE(str2.find("STACK_UNDERFLOW") != std::string::npos);
    EXPECT_TRUE(str2.find("VALUE_MISMATCH") != std::string::npos);
    EXPECT_TRUE(str2.find("POP restore value differs") != std::string::npos);

    CurrentIdStackFrame frame3;
    frame3.uid = 3;
    frame3.anomalies = FrameAnomaly::OUT_OF_ORDER_POP;
    frame3.anomalyDetailKind = AnomalyDetailKind::OUT_OF_ORDER_POP_DYNAMIC;
    frame3.skippedCount = 2;
    frame3.skippedUids[0] = 10;
    frame3.skippedUids[1] = 20;
    frame3.expectedTopUid = 30;

    std::string str3 = frame3.ToString();
    EXPECT_TRUE(str3.find("OUT_OF_ORDER_POP") != std::string::npos);
    EXPECT_TRUE(str3.find("not top") != std::string::npos);
    EXPECT_TRUE(str3.find("expected=30") != std::string::npos);
    EXPECT_TRUE(str3.find("skipped 2 frames") != std::string::npos);
    EXPECT_TRUE(str3.find("[uid=10") != std::string::npos);
    EXPECT_TRUE(str3.find("uid=20") != std::string::npos);
}

/**
 * @tc.name: ContainerScopeTest042
 * @tc.desc: Diagnose with balanced stack and with anomalies
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest042, TestSize.Level1)
{
    ContainerScope::ClearHistory();
    std::string report1 = ContainerScope::Diagnose();
    EXPECT_TRUE(report1.find("Stack balanced: YES") != std::string::npos);
    EXPECT_TRUE(report1.find("STACK_UNDERFLOW:") == std::string::npos);

    uint64_t uid = ContainerScope::PushCurrent(TEST_INSTANCE_ID_CONTAINER, "test.cpp", 2900,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
    ContainerScope::PopCurrent(0, INSTANCE_ID_UNDEFINED, "test.cpp", 3000,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));

    std::string report2 = ContainerScope::Diagnose();
    EXPECT_TRUE(report2.find("Stack balanced: NO") != std::string::npos);
    EXPECT_TRUE(report2.find("STACK_UNDERFLOW:") != std::string::npos);

    ContainerScope::PopCurrent(uid, INSTANCE_ID_UNDEFINED, "test.cpp", 3100,
        static_cast<int32_t>(CurrentIdSourceType::RAII_SCOPE));
}
#endif // ENABLE_CONTAINER_SCOPE_TRACKING

/**
 * @tc.name: ContainerScopeTest018
 * @tc.desc: SafelyId - local fallback and checkThread option
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare ids and thread check result
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateLocalCurrent(TEST_INSTANCE_ID_SUB_CONTAINER);
    MockThreadCheckResult(TEST_INSTANCE_ID_CONTAINER, false);
    MockThreadCheckResult(TEST_INSTANCE_ID_SUB_CONTAINER, true);

    /**
     * @tc.steps: step2. checkThread=true prefers local thread id
     * @tc.expected: SafelyId equals local id
     */
    EXPECT_EQ(ContainerScope::SafelyId(), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step3. checkThread=false ignores local fallback
     * @tc.expected: SafelyId equals active id
     */
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. clear set value
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateLocalCurrent(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ClearMockThreadCheckResult();
}

/**
 * @tc.name: ContainerScopeTest019
 * @tc.desc: CurrentIdWithReason - local fallback and checkThread option
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare ids and thread check result
     */
    ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateLocalCurrent(TEST_INSTANCE_ID_SUB_CONTAINER);
    MockThreadCheckResult(TEST_INSTANCE_ID_CONTAINER, false);
    MockThreadCheckResult(TEST_INSTANCE_ID_SUB_CONTAINER, true);

    /**
     * @tc.steps: step2. checkThread=true returns local fallback with LOCAL reason
     */
    auto currentIdWithReason = ContainerScope::CurrentIdWithReason();
    EXPECT_EQ(currentIdWithReason.first, TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(currentIdWithReason.second, InstanceIdGenReason::LOCAL);

    /**
     * @tc.steps: step3. checkThread=false keeps foreground path and reason
     */
    auto currentIdWithReasonWithoutThreadCheck = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(currentIdWithReasonWithoutThreadCheck.first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(currentIdWithReasonWithoutThreadCheck.second, InstanceIdGenReason::FOREGROUND);

    /**
     * @tc.steps: step4. clear set value
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateLocalCurrent(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    ClearMockThreadCheckResult();
}

/**
 * @tc.name: ContainerScopeTest020
 * @tc.desc: Isolated base query functions (ContainerCount, SingletonId, DefaultId)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Mark isolated, no local containers added
     * @tc.expected: ContainerCount=0, SingletonId=UNDEFINED, DefaultId=UNDEFINED
     */
    ContainerScope::MarkIsolatedThread();
    EXPECT_EQ(ContainerScope::ContainerCount(), 0);
    EXPECT_EQ(ContainerScope::SingletonId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::DefaultId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Add one local container
     * @tc.expected: ContainerCount=1, SingletonId=that ID, DefaultId=that ID
     */
    ContainerScope::AddLocal(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::ContainerCount(), 1);
    EXPECT_EQ(ContainerScope::SingletonId(), TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::DefaultId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Add a second local container
     * @tc.expected: ContainerCount=2, SingletonId=UNDEFINED, DefaultId=last (rbegin)
     */
    ContainerScope::AddLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::ContainerCount(), 2);
    EXPECT_EQ(ContainerScope::SingletonId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::DefaultId(), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step4. Cleanup
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
}

/**
 * @tc.name: ContainerScopeTest021
 * @tc.desc: Isolated RecentActiveId and RecentForegroundId return local values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Setup global recent IDs and mark isolated
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::MarkIsolatedThread();
    ContainerScope::AddLocal(TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step2. RecentActiveId/RecentForegroundId should return local (UNDEFINED), not global
     * @tc.expected: Both UNDEFINED (local default, not the global value)
     */
    EXPECT_EQ(ContainerScope::RecentActiveId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step3. Update via dual-write, verify local is updated
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentActiveId(), TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step4. Cleanup
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest022
 * @tc.desc: Isolated SafelyId full decision chain (empty→singleton→active→foreground→default)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Isolated with empty local set
     * @tc.expected: SafelyId = UNDEFINED
     */
    ContainerScope::MarkIsolatedThread();
    EXPECT_EQ(ContainerScope::SafelyId(false), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step2. Add one local container (singleton)
     * @tc.expected: SafelyId = that ID
     */
    ContainerScope::AddLocal(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. Add second, set local recent active
     * @tc.expected: SafelyId = active ID
     */
    ContainerScope::AddLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. Clear active, set local recent foreground
     * @tc.expected: SafelyId = foreground ID
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step5. Clear both active and foreground
     * @tc.expected: SafelyId = DefaultId (rbegin of local set)
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step6. Cleanup
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
}

/**
 * @tc.name: ContainerScopeTest023
 * @tc.desc: Isolated CurrentIdWithReason full decision chain
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SCOPE - set CurrentId directly
     */
    ContainerScope::MarkIsolatedThread();
    ContainerScope::AddLocal(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateCurrent(TEST_INSTANCE_ID_CONTAINER);
    auto result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(result.second, InstanceIdGenReason::SCOPE);

    /**
     * @tc.steps: step2. SINGLETON - clear CurrentId, only one local container
     */
    ContainerScope::UpdateCurrent(INSTANCE_ID_UNDEFINED);
    result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(result.second, InstanceIdGenReason::SINGLETON);

    /**
     * @tc.steps: step3. ACTIVE - add second container, set local recent active
     */
    ContainerScope::AddLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(result.second, InstanceIdGenReason::ACTIVE);

    /**
     * @tc.steps: step4. FOREGROUND - clear active, set foreground
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_SUB_CONTAINER);
    result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(result.second, InstanceIdGenReason::FOREGROUND);

    /**
     * @tc.steps: step5. DEFAULT - clear both active and foreground
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
    result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(result.second, InstanceIdGenReason::DEFAULT);

    /**
     * @tc.steps: step6. UNDEFINED - remove all local containers
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    result = ContainerScope::CurrentIdWithReason(false);
    EXPECT_EQ(result.first, INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(result.second, InstanceIdGenReason::UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest024
 * @tc.desc: Isolated local lifecycle: AddLocal, RemoveLocal, cache cleanup, and reset
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Setup: add global container for later verification
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Mark isolated, add local containers, set local active/foreground
     */
    ContainerScope::MarkIsolatedThread();
    ContainerScope::AddLocal(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_SUB_CONTAINER);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step3. RemoveLocal clears active/foreground cache for that ID
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_SUB_CONTAINER);

    /**
     * @tc.steps: step4. ResetIsolatedThread restores global path
     * @tc.expected: ContainerCount=1 (global), SafelyId returns global container
     */
    ContainerScope::ResetIsolatedThread();
    EXPECT_EQ(ContainerScope::ContainerCount(), 1);
    EXPECT_EQ(ContainerScope::SafelyId(false), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step5. Cleanup global
     */
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest025
 * @tc.desc: Isolated UpdateRecentActive/Foreground dual-write (global + local)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Mark isolated, add local container
     */
    ContainerScope::MarkIsolatedThread();
    ContainerScope::AddLocal(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. UpdateRecentActive on isolated thread
     * @tc.expected: RecentActiveId returns local value; global also updated
     */
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentActiveId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step3. UpdateRecentForeground on isolated thread
     * @tc.expected: RecentForegroundId returns local value
     */
    ContainerScope::UpdateRecentForeground(TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step4. Verify global was also written
     * RemoveLocal + ResetIsolatedThread to fall back to global path.
     * @tc.expected: Global RecentActiveId and RecentForegroundId were also set
     */
    ContainerScope::RemoveLocal(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::ResetIsolatedThread();
    EXPECT_EQ(ContainerScope::RecentActiveId(), TEST_INSTANCE_ID_CONTAINER);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step5. Cleanup global
     */
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
    ContainerScope::UpdateRecentForeground(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest026
 * @tc.desc: Isolated thread does not return global container IDs
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple global containers
     */
    ContainerScope::Add(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Add(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(TEST_INSTANCE_ID_CONTAINER);

    /**
     * @tc.steps: step2. Mark isolated, add a different local container
     */
    constexpr int32_t LOCAL_ONLY_ID = 200000;
    ContainerScope::MarkIsolatedThread();
    ContainerScope::AddLocal(LOCAL_ONLY_ID);

    /**
     * @tc.steps: step3. All queries return local values, never global
     * @tc.expected: ContainerCount=1, SingletonId=LOCAL_ONLY_ID, SafelyId=LOCAL_ONLY_ID
     */
    EXPECT_EQ(ContainerScope::ContainerCount(), 1);
    EXPECT_EQ(ContainerScope::SingletonId(), LOCAL_ONLY_ID);
    EXPECT_EQ(ContainerScope::SafelyId(false), LOCAL_ONLY_ID);
    EXPECT_EQ(ContainerScope::DefaultId(), LOCAL_ONLY_ID);
    EXPECT_EQ(ContainerScope::RecentActiveId(), INSTANCE_ID_UNDEFINED);
    EXPECT_EQ(ContainerScope::RecentForegroundId(), INSTANCE_ID_UNDEFINED);

    /**
     * @tc.steps: step4. Cleanup
     */
    ContainerScope::RemoveLocal(LOCAL_ONLY_ID);
    ContainerScope::Remove(TEST_INSTANCE_ID_CONTAINER);
    ContainerScope::Remove(TEST_INSTANCE_ID_SUB_CONTAINER);
    ContainerScope::UpdateRecentActive(INSTANCE_ID_UNDEFINED);
}

/**
 * @tc.name: ContainerScopeTest_IsIsolatedThread_Lifecycle001
 * @tc.desc: Test IsIsolatedThread default false, true after mark, false after reset
 * @tc.type: FUNC
 */
HWTEST_F(ContainerScopeTest, ContainerScopeTest_IsIsolatedThread_Lifecycle001, TestSize.Level1)
{
    EXPECT_FALSE(ContainerScope::IsIsolatedThread());

    ContainerScope::MarkIsolatedThread();
    EXPECT_TRUE(ContainerScope::IsIsolatedThread());

    ContainerScope::ResetIsolatedThread();
    EXPECT_FALSE(ContainerScope::IsIsolatedThread());
}
} // namespace OHOS::Ace
