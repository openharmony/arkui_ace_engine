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

#include "rosen_asset_manager.h"

#include "base/log/log.h"

namespace OHOS::Ace {
RefPtr<Asset> RSAssetManager::GetAsset(const std::string& assetName)
{
    if (assetName.empty()) {
        LOGE("GetAsset assetName is empty");
        return nullptr;
    }

    for (const auto& provider : providers_) {
        auto fileProvider = AceType::DynamicCast<RSAssetProvider>(provider);
        if (fileProvider == nullptr) {
            continue;
        }

        auto asset = fileProvider->GetAsset(assetName);
        if (asset == nullptr) {
            continue;
        }

        return asset;
    }

    LOGW("find asset failed, assetName = %{public}s", assetName.c_str());
    return nullptr;
}

std::string RSAssetManager::GetAssetPath(const std::string& assetName, bool isAddHapPath)
{
    for (const auto& provider : providers_) {
        std::string path = provider->GetAssetPath(assetName, isAddHapPath);
        if (!path.empty()) {
            return path;
        }
    }

    return "";
}

void RSAssetManager::GetAssetList(const std::string& path, std::vector<std::string>& assetList) const
{
    for (const auto& provider : providers_) {
        provider->GetAssetList(path, assetList);
    }
}

bool RSAssetManager::GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const
{
    for (const auto& provider : providers_) {
        if (provider->GetFileInfo(fileName, fileInfo)) {
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace
