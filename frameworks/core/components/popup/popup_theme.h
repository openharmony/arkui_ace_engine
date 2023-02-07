/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr uint32_t SHOW_TIME = 250; // unit is ms.
constexpr uint32_t HIDE_TIME = 250; // unit is ms.
constexpr Dimension TARGET_SPACE = 8.0_vp;
constexpr double DEFAULT_OPACITY = 0.95;
} // namespace

/**
 * PopupTheme defines color and styles of PopupComponent. PopupTheme should be built
 * using PopupTheme::Builder.
 */
class PopupTheme : public virtual Theme {
    DECLARE_ACE_TYPE(PopupTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<PopupTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<PopupTheme> theme = AceType::Claim(new PopupTheme());
            if (!themeConstants) {
                return theme;
            }
            // init theme from global data
            theme->padding_ = Edge(themeConstants->GetDimension(THEME_POPUP_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_POPUP_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_POPUP_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_POPUP_PADDING_VERTICAL));
            theme->maskColor_ = themeConstants->GetColor(THEME_POPUP_MASK_COLOR);
            theme->backgroundColor_ =
                themeConstants->GetColor(THEME_POPUP_BACKGROUND_COLOR).ChangeOpacity(DEFAULT_OPACITY);
            theme->textStyle_.SetTextColor(themeConstants->GetColor(THEME_POPUP_TEXT_COLOR));
            theme->textStyle_.SetFontSize(themeConstants->GetDimension(THEME_POPUP_TEXT_FONTSIZE));
            theme->radius_ = Radius(
                themeConstants->GetDimension(THEME_POPUP_RADIUS), themeConstants->GetDimension(THEME_POPUP_RADIUS));
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            theme->showTime_ = SHOW_TIME;
            theme->hideTime_ = HIDE_TIME;
            theme->targetSpace_ = TARGET_SPACE;
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<PopupTheme>& theme) const
        {
            if (!themeStyle || !theme) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_POPUP, nullptr);
            if (!pattern) {
                LOGW("find pattern of popup fail");
                return;
            }
            theme->backgroundColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, theme->backgroundColor_);
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 14.0_fp);
            theme->buttonFontSize_ = pattern->GetAttr<Dimension>(POPUP_BUTTON_TEXT_FONT_SIZE, 14.0_fp);
            theme->fontColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::WHITE);
            theme->buttonHoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, Color());
            theme->buttonPressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, Color());
            theme->focusColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, Color());
            theme->radius_ = Radius(pattern->GetAttr<Dimension>(POPUP_BORDER_RADIUS, 24.0_vp),
                pattern->GetAttr<Dimension>(POPUP_BORDER_RADIUS, 24.0_vp));
            theme->padding_ = Edge(pattern->GetAttr<Dimension>(POPUP_HORIZONTAL_PADDING, 16.0_vp),
                pattern->GetAttr<Dimension>(POPUP_VERTICAL_PADDING, 12.0_vp),
                pattern->GetAttr<Dimension>(POPUP_HORIZONTAL_PADDING, 16.0_vp),
                pattern->GetAttr<Dimension>(POPUP_VERTICAL_PADDING, 12.0_vp));
        }
    };

    ~PopupTheme() override = default;

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Color& GetMaskColor() const
    {
        return maskColor_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetButtonHoverColor() const
    {
        return buttonHoverColor_;
    }

    const Color& GetButtonBackgroundColor() const
    {
        return buttonBackgroundColor_;
    }

    const Color& GetButtonPressColor() const
    {
        return buttonPressColor_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetButtonFontSize() const
    {
        return buttonFontSize_;
    }

    const Color& GetFontColor() const
    {
        return fontColor_;
    }

    const Radius& GetRadius() const
    {
        return radius_;
    }

    uint32_t GetShowTime() const
    {
        return showTime_;
    }

    uint32_t GetHideTime() const
    {
        return hideTime_;
    }

    const Dimension& GetTargetSpace() const
    {
        return targetSpace_;
    }

    const Dimension& GetBubbleSpacing() const
    {
        return bubbleSpacing_;
    }

    const Dimension& GetButtonTextInsideMargin() const
    {
        return buttonTextInsideMargin_;
    }

    const Dimension& GetButtonSpacing() const
    {
        return buttonSpacing;
    }

    const Dimension& GetLittlePadding() const
    {
        return littlePadding_;
    }

    const Dimension& GetFocusPaintWidth() const
    {
        return focusPaintWidth_;
    }

    const Dimension& GetButtonMiniMumWidth() const
    {
        return buttonMiniMumWidth;
    }

    const Dimension& GetBubbleMiniMumHeight() const
    {
        return bubbleMiniMumHeight_;
    }

    const Dimension& GetArrowHeight() const
    {
        return arrowHeight_;
    }

protected:
    PopupTheme() = default;

private:
    Edge padding_;
    Color maskColor_;
    Color backgroundColor_;
    Color buttonHoverColor_ = Color(0x0cffffff);
    Color buttonBackgroundColor_ = Color::TRANSPARENT;
    Color buttonPressColor_ = Color(0x1affffff);
    Color focusColor_ = Color::WHITE;

    TextStyle textStyle_;
    Radius radius_;
    uint32_t showTime_ = 0;
    uint32_t hideTime_ = 0;
    Dimension targetSpace_;
    Dimension fontSize_;
    Dimension buttonFontSize_ = 14.0_fp;
    Color fontColor_;
    Dimension bubbleSpacing_ = 8.0_vp;
    Dimension buttonTextInsideMargin_ = 8.0_vp;
    Dimension buttonSpacing = 4.0_vp;
    Dimension littlePadding_ = 4.0_vp;
    Dimension arrowHeight_ = 8.0_vp;
    Dimension focusPaintWidth_ = 2.0_vp;
    Dimension buttonMiniMumWidth = 72.0_vp;
    Dimension bubbleMiniMumHeight_ = 48.0_vp;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_THEME_H
