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
#include "native_type.h"
#include "node_model.h"

#include "base/error/error_code.h"

namespace OHOS::Ace::DialogModel {
ArkUI_NativeDialogHandler Create()
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return nullptr;
    }
    auto dialog = impl->getDialogAPI()->create();
    return new ArkUI_NativeDialog({ dialog });
}

void Dispose(ArkUI_NativeDialogHandler handler)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return;
    }
    impl->getDialogAPI()->dispose(handler->controller);
    delete handler;
}

int32_t AttachContent(ArkUI_NativeDialogHandler handler, ArkUI_NodeHandle content)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler || !content) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->attachContent(handler->controller, content->uiNodeHandle);
}

int32_t DetachContent(ArkUI_NativeDialogHandler handler, ArkUI_NodeHandle content)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler || !content) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->detachContent(handler->controller, content->uiNodeHandle);
}

int32_t SetContentAlignment(ArkUI_NativeDialogHandler handler, int32_t alignment, float offsetX, float offsetY)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setContentAlignment(handler->controller,
        alignment, offsetX, offsetY);
}

int32_t ResetContentAlignment(ArkUI_NativeDialogHandler handler)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->resetContentAlignment(handler->controller);
}

int32_t SetMode(ArkUI_NativeDialogHandler handler, bool useModalMode, bool autoCancel)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setMode(handler->controller, useModalMode, autoCancel);
}

int32_t SetMask(ArkUI_NativeDialogHandler handler, uint32_t maskColor, const ArkUI_Rect* maskRect)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (maskRect) {
        ArkUIRect rect = { maskRect->x, maskRect->y, maskRect->width, maskRect->height };
        return impl->getDialogAPI()->setMask(handler->controller, maskColor, &rect);
    } else {
        return impl->getDialogAPI()->setMask(handler->controller, maskColor, nullptr);
    }
}

int32_t SetBackgroundColor(ArkUI_NativeDialogHandler handler, uint32_t backgroundColor)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setBackgroundColor(handler->controller, backgroundColor);
}

int32_t SetCornerRadius(ArkUI_NativeDialogHandler handler, float topLeft, float topRight,
    float bottomLeft, float bottomRight)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setCornerRadius(handler->controller,
        topLeft, topRight, bottomLeft, bottomRight);
}

int32_t SetGridCount(ArkUI_NativeDialogHandler handler, int32_t gridCount)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setGridCount(handler->controller, gridCount);
}

int32_t SetCustomStyle(ArkUI_NativeDialogHandler handler, bool customStyle)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setCustomStyle(handler->controller, customStyle);
}

int32_t UseCustomAnimation(ArkUI_NativeDialogHandler handler, bool useCustomAnimation)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->useCustomAnimation(handler->controller, useCustomAnimation);
}

int32_t Show(ArkUI_NativeDialogHandler handler, bool showInSubWindow)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->show(handler->controller, showInSubWindow);
}

int32_t Close(ArkUI_NativeDialogHandler handler)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->close(handler->controller);
}

int32_t RegiesterOnWillDismiss(ArkUI_NativeDialogHandler handler, OnWillDismissEvent eventHandler)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !handler) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->registerOnWillDismiss(handler->controller, eventHandler);
}

} // namespace OHOS::Ace::NG::DialogModel