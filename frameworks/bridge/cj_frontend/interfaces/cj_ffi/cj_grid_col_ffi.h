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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GIRD_COL_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_GIRD_COL_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_grid_row_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkGridColCreate();
CJ_EXPORT void FfiOHOSAceFrameworkGridColCreateWithInt32(int32_t span, int32_t offset, int32_t order);
CJ_EXPORT void FfiOHOSAceFrameworkGridColCreateWithOption(GridRowColumnOption span, GridRowColumnOption offset,
                                                          GridRowColumnOption order);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetSpan(int32_t span);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetSpanWithOption(GridRowColumnOption span);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetOffset(int32_t offset);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetOffsetWithOption(GridRowColumnOption offset);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetOrder(int32_t order);
CJ_EXPORT void FfiOHOSAceFrameworkGridColSetOrderWithOption(GridRowColumnOption order);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_GIRD_COL_FFI_H