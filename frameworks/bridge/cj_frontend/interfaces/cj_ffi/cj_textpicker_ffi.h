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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXTPICKER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXTPICKER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorStringPtr = void*;
using VectorUInt32Handle = void*;

extern "C" {
struct CJDialogShow {
    uint32_t selected;
    double height;
    int32_t heightUnit;
    void (*accept)(CJTextPickerResult pickerResult);
    void (*cancel)();
    void (*change)(CJTextPickerResult pickerResult);
};

struct DividerParams {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double startMargin;
    int32_t startMarginUnit;
    double endMargin;
    int32_t endMarginUnit;
};

CJ_EXPORT void FfiOHOSAceFrameworkTextPickerDialogShow(VectorStringPtr vecContent, CJDialogShow value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetDefaultPickerItemHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetCanLoop(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPikerSetDisappearTextStyle(uint32_t color, double size,
    int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetGradientHeight(double length, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetDivider(DividerParams params);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedIndexSingle(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedIndexMulti(VectorUInt32Handle values);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerOnChange(void (*callback)(CJTextPickerResult pickerResult));
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreate(VectorStringPtr vecContent, uint32_t selected, const char* value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXTPICKER_FFI_H
