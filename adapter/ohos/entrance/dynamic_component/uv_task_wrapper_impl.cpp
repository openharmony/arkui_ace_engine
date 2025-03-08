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
#include "base/utils/time_util.h"

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

void UVTaskWrapperImpl::Call(const TaskExecutor::Task& task, uint32_t delayTime)
{
    if (delayTime <= 0) {
        Call(task);
        return;
    }

    uv_loop_t *loop = nullptr;
    napi_get_uv_event_loop(env_, &loop);
    uv_update_time(loop);
    uv_timer_t *timer = new uv_timer_t;
    uv_timer_init(loop, timer);
    timer->data = new UVTimerWorkWrapper(task, delayTime, GetCurrentTimestamp());
    uv_timer_start(
        timer,
        [](uv_timer_t *timer) {
            UVTimerWorkWrapper* workWrapper = reinterpret_cast<UVTimerWorkWrapper*>(timer->data);
            if (workWrapper) {
                LOGD("Start work delayTime: %{public}u, taskTime: %{public}" PRId64 ", curTime: %{public}" PRId64,
                    workWrapper->GetDelayTime(), workWrapper->GetTaskTime(), GetCurrentTimestamp());
                (*workWrapper)();
                delete workWrapper;
            }
            uv_timer_stop(timer);
            uv_close(
                reinterpret_cast<uv_handle_t *>(timer),
                [](uv_handle_t *timer) {
                    delete reinterpret_cast<uv_timer_t *>(timer);
            });
        },
        delayTime, 0);
}
} // namespace OHOS::Ace::NG
