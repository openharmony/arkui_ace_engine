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
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/utils/time_util.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "base/geometry/rect.h"
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

void DragDropManager::OnDragOut()
{
#ifdef ENABLE_DRAG_FRAMEWORK
    if (IsNeedScaleDragPreview()) {
        InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        auto containerId = Container::CurrentId();
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        auto overlayManager = subwindow->GetOverlayManager();
        overlayManager->RemovePixelMap();
        SubwindowManager::GetInstance()->HidePreviewNG();
        info_.scale = -1.0;
    }
#endif
}

void DragDropManager::CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height)
{
#if !defined(PREVIEW)
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rect = pipeline->GetDisplayWindowRectInfo();
    dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
        static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
        static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), width, height);
    if (dragWindow_) {
        dragWindow_->SetOffset(rect.Left(), rect.Top());
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
    auto children = parentFrameNode->GetFrameChildren();

    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto child = iter->Upgrade();
        if (child == nullptr) {
            continue;
        }
        auto childNode = AceType::DynamicCast<UINode>(child);
        auto childFindResult = FindTargetInChildNodes(childNode, hitFrameNodes, findDrop);
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
            if (eventHub->HasOnDrop() || eventHub->HasOnItemDrop() || eventHub->HasCustomerOnDrop()
                || V2::UI_EXTENSION_COMPONENT_ETS_TAG == parentFrameNode->GetTag()) {
                return parentFrameNode;
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
            TAG_LOGI(AceLogTag::ACE_DRAG, "Cannot find targetNodes.");
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
        UpdateDragStyle(DragCursorStyleCore::MOVE);
        return;
    }
    for (const auto& it : summaryMap_) {
        if (dragFrameNodeAllowDrop.find(it.first) == dragFrameNodeAllowDrop.end()) {
            UpdateDragStyle(DragCursorStyleCore::FORBIDDEN);
            return;
        }
    }
    UpdateDragStyle(isCopy ? DragCursorStyleCore::COPY : DragCursorStyleCore::MOVE);
}

void DragDropManager::UpdateDragStyle(const DragCursorStyleCore& dragStyle)
{
    if (dragStyle != dragCursorStyleCore_) {
        dragCursorStyleCore_ = dragStyle;
        InteractionInterface::GetInstance()->UpdateDragStyle(dragCursorStyleCore_);
    }
}
#endif // ENABLE_DRAG_FRAMEWORK

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
            continue;
        }
        auto pattern = frameNode->GetPattern<Pattern>();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnDragStatusCallback(dragEventType, notifyEvent);
    }
}

void DragDropManager::NotifyDragFrameNode(
    const Point& point, const DragEventType& dragEventType, const DragRet& dragRet)
{
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    UpdateNotifyDragEvent(notifyEvent, point, dragEventType);
    notifyEvent->SetResult(dragRet);
    NotifyDragRegisterFrameNode(nodesForDragNotify_, dragEventType, notifyEvent);
}

void DragDropManager::OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    NotifyDragFrameNode(point, DragEventType::START);
    CHECK_NULL_VOID(frameNode);
    preTargetFrameNode_ = frameNode;
    draggedFrameNode_ = preTargetFrameNode_;
}

void DragDropManager::OnDragStart(const Point& point)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    NotifyDragFrameNode(point, DragEventType::START);
}

void DragDropManager::PrintDragFrameNode(const Point& point, const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);
    if (SystemProperties::GetDebugEnabled()) {
        if (preTargetFrameNode_) {
            TAG_LOGI(AceLogTag::ACE_DRAG,"Drag Position is %{public}f and %{public}f, "
                "PreTargetFrameNode is %{public}s, depth is %{public}d, "
                "New find targetNode is %{public}s, depth is %{public}d.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()),
                preTargetFrameNode_->GetTag().c_str(), preTargetFrameNode_->GetDepth(),
                dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
        } else {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Drag Position is %{public}f and %{public}f, "
                "PreTargetFrameNode is nullptr, "
                "New find targetNode is %{public}s, depth is %{public}d.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()),
                dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
        }
    }
}

void DragDropManager::OnDragMoveOut(const PointerEvent& pointerEvent, const std::string& extraInfo)
{
    Point point  = pointerEvent.GetPoint();
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    SetIsWindowConsumed(false);
#endif // ENABLE_DRAG_FRAMEWORK
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(Point(-1, -1));
    if (preTargetFrameNode_) {
        FireOnDragEvent(preTargetFrameNode_, point, DragEventType::LEAVE, extraInfo_);
        preTargetFrameNode_ = nullptr;
    }
}

void DragDropManager::OnDragMove(const PointerEvent& pointerEvent, const std::string& extraInfo)
{
    Point point  = pointerEvent.GetPoint();
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    SetIsWindowConsumed(false);
#endif // ENABLE_DRAG_FRAMEWORK
    SubwindowManager::GetInstance()->UpdateHideMenuOffsetNG(OffsetF(static_cast<float>(point.GetX()),
        static_cast<float>(point.GetY())));
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(point);
    auto dragFrameNode = FindDragFrameNodeByPosition(
        static_cast<float>(point.GetX()), static_cast<float>(point.GetY()), DragType::COMMON, false);
    if (!dragFrameNode) {
        if (preTargetFrameNode_) {
            FireOnDragEvent(preTargetFrameNode_, point, DragEventType::LEAVE, extraInfo);
            preTargetFrameNode_ = nullptr;
        }

#ifdef ENABLE_DRAG_FRAMEWORK
        if (!isMouseDragged_ || isDragWindowShow_) {
            UpdateDragStyle(DragCursorStyleCore::MOVE);
        }
#endif // ENABLE_DRAG_FRAMEWORK
        return;
    }

    if (V2::UI_EXTENSION_COMPONENT_ETS_TAG == dragFrameNode->GetTag()) {
        auto pattern = dragFrameNode->GetPattern<Pattern>();
        pattern->HandleDragEvent(pointerEvent);
        return;
    }

    if (dragFrameNode == preTargetFrameNode_) {
        FireOnDragEvent(dragFrameNode, point, DragEventType::MOVE, extraInfo);
        return;
    }

    if (preTargetFrameNode_) {
        auto preRect = preTargetFrameNode_->GetTransformRectRelativeToWindow();
        if (!preRect.IsInnerRegion(PointF(static_cast<float>(point.GetX()), static_cast<float>(point.GetY())))) {
            PrintDragFrameNode(point, dragFrameNode);
            FireOnDragEvent(preTargetFrameNode_, point, DragEventType::LEAVE, extraInfo);
        }
    }
    PrintDragFrameNode(point, dragFrameNode);
    FireOnDragEvent(dragFrameNode, point, DragEventType::ENTER, extraInfo);
    preTargetFrameNode_ = dragFrameNode;
}

void DragDropManager::OnDragEnd(const PointerEvent& pointerEvent, const std::string& extraInfo)
{
    Point point  = pointerEvent.GetPoint();
    dragDropState_ = DragDropMgrState::IDLE;
    preTargetFrameNode_ = nullptr;
    hasNotifiedTransformation_ = false;
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            return;
        }
    }
    if (isDragCancel_) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "DragDropManager is dragCancel, finish drag. WindowId is %{public}d.",
                container->GetWindowId());
        }
        InteractionInterface::GetInstance()->SetDragWindowVisible(false);
        DragDropRet dragDropRet { DragRet::DRAG_CANCEL, false, container->GetWindowId() };
        InteractionInterface::GetInstance()->StopDrag(dragDropRet);
        NotifyDragFrameNode(point, DragEventType::DROP, DragRet::DRAG_CANCEL);
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
            TAG_LOGI(AceLogTag::ACE_DRAG, "Position is %{public}f and %{public}f. TargetNode is %{public}s.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()),
                dragFrameNode->GetTag().c_str());
        } else {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Position is %{public}f and %{public}f. TargetNode is nullptr.",
                static_cast<float>(point.GetX()), static_cast<float>(point.GetY()));
        }
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    if (!dragFrameNode) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGW(AceLogTag::ACE_DRAG,
                "DragDropManager onDragEnd, not find drop target, stop drag. WindowId is %{public}d.",
                container->GetWindowId());
        }
        DragDropRet dragDropRet { DragRet::DRAG_FAIL, isMouseDragged_, container->GetWindowId() };
        InteractionInterface::GetInstance()->StopDrag(dragDropRet);
        NotifyDragFrameNode(point, DragEventType::DROP, DragRet::DRAG_FAIL);
        summaryMap_.clear();
        parentHitNodes_.clear();
        return;
    }
#endif // ENABLE_DRAG_FRAMEWORK

    CHECK_NULL_VOID(dragFrameNode);
    if (V2::UI_EXTENSION_COMPONENT_ETS_TAG == dragFrameNode->GetTag()) {
        auto pattern = dragFrameNode->GetPattern<Pattern>();
        pattern->HandleDragEvent(pointerEvent);
        return;
    }

    auto eventHub = dragFrameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    UpdateDragEvent(event, point);
    auto extraParams = eventHub->GetDragExtraParams(extraInfo_, point, DragEventType::DROP);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, event, extraParams);
    eventHub->HandleInternalOnDrop(event, extraParams);
    ClearVelocityInfo();
#ifdef ENABLE_DRAG_FRAMEWORK
    SetIsDragged(false);
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "DragDropManager finish drop, start do drop animation. UseCustomAnimation is %{public}d."
            " WindowId is %{public}d.", event->IsUseCustomAnimation(), container->GetWindowId());
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragResult = event->GetResult();
    auto useCustomAnimation = event->IsUseCustomAnimation();
    auto windowId = container->GetWindowId();
    pipeline->SetDragCleanTask([dragResult, useCustomAnimation, isMouseDragged = isMouseDragged_, windowId]() {
        InteractionInterface::GetInstance()->SetDragWindowVisible(!useCustomAnimation);
        DragDropRet dragDropRet { dragResult, useCustomAnimation, windowId };
        InteractionInterface::GetInstance()->StopDrag(dragDropRet);
    });
    NotifyDragFrameNode(point, DragEventType::DROP, event->GetResult());
    dragFrameNode->MarkDirtyNode();
    summaryMap_.clear();
    parentHitNodes_.clear();
#endif // ENABLE_DRAG_FRAMEWORK
}

#ifdef ENABLE_DRAG_FRAMEWORK
void DragDropManager::RequireSummary()
{
    std::map<std::string, int64_t> summary;
    int32_t ret = InteractionInterface::GetInstance()->GetDragSummary(summary);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "RequireSummary: Interaction GetSummary failed: %{public}d", ret);
    }
    std::string extraInfo;
    ret = InteractionInterface::GetInstance()->GetDragExtraInfo(extraInfo);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "GetExtraInfo: Interaction GetExtraInfo failed: %{public}d", ret);
    }
    previewRect_ = Rect(-1, -1, -1, -1);
    extraInfo_ = extraInfo;
    summaryMap_ = summary;
    UpdateDragStyle();
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
        ShadowOffsetData shadowOffsetData { -1, -1, -1, -1 };
        int ret = InteractionInterface::GetInstance()->GetShadowOffset(shadowOffsetData);
        if (ret == 0) {
            previewRect_ = Rect(
                shadowOffsetData.offsetX,
                shadowOffsetData.offsetY,
                shadowOffsetData.width,
                shadowOffsetData.height);
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
    if (!eventHub->HasOnDrop() && !eventHub->HasOnItemDrop() && !eventHub->HasCustomerOnDrop()) {
        return;
    }
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

    FireOnEditableTextComponent(frameNode, type);
    FireOnDragEventWithDragType(eventHub, type, event, extraParams);

#ifdef ENABLE_DRAG_FRAMEWORK
    if (isMouseDragged_ && !isDragWindowShow_) {
        return;
    }
    if (event->GetResult() == DragRet::ENABLE_DROP) {
        if (event->IsCopy()) {
            UpdateDragStyle(DragCursorStyleCore::COPY);
        } else {
            UpdateDragStyle(DragCursorStyleCore::MOVE);
        }
    } else if (event->GetResult() == DragRet::DISABLE_DROP) {
        UpdateDragStyle(DragCursorStyleCore::FORBIDDEN);
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

    auto windowScale = GetSmallWindowScale();
    auto windowX = globalX * windowScale;
    auto windowY = globalY * windowScale;
    UpdateDragWindowPosition(static_cast<int32_t>(windowX), static_cast<int32_t>(windowY));

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(pipeline->ConvertPxToVp(Dimension(windowX, DimensionUnit::PX)));
    itemDragInfo.SetY(pipeline->ConvertPxToVp(Dimension(windowY, DimensionUnit::PX)));

    // use -1 for grid item not in eventGrid
    auto getDraggedIndex = [draggedGrid = draggedGridFrameNode_, draggedIndex, dragType](
                               const RefPtr<FrameNode>& eventGrid) {
        return (dragType == DragType::GRID) ? (eventGrid == draggedGrid ? draggedIndex : -1) : draggedIndex;
    };

    auto dragFrameNode = FindDragFrameNodeByPosition(windowX, windowY, dragType, false);
    if (!dragFrameNode) {
        if (preGridTargetFrameNode_) {
            FireOnItemDragEvent(preGridTargetFrameNode_, dragType, itemDragInfo, DragEventType::LEAVE,
                getDraggedIndex(preGridTargetFrameNode_));
            preGridTargetFrameNode_ = nullptr;
        }
        return;
    }

    if (dragFrameNode == preGridTargetFrameNode_) {
        int32_t insertIndex = GetItemIndex(dragFrameNode, dragType, windowX, windowY);
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

float DragDropManager::GetSmallWindowScale() const
{
    float scale = 1.0f;
#ifdef ENABLE_DRAG_FRAMEWORK
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, scale);
    scale = container->GetSmallWindowScale();
#endif // ENABLE_DRAG_FRAMEWORK
    return scale;
}

void DragDropManager::OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType)
{
    dragDropState_ = DragDropMgrState::IDLE;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowScale = GetSmallWindowScale();
    auto windowX = globalX * windowScale;
    auto windowY = globalY * windowScale;

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(pipeline->ConvertPxToVp(Dimension(windowX, DimensionUnit::PX)));
    itemDragInfo.SetY(pipeline->ConvertPxToVp(Dimension(windowY, DimensionUnit::PX)));

    auto dragFrameNode = FindDragFrameNodeByPosition(windowX, windowY, dragType, true);
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
        int32_t insertIndex = GetItemIndex(dragFrameNode, dragType, windowX, windowY);
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
    dragDropState_ = DragDropMgrState::IDLE;
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
    SetIsDragged(false);
    SetIsDragWindowShow(false);
    previewRect_ = Rect(-1, -1, -1, -1);
    isMouseDragged_ = false;
    currentId_ = -1;
}

void DragDropManager::CancelItemDrag()
{
    if (draggedGridFrameNode_) {
        auto listEventHub = draggedGridFrameNode_->GetEventHub<ListEventHub>();
        if (listEventHub) {
            listEventHub->HandleOnItemDragCancel();
            return;
        }
        auto gridEventHub = draggedGridFrameNode_->GetEventHub<GridEventHub>();
        if (gridEventHub) {
            gridEventHub->HandleOnItemDragCancel();
            return;
        }
    }
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
        if (dragEventType != DragEventType::DROP) {
            notifyEvent->SetVelocity(velocityTracker_.GetVelocity());
        }
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
    event->SetVelocity(velocityTracker_.GetVelocity());
#ifdef ENABLE_DRAG_FRAMEWORK
    std::string udKey;
    InteractionInterface::GetInstance()->GetUdKey(udKey);
    if (udKey.empty()) {
        event->SetIsGetDataSuccess(false);
    } else {
        event->SetUdKey(udKey);
    }
    int ret = InteractionInterface::GetInstance()->AddPrivilege();
    if (ret != 0 && SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Interaction AddPrivilege in DragEnd with code:%{public}d", ret);
    }
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->CreateUnifiedData();
    ret = UdmfClient::GetInstance()->GetData(udData, udKey);
    if (ret != 0) {
        event->SetIsGetDataSuccess(false);
    } else {
        event->SetIsGetDataSuccess(true);
    }
    auto unifiedData = udData;
    event->SetData(unifiedData);
    RequireSummary();
    event->SetSummary(summaryMap_);
    ShadowOffsetData shadowOffsetData { -1, -1, -1, -1 };
    ret = InteractionInterface::GetInstance()->GetShadowOffset(shadowOffsetData);
    if (ret == 0) {
        previewRect_ = Rect(
            point.GetX() + shadowOffsetData.offsetX,
            point.GetY() + shadowOffsetData.offsetY,
            shadowOffsetData.width,
            shadowOffsetData.height);
        event->SetPreviewRect(previewRect_);
    } else {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Interaction GetShadowOffset in DragEnd with code:%{public}d", ret);
        }
        event->SetPreviewRect(previewRect_ + Offset(point.GetX(), point.GetY()));
    }
#endif // ENABLE_DRAG_FRAMEWORK
}

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

#ifdef ENABLE_DRAG_FRAMEWORK
bool DragDropManager::IsMsdpDragging() const
{
    DragState dragState;
    InteractionInterface::GetInstance()->GetDragState(dragState);
    return dragState == DragState::START;
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

#ifdef ENABLE_DRAG_FRAMEWORK
bool DragDropManager::GetDragPreviewInfo(const RefPtr<OverlayManager>& overlayManager,
    DragPreviewInfo& dragPreviewInfo)
{
    if (!overlayManager->GetHasPixelMap()) {
        return false;
    }
    auto imageNode = overlayManager->GetPixelMapContentNode();
    if (!imageNode) {
        return false;
    }
    double maxWidth = GridSystemManager::GetInstance().GetMaxWidthWithColumnType(GridColumnType::DRAG_PANEL);
    auto width = imageNode->GetGeometryNode()->GetFrameRect().Width();
    dragPreviewInfo.scale = static_cast<float>(imageNode->GetPreviewScaleVal());
    dragPreviewInfo.height = imageNode->GetGeometryNode()->GetFrameRect().Height();
    dragPreviewInfo.width = static_cast<double>(width);
    dragPreviewInfo.maxWidth = maxWidth;
    dragPreviewInfo.imageNode = imageNode;
    return true;
}

bool DragDropManager::IsNeedScaleDragPreview()
{
    return info_.scale > 0 && info_.scale < 1.0f;
}

double DragDropManager::CalcDragPreviewDistanceWithPoint(
    const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info)
{
    CHECK_NULL_RETURN(info.imageNode, 0.0);
    auto nodeOffset = info.imageNode->GetTransformRelativeOffset();
    auto renderContext = info.imageNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, 0.0);
    auto width = renderContext->GetPaintRectWithTransform().Width();
    nodeOffset.SetX(nodeOffset.GetX() + width / 2);
    nodeOffset.SetY(nodeOffset.GetY() + preserverHeight.ConvertToPx());
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        auto windowOffset = pipeline->GetWindow()->GetCurrentWindowRect().GetOffset();
        x += windowOffset.GetX();
        y += windowOffset.GetY();
    }
    return sqrt(pow(nodeOffset.GetX() - x, 2) + pow(nodeOffset.GetY() - y, 2));
}

Offset DragDropManager::CalcDragMoveOffset(
    const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info)
{
    CHECK_NULL_RETURN(info.imageNode, Offset(0.0f, 0.0f));
    auto originPoint = info.imageNode->GetOffsetRelativeToWindow();
    if (IsNeedScaleDragPreview()) {
        originPoint.SetX(originPoint.GetX() + 0.5 * (1 - info.scale) * info.width + info.maxWidth / 2);
        originPoint.SetY(originPoint.GetY() + 0.5 * (1 - info.scale) * info.height + preserverHeight.ConvertToPx());
    }
    Offset newOffset { x - originPoint.GetX(), y - originPoint.GetY() };
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        auto windowOffset = pipeline->GetWindow()->GetCurrentWindowRect().GetOffset();
        newOffset.SetX(newOffset.GetX() + windowOffset.GetX());
        newOffset.SetY(newOffset.GetY() + windowOffset.GetY());
    }
    return newOffset;
}

void DragDropManager::DoDragMoveAnimate(const PointerEvent& pointerEvent)
{
    if (!IsNeedScaleDragPreview()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    auto containerId = Container::CurrentId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
    CHECK_NULL_VOID(subwindow);
    auto overlayManager = subwindow->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    Dimension preserveHeight = 8.0_vp;
    auto x = pointerEvent.GetPoint().GetX();
    auto y = pointerEvent.GetPoint().GetY();
    Offset newOffset = CalcDragMoveOffset(preserveHeight, x, y, info_);
    AnimationOption option;
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.347f, 0.99f, 0.0f);
    constexpr int32_t animateDuration = 30;
    option.SetCurve(curve);
    option.SetDuration(animateDuration);
    auto distance = CalcDragPreviewDistanceWithPoint(preserveHeight, x, y, info_);
    option.SetOnFinishEvent([distance, overlayManager, pipeline]() {
        constexpr decltype(distance) MAX_DIS = 5.0;
        if (distance < MAX_DIS) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
            if (overlayManager->GetHasPixelMap()) {
                SubwindowManager::GetInstance()->HidePreviewNG();
                overlayManager->RemovePixelMap();
            }
        }
    });
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationUtils::Animate(
        option,
        [renderContext, localPoint = newOffset]() {
            renderContext->UpdateTransformTranslate({ localPoint.GetX(), localPoint.GetY(), 0.0f });
        },
        option.GetOnFinishEvent());
}

void DragDropManager::DoDragStartAnimation(const RefPtr<OverlayManager>& overlayManager, const GestureEvent& event)
{
    CHECK_NULL_VOID(overlayManager);
    if (!(GetDragPreviewInfo(overlayManager, info_)) || !IsNeedScaleDragPreview()) {
        return;
    }
    Dimension preserveHeight = 8.0_vp;
    Offset newOffset = CalcDragMoveOffset(preserveHeight,
        static_cast<int32_t>(event.GetGlobalLocation().GetX()), static_cast<int32_t>(event.GetGlobalLocation().GetY()),
        info_);
    AnimationOption option;
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.347f, 0.99f, 0.0f);
    constexpr int32_t animateDuration = 30;
    option.SetCurve(curve);
    option.SetDuration(animateDuration);
    auto renderContext = info_.imageNode->GetRenderContext();
    AnimationUtils::Animate(
        option,
        [renderContext, scale = info_.scale, newOffset]() {
            renderContext->UpdateTransformScale({ scale, scale });
            renderContext->UpdateTransformTranslate({ newOffset.GetX(), newOffset.GetY(), 0.0f });
        },
        option.GetOnFinishEvent());
}
#endif
void DragDropManager::FireOnEditableTextComponent(const RefPtr<FrameNode>& frameNode,
    DragEventType type)
{
    auto frameTag = frameNode->GetTag();
    if (!IsEditableTextComponent(frameTag)) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_DRAG,
                "This frame node is not editable text component %{public}s", frameTag.c_str());
        }
        return;
    }

    if (type != DragEventType::ENTER && type != DragEventType::LEAVE) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "It is an invalid drag type %{public}d", type);
        }
        return;
    }

    if (type == DragEventType::LEAVE) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "The current control has been dragged away.");
        hasNotifiedTransformation_ = false;
        return;
    }

    if (hasNotifiedTransformation_) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Coordinates have been transformed.");
        return;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    auto ret = InteractionInterface::GetInstance()->EnterTextEditorArea(true);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Fail to notify entering text editor erea.");
        return;
    }
#endif // ENABLE_DRAG_FRAMEWORK
    hasNotifiedTransformation_ = true;
}

} // namespace OHOS::Ace::NG
