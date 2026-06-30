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

#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> LazyDynamicLayoutModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyDynamicLayout", nodeId);
    
    auto patternGenerator = []() -> RefPtr<Pattern> {
        auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
        return AceType::MakeRefPtr<LazyDynamicLayoutPattern>(customParams);
    };
    
    auto [frameNode, isInitialRender] =
        DynamicLayoutNode::GetOrCreateDynamicLayoutNode("LazyDynamicLayout", nodeId, patternGenerator);
    return frameNode;
}

void LazyDynamicLayoutModelStatic::SetParams(
    FrameNode* frameNode, const RefPtr<LazyCustomLayoutAlgorithmParam>& params)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(params);
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateCustomLayoutAlgorithmParam(params);
}

void LazyDynamicLayoutModelStatic::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    customParams->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyDynamicLayoutModelStatic::SetAdjustedOffset(FrameNode* frameNode, float adjustedOffset)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    customParams->SetAdjustedOffset(adjustedOffset);
}

void LazyDynamicLayoutModelStatic::SetInActiveChildren(
    FrameNode* frameNode, const std::vector<int32_t>& inActiveChildren)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    CHECK_NULL_VOID(customParams);
    customParams->SetInActiveChildren(inActiveChildren);
}

} // namespace OHOS::Ace::NG