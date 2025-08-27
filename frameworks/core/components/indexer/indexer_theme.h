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
#include "core/common/container.h"
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
            RefPtr<IndexerTheme> theme = AceType::MakeRefPtr<IndexerTheme>();
            if (!themeConstants) {
                LOGE("Build AppTheme error, themeConstants is null!");
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }
    };

    const Color& GetIndexerBackgroundColor() const
    {
        return indexerBackgroundColor_;
    }
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
    const Color& GetSelectedBackgroundColor() const
    {
        return selectedBackgroundColor_;
    }
    const Color& GetSelectedBackgroundColorArc() const
    {
        return selectedBackgroundColorArc_;
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
    const Color& GetPressedBgAreaColor() const
    {
        return pressedBgAreaColor_;
    }
    const Color& GetSlipPressedBackgroundColor() const
    {
        return slipPressedBackgroundColor_;
    }
    const Color& GetPopupClickedBgAreaColor() const
    {
        return popupClickedBgAreaColor_;
    }
    const Color& GetPopupTitleBackground() const
    {
        return popupTitleBackground_;
    }
    const std::string& GetAccessibilityExpand() const
    {
        return accessibilityExpand_;
    }
    const std::string& GetAccessibilityExpanded() const
    {
        return accessibilityExpanded_;
    }
    const std::string& GetAccessibilityCollapse() const
    {
        return accessibilityCollapse_;
    }
    const std::string& GetAccessibilityCollapsed() const
    {
        return accessibilityCollapsed_;
    }
    const Color& GetPopupUnclickedBgAreaColor() const
    {
        return popupUnclickedBgAreaColor_;
    }
    static constexpr double SLIP_BACKGROUND_OPACITY = 0.05;
    static constexpr double SLIP_PRESS_BACKGROUND_OPACITY = 0.1;
    static constexpr float TEXT_PADDING_LEFT = 12.0f;
    static constexpr float TEXT_PADDING_TOP = 6.0f;

protected:
    IndexerTheme() = default;

    Color indexerBackgroundColor_;
    Color defaultTextColor_;
    Color selectedTextColor_;
    Color popupTextColor_;
    Dimension popupTextSize_;
    Color selectedBackgroundColor_;
    Color selectedBackgroundColorArc_;
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
    Color pressedBgAreaColor_;
    Color slipPressedBackgroundColor_;
    Color popupClickedBgAreaColor_;
    Color popupTitleBackground_;
    Color popupUnclickedBgAreaColor_;
    std::string accessibilityExpand_;
    std::string accessibilityExpanded_;
    std::string accessibilityCollapse_;
    std::string accessibilityCollapsed_;

private:
    static void ParseColorAttributes(const RefPtr<ThemeStyle>& indexerPattern, const RefPtr<IndexerTheme>& theme)
    {
        theme->indexerBackgroundColor_ = indexerPattern->GetAttr<Color>("indexer_bar_color", Color(0xff262626));
        theme->defaultTextColor_ = indexerPattern->GetAttr<Color>("default_text_color", Color(DEFAULT_TEXT_COLOR));
        theme->selectedTextColor_ = indexerPattern->GetAttr<Color>("selected_text_color", Color(SELECT_TEXT_COLOR));
        theme->popupTextColor_ = indexerPattern->GetAttr<Color>("popup_text_color", Color(POPUP_TEXT_COLOR));
        theme->selectedBackgroundColorArc_ =
            indexerPattern->GetAttr<Color>("selected_background_color_arc", Color(SELECT_BACKGROUD_COLOR_ARC));
        theme->selectedBackgroundColor_ =
            indexerPattern->GetAttr<Color>("selected_background_color", Color(SELECT_BACKGROUD_COLOR)).ChangeOpacity(
                indexerPattern->GetAttr<double>("selected_background_color_opacity", SELECT_BACKGROUND_OPACITY));
        theme->popupSeparateColor_ =
            indexerPattern->GetAttr<Color>("popup_separator_color", Color(POPUP_SEPARATOR_COLOR));
        theme->popupSelectedTextColor_ =
            indexerPattern->GetAttr<Color>("popup_selected_text_color", Color(POPUP_SELECTED_TEXT_COLOR));
        theme->popupUnselectedTextColor_ =
            indexerPattern->GetAttr<Color>("popup_unselected_text_color", Color(POPUP_UNSELECTED_TEXT_COLOR));
        theme->hoverBgAreaColor_ = indexerPattern->GetAttr<Color>("hover_bg_area_color", Color(HOVER_BG_AREA_COLOR));
        theme->slipHoverBackgroundColor_ =
            indexerPattern->GetAttr<Color>("slip_hover_background_color", Color(SLIP_HOVER_BACKGROUD_COLOR));
        theme->focusBgOutlineColor_ =
            indexerPattern->GetAttr<Color>("focus_bg_outline_color", Color(FOCUS_BG_OUTLINE_COLOR));
        theme->pressedBgAreaColor_ =
            indexerPattern->GetAttr<Color>("pressed_bg_area_color", Color(PRESSED_BG_AREA_COLOR));
        theme->slipPressedBackgroundColor_ =
            indexerPattern->GetAttr<Color>("slip_pressed_background_color", Color(SLIP_PRESSED_BACKGROUD_COLOR));
        theme->popupClickedBgAreaColor_ =
            indexerPattern->GetAttr<Color>("popup_clicked_bg_area_color", Color(POPUP_CLICKED_BG_AREA_COLOR));
        theme->popupTitleBackground_ =
            indexerPattern->GetAttr<Color>("popup_title_color", Color(POPUP_TITLE_BG_AREA_COLOR));
    }

    static void ParseDimensionAttributes(const RefPtr<ThemeStyle>& indexerPattern,
        const RefPtr<IndexerTheme>& theme)
    {
        theme->popupTextSize_ =
            indexerPattern->GetAttr<Dimension>("popup_text_size", Dimension(POPUP_TEXT_SIZE, DimensionUnit::FP));
        theme->popupAreaSize_ =
            indexerPattern->GetAttr<Dimension>("popup_area_size", Dimension(POPUP_AREA_SIZE, DimensionUnit::VP));
        theme->hoverRadiusSize_ =
            indexerPattern->GetAttr<Dimension>("hover_radius_size", Dimension(HOVER_RADIUS_SIZE, DimensionUnit::VP));
        theme->hoverBgAreaSize_ =
            indexerPattern->GetAttr<Dimension>("hover_bg_area_size", Dimension(HOVER_BG_AREA_SIZE, DimensionUnit::VP));
        theme->hoverTextAlpha_ =
            indexerPattern->GetAttr<Dimension>("hover_text_alpha", Dimension(HOVER_TEXT_ALPHA, DimensionUnit::PX));
        theme->focusBgOutlineSize_ = indexerPattern->GetAttr<Dimension>(
            "focus_bg_outline_size", Dimension(FOCUS_BG_OUTLINE_SIZE, DimensionUnit::VP));
    }

    static void ParseTextStyleAttributes(const RefPtr<ThemeStyle>& indexerPattern,
        const RefPtr<IndexerTheme>& theme)
    {
        theme->seletctTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("selected_text_color", Color(SELECT_TEXT_COLOR)));
        theme->seletctTextStyle_.SetFontStyle(FontStyle::NORMAL);
        theme->defaultTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("default_text_color", Color(DEFAULT_TEXT_COLOR)));
        theme->defaultTextStyle_.SetFontStyle(FontStyle::NORMAL);
        theme->popupTextStyle_.SetFontSize(
            indexerPattern->GetAttr<Dimension>("popup_text_size", Dimension(POPUP_TEXT_SIZE, DimensionUnit::VP)));
        theme->popupTextStyle_.SetTextColor(
            indexerPattern->GetAttr<Color>("popup_text_color", Color(POPUP_TEXT_COLOR)));
        theme->popupTextStyle_.SetFontWeight(FontWeight::MEDIUM);
        theme->popupTextStyle_.SetFontStyle(FontStyle::NORMAL);
    }

    static void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<IndexerTheme>& theme)
    {
        RefPtr<ThemeStyle> indexerPattern = themeConstants->GetPatternByName(THEME_PATTERN_INDEXER);
        if (!indexerPattern) {
            LOGE("Pattern of indexer is null, please check!");
            return;
        }
        ParseColorAttributes(indexerPattern, theme);
        ParseDimensionAttributes(indexerPattern, theme);
        ParseTextStyleAttributes(indexerPattern, theme);
        theme->accessibilityExpand_ = indexerPattern->GetAttr<std::string>("filter_accessibility_expand", "");
        theme->accessibilityCollapsed_ = indexerPattern->GetAttr<std::string>("filter_accessibility_expanded", "");
        theme->accessibilityExpanded_ = indexerPattern->GetAttr<std::string>("filter_accessibility_collapse", "");
        theme->accessibilityCollapse_ = indexerPattern->GetAttr<std::string>("filter_accessibility_collapsed", "");
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            theme->popupBackgroundColor_ = indexerPattern->GetAttr<Color>(
                "popup_background_color_api_twelve", Color(POPUP_BACKGROUND_COLOR_API_TWELVE));
            theme->popupUnclickedBgAreaColor_ =
                indexerPattern->GetAttr<Color>("popup_unclicked_bg_area_color", Color(POPUP_UNCLICKED_BG_AREA_COLOR));
            theme->hoverTextSize_ = indexerPattern->GetAttr<Dimension>(
                "hover_text_size_api_twelve", Dimension(HOVER_TEXT_SIZE_API_TWELVE, DimensionUnit::FP));
            theme->seletctTextStyle_.SetFontSize(indexerPattern->GetAttr<Dimension>(
                "hover_text_size_api_twelve", Dimension(HOVER_TEXT_SIZE_API_TWELVE, DimensionUnit::FP)));
            theme->seletctTextStyle_.SetFontWeight(FontWeight::MEDIUM);
            theme->defaultTextStyle_.SetFontSize(indexerPattern->GetAttr<Dimension>(
                "hover_text_size_api_twelve", Dimension(HOVER_TEXT_SIZE_API_TWELVE, DimensionUnit::FP)));
            theme->defaultTextStyle_.SetFontWeight(FontWeight::MEDIUM);
        } else {
            theme->popupBackgroundColor_ =
                indexerPattern->GetAttr<Color>("popup_background_color", Color(POPUP_BACKGROUND_COLOR));
            theme->popupUnclickedBgAreaColor_ =
                indexerPattern->GetAttr<Color>("popup_background_color", Color(POPUP_BACKGROUND_COLOR));
            theme->hoverTextSize_ =
                indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP));
            theme->seletctTextStyle_.SetFontSize(
                indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP)));
            theme->seletctTextStyle_.SetFontWeight(FontWeight::REGULAR);
            theme->defaultTextStyle_.SetFontSize(
                indexerPattern->GetAttr<Dimension>("hover_text_size", Dimension(HOVER_TEXT_SIZE, DimensionUnit::FP)));
            theme->defaultTextStyle_.SetFontWeight(FontWeight::REGULAR);
        }
    }
    static constexpr uint32_t DEFAULT_TEXT_COLOR = 0x99182431;
    static constexpr uint32_t POPUP_SELECTED_TEXT_COLOR = 0xff182431;
    static constexpr uint32_t POPUP_UNSELECTED_TEXT_COLOR = 0xff182431;
    static constexpr uint32_t SELECT_TEXT_COLOR = 0xff007dff;
    static constexpr uint32_t POPUP_TEXT_COLOR = 0xff007dff;
    static constexpr float POPUP_TEXT_SIZE = 24.0;
    static constexpr uint32_t SELECT_BACKGROUD_COLOR = 0x33007dff;
    static constexpr uint32_t SELECT_BACKGROUD_COLOR_ARC = 0xFF1F71FF;
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
    static constexpr uint32_t PRESSED_BG_AREA_COLOR = 0x19182431;
    static constexpr uint32_t SLIP_PRESSED_BACKGROUD_COLOR = 0x19182431;
    static constexpr uint32_t POPUP_CLICKED_BG_AREA_COLOR = 0x0c182431;
    static constexpr uint32_t POPUP_TITLE_BG_AREA_COLOR = 0x0c182431;
    static constexpr uint32_t POPUP_UNCLICKED_BG_AREA_COLOR = 0x00000000;
    static constexpr uint32_t POPUP_BACKGROUND_COLOR_API_TWELVE = 0x66808080;
    static constexpr float HOVER_TEXT_SIZE_API_TWELVE = 10.0f;
};
} // namespace OHOS::Ace
#endif
