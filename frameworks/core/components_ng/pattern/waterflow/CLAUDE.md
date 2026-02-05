# WaterFlow Pattern

> Supplements root `CLAUDE.md`. All root-level rules apply.

## Overview

WaterFlow is a scrollable multi-column "waterfall" layout. Items are placed into the shortest lane.                                                      
Two layout modes exist:

- **TOP_DOWN** — full layout information retained
- **SLIDING_WINDOW** — viewport-window model for large datasets

Both modes support **WaterFlowSections** for multi-segment layouts.

---

## Responsibilities

### Pattern handles
- Scroll state & interaction (offset, velocity, overscroll)
- Layout algorithm selection
- Event dispatching (ReachStart, ReachEnd, ScrollIndex, Observer events)
- Sections synchronization via callbacks
- Cache preloading orchestration

### Pattern does NOT handle
- Item measurement/positioning → **LayoutAlgorithm**
- Drawing/rendering → **PaintMethod**
- Item creation → **LazyForEach / LayoutWrapper**
- Cross-axis sizing → **LayoutProperty**

### LayoutInfo stores
- Mode-specific layout state (items, lanes, offsets)
- Viewport range (`startIndex_`, `endIndex_`)
- Scroll position and boundary state

### LayoutAlgorithm executes
- **Measure phase**: fill viewport, measure items
- **Layout phase**: position items
- **Note**: `WaterFlowLayoutAlgorithm` updates positional fields directly in `FillViewport()`. `WaterFlowSegmentedLayout` and `WaterFlowLayoutSW` call   
  `Sync()` for state consolidation.

  ---                                                                                                                                                      

## Architecture & Algorithm Selection

```
WaterFlowPattern  
├── layoutInfo_ (WaterFlowLayoutInfoBase)  
│       ├── WaterFlowLayoutInfo      [TOP_DOWN]  
│       └── WaterFlowLayoutInfoSW    [SLIDING_WINDOW]  
└── CreateLayoutAlgorithm()  
    ├── WaterFlowLayoutAlgorithm   [TOP_DOWN, no sections AND system flag off]  
    │   └── inherits WaterFlowLayoutBase  
    ├── WaterFlowSegmentedLayout   [TOP_DOWN, sections OR system flag on]  
    │   └── inherits WaterFlowSegmentLayoutBase  
    └── WaterFlowLayoutSW          [SLIDING_WINDOW, supports sections via inheritance]  
        └── inherits WaterFlowSegmentLayoutBase  
  
where WaterFlowSegmentLayoutBase inherits WaterFlowLayoutBase 
```

### Selection rules

1. If mode is **SLIDING_WINDOW** → `WaterFlowLayoutSW`
2. Else if sections exist OR `SystemProperties::WaterFlowUseSegmentedLayout()` → `WaterFlowSegmentedLayout`
3. Else → `WaterFlowLayoutAlgorithm`

`SystemProperties::WaterFlowUseSegmentedLayout()` is a system-level switch that alters architecture by forcing the segmented algorithm.


### Inheritance hierarchy

- `WaterFlowLayoutAlgorithm` directly inherits `WaterFlowLayoutBase`
- `WaterFlowSegmentLayoutBase` inherits `WaterFlowLayoutBase` and provides shared section support
- Both `WaterFlowSegmentedLayout` and `WaterFlowLayoutSW` inherit `WaterFlowSegmentLayoutBase`, gaining section capabilities through this inheritance
---

## Layout Mode Differences

### TOP_DOWN
- Retains full layout information for all measured items
- `currentOffset_` is always accurate (not estimated)
- `scrollTo()` / `animateTo()` work reliably based on stored item positions
- Supports fast position lookup via binary search (`endPosArray_`)

### SLIDING_WINDOW
- Maintains only viewport + cache window (windowed model)
- Scroll offset may become **estimated** after jumps or section changes
- Position-based `scrollTo()` / `animateTo()` may be unreliable → Prefer `ScrollToIndex()`
- Uses lane-based window structure
- Can trigger misalignment correction to rebuild layout

### Both modes
- Support segmented layouts via **WaterFlowSections**
- Allow per-section layout differences (columns, gaps, margins)

---

## Lifecycle Invariants

1. **BeforeCreateLayoutWrapper()**
   - Process pending section changes
   - Prepare segmentation state

2. **CreateLayoutAlgorithm()**
   - Select algorithm based on mode / sections / system flag

3. **Measure()**
    - Fill viewport, measure items
    - **For WaterFlowLayoutSW**: `Sync()` is called once at the end of Measure as a post-measure consolidation step that:
        - Calculates `startIndex_`, `endIndex_` from lane data
        - Updates `startPos_`, `endPos_`
        - Sets boundary flags (e.g., `itemStart_`, `itemEnd_`, `offsetEnd_`)
        - Resets `delta_` to 0
        - Consumes pending offset changes
    - **For WaterFlowSegmentedLayout**: `Sync()` may be called multiple times during measurement in different scenarios (offset scrolling, jump           
      operations, height changes) to update positional state
    - **For WaterFlowLayoutAlgorithm**: Core positional fields are updated directly in `FillViewport()` during measurement (no `Sync()` call)

4. **Layout()**
    - Position items (executed by LayoutAlgorithm)
    - **LayoutAlgorithm may**:
        - Call `UpdateStartIndex()` for index calibration (`WaterFlowLayoutAlgorithm` does this)
        - Update `firstIndex_` for viewport tracking
        - Call cache state methods like `BeginCacheUpdate()` / `EndCacheUpdate()` (SW only)
    - **Pattern does NOT directly participate in Layout execution**
        - Pattern may call state synchronization methods (e.g., `UpdateStartIndex()`) in `OnDirtyLayoutWrapperSwap()`
    - Most positional updates occur during Measure phase

5. **OnDirtyLayoutWrapperSwap()**
   - Calibrate scroll state (may call `UpdateStartIndex()` for state synchronization)
   - Reset transient flags
   - Fire layout-dependent events

6. **TriggerPostLayoutEvents()**
   - Dispatch scroll / reach / observer events

### Rules

- **Pattern** does not directly execute layout positioning (this is LayoutAlgorithm's responsibility)
- **Pattern** may call state synchronization methods (e.g., `UpdateStartIndex()`) in `OnDirtyLayoutWrapperSwap()`
- **LayoutAlgorithm** may perform index adjustments during its Layout phase execution
- `measureInNextFrame_` defers event firing and triggers re-measure in next frame

---

## Event Semantics

### ReachStart
ReachStart is a **layout-state boundary event** with mode-specific implementations:
- **TOP_DOWN mode**: Uses **offset-transition-based** detection, comparing previous and current scroll offsets against `contentStartOffset`
- **SLIDING_WINDOW mode**: Uses **flag-change-based** detection (checking `itemStart_` flag transitions) combined with **offset-transition-based**       
  overscroll recovery                                                                                                                                      
  Both approaches detect the start boundary, but through different mechanisms suited to their layout models.

### ReachEnd
Triggered only when:
- Layout indicates end-of-content boundary, **and**
- `repeatDifference_ == 0` (all repeat items loaded)

### ScrollIndex
Triggered when the visible item range changes.

Observer events fire alongside user callbacks for scroll and reach events.

---

## Critical Invariants (DO NOT BREAK)

1. **Index conversion must respect footer participation**                                                                                                
   All FlowItem index → child node conversions must use layout-provided mapping                                                                          
   to correctly account for footer participation.

2. **Transient state cleanup**                                                                                                                           
   Jump and position-calculation flags must be cleared after layout swap.                                                                                
   Missing resets lead to state corruption.

3. **Sync timing (WaterFlowSegmentedLayout and WaterFlowLayoutSW only)**
    - Sync consumes pending offset changes
    - Must not run before measurement completes
    - Note: WaterFlowLayoutAlgorithm updates positional fields directly in `FillViewport()` without using Sync

4. **Misalignment correction**                                                                                                                           
   Must be checked at:
    - Scroll end
    - Animation stop
    - After layout swap in `OnDirtyLayoutWrapperSwap()` (especially at section boundaries)

   Layout may need to reset and rebuild if state becomes inconsistent.

5. **Section change flow**                                                                                                                               
   Section updates propagate via callbacks → queued changes → processed before next layout.

6. **Cache preload isolation (SW)**                                                                                                                      
   Cache measurement must not permanently modify visible layout window state.

7. **Pattern–Algorithm boundary**
    - **Pattern** does not directly participate in LayoutAlgorithm's Layout phase execution
    - **Pattern** may call state synchronization methods (e.g., `UpdateStartIndex()`) in `OnDirtyLayoutWrapperSwap()`
    - **LayoutAlgorithm** may perform index calibration during Layout phase (e.g., `WaterFlowLayoutAlgorithm` calls `UpdateStartIndex()`)
    - Most positional updates originate from Measure phase (via `Sync()` for segmented/SW, or direct updates in `FillViewport()` for basic layout)
    - Cache state methods (`BeginCacheUpdate()` / `EndCacheUpdate()`) are SW-only, called by LayoutAlgorithm

---

## Common Pitfalls

1. Inconsistent lane/index mappings
2. Footer index miscalculation
3. Assuming precise offset in SLIDING_WINDOW after jumps
4. Reach-end firing while repeat items still loading
5. Not clearing position-calculation flags
6. Running Sync before measurement completes (only applies to WaterFlowSegmentedLayout and WaterFlowLayoutSW)

---

## Debug Cheat Sheet

Key state groups:

- **Viewport range**: `startIndex_`, `endIndex_`
- **Boundary state**: `itemStart_`, `offsetEnd_`
- **Scroll transition**: `delta_`, `totalOffset_`, `currentOffset_`
- **Jump state**: `jumpIndex_`, `duringPositionCalc_`
- **Deferred layout**: `measureInNextFrame_`, `synced_` (SW only)
- **Data shift**: `newStartIndex_`, `repeatDifference_`

Useful dumps:
- `DumpAdvanceInfo()`
- Lane state dump (SLIDING_WINDOW)

## Notes
### UpdateStartIndex() behavior differences
In segmented layouts with non-empty `itemInfos_`, `UpdateStartIndex()` returns early without executing update logic, as the item position data structure
is already maintained.

### WaterFlowLayoutSW section support
`WaterFlowLayoutSW` gains section support through inheritance from `WaterFlowSegmentLayoutBase`, not through direct implementation. This allows it to    
reuse segmented layout logic while maintaining the sliding window model.

### WaterFlowLayoutInfo Sync() method availability
`WaterFlowLayoutInfo` provides a `Sync()` method for post-measurement state consolidation, but `WaterFlowLayoutAlgorithm` doesn't call it. Instead,      
`WaterFlowLayoutAlgorithm` updates positional fields (`startIndex_`, `endIndex_`, `itemStart_`, `itemEnd_`, `offsetEnd_`) directly within                
`FillViewport()` during the measurement phase.