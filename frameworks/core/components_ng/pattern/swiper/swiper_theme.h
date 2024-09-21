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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_VELOCITY_COEFFICIENT = 1.0;
} // namespace

class SwiperTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SwiperTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SwiperTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<SwiperTheme> theme = AceType::Claim(new SwiperTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeStyle, const RefPtr<SwiperTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetPatternByName(THEME_PATTERN_SWIPER);
            if (!pattern) {
                return;
            }
            theme->touchPadVelocityCoefficient_ =
                pattern->GetAttr<double>("swiper_velocity_coefficient_touch_pad", DEFAULT_VELOCITY_COEFFICIENT);
        }
    };

    SwiperTheme() = default;
    ~SwiperTheme() override = default;

    double GetTouchPadVelocityCoefficient() const
    {
        return touchPadVelocityCoefficient_;
    }

private:
    double touchPadVelocityCoefficient_ = DEFAULT_VELOCITY_COEFFICIENT;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_H
