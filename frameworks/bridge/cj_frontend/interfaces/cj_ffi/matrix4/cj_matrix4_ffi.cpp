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
            auto index = i * Matrix4::DIMENSION + j;
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
        return ERR_INVALID_INSTANCE_CODE;
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
        Point point { ffiPoint.x, ffiPoint.y };
        Point target = matrix * point;
        result.x = target.GetX();
        result.y = target.GetY();
        return result;
    } else {
        LOGE("FfiOHOSMatrix4TransformPoint: invalid id of Matrix4");
        return result;
    }
}
}
