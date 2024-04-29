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
#define private public
#include "test/mock/core/common/mock_container.h"
#include "base/utils/system_properties.h"
#include "bridge/common/plugin_adapter/plugin_bridge.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
const std::string INFO_STR_ONE = "{\"brand\":\"test_brand\","
                                 "\"manufacturer\":\"test_manufacturer\","
                                 "\"model\":\"test\","
                                 "\"product\":\"phone 1.0\","
                                 "\"apiVersion\":9,"
                                 "\"releaseType\":\"Beta\","
                                 "\"deviceType\":\"PHONE\","
                                 "\"language\":\"zh-Hans\","
                                 "\"region\":\"CN\","
                                 "\"windowWidth\":100,"
                                 "\"windowHeight\":100,"
                                 "\"screenDensity\":1,"
                                 "\"screenShape\":\"circle\"}";

const std::string INFO_STR_TWO = "{\"brand\":\"test_brand\","
                                 "\"manufacturer\":\"test_manufacturer\","
                                 "\"model\":\"test\","
                                 "\"product\":\"phone 2.0\","
                                 "\"apiVersion\":10,"
                                 "\"releaseType\":\"Beta\","
                                 "\"deviceType\":\"PHONE\","
                                 "\"language\":\"zh-Hans\","
                                 "\"region\":\"CN\","
                                 "\"windowWidth\":50,"
                                 "\"windowHeight\":50,"
                                 "\"screenDensity\":1,"
                                 "\"screenShape\":\"rect\"}";

const std::string INFO_STR_DEFAULT = "{\"language\":\"zh-Hans\","
                                     "\"region\":\"CN\","
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
     * @tc.steps: step1. Use default device information.
     * @tc.expected: step1. Get the device information as expected.
     */
    PluginBridge pluginBridge;
    auto infoPair = pluginBridge.GetDeviceInfo();
    EXPECT_EQ(infoPair.first, INFO_STR_DEFAULT);
    EXPECT_EQ(infoPair.second, false);
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
    systemPro.InitDeviceInfo(100, 100, 1, 1.0, true);
    systemPro.brand_ = "test_brand";
    systemPro.manufacturer_ = "test_manufacturer";
    systemPro.product_ = "phone 1.0";
    systemPro.apiVersion_ = "9";
    systemPro.releaseType_ = "Beta";
    systemPro.model_ = "test";
    systemPro.paramDeviceType_ = "PHONE";
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
 * @tc.name: GetDevInfoTest003
 * @tc.desc: Initialize device information
 * @tc.type: FUNC
 */
HWTEST_F(PluginAdapterTest, GetDevInfoTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize device information.
     * @tc.expected: step1. Get the device information as expected.
     */
    SystemProperties systemPro;
    systemPro.InitDeviceInfo(100, 100, 1, 1.0, false);
    systemPro.brand_ = "test_brand";
    systemPro.manufacturer_ = "test_manufacturer";
    systemPro.product_ = "phone 2.0";
    systemPro.apiVersion_ = "10";
    systemPro.releaseType_ = "Beta";
    systemPro.model_ = "test";
    systemPro.paramDeviceType_ = "PHONE";
    PluginBridge pluginBridge;
    auto container = AceType::MakeRefPtr<MockContainer>();
    AceEngine::Get().AddContainer(-1, container);
    auto infoPair = pluginBridge.GetDeviceInfo();
    EXPECT_EQ(infoPair.first, INFO_STR_TWO);
    EXPECT_EQ(infoPair.second, true);
}

HWTEST_F(PluginAdapterTest, GetMemConfigProperty001, TestSize.Level1)
{
    OHOS::system::SetParameter("persist.ark.mem_config_property", "jsHeap500");
    std::string ret = SystemProperties::GetMemConfigProperty("persist.ark.mem_config_property", "");
    EXPECT_EQ(ret, "jsHeap500");
}
} // namespace OHOS::Ace::Framework
