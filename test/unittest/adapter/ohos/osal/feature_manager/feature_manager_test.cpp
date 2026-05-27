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

#include "app_space_comp_config_reader.h"
#include "gtest/gtest.h"
#include "mock_extra_modules_manager.h"

#include "base/utils/feature_manager.h"
#include "core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t ERROR_CODE = -1;
const std::string TEST_BUNDLE_NAME = "com.example.feature";
const std::string OTHER_BUNDLE_NAME = "com.example.other";
const std::string TEST_KEY = "arkui.multi.feature";
const std::string OTHER_KEY = "arkui.multi.other";
const std::string TEST_VALUE = "any string value";
} // namespace

void FeatureManager::ResetForTest()
{
    Init();
}

class FeatureManagerTest : public testing::Test {
public:
    void SetUp() override
    {
        AceApplicationInfo::GetInstance().SetPackageName(TEST_BUNDLE_NAME);
        CompConfigClient::AppSpaceCompConfigReaderMock::Reset();
        MockExtraModulesManager::Reset();
        MockExtraModulesManager::SetAppSpaceCompConfigFuncs(
            &CompConfigClient::AppSpaceCompConfigReader::Init, &CompConfigClient::AppSpaceCompConfigReader::GetConfig);
        FeatureManager::GetInstance().ResetForTest();
    }

    void TearDown() override
    {
        AceApplicationInfo::GetInstance().SetPackageName("");
        FeatureManager::GetInstance().ResetForTest();
        CompConfigClient::AppSpaceCompConfigReaderMock::Reset();
        MockExtraModulesManager::Reset();
    }
};

/**
 * @tc.name: GetFeatureParam001
 * @tc.desc: GetFeatureParam returns success and string value from AppSpaceCompConfigReader.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam001, TestSize.Level1)
{
    CompConfigClient::AppSpaceCompConfigReaderMock::SetConfigResult(0, TEST_VALUE);

    std::string value;
    auto result = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, value);

    EXPECT_EQ(result, FeatureManager::SUCCESS);
    EXPECT_EQ(value, TEST_VALUE);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetLastInitBundleName(), TEST_BUNDLE_NAME);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetLastConfigKey(), TEST_KEY);
}

/**
 * @tc.name: GetFeatureParam002
 * @tc.desc: GetFeatureParam returns key_not_found for empty key and does not read config.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam002, TestSize.Level1)
{
    std::string value = TEST_VALUE;
    auto result = FeatureManager::GetInstance().GetFeatureParam("", value);

    EXPECT_EQ(result, FeatureManager::KEY_NOT_FOUND);
    EXPECT_TRUE(value.empty());
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 0);
}

/**
 * @tc.name: GetFeatureParam003
 * @tc.desc: GetFeatureParam returns init_failed when reader init fails.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam003, TestSize.Level1)
{
    CompConfigClient::AppSpaceCompConfigReaderMock::Reset();
    CompConfigClient::AppSpaceCompConfigReaderMock::SetInitResult(ERROR_CODE);
    FeatureManager::GetInstance().ResetForTest();

    std::string value = TEST_VALUE;
    auto result = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, value);

    EXPECT_EQ(result, FeatureManager::INIT_FAILED);
    EXPECT_TRUE(value.empty());
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 0);
}

/**
 * @tc.name: GetFeatureParam004
 * @tc.desc: GetFeatureParam returns key_not_found when GetConfig fails.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam004, TestSize.Level1)
{
    CompConfigClient::AppSpaceCompConfigReaderMock::SetConfigResult(ERROR_CODE, TEST_VALUE);

    std::string value = TEST_VALUE;
    auto result = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, value);

    EXPECT_EQ(result, FeatureManager::KEY_NOT_FOUND);
    EXPECT_TRUE(value.empty());
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 1);
}

/**
 * @tc.name: GetFeatureParam005
 * @tc.desc: GetFeatureParam uses the reader initialized by FeatureManager singleton.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam005, TestSize.Level1)
{
    CompConfigClient::AppSpaceCompConfigReaderMock::SetConfigResult(0, TEST_VALUE);

    std::string firstValue;
    std::string secondValue;
    auto firstResult = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, firstValue);
    auto secondResult = FeatureManager::GetInstance().GetFeatureParam(OTHER_KEY, secondValue);

    EXPECT_EQ(firstResult, FeatureManager::SUCCESS);
    EXPECT_EQ(secondResult, FeatureManager::SUCCESS);
    EXPECT_EQ(firstValue, TEST_VALUE);
    EXPECT_EQ(secondValue, TEST_VALUE);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 2);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetLastConfigKey(), OTHER_KEY);
}

/**
 * @tc.name: GetFeatureParam006
 * @tc.desc: GetFeatureParam does not reinitialize reader after singleton initialization.
 * @tc.type: FUNC
 */
HWTEST_F(FeatureManagerTest, GetFeatureParam006, TestSize.Level1)
{
    CompConfigClient::AppSpaceCompConfigReaderMock::SetConfigResult(0, TEST_VALUE);

    std::string firstValue;
    std::string secondValue;
    auto firstResult = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, firstValue);
    AceApplicationInfo::GetInstance().SetPackageName(OTHER_BUNDLE_NAME);
    auto secondResult = FeatureManager::GetInstance().GetFeatureParam(TEST_KEY, secondValue);

    EXPECT_EQ(firstResult, FeatureManager::SUCCESS);
    EXPECT_EQ(secondResult, FeatureManager::SUCCESS);
    EXPECT_EQ(firstValue, TEST_VALUE);
    EXPECT_EQ(secondValue, TEST_VALUE);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetInitCallCount(), 1);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetConfigCallCount(), 2);
    EXPECT_EQ(CompConfigClient::AppSpaceCompConfigReaderMock::GetLastInitBundleName(), TEST_BUNDLE_NAME);
}
} // namespace OHOS::Ace
