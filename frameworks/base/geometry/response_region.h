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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_RESPONSE_REGION_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_RESPONSE_REGION_H

#include <cmath>
#include <limits>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/dimension_offset.h"
#include "base/json/json_util.h"
#include "core/components_ng/event/event_constants.h"

namespace OHOS::Ace {

class ResponseRegion {
public:
    ResponseRegion() = default;
    ~ResponseRegion() = default;

    ResponseRegion(const NG::ResponseRegionSupportedTool& tool, const CalcDimension& x,
        const CalcDimension& y, const CalcDimension& width, const CalcDimension& height);

    ResponseRegion(const ResponseRegion& responseRegion);

    const NG::ResponseRegionSupportedTool& GetTool() const;

    const CalcDimension& GetWidth() const;

    const CalcDimension& GetHeight() const;

    const CalcDimension& GetX() const;

    const CalcDimension& GetY() const;

    void SetWidth(const CalcDimension& width);

    void SetHeight(const CalcDimension& height);

    void SetX(const CalcDimension& x);

    void SetY(const CalcDimension& y);

    void SetTool(const NG::ResponseRegionSupportedTool& tool);

    ResponseRegion& operator=(const ResponseRegion& responseRegion);

private:
    NG::ResponseRegionSupportedTool tool_ = NG::ResponseRegionSupportedTool::ALL;
    CalcDimension width_ = 0.0_vp;
    CalcDimension height_ = 0.0_vp;
    CalcDimension x_ = 0.0_vp;
    CalcDimension y_ = 0.0_vp;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_RESPONSE_REGION_H
