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

#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr double DEFAULT_REFRESH_RATE = 60.0;
constexpr double NS_PER_SECOND = 1e9;
} // namespace

ScrollPlaceholderManager::ScrollPlaceholderManager(const WeakPtr<PipelineContext>& context) : context_(context) {}

uint64_t ScrollPlaceholderManager::RegisterTemplate(const std::string& id, ScrollPlaceholderBuilder&& builder)
{
    if (id.empty() || !builder) {
        TAG_LOGW(AceLogTag::ACE_SCROLL, "scroll placeholder template register rejected: invalid id or builder");
        return 0;
    }
    std::lock_guard<std::mutex> lock(templateMutex_);
    auto iter = templates_.find(id);
    if (iter != templates_.end()) {
        // Atomic re-publish: publish a new generation under the same id.
        iter->second.builder = std::move(builder);
        iter->second.generation = nextTemplateGeneration_++;
        TAG_LOGI(AceLogTag::ACE_SCROLL, "scroll placeholder template republished id=%{public}s gen=%{public}" PRIu64,
            id.c_str(), iter->second.generation);
        return iter->second.generation;
    }
    TemplateRecord record { std::move(builder), nextTemplateGeneration_++ };
    auto generation = record.generation;
    templates_.emplace(id, std::move(record));
    return generation;
}

void ScrollPlaceholderManager::UnregisterTemplate(const std::string& id)
{
    std::lock_guard<std::mutex> lock(templateMutex_);
    templates_.erase(id);
}

bool ScrollPlaceholderManager::HasTemplate(const std::string& id) const
{
    std::lock_guard<std::mutex> lock(templateMutex_);
    return templates_.find(id) != templates_.end();
}

uint64_t ScrollPlaceholderManager::GetTemplateGeneration(const std::string& id) const
{
    std::lock_guard<std::mutex> lock(templateMutex_);
    auto iter = templates_.find(id);
    return iter == templates_.end() ? 0 : iter->second.generation;
}

void ScrollPlaceholderManager::RegisterContainer(const WeakPtr<FrameNode>& host,
    ScrollPlaceholderProvider&& provider, ScrollPlaceholderItemFactory&& itemFactory)
{
    auto hostNode = host.Upgrade();
    CHECK_NULL_VOID(hostNode);
    if (!provider || !itemFactory) {
        return;
    }
    auto& record = containers_[hostNode->GetId()];
    record.host = host;
    record.provider = std::move(provider);
    record.itemFactory = std::move(itemFactory);
    record.containerGen++;
    TAG_LOGI(AceLogTag::ACE_SCROLL, "scroll placeholder container registered hostId=%{public}d",
        hostNode->GetId());
}

void ScrollPlaceholderManager::UnregisterContainer(int32_t hostId)
{
    CancelContainerTasks(hostId);
    containers_.erase(hostId);
}

bool ScrollPlaceholderManager::IsContainerRegistered(int32_t hostId) const
{
    return containers_.find(hostId) != containers_.end();
}

void ScrollPlaceholderManager::NotifyDataChanged(int32_t hostId)
{
    auto iter = containers_.find(hostId);
    if (iter == containers_.end()) {
        return;
    }
    iter->second.dataGen++;
    // Stale tasks are rejected during the next flush via generation checks.
}

ScrollPlaceholderGeneration ScrollPlaceholderManager::GetContainerGeneration(int32_t hostId) const
{
    ScrollPlaceholderGeneration gen;
    auto iter = containers_.find(hostId);
    if (iter == containers_.end()) {
        return gen;
    }
    gen.containerGen = iter->second.containerGen;
    gen.dataGen = iter->second.dataGen;
    return gen;
}

WeakPtr<FrameNode> ScrollPlaceholderManager::GetRegisteredHost(int32_t hostId) const
{
    auto iter = containers_.find(hostId);
    return iter == containers_.end() ? nullptr : iter->second.host;
}

void ScrollPlaceholderManager::RecordBuildCost(
    int32_t hostId, const std::string& templateKey, int64_t durationNs)
{
    predictor_.RecordBuildCost(templateKey, durationNs);
}

std::optional<ScrollPlaceholderDecision> ScrollPlaceholderManager::DecideItemBuild(int32_t hostId, int32_t index)
{
    auto iter = containers_.find(hostId);
    if (iter == containers_.end()) {
        return std::nullopt; // feature not enabled on this container
    }
    auto options = ResolveOptions(iter->second, index);
    std::string templateKey = options.id.empty() ? std::string("default#") + std::to_string(hostId) : options.id;
    auto estimate = predictor_.EstimateBuildCost(templateKey);
    auto remaining = GetRemainingFrameBudgetNs();
    return ScrollPlaceholderPredictor::Decide(estimate.estimateNs, remaining);
}

int64_t ScrollPlaceholderManager::GetRemainingFrameBudgetNs() const
{
    auto context = context_.Upgrade();
    if (!context) {
        return static_cast<int64_t>(NS_PER_SECOND / DEFAULT_REFRESH_RATE);
    }
    double refreshRate = context->GetRefreshRateValue();
    if (refreshRate <= 0.0) {
        refreshRate = DEFAULT_REFRESH_RATE;
    }
    const int64_t frameBudget = static_cast<int64_t>(NS_PER_SECOND / refreshRate);
    const int64_t recvTime = context->GetFrameRecvTime();
    const int64_t now = GetSysTimestamp();
    if (recvTime < 0 || now < recvTime) {
        return frameBudget;
    }
    const int64_t elapsed = now - recvTime;
    return std::max<int64_t>(frameBudget - elapsed, 0);
}

ScrollPlaceholderManager::ContainerRecord* ScrollPlaceholderManager::FindContainerMutable(int32_t hostId)
{
    auto iter = containers_.find(hostId);
    return iter == containers_.end() ? nullptr : &iter->second;
}

const ScrollPlaceholderManager::ContainerRecord* ScrollPlaceholderManager::FindContainer(int32_t hostId) const
{
    auto iter = containers_.find(hostId);
    return iter == containers_.end() ? nullptr : &iter->second;
}

ScrollPlaceholderOptions ScrollPlaceholderManager::ResolveOptions(
    const ContainerRecord& container, int32_t index)
{
    ScrollPlaceholderOptions options;
    if (container.provider) {
        auto provided = container.provider(index);
        if (provided.has_value()) {
            options = std::move(provided.value());
        }
    }
    if (!options.id.empty() && !HasTemplate(options.id)) {
        // Unknown id: fall back to the default placeholder, keep scrolling alive (AC-5).
        TAG_LOGW(AceLogTag::ACE_SCROLL, "scroll placeholder id not registered, fallback: id=%{public}s index=%{public}d",
            options.id.c_str(), index);
        options.id.clear();
        ++diagnostics_.defaultFallbackUsed;
    }
    return options;
}

RefPtr<UINode> ScrollPlaceholderManager::BuildTemplateSnapshot(const std::string& id)
{
    if (id.empty()) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(templateMutex_);
    auto iter = templates_.find(id);
    if (iter == templates_.end()) {
        return nullptr;
    }
    // Placeholder templates are immutable static subtrees: invoking the builder
    // again yields an equivalent snapshot. Draft: build on the UI thread; the
    // worker-pool preparation path (P-05) will replace this with a clone of a
    // pre-built snapshot guarded by the template generation.
    return iter->second.builder ? iter->second.builder() : nullptr;
}

ScrollPlaceholderManager::PlaceholderItem ScrollPlaceholderManager::CreatePlaceholderItem(int32_t hostId, int32_t index)
{
    PlaceholderItem result;
    auto* container = FindContainerMutable(hostId);
    CHECK_NULL_RETURN(container, result);
    auto host = container->host.Upgrade();
    CHECK_NULL_RETURN(host, result);
    auto options = ResolveOptions(*container, index);
    result.templateId = options.id;
    result.templateKey = options.id.empty() ? std::string("default#") + std::to_string(hostId) : options.id;

    auto itemShell = container->itemFactory(options);
    CHECK_NULL_RETURN(itemShell, result);
    auto layoutProperty = itemShell->GetLayoutProperty();
    if (layoutProperty && options.size.has_value()) {
        CalcLength width;
        CalcLength height;
        if (options.size->width.has_value()) {
            width = CalcLength(options.size->width.value());
        }
        if (options.size->height.has_value()) {
            height = CalcLength(options.size->height.value());
        }
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
    }
    auto visual = BuildTemplateSnapshot(options.id);
    RefPtr<FrameNode> visualFrame;
    if (!visual) {
        // Default placeholder: minimal transparent layout-only node (AR-UX-01
        // tracks the final default visual; the draft uses a plain FrameNode).
        visualFrame = FrameNode::CreateFrameNode(
            "ScrollPlaceholderVisual", ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<Pattern>());
        CHECK_NULL_RETURN(visualFrame, result);
        visual = visualFrame;
        ++diagnostics_.defaultFallbackUsed;
    } else {
        visualFrame = AceType::DynamicCast<FrameNode>(visual);
    }
    if (visualFrame && options.size.has_value()) {
        auto visualProperty = visualFrame->GetLayoutProperty();
        if (visualProperty) {
            CalcLength width;
            CalcLength height;
            if (options.size->width.has_value()) {
                width = CalcLength(options.size->width.value());
            }
            if (options.size->height.has_value()) {
                height = CalcLength(options.size->height.value());
            }
            visualProperty->UpdateUserDefinedIdealSize(CalcSize(width, height));
        }
    }
    itemShell->AddChild(visual);
    itemShell->MarkNeedSyncRenderTree();
    ++diagnostics_.placeholdersCreated;
    ++placeholdersThisFrame_;
    result.node = std::move(itemShell);
    return result;
}

void ScrollPlaceholderManager::EnqueueRealBuild(
    int32_t hostId, int32_t index, const ScrollPlaceholderGeneration& gen, RealBuildTaskBody&& body)
{
    auto* container = FindContainerMutable(hostId);
    CHECK_NULL_VOID(container);
    CHECK_NULL_VOID(body);
    int32_t pendingForContainer = 0;
    for (const auto& task : pendingTasks_) {
        if (task.hostId == hostId) {
            ++pendingForContainer;
        }
    }
    if (pendingForContainer >= MAX_PENDING_PER_CONTAINER) {
        // Queue overflow protection on fast fling: drop the oldest task of this
        // container; its placeholder stays until the item is recycled.
        for (auto it = pendingTasks_.begin(); it != pendingTasks_.end(); ++it) {
            if (it->hostId == hostId) {
                pendingTasks_.erase(it);
                ++diagnostics_.cancelled;
                break;
            }
        }
    }
    RealBuildTask task;
    task.taskId = nextTaskId_++;
    task.hostId = hostId;
    task.index = index;
    task.gen = gen;
    task.body = std::move(body);
    pendingTasks_.emplace_back(std::move(task));
    ++diagnostics_.realBuildEnqueued;
}

void ScrollPlaceholderManager::DropTask(std::deque<RealBuildTask>::iterator& it, ScrollPlaceholderCommitResult reason)
{
    if (reason == ScrollPlaceholderCommitResult::STALE_DROPPED) {
        ++diagnostics_.staleDropped;
    } else if (reason == ScrollPlaceholderCommitResult::CANCELLED) {
        ++diagnostics_.cancelled;
    }
    it = pendingTasks_.erase(it);
}

void ScrollPlaceholderManager::FlushRealBuildTasks(int64_t deadlineNs)
{
    if (pendingTasks_.empty()) {
        return;
    }
    ACE_SCOPED_TRACE("ScrollPlaceholder::FlushRealBuild size:%zu", pendingTasks_.size());
    int32_t executed = 0;
    auto it = pendingTasks_.begin();
    while (it != pendingTasks_.end()) {
        if (executed >= MAX_REAL_BUILD_PER_FRAME) {
            break; // keep the rest for the next frame
        }
        if (GetSysTimestamp() > deadlineNs) {
            break; // out of budget for this frame
        }
        auto* container = FindContainerMutable(it->hostId);
        if (!container) {
            DropTask(it, ScrollPlaceholderCommitResult::CANCELLED);
            continue;
        }
        // Generation check (container/data): template generation is validated
        // inside the task body against the registry at commit time.
        ScrollPlaceholderGeneration current;
        current.containerGen = container->containerGen;
        current.dataGen = container->dataGen;
        current.templateGen = it->gen.templateGen;
        if (!it->gen.Matches(current)) {
            TAG_LOGI(AceLogTag::ACE_SCROLL,
                "scroll placeholder task stale dropped hostId=%{public}d index=%{public}d", it->hostId, it->index);
            DropTask(it, ScrollPlaceholderCommitResult::STALE_DROPPED);
            continue;
        }
        if (!it->body) {
            DropTask(it, ScrollPlaceholderCommitResult::FAILED);
            continue;
        }
        int64_t buildDuration = 0;
        auto result = it->body(buildDuration);
        if (result == ScrollPlaceholderCommitResult::COMMITTED) {
            ++diagnostics_.realBuildCommitted;
            ++executed;
        }
        // The body has consumed the task regardless of outcome (COMMITTED /
        // STALE_DROPPED / FAILED all resolve the placeholder one way or another).
        it = pendingTasks_.erase(it);
    }
}

void ScrollPlaceholderManager::CancelContainerTasks(int32_t hostId)
{
    auto it = pendingTasks_.begin();
    while (it != pendingTasks_.end()) {
        if (it->hostId == hostId) {
            it = pendingTasks_.erase(it);
            ++diagnostics_.cancelled;
        } else {
            ++it;
        }
    }
}

bool ScrollPlaceholderManager::HasPendingRealBuild(int32_t hostId) const
{
    for (const auto& task : pendingTasks_) {
        if (task.hostId == hostId) {
            return true;
        }
    }
    return false;
}

bool ScrollPlaceholderManager::ShouldContinuePlaceholderLayout(int32_t hostId)
{
    if (!IsContainerRegistered(hostId)) {
        return false;
    }
    // Placeholder creation and measurement is cheap; cap the extra work per
    // frame so a very fast fling still yields within the frame.
    return placeholdersThisFrame_ < MAX_PLACEHOLDER_PER_FRAME;
}

void ScrollPlaceholderManager::OnFrameStart()
{
    placeholdersThisFrame_ = 0;
}

} // namespace OHOS::Ace::NG
