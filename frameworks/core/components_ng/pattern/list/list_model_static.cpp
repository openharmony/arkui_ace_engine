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

#include "core/components_ng/pattern/list/list_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

RefPtr<FrameNode> ListModelStatic::CreateFrameNode(int32_t nodeId, bool isCreateArc)
{
    RefPtr<FrameNode> frameNode = nullptr;
    if (!isCreateArc) {
        frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, nodeId, AceType::MakeRefPtr<ListPattern>());
    } else {
        frameNode = FrameNode::CreateFrameNode(V2::ARC_LIST_ETS_TAG, nodeId, AceType::MakeRefPtr<ArcListPattern>());
    }
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    return frameNode;
}

void ListModelStatic::SetListItemAlign(FrameNode* frameNode, const std::optional<V2::ListItemAlign>& listItemAlign)
{
    if (listItemAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, frameNode);
    }
}

void ListModelStatic::SetListDirection(FrameNode* frameNode, const std::optional<int32_t>& axis)
{
    if (axis.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, static_cast<Axis>(axis.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, frameNode);
    }
}

void ListModelStatic::SetListScrollBar(FrameNode* frameNode, const std::optional<int32_t>& barState)
{
    CHECK_NULL_VOID(frameNode);
    int32_t displayNumber;

    if (!barState.has_value() ||
        (barState.value() < 0 || barState.value() >= static_cast<int32_t>(DISPLAY_MODE.size()))) {
        displayNumber = static_cast<int32_t>(DisplayMode::AUTO);
    } else {
        displayNumber = barState.value();
    }

    ScrollableModelNG::SetScrollBarMode(frameNode, displayNumber);
}

void ListModelStatic::SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider)
{
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, frameNode);
    }
}

void ListModelStatic::SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle)
{
    if (stickyStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle,
            static_cast<V2::StickyStyle>(stickyStyle.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle, frameNode);
    }
}

void ListModelStatic::SetScrollSnapAlign(FrameNode* frameNode, const std::optional<ScrollSnapAlign>& scrollSnapAlign)
{
    if (scrollSnapAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, frameNode);
    }
}

void ListModelStatic::SetListFriction(FrameNode* frameNode, const std::optional<double>& friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    auto frictionValue = friction.value_or(FRICTION);
    if (LessOrEqual(frictionValue, 0.0)) {
        frictionValue = FRICTION;
    }
    pattern->SetFriction(frictionValue);
}

RefPtr<ScrollProxy> ListModelStatic::GetOrCreateScrollBarProxy(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto scrollBarProxy = pattern->GetScrollBarProxy();
    if (scrollBarProxy == nullptr) {
        scrollBarProxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
        pattern->SetScrollBarProxy(scrollBarProxy);
    }
    return scrollBarProxy;
}

void ListModelStatic::SetInitialIndex(FrameNode* frameNode, const std::optional<int32_t>& initialIndex)
{
    if (initialIndex.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, initialIndex.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, frameNode);
    }
}

void ListModelStatic::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    if (cachedCount >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, cachedCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, frameNode);
    }
}

void ListModelStatic::SetListNestedScroll(FrameNode* frameNode, const std::optional<NestedScrollMode>& forward,
    const std::optional<NestedScrollMode>& backward)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);

    NestedScrollOptions options = {.forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY};
    if (forward.has_value()) {
        options.forward = forward.value();
    }

    if (backward.has_value()) {
        options.backward = backward.value();
    }

    pattern->SetNestedScroll(options);
}

void ListModelStatic::SetLaneGutter(FrameNode* frameNode, const std::optional<Dimension>& laneGutter)
{
    if (laneGutter.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, frameNode);
    }
}

void ListModelStatic::SetListSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Space, space.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Space, frameNode);
    }
}

void ListModelStatic::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

RefPtr<ListChildrenMainSize> ListModelStatic::GetOrCreateListChildrenMainSize(
    FrameNode* frameNode, const std::optional<float>& defaultSize)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto childrenMainSize = pattern->GetOrCreateListChildrenMainSize();
    if (defaultSize.has_value()) {
        childrenMainSize->UpdateDefaultSize(defaultSize.value());
    }
    return childrenMainSize;
}

RefPtr<ListChildrenMainSize> ListModelStatic::GetOrCreateListChildrenMainSize(
    FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

void ListModelStatic::SetOnItemDelete(FrameNode* frameNode, OnItemDeleteEvent&& onItemDelete)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    LOGE("ListModelStatic::SetOnItemDelete, the ListEventHub does not support 'OnItemDelete' yet");
    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

RefPtr<ScrollControllerBase> ListModelStatic::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetPositionController()) {
        auto controller = AceType::MakeRefPtr<NG::ListPositionController>();
        pattern->SetPositionController(controller);
        controller->SetScrollPattern(pattern);
        pattern->TriggerModifyDone();
    }
    return pattern->GetPositionController();
}

void ListModelStatic::SetContentStartOffset(FrameNode* frameNode, float startOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentStartOffset, startOffset, frameNode);
}

void ListModelStatic::SetContentEndOffset(FrameNode* frameNode, float endOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentEndOffset, endOffset, frameNode);
}

void ListModelStatic::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddListDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ListModelStatic::SetOnScrollIndex(FrameNode* frameNode, OnScrollIndexEvent&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void ListModelStatic::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ListModelStatic::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void ListModelStatic::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ListModelStatic::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ListModelStatic::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void ListModelStatic::SetChainAnimation(FrameNode* frameNode, bool chainAnimation)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ChainAnimation, chainAnimation, frameNode);
}

void ListModelStatic::SetChainAnimationOptions(FrameNode* frameNode, const ChainAnimationOptions& options)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetChainAnimationOptions(options);
}

void ListModelStatic::SetScrollEnabled(FrameNode* frameNode, bool enableScrollInteraction)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollEnabled, enableScrollInteraction, frameNode);
}

void ListModelStatic::SetListMaintainVisibleContentPosition(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaintainVisibleContentPosition(enabled);
}

void ListModelStatic::SetOnScrollVisibleContentChange(
    FrameNode* frameNode, OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollVisibleContentChange(std::move(onScrollVisibleContentChange));
}

void ListModelStatic::SetOnItemMove(FrameNode* frameNode, OnItemMoveEvent&& onItemMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemMove(std::move(onItemMove));

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetOnItemDragStart(FrameNode* frameNode, OnItemDragStartFunc&& onItemDragStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart =
        [func = std::move(onItemDragStart)](const ItemDragInfo& dragInfo, int32_t index) -> RefPtr<AceType> {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            return func(dragInfo, index);
        }
    };
    eventHub->SetOnItemDragStart(onDragStart);

    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    eventHub->InitItemDragEvent(gestureEventHub);

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetOnItemDragEnter(FrameNode* frameNode, OnItemDragEnterFunc&& onItemDragEnter)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetOnItemDragLeave(FrameNode* frameNode, OnItemDragLeaveFunc&& onItemDragLeave)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetOnItemDragMove(FrameNode* frameNode, OnItemDragMoveFunc&& onItemDragMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetOnItemDrop(FrameNode* frameNode, OnItemDropFunc&& onItemDrop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(onItemDrop));

    ListModelStatic::AddDragFrameNodeToManager(frameNode);
}

void ListModelStatic::SetLanes(FrameNode* frameNode, int32_t lanes)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes, frameNode);
}

void ListModelStatic::SetLaneConstrain(
    FrameNode* frameNode, const Dimension& laneMinLength, const Dimension& laneMaxLength)
{
    SetLaneMinLength(frameNode, laneMinLength);
    SetLaneMaxLength(frameNode, laneMaxLength);
}

void ListModelStatic::SetLaneGutter(FrameNode* frameNode, const Dimension& laneGutter)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter, frameNode);
}

void ListModelStatic::SetLaneMinLength(FrameNode* frameNode, const Dimension& laneMinLength)
{
    if (laneMinLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMinLength, laneMinLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMinLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelStatic::SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength)
{
    if (laneMaxLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMaxLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelStatic::SetEditMode(FrameNode* frameNode, bool editMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, EditMode, editMode, frameNode);
}

void ListModelStatic::SetMultiSelectable(FrameNode* frameNode, bool selectable)
{
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(selectable);
}
} // namespace OHOS::Ace::NG