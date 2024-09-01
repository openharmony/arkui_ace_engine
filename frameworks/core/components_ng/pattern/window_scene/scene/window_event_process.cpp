/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "window_event_process.h"

#include "pointer_event.h"

namespace OHOS::Ace::NG {
WindowEventProcess::WindowEventProcess() {}

WindowEventProcess::~WindowEventProcess() {}

void WindowEventProcess::ProcessEnterLeaveEvent(int32_t nodeId,
    sptr<Rosen::Session> session, const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(pointerEvent);
    std::shared_ptr<MMI::PointerEvent> enterEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);

    int32_t action = pointerEvent->GetPointerAction();
    if (action == MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW) {
        lastWindowNodeId_ = nodeId;
        lastWeakSession_ = session;
        lastPointEvent_ = enterEvent;
        return;
    }
    auto lastSession = lastWeakSession_.promote();
    if (lastSession == nullptr) {
        enterEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW);
        DispatchPointerEvent(session, enterEvent);
        lastWindowNodeId_ = nodeId;
        lastWeakSession_ = session;
        lastPointEvent_ = enterEvent;
        return;
    }

    if (lastWindowNodeId_ != nodeId) {
        if (lastPointEvent_ != nullptr) {
            lastPointEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
            lastPointEvent_->SetId(pointerEvent->GetId());
            DispatchPointerEvent(lastSession, lastPointEvent_);

            enterEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW);
            DispatchPointerEvent(session, enterEvent);
        }
        lastWindowNodeId_ = nodeId;
        lastWeakSession_ = session;
    }
    lastPointEvent_ = enterEvent;
}

void WindowEventProcess::ProcessWindowMouseEvent(int32_t nodeId,
    sptr<Rosen::Session> session, const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(pointerEvent);
    if (pointerEvent->GetSourceType() != MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        return;
    }
    int32_t action = pointerEvent->GetPointerAction();
    if ((action == MMI::PointerEvent::POINTER_ACTION_MOVE &&
        pointerEvent->GetButtonId() == MMI::PointerEvent::BUTTON_NONE) ||
        (action == MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW)) {
        ProcessEnterLeaveEvent(nodeId, session, pointerEvent);
    }
    if (action == MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW) {
        CleanWindowMouseRecord();
    }
}

void WindowEventProcess::ProcessWindowDragEvent(int32_t nodeId,
    sptr<Rosen::Session> session, const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(pointerEvent);
    int32_t action = pointerEvent->GetPointerAction();
    if (action == MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        CleanWindowDragEvent();
        return;
    }
    if (action != MMI::PointerEvent::POINTER_ACTION_PULL_MOVE) {
        return;
    }
    std::shared_ptr<MMI::PointerEvent> event = std::make_shared<MMI::PointerEvent>(*pointerEvent);
    if ((lastDragWindowNodeId_ != -1) && (nodeId != lastDragWindowNodeId_)) {
        if (lastDragPointEvent_ != nullptr) {
            lastDragPointEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW);
            lastDragPointEvent_->SetId(pointerEvent->GetId());
            auto lastSession = lastDragSession_.promote();
            if (lastSession != nullptr) {
                DispatchPointerEvent(lastSession, lastDragPointEvent_);
            }
            event->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW);
            DispatchPointerEvent(session, event);
            if (event->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
                UpdateWindowMouseRecord(nodeId, session, event);
            }
        }
    }
    lastDragWindowNodeId_ = nodeId;
    lastDragSession_ = session;
    lastDragPointEvent_ = event;
}

void WindowEventProcess::CleanWindowMouseRecord()
{
    lastWindowNodeId_ = -1;
    lastWeakSession_ = nullptr;
    lastPointEvent_ = nullptr;
}

void WindowEventProcess::CleanWindowDragEvent()
{
    lastDragWindowNodeId_ = -1;
    lastDragSession_ = nullptr;
    lastDragPointEvent_ = nullptr;
}

void WindowEventProcess::UpdateWindowMouseRecord(int32_t nodeId,
    sptr<Rosen::Session> session, const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    lastWindowNodeId_ = nodeId;
    lastWeakSession_ = session;
    lastPointEvent_ = pointerEvent;
}

void WindowEventProcess::DispatchPointerEvent(sptr<Rosen::Session> session,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(pointerEvent);
    session->TransferPointerEvent(pointerEvent);
}
} // namespace OHOS::Ace::NG
