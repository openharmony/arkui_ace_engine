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
#include "base/geometry/dimension.h"

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
    ArkUI_Int32 enableCustomStyle;
    ArkUI_Int32 showInSubWindow;
    ArkUI_Bool enableCustomAnimation;
    bool (*onWillDismissCall)(ArkUI_Int32);
    void (*onWillDismissCallByNDK)(ArkUI_DialogDismissEvent*);
    void* userData;
    std::optional<ArkUI_Float32> keyboardAvoidDistanceValue;
    OHOS::Ace::DimensionUnit keyboardAvoidDistanceUnit;
};

namespace OHOS::Ace::NG::CustomDialog {
ArkUIDialogHandle CreateDialog();
void DisposeDialog(ArkUIDialogHandle handle);
ArkUI_Int32 SetDialogContent(ArkUIDialogHandle handle, ArkUINodeHandle contentNode);
ArkUI_Int32 RemoveDialogContent(ArkUIDialogHandle handle);
ArkUI_Int32 SetDialogContentAlignment(ArkUIDialogHandle handle,
    ArkUI_Int32 alignment, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY);
ArkUI_Int32 ResetDialogContentAlignment(ArkUIDialogHandle handle);
ArkUI_Int32 SetDialogModalMode(ArkUIDialogHandle handle, bool isModal);
ArkUI_Int32 SetDialogAutoCancel(ArkUIDialogHandle handle, bool autoCancel);
ArkUI_Int32 SetDialogMask(ArkUIDialogHandle handle, ArkUI_Uint32 maskColor, ArkUIRect* rect);
ArkUI_Int32 SetDialogBackgroundColor(ArkUIDialogHandle handle, ArkUI_Uint32 backgroundColor);
ArkUI_Int32 SetDialogCornerRadius(ArkUIDialogHandle handle, ArkUI_Float32 topLeft, ArkUI_Float32 topRight,
    ArkUI_Float32 bottomLeft, ArkUI_Float32 bottomRight);
ArkUI_Int32 SetDialogGridColumnCount(ArkUIDialogHandle handle, ArkUI_Int32 gridCount);
ArkUI_Int32 EnableDialogCustomStyle(ArkUIDialogHandle handle, bool enableCustomStyle);
ArkUI_Int32 EnableDialogCustomAnimation(ArkUIDialogHandle handle, bool enableCustomAnimation);
ArkUI_Int32 ShowDialog(ArkUIDialogHandle handle, bool showInSubWindow);
ArkUI_Int32 CloseDialog(ArkUIDialogHandle handle);
ArkUI_Int32 RegisterOnWillDialogDismiss(ArkUIDialogHandle handler, bool (*eventHandler)(ArkUI_Int32));
ArkUI_Int32 RegisterOnWillDialogDismissWithUserData(
    ArkUIDialogHandle handler, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event));
ArkUI_Int32 SetKeyboardAvoidDistance(ArkUIDialogHandle handle, float distance, ArkUI_Int32 unit);
} // namespace OHOS::Ace::NG::CustomDialog

#endif
