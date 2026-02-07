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

#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"

namespace OHOS::Ace::NG {
void DynamicLayoutModelNG::UpdatePropertyFromLinearParam(
    const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params)
{
    auto linearParam = AceType::DynamicCast<LinearLayoutAlgorithmParam>(params);
    CHECK_NULL_VOID(linearParam);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, linearParam->GetSpace(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, linearParam->GetMainAxisAlign(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, linearParam->GetCrossAxisAlign(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, IsReverse, linearParam->IsReverse(), frameNode);
}

void DynamicLayoutModelNG::UpdatePropertyFromStackParam(
    const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params)
{
    auto stackParam = AceType::DynamicCast<StackLayoutAlgorithmParam>(params);
    CHECK_NULL_VOID(stackParam);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(StackLayoutProperty, Alignment, stackParam->GetAlignContent(), frameNode);
}

void DynamicLayoutModelNG::UpdatePropertyFromCustomParam(
    const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params)
{
    auto customParam = AceType::DynamicCast<CustomLayoutAlgorithmParam>(params);
    CHECK_NULL_VOID(customParam);
    CHECK_NULL_VOID(frameNode);
    auto dynamicLayoutPattern = frameNode->GetPattern<DynamicLayoutPattern>();
    CHECK_NULL_VOID(dynamicLayoutPattern);
    dynamicLayoutPattern->UpdateCustomLayoutAlgorithmParam(customParam);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void DynamicLayoutModelNG::UpdatePropertyFromGridParam(
    const RefPtr<NG::FrameNode> &frameNode, const RefPtr<AlgorithmParamBase>& params)
{
    auto gridParam = AceType::DynamicCast<GridLayoutAlgorithmParam>(params);
    CHECK_NULL_VOID(gridParam);
    CHECK_NULL_VOID(frameNode);

    // Set LazyGridLayoutProperty properties
    // Reference GridModelNG logic: ColumnsTemplate and ItemFillPolicy are mutually exclusive
    if (gridParam->GetItemFillPolicy().has_value()) {
        // Reset ColumnsTemplate when setting ItemFillPolicy
        ACE_RESET_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ItemFillPolicy,
            gridParam->GetItemFillPolicy().value(), frameNode);
    } else if (!gridParam->GetColumnsTemplate().empty()) {
        // Reset ItemFillPolicy when setting ColumnsTemplate
        ACE_RESET_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ItemFillPolicy, frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate,
            gridParam->GetColumnsTemplate(), frameNode);
    }

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap,
        gridParam->GetRowsGap(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap,
        gridParam->GetColumnsGap(), frameNode);

    // Set Pattern's DynamicLayout flag
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDynamicLayoutOptions(true);

    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(const RefPtr<FrameNode> &frameNode,
    const RefPtr<AlgorithmParamBase>& algorithmParams, NG::DynamicLayoutType type)
{
    if (updateLayoutPropertyFuncMap_.find(type) != updateLayoutPropertyFuncMap_.end()) {
        updateLayoutPropertyFuncMap_[type](frameNode, algorithmParams);
    }
}

std::unordered_map<DynamicLayoutType, UpdateLayoutPropertyFunc> DynamicLayoutModelNG::updateLayoutPropertyFuncMap_ = {
    { DynamicLayoutType::COLUMN_LAYOUT, &DynamicLayoutModelNG::UpdatePropertyFromLinearParam },
    { DynamicLayoutType::ROW_LAYOUT, &DynamicLayoutModelNG::UpdatePropertyFromLinearParam },
    { DynamicLayoutType::STACK_LAYOUT, &DynamicLayoutModelNG::UpdatePropertyFromStackParam },
    { DynamicLayoutType::CUSTOM_LAYOUT, &DynamicLayoutModelNG::UpdatePropertyFromCustomParam },
    { DynamicLayoutType::GRID_LAYOUT, &DynamicLayoutModelNG::UpdatePropertyFromGridParam },
};

void DynamicLayoutModelNG::Create(
    const RefPtr<AlgorithmParamBase>& params, NG::DynamicLayoutType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE(
        "Create[%s][self:%d][layoutType:%d]", "DynamicLayout", nodeId, static_cast<int32_t>(type));
    auto patternGenerator =
        [layoutType = type, params = params]() -> RefPtr<Pattern> {
        switch (layoutType) {
            case DynamicLayoutType::COLUMN_LAYOUT:
                return AceType::MakeRefPtr<LinearLayoutPattern>(true);
            case DynamicLayoutType::ROW_LAYOUT:
                return AceType::MakeRefPtr<LinearLayoutPattern>(false);
            case DynamicLayoutType::STACK_LAYOUT:
                return AceType::MakeRefPtr<StackPattern>();
            case DynamicLayoutType::CUSTOM_LAYOUT: {
                auto customParams = AceType::DynamicCast<CustomLayoutAlgorithmParam>(params);
                return AceType::MakeRefPtr<DynamicLayoutPattern>(customParams);
            }
            case DynamicLayoutType::GRID_LAYOUT: {
                auto gridParams = AceType::DynamicCast<GridLayoutAlgorithmParam>(params);
                auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
                // Set DynamicLayout flag
                pattern->SetDynamicLayoutOptions(true);
                return pattern;
            }
            default:
                return AceType::MakeRefPtr<DynamicLayoutPattern>();
        }
    };
    auto [frameNode, isInitialRender] =
        DynamicLayoutNode::GetOrCreateDynamicLayoutNode("DynamicLayout", nodeId, patternGenerator);
    stack->Push(frameNode);
    if (!isInitialRender && frameNode->GetLayoutType() != type) {
        auto pattern = patternGenerator();
        CHECK_NULL_VOID(pattern);
        frameNode->ReplacePattern(pattern);
    }
    UpdatePropertyFromAlgorithmParams(frameNode, params, type);
    frameNode->SetLayoutType(type);
}
} // namespace OHOS::Ace::NG