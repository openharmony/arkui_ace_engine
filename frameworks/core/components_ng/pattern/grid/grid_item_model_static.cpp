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

#include "core/components_ng/pattern/grid/grid_item_model_static.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
 
namespace OHOS::Ace::NG {
RefPtr<FrameNode> GridItemModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = ScrollableItemPool::GetInstance().Allocate(V2::GRID_ITEM_ETS_TAG, nodeId,
        [itemStyle = GridItemStyle::NONE]() { return AceType::MakeRefPtr<GridItemPattern>(nullptr, itemStyle); });

    return frameNode;
}

void GridItemModelStatic::SetForceRebuild(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetForceRebuild(value);
}

void GridItemModelStatic::SetSelectable(FrameNode* frameNode, bool selectable)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectable(selectable);
}

void GridItemModelStatic::SetSelected(FrameNode* frameNode, bool selected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(selected);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, selected);
}

void GridItemModelStatic::SetRowStart(FrameNode* frameNode, int32_t rowStart)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridItemLayoutProperty, RowStart, rowStart, frameNode);
}

void GridItemModelStatic::SetRowEnd(FrameNode* frameNode, int32_t rowEnd)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridItemLayoutProperty, RowEnd, rowEnd, frameNode);
}

void GridItemModelStatic::SetColumnStart(FrameNode* frameNode, int32_t columnStart)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridItemLayoutProperty, ColumnStart, columnStart, frameNode);
}

void GridItemModelStatic::SetColumnEnd(FrameNode* frameNode, int32_t columnEnd)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridItemLayoutProperty, ColumnEnd, columnEnd, frameNode);
}

void GridItemModelStatic::SetGridItemStyle(FrameNode* frameNode, GridItemStyle gridItemStyle)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPatternPtr<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateGridItemStyle(gridItemStyle);
}

void GridItemModelStatic::SetOnSelect(FrameNode* frameNode, SelectFunc&& onSelect)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(onSelect));
}

void GridItemModelStatic::SetSelectChangeEvent(FrameNode* frameNode, SelectFunc&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectChangeEvent(std::move(changeEvent));
}
} // namespace OHOS::Ace::NG