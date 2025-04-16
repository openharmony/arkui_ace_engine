/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_adapter.h"

#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> UIExtensionAdapter::CreateFrameNode(
    int32_t nodeId, NG::SessionType sessionType)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId, [sessionType] () {
            return AceType::MakeRefPtr<UIExtensionPattern>(false, false, false, sessionType);
        });
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_RETURN(pattern, frameNode);
    return frameNode;
}

void UIExtensionAdapter::UpdateUecConfig(
    FrameNode* frameNode, bool isTransferringCaller, bool densityDpi)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetIsTransferringCaller() != isTransferringCaller) {
        pattern->SetIsTransferringCaller(isTransferringCaller);
    }
    pattern->SetDensityDpi(densityDpi);
}

void UIExtensionAdapter::UpdateWant(FrameNode* frameNode, const AAFwk::Want& want)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(frameNode->GetPattern());
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetWantWrap(AceType::MakeRefPtr<OHOS::Ace::WantWrapOhos>(want));
}

void UIExtensionAdapter::SetOnError(FrameNode* frameNode,
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnErrorCallback(std::move(onError));
}

void UIExtensionAdapter::SetOnReceive(FrameNode* frameNode,
    std::function<void(const AAFwk::WantParams&)>&& onReceive)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReceiveCallback(std::move(onReceive));
}

void UIExtensionAdapter::SetOnRelease(
    FrameNode* frameNode, std::function<void(int32_t)>&& onRelease)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnReleaseCallback(std::move(onRelease));
}

void UIExtensionAdapter::SetOnRemoteReady(FrameNode* frameNode,
    std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnRemoteReadyCallback(std::move(onRemoteReady));
}

void UIExtensionAdapter::SetOnResult(
    FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnResultCallback(std::move(onResult));
}

void UIExtensionAdapter::SetOnTerminated(FrameNode* frameNode,
    std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnTerminatedCallback(std::move(onTerminated));
}
} // namespace OHOS::Ace::NG