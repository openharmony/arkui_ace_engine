/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H

#include "base/image/pixel_map.h"
#include "base/utils/resource_configuration.h"
#include "core/common/resource/resource_configuration.h"
#include "core/components/theme/theme_style.h"
namespace OHOS::Ace {

struct RawfileDescription {
    // the rawfile fd
    int fd = 0;
    // the offset from where the rawfile starts in the hap
    long offset = 0;
    // the length of the rawfile in the hap
    long length = 0;
};

class ResourceAdapter : public virtual AceType {
    DECLARE_ACE_TYPE(ResourceAdapter, AceType);

public:
    ResourceAdapter() = default;
    ~ResourceAdapter() override = default;

    static RefPtr<ResourceAdapter> Create();
    static RefPtr<ResourceAdapter> CreateV2();

    virtual void Init(const ResourceInfo& resourceInfo) {}

    virtual void UpdateConfig(const ResourceConfiguration& config, bool themeFlag = false) {}

    virtual RefPtr<ThemeStyle> GetTheme(int32_t themeId)
    {
        return nullptr;
    }

    virtual Color GetColor(uint32_t resId) = 0;

    virtual Color GetColorByName(const std::string& resName)
    {
        return {};
    }

    virtual Dimension GetDimension(uint32_t resId) = 0;

    virtual Dimension GetDimensionByName(const std::string& resName)
    {
        return {};
    }

    virtual std::string GetString(uint32_t resId) = 0;

    virtual std::string GetStringByName(const std::string& resName)
    {
        return {};
    }

    virtual std::vector<std::string> GetStringArray(uint32_t resId) const = 0;

    virtual std::vector<std::string> GetStringArrayByName(const std::string& resName) const
    {
        return {};
    }

    virtual double GetDouble(uint32_t resId) = 0;

    virtual double GetDoubleByName(const std::string& resName)
    {
        return 0.0;
    }

    virtual int32_t GetInt(uint32_t resId) = 0;

    virtual int32_t GetIntByName(const std::string& resName)
    {
        return 0;
    }

    virtual std::string GetPluralString(uint32_t resId, int quantity)
    {
        return {};
    }

    virtual std::string GetPluralStringByName(const std::string& resName, int quantity)
    {
        return {};
    }

    virtual std::shared_ptr<Media::PixelMap> GetPixelMap(uint32_t resId)
    {
        return nullptr;
    }

    virtual std::string GetMediaPath(uint32_t resId)
    {
        return {};
    }

    virtual std::string GetMediaPathByName(const std::string& resName)
    {
        return {};
    }

    virtual std::string GetRawfile(const std::string& fileName)
    {
        return {};
    }

    virtual bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        return false;
    }

    virtual bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName)
    {
        return false;
    }

    virtual bool GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        return false;
    }

    virtual bool GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName)
    {
        return false;
    }

    virtual bool GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        return false;
    }

    virtual bool GetMediaData(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName)
    {
        return false;
    }

    virtual bool GetBoolean(uint32_t resId) const
    {
        return false;
    }

    virtual bool GetBooleanByName(const std::string& resName) const
    {
        return false;
    }

    virtual std::vector<uint32_t> GetIntArray(uint32_t resId) const
    {
        return {};
    }

    virtual std::vector<uint32_t> GetIntArrayByName(const std::string& resName) const
    {
        return {};
    }

    virtual bool GetResource(uint32_t resId, std::ostream& dest) const
    {
        return false;
    }

    virtual bool GetResource(const std::string& resId, std::ostream& dest) const
    {
        return false;
    }

    virtual bool GetIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const
    {
        return false;
    }

    virtual void UpdateResourceManager(const std::string& bundleName, const std::string& moduleName) {}

    virtual bool CloseRawFileDescription(const std::string& rawfileName) const
    {
        return false;
    }

    virtual bool GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
    {
        return false;
    }

    /*
     * Get rawfile file description which will not be cached.
     * NOTE: false value will be returned if not found.
     * @param[in] rawfileName Target rawfile.
     * @return success or not to close file info.
     */
    virtual bool GetRawFD(const std::string& /* rawfileName */, RawfileDescription& /* rawfileDescription */) const
    {
        return false;
    }

    virtual bool GetMediaById(const int32_t& resId, std::string& mediaPath) const
    {
        return false;
    }

    virtual uint32_t GetResourceLimitKeys() const
    {
        return 0;
    }

    virtual uint32_t GetSymbolByName(const char *name) const
    {
        return -1;
    }

    virtual uint32_t GetSymbolById(uint32_t resId) const
    {
        return -1;
    }

    virtual RefPtr<ThemeStyle> GetPatternByName(const std::string& patternName)
    {
        return nullptr;
    }

    static RefPtr<ResourceAdapter> CreateNewResourceAdapter(
        const std::string& bundleName, const std::string& moduleName);

    virtual void UpdateColorMode(ColorMode colorMode) {}

    virtual ColorMode GetResourceColorMode() const
    {
        return ColorMode::LIGHT;
    }

    virtual RefPtr<ResourceAdapter> GetOverrideResourceAdapter(
        const ResourceConfiguration& config, const ConfigurationChange& configurationChange)
    {
        return nullptr;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H
