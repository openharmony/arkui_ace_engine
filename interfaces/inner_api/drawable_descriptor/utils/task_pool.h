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
#ifndef FOUNDATION_ACE_INTERFACE_BASE_TASK_POOL_H
#define FOUNDATION_ACE_INTERFACE_BASE_TASK_POOL_H

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>

namespace OHOS {
namespace Ace {
namespace Drawable {
class TaskPool {
public:
    using Task = std::function<void()>;

    TaskPool(const TaskPool&) = delete;
    TaskPool& operator=(const TaskPool&) = delete;
    virtual ~TaskPool() = default;

    static TaskPool* GetInstance();

    virtual void PostTask(Task&& task, const std::string& name);

protected:
    TaskPool() = default;
    int32_t defaultMaxConcurrency_ = 8;

private:
    static std::unique_ptr<TaskPool> instance_;
    static std::once_flag initFlag;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_BASE_TASK_POOL_H
