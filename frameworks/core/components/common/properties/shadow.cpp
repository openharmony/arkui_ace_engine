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

#include "core/components/common/properties/shadow.h"

#include "core/animation/evaluator.h"
#include "core/components/common/properties/shadow_config.h"

namespace OHOS::Ace {

Shadow Shadow::Blend(const Shadow& to, const Shadow& from, float progress)
{
    auto offset = from.offset_ + (to.offset_ - from.offset_) * progress;
    auto blurRadius = from.blurRadius_ + (to.blurRadius_ - from.blurRadius_) * progress;
    auto spreadRadius = from.spreadRadius_ + (to.spreadRadius_ - from.spreadRadius_) * progress;
    LinearEvaluator<Color> evaluator;
    auto color = evaluator.Evaluate(from.color_, to.color_, progress);
    return Shadow(blurRadius, spreadRadius, offset, color);
}

Shadow Shadow::CreateShadow(ShadowStyle style)
{
    auto colorMode = SystemProperties::GetColorMode();
    if (colorMode == ColorMode::DARK) {
        switch (style) {
            case ShadowStyle::OuterDefaultXS:
                return ShadowConfig::DefaultShadowXSDark;
            case ShadowStyle::OuterDefaultSM:
                return ShadowConfig::DefaultShadowSDark;
            case ShadowStyle::OuterDefaultMD:
                return ShadowConfig::DefaultShadowMDark;
            case ShadowStyle::OuterDefaultLG:
                return ShadowConfig::DefaultShadowLDark;
            case ShadowStyle::OuterFloatingSM:
                return ShadowConfig::FloatingShadowSDark;
            case ShadowStyle::OuterFloatingMD:
                return ShadowConfig::FloatingShadowMDark;
            default:
                return ShadowConfig::NoneShadow;
        }
    }
    switch (style) {
        case ShadowStyle::OuterDefaultXS:
            return ShadowConfig::DefaultShadowXS;
        case ShadowStyle::OuterDefaultSM:
            return ShadowConfig::DefaultShadowS;
        case ShadowStyle::OuterDefaultMD:
            return ShadowConfig::DefaultShadowM;
        case ShadowStyle::OuterDefaultLG:
            return ShadowConfig::DefaultShadowL;
        case ShadowStyle::OuterFloatingSM:
            return ShadowConfig::FloatingShadowS;
        case ShadowStyle::OuterFloatingMD:
            return ShadowConfig::FloatingShadowM;
        default:
            return ShadowConfig::NoneShadow;
    }
    return ShadowConfig::NoneShadow;
}
} // namespace OHOS::Ace