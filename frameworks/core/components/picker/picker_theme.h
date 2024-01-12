/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_THEME_H

#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/picker/picker_data.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr Dimension DIVIDER_THICKNESS = 1.0_px;
} // namespace

class PickerTheme final : public virtual Theme {
    DECLARE_ACE_TYPE(PickerTheme, Theme);

public:
    class Builder final {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<PickerTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<PickerTheme> theme = AceType::Claim(new PickerTheme());
            if (!themeConstants) {
                return theme;
            }

            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle) {
                return theme;
            }

            InitializeTextStyles(theme, themeStyle);
            theme->optionSizeUnit_ = DimensionUnit::VP;
            theme->lunarWidth_ = Dimension(36.0, DimensionUnit::VP);  // this width do not need setting by outer.
            theme->lunarHeight_ = Dimension(18.0, DimensionUnit::VP); // this height do not need setting by outer.
            theme->rotateInterval_ = 15.0; // when rotate 15.0 angle handle scroll of picker column.
            theme->dividerThickness_ = DIVIDER_THICKNESS;
            Parse(themeStyle, theme);
            return theme;
        }

        void Parse(const RefPtr<ThemeStyle>& style, const RefPtr<PickerTheme>& theme) const
        {
            if (!style || !theme) {
                return;
            }
            auto pattern = style->GetAttr<RefPtr<ThemeStyle>>("picker_pattern", nullptr);
            if (!pattern) {
                LOGE("Pattern of picker is null, please check!");
                return;
            }

            theme->popupDecoration_ = AceType::MakeRefPtr<Decoration>();
            if (!theme->popupDecoration_) {
                return;
            }
            theme->popupDecoration_->SetBackgroundColor(pattern->GetAttr<Color>("popup_bg_color", Color()));
            theme->popupDecoration_->SetBorderRadius(
                Radius(pattern->GetAttr<Dimension>("picker_popup_radius", 0.0_vp)));
            theme->popupEdge_.SetLeft(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
            theme->popupEdge_.SetTop(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
            theme->popupEdge_.SetRight(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
            theme->popupEdge_.SetBottom(pattern->GetAttr<Dimension>("picker_popup_padding_bottom", 0.0_vp));
            auto showOptionCount = static_cast<int32_t>(pattern->GetAttr<double>("picker_show_option_count", 0.0));
            theme->showOptionCount_ =
                showOptionCount < 0 ? theme->showOptionCount_ : static_cast<uint32_t>(showOptionCount);
            theme->showButtons_ = static_cast<bool>(pattern->GetAttr<double>("picker_show_buttons", 0.0));
            theme->focusColor_ = pattern->GetAttr<Color>("picker_focus_color", Color());
            theme->focusRadius_ = Radius(pattern->GetAttr<Dimension>("picker_focus_radius", 0.0_vp));
            theme->selectedOptionSize_ = Size(pattern->GetAttr<double>("picker_option_width", 0.0),
                pattern->GetAttr<double>("picker_select_option_height", 0.0));
            theme->normalOptionSize_ = Size(pattern->GetAttr<double>("picker_option_width", 0.0),
                pattern->GetAttr<double>("picker_normal_option_height", 0.0));
            theme->optionPadding_ = pattern->GetAttr<double>("picker_option_padding", 0.0);
            theme->jumpInterval_ = pattern->GetAttr<Dimension>("picker_jump_interval", 0.0_vp);
            theme->columnIntervalMargin_ = pattern->GetAttr<Dimension>("picker_column_margin", 0.0_vp);
            theme->selectedOptionDecoration_ = AceType::MakeRefPtr<Decoration>();
            if (!theme->selectedOptionDecoration_) {
                return;
            }
            theme->selectedOptionDecoration_->SetBackgroundColor(
                pattern->GetAttr<Color>("picker_select_option_back_color", Color()));
            theme->selectedOptionDecoration_->SetBorderRadius(
                Radius(pattern->GetAttr<Dimension>("picker_select_option_radius", 0.0_vp)));
            theme->focusOptionDecoration_ = AceType::MakeRefPtr<Decoration>();
            if (!theme->focusOptionDecoration_) {
                return;
            }
            theme->focusOptionDecoration_->SetBackgroundColor(
                pattern->GetAttr<Color>("picker_focus_option_back_color", Color()));
            theme->focusOptionDecoration_->SetBorderRadius(
                Radius(pattern->GetAttr<Dimension>("picker_focus_option_radius", 0.0_vp)));
            theme->buttonWidth_ = pattern->GetAttr<Dimension>("picker_button_width", 0.0_vp);
            theme->buttonHeight_ = pattern->GetAttr<Dimension>("picker_button_height", 0.0_vp);
            theme->buttonTopPadding_ = pattern->GetAttr<Dimension>("picker_button_top_padding", 0.0_vp);
            theme->titleBottomPadding_ = pattern->GetAttr<Dimension>("picker_title_bottom_padding", 0.0_vp);
            theme->popupOutDecoration_ = AceType::MakeRefPtr<Decoration>();
            if (!theme->popupOutDecoration_) {
                return;
            }
            theme->popupOutDecoration_->SetBackgroundColor(
                pattern->GetAttr<Color>("picker_dialog_mask_color", Color()));
            auto timeSplitter = static_cast<int32_t>(pattern->GetAttr<double>("picker_time_splitter", 0.0));
            theme->timeSplitter_ = timeSplitter < 0 ? theme->timeSplitter_ : static_cast<uint32_t>(timeSplitter);
            theme->dividerSpacing_ = pattern->GetAttr<Dimension>("picker_select_divider_spacing", 0.0_vp);
            theme->dividerColor_ = pattern->GetAttr<Color>("picker_select_divider_color", Color());
            theme->gradientHeight_ = pattern->GetAttr<Dimension>("picker_select_gradient_height", 0.0_vp);
            theme->columnFixedWidth_ = pattern->GetAttr<Dimension>("picker_column_fixed_width", 0.0_vp);
            theme->pressColor_ = pattern->GetAttr<Color>("picker_press_color", Color());
            theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, theme->hoverColor_);
            theme->pressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, theme->pressColor_);
            theme->paddingHorizontal_ = pattern->GetAttr<Dimension>("padding_horizontal", 24.0_vp);
            theme->popupDecoration_->SetBackgroundColor(
                pattern->GetAttr<Color>("popup_bg_color", theme->popupDecoration_->GetBackgroundColor()));
            theme->focusColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, theme->focusColor_);
            theme->selectedOptionStyle_.SetTextColor(
                pattern->GetAttr<Color>("selected_text_color", theme->selectedOptionStyle_.GetTextColor()));
            theme->focusOptionStyle_.SetTextColor(theme->selectedOptionStyle_.GetTextColor());
            theme->normalOptionStyle_.SetTextColor(
                pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, theme->normalOptionStyle_.GetTextColor()));
            theme->disappearOptionStyle_.SetTextColor(theme->normalOptionStyle_.GetTextColor());
            theme->titleStyle_.SetTextColor(theme->normalOptionStyle_.GetTextColor());
            theme->dividerColor_ = pattern->GetAttr<Color>("divider_color", theme->dividerColor_);
            theme->dividerThickness_ = pattern->GetAttr<Dimension>("divider_thickness", 2.0_px);
            theme->contentMarginVertical_ = pattern->GetAttr<Dimension>("content_margin_vertical", 8.0_vp);
            theme->lunarswitchTextSize_ =
                pattern->GetAttr<Dimension>("lunarswitch_text_size", theme->lunarswitchTextSize_);
            theme->lunarswitchTextColor_ =
                pattern->GetAttr<Color>("lunarswitch_text_color", theme->lunarswitchTextColor_);
        }

    private:
        void InitializeButtonTextStyles(const RefPtr<PickerTheme>& theme, const RefPtr<ThemeStyle>& themeStyle) const
        {
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("picker_pattern", nullptr);
            if (pattern) {
                theme->buttonStyle_.SetFontSize(pattern->GetAttr<Dimension>("picker_button_font_size", 0.0_fp));
                theme->buttonStyle_.SetTextColor(pattern->GetAttr<Color>("picker_button_text_color", Color()));
            }
        }

        void InitializeTitleTextStyles(const RefPtr<PickerTheme>& theme, const RefPtr<ThemeStyle>& themeStyle) const
        {
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("picker_pattern", nullptr);
            if (pattern) {
                theme->titleStyle_.SetFontSize(pattern->GetAttr<Dimension>("picker_title_font_size", 0.0_fp));
                theme->titleStyle_.SetTextColor(pattern->GetAttr<Color>("picker_title_text_color", Color()));
            }
            theme->titleStyle_.SetFontWeight(FontWeight::W500);
            theme->titleStyle_.SetMaxLines(1);
            theme->titleStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);
        }

        void InitializeItemTextStyles(const RefPtr<PickerTheme>& theme, const RefPtr<ThemeStyle>& themeStyle) const
        {
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("picker_pattern", nullptr);
            if (pattern) {
                theme->selectedOptionStyle_.SetTextColor(
                    pattern->GetAttr<Color>("selected_text_color", Color(0x007DFF)));
                theme->selectedOptionStyle_.SetFontSize(
                    pattern->GetAttr<Dimension>("selected_text_size", 20.0_vp));
                theme->selectedOptionStyle_.SetFontWeight(FontWeight::MEDIUM);
                theme->selectedOptionStyle_.SetAdaptTextSize(theme->selectedOptionStyle_.GetFontSize(),
                    pattern->GetAttr<Dimension>("picker_select_option_min_font_size", 0.0_fp));
                theme->selectedOptionStyle_.SetMaxLines(1);
                theme->selectedOptionStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);

                theme->normalOptionStyle_.SetTextColor(
                    pattern->GetAttr<Color>("text_color", Color(0xff182431)));
                theme->normalOptionStyle_.SetFontSize(
                    pattern->GetAttr<Dimension>("text_size", 16.0_fp));
                theme->normalOptionStyle_.SetFontWeight(FontWeight::REGULAR);
                theme->normalOptionStyle_.SetAdaptTextSize(theme->normalOptionStyle_.GetFontSize(),
                    pattern->GetAttr<Dimension>("picker_normal_option_min_font_size", 0.0_fp));
                theme->normalOptionStyle_.SetMaxLines(1);
                theme->normalOptionStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);

                theme->disappearOptionStyle_.SetTextColor(
                    pattern->GetAttr<Color>("disappear_text_color", Color(0xff182431)));
                theme->disappearOptionStyle_.SetFontSize(
                    pattern->GetAttr<Dimension>("disappear_text_size", 14.0_fp));
                theme->disappearOptionStyle_.SetFontWeight(FontWeight::REGULAR);
                theme->disappearOptionStyle_.SetAdaptTextSize(theme->disappearOptionStyle_.GetFontSize(),
                    pattern->GetAttr<Dimension>("picker_normal_option_min_font_size", 0.0_fp));
                theme->disappearOptionStyle_.SetMaxLines(1);
                theme->disappearOptionStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);
            }

            theme->focusOptionStyle_.SetFontSize(pattern->GetAttr<Dimension>("picker_focus_option_font_size", 0.0_fp));
            theme->focusOptionStyle_.SetTextColor(pattern->GetAttr<Color>("picker_focus_option_text_color", Color()));
            theme->focusOptionStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("picker_focus_option_weight", 0.0))));
            theme->focusOptionStyle_.SetAdaptTextSize(theme->focusOptionStyle_.GetFontSize(),
                pattern->GetAttr<Dimension>("picker_select_option_min_font_size", 0.0_fp));
            theme->focusOptionStyle_.SetMaxLines(1);
            theme->focusOptionStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);

            if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
                theme->focusOptionStyle_ = theme->selectedOptionStyle_; // focus style the same with selected on phone
            }
        }

        void InitializeTextStyles(const RefPtr<PickerTheme>& theme, const RefPtr<ThemeStyle>& themeStyle) const
        {
            InitializeItemTextStyles(theme, themeStyle);
            InitializeTitleTextStyles(theme, themeStyle);
            InitializeButtonTextStyles(theme, themeStyle);
        }
    };

    ~PickerTheme() override = default;

    RefPtr<PickerTheme> clone() const
    {
        auto theme = AceType::Claim(new PickerTheme());
        theme->selectedOptionSize_ = selectedOptionSize_;
        theme->selectedOptionStyle_ = selectedOptionStyle_;
        theme->normalOptionSize_ = normalOptionSize_;
        theme->normalOptionStyle_ = normalOptionStyle_;
        theme->disappearOptionStyle_ = disappearOptionStyle_;
        theme->showOptionCount_ = showOptionCount_;
        theme->optionSizeUnit_ = optionSizeUnit_;
        theme->popupDecoration_ = popupDecoration_;
        theme->focusColor_ = focusColor_;
        theme->popupEdge_ = popupEdge_;
        theme->focusOptionStyle_ = focusOptionStyle_;
        theme->focusOptionDecoration_ = focusOptionDecoration_;
        theme->selectedOptionDecoration_ = selectedOptionDecoration_;
        theme->buttonStyle_ = buttonStyle_;
        theme->showButtons_ = showButtons_;
        theme->buttonWidth_ = buttonWidth_;
        theme->buttonHeight_ = buttonHeight_;
        theme->buttonTopPadding_ = buttonTopPadding_;
        theme->jumpInterval_ = jumpInterval_;
        theme->columnIntervalMargin_ = columnIntervalMargin_;
        theme->focusRadius_ = focusRadius_;
        theme->optionPadding_ = optionPadding_;
        theme->titleStyle_ = titleStyle_;
        theme->titleBottomPadding_ = titleBottomPadding_;
        theme->popupOutDecoration_ = popupOutDecoration_;
        theme->lunarWidth_ = lunarWidth_;
        theme->lunarHeight_ = lunarHeight_;
        theme->timeSplitter_ = timeSplitter_;
        theme->rotateInterval_ = rotateInterval_;
        theme->dividerThickness_ = dividerThickness_;
        theme->dividerSpacing_ = dividerSpacing_;
        theme->dividerColor_ = dividerColor_;
        theme->gradientHeight_ = gradientHeight_;
        theme->columnFixedWidth_ = columnFixedWidth_;
        theme->disappearOptionStyle_ = disappearOptionStyle_;
        theme->pressColor_ = pressColor_;
        theme->hoverColor_ = hoverColor_;
        theme->lunarswitchTextColor_ = lunarswitchTextColor_;
        theme->lunarswitchTextSize_ = lunarswitchTextSize_;
        theme->defaultStartDate_ = defaultStartDate_;
        theme->defaultEndDate_ = defaultEndDate_;
        return theme;
    }

    const TextStyle& GetOptionStyle(bool selected, bool focus) const
    {
        if (!selected) {
            return normalOptionStyle_;
        }

        if (focus) {
            return focusOptionStyle_;
        }

        return selectedOptionStyle_;
    }
    void SetOptionStyle(bool selected, bool focus, const TextStyle& value)
    {
        if (!selected) {
            normalOptionStyle_ = value;
        } else if (focus) {
            focusOptionStyle_ = value;
        } else {
            selectedOptionStyle_ = value;
        }
    }

    const TextStyle& GetDisappearOptionStyle() const
    {
        return disappearOptionStyle_;
    }
    void SetDisappearOptionStyle(const TextStyle& value)
    {
        disappearOptionStyle_ = value;
    }

    const TextStyle& GetButtonStyle() const
    {
        return buttonStyle_;
    }

    const RefPtr<Decoration>& GetOptionDecoration(bool focus)
    {
        if (focus) {
            return focusOptionDecoration_;
        }

        return selectedOptionDecoration_;
    }
    void SetOptionDecoration(bool focus, const RefPtr<Decoration>& value)
    {
        if (focus) {
            focusOptionDecoration_ = value;
        } else {
            selectedOptionDecoration_ = value;
        }
    }

    const Size& GetOptionSize(bool selected) const
    {
        if (selected) {
            return selectedOptionSize_;
        }

        return normalOptionSize_;
    }

    uint32_t GetShowOptionCount() const
    {
        return showOptionCount_;
    }

    DimensionUnit GetOptionSizeUnit() const
    {
        return optionSizeUnit_;
    }

    const RefPtr<Decoration>& GetPopupDecoration(bool isOutBox) const
    {
        if (!isOutBox) {
            return popupDecoration_;
        }
        return popupOutDecoration_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    const Edge& GetPopupEdge() const
    {
        return popupEdge_;
    }

    bool GetShowButtons() const
    {
        return showButtons_;
    }

    const Dimension& GetButtonWidth() const
    {
        return buttonWidth_;
    }

    const Dimension& GetButtonHeight() const
    {
        return buttonHeight_;
    }

    const Dimension& GetButtonTopPadding() const
    {
        return buttonTopPadding_;
    }

    const Dimension& GetJumpInterval() const
    {
        return jumpInterval_;
    }

    const Dimension& GetColumnIntervalMargin() const
    {
        return columnIntervalMargin_;
    }

    const Radius& GetFocusRadius() const
    {
        return focusRadius_;
    }

    double GetOptionPadding() const
    {
        return optionPadding_;
    }
    void SetOptionPadding(double value)
    {
        optionPadding_ = value;
    }

    const TextStyle& GetTitleStyle() const
    {
        return titleStyle_;
    }

    const Dimension& GetTitleBottomPadding() const
    {
        return titleBottomPadding_;
    }

    const Dimension& GetLunarWidth() const
    {
        return lunarWidth_;
    }

    const Dimension& GetLunarHeight() const
    {
        return lunarHeight_;
    }

    bool HasTimeSplitter() const
    {
        return (timeSplitter_ > 0);
    }

    double GetRotateInterval() const
    {
        return rotateInterval_;
    }

    const Dimension& GetDividerThickness() const
    {
        return dividerThickness_;
    }

    const Dimension& GetDividerSpacing() const
    {
        return dividerSpacing_;
    }

    const Color& GetDividerColor() const
    {
        return dividerColor_;
    }

    const Dimension& GetGradientHeight() const
    {
        return gradientHeight_;
    }

    const Dimension& GetColumnFixedWidth() const
    {
        return columnFixedWidth_;
    }

    Dimension GetColumnBottomTotalHeight(bool hasLunar) const
    {
        if (hasLunar) {
            return buttonHeight_ + lunarHeight_ + buttonTopPadding_ * 2 + popupEdge_.Bottom();
        } else {
            return buttonHeight_ + buttonTopPadding_ + popupEdge_.Bottom();
        }
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Dimension& GetPaddingHorizontal() const
    {
        return paddingHorizontal_;
    }

    const Dimension& GetContentMarginVertical() const
    {
        return contentMarginVertical_;
    }

    const Dimension& GetLunarSwitchTextSize() const
    {
        return lunarswitchTextSize_;
    }

    const Color& GetLunarSwitchTextColor() const
    {
        return lunarswitchTextColor_;
    }

    const PickerDate& GetDefaultStartDate() const
    {
        return defaultStartDate_;
    }

    const PickerDate& GetDefaultEndDate() const
    {
        return defaultEndDate_;
    }

private:
    PickerTheme() = default;

    Color focusColor_;
    Color hoverColor_;
    Color pressColor_;
    Color lunarswitchTextColor_;

    Radius focusRadius_;
    uint32_t showOptionCount_ = 0;
    bool showButtons_ = false;
    Dimension jumpInterval_;

    // popup style
    RefPtr<Decoration> popupDecoration_;
    RefPtr<Decoration> popupOutDecoration_;
    Edge popupEdge_;

    // column
    Dimension columnIntervalMargin_;

    // text style
    TextStyle focusOptionStyle_;
    TextStyle selectedOptionStyle_;
    TextStyle normalOptionStyle_;
    TextStyle disappearOptionStyle_;
    TextStyle buttonStyle_;
    TextStyle titleStyle_;

    // text around decoration
    RefPtr<Decoration> selectedOptionDecoration_;
    RefPtr<Decoration> focusOptionDecoration_;

    // option size
    Size selectedOptionSize_;
    Size normalOptionSize_;
    double optionPadding_ = 0.0;
    DimensionUnit optionSizeUnit_ = DimensionUnit::PX;

    // buttons size
    Dimension buttonWidth_;
    Dimension buttonHeight_;
    Dimension buttonTopPadding_;
    Dimension titleBottomPadding_;

    // lunar size
    Dimension lunarWidth_;
    Dimension lunarHeight_;

    uint32_t timeSplitter_ = 0;

    double rotateInterval_ = 0.0;
    Dimension dividerThickness_;
    Dimension dividerSpacing_;
    Color dividerColor_;
    Dimension gradientHeight_;
    Dimension columnFixedWidth_;

    Dimension paddingHorizontal_;
    Dimension contentMarginVertical_;
    Dimension lunarswitchTextSize_;

    PickerDate defaultStartDate_ = PickerDate(1970, 1, 1);
    PickerDate defaultEndDate_ = PickerDate(2100, 12, 31);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_THEME_H
