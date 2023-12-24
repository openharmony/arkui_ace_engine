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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_SHADOW_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_SHADOW_THEME_H

#include <string>
#include "theme_attributes.h"

#include "base/utils/device_config.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

enum class BlurStyle;
enum class ThemeColorMode;

class ShadowTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ShadowTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<ShadowTheme> Build(const RefPtr<ThemeConstants>& themeConstants)
        {
            RefPtr<ShadowTheme> theme = AceType::Claim(new ShadowTheme());
            CHECK_NULL_RETURN(themeConstants, theme);
            auto themeStyle = themeConstants->GetThemeStyle();
            CHECK_NULL_RETURN(themeStyle, theme);
            auto shadowTheme = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SHADOW, nullptr);
            if (!shadowTheme) {
                TAG_LOGW(AceLogTag::ACE_THEME, "find pattern of shadow fail");
                return theme;
            }
            ParsePattern(shadowTheme, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ShadowTheme>& theme)
        {
            std::unordered_map<ShadowStyle, std::string> shadowStyles { { ShadowStyle::OuterDefaultXS, "default_xs" },
                { ShadowStyle::OuterDefaultSM, "default_sm" }, { ShadowStyle::OuterDefaultMD, "default_md" },
                { ShadowStyle::OuterDefaultLG, "default_lg" }, { ShadowStyle::OuterFloatingSM, "floating_sm" },
                { ShadowStyle::OuterFloatingMD, "floating_md" } };

            for (auto iter = shadowStyles.begin(); iter != shadowStyles.end(); ++iter) {
                auto shadowDark = ParseShadowParam(themeStyle, iter->first, iter->second, true);
                auto shadowLight = ParseShadowParam(themeStyle, iter->first, iter->second, false);
                theme->shadowStyles_.emplace(GetKeyOfShadowStyle(iter->first, ColorMode::DARK), shadowDark);
                theme->shadowStyles_.emplace(GetKeyOfShadowStyle(iter->first, ColorMode::LIGHT), shadowLight);
            }
        }

        Shadow ParseShadowParam(
            const RefPtr<ThemeStyle>& themeStyle, ShadowStyle shadowStyle, const std::string& name, bool isDark)
        {
            const std::string prefix = std::string("shadow_style_") + name;
            const char* attrs[] = { "_shadow", "_offset_x", "_offset_y", "_color" };
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
            
            return Shadow(elevation, offset, color, shadowStyle);
        }
    };
    ~ShadowTheme() override = default;
    Shadow GetShadow(ShadowStyle style, ColorMode colorMode) const
    {
        auto key = GetKeyOfShadowStyle(style, colorMode);
        auto iter = shadowStyles_.find(key);
        return iter != shadowStyles_.end() ? iter->second : Shadow();
    }

protected:
    ShadowTheme() = default;

private:
    static uint32_t GetKeyOfShadowStyle(ShadowStyle style, ColorMode colorMode)
    {
        return (static_cast<uint32_t>(colorMode) << 8) + static_cast<uint32_t>(style); // can hold 2^8 shadowStyle enums
    }

    std::unordered_map<uint32_t, Shadow> shadowStyles_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_BLUR_STYLE_THEME_H
