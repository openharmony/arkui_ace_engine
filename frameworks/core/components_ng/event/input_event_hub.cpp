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

#include "core/components_ng/event/input_event_hub.h"

#include "core/components_ng/event/event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

InputEventHub::InputEventHub(const WeakPtr<EventHub>& eventHub) : eventHub_(eventHub) {}

RefPtr<FrameNode> InputEventHub::GetFrameNode() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->GetFrameNode() : nullptr;
}

bool InputEventHub::ProcessMouseTestHit(const OffsetF& coordinateOffset, MouseTestResult& onMouseResult,
    MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;

    if (mouseEventActuator_) {
        mouseEventActuator_->OnCollectMouseEvent(coordinateOffset, getEventTargetImpl, onMouseResult, hoverNode);
    }
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectHoverEvent(coordinateOffset, getEventTargetImpl, onHoverResult);
    }
    return false;
}
} // namespace OHOS::Ace::NG