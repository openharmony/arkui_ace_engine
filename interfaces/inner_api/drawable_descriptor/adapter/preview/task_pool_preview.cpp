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

#include "utils/task_pool.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class TaskPoolPreview final : public TaskPool {
public:
    TaskPoolPreview() = default;
    ~TaskPoolPreview() = default;

    void PostTask(Task&& task, const std::string& name) override;
};

std::unique_ptr<TaskPool> TaskPool::instance_;
std::once_flag TaskPool::initFlag;

TaskPool* TaskPool::GetInstance()
{
    std::call_once(initFlag, []() { instance_.reset(new TaskPoolPreview); });
    return instance_.get();
}

void TaskPoolPreview::PostTask(Task&& task, const std::string& name) {}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
