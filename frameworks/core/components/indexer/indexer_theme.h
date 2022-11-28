/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_INDEXER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_INDEXER_THEME_H

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_style.h"

namespace OHOS::Ace {
class IndexerTheme : public virtual Theme {
    DECLARE_ACE_TYPE(IndexerTheme, Theme);

public:
    ~IndexerTheme() = default;
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<IndexerTheme> Build(const RefPtr<ThemeConstants>& themeConstants)
        {
            RefPtr<IndexerTheme> theme = AceType::Claim(new IndexerTheme());
            if (!themeConstants) {
                LOGE("Build AppTheme error, themeConstants is null!");
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }
    };

    const Color& GetDefaultTextColor() const
    {
        return defaultTextColor_;
    }
    const Color& GetSelectedTextColor() const
    {
        return selectedTextColor_;
    }
    const Color& GetPopupTextColor() const
    {
        return popupTextColor_;
    }
    const Dimension& GetPopupTextSize() const
    {
        return popupTextSize_;
    }
    const Color& GetPopupBackgroundColor() const
    {
        return popupBackgroundColor_;
    }
    const Color& GetPopupSeparateColor() const
    {
        return popupSeparateColor_;
    }
    const Color& GetSeclectedBackgroundColor() const
    {
        return selectedBackgroundColor_;
    }
    const Dimension& GetPopupAreaSize_() const
    {
        return popupAreaSize_;
    }
    const Dimension& GetHoverRadiusSize_() const
    {
        return hoverRadiusSize_;
    }
    const Dimension& GetHoverBgAreaSize() const
    {
        return hoverBgAreaSize_;
    }
    const Color& GetHoverBgAreaColor() const
    {
        return hoverBgAreaColor_;
    }
    const Dimension& GetHoverTextSize() const
    {
        return hoverTextSize_;
    }
    const Color& GetHoverTextColor() const
    {
        return hoverTextColor_;
    }
    const Dimension& GetHoverTextAlpha() const
    {
        return hoverTextAlpha_;
    }
    const Color& GetSlipHoverBackgroundColor() const
    {
        return slipHoverBackgroundColor_;
    }
    const Color& GetFocusBgOutlineColor() const
    {
        return focusBgOutlineColor_;
    }
    const Dimension& GetFocusBgOutlineSize() const
    {
        return focusBgOutlineSize_;
    }
    const TextStyle& GetSelectTextStyle() const
    {
        return seletctTextStyle_;
    }
    const TextStyle& GetDefaultTextStyle() const
    {
        return defaultTextStyle_;
    }
    const TextStyle& GetPopupTextStyle() const
    {
        return popupTextStyle_;
    }

    static constexpr double SLIP_BACKGROUND_OPACITY = 0.05;
    static constexpr double TEXT_COLOR_OPACITY = 0.6;
    static constexpr double SELECT_BACKGROUND_OPACITY = 0.1;

protected:
    IndexerTheme() = default;

    Color defaultTextColor_;
    Color selectedTextColor_;
    Color popupTextColor_;
    Dimension popupTextSize_;
    Color selectedBackgroundColor_;
    Color popupBackgroundColor_;
    Color popupSeparateColor_;
    Dimension popupAreaSize_;
    Dimension hoverRadiusSize_;
    Dimension hoverBgAreaSize_;
    Color hoverBgAreaColor_;
    Dimension hoverTextSize_;
    Color hoverTextColor_;
    Dimension hoverTextAlpha_;
    Color slipHoverBackgroundColor_;
    Color focusBgOutlineColor_;
    Dimension focusBgOutlineSize_;
    TextStyle seletctTextStyle_;
    TextStyle defaultTextStyle_;
    TextStyle popupTextStyle_;

private:
    static void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<IndexerTheme>& theme)
    {
        if (!themeStyle) {
            return;
        }
        auto indexerPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_INDEXER, nullptr);
        if (!indexerPattern) {
            LOGE("Pattern of indexer is null, please check!");
            return;
        }
        theme->defaultTextColor_ =
            indexerPattern->GetAttr<Color>("default_text_color", Color::RED).ChangeOpacity(TEXT_COLOR_OPACITY);
        theme->selectedTextColor_ = indexerPattern->GetAttr<Color>("selected_text_color", Color::RED);
        theme->popupTextColor_ = indexerPattern->GetAttr<Color>("popup_text_color", Color::RED);
        theme->popupTextSize_ = indexerPattern->GetAttr<Dimension>("popup_text_size", 0.0_vp);
        theme->selectedBackgroundColor_ = indexerPattern->GetAttr<Color>("selected_background_color", Color::RED)
                                              .ChangeOpacity(SELECT_BACKGROUND_OPACITY);
        theme->popupBackgroundColor_ = indexerPattern->GetAttr<Color>("popup_background_color", Color::RED);
        theme->popupSeparateColor_ = indexerPattern->GetAttr<Color>("popup_separator_color", Color::RED);
        theme->popupAreaSize_ = indexerPattern->GetAttr<Dimension>("popup_area_size", 0.0_vp);
        theme->hoverRadiusSize_ = indexerPattern->GetAttr<Dimension>("hover_radius_size", 0.0_vp);
        theme->hoverBgAreaSize_ = indexerPattern->GetAttr<Dimension>("hover_bg_area_size", 0.0_vp);
        theme->hoverBgAreaColor_ = indexerPattern->GetAttr<Color>("hover_bg_area_color", Color::RED);
        theme->hoverTextSize_ = indexerPattern->GetAttr<Dimension>("hover_text_size", 0.0_vp);
        theme->hoverTextColor_ =
            indexerPattern->GetAttr<Color>("hover_text_color", Color::RED).ChangeOpacity(TEXT_COLOR_OPACITY);
        theme->hoverTextAlpha_ = indexerPattern->GetAttr<Dimension>("hover_text_alpha", 0.0_vp);
        theme->slipHoverBackgroundColor_ = indexerPattern->GetAttr<Color>("slip_hover_background_color", Color::RED)
                                               .ChangeOpacity(SLIP_BACKGROUND_OPACITY);
        theme->focusBgOutlineColor_ = indexerPattern->GetAttr<Color>("focus_bg_outline_color", Color::RED);
        theme->focusBgOutlineSize_ = indexerPattern->GetAttr<Dimension>("focus_bg_outline_size", 0.0_vp);
        theme->seletctTextStyle_.SetFontSize(indexerPattern->GetAttr<Dimension>("hover_text_size", 0.0_vp));
        theme->seletctTextStyle_.SetTextColor(indexerPattern->GetAttr<Color>("selected_text_color", Color::RED));
        theme->seletctTextStyle_.SetFontWeight(FontWeight::REGULAR);
        theme->defaultTextStyle_.SetFontSize(indexerPattern->GetAttr<Dimension>("hover_text_size", 0.0_vp));
        theme->defaultTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("default_text_color", Color::RED).ChangeOpacity(TEXT_COLOR_OPACITY));
        theme->defaultTextStyle_.SetFontWeight(FontWeight::REGULAR);
        theme->popupTextStyle_.SetFontSize(indexerPattern->GetAttr<Dimension>("popup_text_size", 0.0_vp));
        theme->popupTextStyle_.SetTextColor(indexerPattern->GetAttr<Color>("popup_text_color", Color::RED));
        theme->popupTextStyle_.SetFontWeight(FontWeight::MEDIUM);
    }
};
} // namespace OHOS::Ace
#endif