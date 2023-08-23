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

#include "core/components_ng/pattern/list/list_item_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ListItemModelNG::Create(std::function<void(int32_t)>&& deepRenderFunc, V2::ListItemStyle listItemStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        ScopedViewStackProcessor scopedViewStackProcessor;
        deepRenderFunc(nodeId);
        return ViewStackProcessor::GetInstance()->Finish();
    };
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender)), itemStyle = listItemStyle]() {
            return AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, itemStyle);
        });
    stack->Push(frameNode);
}

void ListItemModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });
    stack->Push(frameNode);
}

void ListItemModelNG::SetSwiperAction(
    std::function<void()>&& startAction, std::function<void()>&& endAction, V2::SwipeEdgeEffect edgeEffect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<NG::UINode> startNode;
    if (startAction) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        startAction();
        startNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    if (startNode) {
        pattern->SetStartNode(startNode);
    }
    RefPtr<NG::UINode> endNode;
    if (endAction) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        endAction();
        endNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    if (endNode) {
        pattern->SetEndNode(endNode);
    }

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
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, selected);
}

void ListItemModelNG::SetSelectChangeEvent(std::function<void(bool)>&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectChangeEvent(std::move(changeEvent));
}

void ListItemModelNG::SetSelectCallback(OnSelectFunc&& selectCallback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(selectCallback));
}

void ListItemModelNG::SetDeleteArea(std::function<void()>&& builderAction, bool useDefaultDeleteAnimation,
    OnDeleteEvent&& onDelete, OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    const Dimension& length, bool isStartArea)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (isStartArea) {
        RefPtr<NG::UINode> startNode;
        if (builderAction) {
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderAction();
            startNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        if (startNode) {
            pattern->SetStartNode(startNode);
        }
        if (onDelete) {
            eventHub->SetStartOnDelete(std::move(onDelete));
        }
        if (onEnterDeleteArea) {
            eventHub->SetOnEnterStartDeleteArea(std::move(onEnterDeleteArea));
        }
        if (onExitDeleteArea) {
            eventHub->SetOnExitStartDeleteArea(std::move(onExitDeleteArea));
        }
        pattern->SetUseStartDefaultDeleteAnimation(useDefaultDeleteAnimation);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, StartDeleteAreaDistance, length);
    } else {
        RefPtr<NG::UINode> endNode;
        if (builderAction) {
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderAction();
            endNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        if (endNode) {
            pattern->SetEndNode(endNode);
        }
        if (onDelete) {
            eventHub->SetEndOnDelete(std::move(onDelete));
        }
        if (onEnterDeleteArea) {
            eventHub->SetOnEnterEndDeleteArea(std::move(onEnterDeleteArea));
        }
        if (onExitDeleteArea) {
            eventHub->SetOnExitEndDeleteArea(std::move(onExitDeleteArea));
        }
        pattern->SetUseEndDefaultDeleteAnimation(useDefaultDeleteAnimation);
        ACE_UPDATE_LAYOUT_PROPERTY(ListItemLayoutProperty, EndDeleteAreaDistance, length);
    }
}
} // namespace OHOS::Ace::NG
