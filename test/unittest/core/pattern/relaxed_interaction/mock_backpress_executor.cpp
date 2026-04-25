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

#include "core/components_ng/relaxed_interaction/executors/backpress_executor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

BackpressExecutor::BackpressExecutor(WeakPtr<PipelineContext> context) : BaseExecutor(context) {}

ExecutorResult BackpressExecutor::ExecuteStep()
{
    return ExecutorResult::FAILED;
}

} // namespace OHOS::Ace::NG
