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

#include "core/components_ng/event/error_reporter/general_interaction_error_reporter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
GeneralInteractionErrorReporter& GeneralInteractionErrorReporter::GetInstance()
{
    static GeneralInteractionErrorReporter instance;
    return instance;
}

void GeneralInteractionErrorReporter::Submit(
    const GeneralInteractionErrorInfo& generalEventErrorInfo, int32_t containerId)
{
    auto container = Container::GetContainer(containerId);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [generalEventErrorInfo]() { EventReport::ReportGeneralInteractionError(generalEventErrorInfo); },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIEventBehaviorReporter");
}
} // namespace OHOS::Ace::NG
