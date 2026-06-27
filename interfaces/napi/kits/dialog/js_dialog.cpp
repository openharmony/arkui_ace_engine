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
#include "dialog_params.h"

#include "base/error/error_code.h"
#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

extern const char _binary_dialog_js_start[];
extern const char _binary_dialog_js_end[];
extern const char _binary_dialog_abc_start[];
extern const char _binary_dialog_abc_end[];

extern "C" __attribute__((visibility("default"))) void NAPI_dialog_GetJSCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_dialog_js_start;
    }
    if (bufLen != nullptr) {
        *bufLen = _binary_dialog_js_end - _binary_dialog_js_start;
    }
}

extern "C" __attribute__((visibility("default"))) void NAPI_dialog_GetABCCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_dialog_abc_start;
    }
    if (bufLen != nullptr) {
        *bufLen = _binary_dialog_abc_end - _binary_dialog_abc_start;
    }
}

namespace OHOS::Ace {
namespace {
constexpr int32_t CALLBACK_ERRORCODE_CANCEL = 1;
constexpr int32_t CALLBACK_DATACODE_ZERO = 0;

constexpr size_t PARAM_INDEX_FIRST = 0;
constexpr size_t PARAM_INDEX_SECOND = 1;
constexpr size_t MAX_PARAM_COUNT = 2;
constexpr size_t MIN_PARAM_COUNT = 1;
} // namespace

napi_value JSPresentDialog(napi_env env, napi_callback_info info)
{
    size_t argc = MIN_PARAM_COUNT;
    napi_value argv[MIN_PARAM_COUNT] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < MIN_PARAM_COUNT) {
        Napi::NapiThrow(env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    DialogProperties dialogProps;
    dialogProps.isDialogNapiCall = true;
    if (!GetDialogOptions(env, argv[PARAM_INDEX_FIRST], dialogProps)) {
        Napi::NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto context = std::make_shared<DialogAsyncContext>();
    context->env = env;
    context->instanceId = Container::CurrentIdSafely();
    napi_value result = CreateDialogPromise(env, context);
    auto finishCallback = CreatePresentFinishCallback(context);
    auto mountCallback = CreatePresentCustomFinishCallback(context);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_RETURN(container, result);
        container->GetTaskExecutor()->PostTask(
            [context]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    RejectPromise(context->env, context->deferred,
                        "Internal error.", ERROR_CODE_INTERNAL_ERROR);
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogShowNoDelegate");
        context = nullptr;
        return result;
    }

    {
        auto callbackForCancel = finishCallback;
        dialogProps.onSuccess = std::move(finishCallback);
        dialogProps.onCancel = [cb = std::move(callbackForCancel)]() {
            cb(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO);
        };

        auto instanceId = context->instanceId;
        ContainerScope scope(instanceId);
        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, result);
        auto overlayManager = pipelineContext->GetOverlayManager();
        auto task = [dialogProps, instanceId,
                     callback = std::move(mountCallback)](const RefPtr<NG::OverlayManager>& overlayManager) {
            CHECK_NULL_VOID(overlayManager);
            auto container = AceEngine::Get().GetContainer(instanceId);
            CHECK_NULL_VOID(container);
            if (container->IsSubContainer()) {
                auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(instanceId);
                container = AceEngine::Get().GetContainer(parentContainerId);
                CHECK_NULL_VOID(container);
            }
            if (!dialogProps.isShowInSubWindow) {
                overlayManager->ShowDialog(
                    dialogProps, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft(), std::move(callback));
                return;
            }
            auto dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProps, nullptr, std::move(callback));
            CHECK_NULL_VOID(dialog);
            if (dialogProps.isModal && !container->IsUIExtensionWindow()) {
                DialogProperties maskProps = {
                    .autoCancel = dialogProps.autoCancel,
                    .isMask = true,
                };
                auto mask = overlayManager->ShowDialog(maskProps, nullptr, false);
                CHECK_NULL_VOID(mask);
                overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
            }
        };
        if (dialogProps.dialogLevelMode == LevelMode::EMBEDDED) {
            NG::DialogManager::ShowInEmbeddedOverlay(
                std::move(task), "ArkUIDialogShow", dialogProps.dialogLevelUniqueId);
        } else {
            pipelineContext->GetTaskExecutor()->PostTask(
                [task, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
                    task(weak.Upgrade());
                },
                TaskExecutor::TaskType::UI, "ArkUIDialogShow");
        }
    }
    return result;
}

napi_value JSPresentCustomDialog(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_PARAM_COUNT;
    napi_value argv[MAX_PARAM_COUNT] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < MIN_PARAM_COUNT) {
        Napi::NapiThrow(env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    DialogProperties dialogProps;
    dialogProps.isUserCreatedDialog = true;
    dialogProps.isDialogNapiCall = true;
    dialogProps.customStyle = false;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[PARAM_INDEX_FIRST], &valueType);
    if (valueType == napi_function) {
        GetCustomBuilder(env, argv[PARAM_INDEX_FIRST], dialogProps);
    } else if (valueType == napi_object) {
        WeakPtr<NG::UINode> nodeWk;
        if (!GetFrameNodePtr(env, argv[PARAM_INDEX_FIRST], nodeWk)) {
            Napi::NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
        dialogProps.contentNode = nodeWk;
    } else {
        Napi::NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    if (argc >= MAX_PARAM_COUNT) {
        GetCustomDialogOptions(env, argv[PARAM_INDEX_SECOND], dialogProps);
    }

    auto context = std::make_shared<DialogAsyncContext>();
    context->env = env;
    context->instanceId = Container::CurrentIdSafely();
    napi_value result = CreateDialogPromise(env, context);
    auto finishCallback = CreatePresentCustomFinishCallback(context);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_RETURN(container, result);
        container->GetTaskExecutor()->PostTask(
            [context]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    RejectPromise(context->env, context->deferred,
                        "Internal error.", ERROR_CODE_INTERNAL_ERROR);
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogOpenCustomNoDelegate");
        context = nullptr;
        return result;
    }

    {
        auto instanceId = context->instanceId;
        ContainerScope scope(instanceId);
        auto pipelineContext = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, result);
        auto overlayManager = pipelineContext->GetOverlayManager();
        auto task = [dialogProps, callback = std::move(finishCallback)](
                        const RefPtr<NG::OverlayManager>& overlayManager) mutable {
            CHECK_NULL_VOID(overlayManager);
            if (dialogProps.isShowInSubWindow) {
                SubwindowManager::GetInstance()->OpenCustomDialogNG(dialogProps, std::move(callback));
                if (dialogProps.isModal) {
                    TAG_LOGW(AceLogTag::ACE_OVERLAY, "Temporary not support isShowInSubWindow and isModal.");
                }
            } else {
                overlayManager->OpenCustomDialog(dialogProps, std::move(callback));
            }
        };
        if (dialogProps.dialogLevelMode == LevelMode::EMBEDDED) {
            NG::DialogManager::ShowInEmbeddedOverlay(
                std::move(task), "ArkUIDialogOpenCustom", dialogProps.dialogLevelUniqueId);
        } else {
            pipelineContext->GetTaskExecutor()->PostTask(
                [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
                    task(weak.Upgrade());
                },
                TaskExecutor::TaskType::UI, "ArkUIDialogOpenCustom");
        }
    }
    return result;
}

napi_value JSUpdateCustomDialog(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_PARAM_COUNT;
    napi_value argv[MAX_PARAM_COUNT] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < MAX_PARAM_COUNT) {
        Napi::NapiThrow(env, "The number of parameters must be greater than or equal to 2.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    WeakPtr<NG::UINode> nodeWk;
    if (!GetFrameNodePtr(env, argv[PARAM_INDEX_FIRST], nodeWk)) {
        Napi::NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    DialogProperties dialogProps;
    if (argc >= MAX_PARAM_COUNT) {
        GetDialogBaseOptions(env, argv[PARAM_INDEX_SECOND], dialogProps);
    }

    auto context = std::make_shared<DialogAsyncContext>();
    context->env = env;
    context->instanceId = Container::CurrentIdSafely();
    napi_value result = CreateDialogPromise(env, context);
    auto finishCallback = CreateUpdateFinishCallback(context);
    auto nodePtr = nodeWk.Upgrade();
    CHECK_NULL_RETURN(nodePtr, result);
    auto pipelineContext = nodePtr->GetContextWithCheck();
    CHECK_NULL_RETURN(pipelineContext, result);
    auto overlayManager = pipelineContext->GetOverlayManager();
    auto task = [nodeWk, dialogProps, callback = std::move(finishCallback),
                 weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
        auto overlayManager = weak.Upgrade();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->UpdateCustomDialog(nodeWk, dialogProps, std::move(callback));
    };
    pipelineContext->GetTaskExecutor()->PostTask(
        std::move(task), TaskExecutor::TaskType::UI, "ArkUIDialogUpdate");
    return result;
}

napi_value JSDismissDialog(napi_env env, napi_callback_info info)
{
    size_t argc = MIN_PARAM_COUNT;
    napi_value argv[MIN_PARAM_COUNT] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < MIN_PARAM_COUNT) {
        Napi::NapiThrow(env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto context = std::make_shared<DialogAsyncContext>();
    context->env = env;
    context->instanceId = Container::CurrentIdSafely();
    napi_value result = CreateDialogPromise(env, context);

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[PARAM_INDEX_FIRST], &valueType);

    if (valueType == napi_number) {
        int32_t dialogId = 0;
        napi_get_value_int32(env, argv[PARAM_INDEX_FIRST], &dialogId);
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            auto container = AceEngine::Get().GetContainer(context->instanceId);
            CHECK_NULL_RETURN(container, result);
            container->GetTaskExecutor()->PostTask(
                [context]() {
                    if (context == nullptr) {
                        return;
                    }
                    napi_handle_scope scope = nullptr;
                    napi_open_handle_scope(context->env, &scope);
                    if (context->deferred) {
                        RejectPromise(context->env, context->deferred,
                            "Internal error.", ERROR_CODE_INTERNAL_ERROR);
                        context->deferred = nullptr;
                    }
                    napi_close_handle_scope(context->env, scope);
                },
                TaskExecutor::TaskType::JS, "ArkUIDialogDismissNoDelegate");
            context = nullptr;
            return result;
        }
        delegate->CloseCustomDialog(dialogId);
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_RETURN(container, result);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_RETURN(taskExecutor, result);
        taskExecutor->PostTask(
            [context]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    napi_value undefined = nullptr;
                    napi_get_undefined(context->env, &undefined);
                    napi_resolve_deferred(context->env, context->deferred, undefined);
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogDismissByIdCallback");
        context = nullptr;
        return result;
    }

    // Close by ComponentContent
    WeakPtr<NG::UINode> nodeWk;
    if (!GetFrameNodePtr(env, argv[PARAM_INDEX_FIRST], nodeWk)) {
        Napi::NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto finishCallback = CreateDismissFinishCallback(context);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        auto container = AceEngine::Get().GetContainer(context->instanceId);
        CHECK_NULL_RETURN(container, result);
        container->GetTaskExecutor()->PostTask(
            [context]() {
                if (context == nullptr) {
                    return;
                }
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(context->env, &scope);
                if (context->deferred) {
                    RejectPromise(context->env, context->deferred,
                        "Internal error.", ERROR_CODE_INTERNAL_ERROR);
                    context->deferred = nullptr;
                }
                napi_close_handle_scope(context->env, scope);
            },
            TaskExecutor::TaskType::JS, "ArkUIDialogDismissByNodeNoDelegate");
        context = nullptr;
        return result;
    }
    delegate->CloseCustomDialog(nodeWk, std::move(finishCallback));
    return result;
}

// Module export and registration
napi_value DialogExport(napi_env env, napi_value exports)
{
    napi_property_descriptor dialogDesc[] = {
        DECLARE_NAPI_FUNCTION("presentDialog", JSPresentDialog),
        DECLARE_NAPI_FUNCTION("presentCustomDialog", JSPresentCustomDialog),
        DECLARE_NAPI_FUNCTION("updateCustomDialog", JSUpdateCustomDialog),
        DECLARE_NAPI_FUNCTION("dismissDialog", JSDismissDialog),
    };

    NAPI_CALL(env, napi_define_properties(env, exports,
        sizeof(dialogDesc) / sizeof(dialogDesc[0]), dialogDesc));

    DialogControllerImpl::Define(env, exports);
    return exports;
}

static napi_module_with_js dialogModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = DialogExport,
    .nm_modname = "arkui.dialog",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_dialog_GetABCCode,
    .nm_get_js_code = NAPI_dialog_GetJSCode,
};

extern "C" __attribute__((constructor)) void DialogRegister()
{
    napi_module_with_js_register(&dialogModule);
}
} // namespace OHOS::Ace
