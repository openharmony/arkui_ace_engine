/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model_static.h"

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_node.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/arkts_dynamic_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> DynamicModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = DynamicNode::GetOrCreateDynamicNode(
        V2::DYNAMIC_COMPONENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ArktsDynamicPattern>(); });
    return frameNode;
}

void* DynamicModelStatic::CreateFrameNodeByIncRefCount(int32_t nodeId)
{
    auto frameNode = NG::DynamicModelStatic::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void DynamicModelStatic::SetDynamicParam(FrameNode* frameNode, const DynamicParam& param)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArktsDynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDynamicParam(param);
}

void DynamicModelStatic::SetOnError(FrameNode* frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArktsDynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void DynamicModelStatic::SetIsReportFrameEvent(FrameNode* frameNode, bool isReportFrameEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ArktsDynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsReportFrameEvent(isReportFrameEvent);
}
} // namespace OHOS::Ace::NG
