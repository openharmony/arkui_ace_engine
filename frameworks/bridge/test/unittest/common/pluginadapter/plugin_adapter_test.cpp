/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/test/unittest/geometry/mock_container.h"
#include "bridge/common/plugin_adapter/plugin_bridge.h"
#include "core/common/container.h"
#include "core/common/ace_engine.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
const std::string INFO_STR_ONE = "{\"brand\":\"default\","
                                 "\"manufacturer\":\"default\","
                                 "\"model\":\"ohos\","
                                 "\"product\":\"OpenHarmony 3.2\","
                                 "\"apiVersion\":9,"
                                 "\"releaseType\":\"Canary1\","
                                 "\"deviceType\":\"default\","
                                 "\"language\":\"zh-Hans\","
                                 "\"region\":\"CN\","
                                 "\"windowWidth\":100,"
                                 "\"windowHeight\":100,"
                                 "\"screenDensity\":1,"
                                 "\"screenShape\":\"circle\"}";
const std::string INFO_STR_TWO = "{\"brand\":\"default\","
                                 "\"manufacturer\":\"default\","
                                 "\"model\":\"ohos\","
                                 "\"product\":\"OpenHarmony 3.2\","
                                 "\"apiVersion\":9,"
                                 "\"releaseType\":\"Canary1\","
                                 "\"deviceType\":\"default\","
                                 "\"language\":\"zh-Hans\","
                                 "\"region\":\"CN\","
                                 "\"windowWidth\":50,"
                                 "\"windowHeight\":50,"
                                 "\"screenDensity\":1,"
                                 "\"screenShape\":\"rect\"}";
} // namespace

class PluginAdapterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void PluginAdapterTest::SetUpTestCase() {}
void PluginAdapterTest::TearDownTestCase() {}
void PluginAdapterTest::SetUp() {}
void PluginAdapterTest::TearDown() {}

/**
 * @tc.name: GetDevInfoTest001
 * @tc.desc: Initialize device information
 * @tc.type: FUNC
 */
HWTEST_F(PluginAdapterTest, GetDevInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize device information.
     * @tc.expected: step1. Get the device information as expected.
     */
    SystemProperties systemPro;
    systemPro.InitDeviceInfo(100, 100, 1, 1.0, true);
    PluginBridge pluginBridge;
    auto container = AceType::MakeRefPtr<MockContainer>();
    EXPECT_CALL(*container, GetViewWidth()).Times(2).WillOnce(Return(100)).WillOnce(Return(50));
    EXPECT_CALL(*container, GetViewHeight()).Times(2).WillOnce(Return(100)).WillOnce(Return(50));
    AceEngine::Get().AddContainer(-1, container);
    auto infoPair = pluginBridge.GetDeviceInfo();
    EXPECT_EQ(infoPair.first, INFO_STR_ONE);
    EXPECT_EQ(infoPair.second, true);
}

/**
 * @tc.name: GetDevInfoTest002
 * @tc.desc: Initialize device information
 * @tc.type: FUNC
 */
HWTEST_F(PluginAdapterTest, GetDevInfoTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize device information.
     * @tc.expected: step1. Get the device information as expected.
     */
    SystemProperties systemPro;
    systemPro.InitDeviceInfo(100, 100, 1, 1.0, false);
    PluginBridge pluginBridge;
    auto container = AceType::MakeRefPtr<MockContainer>();
    AceEngine::Get().AddContainer(-1, container);
    auto infoPair = pluginBridge.GetDeviceInfo();
    EXPECT_EQ(infoPair.first, INFO_STR_TWO);
    EXPECT_EQ(infoPair.second, true);
}
} // namespace OHOS::Ace::Framework
