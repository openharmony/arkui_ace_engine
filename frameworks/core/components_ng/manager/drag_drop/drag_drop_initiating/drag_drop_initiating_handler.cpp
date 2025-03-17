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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_handler.h"

namespace OHOS::Ace::NG {
DragDropInitiatingHandler::DragDropInitiatingHandler(const RefPtr<FrameNode>& frameNode)
{
    if (!initiatingFlow_) {
        initiatingFlow_ = AceType::MakeRefPtr<DragDropInitiatingStateMachine>(frameNode);
    }
}

DragDropInitiatingStatus DragDropInitiatingHandler::GetDragDropInitiatingStatus()
{
    if (!initiatingFlow_) {
        return DragDropInitiatingStatus::IDLE;
    }
    return initiatingFlow_->GetDragDropInitiatingStatus();
}

void DragDropInitiatingHandler::NotifyLongPressOnAction(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleLongPressOnAction(info);
}

void DragDropInitiatingHandler::NotifyLongPressOnActionEnd(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleLongPressOnActionEnd(info);
}

void DragDropInitiatingHandler::NotifyLongPressOnActionCancel(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleLongPressOnActionCancel(info);
}

void DragDropInitiatingHandler::NotifyPreviewLongPressOnAction(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePreviewLongPressOnAction(info);
}

void DragDropInitiatingHandler::NotifyPreviewLongPressOnActionEnd(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePreviewLongPressOnActionEnd(info);
}

void DragDropInitiatingHandler::NotifyPreviewLongPressOnActionCancel(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePreviewLongPressOnActionCancel(info);
}

void DragDropInitiatingHandler::NotifyPanOnActionStart(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePanOnActionStart(info);
}

void DragDropInitiatingHandler::NotifyPanOnActionUpdate(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePanOnActionUpdate(info);
}

void DragDropInitiatingHandler::NotifyPanOnActionEnd(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePanOnActionEnd(info);
}

void DragDropInitiatingHandler::NotifyPanOnActionCancel(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePanOnActionCancel(info);
}

void DragDropInitiatingHandler::NotifyPanOnReject()
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePanOnReject();
}

void DragDropInitiatingHandler::NotifySequenceOnActionCancel(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleSequenceOnActionCancel(info);
}

void DragDropInitiatingHandler::NotifyHitTesting(const TouchEvent& touchEvent)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->InitializeState();
    initiatingFlow_->HandleHitTesting(touchEvent);
}

void DragDropInitiatingHandler::NotifyTouchEvent(const TouchEvent& touchEvent)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleTouchEvent(touchEvent);
}

void DragDropInitiatingHandler::NotifyPullEvent(const DragPointerEvent& dragPointerEvent)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandlePullEvent(dragPointerEvent);
}

void DragDropInitiatingHandler::NotifyReStartDrag(const GestureEvent& info)
{
    CHECK_NULL_VOID(initiatingFlow_);
    initiatingFlow_->HandleReStartDrag(info);
}

RefPtr<PixelMap> DragDropInitiatingHandler::GetPreScaledPixelMapForDragThroughTouch(float& preScale)
{
    CHECK_NULL_RETURN(initiatingFlow_, nullptr);
    auto params = initiatingFlow_->GetDragDropInitiatingParams();
    preScale = params.preScaleValue;
    return params.preScaledPixelMap;
}

void DragDropInitiatingHandler::ResetPreScaledPixelMapForDragThroughTouch()
{
    CHECK_NULL_VOID(initiatingFlow_);
    auto& params = initiatingFlow_->GetDragDropInitiatingParams();
    params.preScaledPixelMap = nullptr;
    params.preScaleValue = 1.0f;
}

void DragDropInitiatingHandler::NotifyDragStart()
{
    CHECK_NULL_VOID(initiatingFlow_);
    return initiatingFlow_->HandleDragStart();
}

void DragDropInitiatingHandler::NotifyDragEnd()
{
    CHECK_NULL_VOID(initiatingFlow_);
    return initiatingFlow_->HandleDragEnd();
}

void DragDropInitiatingHandler::NotifyTransDragWindowToFwk()
{
    CHECK_NULL_VOID(initiatingFlow_);
    return initiatingFlow_->TransDragWindowToFwk();
}

void DragDropInitiatingHandler::NotifyMenuShow(bool isMenuShow)
{
    CHECK_NULL_VOID(initiatingFlow_);
    return initiatingFlow_->TransMenuShow(isMenuShow);
}

void DragDropInitiatingHandler::SetThumbnailCallback(std::function<void(Offset)>&& callback)
{
    CHECK_NULL_VOID(initiatingFlow_);
    return initiatingFlow_->SetThumbnailCallback(std::move(callback));
}

bool DragDropInitiatingHandler::IsNeedGather()
{
    if (initiatingFlow_) {
        auto params = initiatingFlow_->GetDragDropInitiatingParams();
        return params.isNeedGather;
    }
    return false;
}
} // namespace OHOS::Ace::NG
