/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_node.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_pattern.h"
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> UIExtensionModelNG::Create(const std::string& bundleName, const std::string& abilityName,
    const std::map<std::string, std::string>& params, std::function<void(int32_t)>&& onRelease,
    std::function<void(int32_t, const std::string&, const std::string&)>&& onError)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<UIExtensionPattern>(); });
    auto wantWrap = WantWrap::CreateWantWrap(bundleName, abilityName);
    CHECK_NULL_RETURN(wantWrap, frameNode);
    wantWrap->SetWantParam(params);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->UpdateWant(wantWrap);
    pattern->SetOnReleaseCallback(std::move(onRelease));
    pattern->SetOnErrorCallback(std::move(onError));
    return frameNode;
}

RefPtr<FrameNode> UIExtensionModelNG::Create(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const InnerModalUIExtensionConfig& config)
{
    bool isAsyncModalBinding = config.isAsyncModalBinding;
    bool isModal = config.isModal;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        [isAsyncModalBinding, isModal]() {
            return AceType::MakeRefPtr<UIExtensionPattern>(false, isModal, isAsyncModalBinding);
        });
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    pattern->SetDensityDpi(config.isDensityFollowHost);
    pattern->SetIsWindowModeFollowHost(config.isWindowModeFollowHost);
    pattern->UpdateWant(want);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, frameNode);
    pipeline->AddWindowStateChangedCallback(nodeId);
    pattern->SetOnReleaseCallback(std::move(callbacks.onRelease));
    pattern->SetOnErrorCallback(std::move(callbacks.onError));
    pattern->SetOnResultCallback(std::move(callbacks.onResult));
    pattern->SetOnReceiveCallback(std::move(callbacks.onReceive));
    pattern->SetModalOnRemoteReadyCallback(std::move(callbacks.onRemoteReady));
    pattern->SetModalOnDestroy(std::move(callbacks.onDestroy));
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, frameNode);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
    return frameNode;
}

void UIExtensionModelNG::Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap,
    const std::map<PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap,
    bool transferringCaller, bool densityDpi, bool isWindowModeFollowHost)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        [transferringCaller]() { return AceType::MakeRefPtr<UIExtensionPattern>(transferringCaller); });
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPlaceholderMap(placeholderMap);
    pattern->SetDensityDpi(densityDpi);
    pattern->SetIsWindowModeFollowHost(isWindowModeFollowHost);
    pattern->UpdateWant(wantWrap);
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

// for EmbeddedComponent
void UIExtensionModelNG::Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, SessionType sessionType)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::EMBEDDED_COMPONENT_ETS_TAG, nodeId,
        [sessionType]() { return AceType::MakeRefPtr<UIExtensionPattern>(false, false, false, sessionType); });
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetWantWrap(wantWrap);
    if (frameNode->GetNodeStatus() == NodeStatus::NORMAL_NODE) {
        pattern->UpdateWant(wantWrap);
    }
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void UIExtensionModelNG::Create(const UIExtensionConfig& config)
{
    switch (config.sessionType) {
        case SessionType::SECURITY_UI_EXTENSION_ABILITY:
            CreateSecurityUIExtension(config);
            break;
        case SessionType::DYNAMIC_COMPONENT:
            CreateDynamicComponent(config);
            break;
        case SessionType::ISOLATED_COMPONENT:
            CreateIsolatedComponent(config);
            break;
        default:
            LOGW("The type uiextension is not supported");
    }
}

void UIExtensionModelNG::CreateDynamicComponent(const UIExtensionConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "CreateDynamicComponent");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = DynamicNode::GetOrCreateDynamicNode(
        V2::DYNAMIC_COMPONENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DynamicPattern>(); });
    auto pattern = frameNode->GetPattern<DynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBackgroundTransparent(config.backgroundTransparent);
    stack->Push(frameNode);
}

void UIExtensionModelNG::CreateIsolatedComponent(const UIExtensionConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "CreateIsolatedComponent");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::ISOLATED_COMPONENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    auto pattern = frameNode->GetPattern<IsolatedPattern>();
    CHECK_NULL_VOID(pattern);
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void UIExtensionModelNG::CreateSecurityUIExtension(const UIExtensionConfig& config)
{
    TAG_LOGI(AceLogTag::ACE_SECURITYUIEXTENSION, "CreateSecurityUIExtension");
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->Initialize(config);
    pattern->SetPlaceholderNode(config.placeholderNode);
    pattern->UpdateWant(config.wantWrap);
    pattern->SetDensityDpi(config.densityDpi);
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->AddDragFrameNode(nodeId, AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

void UIExtensionModelNG::InitializeDynamicComponent(const RefPtr<FrameNode>& frameNode, const std::string& hapPath,
    const std::string& abcPath, const std::string& entryPoint, void* runtime)
{
    auto pattern = frameNode->GetPattern<DynamicPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitializeDynamicComponent(hapPath, abcPath, entryPoint, runtime);
}

void UIExtensionModelNG::InitializeIsolatedComponent(
    const RefPtr<NG::FrameNode>& frameNode, const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime)
{
    auto pattern = frameNode->GetPattern<IsolatedPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitializeIsolatedComponent(wantWrap, runtime);
}

void UIExtensionModelNG::SetAdaptiveWidth(bool state)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IsolatedPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAdaptiveWidth(state);
}

void UIExtensionModelNG::SetAdaptiveHeight(bool state)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IsolatedPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAdaptiveHeight(state);
}

void UIExtensionModelNG::SetOnRemoteReady(std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnRemoteReadyCallback(std::move(onRemoteReady));
}

void UIExtensionModelNG::SetSecurityOnRemoteReady(
    std::function<void(const RefPtr<NG::SecurityUIExtensionProxy>&)>&& onRemoteReady)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRemoteReadyCallback(std::move(onRemoteReady));
    return;
}

void UIExtensionModelNG::SetOnRelease(std::function<void(int32_t)>&& onRelease)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReleaseCallback(std::move(onRelease));
}

void UIExtensionModelNG::SetOnResult(std::function<void(int32_t, const AAFwk::Want&)>&& onResult)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    pattern->SetOnResultCallback(std::move(onResult));
}

void UIExtensionModelNG::SetOnTerminated(
    std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated, NG::SessionType sessionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (sessionType == SessionType::SECURITY_UI_EXTENSION_ABILITY) {
        auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnTerminatedCallback(std::move(onTerminated));
        return;
    }

    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    pattern->SetOnTerminatedCallback(std::move(onTerminated));
}

void UIExtensionModelNG::SetOnReceive(
    std::function<void(const AAFwk::WantParams&)>&& onReceive, NG::SessionType sessionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (sessionType == SessionType::SECURITY_UI_EXTENSION_ABILITY) {
        auto eventHub = frameNode->GetOrCreateEventHub<UIExtensionHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnReceiveCallback(std::move(onReceive));
        return;
    }

    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    pattern->SetOnReceiveCallback(std::move(onReceive));
}

std::string UIExtensionModelNG::GetUiExtensionType(NG::SessionType sessionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, "");
    if (sessionType == SessionType::SECURITY_UI_EXTENSION_ABILITY) {
        auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
        CHECK_NULL_RETURN(pattern, "");
        return pattern->GetUiExtensionType();
    }
    return "";
}

void UIExtensionModelNG::SetOnError(
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError,
    NG::SessionType sessionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (sessionType == SessionType::SECURITY_UI_EXTENSION_ABILITY) {
        auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetOnErrorCallback(std::move(onError));
        return;
    }

    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void UIExtensionModelNG::SetPlatformOnError(
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<PlatformPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void UIExtensionModelNG::SetOnDrawReady(std::function<void()>&& onDrawReady)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnDrawReadyCallback(std::move(onDrawReady));
}
} // namespace OHOS::Ace::NG
