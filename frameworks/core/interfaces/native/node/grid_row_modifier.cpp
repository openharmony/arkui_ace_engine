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
#include "core/interfaces/native/node/grid_row_modifier.h"

#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
constexpr int X_XS = 0;
constexpr int X_SM = 1;
constexpr int X_MD = 2;
constexpr int X_LG = 3;
constexpr int X_XL = 4;
constexpr int X_XXL = 5;
constexpr int Y_XS = 6;
constexpr int Y_SM = 7;
constexpr int Y_MD = 8;
constexpr int Y_LG = 9;
constexpr int Y_XL = 10;
constexpr int Y_XXL = 11;
void SetAlignItems(ArkUINodeHandle node, int32_t alignItems)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexAlign alignItemsValue = static_cast<FlexAlign>(alignItems);
    GridRowModelNG::SetAlignItems(frameNode, alignItemsValue);
}

void ResetAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexAlign resetValue = FlexAlign::FLEX_START;
    GridRowModelNG::SetAlignItems(frameNode, resetValue);
}

void InheritGridRowGutterOption(const RefPtr<V2::Gutter>& gutter,
    int32_t *gutterSizeArray)
{
    gutter->xXs = Dimension(gutterSizeArray[X_XS], DimensionUnit::VP);
    gutter->xSm = Dimension(gutterSizeArray[X_SM], DimensionUnit::VP);
    gutter->xMd = Dimension(gutterSizeArray[X_MD], DimensionUnit::VP);
    gutter->xLg = Dimension(gutterSizeArray[X_LG], DimensionUnit::VP);
    gutter->xXl = Dimension(gutterSizeArray[X_XL], DimensionUnit::VP);
    gutter->xXXl = Dimension(gutterSizeArray[X_XXL], DimensionUnit::VP);
    gutter->yXs = Dimension(gutterSizeArray[Y_XS], DimensionUnit::VP);
    gutter->ySm = Dimension(gutterSizeArray[Y_SM], DimensionUnit::VP);
    gutter->yMd = Dimension(gutterSizeArray[Y_MD], DimensionUnit::VP);
    gutter->yLg = Dimension(gutterSizeArray[Y_LG], DimensionUnit::VP);
    gutter->yXl = Dimension(gutterSizeArray[Y_XL], DimensionUnit::VP);
    gutter->yXXl = Dimension(gutterSizeArray[Y_XXL], DimensionUnit::VP);
}

void InheritGridRowOption(const RefPtr<OHOS::Ace::V2::GridContainerSize> &gridContainerSize,
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
    gridContainerSize->xs = containerSizeArray[XS];
    gridContainerSize->sm = containerSizeArray[SM];
    gridContainerSize->md = containerSizeArray[MD];
    gridContainerSize->lg = containerSizeArray[LG];
    gridContainerSize->xl = containerSizeArray[XL];
    gridContainerSize->xxl = containerSizeArray[XXL];
}

void SetDirection(ArkUINodeHandle node, int32_t direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto parsedDirection = static_cast<V2::GridRowDirection>(direction);
    GridRowModelNG::SetDirection(frameNode, parsedDirection);
}

void ResetDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = V2::GridRowDirection::Row;
    GridRowModelNG::SetDirection(frameNode, direction);
}

void SetBreakpoints(ArkUINodeHandle node, int32_t reference, const ArkUI_Float32* pointValues,
    const char* pointStr[], int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto parsedBreakpoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    parsedBreakpoints->reference = static_cast<V2::BreakPointsReference>(reference);
    parsedBreakpoints->breakpoints.clear();
    if (size > 0) {
        double width = -1.0;
        for (int32_t i = 0; i < size; i++) {
            CalcDimension valueDimension = Dimension(pointValues[i], DimensionUnit::VP);
            if (GreatNotEqual(width, valueDimension.Value())) {
                break;
            }
            width = valueDimension.Value();
            parsedBreakpoints->breakpoints.push_back(pointStr[i]);
        }
    }
    GridRowModelNG::SetBreakpoints(frameNode, parsedBreakpoints);
}

void ResetBreakpoints(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto parsedBreakpoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    GridRowModelNG::SetBreakpoints(frameNode, parsedBreakpoints);
}

void SetColumns(ArkUINodeHandle node, int32_t *containerSizeArray, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto parsedColumns = Referenced::MakeRefPtr<V2::GridContainerSize>(12);
    InheritGridRowOption(parsedColumns, containerSizeArray, size, 0);
    GridRowModelNG::SetColumns(frameNode, parsedColumns);
}

void ResetColumns(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto parsedColumns = Referenced::MakeRefPtr<V2::GridContainerSize>(12);
    GridRowModelNG::SetColumns(frameNode, parsedColumns);
}

void SetGutter(ArkUINodeHandle node, int32_t *containerSizeArray, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto parsedGutter = Referenced::MakeRefPtr<V2::Gutter>();
    InheritGridRowGutterOption(parsedGutter, containerSizeArray);
    GridRowModelNG::SetGutter(frameNode, parsedGutter);
}

void ResetGutter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto parsedGutter = Referenced::MakeRefPtr<V2::Gutter>();
    GridRowModelNG::SetGutter(frameNode, parsedGutter);
}

void SetOnBreakpointChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onBreakpointChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GridRowModelNG::SetOnBreakPointChange(frameNode, std::move(*onBreakpointChange));
    } else {
        GridRowModelNG::SetOnBreakPointChange(frameNode, nullptr);
    }
}

void ResetOnBreakpointChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridRowModelNG::SetOnBreakPointChange(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUIGridRowModifier* GetGridRowModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGridRowModifier modifier = {
        .setAlignItems = SetAlignItems,
        .resetAlignItems = ResetAlignItems,
        .setDirection = SetDirection,
        .resetDirection = ResetDirection,
        .setBreakpoints = SetBreakpoints,
        .resetBreakpoints = ResetBreakpoints,
        .setColumns = SetColumns,
        .resetColumns = ResetColumns,
        .setGutter = SetGutter,
        .resetGutter = ResetGutter,
        .setOnBreakpointChange = SetOnBreakpointChange,
        .resetOnBreakpointChange = ResetOnBreakpointChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIGridRowModifier* GetCJUIGridRowModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGridRowModifier modifier = {
        .setAlignItems = SetAlignItems,
        .resetAlignItems = ResetAlignItems,
        .setDirection = SetDirection,
        .resetDirection = ResetDirection,
        .setBreakpoints = SetBreakpoints,
        .resetBreakpoints = ResetBreakpoints,
        .setColumns = SetColumns,
        .resetColumns = ResetColumns,
        .setGutter = SetGutter,
        .resetGutter = ResetGutter,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
