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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ScrollToIndexFunc = std::function<void(int32_t)>;
using ItemDragStartFunc = std::function<RefPtr<UINode>(const ItemDragInfo&, int32_t)>;
using ItemDragEnterFunc = std::function<void(const ItemDragInfo&)>;
using ItemDragMoveFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t)>;
using ItemDragLeaveFunc = std::function<void(const ItemDragInfo&, int32_t)>;
using ItemDropFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>;

class GridEventHub : public EventHub {
    DECLARE_ACE_TYPE(GridEventHub, EventHub)

public:
    GridEventHub() = default;
    ~GridEventHub() override = default;

    void SetOnScrollToIndex(ScrollToIndexFunc&& onScrollToIndex)
    {
        onScrollToIndex_ = std::move(onScrollToIndex);
    }

    void SetOnItemDragStart(ItemDragStartFunc&& onItemDragStart)
    {
        onItemDragStart_ = std::move(onItemDragStart);
    }

    void SetOnItemDragEnter(ItemDragEnterFunc&& onItemDragEnter)
    {
        onItemDragEnter_ = std::move(onItemDragEnter);
    }

    void SetOnItemDragMove(ItemDragMoveFunc&& onItemDragMove)
    {
        onItemDragMove_ = std::move(onItemDragMove);
    }

    void SetOnItemDragLeave(ItemDragLeaveFunc&& onItemDragLeave)
    {
        onItemDragLeave_ = std::move(onItemDragLeave);
    }

    void SetOnItemDrop(ItemDropFunc&& onItemDrop)
    {
        onItemDrop_ = std::move(onItemDrop);
    }

    void FireOnScrollToIndex(int32_t param) const
    {
        if (onScrollToIndex_) {
            onScrollToIndex_(param);
        }
    }

    RefPtr<UINode> FireOnItemDragStart(const ItemDragInfo& dragInfo, int32_t itemIndex) const;

    void FireOnItemDragEnter(const ItemDragInfo& dragInfo) const
    {
        if (onItemDragEnter_) {
            onItemDragEnter_(dragInfo);
        }
    }

    void FireOnItemDragMove(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) const
    {
        if (onItemDragMove_) {
            onItemDragMove_(dragInfo, itemIndex, insertIndex);
        }
    }

    void FireOnItemDragLeave(const ItemDragInfo& dragInfo, int32_t itemIndex) const
    {
        if (onItemDragLeave_) {
            onItemDragLeave_(dragInfo, itemIndex);
        }
    }

    void FireOnItemDrop(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) const
    {
        if (onItemDrop_) {
            onItemDrop_(dragInfo, itemIndex, insertIndex, isSuccess);
        }
    }

private:
    ScrollToIndexFunc onScrollToIndex_;
    ItemDragStartFunc onItemDragStart_;
    ItemDragEnterFunc onItemDragEnter_;
    ItemDragMoveFunc onItemDragMove_;
    ItemDragLeaveFunc onItemDragLeave_;
    ItemDropFunc onItemDrop_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H