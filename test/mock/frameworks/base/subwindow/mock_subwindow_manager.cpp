/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/geometry/rect.h"
#include "base/log/log_wrapper.h"
#include "base/subwindow/subwindow_manager.h"

namespace OHOS::Ace {
namespace {
static RefPtr<Subwindow> g_currentWindow;
} // namespace

std::shared_ptr<SubwindowManager> SubwindowManager::instance_;

std::shared_ptr<SubwindowManager> SubwindowManager::GetInstance()
{
    if (!instance_) {
        instance_ = std::make_shared<SubwindowManager>();
    }
    return instance_;
}

void SubwindowManager::HidePopupNG(int32_t targetId, int32_t instanceId) {}

void SubwindowManager::ShowPopupNG(const RefPtr<NG::FrameNode>& targetNode, const NG::PopupInfo& popupInfo,
    const std::function<void(int32_t)>&& onWillDismiss, bool interactiveDismiss)
{}
void SubwindowManager::ShowTipsNG(const RefPtr<NG::FrameNode>& targetNode, const NG::PopupInfo& popupInfo,
    int32_t appearingTime, int32_t appearingTimeWithContinuousOperation)
{}
void SubwindowManager::HideTipsNG(int32_t targetId, int32_t disappearingTime, int32_t instanceId) {}
void SubwindowManager::HideMenuNG(const RefPtr<NG::FrameNode>& menu, int32_t targetId) {}

void SubwindowManager::HideMenuNG(bool showPreviewAnimation, bool startDrag) {}

void SubwindowManager::SetHotAreas(
    const std::vector<Rect>& rects, SubwindowType type, int32_t overlayId, int32_t instanceId) {}

void SubwindowManager::HideSubWindowNG() {}

const RefPtr<Subwindow> SubwindowManager::GetCurrentWindow()
{
    return g_currentWindow;
}

Rect SubwindowManager::GetParentWindowRect()
{
    return Rect();
}

int32_t SubwindowManager::GetParentContainerId(int32_t containerId)
{
    return -1;
}

int32_t SubwindowManager::GetSubContainerId(int32_t parentContainerId)
{
    return -1;
}

const std::vector<int32_t> SubwindowManager::GetAllSubContainerId(int32_t parentContainerId)
{
    (void)parentContainerId;
    return {};
}

const RefPtr<Subwindow> SubwindowManager::GetSubwindow(int32_t instanceId)
{
    return nullptr;
}

const RefPtr<Subwindow> SubwindowManager::GetSubwindowByType(int32_t instanceId, SubwindowType windowType, int32_t nodeId)
{
    (void)instanceId;
    (void)windowType;
    (void)nodeId;
    return nullptr;
}

void SubwindowManager::ResizeWindowForFoldStatus(int32_t parentContainerId) {}

void SubwindowManager::MarkDirtyDialogSafeArea() {}

void SubwindowManager::ClearAllMenuPopup(int32_t instanceId)
{
    (void)instanceId;
}

void SubwindowManager::ClearToastInSubwindow() {}

void SubwindowManager::ClearToastInSystemSubwindow() {}

void SubwindowManager::FlushSubWindowUITasks(int32_t instanceId)
{
    (void)instanceId;
}
} // namespace OHOS::Ace
