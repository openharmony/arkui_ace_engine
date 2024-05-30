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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_EVIRONMENT_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_EVIRONMENT_H

#include <string>
#include "base/memory/referenced.h"
#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT NativeOptionBool FfiOHOSAceFrameworkEnvironmentGetAccessibilityEnabled();
CJ_EXPORT NativeOptionInt32 FfiOHOSAceFrameworkEnvironmentGetColorMode();
CJ_EXPORT NativeOptionFloat32 FfiOHOSAceFrameworkEnvironmentGetFontScale();
CJ_EXPORT NativeOptionFloat32 FfiOHOSAceFrameworkEnvironmentGetFontWeightScale();
CJ_EXPORT NativeOptionInt32 FfiOHOSAceFrameworkEnvironmentGetLayoutDirection();
CJ_EXPORT NativeOptionCString FfiOHOSAceFrameworkEnvironmentGetLanguageCode();
}

#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_EVIRONMENT_H