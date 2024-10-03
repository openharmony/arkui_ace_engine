/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_MODEL_H

#include <memory>
#include <mutex>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ListModel {
public:
    static ListModel* GetInstance();
    virtual ~ListModel() = default;

    virtual void Create() = 0;
    virtual void SetSpace(const Dimension& space) = 0;
    virtual void SetInitialIndex(int32_t initialIndex) = 0;
    virtual RefPtr<ScrollControllerBase> CreateScrollController() = 0;
    virtual void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) = 0;
    virtual void SetListDirection(Axis axis) = 0;
    virtual void SetScrollBar(DisplayMode scrollBar) = 0;
    virtual void SetScrollBarColor(const std::string& value) = 0;
    virtual void SetScrollBarWidth(const std::string& value) = 0;
    virtual void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled) = 0;
    virtual void SetEditMode(bool editMode) = 0;
    virtual void SetDivider(const V2::ItemDivider& divider) = 0;
    virtual void SetChainAnimation(bool enableChainAnimation) = 0;
    virtual void SetChainAnimationOptions(const ChainAnimationOptions& options) = 0;
    virtual void SetLanes(int32_t lanes) = 0;
    virtual void SetLaneConstrain(const Dimension& laneMinLength, const Dimension& laneMaxLength) = 0;
    virtual void SetLaneMinLength(const Dimension& laneMinLength) = 0;
    virtual void SetLaneMaxLength(const Dimension& laneMaxLength) = 0;
    virtual void SetLaneGutter(const Dimension& laneGutter) = 0;
    virtual void SetListItemAlign(V2::ListItemAlign listItemAlign) = 0;
    virtual void SetMultiSelectable(bool selectable) = 0;
    virtual void SetCachedCount(int32_t cachedCount, bool show = false) = 0;
    virtual void SetHasWidth(bool hasWidth) = 0;
    virtual void SetHasHeight(bool hasHeight) = 0;
    virtual void SetSticky(V2::StickyStyle stickyStyle) = 0;
    virtual void SetContentStartOffset(float startOffset) = 0;
    virtual void SetContentEndOffset(float endOffset) = 0;
    virtual void SetNestedScroll(const NestedScrollOptions& nestedOpt) = 0;
    virtual void SetScrollEnabled(bool scrollEnabled) = 0;
    virtual void SetFriction(double friction) = 0;
    virtual void SetMaintainVisibleContentPosition(bool enabled) = 0;
    virtual void SetOnScroll(OnScrollEvent&& onScroll) = 0;
    virtual void SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin) = 0;
    virtual void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin) = 0;
    virtual void SetOnScrollStart(OnScrollStartEvent&& onScrollStart) = 0;
    virtual void SetOnScrollStop(OnScrollStopEvent&& onScrollStop) = 0;
    virtual void SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex) = 0;
    virtual void SetOnScrollVisibleContentChange(OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange) = 0;
    virtual void SetOnReachStart(OnReachEvent&& onReachStart) = 0;
    virtual void SetOnReachEnd(OnReachEvent&& onReachEnd) = 0;
    virtual void SetOnItemDelete(OnItemDeleteEvent&& onItemDelete) = 0;
    virtual void SetOnItemMove(OnItemMoveEvent&& onItemMove) = 0;
    virtual void SetOnItemDragStart(OnItemDragStartFunc&& onItemDragStart) = 0;
    virtual void SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter) = 0;
    virtual void SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave) = 0;
    virtual void SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove) = 0;
    virtual void SetOnItemDrop(OnItemDropFunc&& onItemDrop) = 0;
    virtual void SetScrollSnapAlign(V2::ScrollSnapAlign scrollSnapAlign) {};
    virtual RefPtr<NG::ListChildrenMainSize> GetOrCreateListChildrenMainSize()
    {
        return nullptr;
    }

    virtual DisplayMode GetDisplayMode() const = 0;

private:
    static std::unique_ptr<ListModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_MODEL_H
