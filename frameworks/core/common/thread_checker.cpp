/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/common/thread_checker.h"

#include "core/common/container.h"

namespace OHOS::Ace {

bool CheckThread(TaskExecutor::TaskType threadType)
{
    if (!Container::IsCurrentUseNewPipeline() && threadType == TaskExecutor::TaskType::PLATFORM) {
        return Container::CurrentId() == INSTANCE_ID_PLATFORM;
    }
    auto taskExecutor = Container::CurrentTaskExecutor();
    if (taskExecutor) {
        return taskExecutor->WillRunOnCurrentThread(threadType);
    }
    LOGI("checkThread: null taskExecutor, check id:%{public}d", Container::CurrentId());
    return false;
}

} // namespace OHOS::Ace