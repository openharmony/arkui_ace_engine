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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_circle_ffi.h"

#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"

extern "C" {
void FfiOHOSAceFrameworkCircleCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    OHOS::Ace::CircleModel::GetInstance()->Create();
    if (width > 0.0) {
        FfiOHOSAceFrameworkShapeSetWidth(width, widthUnit);
    }
    if (height > 0.0) {
        FfiOHOSAceFrameworkShapeSetHeight(height, heightUnit);
    }
}

int64_t FfiOHOSAceFrameworkCircleInsCreate(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    OHOS::Ace::Dimension dWidth(width, static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    OHOS::Ace::Dimension dHeight(height, static_cast<OHOS::Ace::DimensionUnit>(heightUnit));
    auto ret_ = OHOS::FFI::FFIData::Create<OHOS::Ace::Framework::NativeCircle>(dWidth, dHeight);
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}
}
