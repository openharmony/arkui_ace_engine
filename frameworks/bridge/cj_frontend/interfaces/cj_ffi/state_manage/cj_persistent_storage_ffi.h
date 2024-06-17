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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PERSISTENT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PERSISTENT_H

#include <string>
#include "base/memory/referenced.h"
#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using NotifyCallbackString = void (*)(const char* key, const char* value);
using NotifyCallbackInt64 = void (*)(const char* key, int64_t value);
using NotifyCallbackFloat64 = void (*)(const char* key, double value);
using NotifyCallbackBool = void (*)(const char* key, bool value);

extern "C" {
CJ_EXPORT NativeOptionCString FfiOHOSAceFrameworkPersistentGetString(const char* key);
CJ_EXPORT NativeOptionInt64 FfiOHOSAceFrameworkPersistentGetInt64(const char* key);
CJ_EXPORT NativeOptionFloat64 FfiOHOSAceFrameworkPersistentGetFloat64(const char* key);
CJ_EXPORT NativeOptionBool FfiOHOSAceFrameworkPersistentGetBool(const char* key);

CJ_EXPORT void FfiOHOSAceFrameworkPersistentSetString(
    const char* key, const char* value, NotifyCallbackString callback);
CJ_EXPORT void FfiOHOSAceFrameworkPersistentSetInt64(const char* key, int64_t value, NotifyCallbackInt64 callback);
CJ_EXPORT void FfiOHOSAceFrameworkPersistentSetFloat64(const char* key, double value, NotifyCallbackFloat64 callback);
CJ_EXPORT void FfiOHOSAceFrameworkPersistentSetBool(const char* key, bool value, NotifyCallbackBool callback);

CJ_EXPORT void FfiOHOSAceFrameworkPersistentDelete(const char* key);
CJ_EXPORT void FfiOHOSAceFrameworkPersistentClear();
}
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_PERSISTENT_H