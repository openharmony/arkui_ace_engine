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

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ResourceWrapper : public AceType {
    DECLARE_ACE_TYPE(ResourceWrapper, AceType);

public:
    ResourceWrapper(RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter)
        : themeConstants_(themeConstants), resourceAdapter_(resourceAdapter) {};
    ResourceWrapper(
        RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter, ColorMode colorMode);
    ~ResourceWrapper() override;

    Color GetColor(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetColor(key);
        }
        return themeConstants_->GetColor(key);
    }

    Color GetColorByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetColorByName(resName);
        }
        return themeConstants_->GetColorByName(resName);
    }

    Dimension GetDimension(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetDimension(key);
        }
        return themeConstants_->GetDimension(key);
    }

    Dimension GetDimensionByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetDimensionByName(resName);
        }
        return themeConstants_->GetDimensionByName(resName);
    }

    int32_t GetInt(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetInt(key);
        }
        return themeConstants_->GetInt(key);
    }

    int32_t GetIntByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetIntByName(resName);
        }
        return themeConstants_->GetIntByName(resName);
    }

    double GetDouble(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetDouble(key);
        }
        return themeConstants_->GetDouble(key);
    }

    double GetDoubleByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetDoubleByName(resName);
        }
        return themeConstants_->GetDoubleByName(resName);
    }

    std::string GetString(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetString(key);
        }
        return themeConstants_->GetString(key);
    }

    std::string GetStringByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetStringByName(resName);
        }
        return themeConstants_->GetStringByName(resName);
    }

    std::string GetPluralString(uint32_t key, int count) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetPluralString(key, count);
        }
        return themeConstants_->GetPluralString(key, count);
    }

    std::string GetPluralStringByName(const std::string& resName, int count) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetPluralStringByName(resName, count);
        }
        return themeConstants_->GetPluralStringByName(resName, count);
    }

    bool GetBoolean(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetBoolean(key);
        }
        return themeConstants_->GetBoolean(key);
    }

    bool GetBooleanByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetBooleanByName(resName);
        }
        return themeConstants_->GetBooleanByName(resName);
    }

    std::vector<uint32_t> GetIntArray(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetIntArray(key);
        }
        return themeConstants_->GetIntArray(key);
    }

    std::vector<uint32_t> GetIntArrayByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetIntArrayByName(resName);
        }
        return themeConstants_->GetIntArrayByName(resName);
    }

    std::shared_ptr<Media::PixelMap> GetPixelMap(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetPixelMap(key);
        }
        return themeConstants_->GetPixelMap(key);
    }

    std::vector<std::string> GetStringArray(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetStringArray(key);
        }
        return themeConstants_->GetStringArray(key);
    }

    std::vector<std::string> GetStringArrayByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetStringArrayByName(resName);
        }
        return themeConstants_->GetStringArrayByName(resName);
    }

    std::string GetMediaPath(uint32_t key) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetMediaPath(key);
        }
        return themeConstants_->GetMediaPath(key);
    }

    std::string GetMediaPathByName(const std::string& resName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetMediaPathByName(resName);
        }
        return themeConstants_->GetMediaPathByName(resName);
    }

    std::string GetRawfile(const std::string& fileName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetRawfile(fileName);
        }
        return themeConstants_->GetRawfile(fileName);
    }

    bool GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetRawFileDescription(rawfileName, rawfileDescription);
        }
        return themeConstants_->GetRawFileDescription(rawfileName, rawfileDescription);
    }

    bool CloseRawFileDescription(const std::string& rawfileName) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->CloseRawFileDescription(rawfileName);
        }
        return themeConstants_->CloseRawFileDescription(rawfileName);
    }

    bool GetMediaById(const int32_t& resId, std::string& mediaPath) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetMediaById(resId, mediaPath);
        }
        return themeConstants_->GetMediaById(resId, mediaPath);
    }

    template<class T>
    bool GetMediaResource(T& resId, std::ostream& dest) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetResource(resId, dest);
        }
        return themeConstants_->GetMediaResource<T>(resId, dest);
    }

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetMediaData(resId, len, dest);
        }
        return themeConstants_->GetMediaData<T>(resId, len, dest);
    }

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest, const std::string& bundleName,
        const std::string& moduleName)
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetMediaData(resId, len, dest, bundleName, moduleName);
        }
        return themeConstants_->GetMediaData<T>(resId, len, dest, bundleName, moduleName);
    }

    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetRawFileData(rawFile, len, dest);
        }
        return themeConstants_->GetRawFileData(rawFile, len, dest);
    }

    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName)
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
        }
        return themeConstants_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
    }

    bool GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const
    {
        if (SystemProperties::GetResourceDecoupling()) {
            return resourceAdapter_->GetIdByName(resName, resType, resId);
        }
        return themeConstants_->GetResourceIdByName(resName, resType, resId);
    }

    uint32_t GetSymbolByName(const char *name) const
    {
        return resourceAdapter_->GetSymbolByName(name);
    }

    uint32_t GetSymbolById(uint32_t resId) const
    {
        return resourceAdapter_->GetSymbolById(resId);
    }

private:
    RefPtr<ThemeConstants> themeConstants_;
    RefPtr<ResourceAdapter> resourceAdapter_;
    ColorMode localColorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};
} // namespace OHOS::Ace

#endif