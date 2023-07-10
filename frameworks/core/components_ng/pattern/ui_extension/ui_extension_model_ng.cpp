/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void UIExtensionModelNG::Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG, nodeId,
        [wantWrap]() { return AceType::MakeRefPtr<UIExtensionPattern>(wantWrap); });
    stack->Push(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
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

void UIExtensionModelNG::SetOnReceive(std::function<void(const AAFwk::WantParams&)>&& onReceive)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    pattern->SetOnReceiveCallback(std::move(onReceive));
}

void UIExtensionModelNG::SetOnError(
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<UIExtensionPattern>();
    pattern->SetOnErrorCallback(std::move(onError));
}
} // namespace OHOS::Ace::NG
