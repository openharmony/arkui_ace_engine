/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

std::mutex SubwindowManager::instanceMutex_;
std::shared_ptr<SubwindowManager> SubwindowManager::instance_;
thread_local RefPtr<Subwindow> SubwindowManager::currentSubwindow_;

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
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Already have container of this windowId, windowId: %{public}u", windowId);
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
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Container id is %{public}d, parent id is %{public}d.", containerId,
        parentContainerId);
    std::lock_guard<std::mutex> lock(parentMutex_);
    parentContainerMap_.try_emplace(containerId, parentContainerId);
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
        return -1;
    }
}

int32_t SubwindowManager::GetSubContainerId(int32_t parentContainerId)
{
    std::lock_guard<std::mutex> lock(parentMutex_);
    for (auto it = parentContainerMap_.begin(); it != parentContainerMap_.end(); it++) {
        if (it->second == parentContainerId) {
            return it->first;
        }
    }
    return -1;
}

void SubwindowManager::AddSubwindow(int32_t instanceId, RefPtr<Subwindow> subwindow)
{
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "add subwindow failed.");
        return;
    }
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Add subwindow into map, instanceId is %{public}d, subwindow id is %{public}d.",
        instanceId, subwindow->GetSubwindowId());
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    auto result = subwindowMap_.try_emplace(searchKey, subwindow);
    if (!result.second) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Add failed of this instance %{public}d", instanceId);
        return;
    }
}

void SubwindowManager::AddToastSubwindow(int32_t instanceId, RefPtr<Subwindow> subwindow)
{
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "add toast subwindow failed.");
        return;
    }
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Add toast into map, instanceId is %{public}d, subwindow id is %{public}d.",
        instanceId, subwindow->GetSubwindowId());
    std::lock_guard<std::mutex> lock(toastMutex_);
    auto result = toastWindowMap_.try_emplace(searchKey, subwindow);
    if (!result.second) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Add toast failed of this instance %{public}d", instanceId);
        return;
    }
}

void SubwindowManager::AddSystemToastWindow(int32_t instanceId, RefPtr<Subwindow> subwindow)
{
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "add system toast subwindow failed.");
        return;
    }
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW,
        "Add system toast into map, instanceId is %{public}d, subwindow id is %{public}d.",
        instanceId, subwindow->GetSubwindowId());
    std::lock_guard<std::mutex> lock(systemToastMutex_);
    auto result = systemToastWindowMap_.try_emplace(searchKey, subwindow);
    if (!result.second) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Add system toast failed of this instance %{public}d", instanceId);
        return;
    }
}

void SubwindowManager::DeleteHotAreas(int32_t instanceId, int32_t nodeId)
{
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to get the subwindow which overlay node in, so get the current one.");
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->DeleteHotAreas(nodeId);
    }
}
void SubwindowManager::RemoveSubwindow(int32_t instanceId)
{
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    subwindowMap_.erase(searchKey);
}

const RefPtr<Subwindow> SubwindowManager::GetSubwindow(int32_t instanceId)
{
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    auto result = subwindowMap_.find(searchKey);
    if (result != subwindowMap_.end()) {
        return result->second;
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to find subwindow in subwindowMap_, searchKey is %{public}s.",
            searchKey.ToString().c_str());
        return nullptr;
    }
}

const RefPtr<Subwindow> SubwindowManager::GetSubwindow(int32_t instanceId, uint64_t displayId)
{
    SubwindowKey searchKey {.instanceId = instanceId, .displayId = displayId };
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    auto result = subwindowMap_.find(searchKey);
    if (result != subwindowMap_.end()) {
        return result->second;
    }
    TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to find subwindow in subwindowMap_, searchKey is %{public}s.",
        searchKey.ToString().c_str());
    return nullptr;
}

const RefPtr<Subwindow> SubwindowManager::GetToastSubwindow(int32_t instanceId)
{
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    std::lock_guard<std::mutex> lock(toastMutex_);
    auto result = toastWindowMap_.find(searchKey);
    if (result != toastWindowMap_.end()) {
        return result->second;
    }
    TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to find subwindow in toastWindowMap_, searchKey is %{public}s.",
        searchKey.ToString().c_str());
    return nullptr;
}

const RefPtr<Subwindow> SubwindowManager::GetSystemToastWindow(int32_t instanceId)
{
    SubwindowKey searchKey = GetCurrentSubwindowKey(instanceId);
    std::lock_guard<std::mutex> lock(systemToastMutex_);
    auto result = systemToastWindowMap_.find(searchKey);
    if (result != systemToastWindowMap_.end()) {
        return result->second;
    }
    TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to find subwindow in systemToastWindowMap_, searchKey is %{public}s.",
        searchKey.ToString().c_str());
    return nullptr;
}

const RefPtr<Subwindow> SubwindowManager::GetOrCreateSubwindow(int32_t instanceId)
{
    auto subwindow = GetSubwindow(instanceId);
    if (subwindow) {
        return subwindow;
    }

    subwindow = Subwindow::CreateSubwindow(instanceId);
    if (!subwindow) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Create sub window failed, instanceId is %{public}d.", instanceId);
        return nullptr;
    }
    AddSubwindow(instanceId, subwindow);
    return subwindow;
}

int32_t SubwindowManager::GetDialogSubwindowInstanceId(int32_t SubwindowId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "get dialog subwindow instanceid enter");
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    for (auto it = subwindowMap_.begin(); it != subwindowMap_.end(); it++) {
        if (it->second->GetSubwindowId() == SubwindowId) {
            return (it->first).instanceId;
        }
    }
    TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to get parentContainerId of subwindow in subwindowMap_,"
        "subwindowId is %{public}d.", SubwindowId);
    return 0;
}

void SubwindowManager::SetCurrentSubwindow(const RefPtr<Subwindow>& subwindow)
{
    currentSubwindow_ = subwindow;
}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentWindow()
{
    return currentSubwindow_;
}

Rect SubwindowManager::GetParentWindowRect()
{
    Rect rect;
    CHECK_NULL_RETURN(currentSubwindow_, rect);
    return currentSubwindow_->GetParentWindowRect();
}

RefPtr<Subwindow> SubwindowManager::ShowPreviewNG(bool isStartDraggingFromSubWindow)
{
    auto containerId = Container::CurrentId();
    auto subwindow =
        GetOrCreateSubwindow(containerId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(containerId) : containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return nullptr;
    }
    if (!subwindow->ShowPreviewNG(isStartDraggingFromSubWindow)) {
        return nullptr;
    }
    return subwindow;
}

void SubwindowManager::ShowMenuNG(const RefPtr<NG::FrameNode>& menuNode, const NG::MenuParam& menuParam,
    const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show menu ng enter");
    CHECK_NULL_VOID(targetNode);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return;
    }
    subwindow->ShowMenuNG(menuNode, menuParam, targetNode, offset);
}

void SubwindowManager::ShowMenuNG(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
    const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show menu ng enter");
    CHECK_NULL_VOID(targetNode);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return;
    }
    subwindow->ShowMenuNG(std::move(buildFunc), std::move(previewBuildFunc), menuParam, targetNode, offset);
}

void SubwindowManager::HidePreviewNG()
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->HidePreviewNG();
    }
}

void SubwindowManager::HideMenuNG(const RefPtr<NG::FrameNode>& menu, int32_t targetId)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "hide menu ng enter");
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->HideMenuNG(menu, targetId);
    }
}

void SubwindowManager::HideMenuNG(bool showPreviewAnimation, bool startDrag)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "hide menu ng enter");
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->HideMenuNG(showPreviewAnimation, startDrag);
    }
}

void SubwindowManager::UpdateHideMenuOffsetNG(
    const NG::OffsetF& offset, float menuScale, bool isRedragStart, int32_t menuWrapperId)
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->UpdateHideMenuOffsetNG(offset, menuScale, isRedragStart, menuWrapperId);
    }
}

void SubwindowManager::ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
    const NG::OffsetF& offset)
{
    CHECK_NULL_VOID(dragPreviewNode);
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->ContextMenuSwitchDragPreviewAnimationtNG(dragPreviewNode, offset);
    }
}

void SubwindowManager::UpdatePreviewPosition()
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->UpdatePreviewPosition();
    }
}

bool SubwindowManager::GetMenuPreviewCenter(NG::OffsetF& offset)
{
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        return subwindow->GetMenuPreviewCenter(offset);
    }
    return false;
}

void SubwindowManager::ClearMenuNG(int32_t instanceId, int32_t targetId, bool inWindow, bool showAnimation)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "clear menu ng enter");
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
#ifdef OHOS_STANDARD_SYSTEM
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
#else
        subwindow =
            GetSubwindow(GetParentContainerId(instanceId) != -1 ? GetParentContainerId(instanceId) : instanceId);
#endif
    } else {
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->ClearMenuNG(targetId, inWindow, showAnimation);
    }
}

void SubwindowManager::ClearPopupInSubwindow(int32_t instanceId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "clear popup in subwindow enter");
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }
    if (subwindow) {
        subwindow->ClearPopupNG();
    }
}

void SubwindowManager::ShowPopupNG(const RefPtr<NG::FrameNode>& targetNode, const NG::PopupInfo& popupInfo,
    const std::function<void(int32_t)>&& onWillDismiss, bool interactiveDismiss)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show popup ng enter");
    CHECK_NULL_VOID(targetNode);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto containerId = pipelineContext->GetInstanceId();

    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return;
    }
    subwindow->ShowPopupNG(targetNode->GetId(), popupInfo, std::move(onWillDismiss), interactiveDismiss);
}

void SubwindowManager::HidePopupNG(int32_t targetId, int32_t instanceId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "hide popup ng enter");
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to get the subwindow which overlay node in, so get the current one.");
        subwindow = GetCurrentWindow();
    }

    if (subwindow) {
        subwindow->HidePopupNG(targetId);
    }
}

void SubwindowManager::ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show popup enter");
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, newComponentWeak = WeakPtr<Component>(newComponent), disableTouchEvent] {
            auto subwindow = SubwindowManager::GetInstance()->GetOrCreateSubwindow(containerId);
            if (!subwindow) {
                TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
                return;
            }
            auto newComponent = newComponentWeak.Upgrade();
            CHECK_NULL_VOID(newComponent);
            subwindow->ShowPopup(newComponent, disableTouchEvent);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowPopup", PriorityType::VIP);
}

bool SubwindowManager::CancelPopup(const std::string& id)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "cancel popup enter");
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        return subwindow->CancelPopup(id);
    }
    return false;
}

void SubwindowManager::ShowMenu(const RefPtr<Component>& newComponent)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show menu enter");
    auto containerId = Container::CurrentId();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [containerId, weakMenu = AceType::WeakClaim(AceType::RawPtr(newComponent))] {
            auto menu = weakMenu.Upgrade();
            CHECK_NULL_VOID(menu);
            auto subwindow = SubwindowManager::GetInstance()->GetOrCreateSubwindow(containerId);
            if (!subwindow) {
                TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
                return;
            }
            subwindow->ShowMenu(menu);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowMenu", PriorityType::VIP);
}

void SubwindowManager::CloseMenu()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close menu enter");
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->CloseMenu();
    }
}

void SubwindowManager::ClearMenu()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "clear menu enter");
    auto subwindow = GetCurrentWindow();
    if (subwindow) {
        subwindow->ClearMenu();
    }
}

void SubwindowManager::SetHotAreas(const std::vector<Rect>& rects, int32_t nodeId, int32_t instanceId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "set hot areas enter");
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to get the subwindow which overlay node in, so get the current one.");
        subwindow = GetCurrentWindow();
    }

    if (subwindow) {
        subwindow->SetHotAreas(rects, nodeId);
    }
}

RefPtr<NG::FrameNode> SubwindowManager::ShowDialogNG(
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show dialog ng enter");
    auto containerId = Container::CurrentId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return nullptr;
    }
    return subwindow->ShowDialogNG(dialogProps, std::move(buildFunc));
}
RefPtr<NG::FrameNode> SubwindowManager::ShowDialogNGWithNode(const DialogProperties& dialogProps,
    const RefPtr<NG::UINode>& customNode)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show dialog ng enter");
    auto containerId = Container::CurrentId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return nullptr;
    }
    return subwindow->ShowDialogNGWithNode(dialogProps, customNode);
}
void SubwindowManager::CloseDialogNG(const RefPtr<NG::FrameNode>& dialogNode)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close dialog ng enter");
    auto containerId = Container::CurrentId();
    auto subwindow = GetSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get subwindow failed.");
        return;
    }
    return subwindow->CloseDialogNG(dialogNode);
}

void SubwindowManager::OpenCustomDialogNG(const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show customDialog ng enter");
    auto containerId = Container::CurrentId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return;
    }
    return subwindow->OpenCustomDialogNG(dialogProps, std::move(callback));
}

void SubwindowManager::CloseCustomDialogNG(int32_t dialogId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close customDialog ng enter");
    for (auto &overlay : GetAllSubOverlayManager()) {
        CHECK_NULL_VOID(overlay);
        if (overlay->GetDialogMap().find(dialogId) != overlay->GetDialogMap().end()) {
            return overlay->CloseCustomDialog(dialogId);
        }
    }
}

void SubwindowManager::CloseCustomDialogNG(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "close customDialog ng enter");
    for (auto &overlay : GetAllSubOverlayManager()) {
        CHECK_NULL_VOID(overlay);
        overlay->CloseCustomDialog(node, std::move(callback));
    }
}

void SubwindowManager::UpdateCustomDialogNG(
    const WeakPtr<NG::UINode>& node, const PromptDialogAttr &dialogAttr, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "update customDialog ng enter");
    DialogProperties dialogProperties = {
        .autoCancel = dialogAttr.autoCancel,
        .maskColor = dialogAttr.maskColor,
        .isSysBlurStyle = false
    };
    if (dialogAttr.alignment.has_value()) {
        dialogProperties.alignment = dialogAttr.alignment.value();
    }
    if (dialogAttr.offset.has_value()) {
        dialogProperties.offset = dialogAttr.offset.value();
    }
    for (auto &overlay : GetAllSubOverlayManager()) {
        if (overlay) {
            overlay->UpdateCustomDialog(node, dialogProperties, std::move(callback));
        }
    }
}

void SubwindowManager::HideDialogSubWindow(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "hide dialog subwindow enter");
#ifdef OHOS_STANDARD_SYSTEM
    auto subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
#else
    auto subwindow =
        GetSubwindow(GetParentContainerId(instanceId) != -1 ? GetParentContainerId(instanceId) : instanceId);
#endif
    CHECK_NULL_VOID(subwindow);
    auto overlay = subwindow->GetOverlayManager();
    CHECK_NULL_VOID(overlay);
    if (overlay->GetDialogMap().size() == 0) {
        subwindow->HideSubWindowNG();
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "fail to hide dialog subwindow, instanceId is %{public}d.", instanceId);
    }
}

void SubwindowManager::AddDialogSubwindow(int32_t instanceId, const RefPtr<Subwindow>& subwindow)
{
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Add dialog subwindow failed, the subwindow is null.");
        return;
    }
    std::lock_guard<std::mutex> lock(dialogSubwindowMutex_);
    auto result = dialogSubwindowMap_.try_emplace(instanceId, subwindow);
    if (!result.second) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Add dialog failed of this instance %{public}d", instanceId);
        return;
    }
}

const RefPtr<Subwindow> SubwindowManager::GetDialogSubwindow(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(dialogSubwindowMutex_);
    auto result = dialogSubwindowMap_.find(instanceId);
    if (result != dialogSubwindowMap_.end()) {
        return result->second;
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "Fail to get subwindow in dialogSubwindowMap_, instanceId is %{public}d",
            instanceId);
        return nullptr;
    }
}

void SubwindowManager::SetCurrentDialogSubwindow(const RefPtr<Subwindow>& subwindow)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "set current dialog subwindow enter");
    std::lock_guard<std::mutex> lock(currentDialogSubwindowMutex_);
    currentDialogSubwindow_ = subwindow;
}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentDialogWindow()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "get current dialog window enter");
    std::lock_guard<std::mutex> lock(currentDialogSubwindowMutex_);
    return currentDialogSubwindow_;
}

RefPtr<Subwindow> SubwindowManager::GetOrCreateSubWindow()
{
    auto containerId = Container::CurrentId();
    auto subwindow = GetDialogSubwindow(containerId);
    if (!subwindow) {
        subwindow = Subwindow::CreateSubwindow(containerId);
        CHECK_NULL_RETURN(subwindow, nullptr);
        AddDialogSubwindow(containerId, subwindow);
    }
    return subwindow;
}

RefPtr<Subwindow> SubwindowManager::GetOrCreateSystemSubWindow(int32_t containerId)
{
    auto subwindow = GetSystemToastWindow(containerId);
    if (!subwindow) {
        subwindow = Subwindow::CreateSubwindow(containerId);
        CHECK_NULL_RETURN(subwindow, nullptr);
        AddSystemToastWindow(containerId, subwindow);
    }
    return subwindow;
}

void SubwindowManager::ShowToastNG(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show toast ng enter");
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
            TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast : %{public}d", containerId);
            subwindow->ShowToast(toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowToastNG", PriorityType::VIP);
}

ToastWindowType SubwindowManager::GetToastWindowType(int32_t instanceId)
{
    auto parentContainer = Container::GetContainer(instanceId);
    CHECK_NULL_RETURN(parentContainer, ToastWindowType::TOAST_IN_TYPE_TOAST);
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "GetToastWindowType instanceId: %{public}d", instanceId);
    // toast window should be TOAST_IN_TYPE_APP_SUB_WINDOW when parent window is dialog window.
    if (parentContainer->IsMainWindow() || parentContainer->IsSubWindow() ||
        parentContainer->IsDialogWindow()) {
        return ToastWindowType::TOAST_IN_TYPE_APP_SUB_WINDOW;
    } else if (parentContainer->IsScenceBoardWindow()) {
        return ToastWindowType::TOAST_IN_TYPE_SYSTEM_FLOAT;
    } else if (parentContainer->IsSystemWindow()) {
        return ToastWindowType::TOAST_IN_TYPE_SYSTEM_SUB_WINDOW;
    } else if (parentContainer->IsUIExtensionWindow()) {
        if (parentContainer->IsHostMainWindow() || parentContainer->IsHostSubWindow() ||
            parentContainer->IsHostDialogWindow()) {
            return ToastWindowType::TOAST_IN_TYPE_APP_SUB_WINDOW;
        } else if (parentContainer->IsHostSceneBoardWindow()) {
            return ToastWindowType::TOAST_IN_TYPE_SYSTEM_FLOAT;
        } else if (parentContainer->IsHostSystemWindow()) {
            return ToastWindowType::TOAST_IN_TYPE_SYSTEM_SUB_WINDOW;
        }
    }
    return ToastWindowType::TOAST_IN_TYPE_TOAST;
}

void SubwindowManager::ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show toast enter");
    auto containerId = Container::CurrentId();
    auto isTopMost = toastInfo.showMode == NG::ToastShowMode::TOP_MOST;
    // for pa service
    if ((isTopMost && containerId >= MIN_PA_SERVICE_ID && containerId < MIN_SUBCONTAINER_ID) ||
        (!isTopMost && containerId >= MIN_PA_SERVICE_ID) || containerId < 0) {
        auto subwindow = toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST ?
            GetOrCreateSystemSubWindow(containerId) : GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->SetIsSystemTopMost(toastInfo.showMode == NG::ToastShowMode::SYSTEM_TOP_MOST);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast");
        subwindow->ShowToast(toastInfo, std::move(callback));
    } else {
        // for ability
        auto parentContainer = Container::GetContainer(containerId);
        // in scenceboard, system_top_most needs to go the old way,
        // default and top_most need to go showToastNG
        if (toastInfo.showMode == NG::ToastShowMode::TOP_MOST ||
            (parentContainer && parentContainer->IsScenceBoardWindow() &&
            toastInfo.showMode != NG::ToastShowMode::SYSTEM_TOP_MOST)) {
            ShowToastNG(toastInfo, std::move(callback));
            return;
        }
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [containerId, toastInfo, callbackParam = std::move(callback)] {
        auto subwindow = SubwindowManager::GetInstance()->GetOrCreateToastWindow(containerId, toastInfo.showMode);
                CHECK_NULL_VOID(subwindow);
                TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before show toast : %{public}d", containerId);
                subwindow->ShowToast(toastInfo, std::move(const_cast<std::function<void(int32_t)>&&>(callbackParam)));
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUISubwindowShowToast", PriorityType::VIP);
    }
}

void SubwindowManager::CloseToast(
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
        subwindow->CloseToast(toastId, std::move(callback));
    } else {
        // for ability
        if (showMode == NG::ToastShowMode::TOP_MOST) {
            auto subwindow = GetToastSubwindow(containerId);
            subwindow->CloseToast(toastId, std::move(callback));
            return;
        }
        auto manager = SubwindowManager::GetInstance();
        CHECK_NULL_VOID(manager);
        auto subwindow = showMode == NG::ToastShowMode::SYSTEM_TOP_MOST ?
            GetSystemToastWindow(containerId) : GetSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "before close toast : %{public}d", containerId);
        subwindow->CloseToast(toastId, std::move(callback));
    }
}

RefPtr<Subwindow> SubwindowManager::GetOrCreateToastWindow(int32_t containerId, const NG::ToastShowMode& showMode)
{
    auto isSystemTopMost = (showMode == NG::ToastShowMode::SYSTEM_TOP_MOST);
    RefPtr<Subwindow> subwindow = nullptr;
    if (isSystemTopMost) {
        subwindow = GetSystemToastWindow(containerId);
    } else {
        subwindow = GetSubwindow(containerId);
    }

    if (!subwindow) {
        subwindow = Subwindow::CreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "create sub window failed");
            return nullptr;
        }
        subwindow->SetIsSystemTopMost(isSystemTopMost);
        subwindow->SetAboveApps(showMode == NG::ToastShowMode::TOP_MOST);
        if (isSystemTopMost) {
            AddSystemToastWindow(containerId, subwindow);
        } else {
            AddSubwindow(containerId, subwindow);
        }
    }

    return subwindow;
}

RefPtr<Subwindow> SubwindowManager::GetOrCreateToastWindowNG(int32_t containerId,
    const ToastWindowType& windowType, uint32_t mainWindowId)
{
    RefPtr<Subwindow> subwindow = GetToastSubwindow(containerId);
    if (!subwindow) {
        subwindow = Subwindow::CreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "create toast subwindow failed");
            return nullptr;
        }
        subwindow->SetToastWindowType(windowType);
        subwindow->SetMainWindowId(mainWindowId);
        AddToastSubwindow(containerId, subwindow);
    }
    return subwindow;
}

void SubwindowManager::ClearToastInSubwindow()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "clear toast in subwindow enter");
    auto containerId = Container::CurrentId();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    RefPtr<Subwindow> subwindow;
    // The main window does not need to clear Toast
    if (containerId != -1 && containerId < MIN_SUBCONTAINER_ID) {
        // get the subwindow which overlay node in, not current
        auto parentContainerId = containerId >= MIN_SUBCONTAINER_ID ?
            GetParentContainerId(containerId) : containerId;
        subwindow = GetToastSubwindow(parentContainerId);
    }
    if (subwindow) {
        subwindow->ClearToast();
    }
}

void SubwindowManager::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& napiCallback,
    const std::set<std::string>& dialogCallbacks)
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
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowDialog(title, message, buttons, autoCancel, std::move(napiCallback), dialogCallbacks);
        // for ability
    } else {
        auto subwindow = GetOrCreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
            return;
        }
        subwindow->ShowDialog(title, message, buttons, autoCancel, std::move(napiCallback), dialogCallbacks);
    }
}

void SubwindowManager::ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
    std::function<void(int32_t, int32_t)>&& napiCallback, const std::set<std::string>& dialogCallbacks)
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
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->ShowDialog(dialogAttr, buttons, std::move(napiCallback), dialogCallbacks);
        // for ability
    } else {
        auto subwindow = GetOrCreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
            return;
        }
        subwindow->ShowDialog(dialogAttr, buttons, std::move(napiCallback), dialogCallbacks);
    }
}

void SubwindowManager::ShowActionMenu(
    const std::string& title, const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "show action menu enter");
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
        auto subwindow = GetOrCreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
            return;
        }
        subwindow->ShowActionMenu(title, button, std::move(callback));
    }
}

void SubwindowManager::CloseDialog(int32_t instanceId)
{
    auto subwindow = GetDialogSubwindow(instanceId);
    if (!subwindow) {
        subwindow = GetSubwindow(instanceId);
        if (subwindow) {
            subwindow->Close();
            return;
        }
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get dialog subwindow failed.");
        return;
    }
    auto subContainerId = GetSubContainerId(instanceId);
    if (subContainerId > -1) {
        subwindow->CloseDialog(subContainerId);
    }
}

void SubwindowManager::OpenCustomDialog(const PromptDialogAttr &dialogAttr, std::function<void(int32_t)> &&callback)
{
    PromptDialogAttr tmpPromptAttr = dialogAttr;
    tmpPromptAttr.showInSubWindow = false;
    auto containerId = Container::CurrentId();
    // for pa service
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "container %{public}d open the custom dialog", containerId);
    if (containerId >= MIN_PA_SERVICE_ID || containerId < 0) {
        auto subwindow = GetOrCreateSubWindow();
        CHECK_NULL_VOID(subwindow);
        subwindow->OpenCustomDialog(tmpPromptAttr, std::move(callback));
        // for ability
    } else {
        auto subwindow = GetOrCreateSubwindow(containerId);
        if (!subwindow) {
            TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
            return;
        }
        subwindow->OpenCustomDialog(tmpPromptAttr, std::move(callback));
    }
    return;
}

void SubwindowManager::CloseCustomDialog(const int32_t dialogId)
{
    auto containerId = Container::CurrentId();
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "CloseCustomDialog dialogId = %{public}d, containerId = %{public}d.",
        dialogId, containerId);
    auto subwindow = GetDialogSubwindow(containerId);
    if (!subwindow) {
        return;
    }
    subwindow->CloseCustomDialog(dialogId);
    return;
}

void SubwindowManager::CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback)
{
    auto containerId = Container::CurrentId();
    auto subwindow = GetDialogSubwindow(containerId);
    if (!subwindow) {
        return;
    }
    subwindow->CloseCustomDialog(node, std::move(callback));
    return;
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
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "fail to hide subwindow, subwindow is null.");
    }
}

void SubwindowManager::HideToastSubWindowNG()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "hide toast subwindow enter");
    RefPtr<Subwindow> subwindow;
    auto container = Container::Current();
    auto containerId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsDialogContainer()) {
        subwindow = GetCurrentDialogWindow();
    } else if (containerId != -1) {
        auto parentContainerId = containerId >= MIN_SUBCONTAINER_ID ?
            GetParentContainerId(containerId) : containerId;
        subwindow = GetToastSubwindow(parentContainerId);
    }
    if (subwindow) {
        subwindow->HideSubWindowNG();
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "fail to hide toast subwindow, subwindow is null.");
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

bool SubwindowManager::GetShown()
{
    auto containerId = Container::CurrentId();
    auto subwindow = GetOrCreateSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "get or create subwindow failed");
        return false;
    }
    return subwindow->GetShown();
}

void SubwindowManager::ResizeWindowForFoldStatus(int32_t parentContainerId)
{
    auto containerId = Container::CurrentId();
    auto subwindow = parentContainerId < 0 || parentContainerId >= MIN_PA_SERVICE_ID ?
        GetDialogSubwindow(parentContainerId) : GetToastSubwindow(containerId);
    if (!subwindow) {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW,
            "Get Subwindow error, containerId = %{public}d, parentContainerId = %{public}d", containerId,
            parentContainerId);
        return;
    }
    subwindow->ResizeWindowForFoldStatus(parentContainerId);
}

void SubwindowManager::MarkDirtyDialogSafeArea()
{
    auto containerId = Container::CurrentId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
    CHECK_NULL_VOID(subwindow);
    if (subwindow) {
        subwindow->MarkDirtyDialogSafeArea();
    }
    subwindow = GetToastSubwindow(containerId);
    if (subwindow) {
        subwindow->MarkDirtyDialogSafeArea();
    }
}

void SubwindowManager::HideSystemTopMostWindow()
{
    auto containerId = Container::CurrentId();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    auto parentContainerId = containerId >= MIN_SUBCONTAINER_ID ?
            GetParentContainerId(containerId) : containerId;
    auto subwindow = GetSystemToastWindow(parentContainerId);
    if (subwindow) {
        subwindow->HideSubWindowNG();
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "can not find systemTopMost window when hide window");
    }
}

void SubwindowManager::ClearToastInSystemSubwindow()
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "clear toast in system subwindow enter");
    auto containerId = Container::CurrentId();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    RefPtr<Subwindow> subwindow;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        if (containerId != -1 && containerId < MIN_SUBCONTAINER_ID) {
            subwindow = GetSystemToastWindow(containerId);
        }
    } else {
        auto parentContainerId = containerId >= MIN_SUBCONTAINER_ID ?
            GetParentContainerId(containerId) : containerId;
        subwindow = GetSystemToastWindow(parentContainerId);
    }
    if (subwindow) {
        subwindow->ClearToast();
    } else {
        TAG_LOGW(AceLogTag::ACE_SUB_WINDOW, "can not find systemTopMost window when clear system toast");
    }
}
void SubwindowManager::OnWindowSizeChanged(int32_t instanceId, Rect windowRect, WindowSizeChangeReason reason)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    if (!container->IsUIExtensionWindow() || uiExtensionWindowRect_ == windowRect) {
        return;
    }
    auto subContainer = Container::GetContainer(GetSubContainerId(instanceId));
    CHECK_NULL_VOID(subContainer);
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(subContainer->GetPipelineContext());
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->OnUIExtensionWindowSizeChange();
    uiExtensionWindowRect_ = windowRect;
}

void SubwindowManager::FlushSubWindowUITasks(int32_t instanceId)
{
    auto subwindowContainerId = GetSubContainerId(instanceId);
    if (subwindowContainerId >= MIN_SUBCONTAINER_ID) {
        auto subPipline = NG::PipelineContext::GetContextByContainerId(subwindowContainerId);
        CHECK_NULL_VOID(subPipline);
        ContainerScope scope(subwindowContainerId);
        subPipline->FlushUITasks();
    }
}

RefPtr<NG::FrameNode> SubwindowManager::GetSubwindowDialogNodeWithExistContent(const RefPtr<NG::UINode>& node)
{
    for (auto &overlay : GetAllSubOverlayManager()) {
        CHECK_NULL_RETURN(overlay, nullptr);
        auto dialogNode = overlay->GetDialogNodeWithExistContent(node);
        if (dialogNode) {
            return dialogNode;
        }
    }
    return nullptr;
}

void SubwindowManager::SetRect(const NG::RectF& rect, int32_t instanceId)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "set subwindow rect enter");
    RefPtr<Subwindow> subwindow;
    if (instanceId != -1) {
        // get the subwindow which overlay node in, not current
        subwindow = GetSubwindow(instanceId >= MIN_SUBCONTAINER_ID ? GetParentContainerId(instanceId) : instanceId);
    } else {
        subwindow = GetCurrentWindow();
    }

    if (subwindow) {
        subwindow->SetRect(rect);
    } else {
        TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "can not get subwindow, set rect failed");
    }
}

bool SubwindowManager::IsFreeMultiWindow(int32_t instanceId) const
{
    auto parentContainerId = instanceId >= MIN_SUBCONTAINER_ID
                                 ? SubwindowManager::GetInstance()->GetParentContainerId(instanceId)
                                 : instanceId;
    auto subWindow = SubwindowManager::GetInstance()->GetSubwindow(parentContainerId);
    CHECK_NULL_RETURN(subWindow, false);
    return subWindow->IsFreeMultiWindow();
}

const std::vector<RefPtr<NG::OverlayManager>> SubwindowManager::GetAllSubOverlayManager()
{
    std::lock_guard<std::mutex> lock(subwindowMutex_);
    std::vector<RefPtr<NG::OverlayManager>> subOverlayManager;
    subOverlayManager.reserve(subwindowMap_.size());
    auto iter = subwindowMap_.begin();
    while (iter != subwindowMap_.end()) {
        auto subwindow = iter->second;
        if (subwindow) {
            subOverlayManager.push_back(subwindow->GetOverlayManager());
        }
        iter++;
    }
    return subOverlayManager;
}

SubwindowKey SubwindowManager::GetCurrentSubwindowKey(int32_t instanceId)
{
    uint64_t displayId = 0;
    SubwindowKey searchKey;
    searchKey.instanceId = instanceId;
    auto container = Container::GetContainer(instanceId);
    if (container) {
        displayId = container->GetCurrentDisplayId();
    }
    searchKey.displayId = displayId;
    return searchKey;
}
} // namespace OHOS::Ace
