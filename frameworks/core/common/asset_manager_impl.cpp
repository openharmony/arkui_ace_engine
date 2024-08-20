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

#include "core/common/asset_manager_impl.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
size_t AssetImpl::GetSize() const
{
    CHECK_NULL_RETURN(assetMapping_, 0);
    return assetMapping_->GetSize();
}

const uint8_t* AssetImpl::GetData() const
{
    CHECK_NULL_RETURN(assetMapping_, nullptr);
    return assetMapping_->GetAsset();
}

void AssetManagerImpl::PushFront(RefPtr<AssetProvider> provider)
{
    if (provider && provider->IsValid()) {
        assetProviders_.push_front(std::move(provider));
    }
}

void AssetManagerImpl::PushBack(RefPtr<AssetProvider> provider)
{
    if (provider && provider->IsValid()) {
        assetProviders_.push_back(std::move(provider));
    }
}

RefPtr<Asset> AssetManagerImpl::GetAsset(const std::string& assetName)
{
    if (assetName.empty()) {
        LOGW("GetAsset failed. assetName is null.");
        return nullptr;
    }

    for (const auto& assetProvider : assetProviders_) {
        auto asProvider = AceType::DynamicCast<AssetProviderImpl>(assetProvider);
        if (!asProvider) {
            continue;
        }

        auto assetMapping = asProvider->GetAsMapping(assetName);
        if (assetMapping) {
            return AceType::MakeRefPtr<AssetImpl>(std::move(assetMapping));
        }
    }

    LOGW("GetAsset failed: %{public}s", assetName.c_str());
    return nullptr;
}

std::vector<RefPtr<Asset>> AssetManagerImpl::GetAssetFromI18n(const std::string& assetName)
{
    std::vector<RefPtr<Asset>> i18nAssetVector;
    if (assetName.empty()) {
        LOGW("GetAsset from i18n failed. assetName is null.");
        return i18nAssetVector;
    }

    for (const auto& assetProvider : assetProviders_) {
        auto asProvider = AceType::DynamicCast<AssetProviderImpl>(assetProvider);
        if (!asProvider) {
            continue;
        }

        auto assetVector = asProvider->GetAsMappingFromI18n(assetName);
        for (auto& assetMapping : assetVector) {
            i18nAssetVector.push_back(AceType::MakeRefPtr<AssetImpl>(std::move(assetMapping)));
        }
    }
    return i18nAssetVector;
}

std::string AssetManagerImpl::GetAssetPath(const std::string& assetName, bool isAddHapPath)
{
    for (const auto& assetProvider : assetProviders_) {
        std::string assetPath = assetProvider->GetAssetPath(assetName, isAddHapPath);
        if (!assetPath.empty()) {
            return assetPath;
        }
    }

    return "";
}

void AssetManagerImpl::SetLibPath(const std::string& appLibPathKey, const std::vector<std::string>& packagePath)
{
    libKey_ = appLibPathKey;
    libPath_ = packagePath;
}

std::vector<std::string> AssetManagerImpl::GetLibPath() const
{
    return libPath_;
}

std::string AssetManagerImpl::GetAppLibPathKey() const
{
    return libKey_;
}

void AssetManagerImpl::GetAssetList(const std::string& path, std::vector<std::string>& assetList) const
{
    for (const auto& assetProvider : assetProviders_) {
        assetProvider->GetAssetList(path, assetList);
    }
}

bool AssetManagerImpl::GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const
{
    for (const auto& assetProvider : assetProviders_) {
        if (assetProvider->GetFileInfo(fileName, fileInfo)) {
            return true;
        }
    }
    return false;
}

void AssetManagerImpl::ReloadProvider()
{
    for (auto& assetProvider : assetProviders_) {
        assetProvider->Reload();
    }
}
} // namespace OHOS::Ace
