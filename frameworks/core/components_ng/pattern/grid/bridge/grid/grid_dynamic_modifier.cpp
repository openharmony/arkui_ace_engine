/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include <memory>

#include "interfaces/native/native_type.h"
#include "interfaces/native/node/grid_layout_option.h"
#include "interfaces/native/node/node_model.h"

#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/bridge/grid/grid_model_impl.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::GridModelImpl* GetGridModelImpl()
{
    static Framework::GridModelImpl instance;
    return &instance;
}
#endif
namespace NG {
namespace {
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
const int32_t ERROR_INT_CODE = -1;
const int32_t ENABLE_FINGER_MULTI_SELECT_INDEX = 2;
std::string g_strValue;
using GridSizeCallback = ArkUI_GridItemSize (*)(int32_t, void*);
using GridRectCallback = ArkUI_GridItemRect (*)(int32_t, void*);
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

} // namespace

void SetGridColumnsTemplate(ArkUINodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetGridColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}
void SetGridRowsTemplate(ArkUINodeHandle node, const char* rowsTemplate)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, std::string(rowsTemplate));
}

void ResetGridRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsTemplate(frameNode, DEFAULT_ROWS_TEMPLATE);
}
void SetGridColumnsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap, void* columnsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
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

    if (SystemProperties::ConfigChangePerform()) {
        auto* columnsGapInner = reinterpret_cast<ResourceObject*>(columnsGapRawPtr);
        auto columnsGapResObj = AceType::Claim(columnsGapInner);
        GridModelNG::ParseResObjColumnsGap(frameNode, columnsGapResObj);
    }
}

void SetGridColumnsGapByJs(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap, void* columnsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(columnsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(columnsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(columnsGap->value, unitEnum);
    }
    if (LessNotEqual(gap.Value(), 0.0)) {
        gap = 0.0_vp;
    }
    GridModelNG::SetColumnsGap(frameNode, gap);

    if (SystemProperties::ConfigChangePerform()) {
        auto* columnsGapInner = reinterpret_cast<ResourceObject*>(columnsGapRawPtr);
        auto columnsGapResObj = AceType::Claim(columnsGapInner);
        GridModelNG::ParseResObjColumnsGap(frameNode, columnsGapResObj);
    }
}

void ResetGridColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetColumnsGap(frameNode, DEFAULT_COLUMNS_GAP);

    if (SystemProperties::ConfigChangePerform()) {
        GridModelNG::ParseResObjColumnsGap(frameNode, nullptr);
    }
}

void SetGridRowsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap, void* rowsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
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
    if (SystemProperties::ConfigChangePerform()) {
        auto* rowsGapInner = reinterpret_cast<ResourceObject*>(rowsGapRawPtr);
        auto rowsGapResObj = AceType::Claim(rowsGapInner);
        GridModelNG::ParseResObjRowsGap(frameNode, rowsGapResObj);
    }
}

void SetGridRowsGapByJs(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap, void* rowsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(rowsGap->unit);
    Dimension gap;
    if (unitEnum == DimensionUnit::CALC) {
        gap = CalcDimension(rowsGap->string, DimensionUnit::CALC);
    } else {
        gap = CalcDimension(rowsGap->value, unitEnum);
    }
    if (LessNotEqual(gap.Value(), 0.0)) {
        gap = 0.0_vp;
    }
    GridModelNG::SetRowsGap(frameNode, gap);
    if (SystemProperties::ConfigChangePerform()) {
        auto* rowsGapInner = reinterpret_cast<ResourceObject*>(rowsGapRawPtr);
        auto rowsGapResObj = AceType::Claim(rowsGapInner);
        GridModelNG::ParseResObjRowsGap(frameNode, rowsGapResObj);
    }
}

void ResetGridRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetRowsGap(frameNode, DEFAULT_ROWS_GAP);
    if (SystemProperties::ConfigChangePerform()) {
        GridModelNG::ParseResObjRowsGap(frameNode, nullptr);
    }
}

void SetGridScrollBar(ArkUINodeHandle node, int32_t scrollBar)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    DisplayMode mode = static_cast<DisplayMode>(scrollBar);
    GridModelNG::SetScrollBarMode(frameNode, mode);
}

void ResetGridScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarMode(frameNode, DEFAULT_SCROLL_BAR);
}

ArkUI_Int32 GetGridScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return GridModelNG::GetScrollBarMode(frameNode);
}

void SetGridScrollBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension scrollBarWidth = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    GridModelNG::SetScrollBarWidth(frameNode, scrollBarWidth);
}

void ResetGridScrollBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarWidth(frameNode, DEFAULT_SCROLL_BAR_WIDTH);
}

void SetScrollBarWidthString(ArkUINodeHandle node, ArkUI_CharPtr scrollBarWidthStr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarWidth(frameNode, std::string(scrollBarWidthStr));
}

ArkUI_Float32 GetGridScrollBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return GridModelNG::GetScrollBarWidth(frameNode);
}

void SetGridScrollBarWidthResObj(ArkUINodeHandle node, ArkUI_VoidPtr resObjRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::CreateWithResourceObjScrollBarWidth(
        frameNode, AceType::Claim(reinterpret_cast<ResourceObject*>(resObjRawPtr)));
}

void SetGridScrollBarColor(ArkUINodeHandle node, uint32_t scrollBarColor)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarColor(frameNode, Color(scrollBarColor));
}

void SetGridScrollBarColorPtr(ArkUINodeHandle node, ArkUI_Int32 color, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        GridModelNG::CreateWithResourceObjScrollBarColor(frameNode, resObj);
    }
    GridModelNG::SetScrollBarColor(frameNode, result);
}

void CreateWithResourceObjGridScrollBarColor(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    GridModelNG::CreateWithResourceObjScrollBarColor(frameNode, AceType::Claim(resourceObj));
}

void ResetGridScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollBarColor(frameNode, std::nullopt);

    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CreateWithResourceObjGridScrollBarColor(node, nullptr);
}

ArkUI_Uint32 GetGridScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return GridModelNG::GetScrollBarColor(frameNode);
}

void SetGridCachedCount(ArkUINodeHandle node, int32_t cachedCount)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetGridCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
}

void SetGridEditMode(ArkUINodeHandle node, ArkUI_Bool editMode)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, editMode);
}

void ResetGridEditMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEditable(frameNode, DEFAULT_EDIT_MODE);
}

ArkUI_Bool GetGridEditMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetEditable(frameNode);
}

void SetGridMultiSelectable(ArkUINodeHandle node, ArkUI_Bool multiSelectable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, multiSelectable);
}

void ResetGridMultiSelectable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMultiSelectable(frameNode, DEFAULT_MULTI_SELECTABLE);
}

ArkUI_Bool GetGridMultiSelectable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetMultiSelectable(frameNode);
}

void SetGridMaxCount(ArkUINodeHandle node, int32_t maxCount)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, maxCount);
}

void ResetGridMaxCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMaxCount(frameNode, DEFAULT_MAX_COUNT);
}

void SetGridMinCount(ArkUINodeHandle node, int32_t minCount)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, minCount);
}

void ResetGridMinCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetMinCount(frameNode, DEFAULT_MIN_COUNT);
}

void SetGridCellLength(ArkUINodeHandle node, int32_t cellLength)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, cellLength);
}

void ResetGridCellLength(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCellLength(frameNode, DEFAULT_CELL_LENGTH);
}

void SetGridLayoutDirection(ArkUINodeHandle node, int32_t layoutDirection)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FlexDirection direction = static_cast<FlexDirection>(layoutDirection);
    GridModelNG::SetLayoutDirection(frameNode, direction);
}

void ResetGridLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutDirection(frameNode, DEFAULT_LAYOUT_DIRECTION);
}

void SetGridSupportAnimation(ArkUINodeHandle node, ArkUI_Bool supportAnimation)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, supportAnimation);
}

void ResetGridSupportAnimation(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportAnimation(frameNode, DEFAULT_SUPPORT_ANIMATION);
}

ArkUI_Bool GetGridSupportAnimation(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetSupportAnimation(frameNode);
}

void SetEdgeEffect(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEdgeEffect(
        frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetNestedScroll(frameNode, opt);
}

void ResetNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    const NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    GridModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void GetNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions options = GridModelNG::GetNestedScroll(frameNode);
    (*values)[0] = static_cast<ArkUI_Int32>(options.forward);
    (*values)[1] = static_cast<ArkUI_Int32>(options.backward);
}

void SetEnableScroll(ArkUINodeHandle node, ArkUI_Bool ScrollEnabled)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, ScrollEnabled);
}

void ResetEnableScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Bool scrollEnabled = true;
    GridModelNG::SetScrollEnabled(frameNode, scrollEnabled);
}

void SetFriction(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetFriction(frameNode, friction);
}

void ResetFriction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 friction = -1.0;
    GridModelNG::SetFriction(frameNode, friction);
}

ArkUI_Float32 GetFriction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<float>(GridModelNG::GetFriction(frameNode));
}

void SetGridFocusWrapMode(ArkUINodeHandle node, int32_t focusWrapMode)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FocusWrapMode mode = static_cast<FocusWrapMode>(focusWrapMode);
    GridModelNG::SetFocusWrapMode(frameNode, mode);
}

void ResetGridFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetFocusWrapMode(frameNode, FocusWrapMode::DEFAULT);
}

ArkUI_Int32 GetGridFocusWrapMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(GridModelNG::GetFocusWrapMode(frameNode));
}

void SetFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 flingSpeedLimit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, flingSpeedLimit);
}

void ResetFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 flingSpeedLimit = -1.0;
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, flingSpeedLimit);
}

void SetGridAlignItems(ArkUINodeHandle node, int32_t alignItems)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode, static_cast<GridItemAlignment>(alignItems));
}

void ResetGridAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetAlignItems(frameNode, GridItemAlignment::DEFAULT);
}

ArkUI_Int32 GetGridAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<int32_t>(GridModelNG::GetAlignItems(frameNode));
}

void SetGridSyncLoad(ArkUINodeHandle node, ArkUI_Bool syncLoad)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSyncLoad(frameNode, syncLoad);
}

void ResetGridSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSyncLoad(frameNode, true);
}

ArkUI_Bool GetGridSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return GridModelNG::GetSyncLoad(frameNode);
}

void SetGridEditModeOptions(ArkUINodeHandle node, void* options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    EditModeOptions* newOptions = reinterpret_cast<EditModeOptions*>(options);
    GridModelNG::SetEditModeOptions(frameNode, *newOptions);
}

void ResetGridEditModeOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    EditModeOptions newOptions;
    GridModelNG::SetEditModeOptions(frameNode, newOptions);
}

void GetGridEditModeOptions(ArkUINodeHandle node, ArkUI_Int32 (*values)[3])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    EditModeOptions options = GridModelNG::GetEditModeOptions(frameNode);
    (*values)[0] = options.enableGatherSelectedItemsAnimation ? 1 : 0;
    (*values)[1] = options.useDefaultMultiSelectStyle ? 1 : 0;
    (*values)[ENABLE_FINGER_MULTI_SELECT_INDEX] = options.enableFingerMultiSelect ? 1 : 0;
}

ArkUI_CharPtr GetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = GridModelNG::GetColumnsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = GridModelNG::GetRowsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_Float32 GetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return GridModelNG::GetColumnsGap(frameNode);
}

ArkUI_Float32 GetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return GridModelNG::GetRowsGap(frameNode);
}

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetCachedCount(frameNode, 1);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return GridModelNG::GetCachedCount(frameNode);
}

void SetShowCached(ArkUINodeHandle node, ArkUI_Bool show)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetShowCached(frameNode, show);
}

void ResetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetShowCached(frameNode, false);
}

ArkUI_Bool GetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetShowCached(frameNode);
}

void SetGridFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    NG::ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetGridFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}

void SetItemFillPolicy(ArkUINodeHandle node, int32_t policy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PresetFillType fileType = static_cast<PresetFillType>(policy);
    GridModelNG::SetItemFillPolicy(frameNode, fileType);
}

void ResetItemFillPolicy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::ResetItemFillPolicy(frameNode);
}

ArkUI_Int32 GetItemFillPolicy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<int32_t>(GridModelNG::GetItemFillPolicy(frameNode));
}

void SetGridEnableScrollInteraction(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, value);
}

ArkUI_Int32 GetGridEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return GridModelNG::GetScrollEnabled(frameNode);
}

void ResetGridEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetScrollEnabled(frameNode, true);
}

void SetGridLayoutOptions(ArkUINodeHandle node, ArkUIGridLayoutOptions option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridLayoutOptions gridLayoutOptions;

    if (option->size > 0 && !option->irregularIndexes.empty()) {
        gridLayoutOptions.irregularIndexes.clear();
        gridLayoutOptions.irregularIndexes.insert(option->irregularIndexes.begin(), option->irregularIndexes.end());
    }
    if (option->onGetIrregularSizeByIndex) {
        auto callback = reinterpret_cast<GridSizeCallback>(option->onGetIrregularSizeByIndex);
        void* userData = option->irregularSizeUserData;
        gridLayoutOptions.getSizeByIndex = [callback, userData](int32_t index) -> GridItemSize {
            ArkUI_GridItemSize arkSize = callback(index, userData);
            return GridItemSize { arkSize.rowSpan, arkSize.columnSpan };
        };
    }
    if (option->onRectByIndexCallback) {
        auto callback = reinterpret_cast<GridRectCallback>(option->onRectByIndexCallback);
        void* userData = option->rectByIndexUserData;
        gridLayoutOptions.getRectByIndex = [callback, userData](int32_t index) -> GridItemRect {
            ArkUI_GridItemRect arkRect = callback(index, userData);
            return GridItemRect { arkRect.rowStart, arkRect.rowSpan, arkRect.columnStart, arkRect.columnSpan };
        };
    }
    GridModelNG::SetLayoutOptions(frameNode, gridLayoutOptions);
}

void SetLayoutOptions(ArkUINodeHandle node, void* option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetLayoutOptions(frameNode, *reinterpret_cast<GridLayoutOptions*>(option));
}

void ResetGridLayoutOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::ResetLayoutOptions(frameNode);
}

void SetScrollToIndex(
    ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment, float options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> extraOffset = options;
    GridModelNG::SetScrollToIndex(frameNode, index, animation, alignment, extraOffset);
}

void SetSupportLazyLoadingEmptyBranch(ArkUINodeHandle node, ArkUI_Bool support)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportLazyLoadingEmptyBranch(frameNode, support);
}

ArkUI_Bool GetSupportLazyLoadingEmptyBranch(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetSupportLazyLoadingEmptyBranch(frameNode);
}

void SetGridEnableEditMode(ArkUINodeHandle node, ArkUI_Bool enableEditMode)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEnableEditMode(frameNode, enableEditMode);
}

void ResetGridEnableEditMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEnableEditMode(frameNode, false);
}

ArkUI_Bool GetGridEnableEditMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return GridModelNG::GetEnableEditMode(frameNode);
}

ArkUINodeHandle GetGridController(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = GridModelNG::GetOrCreateController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void SetGridScrollBarProxy(ArkUINodeHandle node, ArkUINodeHandle proxy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollProxy = AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy));
    pattern->SetScrollBarProxy(AceType::DynamicCast<NG::ScrollBarProxy>(scrollProxy));
}

void SetOnGridScrollIndex(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollIndex(frameNode, nullptr);
}

void SetOnGridScrollIndexCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollBarUpdate(frameNode, nullptr);
}

void SetGridOnItemDragStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ItemDragInfo& dragInfo, int32_t itemIndex) -> RefPtr<UINode> {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_GRID_ITEM_DRAG_START;
        event.mixedEvent.numberDataLength = 3;
        event.mixedEvent.numberData[0].f32 = dragInfo.GetX();
        event.mixedEvent.numberData[1].f32 = dragInfo.GetY();
        event.mixedEvent.numberData[2].i32 = itemIndex;
        SendArkUISyncEvent(&event);
        if (event.mixedEvent.numberReturnData[0].i32 == 1) {
            return dragInfo.GetFrameNode().Upgrade();
        } else {
            return nullptr;
        }
    };
    GridModelNG::SetOnGridItemDragStart(frameNode, std::move(onEvent));
}

void SetOnGridItemDragStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragStart(frameNode, nullptr);
}

void SetGridOnItemDragEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ItemDragInfo& dragInfo) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_ITEM_DRAG_ENTER;
        event.componentAsyncEvent.data[0].f32 = dragInfo.GetX();
        event.componentAsyncEvent.data[1].f32 = dragInfo.GetY();
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnItemDragEnter(frameNode, std::move(onEvent));
}

void SetOnGridItemDragEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragEnter(frameNode, nullptr);
}

void SetGridOnItemDragMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_ITEM_DRAG_MOVE;
        event.componentAsyncEvent.data[0].f32 = dragInfo.GetX();
        event.componentAsyncEvent.data[1].f32 = dragInfo.GetY();
        event.componentAsyncEvent.data[2].i32 = itemIndex;
        event.componentAsyncEvent.data[3].i32 = insertIndex;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnItemDragMove(frameNode, std::move(onEvent));
}

void SetOnGridItemDragMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragMove(frameNode, nullptr);
}

void SetGridOnItemDragLeave(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ItemDragInfo& dragInfo, int32_t itemIndex) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_ITEM_DRAG_LEAVE;
        event.componentAsyncEvent.data[0].f32 = dragInfo.GetX();
        event.componentAsyncEvent.data[1].f32 = dragInfo.GetY();
        event.componentAsyncEvent.data[2].i32 = itemIndex;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnItemDragLeave(frameNode, std::move(onEvent));
}

void SetOnGridItemDragLeave(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDragLeave(frameNode, nullptr);
}

void SetGridOnItemDrop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_ITEM_DROP;
        event.componentAsyncEvent.data[0].f32 = dragInfo.GetX();
        event.componentAsyncEvent.data[1].f32 = dragInfo.GetY();
        event.componentAsyncEvent.data[2].i32 = itemIndex;
        event.componentAsyncEvent.data[3].i32 = insertIndex;
        event.componentAsyncEvent.data[4].i32 = isSuccess;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnItemDrop(frameNode, std::move(onEvent));
}

void SetOnGridItemDrop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnItemDrop(frameNode, nullptr);
}

void CreateWithResourceObjGridFriction(ArkUINodeHandle node, void* resObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(resObj);
    auto* resourceObj = reinterpret_cast<ResourceObject*>(resObj);
    GridModelNG::CreateWithResourceObjFriction(frameNode, AceType::Claim(resourceObj));
}

void SetOnGridWillScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillScroll = [extraParam](const Dimension& offset, const ScrollState& state,
                            ScrollSource source) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_WILL_SCROLL;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        event.componentAsyncEvent.data[2].i32 = static_cast<int>(source);
        SendArkUISyncEvent(&event);
        scrollRes.offset = Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    ScrollableModelNG::SetOnWillScroll(frameNode, std::move(onWillScroll));
}

void ResetOnGridWillScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
}

void SetOnGridDidScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto setOnDidScroll = [extraParam](const Dimension& offset, const ScrollState& state) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.subKind = ON_GRID_DID_SCROLL;
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUISyncEvent(&event);
    };
    ScrollableModelNG::SetOnDidScroll(frameNode, std::move(setOnDidScroll));
}

void ResetOnGridDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
}

void SetOnGridScrollStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStart = [extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_START;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}

void ResetOnGridScrollStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollStart(frameNode, nullptr);
}

void SetOnGridScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStop = [extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_STOP;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

void ResetOnGridScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollStop(frameNode, nullptr);
}

void SetOnGridScrollFrameBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollFrameBegin = [extraParam](const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_SCROLL_FRAME_BEGIN;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUISyncEvent(&event);
        scrollRes.offset = usePx ? Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::PX)
                                 : Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    GridModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}

void ResetOnGridScrollFrameBegin(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
}

void SetOnGridScrollBarUpdate(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onGridScrollBarUpdate = [extraParam](int32_t index,
                                     Dimension offset) -> std::pair<std::optional<float>, std::optional<float>> {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.mixedEvent.subKind = ON_GRID_SCROLL_BAR_UPDATE;
        event.mixedEvent.numberDataLength = 2;
        event.mixedEvent.numberData[0].i32 = index;
        event.mixedEvent.numberData[1].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        SendArkUISyncEvent(&event);
        return std::make_pair(std::optional<float>(event.mixedEvent.numberReturnData[0].f32),
            std::optional<float>(event.mixedEvent.numberReturnData[1].f32));
    };
    GridModelNG::SetOnScrollBarUpdate(frameNode, std::move(onGridScrollBarUpdate));
}

void SetOnGridEditModeChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [extraParam](bool enableEditMode) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_GRID_EDIT_MODE_CHANGE;
        event.componentAsyncEvent.data[0].i32 = enableEditMode ? 1 : 0;
        SendArkUISyncEvent(&event);
    };
    GridModelNG::SetEnableEditModeChangeEvent(frameNode, std::move(onChange));
}

void ResetOnGridEditModeChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEnableEditModeChangeEvent(frameNode, nullptr);
}

void SetOnGridEditModeChangeCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(extraParam);
        GridModelNG::SetEnableEditModeChangeEvent(frameNode, std::move(*onChange));
    } else {
        GridModelNG::SetEnableEditModeChangeEvent(frameNode, nullptr);
    }
}

void SetOnScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScroll = reinterpret_cast<OnScrollEvent*>(callback);
    GridModelNG::SetOnScroll(frameNode, onScroll ? std::move(*onScroll) : nullptr);
}

void SetOnReachStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachStart = reinterpret_cast<OnReachEvent*>(callback);
    GridModelNG::SetOnReachStart(frameNode, onReachStart ? std::move(*onReachStart) : nullptr);
}

void SetOnReachEnd(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachEnd = reinterpret_cast<OnReachEvent*>(callback);
    GridModelNG::SetOnReachEnd(frameNode, onReachEnd ? std::move(*onReachEnd) : nullptr);
}

void SetOnScrollStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStart = reinterpret_cast<OnScrollStartEvent*>(callback);
    GridModelNG::SetOnScrollStart(frameNode, onScrollStart ? std::move(*onScrollStart) : nullptr);
}

void SetOnScrollStop(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStop = reinterpret_cast<OnScrollStopEvent*>(callback);
    GridModelNG::SetOnScrollStop(frameNode, onScrollStop ? std::move(*onScrollStop) : nullptr);
}

void SetOnScrollFrameBegin(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollFrameBegin = reinterpret_cast<OnScrollFrameBeginEvent*>(callback);
    GridModelNG::SetOnScrollFrameBegin(frameNode, onScrollFrameBegin ? std::move(*onScrollFrameBegin) : nullptr);
}

void SetOnScrollToIndex(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto event = reinterpret_cast<ScrollToIndexFunc*>(callback);
    GridModelNG::SetOnScrollToIndex(frameNode, event ? std::move(*event) : nullptr);
}

void* GetEventSetHandler(uint32_t kind)
{
    static const ComponentAsyncEventHandler gridNodeAsyncEventHandlers[] = {
        nullptr,
        SetOnGridScrollStart,
        SetOnGridScrollStop,
        SetOnGridScrollIndex,
        SetOnGridScrollFrameBegin,
        SetOnGridWillScroll,
        SetOnGridDidScroll,
        SetOnGridScrollBarUpdate,
        SetGridOnItemDragStart,
        SetGridOnItemDragEnter,
        SetGridOnItemDragMove,
        SetGridOnItemDragLeave,
        SetGridOnItemDrop,
        SetOnGridEditModeChange,
    };
    if (kind >= sizeof(gridNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(gridNodeAsyncEventHandlers[kind]);
}

void* GetEventResetHandler(uint32_t kind)
{
    static const ResetComponentAsyncEventHandler gridNodeResetAsyncEventHandlers[] = {
        nullptr,
        ResetOnGridScrollStart,
        ResetOnGridScrollStop,
        ResetOnGridScrollIndex,
        ResetOnGridScrollFrameBegin,
        ResetOnGridWillScroll,
        ResetOnGridDidScroll,
        ResetOnGridScrollBarUpdate,
        ResetOnGridItemDragEnter,
        ResetOnGridItemDragLeave,
        ResetOnGridItemDragMove,
        ResetOnGridItemDragStart,
        ResetOnGridItemDrop,
        ResetOnGridEditModeChange,
    };
    if (kind >= sizeof(gridNodeResetAsyncEventHandlers) / sizeof(ResetComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(gridNodeResetAsyncEventHandlers[kind]);
}

void InitScroller(ArkUINodeHandle node, void* controller, void* proxy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::InitScroller(frameNode, AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller)),
        AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy)));
}

ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(frameNode.GetRawPtr());
}

void Create(void* controller, void* proxy)
{
    GridModelNG::CreateGrid(AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller)),
        AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy)));
}

void* CreatePositionController()
{
    auto controller = GridModelNG::CreatePositionControllerStatic();
    controller->IncRefCount();
    return controller.GetRawPtr();
}

void* CreateScrollBarProxy()
{
    auto proxy = GridModelNG::CreateScrollBarProxyStatic();
    proxy->IncRefCount();
    return proxy.GetRawPtr();
}

void PopGrid()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGrid][pop]", PopGrid);
    }
    GridModelNG::PopStatic();
}

ArkUI_Int32 GetDisplayMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(DisplayMode::AUTO));
    return static_cast<ArkUI_Int32>(GridModelNG::GetDisplayMode(frameNode));
}

void SetEnableEditMode(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetEnableEditMode(frameNode, enable);
}

void SetEnableEditModeChangeEvent(ArkUINodeHandle node, void* event)
{
    CHECK_NULL_VOID(event);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto enableEditModeChangeEvent = reinterpret_cast<std::function<void(bool)>*>(event);
    GridModelNG::SetEnableEditModeChangeEvent(frameNode, std::move(*enableEditModeChangeEvent));
}

void SetDirection(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextDirection textDirection = static_cast<TextDirection>(direction);
    GridModelNG::SetIsRTL(frameNode, textDirection);
}

void SetHeight(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension height;
    if (unit == static_cast<ArkUI_Int32>(DimensionUnit::CALC)) {
        height = CalcDimension(calcValue, DimensionUnit::CALC);
    } else {
        height = CalcDimension(value, static_cast<DimensionUnit>(unit));
    }
    GridModelNG::SetGridHeight(frameNode, height);
}

void SetSupportDragAnimation(ArkUINodeHandle node, ArkUI_Bool support)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GridModelNG::SetSupportDragAnimation(frameNode, support);
}

#ifndef CROSS_PLATFORM
void CreateImpl(void* controller, void* proxy)
{
    GetGridModelImpl()->Create(AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller)),
        AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy)));
}

void* CreatePositionControllerImpl()
{
    auto controller = GetGridModelImpl()->CreatePositionController();
    controller->IncRefCount();
    return controller.GetRawPtr();
}

void* CreateScrollBarProxyImpl()
{
    auto proxy = GetGridModelImpl()->CreateScrollBarProxy();
    proxy->IncRefCount();
    return proxy.GetRawPtr();
}

void PopGridImpl()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGrid][pop]", PopGridImpl);
    }
    GetGridModelImpl()->Pop();
}

void SetGridColumnsTemplateImpl(ArkUINodeHandle node, const char* columnsTemplate)
{
    GetGridModelImpl()->SetColumnsTemplate(columnsTemplate);
}

void SetGridRowsTemplateImpl(ArkUINodeHandle node, const char* rowsTemplate)
{
    GetGridModelImpl()->SetRowsTemplate(rowsTemplate);
}

void SetGridColumnsGapImpl(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap, void* columnsGapRawPtr)
{
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
    GetGridModelImpl()->SetColumnsGap(gap);
}

void SetGridRowsGapImpl(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap, void* rowsGapRawPtr)
{
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
    GetGridModelImpl()->SetRowsGap(gap);
}

void SetGridScrollBarImpl(ArkUINodeHandle node, int32_t scrollBar)
{
    GetGridModelImpl()->SetScrollBarMode(static_cast<DisplayMode>(scrollBar));
}

void SetGridScrollBarColorImpl(ArkUINodeHandle node, uint32_t scrollBarColor) {}

ArkUI_Int32 GetDisplayModeImpl(ArkUINodeHandle node)
{
    return static_cast<ArkUI_Int32>(GetGridModelImpl()->GetDisplayMode());
}

void SetScrollBarWidthStringImpl(ArkUINodeHandle node, ArkUI_CharPtr scrollBarWidthStr)
{
    GetGridModelImpl()->SetScrollBarWidth(std::string(scrollBarWidthStr));
}

void SetGridScrollBarWidthResObjImpl(ArkUINodeHandle node, ArkUI_VoidPtr resObjRawPtr) {}

void SetOnGridScrollBarUpdateCallBackImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onScrollBarUpdate = reinterpret_cast<ScrollBarUpdateFunc*>(extraParam);
    GetGridModelImpl()->SetOnScrollBarUpdate(std::move(*onScrollBarUpdate));
}

void SetGridCachedCountImpl(ArkUINodeHandle node, int32_t cachedCount)
{
    GetGridModelImpl()->SetCachedCount(cachedCount, true);
}

void SetShowCachedImpl(ArkUINodeHandle node, ArkUI_Bool show) {}

void SetGridEditModeImpl(ArkUINodeHandle node, ArkUI_Bool editMode)
{
    GetGridModelImpl()->SetEditable(editMode);
}

void SetGridMultiSelectableImpl(ArkUINodeHandle node, ArkUI_Bool multiSelectable)
{
    GetGridModelImpl()->SetMultiSelectable(multiSelectable);
}

void SetGridMaxCountImpl(ArkUINodeHandle node, int32_t maxCount)
{
    GetGridModelImpl()->SetMaxCount(maxCount);
}

void SetGridMinCountImpl(ArkUINodeHandle node, int32_t minCount)
{
    GetGridModelImpl()->SetMinCount(minCount);
}

void SetGridCellLengthImpl(ArkUINodeHandle node, int32_t cellLength)
{
    GetGridModelImpl()->SetCellLength(cellLength);
}

void SetGridLayoutDirectionImpl(ArkUINodeHandle node, int32_t layoutDirection)
{
    FlexDirection direction = static_cast<FlexDirection>(layoutDirection);
    GetGridModelImpl()->SetLayoutDirection(direction);
}

void SetSupportDragAnimationImpl(ArkUINodeHandle node, ArkUI_Bool support)
{
    GetGridModelImpl()->SetSupportDragAnimation(support);
}

void SetEdgeEffectImpl(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    GetGridModelImpl()->SetEdgeEffect(
        static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void SetDirectionImpl(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    TextDirection textDirection = static_cast<TextDirection>(direction);
    GetGridModelImpl()->SetIsRTL(textDirection);
}

void SetGridSupportAnimationImpl(ArkUINodeHandle node, ArkUI_Bool supportAnimation)
{
    GetGridModelImpl()->SetSupportAnimation(supportAnimation);
}

void SetOnGridItemDragEnterImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onItemDragEnter = reinterpret_cast<ItemDragEnterFunc*>(extraParam);
    GetGridModelImpl()->SetOnItemDragEnter(std::move(*onItemDragEnter));
}

void SetOnGridItemDragMoveImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onItemDragMove = reinterpret_cast<ItemDragMoveFunc*>(extraParam);
    GetGridModelImpl()->SetOnItemDragMove(std::move(*onItemDragMove));
}

void SetOnGridItemDragLeaveImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onItemDragLeave = reinterpret_cast<ItemDragLeaveFunc*>(extraParam);
    GetGridModelImpl()->SetOnItemDragLeave(std::move(*onItemDragLeave));
}

void SetOnGridItemDragStartImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onItemDragStart = reinterpret_cast<std::function<void(const ItemDragInfo&, int32_t)>*>(extraParam);
    GetGridModelImpl()->SetOnItemDragStart(std::move(*onItemDragStart));
}

void SetHeightImpl(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    CalcDimension height;
    if (unit == static_cast<ArkUI_Int32>(DimensionUnit::CALC)) {
        height = CalcDimension(calcValue, DimensionUnit::CALC);
    } else {
        height = CalcDimension(value, static_cast<DimensionUnit>(unit));
    }
    GetGridModelImpl()->SetGridHeight(height);
}

void SetOnGridItemDropImpl(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(extraParam);
    auto onItemDrop = reinterpret_cast<ItemDropFunc*>(extraParam);
    GetGridModelImpl()->SetOnItemDrop(std::move(*onItemDrop));
}

void SetNestedScrollImpl(ArkUINodeHandle node, int32_t forward, int32_t backward)
{
    NestedScrollOptions opt = {
        .forward = static_cast<NestedScrollMode>(forward),
        .backward = static_cast<NestedScrollMode>(backward),
    };
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetGridModelImpl()->SetNestedScroll(opt);
}

void SetEnableScrollImpl(ArkUINodeHandle node, ArkUI_Bool scrollEnabled)
{
    GetGridModelImpl()->SetScrollEnabled(scrollEnabled);
}

void SetOnScrollToIndexImpl(ArkUINodeHandle node, void* callback)
{
    auto event = reinterpret_cast<ScrollToIndexFunc*>(callback);
    GetGridModelImpl()->SetOnScrollToIndex(event ? std::move(*event) : nullptr);
}
#endif

namespace NodeModifier {
const ArkUIGridModifier* GetGridDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIGridModifier modifierImpl = {
            .setGridColumnsTemplate = SetGridColumnsTemplateImpl,
            .resetGridColumnsTemplate = nullptr,
            .setGridRowsTemplate = SetGridRowsTemplateImpl,
            .resetGridRowsTemplate = nullptr,
            .setGridColumnsGap = nullptr,
            .setGridColumnsGapByJs = SetGridColumnsGapImpl,
            .resetGridColumnsGap = nullptr,
            .setGridRowsGap = nullptr,
            .setGridRowsGapByJs = SetGridRowsGapImpl,
            .resetGridRowsGap = nullptr,
            .setGridScrollBar = SetGridScrollBarImpl,
            .resetGridScrollBar = nullptr,
            .getGridScrollBar = nullptr,
            .setGridScrollBarWidth = nullptr,
            .resetGridScrollBarWidth = nullptr,
            .setScrollBarWidthString = SetScrollBarWidthStringImpl,
            .getGridScrollBarWidth = nullptr,
            .setGridScrollBarWidthResObj = SetGridScrollBarWidthResObjImpl,
            .setGridScrollBarColor = SetGridScrollBarColorImpl,
            .setGridScrollBarColorPtr = nullptr,
            .resetGridScrollBarColor = nullptr,
            .getGridScrollBarColor = nullptr,
            .setGridCachedCount = SetGridCachedCountImpl,
            .resetGridCachedCount = nullptr,
            .setShowCached = SetShowCachedImpl,
            .resetShowCached = nullptr,
            .getShowCached = nullptr,
            .setGridEditMode = SetGridEditModeImpl,
            .resetGridEditMode = nullptr,
            .getGridEditMode = nullptr,
            .setGridMultiSelectable = SetGridMultiSelectableImpl,
            .resetGridMultiSelectable = nullptr,
            .getGridMultiSelectable = nullptr,
            .setGridMaxCount = SetGridMaxCountImpl,
            .resetGridMaxCount = nullptr,
            .setGridMinCount = SetGridMinCountImpl,
            .resetGridMinCount = nullptr,
            .setGridCellLength = SetGridCellLengthImpl,
            .resetGridCellLength = nullptr,
            .setGridLayoutDirection = SetGridLayoutDirectionImpl,
            .resetGridLayoutDirection = nullptr,
            .setGridSupportAnimation = SetGridSupportAnimationImpl,
            .resetGridSupportAnimation = nullptr,
            .getGridSupportAnimation = nullptr,
            .setEdgeEffect = SetEdgeEffectImpl,
            .resetEdgeEffect = nullptr,
            .setNestedScroll = SetNestedScrollImpl,
            .resetNestedScroll = nullptr,
            .getNestedScroll = nullptr,
            .setEnableScroll = SetEnableScrollImpl,
            .resetEnableScroll = nullptr,
            .setFriction = nullptr,
            .resetFriction = nullptr,
            .getFriction = nullptr,
            .setGridFocusWrapMode = nullptr,
            .resetGridFocusWrapMode = nullptr,
            .getGridFocusWrapMode = nullptr,
            .getGridColumnsTemplate = nullptr,
            .getGridRowsTemplate = nullptr,
            .getGridColumnsGap = nullptr,
            .getGridRowsGap = nullptr,
            .setNodeAdapter = nullptr,
            .resetNodeAdapter = nullptr,
            .getNodeAdapter = nullptr,
            .setCachedCount = nullptr,
            .resetCachedCount = nullptr,
            .getCachedCount = nullptr,
            .setGridAlignItems = nullptr,
            .resetGridAlignItems = nullptr,
            .getGridAlignItems = nullptr,
            .setSyncLoad = nullptr,
            .resetSyncLoad = nullptr,
            .getSyncLoad = nullptr,
            .setEditModeOptions = nullptr,
            .resetEditModeOptions = nullptr,
            .getEditModeOptions = nullptr,
            .setGridFadingEdge = nullptr,
            .resetGridFadingEdge = nullptr,
            .setOnGridScrollIndexCallBack = nullptr,
            .resetOnGridScrollIndex = nullptr,
            .setOnGridScrollBarUpdateCallBack = SetOnGridScrollBarUpdateCallBackImpl,
            .resetOnGridScrollBarUpdate = nullptr,
            .setOnGridScroll = nullptr,
            .setOnGridReachStart = nullptr,
            .setOnGridReachEnd = nullptr,
            .setOnGridScrollStart = nullptr,
            .setOnGridScrollStop = nullptr,
            .setOnGridScrollFrameBegin = nullptr,
            .setOnGridItemDragStart = SetOnGridItemDragStartImpl,
            .resetOnGridItemDragStart = nullptr,
            .setOnGridItemDragEnter = SetOnGridItemDragEnterImpl,
            .resetOnGridItemDragEnter = nullptr,
            .setOnGridItemDragMove = SetOnGridItemDragMoveImpl,
            .resetOnGridItemDragMove = nullptr,
            .setOnGridItemDragLeave = SetOnGridItemDragLeaveImpl,
            .resetOnGridItemDragLeave = nullptr,
            .setOnGridItemDrop = SetOnGridItemDropImpl,
            .resetOnGridItemDrop = nullptr,
            .createWithResourceObjFriction = nullptr,
            .createWithResourceObjScrollBarColor = nullptr,
            .resetGridEnableScrollInteraction = nullptr,
            .setGridEnableScrollInteraction = nullptr,
            .getGridEnableScrollInteraction = nullptr,
            .resetGridLayoutOptions = nullptr,
            .setGridLayoutOptions = nullptr,
            .resetItemFillPolicy = nullptr,
            .setItemFillPolicy = nullptr,
            .getItemFillPolicy = nullptr,
            .setScrollToIndex = nullptr,
            .setSupportLazyLoadingEmptyBranch = nullptr,
            .getSupportLazyLoadingEmptyBranch = nullptr,
            .setScrollBarProxy = nullptr,
            .getController = nullptr,
            .setGridEnableEditMode = nullptr,
            .resetGridEnableEditMode = nullptr,
            .getGridEnableEditMode = nullptr,
            .setOnGridEditModeChangeCallBack = nullptr,
            .resetOnGridEditModeChange = nullptr,
            .createFrameNode = nullptr,
            .create = CreateImpl,
            .createPositionController = CreatePositionControllerImpl,
            .createScrollBarProxy = CreateScrollBarProxyImpl,
            .getEventSetHandler = nullptr,
            .getEventResetHandler = nullptr,
            .initScroller = nullptr,
            .setLayoutOptions = nullptr,
            .popGrid = PopGridImpl,
            .getDisplayMode = GetDisplayModeImpl,
            .setEnableEditMode = nullptr,
            .setEnableEditModeChangeEvent = nullptr,
            .setSupportDragAnimation = SetSupportDragAnimationImpl,
            .setDirection = SetDirectionImpl,
            .setHeight = SetHeightImpl,
            .setOnScrollToIndex = SetOnScrollToIndexImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGridModifier modifier = {
        .setGridColumnsTemplate = SetGridColumnsTemplate,
        .resetGridColumnsTemplate = ResetGridColumnsTemplate,
        .setGridRowsTemplate = SetGridRowsTemplate,
        .resetGridRowsTemplate = ResetGridRowsTemplate,
        .setGridColumnsGap = SetGridColumnsGap,
        .setGridColumnsGapByJs = SetGridColumnsGapByJs,
        .resetGridColumnsGap = ResetGridColumnsGap,
        .setGridRowsGap = SetGridRowsGap,
        .setGridRowsGapByJs = SetGridRowsGapByJs,
        .resetGridRowsGap = ResetGridRowsGap,
        .setGridScrollBar = SetGridScrollBar,
        .resetGridScrollBar = ResetGridScrollBar,
        .getGridScrollBar = GetGridScrollBar,
        .setGridScrollBarWidth = SetGridScrollBarWidth,
        .resetGridScrollBarWidth = ResetGridScrollBarWidth,
        .setScrollBarWidthString = SetScrollBarWidthString,
        .getGridScrollBarWidth = GetGridScrollBarWidth,
        .setGridScrollBarWidthResObj = SetGridScrollBarWidthResObj,
        .setGridScrollBarColor = SetGridScrollBarColor,
        .setGridScrollBarColorPtr = SetGridScrollBarColorPtr,
        .resetGridScrollBarColor = ResetGridScrollBarColor,
        .getGridScrollBarColor = GetGridScrollBarColor,
        .setGridCachedCount = SetGridCachedCount,
        .resetGridCachedCount = ResetGridCachedCount,
        .setShowCached = SetShowCached,
        .resetShowCached = ResetShowCached,
        .getShowCached = GetShowCached,
        .setGridEditMode = SetGridEditMode,
        .resetGridEditMode = ResetGridEditMode,
        .getGridEditMode = GetGridEditMode,
        .setGridMultiSelectable = SetGridMultiSelectable,
        .resetGridMultiSelectable = ResetGridMultiSelectable,
        .getGridMultiSelectable = GetGridMultiSelectable,
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
        .getGridSupportAnimation = GetGridSupportAnimation,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setNestedScroll = SetNestedScroll,
        .resetNestedScroll = ResetNestedScroll,
        .getNestedScroll = GetNestedScroll,
        .setEnableScroll = SetEnableScroll,
        .resetEnableScroll = ResetEnableScroll,
        .setFriction = SetFriction,
        .resetFriction = ResetFriction,
        .getFriction = GetFriction,
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
        .getGridAlignItems = GetGridAlignItems,
        .setSyncLoad = SetGridSyncLoad,
        .resetSyncLoad = ResetGridSyncLoad,
        .getSyncLoad = GetGridSyncLoad,
        .setEditModeOptions = SetGridEditModeOptions,
        .resetEditModeOptions = ResetGridEditModeOptions,
        .getEditModeOptions = GetGridEditModeOptions,
        .setGridFadingEdge = SetGridFadingEdge,
        .resetGridFadingEdge = ResetGridFadingEdge,
        .setOnGridScrollIndexCallBack = SetOnGridScrollIndexCallBack,
        .resetOnGridScrollIndex = ResetOnGridScrollIndex,
        .setOnGridScrollBarUpdateCallBack = SetOnGridScrollBarUpdateCallBack,
        .resetOnGridScrollBarUpdate = ResetOnGridScrollBarUpdate,
        .setOnGridScroll = SetOnScroll,
        .setOnGridReachStart = SetOnReachStart,
        .setOnGridReachEnd = SetOnReachEnd,
        .setOnGridScrollStart = SetOnScrollStart,
        .setOnGridScrollStop = SetOnScrollStop,
        .setOnGridScrollFrameBegin = SetOnScrollFrameBegin,
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
        .createWithResourceObjScrollBarColor = CreateWithResourceObjGridScrollBarColor,
        .resetGridEnableScrollInteraction = ResetGridEnableScrollInteraction,
        .setGridEnableScrollInteraction = SetGridEnableScrollInteraction,
        .getGridEnableScrollInteraction = GetGridEnableScrollInteraction,
        .resetGridLayoutOptions = ResetGridLayoutOptions,
        .setGridLayoutOptions = SetGridLayoutOptions,
        .resetItemFillPolicy = ResetItemFillPolicy,
        .setItemFillPolicy = SetItemFillPolicy,
        .getItemFillPolicy = GetItemFillPolicy,
        .setScrollToIndex = SetScrollToIndex,
        .setSupportLazyLoadingEmptyBranch = SetSupportLazyLoadingEmptyBranch,
        .getSupportLazyLoadingEmptyBranch = GetSupportLazyLoadingEmptyBranch,
        .setScrollBarProxy = SetGridScrollBarProxy,
        .getController = GetGridController,
        .setGridEnableEditMode = SetGridEnableEditMode,
        .resetGridEnableEditMode = ResetGridEnableEditMode,
        .getGridEnableEditMode = GetGridEnableEditMode,
        .setOnGridEditModeChangeCallBack = SetOnGridEditModeChangeCallBack,
        .resetOnGridEditModeChange = ResetOnGridEditModeChange,
        .createFrameNode = CreateFrameNode,
        .create = Create,
        .createPositionController = CreatePositionController,
        .createScrollBarProxy = CreateScrollBarProxy,
        .getEventSetHandler = GetEventSetHandler,
        .getEventResetHandler = GetEventResetHandler,
        .initScroller = InitScroller,
        .setLayoutOptions = SetLayoutOptions,
        .popGrid = PopGrid,
        .getDisplayMode = GetDisplayMode,
        .setEnableEditMode = SetEnableEditMode,
        .setEnableEditModeChangeEvent = SetEnableEditModeChangeEvent,
        .setSupportDragAnimation = SetSupportDragAnimation,
        .setDirection = SetDirection,
        .setHeight = SetHeight,
        .setOnScrollToIndex = SetOnScrollToIndex,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIGridModifier* GetCJUIGridDynamicModifier()
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

} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace