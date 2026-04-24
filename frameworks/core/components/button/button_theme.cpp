/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components/button/button_theme.h"

#include "core/components/common/layout/constants.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

RefPtr<ButtonTheme> ButtonTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<ButtonTheme> theme = AceType::MakeRefPtr<ButtonTheme>();
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void ButtonTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ButtonTheme>& theme) const
{
    if (!themeConstants) {
        return;
    }
    RefPtr<ThemeStyle> buttonPattern = themeConstants->GetPatternByName(THEME_PATTERN_BUTTON);
    if (!buttonPattern) {
        LOGW("find pattern of button fail");
        return;
    }
    theme->bgColor_ = buttonPattern->GetAttr<Color>("button_bg_color", Color());
    theme->roleWarningColor_ = buttonPattern->GetAttr<Color>("role_warning", Color());
    theme->clickedColor_ = buttonPattern->GetAttr<Color>("bg_color_clicked_blend", Color());
    theme->disabledColor_ =
        theme->bgColor_.BlendOpacity(buttonPattern->GetAttr<double>(PATTERN_BG_COLOR_DISABLED_ALPHA, 0.0));
    theme->hoverColor_ = buttonPattern->GetAttr<Color>("bg_color_hovered_blend", Color());
    theme->borderColor_ = buttonPattern->GetAttr<Color>("border_color", Color());
    theme->borderWidth_ = buttonPattern->GetAttr<Dimension>("border_width", 0.0_vp);
    theme->textStyle_.SetTextColor(buttonPattern->GetAttr<Color>("button_text_color", Color()));
    theme->textDisabledColor_ =
        buttonPattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color())
            .BlendOpacity(buttonPattern->GetAttr<double>("text_color_disabled_alpha", 0.0));
    theme->textWaitingColor_ = buttonPattern->GetAttr<Color>("waiting_button_text_color", Color());
    theme->normalTextColor_ = buttonPattern->GetAttr<Color>("normal_text_color", Color());
    theme->downloadBackgroundColor_ =
        buttonPattern->GetAttr<Color>("download_button_bg_color", Color())
            .BlendOpacity(buttonPattern->GetAttr<double>("download_button_bg_color_alpha", 0.0));
    theme->downloadBorderColor_ =
        buttonPattern->GetAttr<Color>("download_button_border_color", Color())
            .BlendOpacity(buttonPattern->GetAttr<double>("download_button_border_color_alpha", 0.0));
    theme->downloadProgressColor_ =
        buttonPattern->GetAttr<Color>("download_button_process_color", Color())
            .BlendOpacity(buttonPattern->GetAttr<double>("download_button_process_color_alpha", 0.0));
    theme->downloadTextColor_ = buttonPattern->GetAttr<Color>("download_button_text_color", Color());
    theme->progressColor_ = buttonPattern->GetAttr<Color>("process_button_text_color", Color());
    theme->radius_ = buttonPattern->GetAttr<Dimension>("button_radius", 0.0_vp);
    theme->bgFocusColor_ = buttonPattern->GetAttr<Color>("button_bg_focus_color", Color());
    theme->bgDisabledAlpha_ = buttonPattern->GetAttr<double>("bg_color_disabled_alpha", 0.0);
    theme->textFocusColor_ = buttonPattern->GetAttr<Color>("button_text_focus_color", Color());
    theme->textStyle_.SetFontSize(buttonPattern->GetAttr<Dimension>("button_font_size", 0.0_fp));
    theme->textStyle_.SetFontWeight(
        FontWeight(static_cast<int32_t>(buttonPattern->GetAttr<double>("button_font_weight", 0.0))));
    theme->minWidth_ = buttonPattern->GetAttr<Dimension>("button_min_width", 0.0_vp);
    theme->height_ = buttonPattern->GetAttr<Dimension>("button_height", 0.0_vp);
    theme->downloadHeight_ = buttonPattern->GetAttr<Dimension>("button_download_height", 0.0_vp);
    theme->padding_ = Edge(buttonPattern->GetAttr<Dimension>("button_horizontal_padding", 0.0_vp).Value(),
        buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Value(),
        buttonPattern->GetAttr<Dimension>("button_horizontal_padding", 0.0_vp).Value(),
        buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Value(),
        buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Unit());
    theme->minFontSize_ = buttonPattern->GetAttr<Dimension>("button_min_font_size", 0.0_fp);
    ParseAdditionalStylePattern(buttonPattern, theme);
}

void ButtonTheme::Builder::ParseAdditionalStylePattern(
    const RefPtr<ThemeStyle>& buttonPattern, const RefPtr<ButtonTheme>& theme) const
{
    int32_t maxlines = static_cast<int32_t>(buttonPattern->GetAttr<double>("button_text_max_lines", 0.0));
    theme->textMaxLines_ = maxlines < 0 ? theme->textMaxLines_ : static_cast<uint32_t>(maxlines);
    theme->minCircleButtonDiameter_ = buttonPattern->GetAttr<Dimension>("min_circle_button_diameter", 0.0_vp);
    theme->minCircleButtonIcon_ = buttonPattern->GetAttr<Dimension>("min_circle_button_icon_size", 0.0_vp);
    theme->minCircleButtonPadding_ =
        Edge(buttonPattern->GetAttr<Dimension>("min_circle_button_padding", 0.0_vp));
    theme->maxCircleButtonDiameter_ = buttonPattern->GetAttr<Dimension>("max_circle_button_diameter", 0.0_vp);
    theme->maxCircleButtonIcon_ = buttonPattern->GetAttr<Dimension>("max_circle_button_icon_size", 0.0_vp);
    theme->maxCircleButtonPadding_ =
        Edge(buttonPattern->GetAttr<Dimension>("button_max_circle_button_padding", 0.0_vp));
    theme->progressFocusColor_ = buttonPattern->GetAttr<Color>("button_progress_focus_color", Color());
    theme->downloadFontSize_ = buttonPattern->GetAttr<Dimension>("button_download_font_size", 0.0_fp);
    theme->progressDiameter_ = buttonPattern->GetAttr<Dimension>("button_progress_diameter", 0.0_vp);
    theme->innerPadding_ = buttonPattern->GetAttr<Dimension>("button_inner_padding", 0.0_vp);
    theme->borderWidthSmall_ = buttonPattern->GetAttr<Dimension>("width_border_small", 0.0_vp);
    theme->borderColorSmall_ = buttonPattern->GetAttr<Color>("color_border_small", Color());
    theme->shadowNormal_ = static_cast<uint32_t>(buttonPattern->GetAttr<double>("shadow_default", 0.0));
    theme->shadowFocus_ = static_cast<uint32_t>(buttonPattern->GetAttr<double>("shadow_focus", 0.0));
    theme->scaleHoverOrFocus_ =  buttonPattern->GetAttr<double>("scale_focus", 0.0);
    theme->paddingText_ = buttonPattern->GetAttr<Dimension>("padding_text", 0.0_vp);
    theme->textBackgroundFocus_ = buttonPattern->GetAttr<Color>("focus_bg_text", Color());
    theme->normalBackgroundFocus_ = buttonPattern->GetAttr<Color>("normal_button_focus_bgcolor", Color());
    theme->emphasizeBackgroundFocus_ = buttonPattern->GetAttr<Color>("emphasize_focus_color", Color());
    theme->bigFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_big_font_size_scale", 0.0);
    theme->largeFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_large_font_size_scale", 0.0);
    theme->maxFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_max_font_size_scale", 0.0);
    theme->agingNormalPadding_ = buttonPattern->GetAttr<Dimension>("button_aging_normal_padding", 0.0_vp);
    theme->agingSmallPadding_ = buttonPattern->GetAttr<Dimension>("button_aging_small_padding", 0.0_vp);
    theme->agingTextMaxLines_ =
        static_cast<uint32_t>(buttonPattern->GetAttr<double>("button_aging_text_max_lines", 0.0));
    theme->textButtonFontSize_ = buttonPattern->GetAttr<Dimension>("text_button_font_size", 0.0_fp);
    theme->isApplyFontSize_ =
        static_cast<bool>(buttonPattern->GetAttr<double>("apply_text_font_size", 0.0));
    ParseSubStylePattern(buttonPattern, theme);
}

void ButtonTheme::Builder::ParseSubStylePattern(
    const RefPtr<ThemeStyle>& buttonPattern, const RefPtr<ButtonTheme>& theme) const
{
    std::unordered_map<ButtonStyleMode, Color> normalBgColorMap_ = { { ButtonStyleMode::EMPHASIZE,
                                                                         theme->bgColor_ },
        { ButtonStyleMode::NORMAL, buttonPattern->GetAttr<Color>("bg_color_normal", Color()) },
        { ButtonStyleMode::TEXT, Color::TRANSPARENT } };
    std::unordered_map<ButtonStyleMode, Color> errorBgColorMap_ = { { ButtonStyleMode::EMPHASIZE,
                                                                        theme->roleWarningColor_ },
        { ButtonStyleMode::NORMAL, buttonPattern->GetAttr<Color>("bg_color_normal", Color()) },
        { ButtonStyleMode::TEXT, Color::TRANSPARENT } };
    theme->bgColorMap_.emplace(ButtonRole::NORMAL, normalBgColorMap_);
    theme->bgColorMap_.emplace(ButtonRole::ERROR, errorBgColorMap_);
    theme->textColorMap_.insert(std::pair<ButtonStyleMode, Color>(
        ButtonStyleMode::EMPHASIZE, buttonPattern->GetAttr<Color>("emphasize_button_text_color", Color())));
    theme->textColorMap_.insert(
        std::pair<ButtonStyleMode, Color>(ButtonStyleMode::NORMAL, theme->normalTextColor_));
    theme->textColorMap_.insert(std::pair<ButtonStyleMode, Color>(
        ButtonStyleMode::TEXT, buttonPattern->GetAttr<Color>("text_button_text_color", Color())));
    theme->focusTextColorMap_.insert(std::pair<ButtonStyleMode, Color>(
        ButtonStyleMode::NORMAL, buttonPattern->GetAttr<Color>("normal_button_text_focus_color", Color())));
    theme->focusTextColorMap_.insert(std::pair<ButtonStyleMode, Color>(
        ButtonStyleMode::TEXT, buttonPattern->GetAttr<Color>("text_button_text_focus_color", Color())));
    theme->textColorByRoleMap_.insert(
        std::pair<ButtonRole, Color>(ButtonRole::NORMAL, theme->normalTextColor_));
    theme->textColorByRoleMap_.insert(
        std::pair<ButtonRole, Color>(ButtonRole::ERROR, theme->roleWarningColor_));
    theme->heightMap_.insert(std::pair<ControlSize, Dimension>(ControlSize::NORMAL, theme->height_));
    theme->heightMap_.insert(std::pair<ControlSize, Dimension>(
        ControlSize::SMALL, buttonPattern->GetAttr<Dimension>("small_button_height", 0.0_vp)));

    theme->textSizeMap_.insert(std::pair<ControlSize, Dimension>(
        ControlSize::NORMAL, buttonPattern->GetAttr<Dimension>("button_font_size", 0.0_fp)));
    theme->textSizeMap_.insert(std::pair<ControlSize, Dimension>(
        ControlSize::SMALL, buttonPattern->GetAttr<Dimension>("small_button_font_size", 0.0_fp)));

    theme->paddingMap_.insert(std::pair<ControlSize, Edge>(ControlSize::NORMAL, theme->padding_));
    theme->paddingMap_.insert(std::pair<ControlSize, Edge>(ControlSize::SMALL,
        Edge(buttonPattern->GetAttr<Dimension>("small_button_horizontal_padding", 0.0_vp).Value(),
            buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Value(),
            buttonPattern->GetAttr<Dimension>("small_button_horizontal_padding", 0.0_vp).Value(),
            buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Value(),
            buttonPattern->GetAttr<Dimension>("button_vertical_padding", 0.0_vp).Unit())));
    theme->borderRadiusMap_.insert(std::pair<ControlSize, Dimension>(
        ControlSize::NORMAL, buttonPattern->GetAttr<Dimension>("button_border_radius_normal", 20.0_vp)));
    theme->borderRadiusMap_.insert(std::pair<ControlSize, Dimension>(
        ControlSize::SMALL, buttonPattern->GetAttr<Dimension>("button_border_radius_small", 14.0_vp)));
    theme->pasteText_ = buttonPattern->GetAttr<std::string>("textoverlay_paste", "");
    theme->cancelText_ = buttonPattern->GetAttr<std::string>("common_cancel_text", "");
}

} // namespace OHOS::Ace
