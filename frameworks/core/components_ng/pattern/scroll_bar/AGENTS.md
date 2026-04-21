# ScrollBar Pattern Component Knowledge

This document provides specific guidance for the ScrollBar pattern component within the ACE Engine NG architecture.

## Overview

The ScrollBar pattern is a **controller component** that provides visual scrolling indicators for scrollable containers (List, Grid, Scroll, etc.). It is NOT a standalone component but rather an auxiliary UI element that operates through a proxy-based communication pattern.

## Responsibility Boundaries

### What ScrollBarPattern Does

1. **Scroll Position Visualization**
   - Displays current scroll position within the viewport
   - Shows proportion of visible content to total content
   - Provides visual feedback for scrollable vs non-scrollable states

2. **User Interaction Handling**
   - Direct scrollbar dragging (PanGesture)
   - Track click-to-scroll (ClickGesture)
   - Long-press continuous scrolling (LongPressGesture)
   - Mouse hover and wheel events

3. **Display Mode Management**
   - `DisplayMode::AUTO` - Shows during scroll, auto-hides after delay
   - `DisplayMode::ON` - Always visible
   - `DisplayMode::OFF` - Never visible

4. **Proxy Communication**
   - Bidirectional communication with ScrollablePattern via ScrollBarProxy
   - Notifies scrollable node of scrollbar-driven position changes
   - Receives notifications from scrollable node to update visual state

### What ScrollBarPattern Does NOT Do

- **NOT** responsible for actual content scrolling (handled by ScrollablePattern)
- **NOT** a standalone interactive component (must be attached to a scrollable parent)
- **NOT** responsible for touch event hit testing outside its region (delegates to ScrollablePattern)
- **NOT** managing scroll physics or edge effects (handled by ScrollablePattern with overScroll)

## Architecture Relationships

```
┌─────────────────────────────────────────────────────────────┐
│  Scrollable Components (List/Grid/Scroll)                  │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  ScrollablePattern                                   │   │
│  │    - Manages scroll position & physics               │   │
│  │    - Handles content layout & viewport               │   │
│  └──────────────────┬──────────────────────────────────┘   │
│                     │                                       │
│                     │ RegisterScrollableNode()              │
│                     ↓                                       │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  ScrollBarProxy (Communication Bridge)              │   │
│  │    - Mediates between Scrollable & ScrollBar        │   │
│  │    - Manages 1:N scrollable-to-scrollbar mapping    │   │
│  └──────────────────┬──────────────────────────────────┘   │
│                     │ RegisterScrollBar()                  │
│                     ↓                                       │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  ScrollBarPattern (This Component)                  │   │
│  │    - Visual rendering of scrollbar indicator        │   │
│  │    - Handles drag/click/long-press interactions     │   │
│  │    - Manages show/hide animations                   │   │
│  └──────────────────┬──────────────────────────────────┘   │
│                     │                                       │
│                     ↓                                       │
│  ┌─────────────────────────────────────────────────────┐   │
│  │  Inner ScrollBar (scroll/inner/scroll_bar.h)       │   │
│  │    - Actual rendering logic & geometry calculation  │   │
│  │    - Gesture recognizers & input handling           │   │
│  │    - Animation & visual effects                     │   │
│  └─────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

### Component Structure

```
scroll_bar/
├── scroll_bar_pattern.{h,cpp}              # Main pattern class
├── scroll_bar_layout_algorithm.{h,cpp}     # Layout measurement
├── scroll_bar_layout_property.h             # Layout properties (Axis, DisplayMode)
├── scroll_bar_paint_property.h              # Paint properties (colors, styles)
├── scroll_bar_paint_method.{h,cpp}          # Render pipeline integration
├── scroll_bar_model_ng.{h,cpp}              # Frontend API interface
├── scroll_bar_accessibility_property.{h,cpp} # Accessibility properties and methods
└── proxy/
    ├── scroll_bar_proxy.{h,cpp}            # Communication bridge
    └── scroll_proxy.h                      # Base proxy interface
```

## Layer Interactions

### Pattern ↔ LayoutAlgorithm

- **ScrollBarLayoutAlgorithm** ([scroll_bar_layout_algorithm.h](scroll_bar_layout_algorithm.h:28))
  - Measures scrollbar size based on constraints and theme
  - Calculates `scrollableDistance_` from viewport/content size difference
  - Positions child (scrollable content) within scrollbar container

- **Key Data Flow:**
  ```cpp
  // In Layout():
  scrollableDistance_ = GetMainAxisSize(size, axis) - GetMainAxisSize(childSize, axis);
  currentOffset_ = scrollableNodeOffset * scrollableDistance_ / controlDistance;
  ```

### Pattern ↔ Model

- **ScrollBarModelNG** ([scroll_bar_model_ng.h](scroll_bar_model_ng.h:23))
  - Frontend (ArkTS) interface for scrollbar configuration
  - Static methods for property updates on existing FrameNodes
  - Delegates to ScrollBarProxy for nested scroll configuration

### Pattern ↔ ScrollBar (Inner Class)

- **ScrollBar** ([scroll/inner/scroll_bar.h](../scroll/inner/scroll_bar.h:58))
  - Separate class handling actual rendering and input
  - Created/managed by ScrollBarPattern
  - Communicates via callbacks registered in `RegisterScrollBarEventTask()`

## Critical Behaviors - Must Not Change

### Public API Contract

1. **Scroll Position Callback Signature**
   ```cpp
   // Defined in scroll_bar_pattern.cpp:340
   ScrollBarPositionCallback = bool(double offset, int32_t source, bool isMouseWheelScroll)
   ```
   - **DO NOT** change parameter types or order
   - **DO NOT** change return type (bool indicates if scroll was consumed)
   - `source` values: `SCROLL_FROM_BAR`, `SCROLL_FROM_START`, `SCROLL_FROM_BAR_FLING`, `SCROLL_FROM_BAR_OVER_DRAG`

2. **DisplayMode Semantics**
   - `AUTO`: Must hide after `BAR_DISAPPEAR_DELAY_DURATION` (2000ms) of inactivity
   - `ON`: Must always remain visible
   - `OFF`: Must never render or respond to input
   - **DO NOT** add new display modes without API review

3. **Axis Direction Enum Values**
   - `Axis::VERTICAL`, `Axis::HORIZONTAL`, `Axis::FREE`, `Axis::NONE`
   - **DO NOT** renumber enum values (affects serialized state)

### Event Ordering Guarantees

The scroll event sequence MUST be maintained:

```
1. User starts drag → HandleDragStart() → ScrollPositionCallback(SCROLL_FROM_START)
   - Sets isScrolling_ = true
   - Stops disappear animator
   - Notifies proxy of scroll start

2. Drag continues → HandleDragUpdate() → ScrollPositionCallback(offset, SCROLL_FROM_BAR)
   - Updates currentOffset_
   - Notifies scrollable node via proxy

3. User releases → HandleDragEnd() → [optional fling] → scrollEndCallback_()
   - Handles friction motion if velocity > 0
   - Sets isScrolling_ = false
   - Starts disappear animator if AUTO mode
```

**DO NOT** change this event ordering - dependent components rely on it.

### Lifecycle Constraints

1. **OnModifyDone()** ([scroll_bar_pattern.cpp:51](scroll_bar_pattern.cpp:51))
   - Called after property updates
   - Must initialize scrollable event and pan recognizer
   - Must configure accessibility
   - **DO NOT** skip calling `Pattern::OnModifyDone()`

2. **OnDirtyLayoutWrapperSwap()** ([scroll_bar_pattern.cpp:439](scroll_bar_pattern.cpp:439))
   - Must return `true` if display state changed
   - Must update `scrollableDistance_` from layout algorithm
   - **DO NOT** mark nodes dirty within this callback (layout phase)

3. **Destructor** ([scroll_bar_pattern.h:42](scroll_bar_pattern.h:42))
   - Must call `scrollBarProxy_->UnRegisterScrollBar()`
   - **DO NOT** leak proxy registrations

## Common Pitfalls

### 1. hasChild_ State Synchronization

**Problem**: `hasChild_` indicates whether ScrollBar has a child FrameNode. In API 12+, inner ScrollBar mode uses `!hasChild_`.

```cpp
// scroll_bar_pattern.cpp:445
bool updateFlag = false;
if (UseInnerScrollBar()) {
    updateFlag = true;
} else {
    // Legacy path: get scrollableDistance from LayoutAlgorithm
    auto layoutAlgorithm = DynamicCast<ScrollBarLayoutAlgorithm>(...);
    scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
}
```

**Rule**:
- Always check `UseInnerScrollBar()` before accessing `scrollBar_` methods
- When `hasChild_` is true, use `childRect_` for hit testing
- When `hasChild_` is false, use `scrollBar_->InBarTouchRegion()` or `InBarHoverRegion()`

### 2. ScrollBarProxy Registration

**Problem**: Forgetting to unregister leads to use-after-free crashes.

```cpp
// CORRECT - In destructor
ScrollBarPattern::~ScrollBarPattern()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterScrollBar(AceType::WeakClaim(this));
    }
}
```

**Rule**:
- Always unregister in destructor
- Always use `WeakClaim(this)` when registering callbacks
- Check `scrollBarProxy_` null before dereferencing

### 3. DisplayMode Animation Conflicts

**Problem**: Multiple disappear animations can conflict.

```cpp
// scroll_bar_pattern.cpp:678
if (disapplearDelayTask_) {
    disapplearDelayTask_.Cancel();  // Always cancel before scheduling new task
}
```

**Rule**:
- Always cancel existing delay task before scheduling new one
- Use `StopDisappearAnimator()` before `StartDisappearAnimator()`
- Check `controlDistanceChanged_` flag to avoid redundant animations

### 4. controlDistance_ vs scrollableDistance_

**Problem**: Confusing these two distance values.

- **`controlDistance_`**: Total scrollable distance of the scrollable node (passed via proxy)
- **`scrollableDistance_`**: Distance within the scrollbar container (layout calculation)

```cpp
// Converting between them:
currentOffset_ = scrollableNodeOffset * scrollableDistance_ / controlDistance;
```

**Rule**:
- `controlDistance_` is set by ScrollablePattern via proxy
- `scrollableDistance_` is calculated in LayoutAlgorithm
- Never use them interchangeably

### 5. OverScroll Edge Cases

**Problem**: OverScroll behavior depends on multiple conditions.

```cpp
// scroll_bar_pattern.cpp:837
bool canOverScroll = isTouchScreen_ && CanOverScrollWithDelta(offset);
int source = isTouchScreen_ && canOverScroll ? SCROLL_FROM_BAR_OVER_DRAG : SCROLL_FROM_BAR;
```

**Rule**:
- Check `isTouchScreen_` flag before allowing over-scroll
- Always query proxy with `CanOverScrollWithDelta()` first
- Use correct `source` parameter based on over-scroll state

## Debugging

### Log Tag

Use `AceLogTag::ACE_SCROLL_BAR` for scrollbar-specific logging:

```cpp
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "outer scrollBar drag start");
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "outer scrollBar drag end, velocity is %{public}f", velocity);
```

### Important State Variables

| Variable | Purpose | Key Checkpoints |
|----------|---------|-----------------|
| `currentOffset_` | Current scroll position | Updated in `UpdateCurrentOffset()` |
| `scrollableDistance_` | Max scroll distance | Set in `OnDirtyLayoutWrapperSwap()` |
| `controlDistance_` | Scrollable node's distance | Set via proxy `NotifyScrollBar()` |
| `displayMode_` | Visibility mode | Checked in `StartDisappearAnimator()` |
| `hasChild_` | Child node presence | Determines `UseInnerScrollBar()` |
| `isScrolling_` | Scroll in progress | Set on drag start, cleared on end |
| `childRect_` | Child frame geometry | Used for hit testing when `hasChild_` true |

### Common Issues & Diagnostics

**Symptom**: Scrollbar not visible when content is scrollable
- Check `displayMode_` is not `OFF`
- Check `controlDistance_ > 0` (set via proxy)
- Check `IsScrollable()` returns true on inner ScrollBar
- Check opacity is not 0

**Symptom**: Scrollbar not responding to drag
- Check pan recognizer is initialized in `OnModifyDone()`
- Check `InBarRegionCallback()` returns true for touch points
- Check `scrollableEvent_` is added to gesture hub
- Check axis direction matches pan recognizer direction

**Symptom**: Crash after removing scrollable component
- Check destructor unregisters from proxy
- Check callbacks use `WeakClaim(this)`
- Check no dangling `scrollBarProxy_` references

## Version-Specific Behavior

### API 12+ (PlatformVersion::VERSION_TWELVE)

1. **Inner ScrollBar Mode**
   ```cpp
   bool UseInnerScrollBar() const {
       return !hasChild_ && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE);
   }
   ```
   - Uses separate `ScrollBar` class for rendering
   - Direct input handling without child FrameNode
   - Different hit testing logic

2. **PositionMode Logic**
   - Automatically determines LEFT vs RIGHT based on `TextDirection::RTL`
   - See `GetPositionMode()` in [scroll_bar_pattern.cpp:270](scroll_bar_pattern.cpp:270)

3. **Animation Curves**
   - Inner scrollbar uses `Curves::SHARP` for disappear animation
   - Legacy scrollbar uses `Curves::FRICTION`
   - Frame rate range: [0, 90] fps, expected 15 fps

### Legacy (pre-API 12)

- Always has child FrameNode
- Hit testing uses `childRect_`
- `scrollableDistance_` from LayoutAlgorithm

## Framework Code Rules

This is framework core code - additional constraints apply:

1. **No Business Logic**: Do not add application-specific behavior
2. **No Feature Flags**: Use `ace_config.gni` for conditional features, not inline checks
3. **Performance Critical**: Scrollbar runs on every scroll frame - avoid expensive operations
4. **Thread Safety**: All methods run on UI thread - no synchronization needed
5. **Backward Compatibility**: Preserve legacy code paths for API < 12

## Related Components

- **ScrollablePattern**: Base pattern for scrollable containers
- **ListPattern**: Specific scrollable implementation
- **GridPattern**: Specific scrollable implementation
- **ScrollPattern**: Generic scroll component
- **ScrollBarOverlayModifier**: Visual rendering for inner scrollbar
- **FrictionMotion**: Fling animation physics

## References

- Root CLAUDE.md: `../../../CLAUDE.md`
- ScrollBar proxy: [proxy/scroll_bar_proxy.h](proxy/scroll_bar_proxy.h:47)
- Inner ScrollBar: [../scroll/inner/scroll_bar.h](../scroll/inner/scroll_bar.h:58)
- Theme configuration: `core/components/scroll_bar/scroll_bar_theme.h`
