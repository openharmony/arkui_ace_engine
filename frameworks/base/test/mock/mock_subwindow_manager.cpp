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
#include "base/subwindow/subwindow_manager.h"
#include "core/common/container.h"
namespace OHOS::Ace {
namespace {
static RefPtr<Subwindow> g_currentWindow;
}

std::shared_ptr<SubwindowManager> SubwindowManager::instance_;

std::shared_ptr<SubwindowManager> SubwindowManager::GetInstance()
{
    if (!instance_) {
        instance_ = std::make_shared<SubwindowManager>();
    }
    return instance_;
}

void SubwindowManager::HidePopupNG(int32_t targetId)
{
    LOGI("SubwindowManager::HidePopupNG MOCK");
}

void SubwindowManager::ShowPopupNG(int32_t targetId, const NG::PopupInfo& popupInfo) {}

void SubwindowManager::HideMenuNG(int32_t targetId) {}

void SubwindowManager::HideMenuNG() {}

void SubwindowManager::SetHotAreas(const std::vector<Rect>& rects) {}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentWindow()
{
    return g_currentWindow;
}

Rect SubwindowManager::GetParentWindowRect()
{
    return Rect();
}

const RefPtr<Subwindow>& SubwindowManager::GetCurrentDialogWindow()
{
    std::lock_guard<std::mutex> lock(currentDialogSubwindowMutex_);
    return currentDialogSubwindow_;
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

} // namespace OHOS::Ace
