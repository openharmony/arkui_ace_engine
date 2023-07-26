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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H

#include <stdint.h>
#include "base/memory/ace_type.h"
#include "core/components/hyperlink/hyperlink_resources.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::NG {
constexpr int32_t INVALID_IDX = -1;
class ListEventHub : public EventHub {
    DECLARE_ACE_TYPE(ListEventHub, EventHub)

public:
    ListEventHub() = default;
    ~ListEventHub() override = default;

    void SetOnScroll(OnScrollEvent&& onScroll)
    {
        onScrollEvent_ = std::move(onScroll);
    }

    const OnScrollEvent& GetOnScroll() const
    {
        return onScrollEvent_;
    }

    void SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin)
    {
        onScrollBeginEvent_ = std::move(onScrollBegin);
    }

    const OnScrollBeginEvent& GetOnScrollBegin() const
    {
        return onScrollBeginEvent_;
    }

    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
    {
        onScrollFrameBeginEvent_ = std::move(onScrollFrameBegin);
    }

    const OnScrollFrameBeginEvent& GetOnScrollFrameBegin() const
    {
        return onScrollFrameBeginEvent_;
    }

    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
    {
        onScrollStartEvent_ = std::move(onScrollStart);
    }

    const OnScrollStartEvent& GetOnScrollStart() const
    {
        return onScrollStartEvent_;
    }

    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
    {
        onScrollStopEvent_ = std::move(onScrollStop);
    }

    const OnScrollStopEvent& GetOnScrollStop() const
    {
        return onScrollStopEvent_;
    }

    void SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex)
    {
        onScrollIndexEvent_ = std::move(onScrollIndex);
    }

    const OnScrollIndexEvent& GetOnScrollIndex() const
    {
        return onScrollIndexEvent_;
    }

    void SetOnReachStart(OnReachEvent&& onReachStart)
    {
        onReachStartEvent_ = std::move(onReachStart);
    }

    const OnReachEvent& GetOnReachStart() const
    {
        return onReachStartEvent_;
    }

    void SetOnReachEnd(OnReachEvent&& onReachEnd)
    {
        onReachEndEvent_ = std::move(onReachEnd);
    }

    const OnReachEvent& GetOnReachEnd() const
    {
        return onReachEndEvent_;
    }

    void SetOnItemMove(OnItemMoveEvent&& onItemMove)
    {
        onItemMoveEvent_ = std::move(onItemMove);
    }

    const OnItemMoveEvent& GetOnItemMove() const
    {
        return onItemMoveEvent_;
    }

    void SetOnItemDragStart(OnItemDragStartFunc&& onItemDragStart)
    {
        onItemDragStartEvent_ = std::move(onItemDragStart);
    }

    const OnItemDragStartFunc& GetOnItemDragStart() const
    {
        return onItemDragStartEvent_;
    }

    void SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter)
    {
        onItemDragEnterEvent_ = std::move(onItemDragEnter);
    }

    const OnItemDragEnterFunc& GetOnItemDragEnter() const
    {
        return onItemDragEnterEvent_;
    }

    void SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave)
    {
        onItemDragLeaveEvent_ = std::move(onItemDragLeave);
    }

    const OnItemDragLeaveFunc& GetOnItemDragLeave() const
    {
        return onItemDragLeaveEvent_;
    }

    void SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove)
    {
        onItemDragMoveEvent_ = std::move(onItemDragMove);
    }

    const OnItemDragMoveFunc& GetOnItemDragMove() const
    {
        return onItemDragMoveEvent_;
    }

    void SetOnItemDrop(OnItemDropFunc&& onItemDrop)
    {
        onItemDropEvent_ = std::move(onItemDrop);
    }

    const OnItemDropFunc& GetOnItemDrop() const
    {
        return onItemDropEvent_;
    }

    RefPtr<UINode> FireOnItemDragStart(const ItemDragInfo& dragInfo, int32_t itemIndex) const
    {
        if (onItemDragStartEvent_) {
            return AceType::DynamicCast<UINode>(onItemDragStartEvent_(dragInfo, itemIndex));
        }
        return nullptr;
    }

    void FireOnItemDragEnter(const ItemDragInfo& dragInfo) const
    {
        if (onItemDragEnterEvent_) {
            onItemDragEnterEvent_(dragInfo);
        }
    }

    void FireOnItemDragMove(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) const
    {
        if (onItemDragMoveEvent_) {
            onItemDragMoveEvent_(dragInfo, itemIndex, insertIndex);
        }
    }

    void FireOnItemDragLeave(const ItemDragInfo& dragInfo, int32_t itemIndex) const
    {
        if (onItemDragLeaveEvent_) {
            onItemDragLeaveEvent_(dragInfo, itemIndex);
        }
    }

    bool FireOnItemDrop(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) const
    {
        if (onItemDropEvent_) {
            if (onItemMoveEvent_ && itemIndex >= 0 && insertIndex >= 0) {
                isSuccess = onItemMoveEvent_(itemIndex, insertIndex);
            }
            onItemDropEvent_(dragInfo, itemIndex, insertIndex, isSuccess);
            return true;
        }
        return false;
    }

    std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType drag) override
    {
        auto json = JsonUtil::Create(true);
        if (drag == DragEventType::DROP || drag == DragEventType::MOVE) {
            int32_t index = GetListItemIndexByPosition(point.GetX(), point.GetY());
            json->Put("insertIndex", index);
        }
        if (!extraInfo.empty()) {
            json->Put("extraInfo", extraInfo.c_str());
        }
        return json->ToString();
    }

    bool HasOnItemDragMove() override
    {
        return static_cast<bool>(onItemDragMoveEvent_);
    }

    bool HasOnItemDrop() override
    {
        return static_cast<bool>(onItemDropEvent_);
    }

    void InitItemDragEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleOnItemDragStart(const GestureEvent& info);
    void HandleOnItemDragUpdate(const GestureEvent& info);
    void HandleOnItemDragEnd(const GestureEvent& info);
    void HandleOnItemDragCancel();
    int32_t GetListItemIndexByPosition(float x, float y, bool strict = false);
private:
    Axis GetDirection() const;

    OnScrollEvent onScrollEvent_;
    OnScrollBeginEvent onScrollBeginEvent_;
    OnScrollFrameBeginEvent onScrollFrameBeginEvent_;
    OnScrollStartEvent onScrollStartEvent_;
    OnScrollStopEvent onScrollStopEvent_;
    OnScrollIndexEvent onScrollIndexEvent_;
    OnReachEvent onReachStartEvent_;
    OnReachEvent onReachEndEvent_;
    OnItemMoveEvent onItemMoveEvent_;
    OnItemDragStartFunc onItemDragStartEvent_;
    OnItemDragEnterFunc onItemDragEnterEvent_;
    OnItemDragLeaveFunc onItemDragLeaveEvent_;
    OnItemDragMoveFunc onItemDragMoveEvent_;
    OnItemDropFunc onItemDropEvent_;

    RefPtr<DragDropProxy> dragDropProxy_;
    int32_t draggedIndex_ = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H