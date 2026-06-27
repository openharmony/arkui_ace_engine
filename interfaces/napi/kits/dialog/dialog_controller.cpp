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

#include "dialog_controller.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

namespace OHOS::Ace {
void DialogControllerImpl::SetDialogNode(const WeakPtr<NG::FrameNode>& node)
{
    dialogNode_ = node;
    auto dialogNode = dialogNode_.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    auto pattern = dialogNode->GetPattern<NG::DialogPattern>();
    CHECK_NULL_VOID(pattern);
    if (PromptActionCommonState::UNINITIALIZED == pattern->GetState()) {
        pattern->SetState(PromptActionCommonState::INITIALIZED);
        TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is INITIALIZED.");
    }
    hasBind_ = true;
}

void DialogControllerImpl::Close()
{
    auto dialogNode = dialogNode_.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    auto pipeline = dialogNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode);
}

PromptActionCommonState DialogControllerImpl::GetState()
{
    PromptActionCommonState state = PromptActionCommonState::UNINITIALIZED;
    if (dialogNode_.Invalid()) {
        if (hasBind_) {
            return PromptActionCommonState::DISAPPEARED;
        }
        return state;
    }
    auto dialogNode = dialogNode_.Upgrade();
    CHECK_NULL_RETURN(dialogNode, state);
    auto pattern = dialogNode->GetPattern<NG::DialogPattern>();
    CHECK_NULL_RETURN(pattern, state);
    state = pattern->GetState();
    return state;
}

napi_value DialogControllerImpl::Define(napi_env env, napi_value exports)
{
    napi_value dialogController = nullptr;
    napi_create_object(env, &dialogController);

    napi_value bindDialogFunc = nullptr;
    napi_create_function(env, "bindDialog", NAPI_AUTO_LENGTH, Constructor, nullptr, &bindDialogFunc);
    napi_set_named_property(env, dialogController, "bindDialog", bindDialogFunc);

    napi_value closeDialogFunc = nullptr;
    napi_create_function(env, "closeDialog", NAPI_AUTO_LENGTH, Close, nullptr, &closeDialogFunc);
    napi_set_named_property(env, dialogController, "closeDialog", closeDialogFunc);

    napi_value getStateFunc = nullptr;
    napi_create_function(env, "getState", NAPI_AUTO_LENGTH, GetState, nullptr, &getStateFunc);
    napi_set_named_property(env, dialogController, "getState", getStateFunc);

    napi_set_named_property(env, exports, "DialogController", dialogController);
    return exports;
}

napi_value DialogControllerImpl::Constructor(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        Napi::NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto* controller = new DialogControllerImpl();
    napi_status status = napi_wrap(env, argv[0], controller, Destructor, nullptr, nullptr);
    if (status != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Failed to wrap DialogControllerImpl.");
        delete controller;
        return nullptr;
    }
    return thisArg;
}

napi_value DialogControllerImpl::Close(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        Napi::NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    DialogControllerImpl* controller = nullptr;
    napi_status status = napi_unwrap(env, argv[0], reinterpret_cast<void**>(&controller));
    if (status != napi_ok || !controller) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Failed to unwrap DialogControllerImpl.");
        return nullptr;
    }
    controller->Close();
    return thisArg;
}

napi_value DialogControllerImpl::GetState(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        Napi::NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    DialogControllerImpl* controller = nullptr;
    napi_status status = napi_unwrap(env, argv[0], reinterpret_cast<void**>(&controller));
    if (status != napi_ok || !controller) {
        return nullptr;
    }
    auto state = controller->GetState();
    napi_value dialogState = nullptr;
    napi_create_int32(env, static_cast<int32_t>(state), &dialogState);
    return dialogState;
}

void DialogControllerImpl::Destructor(napi_env env, void* data, void* hint)
{
    auto* controller = reinterpret_cast<DialogControllerImpl*>(data);
    if (controller != nullptr) {
        delete controller;
    }
}
} // namespace OHOS::Ace
