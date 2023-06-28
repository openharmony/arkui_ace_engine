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

void WindowEventProcess::ProcessWindowEvent(const RefPtr<WindowNode>& windowNode,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent, bool isDrag)
{
    CHECK_NULL_VOID(windowNode);
    auto lastWindowNode = lastWeakWindowNode_.Upgrade();
    if (lastWindowNode == nullptr) {
        LOGD("First enter window, lastWindowNode is not exit");
        std::shared_ptr<MMI::PointerEvent> enterEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);
        enterEvent->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW);
        DispatchPointerEvent(windowNode, enterEvent);
        lastWeakWindowNode_ = windowNode;
        lastPointEvent_ = enterEvent;
        return;
    }

    if (windowNode->GetId() != lastWindowNode->GetId()) {
        LOGD("Window switching");
        std::shared_ptr<MMI::PointerEvent> enterEvent = std::make_shared<MMI::PointerEvent>(*pointerEvent);
        int32_t dispatchAction = isDrag ? MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW :
            MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW;
        lastPointEvent_->SetPointerAction(MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW);
        DispatchPointerEvent(lastWindowNode, lastPointEvent_);

        dispatchAction = isDrag ? MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW :
            MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW;
        enterEvent->SetPointerAction(dispatchAction);
        DispatchPointerEvent(windowNode, enterEvent);
        lastWeakWindowNode_ = windowNode;
        lastPointEvent_ = enterEvent;
    }
}

void WindowEventProcess::DispatchPointerEvent(const RefPtr<WindowNode>& windowNode,
    const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(windowNode);
    auto pattern = windowNode->GetPattern<WindowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->DispatchPointerEvent(pointerEvent);
}
}