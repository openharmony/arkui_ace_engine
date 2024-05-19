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
            theme->padding_ = Edge(themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL));
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
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
            theme->dragBackgroundColor_ =
                pattern->GetAttr<Color>("drag_background_color", Color::WHITE).ChangeOpacity(DRAG_BACKGROUND_OPACITY);
            theme->defaultCaretHeight_ = pattern->GetAttr<Dimension>("default_caret_height", 18.5_vp);
            theme->disabledAlpha_ = static_cast<float>(pattern->GetAttr<double>("text_color_disabled_alpha", 0.0));
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color(0x99000000));
            theme->caretColor_ = pattern->GetAttr<Color>("caret_color", Color(0xff007dff));
            theme->selectedBackgroundColor_ = pattern->GetAttr<Color>("selected_background_color", Color(0xff007dff));
            theme->previewUnderlineColor_ = pattern->GetAttr<Color>("preview_underline_color", Color(0xff007dff));
            theme->previewUnderlineWidth_ = pattern->GetAttr<Dimension>("preview_underline_width", 1.0_vp);
            RefPtr<ThemeStyle> textfieldPattern = themeConstants->GetPatternByName("textfield_pattern");
            if (!textfieldPattern) {
                LOGW("find pattern of textfield fail");
                return;
            }
            auto textfieldShowHandle = textfieldPattern->GetAttr<std::string>("textfield_show_handle", "0");
            theme->richeditorShowHandle_ = StringUtils::StringToInt(textfieldShowHandle);
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>("default_text_color", DEFAULT_TEXT_COLOR));
            theme->textStyle_.SetTextDecorationColor(pattern->GetAttr<Color>("default_text_color", DEFAULT_TEXT_COLOR));
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

    TextStyle GetTextStyle() const
    {
        return textStyle_;
    }

    const Color& GetDragBackgroundColor() const
    {
        return dragBackgroundColor_;
    }

protected:
    RichEditorTheme() = default;

private:
    float disabledAlpha_ = 0.0f;
    bool draggable_ = false;
    Dimension defaultCaretHeight_ = 18.5_vp;
    Dimension scrollbarMinHeight_ = 4.0_vp;
    Edge padding_;

    // UX::insert cursor offset up by 8vp
    Dimension insertCursorOffset_ = 8.0_vp;

    TextStyle textStyle_;
    Color placeholderColor_ = Color(0x99000000);
    Color caretColor_ = Color(0xff007dff);
    Color selectedBackgroundColor_ = Color(0xff007dff);
    Color dragBackgroundColor_ = Color::WHITE;
    Color previewUnderlineColor_ = Color(0xff007dff);
    Dimension previewUnderlineWidth_ = 1.0_vp;
    bool richeditorShowHandle_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_RICH_EDITOR_THEME_H
