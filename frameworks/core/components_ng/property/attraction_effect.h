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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_ATTRACTION_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_ATTRACTION_EFFECT_H

#include "base/geometry/calc_dimension.h"

namespace OHOS::Ace::NG {
struct AttractionEffect {
    float fraction = 0.0f; // range is 0.0~1.0
    CalcDimension destinationX;
    CalcDimension destinationY;
    bool operator==(const AttractionEffect& other) const
    {
        return NearEqual(fraction, other.fraction) && destinationX == other.destinationX &&
               destinationY == other.destinationY;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_ATTRACTION_EFFECT_H
