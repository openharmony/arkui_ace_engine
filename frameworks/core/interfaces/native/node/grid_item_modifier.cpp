/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/grid_item_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

constexpr int32_t DEFAULT_GRID_ITEM_VALUE = 0;

void SetGridItemSelectable(NodeHandle node, bool selectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, selectable);
}

void ResetGridItemSelectable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, true);
}

void SetGridItemSelected(NodeHandle node, bool selected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, selected);
}

void ResetGridItemSelected(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, false);
}

void SetGridItemRowStart(NodeHandle node, int32_t rowStart)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, rowStart);
}

void ResetGridItemRowStart(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemRowEnd(NodeHandle node, int32_t rowEnd)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, rowEnd);
}

void ResetGridItemRowEnd(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnStart(NodeHandle node, int32_t columnStart)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, columnStart);
}

void ResetGridItemColumnStart(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnEnd(NodeHandle node, int32_t columnEnd)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, columnEnd);
}

void ResetGridItemColumnEnd(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

ArkUIGridItemModifierAPI GetGridItemModifier()
{
    static const ArkUIGridItemModifierAPI modifier = { SetGridItemSelectable, ResetGridItemSelectable,
        SetGridItemSelected, ResetGridItemSelected, SetGridItemRowStart, ResetGridItemRowStart,
        SetGridItemRowEnd, ResetGridItemRowEnd, SetGridItemColumnStart, ResetGridItemColumnStart,
        SetGridItemColumnEnd, ResetGridItemColumnEnd };
    return modifier;
}
} // namespace OHOS::Ace::NG