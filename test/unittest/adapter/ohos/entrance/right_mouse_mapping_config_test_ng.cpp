/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "base/utils/feature_manager.h"
#include "core/event/event_info_convertor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RightMouseMappingConfigTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        FeatureManager::GetInstance().ClearFeatureParamForTest();
    }

    static void TearDownTestSuite()
    {
        FeatureManager::GetInstance().ClearFeatureParamForTest();
    }

    void SetUp() override
    {
        FeatureManager::GetInstance().ClearFeatureParamForTest();
    }

    void TearDown() override
    {
        FeatureManager::GetInstance().ClearFeatureParamForTest();
    }
};

/**
 * @tc.name: GetRightMouse2LongPressConfig001
 * @tc.desc: Valid config with component whitelist returns MATCHED and parses the whitelist.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig001, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput","TextArea"]})",
        FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 2U);
    EXPECT_EQ(components[0], "TextInput");
    EXPECT_EQ(components[1], "TextArea");
}

/**
 * @tc.name: GetRightMouse2LongPressConfig002
 * @tc.desc: "All" wildcard returns MATCHED and clears the component list.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig002, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":true,"needTransferComponent":["All","TextInput"]})",
        FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::MATCHED);
    EXPECT_TRUE(enabled);
    EXPECT_TRUE(components.empty());
}

/**
 * @tc.name: GetRightMouse2LongPressConfig003
 * @tc.desc: rightMouse2LongPress=false returns UNMATCHED.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig003, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":false,"needTransferComponent":["TextInput"]})",
        FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

/**
 * @tc.name: GetRightMouse2LongPressConfig004
 * @tc.desc: Enabled but empty/missing needTransferComponent array returns UNMATCHED.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig004, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":true})", FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::UNMATCHED);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

/**
 * @tc.name: GetRightMouse2LongPressConfig005
 * @tc.desc: Invalid JSON string returns NOT_FOUND.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig005, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        "invalid json {{{", FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::NOT_FOUND);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

/**
 * @tc.name: GetRightMouse2LongPressConfig006
 * @tc.desc: Missing config key returns NOT_FOUND.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, GetRightMouse2LongPressConfig006, TestSize.Level1)
{
    bool enabled = false;
    std::vector<std::string> components;
    auto ret = EventInfoConvertor::GetRightMouse2LongPressConfig(enabled, components);
    EXPECT_EQ(ret, EventInfoConvertor::Mouse2TouchEventModeResult::NOT_FOUND);
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

/**
 * @tc.name: IsRightMouseMappingEnabled001
 * @tc.desc: Valid enabled config returns true.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, IsRightMouseMappingEnabled001, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":true,"needTransferComponent":["TextInput"]})",
        FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    EXPECT_TRUE(EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components));
    EXPECT_TRUE(enabled);
    ASSERT_EQ(components.size(), 1U);
    EXPECT_EQ(components[0], "TextInput");
}

/**
 * @tc.name: IsRightMouseMappingEnabled002
 * @tc.desc: Disabled config returns false.
 * @tc.type: FUNC
 */
HWTEST_F(RightMouseMappingConfigTestNg, IsRightMouseMappingEnabled002, TestSize.Level1)
{
    FeatureManager::GetInstance().SetFeatureParamForTest("contextMenuOptions",
        R"({"rightMouse2LongPress":false,"needTransferComponent":["TextInput"]})",
        FeatureManager::SUCCESS);
    bool enabled = false;
    std::vector<std::string> components;
    EXPECT_FALSE(EventInfoConvertor::IsRightMouseMappingEnabled(enabled, components));
    EXPECT_FALSE(enabled);
    EXPECT_TRUE(components.empty());
}

} // namespace OHOS::Ace::NG
