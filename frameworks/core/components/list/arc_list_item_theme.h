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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_ITEM_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_ITEM_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {

/**
 * ArcListItemTheme defines styles of arc list or grid item. ArcListItemTheme should be built
 * using ArcListItemTheme::Builder.
 */
class ArcListItemTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ArcListItemTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ArcListItemTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ArcListItemTheme> theme = AceType::MakeRefPtr<ArcListItemTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ArcListItemTheme>& theme) const
        {
            static const Dimension arcListItemGroupInterval = 4.0_vp;
            static const Dimension arcListItemPadding = 8.0_vp;
            static const int32_t arcListItemHoverDuration = 250;
            static const int32_t arcListItemHoverToPressDuration = 100;
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("arc_list_item_pattern", nullptr);
            if (!pattern) {
                LOGE("Pattern of arc list item is null, please check!");
                return;
            }
            theme->itemDefaultColor_ = pattern->GetAttr<Color>("item_normal_color", Color::WHITE);
            theme->borderRadiusValue_ = pattern->GetAttr<Dimension>("item_border_radius", 0.0_vp);
            theme->itemBorderRadius_.SetRadius(theme->borderRadiusValue_ - arcListItemGroupInterval);
            theme->itemLeftPadding_ = arcListItemPadding;
            theme->itemRightPadding_ = arcListItemPadding;
            theme->focusBorderColor_ = pattern->GetAttr<Color>("item_focus_color", Color::WHITE);
            theme->hoverColor_ = pattern->GetAttr<Color>("item_hover_color", Color::WHITE);
            theme->pressColor_ = pattern->GetAttr<Color>("item_press_color", Color::WHITE);
            theme->disabledAlpha_ = pattern->GetAttr<double>("item_disabled_alpha", 0.0);
            theme->hoverAnimationDuration_ = arcListItemHoverDuration;
            theme->hoverToPressAnimationDuration_ = arcListItemHoverToPressDuration;
        }
    };

    ~ArcListItemTheme() override = default;

    const Color& GetItemDefaultColor() const
    {
        return itemDefaultColor_;
    }
    const Dimension& GetItemDefaultHeight() const
    {
        return defaultHeight_;
    }
    const NG::BorderRadiusProperty& GetItemDefaultBorderRadius() const
    {
        return itemBorderRadius_;
    }
    const Dimension& GetItemDefaultLeftPadding() const
    {
        return itemLeftPadding_;
    }
    const Dimension& GetItemDefaultRightPadding() const
    {
        return itemRightPadding_;
    }
    const Color& GetItemFocusBorderColor() const
    {
        return focusBorderColor_;
    }
    const Dimension& GetItemFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }
    const Color& GetItemHoverColor() const
    {
        return hoverColor_;
    }
    const Color& GetItemPressColor() const
    {
        return pressColor_;
    }
    double GetItemDisabledAlpha() const
    {
        return disabledAlpha_;
    }
    int32_t GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }
    int32_t GetHoverToPressAnimationDuration() const
    {
        return hoverToPressAnimationDuration_;
    }
    const Dimension& GetDeleteDistance() const
    {
        return deleteDistance_;
    }

protected:
    ArcListItemTheme() = default;

private:
    Color itemDefaultColor_;
    Dimension defaultHeight_ = 48.0_vp;
    NG::BorderRadiusProperty itemBorderRadius_;
    Dimension itemLeftPadding_;
    Dimension itemRightPadding_;
    Color focusBorderColor_;
    Dimension focusBorderWidth_ = 2.0_vp;
    Color hoverColor_;
    Color pressColor_;
    double disabledAlpha_ = 0.4;
    Dimension borderRadiusValue_;
    int32_t hoverAnimationDuration_ = 0;
    int32_t hoverToPressAnimationDuration_ = 0;
    Dimension deleteDistance_ = 56.0_vp;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_ARC_LIST_ARC_LIST_ITEM_THEME_H
