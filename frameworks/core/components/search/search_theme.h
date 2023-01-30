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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * SearchTheme defines color and styles of SearchComponent. SearchTheme should be built
 * using SearchTheme::Builder.
 */
class SearchTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SearchTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SearchTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SearchTheme> theme = AceType::Claim(new SearchTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->height_ = themeConstants->GetDimension(THEME_SEARCH_DEFAULT_HEIGHT);
            theme->placeholderColor_ = themeConstants->GetColor(THEME_SEARCH_PLACEHOLDER_COLOR);
            theme->focusPlaceholderColor_ = themeConstants->GetColor(THEME_SEARCH_FOCUS_PLACEHOLDER_COLOR);
            theme->textColor_ = themeConstants->GetColor(THEME_SEARCH_TEXT_COLOR);
            theme->focusTextColor_ = themeConstants->GetColor(THEME_SEARCH_FOCUS_TEXT_COLOR);
            theme->fontSize_ = themeConstants->GetDimension(THEME_SEARCH_FONT_SIZE);
            theme->iconSize_ = themeConstants->GetDimension(THEME_SEARCH_ICON_SIZE);
            theme->closeIconSize_ = themeConstants->GetDimension(THEME_SEARCH_CLOSE_ICON_SIZE);
            theme->closeIconHotZoneSize_ = themeConstants->GetDimension(THEME_SEARCH_CLOSE_ICON_HOT_ZONE_HORIZONTAL);
            theme->textFieldWidthReserved_ = theme->closeIconHotZoneSize_;
            theme->leftPadding_ = themeConstants->GetDimension(THEME_SEARCH_TEXT_FIELD_PADDING_LEFT);
            theme->rightPadding_ = themeConstants->GetDimension(THEME_SEARCH_TEXT_FIELD_PADDING_RIGHT);
            theme->fontWeight_ = FontWeight(themeConstants->GetInt(THEME_SEARCH_FONT_WEIGHT));
            theme->borderRadius_ = Radius(themeConstants->GetDimension(THEME_SEARCH_TEXT_FIELD_BORDER_RADIUS));
            theme->blockRightShade_ = themeConstants->GetInt(THEME_SEARCH_BLOCK_RIGHT_SHADE);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<SearchTheme>& theme) const
        {
            if (!themeStyle || !theme) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SEARCH, nullptr);
            if (!pattern) {
                LOGW("find pattern of search fail");
                return;
            }
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color());
            theme->focusPlaceholderColor_ = pattern->GetAttr<Color>("tips_text_color_focused", Color());
            theme->textColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->focusTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_FOCUSED, Color());
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_fp);
            theme->touchColor_ = pattern->GetAttr<Color>("search_touch_color", Color());
            theme->hoverColor_ = pattern->GetAttr<Color>("search_hover_color", Color());
            theme->searchDividerColor_ = pattern->GetAttr<Color>("search_divider_color", Color());
            theme->searchButtonTextColor_ = pattern->GetAttr<Color>("search_button_text_color", Color());
            theme->searchIconColor_ = pattern->GetAttr<Color>("search_icon_color", Color());
            theme->searchButtonTextPadding_ = pattern->GetAttr<Dimension>("search_button_text_padding", Dimension());
            theme->searchButtonSpace_ = pattern->GetAttr<Dimension>("search_button_space", Dimension());
            theme->dividerSideSpace_ = pattern->GetAttr<Dimension>("search_divider_side_space", Dimension());
            theme->iconHeight_ = pattern->GetAttr<Dimension>("search_icon_height", Dimension());
            theme->searchIconLeftSpace_ = pattern->GetAttr<Dimension>("search_icon_left_space", Dimension());
            theme->searchIconRightSpace_ = pattern->GetAttr<Dimension>("search_icon_right_space", Dimension());
        }
    };

    ~SearchTheme() override = default;

    const Color& GetPlaceholderColor() const
    {
        return placeholderColor_;
    }

    const Color& GetFocusPlaceholderColor() const
    {
        return focusPlaceholderColor_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetFocusTextColor() const
    {
        return focusTextColor_;
    }

    const Color& GetTouchColor() const
    {
        return touchColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

    const Dimension& GetCloseIconSize() const
    {
        return closeIconSize_;
    }

    const Dimension& GetCloseIconHotZoneSize() const
    {
        return closeIconHotZoneSize_;
    }

    const Dimension& GetTextFieldWidthReserved() const
    {
        return textFieldWidthReserved_;
    }

    const Dimension& GetLeftPadding() const
    {
        return leftPadding_;
    }

    const Dimension& GetRightPadding() const
    {
        return rightPadding_;
    }

    const FontWeight& GetFontWeight() const
    {
        return fontWeight_;
    }

    const Radius& GetBorderRadius() const
    {
        return borderRadius_;
    }

    bool GetBlockRightShade() const
    {
        return blockRightShade_;
    }

    const Dimension& GetDividerSideSpace() const
    {
        return dividerSideSpace_;
    }

    const Dimension& GetSearchDividerWidth() const
    {
        return searchDividerWidth_;
    }

    const Dimension& GetSearchButtonTextPadding() const
    {
        return searchButtonTextPadding_;
    }

    const Dimension& GetSearchButtonSpace() const
    {
        return searchButtonSpace_;
    }

    const Dimension& GetIconHeight() const
    {
        return iconHeight_;
    }

    const Dimension& GetSearchIconLeftSpace() const
    {
        return searchIconLeftSpace_;
    }

    const Dimension& GetSearchIconRightSpace() const
    {
        return searchIconRightSpace_;
    }

    const Color& GetSearchDividerColor() const
    {
        return searchDividerColor_;
    }

    const Color& GetSearchButtonTextColor() const
    {
        return searchButtonTextColor_;
    }

    const Color& GetSearchIconColor() const
    {
        return searchIconColor_;
    }

protected:
    SearchTheme() = default;

private:
    Color placeholderColor_;
    Color focusPlaceholderColor_;
    Color textColor_;
    Color focusTextColor_;
    Color touchColor_;
    Color hoverColor_;
    Dimension height_;
    Dimension fontSize_;
    Dimension iconSize_;
    Dimension closeIconSize_;
    Dimension closeIconHotZoneSize_;
    Dimension textFieldWidthReserved_;
    Dimension leftPadding_;
    Dimension rightPadding_;
    FontWeight fontWeight_ = FontWeight::NORMAL;
    Radius borderRadius_;
    bool blockRightShade_ = false;
    Dimension dividerSideSpace_;
    Dimension searchDividerWidth_ = 1.0_px;
    Dimension searchButtonTextPadding_;
    Dimension searchButtonSpace_;
    Dimension iconHeight_;
    Dimension searchIconLeftSpace_;
    Dimension searchIconRightSpace_;
    Color searchDividerColor_;
    Color searchButtonTextColor_;
    Color searchIconColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SEARCH_SEARCH_THEME_H
