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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASSET_MANAGER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASSET_MANAGER_IMPL_H

#include <deque>
#include <vector>
#include <memory>
#include <mutex>

#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"
#include "core/common/asset_mapping.h"

namespace OHOS::Ace {
class AssetImpl final : public Asset {
public:
    AssetImpl(std::unique_ptr<AssetMapping> mapping) : assetMapping_(std::move(mapping)) {};
    ~AssetImpl() override = default;
    size_t GetSize() const override;
    const uint8_t* GetData() const override;

private:
    std::unique_ptr<AssetMapping> assetMapping_;
};

class AssetProviderImpl : public AssetProvider {
    DECLARE_ACE_TYPE(AssetProviderImpl, AssetProvider);

public:
    virtual std::unique_ptr<AssetMapping> GetAsMapping(const std::string& assetName) const = 0;
    virtual std::vector<std::unique_ptr<AssetMapping>> GetAsMappingFromI18n(const std::string& assetName) const = 0;
};

class ACE_EXPORT AssetManagerImpl final : public AssetManager {
    DECLARE_ACE_TYPE(AssetManagerImpl, AssetManager);

public:
    AssetManagerImpl() = default;
    ~AssetManagerImpl() override = default;
    void PushFront(RefPtr<AssetProvider> provider) override;
    void PushBack(RefPtr<AssetProvider> provider) override;
    RefPtr<Asset> GetAsset(const std::string& assetName) override;
    std::vector<RefPtr<Asset>> GetAssetFromI18n(const std::string& assetName) override;
    std::string GetAssetPath(const std::string& assetName, bool isAddHapPath) override;
    void SetLibPath(const std::string& appLibPathKey, const std::vector<std::string>& packagePath) override;
    std::vector<std::string> GetLibPath() const override;
    std::string GetAppLibPathKey() const override;
    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) const override;
    bool GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const override;
    void ReloadProvider();

private:
    std::vector<std::string> libPath_;
    std::string libKey_;
    std::deque<RefPtr<AssetProvider>> assetProviders_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASSET_MANAGER_IMPL_H
