/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "js_prompt_controller.h"
#include "prompt_controller.h"

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Napi {

napi_value JSPromptController::CloseDialog(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    PromptDialogController* controller = nullptr;
    napi_status status = napi_unwrap(env, argv[0], reinterpret_cast<void**>(&controller));
    if (status != napi_ok || !controller) {
        LOGE("Failed to unwrap PromptDialogController.");
        return nullptr;
    }
    controller->Close();
    return thisArg;
}

napi_value JSPromptController::GetState(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    PromptDialogController* controller = nullptr;
    napi_status status = napi_unwrap(env, argv[0], reinterpret_cast<void**>(&controller));
    if (status != napi_ok || !controller) {
        return nullptr;
    }
    auto state = controller->GetState();
    napi_value dialogState;
    napi_status createStatus = napi_create_int32(env, static_cast<int32_t>(state), &dialogState);
    if (createStatus != napi_ok) {
        return nullptr;
    }
    return dialogState;
}

void JSPromptController::DialogControllerDestructor(napi_env env, void* data, void* hint)
{
    PromptDialogController* controller = reinterpret_cast<PromptDialogController*>(data);
    CHECK_NULL_VOID(controller);
    delete controller;
    controller = nullptr;
}

napi_value JSPromptController::DialogControllerConstructor(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisArg, nullptr));
    if (argc < 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    PromptDialogController* controller = new (std::nothrow) PromptDialogController();
    napi_status status = napi_wrap(env, argv[0], controller, DialogControllerDestructor, nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("Failed to wrap PromptDialogController.");
        return nullptr;
    }
    return thisArg;
}

napi_status JSPromptController::Define(napi_env env, napi_value exports)
{
    napi_value promptController = nullptr;
    napi_create_object(env, &promptController);

    napi_value bindDialogFunc = nullptr;
    napi_create_function(env, "bindDialog", NAPI_AUTO_LENGTH, DialogControllerConstructor, nullptr, &bindDialogFunc);
    napi_set_named_property(env, promptController, "bindDialog", bindDialogFunc);
    napi_value closeDialogFunc = nullptr;
    napi_create_function(env, "closeDialog", NAPI_AUTO_LENGTH, CloseDialog, nullptr, &closeDialogFunc);
    napi_set_named_property(env, promptController, "closeDialog", closeDialogFunc);
    napi_value getStateFunc = nullptr;
    napi_create_function(env, "getState", NAPI_AUTO_LENGTH, GetState, nullptr, &getStateFunc);
    napi_set_named_property(env, promptController, "getState", getStateFunc);

    napi_set_named_property(env, exports, "PromptController", promptController);
    return napi_ok;
}

} // namespace OHOS::Ace::Napi
