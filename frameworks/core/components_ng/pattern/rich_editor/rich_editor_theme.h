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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
/**
 * TextTheme defines color and styles of ThemeComponent. RichEditorTheme should be built
 * using RichEditorTheme::Builder.
 */

namespace {
constexpr Color DEFAULT_TEXT_COLOR = Color(0xe5000000);
constexpr float DRAG_BACKGROUND_OPACITY = 0.95f;
constexpr float DEFAULT_TEXT_SIZE = 16.0f;
} // namespace

class RichEditorTheme : public virtual Theme {
    DECLARE_ACE_TYPE(RichEditorTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<RichEditorTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<RichEditorTheme> theme = AceType::Claim(new RichEditorTheme());
            if (!themeConstants) {
                return theme;
            }
            InitThemeDefaults(themeConstants, theme);
            ParsePattern(themeConstants, theme);
            return theme;
        }

    protected:
        void InitThemeDefaults(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RichEditorTheme>& theme) const
        {
            CHECK_NULL_VOID(theme && themeConstants);
            theme->padding_ = Edge(themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL));
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RichEditorTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_RICH_EDITOR);
            if (!pattern) {
                return;
            }
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            auto dragBackgroundColor = pattern->GetAttr<Color>("drag_background_color", Color::WHITE);
            if (Container::CurrentColorMode() == ColorMode::DARK) {
                dragBackgroundColor = dragBackgroundColor.ChangeOpacity(DRAG_BACKGROUND_OPACITY);
            }
            theme->dragBackgroundColor_ = dragBackgroundColor;
            theme->dragCornerRadius_ = pattern->GetAttr<Dimension>("drag_corner_radius", 18.0_vp);
            theme->defaultCaretHeight_ = pattern->GetAttr<Dimension>("default_caret_height", 18.5_vp);
            theme->disabledAlpha_ = static_cast<float>(pattern->GetAttr<double>("text_color_disabled_alpha", 0.0));
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color(0x99000000));
            theme->caretColor_ = pattern->GetAttr<Color>("caret_color", Color(0xff007dff));
            theme->selectedBackgroundColor_ = pattern->GetAttr<Color>("selected_background_color", Color(0xff007dff));
            theme->previewUnderlineColor_ = pattern->GetAttr<Color>("preview_underline_color", Color(0xff007dff));
            theme->popIconColor_ = pattern->GetAttr<Color>("pop_icon_color", Color(0x99000000));
            theme->menuTitleColor_ = pattern->GetAttr<Color>("menu_title_color", Color(0x99000000));
            theme->menuTextColor_ = pattern->GetAttr<Color>("menu_text_color", Color(0x99000000));
            theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color", Color(0x99000000));
            theme->previewUnderlineWidth_ = pattern->GetAttr<Dimension>("preview_underline_width", 2.0_vp);
            auto showHandle = pattern->GetAttr<std::string>("rich_editor_show_handle", "0");
            theme->richeditorShowHandle_ = StringUtils::StringToInt(showHandle);
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>("default_text_color", DEFAULT_TEXT_COLOR));
            theme->textStyle_.SetTextDecorationColor(pattern->GetAttr<Color>("default_text_color", DEFAULT_TEXT_COLOR));
            theme->textStyle_.SetFontSize(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP));
            theme->aiWriteBundleName_ = pattern->GetAttr<std::string>("rich_editor_writting_bundle_name", "");
            theme->aiWriteAbilityName_ = pattern->GetAttr<std::string>("rich_editor_writting_ability_name", "");
            theme->aiWriteIsSupport_ = pattern->GetAttr<std::string>("rich_editor_writting_is_support", "");
            auto translateIsSupport = pattern->GetAttr<std::string>("menu_translate_is_support", "0");
            theme->translateIsSupport_ = StringUtils::StringToInt(translateIsSupport);
            auto searchIsSupport = pattern->GetAttr<std::string>("richeditor_menu_search_is_support", "0");
            theme->searchIsSupport_ = StringUtils::StringToInt(searchIsSupport);
            theme->urlDisabledOpacity_ = pattern->GetAttr<double>("interactive_disable", URL_DISA_OPACITY);
            theme->urlDefaultColor_ = pattern->GetAttr<Color>("font_emphasize", Color(0xff007dff));
            theme->urlDisabledColor_ = theme->urlDefaultColor_.BlendOpacity(theme->urlDisabledOpacity_);
            theme->urlHoverColor_ = pattern->GetAttr<Color>("interactive_hover", Color(0x0C182431));
            theme->urlPressColor_ = pattern->GetAttr<Color>("interactive_pressed", Color(0x19182431));
            theme->cameraSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.camera");
            theme->scanSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.line_viewfinder");
            theme->imageSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.picture");
            theme->chevronRightSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_right");
        }
    };

    ~RichEditorTheme() override = default;

    bool GetDraggable() const
    {
        return draggable_;
    }

    const Dimension& GetDefaultCaretHeight() const
    {
        return defaultCaretHeight_;
    }

    float GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

    const Dimension& GetScrollbarMinHeight()
    {
        return scrollbarMinHeight_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetInsertCursorOffset() const
    {
        return insertCursorOffset_;
    }

    const Color& GetPreviewUnderLineColor() const
    {
        return previewUnderlineColor_;
    }

    const Color& GetPopIconColor() const
    {
        return popIconColor_;
    }

    const Color& GetMenuTitleColor() const
    {
        return menuTitleColor_;
    }

    const Color& GetMenuTextColor() const
    {
        return menuTextColor_;
    }

    const Color& GetMenuIconColor() const
    {
        return menuIconColor_;
    }

    const Dimension& GetPreviewUnderlineWidth()
    {
        return previewUnderlineWidth_;
    }

    const Color& GetPlaceholderColor() const
    {
        return placeholderColor_;
    }

    const Color GetCaretColor()
    {
        return caretColor_;
    }

    const Color GetSelectedBackgroundColor()
    {
        return selectedBackgroundColor_;
    }

    bool IsRichEditorShowHandle() const
    {
        return richeditorShowHandle_;
    }

    const Color& GetDragBackgroundColor() const
    {
        return dragBackgroundColor_;
    }

    TextStyle GetTextStyle() const
    {
        return textStyle_;
    }

    Dimension GetDragCornerRadius() const
    {
        return dragCornerRadius_;
    }
    const std::string& GetAIWriteBundleName() const
    {
        return aiWriteBundleName_;
    }
    const std::string& GetAIWriteAbilityName() const
    {
        return aiWriteAbilityName_;
    }

    const std::string& GetAIWriteIsSupport() const
    {
        return aiWriteIsSupport_;
    }

    bool GetTranslateIsSupport() const
    {
        return translateIsSupport_;
    }

    bool GetSearchIsSupport() const
    {
        return searchIsSupport_;
    }

    const Color& GetUrlDisabledColor() const
    {
        return urlDisabledColor_;
    }

    const Color& GetUrlDefaultColor() const
    {
        return urlDefaultColor_;
    }

    const Color& GetUrlHoverColor() const
    {
        return urlHoverColor_;
    }

    const Color& GetUrlPressColor() const
    {
        return urlPressColor_;
    }

    uint32_t GetCameraSymbolId() const
    {
        return cameraSymbolId_;
    }

    uint32_t GetScanSymbolId() const
    {
        return scanSymbolId_;
    }

    uint32_t GetImageSymbolId() const
    {
        return imageSymbolId_;
    }

    uint32_t GetChevronRightSymbolId() const
    {
        return chevronRightSymbolId_;
    }
protected:
    RichEditorTheme() = default;
    TextStyle textStyle_;
    float urlDisabledOpacity_ = URL_DISA_OPACITY;
    Color urlDisabledColor_ = Color(0x99000000);
    Color urlDefaultColor_ = Color(0x99000000);
    Color urlHoverColor_ = Color(0x99000000);
    Color urlPressColor_ = Color(0x99000000);

private:
    float disabledAlpha_ = 0.0f;
    bool draggable_ = false;
    Dimension defaultCaretHeight_ = 18.5_vp;
    Dimension scrollbarMinHeight_ = 4.0_vp;
    Edge padding_;

    // UX::insert cursor offset up by 24vp
    Dimension insertCursorOffset_ = 24.0_vp;
    Color placeholderColor_ = Color(0x99000000);
    Color caretColor_ = Color(0xff007dff);
    Color selectedBackgroundColor_ = Color(0xff007dff);
    Color dragBackgroundColor_ = Color::WHITE;
    Dimension dragCornerRadius_ = 18.0_vp;
    Color previewUnderlineColor_ = Color(0xff007dff);
    Color popIconColor_ = Color(0x99000000);
    Color menuTitleColor_ = Color(0x99000000);
    Color menuTextColor_ = Color(0x99000000);
    Color menuIconColor_ = Color(0x99000000);
    Dimension previewUnderlineWidth_ = 2.0_vp;
    bool richeditorShowHandle_ = false;
    std::string aiWriteBundleName_;
    std::string aiWriteAbilityName_;
    std::string aiWriteIsSupport_;
    bool translateIsSupport_ = false;
    bool searchIsSupport_ = false;
    uint32_t cameraSymbolId_;
    uint32_t scanSymbolId_;
    uint32_t imageSymbolId_;
    uint32_t chevronRightSymbolId_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H
