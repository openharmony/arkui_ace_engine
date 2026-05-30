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

#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"

namespace OHOS::Ace::NG {

void LazyDynamicLayoutModelNG::UpdatePropertyFromCustomParam(
    const RefPtr<FrameNode>& frameNode, const RefPtr<LazyCustomLayoutAlgorithmParam>& customParams)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(customParams);
    auto lazyDynamicLayoutPattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(lazyDynamicLayoutPattern);
    lazyDynamicLayoutPattern->UpdateCustomLayoutAlgorithmParam(customParams);
}

void LazyDynamicLayoutModelNG::SetOnVisibleIndexesChange(
    FrameNode* frameNode, OnVisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto lazyDynamicLayoutPattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(lazyDynamicLayoutPattern);
    auto customParams = lazyDynamicLayoutPattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    customParams->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyDynamicLayoutModelNG::SetAdjustedOffset(FrameNode* frameNode, float adjustedOffset)
{
    CHECK_NULL_VOID(frameNode);
    auto lazyDynamicLayoutPattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(lazyDynamicLayoutPattern);
    auto customParams = lazyDynamicLayoutPattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    auto lazyParams = AceType::DynamicCast<LazyCustomLayoutAlgorithmParam>(customParams);
    CHECK_NULL_VOID(lazyParams);
    lazyParams->SetAdjustedOffset(adjustedOffset);
}

void LazyDynamicLayoutModelNG::SetInActiveChildren(FrameNode* frameNode, const std::vector<int32_t>& inActiveChildren)
{
    CHECK_NULL_VOID(frameNode);
    auto lazyDynamicLayoutPattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(lazyDynamicLayoutPattern);
    auto customParams = lazyDynamicLayoutPattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    customParams->SetInActiveChildren(inActiveChildren);
}

void LazyDynamicLayoutModelNG::Create(const RefPtr<LazyCustomLayoutAlgorithmParam>& customParams)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyDynamicLayout", nodeId);
    
    auto patternGenerator = [customParams]() -> RefPtr<Pattern> {
        return AceType::MakeRefPtr<LazyDynamicLayoutPattern>(customParams);
    };
    
    auto [frameNode, isInitialRender] =
        DynamicLayoutNode::GetOrCreateDynamicLayoutNode("LazyDynamicLayout", nodeId, patternGenerator);
    stack->Push(frameNode);
    
    if (!isInitialRender) {
        auto pattern = patternGenerator();
        CHECK_NULL_VOID(pattern);
        frameNode->ReplacePattern(pattern);
    }

    UpdatePropertyFromCustomParam(frameNode, customParams);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG