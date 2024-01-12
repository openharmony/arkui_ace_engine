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

#include "core/components_ng/pattern/list/list_model_ng.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

void ListModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LIST_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LIST_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ListPattern>(); });
    stack->Push(frameNode);
}

RefPtr<FrameNode> ListModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, nodeId, AceType::MakeRefPtr<ListPattern>());
    return frameNode;
}

void ListModelNG::SetSpace(const Dimension& space)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Space, space);
}

void ListModelNG::SetInitialIndex(int32_t initialIndex)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, initialIndex);
}

void ListModelNG::SetContentStartOffset(float startOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ContentStartOffset, startOffset);
}

void ListModelNG::SetContentEndOffset(float endOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ContentEndOffset, endOffset);
}

RefPtr<ScrollControllerBase> ListModelNG::CreateScrollController()
{
    return AceType::MakeRefPtr<NG::ListPositionController>();
}

void ListModelNG::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
    CHECK_NULL_VOID(list);
    list->SetPositionController(AceType::DynamicCast<ListPositionController>(scroller));
    list->SetScrollBarProxy(AceType::DynamicCast<ScrollBarProxy>(proxy));
}

void ListModelNG::SetListDirection(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, axis);
}

void ListModelNG::SetScrollBar(DisplayMode scrollBar)
{
    ScrollableModelNG::SetScrollBarMode(scrollBar);
}

void ListModelNG::SetScrollBarColor(const std::string& value)
{
    ScrollableModelNG::SetScrollBarColor(value);
}
void ListModelNG::SetScrollBarWidth(const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(value);
}

void ListModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled);
}

void ListModelNG::SetEditMode(bool editMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, EditMode, editMode);
}

void ListModelNG::SetDivider(const V2::ItemDivider& divider)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider);
}

void ListModelNG::SetChainAnimation(bool enableChainAnimation)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ChainAnimation, enableChainAnimation);
}

void ListModelNG::SetChainAnimationOptions(const ChainAnimationOptions& options)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetChainAnimationOptions(options);
}

void ListModelNG::SetLanes(int32_t lanes)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes);
}

void ListModelNG::SetLaneConstrain(const Dimension& laneMinLength, const Dimension& laneMaxLength)
{
    SetLaneMinLength(laneMinLength);
    SetLaneMaxLength(laneMaxLength);
}

void ListModelNG::SetLaneMinLength(const Dimension& laneMinLength)
{
    if (laneMinLength.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMinLength, laneMinLength);
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMinLength, PROPERTY_UPDATE_MEASURE);
    }
}

void ListModelNG::SetLaneMaxLength(const Dimension& laneMaxLength)
{
    if (laneMaxLength.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength);
    } else {
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMaxLength, PROPERTY_UPDATE_MEASURE);
    }
}

void ListModelNG::SetLaneGutter(const Dimension& laneGutter)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter);
}

void ListModelNG::SetListItemAlign(V2::ListItemAlign listItemAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign);
}

void ListModelNG::SetCachedCount(int32_t cachedCount)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, cachedCount);
}

void ListModelNG::SetSticky(V2::StickyStyle stickyStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle, stickyStyle);
}

void ListModelNG::SetScrollSnapAlign(V2::ScrollSnapAlign scrollSnapAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign);
}

void ListModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void ListModelNG::SetMultiSelectable(bool selectable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(selectable);
}

void ListModelNG::SetScrollEnabled(bool scrollEnabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollEnabled, scrollEnabled);
}

void ListModelNG::SetFriction(double friction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void ListModelNG::SetOnScroll(OnScrollEvent&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void ListModelNG::SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollBegin(std::move(onScrollBegin));
}

void ListModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void ListModelNG::SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ListModelNG::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ListModelNG::SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void ListModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ListModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void ListModelNG::SetOnItemMove(OnItemMoveEvent&& onItemMove)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemMove(std::move(onItemMove));

    AddDragFrameNodeToManager();
}

void ListModelNG::SetOnItemDragStart(OnItemDragStartFunc&& onItemDragStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

    AddDragFrameNodeToManager();
}

void ListModelNG::SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    AddDragFrameNodeToManager();
}

void ListModelNG::SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    AddDragFrameNodeToManager();
}

void ListModelNG::SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    AddDragFrameNodeToManager();
}

void ListModelNG::SetOnItemDrop(OnItemDropFunc&& onItemDrop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(onItemDrop));

    AddDragFrameNodeToManager();
}

void ListModelNG::AddDragFrameNodeToManager() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddListDragFrameNode(frameNode->GetId(), AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

DisplayMode ListModelNG::GetDisplayMode() const
{
    auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
    CHECK_NULL_RETURN(list, DisplayMode::AUTO);
    return list->GetDefaultScrollBarDisplayMode();
}

void ListModelNG::SetEditMode(FrameNode* frameNode, bool editMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, EditMode, editMode, frameNode);
}

void ListModelNG::SetMultiSelectable(FrameNode* frameNode, bool selectable)
{
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(selectable);
}

void ListModelNG::SetChainAnimation(FrameNode* frameNode, bool chainAnimation)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ChainAnimation, chainAnimation, frameNode);
}

void ListModelNG::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, cachedCount, frameNode);
}

void ListModelNG::SetScrollEnabled(FrameNode* frameNode, bool enableScrollInteraction)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollEnabled, enableScrollInteraction, frameNode);
}

void ListModelNG::SetSticky(FrameNode* frameNode, int32_t stickyStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle,
        static_cast<V2::StickyStyle>(stickyStyle), frameNode);
}

void ListModelNG::SetEdgeEffect(FrameNode* frameNode, int32_t edgeEffect, bool alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void ListModelNG::SetListDirection(FrameNode* frameNode, int32_t axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, static_cast<Axis>(axis), frameNode);
}

void ListModelNG::SetListFriction(FrameNode* frameNode, double friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (LessOrEqual(friction, 0.0)) {
        pattern->SetFriction(FRICTION);
    }
    pattern->SetFriction(friction);
}

void ListModelNG::SetListNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void ListModelNG::SetListScrollBar(FrameNode* frameNode, int32_t barState)
{
    int32_t displayNumber;
    DisplayMode mode;
    if (barState < 0 || barState >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
        if (!list) {
            mode = DisplayMode::AUTO;
        } else {
            mode = list->GetDefaultScrollBarDisplayMode();
        }
        displayNumber = static_cast<int32_t>(mode);
    } else {
        displayNumber = barState;
    }
    ScrollableModelNG::SetScrollBarMode(frameNode, displayNumber);
}

void ListModelNG::SetLanes(FrameNode* frameNode, int32_t lanes)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes, frameNode);
}

void ListModelNG::SetLaneConstrain(FrameNode* frameNode, const Dimension& laneMinLength, const Dimension& laneMaxLength)
{
    SetLaneMinLength(frameNode, laneMinLength);
    SetLaneMaxLength(frameNode, laneMaxLength);
}

void ListModelNG::SetLaneMinLength(FrameNode* frameNode, const Dimension& laneMinLength)
{
    if (laneMinLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMinLength, laneMinLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMinLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelNG::SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength)
{
    if (laneMaxLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMaxLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelNG::SetLaneGutter(FrameNode* frameNode, const Dimension& laneGutter)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter, frameNode);
}

void ListModelNG::SetListItemAlign(FrameNode* frameNode, V2::ListItemAlign listItemAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign, frameNode);
}

void ListModelNG::SetScrollSnapAlign(FrameNode* frameNode, V2::ScrollSnapAlign scrollSnapAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign, frameNode);
}

void ListModelNG::SetDivider(FrameNode* frameNode, const V2::ItemDivider& divider)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
}

void ListModelNG::SetChainAnimationOptions(FrameNode* frameNode, const ChainAnimationOptions& options)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetChainAnimationOptions(options);
}

} // namespace OHOS::Ace::NG
