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
namespace {
void GetOffsetToAncestorRevertTransform(const RefPtr<NG::FrameNode>& ancestor, const RefPtr<NG::FrameNode>& endNode,
    const PointF& pointAncestor, PointF& pointNode)
{
    CHECK_NULL_VOID(ancestor);
    CHECK_NULL_VOID(endNode);
    auto context = endNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto rect = context->GetPaintRectWithoutTransform();
    OffsetF offset = rect.GetOffset();
    VectorF finalScale {1.0f, 1.0f};
    auto scale = endNode->GetTransformScale();
    finalScale.x = scale.x;
    finalScale.y = scale.y;
    
    PointF ancestorLeftTopPoint(offset.GetX(), offset.GetY());
    context->GetPointTransformRotate(ancestorLeftTopPoint);
    auto parent = endNode->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        if (parentRenderContext) {
            offset = parentRenderContext->GetPaintRectWithoutTransform().GetOffset();
            PointF pointTmp(offset.GetX() + ancestorLeftTopPoint.GetX(), offset.GetY() + ancestorLeftTopPoint.GetY());
            parentRenderContext->GetPointTransformRotate(pointTmp);
            ancestorLeftTopPoint.SetX(pointTmp.GetX());
            ancestorLeftTopPoint.SetY(pointTmp.GetY());
            auto scale = parent->GetTransformScale();
            finalScale.x *= scale.x;
            finalScale.y *= scale.y;
        }

        if (ancestor && (parent == ancestor)) {
            break;
        }

        parent = parent->GetAncestorNodeOfFrame(true);
    }

    if ((NearEqual(finalScale.x, 1.0f) && NearEqual(finalScale.y, 1.0f)) ||
        NearZero(finalScale.x) || NearZero(finalScale.y)) {
        pointNode.SetX(pointAncestor.GetX() - ancestorLeftTopPoint.GetX());
        pointNode.SetY(pointAncestor.GetY() - ancestorLeftTopPoint.GetY());
    } else {
        pointNode.SetX((pointAncestor.GetX() - ancestorLeftTopPoint.GetX()) / finalScale.x);
        pointNode.SetY((pointAncestor.GetY() - ancestorLeftTopPoint.GetY()) / finalScale.y);
    }
    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
        "GetOffsetToAncestorRevertTransform: offsetX %{public}f offsetY %{public}f scaleX %{public}f scaleY %{public}f",
        pointNode.GetX(), pointNode.GetY(), finalScale.x, finalScale.y);
}

void AddTouchEventAllFingersInfo(const RefPtr<NG::FrameNode>& node, TouchEventInfo& eventInfo, const TouchEvent& event)
{
    // all fingers collection
    for (const auto& item : event.pointers) {
        float globalX = item.x;
        float globalY = item.y;
        float screenX = item.screenX;
        float screenY = item.screenY;
        double globalDisplayX = item.globalDisplayX;
        double globalDisplayY = item.globalDisplayY;
        PointF localPoint(globalX, globalY);
        NGGestureRecognizer::Transform(localPoint, node, false, false);
        auto localX = static_cast<float>(localPoint.GetX());
        auto localY = static_cast<float>(localPoint.GetY());
        TouchLocationInfo info("onTouch", item.originalId);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetGlobalDisplayLocation(Offset(globalDisplayX, globalDisplayY));
        info.SetTouchType(event.type);
        info.SetForce(item.force);
        info.SetPressedTime(item.downTime);
        info.SetWidth(item.width);
        info.SetHeight(item.height);
        if (item.tiltX.has_value()) {
            info.SetTiltX(item.tiltX.value());
        }
        if (item.tiltY.has_value()) {
            info.SetTiltY(item.tiltY.value());
        }
        info.SetSourceTool(item.sourceTool);
        eventInfo.AddTouchLocationInfo(std::move(info));
    }
}

void ConvertTouchEvent2TouchEventInfo(const RefPtr<NG::FrameNode>& node, const TouchEvent& event,
    TouchEventInfo& eventInfo)
{
    eventInfo.SetTimeStamp(event.time);
    eventInfo.SetDeviceId(event.deviceId);
    eventInfo.SetPointerEvent(event.GetTouchEventPointerEvent());
    TouchLocationInfo changedInfo("onTouch", event.originalId);
    PointF lastLocalPoint(event.x, event.y);
    NGGestureRecognizer::Transform(lastLocalPoint, node, false, false);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    changedInfo.SetLocalLocation(Offset(localX, localY));
    changedInfo.SetGlobalLocation(Offset(event.x, event.y));
    changedInfo.SetScreenLocation(Offset(event.screenX, event.screenY));
    changedInfo.SetGlobalDisplayLocation(Offset(event.globalDisplayX, event.globalDisplayY));
    changedInfo.SetTouchType(event.type);
    changedInfo.SetForce(event.force);
    changedInfo.SetPressedTime(event.pressedTime);
    changedInfo.SetWidth(event.width);
    changedInfo.SetHeight(event.height);
    if (event.tiltX.has_value()) {
        changedInfo.SetTiltX(event.tiltX.value());
    }
    if (event.tiltY.has_value()) {
        changedInfo.SetTiltY(event.tiltY.value());
    }
    changedInfo.SetSourceTool(event.sourceTool);
    eventInfo.AddChangedTouchLocationInfo(std::move(changedInfo));

    AddTouchEventAllFingersInfo(node, eventInfo, event);
    eventInfo.SetSourceDevice(event.sourceType);
    eventInfo.SetForce(event.force);
    if (event.tiltX.has_value()) {
        eventInfo.SetTiltX(event.tiltX.value());
    }
    if (event.tiltY.has_value()) {
        eventInfo.SetTiltY(event.tiltY.value());
    }
    if (event.rollAngle.has_value()) {
        eventInfo.SetRollAngle(event.rollAngle.value());
    }
    eventInfo.SetSourceTool(event.sourceTool);
    EventTarget eventTarget;
    eventTarget.id = node->GetInspectorId().value_or("").c_str();
    eventInfo.SetTarget(eventTarget);
}

bool CheckAndSendHoverEnterByAncestor(const RefPtr<NG::FrameNode>& ancestor)
{
    CHECK_NULL_RETURN(ancestor, false);
    auto pipeline = ancestor->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    // Inter Process is showed as a component with rect like form process,
    // need send hover enter when no component hovered to focus outside
    if (pipeline->IsFormRender() || pipeline->IsJsCard() || pipeline->IsJsPlugin()) {
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "SendHoverEnterByAncestor");
        ancestor->OnAccessibilityEvent(AccessibilityEventType::HOVER_ENTER_EVENT);
        return true;
    }
    return false;
}

bool IsTouchExplorationEnabled(const RefPtr<FrameNode>& root)
{
    CHECK_NULL_RETURN(root, true);
    auto pipeline = root->GetContext();
    CHECK_NULL_RETURN(pipeline, true);
    auto jsAccessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(jsAccessibilityManager, true);
    auto accessibilityWorkMode = jsAccessibilityManager->GenerateAccessibilityWorkMode();
    return accessibilityWorkMode.isTouchExplorationEnabled;
}

WeakPtr<NG::FrameNode> GetEmbedNodeBySurfaceId(const std::string& surfaceId)
{
    std::stringstream ss(surfaceId);
    uint64_t id;
    if (ss >> id) {
        return ElementRegister::GetInstance()->GetEmbedNodeBySurfaceId(id);
    }
    return nullptr;
}
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event)
{
    if (root == nullptr || !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        !IsTouchExplorationEnabled(root) || event.sourceType != SourceType::MOUSE) {
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
    HandleHoverEventParam param {point, SourceType::MOUSE, type, event.time};
    TouchEvent touchEvent;
    HandleAccessibilityHoverEventInner(root, param, touchEvent);
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event)
{
    if (root == nullptr ||
        !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        !IsTouchExplorationEnabled(root) ||
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
    auto& hoverState = hoverStateManager_.GetHoverState(root->GetAccessibilityId());
    if (event.pointers.size() > 1 && event.sourceType == SourceType::TOUCH) {
        if (hoverState.source == SourceType::TOUCH) {
            hoverStateManager_.ResetHoverState(hoverState);
            return;
        }
    }
    HandleHoverEventParam param {point, event.sourceType, type, event.time};
    HandleAccessibilityHoverEventInner(root, param, event);
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, float pointX, float pointY,
    int32_t sourceType, int32_t eventType, int64_t timeMs)
{
    if (root == nullptr ||
        !AceApplicationInfo::GetInstance().IsAccessibilityEnabled() ||
        !IsTouchExplorationEnabled(root) ||
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
    }
    HandleHoverEventParam param {point, static_cast<SourceType>(sourceType),
        static_cast<AccessibilityHoverEventType>(eventType), time};
    TouchEvent touchEvent;
    HandleAccessibilityHoverEventInner(root, param, touchEvent);
}

bool HasTransparentCallback(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    return accessibilityManager->IsInHoverTransparentCallbackList(node);
}

bool AccessibilityManagerNG::ExecuteChildNodeHoverTransparentCallback(const RefPtr<FrameNode>& root,
    const PointF& point, const TouchEvent& event)
{
    CHECK_NULL_RETURN(root, false);
    auto renderContext = root->GetRenderContext();
    auto accessibilityProperty = root->GetAccessibilityProperty<NG::AccessibilityProperty>();
    PointF selfPoint = point;
    if (accessibilityProperty) {
        bool isInHoverArea = false;
        if (renderContext) {
            auto rect = AccessibilityProperty::UpdateHoverTestRect(root);
            renderContext->GetPointWithRevert(selfPoint);
            isInHoverArea = rect.IsInnerRegion(selfPoint);
        }
        auto callback = accessibilityProperty->GetAccessibilityTransparentCallbackFunc();
        if (callback && isInHoverArea) {
            TouchEventInfo eventInfo("touchEvent");
            ConvertTouchEvent2TouchEventInfo(root, event, eventInfo);
            callback(eventInfo);
        }
    }
    auto children = root->GetFrameChildren();
    for (auto childWeak = children.rbegin(); childWeak != children.rend(); ++childWeak) {
        auto child = childWeak->Upgrade();
        if (child == nullptr) {
            continue;
        }
        PointF noOffsetPoint = selfPoint;
        if (renderContext) {
            auto orginRect = renderContext->GetPaintRectWithoutTransform();
            noOffsetPoint = selfPoint - orginRect.GetOffset();
        }
        ExecuteChildNodeHoverTransparentCallback(child, noOffsetPoint, event);
    }
    return true;
}

bool AccessibilityManagerNG::HandleAccessibilityHoverTransparentCallback(bool transformed,
    const RefPtr<FrameNode>& root,
    const HandleTransparentCallbackParam& param,
    const PointF& point,
    const TouchEvent& event)
{
    static constexpr int32_t INVALID_NODE_ID = -1;
    if (transformed) {
        return false;
    }
    if ((param.currentHoveringId == INVALID_NODE_ID) && (param.lastHoveringId == INVALID_NODE_ID)) {
        return ExecuteChildNodeHoverTransparentCallback(root, point, event);
    }
    return false;
}

HandleHoverRet AccessibilityManagerNG::HandleAccessibilityHoverEventInner(
    const RefPtr<FrameNode>& root,
    const HandleHoverEventParam& param,
    const TouchEvent& event)
{
    CHECK_NULL_RETURN(root, HandleHoverRet::HOVER_FAIL);
    auto& hoverState = hoverStateManager_.GetHoverState(root->GetAccessibilityId());
    auto sourceType = param.sourceType;
    auto eventType = param.eventType;
    auto time = param.time;
    static constexpr size_t THROTTLE_INTERVAL_HOVER_EVENT = 10;
    uint64_t duration =
        static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(time - hoverState.time).count());
    if (!hoverState.idle) {
        if ((!IsEventTypeChangeDirectHandleHover(eventType, hoverState.eventType))
            && (duration < THROTTLE_INTERVAL_HOVER_EVENT)) {
            return HandleHoverRet::IN_TIME_LIMIT;
        }
    }

    static constexpr size_t MIN_SOURCE_CHANGE_GAP_MS = 1000;
    if (sourceType != hoverState.source && !hoverState.idle) {
        if (duration < MIN_SOURCE_CHANGE_GAP_MS) {
            return HandleHoverRet::IN_TIME_LIMIT;
        }
        hoverStateManager_.ResetHoverState(hoverState);
    }

    ACE_SCOPED_TRACE("HandleAccessibilityHoverEventInner");
    if (eventType == AccessibilityHoverEventType::ENTER) {
        hoverStateManager_.ResetHoverState(hoverState);
    }
    std::vector<WeakPtr<FrameNode>> currentNodesHovering;
    std::vector<RefPtr<FrameNode>> lastNodesHovering;
    std::vector<int32_t> lastNodesHoveringId;
    for (const auto& nodeWeak: hoverState.nodesHovering) {
        auto node = nodeWeak.Upgrade();
        if (node != nullptr) {
            lastNodesHovering.push_back(node);
            lastNodesHoveringId.push_back(node->GetId());
        }
    }
    if (eventType != AccessibilityHoverEventType::EXIT) {
        std::unique_ptr<AccessibilityProperty::HoverTestDebugTraceInfo> debugInfo = nullptr;
        AccessibilityHoverTestPath path = AccessibilityProperty::HoverTest(param.point, root, debugInfo);
        for (const auto& node: path) {
            auto id = node->GetId();
            if (std::find(lastNodesHoveringId.begin(), lastNodesHoveringId.end(), id) != lastNodesHoveringId.end() ||
                AccessibilityProperty::IsAccessibilityFocusable(node)) {
                currentNodesHovering.push_back(node);
            }
        }
    }
    auto sendHoverEnter = false;
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
    bool transformHover = false;
    if (lastHoveringId != INVALID_NODE_ID && lastHoveringId != currentHoveringId) {
        lastHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_EXIT_EVENT);
        transformHover = NotifyHoverEventToNodeSession(lastHovering, root, param.point,
            sourceType, AccessibilityHoverEventType::EXIT, time);
    }
    if (currentHovering && (currentHoveringId != INVALID_NODE_ID)) {
        if (currentHoveringId != lastHoveringId && (!IgnoreCurrentHoveringNode(currentHovering))) {
            currentHovering->OnAccessibilityEvent(AccessibilityEventType::HOVER_ENTER_EVENT);
            sendHoverEnter = true;
        }
        transformHover = NotifyHoverEventToNodeSession(currentHovering, root, param.point,
            sourceType, eventType, time);
    }

    if (!sendHoverEnter && (eventType == AccessibilityHoverEventType::ENTER)) {
        // check need send hover enter when no component hovered to focus outside
        transformHover |= CheckAndSendHoverEnterByAncestor(root);
    }

    if ((sourceType != SourceType::MOUSE) && (!param.ignoreTransparent)) {
        HandleTransparentCallbackParam callbackParam = {currentHoveringId, lastHoveringId};
        HandleAccessibilityHoverTransparentCallback(transformHover, root, callbackParam, param.point, event);
    }

    hoverState.nodesHovering = std::move(currentNodesHovering);
    hoverState.time = time;
    hoverState.source = sourceType;
    hoverState.idle = eventType == AccessibilityHoverEventType::EXIT;
    hoverState.eventType = eventType;
    if (sendHoverEnter && !transformHover) {
        return HandleHoverRet::HOVER_HIT;
    }
    return HandleHoverRet::HOVER_FAIL;
}

HandleHoverRet AccessibilityManagerNG::HandleAccessibilityHoverEventBySurfaceId(
    const std::string& surfaceId,
    HandleHoverEventParam& param)
{
    auto root = GetEmbedNodeBySurfaceId(surfaceId).Upgrade();
    CHECK_NULL_RETURN(root, HandleHoverRet::HOVER_FAIL);
    TouchEvent event;
    param.ignoreTransparent = true;
    return HandleAccessibilityHoverEventInner(root, param, event);
}

bool AccessibilityManagerNG::IgnoreCurrentHoveringNode(const RefPtr<FrameNode> &node)
{
    auto sessionAdapter = AccessibilitySessionAdapter::GetSessionAdapter(node);
    CHECK_NULL_RETURN(sessionAdapter, false);
    return sessionAdapter->IgnoreHostNode();
}

bool AccessibilityManagerNG::NotifyHoverEventToNodeSession(const RefPtr<FrameNode>& node,
    const RefPtr<FrameNode>& rootNode, const PointF& pointRoot,
    SourceType sourceType, AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto eventHub = node->GetOrCreateEventHub<EventHub>();
    if (!eventHub->IsEnabled()) {
        // If the host component is disabled, do not transfer hover event.
        return false;
    }
    auto sessionAdapter = AccessibilitySessionAdapter::GetSessionAdapter(node);
    CHECK_NULL_RETURN(sessionAdapter, false);
    // mouse event will not be hover and may be transformed by component self through touch event transform
    if ((sourceType == SourceType::MOUSE) && (sessionAdapter->IgnoreTransformMouseEvent())) {
        return false;
    }
    PointF pointNode(pointRoot);
    if (AccessibilityManagerNG::ConvertPointFromAncestorToNode(rootNode, node, pointRoot, pointNode)) {
        sessionAdapter->TransferHoverEvent(pointNode, sourceType, eventType, time);
        return true;
    }
    return false;
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
    // revert scale from endNode to ancestor
    GetOffsetToAncestorRevertTransform(ancestor, endNode, pointAncestor, pointNode);
    return true;
}

bool AccessibilityManagerNG::IsEventTypeChangeDirectHandleHover(
    AccessibilityHoverEventType eventType,
    AccessibilityHoverEventType prevEventType)
{
    if ((prevEventType == AccessibilityHoverEventType::MOVE)
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
    CHECK_NULL_VOID(root);
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

AccessibilityHoverState& AccessibilityHoverStateManager::GetHoverState(int64_t accessibilityId)
{
    auto it = hoverStateMap_.find(accessibilityId);
    if (it != hoverStateMap_.end()) {
        return it->second;
    }
    hoverStateMap_.emplace(accessibilityId, AccessibilityHoverState {});
    return hoverStateMap_[accessibilityId];
}

void AccessibilityHoverStateManager::ResetHoverState(AccessibilityHoverState& hoverState)
{
    hoverState.idle = true;
    hoverState.nodesHovering.clear();
}
} // namespace OHOS::Ace::NG
