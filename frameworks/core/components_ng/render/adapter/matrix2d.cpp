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

#include "frameworks/core/components_ng/render/adapter/matrix2d.h"
#include "include/core/SkMatrix.h"
#ifndef ARKUI_CAPI_UNITTEST
#include "2d_graphics/include/utils/matrix.h"
#endif // ARKUI_CAPI_UNITTEST
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
constexpr double OHOS_SEMI_CIRCLE_ANGEL = 180.0;
void ConvertToMatrix(const TransformParam& param, SkMatrix& skMatrix)
{
    double scaleX = param.scaleX;
    double skewX = param.skewX;
    double skewY = param.skewY;
    double scaleY = param.scaleY;
    double translateX = param.translateX;
    double translateY = param.translateY;
    skMatrix.setAll(scaleX, skewX, translateX, skewY, scaleY, translateY, 0.0f, 0.0f, 1.0f);
}

void ConvertToTransformParam(TransformParam& param, const SkMatrix& skMatrix)
{
    param.scaleX = skMatrix.getScaleX();
    param.skewX = skMatrix.getSkewX();
    param.skewY = skMatrix.getSkewY();
    param.scaleY = skMatrix.getScaleY();
    param.translateX = skMatrix.getTranslateX();
    param.translateY = skMatrix.getTranslateY();
}

bool Matrix2D::Invert(TransformParam& param)
{
    SkMatrix skMatrix;
    ConvertToMatrix(param, skMatrix);
    if (skMatrix.invert(&skMatrix)) {
        ConvertToTransformParam(param, skMatrix);
        return true;
    }
    return false;
}

void Matrix2D::Identity(TransformParam& param)
{
    SkMatrix skMatrix;
    ConvertToMatrix(param, skMatrix);
    skMatrix.reset();
    ConvertToTransformParam(param, skMatrix);
}

void Matrix2D::Scale(TransformParam& param, double sx, double sy)
{
    SkMatrix skMatrix;
    ConvertToMatrix(param, skMatrix);
    skMatrix = skMatrix.preScale(sx, sy);
    ConvertToTransformParam(param, skMatrix);
}

void Matrix2D::Translate(TransformParam& param, double tx, double ty)
{
    SkMatrix skMatrix;
    ConvertToMatrix(param, skMatrix);
    skMatrix = skMatrix.postTranslate(tx, ty);
    ConvertToTransformParam(param, skMatrix);
}

void Matrix2D::Rotate(TransformParam& param, double degree, double rx, double ry)
{
    SkMatrix skMatrix;
    ConvertToMatrix(param, skMatrix);
    // convert from radians to degree.
    degree = degree * OHOS_SEMI_CIRCLE_ANGEL / ACE_PI;
    skMatrix = skMatrix.preRotate(degree, rx, ry);
    ConvertToTransformParam(param, skMatrix);
}
} // namespace OHOS::Ace::NG

