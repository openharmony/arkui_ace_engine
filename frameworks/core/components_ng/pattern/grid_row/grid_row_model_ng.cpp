/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
    RefPtr<V2::GridContainerSize> col;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        col = Referenced::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
    } else {
        col = Referenced::MakeRefPtr<V2::GridContainerSize>();
    }
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
    auto gridRowpattern = frameNode->GetPattern<GridRowLayoutPattern>();
    CHECK_NULL_VOID(gridRowpattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [gutter, weak = AceType::WeakClaim(
        AceType::RawPtr(frameNode))](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        RefPtr<V2::Gutter> &value = const_cast<RefPtr<V2::Gutter> &>(gutter);
        value->ReloadResources(value);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *value, frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    gridRowpattern->AddResObj("gridrow.gutter", resObj, std::move(updateFunc));
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
    auto eventHub = frameNode->GetOrCreateEventHub<GridRowEventHub>();
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

void GridRowModelNG::SetAlignItems(FrameNode* frameNode, const std::optional<FlexAlign>& alignItem)
{
    CHECK_NULL_VOID(frameNode);
    if (alignItem.has_value()) {
        auto layoutProperty = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignItems(alignItem.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, frameNode);
    }
}

void GridRowModelNG::SetGutter(FrameNode* frameNode, const RefPtr<V2::Gutter>& gutter)
{
    CHECK_NULL_VOID(frameNode);
    if (gutter) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *gutter, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, frameNode);
    }
}

void GridRowModelNG::SetColumns(FrameNode* frameNode, const RefPtr<V2::GridContainerSize>& col)
{
    CHECK_NULL_VOID(frameNode);
    if (col) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, *col, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, frameNode);
    }
}

void GridRowModelNG::SetBreakpoints(FrameNode* frameNode, const RefPtr<V2::BreakPoints>& breakpoints)
{
    CHECK_NULL_VOID(frameNode);
    if (breakpoints) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, *breakpoints, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, frameNode);
    }
}

void GridRowModelNG::SetDirection(FrameNode* frameNode, const std::optional<V2::GridRowDirection>& direction)
{
    CHECK_NULL_VOID(frameNode);
    if (direction.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, direction.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, frameNode);
    }
}

void GridRowModelNG::SetOnBreakPointChange(FrameNode* frameNode,
    std::function<void(const std::string)>&& onBreakPointChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridRowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBreakpointChange(std::move(onBreakPointChange));
}
} // namespace OHOS::Ace::NG