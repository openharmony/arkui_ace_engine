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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EDGELIGHT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EDGELIGHT_PROPERTY_H

#include "base/geometry/calc_dimension.h"

namespace OHOS::Ace::NG {

enum class EdgeLightPosition {
    TOP_LEFT = 0,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

struct EdgeLightParam {
    EdgeLightPosition edgeLightPosition;
    CalcDimension length;
    float intensity;
    CalcDimension thickness;
    Color color;

    bool operator==(const EdgeLightParam &param) const
    {
        return length == param.length &&
               NearEqual(intensity, param.intensity) &&
               thickness == param.thickness &&
               edgeLightPosition == param.edgeLightPosition &&
               color == param.color;
    }
};
} // namespace OHOS::Ace::NG

#endif