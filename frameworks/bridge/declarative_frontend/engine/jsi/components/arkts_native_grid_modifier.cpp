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
#include "./arkts_native_grid_modifier.h"

#include <unordered_map>

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::NG {
const std::string DEFAULT_ROWS_TEMPLATE = "1fr";
const std::string DEFAULT_COLUMNS_TEMPLATE = "1fr";
constexpr Dimension DEFAULT_COLUMNS_GAP = 0.0_fp;
constexpr Dimension DEFAULT_ROWS_GAP = 0.0_fp;
constexpr DisplayMode DEFAULT_SCROLL_BAR = DisplayMode::AUTO;
constexpr Dimension DEFAULT_SCROLL_BAR_WIDTH = 4.0_vp;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr bool DEFAULT_EDIT_MODE = false;
constexpr FlexDirection DEFAULT_LAYOUT_DIRECTION = FlexDirection::ROW;
constexpr int32_t DEFAULT_MAX_COUNT = Infinity<int32_t>();
constexpr int32_t DEFAULT_MIN_COUNT = 1;
constexpr int32_t DEFAULT_CELL_LENGTH = 0;
constexpr bool DEFAULT_MULTI_SELECTABLE = false;
constexpr bool DEFAULT_SUPPORT_ANIMATION = false;

void SetGridColumnsTemplate(NodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetGridColumnsTemplate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}
void SetGridRowsTemplate(NodeHandle node, const char* rowsTemplate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, std::string(rowsTemplate));
}

void ResetGridRowsTemplate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, DEFAULT_ROWS_TEMPLATE);
}
void SetGridColumnsGap(NodeHandle node, const struct ArkUIResourceLength* columnsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(columnsGap->Uint);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(columnsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(columnsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    GridModelNG::SetColumnsGap(frameNode, gap);
}

void ResetGridColumnsGap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsGap(frameNode, DEFAULT_COLUMNS_GAP);
}

void SetGridRowsGap(NodeHandle node, const struct ArkUIResourceLength* rowsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(rowsGap->Uint);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(rowsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(rowsGap->value, unitEnum);
    }
    if (LessOrEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    GridModelNG::SetRowsGap(frameNode, gap);
}

void ResetGridRowsGap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsGap(frameNode, DEFAULT_ROWS_GAP);
}

void SetGridScrollBar(NodeHandle node, int32_t scrollBar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DisplayMode mode = static_cast<DisplayMode>(scrollBar);
    GridModelNG::SetScrollBarMode(frameNode, mode);
}

void ResetGridScrollBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarMode(frameNode, DEFAULT_SCROLL_BAR);
}

void SetGridScrollBarWidth(NodeHandle node, const struct ArkUIDimensionType* scrollBarWidthType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension scrollBarWidth =
        Dimension(scrollBarWidthType->value, static_cast<OHOS::Ace::DimensionUnit>(scrollBarWidthType->units));
    GridModelNG::SetScrollBarWidth(frameNode, scrollBarWidth);
}

void ResetGridScrollBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarWidth(frameNode, DEFAULT_SCROLL_BAR_WIDTH);
}

void SetGridScrollBarColor(NodeHandle node, uint32_t scrollBarColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarColor(frameNode, Color(scrollBarColor));
}

void ResetGridScrollBarColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    GridModelNG::SetScrollBarColor(frameNode, scrollBarTheme->GetForegroundColor());
}

void SetGridCachedCount(NodeHandle node, int32_t cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetGridCachedCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
}

void SetGridEditMode(NodeHandle node, bool editMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, editMode);
}

void ResetGridEditMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, DEFAULT_EDIT_MODE);
}

void SetGridMultiSelectable(NodeHandle node, bool multiSelectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, multiSelectable);
}

void ResetGridMultiSelectable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, DEFAULT_MULTI_SELECTABLE);
}

void SetGridMaxCount(NodeHandle node, int32_t maxCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, maxCount);
}

void ResetGridMaxCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, DEFAULT_MAX_COUNT);
}

void SetGridMinCount(NodeHandle node, int32_t minCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, minCount);
}

void ResetGridMinCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, DEFAULT_MIN_COUNT);
}

void SetGridCellLength(NodeHandle node, int32_t cellLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, cellLength);
}

void ResetGridCellLength(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, DEFAULT_CELL_LENGTH);
}

void SetGridLayoutDirection(NodeHandle node, int32_t layoutDirection)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexDirection direction = static_cast<FlexDirection>(layoutDirection);
    GridModelNG::SetLayoutDirection(frameNode, direction);
}

void ResetGridLayoutDirection(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutDirection(frameNode, DEFAULT_LAYOUT_DIRECTION);
}

void SetGridSupportAnimation(NodeHandle node, bool supportAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, supportAnimation);
}

void ResetGridSupportAnimation(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, DEFAULT_SUPPORT_ANIMATION);
}

void SetEdgeEffect(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void ResetEdgeEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    bool alwaysEnabled = false;
    GridModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

void SetNestedScroll(NodeHandle node, int32_t forward, int32_t backward)
{
    NestedScrollOptions opt = {
        .forward = static_cast<NestedScrollMode>(forward),
        .backward = static_cast<NestedScrollMode>(backward),
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetNestedScroll(frameNode, opt);
}

void ResetNestedScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    GridModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetEnableScroll(NodeHandle node, bool ScrollEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, ScrollEnabled);
}

void ResetEnableScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool scrollEnabled = true;
    GridModelNG::SetScrollEnabled(frameNode, scrollEnabled);
}

void SetFriction(NodeHandle node, double friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetFriction(frameNode, friction);
}

void ResetFriction(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    double friction = -1.0;
    GridModelNG::SetFriction(frameNode, friction);
}

ArkUIGridModifierAPI GetGridModifier()
{
    static const ArkUIGridModifierAPI modifier = { SetGridColumnsTemplate, ResetGridColumnsTemplate,
        SetGridRowsTemplate, ResetGridRowsTemplate, SetGridColumnsGap, ResetGridColumnsGap, SetGridRowsGap,
        ResetGridRowsGap, SetGridScrollBar, ResetGridScrollBar, SetGridScrollBarWidth, ResetGridScrollBarWidth,
        SetGridScrollBarColor, ResetGridScrollBarColor, SetGridCachedCount, ResetGridCachedCount, SetGridEditMode,
        ResetGridEditMode, SetGridMultiSelectable, ResetGridMultiSelectable, SetGridMaxCount, ResetGridMaxCount,
        SetGridMinCount, ResetGridMinCount, SetGridCellLength, ResetGridCellLength, SetGridLayoutDirection,
        ResetGridLayoutDirection, SetGridSupportAnimation, ResetGridSupportAnimation, SetEdgeEffect, ResetEdgeEffect,
        SetNestedScroll, ResetNestedScroll, SetEnableScroll, ResetEnableScroll, SetFriction, ResetFriction };

    return modifier;
}
} // namespace OHOS::Ace::NG