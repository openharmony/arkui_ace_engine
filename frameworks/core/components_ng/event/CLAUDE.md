# Event Subdirectory Rules

This document contains specialized rules for the `components_ng/event` directory and **must inherit and comply with** the repository root `CLAUDE.md`.
This document only describes constraints and knowledge specific to this directory.

Scope: `frameworks/core/components_ng/event/`

## Overview

The Event directory hosts the NG event infrastructure for FrameNode-based components: gesture dispatch, focus handling, input event routing, and UI state styles handling.
It provides reusable hubs and actuators that connect frontend callbacks to core gesture and focus pipelines.
Changes here affect many components indirectly; treat APIs and enums as cross-cutting contracts.

## Directory Structure

```
frameworks/core/components_ng/event/
├── BUILD.gn
├── event_hub.h/cpp
├── gesture_event_hub.h/cpp
├── gesture_event_hub_drag.cpp
├── input_event_hub.h/cpp
├── event_constants.h
├── visible_ratio_callback.h
├── focus_hub.h/cpp
├── focus_event_handler.h/cpp
├── focus_box.h/cpp
├── focus_state.h
├── focus_type.h
├── state_style_manager.h/cpp
├── response_ctrl.h/cpp
├── target_component.h/cpp
├── click_event.h/cpp
├── pan_event.h/cpp
├── long_press_event.h/cpp
├── scrollable_event.h/cpp
├── touch_event.h/cpp
├── drag_event.h/cpp
├── drag_drop_event.h/cpp
├── input_event.h/cpp
├── overflow_scroll_event_hub.h
└── error_reporter/
    ├── general_interaction_error_reporter.h/cpp
```

## Responsibility Boundaries

### Core Responsibilities

- **EventHub** (`event_hub.h/.cpp`)
  - Owns and lazily creates `GestureEventHub`, `InputEventHub`, and `FocusHub` (`GetOrCreate*` APIs).
  - Attaches to a `FrameNode` via `AttachHost` and keeps the weak host reference.
  - Exposes common callbacks: `SetOnAppear`, `SetOnDisappear`, `SetOnAreaChanged`, `SetOnSizeChanged`.
  - Manages drag-and-drop callbacks through `DragDropCallbackSet` and visible-area callbacks via `VisibleAreaChangeCallbackSet`.

- **GestureEventHub** (`gesture_event_hub.h/.cpp`, `gesture_event_hub_drag.cpp`)
  - Registers gestures and gesture recognizers: `AddGesture`, `AttachGesture`, `RemoveGesture`, `RemoveGesturesByTag`.
  - Hosts actuator-based events (click, pan, long-press, scrollable, touch, drag).
  - Coordinates touch tests and response regions for gesture dispatch.
  - Owns drag-drop preparation and preview flow (menu/preview helpers in `gesture_event_hub_drag.cpp`).

- **InputEventHub** (`input_event_hub.h/.cpp`)
  - Routes mouse/hover/hover-move/accessibility-hover via `InputEventActuator`.
  - Stores hover effect configuration and JS FrameNode callbacks.
  - Tracks touchpad interaction listeners.

- **FocusHub / FocusEventHandler** (`focus_hub.h/.cpp`, `focus_event_handler.h/.cpp`)
  - Maintains focus state, navigation, and focus paint parameters (`FocusPaintParam`).
  - Handles focus/blur callbacks and key/crown/focus-axis events.
  - Owns default focus and tab index metadata through `FocusCallbackEvents`.

- **StateStyleManager** (`state_style_manager.h/.cpp`)
  - Manages UI state bits (`UI_STATE_*`) and notifies state style subscribers.
  - Drives pressed state transitions and press-style tasks.

- **ResponseCtrl** (`response_ctrl.h/.cpp`)
  - Implements monopolize-response gating via `ShouldResponse`, `TrySetFirstResponse`, and `Reset`.

- **TargetComponent** (`target_component.h/.cpp`)
  - Stores gesture judge callbacks and gesture-recognizer context for a `UINode`.

### What Not to Do
 - **Do not instantiate hubs directly**; always go through `EventHub::GetOrCreate*` to preserve lazy ownership.
 - **Do not bypass actuator APIs** by calling recognizers directly from component code.
 - **Do not move event enums or bit flags** out of `event_constants.h` or `state_style_manager.h`.
 - **Do not add heavy logic inside callbacks** that run in hot event paths.
 - **Do not print any coordinates or location information** in logs.

## Architectural Layer Relationships

```
FrameNode
  └─ EventHub
      ├─ GestureEventHub
      │   ├─ ClickEventActuator / PanEventActuator / LongPressEventActuator
      │   ├─ ScrollableActuator / TouchEventActuator
      │   └─ DragEventActuator / DragDropEventActuator
      ├─ InputEventHub
      │   └─ InputEventActuator (mouse/hover/accessibility hover)
      └─ FocusHub (FocusEventHandler + FocusState)
```

**Key relationships**
- `EventHub` owns sub-hubs and mediates host attachment (`AttachHost`).
- Actuators implement `GestureEventActuator::OnCollectTouchTarget` to participate in touch testing.
- Focus handling uses `FocusCallbackEvents` to store user/JS callbacks and focus metadata.

## Event Flow (High Level)

1. Input arrives (touch/mouse/key/crown) through the pipeline.
2. EventHub delegates to the appropriate hub (gesture/input/focus).
3. Actuators collect touch targets and feed recognizers.
4. Recognizers resolve and invoke `GestureEventFunc`/`OnKeyEventFunc` callbacks.

## Behaviors That Must Not Change

### 1. Lazy Hub Creation

`EventHub::GetOrCreateGestureEventHub`, `GetOrCreateInputEventHub`, and `GetOrCreateFocusHub` must remain lazy.
This guarantees a stable ownership model and avoids allocating hubs for nodes that never receive events.

### 2. UI State Bit Definitions

`UI_STATE_*` values in `state_style_manager.h` are part of public behavior:
- `UI_STATE_NORMAL = 0`
- `UI_STATE_PRESSED = 1`
- `UI_STATE_FOCUSED = 1 << 1`
- `UI_STATE_DISABLED = 1 << 2`
- `UI_STATE_SELECTED = 1 << 3`
- `UI_STATE_UNKNOWN = 1 << 9`

### 3. Focus Callback Storage

`FocusCallbackEvents` must remain the storage point for focus/blur/key/crown callbacks.
Do not scatter focus callbacks into unrelated classes.

### 4. Event Constants Scope

Enums in `event_constants.h` (e.g., `HitTestMode`, `TouchTestStrategy`, `GestureCallbackType`) are shared with
hit-testing and gesture resolution code. Keep names and numeric ordering stable when possible.

### 5. Response Control Semantics

`ResponseCtrl` must continue to gate monopolized response based on the first responder.
Changing `MonopolizeState` flow alters input routing across siblings.

## Common Pitfalls

- Using `SetOnTouchEvent` on the wrong hub: touch events belong to `GestureEventHub`, not `InputEventHub`.
- Forgetting to call `GetOrCreate*` before registering events, leaving callbacks unbound.
- Overwriting JS FrameNode callbacks when the user callback is intended (`SetFrameNodeCommonOn*` vs `Set*`).
- Modifying `event_constants.h` enums without updating all dependent code paths.

## Debugging Methods

### 1. Logging Macros

Search for `AceLogTag::ACE_FOCUS`, `AceLogTag::ACE_DRAG`, and `AceLogTag::ACE_STATE_STYLE` in this directory.
Use `TAG_LOGD/LOGI/LOGW` consistently to match existing focus and drag logs.

### 2. Tracing

`ACE_SCOPED_TRACE`, `ACE_EVENT_SCOPED_TRACE`, and `ACE_BENCH_MARK_TRACE` appear in focus and drag flows.
Add traces around new hot paths to diagnose ordering and latency.

### 3. Key Data Structure Checks

- Verify `EventHub` has a valid host via `GetFrameNode()` before dereferencing.
- Validate `FocusCallbackEvents` for null before invoking callbacks.
- Guard drag preview helpers in `gesture_event_hub_drag.cpp` with null checks (pattern already uses `CHECK_NULL_*`).

### 4. Common Problem Localization

- Drag preview and menu issues: `gesture_event_hub_drag.cpp`.
- Focus navigation failures: `focus_hub.cpp` and `focus_event_handler.cpp`.
- Pressed style glitches: `state_style_manager.cpp`.

## Special Feature Constraints

- Drag-and-drop uses `DragDropInfo`, `DragDropCallbackSet`, and preview helpers; do not bypass the hub.
- Focus box styling is centralized in `FocusBox` and `FocusPaintParam`; avoid ad-hoc drawing.
- Visible-area callbacks are tracked through `VisibleAreaChangeCallbackSet` and `VisibleAreaChangeConfig`.

## Performance Constraints

- Avoid allocations in hot callbacks (`OnTouch`, `OnMouse`, `OnKey`); reuse objects when possible.
- Keep gesture and focus callbacks lightweight to prevent frame jank.
- Do not add heavy JSON serialization in event paths; keep it in debug-only utilities.

## Backward Compatibility

- Preserve public callback semantics for `EventHub` and `GestureEventHub` APIs.
- Append new enum values instead of reordering existing ones.
- Keep `FocusType`/`FocusStyleType` values stable to avoid breaking JS behavior.

## Summary

The `components_ng/event` directory is the shared event backbone for NG components.
Follow the hub + actuator pattern, keep enums and callbacks stable, and use existing logging/tracing conventions.
When in doubt, inspect the relevant hub or actuator header before changing behavior.
