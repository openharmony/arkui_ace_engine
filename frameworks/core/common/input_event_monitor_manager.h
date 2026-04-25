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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_EVENT_MONITOR_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_EVENT_MONITOR_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <variant>

#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace {
enum class InputEventSubTypeMask : uint32_t {
    NONE = 0,
    LEFT_MOUSE_DOWN = 1u << 0,
    LEFT_MOUSE_UP = 1u << 1,
    RIGHT_MOUSE_DOWN = 1u << 2,
    RIGHT_MOUSE_UP = 1u << 3,
    MIDDLE_MOUSE_DOWN = 1u << 4,
    MIDDLE_MOUSE_UP = 1u << 5,
    LEFT_MOUSE_DRAGGING = 1u << 6,
    RIGHT_MOUSE_DRAGGING = 1u << 7,
    MIDDLE_MOUSE_DRAGGING = 1u << 8,
    TOUCH_DOWN = 1u << 9,
    TOUCH_UP = 1u << 10,
    KEY_DOWN = 1u << 11,
    KEY_UP = 1u << 12,
};

enum class InputEventInterceptAction : int32_t {
    CONTINUE = 0,
    BLOCK = 1,
};

class RawInputEventWrapper {
public:
    using EventVariant = std::variant<MouseEvent, TouchEvent, KeyEvent>;

    explicit RawInputEventWrapper(const MouseEvent& event) : event_(event) {}
    explicit RawInputEventWrapper(const TouchEvent& event) : event_(event) {}
    explicit RawInputEventWrapper(const KeyEvent& event) : event_(event) {}

    bool IsMouseEvent() const
    {
        return std::holds_alternative<MouseEvent>(event_);
    }

    bool IsTouchEvent() const
    {
        return std::holds_alternative<TouchEvent>(event_);
    }

    bool IsKeyEvent() const
    {
        return std::holds_alternative<KeyEvent>(event_);
    }

    const MouseEvent* GetMouseEvent() const
    {
        return std::get_if<MouseEvent>(&event_);
    }

    const TouchEvent* GetTouchEvent() const
    {
        return std::get_if<TouchEvent>(&event_);
    }

    const KeyEvent* GetKeyEvent() const
    {
        return std::get_if<KeyEvent>(&event_);
    }

private:
    EventVariant event_;
};

using InputEventListenerCallback = std::function<InputEventInterceptAction(const RawInputEventWrapper&)>;

class MonitorIdentity : public AceType {
    DECLARE_ACE_TYPE(MonitorIdentity, AceType);

public:
    MonitorIdentity() = default;
    ~MonitorIdentity() override = default;
};

struct MonitorInfo {
    RefPtr<MonitorIdentity> identity;
    InputEventListenerCallback handler;
    uint32_t eventMask = 0;
};

class InputEventMonitorHolder : public AceType {
    DECLARE_ACE_TYPE(InputEventMonitorHolder, AceType);

public:
    explicit InputEventMonitorHolder(RefPtr<MonitorIdentity> monitorIdentity)
        : monitorIdentity_(std::move(monitorIdentity))
    {}

    ~InputEventMonitorHolder() override = default;

    const RefPtr<MonitorIdentity>& GetIdentity() const
    {
        return monitorIdentity_;
    }

private:
    RefPtr<MonitorIdentity> monitorIdentity_;
};

enum class InteractionState {
    DOWN_DELIVERED,
    DOWN_BLOCKED,
};

class InteractionTracker {
public:
    void OnDownEvent(uint64_t interactionKey);
    void OnDownEventBlocked(uint64_t interactionKey);
    bool IsDownEventDelivered(uint64_t interactionKey) const;
    bool IsDownEventBlocked(uint64_t interactionKey) const;
    void EndInteraction(uint64_t interactionKey);

private:
    std::unordered_map<uint64_t, InteractionState> activeInteractions_;
};

class InputEventMonitorManager : public AceType {
    DECLARE_ACE_TYPE(InputEventMonitorManager, AceType);

public:
    InputEventMonitorManager() = default;
    ~InputEventMonitorManager() override = default;

    RefPtr<MonitorIdentity> AddLocalInputMonitor(uint32_t eventMask, InputEventListenerCallback handler);
    void RemoveLocalInputMonitor(const RefPtr<MonitorIdentity>& identity);

    bool ProcessMouseEvent(MouseEvent& event);
    bool ProcessTouchEvent(TouchEvent& event);
    bool ProcessKeyEvent(KeyEvent& event);

private:
    static constexpr uint32_t INPUT_EVENT_MASK_SET =
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_UP) |
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_UP) |
        static_cast<uint32_t>(InputEventSubTypeMask::MIDDLE_MOUSE_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::MIDDLE_MOUSE_UP) |
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DRAGGING) |
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_DRAGGING) |
        static_cast<uint32_t>(InputEventSubTypeMask::MIDDLE_MOUSE_DRAGGING) |
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_UP) |
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP);

    static InputEventSubTypeMask GetSubTypeMask(const MouseEvent& event);
    static InputEventSubTypeMask GetSubTypeMask(const TouchEvent& event);
    static InputEventSubTypeMask GetSubTypeMask(const KeyEvent& event);

    static uint64_t GetMouseInteractionId(const MouseEvent& event);
    static uint64_t GetTouchInteractionId(const TouchEvent& event);
    static uint64_t GetKeyInteractionId(const KeyEvent& event);

    static bool IsValidEventMask(uint32_t eventMask);
    InputEventInterceptAction RunMonitorChain(
        InputEventSubTypeMask event, const RawInputEventWrapper& wrapper) const;

    std::vector<MonitorInfo> monitors_;
    InteractionTracker mouseTracker_;
    InteractionTracker touchTracker_;
    InteractionTracker keyTracker_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_EVENT_MONITOR_MANAGER_H
