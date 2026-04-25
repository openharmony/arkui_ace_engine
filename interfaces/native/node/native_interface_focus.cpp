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

#include "interfaces/native/native_interface_focus.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/native_error_message_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(impl, ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT,
        "OH_ArkUI_FocusRequest", "Native module not initialized");
    CHECK_NULL_RETURN_WITH_MESSAGE(node, ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT,
        "OH_ArkUI_FocusRequest", "Node parameter is null");
    auto ret = impl->getNodeModifiers()->getFrameNodeModifier()->requestFocus(node->uiNodeHandle);
    return static_cast<ArkUI_ErrorCode>(ret);
}

void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, "OH_ArkUI_FocusClear", "Native module not initialized");
        return;
    }
    if (!uiContext) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, "OH_ArkUI_FocusClear", "UI context parameter is null");
        return;
    }
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    impl->getNodeModifiers()->getFrameNodeModifier()->clearFocus(context->id);
}

void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, "OH_ArkUI_FocusActivate", "Native module not initialized");
        return;
    }
    if (!uiContext) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID, "OH_ArkUI_FocusActivate", "UI context parameter is null");
        return;
    }
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    impl->getNodeModifiers()->getFrameNodeModifier()->focusActivate(context->id, isActive, isAutoInactive);
}

void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID,
            "OH_ArkUI_FocusSetAutoTransfer", "Native module not initialized");
        return;
    }
    if (!uiContext) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID,
            "OH_ArkUI_FocusSetAutoTransfer", "UI context parameter is null");
        return;
    }
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    impl->getNodeModifiers()->getFrameNodeModifier()->setAutoFocusTransfer(context->id, autoTransfer);
}

void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID,
            "OH_ArkUI_FocusSetKeyProcessingMode", "Native module not initialized");
        return;
    }
    if (!uiContext) {
        SET_ERROR_MESSAGE(ARKUI_ERROR_CODE_PARAM_INVALID,
            "OH_ArkUI_FocusSetKeyProcessingMode", "UI context parameter is null");
        return;
    }
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    impl->getNodeModifiers()->getFrameNodeModifier()->setKeyProcessingMode(context->id, static_cast<ArkUI_Int32>(mode));
}
#ifdef __cplusplus
};
#endif
