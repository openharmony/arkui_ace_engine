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

#include "core/components/theme/theme_constants.h"

#include "base/resource/ace_res_config.h"

namespace OHOS::Ace {
namespace {

const ResValueWrapper ERROR_VALUE = { .type = ThemeConstantsType::ERROR };
// Don't use Color::BLACK in case Color haven't been initialized.
const Color ERROR_VALUE_COLOR = Color(0xff000000);
constexpr Dimension ERROR_VALUE_DIMENSION = 0.0_vp;
constexpr int32_t ERROR_VALUE_INT = 0;
constexpr uint32_t ERROR_VALUE_UINT = 0;
constexpr double ERROR_VALUE_DOUBLE = 0.0;
constexpr double BLEND_ALPHA_MAX = 1.0;
constexpr InternalResource::ResourceId ERROR_VALUE_RESOURCE_ID = InternalResource::ResourceId::NO_ID;
const char STYLES_FOLDER_PATH[] = "resources/styles/";
const char FILE_TYPE_JSON[] = ".json";
const char CUSTOM_STYLE_ROOT_NAME[] = "style";
const Color TRANSPARENT_BG_COLOR = Color::FromRGBO(0, 0, 0, 0.2);
// For global resource manager system, system resource id is in [0x7000000, 0x7ffffff],
// and the id of resource defined by developer in the "resource" directory is greater than or equal to 0x1000000.
constexpr uint32_t GLOBAL_RESOURCE_ID_START = 0x1000000;

DeviceType g_deviceType = DeviceType::PHONE;

// Check whether value is match with expected type
bool ValueTypeMatch(const ResValueWrapper& valueWrapper, uint32_t key, const ThemeConstantsType& expectType)
{
    if (valueWrapper.type == ThemeConstantsType::ERROR) {
        return false;
    }
    if (valueWrapper.type != expectType) {
        return false;
    }
    return true;
}

bool IsGlobalResource(uint32_t resId)
{
    return resId >= GLOBAL_RESOURCE_ID_START;
}

} // namespace

void ThemeConstants::InitDeviceType()
{
    g_deviceType = SystemProperties::GetDeviceType();
}

const ResValueWrapper* ThemeConstants::GetPlatformConstants(uint32_t key)
{
#ifdef WEARABLE_PRODUCT
    if (g_deviceType == DeviceType::WATCH && key < ThemeConstants::WatchMapCount &&
        ThemeConstants::styleMapWatch[key] != nullptr) {
        return ThemeConstants::styleMapWatch[key];
    }
#else
    if (g_deviceType == DeviceType::TV && key < ThemeConstants::TvMapCount &&
        ThemeConstants::styleMapTv[key] != nullptr) {
        return ThemeConstants::styleMapTv[key];
    }
#endif
    if (key < ThemeConstants::DefaultMapCount) {
        return ThemeConstants::styleMapDefault[key];
    }
    return nullptr;
}

Color ThemeConstants::GetColor(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return ERROR_VALUE_COLOR;
        }
        return resAdapter_->GetColor(key);
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::COLOR)) {
        return ERROR_VALUE_COLOR;
    }
    auto colorPair = valueWrapper.GetValue<Color>(ERROR_VALUE_COLOR);
    if (!colorPair.first) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Get theme color error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return colorPair.second;
}

Color ThemeConstants::GetColorByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_COLOR;
    }
    return resAdapter_->GetColorByName(resName);
}

Dimension ThemeConstants::GetDimension(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return ERROR_VALUE_DIMENSION;
        }
        auto result = resAdapter_->GetDimension(key);
        if (NearZero(result.Value())) {
            result = StringUtils::StringToDimension(resAdapter_->GetString(key));
        }
        return result;
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::DIMENSION)) {
        return ERROR_VALUE_DIMENSION;
    }
    auto dimensionPair = valueWrapper.GetValue<Dimension>(ERROR_VALUE_DIMENSION);
    if (!dimensionPair.first) {
        TAG_LOGW(
            AceLogTag::ACE_THEME, "Get theme dimension error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return dimensionPair.second;
}

Dimension ThemeConstants::GetDimensionByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_DIMENSION;
    }
    auto result = resAdapter_->GetDimensionByName(resName);
    if (NearZero(result.Value())) {
        result = StringUtils::StringToDimension(resAdapter_->GetStringByName(resName));
    }
    return result;
}

int32_t ThemeConstants::GetInt(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return ERROR_VALUE_INT;
        }
        return resAdapter_->GetInt(key);
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::INT)) {
        return ERROR_VALUE_INT;
    }
    auto intPair = valueWrapper.GetValue<int32_t>(ERROR_VALUE_INT);
    if (!intPair.first) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Get theme int error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return intPair.second;
}

int32_t ThemeConstants::GetIntByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_INT;
    }
    return resAdapter_->GetIntByName(resName);
}

double ThemeConstants::GetDouble(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return ERROR_VALUE_DOUBLE;
        }
        return resAdapter_->GetDouble(key);
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::DOUBLE)) {
        return ERROR_VALUE_DOUBLE;
    }
    auto doublePair = valueWrapper.GetValue<double>(ERROR_VALUE_DOUBLE);
    if (!doublePair.first) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Get theme double error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return doublePair.second;
}

double ThemeConstants::GetDoubleByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_DOUBLE;
    }
    return resAdapter_->GetDoubleByName(resName);
}

std::string ThemeConstants::GetString(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return "";
        }
        return resAdapter_->GetString(key);
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::STRING)) {
        return "";
    }
    auto stringPair = valueWrapper.GetValue<std::string>("");
    if (!stringPair.first) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Get theme string error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return stringPair.second;
}

std::string ThemeConstants::GetStringByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return "";
    }
    return resAdapter_->GetStringByName(resName);
}

std::string ThemeConstants::GetPluralString(uint32_t key, int count) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return "";
        }
        return resAdapter_->GetPluralString(key, count);
    }
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::STRING)) {
        return "";
    }
    auto stringPair = valueWrapper.GetValue<std::string>("");
    if (!stringPair.first) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Get theme pluralString error: %{public}u, type: %{public}u", key,
            valueWrapper.type);
    }
    return stringPair.second;
}

std::string ThemeConstants::GetPluralStringByName(const std::string& resName, int count) const
{
    if (!resAdapter_) {
        return "";
    }
    return resAdapter_->GetPluralStringByName(resName, count);
}

std::vector<std::string> ThemeConstants::GetStringArray(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return {};
        }
        return resAdapter_->GetStringArray(key);
    }
    return {};
}

std::vector<std::string> ThemeConstants::GetStringArrayByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return {};
    }
    return resAdapter_->GetStringArrayByName(resName);
}

std::string ThemeConstants::GetMediaPath(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return "";
        }
        return resAdapter_->GetMediaPath(key);
    }
    return "";
}

std::string ThemeConstants::GetMediaPathByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return "";
    }
    return resAdapter_->GetMediaPathByName(resName);
}

std::string ThemeConstants::GetRawfile(const std::string& fileName) const
{
    if (!resAdapter_) {
        return "";
    }
    return resAdapter_->GetRawfile(fileName);
}

bool ThemeConstants::GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetRawFileDescription(rawfileName, rawfileDescription);
}

bool ThemeConstants::CloseRawFileDescription(const std::string& rawfileName) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->CloseRawFileDescription(rawfileName);
}

bool ThemeConstants::GetMediaById(const int32_t& resId, std::string& mediaPath) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetMediaById(resId, mediaPath);
}

bool ThemeConstants::GetBoolean(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return false;
        }
        return resAdapter_->GetBoolean(key);
    }
    return false;
}

bool ThemeConstants::GetBooleanByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetBooleanByName(resName);
}

uint32_t ThemeConstants::GetSymbolByName(const char* name) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_UINT;
    }
    return resAdapter_->GetSymbolByName(name);
}

std::vector<uint32_t> ThemeConstants::GetIntArray(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return {};
        }
        return resAdapter_->GetIntArray(key);
    }
    return {};
}

std::vector<uint32_t> ThemeConstants::GetIntArrayByName(const std::string& resName) const
{
    if (!resAdapter_) {
        return {};
    }
    return resAdapter_->GetIntArrayByName(resName);
}

bool ThemeConstants::GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetIdByName(resName, resType, resId);
}

InternalResource::ResourceId ThemeConstants::GetResourceId(uint32_t key) const
{
    const auto& valueWrapper = GetValue(key);
    if (!ValueTypeMatch(valueWrapper, key, ThemeConstantsType::RESOURCE_ID)) {
        return ERROR_VALUE_RESOURCE_ID;
    }
    auto resPair = valueWrapper.GetValue<InternalResource::ResourceId>(ERROR_VALUE_RESOURCE_ID);
    if (!resPair.first) {
        TAG_LOGW(
            AceLogTag::ACE_THEME, "Get theme resourceId error: %{public}u, type: %{public}u", key, valueWrapper.type);
    }
    return resPair.second;
}

std::shared_ptr<Media::PixelMap> ThemeConstants::GetPixelMap(uint32_t key) const
{
    if (IsGlobalResource(key)) {
        if (!resAdapter_) {
            return nullptr;
        }
        return resAdapter_->GetPixelMap(key);
    }
    return nullptr;
}

ResValueWrapper ThemeConstants::GetValue(uint32_t key) const
{
    // Find resource at custom styles.
    auto customIter = customStyleMap_.find(key);
    if (customIter != customStyleMap_.end()) {
        return customIter->second;
    }
    // Find resource at prebuilt maps.
    const auto platformConstants = ThemeConstants::GetPlatformConstants(key);
    if (platformConstants == nullptr) {
        return ERROR_VALUE;
    }
    if (platformConstants->type != ThemeConstantsType::REFERENCE) {
        return *platformConstants;
    }
    // This value point to another style, recursively find target.
    auto uintPtr = std::get_if<uint32_t>(&(platformConstants->value));
    if (!uintPtr) {
        return ERROR_VALUE;
    }
    // Copy reference value, blend alpha if need(reference color and current blendAlpha < 1.0).
    auto refValue = GetValue(*uintPtr);
    refValue.isPublic = platformConstants->isPublic;
    auto blendAlpha = GetBlendAlpha(platformConstants->blendAlpha);
    if ((refValue.type == ThemeConstantsType::COLOR) && (blendAlpha < BLEND_ALPHA_MAX)) {
        auto colorPtr = std::get_if<Color>(&refValue.value);
        if (!colorPtr) {
            return ERROR_VALUE;
        }
        refValue.value = colorPtr->BlendOpacity(blendAlpha);
    }
    return refValue;
}

double ThemeConstants::GetBlendAlpha(const BlendAlpha& blendAlpha) const
{
    auto doublePtr = std::get_if<double>(&blendAlpha);
    if (doublePtr) {
        return *doublePtr;
    }
    auto idPtr = std::get_if<uint32_t>(&blendAlpha);
    if (idPtr) {
        return ThemeConstants::GetDouble(*idPtr);
    }
    return BLEND_ALPHA_MAX;
}

void ThemeConstants::LoadTheme(int32_t themeId)
{
    if (!resAdapter_) {
        return;
    }
    currentThemeStyle_ = resAdapter_->GetTheme(themeId);
    if (currentThemeStyle_) {
        currentThemeStyle_->SetName(std::to_string(themeId));
    }
}

void ThemeConstants::ParseTheme()
{
    if (currentThemeStyle_) {
        currentThemeStyle_->ParseContent();
    }
}

void ThemeConstants::LoadCustomStyle(const RefPtr<AssetManager>& assetManager)
{
    if (!assetManager) {
        return;
    }

    std::vector<std::string> files;

    assetManager->GetAssetList(STYLES_FOLDER_PATH, files);

    std::vector<std::string> fileNameList;
    for (const auto& file : files) {
        if (StringUtils::EndWith(file, FILE_TYPE_JSON)) {
            fileNameList.emplace_back(file.substr(0, file.size() - (sizeof(FILE_TYPE_JSON) - 1)));
        }
    }

    std::vector<std::string> priorityFileList;
    priorityFileList = AceResConfig::GetStyleResourceFallback(fileNameList);
    for (auto fileIter = priorityFileList.rbegin(); fileIter != priorityFileList.rend(); ++fileIter) {
        auto fileFullPath = STYLES_FOLDER_PATH + *fileIter + std::string(FILE_TYPE_JSON);
        auto asset = assetManager->GetAsset(fileFullPath);
        ThemeConstants::LoadFile(asset);
    }
}

void ThemeConstants::ParseCustomStyle(const std::string& content)
{
    auto rootJson = JsonUtil::ParseJsonString(content);
    auto rootNode = rootJson->GetObject(CUSTOM_STYLE_ROOT_NAME);
    if (rootNode->IsNull()) {
        return;
    }
    auto child = rootNode->GetChild();
    while (child && !child->IsNull()) {
        const auto& key = child->GetKey();
        const auto& value = child->GetString();
        child = child->GetNext();
        uint32_t styleId = StringUtils::StringToUint(key, UINT32_MAX);
        if (styleId == UINT32_MAX) {
            // Id format error.
            continue;
        }
        const auto& oldValue = ThemeConstants::GetValue(styleId);
        if (oldValue.type == ThemeConstantsType::ERROR) {
            // Id not found.
            continue;
        }
        if (!oldValue.isPublic) {
            // Id is not public.
            continue;
        }
        const auto& newValue = ThemeUtils::ParseStyleValue(styleId, oldValue, value);
        // Replace default style with user custom style, use type to check parse success.
        if (newValue.type == oldValue.type) {
            customStyleMap_[styleId] = newValue;
        }
    }
}

void ThemeConstants::LoadFile(const RefPtr<Asset>& asset)
{
    if (!asset) {
        return;
    }

    auto fileSize = asset->GetSize();
    if (fileSize <= 0) {
        return;
    }
    const auto& fileData = asset->GetData();
    if (!fileData) {
        return;
    }
    std::string styleContent;
    styleContent.assign(fileData, fileData + fileSize);
    if (styleContent.empty()) {
        return;
    }
    ParseCustomStyle(styleContent);
}

void ThemeConstants::SetColorScheme(ColorScheme colorScheme)
{
    if (!currentThemeStyle_) {
        return;
    }
    if (colorScheme == ColorScheme::SCHEME_TRANSPARENT) {
        currentThemeStyle_->SetAttr(
            THEME_ATTR_BG_COLOR, { .type = ThemeConstantsType::COLOR, .value = TRANSPARENT_BG_COLOR });
    }
}

} // namespace OHOS::Ace
