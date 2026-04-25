/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/input_event_monitor_manager.h"

namespace OHOS::Ace {
void InteractionTracker::OnDownEvent(uint64_t interactionKey)
{
    activeInteractions_[interactionKey] = InteractionState::DOWN_DELIVERED;
}

void InteractionTracker::OnDownEventBlocked(uint64_t interactionKey)
{
    activeInteractions_[interactionKey] = InteractionState::DOWN_BLOCKED;
}

bool InteractionTracker::IsDownEventDelivered(uint64_t interactionKey) const
{
    auto it = activeInteractions_.find(interactionKey);
    return it != activeInteractions_.end() && it->second == InteractionState::DOWN_DELIVERED;
}

bool InteractionTracker::IsDownEventBlocked(uint64_t interactionKey) const
{
    auto it = activeInteractions_.find(interactionKey);
    return it != activeInteractions_.end() && it->second == InteractionState::DOWN_BLOCKED;
}

void InteractionTracker::EndInteraction(uint64_t interactionKey)
{
    activeInteractions_.erase(interactionKey);
}

RefPtr<MonitorIdentity> InputEventMonitorManager::AddLocalInputMonitor(
    uint32_t eventMask, InputEventListenerCallback handler)
{
    if (!IsValidEventMask(eventMask) || !handler) {
        return nullptr;
    }
    auto identity = AceType::MakeRefPtr<MonitorIdentity>();
    monitors_.emplace_back(MonitorInfo { identity, std::move(handler), eventMask });
    return identity;
}

void InputEventMonitorManager::RemoveLocalInputMonitor(const RefPtr<MonitorIdentity>& identity)
{
    CHECK_NULL_VOID(identity);
    monitors_.erase(std::remove_if(monitors_.begin(), monitors_.end(),
        [&identity](const MonitorInfo& info) { return info.identity == identity; }), monitors_.end());
}

bool InputEventMonitorManager::ProcessMouseEvent(MouseEvent& event)
{
    CHECK_EQUAL_RETURN(monitors_.empty(), true, false);
    auto interactionKey = GetMouseInteractionId(event);
    if (event.action == MouseAction::PRESS) {
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            mouseTracker_.OnDownEventBlocked(interactionKey);
            return true;
        }
        mouseTracker_.OnDownEvent(interactionKey);
        return false;
    }
    if (event.action == MouseAction::MOVE) {
        if (mouseTracker_.IsDownEventBlocked(interactionKey)) {
            return true;
        }
        auto subTypeMask = GetSubTypeMask(event);
        if (subTypeMask == InputEventSubTypeMask::NONE) {
            return false;
        }
        RawInputEventWrapper wrapper(event);
        return RunMonitorChain(subTypeMask, wrapper) == InputEventInterceptAction::BLOCK;
    }
    if (event.action == MouseAction::RELEASE) {
        if (mouseTracker_.IsDownEventBlocked(interactionKey)) {
            mouseTracker_.EndInteraction(interactionKey);
            return true;
        }
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            if (mouseTracker_.IsDownEventDelivered(interactionKey)) {
                event.action = MouseAction::CANCEL;
                event.isFalsifyCancel = true;
            }
            mouseTracker_.EndInteraction(interactionKey);
            return true;
        }
        mouseTracker_.EndInteraction(interactionKey);
        return false;
    }
    if (event.action == MouseAction::CANCEL || event.action == MouseAction::WINDOW_LEAVE) {
        mouseTracker_.EndInteraction(interactionKey);
    }
    return false;
}

bool InputEventMonitorManager::ProcessTouchEvent(TouchEvent& event)
{
    CHECK_EQUAL_RETURN(monitors_.empty(), true, false);
    auto interactionKey = GetTouchInteractionId(event);
    if (event.type == TouchType::DOWN) {
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            touchTracker_.OnDownEventBlocked(interactionKey);
            return true;
        }
        touchTracker_.OnDownEvent(interactionKey);
        return false;
    }
    if (event.type == TouchType::MOVE) {
        return touchTracker_.IsDownEventBlocked(interactionKey);
    }
    if (event.type == TouchType::UP) {
        if (touchTracker_.IsDownEventBlocked(interactionKey)) {
            touchTracker_.EndInteraction(interactionKey);
            return true;
        }
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            if (touchTracker_.IsDownEventDelivered(interactionKey)) {
                event.type = TouchType::CANCEL;
                event.isFalsified = true;
            }
            touchTracker_.EndInteraction(interactionKey);
            return true;
        }
        touchTracker_.EndInteraction(interactionKey);
        return false;
    }
    if (event.type == TouchType::CANCEL) {
        touchTracker_.EndInteraction(interactionKey);
    }
    return false;
}

bool InputEventMonitorManager::ProcessKeyEvent(KeyEvent& event)
{
    CHECK_EQUAL_RETURN(monitors_.empty(), true, false);
    auto interactionKey = GetKeyInteractionId(event);
    if (event.action == KeyAction::DOWN) {
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            keyTracker_.OnDownEventBlocked(interactionKey);
            return true;
        }
        keyTracker_.OnDownEvent(interactionKey);
        return false;
    }
    if (event.action == KeyAction::UP) {
        if (keyTracker_.IsDownEventBlocked(interactionKey)) {
            keyTracker_.EndInteraction(interactionKey);
            return true;
        }
        RawInputEventWrapper wrapper(event);
        if (RunMonitorChain(GetSubTypeMask(event), wrapper) == InputEventInterceptAction::BLOCK) {
            if (keyTracker_.IsDownEventDelivered(interactionKey)) {
                event.action = KeyAction::CANCEL;
                event.isPreIme = false;
                event.isFalsifyCancel = true;
            }
            keyTracker_.EndInteraction(interactionKey);
            return true;
        }
        keyTracker_.EndInteraction(interactionKey);
        return false;
    }
    if (event.action == KeyAction::CANCEL) {
        keyTracker_.EndInteraction(interactionKey);
    }
    return false;
}

InputEventSubTypeMask InputEventMonitorManager::GetSubTypeMask(const MouseEvent& event)
{
    switch (event.action) {
        case MouseAction::PRESS:
            switch (event.button) {
                case MouseButton::LEFT_BUTTON:
                    return InputEventSubTypeMask::LEFT_MOUSE_DOWN;
                case MouseButton::RIGHT_BUTTON:
                    return InputEventSubTypeMask::RIGHT_MOUSE_DOWN;
                case MouseButton::MIDDLE_BUTTON:
                    return InputEventSubTypeMask::MIDDLE_MOUSE_DOWN;
                default:
                    return InputEventSubTypeMask::NONE;
            }
        case MouseAction::RELEASE:
            switch (event.button) {
                case MouseButton::LEFT_BUTTON:
                    return InputEventSubTypeMask::LEFT_MOUSE_UP;
                case MouseButton::RIGHT_BUTTON:
                    return InputEventSubTypeMask::RIGHT_MOUSE_UP;
                case MouseButton::MIDDLE_BUTTON:
                    return InputEventSubTypeMask::MIDDLE_MOUSE_UP;
                default:
                    return InputEventSubTypeMask::NONE;
            }
        case MouseAction::MOVE: {
            switch (event.button) {
                case MouseButton::LEFT_BUTTON:
                    return InputEventSubTypeMask::LEFT_MOUSE_DRAGGING;
                case MouseButton::RIGHT_BUTTON:
                    return InputEventSubTypeMask::RIGHT_MOUSE_DRAGGING;
                case MouseButton::MIDDLE_BUTTON:
                    return InputEventSubTypeMask::MIDDLE_MOUSE_DRAGGING;
                default:
                    return InputEventSubTypeMask::NONE;
            }
        }
        default:
            return InputEventSubTypeMask::NONE;
    }
}

InputEventSubTypeMask InputEventMonitorManager::GetSubTypeMask(const TouchEvent& event)
{
    switch (event.type) {
        case TouchType::DOWN:
            return InputEventSubTypeMask::TOUCH_DOWN;
        case TouchType::UP:
            return InputEventSubTypeMask::TOUCH_UP;
        default:
            return InputEventSubTypeMask::NONE;
    }
}

InputEventSubTypeMask InputEventMonitorManager::GetSubTypeMask(const KeyEvent& event)
{
    switch (event.action) {
        case KeyAction::DOWN:
            return InputEventSubTypeMask::KEY_DOWN;
        case KeyAction::UP:
            return InputEventSubTypeMask::KEY_UP;
        default:
            return InputEventSubTypeMask::NONE;
    }
}

uint64_t InputEventMonitorManager::GetMouseInteractionId(const MouseEvent& event)
{
    auto idLowBits = static_cast<uint64_t>(event.deviceId);
    auto idHighBits = static_cast<uint64_t>(static_cast<uint32_t>(event.button)) << 32;
    return idLowBits ^ idHighBits;
}

uint64_t InputEventMonitorManager::GetTouchInteractionId(const TouchEvent& event)
{
    auto idLowBits = static_cast<uint64_t>(event.deviceId);
    auto idHighBits = static_cast<uint64_t>(static_cast<uint32_t>(event.id)) << 32;
    return idLowBits ^ idHighBits;
}

uint64_t InputEventMonitorManager::GetKeyInteractionId(const KeyEvent& event)
{
    auto idLowBits = static_cast<uint64_t>(event.deviceId);
    auto idHighBits = static_cast<uint64_t>(static_cast<uint32_t>(event.code)) << 32;
    return idLowBits ^ idHighBits;
}

bool InputEventMonitorManager::IsValidEventMask(uint32_t eventMask)
{
    return eventMask != static_cast<uint32_t>(InputEventSubTypeMask::NONE) && (eventMask & ~INPUT_EVENT_MASK_SET) == 0;
}

InputEventInterceptAction InputEventMonitorManager::RunMonitorChain(
    InputEventSubTypeMask event, const RawInputEventWrapper& wrapper) const
{
    auto eventMask = static_cast<uint32_t>(event);
    if (!IsValidEventMask(eventMask)) {
        return InputEventInterceptAction::CONTINUE;
    }
    auto monitorChain = monitors_;
    for (const auto& info : monitorChain) {
        if ((info.eventMask & eventMask) == 0) {
            continue;
        }
        if (info.handler(wrapper) == InputEventInterceptAction::BLOCK) {
            return InputEventInterceptAction::BLOCK;
        }
    }
    return InputEventInterceptAction::CONTINUE;
}
} // namespace OHOS::Ace
