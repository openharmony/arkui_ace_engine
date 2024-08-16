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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetHeight(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetSize(
    double width, uint32_t widthUnit, double height, uint32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorder(CJBorder params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderWidth(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderWidthWithCJEdge(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBorderRadius(double value, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetAllBorderRadius(CJBorderRadius value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPadding(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMargin(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMargins(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPlaceholderColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetPlaceholderFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetEnterKeyType(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetCaretColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetMaxLength(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetTextAlign(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontSize(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontWeight(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontStyle(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetFontFamily(const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldSetInputFilter(const char* value, void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnSubmit(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnChange(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnCopy(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnCut(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnPaste(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkTextFieldOnEditChanged(void (*callback)(bool value));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXTINPUT_FFI_H
