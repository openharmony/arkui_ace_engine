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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_line_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkLineCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    LineModel::GetInstance()->Create();
    if (width > 0.0) {
        FfiOHOSAceFrameworkShapeSetWidth(width, widthUnit);
    }
    if (height > 0.0) {
        FfiOHOSAceFrameworkShapeSetHeight(height, heightUnit);
    }
}

void FfiOHOSAceFrameworkLineSetStart(double x, double y)
{
    ShapePoint startPoint;
    startPoint.first = Dimension(x, DimensionUnit::VP);
    startPoint.second = Dimension(y, DimensionUnit::VP);
    LineModel::GetInstance()->StartPoint(startPoint);
}

void FfiOHOSAceFrameworkLineSetEnd(double x, double y)
{
    ShapePoint endPoint;
    endPoint.first = Dimension(x, DimensionUnit::VP);
    endPoint.second = Dimension(y, DimensionUnit::VP);
    LineModel::GetInstance()->EndPoint(endPoint);
}
}
