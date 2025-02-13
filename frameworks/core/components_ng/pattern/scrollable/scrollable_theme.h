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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLLABLE_SCROLLABLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLLABLE_SCROLLABLE_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {

class ScrollableTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ScrollableTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ScrollableTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ScrollableTheme> theme = AceType::Claim(new ScrollableTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ScrollableTheme>& theme) const
        {
            if (!theme) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_SCROLLABLE);
            if (!pattern) {
                return;
            }
            theme->friction_ = pattern->GetAttr<double>("scroll_able_friction", 0.75f);
            theme->flingVelocityScale_ = pattern->GetAttr<double>("scroll_able_fling_velocity_scale", 1.5f);
            theme->springVelocityScale_ = pattern->GetAttr<double>("scroll_able_spring_velocity_scale", 1.5f);
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
                theme->ratio_ = pattern->GetAttr<double>("scroll_able_over_edge_following_ratio_api_sixteen", 5.0f);
            } else {
                theme->ratio_ = pattern->GetAttr<double>("scroll_able_over_edge_following_ratio", 1.848f);
            }
            theme->springResponse_ = pattern->GetAttr<double>("scroll_able_spring_response", 0.417f);
            theme->touchPadVelocityScaleRate_ =
                pattern->GetAttr<double>("scroll_able_touch_pad_velocity_scale_rate", 1.0f);
        }
    };

    ~ScrollableTheme() override = default;

    float GetFriction() const
    {
        return friction_;
    }

    float GetFlingVelocityScale() const
    {
        return flingVelocityScale_;
    }

    float GetSpringVelocityScale() const
    {
        return springVelocityScale_;
    }

    float GetRatio() const
    {
        return ratio_;
    }

    float GetSpringResponse() const
    {
        return springResponse_;
    }

    float GetTouchPadVelocityScaleRate() const
    {
        return touchPadVelocityScaleRate_;
    }

protected:
    ScrollableTheme() = default;

private:
    float friction_ = 0.75f;
    float flingVelocityScale_ = 1.5f;
    float springVelocityScale_ = 1.5f;
    float ratio_ = 1.848f;
    float springResponse_ = 0.416f;
    float touchPadVelocityScaleRate_ = 1.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLLABLE_SCROLLABLE_THEME_H
