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

#include <ani.h>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "prompt_action_params.h"
#include "toast_params.h"
#include "dialog_params.h"
#include "prompt_action_utils.h"

#include "frameworks/base/error/error_code.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/core/components/common/properties/shadow.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/toast/toast_layout_property.h"
#include "frameworks/core/components_ng/pattern/overlay/dialog_manager_static.h"
#include "frameworks/core/components_ng/pattern/overlay/overlay_manager.h"
#include "frameworks/core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/referenced.h"

namespace OHOS::Ace::NG {
bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafely();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}

bool ContainerIsScenceBoard()
{
    auto container = Container::CurrentSafely();
    if (!container) {
        container = Container::GetActive();
    }
    return container && container->IsScenceBoardWindow();
}
} // OHOS::Ace::NG

static void ShowToast(ani_env* env, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] showToast enter.");
    auto toastInfo = OHOS::Ace::NG::ToastInfo {
        .duration = -1,
        .showMode = OHOS::Ace::NG::ToastShowMode::DEFAULT,
        .alignment = -1
    };
    if (!GetShowToastOptions(env, options, toastInfo)) {
        return;
    }

    std::function<void(int32_t)> toastCallback = nullptr;
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard() && toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        OHOS::Ace::NG::DialogManagerStatic::ShowToastStatic(toastInfo, nullptr, OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToastStatic(toastInfo, nullptr);
    }
}

static ani_object OpenToast(ani_env* env, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] openToast enter.");
    auto toastInfo =
        OHOS::Ace::NG::ToastInfo { .duration = -1, .showMode = OHOS::Ace::NG::ToastShowMode::DEFAULT, .alignment = -1 };
    if (!GetShowToastOptions(env, options, toastInfo)) {
        return nullptr;
    }
    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }
    std::function<void(int32_t)> toastCallback = GetToastPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService()) &&
        !OHOS::Ace::NG::ContainerIsScenceBoard() && toastInfo.showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        OHOS::Ace::NG::DialogManagerStatic::ShowToastStatic(
            toastInfo, std::move(toastCallback), OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowToastStatic(toastInfo, std::move(toastCallback));
    }
    return result;
}

static void CloseToast(ani_env* env, ani_double toastId)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] closeToast enter.");
    std::function<void(int32_t)> toastCloseCallback = nullptr;
    toastCloseCallback = [env](int32_t errorCode) mutable {
        if (errorCode != OHOS::Ace::ERROR_CODE_NO_ERROR) {
            OHOS::Ace::Ani::AniThrow(env, "The toastId is invalid.", errorCode);
        };
    };
    if (!toastId) {
        toastCloseCallback(OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return;
    }
    if (toastId < 0 || toastId > INT32_MAX) {
        toastCloseCallback(OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return;
    }
    int32_t showModeVal = static_cast<int32_t>(static_cast<uint32_t>(toastId) & 0b111);
    int32_t id = static_cast<int32_t>(static_cast<uint32_t>(toastId) >> 3);
    if (id < 0 || showModeVal < 0 ||
        showModeVal > static_cast<int32_t>(OHOS::Ace::NG::ToastShowMode::SYSTEM_TOP_MOST)) {
        toastCloseCallback(OHOS::Ace::ERROR_CODE_TOAST_NOT_FOUND);
        return;
    }
    auto showMode = static_cast<OHOS::Ace::NG::ToastShowMode>(showModeVal);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService()) &&
        !OHOS::Ace::NG::ContainerIsScenceBoard() && showMode == OHOS::Ace::NG::ToastShowMode::DEFAULT) {
        OHOS::Ace::NG::DialogManagerStatic::CloseToastStatic(
            id, std::move(toastCloseCallback), OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->CloseToastStatic(id, showMode, std::move(toastCloseCallback));
    }
}

static void ShowDialogWithCallback(ani_env* env, ani_object options, ani_fn_object callback)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] showDialog1 enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetShowDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show dialog options fail.");
        return;
    }

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    asyncContext->callback = callback;

    std::function<void(int32_t, int32_t)> finishCallback = GetShowDialogCallback(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::ShowDialogStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowDialogStatic(dialogProps, std::move(finishCallback));
    }
}

static ani_object ShowDialog(ani_env* env, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] showDialog enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetShowDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show dialog options fail.");
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t, int32_t)> finishCallback = GetShowDialogPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::ShowDialogStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowDialogStatic(dialogProps, std::move(finishCallback));
    }
    return result;
}

static void ShowActionMenuWithCallback(ani_env* env, ani_object options, ani_fn_object callback)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] showActionMenu1 enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetActionMenuOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show action menu options fail.");
        return;
    }

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    asyncContext->callback = callback;

    std::function<void(int32_t, int32_t)> finishCallback = GetShowActionMenuCallback(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::ShowActionMenuStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowActionMenuStatic(dialogProps, std::move(finishCallback));
    }
}

static ani_object ShowActionMenu(ani_env* env, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] showActionMenu enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetActionMenuOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show action menu options fail.");
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t, int32_t)> finishCallback = GetShowActionMenuPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::ShowActionMenuStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowActionMenuStatic(dialogProps, std::move(finishCallback));
    }
    return result;
}

static ani_object OpenCustomDialogContent(ani_env* env, ani_long content, ani_object options,
    ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] openCustomDialog1 enter.");
    OHOS::Ace::DialogProperties dialogProps;
    GetBaseDialogOptions(env, options, dialogProps);
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    dialogProps.contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::Referenced::RawPtr(frameNode));

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t)> finishCallback = GetCustomDialogContentPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::OpenCustomDialogStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->OpenCustomDialogStatic(dialogProps, std::move(finishCallback));
    }
    return result;
}

static ani_object OpenCustomDialog(ani_env* env, ani_long builder, ani_object options, ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] openCustomDialog enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetCustomDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse open custom dialog options fail.");
        return nullptr;
    }
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);
    dialogProps.customBuilder = GetCustomBuilder(env, builder);
    dialogProps.isUserCreatedDialog = true;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t)> finishCallback = GetOpenCustomDialogPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::OpenCustomDialogStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->OpenCustomDialogStatic(dialogProps, std::move(finishCallback));
    }
    return result;
}

static ani_object UpdateCustomDialog(ani_env* env, ani_long content, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] updateCustomDialog enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetBaseDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse open custom dialog options fail.");
        return nullptr;
    }
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::Referenced::RawPtr(frameNode));

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t)> finishCallback = GetCustomDialogContentPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::UpdateCustomDialogStatic(
            contentNode, dialogProps, std::move(finishCallback));
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::PromptDialogAttr dialogAttr = {
            .autoCancel = dialogProps.autoCancel,
            .alignment = dialogProps.alignment,
            .offset = dialogProps.offset,
            .maskColor = dialogProps.maskColor,
        };
        OHOS::Ace::SubwindowManager::GetInstance()->UpdateCustomDialogNG(
            contentNode, dialogAttr, std::move(finishCallback));
    }
    return result;
}

static ani_object CloseCustomDialogContent(ani_env* env, ani_long content)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] closeCustomDialog1 enter.");
    Ark_FrameNode peerNode = (Ark_FrameNode)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::Referenced::RawPtr(frameNode));

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    ani_status status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Create promise object fail.");
    }

    std::function<void(int32_t)> finishCallback = GetCustomDialogContentPromise(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::CloseCustomDialogStatic(contentNode, std::move(finishCallback));
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->CloseCustomDialogNG(contentNode, std::move(finishCallback));
    }
    return result;
}

static void CloseCustomDialog(ani_env* env, ani_double dialogId)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] closeCustomDialog enter.");
    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();

    int32_t customDialogId = static_cast<int32_t>(static_cast<double>(dialogId));
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::CloseCustomDialogStatic(customDialogId, OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->CloseCustomDialogNG(customDialogId);
    }
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] ANI_Constructor start.");
    ani_env *env;
    ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
    if (status != ANI_OK) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    status = env->FindNamespace("L@ohos/promptAction/promptAction;", &ns);
    if (status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"showToast", nullptr, reinterpret_cast<void *>(ShowToast)},
        ani_native_function {"openToast", nullptr, reinterpret_cast<void *>(OpenToast)},
        ani_native_function {"closeToast", nullptr, reinterpret_cast<void *>(CloseToast)},
        ani_native_function {"showDialog1", nullptr, reinterpret_cast<void *>(ShowDialogWithCallback)},
        ani_native_function {"showDialog", nullptr, reinterpret_cast<void *>(ShowDialog)},
        ani_native_function {"showActionMenu1", nullptr, reinterpret_cast<void *>(ShowActionMenuWithCallback)},
        ani_native_function {"showActionMenu", nullptr, reinterpret_cast<void *>(ShowActionMenu)},
        ani_native_function {"openCustomDialog1", nullptr, reinterpret_cast<void *>(OpenCustomDialogContent)},
        ani_native_function {"openCustomDialog", nullptr, reinterpret_cast<void *>(OpenCustomDialog)},
        ani_native_function {"updateCustomDialog", nullptr, reinterpret_cast<void *>(UpdateCustomDialog)},
        ani_native_function {"closeCustomDialog1", nullptr, reinterpret_cast<void *>(CloseCustomDialogContent)},
        ani_native_function {"closeCustomDialog", nullptr, reinterpret_cast<void *>(CloseCustomDialog)},
    };
    status = env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size());
    if (status != ANI_OK) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] ANI_Constructor end.");
    return ANI_OK;
}
