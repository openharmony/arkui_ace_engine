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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H

#include <cstdint>
#include <cstdio>

#include "cj_native_view_ffi.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
using VectorCJStringHandle = void*;
extern "C" {
struct VectorToCFFIArrayString {
    size_t size;
    char** buffer;
    void (*free)(VectorToCFFIArrayString*);
};

struct SetIdResultFFI {
    VectorToCFFIArray diffIndexArrayPtr;
    VectorToCFFIArray duplicateIdsPtr;
    VectorToCFFIArray removedChildElmtIdsPtr;
};

typedef void (*ViewCallBack)(int64_t);
typedef ExternalString (*IdCallBack)(int64_t);

CJ_EXPORT void FfiOHOSAceFrameworkForEachCreateFU(
    char* viewId, int64_t parentViewID, int64_t dataSize, ViewCallBack callbackView, IdCallBack callbackKey);
CJ_EXPORT void FfiOHOSAceFrameworkForEachCreate();
CJ_EXPORT void FfiOHOSAceFrameworkForEachPop();
CJ_EXPORT VectorToCFFIArrayString FfiOHOSAceFrameworkViewGetIdArray(int64_t elmtId);
CJ_EXPORT VectorToCFFIArray FfiOHOSAceFrameworkViewSetIdArray(int64_t elmtId, VectorCJStringHandle vecHandle);
CJ_EXPORT SetIdResultFFI FfiOHOSAceFrameworkViewSetIdArrayReturnStruct(int64_t elmtId, VectorCJStringHandle newIdArray);
CJ_EXPORT void FfiOHOSAceFrameworkViewCreateNewChildStart(char* elmtId);
CJ_EXPORT void FfiOHOSAceFrameworkViewCreateNewChildFinish(char* elmtId);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TOGGLE_FFI_H
