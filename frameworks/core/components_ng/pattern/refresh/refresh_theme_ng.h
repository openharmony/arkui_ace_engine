/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_REFRESH_REFRESH_THEME_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_REFRESH_REFRESH_THEME_NG_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int TEXT_FIELD_FONT_WEIGHT = 3;
} // namespace

/**
 * RefreshThemeNG should be built using RefreshThemeNG::Builder.
 */
class RefreshThemeNG : public virtual Theme {
    DECLARE_ACE_TYPE(RefreshThemeNG, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<RefreshThemeNG> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<RefreshThemeNG> theme = AceType::MakeRefPtr<RefreshThemeNG>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RefreshThemeNG>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_REFRESH);
            if (!pattern) {
                LOGW("find pattern of refresh fail");
                return;
            }
            theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_vp));
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK));
            theme->progressColor_ = pattern->GetAttr<Color>("progress_color", Color::BLACK);
            theme->loadingDistance_ = pattern->GetAttr<Dimension>("default_loading_distance", 16.0_vp);
            theme->progressDiameter_ = pattern->GetAttr<Dimension>("default_progress_diameter", 32.0_vp);
            theme->textStyle_.SetFontWeight(
                FontWeight(pattern->GetAttr<int>("textfield_font_weight", TEXT_FIELD_FONT_WEIGHT)));
            theme->ratio_ = pattern->GetAttr<double>("refresh_over_edge_following_ratio", 1.848f);
            theme->ratioGreatApi_ = pattern->GetAttr<double>("refresh_over_edge_following_ratio_api_twenty", 5.0f);
        }
    };

    ~RefreshThemeNG() override = default;

    const Dimension& GetLoadingDistance() const
    {
        return loadingDistance_;
    }

    const Dimension& GetProgressDiameter() const
    {
        return progressDiameter_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Color& GetProgressColor() const
    {
        return progressColor_;
    }

    float GetRatio() const
    {
        return ratio_;
    }

    float GetGreatApiRatio() const
    {
        return ratioGreatApi_;
    }

protected:
    RefreshThemeNG() = default;

private:
    Dimension loadingDistance_;
    Dimension progressDiameter_;
    TextStyle textStyle_;
    Color progressColor_;
    float ratio_ = 1.848f;
    float ratioGreatApi_ = 5.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_REFRESH_REFRESH_THEME_NG_H