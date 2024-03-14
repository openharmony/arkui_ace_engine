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

#ifndef ARKUI_NATIVE_NODE_DIALOG_MODEL_H
#define ARKUI_NATIVE_NODE_DIALOG_MODEL_H

#include "native_dialog.h"
#include "native_type.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_NativeDialog {
    ArkUIDialogHandle controller = nullptr;
};

#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::DialogModel {
ArkUI_NativeDialogHandler Create();
void Dispose(ArkUI_NativeDialogHandler handler);
int32_t AttachContent(ArkUI_NativeDialogHandler handler, ArkUI_NodeHandle content);
int32_t DetachContent(ArkUI_NativeDialogHandler handler, ArkUI_NodeHandle content);
int32_t SetContentAlignment(ArkUI_NativeDialogHandler handler, int32_t alignment, float offsetX, float offsetY);
int32_t ResetContentAlignment(ArkUI_NativeDialogHandler handler);
int32_t SetMode(ArkUI_NativeDialogHandler handler, bool useModalMode, bool autoCancel);
int32_t SetMask(ArkUI_NativeDialogHandler handler, uint32_t maskColor, const ArkUI_Rect* rect);
int32_t SetBackgroundColor(ArkUI_NativeDialogHandler handler, uint32_t backgroundColor);
int32_t SetCornerRadius(ArkUI_NativeDialogHandler handler, float topLeft, float topRight,
    float bottomLeft, float bottomRight);
int32_t SetGridCount(ArkUI_NativeDialogHandler handler, int32_t gridCount);
int32_t SetCustomStyle(ArkUI_NativeDialogHandler handler, bool customStyle);
int32_t UseCustomAnimation(ArkUI_NativeDialogHandler handler, bool useCustomAnimation);
int32_t RegiesterOnWillDismiss(ArkUI_NativeDialogHandler handler, OnWillDismissEvent eventHandler);
int32_t Show(ArkUI_NativeDialogHandler handler, bool showInSubWindow);
int32_t Close(ArkUI_NativeDialogHandler handler);
} // namespace OHOS::Ace::NG::DialogModel

#endif // ARKUI_NATIVE_NODE_DIALOG_MODEL_H