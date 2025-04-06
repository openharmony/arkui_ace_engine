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

#include "adapter/ohos/entrance/utils.h"

#include <regex>

#include "wm/wm_common.h"

#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"

namespace OHOS::Ace {

std::string GetStringFromFile(const std::string& packagePathStr, const std::string& fileName)
{
    auto configPath = packagePathStr + fileName;
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(configPath.c_str(), realPath) == nullptr) {
        LOGE("realpath fail! filePath: %{private}s, fail reason: %{public}s", configPath.c_str(), strerror(errno));
        return "";
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (!file) {
        LOGE("open file failed, filePath: %{private}s, fail reason: %{public}s", configPath.c_str(), strerror(errno));
        return "";
    }
    if (std::fseek(file.get(), 0, SEEK_END) != 0) {
        LOGE("seek file tail error");
        return "";
    }

    int64_t size = std::ftell(file.get());
    if (size == -1L) {
        return "";
    }

    std::string fileData;
    fileData.resize(size);

    rewind(file.get());
    size_t result = std::fread(fileData.data(), 1, fileData.size(), file.get());
    if (result != static_cast<size_t>(size)) {
        LOGE("read file failed");
        return "";
    }

    return fileData;
}

std::string GetStringFromHap(const std::string& hapPath, const std::string& fileName)
{
    bool newCreate = false;
    std::string loadPath = AbilityBase::ExtractorUtil::GetLoadFilePath(hapPath);
    std::shared_ptr<AbilityBase::Extractor> extractor = AbilityBase::ExtractorUtil::GetExtractor(loadPath, newCreate);
    if (!extractor) {
        LOGE("read file %{public}s error\n", hapPath.c_str());
        return "";
    }

    std::ostringstream osstream;
    bool hasFile = extractor->GetFileBuffer(fileName, osstream);
    if (!hasFile) {
        LOGE("read file %{public}s /config.json error\n", hapPath.c_str());
        return "";
    }

    return osstream.str();
}

bool CheckUrlValid(const std::string& url, const std::string& hapPath)
{
    std::string bundleNameFlag = "@bundle:";
    if (url.find(bundleNameFlag) == 0) {
        return true;
    }

    auto moduleContent = GetStringFromHap(hapPath, "module.json");
    auto moduleValue = JsonUtil::ParseJsonString(moduleContent);
    auto pagesValue = moduleValue->GetValue("module")->GetString("pages");
    std::string profileMark = "$profile:";
    auto jsonPath = pagesValue.replace(0, profileMark.size(), "resources/base/profile/") + ".json";

    auto jsonContent = GetStringFromHap(hapPath, jsonPath);
    auto jsonValue = JsonUtil::ParseJsonString(jsonContent);
    auto srcValue = jsonValue->GetValue("src");
    auto arrSize = srcValue->GetArraySize();

    for (int32_t i = 0; i < arrSize; i++) {
        auto urlPath = srcValue->GetArrayItem(i)->GetString();
        if (urlPath == url) {
            return true;
        }
    }

    return false;
}

RefPtr<AssetProviderImpl> CreateAssetProviderImpl(
    const std::string& packagePath, const std::vector<std::string>& assetBasePaths, bool useCache)
{
    if (std::regex_match(packagePath, std::regex(".*\\.hap"))) {
        auto assetProviderImpl = AceType::MakeRefPtr<HapAssetProviderImpl>();
        if (assetProviderImpl->Initialize(packagePath, assetBasePaths, useCache)) {
            return assetProviderImpl;
        }
    } else {
        auto assetProviderImpl = AceType::MakeRefPtr<FileAssetProviderImpl>();
        if (assetProviderImpl->Initialize(packagePath, assetBasePaths)) {
            return assetProviderImpl;
        }
    }
    return nullptr;
}

NG::SafeAreaInsets ConvertAvoidArea(const OHOS::Rosen::AvoidArea& avoidArea)
{
    return NG::SafeAreaInsets({ avoidArea.leftRect_.posX_, avoidArea.leftRect_.posX_ + avoidArea.leftRect_.width_ },
        { avoidArea.topRect_.posY_, avoidArea.topRect_.posY_ + avoidArea.topRect_.height_ },
        { avoidArea.rightRect_.posX_, avoidArea.rightRect_.posX_ + avoidArea.rightRect_.width_ },
        { avoidArea.bottomRect_.posY_, avoidArea.bottomRect_.posY_ + avoidArea.bottomRect_.height_ });
}

Rosen::AvoidArea ConvertAvoidArea(const NG::SafeAreaInsets& insets, int32_t rootWidth, int32_t rootHeight)
{
    Rosen::AvoidArea area;
    area.topRect_ = Rosen::Rect{ 0, insets.top_.start, rootWidth, insets.top_.end - insets.top_.start };
    area.leftRect_ = Rosen::Rect{ insets.left_.start, 0, insets.left_.end - insets.left_.start, rootHeight };
    area.rightRect_ = Rosen::Rect{ insets.right_.start, 0, insets.right_.end - insets.right_.start, rootHeight };
    area.bottomRect_ = Rosen::Rect{ 0, insets.bottom_.start, rootWidth, insets.bottom_.end - insets.bottom_.start };
    return area;
}

Rect ConvertDMRect2Rect(const OHOS::Rosen::DMRect& displayAvailableRect)
{
    return Rect(displayAvailableRect.posX_, displayAvailableRect.posY_, displayAvailableRect.width_,
        displayAvailableRect.height_);
}
} // namespace OHOS::Ace
