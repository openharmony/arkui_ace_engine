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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SECURITY_COMPONENT_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SECURITY_COMPONENT_THEME_H

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_style.h"
#include "core/components_ng/pattern/security_component/security_component_log.h"

namespace OHOS::Ace::NG {
class SecurityComponentTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SecurityComponentTheme, Theme);

public:
    ~SecurityComponentTheme() = default;

    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<SecurityComponentTheme> Build(const RefPtr<ThemeConstants>& themeConstants)
        {
            RefPtr<SecurityComponentTheme> theme = AceType::Claim(new SecurityComponentTheme());
            if (!themeConstants) {
                SC_LOG_ERROR("Build SecurityComponentTheme error, themeConstants is null!");
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }
    };

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetMinIconSize() const
    {
        return minIconSize_;
    }

    const Dimension& GetMinFontSize() const
    {
        return minFontSize_;
    }

    const Dimension& GetBackgroundTopPadding() const
    {
        return backgroundTopPadding_;
    }

    const Dimension& GetBackgroundRightPadding() const
    {
        return backgroundRightPadding_;
    }

    const Dimension& GetBackgroundBottomPadding() const
    {
        return backgroundBottomPadding_;
    }

    const Dimension& GetBackgroundLeftPadding() const
    {
        return backgroundLeftPadding_;
    }

    const Dimension& GetTextIconSpace() const
    {
        return textIconSpace_;
    }

    const Dimension& GetPaddingWithoutBg() const
    {
        return paddingWithoutBg_;
    }

    const Dimension& GetDefaultBorderRadius() const
    {
        return defaultBorderRadius_;
    }

    const Dimension& GetBorderRadius() const
    {
        return borderRadius_;
    }

    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    const Color& GetIconColor() const
    {
        return iconColor_;
    }

    const Color& GetFontColor() const
    {
        return fontColor_;
    }

    const Color& GetIconColorNoBg() const
    {
        return iconColorNoBg_;
    }

    const Color& GetFontColorNoBg() const
    {
        return fontColorNoBg_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetBorderColor() const
    {
        return borderColor_;
    }

    const Color& GetDefaultSymbolIconColor() const
    {
        return defaultSymbolIconColor_;
    }

    const std::string& GetLocationDescriptions(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(locationDescriptions_.size())) {
            return emptyString_;
        }
        return locationDescriptions_[index];
    }

    const std::string& GetPasteDescriptions(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(pasteDescriptions_.size())) {
            return emptyString_;
        }
        return pasteDescriptions_[index];
    }

    const std::string& GetSaveDescriptions(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(saveDescriptions_.size())) {
            return emptyString_;
        }
        return saveDescriptions_[index];
    }

    uint32_t GetDefaultTextMaxLines() const
    {
        return defaultTextMaxLines_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    float GetBgDisabledAlpha() const
    {
        return bgDisabledAlpha_;
    }

private:
    SecurityComponentTheme() = default;
    static void ParseLocationDescriptions(RefPtr<ThemeStyle> securityComponentPattern,
        const RefPtr<SecurityComponentTheme>& theme)
    {
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_current_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_add_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_select_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_share_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_send_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_locating", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_send_current_location", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_relocation", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_punch_in", ""));
        theme->locationDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_current_position", ""));
    }

    static void ParsePasteDescriptions(RefPtr<ThemeStyle> securityComponentPattern,
        const RefPtr<SecurityComponentTheme>& theme)
    {
        theme->pasteDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_paste", ""));
    }

    static void ParseSaveDescriptions(RefPtr<ThemeStyle> securityComponentPattern,
        const RefPtr<SecurityComponentTheme>& theme)
    {
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_download", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_download_file", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_save", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_save_image", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_save_file", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_download_and_share", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_receive", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_continue_to_receive", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_save_to_gallery", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_export_to_gallery", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_quick_save_to_gallery", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_quick_resave_to_gallery", ""));
        theme->saveDescriptions_.emplace_back(
            securityComponentPattern->GetAttr<std::string>("description_save_all", ""));
    }

    static void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SecurityComponentTheme>& theme)
    {
        RefPtr<ThemeStyle> securityComponentPattern =
            themeConstants->GetPatternByName(THEME_PATTERN_SECURITY_COMPONENT);
        if (!securityComponentPattern) {
            return;
        }
        theme->iconSize_ = securityComponentPattern->GetAttr<Dimension>("icon_size", 0.0_vp);
        theme->fontSize_ = securityComponentPattern->GetAttr<Dimension>("font_size", 0.0_vp);
        theme->minIconSize_ = securityComponentPattern->GetAttr<Dimension>("min_icon_size", 0.0_vp);
        theme->minFontSize_ = securityComponentPattern->GetAttr<Dimension>("min_font_size", 0.0_vp);
        theme->backgroundTopPadding_ =
            securityComponentPattern->GetAttr<Dimension>("background_top_padding", 0.0_vp);
        theme->backgroundRightPadding_ =
            securityComponentPattern->GetAttr<Dimension>("background_right_padding", 0.0_vp);
        theme->backgroundBottomPadding_ =
            securityComponentPattern->GetAttr<Dimension>("background_bottom_padding", 0.0_vp);
        theme->backgroundLeftPadding_ =
            securityComponentPattern->GetAttr<Dimension>("background_left_padding", 0.0_vp);
        theme->textIconSpace_ = securityComponentPattern->GetAttr<Dimension>("text_icon_padding", 0.0_vp);
        theme->paddingWithoutBg_ = securityComponentPattern->GetAttr<Dimension>("padding_without_background", 0.0_vp);
        theme->borderRadius_ = securityComponentPattern->GetAttr<Dimension>("border_radius", 0.0_vp);
        theme->defaultBorderRadius_ = securityComponentPattern->GetAttr<Dimension>("default_border_radius", 0.0_vp);
        theme->borderWidth_ = securityComponentPattern->GetAttr<Dimension>("border_width", 0.0_vp);
        theme->iconColor_ = securityComponentPattern->GetAttr<Color>("icon_color", Color());
        theme->fontColor_ = securityComponentPattern->GetAttr<Color>("font_color", Color());
        theme->iconColorNoBg_ = securityComponentPattern->GetAttr<Color>("icon_color_no_bg", Color());
        theme->fontColorNoBg_ = securityComponentPattern->GetAttr<Color>("font_color_no_bg", Color());
        theme->backgroundColor_ = securityComponentPattern->GetAttr<Color>("background_color", Color());
        theme->borderColor_ = securityComponentPattern->GetAttr<Color>("border_color", Color());
        theme->defaultSymbolIconColor_ = securityComponentPattern->GetAttr<Color>("menu_icon_color", Color());
        ParseLocationDescriptions(securityComponentPattern, theme);
        ParsePasteDescriptions(securityComponentPattern, theme);
        ParseSaveDescriptions(securityComponentPattern, theme);
    }

    Dimension iconSize_;
    Dimension fontSize_;
    Dimension minIconSize_;
    Dimension minFontSize_;
    Dimension backgroundTopPadding_;
    Dimension backgroundRightPadding_;
    Dimension backgroundBottomPadding_;
    Dimension backgroundLeftPadding_;
    Dimension textIconSpace_;
    Dimension borderRadius_;
    Dimension defaultBorderRadius_;
    Dimension borderWidth_;
    Dimension paddingWithoutBg_;

    Color iconColor_;
    Color fontColor_;
    Color iconColorNoBg_;
    Color fontColorNoBg_;
    Color backgroundColor_;
    Color borderColor_;
    Color defaultSymbolIconColor_;

    uint32_t defaultTextMaxLines_ = 1000000; // Infinity
    TextStyle textStyle_;
    float bgDisabledAlpha_ = 0.4f;

    std::vector<std::string> locationDescriptions_;
    std::vector<std::string> pasteDescriptions_;
    std::vector<std::string> saveDescriptions_;
    std::string emptyString_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_APP_BAR_THEME_H
