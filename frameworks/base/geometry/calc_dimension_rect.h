/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_CALC_DIMENSION_RECT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_CALC_DIMENSION_RECT_H

#include <cmath>
#include <limits>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension_rect.h"

namespace OHOS::Ace {

class CalcDimensionRect {
public:
    CalcDimensionRect() = default;
    ~CalcDimensionRect() = default;

    CalcDimensionRect(
        const CalcDimension& width, const CalcDimension& height, const CalcDimension& x, const CalcDimension& y);

    CalcDimensionRect(const DimensionRect& dimensionRect);

    const CalcDimension& GetWidth() const;

    const CalcDimension& GetHeight() const;

    const CalcDimension& GetX() const;

    const CalcDimension& GetY() const;

    void SetWidth(const CalcDimension& width);

    void SetHeight(const CalcDimension& height);

    void SetX(const CalcDimension& x);

    void SetY(const CalcDimension& y);

    std::string ToString() const;

    std::string ToJsonString() const;

    CalcDimensionRect& operator=(const DimensionRect& newDimension);

private:
    CalcDimension width_ = 0.0_vp;
    CalcDimension height_ = 0.0_vp;
    CalcDimension x_ = 0.0_vp;
    CalcDimension y_ = 0.0_vp;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_CALC_DIMENSION_RECT_H
