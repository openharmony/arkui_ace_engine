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

#ifndef FOUNDATION_ARKUI_FRAMEWORKS_CORE_COMMON_ANR_THREAD_H
#define FOUNDATION_ARKUI_FRAMEWORKS_CORE_COMMON_ANR_THREAD_H

#include <functional>
#include <cstdint>
#include <string>

#include "base/thread/task_executor.h"

namespace OHOS::Ace {
class AnrThread {

public:
    static void Start();
    static void Stop();
    using Task = std::function<void()>;
    static bool PostTaskToTaskRunner(
        Task&& task, uint32_t delayTime, const std::string& name, PriorityType priorityType);
};
} // namespace OHOS::Ace
#endif
