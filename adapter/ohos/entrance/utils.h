/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H

#include <string>

#include "base/log/log.h"
#include "base/geometry/rect.h"
#include "core/common/asset_manager_impl.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Rosen {
    class AvoidArea;
    struct DMRect;
}
namespace OHOS::Ace {

std::string GetStringFromFile(const std::string& packagePathStr, const std::string& fileName);
std::string GetStringFromHap(const std::string& hapPath, const std::string& fileName);
bool CheckUrlValid(const std::string& url, const std::string& hapPath);

RefPtr<AssetProviderImpl> CreateAssetProviderImpl(
    const std::string& packagePath, const std::vector<std::string>& assetBasePaths, bool useCache = true);

inline const std::string GenerateFullPath(const std::string& prePath, const std::string& postPath)
{
    if (prePath.empty() && postPath.empty()) {
        return "";
    }
    std::string tmpPostPath = postPath;
    if (tmpPostPath.back() == '/') {
        tmpPostPath.pop_back();
    }
    std::string fullPath = prePath;
    if (fullPath.empty() || fullPath.back() == '/') {
        fullPath += tmpPostPath;
    } else {
        fullPath += "/" + tmpPostPath;
    }
    return fullPath;
}

NG::SafeAreaInsets ConvertAvoidArea(const OHOS::Rosen::AvoidArea& avoidArea);
Rect ConvertDMRect2Rect(const OHOS::Rosen::DMRect& displayAvailableRect);
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_UTILS_H
