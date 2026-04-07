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

#include "core/components_ng/relaxed_interaction/executors/strict_content_switch_executor.h"

#include "base/log/log_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

StrictContentSwitchExecutor::StrictContentSwitchExecutor(WeakPtr<PipelineContext> context, const std::string mode,
    const std::string direction, const uint32_t count, const PointF& coordinates)
    : BaseExecutor(context), mode_(mode), direction_(direction), count_(count), coordinates_(coordinates)
{}

ExecutorResult StrictContentSwitchExecutor::ExecuteStep()
{
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "Pipeline context is null");
        return ExecutorResult::FAILED;
    }

    auto frameNode = FindFrameNode(coordinates_.GetX(), coordinates_.GetY());
    if (!frameNode) {
        return ExecutorResult::FAILED;
    }

    return TriggerContentSwitch(frameNode);
}

ExecutorResult StrictContentSwitchExecutor::TriggerContentSwitch(const RefPtr<FrameNode> frameNode)
{
    return ExecutorResult::SUCCESS;
}

} // namespace OHOS::Ace::NG
