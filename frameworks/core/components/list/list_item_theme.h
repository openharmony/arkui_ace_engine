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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_ITEM_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_ITEM_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace {
namespace {
constexpr Dimension LISTITEM_MARGIN_PADDING = 12.0_vp;
constexpr Dimension LISTITEM_LISTITEMGROUP_INTERVAL = 4.0_vp;
constexpr Dimension LISTITEMGROUP_PADDING = 4.0_vp;
constexpr Dimension LISTITEM_PADDING = 8.0_vp;
constexpr double SELECTED_ALPHA = 0.1;
} // namespace

/**
 * ListItemTheme defines styles of list or grid item. ListItemTheme should be built
 * using ListItemTheme::Builder.
 */
class ListItemTheme : public virtual Theme {
DECLARE_ACE_TYPE(ListItemTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ListItemTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ListItemTheme> theme = AceType::MakeRefPtr<ListItemTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ListItemTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("list_item_pattern", nullptr);
            if (!pattern) {
                LOGE("Pattern of checkbox is null, please check!");
                return;
            }
            theme->defaultColor_ = pattern->GetAttr<Color>("item_normal_color", Color::WHITE);
            theme->itemDefaultColor_ = pattern->GetAttr<Color>("item_normal_color", Color::WHITE);
            theme->defaultLeftMargin_ = pattern->GetAttr<Dimension>("item_margin_left", LISTITEM_MARGIN_PADDING);
            theme->defaultRightMargin_ = pattern->GetAttr<Dimension>("item_margin_right", LISTITEM_MARGIN_PADDING);
            theme->defaultPadding_ = Edge(LISTITEMGROUP_PADDING);
            theme->borderRadiusValue_ = pattern->GetAttr<Dimension>("item_border_radius", 0.0_vp);
            theme->defaultBorderRadius_.SetRadius(theme->borderRadiusValue_);
            theme->itemBorderRadius_.SetRadius(theme->borderRadiusValue_ - LISTITEM_LISTITEMGROUP_INTERVAL);
            theme->itemLeftPadding_ = LISTITEM_PADDING;
            theme->itemRightPadding_ = LISTITEM_PADDING;
            theme->focusBorderColor_ = pattern->GetAttr<Color>("item_focus_color", Color::WHITE);
            theme->clickColor_ = pattern->GetAttr<Color>("item_press_color", Color::WHITE);
            theme->hoverColor_ = pattern->GetAttr<Color>("item_hover_color", Color::WHITE);
            theme->pressColor_ = pattern->GetAttr<Color>("item_press_color", Color::WHITE);
            theme->disabledAlpha_ = pattern->GetAttr<double>("item_disabled_alpha", 0.0);
            theme->selectedColor_ = pattern->GetAttr<Color>("item_select_color", Color::WHITE);
            theme->selectedColorWithAlpha_ =
                theme->selectedColor_.BlendOpacity(pattern->GetAttr<double>("item_selected_alpha", SELECTED_ALPHA));
            theme->hoverAnimationDuration_ = 250; //250: the duration of hover animation, unit is ms.
            theme->hoverToPressAnimationDuration_ = 100; //100: the duration of hover to press animation, unit is ms.
            theme->clickAlphaBegin_ = pattern->GetAttr<double>("click_alpha_begin", 0.0f);
            theme->clickAlphaEnd_ = pattern->GetAttr<double>("click_alpha_end", 0.05f);
            theme->clickScale_ = pattern->GetAttr<double>("click_scale", 0.95f);
            theme->focusScale_ = pattern->GetAttr<double>("focus_scale", 1.12f);
            theme->focusScaleLarge_ = pattern->GetAttr<double>("focus_scale_large", 0.94f);
            theme->focusScaleMiddle_ = pattern->GetAttr<double>("focus_scale_middle", 0.8f);
            theme->focusScaleLittle_ = pattern->GetAttr<double>("focus_scale_little", 0.6f);
            theme->focusOpacityLarge_ = pattern->GetAttr<double>("focus_opacity_large", 1.0f);
            theme->focusOpacityMiddle_ = pattern->GetAttr<double>("focus_opacity_middle", 0.66f);
            theme->focusOpacityLittle_ = pattern->GetAttr<double>("focus_opacity_little", 0.38f);
            theme->focusAnimationDuration_ = pattern->GetAttr<double>("focus_animation_duration", 100.0f);
            theme->clickAnimationDuration_ = pattern->GetAttr<double>("click_animation_duration", 200.0f);
            theme->itemSize_ = pattern->GetAttr<Dimension>("item_size", 76.0_vp);
            theme->paddingInPercent_ = pattern->GetAttr<double>("padding_in_percent", 0.0f);
            theme->groupImageSize_ = pattern->GetAttr<Dimension>("group_image_size", 24.0_vp);
        }
    };

    ~ListItemTheme() override = default;

    const Color& GetClickColor() const
    {
        return clickColor_;
    }
    double GetClickAlphaBegin() const
    {
        return clickAlphaBegin_;
    }
    double GetClickAlphaEnd() const
    {
        return clickAlphaEnd_;
    }
    double GetClickScale() const
    {
        return clickScale_;
    }
    double GetFocusScale() const
    {
        return focusScale_;
    }
    double GetFocusScaleLarge() const
    {
        return focusScaleLarge_;
    }
    double GetFocusScaleMiddle() const
    {
        return focusScaleMiddle_;
    }
    double GetFocusScaleLittle() const
    {
        return focusScaleLittle_;
    }
    double GetFocusOpacityLarge() const
    {
        return focusOpacityLarge_;
    }
    double GetFocusOpacityMiddle() const
    {
        return focusOpacityMiddle_;
    }
    double GetFocusOpacityLittle() const
    {
        return focusOpacityLittle_;
    }
    double GetFocusAnimationDuration() const
    {
        return focusAnimationDuration_;
    }
    double GetClickAnimationDuration() const
    {
        return clickAnimationDuration_;
    }
    Dimension GetItemSize() const
    {
        return itemSize_;
    }
    double GetItemPaddingInPercent() const
    {
        return paddingInPercent_;
    }
    Dimension GetGroupImageSize() const
    {
        return groupImageSize_;
    }
    double GetItemSwipeThreshold() const
    {
        return swipeThreshold_;
    }
    double GetItemSwipeSpeedThreshold() const
    {
        return swipeSpeedThreshold_;
    }
    double GetItemSwipeRatio() const
    {
        return swipeRatio_;
    }
    double GetItemSwipeSpringMass() const
    {
        return swipeSpringMass_;
    }
    double GetItemSwipeSpringStiffness() const
    {
        return swipeSpringStiffness_;
    }
    double GetItemSwipeSpringDamping() const
    {
        return swipeSpringDamping_;
    }
    const Dimension& GetDeleteDistance() const
    {
        return deleteDistance_;
    }
    const Color& GetItemGroupDefaultColor() const
    {
        return defaultColor_;
    }
    const Color& GetItemDefaultColor() const
    {
        return itemDefaultColor_;
    }
    const Dimension& GetItemDefaultHeight() const
    {
        return defaultHeight_;
    }
    const NG::BorderRadiusProperty& GetItemGroupDefaultBorderRadius() const
    {
        return defaultBorderRadius_;
    }
    const NG::BorderRadiusProperty& GetItemDefaultBorderRadius() const
    {
        return itemBorderRadius_;
    }
    const Dimension& GetItemGroupDefaultLeftMargin() const
    {
        return defaultLeftMargin_;
    }
    const Dimension& GetItemGroupDefaultRightMargin() const
    {
        return defaultRightMargin_;
    }
    const Edge& GetItemGroupDefaultPadding() const
    {
        return defaultPadding_;
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
    int32_t GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }
    int32_t GetHoverToPressAnimationDuration() const
    {
        return hoverToPressAnimationDuration_;
    }
    double GetItemDisabledAlpha() const
    {
        return disabledAlpha_;
    }
    const Color& GetItemSelectedColor() const
    {
        return selectedColorWithAlpha_;
    }

protected:
    ListItemTheme() = default;

private:
    Color clickColor_;
    double clickAlphaBegin_ = 1.0;
    double clickAlphaEnd_ = 1.0;
    double clickScale_ = 1.0;
    double focusScale_ = 1.0;
    double focusScaleLarge_ = 1.0;
    double focusScaleMiddle_ = 1.0;
    double focusScaleLittle_ = 1.0;
    double focusOpacityLarge_ = 1.0;
    double focusOpacityMiddle_ = 1.0;
    double focusOpacityLittle_ = 1.0;
    double focusAnimationDuration_ = 100.0;
    double clickAnimationDuration_ = 200.0;
    double paddingInPercent_ = 0.0;
    double swipeThreshold_ = 0.25;
    double swipeSpeedThreshold_ = 1200;
    double swipeRatio_ = 0.6;
    double swipeSpringMass_ = 1;
    double swipeSpringStiffness_ = 228;
    double swipeSpringDamping_ = 30;
    Dimension itemSize_;
    Dimension groupImageSize_;
    Dimension deleteDistance_ = 56.0_vp;
    Color defaultColor_;
    Color itemDefaultColor_;
    Dimension defaultHeight_ = 48.0_vp;
    NG::BorderRadiusProperty defaultBorderRadius_;
    NG::BorderRadiusProperty itemBorderRadius_;
    Dimension defaultLeftMargin_;
    Dimension defaultRightMargin_;
    Dimension itemLeftPadding_;
    Dimension itemRightPadding_;
    Edge defaultPadding_;
    Color focusBorderColor_;
    Dimension focusBorderWidth_ = 2.0_vp;
    Color hoverColor_;
    Color pressColor_;
    int32_t hoverAnimationDuration_ = 0;
    int32_t hoverToPressAnimationDuration_ = 0;
    double disabledAlpha_ = 0.4;
    Color selectedColor_;
    Color selectedColorWithAlpha_;
    Dimension borderRadiusValue_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_LIST_LIST_ITEM_THEME_H
