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

#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace {

const std::unordered_map<BlurStyle, std::string> BlurStyleTheme::validBlurStyles_ = {
    { BlurStyle::THIN, "thin" },
    { BlurStyle::REGULAR, "regular" },
    { BlurStyle::THICK, "thick" },
    { BlurStyle::BACKGROUND_THIN, "background_thin" },
    { BlurStyle::BACKGROUND_REGULAR, "background_regular" },
    { BlurStyle::BACKGROUND_THICK, "background_thick" },
    { BlurStyle::BACKGROUND_ULTRA_THICK, "background_ultra_thick" },
    { BlurStyle::COMPONENT_ULTRA_THIN, "component_ultra_thin" },
    { BlurStyle::COMPONENT_THIN, "component_thin" },
    { BlurStyle::COMPONENT_REGULAR, "component_regular" },
    { BlurStyle::COMPONENT_THICK, "component_thick" },
    { BlurStyle::COMPONENT_ULTRA_THICK, "component_ultra_thick" },
    { BlurStyle::COMPONENT_ULTRA_THICK_WINDOW, "component_ultra_thick_window" }
};

RefPtr<BlurStyleTheme> BlurStyleTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<BlurStyleTheme> theme = AceType::MakeRefPtr<BlurStyleTheme>();
    CHECK_NULL_RETURN(themeConstants, theme);
    RefPtr<ThemeStyle> blurTheme = themeConstants->GetPatternByName(THEME_BLUR_STYLE_COMMON);
    if (!blurTheme) {
        TAG_LOGW(AceLogTag::ACE_THEME, "find pattern of blur style fail");
        return theme;
    }
    theme->SetThemeStyle(blurTheme);
    return theme;
}

void BlurStyleTheme::SetThemeStyle(const RefPtr<ThemeStyle>& themeStyle)
{
    themeStyle_ = themeStyle;
}

BlurParameter BlurStyleTheme::ParseBlurParam(
    const RefPtr<ThemeStyle>& themeStyle, const std::string& styleName, bool isDark) const
{
    constexpr char prefix[] = "blur_style";
    constexpr char radiusName[] = "radius";
    constexpr char saturationName[] = "saturation";
    constexpr char brightnessName[] = "brightness";
    constexpr char maskColorName[] = "color";
    constexpr char darkSuffix[] = "_dark";
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

std::optional<BlurParameter> BlurStyleTheme::GetBlurParameter(BlurStyle style, ThemeColorMode colorMode)
{
    auto key = GetKeyOfBlurStyle(style, colorMode);
    auto iter = blurParams_.find(key);
    if (iter != blurParams_.end()) {
        return std::optional<BlurParameter>(iter->second);
    }
    auto blurIter = validBlurStyles_.find(style);
    if (blurIter == validBlurStyles_.end() || !themeStyle_) {
        return std::nullopt;
    }
    auto blur = ParseBlurParam(themeStyle_, blurIter->second, colorMode == ThemeColorMode::DARK);
    blurParams_.emplace(key, blur);
    return blur;
}
} // namespace OHOS::Ace
