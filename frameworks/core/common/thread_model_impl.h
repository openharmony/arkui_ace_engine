/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMMON_THREAD_MODEL_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_COMMON_THREAD_MODEL_IMPL_H

#include "core/common/task_runners.h"
#include "core/common/thread_container.h"

namespace OHOS::Ace {
class ThreadModelImpl {
public:
    ThreadModelImpl(ThreadContainer threadContainer, TaskRunners taskRunners);
    ~ThreadModelImpl() = default;

    static std::unique_ptr<ThreadModelImpl> CreateThreadModel(
        bool useCurrentEventRunner, bool hasUiThread, bool useGpuThread);

    const TaskRunners& GetTaskRunners() const;

private:
    const ThreadContainer threadContainer_;
    const TaskRunners taskRunners_;
    ACE_DISALLOW_COPY_AND_MOVE(ThreadModelImpl);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMMON_THREAD_MODEL_IMPL_H
