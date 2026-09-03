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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_template_registry.h"

namespace OHOS::Ace::NG {
namespace {
// At most 20 templates keep built placeholder instances at the same time.
constexpr size_t TEMPLATE_INSTANCE_LRU_CAPACITY = 20;
} // namespace

uint64_t ScrollPlaceholderTemplateRegistry::Register(
    const std::string& templateId, ScrollPlaceholderBuilder&& builder)
{
    if (templateId.empty()) {
        return 0;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    uint64_t generation = ++generationIndex_[templateId];
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        TemplateEntry entry;
        entry.templateId = templateId;
        entry.generation = generation;
        entry.builder = std::move(builder);
        it = entries_.emplace(templateId, std::move(entry)).first;
    } else {
        // Re-register publishes a new generation atomically: in-flight results of the old
        // generation become stale, previously cached instances and the copy source are
        // dropped (the new source is seeded by the registration path on the UI thread).
        it->second.generation = generation;
        it->second.builder = std::move(builder);
        it->second.sourceInstance = nullptr;
        it->second.cachedInstances.clear();
        it->second.cachedInstances.shrink_to_fit();
    }
    TouchLruLocked(it->second);
    EvictOverCapacityLocked();
    return generation;
}

bool ScrollPlaceholderTemplateRegistry::Unregister(const std::string& templateId)
{
    if (templateId.empty()) {
        return false;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return false;
    }
    if (it->second.hot) {
        lruOrder_.erase(it->second.lruIt);
    }
    // Bump the generation index so results already carrying the removed generation are stale
    // even before any re-register happens.
    uint64_t latest = generationIndex_[templateId];
    if (latest < it->second.generation) {
        latest = it->second.generation;
    }
    generationIndex_[templateId] = latest + 1;
    entries_.erase(it);
    return true;
}

bool ScrollPlaceholderTemplateRegistry::IsRegistered(const std::string& templateId) const
{
    if (templateId.empty()) {
        return false;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    return entries_.find(templateId) != entries_.end();
}

std::optional<ScrollPlaceholderTemplateSnapshot> ScrollPlaceholderTemplateRegistry::LookupForCreate(
    const std::string& templateId)
{
    if (templateId.empty()) {
        return std::nullopt;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return std::nullopt;
    }
    TouchLruLocked(it->second);
    EvictOverCapacityLocked();
    return MakeSnapshot(it->second);
}

std::optional<ScrollPlaceholderTemplateSnapshot> ScrollPlaceholderTemplateRegistry::Peek(
    const std::string& templateId) const
{
    if (templateId.empty()) {
        return std::nullopt;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return std::nullopt;
    }
    return MakeSnapshot(it->second);
}

uint64_t ScrollPlaceholderTemplateRegistry::GetCurrentGeneration(const std::string& templateId) const
{
    if (templateId.empty()) {
        return 0;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = generationIndex_.find(templateId);
    return it == generationIndex_.end() ? 0 : it->second;
}

void ScrollPlaceholderTemplateRegistry::SetTemplateSourceInstance(
    const std::string& templateId, const RefPtr<UINode>& instance)
{
    if (templateId.empty() || !instance) {
        return;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return;
    }
    it->second.sourceInstance = instance;
}

RefPtr<UINode> ScrollPlaceholderTemplateRegistry::GetTemplateSourceInstance(
    const std::string& templateId) const
{
    if (templateId.empty()) {
        return nullptr;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    return it == entries_.end() ? nullptr : it->second.sourceInstance;
}

void ScrollPlaceholderTemplateRegistry::CacheTemplateInstance(
    const std::string& templateId, const RefPtr<UINode>& instance)
{
    if (templateId.empty() || !instance) {
        return;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return;
    }
    // Cold (LRU-demoted) entries keep only their registration relation; and the pool never
    // holds more than capacity - 1 spare copies (the resident source takes one slot), so
    // concurrent background commits cannot overfill it.
    if (!it->second.hot ||
        it->second.cachedInstances.size() >= SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY - 1) {
        return;
    }
    it->second.cachedInstances.emplace_back(instance);
}

RefPtr<UINode> ScrollPlaceholderTemplateRegistry::AcquireTemplateInstance(const std::string& templateId)
{
    if (templateId.empty()) {
        return nullptr;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    if (it == entries_.end()) {
        return nullptr;
    }
    auto& instances = it->second.cachedInstances;
    while (!instances.empty()) {
        RefPtr<UINode> instance = instances.back();
        instances.pop_back();
        if (instance) {
            return instance;
        }
    }
    return nullptr;
}

size_t ScrollPlaceholderTemplateRegistry::GetCachedInstanceCount(const std::string& templateId) const
{
    if (templateId.empty()) {
        return 0;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    auto it = entries_.find(templateId);
    return it == entries_.end() ? 0 : it->second.cachedInstances.size();
}

size_t ScrollPlaceholderTemplateRegistry::GetHotTemplateCount() const
{
    std::lock_guard<std::mutex> guard(mutex_);
    return lruOrder_.size();
}

size_t ScrollPlaceholderTemplateRegistry::GetEvictedTemplateCount() const
{
    std::lock_guard<std::mutex> guard(mutex_);
    return evictedTemplateCount_;
}

void ScrollPlaceholderTemplateRegistry::Clear()
{
    std::lock_guard<std::mutex> guard(mutex_);
    entries_.clear();
    generationIndex_.clear();
    lruOrder_.clear();
}

void ScrollPlaceholderTemplateRegistry::TouchLruLocked(TemplateEntry& entry)
{
    if (entry.hot) {
        lruOrder_.erase(entry.lruIt);
    }
    lruOrder_.push_front(entry.templateId);
    entry.lruIt = lruOrder_.begin();
    entry.hot = true;
}

void ScrollPlaceholderTemplateRegistry::EvictOverCapacityLocked()
{
    while (lruOrder_.size() > TEMPLATE_INSTANCE_LRU_CAPACITY) {
        auto lastIt = std::prev(lruOrder_.end());
        auto entryIt = entries_.find(*lastIt);
        if (entryIt != entries_.end()) {
            // Demote to a cold entry: release the copy source and all unmounted instances,
            // keep the registration relation and generation semantics untouched.
            entryIt->second.sourceInstance = nullptr;
            entryIt->second.cachedInstances.clear();
            entryIt->second.cachedInstances.shrink_to_fit();
            entryIt->second.hot = false;
            evictedTemplateCount_++;
        }
        lruOrder_.erase(lastIt);
    }
}

ScrollPlaceholderTemplateSnapshot ScrollPlaceholderTemplateRegistry::MakeSnapshot(const TemplateEntry& entry)
{
    ScrollPlaceholderTemplateSnapshot snapshot;
    snapshot.templateId = entry.templateId;
    snapshot.generation = entry.generation;
    snapshot.builder = entry.builder;
    return snapshot;
}

} // namespace OHOS::Ace::NG
