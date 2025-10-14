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
#include "prompt_action_controller.h"

#include "base/subwindow/subwindow_manager.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/core/components/common/properties/shadow.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/toast/toast_layout_property.h"
#include "frameworks/core/components_ng/pattern/overlay/dialog_manager_static.h"
#include "frameworks/core/components_ng/pattern/overlay/overlay_manager.h"
#include "frameworks/core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/referenced.h"

using OHOS::Ace::FrameNodePeer;

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
    return container && container->IsSceneBoardWindow();
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
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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

static void CloseToast(ani_env* env, ani_int toastId)
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

static void ShowDialogWithCallback(ani_env* env, ani_object options, ani_object callback, ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] ShowDialogWithCallback enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetShowDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show dialog options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return;
    }
    GetShowDialogOptionsInternal(env, optionsInternal, dialogProps);
    dialogProps.type = OHOS::Ace::DialogType::ALERT_DIALOG;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_ref globalRef;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &globalRef);
    asyncContext->callback = reinterpret_cast<ani_fn_object>(globalRef);

    std::function<void(int32_t, int32_t)> finishCallback = GetShowDialogCallback(asyncContext);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::ShowDialogStatic(dialogProps, std::move(finishCallback),
            OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->ShowDialogStatic(dialogProps, std::move(finishCallback));
    }
}

static ani_object ShowDialog(ani_env* env, ani_object options, ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] ShowDialog enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetShowDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show dialog options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    GetShowDialogOptionsInternal(env, optionsInternal, dialogProps);
    dialogProps.type = OHOS::Ace::DialogType::ALERT_DIALOG;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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

static void ShowActionMenuWithCallback(ani_env* env, ani_object options, ani_object callback)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] ShowActionMenuWithCallback enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetActionMenuOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show action menu options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return;
    }
    dialogProps.autoCancel = true;
    dialogProps.isMenu = true;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_ref globalRef;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(callback), &globalRef);
    asyncContext->callback = reinterpret_cast<ani_fn_object>(globalRef);

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
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] ShowActionMenu enter.");
    OHOS::Ace::DialogProperties dialogProps;
    if (!GetActionMenuOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse show action menu options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    dialogProps.autoCancel = true;
    dialogProps.isMenu = true;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] OpenCustomDialogContent enter.");
    FrameNodePeer* peerNode = (FrameNodePeer*)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        OHOS::Ace::Ani::AniThrow(env, "The ComponentContent is incorrect.", OHOS::Ace::ERROR_CODE_DIALOG_CONTENT_ERROR);
        return nullptr;
    }
    frameNode->SetBuilderFunc(nullptr);

    OHOS::Ace::DialogProperties dialogProps;
    dialogProps.contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::AceType::RawPtr(frameNode));
    GetBaseDialogOptions(env, options, dialogProps);
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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

static ani_object OpenCustomDialog(ani_env* env, ani_object builderOptions, ani_object options,
    ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] OpenCustomDialog enter.");
    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
    }

    OHOS::Ace::DialogProperties dialogProps;
    bool builderResult = GetCustomBuilder(env, builderOptions, dialogProps.customBuilder);
    bool destroyResult = GetDestroyCallback(env, builderOptions, dialogProps.destroyCallback);
    if (!builderResult || !destroyResult) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse dialog builder options fail.");
        return nullptr;
    }

    if (!GetCustomDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse open custom dialog options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);
    dialogProps.isUserCreatedDialog = true;

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
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] UpdateCustomDialog enter.");
    FrameNodePeer* peerNode = (FrameNodePeer*)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        OHOS::Ace::Ani::AniThrow(env, "The ComponentContent is incorrect.", OHOS::Ace::ERROR_CODE_DIALOG_CONTENT_ERROR);
        return nullptr;
    }
    auto contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::AceType::RawPtr(frameNode));

    OHOS::Ace::DialogProperties dialogProps;
    if (!GetBaseDialogOptions(env, options, dialogProps)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse open custom dialog options fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    dialogProps.isSysBlurStyle = false;

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] CloseCustomDialogContent enter.");
    FrameNodePeer* peerNode = (FrameNodePeer*)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        OHOS::Ace::Ani::AniThrow(env, "The ComponentContent is incorrect.", OHOS::Ace::ERROR_CODE_DIALOG_CONTENT_ERROR);
        return nullptr;
    }
    auto contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::AceType::RawPtr(frameNode));

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result = {};
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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

static void CloseCustomDialog(ani_env* env, ani_int dialogId)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] CloseCustomDialog enter.");
    int32_t customDialogId = static_cast<int32_t>(dialogId);
    if ((OHOS::Ace::SystemProperties::GetExtSurfaceEnabled() || !OHOS::Ace::NG::ContainerIsService())
        && !OHOS::Ace::NG::ContainerIsScenceBoard()) {
        OHOS::Ace::NG::DialogManagerStatic::CloseCustomDialogStatic(customDialogId, OHOS::Ace::INSTANCE_ID_UNDEFINED);
    } else if (OHOS::Ace::SubwindowManager::GetInstance() != nullptr) {
        OHOS::Ace::SubwindowManager::GetInstance()->CloseCustomDialogNG(customDialogId);
    }
}

static ani_object OpenCustomDialogWithController(ani_env* env, ani_long content, ani_object controller,
    ani_object options, ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] OpenCustomDialogWithController enter.");
    FrameNodePeer* peerNode = (FrameNodePeer*)content;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    if (!frameNode) {
        OHOS::Ace::Ani::AniThrow(env, "The ComponentContent is incorrect.", OHOS::Ace::ERROR_CODE_DIALOG_CONTENT_ERROR);
        return nullptr;
    }
    frameNode->SetBuilderFunc(nullptr);

    OHOS::Ace::DialogProperties dialogProps;
    dialogProps.contentNode = OHOS::Ace::AceType::WeakClaim(OHOS::Ace::AceType::RawPtr(frameNode));
    if (!OHOS::Ace::Ani::GetDialogController(env, controller, dialogProps.dialogCallback)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse dialog controller fail.");
        OHOS::Ace::Ani::AniThrow(env, "The type of parameters is incorrect.", OHOS::Ace::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    GetBaseDialogOptions(env, options, dialogProps);
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result;
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
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

static ani_object PresentCustomDialog(ani_env* env, ani_object builderOptions, ani_object controller,
    ani_object options, ani_object optionsInternal)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] PresentCustomDialog enter.");
    OHOS::Ace::DialogProperties dialogProps;
    bool builderResult = GetCustomBuilder(env, builderOptions, dialogProps.customBuilder);
    bool destroyResult = GetDestroyCallback(env, builderOptions, dialogProps.destroyCallback);
    bool builderWithIdResult = GetCustomBuilderWithId(env, builderOptions, dialogProps.customBuilderWithId);
    if ((!builderResult && !builderWithIdResult) || !destroyResult) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "Parse dialog builder options fail.");
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptActionAsyncContext>();
    ani_status status = env->GetVM(&asyncContext->vm);
    if (status != ANI_OK || asyncContext->vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return nullptr;
    }
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ani_object result;
    status = env->Promise_New(&asyncContext->deferred, &result);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] Promise_New fail. status: %{public}d", status);
    }

    OHOS::Ace::Ani::GetDialogController(env, controller, dialogProps.dialogCallback);
    GetDialogOptions(env, options, dialogProps);
    GetDialogOptionsInternal(env, optionsInternal, dialogProps);
    dialogProps.isUserCreatedDialog = true;

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

static ani_object GetTopOrder(ani_env* env)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] GetTopOrder enter.");
    ani_object aniOrder = nullptr;
    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return aniOrder;
    }
    aniOrder = static_cast<ani_object>(undefinedRef);

    auto context = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, aniOrder);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, aniOrder);
    auto orderValue = overlayManager->GetTopOrder();
    if (orderValue.has_value()) {
        aniOrder = CreateANIDoubleObject(env, orderValue.value());
    }
    return aniOrder;
}

static ani_object GetBottomOrder(ani_env* env)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] GetBottomOrder enter.");
    ani_object aniOrder = nullptr;
    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return aniOrder;
    }
    aniOrder = static_cast<ani_object>(undefinedRef);

    auto context = OHOS::Ace::NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, aniOrder);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, aniOrder);
    auto orderValue = overlayManager->GetBottomOrder();
    if (orderValue.has_value()) {
        aniOrder = CreateANIDoubleObject(env, orderValue.value());
    }
    return aniOrder;
}

static ani_object GetDialogNode(ani_env* env, ani_long content)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetDialogNode enter.");
    ani_ref undefinedRef = nullptr;
    ani_status status = env->GetUndefined(&undefinedRef);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetUndefined fail. status: %{public}d", status);
        return nullptr;
    }
    ani_object result = static_cast<ani_object>(undefinedRef);

    auto* uiNode = reinterpret_cast<ArkUINodeHandle>(content);
    CHECK_NULL_RETURN(uiNode, result);
    auto contentNode = OHOS::Ace::AceType::Claim(reinterpret_cast<OHOS::Ace::NG::UINode *>(uiNode));
    CHECK_NULL_RETURN(contentNode, result);
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> dialogNode = contentNode->GetParentFrameNode();
    while (dialogNode) {
        if (dialogNode->GetTag() == OHOS::Ace::V2::DIALOG_ETS_TAG) {
            break;
        }
        dialogNode = dialogNode->GetParentFrameNode();
    }
    CHECK_NULL_RETURN(dialogNode, result);

    auto* node = OHOS::Ace::AceType::RawPtr(dialogNode);
    CHECK_NULL_RETURN(node, result);
    int64_t nodePtr = reinterpret_cast<int64_t>(node);
    return CreateANILongObject(env, nodePtr);
}

static ani_boolean SetDialogController(ani_env* env, ani_long dialog, ani_object controller)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] SetDialogController enter.");
    ani_boolean result = static_cast<ani_boolean>(false);
    auto* uiNode = reinterpret_cast<ArkUINodeHandle>(dialog);
    CHECK_NULL_RETURN(uiNode, result);
    auto dialogNode = OHOS::Ace::AceType::Claim(reinterpret_cast<OHOS::Ace::NG::FrameNode *>(uiNode));
    CHECK_NULL_RETURN(dialogNode, result);

    if (IsUndefinedObject(env, controller)) {
        return result;
    }

    ani_long nativePtr;
    ani_status status = env->Object_GetFieldByName_Long(controller, "nativePtr", &nativePtr);
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG,
            "[ANI] Object_GetFieldByName_Long fail. status: %{public}d", status);
        return result;
    }

    auto dialogController = reinterpret_cast<OHOS::Ace::Ani::PromptActionDialogController *>(nativePtr);
    CHECK_NULL_RETURN(dialogController, false);
    dialogController->SetNode(dialogNode);
    result = static_cast<ani_boolean>(true);
    return result;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "PromptAction ANI_Constructor start.");
    ani_env *env;
    ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "PromptAction GetEnv fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    ani_namespace ns;
    status = env->FindNamespace("@ohos.promptAction.promptAction", &ns);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "PromptAction FindNamespace fail. status: %{public}d", status);
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
        ani_native_function {"openCustomDialogWithController", nullptr,
            reinterpret_cast<void *>(OpenCustomDialogWithController)},
        ani_native_function {"presentCustomDialog", nullptr, reinterpret_cast<void *>(PresentCustomDialog)},
        ani_native_function {"getTopOrder", nullptr, reinterpret_cast<void *>(GetTopOrder)},
        ani_native_function {"getBottomOrder", nullptr, reinterpret_cast<void *>(GetBottomOrder)},
        ani_native_function {"getDialogNode", nullptr, reinterpret_cast<void *>(GetDialogNode)},
        ani_native_function {"setDialogController", nullptr, reinterpret_cast<void *>(SetDialogController)},
    };
    status = env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "PromptAction BindFunctions fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    status = OHOS::Ace::Ani::BindCommonController(env);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY,
            "PromptAction BindCommonController fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    status = OHOS::Ace::Ani::BindDialogController(env);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY,
            "PromptAction BindDialogController fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    status = OHOS::Ace::Ani::BindDismissDialogAction(env);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY,
            "PromptAction BindDismissDialogAction fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "PromptAction ANI_Constructor end.");
    return ANI_OK;
}
