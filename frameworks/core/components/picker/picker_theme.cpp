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

#include "core/components/picker/picker_theme.h"

//In landscape mode, if the height is below 640, no aging adaptation will be performed
constexpr double DEFAULT_LIMIT_WIDTH = 640.0;

namespace OHOS::Ace {
void PickerTheme::Builder::Parse(const RefPtr<ThemeStyle>& style, const RefPtr<PickerTheme>& theme) const
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
    theme->popupDecoration_->SetBorderRadius(Radius(pattern->GetAttr<Dimension>("picker_popup_radius", 0.0_vp)));
    theme->popupEdge_.SetLeft(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
    theme->popupEdge_.SetTop(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
    theme->popupEdge_.SetRight(pattern->GetAttr<Dimension>("picker_popup_padding", 0.0_vp));
    theme->popupEdge_.SetBottom(pattern->GetAttr<Dimension>("picker_popup_padding_bottom", 0.0_vp));
    auto showOptionCount = static_cast<int32_t>(pattern->GetAttr<double>("picker_show_option_count", 0.0));
    theme->showOptionCount_ = showOptionCount < 0 ? theme->showOptionCount_ : static_cast<uint32_t>(showOptionCount);
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
    theme->popupOutDecoration_->SetBackgroundColor(pattern->GetAttr<Color>("picker_dialog_mask_color", Color()));
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
    if (!theme->IsCircleDial()) {
        theme->focusOptionStyle_.SetTextColor(theme->selectedOptionStyle_.GetTextColor());
    }
    theme->normalOptionStyle_.SetTextColor(
        pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, theme->normalOptionStyle_.GetTextColor()));
    theme->disappearOptionStyle_.SetTextColor(theme->normalOptionStyle_.GetTextColor());
    theme->titleStyle_.SetTextColor(theme->normalOptionStyle_.GetTextColor());
    theme->dividerColor_ = pattern->GetAttr<Color>("divider_color", theme->dividerColor_);
    theme->dividerThickness_ = pattern->GetAttr<Dimension>("divider_thickness", 2.0_px);
    theme->contentMarginVertical_ = pattern->GetAttr<Dimension>("content_margin_vertical", 8.0_vp);
    theme->lunarswitchTextSize_ = pattern->GetAttr<Dimension>("lunarswitch_text_size", theme->lunarswitchTextSize_);
    theme->lunarswitchTextColor_ = pattern->GetAttr<Color>("lunarswitch_text_color", theme->lunarswitchTextColor_);
    auto showCountLandscape = static_cast<int32_t>(pattern->GetAttr<double>("picker_show_count_landscape", 3));
    theme->showCountLandscape_ =
        showCountLandscape < 0 ? theme->showCountLandscape_ : static_cast<uint32_t>(showCountLandscape);
    auto showCountPortrait = static_cast<int32_t>(pattern->GetAttr<double>("picker_show_count_portrait", 5));
    theme->showCountPortrait_ =
        showCountPortrait < 0 ? theme->showCountPortrait_ : static_cast<uint32_t>(showCountPortrait);
    theme->deviceHeightLimit_ = pattern->GetAttr<double>("picker_device_height_limit", DEFAULT_LIMIT_WIDTH);
    theme->gradientHeightLimit_ = pattern->GetAttr<Dimension>("picker_gradient_limit", 54.0_vp);
    theme->dividerSpacingHeightLimit_ = pattern->GetAttr<Dimension>("picker_divider_spacing_limit", 64.0_vp);
    theme->pickerDialogFontPadding_ = pattern->GetAttr<Dimension>("picker_divider_spacing_padding", 8.0_vp);
    theme->selectedTextStyle_ = pattern->GetAttr<Dimension>("picker_select_Font_limit", 40.0_fp);
    theme->normalTextStyle_ = pattern->GetAttr<Dimension>("picker_normal_Font_limit", 32.0_fp);
    theme->disappearTextStyle_ = pattern->GetAttr<Dimension>("picker_disappear_Font_limit", 28.0_fp);
    theme->pickerDialogNormalFontScale_ = pattern->GetAttr<double>("picker_dialog_normal", 1.0f);
    theme->pickerDialogMaxOneFontScale_ = pattern->GetAttr<double>("picker_dialog_maxone", 1.75f);
    theme->pickerDialogMaxTwoFontScale_ = pattern->GetAttr<double>("picker_dialog_maxtwo", 2.0f);
    theme->pickerDialogMaxThirdFontScale_ = pattern->GetAttr<double>("picker_dialog_maxthird", 3.2f);
    theme->titleFontScaleLimit_ = pattern->GetAttr<double>("picker_dialog_max", 1.45f);
}
} // namespace OHOS::Ace