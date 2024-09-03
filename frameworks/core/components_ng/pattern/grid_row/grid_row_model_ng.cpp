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

#include "grid_row_model_ng.h"

#include "grid_row_layout_pattern.h"

namespace OHOS::Ace::NG {
void GridRowModelNG::Create()
{
    auto col = Referenced::MakeRefPtr<V2::GridContainerSize>();
    auto gutter = Referenced::MakeRefPtr<V2::Gutter>();
    auto breakpoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    auto direction = V2::GridRowDirection::Row;
    Create(col, gutter, breakpoints, direction);
}

void GridRowModelNG::Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
    const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::GRID_ROW_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ROW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridRowLayoutPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, *col);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *gutter);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, *breakpoints);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, direction);
}

RefPtr<FrameNode> GridRowModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ROW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridRowLayoutPattern>(); });
    return frameNode;
}

void GridRowModelNG::SetOnBreakPointChange(std::function<void(const std::string)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridRowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBreakpointChange(std::move(onChange));
}

void GridRowModelNG::SetAlignItems(FlexAlign alignItem)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutPriority = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutPriority);
    layoutPriority->UpdateAlignItems(alignItem);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem);
}

void GridRowModelNG::SetAlignItems(FrameNode* frameNode, FlexAlign alignItem)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutPriority = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutPriority);
    layoutPriority->UpdateAlignItems(alignItem);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem, frameNode);
}

void GridRowModelNG::SetGutter(FrameNode* frameNode, const RefPtr<V2::Gutter>& gutter)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *gutter, frameNode);
}

void GridRowModelNG::SetColumns(FrameNode* frameNode, const RefPtr<V2::GridContainerSize>& col)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, *col, frameNode);
}

void GridRowModelNG::SetBreakpoints(FrameNode* frameNode, const RefPtr<V2::BreakPoints>& breakpoints)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, *breakpoints, frameNode);
}

void GridRowModelNG::SetDirection(FrameNode* frameNode, V2::GridRowDirection direction)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, direction, frameNode);
}

void GridRowModelNG::SetOnBreakPointChange(FrameNode* frameNode,
    std::function<void(const std::string)>&& onBreakPointChange)
{
    auto eventHub = frameNode->GetEventHub<GridRowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBreakpointChange(std::move(onBreakPointChange));
}
} // namespace OHOS::Ace::NG