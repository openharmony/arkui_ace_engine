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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_INDICATOR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_INDICATOR_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

constexpr double SWIPER_ARROW_ALPHA_DISABLED = 0.4;

class SwiperIndicatorTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SwiperIndicatorTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SwiperIndicatorTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SwiperIndicatorTheme> theme = AceType::Claim(new SwiperIndicatorTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->color_ = themeConstants->GetColor(THEME_SWIPER_INDICATOR_NORMAL_COLOR);
            theme->selectedColor_ = themeConstants->GetColor(THEME_SWIPER_INDICATOR_SELECTED_COLOR);
            theme->size_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_SIZE);
            theme->selectedSize_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_SELECTED_SIZE);
            theme->isHasMask_ = themeConstants->GetInt(THEME_SWIPER_INDICATOR_MASK);
            theme->indicatorPointPadding_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_POINT_PADDING);
            theme->digitalIndicatorTextStyle_.SetFontSize(
                themeConstants->GetDimension(THEME_SWIPER_DIGITAL_INDICATOR_FONT_SIZE));
            theme->digitalIndicatorTextStyle_.SetTextColor(
                themeConstants->GetColor(THEME_SWIPER_DIGITAL_INDICATOR_TEXT_COLOR));
            theme->startEndPadding_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_START_END_PADDING);
            theme->pressPadding_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_PRESS_PADDING);
            theme->pressPointPadding_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_PRESS_POINT_PADDING);
            theme->pressSize_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_PRESS_SIZE);
            theme->hoverSize_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_HOVER_SIZE);
            theme->hotZoneSize_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_HOTZONE_SIZE);
            theme->hotZoneColor_ = themeConstants->GetColor(THEME_SWIPER_INDICATOR_HOTZONE_COLOR);
            theme->hotZoneSize_ = themeConstants->GetDimension(THEME_SWIPER_INDICATOR_HOTZONE_SIZE);
            theme->indicatorTextFocusColor_ = themeConstants->GetColor(THEME_SWIPER_DIGITAL_INDICATOR_FOCUS_TEXT_COLOR);
            theme->isIndicatorDisabled_ = themeConstants->GetInt(THEME_SWIPER_INDICATOR_DISABLED);
            theme->animationCurve_ = AnimationCurve(themeConstants->GetInt(THEME_SWIPER_ANIMATION_CURVE));
            theme->animationOpacity_ = themeConstants->GetInt(THEME_SWIPER_ANIMATION_OPACITY);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<SwiperIndicatorTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto swiperPattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SWIPER, nullptr);
            if (!swiperPattern) {
                LOGW("find pattern of swiper fail");
                return;
            }
            theme->color_ = swiperPattern->GetAttr<Color>("indicator_color", Color::TRANSPARENT);
            theme->hotZoneColor_ = swiperPattern->GetAttr<Color>("indicator_hotzone_color", Color::TRANSPARENT);
            theme->indicatorTextFocusColor_ =
                swiperPattern->GetAttr<Color>("indicator_text_color_focused", Color::TRANSPARENT);
            theme->digitalIndicatorTextStyle_.SetTextColor(
                swiperPattern->GetAttr<Color>("indicator_text_font_color", Color::TRANSPARENT));
            theme->digitalIndicatorTextStyle_.SetFontSize(
                swiperPattern->GetAttr<Dimension>("indicator_text_font_size", 14.0_vp));
            theme->selectedColor_ = swiperPattern->GetAttr<Color>("indicator_color_selected", Color::TRANSPARENT);
            theme->hoverColor_ = swiperPattern->GetAttr<Color>("indicator_color_hover", Color::TRANSPARENT);
            theme->pressedColor_ = swiperPattern->GetAttr<Color>("indicator_color_pressed", Color::TRANSPARENT);
            theme->focusedColor_ = swiperPattern->GetAttr<Color>("indicator_color_focused", Color::TRANSPARENT);
            theme->arrowBoardColorHover_ =
                swiperPattern->GetAttr<Color>("arrow_color_boardColor_hover", Color::TRANSPARENT);
            theme->arrowBoardColorClick_ =
                swiperPattern->GetAttr<Color>("arrow_color_boardColor_click", Color::TRANSPARENT);
            theme->arrowColorPrimary_ = swiperPattern->GetAttr<Color>("arrow_color_primary", Color::TRANSPARENT);
            theme->arrowColorPrimaryContrary_ =
                swiperPattern->GetAttr<Color>("arrow_color_primary_contrary", Color::TRANSPARENT);
            theme->arrowDisabledAlpha_ =
                swiperPattern->GetAttr<double>("arrow_disabled_alpha", SWIPER_ARROW_ALPHA_DISABLED);
            theme->arrowScale_ = Dimension(24.0_vp);
            theme->arrowHorizontalMargin_ = swiperPattern->GetAttr<Dimension>("arrow_horizontal_margin", 8.0_vp);
            theme->arrowVerticalMargin_ = swiperPattern->GetAttr<Dimension>("arrow_vertical_margin", 8.0_vp);
            theme->smallArrowBoardSize_ = Dimension(24.0_vp);
            theme->smallArrowSize_ = Dimension(18.0_vp);
            theme->smallArrowBoardColor_ = Color::TRANSPARENT;
            theme->smallArrowColor_ = swiperPattern->GetAttr<Color>("arrow_color_primary", Color::TRANSPARENT);
            theme->bigArrowBoardSize_ = Dimension(32.0_vp);
            theme->bigArrowSize_ = Dimension(24.0_vp);
            theme->bigArrowBoardColor_ =
                swiperPattern->GetAttr<Color>("arrow_color_component_normal", Color::TRANSPARENT);
            theme->bigArrowColor_ = swiperPattern->GetAttr<Color>("arrow_color_primary", Color::TRANSPARENT);
        }
    };

    ~SwiperIndicatorTheme() override = default;

    const Color& GetColor() const
    {
        return color_;
    }

    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressedColor() const
    {
        return pressedColor_;
    }

    const Color& GetFocusedColor() const
    {
        return focusedColor_;
    }

    const Dimension& GetSize() const
    {
        return size_;
    }

    const Dimension& GetSelectedSize() const
    {
        return selectedSize_;
    }

    bool GetIndicatorMask() const
    {
        return isHasMask_;
    }

    const Dimension& GetIndicatorPointPadding() const
    {
        return indicatorPointPadding_;
    }

    const TextStyle& GetDigitalIndicatorTextStyle() const
    {
        return digitalIndicatorTextStyle_;
    }

    const Dimension& GetStartEndPadding() const
    {
        return startEndPadding_;
    }

    const Dimension& GetPressPadding() const
    {
        return pressPadding_;
    }

    const Dimension& GetPressPointPadding() const
    {
        return pressPointPadding_;
    }

    const Dimension& GetPressSize() const
    {
        return pressSize_;
    }

    const Dimension& GetHoverSize() const
    {
        return hoverSize_;
    }

    const Dimension& GetHotZoneSize() const
    {
        return hotZoneSize_;
    }

    const Color& GetHotZoneColor() const
    {
        return hotZoneColor_;
    }

    const Color& GetIndicatorTextFocusColor() const
    {
        return indicatorTextFocusColor_;
    }

    bool GetIndicatorDisabled() const
    {
        return isIndicatorDisabled_;
    }

    AnimationCurve GetAnimationCurve() const
    {
        return animationCurve_;
    }

    bool IsAnimationOpacity() const
    {
        return animationOpacity_;
    }

    const Color& GetArrowBoardColorHover() const
    {
        return arrowBoardColorHover_;
    }

    const Color& GetArrowBoardColorClick() const
    {
        return arrowBoardColorClick_;
    }

    const Color& GetArrowColorPrimary() const
    {
        return arrowColorPrimary_;
    }

    const Color& GetArrowColorPrimaryContrary() const
    {
        return arrowColorPrimaryContrary_;
    }

    bool GetIsShowArrowBoard() const
    {
        return isShowArrowBoard_;
    }

    bool GetIsSiderMiddle() const
    {
        return isSiderMiddle_;
    }

    const Dimension& GetSmallArrowBoardSize() const
    {
        return smallArrowBoardSize_;
    }

    const Dimension& GetSmallArrowSize() const
    {
        return smallArrowSize_;
    }
    const Color& GetSmallArrowBoardColor() const
    {
        return smallArrowBoardColor_;
    }

    const Color& GetSmallArrowColor() const
    {
        return smallArrowColor_;
    }
    const Dimension& GetBigArrowBoardSize() const
    {
        return bigArrowBoardSize_;
    }

    const Dimension& GetBigArrowSize() const
    {
        return bigArrowSize_;
    }
    const Color& GetBigArrowBoardColor() const
    {
        return bigArrowBoardColor_;
    }

    const Color& GetBigArrowColor() const
    {
        return bigArrowColor_;
    }

    double GetArrowDisabledAlpha() const
    {
        return arrowDisabledAlpha_;
    }

    const Dimension& GetArrowScale() const
    {
        return arrowScale_;
    }

    const Dimension& GetArrowHorizontalMargin() const
    {
        return arrowHorizontalMargin_;
    }

    const Dimension& GetArrowVerticalMargin() const
    {
        return arrowVerticalMargin_;
    }

protected:
    SwiperIndicatorTheme() = default;

private:
    Color color_;
    Color selectedColor_;
    Color hoverColor_;
    Color pressedColor_;
    Color focusedColor_;
    Dimension size_;
    Dimension selectedSize_;
    Dimension indicatorPointPadding_;
    bool isHasMask_ = false;
    TextStyle digitalIndicatorTextStyle_;
    Dimension startEndPadding_;
    Dimension pressPadding_;
    Dimension pressPointPadding_;
    Dimension pressSize_;
    Dimension hoverSize_;
    Dimension hotZoneSize_;
    Color hotZoneColor_;
    Color indicatorTextFocusColor_;
    bool isIndicatorDisabled_ = false;
    AnimationCurve animationCurve_ = { AnimationCurve::FRICTION };
    bool animationOpacity_ = true;
    Color arrowBoardColorHover_;
    Color arrowBoardColorClick_;
    Color arrowColorPrimary_;
    Color arrowColorPrimaryContrary_;
    bool isShowArrowBoard_ = false;
    bool isSiderMiddle_ = false;
    Dimension smallArrowBoardSize_;
    Dimension smallArrowSize_;
    Color smallArrowBoardColor_;
    Color smallArrowColor_;
    Dimension bigArrowBoardSize_;
    Dimension bigArrowSize_;
    Color bigArrowBoardColor_;
    Color bigArrowColor_;
    double arrowDisabledAlpha_ = 0.4;
    Dimension arrowScale_;
    Dimension arrowHorizontalMargin_;
    Dimension arrowVerticalMargin_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_INDICATOR_THEME_H
