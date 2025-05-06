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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_adapter.h"

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> UIExtensionAdapter::CreateEmbeddedComponent(
    int32_t nodeId, const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    auto* stack = ViewStackProcessor::GetInstance();
    SessionType sessionType = SessionType::EMBEDDED_UI_EXTENSION;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::EMBEDDED_COMPONENT_ETS_TAG, nodeId,
        [sessionType]() { return AceType::MakeRefPtr<UIExtensionPattern>(false, false, false, sessionType); });
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->SetWantWrap(wantWrap);
    if (frameNode->GetNodeStatus() == NodeStatus::NORMAL_NODE) {
        pattern->UpdateWant(wantWrap);
    }
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, frameNode);
    pipeline->AddWindowStateChangedCallback(nodeId);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, frameNode);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
    return frameNode;
}

void UIExtensionAdapter::SetEmbeddedComponentWant(FrameNode* frameNode, const AAFwk::Want& want)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateWant(want);
}

void UIExtensionAdapter::SetEmbeddedComponentOnError(FrameNode* frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void UIExtensionAdapter::SetEmbeddedComponentOnTerminated(
    FrameNode* frameNode, std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnTerminatedCallback(std::move(onTerminated));
}
} // namespace OHOS::Ace::NG