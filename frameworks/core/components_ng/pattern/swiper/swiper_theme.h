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

namespace OHOS::Ace {
class ThemeConstants;
}

namespace OHOS::Ace::NG {

class SwiperTheme : public virtual Theme {
    DECLARE_ACE_TYPE(SwiperTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<SwiperTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeStyle, const RefPtr<SwiperTheme>& theme) const;
    };

    SwiperTheme() = default;
    ~SwiperTheme() override = default;

    double GetTouchPadVelocityCoefficient() const
    {
        return touchPadVelocityCoefficient_;
    }

    double GetAnimationCurveStiffness() const
    {
        return animationCurveStiffness_;
    }

    double GetAnimationCurveDamping() const
    {
        return animationCurveDamping_;
    }

private:
    double touchPadVelocityCoefficient_ = 1.0;
    double animationCurveStiffness_ = 328.0;
    double animationCurveDamping_ = 34.0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_THEME_H
