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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DELAY_LOG_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DELAY_LOG_H
#include <cstdint>
#include "base/thread/task_executor.h"

namespace OHOS::Ace {
struct TaskTimeRecord {
    int64_t lastTaskTime = 0;
    int64_t currentTaskTime = 0;
    std::string taskName;
};

class ArkUIDelayLogTask {
public:
    static void PostReductionTask(
        std::function<void()> task, TaskTimeRecord& taskTimeRecord, uint32_t delayTime);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DELAY_LOG_H