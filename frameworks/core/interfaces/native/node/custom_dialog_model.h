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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_CUSTOM_DIALOG_MODEL_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_CUSTOM_DIALOG_MODEL_H

#include "core/interfaces/arkoala/arkoala_api.h"

struct _ArkUIDialog {
    void* dialogHandle;
    void* contentHandle;
    ArkUI_Int32 alignment;
    ArkUI_Float32 offsetX;
    ArkUI_Float32 offsetY;
    ArkUI_Int32 isModal;
    ArkUI_Int32 autoCancel;
    ArkUI_Uint32 maskColor;
    ArkUIRect* maskRect;
    ArkUI_Uint32 backgroundColor;
    ArkUICornerRadius* cornerRadiusRect;
    ArkUI_Int32 gridCount;
    ArkUI_Int32 customStyle;
    ArkUI_Int32 showInSubWindow;
    ArkUI_Bool useCustomAnimation;
    bool (*onWillDissmissCall)(ArkUI_Int32);
};

namespace OHOS::Ace::NG::CustomDialog {
ArkUIDialogHandle CreateDialog();
void  DisposeDialog(ArkUIDialogHandle handler);
ArkUI_Int32  AttachDialogContent(ArkUIDialogHandle handler, ArkUINodeHandle contentNode);
ArkUI_Int32  DetachDialogContent(ArkUIDialogHandle handler, ArkUINodeHandle contentNode);
ArkUI_Int32  SetDialogContentAlignment(ArkUIDialogHandle handler,
    ArkUI_Int32 alignment, float offsetX, float offsetY);
ArkUI_Int32  ResetDialogContentAlignment(ArkUIDialogHandle handler);
ArkUI_Int32  SetDialogMode(ArkUIDialogHandle handler, bool useModalMode, bool autoCancel);
ArkUI_Int32  SetDialogMask(ArkUIDialogHandle handler, ArkUI_Uint32 maskColor, ArkUIRect* rect);
ArkUI_Int32 SetDialogBackgroundColor(ArkUIDialogHandle handler, ArkUI_Uint32 backgroundColor);
ArkUI_Int32 SetDialogCornerRadius(ArkUIDialogHandle handler, float topLeft, float topRight,
    float bottomLeft, float bottomRight);
ArkUI_Int32 SetDialogGridCount(ArkUIDialogHandle handler, ArkUI_Int32 gridCount);
ArkUI_Int32 SetDialogCustomStyle(ArkUIDialogHandle handler, bool customStyle);
ArkUI_Int32 UseDialogCustomAnimation(ArkUIDialogHandle handler, ArkUI_Bool useCustomAnimation);
ArkUI_Int32  ShowDialog(ArkUIDialogHandle handler, bool showInSubWindow);
ArkUI_Int32  CloseDialog(ArkUIDialogHandle handler);
ArkUI_Int32  RegiesterOnWillDialogDismiss(ArkUIDialogHandle handler, bool (*eventHandler)(ArkUI_Int32));
} // namespace OHOS::Ace::NG::CustomDialog

#endif