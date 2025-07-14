/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "mock_theme_style.h"

namespace OHOS::Ace {
namespace {
constexpr InternalResource::ResourceId ERROR_VALUE_RESOURCE_ID = InternalResource::ResourceId::NO_ID;
constexpr double BLEND_ALPHA_MAX = 1.0;
constexpr double DIMENSION_DEFAULT = 10.0;
constexpr int32_t INT_DEFAULT = 5;
const ResValueWrapper ERROR_VALUE = { .type = ThemeConstantsType::ERROR };
} // namespace
void ThemeConstants::InitDeviceType()
{
}

const ResValueWrapper* ThemeConstants::GetPlatformConstants(uint32_t key)
{
    return nullptr;
}

Color ThemeConstants::GetColor(uint32_t key) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<Color>(std::to_string(key), Color::RED);
    }
    return Color::RED;
}

Color ThemeConstants::GetColorByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<Color>(resName, Color::RED);
    }
    return Color::RED;
}

Dimension ThemeConstants::GetDimension(uint32_t key) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<Dimension>(std::to_string(key), Dimension(DIMENSION_DEFAULT));
    }
    return Dimension(DIMENSION_DEFAULT);
}

Dimension ThemeConstants::GetDimensionByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<Dimension>(resName, Dimension(DIMENSION_DEFAULT));
    }
    return Dimension(DIMENSION_DEFAULT);
}

int32_t ThemeConstants::GetInt(uint32_t key) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<int32_t>(std::to_string(key), INT_DEFAULT);
    }
    return INT_DEFAULT;
}

int32_t ThemeConstants::GetIntByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<int32_t>(resName, 0);
    }
    return 0;
}

double ThemeConstants::GetDouble(uint32_t key) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<double>(std::to_string(key), 0.0f);
    }
    return 0;
}

double ThemeConstants::GetDoubleByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<double>(resName, 0.0f);
    }
    return 0;
}

std::string ThemeConstants::GetString(uint32_t key) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<std::string>(std::to_string(key), "");
    }
    return "";
}

std::string ThemeConstants::GetStringByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<std::string>(resName, "");
    }
    return "";
}

std::string ThemeConstants::GetPluralString(uint32_t key, int count) const
{
    return "";
}

std::string ThemeConstants::GetPluralStringByName(const std::string& resName, int count) const
{
    return "";
}

std::vector<std::string> ThemeConstants::GetStringArray(uint32_t key) const
{
    if (currentThemeStyle_) {
        auto value = currentThemeStyle_->GetAttr<std::string>(std::to_string(key), "");
        if (value.empty()) {
            return {};
        } else {
            return { value };
        }
    }
    return {};
}

std::vector<std::string> ThemeConstants::GetStringArrayByName(const std::string& resName) const
{
    if (currentThemeStyle_) {
        auto value = currentThemeStyle_->GetAttr<std::string>(resName, "");
        if (value.empty()) {
            return {};
        } else {
            return { value };
        }
    }
    return {};
}

std::string ThemeConstants::GetMediaPath(uint32_t key) const
{
    return "";
}

std::string ThemeConstants::GetMediaPathByName(const std::string& resName) const
{
    return "";
}

std::string ThemeConstants::GetRawfile(const std::string& fileName) const
{
    return "";
}

bool ThemeConstants::GetRawFileDescription(const std::string& rawfileName, RawfileDescription& rawfileDescription) const
{
    return false;
}

bool ThemeConstants::GetMediaById(const int32_t& resId, std::string& mediaPath) const
{
    return false;
}

bool ThemeConstants::GetBoolean(uint32_t key) const
{
    return false;
}

bool ThemeConstants::GetBooleanByName(const std::string& resName) const
{
    return false;
}

uint32_t ThemeConstants::GetSymbolByName(const char* name) const
{
    if (currentThemeStyle_) {
        return currentThemeStyle_->GetAttr<int32_t>(name, -1);
    }
    return -1;
}

uint32_t ThemeConstants::GetSymbolById(uint32_t resId) const
{
    return  0;
}

std::vector<uint32_t> ThemeConstants::GetIntArray(uint32_t key) const
{
    return {};
}

std::vector<uint32_t> ThemeConstants::GetIntArrayByName(const std::string& resName) const
{
    return {};
}

bool ThemeConstants::GetResourceIdByName(const std::string& resName, const std::string& resType, uint32_t& resId) const
{
    return false;
}

InternalResource::ResourceId ThemeConstants::GetResourceId(uint32_t key) const
{
    return ERROR_VALUE_RESOURCE_ID;
}

ResValueWrapper ThemeConstants::GetValue(uint32_t key) const
{
    return ERROR_VALUE;
}

double ThemeConstants::GetBlendAlpha(const BlendAlpha& blendAlpha) const
{
    return BLEND_ALPHA_MAX;
}

void ThemeConstants::LoadTheme(int32_t themeId)
{
    currentThemeStyle_ = MockThemeStyle::GetInstance();
}

void ThemeConstants::ParseTheme()
{
}

void ThemeConstants::LoadCustomStyle(const RefPtr<AssetManager>& assetManager)
{
}

void ThemeConstants::ParseCustomStyle(const std::string& content)
{
}

void ThemeConstants::LoadFile(const RefPtr<Asset>& asset)
{
}

void ThemeConstants::SetColorScheme(ColorScheme colorScheme)
{
}

RefPtr<ThemeStyle> ThemeConstants::GetPatternByName(const std::string& patternName)
{
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

std::shared_ptr<Media::PixelMap> ThemeConstants::GetPixelMap(uint32_t key) const
{
    return nullptr;
}
} // namespace OHOS::Ace
