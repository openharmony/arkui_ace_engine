/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <memory>
#include <mutex>

#include "unistd.h"

#include "base/geometry/rect.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"

namespace OHOS::Ace {

std::mutex SubwindowManager::instanceMutex_;
std::shared_ptr<SubwindowManager> SubwindowManager::instance_;

std::shared_ptr<SubwindowManager> SubwindowManager::GetInstance()
{
    std::lock_guard<std::mutex> lock(instanceMutex_);
    if (!instance_) {
        instance_ = std::make_shared<SubwindowManager>();
    }
    return instance_;
}

void SubwindowManager::AddContainerId(uint32_t windowId, int32_t containerId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto result = containerMap_.try_emplace(windowId, containerId);
    if (!result.second) {
        LOGW("Already have container of this windowId, windowId: %{public}u", windowId);
    }
}

void SubwindowManager::RemoveContainerId(uint32_t windowId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    containerMap_.erase(windowId);
}

int32_t SubwindowManager::GetContainerId(uint32_t windowId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto result = containerMap_.find(windowId);
    if (result != containerMap_.end()) {
        return result->second;
    } else {
        return -1;
    }
}

void SubwindowManager::AddParentContainerId(int32_t containerId, int32_t parentContainerId)
{
    LOGI("Container id is %{public}d, parent id is %{public}d.", containerId, parentContainerId);
    std::lock_guard<std::mutex> lock(parentMutex_);
    auto result = parentContainerMap_.try_emplace(containerId, parentContainerId);
    if (!result.second) {
        LOGW("Already have container of this %{public}d", containerId);
    }
}

void SubwindowManager::RemoveParentContainerId(int32_t containerId)
{
    std::lock_guard<std::mutex> lock(parentMutex_);
    parentContainerMap_.erase(containerId);
}

int32_t SubwindowManager::GetParentContainerId(int32_t containerId)
{
    std::lock_guard<std::mutex> lock(parentMutex_);
    auto result = parentContainerMap_.find(containerId);
    if (result != parentContainerMap_.end()) {
        return result->second;
    } else {
        return 0;
    }
}

void SubwindowManager::AddSubwindow(int32_t instanceId, RefPtr<Subwindow> subwindow)
{
    if (!subwindow) {
        LOGE("Add subwindow failed, the subwindow is null.");
        return;
    }
    LOGI("Add subwindow into map, instanceId is %{public}d, subwindow id is %{public}d.", instanceId,
        subwindow->GetSubwindowId());
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    auto result = subwindowMap_.try_emplace(instanceId, subwindow);
    if (!result.second) {
        LOGE("Add failed of this instance %{public}d", instanceId);
        return;
    }
    LOGI("Add subwindow success of this instance %{public}d.", instanceId);
}

void SubwindowManager::RemoveSubwindow(int32_t instanceId)
{
    LOGI("Remove subwindow of this instance %{public}d", instanceId);
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    int res = static_cast<int>(subwindowMap_.erase(instanceId));
    if (res == 0) {
        LOGW("Remove subwindow of instance %{public}d failed.", instanceId);
    }
}

const RefPtr<Subwindow> SubwindowManager::GetSubwindow(int32_t instanceId)
{
    LOGI("Get subwindow of instance %{public}d.", instanceId);
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    auto result = subwindowMap_.find(instanceId);
    if (result != subwindowMap_.end()) {
        return result->second;
    } else {
        return nullptr;
    }
}

void SubwindowManager::SetCurrentSubwindowName(const std::string& currentSubwindowName)
{
    std::lock_guard<std::mutex> lock(currentSubwindowMutex_);
    currentSubwindowName_ = currentSubwindowName;
}

std::string SubwindowManager::GetCurrentSubWindowName()
{
    std::lock_guard<std::mutex> lock(currentSubwindowMutex_);
    return currentSubwindowName_;
}

void SubwindowManager::SetCurrentSubwindow(const RefPtr<Subwindow>& subwindow)
{
    std::lock_guard<std::mutex> lock(currentSubwindowMutex_);
    currentSubwindow_ = subwindow;

    if (onShowMenuCallback_) {
        RegisterOnShowMenu(onShowMenuCallback_);
    }
    if (onHideMenuCallback_) {
        RegisterOnHideMenu(onHideMenuCallback_);
    }
}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentWindow()
{
    std::lock_guard<std::mutex> lock(currentSubwindowMutex_);
    return currentSubwindow_;
}

Rect SubwindowManager::GetParentWindowRect()
{
    std::lock_guard<std::mutex> lock(currentSubwindowMutex_);
    Rect rect;
    CHECK_NULL_RETURN(currentSubwindow_, rect);
    return currentSubwindow_->GetParentWindowRect();
}

void SubwindowManager::ShowMenuNG(const RefPtr<NG::FrameNode>& menuNode, int32_t targetId,
    const NG::OffsetF& offset, bool isAboveApps)
{
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, weakMenu = AceType::WeakClaim(AceType::RawPtr(menuNode)), targetId, offset, isAboveApps] {
            auto manager = SubwindowManager::GetInstance();
            CHECK_NULL_VOID(manager);
            auto menu = weakMenu.Upgrade();
            CHECK_NULL_VOID(menu);
            auto subwindow = manager->GetSubwindow(containerId);
            if (!subwindow) {
                LOGI("Subwindow is null, add a new one.");
                subwindow = Subwindow::CreateSubwindow(containerId);
                subwindow->SetAboveApps(isAboveApps);
                subwindow->InitContainer();
                manager->AddSubwindow(containerId, subwindow);
            }
            subwindow->ShowMenuNG(menu, targetId, offset);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void SubwindowManager::HideMenuNG(int32_t targetId)
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->HideMenuNG(targetId);
    }
}

void SubwindowManager::HideMenuNG()
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->HideMenuNG();
    }
}

void SubwindowManager::ClearMenuNG(int32_t instanceId)
{
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->ClearMenuNG();
    }
}

void SubwindowManager::ShowPopupNG(int32_t targetId, const NG::PopupInfo& popupInfo)
{
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, targetId, popupInfo] {
            auto manager = SubwindowManager::GetInstance();
            CHECK_NULL_VOID(manager);
            auto subwindow = manager->GetSubwindow(containerId);
            if (!subwindow) {
                LOGI("Subwindow is null, add a new one.");
                subwindow = Subwindow::CreateSubwindow(containerId);
                subwindow->InitContainer();
                manager->AddSubwindow(containerId, subwindow);
            }
            subwindow->ShowPopupNG(targetId, popupInfo);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void SubwindowManager::HidePopupNG(int32_t targetId, int32_t instanceId)
{
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }

    if (subwindow) {
        subwindow->HidePopupNG(targetId);
    }
}

void SubwindowManager::ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent)
{
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, newComponentWeak = WeakPtr<Component>(newComponent), disableTouchEvent] {
            auto manager = SubwindowManager::GetInstance();
            CHECK_NULL_VOID(manager);
            auto subwindow = manager->GetSubwindow(containerId);
            if (!subwindow) {
                LOGI("Subwindow is null, add a new one.");
                subwindow = Subwindow::CreateSubwindow(containerId);
                subwindow->InitContainer();
                manager->AddSubwindow(containerId, subwindow);
            }
            auto newComponent = newComponentWeak.Upgrade();
            CHECK_NULL_VOID(newComponent);
            subwindow->ShowPopup(newComponent, disableTouchEvent);
        },
        TaskExecutor::TaskType::PLATFORM);
}

bool SubwindowManager::CancelPopup(const std::string& id)
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        return subwindow->CancelPopup(id);
    }
    return false;
}

void SubwindowManager::ShowMenu(const RefPtr<Component>& newComponent)
{
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, newComponent] {
            auto manager = SubwindowManager::GetInstance();
            CHECK_NULL_VOID(manager);
            auto subwindow = manager->GetSubwindow(containerId);
            if (!subwindow) {
                LOGI("Subwindow is null, add a new one.");
                subwindow = Subwindow::CreateSubwindow(containerId);
                subwindow->InitContainer();
                manager->AddSubwindow(containerId, subwindow);
            }
            subwindow->ShowMenu(newComponent);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void SubwindowManager::CloseMenu()
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->CloseMenu();
    }
}

void SubwindowManager::ClearMenu()
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->ClearMenu();
    }
}

void SubwindowManager::SetHotAreas(const std::vector<Rect>& rects, int32_t overlayId, int32_t instanceId)
{
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }

    if (subwindow) {
        subwindow->SetHotAreas(rects, overlayId);
    }
}

RefPtr<NG::FrameNode> SubwindowManager::ShowDialogNG(
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc)
{
    auto containerId = Container::CurrentId();
    auto subwindow = GetSubwindow(containerId);
    if (!subwindow) {
        LOGI("Subwindow is null, add a new one.");
        subwindow = Subwindow::CreateSubwindow(containerId);
        subwindow->InitContainer();
        AddSubwindow(containerId, subwindow);
    }
    return subwindow->ShowDialogNG(dialogProps, std::move(buildFunc));
}

void SubwindowManager::AddDialogSubwindow(int32_t instanceId, const RefPtr<Subwindow>& subwindow)
{
    if (!subwindow) {
        LOGE("Add dialog subwindow failed, the subwindow is null.");
        return;
    }
    LOGI("Add dialog subwindow into map, instanceId is %{public}d, subwindow id is %{public}d.", instanceId,
        subwindow->GetSubwindowId());
    std::lock_guard<std::mutex> lock(dialogSubwindowMutex_);
    auto result = dialogSubwindowMap_.try_emplace(instanceId, subwindow);
    if (!result.second) {
        LOGE("Add dialog failed of this instance %{public}d", instanceId);
        return;
    }
    LOGI("Add dialog subwindow success of this instance %{public}d.", instanceId);
}

const RefPtr<Subwindow> SubwindowManager::GetDialogSubwindow(int32_t instanceId)
{
    LOGI("Get dialog subwindow of instance %{public}d.", instanceId);
    std::lock_guard<std::mutex> lock(dialogSubwindowMutex_);
    auto result = dialogSubwindowMap_.find(instanceId);
    if (result != dialogSubwindowMap_.end()) {
        return result->second;
    } else {
        return nullptr;
    }
}

void SubwindowManager::SetCurrentDialogSubwindow(const RefPtr<Subwindow>& subwindow)
{
    std::lock_guard<std::mutex> lock(currentDialogSubwindowMutex_);
    currentDialogSubwindow_ = subwindow;
}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentDialogWindow()
{
    std::lock_guard<std::mutex> lock(currentDialogSubwindowMutex_);
    return currentDialogSubwindow_;
}

RefPtr<Subwindow> SubwindowManager::GetOrCreateSubWindow()
{
    auto containerId = Container::CurrentId();
    LOGI("SubwindowManager::GetOrCreateSubWindow containerId = %{public}d.", containerId);
    auto subwindow = GetDialogSubwindow(containerId);
    if (!subwindow) {
        LOGI("Subwindow is null, add a new one.");
        subwindow = Subwindow::CreateSubwindow(containerId);
        AddDialogSubwindow(containerId, subwindow);
    }
    return subwindow;
}

void SubwindowManager::ShowToast(const std::string& message, int32_t duration, const std::string& bottom)
{
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
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowToast(message, duration, bottom);
        // for ability
    } else {
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [containerId, message, duration, bottom] {
                auto manager = SubwindowManager::GetInstance();
                CHECK_NULL_VOID(manager);
                auto subwindow = manager->GetSubwindow(containerId);
                if (!subwindow) {
                    LOGI("Subwindow is null, add a new one.");
                    subwindow = Subwindow::CreateSubwindow(containerId);
                    subwindow->InitContainer();
                    manager->AddSubwindow(containerId, subwindow);
                }
                subwindow->ShowToast(message, duration, bottom);
            },
            TaskExecutor::TaskType::PLATFORM);
    }
}

void SubwindowManager::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& napiCallback,
    const std::set<std::string>& dialogCallbacks)
{
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
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowDialog(title, message, buttons, autoCancel, std::move(napiCallback), dialogCallbacks);
        // for ability
    } else {
        auto subwindow = GetSubwindow(containerId);
        if (!subwindow) {
            LOGI("Subwindow is null, add a new one.");
            subwindow = Subwindow::CreateSubwindow(containerId);
            subwindow->InitContainer();
            AddSubwindow(containerId, subwindow);
        }
        subwindow->ShowDialog(title, message, buttons, autoCancel, std::move(napiCallback), dialogCallbacks);
    }
}

void SubwindowManager::ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
    std::function<void(int32_t, int32_t)>&& napiCallback, const std::set<std::string>& dialogCallbacks)
{
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
        auto subWindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subWindow);
        subWindow->ShowDialog(dialogAttr, buttons, std::move(napiCallback), dialogCallbacks);
        // for ability
    } else {
        auto subWindow = GetSubwindow(containerId);
        if (!subWindow) {
            LOGI("SubWindow is null, add a new one.");
            subWindow = Subwindow::CreateSubwindow(containerId);
            subWindow->InitContainer();
            AddSubwindow(containerId, subWindow);
        }
        subWindow->ShowDialog(dialogAttr, buttons, std::move(napiCallback), dialogCallbacks);
    }
}

void SubwindowManager::ShowActionMenu(
    const std::string& title, const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
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
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowActionMenu(title, button, std::move(callback));
        // for ability
    } else {
        auto subwindow = GetSubwindow(containerId);
        if (!subwindow) {
            LOGI("Subwindow is null, add a new one.");
            subwindow = Subwindow::CreateSubwindow(containerId);
            subwindow->InitContainer();
            AddSubwindow(containerId, subwindow);
        }
        subwindow->ShowActionMenu(title, button, std::move(callback));
    }
}

void SubwindowManager::CloseDialog(int32_t instanceId)
{
    LOGI("SubwindowManager::CloseDialog containerId = %{public}d.", instanceId);
    auto subwindow = GetDialogSubwindow(instanceId);
    if (!subwindow) {
        LOGE("SubwindowManager::CloseDialog Subwindow is null.");
        return;
    }
    for (auto& containerMap : parentContainerMap_) {
        if (containerMap.second == instanceId) {
            subwindow->CloseDialog(containerMap.first);
        }
    }
}

void SubwindowManager::HideSubWindowNG()
{
    RefPtr<Subwindow> subwindow;
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsDialogContainer()) {
        subwindow = GetCurrentDialogWindow();
    } else {
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->HideSubWindowNG();
    }
}

void SubwindowManager::RegisterOnShowMenu(const std::function<void()>& callback)
{
    onShowMenuCallback_ = callback;
    if (currentSubwindow_) {
        auto overlayManager = currentSubwindow_->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->RegisterOnShowMenu(callback);
    }
}

void SubwindowManager::RegisterOnHideMenu(const std::function<void()>& callback)
{
    onHideMenuCallback_ = callback;
    if (currentSubwindow_) {
        auto overlayManager = currentSubwindow_->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->RegisterOnHideMenu(callback);
    }
}

void SubwindowManager::RequestFocusSubwindow(int32_t instanceId)
{
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->RequestFocus();
    }
}
} // namespace OHOS::Ace
