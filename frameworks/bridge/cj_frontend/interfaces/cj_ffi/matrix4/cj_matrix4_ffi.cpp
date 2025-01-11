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

#include "bridge/cj_frontend/interfaces/cj_ffi/matrix4/cj_matrix4_ffi.h"

#include "draw/canvas.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Matrix4 {

NativeMatrix::NativeMatrix() : FFIData()
{
    LOGI("Native NativeMatrix constructed");
}
} // namespace OHOS::Matrix4

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Matrix4;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace::NG;
using namespace OHOS::Rosen::Drawing;

extern "C" {
int64_t FfiOHOSMatrix4Init(VectorFloat32Ptr array)
{
    auto nativeMatrix = FFIData::Create<NativeMatrix>();
    if (nativeMatrix == nullptr) {
        return FFI_ERROR_CODE;
    }
    Matrix4 matrix = Matrix4::CreateIdentity();

    const auto& vector = *reinterpret_cast<std::vector<float>*>(array);
    if (vector.size() != Matrix4::DIMENSION * Matrix4::DIMENSION) {
        LOGE("FfiOHOSMatrix4Init: invalid size of matrix4 array");
        nativeMatrix->SetMatrix4(std::move(matrix));
        return nativeMatrix->GetID();
    }
    for (int32_t i = 0; i < Matrix4::DIMENSION; i++) {
        for (int32_t j = 0; j < Matrix4::DIMENSION; j++) {
            unsigned long index = static_cast<unsigned long>(i * Matrix4::DIMENSION + j);
            if (index < vector.size()) {
                matrix.Set(j, i, vector[index]);
            }
        }
    }

    nativeMatrix->SetMatrix4(std::move(matrix));
    return nativeMatrix->GetID();
}

int64_t FfiOHOSMatrix4Identity()
{
    auto nativeMatrix = FFIData::Create<NativeMatrix>();
    if (nativeMatrix == nullptr) {
        return FFI_ERROR_CODE;
    }
    nativeMatrix->SetMatrix4(Matrix4::CreateIdentity());
    return nativeMatrix->GetID();
}

int64_t FfiOHOSMatrix4Copy(int64_t id)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix == nullptr) {
        return FFI_ERROR_CODE;
    }
    if (nativeMatrix != nullptr) {
        auto copyMatrix = nativeMatrix->GetMatrix4();
        auto result = FFIData::Create<NativeMatrix>();
        result->SetMatrix4(std::move(copyMatrix));
        return result->GetID();
    } else {
        LOGE("FfiOHOSMatrix4Copy: invalid id of Matrix");
        return FFI_ERROR_CODE;
    }
}

void FfiOHOSMatrix4Invert(int64_t id)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix == nullptr) {
        return;
    }
    if (nativeMatrix != nullptr) {
        auto invertMatrix = Matrix4::Invert(nativeMatrix->GetMatrix4());
        nativeMatrix->SetMatrix4(std::move(invertMatrix));
    } else {
        LOGE("FfiOHOSMatrix4Invert: invalid id of Matrix");
    }
}

void FfiOHOSMatrix4Combine(int64_t origin, int64_t target)
{
    auto nativeMatrixOrigin = FFIData::GetData<NativeMatrix>(origin);
    auto nativeMatrixTarget = FFIData::GetData<NativeMatrix>(target);
    if (nativeMatrixOrigin == nullptr) {
        LOGE("FfiOHOSMatrix4Combine: invalid id of MatrixResult");
        return;
    }
    if (nativeMatrixTarget == nullptr) {
        LOGE("FfiOHOSMatrix4Combine: invalid id of MatrixTarge");
        return;
    }
    Matrix4 originMatrix4 = nativeMatrixOrigin->GetMatrix4();
    auto result = originMatrix4 * nativeMatrixTarget->GetMatrix4();
    nativeMatrixOrigin->SetMatrix4(std::move(result));
}

void FfiOHOSMatrix4Translate(int64_t id, float x, float y, float z)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto result = Matrix4::CreateTranslate(x, y, z) * nativeMatrix->GetMatrix4();
        nativeMatrix->SetMatrix4(std::move(result));
    } else {
        LOGE("FfiOHOSMatrix4Translate: invalid id of Matrix4");
    }
}

void FfiOHOSMatrix4Scale(int64_t id, FfiScaleParams params)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto scaleMatrix = Matrix4::CreateScale(params.x, params.y, params.z);
        if (!NearZero(params.centerX) || !NearZero(params.centerY)) {
            auto translate1 = Matrix4::CreateTranslate(params.centerX, params.centerY, 0.0);
            auto translate2 = Matrix4::CreateTranslate(-params.centerX, -params.centerY, 0.0);
            scaleMatrix = scaleMatrix * translate2;
            scaleMatrix = translate1 * scaleMatrix;
        }
        auto result = scaleMatrix * nativeMatrix->GetMatrix4();
        nativeMatrix->SetMatrix4(std::move(result));
    } else {
        LOGE("FfiOHOSMatrix4Scale: invalid id of Matrix4");
    }
}

void FfiOHOSMatrix4Rotate(int64_t id, FfiRotateParams params)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto rotateMatrix = Matrix4::CreateRotate(params.angle, params.x, params.y, params.z);
        if (!NearZero(params.centerX) || !NearZero(params.centerY)) {
            auto translate1 = Matrix4::CreateTranslate(params.centerX, params.centerY, 0.0);
            auto translate2 = Matrix4::CreateTranslate(-params.centerX, -params.centerY, 0.0);
            rotateMatrix = rotateMatrix * translate2;
            rotateMatrix = translate1 * rotateMatrix;
        }
        auto result = rotateMatrix * nativeMatrix->GetMatrix4();
        nativeMatrix->SetMatrix4(std::move(result));
    } else {
        LOGE("FfiOHOSMatrix4Scale: invalid id of Matrix4");
    }
}

FfiPoint FfiOHOSMatrix4TransformPoint(int64_t id, FfiPoint ffiPoint)
{
    FfiPoint result = { 0.0, 0.0 };
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto matrix = nativeMatrix->GetMatrix4();
        OHOS::Ace::Point point { ffiPoint.x, ffiPoint.y };
        OHOS::Ace::Point target = matrix * point;
        result.x = target.GetX();
        result.y = target.GetY();
        return result;
    } else {
        LOGE("FfiOHOSMatrix4TransformPoint: invalid id of Matrix4");
        return result;
    }
}

void FfiOHOSMatrix4Skew(int64_t id, float x, float y)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix != nullptr) {
        auto skewMatrix = Matrix4::CreateFactorSkew(x, y);
        auto result = skewMatrix * nativeMatrix->GetMatrix4();
        nativeMatrix->SetMatrix4(std::move(result));
    } else {
        LOGE("FfiOHOSMatrix4Skew: invalid id of Matrix4");
    }
}

void SetMatrix4PolyToPoly(const int64_t id, const std::vector<OHOS::Ace::NG::PointT<int32_t>>& totalPoint)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix == nullptr) {
        LOGE("SetMatrix4PolyToPoly: invalid id of Matrix4");
        return;
    }
    auto matrix3d = OHOS::Rosen::Drawing::Matrix();
    auto matrix = nativeMatrix->GetMatrix4();
    /**
     * When converting from matrix4 to matrix3
     * [a b c]    [a b 0 c]
     * [d e f] -> [d e 0 f]
     * [g h i]    [0 0 1 0]
     *            [g h 0 i]
     */
    // cangjie remains consistent with arkts
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
    // cangjie remains consistent with arkts
    Matrix4 retMatrix4(matrix3d.Get(0), matrix3d.Get(1), 0, matrix3d.Get(2), matrix3d.Get(3), matrix3d.Get(4), 0,
        matrix3d.Get(5), 0, 0, 1, 0, matrix3d.Get(6), matrix3d.Get(7), 0, matrix3d.Get(8));
    nativeMatrix->SetMatrix4(std::move(retMatrix4));
}

void FfiOHOSMatrix4SetPolyToPoly(int64_t id, FfiPolyToPolyOptions option)
{
    auto nativeMatrix = FFIData::GetData<NativeMatrix>(id);
    if (nativeMatrix == nullptr) {
        LOGE("FfiOHOSMatrix4SetPolyToPoly: invalid id of Matrix4");
        return;
    }
    const auto& xSrcVector = *reinterpret_cast<std::vector<int32_t>*>(option.srcX);
    const auto& ySrcVector = *reinterpret_cast<std::vector<int32_t>*>(option.srcY);
    const auto& xDstVector = *reinterpret_cast<std::vector<int32_t>*>(option.dstX);
    const auto& yDstVector = *reinterpret_cast<std::vector<int32_t>*>(option.dstY);
    int32_t srcIndex = option.srcIndex;
    int32_t dstIndex = option.dstIndex;
    int32_t pointCount = option.pointCount;
    if (pointCount <= 0 || pointCount > static_cast<int32_t>(xSrcVector.size()) ||
        pointCount > static_cast<int32_t>(xDstVector.size())) {
        LOGE("setpPolyToPoly pointCount out of range pointCount:%{public}d, src size:%{public}d, dst size:%{public}d",
            static_cast<int>(pointCount), static_cast<int>(xSrcVector.size()), static_cast<int>(xDstVector.size()));
        return;
    }
    if (srcIndex < 0 || (pointCount + srcIndex) > static_cast<int32_t>(xSrcVector.size())) {
        LOGE("setpPolyToPoly srcIndex out of range srcIndex:%{public}d, pointCount:%{public}d, src size%{public}d",
            static_cast<int>(srcIndex), static_cast<int>(pointCount), static_cast<int>(xSrcVector.size()));
        return;
    }
    if (dstIndex < 0 || (pointCount + dstIndex) > static_cast<int32_t>(xDstVector.size())) {
        LOGE("setpPolyToPoly dstIndex out of range dstIndex:%{public}d, pointCount:%{public}d, dst size%{public}d",
            static_cast<int>(dstIndex), static_cast<int>(pointCount), static_cast<int>(xDstVector.size()));
        return;
    }
    VectorPoints totalPoints;
    int srcLastIndex = pointCount + srcIndex;
    int dstLastIndex = pointCount + dstIndex;
    for (int i = srcIndex; i < srcLastIndex; i++) {
        totalPoints.push_back(OHOS::Ace::NG::PointT(xSrcVector[i], ySrcVector[i]));
    }
    for (int i = dstIndex; i < dstLastIndex; i++) {
        totalPoints.push_back(OHOS::Ace::NG::PointT(xDstVector[i], yDstVector[i]));
    }
    SetMatrix4PolyToPoly(id, totalPoints);
}
}
