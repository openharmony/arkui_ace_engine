/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_theme.h"

#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr double DEFAULT_VELOCITY_COEFFICIENT = 1.0;
constexpr float DEFAULT_STIFFNESS = 328.0f;
constexpr float DEFAULT_DAMPING = 34.0f;
} // namespace

RefPtr<SwiperTheme> SwiperTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<SwiperTheme> theme = AceType::MakeRefPtr<SwiperTheme>();
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void SwiperTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeStyle, const RefPtr<SwiperTheme>& theme) const
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
    theme->animationCurveStiffness_ =
        pattern->GetAttr<double>("swiper_fling_animation_stiffness", DEFAULT_STIFFNESS);
    theme->animationCurveDamping_ =
        pattern->GetAttr<double>("swiper_fling_animation_damping", DEFAULT_DAMPING);
}

} // namespace OHOS::Ace::NG
