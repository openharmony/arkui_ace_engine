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
}
} // namespace OHOS::Ace