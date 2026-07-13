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

#include "base/resource/asset_manager.h"
#include "base/utils/resource_configuration.h"
#include "core/components/theme/resource_adapter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {

// Don't use Color::BLACK in case Color haven't been initialized.
const Color ERROR_VALUE_COLOR = Color(0xff000000);
constexpr Dimension ERROR_VALUE_DIMENSION = 0.0_vp;
constexpr int32_t ERROR_VALUE_INT = 0;
constexpr uint32_t ERROR_VALUE_UINT = 0;
constexpr double ERROR_VALUE_DOUBLE = 0.0;
constexpr InternalResource::ResourceId ERROR_VALUE_RESOURCE_ID = InternalResource::ResourceId::NO_ID;
const Color TRANSPARENT_BG_COLOR = Color::FromRGBO(0, 0, 0, 0.2);
// For global resource manager system, system resource id is in [0x7000000, 0x7ffffff],
// and the id of resource defined by developer in the "resource" directory is greater than or equal to 0x1000000.
constexpr uint32_t GLOBAL_RESOURCE_ID_START = 0x1000000;

bool IsGlobalResource(uint32_t resId)
{
    return resId >= GLOBAL_RESOURCE_ID_START;
}

} // namespace

ThemeConstants::ThemeConstants(RefPtr<ResourceAdapter> resourceAdapter) : resAdapter_(resourceAdapter) {}

ThemeConstants::~ThemeConstants() = default;

void ThemeConstants::InitResource(const ResourceInfo& resourceInfo)
{
    if (resAdapter_) {
        resAdapter_->Init(resourceInfo);
    }
}

void ThemeConstants::UpdateConfig(const ResourceConfiguration& config)
{
    if (resAdapter_) {
        resAdapter_->UpdateConfig(config);
    }
}

RefPtr<ThemeStyle> ThemeConstants::GetThemeStyle() const
{
    return currentThemeStyle_;
}

void ThemeConstants::UpdateThemeConstants(const std::string& bundleName, const std::string& moduleName)
{
    if (resAdapter_) {
        resAdapter_->UpdateResourceManager(bundleName, moduleName);
    }
}

void ThemeConstants::UpdateResourceAdapter(const RefPtr<ResourceAdapter>& adapter)
{
    resAdapter_ = adapter;
}

uint32_t ThemeConstants::GetResourceLimitKeys() const
{
    CHECK_NULL_RETURN(resAdapter_, 0);
    return resAdapter_->GetResourceLimitKeys();
}

RefPtr<ResourceAdapter> ThemeConstants::GetResourceAdapter()
{
    return resAdapter_;
}

bool ThemeConstants::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetRawFileData(rawFile, len, dest);
}

bool ThemeConstants::GetRawFileData(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetRawFileData(rawFile, len, dest, bundleName, moduleName);
}

template<class T>
bool ThemeConstants::GetMediaResource(T& resId, std::ostream& dest) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetResource(resId, dest);
}

template<class T>
bool ThemeConstants::GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetMediaData(resId, len, dest);
}

template<class T>
bool ThemeConstants::GetMediaData(T& resId, size_t& len, std::unique_ptr<uint8_t[]>& dest,
    const std::string& bundleName, const std::string& moduleName)
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetMediaData(resId, len, dest, bundleName, moduleName);
}

template bool ThemeConstants::GetMediaResource<uint32_t>(uint32_t&, std::ostream&) const;
template bool ThemeConstants::GetMediaResource<std::string>(std::string&, std::ostream&) const;
template bool ThemeConstants::GetMediaData<uint32_t>(uint32_t&, size_t&, std::unique_ptr<uint8_t[]>&);
template bool ThemeConstants::GetMediaData<std::string>(std::string&, size_t&, std::unique_ptr<uint8_t[]>&);
template bool ThemeConstants::GetMediaData<uint32_t>(uint32_t&, size_t&, std::unique_ptr<uint8_t[]>&,
    const std::string&, const std::string&);
template bool ThemeConstants::GetMediaData<std::string>(std::string&, size_t&, std::unique_ptr<uint8_t[]>&,
    const std::string&, const std::string&);

Color ThemeConstants::GetColor(uint32_t key) const
{
    if (!IsGlobalResource(key) || !resAdapter_) {
        return ERROR_VALUE_COLOR;
    }
    return resAdapter_->GetColor(key);
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
    if (!IsGlobalResource(key) || !resAdapter_) {
        return ERROR_VALUE_DIMENSION;
    }
    auto result = resAdapter_->GetDimension(key);
    if (NearZero(result.Value())) {
        result = StringUtils::StringToDimension(resAdapter_->GetString(key));
    }
    return result;
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
    if (!IsGlobalResource(key) || !resAdapter_) {
        return ERROR_VALUE_INT;
    }
    return resAdapter_->GetInt(key);
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
    if (!IsGlobalResource(key) || !resAdapter_) {
        return ERROR_VALUE_DOUBLE;
    }
    return resAdapter_->GetDouble(key);
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
    if (!IsGlobalResource(key) || !resAdapter_) {
        return "";
    }
    return resAdapter_->GetString(key);
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
    if (!IsGlobalResource(key) || !resAdapter_) {
        return "";
    }
    return resAdapter_->GetPluralString(key, count);
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

bool ThemeConstants::GetRawFD(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    if (!resAdapter_) {
        return false;
    }
    return resAdapter_->GetRawFD(rawfileName, rawfileDescription);
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

uint32_t ThemeConstants::GetSymbolById(uint32_t resId) const
{
    if (!resAdapter_) {
        return ERROR_VALUE_UINT;
    }
    return resAdapter_->GetSymbolById(resId);
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

InternalResource::ResourceId ThemeConstants::GetResourceId(uint32_t) const
{
    return ERROR_VALUE_RESOURCE_ID;
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

RefPtr<ThemeStyle> ThemeConstants::GetPatternByName(const std::string& patternName)
{
    // if LocalColorMode is different from SystemColorMode, GetPattern from SysResMgr directly by LocolColorMode
    if (auto pipelineContext = NG::PipelineContext::GetCurrentContext(); pipelineContext) {
        ColorMode systemMode = pipelineContext->GetColorMode();
        ColorMode localMode = pipelineContext->GetLocalColorMode();
        if (localMode != ColorMode::COLOR_MODE_UNDEFINED && localMode != systemMode) {
            // currentThemeStyle_ contains patterns for different color scheme, so need to get pattern from resAdapter_
            auto patternStyle = resAdapter_ ? resAdapter_->GetPatternByName(patternName) : nullptr;
            if (patternStyle != nullptr) {
                return patternStyle;
            }
        }
    }

    if (!currentThemeStyle_) {
        TAG_LOGE(AceLogTag::ACE_THEME, "Get theme by name error: currentThemeStyle_ is null");
        return nullptr;
    }
    currentThemeStyle_->CheckThemeStyleLoaded(patternName);
    auto patternStyle = currentThemeStyle_->GetAttr<RefPtr<ThemeStyle>>(patternName, nullptr);
    if (!patternStyle && resAdapter_) {
        patternStyle = resAdapter_->GetPatternByName(patternName);
        ResValueWrapper value = { .type = ThemeConstantsType::PATTERN,
            .value = patternStyle };
        currentThemeStyle_->SetAttr(patternName, value);
    }
    return patternStyle;
}

} // namespace OHOS::Ace
