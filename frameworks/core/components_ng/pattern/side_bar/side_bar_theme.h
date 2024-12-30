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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {
/**
 * SideBarTheme defines color and styles of SideBarPattern. SideBarTheme should be built
 * using SideBarTheme::Builder.
 */
class SideBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SideBarTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SideBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SideBarTheme> theme = AceType::Claim(new SideBarTheme());
            if (!themeConstants) {
                return theme;
            }

            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SideBarTheme>& theme) const
        {
            RefPtr<ThemeStyle> sideBarPattern = themeConstants->GetPatternByName(THEME_PATTERN_SIDE_BAR);
            if (!sideBarPattern) {
                return;
            }

            theme->controlImageColor_ = sideBarPattern->GetAttr<Color>("control_image_color", Color::BLACK);
            theme->sideBarBackgroundColor_ = sideBarPattern->GetAttr<Color>("side_bar_background_color", Color::WHITE);
            theme->controlButtonRadius_ = sideBarPattern->GetAttr<Dimension>("control_button_radius", 0.0_vp);
            auto dividerShadowEnable = sideBarPattern->GetAttr<std::string>("divider_shadow_enable", "0");
            theme->dividerShadowEnable_ = StringUtils::StringToInt(dividerShadowEnable);

            auto sideBarUnfocusEffectEnable
                = sideBarPattern->GetAttr<std::string>("section_unfocus_effect_enable", "0");
            theme->sideBarUnfocusEffectEnable_ = StringUtils::StringToInt(sideBarUnfocusEffectEnable);
            theme->sideBarUnfocusColor_ = sideBarPattern->GetAttr<Color>("color_panel_bg", Color::TRANSPARENT);

            theme->controlButtonIconColor_ = sideBarPattern->GetAttr<Color>("dialog_icon_primary", Color::TRANSPARENT);
            theme->controlButtonBackboardColor_ =
                sideBarPattern->GetAttr<Color>("control_button_back_board_color", Color::TRANSPARENT);
            theme->controlButtonBackboardColorHover_ =
                sideBarPattern->GetAttr<Color>("control_button_back_board_color_hover", Color::TRANSPARENT);
            theme->controlButtonBackboardColorPress_ =
                sideBarPattern->GetAttr<Color>("control_button_back_board_color_press", Color::TRANSPARENT);
            theme->controlButtonBackboardStrokeColor_ =
                sideBarPattern->GetAttr<Color>("control_button_back_board_stroke_color", Color::TRANSPARENT);
            theme->controlButtonBackboardRadius_ =
                sideBarPattern->GetAttr<Dimension>("dialog_radius_level10", 20.0_vp);
            theme->controlButtonMarginLeftSmall_ =
                sideBarPattern->GetAttr<Dimension>("control_button_margin_left_small", 0.0_vp);
            theme->controlButtonMarginLeftMiddle_ =
                sideBarPattern->GetAttr<Dimension>("control_button_margin_left_middle", 0.0_vp);
            theme->controlButtonMarginLeftLarge_ =
                sideBarPattern->GetAttr<Dimension>("control_button_margin_left_large", 0.0_vp);
            theme->breakPointHorizontalSmall_ =
                sideBarPattern->GetAttr<Dimension>("break_point_horizontal_small", 0.0_vp);
            theme->breakPointHorizontalMiddle_ =
                sideBarPattern->GetAttr<Dimension>("break_point_horizontal_middle", 0.0_vp);
            theme->controlButtonMarginTopSmall_ =
                sideBarPattern->GetAttr<Dimension>("control_button_margin_top_small", 0.0_vp);
            theme->controlButtonWidthSmall_ =
                sideBarPattern->GetAttr<Dimension>("control_button_width_small", 0.0_vp);
            theme->controlButtonHeightSmall_ =
                sideBarPattern->GetAttr<Dimension>("control_button_height_small", 0.0_vp);
            theme->sideBarWidth_ = sideBarPattern->GetAttr<Dimension>("side_bar_width", -1.0_vp);
        }
    };

    ~SideBarTheme() override = default;

    const Color& GetControlImageColor() const
    {
        return controlImageColor_;
    }

    const Color& GetSideBarBackgroundColor() const
    {
        return sideBarBackgroundColor_;
    }

    const Dimension& GetControlButtonRadius() const
    {
        return controlButtonRadius_;
    }

    int32_t GetDividerShadowEnable() const
    {
        return dividerShadowEnable_;
    }

    const int32_t& GetSideBarUnfocusEffectEnable() const
    {
        return sideBarUnfocusEffectEnable_;
    }

    const Color& GetSideBarUnfocusColor() const
    {
        return sideBarUnfocusColor_;
    }

    const Color& GetControlButtonIconColor() const
    {
        return controlButtonIconColor_;
    }

    const Color& GetControlButtonBackboardColor() const
    {
        return controlButtonBackboardColor_;
    }

    const Color& GetControlButtonBackboardColorHover() const
    {
        return controlButtonBackboardColorHover_;
    }

    const Color& GetControlButtonBackboardColorPress() const
    {
        return controlButtonBackboardColorPress_;
    }

    const Color& GetControlButtonBackboardStrokeColor() const
    {
        return controlButtonBackboardStrokeColor_;
    }

    const Dimension& GetControlButtonBackboardRadius() const
    {
        return controlButtonBackboardRadius_;
    }

    const Dimension& GetControlButtonMarginLeftSmall() const
    {
        return controlButtonMarginLeftSmall_;
    }

    const Dimension& GetControlButtonMarginLeftMiddle() const
    {
        return controlButtonMarginLeftMiddle_;
    }
    
    const Dimension& GetControlButtonMarginLeftLarge() const
    {
        return controlButtonMarginLeftLarge_;
    }

    const Dimension& GetBreakPointHorizontalSmall() const
    {
        return breakPointHorizontalSmall_;
    }

    const Dimension& GetBreakPointHorizontalMiddle() const
    {
        return breakPointHorizontalMiddle_;
    }

    const Dimension& GetControlButtonMarginTopSmall() const
    {
        return controlButtonMarginTopSmall_;
    }

    const Dimension& GetControlButtonWidthSmall() const
    {
        return controlButtonWidthSmall_;
    }

    const Dimension& GetControlButtonHeightSmall() const
    {
        return controlButtonHeightSmall_;
    }

    const Dimension& GetSideBarWidth() const
    {
        return sideBarWidth_;
    }

protected:
    SideBarTheme() = default;

private:
    Color controlImageColor_ = Color::BLACK;
    Color sideBarBackgroundColor_ = Color::WHITE;
    Dimension controlButtonRadius_;
    int32_t dividerShadowEnable_ = 0;
    int32_t sideBarUnfocusEffectEnable_ = 0;
    Color sideBarUnfocusColor_ = Color::TRANSPARENT;
    // version 13
    Color controlButtonIconColor_ = Color::BLACK;
    Color controlButtonBackboardColor_ = Color::TRANSPARENT;
    Color controlButtonBackboardColorHover_ = Color::TRANSPARENT;
    Color controlButtonBackboardColorPress_ = Color::TRANSPARENT;
    Color controlButtonBackboardStrokeColor_ = Color::TRANSPARENT;
    Dimension controlButtonBackboardRadius_ = 0.0_vp;
    Dimension controlButtonMarginLeftSmall_ = 0.0_vp;
    Dimension controlButtonMarginLeftMiddle_ = 0.0_vp;
    Dimension controlButtonMarginLeftLarge_ = 0.0_vp;
    Dimension breakPointHorizontalSmall_ = 0.0_vp;
    Dimension breakPointHorizontalMiddle_ = 0.0_vp;
    Dimension controlButtonMarginTopSmall_ = 0.0_vp;
    Dimension controlButtonWidthSmall_ = 0.0_vp;
    Dimension controlButtonHeightSmall_ = 0.0_vp;
    Dimension sideBarWidth_ = -1.0_vp;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_THEME_H
