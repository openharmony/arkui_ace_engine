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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_MANAGER_H

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/manager/select_content_overlay/selection_container.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectionContainerManager : public virtual AceType {
    DECLARE_ACE_TYPE(SelectionContainerManager, AceType);

public:
    SelectionContainerManager() = default;
    ~SelectionContainerManager() override = default;

    void RegisterSelectionContainer(int32_t selectionContainerId, const RefPtr<SelectionContainer>& selectionContainer);
    void UnregisterSelectionContainer(int32_t selectionContainerId);
    RefPtr<SelectionContainer> GetSelectionContainer(int32_t selectionContainerId);

    void RegisterChild(
        int32_t selectionContainerId, const RefPtr<SelectionContainerChild>& selectionContainerChild);
    void UnregisterChild(int32_t selectionContainerId, int32_t childId);
    bool HandleSelectionStart(int32_t selectionContainerId, const SelectionStartEventInfo& eventInfo);
    bool HandleSelectionUpdate(int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo);
    bool ProcessGestureSelectionEnd(int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo);
    bool ProcessMouseLeftRelease(int32_t selectionContainerId, const SelectionEndEventInfo& eventInfo);
    void MarkChildSortDirty(int32_t selectionContainerId);
    void RefreshChildSortResult(int32_t selectionContainerId);
    std::vector<WeakPtr<SelectionContainerChild>> GetChildList(int32_t selectionContainerId);

private:
    std::unordered_map<int32_t, WeakPtr<SelectionContainer>> selectionContainerMap_;

    ACE_DISALLOW_COPY_AND_MOVE(SelectionContainerManager);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_MANAGER_H
