/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace::NG {
enum class GridItemStyle {
    NONE = 0,
    PLAIN,
};

/**
 * GridItemTheme defines styles of grid item. GridItemTheme should be built using GridItemTheme::Builder.
 */
class GridItemTheme : public virtual Theme {
    DECLARE_ACE_TYPE(GridItemTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<GridItemTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<GridItemTheme> theme = AceType::Claim(new GridItemTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<GridItemTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_GRID);
            if (!pattern) {
                return;
            }
            theme->pressColor_ = pattern->GetAttr<Color>("grid_item_press_color", Color::WHITE);
            theme->hoverColor_ = pattern->GetAttr<Color>("grid_item_hover_color", Color::WHITE);
            theme->focusRadius_ = pattern->GetAttr<Dimension>("grid_item_focus_border_radius", 0.0_vp);
            theme->focusColor_ = pattern->GetAttr<Color>("grid_item_focus_color", Color::WHITE);
            theme->borderRadius_.SetRadius(theme->focusRadius_);
        }
    };

    ~GridItemTheme() override = default;

    const Color& GetGridItemPressColor() const
    {
        return pressColor_;
    }
    const Color& GetGridItemHoverColor() const
    {
        return hoverColor_;
    }
    int32_t GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }
    int32_t GetHoverToPressAnimationDuration() const
    {
        return hoverToPressAnimationDuration_;
    }
    double GetGridItemDisabledAlpha() const
    {
        return disabledAlpha_;
    }
    double GetGridItemEnabledAlpha() const
    {
        return enabledAlpha_;
    }
    const Dimension& GetGridItemFocusRadius() const
    {
        return focusRadius_;
    }
    const Dimension& GetFocusPaintPadding() const
    {
        return focusPaintPadding_;
    }
    const Color& GetGridItemFocusColor() const
    {
        return focusColor_;
    }
    const NG::BorderRadiusProperty& GetGridItemBorderRadius() const
    {
        return borderRadius_;
    }

protected:
    GridItemTheme() = default;

private:
    Color pressColor_;
    Color hoverColor_;
    int32_t hoverAnimationDuration_ = 250;
    int32_t hoverToPressAnimationDuration_ = 100;
    double disabledAlpha_ = 0.4;
    double enabledAlpha_ = 1.0;
    Dimension focusRadius_;
    Dimension focusPaintPadding_ = 3.0_vp;
    Color focusColor_;
    Dimension borderRadiusValue_;
    NG::BorderRadiusProperty borderRadius_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_THEME_H
