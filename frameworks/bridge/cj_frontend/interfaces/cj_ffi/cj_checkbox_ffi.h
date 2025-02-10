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

#ifndef OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxCreate(const char* name, const char* group);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSelect(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetSelectedColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetWidth(double width, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetHeight(double height, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetSize(double width, uint32_t widthUnit, double height, uint32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetPadding(double padding, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetOnChange(void (*callback)(bool isOn));
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxSetCheckboxStyle(int32_t checkBoxStyle);
CJ_EXPORT void FfiCheckBoxSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiCheckBoxSetResponseRegionArray(VectorStringPtr vecContent);
CJ_EXPORT void FfiCheckBoxCreateWithIndicator(const char* name, const char* group, void (*indicatorBuilder)());
CJ_EXPORT void FfiCheckBoxUnselectedColor(uint32_t color);
CJ_EXPORT void FfiCheckBoxMarkStyle(
    uint32_t strokeColor, double size, int32_t sizeUnit, double strokeWidth, int32_t strokeWidthUnit);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_FFI_H
