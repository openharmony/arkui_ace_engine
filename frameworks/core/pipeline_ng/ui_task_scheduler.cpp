/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/pipeline_ng/ui_task_scheduler.h"

#include "base/log/ace_performance_check.h"
#include "base/log/frame_report.h"
#include "base/memory/referenced.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
uint64_t UITaskScheduler::frameId_ = 0;

UITaskScheduler::~UITaskScheduler() = default;

void UITaskScheduler::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    dirtyLayoutNodes_.emplace_back(dirty);
}

void UITaskScheduler::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    auto result = dirtyRenderNodes_[dirty->GetPageId()].emplace(dirty);
    if (!result.second) {
        LOGW("fail to emplace %{public}s render node", dirty->GetTag().c_str());
    }
}

void UITaskScheduler::FlushLayoutTask(bool forceUseMainThread)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (dirtyLayoutNodes_.empty()) {
        return;
    }
    isLayouting_ = true;
    auto dirtyLayoutNodes = std::move(dirtyLayoutNodes_);
    PageDirtySet dirtyLayoutNodesSet(dirtyLayoutNodes.begin(), dirtyLayoutNodes.end());

    // Priority task creation
    int64_t time = 0;
    for (auto&& node : dirtyLayoutNodesSet) {
        // need to check the node is destroying or not before CreateLayoutTask
        if (!node || node->IsInDestroying()) {
            continue;
        }
        time = GetSysTimestamp();
        auto task = node->CreateLayoutTask(forceUseMainThread);
        if (task) {
            if (forceUseMainThread || (task->GetTaskThreadType() == MAIN_TASK)) {
                (*task)();
                time = GetSysTimestamp() - time;
            } else {
                LOGW("need to use multithread feature");
            }
        }
        if (frameInfo_ != nullptr) {
            frameInfo_->AddTaskInfo(node->GetTag(), node->GetId(), time, FrameInfo::TaskType::LAYOUT);
        }
    }
    isLayouting_ = false;
}

void UITaskScheduler::FlushRenderTask(bool forceUseMainThread)
{
    CHECK_RUN_ON(UI);
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushRender();
    }
    auto dirtyRenderNodes = std::move(dirtyRenderNodes_);
    // Priority task creation
    int64_t time = 0;
    for (auto&& pageNodes : dirtyRenderNodes) {
        ACE_SCOPED_TRACE("FlushRenderTask %zu", pageNodes.second.size());
        for (auto&& node : pageNodes.second) {
            if (!node) {
                continue;
            }
            if (node->IsInDestroying()) {
                continue;
            }
            time = GetSysTimestamp();
            auto task = node->CreateRenderTask(forceUseMainThread);
            if (task) {
                if (forceUseMainThread || (task->GetTaskThreadType() == MAIN_TASK)) {
                    (*task)();
                    time = GetSysTimestamp() - time;
                    if (frameInfo_ != nullptr) {
                        frameInfo_->AddTaskInfo(node->GetTag(), node->GetId(), time, FrameInfo::TaskType::RENDER);
                    }
                } else {
                    LOGW("need to use multithread feature");
                }
            }
        }
    }
}

bool UITaskScheduler::NeedAdditionalLayout()
{
    bool ret = false;
    ElementRegister::GetInstance()->ReSyncGeometryTransition();

    RootDirtyMap dirtyLayoutNodesMap;
    for (auto&& dirty : dirtyLayoutNodes_) {
        dirtyLayoutNodesMap[dirty->GetPageId()].emplace(dirty);
    }

    for (auto&& pageNodes : dirtyLayoutNodesMap) {
        for (auto&& node : pageNodes.second) {
            if (!node || !node->GetLayoutProperty()) {
                continue;
            }
            const auto& geometryTransition = node->GetLayoutProperty()->GetGeometryTransition();
            if (geometryTransition != nullptr) {
                ret |= geometryTransition->OnAdditionalLayout(node);
            }
        }
    }
    return ret;
}

void UITaskScheduler::FlushTask()
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("UITaskScheduler::FlushTask");
    FlushLayoutTask();
    if (NeedAdditionalLayout()) {
        FlushLayoutTask();
    }
    if (!afterLayoutTasks_.empty()) {
        FlushAfterLayoutTask();
    }
    ElementRegister::GetInstance()->ClearPendingRemoveNodes();
    FlushRenderTask();
}

void UITaskScheduler::AddPredictTask(PredictTask&& task)
{
    predictTask_.push_back(std::move(task));
}

void UITaskScheduler::FlushPredictTask(int64_t deadline, bool canUseLongPredictTask)
{
    decltype(predictTask_) tasks(std::move(predictTask_));
    for (const auto& task : tasks) {
        if (task) {
            task(deadline, canUseLongPredictTask);
        }
    }
}

void UITaskScheduler::CleanUp()
{
    dirtyLayoutNodes_.clear();
    dirtyRenderNodes_.clear();
}

bool UITaskScheduler::isEmpty()
{
    return dirtyLayoutNodes_.empty() && dirtyRenderNodes_.empty();
}

void UITaskScheduler::AddAfterLayoutTask(std::function<void()>&& task)
{
    afterLayoutTasks_.emplace_back(std::move(task));
}

void UITaskScheduler::FlushAfterLayoutTask()
{
    decltype(afterLayoutTasks_) tasks(std::move(afterLayoutTasks_));
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}

void UITaskScheduler::AddAfterRenderTask(std::function<void()>&& task)
{
    afterRenderTasks_.emplace_back(std::move(task));
}

void UITaskScheduler::FlushAfterRenderTask()
{
    ACE_SCOPED_TRACE("UITaskScheduler::FlushAfterRenderTask");
    decltype(afterRenderTasks_) tasks(std::move(afterRenderTasks_));
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}

} // namespace OHOS::Ace::NG
