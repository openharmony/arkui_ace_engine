/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

constexpr int32_t DEFAULT_GRID_ITEM_VALUE = 0;

void SetGridItemSelectable(ArkUINodeHandle node, ArkUI_Bool selectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, selectable);
}

void ResetGridItemSelectable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, true);
}

void SetGridItemSelected(ArkUINodeHandle node, ArkUI_Bool selected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, selected);
}

void ResetGridItemSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, false);
}

void SetGridItemRowStart(ArkUINodeHandle node, int32_t rowStart)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, rowStart);
}

void ResetGridItemRowStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemRowEnd(ArkUINodeHandle node, int32_t rowEnd)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, rowEnd);
}

void ResetGridItemRowEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetRowEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnStart(ArkUINodeHandle node, int32_t columnStart)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, columnStart);
}

void ResetGridItemColumnStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnStart(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemColumnEnd(ArkUINodeHandle node, int32_t columnEnd)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, columnEnd);
}

void ResetGridItemColumnEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetColumnEnd(frameNode, DEFAULT_GRID_ITEM_VALUE);
}

void SetGridItemOptions(ArkUINodeHandle node, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetGridItemStyle(frameNode, static_cast<GridItemStyle>(style));
}

namespace NodeModifier {
const ArkUIGridItemModifier* GetGridItemModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIGridItemModifier modifier = {
        .setGridItemSelectable = SetGridItemSelectable,
        .resetGridItemSelectable = ResetGridItemSelectable,
        .setGridItemSelected = SetGridItemSelected,
        .resetGridItemSelected = ResetGridItemSelected,
        .setGridItemRowStart = SetGridItemRowStart,
        .resetGridItemRowStart = ResetGridItemRowStart,
        .setGridItemRowEnd = SetGridItemRowEnd,
        .resetGridItemRowEnd = ResetGridItemRowEnd,
        .setGridItemColumnStart = SetGridItemColumnStart,
        .resetGridItemColumnStart = ResetGridItemColumnStart,
        .setGridItemColumnEnd = SetGridItemColumnEnd,
        .resetGridItemColumnEnd = ResetGridItemColumnEnd,
        .setGridItemOptions = SetGridItemOptions,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUIGridItemModifier* GetCJUIGridItemModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIGridItemModifier modifier = {
        .setGridItemSelectable = SetGridItemSelectable,
        .resetGridItemSelectable = ResetGridItemSelectable,
        .setGridItemSelected = SetGridItemSelected,
        .resetGridItemSelected = ResetGridItemSelected,
        .setGridItemRowStart = SetGridItemRowStart,
        .resetGridItemRowStart = ResetGridItemRowStart,
        .setGridItemRowEnd = SetGridItemRowEnd,
        .resetGridItemRowEnd = ResetGridItemRowEnd,
        .setGridItemColumnStart = SetGridItemColumnStart,
        .resetGridItemColumnStart = ResetGridItemColumnStart,
        .setGridItemColumnEnd = SetGridItemColumnEnd,
        .resetGridItemColumnEnd = ResetGridItemColumnEnd,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
