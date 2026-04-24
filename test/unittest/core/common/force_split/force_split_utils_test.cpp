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

#include "base/json/json_util.h"
#include "core/common/force_split/force_split_utils.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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
 * @tc.name: ParseSystemForceSplitConfig001
 * @tc.desc: Branch: if (!configJson) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig001, TestSize.Level1)
{
    std::string configStr = "";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig002
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig002, TestSize.Level1)
{
    std::string configStr = "[ ]";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig003
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig003, TestSize.Level1)
{
    std::string configStr = "{ \"enableHook\": true }";
    NG::ForceSplitConfig config;
    config.isArkUIHookEnabled = false;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
}

/**
 * @tc.name: ParseSystemForceSplitConfig004
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig004, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": [] }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig005
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_ID_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig005, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"id\": true } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationId.has_value());

    configStr = "{ \"navigationOptions\": { \"id\": \"\" } }";
    ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.navigationId.has_value());

    configStr = "{ \"navigationOptions\": { \"id\": \"myNavId\" } }";
    ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationId.has_value());
    EXPECT_EQ(config.navigationId.value(), "myNavId");
}

/**
 * @tc.name: ParseSystemForceSplitConfig006
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DEPTH_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig006, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"depth\": true } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationDepth.has_value());

    configStr = "{ \"navigationOptions\": { \"depth\": 3 } }";
    ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDepth.has_value());
    EXPECT_EQ(config.navigationDepth.value(), 3);
}

/**
 * @tc.name: ParseSystemForceSplitConfig007
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DISABLE_PLACEHOLDER_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig007, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"disablePlaceholder\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);

    configStr = "{ \"navigationOptions\": { \"disablePlaceholder\": true } }";
    config.navigationDisablePlaceholder = false;
    ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDisablePlaceholder);
}

/**
 * @tc.name: ParseSystemForceSplitConfig008
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig008, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"disableDivider\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);

    configStr = "{ \"navigationOptions\": { \"disableDivider\": true } }";
    config.navigationDisableDivider = false;
    ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.navigationDisableDivider);
}
/**
 * @tc.name: ParseSystemForceSplitConfig009
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(NAVIGATION_OPTIONS_DISABLE_DIVIDER_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig009, TestSize.Level1)
{
    std::string configStr = "{ \"navigationOptions\": { \"disableDivider\": true } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0010
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig010, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"#FFFF0000\", \"dark\": \"#FF00FF00\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::FromString("#FFFF0000"));
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::FromString("#FF00FF00"));
}

/**
 * @tc.name: ParseSystemForceSplitConfig011
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig011, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": {} }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.splitDividerColorLight.has_value());
    EXPECT_FALSE(config.splitDividerColorDark.has_value());
}

/**
 * @tc.name: ParseSystemForceSplitConfig012
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig012, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"#FFFF0000\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    EXPECT_FALSE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::FromString("#FFFF0000"));
}

/**
 * @tc.name: ParseSystemForceSplitConfig013
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig013, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"dark\": \"#FF00FF00\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::FromString("#FF00FF00"));
}

/**
 * @tc.name: ParseSystemForceSplitConfig014
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig014, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"ABCD\", \"dark\": \"ABCD\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::BLACK);
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::BLACK);
}

/**
 * @tc.name: ParseSystemForceSplitConfig015
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig015, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": 1, \"dark\": 2 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.splitDividerColorLight.has_value());
    EXPECT_FALSE(config.splitDividerColorDark.has_value());
}

/**
 * @tc.name: ParseSystemForceSplitConfig0016
 * @tc.desc: Branch: if (!configJson) { => false
 *                   if (!configJson->IsObject()) { => false
 *                   if (!configJson->Contains(NAVIGATION_OPTIONS_KEY)) { => false
 *                   if (!navOptions || !navOptions->IsObject()) { => false
 *                   if (navOptions->Contains(SPLIT_DIVIDER_COLOR)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig016, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"#FFFF0000\", \"dark\": \"#FF00FF00\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::FromString("#FFFF0000"));
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::FromString("#FF00FF00"));
}

/**
 * @tc.name: ParseSystemForceSplitConfig0017
 * @tc.desc: Branch: Parse wideSplit ratio parameter
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0017, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0018
 * @tc.desc: Branch: Parse squareSplit ratio parameter
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0018, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0019
 * @tc.desc: Branch: Parse both wideSplit and squareSplit ratio parameters
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0019, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"2 | 1\" }, \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 1.0f / 3.0f);
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0020
 * @tc.desc: Branch: wideSplit ratio with invalid format (missing separator)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0020, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"12\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0021
 * @tc.desc: Branch: wideSplit ratio with invalid value (zero)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0021, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"0 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0022
 * @tc.desc: Branch: wideSplit ratio with invalid value (negative)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0022, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"-1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0023
 * @tc.desc: Branch: wideSplit ratio clamped to minimum (1/3)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0023, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 100\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0024
 * @tc.desc: Branch: wideSplit ratio clamped to maximum (2/3)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0024, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"100 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 1.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0025
 * @tc.desc: Branch: wideSplit without ratio key (valid)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0025, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": {} }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.wideSplitRatio.has_value());
}

/**
 * @tc.name: ParseSystemForceSplitConfig0026
 * @tc.desc: Branch: wideSplit ratio with non-string type
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0026, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0027
 * @tc.desc: Branch: wideSplit ratio with empty string
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0027, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0028
 * @tc.desc: Branch: wideSplit ratio with only separator
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0028, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \" | \" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0029
 * @tc.desc: Branch: wideSplit ratio with multiple separators
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0029, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2 | 3\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0030
 * @tc.desc: Branch: wideSplit ratio with spaces around numbers
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0030, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"  1   |   2  \" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0031
 * @tc.desc: Branch: squareSplit ratio with invalid format (missing separator)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0031, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"12\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0032
 * @tc.desc: Branch: squareSplit ratio with invalid value (zero)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0032, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"0 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0033
 * @tc.desc: Branch: squareSplit ratio with invalid value (negative)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0033, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"-1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0034
 * @tc.desc: Branch: squareSplit ratio clamped to minimum (1/3)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0034, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"1 | 100\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0035
 * @tc.desc: Branch: squareSplit ratio clamped to maximum (2/3)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0035, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"100 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 1.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0036
 * @tc.desc: Branch: squareSplit without ratio key (valid)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0036, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": {} }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.squareSplitRatio.has_value());
}

/**
 * @tc.name: ParseSystemForceSplitConfig0037
 * @tc.desc: Branch: squareSplit ratio with non-string type
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0037, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0038
 * @tc.desc: Branch: wideSplit with non-object type
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0038, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": \"invalid\" }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0039
 * @tc.desc: Branch: squareSplit with non-object type
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0039, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": \"invalid\" }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0040
 * @tc.desc: Branch: wideSplit ratio at exactly 1/3 boundary
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0040, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"2 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 1.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0041
 * @tc.desc: Branch: wideSplit ratio at exactly 2/3 boundary
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0041, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0042
 * @tc.desc: Branch: wideSplit ratio with ratio just below 1/3 (should clamp)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0042, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"100 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 1.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0043
 * @tc.desc: Branch: wideSplit ratio with ratio just above 2/3 (should clamp)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0043, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 100\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0044
 * @tc.desc: Branch: wideSplit ratio with both values negative
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0044, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"-1 | -1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0045
 * @tc.desc: Branch: wideSplit ratio with one negative and one positive
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0045, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"-1 | 2\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0046
 * @tc.desc: Branch: wideSplit ratio with both values zero
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0046, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"0 | 0\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0047
 * @tc.desc: Branch: wideSplit ratio with large numbers
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0047, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1000000 | 1000000\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseSystemForceSplitConfig0048
 * @tc.desc: Branch: wideSplit ratio with typical ratio 1:1 (0.5)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSystemForceSplitConfig0048, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseSystemForceSplitConfig(configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParsePagePairs001
 * @tc.desc: Branch: ParsePagePairs returns false and keeps old config when pagePairs is not an array.
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParsePagePairs001, TestSize.Level1)
{
    auto pagePairs = JsonUtil::ParseJsonString("{ \"from\": \"home\", \"to\": \"detail\" }");
    ASSERT_NE(pagePairs, nullptr);
    NG::ForceSplitConfig config;
    config.pagePairs["old"].emplace("target");

    auto ret = NG::ForceSplitUtils::ParsePagePairs(pagePairs, config);
    EXPECT_FALSE(ret);
    ASSERT_EQ(config.pagePairs.count("old"), 1);
    EXPECT_EQ(config.pagePairs["old"].count("target"), 1);
}

/**
 * @tc.name: ParsePagePairs002
 * @tc.desc: Branch: ParsePagePairs skips invalid items and handles wildcard pair.
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParsePagePairs002, TestSize.Level1)
{
    auto pagePairs = JsonUtil::ParseJsonString(R"([
        { "from": "home", "to": "detail1" },
        { "from": "home", "to": "detail2" },
        { "from": "cart", "to": "detail3" },
        { "from": "cart", "to": "*" },
        { "from": "cart", "to": "detail4" },
        { "from": "bad", "to": "" },
        { "from": "", "to": "bad" },
        { "from": 123, "to": "bad" },
        { "from": "bad" },
        []
    ])");
    ASSERT_NE(pagePairs, nullptr);
    NG::ForceSplitConfig config;
    config.pagePairs["old"].emplace("target");

    auto ret = NG::ForceSplitUtils::ParsePagePairs(pagePairs, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.pagePairs.count("old"), 0);
    ASSERT_EQ(config.pagePairs.count("home"), 1);
    EXPECT_EQ(config.pagePairs["home"].size(), 2);
    EXPECT_EQ(config.pagePairs["home"].count("detail1"), 1);
    EXPECT_EQ(config.pagePairs["home"].count("detail2"), 1);
    ASSERT_EQ(config.pagePairs.count("cart"), 1);
    EXPECT_TRUE(config.pagePairs["cart"].empty());
    EXPECT_EQ(config.pagePairs.count("bad"), 0);
}

/**
 * @tc.name: ParseTransPages001
 * @tc.desc: Branch: ParseTransPages returns false and keeps old config when transPages is not an array.
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseTransPages001, TestSize.Level1)
{
    auto transPages = JsonUtil::ParseJsonString("{ \"page\": \"dialog\" }");
    ASSERT_NE(transPages, nullptr);
    NG::ForceSplitConfig config;
    config.transPages.emplace("oldDialog");

    auto ret = NG::ForceSplitUtils::ParseTransPages(transPages, config);
    EXPECT_FALSE(ret);
    EXPECT_EQ(config.transPages.count("oldDialog"), 1);
}

/**
 * @tc.name: ParseTransPages002
 * @tc.desc: Branch: ParseTransPages skips invalid or empty items and de-duplicates valid pages.
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseTransPages002, TestSize.Level1)
{
    auto transPages = JsonUtil::ParseJsonString(R"([
        "dialog1",
        "",
        123,
        { "page": "dialog2" },
        "dialog2",
        "dialog1"
    ])");
    ASSERT_NE(transPages, nullptr);
    NG::ForceSplitConfig config;
    config.transPages.emplace("oldDialog");

    auto ret = NG::ForceSplitUtils::ParseTransPages(transPages, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.transPages.count("oldDialog"), 0);
    EXPECT_EQ(config.transPages.size(), 2);
    EXPECT_EQ(config.transPages.count("dialog1"), 1);
    EXPECT_EQ(config.transPages.count("dialog2"), 1);
}

/**
 * @tc.name: ParseAppForceSplitConfig001
 * @tc.desc: Branch: Parse app forceSplit config with wideSplit ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig001, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseAppForceSplitConfig002
 * @tc.desc: Branch: Parse app forceSplit config with squareSplit ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig002, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseAppForceSplitConfig003
 * @tc.desc: Branch: Parse app forceSplit config with both wideSplit and squareSplit
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig003, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"2 | 1\" }, \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 1.0f / 3.0f);
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseAppForceSplitConfig004
 * @tc.desc: Branch: Parse app forceSplit config with invalid wideSplit format
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig004, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"invalid\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig005
 * @tc.desc: Branch: Parse app forceSplit config with invalid squareSplit format
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig005, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"invalid\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig006
 * @tc.desc: Branch: Parse app forceSplit config with empty wideSplit object
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig006, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": {} }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.wideSplitRatio.has_value());
}

/**
 * @tc.name: ParseAppForceSplitConfig007
 * @tc.desc: Branch: Parse app forceSplit config with empty squareSplit object
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig007, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": {} }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.squareSplitRatio.has_value());
}

/**
 * @tc.name: ParseAppForceSplitConfig008
 * @tc.desc: Branch: Parse app forceSplit config with router=true (early return for wideSplit/squareSplit)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig008, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2\" }, \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(true, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
}

/**
 * @tc.name: ParseAppForceSplitConfig009
 * @tc.desc: Branch: Parse app forceSplit config with wideSplit zero value
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig009, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"0 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig010
 * @tc.desc: Branch: Parse app forceSplit config with squareSplit zero value
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig010, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"0 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig011
 * @tc.desc: Branch: Parse app forceSplit config with wideSplit clamped ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig011, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 100\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
}

/**
 * @tc.name: ParseAppForceSplitConfig012
 * @tc.desc: Branch: Parse app forceSplit config with squareSplit clamped ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig012, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"100 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 1.0f / 3.0f);
}

/**
 * @tc.name: ParseAppForceSplitConfig013
 * @tc.desc: Branch: Parse app forceSplit config with wideSplit non-object
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig013, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": \"invalid\" }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig014
 * @tc.desc: Branch: Parse app forceSplit config with squareSplit non-object
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig014, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": \"invalid\" }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig015
 * @tc.desc: Branch: Parse app forceSplit config with wideSplit non-string ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig015, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig016
 * @tc.desc: Branch: Parse app forceSplit config with squareSplit non-string ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig016, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": 123 } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig017
 * @tc.desc: Branch: Parse app forceSplit config with empty string
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig017, TestSize.Level1)
{
    std::string configStr = "";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig018
 * @tc.desc: Branch: Parse app forceSplit config with non-object root
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig018, TestSize.Level1)
{
    std::string configStr = "[1, 2, 3]";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseAppForceSplitConfig019
 * @tc.desc: Branch: Parse app forceSplit config with combined options including wideSplit/squareSplit
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig019, TestSize.Level1)
{
    std::string configStr = R"({
        "homePage": "home",
        "relatedPage": "detail",
        "wideSplit": { "ratio": "1 | 2" },
        "squareSplit": { "ratio": "1 | 1" },
        "splitDividerColor": { "light": "#FFFF0000", "dark": "#FF00FF00" }
    })";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.homePage, "home");
    EXPECT_EQ(config.relatedPage, "detail");
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), 2.0f / 3.0f);
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), 0.5f);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
}

/**
 * @tc.name: ParseAppForceSplitConfig020
 * @tc.desc: Branch: Parse app forceSplit config with negative ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseAppForceSplitConfig020, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"-1 | 1\" } }";
    NG::ForceSplitConfig config;
    auto ret = NG::ForceSplitUtils::ParseAppForceSplitConfig(false, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: LogSystemForceSplitConfig001
 * @tc.desc: Branch: LogSystemForceSplitConfig with wideSplit/squareSplit ratios
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, LogSystemForceSplitConfig001, TestSize.Level1)
{
    NG::ForceSplitConfig config;
    config.homePage = "home";
    config.wideSplitRatio = 0.6f;
    config.squareSplitRatio = 0.55f;
    config.isArkUIHookEnabled = true;
    NG::ForceSplitUtils::LogSystemForceSplitConfig(false, "home", config);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: LogAppForceSplitConfig001
 * @tc.desc: Branch: LogAppForceSplitConfig with wideSplit/squareSplit ratios
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, LogAppForceSplitConfig001, TestSize.Level1)
{
    NG::ForceSplitConfig config;
    config.homePage = "home";
    config.relatedPage = "detail";
    config.wideSplitRatio = 0.6f;
    config.squareSplitRatio = 0.55f;
    config.isArkUIHookEnabled = true;
    NG::ForceSplitUtils::LogAppForceSplitConfig(false, config);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: LogSystemForceSplitConfig002
 * @tc.desc: Branch: LogSystemForceSplitConfig without wideSplit/squareSplit ratios
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, LogSystemForceSplitConfig002, TestSize.Level1)
{
    NG::ForceSplitConfig config;
    config.homePage = "home";
    config.wideSplitRatio = std::nullopt;
    config.squareSplitRatio = std::nullopt;
    NG::ForceSplitUtils::LogSystemForceSplitConfig(false, "home", config);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: LogAppForceSplitConfig002
 * @tc.desc: Branch: LogAppForceSplitConfig without wideSplit/squareSplit ratios
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, LogAppForceSplitConfig002, TestSize.Level1)
{
    NG::ForceSplitConfig config;
    config.homePage = "home";
    config.relatedPage = "detail";
    config.wideSplitRatio = std::nullopt;
    config.squareSplitRatio = std::nullopt;
    NG::ForceSplitUtils::LogAppForceSplitConfig(false, config);
    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace
