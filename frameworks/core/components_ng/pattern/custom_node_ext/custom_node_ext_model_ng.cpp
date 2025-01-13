/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> CustomNodeExtModelNG::GetOrCreateFrameNode(const std::string& tag)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        tag, nodeId, []() { return AceType::MakeRefPtr<CustomNodeExtPattern>(); });
    stack->Push(frameNode);
    return frameNode;
}

RefPtr<FrameNode> CustomNodeExtModelNG::CreateFrameNode(const std::string& tag)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<CustomNodeExtPattern>());
    return frameNode;
}

void CustomNodeExtModelNG::SetMeasureCallback(
    FrameNode* frameNode, std::function<void(LayoutConstraintF constraints)>&& onMeasure)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMeasureCallback(std::move(onMeasure));
}

void CustomNodeExtModelNG::SetLayoutCallback(FrameNode* frameNode, std::function<void(RectF rect)>&& onLayout)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLayoutCallback(std::move(onLayout));
}

void CustomNodeExtModelNG::SetContentDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetContentDrawCallback(std::move(onDraw));
}

void CustomNodeExtModelNG::SetForegroundDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetForegroundDrawCallback(std::move(onDraw));
}

void CustomNodeExtModelNG::SetOverlayDrawCallback(FrameNode* frameNode, DrawFunction&& onDraw)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOverlayDrawCallback(std::move(onDraw));
}

void CustomNodeExtModelNG::SetOnConfigUpdateCallback(
    FrameNode* frameNode, std::function<void(ConfigurationType configType)>&& onConfigUpdate)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnConfigUpdateCallback(std::move(onConfigUpdate));
}

void CustomNodeExtModelNG::SetOnModifyDoneCallback(FrameNode* frameNode, std::function<void()>&& onModifyDone)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnModifyDoneCallback(std::move(onModifyDone));
}

void CustomNodeExtModelNG::SetOnDirtyLayoutWrapperSwap(
    FrameNode* frameNode, std::function<void(const DirtySwapConfig& config)>&& onDirtySwap)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnDirtyLayoutWrapperSwap(std::move(onDirtySwap));
}

void CustomNodeExtModelNG::SetIsAtomic(FrameNode* frameNode, bool isAtomic)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomNodeExtPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsAtomic(isAtomic);
}
} // OHOS::Ace::NG