/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/matrix2d.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {
const auto TRANSFORM_UNITY_VALUE = 1.00;
} // namespace

bool Matrix2D::Invert(TransformParam& param)
{
    if (NearZero(param.scaleX) && NearZero(param.scaleY) && NearZero(param.skewX) && NearZero(param.skewY) &&
        NearZero(param.translateX) && NearZero(param.translateY)) {
        return false;
    }

    auto tmp = param.scaleX;
    param.scaleX = param.scaleY;
    param.scaleY = tmp;
    tmp = param.skewX;
    param.skewX = param.skewY;
    param.skewY = tmp;
    tmp = param.translateX;
    param.translateX = param.translateY;
    param.translateY = tmp;
    return true;
}

void Matrix2D::Identity(TransformParam& param)
{
    param.scaleX = TRANSFORM_UNITY_VALUE;
    param.scaleY = TRANSFORM_UNITY_VALUE;
    param.skewX = TRANSFORM_UNITY_VALUE;
    param.skewY = TRANSFORM_UNITY_VALUE;
    param.translateX = TRANSFORM_UNITY_VALUE;
    param.translateY = TRANSFORM_UNITY_VALUE;
}

void Matrix2D::Scale(TransformParam& param, double sx, double sy)
{
    param.scaleX *= sx;
    param.scaleY *= sy;
}

void Matrix2D::Translate(TransformParam& param, double tx, double ty)
{
    param.translateX += tx;
    param.translateY += ty;
}

void Matrix2D::Rotate(TransformParam& param, double degree, double rx, double ry)
{
    param.skewX *= degree * rx;
    param.skewY *= degree * ry;
}
} // namespace OHOS::Ace::NG

