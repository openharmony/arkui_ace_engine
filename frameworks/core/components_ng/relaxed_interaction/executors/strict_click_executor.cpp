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

#include "core/components_ng/relaxed_interaction/executors/strict_click_executor.h"

#include <string>

#include "base/log/log_wrapper.h"
#include "core/components_ng/relaxed_interaction/utils/relaxed_event_factory.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

StrictClickExecutor::StrictClickExecutor(WeakPtr<PipelineContext> context, const PointF& coordinates)
    : BaseExecutor(context), coordinates_(coordinates) {}

ExecutorResult StrictClickExecutor::ExecuteStep()
{
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "StrictClickExecutor ExecuteStep begin.");
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGE(AceLogTag::ACE_UIEVENT, "Pipeline context is null");
        return ExecutorResult::FAILED;
    }

    // Use FrameNodeFinder to query FrameNode at coordinates
    auto result = FindFrameNode(coordinates_.GetX(), coordinates_.GetY(), ClickRecognizerPred());
    if (!result.GetNode()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "No FrameNode found at coordinates (%{private}.2f, %{private}.2f)",
                 coordinates_.GetX(), coordinates_.GetY());
        return ExecutorResult::FAILED;
    }
    if (!result.GetClickFunc()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "StrictClickExecutor GetClickFun failed.");
        return ExecutorResult::FAILED;
    }

    auto info = RelaxedEventFactory::CreateClickGestureEvent(result.GetNode());
    result.GetClickFunc()(info);
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "StrictClickExecutor ExecuteStep end.");
    return ExecutorResult::SUCCESS;
}

} // namespace OHOS::Ace::NG