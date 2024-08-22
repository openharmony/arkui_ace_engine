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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkTextCreate(const char* content);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontWeight(const char* fontWeight);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontColor(uint32_t textColor);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextOverflow(int32_t overflow);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMaxLines(int32_t maxLines);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontStyle(int32_t fontStyle);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextAlign(int32_t textAlign);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetLineHeight(double lineHeight, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetFontFamily(const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetDecoration(int32_t typeValue, uint32_t colorValue);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMinFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetMaxFontSize(double fontSize, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetTextCase(int32_t textCase);
CJ_EXPORT void FfiOHOSAceFrameworkTextSetBaselineOffset(double baseLine, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkTextOnClick(void (*callback)(CJClickInfo clickInfo));
CJ_EXPORT void FfiTextSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiTextSetResponseRegionArray(VectorStringPtr vecContent);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
