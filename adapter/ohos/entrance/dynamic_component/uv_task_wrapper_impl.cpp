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
    loop_ = engine->GetUVLoop();
    threadId_ = engine->GetTid();
}

bool UVTaskWrapperImpl::WillRunOnCurrentThread()
{
    return pthread_self() == threadId_;
}

void UVTaskWrapperImpl::Call(const TaskExecutor::Task& task)
{
    if (loop_ == nullptr) {
        LOGW("loop is null");
        return;
    }
    UVWorkWrapper* workWrapper = new UVWorkWrapper(task);
    uv_queue_work(
        loop_, workWrapper, [](uv_work_t* req) {},
        [](uv_work_t* req, int status) {
            auto workWrapper = static_cast<UVWorkWrapper*>(req);
            (*workWrapper)();
            delete workWrapper;
        });
}
} // namespace OHOS::Ace::NG
