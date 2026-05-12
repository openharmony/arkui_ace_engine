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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"

namespace OHOS::Ace {

class ThemeConstants;

/**
 * ToggleTheme defines color and styles of ToggleComponent. ToggleTheme should be built
 * using ToggleTheme::Builder.
 */
class ToggleTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ToggleTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ToggleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ToggleTheme>& theme) const;
    };

    ~ToggleTheme() override = default;

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetCheckedColor() const
    {
        return checkedColor_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Color& GetPressedBlendColor() const
    {
        return pressedBlendColor_;
    }

    double GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

    const Dimension& GetTextMargin() const
    {
        return textMargin_;
    }

    const Dimension& GetButtonMargin() const
    {
        return buttonMargin_;
    }

    const Dimension& GetButtonHeight() const
    {
        return buttonHeight_;
    }

    const Dimension& GetButtonRadius() const
    {
        return buttonRadius_;
    }

    const Dimension& GetTextFontSize() const
    {
        return textFontSize_;
    }

    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    const Dimension& GetBorderWidthUnchecked() const
    {
        return borderWidthUnchecked_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetTextColorFocus() const
    {
        return textColorFocus_;
    }

    const Color& GetBorderColorChecked() const
    {
        return borderColorChecked_;
    }

    const Color& GetBorderColorUnchecked() const
    {
        return borderColorUnchecked_;
    }

    const Color& GetBackgroundColorFocusChecked() const
    {
        return bgColorFocusChecked_;
    }

    const Color& GetBackgroundColorFocusUnchecked() const
    {
        return bgColorFocusUnchecked_;
    }

    uint32_t GetShadowNormal() const
    {
        return shadowNormal_;
    }

    uint32_t GetShadowFocus() const
    {
        return shadowFocus_;
    }

    float GetScaleHoverOrFocus() const
    {
        return scaleHoverOrFocus_;
    }

protected:
    ToggleTheme() = default;
    Color backgroundColor_;
    Color checkedColor_;

private:
    Color pressedBlendColor_;
    TextStyle textStyle_;
    Dimension height_;
    Edge padding_;
    double disabledAlpha_ { 1.0 };
    Dimension textMargin_;
    Dimension buttonMargin_;
    Dimension buttonHeight_;
    Dimension buttonRadius_;
    Dimension textFontSize_;
    Dimension borderWidth_;
    Dimension borderWidthUnchecked_;
    Color textColor_;
    Color borderColorUnchecked_;
    Color borderColorChecked_;
    Color bgColorFocusChecked_;
    Color bgColorFocusUnchecked_;
    Color textColorFocus_;
    uint32_t shadowNormal_;
    uint32_t shadowFocus_;
    float scaleHoverOrFocus_;
    static constexpr double SHADOW_NONE = 6.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H
