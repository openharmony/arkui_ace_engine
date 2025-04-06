/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACE_FRAMEWORK_CJ_COMPONENT_UTILS_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_COMPONENT_UTILS_FFI_H

#include <cstdint>
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"

extern "C" {
struct CSize {
    float width;
    float height;
};

struct COffset {
    float x;
    float y;
};

struct CTranslateResult {
    float x;
    float y;
    float z;
};

struct CScaleResult {
    float x;
    float y;
    float z;
    float centerX;
    float centerY;
};

struct CRotateResult {
    float x;
    float y;
    float z;
    float centerX;
    float centerY;
    float angle;
};

typedef struct {
    float *head;
    int64_t size;
} CArrFloat32;

struct CComponentInfo {
    CSize size;
    COffset localOffset;
    COffset windowOffset;
    COffset screenOffset;
    CTranslateResult translate;
    CScaleResult scale;
    CRotateResult rotate;
    CArrFloat32 transform;
};

CJ_EXPORT CComponentInfo FFIOHOSAceFrameworkComponentUtilsGetById(const char *id);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_COMPONENT_UTILS_FFI_H
