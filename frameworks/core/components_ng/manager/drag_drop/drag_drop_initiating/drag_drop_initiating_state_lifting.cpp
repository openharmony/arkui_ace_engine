/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_lifting.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/gestures/drag_event.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 300;
constexpr int32_t PIXELMAP_ANIMATION_TIME = 800;
constexpr float SCALE_NUMBER = 0.95;
constexpr float PIXELMAP_DRAG_SCALE_MULTIPLE = 1.05f;
constexpr float MENU_DRAG_SCALE = 0.05f;
constexpr float SPRING_RESPONSE = 0.416f;
constexpr float SPRING_DAMPING_FRACTION = 0.73f;
} // namespace

void DragDropInitiatingStateLifting::HandlePreviewLongPressOnActionCancel(const GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "Preview long press event has been canceled.");
    HideEventColumn();
    HidePixelMap(true, 0, 0, false);
}

void DragDropInitiatingStateLifting::HandleOnDragStart(RefPtr<FrameNode> frameNode, const GestureEvent& info)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (!CheckStatusForPanActionBegin(frameNode, info)) {
        return;
    }
    dragDropManager->ResetDragging(DragDropMgrState::ABOUT_TO_PREVIEW);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->GetTextDraggable()) {
        HandleTextDragStart(frameNode, info);
        return;
    }
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    DragDropFuncWrapper::RecordMenuWrapperNodeForDrag(frameNode->GetId());
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        HideEventColumn();
        frameNode->SetOptionsAfterApplied(params.optionsAfterApplied);
    } else {
        frameNode->MarkModifyDone();
        dragDropManager->SetIsShowBadgeAnimation(true);
        HideEventColumn();
        HidePixelMap(true, info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
        UpdateDragPreviewOptionFromModifier();
    }
    auto gestureEvent = info;
    gestureHub->HandleOnDragStart(gestureEvent);
}

void DragDropInitiatingStateLifting::HandlePanOnActionStart(const GestureEvent& info)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    HandleOnDragStart(frameNode, info);
}

void DragDropInitiatingStateLifting::HandlePanOnReject()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    if (manager->IsGatherWithMenu() || !params.hasGatherNode) {
        return;
    }
    manager->RemoveGatherNodeWithAnimation();
}

void DragDropInitiatingStateLifting::HandleSequenceOnActionCancel(const GestureEvent& info)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!gestureHub->GetBindMenuStatus().IsNotNeedShowPreview()) {
        machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
    }
}

void DragDropInitiatingStateLifting::HandleTouchEvent(const TouchEvent& touchEvent)
{
    if (touchEvent.type == TouchType::MOVE) {
        auto point = Point(touchEvent.x, touchEvent.y, touchEvent.screenX, touchEvent.screenY);
        DoDragDampingAnimation(point, touchEvent.id);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->UpdatePointInfoForFinger(touchEvent.id, point);
    }
}

void DragDropInitiatingStateLifting::HandlePanOnActionEnd(const GestureEvent& info)
{
    OnActionEnd(info);
}

void DragDropInitiatingStateLifting::HandleReStartDrag(const GestureEvent& info)
{
    if (info.GetOriginUIInputEventType() == UIInputEventType::AXIS) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "Trigger drag pan event by touch transformed from axis");
        return;
    }
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    HandleOnDragStart(frameNode, info);
}

void DragDropInitiatingStateLifting::DoDragDampingAnimation(const Point& point, int32_t pointerId, bool isReDragStart)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (dragDropManager->IsAboutToPreview() || dragDropManager->IsDragging() ||
        !dragDropManager->IsSameDraggingPointer(pointerId)) {
        return;
    }
    auto startPoint = dragDropManager->GetDragDampStartPoint();
    // get the number with VP unit
    auto distance = SystemProperties::GetDragStartPanDistanceThreshold();
    auto dragPanDistance = Dimension(distance, DimensionUnit::VP).ConvertToPx();
    auto dragStartDampingRatio = SystemProperties::GetDragStartDampingRatio();
    auto dragTotalDistance = dragDropManager->GetUpdateDragMovePosition();
    auto delta = Offset(dragTotalDistance.GetX(), dragTotalDistance.GetY());
    // delta.GetDistance(): pixelMap real move distance
    if (delta.GetDistance() > dragPanDistance * dragStartDampingRatio) {
        if (dragDropManager->GetDampingOverflowCount() == 1) {
            return;
        }
        dragDropManager->SetDampingOverflowCount();
    }
    // linear decrease for menu scale from 100% to 95% within drag damping range
    auto previewMenuScale = 1.0f - delta.GetDistance() / (dragPanDistance * dragStartDampingRatio) * MENU_DRAG_SCALE;
    auto updateOffset = OffsetF(dragStartDampingRatio * point.GetX() + (1 - dragStartDampingRatio) * startPoint.GetX(),
        dragStartDampingRatio * point.GetY() + (1 - dragStartDampingRatio) * startPoint.GetY());
    auto menuWrapperNode = dragDropManager->GetMenuWrapperNode();
    auto menuWrapperId = menuWrapperNode ? menuWrapperNode->GetId() : -1;
    SubwindowManager::GetInstance()->UpdateHideMenuOffsetNG(updateOffset, previewMenuScale, false, menuWrapperId);
    dragDropManager->UpdateDragMovePosition(updateOffset, false);
    SubwindowManager::GetInstance()->UpdatePreviewPosition();
}

bool DragDropInitiatingStateLifting::CheckDoShowPreview(const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(manager, false);
    if (manager->GetHasPixelMap()) {
        return false;
    }
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (dragDropManager->IsAboutToPreview() || dragDropManager->IsDragging() ||
        dragDropManager->IsDragNodeNeedClean()) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "No need to show drag preview, is about to preview: %{public}d,"
            "is dragging: %{public}d, is need clean drag node: %{public}d",
            dragDropManager->IsAboutToPreview(), dragDropManager->IsDragging(), dragDropManager->IsDragNodeNeedClean());
        return false;
    }
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    if (gestureHub->GetBindMenuStatus().IsNotNeedShowPreview() || isMenuShow) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Not need to show drag preview because of bind context menu");
        return false;
    }
    if (!frameNode->GetDragPreviewOption().isDragPreviewEnabled) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Not need to show drag preview because disable drag preview");
        return false;
    }
    return true;
}

void DragDropInitiatingStateLifting::SetScaleAnimation(int32_t fingerId)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto columnNode = manager->GetPixelMapNode();
    CHECK_NULL_VOID(columnNode);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    CHECK_NULL_VOID(imageNode);
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_RESPONSE, SPRING_DAMPING_FRACTION, 0);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_TIME);
    option.SetCurve(motion);
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    option.SetOnFinishEvent([id = Container::CurrentId(), pointerId = fingerId]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        if (dragDropManager->IsDraggingPressed(pointerId)) {
            DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
        }
    });
    AnimationUtils::Animate(
        option,
        [imageContext]() {
            imageContext->UpdateTransformScale({ PIXELMAP_DRAG_SCALE_MULTIPLE, PIXELMAP_DRAG_SCALE_MULTIPLE });
        },
        option.GetOnFinishEvent());
}

void DragDropInitiatingStateLifting::SetPixelMap()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    RefPtr<PixelMap> pixelMap = gestureHub->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    // create imageNode
    auto imageNode = DragAnimationHelper::CreateImageNode(pixelMap);
    CHECK_NULL_VOID(imageNode);
    imageNode->SetDragPreviewOptions(frameNode->GetDragPreviewOption());
    // create columnNode
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    columnNode->AddChild(imageNode);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    hub->SetPixelMap(gestureHub->GetPixelMap());
    // mount to rootNode
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        auto windowScene = manager->FindWindowScene(frameNode);
        manager->MountPixelMapToWindowScene(columnNode, windowScene);
    } else {
        manager->MountPixelMapToRootNode(columnNode);
    }
    imageNode->MarkModifyDone();
    imageNode->SetLayoutDirtyMarked(true);
    imageNode->SetActive(true);
    auto context = imageNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(imageNode);
    }
    DragEventActuator::UpdateDragNodePosition(imageNode, frameNode, width, height);
    ShowPixelMapAnimation(imageNode, frameNode);
    DragEventActuator::SetPreviewDefaultAnimateProperty(imageNode);
}

void DragDropInitiatingStateLifting::ShowPixelMapAnimation(
    const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    CHECK_NULL_VOID(frameNode);

    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    frameNode->SetOptionsAfterApplied(params.optionsAfterApplied);
    DragAnimationHelper::SetImageNodeInitAttr(frameNode, imageNode);

    auto previewOption = frameNode->GetDragPreviewOption();
    if (params.isNeedGather && previewOption.defaultAnimationBeforeLifting) {
        imageContext->UpdateTransformScale({ SCALE_NUMBER, SCALE_NUMBER });
    }

    // pixel map animation
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent(
        [imageNode, frameNode]() { DragAnimationHelper::SetImageNodeFinishAttr(frameNode, imageNode); });

    AnimationUtils::Animate(
        option,
        [imageNode, weak = WeakClaim(RawPtr(frameNode)), isNeedGather = params.isNeedGather]() mutable {
            auto frameNode = weak.Upgrade();
            if (isNeedGather) {
                DragDropFuncWrapper::ResetNode(frameNode);
            }
            DragDropFuncWrapper::ApplyNewestOptionExecutedFromModifierToNode(frameNode, imageNode);
        },
        option.GetOnFinishEvent());
}

void DragDropInitiatingStateLifting::SetGatherAnimation(const RefPtr<PipelineBase>& context)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    if (!params.isNeedGather) {
        return;
    }
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto columnNode = manager->GetPixelMapNode();
    CHECK_NULL_VOID(columnNode);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetFirstChild());
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    DragAnimationHelper::HideDragNodeCopy(manager);
    DragAnimationHelper::PlayGatherAnimation(imageNode, manager);
    DragAnimationHelper::ShowPreviewBadgeAnimation(gestureHub, manager);
}

void DragDropInitiatingStateLifting::SetEventColumn()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (manager->GetHasEvent()) {
        return;
    }
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto geometryNode = rootNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto width = geometryNode->GetFrameSize().Width();
    auto height = geometryNode->GetFrameSize().Height();
    // create columnNode
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto props = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
    props->UpdateUserDefinedIdealSize(targetSize);
    BindClickEvent(columnNode);
    columnNode->MarkModifyDone();
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        auto machine = GetStateMachine();
        CHECK_NULL_VOID(machine);
        auto params = machine->GetDragDropInitiatingParams();
        auto frameNode = params.frameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto windowScene = manager->FindWindowScene(frameNode);
        manager->MountEventToWindowScene(columnNode, windowScene);
    } else {
        manager->MountEventToRootNode(columnNode);
    }
}

void DragDropInitiatingStateLifting::BindClickEvent(const RefPtr<FrameNode>& columnNode)
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto stateLift = weak.Upgrade();
        CHECK_NULL_VOID(stateLift);
        auto machine = stateLift->GetStateMachine();
        CHECK_NULL_VOID(machine);
        machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
    };
    auto columnGestureHub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(columnGestureHub);
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(callback));
    columnGestureHub->AddClickEvent(clickListener);
    columnGestureHub->SetHitTestMode(HitTestMode::HTMBLOCK);
}

void DragDropInitiatingStateLifting::Init(int32_t currentState)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (currentState < static_cast<int32_t>(DragDropInitiatingStatus::PRESS) && !gestureHub->GetTextDraggable()) {
        UpdateDragPreviewOptionFromModifier();
    }
    if (!CheckDoShowPreview(frameNode)) {
        return;
    }
    if (gestureHub->GetTextDraggable()) {
        if (gestureHub->GetIsTextDraggable()) {
            SetTextAnimation();
            SetEventColumn();
        }
        return;
    }
    if (!IsAllowedDrag()) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragDrop long press and info received");
        return;
    }
    DragDropGlobalController::GetInstance().SetPrepareDragFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDraggingPointer(params.idleFingerId);
    dragDropManager->SetDraggingPressedState(true);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    if (!dragPreviewOption.isLiftingDisabled) {
        SetPixelMap();
        SetGatherAnimation(pipeline);
        SetScaleAnimation(params.idleFingerId);
    }
    SetEventColumn();
    pipeline->FlushSyncGeometryNodeTasks();
}

void OHOS::Ace::NG::DragDropInitiatingStateLifting::SetTextAnimation()
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start set textAnimation.");
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    auto textBase = frameNode->GetPattern<TextBase>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(textBase);
    if (!textBase->BetweenSelectedPosition(params.touchOffset)) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Position is between selected position, stop set text animation.");
        return;
    }
    auto isHandlesShow = pattern->IsHandlesShow();
    auto dragNode = pattern->MoveDragNode();
    CHECK_NULL_VOID(dragNode);
    dragNode->SetDragPreviewOptions(frameNode->GetDragPreviewOption());
    // create columnNode
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    columnNode->AddChild(dragNode);
    auto columnRenderContext = columnNode->GetRenderContext();
    if (columnRenderContext) {
        columnRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));
    }
    // mount to rootNode
    manager->MountPixelMapToRootNode(columnNode);
    auto textDragPattern = dragNode->GetPattern<TextDragPattern>();
    CHECK_NULL_VOID(textDragPattern);
    auto modifier = textDragPattern->GetOverlayModifier();
    CHECK_NULL_VOID(modifier);
    modifier->UpdateHandlesShowFlag(isHandlesShow);
    auto renderContext = dragNode->GetRenderContext();
    if (renderContext) {
        params.preScaledPixelMap = renderContext->GetThumbnailPixelMap();
    }
    modifier->StartFloatingAnimate();
    pattern->OnDragNodeFloating();
    pattern->CloseHandleAndSelect();
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent set text animation success.");
}

void DragDropInitiatingStateLifting::HandlePreDragStatus(const PreDragStatus preDragStatus)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    if (!params.isNeedGather) {
        return;
    }
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (preDragStatus == PreDragStatus::PREVIEW_LIFT_FINISHED) {
        DragDropFuncWrapper::ResetNode(frameNode);
    }
}
} // namespace OHOS::Ace::NG
