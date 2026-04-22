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

#include "core/components_ng/manager/smart_gesture/smart_gesture_decider.h"

#include <algorithm>
#include <optional>

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
namespace {
bool IsNodeClickable(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureHub = eventHub->GetGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    return static_cast<bool>(gestureHub->GetCommonClickEvent());
}
} // namespace

std::optional<SmartGestureProposal> SmartGestureDecider::BuildDefaultProposal(SmartGestureTrigger trigger,
    const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode,
    const std::vector<RefPtr<FrameNode>>& centerHitPath)
{
    switch (trigger) {
        case SmartGestureTrigger::TAP:
            if (visiblePrimaryNodes.empty()) {
                return SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);
            }
            if (selectedNode && IsNodeClickable(selectedNode)) {
                return SmartGestureProposal(
                    SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, selectedNode);
            }
            if (!selectedNode) {
                return SmartGestureProposal(
                    SmartGestureProposalType::SELECT, SmartGestureOperateIntention::TAP, visiblePrimaryNodes.front());
            }
            return SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);
        case SmartGestureTrigger::SLIDE_FORWARD:
            if (!visiblePrimaryNodes.empty()) {
                auto nextNode = GetNextVisiblePrimaryNode(visiblePrimaryNodes, selectedNode);
                if (nextNode) {
                    return SmartGestureProposal(
                        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, nextNode);
                }
                return SmartGestureProposal(
                    SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::SLIDE_FORWARD);
            }
            return BuildCenterHitProposal(centerHitPath);
        case SmartGestureTrigger::WRIST_BACK:
            return SmartGestureProposal(SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);
    }
    return std::nullopt;
}

RefPtr<FrameNode> SmartGestureDecider::GetFirstVisiblePrimaryNode(
    const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes)
{
    if (visiblePrimaryNodes.empty()) {
        return nullptr;
    }
    return visiblePrimaryNodes.front();
}

RefPtr<FrameNode> SmartGestureDecider::GetNextVisiblePrimaryNode(
    const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode)
{
    if (visiblePrimaryNodes.empty()) {
        return nullptr;
    }
    if (!selectedNode) {
        return visiblePrimaryNodes.front();
    }
    auto iter = std::find_if(visiblePrimaryNodes.begin(), visiblePrimaryNodes.end(),
        [selectedId = selectedNode->GetId()](
            const RefPtr<FrameNode>& node) { return node && node->GetId() == selectedId; });
    if (iter == visiblePrimaryNodes.end()) {
        return visiblePrimaryNodes.front();
    }
    if (std::next(iter) == visiblePrimaryNodes.end()) {
        return nullptr;
    }
    return *std::next(iter);
}

std::optional<SmartGestureProposal> SmartGestureDecider::BuildCenterHitProposal(
    const std::vector<RefPtr<FrameNode>>& centerHitPath)
{
    for (const auto& node : centerHitPath) {
        if (!node) {
            continue;
        }
        auto pattern = node->GetPattern();
        if (!pattern) {
            continue;
        }
        if (!pattern->IsScrollAble()) {
            continue;
        }
        auto config = pattern->GetDefaultScrollingConfig();
        if (!config.has_value() || !config->HasValue()) {
            continue;
        }
        return SmartGestureProposal(
            SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config.value());
    }
    return SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::SLIDE_FORWARD);
}
} // namespace OHOS::Ace::NG
