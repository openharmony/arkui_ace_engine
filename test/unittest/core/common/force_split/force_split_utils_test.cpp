/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define protected public

#include "core/common/force_split/force_split_utils.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ForceSplitUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ForceSplitUtilsTest::SetUpTestSuite()
{
    NG::MockPipelineContext::SetUp();
}

void ForceSplitUtilsTest::TearDownTestSuite()
{
    NG::MockPipelineContext::TearDown();
}

/**
 * @tc.name: ParseForceSplitConfig001
 * @tc.desc: Branch: if (!configJson) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig001, TestSize.Level1)
{
    std::string configStr = "";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitConfig002
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig002, TestSize.Level1)
{
    std::string configStr = "[ ]";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitConfig003
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig003, TestSize.Level1)
{
    std::string configStr = "{ \"enableHook\": true }";
    NG::ForceSplitConfig config;
    config.isArkUIHookEnabled = false;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
}

/**
 * @tc.name: ParseForceSplitConfig004
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig004, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": [] }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitConfig005
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_ID_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig005, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"id\": true } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationId.has_value());

    configStr = "{ \"navigationOptions\": { \"id\": \"\" } }";
    ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.navigationId.has_value());

    configStr = "{ \"navigationOptions\": { \"id\": \"myNavId\" } }";
    ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationId.has_value());
    EXPECT_EQ(config.navigationId.value(), "myNavId");
}

/**
 * @tc.name: ParseForceSplitConfig006
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DEPTH_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig006, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"depth\": true } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationDepth.has_value());

    configStr = "{ \"navigationOptions\": { \"depth\": 3 } }";
    ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDepth.has_value());
    EXPECT_EQ(config.navigationDepth.value(), 3);
}

/**
 * @tc.name: ParseForceSplitConfig007
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig007, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"disablePlaceholder\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);

    configStr = "{ \"navigationOptions\": { \"disablePlaceholder\": true } }";
    config.navigationDisablePlaceholder = false;
    ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDisablePlaceholder);
}

/**
 * @tc.name: ParseForceSplitConfig008
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitConfig008, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"disableDivider\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);

    configStr = "{ \"navigationOptions\": { \"disableDivider\": true } }";
    config.navigationDisableDivider = false;
    ret = NG::ForceSplitUtils::ParseForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDisableDivider);
}
} // namespace OHOS::Ace
