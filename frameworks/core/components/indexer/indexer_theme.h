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

#include <string>
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
    const Dimension& GetPopupAreaSize() const
    {
        return popupAreaSize_;
    }
    const Dimension& GetHoverRadiusSize() const
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
    const Color& GetPopupSelectedTextColor() const
    {
        return popupSelectedTextColor_;
    }
    const Color& GetPopupUnselectedTextColor() const
    {
        return popupUnselectedTextColor_;
    }
    static constexpr double SLIP_BACKGROUND_OPACITY = 0.05;
    static constexpr double SLIP_PRESS_BACKGROUND_OPACITY = 0.1;
    static constexpr float TEXT_PADDING_LEFT = 12.0f;
    static constexpr float TEXT_PADDING_TOP = 6.0f;

protected:
    IndexerTheme() = default;

    Color defaultTextColor_;
    Color selectedTextColor_;
    Color popupTextColor_;
    Dimension popupTextSize_;
    Color selectedBackgroundColor_;
    Color popupBackgroundColor_;
    Color popupSeparateColor_;
    Color popupSelectedTextColor_;
    Color popupUnselectedTextColor_;
    Dimension popupAreaSize_;
    Dimension hoverRadiusSize_;
    Dimension hoverBgAreaSize_;
    Color hoverBgAreaColor_;
    Dimension hoverTextSize_;
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
            indexerPattern->GetAttr<Color>("default_text_color", Color(DEFAULT_TEXT_COLOR));
        theme->selectedTextColor_ = indexerPattern->GetAttr<Color>("selected_text_color", Color(SELECT_TEXT_COLOR));
        theme->popupTextColor_ = indexerPattern->GetAttr<Color>("popup_text_color", Color(POPUP_TEXT_COLOR));
        theme->popupTextSize_ =
            indexerPattern->GetAttr<Dimension>("popup_text_size", Dimension(POPUP_TEXT_SIZE, DimensionUnit::FP));
        theme->selectedBackgroundColor_ =
            indexerPattern->GetAttr<Color>("selected_background_color", Color(SELECT_BACKGROUD_COLOR)).ChangeOpacity(
                indexerPattern->GetAttr<double>("selected_background_color_opacity", SELECT_BACKGROUND_OPACITY));
        theme->popupBackgroundColor_ =
            indexerPattern->GetAttr<Color>("popup_background_color", Color(POPUP_BACKGROUND_COLOR));
        theme->popupSeparateColor_ =
            indexerPattern->GetAttr<Color>("popup_separator_color", Color(POPUP_SEPARATOR_COLOR));
        theme->popupSelectedTextColor_ =
            indexerPattern->GetAttr<Color>("popup_selected_text_color", Color(POPUP_SELECTED_TEXT_COLOR));
        theme->popupUnselectedTextColor_ =
            indexerPattern->GetAttr<Color>("popup_unselected_text_color", Color(POPUP_UNSELECTED_TEXT_COLOR));
        theme->popupAreaSize_ =
            indexerPattern->GetAttr<Dimension>("popup_area_size", Dimension(POPUP_AREA_SIZE, DimensionUnit::VP));
        theme->hoverRadiusSize_ =
            indexerPattern->GetAttr<Dimension>("hover_radius_size", Dimension(HOVER_RADIUS_SIZE, DimensionUnit::VP));
        theme->hoverBgAreaSize_ =
            indexerPattern->GetAttr<Dimension>("hover_bg_area_size", Dimension(HOVER_BG_AREA_SIZE, DimensionUnit::VP));
        theme->hoverBgAreaColor_ = indexerPattern->GetAttr<Color>("hover_bg_area_color", Color(HOVER_BG_AREA_COLOR));
        theme->hoverTextSize_ =
            indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP));
        theme->hoverTextAlpha_ =
            indexerPattern->GetAttr<Dimension>("hover_text_alpha", Dimension(HOVER_TEXT_ALPHA, DimensionUnit::PX));
        theme->slipHoverBackgroundColor_ =
            indexerPattern->GetAttr<Color>("slip_hover_background_color", Color(SLIP_HOVER_BACKGROUD_COLOR));
        theme->focusBgOutlineColor_ =
            indexerPattern->GetAttr<Color>("focus_bg_outline_color", Color(FOCUS_BG_OUTLINE_COLOR));
        theme->focusBgOutlineSize_ = indexerPattern->GetAttr<Dimension>(
            "focus_bg_outline_size", Dimension(FOCUS_BG_OUTLINE_SIZE, DimensionUnit::VP));
        theme->seletctTextStyle_.SetFontSize(
            indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP)));
        theme->seletctTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("selected_text_color", Color(SELECT_TEXT_COLOR)));
        theme->seletctTextStyle_.SetFontWeight(FontWeight::REGULAR);
        theme->seletctTextStyle_.SetFontStyle(FontStyle::NORMAL);
        std::vector<std::string> fontFamilies;
        std::string defaultFamily = "HarmonyOS Sans";
        fontFamilies.emplace_back(defaultFamily);
        theme->seletctTextStyle_.SetFontFamilies(fontFamilies);
        theme->defaultTextStyle_.SetFontSize(
            indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP)));
        theme->defaultTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("default_text_color", Color(DEFAULT_TEXT_COLOR)));
        theme->defaultTextStyle_.SetFontWeight(FontWeight::REGULAR);
        theme->defaultTextStyle_.SetFontStyle(FontStyle::NORMAL);
        theme->defaultTextStyle_.SetFontFamilies(fontFamilies);
        theme->popupTextStyle_.SetFontSize(
            indexerPattern->GetAttr<Dimension>("popup_text_size", Dimension(POPUP_TEXT_SIZE, DimensionUnit::VP)));
        theme->popupTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("popup_text_color", Color(POPUP_TEXT_COLOR)));
        theme->popupTextStyle_.SetFontWeight(FontWeight::MEDIUM);
        theme->popupTextStyle_.SetFontStyle(FontStyle::NORMAL);
        theme->popupTextStyle_.SetFontFamilies(fontFamilies);
    }
    static constexpr uint32_t DEFAULT_TEXT_COLOR = 0x99182431;
    static constexpr uint32_t POPUP_SELECTED_TEXT_COLOR = 0xff182431;
    static constexpr uint32_t POPUP_UNSELECTED_TEXT_COLOR = 0xff182431;
    static constexpr uint32_t SELECT_TEXT_COLOR = 0xff007dff;
    static constexpr uint32_t POPUP_TEXT_COLOR = 0xff007dff;
    static constexpr float POPUP_TEXT_SIZE = 24.0;
    static constexpr uint32_t SELECT_BACKGROUD_COLOR = 0x33007dff;
    static constexpr uint32_t POPUP_BACKGROUND_COLOR = 0xffffffff;
    static constexpr uint32_t POPUP_SEPARATOR_COLOR = 0x33182431;
    static constexpr float POPUP_AREA_SIZE = 56.0f;
    static constexpr float HOVER_RADIUS_SIZE = 4.0f;
    static constexpr float HOVER_BG_AREA_SIZE = 16.0f;
    static constexpr uint32_t HOVER_BG_AREA_COLOR = 0x0c182431;
    static constexpr float HOVER_TEXT_SIZE = 12.0f;
    static constexpr uint32_t HOVER_TEXT_COLOR = 0xff182431;
    static constexpr float HOVER_TEXT_ALPHA = 0.6f;
    static constexpr uint32_t SLIP_HOVER_BACKGROUD_COLOR = 0x000000;
    static constexpr uint32_t FOCUS_BG_OUTLINE_COLOR = 0xff007dff;
    static constexpr float FOCUS_BG_OUTLINE_SIZE = 2.0f;
    static constexpr float TEXT_COLOR_OPACITY = 0.6f;
    static constexpr float SELECT_BACKGROUND_OPACITY = 0.1f;
};
} // namespace OHOS::Ace
#endif