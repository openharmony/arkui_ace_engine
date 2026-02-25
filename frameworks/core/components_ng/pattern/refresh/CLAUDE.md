# Refresh Pattern Subdirectory Rules

This document contains specialized rules for the Refresh Pattern directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Responsibility Boundaries

### Core Responsibilities

**RefreshPattern** is the core logic layer for pull-to-refresh components, responsible for:

1. **Gesture Handling**
   - Handle pan gesture events (drag start/update/end/cancel)
   - Calculate pull down distance with damping
   - Trigger refresh when threshold is crossed

2. **State Management**
   - Manage refresh state transitions (INACTIVE → DRAG → OVER_DRAG → REFRESH → DONE)
   - Update refresh status and fire corresponding events
   - Coordinate with child scrollable components

3. **Animation Control**
   - Control spring animations for smooth feedback
   - Manage LoadingProgress animation states
   - Handle custom builder UI animations

4. **Nested Scrolling**
   - Coordinate scroll handling with child components (List, Grid, WaterFlow)
   - Handle nested scroll modes (SELF_FIRST, PARENT_FIRST, SELF_ONLY, PARALLEL)
   - Manage scroll offset and child positioning

5. **Custom Builder Support**
   - Add/remove custom refresh UI via `@Builder`
   - Replace default LoadingProgress with custom UI

### What Not to Do

- ❌ **Don't handle rendering directly** - Rendering is handled by LoadingProgress Pattern or custom builder
- ❌ **Don't create child nodes manually** - Child nodes are created in `RefreshModelNG::Create()`
- ❌ **Don't manage animation timing manually** - Use framework animation system (AnimationUtils)
- ❌ **Don't directly modify child scroll position** - Use nested scroll interfaces
- ❌ **Don't skip state transitions** - Always follow proper state machine

## Architectural Layer Relationships

### Relationship with NestableScrollContainer Base Class

```
NestableScrollContainer (Base Class)
    └─ RefreshPattern (Derived Class)
        ├─ Gesture Handling
        ├─ State Management
        ├─ Animation Control
        └─ Nested Scrolling Coordination
```

**Key Constraints**:
- RefreshPattern inherits nested scroll logic from NestableScrollContainer
- Don't duplicate nested scroll logic already in base class
- Follow lifecycle method call order defined by base class
- Implement `HandleScroll()` for nested scroll coordination

### Relationship with Child Scrollable Components

**Child Node Structure**:
```
Refresh FrameNode
    └─ Scrollable Child FrameNode (List/Grid/WaterFlow)
        └─ ScrollablePattern (handles child scrolling)
```

**Separation of Responsibilities**:
- **RefreshPattern**: Handle pull-to-refresh gesture, manage refresh state, control animations
- **Child ScrollablePattern**: Handle content scrolling, report scroll position/boundary

**⚠️ Critical Constraints**:
- RefreshPattern accesses child through `GetFirstChild()` or specific child reference
- Don't directly call child Pattern's scroll methods
- Use nested scroll interfaces (`HandleScroll()`, `OnScrollStartRecursive()`, `OnScrollEndRecursive()`)
- Child must report scroll boundary correctly for refresh to trigger

### Relationship with RefreshLayoutAlgorithm

**Data Flow**:
```
Pattern (Business Logic Layer)
    ├─ Refresh state (refreshStatus_, scrollOffset_)
    ├─ Animation state (animationState_, isSourceFromAnimation_)
    └─ Refresh configuration (refreshOffset_, friction_)
         ↓
LayoutAlgorithm (Layout Calculation Layer)
    ├─ Measure (measure refresh container)
    ├─ Layout (position custom builder or LoadingProgress)
    └─ Position child scrollable component
```

**⚠️ Critical Constraints**:
- LayoutAlgorithm should not directly access Pattern's gesture or animation state
- Don't trigger animations in LayoutAlgorithm
- Pattern receives layout results in `OnDirtyLayoutWrapperSwap()`

### Relationship with Model

**Model Layer** (`refresh_model_ng.h`):
- Provides ArkTS/TS declarative APIs
- Creates Refresh FrameNode and child scrollable node
- Manages property settings (refreshOffset, friction, loadingText, etc.)

**Pattern Layer**:
- Implements gesture handling logic
- Responds to Model property changes (through `OnModifyDone()`)
- Not directly exposed to developers

**⚠️ Critical Constraints**:
- Don't call Model methods directly in Pattern
- Model and Pattern have unidirectional dependency: Model → Pattern

## Behaviors That Must Not Change

### 1. State Transition Order

**RefreshStatus State Machine** (must remain consistent):

```
INACTIVE (Initial)
    ↓ pull down
DRAG (Dragging, below threshold)
    ↓ continue pulling past threshold
OVER_DRAG (Above threshold, ready to refresh)
    ↓ release
REFRESH (Currently refreshing)
    ↓ refresh complete
DONE (Complete, returning)
    ↓ animation complete
INACTIVE
```

**Prohibited**:
- ❌ Skip state transitions (e.g., DRAG directly to REFRESH)
- ❌ Change to DONE state without completing refresh
- ❌ Fire onRefreshing event before REFRESH state

### 2. Pull Down Ratio (Damping) Formula

**Damping Formula** (must remain consistent):
```cpp
ratio = exp(-ratio_ * gamma)
where gamma = scrollOffset / contentHeight
```

**Prohibited**:
- ❌ Change damping formula without considering UX impact
- ❌ Use linear damping (breaks physics-based feel)
- ❌ Ignore content height in calculation

### 3. Event Firing Order

Refresh events must be fired in the following order:

```
UpdateRefreshStatus(REFRESH)
    ↓
FireChangeEvent("true")
    ↓
FireOnRefreshing()
    ↓
[User performs refresh action]
    ↓
UpdateRefreshStatus(DONE)
    ↓
FireChangeEvent("false")
    ↓
FireOnStateChange(DONE)
```

**Prohibited**:
- ❌ Change event firing order
- ❌ Fire onRefreshing before updating to REFRESH state
- ❌ Skip onStateChange when state transitions

### 4. Spring Animation Parameters

**Spring Animation** (must remain consistent):
```cpp
auto curve = AceType::MakeRefPtr<InterpolatingSpring>(
    velocity,  // User's drag velocity
    1.0f,      // Response (stiffness)
    228.0f,    // Damping ratio
    30.0f      // Initial displacement
);
```

**Prohibited**:
- ❌ Change spring parameters without UX validation
- ❌ Use linear or ease-in-out curve (breaks physics-based feel)
- ❌ Ignore user's drag velocity in animation

## Common Pitfalls

### 1. ScrollOffset Not Updated After Size Change

**⚠️ Common Mistakes**:
- ❌ **Forgot to update `scrollOffset_` when refresh container resizes**
  - Scenario: Refresh container resized from 100px to 200px
  - Consequence: Pull down ratio calculation incorrect, animation behaves abnormally

**Correct Approach**:
```cpp
bool RefreshPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    // Check if size changed
    auto newHeight = geometryNode->GetFrameSize().Height();
    if (containerHeight_ != newHeight) {
        containerHeight_ = newHeight;
        // Reset or adjust scrollOffset if needed
    }
    return false;
}
```

### 2. Nested Scroll Mode Misconfiguration

**⚠️ Common Mistakes**:
- ❌ **Wrong nested scroll mode causes gesture conflict**
  - Scenario: Child List and Refresh both want to handle drag
  - Consequence: Jerky scrolling or refresh not triggering

**Correct Approach**:
```cpp
// In ArkTS, configure nested scroll mode
Refresh() {
  List() {
    // content
  }
}
.nestedScroll({
  forward: NestedScrollMode.PARENT_FIRST,  // Refresh handles first when pulling down
  backward: NestedScrollMode.SELF_ONLY     // Only child handles when scrolling up
})
```

**Understanding Modes**:
- `PARENT_FIRST`: Parent (Refresh) handles scroll first, then child
- `SELF_FIRST`: Child handles first, then parent
- `SELF_ONLY`: Only child handles (Refresh won't trigger)
- `PARALLEL`: Both handle simultaneously

### 3. Custom Builder Not Properly Replaced

**⚠️ Common Mistakes**:
- ❌ **Custom builder added but default LoadingProgress still visible**
  - Scenario: Both custom builder and LoadingProgress displayed
  - Consequence: Duplicate refresh indicators

**Correct Approach**:
```cpp
void RefreshPattern::AddCustomBuilderNode(const RefPtr<NG::UINode>& builder)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!builder) {
        // Remove custom builder if null
        if (isCustomBuilderExist_) {
            host->RemoveChild(customBuilder_);
            isCustomBuilderExist_ = false;
            customBuilder_ = nullptr;
        }
        return;
    }

    // Remove default loading progress first
    if (progressChild_) {
        if (columnNode_) {
            host->RemoveChild(columnNode_);
            columnNode_ = nullptr;
            loadingTextNode_ = nullptr;
        }
        host->RemoveChild(progressChild_);
        progressChild_ = nullptr;
    }

    // Add custom builder at position 0 (top of child list)
    host->AddChild(builder, 0);
    UpdateFirstChildPlacement();
    UpdateScrollTransition(host, 0.f);

    customBuilder_ = AceType::DynamicCast<FrameNode>(builder);
    isCustomBuilderExist_ = true;
}
```

### 4. Animation State Inconsistency

**⚠️ Common Mistakes**:
- ❌ **Animation state doesn't match visual state**
  - Scenario: `refreshStatus_` is REFRESH but LoadingProgress shows FOLLOW_HAND
  - Consequence: User sees wrong animation state

**Root Cause**:
- Forgetting to update animation state after status change
- Race condition between animation callback and state update

**Correct Approach**:
```cpp
void RefreshPattern::UpdateRefreshStatus(RefreshStatus newStatus)
{
    if (refreshStatus_ == newStatus) {
        return;
    }
    refreshStatus_ = newStatus;
    isRefreshing_ = (refreshStatus_ == RefreshStatus::REFRESH);

    // Update animation state to match status
    if (refreshStatus_ == RefreshStatus::REFRESH) {
        UpdateLoadingProgressStatus(
            RefreshAnimationState::RECYCLE, 1.0f);
    } else if (refreshStatus_ == RefreshStatus::DRAG ||
               refreshStatus_ == RefreshStatus::OVER_DRAG) {
        UpdateLoadingProgressStatus(
            RefreshAnimationState::FOLLOW_HAND, GetFollowRatio());
    }

    // Fire events after state update
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto refreshEventHub = host->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(refreshEventHub);

    if (refreshStatus_ == RefreshStatus::REFRESH) {
        refreshEventHub->FireChangeEvent("true");
        refreshEventHub->FireOnRefreshing();
    } else {
        refreshEventHub->FireChangeEvent("false");
    }
    refreshEventHub->FireOnStateChange(static_cast<int>(refreshStatus_));
}
```

### 5. API Version Compatibility

**⚠️ Common Mistakes**:
- ❌ **Not handling API 10- and API 11+ differences**
  - Scenario: Using `offsetProperty_` on API 10- causes crash
  - Consequence: App crashes on older devices

**Correct Approach**:
```cpp
void RefreshPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // Check API version
    isHigherVersion_ = context->GetMinPlatformVersion() >=
                       static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);

    if (isHigherVersion_) {
        // API 11+: Use NodeAnimatableProperty
        offsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f);
        host->GetRenderContext()->SetOffsetProperty(offsetProperty_);
    } else {
        // API 10-: Use legacy property
        lowVersionOffset_ = 0.0f;
    }
}

// Always check version before using
void RefreshPattern::UpdateScrollOffset(float offset)
{
    if (isHigherVersion_) {
        CHECK_NULL_VOID(offsetProperty_);
        offsetProperty_->Set(offset);
    } else {
        lowVersionOffset_ = offset;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetRenderContext()->SetOffset(OffsetT(0.0f, offset));
    }
}
```

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// Refresh related logs
TAG_LOGI(AceLogTag::ACE_REFRESH, "Drag start and drag motion triggered");
TAG_LOGD(AceLogTag::ACE_REFRESH, "scrollOffset: %{public}f", scrollOffset_);

// Animation related logs
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Animation duration: %{public}f", duration);

// State change logs
TAG_LOGI(AceLogTag::ACE_REFRESH, "Refresh status changed %{public}d",
         static_cast<int>(refreshStatus_));
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void RefreshPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    json->Put("refreshStatus", static_cast<int>(refreshStatus_));
    json->Put("scrollOffset", scrollOffset_);
    json->Put("refreshOffset", refreshOffset_.ConvertToPx());
    json->Put("isRefreshing", isRefreshing_ ? "true" : "false");
    json->Put("animationState", static_cast<int>(animationState_));
    json->Put("isCustomBuilderExist", isCustomBuilderExist_ ? "true" : "false");
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Pattern state
refreshStatus_             // Current refresh status (INACTIVE/DRAG/OVER_DRAG/REFRESH/DONE)
scrollOffset_              // Current pull down distance (in pixels)
isRefreshing_              // Whether refresh is in progress
animationState_            // Animation state (FOLLOW_HAND/FOLLOW_TO_RECYCLE/RECYCLE)
isSourceFromAnimation_     // Whether scroll is from animation
isHigherVersion_           // API 11+ or API 10-

// LayoutProperty state
refreshOffset_             // Distance to trigger refresh (default: 64.0_vp)
friction_                  // Friction coefficient (default: 62)
pullToRefresh_             // Enable pull-to-refresh (default: true)
pullUpToCancelRefresh_     // Enable swipe-up to cancel (default: true)

// Child state
customBuilder_             // Custom builder FrameNode (if exists)
progressChild_             // Default LoadingProgress child
```

### 4. Common Problem Localization

**Problem: Refresh not triggering**
- Check if `pullToRefresh` is true
- Check if child is at top (scroll position = 0)
- Check if pull distance reaches `refreshOffset`
- Check if nested scroll mode allows Refresh to handle
- Verify `OnHandleScroll()` is being called

**Problem: Animation is jerky**
- Check if spring animation parameters are correct
- Verify scrollOffset is updated smoothly
- Check if expensive operations in drag callback
- Verify FRC (Frame Rate Collector) is optimized

**Problem: Events not firing**
- Check if RefreshEventHub exists
- Verify event callbacks registered in Model
- Check if state transition actually occurred
- Verify `isRefreshing_` matches `refreshStatus_`

**Problem: Custom builder not showing**
- Check if builder is decorated with `@Builder`
- Verify builder returns valid component
- Check if `isCustomBuilderExist_` is true
- Verify default LoadingProgress was removed

## Special Feature Constraints

### Pull-to-Refresh Gesture Recognition

**Gesture Recognition Logic**:
```cpp
bool RefreshPattern::HandleDragUpdate(float delta, float mainSpeed)
{
    // Only handle when child is at top and pulling down
    if (Positive(delta) || NearZero(scrollOffset_)) {
        auto child = GetChildScrollable();
        if (child && child->GetCurrentPosition() > 0) {
            // Child not at top, don't handle
            return { delta, false };
        }
    }

    // Calculate damped pull distance
    auto ratio = CalculatePullDownRatio();
    auto newOffset = scrollOffset_ + delta * ratio;

    // Update scroll offset and child position
    UpdateScrollOffset(newOffset);
    UpdateChildPosition();

    // Update refresh status based on threshold
    auto refreshOffsetPx = refreshOffset_.ConvertToPx();
    if (scrollOffset_ >= refreshOffsetPx) {
        if (refreshStatus_ == RefreshStatus::DRAG) {
            UpdateRefreshStatus(RefreshStatus::OVER_DRAG);
        }
    } else {
        if (refreshStatus_ == RefreshStatus::OVER_DRAG) {
            UpdateRefreshStatus(RefreshStatus::DRAG);
        }
    }

    return { 0.0f, true }; // Consumed all delta
}
```

**⚠️ Constraints**:
- Must check child scroll position before handling
- Must apply damping ratio to delta
- Must update status based on threshold crossing

### Custom Builder UI Replacement

**Replacement Rules**:
- Custom builder replaces default LoadingProgress completely
- Custom builder is always positioned at top (index 0)
- Removing custom builder (passing null) restores default UI

**⚠️ Constraints**:
```cpp
// ✅ Correct: Remove default UI before adding custom
if (progressChild_) {
    host->RemoveChild(progressChild_);
    progressChild_ = nullptr;
}
host->AddChild(builder, 0);

// ❌ Wrong: Add custom without removing default
host->AddChild(builder, 0);  // Both visible!
```

### Nested Scrolling Coordination

**Coordination Rules**:
- Refresh handles downward pull when child is at top
- Child handles upward scroll normally
- Scroll modes determine who handles first

**⚠️ Constraints**:
- Always respect `NestedScrollMode` configuration
- Don't consume delta if not handling (return remain)
- Report scroll boundary correctly to parent

### Keyboard Shortcuts

**Supported Shortcuts**:
- `F5`: Trigger refresh
- `Ctrl+R` / `Cmd+R`: Trigger refresh

**⚠️ Constraints**:
```cpp
bool RefreshPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_F5 ||
        (event.IsCombinationKey() && event.IsCtrlWith(KeyCode::KEY_R))) {
        if (!isRefreshing_) {
            QuickStartFresh();  // Directly start refresh
            return true;
        }
    }
    return false;
}
```

- Only trigger if not already refreshing
- Only trigger on key press (not release)

## Performance Constraints

### 1. Animation Frame Rate

**Target**: 60 FPS (frames per second)

**Anti-pattern**:
```cpp
// ❌ Update position too frequently with expensive operations
void RefreshPattern::UpdateScrollOffset(float offset)
{
    // Called every frame during drag
    scrollOffset_ = offset;

    // Expensive string operation in hot path
    auto offsetStr = std::to_string(offset);
    TAG_LOGI(AceLogTag::ACE_REFRESH, "%s", offsetStr.c_str());  // Slow!
}
```

**Correct Approach**:
- Keep animation loop lightweight
- Use `TAG_LOGD` for debug logs (can be compiled out)
- Pre-calculate values when possible
- Avoid string operations in hot paths

### 2. Drag Callback Frequency

**⚠️ Constraint**:
- Drag callbacks can be called 60+ times per second
- Don't perform expensive operations in drag callback
- Debounce or throttle operations if needed

**Correct Timing**:
```cpp
ScrollResult RefreshPattern::HandleDragUpdate(float delta, float mainSpeed)
{
    // ✅ Lightweight: Just update state
    auto ratio = CalculatePullDownRatio();
    auto newOffset = scrollOffset_ + delta * ratio;
    UpdateScrollOffset(newOffset);

    // ❌ Avoid: Heavy calculations or I/O
    // SaveToDatabase();  // Don't do this in drag callback!

    return { 0.0f, true };
}
```

### 3. FRC Integration

**FRC (Frame Rate Collector)** integration for performance tracking:
```cpp
void RefreshPattern::UpdateDragFRCSceneInfo(
    const std::string& scene, float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(scene, std::abs(speed), sceneStatus);
}
```

**Usage**:
- Call `UpdateDragFRCSceneInfo()` with scene info on drag start/end
- Scene name: `REFRESH_DRAG_SCENE`
- Track speed and status (START/END)

### 4. Animation Resource Management

**Best Practices**:
```cpp
// ✅ Reuse animation controller
void RefreshPattern::ResetAnimation()
{
    if (animation_) {
        animation_->Stop();  // Stop existing
        animation_ = nullptr;
    }
}

// ❌ Don't create new animation without stopping old
// auto animation = AnimationUtils::StartAnimation(...);  // Leaks old animation!
```

## Backward Compatibility

### API Version Differences

**API 10-** (PlatformVersion < VERSION_ELEVEN):
- Uses `lowVersionOffset_` float property
- Sets offset via `SetOffset(OffsetT)` on RenderContext

**API 11+** (PlatformVersion >= VERSION_ELEVEN):
- Uses `offsetProperty_` NodeAnimatableProperty
- Sets offset via `SetOffsetProperty()` on RenderContext

**Compatibility Pattern**:
```cpp
void RefreshPattern::UpdateScrollOffset(float offset)
{
    if (isHigherVersion_) {
        CHECK_NULL_VOID(offsetProperty_);
        offsetProperty_->Set(offset);
    } else {
        lowVersionOffset_ = offset;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetRenderContext()->SetOffset(OffsetT(0.0f, offset));
    }
}
```

### Deprecated But Cannot Remove

None currently deprecated. All public APIs are stable.

### New Method Constraints

- New public methods must consider both API 10- and API 11+
- Don't change default behavior of existing properties
- If behavior needs to change, add new properties to control it
- Maintain backward compatibility for existing ArkTS code

## Summary

**Core Principles**:
1. **State machine is sacred** - Always follow INACTIVE → DRAG → OVER_DRAG → REFRESH → DONE order
2. **Damping formula must not change** - `ratio = exp(-ratio_ * gamma)` provides physics-based feel
3. **Nested scroll coordination is critical** - Respect scroll modes and child boundaries
4. **Custom builder replaces default UI** - Remove LoadingProgress before adding custom builder
5. **API version compatibility is mandatory** - Handle API 10- and API 11+ differences
6. **Performance matters** - Keep drag callbacks lightweight, maintain 60 FPS

**Remember**: This is framework core code, any modification may affect upper-layer applications. Before modifying:
- Understand existing data flow
- Confirm won't break API compatibility
- Consider performance impact
- Add corresponding test cases
- Test on both API 10- and API 11+ devices
