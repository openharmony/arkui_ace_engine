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

#include "core/components_ng/manager/select_content_overlay/selection_container_manager.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void SelectionContainerManager::RegisterSelectionContainer(
    int32_t selectionContainerId, const RefPtr<SelectionContainer>& selectionContainer)
{
    CHECK_NULL_VOID(selectionContainer);
    selectionContainerMap_[selectionContainerId] = selectionContainer;
}

void SelectionContainerManager::UnregisterSelectionContainer(int32_t selectionContainerId)
{
    auto container = GetSelectionContainer(selectionContainerId);
    if (container) {
        auto childList = container->GetChildList();
        for (const auto& weakChild : childList) {
            auto child = weakChild.Upgrade();
            if (child) {
                child->ClearSelectionContainer();
            }
        }
    }
    selectionContainerMap_.erase(selectionContainerId);
}

RefPtr<SelectionContainer> SelectionContainerManager::GetSelectionContainer(int32_t selectionContainerId)
{
    auto iter = selectionContainerMap_.find(selectionContainerId);
    if (iter == selectionContainerMap_.end()) {
        return nullptr;
    }
    auto selectionContainer = iter->second.Upgrade();
    if (!selectionContainer) {
        selectionContainerMap_.erase(iter);
        return nullptr;
    }
    return selectionContainer;
}

void SelectionContainerManager::RegisterChild(
    int32_t selectionContainerId, const RefPtr<SelectionContainerChild>& child)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_VOID(container);
    container->RegisterChild(child);
    child->SetSelectionContainer(container);
}

void SelectionContainerManager::UnregisterChild(int32_t selectionContainerId, int32_t childId)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_VOID(container);
    auto childList = container->GetChildList();
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto childNode = child->GetHostNode();
        if (childNode && childNode->GetId() == childId) {
            child->ClearSelectionContainer();
            break;
        }
    }
    container->UnregisterChild(childId);
}

bool SelectionContainerManager::HandleSelectionStart(
    int32_t selectionContainerId, const SelectionStartEventInfo& eventInfo)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->HandleSelectionStart(eventInfo);
}

bool SelectionContainerManager::HandleSelectionUpdate(
    int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->HandleSelectionUpdate(eventInfo);
}

bool SelectionContainerManager::ProcessGestureSelectionEnd(
    int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->ProcessGestureSelectionEnd(eventInfo);
}

bool SelectionContainerManager::ProcessMouseLeftRelease(
    int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->ProcessMouseLeftRelease(eventInfo);
}

void SelectionContainerManager::MarkChildSortDirty(int32_t selectionContainerId)
{
    auto container = GetSelectionContainer(selectionContainerId);
    CHECK_NULL_VOID(container);
    container->MarkChildSortDirty();
}

void SelectionContainerManager::RefreshChildSortResult(int32_t selectionContainerId)
{
    auto container = GetSelectionContainer(selectionContainerId);
    if (!container) {
        return;
    }
    container->RefreshChildSortResult();
}

std::vector<WeakPtr<SelectionContainerChild>> SelectionContainerManager::GetChildList(
    int32_t selectionContainerId)
{
    auto container = GetSelectionContainer(selectionContainerId);
    if (!container) {
        return {};
    }
    return container->GetChildList();
}

} // namespace OHOS::Ace::NG
