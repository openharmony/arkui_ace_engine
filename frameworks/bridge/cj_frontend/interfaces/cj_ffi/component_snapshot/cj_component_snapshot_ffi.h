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

#ifndef OHOS_ACE_FRAMEWORK_CJ_COMPONENT_SNAPSHOT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_COMPONENT_SNAPSHOT_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"

extern "C" {
struct CSnapshotGetSyncRet {
    int32_t errCode;
    int64_t pixelMapId;
};

struct CSnapshotOptions {
    float scale;
    bool waitUntilRenderFinished;
};

CJ_EXPORT void FfiOHOSAceFrameworkComponentSnapshotGet(
    const char* id,
    void (*callback)(NativeOptionInt32 errCode, NativeOptionInt64 pixelMapId),
    CSnapshotOptions options);

CJ_EXPORT void FfiOHOSAceFrameworkComponentSnapshotCreate(
    void (*builder)(),
    void (*callback)(NativeOptionInt32 errCode, NativeOptionInt64 pixelMapId),
    int32_t delay,
    bool checkImageStatus,
    CSnapshotOptions options);

CJ_EXPORT CSnapshotGetSyncRet FfiOHOSAceFrameworkComponentSnapshotGetSync(
    const char* id,
    CSnapshotOptions options);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_COMPONENT_SNAPSHOT_FFI_H