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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_THEME_H

#include "base/geometry/dimension.h"
#include "base/resource/internal_resource.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"

namespace OHOS::Ace {
class ThemeConstants;

constexpr Color DEFAULT_UNCHECK_BORDER_COLOR = Color(0x4B181819);
class CheckableTheme : public virtual Theme {
    DECLARE_ACE_TYPE(CheckableTheme, Theme);

public:
    ~CheckableTheme() override = default;

    const Color& GetPointColor() const
    {
        return pointColor_;
    }
    const Color& GetActiveColor() const
    {
        return activeColor_;
    }
    const Color& GetInactiveColor() const
    {
        return inactiveColor_;
    }
    const Color& GetFocusColor() const
    {
        return focusColor_;
    }
    const Color& GetFocusBoardColor() const
    {
        return focusBoardColor_;
    }
    const Color& GetBorderFocusedColor() const
    {
        return borderFocusedColor_;
    }
    const Color& GetFocusedBGColorUnselected() const
    {
        return focusedBGColorUnselected_;
    }
    const Dimension& GetWidth() const
    {
        return width_;
    }
    const Dimension& GetHeight() const
    {
        return height_;
    }
    const Dimension& GetHotZoneHorizontalPadding() const
    {
        return hotZoneHorizontalPadding_;
    }
    const Dimension& GetHotZoneVerticalPadding() const
    {
        return hotZoneVerticalPadding_;
    }
    double GetAspectRatio() const
    {
        return aspectRatio_;
    }
    const Dimension& GetDefaultWidth() const
    {
        return defaultWidth_;
    }
    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }
    double GetRadioInnerSizeRatio() const
    {
        return radioInnerSizeRatio_;
    }
    bool GetNeedFocus() const
    {
        return needFocus_;
    }
    bool IsBackgroundSolid() const
    {
        return backgroundSolid_;
    }
    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    void SetHoverColor(const Color& hoverColor)
    {
        hoverColor_ = hoverColor;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    void SetClickEffectColor(const Color& clickEffectColor)
    {
        clickEffectColor_ = clickEffectColor;
    }

    const Color& GetClickEffectColor() const
    {
        return clickEffectColor_;
    }

    const Color& GetInactivePointColor() const
    {
        return inactivePointColor_;
    }

    const Color& GetShadowColor() const
    {
        return shadowColor_;
    }

    const Dimension& GetShadowWidth() const
    {
        return shadowWidth_;
    }

    const Dimension& GetHoverRadius() const
    {
        return hoverRadius_;
    }

    const Dimension& GetDefaultPaddingSize() const
    {
        return defaultPaddingSize_;
    }

    const Dimension& GetFocusRadius() const
    {
        return focusRadius_;
    }

    const Dimension& GetFocusPaintPadding() const
    {
        return focusPaintPadding_;
    }

    const Dimension& GetFocusBoardSize() const
    {
        return focusBoardSize_;
    }

    const Dimension& GetRoundFocusBoardSize() const
    {
        return roundFocusBoardSize_;
    }

    const Dimension& GetDefaultRoundPaddingSize() const
    {
        return defaultRoundPaddingSize_;
    }

    double GetHoverDuration() const
    {
        return hoverDuration_;
    }

    double GetHoverToTouchDuration() const
    {
        return hoverToTouchDuration_;
    }

    double GetTouchDuration() const
    {
        return touchDuration_;
    }
    const InternalResource::ResourceId& GetTickResourceId() const
    {
        return tickResourceId_;
    }
    const InternalResource::ResourceId& GetDotResourceId() const
    {
        return dotResourceId_;
    }

    const Color& GetFocusLineColor() const
    {
        return focusLineColor_;
    }

    const Color& GetFocusedBgColor() const
    {
        return focusedBgColor_;
    }

    const Dimension& GetSizeFocusBg() const
    {
        return sizeFocusBg_;
    }

    const Dimension& GetSizeHoverBg() const
    {
        return sizeHoverBg_;
    }

    const Color& GetFocusedRingUnchecked() const
    {
        return focusedRingUnchecked_;
    }

    const Color& GetFocusedBgUnchecked() const
    {
        return focusedBgUnchecked_;
    }

    const Dimension& GetHotZoneHorizontalSize() const
    {
        return hotZoneHorizontalSize_;
    }

    const Dimension& GetHotZoneVerticalSize() const
    {
        return hotZoneVerticalSize_;
    }
    const Color& GetUnCheckBorderColor() const
    {
        return uncheckBorderColor_;
    }
protected:
    CheckableTheme() = default;

    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    Color inactivePointColor_;
    Color focusColor_;
    Color hoverColor_;
    Color clickEffectColor_;
    Color shadowColor_;
    Color focusBoardColor_;
    Color borderFocusedColor_;
    Color focusedBGColorUnselected_;
    Color focusLineColor_;
    Color focusedRingUnchecked_;
    Color focusedBgUnchecked_;
    Color focusedBgColor_;
    Dimension sizeFocusBg_;
    Dimension sizeHoverBg_;
    Dimension width_;
    Dimension height_;
    Dimension hotZoneHorizontalPadding_;
    Dimension hotZoneVerticalPadding_;
    Dimension defaultWidth_;
    Dimension defaultHeight_;
    Dimension borderWidth_;
    Dimension shadowWidth_;
    Dimension hoverRadius_;
    Dimension defaultPaddingSize_;
    Dimension defaultRoundPaddingSize_;
    Dimension focusRadius_;
    Dimension focusPaintPadding_;
    Dimension focusBoardSize_;
    Dimension roundFocusBoardSize_;
    double hoverDuration_ = 0.0f;
    double hoverToTouchDuration_ = 0.0f;
    double touchDuration_ = 0.0f;
    double aspectRatio_ = 1.0;
    double radioInnerSizeRatio_ = 0.5;
    bool needFocus_ = true;
    bool backgroundSolid_ = true;
    const float ratio_ = 1.8f;
    InternalResource::ResourceId tickResourceId_ = InternalResource::ResourceId::RADIO_TICK_SVG;
    InternalResource::ResourceId dotResourceId_ = InternalResource::ResourceId::RADIO_DOT_SVG;
    Dimension hotZoneHorizontalSize_;
    Dimension hotZoneVerticalSize_;
    Color uncheckBorderColor_;
};

class CheckboxTheme : public CheckableTheme {
    DECLARE_ACE_TYPE(CheckboxTheme, CheckableTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<CheckboxTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CheckboxTheme>& theme) const;

        void SetCheckboxSize(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CheckboxTheme>& theme) const;

        void SetCheckboxFocus(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<CheckboxTheme>& theme) const;
    };

    const Dimension& GetHoverPaddingSize() const
    {
        return hoverPaddingSize_;
    }

    const Dimension& GetBorderRadius() const
    {
        return borderRadius_;
    }

    const Dimension& GetWhiteBorderRadius() const
    {
        return whiteBorderRadius_;
    }

    const Dimension& GetCheckStroke() const
    {
        return checkStroke_;
    }

    double GetColorAnimationDuration() const
    {
        return colorAnimationDuration_;
    }

    bool IsCircleDial() const
    {
        return showCircleDial_;
    }

private:
    Dimension borderRadius_;
    Dimension whiteBorderRadius_;
    Dimension checkStroke_;
    Dimension hoverPaddingSize_;
    double colorAnimationDuration_ = 0.0;
    bool showCircleDial_ = false;
};

class SwitchTheme : public CheckableTheme {
    DECLARE_ACE_TYPE(SwitchTheme, CheckableTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SwitchTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParseSubStylePattern(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<SwitchTheme>& theme) const;
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<SwitchTheme>& theme) const;
    };

    const Color& GetPointColorUnselectedFocus() const
    {
        return focusedPointColorUnselected_;
    }

    const Color& GetPointColorUnchecked() const
    {
        return pointColorUnchecked_;
    }

    const Dimension& GetFocusBoardWidth() const
    {
        return focusBoardWidth_;
    }

    const Dimension& GetFocusBoardHeight() const
    {
        return focusBoardHeight_;
    }

    const Dimension& GetFocusBoardRadius() const
    {
        return focusBoardRadius_;
    }

    float GetRatio() const
    {
        return ratio_;
    }

    double GetColorAnimationDuration() const
    {
        return colorAnimationDuration_;
    }

    double GetPointAnimationDuration() const
    {
        return pointAnimationDuration_;
    }

    const Color& GetInteractiveHoverColor() const
    {
        return interactiveHoverColor_;
    }

    const Color& GetInteractivePressedColor() const
    {
        return interactivePressedColor_;
    }

    bool GetSwitchUseDiffPointColor() const
    {
        return isUseDiffPointColor_;
    }

    const Dimension& GetSwitchFocuPadding() const
    {
        return focusPadding_;
    }

    const std::string& GetSwitchOnText() const
    {
        return switchOnText_;
    }

    const std::string& GetSwitchOffText() const
    {
        return switchOffText_;
    }

private:
    double colorAnimationDuration_ = 0.0;
    double pointAnimationDuration_ = 0.0;
    Color interactiveHoverColor_;
    Color interactivePressedColor_;
    bool isUseDiffPointColor_ = false;
    Color focusedPointColorUnselected_;
    Color pointColorUnchecked_;
    Dimension focusBoardWidth_;
    Dimension focusBoardHeight_;
    Dimension focusBoardRadius_;
    Dimension focusPadding_;
    std::string switchOnText_;
    std::string switchOffText_;
};

class RadioTheme : public CheckableTheme {
    DECLARE_ACE_TYPE(RadioTheme, CheckableTheme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<RadioTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParseUncheckBorderColor(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RadioTheme>& theme) const;

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RadioTheme>& theme) const;

        void SetRadioSize(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RadioTheme>& theme) const;
        void ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RadioTheme>& theme) const;
    };

    bool IsCircleDial() const
    {
        return showCircleDial_;
    }

private:
    bool showCircleDial_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_CHECKABLE_THEME_H
