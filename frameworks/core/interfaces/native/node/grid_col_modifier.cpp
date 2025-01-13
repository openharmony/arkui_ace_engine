/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/node/grid_col_modifier.h"

#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t SIZE_ARRAY = 6;
constexpr int COL_0 = 0;
constexpr int COL_1 = 1;
constexpr int COL_2 = 2;
constexpr int COL_3 = 3;
constexpr int COL_4 = 4;
constexpr int COL_5 = 5;

void InheritGridContainerSize(OHOS::Ace::V2::GridContainerSize &gridContainerSize,
    int32_t *containerSizeArray, int32_t size, int32_t defaultVal)
{
    if (containerSizeArray[0] == -1) {
        containerSizeArray[0] = defaultVal;
    }
    for (int32_t i = 1; i < size; i++) {
        if (containerSizeArray[i] == -1) {
            containerSizeArray[i] = containerSizeArray[i - 1];
        }
    }
    gridContainerSize.xs = containerSizeArray[COL_0];
    gridContainerSize.sm = containerSizeArray[COL_1];
    gridContainerSize.md = containerSizeArray[COL_2];
    gridContainerSize.lg = containerSizeArray[COL_3];
    gridContainerSize.xl = containerSizeArray[COL_4];
    gridContainerSize.xxl = containerSizeArray[COL_5];
}

void SetSpan(ArkUINodeHandle node, int32_t *containerSizeArray, int32_t size)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto span = OHOS::Ace::V2::GridContainerSize(1);
    InheritGridContainerSize(span, containerSizeArray, size, 1);
    GridColModelNG::SetSpan(frameNode, span);
}

void ResetSpan(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto span = OHOS::Ace::V2::GridContainerSize(1);
    int32_t containerSizeArray[SIZE_ARRAY] = {1, 1, 1, 1, 1, 1};
    InheritGridContainerSize(span, containerSizeArray, SIZE_ARRAY, 1);
    GridColModelNG::SetSpan(frameNode, span);
}

void SetGridColOffset(ArkUINodeHandle node, int32_t *containerSizeArray, int32_t size)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto offset = OHOS::Ace::V2::GridContainerSize(0);
    InheritGridContainerSize(offset, containerSizeArray, size, 0);
    GridColModelNG::SetOffset(frameNode, offset);
}

void ResetGridColOffset(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto offset = OHOS::Ace::V2::GridContainerSize(0);
    int32_t containerSizeArray[SIZE_ARRAY] = {0};
    InheritGridContainerSize(offset, containerSizeArray, SIZE_ARRAY, 0);
    GridColModelNG::SetOffset(frameNode, offset);
}

void SetOrder(ArkUINodeHandle node, int32_t *containerSizeArray, int32_t size)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto Order = OHOS::Ace::V2::GridContainerSize(0);
    InheritGridContainerSize(Order, containerSizeArray, size, 0);
    GridColModelNG::SetOrder(frameNode, Order);
}

void ResetOrder(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto Order = OHOS::Ace::V2::GridContainerSize(0);
    int32_t containerSizeArray[SIZE_ARRAY] = {0};
    InheritGridContainerSize(Order, containerSizeArray, SIZE_ARRAY, 0);
    GridColModelNG::SetOrder(frameNode, Order);
}

namespace NodeModifier {
const ArkUIGridColModifier* GetGridColModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIGridColModifier modifier = {
        .setSpan = SetSpan,
        .resetSpan = ResetSpan,
        .setGridColOffset = SetGridColOffset,
        .resetGridColOffset = ResetGridColOffset,
        .setOrder = SetOrder,
        .resetOrder = ResetOrder,
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

const CJUIGridColModifier* GetCJUIGridColModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIGridColModifier modifier = {
        .setSpan = SetSpan,
        .resetSpan = ResetSpan,
        .setGridColOffset = SetGridColOffset,
        .resetGridColOffset = ResetGridColOffset,
        .setOrder = SetOrder,
        .resetOrder = ResetOrder,
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
}
