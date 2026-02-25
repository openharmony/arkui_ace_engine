# Scroll Pattern Subdirectory Rules

This document contains specialized rules for the Scroll Pattern directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Responsibility Boundaries

### Core Responsibilities

**ScrollPattern** is the core logic layer for scroll components, responsible for:

1. **Scroll Position Management**
   - Maintain current offset (`currentOffset_`)
   - Calculate scrollable distance (`scrollableDistance_`)
   - Manage scroll boundary checks (`IsAtTop()`, `IsAtBottom()`)

2. **Layout Algorithm Coordination**
   - Create `ScrollLayoutAlgorithm` instances (in `CreateLayoutAlgorithm()`)
   - Pass scroll state to LayoutAlgorithm
   - Receive layout results from LayoutAlgorithm

3. **Scroll Event Handling**
   - Handle scroll callbacks (`OnScrollCallback()`)
   - Fire scroll events (`FireOnDidScroll()`)
   - Manage edge reach events (`FireOnReachStart()`, `FireOnReachEnd()`)

4. **Special Features**
   - ScrollSnap (scroll alignment)
   - Paging (paginated scrolling)
   - FreeScroll (2D free scrolling)
   - Zoom (scaling support)

### What Not to Do

- ❌ **Don't handle rendering directly** - Rendering is handled by `ScrollPaintMethod`
- ❌ **Don't handle gesture recognition** - Gestures are handled by `ScrollablePattern` base class
- ❌ **Don't manage child component creation** - Children are managed by the frontend
- ❌ **Don't handle style properties** - Properties are managed by `ScrollLayoutProperty`

## Architectural Layer Relationships

### Relationship with ScrollablePattern Base Class

```
ScrollablePattern (Base Class)
    ├─ Gesture Recognition (PanGesture)
    ├─ Scroll Controller (ScrollPositionController)
    └─ Edge Effect (EdgeEffect)
         ↓
ScrollPattern (Derived Class)
    ├─ Scroll Logic Implementation
    ├─ Layout Algorithm Creation
    └─ Event Firing
```

**Key Constraints**:
- Don't duplicate gesture handling logic from the base class in ScrollPattern
- Public APIs provided by the base class must maintain compatibility
- Observe timing requirements when calling base class methods

### Relationship with ScrollLayoutAlgorithm

**Separation of Responsibilities**:
```
Pattern (Business Logic Layer)
    ├─ State Management (currentOffset_, scrollableDistance_)
    ├─ Event Handling (OnScrollCallback, FireOnDidScroll)
    └─ Lifecycle Management (OnModifyDone, OnDirtyLayoutWrapperSwap)
         ↓
LayoutAlgorithm (Layout Calculation Layer)
    ├─ Measure (measure child nodes)
    ├─ Layout (apply offsets)
    └─ CalcContentOffset (calculate content offset)
```

**Data Flow**:
1. Pattern creates LayoutAlgorithm instance in `CreateLayoutAlgorithm()`
2. Pattern passes `currentOffset_` to LayoutAlgorithm
3. LayoutAlgorithm calculates layout in `Measure()` / `Layout()`
4. LayoutAlgorithm returns calculation results (e.g., `scrollableDistance_`) to Pattern
5. Pattern receives layout results in `OnDirtyLayoutWrapperSwap()`

**⚠️ Critical Constraints**:
- LayoutAlgorithm **should not** directly access Pattern
- Pattern **should not** modify LayoutAlgorithm state during layout process
- Data is passed through constructors and return values

### Relationship with Model

**Model Layer** (`scroll_model_ng.h`):
- Provides ArkTS/TS declarative APIs
- Creates FrameNode and Pattern
- Manages property settings (through Modifiers)

**Pattern Layer**:
- Implements component logic
- Responds to Model property changes (through `OnModifyDone()`)
- Not directly exposed to developers

**⚠️ Critical Constraints**:
- Don't call Model methods directly in Pattern
- Model and Pattern have unidirectional dependency: Model → Pattern

## Behaviors That Must Not Change

### 1. Public API Semantics

The semantics of the following methods must remain stable, modifications must ensure backward compatibility:

```cpp
// Scroll to specified position (absolute position)
void ScrollTo(float position);

// Scroll by specified distance (relative offset)
void ScrollBy(float pixelX, float pixelY, bool smooth, ...);

// Scroll to edge
void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);

// Get current position
double GetCurrentPosition() const;
```

**Prohibited**:
- ❌ Change parameter meanings (e.g., `ScrollTo(0)` from "scroll to top" to something else)
- ❌ Change return value units (e.g., from pixels to logical pixels)
- ❌ Change boundary behavior (e.g., handling of out-of-bounds)

### 2. Event Firing Order

Scroll events must be fired in the following order:

```
OnScrollCallback (scroll start/in progress)
    ↓
FireObserverTwoDimensionOnWillScroll (about to scroll, interceptable)
    ↓
UpdateCurrentOffset (update offset)
    ↓
FireOnDidScroll (scroll complete)
    ↓
OnScrollEndCallback (scroll end)
    ↓
FireOnReachStart / FireOnReachEnd (if boundary reached)
```

**Prohibited**:
- ❌ Change event firing order
- ❌ Modify offset before OnScrollCallback
- ❌ Fire OnScrollEndCallback before FireOnDidScroll

### 3. Lifecycle Method Call Order

Pattern lifecycle methods are called by the framework and must observe:

```
1. CreateLayoutProperty() - create layout property
2. CreateEventHub() - create event hub
3. CreateLayoutAlgorithm() - create layout algorithm (on every layout)
4. OnModifyDone() - property modification complete
5. OnDirtyLayoutWrapperSwap() - layout result swap
6. OnAttachToMainTree() - attach to main tree
7. OnDetachFromMainTree() - detach from main tree
```

**Prohibited**:
- ❌ Trigger layout in OnModifyDone
- ❌ Access LayoutWrapper in CreateLayoutAlgorithm
- ❌ Access FrameNode in destructor

### 4. Scroll Boundary Behavior

Boundary checks must remain consistent:

```cpp
// Top check: currentOffset_ >= 0
bool IsAtTop() const override;

// Bottom check: currentOffset_ <= -scrollableDistance_
bool IsAtBottom(bool considerRepeat = false) const override;

// Out-of-bounds check
bool IsOutOfBoundary(bool useCurrentDelta = true) const override;
```

**Prohibited**:
- ❌ Change mathematical definition of boundaries
- ❌ Allow out-of-bounds without triggering edge effects
- ❌ Modify `scrollableDistance_` calculation method

## Common Pitfalls

### 1. Cache Invalidation Issues

**Cache Structure**:
```cpp
std::list<ScrollLayoutInfo> scrollLayoutInfos_;   // layout cache
std::list<ScrollMeasureInfo> scrollMeasureInfos_; // measure cache
```

**Cache Limit**: Maximum 30 entries per cache (LRU eviction)

**⚠️ Common Mistakes**:
- ❌ **Forgetting to invalidate cache when constraints change**
  - Wrong: Modified `ScrollLayoutProperty` but didn't mark cache invalid
  - Right: Check `layoutWrapper->ConstraintChanged()` in `OnDirtyLayoutWrapperSwap()`

- ❌ **Adding cache at wrong time**
  - Wrong: Add cache in `OnModifyDone()` (layout hasn't happened yet)
  - Right: Add cache in `OnDirtyLayoutWrapperSwap()`

**Correct Approach**:
```cpp
void ScrollPattern::AddScrollLayoutInfo()
{
    ScrollLayoutInfo info;
    info.changedTime_ = GetTimestamp();
    info.scrollableDistance_ = scrollableDistance_;
    info.scrollSize_ = viewSize_;
    info.viewPort_ = viewPort_;
    info.childSize_ = viewPortExtent_;

    scrollLayoutInfos_.push_back(info);
    if (scrollLayoutInfos_.size() > SCROLL_LAYOUT_INFO_COUNT) {
        scrollLayoutInfos_.pop_front(); // LRU
    }
}
```

### 2. Pattern and LayoutAlgorithm State Synchronization

**⚠️ Common Mistakes**:
- ❌ **Modified `currentOffset_` in Pattern, but LayoutAlgorithm doesn't know**
  - Scenario: Called `JumpToPosition()` without recreating LayoutAlgorithm
  - Consequence: Next layout uses old offset

- ❌ **Modified state in LayoutAlgorithm, but Pattern doesn't know**
  - Scenario: `scrollableDistance_` recalculated in LayoutAlgorithm
  - Consequence: Pattern's `scrollableDistance_` is stale

**Correct Approach**:
```cpp
// Pattern passes latest state when creating LayoutAlgorithm
RefPtr<LayoutAlgorithm> ScrollPattern::CreateLayoutAlgorithm() override
{
    auto scrollLayoutAlgorithm = MakeRefPtr<ScrollLayoutAlgorithm>(currentOffset_);
    scrollLayoutAlgorithm->SetScrollableDistance(scrollableDistance_);
    return scrollLayoutAlgorithm;
}

// Pattern receives updates in OnDirtyLayoutWrapperSwap
bool ScrollPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
{
    auto algorithm = DynamicCast<ScrollLayoutAlgorithm>(dirty->GetLayoutAlgorithm());
    if (algorithm) {
        scrollableDistance_ = algorithm->GetScrollableDistance();
        // ... sync other state
    }
}
```

### 3. Timing of Scroll Position Calculation

**⚠️ Common Mistakes**:
- ❌ **Access GetHost()->GetGeometryNode() in OnModifyDone**
  - Problem: geometryNode might not be updated yet
  - Consequence: Get wrong dimensions

- ❌ **Use `currentOffset_` in Measure**
  - Problem: Measure phase should not apply scroll offset
  - Consequence: Child node measure incorrect

**Correct Timing**:
- ✅ **Access layout results in `OnDirtyLayoutWrapperSwap()`**
- ✅ **Apply offset in `LayoutAlgorithm::Layout()`**

### 4. ScrollSnap and Paging Conflicts

**⚠️ Common Mistakes**:
- ❌ **Enable both ScrollSnap and Paging simultaneously**
  - Scenario: Set both `scrollSnapInterval` and `enablePaging`
  - Consequence: Undefined behavior

**Correct Approach**:
```cpp
bool ScrollPattern::IsScrollSnap() override
{
    // Check Paging first
    if (enablePagingStatus_ == ScrollPagingStatus::VALID) {
        return true;
    }
    // Then check ScrollSnap
    return !snapOffsets_.empty() && GetScrollSnapAlign() != ScrollSnapAlign::NONE;
}
```

### 5. Recursive Layout Triggering

**⚠️ Common Mistakes**:
- ❌ **Modify layout properties during layout**
  - Scenario: Call `FireOnDidScroll()` in `OnDirtyLayoutWrapperSwap()`, callback modifies properties
  - Consequence: Trigger new layout, possible infinite loop

**Correct Approach**:
```cpp
// Use PostTask for delayed processing
FireOnDidScroll(scroll);
// If need to trigger new layout, use:
auto host = GetHost();
CHECK_NULL_VOID(host);
host->GetTaskExecutor()->PostTask(
    [weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // Trigger new layout
    },
    TaskExecutor::TaskType::UI);
```

### 6. Edge Effect Coordinate System

**⚠️ Common Mistakes**:
- ❌ **Confuse `currentOffset_` with scroll direction**
  - Scenario: When scrolling down, `currentOffset_` is negative
  - Consequence: Edge effect direction wrong

**Remember**:
- `currentOffset_ > 0`: Content offset upward (show upper content)
- `currentOffset_ < 0`: Content offset downward (show lower content)
- `currentOffset_ == 0`: At top
- `currentOffset_ == -scrollableDistance_`: At bottom

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// Scroll related logs
TAG_LOGI(AceLogTag::ACE_SCROLL, "ScrollTo position: %{public}f", position);

// Layout related logs
TAG_LOGD(AceLogTag::ACE_LAYOUT, "Measure: selfSize=%{public}s", size.ToString().c_str());
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Use dump interface for debugging**:
```cpp
// Call in component
// DumpHandle->DumpFocusTree();

// Or implement own dump method
void ScrollPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override
{
    json->Put("currentOffset", currentOffset_);
    json->Put("scrollableDistance", scrollableDistance_);
    json->Put("viewPort", viewPort_.ToString().c_str());
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Pattern state
currentOffset_           // current offset
scrollableDistance_      // scrollable distance
viewPort_                // viewport size
viewPortExtent_          // content size

// Cache state
scrollLayoutInfos_.size()      // cache entry count
scrollMeasureInfos_.size()     // measure cache entry count

// Snap state
snapOffsets_.size()            // snap point count
enablePagingStatus_            // paging status
```

### 4. Common Problem Localization

**Problem: Scroll position incorrect**
- Check if `currentOffset_` matches value in LayoutAlgorithm
- Check if `scrollableDistance_` is calculated correctly
- Check if offset was modified at wrong time

**Problem: Layout cache not working**
- Check if `ConstraintChanged()` returns false
- Check if cache exceeds 30 entries
- Check if `changedTime_` is updated correctly

**Problem: Events not firing**
- Check if events registered in `OnModifyDone()`
- Check if `FireOnReachStart()` conditions are correct
- Check if `prevOffset_` is maintained correctly

## Special Feature Constraints

### ScrollSnap (Scroll Alignment)

**Calculation Timing**:
- Call `CaleSnapOffsets()` in `OnModifyDone()`
- Recalculate when `scrollSnapUpdate_` flag is true

**⚠️ Constraints**:
- `snapOffsets_` must be in ascending order
- First snapOffset must be 0 (or close to 0)
- Last snapOffset must be `-scrollableDistance_`

### FreeScroll (2D Scrolling)

**Enable Condition**:
- `GetAxis() == Axis::FREE`

**⚠️ Constraints**:
- Cannot use single-axis scroll methods (e.g., `ScrollTo()`) in FreeScroll mode
- Must use dedicated methods like `FreeScrollBy()`, `FreeScrollTo()`
- Offset is `OffsetF` (2D) not a single float value

### Zoom (Scaling)

**⚠️ Constraints**:
- `zoomScale_` valid range is `[minZoomScale_, maxZoomScale_]`
- Scaling affects `scrollableDistance_` calculation
- Scaling and scrolling can happen simultaneously, handle concurrency properly

## Performance Constraints

### 1. Avoid Frequent Measure/Layout

**Anti-pattern**:
```cpp
// ❌ Trigger layout in scroll callback
void ScrollPattern::OnScrollCallback(float offset, int32_t source) override
{
    UpdateCurrentOffset(offset, source);
    FireOnDidScroll(offset);  // If callback modifies properties, triggers new layout
}
```

**Correct Approach**:
- Use `requestFrame` to merge multiple layout requests
- Trigger layout only when scroll ends (`OnScrollEndCallback`)

### 2. Cache Hit Rate Optimization

**Target**: Cache hit rate > 80%

**Optimization Directions**:
- Reduce unnecessary constraint changes
- Use `changedTime_` to filter stale cache
- Avoid frequent modification of `ScrollLayoutProperty`

### 3. Event Callback Performance

**⚠️ Constraints**:
- `OnScrollCallback` is called frequently during scrolling
- Callbacks should not have heavy calculations (e.g., traversing all child nodes)
- Use `OnScrollEndCallback` for batch updates

## Backward Compatibility

### Deprecated But Cannot Remove Methods

```cpp
// Kept for compatibility with old code
double GetTotalOffset() const override;  // Use GetCurrentPosition() instead
```

### New Method Constraints

- New public methods must consider impact on existing APIs
- Don't change default behavior of existing methods
- If behavior needs to change, add new properties to control it

## Summary

**Core Principles**:
1. **Pattern is logic layer, not layout layer** - Leave layout calculation to LayoutAlgorithm
2. **State synchronization must be correct** - Keep Pattern ↔ LayoutAlgorithm data flow clear
3. **Manage cache properly** - Add and invalidate at appropriate times
4. **Event order must not be chaotic** - Observe framework-defined event firing order
5. **Boundary behavior must be consistent** - Maintain API semantic stability

**Remember**: This is framework core code, any modification may affect upper-layer applications. Before modifying:
- Understand existing data flow
- Confirm won't break API compatibility
- Consider performance impact
- Add corresponding test cases
