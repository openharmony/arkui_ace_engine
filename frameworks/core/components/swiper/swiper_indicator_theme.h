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
namespace {
constexpr double SWIPER_ARROW_ALPHA_DISABLED = 0.4;
constexpr Dimension SWIPER_ARROW_SCALE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_SMALL_ARROW_BACKGROUND_SIZE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_SMALL_ARROW_SIZE = 18.0_vp;
constexpr Dimension SWIPER_ARROW_BIG_ARROW_BACKGROUND_SIZE = 32.0_vp;
constexpr Dimension SWIPER_ARROW_BIG_ARROW_SIZE = 24.0_vp;
constexpr Dimension SWIPER_ARROW_HORIZONTAL_MARGIN_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_ARROW_VERTICAL_MARGIN_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_FOCUSED_BORDER_WIDTH = 2.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_PADDING_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_VERTICAL_PADDING_DEFAULT = 8.0_vp;
constexpr Dimension SWIPER_INDICATOR_DIGIT_HEIGHT = 32.0_vp;
constexpr Dimension SWIPER_INDICATOR_DOT_PADDING_DEFAULT = 12.0_vp;
constexpr Dimension SWIPER_INDICATOR_DOT_ITEM_SPACE = 8.0_vp;
} // namespace

enum class OverlongType {
    NONE = 0,
    LEFT_NORMAL_RIGHT_FADEOUT,
    LEFT_FADEOUT_RIGHT_NORMAL,
    LEFT_FADEOUT_RIGHT_FADEOUT
};

enum class OverlongIndicatorMove {
    NONE = 0,
    MOVE_FORWARD,
    MOVE_BACKWARD
};

enum class GestureState {
    GESTURE_STATE_INIT,
    GESTURE_STATE_NONE,
    GESTURE_STATE_FOLLOW_LEFT,
    GESTURE_STATE_FOLLOW_RIGHT,
    GESTURE_STATE_RELEASE_LEFT,
    GESTURE_STATE_RELEASE_RIGHT
};

enum class TouchBottomTypeLoop {
    TOUCH_BOTTOM_TYPE_LOOP_NONE,
    TOUCH_BOTTOM_TYPE_LOOP_LEFT,
    TOUCH_BOTTOM_TYPE_LOOP_RIGHT,
};
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
            theme->leftSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_left");
            theme->rightSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_right");
            theme->upSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_up");
            theme->downSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_down");
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SwiperIndicatorTheme>& theme) const
        {
            RefPtr<ThemeStyle> swiperPattern = themeConstants->GetPatternByName(THEME_PATTERN_SWIPER);
            if (!swiperPattern) {
                LOGW("find pattern of swiper fail");
                return;
            }
            theme->size_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_size", 0.0_vp);
            theme->selectedSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_selected_size", 0.0_vp);
            theme->isHasMask_ = static_cast<bool>(swiperPattern->GetAttr<double>("swiper_indicator_mask", 0.0));
            theme->indicatorPointPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_point_padding", 0.0_vp);
            theme->startEndPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_start_end_padding", 0.0_vp);
            theme->pressPadding_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_press_padding", 0.0_vp);
            theme->pressPointPadding_ =
                swiperPattern->GetAttr<Dimension>("swiper_indicator_press_point_padding", 0.0_vp);
            theme->pressSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_press_size", 0.0_vp);
            theme->hoverSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_hover_size", 0.0_vp);
            theme->hotZoneSize_ = swiperPattern->GetAttr<Dimension>("swiper_indicator_hotzone_size", 0.0_vp);
            theme->isIndicatorDisabled_ =
                static_cast<bool>(swiperPattern->GetAttr<double>("swiper_indicator_disabled", 0.0));
            theme->animationCurve_ =
                AnimationCurve(static_cast<int32_t>(swiperPattern->GetAttr<double>("swiper_animation_curve", 0.0)));
            theme->animationOpacity_ =
                static_cast<bool>(swiperPattern->GetAttr<double>("swiper_animation_opacity", 0.0));
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
            ParsePattern2(themeConstants, theme, swiperPattern);
        }

        void ParsePattern2(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SwiperIndicatorTheme>& theme,
            const RefPtr<ThemeStyle> swiperPattern) const
        {
            theme->focusedBorderWidth_ = SWIPER_FOCUSED_BORDER_WIDTH;
            theme->hoverArrowBackgroundColor_ =
                swiperPattern->GetAttr<Color>(ARROW_COLOR_BOARDCOLOR_HOVER, Color::TRANSPARENT);
            theme->clickArrowBackgroundColor_ =
                swiperPattern->GetAttr<Color>(ARROW_COLOR_BOARDCOLOR_CLICK, Color::TRANSPARENT);
            theme->arrowColorPrimary_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
            theme->arrowColorPrimaryContrary_ =
                swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY_CONTRARY, Color::TRANSPARENT);
            theme->arrowDisabledAlpha_ =
                swiperPattern->GetAttr<double>(ARROW_DISABLED_ALPHA, SWIPER_ARROW_ALPHA_DISABLED);
            theme->arrowScale_ = SWIPER_ARROW_SCALE;
            theme->arrowHorizontalMargin_ =
                swiperPattern->GetAttr<Dimension>(ARROW_HORIZONTAL_MARGIN, SWIPER_ARROW_HORIZONTAL_MARGIN_DEFAULT);
            theme->arrowVerticalMargin_ =
                swiperPattern->GetAttr<Dimension>(ARROW_VERTICAL_MARGIN, SWIPER_ARROW_VERTICAL_MARGIN_DEFAULT);
            theme->smallArrowBackgroundSize_ = SWIPER_ARROW_SMALL_ARROW_BACKGROUND_SIZE;
            theme->smallArrowSize_ = SWIPER_ARROW_SMALL_ARROW_SIZE;
            theme->smallArrowBackgroundColor_ = Color::TRANSPARENT;
            theme->smallArrowColor_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
            theme->bigArrowBackgroundSize_ = SWIPER_ARROW_BIG_ARROW_BACKGROUND_SIZE;
            theme->bigArrowSize_ = SWIPER_ARROW_BIG_ARROW_SIZE;
            theme->bigArrowBackgroundColor_ =
                swiperPattern->GetAttr<Color>(ARROW_COLOR_COMPONENT_NORMAL, Color::TRANSPARENT);
            theme->bigArrowColor_ = swiperPattern->GetAttr<Color>(ARROW_COLOR_PRIMARY, Color::TRANSPARENT);
            theme->indicatorDigitPadding_ = SWIPER_INDICATOR_DIGIT_PADDING_DEFAULT;
            theme->indicatorDigitVerticalPadding_ = SWIPER_INDICATOR_DIGIT_VERTICAL_PADDING_DEFAULT;
            theme->indicatorDotPadding_ = SWIPER_INDICATOR_DOT_PADDING_DEFAULT;
            theme->indicatorDigitHeight_ = SWIPER_INDICATOR_DIGIT_HEIGHT;
            theme->indicatorDotItemSpace_ = SWIPER_INDICATOR_DOT_ITEM_SPACE;
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

    const Dimension& GetFocusedBorderWidth() const
    {
        return focusedBorderWidth_;
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

    const Color& GetHoverArrowBackgroundColor() const
    {
        return hoverArrowBackgroundColor_;
    }

    const Color& GetClickArrowBackgroundColor() const
    {
        return clickArrowBackgroundColor_;
    }

    const Color& GetArrowColorPrimary() const
    {
        return arrowColorPrimary_;
    }

    const Color& GetArrowColorPrimaryContrary() const
    {
        return arrowColorPrimaryContrary_;
    }

    bool GetIsShowArrowBackground() const
    {
        return isShowArrowBackground_;
    }

    bool GetIsSidebarMiddle() const
    {
        return isSidebarMiddle_;
    }

    const Dimension& GetSmallArrowBackgroundSize() const
    {
        return smallArrowBackgroundSize_;
    }

    const Dimension& GetSmallArrowSize() const
    {
        return smallArrowSize_;
    }
    const Color& GetSmallArrowBackgroundColor() const
    {
        return smallArrowBackgroundColor_;
    }

    const Color& GetSmallArrowColor() const
    {
        return smallArrowColor_;
    }
    const Dimension& GetBigArrowBackgroundSize() const
    {
        return bigArrowBackgroundSize_;
    }

    const Dimension& GetBigArrowSize() const
    {
        return bigArrowSize_;
    }
    const Color& GetBigArrowBackgroundColor() const
    {
        return bigArrowBackgroundColor_;
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

    const Dimension& GetIndicatorDigitPadding() const
    {
        return indicatorDigitPadding_;
    }

    const Dimension& GetIndicatorDotPadding() const
    {
        return indicatorDotPadding_;
    }

    const Dimension& GetIndicatorDigitHeight() const
    {
        return indicatorDigitHeight_;
    }

    const Dimension& GetIndicatorDigitVerticalPadding() const
    {
        return indicatorDigitVerticalPadding_;
    }

    const Dimension& GetIndicatorDotItemSpace() const
    {
        return indicatorDotItemSpace_;
    }

    uint32_t GetLeftSymbolId() const
    {
        return leftSymbolId_;
    }

    uint32_t GetRightSymbolId() const
    {
        return rightSymbolId_;
    }

    uint32_t GetUpSymbolId() const
    {
        return upSymbolId_;
    }

    uint32_t GetDownSymbolId() const
    {
        return downSymbolId_;
    }

protected:
    SwiperIndicatorTheme() = default;

private:
    Color color_;
    Color selectedColor_;
    Color hoverColor_;
    Color pressedColor_;
    Color focusedColor_;
    Dimension focusedBorderWidth_;
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
    Color hoverArrowBackgroundColor_;
    Color clickArrowBackgroundColor_;
    Color arrowColorPrimary_;
    Color arrowColorPrimaryContrary_;
    bool isShowArrowBackground_ = false;
    bool isSidebarMiddle_ = false;
    Dimension smallArrowBackgroundSize_;
    Dimension smallArrowSize_;
    Color smallArrowBackgroundColor_;
    Color smallArrowColor_;
    Dimension bigArrowBackgroundSize_;
    Dimension bigArrowSize_;
    Color bigArrowBackgroundColor_;
    Color bigArrowColor_;
    double arrowDisabledAlpha_ = 0.4;
    Dimension arrowScale_;
    Dimension arrowHorizontalMargin_;
    Dimension arrowVerticalMargin_;
    Dimension indicatorDigitPadding_;
    Dimension indicatorDigitVerticalPadding_;
    Dimension indicatorDotPadding_;
    Dimension indicatorDigitHeight_;
    Dimension indicatorDotItemSpace_;
    uint32_t leftSymbolId_ = 0;
    uint32_t rightSymbolId_ = 0;
    uint32_t upSymbolId_ = 0;
    uint32_t downSymbolId_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_INDICATOR_THEME_H
