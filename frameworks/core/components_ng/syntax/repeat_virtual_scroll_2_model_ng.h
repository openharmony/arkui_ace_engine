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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_MODEL_NG_H

#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <vector>

#include "base/utils/macros.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RepeatVirtualScroll2ModelNG : public RepeatVirtualScroll2Model {
public:
    void Create(uint32_t arrLen, uint32_t totalCount,
        const std::function<std::pair<uint32_t, uint32_t>(int32_t)>& onGetRid4Index,
        const std::function<void(int32_t, int32_t)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
        const std::function<void(int32_t, int32_t)>& onMoveFromTo, const std::function<void()>& onPurge) override;

    void RemoveNode(uint32_t rid) override;
    void SetInvalid(int32_t repeatElmtId, uint32_t rid) override;

    void RequestContainerReLayout(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount,
        int32_t invalidateContainerLayoutFromChildIndex = INT_MIN) override;
    void NotifyContainerLayoutChange(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount, int32_t index,
        int32_t count, NG::UINode::NotificationType notificationType) override;

    void UpdateL1Rid4Index(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount,
        uint32_t invalidateContainerLayoutFromChildIndex, std::map<int32_t, uint32_t>& l1Rd4Index) override;
    void OnMove(int32_t repeatElmtId, std::function<void(int32_t, int32_t)>&& onMove) override;
    void SetItemDragHandler(int32_t repeatElmtId, std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop) override;
    void SetCreateByTemplate(bool isCreatedByTemplate) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_MODEL_NG_H
