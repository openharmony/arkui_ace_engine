/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/dialog/dialog_event_hub.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void DialogEventHub::FireCancelEvent() const
{
    CHECK_NULL_VOID(onCancel_);
    onCancel_();
}

void DialogEventHub::FireSuccessEvent(int32_t buttonIdx)
{
    CHECK_NULL_VOID(onSuccess_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->GetTaskExecutor()->PostTask(
        [onSuccess = onSuccess_, buttonIdx] { onSuccess(0, buttonIdx); },
        TaskExecutor::TaskType::JS, "ArkUIDialogSuccessEvent", PriorityType::VIP);
}

} // namespace OHOS::Ace::NG
