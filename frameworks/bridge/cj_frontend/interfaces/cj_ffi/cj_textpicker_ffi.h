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

using VectorRangeContentHandle = void*;
using VectorTextCascadePickerOptionsHandle = void*;
using VectorUInt32Handle = void*;
using VectorStringPtr = void*;

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

struct CJRangeContent {
    std::string icon_;
    std::string text_;
};

struct CJTextCascadePickerOptions {
    VectorStringPtr rangeResult;
    VectorTextCascadePickerOptionsHandle children;
};

struct CJTextArrayParamSingle {
    const VectorRangeContentHandle result;
    uint32_t kind;
    uint32_t selected;
    const char* value;
    void (*selectedChangeEvent)(uint32_t selectedchange);
    void (*valueChangeEvent)(const char* valuechange);
};

struct CJTextArrayParamMulti {
    const VectorTextCascadePickerOptionsHandle options;
    VectorUInt32Handle selecteds;
    VectorStringPtr values;
    uint32_t maxcount;
    bool isCascade = false;
    bool isHasSelectAttr = false;
    void (*selectedsChangeEvent)(VectorUInt32Handle selectedchange);
    void (*valuesChangeEvent)(VectorStringPtr valuechange);
};

CJ_EXPORT VectorRangeContentHandle FFICJVectorCreateRangeContent(int64_t size);
CJ_EXPORT void FFICJVectorRangeContentDelete(VectorRangeContentHandle vec);
CJ_EXPORT void FFICJVectorRangeContentSetElement(
    VectorRangeContentHandle vec, int64_t index, CJRangeContent rangeContentOptions);
CJ_EXPORT VectorTextCascadePickerOptionsHandle FFICJVectorCreateTextCascadePickerOptions(int64_t size);
CJ_EXPORT void FFICJVectorTextCascadePickerOptionsDelete(VectorTextCascadePickerOptionsHandle vec);
CJ_EXPORT void FFICJVectorTextCascadePickerOptionsSetElement(
    VectorTextCascadePickerOptionsHandle vec, int64_t index, CJTextCascadePickerOptions textCascadeOptions);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerDialogShow(VectorStringPtr vecContent, CJDialogShow value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetDefaultPickerItemHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetCanLoop(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreate(VectorStringPtr vecContent, uint32_t selected, const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreateSingle(CJTextArrayParamSingle param);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreateMulti(CJTextArrayParamMulti param);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreateMulti(CJTextArrayParamMulti param);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetDisappearTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetGradientHeight(double length, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetDivider(DividerParams params);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedIndexSingle(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetSelectedIndexMulti(VectorUInt32Handle values);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerOnChange(void (*callback)(CJTextPickerResult pickerResult));
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerCreate(VectorStringPtr vecContent, uint32_t selected, const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkTextPickerSetOpacity(double opacity);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXTPICKER_FFI_H
