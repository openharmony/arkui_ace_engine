/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H

#include "base/i18n/localization.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr float DEFAULT_START_DEGREE = 0.0f;
inline constexpr float DEFAULT_END_DEGREE = 360.0f;
inline constexpr float EDGE = 15.0f;
inline constexpr float HEIGHT_OFFSET = 5.0f;
inline constexpr float INDICATOR_STROKE_WIDTH = 5.0f;
inline constexpr int8_t UNSELECT_ALPHA = 125;
inline constexpr float DEFAULT_MIN_VALUE = 0.0f;
inline constexpr float DEFAULT_MAX_VALUE = 100.0f;
inline constexpr float MONOCHROME_CIRCULAR_BACKGROUND_COLOR_OPACITY = 0.2f;
inline constexpr float INDICATOR_WIDTH_RATIO = 0.135f;
inline constexpr float INDICATOR_HEIGHT_RATIO = 0.087f;
inline constexpr float INDICATOR_CORNER_RADIUS_RATIO = 0.01f;
inline constexpr float INDICATOR_BORDER_WIDTH_RATIO_DOUBLE = 0.06f;
inline constexpr float INTERVAL_RATIO = 0.08f;
inline constexpr Dimension TRACK_THICKNESS = 4.0_vp;
inline constexpr float INDICATOR_BORDER_WIDTH_RATIO = 0.03f;
inline constexpr float DESCRIPTION_NODE_WIDTH_RATIO = 0.4444f;
inline constexpr float DESCRIPTION_NODE_HEIGHT_RATIO = 0.254f;
inline constexpr float DESCRIPTION_IMAGE_NODE_WIDTH_RATIO = 0.286f;
inline constexpr float DESCRIPTION_IMAGE_NODE_HEIGHT_RATIO = 0.286f;
inline constexpr float DESCRIPTION_X = 0.2778f;
inline constexpr float DESCRIPTION_Y = 0.746f;
inline constexpr float DESCRIPTION_IMAGE_X = 0.357f;
inline constexpr float DESCRIPTION_IMAGE_Y = 0.714f;
inline constexpr float LIMIT_VALUE_MIN_OR_MAX_HEIGHT_RATIO = 0.2222f;
inline constexpr float LIMIT_VALUE_Y = 0.722f;
inline constexpr float DEFAULT_GAUGE_SHADOW_RADIUS = 20.0f;
inline constexpr float DEFAULT_GAUGE_SHADOW_OFFSETX = 5.0f;
inline constexpr float DEFAULT_GAUGE_SHADOW_OFFSETY = 5.0f;
inline constexpr float SHADOW_ALPHA = 0.4f;
inline constexpr Dimension INDICATOR_DISTANCE_TO_TOP = 8.0_vp;
inline constexpr Dimension LIMIT_VALUE_MAX_FONTSIZE = 40.0_vp;
inline constexpr int32_t COLORS_MAX_COUNT = 9;
inline constexpr float RADIUS_TO_DIAMETER = 2.0f;
inline constexpr float INDICATOR_WIDTH_RADIO = 0.135f;
inline constexpr float INDICATOR_HEIGHT_RADIO = 0.095f;
inline constexpr float LIMIT_VALUE_MIN_SAFE_DISTANCE_RATIO = 0.031;
inline constexpr float LIMIT_VALUE_MAX_SAFE_DISTANCE_RATIO = 0.031;
inline constexpr float LIMIT_VALUE_SPACE_SAFE_DISTANCE_RATIO = 0.0635;
inline const std::vector<Color> GAUGE_DEFAULT_COLOR { Color(0xFF64BB5C), Color(0xFFF7CE00), Color(0xFFE84026) };
} // namespace

/**
 * GaugeTheme defines color and styles of GaugePattern. GaugeTheme should be built
 * using GaugeTheme::Builder.
 */
class GaugeTheme : public virtual Theme {
    DECLARE_ACE_TYPE(GaugeTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<GaugeTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<GaugeTheme> theme = AceType::MakeRefPtr<GaugeTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<GaugeTheme>& theme) const
        {
            RefPtr<ThemeStyle> gaugePattern = themeConstants->GetPatternByName(THEME_PATTERN_GAUGE);
            if (!gaugePattern) {
                return;
            }

            theme->indicatorColor_ = gaugePattern->GetAttr<Color>("indicator_color", Color::BLACK);
            theme->indicatorBorderColor_ = gaugePattern->GetAttr<Color>("indicator_border_color", Color::WHITE);
            theme->limitValueMinFontSize_ = gaugePattern->GetAttr<Dimension>("limit_value_min_font_size", 10.0_vp);
            theme->indicatorWidthRatio_ = gaugePattern->GetAttr<double>("indicator_width_ratio", INDICATOR_WIDTH_RATIO);
            theme->indicatorHeightRatio_ =
                gaugePattern->GetAttr<double>("indicator_height_ratio", INDICATOR_HEIGHT_RATIO);
            theme->indicatorRadiusRatio_ =
                gaugePattern->GetAttr<double>("indicator_corner_radius_ratio", INDICATOR_CORNER_RADIUS_RATIO);
            theme->indicatorBorderRatio_ =
                gaugePattern->GetAttr<double>("indicator_border_ratio", INDICATOR_BORDER_WIDTH_RATIO_DOUBLE);
            theme->intervalRatio_ = gaugePattern->GetAttr<double>("interval_ratio", INTERVAL_RATIO);
            theme->trackThickness_ = gaugePattern->GetAttr<Dimension>("track_thickness", TRACK_THICKNESS);
        }
    };

    ~GaugeTheme() override = default;

    const Color& GetIndicatorColor() const
    {
        return indicatorColor_;
    }

    const Color& GetIndicatorBorderColor() const
    {
        return indicatorBorderColor_;
    }

    const Dimension& GetLimitValueMinFontSize() const
    {
        return limitValueMinFontSize_;
    }

    const Dimension& GetTrackThickness() const
    {
        return trackThickness_;
    }

    const float& GetIndicatorRadiusRatio()
    {
        return indicatorRadiusRatio_;
    }

    const float& GetIndicatorBorderRatio() const
    {
        return indicatorBorderRatio_;
    }

    const float& GetIndicatorWidthRatio() const
    {
        return indicatorWidthRatio_;
    }

    const float& GetIndicatorHeightRatio() const
    {
        return indicatorHeightRatio_;
    }

    const float& GetIntervalRatio() const
    {
        return intervalRatio_;
    }

protected:
    GaugeTheme() = default;

private:
    Color indicatorColor_;
    Color indicatorBorderColor_;
    Dimension limitValueMinFontSize_;
    Dimension trackThickness_;
    float intervalRatio_ = 0.0f;
    float indicatorWidthRatio_ = 0.0f;
    float indicatorHeightRatio_ = 0.0f;
    float indicatorRadiusRatio_ = 0.0f;
    float indicatorBorderRatio_ = 0.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H