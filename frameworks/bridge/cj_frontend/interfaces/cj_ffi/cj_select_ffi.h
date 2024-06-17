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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SELECT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SELECT_FFI_H

#include <cstdint>
#include <vector>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorStringPtr = void*;
using VectorNativeSelectOptionHandle = void*;

extern "C" {
struct NativeSelectOption {
    char* value;
    char* icon;
};
CJ_EXPORT VectorNativeSelectOptionHandle FFICJCreateVectorNativeSelectOption(int64_t size);
CJ_EXPORT void FFICJVectorNativeSelectOptionSetElement(
    VectorNativeSelectOptionHandle vec, int64_t index, NativeSelectOption selectOption);
CJ_EXPORT void FFICJVectorNativeSelectOptionDelete(VectorNativeSelectOptionHandle vec);

CJ_EXPORT void FfiOHOSAceFrameworkSelectCreate(VectorNativeSelectOptionHandle values);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetSelected(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetValue(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetSelectedOptionBgColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetSelectedOptionFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetSelectedOptionFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionBgColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionFontColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetSpace(double width, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetArrowPosition(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetMenuAlign(
    int32_t value, double dx, int32_t dxUnit, double dy, int32_t dyUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionWidth(double width, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionWidthWithMode(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetOptionHeight(double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetMenuBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSelectSetMenuBackgroundBlurStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkSelectOnSelect(void (*callback)(int32_t index, const char* value));
};
#endif