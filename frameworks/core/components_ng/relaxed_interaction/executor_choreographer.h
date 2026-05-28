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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_CHOREOGRAPHER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_CHOREOGRAPHER_H

#include <deque>
#include <memory>
#include <vector>

#include "core/components_ng/relaxed_interaction/base_executor.h"

namespace OHOS::Ace::NG {

class ExecutorChoreographer {
public:
    ExecutorChoreographer() = default;
    ~ExecutorChoreographer() = default;

    void Enqueue(std::vector<std::unique_ptr<BaseExecutor>>&& executors);

    ExecutorResult ExecuteNext();

    void Clear();

    bool HasCurrent() const
    {
        return currentExecutor_ != nullptr;
    }

    bool HasNext() const
    {
        return !executorQueue_.empty();
    }

    size_t GetQueueSize() const
    {
        return executorQueue_.size();
    }

private:
    bool MoveToNext();

    std::deque<std::unique_ptr<BaseExecutor>> executorQueue_;

    std::unique_ptr<BaseExecutor> currentExecutor_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_EXECUTOR_CHOREOGRAPHER_H
