/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/drag_event.h"

#include "base/log/ace_trace.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/container.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/constants.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"

#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#endif // WEB_SUPPORTED

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PAN_FINGER = 1;
constexpr double PAN_DISTANCE = 5.0;
constexpr int32_t LONG_PRESS_DURATION = 500;
constexpr int32_t PREVIEW_LONG_PRESS_RECONGNIZER = 800;
constexpr Dimension FILTER_VALUE(0.0f);
constexpr float PIXELMAP_DRAG_SCALE_MULTIPLE = 1.05f;
constexpr int32_t PIXELMAP_ANIMATION_TIME = 800;
constexpr float SCALE_NUMBER = 0.95f;
constexpr int32_t FILTER_TIMES = 250;
constexpr int32_t PRE_DRAG_TIMER_DEADLINE = 50; // 50ms
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 300;
constexpr float SPRING_RESPONSE = 0.416f;
constexpr float SPRING_DAMPING_FRACTION = 0.73f;
constexpr Dimension PIXELMAP_BORDER_RADIUS = 16.0_vp;
constexpr Dimension PREVIEW_BORDER_RADIUS = 12.0_vp;
constexpr float BLUR_SIGMA_SCALE = 0.57735f;
constexpr float SCALE_HALF = 0.5f;
constexpr float DEFAULT_ANIMATION_SCALE = 0.95f;
constexpr Dimension BADGE_RELATIVE_OFFSET = 8.0_vp;
constexpr float DEFAULT_OPACITY = 0.95f;
constexpr float MIN_OPACITY { 0.0f };
constexpr float MAX_OPACITY { 1.0f };
constexpr float MENU_DRAG_SCALE = 0.05f;
#if defined(PIXEL_MAP_SUPPORTED)
constexpr int32_t CREATE_PIXELMAP_TIME = 80;
#endif
} // namespace

DragEventActuator::DragEventActuator(
    const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction, int32_t fingers, float distance)
    : gestureEventHub_(gestureEventHub), direction_(direction), fingers_(fingers), distance_(distance)
{
    if (fingers_ < PAN_FINGER) {
        fingers_ = PAN_FINGER;
    }

    if (LessOrEqual(distance_, PAN_DISTANCE)) {
        distance_ = PAN_DISTANCE;
    }

    panRecognizer_ = MakeRefPtr<PanRecognizer>(fingers_, direction_, distance_);
    panRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, fingers_, false, true);
    longPressRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(PREVIEW_LONG_PRESS_RECONGNIZER, fingers_, false, true);
    previewLongPressRecognizer_->SetGestureInfo(
        MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_->SetThumbnailDeadline(PRE_DRAG_TIMER_DEADLINE);
    isNotInPreviewState_ = false;
}

void DragEventActuator::StartDragTaskForWeb(const GestureEvent& info)
{
    auto gestureInfo = const_cast<GestureEvent&>(info);
    if (actionStart_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop start drag task for web success");
        actionStart_(gestureInfo);
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "DragDrop start drag task for web failed,"
            "because actionStart function is null");
    }
}

void DragEventActuator::StartLongPressActionForWeb(bool isFloatImage)
{
    TAG_LOGW(AceLogTag::ACE_WEB, "StartLongPressActionForWeb isFloatImage:%{public}d", isFloatImage);
    isFloatImage_ = isFloatImage;
    if (!isReceivedLongPress_) {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop not received long press action,"
            "don't start long press action for web");
        return;
    }
    if (longPressUpdate_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop call long press update,"
            "after update set false again");
        longPressUpdate_(longPressInfo_);
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "DragDrop long press update null");
    }
    isReceivedLongPress_ = false;
}

void DragEventActuator::CancelDragForWeb()
{
    if (actionCancel_) {
        TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop call action cancel success");
        actionCancel_();
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "DragDrop action cancel null");
    }
}

/**
 * Do some nessessary check before returning the gesture recognizer collection result
 * to parent during the hittest process. For example, if there is one drag operation
 * already in our system, it is not allowed to start new interation for drag operation.
 */
bool DragEventActuator::IsGlobalStatusSuitableForDragging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (dragDropManager->IsDragging()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, is dragging status");
        return false;
    }

    if (dragDropManager->IsMSDPDragging()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, is msdp dragging status");
        return false;
    }

    return true;
}

bool DragEventActuator::IsSelfAndParentDragForbidden(const RefPtr<FrameNode>& frameNode)
{
    auto parent = frameNode;
    while (parent) {
        auto eventHub = parent->GetEventHub<EventHub>();
        parent = parent->GetAncestorNodeOfFrame(true);
        if (!eventHub) {
            continue;
        }
        auto gestureEventHub = eventHub->GetGestureEventHub();
        if (!gestureEventHub) {
            continue;
        }
        if (gestureEventHub->IsDragForbidden()) {
            return true;
        }
    }
    return false;
}

/**
 * check the current node's status to decide if it can initiate one drag operation
 */
bool DragEventActuator::IsCurrentNodeStatusSuitableForDragging(
    const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, false);

    if (gestureHub->IsDragForbidden() || (!frameNode->IsDraggable() && frameNode->IsCustomerSet()) ||
        touchRestrict.inputEventType == InputEventType::AXIS || IsBelongToMultiItemNode(frameNode)) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "No need to collect drag gestures result, drag forbidden set is %{public}d,"
            "frameNode draggable is %{public}d, custom set is %{public}d",
            gestureHub->IsDragForbidden(), frameNode->IsDraggable(), frameNode->IsCustomerSet());
        return false;
    }

    if (IsSelfAndParentDragForbidden(frameNode)) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "No need to collect drag gestures result, parent is drag forbidden.");
        return false;
    }

    return true;
}

void DragEventActuator::RestartDragTask(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag pan event by axis");
        return;
    }
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    UpdatePreviewOptionFromModifier(frameNode);
    auto gestureInfo = const_cast<GestureEvent&>(info);
    if (actionStart_) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Restart drag for lifting status");
        actionStart_(gestureInfo);
    }
}

bool DragEventActuator::IsNotNeedShowPreviewForWeb(const RefPtr<FrameNode>& frameNode)
{
#ifdef WEB_SUPPORTED
    bool isNotNeedShowPreview = false;
    if (frameNode && frameNode->GetTag() == V2::WEB_ETS_TAG) {
        auto webPattern = frameNode->GetPattern<WebPattern>();
        CHECK_NULL_RETURN(webPattern, false);
        isNotNeedShowPreview = webPattern->IsPreviewMenuNotNeedShowPreview();
    }
    return isNotNeedShowPreview;
#else
    return false;
#endif
}

void DragEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, ResponseLinkResult& responseLinkResult)
{
    CHECK_NULL_VOID(userCallback_);
    isDragUserReject_ = false;
    isDragPrepareFinish_ = false;
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetPrepareDragFrameNode(nullptr);
    dragDropManager->SetIsDragNodeNeedClean(false);
    if (!IsGlobalStatusSuitableForDragging() || !IsCurrentNodeStatusSuitableForDragging(frameNode, touchRestrict)) {
        return;
    }
    auto focusHub = frameNode->GetFocusHub();
    bool hasContextMenuUsingGesture = focusHub == nullptr
                              ? false : focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
    dragDropManager->SetPreDragStatus(PreDragStatus::ACTION_DETECTING_STATUS);
    auto actionStart = [weak = WeakClaim(this), this](GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag action start.");
        ACE_SCOPED_TRACE("drag: pan successed, start handling");
        auto actuator = weak.Upgrade();
        if (!actuator) {
            DragEventActuator::ResetDragStatus();
            return;
        }
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        actuator->ResetResponseRegion();
        actuator->SetGatherNode(nullptr);
        if (dragDropManager->IsDragging() || dragDropManager->IsMSDPDragging()) {
            TAG_LOGI(AceLogTag::ACE_DRAG,
                "It's already dragging now, dragging is %{public}d, MSDP dragging is %{public}d",
                dragDropManager->IsDragging(), dragDropManager->IsMSDPDragging());
            return;
        }
        if (dragDropManager->GetPreDragStatus() >= PreDragStatus::PREVIEW_LANDING_FINISHED) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Drag preview is landing finished, stop dragging.");
            return;
        }
        if (dragDropManager->IsDragNodeNeedClean()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Drag node have been cleaned by backpress or click event, stop dragging.");
            return;
        }
        dragDropManager->SetHasGatherNode(false);
        dragDropManager->ResetDragging(DragDropMgrState::ABOUT_TO_PREVIEW);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        if (info.GetSourceDevice() != SourceType::MOUSE) {
            if (gestureHub->GetTextDraggable()) {
                auto pattern = frameNode->GetPattern<TextBase>();
                CHECK_NULL_VOID(pattern);
                if (!pattern->IsSelected()) {
                    dragDropManager->ResetDragging();
                    gestureHub->SetIsTextDraggable(false);
                    TAG_LOGW(AceLogTag::ACE_DRAG, "Text is not selected, stop dragging.");
                    return;
                }
                if (gestureHub->GetIsTextDraggable()) {
                    SetTextPixelMap(gestureHub);
                } else {
                    gestureHub->SetPixelMap(nullptr);
                }
            } else {
                HideEventColumn();
                HideFilter();
                RecordMenuWrapperNodeForDrag(frameNode->GetId());
                SubwindowManager::GetInstance()->HideMenuNG(false, true);
                frameNode->SetOptionsAfterApplied(actuator->GetOptionsAfterApplied());
            }
        }

        if (info.GetSourceDevice() == SourceType::MOUSE) {
            frameNode->MarkModifyDone();
            dragDropManager->SetIsShowBadgeAnimation(true);
            auto pattern = frameNode->GetPattern<TextBase>();
            if (gestureHub->GetTextDraggable() && pattern) {
                if (!pattern->IsSelected() || pattern->GetMouseStatus() == MouseStatus::MOVE) {
                    dragDropManager->ResetDragging();
                    gestureHub->SetIsTextDraggable(false);
                    TAG_LOGW(AceLogTag::ACE_DRAG, "Text isSelected: %{public}d, stop dragging.", pattern->IsSelected());
                    return;
                }
                if (pattern->BetweenSelectedPosition(info.GetGlobalLocation())) {
                    if (textDragCallback_) {
                        textDragCallback_(info.GetGlobalLocation());
                    }
                } else if (!gestureHub->GetIsTextDraggable()) {
                    gestureHub->SetPixelMap(nullptr);
                }
            } else {
                HideEventColumn();
                HidePixelMap(true, info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
                HideFilter();
                RecordMenuWrapperNodeForDrag(frameNode->GetId());
                SubwindowManager::GetInstance()->HideMenuNG(false, true);
                actuator->UpdatePreviewOptionFromModifier(frameNode);
            }
        }
        if (gestureHub->GetTextDraggable() && !gestureHub->GetIsTextDraggable()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Text category component does not meet the drag condition, forbidden drag.");
            dragDropManager->ResetDragging();
            return;
        }
       // Trigger drag start event set by user.
        CHECK_NULL_VOID(actuator->userCallback_);
        auto userActionStart = actuator->userCallback_->GetActionStartEventFunc();
        if (userActionStart) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag start event set by user.");
            userActionStart(info);
        }
        // Trigger custom drag start event
        CHECK_NULL_VOID(actuator->customCallback_);
        auto customActionStart = actuator->customCallback_->GetActionStartEventFunc();
        if (customActionStart) {
            customActionStart(info);
        }
    };
    actionStart_ = actionStart;
    panRecognizer_->SetOnActionStart(actionStart);

    auto actionUpdate = [weak = WeakClaim(this)](GestureEvent& info) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent panRecognizer onActionUpdate.");
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        CHECK_NULL_VOID(actuator->userCallback_);
        auto userActionUpdate = actuator->userCallback_->GetActionUpdateEventFunc();
        if (userActionUpdate) {
            userActionUpdate(info);
        }
        CHECK_NULL_VOID(actuator->customCallback_);
        auto customActionUpdate = actuator->customCallback_->GetActionUpdateEventFunc();
        if (customActionUpdate) {
            customActionUpdate(info);
        }
    };
    panRecognizer_->SetOnActionUpdate(actionUpdate);

    auto actionEnd = [weak = WeakClaim(this)](GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag action end.");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto dragDropManager = pipelineContext->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->SetHasGatherNode(false);
        if (dragDropManager->IsAboutToPreview()) {
            dragDropManager->ResetDragging();
        }
        dragDropManager->SetIsDragNodeNeedClean(false);
        auto actuator = weak.Upgrade();
        if (!actuator) {
            auto overlayManager = pipelineContext->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->RemovePixelMap();
            return;
        }
        CHECK_NULL_VOID(actuator->userCallback_);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        actuator->HideEventColumn();
        if (gestureHub->GetTextDraggable()) {
            actuator->textPixelMap_ = nullptr;
            actuator->HideTextAnimation();
        } else {
            actuator->HidePixelMap();
        }
        auto userActionEnd = actuator->userCallback_->GetActionEndEventFunc();
        if (userActionEnd) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag end event set by user.");
            userActionEnd(info);
        }
        CHECK_NULL_VOID(actuator->customCallback_);
        auto customActionEnd = actuator->customCallback_->GetActionEndEventFunc();
        if (customActionEnd) {
            customActionEnd(info);
        }
        actuator->SetIsNotInPreviewState(false);
    };
    panRecognizer_->SetOnActionEnd(actionEnd);
    auto actionCancel = [weak = WeakClaim(this), hasContextMenuUsingGesture = hasContextMenuUsingGesture,
                            touchSourceType = touchRestrict.sourceType]() {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Drag event has been canceled.");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto dragDropManager = pipelineContext->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->SetHasGatherNode(false);
        auto actuator = weak.Upgrade();
        if (!actuator) {
            DragEventActuator::ResetDragStatus();
            return;
        }
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        if (!actuator->isDragPrepareFinish_ && touchSourceType != SourceType::MOUSE) {
            return;
        }
        actuator->ResetResponseRegion();
        actuator->SetGatherNode(nullptr);
        if (actuator->GetIsNotInPreviewState() && !gestureHub->GetTextDraggable()) {
            DragEventActuator::ExecutePreDragAction(PreDragStatus::ACTION_CANCELED_BEFORE_DRAG, frameNode);
        }
        if (!gestureHub->GetBindMenuStatus().IsNotNeedShowPreview() &&
            !actuator->IsNotNeedShowPreviewForWeb(frameNode)) {
            if (gestureHub->GetTextDraggable()) {
                if (gestureHub->GetIsTextDraggable()) {
                    actuator->HideEventColumn();
                    actuator->textPixelMap_ = nullptr;
                    actuator->HideTextAnimation();
                }
            } else {
                auto renderContext = frameNode->GetRenderContext();
                BorderRadiusProperty borderRadius;
                if (renderContext->GetBorderRadius().has_value()) {
                    borderRadius.UpdateWithCheck(renderContext->GetBorderRadius().value());
                }
                borderRadius.multiValued = false;
                AnimationOption option;
                option.SetDuration(PIXELMAP_ANIMATION_DURATION);
                option.SetCurve(Curves::FRICTION);
                AnimationUtils::Animate(
                    option,
                    [renderContext_ = renderContext, borderRadius_ = borderRadius]() {
                        renderContext_->UpdateBorderRadius(borderRadius_);
                    },
                    option.GetOnFinishEvent());
                actuator->HidePixelMap();
                actuator->HideFilter();
            }
        } else {
            if (actuator->panRecognizer_->getDeviceType() == SourceType::MOUSE) {
                if (!gestureHub->GetTextDraggable()) {
                    actuator->HideEventColumn();
                    actuator->HidePixelMap();
                    actuator->HideFilter();
                }
            }
        }
        actuator->SetIsNotInPreviewState(false);
        CHECK_NULL_VOID(actuator->userCallback_);
        auto userActionCancel = actuator->userCallback_->GetActionCancelEventFunc();
        if (userActionCancel) {
            userActionCancel();
        }
        CHECK_NULL_VOID(actuator->customCallback_);
        auto customActionCancel = actuator->customCallback_->GetActionCancelEventFunc();
        if (customActionCancel) {
            customActionCancel();
        }
    };
    auto panOnReject = [weak = WeakClaim(this), hasContextMenuUsingGesture]() {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger pan onReject");
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        actuator->ResetResponseRegion();
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto manager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        if (manager->IsGatherWithMenu() || !actuator->GetGatherNode()) {
            return;
        }
        actuator->SetGatherNode(nullptr);
        actuator->ClearGatherNodeChildrenInfo();
        auto dragDropManager = pipelineContext->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        auto preDragStatus = dragDropManager->GetPreDragStatus();
        if (preDragStatus <= PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION) {
            manager->RemoveGatherNode();
        } else {
            manager->RemoveGatherNodeWithAnimation();
        }
    };
    panRecognizer_->SetOnReject(panOnReject);
    panRecognizer_->SetIsForDrag(true);
    panRecognizer_->SetMouseDistance(DRAG_PAN_DISTANCE_MOUSE.ConvertToPx());
    actionCancel_ = actionCancel;
    panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    if (touchRestrict.sourceType == SourceType::MOUSE) {
        std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer_ };
        SequencedRecognizer_ = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
        SequencedRecognizer_->RemainChildOnResetStatus();
        SequencedRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        SequencedRecognizer_->SetOnActionCancel(actionCancel);
        SequencedRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        result.emplace_back(SequencedRecognizer_);
        return;
    }
    auto longPressUpdateValue = [weak = WeakClaim(this), hasContextMenuUsingGesture = hasContextMenuUsingGesture](
                                    GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger long press for 500ms.");
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        actuator->isDragPrepareFinish_ = true;
        actuator->SetIsNotInPreviewState(true);
        if (actuator->userCallback_) {
            auto customLongPress = actuator->userCallback_->GetLongPressEventFunc();
            if (customLongPress) {
                customLongPress(info);
            }
        }
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto dragDropManager = pipelineContext->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        dragDropManager->SetIsShowBadgeAnimation(true);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        dragDropManager->SetPrepareDragFrameNode(frameNode);
        if (!gestureHub->GetTextDraggable()) {
            // For the drag initiacating from long press gesture, the preview option set by the modifier
            // should also be applied in floating pharse, so we need to update the preview option here.
            actuator->UpdatePreviewOptionFromModifier(frameNode);
            DragEventActuator::ExecutePreDragAction(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION, frameNode);
        }
        if (hasContextMenuUsingGesture) {
            actuator->SetDragDampStartPointInfo(info.GetGlobalPoint(), info.GetPointerId());
        }
    };
    longPressRecognizer_->SetOnActionUpdate(longPressUpdateValue);
    auto longPressUpdate = [weak = WeakClaim(this), hasContextMenuUsingGesture = hasContextMenuUsingGesture](
                                GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger long press for 800ms.");
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);

        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        if (overlayManager->GetHasPixelMap()) {
            return;
        }
        auto dragDropManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        if (dragDropManager->IsAboutToPreview() || dragDropManager->IsDragging() ||
            dragDropManager->IsDragNodeNeedClean()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "No need to show drag preview, is about to preview: %{public}d,"
                "is dragging: %{public}d, is need clean drag node: %{public}d",
                dragDropManager->IsAboutToPreview(), dragDropManager->IsDragging(),
                dragDropManager->IsDragNodeNeedClean());
            return;
        }
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        auto panRecognizer = actuator->panRecognizer_;
        if (panRecognizer && panRecognizer->GetGestureDisposal() == GestureDisposal::REJECT) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Not need to show drag preview because drag action reject");
            return;
        }
        actuator->isOnBeforeLiftingAnimation = false;
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        if (gestureHub->GetBindMenuStatus().IsNotNeedShowPreview()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Not need to show drag preview because of bind context menu");
            return;
        }
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        if (gestureHub->GetTextDraggable()) {
            actuator->SetIsNotInPreviewState(false);
            if (gestureHub->GetIsTextDraggable()) {
                actuator->SetTextAnimation(gestureHub, info.GetGlobalLocation());
                actuator->SetEventColumn(actuator);
            }
            return;
        }
        if (!actuator->isFloatImage_) {
            actuator->isFloatImage_ = true;
            return;
        }

        bool isAllowedDrag = actuator->IsAllowedDrag();
        if (!isAllowedDrag) {
            actuator->longPressInfo_ = info;
            actuator->isReceivedLongPress_ = true;
            TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop long press and info received");
            return;
        }
        dragDropManager->SetPrepareDragFrameNode(frameNode);
        if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
            actuator->SetFilter(actuator);
        }
        auto manager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        actuator->SetIsNotInPreviewState(false);
        actuator->SetGatherNodeAboveFilter(actuator);
        actuator->SetPixelMap(actuator);
        auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(SPRING_RESPONSE, SPRING_DAMPING_FRACTION, 0);
        auto column = manager->GetPixelMapNode();
        CHECK_NULL_VOID(column);

        auto imageNode = AceType::DynamicCast<FrameNode>(column->GetFirstChild());
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        if (actuator->IsNeedGather()) {
            DragAnimationHelper::PlayGatherAnimation(imageNode, manager);
            actuator->ShowPreviewBadgeAnimation(actuator, manager);
        }
        AnimationOption option;
        option.SetDuration(PIXELMAP_ANIMATION_TIME);
        option.SetCurve(motion);
        DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
        dragDropManager->SetDraggingPointer(info.GetPointerId());
        dragDropManager->SetDraggingPressedState(true);
        option.SetOnFinishEvent(
            [id = Container::CurrentId(), pointerId = info.GetPointerId(), hasContextMenuUsingGesture]() {
                ContainerScope scope(id);
                auto pipeline = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto dragDropManager = pipeline->GetDragDropManager();
                CHECK_NULL_VOID(dragDropManager);
                if (dragDropManager->IsDraggingPressed(pointerId) || hasContextMenuUsingGesture) {
                    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED);
                }
            });
        AnimationUtils::Animate(
            option,
            [imageContext]() {
                imageContext->UpdateTransformScale({ PIXELMAP_DRAG_SCALE_MULTIPLE, PIXELMAP_DRAG_SCALE_MULTIPLE });
            },
            option.GetOnFinishEvent());
        actuator->SetEventColumn(actuator);
    };
    auto longPressCancel = [weak = WeakClaim(this)] {
        // remove drag overlay info by Cancel event.
        TAG_LOGD(AceLogTag::ACE_DRAG, "Long press event has been canceled.");
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        actuator->HideEventColumn();
        actuator->HidePixelMap(true, 0, 0, false);
        actuator->HideFilter();
        actuator->SetIsNotInPreviewState(false);
    };
    longPressUpdate_ = longPressUpdate;
    auto preDragCallback = [weak = WeakClaim(this)](Offset point) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        if (!gestureHub->GetTextDraggable()) {
            DragEventActuator::ExecutePreDragAction(PreDragStatus::ACTION_DETECTING_STATUS, frameNode);
        }
    };
    previewLongPressRecognizer_->SetOnAction(longPressUpdate);
    previewLongPressRecognizer_->SetOnActionCancel(longPressCancel);
    previewLongPressRecognizer_->SetThumbnailCallback(std::move(preDragCallback));
    previewLongPressRecognizer_->SetGestureHub(gestureEventHub_);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    if (!longPressRecognizer_->HasThumbnailCallback() && isAllowedDrag) {
        auto callback = [weakPtr = gestureEventHub_, weak = WeakClaim(this)](Offset point) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger 150ms timer Thumbnail callback.");
            auto gestureHub = weakPtr.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            auto frameNode = gestureHub->GetFrameNode();
            CHECK_NULL_VOID(frameNode);
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto actuator = weak.Upgrade();
            CHECK_NULL_VOID(actuator);
            auto dragPreviewInfo = frameNode->GetDragPreview();
            if (dragPreviewInfo.inspectorId != "") {
                TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through inspectorId.");
                auto previewPixelMap = GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
                gestureHub->SetPixelMap(previewPixelMap);
                gestureHub->SetDragPreviewPixelMap(previewPixelMap);
                actuator->PrepareFinalPixelMapForDragThroughTouch(previewPixelMap, false);
            } else if (dragPreviewInfo.pixelMap != nullptr) {
                TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through pixelMap.");
                gestureHub->SetPixelMap(dragPreviewInfo.pixelMap);
                gestureHub->SetDragPreviewPixelMap(dragPreviewInfo.pixelMap);
                actuator->PrepareFinalPixelMapForDragThroughTouch(dragPreviewInfo.pixelMap, false);
            } else if (dragPreviewInfo.customNode != nullptr) {
#if defined(PIXEL_MAP_SUPPORTED)
                TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through customNode.");
                auto callback = [id = Container::CurrentId(), pipeline, gestureHub, weak]
                    (std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()>) {
                    ContainerScope scope(id);
                    if (pixelMap != nullptr) {
                        auto customPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
                        auto taskScheduler = pipeline->GetTaskExecutor();
                        CHECK_NULL_VOID(taskScheduler);
                        taskScheduler->PostTask(
                            [gestureHub, customPixelMap, weak]() {
                                CHECK_NULL_VOID(gestureHub);
                                gestureHub->SetPixelMap(customPixelMap);
                                gestureHub->SetDragPreviewPixelMap(customPixelMap);
                                auto actuator = weak.Upgrade();
                                CHECK_NULL_VOID(actuator);
                                actuator->PrepareFinalPixelMapForDragThroughTouch(customPixelMap, true);
                            },
                            TaskExecutor::TaskType::UI, "ArkUIDragSetCustomPixelMap");
                    } else {
                        TAG_LOGI(AceLogTag::ACE_DRAG, "PixelMap is null.");
                    }
                };
                SnapshotParam param;
                param.delay = CREATE_PIXELMAP_TIME;
                param.checkImageStatus = true;
                param.options.waitUntilRenderFinished = true;
                OHOS::Ace::NG::ComponentSnapshot::Create(
                    dragPreviewInfo.customNode, std::move(callback), true, param);
                gestureHub->PrintBuilderNode(dragPreviewInfo.customNode);
#endif
            } else {
                actuator->GetThumbnailPixelMapAsync(gestureHub);
            }
            auto longPressRecognizer = actuator->longPressRecognizer_;
            if (longPressRecognizer && longPressRecognizer->GetGestureDisposal() != GestureDisposal::REJECT) {
                if (!CreateGatherNode(actuator)) {
                    actuator->isOnBeforeLiftingAnimation = false;
                    return;
                }
                actuator->isOnBeforeLiftingAnimation = true;
                DragAnimationHelper::PlayGatherAnimationBeforeLifting(actuator);
                DragAnimationHelper::PlayNodeAnimationBeforeLifting(frameNode);
                actuator->SetResponseRegionFull();
            } else {
                actuator->isOnBeforeLiftingAnimation = false;
            }
        };

        longPressRecognizer_->SetThumbnailCallback(std::move(callback));
    }
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { longPressRecognizer_, panRecognizer_ };
    SequencedRecognizer_ = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    SequencedRecognizer_->RemainChildOnResetStatus();
    previewLongPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    previewLongPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    longPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    longPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    SequencedRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    SequencedRecognizer_->SetOnActionCancel(actionCancel);
    SequencedRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    SequencedRecognizer_->SetIsEventHandoverNeeded(true);
    result.emplace_back(SequencedRecognizer_);
    result.emplace_back(previewLongPressRecognizer_);
}

void DragEventActuator::ResetDragStatus()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemovePreviewBadgeNode();
    overlayManager->RemoveGatherNode();
    overlayManager->RemovePixelMap();
    overlayManager->RemoveEventColumn();
    overlayManager->RemoveFilter();
}

void DragEventActuator::SetDragDampStartPointInfo(const Point& point, int32_t pointerId)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDragDampStartPoint(point);
    dragDropManager->SetDraggingPointer(pointerId);
    isRedragStart_ = false;
}

void DragEventActuator::HandleDragDampingMove(const Point& point, int32_t pointerId, bool isRedragStart)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (dragDropManager->IsAboutToPreview() ||
        dragDropManager->IsDragging() || !dragDropManager->IsSameDraggingPointer(pointerId)) {
        return;
    }
    auto startPoint = dragDropManager->GetDragDampStartPoint();
    //get the number with VP unit
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
    auto updateOffset =
        OffsetF(dragStartDampingRatio * point.GetX() + (1 - dragStartDampingRatio) * startPoint.GetX(),
            dragStartDampingRatio * point.GetY() + (1 - dragStartDampingRatio) * startPoint.GetY());
    auto menuWrapperNode = dragDropManager->GetMenuWrapperNode();
    auto menuWrapperId = menuWrapperNode ? menuWrapperNode->GetId() : -1;
    if (isRedragStart && !isRedragStart_) {
        isRedragStart_ = true;
        SubwindowManager::GetInstance()->UpdateHideMenuOffsetNG(updateOffset, previewMenuScale, true, menuWrapperId);
        dragDropManager->UpdateDragMovePosition(updateOffset, true);
    } else {
        SubwindowManager::GetInstance()->UpdateHideMenuOffsetNG(updateOffset, previewMenuScale, false, menuWrapperId);
        dragDropManager->UpdateDragMovePosition(updateOffset, false);
    }
    SubwindowManager::GetInstance()->UpdatePreviewPosition();
}

void DragEventActuator::SetFilter(const RefPtr<DragEventActuator>& actuator)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start setFilter.");
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto parent = frameNode->GetParent();
    CHECK_NULL_VOID(parent);
    while (parent && parent->GetDepth() != 1) {
        parent = parent->GetParent();
    }
    if (!parent) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "DragFrameNode is %{public}s, depth %{public}d, can not find filter root",
            frameNode->GetTag().c_str(), frameNode->GetDepth());
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (!manager->GetHasFilter() && !manager->GetIsOnAnimation()) {
        if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
#ifdef WEB_SUPPORTED
            auto webPattern = frameNode->GetPattern<WebPattern>();
            CHECK_NULL_VOID(webPattern);
            bool isWebmageDrag = webPattern->IsImageDrag();
            WebInfoType type = webPattern->GetWebInfoType();
            CHECK_NULL_VOID(isWebmageDrag && type == WebInfoType::TYPE_MOBILE);
#endif
        } else {
            bool isBindOverlayValue = frameNode->GetLayoutProperty()->GetIsBindOverlayValue(false);
            CHECK_NULL_VOID(isBindOverlayValue && SystemProperties::GetDeviceType() == DeviceType::PHONE);
        }
        // insert columnNode to rootNode
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        columnNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
        // set filter
        TAG_LOGI(AceLogTag::ACE_DRAG, "User Device use default Filter");
        auto container = Container::Current();
        if (container && container->IsScenceBoardWindow()) {
            auto windowScene = manager->FindWindowScene(frameNode);
            manager->MountFilterToWindowScene(columnNode, windowScene);
        } else {
            columnNode->MountToParent(parent);
            columnNode->OnMountToParentDone();
            manager->SetHasFilter(true);
            manager->SetFilterColumnNode(columnNode);
            parent->MarkDirtyNode(NG::PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
        AnimationOption option;
        BlurStyleOption styleOption;
        styleOption.blurStyle = static_cast<BlurStyle>(BlurStyle::BACKGROUND_THIN);
        styleOption.colorMode = static_cast<ThemeColorMode>(static_cast<int32_t>(ThemeColorMode::SYSTEM));
        option.SetDuration(FILTER_TIMES);
        option.SetCurve(Curves::SHARP);
        option.SetOnFinishEvent([pipelineWeak = WeakClaim(RawPtr(pipelineContext))] {
            auto pipelineContext = pipelineWeak.Upgrade();
            CHECK_NULL_VOID(pipelineContext);
            auto manager = pipelineContext->GetOverlayManager();
            CHECK_NULL_VOID(manager);
            manager->SetFilterActive(false);
        });
        columnNode->GetRenderContext()->UpdateBackBlurRadius(FILTER_VALUE);
        AnimationUtils::Animate(
            option, [columnNode, styleOption]() { columnNode->GetRenderContext()->UpdateBackBlurStyle(styleOption); },
            option.GetOnFinishEvent());
    }
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent set filter success.");
}

OffsetF DragEventActuator::GetFloatImageOffset(const RefPtr<FrameNode>& frameNode, const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_RETURN(frameNode, OffsetF());
    auto centerPosition = frameNode->GetPaintRectCenter(true);
    float width = 0.0f;
    float height = 0.0f;
    if (pixelMap) {
        width = pixelMap->GetWidth();
        height = pixelMap->GetHeight();
    }
    auto offsetX = centerPosition.GetX() - width / 2.0f;
    auto offsetY = centerPosition.GetY() - height / 2.0f;
#ifdef WEB_SUPPORTED
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        auto webPattern = frameNode->GetPattern<WebPattern>();
        if (webPattern) {
            auto offsetToWindow = frameNode->GetPaintRectOffset();
            offsetX = offsetToWindow.GetX() + webPattern->GetDragOffset().GetX();
            offsetY = offsetToWindow.GetY() + webPattern->GetDragOffset().GetY();
        }
    }
#endif
    // Check web tag.
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    if (pipelineContext->HasFloatTitle()) {
        offsetX -= static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx());
        offsetY -= static_cast<float>((pipelineContext->GetCustomTitleHeight() + CONTAINER_BORDER_WIDTH).ConvertToPx());
    }
    return OffsetF(offsetX, offsetY);
}

void DragEventActuator::UpdateGatherAnimatePosition(
    std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, const OffsetF& GatherNodeOffset)
{
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        auto childFrameOffset = imageContext->GetPaintRectWithoutTransform();
        imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(GatherNodeOffset.GetX() + childFrameOffset.GetX()),
            Dimension(GatherNodeOffset.GetY() + childFrameOffset.GetY())));
    }
}

void DragEventActuator::UpdatePreviewPositionAndScale(
    const RefPtr<FrameNode>& imageNode, const OffsetF& frameOffset, float scale)
{
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(frameOffset.GetX()), Dimension(frameOffset.GetY())));
    if (GreatNotEqual(scale, 0.0f)) {
        imageContext->UpdateTransformScale({ scale, scale });
    }
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = ClickEffectLevel::LIGHT;
    clickEffectInfo.scaleNumber = SCALE_NUMBER;
    imageContext->UpdateClickEffectLevel(clickEffectInfo);
}

void DragEventActuator::UpdatePreviewAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(frameNode);
    auto frameTag = frameNode->GetTag();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    if (gestureHub->IsTextCategoryComponent(frameTag) && gestureHub->GetTextDraggable()) {
        if (dragPreviewOption.options.shadow.has_value()) {
            auto shadow = dragPreviewOption.options.shadow.value();
            shadow.SetIsFilled(true);
            imageContext->UpdateBackShadow(shadow);
        }
        return;
    }
    imageContext->UpdateOpacity(dragPreviewOption.options.opacity);
    if (dragPreviewOption.options.shadow.has_value()) {
        imageContext->UpdateBackShadow(dragPreviewOption.options.shadow.value());
    }
    if (dragPreviewOption.options.borderRadius.has_value()) {
        imageContext->UpdateBorderRadius(dragPreviewOption.options.borderRadius.value());
        imageContext->UpdateClipEdge(true);
    }
    auto optionsFromModifier = frameNode->GetDragPreviewOption().options;
    if (optionsFromModifier.blurbgEffect.backGroundEffect.radius.IsValid()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundEffect, optionsFromModifier.blurbgEffect.backGroundEffect, imageNode);
    }
}

void DragEventActuator::CreatePreviewNode(const RefPtr<FrameNode>& frameNode, OHOS::Ace::RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pixelMap = frameNode->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto center = frameNode->GetPaintRectCenter();
    auto frameOffset = OffsetF(center.GetX() - (pixelMap->GetWidth() / 2.0f),
        center.GetY() - (pixelMap->GetHeight() / 2.0f));
    imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() {return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);
    imageNode->SetDragPreviewOptions(frameNode->GetDragPreviewOption());

    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(pixelMap->GetWidth()), NG::CalcLength(pixelMap->GetHeight()));
    props->UpdateUserDefinedIdealSize(targetSize);

    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetSyncLoad(true);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    UpdatePreviewPositionAndScale(imageNode, frameOffset, gestureHub->GetMenuPreviewScale());
    UpdatePreviewAttr(frameNode, imageNode);
    imageNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    imageNode->SetLayoutDirtyMarked(true);
    imageNode->SetActive(true);
    auto context = imageNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(imageNode);
    }
    FlushSyncGeometryNodeTasks();
}

void DragEventActuator::SetPreviewDefaultAnimateProperty(const RefPtr<FrameNode>& imageNode)
{
    if (imageNode->IsPreviewNeedScale()) {
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        imageContext->UpdateTransformScale({ 1.0f, 1.0f });
        imageContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    }
}

void DragEventActuator::MountPixelMap(const RefPtr<OverlayManager>& manager, const RefPtr<GestureEventHub>& gestureHub,
    const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode, bool isDragPixelMap)
{
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(gestureHub);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    columnNode->AddChild(imageNode);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    hub->SetPixelMap(gestureHub->GetPixelMap());
    if (textNode) {
        columnNode->AddChild(textNode);
    }
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto windowScene = manager->FindWindowScene(frameNode);
        manager->MountPixelMapToWindowScene(columnNode, windowScene, isDragPixelMap);
    } else {
        manager->MountPixelMapToRootNode(columnNode, isDragPixelMap);
    }
    SetPreviewDefaultAnimateProperty(imageNode);
    columnNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    columnNode->MarkModifyDone();
    columnNode->SetActive(true);
    auto context = columnNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(columnNode);
    }
    FlushSyncGeometryNodeTasks();
}

/* Retrieves a preview PixelMap for a given drag event action.
 * This function attempts to obtain a screenshot of a frameNode associated with an inspector ID.
 * If the frameNode with the given ID does not exist or hasn't been rendered,
 * it falls back to taking a screenshot of the provided frame node.
 *
 * @param inspectorId A string representing the unique identifier for the frameNode's ID.
 * @param selfFrameNode A RefPtr to the frame node associated with the drag event.
 * @return A RefPtr to a PixelMap containing the preview image, or nullptr if not found.
 */
RefPtr<PixelMap> DragEventActuator::GetPreviewPixelMap(
    const std::string& inspectorId, const RefPtr<FrameNode>& selfFrameNode)
{
    // Attempt to retrieve the PixelMap using the inspector ID.
    auto previewPixelMap = GetPreviewPixelMapByInspectorId(inspectorId);

    // If a preview PixelMap was found, return it.
    if (previewPixelMap != nullptr) {
        return previewPixelMap;
    }

    // If not found by inspector ID, attempt to get a screenshot of the frame node.
    return GetScreenShotPixelMap(selfFrameNode);
}

/* Retrieves a preview PixelMap based on an inspector ID.
 * This function attempts to find a frame node associated with the given inspector ID and then takes a screenshot of it.
 *
 * @param inspectorId The unique identifier for a frameNode.
 * @return A RefPtr to a PixelMap containing the preview image, or nullptr if not found or the ID is empty.
 */
RefPtr<PixelMap> DragEventActuator::GetPreviewPixelMapByInspectorId(const std::string& inspectorId)
{
    // Check for an empty inspector ID and return nullptr if it is empty.
    if (inspectorId == "") {
        return nullptr;
    }

    // Retrieve the frame node using the inspector's ID.
    auto dragPreviewFrameNode = Inspector::GetFrameNodeByKey(inspectorId);
    CHECK_NULL_RETURN(dragPreviewFrameNode, nullptr);

    auto layoutProperty = dragPreviewFrameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto visibility = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    if (visibility == VisibleType::INVISIBLE || visibility == VisibleType::GONE) {
        return nullptr;
    }

    // Take a screenshot of the frame node and return it as a PixelMap.
    return GetScreenShotPixelMap(dragPreviewFrameNode);
}

/* Captures a screenshot of the specified frame node and encapsulates it in a PixelMap.
 *
 * @param frameNode A RefPtr reference to the frame node from which to capture the screenshot.
 * @return A RefPtr to a PixelMap containing the screenshot.
 */
RefPtr<PixelMap> DragEventActuator::GetScreenShotPixelMap(const RefPtr<FrameNode>& frameNode)
{
    // Ensure the frame node is not nulls before proceeding.
    CHECK_NULL_RETURN(frameNode, nullptr);

    // Obtain the rendering context from the frame node.
    auto context = frameNode->GetRenderContext();

    // If the rendering context is not available, return nullptr.
    CHECK_NULL_RETURN(context, nullptr);

    // Capture and return the thumbnail PixelMap from the rendering context.
    return context->GetThumbnailPixelMap(true);
}

void DragEventActuator::SetPixelMap(const RefPtr<DragEventActuator>& actuator)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start set pixelMap");
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (manager->GetHasPixelMap()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Dragging animation is currently executing, unable to float other pixelMap.");
        return;
    }
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<PixelMap> pixelMap = gestureHub->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto offset = GetFloatImageOffset(frameNode, pixelMap);
    // create imageNode
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetSyncLoad(true);
    imageNode->SetDragPreviewOptions(frameNode->GetDragPreviewOption());
    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
    props->UpdateUserDefinedIdealSize(targetSize);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = ClickEffectLevel::LIGHT;
    clickEffectInfo.scaleNumber = SCALE_NUMBER;
    imageContext->UpdateClickEffectLevel(clickEffectInfo);
    // create columnNode
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    columnNode->AddChild(imageNode);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    hub->SetPixelMap(gestureHub->GetPixelMap());
    // mount to rootNode
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
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
    FlushSyncGeometryNodeTasks();
    auto focusHub = frameNode->GetFocusHub();
    bool hasContextMenu = focusHub == nullptr
                              ? false : focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
    ShowPixelMapAnimation(imageNode, frameNode, hasContextMenu);
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent set pixelMap success.");
    SetPreviewDefaultAnimateProperty(imageNode);
}

// called when the preview floating or drag begin, this method will try to execute the modifier
// on one temporary frame node, and then get the value user setted from the modifier
void DragEventActuator::UpdatePreviewOptionFromModifier(const RefPtr<FrameNode>& frameNode)
{
    UpdatePreviewOptionDefaultAttr(frameNode);
    auto modifierOnApply = frameNode->GetDragPreviewOption().onApply;
    if (!modifierOnApply) {
        optionsAfterApplied_ = frameNode->GetDragPreviewOption().options;
        return;
    }

    // create one temporary frame node for receiving the value from the modifier
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);

    // execute the modifier
    modifierOnApply(WeakClaim(RawPtr(imageNode)));

    // get values from the temporary frame node
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto opacity = imageContext->GetOpacity();

    OptionsAfterApplied options = frameNode->GetDragPreviewOption().options;
    if (opacity.has_value() && (opacity.value()) <= MAX_OPACITY && (opacity.value()) > MIN_OPACITY) {
        options.opacity = opacity.value();
    } else {
        options.opacity = DEFAULT_OPACITY;
    }

    auto shadow = imageContext->GetBackShadow();
    if (shadow.has_value()) {
        options.shadow = shadow;
    }

    auto borderRadius = imageContext->GetBorderRadius();
    if (borderRadius.has_value()) {
        options.borderRadius = borderRadius;
    }

    // get the old preview option
    DragPreviewOption dragPreviewOption = frameNode->GetDragPreviewOption();
    auto bgEffect = imageContext->GetBackgroundEffect();
    if (bgEffect.has_value()) {
        options.blurbgEffect.backGroundEffect = bgEffect.value();
    } else {
        auto blurstyletmp = imageContext->GetBackBlurStyle();
        if (blurstyletmp.has_value()) {
            bgEffect = BrulStyleToEffection(blurstyletmp);
            if (bgEffect.has_value()) {
                options.blurbgEffect.backGroundEffect = bgEffect.value();
            }
        }
    }
    dragPreviewOption.options = options; // replace the options with the new one after applied
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    optionsAfterApplied_ = options;
}

void DragEventActuator::UpdatePreviewOptionDefaultAttr(const RefPtr<FrameNode>& frameNode)
{
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    dragPreviewOption.options.opacity = DEFAULT_OPACITY;
    if (dragPreviewOption.isDefaultShadowEnabled) {
        dragPreviewOption.options.shadow = GetDefaultShadow();
    } else {
        dragPreviewOption.options.shadow = std::nullopt;
    }
    if (dragPreviewOption.isDefaultRadiusEnabled || dragPreviewOption.isMultiSelectionEnabled) {
        dragPreviewOption.options.borderRadius = GetDefaultBorderRadius();
    } else {
        dragPreviewOption.options.borderRadius = std::nullopt;
    }
    frameNode->SetDragPreviewOptions(dragPreviewOption); // replace the options with the new one
}

float DragEventActuator::RadiusToSigma(float radius)
{
    return GreatNotEqual(radius, 0.0f) ? BLUR_SIGMA_SCALE * radius + SCALE_HALF : 0.0f;
}

std::optional<EffectOption> DragEventActuator::BrulStyleToEffection(const std::optional<BlurStyleOption>& blurStyleOp)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        LOGW("cannot find theme of blurStyle, create blurStyle failed");
        return std::nullopt;
    }
    ThemeColorMode colorMode = blurStyleOp->colorMode;
    if (blurStyleOp->colorMode == ThemeColorMode::SYSTEM) {
        colorMode = SystemProperties::GetColorMode() == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    }
    auto blurParam = blurStyleTheme->GetBlurParameter(blurStyleOp->blurStyle, colorMode);
    CHECK_NULL_RETURN(blurParam, std::nullopt);
    auto ratio = blurStyleOp->scale;
    auto maskColor = blurParam->maskColor.BlendOpacity(ratio);
    auto radiusPx = blurParam->radius * pipeline->GetDipScale();
    auto radiusBlur = RadiusToSigma(radiusPx) * ratio;
    auto saturation = (blurParam->saturation - 1) * ratio + 1.0;
    auto brightness = (blurParam->brightness - 1) * ratio + 1.0;
    Dimension dimen(radiusBlur);
    EffectOption bgEffection = {dimen, saturation, brightness, maskColor,
        blurStyleOp->adaptiveColor, blurStyleOp->blurOption};
    return std::optional<EffectOption>(bgEffection);
}

void DragEventActuator::ApplyNewestOptionExecutedFromModifierToNode(
    const RefPtr<FrameNode>& optionHolderNode, const RefPtr<FrameNode>& targetNode)
{
    auto optionsFromModifier = targetNode->GetDragPreviewOption().options;
    ACE_UPDATE_NODE_RENDER_CONTEXT(Opacity, optionsFromModifier.opacity, targetNode);
    if (optionsFromModifier.blurbgEffect.backGroundEffect.radius.IsValid()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundEffect, optionsFromModifier.blurbgEffect.backGroundEffect, targetNode);
    }
    if (optionsFromModifier.shadow.has_value()) {
        // if shadow is unfilled, set shadow after animation
        if (optionsFromModifier.shadow->GetIsFilled()) {
            ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, optionsFromModifier.shadow.value(), targetNode);
        }
    }

    const auto& target = targetNode->GetRenderContext();
    if (optionsFromModifier.borderRadius.has_value()) {
        target->UpdateBorderRadius(optionsFromModifier.borderRadius.value());
        target->UpdateClipEdge(true);
    }
}

void DragEventActuator::SetEventColumn(const RefPtr<DragEventActuator>& actuator)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "DragEvent start set eventColumn.");
    auto pipelineContext = PipelineContext::GetCurrentContext();
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
    if (container && container->IsScenceBoardWindow()) {
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto frameNode = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto windowScene = manager->FindWindowScene(frameNode);
        manager->MountEventToWindowScene(columnNode, windowScene);
    } else {
        manager->MountEventToRootNode(columnNode);
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "DragEvent set eventColumn success. depth %{public}d, id %{public}d.",
        columnNode->GetDepth(), columnNode->GetId());
}

void DragEventActuator::HideFilter()
{
    auto gestureEventHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureEventHub);
    auto frameNode = gestureEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() != V2::WEB_ETS_TAG) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemoveFilterAnimation();
}

void DragEventActuator::HidePixelMap(bool startDrag, double x, double y, bool showAnimation)
{
    auto gestureEventHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureEventHub);
    auto frameNode = gestureEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (!startDrag) {
        manager->RemovePreviewBadgeNode();
        manager->RemoveGatherNodeWithAnimation();
    }

    if (showAnimation) {
        manager->RemovePixelMapAnimation(startDrag, x, y);
    } else {
        manager->RemovePixelMap();
    }
}

void DragEventActuator::HideEventColumn()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemoveEventColumn();
}

void DragEventActuator::BindClickEvent(const RefPtr<FrameNode>& columnNode)
{
    auto callback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "start click event callback");
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        auto gestureHub = actuator->gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        actuator->HideEventColumn();
        if (gestureHub->GetTextDraggable()) {
            actuator->HideTextAnimation();
        } else {
            actuator->HidePixelMap();
            actuator->HideFilter();
        }
    };
    auto columnGestureHub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(columnGestureHub);
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(callback));
    columnGestureHub->AddClickEvent(clickListener);
    if (!GetIsBindOverlayValue(Claim(this))) {
        columnGestureHub->SetHitTestMode(HitTestMode::HTMBLOCK);
    }
}

void DragEventActuator::ShowPixelMapAnimation(const RefPtr<FrameNode>& imageNode,
    const RefPtr<FrameNode>& frameNode, bool hasContextMenu)
{
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetOptionsAfterApplied(optionsAfterApplied_);
    SetImageNodeInitAttr(frameNode, imageNode);
    // pixel map animation
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent([imageNode, frameNode]() {
        DragEventActuator::SetImageNodeFinishAttr(frameNode, imageNode);
    });
    
    AnimationUtils::Animate(
        option,
        [imageNode, hasContextMenu, weak = WeakClaim(RawPtr(frameNode))]() mutable {
            auto imageContext = imageNode->GetRenderContext();
            CHECK_NULL_VOID(imageContext);
            auto frameNode = weak.Upgrade();
            ApplyNewestOptionExecutedFromModifierToNode(frameNode, imageNode);
            if (hasContextMenu) {
                BorderRadiusProperty borderRadius;
                borderRadius.SetRadius(PIXELMAP_BORDER_RADIUS);
                imageContext->UpdateBorderRadius(borderRadius);
            }
            DragEventActuator::ResetNode(frameNode);
        },
        option.GetOnFinishEvent());
}

void DragEventActuator::ExecutePreDragAction(const PreDragStatus preDragStatus, const RefPtr<FrameNode>& frameNode)
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (dragDropManager->IsDragging() || dragDropManager->IsMSDPDragging()) {
        return;
    }
    RefPtr<EventHub> eventHub;
    if (frameNode) {
        eventHub = frameNode->GetEventHub<EventHub>();
    } else {
        auto preDragFrameNode = dragDropManager->GetPrepareDragFrameNode().Upgrade();
        CHECK_NULL_VOID(preDragFrameNode);
        eventHub = preDragFrameNode->GetEventHub<EventHub>();
    }
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!gestureHub->IsAllowedDrag(eventHub) || gestureHub->GetTextDraggable()) {
        return;
    }
    if (preDragStatus == PreDragStatus::PREVIEW_LANDING_STARTED) {
        dragDropManager->SetIsDragNodeNeedClean(true);
    }
    auto onPreDragStatus = PreDragStatus::ACTION_CANCELED_BEFORE_DRAG;
    if (dragDropManager->GetPreDragStatus() <= preDragStatus &&
        preDragStatus != PreDragStatus::ACTION_CANCELED_BEFORE_DRAG) {
        auto nextPreDragStatus = static_cast<PreDragStatus>(static_cast<int32_t>(preDragStatus) + 1);
        dragDropManager->SetPreDragStatus(nextPreDragStatus);
        onPreDragStatus = preDragStatus;
    }
    auto onPreDragFunc = eventHub->GetOnPreDrag();
    CHECK_NULL_VOID(onPreDragFunc);
    if (preDragStatus == PreDragStatus::PREVIEW_LIFT_FINISHED ||
        preDragStatus == PreDragStatus::PREVIEW_LANDING_FINISHED) {
        auto taskScheduler = mainPipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [onPreDragStatus, callback = onPreDragFunc]() {
                CHECK_NULL_VOID(callback);
                callback(onPreDragStatus);
            },
            TaskExecutor::TaskType::UI, "ArkUIDragExecutePreDrag");
    } else {
        onPreDragFunc(onPreDragStatus);
    }
}

void DragEventActuator::SetThumbnailCallback(std::function<void(Offset)>&& callback)
{
    textDragCallback_ = callback;
    longPressRecognizer_->SetThumbnailCallback(std::move(callback));
}

void DragEventActuator::SetTextPixelMap(const RefPtr<GestureEventHub>& gestureHub)
{
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    CHECK_NULL_VOID(pattern);

    auto dragNode = pattern->MoveDragNode();
    pattern->CloseSelectOverlay();
    CHECK_NULL_VOID(dragNode);
    auto pixelMap = dragNode->GetRenderContext()->GetThumbnailPixelMap();
    if (textPixelMap_) {
        gestureHub->SetPixelMap(textPixelMap_);
        textPixelMap_ = nullptr;
    } else if (pixelMap) {
        gestureHub->SetPixelMap(pixelMap);
    } else {
        gestureHub->SetPixelMap(nullptr);
    }
}

void DragEventActuator::SetTextAnimation(const RefPtr<GestureEventHub>& gestureHub, const Offset& globalLocation)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start set textAnimation.");
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->SetHasFilter(false);
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    auto textBase = frameNode->GetPattern<TextBase>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(textBase);
    if (!textBase->BetweenSelectedPosition(globalLocation)) {
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
    // mount to rootNode
    manager->MountPixelMapToRootNode(columnNode);
    auto textDragPattern = dragNode->GetPattern<TextDragPattern>();
    CHECK_NULL_VOID(textDragPattern);
    auto modifier = textDragPattern->GetOverlayModifier();
    CHECK_NULL_VOID(modifier);
    modifier->UpdateHandlesShowFlag(isHandlesShow);
    auto renderContext = dragNode->GetRenderContext();
    if (renderContext) {
        textPixelMap_ = renderContext->GetThumbnailPixelMap();
    }
    modifier->StartFloatingAnimate();
    pattern->CloseHandleAndSelect();
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent set text animation success.");
}

void DragEventActuator::HideTextAnimation(bool startDrag, double globalX, double globalY)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start hide text animation.");
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    bool isAllowedDrag = IsAllowedDrag();
    if (!gestureHub->GetTextDraggable() || !isAllowedDrag) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Text is not draggable, stop set hide text animation.");
        return;
    }
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    CHECK_NULL_VOID(pattern);
    auto node = pattern->MoveDragNode();
    CHECK_NULL_VOID(node);
    auto textDragPattern = node->GetPattern<TextDragPattern>();
    CHECK_NULL_VOID(textDragPattern);
    auto modifier = textDragPattern->GetOverlayModifier();
    CHECK_NULL_VOID(modifier);
    auto removeColumnNode = [id = Container::CurrentId(), startDrag, weakPattern = WeakPtr<TextDragBase>(pattern),
            weakEvent = gestureEventHub_, weakModifier = WeakPtr<TextDragOverlayModifier>(modifier)] {
        ContainerScope scope(id);
        if (!startDrag) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto modifier = weakModifier.Upgrade();
            CHECK_NULL_VOID(modifier);
            pattern->ShowHandles(modifier->IsHandlesShow());
        }
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto manager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        manager->RemovePixelMap();
        TAG_LOGD(AceLogTag::ACE_DRAG, "In removeColumnNode callback, set DragWindowVisible true.");
        auto gestureHub = weakEvent.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto dragDropManager = pipeline->GetDragDropManager();
        if (!gestureHub->IsPixelMapNeedScale() && dragDropManager && dragDropManager->IsDragging()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
        gestureHub->SetPixelMap(nullptr);
    };
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent(removeColumnNode);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    auto dragNode = manager->GetPixelMapNode();
    CHECK_NULL_VOID(dragNode);
    auto dragFrame = dragNode->GetGeometryNode()->GetFrameRect();
    auto frameWidth = dragFrame.Width();
    auto frameHeight = dragFrame.Height();
    auto pixelMap = gestureHub->GetPixelMap();
    float scale = 1.0f;
    if (pixelMap) {
        scale = gestureHub->GetPixelMapScale(pixelMap->GetHeight(), pixelMap->GetWidth());
    }
    auto context = dragNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformScale(VectorF(1.0f, 1.0f));
    AnimationUtils::Animate(
        option,
        [context, startDrag, globalX, globalY, frameWidth, frameHeight, scale]() {
            if (startDrag) {
                context->UpdatePosition(OffsetT<Dimension>(Dimension(globalX + frameWidth * PIXELMAP_WIDTH_RATE),
                    Dimension(globalY + frameHeight * PIXELMAP_HEIGHT_RATE)));
                context->UpdateTransformScale(VectorF(scale, scale));
                context->OnModifyDone();
            }
        },
        option.GetOnFinishEvent());
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent set hide text animation success.");
}

// update ImageNode default attr before floating
void DragEventActuator::SetImageNodeInitAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(frameNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();

    // update default scale
    bool defaultAnimationBeforeLifting = dragPreviewOption.defaultAnimationBeforeLifting;
    if (defaultAnimationBeforeLifting) {
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        }
        imageContext->UpdateTransformScale({ DEFAULT_ANIMATION_SCALE, DEFAULT_ANIMATION_SCALE });
    } else {
        imageContext->UpdateTransformScale({ 1.0f, 1.0f });
    }
    
    // update shadow
    auto shadow = Shadow::CreateShadow(ShadowStyle::None);
    if (dragPreviewOption.options.shadow.has_value()) {
        shadow = dragPreviewOption.options.shadow.value();
        shadow.SetColor(Color(0x00000000));
    }
    imageContext->UpdateBackShadow(shadow);
    
    // update radius
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(0.0_vp);
    imageContext->UpdateBorderRadius(borderRadius);
    
    // update opacity
    imageContext->UpdateOpacity(1.0f);
}

void DragEventActuator::SetImageNodeFinishAttr(const RefPtr<FrameNode>& frameNode,
    const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(frameNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    if (dragPreviewOption.options.shadow.has_value() && !dragPreviewOption.options.shadow->GetIsFilled()) {
        imageContext->UpdateBackShadow(dragPreviewOption.options.shadow.value());
    }
}

bool DragEventActuator::GetIsBindOverlayValue(const RefPtr<DragEventActuator>& actuator)
{
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, true);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, true);
    bool isBindOverlayValue = frameNode->GetLayoutProperty()->GetIsBindOverlayValue(false);
    return isBindOverlayValue;
}

bool DragEventActuator::IsAllowedDrag()
{
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, false);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    return isAllowedDrag;
}

void DragEventActuator::CopyDragEvent(const RefPtr<DragEventActuator>& dragEventActuator)
{
    userCallback_ = dragEventActuator->userCallback_;
    customCallback_ = dragEventActuator->customCallback_;
    panRecognizer_ = MakeRefPtr<PanRecognizer>(fingers_, direction_, distance_);
    panRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, fingers_, false, false);
    longPressRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(PREVIEW_LONG_PRESS_RECONGNIZER, fingers_, false, false);
    previewLongPressRecognizer_->SetGestureInfo(
        MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    isNotInPreviewState_ = false;
    actionStart_ = dragEventActuator->actionStart_;
    longPressUpdate_ = dragEventActuator->longPressUpdate_;
    actionCancel_ = dragEventActuator->actionCancel_;
    textDragCallback_ = dragEventActuator->textDragCallback_;
    longPressInfo_ = dragEventActuator->longPressInfo_;
}

void DragEventActuator::FlushSyncGeometryNodeTasks()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->FlushSyncGeometryNodeTasks();
}

void DragEventActuator::SetGatherNodeAboveFilter(const RefPtr<DragEventActuator>& actuator)
{
    CHECK_NULL_VOID(actuator);
    if (!actuator->IsNeedGather()) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gatherNode = manager->GetGatherNode();
    auto gatherNodeChildrenInfo = manager->GetGatherNodeChildrenInfo();
    manager->RemoveGatherNode();
    MountGatherNode(manager, frameNode, gatherNode, gatherNodeChildrenInfo);
}

RefPtr<FrameNode> DragEventActuator::GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
    const RefPtr<DragEventActuator>& actuator, std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
{
    CHECK_NULL_RETURN(actuator, nullptr);
    if (!actuator->IsNeedGather()) {
        return nullptr;
    }
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto previewOptions = frameNode->GetDragPreviewOption();
    if (!previewOptions.isMultiSelectionEnabled) {
        return nullptr;
    }
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto gatherNode = overlayManager->GetGatherNode();
    if (!gatherNode) {
        auto gatherNode = CreateGatherNode(actuator);
        if (gatherNode) {
            MarkDirtyGatherNode(gatherNode);
        }
        gatherNodeChildrenInfo = actuator->GetGatherNodeChildrenInfo();
        actuator->ClearGatherNodeChildrenInfo();
        actuator->SetGatherNode(nullptr);
        return gatherNode;
    } else {
        gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
        overlayManager->RemoveGatherNode();
    }
    return gatherNode;
}

RefPtr<FrameNode> DragEventActuator::CreateGatherNode(const RefPtr<DragEventActuator>& actuator)
{
    CHECK_NULL_RETURN(actuator, nullptr);
    auto gestureHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(manager, nullptr);

    if (manager->GetHasGatherNode()) {
        return nullptr;
    }

    if (!actuator->IsNeedGather()) {
        return nullptr;
    }
    auto fatherNode = actuator->itemParentNode_.Upgrade();
    CHECK_NULL_RETURN(fatherNode, nullptr);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, nullptr);
    auto children = scrollPattern->GetVisibleSelectedItems();
    if (children.size() < 1) {
        return nullptr;
    }
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    actuator->ClearGatherNodeChildrenInfo();
    auto geometryNode = stackNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    geometryNode->SetFrameOffset({0.0f, 0.0f});

    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto itemFrameNode = (*iter);
        if (itemFrameNode == frameNode) {
            continue;
        }
        GatherNodeChildInfo gatherNodeChildInfo;
        auto imageNode = CreateImageNode(itemFrameNode, gatherNodeChildInfo);
        CHECK_NULL_RETURN(imageNode, nullptr);
        stackNode->AddChild(imageNode);
        actuator->PushBackGatherNodeChild(gatherNodeChildInfo);
    }
    actuator->SetGatherNode(stackNode);
    return stackNode;
}

RefPtr<FrameNode> DragEventActuator::CreateImageNode(const RefPtr<FrameNode>& frameNode,
    GatherNodeChildInfo& gatherNodeChildInfo)
{
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);
    GetFrameNodePreviewPixelMap(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto pixelMap = gestureHub->GetDragPreviewPixelMap();
    int32_t width = 0;
    int32_t height = 0;
    if (pixelMap) {
        width = pixelMap->GetWidth();
        height = pixelMap->GetHeight();
    }
    auto offset = GetFloatImageOffset(frameNode, pixelMap);
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    
    imageNode->SetDragPreviewOptions(frameNode->GetDragPreviewOption());
    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(renderProps, nullptr);
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    renderProps->UpdateNeedBorderRadius(false);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(width), NG::CalcLength(height));
    props->UpdateUserDefinedIdealSize(targetSize);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_RETURN(imageContext, nullptr);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
    Vector5F rotate = Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    imageContext->UpdateTransformRotate(rotate);
    imageContext->UpdateClipEdge(true);
    imageContext->UpdateBorderRadius(BorderRadiusProperty(Dimension()));
    imageContext->UpdateOpacity(1.0f);
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = ClickEffectLevel::LIGHT;
    clickEffectInfo.scaleNumber = SCALE_NUMBER;
    imageContext->UpdateClickEffectLevel(clickEffectInfo);

    gatherNodeChildInfo = {imageNode, offset, width, height, width / 2.0f, height / 2.0f};
    return imageNode;
}

void DragEventActuator::MarkDirtyGatherNode(const RefPtr<FrameNode>& gatherNode)
{
    CHECK_NULL_VOID(gatherNode);
    gatherNode->MarkModifyDone();
    gatherNode->SetLayoutDirtyMarked(true);
    auto context = gatherNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(gatherNode);
    }

    auto children = gatherNode->GetChildren();
    for (const auto& child : children) {
        CHECK_NULL_VOID(child);
        auto imageNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(imageNode);
        imageNode->MarkModifyDone();
        imageNode->SetLayoutDirtyMarked(true);
        if (context) {
            context->FlushUITaskWithSingleDirtyNode(imageNode);
        }
    }
}

void DragEventActuator::ResetNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    bool defaultAnimationBeforeLifting = frameNode->GetDragPreviewOption().defaultAnimationBeforeLifting;
    if (!defaultAnimationBeforeLifting) {
        return;
    }
    auto frameContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(frameContext);
    frameContext->UpdateTransformScale({ 1.0f, 1.0f });
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
}

void DragEventActuator::MountGatherNode(const RefPtr<OverlayManager>& overlayManager,
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& gatherNode,
    const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
{
    if (!overlayManager || !frameNode || !gatherNode) {
        return;
    }

    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        auto windowScene = overlayManager->FindWindowScene(frameNode);
        overlayManager->MountGatherNodeToWindowScene(gatherNode, gatherNodeChildrenInfo, windowScene);
    } else {
        overlayManager->MountGatherNodeToRootNode(gatherNode, gatherNodeChildrenInfo);
    }
    MarkDirtyGatherNode(gatherNode);
}

void DragEventActuator::GetFrameNodePreviewPixelMap(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (dragPreviewInfo.inspectorId != "") {
        auto previewPixelMap = GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
        gestureHub->SetDragPreviewPixelMap(previewPixelMap);
        return;
    } else if (dragPreviewInfo.pixelMap != nullptr) {
        gestureHub->SetDragPreviewPixelMap(dragPreviewInfo.pixelMap);
        return;
    }
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap(true);
    gestureHub->SetDragPreviewPixelMap(pixelMap);
}

bool DragEventActuator::IsBelongToMultiItemNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (IsSelectedItemNode(frameNode)) {
        isSelectedItemNode_ = true;
        FindItemParentNode(frameNode);
        return false;
    }
    isSelectedItemNode_ = false;
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_RETURN(uiNode, false);
    while (!IsSelectedItemNode(uiNode)) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, false);
    }
    return true;
}

bool DragEventActuator::IsSelectedItemNode(const RefPtr<UINode>& uiNode)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto dragPreview = frameNode->GetDragPreviewOption();
    if (!dragPreview.isMultiSelectionEnabled) {
        return false;
    }
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    if (!isAllowedDrag) {
        return false;
    }
    if (frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG) {
        auto itemPattern = frameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_RETURN(itemPattern, false);
        if (itemPattern->IsSelected()) {
            return true;
        }
    }
    if (frameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
        auto itemPattern = frameNode->GetPattern<ListItemPattern>();
        CHECK_NULL_RETURN(itemPattern, false);
        if (itemPattern->IsSelected()) {
            return true;
        }
    }
    return false;
}

void DragEventActuator::FindItemParentNode(const RefPtr<FrameNode>& frameNode)
{
    itemParentNode_ = nullptr;
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() != V2::GRID_ITEM_ETS_TAG && frameNode->GetTag() != V2::LIST_ITEM_ETS_TAG) {
        return;
    }
    auto parentType = frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG ? V2::GRID_ETS_TAG : V2::LIST_ETS_TAG;
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_VOID(uiNode);
    while (uiNode->GetTag() != parentType) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_VOID(uiNode);
    }
    auto parentNode = AceType::DynamicCast<FrameNode>(uiNode);
    itemParentNode_ = parentNode;
}

bool DragEventActuator::IsNeedGather() const
{
    auto fatherNode = itemParentNode_.Upgrade();
    CHECK_NULL_RETURN(fatherNode, false);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    auto children = scrollPattern->GetVisibleSelectedItems();
    if (!isSelectedItemNode_ || children.size() < 1) {
        return false;
    }
    return true;
}

void DragEventActuator::AddTouchListener(const TouchRestrict& touchRestrict)
{
    CHECK_NULL_VOID(userCallback_);
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (!IsGlobalStatusSuitableForDragging() || !IsCurrentNodeStatusSuitableForDragging(frameNode, touchRestrict)) {
        gestureHub->RemoveTouchEvent(touchListener_);
        return;
    }
    auto focusHub = frameNode->GetFocusHub();
    bool hasContextMenuUsingGesture = focusHub ?
        focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU) : false;
    auto touchTask = [hasContextMenuUsingGesture, weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            actuator->HandleTouchUpEvent();
        } else if (info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            actuator->HandleTouchCancelEvent();
        } else if (info.GetTouches().front().GetTouchType() == TouchType::MOVE) {
            if (hasContextMenuUsingGesture) {
                auto point = Point(info.GetTouches().front().GetGlobalLocation().GetX(),
                                   info.GetTouches().front().GetGlobalLocation().GetY());
                actuator->HandleDragDampingMove(point, info.GetTouches().front().GetFingerId());
            }
            actuator->HandleTouchMoveEvent();
        }
    };
    gestureHub->RemoveTouchEvent(touchListener_);
    touchListener_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchListener_);
}

void DragEventActuator::HandleTouchUpEvent()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetHasGatherNode(false);
    DragAnimationHelper::PlayNodeResetAnimation(Claim(this));
    ResetResponseRegion();
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (IsNeedGather() && !manager->IsGatherWithMenu()) {
        SetGatherNode(nullptr);
        ClearGatherNodeChildrenInfo();
        auto manager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        manager->RemoveGatherNodeWithAnimation();
    }
}

void DragEventActuator::HandleTouchCancelEvent()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetHasGatherNode(false);
    ResetResponseRegion();
}

void DragEventActuator::HandleTouchMoveEvent()
{
    if (longPressRecognizer_ && isOnBeforeLiftingAnimation &&
        longPressRecognizer_->GetGestureDisposal() == GestureDisposal::REJECT) {
        SetGatherNode(nullptr);
        ClearGatherNodeChildrenInfo();
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto manager = pipelineContext->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        manager->RemoveGatherNode();
        isOnBeforeLiftingAnimation = false;
        ResetResponseRegion();
    }
}

void DragEventActuator::SetGatherNode(const RefPtr<FrameNode>& gatherNode)
{
    gatherNode_ = gatherNode;
}

RefPtr<FrameNode> DragEventActuator::GetGatherNode() const
{
    return gatherNode_;
}

const std::vector<GatherNodeChildInfo>& DragEventActuator::GetGatherNodeChildrenInfo() const
{
    return gatherNodeChildrenInfo_;
}

void DragEventActuator::ClearGatherNodeChildrenInfo()
{
    gatherNodeChildrenInfo_.clear();
}

void DragEventActuator::PushBackGatherNodeChild(GatherNodeChildInfo& gatherNodeChild)
{
    gatherNodeChildrenInfo_.emplace_back(gatherNodeChild);
}

const RefPtr<FrameNode> DragEventActuator::GetItemParentNode() const
{
    return itemParentNode_.Upgrade();
}

RefPtr<FrameNode> DragEventActuator::GetFrameNode()
{
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto frameNode = gestureHub->GetFrameNode();
    return frameNode;
}

void DragEventActuator::PrepareShadowParametersForDragData(const RefPtr<FrameNode>& frameNode,
    std::unique_ptr<JsonValue>& arkExtraInfoJson, float scale)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arkExtraInfoJson);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    auto shadow = dragPreviewOption.options.shadow;
    if (!shadow.has_value() || !shadow->IsValid()) {
        arkExtraInfoJson->Put("shadow_enable", false);
        return;
    }
    auto frameTag = frameNode->GetTag();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->IsTextCategoryComponent(frameTag) && gestureHub->GetTextDraggable() &&
        gestureHub->GetIsTextDraggable()) {
        auto stringPath = dragPreviewOption.options.shadowPath;
        RSPath path;
        if (path.BuildFromSVGString(stringPath)) {
            RSMatrix matrix;
            matrix.Set(RSMatrix::SCALE_X, scale);
            matrix.Set(RSMatrix::SCALE_Y, scale);
            path.Transform(matrix);
            stringPath = path.ConvertToSVGString();
        }
        arkExtraInfoJson->Put("drag_type", "text");
        arkExtraInfoJson->Put("drag_shadow_path", stringPath.c_str());
    } else {
        arkExtraInfoJson->Put("drag_type", "non-text");
    }
    arkExtraInfoJson->Put("shadow_enable", true);
    ParseShadowInfo(shadow.value(), arkExtraInfoJson);
}

void DragEventActuator::ParseShadowInfo(Shadow& shadow, std::unique_ptr<JsonValue>& arkExtraInfoJson)
{
    arkExtraInfoJson->Put("shadow_is_filled", shadow.GetIsFilled());
    arkExtraInfoJson->Put("drag_shadow_OffsetX", shadow.GetOffset().GetX());
    arkExtraInfoJson->Put("drag_shadow_OffsetY", shadow.GetOffset().GetY());
    arkExtraInfoJson->Put("shadow_mask", shadow.GetShadowType() == ShadowType::BLUR);
    int32_t argb = static_cast<int32_t>(shadow.GetColor().GetValue());
    arkExtraInfoJson->Put("drag_shadow_argb", argb);
    int64_t strategy = static_cast<int64_t>(shadow.GetShadowColorStrategy());
    arkExtraInfoJson->Put("shadow_color_strategy", strategy);
    arkExtraInfoJson->Put("shadow_corner", shadow.GetBlurRadius());
    arkExtraInfoJson->Put("shadow_elevation", shadow.GetElevation());
    arkExtraInfoJson->Put("shadow_is_hardwareacceleration", shadow.GetHardwareAcceleration());
}

std::optional<Shadow> DragEventActuator::GetDefaultShadow()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, std::nullopt);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, std::nullopt);
    auto colorMode = SystemProperties::GetColorMode();
    auto shadow = shadowTheme->GetShadow(ShadowStyle::OuterFloatingSM, colorMode);
    shadow.SetIsFilled(true);
    return shadow;
}

void DragEventActuator::PrepareRadiusParametersForDragData(const RefPtr<FrameNode>& frameNode,
    std::unique_ptr<JsonValue>& arkExtraInfoJson)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arkExtraInfoJson);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    auto borderRadius = dragPreviewOption.options.borderRadius;
    if (borderRadius.has_value()) {
        if (borderRadius.value().radiusTopLeft.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius1", borderRadius.value().radiusTopLeft.value().Value());
        }
        if (borderRadius.value().radiusTopRight.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius2", borderRadius.value().radiusTopRight.value().Value());
        }
        if (borderRadius.value().radiusBottomRight.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius3", borderRadius.value().radiusBottomRight.value().Value());
        }
        if (borderRadius.value().radiusBottomLeft.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius4", borderRadius.value().radiusBottomLeft.value().Value());
        }
    }
}

std::optional<BorderRadiusProperty> DragEventActuator::GetDefaultBorderRadius()
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(PREVIEW_BORDER_RADIUS);
    return borderRadius;
}

void DragEventActuator::ShowPreviewBadgeAnimation(
    const RefPtr<DragEventActuator>& actuator, const RefPtr<OverlayManager>& manager)
{
    auto gestureEventHub = actuator->gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureEventHub);
    auto frameNode = gestureEventHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    auto badgeNumber = dragPreviewOptions.GetCustomerBadgeNumber();
    int32_t childSize = badgeNumber.has_value() ? badgeNumber.value()
                                             : static_cast<int32_t>(manager->GetGatherNodeChildrenInfo().size()) + 1;
    auto textNode = CreateBadgeTextNode(frameNode, childSize, PIXELMAP_DRAG_SCALE_MULTIPLE, true);
    CHECK_NULL_VOID(textNode);
    auto column = manager->GetPixelMapNode();
    CHECK_NULL_VOID(column);
    column->AddChild(textNode);

    DragAnimationHelper::ShowBadgeAnimation(textNode);
}

RefPtr<FrameNode> DragEventActuator::CreateBadgeTextNode(
    const RefPtr<FrameNode>& frameNode, int32_t childSize, float previewScale, bool isUsePixelMapOffset)
{
    if (childSize <= 1) {
        return nullptr;
    }
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(textNode, nullptr);
    auto badgeLength = std::to_string(childSize).size();
    DragAnimationHelper::UpdateBadgeLayoutAndRenderContext(textNode, badgeLength, childSize);

    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_RETURN(textRenderContext, nullptr);
    auto pixelMap = frameNode->GetPixelMap();
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto offset = isUsePixelMapOffset ? GetFloatImageOffset(frameNode, pixelMap) : frameNode->GetPaintRectOffset();
    double textOffsetX = offset.GetX() + width * (previewScale + 1) / 2 -
        BADGE_RELATIVE_OFFSET.ConvertToPx() - (BADGE_RELATIVE_OFFSET.ConvertToPx() * badgeLength);
    double textOffsetY = offset.GetY() - height * (previewScale - 1) / 2 - BADGE_RELATIVE_OFFSET.ConvertToPx();
    textRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(textOffsetX), Dimension(textOffsetY)));
    textNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    textNode->MarkModifyDone();
    textNode->SetLayoutDirtyMarked(true);
    textNode->SetActive(true);
    auto context = textNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(textNode);
    }
    FlushSyncGeometryNodeTasks();
    return textNode;
}

void DragEventActuator::GetThumbnailPixelMapAsync(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    auto callback = [id = Container::CurrentId(), gestureHub](const RefPtr<PixelMap>& pixelMap) {
        ContainerScope scope(id);
        if (pixelMap != nullptr) {
            auto taskScheduler = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskScheduler);
            taskScheduler->PostTask(
                [gestureHub, pixelMap]() {
                    CHECK_NULL_VOID(gestureHub);
                    gestureHub->SetPixelMap(pixelMap);
                    TAG_LOGI(AceLogTag::ACE_DRAG, "Set thumbnail pixelMap async success.");
                },
                TaskExecutor::TaskType::UI, "ArkUIDragSetPixelMap");
        }
    };
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (!context->CreateThumbnailPixelMapAsyncTask(true, std::move(callback))) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Create thumbnail pixelMap async task failed!");
    }
}

void DragEventActuator::SetResponseRegionFull()
{
    if (!IsNeedGather() || isResponseRegionFull_) {
        return;
    }
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    
    responseRegion_ = gestureHub->GetResponseRegion();
    DimensionRect hotZoneRegion;

    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(-paintRect.GetOffset().GetX()),
        Dimension(-paintRect.GetOffset().GetY())));
    
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto geometryNode = rootNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto width = geometryNode->GetFrameSize().Width();
    auto height = geometryNode->GetFrameSize().Height();
    hotZoneRegion.SetSize(DimensionSize(Dimension(width), Dimension(height)));
    gestureHub->SetResponseRegion(std::vector<DimensionRect>({ hotZoneRegion }));
    isResponseRegionFull_ = true;
}

void DragEventActuator::ResetResponseRegion()
{
    if (isResponseRegionFull_) {
        auto gestureHub = gestureEventHub_.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetResponseRegion(responseRegion_);
        isResponseRegionFull_ = false;
    }
}

void DragEventActuator::PrepareFinalPixelMapForDragThroughTouch(RefPtr<PixelMap> pixelMap, bool immediately)
{
    ResetPreScaledPixelMapForDragThroughTouch();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto windowScale = dragDropManager->GetWindowScale();
    float scale = windowScale * PIXELMAP_DRAG_SCALE_MULTIPLE;

    auto task = [weak = WeakClaim(this), pixelMap, scale] () {
        auto actuator = weak.Upgrade();
        CHECK_NULL_VOID(actuator);
        actuator->DoPixelMapScaleForDragThroughTouch(pixelMap, scale);
    };

    if (immediately) {
        task();
        return;
    }

    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    taskScheduler->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIPrepareScaledPixel", PriorityType::VIP);
}

void DragEventActuator::DoPixelMapScaleForDragThroughTouch(RefPtr<PixelMap> pixelMap, float targetScale)
{
#if defined(PIXEL_MAP_SUPPORTED)
    preScaledPixelMap_ = PixelMap::CopyPixelMap(pixelMap);
    if (!preScaledPixelMap_) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Copy preScaledPixelMap_ is failure!");
        return;
    }
    preScaledPixelMap_->Scale(targetScale, targetScale, AceAntiAliasingOption::HIGH);
    preScaleValue_ = targetScale;
#endif
}

RefPtr<PixelMap> DragEventActuator::GetPreScaledPixelMapForDragThroughTouch(float& preScale)
{
    preScale = preScaleValue_;
    return preScaledPixelMap_;
}

void DragEventActuator::ResetPreScaledPixelMapForDragThroughTouch()
{
    preScaledPixelMap_ = nullptr;
    preScaleValue_ = 1.0f;
}

void DragEventActuator::RecordMenuWrapperNodeForDrag(int32_t targetId)
{
    auto subWindow = SubwindowManager::GetInstance()->GetCurrentWindow();
    CHECK_NULL_VOID(subWindow);
    auto overlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuWrapperNode = overlayManager->GetMenuNode(targetId);
    CHECK_NULL_VOID(menuWrapperNode);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetMenuWrapperNode(menuWrapperNode);
}
} // namespace OHOS::Ace::NG
