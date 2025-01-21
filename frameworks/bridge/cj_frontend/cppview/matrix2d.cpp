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

#include "bridge/cj_frontend/cppview/matrix2d.h"

#include "core/components_ng/render/adapter/matrix2d.h"

using namespace OHOS::Ace;

namespace OHOS::Ace::Framework {

NativeMatrix2d::NativeMatrix2d() : FFIData() {}

NativeMatrix2d::NativeMatrix2d(const int32_t unit) : FFIData()
{
    unit_ = static_cast<CanvasUnit>(unit);
}

NativeMatrix2d::~NativeMatrix2d()
{
    LOGI("Native Matrix2d Destroyed: %{public}" PRId64, GetID());
}

void NativeMatrix2d::Identity()
{
    NG::Matrix2D::Identity(transform_);
}

void NativeMatrix2d::Invert()
{
    bool retValue = NG::Matrix2D::Invert(transform_);
    if (!retValue) {
        transform_.scaleX = 0.0;
        transform_.scaleY = 0.0;
        transform_.skewX = 0.0;
        transform_.skewY = 0.0;
        transform_.translateX = 0.0;
        transform_.translateY = 0.0;
    }
}

void NativeMatrix2d::Rotate(double degree, double rx, double ry)
{
    double density = GetDensity();
    rx *= density;
    ry *= density;
    NG::Matrix2D::Rotate(transform_, degree, rx, ry);
}

void NativeMatrix2d::Translate(double tx, double ty)
{
    double density = GetDensity();
    tx *= density;
    ty *= density;
    NG::Matrix2D::Translate(transform_, tx, ty);
}

void NativeMatrix2d::Scale(double sx, double sy)
{
    NG::Matrix2D::Scale(transform_, sx, sy);
}

} // namespace OHOS::Ace::Framework