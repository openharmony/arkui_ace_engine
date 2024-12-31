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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * SliderTheme defines color and styles of SliderComponent. SliderTheme should be built
 * using SliderTheme::Builder.
 */
class SliderTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SliderTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        static constexpr Color BLOCK_COLOR_PRESSED = Color(0x19182431);
        static constexpr Color BLOCK_OUTER_EDGE_COLOR = Color(0x0A000000);
        static constexpr Color BLOCK_SHADOW_COLOR = Color(0x26000000);
        static constexpr Dimension BUBBLE_TO_CIRCLE_CENTER_DISTANCE = 20.0_vp;
        static constexpr Dimension MEASURE_CONTENT_DEFAULT_WIDTH = 40.0_vp;
        static constexpr Dimension OUTSET_HOT_BLOCK_SHADOW_WIDTH = 4.0_vp;
        static constexpr Dimension INSET_HOT_BLOCK_SHADOW_WIDTH = 6.0_vp;
        static constexpr Dimension FOCUS_SIDE_DISTANCE = 2.0_vp;
        static constexpr double DEFAULT_SLIDER_PPI = 775.0;
        static constexpr int32_t SLIDER_TIP_DELAY_TIME = 2000;
#ifdef SUPPORT_DIGITAL_CROWN
        static constexpr double CROWN_DISPLAY_CONTROL_RATIO = 2.1;
#endif

        RefPtr<SliderTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SliderTheme> theme = AceType::Claim(new SliderTheme());
            if (!themeConstants) {
                return theme;
            }
            // init theme from global data
            ParsePattern(themeConstants, theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SliderTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SLIDER);
            if (pattern) {
                const double defaultMarkColorAplpa = 0.1;
                theme->trackBgColor_ = pattern->GetAttr<Color>("track_bg_color", Color::RED);
                theme->trackSelectedColor_ = pattern->GetAttr<Color>("track_color_selected", Color::RED);
                theme->markerColor_ =
                    pattern->GetAttr<Color>("marker_color", Color::RED)
                        .BlendOpacity(pattern->GetAttr<double>("marker_color_alpha", defaultMarkColorAplpa));
                theme->tipTextColor_ = pattern->GetAttr<Color>("tip_text_color", Color::RED);
                theme->tipColor_ = pattern->GetAttr<Color>("tip_color", Color::RED);
                theme->blockHoverColor_ = pattern->GetAttr<Color>("block_color_hovered", Color::RED);
                theme->blockPressedColor_ = pattern->GetAttr<Color>("block_color_pressed", BLOCK_COLOR_PRESSED);
                theme->blockOuterEdgeColor_ = pattern->GetAttr<Color>("block_outer_edge_color", BLOCK_OUTER_EDGE_COLOR);
                theme->bubbleToCircleCenterDistance_ =
                    pattern->GetAttr<Dimension>("bubble_to_circle_center_distance", BUBBLE_TO_CIRCLE_CENTER_DISTANCE);
                theme->measureContentDefaultWidth_ =
                    pattern->GetAttr<Dimension>("measure_content_default_width", MEASURE_CONTENT_DEFAULT_WIDTH);
                theme->outsetHotBlockShadowWidth_ =
                    pattern->GetAttr<Dimension>("outset_hot_block_shadow_width", OUTSET_HOT_BLOCK_SHADOW_WIDTH);
                theme->insetHotBlockShadowWidth_ =
                    pattern->GetAttr<Dimension>("inset_hot_block_shadow_width", INSET_HOT_BLOCK_SHADOW_WIDTH);
                theme->focusSideDistance_ = pattern->GetAttr<Dimension>("focus_side_distance", FOCUS_SIDE_DISTANCE);
                theme->layoutMaxLength_ = pattern->GetAttr<Dimension>("slider_max_length", .0_vp);
                theme->hoverAnimationDuration_ = pattern->GetAttr<double>("hover_animation_duration", 0.0);
                theme->pressAnimationDuration_ = pattern->GetAttr<double>("press_animation_duration", 0.0);
                theme->moveAnimationDuration_ = pattern->GetAttr<double>("move_animation_duration", 0.0);
                theme->disabledAlpha_ = pattern->GetAttr<double>("slider_disable_alpha", 0.0);
                theme->sliderPPI_ = pattern->GetAttr<double>("slider_pixels_per_inch", DEFAULT_SLIDER_PPI);
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
#ifdef SUPPORT_DIGITAL_CROWN
                theme->crownDisplayControlRatio_ =
                    pattern->GetAttr<double>("crown_display_control_ratio", CROWN_DISPLAY_CONTROL_RATIO);
#endif
            } else {
                LOGW("find pattern of slider fail");
            }
        }
    };

    ~SliderTheme() override = default;

    Dimension GetOutsetBlockSize() const
    {
        return outsetBlockSize_;
    }

    Dimension GetOutsetBlockHotSize() const
    {
        return outsetBlockHotSize_;
    }

    Dimension GetInsetBlockSize() const
    {
        return insetBlockSize_;
    }

    Dimension GetInsetBlockHotSize() const
    {
        return insetBlockHotSize_;
    }

    Color GetBlockHoverColor() const
    {
        return blockHoverColor_;
    }

    Color GetBlockColor() const
    {
        return blockColor_;
    }

    Dimension GetInsetTrackThickness() const
    {
        return insetTrackThickness_;
    }

    Dimension GetOutsetTrackThickness() const
    {
        return outsetTrackThickness_;
    }

    Dimension GetNoneBlockHotSize() const
    {
        return noneBlockHotSize_;
    }
    Dimension GetNoneTrackThickness() const
    {
        return noneTrackThickness_;
    }

    Dimension GetMarkerSize() const
    {
        return markerSize_;
    }

    Dimension GetTipFontSize() const
    {
        return tipFontSize_;
    }

    Dimension GetTipTextPadding() const
    {
        return tipTextPadding_;
    }

    Dimension GetBubbleToCircleCenterDistance() const
    {
        return bubbleToCircleCenterDistance_;
    }

    Dimension GetMeasureContentDefaultWidth() const
    {
        return measureContentDefaultWidth_;
    }

    Dimension GetOutsetHotBlockShadowWidth() const
    {
        return outsetHotBlockShadowWidth_;
    }

    Dimension GetInsetHotBlockShadowWidth() const
    {
        return insetHotBlockShadowWidth_;
    }

    Color GetBlockPressedColor() const
    {
        return blockPressedColor_;
    }

    Color GetBlockOuterEdgeColor() const
    {
        return blockOuterEdgeColor_;
    }

    Color GetTipColor() const
    {
        return tipColor_;
    }

    Color GetTipTextColor() const
    {
        return tipTextColor_;
    }

    Color GetMarkerColor() const
    {
        return markerColor_;
    }

    Color GetTrackBgColor() const
    {
        return trackBgColor_;
    }

    Color GetTrackSelectedColor() const
    {
        return trackSelectedColor_;
    }

    Color GetBlockShadowColor() const
    {
        return blockShadowColor_;
    }

    Dimension GetFocusSideDistance() const
    {
        return focusSideDistance_;
    }

    Dimension GetLayoutMaxLength() const
    {
        return layoutMaxLength_;
    }

    double GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }

    double GetPressAnimationDuration() const
    {
        return pressAnimationDuration_;
    }

    double GetMoveAnimationDuration() const
    {
        return moveAnimationDuration_;
    }

    double GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

    double GetSliderPPI() const
    {
        return sliderPPI_;
    }

    std::string GetSelectedTxt() const
    {
        return selectedTxt_;
    }
    std::string GetUnselectedTxt() const
    {
        return unselectedTxt_;
    }
    std::string GetUnselectedDesc() const
    {
        return unselectedDesc_;
    }
    std::string GetDisabelDesc() const
    {
        return disabledDesc_;
    }
    int32_t GetTipDelayTime() const
    {
        return tipDelayTime_;
    }

#ifdef SUPPORT_DIGITAL_CROWN
    double GetCrownDisplayControlRatio() const
    {
        return crownDisplayControlRatio_;
    }
#endif

    bool ShowFocusFrame() const
    {
        return showFocusFrame_;
    }

    double GetFocusedScaleValue() const
    {
        return focusedScaleValue_;
    }

    Dimension GetMeasureContentOutsetWidth() const
    {
        return measureContentOutsetWidth_;
    }

    const Color& GetOutsetModeSelectedTrackColor() const
    {
        return outsetModeSelectedTrackColor_;
    }

    const Color& GetNoneModeSelectedTrackColor() const
    {
        return noneModeSelectedTrackColor_;
    }

protected:
    SliderTheme() = default;

private:
    // outset slider mode
    Dimension outsetBlockSize_;
    Dimension outsetBlockHotSize_;
    Dimension outsetTrackThickness_;
    Dimension outsetHotBlockShadowWidth_;

    // inset slide mode
    Dimension insetBlockSize_;
    Dimension insetBlockHotSize_;
    Dimension insetTrackThickness_;
    Dimension insetHotBlockShadowWidth_;

    // none slider mode
    Dimension noneBlockHotSize_;
    Dimension noneTrackThickness_;

    // common
    Dimension markerSize_;
    Dimension tipFontSize_;
    Dimension tipTextPadding_;
    Dimension bubbleToCircleCenterDistance_;
    Dimension measureContentDefaultWidth_;
    Color blockColor_;
    Color blockHoverColor_;
    Color blockPressedColor_;
    Color blockOuterEdgeColor_;
    Color tipColor_;
    Color tipTextColor_;
    Color markerColor_;
    Color trackBgColor_;
    Color trackSelectedColor_;
    Color blockShadowColor_;

    // others
    Dimension focusSideDistance_;
    Dimension layoutMaxLength_;
    double hoverAnimationDuration_ = 0.0;
    double pressAnimationDuration_ = 0.0;
    double moveAnimationDuration_ = 0.0;
    double disabledAlpha_ = 1.0;
    double sliderPPI_ = 0.0;
    int32_t tipDelayTime_ = 0;

    // accessibility
    std::string selectedTxt_ = "";
    std::string unselectedTxt_ = "";
    std::string unselectedDesc_ = "";
    std::string disabledDesc_ = "";
#ifdef SUPPORT_DIGITAL_CROWN
    double crownDisplayControlRatio_ = 1.0;
#endif
    bool showFocusFrame_ = 0.0;
    double focusedScaleValue_ = 1.0;
    Dimension measureContentOutsetWidth_;
    Color outsetModeSelectedTrackColor_;
    Color noneModeSelectedTrackColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_THEME_H
