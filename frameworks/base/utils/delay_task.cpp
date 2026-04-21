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

#include "base/utils/delay_task.h"
#include "base/utils/utils.h"
#include "base/utils/time_util.h"

namespace OHOS::Ace {
void ArkUIDelayLogTask::PostReductionTask(
    std::function<void()> task, TaskTimeRecord& taskTimeRecord, uint32_t delayTime)
{
    CHECK_NULL_VOID(task);
    taskTimeRecord.currentTaskTime = GetCurrentTimestamp();
    if (delayTime == 0|| taskTimeRecord.lastTaskTime == 0 ||
        (taskTimeRecord.currentTaskTime - taskTimeRecord.lastTaskTime) >= static_cast<int64_t>(delayTime)) {
        taskTimeRecord.lastTaskTime = taskTimeRecord.currentTaskTime;
        task();
    }
    LOGD("ArkUIDelayLogTask::PostReductionTask task %{public}s lastTaskTime:%{public}s",
        taskTimeRecord.taskName.c_str(), ConvertTimestampToStr(taskTimeRecord.lastTaskTime).c_str());
}
}