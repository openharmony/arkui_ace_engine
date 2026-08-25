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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_UTILS_H

#include <string>

#include "base/memory/ace_type.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"

namespace OHOS::Ace::NG {

class UINode;
class FrameNode;
class LayoutWrapper;
class PipelineContext;

/**
 * FEAT-005 helpers shared by the lazy syntax resolver and the three
 * scrollable containers (List / Grid / WaterFlow).
 */
class ACE_EXPORT ScrollPlaceholderUtils {
public:
    ScrollPlaceholderUtils() = delete;

    /** True when FEAT-005 scroll placeholder support is compiled in. */
    static bool IsSupported()
    {
        return true;
    }

    /**
     * Returns the per-pipeline coordinator of the pipeline owning [node],
     * creating it on first use. Nullptr when no pipeline is reachable.
     */
    static RefPtr<ScrollPlaceholderManager> GetManager(const RefPtr<UINode>& node);
    static RefPtr<ScrollPlaceholderManager> GetManager(PipelineContext* context);

    /**
     * Walks up from [start] (a LazyForEachNode or any descendant) to the
     * nearest List/Grid/WaterFlow host frame node that is placeholder-enabled.
     * Returns nullptr when the enclosing scroll container did not opt in.
     * Bounded by a depth cap to survive deep hierarchies.
     */
    static RefPtr<FrameNode> FindEnabledHost(const RefPtr<UINode>& start);

    /** True when [tag] is one of the three supported scroll containers. */
    static bool IsScrollContainerTag(const std::string& tag);

    /**
     * Layout-algorithm hook: returns true when a layout loop that hit its
     * response deadline may continue with placeholder items (feature enabled
     * and per-frame placeholder budget not exhausted).
     */
    static bool ShouldContinuePlaceholderLayout(LayoutWrapper* layoutWrapper);

    /**
     * Notifies the coordinator that the dataset of the scroll container above
     * [lazyNode] changed: pending placeholder real-builds become stale and are
     * dropped at commit time (generation check).
     */
    static void NotifyPlaceholderDataChanged(const RefPtr<UINode>& lazyNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_UTILS_H
