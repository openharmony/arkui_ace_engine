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

#include "adapter/ohos/entrance/hap_asset_provider.h"

using namespace testing::ext;

namespace OHOS::Ace {
class HapAssetProviderTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<HapAssetProvider> hapAssetProvider_;
};

void HapAssetProviderTest::SetUpTestCase() {}

void HapAssetProviderTest::TearDownTestCase() {}

void HapAssetProviderTest::SetUp() {}

void HapAssetProviderTest::TearDown() {}

/**
 * @tc.name: HapAssetProviderTest_001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_001, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    bool result = hapAssetProvider_->Initialize(hapPath, assetBasePaths);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HapAssetProviderTest_002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_002, TestSize.Level1)
{
    std::string hapPath = "";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("/system/app/com.ohos.photos/Photos.hap");
    bool result = hapAssetProvider_->Initialize(hapPath, assetBasePaths);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HapAssetProviderTest_003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_003, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("/system/app/com.ohos.photos/Photos.hap");
    HapAssetProvider hapAssetProvider;
    bool result = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HapAssetProviderTest_004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_004, TestSize.Level1)
{
    HapAssetProvider hapAssetProvider;
    bool result = hapAssetProvider.IsValid();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HapAssetProviderTest_005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_005, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("/error/");
    HapAssetProvider hapAssetProvider;
    bool result = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result);
    std::string assetName = "error";
    std::unique_ptr<fml::Mapping> testMapping = hapAssetProvider.GetAsMapping(assetName);
    EXPECT_EQ(testMapping, nullptr);
}

/**
 * @tc.name: HapAssetProviderTest_006
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_006, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    HapAssetProvider hapAssetProvider;
    bool result = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result);

    std::string assetName = "form_config.json";
    std::unique_ptr<fml::Mapping> testMapping = hapAssetProvider.GetAsMapping(assetName);
    EXPECT_NE(testMapping, nullptr);
}

/**
 * @tc.name: HapAssetProviderTest_007
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_007, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    HapAssetProvider hapAssetProvider;
    bool result_init = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result_init);

    std::string assetName = "error";
    std::string result = hapAssetProvider.GetAssetPath(assetName);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: HapAssetProviderTest_008
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_008, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    HapAssetProvider hapAssetProvider;
    bool result_init = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result_init);

    std::string assetName = "form_config.json";
    std::string result = hapAssetProvider.GetAssetPath(assetName);
    EXPECT_EQ(result, "/system/app/com.ohos.photos/Photos.hap/resources/base/profile/");
}

/**
 * @tc.name: HapAssetProviderTest_009
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HapAssetProviderTest, HapAssetProviderTest_009, TestSize.Level1)
{
    std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back("resources/base/profile/");
    HapAssetProvider hapAssetProvider;
    bool result_init = hapAssetProvider.Initialize(hapPath, assetBasePaths);
    EXPECT_TRUE(result_init);

    std::string path = "error";
    std::vector<std::string> assetList;
    hapAssetProvider.GetAssetList(path, assetList);
    EXPECT_TRUE(assetList.empty());
}
} // namespace OHOS::Ace
