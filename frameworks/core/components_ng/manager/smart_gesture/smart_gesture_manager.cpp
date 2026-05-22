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

#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"

#include <algorithm>
#include <cmath>
#include <list>
#include <set>
#include <unordered_set>

#ifndef CROSS_PLATFORM
#include "interfaces/inner_api/ace/ui_content.h"
#endif
#include "ui/base/utils/utils.h"

#include "base/log/log_wrapper.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/event_manager.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_decider.h"
#include "core/components_ng/property/smart_gesture_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ACE_FORCE_EXPORT
SmartGestureProposal::SmartGestureProposal(
    SmartGestureProposalType proposalType, SmartGestureOperateIntention intention, const RefPtr<FrameNode>& node)
    : type(proposalType), operateIntention(intention), targetNode(node)
{}

ACE_FORCE_EXPORT
SmartGestureProposal::SmartGestureProposal(SmartGestureProposalType proposalType,
    SmartGestureOperateIntention intention, const RefPtr<FrameNode>& node, const ScrollingConfig& config)
    : type(proposalType), operateIntention(intention), targetNode(node), scrollingConfig(config)
{}

ACE_FORCE_EXPORT
RefPtr<FrameNode> SmartGestureProposal::GetTargetNode() const
{
    return targetNode.Upgrade();
}

namespace {
constexpr double HALF_DIVISOR = 2.0;
constexpr int32_t CENTER_HIT_TEST_TOUCH_ID = 0;

SmartGestureProposal BuildNoneActionProposal(SmartGestureTrigger trigger)
{
    switch (trigger) {
        case SmartGestureTrigger::SLIDE_FORWARD:
            return SmartGestureProposal(
                SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::SLIDE_FORWARD);
        case SmartGestureTrigger::WRIST_BACK:
            return SmartGestureProposal(
                SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::BACK_PRESS);
        case SmartGestureTrigger::TAP:
            break;
    }
    return SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);
}

struct VisiblePrimaryActionSnapshot {
    RefPtr<FrameNode> node;
    RectF visibleRect;
    uint64_t order = 0;
};

bool IsVisibleRectUsable(const RectF& rect)
{
    return rect.IsValid() && !rect.IsEmpty();
}

bool IsNodeClickable(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureHub = eventHub->GetGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    return static_cast<bool>(gestureHub->GetCommonClickEvent());
}

bool DispatchSmartGestureClick(const RefPtr<FrameNode>& node, const KeyEvent& event)
{
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureHub = eventHub->GetGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    auto click = gestureHub->GetCommonClickEvent();
    CHECK_NULL_RETURN(click, false);

    GestureEvent info;
    auto context = node->GetContextRefPtr();
    info.SetTimeStamp(event.timeStamp);

    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto rect = geometryNode->GetFrameRect();
    auto centerToWindow = Offset((rect.Left() + rect.Right()) / 2, (rect.Top() + rect.Bottom()) / 2);
    auto centerToNode = Offset((rect.Right() - rect.Left()) / 2, (rect.Bottom() - rect.Top()) / 2);
    info.SetGlobalLocation(centerToWindow);
    info.SetLocalLocation(centerToNode);
    info.SetSourceDevice(event.sourceType);
    info.SetDeviceId(event.deviceId);
    info.SetInputEventType(InputEventType::KEYBOARD);
    info.SetPatternName(node->GetTag().c_str());

    if (context) {
        auto windowOffset = context->GetCurrentWindowRect().GetOffset() + centerToWindow;
        auto globalWindowOffset = context->GetGlobalDisplayWindowRect().GetOffset() + centerToWindow;
        info.SetScreenLocation(windowOffset);
        info.SetGlobalDisplayLocation(globalWindowOffset);
    }
    info.SetSourceTool(SourceTool::UNKNOWN);
    auto targetImpl = eventHub->CreateGetEventTargetImpl();
    if (targetImpl) {
        info.SetTarget(targetImpl().value_or(EventTarget()));
    }
    info.SetTargetDisplayId(event.targetDisplayId);

    click(info);
    return true;
}

bool IsScrollableRevealAnchorNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    const auto& tag = node->GetTag();
    return tag == V2::LIST_ITEM_ETS_TAG || tag == V2::LIST_ITEM_GROUP_ETS_TAG || tag == V2::ARC_LIST_ITEM_ETS_TAG;
}

RefPtr<FrameNode> ResolveScrollableRevealAnchor(const RefPtr<FrameNode>& node)
{
    auto current = node;
    while (current) {
        if (IsScrollableRevealAnchorNode(current)) {
            return current;
        }
        current = current->GetParentFrameNode();
    }
    return node;
}

RectF GetNodeVisibleRect(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, RectF());
    RectF visibleRect;
    RectF visibleInnerRect;
    RectF frameRect;
    node->GetVisibleRectWithClip(visibleRect, visibleInnerRect, frameRect, false);
    return visibleRect;
}

double GetCenterX(const RectF& rect)
{
    return rect.Left() + rect.Width() / HALF_DIVISOR;
}

double GetCenterY(const RectF& rect)
{
    return rect.Top() + rect.Height() / HALF_DIVISOR;
}

void CollectPanGestureNodes(std::vector<RefPtr<FrameNode>>& centerHitPath, std::unordered_set<int32_t>& visitedNodeIds,
    const RefPtr<NGGestureRecognizer>& gestureRecognizer)
{
    CHECK_NULL_VOID(gestureRecognizer);
    if (gestureRecognizer->GetRecognizerType() == GestureTypeName::PAN_GESTURE) {
        auto currentNode = gestureRecognizer->GetAttachedNode().Upgrade();
        if (currentNode && visitedNodeIds.insert(currentNode->GetId()).second) {
            centerHitPath.emplace_back(currentNode);
        }
    }

    auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(gestureRecognizer);
    if (!recognizerGroup) {
        return;
    }

    for (const auto& childRecognizer : recognizerGroup->GetGroupRecognizer()) {
        auto childGestureRecognizer = AceType::DynamicCast<NGGestureRecognizer>(childRecognizer);
        CollectPanGestureNodes(centerHitPath, visitedNodeIds, childGestureRecognizer);
    }
}

void CollectTouchedFrameNodes(
    std::set<WeakPtr<FrameNode>>& frameNodes, const std::list<RefPtr<NGGestureRecognizer>>& touchTestResults)
{
    for (const auto& item : touchTestResults) {
        CHECK_NULL_CONTINUE(item);
        auto node = item->GetAttachedNode().Upgrade();
        if (node) {
            frameNodes.emplace(node);
        }
        auto group = AceType::DynamicCast<RecognizerGroup>(item);
        if (group) {
            CollectTouchedFrameNodes(frameNodes, group->GetGroupRecognizer());
        }
    }
}

void CleanTouchedFrameNodes(std::set<WeakPtr<FrameNode>>& frameNodes)
{
    for (const auto& item : frameNodes) {
        auto frameNode = item.Upgrade();
        CHECK_NULL_CONTINUE(frameNode);
        auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
        if (gestureEventHub) {
            gestureEventHub->CleanExternalRecognizers();
            gestureEventHub->CleanInnerRecognizer();
            gestureEventHub->CleanNodeRecognizer();
        }
    }
}

void CleanTemporaryGestureArena(const RefPtr<PipelineContext>& context, const TouchTestResult& touchTestResult)
{
    CHECK_NULL_VOID(context);
    auto eventManager = context->GetEventManager();
    CHECK_NULL_VOID(eventManager);

    std::list<RefPtr<NGGestureRecognizer>> hitTestRecognizers;
    for (const auto& item : touchTestResult) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(item);
        if (recognizer) {
            hitTestRecognizers.emplace_back(recognizer);
        }
    }

    std::set<WeakPtr<FrameNode>> touchedFrameNodes;
    CollectTouchedFrameNodes(touchedFrameNodes, hitTestRecognizers);

    auto referee = eventManager->GetGestureRefereeNG(nullptr);
    CHECK_NULL_VOID(referee);
    referee->CleanGestureStateVoluntarily(CENTER_HIT_TEST_TOUCH_ID);
    referee->CleanGestureScope(CENTER_HIT_TEST_TOUCH_ID);
    CleanTouchedFrameNodes(touchedFrameNodes);
}

void SortPrimaryActionLayer(std::vector<VisiblePrimaryActionSnapshot>& snapshots, size_t layerBegin, size_t layerEnd)
{
    auto baseIter = std::min_element(snapshots.begin() + static_cast<long>(layerBegin),
        snapshots.begin() + static_cast<long>(layerEnd), [](const auto& left, const auto& right) {
            if (!NearEqual(left.visibleRect.Left(), right.visibleRect.Left())) {
                return left.visibleRect.Left() < right.visibleRect.Left();
            }
            if (!NearEqual(left.visibleRect.Top(), right.visibleRect.Top())) {
                return left.visibleRect.Top() < right.visibleRect.Top();
            }
            return left.order < right.order;
        });
    double baseCenterX = GetCenterX(baseIter->visibleRect);
    double baseCenterY = GetCenterY(baseIter->visibleRect);
    std::stable_sort(snapshots.begin() + static_cast<long>(layerBegin), snapshots.begin() + static_cast<long>(layerEnd),
        [baseCenterX, baseCenterY](const auto& left, const auto& right) {
            double leftDx = GetCenterX(left.visibleRect) - baseCenterX;
            double leftDy = GetCenterY(left.visibleRect) - baseCenterY;
            double rightDx = GetCenterX(right.visibleRect) - baseCenterX;
            double rightDy = GetCenterY(right.visibleRect) - baseCenterY;
            double leftDistanceSquare = leftDx * leftDx + leftDy * leftDy;
            double rightDistanceSquare = rightDx * rightDx + rightDy * rightDy;
            if (!NearEqual(leftDistanceSquare, rightDistanceSquare)) {
                return leftDistanceSquare < rightDistanceSquare;
            }
            double leftAbsDx = std::abs(leftDx);
            double rightAbsDx = std::abs(rightDx);
            if (!NearEqual(leftAbsDx, rightAbsDx)) {
                return leftAbsDx < rightAbsDx;
            }
            double leftAbsDy = std::abs(leftDy);
            double rightAbsDy = std::abs(rightDy);
            if (!NearEqual(leftAbsDy, rightAbsDy)) {
                return leftAbsDy < rightAbsDy;
            }
            if (!NearEqual(left.visibleRect.Left(), right.visibleRect.Left())) {
                return left.visibleRect.Left() < right.visibleRect.Left();
            }
            if (!NearEqual(left.visibleRect.Top(), right.visibleRect.Top())) {
                return left.visibleRect.Top() < right.visibleRect.Top();
            }
            return left.order < right.order;
        });
}

void SortVisiblePrimaryActionSnapshots(std::vector<VisiblePrimaryActionSnapshot>& snapshots)
{
    // Rule 1: sort all visible primary-action nodes by top edge from top to bottom first.
    std::stable_sort(snapshots.begin(), snapshots.end(), [](const auto& left, const auto& right) {
        if (!NearEqual(left.visibleRect.Top(), right.visibleRect.Top())) {
            return left.visibleRect.Top() < right.visibleRect.Top();
        }
        if (!NearEqual(left.visibleRect.Left(), right.visibleRect.Left())) {
            return left.visibleRect.Left() < right.visibleRect.Left();
        }
        return left.order < right.order;
    });

    std::vector<VisiblePrimaryActionSnapshot> sortedSnapshots;
    sortedSnapshots.reserve(snapshots.size());
    size_t layerBegin = 0;
    while (layerBegin < snapshots.size()) {
        // Rules 2-4: build layers from top to bottom. Layer membership is determined against the
        // current layer start node, instead of using transitive overlap expansion.
        size_t layerEnd = layerBegin + 1;
        float layerBottom = snapshots[layerBegin].visibleRect.Bottom();
        while (layerEnd < snapshots.size() && LessOrEqual(snapshots[layerEnd].visibleRect.Top(), layerBottom)) {
            ++layerEnd;
        }

        // Rules 5-6: within the same layer, sort by center distance to the base node, then
        // break ties by horizontal distance, vertical distance, left edge, top edge, and finally
        // the original node registration order.
        SortPrimaryActionLayer(snapshots, layerBegin, layerEnd);

        sortedSnapshots.insert(sortedSnapshots.end(), snapshots.begin() + static_cast<long>(layerBegin),
            snapshots.begin() + static_cast<long>(layerEnd));
        layerBegin = layerEnd;
    }
    snapshots.swap(sortedSnapshots);
}
} // namespace

SmartGestureManager::SmartGestureManager(const WeakPtr<PipelineContext>& context) : context_(context)
{
    RefreshProductGestureEnabled();
}

void SmartGestureManager::RefreshProductGestureEnabled()
{
    productGestureEnabled_ = SystemProperties::GetSmartGestureEnabled();
}

void SmartGestureManager::SetMonitor(SmartGestureMonitor&& callback)
{
    monitorCallback_ = std::move(callback);
}

bool SmartGestureManager::HandleTrigger(SmartGestureTrigger trigger)
{
    KeyEvent event;
    return HandleTrigger(trigger, event);
}

bool SmartGestureManager::HandleTrigger(SmartGestureTrigger trigger, const KeyEvent& event)
{
    RefreshSelectedNodeState();
    CHECK_EQUAL_RETURN(productGestureEnabled_, false, false);
    if (trigger != SmartGestureTrigger::WRIST_BACK && !smartTapAndSlideGesturesEnabled_) {
        return false;
    }

    auto visiblePrimaryNodes = BuildVisiblePrimaryActionNodes();
    auto selectedNode = selectedNode_.Upgrade();
    std::vector<RefPtr<FrameNode>> centerHitPath;
    if (trigger == SmartGestureTrigger::SLIDE_FORWARD) {
        centerHitPath = BuildCenterHitPath();
    }
    std::optional<SmartGestureProposal> defaultProposal;
    if (trigger == SmartGestureTrigger::SLIDE_FORWARD) {
        defaultProposal = BuildSlideForwardProposal(visiblePrimaryNodes, selectedNode, centerHitPath);
    } else {
        defaultProposal =
            SmartGestureDecider::BuildDefaultProposal(trigger, visiblePrimaryNodes, selectedNode, centerHitPath);
    }

    if (!defaultProposal.has_value() && !GetMonitorHandle()) {
        return false;
    }

    // Return value semantics: true only when smart gesture processing ends up executing
    // a concrete action successfully; false means the gesture should be treated as unhandled,
    // including monitor veto, invalid proposal, or a final NONE_ACTION proposal.
    auto fallbackProposal = defaultProposal.value_or(BuildNoneActionProposal(trigger));
    auto proposal = ResolveProposal(fallbackProposal);
    bool executeResult = false;
    if (proposal.has_value()) {
        executeResult = ExecuteProposal(proposal.value(), event);
    }
    RecordExecutionSnapshot(trigger, static_cast<bool>(GetMonitorHandle()), fallbackProposal, proposal, executeResult);
    return executeResult;
}

void SmartGestureManager::RequestSelected(const std::string& inspectorId)
{
    RefreshSelectedNodeState();
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto frameNode =
        ElementRegister::GetInstance()->GetAttachedFrameNodeById(inspectorId, false, context->GetInstanceId());
    CHECK_NULL_VOID(IsPrimaryActionNodeActive(frameNode));
    CHECK_NULL_VOID(IsNodeClickable(frameNode));
    UpdateSelectedNode(frameNode);
}

void SmartGestureManager::ClearSelected()
{
    UpdateSelectedNode(nullptr);
}

void SmartGestureManager::UpdateSelectedNodePaintIfNeeded(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto selectedNode = selectedNode_.Upgrade();
    CHECK_NULL_VOID(selectedNode);
    if (selectedNode->GetId() != node->GetId()) {
        return;
    }
    selectedNode_ = node;
    SyncSelectedNodePaint(node);
}

std::vector<RefPtr<FrameNode>> SmartGestureManager::BuildVisiblePrimaryActionNodes()
{
    CHECK_NULL_RETURN(GetPipelineContext(), {});

    std::vector<VisiblePrimaryActionSnapshot> snapshots;
    snapshots.reserve(primaryActionRegistry_.size());
    for (auto iter = primaryActionRegistry_.begin(); iter != primaryActionRegistry_.end();) {
        auto frameNode = iter->second.node.Upgrade();
        if (!frameNode) {
            iter = primaryActionRegistry_.erase(iter);
            continue;
        }
        if (!IsPrimaryActionNodeActive(frameNode)) {
            ++iter;
            continue;
        }
        auto visibleRect = GetNodeVisibleRect(frameNode);
        if (!IsVisibleRectUsable(visibleRect)) {
            ++iter;
            continue;
        }
        VisiblePrimaryActionSnapshot snapshot;
        snapshot.node = frameNode;
        snapshot.visibleRect = visibleRect;
        snapshot.order = iter->second.order;
        snapshots.emplace_back(std::move(snapshot));
        ++iter;
    }

    SortVisiblePrimaryActionSnapshots(snapshots);
    std::vector<RefPtr<FrameNode>> visibleNodes;
    visibleNodes.reserve(snapshots.size());
    for (const auto& snapshot : snapshots) {
        visibleNodes.emplace_back(snapshot.node);
    }
    return visibleNodes;
}

void SmartGestureManager::SyncPrimaryActionNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto smartGestureProperty = node->GetSmartGestureProperty();
    if (smartGestureProperty && smartGestureProperty->IsPrimaryActionEnabled()) {
        AddPrimaryActionNode(node);
        return;
    }
    RemovePrimaryActionNode(node->GetId());
}

void SmartGestureManager::AddPrimaryActionNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto it = primaryActionRegistry_.find(node->GetId());
    uint64_t order = (it != primaryActionRegistry_.end()) ? it->second.order : nextPrimaryActionOrder_++;
    primaryActionRegistry_.insert_or_assign(node->GetId(), PrimaryActionEntry{node, order});
    auto selectedNode = selectedNode_.Upgrade();
    if (selectedNode && selectedNode->GetId() == node->GetId()) {
        SyncSelectedNodePaint(node);
    }
}

void SmartGestureManager::RemovePrimaryActionNode(int32_t nodeId)
{
    auto selectedNode = selectedNode_.Upgrade();
    if (selectedNode && selectedNode->GetId() == nodeId) {
        ClearSelected();
    }
    primaryActionRegistry_.erase(nodeId);
}

RefPtr<PipelineContext> SmartGestureManager::GetPipelineContext() const
{
    return context_.Upgrade();
}

SmartGestureManager::SmartGestureMonitor SmartGestureManager::GetMonitorHandle() const
{
    return monitorCallback_;
}

void SmartGestureManager::UpdateSelectedNode(const RefPtr<FrameNode>& node)
{
    auto currentSelectedNode = selectedNode_.Upgrade();
    if (currentSelectedNode && node && currentSelectedNode->GetId() == node->GetId()) {
        selectedNode_ = node;
        SyncSelectedNodePaint(node);
        return;
    }
    if (currentSelectedNode) {
        ClearSelectedNodePaint(currentSelectedNode);
    }
    if (!node) {
        selectedNode_.Reset();
        return;
    }
    selectedNode_ = node;
    SyncSelectedNodePaint(node);
    RevealSelectedNodeIfNeeded(node);
}

std::vector<RefPtr<FrameNode>> SmartGestureManager::BuildCenterHitPath() const
{
    auto context = GetPipelineContext();
    CHECK_NULL_RETURN(context, {});
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, {});
    auto rootRect = context->GetRootRect();
    CHECK_NULL_RETURN(rootRect.IsValid() && !rootRect.IsEmpty(), {});

    const float centerX = rootRect.Left() + rootRect.Width() / 2.0f;
    const float centerY = rootRect.Top() + rootRect.Height() / 2.0f;
    PointF centerPoint(centerX, centerY);

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::TOUCH;
    touchRestrict.sourceTool = SourceTool::FINGER;
    touchRestrict.hitTestType = SourceType::TOUCH;
    touchRestrict.inputEventType = InputEventType::TOUCH_SCREEN;
    touchRestrict.touchEvent.SetId(CENTER_HIT_TEST_TOUCH_ID)
        .SetOriginalId(CENTER_HIT_TEST_TOUCH_ID)
        .SetX(centerX)
        .SetY(centerY)
        .SetScreenX(centerX)
        .SetScreenY(centerY)
        .SetType(TouchType::DOWN)
        .SetSourceType(SourceType::TOUCH)
        .SetSourceTool(SourceTool::FINGER);

    TouchTestResult hitTestResult;
    ResponseLinkResult responseLinkResult;
    rootNode->TouchTest(centerPoint, centerPoint, centerPoint, touchRestrict, hitTestResult, CENTER_HIT_TEST_TOUCH_ID,
        responseLinkResult);

    std::vector<RefPtr<FrameNode>> centerHitPath;
    centerHitPath.reserve(hitTestResult.size());
    std::unordered_set<int32_t> visitedNodeIds;
    for (const auto& target : hitTestResult) {
        auto gestureRecognizer = AceType::DynamicCast<NGGestureRecognizer>(target);
        CHECK_NULL_CONTINUE(gestureRecognizer);
        CollectPanGestureNodes(centerHitPath, visitedNodeIds, gestureRecognizer);
    }
    CleanTemporaryGestureArena(context, hitTestResult);
    return centerHitPath;
}

std::vector<RefPtr<FrameNode>> SmartGestureManager::BuildSelectedAncestorPath(
    const RefPtr<FrameNode>& selectedNode) const
{
    std::vector<RefPtr<FrameNode>> ancestorPath;
    auto currentNode = selectedNode ? selectedNode->GetAncestorNodeOfFrame(false) : nullptr;
    while (currentNode) {
        ancestorPath.emplace_back(currentNode);
        currentNode = currentNode->GetAncestorNodeOfFrame(false);
    }
    return ancestorPath;
}

SmartGestureProposal SmartGestureManager::BuildSlideForwardProposal(
    const std::vector<RefPtr<FrameNode>>& visiblePrimaryNodes, const RefPtr<FrameNode>& selectedNode,
    const std::vector<RefPtr<FrameNode>>& centerHitPath) const
{
    if (!visiblePrimaryNodes.empty()) {
        auto nextNode = SmartGestureDecider::GetNextVisiblePrimaryNode(visiblePrimaryNodes, selectedNode);
        if (nextNode) {
            return SmartGestureProposal(
                SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, nextNode);
        }
        auto selectedAncestorPath = BuildSelectedAncestorPath(selectedNode);
        auto scrollProposal = SmartGestureDecider::BuildCenterHitProposal(selectedAncestorPath);
        if (scrollProposal.type != SmartGestureProposalType::NONE_ACTION) {
            return scrollProposal;
        }
        auto firstNode = SmartGestureDecider::GetFirstVisiblePrimaryNode(visiblePrimaryNodes);
        if (firstNode) {
            return SmartGestureProposal(
                SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, firstNode);
        }
        return SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::SLIDE_FORWARD);
    }
    return SmartGestureDecider::BuildCenterHitProposal(centerHitPath);
}

void SmartGestureManager::RevealSelectedNodeIfNeeded(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto revealTarget = ResolveScrollableRevealAnchor(node);
    CHECK_NULL_VOID(revealTarget);
    auto parent = revealTarget->GetParent();
    while (parent) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!parentFrameNode) {
            parent = parent->GetParent();
            continue;
        }
        auto pattern = parentFrameNode->GetPattern();
        if (pattern && pattern->ScrollToNode(revealTarget)) {
            return;
        }
        parent = parent->GetParent();
    }
}

void SmartGestureManager::PaintSelectedNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto focusHub = node->GetFocusHub();
    if (focusHub && focusHub->PaintFocusStateToRenderContext()) {
        selectedPaintedNode_ = node;
        return;
    }
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    renderContext->PaintFocusState(appTheme->GetFocusOutPaddingVp(), appTheme->GetFocusColor(),
        appTheme->GetFocusWidthVp(), appTheme->IsFocusBoxGlow());
    selectedPaintedNode_ = node;
}

void SmartGestureManager::ClearSelectedNodePaint(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto paintedNode = selectedPaintedNode_.Upgrade();
    if (!paintedNode || paintedNode->GetId() != node->GetId()) {
        return;
    }
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->ClearFocusState();
    selectedPaintedNode_.Reset();
}

void SmartGestureManager::SyncSelectedNodePaint(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (IsPrimaryActionNodeSelectable(node)) {
        PaintSelectedNode(node);
        return;
    }
    ClearSelectedNodePaint(node);
}

void SmartGestureManager::RefreshSelectedNodeState()
{
    auto selectedNode = selectedNode_.Upgrade();
    if (!selectedNode) {
        selectedNode_.Reset();
        return;
    }
    if (!IsSelectedNodeValid(selectedNode)) {
        ClearSelected();
    }
}

bool SmartGestureManager::IsSelectedNodeValid(const RefPtr<FrameNode>& node) const
{
    return IsPrimaryActionNodeActive(node) && IsPrimaryActionNodeVisible(node);
}

std::optional<SmartGestureProposal> SmartGestureManager::ResolveProposal(
    const SmartGestureProposal& defaultProposal) const
{
    if (!ValidateProposal(defaultProposal)) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "smart gesture reject invalid default proposal, type=%{public}d",
            static_cast<int32_t>(defaultProposal.type));
        return std::nullopt;
    }
    auto monitor = GetMonitorHandle();
    if (!monitor) {
        return defaultProposal;
    }
    auto resolution = monitor(defaultProposal);
    if (!resolution.isConsumed) {
        return std::nullopt;
    }
    if (!resolution.hasSelectedProposal) {
        return defaultProposal;
    }
    if (!resolution.selectedProposal.has_value()) {
        return std::nullopt;
    }
    if (!ValidateProposal(resolution.selectedProposal.value())) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "smart gesture reject invalid monitor proposal, type=%{public}d",
            static_cast<int32_t>(resolution.selectedProposal->type));
        return std::nullopt;
    }
    return resolution.selectedProposal;
}

void SmartGestureManager::RecordExecutionSnapshot(SmartGestureTrigger trigger, bool hasMonitor,
    const SmartGestureProposal& defaultProposal, const std::optional<SmartGestureProposal>& resolvedProposal,
    bool executeResult) const
{
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto eventManager = context->GetEventManager();
    CHECK_NULL_VOID(eventManager);

    SmartGestureExecutionSnapshot snapshot;
    snapshot.trigger = trigger;
    snapshot.hasMonitor = hasMonitor;
    snapshot.defaultProposalType = defaultProposal.type;
    auto defaultNode = defaultProposal.GetTargetNode();
    snapshot.defaultProposalNodeId = defaultNode ? defaultNode->GetId() : -1;
    if (resolvedProposal.has_value()) {
        snapshot.resolvedProposalType = resolvedProposal->type;
        auto resolvedNode = resolvedProposal->GetTargetNode();
        snapshot.resolvedProposalNodeId = resolvedNode ? resolvedNode->GetId() : -1;
    } else {
        snapshot.resolvedProposalType = SmartGestureProposalType::NONE_ACTION;
        snapshot.resolvedProposalNodeId = -1;
    }
    snapshot.executeResult = executeResult;
    eventManager->RecordSmartGestureExecution(std::move(snapshot));
}

bool SmartGestureManager::ValidateProposal(const SmartGestureProposal& proposal) const
{
    switch (proposal.type) {
        case SmartGestureProposalType::NONE_ACTION:
            return true;
        case SmartGestureProposalType::CLICK:
            return ValidateClickProposal(proposal);
        case SmartGestureProposalType::SELECT:
            return ValidateSelectProposal(proposal);
        case SmartGestureProposalType::SCROLL:
            return ValidateScrollProposal(proposal);
        case SmartGestureProposalType::BACK_PRESS:
            return true;
    }
    return false;
}

bool SmartGestureManager::ValidateTargetNode(const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    auto context = GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(node->GetContextRefPtr() == context, false);
    CHECK_NULL_RETURN(node->IsOnMainTree(), false);
    if (!IsPrimaryActionNodeVisible(node)) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "smart gesture ignore hidden target, nodeId=%{public}d tag=%{public}s",
            node->GetId(), node->GetTag().c_str());
        return false;
    }
    return true;
}

bool SmartGestureManager::ValidateClickProposal(const SmartGestureProposal& proposal) const
{
    auto node = proposal.GetTargetNode();
    CHECK_NULL_RETURN(ValidateTargetNode(node), false);
    CHECK_NULL_RETURN(IsPrimaryActionNodeActive(node), false);
    return IsNodeClickable(node);
}

bool SmartGestureManager::ValidateSelectProposal(const SmartGestureProposal& proposal) const
{
    auto node = proposal.GetTargetNode();
    CHECK_NULL_RETURN(ValidateTargetNode(node), false);
    CHECK_NULL_RETURN(IsPrimaryActionNodeActive(node), false);
    return IsNodeClickable(node);
}

bool SmartGestureManager::ValidateScrollProposal(const SmartGestureProposal& proposal) const
{
    auto node = proposal.GetTargetNode();
    CHECK_NULL_RETURN(ValidateTargetNode(node), false);
    CHECK_NULL_RETURN(proposal.scrollingConfig.has_value() && proposal.scrollingConfig->HasValue(), false);
    auto pattern = node->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsScrollAble(proposal.scrollingConfig->direction);
}

bool SmartGestureManager::ExecuteProposal(const SmartGestureProposal& proposal, const KeyEvent& event)
{
    auto targetNode = proposal.GetTargetNode();
    switch (proposal.type) {
        case SmartGestureProposalType::NONE_ACTION:
            return false;
        case SmartGestureProposalType::SELECT:
            UpdateSelectedNode(targetNode);
            return true;
        case SmartGestureProposalType::CLICK:
            return ExecuteClickProposal(targetNode, event);
        case SmartGestureProposalType::SCROLL:
            return ExecuteScrollProposal(proposal);
        case SmartGestureProposalType::BACK_PRESS:
            ExecuteBackPressProposal();
            return true;
    }
    return false;
}

bool SmartGestureManager::ExecuteClickProposal(const RefPtr<FrameNode>& node, const KeyEvent& event)
{
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(IsPrimaryActionNodeActive(node), false);
    CHECK_NULL_RETURN(IsNodeClickable(node), false);
    auto selectedNode = selectedNode_.Upgrade();
    // Smart-gesture click follows a strict select-then-click flow:
    // 1. If nothing is selected yet, clicking a target first establishes selection only.
    // 2. If another node is selected, the click proposal is rejected directly.
    // 3. Only when the target already matches the current selection do we dispatch OnClick.
    if (!selectedNode) {
        UpdateSelectedNode(node);
        return true;
    }
    if (selectedNode->GetId() != node->GetId()) {
        return false;
    }
    UpdateSelectedNode(node);
    return DispatchSmartGestureClick(node, event);
}

bool SmartGestureManager::ExecuteScrollProposal(const SmartGestureProposal& proposal)
{
    auto node = proposal.GetTargetNode();
    CHECK_NULL_RETURN(node, false);
    auto pattern = node->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(pattern->IsScrollAble(), false);
    CHECK_NULL_RETURN(proposal.scrollingConfig.has_value(), false);
    pattern->PerformScroll(proposal.scrollingConfig.value());
    return true;
}

void SmartGestureManager::ExecuteBackPressProposal()
{
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    int32_t instanceId = context->GetInstanceId();
    auto uiContent = UIContent::GetUIContent(instanceId);
    CHECK_NULL_VOID(uiContent);
    uiContent->ProcessBackPressed();
}

bool SmartGestureManager::IsPrimaryActionNodeActive(const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    auto context = GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(node->GetContextRefPtr() == context, false);
    CHECK_NULL_RETURN(node->IsOnMainTree(), false);
    auto eventHub = node->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(!eventHub || eventHub->IsEnabled(), false);
    auto smartGestureProperty = node->GetSmartGestureProperty();
    return smartGestureProperty && smartGestureProperty->IsPrimaryActionEnabled();
}

bool SmartGestureManager::IsPrimaryActionNodeVisible(const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(GetPipelineContext(), false);
    auto visibleRect = GetNodeVisibleRect(node);
    return IsVisibleRectUsable(visibleRect);
}

bool SmartGestureManager::IsPrimaryActionNodeSelectable(const RefPtr<FrameNode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    auto smartGestureProperty = node->GetSmartGestureProperty();
    return smartGestureProperty && smartGestureProperty->IsPrimaryActionSelectable();
}
} // namespace OHOS::Ace::NG
