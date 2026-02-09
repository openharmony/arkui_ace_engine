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
};

void DynamicLayoutModelNG::Create(
    const RefPtr<AlgorithmParamBase>& params, NG::DynamicLayoutType type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE(
        "Create[%s][self:%d][layoutType:%d]", "DynamicLayout", nodeId, static_cast<int32_t>(type));
    auto patternGenerator =
        [layoutType = type, params = AceType::DynamicCast<CustomLayoutAlgorithmParam>(params)]() -> RefPtr<Pattern> {
        switch (layoutType) {
            case DynamicLayoutType::COLUMN_LAYOUT:
                return AceType::MakeRefPtr<LinearLayoutPattern>(true);
            case DynamicLayoutType::ROW_LAYOUT:
                return AceType::MakeRefPtr<LinearLayoutPattern>(false);
            case DynamicLayoutType::STACK_LAYOUT:
                return AceType::MakeRefPtr<StackPattern>();
            case DynamicLayoutType::CUSTOM_LAYOUT:
                return AceType::MakeRefPtr<DynamicLayoutPattern>(params);
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