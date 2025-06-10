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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PREVIEW_UI_EXTENSION_ADAPTER_H

#include <memory>
#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
struct ModalUIExtensionCallbacks;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class ACE_EXPORT PreviewUIExtensionAdapter {
public:
    static inline PreviewUIExtensionAdapter* GetInstance()
    {
        if (!Container::IsCurrentUseNewPipeline()) {
            LOGE("Get PreviewUIExtension in non NewPipeline.");
        }
        static PreviewUIExtensionAdapter instance;
        return &instance;
    }
    ~PreviewUIExtensionAdapter() = default;

    RefPtr<FrameNode> CreatePreviewUIExtensionNode(const NG::UIExtensionConfig& config)
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
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_RETURN(dragDropManager, nullptr);
        dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
        return frameNode;
    }

    void UpdatePreviewUIExtensionConfig(const RefPtr<FrameNode>& frameNode,
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
    
    void SetWant(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
    {
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateWant(wantWrap);
    }

    void SetOnRemoteReady(const RefPtr<FrameNode>& frameNode,
        std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onRemoteReady)
    {
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnRemoteReadyCallback(std::move(onRemoteReady));
        return;
    }

    void SetOnTerminated(const RefPtr<FrameNode>& frameNode,
        std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
    {
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnTerminatedCallback(std::move(onTerminated));
    }
    
    void SetOnReceive(const RefPtr<FrameNode>& frameNode,
        std::function<void(const AAFwk::WantParams&)>&& onReceive)
    {
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnReceiveCallback(std::move(onReceive));
    }

    void SetOnError(const RefPtr<FrameNode>& frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
    {
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<PreviewUIExtensionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetOnErrorCallback(std::move(onError));
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
