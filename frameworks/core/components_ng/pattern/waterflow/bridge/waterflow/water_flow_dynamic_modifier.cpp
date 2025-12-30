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
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/waterflow_section_option.h"
#include "ui/base/utils/utils.h"

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/bridge/waterflow/water_flow_model_impl.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::WaterFlowModelImpl* GetWaterFlowModelImpl()
{
    static Framework::WaterFlowModelImpl instance;
    return &instance;
}
#endif
namespace NG {
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
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);


FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void ResetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, "");
}

void SetColumnsTemplate(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, value);
}

ArkUI_Int32 GetItemFillPolicy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<ArkUI_Int32>(WaterFlowModelNG::GetItemFillPolicy(frameNode));
}

void ResetItemFillPolicy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto itemFillPolicy = layoutProperty->GetItemFillPolicy();
    if (itemFillPolicy.has_value()) {
        WaterFlowModelNG::ResetItemFillPolicy(frameNode);
    }
}

void SetItemFillPolicy(ArkUINodeHandle node, int32_t itemFillPolicy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto fillPolicy = PresetFillType::BREAKPOINT_DEFAULT;
    switch (itemFillPolicy) {
        case INDEX_1:
            fillPolicy = PresetFillType::BREAKPOINT_SM1MD2LG3;
            break;
        case INDEX_2:
            fillPolicy = PresetFillType::BREAKPOINT_SM2MD3LG5;
            break;
        default:
            break;
    }
    WaterFlowModelNG::SetItemFillPolicy(frameNode, fillPolicy);
}

void ResetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, "");
}

void SetRowsTemplate(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, value);
}

void ResetWaterFlowEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, true);
}

void SetWaterFlowEnableScrollInteraction(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, value);
}

void SetColumnsGap(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* columnsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension columnsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        columnsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        columnsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetColumnsGap(frameNode, columnsGapDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* columnsGap = reinterpret_cast<ResourceObject*>(columnsGapRawPtr);
        auto columnsGapResObj = AceType::Claim(columnsGap);
        WaterFlowModelNG::ParseResObjColumnsGap(frameNode, columnsGapResObj);
    }
}

void ResetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));

    if (SystemProperties::ConfigChangePerform()) {
        WaterFlowModelNG::ParseResObjColumnsGap(frameNode, nullptr);
    }
}

void SetRowsGap(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* rowsGapRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension rowsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        rowsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        rowsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetRowsGap(frameNode, rowsGapDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* rowsGap = reinterpret_cast<ResourceObject*>(rowsGapRawPtr);
        auto rowsGapResObj = AceType::Claim(rowsGap);
        WaterFlowModelNG::ParseResObjRowsGap(frameNode, rowsGapResObj);
    }
}

void ResetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));

    if (SystemProperties::ConfigChangePerform()) {
        WaterFlowModelNG::ParseResObjRowsGap(frameNode, nullptr);
    }
}

void SetItemMinWidth(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMinWidthRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinWidth(frameNode, minWidthDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMinWidth = reinterpret_cast<ResourceObject*>(itemMinWidthRawPtr);
        auto itemMinWidthResObj = AceType::Claim(itemMinWidth);
        WaterFlowModelNG::ParseResObjItemMinWidth(frameNode, itemMinWidthResObj);
    }
}

void ResetItemMinWidth(ArkUINodeHandle node) {}

void SetItemMinHeight(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMinHeightRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinHeight(frameNode, minHeightDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMinHeight = reinterpret_cast<ResourceObject*>(itemMinHeightRawPtr);
        auto itemMinHeightResObj = AceType::Claim(itemMinHeight);
        WaterFlowModelNG::ParseResObjItemMinHeight(frameNode, itemMinHeightResObj);
    }
}

void ResetItemMinHeight(ArkUINodeHandle node) {}

void SetItemMaxWidth(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMaxWidthRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxWidth(frameNode, maxWidthDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMaxWidth = reinterpret_cast<ResourceObject*>(itemMaxWidthRawPtr);
        auto itemMaxWidthResObj = AceType::Claim(itemMaxWidth);
        WaterFlowModelNG::ParseResObjItemMaxWidth(frameNode, itemMaxWidthResObj);
    }
}

void ResetItemMaxWidth(ArkUINodeHandle node) {}

void SetItemMaxHeight(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMaxHeightRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxHeight(frameNode, maxHeightDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMaxHeight = reinterpret_cast<ResourceObject*>(itemMaxHeightRawPtr);
        auto itemMaxHeightResObj = AceType::Claim(itemMaxHeight);
        WaterFlowModelNG::ParseResObjItemMaxHeight(frameNode, itemMaxHeightResObj);
    }
}

void ResetItemMaxHeight(ArkUINodeHandle node) {}

void SetLayoutDirection(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, static_cast<FlexDirection>(direction));
}

void ResetLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, FlexDirection::COLUMN);
}

void SetWaterFlowNestedScroll(ArkUINodeHandle node, ArkUI_Int32 scrollForward, ArkUI_Int32 scrollBackward)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    WaterFlowModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetWaterFlowFriction(ArkUINodeHandle node, ArkUI_Float32 friction, void* frictionRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, friction);

    if (SystemProperties::ConfigChangePerform()) {
        auto* friction = reinterpret_cast<ResourceObject*>(frictionRawPtr);
        auto frictionResObj = AceType::Claim(friction);
        WaterFlowModelNG::ParseResObjFriction(frameNode, frictionResObj);
    }
}

void ResetWaterFlowFriction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, FRICTION_DEFAULT);
    if (SystemProperties::ConfigChangePerform()) {
        WaterFlowModelNG::ParseResObjFriction(frameNode, nullptr);
    }
}

void SetEdgeEffect(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetEdgeEffect(
        frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void ResetEdgeEffect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    ArkUI_Bool alwaysEnabled = false;
    WaterFlowModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, EffectEdge::ALL);
}

ArkUI_Int32 GetLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(WaterFlowModelNG::GetLayoutDirection(frameNode));
}

ArkUI_CharPtr GetColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = WaterFlowModelNG::GetColumnsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetRowsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = WaterFlowModelNG::GetRowsTemplate(frameNode);
    return g_strValue.c_str();
}

ArkUI_Float32 GetColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return WaterFlowModelNG::GetColumnsGap(frameNode);
}

ArkUI_Float32 GetRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return WaterFlowModelNG::GetRowsGap(frameNode);
}

void GetWaterFlowNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions options = WaterFlowModelNG::GetNestedScroll(frameNode);
    (*values)[0] = static_cast<ArkUI_Int32>(options.forward);
    (*values)[1] = static_cast<ArkUI_Int32>(options.backward);
}

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetCachedCount(frameNode, 1);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetCachedCount(frameNode);
}

void SetShowCached(ArkUINodeHandle node, ArkUI_Bool show)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetShowCached(frameNode, show);
}

void ResetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetShowCached(frameNode, false);
}

ArkUI_Bool GetShowCached(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return WaterFlowModelNG::GetShowCached(frameNode);
}

void SetWaterFlowSyncLoad(ArkUINodeHandle node, ArkUI_Bool syncLoad)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetSyncLoad(frameNode, syncLoad);
}

void ResetWaterFlowSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetSyncLoad(frameNode, true);
}

ArkUI_Bool GetWaterFlowSyncLoad(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetSyncLoad(frameNode);
}

void SetWaterFlowScrollBar(ArkUINodeHandle node, ArkUI_Int32 barState)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarMode(frameNode, static_cast<DisplayMode>(barState));
}

void ResetWaterFlowScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarMode(frameNode, DisplayMode::AUTO);
}

ArkUI_Int32 GetWaterFlowScrollBar(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarMode(frameNode);
}

void SetWaterFlowBarWidth(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarWidth(frameNode, value);
}

void ResetWaterFlowBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::ResetScrollBarWidth(frameNode);
}

ArkUI_Float32 GetWaterFlowBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarWidth(frameNode);
}

void CreateWaterFlowScrollBarColorWithResourceObj(ArkUINodeHandle node, void* colorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* colorPtr = reinterpret_cast<ResourceObject*>(colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    WaterFlowModelNG::ParseResObjScrollBarColor(frameNode, colorResObj);
}

void SetWaterFlowScrollBarColor(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarColor(frameNode, value);
}

void ResetWaterFlowScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::ResetScrollBarColor(frameNode);

    CreateWaterFlowScrollBarColorWithResourceObj(node, nullptr);
}

ArkUI_Uint32 GetWaterFlowScrollBarColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return WaterFlowModelNG::GetScrollBarColor(frameNode);
}

ArkUI_Int32 GetEdgeEffect(ArkUINodeHandle node, ArkUI_Int32 (*values)[3])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    (*values)[0] = static_cast<ArkUI_Int32>(WaterFlowModelNG::GetEdgeEffect(frameNode));
    (*values)[1] = static_cast<ArkUI_Int32>(WaterFlowModelNG::GetEdgeEffectAlways(frameNode));
    (*values)[2] = static_cast<ArkUI_Int32>(WaterFlowModelNG::GetEffectEdge(frameNode)); /* 2: param index */
    return 3; /* 3: param count */
}

ArkUI_Int32 GetEdgeEffectCJ(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    (*values)[INDEX_0] = WaterFlowModelNG::GetEdgeEffect(frameNode);
    (*values)[INDEX_1] = WaterFlowModelNG::GetEdgeEffectAlways(frameNode);
    return INDEX_2;
}

void SetWaterFlowSectionOptions(ArkUINodeHandle node, ArkUI_Int32 start, ArkUIWaterFlowSectionOption option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::ResetSections(frameNode);
}

ArkUI_WaterFlowSectionOption GetWaterFlowSectionOptions(ArkUINodeHandle node)
{
    ArkUI_WaterFlowSectionOption option;
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, option);
    auto sections = WaterFlowModelNG::GetOrCreateWaterFlowSections(frameNode);
    CHECK_NULL_RETURN(sections, option);
    auto newSection = sections->GetSectionInfo();
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMinWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMaxWidth(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMaxWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMinHeight(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMinHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Float32 GetItemMaxHeight(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetItemMaxHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Int32 GetWaterFlowEnableScrollInteraction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetScrollEnabled(frameNode);
}

ArkUI_Float32 GetWaterFlowFriction(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return WaterFlowModelNG::GetFriction(frameNode);
}
void SetScrollToIndex(
    ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment, float options)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> extraOffset = options;
    WaterFlowModelNG::SetScrollToIndex(frameNode, index, animation, alignment, extraOffset);
}

void SetWaterflowFooter(ArkUINodeHandle node, ArkUINodeHandle footer)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* footerNode = reinterpret_cast<FrameNode*>(footer);
    CHECK_NULL_VOID(footerNode);
    WaterFlowModelNG::SetWaterflowFooter(frameNode, footerNode);
}

void ResetWaterflowFooter(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetWaterflowFooter(frameNode, nullptr);
}

void SetFooterCallback(ArkUINodeHandle node, void* func)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto footerAction = *reinterpret_cast<std::function<void()>*>(func);
    CHECK_NULL_VOID(footerAction);
    WaterFlowModelNG::SetFooter(frameNode, std::move(footerAction));
}

void SetWaterFlowFlingSpeedLimit(ArkUINodeHandle node, ArkUI_Float32 maxSpeed)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFlingSpeedLimit(frameNode, maxSpeed);
}

void ResetWaterFlowFlingSpeedLimit(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFlingSpeedLimit(frameNode, -1.0);
}

ArkUINodeHandle GetScrollController(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = WaterFlowModelNG::GetOrCreateController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void SetWaterFlowScroller(ArkUINodeHandle node, ArkUINodeHandle controller, ArkUINodeHandle proxy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto scrollController = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller));
    CHECK_NULL_VOID(scrollController);
    auto scrollProxy = AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy));
    CHECK_NULL_VOID(scrollProxy);
    WaterFlowModelNG::SetScroller(frameNode, scrollController, scrollProxy);
}

ArkUI_Int32 GetWaterFlowLayoutMode(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return static_cast<int32_t>(WaterFlowModelNG::GetLayoutMode(frameNode));
}

void SetWaterFlowLayoutMode(ArkUINodeHandle node, ArkUI_Uint32 layoutMode)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN;
    WaterFlowModelNG::SetLayoutMode(frameNode, mode);
}

void ResetWaterFlowSections(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::ResetSections(frameNode);
}

void SetWaterFlowFadingEdge(
    ArkUINodeHandle node, ArkUI_Bool fadingEdge, ArkUI_Float32 fadingEdgeLengthValue, ArkUI_Int32 fadingEdgeLengthUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension fadingEdgeLengthDimension =
        Dimension(fadingEdgeLengthValue, static_cast<OHOS::Ace::DimensionUnit>(fadingEdgeLengthUnit));
    NG::ScrollableModelNG::SetFadingEdge(frameNode, fadingEdge, fadingEdgeLengthDimension);
}

void ResetWaterFlowFadingEdge(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::ScrollableModelNG::SetFadingEdge(frameNode, false, DEFAULT_FADING_EDGE_LENGTH);
}

ArkUINodeHandle CreateWaterFlow(ArkUI_Int32 nodeId)
{
    auto frameNode = WaterFlowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void Create()
{
    WaterFlowModelNG::CreateFrameNode();
}

void SetScrollEnabled(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, enabled);
}

void SetOnScroll(ArkUINodeHandle node, void* onScrollCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onScrollCallback);
    auto* onScroll = reinterpret_cast<std::function<void(const CalcDimension&, const ScrollState&)>*>(onScrollCallback);
    WaterFlowModelNG::SetOnScroll(frameNode, std::move(*onScroll));
}

void SetOnScrollStart(ArkUINodeHandle node, void* onScrollStartCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onScrollStartCallback);
    auto* onScrollStart = reinterpret_cast<std::function<void()>*>(onScrollStartCallback);
    WaterFlowModelNG::SetOnScrollStart(frameNode, std::move(*onScrollStart));
}

void SetOnScrollStop(ArkUINodeHandle node, void* onScrollStopCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onScrollStopCallback);
    auto* onScrollStop = reinterpret_cast<std::function<void()>*>(onScrollStopCallback);
    WaterFlowModelNG::SetOnScrollStop(frameNode, std::move(*onScrollStop));
}

void SetOnScrollIndex(ArkUINodeHandle node, void* onScrollIndexCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onScrollIndexCallback);
    auto* onScrollIndex = reinterpret_cast<std::function<void(const int32_t, const int32_t)>*>(onScrollIndexCallback);
    WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(*onScrollIndex));
}

void SetOnReachStart(ArkUINodeHandle node, void* onReachStartCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onReachStartCallback);
    auto* onReachStart = reinterpret_cast<std::function<void()>*>(onReachStartCallback);
    WaterFlowModelNG::SetOnReachStart(frameNode, std::move(*onReachStart));
}

void SetOnReachEnd(ArkUINodeHandle node, void* onReachEndCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onReachEndCallback);
    auto* onReachEnd = reinterpret_cast<std::function<void()>*>(onReachEndCallback);
    WaterFlowModelNG::SetOnReachEnd(frameNode, std::move(*onReachEnd));
}

void SetOnScrollFrameBegin(ArkUINodeHandle node, void* onScrollFrameBeginCallback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onScrollFrameBeginCallback);
    auto* onScrollFrameBegin =
        reinterpret_cast<std::function<ScrollFrameResult(const Dimension&, const ScrollState&)>*>(
            onScrollFrameBeginCallback);
    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, std::move(*onScrollFrameBegin));
}

void SetScrollBarColorNull(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollBarColor(frameNode, std::nullopt);
}

void SetScrollBarColorNullImpl(ArkUINodeHandle node) {}

void SetWaterflowFooterWithFrameNode(ArkUINodeHandle node, void* uiNodePtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::UINode* uiNode = reinterpret_cast<NG::UINode*>(uiNodePtr);
    WaterFlowModelNG::SetWaterflowFooterWithFrameNode(frameNode, AceType::Claim(uiNode));
}

void* CreateScrollBarProxy()
{
    auto proxy = WaterFlowModelNG::CreateScrollBarProxyStatic();
    proxy->IncRefCount();
    return AceType::RawPtr(proxy);
}

void SetOnWillScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
        SendArkUISyncEvent(&event);
        scrollRes.offset = Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    ScrollableModelNG::SetOnWillScroll(frameNode, std::move(onWillScroll));
}

void SetOnWaterFlowReachEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachEnd = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_REACH_END;
        SendArkUISyncEvent(&event);
    };
    WaterFlowModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}

void SetOnDidScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
        SendArkUISyncEvent(&event);
    };
    ScrollableModelNG::SetOnDidScroll(frameNode, std::move(setOnDidScroll));
}

void SetOnWaterFlowScrollStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStart = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_START;
        SendArkUISyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}

void SetOnWaterFlowScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollStop = [nodeId, node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_STOP;
        SendArkUISyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

void SetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
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
        SendArkUISyncEvent(&event);
        scrollRes.offset = usePx ? Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::PX)
                                 : Dimension(event.componentAsyncEvent.data[0].f32, DimensionUnit::VP);
        return scrollRes;
    };
    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, std::move(onScrollFrameBegin));
}

void SetOnWaterFlowScrollIndex(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onScrollIndex = [nodeId, node, extraParam](int32_t first, int32_t last) -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_SCROLL_INDEX;
        event.componentAsyncEvent.data[0].i32 = first;
        event.componentAsyncEvent.data[1].i32 = last;
        SendArkUISyncEvent(&event);
    };
    WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(onScrollIndex));
}
void SetOnWaterFlowReachStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto onReachStart = [node, extraParam]() -> void {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_WATER_FLOW_REACH_START;
        SendArkUISyncEvent(&event);
    };
    WaterFlowModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void ResetOnWillScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnWillScroll(frameNode, nullptr);
}
void ResetOnWaterFlowReachEnd(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnReachEnd(frameNode, nullptr);
}
void ResetOnDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ScrollableModelNG::SetOnDidScroll(frameNode, nullptr);
}
void ResetOnWaterFlowScrollStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollStart(frameNode, nullptr);
}
void ResetOnWaterFlowScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollStop(frameNode, nullptr);
}
void ResetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollFrameBegin(frameNode, nullptr);
}
void ResetOnWaterFlowReachStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnReachStart(frameNode, nullptr);
}

void SetOnWaterFlowScrollIndexCallBack(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (extraParam) {
        auto onScrollIndex = reinterpret_cast<ScrollIndexFunc*>(extraParam);
        WaterFlowModelNG::SetOnScrollIndex(frameNode, std::move(*onScrollIndex));
    } else {
        WaterFlowModelNG::SetOnScrollIndex(frameNode, nullptr);
    }
}

void ResetOnWaterFlowScrollIndex(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetOnScrollIndex(frameNode, nullptr);
}

void* GetEventSetHandler(uint32_t kind)
{
    static const ComponentAsyncEventHandler waterFlowNodeAsyncEventHandlers[] = {
        NG::SetOnWillScroll,
        NG::SetOnWaterFlowReachEnd,
        NG::SetOnDidScroll,
        NG::SetOnWaterFlowScrollStart,
        NG::SetOnWaterFlowScrollStop,
        NG::SetOnWaterFlowScrollFrameBegin,
        NG::SetOnWaterFlowScrollIndex,
        NG::SetOnWaterFlowReachStart,
    };
    if (kind >= sizeof(waterFlowNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(waterFlowNodeAsyncEventHandlers[kind]);
}

void* GetEventResetHandler(uint32_t kind)
{
    const ResetComponentAsyncEventHandler waterFlowNodeResetAsyncEventHandlers[] = {
        NG::ResetOnWillScroll,
        NG::ResetOnWaterFlowReachEnd,
        NG::ResetOnDidScroll,
        NG::ResetOnWaterFlowScrollStart,
        NG::ResetOnWaterFlowScrollStop,
        NG::ResetOnWaterFlowScrollFrameBegin,
        NG::ResetOnWaterFlowScrollIndex,
        NG::ResetOnWaterFlowReachStart,
    };
    if (kind >=
        sizeof(waterFlowNodeResetAsyncEventHandlers) / sizeof(ResetComponentAsyncEventHandler)) {
        TAG_LOGE(
            AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(waterFlowNodeResetAsyncEventHandlers[kind]);
}

#ifndef CROSS_PLATFORM
void SetRowsTemplateImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    GetWaterFlowModelImpl()->SetRowsTemplate(value);
}

void SetColumnsGapImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* columnsGapRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension columnsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        columnsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        columnsGapDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetColumnsGap(columnsGapDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* columnsGap = reinterpret_cast<ResourceObject*>(columnsGapRawPtr);
        auto columnsGapResObj = AceType::Claim(columnsGap);
        GetWaterFlowModelImpl()->ParseResObjColumnsGap(columnsGapResObj);
    }
}

void SetRowsGapImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* rowsGapRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension rowsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        rowsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        rowsGapDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetRowsGap(rowsGapDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* rowsGap = reinterpret_cast<ResourceObject*>(rowsGapRawPtr);
        auto rowsGapResObj = AceType::Claim(rowsGap);
        GetWaterFlowModelImpl()->ParseResObjRowsGap(rowsGapResObj);
    }
}

void SetItemMinWidthImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMinWidthRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minWidthDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetItemMinWidth(minWidthDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMinWidth = reinterpret_cast<ResourceObject*>(itemMinWidthRawPtr);
        auto itemMinWidthResObj = AceType::Claim(itemMinWidth);
        GetWaterFlowModelImpl()->ParseResObjItemMinWidth(itemMinWidthResObj);
    }
}

void SetItemMinHeightImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMinHeightRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minHeightDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetItemMinHeight(minHeightDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMinHeight = reinterpret_cast<ResourceObject*>(itemMinHeightRawPtr);
        auto itemMinHeightResObj = AceType::Claim(itemMinHeight);
        GetWaterFlowModelImpl()->ParseResObjItemMinHeight(itemMinHeightResObj);
    }
}

void SetItemMaxWidthImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMaxWidthRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxWidthDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetItemMaxWidth(maxWidthDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMaxWidth = reinterpret_cast<ResourceObject*>(itemMaxWidthRawPtr);
        auto itemMaxWidthResObj = AceType::Claim(itemMaxWidth);
        GetWaterFlowModelImpl()->ParseResObjItemMaxWidth(itemMaxWidthResObj);
    }
}

void SetItemMaxHeightImpl(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue, void* itemMaxHeightRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxHeightDimension = Dimension(value, unitEnum);
    }
    GetWaterFlowModelImpl()->SetItemMaxHeight(maxHeightDimension);

    if (SystemProperties::ConfigChangePerform()) {
        auto* itemMaxHeight = reinterpret_cast<ResourceObject*>(itemMaxHeightRawPtr);
        auto itemMaxHeightResObj = AceType::Claim(itemMaxHeight);
        GetWaterFlowModelImpl()->ParseResObjItemMaxHeight(itemMaxHeightResObj);
    }
}

void SetLayoutDirectionImpl(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    GetWaterFlowModelImpl()->SetLayoutDirection(static_cast<FlexDirection>(direction));
}

void SetWaterFlowNestedScrollImpl(ArkUINodeHandle node, ArkUI_Int32 scrollForward, ArkUI_Int32 scrollBackward)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    nestedOpt.forward = static_cast<NestedScrollMode>(scrollForward);
    nestedOpt.backward = static_cast<NestedScrollMode>(scrollBackward);
    GetWaterFlowModelImpl()->SetNestedScroll(nestedOpt);
}

void SetWaterFlowFrictionImpl(ArkUINodeHandle node, ArkUI_Float32 friction, void* frictionRawPtr)
{
    GetWaterFlowModelImpl()->SetFriction(friction);

    if (SystemProperties::ConfigChangePerform()) {
        auto* friction = reinterpret_cast<ResourceObject*>(frictionRawPtr);
        auto frictionResObj = AceType::Claim(friction);
        GetWaterFlowModelImpl()->ParseResObjFriction(frictionResObj);
    }
}

void SetEdgeEffectImpl(ArkUINodeHandle node, int32_t edgeEffect, ArkUI_Bool alwaysEnabled, ArkUI_Int32 edge)
{
    GetWaterFlowModelImpl()->SetEdgeEffect(
        static_cast<EdgeEffect>(edgeEffect), alwaysEnabled, static_cast<EffectEdge>(edge));
}

void SetCachedCountImpl(ArkUINodeHandle node, ArkUI_Int32 cachedCount)
{
    GetWaterFlowModelImpl()->SetCachedCount(cachedCount, false);
}

void SetWaterFlowScrollBarImpl(ArkUINodeHandle node, ArkUI_Int32 barState)
{
    GetWaterFlowModelImpl()->SetScrollBarMode(static_cast<DisplayMode>(barState));
}

void SetWaterFlowBarWidthImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    GetWaterFlowModelImpl()->SetScrollBarWidth(value);
}

void CreateWaterFlowScrollBarColorWithResourceObjImpl(ArkUINodeHandle node, void* colorRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto* colorPtr = reinterpret_cast<ResourceObject*>(colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    GetWaterFlowModelImpl()->ParseResObjScrollBarColor(colorResObj);
}

void SetWaterFlowScrollBarColorImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    GetWaterFlowModelImpl()->SetScrollBarColor(value);
}

ArkUI_Int32 GetEdgeEffectImpl(ArkUINodeHandle node, ArkUI_Int32 (*values)[3])
{
    (*values)[0] = static_cast<ArkUI_Int32>(GetWaterFlowModelImpl()->GetEdgeEffect());
    return 1; /* 3: param count */
}

void SetFooterCallbackImpl(ArkUINodeHandle node, void* func)
{
    auto footerAction = *reinterpret_cast<std::function<void()>*>(func);
    CHECK_NULL_VOID(footerAction);
    GetWaterFlowModelImpl()->SetFooter(std::move(footerAction));
}

ArkUINodeHandle GetScrollControllerImpl(ArkUINodeHandle node)
{
    auto controller = GetWaterFlowModelImpl()->CreateScrollController();
    controller->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

void SetWaterFlowScrollerImpl(ArkUINodeHandle node, ArkUINodeHandle controller, ArkUINodeHandle proxy)
{
    auto scrollController = AceType::Claim(reinterpret_cast<ScrollControllerBase*>(controller));
    CHECK_NULL_VOID(scrollController);
    auto scrollProxy = AceType::Claim(reinterpret_cast<ScrollProxy*>(proxy));
    CHECK_NULL_VOID(scrollProxy);
    GetWaterFlowModelImpl()->SetScroller(scrollController, scrollProxy);
}

void SetWaterFlowLayoutModeImpl(ArkUINodeHandle node, ArkUI_Uint32 layoutMode)
{
    WaterFlowLayoutMode mode = WaterFlowLayoutMode::TOP_DOWN;
    if (layoutMode >= static_cast<uint32_t>(WaterFlowLayoutMode::TOP_DOWN) &&
        layoutMode <= static_cast<uint32_t>(WaterFlowLayoutMode::SLIDING_WINDOW)) {
        mode = static_cast<WaterFlowLayoutMode>(layoutMode);
    }
    GetWaterFlowModelImpl()->SetLayoutMode(mode);
}

void ResetWaterFlowSectionsImpl(ArkUINodeHandle node)
{
    GetWaterFlowModelImpl()->ResetSections();
}

void CreateImpl()
{
    GetWaterFlowModelImpl()->Create();
}

void SetScrollEnabledImpl(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    GetWaterFlowModelImpl()->SetScrollEnabled(enabled);
}

void SetOnScrollImpl(ArkUINodeHandle node, void* onScrollCallback)
{
    CHECK_NULL_VOID(onScrollCallback);
    auto* onScroll = reinterpret_cast<std::function<void(const CalcDimension&, const ScrollState&)>*>(onScrollCallback);
    GetWaterFlowModelImpl()->SetOnScroll(std::move(*onScroll));
}

void SetOnScrollStartImpl(ArkUINodeHandle node, void* onScrollStartCallback)
{
    CHECK_NULL_VOID(onScrollStartCallback);
    auto* onScrollStart = reinterpret_cast<std::function<void()>*>(onScrollStartCallback);
    GetWaterFlowModelImpl()->SetOnScrollStart(std::move(*onScrollStart));
}

void SetOnScrollStopImpl(ArkUINodeHandle node, void* onScrollStopCallback)
{
    CHECK_NULL_VOID(onScrollStopCallback);
    auto* onScrollStop = reinterpret_cast<std::function<void()>*>(onScrollStopCallback);
    GetWaterFlowModelImpl()->SetOnScrollStop(std::move(*onScrollStop));
}

void SetOnScrollIndexImpl(ArkUINodeHandle node, void* onScrollIndexCallback)
{
    CHECK_NULL_VOID(onScrollIndexCallback);
    auto* onScrollIndex = reinterpret_cast<std::function<void(const int32_t, const int32_t)>*>(onScrollIndexCallback);
    GetWaterFlowModelImpl()->SetOnScrollIndex(std::move(*onScrollIndex));
}

void SetOnReachStartImpl(ArkUINodeHandle node, void* onReachStartCallback)
{
    CHECK_NULL_VOID(onReachStartCallback);
    auto* onReachStart = reinterpret_cast<std::function<void()>*>(onReachStartCallback);
    GetWaterFlowModelImpl()->SetOnReachStart(std::move(*onReachStart));
}

void SetOnReachEndImpl(ArkUINodeHandle node, void* onReachEndCallback)
{
    CHECK_NULL_VOID(onReachEndCallback);
    auto* onReachEnd = reinterpret_cast<std::function<void()>*>(onReachEndCallback);
    GetWaterFlowModelImpl()->SetOnReachEnd(std::move(*onReachEnd));
}

void SetOnScrollFrameBeginImpl(ArkUINodeHandle node, void* onScrollFrameBeginCallback)
{
    CHECK_NULL_VOID(onScrollFrameBeginCallback);
    auto* onScrollFrameBegin =
        reinterpret_cast<std::function<ScrollFrameResult(const Dimension&, const ScrollState&)>*>(
            onScrollFrameBeginCallback);
    GetWaterFlowModelImpl()->SetOnScrollFrameBegin(std::move(*onScrollFrameBegin));
}

void SetWaterflowFooterWithFrameNodeImpl(ArkUINodeHandle node, void* uiNodePtr)
{
    NG::UINode* uiNode = reinterpret_cast<NG::UINode*>(uiNodePtr);
    GetWaterFlowModelImpl()->SetFooterWithFrameNode(AceType::Claim(uiNode));
}

void* CreateScrollBarProxyImpl()
{
    auto proxy = GetWaterFlowModelImpl()->CreateScrollBarProxy();
    proxy->IncRefCount();
    return AceType::RawPtr(proxy);
}

void SetColumnsTemplateImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    GetWaterFlowModelImpl()->SetColumnsTemplate(value);
}

void ResetWaterFlowLayoutModeImpl(ArkUINodeHandle) {}

void ResetItemFillPolicyImpl(ArkUINodeHandle) {}

#endif
} // namespace
namespace NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIWaterFlowModifier modifierImpl = {
            .resetColumnsTemplate = nullptr,
            .setColumnsTemplate = SetColumnsTemplateImpl,
            .getItemFillPolicy = nullptr,
            .resetItemFillPolicy = ResetItemFillPolicyImpl,
            .setItemFillPolicy = nullptr,
            .resetRowsTemplate = nullptr,
            .setRowsTemplate = SetRowsTemplateImpl,
            .resetWaterFlowEnableScrollInteraction = nullptr,
            .setWaterFlowEnableScrollInteraction = nullptr,
            .setColumnsGap = SetColumnsGapImpl,
            .resetColumnsGap = nullptr,
            .setRowsGap = SetRowsGapImpl,
            .resetRowsGap = nullptr,
            .setItemMinWidth = SetItemMinWidthImpl,
            .resetItemMinWidth = nullptr,
            .setItemMaxWidth = SetItemMaxWidthImpl,
            .resetItemMaxWidth = nullptr,
            .setItemMinHeight = SetItemMinHeightImpl,
            .resetItemMinHeight = nullptr,
            .setItemMaxHeight = SetItemMaxHeightImpl,
            .resetItemMaxHeight = nullptr,
            .setLayoutDirection = SetLayoutDirectionImpl,
            .resetLayoutDirection = nullptr,
            .setWaterFlowNestedScroll = SetWaterFlowNestedScrollImpl,
            .resetWaterFlowNestedScroll = nullptr,
            .setWaterFlowFriction = SetWaterFlowFrictionImpl,
            .resetWaterFlowFriction = nullptr,
            .getLayoutDirection = nullptr,
            .getColumnsTemplate = nullptr,
            .getRowsTemplate = nullptr,
            .getColumnsGap = nullptr,
            .getRowsGap = nullptr,
            .getWaterFlowNestedScroll = nullptr,
            .setNodeAdapter = nullptr,
            .resetNodeAdapter = nullptr,
            .getNodeAdapter = nullptr,
            .setCachedCount = SetCachedCountImpl,
            .resetCachedCount = nullptr,
            .getCachedCount = nullptr,
            .setShowCached = nullptr,
            .resetShowCached = nullptr,
            .getShowCached = nullptr,
            .setSyncLoad = nullptr,
            .resetSyncLoad = nullptr,
            .getSyncLoad = nullptr,
            .setEdgeEffect = SetEdgeEffectImpl,
            .resetEdgeEffect = nullptr,
            .setWaterFlowScrollBar = SetWaterFlowScrollBarImpl,
            .resetWaterFlowScrollBar = nullptr,
            .getWaterFlowScrollBar = nullptr,
            .setWaterFlowScrollBarWidth = SetWaterFlowBarWidthImpl,
            .resetWaterFlowScrollBarWidth = nullptr,
            .getWaterFlowScrollBarWidth = nullptr,
            .setWaterFlowScrollBarColor = SetWaterFlowScrollBarColorImpl,
            .resetWaterFlowScrollBarColor = nullptr,
            .getWaterFlowScrollBarColor = nullptr,
            .getEdgeEffect = GetEdgeEffectImpl,
            .setSectionOption = nullptr,
            .resetSectionOption = nullptr,
            .getSectionOption = nullptr,
            .getItemMinWidth = nullptr,
            .getItemMaxWidth = nullptr,
            .getItemMinHeight = nullptr,
            .getItemMaxHeight = nullptr,
            .getWaterFlowEnableScrollInteraction = nullptr,
            .getWaterFlowFriction = nullptr,
            .setScrollToIndex = nullptr,
            .setWaterflowFooter = nullptr,
            .resetWaterflowFooter = nullptr,
            .getScrollController = GetScrollControllerImpl,
            .setWaterFlowScroller = SetWaterFlowScrollerImpl,
            .getWaterFlowLayoutMode = nullptr,
            .setWaterFlowLayoutMode = SetWaterFlowLayoutModeImpl,
            .resetWaterFlowLayoutMode = ResetWaterFlowLayoutModeImpl,
            .resetWaterFlowSections = ResetWaterFlowSectionsImpl,
            .setWaterFlowFadingEdge = nullptr,
            .resetWaterFlowFadingEdge = nullptr,
            .setOnWaterFlowScrollIndexCallBack = nullptr,
            .resetOnWaterFlowScrollIndex = nullptr,
            .createWaterFlowScrollBarColorWithResourceObj = CreateWaterFlowScrollBarColorWithResourceObjImpl,
            .createWaterFlow = nullptr,
            .create = CreateImpl,
            .setScrollEnabled = SetScrollEnabledImpl,
            .setOnScroll = SetOnScrollImpl,
            .setOnScrollStart = SetOnScrollStartImpl,
            .setOnScrollStop = SetOnScrollStopImpl,
            .setOnScrollIndex = SetOnScrollIndexImpl,
            .setOnReachStart = SetOnReachStartImpl,
            .setOnReachEnd = SetOnReachEndImpl,
            .setOnScrollFrameBegin = SetOnScrollFrameBeginImpl,
            .setScrollBarColorNull = SetScrollBarColorNullImpl,
            .setWaterflowFooterWithFrameNode = SetWaterflowFooterWithFrameNodeImpl,
            .setFooterCallback = SetFooterCallbackImpl,
            .createScrollBarProxy = CreateScrollBarProxyImpl,
            .getEventSetHandler = nullptr,
            .getEventResetHandler = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIWaterFlowModifier modifier = {
        .resetColumnsTemplate = ResetColumnsTemplate,
        .setColumnsTemplate = SetColumnsTemplate,
        .getItemFillPolicy = GetItemFillPolicy,
        .resetItemFillPolicy = ResetItemFillPolicy,
        .setItemFillPolicy = SetItemFillPolicy,
        .resetRowsTemplate = ResetRowsTemplate,
        .setRowsTemplate = SetRowsTemplate,
        .resetWaterFlowEnableScrollInteraction = ResetWaterFlowEnableScrollInteraction,
        .setWaterFlowEnableScrollInteraction = SetWaterFlowEnableScrollInteraction,
        .setColumnsGap = SetColumnsGap,
        .resetColumnsGap = ResetColumnsGap,
        .setRowsGap = SetRowsGap,
        .resetRowsGap = ResetRowsGap,
        .setItemMinWidth = SetItemMinWidth,
        .resetItemMinWidth = ResetItemMinWidth,
        .setItemMaxWidth = SetItemMaxWidth,
        .resetItemMaxWidth = ResetItemMaxWidth,
        .setItemMinHeight = SetItemMinHeight,
        .resetItemMinHeight = ResetItemMinHeight,
        .setItemMaxHeight = SetItemMaxHeight,
        .resetItemMaxHeight = ResetItemMaxHeight,
        .setLayoutDirection = SetLayoutDirection,
        .resetLayoutDirection = ResetLayoutDirection,
        .setWaterFlowNestedScroll = SetWaterFlowNestedScroll,
        .resetWaterFlowNestedScroll = ResetWaterFlowNestedScroll,
        .setWaterFlowFriction = SetWaterFlowFriction,
        .resetWaterFlowFriction = ResetWaterFlowFriction,
        .getLayoutDirection = GetLayoutDirection,
        .getColumnsTemplate = GetColumnsTemplate,
        .getRowsTemplate = GetRowsTemplate,
        .getColumnsGap = GetColumnsGap,
        .getRowsGap = GetRowsGap,
        .getWaterFlowNestedScroll = GetWaterFlowNestedScroll,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .getCachedCount = GetCachedCount,
        .setShowCached = SetShowCached,
        .resetShowCached = ResetShowCached,
        .getShowCached = GetShowCached,
        .setSyncLoad = SetWaterFlowSyncLoad,
        .resetSyncLoad = ResetWaterFlowSyncLoad,
        .getSyncLoad = GetWaterFlowSyncLoad,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setWaterFlowScrollBar = SetWaterFlowScrollBar,
        .resetWaterFlowScrollBar = ResetWaterFlowScrollBar,
        .getWaterFlowScrollBar = GetWaterFlowScrollBar,
        .setWaterFlowScrollBarWidth = SetWaterFlowBarWidth,
        .resetWaterFlowScrollBarWidth = ResetWaterFlowBarWidth,
        .getWaterFlowScrollBarWidth = GetWaterFlowBarWidth,
        .setWaterFlowScrollBarColor = SetWaterFlowScrollBarColor,
        .resetWaterFlowScrollBarColor = ResetWaterFlowScrollBarColor,
        .getWaterFlowScrollBarColor = GetWaterFlowScrollBarColor,
        .getEdgeEffect = GetEdgeEffect,
        .setSectionOption = SetWaterFlowSectionOptions,
        .resetSectionOption = ResetWaterFlowSectionOptions,
        .getSectionOption = GetWaterFlowSectionOptions,
        .getItemMinWidth = GetItemMinWidth,
        .getItemMaxWidth = GetItemMaxWidth,
        .getItemMinHeight = GetItemMinHeight,
        .getItemMaxHeight = GetItemMaxHeight,
        .getWaterFlowEnableScrollInteraction = GetWaterFlowEnableScrollInteraction,
        .getWaterFlowFriction = GetWaterFlowFriction,
        .setScrollToIndex = SetScrollToIndex,
        .setWaterflowFooter = SetWaterflowFooter,
        .resetWaterflowFooter = ResetWaterflowFooter,
        .getScrollController = GetScrollController,
        .setWaterFlowScroller = SetWaterFlowScroller,
        .getWaterFlowLayoutMode = GetWaterFlowLayoutMode,
        .setWaterFlowLayoutMode = SetWaterFlowLayoutMode,
        .resetWaterFlowLayoutMode = ResetWaterFlowLayoutMode,
        .resetWaterFlowSections = ResetWaterFlowSections,
        .setWaterFlowFadingEdge = SetWaterFlowFadingEdge,
        .resetWaterFlowFadingEdge = ResetWaterFlowFadingEdge,
        .setOnWaterFlowScrollIndexCallBack = SetOnWaterFlowScrollIndexCallBack,
        .resetOnWaterFlowScrollIndex = ResetOnWaterFlowScrollIndex,
        .createWaterFlowScrollBarColorWithResourceObj = CreateWaterFlowScrollBarColorWithResourceObj,
        .createWaterFlow = CreateWaterFlow,
        .create = Create,
        .setScrollEnabled = SetScrollEnabled,
        .setOnScroll = SetOnScroll,
        .setOnScrollStart = SetOnScrollStart,
        .setOnScrollStop = SetOnScrollStop,
        .setOnScrollIndex = SetOnScrollIndex,
        .setOnReachStart = SetOnReachStart,
        .setOnReachEnd = SetOnReachEnd,
        .setOnScrollFrameBegin = SetOnScrollFrameBegin,
        .setScrollBarColorNull = SetScrollBarColorNull,
        .setWaterflowFooterWithFrameNode = SetWaterflowFooterWithFrameNode,
        .setFooterCallback = SetFooterCallback,
        .createScrollBarProxy = CreateScrollBarProxy,
        .getEventSetHandler = GetEventSetHandler,
        .getEventResetHandler = GetEventResetHandler,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIWaterFlowModifier* GetCJUIWaterFlowModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIWaterFlowModifier modifier = {
        .resetColumnsTemplate = ResetColumnsTemplate,
        .setColumnsTemplate = SetColumnsTemplate,
        .resetRowsTemplate = ResetRowsTemplate,
        .setRowsTemplate = SetRowsTemplate,
        .resetWaterFlowEnableScrollInteraction = ResetWaterFlowEnableScrollInteraction,
        .setWaterFlowEnableScrollInteraction = SetWaterFlowEnableScrollInteraction,
        .setColumnsGap = SetColumnsGap,
        .resetColumnsGap = ResetColumnsGap,
        .setRowsGap = SetRowsGap,
        .resetRowsGap = ResetRowsGap,
        .setItemMinWidth = SetItemMinWidth,
        .resetItemMinWidth = ResetItemMinWidth,
        .setItemMaxWidth = SetItemMaxWidth,
        .resetItemMaxWidth = ResetItemMaxWidth,
        .setItemMinHeight = SetItemMinHeight,
        .resetItemMinHeight = ResetItemMinHeight,
        .setItemMaxHeight = SetItemMaxHeight,
        .resetItemMaxHeight = ResetItemMaxHeight,
        .setLayoutDirection = SetLayoutDirection,
        .resetLayoutDirection = ResetLayoutDirection,
        .setWaterFlowNestedScroll = SetWaterFlowNestedScroll,
        .resetWaterFlowNestedScroll = ResetWaterFlowNestedScroll,
        .setWaterFlowFriction = SetWaterFlowFriction,
        .resetWaterFlowFriction = ResetWaterFlowFriction,
        .getLayoutDirection = GetLayoutDirection,
        .getColumnsTemplate = GetColumnsTemplate,
        .getRowsTemplate = GetRowsTemplate,
        .getColumnsGap = GetColumnsGap,
        .getRowsGap = GetRowsGap,
        .getWaterFlowNestedScroll = GetWaterFlowNestedScroll,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .setCachedCount = SetCachedCount,
        .resetCachedCount = ResetCachedCount,
        .getCachedCount = GetCachedCount,
        .setEdgeEffect = SetEdgeEffect,
        .resetEdgeEffect = ResetEdgeEffect,
        .setWaterFlowScrollBar = SetWaterFlowScrollBar,
        .resetWaterFlowScrollBar = ResetWaterFlowScrollBar,
        .getWaterFlowScrollBar = GetWaterFlowScrollBar,
        .setWaterFlowScrollBarWidth = SetWaterFlowBarWidth,
        .resetWaterFlowScrollBarWidth = ResetWaterFlowBarWidth,
        .getWaterFlowScrollBarWidth = GetWaterFlowBarWidth,
        .setWaterFlowScrollBarColor = SetWaterFlowScrollBarColor,
        .resetWaterFlowScrollBarColor = ResetWaterFlowScrollBarColor,
        .getWaterFlowScrollBarColor = GetWaterFlowScrollBarColor,
        .getEdgeEffect = GetEdgeEffectCJ,
        .setSectionOption = SetWaterFlowSectionOptions,
        .resetSectionOption = ResetWaterFlowSectionOptions,
        .getSectionOption = GetWaterFlowSectionOptions,
        .getItemMinWidth = GetItemMinWidth,
        .getItemMaxWidth = GetItemMaxWidth,
        .getItemMinHeight = GetItemMinHeight,
        .getItemMaxHeight = GetItemMaxHeight,
        .getWaterFlowEnableScrollInteraction = GetWaterFlowEnableScrollInteraction,
        .getWaterFlowFriction = GetWaterFlowFriction,
        .setWaterflowFooter = SetWaterflowFooter,
        .resetWaterflowFooter = ResetWaterflowFooter,
        .setScrollToIndex = SetScrollToIndex,
        .setWaterFlowFlingSpeedLimit = SetWaterFlowFlingSpeedLimit,
        .resetWaterFlowFlingSpeedLimit = ResetWaterFlowFlingSpeedLimit,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace