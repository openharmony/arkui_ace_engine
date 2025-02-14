/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TIME_PICKER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TIME_PICKER_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_datepicker_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
struct FFiTimePickerResult {
    int64_t hour;
    int64_t minute;
    int64_t second;
};

struct NativeTimePickerDialogOptions {
    FfiTime selected;
    int32_t format;
    bool useMilitaryTime;
    NativePickerTextStyle disappearTextStyle;
    NativePickerTextStyle textStyle;
    NativePickerTextStyle selectedTextStyle;
    NativeOptional<NativePickerDialogButtonStyle> acceptButtonStyle;
    NativeOptional<NativePickerDialogButtonStyle> cancelButtonStyle;
    int32_t alignment;
    NativeOffset offset;
    NativeRectangle maskRect;
    NativeOptional<void (*)(FfiTime)> onAccept;
    NativeOptional<void (*)()> onCancel;
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

CJ_EXPORT void FfiOHOSAceFrameworkTimePickerCreate(FfiTime selected, int32_t format);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetUseMilitaryTime(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetDisappearTextStyle(NativePickerTextStyle value);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetTextStyle(NativePickerTextStyle value);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetSelectedTextStyle(NativePickerTextStyle value);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetLoop(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetEnableHapticFeedback(bool enable);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerDateTimeOptions(
    const char* hourType, const char* minuteType, const char* secondType);
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerSetOnChange(void (*callback)(int64_t hour, int64_t minute, int64_t second));
CJ_EXPORT void FfiOHOSAceFrameworkTimePickerDialogShow(NativeTimePickerDialogOptions options);
};
#endif // OHOS_ACE_FRAMEWORK_CJ_TIME_PICKER_FFI_H