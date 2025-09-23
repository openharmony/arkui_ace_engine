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

#include "adapter/ohos/entrance/subwindow/subwindow_ohos.h"

#include "adapter/ohos/entrance/dialog_container.h"
#include "core/components_ng/pattern/overlay/dialog_manager_static.h"

namespace OHOS::Ace {

void SubwindowOhos::ShowToastStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "show toast static, window parent id is %{public}d", parentContainerId_);
    bool isTopMost = toastInfo.showMode == NG::ToastShowMode::TOP_MOST;
    // for pa service
    if ((isTopMost && parentContainerId_ >= MIN_PA_SERVICE_ID && parentContainerId_ < MIN_SUBCONTAINER_ID) ||
        (!isTopMost && parentContainerId_ >= MIN_PA_SERVICE_ID) || parentContainerId_ < 0) {
        ShowToastForServiceStatic(toastInfo, std::move(callback));
    } else {
        ShowToastForAbilityStatic(toastInfo, std::move(callback));
    }
}

void SubwindowOhos::ShowToastForAbilityStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(
        AceLogTag::ACE_SUB_WINDOW, "show toast static for ability enter, containerId : %{public}d", childContainerId_);
    SetIsToastWindow(
        toastInfo.showMode == NG::ToastShowMode::TOP_MOST || toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST);
    auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
    if (!aceContainer) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "get container failed, child containerId : %{public}d", childContainerId_);
        return;
    }
    ContainerScope scope(childContainerId_);
    auto parentContainer = Platform::AceContainer::GetContainer(parentContainerId_);
    CHECK_NULL_VOID(parentContainer);
    if (parentContainer->IsSceneBoardWindow() || toastInfo.showMode == NG::ToastShowMode::TOP_MOST ||
        toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST) {
        ResizeWindow();
        auto currentWindow = SubwindowManager::GetInstance()->GetCurrentWindow();
        ShowWindow(false);
        SubwindowManager::GetInstance()->SetCurrentSubwindow(currentWindow);
        CHECK_NULL_VOID(window_);
        window_->SetTouchable(false);
    }
    NG::DialogManagerStatic::ShowToastStatic(toastInfo, std::move(callback), childContainerId_);
}

void SubwindowOhos::ShowToastForServiceStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    bool ret = CreateEventRunner();
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create event runner failed");
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentDialogSubwindow(AceType::Claim(this));
    if (!handler_->PostTask(GetInitToastDelayTaskStatic(toastInfo, std::move(callback)))) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create show dialog callback failed");
        return;
    }
}

std::function<void()> SubwindowOhos::GetInitToastDelayTaskStatic(const NG::ToastInfo& toastInfo,
    std::function<void(int32_t)>&& callback)
{
    return [toastInfo, callbackParam = std::move(callback)]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos =
            AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentDialogWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        auto childContainerId = subwindowOhos->GetChildContainerId();
        auto window = Platform::DialogContainer::GetUIWindow(childContainerId);
        auto dialogWindow = subwindowOhos->GetDialogWindow();
        if (!dialogWindow || !window || !subwindowOhos->IsToastWindow()) {
            bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY, true);
            if (!ret) {
                TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast dialog window failed");
                return;
            }
            ret = subwindowOhos->InitToastDialogView(width, height, density);
            if (!ret) {
                TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast dialog view failed");
                return;
            }
            subwindowOhos->SetIsToastWindow(true);
        }
        childContainerId = subwindowOhos->GetChildContainerId();
        ContainerScope scope(childContainerId);
        subwindowOhos->UpdateAceView(width, height, density, childContainerId);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW,
            "update ace view width : %{public}d,  height : %{public}d, density : %{public}f,childContainerId : "
            "%{public}d",
            width, height, density, childContainerId);
        auto container = Platform::AceContainer::GetContainer(childContainerId);
        CHECK_NULL_VOID(container);
        container->SetFontScaleAndWeightScale(childContainerId);
        auto ret = subwindowOhos->InitToastServiceConfig();
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast service conf failed");
        }
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height, true);
        Platform::DialogContainer::ShowToastStatic(childContainerId, toastInfo,
            std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
    };
}

void SubwindowOhos::CloseToastStatic(const int32_t toastId, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close toast enter");
    if (parentContainerId_ >= MIN_PA_SERVICE_ID || parentContainerId_ < 0) {
        auto subwindowOhos =
            AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentDialogWindow());
        CHECK_NULL_VOID(subwindowOhos);
        auto childContainerId = subwindowOhos->GetChildContainerId();
        CHECK_NULL_VOID(childContainerId);
        ContainerScope scope(childContainerId);
        Platform::DialogContainer::CloseToastStatic(childContainerId, toastId, std::move(callback));
    } else {
        auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
        CHECK_NULL_VOID(aceContainer);
        NG::DialogManagerStatic::CloseToastStatic(toastId, std::move(callback), childContainerId_);
    }
}

void SubwindowOhos::ShowDialogStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "show dialog with attr, window parent id is %{public}d", parentContainerId_);
    if (parentContainerId_ >= MIN_PA_SERVICE_ID || parentContainerId_ < 0) {
        ShowDialogForServiceStatic(dialogProps, std::move(callback));
    } else {
        ShowDialogForAbilityStatic(dialogProps, std::move(callback));
    }
}

void SubwindowOhos::ShowDialogForAbilityStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));

    auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
    if (!aceContainer) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get ace container failed");
        return;
    }
    NG::DialogManagerStatic::ShowDialogStatic(dialogProps, std::move(callback), childContainerId_);
}

void SubwindowOhos::ShowDialogForServiceStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    bool ret = CreateEventRunner();
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create event runner failed");
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentDialogSubwindow(AceType::Claim(this));
    auto showDialogCallback = [dialogProps, callbackParam = std::move(callback)]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos =
            AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentDialogWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast dialog window failed");
            return;
        }
        ret = subwindowOhos->InitToastDialogView(width, height, density);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast dialog view failed");
            return;
        }
        auto childContainerId = subwindowOhos->GetChildContainerId();
        ContainerScope scope(childContainerId);
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height);
        Platform::DialogContainer::ShowDialogStatic(childContainerId, dialogProps,
            std::move(const_cast<std::function<void(int32_t, int32_t)>&&>(callbackParam)));
    };
    isToastWindow_ = false;
    if (!handler_->PostTask(showDialogCallback)) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create show dialog callback failed");
        return;
    }
}

void SubwindowOhos::ShowActionMenuStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "show custom dialog, window parent id is %{public}d", parentContainerId_);
    if (parentContainerId_ >= MIN_PA_SERVICE_ID || parentContainerId_ < 0) {
        ShowActionMenuForServiceStatic(dialogProps, std::move(callback));
    } else {
        ShowActionMenuForAbilityStatic(dialogProps, std::move(callback));
    }
}

void SubwindowOhos::ShowActionMenuForAbilityStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show action menu for ability enter");
    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));

    auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
    if (!aceContainer) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get container failed");
        return;
    }
    NG::DialogManagerStatic::ShowActionMenuStatic(dialogProps, std::move(callback), childContainerId_);
}

void SubwindowOhos::ShowActionMenuForServiceStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show action menu for service enter");
    bool ret = CreateEventRunner();
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create event runner failed");
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentDialogSubwindow(AceType::Claim(this));
    auto showDialogCallback = [dialogProps, callbackParam = std::move(callback)]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos =
            AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentDialogWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY);
        if (!ret) {
            return;
        }
        ret = subwindowOhos->InitToastDialogView(width, height, density);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "init toast dialog view failed");
            return;
        }
        auto childContainerId = subwindowOhos->GetChildContainerId();
        ContainerScope scope(childContainerId);
        auto container = Platform::AceContainer::GetContainer(childContainerId);
        CHECK_NULL_VOID(container);
        container->SetFontScaleAndWeightScale(childContainerId);
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height);
        Platform::DialogContainer::ShowActionMenuStatic(childContainerId, dialogProps,
            std::move(const_cast<std::function<void(int32_t, int32_t)>&&>(callbackParam)));
    };
    isToastWindow_ = false;
    if (!handler_->PostTask(showDialogCallback)) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "create show dialog callback failed");
        return;
    }
}

void SubwindowOhos::OpenCustomDialogStatic(DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "open custom dialog, window parent id is %{public}d", parentContainerId_);
    if (parentContainerId_ >= MIN_PA_SERVICE_ID || parentContainerId_ < 0) {
        OpenCustomDialogForServiceStatic(dialogProps, std::move(callback));
    } else {
        OpenCustomDialogForAbilityStatic(dialogProps, std::move(callback));
    }
}

void SubwindowOhos::OpenCustomDialogForAbilityStatic(DialogProperties& dialogProps,
    std::function<void(int32_t)>&& callback)
{
    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));

    auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
    if (!aceContainer) {
        TAG_LOGW(
            AceLogTag::ACE_SUB_WINDOW, "open dialog fail, the container %{public}d can not find", childContainerId_);
        return;
    }
    NG::DialogManagerStatic::OpenCustomDialogStatic(dialogProps, std::move(callback), childContainerId_);
}

void SubwindowOhos::OpenCustomDialogForServiceStatic(DialogProperties& dialogProps,
    std::function<void(int32_t)>&& callback)
{
    // temporary not support
    TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "temporary not support for service by promptAction with CustomBuilder");
}
} // namespace OHOS::Ace
