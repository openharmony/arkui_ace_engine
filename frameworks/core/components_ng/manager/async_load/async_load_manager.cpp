/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/async_load/async_load_manager.h"

#include <algorithm>
#include <utility>

#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr char ASYNC_LOAD_TIMEOUT_TASK[] = "AsyncLoadTimeout";
} // namespace

AsyncLoadManager::AsyncLoadManager(int32_t instanceId) : instanceId_(instanceId) {}

void AsyncLoadManager::SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
{
    pipeline_ = pipeline;
}

void AsyncLoadManager::Register(int32_t nodeId, const AsyncLoadConfig& config, ForceLoadCallback forceLoad)
{
    if (nodeId < 0) {
        return;
    }
    // A remount of the same node replaces the previous entry rather than adding a
    // second one, which keeps the one-entry-per-node invariant.
    EraseEntry(nodeId);
    Entry entry;
    entry.nodeId = nodeId;
    entry.config = config;
    entry.forceLoad = std::move(forceLoad);
    entry.generation = ++nextGeneration_;
    pendingQueue_.push_back(std::move(entry));
    ScheduleTimeout(pendingQueue_.back());
}

void AsyncLoadManager::ScheduleTimeout(Entry& entry)
{
    const int32_t timeoutMs = entry.config.timeoutMs.value_or(DEFAULT_TIMEOUT_MS);
    if (timeoutMs < 0) {
        // Negative: never times out; the component keeps waiting until its build completes.
        return;
    }
    if (timeoutMs == 0) {
        // Zero: no waiting. Expired up front so the next vsync force-loads it.
        entry.expired = true;
        return;
    }
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    const int32_t nodeId = entry.nodeId;
    const uint64_t generation = entry.generation;
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this), nodeId, generation]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->MarkExpired(nodeId, generation);
        },
        TaskExecutor::TaskType::UI, static_cast<uint32_t>(timeoutMs), ASYNC_LOAD_TIMEOUT_TASK);
}

void AsyncLoadManager::MarkExpired(int32_t nodeId, uint64_t generation)
{
    for (auto& entry : pendingQueue_) {
        if (entry.nodeId != nodeId) {
            continue;
        }
        // A stale generation means the entry was replaced or removed after this
        // task was posted; marking it expired would force-load an unrelated build.
        if (entry.generation == generation) {
            entry.expired = true;
        }
        return;
    }
}

void AsyncLoadManager::OnLoaded(int32_t nodeId)
{
    EraseEntry(nodeId);
}

void AsyncLoadManager::OnNodeDestroyed(int32_t nodeId)
{
    EraseEntry(nodeId);
}

void AsyncLoadManager::EraseEntry(int32_t nodeId)
{
    auto it = std::find_if(pendingQueue_.begin(), pendingQueue_.end(),
        [nodeId](const Entry& entry) { return entry.nodeId == nodeId; });
    if (it == pendingQueue_.end()) {
        return;
    }
    pendingQueue_.erase(it);
}

void AsyncLoadManager::OnVsync(int64_t nanoTimestamp, int64_t vsyncPeriod)
{
    if (pendingQueue_.empty()) {
        return;
    }
    // Drain at most FORCE_LOAD_LIMIT_PER_FRAME per frame so a burst of timeouts
    // cannot turn the recovery mechanism itself into a dropped-frame source.
    std::list<ForceLoadCallback> pendingCallbacks;
    auto it = pendingQueue_.begin();
    while (it != pendingQueue_.end() &&
           static_cast<int32_t>(pendingCallbacks.size()) < FORCE_LOAD_LIMIT_PER_FRAME) {
        if (!it->expired) {
            ++it;
            continue;
        }
        pendingCallbacks.push_back(std::move(it->forceLoad));
        it = pendingQueue_.erase(it);
    }
    // The callbacks are invoked only after the entries are removed: a component's
    // build reports back through OnLoaded/OnNodeDestroyed, which would otherwise
    // invalidate the iterators used above.
    for (auto& callback : pendingCallbacks) {
        if (callback) {
            callback();
        }
    }
}

RefPtr<UINode> AsyncLoadManager::CreatePlaceholder(const AsyncLoadConfig& config)
{
    if (!config.HasPlaceholder()) {
        // Not configured: the component simply does not show before loading completes.
        return nullptr;
    }
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_RETURN(pipeline, nullptr);
    // Reached through the registry facade ScrollPlaceholderManager publishes, so the
    // scroll-placeholder internals stay untouched.
    auto scrollManager = pipeline->GetOrCreateScrollPlaceholderManager();
    CHECK_NULL_RETURN(scrollManager, nullptr);
    if (!scrollManager->IsTemplateRegistered(config.placeholderId)) {
        // Empty or unregistered id degrades to "not configured": no placeholder is shown and
        // no system default is substituted (spec EX-3).
        return nullptr;
    }
    return scrollManager->AcquireTemplateInstance(config.placeholderId);
}

void AsyncLoadManager::DetachPlaceholder(const RefPtr<UINode>& host, const RefPtr<UINode>& placeholder)
{
    if (host && placeholder) {
        host->RemoveChild(placeholder);
    }
}

size_t AsyncLoadManager::GetExpiredCount() const
{
    return static_cast<size_t>(std::count_if(pendingQueue_.begin(), pendingQueue_.end(),
        [](const Entry& entry) { return entry.expired; }));
}

} // namespace OHOS::Ace::NG
