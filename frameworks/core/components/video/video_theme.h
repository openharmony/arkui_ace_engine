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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_THEME_H

#include "base/geometry/size.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * VideoTheme defines color and styles of VideoComponent. VideoTheme should be built
 * using VideoTheme::Builder.
 */
class VideoTheme : public virtual Theme {
    DECLARE_ACE_TYPE(VideoTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<VideoTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<VideoTheme> theme = AceType::Claim(new VideoTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<VideoTheme>& theme) const
        {
            if (!themeStyle) {
                LOGW("Video parse pattern failed, theme style is null");
                return;
            }
            auto videoPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_VIDEO, nullptr);
            if (!videoPattern) {
                LOGW("find pattern of video fail");
                return;
            }
            theme->btnSize_ = Size(videoPattern->GetAttr<double>("control_bar_play_width", 40.0f),
                videoPattern->GetAttr<double>("control_bar_play_height", 40.0f));
            theme->btnEdge_ = Edge(
                videoPattern->GetAttr<Dimension>("control_bar_play_padding_left", 10.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_play_padding_top", 5.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_play_padding_right", 10.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_play_padding_bottom", 5.0_vp).Value());
            theme->textEdge_ = Edge(
                videoPattern->GetAttr<Dimension>("control_bar_current_time_padding_left", 5.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_current_time_padding_top", 5.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_current_time_padding_right", 5.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_current_time_padding_bottom", 5.0_vp).Value());
            theme->sliderEdge_ = Edge(
                videoPattern->GetAttr<Dimension>("control_bar_progress_padding_left", 0.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_progress_padding_top", 0.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_progress_padding_right", 0.0_vp).Value(),
                videoPattern->GetAttr<Dimension>("control_bar_progress_padding_bottom", 0.0_vp).Value());
            theme->timeTextStyle_.SetFontSize(videoPattern->GetAttr<Dimension>("control_bar_text_font_size", 15.0_vp));
            theme->timeTextStyle_.SetTextColor(videoPattern->GetAttr<Color>("control_bar_text_color", Color::BLACK));
            theme->errorTextStyle_.SetFontSize(videoPattern->GetAttr<Dimension>("control_bar_text_font_size", 15.0_vp));
            theme->errorTextStyle_.SetTextColor(videoPattern->GetAttr<Color>("control_bar_error_text_color",
                Color::GRAY));
            theme->bkgColor_ = videoPattern->GetAttr<Color>("control_bar_background_color", Color(0x64c8c8c8));
        }
    };

    ~VideoTheme() override = default;

    const Size& GetBtnSize() const
    {
        return btnSize_;
    }

    const Edge& GetBtnEdge() const
    {
        return btnEdge_;
    }

    const Edge& GetTextEdge() const
    {
        return textEdge_;
    }

    const Edge& GetSliderEdge() const
    {
        return sliderEdge_;
    }

    const TextStyle& GetTimeTextStyle() const
    {
        return timeTextStyle_;
    }

    const TextStyle& GetErrorTextStyle() const
    {
        return errorTextStyle_;
    }

    const Color& GetBkgColor() const
    {
        return bkgColor_;
    }

protected:
    VideoTheme() = default;

private:
    Size btnSize_;
    Edge btnEdge_;
    Edge textEdge_;
    Edge sliderEdge_;
    TextStyle timeTextStyle_;
    TextStyle errorTextStyle_;
    Color bkgColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_THEME_H
