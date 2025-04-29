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

#ifndef OHOS_ACE_FRAMEWORK_CJ_MATRIX4_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_MATRIX4_FFI_H

#include <cstdint>

#include "ffi_remote_data.h"

#include "base/geometry/matrix4.h"
#include "base/geometry/ng/point_t.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"

using VectorFloat32Ptr = void*;
using VectorInt32Ptr = void*;
using VectorPoints = std::vector<OHOS::Ace::NG::PointT<int32_t>>;

namespace OHOS::Matrix4 {

class ACE_EXPORT NativeMatrix : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeMatrix, OHOS::FFI::FFIData)
public:
    NativeMatrix();

    const OHOS::Ace::Matrix4& GetMatrix4()
    {
        return instance_;
    }

    void SetMatrix4(const OHOS::Ace::Matrix4& instance)
    {
        instance_ = instance;
    }

    void SetMatrix4(OHOS::Ace::Matrix4&& instance)
    {
        instance_ = std::move(instance);
    }

private:
    OHOS::Ace::Matrix4 instance_ = OHOS::Ace::Matrix4();
};

} // namespace OHOS::Matrix4

extern "C" {
struct FfiScaleParams {
    float x;
    float y;
    float z;
    float centerX;
    float centerY;
};

struct FfiRotateParams {
    float x;
    float y;
    float z;
    float angle;
    float centerX;
    float centerY;
};

struct FfiPoint {
    double x;
    double y;
};

struct FfiPolyToPolyOptions {
    VectorInt32Ptr srcX;
    VectorInt32Ptr srcY;
    int32_t srcIndex;
    VectorInt32Ptr dstX;
    VectorInt32Ptr dstY;
    int32_t dstIndex;
    int32_t pointCount;
};

CJ_EXPORT int64_t FfiOHOSMatrix4Init(VectorFloat32Ptr array);
CJ_EXPORT int64_t FfiOHOSMatrix4Identity();
CJ_EXPORT int64_t FfiOHOSMatrix4Copy(int64_t id);
CJ_EXPORT void FfiOHOSMatrix4Invert(int64_t id);
CJ_EXPORT void FfiOHOSMatrix4Combine(int64_t result, int64_t target);
CJ_EXPORT void FfiOHOSMatrix4Translate(int64_t id, float x, float y, float z);
CJ_EXPORT void FfiOHOSMatrix4Scale(int64_t id, FfiScaleParams params);
CJ_EXPORT void FfiOHOSMatrix4Rotate(int64_t id, FfiRotateParams params);
CJ_EXPORT FfiPoint FfiOHOSMatrix4TransformPoint(int64_t id, FfiPoint ffiPoint);
CJ_EXPORT void FfiOHOSMatrix4Skew(int64_t id, float x, float y);
CJ_EXPORT void FfiOHOSMatrix4SetPolyToPoly(int64_t id, FfiPolyToPolyOptions option);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_MATRIX4_FFI_H
