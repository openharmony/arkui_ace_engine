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
#include "core/interfaces/native/node/water_flow_modifier.h"

#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/waterflow_section_option.h"

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"

namespace OHOS::Ace::NG {
namespace {
constexpr ArkUI_Float64 FRICTION_DEFAULT = -1.0;
constexpr ArkUI_Float64 DIMENSION_DEFAULT = 0.0;
const int32_t ERROR_INT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
constexpr Dimension DEFAULT_FADING_EDGE_LENGTH = Dimension(32.0f, DimensionUnit::VP); // default value
constexpr int32_t INDEX_0 = 0;
constexpr int32_t INDEX_1 = 1;
constexpr int32_t INDEX_2 = 2;
std::string g_strValue;

void ResetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, "");
}

void SetColumnsTemplate(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, value);
}

void ResetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, "");
}

void SetRowsTemplate(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, value);
}

void ResetWaterFlowEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, true);
}

void SetWaterFlowEnableScrollInteraction(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, value);
}

void SetColumnsGap(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension columnsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        columnsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        columnsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetColumnsGap(frameNode, columnsGapDimension);
}

void ResetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));
}

void SetRowsGap(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension rowsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        rowsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        rowsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetRowsGap(frameNode, rowsGapDimension);
}

void ResetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));
}

void SetItemMinWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinWidth(frameNode, minWidthDimension);
}

void ResetItemMinWidth(ArkUINodeHandle node) {}

void SetItemMinHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinHeight(frameNode, minHeightDimension);
}

void ResetItemMinHeight(ArkUINodeHandle node) {}

void SetItemMaxWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxWidth(frameNode, maxWidthDimension);
}

void ResetItemMaxWidth(ArkUINodeHandle node) {}

void SetItemMaxHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxHeight(frameNode, maxHeightDimension);
}

void ResetItemMaxHeight(ArkUINodeHandle node) {}

void SetLayoutDirection(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, static_cast<FlexDirection>(direction));
}

void ResetLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, FlexDirection::COLUMN);
}

void SetWaterFlowNestedScroll(ArkUINodeHandle node, ArkUI_Int32 scrollForward, ArkUI_Int32 scrollBackward)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    nestedOpt.forward = static_cast<NestedScrollMode>(scrollForward);
    nestedOpt.backward = static_cast<NestedScrollMode>(scrollBackward);
    WaterFlowModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void ResetWaterFlowNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    WaterFlowModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetWaterFlowFriction(ArkUINodeHandle node, ArkUI_Float32 friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, friction);
}

void ResetWaterFlowFriction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, FRICTION_DEFAULT);
}

void SetEdgeEffect(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    ArkUI_Bool alwaysEnabled = false;
    WaterFlowModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

ArkUI_Int32 GetLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(WaterFlowModelNG::GetLayoutDirection(frameNode));
}

ArkUI_CharPtr GetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = WaterFlowModelNG::GetColumnsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = WaterFlowModelNG::GetRowsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_Float32 GetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return WaterFlowModelNG::GetColumnsGap(frameNode);
}

ArkUI_Float32 GetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return WaterFlowModelNG::GetRowsGap(frameNode);
}

void GetWaterFlowNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions options = WaterFlowModelNG::GetNestedScroll(frameNode);
    (*values)[0] = static_cast<ArkUI_Int32>(options.forward);
    (*values)[1] = static_cast<ArkUI_Int32>(options.backward);
}

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto hasFooter = WaterFlowModelNG::hasFooter(frameNode);
    auto totalChildCount = hasFooter ? frameNode->TotalChildCount() - 1 : frameNode->TotalChildCount();
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
    WaterFlowModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetCachedCount(frameNode, 1);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetCachedCount(frameNode);
}

void SetWaterFlowScrollBar(ArkUINodeHandle node, ArkUI_Int32 barState)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarMode(frameNode, static_cast<DisplayMode>(barState));
}

void ResetWaterFlowScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarMode(frameNode, DisplayMode::AUTO);
}

ArkUI_Int32 GetWaterFlowScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarMode(frameNode);
}

void SetWaterFlowBarWidth(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarWidth(frameNode, value);
}

void ResetWaterFlowBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarWidth(frameNode, "0vp");
}

ArkUI_Float32 GetWaterFlowBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarWidth(frameNode);
}

void SetWaterFlowScrollBarColor(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarColor(frameNode, value);
}

void ResetWaterFlowScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarColor(frameNode, "#FF000000");
}

ArkUI_Uint32 GetWaterFlowScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarColor(frameNode);
}

ArkUI_Int32 GetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    (*values)[INDEX_0] = WaterFlowModelNG::GetEdgeEffect(frameNode);
    (*values)[INDEX_1] = WaterFlowModelNG::GetEdgeEffectAlways(frameNode);
    return INDEX_2;
}

void SetWaterFlowSectionOptions(ArkUINodeHandle node, ArkUI_Int32 start, ArkUIWaterFlowSectionOption option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto waterFlowSections = WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);

    const auto& sectionArray = option->sections;
    const auto sectionsCount = sectionArray.size();

    std::vector<WaterFlowSections::Section> newSections(sectionsCount);

    for (size_t i = 0; i < sectionsCount; ++i) {
        const auto& sectionData = sectionArray[i];
        WaterFlowSections::Section& section = newSections[i];

        section.itemsCount = sectionData.itemsCount;
        section.crossCount = sectionData.crossCount;
        section.columnsGap = Dimension(sectionData.columnsGap);
        section.rowsGap = Dimension(sectionData.rowsGap);

        NG::PaddingProperty paddings;
        paddings.top = std::optional<CalcLength>(sectionData.margin[0]);
        paddings.right = std::optional<CalcLength>(sectionData.margin[1]);
        paddings.bottom = std::optional<CalcLength>(sectionData.margin[2]);
        paddings.left = std::optional<CalcLength>(sectionData.margin[3]);
        section.margin = paddings;
        if (sectionData.onGetItemMainSizeByIndex) {
            section.onGetItemMainSizeByIndex = [sectionData](int32_t value) -> float {
                // onGetItemMainSizeByIndex是一个返回float的函数指针
                using FuncType = float (*)(int32_t, void*);
                FuncType func = reinterpret_cast<FuncType>(sectionData.onGetItemMainSizeByIndex);
                float result = func(value, sectionData.userData);
                return result;
            };
        } else {
            section.onGetItemMainSizeByIndex = nullptr;
        }
    }

    waterFlowSections->ReplaceFrom(start, newSections);
}

void ResetWaterFlowSectionOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::ResetSections(frameNode);
}

ArkUI_WaterFlowSectionOption GetWaterFlowSectionOptions(ArkUINodeHandle node)
{
    ArkUI_WaterFlowSectionOption option;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, option);
    auto newSection = WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode)->GetSectionInfo();
    auto sectionsCount = newSection.size();
    option.sections.resize(sectionsCount);
    for (size_t i = 0; i < sectionsCount; ++i) {
        option.sections[i].itemsCount = newSection[i].itemsCount ? newSection[i].itemsCount : 0;
        option.sections[i].crossCount = newSection[i].crossCount.has_value() ? newSection[i].crossCount.value() : 0;
        option.sections[i].columnsGap = newSection[i].columnsGap.has_value() ? newSection[i].columnsGap->Value() : 0.0f;
        option.sections[i].rowsGap = newSection[i].rowsGap.has_value() ? newSection[i].rowsGap->Value() : 0.0f;
        option.sections[i].margin[0] =
            newSection[i].margin->top.has_value() ? newSection[i].margin->top->GetDimension().Value() : 0.0f;
        option.sections[i].margin[1] =
            newSection[i].margin->right.has_value() ? newSection[i].margin->right->GetDimension().Value() : 0.0f;
        option.sections[i].margin[2] =
            newSection[i].margin->bottom.has_value() ? newSection[i].margin->bottom->GetDimension().Value() : 0.0f;
        option.sections[i].margin[3] =
            newSection[i].margin->left.has_value() ? newSection[i].margin->left->GetDimension().Value() : 0.0f;
    }
    return option;
}

ArkUI_Float32 GetItemMinWidth(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMinWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMaxWidth(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMaxWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMinHeight(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMinHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMaxHeight(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMaxHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Int32 GetWaterFlowEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetScrollEnabled(frameNode);
}

ArkUI_Float32 GetWaterFlowFriction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetFriction(frameNode);
}
void SetScrollToIndex(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollToIndex(frameNode, index, animation, alignment);
}

void SetWaterflowFooter(ArkUINodeHandle node, ArkUINodeHandle footer)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* footerNode = reinterpret_cast<FrameNode*>(footer);
    CHECK_NULL_VOID(footerNode);
    WaterFlowModelNG::SetWaterflowFooter(frameNode, footerNode);
}

void ResetWaterflowFooter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetWaterflowFooter(frameNode, nullptr);
}

void SetWaterFlowFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 maxSpeed)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFlingSpeedLimit(frameNode, maxSpeed);
}

void ResetWaterFlowFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFlingSpeedLimit(frameNode, -1.0);
}

ArkUINodeHandle GetScrollController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = WaterFlowModelNG::GetOrCreateController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void SetWaterFlowScroller(ArkUINodeHandle node, ArkUINodeHandle controller, ArkUINodeHandle proxy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto scrollController = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller));
    CHECK_NULL_VOID(scrollController);
    auto scrollProxy = AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy));
    CHECK_NULL_VOID(scrollProxy);
    WaterFlowModelNG::SetScroller(frameNode, scrollController, scrollProxy);
}

void SetWaterFlowLayoutMode(ArkUINodeHandle node, ArkUI_Uint32 layoutMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN;
    if (layoutMode >= static_cast<uint32_t>(WaterFlowLayoutMode::TOP_DOWN) &&
        layoutMode <= static_cast<uint32_t>(WaterFlowLayoutMode::SLIDING_WINDOW)) {
        mode = static_cast<WaterFlowLayoutMode>(layoutMode);
    }
    WaterFlowModelNG::SetLayoutMode(frameNode, mode);
}

void ResetWaterFlowLayoutMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN;
    WaterFlowModelNG::SetLayoutMode(frameNode, mode);
}

void ResetWaterFlowSections(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::ResetSections(frameNode);
}

void SetWaterFlowFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    NG::ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetWaterFlowFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}
} // namespace
namespace NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const ArkUIWaterFlowModifier modifier = { ResetColumnsTemplate, SetColumnsTemplate, ResetRowsTemplate,
        SetRowsTemplate, ResetWaterFlowEnableScrollInteraction, SetWaterFlowEnableScrollInteraction, SetColumnsGap,
        ResetColumnsGap, SetRowsGap, ResetRowsGap, SetItemMinWidth, ResetItemMinWidth, SetItemMaxWidth,
        ResetItemMaxWidth, SetItemMinHeight, ResetItemMinHeight, SetItemMaxHeight, ResetItemMaxHeight,
        SetLayoutDirection, ResetLayoutDirection, SetWaterFlowNestedScroll, ResetWaterFlowNestedScroll,
        SetWaterFlowFriction, ResetWaterFlowFriction, GetLayoutDirection, GetColumnsTemplate, GetRowsTemplate,
        GetColumnsGap, GetRowsGap, GetWaterFlowNestedScroll, SetNodeAdapter, ResetNodeAdapter, GetNodeAdapter,
        SetCachedCount, ResetCachedCount, GetCachedCount, SetEdgeEffect, ResetEdgeEffect, SetWaterFlowScrollBar,
        ResetWaterFlowScrollBar, GetWaterFlowScrollBar, SetWaterFlowBarWidth, ResetWaterFlowBarWidth,
        GetWaterFlowBarWidth, SetWaterFlowScrollBarColor, ResetWaterFlowScrollBarColor, GetWaterFlowScrollBarColor,
        GetEdgeEffect, SetWaterFlowSectionOptions, ResetWaterFlowSectionOptions, GetWaterFlowSectionOptions,
        GetItemMinWidth, GetItemMaxWidth, GetItemMinHeight, GetItemMaxHeight, GetWaterFlowEnableScrollInteraction,
        GetWaterFlowFriction, SetScrollToIndex, SetWaterflowFooter, ResetWaterflowFooter, SetWaterFlowFlingSpeedLimit,
        ResetWaterFlowFlingSpeedLimit, GetScrollController, SetWaterFlowScroller, SetWaterFlowLayoutMode,
        ResetWaterFlowLayoutMode, ResetWaterFlowSections, SetWaterFlowFadingEdge, ResetWaterFlowFadingEdge };
    return &modifier;
}

const CJUIWaterFlowModifier* GetCJUIWaterFlowModifier()
{
    static const CJUIWaterFlowModifier modifier = { ResetColumnsTemplate, SetColumnsTemplate, ResetRowsTemplate,
        SetRowsTemplate, ResetWaterFlowEnableScrollInteraction, SetWaterFlowEnableScrollInteraction, SetColumnsGap,
        ResetColumnsGap, SetRowsGap, ResetRowsGap, SetItemMinWidth, ResetItemMinWidth, SetItemMaxWidth,
        ResetItemMaxWidth, SetItemMinHeight, ResetItemMinHeight, SetItemMaxHeight, ResetItemMaxHeight,
        SetLayoutDirection, ResetLayoutDirection, SetWaterFlowNestedScroll, ResetWaterFlowNestedScroll,
        SetWaterFlowFriction, ResetWaterFlowFriction, GetLayoutDirection, GetColumnsTemplate, GetRowsTemplate,
        GetColumnsGap, GetRowsGap, GetWaterFlowNestedScroll, SetNodeAdapter, ResetNodeAdapter, GetNodeAdapter,
        SetCachedCount, ResetCachedCount, GetCachedCount, SetEdgeEffect, ResetEdgeEffect, SetWaterFlowScrollBar,
        ResetWaterFlowScrollBar, GetWaterFlowScrollBar, SetWaterFlowBarWidth, ResetWaterFlowBarWidth,
        GetWaterFlowBarWidth, SetWaterFlowScrollBarColor, ResetWaterFlowScrollBarColor, GetWaterFlowScrollBarColor,
        GetEdgeEffect, SetWaterFlowSectionOptions, ResetWaterFlowSectionOptions, GetWaterFlowSectionOptions,
        GetItemMinWidth, GetItemMaxWidth, GetItemMinHeight, GetItemMaxHeight, GetWaterFlowEnableScrollInteraction,
        GetWaterFlowFriction, SetWaterflowFooter, ResetWaterflowFooter, SetScrollToIndex, SetWaterFlowFlingSpeedLimit,
        ResetWaterFlowFlingSpeedLimit, };
    return &modifier;
}

void SetOnWillScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onWillScroll = [nodeId, node, extraParam](const Dimension& offset, const ScrollState& state,
                            ScrollSource source) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_WILL_SCROLL;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        event.componentAsyncEvent.data[2].i32 = static_cast<int>(source);
        SendArkUIAsyncEvent(&event);
        scrollRes.offset = Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    ScrollableModelNG::SetOnWillScroll(frameNode, std::move(onWillScroll));
}

void SetOnWaterFlowReachEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachEnd = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_REACH_END;
        SendArkUIAsyncEvent(&event);
    };
    WaterFlowModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}

void SetOnDidScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto setOnDidScroll = [nodeId, node, extraParam](const Dimension& offset, const ScrollState& state) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_DID_SCROLL;
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUIAsyncEvent(&event);
    };
    ScrollableModelNG::SetOnDidScroll(frameNode, std::move(setOnDidScroll));
}

void SetOnWaterFlowScrollStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStart = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_START;
        SendArkUIAsyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}

void SetOnWaterFlowScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStop = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_STOP;
        SendArkUIAsyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

void SetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollFrameBegin = [nodeId, node, extraParam](
                                  const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
        ScrollFrameResult scrollRes { .offset = offset };
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_FRAME_BEGIN;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        event.componentAsyncEvent.data[0].f32 =
            usePx ? static_cast<float>(offset.ConvertToPx()) : static_cast<float>(offset.Value());
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(state);
        SendArkUIAsyncEvent(&event);
        scrollRes.offset = usePx ? Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::PX)
                                 : Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}

void SetOnWaterFlowScrollIndex(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollIndex = [nodeId, node, extraParam](int32_t first, int32_t last) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_INDEX;
        event.componentAsyncEvent.data[0].i32 = first;
        event.componentAsyncEvent.data[1].i32 = last;
        SendArkUIAsyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}

void SetOnWaterFlowReachStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachStart = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_REACH_START;
        SendArkUIAsyncEvent(&event);
    };
    WaterFlowModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void ResetOnWillScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
}
void ResetOnWaterFlowReachEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnReachEnd(frameNode, nullptr);
}
void ResetOnDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
}
void ResetOnWaterFlowScrollStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollStart(frameNode, nullptr);
}
void ResetOnWaterFlowScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollStop(frameNode, nullptr);
}
void ResetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
}
void ResetOnWaterFlowScrollIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollIndex(frameNode, nullptr);
}
void ResetOnWaterFlowReachStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnReachStart(frameNode, nullptr);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG