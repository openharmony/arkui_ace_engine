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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_SWIPER_MODIFIER_TEST_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_UNITTEST_CAPI_MODIFIERS_SWIPER_MODIFIER_TEST_H

#include "arkoala_api.h"
#include "arkoala_api_generated.h"

#include "core/components/badge/badge_theme.h"

namespace OHOS::Ace::NG {
typedef struct Position {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
} Position;

namespace {
Ark_Position ToArkPos(int32_t value);
Ark_Position ToArkPos(double v, DimensionUnit unit);
Ark_Length ToArkLength(int32_t value);
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {

inline void AssignArkValue(Ark_FontWeight& dst, const FontWeight& src)
{
    switch (src) {
        case FontWeight::W100:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER;
            break;
        case FontWeight::W400:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL;
            break;
        case FontWeight::W700:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLD;
            break;
        case FontWeight::W900:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER;
            break;
        case FontWeight::LIGHTER:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_LIGHTER;
            break;
        case FontWeight::NORMAL:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_NORMAL;
            break;
        case FontWeight::REGULAR:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_REGULAR;
            break;
        case FontWeight::MEDIUM:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_MEDIUM;
            break;
        case FontWeight::BOLD:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLD;
            break;
        case FontWeight::BOLDER:
            dst = Ark_FontWeight::ARK_FONT_WEIGHT_BOLDER;
            break;
        default:
            dst = static_cast<Ark_FontWeight>(-1);
            LOGE("Unexpected enum value in Ark_FontWeight: %{public}d", src);
    }
}

inline void AssignArkValue(Ark_BadgePosition& dst, const BadgePosition& src)
{
    switch (src) {
        case BadgePosition::RIGHT_TOP:
            dst = ARK_BADGE_POSITION_RIGHT_TOP;
            break;
        case BadgePosition::RIGHT:
            dst = ARK_BADGE_POSITION_RIGHT;
            break;
        case BadgePosition::LEFT:
            dst = ARK_BADGE_POSITION_LEFT;
            break;
        default:
            dst = static_cast<Ark_BadgePosition>(-1);
            LOGE("Unexpected enum value in BadgePosition: %{public}d", src);
    }
}

inline void AssignArkValue(Ark_Position& dst, const Position& src);

} // namespace OHOS::Ace::NG::Converter
#endif