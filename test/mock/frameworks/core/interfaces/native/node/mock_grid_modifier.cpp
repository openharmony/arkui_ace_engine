/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/interfaces/native/node/grid_item_modifier.h"
#include "core/interfaces/native/node/grid_modifier.h"

namespace OHOS::Ace::NG {
namespace {
void FireOnItemDragEnter(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnItemDragEnter(dragInfo);
}

void FireOnItemDragMove(
    const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnItemDragMove(dragInfo, itemIndex, insertIndex);
}

void FireOnItemDragLeave(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnItemDragLeave(dragInfo, itemIndex);
}

bool FireOnItemDrop(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex,
    int32_t insertIndex, bool isSuccess)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    return eventHub->FireOnItemDrop(dragInfo, itemIndex, insertIndex, isSuccess);
}

int32_t GetInsertPosition(const RefPtr<FrameNode>& frameNode, float x, float y)
{
    CHECK_NULL_RETURN(frameNode, -1);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventHub, -1);
    return eventHub->GetInsertPosition(x, y);
}

bool CheckPositionInGrid(const RefPtr<FrameNode>& frameNode, float x, float y)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    return eventHub->CheckPostionInGrid(x, y);
}

int32_t GetFrameNodeChildSize(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventHub, 0);
    return eventHub->GetFrameNodeChildSize();
}

int32_t GetGridItemIndex(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& gridItem)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_RETURN(eventHub, 0);
    return eventHub->GetGridItemIndex(gridItem);
}

void HandleOnItemDragCancel(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->HandleOnItemDragCancel();
}

void InitDragManager(const RefPtr<FrameNode>& frameNode, RefPtr<ForEachBaseNode> forEach)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(forEach);
}

void DeInitDragManager(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->DeInitDragManager();
}

bool IsSelected(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSelected();
}

bool IsGridItemPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<GridItemPattern>(pattern);
}
} // namespace

namespace NodeModifier {
const ArkUIGridModifier* GetGridModifier()
{
    static const ArkUIGridModifier modifier = {
    };
    return &modifier;
}

const NG::GridCustomModifier* GetGridCustomModifier()
{
    static const NG::GridCustomModifier modifier = {
        .fireOnItemDragEnter = FireOnItemDragEnter,
        .fireOnItemDragMove = FireOnItemDragMove,
        .fireOnItemDragLeave = FireOnItemDragLeave,
        .fireOnItemDrop = FireOnItemDrop,
        .getInsertPosition = GetInsertPosition,
        .checkPositionInGrid = CheckPositionInGrid,
        .getFrameNodeChildSize = GetFrameNodeChildSize,
        .getGridItemIndex = GetGridItemIndex,
        .handleOnItemDragCancel = HandleOnItemDragCancel,
    };
    return &modifier;
}

const NG::GridItemCustomModifier* GetGridItemCustomModifier()
{
    static const NG::GridItemCustomModifier modifier = {
        .initDragManager = InitDragManager,
        .deInitDragManager = DeInitDragManager,
        .isSelected = IsSelected,
        .isGridItemPattern = IsGridItemPattern,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
