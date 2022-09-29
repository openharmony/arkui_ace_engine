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

#include "core/components_ng/pattern/grid/grid_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void GridView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });
    stack->Push(frameNode);
}

void GridView::SetColumnsTemplate(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, value);
}

void GridView::SetRowsTemplate(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, value);
}

void GridView::SetColumnsGap(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, value);
}

void GridView::SetRowsGap(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, value);
}

void GridView::SetScrollBarMode(DisplayMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarMode, value);
}

void GridView::SetScrollBarColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarColor, value);
}

void GridView::SetScrollBarWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarWidth, value);
}

void GridView::SetCachedCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, value);
}

void GridView::SetEditable(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, Editable, value);
}

void GridView::SetLayoutDirection(FlexDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, LayoutDirection, value);
}

void GridView::SetMaxCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, value);
}

void GridView::SetMinCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, value);
}

void GridView::SetCellLength(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CellLength, value);
}

void GridView::SetMultiSelectable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(value);
}

void GridView::SetSupportAnimation(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportAnimation(value);
}

void GridView::SetOnScrollToIndex(ScrollToIndexFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollToIndex(std::move(value));
}

void GridView::SetOnItemDragStart(ItemDragStartFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragStart(std::move(value));
}

void GridView::SetOnItemDragEnter(ItemDragEnterFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(value));
}

void GridView::SetOnItemDragMove(ItemDragMoveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(value));
}

void GridView::SetOnItemDragLeave(ItemDragLeaveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(value));
}

void GridView::SetOnItemDrop(ItemDropFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(value));
}

} // namespace OHOS::Ace::NG
