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

#ifndef OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

using VectorFfiImageHandle = void*;

extern "C" {
struct FfiImage {
    const char* src;
    int32_t duration;
    double width;
    int32_t widthUnit;
    double height;
    int32_t heightUnit;
    double top;
    int32_t topUnit;
    double left;
    int32_t leftUnit;
};

CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorCreate();
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetImages(VectorFfiImageHandle vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetState(int32_t state);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetDuration(int32_t duration);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetReverse(bool isReverse);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetFixedSize(bool fixedSize);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetPreDecode(int32_t preDecode);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetFillMode(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorSetIterations(int32_t iteration);
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorOnStart(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorOnPause(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorOnRepeat(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorOnCancel(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkImageAnimatorOnFinish(void (*callback)());
CJ_EXPORT VectorFfiImageHandle FfiCJCreateVectorFfiImage(int64_t size);
CJ_EXPORT void FfiCJVectorFfiImageSetElement(VectorFfiImageHandle yec, int64_t index, FfiImage image);
CJ_EXPORT void FfiCJVectorFfiImageDelete(VectorFfiImageHandle vec);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_IMAGE_FFI_H
