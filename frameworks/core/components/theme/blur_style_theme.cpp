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

#include "core/components/theme/blur_style_theme.h"

#include "core/components/common/properties/blur_parameter.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/theme/theme_attributes.h"

namespace OHOS::Ace {

RefPtr<BlurStyleTheme> BlurStyleTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<BlurStyleTheme> theme = AceType::Claim(new BlurStyleTheme());
    CHECK_NULL_RETURN(themeConstants, theme);
    auto themeStyle = themeConstants->GetThemeStyle();
    CHECK_NULL_RETURN(themeStyle, theme);
    auto blurTheme = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_BLUR_STYLE_COMMON, nullptr);
    if (!blurTheme) {
        TAG_LOGW(AceLogTag::ACE_THEME, "find pattern of blur style fail");
        return theme;
    }
    ParsePattern(blurTheme, theme);
    return theme;
}

void BlurStyleTheme::Builder::ParsePattern(
    const RefPtr<ThemeStyle>& themeStyle, const RefPtr<BlurStyleTheme>& theme) const
{
    const static std::pair<std::string, BlurStyle> blurStyles[] = {
        std::pair<std::string, BlurStyle> { "thin", BlurStyle::THIN },
        std::pair<std::string, BlurStyle> { "regular", BlurStyle::REGULAR },
        std::pair<std::string, BlurStyle> { "thick", BlurStyle::THICK },
        std::pair<std::string, BlurStyle> { "background_thin", BlurStyle::BACKGROUND_THIN },
        std::pair<std::string, BlurStyle> { "background_regular", BlurStyle::BACKGROUND_REGULAR },
        std::pair<std::string, BlurStyle> { "background_thick", BlurStyle::BACKGROUND_THICK },
        std::pair<std::string, BlurStyle> { "background_ultra_thick", BlurStyle::BACKGROUND_ULTRA_THICK },
        std::pair<std::string, BlurStyle> { "component_ultra_thin", BlurStyle::COMPONENT_ULTRA_THIN },
        std::pair<std::string, BlurStyle> { "component_thin", BlurStyle::COMPONENT_THIN },
        std::pair<std::string, BlurStyle> { "component_regular", BlurStyle::COMPONENT_REGULAR },
        std::pair<std::string, BlurStyle> { "component_thick", BlurStyle::COMPONENT_THICK },
        std::pair<std::string, BlurStyle> { "component_ultra_thick", BlurStyle::COMPONENT_ULTRA_THICK },
    };
    const auto length = sizeof(blurStyles) / sizeof(std::pair<std::string, BlurStyle>);
    for (size_t i = 0; i != length; ++i) {
        auto blurParamLight = ParseBlurParam(themeStyle, blurStyles[i].first, false);
        auto blurParamDark = ParseBlurParam(themeStyle, blurStyles[i].first, true);
        theme->blurParams_.emplace(GetKeyOfBlurStyle(blurStyles[i].second, ThemeColorMode::LIGHT), blurParamLight);
        theme->blurParams_.emplace(GetKeyOfBlurStyle(blurStyles[i].second, ThemeColorMode::DARK), blurParamDark);
    }
}

BlurParameter BlurStyleTheme::Builder::ParseBlurParam(
    const RefPtr<ThemeStyle>& themeStyle, const std::string& styleName, bool isDark) const
{
    constexpr static char prefix[] = "blur_style";
    constexpr static char radiusName[] = "radius";
    constexpr static char saturationName[] = "saturation";
    constexpr static char brightnessName[] = "brightness";
    constexpr static char maskColorName[] = "color";
    constexpr static char darkSuffix[] = "_dark";
    BlurParameter param;
    auto radiusFullName = std::string(prefix) + "_" + styleName + "_" + radiusName;
    auto saturationFullName = std::string(prefix) + "_" + styleName + "_" + saturationName;
    auto brightnessFullName = std::string(prefix) + "_" + styleName + "_" + brightnessName;
    auto maskColorFullName = std::string(prefix) + "_" + styleName + "_" + maskColorName;
    if (isDark) {
        radiusFullName += darkSuffix;
        saturationFullName += darkSuffix;
        brightnessFullName += darkSuffix;
        maskColorFullName += darkSuffix;
    }
    param.radius = themeStyle->GetAttr<double>(radiusFullName, 0.0);
    param.saturation = themeStyle->GetAttr<double>(saturationFullName, 0.0);
    param.brightness = themeStyle->GetAttr<double>(brightnessFullName, 0.0);
    param.maskColor = themeStyle->GetAttr<Color>(maskColorFullName, Color::WHITE);
    return param;
}

uint32_t BlurStyleTheme::GetKeyOfBlurStyle(BlurStyle style, ThemeColorMode colorMode)
{
    return (static_cast<uint32_t>(colorMode) << 8) + static_cast<uint32_t>(style); // can hold 2^8 blurStyle enums
}

std::optional<BlurParameter> BlurStyleTheme::GetBlurParameter(BlurStyle style, ThemeColorMode colorMode) const
{
    auto key = GetKeyOfBlurStyle(style, colorMode);
    auto iter = blurParams_.find(key);
    return iter != blurParams_.end() ? std::optional<BlurParameter>(iter->second) : std::nullopt;
}
} // namespace OHOS::Ace
