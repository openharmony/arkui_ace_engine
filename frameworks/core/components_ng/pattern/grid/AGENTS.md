# Grid Component Documentation

This document records the core architecture, implementation details, and usage guide for the Grid component.

## Directory Structure

```
grid/
├── Core Implementation
│   ├── grid_pattern.cpp/h              # Grid main logic and lifecycle management
│   ├── grid_model_ng.cpp/h             # Grid data model (ArkTS API layer)
│   └── grid_model_static.cpp/h         # Static Grid model
│
├── Layout Algorithms (5 types)
│   │
│   ├── 1. grid_adaptive/               # Adaptive layout algorithm
│   │   └── grid_adaptive_layout_algorithm.cpp/h
│   │       # Usage: No columnsTemplate and no rowsTemplate
│   │       # Behavior: Items adaptively fill available space
│   │
│   ├── 2. grid_layout/                 # Static layout algorithm
│   │   └── grid_layout_algorithm.cpp/h
│   │       # Usage: Both columnsTemplate and rowsTemplate set
│   │       # Behavior: Fixed grid size, no scrolling
│   │
│   ├── 3. grid_custom/                # Custom layout algorithm
│   │   └── grid_custom_layout_algorithm.cpp/h
│   │       # Usage: userDefined_ flag is true
│   │       # Behavior: Supports layoutOptions, with scrolling
│   │       # Key methods: Measure(), Layout(), MeasureOnJump()
│   │
│   ├── 4. irregular/                   # Irregular layout algorithm
│   │   ├── grid_irregular_filler.cpp/h     # Fill irregular grids
│   │   ├── grid_irregular_layout_algorithm.cpp/h
│   │   │   # Usage: UseIrregularLayout() returns true
│   │   │   # Behavior: Handle items spanning multiple rows/columns
│   │   ├── grid_layout_range_solver.cpp/h  # Solve layout range
│   │   └── grid_layout_utils.cpp/h         # Layout utilities
│   │
│   ├── 5. grid_scroll/                 # Scrollable layout algorithm
│   │   ├── grid_scroll_layout_algorithm.cpp/h (5A)
│   │   │   # Usage: One template set, no layoutOptions
│   │   │   # Behavior: Pure standard scrollable layout
│   │   └── grid_scroll_with_options_layout_algorithm.cpp/h (5B)
│   │       # Usage: One template set, partial layoutOptions
│   │       # Behavior: Standard + supports layoutOptions callbacks
│   │
│   ├── grid_layout_base_algorithm.cpp/h # Layout algorithm base class
│   └── grid_item_layout_algorithm.cpp/h  # GridItem layout algorithm
│
├── Data Structures
│   ├── grid_layout_info.cpp/h          # Core layout data structure
│   ├── grid_layout_property.cpp/h      # Layout properties
│   └── grid_layout_options.h           # Layout configuration options
│
├── GridItem (Child Component)
│   ├── grid_item_pattern.cpp/h         # GridItem core logic
│   ├── grid_item_model_ng.cpp/h        # GridItem model
│   └── grid_item_layout_property.cpp/h # GridItem layout properties
│
├── Functional Modules
│   ├── grid_event_hub.cpp/h            # Event handling
│   ├── grid_focus.cpp/h                # Focus management
│   ├── grid_accessibility_property.cpp/h # Accessibility support
│   └── grid_paint_method.cpp/h         # Painting/rendering
│
└── Utilities
    ├── grid_utils.cpp/h                # Utility functions
    ├── grid_constants.h                # Constants definition
    └── grid_item_theme.h               # Theme configuration
```

## Core Data Flow

```
User API Call (ArkTS/JS)
    ↓
grid_model_ng (receives API call)
    ↓
grid_pattern (core logic management)
    ↓
grid_layout_algorithm (layout calculation)
    ↓
grid_layout_info (stores layout state)
    ↓
Rendering and event handling
```

## Core Classes and Responsibilities

### GridPattern
**File**: [grid_pattern.h](grid_pattern.h)

The main Pattern class for the Grid component, managing component lifecycle, state, and behavior.

**Core Responsibilities**:
- Component initialization and lifecycle management
- Layout coordination and event routing
- **Creating appropriate layout algorithm** ([CreateLayoutAlgorithm()](grid_pattern.cpp#L45))

**Key Members**:
```cpp
GridLayoutInfo info_;        // Layout state information
bool irregular_ = false;     // Whether to use irregular layout
bool userDefined_ = false;   // Whether to use custom layout
GridFocus focusHandler_;     // Focus handler
std::list<GridPreloadItem> preloadItemList_;  // Preload item list
```

**Key Methods**:
- `CreateLayoutAlgorithm()` - Select layout algorithm based on configuration
- `ScrollToIndex()` - Scroll to specified index
- `UpdateCurrentOffset()` - Update scroll offset
- `OnModifyDone()` - Property modification completion callback

### GridLayoutInfo
**File**: [grid_layout_info.h](grid_layout_info.h)

The core data structure for Grid layout, maintaining grid matrix, row heights, item positions, and other states.

**Core Data Members**:
```cpp
Axis axis_;                                    // Main axis direction (VERTICAL/HORIZONTAL)
double currentOffset_;                         // Current scroll offset
int32_t startIndex_;                           // Viewport first item index
int32_t endIndex_;                             // Viewport last item index
int32_t startMainLineIndex_;                   // Viewport first line index
int32_t endMainLineIndex_;                     // Viewport last line index
int32_t crossCount_;                           // Cross axis count (column count or row count)

std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;  // [row, [col, itemIdx]]
std::map<int32_t, float> lineHeightMap_;       // [line number, line height]
std::map<int32_t, int32_t> irregularItemsPosition_;  // Irregular item positions
```

**Key Methods**:
- `GetTotalHeightOfItemsInView()` - Get total height of items in viewport
- `GetContentHeight()` - Get total content height
- `FindInMatrix()` - Find item in grid matrix
- `GetItemPos()` - Get item position
- `UpdateStartIndexByStartLine()` - Update start index based on start line

## Layout Algorithm Details

### Algorithm Selection Logic

Grid supports **five different layout algorithms**, automatically selected based on `columnsTemplate`, `rowsTemplate`, and `layoutOptions`:

| Algorithm | File Location | Usage Scenario | Features |
|-----------|---------------|----------------|----------|
| **1. GridAdaptiveLayoutAlgorithm** | `grid_adaptive/` | No template set | Adaptive layout, items fill available space |
| **2. GridLayoutAlgorithm** | `grid_layout/` | Both templates set | **Static layout**, no scrolling, fixed size |
| **3. GridCustomLayoutAlgorithm** | `grid_custom/` | layoutOptions with both callbacks | Fully custom, supports scrolling |
| **4. GridIrregularLayoutAlgorithm** | `irregular/` | Detected row/column spanning items | Handle spanning items, supports scrolling |
| **5A. GridScrollLayoutAlgorithm** | `grid_scroll/` | One template, no layoutOptions | **Standard scrollable** |
| **5B. GridScrollWithOptionsLayoutAlgorithm** | `grid_scroll/` | One template, partial layoutOptions | Scrollable + partial custom options |

### Algorithm Selection Code Flow

From [GridPattern::CreateLayoutAlgorithm()](grid_pattern.cpp#L45):

```cpp
// 1. Adaptive: No templates
if (!setColumns && !setRows) {
    return GridAdaptiveLayoutAlgorithm();
}

// 2. Static: Both templates set
if (setColumns && setRows) {
    return GridLayoutAlgorithm();  // No scrolling
}

// 3-5. Scrollable layouts (only one template set)
if (userDefined_) {
    return GridCustomLayoutAlgorithm();  // layoutOptions with both callbacks
}
if (UseIrregularLayout()) {
    return GridIrregularLayoutAlgorithm();  // Detected irregular items
}
return GridScrollLayoutAlgorithm();  // Standard scrolling
```

### Flag Detection Logic

From [GridLayoutProperty::UpdateIrregularFlag()](grid_layout_property.cpp#137):

```cpp
// userDefined_ set to TRUE when:
if (layoutOptions.getStartIndexByIndex && layoutOptions.getStartIndexByOffset) {
    pattern->SetUserDefined(true);  // Both callbacks provided
}

// irregular set to TRUE when:
bool vertical = IsVertical();
for (int32_t idx : layoutOptions.irregularIndexes) {
    auto size = layoutOptions.getSizeByIndex(idx);
    // Horizontal scroll: check columns > 1
    // Vertical scroll: check rows > 1
    if ((!vertical && size.columns > 1) || (vertical && size.rows > 1)) {
        pattern->SetIrregular(true);
    }
}
```

### Configuration to Algorithm Mapping

| columnsTemplate | rowsTemplate | layoutOptions | Callbacks | Irregular Items? | Algorithm |
|:---------------:|:------------:|:-------------:|:---------:|:----------------:|:---------:|
| ❌ | ❌ | ❌ | - | - | `GridAdaptiveLayoutAlgorithm` |
| ✅ | ✅ | - | - | - | `GridLayoutAlgorithm` (no scroll) |
| ✅ | ❌ | ✅ | Both | - | `GridCustomLayoutAlgorithm` |
| ❌ | ✅ | ✅ | Both | - | `GridCustomLayoutAlgorithm` |
| ✅ | ❌ | ❌ Partial/None | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ❌ | ✅ | ❌ Partial/None | - | ✅ | `GridIrregularLayoutAlgorithm` |
| ✅ | ❌ | ❌ None | - | ❌ | `GridScrollLayoutAlgorithm` (5A) |
| ❌ | ✅ | ❌ None | - | ❌ | `GridScrollLayoutAlgorithm` (5A) |
| ✅ | ❌ | ✅ Partial | Not both | ❌ | `GridScrollWithOptionsLayoutAlgorithm` (5B) |
| ❌ | ✅ | ✅ Partial | Not both | ❌ | `GridScrollWithOptionsLayoutAlgorithm` (5B) |

### Algorithm Details

#### 1. GridAdaptiveLayoutAlgorithm
**Features**: Items adaptively fill available space, no fixed row/column count
**Supported properties**: `columnsGap`, `rowsGap`, `layoutDirection`, `maxCount`, `minCount`, `cellLength`

#### 2. GridLayoutAlgorithm
**Features**: Static grid, completely fixed, **does not support scrolling**
**Use case**: Fixed grid display with known row/column counts

#### 3. GridCustomLayoutAlgorithm
**Features**: Fully custom layout, supports scrolling
**Trigger condition**: Both `getStartIndexByIndex` and `getStartIndexByOffset` provided in `layoutOptions`

Key methods:
- `Measure()` - Measure all item sizes
- `Layout()` - Position elements
- `MeasureOnJump()` - Handle scrolling to specified index

#### 4. GridIrregularLayoutAlgorithm
**Features**: Handle row/column spanning items, supports scrolling
**Trigger condition**: Detected items with `rowSpan > 1` or `columnSpan > 1`

Related classes:
- `GridIrregularFiller` - Fill irregular grids
- `GridLayoutRangeSolver` - Calculate visible range

#### 5. GridScrollLayoutAlgorithm / GridScrollWithOptionsLayoutAlgorithm
**Features**: Standard Grid layout, supports single-direction scrolling
- **5A** (`GridScrollLayoutAlgorithm`): Pure standard scrolling
- **5B** (`GridScrollWithOptionsLayoutAlgorithm`): Supports partial `layoutOptions`

## GridLayoutOptions (Custom Layout)

**File**: [grid_layout_options.h](grid_layout_options.h)

`layoutOptions` supports fully customizable grid layout.

### Data Structures

```cpp
// Item size (row/column count)
struct GridItemSize {
    int32_t rows = 1;
    int32_t columns = 1;
};

// Item precise position
struct GridItemRect {
    int32_t rowStart = -1;
    int32_t columnStart = -1;
    int32_t rowSpan = 1;
    int32_t columnSpan = 1;
};

// Scroll position information
struct GridStartLineInfo {
    int32_t startIndex = 0;
    int32_t startLine = 0;
    double startOffset = 0.0;
    double totalOffset = 0.0;
};
```

### Callback Functions

```cpp
struct GridLayoutOptions {
    GridItemSize regularSize;                        // Regular item size
    std::set<int32_t> irregularIndexes;              // Irregular item index set

    // Callback functions
    GetSizeByIndex getSizeByIndex;                   // Get size by index
    GetRectByIndex getRectByIndex;                   // Get position by index
    GetStartIndexByOffset getStartIndexByOffset;     // Offset → Position
    GetStartIndexByIndex getStartIndexByIndex;       // Index → Position
};
```

### Callback Requirements

To trigger `GridCustomLayoutAlgorithm` (userDefined_ = true), **must provide both**:
- ✅ `getStartIndexByIndex` - Required, for scrollToIndex
- ✅ `getStartIndexByOffset` - Required, for scroll position calculation

Optional:
- `getSizeByIndex` - Irregular item size (needed when irregularIndexes non-empty)
- `getRectByIndex` - Precise positioning (alternative to getSizeByIndex)

### Usage Scenarios

- Waterfall layout
- Calendar applications (variable-sized events)
- Image gallery (featured items)
- Dashboard (different-sized widgets)

## GridItem (Child Component)

### Core Files

- [grid_item_pattern.h](grid_item_pattern.h) - GridItem main logic
- [grid_item_model_ng.h](grid_item_model_ng.h) - GridItem model
- [grid_item_layout_property.h](grid_item_layout_property.h) - GridItem layout properties

### GridItem Properties

```cpp
// Row/column spans (for irregular layout)
rowStart / rowEnd        // Row start/end
columnStart / columnEnd  // Column start/end

// Selection
selected                 // Whether selected
```

## Key Constants

**File**: [grid_constants.h](grid_constants.h)

Defines constant values used by the Grid component.

## Layout Properties (GridLayoutProperty)

**File**: [grid_layout_property.h](grid_layout_property.h)

### Core Properties

| Property | Type | Description |
|----------|------|-------------|
| `columnsTemplate` | string | Column template, e.g., `"1fr 1fr 2fr"` |
| `rowsTemplate` | string | Row template |
| `columnsGap` | Dimension | Column spacing |
| `rowsGap` | Dimension | Row spacing |
| `cachedCount` | int32_t | Cached row count |
| `layoutOptions` | GridLayoutOptions | Custom layout options |
| `ScrollEnabled` | bool | **(C++ internal)** Whether scrolling is enabled |
| `alignItems` | GridItemAlignment | Item alignment |

**Note**: `ScrollEnabled` is the C++ property name. In ArkTS/JS API, use `.enableScrollInteraction(value: boolean)` instead. |

### Key Methods

```cpp
bool IsVertical() const;              // Whether vertical grid
bool IsConfiguredScrollable() const;  // Whether scrollable
bool IsReverse() const;               // Whether reverse (RTL)
```

## Event Handling (GridEventHub)

**File**: [grid_event_hub.h](grid_event_hub.h)

Handles various events for the Grid component:
- Scroll events
- Item click events
- Scroll boundary events

## Focus Management (GridFocus)

**File**: [grid_focus.h](grid_focus.h)

Manages focus navigation within Grid:
- Focus movement
- Focus wrap mode
- Keyboard navigation

## Common Maintenance Tasks

### 1. Adding New Grid Properties

1. Add property definition in `grid_layout_property.h`
2. Parse property in `grid_model_ng.cpp`
3. Apply property in `grid_pattern.cpp` or layout algorithm
4. Add tests in `test/unittest/core/pattern/grid/`

### 2. Modifying Layout Behavior

Select the correct algorithm based on scenario:

| Scenario | Algorithm to Modify | File Location |
|----------|---------------------|---------------|
| Adaptive grid (no template) | GridAdaptiveLayoutAlgorithm | `grid_adaptive/` |
| Static grid (both templates) | GridLayoutAlgorithm | `grid_layout/` |
| Custom layout | GridCustomLayoutAlgorithm | `grid_custom/` |
| Irregular items (row/column span) | GridIrregularLayoutAlgorithm | `irregular/` |
| Single-direction scrolling | GridScrollLayoutAlgorithm | `grid_scroll/` |

**Common layout algorithm files**:
- `grid_custom_layout_algorithm.cpp` - Custom template layout
- `grid_irregular_layout_algorithm.cpp` - Irregular/spanning items
- `grid_layout_info.cpp` - State management (shared by all algorithms)

**Key methods**:
- `Measure()` - Calculate sizes of all items
- `Layout()` - Position elements in grid
- `MeasureOnJump()` - Handle scroll-to-index functionality
- `MeasureOnOffset()` - Handle scroll offset changes

### 3. Debugging Layout Issues

| Symptom | Possible Location |
|---------|-------------------|
| Wrong item positions | `Layout()` method of layout algorithm |
| Incorrect size calculation | `Measure()` method or `grid_layout_info` |
| Scrolling issues | `MeasureOnOffset()` or scroll offset calculation |
| Missing items | `GridIrregularFiller` or range calculation |
| Focus issues | `grid_focus.cpp` |

## Usage Examples

### 1. Adaptive Layout
```typescript
Grid() {
  // Items fill available space
}
// → GridAdaptiveLayoutAlgorithm
```

### 2A. Static Grid
```typescript
Grid() {
}
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
// → GridLayoutAlgorithm (no scrolling)
```

### 2B. Static Grid + Layout Options
```typescript
layoutOptions: {
    onGetGetRectByIndex:(index) => { /* ... */} //Get node size and position
}
Grid(undefined, this.layoutOptions) {
}
.columnsTemplate("1fr 1fr 1fr")
.rowsTemplate("1fr 1fr")
// → GridLayoutAlgorithm (no scrolling)
```

### 3A. Standard Scrolling
```typescript
Grid() {
}
.columnsTemplate("1fr 1fr 1fr")
// → GridScrollLayoutAlgorithm
```

### 3B. Scrolling + Partial Options
```typescript
layoutOptions: {
    irregularIndexes:[0] //Irregular nodes
}
Grid(this.scroller, this.layoutOptions) {
}
.columnsTemplate("1fr 1fr 1fr")
// → GridScrollWithOptionsLayoutAlgorithm
```

### 4. Irregular Items
```typescript
layoutOptions: {
    irregularIndexes:[0], //Irregular nodes
    onGetIrregularSizeByIndex(index) => { /* ... */}
}
Grid() {
}
.columnsTemplate("1fr 1fr")
// → GridIrregularLayoutAlgorithm
```

### 5. Fully Custom
```typescript
layoutOptions: {
    onGetStartIndexByIndex: (index) => { /* ... */ },
    onGetStartIndexByOffset: (offset) => { /* ... */ }
}
Grid() {
}
.columnsTemplate("1fr 1fr")
// → GridCustomLayoutAlgorithm
```

## Testing Grid Component

Test location: `test/unittest/core/pattern/grid/`

### Test Directory Structure

```
test/unittest/core/pattern/grid/
├── BUILD.gn                           # Test build configuration
├── grid_test_ng.cpp/h                 # Test base class
│
├── General Tests (root directory)
│   ├── grid_attr_test_ng.cpp          # Property tests
│   ├── grid_common_test_ng.cpp        # General tests
│   ├── grid_layout_test_ng.cpp        # Layout tests
│   ├── grid_pattern_test_ng.cpp       # Pattern tests
│   ├── grid_scroller_test_ng.cpp      # Scrolling tests
│   ├── grid_focus_test_ng.cpp         # Focus tests
│   ├── grid_event_test_ng.cpp         # Event tests
│   ├── grid_accessibility_test_ng.cpp # Accessibility tests
│   ├── grid_cache_layout_test_ng.cpp  # Cache layout tests
│   ├── grid_static_test_ng.cpp        # Static layout tests
│   ├── grid_sync_load_test_ng.cpp     # Sync load tests
│   ├── grid_option_layout_test_ng.cpp # Layout option tests
│   └── selectable_item_test.cpp       # Selectable item tests
│
├── custom/                            # Custom layout tests
│   ├── custom_layout_options.cpp/h    # Custom layout option utilities
│   ├── grid_custom_algorithm_test_ng.cpp
│   ├── grid_custom_layout_test_ng.cpp
│   ├── grid_custom_layout_algorithm_test.cpp
│   └── grid_custom_scroller_test_ng.cpp
│
└── irregular/                         # Irregular layout tests
    ├── grid_irregular_filler_test.cpp      # GridIrregularFiller tests
    ├── grid_irregular_layout_test.cpp      # GridIrregularLayout tests
    ├── grid_irregular_layout_testtwo.cpp   # GridIrregularLayout tests 2
    ├── grid_layout_range_solver_test.cpp   # GridLayoutRangeSolver tests
    ├── irregular_matrices.h                # Test matrix data
    └── irregular_matrics.cpp
```

### Test Base Class (GridTestNg)

**File**: `test/unittest/core/pattern/grid/grid_test_ng.h`

`GridTestNg` is the base class for all Grid tests, providing test helper methods:

```cpp
class GridTestNg : public ScrollableUtilsTestNG {
    // Grid creation
    GridModelNG CreateGrid();
    GridModelNG CreateRepeatGrid(int32_t itemNumber, ...);

    // GridItem creation
    GridItemModelNG CreateGridItem(float width, float height, ...);
    void CreateGridItems(int32_t itemNumber = 10, ...);
    void CreateFixedItems(int32_t itemNumber, ...);
    void CreateBigItem(int32_t rowStart, int32_t rowEnd, ...);

    // Scroll operations
    void UpdateCurrentOffset(float offset, int32_t source);

    // Members
    RefPtr<GridPattern> pattern_;
    RefPtr<GridEventHub> eventHub_;
    RefPtr<GridLayoutProperty> layoutProperty_;
};
```

### Running Tests

```bash
# Enter test directory
cd test/unittest

# Run irregular layout tests
python run.py -t grid_test_ng

# Run regular Grid tests
python run.py -t grid_test_regular

# Run custom layout tests
python run.py -t grid_test_custom

# Run irregular layout tests
python run.py -t grid_test_ng

# Run arkts1.2 tests
python run.py -t grid_test_static
```

### Test Coverage

| Test File | Test Content |
|-----------|--------------|
| `grid_attr_test_ng.cpp` | Property setting and updates |
| `grid_layout_test_ng.cpp` | Layout calculation and positioning |
| `grid_scroll_layout_test_ng.cpp` | Scrollable layout |
| `grid_pattern_test_ng.cpp` | Pattern core logic |
| `grid_scroller_test_ng.cpp` | Scrolling behavior |
| `grid_focus_test_ng.cpp` | Focus navigation |
| `grid_event_test_ng.cpp` | Event triggering |
| `grid_cache_layout_test_ng.cpp` | Cache mechanism |
| `grid_static_test_ng.cpp` | Static layout (arkts1.2) |
| `grid_option_layout_test_ng.cpp` | layoutOptions |
| `grid_custom_layout_test_ng.cpp` | Custom layout |
| `grid_irregular_layout_test.cpp` | Irregular layout |
| `layout_info_test.cpp` | GridLayoutInfo data structure |
| `grid_irregular_filler_test.cpp` | GridIrregularFiller |
| `grid_layout_range_solver_test.cpp` | GridLayoutRangeSolver |

## Related Files

Grid component development may need reference to:
- `frameworks/core/components_ng/pattern/scrollable/` - Scrollable base class
- `frameworks/core/layout/` - Common layout algorithms
- `frameworks/core/common/` - Shared utilities

## Design Patterns

### Strategy Pattern
Grid uses the strategy pattern to select different layout algorithms based on configuration. `CreateLayoutAlgorithm()` is the strategy selector.

### Template Method Pattern
`GridLayoutBaseAlgorithm` defines the skeleton of layout algorithms, with subclasses implementing specific steps.

### Observer Pattern
Grid handles and dispatches events through `GridEventHub`.

## JS Bridge Layer Details

### JS to C++ Mapping

**File**: [js_grid.cpp](../../../bridge/declarative_frontend/jsview/js_grid.cpp)

The Grid component maps ArkTS API to C++ implementation through the JS bridge layer.

#### Grid Creation Flow

```typescript
// ArkTS API
Grid(scroller, layoutOptions) {
  // GridItems...
}
.columnsTemplate("1fr 1fr 1fr")
.cachedCount(2)
```

```cpp
// C++ implementation (js_grid.cpp)
void JSGrid::Create(const JSCallbackInfo& info) {
    // 1. Create Scroller controller
    JSScroller* jsScroller = ...;
    positionController = GridModel::GetInstance()->CreatePositionController();
    jsScroller->SetController(positionController);

    // 2. Create Grid component
    GridModel::GetInstance()->Create(positionController, scrollBarProxy);

    // 3. Parse and set layoutOptions
    SetGridLayoutOptions(info);
}
```

#### layoutOptions Parsing

```cpp
void SetGridLayoutOptions(const JSCallbackInfo& info) {
    GridLayoutOptions option;
    auto obj = JSRef<JSObject>::Cast(info[1]);

    // Parse regularSize
    ParseGridItemSize(obj->GetProperty("regularSize"), option.regularSize);

    // Parse irregularIndexes
    auto indexes = obj->GetProperty("irregularIndexes");
    // Add to option.irregularIndexes

    // Parse callback functions
    ParseGetGridItemSize(info, obj, option);      // onGetIrregularSizeByIndex
    ParseGetGridItemRect(info, obj, option);      // onGetRectByIndex
    ParseGetStartIndexByOffset(info, obj, option); // onGetStartIndexByOffset
    ParseGetStartIndexByIndex(info, obj, option);  // onGetStartIndexByIndex

    GridModel::GetInstance()->SetLayoutOptions(option);
}
```

#### Callback Function Wrapping

```cpp
// onGetIrregularSizeByIndex callback
auto onGetIrregularSizeByIndex = [execCtx, func](int32_t index) {
    JAVASCRIPT_EXECUTION_SCOPE(execCtx);
    JSRef<JSVal> itemIndex = JSRef<JSVal>::Make(ToJSValue(index));
    auto result = func->ExecuteJS(1, &itemIndex);
    GridItemSize gridItemSize;
    ParseGridItemSize(result, gridItemSize);
    return gridItemSize;
};

// onGetStartIndexByOffset callback
auto onGetStartIndexByOffset = [execCtx, func](float offset) {
    JAVASCRIPT_EXECUTION_SCOPE(execCtx);
    JSRef<JSVal> jsOffset = JSRef<JSVal>::Make(ToJSValue(Dimension(offset).ConvertToVp()));
    auto result = func->ExecuteJS(1, &jsOffset);

    GridStartLineInfo startLineInfo {
        .startIndex_ = ...,
        .startLine_ = ...,
        .startOffset_ = ...,
        .totalOffset_ = ...
    };
    return startLineInfo;
};
```

## Scroller Scroll Control

### Scroller Interface

**API Documentation**: [ts-container-scroll.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md)

```typescript
// Create Scroller
scroller: Scroller = new Scroller();

// Main methods
scroller.scrollTo(options: ScrollOptions);           // Scroll to specified position
scroller.scrollEdge(value: Edge);                   // Scroll to edge
scroller.scrollToIndex(value: number,
                     smooth?: boolean,
                     align?: ScrollAlign,
                     options?: ScrollToIndexOptions);  // Scroll to specified index
scroller.scrollBy(dx: Length, dy: Length);        // Scroll specified distance
scroller.currentOffset(): OffsetResult;             // Get current offset
scroller.isAtEnd(): boolean;                        // Whether at bottom
scroller.isAtStart(): boolean;                      // Whether at top
scroller.getItemRect(index: number): RectResult;  // Get child component position
```

### ScrollAlign Enum

```typescript
enum ScrollAlign {
    START = 0,   // Start align - specified item start aligns with scroll container start
    CENTER = 1,  // Center align - specified item centered in scroll container on main axis
    END = 2,     // End align - specified item end aligns with scroll container end
    AUTO = 3     // Auto align - no adjustment if item fully visible, otherwise shortest distance
}
```

### ScrollOptions Object

```typescript
interface ScrollOptions {
    xOffset?: number | string;              // Horizontal scroll total offset
    yOffset?: number | string;              // Vertical scroll total offset
    animation?: ScrollAnimationOptions | boolean;  // Animation configuration
    canOverScroll?: boolean;               // Whether can stay at boundary
}

interface ScrollAnimationOptions {
    duration?: number;                     // Scroll duration, default 1000ms
    curve?: Curve | ICurve;                // Scroll curve, default Curve.Ease
    canOverScroll?: boolean;               // Whether to convert to rebound animation after scrolling to boundary
}
```

## Scroll Events Details

### Common Scroll Events

**API Documentation**: [ts-container-scrollable-common.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)

```typescript
// Scroll lifecycle events
.onReachStart(() => void)        // Triggered when reaching start position
.onReachEnd(() => void)          // Triggered when reaching end position
.onScrollStart(() => void)       // Triggered when scroll starts
.onScrollStop(() => void)        // Triggered when scroll stops

// Scroll index change events
.onScrollIndex((first: number, last: number) => void)
// first: First item index in viewport
// last: Last item index in viewport

// Scroll offset events (deprecated, use onDidScroll instead)
.onScroll((scrollOffset: number, scrollState: ScrollState) => void)
```

### Scroll Frame Events

```typescript
// Before scroll callback - can modify scroll amount
.onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => void | ScrollResult)
// scrollOffset: Upcoming scroll offset
// scrollState: Current scroll state
// scrollSource: Scroll operation source (user gesture/program call)
// Return value: Optional, specifies actual scroll offset

// During scroll callback - read-only
.onDidScroll((scrollOffset: number, scrollState: ScrollState) => void)
// scrollOffset: Current frame scroll offset
// scrollState: Current scroll state
```

### Scroll Frame Begin Events

```typescript
.onScrollFrameBegin((offset: number, state: ScrollState) => ScrollResult)
// offset: About-to-happen scroll amount
// state: Current scroll state
// Returns: { offsetRemain: number } - Actual scroll amount
```

## Scrollable Component Common Properties

**API Documentation**: [ts-container-scrollable-common.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)

### ScrollBar Properties

```typescript
.scrollBar(barState: BarState)
// BarState.Auto - Auto display
// BarState.On - Always display
// BarState.Off - Don't display
// BarState.Auto - Default value (List/Grid/Scroll)

.scrollBarWidth(value: number | string)
// Default: 4
// Unit: vp

.scrollBarColor(value: Color | number | string | Resource)
// Default: '#182431' (40% opacity)
```

### Edge Effect

```typescript
.edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions)
// EdgeEffect.Spring - Spring effect
// EdgeEffect.Fade - Shadow effect
// EdgeEffect.None - No effect

// EdgeEffectOptions
interface EdgeEffectOptions {
    alwaysEnabled?: boolean;  // Enable slide effect when content smaller than component
    effectEdge?: EffectEdge;    // Edge effect direction (START/END/BOTH)
}
```

### Nested Scrolling

```typescript
.nestedScroll(value: NestedScrollOptions)
interface NestedScrollOptions {
    scrollForward: NestedScrollMode;   // Nested scroll option when scrolling to end
    scrollBackward: NestedScrollMode;  // Nested scroll option when scrolling to start
}

// NestedScrollMode
// NestedScrollMode.SELF_ONLY - Only self scrolls
// NestedScrollMode.SELF_FIRST - Self first, parent second
// NestedScrollMode.PARENT_FIRST - Parent first, self second
// NestedScrollMode.PARALLEL - Self and parent scroll simultaneously
```

### Common Scroll Properties

```typescript
.enableScrollInteraction(value: boolean)     // Whether to support scroll gesture
.friction(value: number | Resource)         // Friction coefficient (0, +∞)
.flingSpeedLimit(speedLimit: number)        // Fling initial speed limit
.fadingEdge(enabled: boolean, options?)    // Edge fade effect
.clipContent(clip: ContentClipMode)       // Content clipping area
.contentStartOffset(offset: number | Resource)  // Content start offset
.contentEndOffset(offset: number | Resource)    // Content end offset
```

## GridItem Row/Column Span Rules

### Row/Column Number Properties

**API Documentation**: [ts-container-griditem.md](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-griditem.md)

```typescript
GridItem() {
  Text("Row/Column spanning item")
}
.rowStart(0)      // Start row number
.rowEnd(1)         // End row number (spans 2 rows: 0-1)
.columnStart(0)   // Start column number
.columnEnd(1)      // End column number (spans 2 columns: 0-1)
```

### Validity Rules

| Scenario | Row/Column Settings | Layout Result |
|---------|-------------------|---------------|
| Both templates set | Valid row/column numbers | Layout according to specified row/column numbers |
| Both templates set | rowStart/rowEnd or columnStart/columnEnd only | Layout as one row one column |
| Only columnsTemplate | Column numbers | Layout by column count, newline on position conflict |
| Only rowsTemplate | Row numbers | Layout by row count, new column on position conflict |
| No template | Any | Row/column number properties invalid |

### Exception Handling

| Property Settings | Exception Type | Corrected Layout Rule |
|:-----------------|:---------------|:----------------------|
| Only columnsTemplate set | Any row/column exception | Layout as one row one column |
| Only rowsTemplate set | Any row/column exception | Layout as one row one column |
| Both templates set | rowStart < rowEnd | Row span = min(rowEnd-rowStart+1, total rows) |
| Both templates set | rowStart > rowEnd | Layout as one row one column |
| Both templates set | columnStart < columnEnd | Column span = min(columnEnd-columnStart+1, total columns) |
| Both templates set | columnStart > columnEnd | Layout as one row one column |

### Performance Optimization Recommendations

> **Important**: When Grid contains many GridItems, using columnStart/columnEnd/rowStart/rowEnd to set row/column spanning causes scrollToIndex performance issues. Recommend using layoutOptions layout.

**Recommended Practice**:
```typescript
// Not recommended - Poor performance
GridItem() { }
.rowStart(0).rowEnd(1).columnStart(0).columnEnd(1)

// Recommended - Good performance
layoutOptions: {
    irregularIndexes: [0],
    onGetIrregularSizeByIndex: (index) => {
        if (index === 0) return [2, 2];  // 2 rows 2 columns
        return [1, 1];
    }
}
```

## Performance Optimization

### Virtual Scrolling
- Grid uses virtual scrolling, only rendering visible + cached items
- Control cache count through `cachedCount`
- Default value: 1 (changed to screen visible rows in API 11+, max 16)

### Line Skipping
When scroll offset is large, algorithms can skip measuring intermediate items and jump directly to estimated position:

```cpp
bool TrySkipping(float mainSize) {
    float delta = std::abs(info_.currentOffset_ - info_.prevOffset_);
    if (enableSkip_ && delta > mainSize) {
        info_.jumpIndex_ = Negative(delta) ? SkipLinesForward() : SkipLinesBackward();
        Jump(mainSize);
        return true;
    }
    return false;
}
```

### Preloading
- `preloadItemList_` stores items to be preloaded
- Implemented through `PreloadItems()` and `SyncPreloadItems()`

### Recommended Practices

1. **Use LazyForEach**: Combine with Grid for virtual scrolling
2. **Set reasonable cachedCount**: Balance memory and scroll smoothness
3. **Prefer layoutOptions**: Replace rowStart/rowEnd for row/column spanning items
4. **Avoid many GridItem row/column spans**: Causes scrollToIndex performance issues
5. **Enable line skipping**: Enable `enableSkip` optimization for large scroll distances
6. **Use contentStartOffset/contentEndOffset**: Set content margins to avoid first/last items sticking to edges

## API Mapping Summary

### ArkTS API → C++ Implementation

```typescript
// ArkTS
Grid(this.scroller, this.layoutOptions) {
  ForEach(this.items, (item) => {
    GridItem() { Text(item) }
  })
}
.columnsTemplate("1fr 1fr 1fr")
.cachedCount(2)
.onScrollIndex((first, last) => {})
```

```cpp
// C++ implementation path
Grid() → JSGrid::Create()
    ↓
GridModelNG::Create()
    ↓
GridPattern::OnAttachToFrameNode() [initialization]
    ↓
GridPattern::CreateLayoutAlgorithm() [algorithm selection]
    ↓
GridLayoutAlgorithm::Measure/Layout() [layout calculation]
    ↓
GridLayoutInfo::UpdateStartIndexByStartLine() [update index]
```

### Event Flow

```typescript
// ArkTS
.onScrollIndex((first: number, last: number) => void)
```

```cpp
// C++ callback chain
onScrollIndex
    → grid_event_hub.cpp
        → GridEventHub::SetOnScrollIndex()
            → JSGrid::JsOnScrollIndex()
                → Execute JavaScript callback
```

## Related Files Index

### Core Implementation
- [grid_pattern.cpp](grid_pattern.cpp) - Grid main logic
- [grid_layout_property.cpp](grid_layout_property.cpp) - Layout properties
- [grid_layout_info.cpp](grid_layout_info.cpp) - Layout data structure

### Layout Algorithms
- [grid_scroll/grid_scroll_layout_algorithm.cpp](grid_scroll/grid_scroll_layout_algorithm.cpp)
- [irregular/grid_irregular_layout_algorithm.cpp](irregular/grid_irregular_layout_algorithm.cpp)
- [grid_custom/grid_custom_layout_algorithm.cpp](grid_custom/grid_custom_layout_algorithm.cpp)

### JS Bridge
- [js_grid.cpp](../../../bridge/declarative_frontend/jsview/js_grid.cpp) - JS to C++ bridge
- [grid.d.ts](../../../../../interface/sdk-js/api/@internal/component/ets/grid.d.ts) - TypeScript interface definition

### Documentation
- [Grid API Documentation](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-grid.md)
- [GridItem API Documentation](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-griditem.md)
- [Scrollable Component Common Properties](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scrollable-common.md)
- [Scroll & Scroller](../../../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md)
