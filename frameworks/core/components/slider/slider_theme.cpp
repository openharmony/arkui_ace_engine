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

#include "core/components/slider/slider_theme.h"

#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

RefPtr<SliderTheme> SliderTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<SliderTheme> theme = AceType::MakeRefPtr<SliderTheme>();
    if (!themeConstants) {
        return theme;
    }
    // init theme from global data
    ParsePattern(themeConstants, theme);
    return theme;
}

void SliderTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SliderTheme>& theme) const
{
    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SLIDER);
    if (pattern) {
        const double defaultMarkColorAplpa = 0.1;
        theme->trackBgColor_ = pattern->GetAttr<Color>("track_bg_color", Color::RED);
        theme->trackSelectedColor_ = pattern->GetAttr<Color>("track_color_selected", Color::RED);
        theme->markerColor_ = pattern->GetAttr<Color>("marker_color", Color::RED)
                .BlendOpacity(pattern->GetAttr<double>("marker_color_alpha", defaultMarkColorAplpa));
        theme->tipTextColor_ = pattern->GetAttr<Color>("tip_text_color", Color::RED);
        theme->tipColor_ = pattern->GetAttr<Color>("tip_color", Color::RED);
        theme->blockHoverColor_ = pattern->GetAttr<Color>("block_color_hovered", Color::RED);
        theme->blockPressedColor_ = pattern->GetAttr<Color>("block_color_pressed", BLOCK_COLOR_PRESSED);
        theme->blockOuterEdgeColor_ =
            pattern->GetAttr<Color>("block_outer_edge_color", BLOCK_OUTER_EDGE_COLOR);
        theme->bubbleToCircleCenterDistance_ =
            pattern->GetAttr<Dimension>("bubble_to_circle_center_distance", BUBBLE_TO_CIRCLE_CENTER_DISTANCE);
        theme->measureContentDefaultWidth_ =
            pattern->GetAttr<Dimension>("measure_content_default_width", MEASURE_CONTENT_DEFAULT_WIDTH);
        theme->outsetHotBlockShadowWidth_ =
            pattern->GetAttr<Dimension>("outset_hot_block_shadow_width", OUTSET_HOT_BLOCK_SHADOW_WIDTH);
        theme->insetHotBlockShadowWidth_ =
            pattern->GetAttr<Dimension>("inset_hot_block_shadow_width", INSET_HOT_BLOCK_SHADOW_WIDTH);
        theme->focusSideDistance_ =
            pattern->GetAttr<Dimension>("focus_side_distance", FOCUS_SIDE_DISTANCE);
        theme->layoutMaxLength_ = pattern->GetAttr<Dimension>("slider_max_length", .0_vp);
        theme->hoverAnimationDuration_ = pattern->GetAttr<double>("hover_animation_duration", 0.0);
        theme->pressAnimationDuration_ = pattern->GetAttr<double>("press_animation_duration", 0.0);
        theme->moveAnimationDuration_ = pattern->GetAttr<double>("move_animation_duration", 0.0);
        theme->sliderPPI_ = pattern->GetAttr<double>("slider_pixels_per_inch", DEFAULT_SLIDER_PPI);
        theme->disabledAlpha_ = pattern->GetAttr<double>("slider_disable_alpha", 0.0);
        theme->outsetBlockSize_ = pattern->GetAttr<Dimension>("outset_block_size", 16.0_vp);
        theme->outsetBlockHotSize_ = pattern->GetAttr<Dimension>("outset_block_hot_region_size", 40.0_vp);
        theme->blockColor_ = pattern->GetAttr<Color>("block_color", Color(0xffffffff));
        theme->outsetTrackThickness_ = pattern->GetAttr<Dimension>("outset_track_thickness", 4.0_vp);
        theme->insetTrackThickness_ = pattern->GetAttr<Dimension>("inset_track_thickness", 20.0_vp);
        theme->insetBlockSize_ = pattern->GetAttr<Dimension>("inset_block_size", 12.0_vp);
        theme->insetBlockHotSize_ = pattern->GetAttr<Dimension>("inset_block_hot_region_size", 32.0_vp);
        theme->noneTrackThickness_ = pattern->GetAttr<Dimension>("none_track_thickness", 4.0_vp);
        theme->noneBlockHotSize_ = pattern->GetAttr<Dimension>("none_block_hot_region_size", 40.0_vp);
        theme->markerSize_ = pattern->GetAttr<Dimension>("marker_size", 4.0_vp);
        theme->tipFontSize_ = pattern->GetAttr<Dimension>("tip_font_size", 14.0_fp);
        theme->tipTextPadding_ = pattern->GetAttr<Dimension>("tip_text_padding_size", 8.0_vp);
        theme->blockShadowColor_ = pattern->GetAttr<Color>("block_shadow_color", BLOCK_SHADOW_COLOR);
        theme->showFocusFrame_ = static_cast<bool>(pattern->GetAttr<double>("show_focus_frame", 0.0));
        theme->focusedScaleValue_ = pattern->GetAttr<double>("focused_scale_value", 1.0);
        theme->outsetModeSelectedTrackColor_ =
            pattern->GetAttr<Color>("outset_mode_selected_track_color", Color(0xff007dff));
        theme->noneModeSelectedTrackColor_ =
            pattern->GetAttr<Color>("none_mode_selected_track_color", Color(0xff007dff));
        theme->measureContentOutsetWidth_ =
            pattern->GetAttr<Dimension>("measure_content_outset_width", MEASURE_CONTENT_DEFAULT_WIDTH);
        theme->selectedTxt_ = pattern->GetAttr<std::string>("slider_accessibility_selected", "");
        theme->unselectedTxt_ = pattern->GetAttr<std::string>("slider_accessibility_unselected", "");
        theme->unselectedDesc_ = pattern->GetAttr<std::string>("slider_accessibility_unselectedDesc", "");
        theme->disabledDesc_ = pattern->GetAttr<std::string>("slider_accessibility_disabledDesc", "");
        theme->tipDelayTime_ = pattern->GetAttr<int32_t>("slider_tip_delay_time", SLIDER_TIP_DELAY_TIME);
        theme->bubbleTextMax_ = pattern->GetAttr<Dimension>("bubble_text_max", TEXT_MAX);
        theme->bubbleToSliderExtraDistance_ =
            pattern->GetAttr<Dimension>("bubble_to_slider_extra_distance", BUBBLE_TO_SLIDER_EXTRA_DISTANCE);
        theme->bubbleVerticalWidth_ =
            pattern->GetAttr<Dimension>("bubble_vertical_width", BUBBLE_VERTICAL_WIDTH);
        theme->bubbleVerticalHeight_ =
            pattern->GetAttr<Dimension>("bubble_vertical_height", BUBBLE_VERTICAL_HEIGHT);
        theme->bubbleHorizontalWidth_ =
            pattern->GetAttr<Dimension>("bubble_horizontal_width", BUBBLE_HORIZONTAL_WIDTH);
        theme->bubbleHorizontalHeight_ =
            pattern->GetAttr<Dimension>("bubble_horizontal_height", BUBBLE_HORIZONTAL_HEIGHT);
        theme->bubbleLevel1VerticalWidth_ = pattern->GetAttr<Dimension>(
            "bubble_level1_vertical_width", BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH);
        theme->bubbleLevel1VerticalHeight_ = pattern->GetAttr<Dimension>(
            "bubble_level1_vertical_height", BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT);
        theme->bubbleLevel1HorizontalWidth_ = pattern->GetAttr<Dimension>(
            "bubble_level1_horizontal_width", BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH);
        theme->bubbleLevel1HorizontalHeight_ = pattern->GetAttr<Dimension>(
            "bubble_level1_horizontal_height", BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT);
        theme->bubbleLevel2VerticalWidth_ = pattern->GetAttr<Dimension>(
            "bubble_level2_vertical_width", BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH);
        theme->bubbleLevel2VerticalHeight_ = pattern->GetAttr<Dimension>(
            "bubble_level2_vertical_height", BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT);
        theme->bubbleLevel2HorizontalWidth_ = pattern->GetAttr<Dimension>(
            "bubble_level2_horizontal_width", BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH);
        theme->bubbleLevel2HorizontalHeight_ = pattern->GetAttr<Dimension>(
            "bubble_level2_horizontal_height", BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT);
        theme->bubbleArrowHeight_ = pattern->GetAttr<Dimension>("bubble_arrow_height", ARROW_HEIGHT);
        theme->bubbleArrowWidth_ = pattern->GetAttr<Dimension>("bubble_arrow_width", ARROW_WIDTH);
        theme->bubbleArrowRadius_ = pattern->GetAttr<Dimension>("bubble_arrow_radius", ARROW_RADIUS);
        theme->circularHorizontalOffset_ =
            pattern->GetAttr<Dimension>("circular_horizontal_offset", CIRCULAR_HORIZON_OFFSET);
#ifdef SUPPORT_DIGITAL_CROWN
        theme->crownDisplayControlRatio_ =
            pattern->GetAttr<double>("crown_display_control_ratio", CROWN_DISPLAY_CONTROL_RATIO);
#endif
    } else {
        LOGW("find pattern of slider fail");
    }
}

} // namespace OHOS::Ace
