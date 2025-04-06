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

#include "core/components/checkable/checkable_theme.h"

namespace OHOS::Ace {
void CheckboxTheme::Builder::SetCheckboxFocus(const RefPtr<ThemeConstants>& themeConstants,
    const RefPtr<CheckboxTheme>& theme) const
{
    RefPtr<ThemeStyle> checkboxPattern = themeConstants->GetPatternByName(THEME_PATTERN_CHECKBOX);
    if (!checkboxPattern) {
        LOGE("Pattern of checkbox is null, please check!");
        return;
    }
    theme->focusBoardColor_ = checkboxPattern->GetAttr<Color>("color_focused_bg", Color(0xffff0000));
    theme->focusBoardSize_ = checkboxPattern->GetAttr<Dimension>("size_focused_bg", 2.0_vp);
    theme->borderFocusedColor_ = checkboxPattern->GetAttr<Color>("focused_border_color", Color(0xffff0000));
    theme->focusedBGColorUnselected_ =
        checkboxPattern->GetAttr<Color>("focused_bg_color_unselected", Color(0xffff0000));
    theme->roundFocusBoardSize_ = checkboxPattern->GetAttr<Dimension>("round_size_focused_bg", 2.0_vp);
    theme->whiteBorderRadius_ = checkboxPattern->GetAttr<Dimension>("focus_white_border_radius", 0.0_vp);
    theme->focusLineColor_ = checkboxPattern->GetAttr<Color>("checkbox_focus_color_sys", Color(0xff007dff));
    theme->defaultRoundPaddingSize_ =
        checkboxPattern->GetAttr<Dimension>("checkbox_default_round_padding_size", 2.0_vp);
}

void CheckboxTheme::Builder::ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
    const RefPtr<CheckboxTheme>& theme) const
{
    RefPtr<ThemeStyle> checkboxPattern = themeConstants->GetPatternByName(THEME_PATTERN_CHECKBOX);
    if (!checkboxPattern) {
        LOGE("Pattern of checkbox is null, please check!");
        return;
    }
    theme->width_ = checkboxPattern->GetAttr<Dimension>("checkbox_size", 0.0_vp);
    theme->height_ = theme->width_;
    theme->hotZoneHorizontalPadding_ = checkboxPattern->GetAttr<Dimension>("checkbox_hotzone_padding", 0.0_vp);
    theme->defaultWidth_ = checkboxPattern->GetAttr<Dimension>("checkbox_default_size", 0.0_vp);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        theme->defaultPaddingSize_ =
            checkboxPattern->GetAttr<Dimension>("checkbox_default_padding_size", 2.0_vp);
        theme->defaultWidth_ = checkboxPattern->GetAttr<Dimension>("checkbox_default_size_twelve", 24.0_vp);
        theme->hoverPaddingSize_ = checkboxPattern->GetAttr<Dimension>("checkbox_hover_padding_size", 2.0_vp);
        theme->showCircleDial_ = static_cast<bool>(checkboxPattern->GetAttr<double>("radio_circle_dial", 0.0));
    }
    theme->hotZoneVerticalPadding_ = theme->hotZoneHorizontalPadding_;
    theme->defaultHeight_ = theme->defaultWidth_;
    theme->needFocus_ = static_cast<bool>(checkboxPattern->GetAttr<double>("checkbox_need_focus", 0.0));
    theme->backgroundSolid_ =
        static_cast<bool>(checkboxPattern->GetAttr<double>("checkbox_inactive_background_solid", 0.0));
    theme->borderWidth_ = checkboxPattern->GetAttr<Dimension>("checkbox_border_width", 0.0_vp);
    theme->checkStroke_ = checkboxPattern->GetAttr<Dimension>("checkbox_stroke_width", 0.0_vp);
    theme->shadowColor_ = checkboxPattern->GetAttr<Color>("checkbox_shadow_color", Color());
    theme->shadowWidth_ = checkboxPattern->GetAttr<Dimension>("checkbox_shadow_width", 0.0_vp);
    theme->pointColor_ = checkboxPattern->GetAttr<Color>("fg_color_checked", Color::RED);
    theme->activeColor_ = checkboxPattern->GetAttr<Color>("bg_color_checked", Color::RED);
    theme->inactiveColor_ = checkboxPattern->GetAttr<Color>("bg_border_color_unchecked", Color::RED);
    theme->focusColor_ = checkboxPattern->GetAttr<Color>("focus_border_color", Color::RED);
    theme->borderRadius_ = checkboxPattern->GetAttr<Dimension>("bg_border_radius", 0.0_vp);
    theme->hoverColor_ = checkboxPattern->GetAttr<Color>("hover_border_color", Color::RED);
    theme->clickEffectColor_ = checkboxPattern->GetAttr<Color>("click_effect_color", Color::RED);
    theme->inactivePointColor_ = checkboxPattern->GetAttr<Color>("bg_color_unchecked", Color::RED);
    theme->hoverRadius_ = checkboxPattern->GetAttr<Dimension>("hover_border_radius", 0.0_vp);
    theme->focusRadius_ = checkboxPattern->GetAttr<Dimension>("focus_border_radius", 0.0_vp);
    theme->focusPaintPadding_ = checkboxPattern->GetAttr<Dimension>("focus_paint_padding", 0.0_vp);
    theme->hoverDuration_ = checkboxPattern->GetAttr<double>("hover_animation_duration", 0.0);
    theme->hoverToTouchDuration_ = checkboxPattern->GetAttr<double>("hover_to_press_animation_duration", 0.0);
    theme->touchDuration_ = checkboxPattern->GetAttr<double>("touch_animation_duration", 0.0);
    theme->colorAnimationDuration_ = checkboxPattern->GetAttr<double>("color_animation_duration", 0.0);
    SetCheckboxFocus(themeConstants, theme);

    if (SystemProperties::GetDeviceType() != DeviceType::CAR) {
        return;
    }
    SetCheckboxSize(themeConstants, theme);
}

void SwitchTheme::Builder::ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
    const RefPtr<SwitchTheme>& theme) const
{
    RefPtr<ThemeStyle> switchPattern = themeConstants->GetPatternByName(THEME_PATTERN_SWITCH);
    if (!switchPattern) {
        LOGE("Pattern of switch is null, please check!");
        return;
    }
    theme->width_ = switchPattern->GetAttr<Dimension>("switch_pattern_width", 0.0_vp);
    theme->height_ = switchPattern->GetAttr<Dimension>("switch_pattern_height", 0.0_vp);
    theme->hotZoneHorizontalPadding_ =
        switchPattern->GetAttr<Dimension>("switch_hotzone_horizontal_padding", 0.0_vp);
    theme->hotZoneVerticalPadding_ =
        switchPattern->GetAttr<Dimension>("switch_hotzone_vertical_padding", 0.0_vp);
    theme->hotZoneHorizontalSize_ =
        switchPattern->GetAttr<Dimension>("switch_hotzone_horizontal_size", 6.0_vp);
    theme->hotZoneVerticalSize_ =
        switchPattern->GetAttr<Dimension>("switch_hotzone_vertical_size", 14.0_vp);
    theme->aspectRatio_ = switchPattern->GetAttr<double>("switch_aspect_ratio", 0.0);
    theme->backgroundSolid_ =
        static_cast<bool>(switchPattern->GetAttr<double>("switch_inactive_background_solid", 0.0));
    theme->defaultWidth_ = switchPattern->GetAttr<Dimension>("switch_default_width", 0.0_vp);
    theme->defaultHeight_ = switchPattern->GetAttr<Dimension>("switch_default_height", 0.0_vp);
    theme->needFocus_ = static_cast<bool>(switchPattern->GetAttr<double>("switch_need_focus", 0.0));
    theme->borderWidth_ = switchPattern->GetAttr<Dimension>("switch_border_width", 0.0_vp);
    theme->shadowColor_ = switchPattern->GetAttr<Color>("switch_shadow_color", Color());
    theme->shadowWidth_ = switchPattern->GetAttr<Dimension>("switch_pattern_shadow_width", 0.0_vp);
    theme->pointColor_ = switchPattern->GetAttr<Color>("fg_color_checked", Color::RED);
    theme->activeColor_ = switchPattern->GetAttr<Color>("bg_color_checked", Color::RED);
    theme->inactiveColor_ = switchPattern->GetAttr<Color>("bg_color_unchecked", Color::RED);
    theme->focusColor_ = switchPattern->GetAttr<Color>("focus_border_color", Color::RED);
    theme->hoverColor_ = switchPattern->GetAttr<Color>("hover_border_color", Color::RED);
    theme->hoverRadius_ = switchPattern->GetAttr<Dimension>("hover_border_radius", 0.0_vp);
    theme->inactivePointColor_ = switchPattern->GetAttr<Color>("fg_color_unchecked", Color::RED);
    theme->clickEffectColor_ = switchPattern->GetAttr<Color>("click_effect_color", Color::RED);
    theme->focusPaintPadding_ = switchPattern->GetAttr<Dimension>("focus_paint_padding", 0.0_vp);
    theme->hoverDuration_ = switchPattern->GetAttr<double>("hover_animation_duration", 0.0);
    theme->hoverToTouchDuration_ = switchPattern->GetAttr<double>("hover_to_press_animation_duration", 0.0);
    theme->touchDuration_ = switchPattern->GetAttr<double>("touch_animation_duration", 0.0);
    theme->colorAnimationDuration_ = switchPattern->GetAttr<double>("color_animation_duration", 0.0);
    theme->pointAnimationDuration_ = switchPattern->GetAttr<double>("point_animation_duration", 0.0);
    theme->interactiveHoverColor_ = switchPattern->GetAttr<Color>("interactive_hover", Color::RED);
    theme->interactivePressedColor_ = switchPattern->GetAttr<Color>("interactive_pressed", Color::RED);
    if (SystemProperties::GetDeviceType() != DeviceType::CAR) {
        return;
    }
    theme->width_ = switchPattern->GetAttr<Dimension>(SWITCH_WIDTH, 40.0_vp);
    theme->height_ = switchPattern->GetAttr<Dimension>(SWITCH_HEIGHT, 26.0_vp);
    theme->shadowWidth_ = switchPattern->GetAttr<Dimension>(SWITCH_SHADOW_WIDTH, 2.0_vp);
    theme->hotZoneHorizontalPadding_ = switchPattern->GetAttr<Dimension>(SWITCH_HORIZONTAL_PADDING, 4.0_vp);
    theme->hotZoneVerticalPadding_ = switchPattern->GetAttr<Dimension>(SWITCH_VERTICAL_PADDING, 13.0_vp);
}

void SwitchTheme::Builder::ParseSubStylePattern(const RefPtr<ThemeConstants>& themeConstants,
    const RefPtr<SwitchTheme>& theme) const
{
    RefPtr<ThemeStyle> switchPattern = themeConstants->GetPatternByName(THEME_PATTERN_SWITCH);
    if (!switchPattern) {
        LOGE("Pattern of switch is null, please check!");
        return;
    }
    theme->focusBoardWidth_ = switchPattern->GetAttr<Dimension>("switch_focus_board_width", 0.0_vp);
    theme->focusBoardHeight_ = switchPattern->GetAttr<Dimension>("switch_focus_board_height", 0.0_vp);
    theme->focusBoardRadius_ = switchPattern->GetAttr<Dimension>("switch_focus_board_radius", 0.0_vp);
    theme->focusBoardColor_ = switchPattern->GetAttr<Color>("switch_focus_board_color", Color());
    theme->focusedBGColorUnselected_ =
        switchPattern->GetAttr<Color>("switch_focus_bgColor_unselected", Color());
    theme->focusedPointColorUnselected_ =
        switchPattern->GetAttr<Color>("switch_focus_pointColor_unselected", Color());
    theme->pointColorUnchecked_ = switchPattern->GetAttr<Color>("switch_unchecked_pointColor", Color());
    theme->isUseDiffPointColor_ =
        static_cast<bool>(switchPattern->GetAttr<double>("switch_different_pointColor", 0.0));
    theme->focusPadding_ = switchPattern->GetAttr<Dimension>("switch_focus_box_padding", 0.0_vp);
    theme->switchOnText_ = switchPattern->GetAttr<std::string>("switch_on_text", "");
    theme->switchOffText_ = switchPattern->GetAttr<std::string>("switch_off_text", "");
}

void CheckboxTheme::Builder::SetCheckboxSize(const RefPtr<ThemeConstants>& themeConstants,
    const RefPtr<CheckboxTheme>& theme) const
{
    RefPtr<ThemeStyle> checkboxPattern = themeConstants->GetPatternByName(THEME_PATTERN_CHECKBOX);
    // width/height/borderRadius not exist in theme
    theme->width_ = checkboxPattern->GetAttr<Dimension>("width", 26.0_vp);
    theme->height_ = theme->width_;
    theme->borderRadius_ = checkboxPattern->GetAttr<Dimension>("hover_border_radius", 4.0_vp);
    theme->hotZoneHorizontalPadding_ =
        checkboxPattern->GetAttr<Dimension>("hotzone_padding_horizontal", 11.0_vp);
    theme->hotZoneVerticalPadding_ = theme->hotZoneHorizontalPadding_;
}

} // namespace OHOS::Ace
