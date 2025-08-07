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

#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_model_static.h"

#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> SecurityUIExtensionStatic::CreateSecurityUIExtensionComponent(
    int32_t nodeId, NG::SessionType sessionType)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<SecurityUIExtensionPattern>(); });
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode);
    return frameNode;
}

void SecurityUIExtensionStatic::UpdateSecurityUecConfig(
    FrameNode* frameNode, bool isTransferringCaller, bool densityDpi, bool isWindowModeFollowHost,
    const std::map<PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetIsTransferringCaller() != isTransferringCaller) {
        pattern->SetIsTransferringCaller(isTransferringCaller);
    }
    pattern->SetDensityDpi(densityDpi);
    pattern->SetIsWindowModeFollowHost(isWindowModeFollowHost);
}

void SecurityUIExtensionStatic::UpdateSecurityWant(FrameNode* frameNode, const AAFwk::Want& want)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetWantWrap(AceType::MakeRefPtr<OHOS::Ace::WantWrapOhos>(want));
}

void SecurityUIExtensionStatic::SetSecurityOnError(FrameNode* frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    auto pattern = frameNode->GetPattern<SecurityUIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void SecurityUIExtensionStatic::SetSecurityOnReceive(FrameNode* frameNode,
    std::function<void(const AAFwk::WantParams&)>&& onReceive)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReceiveCallback(std::move(onReceive));
}

void SecurityUIExtensionStatic::SetSecurityOnRelease(
    FrameNode* frameNode, std::function<void(int32_t)>&& onRelease)
{
    LOGE("UIExtensionStatic SecurityUEC not support OnRelease.");
}

void SecurityUIExtensionStatic::SetSecurityOnRemoteReady(FrameNode* frameNode,
    std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>&& onRemoteReady)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRemoteReadyCallback(std::move(onRemoteReady));
}

void SecurityUIExtensionStatic::SetSecurityOnResult(
    FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult)
{
    LOGE("UIExtensionStatic SecurityUEC not support OnResult.");
}

void SecurityUIExtensionStatic::SetSecurityOnTerminated(FrameNode* frameNode,
    std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTerminatedCallback(std::move(onTerminated));
}

void SecurityUIExtensionStatic::SetSecurityOnDrawReady(
    FrameNode* frameNode, std::function<void()>&& onDrawReady)
{
    LOGE("UIExtensionStatic SecurityUEC not support OnDrawReady.");
}
} // namespace OHOS::Ace::NG