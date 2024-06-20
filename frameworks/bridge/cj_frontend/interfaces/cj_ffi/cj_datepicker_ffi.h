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

#ifndef OHOS_ACE_FRAMEWORK_CJ_DATA_PANEL_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_DATA_PANEL_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct FFiDatePickerResult {
    int32_t year;
    int32_t month;
    int32_t day;
};

struct FfiTime {
    int64_t year;
    int64_t month;
    int64_t day;
    int64_t hour;
    int64_t min;
    int64_t sec;
    int64_t nsec;
};

CJ_EXPORT void FfiOHOSAceFrameworkDatePickerCreate(FfiTime startDate, FfiTime endDate, FfiTime selectedDate);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetLunar(bool isLunar);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerUseMilitaryTime(bool isUseMilitaryTime);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetOnChange(void (*callback)(int32_t year, int32_t month, int32_t day));
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetOnDateChange(
    void (*callback)(int32_t year, int32_t month, int32_t day));
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetDisappearTextStyle(uint32_t color, double size,
    int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetSelectedTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetDefaultAttributes(void);

};
#endif // OHOS_ACE_FRAMEWORK_CJ_DATA_FFI_H