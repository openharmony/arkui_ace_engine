/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_REF_MANAGER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_REF_MANAGER_H

#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT NativeRefManager final {
public:
    static NativeRefManager& GetInstance()
    {
        static NativeRefManager instance_;
        return instance_;
    }

    void PostDestructorInterceptorTask(std::function<void()>&& task)
    {
        taskExecutor_->PostTask(std::move(task), "DestructorInterceptor", PriorityType::IDLE);
    }

private:
    RefPtr<TaskRunnerAdapter> taskExecutor_ = TaskRunnerAdapterFactory::Create(false, "");
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_REF_MANAGER_H
