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

#ifndef OHOS_ACE_FRAMEWORK_CJ_CALENDAR_PICKER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CALENDAR_PICKER_FFI_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_action_sheet_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_datepicker_ffi.h"
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

struct NativeCalendarDialogOptions {
    NativeLength hintRadius;
    FfiTime selected;
    NativeOptional<void (*)(FfiTime)> onAccept;
    NativeOptional<void (*)()> onCancel;
    NativeOptional<void (*)(FfiTime)> onChange;
    uint32_t backgroundColor;
    int32_t backgroundBlurStyle;
    NativeOptional<NativePickerDialogButtonStyle> acceptButtonStyle;
    NativeOptional<NativePickerDialogButtonStyle> cancelButtonStyle;
    NativeOptional<void (*)()> onDidAppear;
    NativeOptional<void (*)()> onDidDisappear;
    NativeOptional<void (*)()> onWillAppear;
    NativeOptional<void (*)()> onWillDisappear;
    NativeOptional<NativeShadowOptions> shadow;
};

CJ_EXPORT void FfiOHOSAceFrameworkCalendarPickerCreate(double size, int32_t unit, FfiTime date);
CJ_EXPORT void FfiOHOSAceFrameworkCalendarPickerSetEdgeAlign(int32_t alignType, NativeOffset offset);
CJ_EXPORT void FfiOHOSAceFrameworkCalendarPickerSetTextStyle(
    uint32_t color, NativeLength size, const char* weight, const char* family, uint32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkCalendarPickerSetOnChange(void (*callback)(FfiTime));
CJ_EXPORT void FfiOHOSAceFrameworkCalendarPickerDialogShow(NativeCalendarDialogOptions options);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_CALENDAR_PICKER_FFI_H