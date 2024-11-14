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

#include "core/components_ng/pattern/list/list_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/list/list_properties.h"
#include "core/components/list/list_theme.h"

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
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
}

RefPtr<FrameNode> ListModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, nodeId, AceType::MakeRefPtr<ListPattern>());
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    return frameNode;
}

RefPtr<ScrollControllerBase> ListModelNG::GetOrCreateController(FrameNode* frameNode)
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

RefPtr<ScrollProxy> ListModelNG::GetOrCreateScrollBarProxy(FrameNode* frameNode)
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

void ListModelNG::ScrollToEdge(FrameNode* frameNode, ScrollEdgeType scrollEdgeType, bool smooth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() != Axis::NONE) {
        pattern->ScrollToEdge(scrollEdgeType, smooth);
    }
}

RefPtr<FrameNode> ListModelNG::CreateList(int32_t nodeId)
{
    auto listNode =
        FrameNode::GetOrCreateFrameNode(V2::LIST_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ListPattern>(); });
    return listNode;
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

void ListModelNG::SetListItemTotalCount(FrameNode* frameNode, int totalCount)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetListItemAdapter()->totalCount != totalCount) {
        pattern->GetListItemAdapter()->totalCount = static_cast<int32_t>(totalCount);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void ListModelNG::SetListItemAdapterFunc(FrameNode* frameNode, std::function<void(int start, int end)>&& requestFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetListItemAdapter()->requestItemFunc = std::move(requestFunc);
}

void ListModelNG::SetListItemAdapterCallFinish(FrameNode* frameNode, int start, int end)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetListItemAdapter()->range.first = start;
    pattern->GetListItemAdapter()->range.second = end;
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ListModelNG::SetListItemGetFunc(FrameNode* frameNode, std::function<RefPtr<FrameNode>(int32_t index)>&& getFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->GetListItemAdapter()->getItemFunc = std::move(getFunc);
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

int32_t ListModelNG::GetSticky(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(frameNode->GetLayoutProperty<ListLayoutProperty>()->GetStickyStyleValue());
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

int32_t ListModelNG::GetScrollEnabled(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    int32_t value = true;
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    if (layoutProperty->GetScrollEnabled()) {
        value = layoutProperty->GetScrollEnabledValue();
    }
    return value;
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

void ListModelNG::SetMaintainVisibleContentPosition(bool enabled)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaintainVisibleContentPosition(enabled);
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

void ListModelNG::SetOnScrollIndex(FrameNode* frameNode, OnScrollIndexEvent&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void ListModelNG::SetOnScrollVisibleContentChange(OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollVisibleContentChange(std::move(onScrollVisibleContentChange));
}

void ListModelNG::SetOnScrollVisibleContentChange(FrameNode* frameNode,
    OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollVisibleContentChange(std::move(onScrollVisibleContentChange));
}

void ListModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ListModelNG::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
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

void ListModelNG::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
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

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemMove(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& onItemMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onMove = [func = std::move(onItemMove)](int32_t from, int32_t to) -> bool {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            func(from, to);
        }
        return ViewStackProcessor::GetInstance()->Finish();
    };
    eventHub->SetOnItemMove(std::move(onMove));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
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

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragStart(FrameNode* frameNode,
    std::function<void(const ItemDragInfo&, int32_t)>&& onItemDragStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart =
        [func = std::move(onItemDragStart)](const ItemDragInfo& dragInfo, int32_t index) -> RefPtr<AceType> {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            func(dragInfo, index);
        }
        return ViewStackProcessor::GetInstance()->Finish();
    };
    eventHub->SetOnItemDragStart(std::move(onDragStart));

    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    eventHub->InitItemDragEvent(gestureEventHub);

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragEnter(OnItemDragEnterFunc&& onItemDragEnter)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragEnter(FrameNode* frameNode, OnItemDragEnterFunc&& onItemDragEnter)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragLeave(OnItemDragLeaveFunc&& onItemDragLeave)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragLeave(FrameNode* frameNode, OnItemDragLeaveFunc&& onItemDragLeave)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragMove(OnItemDragMoveFunc&& onItemDragMove)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragMove(FrameNode* frameNode, OnItemDragMoveFunc&& onItemDragMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDrop(OnItemDropFunc&& onItemDrop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(onItemDrop));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDrop(FrameNode* frameNode, OnItemDropFunc&& onItemDrop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(onItemDrop));

    ListModelNG::AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddListDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ListModelNG::SetInitialIndex(FrameNode* frameNode, const std::optional<int32_t>& initialIndex)
{
    if (initialIndex.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, initialIndex.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, frameNode);
    }
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
    if (cachedCount >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, cachedCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, frameNode);
    }
}

int32_t ListModelNG::GetCachedCount(FrameNode* frameNode)
{
    int32_t cachedCount = 1;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListLayoutProperty, CachedCount, cachedCount, frameNode, 1);
    return cachedCount;
}

void ListModelNG::SetScrollEnabled(FrameNode* frameNode, bool enableScrollInteraction)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollEnabled, enableScrollInteraction, frameNode);
}

void ListModelNG::SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle)
{
    if (stickyStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle,
            static_cast<V2::StickyStyle>(stickyStyle.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle, frameNode);
    }
}

void ListModelNG::SetEdgeEffect(FrameNode* frameNode, const std::optional<int32_t>& edgeEffect,
    const std::optional<bool>& alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(frameNode,
        static_cast<EdgeEffect>(edgeEffect.value_or(GetEdgeEffect(frameNode))),
        alwaysEnabled.value_or(GetEdgeEffectAlways(frameNode)));
}

int32_t ListModelNG::GetListDirection(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(frameNode->GetLayoutProperty<ListLayoutProperty>()->GetListDirection().value());
}

void ListModelNG::SetListDirection(FrameNode* frameNode, const std::optional<int32_t>& axis)
{
    if (axis.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, static_cast<Axis>(axis.value()), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, frameNode);
    }
}

float ListModelNG::GetListFriction(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetPattern<ListPattern>()->GetFriction();
}

void ListModelNG::SetListFriction(FrameNode* frameNode, const std::optional<double>& friction)
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

void ListModelNG::SetListMaintainVisibleContentPosition(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaintainVisibleContentPosition(enabled);
}

void ListModelNG::SetListNestedScroll(FrameNode* frameNode, const std::optional<NestedScrollMode>& forward,
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

void ListModelNG::SetListNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

NestedScrollOptions ListModelNG::GetListNestedScroll(FrameNode* frameNode)
{
    NestedScrollOptions defaultOptions;
    CHECK_NULL_RETURN(frameNode, defaultOptions);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, defaultOptions);
    return pattern->GetNestedScroll();
}

int32_t ListModelNG::GetListScrollBar(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetScrollBarMode().value());
}

void ListModelNG::SetListScrollBar(FrameNode* frameNode, const std::optional<int32_t>& barState)
{
    CHECK_NULL_VOID(frameNode);
    int32_t displayNumber;
    DisplayMode mode;

    if (!barState.has_value() || (barState.has_value() &&
        (barState.value() < 0 || barState.value() >= static_cast<int32_t>(DISPLAY_MODE.size())))) {
        auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
        if (!list) {
            mode = DisplayMode::AUTO;
        } else {
            mode = list->GetDefaultScrollBarDisplayMode();
        }
        displayNumber = static_cast<int32_t>(mode);
    } else {
        displayNumber = barState.value();
    }

    ScrollableModelNG::SetScrollBarMode(frameNode, displayNumber);
}

float ListModelNG::GetScrollBarWidth(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarWidth();
    return value.ConvertToVp();
}

void ListModelNG::SetListScrollBarWidth(FrameNode* frameNode, const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(frameNode, value);
}

uint32_t ListModelNG::GetScrollBarColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarColor();
    return value.GetValue();
}

void ListModelNG::SetListScrollBarColor(FrameNode* frameNode, const std::string& value)
{
    ScrollableModelNG::SetScrollBarColor(frameNode, value);
}

void ListModelNG::SetLanes(FrameNode* frameNode, int32_t lanes)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes, frameNode);
}

void ListModelNG::SetLaneConstrain(FrameNode* frameNode,
    const Dimension& laneMinLength, const Dimension& laneMaxLength)
{
    SetLaneMinLength(frameNode, laneMinLength);
    SetLaneMaxLength(frameNode, laneMaxLength);
}

void ListModelNG::SetLaneMinLength(FrameNode* frameNode, const Dimension& laneMinLength)
{
    if (laneMinLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMinLength, laneMinLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty,
            LaneMinLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelNG::SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength)
{
    if (laneMaxLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty,
            LaneMaxLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void ListModelNG::SetLaneGutter(FrameNode* frameNode, const std::optional<Dimension>& laneGutter)
{
    if (laneGutter.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, frameNode);
    }
}

int32_t ListModelNG::GetListItemAlign(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(
        frameNode->GetLayoutProperty<ListLayoutProperty>()->GetListItemAlignValue(V2::ListItemAlign::START));
}

void ListModelNG::SetListItemAlign(FrameNode* frameNode, const std::optional<V2::ListItemAlign>& listItemAlign)
{
    if (listItemAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, frameNode);
    }
}

float ListModelNG::GetListSpace(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto value = frameNode->GetLayoutProperty<ListLayoutProperty>()->GetSpaceValue();
    return value.ConvertToVp();
}

void ListModelNG::SetListSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Space, space.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Space, frameNode);
    }
}

int32_t ListModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return ScrollableModelNG::GetEdgeEffect(frameNode);
}

int32_t ListModelNG::GetEdgeEffectAlways(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ScrollableModelNG::GetAlwaysEnabled(frameNode);
}

void ListModelNG::SetScrollSnapAlign(FrameNode* frameNode, const std::optional<V2::ScrollSnapAlign>& scrollSnapAlign)
{
    if (scrollSnapAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, frameNode);
    }
}

void ListModelNG::SetContentStartOffset(FrameNode* frameNode, float startOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentStartOffset, startOffset, frameNode);
}

void ListModelNG::SetContentEndOffset(FrameNode* frameNode, float endOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentEndOffset, endOffset, frameNode);
}

void ListModelNG::SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider)
{
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, frameNode);
    }
}

void ListModelNG::SetChainAnimationOptions(FrameNode* frameNode, const ChainAnimationOptions& options)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetChainAnimationOptions(options);
}

DisplayMode ListModelNG::GetDisplayMode() const
{
    auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
    CHECK_NULL_RETURN(list, DisplayMode::AUTO);
    return list->GetDefaultScrollBarDisplayMode();
}

void ListModelNG::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void ListModelNG::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void ListModelNG::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ListModelNG::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ListModelNG::SetScrollToIndex(FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ScrollToIndex(index, animation, static_cast<ScrollAlign>(alignment));
}

void ListModelNG::SetScrollBy(FrameNode* frameNode, double x, double y)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->StopAnimate();
    auto offset = pattern->GetAxis() == Axis::VERTICAL ? y : x;
    if (NearZero(offset)) {
        return;
    }
    pattern->UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
}

void ListModelNG::SetFlingSpeedLimit(FrameNode* frameNode, double maxSpeed)
{
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, maxSpeed);
}

RefPtr<ListChildrenMainSize> ListModelNG::GetOrCreateListChildrenMainSize()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

RefPtr<ListChildrenMainSize> ListModelNG::GetOrCreateListChildrenMainSize(
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

RefPtr<ListChildrenMainSize> ListModelNG::GetOrCreateListChildrenMainSize(
    FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateListChildrenMainSize();
}

void ListModelNG::SetListChildrenMainSize(
    FrameNode* frameNode, float defaultSize, const std::vector<float>& mainSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetListChildrenMainSize(defaultSize, mainSize);
}

void ListModelNG::ResetListChildrenMainSize(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetChildrenSize();
}

int32_t ListModelNG::GetInitialIndex(FrameNode* frameNode)
{
    int32_t value = 0;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListLayoutProperty, InitialIndex, value, frameNode, value);
    return value;
}

V2::ItemDivider ListModelNG::GetDivider(FrameNode* frameNode)
{
    V2::ItemDivider value;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListLayoutProperty, Divider, value, frameNode, value);
    return value;
}

void ListModelNG::SetScroller(FrameNode* frameNode, RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPositionController(AceType::DynamicCast<ListPositionController>(scroller));
    pattern->SetScrollBarProxy(AceType::DynamicCast<ScrollBarProxy>(proxy));
}
} // namespace OHOS::Ace::NG
