/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "core/common/event_manager.h"
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

    CreateMouseEventActuator();
    CreateHoverEventActuator();
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
    ACE_UINODE_TRACE(host);
    CreateAccessibilityHoverEventActuator();
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

    CreateMouseEventActuator();
    CreateHoverEventActuator();
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectHoverEventForTips(coordinateOffset, getEventTargetImpl, result);
    }
    if (mouseEventActuator_) {
        mouseEventActuator_->OnCollectMouseEventForTips(coordinateOffset, getEventTargetImpl, result);
    }
    return false;
}

bool InputEventHub::ProcessPenHoverTestHit(const OffsetF& coordinateOffset, TouchTestResult& result)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    CreateHoverEventActuator();
    if (hoverEventActuator_) {
        hoverEventActuator_->OnCollectPenHoverEvent(coordinateOffset, getEventTargetImpl, result, host);
    }

    CreateHoverMoveEventActuator();
    if (hoverMoveEventActuator_) {
        hoverMoveEventActuator_->OnCollectPenHoverMoveEvent(coordinateOffset, getEventTargetImpl, result, host);
    }

    return false;
}

bool InputEventHub::ProcessAxisTestHit(
    const OffsetF& coordinateOffset, AxisTestResult& onAxisResult, bool isCoastingAxis)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;

    if (!isCoastingAxis) {
        CreateAxisEventActuator();
        if (axisEventActuator_) {
            axisEventActuator_->OnCollectAxisEvent(coordinateOffset, getEventTargetImpl, onAxisResult);
        }
        return false;
    }

    CreateCoastingAxisEventActuator();
    if (coastingAxisEventActuator_) {
        coastingAxisEventActuator_->OnCollectCoastingAxisEvent(onAxisResult);
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

ACE_FORCE_EXPORT void InputEventHub::SetHoverEffect(HoverEffectType type)
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

void InputEventHub::AddTouchpadInteractionListenerInner(TouchpadInteractionCallback&& callback)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto weakPtr = WeakPtr<FrameNode>(frameNode);
    eventManager->AddTouchpadInteractionListenerInner(frameNode->GetId(), { weakPtr, std::move(callback) });
}

void InputEventHub::CreateMouseEventActuator()
{
    CHECK_NULL_VOID(userMouseFunc_ || userJSFrameNodeMouseFunc_ || !mouseInputEvents_.empty());
    if (!mouseEventActuator_) {
        mouseEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userMouseFunc_) {
        mouseEventActuator_->ReplaceInputEvent(std::move(userMouseFunc_));
    }
    if (userJSFrameNodeMouseFunc_) {
        mouseEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(userJSFrameNodeMouseFunc_));
    }
    if (!mouseInputEvents_.empty()) {
        for (auto& inputEvent : mouseInputEvents_) {
            mouseEventActuator_->AddInputEvent(inputEvent);
        }
        mouseInputEvents_.clear();
    }
}

void InputEventHub::CreateHoverEventActuator()
{
    CHECK_NULL_VOID(userHoverFunc_ || userJSFrameNodeHoverFunc_ || !hoverInputEvents_.empty());
    if (!hoverEventActuator_) {
        hoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userHoverFunc_) {
        hoverEventActuator_->ReplaceInputEvent(std::move(userHoverFunc_));
    }
    if (userJSFrameNodeHoverFunc_) {
        hoverEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(userJSFrameNodeHoverFunc_));
    }
    if (!hoverInputEvents_.empty()) {
        for (auto& inputEvent : hoverInputEvents_) {
            hoverEventActuator_->AddInputEvent(inputEvent);
        }
        hoverInputEvents_.clear();
    }
}

void InputEventHub::CreateHoverMoveEventActuator()
{
    CHECK_NULL_VOID(userHoverMoveFunc_ || userJSFrameNodeHoverMoveFunc_ || !hoverMoveInputEvents_.empty());
    if (!hoverMoveEventActuator_) {
        hoverMoveEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userHoverMoveFunc_) {
        hoverMoveEventActuator_->ReplaceInputEvent(std::move(userHoverMoveFunc_));
    }
    if (userJSFrameNodeHoverMoveFunc_) {
        hoverMoveEventActuator_->ReplaceJSFrameNodeInputEvent(std::move(userJSFrameNodeHoverMoveFunc_));
    }
    if (!hoverMoveInputEvents_.empty()) {
        for (auto& inputEvent : hoverMoveInputEvents_) {
            hoverMoveEventActuator_->AddInputEvent(inputEvent);
        }
        hoverMoveInputEvents_.clear();
    }
}

void InputEventHub::CreateAxisEventActuator()
{
    CHECK_NULL_VOID(userAxisFunc_ || !axisInputEvents_.empty());
    if (!axisEventActuator_) {
        axisEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userAxisFunc_) {
        axisEventActuator_->ReplaceInputEvent(std::move(userAxisFunc_));
    }
    if (!axisInputEvents_.empty()) {
        for (auto& inputEvent : axisInputEvents_) {
            axisEventActuator_->AddInputEvent(inputEvent);
        }
        axisInputEvents_.clear();
    }
}

void InputEventHub::CreateCoastingAxisEventActuator()
{
    CHECK_NULL_VOID(userCoastingAxisFunc_);
    if (!coastingAxisEventActuator_) {
        coastingAxisEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userCoastingAxisFunc_) {
        coastingAxisEventActuator_->ReplaceInputEvent(std::move(userCoastingAxisFunc_));
    }
}

void InputEventHub::CreateAccessibilityHoverEventActuator()
{
    CHECK_NULL_VOID(userAccessibilityHoverFunc_);
    if (!accessibilityHoverEventActuator_) {
        accessibilityHoverEventActuator_ = MakeRefPtr<InputEventActuator>(WeakClaim(this));
    }
    if (userAccessibilityHoverFunc_) {
        accessibilityHoverEventActuator_->ReplaceInputEvent(std::move(userAccessibilityHoverFunc_));
    }
}
} // namespace OHOS::Ace::NG