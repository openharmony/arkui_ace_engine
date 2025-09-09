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

#include "base/utils/multi_thread.h"
#include "base/utils/system_properties.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/list/list_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/manager/scroll_adjust/scroll_adjust_manager.h"

namespace OHOS::Ace::NG {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

void ListModelNG::Create(bool isCreateArc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    const char* tag = isCreateArc ? V2::ARC_LIST_ETS_TAG : V2::LIST_ETS_TAG;
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag, nodeId);
    RefPtr<FrameNode> frameNode = nullptr;
    if (!isCreateArc) {
        frameNode = FrameNode::GetOrCreateFrameNode(tag, nodeId, []() { return AceType::MakeRefPtr<ListPattern>(); });
    } else {
        frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<ArcListPattern>(); });
    }
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    if (SystemProperties::ConfigChangePerform()) {
        auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->ResetDividerColorSetByUser();
        auto resourceObject = AceType::MakeRefPtr<ResourceObject>("", "", 0);
        auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))](
                                const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            frameNode->SetMeasureAnyway(frameNode->GetRerenderable());
        };
        pattern->AddResObj("listMeasureAllItem", resourceObject, std::move(updateFunc));
    }
}

RefPtr<FrameNode> ListModelNG::CreateFrameNode(int32_t nodeId, bool isCreateArc)
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

void ListModelNG::ScrollToEdge(FrameNode* frameNode, ScrollEdgeType scrollEdgeType, bool smooth)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() != Axis::NONE) {
        pattern->ScrollToEdge(scrollEdgeType, smooth);
    }
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

void ListModelNG::SetScrollBarColor(const std::optional<Color>& scrollBarColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetScrollBarColor(frameNode, scrollBarColor);
}

void ListModelNG::SetScrollBarWidth(const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(value);
}

void ListModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled, edge);
}

void ListModelNG::SetEditMode(bool editMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, EditMode, editMode);
}

void ListModelNG::SetDivider(const V2::ItemDivider& divider)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider);
}

void ListModelNG::SetDividerColorByUser(bool isByUser)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, DividerColorSetByUser, isByUser);
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

void ListModelNG::SetCachedCount(int32_t cachedCount, bool show)
{
    int32_t count = cachedCount;
    if (SystemProperties::IsWhiteBlockEnabled()) {
        count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, count);
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, ShowCachedItems, show);
}

int32_t ListModelNG::GetSticky(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    const auto& layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    return static_cast<int32_t>(layoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE));
}

void ListModelNG::SetSticky(V2::StickyStyle stickyStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, StickyStyle, stickyStyle);
}

void ListModelNG::SetScrollSnapAlign(ScrollSnapAlign scrollSnapAlign)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto lastScrollSnapAlign = layoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    if (lastScrollSnapAlign != scrollSnapAlign) {
        auto pattern = frameNode->GetPattern<ListPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->ResetLastSnapTargetIndex();
    }
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

FocusWrapMode ListModelNG::GetFocusWrapMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, FocusWrapMode::DEFAULT);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, FocusWrapMode::DEFAULT);
    return pattern->GetFocusWrapMode();
}

void ListModelNG::SetFocusWrapMode(FocusWrapMode focusWrapMode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusWrapMode(focusWrapMode);
}

void ListModelNG::SetFocusWrapMode(FrameNode* frameNode, FocusWrapMode focusWrapMode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusWrapMode(focusWrapMode);
}

void ListModelNG::SetMaintainVisibleContentPosition(bool enabled)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaintainVisibleContentPosition(enabled);
}

void ListModelNG::SetStackFromEnd(bool enabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, StackFromEnd, enabled);
}

void ListModelNG::SetSyncLoad(bool enabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListLayoutProperty, SyncLoad, enabled);
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddListDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ListModelNG::SetInitialIndex(FrameNode* frameNode, int32_t initialIndex)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, InitialIndex, initialIndex, frameNode);
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
    int32_t count = cachedCount;
    if (SystemProperties::IsWhiteBlockEnabled()) {
        count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CachedCount, count, frameNode);
}

void ListModelNG::SetShowCached(FrameNode* frameNode, bool show)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ShowCachedItems, show, frameNode);
}

int32_t ListModelNG::GetCachedCount(FrameNode* frameNode)
{
    int32_t cachedCount = 1;
    CHECK_NULL_RETURN(frameNode, cachedCount);
    auto property = frameNode->GetLayoutPropertyPtr<ListLayoutProperty>();
    CHECK_NULL_RETURN(property, cachedCount);
    return property->GetCachedCountWithDefault();
}

bool ListModelNG::GetShowCached(FrameNode* frameNode)
{
    bool show = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(ListLayoutProperty, ShowCachedItems, show, frameNode, false);
    return show;
}

void ListModelNG::SetCacheRange(FrameNode* frameNode, int32_t min, int32_t max)
{
    CacheRange range { min, max };
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CacheRange, range, frameNode);
}

void ListModelNG::ResetCacheRange(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(ListLayoutProperty, CacheRange, frameNode);
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

void ListModelNG::SetEdgeEffect(FrameNode* frameNode, int32_t edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(
        frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, edge);
}

int32_t ListModelNG::GetListDirection(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    const auto& layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    return static_cast<int32_t>(layoutProperty->GetListDirectionValue(Axis::VERTICAL));
}

void ListModelNG::SetListDirection(FrameNode* frameNode, int32_t axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListDirection, static_cast<Axis>(axis), frameNode);
}

float ListModelNG::GetListFriction(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetPattern<ListPattern>()->GetFriction();
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

void ListModelNG::CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ListFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("ListFriction", resObj, std::move(updateFunc));
}

void ListModelNG::CreateWithResourceObjLaneGutter(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("LaneGutter");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension laneGutter;
        if (ResourceParseUtils::ParseResDimensionVp(resObj, laneGutter)) {
            if (laneGutter.IsNegative()) {
                laneGutter.Reset();
            }
        }
        ListModelNG::SetLaneGutter(AceType::RawPtr(frameNode), laneGutter);
    };
    pattern->AddResObj("LaneGutter", resObj, std::move(updateFunc));
}

void ListModelNG::CreateWithResourceObjLaneConstrain(
    const RefPtr<ResourceObject>& resObjMinLengthValue, const RefPtr<ResourceObject>& resObjMaxLengthValue)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ListMinLength");
    pattern->RemoveResObj("ListMaxLength");
    if (resObjMinLengthValue) {
        auto&& minLengthupdateFunc = [weak = AceType::WeakClaim(frameNode)](
                                         const RefPtr<ResourceObject>& resObjMinLengthValue) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            CalcDimension minLengthValue;
            if (ResourceParseUtils::ParseResDimensionVp(resObjMinLengthValue, minLengthValue)) {
                ListModelNG::SetLaneMinLength(AceType::RawPtr(frameNode), minLengthValue);
            } else {
                ListModelNG::SetLaneConstrain(AceType::RawPtr(frameNode), -1.0_vp, -1.0_vp);
            }
        };
        pattern->AddResObj("ListMinLength", resObjMinLengthValue, std::move(minLengthupdateFunc));
    }
    if (resObjMaxLengthValue) {
        auto&& maxLengthupdateFunc = [weak = AceType::WeakClaim(frameNode)](
                                         const RefPtr<ResourceObject>& resObjMaxLengthValue) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            CalcDimension maxLengthValue;
            if (ResourceParseUtils::ParseResDimensionVp(resObjMaxLengthValue, maxLengthValue)) {
                ListModelNG::SetLaneMaxLength(AceType::RawPtr(frameNode), maxLengthValue);
            } else {
                ListModelNG::SetLaneConstrain(AceType::RawPtr(frameNode), -1.0_vp, -1.0_vp);
            }
        };
        pattern->AddResObj("ListMaxLength", resObjMaxLengthValue, std::move(maxLengthupdateFunc));
    }
}

void ListModelNG::CreateWithResourceObjScrollBarColor(const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObjScrollBarColor(frameNode, resObj);
}

void ListModelNG::SetListMaintainVisibleContentPosition(FrameNode* frameNode, bool enabled)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaintainVisibleContentPosition(enabled);
}

bool ListModelNG::GetListMaintainVisibleContentPosition(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, false);
    std::optional<bool> maintainVisibleContentPosition = pattern->GetMaintainVisibleContentPosition();
    return maintainVisibleContentPosition.value_or(false);
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

void ListModelNG::SetDividerColorByUser(FrameNode* frameNode, bool colorSetByUser)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, DividerColorSetByUser, colorSetByUser, frameNode);
}

int32_t ListModelNG::GetListScrollBar(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(
        frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetScrollBarMode().value_or(DisplayMode::AUTO));
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

void ListModelNG::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& scrollBarColor)
{
    ScrollableModelNG::SetScrollBarColor(frameNode, scrollBarColor);
}

void ListModelNG::SetLanes(FrameNode* frameNode, int32_t lanes)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Lanes, lanes, frameNode);
}

int32_t ListModelNG::GetLanes(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(frameNode->GetLayoutProperty<ListLayoutProperty>()->GetLanes().value_or(1));
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

float ListModelNG::GetLaneMinLength(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    Dimension laneMinLength = 0.0_vp;
    return frameNode->GetLayoutProperty<ListLayoutProperty>()->GetLaneMinLength().value_or(laneMinLength).Value();
}

void ListModelNG::SetLaneMaxLength(FrameNode* frameNode, const Dimension& laneMaxLength)
{
    if (laneMaxLength.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneMaxLength, laneMaxLength, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(ListLayoutProperty, LaneMaxLength, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

float ListModelNG::GetLaneMaxLength(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    Dimension laneMaxLength = 0.0_vp;
    return frameNode->GetLayoutProperty<ListLayoutProperty>()->GetLaneMaxLength().value_or(laneMaxLength).Value();
}

void ListModelNG::SetLaneGutter(FrameNode* frameNode, const Dimension& laneGutter)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, LaneGutter, laneGutter, frameNode);
}

float ListModelNG::GetLaneGutter(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    Dimension laneLaneGutter = 0.0_vp;
    return frameNode->GetLayoutProperty<ListLayoutProperty>()->GetLaneGutter().value_or(laneLaneGutter).Value();
}

int32_t ListModelNG::GetListItemAlign(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(
        frameNode->GetLayoutProperty<ListLayoutProperty>()->GetListItemAlignValue(V2::ListItemAlign::START));
}

void ListModelNG::SetListItemAlign(FrameNode* frameNode, V2::ListItemAlign listItemAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ListItemAlign, listItemAlign, frameNode);
}

float ListModelNG::GetListSpace(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    const auto& layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto value = layoutProperty->GetSpace().value_or(Dimension(0.0_vp));
    return value.ConvertToVp();
}

void ListModelNG::SetListSpace(FrameNode* frameNode, const Dimension& space)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Space, space, frameNode);
}

int32_t ListModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return ScrollableModelNG::GetEdgeEffect(frameNode);
}

void ListModelNG::SetListStackFromEnd(FrameNode* frameNode, bool enabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, StackFromEnd, enabled, frameNode);
}

bool ListModelNG::GetListStackFromEnd(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto value = frameNode->GetLayoutProperty<ListLayoutProperty>()->GetStackFromEnd().value_or(false);
    return value;
}

void ListModelNG::SetListSyncLoad(FrameNode* frameNode, bool enabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, SyncLoad, enabled, frameNode);
}

bool ListModelNG::GetListSyncLoad(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto value = frameNode->GetLayoutProperty<ListLayoutProperty>()->GetSyncLoad().value_or(true);
    return value;
}

int32_t ListModelNG::GetEdgeEffectAlways(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ScrollableModelNG::GetAlwaysEnabled(frameNode);
}

EffectEdge ListModelNG::GetEffectEdge(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, EffectEdge::ALL);
    return ScrollableModelNG::GetEffectEdge(frameNode);
}

void ListModelNG::SetScrollSnapAlign(FrameNode* frameNode, ScrollSnapAlign scrollSnapAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ScrollSnapAlign, scrollSnapAlign, frameNode);
}

int32_t ListModelNG::GetScrollSnapAlign(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    return static_cast<int32_t>(layoutProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE));
}

void ListModelNG::SetContentStartOffset(FrameNode* frameNode, float startOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentStartOffset, startOffset, frameNode);
}

float ListModelNG::GetContentStartOffset(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    return static_cast<float>(layoutProperty->GetContentStartOffset().value_or(0.0f));
}

void ListModelNG::SetContentEndOffset(FrameNode* frameNode, float endOffset)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, ContentEndOffset, endOffset, frameNode);
}

float ListModelNG::GetContentEndOffset(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    return static_cast<float>(layoutProperty->GetContentEndOffset().value_or(0.0f));
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

DisplayMode ListModelNG::GetDisplayMode() const
{
    auto list = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<ListPattern>();
    CHECK_NULL_RETURN(list, DisplayMode::AUTO);
    return list->GetDefaultScrollBarDisplayMode();
}

void ListModelNG::SetHeader(const RefPtr<FrameNode>& headerNode)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArcListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(headerNode);
}

void ListModelNG::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScroll(std::move(onScroll));
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

void ListModelNG::SetScrollToIndex(
    FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment, std::optional<float> extraOffset)
{
    // call SetScrollToIndexMultiThread by multi thread
    FREE_NODE_CHECK(frameNode, SetScrollToIndex, frameNode, index, animation, alignment, extraOffset);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ScrollToIndex(index, animation, static_cast<ScrollAlign>(alignment), extraOffset);
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

RefPtr<ListChildrenMainSize> ListModelNG::GetOrCreateListChildrenMainSize()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

void ListModelNG::ResetListChildrenMainSize()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetListChildrenMainSize(frameNode);
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

void ListModelNG::SetHeader(FrameNode* frameNode, FrameNode* headerNode)
{
    CHECK_NULL_VOID(headerNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArcListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddHeader(AceType::Claim<FrameNode>(headerNode));
}

#ifdef SUPPORT_DIGITAL_CROWN
void ListModelNG::SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ListModelNG::SetDigitalCrownSensitivity(frameNode, sensitivity);
}

void ListModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArcListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDigitalCrownSensitivity(sensitivity);
}

CrownSensitivity ListModelNG::GetDigitalCrownSensitivity(FrameNode* frameNode)
{
    CrownSensitivity sensitivity = CrownSensitivity::MEDIUM;
    CHECK_NULL_RETURN(frameNode, sensitivity);
    auto pattern = frameNode->GetPattern<ArcListPattern>();
    CHECK_NULL_RETURN(pattern, sensitivity);
    return pattern->GetDigitalCrownSensitivity();
}
#endif

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

void ListModelNG::SetOnScrollVisibleContentChange(
    FrameNode* frameNode, OnScrollVisibleContentChangeEvent&& onScrollVisibleContentChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollVisibleContentChange(std::move(onScrollVisibleContentChange));
}

void ListModelNG::SetOnItemMove(FrameNode* frameNode, OnItemMoveEvent&& onItemMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemMove(std::move(onItemMove));

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragStart(FrameNode* frameNode, OnItemDragStartFunc&& onItemDragStart)
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

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragEnter(FrameNode* frameNode, OnItemDragEnterFunc&& onItemDragEnter)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(onItemDragEnter));

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragLeave(FrameNode* frameNode, OnItemDragLeaveFunc&& onItemDragLeave)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(onItemDragLeave));

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDragMove(FrameNode* frameNode, OnItemDragMoveFunc&& onItemDragMove)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(onItemDragMove));

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::SetOnItemDrop(FrameNode* frameNode, OnItemDropFunc&& onItemDrop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(onItemDrop));

    AddDragFrameNodeToManager(frameNode);
}

void ListModelNG::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddListDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void ListModelNG::ScrollToItemInGroup(
    FrameNode* frameNode, int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    // call ScrollToItemInGroupMultiThread by multi thread
    FREE_NODE_CHECK(frameNode, ScrollToItemInGroup, frameNode, index, indexInGroup, smooth, align);
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    if (align == ScrollAlign::NONE) {
        align = ScrollAlign::START;
    }
    listPattern->ScrollToItemInGroup(index, indexInGroup, smooth, align);
}

void ListModelNG::ParseResObjDividerStrokeWidth(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.strokeWidth");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            result = 0.0_vp;
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.strokeWidth = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.strokeWidth", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerColor(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.color");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color result;
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = frameNode->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto listTheme = pipeline->GetTheme<ListTheme>();
            if (listTheme) {
                divider.color = listTheme->GetDividerColor();
            }
            ListModelNG::SetDividerColorByUser(AceType::RawPtr(frameNode), false);
        } else {
            divider.color = result;
            ListModelNG::SetDividerColorByUser(AceType::RawPtr(frameNode), true);
        }
        divider.color = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.color", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerStartMargin(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.startMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            result = 0.0_vp;
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.startMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.startMargin", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerEndMargin(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.endMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            result = 0.0_vp;
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.endMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.endMargin", resObj, std::move(updateFunc));
}

void ListModelNG::CreateWithResourceObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ListFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("ListFriction", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.strokeWidth");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result) || LessNotEqual(result.Value(), 0.0f) ||
            result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.strokeWidth = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.strokeWidth", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.color");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        Color result;
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = frameNode->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto listTheme = pipeline->GetTheme<ListTheme>();
            if (listTheme) {
                divider.color = listTheme->GetDividerColor();
            }
            ListModelNG::SetDividerColorByUser(AceType::RawPtr(frameNode), false);
        } else {
            divider.color = result;
            ListModelNG::SetDividerColorByUser(AceType::RawPtr(frameNode), true);
        }
        divider.color = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.color", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerStartMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.startMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result) || LessNotEqual(result.Value(), 0.0f) ||
            result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.startMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.startMargin", resObj, std::move(updateFunc));
}

void ListModelNG::ParseResObjDividerEndMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("list.divider.endMargin");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result) || LessNotEqual(result.Value(), 0.0f) ||
            result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
        V2::ItemDivider divider = GetDivider(AceType::RawPtr(frameNode));
        divider.endMargin = result;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListLayoutProperty, Divider, divider, frameNode);
    };
    pattern->AddResObj("list.divider.endMargin", resObj, std::move(updateFunc));
}

void ListModelNG::CreateWithResourceObjLaneConstrain(FrameNode* frameNode,
    const RefPtr<ResourceObject>& resObjMinLengthValue, const RefPtr<ResourceObject>& resObjMaxLengthValue)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ListMinLength");
    pattern->RemoveResObj("ListMaxLength");
    if (resObjMinLengthValue) {
        auto&& minLengthupdateFunc = [weak = AceType::WeakClaim(frameNode)](
                                        const RefPtr<ResourceObject>& resObjMinLengthValue) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            CalcDimension minLengthValue;
            if (ResourceParseUtils::ParseResDimensionVp(resObjMinLengthValue, minLengthValue)) {
                ListModelNG::SetLaneMinLength(AceType::RawPtr(frameNode), minLengthValue);
            } else {
                ListModelNG::SetLaneConstrain(AceType::RawPtr(frameNode), -1.0_vp, -1.0_vp);
            }
        };
        pattern->AddResObj("ListMinLength", resObjMinLengthValue, std::move(minLengthupdateFunc));
    }

    if (resObjMaxLengthValue) {
        auto&& maxLengthupdateFunc = [weak = AceType::WeakClaim(frameNode)](
                                        const RefPtr<ResourceObject>& resObjMaxLengthValue) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            CalcDimension maxLengthValue;
            if (ResourceParseUtils::ParseResDimensionVp(resObjMaxLengthValue, maxLengthValue)) {
                ListModelNG::SetLaneMaxLength(AceType::RawPtr(frameNode), maxLengthValue);
            } else {
                ListModelNG::SetLaneConstrain(AceType::RawPtr(frameNode), -1.0_vp, -1.0_vp);
            }
        };
        pattern->AddResObj("ListMaxLength", resObjMaxLengthValue, std::move(maxLengthupdateFunc));
    }
}

void ListModelNG::CreateWithResourceObjScrollBarColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    ScrollableModelNG::CreateWithResourceObjScrollBarColor(frameNode, resObj);
}
} // namespace OHOS::Ace::NG
