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

#include "core/components_ng/base/ui_node_gc.h"

#include "base/utils/time_util.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
enum {
    PRIORITYTYPE_WATERLINE_LOW = 50,
    PRIORITYTYPE_WATERLINE_HIGH = 100,
    PRIORITYTYPE_WATERLINE_IMMEDIATE = 500,
    PRIORITYTYPE_WATERLINE_VIP,
};
constexpr size_t PER_BUCKET_MAX_SIZE = 10;
constexpr size_t BUCKET_MAX_SIZE = 1000;
thread_local int64_t deadline_ = -1;
thread_local std::queue<std::vector<OHOS::Ace::NG::UINode*>> nodeRawBucket_;
} // namespace

bool UiNodeGc::IsTooLate(int64_t deadline)
{
    if (deadline == -1) {
        return false;
    }

    return GetSysTimestamp() > deadline;
}

bool UiNodeGc::PostTask(const RefPtr<TaskExecutor>& taskExecutor, const TaskExecutor::Task& task,
    const std::string& name, PriorityType priorityType)
{
    if (taskExecutor) {
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name, priorityType);
        return true;
    }
    LOGW("UiNodeGc::PostTask failed");
    task();
    return false;
}

void UiNodeGc::ReleaseInner(OHOS::Ace::NG::UINode* rawPtr)
{
    if (nodeRawBucket_.empty()) {
        nodeRawBucket_.push({ rawPtr });
        return;
    }
    auto& bucket = nodeRawBucket_.back();
    if (bucket.size() >= PER_BUCKET_MAX_SIZE) {
        nodeRawBucket_.push({ rawPtr });
        return;
    }
    bucket.push_back(rawPtr);
}

void UiNodeGc::ReleaseNodeRawBucket()
{
    if (nodeRawBucket_.empty()) {
        return;
    }
    std::vector<OHOS::Ace::NG::UINode*> toDele = std::move(nodeRawBucket_.front());
    nodeRawBucket_.pop();
    ACE_SCOPED_TRACE_COMMERCIAL(
        "ReleaseNodeRawBucket delete %zu, remain node buckets %zu", toDele.size(), nodeRawBucket_.size());
    for (auto ptr : toDele) {
        if (ptr) {
            delete ptr;
        }
    }
}

PriorityType UiNodeGc::JudgeGCLevel(uint32_t remainBucketSize, int64_t deadline)
{
    if (deadline == -1) {
        //  we don't know next frame idle
        return PriorityType::IDLE;
    }

    if (remainBucketSize < PRIORITYTYPE_WATERLINE_LOW) {
        return PriorityType::LOW;
    } else if (remainBucketSize < PRIORITYTYPE_WATERLINE_HIGH) {
        return PriorityType::HIGH;
    } else if (remainBucketSize < PRIORITYTYPE_WATERLINE_IMMEDIATE) {
        return PriorityType::IMMEDIATE;
    }
    return PriorityType::VIP;
}

void UiNodeGc::PostReleaseNodeRawMemoryTask(const RefPtr<TaskExecutor>& taskExecutor)
{
    if (!taskExecutor) {
        LOGE("UiNodeGc::PostReleaseNodeRawMemoryTask taskExecutor is nullptr");
        return;
    }
    ReleaseNodeRawMemory(-1, taskExecutor);
}

void UiNodeGc::ReleaseNodeRawMemoryInner(const RefPtr<TaskExecutor>& taskExecutor)
{
    if (nodeRawBucket_.empty()) {
        return;
    }
    auto remainBucketSize = nodeRawBucket_.size();
    auto nodeGCLevel = JudgeGCLevel(remainBucketSize, deadline_);
    auto task = [nodeGCLevel, remainBucketSize, taskExecutor = taskExecutor]() {
        if (IsTooLate(deadline_) && nodeGCLevel != PriorityType::VIP) {
            return;
        }
        ReleaseNodeRawBucket();
        ReleaseNodeRawMemoryInner(taskExecutor);
    };
    PostTask(taskExecutor, task, "ReleaseNodeRawMemoryTask", nodeGCLevel);
}

void UiNodeGc::ReleaseNodeRawMemory(int64_t deadline, const RefPtr<TaskExecutor>& taskExecutor)
{
    deadline_ = deadline;
    UiNodeGc::ReleaseNodeRawMemoryInner(taskExecutor);
}

void UiNodeGc::OnReleaseFunc(OHOS::Ace::NG::UINode* rawPtr)
{
    if (!rawPtr) {
        LOGE("UiNodeGc::OnReleaseFunc rawPtr is nullptr");
        return;
    }

    if (nodeRawBucket_.size() > BUCKET_MAX_SIZE) {
        LOGW("UiNodeGc::OnReleaseFunc nodeRawBucket size is %{public}zu", nodeRawBucket_.size());
        delete rawPtr;
        return;
    }

    rawPtr->OnDelete();
    ReleaseInner(rawPtr);
}

std::queue<std::vector<OHOS::Ace::NG::UINode*>>& UiNodeGc::MockGetNodeRawBucket()
{
    return nodeRawBucket_;
}
} // namespace OHOS::Ace::NG
