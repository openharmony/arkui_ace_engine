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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_STATIC_H

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_v2/list/list_properties.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ListModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, bool isCreateArc = false);
    static void SetListItemAlign(FrameNode* frameNode, const std::optional<V2::ListItemAlign>& listItemAlign);
    static void SetListDirection(FrameNode* frameNode, const std::optional<int32_t>& axis);
    static void SetListScrollBar(FrameNode* frameNode, const std::optional<int32_t>& barState);
    static void SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider);
    static void SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle);
    static void SetScrollSnapAlign(FrameNode* frameNode, const std::optional<ScrollSnapAlign>& scrollSnapAlign);
    static void SetListFriction(FrameNode* frameNode, const std::optional<double>& friction);
    static RefPtr<ScrollProxy> GetOrCreateScrollBarProxy(FrameNode* frameNode);
    static void SetInitialIndex(FrameNode* frameNode, const std::optional<int32_t>& initialIndex);
    static void SetListNestedScroll(FrameNode* frameNode, const std::optional<NestedScrollMode>& forward,
        const std::optional<NestedScrollMode>& backward);
    static void SetLaneGutter(FrameNode* frameNode, const std::optional<Dimension>& laneGutter);
    static void SetListSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
    static RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize(
        FrameNode* frameNode, const std::optional<float>& defaultSize);
    static RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize(FrameNode* frameNode);
    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static void SetContentStartOffset(FrameNode* frameNode, float startOffset);
    static void SetContentEndOffset(FrameNode* frameNode, float endOffset);
    static void SetCachedCount(FrameNode* frameNode, int32_t cachedCount);
    static void SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetOnScrollIndex(FrameNode* frameNode, OnScrollIndexEvent&& onScrollIndex);
    static void SetOnScrollVisibleContentChange(FrameNode* frameNode,
        OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange);
    static void SetOnItemMove(FrameNode* frameNode, OnItemMoveEvent&& onItemMove);
    static void SetOnItemDragStart(FrameNode* frameNode, OnItemDragStartFunc&& onItemDragStart);
    static void SetOnItemDragEnter(FrameNode* frameNode, OnItemDragEnterFunc&& onItemDragEnter);
    static void SetOnItemDragLeave(FrameNode* frameNode, OnItemDragLeaveFunc&& onItemDragLeave);
    static void SetOnItemDragMove(FrameNode* frameNode, OnItemDragMoveFunc&& onItemDragMove);
    static void SetOnItemDrop(FrameNode* frameNode, OnItemDropFunc&& onItemDrop);
    static void SetOnItemDelete(FrameNode* frameNode, OnItemDeleteEvent&& onItemDelete);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetChainAnimation(FrameNode* frameNode, bool chainAnimation);
    static void SetChainAnimationOptions(FrameNode* frameNode, const ChainAnimationOptions& options);
    static void SetScrollEnabled(FrameNode* frameNode, bool enableScrollInteraction);
    static void SetListMaintainVisibleContentPosition(FrameNode* frameNode, bool enabled);
    static void SetLanes(FrameNode* frameNode, int32_t lanes);
    static void SetLaneGutter(FrameNode* frameNode, const Dimension& laneGutter);
    static void SetLaneConstrain(FrameNode* frameNode, const Dimension& laneMinLength, const Dimension& laneMaxLength);
    static void SetLaneMinLength(FrameNode* frameNode, const Dimension& laneMinLength);
    static void SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength);
    static void SetEditMode(FrameNode* frameNode, bool editMode);
    static void SetMultiSelectable(FrameNode* frameNode, bool selectable);
private:
    static void AddDragFrameNodeToManager(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_STATIC_H
