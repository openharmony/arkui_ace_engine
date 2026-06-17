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

#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace {
constexpr float INDICATOR_ZOOM_IN_SCALE = 1.33;
constexpr double INDICATOR_DRAG_MIN_ANGLE = 6.0f;
constexpr double INDICATOR_DRAG_MAX_ANGLE = 10.0f;

class ThemeConstants;
class ThemeStyle;

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

enum class FadeOutState {
    FADE_OUT_NONE,
    FADE_OUT_LEFT,
    FADE_OUT_RIGHT,
    FADE_OUT_BILATERAL
};
class SwiperIndicatorTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SwiperIndicatorTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SwiperIndicatorTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParsePattern(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SwiperIndicatorTheme>& theme) const;

    private:
        void ParsePattern2(
            const RefPtr<SwiperIndicatorTheme>& theme, const RefPtr<ThemeStyle> swiperPattern) const;
#ifdef SUPPORT_DIGITAL_CROWN
        void ParsePattern3(
            const RefPtr<SwiperIndicatorTheme>& theme, const RefPtr<ThemeStyle> swiperPattern) const;
#endif
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

    const Color& GetArcItemColor() const
    {
        return arcItemColor_;
    }

    const Color& GetArcSelectedItemColor() const
    {
        return arcSelectedItemColor_;
    }

    const Color& GetArcContainerColor() const
    {
        return arcContainerColor_;
    }

    NG::Gradient GetArcMaskColor() const
    {
        NG::GradientColor beginGradientColor;
        NG::GradientColor endGradientColor;
        beginGradientColor.SetLinearColor(LinearColor(arcMaskStartColor_));
        beginGradientColor.SetDimension(Dimension(0.0f));
        endGradientColor.SetLinearColor(LinearColor(arcMaskEndColor_));
        endGradientColor.SetDimension(Dimension(1.0f));
        NG::Gradient gradient;
        gradient.AddColor(beginGradientColor);
        gradient.AddColor(endGradientColor);

        return gradient;
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

    const Color& GetFocusedBgColor() const
    {
        return focusedBgColor_;
    }

    const Color& GetFocusUnSelectedColor() const
    {
        return unSelectedColor_;
    }

    const Color& GetFocusedSelectedColor() const
    {
        return focusedSelectedColor_;
    }

    float GetIndicatorScale() const
    {
        return scaleSwiper_;
    }

    const Dimension& GetIndicatorPaddingDot() const
    {
        return indicatorPaddingDot_;
    }

    const Dimension& GetIndicatorBgHeight() const
    {
        return indicatorBgHeight_;
    }

    const Dimension& GetIndicatorFocusedPadding() const
    {
        return indicatorFocusedPadding_;
    }

    bool GetClipEdge() const
    {
        return clipToBounds_;
    }

    int GetFocusStyleType() const
    {
        return focusStyleType_;
    }

#ifdef SUPPORT_DIGITAL_CROWN
    double GetSlowVelocityThreshold() const
    {
        return slowVelocityThreshold_;
    }

    double GetMediumVelocityThreshold() const
    {
        return mediumVelocityThreshold_;
    }

    double GetFastVelocityThreshold() const
    {
        return fastVelocityThreshold_;
    }

    double GetDisplayControlRatioVerySlow() const
    {
        return displayControlRatioVerySlow_;
    }

    double GetDisplayControlRatioSlow() const
    {
        return displayControlRatioSlow_;
    }

    double GetDisplayControlRatioMedium() const
    {
        return displayControlRatioMedium_;
    }

    double GetDisplayControlRatioFast() const
    {
        return displayControlRatioFast_;
    }

    double GetCrownSensitivityLow() const
    {
        return crownSensitivityLow_;
    }

    double GetCrownSensitivityMedium() const
    {
        return crownSensitivityMedium_;
    }

    double GetCrownSensitivityHigh() const
    {
        return crownSensitivityHigh_;
    }

    double GetSpringVelocityThreshold() const
    {
        return springVelocityThreshold_;
    }

    double GetCrownTranslocationRatio() const
    {
        return crownTranslocationRatio_;
    }
#endif

    double GetIndicatorDragMinAngle() const
    {
        return indicatorDragMinAngle_;
    }

    double GetIndicatorDragMaxAngle() const
    {
        return indicatorDragMaxAngle_;
    }

    const std::string& GetPreAccessibilityText() const
    {
        return preAccessibilityText_;
    }

    const std::string& GetNextAccessibilityText() const
    {
        return nextAccessibilityText_;
    }
protected:
    SwiperIndicatorTheme() = default;

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
    Color arcItemColor_;
    Color arcSelectedItemColor_;
    Color arcContainerColor_;
    Color arcMaskStartColor_;
    Color arcMaskEndColor_;
    uint32_t leftSymbolId_ = 0;
    uint32_t rightSymbolId_ = 0;
    uint32_t upSymbolId_ = 0;
    uint32_t downSymbolId_ = 0;
    Color unSelectedColor_;
    Color focusedBgColor_;
    Color focusedSelectedColor_;
    Dimension indicatorBgHeight_;
    float scaleSwiper_ = INDICATOR_ZOOM_IN_SCALE;
    Dimension indicatorPaddingDot_;
    Dimension indicatorFocusedPadding_;
    bool clipToBounds_ = true;
    int focusStyleType_ = 0;
#ifdef SUPPORT_DIGITAL_CROWN
    double slowVelocityThreshold_ = 0.0f;
    double mediumVelocityThreshold_ = 0.0f;
    double fastVelocityThreshold_ = 0.0f;
    double displayControlRatioVerySlow_ = 0.0f;
    double displayControlRatioSlow_ = 0.0f;
    double displayControlRatioMedium_ = 0.0f;
    double displayControlRatioFast_ = 0.0f;
    double crownSensitivityLow_ = 0.0f;
    double crownSensitivityMedium_ = 0.0f;
    double crownSensitivityHigh_ = 0.0f;
    double springVelocityThreshold_ = 0.0f;
    double crownTranslocationRatio_ = 0.0f;
#endif
    double indicatorDragMinAngle_ = INDICATOR_DRAG_MIN_ANGLE;
    double indicatorDragMaxAngle_ = INDICATOR_DRAG_MAX_ANGLE;
    std::string preAccessibilityText_;
    std::string nextAccessibilityText_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_SWIPER_INDICATOR_THEME_H
