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

#include "uv_task_wrapper_impl.h"

namespace OHOS::Ace::NG {

UVTaskWrapperImpl::UVTaskWrapperImpl(napi_env env)
    :env_(env)
{
    if (env == nullptr) {
        LOGE("env is null");
        return;
    }
    auto engine = reinterpret_cast<NativeEngine*>(env);
    if (engine == nullptr) {
        LOGE("native engine is null");
        return;
    }
    threadId_ = engine->GetTid();
}

bool UVTaskWrapperImpl::WillRunOnCurrentThread()
{
    return pthread_self() == threadId_;
}

void UVTaskWrapperImpl::Call(const TaskExecutor::Task& task)
{
    napi_send_event(env_, [work = std::make_shared<UVWorkWrapper>(task)] {
        (*work)();
    }, napi_eprio_high);
}
} // namespace OHOS::Ace::NG
