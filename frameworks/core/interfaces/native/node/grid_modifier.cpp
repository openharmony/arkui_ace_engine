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
#include "grid_modifier.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"

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
constexpr Dimension DEFAULT_FADING_EDGE_LENGTH = Dimension(32.0f, DimensionUnit::VP); // default value
const float ERROR_FLOAT_CODE = -1.0f;
std::string g_strValue;

void SetGridColumnsTemplate(ArkUINodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetGridColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}
void SetGridRowsTemplate(ArkUINodeHandle node, const char* rowsTemplate)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, std::string(rowsTemplate));
}

void ResetGridRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, DEFAULT_ROWS_TEMPLATE);
}
void SetGridColumnsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(columnsGap->unit);
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

void ResetGridColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsGap(frameNode, DEFAULT_COLUMNS_GAP);
}

void SetGridRowsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(rowsGap->unit);
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

void ResetGridRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsGap(frameNode, DEFAULT_ROWS_GAP);
}

void SetGridScrollBar(ArkUINodeHandle node, int32_t scrollBar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DisplayMode mode = static_cast<DisplayMode>(scrollBar);
    GridModelNG::SetScrollBarMode(frameNode, mode);
}

void ResetGridScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarMode(frameNode, DEFAULT_SCROLL_BAR);
}

void SetGridScrollBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension scrollBarWidth = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    GridModelNG::SetScrollBarWidth(frameNode, scrollBarWidth);
}

void ResetGridScrollBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarWidth(frameNode, DEFAULT_SCROLL_BAR_WIDTH);
}

void SetGridScrollBarColor(ArkUINodeHandle node, uint32_t scrollBarColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarColor(frameNode, Color(scrollBarColor));
}

void ResetGridScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    GridModelNG::SetScrollBarColor(frameNode, scrollBarTheme->GetForegroundColor());
}

void SetGridCachedCount(ArkUINodeHandle node, int32_t cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetGridCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
}

void SetGridEditMode(ArkUINodeHandle node, ArkUI_Bool editMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, editMode);
}

void ResetGridEditMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, DEFAULT_EDIT_MODE);
}

void SetGridMultiSelectable(ArkUINodeHandle node, ArkUI_Bool multiSelectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, multiSelectable);
}

void ResetGridMultiSelectable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, DEFAULT_MULTI_SELECTABLE);
}

void SetGridMaxCount(ArkUINodeHandle node, int32_t maxCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, maxCount);
}

void ResetGridMaxCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, DEFAULT_MAX_COUNT);
}

void SetGridMinCount(ArkUINodeHandle node, int32_t minCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, minCount);
}

void ResetGridMinCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, DEFAULT_MIN_COUNT);
}

void SetGridCellLength(ArkUINodeHandle node, int32_t cellLength)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, cellLength);
}

void ResetGridCellLength(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, DEFAULT_CELL_LENGTH);
}

void SetGridLayoutDirection(ArkUINodeHandle node, int32_t layoutDirection)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexDirection direction = static_cast<FlexDirection>(layoutDirection);
    GridModelNG::SetLayoutDirection(frameNode, direction);
}

void ResetGridLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutDirection(frameNode, DEFAULT_LAYOUT_DIRECTION);
}

void SetGridSupportAnimation(ArkUINodeHandle node, ArkUI_Bool supportAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, supportAnimation);
}

void ResetGridSupportAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, DEFAULT_SUPPORT_ANIMATION);
}

void SetEdgeEffect(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    ArkUI_Bool alwaysEnabled = false;
    GridModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

void SetNestedScroll(ArkUINodeHandle node, int32_t forward, int32_t backward)
{
    NestedScrollOptions opt = {
        .forward = static_cast<NestedScrollMode>(forward),
        .backward = static_cast<NestedScrollMode>(backward),
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetNestedScroll(frameNode, opt);
}

void ResetNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    GridModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetEnableScroll(ArkUINodeHandle node, ArkUI_Bool ScrollEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, ScrollEnabled);
}

void ResetEnableScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Bool scrollEnabled = true;
    GridModelNG::SetScrollEnabled(frameNode, scrollEnabled);
}

void SetFriction(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetFriction(frameNode, friction);
}

void ResetFriction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 friction = -1.0;
    GridModelNG::SetFriction(frameNode, friction);
}

void SetFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 flingSpeedLimit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, flingSpeedLimit);
}

void ResetFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 flingSpeedLimit = -1.0;
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, flingSpeedLimit);
}

void SetGridAlignItems(ArkUINodeHandle node, int32_t alignItems)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode, static_cast<GridItemAlignment>(alignItems));
}

void ResetGridAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode, GridItemAlignment::DEFAULT);
}

ArkUI_CharPtr GetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = GridModelNG::GetColumnsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = GridModelNG::GetRowsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_Float32 GetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return GridModelNG::GetColumnsGap(frameNode);
}

ArkUI_Float32 GetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return GridModelNG::GetRowsGap(frameNode);
}

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto totalChildCount = frameNode->TotalChildCount();
    if (totalChildCount > 0) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_CHILD_NODE_EXIST;
    }
    NodeAdapter::GetNodeAdapterAPI()->attachHostNode(handle, node);
    return ERROR_CODE_NO_ERROR;
}

void ResetNodeAdapter(ArkUINodeHandle node)
{
    NodeAdapter::GetNodeAdapterAPI()->detachHostNode(node);
}

ArkUINodeAdapterHandle GetNodeAdapter(ArkUINodeHandle node)
{
    return NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(node);
}

void SetCachedCount(ArkUINodeHandle node, ArkUI_Int32 cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, 1);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return GridModelNG::GetCachedCount(frameNode);
}

void SetGridFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    NG::ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetGridFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}

namespace NodeModifier {
const ArkUIGridModifier* GetGridModifier()
{
    static const ArkUIGridModifier modifier = { SetGridColumnsTemplate, ResetGridColumnsTemplate, SetGridRowsTemplate,
        ResetGridRowsTemplate, SetGridColumnsGap, ResetGridColumnsGap, SetGridRowsGap, ResetGridRowsGap,
        SetGridScrollBar, ResetGridScrollBar, SetGridScrollBarWidth, ResetGridScrollBarWidth, SetGridScrollBarColor,
        ResetGridScrollBarColor, SetGridCachedCount, ResetGridCachedCount, SetGridEditMode, ResetGridEditMode,
        SetGridMultiSelectable, ResetGridMultiSelectable, SetGridMaxCount, ResetGridMaxCount, SetGridMinCount,
        ResetGridMinCount, SetGridCellLength, ResetGridCellLength, SetGridLayoutDirection, ResetGridLayoutDirection,
        SetGridSupportAnimation, ResetGridSupportAnimation, SetEdgeEffect, ResetEdgeEffect, SetNestedScroll,
        ResetNestedScroll, SetEnableScroll, ResetEnableScroll, SetFriction, ResetFriction, GetColumnsTemplate,
        GetRowsTemplate, GetColumnsGap, GetRowsGap, SetNodeAdapter, ResetNodeAdapter, GetNodeAdapter, SetCachedCount,
        ResetCachedCount, GetCachedCount, SetFlingSpeedLimit, ResetFlingSpeedLimit, SetGridAlignItems,
        ResetGridAlignItems, SetGridFadingEdge, ResetGridFadingEdge };
    return &modifier;
}

const CJUIGridModifier* GetCJUIGridModifier()
{
    static const CJUIGridModifier modifier = {
        SetGridColumnsTemplate, ResetGridColumnsTemplate, SetGridRowsTemplate, ResetGridRowsTemplate,
        SetGridColumnsGap, ResetGridColumnsGap, SetGridRowsGap, ResetGridRowsGap,
        SetGridScrollBar, ResetGridScrollBar, SetGridScrollBarWidth, ResetGridScrollBarWidth, SetGridScrollBarColor,
        ResetGridScrollBarColor, SetGridCachedCount, ResetGridCachedCount, SetGridEditMode, ResetGridEditMode,
        SetGridMultiSelectable, ResetGridMultiSelectable, SetGridMaxCount, ResetGridMaxCount, SetGridMinCount,
        ResetGridMinCount, SetGridCellLength, ResetGridCellLength, SetGridLayoutDirection, ResetGridLayoutDirection,
        SetGridSupportAnimation, ResetGridSupportAnimation, SetEdgeEffect, ResetEdgeEffect, SetNestedScroll,
        ResetNestedScroll, SetEnableScroll, ResetEnableScroll, SetFriction, ResetFriction, GetColumnsTemplate,
        GetRowsTemplate, GetColumnsGap, GetRowsGap, SetNodeAdapter, ResetNodeAdapter, GetNodeAdapter, SetCachedCount,
        ResetCachedCount, GetCachedCount, SetFlingSpeedLimit, ResetFlingSpeedLimit };
    return &modifier;
}

void SetOnGridScrollIndex(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t first, int32_t last) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_SCROLL_TO_INDEX;
        event.componentAsyncEvent.data[0].i32 = first;
        event.componentAsyncEvent.data[1].i32 = last;
        SendArkUIAsyncEvent(&event);
    };
    GridModelNG::SetOnScrollIndex(frameNode, std::move(onEvent));
}

void ResetOnGridScrollIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollIndex(frameNode, nullptr);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG