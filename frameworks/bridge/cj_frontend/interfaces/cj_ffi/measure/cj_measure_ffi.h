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

#ifndef OHOS_ACE_FRAMEWORK_CJ_MEASURE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_MEASURE_FFI_H

#include <cstdint>

#include "base/utils/measure_util.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"


// using namespace OHOS::Ace;

extern "C" {
typedef struct CJMeasureContextToC {
    char* textContent;
    char* fontWeight;
    char* fontFamily;
    NativeOptionLength constraintWidth;
    NativeOptionLength fontSize;
    NativeOptionLength lineHeight;
    NativeOptionLength baselineOffset;
    NativeOptionLength letterSpacing;
    NativeOptionLength textIndent;
    uint32_t maxLines;
    int32_t textAlign;
    int32_t fontStyle;
    int32_t overflow;
    int32_t textCase;
    int32_t wordBreak;
} CJMeasureContextToC;

typedef struct CJSize {
    double width;
    double height;
} CJSize;

CJ_EXPORT double FfiMeasureText(const CJMeasureContextToC cjcontext);
CJ_EXPORT CJSize FfiMeasureTextSize(const CJMeasureContextToC cjcontext);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_MEASURE_FFI_H