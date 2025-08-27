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

#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_adapter.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_hub.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "parameters.h"

namespace {
const char ENABLE_DEBUG_PREVIEW_UIEXTENSION_KEY[] = "persist.ace.debug.preview.uiextension.enabled";
bool IsDebugPreviewUIextensionEnabled()
{
    return OHOS::system::GetParameter(ENABLE_DEBUG_PREVIEW_UIEXTENSION_KEY, "false") == "true";
}
}
namespace OHOS::Ace::NG {
void PreviewUIExtensionAdapter::Create(const NG::UIExtensionConfig& config)
{
    if (!IsDebugPreviewUIextensionEnabled()) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Initialize(config);
    pattern->SetPlaceholderNode(config.placeholderNode);
    pattern->UpdateWant(config.wantWrap);
    pattern->SetDensityDpi(config.densityDpi);
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
}
RefPtr<FrameNode> PreviewUIExtensionAdapter::CreatePreviewUIExtensionNode(const NG::UIExtensionConfig& config)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<PreviewUIExtensionPattern>(); });
    auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    pipeline->AddWindowStateChangedCallback(nodeId);
    return frameNode;
}

void PreviewUIExtensionAdapter::UpdatePreviewUIExtensionConfig(const RefPtr<FrameNode>& frameNode,
    const NG::UIExtensionConfig& config)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Initialize(config);
    pattern->SetPlaceholderNode(config.placeholderNode);
    pattern->UpdateWant(config.wantWrap);
    pattern->SetDensityDpi(config.densityDpi);
}

void PreviewUIExtensionAdapter::SetWant(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateWant(wantWrap);
}

void PreviewUIExtensionAdapter::SetOnRemoteReady(const RefPtr<FrameNode>& frameNode,
    std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onRemoteReady)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRemoteReadyCallback(std::move(onRemoteReady));
    return;
}

void PreviewUIExtensionAdapter::SetOnTerminated(const RefPtr<FrameNode>& frameNode,
    std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTerminatedCallback(std::move(onTerminated));
}

void PreviewUIExtensionAdapter::SetOnReceive(const RefPtr<FrameNode>& frameNode,
    std::function<void(const AAFwk::WantParams&)>&& onReceive)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReceiveCallback(std::move(onReceive));
}

void PreviewUIExtensionAdapter::SetOnError(const RefPtr<FrameNode>& frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}
} // namespace OHOS::Ace::NG