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
#ifndef TASK_DEPENDENCY_MANAGER_H
#define TASK_DEPENDENCY_MANAGER_H

#include <chrono>
#include <functional>
#include <future>
#include <map>
#include <mutex>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
class TaskDependencyManager : public AceType {
    DECLARE_ACE_TYPE(TaskDependencyManager, AceType);
public:
    enum class ErrorCode {
        TASK_ERROR_KEY_CONFLICT = 0,
        TASK_ERROR_KEY_ILLEGAL,
        TASK_ERROR_UNRECORDED_DEPENDENCY
    };
    static RefPtr<TaskDependencyManager> GetInstance();

    // Do not invoke in subthread
    virtual void PostTaskToBg(std::function<void()>&& task, const std::string& taskName,
        std::function<void(ErrorCode, std::function<void()>&&,
        const std::string&)>&& errorHandler = [] (ErrorCode code,
            std::function<void()>&& task,
            const std::string& taskName) {
                task();
        });
    virtual void Wait(const std::string& dependencyName,
        std::function<void(ErrorCode, const std::string&)>&& errorHandler = [] (
            ErrorCode code, const std::string& dependencyName) {
                return;
        });
    // Do not invoke in subthread
    virtual void Sync();
private:
    virtual void Delete(const std::string& taskName);
    static RefPtr<TaskDependencyManager> instance_;
    std::map<std::string, std::shared_ptr<std::future<void>>> futures_;
    std::mutex lock_;
};
} //OHOS::Ace

#endif //TASK_DEPENDENCY_MANAGER_H
