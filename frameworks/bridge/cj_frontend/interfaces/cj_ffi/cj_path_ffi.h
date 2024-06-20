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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PATH_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PATH_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkPathCreate(const char* commands);
CJ_EXPORT void FfiOHOSAceFrameworkPathCreateWithSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit, const char* commands);
CJ_EXPORT void FfiOHOSAceFrameworkPathSetCommands(const char* commands);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPathInsCreate(const char* commands);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPathInsCreateWithSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit, const char* commands);
};
#endif