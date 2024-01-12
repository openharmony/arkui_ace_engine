/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
std::bitset<UI_EXTENSION_ID_FIRST_MAX> UIExtensionManager::UIExtensionIdUtility::idPool_;
std::mutex UIExtensionManager::UIExtensionIdUtility::poolMutex_;
int32_t UIExtensionManager::UIExtensionIdUtility::ApplyExtensionId()
{
    std::lock_guard<std::mutex> poolMutex(UIExtensionManager::UIExtensionIdUtility::poolMutex_);
    for (int32_t index = 0; index < UI_EXTENSION_ID_FIRST_MAX; index++) {
        if (!UIExtensionManager::UIExtensionIdUtility::idPool_.test(index)) {
            UIExtensionManager::UIExtensionIdUtility::idPool_.set(index, 1);
            return index + 1;
        }
    }
    return UI_EXTENSION_UNKNOW_ID;
}

void UIExtensionManager::UIExtensionIdUtility::RecycleExtensionId(int32_t id)
{
    std::lock_guard<std::mutex> poolMutex(UIExtensionManager::UIExtensionIdUtility::poolMutex_);
    if ((id > UI_EXTENSION_UNKNOW_ID) && (id <= UI_EXTENSION_ID_FIRST_MAX)) {
        UIExtensionManager::UIExtensionIdUtility::idPool_.set(id - 1, 0);
    }
}

void UIExtensionManager::RegisterUIExtensionInFocus(
    const WeakPtr<UIExtensionPattern>& uiExtensionFocused, const WeakPtr<SessionWrapper>& sessionWrapper)
{
    uiExtensionFocused_ = uiExtensionFocused;
    sessionWrapper_ = sessionWrapper;
}

bool UIExtensionManager::OnBackPressed()
{
    auto sessionWrapper = sessionWrapper_.Upgrade();
    return sessionWrapper && sessionWrapper->NotifyBackPressedSync();
}

bool UIExtensionManager::IsWrapExtensionAbilityId(int64_t elementId)
{
    return elementId > UI_EXTENSION_OFFSET_MIN;
}

bool UIExtensionManager::IsWindowTypeUIExtension(const RefPtr<PipelineBase>& pipeline)
{
    auto instanceId = pipeline->GetInstanceId();
    auto window = Platform::AceContainer::GetUIWindow(instanceId);
    CHECK_NULL_RETURN(window, false);
    return window->GetType() == OHOS::Rosen::WindowType::WINDOW_TYPE_UI_EXTENSION;
}

bool UIExtensionManager::SendAccessibilityEventInfo(const Accessibility::AccessibilityEventInfo& eventInfo,
    int64_t uiExtensionOffset, const RefPtr<PipelineBase>& pipeline)
{
    CHECK_NULL_RETURN(pipeline, false);
    auto instanceId = pipeline->GetInstanceId();
    auto window = Platform::AceContainer::GetUIWindow(instanceId);
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->TransferAccessibilityEvent(eventInfo, uiExtensionOffset);
    return ret == OHOS::Rosen::WMError::WM_OK;
}

std::pair<int64_t, int64_t> UIExtensionManager::UnWrapExtensionAbilityId(int64_t extensionOffset, int64_t elementId)
{
    if (extensionOffset == 0) {
        return std::pair<int64_t, int64_t>(0, 0);
    }
    int64_t index = elementId / extensionOffset;
    int64_t abilityId = elementId % extensionOffset;
    return std::pair<int64_t, int64_t>(index, abilityId);
}

const RefPtr<FrameNode> UIExtensionManager::GetFocusUiExtensionNode()
{
    auto uiExtensionFocused = uiExtensionFocused_.Upgrade();
    CHECK_NULL_RETURN(uiExtensionFocused, nullptr);
    return uiExtensionFocused->GetHost();
}

int32_t UIExtensionManager::ApplyExtensionId()
{
    CHECK_NULL_RETURN(extensionIdUtility_, UI_EXTENSION_UNKNOW_ID);
    return extensionIdUtility_->ApplyExtensionId();
}

void UIExtensionManager::RecycleExtensionId(int32_t id)
{
    CHECK_NULL_VOID(extensionIdUtility_);
    extensionIdUtility_->RecycleExtensionId(id);
}

void UIExtensionManager::AddAliveUIExtension(int32_t nodeId, const WeakPtr<UIExtensionPattern>& uiExtension)
{
    aliveUIExtensions_.try_emplace(nodeId, uiExtension);
}

void UIExtensionManager::TransferOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type)
{
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->DispatchOriginAvoidArea(avoidArea, type);
        }
    }
}

void UIExtensionManager::RemoveDestroyedUIExtension(int32_t nodeId)
{
    auto it = aliveUIExtensions_.find(nodeId);
    if (it != aliveUIExtensions_.end()) {
        aliveUIExtensions_.erase(nodeId);
    }
}

bool UIExtensionManager::NotifyOccupiedAreaChangeInfo(const sptr<Rosen::OccupiedAreaChangeInfo>& info)
{
    auto sessionWrapper = sessionWrapper_.Upgrade();
    return sessionWrapper && sessionWrapper->NotifyOccupiedAreaChangeInfo(info);
}
} // namespace OHOS::Ace::NG
