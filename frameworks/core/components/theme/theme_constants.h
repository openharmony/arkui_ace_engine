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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_CONSTANTS_H

#include <unordered_map>

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/resource/asset_manager.h"
#include "base/resource/internal_resource.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_style.h"
namespace OHOS::Ace {

class ACE_FORCE_EXPORT ThemeConstants : public AceType {
    DECLARE_ACE_TYPE(ThemeConstants, AceType);

public:
    explicit ThemeConstants(RefPtr<ResourceAdapter> resourceAdapter) : resAdapter_(resourceAdapter) {}
    ~ThemeConstants() override = default;

    /*
     * Init properties at platform.
     */
    static void InitDeviceType();

    void InitResource(const ResourceInfo& resourceInfo)
    {
        if (resAdapter_) {
            resAdapter_->Init(resourceInfo);
        }
    }

    void UpdateConfig(const ResourceConfiguration& config)
    {
        if (resAdapter_) {
            resAdapter_->UpdateConfig(config);
        }
    }

    void ParseTheme();

    /*
     * Get color value from platform constants.
     * Color::BLACK will be returned if value not found or corresponding value is not Color.
     * @param[in] key Target color key.
     * @return Color corresponding to the key.
     */
    Color GetColor(uint32_t key) const;

    /*
     * Get color value from platform constants.
     * Color::BLACK will be returned if value not found or corresponding value is not Color.
     * @param[in] key Target color key.
     * @return Color corresponding to the name.
     */
    Color GetColorByName(const std::string& resName) const;

    /*
     * Get dimension value from platform constants.
     * Dimension with 0.0 will be returned if not found or value is not Dimension.
     * @param[in] key Target dimension key.
     * @return Dimension corresponding to the key.
     */
    Dimension GetDimension(uint32_t key) const;

    /*
     * Get dimension value from platform constants.
     * Dimension with 0.0 will be returned if not found or value is not Dimension.
     * @param[in] name Target dimension name.
     * @return Dimension corresponding to the name.
     */
    Dimension GetDimensionByName(const std::string& resName) const;

    /*
     * Get int32_t value from platform constants.
     * NOTE: -1 will be returned if not found or value is not int32_t.
     * @param[in] key Target key.
     * @return Int value corresponding to the key.
     */
    int32_t GetInt(uint32_t key) const;

    /*
     * Get int32_t value from platform constants.
     * NOTE: -1 will be returned if not found or value is not int32_t.
     * @param[in] key Target key.
     * @return Int value corresponding to the key.
     */
    int32_t GetIntByName(const std::string& resName) const;

    /*
     * Get double value from platform constants.
     * NOTE: 0.0 will be returned if not found or value is not double.
     * @param[in] key Target key.
     * @return Double value corresponding to the key.
     */
    double GetDouble(uint32_t key) const;

    /*
     * Get double value from platform constants.
     * NOTE: 0.0 will be returned if not found or value is not double.
     * @param[in] key Target key.
     * @return Double value corresponding to the key.
     */
    double GetDoubleByName(const std::string& resName) const;

    /*
     * Get string value from platform constants.
     * NOTE: empty string will be returned if not found or value is not string.
     * @param[in] key Target key.
     * @return String value corresponding to the key.
     */
    std::string GetString(uint32_t key) const;

    /*
     * Get string value from platform constants.
     * NOTE: empty string will be returned if not found or value is not string.
     * @param[in] key Target key.
     * @return String value corresponding to the key.
     */
    std::string GetStringByName(const std::string& resName) const;

    /*
     * Get plural string value from platform constants.
     * NOTE: empty string will be returned if not found.
     * @param[in] key Target key, count Target plural string quantity.
     * @return plural string value corresponding to the key and count.
     */
    std::string GetPluralString(uint32_t key, int count) const;

    /*
     * Get plural string value from platform constants.
     * NOTE: empty string will be returned if not found.
     * @param[in] key Target key, count Target plural string quantity.
     * @return plural string value corresponding to the name and count.
     */
    std::string GetPluralStringByName(const std::string& resName, int count) const;

    /*
     * Get bool value from platform constants.
     * NOTE: false will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return bool value corresponding to the key.
     */
    bool GetBoolean(uint32_t key) const;

    /*
     * Get bool value from platform constants.
     * NOTE: false will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return bool value corresponding to the name.
     */
    bool GetBooleanByName(const std::string& resName) const;

    /*
     * Get int value from platform constants.
     * NOTE: false will be returned if not found or value is not uint32_t.
     * @param[in] key Target key.
     * @return uint32_t value corresponding to the name.
     */
    uint32_t GetSymbolByName(const char *name) const;

    /*
     * Get int array value from platform constants.
     * NOTE: empty array will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return int array value corresponding to the key.
     */
    std::vector<uint32_t> GetIntArray(uint32_t key) const;

    /*
     * Get int array value from platform constants.
     * NOTE: empty array will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return int array value corresponding to the name.
     */
    std::vector<uint32_t> GetIntArrayByName(const std::string& resName) const;

    /*
     * Get ResourceId from platform constants.
     * NOTE: ResourceId::NO_ID will be returned if not found or value is not ResourceId.
     */
    InternalResource::ResourceId GetResourceId(uint32_t key) const;

    /*
     * Get PixelMap from platform constants.
     * NOTE: nullptr will be returned if getPixelMap failed.
     */
    std::shared_ptr<Media::PixelMap> GetPixelMap(uint32_t key) const;

    /*
     * Get string array value from platform constants.
     * NOTE: empty array will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return string array value corresponding to the key.
     */
    std::vector<std::string> GetStringArray(uint32_t key) const;

    /*
     * Get string array value from platform constants.
     * NOTE: empty array will be returned if not found or value is not boolean.
     * @param[in] key Target key.
     * @return string array value corresponding to the name.
     */
    std::vector<std::string> GetStringArrayByName(const std::string& resName) const;

    /*
     * Get media path value from platform constants.
     * NOTE: empty string will be returned if not found.
     * @param[in] key Target key.
     * @return media path value corresponding to the key.
     */
    std::string GetMediaPath(uint32_t key) const;

    /*
     * Get media path value from platform constants.
     * NOTE: empty string will be returned if not found.
     * @param[in] key Target key.
     * @return media path value corresponding to the name.
     */
    std::string GetMediaPathByName(const std::string& resName) const;

    /*
     * Get rawfile path.
     * NOTE: empty string will be returned if not found.
     * @param[in] fileName Target file name.
     * @return rawfile path value corresponding to file name.
     */
    std::string GetRawfile(const std::string& fileName) const;

    /*
     * Get rawfile file description.
     * NOTE: false value will be returned if not found.
     * @param[in] rawfileName Target rawfile, rawfileDescription Target file info.
     * @return success or not to get file info.
     */
    bool GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const;

    /*
     * Close rawfile file description.
     * NOTE: false value will be returned if not found.
     * @param[in] rawfileName Target rawfile.
     * @return success or not to close file info.
     */
    bool CloseRawFileDescription(const std::string& rawfileName) const;

    /*
     * Get rawfile file description which will not be cached.
     * NOTE: false value will be returned if not found.
     * @param[in] rawfileName Target rawfile.
     * @return success or not to close file info.
     */
    bool GetRawFD(const std::string& rawfileName, RawfileDescription& rawfileDescription) const;

    /*
     * Get resource media file path.
     * NOTE: false value will be returned if not found.
     * @param[in] resId Target resource id, mediaPath Target media path.
     * @return success or not to get media path.
     */
    bool GetMediaById(const int32_t& resId, std::string& mediaPath) const;

    template<class T>
    bool GetMediaResource(T& resId, std::ostream& dest) const
    {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetResource(resId, dest);
    }

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetMediaData(resId, len, dest);
    }

    template<class T>
    bool GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest, const std::string& bundleName,
        const std::string& moduleName)
    {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetMediaData(resId, len, dest, bundleName, moduleName);
    }

    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
    {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetRawFileData(rawFile, len, dest);
    }

    bool GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
        const std::string& bundleName, const std::string& moduleName)
    {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
    }

    bool GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const;

    void LoadCustomStyle(const RefPtr<AssetManager>& assetManager);

    /*
     * Load theme from system resource.
     */
    void LoadTheme(int32_t themeId);

    RefPtr<ThemeStyle> GetThemeStyle() const
    {
        return currentThemeStyle_;
    }

    void SetColorScheme(ColorScheme colorScheme);

    bool HasCustomStyle(uint32_t key) const
    {
        return customStyleMap_.find(key) != customStyleMap_.end();
    }

    void UpdateThemeConstants(const std::string& bundleName, const std::string& moduleName)
    {
        if (resAdapter_) {
            resAdapter_->UpdateResourceManager(bundleName, moduleName);
        }
    }

    uint32_t GetResourceLimitKeys() const
    {
        CHECK_NULL_RETURN(resAdapter_, 0);
        return resAdapter_->GetResourceLimitKeys();
    }

    RefPtr<ResourceAdapter> GetResourceAdapter()
    {
        return resAdapter_;
    }

    RefPtr<ThemeStyle> GetPatternByName(const std::string& patternName);
private:
    static const ResValueWrapper* GetPlatformConstants(uint32_t key);
    static const ResValueWrapper* styleMapDefault[];
    static uint32_t DefaultMapCount;
    static const ResValueWrapper* styleMapWatch[];
    static uint32_t WatchMapCount;
    static const ResValueWrapper* styleMapTv[];
    static uint32_t TvMapCount;

    ResValueWrapper GetValue(uint32_t key) const;
    double GetBlendAlpha(const BlendAlpha& blendAlpha) const;
    void ParseCustomStyle(const std::string& content);
    void LoadFile(const RefPtr<Asset>& asset);

    RefPtr<ResourceAdapter> resAdapter_;
    RefPtr<ThemeStyle> currentThemeStyle_;
    ThemeConstantsMap customStyleMap_;

    ACE_DISALLOW_COPY_AND_MOVE(ThemeConstants);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_CONSTANTS_H
