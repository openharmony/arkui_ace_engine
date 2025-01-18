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

#ifndef OHOS_ACE_FRAMWORK_CJ_SPAN_FFI_H
#define OHOS_ACE_FRAMWORK_CJ_SPAN_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_span_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_clock_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_ffi.h"

using VectorDoubleHandle = void*;
using VectorStrPtr = void*;
using VectorNativeTextShadows = void*;

extern "C" {
struct NativeTextShadows {
    double radius;
    double offsetX;
    double offsetY;
    uint32_t color;
    bool isFilled;
    int32_t type;
};

CJ_EXPORT VectorNativeTextShadows FFICJCreateVectorNativeTextShadows(int64_t size);
CJ_EXPORT void FFICJVectorNativeTextShadowsSetElement(
    VectorNativeTextShadows vec, int64_t index, NativeTextShadows textShadow);
CJ_EXPORT void FFICJVectorNativeTextShadowsDelete(VectorNativeTextShadows vec);

CJ_EXPORT void FfiOHOSAceFrameworkSpanCreate(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFontColor(uint32_t textColor);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFontStyle(int32_t fontStyle);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetLetterSpacing(double space, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetTextCase(int32_t textCase);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetDecoration(int32_t type, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetOnClick(void (*callback)(CJClickInfo clickInfo));
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetFont(
    const char* family, double size, int32_t unit, const char* weight, int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetBaselineOffset(double offset, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetLineHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetTextShadow(VectorStrPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetTextBackgroundStyle(uint32_t color, double radius, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkSpanSetTextBackgroundStyleBorder(uint32_t color, CBorderRadiuses radius);
}

#endif // OHOS_ACE_FRAMWORK_CJ_SPAN_FFI_H
