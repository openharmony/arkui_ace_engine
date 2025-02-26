/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "dialog_option.h"
#include "native_dialog.h"
#include "node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_CustomDialogOptions* OH_ArkUI_CustomDialog_CreateOptions(ArkUI_NodeHandle content)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !content) {
        return nullptr;
    }
    auto dialog = impl->getDialogAPI()->create();
    auto options = new ArkUI_CustomDialogOptions({ dialog });
    impl->getDialogAPI()->setContent(options->handle, content->uiNodeHandle);
    return options;
}

void OH_ArkUI_CustomDialog_DisposeOptions(ArkUI_CustomDialogOptions* options)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return;
    }
    impl->getDialogAPI()->dispose(options->handle);
    delete options;
    options = nullptr;
}

int32_t OH_ArkUI_CustomDialog_OpenDialog(ArkUI_CustomDialogOptions* options, void (*callback)(int32_t dialogId))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->openCustomDialog(options->handle, callback);
}

int32_t OH_ArkUI_CustomDialog_CloseDialog(int32_t dialogId)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->closeCustomDialog(dialogId);
}

int32_t OH_ArkUI_CustomDialog_SetLevelMode(ArkUI_CustomDialogOptions* options, ArkUI_LevelMode levelMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(levelMode) < static_cast<int32_t>(ARKUI_LEVEL_MODE_OVERLAY) ||
        static_cast<int32_t>(levelMode) > static_cast<int32_t>(ARKUI_LEVEL_MODE_EMBEDDED)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelMode(options->handle, static_cast<int32_t>(levelMode));
}

int32_t OH_ArkUI_CustomDialog_SetLevelUniqueId(ArkUI_CustomDialogOptions* options, int32_t uniqueId)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (uniqueId < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setLevelUniqueId(options->handle, uniqueId);
}

int32_t OH_ArkUI_CustomDialog_SetImmersiveMode(ArkUI_CustomDialogOptions* options, ArkUI_ImmersiveMode immersiveMode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !options) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (static_cast<int32_t>(immersiveMode) < static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_DEFAULT) ||
        static_cast<int32_t>(immersiveMode) > static_cast<int32_t>(ARKUI_IMMERSIVE_MODE_EXTEND)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return impl->getDialogAPI()->setImmersiveMode(options->handle, static_cast<int32_t>(immersiveMode));
}

#ifdef __cplusplus
};
#endif
