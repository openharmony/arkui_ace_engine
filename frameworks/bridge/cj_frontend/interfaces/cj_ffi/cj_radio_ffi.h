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

#ifndef OHOS_ACE_FRAMEWORK_CJ_RADIO_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_RADIO_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkRadioWithIndicatorCreate(
    const char* group, const char* value, int32_t indicatorType, void (*indicatorBuilder)());
CJ_EXPORT void FfiOHOSAceFrameworkRadioCreate(const char* group, const char* value);
CJ_EXPORT void FfiOHOSAceFrameworkRadioChecked(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkRadioSetStyle(
    uint32_t checkedBackgroundColor, uint32_t uncheckedBorderColor, uint32_t indicatorColor);
CJ_EXPORT void FfiOHOSAceFrameworkRadioSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRadioSetPadding(double padding, uint32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkRadioSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkRadioSetHoverEffect(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkRadioOnChange(void (*callback)(bool isChecked));
CJ_EXPORT void FfiRadioSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiRadioSetResponseRegionArray(VectorStringPtr vecContent);
};

#endif // OHOS_ACE_FRAMEWORK_CJ_RADIO_FFI_H
