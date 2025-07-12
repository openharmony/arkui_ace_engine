/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

void SetEdgeEffect(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEdgeEffect(
        frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    ArkUI_Bool alwaysEnabled = false;
    GridModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, EffectEdge::ALL);
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

void SetGridFocusWrapMode(ArkUINodeHandle node, int32_t focusWrapMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FocusWrapMode mode = static_cast<FocusWrapMode>(focusWrapMode);
    GridModelNG::SetFocusWrapMode(frameNode, mode);
}

void ResetGridFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetFocusWrapMode(frameNode, FocusWrapMode::DEFAULT);
}

ArkUI_Int32 GetGridFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(GridModelNG::GetFocusWrapMode(frameNode));
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

void SetGridSyncLoad(ArkUINodeHandle node, ArkUI_Bool syncLoad)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSyncLoad(frameNode, syncLoad);
}

void ResetGridSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSyncLoad(frameNode, true);
}

ArkUI_Bool GetGridSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return GridModelNG::GetSyncLoad(frameNode);
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

void SetShowCached(ArkUINodeHandle node, ArkUI_Bool show)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetShowCached(frameNode, show);
}

void ResetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetShowCached(frameNode, false);
}

ArkUI_Bool GetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetShowCached(frameNode);
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGridModifier modifier = {
        .setGridColumnsTemplate = SetGridColumnsTemplate,
        .resetGridColumnsTemplate = ResetGridColumnsTemplate,
        .setGridRowsTemplate = SetGridRowsTemplate,
        .resetGridRowsTemplate = ResetGridRowsTemplate,
        .setGridColumnsGap = SetGridColumnsGap,
        .resetGridColumnsGap = ResetGridColumnsGap,
        .setGridRowsGap = SetGridRowsGap,
        .resetGridRowsGap = ResetGridRowsGap,
        .setGridScrollBar = SetGridScrollBar,
        .resetGridScrollBar = ResetGridScrollBar,
        .setGridScrollBarWidth = SetGridScrollBarWidth,
        .resetGridScrollBarWidth = ResetGridScrollBarWidth,
        .setGridScrollBarColor = SetGridScrollBarColor,
        .resetGridScrollBarColor = ResetGridScrollBarColor,
        .setGridCachedCount = SetGridCachedCount,
        .resetGridCachedCount = ResetGridCachedCount,
        .setShowCached = SetShowCached,
        .resetShowCached = ResetShowCached,
        .getShowCached = GetShowCached,
        .setGridEditMode = SetGridEditMode,
        .resetGridEditMode = ResetGridEditMode,
        .setGridMultiSelectable = SetGridMultiSelectable,
        .resetGridMultiSelectable = ResetGridMultiSelectable,
        .setGridMaxCount = SetGridMaxCount,
        .resetGridMaxCount = ResetGridMaxCount,
        .setGridMinCount = SetGridMinCount,
        .resetGridMinCount = ResetGridMinCount,
        .setGridCellLength = SetGridCellLength,
        .resetGridCellLength = ResetGridCellLength,
        .setGridLayoutDirection = SetGridLayoutDirection,
        .resetGridLayoutDirection = ResetGridLayoutDirection,
        .setGridSupportAnimation = SetGridSupportAnimation,
        .resetGridSupportAnimation = ResetGridSupportAnimation,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setNestedScroll = SetNestedScroll,
        .resetNestedScroll = ResetNestedScroll,
        .setEnableScroll = SetEnableScroll,
        .resetEnableScroll = ResetEnableScroll,
        .setFriction = SetFriction,
        .resetFriction = ResetFriction,
        .setGridFocusWrapMode = SetGridFocusWrapMode,
        .resetGridFocusWrapMode = ResetGridFocusWrapMode,
        .getGridFocusWrapMode = GetGridFocusWrapMode,
        .getGridColumnsTemplate = GetColumnsTemplate,
        .getGridRowsTemplate = GetRowsTemplate,
        .getGridColumnsGap = GetColumnsGap,
        .getGridRowsGap = GetRowsGap,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .getCachedCount = GetCachedCount,
        .setGridAlignItems = SetGridAlignItems,
        .resetGridAlignItems = ResetGridAlignItems,
        .setSyncLoad = SetGridSyncLoad,
        .resetSyncLoad = ResetGridSyncLoad,
        .getSyncLoad = GetGridSyncLoad,
        .setGridFadingEdge = SetGridFadingEdge,
        .resetGridFadingEdge = ResetGridFadingEdge,
        .setOnGridScrollIndexCallBack = SetOnGridScrollIndexCallBack,
        .resetOnGridScrollIndex = ResetOnGridScrollIndex,
        .setOnGridScrollBarUpdateCallBack = SetOnGridScrollBarUpdateCallBack,
        .resetOnGridScrollBarUpdate = ResetOnGridScrollBarUpdate,
        .setOnGridItemDragStart = SetOnGridItemDragStart,
        .resetOnGridItemDragStart = ResetOnGridItemDragStart,
        .setOnGridItemDragEnter = SetOnGridItemDragEnter,
        .resetOnGridItemDragEnter = ResetOnGridItemDragEnter,
        .setOnGridItemDragMove = SetOnGridItemDragMove,
        .resetOnGridItemDragMove = ResetOnGridItemDragMove,
        .setOnGridItemDragLeave = SetOnGridItemDragLeave,
        .resetOnGridItemDragLeave = ResetOnGridItemDragLeave,
        .setOnGridItemDrop = SetOnGridItemDrop,
        .resetOnGridItemDrop = ResetOnGridItemDrop,
        .createWithResourceObjFriction = CreateWithResourceObjGridFriction,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIGridModifier* GetCJUIGridModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGridModifier modifier = {
        .setGridColumnsTemplate = SetGridColumnsTemplate,
        .resetGridColumnsTemplate = ResetGridColumnsTemplate,
        .setGridRowsTemplate = SetGridRowsTemplate,
        .resetGridRowsTemplate = ResetGridRowsTemplate,
        .setGridColumnsGap = SetGridColumnsGap,
        .resetGridColumnsGap = ResetGridColumnsGap,
        .setGridRowsGap = SetGridRowsGap,
        .resetGridRowsGap = ResetGridRowsGap,
        .setGridScrollBar = SetGridScrollBar,
        .resetGridScrollBar = ResetGridScrollBar,
        .setGridScrollBarWidth = SetGridScrollBarWidth,
        .resetGridScrollBarWidth = ResetGridScrollBarWidth,
        .setGridScrollBarColor = SetGridScrollBarColor,
        .resetGridScrollBarColor = ResetGridScrollBarColor,
        .setGridCachedCount = SetGridCachedCount,
        .resetGridCachedCount = ResetGridCachedCount,
        .setGridEditMode = SetGridEditMode,
        .resetGridEditMode = ResetGridEditMode,
        .setGridMultiSelectable = SetGridMultiSelectable,
        .resetGridMultiSelectable = ResetGridMultiSelectable,
        .setGridMaxCount = SetGridMaxCount,
        .resetGridMaxCount = ResetGridMaxCount,
        .setGridMinCount = SetGridMinCount,
        .resetGridMinCount = ResetGridMinCount,
        .setGridCellLength = SetGridCellLength,
        .resetGridCellLength = ResetGridCellLength,
        .setGridLayoutDirection = SetGridLayoutDirection,
        .resetGridLayoutDirection = ResetGridLayoutDirection,
        .setGridSupportAnimation = SetGridSupportAnimation,
        .resetGridSupportAnimation = ResetGridSupportAnimation,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setNestedScroll = SetNestedScroll,
        .resetNestedScroll = ResetNestedScroll,
        .setEnableScroll = SetEnableScroll,
        .resetEnableScroll = ResetEnableScroll,
        .setFriction = SetFriction,
        .resetFriction = ResetFriction,
        .setGridFocusWrapMode = SetGridFocusWrapMode,
        .resetGridFocusWrapMode = ResetGridFocusWrapMode,
        .getGridFocusWrapMode = GetGridFocusWrapMode,
        .getGridColumnsTemplate = GetColumnsTemplate,
        .getGridRowsTemplate = GetRowsTemplate,
        .getGridColumnsGap = GetColumnsGap,
        .getGridRowsGap = GetRowsGap,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .getCachedCount = GetCachedCount,
        .setFlingSpeedLimit = SetFlingSpeedLimit,
        .resetFlingSpeedLimit = ResetFlingSpeedLimit,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
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
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnScrollIndex(frameNode, std::move(onEvent));
}

void ResetOnGridScrollIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollIndex(frameNode, nullptr);
}

void SetOnGridScrollIndexCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollIndex = reinterpret_cast<ScrollIndexFunc*>(extraParam);
        GridModelNG::SetOnScrollIndex(frameNode, std::move(*onScrollIndex));
    } else {
        GridModelNG::SetOnScrollIndex(frameNode, nullptr);
    }
}

void SetOnGridScrollBarUpdateCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollBarUpdate = reinterpret_cast<ScrollBarUpdateFunc*>(extraParam);
        GridModelNG::SetOnScrollBarUpdate(frameNode, std::move(*onScrollBarUpdate));
    } else {
        GridModelNG::SetOnScrollBarUpdate(frameNode, nullptr);
    }
}

void ResetOnGridScrollBarUpdate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollBarUpdate(frameNode, nullptr);
}

void SetOnGridItemDragStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragStart = reinterpret_cast<std::function<void(const ItemDragInfo&, int32_t)>*>(extraParam);
        GridModelNG::SetOnItemDragStart(frameNode, std::move(*onItemDragStart));
    } else {
        GridModelNG::SetOnItemDragStart(frameNode, nullptr);
    }
}

void ResetOnGridItemDragStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragStart(frameNode, nullptr);
}

void SetOnGridItemDragEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragEnter = reinterpret_cast<ItemDragEnterFunc*>(extraParam);
        GridModelNG::SetOnItemDragEnter(frameNode, std::move(*onItemDragEnter));
    } else {
        GridModelNG::SetOnItemDragEnter(frameNode, nullptr);
    }
}

void ResetOnGridItemDragEnter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragEnter(frameNode, nullptr);
}

void SetOnGridItemDragMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragMove = reinterpret_cast<ItemDragMoveFunc*>(extraParam);
        GridModelNG::SetOnItemDragMove(frameNode, std::move(*onItemDragMove));
    } else {
        GridModelNG::SetOnItemDragMove(frameNode, nullptr);
    }
}

void ResetOnGridItemDragMove(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragMove(frameNode, nullptr);
}

void SetOnGridItemDragLeave(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDragLeave = reinterpret_cast<ItemDragLeaveFunc*>(extraParam);
        GridModelNG::SetOnItemDragLeave(frameNode, std::move(*onItemDragLeave));
    } else {
        GridModelNG::SetOnItemDragLeave(frameNode, nullptr);
    }
}

void ResetOnGridItemDragLeave(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragLeave(frameNode, nullptr);
}

void SetOnGridItemDrop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onItemDrop = reinterpret_cast<ItemDropFunc*>(extraParam);
        GridModelNG::SetOnItemDrop(frameNode, std::move(*onItemDrop));
    } else {
        GridModelNG::SetOnItemDrop(frameNode, nullptr);
    }
}

void ResetOnGridItemDrop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDrop(frameNode, nullptr);
}

void CreateWithResourceObjGridFriction(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(resObj);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    GridModelNG::CreateWithResourceObjFriction(frameNode, AceType::Claim(resourceObj));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
