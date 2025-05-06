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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

InputEventHub::InputEventHub(const WeakPtr<EventHub>& eventHub) : eventHub_(eventHub) {}

RefPtr<FrameNode> InputEventHub::GetFrameNode() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->GetFrameNode() : nullptr;
}

bool InputEventHub::ProcessMouseTestHit(const OffsetF& coordinateOffset, TouchTestResult& result)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;

    if (mouseEventActuator_) {
        mouseEventActuator_->OnCollectMouseEvent(coordinateOffset, getEventTargetImpl, result);
    }
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectHoverEvent(coordinateOffset, getEventTargetImpl, result);
    }
    if (hoverEffectActuator_) {
        hoverEffectActuator_->OnCollectHoverEffect(coordinateOffset, getEventTargetImpl, result);
    }
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    if (accessibilityHoverEventActuator_) {
        accessibilityHoverEventActuator_->OnCollectAccessibilityHoverEvent(
            coordinateOffset, getEventTargetImpl, result, host);
    }
    return false;
}

bool InputEventHub::ProcessTipsMouseTestHit(const OffsetF& coordinateOffset, TouchTestResult& result)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectHoverEventForTips(coordinateOffset, getEventTargetImpl, result);
    }
    return false;
}

bool InputEventHub::ProcessPenHoverTestHit(const OffsetF& coordinateOffset, TouchTestResult& result)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectPenHoverEvent(coordinateOffset, getEventTargetImpl, result, host);
    }

    if (hoverMoveEventActuator_) {
        hoverMoveEventActuator_->OnCollectPenHoverMoveEvent(coordinateOffset, getEventTargetImpl, result, host);
    }

    return false;
}

bool InputEventHub::ProcessAxisTestHit(const OffsetF& coordinateOffset, AxisTestResult& onAxisResult)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;

    if (axisEventActuator_) {
        axisEventActuator_->OnCollectAxisEvent(coordinateOffset, getEventTargetImpl, onAxisResult);
    }
    return false;
}

// register showMenu callback (always replace)
void InputEventHub::BindContextMenu(OnMouseEventFunc&& showMenu)
{
    if (showMenu_) {
        RemoveOnMouseEvent(showMenu_);
    }
    showMenu_ = MakeRefPtr<InputEvent>(std::move(showMenu));
    AddOnMouseEvent(showMenu_);
}

std::string InputEventHub::GetHoverEffectStr() const
{
    switch (hoverEffectType_) {
        case HoverEffectType::AUTO:
            return "HoverEffect.Auto";
        case HoverEffectType::SCALE:
            return "HoverEffect.Scale";
        case HoverEffectType::BOARD:
            return "HoverEffect.Highlight";
        case HoverEffectType::NONE:
            return "HoverEffect.None";
        default:
            return "HoverEffect.Auto";
    }
}

void InputEventHub::SetHoverEffect(HoverEffectType type)
{
    if (!hoverEffectActuator_) {
        hoverEffectActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    auto frameNode = GetFrameNode();
    if (frameNode && hoverEffectType_ != type) {
        frameNode->AnimateHoverEffect(false);
    }
    hoverEffectType_ = type;
}

} // namespace OHOS::Ace::NG