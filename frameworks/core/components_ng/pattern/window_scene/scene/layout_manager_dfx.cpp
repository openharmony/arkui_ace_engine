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

#include "layout_manager_dfx.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr int64_t LAYOUT_MANAGER_INTERVAL = 120;
}

namespace OHOS::Ace::NG {
LayoutManagerDfx* LayoutManagerDfx::GetInstance()
{
    static LayoutManagerDfx instance;
    return &instance;
}

void LayoutManagerDfx::DumpFlushInfo(const TraverseResult& res)
{
    TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "DumpFlushInfo screenId:%{public}" PRIu64, res.screenId);
    for (const auto& [winId, uiParam] : res.uiParams) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "%{public}d|%{public}s|%{public}s|%{public}f|%{public}f|%{public}f|"
            "%{public}f|%{public}d", winId, uiParam.sessionName_.c_str(), uiParam.rect_.ToString().c_str(),
            uiParam.scaleX_, uiParam.scaleY_, uiParam.transX_, uiParam.transY_, uiParam.interactive_);
    }
}

void LayoutManagerDfx::PerformUIParams()
{
    if (curVsyncCnt_ < LAYOUT_MANAGER_INTERVAL) {
        return;
    }
    std::queue<TraverseResult> recordQue = {};
    {
        std::lock_guard lock(recordMutex_);
        recordQue = recordRes_.que;
        recordRes_.size = 0;
        recordRes_.que = {};
        curVsyncCnt_ = 0;
    }

    int32_t cnt = 0;
    while (!recordQue.empty()) {
        TAG_LOGI(AceLogTag::ACE_WINDOW_PIPELINE, "PerformUIParams cnt:%{public}d", cnt);
        DumpFlushInfo(recordQue.front());
        recordQue.pop();
        cnt++;
    }
}

void LayoutManagerDfx::RecordUIParams(TraverseResult uiParams)
{
    std::lock_guard lock(recordMutex_);
    if (recordRes_.size >= RECORD_LIST_MAX_CAPACITY) {
        recordRes_.que.pop();
        recordRes_.size--;
    }
    recordRes_.que.push(uiParams);
    recordRes_.size++;
    curVsyncCnt_++;
}

void LayoutManagerDfx::ExecuteRecordUIParams(TraverseResult& res)
{
    auto task = [this, res] {
        RecordUIParams(res);
        PerformUIParams();
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->PostAsyncEvent(
        std::move(task), "ExecuteRecordUIParams", TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG