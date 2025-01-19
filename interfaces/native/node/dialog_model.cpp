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
#include "dialog_model.h"

#include "node_model.h"

#include "base/error/error_code.h"

namespace OHOS::Ace::DialogModel {
ArkUI_NativeDialogHandle Create()
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    auto dialog = impl->getDialogAPI()->create();
    return new ArkUI_NativeDialog({ dialog });
}

void Dispose(ArkUI_NativeDialogHandle handle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return;
    }
    impl->getDialogAPI()->dispose(handle->controller);
    delete handle;
    handle = nullptr;
}

int32_t SetContent(ArkUI_NativeDialogHandle handle, ArkUI_NodeHandle content)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle || !content) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setContent(handle->controller, content->uiNodeHandle);
}

int32_t RemoveContent(ArkUI_NativeDialogHandle handle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->removeContent(handle->controller);
}

int32_t SetContentAlignment(ArkUI_NativeDialogHandle handle, int32_t alignment, float offsetX, float offsetY)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setContentAlignment(handle->controller,
        alignment, offsetX, offsetY);
}

int32_t ResetContentAlignment(ArkUI_NativeDialogHandle handle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->resetContentAlignment(handle->controller);
}

int32_t SetModalMode(ArkUI_NativeDialogHandle handle, bool isModal)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setModalMode(handle->controller, isModal);
}

int32_t SetAutoCancel(ArkUI_NativeDialogHandle handle, bool autoCancel)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setAutoCancel(handle->controller, autoCancel);
}

int32_t SetMask(ArkUI_NativeDialogHandle handle, uint32_t maskColor, const ArkUI_Rect* maskRect)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (maskRect) {
        ArkUIRect rect = { maskRect->x, maskRect->y, maskRect->width, maskRect->height };
        return impl->getDialogAPI()->setMask(handle->controller, maskColor, &rect);
    } else {
        return impl->getDialogAPI()->setMask(handle->controller, maskColor, nullptr);
    }
}

int32_t SetBackgroundColor(ArkUI_NativeDialogHandle handle, uint32_t backgroundColor)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBackgroundColor(handle->controller, backgroundColor);
}

int32_t SetCornerRadius(ArkUI_NativeDialogHandle handle, float topLeft, float topRight,
    float bottomLeft, float bottomRight)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setCornerRadius(handle->controller,
        topLeft, topRight, bottomLeft, bottomRight);
}

int32_t SetGridColumnCount(ArkUI_NativeDialogHandle handle, int32_t gridCount)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setGridColumnCount(handle->controller, gridCount);
}

int32_t EnableCustomStyle(ArkUI_NativeDialogHandle handle, bool enableCustomStyle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->enableCustomStyle(handle->controller, enableCustomStyle);
}

int32_t EnableCustomAnimation(ArkUI_NativeDialogHandle handle, bool enableCustomAnimation)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->enableCustomAnimation(handle->controller, enableCustomAnimation);
}

int32_t Show(ArkUI_NativeDialogHandle handle, bool showInSubWindow)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->show(handle->controller, showInSubWindow);
}

int32_t Close(ArkUI_NativeDialogHandle handle)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->close(handle->controller);
}

int32_t RegisterOnWillDismiss(ArkUI_NativeDialogHandle handle, ArkUI_OnWillDismissEvent eventHandler)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnWillDismiss(handle->controller, eventHandler);
}

int32_t RegisterOnWillDismissWithUserData(
    ArkUI_NativeDialogHandle handle, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    int result = impl->getDialogAPI()->registerOnWillDismissWithUserData(handle->controller, userData, callback);
    return result;
}

int32_t SetKeyboardAvoidDistance(
    ArkUI_NativeDialogHandle handle, float distance, ArkUI_LengthMetricUnit unit)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_CAPI_INIT_ERROR;
    }
    if (!handle) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (unit < ARKUI_LENGTH_METRIC_UNIT_DEFAULT || unit > ARKUI_LENGTH_METRIC_UNIT_FP) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    int result = impl->getDialogAPI()->setKeyboardAvoidDistance(handle->controller, distance, unit);
    return result;
}

int32_t SetLevelMode(ArkUI_NativeDialogHandle handle, ArkUI_LevelMode levelMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_CAPI_INIT_ERROR;
    }
    if (!handle) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(levelMode) < static_cast<int32_t>(ARKUI_LEVEL_MODE_OVERLAY) ||
        static_cast<int32_t>(levelMode) > static_cast<int32_t>(ARKUI_LEVEL_MODE_EMBEDDED)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelMode(handle->controller, static_cast<int32_t>(levelMode));
}

int32_t SetLevelUniqueId(ArkUI_NativeDialogHandle handle, int32_t uniqueId)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_CAPI_INIT_ERROR;
    }
    if (!handle || uniqueId < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelUniqueId(handle->controller, uniqueId);
}

int32_t SetImmersiveMode(ArkUI_NativeDialogHandle handle, ArkUI_ImmersiveMode immersiveMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_CAPI_INIT_ERROR;
    }
    if (!handle) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(immersiveMode) < static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_DEFAULT) ||
        static_cast<int32_t>(immersiveMode) > static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_FULL)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setImmersiveMode(handle->controller, static_cast<int32_t>(immersiveMode));
}
} // namespace OHOS::Ace::NG::DialogModel

#ifdef __cplusplus
extern "C" {
#endif

void OH_ArkUI_DialogDismissEvent_SetShouldBlockDismiss(ArkUI_DialogDismissEvent* event, bool shouldBlockDismiss)
{
    if (!event) {
        return;
    }
    event->BlockDismiss = shouldBlockDismiss;
}

void* OH_ArkUI_DialogDismissEvent_GetUserData(ArkUI_DialogDismissEvent* event)
{
    if (!event) {
        return nullptr;
    }
    return event->userData;
}

int32_t OH_ArkUI_DialogDismissEvent_GetDismissReason(ArkUI_DialogDismissEvent* event)
{
    if (!event) {
        return -1;
    }
    return event->reason;
}

#ifdef __cplusplus
};
#endif