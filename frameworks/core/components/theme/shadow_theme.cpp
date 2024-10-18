/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components/theme/shadow_theme.h"

namespace OHOS::Ace {
const std::unordered_map<ShadowStyle, std::string> ShadowTheme::validShadowStyles_ = {
    { ShadowStyle::OuterDefaultXS, "default_xs" }, { ShadowStyle::OuterDefaultSM, "default_sm" },
    { ShadowStyle::OuterDefaultMD, "default_md" }, { ShadowStyle::OuterDefaultLG, "default_lg" },
    { ShadowStyle::OuterFloatingSM, "floating_sm" }, { ShadowStyle::OuterFloatingMD, "floating_md" }
};

RefPtr<ShadowTheme> ShadowTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants)
{
    RefPtr<ShadowTheme> theme = AceType::MakeRefPtr<ShadowTheme>();
    CHECK_NULL_RETURN(themeConstants, theme);
    RefPtr<ThemeStyle> shadowTheme = themeConstants->GetPatternByName(THEME_PATTERN_SHADOW);
    if (!shadowTheme) {
        TAG_LOGW(AceLogTag::ACE_THEME, "find pattern of shadow fail");
        return theme;
    }
    theme->SetThemeStyle(shadowTheme);
    return theme;
}

Shadow ShadowTheme::GetShadow(ShadowStyle style, ColorMode colorMode)
{
    auto key = GetKeyOfShadowStyle(style, colorMode);
    auto iter = shadowStyles_.find(key);
    if (iter != shadowStyles_.end()) {
        return iter->second;
    }
    auto shadowIter = validShadowStyles_.find(style);
    if (shadowIter == validShadowStyles_.end() || !themeStyle_) {
        return Shadow();
    }
    auto shadow = ParseShadowParam(themeStyle_, style, shadowIter->second, colorMode == ColorMode::DARK);
    shadowStyles_.emplace(key, shadow);
    return shadow;
}

void ShadowTheme::SetThemeStyle(const RefPtr<ThemeStyle>& themeStyle)
{
    themeStyle_ = themeStyle;
}

uint32_t ShadowTheme::GetKeyOfShadowStyle(ShadowStyle style, ColorMode colorMode)
{
    return (static_cast<uint32_t>(colorMode) << 8) + static_cast<uint32_t>(style); // can hold 2^8 shadowStyle enums
}

Shadow ShadowTheme::ParseShadowParam(
    const RefPtr<ThemeStyle>& themeStyle, ShadowStyle shadowStyle, const std::string& name, bool isDark)
{
    // shadow_style_floating_sm_shadow prefix + name +
    const std::string prefix = std::string("shadow_style_") + name;
    const char* attrs[] = { "_shadow", "_offset_x", "_offset_y", "_color", "_radius" };
    const std::string suffix = isDark ? "_dark" : "";

    Shadow shadow;

    auto elevationName = prefix + std::string(attrs[0]) + suffix;
    auto elevation = themeStyle->GetAttr<double>(elevationName, 0.0);

    auto offsetXName = prefix + std::string(attrs[1]) + suffix;
    auto offsetX = themeStyle->GetAttr<double>(offsetXName, 0.0);
    auto offsetYName = prefix + std::string(attrs[2]) + suffix;
    auto offsetY = themeStyle->GetAttr<double>(offsetYName, 0.0);
    Offset offset(offsetX, offsetY);

    auto colorName = prefix + std::string(attrs[3]) + suffix;
    auto color = themeStyle->GetAttr<Color>(colorName, Color());
    auto radiusName =  prefix + std::string(attrs[4]) + suffix;
    auto radius  =  themeStyle->GetAttr<double>(radiusName, 0.0);
    if (radius != 0.0) {
        return Shadow(radius, offset, color, shadowStyle);
    }
    return Shadow(static_cast<float>(elevation), offset, color, shadowStyle);
}

} // namespace OHOS::Ace
