/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "mock_asset.h"
#include "test/mock/core/common/mock_container.h"

#define private public
#define protected public

#include "core/common/asset_manager_impl.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const std::string ASSET_TEST = "test";
const std::string PACK_PATH = "/system/app/com.ohos.photos/Photos.hap";
const std::string ASSET_BASE_PATH = "/resources/base/profile/";
MediaFileInfo MEDIA_FILE_INFO = { .fileName = ASSET_TEST, .length = 1, .lastModTime = 1, .lastModDate = 1 };
} // namespace

class AssetTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: AssetTest01
 * @tc.desc: Test the asset operation.
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    auto assetProvider = AceType::MakeRefPtr<Ace::FileAssetProviderImpl>();

    /**
     * @tc.steps: step2. call Initialize.
     * @tc.steps: step3. call PushBack with the asset provider.
     */
    std::vector<std::string> basePaths;
    basePaths.push_back(ASSET_BASE_PATH);
    assetProvider->Initialize(PACK_PATH, basePaths);
    assetManager->PushBack(std::move(assetProvider));

    /**
     * @tc.steps: step4. call GetAssetPath with ASSET_TEST.
     * @tc.expected: step4. Return expected results.
     */
    std::string result = assetManager->GetAssetPath(ASSET_TEST, true);
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: AssetTest02
 * @tc.desc: Test the asset operation
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    /**
     * @tc.steps: step2. Call GetAssetPath of asset manager.
     * @tc.expected: step2. Return expected results.
     */
    std::string asset_path = assetManager->GetAssetPath(ASSET_TEST, true);
    EXPECT_EQ(asset_path, "");

    /**
     * @tc.steps: step3. Call GetAssetPath with the asset provider.
     * @tc.expected: step3. Return expected results.
     */

    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAssetPath(ASSET_TEST, true)).Times(1).WillOnce(Return(ASSET_TEST));
    assetManager->PushBack(std::move(assetProvider));

    /**
     * @tc.steps: step4. Call GetAssetPath with the asset provider.
     * @tc.expected: step4. Return expected results.
     */
    std::string path_Result = assetManager->GetAssetPath(ASSET_TEST, true);
    EXPECT_EQ(path_Result, ASSET_TEST);
}

/**
 * @tc.name: AssetTest03
 * @tc.desc: Test the asset operation.
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     * @tc.steps: step2. Build a mockAssetProvider.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    std::vector<std::string> assetList;
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAssetList(ASSET_TEST, assetList)).WillOnce(Return());

    /**
     * @tc.steps: step3. Call PushBack with the asset provider.
     * @tc.steps: step4. Call GetAssetList.
     * @tc.expected: step4. Return expected results.
     */
    assetManager->PushBack(std::move(assetProvider));
    assetManager->GetAssetList(ASSET_TEST, assetList);
    EXPECT_TRUE(assetList.empty());
}

/**
 * @tc.name: AssetTest04
 * @tc.desc: Test the asset operation.
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     * @tc.steps: step2. Call GetFileInfo with null assetName.
     * @tc.expected: step2. Return expected results.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    auto assetProvider = AceType::MakeRefPtr<Ace::FileAssetProviderImpl>();
    std::vector<std::string> assetBasePaths;
    assetBasePaths.push_back(ASSET_BASE_PATH);
    assetProvider->Initialize(PACK_PATH, assetBasePaths);
    assetProvider->GetFileInfo(PACK_PATH, MEDIA_FILE_INFO);
    assetManager->PushBack(std::move(assetProvider));
    bool info_Result = assetManager->GetFileInfo(PACK_PATH, MEDIA_FILE_INFO);
    EXPECT_FALSE(info_Result);
}

/**
 * @tc.name: AssetTest05
 * @tc.desc: Test the asset operation.
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest05, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     * @tc.steps: step2. Call GetAsset with the asset provider.
     * @tc.expected: step2. The expected result is null.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    std::string testFilePath = "core/common/asset/BUILD.gn";
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*assetProvider, GetAsset(testFilePath)).Times(1).WillOnce(Return(nullptr));
    assetProvider->GetAsset(testFilePath);
    assetManager->PushBack(std::move(assetProvider));
    auto asset_Value = assetManager->GetAsset(testFilePath);
    EXPECT_EQ(asset_Value, nullptr);
}

/**
 * @tc.name: AssetTest06
 * @tc.desc: Test the asset operation.
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest06, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a manager.
     */
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();

    /**
     * @tc.steps: step2. Call GetAsset with null assetName.
     * @tc.expected: step2. Return expected results.
     */
    auto result = assetManager->GetAsset("");
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step3. Call GetAsset with assetName.
     * @tc.expected: step3. Return expected results.
     */
    auto asset_Result = assetManager->GetAsset(ASSET_TEST);
    EXPECT_EQ(asset_Result, nullptr);
}

/**
 * @tc.name: AssetTest07
 * @tc.desc: Test PushFront/PushBack
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest07, TestSize.Level1)
{
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    // assetProvider null
    assetManager->PushFront(nullptr);
    assetManager->PushBack(nullptr);
    EXPECT_EQ(assetManager->assetProviders_.size() == 0, true);
    // assetProvider is not null,IsValid is true
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    assetManager->PushFront(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 1, true);
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    assetManager->PushBack(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 2, true);
    // assetProvider is not null,IsValid is false
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(false));
    assetManager->PushFront(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 2, true);
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(false));
    assetManager->PushBack(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 2, true);
}

/**
 * @tc.name: AssetTest08
 * @tc.desc: Test GetAssetFromI18n
 * @tc.type: FUNC
 */
HWTEST_F(AssetTest, AssetTest08, TestSize.Level1)
{
    auto assetManager = AceType::MakeRefPtr<AssetManagerImpl>();
    auto assetProvider = AceType::MakeRefPtr<MockAssetProvider>();
    // assetProvider is not null,IsValid is true
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    assetManager->PushFront(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 1, true);
    EXPECT_CALL(*assetProvider, IsValid()).Times(1).WillOnce(Return(true));
    assetManager->PushBack(assetProvider);
    EXPECT_EQ(assetManager->assetProviders_.size() == 2, true);
    // assetName is empty
    std::string assetName = "";
    std::vector<RefPtr<Asset>> ret = assetManager->GetAssetFromI18n(assetName);
    EXPECT_EQ(ret.size() == 0, true);
    // assetName is not empty
    assetName = "test";
    std::vector<RefPtr<Asset>> ret2 = assetManager->GetAssetFromI18n(assetName);
    EXPECT_EQ(ret2.size() == 0, true);
}
} // namespace OHOS::Ace
