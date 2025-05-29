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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_MODEL_H

#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace {

enum class CreateFrameChildResult;

class ACE_EXPORT RepeatVirtualScroll2Model {
public:
    RepeatVirtualScroll2Model() = default;
    virtual ~RepeatVirtualScroll2Model() = default;

    static RepeatVirtualScroll2Model* GetInstance();
    virtual void Create(uint32_t arrLen, uint32_t totalCount,
        const std::function<std::pair<uint32_t, uint32_t>(int32_t)>& onGetRid4Index,
        const std::function<void(int32_t, int32_t)>& onRecycleItems,
        const std::function<void(int32_t, int32_t, int32_t, int32_t, bool, bool)>& onActiveRange,
        const std::function<void(int32_t, int32_t)>& onMoveFromTo, const std::function<void()>& onPurge) = 0;

    virtual bool IsInAnimation() = 0;
    virtual void RemoveNode(uint32_t rid) = 0;
    virtual void SetInvalid(int32_t repeatElmtId, uint32_t rid) = 0;

    virtual void RequestContainerReLayout(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount,
        int32_t invalidateContainerLayoutFromChildIndex = INT_MIN) = 0;
    virtual void NotifyContainerLayoutChange(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount, int32_t index,
        int32_t count, NG::UINode::NotificationType notificationType) = 0;

    virtual void UpdateL1Rid4Index(int32_t repeatElmtId, uint32_t arrLen, uint32_t totalCount,
        uint32_t invalidateContainerLayoutFromChildIndex, std::map<int32_t, uint32_t>& l1Rd4Index) = 0;
    virtual void OnMove(int32_t repeatElmtId, std::function<void(int32_t, int32_t)>&& onMove) = 0;
    virtual void SetItemDragHandler(int32_t repeatElmtId, std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop) = 0;
    virtual void SetCreateByTemplate(bool isCreatedByTemplate) = 0;

private:
    static std::unique_ptr<RepeatVirtualScroll2Model> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_H
