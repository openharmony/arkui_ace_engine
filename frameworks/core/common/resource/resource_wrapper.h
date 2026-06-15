/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_WRAPPER_H

#include <memory>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/device_config.h"

namespace OHOS {
namespace Media {
class PixelMap;
}
}

namespace OHOS::Ace {

class Color;
class Dimension;
class ThemeConstants;
class ResourceAdapter;
struct RawfileDescription;

class ACE_FORCE_EXPORT ResourceWrapper : public AceType {
    DECLARE_ACE_TYPE(ResourceWrapper, AceType);

public:
    ResourceWrapper(RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter);

    ResourceWrapper(
        RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter, ColorMode colorMode);
    ~ResourceWrapper() override;

    Color GetColor(uint32_t key) const;
    Color GetColorByName(const std::string& resName) const;
    Dimension GetDimension(uint32_t key) const;
    Dimension GetDimensionByName(const std::string& resName) const;
    int32_t GetInt(uint32_t key) const;
    int32_t GetIntByName(const std::string& resName) const;
    double GetDouble(uint32_t key) const;
    double GetDoubleByName(const std::string& resName) const;
    std::string GetString(uint32_t key) const;
    std::string GetStringByName(const std::string& resName) const;
    std::string GetPluralString(uint32_t key, int count) const;
    std::string GetPluralStringByName(const std::string& resName, int count) const;
    bool GetBoolean(uint32_t key) const;
    bool GetBooleanByName(const std::string& resName) const;
    std::vector<uint32_t> GetIntArray(uint32_t key) const;
    std::vector<uint32_t> GetIntArrayByName(const std::string& resName) const;
    std::shared_ptr<Media::PixelMap> GetPixelMap(uint32_t key) const;
    std::vector<std::string> GetStringArray(uint32_t key) const;
    std::vector<std::string> GetStringArrayByName(const std::string& resName) const;
    std::string GetMediaPath(uint32_t key) const;
    std::string GetMediaPathByName(const std::string& resName) const;
    std::string GetRawfile(const std::string& fileName) const;
    bool GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const;
    bool CloseRawFileDescription(const std::string& rawfileName) const;
    bool GetRawFD(const std::string& rawfileName, RawfileDescription& rawfileDescription) const;
    bool GetMediaById(const int32_t& resId, std::string& mediaPath) const;

    template<class T>
    bool GetMediaResource(T& resId, std::ostream& dest) const;

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest);

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest, const std::string& bundleName,
        const std::string& moduleName);

    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest);
    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName);
    bool GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const;
    uint32_t GetSymbolByName(const char* name) const;
    uint32_t GetSymbolById(uint32_t resId) const;
    void UpdateColorMode(ColorMode colorMode);
    const RefPtr<ResourceAdapter>& GetResourceAdapter() const;

private:
    RefPtr<ThemeConstants> themeConstants_;
    RefPtr<ResourceAdapter> resourceAdapter_;
    ColorMode localColorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace

#endif
