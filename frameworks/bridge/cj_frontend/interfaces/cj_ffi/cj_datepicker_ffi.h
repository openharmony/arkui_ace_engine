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

#ifndef OHOS_ACE_FRAMEWORK_CJ_DATA_PICKER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_DATA_PICKER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_action_sheet_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

template<typename T>
struct NativeOptional {
    bool hasValue;
    T value;
};

extern "C" {
struct NativePickerDialogButtonStyle {
    NativeOptional<int32_t> type;
    NativeOptional<int32_t> style;
    NativeOptional<int32_t> role;
    NativeOptional<NativeLength> fontSize;
    NativeOptional<uint32_t> fontColor;
    NativeOptional<char*> fontWeight;
    NativeOptional<int32_t> fontStyle;
    NativeOptional<char*> fontFamily;
    NativeOptional<uint32_t> backgroundColor;
    NativeOptional<NativeBorderRadiuses> borderRadius;
    NativeOptional<bool> primary;
};

struct FFiDatePickerResult {
    int64_t year;
    int64_t month;
    int64_t day;
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

struct NativeOptionFfiTime {
    bool hasValue;
    FfiTime value;
};

struct NativeOptionDateTime {
    bool hasValue;
    const char* hour;
    const char* min;
};

struct NativePickerTextStyle {
    bool hasValue;
    uint32_t color;
    double size;
    uint32_t unit;
    const char* weight;
    const char* family;
    uint32_t style;
};

struct NativeDateDialogOptions {
    NativeOptionFfiTime start;
    NativeOptionFfiTime end;
    NativeOptionFfiTime selected;
    bool lunar;
    bool showTime;
    bool useMilitaryTime;
    bool lunarSwitch;
    NativePickerTextStyle disappearTextStyle;
    NativePickerTextStyle textStyle;
    NativePickerTextStyle selectedTextSytle;
    NativeOptional<NativePickerDialogButtonStyle> acceptButtonStyle;
    NativeOptional<NativePickerDialogButtonStyle> cancelButtonStyle;
    uint32_t alignment;
    NativeOptionOffset offset;
    NativeOptionRect maskRect;
    NativeOptional<void (*)()> onCancel;
    NativeOptional<void (*)(FfiTime)> onAccept;
    NativeOptional<void (*)(FfiTime)> onChange;
    uint32_t backgroundColor;
    int32_t backgroundBlurStyle;
    NativeOptional<void (*)()> onDidAppear;
    NativeOptional<void (*)()> onDidDisappear;
    NativeOptional<void (*)()> onWillAppear;
    NativeOptional<void (*)()> onWillDisappear;
    NativeOptional<NativeShadowOptions> shadow;
    NativeOptionDateTime dateTimeOptions;
};

CJ_EXPORT void FfiOHOSAceFrameworkDatePickerCreate(FfiTime startDate, FfiTime endDate, FfiTime selectedDate);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerCreateWithChangeEvent(
    FfiTime startDate, FfiTime endDate, FfiTime selectedDate, void (*callback)(FfiTime selectedDate));
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetLunar(bool isLunar);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerUseMilitaryTime(bool isUseMilitaryTime);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetOnChange(void (*callback)(int64_t year, int64_t month, int64_t day));
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetOnDateChange(void (*callback)(int64_t year, int64_t month, int64_t day));
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetDisappearTextStyle(uint32_t color, double size,
    int32_t unit, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetSelectedTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetDefaultAttributes(void);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerSetOpacity(double opacity);
CJ_EXPORT void FfiOHOSAceFrameworkDatePickerDialogShow(NativeDateDialogOptions options);

};
#endif // OHOS_ACE_FRAMEWORK_CJ_DATA_FFI_H