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

#ifndef OHOS_ACE_FRAMEWORK_CJ_LINE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_LINE_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkLineCreate(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkLineSetStart(double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkLineSetEnd(double x, double y);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_LINE_FFI_H
