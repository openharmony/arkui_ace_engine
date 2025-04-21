/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/geometry/point.h"
#include "base/geometry/rect.h"
#include "base/log/ace_trace.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
int64_t g_proxyId = 0;
constexpr Dimension PRESERVE_HEIGHT = 8.0_vp;
constexpr float FIRST_PIXELMAP_OPACITY = 0.6f;
constexpr float SECOND_PIXELMAP_OPACITY = 0.3f;
constexpr float FIRST_PIXELMAP_ANGLE = 8.0f;
constexpr float SECOND_PIXELMAP_ANGLE = -8.0f;
constexpr int32_t FIRST_GATHER_PIXEL_MAP = 1;
constexpr int32_t SECOND_GATHER_PIXEL_MAP = 2;
constexpr int32_t SQUARE_NUMBER = 2;
constexpr float TOUCH_DRAG_PIXELMAP_SCALE = 1.05f;
constexpr int32_t MAX_RETRY_TIMES = 3;
constexpr int32_t MAX_RETRY_DURATION = 800;
constexpr float MOVE_DISTANCE_LIMIT = 20.0f;
constexpr uint64_t MOVE_TIME_LIMIT = 6L;
constexpr float MAX_DISTANCE_TO_PRE_POINTER = 3.0f;
constexpr float DEFAULT_SPRING_RESPONSE = 0.347f;
constexpr float MIN_SPRING_RESPONSE = 0.05f;
constexpr float DEL_SPRING_RESPONSE = 0.005f;
constexpr float MIN_UI_EXTENSION_BOUNDARY_DISTANCE = 5.0f;
constexpr float MIN_FOLDER_SUBWINDOW_BOUNDARY_DISTANCE = 5.0f;
constexpr int32_t RESERVED_DEVICEID_1 = 0xAAAAAAFF;
constexpr int32_t RESERVED_DEVICEID_2 = 0xAAAAAAFE;
constexpr uint32_t TASK_DELAY_TIME = 5 * 1000;
constexpr uint32_t DROP_DELAY_TIME = 2 * 1000;
constexpr double DEVICE_TYPE_UNKOWN = 0.0;
constexpr double DEVICE_TYPE_SMALL = 600.0;
constexpr double DEVICE_TYPE_MEDIUM = 840.0;
constexpr int32_t SCALE_TYPE_FIRST = 2;
constexpr int32_t SCALE_TYPE_SECOND = 3;
constexpr int32_t SCALE_TYPE_THIRD = 4;
const RefPtr<InterpolatingSpring> DRAG_TRANSITION_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 380.0f, 34.0f);
} // namespace

RefPtr<RenderContext> GetMenuRenderContextFromMenuWrapper(const RefPtr<FrameNode>& menuWrapperNode)
{
    CHECK_NULL_RETURN(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menuNode, nullptr);
    return menuNode->GetRenderContext();
}

RefPtr<FrameNode> GetMenuWrapperNodeFromDrag()
{
    auto pipelineContext = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto mainDragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(mainDragDropManager, nullptr);
    return mainDragDropManager->GetMenuWrapperNode();
}

DragDropManager::DragDropManager()
{
    if (DragDropGlobalController::GetInstance().IsAlreadyGetAppGlobalDrag()) {
        return;
    }
    bool state = false;
    auto result = InteractionInterface::GetInstance()->GetAppDragSwitchState(state);
    if (result != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "get app drag switch state failed!");
        return;
    }
    DragDropGlobalController::GetInstance().SetIsAppGlobalDragEnabled(state);
}

const Point DragDropManager::GetDragMoveLastPointByCurrentPointer(int32_t pointerId)
{
    return fingerPointInfo_[pointerId];
}

void DragDropManager::UpdatePointInfoForFinger(int32_t pointerId, Point point)
{
    fingerPointInfo_[pointerId] = point;
}

void DragDropManager::SetDelayDragCallBack(const std::function<void()>& cb) noexcept
{
    DragDropGlobalController::GetInstance().SetAsyncDragCallback(cb);
}

void DragDropManager::ExecuteDeadlineTimer()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    taskScheduler->PostDelayedTask(
        [weakManager = WeakClaim(this)]() {
            auto dragDropManager = weakManager.Upgrade();
            CHECK_NULL_VOID(dragDropManager);
            if (DragDropGlobalController::GetInstance().GetAsyncDragCallback()) {
                DragDropGlobalController::GetInstance().GetAsyncDragCallback()();
            }
            dragDropManager->RemoveDeadlineTimer();
        },
        TaskExecutor::TaskType::UI, TASK_DELAY_TIME, "ArkUIDragDeadlineTimer");
}

void DragDropManager::RemoveDeadlineTimer()
{
    DragDropGlobalController::GetInstance().SetAsyncDragCallback(nullptr);
    DragDropGlobalController::GetInstance().SetDragStartRequestStatus(DragStartRequestStatus::READY);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    taskScheduler->RemoveTask(TaskExecutor::TaskType::UI, "ArkUIDragDeadlineTimer");
}

void DragDropManager::HandleSyncOnDragStart(DragStartRequestStatus dragStartRequestStatus)
{
    if (dragStartRequestStatus == DragStartRequestStatus::WAITING) {
        ExecuteDeadlineTimer();
        DragDropGlobalController::GetInstance().SetDragStartRequestStatus(dragStartRequestStatus);
    }
    if (dragStartRequestStatus == DragStartRequestStatus::READY &&
        DragDropGlobalController::GetInstance().GetAsyncDragCallback()) {
        DragDropGlobalController::GetInstance().SetDragStartRequestStatus(dragStartRequestStatus);
        DragDropGlobalController::GetInstance().GetAsyncDragCallback()();
        RemoveDeadlineTimer();
    }
}

RefPtr<DragDropProxy> DragDropManager::CreateAndShowItemDragOverlay(
    const RefPtr<PixelMap>& pixelMap, const GestureEvent& info, const RefPtr<EventHub>& eventHub)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    // create Image for drag
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(imagePattern, nullptr);
    imagePattern->SetSyncLoad(true);
    auto prop = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(prop, nullptr);
    prop->UpdateAutoResize(false);
    prop->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(pixelMap->GetWidth()), NG::CalcLength(pixelMap->GetHeight()));
    prop->UpdateUserDefinedIdealSize(targetSize);
    auto renderProp = imageNode->GetPaintProperty<ImageRenderProperty>();
    renderProp->UpdateImageInterpolation(ImageInterpolation::HIGH);
    imageNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    imageNode->SetLayoutDirtyMarked(true);
    imageNode->SetActive(true);
    auto context = imageNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(imageNode);
    }
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageContext, nullptr);
    imageContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(info.GetGlobalPoint().GetX() - pixelMap->GetWidth() / 2), // 2: Average factor.
            Dimension(info.GetGlobalPoint().GetY() - pixelMap->GetHeight() / 2)));             // 2: Average factor.
    imageContext->OnModifyDone();

    AddItemDrag(imageNode, eventHub);

    itemDragOverlayNode_ = imageNode;
    SetIsDragged(true);
    isDragCancel_ = false;
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

RefPtr<DragDropProxy> DragDropManager::CreateAndShowItemDragOverlay(
    const RefPtr<UINode>& customNode, const GestureEvent& info, const RefPtr<EventHub>& eventHub)
{
    auto frameNode = DynamicCast<FrameNode>(customNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameSize();
    renderContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(info.GetGlobalPoint().GetX() - frameRect.Width() / 2), // 2: Average factor.
            Dimension(info.GetGlobalPoint().GetY() - frameRect.Height() / 2)));             // 2: Average factor.
    renderContext->OnModifyDone();
    AddItemDrag(frameNode, eventHub);
    itemDragOverlayNode_ = frameNode;
    SetIsDragged(true);
    isDragCancel_ = false;
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

int32_t DragDropManager::GetWindowId()
{
    auto windowId = -1;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, windowId);

    if (!container->IsSceneBoardEnabled()) {
        isDragWindowSubWindow_ = false;
        return windowId;
    }

    if (!container->IsMainWindow()) {
        // The window manager currently does not support creating child windows within child windows,
        // so the root main window is used here
        container = Container::GetContainer(CONTAINER_ID_DIVIDE_SIZE);
        CHECK_NULL_RETURN(container, windowId);
        if (!container->IsMainWindow()) {
            isDragWindowSubWindow_ = false;
            return windowId;
        }
    }

    windowId = static_cast<int32_t>(container->GetWindowId());
    isDragWindowSubWindow_ = true;

    return windowId;
}

RefPtr<FrameNode> DragDropManager::CreateDragRootNode(const RefPtr<UINode>& customNode)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);

    auto rootNode = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode->SetActive(true);
    rootNode->SetHostRootId(pipeline->GetInstanceId());
    rootNode->SetHostPageId(-1);
    rootNode->AddChild(customNode);
    rootNode->AttachToMainTree(false, AceType::RawPtr(pipeline));
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    pipeline->FlushUITasks();
    return rootNode;
}

void DragDropManager::AddItemDrag(const RefPtr<FrameNode>& frameNode, const RefPtr<EventHub>& eventHub)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto rootNode = pipeline->GetRootElement();
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        auto host = eventHub->GetFrameNode();
        CHECK_NULL_VOID(host);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        rootNode = DynamicCast<FrameNode>(overlayManager->FindWindowScene(host));
    }
    CHECK_NULL_VOID(rootNode);
    frameNode->MountToParent(rootNode);
    frameNode->OnMountToParentDone();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void DragDropManager::RemoveItemDrag()
{
    CHECK_NULL_VOID(itemDragOverlayNode_);
    auto rootNode = itemDragOverlayNode_->GetParent();
    CHECK_NULL_VOID(rootNode);
    rootNode->RemoveChild(itemDragOverlayNode_);
    rootNode->RebuildRenderContextTree();
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

void DragDropManager::UpdateItemDragPosition(int32_t globalX, int32_t globalY)
{
    CHECK_NULL_VOID(itemDragOverlayNode_);
    auto rect = itemDragOverlayNode_->GetTransformRectRelativeToWindow();
    auto pipeline = itemDragOverlayNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    const Rect windowRect = pipeline->GetDisplayWindowRectInfo();
    auto maxX = static_cast<float>(windowRect.Width() - rect.Width());
    auto maxY = static_cast<float>(windowRect.Height() - rect.Height());
    auto renderContext = itemDragOverlayNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition(
        OffsetT<Dimension>(Dimension(std::min(std::max(globalX - rect.Width() / 2, 0.0f), maxX)), // 2: Average factor.
            Dimension(std::min(std::max(globalY - rect.Height() / 2, 0.0f), maxY))));             // 2: Average factor.
    renderContext->OnModifyDone();
}

void DragDropManager::HideDragPreviewOverlay()
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemovePixelMap();
    manager->RemoveGatherNode();
    manager->RemoveDragPixelMap();
    SubwindowManager::GetInstance()->HidePreviewNG();
}

void DragDropManager::HideDragPreviewWindow(int32_t containerId)
{
    auto overlayManager = GetDragAnimationOverlayManager(containerId);
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemovePixelMap();
    overlayManager->RemoveGatherNode();
    overlayManager->RemoveDragPixelMap();
    SubwindowManager::GetInstance()->HidePreviewNG();
}

void DragDropManager::HideSubwindowDragNode()
{
    auto subwindowOverlayManager = subwindowOverlayManager_.Upgrade();
    CHECK_NULL_VOID(subwindowOverlayManager);
    subwindowOverlayManager->RemovePixelMap();
    subwindowOverlayManager->RemoveGatherNode();
    subwindowOverlayManager->RemoveDragPixelMap();
    subwindowOverlayManager_ = nullptr;
}

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
            auto eventHub = parentFrameNode->GetOrCreateEventHub<EventHub>();
            if (!eventHub) {
                continue;
            }
            if ((eventHub->HasOnDrop()) || (eventHub->HasOnItemDrop()) || (eventHub->HasCustomerOnDrop())) {
                return parentFrameNode;
            }
            if ((V2::UI_EXTENSION_COMPONENT_ETS_TAG == parentFrameNode->GetTag() ||
                V2::EMBEDDED_COMPONENT_ETS_TAG == parentFrameNode->GetTag()) &&
                (!IsUIExtensionShowPlaceholder(parentFrameNode))) {
                return parentFrameNode;
            }
        }
    }
    return nullptr;
}

bool DragDropManager::CheckFrameNodeCanDrop(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if ((eventHub->HasOnDrop()) || (eventHub->HasOnItemDrop()) || (eventHub->HasCustomerOnDrop())) {
        return true;
    }
    if ((V2::UI_EXTENSION_COMPONENT_ETS_TAG == node->GetTag() ||
        V2::EMBEDDED_COMPONENT_ETS_TAG == node->GetTag()) &&
        (!IsUIExtensionShowPlaceholder(node))) {
        return true;
    }

    return false;
}

RefPtr<FrameNode> DragDropManager::FindTargetDropNode(const RefPtr<UINode> parentNode, PointF localPoint)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
    CHECK_NULL_RETURN(parentFrameNode, nullptr);
    if (!parentFrameNode->IsActive() || !parentFrameNode->IsVisible()) {
        return nullptr;
    }
    auto renderContext = parentFrameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    FrameNode::MapPointTo(localPoint, parentFrameNode->GetOrRefreshMatrixFromCache().revertMatrix);
    auto subLocalPoint = localPoint - paintRect.GetOffset();

    auto children = parentFrameNode->GetFrameChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto child = iter->Upgrade();
        if (child == nullptr) {
            continue;
        }
        auto childNode = AceType::DynamicCast<UINode>(child);
        auto childFindResult = FindTargetDropNode(childNode, subLocalPoint);
        if (childFindResult) {
            return childFindResult;
        }
    }

    if (paintRect.IsInRegion(localPoint)) {
        if (parentFrameNode->GetDragHitTestBlock()) {
            return parentFrameNode;
        }
        if (CheckFrameNodeCanDrop(parentFrameNode)) {
            return parentFrameNode;
        }
    }
    return nullptr;
}

RefPtr<FrameNode> DragDropManager::FilterSubwindowDragRootNode(const RefPtr<FrameNode>& node)
{
    auto rootNode = node;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, rootNode);
    auto containerId = container->GetInstanceId();
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(pipeline, rootNode);
    if (isReDragStart_ && !DragDropFuncWrapper::IsExpandDisplay(pipeline) && containerId >= MIN_SUBCONTAINER_ID) {
        rootNode = pipeline->GetRootElement();
    }
    return rootNode;
}

RefPtr<FrameNode> DragDropManager::FindDragFrameNodeByPosition(float globalX, float globalY,
    const RefPtr<FrameNode>& node)
{
    auto rootNode = node;
    if (!rootNode) {
        auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, nullptr);
        rootNode = pipeline->GetRootElement();
    }

    auto result = FindTargetDropNode(rootNode, {globalX, globalY});
    if (result) {
        if (CheckFrameNodeCanDrop(result)) {
            return result;
        }
    }
    return nullptr;
}

bool DragDropManager::CheckDragDropProxy(int64_t id) const
{
    return currentId_ == id;
}

void DragDropManager::UpdateDragAllowDrop(
    const RefPtr<FrameNode>& dragFrameNode, const DragBehavior dragBehavior, const int32_t eventId, bool isCapi)
{
    if (!IsDropAllowed(dragFrameNode)) {
        // simplified specifications for drag cursor style, no longer showing forbidden drag cursor
        UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
        return;
    }

    // drop allowed
    CHECK_NULL_VOID(dragFrameNode);
    const auto& dragFrameNodeAllowDrop = dragFrameNode->GetAllowDrop();
    // special handling for no drag data present situation, always show as move
    // For CAPI ,no ENABLE_DROP and DISABLE_DROP state, skip the judgment and consider it allowed to drop into. Continue
    // to set dragBehavior.
    if (!isCapi && (dragFrameNodeAllowDrop.empty() || summaryMap_.empty())) {
        UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
        return;
    }

    //other case, check drag behavior
    switch (dragBehavior) {
        case DragBehavior::UNKNOWN: {
            // the application does not config the drag behavior, use move when moving within
            // draggedFrameNode or frameNode is disabled, otherwise use copy
            auto eventHub = dragFrameNode->GetOrCreateEventHub<EventHub>();
            if (draggedFrameNode_ == dragFrameNode || !(eventHub && eventHub->IsEnabled()) ||
                CheckExtraSituation(dragFrameNode)) {
                UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
            } else {
                UpdateDragStyle(DragCursorStyleCore::COPY, eventId);
            }
            break;
        }
        case DragBehavior::MOVE: {
            UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
            break;
        }
        case DragBehavior::COPY: {
            UpdateDragStyle(DragCursorStyleCore::COPY, eventId);
            break;
        }
        default: {
            UpdateDragStyle(DragCursorStyleCore::COPY, eventId);
            break;
        }
    }
}

bool DragDropManager::CheckExtraSituation(const RefPtr<FrameNode>& dragFrameNode) const
{
    return CheckInRichEditor(dragFrameNode);
}

bool DragDropManager::CheckInRichEditor(const RefPtr<FrameNode>& dragFrameNode) const
{
    CHECK_NULL_RETURN(dragFrameNode && draggedFrameNode_, false);
    auto parent = draggedFrameNode_->GetAncestorNodeOfFrame(false);
    CHECK_NULL_RETURN(parent && parent->GetTag() == V2::RICH_EDITOR_ETS_TAG, false);
    return dragFrameNode == parent;
}

void DragDropManager::UpdateDragStyle(const DragCursorStyleCore& dragStyle, int32_t eventId)
{
    if (dragStyle != dragCursorStyleCore_) {
        ACE_SCOPED_TRACE("drag: update drag style %d", dragStyle);
        TAG_LOGI(
            AceLogTag::ACE_DRAG, "Update DragStyle to %{public}d, pointerEventId: %{public}d.", dragStyle, eventId);
        auto ret = InteractionInterface::GetInstance()->UpdateDragStyle(dragStyle, eventId);
        if (ret != 0) {
            TAG_LOGI(AceLogTag::ACE_DRAG,
                "Update DragStyle to %{public}d failed, keep %{public}d. pointerEventId: %{public}d. ret = %{public}d",
                dragStyle, dragCursorStyleCore_, eventId, ret);
        } else {
            dragCursorStyleCore_ = dragStyle;
        }
    }
}

bool CheckParentVisible(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
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
        if (!frameNode || !frameNode->IsActive() || !frameNode->IsVisible() || !frameNode->IsOnMainTree()) {
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
    CHECK_NULL_VOID(notifyEvent);
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
        if (!frameNode) {
            continue;
        }
        auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
        if (!CheckParentVisible(frameNode) || (eventHub && !eventHub->IsEnabled())) {
            continue;
        }
        auto pattern = frameNode->GetPattern<Pattern>();
        if (!pattern) {
            continue;
        }
        pattern->HandleOnDragStatusCallback(dragEventType, notifyEvent);
    }
}

void DragDropManager::NotifyDragFrameNode(
    const Point& point, const DragEventType& dragEventType, const DragRet& dragRet)
{
    RefPtr<NotifyDragEvent> notifyEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    CHECK_NULL_VOID(notifyEvent);
    UpdateNotifyDragEvent(notifyEvent, point, dragEventType);
    notifyEvent->SetResult(dragRet);
    NotifyDragRegisterFrameNode(nodesForDragNotify_, dragEventType, notifyEvent);
}

RefPtr<FrameNode> DragDropManager::GetRootNode()
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetRootElement();
}

void DragDropManager::OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    NotifyDragFrameNode(point, DragEventType::START);
    CHECK_NULL_VOID(frameNode);
    preTargetFrameNode_ = frameNode;
    draggedFrameNode_ = preTargetFrameNode_;
    preMovePoint_ = point;
    parentHitNodes_.emplace(frameNode->GetId());

    // Reset hover status when drag start.
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    eventManager->CleanHoverStatusForDragBegin();
}

void DragDropManager::OnDragStart(const Point& point)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    NotifyDragFrameNode(point, DragEventType::START);

    // Reset hover status when drag start.
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    eventManager->CleanHoverStatusForDragBegin();
}

void DragDropManager::PrintDragFrameNode(
    const OHOS::Ace::DragPointerEvent& pointerEvent, const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (preTargetFrameNode_) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "Current windowId is %{public}d, pointerEventId is %{public}d, "
            "PreTargetFrameNode is %{public}s, depth is %{public}d, New find "
            "targetNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId, preTargetFrameNode_->GetTag().c_str(),
            preTargetFrameNode_->GetDepth(), dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
    } else {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "Current windowId is %{public}d, pointerEventId is %{public}d, "
            "PreTargetFrameNode is nullptr, New find targetNode is %{public}s, depth is %{public}d",
            container->GetWindowId(), pointerEvent.pointerEventId, dragFrameNode->GetTag().c_str(),
            dragFrameNode->GetDepth());
    }
}

void DragDropManager::PrintGridDragFrameNode(
    const float globalX, const float globalY, const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (preGridTargetFrameNode_) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "Current windowId is %{public}d"
            "PreTargetFrameNode is %{public}s, depth is %{public}d,"
            "New find targetNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), preGridTargetFrameNode_->GetTag().c_str(),
            preGridTargetFrameNode_->GetDepth(), dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
    } else {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "Current windowId is %{public}d, "
            "PreTargetFrameNode is nullptr, New find targetNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), dragFrameNode->GetTag().c_str(), dragFrameNode->GetDepth());
    }
}

void DragDropManager::TransDragWindowToDragFwk(int32_t windowContainerId)
{
    if (isDragFwkShow_) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "TransDragWindowToDragFwk is %{public}d", isDragFwkShow_);
    ACE_SCOPED_TRACE("drag: set drag window visible by transfer");
    if (draggedFrameNode_) {
        auto gestureHub = draggedFrameNode_->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto dragEventActuator = gestureHub->GetDragEventActuator();
        CHECK_NULL_VOID(dragEventActuator);
        dragEventActuator->NotifyTransDragWindowToFwk();
    }
    InteractionInterface::GetInstance()->SetDragWindowVisible(true);
    DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
    isDragFwkShow_ = true;
    HideSubwindowDragNode();
    auto overlayManager = GetDragAnimationOverlayManager(windowContainerId);
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemoveDragPixelMap();
    overlayManager->RemoveGatherNode();
    SubwindowManager::GetInstance()->HidePreviewNG();
    info_.scale = -1.0;
    dampingOverflowCount_ = 0;
}

void DragDropManager::OnDragMoveOut(const DragPointerEvent& pointerEvent)
{
    Point point = pointerEvent.GetPoint();
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    isReDragStart_ = false;
    SetIsWindowConsumed(false);
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(Point(-1, -1));
    NotifyPullEventListener(pointerEvent);
    if (preTargetFrameNode_) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Leave the current window, windowId is %{public}d,"
            " pointerEventId is %{public}d. PreTargetFrameNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId, preTargetFrameNode_->GetTag().c_str(),
            preTargetFrameNode_->GetDepth());
        FireOnDragEvent(preTargetFrameNode_, pointerEvent, DragEventType::LEAVE, extraInfo_);
        preTargetFrameNode_ = nullptr;
    }
    if (IsNeedDisplayInSubwindow() || isDragWithContextMenu_) {
        TransDragWindowToDragFwk(Container::CurrentId());
    }
    ClearSummary();
    ClearExtraInfo();
    SetDragCursorStyleCore(DragCursorStyleCore::DEFAULT);
}

void DragDropManager::OnDragThrow(const DragPointerEvent& pointerEvent)
{
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    SetIsWindowConsumed(false);
    Point point = pointerEvent.GetPoint();
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(Point(-1, -1));
    if (preTargetFrameNode_) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Throw from the current window, windowId is %{public}d,"
            " pointerEventId is %{public}d. PreTargetFrameNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId, preTargetFrameNode_->GetTag().c_str(),
            preTargetFrameNode_->GetDepth());
        FireOnDragEvent(preTargetFrameNode_, pointerEvent, DragEventType::LEAVE, extraInfo_);
        preTargetFrameNode_ = nullptr;
    }
    TransDragWindowToDragFwk(container->GetInstanceId());
    ClearSummary();
    ClearExtraInfo();
    SetDragCursorStyleCore(DragCursorStyleCore::DEFAULT);
}

void DragDropManager::OnDragPullCancel(const DragPointerEvent& pointerEvent)
{
    RemoveDeadlineTimer();
    auto container = Container::Current();
    auto containerId = container->GetInstanceId();
    DragDropBehaviorReporter::GetInstance().UpdateContainerId(containerId);
    DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::USER_STOP_DRAG);
    if (container && container->IsSceneBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    SetIsWindowConsumed(false);
    Point point = pointerEvent.GetPoint();
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(Point(-1, -1));
    if (preTargetFrameNode_) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Cancel from the current window, windowId is %{public}d,"
            " pointerEventId is %{public}d. PreTargetFrameNode is %{public}s, depth is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId, preTargetFrameNode_->GetTag().c_str(),
            preTargetFrameNode_->GetDepth());
        FireOnDragEvent(preTargetFrameNode_, pointerEvent, DragEventType::LEAVE, extraInfo_);
        preTargetFrameNode_ = nullptr;
    }
    DragDropRet dragDropRet { DragRet::DRAG_CANCEL, false, container->GetWindowId(), DragBehavior::MOVE };
    ResetDragDropStatus(point, dragDropRet, container->GetWindowId());
    ClearSummary();
    ClearExtraInfo();
    ClearVelocityInfo();
    DoDragReset();
}

void DragDropManager::OnDragStartForDragEvent(const DragPointerEvent& pointerEvent,
    const RefPtr<FrameNode>& frameNode)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    ResetPreTargetFrameNode(container->GetInstanceId());
    RequireSummaryIfNecessary(pointerEvent);
    SetDragCursorStyleCore(DragCursorStyleCore::DEFAULT);
    OnDragMove(pointerEvent, extraInfo_, frameNode);
    TAG_LOGI(AceLogTag::ACE_DRAG, "start drag, current windowId is %{public}d", container->GetWindowId());
}

void DragDropManager::HandleDragEvent(const DragPointerEvent& pointerEvent, DragEventAction action,
    const RefPtr<FrameNode>& node)
{
    switch (action) {
        case DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER: {
            RequireSummary();
            OnDragStart(pointerEvent.GetPoint());
            break;
        }
        // PULL_OUT
        case DragEventAction::DRAG_EVENT_OUT: {
            OnDragMoveOut(pointerEvent);
            break;
        }
        case DragEventAction::DRAG_EVENT_PULL_THROW: {
            OnDragThrow(pointerEvent);
            break;
        }
        case DragEventAction::DRAG_EVENT_PULL_CANCEL: {
            OnDragPullCancel(pointerEvent);
            break;
        }
        case DragEventAction::DRAG_EVENT_END: {
            OnDragEnd(pointerEvent, extraInfo_, node);
            break;
        }
        case DragEventAction::DRAG_EVENT_START: {
            OnDragStartForDragEvent(pointerEvent, node);
            break;
        }
        default:
            break;
    }
}

bool DragDropManager::isDistanceLimited(const Point& point)
{
    auto distance = sqrt(pow(point.GetX() - preMovePoint_.GetX(), 2) + pow(point.GetY() - preMovePoint_.GetY(), 2));
    TAG_LOGD(AceLogTag::ACE_DRAG, "onDragMove, distance: %{public}f", distance);
    if (distance < MOVE_DISTANCE_LIMIT) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "onDragMove, distance is less than limit");
        return true;
    }
    return false;
}

bool DragDropManager::isTimeLimited(const DragPointerEvent& pointerEvent, const Point& point)
{
    uint64_t currentTimeStamp = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(pointerEvent.time.time_since_epoch()).count());
    if (currentTimeStamp > preTimeStamp_ && currentTimeStamp - preTimeStamp_ < MOVE_TIME_LIMIT) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "onDragMove, time is less than limit");
        return true;
    }
    return false;
}

bool DragDropManager::ReachMoveLimit(const DragPointerEvent& pointerEvent, const Point& point)
{
    if (pointerEvent.sourceTool == SourceTool::MOUSE) {
        if (isTimeLimited(pointerEvent, point) && isDistanceLimited(point)) {
            return true;
        }
    }
    return false;
}

void DragDropManager::HandleOnDragMove(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
    const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);

    if (dragFrameNode == preTargetFrameNode_) {
        FireOnDragEvent(dragFrameNode, pointerEvent, DragEventType::MOVE, extraInfo);
        return;
    }

    FireOnDragLeave(preTargetFrameNode_, pointerEvent, extraInfo);
    PrintDragFrameNode(pointerEvent, dragFrameNode);
    FireOnDragEvent(dragFrameNode, pointerEvent, DragEventType::ENTER, extraInfo);
    preTargetFrameNode_ = dragFrameNode;
}

void DragDropManager::OnDragMove(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
    const RefPtr<FrameNode>& node)
{
    RequireSummaryIfNecessary(pointerEvent);
    Point point = pointerEvent.GetPoint();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container && container->IsSceneBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            SetIsWindowConsumed(false);
            return;
        }
    }
    if (ReachMoveLimit(pointerEvent, point)) {
        return;
    }
    NotifyPullEventListener(pointerEvent);
    preMovePoint_ = point;
    preDragPointerEvent_ = pointerEvent;
    preTimeStamp_ = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(pointerEvent.time.time_since_epoch()).count());
    SetIsWindowConsumed(false);
    if (isDragFwkShow_) {
        auto menuWrapper = GetMenuWrapperNodeFromDrag();
        if (menuWrapper) {
            auto menuPosition = DragDropFuncWrapper::GetPointRelativeToMainWindow(point);
            SubwindowManager::GetInstance()->UpdateHideMenuOffsetNG(
                menuPosition, 1.0, false, menuWrapper ? menuWrapper->GetId() : -1);
        }
    }
    UpdateVelocityTrackerPoint(point, false);
    UpdateDragListener(point);
    auto dragFrameNode = FindDragFrameNodeByPosition(
        static_cast<float>(point.GetX()), static_cast<float>(point.GetY()), node);
    if (!dragFrameNode) {
        if (preTargetFrameNode_) {
            TAG_LOGI(AceLogTag::ACE_DRAG,
                "Not find drag target node, current windowId is %{public}d, pointerEventId is %{public}d, "
                "PreTargetFrameNode is %{public}s, depth is %{public}d.",
                container->GetWindowId(), pointerEvent.pointerEventId, preTargetFrameNode_->GetTag().c_str(),
                preTargetFrameNode_->GetDepth());
            FireOnDragEvent(preTargetFrameNode_, pointerEvent, DragEventType::LEAVE, extraInfo);
            preTargetFrameNode_ = nullptr;
        }

        if (!isMouseDragged_ || isDragWindowShow_) {
            UpdateDragStyle(DragCursorStyleCore::MOVE, pointerEvent.pointerEventId);
        }
        return;
    }
    HandleOnDragMove(pointerEvent, extraInfo, dragFrameNode);
}

void DragDropManager::ResetDragDropStatus(const Point& point, const DragDropRet& dragDropRet, int32_t windowId)
{
    ACE_SCOPED_TRACE("drag: reset drag %d, %d", dragDropRet.result, dragDropRet.hasCustomAnimation);
    if (dragDropRet.result != DragRet::DRAG_FAIL || !isMouseDragged_) {
        InteractionInterface::GetInstance()->SetDragWindowVisible(!dragDropRet.hasCustomAnimation);
    }
    InteractionInterface::GetInstance()->StopDrag(dragDropRet);
    NotifyDragFrameNode(point, DragEventType::DROP, dragDropRet.result);
    ResetPullId();
    dragCursorStyleCore_ = DragCursorStyleCore::DEFAULT;
    isReDragStart_ = false;
}

void DragDropManager::ResetPreTargetFrameNode(int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    if (container && (container->IsSceneBoardWindow() || container->IsUIExtensionWindow())) {
        return;
    }
    // pull-in subwindow, need to notify showMenu and update menu offset.
    if (instanceId > MIN_SUBCONTAINER_ID) {
        isDragFwkShow_ = true;
    }
    preTargetFrameNode_ = nullptr;
}

void DragDropManager::ResetDragEndOption(
    const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent, int32_t currentId)
{
    SetDragResult(notifyMessage, dragEvent);
    SetDragBehavior(notifyMessage, dragEvent);
    DoDragReset();
    SetIsDragged(false);
    SetDraggingPointer(-1);
    SetDraggingPressedState(false);
    ResetDragPreviewInfo();
    HideDragPreviewWindow(currentId);
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetPressedKeyCodes(GetDragDropPointerEvent().pressedKeyCodes);
}

void DragDropManager::DoDragReset()
{
    dragDropState_ = DragDropMgrState::IDLE;
    preTargetFrameNode_ = nullptr;
    draggedFrameNode_ = nullptr;
    menuWrapperNode_ = nullptr;
    preMovePoint_ = Point(0, 0);
    hasNotifiedTransformation_ = false;
    badgeNumber_ = -1;
    isDragWithContextMenu_ = false;
    dampingOverflowCount_ = 0;
    isDragNodeNeedClean_ = false;
    isAnyDraggableHit_ = false;
    fingerPointInfo_.clear();
    DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
}

void DragDropManager::ResetDraggingStatus(const TouchEvent& touchPoint)
{
    if (IsDraggingPressed(touchPoint.id)) {
        SetDraggingPressedState(false);
    }
    if (!IsItemDragging() && IsDragging() && IsSameDraggingPointer(touchPoint.id)) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Reset dragging status, stop drag. pointerId: %{public}d", touchPoint.id);
        DragPointerEvent dragPointerEvent;
        DragDropFuncWrapper::ConvertPointerEvent(touchPoint, dragPointerEvent);
        SetIsDisableDefaultDropAnimation(true);
        OnDragEnd(dragPointerEvent, "");
    }
}

void DragDropManager::HandleOnDragEnd(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
    const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_VOID(dragFrameNode);
    Point point = pointerEvent.GetPoint();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (!IsDropAllowed(dragFrameNode)) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "DragDropManager onDragEnd, target data is not allowed to fall into. WindowId is %{public}d, "
            "pointerEventId is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId);
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::APP_REFUSE_DATA);
        ACE_SCOPED_TRACE("drag: stop drag, not allowed to drop");
        ResetDragDrop(container->GetWindowId(), point);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Current windowId is %{public}d, pointerEventId is %{public}d, "
        "TargetNode is %{public}s.",
        container->GetWindowId(), pointerEvent.pointerEventId, dragFrameNode->GetTag().c_str());
    if (IsUIExtensionComponent(dragFrameNode)) {
        auto pattern = dragFrameNode->GetPattern<Pattern>();
        pattern->HandleDragEvent(pointerEvent);
        NotifyDragFrameNode(point, DragEventType::DROP);
        return;
    }

    RequestDragSummaryInfoAndPrivilege();
    std::string udKey;
    InteractionInterface::GetInstance()->GetUdKey(udKey);
    auto eventHub = dragFrameNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->GetDisableDataPrefetch()) {
        if (!CheckRemoteData(dragFrameNode, pointerEvent, udKey)) {
            auto unifiedData = RequestUDMFDataWithUDKey(udKey);
            DoDropAction(dragFrameNode, pointerEvent, unifiedData, udKey);
        }
    } else {
        DoDropAction(dragFrameNode, pointerEvent, nullptr, udKey);
    }
}

void DragDropManager::OnDragEnd(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
    const RefPtr<FrameNode>& node, const bool keyEscape)
{
    RemoveDeadlineTimer();
    Point point = pointerEvent.GetPoint();
    dragDropPointerEvent_ = pointerEvent;
    auto preTargetFrameNode = preTargetFrameNode_;
    DoDragReset();
    auto container = Container::Current();
    auto containerId = container->GetInstanceId();
    DragDropBehaviorReporter::GetInstance().UpdateContainerId(containerId);
    if (container && container->IsSceneBoardWindow()) {
        if (IsDragged() && IsWindowConsumed()) {
            TAG_LOGD(AceLogTag::ACE_DRAG, "DragDropManager is dragged or window consumed. WindowId is %{public}d",
                container->GetWindowId());
            return;
        }
    }
    UpdateVelocityTrackerPoint(point, true);
    auto dragFrameNode = FindDragFrameNodeByPosition(
        static_cast<float>(point.GetX()), static_cast<float>(point.GetY()), FilterSubwindowDragRootNode(node));
    if (HandleUIExtensionComponentDragCancel(preTargetFrameNode, dragFrameNode, keyEscape, pointerEvent, point)) {
        return;
    }
    if (isDragCancel_) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::USER_STOP_DRAG);
        TAG_LOGI(AceLogTag::ACE_DRAG, "DragDropManager is dragCancel, finish drag. WindowId is %{public}d, "
            "pointerEventId is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId);
        ACE_SCOPED_TRACE("drag: drag cancelled");
        DragDropRet dragDropRet { DragRet::DRAG_CANCEL, false, container->GetWindowId(), DragBehavior::UNKNOWN };
        ResetDragDropStatus(point, dragDropRet, container->GetWindowId());
        FireOnDragEvent(preTargetFrameNode, pointerEvent, DragEventType::LEAVE, extraInfo);
        ClearVelocityInfo();
        return;
    }
    if (IsUIExtensionComponent(preTargetFrameNode) && preTargetFrameNode != dragFrameNode) {
        HandleUIExtensionDragEvent(preTargetFrameNode, pointerEvent, DragEventType::LEAVE);
    }
    if (!dragFrameNode) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::APP_DATA_UNSUPPORT);
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "DragDropManager onDragEnd, not find drop target, stop drag. WindowId is %{public}d, "
            "pointerEventId is %{public}d.",
            container->GetWindowId(), pointerEvent.pointerEventId);
        ACE_SCOPED_TRACE("drag: drag stop, not find drop target");
        ResetDragDrop(container->GetWindowId(), point);
        return;
    }
    HandleOnDragEnd(pointerEvent, extraInfo, dragFrameNode);
}

bool DragDropManager::HandleUIExtensionComponentDragCancel(const RefPtr<FrameNode>& preTargetFrameNode,
    const RefPtr<FrameNode>& dragFrameNode, const bool keyEscape, const DragPointerEvent& pointerEvent,
    const Point& point)
{
    if (!isDragCancel_) {
        return false;
    }
    if (keyEscape && IsUIExtensionComponent(preTargetFrameNode)) {
        HandleUIExtensionDragEvent(preTargetFrameNode, pointerEvent, DragEventType::PULL_CANCEL);
        NotifyDragFrameNode(point, DragEventType::DROP);
        return true;
    }
    if (IsUIExtensionComponent(dragFrameNode)) {
        auto pattern = dragFrameNode->GetPattern<Pattern>();
        CHECK_NULL_RETURN(pattern, true);
        pattern->HandleDragEvent(pointerEvent);
        NotifyDragFrameNode(point, DragEventType::DROP);
        return true;
    }
    return false;
}

bool DragDropManager::IsDropAllowed(const RefPtr<FrameNode>& dragFrameNode)
{
    CHECK_NULL_RETURN(dragFrameNode, false);
    // application passed in null to indicate refusing all drag data forcedly
    bool isDisallowDropForcedly = dragFrameNode->GetDisallowDropForcedly();
    if (isDisallowDropForcedly) {
        return false;
    }
    const auto& dragFrameNodeAllowDrop = dragFrameNode->GetAllowDrop();
    // if application does not set allow drop or set with empty, treat as all data types is allowed
    if (dragFrameNodeAllowDrop.empty() || summaryMap_.empty()) {
        return true;
    }
    DragDropBehaviorReporter::GetInstance().UpdateAllowDropType(dragFrameNodeAllowDrop);
    for (const auto& it : summaryMap_) {
        // if one matched found, allow drop
        if (dragFrameNodeAllowDrop.find(it.first) != dragFrameNodeAllowDrop.end()) {
            return true;
        }
    }
    return false;
}

void DragDropManager::RequestDragSummaryInfoAndPrivilege()
{
    RequireSummary();
    int ret = InteractionInterface::GetInstance()->AddPrivilege();
    if (ret != 0 && SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Interaction AddPrivilege in DragEnd with code:%{public}d", ret);
    }
    ShadowOffsetData shadowOffsetData { -1, -1, -1, -1 };
    ret = InteractionInterface::GetInstance()->GetShadowOffset(shadowOffsetData);
    if (ret == 0) {
        previewRect_ =
            Rect(shadowOffsetData.offsetX, shadowOffsetData.offsetY, shadowOffsetData.width, shadowOffsetData.height);
    } else {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Interaction GetShadowOffset in DragEnd with code:%{public}d", ret);
    }
}

void DragDropManager::DoDropAction(const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
    const RefPtr<UnifiedData>& unifiedData, const std::string& udKey)
{
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    CHECK_NULL_VOID(event);
    if (!udKey.empty()) {
        event->SetUdKey(udKey);
    }
    if (unifiedData == nullptr) {
        event->SetIsGetDataSuccess(false);
    } else {
        DragDropBehaviorReporter::GetInstance().UpdateRecordSize(unifiedData->GetSize());
        event->SetData(unifiedData);
        event->SetIsGetDataSuccess(true);
    }

    OnDragDrop(event, dragFrameNode, pointerEvent);
}

RefPtr<UnifiedData> DragDropManager::RequestUDMFDataWithUDKey(const std::string& udKey)
{
    if (udKey.empty()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "udKey is empty");
        return nullptr;
    }
    ACE_SCOPED_TRACE("drag: get drag data from udmf");
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->CreateUnifiedData();
    auto ret = UdmfClient::GetInstance()->GetData(udData, udKey);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get udmfData failed");
        return nullptr;
    }
    return udData;
}

void DragDropManager::TryGetDataBackGround(const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
    const std::string& udKey, int32_t count)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    taskScheduler->PostTask(
        [id = Container::CurrentId(), pipeline, dragFrameNode, pointerEvent, udKey, count,
        weakManager = WeakClaim(this)]() {
            ContainerScope scope(id);
            auto dragDropManager = weakManager.Upgrade();
            CHECK_NULL_VOID(dragDropManager);
            auto taskScheduler = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskScheduler);
            auto result = dragDropManager->RequestUDMFDataWithUDKey(udKey);
            if (result != nullptr || count >= MAX_RETRY_TIMES) {
                taskScheduler->PostTask(
                    [dragFrameNode, pointerEvent, weakManager, result, udKey]() {
                        auto dragDropManager = weakManager.Upgrade();
                        CHECK_NULL_VOID(dragDropManager);
                        dragDropManager->DoDropAction(dragFrameNode, pointerEvent, result, udKey);
                    },
                    TaskExecutor::TaskType::UI, "ArkUIDragDropAction");
            } else {
                // first temp get udmfData failed, prepare to retryGetData.
                taskScheduler->PostDelayedTask(
                    [dragFrameNode, pointerEvent, weakManager, count, udKey]() {
                        auto dragDropManager = weakManager.Upgrade();
                        CHECK_NULL_VOID(dragDropManager);
                        dragDropManager->TryGetDataBackGround(dragFrameNode, pointerEvent, udKey, count + 1);
                    },
                    TaskExecutor::TaskType::UI, MAX_RETRY_DURATION, "ArkUIDragDropRetryGetData");
            }
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIDragDropGetDataBackground");
}

bool DragDropManager::CheckRemoteData(
    const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent, const std::string& udKey)
{
    if (udKey.empty()) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::GET_UDKEY_FAIL);
        return false;
    }
    std::string remoteUdKey = udKey;
    auto isRemoteData = UdmfClient::GetInstance()->GetRemoteStatus(remoteUdKey);
    if (isRemoteData) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Stop drag with motion drag action.");
        TryGetDataBackGround(dragFrameNode, pointerEvent, udKey);
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::GET_UDKEY_FAIL);
        DragDropBehaviorReporter::GetInstance().UpdateIsCrossing(CrossingEnd::IS_CROSSING);
        return isRemoteData;
    }
    DragDropBehaviorReporter::GetInstance().UpdateIsCrossing(CrossingEnd::NOT_CROSSING);
    return isRemoteData;
}

void DragDropManager::OnDragDrop(RefPtr<OHOS::Ace::DragEvent>& event, const RefPtr<FrameNode>& dragFrameNode,
    const OHOS::Ace::DragPointerEvent& pointerEvent)
{
    auto point = pointerEvent.GetPoint();
    CHECK_NULL_VOID(dragFrameNode);
    auto eventHub = dragFrameNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    UpdateDragEvent(event, pointerEvent);
    auto extraParams = eventHub->GetDragExtraParams(extraInfo_, point, DragEventType::DROP);
    DragDropGlobalController::GetInstance().SetIsOnOnDropPhase(true);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, event, extraParams);
    if (event->IsDragEndPending() && event->GetRequestIdentify() != -1) {
        if (PostStopDrag(dragFrameNode, pointerEvent, event, extraParams)) {
            return;
        }
    }
    HandleStopDrag(dragFrameNode, pointerEvent, event, extraParams);
    DragDropGlobalController::GetInstance().SetIsOnOnDropPhase(false);
}

void DragDropManager::HandleStopDrag(const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
    const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams)
{
    auto point = pointerEvent.GetPoint();
    CHECK_NULL_VOID(dragFrameNode);
    auto eventHub = dragFrameNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->HandleInternalOnDrop(event, extraParams);
    ClearVelocityInfo();
    SetIsDragged(false);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragResult = event->GetResult();
    if (dragResult == DragRet::DRAG_FAIL) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::APP_RECEIVE_FAIL);
    } else if (dragResult == DragRet::DRAG_CANCEL) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStopResult(DragStopResult::USER_STOP_DRAG);
    }
    auto useCustomAnimation = event->IsUseCustomAnimation();
    auto dragBehavior = event->GetDragBehavior();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto windowId = container->GetWindowId();
    ExecuteStopDrag(event, dragResult, useCustomAnimation, windowId, dragBehavior, pointerEvent);
    NotifyDragFrameNode(point, DragEventType::DROP, event->GetResult());
    dragFrameNode->MarkDirtyNode();
    ResetPullId();
    dragCursorStyleCore_ = DragCursorStyleCore::DEFAULT;
    pipeline->RequestFrame();
}

bool DragDropManager::PostStopDrag(const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
    const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams)
{
    CHECK_NULL_RETURN(dragFrameNode, false);
    CHECK_NULL_RETURN(event, false);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskScheduler, false);
    taskScheduler->PostDelayedTask(
        [pointerEvent, event, extraParams, nodeWeak = WeakClaim(AceType::RawPtr(dragFrameNode)),
            weakManager = WeakClaim(this)]() {
            if (!DragDropGlobalController::GetInstance().IsOnOnDropPhase() || !event) {
                return;
            }
            auto dragDropManager = weakManager.Upgrade();
            if (dragDropManager) {
                auto frameNode = nodeWeak.Upgrade();
                event->SetResult(DragRet::DRAG_FAIL);
                dragDropManager->HandleStopDrag(frameNode, pointerEvent, event, extraParams);
            }
            DragDropGlobalController::GetInstance().SetIsOnOnDropPhase(false);
        },
        TaskExecutor::TaskType::UI, DROP_DELAY_TIME, "ArkUIStopDragDeadlineTimer");
    return DragDropGlobalController::GetInstance().RequestDragEndCallback(event->GetRequestIdentify(),
        event->GetResult(), GetStopDragCallBack(dragFrameNode, pointerEvent, event, extraParams));
}

std::function<void(const DragRet&)> DragDropManager::GetStopDragCallBack(const RefPtr<FrameNode>& dragFrameNode,
    const DragPointerEvent& pointerEvent, const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams)
{
    auto callback = [id = Container::CurrentId(), pointerEvent, event, extraParams,
        nodeWeak = WeakClaim(AceType::RawPtr(dragFrameNode)),
        weakManager = WeakClaim(this)] (const DragRet& dragResult) {
        ContainerScope scope(id);
        auto dragDropManager = weakManager.Upgrade();
        CHECK_NULL_VOID(dragDropManager);
        CHECK_NULL_VOID(event);
        event->SetResult(dragResult);
        auto frameNode = nodeWeak.Upgrade();
        dragDropManager->HandleStopDrag(frameNode, pointerEvent, event, extraParams);
    };
    return callback;
}

void DragDropManager::ExecuteStopDrag(const RefPtr<OHOS::Ace::DragEvent>& event, DragRet dragResult,
    bool useCustomAnimation, int32_t windowId, DragBehavior dragBehavior,
    const OHOS::Ace::DragPointerEvent& pointerEvent)
{
    if (useCustomAnimation && event->HasDropAnimation()) {
        ExecuteCustomDropAnimation(event, DragDropRet { dragResult, useCustomAnimation, windowId, dragBehavior });
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    HideSubwindowDragNode();
    auto overlayManager = GetDragAnimationOverlayManager(pipeline->GetInstanceId());
    if (overlayManager && !isDragFwkShow_) {
        overlayManager->RemoveDragPixelMap();
        overlayManager->RemoveFilter();
        pipeline->FlushMessages();
    }
    pipeline->AddAfterRenderTask([dragResult, useCustomAnimation, windowId, dragBehavior,
                                     pointerEventId = pointerEvent.pointerEventId, weak = WeakClaim(this)]() mutable {
        auto manager = weak.Upgrade();
        if (manager) {
            manager->HideDragPreviewOverlay();
            useCustomAnimation = manager->IsDisableDefaultDropAnimation() ? true : useCustomAnimation;
        }
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "Stop drag, start do drop animation. useCustomAnimation is %{public}d,"
            "WindowId is %{public}d, pointerEventId is %{public}d.",
            useCustomAnimation, windowId, pointerEventId);
        InteractionInterface::GetInstance()->SetDragWindowVisible(!useCustomAnimation);
        DragDropRet dragDropRet { dragResult, useCustomAnimation, windowId, dragBehavior };
        InteractionInterface::GetInstance()->StopDrag(dragDropRet);
    });
}

void DragDropManager::ExecuteCustomDropAnimation(const RefPtr<OHOS::Ace::DragEvent>& event, DragDropRet dragDropRet)
{
    CHECK_NULL_VOID(event);
    event->ExecuteDropAnimation();
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = GetDragAnimationOverlayManager(pipeline->GetInstanceId());
    if (overlayManager) {
        overlayManager->RemoveDragPixelMap();
        overlayManager->RemoveFilter();
    }
    HideSubwindowDragNode();
    InteractionInterface::GetInstance()->SetDragWindowVisible(false);
    pipeline->FlushMessages();
    InteractionInterface::GetInstance()->StopDrag(dragDropRet);
}

void DragDropManager::RequireSummary()
{
    std::map<std::string, int64_t> summary;
    int32_t ret = InteractionInterface::GetInstance()->GetDragSummary(summary);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "RequireSummary: Interaction GetSummary failed: %{public}d", ret);
    } else {
        std::string summarys;
        for (const auto& [udkey, recordSize] : summary) {
            std::string str = udkey + "-" + std::to_string(recordSize) + ";";
            summarys += str;
        }
        TAG_LOGI(AceLogTag::ACE_DRAG, "require summary: %{public}s", summarys.c_str());
        DragDropBehaviorReporter::GetInstance().UpdateSummaryType(summarys);
    }
    std::string extraInfo;
    ret = InteractionInterface::GetInstance()->GetDragExtraInfo(extraInfo);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "GetExtraInfo: Interaction GetExtraInfo failed: %{public}d", ret);
    }
    previewRect_ = Rect(-1, -1, -1, -1);
    extraInfo_ = extraInfo;
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
    ResetPullId();
    ResetRecordSize();
}

void DragDropManager::OnTextDragEnd(float globalX, float globalY, const std::string& extraInfo)
{
    dragDropState_ = DragDropMgrState::IDLE;
    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY);
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
    const RefPtr<FrameNode>& frameNode, const DragPointerEvent& pointerEvent,
    DragEventType type, const std::string& extraInfo)
{
    CHECK_NULL_VOID(frameNode);
    if (IsUIExtensionComponent(frameNode)) {
        HandleUIExtensionDragEvent(frameNode, pointerEvent, type);
        return;
    }
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDrop() && !eventHub->HasOnItemDrop() && !eventHub->HasCustomerOnDrop()) {
        return;
    }
    auto point = pointerEvent.GetPoint();
    auto extraParams = eventHub->GetDragExtraParams(extraInfo_.empty() ? extraInfo : extraInfo_, point, type);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    CHECK_NULL_VOID(event);
    UpdateDragEvent(event, pointerEvent);

    FireOnEditableTextComponent(frameNode, type);
    FireOnDragEventWithDragType(eventHub, type, event, extraParams);

    if (isMouseDragged_ && !isDragWindowShow_) {
        return;
    }
    UpdateDragCursorStyle(frameNode, event, pointerEvent.pointerEventId);
}

void DragDropManager::UpdateDragCursorStyle(const RefPtr<FrameNode>& frameNode,
    const RefPtr<OHOS::Ace::DragEvent>& event, const int32_t eventId)
{
    if (event->GetResult() == DragRet::ENABLE_DROP) {
        if (event->GetDragBehavior() == DragBehavior::MOVE) {
            UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
        } else {
            UpdateDragStyle(DragCursorStyleCore::COPY, eventId);
        }
    } else if (event->GetResult() == DragRet::DISABLE_DROP) {
        // simplified specifications for drag cursor style, no longer showing forbidden drag cursor
        UpdateDragStyle(DragCursorStyleCore::MOVE, eventId);
    } else {
        UpdateDragAllowDrop(frameNode, event->GetDragBehavior(), eventId, event->IsCapi());
    }
}

void DragDropManager::OnItemDragStart(float globalX, float globalY, const RefPtr<FrameNode>& frameNode)
{
    dragDropState_ = DragDropMgrState::DRAGGING;
    preGridTargetFrameNode_ = frameNode;
    draggedGridFrameNode_ = frameNode;
}

void DragDropManager::OnItemDragMove(float globalX, float globalY, int32_t draggedIndex, DragType dragType)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);

    UpdateItemDragPosition(globalX, globalY);

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(globalX);
    itemDragInfo.SetY(globalY);

    // use -1 for grid item not in eventGrid
    auto getDraggedIndex = [draggedGrid = draggedGridFrameNode_, draggedIndex, dragType](
                               const RefPtr<FrameNode>& eventGrid) {
        return (dragType == DragType::GRID) ? (eventGrid == draggedGrid ? draggedIndex : -1) : draggedIndex;
    };

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY);
    if (!dragFrameNode) {
        if (preGridTargetFrameNode_) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Not find drag target node, current windowId is %{public}d,"
                "PreGridTargetFrameNode is %{public}s, depth is %{public}d.",
                container->GetWindowId(), preGridTargetFrameNode_->GetTag().c_str(),
                preGridTargetFrameNode_->GetDepth());
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

    PrintGridDragFrameNode(globalX, globalY, dragFrameNode);
    FireOnItemDragEvent(dragFrameNode, dragType, itemDragInfo, DragEventType::ENTER, getDraggedIndex(dragFrameNode));
    preGridTargetFrameNode_ = dragFrameNode;
}

float DragDropManager::GetWindowScale() const
{
    float scale = 1.0f;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, scale);
    scale = container->GetWindowScale();
    return scale;
}

void DragDropManager::OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType)
{
    dragDropState_ = DragDropMgrState::IDLE;
    auto windowScale = isDragWindowSubWindow_ ? 1.0f : GetWindowScale();
    auto windowX = globalX * windowScale;
    auto windowY = globalY * windowScale;

    OHOS::Ace::ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(windowX);
    itemDragInfo.SetY(windowY);

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY);
    if (!dragFrameNode) {
        // drag on one grid and drop on other area
        if (draggedGridFrameNode_) {
            if (dragType == DragType::GRID) {
                auto eventHub = draggedGridFrameNode_->GetOrCreateEventHub<GridEventHub>();
                CHECK_NULL_VOID(eventHub);
                eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, -1, false);
            } else {
                auto eventHub = draggedGridFrameNode_->GetOrCreateEventHub<ListEventHub>();
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
    dragDropState_ = DragDropMgrState::IDLE;
    preGridTargetFrameNode_ = nullptr;
    draggedGridFrameNode_ = nullptr;
}

void DragDropManager::FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
    const OHOS::Ace::ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex)
{
    CHECK_NULL_VOID(frameNode);
    if (dragType == DragType::GRID) {
        auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
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
        auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
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
    CHECK_NULL_RETURN(frameNode, false);
    if (dragType == DragType::GRID) {
        auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
        CHECK_NULL_RETURN(eventHub, false);
        return eventHub->FireOnItemDrop(itemDragInfo, draggedIndex, insertIndex, isSuccess);
    } else if (dragType == DragType::LIST) {
        auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
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
        auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
        CHECK_NULL_RETURN(eventHub, -1);
        if (frameNode != draggedGridFrameNode_) {
            return eventHub->GetInsertPosition(globalX, globalY);
        }
        auto itemFrameNode = frameNode->FindChildByPositionWithoutChildTransform(globalX, globalY);
        if (!itemFrameNode) {
            if (eventHub->CheckPostionInGrid(globalX, globalY)) {
                return eventHub->GetFrameNodeChildSize();
            }
        } else {
            return eventHub->GetGridItemIndex(itemFrameNode);
        }
    } else if (dragType == DragType::LIST) {
        auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
        CHECK_NULL_RETURN(eventHub, -1);
        return eventHub->GetListItemIndexByPosition(globalX, globalY);
    }
    return -1;
}

void DragDropManager::AddDataToClipboard(const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
            CHECK_NULL_VOID(dragDropManager);
            auto addData = dragDropManager->newData_->ToString();
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
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    ResetRecordSize();
    if (itemDragOverlayNode_) {
        RemoveItemDrag();
        itemDragOverlayNode_ = nullptr;
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
        auto listEventHub = draggedGridFrameNode_->GetOrCreateEventHub<ListEventHub>();
        if (listEventHub) {
            listEventHub->HandleOnItemDragCancel();
            return;
        }
        auto gridEventHub = draggedGridFrameNode_->GetOrCreateEventHub<GridEventHub>();
        if (gridEventHub) {
            gridEventHub->HandleOnItemDragCancel();
            return;
        }
    }
}

RefPtr<DragDropProxy> DragDropManager::CreateFrameworkDragDropProxy()
{
    SetIsDragged(true);
    isDragCancel_ = false;
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

void DragDropManager::UpdateNotifyDragEvent(
    RefPtr<NotifyDragEvent>& notifyEvent, const Point& point, const DragEventType dragEventType)
{
    CHECK_NULL_VOID(notifyEvent);
    notifyEvent->SetX((double)point.GetX());
    notifyEvent->SetY((double)point.GetY());
    notifyEvent->SetScreenX((double)point.GetScreenX());
    notifyEvent->SetScreenY((double)point.GetScreenY());
    if (dragEventType != DragEventType::START) {
        if (dragEventType != DragEventType::DROP) {
            notifyEvent->SetVelocity(velocityTracker_.GetVelocity());
        }
        notifyEvent->SetSummary(summaryMap_);
        notifyEvent->SetPreviewRect(GetDragWindowRect(point));
    }
}

void DragDropManager::UpdateDragEvent(
    RefPtr<OHOS::Ace::DragEvent>& event, const OHOS::Ace::DragPointerEvent& pointerEvent)
{
    auto point = pointerEvent.GetPoint();
    event->SetX(point.GetX());
    event->SetY(point.GetY());
    event->SetScreenX(point.GetScreenX());
    event->SetScreenY(point.GetScreenY());
    event->SetDisplayX((double)pointerEvent.GetDisplayX());
    event->SetDisplayY((double)pointerEvent.GetDisplayY());
    event->SetVelocity(velocityTracker_.GetVelocity());
    event->SetSummary(summaryMap_);
    event->SetPreviewRect(GetDragWindowRect(point));
    event->SetPressedKeyCodes(pointerEvent.pressedKeyCodes);
    event->SetSourceTool(pointerEvent.sourceTool);
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

bool DragDropManager::IsMSDPDragging() const
{
    ACE_SCOPED_TRACE("drag: get drag state from msdp");
    DragState dragState;
    InteractionInterface::GetInstance()->GetDragState(dragState);
    return dragState == DragState::START;
}

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

bool DragDropManager::GetDragPreviewInfo(const RefPtr<OverlayManager>& overlayManager, DragPreviewInfo& dragPreviewInfo,
    const RefPtr<GestureEventHub>& gestureHub, PreparedInfoForDrag& data)
{
    CHECK_NULL_RETURN(overlayManager, false);
    if (!overlayManager->GetHasDragPixelMap()) {
        return false;
    }
    auto imageNode = overlayManager->GetDragPixelMapContentNode();
    CHECK_NULL_RETURN(imageNode, false);
    auto badgeNode = overlayManager->GetDragPixelMapBadgeNode();
    if (badgeNode) {
        dragPreviewInfo.relativeContainerNode = data.relativeContainerNode;
        dragPreviewInfo.textNode = badgeNode;
    }
    CHECK_NULL_RETURN(gestureHub, false);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto previewOption = imageNode->GetDragPreviewOption();
    auto gestureEvent = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEvent, false);
    auto width = data.dragPreviewRect.Width();
    auto height = data.dragPreviewRect.Height();
    auto scaleData = DragDropManager::GetScaleInfo(width, height, gestureEvent->GetTextDraggable());
    CHECK_NULL_RETURN(scaleData, false);
    dragPreviewInfo.scale =
        (imageNode->GetTag() != V2::WEB_ETS_TAG && width > 0 && height > 0 && previewOption.isScaleEnabled)
            ? scaleData->scale : 1.0f;
    if (!isMouseDragged_ && dragPreviewInfo.scale == 1.0f) {
        dragPreviewInfo.scale = TOUCH_DRAG_PIXELMAP_SCALE;
    }
    // set menu preview scale only for no scale menu preview.
    if (isDragWithContextMenu_ && (!previewOption.isScaleEnabled || !scaleData->isNeedScale)) {
        auto imageGestureEventHub = imageNode->GetOrCreateGestureEventHub();
        if (imageGestureEventHub) {
            auto menuPreviewScale = imageGestureEventHub->GetMenuPreviewScale();
            dragPreviewInfo.scale =
                GreatNotEqual(menuPreviewScale, 0.0f) ? menuPreviewScale : TOUCH_DRAG_PIXELMAP_SCALE;
        }
    }
    dragPreviewInfo.height = static_cast<double>(height);
    dragPreviewInfo.width = static_cast<double>(width);
    dragPreviewInfo.maxWidth = scaleData->shortSide;
    dragPreviewInfo.imageNode = imageNode;
    dragPreviewInfo.originOffset = imageNode->GetPositionToWindowWithTransform();
    dragPreviewInfo.originScale = imageNode->GetTransformScale();
    CopyPreparedInfoForDrag(dragPreviewInfo, data);
    return true;
}

void DragDropManager::CopyPreparedInfoForDrag(DragPreviewInfo& dragPreviewInfo, PreparedInfoForDrag& data)
{
    dragPreviewInfo.menuPreviewNode = data.menuPreviewNode;
    dragPreviewInfo.menuPreviewImageNode = data.menuPreviewImageNode;
    dragPreviewInfo.originPreviewRect = data.originPreviewRect;
    dragPreviewInfo.dragPreviewRect = data.dragPreviewRect;
    dragPreviewInfo.relativeContainerNode = data.relativeContainerNode;
    dragPreviewInfo.stackNode = data.stackNode;
    dragPreviewInfo.sizeChangeEffect = data.sizeChangeEffect;
}

bool DragDropManager::IsNeedDoDragMoveAnimate(const DragPointerEvent& pointerEvent)
{
    if (isDragFwkShow_) {
        return false;
    }
    auto x = pointerEvent.GetPoint().GetX();
    auto y = pointerEvent.GetPoint().GetY();
    curPointerOffset_ = { x, y };
    return true;
}

bool DragDropManager::IsNeedScaleDragPreview()
{
    return info_.scale > 0 && info_.scale < 1.0f;
}
// calculate the touch position relative to the sub-window which will be used to do animation on,
// the input [x, y] is the position relative to the window which is receiving the touch event,
// and the position is contain the floatTitle offset.
OffsetF DragDropManager::GetTouchOffsetRelativeToSubwindow(int32_t containerId, int32_t x, int32_t y)
{
    auto touchOffset = OffsetF(x, y);
    auto pipeline = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_RETURN(pipeline, OffsetF(x, y));
    auto window = pipeline->GetWindow();
    CHECK_NULL_RETURN(window, OffsetF(x, y));
    auto windowOffset = window->GetCurrentWindowRect().GetOffset();
    touchOffset.SetX(touchOffset.GetX() + windowOffset.GetX());
    touchOffset.SetY(touchOffset.GetY() + windowOffset.GetY());
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(containerId) : containerId, SubwindowType::TYPE_MENU);
    CHECK_NULL_RETURN(subwindow, OffsetF(x, y));
    auto subwindowOffset = subwindow->GetWindowRect().GetOffset();
    touchOffset.SetX(touchOffset.GetX() - subwindowOffset.GetX());
    touchOffset.SetY(touchOffset.GetY() - subwindowOffset.GetY());
    return touchOffset;
}

double DragDropManager::CalcDragPreviewDistanceWithPoint(
    const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info)
{
    CHECK_NULL_RETURN(info.imageNode, 0.0);
    auto nodeOffset = info.imageNode->GetTransformRelativeOffset();
    auto renderContext = info.imageNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, 0.0);
    nodeOffset -= pixelMapOffset_;
    auto touchOffset = DragDropManager::GetTouchOffsetRelativeToSubwindow(Container::CurrentId(), x, y);
    // calculate distance, so need to pow 2.
    return sqrt(pow(nodeOffset.GetX() - touchOffset.GetX(), 2) + pow(nodeOffset.GetY() - touchOffset.GetY(), 2));
}

Offset DragDropManager::CalcDragMoveOffset(
    const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info)
{
    auto originPoint = info.originOffset;
    originPoint.SetX(originPoint.GetX() - pixelMapOffset_.GetX() +
        (info.originScale.x - info.scale) * info.width / 2.0f);
    originPoint.SetY(originPoint.GetY() - pixelMapOffset_.GetY() +
        (info.originScale.y - info.scale) * info.height / 2.0f);
    auto touchOffset = DragDropManager::GetTouchOffsetRelativeToSubwindow(Container::CurrentId(), x, y);
    Offset newOffset { touchOffset.GetX() - originPoint.GetX(), touchOffset.GetY() - originPoint.GetY() };
    return newOffset;
}

Offset DragDropManager::CalcContentTrationOffset(
    const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info)
{
    auto originPoint = info.originOffset;
    auto scalX = info.dragPreviewRect.Width() / info.originPreviewRect.Width() * info.scale;
    originPoint.SetX(originPoint.GetX() - pixelMapOffset_.GetX() + info.originPreviewRect.Width() * (1 - scalX));
    originPoint.SetY(originPoint.GetY() - pixelMapOffset_.GetY());
    auto touchOffset = DragDropManager::GetTouchOffsetRelativeToSubwindow(Container::CurrentId(), x, y);
    Offset newOffset { touchOffset.GetX() - originPoint.GetX(), touchOffset.GetY() - originPoint.GetY() };
    return newOffset;
}

Offset DragDropManager::CalculateNewOffset(
    const RefPtr<FrameNode>& frameNode, const GestureEvent& event, bool isDragStartPending)
{
    Offset newOffset = { 0, 0 };
    CHECK_NULL_RETURN(frameNode, newOffset);
    auto dragMoveLastPoint = GetDragMoveLastPointByCurrentPointer(event.GetPointerId());
    if (info_.sizeChangeEffect == DraggingSizeChangeEffect::DEFAULT && !info_.textNode) {
        newOffset =
            isDragStartPending
                ? CalcDragMoveOffset(PRESERVE_HEIGHT, static_cast<int32_t>(dragMoveLastPoint.GetX()),
                    static_cast<int32_t>(dragMoveLastPoint.GetY()), info_)
                : CalcDragMoveOffset(PRESERVE_HEIGHT, static_cast<int32_t>(event.GetGlobalLocation().GetX()),
                    static_cast<int32_t>(event.GetGlobalLocation().GetY()), info_);
    } else if (info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_TRANSITION ||
               info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION || info_.textNode) {
        newOffset =
            isDragStartPending
                ? CalcContentTrationOffset(PRESERVE_HEIGHT, static_cast<int32_t>(dragMoveLastPoint.GetX()),
                    static_cast<int32_t>(dragMoveLastPoint.GetY()), info_)
                : CalcContentTrationOffset(PRESERVE_HEIGHT, static_cast<int32_t>(event.GetGlobalLocation().GetX()),
                    static_cast<int32_t>(event.GetGlobalLocation().GetY()), info_);
    }
    return newOffset;
}

bool DragDropManager::UpdateDragMovePositionFinished(
    bool needDoDragMoveAnimate, bool isMenuShow, const Offset& newOffset, int32_t containerId)
{
    if (!isDragWithContextMenu_) {
        return false;
    }

    CHECK_NULL_RETURN(info_.imageNode, false);
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    SubwindowManager::GetInstance()->ContextMenuSwitchDragPreviewAnimation(info_.imageNode,
        OffsetF(newOffset.GetX(), newOffset.GetY()));
    if (!needDoDragMoveAnimate) {
        renderContext->UpdateTransformTranslate({ newOffset.GetX(), newOffset.GetY(), 0.0f });
        if (!isMenuShow) {
            TransDragWindowToDragFwk(containerId);
        }
        return true;
    }
    return false;
}

float DragDropManager::GetCurrentDistance(float x, float y)
{
    auto distance = sqrt(pow(curPointerOffset_.GetX() - x, 2) + pow(curPointerOffset_.GetY() - y, 2));
    CHECK_NULL_RETURN(info_.imageNode, distance);
    auto containerId = Container::CurrentId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
    CHECK_NULL_RETURN(subwindow, distance);
    auto overlayManager = subwindow->GetOverlayManager();
    auto gatherNodeCenter = DragDropFuncWrapper::GetPaintRectCenter(info_.imageNode);
    auto gatherDistance = CalcGatherNodeMaxDistanceWithPoint(overlayManager,
        gatherNodeCenter.GetX(), gatherNodeCenter.GetY());
    return std::max(distance, gatherDistance);
}

void DragDropManager::DoDragMoveAnimate(const DragPointerEvent& pointerEvent)
{
    bool needDoDragMoveAnimate = IsNeedDoDragMoveAnimate(pointerEvent);
    if (!needDoDragMoveAnimate) {
        return;
    }
    isPullMoveReceivedForCurrentDrag_ = true;
    CHECK_NULL_VOID(info_.imageNode);
    auto containerId = Container::CurrentId();
    auto x = pointerEvent.GetDisplayX();
    auto y = pointerEvent.GetDisplayY();
    if (CheckIsUIExtensionBoundary(x, y, containerId) || CheckIsFolderSubwindowBoundary(x, y, containerId)) {
        SetStartAnimation(false);
        TransDragWindowToDragFwk(containerId);
        return;
    }
    auto overlayManager = GetDragAnimationOverlayManager(containerId);
    CHECK_NULL_VOID(overlayManager);
    auto point = pointerEvent.GetPoint();
    Offset newOffset = { 0, 0 };
    if (info_.sizeChangeEffect == DraggingSizeChangeEffect::DEFAULT && !info_.textNode) {
        newOffset = CalcDragMoveOffset(PRESERVE_HEIGHT, point.GetX(), point.GetY(), info_);
    } else if (info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_TRANSITION ||
               info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION || info_.textNode) {
        newOffset = CalcContentTrationOffset(PRESERVE_HEIGHT, point.GetX(), point.GetY(), info_);
    }
    bool isMenuShow = overlayManager->IsMenuShow();
    if (UpdateDragMovePositionFinished(needDoDragMoveAnimate, isMenuShow, newOffset, containerId) ||
        !needDoDragMoveAnimate) {
        return;
    }
    DragMoveAnimation(newOffset, overlayManager, point);
}

void DragDropManager::DragMoveAnimation(
    const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager, Point point)
{
    auto containerId = Container::CurrentId();
    bool isMenuShow = overlayManager->IsMenuShow();
    AnimationOption option;
    auto springResponse =
        std::max(DEFAULT_SPRING_RESPONSE - DEL_SPRING_RESPONSE * allAnimationCnt_, MIN_SPRING_RESPONSE);
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(springResponse, 0.99f, 0.0f);
    constexpr int32_t animateDuration = 30;
    option.SetCurve(curve);
    option.SetDuration(animateDuration);
    bool dragWithContextMenu = isDragWithContextMenu_;
    AddNewDragAnimation();
    option.SetOnFinishEvent([weakManager = WeakClaim(this), containerId, dragWithContextMenu, isMenuShow,
                                x = point.GetX(), y = point.GetY()]() {
        auto dragDropManager = weakManager.Upgrade();
        CHECK_NULL_VOID(dragDropManager);
        if ((dragDropManager->IsAllAnimationFinished() ||
                dragDropManager->GetCurrentDistance(x, y) < MAX_DISTANCE_TO_PRE_POINTER) &&
            (!dragWithContextMenu || !isMenuShow) && dragDropManager->IsStartAnimationFInished()) {
            dragDropManager->SetStartAnimation(false);
            dragDropManager->TransDragWindowToDragFwk(containerId);
        }
    });

    if (info_.sizeChangeEffect == DraggingSizeChangeEffect::DEFAULT) {
        DragDropManager::DragMoveDefaultAnimation(overlayManager, info_, option, newOffset, point);
    } else if ((info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_TRANSITION ||
                   info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION)) {
        DragDropManager::DragMoveTransitionAnimation(overlayManager, info_, option, newOffset, point);
    }
}

void DragDropManager::DragMoveDefaultAnimation(const RefPtr<OverlayManager>& overlayManager,
    const DragPreviewInfo& info, AnimationOption option, const Offset& newOffset, Point point)
{
    auto renderContext = info_.textNode && info_.relativeContainerNode ? info_.relativeContainerNode->GetRenderContext()
                                                                       : info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto offset = OffsetF(point.GetX(), point.GetY());
    auto menuWrapperNode = GetMenuWrapperNodeFromDrag();
    auto menuPosition = overlayManager->CalculateMenuPosition(menuWrapperNode, offset);
    auto menuRenderContext = GetMenuRenderContextFromMenuWrapper(menuWrapperNode);
    AnimationUtils::Animate(
        option,
        [renderContext, localPoint = newOffset, info = info_, overlayManager, menuRenderContext, menuPosition]() {
            if (menuRenderContext && !menuPosition.NonOffset()) {
                menuRenderContext->UpdatePosition(
                    OffsetT<Dimension>(Dimension(menuPosition.GetX()), Dimension(menuPosition.GetY())));
            }
            renderContext->UpdateTransformTranslate({ localPoint.GetX(), localPoint.GetY(), 0.0f });
            UpdateGatherNodePosition(overlayManager, info.imageNode);
        },
        option.GetOnFinishEvent());
}

void DragDropManager::DragMoveTransitionAnimation(const RefPtr<OverlayManager>& overlayManager,
    const DragPreviewInfo& info, AnimationOption option, const Offset& newOffset, Point point)
{
    option.SetCurve(DRAG_TRANSITION_ANIMATION_CURVE);
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationUtils::Animate(
        option,
        [overlayManager, info, newOffset]() {
            CHECK_NULL_VOID(overlayManager);
            auto relativeContainerNodeRenderContext = info.relativeContainerNode->GetRenderContext();
            CHECK_NULL_VOID(relativeContainerNodeRenderContext);
            relativeContainerNodeRenderContext->UpdateTransformTranslate({ newOffset.GetX(), newOffset.GetY(), 0.0f });
            UpdateGatherNodePosition(overlayManager, info.imageNode);
        },
        option.GetOnFinishEvent());
}

void DragDropManager::UpdateDragPreviewScale()
{
    CHECK_NULL_VOID(info_.imageNode);
    if (IsNeedDisplayInSubwindow()) {
        return;
    }
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale({ info_.scale, info_.scale });
}

void DragDropManager::InitDragAnimationPointerEvent(const GestureEvent& event, bool isDragStartPending)
{
    if (isDragStartPending) {
        auto dragMoveLastPoint = GetDragMoveLastPointByCurrentPointer(event.GetPointerId());
        dragAnimationPointerEvent_ = DragPointerEvent(dragMoveLastPoint.GetX(),
            dragMoveLastPoint.GetY(), dragMoveLastPoint.GetScreenX(), dragMoveLastPoint.GetScreenY());
        return;
    }
    dragAnimationPointerEvent_ = DragPointerEvent(event.GetGlobalLocation().GetX(),
        event.GetGlobalLocation().GetY(), event.GetScreenLocation().GetX(), event.GetScreenLocation().GetY());
}

void DragDropManager::DoDragStartAnimation(const RefPtr<OverlayManager>& overlayManager, const GestureEvent& event,
    const RefPtr<GestureEventHub>& gestureHub, PreparedInfoForDrag& data)
{
    auto containerId = Container::CurrentId();
    auto deviceId = static_cast<int32_t>(event.GetDeviceId());
    if (deviceId == RESERVED_DEVICEID_1 || deviceId == RESERVED_DEVICEID_2) {
        isDragFwkShow_ = false;
        TAG_LOGI(AceLogTag::ACE_DRAG, "Do not need animation.");
        TransDragWindowToDragFwk(containerId);
        return;
    }
    CHECK_NULL_VOID(overlayManager);
    CHECK_NULL_VOID(gestureHub);
    bool isDragStartPending = DragDropGlobalController::GetInstance().GetAsyncDragCallback() != nullptr;
    if (!(GetDragPreviewInfo(overlayManager, info_, gestureHub, data)) ||
        (!IsNeedDisplayInSubwindow() && !data.isMenuShow && !isDragWithContextMenu_ && !isDragStartPending)) {
        if (isDragWithContextMenu_) {
            UpdateDragPreviewScale();
            isDragFwkShow_ = false;
        }
        return;
    }
    CHECK_NULL_VOID(info_.imageNode);
    isDragFwkShow_ = false;
    subwindowOverlayManager_ = overlayManager;
    InitDragAnimationPointerEvent(event, isDragStartPending);
    ResetPullMoveReceivedForCurrentDrag();
    Point point = { static_cast<int32_t>(event.GetGlobalLocation().GetX()),
        static_cast<int32_t>(event.GetGlobalLocation().GetY()) };
    auto frameNode = gestureHub->GetFrameNode();
    Offset newOffset = CalculateNewOffset(frameNode, event, isDragStartPending);
    curPointerOffset_ = { newOffset.GetX(), newOffset.GetY() };
    currentAnimationCnt_ = 0;
    allAnimationCnt_ = 0;
    isStartAnimationFinished_ = false;
    DragStartAnimation(newOffset, overlayManager, data, point);
}

void DragDropManager::DragStartAnimation(
    const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager, PreparedInfoForDrag& data, Point point)
{
    CHECK_NULL_VOID(info_.imageNode);
    auto containerId = Container::CurrentId();
    AnimationOption option;
    SetDragStartAnimationOption(option, containerId);
    AddNewDragStartAnimation();
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto callback = [weakManager = WeakClaim(this)](float rate) {
        auto dragDropManager = weakManager.Upgrade();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->SetDragStartAnimationRate(rate);
    };
    auto animateProperty = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(-1.0, std::move(callback));
    CHECK_NULL_VOID(animateProperty);
    renderContext->AttachNodeAnimatableProperty(animateProperty);
    animateProperty->Set(0.0f);
    dragStartAnimationRate_ = 0.0f;
    if (info_.sizeChangeEffect == DraggingSizeChangeEffect::DEFAULT) {
        //Default transition
        StartDragDefaultAnimation(option, newOffset, overlayManager, animateProperty, point);
    } else if (info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_TRANSITION ||
               info_.sizeChangeEffect == DraggingSizeChangeEffect::SIZE_CONTENT_TRANSITION) {
        StartDragTransitionAnimation(newOffset, option, overlayManager, animateProperty, point);
    }
}

void DragDropManager::SetDragStartAnimationOption(AnimationOption& option, int32_t containerId)
{
    const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.347f, 0.99f, 0.0f);
    constexpr int32_t animateDuration = 300;
    option.SetCurve(curve);
    option.SetDuration(animateDuration);
    option.SetOnFinishEvent([weakManager = WeakClaim(this), containerId]() {
        auto dragDropManager = weakManager.Upgrade();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->HandleStartDragAnimationFinish(containerId);
    });
}

void DragDropManager::HandleStartDragAnimationFinish(int32_t containerId)
{
    if (IsAllStartAnimationFinished()) {
        SetStartAnimation(true);
    }
    if (IsPullMoveReceivedForCurrentDrag()) {
        TransDragWindowToDragFwk(containerId);
    }
    auto overlayManager = GetDragAnimationOverlayManager(containerId);
    CHECK_NULL_VOID(overlayManager);
    auto gatherNode = overlayManager->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto info = overlayManager->GetGatherNodeChildrenInfo();
    int cnt = 0;
    for (auto iter = info.rbegin(); iter != info.rend(); iter++) {
        auto imageNode = (*iter).imageNode.Upgrade();
        if (cnt > 1) {
            gatherNode->RemoveChild(imageNode);
        }
        cnt++;
    }
}

void DragDropManager::StartDragDefaultAnimation(AnimationOption option, const Offset& newOffset,
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<NodeAnimatablePropertyFloat>& animateProperty,
    Point point)
{
    auto renderContext = info_.imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto animateCallback = [renderContext, info = info_, newOffset, overlayManager, animateProperty, point]() {
        CHECK_NULL_VOID(renderContext);
        DragAnimationHelper::UpdateStartAnimation(overlayManager, animateProperty, point, info, newOffset);
        if (!info.textNode) {
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale({ info.scale, info.scale });
            renderContext->UpdateTransformTranslate({ newOffset.GetX(), newOffset.GetY(), 0.0f });
            return;
        }
        CHECK_NULL_VOID(info.imageNode);
        auto imageLayoutProperty = info.imageNode->GetLayoutProperty();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(info.width * info.scale, DimensionUnit::PX),
            CalcLength(info.height * info.scale, DimensionUnit::PX) });
        info.relativeContainerNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    };
    if (info_.textNode) {
        option.SetCurve(DRAG_TRANSITION_ANIMATION_CURVE);
        auto pipeline = info_.relativeContainerNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->Animate(option, option.GetCurve(), animateCallback, option.GetOnFinishEvent());
    } else {
        AnimationUtils::Animate(option, animateCallback, option.GetOnFinishEvent());
    }
}

void DragDropManager::StartDragTransitionAnimation(const Offset& newOffset, AnimationOption option,
    const RefPtr<OverlayManager>& overlayManager, const RefPtr<NodeAnimatablePropertyFloat>& animateProperty,
    Point point)
{
    CHECK_NULL_VOID(info_.imageNode);
    option.SetCurve(DRAG_TRANSITION_ANIMATION_CURVE);
    auto callback = [relativeContainerNode = info_.relativeContainerNode, newOffset, info = info_, overlayManager,
                        animateProperty, point]() {
        DragAnimationHelper::UpdateStartAnimation(overlayManager, animateProperty, point, info, newOffset);
        CHECK_NULL_VOID(info.stackNode);
        auto stackLayoutProperty = info.stackNode->GetLayoutProperty();
        CHECK_NULL_VOID(stackLayoutProperty);
        stackLayoutProperty->UpdateUserDefinedIdealSize({ CalcLength(info.width * info.scale, DimensionUnit::PX),
            CalcLength(info.height * info.scale, DimensionUnit::PX) });
        auto stackContext = info.stackNode->GetContext();
        CHECK_NULL_VOID(stackContext);
        info.stackNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    };
    auto pipeline = info_.relativeContainerNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->Animate(option, option.GetCurve(), callback, option.GetOnFinishEvent());
}

void DragDropManager::NotifyEnterTextEditorArea()
{
    auto ret = InteractionInterface::GetInstance()->EnterTextEditorArea(true);
    if (ret != 0) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Fail to notify entering text editor erea.");
        return;
    }

    hasNotifiedTransformation_ = true;
}

void DragDropManager::FireOnEditableTextComponent(const RefPtr<FrameNode>& frameNode,
    DragEventType type)
{
    CHECK_NULL_VOID(frameNode);
    auto frameTag = frameNode->GetTag();
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    if (!IsEditableTextComponent(frameTag) || !(eventHub && eventHub->IsEnabled()) || !isDragFwkShow_) {
        return;
    }

    // When moving in an editable text component whithout animation, and has not notified msdp yet, notify msdp.
    if (type == DragEventType::MOVE && IsEditableTextComponent(frameTag) && isDragFwkShow_ &&
        !hasNotifiedTransformation_) {
        NotifyEnterTextEditorArea();
        return;
    }
    if (type != DragEventType::ENTER && type != DragEventType::LEAVE) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "It is an invalid drag type %{public}d", type);
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

    NotifyEnterTextEditorArea();
}

void DragDropManager::SetDragResult(
    const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragRet result = DragRet::DRAG_FAIL;
    switch (notifyMessage.result) {
        case DragRet::DRAG_SUCCESS:
            result = DragRet::DRAG_SUCCESS;
            break;
        case DragRet::DRAG_FAIL:
            result = DragRet::DRAG_FAIL;
            break;
        case DragRet::DRAG_CANCEL:
            result = DragRet::DRAG_CANCEL;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetResult(result);
}

void DragDropManager::SetDragBehavior(
    const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    switch (notifyMessage.dragBehavior) {
        case DragBehavior::COPY:
            dragBehavior = DragBehavior::COPY;
            break;
        case DragBehavior::MOVE:
            dragBehavior = DragBehavior::MOVE;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetDragBehavior(dragBehavior);
}

void DragDropManager::UpdateGatherNodeAttr(const RefPtr<OverlayManager>& overlayManager,
    const GatherAnimationInfo& info)
{
    CHECK_NULL_VOID(overlayManager);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
    BorderRadiusProperty borderRadius;
    if (info.borderRadius.has_value()) {
        borderRadius = info.borderRadius.value();
    }
    borderRadius.multiValued = false;
    int32_t cnt = static_cast<int>(gatherNodeChildrenInfo.size());
    auto scale = info.scale <= 0.0f ? 1.0f : info.scale;
    std::vector<std::pair<float, float>> props(cnt, { 0.0, 0.0 });
    if (cnt > 0) {
        props[cnt - FIRST_GATHER_PIXEL_MAP] = { FIRST_PIXELMAP_ANGLE, FIRST_PIXELMAP_OPACITY };
    }
    if (cnt > 1) {
        props[cnt - SECOND_GATHER_PIXEL_MAP] = { SECOND_PIXELMAP_ANGLE, SECOND_PIXELMAP_OPACITY };
    }
    for (int32_t i = 0; i < cnt; ++i) {
        auto imageNode = gatherNodeChildrenInfo[i].imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        auto& childInfo = gatherNodeChildrenInfo[i];
        auto updateScale = scale;
        if (((childInfo.width > info.width) || (childInfo.height > info.height)) &&
            !NearZero(childInfo.width) && !NearZero(childInfo.height)) {
            updateScale *= std::min(info.width / childInfo.width, info.height / childInfo.height);
        }
        imageContext->UpdateTransformScale({ updateScale, updateScale });
        imageContext->UpdateBorderRadius(borderRadius);
        imageContext->UpdateOpacity(props[i].second);
        Vector5F rotate = Vector5F(0.0f, 0.0f, 1.0f, props[i].first, 0.0f);
        imageContext->UpdateTransformRotate(rotate);
    }
}

void DragDropManager::UpdateGatherNodePosition(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(overlayManager);
    auto gatherNode = overlayManager->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto gatherNodeCenter = DragDropFuncWrapper::GetPaintRectCenterToScreen(imageNode);
    gatherNodeCenter -= DragDropFuncWrapper::GetCurrentWindowOffset(gatherNode->GetContextRefPtr());
    OffsetF offset;
    auto info = overlayManager->GetGatherNodeChildrenInfo();
    for (auto iter = info.rbegin(); iter != info.rend(); iter++) {
        auto& child = (*iter);
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        offset.SetX(gatherNodeCenter.GetX() - child.halfWidth);
        offset.SetY(gatherNodeCenter.GetY() - child.halfHeight);
        DragDropFuncWrapper::UpdateNodePositionToWindow(imageNode, offset);
    }
}

void DragDropManager::UpdateTextNodePosition(const RefPtr<FrameNode>& textNode, const Offset& localPoint)
{
    CHECK_NULL_VOID(textNode);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->UpdateTransformTranslate({ localPoint.GetX(), localPoint.GetY(), 0.0f });
}

double DragDropManager::CalcGatherNodeMaxDistanceWithPoint(const RefPtr<OverlayManager>& overlayManager,
    int32_t x, int32_t y)
{
    CHECK_NULL_RETURN(overlayManager, 0.0f);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
    double maxDistance = 0.0;
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_RETURN(imageNode, 0.0f);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_RETURN(imageContext, 0.0f);
        auto renderPosition = imageContext->GetPropertyOfPosition();
        double dis = sqrt(pow(renderPosition.GetX() + child.halfWidth - x, SQUARE_NUMBER) +
            pow(renderPosition.GetY() + child.halfHeight - y, SQUARE_NUMBER));
        maxDistance = std::max(maxDistance, dis);
    }
    return maxDistance;
}

bool DragDropManager::IsNeedDisplayInSubwindow()
{
    if (IsNeedScaleDragPreview()) {
        return true;
    }
    auto overlayManager = GetDragAnimationOverlayManager(Container::CurrentId());
    CHECK_NULL_RETURN(overlayManager, false);
    auto gatherNode = overlayManager->GetGatherNode();
    return gatherNode != nullptr;
}

void DragDropManager::PushGatherPixelMap(const RefPtr<PixelMap>& pixelMap)
{
    gatherPixelMaps_.push_back(pixelMap);
}

void DragDropManager::GetGatherPixelMap(
    DragDataCore& dragData, float scale, float previewWidth, float previewHeight)
{
    for (const auto& gatherPixelMap : gatherPixelMaps_) {
        RefPtr<PixelMap> pixelMapDuplicated = gatherPixelMap;
#if defined(PIXEL_MAP_SUPPORTED)
        pixelMapDuplicated = PixelMap::CopyPixelMap(gatherPixelMap);
        if (!pixelMapDuplicated) {
            TAG_LOGW(AceLogTag::ACE_DRAG, "Copy PixelMap is failure!");
            pixelMapDuplicated = gatherPixelMap;
        }
#endif
        CHECK_NULL_VOID(pixelMapDuplicated);
        auto width = pixelMapDuplicated->GetWidth() * scale;
        auto height = pixelMapDuplicated->GetHeight() * scale;
        auto updateScale = scale;
        if (((width > previewWidth) || (height > previewHeight)) && !NearZero(width) && !NearZero(height)) {
            updateScale *= std::min(previewWidth / width, previewHeight / height);
        }
        pixelMapDuplicated->Scale(updateScale, updateScale, AceAntiAliasingOption::HIGH);
        dragData.shadowInfos.push_back({pixelMapDuplicated, 0.0f, 0.0f});
    }
    gatherPixelMaps_.clear();
    return;
}

void DragDropManager::ResetDragDrop(int32_t windowId, const Point& point)
{
    DragDropRet dragDropRet { DragRet::DRAG_FAIL, isMouseDragged_, windowId, DragBehavior::UNKNOWN };
    HideDragPreviewOverlay();
    ClearVelocityInfo();
    ResetDragDropStatus(point, dragDropRet, windowId);
    dragCursorStyleCore_ = DragCursorStyleCore::DEFAULT;
}

void DragDropManager::FireOnDragLeave(
    const RefPtr<FrameNode>& preTargetFrameNode, const DragPointerEvent& pointerEvent, const std::string& extraInfo)
{
    auto point = pointerEvent.GetPoint();
    if (preTargetFrameNode) {
        auto preRect = preTargetFrameNode->GetTransformRectRelativeToWindow();
        // If the point is out of the pre node, it means we are totally inside a new node, notify leave anyway
        if (!preRect.IsInnerRegion(PointF(static_cast<float>(point.GetX()), static_cast<float>(point.GetY())))) {
            FireOnDragEvent(preTargetFrameNode, pointerEvent, DragEventType::LEAVE, extraInfo);
            return;
        }

        // If reach here, it means we are entering one new node's area, but without leaving the area of the pre
        // one, this usually happens when moving from parent into its child.
        // Check the configuration to decide the notify to parent node.
        if (eventStrictReportingEnabled_) {
            FireOnDragEvent(preTargetFrameNode_, pointerEvent, DragEventType::LEAVE, extraInfo);
        }
    }
}

bool DragDropManager::IsUIExtensionShowPlaceholder(const RefPtr<NG::UINode>& node)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_RETURN(node, true);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, true);
    auto manager = pipeline->GetUIExtensionManager();
    CHECK_NULL_RETURN(manager, true);
    return manager->IsShowPlaceholder(node->GetId());
#endif
    return true;
}

void DragDropManager::UpdateDragMovePosition(const NG::OffsetF& offset, bool isRedragStart)
{
    if (isRedragStart) {
        ResetContextMenuRedragPosition();
    }
    lastDragMovePosition_ = dragMovePosition_;
    dragMovePosition_ = offset;
    if (lastDragMovePosition_.NonOffset()) {
        return;
    }
    dragTotalMovePosition_ += (dragMovePosition_ - lastDragMovePosition_);
}

bool DragDropManager::IsUIExtensionComponent(const RefPtr<NG::UINode>& node)
{
    CHECK_NULL_RETURN(node, false);
    return (V2::UI_EXTENSION_COMPONENT_ETS_TAG == node->GetTag() || V2::EMBEDDED_COMPONENT_ETS_TAG == node->GetTag()) &&
           (!IsUIExtensionShowPlaceholder(node));
}

void DragDropManager::HandleUIExtensionDragEvent(
    const RefPtr<FrameNode>& frameNode, const DragPointerEvent& pointerEvent, DragEventType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);

    auto dragEvent = pointerEvent;
    if (type == DragEventType::ENTER) {
        dragEvent.action = PointerAction::PULL_IN_WINDOW;
    } else if (type == DragEventType::LEAVE) {
        dragEvent.action = PointerAction::PULL_OUT_WINDOW;
    } else if (type == DragEventType::PULL_CANCEL) {
        dragEvent.action = PointerAction::PULL_CANCEL;
    }
    pattern->HandleDragEvent(dragEvent);
}

RectF DragDropManager::GetMenuPreviewRect()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, RectF());
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, RectF());
    auto menuWrapperNode = dragDropManager->GetMenuWrapperNode();
    CHECK_NULL_RETURN(menuWrapperNode, RectF());
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, RectF());
    auto menuPreview = menuWrapperPattern->GetPreview();
    CHECK_NULL_RETURN(menuPreview, RectF());
    auto previewPaintRect = DragDropFuncWrapper::GetPaintRectToScreen(menuPreview);
    previewPaintRect -= DragDropFuncWrapper::GetCurrentWindowOffset(pipelineContext);
    return previewPaintRect;
}

double DragDropManager::GetMaxWidthBaseOnGridSystem(const RefPtr<PipelineBase>& pipeline)
{
    auto context = DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(context, -1.0f);
    auto dragDropMgr = context->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropMgr, -1.0f);
    auto& columnInfo = dragDropMgr->columnInfo_;
    if (!columnInfo) {
        columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::DRAG_PANEL);
        auto gridContainer = columnInfo->GetParent();
        if (gridContainer) {
            auto rootWidth = context->GetRootWidth();
            if (LessOrEqual(rootWidth, 0.0)) {
                auto mainPipeline = PipelineContext::GetMainPipelineContext();
                rootWidth = GridSystemManager::GetInstance().GetScreenWidth(mainPipeline);
            }
            // cannot handle multi-screen
            gridContainer->BuildColumnWidth(rootWidth);
        }
        dragDropMgr->columnInfo_ = columnInfo;
    }

    auto gridSizeType = GridSystemManager::GetInstance().GetCurrentSize();
    if (gridSizeType > GridSizeType::LG) {
        gridSizeType = GridSizeType::LG;
    }
    if (gridSizeType < GridSizeType::SM) {
        gridSizeType = GridSizeType::SM;
    }
    auto columns = columnInfo->GetColumns(gridSizeType);
    double maxWidth = columnInfo->GetWidth(columns);
    return maxWidth;
}

std::shared_ptr<ScaleDataInfo> DragDropManager::GetScaleInfo(float width, float height, bool textDraggable)
{
    auto scaleDataInfo = std::make_shared<ScaleDataInfo>();
    CHECK_NULL_RETURN(scaleDataInfo, nullptr);
    scaleDataInfo->shortSide = fmin(SystemProperties::GetDeviceHeight(), SystemProperties::GetDeviceWidth());
    auto shortSide = PipelineBase::Px2VpWithCurrentDensity(scaleDataInfo->shortSide);
    if (shortSide <= DEVICE_TYPE_UNKOWN) {
        return scaleDataInfo;
    } else if (shortSide <= DEVICE_TYPE_SMALL) {
        scaleDataInfo = DragDropManager::CalculateScale(width, height,
            textDraggable ? scaleDataInfo->shortSide : scaleDataInfo->shortSide / SCALE_TYPE_FIRST,
            scaleDataInfo->shortSide / SCALE_TYPE_FIRST);
    } else if (shortSide <= DEVICE_TYPE_MEDIUM) {
        scaleDataInfo = CalculateScale(width, height,
            textDraggable ? scaleDataInfo->shortSide / SCALE_TYPE_FIRST : scaleDataInfo->shortSide / SCALE_TYPE_THIRD,
            scaleDataInfo->shortSide / SCALE_TYPE_THIRD);
    } else {
        scaleDataInfo = CalculateScale(width, height,
            textDraggable ? scaleDataInfo->shortSide * SCALE_TYPE_FIRST / SCALE_TYPE_SECOND
                          : scaleDataInfo->shortSide / SCALE_TYPE_SECOND,
            scaleDataInfo->shortSide / SCALE_TYPE_SECOND);
    }
    return scaleDataInfo;
}

std::shared_ptr<ScaleDataInfo> DragDropManager::CalculateScale(
    float width, float height, float widthLimit, float heightLimit)
{
    auto scaleDataInfo = std::make_shared<ScaleDataInfo>();
    CHECK_NULL_RETURN(scaleDataInfo, nullptr);
    if ((width > 0 && height > 0) && (width > widthLimit || height > heightLimit)) {
        scaleDataInfo->scale = fmin(widthLimit / width, heightLimit / height);
        scaleDataInfo->isNeedScale = true;
    }
    return scaleDataInfo;
}

const RefPtr<NG::OverlayManager> DragDropManager::GetDragAnimationOverlayManager(int32_t containerId)
{
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(containerId) : containerId, SubwindowType::TYPE_MENU);
    CHECK_NULL_RETURN(subwindow, nullptr);
    return subwindow->GetOverlayManager();
}

void DragDropManager::RemoveDragFrameNode(int32_t id)
{
    dragFrameNodes_.erase(id);
    gridDragFrameNodes_.erase(id);
    listDragFrameNodes_.erase(id);
    textFieldDragFrameNodes_.erase(id);
}

void DragDropManager::SetIsDragged(bool isDragged)
{
    if (isDragged && isDragged_ != isDragged && notifyInDraggedCallback_) {
        notifyInDraggedCallback_();
    }
    isDragged_ = isDragged;
}

void DragDropManager::RegisterDragStatusListener(int32_t nodeId, const WeakPtr<FrameNode>& node)
{
    auto ret = nodesForDragNotify_.try_emplace(nodeId, node);
    if (!ret.second) {
        nodesForDragNotify_[nodeId] = node;
    }
}

void DragDropManager::RegisterPullEventListener(
    int32_t uniqueIdentify, std::function<void(const DragPointerEvent&)> callback)
{
    pullEventListener_[uniqueIdentify] = callback;
}

void DragDropManager::UnRegisterPullEventListener(int32_t uniqueIdentify)
{
    auto it = pullEventListener_.find(uniqueIdentify);
    if (it != pullEventListener_.end()) {
        pullEventListener_.erase(it);
    }
}

void DragDropManager::NotifyPullEventListener(const DragPointerEvent& pointerEvent)
{
    if (pullEventListener_.empty()) {
        return;
    }
    for (const auto& pair : pullEventListener_) {
        if (pair.second) {
            pair.second(pointerEvent);
        }
    }
}

bool DragDropManager::IsDraggingPressed(int32_t currentPointerId) const
{
    if (currentPointerId_ == currentPointerId) {
        return draggingPressedState_;
    }
    return false;
}

void DragDropManager::ResetContextMenuDragPosition()
{
    dragMovePosition_.Reset();
    lastDragMovePosition_.Reset();
    dragTotalMovePosition_.Reset();
}

void DragDropManager::ResetContextMenuRedragPosition()
{
    dragMovePosition_.Reset();
    lastDragMovePosition_.Reset();
}

void DragDropManager::AddNewDragAnimation()
{
    currentAnimationCnt_++;
    allAnimationCnt_++;
}

void DragDropManager::AddNewDragStartAnimation()
{
    currentStartAnimationCnt_++;
    allStartAnimationCnt_++;
}

bool DragDropManager::IsAllAnimationFinished()
{
    currentAnimationCnt_--;
    return currentAnimationCnt_ == 0;
}

bool DragDropManager::IsAllStartAnimationFinished()
{
    currentStartAnimationCnt_--;
    return currentStartAnimationCnt_ == 0;
}

bool DragDropManager::CheckIsNewDrag(const DragPointerEvent& pointerEvent) const
{
    return (pointerEvent.pullId != -1) && (pointerEvent.pullId != currentPullId_);
}

void DragDropManager::RequireSummaryIfNecessary(const DragPointerEvent& pointerEvent)
{
    if (CheckIsNewDrag(pointerEvent)) {
        currentPullId_ = pointerEvent.pullId;
        RequireSummary();
    }
}

bool DragDropManager::IsAnyDraggableHit(const RefPtr<PipelineBase>& pipeline, int32_t pointId)
{
    if (isAnyDraggableHit_) {
        return true;
    }

    auto pipelineContext = AceType::DynamicCast<PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, false);
    auto eventManager = pipelineContext->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    auto touchTestResults = eventManager->touchTestResults_;
    const auto iter = touchTestResults.find(pointId);
    if (iter == touchTestResults.end() || iter->second.empty()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "touch test result is empty.");
        return false;
    }
    for (const auto& touchTestResult : iter->second) {
        auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(touchTestResult);
        if (recognizer) {
            continue;
        }
        auto node = touchTestResult->GetAttachedNode().Upgrade();
        CHECK_NULL_RETURN(node, false);
        if (IsUIExtensionComponent(node)) {
            return true;
        }
    }
    return false;
}

int32_t DragDropManager::CancelUDMFDataLoading(const std::string& key)
{
    return UdmfClient::GetInstance()->Cancel(key);
}

bool DragDropManager::CheckIsFolderSubwindowBoundary(float x, float y, int32_t instanceId)
{
    if (!SystemProperties::IsSuperFoldDisplayDevice() || NearZero(info_.scale)) {
        return false;
    }
    auto mainContainerId = instanceId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(instanceId) : instanceId;
    auto container = Container::GetContainer(mainContainerId);
    CHECK_NULL_RETURN(container, false);
    if (container->GetCurrentFoldStatus() == FoldStatus::EXPAND) {
        return false;
    }
    auto isCrossWindow = container->IsCrossAxisWindow();
    auto isSceneBoard = container->IsSceneBoardWindow();
    if (isCrossWindow || isSceneBoard) {
        return false;
    }
    auto subwindow = SubwindowManager::GetInstance()->GetCurrentWindow();
    CHECK_NULL_RETURN(subwindow, false);
    auto rect = subwindow->GetWindowRect();
    auto scale = dragStartAnimationRate_ * (info_.scale - info_.originScale.y) + info_.originScale.y;
    OffsetF pixelMapOffset = pixelMapOffset_ / info_.scale * scale;
    float top = y + pixelMapOffset.GetY();
    float bottom = y + pixelMapOffset.GetY() + info_.height * scale;
    float distance = std::min(top - rect.Top(), rect.Bottom() - bottom);
    return distance < MIN_FOLDER_SUBWINDOW_BOUNDARY_DISTANCE;
}

bool DragDropManager::CheckIsUIExtensionBoundary(float x, float y, int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    if (!container->IsUIExtensionWindow()) {
        return false;
    }
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto rect = pipeline->GetCurrentWindowRect();
    auto distance = std::min(std::min(x - rect.Left(), rect.Right() - x),
        std::min(y - rect.Top(), rect.Bottom() - y));
    return distance < MIN_UI_EXTENSION_BOUNDARY_DISTANCE;
}
} // namespace OHOS::Ace::NG
