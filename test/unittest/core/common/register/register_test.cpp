/*
# Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#include "gtest/gtest.h"

#include "base/log/log.h"
#include "core/common/register/hdc_connect.h"
#include "core/common/register/hdc_jdwp.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
extern std::unique_ptr<ConnectManagement> g_connectManagement;
class RegisterTest : public testing::Test {};

/**
 * @tc.name: CastToRegisterTest001
 * @tc.desc: Test cast to register.
 * @tc.type: FUNC
 */
HWTEST_F(RegisterTest, CastToRegisterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. stop connect before start.
     * @tc.expected: step1. g_connectManagement is null.
     */
    StopConnect();
    EXPECT_EQ(g_connectManagement, nullptr);
}

/**
 * @tc.name: CastToRegisterTest002
 * @tc.desc: Test cast to register.
 * @tc.type: FUNC
 */
HWTEST_F(RegisterTest, CastToRegisterTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. start connect.
     * @tc.expected: step1. g_connectManagement is not null and the pktName is right.
     */
    StartConnect("test_pkt_name");
    ASSERT_NE(g_connectManagement, nullptr);
    EXPECT_EQ(g_connectManagement->GetPkgName(), "test_pkt_name");

    /**
     * @tc.steps: step2. sleep 3 second.
     */
    sleep(3);

    /**
     # @tc.steps: step3. stop connect.
     * @tc.expected: step3. g_connectManagement is not null
     */
    StopConnect();
    ASSERT_NE(g_connectManagement, nullptr);
}

/**
 * @tc.name: CastToRegisterTest003
 * @tc.desc: Test cast to register.
 * @tc.type: FUNC
 */
HWTEST_F(RegisterTest, CastToRegisterTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. start connect.
     * @tc.expected: step1. g_connectManagement is not null and the pktName is right.
     */
    StartConnect("test_pkt_name");
    ASSERT_NE(g_connectManagement, nullptr);
    EXPECT_EQ(g_connectManagement->GetPkgName(), "test_pkt_name");

    /**
     * @tc.steps: step2. sleep 3 second.
     */
    sleep(3);

    /**
     # @tc.steps: step3. start connect again
     * @tc.expected: step3. start fail and g_connectManagement is not null and the pktName is same with first start.
     */
    StartConnect("test_pkt_name_2");
    ASSERT_NE(g_connectManagement, nullptr);
    EXPECT_EQ(g_connectManagement->GetPkgName(), "test_pkt_name");
}

/**g_threadRunning
 * @tc.name: CastToRegisterTest004
 * @tc.desc: Test cast to HdcJdwpSimulator.
 * @tc.type: FUNC
 */
HWTEST_F(RegisterTest, CastToRegisterTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. new a HdcJdwpSimulator.
     * @tc.steps: step2. Call DisConnect before connect
     # @tc.steps: step3. delete the HdcJdwpSimulator
     * @tc.expected: step2. not effect, not crash
     * @tc.expected: step3. not effect, not crash
     */
    HdcJdwpSimulator* hdcJdwpSimulator = new HdcJdwpSimulator("test_pkt_name");
    hdcJdwpSimulator->Disconnect();
    delete hdcJdwpSimulator;
    hdcJdwpSimulator = nullptr;
    EXPECT_EQ(1, 1);
}

HdcJdwpSimulator* g_hdcJdwpSimulator = nullptr;
bool g_threadRunning = false;
void* HdcConnectRun_Test(void* pkgContent)
{
    g_threadRunning = true;
    std::string pkgName = static_cast<ConnectManagement*>(pkgContent)->GetPkgName();
    g_hdcJdwpSimulator = new (std::nothrow) HdcJdwpSimulator(pkgName);
    if (!g_hdcJdwpSimulator->Connect()) {
        LOGE("Connect fail.");
        g_threadRunning = false;
        return nullptr;
    }
    g_threadRunning = false;
    return nullptr;
}

/**
 * @tc.name: CastToRegisterTest005
 * @tc.desc: Test cast to HdcJdwpSimulator.
 * @tc.type: FUNC
 */
HWTEST_F(RegisterTest, CastToRegisterTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. new a ConnectManagement and start the connect thread
     * @tc.expected: step1. connect ok, the thread is runed.
     */
    pthread_t tid;
    g_connectManagement = std::make_unique<ConnectManagement>();
    g_connectManagement->SetPkgName("test_pkt_name");
    if (pthread_create(&tid, nullptr, &HdcConnectRun_Test, static_cast<void*>(g_connectManagement.get())) != 0) {
        LOGE("pthread_create fail!");
        return;
    }
    sleep(3);
    EXPECT_TRUE(g_threadRunning);

    /**
     * @tc.steps: step2. Call  disconnect and delete the  HdcJdwpSimulator
     * @tc.expected: step2. Disconnect ok, the thread is stopped.
     */
    g_hdcJdwpSimulator->Disconnect();
    delete g_hdcJdwpSimulator;
    g_hdcJdwpSimulator = nullptr;
    sleep(2);
    EXPECT_FALSE(g_threadRunning);
}
} // namespace OHOS::Ace
