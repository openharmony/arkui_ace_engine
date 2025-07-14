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

#include "core/components_ng/pattern/list/list_item_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ListItemModelNG::Create(
    std::function<void(int32_t)>&& deepRenderFunc, V2::ListItemStyle listItemStyle, bool isCreateArc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    if (deepRenderFunc) {
        auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
            CHECK_NULL_RETURN(deepRenderFunc, nullptr);
            ScopedViewStackProcessor scopedViewStackProcessor;
            deepRenderFunc(nodeId);
            return ViewStackProcessor::GetInstance()->Finish();
        };
        const char* tag = isCreateArc ? V2::ARC_LIST_ITEM_ETS_TAG : V2::LIST_ITEM_ETS_TAG;
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag, nodeId);
        RefPtr<FrameNode> frameNode = nullptr;
        if (!isCreateArc) {
            frameNode = ScrollableItemPool::GetInstance().Allocate(tag, nodeId,
                [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender)), style = listItemStyle]() {
                    return AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, style);
                });
        } else {
            frameNode = ScrollableItemPool::GetInstance().Allocate(tag, nodeId,
                [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender)), style = listItemStyle]() {
                    return AceType::MakeRefPtr<ArcListItemPattern>(shallowBuilder, style);
                });
        }
        stack->Push(frameNode);
    } else {
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LIST_ITEM_ETS_TAG, nodeId);
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, nodeId,
            [listItemStyle]() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, listItemStyle); });
        stack->Push(frameNode);
    }
}

void ListItemModelNG::Create(bool isCreateArc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    RefPtr<FrameNode> frameNode = nullptr;
    if (!isCreateArc) {
        frameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });
    } else {
        frameNode = FrameNode::GetOrCreateFrameNode(V2::ARC_LIST_ITEM_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<ArcListItemPattern>(nullptr, V2::ListItemStyle::NONE); });
    }
    stack->Push(frameNode);
}

void ListItemModelNG::OnDidPop()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->OnDidPop();
}

RefPtr<FrameNode> ListItemModelNG::CreateFrameNode(int32_t nodeId, bool isCreateArc)
{
    if (isCreateArc) {
        return FrameNode::CreateFrameNode(V2::ARC_LIST_ITEM_ETS_TAG, nodeId,
            AceType::MakeRefPtr<ArcListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    }
    auto frameNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    return frameNode;
}

// use SetDeleteArea to update builder function
void ListItemModelNG::SetSwiperAction(std::function<void()>&& startAction, std::function<void()>&& endAction,
    OnOffsetChangeFunc&& onOffsetChangeFunc, V2::SwipeEdgeEffect edgeEffect, NG::FrameNode* node)
{
    if (!node) {
        node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOffsetChangeCallBack(std::move(onOffsetChangeFunc));
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, EdgeEffect, edgeEffect);
}

void ListItemModelNG::SetSticky(V2::StickyMode stickyMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, StickyMode, stickyMode);
}

void ListItemModelNG::SetEditMode(uint32_t editMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, EditMode, editMode);
}

void ListItemModelNG::SetSelectable(bool selectable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectable(selectable);
}

void ListItemModelNG::SetSelected(bool selected)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(selected);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, selected);
}

void ListItemModelNG::SetSelectChangeEvent(std::function<void(bool)>&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectChangeEvent(std::move(changeEvent));
}

void ListItemModelNG::SetSelectCallback(OnSelectFunc&& selectCallback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(selectCallback));
}

void ListItemModelNG::SetAutoScale(bool autoScale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ListItemModelNG::SetAutoScale(frameNode, autoScale);
}

void ListItemModelNG::SetDeleteArea(std::function<void()>&& builderAction, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea, NG::FrameNode* node)
{
    if (!node) {
        node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = node->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (isStartArea) {
        RefPtr<NG::UINode> startNode;
        if (builderAction) {
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderAction();
            startNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        pattern->SetStartNode(startNode);
        InstallSwiperCallBack(eventHub, std::move(onDelete), std::move(onEnterDeleteArea), std::move(onExitDeleteArea),
            std::move(onStateChange), isStartArea);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, length);
    } else {
        RefPtr<NG::UINode> endNode;
        if (builderAction) {
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderAction();
            endNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        pattern->SetEndNode(endNode);
        InstallSwiperCallBack(eventHub, std::move(onDelete), std::move(onEnterDeleteArea), std::move(onExitDeleteArea),
            std::move(onStateChange), isStartArea);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, length);
    }
}

void ListItemModelNG::InstallSwiperCallBack(RefPtr<ListItemEventHub> eventHub, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, bool isStartArea)
{
    CHECK_NULL_VOID(eventHub);
    if (isStartArea) {
        eventHub->SetStartOnDelete(std::move(onDelete));
        eventHub->SetOnEnterStartDeleteArea(std::move(onEnterDeleteArea));
        eventHub->SetOnExitStartDeleteArea(std::move(onExitDeleteArea));
        eventHub->SetStartOnStateChange(std::move(onStateChange));
    } else {
        eventHub->SetEndOnDelete(std::move(onDelete));
        eventHub->SetOnEnterEndDeleteArea(std::move(onEnterDeleteArea));
        eventHub->SetOnExitEndDeleteArea(std::move(onExitDeleteArea));
        eventHub->SetEndOnStateChange(std::move(onStateChange));
    }
}

void ListItemModelNG::SetSelected(FrameNode* frameNode, bool selected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(selected);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, selected);
}

void ListItemModelNG::SetSelectable(FrameNode* frameNode, bool selectable)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectable(selectable);
}

void ListItemModelNG::SetDeleteArea(FrameNode* frameNode, FrameNode* buildNode, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (isStartArea) {
        const auto startNode = AceType::Claim<UINode>(buildNode);
        pattern->SetStartNode(startNode);

        eventHub->SetStartOnDelete(std::move(onDelete));
        eventHub->SetOnEnterStartDeleteArea(std::move(onEnterDeleteArea));
        eventHub->SetOnExitStartDeleteArea(std::move(onExitDeleteArea));
        eventHub->SetStartOnStateChange(std::move(onStateChange));
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, length, frameNode);
    } else {
        const auto endNode = AceType::Claim<UINode>(buildNode);
        pattern->SetEndNode(endNode);

        eventHub->SetEndOnDelete(std::move(onDelete));
        eventHub->SetOnEnterEndDeleteArea(std::move(onEnterDeleteArea));
        eventHub->SetOnExitEndDeleteArea(std::move(onExitDeleteArea));
        eventHub->SetEndOnStateChange(std::move(onStateChange));
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, length, frameNode);
    }
}

void ListItemModelNG::SetSwiperAction(FrameNode* frameNode, std::function<void()>&& startAction,
    std::function<void()>&& endAction, OnOffsetChangeFunc&& onOffsetChangeFunc, V2::SwipeEdgeEffect edgeEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOffsetChangeCallBack(std::move(onOffsetChangeFunc));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EdgeEffect, edgeEffect, frameNode);
}

void ListItemModelNG::SetSelectCallback(FrameNode* frameNode, OnSelectFunc&& selectCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(selectCallback));
}

void ListItemModelNG::SetDeleteAreaWithFrameNode(const RefPtr<NG::UINode>& builderComponent, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea, NG::FrameNode* node)
{
    if (!node) {
        node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = node->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (isStartArea) {
        pattern->SetStartNode(builderComponent);
        InstallSwiperCallBack(eventHub, std::move(onDelete), std::move(onEnterDeleteArea), std::move(onExitDeleteArea),
            std::move(onStateChange), isStartArea);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, length);
    } else {
        pattern->SetEndNode(builderComponent);
        InstallSwiperCallBack(eventHub, std::move(onDelete), std::move(onEnterDeleteArea), std::move(onExitDeleteArea),
            std::move(onStateChange), isStartArea);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, length);
    }
}

void ListItemModelNG::SetAutoScale(FrameNode* frameNode, bool autoScale)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ArcListItemLayoutProperty, AutoScale, autoScale, frameNode);
}

void ListItemModelNG::SetStyle(FrameNode* frameNode, V2::ListItemStyle style)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetListItemStyle(style);
}

void ListItemModelNG::ParseResObjStartArea(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItem.StartDeleteAreaDistance");
    CHECK_NULL_VOID(resObj);
        auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
            CalcDimension result;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                return;
            }
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, result, frameNode);
        };
        pattern->AddResObj("listItem.StartDeleteAreaDistance", resObj, std::move(updateFunc));
}

void ListItemModelNG::ParseResObjEndArea(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("listItem.EndDeleteAreaDistance");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [frameNode](const RefPtr<ResourceObject>& resObj) {
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
            return;
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, result, frameNode);
    };
    pattern->AddResObj("listItem.EndDeleteAreaDistance", resObj, std::move(updateFunc));
}
} // namespace OHOS::Ace::NG
