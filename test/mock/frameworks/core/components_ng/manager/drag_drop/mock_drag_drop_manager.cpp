/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

#include "core/components/common/layout/grid_column_info.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_detector.h"

namespace OHOS::Ace::NG {
DragDropManager::DragDropManager() = default;
DragDropManager::~DragDropManager() = default;

std::string DragDropManager::GetExtraInfo()
{
    return {};
}

void DragDropManager::OnDragMove(
    const DragPointerEvent& pointerEvent, const std::string& extraInfo, const RefPtr<FrameNode>& node)
{
    (void)pointerEvent;
    (void)extraInfo;
    (void)node;
}

void DragDropManager::DispatchLastDragEventVoluntarily(bool isCancel)
{
    (void)isCancel;
}

void DragDropManager::DoDragMoveAnimate(const DragPointerEvent& pointerEvent)
{
    (void)pointerEvent;
}

bool DragDropManager::IsMSDPDragging() const
{
    return false;
}

void DragDropManager::HandleTouchEvent(const TouchEvent& event, const RefPtr<NG::FrameNode>& node)
{
    (void)event;
    (void)node;
}

void DragDropManager::HandleMouseEvent(const MouseEvent& event)
{
    isDragCancel_ = (event.button == MouseButton::RIGHT_BUTTON && event.action == MouseAction::PRESS);
}

void DragDropManager::HandlePipelineOnHide() {}

void DragDropManager::OnDragEnd() {}

void DragDropManager::HandleDragEvent(
    const DragPointerEvent& pointerEvent, DragEventAction action, const RefPtr<FrameNode>& node)
{
    (void)pointerEvent;
    (void)node;
    switch (action) {
        case DragEventAction::DRAG_EVENT_START:
            preTargetFrameNode_.Reset();
            break;
        case DragEventAction::DRAG_EVENT_PULL_CANCEL:
            dragDropState_ = DragDropMgrState::IDLE;
            break;
        case DragEventAction::DRAG_EVENT_PULL_THROW:
            isWindowConsumed_ = false;
            break;
        default:
            break;
    }
}

void DragDropManager::SetDragAnimationPointerEvent(const DragPointerEvent& pointerEvent, const RefPtr<FrameNode>& node)
{
    (void)node;
    dragAnimationPointerEvent_ = pointerEvent;
}
} // namespace OHOS::Ace::NG
