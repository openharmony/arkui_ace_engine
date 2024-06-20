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

#ifndef OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H
#define OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkGridCreate();
CJ_EXPORT void FfiOHOSAceFrameworkGridCreateScroller(int64_t scrollerID);
CJ_EXPORT void FfiOHOSAceFrameworkGridSetCachedCount(int32_t cachedCount);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsTemplate(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsTemplate(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsGapWithString(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridColumnsGapWithNum(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsGapWithString(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkGridRowsGapWithNum(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkGridOnScrollIndex(void (*callback)(uint32_t index));
}

#endif // OHOS_ACE_FRAMWORK_CJ_GRID_FFI_H
