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

#include "base/subwindow/subwindow_manager.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
void SubwindowManager::ShowToastStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show toast static enter");
    auto containerId = Container::CurrentId();
    bool isTopMost = toastInfo.showMode == NG::ToastShowMode::TOP_MOST;
    // for pa service
    if ((isTopMost && containerId >= MIN_PA_SERVICE_ID && containerId < MIN_SUBCONTAINER_ID) ||
        (!isTopMost && containerId >= MIN_PA_SERVICE_ID) || containerId < 0) {
        auto subwindow = toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST ?
            GetOrCreateSystemSubWindow(containerId) : GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->SetIsSystemTopMost(toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast static");
        subwindow->ShowToastStatic(toastInfo, std::move(callback));
    } else {
        // for ability
        auto parentContainer = Container::GetContainer(containerId);
        // in scenceboard, system_top_most needs to go the old way,
        // default and top_most need to go showToastNG
        if (toastInfo.showMode == NG::ToastShowMode::TOP_MOST ||
            (parentContainer && parentContainer->IsSceneBoardWindow() &&
            toastInfo.showMode != NG::ToastShowMode::SYSTEM_TOP_MOST)) {
            ShowToastNGStatic(toastInfo, std::move(callback));
            return;
        }
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [containerId, toastInfo, callbackParam = std::move(callback)] {
                auto manager = SubwindowManager::GetInstance();
                CHECK_NULL_VOID(manager);
                auto subwindow = manager->GetOrCreateToastWindow(containerId, toastInfo.showMode);
                CHECK_NULL_VOID(subwindow);
                TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast static : %{public}d", containerId);
                subwindow->ShowToastStatic(
                    toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowToastStatic");
    }
}

void SubwindowManager::ShowToastNGStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show toast ng static enter");
    auto containerId = Container::CurrentId();
    auto windowType = GetToastWindowType(containerId);
    auto container = Container::GetContainer(containerId);
    CHECK_NULL_VOID(container);
    auto windowId = container->GetWindowId();
    // Get the parent window ID before the asynchronous operation
    auto mainWindowId = container->GetParentMainWindowId(windowId);
    // for ability
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, toastInfo, callbackParam = std::move(callback), windowType, mainWindowId] {
            auto subwindow = SubwindowManager::GetInstance()->GetOrCreateToastWindowNG(
                containerId, windowType, mainWindowId);
            CHECK_NULL_VOID(subwindow);
            TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast static : %{public}d", containerId);
            subwindow->ShowToastStatic(
                toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowToastNGStatic");
}

void SubwindowManager::CloseToastStatic(
    const int32_t toastId, const NG::ToastShowMode& showMode, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close toast enter");
    auto containerId = Container::CurrentId();
    if (containerId >= MIN_PA_SERVICE_ID || containerId < 0) {
        // for pa service
        auto subwindow = showMode == NG::ToastShowMode::SYSTEM_TOP_MOST ?
            GetSystemToastWindow(containerId) : GetDialogSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        subwindow->SetIsSystemTopMost(showMode == NG::ToastShowMode::SYSTEM_TOP_MOST);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before close toast");
        subwindow->CloseToastStatic(toastId, std::move(callback));
    } else {
        // for ability
        if (showMode == NG::ToastShowMode::TOP_MOST) {
            auto subwindow =
                containerId < MIN_SUBCONTAINER_ID ? GetToastSubwindow(containerId) : GetSubwindow(containerId);
            CHECK_NULL_VOID(subwindow);
            subwindow->CloseToastStatic(toastId, std::move(callback));
            return;
        }
        auto manager = SubwindowManager::GetInstance();
        CHECK_NULL_VOID(manager);
        auto subwindow = (showMode == NG::ToastShowMode::SYSTEM_TOP_MOST && containerId < MIN_SUBCONTAINER_ID)
                            ? GetSystemToastWindow(containerId)
                            : GetSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before close toast : %{public}d", containerId);
        subwindow->CloseToastStatic(toastId, std::move(callback));
    }
}

void SubwindowManager::ShowDialogStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show dialog enter");
    auto containerId = Container::CurrentId();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    if (containerId >= MIN_PA_SERVICE_ID || containerId < 0) {
        auto subwindow = GetOrCreateSubWindow(true);
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowDialogStatic(dialogProps, std::move(callback));
        // for ability
    } else {
        auto subwindow = GetSubwindowByType(containerId, SubwindowType::TYPE_DIALOG);
        if (!IsSubwindowExist(subwindow)) {
            subwindow = Subwindow::CreateSubwindow(containerId);
            CHECK_NULL_VOID(subwindow);
            CHECK_NULL_VOID(subwindow->CheckHostWindowStatus());
            subwindow->InitContainer();
            CHECK_NULL_VOID(subwindow->GetIsRosenWindowCreate());
            AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, subwindow);
        }
        subwindow->ShowDialogStatic(dialogProps, std::move(callback));
    }
}

void SubwindowManager::ShowActionMenuStatic(DialogProperties& dialogProps,
    std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show action menu static enter");
    auto containerId = Container::CurrentId();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    if (containerId >= MIN_PA_SERVICE_ID || containerId < 0) {
        auto subwindow = GetOrCreateSubWindow(true);
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowActionMenuStatic(dialogProps, std::move(callback));
        // for ability
    } else {
        auto subwindow = GetSubwindowByType(containerId, SubwindowType::TYPE_DIALOG);
        if (!IsSubwindowExist(subwindow)) {
            subwindow = Subwindow::CreateSubwindow(containerId);
            CHECK_NULL_VOID(subwindow);
            CHECK_NULL_VOID(subwindow->CheckHostWindowStatus());
            subwindow->InitContainer();
            CHECK_NULL_VOID(subwindow->GetIsRosenWindowCreate());
            AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, subwindow);
        }
        subwindow->ShowActionMenuStatic(dialogProps, std::move(callback));
    }
}

void SubwindowManager::OpenCustomDialogStatic(DialogProperties &dialogProps,
    std::function<void(int32_t)> &&callback)
{
    DialogProperties tmpDialogProps = dialogProps;
    tmpDialogProps.isShowInSubWindow = false;
    auto containerId = Container::CurrentId();
    // for pa service
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "container %{public}d open the custom dialog static", containerId);
    if (containerId >= MIN_PA_SERVICE_ID || containerId < 0) {
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->OpenCustomDialogStatic(tmpDialogProps, std::move(callback));
        // for ability
    } else {
        auto subwindow = GetSubwindowByType(containerId, SubwindowType::TYPE_DIALOG);
        if (!IsSubwindowExist(subwindow)) {
            subwindow = Subwindow::CreateSubwindow(containerId);
            CHECK_NULL_VOID(subwindow);
            CHECK_NULL_VOID(subwindow->CheckHostWindowStatus());
            subwindow->InitContainer();
            CHECK_NULL_VOID(subwindow->GetIsRosenWindowCreate());
            AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, subwindow);
        }
        subwindow->OpenCustomDialogStatic(tmpDialogProps, std::move(callback));
    }
    return;
}
} // namespace OHOS::Ace
