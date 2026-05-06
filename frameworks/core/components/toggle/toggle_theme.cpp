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

#include "core/components/toggle/toggle_theme.h"

#include "core/components/common/layout/constants.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

RefPtr<ToggleTheme> ToggleTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<ToggleTheme> theme = AceType::MakeRefPtr<ToggleTheme>();
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void ToggleTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ToggleTheme>& theme) const
{
    RefPtr<ThemeStyle> togglePattern = themeConstants->GetPatternByName(THEME_PATTERN_TOGGLE);
    if (!togglePattern) {
        return;
    }
    theme->textStyle_.SetFontSize(togglePattern->GetAttr<Dimension>("toggle_text_font_size", 0.0_fp));
    theme->textStyle_.SetFontWeight(
        FontWeight(static_cast<int32_t>(togglePattern->GetAttr<double>("toggle_text_font_weight", 0.0))));
    theme->height_ = togglePattern->GetAttr<Dimension>("toggle_height", 0.0_vp);
    theme->padding_ = Edge(togglePattern->GetAttr<Dimension>("toggle_padding_horizontal", 0.0_vp).Value(),
        togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Value(),
        togglePattern->GetAttr<Dimension>("toggle_padding_horizontal", 0.0_vp).Value(),
        togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Value(),
        togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Unit());
    theme->disabledAlpha_ = togglePattern->GetAttr<double>("toggle_disable_alpha", 0.0);
    theme->backgroundColor_ = togglePattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
    theme->checkedColor_ = togglePattern->GetAttr<Color>("bg_color_checked", Color())
        .BlendOpacity(togglePattern->GetAttr<double>("bg_color_checked_alpha", 0.0));
    theme->textStyle_.SetTextColor(togglePattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color()));
    theme->pressedBlendColor_ = togglePattern->GetAttr<Color>("bg_color_pressed_blend", Color());
    theme->textMargin_ = togglePattern->GetAttr<Dimension>("text_margin", Dimension());
    theme->buttonMargin_ = togglePattern->GetAttr<Dimension>("button_margin", Dimension());
    theme->buttonHeight_ = togglePattern->GetAttr<Dimension>("button_height", Dimension());
    theme->buttonRadius_ = togglePattern->GetAttr<Dimension>("button_radius", Dimension());
    theme->textFontSize_ = togglePattern->GetAttr<Dimension>("text_font_size", Dimension());
    theme->textColor_ = togglePattern->GetAttr<Color>("text_color", Color());
    theme->shadowNormal_ = static_cast<uint32_t>(
        togglePattern->GetAttr<double>("shadow_default_status_button", SHADOW_NONE));
    theme->shadowFocus_ = static_cast<uint32_t>(
        togglePattern->GetAttr<double>("shadow_focus_status_button", SHADOW_NONE));
    theme->scaleHoverOrFocus_ = togglePattern->GetAttr<double>("scale_focus_status_button", 1.0);
    theme->borderWidth_ = togglePattern->GetAttr<Dimension>("border_width_status_button", Dimension());
    theme->borderColorChecked_ = togglePattern->GetAttr<Color>("border_color_status_button_checked", Color());
    theme->borderWidthUnchecked_ =
        togglePattern->GetAttr<Dimension>("border_width_status_button_unchecked", theme->borderWidth_);
    theme->borderColorUnchecked_ = togglePattern->GetAttr<Color>(
        "border_color_status_button_unchecked", Color());
    theme->bgColorFocusChecked_ = togglePattern->GetAttr<Color>(
        "bg_color_focus_status_button_checked", Color())
        .BlendOpacity(togglePattern->GetAttr<double>("bg_color_checked_focus_alpha", 0.0));
    theme->bgColorFocusUnchecked_ = togglePattern->GetAttr<Color>(
        "bg_color_focus_status_button_unchecked", Color());
    theme->textColorFocus_ = togglePattern->GetAttr<Color>("status_button_text_color_focus", Color());
}

} // namespace OHOS::Ace
