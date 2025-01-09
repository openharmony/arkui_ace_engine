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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHEET_SHEET_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHEET_SHEET_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SHEET_BLANK_MINI_HEIGHT = 8.0_vp;
constexpr Dimension SHEET_HOVERMODE_UP_HEIGHT = 40.0_vp;
constexpr Dimension SHEET_HOVERMODE_DOWN_HEIGHT = 28.0_vp;
constexpr Dimension SHEET_BLANK_FLOATING_STATUS_BAR = 32.0_vp;
constexpr Dimension SHEET_SPLIT_AI_BAR = 24.0_vp;
constexpr Dimension SHEET_SPLIT_STATUS_BAR = 24.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_PADDING = 8.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_HEIGHT = 56.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_HEIGHT_DOUBLE = 72.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_WIDTH = 40.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_HEIGHT = 40.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_IMAGE_HEIGHT = 18.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_IMAGE_WIDTH = 18.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_TITLE_SPACE = 32.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_TITLE_SPACE_NEW = 8.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_RADIUS = 20.0_vp;
constexpr Dimension SHEET_DRAG_BAR_WIDTH = 64.0_vp;
constexpr Dimension SHEET_DRAG_BAR_HEIGHT = 16.0_vp;
constexpr Dimension SHEET_LANDSCAPE_WIDTH = 480.0_vp;
constexpr Dimension SHEET_POPUP_WIDTH = 360.0_vp;
constexpr Dimension SHEET_BIG_WINDOW_WIDTH = 480.0_vp;
constexpr Dimension SHEET_BIG_WINDOW_HEIGHT = 560.0_vp;
constexpr Dimension SHEET_BIG_WINDOW_MIN_HEIGHT = 320.0_vp;
constexpr Dimension SHEET_ARROW_WIDTH = 32.0_vp;
constexpr Dimension SHEET_ARROW_HEIGHT = 8.0_vp;
constexpr Dimension SHEET_TARGET_SPACE = 8.0_vp;
constexpr Dimension SHEET_DEVICE_WIDTH_BREAKPOINT = 600.0_vp;
constexpr Dimension SHEET_PC_DEVICE_WIDTH_BREAKPOINT = 840.0_vp;
constexpr Dimension SHEET_DOUBLE_TITLE_TOP_PADDING = 16.0_vp;
constexpr Dimension SHEET_DOUBLE_TITLE_BOTTON_MARGIN = 4.0_vp;
constexpr Dimension SHEET_TITLE_AREA_MARGIN = -8.0_vp;
constexpr int32_t SHEET_TITLE_MAX_LINES = 1;
constexpr int32_t SHEET_SHADOW_NONE = 6;
constexpr Dimension SHEET_TITLE_TEXT_HORIZONTAL_MARGIN = 16.0_vp;
constexpr double SHEET_TITLE_FONT_WEIGHT = 9.0;
} // namespace
class SheetTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SheetTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SheetTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SheetTheme> theme = AceType::Claim(new SheetTheme());
            if (!themeConstants) {
                return theme;
            }

            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SheetTheme>& theme) const
        {
            RefPtr<ThemeStyle> sheetPattern = themeConstants->GetPatternByName(THEME_PATTERN_SHEET);
            if (!sheetPattern) {
                TAG_LOGE(AceLogTag::ACE_SHEET, "sheetPattern is null");
                return;
            }

            theme->sheetRadius_ = sheetPattern->GetAttr<Dimension>("sheet_radius", 32.0_vp);
            theme->titleTextFontSize_ = sheetPattern->GetAttr<Dimension>("title_text_font_size", 20.0_vp);
            theme->titleTextMargin_ = sheetPattern->GetAttr<Dimension>("title_text_margin", 16.0_vp);
            theme->subtitleTextFontSize_ = sheetPattern->GetAttr<Dimension>("subtitle_text_font_size", 14.0_fp);
            theme->subtitleTextMargin_ = sheetPattern->GetAttr<Dimension>("subtitle_text_margin", 2.0_fp);
            theme->titleTextFontColor_ = sheetPattern->GetAttr<Color>("title_text_font_color", Color(0xff182431));
            theme->subtitleTextFontColor_ = sheetPattern->GetAttr<Color>("subtitle_text_font_color", Color(0x99182431));
            theme->sheetBackgoundColor_ = sheetPattern->GetAttr<Color>("sheet_background_color", Color(0xfff1f3f5));
            theme->dragBarColor_ = sheetPattern->GetAttr<Color>("drag_bar_color", Color(0x33182431));
            theme->sheetType_ = sheetPattern->GetAttr<std::string>("sheet_type", "auto");
            theme->sheetBottom_ = sheetPattern->GetAttr<std::string>("sheet_bottom", "auto");
            theme->maskColor_ = sheetPattern->GetAttr<Color>("mask_color", Color(0x33182431));
            theme->closeIconColor_ = sheetPattern->GetAttr<Color>("close_icon_color", Color(0x0c182431));
            theme->closeIconImageColor_ = sheetPattern->GetAttr<Color>("close_icon_image_color", Color(0xff182431));
            theme->sheetBackgroundBlurStyle_ = sheetPattern->GetAttr<int>("sheet_background_blur_style", 0);
            theme->sheetNormalScale_ = sheetPattern->GetAttr<double>("sheet_normal_aging_scale", 1.0f);
            theme->sheetMaxAgingScale_ = sheetPattern->GetAttr<double>("sheet_max_aging_scale", 1.75f);
            theme->closeIconSource_ = themeConstants->GetSymbolByName("sys.symbol.xmark");
            theme->closeIconSymbolColor_ = sheetPattern->GetAttr<Color>("close_icon_symbol_color", Color(0xff182431));
            theme->sheetShadowConfig_ = sheetPattern->GetAttr<int32_t>("sheet_shadow_config", SHEET_SHADOW_NONE);
            theme->sheetShadowConfigS_ = sheetPattern->GetAttr<int32_t>("sheet_shadow_config_s", SHEET_SHADOW_NONE);
            theme->sheetOuterBorderWidth_ = sheetPattern->GetAttr<Dimension>("sheet_outline_border_width", 0.0_vp);
            // If the outline border width is valid, outline border, shadow and border are default enable.
            theme->isOuterBorderEnable_ = theme->sheetOuterBorderWidth_.IsValid();
            theme->sheetInnerBorderWidth_ = sheetPattern->GetAttr<Dimension>("sheet_inner_border_width", 0.0_vp);
            theme->sheetOuterBorderColor_ =
                sheetPattern->GetAttr<Color>("sheet_outline_border_color", Color::TRANSPARENT);
            theme->sheetInnerBorderColor_ =
                sheetPattern->GetAttr<Color>("sheet_inner_border_color", Color::TRANSPARENT);
            theme->closeIconWidth_ =
                sheetPattern->GetAttr<Dimension>("close_icon_width", SHEET_CLOSE_ICON_IMAGE_HEIGHT);
            theme->titleTextHorizMargin_ =
                sheetPattern->GetAttr<Dimension>("title_text_horizontal_margin", SHEET_TITLE_TEXT_HORIZONTAL_MARGIN);
            theme->closeIconRadius_ = sheetPattern->GetAttr<Dimension>("close_icon_radius", SHEET_CLOSE_ICON_RADIUS);
            ParseAdditionalStylePattern(sheetPattern, theme);
        }

        void ParseAdditionalStylePattern(
            const RefPtr<ThemeStyle>& sheetPattern, const RefPtr<SheetTheme>& theme) const
        {
            theme->largePercent_ = sheetPattern->GetAttr<double>("sheet_height_percent_large", 1.0f);
            theme->mediumPercent_ = sheetPattern->GetAttr<double>("sheet_height_percent_medium", 0.6f);
            theme->operationAreaHeight_ = sheetPattern->GetAttr<Dimension>("sheet_operation_height", 56.0_vp);
            theme->heightApplyFullScreen_ =
                static_cast<bool>(sheetPattern->GetAttr<int>("sheet_height_apply_full_screen", 0));
            theme->showCloseIcon_ = static_cast<bool>(sheetPattern->GetAttr<int>("sheet_show_close_icon", 1));
            theme->sheetTitleFontWeight_ = FontWeight(static_cast<int32_t>(
                sheetPattern->GetAttr<double>("sheet_title_font_weight", SHEET_TITLE_FONT_WEIGHT)));
            theme->sheetDragBarHeight_ = sheetPattern->GetAttr<Dimension>("sheet_drag_bar_height",
                SHEET_DRAG_BAR_HEIGHT);
            theme->titleTopPadding_ = sheetPattern->GetAttr<Dimension>("sheet_double_title_top_padding",
                SHEET_DOUBLE_TITLE_TOP_PADDING);
            theme->sheetTitleAreaMargin_ = sheetPattern->GetAttr<Dimension>("sheet_title_area_margin",
                SHEET_TITLE_AREA_MARGIN);
        }
    };
    ~SheetTheme() override = default;

    const Dimension& GetSheetRadius() const
    {
        return sheetRadius_;
    }

    const Dimension& GetTitleTextFontSize() const
    {
        return titleTextFontSize_;
    }

    const Dimension& GetTitleTextMargin() const
    {
        return titleTextMargin_;
    }

    const Dimension& GetTitleTextHorizMargin() const
    {
        return titleTextHorizMargin_;
    }

    const Dimension& GetSubtitleTextFontSize() const
    {
        return subtitleTextFontSize_;
    }

    const Dimension& GetSubtitleTextMargin() const
    {
        return subtitleTextMargin_;
    }

    const Color& GetTitleTextFontColor() const
    {
        return titleTextFontColor_;
    }

    const Color& GetSubtitleTextFontColor() const
    {
        return subtitleTextFontColor_;
    }

    const Color& GetSheetBackgoundColor() const
    {
        return sheetBackgoundColor_;
    }

    const Color& GetDragBarColor() const
    {
        return dragBarColor_;
    }

    const Color& GetMaskColor() const
    {
        return maskColor_;
    }

    const Color& GetCloseIconColor() const
    {
        return closeIconColor_;
    }

    const Color& GetCloseIconImageColor() const
    {
        return closeIconImageColor_;
    }

    bool IsOnlyBottom() const
    {
        return sheetBottom_ == "bottom";
    }

    const std::string& GetSheetType() const
    {
        return sheetType_;
    }

    const int& GetSheetBackgroundBlurStyle() const
    {
        return sheetBackgroundBlurStyle_;
    }

    const double& GetSheetNormalScale() const
    {
        return sheetNormalScale_;
    }

    const double& GetSheetMaxAgingScale() const
    {
        return sheetMaxAgingScale_;
    }

    const Color& GetCloseIconSymbolColor() const
    {
        return closeIconSymbolColor_;
    }

    const uint32_t& GetCloseIconSource() const
    {
        return closeIconSource_;
    }

    int32_t GetSheetShadowConfig() const
    {
        return sheetShadowConfig_;
    }

    int32_t GetSheetShadowConfigS() const
    {
        return sheetShadowConfigS_;
    }

    const Dimension& GetSheetOuterBorderWidth() const
    {
        return sheetOuterBorderWidth_;
    }

    const Dimension& GetSheetInnerBorderWidth() const
    {
        return sheetInnerBorderWidth_;
    }

    const Color& GetSheetOuterBorderColor() const
    {
        return sheetOuterBorderColor_;
    }

    const Color& GetSheetInnerBorderColor() const
    {
        return sheetInnerBorderColor_;
    }

    bool IsOuterBorderEnable() const
    {
        return isOuterBorderEnable_;
    }

    const Dimension& GetCloseIconWidth() const
    {
        return closeIconWidth_;
    }

    const Dimension& GetCloseIconRadius() const
    {
        return closeIconRadius_;
    }

    const Dimension& GetOperationAreaHeight() const
    {
        return operationAreaHeight_;
    }

    double GetLargePercent() const
    {
        return largePercent_;
    }

    double GetMediumPercent() const
    {
        return mediumPercent_;
    }

    bool GetHeightApplyFullScreen() const
    {
        return heightApplyFullScreen_;
    }

    bool GetShowCloseIcon() const
    {
        return showCloseIcon_;
    }
    const FontWeight& GetSheetTitleFontWeight() const
    {
        return sheetTitleFontWeight_;
    }

    const Dimension& GetSheetDragBarHeight() const
    {
        return sheetDragBarHeight_;
    }

    const Dimension& GetTitleTopPadding() const
    {
        return titleTopPadding_;
    }

    const Dimension& GetSheetTitleAreaMargin() const
    {
        return sheetTitleAreaMargin_;
    }
protected:
    SheetTheme() = default;

private:
    Dimension sheetRadius_;
    Dimension titleTextFontSize_;
    Dimension titleTextMargin_;
    Dimension subtitleTextFontSize_;
    Dimension subtitleTextMargin_;
    Dimension sheetDragBarHeight_;
    Dimension titleTopPadding_;
    Dimension sheetTitleAreaMargin_;
    FontWeight sheetTitleFontWeight_ = FontWeight::BOLD;
    Color titleTextFontColor_;
    Color subtitleTextFontColor_;
    Color sheetBackgoundColor_;
    Color dragBarColor_;
    Color maskColor_;
    Color closeIconColor_;
    Color closeIconImageColor_;
    Color closeIconSymbolColor_;
    std::string sheetType_;
    std::string sheetBottom_;
    int sheetBackgroundBlurStyle_;
    double sheetNormalScale_;
    double sheetMaxAgingScale_;
    uint32_t closeIconSource_ = 0;
    int32_t sheetShadowConfig_;
    int32_t sheetShadowConfigS_;
    Dimension sheetOuterBorderWidth_;
    Dimension sheetInnerBorderWidth_;
    bool isOuterBorderEnable_;
    Color sheetOuterBorderColor_;
    Color sheetInnerBorderColor_;
    Dimension closeIconWidth_;
    Dimension titleTextHorizMargin_;
    Dimension closeIconRadius_;
    Dimension operationAreaHeight_;
    double largePercent_ = 1.0; // 1.0 is default value
    double mediumPercent_ = 0.6; // 0.6 is default value
    bool heightApplyFullScreen_ = false;
    bool showCloseIcon_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHEET_SHEET_THEME_H
