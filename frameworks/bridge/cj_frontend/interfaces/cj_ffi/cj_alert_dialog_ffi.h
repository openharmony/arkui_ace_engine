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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_action_sheet_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
struct NativeAlertDialogButtonOptions {
    bool enabled;
    bool defaultFocus;
    int32_t* style;
    char* value;
    uint32_t* fontColor;
    uint32_t* backgroundColor;
    void (*action)();
    bool primary;
};

struct NativeAlertDialogParam {
    char* message;
    NativeOptionCString title;
    NativeOptionCString subtitle;
    NativeOptionBool autoCancel;
    NativeOptionCallBack cancel;
    NativeOptionInt32 alignment;
    NativeOptionOffset offset;
    NativeOptionInt32 gridCount;
    NativeOptionRect maskRect;
    NativeOptionBool showInSubWindow;
    NativeOptionBool isModal;
    NativeOptionUInt32 backgroundColor;
    NativeOptionInt32 backgroundBlurStyle;
    NativeOptionCallback1Param onWillDismiss;
    NativeOptionRadius cornerRadius;
    NativeOptionLength borderWidth;
    NativeOptionUInt32 borderColor;
    NativeOptionEdgeStyle borderStyle;
    NativeOptionLength width;
    NativeOptionLength height;
    NativeOptionInt64 transition;
    NativeOptionUInt32 textstyle;
};

struct CArrNativeAlertDialogButtonOptions {
    NativeAlertDialogButtonOptions* head;
    int32_t size;
};

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithConfirmShadowStyle(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm, int32_t shadowStyle);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithConfirmShadowOptions(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm, NativeShadowOptions shadowOptions);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithConfirm(
    NativeAlertDialogParam alertDialog, NativeAlertDialogButtonOptions confirm);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithButtonsShadowStyle(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton, int32_t shadowStyle);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithButtonsShadowOptions(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton,
    NativeShadowOptions shadowOptions);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithButtons(NativeAlertDialogParam alertDialog,
    NativeAlertDialogButtonOptions primaryButton, NativeAlertDialogButtonOptions secondaryButton);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithOptionsShadowStyle(NativeAlertDialogParam alertDialog,
    CArrNativeAlertDialogButtonOptions buttons, int32_t shadowStyle, int32_t buttonDirection);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithOptionsShadowOptions(NativeAlertDialogParam alertDialog,
    CArrNativeAlertDialogButtonOptions buttons, NativeShadowOptions shadowOptions, int32_t buttonDirection);

CJ_EXPORT void FfiOHOSShowAlertDialogParamWithOptions(
    NativeAlertDialogParam alertDialog, CArrNativeAlertDialogButtonOptions buttons, int32_t buttonDirection);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_ALERT_DIALOG_FFI_H
