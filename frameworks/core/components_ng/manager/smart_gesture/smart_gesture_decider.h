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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_DECIDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_DECIDER_H

#include <optional>
#include <vector>

#include "core/components_ng/manager/smart_gesture/smart_gesture_types.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT SmartGestureDecider final {
public:
    static std::optional<SmartGestureProposal> BuildDefaultProposal(SmartGestureTrigger trigger,
        const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode,
        const std::vector<RefPtr<FrameNode>>& centerHitPath);

    static std::optional<SmartGestureProposal> BuildCenterHitProposal(
        const std::vector<RefPtr<FrameNode>>& centerHitPath);

    static RefPtr<FrameNode> GetFirstVisiblePrimaryNode(const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes);

    static RefPtr<FrameNode> GetNextVisiblePrimaryNode(
        const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_DECIDER_H
