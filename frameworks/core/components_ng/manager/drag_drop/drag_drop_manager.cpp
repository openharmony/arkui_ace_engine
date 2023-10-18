/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/point.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/utils/time_util.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "base/geometry/rect.h"
#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#include "core/common/udmf/udmf_client.h"
#endif // ENABLE_DRAG_FRAMEWORK

namespace OHOS::Ace::NG {
#ifdef ENABLE_DRAG_FRAMEWORK
using namespace Msdp::DeviceStatus;
#endif // ENABLE_DRAG_FRAMEWORK
namespace {
int64_t g_proxyId = 0;
#ifdef ENABLE_DRAG_FRAMEWORK
constexpr float PIXELMAP_POSITION_WIDTH = 0.5f;
constexpr float PIXELMAP_POSITION_HEIGHT = 0.2f;
#endif // ENABLE_DRAG_FRAMEWORK
} // namespace

RefPtr<DragDropProxy> DragDropManager::CreateAndShowDragWindow(
    const RefPtr<PixelMap>& pixelMap, const GestureEvent& info)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    SetIsDragged(true);
    isDragCancel_ = false;
#if !defined(PREVIEW)
    if (dragWindow_) {
        LOGW("CreateAndShowDragWindow: There is a drag window, create drag window failed.");
        return nullptr;
    }

    CreateDragWindow(info, pixelMap->GetWidth(), pixelMap->GetHeight());
    if (!dragWindow_) {
        return nullptr;
    }
    dragWindow_->DrawPixelMap(pixelMap);
#endif
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

RefPtr<DragDropProxy> DragDropManager::CreateAndShowDragWindow(
    const RefPtr<UINode>& customNode, const GestureEvent& info)
{
    dragWindowRootNode_ = CreateDragRootNode(customNode);
    CHECK_NULL_RETURN(dragWindowRootNode_, nullptr);
    SetIsDragged(true);
    isDragCancel_ = false;
#if !defined(PREVIEW)
    if (dragWindow_) {
        LOGW("CreateAndShowDragWindow: There is a drag window, create drag window failed.");
        return nullptr;
    }

    auto geometryNode = dragWindowRootNode_->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);

    auto frameRect = geometryNode->GetFrameSize();
    CreateDragWindow(info, static_cast<uint32_t>(frameRect.Width()), static_cast<uint32_t>(frameRect.Height()));
    if (!dragWindow_) {
        return nullptr;
    }
    dragWindow_->DrawFrameNode(dragWindowRootNode_);
#endif
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

RefPtr<DragDropProxy> DragDropManager::CreateTextDragDropProxy()
{
    SetIsDragged(true);
    isDragCancel_ = false;
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

void DragDropManager::CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height)
{
    LOGI("CreateDragWindow");
#if !defined(PREVIEW)
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rect = pipeline->GetCurrentWindowRect();
    dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
        static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
        static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), width, height);
    if (dragWindow_) {
        dragWindow_->SetOffset(rect.Left(), rect.Top());
    } else {
        LOGE("dragWindow create failed!");
    }
#endif
}

RefPtr<FrameNode> DragDropManager::CreateDragRootNode(const RefPtr<UINode>& customNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);

    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode->SetActive(true);
    rootNode->SetHostRootId(pipeline->GetInstanceId());
    rootNode->SetHostPageId(-1);
    rootNode->AddChild(customNode);
    rootNode->AttachToMainTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    pipeline->FlushUITasks();
    return rootNode;
}

void DragDropManager::UpdateDragWindowPosition(int32_t globalX, int32_t globalY)
{
#if !defined(PREVIEW)
    CHECK_NULL_VOID(dragWindow_);
    dragWindow_->MoveTo(globalX, globalY);
#endif
}

#ifdef ENABLE_DRAG_FRAMEWORK
void DragDropManager::UpdatePixelMapPosition(int32_t globalX, int32_t globalY)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto rootNode = pipeline->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    if (manager->GetHasPixelMap()) {
        auto columnNode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetLastChild());
        CHECK_NULL_VOID(columnNode);
        auto imageNode = AceType::DynamicCast<NG::FrameNode>(columnNode->GetLastChild());
        CHECK_NULL_VOID(imageNode);
        auto geometryNode = imageNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto width = geometryNode->GetFrameSize().Width();
        auto height = geometryNode->GetFrameSize().Height();
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        CHECK_NULL_VOID(draggedFrameNode_);
        auto hub = draggedFrameNode_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(hub);
        if (!hub->GetTextDraggable()) {
            hub = columnNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(hub);
        }
        RefPtr<PixelMap> pixelMap = hub->GetPixelMap();
        CHECK_NULL_VOID(pixelMap);
        float scale = NearZero(width) ? 1.0f : pixelMap->GetWidth() / width;
        imageContext->UpdatePosition(NG::OffsetT<Dimension>(
            Dimension(globalX - width * PIXELMAP_POSITION_WIDTH * scale - width / 2.0f + width * scale / 2.0f),
            Dimension(globalY - height * PIXELMAP_POSITION_HEIGHT * scale - height / 2.0f + height * scale / 2.0f)));
        imageContext->OnModifyDone();
    }
}
#endif // ENABLE_DRAG_FRAMEWORK

RefPtr<FrameNode> DragDropManager::FindTargetInChildNodes(
    const RefPtr<UINode> parentNode, std::vector<RefPtr<FrameNode>> hitFrameNodes, bool findDrop)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    if (parentFrameNode && (!parentFrameNode->IsActive() || !parentFrameNode->IsVisible())) {
        return nullptr;
    }
    auto children = parentNode->GetChildren();

    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto child = *iter;
        if (child == nullptr) {
            LOGW("when findding target in child nodes, find child is nullptr");
            continue;
        }
        auto childFindResult = FindTargetInChildNodes(child, hitFrameNodes, findDrop);
        if (childFindResult) {
            return childFindResult;
        }
    }

    CHECK_NULL_RETURN(parentFrameNode, nullptr);
    for (auto iter : hitFrameNodes) {
        if (parentFrameNode == iter) {
            auto eventHub = parentFrameNode->GetEventHub<EventHub>();
            if (!eventHub) {
                continue;
            }
            if (eventHub->HasOnDrop() || eventHub->HasOnItemDrop() || eventHub->HasCustomerOnDrop()) {
                return parentFrameNode;
            }
            if (SystemProperties::GetDebugEnabled()) {
                LOGW("Iter is in hitFrameNodes, but findDrop not suit with bind function.");
            }
        }
    }
    return nullptr;
}

RefPtr<FrameNode> DragDropManager::FindDragFrameNodeByPosition(
    float globalX, float globalY, DragType dragType, bool findDrop)
{
    std::map<int32_t, WeakPtr<FrameNode>> frameNodes;
    switch (dragType) {
        case DragType::COMMON:
            frameNodes = dragFrameNodes_;
            break;
        case DragType::GRID:
            frameNodes = gridDragFrameNodes_;
            break;
        case DragType::LIST:
            frameNodes = listDragFrameNodes_;
            break;
        case DragType::TEXT:
            frameNodes = textFieldDragFrameNodes_;
            break;
        default:
            break;
    }

    if (frameNodes.empty()) {
        if (SystemProperties::GetDebugEnabled()) {
            LOGW("FrameNodes which have onDragMove or onDrop set is empty, cannot find targetNode.");
        }
        return nullptr;
    }

    PointF point(globalX, globalY);
    std::vector<RefPtr<FrameNode>> hitFrameNodes;
    for (auto iterOfFrameNode = frameNodes.begin(); iterOfFrameNode != frameNodes.end(); iterOfFrameNode++) {
        auto frameNode = iterOfFrameNode->second.Upgrade();
        if (!frameNode || !frameNode->IsVisible()) {
            continue;
        }
        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        auto globalFrameRect = geometryNode->GetFrameRect();
        globalFrameRect.SetOffset(frameNode->GetTransformRelativeOffset());
        if (globalFrameRect.IsInRegion(point)) {
            hitFrameNodes.push_back(frameNode);
        }
    }

    if (hitFrameNodes.empty()) {
        if (SystemProperties::GetDebugEnabled()) {
            LOGW("HitFrameNodes vector is empty, cannot find targetNode.");
        }
        return nullptr;
    }
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(manager, nullptr);
    auto rootNode = pipeline->GetRootElement();

    auto result = FindTargetInChildNodes(rootNode, hitFrameNodes, findDrop);
    if (result) {
        return result;
    }
    if (SystemProperties::GetDebugEnabled()) {
        LOGW("Don't find targetNode by position in rootNode, return nullptr.");
    }
    return nullptr;
}

bool DragDropManager::CheckDragDropProxy(int64_t id) const
{
    return currentId_ == id;
}

#ifdef ENABLE_DRAG_FRAMEWORK
void DragDropManager::UpdateDragAllowDrop(const RefPtr<FrameNode>& dragFrameNode, const bool isCopy)
{
    const auto& dragFrameNodeAllowDrop = dragFrameNode->GetAllowDrop();
    if (dragFrameNodeAllowDrop.empty() || summaryMap_.empty()) {
        InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::MOVE);
        return;
    }
    for (const auto& it : summaryMap_) {
        if (dragFrameNodeAllowDrop.find(it.first) == dragFrameNodeAllowDrop.end()) {
            InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::FORBIDDEN);
            return;
        }
    }
    InteractionManager::GetInstance()->UpdateDragStyle(isCopy ? DragCursorStyle::COPY : DragCursorStyle::MOVE);
}
#endif // ENABLE_DRAG_FRAMEWORK

void DragDropManager::RegisterDragStatusListener(int32_t nodeId, const WeakPtr<FrameNode>& node)
{
    auto ret = nodesForDragNotify_.try_emplace(nodeId, node);
    if (!ret.second) {
        nodesForDragNotify_[nodeId] = node;
    }
}

void DragDropManager::UnRegisterDragStatusListener(int32_t nodeId)
{
    nodesForDragNotify_.erase(nodeId);
}

bool CheckParentVisible(const RefPtr<FrameNode>& frameNode)
{
    bool isVisible = frameNode->IsVisible();
    if (!isVisible) {
        return false;
    }
    auto parent = frameNode->GetParent();
    while (parent && parent->GetDepth() != 1) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(parent);
        if (parentFrameNode && !parentFrameNode->IsVisible()) {
            isVisible = false;
            break;
        }
        parent = parent->GetParent();
    }
    return isVisible;
}

std::unordered_set<int32_t> DragDropManager::FindHitFrameNodes(const Point& point)
{
    std::unordered_set<int32_t> frameNodeList;
    for (auto iter = nodesForDragNotify_.begin(); iter != nodesForDragNotify_.end(); iter++) {
        auto frameNode = iter->second.Upgrade();
        if (!frameNode || !frameNode->IsActive() || !frameNode->IsVisible()) {
            continue;
        }
        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        auto globalFrameRect = geometryNode->GetFrameRect();
        globalFrameRect.SetOffset(frameNode->GetTransformRelativeOffset());
        if (globalFrameRect.IsInRegion(PointF(static_cast<float>(point.GetX()), static_cast<float>(point.GetY())))) {
            frameNodeList.emplace(frameNode->GetId());
        }
    }
    return frameNodeList;
}

void DragDropManager::UpdateDragListener(const Point& point)
{
    auto hitNodes = FindHitFrameNodes(point);
    std::unordered_map<int32_t, WeakPtr<FrameNode>> dragEnterNodes;
    std::unordered_map<int32_t, WeakPtr<FrameNode>> dragMoveNodes;
    std::unordered_map<int32_t, WeakPtr<FrameNode>> dragLeaveNodes;
    for (auto iter = nodesForDragNotify_.begin(); iter != nodesForDragNotify_.end(); iter++) {
        auto localHitResult = hitNodes.find(iter->first) != hitNodes.end();
        auto preHitResult = parentHitNodes_.find(iter->first) != parentHitNodes_.end();
        if (localHitResult && preHitResult) {
            dragMoveNodes[iter->first] = iter->second;
        }
        if (localHitResult && !preHitResult) {
            dragEnterNodes[iter->first] = iter->second;
        }
        if (!localHitResult && preHitResult) {
            dragLeaveNodes[iter->first] = iter->second;
        }
    }
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    UpdateNotifyDragEvent(notifyEvent, point, DragEventType::MOVE);

    NotifyDragRegisterFrameNode(dragMoveNodes, DragEventType::MOVE, notifyEvent);
    NotifyDragRegisterFrameNode(dragEnterNodes, DragEventType::ENTER, notifyEvent);
    NotifyDragRegisterFrameNode(dragLeaveNodes, DragEventType::LEAVE, notifyEvent);
    parentHitNodes_ = std::move(hitNodes);
}

void DragDropManager::NotifyDragRegisterFrameNode(std::unordered_map<int32_t, WeakPtr<FrameNode>> nodes,
    DragEventType dragEventType, RefPtr<NotifyDragEvent>& notifyEvent)
{
    for (auto iter = nodes.begin(); iter != nodes.end(); iter++) {
        auto frameNode = iter->second.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetEventHub<EventHub>();
        if (!CheckParentVisible(frameNode) || (eventHub && !eventHub->IsEnabled())) {
            if (SystemProperties::GetDebugEnabled()) {
                LOGI("DragDropManager NotifyDragRegisterFrameNode. Dragged frameNode is %{public}s is InVisible or "
                     "Disabled",
                    frameNode->GetTag().c_str());
            }
            continue;
        }
        auto pattern = frameNode->GetPattern<Pattern>();
        CHECK_NULL_VOID(pattern);
#ifdef ENABLE_DRAG_FRAMEWORK
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager NotifyDragRegisterFrameNode. Dragged frameNode is %{public}s, depth is %{public}d, "
                 "DragEventType is %{public}d.",
                frameNode->GetTag().c_str(), frameNode->GetDepth(), static_cast<int32_t>(dragEventType));
        }
        pattern->HandleOnDragStatusCallback(dragEventType, notifyEvent);
#endif // ENABLE_DRAG_FRAMEWORK
    }
}

void DragDropManager::OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    CHECK_NULL_VOID(frameNode);
    preTargetFrameNode_ = frameNode;
    draggedFrameNode_ = preTargetFrameNode_;
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("DragDropManager onDragStart. Dragged frameNode is %{public}s, depth is %{public}d.",
            frameNode->GetTag().c_str(), frameNode->GetDepth());
    }
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    UpdateNotifyDragEvent(notifyEvent, point, DragEventType::START);
    NotifyDragRegisterFrameNode(nodesForDragNotify_, DragEventType::START, notifyEvent);
}

void DragDropManager::PrintDragFrameNode(const Point& point, const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);
    if (SystemProperties::GetDebugEnabled()) {
        if (preTargetFrameNode_) {
            LOGI("Position is %{public}f and %{public}f.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()));
            LOGI("PreTargetFrameNode is %{public}s, depth is %{public}d.",
                preTargetFrameNode_->GetTag().c_str(), preTargetFrameNode_->GetDepth());
            LOGI("New find targetNode is %{public}s, depth is %{public}d.",
                dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
        } else {
            LOGI("Position is %{public}f and %{public}f.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()));
            LOGI("PreTargetFrameNode is nullptr.");
            LOGI("New find targetNode is %{public}s, depth is %{public}d.",
                dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
        }
    }
}

void DragDropManager::OnDragMove(const Point& point, const std::string& extraInfo)
{
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            LOGD("The event does not need to be handled");
            SetIsWindowConsumed(false);
            return;
        }
    }
    SetIsWindowConsumed(false);
#endif // ENABLE_DRAG_FRAMEWORK
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(point);
    auto dragFrameNode = FindDragFrameNodeByPosition(
        static_cast<float>(point.GetX()), static_cast<float>(point.GetY()), DragType::COMMON, false);
    PrintDragFrameNode(point, dragFrameNode);
    if (!dragFrameNode) {
        if (preTargetFrameNode_) {
            FireOnDragEvent(preTargetFrameNode_, point, DragEventType::LEAVE, extraInfo);
            preTargetFrameNode_ = nullptr;
        }

#ifdef ENABLE_DRAG_FRAMEWORK
        if (!isMouseDragged_ || isDragWindowShow_) {
            InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::MOVE);
        }
#endif // ENABLE_DRAG_FRAMEWORK
        return;
    }

    if (dragFrameNode == preTargetFrameNode_) {
        FireOnDragEvent(dragFrameNode, point, DragEventType::MOVE, extraInfo);
        return;
    }

    if (preTargetFrameNode_) {
        auto preRect = preTargetFrameNode_->GetTransformRectRelativeToWindow();
        if (!preRect.IsInRegion(PointF(static_cast<float>(point.GetX()), static_cast<float>(point.GetY())))) {
            FireOnDragEvent(preTargetFrameNode_, point, DragEventType::LEAVE, extraInfo);
        }
    }
    FireOnDragEvent(dragFrameNode, point, DragEventType::ENTER, extraInfo);
    preTargetFrameNode_ = dragFrameNode;
}

#ifdef ENABLE_DRAG_FRAMEWORK
DragResult TranslateDragResult(DragRet dragResult)
{
    switch (dragResult) {
        case DragRet::DRAG_SUCCESS:
            return DragResult::DRAG_SUCCESS;
        case DragRet::DRAG_FAIL:
            return DragResult::DRAG_FAIL;
        case DragRet::DRAG_CANCEL:
            return DragResult::DRAG_CANCEL;
        default:
            return DragResult::DRAG_SUCCESS;
    }
}
#endif // ENABLE_DRAG_FRAMEWORK

void DragDropManager::OnDragEnd(const Point& point, const std::string& extraInfo)
{
    dragDropState_ = DragDropMgrState::IDLE;
    preTargetFrameNode_ = nullptr;
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            LOGD("The event does not need to be handled");
            return;
        }
    }
    if (isDragCancel_) {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager is dragCancel, finish drag. WindowId is %{public}d.", container->GetWindowId());
        }
        InteractionManager::GetInstance()->SetDragWindowVisible(false);
        DragDropResult dropResult { DragResult::DRAG_CANCEL, false, container->GetWindowId() };
        InteractionManager::GetInstance()->StopDrag(dropResult);
        RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
        UpdateNotifyDragEvent(notifyEvent, point, DragEventType::DROP);
        notifyEvent->SetResult(DragRet::DRAG_CANCEL);
        NotifyDragRegisterFrameNode(nodesForDragNotify_, DragEventType::DROP, notifyEvent);
        summaryMap_.clear();
        parentHitNodes_.clear();
        ClearVelocityInfo();
        return;
    }
#endif // ENABLE_DRAG_FRAMEWORK
    UpdateVelocityTrackerPoint(point, true);
    auto dragFrameNode = FindDragFrameNodeByPosition(
        static_cast<float>(point.GetX()), static_cast<float>(point.GetY()), DragType::COMMON, true);
    if (SystemProperties::GetDebugEnabled()) {
        if (dragFrameNode) {
            LOGI("Position is %{public}f and %{public}f. TargetNode is %{public}s.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()),
                dragFrameNode->GetTag().c_str());
        } else {
            LOGI("Position is %{public}f and %{public}f. TargetNode is nullptr.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()));
        }
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    if (!dragFrameNode) {
        if (SystemProperties::GetDebugEnabled()) {
            LOGW("DragDropManager onDragEnd, not find drop target, stop drag. WindowId is %{public}d.",
                container->GetWindowId());
        }
        DragDropResult dropResult { DragResult::DRAG_FAIL, isMouseDragged_, container->GetWindowId() };
        InteractionManager::GetInstance()->StopDrag(dropResult);
        RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
        UpdateNotifyDragEvent(notifyEvent, point, DragEventType::DROP);
        notifyEvent->SetResult(DragRet::DRAG_FAIL);
        NotifyDragRegisterFrameNode(nodesForDragNotify_, DragEventType::DROP, notifyEvent);
        summaryMap_.clear();
        parentHitNodes_.clear();
        return;
    }
#endif // ENABLE_DRAG_FRAMEWORK
    CHECK_NULL_VOID(dragFrameNode);
    auto eventHub = dragFrameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto extraParams = eventHub->GetDragExtraParams(extraInfo_, point, DragEventType::DROP);
    UpdateDragEvent(event, point);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, event, extraParams);
    eventHub->HandleInternalOnDrop(event, extraParams);
    ClearVelocityInfo();
#ifdef ENABLE_DRAG_FRAMEWORK
    SetIsDragged(false);
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("DragDropManager finish drop, start do drop animation. UseCustomAnimation is %{public}d."
        " WindowId is %{public}d.",
            event->IsUseCustomAnimation(), container->GetWindowId());
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragResult = TranslateDragResult(event->GetResult());
    auto useCustomAnimation = event->IsUseCustomAnimation();
    auto windowId = container->GetWindowId();
    pipeline->SetDragCleanTask([dragResult, useCustomAnimation, isMouseDragged = isMouseDragged_, windowId]() {
        InteractionManager::GetInstance()->SetDragWindowVisible(isMouseDragged ? !isMouseDragged : !useCustomAnimation);
        DragDropResult dropResult { dragResult, isMouseDragged ? isMouseDragged : useCustomAnimation, windowId };
        InteractionManager::GetInstance()->StopDrag(dropResult);
    });
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    UpdateNotifyDragEvent(notifyEvent, point, DragEventType::DROP);
    notifyEvent->SetResult(event->GetResult());
    NotifyDragRegisterFrameNode(nodesForDragNotify_, DragEventType::DROP, notifyEvent);
    dragFrameNode->MarkDirtyNode();
    summaryMap_.clear();
    parentHitNodes_.clear();
#endif // ENABLE_DRAG_FRAMEWORK
}

#ifdef ENABLE_DRAG_FRAMEWORK
void DragDropManager::RequireSummary()
{
    std::string udKey;
    InteractionManager::GetInstance()->GetUdKey(udKey);
    if (SystemProperties::GetDebugEnabled()) {
        if (udKey.empty()) {
            LOGW("Requiry summary get empty udKey.");
        } else {
            LOGI("Requiry summary get udKey %{public}s", udKey.c_str());
        }
    }
    std::map<std::string, int64_t> summary;
    int32_t ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
    if (ret != 0) {
        LOGW("OnDragStart: UDMF GetSummary failed: %{public}d", ret);
    }
    previewRect_ = Rect(-1, -1, -1, -1);
    summaryMap_ = summary;
}

void DragDropManager::ResetRecordSize(uint32_t recordSize)
{
    recordSize_ = recordSize;
}

uint32_t DragDropManager::GetRecordSize() const
{
    return recordSize_;
}

Rect DragDropManager::GetDragWindowRect(const Point& point)
{
    if (!previewRect_.IsValid()) {
        int x = -1;
        int y = -1;
        int width = -1;
        int height = -1;
        int retOffset = InteractionManager::GetInstance()->GetShadowOffset(x, y, width, height);
        if (retOffset == 0) {
            previewRect_ = Rect(x, y, width, height);
        } else if (SystemProperties::GetDebugEnabled()) {
            LOGW("InteractionManager GetShadowOffset is failed:%{public}d", retOffset);
        }
    }
    return previewRect_ + Offset(point.GetX(), point.GetY());
}

void DragDropManager::ClearSummary()
{
    previewRect_ = Rect(-1, -1, -1, -1);
    summaryMap_.clear();
    parentHitNodes_.clear();
    ResetRecordSize();
}
#endif // ENABLE_DRAG_FRAMEWORK

void DragDropManager::OnTextDragEnd(float globalX, float globalY, const std::string& extraInfo)
{
    dragDropState_ = DragDropMgrState::IDLE;
    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY, DragType::TEXT, true);
    if (dragFrameNode) {
        auto textFieldPattern = dragFrameNode->GetPattern<TextFieldPattern>();
        if (textFieldPattern) {
            textFieldPattern->InsertValue(extraInfo);
        }
    }
    LOGI("OnTextDragEnd");
    SetIsDragged(false);
    currentId_ = -1;
}

void DragDropManager::onDragCancel()
{
    preTargetFrameNode_ = nullptr;
    draggedFrameNode_ = nullptr;
}

void DragDropManager::FireOnDragEventWithDragType(const RefPtr<EventHub>& eventHub, DragEventType type,
    RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams)
{
    switch (type) {
        case DragEventType::ENTER: {
            eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, event, extraParams);
            eventHub->FireOnDragEnter(event, extraParams);
            break;
        }
        case DragEventType::MOVE: {
            eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, event, extraParams);
            eventHub->FireOnDragMove(event, extraParams);
            break;
        }
        case DragEventType::LEAVE: {
            eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, event, extraParams);
            eventHub->FireOnDragLeave(event, extraParams);
            break;
        }
        case DragEventType::DROP: {
            eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, event, extraParams);
            eventHub->HandleInternalOnDrop(event, extraParams);
            break;
        }
        default:
            break;
    }
}

void DragDropManager::FireOnDragEvent(
    const RefPtr<FrameNode>& frameNode, const Point& point, DragEventType type, const std::string& extraInfo)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto extraParams = eventHub->GetDragExtraParams(extraInfo_.empty() ? extraInfo : extraInfo_, point, type);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    event->SetX((double)point.GetX());
    event->SetY((double)point.GetY());
    event->SetScreenX((double)point.GetScreenX());
    event->SetScreenY((double)point.GetScreenY());
    event->SetVelocity(velocityTracker_.GetVelocity());
#ifdef ENABLE_DRAG_FRAMEWORK
    event->SetSummary(summaryMap_);
    event->SetPreviewRect(GetDragWindowRect(point));
#endif // ENABLE_DRAG_FRAMEWORK

    FireOnDragEventWithDragType(eventHub, type, event, extraParams);

#ifdef ENABLE_DRAG_FRAMEWORK
    if (isMouseDragged_ && !isDragWindowShow_) {
        return;
    }
    if (event->GetResult() == DragRet::ENABLE_DROP) {
        if (event->IsCopy()) {
            InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::COPY);
        } else {
            InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::MOVE);
        }
    } else if (event->GetResult() == DragRet::DISABLE_DROP) {
        InteractionManager::GetInstance()->UpdateDragStyle(DragCursorStyle::FORBIDDEN);
    } else {
        UpdateDragAllowDrop(frameNode, event->IsCopy());
    }
#endif // ENABLE_DRAG_FRAMEWORK
}

void DragDropManager::OnItemDragStart(float globalX, float globalY, const RefPtr<FrameNode>& frameNode)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    preGridTargetFrameNode_ = frameNode;
    draggedGridFrameNode_ = frameNode;
}

void DragDropManager::OnItemDragMove(float globalX, float globalY, int32_t draggedIndex, DragType dragType)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    UpdateDragWindowPosition(static_cast<int32_t>(globalX), static_cast<int32_t>(globalY));

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(pipeline->ConvertPxToVp(Dimension(globalX, DimensionUnit::PX)));
    itemDragInfo.SetY(pipeline->ConvertPxToVp(Dimension(globalY, DimensionUnit::PX)));

    // use -1 for grid item not in eventGrid
    auto getDraggedIndex = [draggedGrid = draggedGridFrameNode_, draggedIndex, dragType](
                               const RefPtr<FrameNode>& eventGrid) {
        return (dragType == DragType::GRID) ? (eventGrid == draggedGrid ? draggedIndex : -1) : draggedIndex;
    };

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY, dragType, false);
    if (!dragFrameNode) {
        if (preGridTargetFrameNode_) {
            FireOnItemDragEvent(preGridTargetFrameNode_, dragType, itemDragInfo, DragEventType::LEAVE,
                getDraggedIndex(preGridTargetFrameNode_));
            preGridTargetFrameNode_ = nullptr;
        }
        return;
    }

    if (dragFrameNode == preGridTargetFrameNode_) {
        int32_t insertIndex = GetItemIndex(dragFrameNode, dragType, globalX, globalY);
        FireOnItemDragEvent(
            dragFrameNode, dragType, itemDragInfo, DragEventType::MOVE, getDraggedIndex(dragFrameNode), insertIndex);
        return;
    }

    if (preGridTargetFrameNode_) {
        FireOnItemDragEvent(preGridTargetFrameNode_, dragType, itemDragInfo, DragEventType::LEAVE,
            getDraggedIndex(preGridTargetFrameNode_));
    }

    FireOnItemDragEvent(dragFrameNode, dragType, itemDragInfo, DragEventType::ENTER, getDraggedIndex(dragFrameNode));
    preGridTargetFrameNode_ = dragFrameNode;
}

void DragDropManager::OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType)
{
    dragDropState_ = DragDropMgrState::IDLE;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(pipeline->ConvertPxToVp(Dimension(globalX, DimensionUnit::PX)));
    itemDragInfo.SetY(pipeline->ConvertPxToVp(Dimension(globalY, DimensionUnit::PX)));

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY, dragType, true);
    if (!dragFrameNode) {
        // drag on one grid and drop on other area
        if (draggedGridFrameNode_) {
            if (dragType == DragType::GRID) {
                auto eventHub = draggedGridFrameNode_->GetEventHub<GridEventHub>();
                CHECK_NULL_VOID(eventHub);
                eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, -1, false);
            } else {
                auto eventHub = draggedGridFrameNode_->GetEventHub<ListEventHub>();
                CHECK_NULL_VOID(eventHub);
                eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, -1, false);
            }
        }
    } else {
        int32_t insertIndex = GetItemIndex(dragFrameNode, dragType, globalX, globalY);
        // drag and drop on the same grid
        if (dragFrameNode == draggedGridFrameNode_) {
            FireOnItemDropEvent(dragFrameNode, dragType, itemDragInfo, draggedIndex, insertIndex, true);
        } else {
            // drag and drop on different grid
            bool isSuccess = FireOnItemDropEvent(dragFrameNode, dragType, itemDragInfo, -1, insertIndex, true);
            if (draggedGridFrameNode_) {
                FireOnItemDropEvent(draggedGridFrameNode_, dragType, itemDragInfo, draggedIndex, -1, isSuccess);
            }
        }
    }

    preGridTargetFrameNode_ = nullptr;
    draggedGridFrameNode_ = nullptr;
}

void DragDropManager::onItemDragCancel()
{
    preGridTargetFrameNode_ = nullptr;
    draggedGridFrameNode_ = nullptr;
}

void DragDropManager::FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
    const OHOS::Ace::ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex)
{
    if (dragType == DragType::GRID) {
        auto eventHub = frameNode->GetEventHub<GridEventHub>();
        CHECK_NULL_VOID(eventHub);
        switch (type) {
            case DragEventType::ENTER:
                eventHub->FireOnItemDragEnter(itemDragInfo);
                break;
            case DragEventType::MOVE:
                eventHub->FireOnItemDragMove(itemDragInfo, draggedIndex, insertIndex);
                break;
            case DragEventType::LEAVE:
                eventHub->FireOnItemDragLeave(itemDragInfo, draggedIndex);
                break;
            default:
                break;
        }
    } else if (dragType == DragType::LIST) {
        auto eventHub = frameNode->GetEventHub<ListEventHub>();
        CHECK_NULL_VOID(eventHub);
        switch (type) {
            case DragEventType::ENTER:
                eventHub->FireOnItemDragEnter(itemDragInfo);
                break;
            case DragEventType::MOVE:
                eventHub->FireOnItemDragMove(itemDragInfo, draggedIndex, insertIndex);
                break;
            case DragEventType::LEAVE:
                eventHub->FireOnItemDragLeave(itemDragInfo, draggedIndex);
                break;
            default:
                break;
        }
    }
}

bool DragDropManager::FireOnItemDropEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
    const OHOS::Ace::ItemDragInfo& itemDragInfo, int32_t draggedIndex, int32_t insertIndex, bool isSuccess)
{
    if (dragType == DragType::GRID) {
        auto eventHub = frameNode->GetEventHub<GridEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        return eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, insertIndex, isSuccess);
    } else if (dragType == DragType::LIST) {
        auto eventHub = frameNode->GetEventHub<ListEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        return eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, insertIndex, isSuccess);
    }
    return false;
}

int32_t DragDropManager::GetItemIndex(
    const RefPtr<FrameNode>& frameNode, DragType dragType, float globalX, float globalY)
{
    CHECK_NULL_RETURN(frameNode, -1);
    if (dragType == DragType::GRID) {
        auto eventHub = frameNode->GetEventHub<GridEventHub>();
        CHECK_NULL_RETURN(eventHub, -1);
        if (frameNode != draggedGridFrameNode_) {
            return eventHub->GetInsertPosition(globalX, globalY);
        }
        auto itemFrameNode = frameNode->FindChildByPosition(globalX, globalY);
        if (!itemFrameNode) {
            if (eventHub->CheckPostionInGrid(globalX, globalY)) {
                return eventHub->GetFrameNodeChildSize();
            }
        } else {
            return eventHub->GetGridItemIndex(itemFrameNode);
        }
    } else if (dragType == DragType::LIST) {
        auto eventHub = frameNode->GetEventHub<ListEventHub>();
        CHECK_NULL_RETURN(eventHub, -1);
        return eventHub->GetListItemIndexByPosition(globalX, globalY);
    }
    return -1;
}

void DragDropManager::AddDataToClipboard(const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (!extraInfo.empty()) {
        if (!newData_) {
            newData_ = JsonUtil::Create(true);
            newData_->Put("customDragInfo", extraInfo.c_str());
        } else {
            newData_->Replace("customDragInfo", extraInfo.c_str());
        }
    } else {
        return;
    }
    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }
    if (!addDataCallback_) {
        auto callback = [weakManager = WeakClaim(this)](const std::string& data) {
            auto dragDropManager = weakManager.Upgrade();
            auto addData = dragDropManager->newData_->ToString();
            CHECK_NULL_VOID(dragDropManager);
            auto clipboardAllData = JsonUtil::Create(true);
            clipboardAllData->Put("preData", data.c_str());
            clipboardAllData->Put("newData", addData.c_str());
            dragDropManager->clipboard_->SetData(clipboardAllData->ToString(), CopyOptions::Local, true);
        };
        addDataCallback_ = callback;
    }
    if (clipboard_) {
        clipboard_->GetData(addDataCallback_, true);
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    extraInfo_ = extraInfo;
#endif // ENABLE_DRAG_FRAMEWORK
}

void DragDropManager::GetExtraInfoFromClipboard(std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }

    if (!getDataCallback_) {
        auto callback = [weak = WeakClaim(this)](const std::string& data) {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto json = JsonUtil::ParseJsonString(data);
            auto newData = JsonUtil::ParseJsonString(json->GetString("newData"));
            manager->extraInfo_ = newData->GetString("customDragInfo");
        };
        getDataCallback_ = callback;
    }

    if (getDataCallback_ && clipboard_) {
        clipboard_->GetData(getDataCallback_, true);
    }

    extraInfo = extraInfo_;
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("DragDropManager get extra info from clipBoard, extraInfo is %{public}s",
            extraInfo_.c_str());
    }
}

void DragDropManager::RestoreClipboardData()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }

    if (!deleteDataCallback_) {
        auto callback = [weakManager = WeakClaim(this)](const std::string& data) {
            auto dragDropManager = weakManager.Upgrade();
            CHECK_NULL_VOID(dragDropManager);
            auto json = JsonUtil::ParseJsonString(data);
            if (json->Contains("preData")) {
                dragDropManager->clipboard_->SetData(json->GetString("preData"));
            }
        };
        deleteDataCallback_ = callback;
    }
    if (clipboard_) {
        clipboard_->GetData(deleteDataCallback_, true);
    }
}

void DragDropManager::DestroyDragWindow()
{
#if !defined(PREVIEW) && !defined(ENABLE_DRAG_FRAMEWORK)
    CHECK_NULL_VOID(dragWindow_);
    dragWindow_->Destroy();
    dragWindow_ = nullptr;
#elif defined(ENABLE_DRAG_FRAMEWORK)
    if (dragWindow_ != nullptr) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
    }
    ResetRecordSize();
#endif // ENABLE_DRAG_FRAMEWORK
    if (dragWindowRootNode_) {
        dragWindowRootNode_ = nullptr;
    }
    LOGI("DestroyDragWindow");
    SetIsDragged(false);
    SetIsDragWindowShow(false);
    previewRect_ = Rect(-1, -1, -1, -1);
    isMouseDragged_ = false;
    currentId_ = -1;
}

#ifdef ENABLE_DRAG_FRAMEWORK
RefPtr<DragDropProxy> DragDropManager::CreateFrameworkDragDropProxy()
{
    SetIsDragged(true);
    isDragCancel_ = false;
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}
#endif // ENABLE_DRAG_FRAMEWORK

void DragDropManager::UpdateNotifyDragEvent(
    RefPtr<NotifyDragEvent>& notifyEvent, const Point& point, const DragEventType dragEventType)
{
    notifyEvent->SetX((double)point.GetX());
    notifyEvent->SetY((double)point.GetY());
    notifyEvent->SetScreenX((double)point.GetScreenX());
    notifyEvent->SetScreenY((double)point.GetScreenY());
    if (dragEventType != DragEventType::START) {
        notifyEvent->SetVelocity(velocityTracker_.GetVelocity());
#ifdef ENABLE_DRAG_FRAMEWORK
        notifyEvent->SetSummary(summaryMap_);
        notifyEvent->SetPreviewRect(GetDragWindowRect(point));
#endif // ENABLE_DRAG_FRAMEWORK
    }
}

void DragDropManager::UpdateDragEvent(RefPtr<OHOS::Ace::DragEvent>& event, const Point& point)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    event->SetX(point.GetX());
    event->SetY(point.GetY());
    event->SetScreenX(point.GetScreenX());
    event->SetScreenY(point.GetScreenY());
#ifdef ENABLE_DRAG_FRAMEWORK
    std::string udKey;
    InteractionManager::GetInstance()->GetUdKey(udKey);
    if (udKey.empty()) {
        LOGW("InteractionManager GetUdkey is null");
        event->SetIsGetDataSuccess(false);
    } else {
        event->SetUdKey(udKey);
    }
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->CreateUnifiedData();
    int ret = UdmfClient::GetInstance()->GetData(udData, udKey);
    if (ret != 0) {
        LOGW("UDMF GetData failed: %{public}d", ret);
        event->SetIsGetDataSuccess(false);
    } else {
        event->SetIsGetDataSuccess(true);
    }
    auto unifiedData = udData;
    event->SetData(unifiedData);
    event->SetSummary(summaryMap_);
    int x = -1;
    int y = -1;
    int width = -1;
    int height = -1;
    int retOffset = InteractionManager::GetInstance()->GetShadowOffset(x, y, width, height);
    if (retOffset == 0) {
        previewRect_ = Rect(point.GetX() + x, point.GetY() + y, width, height);
        event->SetPreviewRect(previewRect_);
    } else {
        previewRect_ = Rect(x, y, width, height);
        event->SetPreviewRect(previewRect_);
        LOGW("InteractionManager GetShadowOffset is failed:%{public}d", retOffset);
    }
#endif // ENABLE_DRAG_FRAMEWORK
}

#ifdef ENABLE_DRAG_FRAMEWORK
std::string DragDropManager::GetExtraInfo()
{
    return extraInfo_;
}

void DragDropManager::SetExtraInfo(const std::string& extraInfo)
{
    extraInfo_ = extraInfo;
}

void DragDropManager::ClearExtraInfo()
{
    extraInfo_.clear();
}
#endif // ENABLE_DRAG_FRAMEWORK

void DragDropManager::ClearVelocityInfo()
{
    velocityTracker_.Reset();
}

void DragDropManager::UpdateVelocityTrackerPoint(const Point& point, bool isEnd)
{
    std::chrono::microseconds microseconds(GetMicroTickCount());
    TimeStamp curTime(microseconds);
    velocityTracker_.UpdateTrackerPoint(point.GetX(), point.GetY(), curTime, isEnd);
}

} // namespace OHOS::Ace::NG
