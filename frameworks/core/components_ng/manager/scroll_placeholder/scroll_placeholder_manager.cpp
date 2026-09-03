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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"

#include <algorithm>
#include <cinttypes>
#include <utility>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/time_util.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
// Reserved slice of each frame for framework work (layout/render sync) after item creation.
constexpr int64_t FRAMEWORK_SAFETY_MARGIN_NS = 1000000; // 1ms
// Fallback frame period when the window cannot provide one (host tests, early frames).
constexpr int64_t DEFAULT_VSYNC_PERIOD_NS = 16666667; // ~60Hz

int64_t EffectiveVsyncPeriod(int64_t vsyncPeriodNs)
{
    return vsyncPeriodNs > 0 ? vsyncPeriodNs : DEFAULT_VSYNC_PERIOD_NS;
}
} // namespace

ScrollPlaceholderManager::ScrollPlaceholderManager(int32_t instanceId) : instanceId_(instanceId) {}

void ScrollPlaceholderManager::SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
{
    pipeline_ = pipeline;
}

void ScrollPlaceholderManager::NotifyVsync(int64_t vsyncTimestampNs, int64_t vsyncPeriodNs)
{
    if (destroyed_.load(std::memory_order_relaxed)) {
        return;
    }
    CloseObservationFrame(vsyncTimestampNs);
    lastVsyncTimestampNs_ = vsyncTimestampNs;
    vsyncPeriodNs_ = vsyncPeriodNs;
    frameAnchored_ = true;
}

uint64_t ScrollPlaceholderManager::RegisterTemplate(
    const std::string& templateId, ScrollPlaceholderBuilder&& builder)
{
    if (destroyed_.load(std::memory_order_relaxed)) {
        return 0;
    }
    if (templateId.empty() || !builder) {
        registerRejected_.fetch_add(1, std::memory_order_relaxed);
        TAG_LOGW(AceLogTag::ACE_SCROLL,
            "ScrollPlaceholder register rejected: invalid templateId or empty builder, instanceId=%{public}d",
            instanceId_);
        return 0;
    }
    uint64_t generation = registry_.Register(templateId, std::move(builder));
    if (generation == 0) {
        return 0;
    }
    // Registration builds one placeholder instance synchronously (the framework generates the
    // read-only template subtree in its container at registration time), so the first acquire
    // is served from the pool; background clones then refill it to capacity.
    auto snapshot = registry_.LookupForCreate(templateId);
    if (snapshot.has_value() && snapshot->builder) {
        ResetPendingCloneSlots(templateId);
        registry_.CacheTemplateInstance(templateId, snapshot->builder());
        ScheduleBackgroundReplenish(templateId);
    }
    return generation;
}

bool ScrollPlaceholderManager::UnregisterTemplate(const std::string& templateId)
{
    if (destroyed_.load(std::memory_order_relaxed)) {
        return false;
    }
    bool removed = registry_.Unregister(templateId);
    if (removed) {
        // Pending tasks of this template are stale by generation; drop them eagerly.
        PurgeTemplateRealBuilds(templateId, ScrollPlaceholderCancelReason::UNREGISTER);
        ResetPendingCloneSlots(templateId);
    }
    return removed;
}

bool ScrollPlaceholderManager::IsTemplateRegistered(const std::string& templateId) const
{
    return registry_.IsRegistered(templateId);
}

std::optional<ScrollPlaceholderTemplateSnapshot> ScrollPlaceholderManager::LookupTemplateForCreate(
    const std::string& templateId)
{
    return registry_.LookupForCreate(templateId);
}

void ScrollPlaceholderManager::CacheTemplateInstance(
    const std::string& templateId, const RefPtr<UINode>& instance)
{
    registry_.CacheTemplateInstance(templateId, instance);
}

RefPtr<UINode> ScrollPlaceholderManager::AcquireTemplateInstance(const std::string& templateId)
{
    if (destroyed_.load(std::memory_order_relaxed) || templateId.empty()) {
        return nullptr;
    }
    auto cached = registry_.AcquireTemplateInstance(templateId);
    if (cached) {
        ScheduleBackgroundReplenish(templateId);
        return cached;
    }
    // Empty pool: synchronously create one instance from the current template so the request
    // is served right away; background clones refill the pool afterwards.
    auto snapshot = registry_.LookupForCreate(templateId);
    if (!snapshot.has_value() || !snapshot->builder) {
        return nullptr;
    }
    auto instance = snapshot->builder();
    ScheduleBackgroundReplenish(templateId);
    return instance;
}

size_t ScrollPlaceholderManager::GetCachedInstanceCount(const std::string& templateId) const
{
    return registry_.GetCachedInstanceCount(templateId);
}

size_t ScrollPlaceholderManager::GetHotTemplateCount() const
{
    return registry_.GetHotTemplateCount();
}

size_t ScrollPlaceholderManager::GetPendingCloneCount(const std::string& templateId) const
{
    std::lock_guard<std::mutex> guard(cloneMutex_);
    auto it = pendingCloneCount_.find(templateId);
    return it == pendingCloneCount_.end() ? 0 : it->second;
}

void ScrollPlaceholderManager::ScheduleBackgroundReplenish(const std::string& templateId)
{
    if (destroyed_.load(std::memory_order_relaxed) || templateId.empty()) {
        return;
    }
    auto snapshot = registry_.LookupForCreate(templateId);
    if (!snapshot.has_value() || !snapshot->builder) {
        return;
    }
    size_t toSubmit = 0;
    {
        std::lock_guard<std::mutex> guard(cloneMutex_);
        size_t held = registry_.GetCachedInstanceCount(templateId) + pendingCloneCount_[templateId];
        if (held < SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY) {
            toSubmit = SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - held;
            pendingCloneCount_[templateId] += static_cast<uint32_t>(toSubmit);
        }
    }
    // The RefPtr keeps the manager alive until every submitted task finishes; the task itself
    // only touches atomics, the mutex-guarded registry and the immutable builder handle.
    auto self = AceType::Claim(this);
    for (size_t i = 0; i < toSubmit; i++) {
        ScrollPlaceholderBuilder builderCopy = snapshot->builder;
        SubmitBackgroundCloneTask([self, templateId, generation = snapshot->generation, builderCopy]() {
            self->RunBackgroundClone(templateId, generation, builderCopy);
        });
    }
}

void ScrollPlaceholderManager::RunBackgroundClone(
    const std::string& templateId, uint64_t generation, const ScrollPlaceholderBuilder& builder)
{
    // Runs off the UI thread through the BackgroundTaskExecutor. Invoking the restricted
    // immutable builder yields a fresh equivalent instance (the deep template subtree clone
    // swaps in with the compiler restricted factory contract). Every exit path must release
    // the pending slot this task occupies.
    do {
        if (destroyed_.load(std::memory_order_relaxed) || !builder) {
            break;
        }
        auto instance = builder();
        if (!instance) {
            break;
        }
        if (registry_.GetCurrentGeneration(templateId) != generation) {
            // Template re-registered or unregistered while the clone was in flight: the
            // stale result is dropped and never cached.
            break;
        }
        registry_.CacheTemplateInstance(templateId, instance);
    } while (false);
    ReleasePendingCloneSlot(templateId);
}

void ScrollPlaceholderManager::ReleasePendingCloneSlot(const std::string& templateId)
{
    std::lock_guard<std::mutex> guard(cloneMutex_);
    auto it = pendingCloneCount_.find(templateId);
    if (it == pendingCloneCount_.end()) {
        return;
    }
    it->second = it->second > 0 ? it->second - 1 : 0;
    if (it->second == 0) {
        pendingCloneCount_.erase(it);
    }
}

void ScrollPlaceholderManager::ResetPendingCloneSlots(const std::string& templateId)
{
    std::lock_guard<std::mutex> guard(cloneMutex_);
    pendingCloneCount_.erase(templateId);
}

void ScrollPlaceholderManager::SubmitBackgroundCloneTask(std::function<void()> task)
{
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(task), BgTaskPriority::LOW);
}

ScrollPlaceholderPredictResult ScrollPlaceholderManager::Predict(
    const ScrollPlaceholderPredictParams& params, int64_t frameDeadlineNs) const
{
    ScrollPlaceholderPredictResult result = PredictCore(params, frameDeadlineNs);
    if (result.decision == ScrollPlaceholderDecision::BUILD_REAL_NOW) {
        predictBuildRealNow_.fetch_add(1, std::memory_order_relaxed);
    } else {
        predictUsePlaceholder_.fetch_add(1, std::memory_order_relaxed);
    }
    return result;
}

ScrollPlaceholderPredictResult ScrollPlaceholderManager::PredictCore(
    const ScrollPlaceholderPredictParams& params, int64_t frameDeadlineNs) const
{
    ScrollPlaceholderPredictResult result;
    result.estimateNs = EstimateRealBuildDuration(params);
    int64_t deadline = frameDeadlineNs > 0 ? frameDeadlineNs : GetVsyncDerivedFrameDeadlineNs();
    if (deadline <= 0 || destroyed_.load(std::memory_order_relaxed)) {
        // No frame anchor yet (feature engaged before the first vsync) or manager destroyed:
        // keep the legacy synchronous build path instead of forcing placeholders.
        result.decision = ScrollPlaceholderDecision::BUILD_REAL_NOW;
        return result;
    }
    result.budgetAvailable = true;
    result.remainingBudgetNs = GetRemainingFrameBudgetNs(deadline);
    if (result.estimateNs <= result.remainingBudgetNs) {
        result.decision = ScrollPlaceholderDecision::BUILD_REAL_NOW;
    } else {
        result.decision = ScrollPlaceholderDecision::USE_PLACEHOLDER;
    }
    return result;
}

int64_t ScrollPlaceholderManager::EstimateRealBuildDuration(const ScrollPlaceholderPredictParams& params) const
{
    return costModel_.EstimateRealBuildDuration(params.componentType, params.templateId);
}

int64_t ScrollPlaceholderManager::GetRemainingFrameBudgetNs(int64_t frameDeadlineNs) const
{
    int64_t remaining = frameDeadlineNs - GetSysTimestamp() - FRAMEWORK_SAFETY_MARGIN_NS;
    return remaining > 0 ? remaining : 0;
}

int64_t ScrollPlaceholderManager::GetVsyncDerivedFrameDeadlineNs() const
{
    if (!frameAnchored_ || lastVsyncTimestampNs_ <= 0) {
        return 0;
    }
    return lastVsyncTimestampNs_ + EffectiveVsyncPeriod(vsyncPeriodNs_);
}

void ScrollPlaceholderManager::RecordRealBuildDuration(
    const ScrollPlaceholderPredictParams& params, int64_t durationNs)
{
    costModel_.RecordRealBuildDuration(params.componentType, params.templateId, durationNs);
}

void ScrollPlaceholderManager::EnqueueRealBuild(const ScrollPlaceholderPredictParams& params,
    uint64_t templateGeneration, RealBuildTaskFunc&& task, ScrollPlaceholderRealBuildPriority priority)
{
    if (destroyed_.load(std::memory_order_relaxed) || !task) {
        return;
    }
    for (const auto& pending : pendingRealBuilds_) {
        if (pending.params.hostNodeId == params.hostNodeId && pending.params.index == params.index) {
            // Same item identity is already scheduled; keep the first task.
            return;
        }
    }
    RealBuildTask pendingTask;
    pendingTask.params = params;
    pendingTask.templateGeneration = templateGeneration;
    pendingTask.sequence = nextTaskSequence_++;
    pendingTask.priority = priority;
    pendingTask.task = std::move(task);
    pendingRealBuilds_.emplace_back(std::move(pendingTask));
}

void ScrollPlaceholderManager::FlushRealBuild(int64_t deadlineNs)
{
    if (destroyed_.load(std::memory_order_relaxed) || pendingRealBuilds_.empty()) {
        return;
    }
    flushRounds_.fetch_add(1, std::memory_order_relaxed);
    ACE_SCOPED_TRACE("ScrollPH.FlushRealBuild");
    // Visible items first, FIFO inside the same priority band.
    std::stable_sort(pendingRealBuilds_.begin(), pendingRealBuilds_.end(),
        [](const RealBuildTask& lhs, const RealBuildTask& rhs) { return lhs.priority < rhs.priority; });
    std::deque<RealBuildTask> requeued;
    bool budgetExhausted = false;
    while (!pendingRealBuilds_.empty()) {
        RealBuildTask pendingTask = std::move(pendingRealBuilds_.front());
        pendingRealBuilds_.pop_front();
        int64_t remaining = deadlineNs - GetSysTimestamp() - FRAMEWORK_SAFETY_MARGIN_NS;
        if (remaining <= 0) {
            requeued.push_back(std::move(pendingTask));
            budgetExhausted = true;
            break;
        }
        if (!pendingTask.params.templateId.empty() &&
            registry_.GetCurrentGeneration(pendingTask.params.templateId) != pendingTask.templateGeneration) {
            realBuildDropped_.fetch_add(1, std::memory_order_relaxed);
            continue;
        }
        int64_t estimate = costModel_.EstimateRealBuildDuration(
            pendingTask.params.componentType, pendingTask.params.templateId);
        if (estimate > remaining) {
            requeued.push_back(std::move(pendingTask));
            budgetExhausted = true;
            break;
        }
        int64_t start = GetSysTimestamp();
        bool committed = pendingTask.task();
        int64_t duration = GetSysTimestamp() - start;
        costModel_.RecordRealBuildDuration(pendingTask.params.componentType, pendingTask.params.templateId, duration);
        if (committed) {
            realBuildExecuted_.fetch_add(1, std::memory_order_relaxed);
        } else {
            realBuildDropped_.fetch_add(1, std::memory_order_relaxed);
        }
    }
    if (budgetExhausted) {
        while (!pendingRealBuilds_.empty()) {
            requeued.push_back(std::move(pendingRealBuilds_.front()));
            pendingRealBuilds_.pop_front();
        }
        realBuildRequeued_.fetch_add(requeued.size(), std::memory_order_relaxed);
        RequestFrameIfAlive();
    }
    pendingRealBuilds_ = std::move(requeued);
}

bool ScrollPlaceholderManager::HasPendingRealBuild() const
{
    return !pendingRealBuilds_.empty();
}

size_t ScrollPlaceholderManager::GetPendingRealBuildCount() const
{
    return pendingRealBuilds_.size();
}

void ScrollPlaceholderManager::CancelHostRealBuilds(int32_t hostNodeId, ScrollPlaceholderCancelReason reason)
{
    auto reasonIndex = static_cast<size_t>(reason);
    size_t cancelled = 0;
    std::deque<RealBuildTask> kept;
    for (auto& pending : pendingRealBuilds_) {
        if (pending.params.hostNodeId == hostNodeId) {
            cancelled++;
        } else {
            kept.push_back(std::move(pending));
        }
    }
    pendingRealBuilds_ = std::move(kept);
    if (cancelled > 0 && reasonIndex < CANCEL_REASON_COUNT) {
        cancelledByReason_[reasonIndex].fetch_add(cancelled, std::memory_order_relaxed);
    }
}

void ScrollPlaceholderManager::Destroy()
{
    if (destroyed_.exchange(true, std::memory_order_relaxed)) {
        return;
    }
    size_t dropped = pendingRealBuilds_.size();
    pendingRealBuilds_.clear();
    if (dropped > 0) {
        cancelledByReason_[static_cast<size_t>(ScrollPlaceholderCancelReason::PIPELINE_DESTROYED)]
            .fetch_add(dropped, std::memory_order_relaxed);
    }
    registry_.Clear();
    TAG_LOGI(AceLogTag::ACE_SCROLL,
        "ScrollPlaceholderManager destroyed, instanceId=%{public}d, dropped pending tasks=%{public}zu", instanceId_,
        dropped);
}

bool ScrollPlaceholderManager::IsDestroyed() const
{
    return destroyed_.load(std::memory_order_relaxed);
}

ScrollPlaceholderPredictResult ScrollPlaceholderManager::NotifyRealBuildStart(
    const ScrollPlaceholderPredictParams& params)
{
    ScrollPlaceholderPredictResult result = PredictCore(params, 0);
    if (destroyed_.load(std::memory_order_relaxed)) {
        return result;
    }
    size_t componentIndex = ComponentIndex(params.componentType);
    auto& stats = frameStats_[componentIndex];
    if (result.budgetAvailable) {
        // Budget information available: record what the prediction would have decided.
        if (result.decision == ScrollPlaceholderDecision::BUILD_REAL_NOW) {
            stats.suggestedReal++;
        } else {
            stats.suggestedPlaceholder++;
        }
        stats.lastRemainingBudgetNs = result.remainingBudgetNs;
    }
    return result;
}

void ScrollPlaceholderManager::NotifyRealBuildEnd(
    const ScrollPlaceholderPredictParams& params, int64_t buildStartNs)
{
    if (destroyed_.load(std::memory_order_relaxed) || buildStartNs <= 0) {
        return;
    }
    int64_t durationNs = GetSysTimestamp() - buildStartNs;
    if (durationNs < 0) {
        durationNs = 0;
    }
    costModel_.RecordRealBuildDuration(params.componentType, params.templateId, durationNs);
    observedRealBuilds_.fetch_add(1, std::memory_order_relaxed);
    size_t componentIndex = ComponentIndex(params.componentType);
    auto& stats = frameStats_[componentIndex];
    stats.observedBuilds++;
    stats.totalBuildNs += durationNs;
    if (durationNs > stats.maxBuildNs) {
        stats.maxBuildNs = durationNs;
    }
    TAG_LOGD(AceLogTag::ACE_SCROLL,
        "ScrollPH item built: component=%{public}d host=%{public}d index=%{public}d cache=%{public}d "
        "costUs=%{public}" PRId64 " estimateUs=%{public}" PRId64,
        static_cast<int32_t>(params.componentType), params.hostNodeId, params.index,
        static_cast<int32_t>(params.cacheBuild), durationNs / 1000,
        EstimateRealBuildDuration(params) / 1000);
}

ScrollPlaceholderManager::FrameObservationStats ScrollPlaceholderManager::GetLastFrameObservation(
    ScrollPlaceholderComponentType componentType) const
{
    return lastFrameStats_[ComponentIndex(componentType)];
}

void ScrollPlaceholderManager::CloseObservationFrame(int64_t vsyncTimestampNs)
{
    for (size_t i = 0; i < COMPONENT_TYPE_COUNT; i++) {
        const auto& stats = frameStats_[i];
        if (stats.observedBuilds == 0) {
            continue;
        }
        int64_t avgBuildNs = stats.observedBuilds == 0 ? 0 : stats.totalBuildNs / stats.observedBuilds;
        int64_t estimateNs = costModel_.EstimateRealBuildDuration(
            static_cast<ScrollPlaceholderComponentType>(i), std::string());
        // One summary per frame and container type: measured average item cost plus what the
        // load prediction would have suggested (build now vs defer to placeholder) this frame.
        TAG_LOGI(AceLogTag::ACE_SCROLL,
            "ScrollPH frame summary: component=%{public}d realBuilt=%{public}u avgCostUs=%{public}" PRId64
            " maxCostUs=%{public}" PRId64 " estimateUs=%{public}" PRId64 " suggestReal=%{public}u "
            "suggestPlaceholder=%{public}u remainingBudgetUs=%{public}" PRId64 " vsync=%{public}" PRId64,
            static_cast<int32_t>(i), stats.observedBuilds, avgBuildNs / 1000, stats.maxBuildNs / 1000,
            estimateNs / 1000, stats.suggestedReal, stats.suggestedPlaceholder,
            stats.lastRemainingBudgetNs / 1000, vsyncTimestampNs);
        ACE_SCOPED_TRACE_COMMERCIAL(
            "ScrollPH.FrameSummary[component:%d realBuilt:%u avgCostUs:%" PRId64 " estimateUs:%" PRId64
            " suggestReal:%u suggestPlaceholder:%u]",
            static_cast<int32_t>(i), stats.observedBuilds, avgBuildNs / 1000, estimateNs / 1000,
            stats.suggestedReal, stats.suggestedPlaceholder);
    }
    lastFrameStats_ = frameStats_;
    frameStats_ = {};
}

size_t ScrollPlaceholderManager::ComponentIndex(ScrollPlaceholderComponentType componentType)
{
    auto index = static_cast<size_t>(componentType);
    return index < COMPONENT_TYPE_COUNT ? index : 0;
}

ScrollPlaceholderManager::Diagnostics ScrollPlaceholderManager::GetDiagnostics() const
{
    Diagnostics diagnostics;
    diagnostics.predictBuildRealNow = predictBuildRealNow_.load(std::memory_order_relaxed);
    diagnostics.predictUsePlaceholder = predictUsePlaceholder_.load(std::memory_order_relaxed);
    diagnostics.realBuildExecuted = realBuildExecuted_.load(std::memory_order_relaxed);
    diagnostics.realBuildRequeued = realBuildRequeued_.load(std::memory_order_relaxed);
    diagnostics.realBuildDropped = realBuildDropped_.load(std::memory_order_relaxed);
    diagnostics.registerRejected = registerRejected_.load(std::memory_order_relaxed);
    diagnostics.lruEvictedTemplates = registry_.GetEvictedTemplateCount();
    diagnostics.flushRounds = flushRounds_.load(std::memory_order_relaxed);
    diagnostics.requestFrameCount = requestFrameCount_.load(std::memory_order_relaxed);
    diagnostics.observedRealBuilds = observedRealBuilds_.load(std::memory_order_relaxed);
    for (size_t i = 0; i < CANCEL_REASON_COUNT; i++) {
        diagnostics.cancelledByReason[i] = cancelledByReason_[i].load(std::memory_order_relaxed);
    }
    return diagnostics;
}

void ScrollPlaceholderManager::RequestFrameIfAlive()
{
    requestFrameCount_.fetch_add(1, std::memory_order_relaxed);
    auto pipeline = pipeline_.Upgrade();
    if (pipeline) {
        pipeline->RequestFrame();
    }
}

void ScrollPlaceholderManager::PurgeTemplateRealBuilds(
    const std::string& templateId, ScrollPlaceholderCancelReason reason)
{
    auto reasonIndex = static_cast<size_t>(reason);
    size_t cancelled = 0;
    std::deque<RealBuildTask> kept;
    for (auto& pending : pendingRealBuilds_) {
        if (pending.params.templateId == templateId) {
            cancelled++;
        } else {
            kept.push_back(std::move(pending));
        }
    }
    pendingRealBuilds_ = std::move(kept);
    if (cancelled > 0 && reasonIndex < CANCEL_REASON_COUNT) {
        cancelledByReason_[reasonIndex].fetch_add(cancelled, std::memory_order_relaxed);
    }
}

} // namespace OHOS::Ace::NG
