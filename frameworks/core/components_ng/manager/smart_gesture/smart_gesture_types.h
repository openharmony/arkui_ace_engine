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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_TYPES_H

#include <cstdint>
#include <optional>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
enum class SmartGestureTrigger : uint8_t {
    TAP = 0,
    SLIDE_FORWARD,
    WRIST_BACK,
};

enum class SmartGestureOperateIntention : uint8_t {
    TAP = 0,
    SLIDE_FORWARD,
    BACK_PRESS,
};

enum class SmartGestureProposalType : uint8_t {
    NONE_ACTION = 0,
    CLICK,
    SELECT,
    SCROLL,
    BACK_PRESS,
};

enum class SmartGestureDirection : uint8_t {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

struct ScrollingConfig {
    std::optional<int32_t> count;
    std::optional<double> distance;
    SmartGestureDirection direction = SmartGestureDirection::FORWARD;

    bool HasValue() const
    {
        return count.has_value() || distance.has_value();
    }
};

struct SmartGestureProposal {
    SmartGestureProposalType type = SmartGestureProposalType::NONE_ACTION;
    SmartGestureOperateIntention operateIntention = SmartGestureOperateIntention::TAP;
    WeakPtr<FrameNode> targetNode;
    std::optional<ScrollingConfig> scrollingConfig;

    SmartGestureProposal() = default;
    explicit SmartGestureProposal(SmartGestureProposalType proposalType,
        SmartGestureOperateIntention intention = SmartGestureOperateIntention::TAP)
        : type(proposalType), operateIntention(intention)
    {}
    SmartGestureProposal(
        SmartGestureProposalType proposalType, SmartGestureOperateIntention intention, const RefPtr<FrameNode>& node);
    SmartGestureProposal(SmartGestureProposalType proposalType, SmartGestureOperateIntention intention,
        const RefPtr<FrameNode>& node, const ScrollingConfig& config);

    RefPtr<FrameNode> GetTargetNode() const;
};

struct SmartGestureHandlingResolution {
    bool isConsumed = true;
    bool hasSelectedProposal = false;
    std::optional<SmartGestureProposal> selectedProposal;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_TYPES_H
