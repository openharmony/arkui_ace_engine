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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * PieceTheme defines default style of DOMPiece,using PieceTheme::Builder to build DOMPiece.
 */
class PieceTheme : public virtual Theme {
    DECLARE_ACE_TYPE(PieceTheme, Theme);

public:
    class Builder final {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<PieceTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<PieceTheme> theme = AceType::MakeRefPtr<PieceTheme>();
            if (!themeConstants) {
                return theme;
            }
            theme->iconResource_ = themeConstants->GetResourceId(THEME_PIECE_ICON_SOURCE);
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<PieceTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_PIECE);
            if (!pattern) {
                LOGW("find pattern of piece fail");
                return;
            }
            theme->height_ = pattern->GetAttr<Dimension>("piece_height", 0.0_vp);
            theme->textStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);
            auto maxlines = static_cast<int32_t>(pattern->GetAttr<double>("piece_text_lines", 0.0));
            theme->textStyle_.SetMaxLines(maxlines < 0 ? UINT32_MAX : maxlines);
            theme->textStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("piece_font_weight", 0.0))));
            theme->paddingHorizontal_ = pattern->GetAttr<Dimension>("piece_padding_horizontal", 0.0_vp);
            theme->paddingVertical_ = pattern->GetAttr<Dimension>("piece_padding_vertical", 0.0_vp);
            theme->iconSize_ = pattern->GetAttr<Dimension>("piece_icon_size", 0.0_vp);
            theme->interval_ = pattern->GetAttr<Dimension>("piece_interval", 0.0_vp);
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color()));
            theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_fp));
            theme->backgroundColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color())
                .BlendOpacity(pattern->GetAttr<double>(PATTERN_BG_COLOR_ALPHA, 0.0));
            theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, Color());
        }
    };

    ~PieceTheme() override = default;
    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }
    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }
    const Dimension& GetHeight() const
    {
        return height_;
    }
    const Dimension& GetPaddingVertical() const
    {
        return paddingVertical_;
    }
    const Dimension& GetPaddingHorizontal() const
    {
        return paddingHorizontal_;
    }
    const Dimension& GetInterval() const
    {
        return interval_;
    }
    InternalResource::ResourceId GetIconResource() const
    {
        return iconResource_;
    }
    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }
    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

protected:
    PieceTheme() = default;

private:
    Color hoverColor_;
    Color backgroundColor_;
    Dimension height_;
    Dimension interval_;
    Dimension iconSize_;
    Dimension paddingVertical_;
    Dimension paddingHorizontal_;
    TextStyle textStyle_;
    InternalResource::ResourceId iconResource_ = InternalResource::ResourceId::NO_ID;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PIECE_PIECE_THEME_H
