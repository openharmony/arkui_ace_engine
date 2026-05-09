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

#include "core/components_ng/relaxed_interaction/executors/smart_gesture_executor.h"

#include "base/log/log_wrapper.h"
#include "core/common/event_manager.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

SmartGestureExecutor::SmartGestureExecutor(WeakPtr<PipelineContext> context, SmartGestureTrigger trigger)
    : BaseExecutor(context)
{
    trigger_ = trigger;
}

ExecutorResult SmartGestureExecutor::ExecuteStep()
{
    auto context = context_.Upgrade();
    if (!context) {
        return ExecutorResult::FAILED;
    }
    auto eventManager = context->GetEventManager();
    if (!eventManager) {
        return ExecutorResult::FAILED;
    }
    auto smartGestureManager = eventManager->GetOrCreateSmartGestureManager();
    if (smartGestureManager) {
        return smartGestureManager->HandleTrigger(trigger_) ? ExecutorResult::SUCCESS : ExecutorResult::FAILED;
    }
    return ExecutorResult::FAILED;
}

std::string SmartGestureExecutor::GetType() const
{
    return "smart_gesture";
}

std::string SmartGestureExecutor::GetDescription() const
{
    return BaseExecutor::GetDescription();
}

bool SmartGestureExecutor::IsSingleStep() const
{
    return true;
}

} // namespace OHOS::Ace::NG
