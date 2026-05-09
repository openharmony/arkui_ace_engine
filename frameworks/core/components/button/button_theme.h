/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"

namespace OHOS::Ace {

class ThemeConstants;
class ThemeStyle;

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

        RefPtr<ButtonTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ButtonTheme>& theme) const;
        void ParseAdditionalStylePattern(
            const RefPtr<ThemeStyle>& buttonPattern, const RefPtr<ButtonTheme>& theme) const;

    private:
        void ParseSubStylePattern(const RefPtr<ThemeStyle>& buttonPattern, const RefPtr<ButtonTheme>& theme) const;
    };

    ~ButtonTheme() override = default;

    const Dimension& GetRadius() const
    {
        return radius_;
    }

    virtual const Color& GetBgColor() const
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

    uint32_t GetShadowNormal() const
    {
        return shadowNormal_;
    }

    uint32_t GetShadowFocus() const
    {
        return shadowFocus_;
    }

    double GetScaleHoverOrFocus() const
    {
        return scaleHoverOrFocus_;
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

    virtual Color GetBgColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const
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

    virtual const Color& GetTextColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const
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

    const Color& GetFocusTextColor(ButtonStyleMode buttonStyle, ButtonRole buttonRole) const
    {
        auto roleResult = textColorByRoleMap_.find(buttonRole);
        auto result = focusTextColorMap_.find(buttonStyle);
        if (roleResult == textColorByRoleMap_.end() || result == focusTextColorMap_.end()) {
            return normalTextColor_;
        }
        if (buttonRole == ButtonRole::ERROR && buttonStyle != ButtonStyleMode::EMPHASIZE) {
            return roleResult->second;
        }
        return result->second;
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

    const Dimension& GetBorderWidthSmall() const
    {
        return borderWidthSmall_;
    }

    const Dimension& GetPaddingText() const
    {
        return paddingText_;
    }

    const Color& GetBorderColorSmall() const
    {
        return borderColorSmall_;
    }

    const Color& GetTextBackgroundFocus() const
    {
        return textBackgroundFocus_;
    }

    const Color& GetNormalBackgroundFocus() const
    {
        return normalBackgroundFocus_;
    }

    const Color& GetEmphasizeBackgroundFocus() const
    {
        return emphasizeBackgroundFocus_;
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

    const Dimension& GetTextButtonFontSize() const
    {
        return textButtonFontSize_;
    }

    bool GetIsApplyTextFontSize() const
    {
        return isApplyFontSize_;
    }

    const std::string& GetPasteText() const
    {
        return pasteText_;
    }

    const std::string& GetCancelText() const
    {
        return cancelText_;
    }

protected:
    ButtonTheme() = default;
    TextStyle textStyle_;

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
    Color focusBorderColor_;
    Color borderColorSmall_;
    Color textBackgroundFocus_;
    Color normalBackgroundFocus_;
    Color emphasizeBackgroundFocus_;
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
    Dimension focusBorderWidth_;
    Dimension borderWidthSmall_;
    Dimension paddingText_;
    Dimension textButtonFontSize_;
    std::unordered_map<ButtonRole, std::unordered_map<ButtonStyleMode, Color>> bgColorMap_;
    std::unordered_map<ButtonStyleMode, Color> focusTextColorMap_;
    std::unordered_map<ButtonRole, Color> textColorByRoleMap_;
    std::unordered_map<ButtonStyleMode, Color> textColorMap_;
    std::unordered_map<ControlSize, Dimension> heightMap_;
    std::unordered_map<ControlSize, Dimension> textSizeMap_;
    std::unordered_map<ControlSize, Edge> paddingMap_;
    std::unordered_map<ControlSize, Dimension> borderRadiusMap_;
    double bgDisabledAlpha_ = 1.0;
    double scaleHoverOrFocus_ = 1.0;
    uint32_t textMaxLines_ = 1;
    uint32_t shadowNormal_ = 0;
    uint32_t shadowFocus_ = 0;
    float bigFontSizeScale_ = 1.75f;
    float largeFontSizeScale_ = 2.0f;
    float maxFontSizeScale_ = 3.2f;
    Dimension agingNormalPadding_;
    Dimension agingSmallPadding_;
    uint32_t agingTextMaxLines_ = 2;
    bool isApplyFontSize_ = false;
    std::string pasteText_;
    std::string cancelText_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUTTON_BUTTON_THEME_H
