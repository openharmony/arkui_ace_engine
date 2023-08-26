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

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "frameworks/core/event/ace_events.h"
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
        LOGD("Window switching, enter window:%{public}d, leave window:%{public}d",
            nodeId, lastWindowNodeId_);
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

void WindowEventProcess::ProcessWindowDragEvent(const RefPtr<WindowNode>& windowNode,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(windowNode);
    CHECK_NULL_VOID(pointerEvent);
    std::shared_ptr<MMI::PointerEvent> event = std::make_shared<MMI::PointerEvent>(*pointerEvent);
    auto lastWindowNode = lastDragWindowNode_.Upgrade();
    if ((lastWindowNode != nullptr) && (windowNode->GetId() != lastWindowNode->GetId())) {
        LOGD("Window switching, pull in window:%{public}d, pull out window:%{public}d",
            windowNode->GetId(), lastWindowNode->GetId());
        if (lastDragPointEvent_ != nullptr) {
            lastDragPointEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW);
            lastDragPointEvent_->SetId(pointerEvent->GetId());
            DispatchPointerEvent(lastWindowNode, lastDragPointEvent_);

            event->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW);
            DispatchPointerEvent(windowNode, event);
            if (event->GetSourceType() == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
                UpdateWindowMouseRecord(windowNode, event);
            }
        }
    }
    lastDragWindowNode_ = windowNode;
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
    lastDragWindowNode_ = nullptr;
    lastDragPointEvent_ = nullptr;
}

void WindowEventProcess::UpdateWindowMouseRecord(const RefPtr<WindowNode>& windowNode,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(windowNode);
    lastWindowNodeId_ = windowNode->GetId();
    auto pattern = windowNode->GetPattern<WindowPattern>();
    CHECK_NULL_VOID(pattern);
    lastWeakSession_ = pattern->GetSession();
    lastPointEvent_ = pointerEvent;
}

void WindowEventProcess::DispatchPointerEvent(const RefPtr<WindowNode>& windowNode,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(windowNode);
    auto pattern = windowNode->GetPattern<WindowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->DispatchPointerEvent(pointerEvent);
}

void WindowEventProcess::DispatchPointerEvent(sptr<Rosen::Session> session,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session);
    CHECK_NULL_VOID(pointerEvent);
    session->TransferPointerEvent(pointerEvent);
}
} // namespace OHOS::Ace::NG
