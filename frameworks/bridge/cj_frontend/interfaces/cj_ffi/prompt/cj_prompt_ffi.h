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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_alert_dialog_ffi.h"

extern "C" {
typedef struct CButtonInfo {
    const char* text;
    uint32_t textColor;
} CButtonInfo;

struct NativeBaseOption {
    NativeRectangle maskRect;
    int32_t alignment;
    NativeOffset offset;
    bool isModal;
    bool showInSubWindow;
};

using ShowDialogCallBack = void (*)(int32_t, int32_t);
using ShowActionMenuCallBack = void (*)(int32_t, int32_t);

CJ_EXPORT void* FfiPromptMallocButtons(int64_t size);
CJ_EXPORT void FfiPromptShowToast(const char* message, int32_t duration, const char* bottom, int32_t mode);
CJ_EXPORT void FfiPromptShowDialog(const char* title, const char* message, int32_t size,
    CButtonInfo* buttonsInfo, ShowDialogCallBack callback);
CJ_EXPORT void FfiPromptShowActionMenu(
    const char* title, int32_t buttonSize, CButtonInfo* buttonsInfo, ShowActionMenuCallBack callback);
CJ_EXPORT void FfiPromptOpenCustomDialog(void(*builder)(), NativeBaseOption options, void(*callback)(int32_t id));
CJ_EXPORT void FfiPromptCloseCustomDialog(int32_t id);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PROMPT_FFI_H
