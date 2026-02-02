/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "martix_modifier.h"
#include "base/geometry/matrix4.h"
#include "frameworks/core/components_ng/render/adapter/matrix_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
constexpr int NUM_9 = 9;
constexpr int NUM_10 = 10;
constexpr int NUM_11 = 11;
constexpr int NUM_12 = 12;
constexpr int NUM_13 = 13;
constexpr int NUM_14 = 14;
constexpr int NUM_15 = 15;
ArkUIMatrix4Handle CreateIdentity()
{
    OHOS::Ace::Matrix4* matrix = new OHOS::Ace::Matrix4();
    return reinterpret_cast<ArkUIMatrix4Handle>(matrix);
}

ArkUIMatrix4Handle CreateByElements(const float* elements)
{
    OHOS::Ace::Matrix4* matrix = new OHOS::Ace::Matrix4;
    *matrix = OHOS::Ace::Matrix4(static_cast<double>(elements[NUM_0]), static_cast<double>(elements[NUM_4]),
        static_cast<double>(elements[NUM_8]), static_cast<double>(elements[NUM_12]),
        static_cast<double>(elements[NUM_1]), static_cast<double>(elements[NUM_5]),
        static_cast<double>(elements[NUM_9]), static_cast<double>(elements[NUM_13]),
        static_cast<double>(elements[NUM_2]), static_cast<double>(elements[NUM_6]),
        static_cast<double>(elements[NUM_10]), static_cast<double>(elements[NUM_14]),
        static_cast<double>(elements[NUM_3]), static_cast<double>(elements[NUM_7]),
        static_cast<double>(elements[NUM_11]), static_cast<double>(elements[NUM_15]));
    return reinterpret_cast<ArkUIMatrix4Handle>(matrix);
}

ArkUIMatrix4Handle Copy(const ArkUIMatrix4Handle matrix)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_RETURN(matrixType, nullptr);
    OHOS::Ace::Matrix4* matrixCopy = new OHOS::Ace::Matrix4;
    for (int row = 0; row < NUM_4; ++row) {
        for (int col = 0; col < NUM_4; ++col) {
            double value = matrixType->Get(row, col);
            matrixCopy->Set(row, col, value);
        }
    }
    return reinterpret_cast<ArkUIMatrix4Handle>(matrixCopy);
}

void Invert(ArkUIMatrix4Handle matrix)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    *matrixType = OHOS::Ace::Matrix4::Invert(*matrixType);
}

void Combine(ArkUIMatrix4Handle oriMatrix, ArkUIMatrix4Handle anotherMatrix)
{
    auto* oriMatrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(oriMatrix);
    CHECK_NULL_VOID(oriMatrixType);
    auto* anotherMatrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(anotherMatrix);
    CHECK_NULL_VOID(anotherMatrixType);
    *oriMatrixType = (*anotherMatrixType) * (*oriMatrixType);
}

void Translate(ArkUIMatrix4Handle matrix, float dx, float dy, float dz)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    *matrixType = OHOS::Ace::Matrix4::CreateTranslate(dx, dy, dz) * (*matrixType);
}

void Scale(ArkUIMatrix4Handle matrix, const ArkUI_Matrix4ScaleOptions* scale)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    CHECK_NULL_VOID(scale);
    OHOS::Ace::Matrix4 scaleMatrix = OHOS::Ace::Matrix4::CreateScale(scale->x, scale->y, scale->z);
    if (!NearZero(scale->centerX) || !NearZero(scale->centerY)) {
        auto translate1 = Matrix4::CreateTranslate(scale->centerX, scale->centerY, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-scale->centerX, -scale->centerY, 0.0);
        scaleMatrix = scaleMatrix * translate2;
        scaleMatrix = translate1 * scaleMatrix;
    }
    *matrixType = scaleMatrix * (*matrixType);
}

void Rotate(ArkUIMatrix4Handle matrix, const ArkUI_Matrix4RotationOptions* rotate)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    CHECK_NULL_VOID(rotate);
    OHOS::Ace::Matrix4 rotateMatrix;
    if (!rotate->isSetX && !rotate->isSetY && !rotate->isSetZ) {
        rotateMatrix = Matrix4::CreateRotate(rotate->angle, 0.0f, 0.0f, 1.0f);
    } else {
        rotateMatrix = Matrix4::CreateRotate(rotate->angle, rotate->x, rotate->y, rotate->z);
    }
    if (!NearZero(rotate->centerX) || !NearZero(rotate->centerY)) {
        auto translate1 = Matrix4::CreateTranslate(rotate->centerX, rotate->centerY, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-rotate->centerX, -rotate->centerY, 0.0);
        rotateMatrix = rotateMatrix * translate2;
        rotateMatrix = translate1 * rotateMatrix;
    }
    *matrixType = rotateMatrix * (*matrixType);
}

void Skew(ArkUIMatrix4Handle matrix, const float skewX, const float skewY)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    *matrixType = Matrix4::CreateFactorSkew(skewX, skewY) * (*matrixType);
}

void TransformPoint(ArkUIMatrix4Handle matrix, float oriPointX, float oriPointY, float* resultX, float* resultY)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    CHECK_NULL_VOID(resultX);
    CHECK_NULL_VOID(resultY);
    Point point { oriPointX, oriPointY };
    Point target = matrixType->TransformPoint(point);
    *resultX = static_cast<float>(target.GetX());
    *resultY = static_cast<float>(target.GetY());
}

void SetPolyToPoly(ArkUIMatrix4Handle matrix, std::vector<std::pair<float, float>>& srcIndex,
    std::vector<std::pair<float, float>>& dstIndex)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    std::vector<OHOS::Ace::NG::PointT<float>> totalPoint;
    for (uint32_t i = 0; i < srcIndex.size(); i++) {
        totalPoint.emplace_back(srcIndex[i].first, srcIndex[i].second);
    }
    for (uint32_t i = 0; i < dstIndex.size(); i++) {
        totalPoint.emplace_back(dstIndex[i].first, dstIndex[i].second);
    }
    Matrix4 ret = OHOS::Ace::NG::MatrixUtil::SetMatrixPolyToPolyFloat(*matrixType, totalPoint);
    *matrixType = ret;
}

void GetElements(const ArkUIMatrix4Handle matrix, float* result)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    for (int row = 0; row < OHOS::Ace::Matrix4::DIMENSION; ++row) {
        for (int col = 0; col < OHOS::Ace::Matrix4::DIMENSION; ++col) {
            double value = matrixType->Get(row, col);
            int index = col * OHOS::Ace::Matrix4::DIMENSION + row;
            result[index] = static_cast<float>(value);
        }
    }
}

void Dispose(ArkUIMatrix4Handle matrix)
{
    auto* matrixType = reinterpret_cast<OHOS::Ace::Matrix4*>(matrix);
    CHECK_NULL_VOID(matrixType);
    delete matrixType;
}
} // namespace

namespace NodeModifier {
const ArkUIMatrix4Modifier* GetMatrix4Modifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIMatrix4Modifier modifier = {
        .createMatrix4 = CreateIdentity,
        .createByElements = CreateByElements,
        .getElements = GetElements,
        .dispose = Dispose,
        .copy = Copy,
        .invert = Invert,
        .combine = Combine,
        .translate = Translate,
        .scale = Scale,
        .rotate = Rotate,
        .skew = Skew,
        .transformPoint = TransformPoint,
        .setPolyToPoly = SetPolyToPoly,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG