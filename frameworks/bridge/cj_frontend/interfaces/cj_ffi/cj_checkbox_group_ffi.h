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

#ifndef OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_GROUP_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_GROUP_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components/checkable/checkable_component.h"

extern "C" {
struct FFiCheckboxGroupResult {
    int32_t status;
    int64_t size;
    const char** nameBuffer;
};

CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupCreate(const char* name);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSelectAll(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetSelectedColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetWidth(double width, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetHeight(double height, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetSize(
    double width, uint32_t widthUnit, double height, uint32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetPadding(double padding, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetOnChange(void (*callback)(FFiCheckboxGroupResult info));
CJ_EXPORT void FfiCheckBoxGroupSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiCheckBoxGroupSetResponseRegionArray(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetUnSelectedColor(uint32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetMark(
    uint32_t strokeColor, double size, int32_t sizeUnit, double strokeWidth, int32_t strokeWidthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkCheckBoxGroupSetCheckboxShape(int32_t value);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_CHECKBOX_GROUP_FFI_H
