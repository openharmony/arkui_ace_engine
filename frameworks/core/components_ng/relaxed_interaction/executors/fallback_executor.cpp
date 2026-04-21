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

#include "core/components_ng/relaxed_interaction/executors/fallback_executor.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/inspector.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

FallbackExecutor::FallbackExecutor(
    WeakPtr<PipelineContext> context, const std::string& identity, const std::string& body)
    : BaseExecutor(context), identity_(identity), body_(body)
{}

FallbackExecutor::FallbackExecutor(WeakPtr<PipelineContext> context, const int32_t identity, const std::string& body)
    : BaseExecutor(context), identity_(identity), body_(body)
{}

ExecutorResult FallbackExecutor::ExecuteStep()
{
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null, cannot query FrameNode");
        return ExecutorResult::FAILED;
    }

    RefPtr<AceType> uiNode;
    if (std::holds_alternative<std::int32_t>(identity_)) {
        uiNode = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(std::get<std::int32_t>(identity_));
    } else {
        auto rootNode = context->GetRootElement();
        if (!rootNode) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "Root node is null, cannot query FrameNode at coordinates");
            return ExecutorResult::FAILED;
        }
        uiNode = Inspector::GetInspectorByKey(rootNode, std::get<std::string>(identity_));
    }

    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
    if (!frameNode) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "FrameNode is null");
        return ExecutorResult::FAILED;
    }

    frameNode->OnRecvCommand(body_);
    return ExecutorResult::SUCCESS;
}

} // namespace OHOS::Ace::NG
