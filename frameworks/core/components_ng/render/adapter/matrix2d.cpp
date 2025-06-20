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
#include "2d_graphics/include/utils/matrix.h"

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
    degree = degree * OHOS_SEMI_CIRCLE_ANGEL / M_PI;
    skMatrix = skMatrix.preRotate(degree, rx, ry);
    ConvertToTransformParam(param, skMatrix);
}

Matrix4 SetMatrixPolyToPoly(
    const Matrix4& matrix, const std::vector<OHOS::Ace::NG::PointT<int32_t>>& totalPoint)
{
    auto matrix3d = OHOS::Rosen::Drawing::Matrix();
    /**
     * When converting from matrix4 to matrix3
     * [a b c]    [a b 0 c]
     * [d e f] -> [d e 0 f]
     * [g h i]    [0 0 1 0]
     *            [g h 0 i]
    */
    matrix3d.SetMatrix(matrix.Get(0, 0), matrix.Get(1, 0), matrix.Get(3, 0), matrix.Get(0, 1), matrix.Get(1, 1),
        matrix.Get(3, 1), matrix.Get(0, 3), matrix.Get(1, 3), matrix.Get(3, 3));
    size_t arrayLength = totalPoint.size() / 2;
    OHOS::Rosen::Drawing::PointF src[arrayLength];
    OHOS::Rosen::Drawing::PointF dst[arrayLength];
    for (size_t i = 0; i < arrayLength; i++) {
        auto point = totalPoint[i];
        src[i] = OHOS::Rosen::Drawing::Point(point.GetX(), point.GetY());
    }
    for (size_t i = 0; i < arrayLength; i++) {
        auto point = totalPoint[i + arrayLength];
        dst[i] = OHOS::Rosen::Drawing::Point(point.GetX(), point.GetY());
    }
    matrix3d.SetPolyToPoly(src, dst, arrayLength);
    Matrix4 retMatrix4(matrix3d.Get(0), matrix3d.Get(1), 0, matrix3d.Get(2), matrix3d.Get(3), matrix3d.Get(4), 0,
        matrix3d.Get(5), 0, 0, 1, 0, matrix3d.Get(6), matrix3d.Get(7), 0, matrix3d.Get(8));
    return retMatrix4;
}
} // namespace OHOS::Ace::NG

