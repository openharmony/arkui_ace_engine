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

#include "core/components_ng/pattern/list/list_item_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"

namespace OHOS::Ace::NG {

void ListItemModelStatic::SetSticky(FrameNode* frameNode, const std::optional<V2::StickyMode>& stickyMode)
{
    if (stickyMode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StickyMode, stickyMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StickyMode, frameNode);
    }
}

RefPtr<FrameNode> ListItemModelStatic::CreateFrameNode(int32_t nodeId, bool isCreateArc)
{
    if (isCreateArc) {
        return FrameNode::CreateFrameNode(V2::ARC_LIST_ITEM_ETS_TAG, nodeId,
            AceType::MakeRefPtr<ArcListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    }
    auto frameNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
    return frameNode;
}

void ListItemModelStatic::SetSelectCallback(FrameNode* frameNode, OnSelectFunc&& selectCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(selectCallback));
}

void ListItemModelStatic::SetSelectChangeEvent(FrameNode* frameNode, OnSelectFunc&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectChangeEvent(std::move(changeEvent));
}

void ListItemModelStatic::SetEditMode(FrameNode* frameNode, uint32_t editMode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EditMode, editMode, frameNode);
}

void ListItemModelStatic::SetSelectable(FrameNode* frameNode, bool selectable)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectable(selectable);
}

void ListItemModelStatic::SetStyle(FrameNode* frameNode, const std::optional<V2::ListItemStyle>& style)
{
}

void ListItemModelStatic::SetSelected(FrameNode* frameNode, bool selected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(selected);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, selected);
}

void ListItemModelStatic::SetDeleteArea(FrameNode* frameNode, UINode* buildNode, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const std::optional<Dimension>& length, bool isStartArea)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
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
        if (length) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, length.value(), frameNode);
        } else {
            ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, frameNode);
        }
    } else {
        const auto endNode = AceType::Claim<UINode>(buildNode);
        pattern->SetEndNode(endNode);

        eventHub->SetEndOnDelete(std::move(onDelete));
        eventHub->SetOnEnterEndDeleteArea(std::move(onEnterDeleteArea));
        eventHub->SetOnExitEndDeleteArea(std::move(onExitDeleteArea));
        eventHub->SetEndOnStateChange(std::move(onStateChange));
        if (length) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, length.value(), frameNode);
        } else {
            ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, frameNode);
        }
    }
}

void ListItemModelStatic::SetSwiperAction(FrameNode* frameNode, std::function<void()>&& startAction,
    std::function<void()>&& endAction, OnOffsetChangeFunc&& onOffsetChangeFunc,
    const std::optional<V2::SwipeEdgeEffect>& edgeEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOffsetChangeCallBack(std::move(onOffsetChangeFunc));
    if (edgeEffect.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EdgeEffect, edgeEffect.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ListItemLayoutProperty, EdgeEffect, frameNode);
    }
}
} // namespace OHOS::Ace::NG