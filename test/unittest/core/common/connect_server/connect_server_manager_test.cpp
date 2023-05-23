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
#include "gmock/gmock.h"

#define private public
#define protected public
#include "base/log/log.h"
#include "core/common/ace_application_info.h"
#include "core/common/connect_server_manager.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
// namespace
class ConnectServerManagerTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        AceApplicationInfo::GetInstance().isDebugVersion_ = true;
    }
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ConnectServerManagerTest001
 * @tc.desc: Verify the static Get fuction of ConnectServerManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ConnectServerManagerTest, ConnectServerManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Try ConnectServerManager::Get().
     */
    ConnectServerManager& instance = ConnectServerManager::Get();

    /**
     * @tc.steps: step2. Try ConnectServerManager::Get() again.
     * @tc.expected: step2. The instance address is consistent.
     */
    ConnectServerManager& instance2 = ConnectServerManager::Get();
    EXPECT_EQ(&instance, &instance2);
}

/**
 * @tc.name: ConnectServerManagerTest002
 * @tc.desc: Verify the AddInstance and RemoveInstance Interface of ConnectServerManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ConnectServerManagerTest, ConnectServerManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetInstance first.
     * @tc.expected: step1. The instance internal handlerConnectServerSo_ Property is not nullptr.
     */
    ConnectServerManager& instance = ConnectServerManager::Get();
    EXPECT_NE(instance.handlerConnectServerSo_, nullptr);

    /**
     * @tc.steps: step2. Call AddInstance only id without name.
     * @tc.expected: step2. The instance internal instanceMap_ include instance with default name .
     */
    instance.AddInstance(1000);
    EXPECT_EQ(instance.instanceMap_[1000], "PandaDebugger");
    /**
     * @tc.steps: step3. Call AddInstance id and name.
     * @tc.expected: step3. The instance internal instanceMap_ include instance with name .
     */
    instance.AddInstance(1001, "Chinese", "TestDebugger");
    EXPECT_EQ(instance.instanceMap_[1001], "TestDebugger");

    /**
     * @tc.steps: step4. Call RemoveInstance.
     * @tc.expected: step4. instanceMap_ Removed this instance .
     */
    instance.RemoveInstance(1000);
    EXPECT_TRUE(instance.instanceMap_[1000].empty());
    instance.RemoveInstance(1001);
    EXPECT_TRUE(instance.instanceMap_[1001].empty());
}
/**
 * @tc.name: ConnectServerManagerTest003
 * @tc.desc: Verify the SetLayoutInspectorCallback and GetLayoutInspectorCallback Interface of ConnectServerManager work
 * correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ConnectServerManagerTest, ConnectServerManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build CallBack first..
     */
    std::function<void(int32_t)> createLayoutInfo_ = [](int32_t x) {};
    std::function<void(int32_t)> setStatus_ = [](int32_t x) {};

    /**
     * @tc.steps: step2. Call GetInstance .
     */
    ConnectServerManager& instance = ConnectServerManager::Get();

    /**
     * @tc.steps: step3. Call SetLayoutInspectorCallback .
     * @tc.expected: step3. The Callback inside the instance is not nullptr .
     */
    instance.SetLayoutInspectorCallback(createLayoutInfo_, setStatus_);
    EXPECT_NE(&instance.createLayoutInfo_, nullptr);
    EXPECT_NE(&instance.setStatus_, nullptr);

    /**
     * @tc.steps: step4. Call GetLayoutInspectorCallback .
     * @tc.expected: step4. The LayoutInspectorCallback obtained is not nullptr.
     */
    std::function<void(int32_t)> innerLayoutInspectorCallback = instance.GetLayoutInspectorCallback();
    EXPECT_NE(&innerLayoutInspectorCallback, nullptr);
}
} // namespace OHOS::Ace