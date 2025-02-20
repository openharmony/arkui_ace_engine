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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NATIVE_VIEW_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NATIVE_VIEW_FFI_H

#include <cstdint>
#include <cstdio>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"

using VectorCJInt64Handle = void*;
extern "C" {
struct VectorToCFFIArray {
    size_t size;
    int64_t* buffer;
    void (*free)(int64_t*);
};

CJ_EXPORT void FfiOHOSAceFrameworkThrowNativeError(const char* msg);
CJ_EXPORT void FfiOHOSAceFrameworkNativeLog(const char* msg);
CJ_EXPORT bool FfiOHOSAceFrameworkLoadNativeView(int64_t nativeViewID);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewCreate(int64_t nativeViewID);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewCreateRecycle(
    int64_t nativeViewId, bool isRecycling, const char* name, void (*callback)());
CJ_EXPORT int64_t FfiOHOSAceFrameworkNativeViewCtor(int64_t remoteId);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewDestroy(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewBindRemote(int64_t nativeViewId, int64_t view);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewMarkNeedUpdate(int64_t nativeViewId);
CJ_EXPORT bool FfiOHOSAceFrameworkNativeViewNeedsUpdate(int64_t nativeViewId);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewMarkStatic(int64_t nativeViewId);
CJ_EXPORT bool FfiOHOSAceFrameworkNativeViewIsStatic(int64_t nativeViewId);
CJ_EXPORT ExternalString FfiOHOSAceFrameworkProcessViewId(int64_t nativeViewId);
CJ_EXPORT bool FfiOHOSAceFrameworkNativeViewIsFirstRender(int64_t nativeViewId);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewResetRecycleCustomNode(int64_t nativeViewId);

CJ_EXPORT VectorToCFFIArray FfiOHOSAceFrameworkViewGetDeletedElemtIds(int64_t nativeViewId);
CJ_EXPORT VectorCJInt64Handle FFICJCreateVectorCJInt64(int64_t size);
CJ_EXPORT void FFICJVectorCJInt64SetElement(VectorCJInt64Handle vec, int64_t index, int64_t value);
CJ_EXPORT void FFICJVectorCJInt64Delete(VectorCJInt64Handle vec);

CJ_EXPORT void FfiOHOSAceFrameworkNativeViewSyncInstanceId(int64_t nativeViewId);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewRestoreInstanceId(int64_t nativeViewId);
CJ_EXPORT void FfiOHOSAceFrameworkNativeViewFinishUpdateFunc(int64_t nativeViewId, int64_t elmtId);
CJ_EXPORT void FfiOHOSAceFrameworkViewDeletedElmtIdsHaveBeenPurged(int64_t nativeViewId, VectorCJInt64Handle vec);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NATIVE_VIEW_FFI_H
