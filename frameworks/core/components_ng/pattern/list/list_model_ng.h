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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_NG_H
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT ListModelNG : public ListModel {
public:
    void Create(bool isCreateArc = false) override;
    void SetSpace(const Dimension& space) override;
    void SetInitialIndex(int32_t initialIndex) override;
    RefPtr<ScrollControllerBase> CreateScrollController() override;
    void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) override;
    void SetListDirection(Axis axis) override;
    void SetScrollBar(DisplayMode scrollBar) override;
    void SetScrollBarColor(const std::string& value) override;
    void SetScrollBarWidth(const std::string& value) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge = EffectEdge::ALL) override;
    void SetEditMode(bool editMode) override;
    void SetDivider(const V2::ItemDivider& divider) override;
    void SetChainAnimation(bool enableChainAnimation) override;
    void SetChainAnimationOptions(const ChainAnimationOptions& options) override;
    void SetLanes(int32_t lanes) override;
    void SetLaneConstrain(const Dimension& laneMinLength, const Dimension& laneMaxLength) override;
    void SetLaneMinLength(const Dimension& laneMinLength) override;
    void SetLaneMaxLength(const Dimension& laneMaxLength) override;
    void SetLaneGutter(const Dimension& laneGutter) override;
    void SetListItemAlign(V2::ListItemAlign listItemAlign) override;
    void SetCachedCount(int32_t cachedCount, bool show = false) override;
    void SetMultiSelectable(bool selectable) override;
    void SetHasWidth(bool hasWidth) override {}
    void SetHasHeight(bool hasHeight) override {}
    void SetSticky(V2::StickyStyle stickyStyle) override;
    void SetContentStartOffset(float startOffset) override;
    void SetContentEndOffset(float endOffset) override;
    void SetScrollSnapAlign(ScrollSnapAlign scrollSnapAlign) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;
    void SetFriction(double friction) override;
    void SetFocusWrapMode(FocusWrapMode focusWrapMode) override;
    void SetMaintainVisibleContentPosition(bool enabled) override;
    void SetStackFromEnd(bool enabled) override;
    void SetSyncLoad(bool enabled) override;
    void SetOnScroll(OnScrollEvent&& onScroll) override;
    void SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin) override;
    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin) override;
    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart) override;
    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop) override;
    void SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex) override;
    void SetOnScrollVisibleContentChange(OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange) override;
    void SetOnReachStart(OnReachEvent&& onReachStart) override;
    void SetOnReachEnd(OnReachEvent&& onReachEnd) override;
    void SetOnItemDelete(OnItemDeleteEvent&& onItemDelete) override {}
    void SetOnItemMove(OnItemMoveEvent&& onItemMove) override;
    void SetOnItemDragStart(OnItemDragStartFunc&& onItemDragStart) override;
    void SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter) override;
    void SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave) override;
    void SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove) override;
    void SetOnItemDrop(OnItemDropFunc&& onItemDrop) override;
    RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize() override;

    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static RefPtr<ScrollProxy> GetOrCreateScrollBarProxy(FrameNode* frameNode);
    static void ScrollToEdge(FrameNode* frameNode, ScrollEdgeType scrollEdgeType, bool smooth);
    static void SetInitialIndex(FrameNode* frameNode, const std::optional<int32_t>& initialIndex);
    static void SetEditMode(FrameNode* frameNode, bool editMode);
    static void SetMultiSelectable(FrameNode* frameNode, bool selectable);
    static void SetChainAnimation(FrameNode* frameNode, bool chainAnimation);
    static void SetCachedCount(FrameNode* frameNode, int32_t cachedCount);
    static void SetShowCached(FrameNode* frameNode, bool show);
    static int32_t GetCachedCount(FrameNode* frameNode);
    static bool GetShowCached(FrameNode* frameNode);
    static int32_t GetScrollEnabled(FrameNode* frameNode);
    static void SetScrollEnabled(FrameNode* frameNode, bool enableScrollInteraction);
    static int32_t GetSticky(FrameNode* frameNode);
    static void SetSticky(FrameNode* frameNode, int32_t stickyStyle);
    static void SetEdgeEffect(FrameNode* frameNode, int32_t edgeEffect, bool alwaysEnabled, EffectEdge edge);
    static int32_t GetListDirection(FrameNode* frameNode);
    static void SetListDirection(FrameNode* frameNode, const std::optional<int32_t>& axis);
    static float GetListFriction(FrameNode* frameNode);
    static void SetListFriction(FrameNode* frameNode, double friction);
    static void SetListMaintainVisibleContentPosition(FrameNode* frameNode, bool enabled);
    static bool GetListMaintainVisibleContentPosition(FrameNode* frameNode);
    static void SetListNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static int32_t GetListScrollBar(FrameNode* frameNode);
    static void SetListScrollBar(FrameNode* frameNode, const std::optional<int32_t>& barState);
    static float GetScrollBarWidth(FrameNode* frameNode);
    static void SetListScrollBarWidth(FrameNode* frameNode, const std::string& value);
    static uint32_t GetScrollBarColor(FrameNode* frameNode);
    static void SetListScrollBarColor(FrameNode* frameNode, const std::string& value);
    static void SetLanes(FrameNode* frameNode, int32_t lanes);
    static int32_t GetLanes(FrameNode* frameNode);
    static void SetLaneConstrain(FrameNode* frameNode, const Dimension& laneMinLength, const Dimension& laneMaxLength);
    static void SetLaneMinLength(FrameNode* frameNode, const Dimension& laneMinLength);
    static float GetLaneMinLength(FrameNode* frameNode);
    static void SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength);
    static FocusWrapMode GetFocusWrapMode(FrameNode* frameNode);
    static void SetFocusWrapMode(FrameNode* frameNode, FocusWrapMode focusWrapMode);
    static float GetLaneMaxLength(FrameNode* frameNode);
    static void SetLaneGutter(FrameNode* frameNode, const Dimension& laneGutter);
    static float GetLaneGutter(FrameNode* frameNode);
    static int32_t GetListItemAlign(FrameNode* frameNode);
    static void SetListItemAlign(FrameNode* frameNode, const std::optional<V2::ListItemAlign>& listItemAlign);
    static float GetListSpace(FrameNode* frameNode);
    static void SetListSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
    static int32_t GetEdgeEffectAlways(FrameNode* frameNode);
    static void SetScrollSnapAlign(FrameNode* frameNode, const std::optional<ScrollSnapAlign>& scrollSnapAlign);
    static int32_t GetScrollSnapAlign(FrameNode* frameNode);
    static void SetContentStartOffset(FrameNode* frameNode, float startOffset);
    static float GetContentStartOffset(FrameNode* frameNode);
    static void SetContentEndOffset(FrameNode* frameNode, float endOffset);
    static float GetContentEndOffset(FrameNode* frameNode);
    static void SetDivider(FrameNode* frameNode, const V2::ItemDivider& divider);
    static void SetChainAnimationOptions(FrameNode* frameNode, const ChainAnimationOptions& options);
    static int32_t GetEdgeEffect(FrameNode* frameNode);
    static void SetListStackFromEnd(FrameNode* frameNode, bool enabled);
    static bool GetListStackFromEnd(FrameNode* frameNode);
    static void SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetOnScrollIndex(FrameNode* frameNode, OnScrollIndexEvent&& onScrollIndex);
    static NestedScrollOptions GetListNestedScroll(FrameNode* frameNode);
    DisplayMode GetDisplayMode() const override;
    void SetHeader(const RefPtr<FrameNode>& headerNode) override;
    void ResetListChildrenMainSize() override;
#ifdef SUPPORT_DIGITAL_CROWN
    void SetDigitalCrownSensitivity(CrownSensitivity sensitivity) override;
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity);
    static CrownSensitivity GetDigitalCrownSensitivity(FrameNode* frameNode);
#endif
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, bool isCreateArc = false);
    static void SetScrollToIndex(FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment,
        std::optional<float> extraOffset = std::nullopt);
    static void SetScrollBy(FrameNode* frameNode, double x, double y);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetListChildrenMainSize(
        FrameNode* frameNode, float defaultSize, const std::vector<float>& mainSize);
    static void ResetListChildrenMainSize(FrameNode* frameNode);
    static int32_t GetInitialIndex(FrameNode* frameNode);
    static V2::ItemDivider GetDivider(FrameNode* frameNode);
    static void SetScroller(FrameNode* frameNode, RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy);
    static void SetOnScrollVisibleContentChange(FrameNode* frameNode, OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange);
    static void SetOnItemMove(FrameNode* frameNode, OnItemMoveEvent&& onItemMove);
    static void SetOnItemDragStart(FrameNode* frameNode, OnItemDragStartFunc&& onItemDragStart);
    static void SetOnItemDragEnter(FrameNode* frameNode, OnItemDragEnterFunc&& onItemDragEnter);
    static void SetOnItemDragLeave(FrameNode* frameNode, OnItemDragLeaveFunc&& onItemDragLeave);
    static void SetOnItemDragMove(FrameNode* frameNode, OnItemDragMoveFunc&& onItemDragMove);
    static void SetOnItemDrop(FrameNode* frameNode, OnItemDropFunc&& onItemDrop);
    static void ScrollToItemInGroup(
        FrameNode* frameNode, int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align);
    static void SetHeader(FrameNode* frameNode, FrameNode* headerNode);
private:
    void AddDragFrameNodeToManager() const;
    static void AddDragFrameNodeToManager(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_MODEL_NG_H
