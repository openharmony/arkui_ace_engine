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
#include "frameworks/core/components/common/properties/shadow.h"
#include "frameworks/core/components/dialog/dialog_properties.h"

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
    ArkUI_Int32 levelMode;
    ArkUI_Int32 levelUniqueId;
    ArkUI_Int32 immersiveMode;
    ArkUI_Float64 levelOrder;
    void* onWillAppearData;
    void* onDidAppearData;
    void* onWillDisappearData;
    void* onDidDisappearData;
    void (*onWillAppear)(void*);
    void (*onDidAppear)(void*);
    void (*onWillDisappear)(void*);
    void (*onDidDisappear)(void*);
    ArkUIBorderWidth* borderWidthEdgeWidths;
    OHOS::Ace::DimensionUnit borderWidthUnit;
    ArkUIBorderColor* borderColors;
    ArkUIBorderStyle* borderStyles;
    std::optional<ArkUI_Float32> widthValue;
    OHOS::Ace::DimensionUnit widthUnit;
    std::optional<ArkUI_Float32> heightValue;
    OHOS::Ace::DimensionUnit heightUnit;
    OHOS::Ace::ShadowStyle shadowStyle;
    OHOS::Ace::Shadow customShadow;
    ArkUI_Int32 blurStyle;
    OHOS::Ace::KeyboardAvoidMode keyboardAvoidMode;
    ArkUI_Bool enableHoverMode;
    OHOS::Ace::HoverModeAreaType hoverModeAreaType;
    ArkUI_Int32 focusable;
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
ArkUI_Int32 SetLevelMode(ArkUIDialogHandle handle, ArkUI_Int32 mode);
ArkUI_Int32 SetLevelUniqueId(ArkUIDialogHandle handle, ArkUI_Int32 uniqueId);
ArkUI_Int32 SetImmersiveMode(ArkUIDialogHandle handle, ArkUI_Int32 mode);
ArkUI_Int32 SetLevelOrder(ArkUIDialogHandle handle, ArkUI_Float64 levelOrder);
ArkUI_Int32 RegisterOnWillAppearDialog(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData));
ArkUI_Int32 RegisterOnDidAppearDialog(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData));
ArkUI_Int32 RegisterOnWillDisappearDialog(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData));
ArkUI_Int32 RegisterOnDidDisappearDialog(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData));
ArkUI_Int32 OpenCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId));
ArkUI_Int32 CloseCustomDialog(ArkUI_Int32 dialogId);
ArkUI_Int32 UpdateCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId));
ArkUI_Int32 SetDialogSubwindowMode(ArkUIDialogHandle handle, bool showInSubWindow);
ArkUI_Int32 SetDialogBorderWidth(ArkUIDialogHandle handle, ArkUI_Float32 top, ArkUI_Float32 right, ArkUI_Float32 bottom,
    ArkUI_Float32 left, ArkUI_Int32 unit);
ArkUI_Int32 SetDialogBorderColor(
    ArkUIDialogHandle handle, ArkUI_Uint32 top, ArkUI_Uint32 right, ArkUI_Uint32 bottom, ArkUI_Uint32 left);
ArkUI_Int32 SetDialogBorderStyle(
    ArkUIDialogHandle controllerHandler, ArkUI_Int32 top, ArkUI_Int32 right, ArkUI_Int32 bottom, ArkUI_Int32 left);
ArkUI_Int32 SetWidth(ArkUIDialogHandle handle, float width, ArkUI_Int32 unit);
ArkUI_Int32 SetHeight(ArkUIDialogHandle handle, float height, ArkUI_Int32 unit);
ArkUI_Int32 SetShadow(ArkUIDialogHandle controllerHandler, ArkUI_Int32 shadow);
ArkUI_Int32 SetDialogCustomShadow(
    ArkUIDialogHandle controllerHandler, const ArkUIInt32orFloat32* shadows, ArkUI_Int32 length);
ArkUI_Int32 SetBackgroundBlurStyle(ArkUIDialogHandle controllerHandler, ArkUI_Int32 blurStyle);
ArkUI_Int32 SetKeyboardAvoidMode(ArkUIDialogHandle controllerHandler, ArkUI_Int32 keyboardAvoidMode);
ArkUI_Int32 EnableHoverMode(ArkUIDialogHandle controllerHandler, bool enableHoverMode);
ArkUI_Int32 SetHoverModeArea(ArkUIDialogHandle controllerHandler, ArkUI_Int32 hoverModeAreaType);
ArkUI_Int32 SetFocusable(ArkUIDialogHandle handle, bool focusable);
} // namespace OHOS::Ace::NG::CustomDialog

#endif
