/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/lazy_water_flow_layout_modifier.h"

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#include "core/components_ng/pattern/list/list_properties.h"

namespace OHOS::Ace::NG {
namespace {
const std::string DEFAULT_COLUMNS_TEMPLATE = "1fr";
constexpr Dimension DEFAULT_COLUMNS_GAP = 0.0_fp;
constexpr Dimension DEFAULT_ROWS_GAP = 0.0_fp;
using VisibleIndexesChangeFunc = std::function<void(int32_t, int32_t)>;

FrameNode* GetLazyWaterFlowLayoutFrameNode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(frameNode->GetPattern<LazyWaterFlowLayoutPattern>(), nullptr);
    return frameNode;
}

Dimension ParseResourceLength(const ArkUIResourceLength* length)
{
    CHECK_NULL_RETURN(length, 0.0_px);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(length->unit);
    if (unitEnum == DimensionUnit::CALC) {
        // ArkUIResourceLength is a C ABI struct, so CALC strings may be absent on invalid input.
        CHECK_NULL_RETURN(length->string, 0.0_px);
        return CalcDimension(length->string, DimensionUnit::CALC);
    }
    return CalcDimension(length->value, unitEnum);
}

void SetVisibleIndexesChangeCallback(FrameNode* frameNode, void* extraParam)
{
    CHECK_NULL_VOID(frameNode);
    if (!extraParam) {
        LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(frameNode, nullptr);
        return;
    }
    // This helper follows LazyWaterFlow's bridge ABI contract: the bridge transfers ownership of a heap callback.
    std::unique_ptr<VisibleIndexesChangeFunc> onVisibleIndexesChange(
        reinterpret_cast<VisibleIndexesChangeFunc*>(extraParam));
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(frameNode, std::move(*onVisibleIndexesChange));
}
}

void SetLazyWaterFlowLayoutColumnsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(columnsGap);
    auto gap = ParseResourceLength(columnsGap);
    if (LessNotEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyWaterFlowLayoutModel::SetColumnGap(frameNode, gap);
}

void ResetLazyWaterFlowLayoutColumnsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyWaterFlowLayoutModel::SetColumnGap(frameNode, DEFAULT_COLUMNS_GAP);
}

void SetLazyWaterFlowLayoutRowsGap(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rowsGap);
    auto gap = ParseResourceLength(rowsGap);
    if (LessNotEqual(gap.Value(), 0.0)) {
        gap = 0.0_px;
    }
    LazyWaterFlowLayoutModel::SetRowGap(frameNode, gap);
}

void ResetLazyWaterFlowLayoutRowsGap(ArkUINodeHandle node)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyWaterFlowLayoutModel::SetRowGap(frameNode, DEFAULT_ROWS_GAP);
}

void SetLazyWaterFlowLayoutColumnsTemplate(ArkUINodeHandle node, const char* columnsTemplate)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(columnsTemplate);
    LazyVWaterFlowLayoutModel::SetColumnsTemplate(frameNode, std::string(columnsTemplate));
}

void ResetLazyWaterFlowLayoutColumnsTemplate(ArkUINodeHandle node)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyVWaterFlowLayoutModel::SetColumnsTemplate(frameNode, DEFAULT_COLUMNS_TEMPLATE);
}

void SetLazyWaterFlowLayoutOnVisibleIndexesChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SetVisibleIndexesChangeCallback(frameNode, extraParam);
}

void ResetLazyWaterFlowLayoutOnVisibleIndexesChange(ArkUINodeHandle node)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(frameNode, nullptr);
}

void SetLazyWaterFlowLayoutItemFillPolicy(ArkUINodeHandle node, ArkUI_Int32 policy)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (policy < static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT) ||
        policy > static_cast<int32_t>(PresetFillType::BREAKPOINT_SM2MD3LG5)) {
        policy = static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT);
    }
    LazyVWaterFlowLayoutModel::SetColumnsTemplate(frameNode, "");
    LazyVWaterFlowLayoutModel::SetItemFillPolicy(frameNode, static_cast<PresetFillType>(policy));
}

void ResetLazyWaterFlowLayoutItemFillPolicy(ArkUINodeHandle node)
{
    auto* frameNode = GetLazyWaterFlowLayoutFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LazyVWaterFlowLayoutModel::ResetItemFillPolicy(frameNode);
}

namespace NodeModifier {
const ArkUILazyWaterFlowLayoutModifier* GetLazyWaterFlowLayoutDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILazyWaterFlowLayoutModifier modifier = {
        .setColumnsGap = SetLazyWaterFlowLayoutColumnsGap,
        .resetColumnsGap = ResetLazyWaterFlowLayoutColumnsGap,
        .setRowsGap = SetLazyWaterFlowLayoutRowsGap,
        .resetRowsGap = ResetLazyWaterFlowLayoutRowsGap,
        .setColumnsTemplate = SetLazyWaterFlowLayoutColumnsTemplate,
        .resetColumnsTemplate = ResetLazyWaterFlowLayoutColumnsTemplate,
        .setOnVisibleIndexesChange = SetLazyWaterFlowLayoutOnVisibleIndexesChange,
        .resetOnVisibleIndexesChange = ResetLazyWaterFlowLayoutOnVisibleIndexesChange,
        .setItemFillPolicy = SetLazyWaterFlowLayoutItemFillPolicy,
        .resetItemFillPolicy = ResetLazyWaterFlowLayoutItemFillPolicy,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
