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
#include "adapter/ohos/entrance/utils.h"

using namespace testing::ext;

namespace OHOS::Ace {
class EntranceUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void EntranceUtilsTest::SetUpTestCase() {}

void EntranceUtilsTest::TearDownTestCase() {}

void EntranceUtilsTest::SetUp() {}

void EntranceUtilsTest::TearDown() {}

/**
 * @tc.name: EntranceUtilsTest_001
 * @tc.desc: GetStringFromFile
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_001, TestSize.Level1)
{
    const std::string packagePathStr;
    const std::string fileName;
    std::string stringFromFile = OHOS::Ace::GetStringFromFile(packagePathStr, fileName);
    EXPECT_EQ(stringFromFile, "");
}

/**
 * @tc.name: EntranceUtilsTest_002
 * @tc.desc: GetStringFromFile
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_002, TestSize.Level1)
{
    const std::string packagePathStr = "/system/app/com.ohos.photos";
    const std::string fileName = "/error";
    std::string stringFromFile = OHOS::Ace::GetStringFromFile(packagePathStr, fileName);
    EXPECT_EQ(stringFromFile, "");
}

/**
 * @tc.name: EntranceUtilsTest_003
 * @tc.desc: GetStringFromFile
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_003, TestSize.Level1)
{
    const std::string packagePathStr = "/system/app/com.ohos.photos";
    const std::string fileName = "/Photos.hap";
    std::string stringFromFile = OHOS::Ace::GetStringFromFile(packagePathStr, fileName);
    EXPECT_NE(stringFromFile, "");
}

/**
 * @tc.name: EntranceUtilsTest_004
 * @tc.desc: GetStringFromHap
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_004, TestSize.Level1)
{
    const std::string hapPath = "error";
    const std::string fileName;
    std::string StringFromHap = OHOS::Ace::GetStringFromHap(hapPath, fileName);
    EXPECT_EQ(StringFromHap, "");
}

/**
 * @tc.name: EntranceUtilsTest_005
 * @tc.desc: GetStringFromHap
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_005, TestSize.Level1)
{
    const std::string hapPath = "/system/app/com.ohos.photos/Photos.hap";
    const std::string fileName = "error";
    std::string StringFromHap = OHOS::Ace::GetStringFromHap(hapPath, fileName);
    EXPECT_EQ(StringFromHap, "");
}

/**
 * @tc.name: EntranceUtilsTest_007
 * @tc.desc: CreateAssetProvider
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_007, TestSize.Level1)
{
    std::string packagePath = "";
    std::vector<std::string> assetBasePaths;
    RefPtr<FlutterAssetProvider> testFlutterAssetProvider = CreateAssetProvider(packagePath, assetBasePaths);
    EXPECT_EQ(testFlutterAssetProvider, nullptr);
}

/**
 * @tc.name: EntranceUtilsTest_008
 * @tc.desc: CreateAssetProvider
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(EntranceUtilsTest, EntranceUtilsTest_008, TestSize.Level1)
{
    std::string packagePath = "/system/app/com.ohos.photos";
    std::vector<std::string> assetBasePaths;
        assetBasePaths.push_back("assets/js/com.ohos.photos/");
        assetBasePaths.emplace_back("assets/js/share/");
        assetBasePaths.emplace_back("");
        assetBasePaths.emplace_back("js/");
        assetBasePaths.emplace_back("ets/");
    RefPtr<FlutterAssetProvider> testFlutterAssetProvider = CreateAssetProvider(packagePath, assetBasePaths);
    EXPECT_NE(testFlutterAssetProvider, nullptr);
}
} // namespace OHOS::Ace