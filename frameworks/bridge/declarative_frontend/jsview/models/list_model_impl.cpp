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

#include "bridge/declarative_frontend/jsview/models/list_model_impl.h"

#include <memory>

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

void ListModelImpl::Create()
{
    auto listComponent = AceType::MakeRefPtr<V2::ListComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(listComponent);
    ViewStackProcessor::GetInstance()->Push(listComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
}

void ListModelImpl::SetSpace(const Dimension& space)
{
    JSViewSetProperty(&V2::ListComponent::SetSpace, space);
}

void ListModelImpl::SetInitialIndex(int32_t initialIndex)
{
    JSViewSetProperty(&V2::ListComponent::SetInitialIndex, initialIndex);
}

RefPtr<ScrollControllerBase> ListModelImpl::CreateScrollController()
{
    return AceType::MakeRefPtr<V2::ListPositionController>();
}

void ListModelImpl::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    auto listScroller = AceType::DynamicCast<V2::ListPositionController>(scroller);
    JSViewSetProperty(&V2::ListComponent::SetScrollController, listScroller);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
    JSViewSetProperty(&V2::ListComponent::SetScrollBarProxy, scrollBarProxy);
}

void ListModelImpl::SetListDirection(Axis axis)
{
    JSViewSetProperty(&V2::ListComponent::SetDirection, axis);
}

void ListModelImpl::SetScrollBar(DisplayMode scrollBar)
{
    JSViewSetProperty(&V2::ListComponent::SetScrollBar, scrollBar);
}

void ListModelImpl::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
{
    JSViewSetProperty(&V2::ListComponent::SetEdgeEffect, edgeEffect);
}

void ListModelImpl::SetEditMode(bool editMode)
{
    JSViewSetProperty(&V2::ListComponent::SetEditMode, editMode);
}

void ListModelImpl::SetListItemAlign(V2::ListItemAlign listItemAlign)
{
    JSViewSetProperty(&V2::ListComponent::SetListItemAlign, listItemAlign);
}

void ListModelImpl::SetDivider(const V2::ItemDivider& divider)
{
    auto dividerPtr = std::make_unique<V2::ItemDivider>(divider);
    JSViewSetProperty(&V2::ListComponent::SetItemDivider, std::move(dividerPtr));
}

void ListModelImpl::SetChainAnimation(bool enableChainAnimation)
{
    JSViewSetProperty(&V2::ListComponent::SetChainAnimation, enableChainAnimation);
}

void ListModelImpl::SetLanes(int32_t lanes)
{
    JSViewSetProperty(&V2::ListComponent::SetLanes, lanes);
}

void ListModelImpl::SetLaneConstrain(const Dimension& laneMinLength, const Dimension& laneMaxLength)
{
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get ListComponent in view stack");
        return;
    }
    component->SetLaneConstrain(laneMinLength, laneMaxLength);
}

void ListModelImpl::SetCachedCount(int32_t cachedCount, bool show)
{
    JSViewSetProperty(&V2::ListComponent::SetCachedCount, cachedCount);
}

void ListModelImpl::SetMultiSelectable(bool selectable)
{
    JSViewSetProperty(&V2::ListComponent::SetMultiSelectable, selectable);
}

void ListModelImpl::SetHasWidth(bool hasWidth)
{
    JSViewSetProperty(&V2::ListComponent::SetHasWidth, hasWidth);
}

void ListModelImpl::SetHasHeight(bool hasHeight)
{
    JSViewSetProperty(&V2::ListComponent::SetHasHeight, hasHeight);
}

void ListModelImpl::SetSticky(V2::StickyStyle stickyStyle)
{
    JSViewSetProperty(&V2::ListComponent::SetSticky, stickyStyle);
}

void ListModelImpl::SetContentStartOffset(float startOffset)
{
    JSViewSetProperty(&V2::ListComponent::SetContentStartOffset, startOffset);
}

void ListModelImpl::SetContentEndOffset(float endOffset)
{
    JSViewSetProperty(&V2::ListComponent::SetContentEndOffset, endOffset);
}

void ListModelImpl::SetOnScroll(OnScrollEvent&& onScroll)
{
    JSViewSetProperty(&V2::ListComponent::SetOnScroll, std::move(onScroll));
}

void ListModelImpl::SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin)
{
    JSViewSetProperty(&V2::ListComponent::SetOnScrollBegin, std::move(onScrollBegin));
}

void ListModelImpl::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
}

void ListModelImpl::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    JSViewSetProperty(&V2::ListComponent::SetOnScrollStop, std::move(onScrollStop));
}

void ListModelImpl::SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex)
{
    JSViewSetProperty(&V2::ListComponent::SetOnScrollIndex, std::move(onScrollIndex));
}

void ListModelImpl::SetOnReachStart(OnReachEvent&& onReachStart)
{
    JSViewSetProperty(&V2::ListComponent::SetOnReachStart, std::move(onReachStart));
}

void ListModelImpl::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    JSViewSetProperty(&V2::ListComponent::SetOnReachEnd, std::move(onReachEnd));
}

void ListModelImpl::SetOnItemDelete(OnItemDeleteEvent&& onItemDelete)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDelete, std::move(onItemDelete));
}

void ListModelImpl::SetOnItemMove(OnItemMoveEvent&& onItemMove)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemMove, std::move(onItemMove));
}

void ListModelImpl::SetOnItemDragStart(OnItemDragStartFunc&& onItemDragStart)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDragStartId, std::move(onItemDragStart));
}

void ListModelImpl::SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDragEnterId, std::move(onItemDragEnter));
}

void ListModelImpl::SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDragMoveId, std::move(onItemDragMove));
}

void ListModelImpl::SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDragLeaveId, std::move(onItemDragLeave));
}

void ListModelImpl::SetOnItemDrop(OnItemDropFunc&& onItemDrop)
{
    JSViewSetProperty(&V2::ListComponent::SetOnItemDropId, std::move(onItemDrop));
}

} // namespace OHOS::Ace::Framework
