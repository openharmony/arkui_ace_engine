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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H

#include <functional>

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_v2/grid/grid_event.h"

namespace OHOS::Ace::NG {

using ScrollToIndexFunc = std::function<void(const BaseEventInfo*)>;
using ScrollBarUpdateFunc = std::function<std::pair<std::optional<float>, std::optional<float>>(int32_t, Dimension)>;
using ItemDragStartFunc = std::function<RefPtr<UINode>(const ItemDragInfo&, int32_t)>;
using ItemDragEnterFunc = std::function<void(const ItemDragInfo&)>;
using ItemDragMoveFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t)>;
using ItemDragLeaveFunc = std::function<void(const ItemDragInfo&, int32_t)>;
using ItemDropFunc = std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)>;
using ScrollIndexFunc = std::function<void(int32_t, int32_t)>;

class GridEventHub : public ScrollableEventHub {
    DECLARE_ACE_TYPE(GridEventHub, ScrollableEventHub);

public:
    GridEventHub() = default;
    ~GridEventHub() override = default;

    void FireOnDisappear() override
    {
        EventHub::FireOnDisappear();
        HandleOnItemDragCancel();
    }

    void SetOnScrollToIndex(ScrollToIndexFunc&& onScrollToIndex)
    {
        onScrollToIndex_ = std::move(onScrollToIndex);
    }

    void SetOnScrollBarUpdate(ScrollBarUpdateFunc&& onScrollBarUpdate)
    {
        onScrollBarUpdate_ = std::move(onScrollBarUpdate);
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
            V2::GridEventInfo info(param);
            onScrollToIndex_(&info);
        }
    }

    void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
    {
        onScrollIndexEvent_ = std::move(onScrollIndex);
    }

    const ScrollIndexFunc& GetOnScrollIndex() const
    {
        return onScrollIndexEvent_;
    }

    void SetJSFrameNodeOnGridScrollIndex(ScrollIndexFunc&& onScroll)
    {
        onJSFrameNodeScrollIndexEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnGridScrollIndex()
    {
        if (onJSFrameNodeScrollIndexEvent_) {
            onJSFrameNodeScrollIndexEvent_ = nullptr;
        }
    }

    const ScrollIndexFunc& GetJSFrameNodeOnGridScrollIndex() const
    {
        return onJSFrameNodeScrollIndexEvent_;
    }

    std::pair<std::optional<float>, std::optional<float>> FireOnScrollBarUpdate(int32_t index, const Dimension& offset)
    {
        if (onScrollBarUpdate_) {
            return onScrollBarUpdate_(index, offset);
        }
        return std::pair<std::optional<float>, std::optional<float>>();
    }

    RefPtr<UINode> FireOnItemDragStart(const ItemDragInfo& dragInfo, int32_t itemIndex) const
    {
        if (onItemDragStart_) {
            return onItemDragStart_(dragInfo, itemIndex);
        }
        return nullptr;
    }

    void FireOnItemDragEnter(const ItemDragInfo& dragInfo);

    void FireOnItemDragMove(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) const;

    void FireOnItemDragLeave(const ItemDragInfo& dragInfo, int32_t itemIndex);

    bool FireOnItemDrop(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess);

    bool HasOnItemDragMove() override
    {
        return static_cast<bool>(onItemDragMove_);
    }

    bool HasOnItemDrop() override
    {
        return static_cast<bool>(onItemDrop_);
    }

    void InitItemDragEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleOnItemDragStart(const GestureEvent& info);
    void HandleOnItemDragUpdate(const GestureEvent& info);
    void HandleOnItemDragEnd(const GestureEvent& info);
    void HandleOnItemDragCancel();
    int32_t GetGridItemIndex(const RefPtr<FrameNode>& frameNode);
    bool CheckPostionInGrid(float x, float y);
    int32_t GetInsertPosition(float x, float y);
    int GetFrameNodeChildSize();

private:
    bool GetEditable() const;
    void MoveItems(int32_t itemIndex, int32_t insertIndex) const;

    ScrollToIndexFunc onScrollToIndex_;
    ScrollBarUpdateFunc onScrollBarUpdate_;
    ItemDragStartFunc onItemDragStart_;
    ItemDragEnterFunc onItemDragEnter_;
    ItemDragMoveFunc onItemDragMove_;
    ItemDragLeaveFunc onItemDragLeave_;
    ItemDropFunc onItemDrop_;
    RefPtr<DragDropProxy> dragDropProxy_;
    int32_t draggedIndex_ = 0;
    RefPtr<FrameNode> draggingItem_;

    ScrollIndexFunc onScrollIndexEvent_;
    ScrollIndexFunc onJSFrameNodeScrollIndexEvent_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_EVENT_HUB_H