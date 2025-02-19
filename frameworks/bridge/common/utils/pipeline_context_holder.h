/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_PIPELINE_CONTEXT_HOLDER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_PIPELINE_CONTEXT_HOLDER_H

#include <future>

#include "base/thread/task_executor.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Framework {

class PipelineContextHolder {
public:
    ~PipelineContextHolder()
    {
        if (pipelineContext_) {
            auto taskExecutor = pipelineContext_->GetTaskExecutor();
            // To guarantee the pipelineContext_ destruct in platform thread
            auto context = AceType::RawPtr(pipelineContext_);
            context->IncRefCount();
            pipelineContext_.Reset();
            taskExecutor->PostTask(
                [context] { context->DecRefCount(); }, TaskExecutor::TaskType::PLATFORM, "ArkUIDecRefCount");
        }
    }

    void Attach(const RefPtr<PipelineBase>& context)
    {
        if (attached_) {
            return;
        }
        if (!context) {
            return;
        }

        attached_ = true;
        promise_.set_value(context);
    }

    const RefPtr<PipelineBase>& Get()
    {
        if (!pipelineContext_) {
            pipelineContext_ = future_.get();
            ACE_DCHECK(pipelineContext_);
        }
        return pipelineContext_;
    }

private:
    bool attached_ = false;
    std::promise<RefPtr<PipelineBase>> promise_;
    std::future<RefPtr<PipelineBase>> future_ = promise_.get_future();
    RefPtr<PipelineBase> pipelineContext_;
};

}
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_PIPELINE_CONTEXT_HOLDER_H