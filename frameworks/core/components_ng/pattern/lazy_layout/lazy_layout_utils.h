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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H

#include <optional>
#include <vector>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

// Ancestor WaterFlow + whether the path crosses a FlowItem (a path through FlowItem makes the WaterFlow's
// lane count irrelevant to the lazy contract).
struct WaterFlowAncestorInfo {
    RefPtr<FrameNode> node;
    bool throughFlowItem = false;
};

struct ACE_FORCE_EXPORT LazyLayoutUtils {
    static bool IsAllowedIntermediateNode(const RefPtr<UINode>& node);
    static bool IsVerticalScrollableParent(const RefPtr<UINode>& node);
    static bool IsScrollableParent(const RefPtr<UINode>& node, Axis axis);
    static void ValidateLazyLayoutParent(const RefPtr<FrameNode>& host, const std::string& componentName);
    static void ValidateLazyLayoutParentWithAxis(
        const RefPtr<FrameNode>& host, const std::string& componentName, Axis axis);
    static std::optional<ViewPosReference> GetViewPosReference(
        const RefPtr<FrameNode>& frameNode,
        const std::vector<std::string>& extraAllowedTags = {});

    // True iff a WaterFlow ancestor exists WITHOUT crossing a FlowItem.
    static bool HasDirectWaterFlowAncestor(const RefPtr<FrameNode>& frameNode);

    static std::optional<WaterFlowAncestorInfo> FindWaterFlowAncestorInfo(const RefPtr<FrameNode>& frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H
