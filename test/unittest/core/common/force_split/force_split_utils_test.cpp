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
namespace {
constexpr bool ROUTER_SPLIT = true;
constexpr bool NAVIGATION_SPLIT = false;
constexpr int32_t TEST_NAVIGATION_DEPTH = 3;
constexpr float EXPECTED_HALF_RATIO = 0.5f;
constexpr float EXPECTED_ONE_THIRD_RATIO = 1.0f / 3.0f;
constexpr float EXPECTED_TWO_THIRDS_RATIO = 2.0f / 3.0f;
constexpr char WIDE_SPLIT_KEY[] = "wideSplit";
constexpr char SQUARE_SPLIT_KEY[] = "squareSplit";
} // namespace

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
 * @tc.name: ParseForceSplitParam001
 * @tc.desc: Branch: if (configJsonStr.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam001, TestSize.Level1)
{
    std::string configStr = "";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    config.homePage = "HomePage";
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.homePage, "HomePage");
}

/**
 * @tc.name: ParseForceSplitParam002
 * @tc.desc: Branch: if (!configJson) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam002, TestSize.Level1)
{
    std::string configStr = "{";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam003
 * @tc.desc: Branch: if (!configJson->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam003, TestSize.Level1)
{
    std::string configStr = "[ ]";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam004
 * @tc.desc: Branch: config.isArkUIHookEnabled = configJson->GetBool(ENABLE_HOOK_KEY, false)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam004, TestSize.Level1)
{
    std::string configStr = "{ \"enableReducedContainerSize\": true }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    config.isArkUIHookEnabled = false;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
}

/**
 * @tc.name: ParseForceSplitParam005
 * @tc.desc: Branch: if (configJson->Contains(HOME_PAGE_KEY)) { => true
 *                   if (!homePageJson->IsString()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam005, TestSize.Level1)
{
    std::string configStr = "{ \"homePage\": 1 }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam006
 * @tc.desc: Branch: if (configJson->Contains(RELATED_PAGE_KEY)) { => true
 *                   if (!relatedPageJson->IsString()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam006, TestSize.Level1)
{
    std::string configStr = "{ \"relatedPage\": 1 }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam007
 * @tc.desc: Branch: if (isRouterSplit) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam007, TestSize.Level1)
{
    std::string configStr =
        "{ \"enableReducedContainerSize\": true, \"homePage\": \"HomePage\", \"relatedPage\": \"RelatedPage\", "
        "\"dialogSupportSplit\": false, \"homeNavigationId\": true, \"homeNavigationDepth\": \"3\", "
        "\"navigationDisablePlaceholder\": true, \"navigationDisableDivider\": true }";
    bool isRouterSplit = ROUTER_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
    EXPECT_EQ(config.homePage, "HomePage");
    EXPECT_EQ(config.relatedPage, "RelatedPage");
    EXPECT_FALSE(config.dialogSupportSplit);
    EXPECT_FALSE(config.navigationId.has_value());
    EXPECT_FALSE(config.navigationDepth.has_value());
    EXPECT_FALSE(config.navigationDisablePlaceholder);
    EXPECT_FALSE(config.navigationDisableDivider);
}

/**
 * @tc.name: ParseForceSplitParam008
 * @tc.desc: Branch: if (configJson->Contains(FULL_SCREEN_PAGES_KEY)) { => true
 *                   if (!fullScreenPages || !fullScreenPages->IsArray()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam008, TestSize.Level1)
{
    std::string configStr = "{ \"fullScreenPages\": {} }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam009
 * @tc.desc: Branch: ParseFullScreenPages ignores invalid items and empty strings
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam009, TestSize.Level1)
{
    std::string configStr = "{ \"fullScreenPages\": [\"DetailPage\", 1, \"\"] }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.fullScreenPages.size(), 1);
    EXPECT_TRUE(config.fullScreenPages.find("DetailPage") != config.fullScreenPages.end());
}

/**
 * @tc.name: ParseForceSplitParam010
 * @tc.desc: Branch: if (configJson->Contains(SPLIT_DIVIDER_COLOR)) { => true
 *                   if (!splitDividerColor || !splitDividerColor->IsObject()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam010, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": [] }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam011
 * @tc.desc: Branch: ParseSplitDividerColor with valid light and dark values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam011, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"#FFFF0000\", \"dark\": \"#FF00FF00\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::FromString("#FFFF0000"));
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::FromString("#FF00FF00"));
}

/**
 * @tc.name: ParseForceSplitParam012
 * @tc.desc: Branch: ParseSplitDividerColor uses Color::BLACK for invalid color strings
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam012, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": \"ABCD\", \"dark\": \"ABCD\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.splitDividerColorLight.has_value());
    ASSERT_TRUE(config.splitDividerColorDark.has_value());
    EXPECT_EQ(config.splitDividerColorLight.value(), Color::BLACK);
    EXPECT_EQ(config.splitDividerColorDark.value(), Color::BLACK);
}

/**
 * @tc.name: ParseForceSplitParam013
 * @tc.desc: Branch: if (!lightColorValue->IsString()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam013, TestSize.Level1)
{
    std::string configStr = "{ \"splitDividerColor\": { \"light\": 1, \"dark\": 2 } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.splitDividerColorLight.has_value());
    EXPECT_FALSE(config.splitDividerColorDark.has_value());
}

/**
 * @tc.name: ParseForceSplitParam014
 * @tc.desc: Branch: Parse wideSplit ratio parameter
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam014, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"1 | 2\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), EXPECTED_TWO_THIRDS_RATIO);
}

/**
 * @tc.name: ParseForceSplitParam015
 * @tc.desc: Branch: Parse squareSplit ratio parameter
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam015, TestSize.Level1)
{
    std::string configStr = "{ \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), EXPECTED_HALF_RATIO);
}

/**
 * @tc.name: ParseForceSplitParam016
 * @tc.desc: Branch: ParseSplitParam with clamp range [1/3, 2/3]
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam016, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"100 | 1\" },"
                            "\"squareSplit\": { \"ratio\": \"1 | 100\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    ASSERT_TRUE(config.wideSplitRatio.has_value());
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.wideSplitRatio.value(), EXPECTED_ONE_THIRD_RATIO);
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), EXPECTED_TWO_THIRDS_RATIO);
}

/**
 * @tc.name: ParseForceSplitParam017
 * @tc.desc: Branch: if (pos == std::string::npos) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam017, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"12\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam018
 * @tc.desc: Branch: if (primaryValue <= 0 || secondaryValue <= 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam018, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": { \"ratio\": \"0 | 1\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam019
 * @tc.desc: Branch: if (!split->Contains(RATIO_KEY)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam019, TestSize.Level1)
{
    std::string configStr = "{ \"wideSplit\": {} }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(config.wideSplitRatio.has_value());
}

/**
 * @tc.name: ParseForceSplitParam020
 * @tc.desc: Branch: if (!modeJson || !modeJson->IsNumber()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam020, TestSize.Level1)
{
    std::string configStr = "{ \"mode\": \"1\" }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam021
 * @tc.desc: Branch: if (modeValue != DISPLACE_BEHAVIOR_MODE && modeValue != NAVIGATION_BEHAVIOR_MODE) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam021, TestSize.Level1)
{
    std::string configStr = "{ \"mode\": 2 }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam022
 * @tc.desc: Branch: if (!pagePairs || !pagePairs->IsArray()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam022, TestSize.Level1)
{
    std::string configStr = "{ \"pagePairs\": {} }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam023
 * @tc.desc: Branch: ParsePagePairs handles wildcard, invalid items and navigation mode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam023, TestSize.Level1)
{
    std::string configStr =
        "{ \"mode\": 1, \"pagePairs\": ["
        "{ \"from\": \"PageA\", \"to\": \"PageB\" },"
        "{ \"from\": \"PageA\", \"to\": \"*\" },"
        "{ \"from\": \"PageA\", \"to\": \"PageC\" },"
        "{ \"from\": \"\", \"to\": \"ignored\" },"
        "{ \"from\": \"PageD\" },"
        "1 ], \"transPages\": [\"TransitionPage\", \"\", 1] }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.behaviorMode, NG::ForceSplitBehaviorMode::NAVIGATION);
    EXPECT_TRUE(config.pagePairs.find("PageA") != config.pagePairs.end());
    EXPECT_TRUE(config.pagePairs["PageA"].empty());
    EXPECT_EQ(config.pagePairs.size(), 1);
    EXPECT_TRUE(config.transPages.empty());
}

/**
 * @tc.name: ParseForceSplitParam024
 * @tc.desc: Branch: if (!transPages || !transPages->IsArray()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam024, TestSize.Level1)
{
    std::string configStr = "{ \"mode\": 0, \"transPages\": {} }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam025
 * @tc.desc: Branch: if (configJson->Contains(HOME_NAVIGATION_ID_KEY)) { => true
 *                   if (!idJson->IsString()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam025, TestSize.Level1)
{
    std::string configStr = "{ \"homeNavigationId\": true }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationId.has_value());
}

/**
 * @tc.name: ParseForceSplitParam026
 * @tc.desc: Branch: if (configJson->Contains(HOME_NAVIGATION_DEPTH_KEY)) { => true
 *                   if (!depthJson->IsNumber()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam026, TestSize.Level1)
{
    std::string configStr = "{ \"homeNavigationDepth\": \"3\" }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(config.navigationDepth.has_value());
}

/**
 * @tc.name: ParseForceSplitParam027
 * @tc.desc: Branch: if (!disablePlaceholderJson->IsBool()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam027, TestSize.Level1)
{
    std::string configStr = "{ \"navigationDisablePlaceholder\": 1 }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam028
 * @tc.desc: Branch: if (!disableDividerJson->IsBool()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam028, TestSize.Level1)
{
    std::string configStr = "{ \"navigationDisableDivider\": 1 }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseForceSplitParam029
 * @tc.desc: Branch: non-router config parses navigation fields successfully
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam029, TestSize.Level1)
{
    std::string configStr =
        "{ \"enableReducedContainerSize\": true, \"homePage\": \"HomePage\", \"relatedPage\": \"RelatedPage\", "
        "\"homeNavigationId\": \"mainNav\", \"homeNavigationDepth\": 3, "
        "\"navigationDisablePlaceholder\": true, \"navigationDisableDivider\": true }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.isArkUIHookEnabled);
    EXPECT_EQ(config.homePage, "HomePage");
    EXPECT_EQ(config.relatedPage, "RelatedPage");
    ASSERT_TRUE(config.navigationId.has_value());
    ASSERT_TRUE(config.navigationDepth.has_value());
    EXPECT_EQ(config.navigationId.value(), "mainNav");
    EXPECT_EQ(config.navigationDepth.value(), TEST_NAVIGATION_DEPTH);
    EXPECT_TRUE(config.navigationDisablePlaceholder);
    EXPECT_TRUE(config.navigationDisableDivider);
}

/**
 * @tc.name: ParseForceSplitParam030
 * @tc.desc: Branch: empty string values do not overwrite existing fields
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseForceSplitParam030, TestSize.Level1)
{
    std::string configStr =
        "{ \"homePage\": \"\", \"relatedPage\": \"\", \"homeNavigationId\": \"\", \"wideSplit\": {}, "
        "\"dialogSupportSplit\": true }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    config.homePage = "HomePage";
    config.relatedPage = "RelatedPage";
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(config.homePage, "HomePage");
    EXPECT_EQ(config.relatedPage, "RelatedPage");
    EXPECT_FALSE(config.navigationId.has_value());
    EXPECT_FALSE(config.wideSplitRatio.has_value());
    EXPECT_TRUE(config.dialogSupportSplit);
}

/**
 * @tc.name: ParseSplitParam_IsDraggable001
 * @tc.desc: Branch: if (!split || !split->IsObject()) => true
 *           ParseSplitParam with null json object returns false
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable001, TestSize.Level1)
{
    std::unique_ptr<JsonValue> split = nullptr;
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(splitRatio.has_value());
}

/**
 * @tc.name: ParseSplitParam_IsDraggable002
 * @tc.desc: Branch: if (!split || !split->IsObject()) => false
 *                   if (!split->Contains(RATIO_KEY) && !split->Contains(IS_DRAGGABLE_KEY)) => true
 *           ParseSplitParam with empty object returns true without setting ratio or draggable
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable002, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(splitRatio.has_value());
    EXPECT_FALSE(isDraggable);
}

/**
 * @tc.name: ParseSplitParam_IsDraggable003
 * @tc.desc: Branch: if (!split->Contains(RATIO_KEY) && !split->Contains(IS_DRAGGABLE_KEY)) => false
 *                   if (split->Contains(IS_DRAGGABLE_KEY)) => true
 *                   isDraggable = split->GetBool(IS_DRAGGABLE_KEY, false) => true
 *           ParseSplitParam with isDraggable=true returns true without parsing ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable003, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{\"isDraggable\": true}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(isDraggable);
    EXPECT_FALSE(splitRatio.has_value());
}

/**
 * @tc.name: ParseSplitParam_IsDraggable004
 * @tc.desc: Branch: if (split->Contains(IS_DRAGGABLE_KEY)) => true
 *                   isDraggable = split->GetBool(IS_DRAGGABLE_KEY, false) => false
 *                   if (isDraggable) => false
 *                   continue to parse ratio
 *           ParseSplitParam with isDraggable=false continues to parse ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable004, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{\"isDraggable\": false, \"ratio\": \"1 | 2\"}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(isDraggable);
    ASSERT_TRUE(splitRatio.has_value());
    EXPECT_FLOAT_EQ(splitRatio.value(), EXPECTED_TWO_THIRDS_RATIO);
}

/**
 * @tc.name: ParseSplitParam_IsDraggable005
 * @tc.desc: Branch: isDraggable=false, has both ratio and isDraggable keys
 *                   isDraggable key value is false, ratio is valid
 *           ParseSplitParam parses ratio when isDraggable key exists but value is false
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable005, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{\"isDraggable\": false, \"ratio\": \"1 | 1\"}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, SQUARE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(isDraggable);
    ASSERT_TRUE(splitRatio.has_value());
    EXPECT_FLOAT_EQ(splitRatio.value(), EXPECTED_HALF_RATIO);
}

/**
 * @tc.name: ParseSplitParam_IsDraggable006
 * @tc.desc: Branch: has ratio but no isDraggable key
 *                   ParseSplitParam parses ratio normally
 *           ParseSplitParam parses ratio when only ratio key exists
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable006, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{\"ratio\": \"2 | 1\"}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_FALSE(isDraggable);
    ASSERT_TRUE(splitRatio.has_value());
    EXPECT_FLOAT_EQ(splitRatio.value(), EXPECTED_ONE_THIRD_RATIO);
}

/**
 * @tc.name: ParseSplitParam_IsDraggable007
 * @tc.desc: Branch: has isDraggable=true and invalid ratio
 *                   ParseSplitParam returns true without checking ratio validity
 *           ParseSplitParam skips ratio validation when isDraggable is true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable007, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("{\"isDraggable\": true, \"ratio\": \"invalid_ratio\"}");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(isDraggable);
    EXPECT_FALSE(splitRatio.has_value());
}

/**
 * @tc.name: ParseSplitParam_IsDraggable008
 * @tc.desc: Branch: json object is array (not object)
 *                   ParseSplitParam returns false
 *           ParseSplitParam with invalid json type returns false
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseSplitParam_IsDraggable008, TestSize.Level1)
{
    auto split = JsonUtil::ParseJsonData("[\"item1\", \"item2\"]");
    ASSERT_NE(split, nullptr);
    std::optional<float> splitRatio;
    bool isDraggable = false;
    auto ret = NG::ForceSplitUtils::ParseSplitParam(split, WIDE_SPLIT_KEY, splitRatio, isDraggable);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ParseCommonParam_IsDraggable001
 * @tc.desc: Branch: wideSplit has isDraggable=true, squareSplit has isDraggable=false
 *           ParseCommonConfig correctly sets both isDraggable flags
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitUtilsTest, ParseCommonParam_IsDraggable001, TestSize.Level1)
{
    std::string configStr =
        "{ \"wideSplit\": { \"isDraggable\": true }, \"squareSplit\": { \"ratio\": \"1 | 1\" } }";
    bool isRouterSplit = NAVIGATION_SPLIT;
    NG::ForceSplitParam config;
    auto ret = NG::ForceSplitUtils::ParseForceSplitParam(isRouterSplit, configStr, config);
    EXPECT_TRUE(ret);
    EXPECT_TRUE(config.wideSplitIsDraggable);
    EXPECT_FALSE(config.squareSplitIsDraggable);
    ASSERT_TRUE(config.squareSplitRatio.has_value());
    EXPECT_FLOAT_EQ(config.squareSplitRatio.value(), EXPECTED_HALF_RATIO);
}
} // namespace OHOS::Ace
