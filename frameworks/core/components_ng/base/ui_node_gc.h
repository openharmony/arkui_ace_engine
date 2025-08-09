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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_GC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_GC_H

#include <cstdint>
#include <queue>
#include <vector>

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace::NG {
class UINode;
class UiNodeGc final {
public:
    static void OnReleaseFunc(OHOS::Ace::NG::UINode* frameNodeRawPtr);
    static void ReleaseNodeRawMemory(int64_t deadline, const RefPtr<TaskExecutor>& taskExecutor);
    static void PostReleaseNodeRawMemoryTask(const RefPtr<TaskExecutor>& taskExecutor);

private:
    UiNodeGc() = delete;
    ~UiNodeGc() = delete;

    static bool IsTooLate(int64_t deadline);
    static bool PostTask(const RefPtr<TaskExecutor>& taskExecutor, const TaskExecutor::Task& task,
        const std::string& name, PriorityType priorityType = PriorityType::LOW);
    static void ReleaseNodeRawMemoryInner(const RefPtr<TaskExecutor>& taskExecutor);
    static void ReleaseInner(OHOS::Ace::NG::UINode* frameNodeRawPtr);
    static void ReleaseNodeRawBucket();
    static PriorityType JudgeGCLevel(uint32_t remainBucketSize, int64_t deadline);
    static std::queue<std::vector<OHOS::Ace::NG::UINode*>>& MockGetNodeRawBucket();

    ACE_DISALLOW_COPY_AND_MOVE(UiNodeGc);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_UI_NODE_GC_H
