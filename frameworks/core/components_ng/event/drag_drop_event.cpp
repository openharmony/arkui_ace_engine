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

#include "core/components_ng/event/drag_drop_event.h"

#include "base/log/ace_trace.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DURATION = 500;
constexpr int32_t PREVIEW_LONG_PRESS_RECOGNIZER = 800;
constexpr int32_t DEFAULT_DRAG_FINGERS = 1;
constexpr Dimension DEFAULT_DRAG_DISTANCE = 10.0_vp;
constexpr PanDirection DEFAULT_DRAG_DIRECTION = { PanDirection::ALL };
} // namespace

DragDropEventActuator::DragDropEventActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : DragEventActuator(gestureEventHub), gestureEventHub_(gestureEventHub)
{
    panRecognizer_ =
        MakeRefPtr<PanRecognizer>(DEFAULT_DRAG_FINGERS, DEFAULT_DRAG_DIRECTION, DEFAULT_DRAG_DISTANCE.ConvertToPx());
    panRecognizer_->SetIsForDrag(true);
    panRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragPanDistanceMouse = DRAG_PAN_DISTANCE_MOUSE;
    auto appTheme = pipeline->GetTheme<AppTheme>();
    if (appTheme) {
        dragPanDistanceMouse = appTheme->GetDragPanDistanceMouse();
    }
    panRecognizer_->SetMouseDistance(dragPanDistanceMouse.ConvertToPx());
    longPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, DEFAULT_DRAG_FINGERS, false, true);
    longPressRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(PREVIEW_LONG_PRESS_RECOGNIZER, DEFAULT_DRAG_FINGERS, false, true);
    previewLongPressRecognizer_->SetGestureInfo(
        MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_->SetGestureHub(gestureEventHub_);
    auto frameNode = gestureEventHub.Upgrade()->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    dragDropInitiatingHandler_ = AceType::MakeRefPtr<DragDropInitiatingHandler>(frameNode);
    SetIsNewFwk(true);
}

void DragDropEventActuator::InitPanAction()
{
    panRecognizer_->SetOnActionStart(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPanOnActionStart(info);
        });
    panRecognizer_->SetOnActionUpdate(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPanOnActionUpdate(info);
        });
    panRecognizer_->SetOnActionEnd(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPanOnActionEnd(info);
        });
    panRecognizer_->SetOnActionCancel(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPanOnActionCancel(info);
        });
    panRecognizer_->SetOnReject([weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)]() {
        auto handler = weakHandler.Upgrade();
        CHECK_NULL_VOID(handler);
        handler->NotifyPanOnReject();
    });
}

void DragDropEventActuator::InitLongPressAction()
{
    longPressRecognizer_->SetOnAction(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyLongPressOnAction(info);
        });
    previewLongPressRecognizer_->SetOnAction(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPreviewLongPressOnAction(info);
        });
    previewLongPressRecognizer_->SetOnActionCancel(
        [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](GestureEvent& info) {
            auto handler = weakHandler.Upgrade();
            CHECK_NULL_VOID(handler);
            handler->NotifyPreviewLongPressOnActionCancel(info);
        });
}

void DragDropEventActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, ResponseLinkResult& responseLinkResult)
{
    InitDragDropStatusToIdle();
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (!DragDropFuncWrapper::IsGlobalStatusSuitableForDragging() ||
        !DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(frameNode, touchRestrict) ||
        (DragDropFuncWrapper::IsBelongToMultiItemNode(frameNode) &&
        !DragDropFuncWrapper::IsSelectedItemNode(frameNode))) {
        return;
    }
    CHECK_NULL_VOID(dragDropInitiatingHandler_);
    auto touchEvent = touchRestrict.touchEvent;
    RecordTouchDownPoint(touchEvent);
    dragDropInitiatingHandler_->NotifyHitTesting(touchEvent);
    InitPanAction();
    panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    auto sequenceOnActionCancel = [weakHandler = WeakPtr<DragDropInitiatingHandler>(dragDropInitiatingHandler_)](
                                      GestureEvent& info) {
        auto handler = weakHandler.Upgrade();
        CHECK_NULL_VOID(handler);
        handler->NotifySequenceOnActionCancel(info);
    };
    if (touchRestrict.sourceType == SourceType::MOUSE) {
        std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer_ };
        SequencedRecognizer_ = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
        SequencedRecognizer_->RemainChildOnResetStatus();
        SequencedRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        SequencedRecognizer_->SetOnActionCancel(sequenceOnActionCancel);
        SequencedRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        result.emplace_back(SequencedRecognizer_);
        return;
    }
    InitLongPressAction();
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { longPressRecognizer_, panRecognizer_ };
    SequencedRecognizer_ = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    SequencedRecognizer_->RemainChildOnResetStatus();
    previewLongPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    previewLongPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    longPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    longPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    SequencedRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    SequencedRecognizer_->SetOnActionCancel(sequenceOnActionCancel);
    SequencedRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    SequencedRecognizer_->SetIsEventHandoverNeeded(true);
    result.emplace_back(SequencedRecognizer_);
    result.emplace_back(previewLongPressRecognizer_);
}

void DragDropEventActuator::CopyEvent(const RefPtr<DragDropEventActuator>& dragDropEventActuator)
{
    auto fingers = GetFingers();
    auto direction = GetDirection();
    auto distance = GetDistance();
    panRecognizer_ = MakeRefPtr<PanRecognizer>(fingers, direction, distance);
    panRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION, fingers, false, false);
    longPressRecognizer_->SetGestureInfo(MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    previewLongPressRecognizer_ =
        AceType::MakeRefPtr<LongPressRecognizer>(PREVIEW_LONG_PRESS_RECOGNIZER, fingers, false, false);
    previewLongPressRecognizer_->SetGestureInfo(
        MakeRefPtr<GestureInfo>(GestureTypeName::DRAG, GestureTypeName::DRAG, true));
    gestureEventHub_ = dragDropEventActuator->gestureEventHub_;
    CHECK_NULL_VOID(dragDropEventActuator->dragDropInitiatingHandler_);
    auto originDragDropInitiatingHandler = dragDropEventActuator->dragDropInitiatingHandler_;
    if (originDragDropInitiatingHandler) {
        dragDropInitiatingHandler_ = originDragDropInitiatingHandler;
    }
}

void DragDropEventActuator::RestartDragTask(const GestureEvent& info)
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->NotifyReStartDrag(info);
    }
}

void DragDropEventActuator::NotifyDragStart()
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->NotifyDragStart();
    }
}

bool DragDropEventActuator::GetIsNotInPreviewState() const
{
    if (dragDropInitiatingHandler_) {
        return dragDropInitiatingHandler_->GetDragDropInitiatingStatus() != DragDropInitiatingStatus::LIFTING;
    }
    return true;
}

RefPtr<PixelMap> DragDropEventActuator::GetPreScaledPixelMapForDragThroughTouch(float& preScale)
{
    auto gestureHub = gestureEventHub_.Upgrade();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    if (dragDropInitiatingHandler_ && !gestureHub->GetTextDraggable()) {
        return dragDropInitiatingHandler_->GetPreScaledPixelMapForDragThroughTouch(preScale);
    }
    return nullptr;
}

void DragDropEventActuator::ResetPreScaledPixelMapForDragThroughTouch()
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->ResetPreScaledPixelMapForDragThroughTouch();
    }
}

void DragDropEventActuator::NotifyTransDragWindowToFwk()
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->NotifyTransDragWindowToFwk();
    }
}

void DragDropEventActuator::NotifyMenuShow(bool isMenuShow)
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->NotifyMenuShow(isMenuShow);
    }
}

void DragDropEventActuator::SetThumbnailCallback(std::function<void(Offset)>&& callback)
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->SetThumbnailCallback(std::move(callback));
    }
}

void DragDropEventActuator::HandleTouchEvent(const TouchEventInfo& info, bool isRestartDrag)
{
    if (info.GetTouches().empty()) {
        return;
    }
    if (dragDropInitiatingHandler_) {
        TouchEvent touchEvent;
        touchEvent.type = info.GetTouches().front().GetTouchType();
        touchEvent.x = info.GetTouches().front().GetGlobalLocation().GetX();
        touchEvent.y = info.GetTouches().front().GetGlobalLocation().GetY();
        touchEvent.screenX = info.GetTouches().front().GetScreenLocation().GetX();
        touchEvent.screenY = info.GetTouches().front().GetScreenLocation().GetY();
        touchEvent.id = info.GetTouches().front().GetFingerId();
        dragDropInitiatingHandler_->NotifyTouchEvent(touchEvent);
    }
}

bool DragDropEventActuator::IsNeedGather() const
{
    if (dragDropInitiatingHandler_) {
        return dragDropInitiatingHandler_->IsNeedGather();
    }
    return false;
}

void DragDropEventActuator::NotifyDragEnd()
{
    if (dragDropInitiatingHandler_) {
        dragDropInitiatingHandler_->NotifyDragEnd();
    }
}
} // namespace OHOS::Ace::NG