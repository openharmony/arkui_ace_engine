/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_nav_path_stack_ffi.h"

extern "C" {
struct CJNavDestinationContext {
    CJNavPathInfoFFi pathInfo;
    int64_t pathStack;
    uint64_t navDestinationId;
};

CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationCreate();
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnBackPressed(bool (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkNavdestinationSetOnReady(void (*callback)(CJNavDestinationContext context));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_NAVDESTINATION_FFI_H
