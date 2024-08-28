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
constexpr Dimension BORDER_RADIUS_POPUP = 20.0_vp;
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
            ParsePattern(themeConstants, theme);
            theme->showTime_ = SHOW_TIME;
            theme->hideTime_ = HIDE_TIME;
            theme->targetSpace_ = TARGET_SPACE;
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<PopupTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_POPUP);
            if (!pattern) {
                LOGW("find pattern of popup fail");
                return;
            }
            theme->maskColor_ = pattern->GetAttr<Color>("popup_mask_color", Color());
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>("popup_text_color", Color()));
            theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>("popup_text_font_size", 0.0_vp));
            theme->backgroundColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, theme->backgroundColor_);
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 14.0_fp);
            theme->buttonFontSize_ = pattern->GetAttr<Dimension>(POPUP_BUTTON_TEXT_FONT_SIZE, 14.0_fp);
            theme->fontColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::WHITE);
            theme->buttonHoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, Color());
            theme->buttonPressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, Color());
            theme->focusColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, Color());
            auto popupBorderRadius = pattern->GetAttr<Dimension>("popup_border_radius", BORDER_RADIUS_POPUP);
            theme->radius_ = Radius(popupBorderRadius, popupBorderRadius);
            theme->padding_ = Edge(pattern->GetAttr<Dimension>(POPUP_HORIZONTAL_PADDING, 16.0_vp),
                pattern->GetAttr<Dimension>(POPUP_VERTICAL_PADDING, 12.0_vp),
                pattern->GetAttr<Dimension>(POPUP_HORIZONTAL_PADDING, 16.0_vp),
                pattern->GetAttr<Dimension>(POPUP_VERTICAL_PADDING, 12.0_vp));
            auto popupDoubleBorderEnable = pattern->GetAttr<std::string>("popup_double_border_enable", "0");
            theme->popupDoubleBorderEnable_ = StringUtils::StringToInt(popupDoubleBorderEnable);
            theme->popupOuterBorderWidth_ = pattern->GetAttr<Dimension>("popup_outer_border_width", 0.8_vp);
            theme->popupOuterBorderColor_ = pattern->GetAttr<Color>("popup_outer_border_color", Color::TRANSPARENT);
            theme->popupInnerBorderWidth_ = pattern->GetAttr<Dimension>("popup_inner_border_width", 0.8_vp);
            theme->popupInnerBorderColor_ = pattern->GetAttr<Color>("popup_inner_border_color", Color::TRANSPARENT);
            theme->buttonFontColor_ = pattern->GetAttr<Color>("text_primary_activated_color", Color::WHITE);
            theme->fontPrimaryColor_ = pattern->GetAttr<Color>("text_primary_color", Color::WHITE);
            theme->fontSecondaryColor_ = pattern->GetAttr<Color>("text_secondary_color", Color::WHITE);
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

    const Dimension& GetAgingTextLeftPadding() const
    {
        return ageTextLeftPadding_;
    }

    const Dimension& GetAgingTextRightPadding() const
    {
        return ageTextRightPadding_;
    }

    const Dimension& GetAgingButtonTextLeftPadding() const
    {
        return ageButtonTextLeftPadding_;
    }

    const Dimension& GetAgingButtonTextRightPadding() const
    {
        return ageButtonTextRightPadding_;
    }

    const Dimension& GetAgingButtonLeftPadding() const
    {
        return ageButtonLeftPadding_;
    }

    const Dimension& GetAgingButtonRightPadding() const
    {
        return ageButtonRightPadding_;
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

    float GetPopupAnimationOffset() const
    {
        return popupAnimationOffset_;
    }

    int32_t GetShowDuration() const
    {
        return popupAnimationShowDuration_;
    }

    int32_t GetCloseDuration() const
    {
        return popupAnimationCloseDuration_;
    }
    int32_t GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }
    int32_t GetHoverToPressAnimationDuration() const
    {
        return hoverToPressAnimationDuration_;
    }

    float GetOpacityStart() const
    {
        return opacityStart_;
    }

    float GetOpacityEnd() const
    {
        return opacityEnd_;
    }

    float GetHoverOpacity() const
    {
        return opacityHover_;
    }

    float GetPressOpacity() const
    {
        return opacityPress_;
    }

    int32_t GetPopupDoubleBorderEnable() const
    {
        return popupDoubleBorderEnable_;
    }

    Dimension GetPopupOuterBorderWidth() const
    {
        return popupOuterBorderWidth_;
    }

    Color GetPopupOuterBorderColor() const
    {
        return popupOuterBorderColor_;
    }

    Dimension GetPopupInnerBorderWidth() const
    {
        return popupInnerBorderWidth_;
    }

    Color GetPopupInnerBorderColor() const
    {
        return popupInnerBorderColor_;
    }

    Color GetButtonFontColor() const
    {
        return buttonFontColor_;
    }

    Color GetFontPrimaryColor() const
    {
        return fontPrimaryColor_;
    }

    Color GetFontSecondaryColor() const
    {
        return fontSecondaryColor_;
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
    int32_t popupDoubleBorderEnable_ = 0;
    Dimension popupOuterBorderWidth_ = 0.8_vp;
    Color popupOuterBorderColor_ = Color::TRANSPARENT;
    Dimension popupInnerBorderWidth_ = 0.8_vp;
    Color popupInnerBorderColor_ = Color::TRANSPARENT;

    TextStyle textStyle_;
    Radius radius_;
    uint32_t showTime_ = 0;
    uint32_t hideTime_ = 0;
    Dimension targetSpace_ = TARGET_SPACE;
    Dimension fontSize_;
    Dimension buttonFontSize_ = 14.0_fp;
    Color fontColor_;
    Dimension bubbleSpacing_ = 8.0_vp;
    Dimension ageTextLeftPadding_ = 12.0_vp;
    Dimension ageTextRightPadding_ = 12.0_vp;
    Dimension ageButtonTextLeftPadding_ = 12.0_vp;
    Dimension ageButtonTextRightPadding_ = 16.0_vp;
    Dimension ageButtonLeftPadding_ = 0.0_vp;
    Dimension ageButtonRightPadding_ = 0.0_vp;
    Dimension buttonTextInsideMargin_ = 8.0_vp;
    Dimension buttonSpacing = 4.0_vp;
    Dimension littlePadding_ = 4.0_vp;
    Dimension arrowHeight_ = 8.0_vp;
    Dimension focusPaintWidth_ = 2.0_vp;
    Dimension buttonMiniMumWidth = 72.0_vp;
    Dimension bubbleMiniMumHeight_ = 48.0_vp;
    float popupAnimationOffset_ = 8.0f;
    int32_t popupAnimationShowDuration_ = 250;
    int32_t popupAnimationCloseDuration_ = 100;
    int32_t hoverAnimationDuration_ = 250;
    int32_t hoverToPressAnimationDuration_ = 100;
    float opacityStart_ = 0.0f;
    float opacityEnd_ = 1.0f;
    float opacityHover_ = 0.05f;
    float opacityPress_ = 0.1f;
    Color buttonFontColor_;
    Color fontPrimaryColor_;
    Color fontSecondaryColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_THEME_H
