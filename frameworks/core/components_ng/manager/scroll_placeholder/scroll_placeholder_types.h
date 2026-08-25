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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H

#include <cstdint>
#include <functional>
#include <optional>
#include <string>

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

class UINode;
class FrameNode;

/**
 * FEAT-005: shared contracts of the scroll placeholder framework.
 *
 * The feature is opt-in: a List/Grid/WaterFlow participates only when the
 * developer sets the `scrollPlaceHolder(provider)` attribute on it. All types
 * below are internal (framework) contracts; the public ArkTS surface is
 * declared in interface_sdk-js (PR #35330).
 */

/** Layout suggestion returned by the developer provider. Values are in vp. */
struct ScrollPlaceHolderSizeOption {
    std::optional<float> width;
    std::optional<float> height;
};

/** Result of the developer `scrollPlaceHolder((index) => {...})` callback. */
struct ScrollPlaceHolderOptions {
    /** Registered template id. Empty/unknown ids fall back to the default placeholder. */
    std::string id;
    /** Suggested placeholder size; the real item is re-laid-out with normal constraints on swap. */
    std::optional<ScrollPlaceHolderSizeOption> size;
};

/**
 * Provider: index -> placeholder options. Returning std::nullopt selects the
 * default (layout-only) placeholder. Provider is always invoked on the UI thread.
 */
using ScrollPlaceHolderProvider = std::function<std::optional<ScrollPlaceHolderOptions>(int32_t index)>;

/**
 * Immutable placeholder template builder. Placeholder templates are static
 * subtrees (declared via `@Builder({ isScrollPlaceHolder: true })`); builders
 * must not touch reactive state, gestures or business callbacks. The compiler
 * side validation lives in arkcompiler_ets_frontend; the runtime treats every
 * registered builder as read-only.
 */
using ScrollPlaceHolderBuilder = std::function<RefPtr<UINode>()>;

/**
 * Container adapter hook: creates the item shell node for a placeholder on the
 * UI thread, e.g. a ListItem for List, GridItem for Grid, FlowItem for
 * WaterFlow. The manager fills the shell with the placeholder visual subtree.
 */
using ScrollPlaceholderItemFactory = std::function<RefPtr<FrameNode>(const ScrollPlaceHolderOptions& options)>;

/** Decision produced before a real item build. */
enum class ScrollPlaceholderDecision {
    /** Budget looks sufficient: build the real item synchronously. */
    SYNC_BUILD = 0,
    /** Budget insufficient: mount a placeholder, queue the real build as a UI-thread frame task. */
    DEFER_WITH_PLACEHOLDER = 1,
};

/**
 * Generation snapshot attached to every placeholder/real build task.
 * A result may be committed only when the snapshot still matches the current
 * generations of its container. See ScrollPlaceholderManager for the owning
 * counters (five kinds: container / data / item / template / task).
 */
struct ScrollPlaceholderGeneration {
    uint64_t containerGen = 0;
    uint64_t dataGen = 0;
    uint64_t templateGen = 0;

    bool Matches(const ScrollPlaceholderGeneration& other) const
    {
        return containerGen == other.containerGen && dataGen == other.dataGen && templateGen == other.templateGen;
    }
};

/** Result of a real-build task, reported back to the manager for diagnostics. */
enum class ScrollPlaceholderCommitResult {
    COMMITTED = 0,      // real node built and placeholder replaced
    STALE_DROPPED = 1,  // generation mismatch: result discarded
    CANCELLED = 2,      // container destroyed / item recycled before execution
    FAILED = 3,         // build failed; placeholder stays until next attempt
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H
