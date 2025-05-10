/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {

class LinearIndicatorTheme : public virtual Theme {
    DECLARE_ACE_TYPE(LinearIndicatorTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<LinearIndicatorTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<LinearIndicatorTheme> theme = AceType::MakeRefPtr<LinearIndicatorTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeStyle, const RefPtr<LinearIndicatorTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetPatternByName(THEME_PATTERN_LINEAR_INDICATOR);
            if (!pattern) {
                return;
            }
            theme->trackBackgroundColor_ = pattern->GetAttr<Color>("comp_background_tertiary", Color(0X0C182431));
            theme->trackColor_ = pattern->GetAttr<Color>("comp_background_emphasize", Color(0xFF007DFF));
            theme->paddingLeft_ = pattern->GetAttr<Dimension>("padding_level8", 16.0_vp);
            theme->paddingRight_ = pattern->GetAttr<Dimension>("padding_level8", 16.0_vp);
        }
    };
    LinearIndicatorTheme() = default;
    ~LinearIndicatorTheme() override = default;

    const Color& GetTrackBackgroundColor() const
    {
        return trackBackgroundColor_;
    }

    const Color& GetTrackColor() const
    {
        return trackColor_;
    }

    const Dimension& GetPaddingLeft() const
    {
        return paddingLeft_;
    }

    const Dimension& GetPaddingRight() const
    {
        return paddingRight_;
    }

    const Dimension& GetPaddingTop() const
    {
        return paddingTop_;
    }

    const Dimension& GetPaddingBottom() const
    {
        return paddingBottom_;
    }

    const Dimension& GetDefaultSpace() const
    {
        return defaultSpace_;
    }

    int GetDefaultProgressCount() const
    {
        return defaultProgressCount_;
    }

    int GetDefaultProgressMin() const
    {
        return defaultProgressMin_;
    }

    bool GetDefaultLoop() const
    {
        return defaultLoop_;
    }

    const Dimension& GetDefaultStrokeWidth() const
    {
        return defaultStrokeWidth_;
    }

    const Dimension& GetDefaultStrokeWidthMin() const
    {
        return defaultStrokeWidthMin_;
    }

    const Dimension& GetDefaultStrokeRadius() const
    {
        return defaultStrokeRadius_;
    }

    int GetDefaultIntervalTime() const
    {
        return defaultIntervalTime_;
    }

    int GetDefaultDurationTime() const
    {
        return defaultDurationTime_;
    }

    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }

private:
    Color trackBackgroundColor_ = Color(0X0C182431);
    Color trackColor_ = Color(0xFF007DFF);
    Dimension paddingLeft_ = 16.0_vp;
    Dimension paddingRight_ = 16.0_vp;
    Dimension paddingTop_ = 0.0_vp;
    Dimension paddingBottom_ = 0.0_vp;
    Dimension defaultSpace_ = 4.0_vp;
    int32_t defaultProgressCount_ = 5;
    int32_t defaultProgressMin_ = 2;
    bool defaultLoop_ = true;
    Dimension defaultStrokeWidth_ = 2.0_vp;
    Dimension defaultStrokeWidthMin_ = 0.0_vp;
    Dimension defaultStrokeRadius_ = 1.0_vp;
    int32_t defaultIntervalTime_ = 0;
    int32_t defaultDurationTime_ = 4000;

    Dimension defaultHeight_ = 24.0_vp;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_THEME_H
