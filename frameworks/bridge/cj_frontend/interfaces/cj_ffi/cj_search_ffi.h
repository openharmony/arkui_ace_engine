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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct SearchCreateParam {
    const char* value;
    const char* placeholder;
    int64_t iconID;
    uint32_t iconType;
    const char* iconParams;
    int64_t controllerID;
};
CJ_EXPORT void FfiOHOSAceFrameworkSearchCreateByIconID(SearchCreateParam value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetSearchButton(const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetPlaceholderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetPlaceholderFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetTextFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily);

struct SearchSetBorder {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double radius;
    int32_t radiusUnit;
    int32_t style;
};
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorder(SearchSetBorder value);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderWidth(double width, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetBorderRadius(double radius, int32_t radiusUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetHeight(double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkSearchSetCopyOption(int32_t copyOption);
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnSubmit(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnChange(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnCopy(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnCut(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkSearchOnPaste(void (*callback)(const char* value));

CJ_EXPORT int64_t FfiOHOSAceFrameworkSearchController();
CJ_EXPORT void FfiOHOSAceFrameworkSearchCaretPosition(int64_t selfID, int32_t carePosition);
CJ_EXPORT void FfiOHOSAceFrameworkSearchCreateByIconRes(
    const char* value, const char* placeholder, const char* iconUrl, int64_t controllerId);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_SCROLLBAR_FFI_H
