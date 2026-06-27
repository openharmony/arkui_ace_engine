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

#include "core/components/swiper/swiper_indicator_theme.h"

#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
namespace {
constexpr double SWIPER_ARROW_ALPHA_DISABLED = 0.4;
constexpr Dimension SWIPER_ARROW_SCALE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_SMALL_ARROW_BACKGROUND_SIZE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_SMALL_ARROW_SIZE = 18.0_vp;
constexpr Dimension SWIPER_ARROW_BIG_ARROW_BACKGROUND_SIZE = 32.0_vp;
constexpr Dimension SWIPER_ARROW_BIG_ARROW_SIZE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_HORIZONTAL_MARGIN_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_ARROW_VERTICAL_MARGIN_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_FOCUSED_BORDER_WIDTH = 2.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_PADDING_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_VERTICAL_PADDING_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_HEIGHT = 32.0_vp;
constexpr Dimension SWIPER_INDICATOR_DOT_PADDING_DEFAULT = 12.0_vp;
constexpr Dimension SWIPER_INDICATOR_DOT_ITEM_SPACE = 8.0_vp;
} // namespace

RefPtr<SwiperIndicatorTheme> SwiperIndicatorTheme::Builder::Build(
    const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<SwiperIndicatorTheme> theme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void SwiperIndicatorTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SwiperIndicatorTheme>& theme) const
{
    theme->leftSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_left");
    theme->rightSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_right");
    theme->upSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_up");
    theme->downSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_down");

    RefPtr<ThemeStyle> swiperPattern = themeConstants->GetPatternByName(THEME_PATTERN_SWIPER);
    if (!swiperPattern) {
        LOGW("find pattern of swiper fail");
        return;
    }
    theme->indicatorPaddingDot_ = swiperPattern->GetAttr<Dimension>("indicator_padding_dot", 12.0_vp);
    theme->unSelectedColor_ = swiperPattern->GetAttr<Color>("color_focus_unselected", Color::TRANSPARENT);
    theme->focusedBgColor_ = swiperPattern->GetAttr<Color>("color_focus_bg", Color::TRANSPARENT);
    theme->indicatorBgHeight_ = swiperPattern->GetAttr<Dimension>("indicator_bg_height", 12.0_vp);
    theme->focusedSelectedColor_ =
        swiperPattern->GetAttr<Color>("indicator_color_focused_selected", Color::TRANSPARENT);
    theme->scaleSwiper_ = swiperPattern->GetAttr<double>("indicator_scale_swiper", INDICATOR_ZOOM_IN_SCALE);
    theme->indicatorFocusedPadding_ = swiperPattern->GetAttr<Dimension>("indicator_focused_padding", 0.0_vp);
    theme->clipToBounds_ = static_cast<bool>(swiperPattern->GetAttr<int>("clip_bounds", 1));
    theme->focusStyleType_ = swiperPattern->GetAttr<int>("swiper_focus_style_type", 0);
    theme->size_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_size", 0.0_vp);
    theme->selectedSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_selected_size", 0.0_vp);
    theme->isHasMask_ = static_cast<bool>(swiperPattern->GetAttr<double>("swiper_indicator_mask", 0.0));
    theme->indicatorPointPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_point_padding", 0.0_vp);
    theme->startEndPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_start_end_padding", 0.0_vp);
    theme->pressPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_press_padding", 0.0_vp);
    theme->pressPointPadding_ =
        swiperPattern->GetAttr<Dimension>("swiper_indicator_press_point_padding", 0.0_vp);
    theme->pressSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_press_size", 0.0_vp);
    theme->hoverSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_hover_size", 0.0_vp);
    theme->hotZoneSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_hotzone_size", 0.0_vp);
    theme->isIndicatorDisabled_ =
        static_cast<bool>(swiperPattern->GetAttr<double>("swiper_indicator_disabled", 0.0));
    theme->animationCurve_ =
        AnimationCurve(static_cast<int32_t>(swiperPattern->GetAttr<double>("swiper_animation_curve", 0.0)));
    theme->animationOpacity_ =
        static_cast<bool>(swiperPattern->GetAttr<double>("swiper_animation_opacity", 0.0));
    theme->color_ = swiperPattern->GetAttr<Color>("indicator_color", Color::TRANSPARENT);
    theme->hotZoneColor_ = swiperPattern->GetAttr<Color>("indicator_hotzone_color", Color::TRANSPARENT);
    theme->indicatorTextFocusColor_ =
        swiperPattern->GetAttr<Color>("indicator_text_color_focused", Color::TRANSPARENT);
    theme->digitalIndicatorTextStyle_.SetTextColor(
        swiperPattern->GetAttr<Color>("indicator_text_font_color", Color::TRANSPARENT));
    theme->digitalIndicatorTextStyle_.SetFontSize(
        swiperPattern->GetAttr<Dimension>("indicator_text_font_size", 14.0_vp));
    theme->selectedColor_ = swiperPattern->GetAttr<Color>("indicator_color_selected", Color::TRANSPARENT);
    theme->hoverColor_ = swiperPattern->GetAttr<Color>("indicator_color_hover", Color::TRANSPARENT);
    theme->pressedColor_ = swiperPattern->GetAttr<Color>("indicator_color_pressed", Color::TRANSPARENT);
    theme->focusedColor_ = swiperPattern->GetAttr<Color>("indicator_color_focused", Color::TRANSPARENT);
    ParsePattern2(theme, swiperPattern);
}

void SwiperIndicatorTheme::Builder::ParsePattern2(
    const RefPtr<SwiperIndicatorTheme>& theme, const RefPtr<ThemeStyle> swiperPattern) const
{
    theme->preAccessibilityText_ = swiperPattern->GetAttr<std::string>("prev_arrow_accessibility_text", "");
    theme->nextAccessibilityText_ = swiperPattern->GetAttr<std::string>("next_arrow_accessibility_text", "");
    theme->focusedBorderWidth_ = SWIPER_FOCUSED_BORDER_WIDTH;
    theme->hoverArrowBackgroundColor_ =
        swiperPattern->GetAttr<Color>(ARROW_COLOR_BOARDCOLOR_HOVER, Color::TRANSPARENT);
    theme->clickArrowBackgroundColor_ =
        swiperPattern->GetAttr<Color>(ARROW_COLOR_BOARDCOLOR_CLICK, Color::TRANSPARENT);
    theme->arrowColorPrimary_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
    theme->arrowColorPrimaryContrary_ =
        swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY_CONTRARY, Color::TRANSPARENT);
    theme->arrowDisabledAlpha_ =
        swiperPattern->GetAttr<double>(ARROW_DISABLED_ALPHA, SWIPER_ARROW_ALPHA_DISABLED);
    theme->arrowScale_ = SWIPER_ARROW_SCALE;
    theme->arrowHorizontalMargin_ =
        swiperPattern->GetAttr<Dimension>(ARROW_HORIZONTAL_MARGIN, SWIPER_ARROW_HORIZONTAL_MARGIN_DEFAULT);
    theme->arrowVerticalMargin_ =
        swiperPattern->GetAttr<Dimension>(ARROW_VERTICAL_MARGIN, SWIPER_ARROW_VERTICAL_MARGIN_DEFAULT);
    theme->smallArrowBackgroundSize_ = SWIPER_ARROW_SMALL_ARROW_BACKGROUND_SIZE;
    theme->smallArrowSize_ = SWIPER_ARROW_SMALL_ARROW_SIZE;
    theme->smallArrowBackgroundColor_ = Color::TRANSPARENT;
    theme->smallArrowColor_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
    theme->bigArrowBackgroundSize_ = SWIPER_ARROW_BIG_ARROW_BACKGROUND_SIZE;
    theme->bigArrowSize_ = SWIPER_ARROW_BIG_ARROW_SIZE;
    theme->bigArrowBackgroundColor_ =
        swiperPattern->GetAttr<Color>(ARROW_COLOR_COMPONENT_NORMAL, Color::TRANSPARENT);
    theme->bigArrowColor_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
    theme->indicatorDigitPadding_ = SWIPER_INDICATOR_DIGIT_PADDING_DEFAULT;
    theme->indicatorDigitVerticalPadding_ = SWIPER_INDICATOR_DIGIT_VERTICAL_PADDING_DEFAULT;
    theme->indicatorDotPadding_ = SWIPER_INDICATOR_DOT_PADDING_DEFAULT;
    theme->indicatorDigitHeight_ = SWIPER_INDICATOR_DIGIT_HEIGHT;
    theme->indicatorDotItemSpace_ =
        swiperPattern->GetAttr<Dimension>("swiper_indicator_dot_item_space", SWIPER_INDICATOR_DOT_ITEM_SPACE);
    theme->arcSelectedItemColor_ = swiperPattern->GetAttr<Color>("dot_active_color", Color::TRANSPARENT);
    theme->arcItemColor_ = swiperPattern->GetAttr<Color>("dot_color", Color::TRANSPARENT);
    theme->arcMaskStartColor_ = swiperPattern->GetAttr<Color>("mask_color_start", Color::TRANSPARENT);
    theme->arcMaskEndColor_ = swiperPattern->GetAttr<Color>("mask_color_end", Color::TRANSPARENT);
    theme->arcContainerColor_ = swiperPattern->GetAttr<Color>("container_color", Color::TRANSPARENT);
    theme->indicatorDragMinAngle_ =
        swiperPattern->GetAttr<double>("swiper_indicator_drag_min_angle", INDICATOR_DRAG_MIN_ANGLE);
    theme->indicatorDragMaxAngle_ =
        swiperPattern->GetAttr<double>("swiper_indicator_drag_max_angle", INDICATOR_DRAG_MAX_ANGLE);
#ifdef SUPPORT_DIGITAL_CROWN
    ParsePattern3(theme, swiperPattern);
#endif
}

#ifdef SUPPORT_DIGITAL_CROWN
void SwiperIndicatorTheme::Builder::ParsePattern3(
    const RefPtr<SwiperIndicatorTheme>& theme, const RefPtr<ThemeStyle> swiperPattern) const
{
    theme->slowVelocityThreshold_ = swiperPattern->GetAttr<double>("swiper_slow_velocity_threshold", 0.0f);
    theme->mediumVelocityThreshold_ = swiperPattern->GetAttr<double>("swiper_medium_velocity_threshold", 0.0f);
    theme->fastVelocityThreshold_ = swiperPattern->GetAttr<double>("swiper_fast_velocity_threshold", 0.0f);
    theme->displayControlRatioVerySlow_ =
        swiperPattern->GetAttr<double>("swiper_display_control_ratio_very_slow", 0.0f);
    theme->displayControlRatioSlow_ = swiperPattern->GetAttr<double>("swiper_display_control_ratio_slow", 0.0f);
    theme->displayControlRatioMedium_ =
        swiperPattern->GetAttr<double>("swiper_display_control_ratio_medium", 0.0f);
    theme->displayControlRatioFast_ = swiperPattern->GetAttr<double>("swiper_display_control_ratio_fast", 0.0f);
    theme->crownSensitivityLow_ = swiperPattern->GetAttr<double>("swiper_crown_sensitivity_low", 0.0f);
    theme->crownSensitivityMedium_ = swiperPattern->GetAttr<double>("swiper_crown_sensitivity_medium", 0.0f);
    theme->crownSensitivityHigh_ = swiperPattern->GetAttr<double>("swiper_crown_sensitivity_high", 0.0f);
    theme->springVelocityThreshold_ = swiperPattern->GetAttr<double>("swiper_spring_velocity_threshold", 0.0f);
    theme->crownTranslocationRatio_ = swiperPattern->GetAttr<double>("swiper_crown_translocation_ratio", 0.0f);
}
#endif

} // namespace OHOS::Ace
