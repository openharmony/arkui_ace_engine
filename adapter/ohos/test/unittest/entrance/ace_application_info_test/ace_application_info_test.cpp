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

#include <gtest/gtest.h>

#include "ace_application_info.h"

using namespace testing::ext;
using namespace OHOS::Ace::Platform;
using namespace OHOS::Global::Resource;

namespace OHOS::Ace {
class AceApplicationInfoTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AceApplicationInfoTest::SetUpTestCase() {}

void AceApplicationInfoTest::TearDownTestCase() {}

void AceApplicationInfoTest::SetUp() {}

void AceApplicationInfoTest::TearDown() {}

/**
 * @tc.name: AceApplicationInfoTest_001
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_001, TestSize.Level1)
{
    AceApplicationInfoImpl::GetInstance();
    AceApplicationInfo::GetInstance();
}

/**
 * @tc.name: AceApplicationInfoTest_002
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_002, TestSize.Level1)
{
    std::string language = "am";
    std::string countryOrRegion {""};
    std::string script {""};
    std::string keywordsAndValues {""} ;
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion,
        script, keywordsAndValues);

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLanguage().c_str(),
        language.c_str());
}

/**
 * @tc.name: AceApplicationInfoTest_003
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_003, TestSize.Level1)
{
    std::string language = "en";
    std::string countryOrRegion {""};
    std::string script {"GB"};
    std::string keywordsAndValues {""} ;
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion,
        script, keywordsAndValues);

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLanguage().c_str(),
        language.c_str());

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLocaleTag().c_str(),
        "en-GB");
}

/**
 * @tc.name: AceApplicationInfoTest_004
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_004, TestSize.Level1)
{
    std::string language = "zh";
    std::string countryOrRegion {"HK"};
    std::string script {""};
    std::string keywordsAndValues {""} ;
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion,
        script, keywordsAndValues);

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLanguage().c_str(),
        language.c_str());

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLocaleTag().c_str(),
        "zh-HK");
}

/**
 * @tc.name: AceApplicationInfoTest_005
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_005, TestSize.Level1)
{
    std::string language = "zh";
    std::string countryOrRegion {"HK"};

    std::shared_ptr<ResourceManager> resourceManager(CreateResourceManager());
    AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager);
    AceApplicationInfo::GetInstance().ChangeLocale(language, countryOrRegion);

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLanguage().c_str(),
        language.c_str());

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetLocaleTag().c_str(),
        "zh-HK");
}

/**
 * @tc.name: AceApplicationInfoTest_006
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_006, TestSize.Level1)
{
    AceBundleInfo bundleInfo;
    EXPECT_FALSE(AceApplicationInfo::GetInstance().GetBundleInfo("", bundleInfo));
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GetLifeTime() == 0.0);
}

/**
 * @tc.name: AceApplicationInfoTest_007
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceApplicationInfoTest, AceApplicationInfoTest_007, TestSize.Level1)
{
    AceApplicationInfoImpl::GetInstance().SetJsEngineParam("key1", "value1");
    AceApplicationInfoImpl::GetInstance().SetJsEngineParam("key2", "value2");

    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetJsEngineParam("key1").c_str(),
        "value1");
    EXPECT_STREQ(AceApplicationInfo::GetInstance().GetJsEngineParam("key2").c_str(),
        "value2");
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GetJsEngineParam("key").empty());
}
}