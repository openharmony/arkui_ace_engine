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

void ListItemModelNG::Create(std::function<void(int32_t)>&& deepRenderFunc)
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
        V2::LIST_ITEM_ETS_TAG, nodeId, [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<ListItemPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
}

void ListItemModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr); });
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

void ListItemModelNG::SetSelectCallback(OnSelectFunc&& selectCallback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(selectCallback));
}
} // namespace OHOS::Ace::NG
