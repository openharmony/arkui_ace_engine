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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TEMPLATE_REGISTRY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TEMPLATE_REGISTRY_H

#include <cstdint>
#include <list>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"

namespace OHOS::Ace::NG {

// Immutable snapshot handed out to creation paths; worker-visible state is limited to this value.
struct ScrollPlaceholderTemplateSnapshot {
    std::string templateId;
    uint64_t generation = 0;
    ScrollPlaceholderBuilder builder;
};

// Per container template registry (design ADR-3/ADR-12):
// - registration relation (id + builder handle + generation) persists without bound;
// - built placeholder instances are retained per template entry under an LRU of hot entries
//   (capacity 20), each hot entry holding at most SCROLL_PLACEHOLDER_INSTANCE_CACHE_CAPACITY
//   instances: eviction releases all unmounted instances of the least recently used entry
//   and demotes it to a cold entry keeping only the registration relation;
// - generation is monotonically increasing per id across re-register and unregister, so any
//   in-flight result carrying an older generation is stale by comparison;
// - heat is promoted only by register and by create-path lookup; isRegistered never promotes.
class ScrollPlaceholderTemplateRegistry {
public:
    ScrollPlaceholderTemplateRegistry() = default;
    ~ScrollPlaceholderTemplateRegistry() = default;

    // Registers or atomically re-publishes the template; returns the new generation.
    uint64_t Register(const std::string& templateId, ScrollPlaceholderBuilder&& builder);
    // Idempotent unregister; returns true when an entry was actually removed.
    bool Unregister(const std::string& templateId);
    // Read-only query covering hot and cold entries; never promotes LRU heat.
    bool IsRegistered(const std::string& templateId) const;
    // Create-path lookup: promotes the entry to the MRU end and may evict overflow entries.
    std::optional<ScrollPlaceholderTemplateSnapshot> LookupForCreate(const std::string& templateId);
    // Validation-path lookup without LRU side effects.
    std::optional<ScrollPlaceholderTemplateSnapshot> Peek(const std::string& templateId) const;
    // Latest issued generation for the id (0 when never registered); survives removal.
    uint64_t GetCurrentGeneration(const std::string& templateId) const;

    // Instance retention of built (unmounted) placeholder nodes, owned by hot entries.
    void CacheTemplateInstance(const std::string& templateId, const RefPtr<UINode>& instance);
    RefPtr<UINode> AcquireTemplateInstance(const std::string& templateId);
    size_t GetCachedInstanceCount(const std::string& templateId) const;
    size_t GetHotTemplateCount() const;
    size_t GetEvictedTemplateCount() const;

    // Releases everything (container destroy).
    void Clear();

private:
    struct TemplateEntry {
        std::string templateId;
        uint64_t generation = 0;
        ScrollPlaceholderBuilder builder;
        std::vector<RefPtr<UINode>> cachedInstances;
        bool hot = false;
        std::list<std::string>::iterator lruIt;
    };

    void TouchLruLocked(TemplateEntry& entry);
    void EvictOverCapacityLocked();
    static ScrollPlaceholderTemplateSnapshot MakeSnapshot(const TemplateEntry& entry);

    mutable std::mutex mutex_;
    std::unordered_map<std::string, TemplateEntry> entries_;
    std::unordered_map<std::string, uint64_t> generationIndex_;
    std::list<std::string> lruOrder_; // front = most recently used
    size_t evictedTemplateCount_ = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TEMPLATE_REGISTRY_H
