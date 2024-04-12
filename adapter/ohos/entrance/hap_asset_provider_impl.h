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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_IMPL_H

#include <mutex>
#include <sstream>
#include <string>
#include <vector>

#include "extractor.h"

#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/asset_mapping.h"

namespace OHOS::Ace {
class ACE_EXPORT HapAssetProviderImpl : public AssetProviderImpl {
    DECLARE_ACE_TYPE(HapAssetProviderImpl, AssetProviderImpl);
public:
    HapAssetProviderImpl() = default;
    ~HapAssetProviderImpl() override = default;

    bool Initialize(const std::string& hapPath, const std::vector<std::string>& assetBasePaths, bool useCache = true);
    std::unique_ptr<AssetMapping> GetAsMapping(const std::string& assetName) const override;
    std::vector<std::unique_ptr<AssetMapping>> GetAsMappingFromI18n(const std::string& assetName) const override;
    bool IsValid() const override;
    std::string GetAssetPath(const std::string& assetName, bool isAddHapPath) override;
    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) override;
    bool GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const override;
    void Reload() override;

private:
    class HapAssetImplMapping : public AssetMapping {
    public:
        explicit HapAssetImplMapping(const std::ostringstream& ostream)
        {
            const std::string& content = ostream.str();
            data_.assign(content.data(), content.data() + content.size());
        }

        ~HapAssetImplMapping() override = default;

        size_t GetSize() const override
        {
            return data_.size();
        }

        const uint8_t* GetAsset() const override
        {
            return data_.data();
        }

    private:
        std::vector<uint8_t> data_;
    };

    mutable std::mutex mutex_;
    std::string hapPath_;
    std::string loadPath_;
    std::shared_ptr<AbilityBase::Extractor> runtimeExtractor_;
    std::vector<std::string> assetBasePaths_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_IMPL_H
