/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_model.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG {
namespace {
ArkUIDialogHandle CreateDialog()
{
    return CustomDialog::CreateDialog();
}

void DisposeDialog(ArkUIDialogHandle handle)
{
    CustomDialog::DisposeDialog(handle);
}

ArkUI_Int32 SetDialogContent(ArkUIDialogHandle handle, ArkUINodeHandle contentNode)
{
    return CustomDialog::SetDialogContent(handle, contentNode);
}

ArkUI_Int32 RemoveDialogContent(ArkUIDialogHandle handle)
{
    return CustomDialog::RemoveDialogContent(handle);
}

ArkUI_Int32 SetDialogContentAlignment(
    ArkUIDialogHandle handle, ArkUI_Int32 alignment, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
{
    return CustomDialog::SetDialogContentAlignment(handle, alignment, offsetX, offsetY);
}

ArkUI_Int32 ResetDialogContentAlignment(ArkUIDialogHandle handle)
{
    return CustomDialog::ResetDialogContentAlignment(handle);
}

ArkUI_Int32 SetDialogModalMode(ArkUIDialogHandle handle, ArkUI_Bool isModal)
{
    return CustomDialog::SetDialogModalMode(handle, isModal);
}

ArkUI_Int32 SetDialogAutoCancel(ArkUIDialogHandle handle, ArkUI_Bool autoCancel)
{
    return CustomDialog::SetDialogAutoCancel(handle, autoCancel);
}

ArkUI_Int32 SetDialogMask(ArkUIDialogHandle handle, ArkUI_Uint32 maskColor, ArkUIRect* rect)
{
    return CustomDialog::SetDialogMask(handle, maskColor, rect);
}

ArkUI_Int32 SetDialogBackgroundColor(ArkUIDialogHandle handle, uint32_t backgroundColor)
{
    return CustomDialog::SetDialogBackgroundColor(handle, backgroundColor);
}

ArkUI_Int32 SetDialogBackgroundColorWithColorSpace(
    ArkUIDialogHandle handle, uint32_t backgroundColor, int32_t colorSpace)
{
    return CustomDialog::SetDialogBackgroundColor(handle, backgroundColor);
}

ArkUI_Int32 SetDialogCornerRadius(
    ArkUIDialogHandle handle, float topLeft, float topRight, float bottomLeft, float bottomRight)
{
    return CustomDialog::SetDialogCornerRadius(handle, topLeft, topRight, bottomLeft, bottomRight);
}

ArkUI_Int32 SetDialogGridColumnCount(ArkUIDialogHandle handle, int32_t gridCount)
{
    return CustomDialog::SetDialogGridColumnCount(handle, gridCount);
}

ArkUI_Int32 EnableDialogCustomStyle(ArkUIDialogHandle handle, ArkUI_Bool enableCustomStyle)
{
    return CustomDialog::EnableDialogCustomStyle(handle, enableCustomStyle);
}

ArkUI_Int32 EnableDialogCustomAnimation(ArkUIDialogHandle handle, ArkUI_Bool enableCustomAnimation)
{
    return CustomDialog::EnableDialogCustomAnimation(handle, enableCustomAnimation);
}

ArkUI_Int32 ShowDialog(ArkUIDialogHandle handle, ArkUI_Bool showInSubWindow)
{
    return CustomDialog::ShowDialog(handle, showInSubWindow);
}

ArkUI_Int32 CloseDialog(ArkUIDialogHandle handle)
{
    return CustomDialog::CloseDialog(handle);
}

// Register closing event
ArkUI_Int32 RegisterOnWillDialogDismiss(ArkUIDialogHandle handle, bool (*eventHandler)(ArkUI_Int32))
{
    return CustomDialog::RegisterOnWillDialogDismiss(handle, eventHandler);
}

// Register closing event
ArkUI_Int32 RegisterOnWillDismissWithUserData(
    ArkUIDialogHandle handler, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event))
{
    return CustomDialog::RegisterOnWillDialogDismissWithUserData(handler, userData, callback);
}

ArkUI_Int32 GetDialogState(ArkUIDialogHandle handle, ArkUI_Int32* dialogState)
{
    return CustomDialog::GetDialogState(handle, dialogState);
}

ArkUI_Int32 SetKeyboardAvoidDistance(ArkUIDialogHandle handle, float distance, ArkUI_Int32 unit)
{
    return CustomDialog::SetKeyboardAvoidDistance(handle, distance, unit);
}

ArkUI_Int32 SetDialogLevelMode(ArkUIDialogHandle handle, ArkUI_Int32 mode)
{
    return CustomDialog::SetLevelMode(handle, mode);
}

ArkUI_Int32 SetDialogLevelUniqueId(ArkUIDialogHandle handle, ArkUI_Int32 uniqueId)
{
    return CustomDialog::SetLevelUniqueId(handle, uniqueId);
}

ArkUI_Int32 SetDialogImmersiveMode(ArkUIDialogHandle handle, ArkUI_Int32 mode)
{
    return CustomDialog::SetImmersiveMode(handle, mode);
}

ArkUI_Int32 SetLevelOrder(ArkUIDialogHandle handle, ArkUI_Float64 levelOrder)
{
    return CustomDialog::SetLevelOrder(handle, levelOrder);
}

ArkUI_Int32 RegisterOnWillAppear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnWillAppearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnDidAppear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnDidAppearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnWillDisappear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnWillDisappearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnDidDisappear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnDidDisappearDialog(handle, userData, callback);
}

ArkUI_Int32 SetDialogBorderWidth(ArkUIDialogHandle handle, ArkUI_Float32 top, ArkUI_Float32 right, ArkUI_Float32 bottom,
    ArkUI_Float32 left, ArkUI_Int32 unit)
{
    return CustomDialog::SetDialogBorderWidth(handle, top, right, bottom, left, unit);
}

ArkUI_Int32 SetDialogBorderColor(ArkUIDialogHandle handle, uint32_t top, uint32_t right, uint32_t bottom, uint32_t left)
{
    return CustomDialog::SetDialogBorderColor(handle, top, right, bottom, left);
}

ArkUI_Int32 SetDialogBorderStyle(ArkUIDialogHandle handle, int32_t top, int32_t right, int32_t bottom, int32_t left)
{
    return CustomDialog::SetDialogBorderStyle(handle, top, right, bottom, left);
}

ArkUI_Int32 SetDialogWidth(ArkUIDialogHandle handle, float width, ArkUI_Int32 unit)
{
    return CustomDialog::SetWidth(handle, width, unit);
}

ArkUI_Int32 SetDialogHeight(ArkUIDialogHandle handle, float height, ArkUI_Int32 unit)
{
    return CustomDialog::SetHeight(handle, height, unit);
}

ArkUI_Int32 SetDialogShadow(ArkUIDialogHandle handle, ArkUI_Int32 shadow)
{
    return CustomDialog::SetShadow(handle, shadow);
}

ArkUI_Int32 SetDialogCustomShadow(ArkUIDialogHandle handle, const ArkUIInt32orFloat32* shadows, ArkUI_Int32 length)
{
    return CustomDialog::SetDialogCustomShadow(handle, shadows, length);
}

ArkUI_Int32 SetDialogBackgroundBlurStyle(ArkUIDialogHandle handle, ArkUI_Int32 blurStyle)
{
    return CustomDialog::SetBackgroundBlurStyle(handle, blurStyle);
}

ArkUI_Int32 SetDialogKeyboardAvoidMode(ArkUIDialogHandle handle, ArkUI_Int32 keyboardAvoidMode)
{
    return CustomDialog::SetKeyboardAvoidMode(handle, keyboardAvoidMode);
}

ArkUI_Int32 EnableDialogHoverMode(ArkUIDialogHandle handle, ArkUI_Bool enableHoverMode)
{
    return CustomDialog::EnableHoverMode(handle, enableHoverMode);
}

ArkUI_Int32 SetDialogHoverModeArea(ArkUIDialogHandle handle, ArkUI_Int32 hoverModeAreaType)
{
    return CustomDialog::SetHoverModeArea(handle, hoverModeAreaType);
}

ArkUI_Int32 SetDialogFocusable(ArkUIDialogHandle handle, ArkUI_Bool focusable)
{
    return CustomDialog::SetFocusable(handle, focusable);
}

ArkUI_Int32 OpenCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId))
{
    return CustomDialog::OpenCustomDialog(handle, callback);
}

ArkUI_Int32 UpdateCustomDialog(ArkUIDialogHandle handle, void (*callback)(int32_t dialogId))
{
    return CustomDialog::UpdateCustomDialog(handle, callback);
}

ArkUI_Int32 CloseCustomDialog(ArkUI_Int32 dialogId)
{
    return CustomDialog::CloseCustomDialog(dialogId);
}

ArkUI_Int32 SetDialogSubwindowMode(ArkUIDialogHandle handle, ArkUI_Bool showInSubWindow)
{
    return CustomDialog::SetDialogSubwindowMode(handle, showInSubWindow);
}

ArkUI_Int32 SetDialogDisplayModeInSubWindow(ArkUIDialogHandle handle, ArkUI_Int32 displayModeInSubWindow)
{
    return CustomDialog::SetDialogDisplayModeInSubWindow(handle, displayModeInSubWindow);
}

ArkUI_Int32 SetSystemMaterial(ArkUIDialogHandle handle, ArkUI_ImmersiveMaterial* material)
{
    return CustomDialog::SetSystemMaterial(handle, material);
}

ArkUI_Int32 SetBackgroundBlurStyleOptions(ArkUIDialogHandle handle, ArkUI_Int32 (*intArray)[3], ArkUI_Float32 scale,
    ArkUI_Uint32 (*uintArray)[3], ArkUI_Bool isValidColor)
{
    return CustomDialog::SetBackgroundBlurStyleOptions(handle, intArray, scale, uintArray, isValidColor);
}

ArkUI_Int32 SetBackgroundEffect(ArkUIDialogHandle handle, ArkUI_Float32 (*floatArray)[3], ArkUI_Int32 (*intArray)[2],
    ArkUI_Uint32 (*uintArray)[4], ArkUI_Bool (*boolArray)[2])
{
    return CustomDialog::SetBackgroundEffect(handle, floatArray, intArray, uintArray, boolArray);
}

ArkUI_Int32 OpenCustomDialogWithErrorCallback(
    ArkUIDialogHandle handle, void* userData, void (*callback)(int32_t errorCode, int32_t dialogId, void* userData))
{
    return CustomDialog::OpenCustomDialogWithErrorCallback(handle, userData, callback);
}
} // namespace

const ArkUIDialogAPI* GetDialogAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDialogAPI dialogImpl = {
        .create = CreateDialog,
        .dispose = DisposeDialog,
        .setContent = SetDialogContent,
        .removeContent = RemoveDialogContent,
        .setContentAlignment = SetDialogContentAlignment,
        .resetContentAlignment = ResetDialogContentAlignment,
        .setModalMode = SetDialogModalMode,
        .setAutoCancel = SetDialogAutoCancel,
        .setMask = SetDialogMask,
        .setBackgroundColor = SetDialogBackgroundColor,
        .setBackgroundColorWIthColorSpace = SetDialogBackgroundColorWithColorSpace,
        .setCornerRadius = SetDialogCornerRadius,
        .setGridColumnCount = SetDialogGridColumnCount,
        .enableCustomStyle = EnableDialogCustomStyle,
        .enableCustomAnimation = EnableDialogCustomAnimation,
        .show = ShowDialog,
        .close = CloseDialog,
        .registerOnWillDismiss = RegisterOnWillDialogDismiss,
        .registerOnWillDismissWithUserData = RegisterOnWillDismissWithUserData,
        .getState = GetDialogState,
        .setKeyboardAvoidDistance = SetKeyboardAvoidDistance,
        .setLevelMode = SetDialogLevelMode,
        .setLevelUniqueId = SetDialogLevelUniqueId,
        .setImmersiveMode = SetDialogImmersiveMode,
        .setLevelOrder = SetLevelOrder,
        .registerOnWillAppear = RegisterOnWillAppear,
        .registerOnDidAppear = RegisterOnDidAppear,
        .registerOnWillDisappear = RegisterOnWillDisappear,
        .registerOnDidDisappear = RegisterOnDidDisappear,
        .setBorderWidth = SetDialogBorderWidth,
        .setBorderColor = SetDialogBorderColor,
        .setBorderStyle = SetDialogBorderStyle,
        .setWidth = SetDialogWidth,
        .setHeight = SetDialogHeight,
        .setShadow = SetDialogShadow,
        .setCustomShadow = SetDialogCustomShadow,
        .setBackgroundBlurStyle = SetDialogBackgroundBlurStyle,
        .setKeyboardAvoidMode = SetDialogKeyboardAvoidMode,
        .enableHoverMode = EnableDialogHoverMode,
        .setHoverModeArea = SetDialogHoverModeArea,
        .setFocusable = SetDialogFocusable,
        .openCustomDialog = OpenCustomDialog,
        .updateCustomDialog = UpdateCustomDialog,
        .closeCustomDialog = CloseCustomDialog,
        .setSubwindowMode = SetDialogSubwindowMode,
        .setDisplayModeInSubWindow = SetDialogDisplayModeInSubWindow,
        .setSystemMaterial = SetSystemMaterial,
        .setBackgroundBlurStyleOptions = SetBackgroundBlurStyleOptions,
        .setBackgroundEffect = SetBackgroundEffect,
        .openCustomDialogWithErrorCallback = OpenCustomDialogWithErrorCallback,
    };
    CHECK_INITIALIZED_FIELDS_END(dialogImpl, 0, 0, 0); // don't move this line
    return &dialogImpl;
}

const CJUIDialogAPI* GetCJUIDialogAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDialogAPI dialogImpl = {
        .create = CreateDialog,
        .dispose = DisposeDialog,
        .setContent = SetDialogContent,
        .removeContent = RemoveDialogContent,
        .setContentAlignment = SetDialogContentAlignment,
        .resetContentAlignment = ResetDialogContentAlignment,
        .setModalMode = SetDialogModalMode,
        .setAutoCancel = SetDialogAutoCancel,
        .setMask = SetDialogMask,
        .setBackgroundColor = SetDialogBackgroundColor,
        .setBackgroundColorWithColorSpace = SetDialogBackgroundColorWithColorSpace,
        .setCornerRadius = SetDialogCornerRadius,
        .setGridColumnCount = SetDialogGridColumnCount,
        .enableCustomStyle = EnableDialogCustomStyle,
        .enableCustomAnimation = EnableDialogCustomAnimation,
        .show = ShowDialog,
        .close = CloseDialog,
        .registerOnWillDismiss = RegisterOnWillDialogDismiss,
    };
    CHECK_INITIALIZED_FIELDS_END(dialogImpl, 0, 0, 0); // don't move this line
    return &dialogImpl;
}
} // namespace OHOS::Ace::NG
