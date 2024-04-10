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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATA_PANEL_DATA_PANEL_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATA_PANEL_DATA_PANEL_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {

class DataPanelTheme : public virtual Theme {
    DECLARE_ACE_TYPE(DataPanelTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<DataPanelTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<DataPanelTheme> theme = AceType::Claim(new DataPanelTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DataPanelTheme>& theme) const
        {
            RefPtr<ThemeStyle> dataPanelPattern = themeConstants->GetPatternByName(THEME_PATTERN_DATA_PANEL);
            if (!dataPanelPattern) {
                LOGW("find pattern of datapanel fail");
                return;
            }
            theme->thickness_ = dataPanelPattern->GetAttr<Dimension>("datapanel_thickness", 0.0_vp);
            theme->defaultHeight_ = dataPanelPattern->GetAttr<Dimension>("datapanel_height", 0.0_vp);
            theme->defaultWidth_ = dataPanelPattern->GetAttr<Dimension>("datapanel_width", 0.0_vp);
            theme->defaultBorderRadius_ = dataPanelPattern->GetAttr<Dimension>("datapanel_corner_radius", 8.0_vp);
            theme->trackShadowOffsetX_ = dataPanelPattern->GetAttr<Dimension>("datapanel_trackshadow_offsetx", 0.0_vp);
            theme->trackShadowOffsetY_ = dataPanelPattern->GetAttr<Dimension>("datapanel_trackshadow_offsety", 0.0_vp);
            theme->backgroundColor_ = dataPanelPattern->GetAttr<Color>(PATTERN_BG_COLOR, Color::BLACK);
            theme->trackShadowRadius_ = dataPanelPattern->GetAttr<Dimension>(DATA_PANEL_TRACK_SHADOW_RADIU, 0.0_vp);
            theme->loadingColors_.first = dataPanelPattern->GetAttr<Color>(DATA_PANEL_LOADING_COLOR_END, Color::BLACK);
            theme->loadingColors_.second =
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_LOADING_COLOR_START, Color::BLACK);
            theme->progressColors_.first =
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_PROGRESS_COLOR_END, Color::BLACK);
            theme->progressColors_.second =
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_PROGRESS_COLOR_START, Color::BLACK);
            theme->percentageColors_.clear();
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_1_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_1_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_2_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_2_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_3_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_3_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_4_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_4_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_5_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_5_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_6_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_6_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_7_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_7_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_8_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_8_END, Color::BLACK));
            theme->percentageColors_.emplace_back(
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_9_START, Color::BLACK),
                dataPanelPattern->GetAttr<Color>(DATA_PANEL_COLOR_9_END, Color::BLACK));
        }
    };

    const std::pair<Color, Color>& GetLoadingColor() const
    {
        return loadingColors_;
    }

    const std::pair<Color, Color>& GetProgressColor() const
    {
        return progressColors_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }

    const Dimension& GetDefaultWidth() const
    {
        return defaultWidth_;
    }

    const Dimension& GetDefaultBorderRadius() const
    {
        return defaultBorderRadius_;
    }

    const Dimension& GetThickness() const
    {
        return thickness_;
    }

    const std::vector<std::pair<Color, Color>> GetColorsArray() const
    {
        return percentageColors_;
    }

    const Dimension& GetTrackShadowRadius() const
    {
        return trackShadowRadius_;
    }

    const Dimension& GetTrackShadowOffsetX() const
    {
        return trackShadowOffsetX_;
    }

    const Dimension& GetTrackShadowOffsetY() const
    {
        return trackShadowOffsetY_;
    }

protected:
private:
    std::vector<std::pair<Color, Color>> percentageColors_;
    std::pair<Color, Color> loadingColors_;
    std::pair<Color, Color> progressColors_;
    Color backgroundColor_;
    Dimension defaultHeight_;
    Dimension defaultWidth_;
    Dimension defaultBorderRadius_;
    Dimension thickness_;
    Dimension trackShadowRadius_;
    Dimension trackShadowOffsetX_;
    Dimension trackShadowOffsetY_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATA_PANEL_DATA_PANEL_THEME_H
