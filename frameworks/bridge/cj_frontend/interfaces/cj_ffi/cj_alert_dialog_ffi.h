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

#ifndef OHOS_ACE_FRAMEWORK_CJ_ALERT_DIALOG_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_ALERT_DIALOG_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct NativeRectangle {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    double width;
    int32_t widthUnit;
    double height;
    int32_t heightUnit;
};

struct NativeAlertDialogButtonOptions {
    bool enabled;
    bool defaultFocus;
    int32_t* style;
    char* value;
    uint32_t* fontColor;
    uint32_t* backgroundColor;
    void (*action)();
};

struct NativeAlertDialogParam {
    char* title;
    char* subtitle;
    char* message;
    bool autoCancel;
    void (*cancel)();
    int32_t alignment;
    NativeOffset offset;
    int32_t gridCount;
    NativeRectangle maskRect;
    bool showInSubWindow;
    bool isModal;
    uint32_t backgroundColor;
    int32_t backgroundBlurStyle;
};

struct CArrNativeAlertDialogButtonOptions {
    NativeAlertDialogButtonOptions* head;
    int32_t size;
};

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithConfirm(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithButtons(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithOptions(
    NativeAlertDialogParam alertDialog, CArrNativeAlertDialogButtonOptions buttons, int32_t buttonDirection);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_ALERT_DIALOG_FFI_H
