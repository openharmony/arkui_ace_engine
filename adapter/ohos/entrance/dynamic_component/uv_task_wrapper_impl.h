/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_UV_TASK_WRAPPER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_UV_TASK_WRAPPER_H

#include "jsnapi.h"
#include "native_engine.h"

#include "base/thread/task_executor.h"

namespace OHOS::Ace::NG {

class UVTaskWrapperImpl : public TaskWrapper {
public:
    explicit UVTaskWrapperImpl(napi_env env);
    bool WillRunOnCurrentThread() override;
    void Call(const TaskExecutor::Task& task) override;

private:
    pthread_t threadId_ = 0;
    napi_env env_;
};

class UVWorkWrapper : public uv_work_t {
public:
    explicit UVWorkWrapper(const TaskExecutor::Task& task) : uv_work_t(), task_(task)
    {
    }

    void operator()() const
    {
        task_();
    }

private:
    TaskExecutor::Task task_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_DYNAMIC_COMPONENT_UV_TASK_WRAPPER_H