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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_polyline_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const int SIZE_CHECK = 2;
}

extern "C" {
void FfiOHOSAceFrameworkPolylineCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    PolygonModel::GetInstance()->Create(false);
    if (width > 0.0) {
        FfiOHOSAceFrameworkShapeSetWidth(width, widthUnit);
    }
    if (height > 0.0) {
        FfiOHOSAceFrameworkShapeSetHeight(height, heightUnit);
    }
}

void FfiOHOSAceFrameworkPolylineSetPoints(VectorFloat64Ptr xPointVec, VectorFloat64Ptr yPointVec)
{
    ShapePoint point;
    ShapePoints points;
    const auto& xPointVector = *reinterpret_cast<std::vector<double>*>(xPointVec);
    const auto& yPointVector = *reinterpret_cast<std::vector<double>*>(yPointVec);
    if (xPointVector.size() < SIZE_CHECK || xPointVector.size() != yPointVector.size()) {
        LOGE("Polyline set points error: params requires at least 2 points or point data loss");
        return;
    }
    for (size_t i = 0; i < xPointVector.size(); ++i) {
        point.first = Dimension(xPointVector[i], DimensionUnit::VP);
        point.second = Dimension(yPointVector[i], DimensionUnit::VP);
        points.push_back(point);
    }
    PolygonModel::GetInstance()->SetPoints(points);
}
}
