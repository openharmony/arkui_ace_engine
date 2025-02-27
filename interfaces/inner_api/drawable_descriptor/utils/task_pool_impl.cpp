/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include <mutex>

#include "ffrt_inner.h"

#include "utils/task_pool.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class TaskPoolImpl final : public TaskPool {
public:
    TaskPoolImpl();
    ~TaskPoolImpl() = default;

    void PostTask(Task&& task, const std::string& name) override;

private:
    std::unique_ptr<ffrt::queue> queue_ = nullptr;
};

std::unique_ptr<TaskPool> TaskPool::instance_;
std::once_flag TaskPool::initFlag;

TaskPool* TaskPool::GetInstance()
{
    std::call_once(initFlag, []() { instance_.reset(new TaskPoolImpl); });
    return instance_.get();
}

TaskPoolImpl::TaskPoolImpl()
{
    queue_ = std::make_unique<ffrt::queue>(ffrt::queue_concurrent, "ImageTaskPool",
        ffrt::queue_attr().qos(ffrt::qos_default).max_concurrency(defaultMaxConcurrency_));
}

void TaskPoolImpl::PostTask(Task&& task, const std::string& name)
{
    queue_->submit_h(task);
}

} // namespace Drawable
} // namespace Ace
} // namespace OHOS
