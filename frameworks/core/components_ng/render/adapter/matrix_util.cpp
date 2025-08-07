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

#include "frameworks/core/components_ng/render/adapter/matrix_util.h"

#include "2d_graphics/include/utils/matrix.h"

namespace OHOS::Ace::NG {
constexpr int32_t POSITION_TWO = 2;
constexpr int32_t POSITION_THREE = 3;
constexpr int32_t POSITION_FOUR = 4;
constexpr int32_t POSITION_FIVE = 5;
constexpr int32_t POSITION_SIX = 6;
constexpr int32_t POSITION_SEVEN = 7;
constexpr int32_t POSITION_EIGHT = 8;

Matrix4 MatrixUtil::SetMatrixPolyToPoly(
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
    matrix3d.SetMatrix(matrix.Get(0, 0), matrix.Get(1, 0), matrix.Get(POSITION_THREE, 0), matrix.Get(0, 1),
        matrix.Get(1, 1), matrix.Get(POSITION_THREE, 1), matrix.Get(0, POSITION_THREE), matrix.Get(1, POSITION_THREE),
        matrix.Get(POSITION_THREE, POSITION_THREE));
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
    Matrix4 retMatrix4(matrix3d.Get(0), matrix3d.Get(1), 0, matrix3d.Get(POSITION_TWO), matrix3d.Get(POSITION_THREE),
        matrix3d.Get(POSITION_FOUR), 0, matrix3d.Get(POSITION_FIVE), 0, 0, 1, 0, matrix3d.Get(POSITION_SIX),
        matrix3d.Get(POSITION_SEVEN), 0, matrix3d.Get(POSITION_EIGHT));
    return retMatrix4;
}
}