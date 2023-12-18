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
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SHEET_BLANK_MINI_HEIGHT = 8.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_PADDING = 8.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_HEIGHT = 56.0_vp;
constexpr Dimension SHEET_OPERATION_AREA_HEIGHT_DOUBLE = 72.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_WIDTH = 40.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_HEIGHT = 40.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_IMAGE_HEIGHT = 18.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_IMAGE_WIDTH = 18.0_vp;
constexpr Dimension SHEET_CLOSE_ICON_TITLE_SPACE = 32.0_vp;
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
constexpr Dimension SHEET_DOUBLE_TITLE_TOP_PADDING = 15.0_vp;
constexpr Dimension SHEET_DOUBLE_TITLE_BOTTON_PADDING = 8.0_vp;
constexpr Dimension SHEET_TITLE_AERA_MARGIN = -8.0_vp;
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

            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<SheetTheme>& theme) const
        {
            if (!themeStyle) {
                LOGE("themeStyle is null");
                return;
            }

            auto sheetPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SHEET, nullptr);
            if (!sheetPattern) {
                LOGE("sheetPattern is null");
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
            theme->maskColor_ = sheetPattern->GetAttr<Color>("mask_color", Color(0x33182431));
            theme->closeIconColor_ = sheetPattern->GetAttr<Color>("close_icon_color", Color(0x0c182431));
            theme->closeIconImageColor_ = sheetPattern->GetAttr<Color>("close_icon_image_color", Color(0xff182431));
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

    const std::string& GetSheetType() const
    {
        return sheetType_;
    }

protected:
    SheetTheme() = default;

private:
    Dimension sheetRadius_;
    Dimension titleTextFontSize_;
    Dimension titleTextMargin_;
    Dimension subtitleTextFontSize_;
    Dimension subtitleTextMargin_;
    Color titleTextFontColor_;
    Color subtitleTextFontColor_;
    Color sheetBackgoundColor_;
    Color dragBarColor_;
    Color maskColor_;
    Color closeIconColor_;
    Color closeIconImageColor_;
    std::string sheetType_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHEET_SHEET_THEME_H
