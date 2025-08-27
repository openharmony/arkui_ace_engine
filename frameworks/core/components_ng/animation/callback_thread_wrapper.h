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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_ANIMATION_CALLBACK_THREAD_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_ANIMATION_CALLBACK_THREAD_WRAPPER_H

#include <functional>
#include <mutex>

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CallbackThreadWrapper {
public:
    CallbackThreadWrapper(
    const RefPtr<TaskExecutor>& taskExecutor, const std::function<void()>& callback, bool once)
        : taskExecutor_(taskExecutor), callback_(callback), once_(once)
    {}
    ~CallbackThreadWrapper()
    {
        if (callback_ && taskExecutor_ && !taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            auto mutex = std::make_shared<std::mutex>();
            std::lock_guard lock(*mutex);
            taskExecutor_->PostTask(
                [callback = callback_, mutex]() mutable {
                    std::lock_guard lock(*mutex);
                    callback = nullptr;
                },
                TaskExecutor::TaskType::UI, "ArkUICallbackThreadWrapper", PriorityType::HIGH);
            callback_ = nullptr;
        }
    }
    void operator()()
    {
        if (callback_) {
            callback_();
            if (once_) {
                callback_ = nullptr;
            }
        }
    }
private:
    RefPtr<TaskExecutor> taskExecutor_;
    std::function<void()> callback_;
    bool once_ = false; // flag of executing only once
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_ANIMATION_CALLBACK_THREAD_WRAPPER_H
