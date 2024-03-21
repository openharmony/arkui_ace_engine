/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/accessibility/accessibility_manager_ng.h"

#include "core/accessibility/accessibility_constants.h"
#include "core/accessibility/accessibility_session_adapter.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event)
{
    if (root == nullptr ||
        !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        event.sourceType != SourceType::MOUSE) {
        return;
    }
    AccessibilityHoverEventType type = AccessibilityHoverEventType::MOVE;
    switch (event.action) {
        case MouseAction::WINDOW_ENTER:
            type = AccessibilityHoverEventType::ENTER;
            break;
        case MouseAction::MOVE:
            type = AccessibilityHoverEventType::MOVE;
            break;
        case MouseAction::WINDOW_LEAVE:
            type = AccessibilityHoverEventType::EXIT;
            break;
        default:
            return;
    }
    PointF point(event.x, event.y);
    HandleAccessibilityHoverEventInner(root, point, SourceType::MOUSE, type, event.time);
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event)
{
    if (root == nullptr ||
        !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        event.sourceType == SourceType::MOUSE) {
        return;
    }
    AccessibilityHoverEventType type = AccessibilityHoverEventType::MOVE;
    switch (event.type) {
        case TouchType::HOVER_ENTER:
            type = AccessibilityHoverEventType::ENTER;
            break;
        case TouchType::HOVER_MOVE:
            type = AccessibilityHoverEventType::MOVE;
            break;
        case TouchType::HOVER_EXIT:
            type = AccessibilityHoverEventType::EXIT;
            break;
        default:
            return;
    }
    PointF point(event.x, event.y);
    if (event.pointers.size() > 1 && event.sourceType == SourceType::TOUCH) {
        if (hoverState_.source == SourceType::TOUCH) {
            ResetHoverState();
            return;
        }
    }
    HandleAccessibilityHoverEventInner(root, point, event.sourceType, type, event.time);
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, float pointX, float pointY,
    int32_t sourceType, int32_t eventType, int64_t timeMs)
{
    if (root == nullptr ||
        !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        eventType < 0 || eventType >= AccessibilityHoverEventType::Count) {
        return;
    }
    PointF point(pointX, pointY);
    TimeStamp time((std::chrono::milliseconds(timeMs)));
    HandleAccessibilityHoverEventInner(root, point, static_cast<SourceType>(sourceType),
        static_cast<AccessibilityHoverEventType>(eventType), time);
}

void AccessibilityManagerNG::HandleAccessibilityHoverEventInner(
    const RefPtr<FrameNode>& root,
    const PointF& point,
    SourceType sourceType,
    AccessibilityHoverEventType eventType,
    TimeStamp time)
{
    static constexpr size_t THROTTLE_INTERVAL_HOVER_EVENT = 100;
    size_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(time - hoverState_.time).count();
    if (!hoverState_.idle && duration < THROTTLE_INTERVAL_HOVER_EVENT) {
        return;
    }
    static constexpr size_t MIN_SOURCE_CHANGE_GAP_MS = 1000;
    if (sourceType != hoverState_.source && !hoverState_.idle) {
        if (duration < MIN_SOURCE_CHANGE_GAP_MS) {
            return;
        }
        ResetHoverState();
    }

    ACE_SCOPED_TRACE("HandleAccessibilityHoverEventInner");
    if (eventType == AccessibilityHoverEventType::ENTER) {
        ResetHoverState();
    }
    std::vector<WeakPtr<FrameNode>> currentNodesHovering;
    std::vector<RefPtr<FrameNode>> lastNodesHovering;
    std::vector<int32_t> lastNodesHoveringId;
    for (const auto& nodeWeak: hoverState_.nodesHovering) {
        auto node = nodeWeak.Upgrade();
        if (node != nullptr) {
            lastNodesHovering.push_back(node);
            lastNodesHoveringId.push_back(node->GetId());
        }
    }
    if (eventType != AccessibilityHoverEventType::EXIT) {
        std::unique_ptr<AccessibilityProperty::HoverTestDebugTraceInfo> debugInfo = nullptr;
        AccessibilityHoverTestPath path = AccessibilityProperty::HoverTest(point, root, debugInfo);
        for (const auto& node: path) {
            auto id = node->GetId();
            if (std::find(lastNodesHoveringId.begin(), lastNodesHoveringId.end(), id) != lastNodesHoveringId.end() ||
                AccessibilityProperty::IsAccessibilityFocusable(node)) {
                currentNodesHovering.push_back(node);
            }
        }
    }

    static constexpr int32_t INVALID_NODE_ID = -1;
    int32_t lastHoveringId = INVALID_NODE_ID;
    RefPtr<FrameNode> lastHovering = nullptr;
    if (!lastNodesHovering.empty()) {
        lastHovering = lastNodesHovering.back();
        lastHoveringId = lastHovering->GetId();
    }
    int32_t currentHoveringId = INVALID_NODE_ID;
    RefPtr<FrameNode> currentHovering = nullptr;
    if (!currentNodesHovering.empty()) {
        currentHovering = currentNodesHovering.back().Upgrade();
        currentHoveringId = currentHovering->GetId();
    }
    if (lastHoveringId != INVALID_NODE_ID && lastHoveringId != currentHoveringId) {
        lastHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_EXIT_EVENT);
        NotifyHoverEventToNodeSession(lastHovering, root, point,
            sourceType, AccessibilityHoverEventType::EXIT, time);
    }
    if (currentHoveringId != INVALID_NODE_ID) {
        if (currentHoveringId != lastHoveringId) {
            currentHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_ENTER_EVENT);
        }
        NotifyHoverEventToNodeSession(currentHovering, root, point,
            sourceType, eventType, time);
    }

    hoverState_.nodesHovering = std::move(currentNodesHovering);
    hoverState_.time = time;
    hoverState_.source = sourceType;
    hoverState_.idle = eventType == AccessibilityHoverEventType::EXIT;
}

void AccessibilityManagerNG::NotifyHoverEventToNodeSession(const RefPtr<FrameNode>& node,
    const RefPtr<FrameNode>& rootNode, const PointF& pointRoot,
    SourceType sourceType, AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto sessionAdapter = AccessibilitySessionAdapter::GetSessionAdapter(node);
    CHECK_NULL_VOID(sessionAdapter);
    PointF pointNode(pointRoot);
    if (RenderContext::ConvertPointFromAncestorToNode(rootNode, node, pointRoot, pointNode)) {
        sessionAdapter->TransferHoverEvent(pointNode, sourceType, eventType, time);
    }
}

void AccessibilityManagerNG::ResetHoverState()
{
    hoverState_.idle = true;
    hoverState_.nodesHovering.clear();
}

void AccessibilityManagerNG::HoverTestDebug(const RefPtr<FrameNode>& root, const PointF& point,
    std::string& summary, std::string& detail) const
{
    auto summaryJson = JsonUtil::Create(true);
    auto detailJson = JsonUtil::Create(true);
    std::stringstream summaryNodesSearched;
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    AccessibilityHoverTestPath path = AccessibilityProperty::HoverTest(point, root, debugInfo);
    auto summaryPath = JsonUtil::CreateArray(false);
    auto summarySelected = JsonUtil::CreateArray(false);

    auto detaiSelectionInfo = JsonUtil::CreateArray(false);
    size_t numNodesSelected = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        summaryPath->Put(std::to_string(i).c_str(), path[i]->GetAccessibilityId());
        auto detailNodeSelection = JsonUtil::Create(false);
        if (AccessibilityProperty::IsAccessibilityFocusableDebug(path[i], detailNodeSelection)) {
            summarySelected->Put(std::to_string(numNodesSelected).c_str(), path[i]->GetAccessibilityId());
            ++numNodesSelected;
        }
        detaiSelectionInfo->Put(std::to_string(i).c_str(), detailNodeSelection);
    }
    summaryJson->Put("path", summaryPath);
    summaryJson->Put("nodesSelected", summarySelected);

    auto detailSearchInfo = JsonUtil::CreateArray(false);
    for (size_t i = 0; i < debugInfo->trace.size(); ++i) {
        auto detailNodeSearch = std::move(debugInfo->trace[i]);
        detailSearchInfo->Put(std::to_string(i).c_str(), detailNodeSearch);
    }
    detailJson->Put("detailSearch", detailSearchInfo);
    detailJson->Put("detailSelection", detaiSelectionInfo);
    std::stringstream detailFiltered;
    summary = summaryJson->ToString();
    detail = detailJson->ToString();
}
} // namespace OHOS::Ace::NG
