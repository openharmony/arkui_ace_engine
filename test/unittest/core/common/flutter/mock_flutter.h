/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FLUTTER_MOCK_FLUTTER_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FLUTTER_MOCK_FLUTTER_H

#include "gmock/gmock.h"

namespace OHOS::Ace {
class MockAsset final : public Asset {
public:
    ~MockAsset() override = default;

    MOCK_METHOD(size_t, GetSize, (), (const, override));

    MOCK_METHOD(uint8_t*, GetData, (), (const, override));
};

class MockFileAssetProvider final : public Plugin::FileAssetProvider {
public:
    MockFileAssetProvider() = default;

    MOCK_METHOD(std::string, GetAssetPath, (const std::string& /* assetName */, bool /* isAddHapPath */),
        (override));

    MOCK_METHOD(bool, IsValid, (), (const, override));

    MOCK_METHOD(void, GetAssetList, (const std::string& path, std::vector<std::string>& assetList),
        (override));

    MOCK_METHOD(bool, Initialize, (const std::string& packagePath, const std::vector<std::string>& assetBasePaths));

    std::unique_ptr<fml::Mapping> GetAsMapping(const std::string& assetName) const
    {
        int64_t size = 101;
        uint8_t* dataArray = new (std::nothrow) uint8_t[size];
        std::unique_ptr<uint8_t[]> data(dataArray);

        return std::make_unique<MockFileAssetProvider::FileAssetMapping>(std::move(data), size);
    }

    bool GetFileInfo(const std::string& /* fileName */, MediaFileInfo& /* fileInfo */) const
    {
        return true;
    }
};

class MockAssetManager final : public AssetManager {
public:
    ~MockAssetManager() override = default;

    MOCK_METHOD(void, PushFront, (RefPtr<AssetProvider> provider), (override));
    MOCK_METHOD(void, PushBack, (RefPtr<AssetProvider> provider), (override));
    MOCK_METHOD(RefPtr<Asset>, GetAsset, (const std::string& assetName), (override));
    MOCK_METHOD(std::string, GetAssetPath, (const std::string& /* assetName */, bool /* isAddHapPath */),
        (override));
    MOCK_METHOD(void, SetLibPath, (const std::string& appLibPathKey, const std::vector<std::string>& packagePath),
        (override));
    MOCK_METHOD(std::string, GetAppLibPathKey, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, GetLibPath, (), (const, override));
    MOCK_METHOD(void, GetAssetList, (const std::string& path, std::vector<std::string>& assetList),
        (const, override));
    MOCK_METHOD(bool, GetFileInfo, (const std::string& /* fileName */, MediaFileInfo& /* fileInfo */),
        (const, override));
};
}
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FLUTTER_MOCK_FLUTTER_H

