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

#include <cinttypes>
#include <sstream>
#include <string>

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "base/utils/time_util.h"
#include "core/components_ng/manager/load_complete/load_complete_manager.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
#include "ui/base/utils/utils.h"

namespace {
constexpr int32_t TIMEOUT_VALUE = 3000;
constexpr float NANOSECOND_CONVERSION = 1000 * 1000; // Millisecond and nanosecond conversion.
constexpr float STOP_COLLECT_TIME_WAIT = 100; // Stop collecting asynchronous task waiting time.
constexpr float COMPONENT_LOAD_NUMBER = 100; // Number of components loaded in 100 milliseconds.
} // namespace

namespace OHOS::Ace::NG {
void LoadCompleteManager::PostTimeoutTask()
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "LoadCompleteTimeoutTask");
    std::weak_ptr<LoadCompleteManager> loadCompleteManagerWeak = shared_from_this();
    taskExecutor->PostDelayedTask(
        [weak = loadCompleteManagerWeak]() -> void {
            auto loadCompleteMgr = weak.lock();
            CHECK_NULL_VOID(loadCompleteMgr);
            loadCompleteMgr->ForceFinishCollectTask();
        },
        TaskExecutor::TaskType::UI, TIMEOUT_VALUE, "LoadCompleteTimeoutTask");
}

void LoadCompleteManager::ResetManagerStatus()
{
    collectStatus_ = CollectStatus::INIT;
    nodeNum_ = 0;
    nodeSet_.clear();
}

void LoadCompleteManager::StartCollect(const std::string& pageUrl)
{
    if (collectStatus_ != CollectStatus::INIT) {
        return;
    }
    ResetManagerStatus();
    collectStatus_ = CollectStatus::COLLECTING;
    pageUrl_ = pageUrl;
    PostTimeoutTask();
    beginTime_ = GetSysTimestamp();
    AceAsyncTraceBeginCommercial(0, "APP_COMPONENT_LOAD");
}

void LoadCompleteManager::TryStopCollect()
{
    if (nodeNum_ > COMPONENT_LOAD_NUMBER) {
        nodeNum_ = 0;
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "TryStopCollectTask");
        std::weak_ptr<LoadCompleteManager> loadCompleteManagerWeak = shared_from_this();
        taskExecutor->PostDelayedTask(
            [weak = loadCompleteManagerWeak]() -> void {
                auto loadCompleteMgr = weak.lock();
                CHECK_NULL_VOID(loadCompleteMgr);
                loadCompleteMgr->TryStopCollect();
            },
            TaskExecutor::TaskType::UI, STOP_COLLECT_TIME_WAIT, "TryStopCollectTask");
    } else {
        collectStatus_ = CollectStatus::ANALYSIS;
        TryFinishCollectTask();
    }
}

void LoadCompleteManager::StopCollect()
{
    nodeNum_ = 0;
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "TryStopCollectTask");
    std::weak_ptr<LoadCompleteManager> loadCompleteManagerWeak = shared_from_this();
    taskExecutor->PostDelayedTask(
        [weak = loadCompleteManagerWeak]() -> void {
            auto loadCompleteMgr = weak.lock();
            CHECK_NULL_VOID(loadCompleteMgr);
            loadCompleteMgr->TryStopCollect();
        },
        TaskExecutor::TaskType::UI, STOP_COLLECT_TIME_WAIT, "TryStopCollectTask");
}

void LoadCompleteManager::ForceFinishCollectTask()
{
    if (collectStatus_ != CollectStatus::INIT) {
        collectStatus_ = CollectStatus::ANALYSIS;
        FinishCollectTask();
    }
}

void LoadCompleteManager::TryFinishCollectTask()
{
    if (collectStatus_ == CollectStatus::ANALYSIS && nodeSet_.size() == 0) {
        FinishCollectTask();
    }
}

void LoadCompleteManager::FinishCollectTask()
{
    AceAsyncTraceEndCommercial(0, "APP_COMPONENT_LOAD");
    int64_t loadCost = GetSysTimestamp() - beginTime_;
    if (loadCost > (SystemProperties::GetPageLoadTimethreshold() * NANOSECOND_CONVERSION)) {
        EventInfo eventInfo = {
            .errorType = static_cast<int32_t>(OHOS::Ace::ComponentExcepType::COMPONENT_LOAD_TIMEOUT),
            .pageUrl = pageUrl_.c_str(),
            .loadCost = loadCost,
        };
        EventReport::ReportComponentLoadTimeout(eventInfo);
    }

    ResetManagerStatus();
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "LoadCompleteTimeoutTask");
    taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "TryStopCollectTask");
}

void LoadCompleteManager::AddLoadComponent(int32_t nodeId)
{
    if (collectStatus_ != CollectStatus::COLLECTING) {
        return;
    }
    nodeSet_.insert(nodeId);
    nodeNum_++;
}

void LoadCompleteManager::DeleteLoadComponent(int32_t nodeId)
{
    if (collectStatus_ == CollectStatus::INIT) {
        return;
    }
    nodeSet_.erase(nodeId);
    TryFinishCollectTask();
}

void LoadCompleteManager::CompleteLoadComponent(int32_t nodeId)
{
    if (collectStatus_ == CollectStatus::INIT) {
        return;
    }
    nodeSet_.erase(nodeId);
    TryFinishCollectTask();
}
} // namespace OHOS::Ace::NG
