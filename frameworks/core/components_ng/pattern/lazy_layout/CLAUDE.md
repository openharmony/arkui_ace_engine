# LazyLayout Pattern Subdirectory Rules

This document contains specialized rules for the LazyLayout Pattern directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Responsibility Boundaries

### Core Responsibilities

**LazyGridLayoutPattern** is the core logic layer for lazy-loading grid layout components, responsible for:

1. **Lazy Loading Management**
   - Only measure and layout visible items + prediction buffer
   - Schedule predictive rendering tasks during idle time
   - Manage position cache for fast scrolling

2. **Parent Container Validation**
   - Validate LazyGrid is used under WaterFlow component
   - Set `needLazyLayout` flag on appropriate parent chain
   - Abort with LOGF_ABORT if parent hierarchy is invalid

3. **Layout Information Management**
   - Maintain position mapping (`posMap_`) for all measured items
   - Track visible range (`startIndex_`, `endIndex_`)
   - Manage cache range (`layoutedStartIndex_`, `layoutedEndIndex_`)
   - Handle prediction deadline for idle tasks

4. **Focus Management**
   - Provide ScopeFocus support for keyboard navigation
   - Support universal focus direction (all directions)

5. **Adjust Offset Tracking**
   - Track layout adjustments via `AdjustOffset` structure
   - Report offset changes to parent WaterFlow

### What Not to Do

- ❌ **Don't handle rendering directly** - Rendering is handled by child GridItem components
- ❌ **Don't create child nodes manually** - Child nodes are created by WaterFlow data source
- ❌ **Don't implement scroll logic** - Scrolling is handled by parent WaterFlow
- ❌ **Don't directly manipulate layout algorithm state** - Use LayoutInfo interface
- ❌ **Don't bypass parent validation** - Must verify WaterFlow parent in `OnAttachToMainTree()`

## Architectural Layer Relationships

### Relationship with LazyLayoutPattern Base Class

```
Pattern (Base Class)
    └─ LazyLayoutPattern (Abstract Base)
        ├─ AdjustOffset tracking
        ├─ Lazy layout interface
        └─ LazyGridLayoutPattern (Derived)
            ├─ Grid-specific lazy loading
            ├─ Parent validation
            ├─ Prediction task scheduling
            └─ Focus management
```

**Key Constraints**:
- LazyGridLayoutPattern inherits lazy layout interfaces from LazyLayoutPattern
- Must implement `GetAdjustOffset()` and `GetAndResetAdjustOffset()` virtual methods
- Don't duplicate lazy layout logic already in base class
- Follow lifecycle method call order defined by Pattern base class

### Relationship with WaterFlow Parent

**Parent-Child Structure**:
```
WaterFlow FrameNode
    └─ LazyVGridLayout FrameNode
        └─ GridItem FrameNode(s) (created by data source)
            └─ GridItemPattern (handles individual item)
```

**Separation of Responsibilities**:
- **WaterFlowPattern**: Handle scrolling, viewport management, focus navigation
- **LazyGridLayoutPattern**: Lazy layout calculation, position caching, prediction
- **GridItemPattern**: Individual item rendering and interaction

**⚠️ Critical Constraints**:
- LazyVGridLayout MUST be a descendant of WaterFlow component
- Can be nested through: `COMMON_VIEW_ETS_TAG`, `NODE_CONTAINER_ETS_TAG`, `BuilderProxyNode`, `FLOW_ITEM_ETS_TAG`
- If parent is not WaterFlow or allowed intermediate nodes, `LOGF_ABORT` will be triggered
- Don't set `needLazyLayout` on arbitrary parents - only WaterFlow and specific intermediate nodes

### Relationship with LazyGridLayoutAlgorithm

**Data Flow**:
```
Pattern (Business Logic Layer)
    ├─ Layout state (layoutInfo_, itemTotalCount_)
    ├─ Axis direction (axis_)
    └─ Prediction control (deadline_)
         ↓
LayoutAlgorithm (Layout Calculation Layer)
    ├─ Measure (lazy or full measurement strategy)
    ├─ Layout (position grid items)
    ├─ Cache management (position cache for fast scrolling)
    └─ Prediction (idle time pre-rendering)
```

**⚠️ Critical Constraints**:
- LayoutAlgorithm should not directly access Pattern's prediction task state
- Don't post prediction tasks in LayoutAlgorithm
- Pattern receives layout results in `OnDirtyLayoutWrapperSwap()`
- LayoutAlgorithm uses `layoutInfo_->deadline_` to limit prediction work

### Relationship with LazyGridLayoutInfo

**Info Layer** (`lazy_grid_layout_info.h`):
- Maintains position mapping: `std::map<int32_t, GridItemMainPos> posMap_`
- Tracks visible range: `startIndex_`, `endIndex_`
- Tracks cache range: `layoutedStartIndex_`, `layoutedEndIndex_`
- Manages prediction state: `deadline_`

**Pattern Layer**:
- Creates LayoutInfo instance in constructor
- Passes LayoutInfo to LayoutAlgorithm
- Checks `NeedPredict()` to decide if prediction task should be posted

**⚠️ Critical Constraints**:
- Pattern and Algorithm share ownership of LayoutInfo (RefPtr)
- Don't modify LayoutInfo state directly in Pattern - use Algorithm
- LayoutInfo is the single source of truth for layout state

### Relationship with Model

**Model Layer** (`lazy_grid_layout_model.h`):
- Provides ArkTS/TS declarative APIs
- Creates LazyVGridLayout FrameNode
- Manages property settings (columnsTemplate, rowGap, columnGap)

**Pattern Layer**:
- Receives property changes through `OnDirtyLayoutWrapperSwap()`
- Implements lazy loading logic
- Not directly exposed to developers

**⚠️ Critical Constraints**:
- Don't call Model methods directly in Pattern
- Model and Pattern have unidirectional dependency: Model → Pattern
- Properties flow: ArkTS → Model → LayoutProperty → Pattern/Algorithm

## Behaviors That Must Not Change

### 1. Parent Validation Logic

**Parent Validation** (must remain consistent):

```cpp
void LazyGridLayoutPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedLazyLayout(true);

    auto parent = host->GetParent();
    while (parent) {
        auto frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            parent = parent->GetParent();
            continue;
        }

        // Allowed intermediate nodes
        if (parent->GetTag() == V2::COMMON_VIEW_ETS_TAG ||
            parent->GetTag() == V2::NODE_CONTAINER_ETS_TAG ||
            parent->GetTag() == "BuilderProxyNode" ||
            parent->GetTag() == V2::FLOW_ITEM_ETS_TAG) {
            frameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }

        // Must be WaterFlow
        if (parent->GetTag() != V2::WATERFLOW_ETS_TAG) {
            LOGF_ABORT("LazyGridLayout cannot be used under the %{public}s",
                       parent->GetTag().c_str());
        }
        return;
    }
}
```

**Prohibited**:
- ❌ Skip parent validation
- ❌ Allow LazyGrid under arbitrary parents
- ❌ Remove `LOGF_ABORT` for invalid parents
- ❌ Change the order of parent traversal

### 2. Prediction Task Scheduling

**Prediction Task Flow** (must remain consistent):

```
OnDirtyLayoutWrapperSwap()
    ↓
Check layoutInfo_->NeedPredict()
    ↓ (if true)
PostIdleTask() → AddPredictTask to PipelineContext
    ↓
ProcessIdleTask(deadline)
    ↓
Set layoutInfo_->deadline_ = deadline
    ↓
FrameNode::ProcessOffscreenNode()
    ↓
Reset layoutInfo_->deadline_
```

**Prohibited**:
- ❌ Post prediction task without checking `NeedPredict()`
- ❌ Ignore deadline in prediction task
- ❌ Modify deadline during prediction execution
- ❌ Call `ProcessOffscreenNode` without setting deadline

### 3. Position Mapping Structure

**GridItemMainPos** (must remain consistent):
```cpp
struct GridItemMainPos {
    int32_t laneIdx = 0;      // Lane (column) index, 0-based
    float startPos = 0.0f;    // Main axis start position
    float endPos = 0.0f;      // Main axis end position
};
```

**Prohibited**:
- ❌ Change field names or types
- ❌ Add new fields without updating all usage sites
- ❌ Use `startPos`/`endPos` for cross axis

### 4. Lane Calculation Formula

**Lane Floor/Ceil** (must remain consistent):
```cpp
int32_t LanesFloor(int32_t index) const
{
    int32_t tempIndex = std::min(index, totalItemCount_ - 1);
    return lanes_ <= 1 ? tempIndex : (tempIndex - tempIndex % lanes_);
}

int32_t LanesCeil(int32_t index) const
{
    int32_t tempIndex = lanes_ <= 1 ? index : (index - index % lanes_ + lanes_ - 1);
    return std::min(tempIndex, totalItemCount_ - 1);
}
```

**Prohibited**:
- ❌ Change formula logic
- ❌ Handle `lanes_ <= 1` case differently
- ❌ Remove `std::min` bounds check

### 5. Cache Size Default

**Cache Size** (must remain consistent):
```cpp
float cacheSize_ = 0.5f;  // 50% of viewport size
```

**Prohibited**:
- ❌ Change default cache size without performance testing
- ❌ Set cache size to 0 (breaks smooth scrolling)
- ❌ Set cache size > 1.0 (wastes memory)

## Common Pitfalls

### 1. Prediction Task Deadline Not Respected

**⚠️ Common Mistakes**:
- ❌ **Ignoring deadline causes prediction task to block main thread**
  - Scenario: Prediction task runs beyond deadline, freezes UI
  - Consequence: Janky scrolling, ANR (Application Not Responding)

**Correct Approach**:
```cpp
void LazyGridLayoutAlgorithm::PredictLayoutForward(
    LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset)
{
    auto deadline = layoutInfo_->deadline_.value();
    int32_t currIndex = layoutInfo_->layoutedEndIndex_;

    while (currIndex < totalItemCount_ - 1 &&
           LessNotEqual(layoutedEnd, layoutInfo_->cacheEndPos_)) {
        // Check deadline BEFORE expensive operations
        if (GetSysTimestamp() > deadline) {
            break;  // Time's up, stop prediction
        }

        // Measure and layout next item
        // ...
        currIndex++;
    }
}
```

### 2. Position Map Not Updated After Layout

**⚠️ Common Mistakes**:
- ❌ **Forgot to update posMap_ after measuring item**
  - Scenario: Item measured but position not recorded
  - Consequence: Cache lookup fails, item re-measured on next scroll

**Correct Approach**:
```cpp
void LazyGridLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper,
    int32_t startIndex, float startPos)
{
    // ... measure item ...
    float itemMainSize = wrapper->GetGeometryNode()->GetFrameSize().Height();

    // Always update posMap_ after measurement
    GridItemMainPos pos;
    pos.laneIdx = laneIdx;
    pos.startPos = currentPos;
    pos.endPos = currentPos + itemMainSize;
    layoutInfo_->SetPosMap(currIndex, pos);

    // Update current position
    currentPos += itemMainSize + spaceWidth_;
}
```

### 3. Invalid Parent Hierarchy

**⚠️ Common Mistakes**:
- ❌ **Using LazyVGridLayout without WaterFlow parent**
  - Scenario: Directly place LazyVGridLayout in Column
  - Consequence: LOGF_ABORT crashes app

**Correct Approach**:
```typescript
// ❌ Wrong: No WaterFlow parent
Column() {
  LazyVGridLayout() {
    // items
  }
}

// ✅ Correct: Under WaterFlow
WaterFlow() {
  LazyVGridLayout() {
    // items
  }
  .columnsTemplate("1fr 1fr")
}

// ✅ Correct: Through allowed intermediate nodes
WaterFlow() {
  FlowItem() {
    LazyVGridLayout() {
      // items
    }
  }
}
```

### 4. Adjust Offset Not Reset

**⚠️ Common Mistakes**:
- ❌ **AdjustOffset accumulates across layouts**
  - Scenario: Offset keeps growing, items drift away
  - Consequence: Items positioned incorrectly

**Correct Approach**:
```cpp
// Pattern stores offset
AdjustOffset LazyGridLayoutPattern::GetAdjustOffset() const
{
    return layoutInfo_->adjustOffset_;
}

// Parent WaterFlow reads and resets
AdjustOffset LazyGridLayoutPattern::GetAndResetAdjustOffset()
{
    AdjustOffset ret = layoutInfo_->adjustOffset_;
    layoutInfo_->adjustOffset_ = AdjustOffset();  // Reset!
    return ret;
}

// WaterFlow usage
auto offset = lazyGridPattern->GetAndResetAdjustOffset();
// Apply offset and it's automatically reset
```

### 5. Total Item Count Out of Sync

**⚠️ Common Mistakes**:
- ❌ **totalItemCount_ differs from actual data source size**
  - Scenario: Data source updated but count not refreshed
  - Consequence: Crash when accessing out-of-bounds index

**Correct Approach**:
```cpp
bool LazyGridLayoutPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(
        dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<LazyGridLayoutAlgorithm>(
        layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);

    // Always sync count from algorithm
    itemTotalCount_ = layoutAlgorithm->GetTotalItemCount();

    if (layoutInfo_->NeedPredict()) {
        PostIdleTask();
    }
    return false;
}
```

### 6. needAllLayout Flag Misuse

**⚠️ Common Mistakes**:
- ❌ **Set needAllLayout_=true unnecessarily**
  - Scenario: All items measured even with 10000+ data
  - Consequence: First layout takes seconds, freezes UI

**Correct Approach**:
```cpp
void LazyGridLayoutAlgorithm::SetRefencesPos(float startPos, float endPos,
    float referencePos, bool forwardLayout)
{
    viewStart_ = startPos;
    viewEndPos_ = endPos;
    referencePos_ = referencePos;
    forwardLayout_ = forwardLayout;
    needAllLayout_ = false;  // Enable lazy loading!
}

void LazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (layoutInfo_->deadline_) {
        return;  // Prediction mode
    } else if (totalItemCount_ == 0) {
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else if (needAllLayout_) {
        MeasureGridItemAll(layoutWrapper);  // Only if explicitly needed
    } else {
        MeasureGridItemLazy(layoutWrapper);  // Default: lazy loading
    }
}
```

### 7. Focus Algorithm Not Configured

**⚠️ Common Mistakes**:
- ❌ **Keyboard navigation doesn't work in LazyGrid**
  - Scenario: Tab key doesn't move focus between grid items
  - Consequence: Poor accessibility

**Correct Approach**:
```cpp
FocusPattern LazyGridLayoutPattern::GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm LazyGridLayoutPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(
        ScopeFocusDirection::UNIVERSAL,  // All directions
        false,                            // Not cyclic
        true,                             // Wrap enabled
        ScopeType::OTHERS                 // Scope type
    );
}
```

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// LazyLayout related logs
TAG_LOGI(AceLogTag::ACE_LAZY_LAYOUT, "LazyGrid prediction started");
TAG_LOGD(AceLogTag::ACE_LAZY_LAYOUT, "startIndex: %{public}d, endIndex: %{public}d",
         layoutInfo_->startIndex_, layoutInfo_->endIndex_);

// Algorithm logs
TAG_LOGD(AceLogTag::ACE_LAYOUT, "lanes: %{public}d, totalItems: %{public}d",
         lanes_, totalItemCount_);

// State change logs
TAG_LOGI(AceLogTag::ACE_LAZY_LAYOUT, "NeedPredict: %{public}s",
         layoutInfo_->NeedPredict() ? "true" : "false");
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void LazyGridLayoutInfo::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("totalItemCount", totalItemCount_);
    json->Put("startIndex", startIndex_);
    json->Put("endIndex", endIndex_);
    json->Put("lanes", lanes_);
    json->Put("totalMainSize", totalMainSize_);
    json->Put("layoutedStartIndex", layoutedStartIndex_);
    json->Put("layoutedEndIndex", layoutedEndIndex_);
    json->Put("cachedStartIndex", cachedStartIndex_);
    json->Put("cachedEndIndex", cachedEndIndex_);

    // Position map size
    json->Put("posMapSize", static_cast<int32_t>(posMap_.size()));
}

void LazyGridLayoutPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(layoutInfo_);
    layoutInfo_->DumpAdvanceInfo(json);
    json->Put("itemTotalCount", itemTotalCount_);
    json->Put("axis", axis_ == Axis::VERTICAL ? "VERTICAL" : "HORIZONTAL");
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Pattern state
axis_                      // Layout direction (VERTICAL/HORIZONTAL)
itemTotalCount_            // Total number of items
layoutInfo_                // Layout information container

// LayoutInfo state
posMap_                    // Position mapping (index → GridItemMainPos)
startIndex_                // First visible item index
endIndex_                  // Last visible item index
totalItemCount_            // Total item count
lanes_                     // Number of columns
totalMainSize_             // Total main axis size
layoutedStartIndex_        // Cached start index
layoutedEndIndex_          // Cached end index
deadline_                  // Prediction deadline (if set)

// LayoutProperty state
propRowGap_                // Row gap spacing
propColumnGap_             // Column gap spacing
propColumnsTemplate_       // Column template string

// Algorithm state
needAllLayout_             // Whether full layout needed
viewStart_                 // Viewport start position
viewEndPos_                // Viewport end position
forwardLayout_             // Layout direction flag
```

### 4. Common Problem Localization

**Problem: Items not visible**
- Check if `totalItemCount_` > 0
- Check if `startIndex_` and `endIndex_` are valid
- Verify WaterFlow parent exists
- Check `columnsTemplate` is correctly set
- Verify viewport size is valid

**Problem: Scrolling is janky**
- Check if prediction deadline is respected
- Verify position cache is being used
- Check for expensive operations in Measure/Layout
- Verify `cacheSize_` is appropriate (not 0)

**Problem: Items positioned incorrectly**
- Check `posMap_` has correct positions
- Verify `lanes_` calculation matches `columnsTemplate`
- Check if `spaceWidth_` (gap) is applied correctly
- Verify `laneIdx` is within 0 to `lanes_-1`

**Problem: Prediction not working**
- Check `NeedPredict()` returns true
- Verify prediction task is posted via `AddPredictTask`
- Check if `deadline_` is set during prediction
- Verify `ProcessOffscreenNode` is called

**Problem: Parent validation fails**
- Check parent hierarchy includes WaterFlow
- Verify intermediate nodes are allowed types
- Check if parent tags match expected values

## Special Feature Constraints

### Lazy Loading Measurement Strategy

**Measurement Strategy**:
```cpp
void LazyGridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (layoutInfo_->deadline_) {
        // Prediction mode: time-constrained measurement
        return;
    } else if (totalItemCount_ == 0) {
        // Empty data
        layoutInfo_->SetTotalItemCount(0);
        totalMainSize_ = 0.0f;
    } else if (needAllLayout_) {
        // Full layout: measure all items (rare, only when needed)
        MeasureGridItemAll(layoutWrapper);
    } else {
        // Lazy loading: measure only visible + cache range
        MeasureGridItemLazy(layoutWrapper);
    }
}
```

**⚠️ Constraints**:
- Must check `deadline_` first (prediction mode has priority)
- `needAllLayout_` should rarely be true
- Default to lazy loading mode for normal operation

### Position Cache Management

**Cache Strategy**:
```cpp
void LazyGridLayoutAlgorithm::LayoutCachedItems(LayoutWrapper* layoutWrapper,
    float crossSize, const OffsetF& paddingOffset)
{
    // Layout items using cached positions
    for (auto index = layoutedStartIndex_; index <= layoutedEndIndex_; index++) {
        auto it = layoutInfo_->posMap_.find(index);
        if (it != layoutInfo_->posMap_.end()) {
            // Use cached position, skip measurement
            SetItemOffset(wrapper, it->second, crossSize, paddingOffset);
        }
    }
}
```

**⚠️ Constraints**:
- Always check if position exists in `posMap_` before using
- Don't assume all cached items have valid positions
- Update cache when layout constraints change (gap, template, etc.)

### Column Template Parsing

**Template Examples**:
```
"1fr 1fr 1fr"           → 3 equal columns
"1fr 2fr 1fr"           → 3 columns, middle is 2x width
"100px 1fr 100px"       → Fixed + flexible + fixed
"repeat(3, 1fr)"        → 3 equal columns (if supported)
```

**⚠️ Constraints**:
- Template parsing happens in LayoutAlgorithm
- Invalid template should fall back to single column
- Don't modify template after initial layout without re-measure

### GridItemMainPos Structure

**Position Structure**:
```cpp
struct GridItemMainPos {
    int32_t laneIdx = 0;      // Which lane (column) this item belongs to
    float startPos = 0.0f;    // Start position on main axis
    float endPos = 0.0f;      // End position on main axis
};
```

**⚠️ Constraints**:
- `laneIdx` must be in range [0, lanes_-1]
- `startPos` <= `endPos` (invariant)
- Positions are relative to container, not viewport

### AdjustOffset Tracking

**Offset Structure**:
```cpp
struct AdjustOffset {
    float start = 0.0f;  // Top edge adjustment (+ = up, - = down)
    float end = 0.0f;    // Bottom edge adjustment (+ = down, - = up)
};
```

**⚠️ Constraints**:
- Offset is consumed by WaterFlow after read
- Must reset offset after `GetAndResetAdjustOffset()`
- Offset accumulates within single layout pass

### Focus Navigation

**Focus Configuration**:
```cpp
FocusPattern GetFocusPattern() const
{
    return { FocusType::SCOPE, true };
}

ScopeFocusAlgorithm GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(
        ScopeFocusDirection::UNIVERSAL,  // All 4 directions
        false,                            // Not cyclic
        true,                             // Wrap at edges
        ScopeType::OTHERS
    );
}
```

**⚠️ Constraints**:
- Focus type must be `SCOPE`
- Direction should be `UNIVERSAL` for grid navigation
- Wrap should be enabled for better UX
- Scope type is `OTHERS` (not list-specific)

## Performance Constraints

### 1. Layout Performance

**Target**: Layout should complete within 16ms (60 FPS)

**Anti-pattern**:
```cpp
// ❌ Expensive operations in Measure
void LazyGridLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper,
    int32_t startIndex, float startPos)
{
    while (currIndex < totalItemCount_) {
        // Measure item
        wrapper->Measure(contentConstraint);

        // ❌ Expensive string formatting in hot path
        std::string log = "Item " + std::to_string(currIndex) +
                         " at " + std::to_string(currentPos);
        TAG_LOGI(AceLogTag::ACE_LAZY_LAYOUT, "%s", log.c_str());  // Slow!
    }
}
```

**Correct Approach**:
- Keep Measure loop lightweight
- Use `TAG_LOGD` for debug logs (can be compiled out)
- Pre-calculate column widths and positions
- Avoid string operations in hot paths

### 2. Memory Usage

**⚠️ Constraint**:
- `posMap_` grows with number of measured items
- For 10000 items, position map can consume significant memory
- Cache size (`cacheSize_`) affects number of active nodes

**Correct Usage**:
```cpp
// ✅ Reasonable cache size
float cacheSize_ = 0.5f;  // 50% of viewport

// ❌ Too large cache
float cacheSize_ = 2.0f;  // 200% of viewport, wastes memory

// ✅ Clear old cache entries when scrolling far
if (std::abs(newStartIndex - oldStartIndex) > cacheThreshold) {
    layoutInfo_->posMap_.clear();  // Reset cache
}
```

### 3. Prediction Task Timing

**⚠️ Constraint**:
- Prediction tasks should respect deadline
- Typical prediction time budget: 8-12ms per frame
- Check timestamp frequently in prediction loop

**Correct Timing**:
```cpp
void LazyGridLayoutAlgorithm::PredictLayoutForward(LayoutWrapper* layoutWrapper,
    float crossSize, const OffsetF& paddingOffset)
{
    auto deadline = layoutInfo_->deadline_.value();
    int32_t currIndex = layoutInfo_->layoutedEndIndex_;

    while (currIndex < totalItemCount_ - 1) {
        // ✅ Check deadline BEFORE each item
        if (GetSysTimestamp() > deadline) {
            break;  // Stop prediction
        }

        // Measure item
        // ...

        // ✅ Check deadline AFTER expensive operation
        if (GetSysTimestamp() > deadline) {
            break;
        }

        currIndex++;
    }
}
```

### 4. Position Lookup Performance

**Best Practices**:
```cpp
// ✅ Use map::find() for O(log n) lookup
auto it = layoutInfo_->posMap_.find(index);
if (it != layoutInfo_->posMap_.end()) {
    pos = it->second;
}

// ❌ Don't use linear search
for (auto& pair : layoutInfo_->posMap_) {
    if (pair.first == index) {  // O(n) slow!
        pos = pair.second;
        break;
    }
}
```

## Backward Compatibility

### API Version Differences

LazyGrid is relatively new, no significant version differences currently.

**Future considerations**:
- If adding new lazy loading strategies, maintain existing behavior
- If changing cache defaults, provide override option
- Maintain parent validation rules for compatibility

### Deprecated But Cannot Remove

None currently deprecated. All public APIs are stable.

### New Method Constraints

- New public methods must consider performance impact
- Don't change default cache size without benchmarking
- If adding new layout strategies, keep existing as default
- Maintain parent validation for compatibility

## Summary

**Core Principles**:
1. **Parent validation is mandatory** - LazyVGridLayout MUST be under WaterFlow
2. **Lazy loading is the default** - Only measure visible + cache, not all items
3. **Respect prediction deadline** - Never let prediction task block main thread
4. **Position cache is critical** - Maintain accurate `posMap_` for performance
5. **AdjustOffset must be reset** - Consume offset after reporting to parent
6. **Performance matters** - Keep Measure/Layout under 16ms, check deadline frequently

**Remember**: This is framework core code for high-performance grid layouts. Before modifying:
- Understand lazy loading flow thoroughly
- Confirm won't break WaterFlow integration
- Consider performance impact (memory + CPU)
- Test with large datasets (10000+ items)
- Verify parent validation still works

**Testing Checklist**:
- [ ] Parent validation works (WaterFlow + intermediate nodes)
- [ ] LOGF_ABORT triggers for invalid parents
- [ ] Lazy loading only measures visible items
- [ ] Prediction tasks respect deadline
- [ ] Position cache improves scroll performance
- [ ] AdjustOffset is consumed and reset
- [ ] Focus navigation works in all directions
- [ ] Large dataset (10000+) scrolls smoothly
- [ ] Memory usage is reasonable
