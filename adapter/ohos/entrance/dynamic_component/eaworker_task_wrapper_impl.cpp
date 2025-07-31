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

#include "eaworker_task_wrapper_impl.h"


#include <ani.h>
#include "concurrency_helpers.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/utils/time_util.h"
#include "bridge/arkts_frontend/arkts_frontend.h"


namespace OHOS::Ace::NG {
namespace {
void GetVM(int32_t hostInstanceId, ani_vm **vm)
{
    auto container = Platform::AceContainer::GetContainer(hostInstanceId);
    CHECK_NULL_VOID(container);
    RefPtr<Frontend> frontend = container->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto arktsFrontend = AceType::DynamicCast<ArktsFrontend>(frontend);
    CHECK_NULL_VOID(arktsFrontend);
    *vm = arktsFrontend->GetVM();
}

void GetAniEnv(int32_t hostInstanceId, bool attachCurrentThread, ani_env **result)
{
    ani_vm *vm = nullptr;
    GetVM(hostInstanceId, &vm);
    CHECK_NULL_VOID(vm);
    ani_status status = ANI_OK;
    if (!attachCurrentThread) {
        ani_option interopEnabled {"--interop=enable", nullptr};
        ani_options aniArgs {1, &interopEnabled};
        status = vm->AttachCurrentThread(&aniArgs, ANI_VERSION_1, result);
        if (status == ANI_OK) {
            return;
        }

        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "AttachCurrentThread failed, status: %{public}d", status);
    }

    if ((status = vm->GetEnv(ANI_VERSION_1, result)) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "GetAniEnv from vm failed, status: %{public}d", status);
        return;
    }
}

bool CheckWorkerId(int32_t workerId)
{
    return workerId >= 0;
}
}

EaWorkerTaskWrapperImpl::EaWorkerTaskWrapperImpl(int32_t hostInstanceId, int32_t workerId)
    :hostInstanceId_(hostInstanceId), workerId_(workerId)
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "Create EaWorkerTaskWrapperImpl "
        "hostInstanceId: %{public}d, workerId:%{public}d", hostInstanceId_, workerId_);
}

EaWorkerTaskWrapperImpl::~EaWorkerTaskWrapperImpl()
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "Destory EaWorkerTaskWrapperImpl "
        "hostInstanceId: %{public}d, workerId:%{public}d", hostInstanceId_, workerId_);
}

void EaWorkerTaskWrapperImpl::SetCurrentPthread(const pthread_t& threadId)
{
    threadId_ = threadId;
}

bool EaWorkerTaskWrapperImpl::WillRunOnCurrentThread()
{
    return pthread_self() == threadId_;
}

void *EaWorkerTaskWrapperImpl::GetCurrentAniEnv()
{
    ani_vm *vmInThread = nullptr;
    ani_size bufferSize = 1;
    ani_size size = 0;
    if (ANI_GetCreatedVMs(&vmInThread, bufferSize, &size) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "ANI_GetCreatedVMs failed");
        return nullptr;
    }

    if (bufferSize != size) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "bufferSize %{public}zu , size: %{public}zu", bufferSize, size);
        return nullptr;
    }

    ani_env *envCurr = nullptr;
    if (vmInThread->GetEnv(ANI_VERSION_1, &envCurr) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "GetEnv failed");
        return nullptr;
    }

    return envCurr;
}

bool EaWorkerTaskWrapperImpl::HasAttachCurrentThread(pthread_t tid)
{
    if (threadId_ == tid) {
        return true;
    }

    return attachCurrentThreads_.find(tid) != attachCurrentThreads_.end();
}

void EaWorkerTaskWrapperImpl::Call(const TaskExecutor::Task& task)
{
    if (!CheckWorkerId(workerId_)) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "EaWorkerTaskWrapperImpl Call due "
            "to error invalid workerId: %{public}d", workerId_);
        return;
    }
    ani_env *callerAniEnv = nullptr;
    auto tid = pthread_self();
    bool attachCurrentThread = HasAttachCurrentThread(tid);
    GetAniEnv(hostInstanceId_, attachCurrentThread, &callerAniEnv);
    auto callerWorkerId = arkts::concurrency_helpers::GetWorkerId(callerAniEnv);
    if (callerAniEnv == nullptr) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "EaWorkerTaskWrapperImpl callerAniEnv is nullptr, "
            "callerWorkerId: %{public}d, workerId: %{public}d", callerWorkerId, workerId_);
        return;
    }

    if (!attachCurrentThread) {
        attachCurrentThreads_.insert(tid);
    }

    int64_t ts = GetSysTimestamp();
    EaWorkerEvent* event = new EaWorkerEvent(task, ts);
    auto status = arkts::concurrency_helpers::SendEvent(callerAniEnv, workerId_,
        [] (void *data) {
            auto *event = reinterpret_cast<EaWorkerEvent *>(data);
            if (event == nullptr) {
                TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "event is null");
                return;
            }

            event->Fire();
        }, reinterpret_cast<void *>(event));
    if (status != arkts::concurrency_helpers::WorkStatus::OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "SendEvent error");
    }
}

void EaWorkerTaskWrapperImpl::DumpWorker()
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "DumpWorker start when gettid: %{public}s",
        std::to_string(gettid()).c_str());
    ani_vm *vmInThread = nullptr;
    ani_size bufferSize = 1;
    ani_size size = 0;
    if (ANI_GetCreatedVMs(&vmInThread, bufferSize, &size) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "ANI_GetCreatedVMs failed");
        return;
    }

    if (bufferSize != size) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "bufferSize %{public}zu , size: %{public}zu", bufferSize, size);
        return;
    }

    ani_env *envCurr = nullptr;
    if (vmInThread->GetEnv(ANI_VERSION_1, &envCurr) != ANI_OK) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "GetEnv failed");
        return;
    }

    auto worker_id = arkts::concurrency_helpers::GetWorkerId(envCurr);
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "DumpWorker end, worker_id: %{public}d", worker_id);
}

void EaWorkerTaskWrapperImpl::Call(const TaskExecutor::Task& task, uint32_t delayTime)
{
    Call(task);
}
} // namespace OHOS::Ace::NG
