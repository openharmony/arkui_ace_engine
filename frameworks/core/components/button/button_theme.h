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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * ButtonTheme defines color and styles of ButtonComponent. ButtonTheme should be built
 * using ButtonTheme::Builder.
 */
class ButtonTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ButtonTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ButtonTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ButtonTheme> theme = AceType::Claim(new ButtonTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ButtonTheme>& theme) const
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
        void ParseAdditionalStylePattern(
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
            theme->bigFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_big_font_size_scale", 0.0);
            theme->largeFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_large_font_size_scale", 0.0);
            theme->maxFontSizeScale_ = buttonPattern->GetAttr<double>("button_aging_max_font_size_scale", 0.0);
            theme->agingNormalPadding_ = buttonPattern->GetAttr<Dimension>("button_aging_normal_padding", 0.0_vp);
            theme->agingSmallPadding_ = buttonPattern->GetAttr<Dimension>("button_aging_small_padding", 0.0_vp);
            theme->agingTextMaxLines_ =
                static_cast<uint32_t>(buttonPattern->GetAttr<double>("button_aging_text_max_lines", 0.0));
            ParseSubStylePattern(buttonPattern, theme);
        }

        void ParseSubStylePattern(const RefPtr<ThemeStyle>& buttonPattern, const RefPtr<ButtonTheme>& theme) const
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
            theme->textColorMap_.insert(
                std::pair<ButtonStyleMode, Color>(ButtonStyleMode::TEXT, theme->normalTextColor_));
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
        }
    };

    ~ButtonTheme() override = default;

    const Dimension& GetRadius() const
    {
        return radius_;
    }

    const Color& GetBgColor() const
    {
        return bgColor_;
    }

    const Color& GetBgFocusColor() const
    {
        return bgFocusColor_;
    }

    const Color& GetClickedColor() const
    {
        return clickedColor_;
    }

    const Color& GetDisabledColor() const
    {
        return disabledColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetBorderColor() const
    {
        return borderColor_;
    }

    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    double GetBgDisabledAlpha() const
    {
        return bgDisabledAlpha_;
    }

    const Color& GetTextFocusColor() const
    {
        return textFocusColor_;
    }

    const Color& GetTextDisabledColor() const
    {
        return textDisabledColor_;
    }

    const Color& GetNormalTextColor() const
    {
        return normalTextColor_;
    }

    const Color& GetDownloadBackgroundColor() const
    {
        return downloadBackgroundColor_;
    }

    const Color& GetDownloadTextColor() const
    {
        return downloadTextColor_;
    }

    const Color& GetTextWaitingColor() const
    {
        return textWaitingColor_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Dimension& GetMinWidth() const
    {
        return minWidth_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Dimension& GetDownloadHeight() const
    {
        return downloadHeight_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetMinFontSize() const
    {
        return minFontSize_;
    }

    const Dimension& GetDownloadFontSize() const
    {
        return downloadFontSize_;
    }

    const Dimension& GetMaxFontSize() const
    {
        return textStyle_.GetFontSize();
    }

    uint32_t GetTextMaxLines() const
    {
        return textMaxLines_;
    }

    const Dimension& GetMinCircleButtonDiameter() const
    {
        return minCircleButtonDiameter_;
    }

    const Dimension& GetMinCircleButtonIcon() const
    {
        return minCircleButtonIcon_;
    }

    const Edge& GetMinCircleButtonPadding() const
    {
        return minCircleButtonPadding_;
    }

    const Dimension& GetMaxCircleButtonDiameter() const
    {
        return maxCircleButtonDiameter_;
    }

    const Dimension& GetMaxCircleButtonIcon() const
    {
        return maxCircleButtonIcon_;
    }

    const Edge& GetMaxCircleButtonPadding() const
    {
        return maxCircleButtonPadding_;
    }

    const Color& GetProgressFocusColor() const
    {
        return progressFocusColor_;
    }

    const Color& GetDownloadBorderColor() const
    {
        return downloadBorderColor_;
    }

    const Color& GetProgressColor() const
    {
        return progressColor_;
    }

    const Dimension& GetProgressDiameter() const
    {
        return progressDiameter_;
    }

    const Color& GetDownloadProgressColor() const
    {
        return downloadProgressColor_;
    }

    const Dimension& GetInnerPadding() const
    {
        return innerPadding_;
    }

    Color GetBgColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const
    {
        auto bgColorMapByRole_ = bgColorMap_.find(buttonRole);
        if (bgColorMapByRole_ != bgColorMap_.end()) {
            std::unordered_map<ButtonStyleMode, Color> bgColorMapByStyle_ = bgColorMapByRole_->second;
            auto result = bgColorMapByStyle_.find(buttonStyle);
            if (result != bgColorMapByStyle_.end()) {
                return result->second;
            }
        }
        return bgColor_;
    }

    const Color& GetTextColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const
    {
        auto roleResult = textColorByRoleMap_.find(buttonRole);
        auto result = textColorMap_.find(buttonStyle);
        if (roleResult != textColorByRoleMap_.end() && result != textColorMap_.end()) {
            if (buttonRole == ButtonRole::ERROR) {
                if (buttonStyle == ButtonStyleMode::EMPHASIZE) {
                    return result->second;
                }
                return roleResult->second;
            }
            return result->second;
        }
        return normalTextColor_;
    }

    const Dimension& GetHeight(ControlSize controlSize) const
    {
        auto result = heightMap_.find(controlSize);
        if (result != heightMap_.end()) {
            return result->second;
        }
        return height_;
    }

    const Dimension& GetBorderRadius(ControlSize controlSize) const
    {
        auto result = borderRadiusMap_.find(controlSize);
        if (result != borderRadiusMap_.end()) {
            return result->second;
        }
        return borderRadius_;
    }

    const Dimension& GetTextSize(ControlSize controlSize) const
    {
        auto result = textSizeMap_.find(controlSize);
        if (result != textSizeMap_.end()) {
            return result->second;
        }
        return textStyle_.GetFontSize();
    }

    const Edge& GetPadding(ControlSize controlSize) const
    {
        auto result = paddingMap_.find(controlSize);
        if (result != paddingMap_.end()) {
            return result->second;
        }
        return padding_;
    }

    float GetBigFontSizeScale() const
    {
        return bigFontSizeScale_;
    }

    float GetLargeFontSizeScale() const
    {
        return largeFontSizeScale_;
    }

    float GetMaxFontSizeScale() const
    {
        return maxFontSizeScale_;
    }

    const Dimension& GetAgingNormalPadding() const
    {
        return agingNormalPadding_;
    }

    const Dimension& GetAgingSmallPadding() const
    {
        return agingSmallPadding_;
    }

    uint32_t GetAgingTextMaxLines() const
    {
        return agingTextMaxLines_;
    }

protected:
    ButtonTheme() = default;

private:
    Color bgColor_;
    Color roleWarningColor_;
    Color bgFocusColor_;
    Color clickedColor_;
    Color disabledColor_;
    Color hoverColor_;
    Color borderColor_;
    Color textFocusColor_;
    Color textDisabledColor_;
    Color textWaitingColor_;
    Color progressColor_;
    Color progressFocusColor_;
    Color normalTextColor_;
    Color downloadBackgroundColor_;
    Color downloadTextColor_;
    Color downloadBorderColor_;
    Color downloadProgressColor_;
    TextStyle textStyle_;
    Edge padding_;
    Edge minCircleButtonPadding_;
    Edge maxCircleButtonPadding_;

    Dimension radius_;
    Dimension minWidth_;
    Dimension height_;
    Dimension progressDiameter_;
    Dimension innerPadding_;
    Dimension minFontSize_;
    Dimension downloadFontSize_;
    Dimension minCircleButtonDiameter_;
    Dimension minCircleButtonIcon_;
    Dimension maxCircleButtonDiameter_;
    Dimension maxCircleButtonIcon_;
    Dimension borderWidth_;
    Dimension downloadHeight_;
    Dimension borderRadius_;
    std::unordered_map<ButtonRole, std::unordered_map<ButtonStyleMode, Color>> bgColorMap_;
    std::unordered_map<ButtonRole, Color> textColorByRoleMap_;
    std::unordered_map<ButtonStyleMode, Color> textColorMap_;
    std::unordered_map<ControlSize, Dimension> heightMap_;
    std::unordered_map<ControlSize, Dimension> textSizeMap_;
    std::unordered_map<ControlSize, Edge> paddingMap_;
    std::unordered_map<ControlSize, Dimension> borderRadiusMap_;
    double bgDisabledAlpha_ = 1.0;
    uint32_t textMaxLines_ = 1;
    float bigFontSizeScale_ = 1.75f;
    float largeFontSizeScale_ = 2.0f;
    float maxFontSizeScale_ = 3.2f;
    Dimension agingNormalPadding_;
    Dimension agingSmallPadding_;
    uint32_t agingTextMaxLines_ = 2;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H
