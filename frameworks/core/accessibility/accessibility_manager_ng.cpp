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
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

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
        eventType < 0 || eventType >= static_cast<int32_t>(AccessibilityHoverEventType::Count)) {
        return;
    }
    PointF point(pointX, pointY);
    TimeStamp time((std::chrono::milliseconds(timeMs)));

    if (IsHandlePipelineAccessibilityHoverEnter(root)) {
        TouchEvent event;
        event.x = pointX;
        event.y = pointY;
        event.sourceType = static_cast<SourceType>(sourceType);
        event.time = time;
        HandlePipelineAccessibilityHoverEnter(root, event, eventType);
    } else {
        HandleAccessibilityHoverEventInner(root, point, static_cast<SourceType>(sourceType),
            static_cast<AccessibilityHoverEventType>(eventType), time);
    }
}

void AccessibilityManagerNG::HandleAccessibilityHoverEventInner(
    const RefPtr<FrameNode>& root,
    const PointF& point,
    SourceType sourceType,
    AccessibilityHoverEventType eventType,
    TimeStamp time)
{
    static constexpr size_t THROTTLE_INTERVAL_HOVER_EVENT = 100;
    uint64_t duration =
        static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(time - hoverState_.time).count());
    if (!hoverState_.idle) {
        if ((!IsEventTypeChangeDirectHandleHover(eventType)) && (duration < THROTTLE_INTERVAL_HOVER_EVENT)) {
            return;
        }
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
    if (!DeliverAccessibilityHoverEvent(currentHovering, point)) {
        if (lastHoveringId != INVALID_NODE_ID && lastHoveringId != currentHoveringId) {
            lastHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_EXIT_EVENT);
            NotifyHoverEventToNodeSession(lastHovering, root, point,
                sourceType, AccessibilityHoverEventType::EXIT, time);
        }
        if (currentHoveringId != INVALID_NODE_ID) {
            if (currentHoveringId != lastHoveringId && (!IgnoreCurrentHoveringNode(currentHovering))) {
                currentHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_ENTER_EVENT);
            }
            NotifyHoverEventToNodeSession(currentHovering, root, point,
                sourceType, eventType, time);
        }
    }

    hoverState_.nodesHovering = std::move(currentNodesHovering);
    hoverState_.time = time;
    hoverState_.source = sourceType;
    hoverState_.idle = eventType == AccessibilityHoverEventType::EXIT;
    hoverState_.eventType = eventType;
}

bool AccessibilityManagerNG::DeliverAccessibilityHoverEvent(const RefPtr<FrameNode>& hoverNode, const PointF& point)
{
    CHECK_NULL_RETURN(hoverNode, false);
    auto hoverNodePattern = hoverNode->GetPattern();
    CHECK_NULL_RETURN(hoverNodePattern, false);
    return hoverNodePattern->OnAccessibilityHoverEvent(point);
}

bool AccessibilityManagerNG::IgnoreCurrentHoveringNode(const RefPtr<FrameNode> &node)
{
    auto sessionAdapter = AccessibilitySessionAdapter::GetSessionAdapter(node);
    CHECK_NULL_RETURN(sessionAdapter, false);
    return sessionAdapter->IgnoreHostNode();
}

void AccessibilityManagerNG::NotifyHoverEventToNodeSession(const RefPtr<FrameNode>& node,
    const RefPtr<FrameNode>& rootNode, const PointF& pointRoot,
    SourceType sourceType, AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto eventHub = node->GetEventHub<EventHub>();
    if (!eventHub->IsEnabled()) {
        // If the host component is disabled, do not transfer hover event.
        return;
    }
    auto sessionAdapter = AccessibilitySessionAdapter::GetSessionAdapter(node);
    CHECK_NULL_VOID(sessionAdapter);
    PointF pointNode(pointRoot);
    if (AccessibilityManagerNG::ConvertPointFromAncestorToNode(rootNode, node, pointRoot, pointNode)) {
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
    auto summaryJson = JsonUtil::Create();
    auto detailJson = JsonUtil::Create();
    std::stringstream summaryNodesSearched;
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    AccessibilityHoverTestPath path = AccessibilityProperty::HoverTest(point, root, debugInfo);
    auto summaryPath = JsonUtil::CreateArray();
    auto summarySelected = JsonUtil::CreateArray();

    auto detaiSelectionInfo = JsonUtil::CreateArray();
    size_t numNodesSelected = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        summaryPath->Put(std::to_string(i).c_str(), path[i]->GetAccessibilityId());
        auto detailNodeSelection = JsonUtil::Create();
        if (AccessibilityProperty::IsAccessibilityFocusableDebug(path[i], detailNodeSelection)) {
            summarySelected->Put(std::to_string(numNodesSelected).c_str(), path[i]->GetAccessibilityId());
            ++numNodesSelected;
        }
        detaiSelectionInfo->PutRef(std::move(detailNodeSelection));
    }
    summaryJson->PutRef("path", std::move(summaryPath));
    summaryJson->PutRef("nodesSelected", std::move(summarySelected));

    auto detailSearchInfo = JsonUtil::CreateArray();
    for (size_t i = 0; i < debugInfo->trace.size(); ++i) {
        auto detailNodeSearch = std::move(debugInfo->trace[i]);
        detailSearchInfo->Put(std::to_string(i).c_str(), detailNodeSearch);
    }
    detailJson->PutRef("detailSearch", std::move(detailSearchInfo));
    detailJson->PutRef("detailSelection", std::move(detaiSelectionInfo));
    summary = summaryJson->ToString();
    detail = detailJson->ToString();
}

bool AccessibilityManagerNG::ConvertPointFromAncestorToNode(
    const RefPtr<NG::FrameNode>& ancestor, const RefPtr<NG::FrameNode>& endNode,
    const PointF& pointAncestor, PointF& pointNode)
{
    CHECK_NULL_RETURN(ancestor, false);
    CHECK_NULL_RETURN(endNode, false);
    std::vector<RefPtr<NG::FrameNode>> path;
    RefPtr<NG::FrameNode> curr = endNode;
    while (curr != nullptr && curr->GetId() != ancestor->GetId()) {
        path.push_back(curr);
        curr = curr->GetAncestorNodeOfFrame();
    }
    CHECK_NULL_RETURN(curr, false);
    pointNode = pointAncestor;
    for (const auto& node : path) {
        auto renderContext = node->GetRenderContext();
        renderContext->GetPointWithRevert(pointNode);
        auto rect = renderContext->GetPaintRectWithoutTransform();
        pointNode = pointNode - rect.GetOffset();
    }
    return true;
}

bool AccessibilityManagerNG::IsEventTypeChangeDirectHandleHover(AccessibilityHoverEventType eventType)
{
    if ((hoverState_.eventType == AccessibilityHoverEventType::MOVE)
        && (eventType == AccessibilityHoverEventType::EXIT)) {
        return true;
    }
    return false;
}

bool AccessibilityManagerNG::IsHandlePipelineAccessibilityHoverEnter(const RefPtr<NG::FrameNode>& root)
{
    auto pipeline = root->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(ngPipeline, false);

    auto container = Container::GetContainer(ngPipeline->GetInstanceId());
    if (container && (container->IsUIExtensionWindow())) {
        return true;
    }
    return false;
}

void AccessibilityManagerNG::HandlePipelineAccessibilityHoverEnter(
    const RefPtr<NG::FrameNode>& root,
    TouchEvent& event,
    int32_t eventType)
{
    AccessibilityHoverEventType eventHoverType = static_cast<AccessibilityHoverEventType>(eventType);
    event.type = TouchType::HOVER_MOVE;
    switch (eventHoverType) {
        case AccessibilityHoverEventType::ENTER:
            event.type = TouchType::HOVER_ENTER;
            break;
        case AccessibilityHoverEventType::MOVE:
            event.type = TouchType::HOVER_MOVE;
            break;
        case AccessibilityHoverEventType::EXIT:
            event.type = TouchType::HOVER_EXIT;
            break;
        default:
            break;
    }

    auto pipeline = root->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->OnAccessibilityHoverEvent(event, root);
}
} // namespace OHOS::Ace::NG
