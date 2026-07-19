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
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
NG::LineModelNG* GetLineModel()
{
    static NG::LineModelNG* cachedModel = nullptr;
    if (cachedModel == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Line");
        if (module == nullptr) {
            LOGF_ABORT("Can't find line dynamic module");
        }
        cachedModel = reinterpret_cast<NG::LineModelNG*>(module->GetModel());
    }
    return cachedModel;
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkLineCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    GetLineModel()->Create();
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
    GetLineModel()->StartPoint(startPoint);
}

void FfiOHOSAceFrameworkLineSetEnd(double x, double y)
{
    ShapePoint endPoint;
    endPoint.first = Dimension(x, DimensionUnit::VP);
    endPoint.second = Dimension(y, DimensionUnit::VP);
    GetLineModel()->EndPoint(endPoint);
}
}
