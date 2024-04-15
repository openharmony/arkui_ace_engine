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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_FILE_ASSET_PROVIDER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_FILE_ASSET_PROVIDER_IMPL_H

#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/asset_mapping.h"

namespace OHOS::Ace {
class ACE_EXPORT FileAssetProviderImpl : public AssetProviderImpl {
    DECLARE_ACE_TYPE(FileAssetProviderImpl, AssetProviderImpl);
public:
    FileAssetProviderImpl() = default;
    ~FileAssetProviderImpl() override = default;

    bool Initialize(const std::string& packagePath, const std::vector<std::string>& assetBasePaths);
    std::unique_ptr<AssetMapping> GetAsMapping(const std::string& assetName) const override;
    std::vector<std::unique_ptr<AssetMapping>> GetAsMappingFromI18n(const std::string& assetName) const override
    {
        return {};
    }
    bool IsValid() const override;
    std::string GetAssetPath(const std::string& assetName, bool isAddHapPath) override;
    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) override;

private:
    class FileAssetImplMapping : public AssetMapping {
    public:
        FileAssetImplMapping(std::unique_ptr<uint8_t[]> data, size_t size) : data_(std::move(data)), size_(size) {}
        ~FileAssetImplMapping() override = default;

        size_t GetSize() const override
        {
            return size_;
        }

        const uint8_t* GetAsset() const override
        {
            return data_.get();
        }

    private:
        std::unique_ptr<uint8_t[]> data_;
        size_t size_ = 0;
    };

    mutable std::mutex mutex_;
    std::string packagePath_;
    std::vector<std::string> assetBasePaths_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_FILE_ASSET_PROVIDER_IMPL_H
