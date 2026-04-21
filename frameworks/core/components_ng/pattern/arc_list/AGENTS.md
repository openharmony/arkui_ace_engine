# ArcList Unit Test Documentation

## Directory Structure

```
test/unittest/core/pattern/arc_list/
├── BUILD.gn                           # GN build configuration file
├── arc_list_test_ng.h                 # Test base class header file
├── arc_list_test_ng.cpp               # Test base class implementation
├── arc_list_pattern_test_ng.cpp       # Pattern functionality tests
├── arc_list_attr_test_ng.cpp          # Attribute tests
├── arc_list_common_test_ng.cpp        # Common functionality tests
├── arc_list_layout_test_ng.cpp        # Layout algorithm tests
├── arc_list_scroller_event_test_ng.cpp # Scroll event tests
├── arc_list_scroller_test_ng.cpp      # Scroller tests
├── arc_list_swipe_test_ng.cpp         # Swipe-to-delete tests
└── arc_scroll_test_ng.cpp            # Arc scroll bar tests
```

## Overview

This test directory contains unit tests for the **ArcList** (Arc-shaped List) component, covering core functionality, layout algorithms, event handling, swipe interactions, and more. ArcList is a specialized list component in OpenHarmony ACE Engine designed for wearable devices, supporting arc-shaped layout and digital crown scrolling.

## Test Base Class

### ArcListTestNg

The base class for all tests, defined in [arc_list_test_ng.h](arc_list_test_ng.h), providing test infrastructure and helper methods.

#### Key Constants

| Constant Name | Value | Description |
|---------------|--------|-------------|
| `LIST_WIDTH` | 240.f | List width |
| `LIST_HEIGHT` | 400.f | List height |
| `ITEM_WIDTH` | 60.f | List item width |
| `ITEM_HEIGHT` | 100.f | List item height |
| `TOTAL_ITEM_NUMBER` | 6 | Total number of list items |
| `VIEW_ITEM_NUMBER` | 4 | Number of visible items |
| `ARC_LIST_ITER_SCALE` | 0.92f | Arc list iteration scale factor |
| `ARC_LIST_FRICTION` | 0.8f | Friction coefficient |
| `ARC_LIST_ITEM_SNAP_SIZE` | 72.5f | Snap size |

#### Core Member Variables

```cpp
RefPtr<FrameNode> frameNode_;                          // Frame node
RefPtr<ArcListPattern> pattern_;                       // Pattern object
RefPtr<ListEventHub> eventHub_;                        // Event hub
RefPtr<ArcListLayoutProperty> layoutProperty_;         // Layout property
RefPtr<ScrollablePaintProperty> paintProperty_;        // Paint property
```

#### Key Helper Methods

| Method | Description |
|---------|-------------|
| `CreateList()` | Create ArcList component |
| `CreateListWithHeader()` | Create ArcList with header |
| `CreateListItem()` | Create list item |
| `CreateListItems()` | Batch create list items |
| `ScrollUp/ScrollDown()` | Scroll up/down |
| `ScrollToIndex()` | Scroll to specified index |
| `ScrollToEdge()` | Scroll to boundary |
| `UpdateCurrentOffset()` | Update current offset |
| `GetALLItem()` | Get all list items |

## Test File Categories

### 1. Pattern Functionality Tests (arc_list_pattern_test_ng.cpp)

Tests core functionality of `ArcListPattern`, containing 11 test cases.

#### Test Case List

| Test Case | Description |
|-----------|-------------|
| `OnDirtyLayoutWrapperSwap001` | Test dirty swap when skipping measure and layout |
| `OnDirtyLayoutWrapperSwap002` | Test dirty swap during normal layout |
| `ScrollListForFocus` | Test focus scroll functionality |
| `ToJsonValue` | Test JSON serialization |
| `GetItemDisplayInfo` | Test getting item display information |
| `StartSnapAnimation` | Test starting snap animation |
| `GetScrollUpdateFriction` | Test getting scroll friction coefficient |
| `HandleScrollBarOutBoundary001/002` | Test scroll bar out-of-bounds handling |
| `CreateAnalyzerOverlay` | Test creating gradient edge overlay |

### 2. Attribute Tests (arc_list_attr_test_ng.cpp)

Contains approximately **140+ test cases**, covering various ArcList attributes.

#### Main Test Categories

**Layout Attribute Tests**
- `ArcListLayoutProperty001-006` - Layout property serialization/deserialization
- `ArcListItemLayoutProperty001-003` - List item layout properties

**Space Attribute Tests**
- `AttrSpace001-003` - Space attribute tests

**Initial Index Tests**
- `AttrInitIndex001-006` - Initial index attribute tests

**Scroll Bar Attribute Tests**
- `AttrScrollBar001-002` - Scroll bar display mode

**Snap Alignment Tests**
- `AttrScrollSnapAlign001-005` - Scroll snap alignment tests

**Other Attributes**
- `AttrSLECM001` - Edge effect and chain animation
- `AttrEnableScrollInteraction001-004` - Enable scroll interaction
- `AttrFriction001-003` - Friction coefficient
- `FadingEdge001-002` - Fading edge effect
- `InitDisableEvent001` - Disable event initialization

**Layout Algorithm Related**
- `GetOneItemSnapPosByFinalPos001-005` - Get single item snap position
- `GetItemSnapPosition001-004` - Get item snap position
- `GetMidIndex001-002` - Get middle index
- `SetListChildrenMainSize001` - Set child main axis size

### 3. Common Functionality Tests (arc_list_common_test_ng.cpp)

#### Test Case List

| Test Case | Description |
|-----------|-------------|
| `FocusStep001-007` | Focus step tests |
| `PerformActionTest002` | Perform action test |
| `FRCCallback001` | FRC (Frame Rate Control) callback test |
| `EventHub002` | Event hub test |
| `GetScrollUpdateFriction001-002` | Scroll friction coefficient tests |

### 4. Layout Algorithm Tests (arc_list_layout_test_ng.cpp)

Contains approximately **80+ test cases**, testing core logic of layout algorithm.

#### Main Test Categories

**Layout Algorithm Tests**
- `GetNearScale001` - Get near scale factor
- `UpdatePosMap001` - Update position map
- `FixPredictSnapOffset001-002` - Fix predicted snap offset
- `MeasureList001` - Measure list
- `FixPredictSnapPos001-002` - Fix predicted snap position

**Alignment Tests**
- `FixPredictSnapOffsetAlignCenter001-007` - Center alignment fix

**Header Tests**
- `MeasureHeader001` - Measure header
- `LayoutHeader001-003` - Layout header

**Boundary Handling**
- `HandleScrollBarOutBoundary001-004` - Scroll bar out-of-bounds handling
- `CheckNeedUpdateHeaderOffset001-009` - Check if header offset needs update

**Other Layout Tests**
- `PaintMethod003` - Paint method test
- `Pattern007-008` - Pattern tests
- `Pattern010` - Layout test
- `ListLayout_SafeArea001-002` - Safe area layout test
- `ChildrenMainSize005-006` - Child main axis size tests

**ListItem Tests**
- `ListItemCreateForCardModeTest001` - Card mode creation
- `ListItemHoverEventForCardModeTest001` - Hover event
- `ListItemPressEventForCardModeTest001` - Press event

### 5. Scroll Event Tests (arc_list_scroller_event_test_ng.cpp)

Tests scroll-related events, containing approximately 15 test cases.

#### Test Case List

| Test Case | Description |
|-----------|-------------|
| `Event001-002` | Scroll callback tests |
| `Event003-005` | Reach start/end events |
| `Event006-007` | Reach boundary events |
| `ScrollWillReachEdge001` | About to reach edge event |
| `OnScrollFrameOffset001-002` | Scroll frame offset events |
| `OnScrollCallback001` | Scroll callback |
| `OnScrollTouchEdgeInsets001` | Scroll touch edge insets |

### 6. Scroller Tests (arc_list_scroller_test_ng.cpp)

Tests scroll functionality, containing approximately 40+ test cases.

#### Main Test Categories

**Scroll to Index Tests**
- `ScrollToIndex001-020` - Index scrolling in various scenarios
- `ScrollToIndexWithSpace001` - Index scrolling with space
- `ScrollToIndexWithHeader001` - Index scrolling with header

**Scroll to Position Tests**
- `ScrollTo001-008` - Scroll to specified position

**Scroll to Edge Tests**
- `ScrollToEdge001-005` - Scroll to boundary

**Boundary State Tests**
- `IsAtTop001-003` - Top state judgment
- `IsAtBottom001-004` - Bottom state judgment

**Other Scroll Tests**
- `ScrollPage001-002` - Page scrolling
- `ScrollBy001` - Relative scrolling
- `Scroll001` - Basic scrolling

### 7. Swipe-to-Delete Tests (arc_list_swipe_test_ng.cpp)

Tests swipe-to-delete functionality for list items, containing approximately 30 test cases.

#### Main Test Categories

**Basic Swipe Tests**
- `SwiperItem001-004` - Basic swipe item functionality

**Edge Effect Tests**
- `SwiperItemWithEdgeEffect001-002` - Edge effect (Spring/None)

**Delete Area Tests**
- `SwipeEnterDeleteArea001-003` - Enter delete area
- `SwipeExitDeleteArea001-003` - Exit delete area

**Other Swipe Tests**
- `SwipeActionOnOffsetChange001-002` - Offset change events
- `SwipeToTopOrBottom001-002` - Swipe to top/bottom

### 8. Arc Scroll Bar Tests (arc_scroll_test_ng.cpp)

Tests arc scroll bar component, containing approximately 10 test cases.

#### Test Case List

| Test Case | Description |
|-----------|-------------|
| `ArcScrollBarTestNg001` | Drag test |
| `ArcScrollBarTestNg002` - RTL layout drag test |
| `ArcScrollBarTestNg003` | Touch/Hover/Rect area tests |
| `ArcScrollBarTestNg004` | Arc scroll bar test |

## Key Test Scenarios

### 1. Layout Algorithm

ArcList uses a special arc layout algorithm, tests cover:
- **Scale Factor Calculation**: Calculate scale factor based on distance from center
- **Position Mapping**: Maintain position map for items
- **Snap Alignment**: Support START/CENTER/END/AUTO alignment modes
- **Header Handling**: Support sticky header

### 2. Scroll Interactions

- **Digital Crown Scrolling**: Support digital crown scrolling for smartwatches
- **Touch Scrolling**: Support gesture swiping
- **Scroll Bar Control**: Quick positioning via scroll bar

### 3. Boundary Handling

- **Spring Effect**: Elastic rebound when exceeding boundaries
- **Boundary Events**: Trigger events when reaching top/bottom
- **Out-of-Bounds Protection**: Prevent scrolling beyond valid range

### 4. Performance Optimization

- **Caching Mechanism**: Control cache count via `cachedCount`
- **On-Demand Loading**: Only create items in visible area
- **Position Prediction**: Predict scroll stop position for performance optimization

## Test Coverage

### Feature Coverage

| Feature Module | Coverage | Test Case Count |
|---------------|-----------|------------------|
| Layout Algorithm | High | 80+ |
| Attribute Settings | High | 140+ |
| Scroll Interactions | High | 40+ |
| Event Handling | Medium | 15+ |
| Swipe-to-Delete | Medium | 30+ |
| Pattern | High | 11+ |
| **Total** | - | **320+** |

### Branch Coverage

Tests cover the following key branches:
- ✅ Different scroll sources (UPDATE/AXIS/BAR/ANIMATION, etc.)
- ✅ Different alignment modes (START/CENTER/END/AUTO)
- ✅ Boundary conditions (top/bottom/out-of-bounds)
- ✅ Empty list handling
- ✅ Header present/not present
- ✅ Different platform versions (API 9/10)
- ✅ Different edge effects (Spring/None)
- ✅ List item styles (NORMAL/CARD)

## Testing Best Practices

### 1. Test Naming Convention

```cpp
/**
 * @tc.name: <test_case_name>
 * @tc.desc: <test_description>
 * @tc.type: FUNC
 */
HWTEST_F(<test_class>, <test_case_name>, TestSize.Level1)
{
    // Test code
}
```

### 2. Assertion Usage

```cpp
// Equality assertion
EXPECT_EQ(actual, expected);

// Boolean assertion
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);

// Floating point assertion
EXPECT_TRUE(IsEqual(float1, float2));
EXPECT_TRUE(NearEqual(float1, float2));
```

### 3. Helper Macros

```cpp
// Get child nodes
GetChildFrameNode(frameNode_, index)
GetChildPattern<Type>(frameNode_, index)

// Get position/size
GetChildX(frameNode_, index)
GetChildY(frameNode_, index)
GetChildRect(frameNode_, index)
```

## Dependencies

### Internal Dependencies

```
arc_list_test_ng.cpp (base class)
    ├── arc_list_pattern_test_ng.cpp
    ├── arc_list_attr_test_ng.cpp
    ├── arc_list_common_test_ng.cpp
    ├── arc_list_layout_test_ng.cpp
    ├── arc_list_scroller_event_test_ng.cpp
    ├── arc_list_scroller_test_ng.cpp
    └── arc_list_swipe_test_ng.cpp

scroll_test_ng.cpp (base class)
    └── arc_scroll_test_ng.cpp
```

### External Dependencies

- `core/components_ng/pattern/arc_list/*` - ArcList component implementation
- `core/components_ng/pattern/list/*` - List component base implementation
- `core/components_ng/pattern/arc_scroll/*` - Arc scroll component
- `test/mock/*` - Mock objects

## Build Configuration

### Key BUILD.gn Contents

```gn
ace_unittest("arc_list_test_ng") {
  type = "new"
  sources = [
    "arc_list_attr_test_ng.cpp",
    "arc_list_common_test_ng.cpp",
    "arc_list_layout_test_ng.cpp",
    "arc_list_pattern_test_ng.cpp",
    "arc_list_scroller_event_test_ng.cpp",
    "arc_list_scroller_test_ng.cpp",
    "arc_list_swipe_test_ng.cpp",
    "arc_list_test_ng.cpp",
    "arc_scroll_test_ng.cpp",
    # ... other source files
  ]
}
```

## Running Tests

```bash
# Build tests
./build.sh --product-name <product> --build-target arc_list_test_ng

# Run tests
./arkui_arc_list_test_ng
```

## Test Data

### Typical Test Scenario Data

| Scenario | List Size | Item Count | Item Height | Space |
|----------|-----------|-------------|--------------|--------|
| Basic scenario | 240×400 | 6 | 100 | 0 |
| Scroll scenario | 240×400 | 20 | 100 | 0 |
| With space | 240×400 | 16 | 100 | 10 |
| With header | 240×400 | 10 | 100 | 0 |

### Boundary Test Data

- **Minimum items**: 1
- **Maximum test items**: 20
- **Invalid indices**: -2, 100
- **Boundary indices**: 0, maxIndex

---
