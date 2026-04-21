# ArkUI List Component - Technical Documentation

This document provides technical reference for understanding the List component implementation in the ACE Engine.

## Component Overview

List is a scrollable container that displays ListItem and ListItemGroup child components along a main axis. It is the most commonly used list component in ArkUI.

### Key Characteristics

- **Lazy Loading**: Creates only visible and preloaded child components on-demand
- **High Performance**: Supports millions of data items with LazyForEach
- **Multi-Lane Layout**: Supports lanes property for multi-lane-style lists
- **Rich Interactions**: ListItem Swipe actions, drag-drop, chain animations, scroll snapping, etc

### Component Hierarchy

```
Pattern
    └── ScrollablePattern (Scrollable container base class)
            └── SelectableContainerPattern (Selectable container)
                    └── ListPattern
                            ├── ListItemPattern
                            └── ListItemGroupPattern
```

### Inheritance Chain

```
Pattern
    └── ScrollablePattern (Nestable scroll, edge effects, scrollbar)
            └── SelectableContainerPattern (Selection, edit mode)
                    └── ListPattern (List-specific layout and behavior)
```

## Core Design Concepts

### 1. Layout Process

The List component follows a **three-phase layout flow**: Measure → Layout → OnDirtyLayoutWrapperSwap

#### Complete Call Chain

```
[Phase 1: Measure]
========================================
Framework calls
  ↓
FrameNode::Measure(parentConstraint)
  ├─ GetLayoutAlgorithm(true)
  │   └─ pattern_->CreateLayoutAlgorithm()
  │        └─ new ListLayoutAlgorithm()
  │
  └─ layoutAlgorithm_->Measure(this)
       └─ ListLayoutAlgorithm::Measure(layoutWrapper)
            ├─ Get constraints and properties
            ├─ Calculate content size
            ├─ Determine layout strategy (forward/backward/jump)
            ├─ MeasureList()
            │   ├─ GetOrCreateChildByIndex(index)
            │   │   ├─ Reuse existing nodes
            │   │   ├─ LazyForEach on-demand creation
            │   │   └─ Measure(child)
            │   └─ Record position → itemPosition_[index] = position
            └─ geometryNode->SetFrameSize(size)

[Phase 2: Layout]
========================================
Framework calls
  ↓
FrameNode::Layout()
  └─ layoutAlgorithm_->Layout(this)
       └─ ListLayoutAlgorithm::Layout(layoutWrapper)
            └─ Call Layout() for each child
                 └─ Sync itemPosition_ to GeometryNode

[Phase 3: OnDirtyLayoutWrapperSwap]
========================================
Framework calls
  ↓
ListPattern::OnDirtyLayoutWrapperSwap(dirty, config)
  ├─ Get layout results from layoutAlgorithm
  │   ├─ itemPosition_ → ListPattern::itemPosition_
  │   ├─ maxListItemIndex_ → ListPattern::maxListItemIndex_
  │   └─ contentMainSize_ → ListPattern::contentMainSize_
  │
  └─ Fire developer callbacks
       ├─ onScrollIndex(start, end, center)
       ├─ onReachStart / onReachEnd
       └─ Update selectedIndex
```

#### Key Understanding

1. **Measure and Layout are two independent methods** called separately by the framework
2. **ListLayoutAlgorithm::Measure** measures self and child node sizes
3. **ListLayoutAlgorithm::Layout** positions child nodes correctly
4. **OnDirtyLayoutWrapperSwap** exchanges layout information between framework and Pattern then fire developer callbacks

#### Layout Strategy

List determines which index to start measuring based on scroll state:

- **Forward layout**: From `startIndex_`, forward sequentially
- **Backward layout**: From `endIndex_`, backward sequentially
- **Jump layout**: From `jumpIndex_` or `targetIndex_`, aligned according to `scrollAlign_`

### 2. Lazy Loading Mechanism

LazyForEach achieves memory optimization through **on-demand creation** and **deferred destruction**.

#### Lifecycle

**Creation**:
```
List Measure needs child at index
  ↓
GetOrCreateChildByIndex(index)
  ↓
LazyForEachNode::GetFrameChildByIndex()
  ├─ Check CachedUINodeMap
  │   ├─ Hit → Return cached
  │   └─ Miss ↓
  ├─ builder_->GetChild(index)
  │   └─ Call itemGenerator(item, index)
  └─ Store in cache
```

**Destruction**:
```
List Measure complete, calculate new visible range
  ↓
SetActiveChildRange(start, end, cacheStart, cacheEnd)
  ↓
LazyForEachNode::DoSetActiveChildRange()
  ├─ Find items outside range
  ├─ Mark for destruction (add to removingNodes_)
  └─ Post to Idle task
      ↓
[Execute during idle time]
  ├─ Call Detach
  ├─ Remove from cache
  └─ Trigger aboutToRecycle() (if reusable)
```

**Key Points**:
- Items are **NOT immediately destroyed** when leaving screen, they wait for idle time
- Preload range items are also created
- With `@Reusable`, items go to reuse pool instead of being destroyed

### 3. ListItemGroup Indexing

ListItemGroup as a child component of List has its own index system.

#### Index Structure

```
List level (global indices):
  [0] ListItem                        index = 0
  [1] ListItemGroup                   index = 1
       ├─ [0] ListItem (internal)          indexInGroup = 0
       ├─ [1] ListItem                   indexInGroup = 1
       └─ [2] ListItem                   indexInGroup = 2
  [2] ListItem                        index = 2

Key point:
- The entire ListItemGroup occupies ONE index in List (index = 1)
- Internally, it has multiple children with their own indexInGroup
```

### 5. Multi-lane Layout (Lanes)

List supports multi-lane layout through the `lanes` property.

#### Layout Modes

**Fixed columns** (`lanes: N`):
```
eg. lanes = 3, totalItemCount = 5
┌──────┬──────┬──────┐
│Item_0│Item_1│Item_2│  row 0
├──────┼──────┼──────┤
│Item_3│Item_4│      │  row 1
└──────┴──────┴──────┘

Row Height Calculation:
  - Each row's height is determined by the TALLEST ListItem in that row
  - All items in the same row are TOP-ALIGNED (start from same Y position)
  - Example: If Item_0=100vp, Item_1=50vp, Item_2=20vp, then rowHeight=100vp

Position Allocation:
  mainPos (Y) = row * (rowHeight + rowSpace)
  crossPos (X) = lane * (itemWidth + laneGutter)
```

## Performance Optimization

### 1. Preloading (cachedCount)

**Purpose**: Create a small number of items outside visible area to reduce scroll lag

```typescript
List().cachedCount(5)  // Preload 5 items on each side
```

**API 12+**:
```typescript
.cachedCount({ minCount: 3, maxCount: 10 })  // Range control
.cachedCount(5, false)  // Preload but not show
```

## Key Classes and Responsibilities

### ListPattern

**Responsibility**: Business logic and state management for List

**Key Members**:
- `maxListItemIndex_`: Maximum item index
- `startIndex_` / `endIndex_`: Current visible index range
- `contentMainSize_`: Total content size (of visible content)
- `itemPosition_`: **Relative position map** for visible items in current frame
  - Records positions **relative to List viewport**
  - Example: If item2 (100px tall) is halfway above viewport top, its position = -50
  - If single-column, no space: item3 position = 50, item4 position = 150
- `posMap_`: **Absolute position map** (persistent ListPositionMap, relative to content start)
  - With `childrenMainSize`: stores ALL items' absolute positions
  - Without `childrenMainSize`: stores only items that have EVER been visible
  - Positions are absolute from content start (item0=0, item1=100, item2=200, ...)
  - Even when item2 is at viewport top (itemPosition_[2]=0), posMap_[2]=200
- `childrenSize_`: Predefined item sizes from developers
- `chainAnimation_`: Chain animation controller
- `scrollable_`: Scroll handler

### ListLayoutAlgorithm

**Responsibility**: Implements List's Measure and Layout algorithms

**Key Members**:
- `itemPosition_`: Temporary position map for current frame (synced to ListPattern after layout)
- `currentOffset_`: Current frame offset (not persistent scroll offset)
- `spaceWidth_`: Item spacing
- `lanes_`: Number of columns
- `jumpIndex_` / `targetIndex_`: Jump target indices
- `scrollAlign_`: Alignment mode

**Measure Flow**:
1. Get constraints and properties
2. Calculate content size
3. Determine layout strategy
4. MeasureList() → Measure and position items
5. Set self size

### ListItemPattern

**Responsibility**: Individual item interaction and state

### ListItemGroupPattern

**Responsibility**: Manage a group of ListItems and optional header/footer

**Child Structure** (order in children array):
```
[header] → [ListItem_0, ListItem_1, ..., ListItem_N] → [footer]
```
- Header and footer are **optional** (one or both may exist, or neither)
- If header exists: `itemStartIndex_ = 1` (first ListItem at children[1])
- If no header: `itemStartIndex_ = 0` (first ListItem at children[0])

**Key Members**:
- `header_` / `footer_`: Optional Header/Footer nodes
- `itemStartIndex_`: Index of first ListItem in children array (0 or 1)
- `groupItemPositionMap_`: Internal position map for group items (indexInGroup → position)

## Advanced Features

### 1. Chain Animation

**Effect**: Item spacing presents spring animation during scroll

**Limitations**:
- Single column only (lanes = 1)
- Must set `edgeEffect: EdgeEffect.Spring`

### 2. Scroll Snap

**Purpose**: Automatically snap to item boundary when scroll stops

**Implementation**: Find nearest item on scroll stop, calculate target position, execute animation

## Key File Index

### Pattern Implementation
- `list_pattern.h/cpp` - ListPattern main logic
- `list_item_pattern.h/cpp` - ListItemPattern interaction management
- `list_item_group_pattern.h/cpp` - ListItemGroupPattern group management

### Layout Algorithm
- `list_layout_algorithm.h/cpp` - Measure/Layout core algorithm
- `list_lanes_layout_algorithm.h/cpp` - Multi-column layout
- `list_divider_arithmetic.h/cpp` - Divider calculation

### Properties
- `list_layout_property.h/cpp` - List layout properties
- `list_item_layout_property.h/cpp` - ListItem layout properties
- `list_properties.h` - Enum and structure definitions

### Model
- `list_model_ng.h/cpp` - Declarative frontend Model interface
- `list_position_controller.h/cpp` - Scroll controller

### Utilities
- `list_position_map.h/cpp` - Position mapping
- `list_children_main_size.h` - Predefined item sizes

### Bridge
- `js_list.cpp` - JS API parsing

### Base Classes
- `scrollable/scrollable_pattern.h` - Scrollable component base class
- `scrollable/scrollable.h` - Scroll event handling
- `scrollable/selectable_container_pattern.h` - Selectable container base class

## Summary

The core of List component lies in **balancing performance and functionality**:

**Design Core**:
1. **Three-phase layout**: Measure → Layout → OnDirtyLayoutWrapperSwap
2. **Dual-layer position management**: Relative (itemPosition_, per-frame) vs Absolute (posMap_, persistent)
3. **Lazy loading**: LazyForEach + on-demand creation + deferred destruction
4. **Dual-level indexing**: List global + Group local

Master these points to handle various complex list scenarios.