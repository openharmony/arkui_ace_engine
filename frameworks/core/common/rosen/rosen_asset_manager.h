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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ASSET_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ASSET_MANAGER_H

#include <deque>
#include <vector>

#include "base/log/event_report.h"
#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

class RSAsset final : public Asset {
public:
    RSAsset(std::unique_ptr<char[]> data, size_t size)
        : data_(std::move(data)), size_(size)
    {
    }

    size_t GetSize() const override
    {
        return size_;
    }

    const uint8_t* GetData() const override
    {
        return reinterpret_cast<uint8_t *>(data_.get());
    }

private:
    std::unique_ptr<char[]> data_ = nullptr;
    size_t size_ = 0;
};

class RSAssetProvider : public AssetProvider {
    DECLARE_ACE_TYPE(RSAssetProvider, AssetProvider);

public:
    virtual RefPtr<Asset> GetAsset(const std::string &assetName) const = 0;
};

class ACE_EXPORT RSAssetManager final : public AssetManager {
    DECLARE_ACE_TYPE(RSAssetManager, AssetManager);

public:
    RSAssetManager() = default;
    ~RSAssetManager() override = default;

    void PushFront(RefPtr<AssetProvider> provider) override
    {
        if (!provider || !provider->IsValid()) {
            return;
        }
        providers_.push_front(std::move(provider));
    }

    void PushBack(RefPtr<AssetProvider> provider) override
    {
        if (!provider || !provider->IsValid()) {
            return;
        }
        providers_.push_back(std::move(provider));
    }

    RefPtr<Asset> GetAsset(const std::string& assetName) override;

    std::vector<RefPtr<Asset>> GetAssetFromI18n(const std::string& assetName) override
    {
        return {};
    }

    std::string GetAssetPath(const std::string& assetName, bool isAddHapPath) override;

    void SetLibPath(const std::string& appLibPathKey, const std::vector<std::string>& packagePath) override
    {
        appLibPathKey_ = appLibPathKey;
        packagePath_ = packagePath;
    }

    std::vector<std::string> GetLibPath() const override
    {
        return packagePath_;
    }

    std::string GetAppLibPathKey() const override
    {
        return appLibPathKey_;
    }

    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) const override;

    bool GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const override;

private:
    std::deque<RefPtr<AssetProvider>> providers_;
    std::vector<std::string> packagePath_;
    std::string appLibPathKey_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_ASSET_MANAGER_H
