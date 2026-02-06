# Syntax Subdirectory Rules

This document contains specialized rules for the Syntax directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Module Overview

**Syntax** module is the core module in ACE Engine that handles **UI syntax features and control flow**. Unlike traditional visual components (such as Button, Text), this module focuses on:

1. **Loop Rendering**: ForEach (standard loop), LazyForEach (lazy-loaded loop), Repeat (repeat rendering), RepeatVirtualScroll (virtual scrolling)
2. **Conditional Rendering**: IfElse (conditional branch rendering)
3. **Special Syntax**: WithTheme (theme scoping), ContentSlot (content slot)

**Code Scale**:
- ~21 core files
- ~6000+ lines of C++ code
- 4 loop components + 2 special components

## Responsibility Boundaries

### Core Responsibilities

**Syntax module's core responsibilities** are to provide underlying implementation support for declarative UI syntax features, specifically:

#### 1. Loop Components (Loop Components Family)

**ForEachNode** - Standard loop rendering component:
- Data-driven updates (via keyGenerator for unique identification)
- Differential algorithm implementation (CompareAndUpdateChildren)
- Drag-and-drop sorting support (MoveData, FireOnMove)

**LazyForEachNode** - Lazy-loaded loop rendering component:
- On-demand rendering (only visible range + cache range)
- Data source listening (V2::DataChangeListener interface)
- Idle task pre-building (PostIdleTask)
- L1/L2 cache management

**RepeatNode** - Simple repeat rendering component:
- Fixed-count repeat rendering
- Value-array parameter driven (repeats based on array length)
- Shares ForEachBaseNode base class

**RepeatVirtualScroll2Node** - Virtual scrolling component (API 16+):
- Only renders visible range ListItems
- Dual-layer cache mechanism (L1 active cache + L2 inactive cache)
- Node reuse strategy
- Predictive rendering

#### 2. Conditional Rendering Component

**IfElseNode** - Conditional branch rendering component:
- Branch ID management (branchId_ identifies currently active branch)
- Branch switching mechanism (SetBranchId, FlushUpdateAndMarkDirty)
- State retention strategy (TryRetake, CollectRetakenNodes)
- Node reuse support

#### 3. Special Syntax Components

**WithThemeNode** - Theme scoping component:
- Theme scope isolation (ThemeScopeId management)
- Theme update notifications (NotifyThemeScopeUpdate)
- Scope destruction callback (ThemeScopeDestroyCallback)

**ContentSlotNode** - Content slot component:
- Dynamic content attach/detach (AttachNodeContent, DetachNodeContent)
- Lifecycle management (OnAttachToMainTree, OnDetachFromMainTree)
- NodeContent bidirectional binding

### What Not to Do

- ❌ **Don't create child nodes directly** - Child nodes are created by frontend (ArkTS/Cangjie) through data source
- ❌ **Don't handle rendering logic** - Rendering is handled by child component's own Pattern
- ❌ **Don't implement scrolling logic** - Scrolling is handled by parent container (List/Grid/WaterFlow)
- ❌ **Don't manipulate frontend state directly** - State is synchronized through Model layer and event callbacks
- ❌ **Don't skip base class interfaces** - Must implement all virtual functions specified by ForEachBaseNode

## Architectural Layer Relationships

### Relationship with UINode Base Class

```
UINode (Base Class)
    ├─ IsSyntaxNode() override → true
    └─ Syntax Components
        ├─ ForEachBaseNode (Loop component base class)
        │   ├─ ForEachNode
        │   ├─ RepeatNode
        │   ├─ LazyForEachNode
        │   └─ RepeatVirtualScroll2Node
        ├─ IfElseNode
        ├─ WithThemeNode
        └─ ContentSlotNode
```

**Key Constraints**:
- All syntax nodes must override `IsSyntaxNode()` to return `true`
- ForEachBaseNode provides common interfaces for loop components (MoveData, GetFrameNode, FireOnMove)
- Don't implement visual component logic (such as drawing, event handling) in syntax nodes

### Relationship with Frontend Bridge Layer

**Frontend bridge layer** is the primary caller of Syntax components:

```
ArkTS Frontend (declarative_frontend)
    ↓
ForEachModelNG / LazyForEachModelNG / IfElseModelNG
    ↓
ForEachNode / LazyForEachNode / IfElseNode (C++ Pattern)
```

**Declarative Frontend** (`frameworks/bridge/declarative_frontend/`):
- `jsview/js_for_each.cpp` - ForEach frontend bridge
- `jsview/js_lazy_foreach.cpp` - LazyForEach frontend bridge
- `jsview/js_repeat_virtual_scroll.cpp` - RepeatVirtualScroll frontend bridge
- `jsview/js_if_else.cpp` - IfElse frontend bridge

**CJ Frontend** (`frameworks/bridge/cj_frontend/`):
- `cppview/lazy_foreach.cpp` - LazyForEach Cangjie bridge
- `cppview/if_else.cpp` - IfElse Cangjie bridge

**⚠️ Critical Constraints**:
- Frontend creates and manages syntax nodes through Model layer
- Frontend is responsible for providing data source (IDataSource) and generator functions (itemGen)
- Frontend and C++ layer have unidirectional dependency: Frontend → C++
- Don't call frontend methods directly in C++ layer

### Relationship with Parent Container

**Syntax nodes are typically direct children of parent containers**:

```
List FrameNode (Scroll Container)
    └─ LazyForEachNode (Syntax Node)
        └─ ListItem FrameNode(s) (Created by data source)

or

Column FrameNode
    └─ IfElseNode (Syntax Node)
        └─ User-specified component (branch content)
```

**Separation of Responsibilities**:
- **Parent Container Pattern** (e.g., ListPattern): Handle scrolling, layout calculation, visibility determination
- **Syntax Node Pattern** (e.g., LazyForEachNode): Handle data-driven updates, node reuse, cache management
- **Child Node Pattern** (e.g., ListItemPattern): Handle individual item rendering and interaction

**⚠️ Critical Constraints**:
- Syntax nodes don't directly participate in scrolling logic
- Parent container retrieves child nodes through `GetFrameChildByIndex()`
- Syntax nodes decide whether to return cached nodes or create new ones based on index

### Relationship with Data Source

**LazyForEach and data source interaction**:

```
IDataSource (Frontend Interface)
    ↓
LazyForEachBuilder (C++ Bridge)
    ↓
LazyForEachNode (Syntax Node)
```

**Data source interface** (`V2::IDataSource`):
- `totalCount()` - Total number of data items
- `getData(index)` - Get data at specified index
- `registerDataChangeListener(listener)` - Register data change listener

**⚠️ Critical Constraints**:
- LazyForEachNode interacts with data source through LazyForEachBuilder
- Data source changes are notified through `V2::DataChangeListener` interface
- Don't access frontend data source objects directly in C++ layer

## Behaviors That Must Not Change

### 1. ForEach Differential Algorithm Logic

**Differential algorithm** (must remain consistent):

```cpp
// for_each_node.cpp:91-120
void ForEachNode::CompareAndUpdateChildren()
{
    // 1. Create new and old ID sets for fast lookup
    std::unordered_set<std::string> newIdsSet(ids_.begin(), ids_.end());
    std::unordered_set<std::string> oldIdsSet(tempIds_.begin(), tempIds_.end());

    // 2. Swap new and old child nodes
    std::swap(children, tempChildren_);

    // 3. Remove old nodes not in new ID set
    for (const auto& oldId : tempOldIdsSet_) {
        auto iter = oldNodeByIdMap_.find(oldId);
        if (iter != oldNodeByIdMap_.end()) {
            RemoveChild(iter->second, true);
        }
    }

    // 4. Map child nodes with IDs
    MappingChildWithId(oldIdsSet, additionalChildComps, oldNodeByIdMap_);

    // 5. Add new nodes to children_
    // 6. Update tempIds_, tempChildren_, tempOldIdsSet_
}
```

**Prohibited**:
- ❌ Change differential algorithm basic logic (may cause unnecessary node rebuilds)
- ❌ Skip ID comparison steps
- ❌ Modify timing of `ids_` and `tempIds_` synchronization

### 2. IfElse Branch Switching Flow

**Branch switching flow** (must remain consistent):

```
SetBranchId(newBranchId, removedElmtId, reservedElmtId)
    ↓ (if branchId changed)
Clean(false, true, branchId_)  // Mark old branch children for deletion
    ↓
CollectCleanedChildren(GetChildren(), removedElmtId, reservedElmtId, true)
    ↓
branchId_ = newBranchId  // Update branch ID
    ↓
FlushUpdateAndMarkDirty()
    ↓
FireChangeEvent / FireOnStateChange  // Fire events
    ↓
branchIdChanged_ = false
```

**Prohibited**:
- ❌ Modify branch switching step order
- ❌ Fire events before updating `branchId_`
- ❌ Skip `Clean()` or `CollectCleanedChildren()` steps

### 3. LazyForEach GetFrameChildByIndex Logic

**On-demand rendering logic** (must remain consistent):

```cpp
// lazy_for_each_node.cpp:386-406
RefPtr<UINode> LazyForEachNode::GetFrameChildByIndex(
    uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    if (index >= static_cast<uint32_t>(FrameCount())) {
        return nullptr;  // Out of range
    }

    auto child = builder_->GetChildByIndex(index, needBuild, isCache);
    if (!child.second) {
        return nullptr;  // Build failed
    }

    child.second->UpdateThemeScopeId(GetThemeScopeId());

    if (isCache) {
        // Cache mode: don't add to render tree
        child.second->SetParent(WeakClaim(this));
        child.second->SetJSViewActive(false, true);
        auto childNode = child.second->GetFrameChildByIndex(0, needBuild);
        builder_->ProcessOffscreenNode(childNode, false);
        return childNode;
    }

    // Normal mode: add to render tree
    // ...
}
```

**Prohibited**:
- ❌ Change parameter meanings (such as `needBuild`, `isCache`)
- ❌ Add nodes to render tree when `isCache=true`
- ❌ Return nodes without checking index bounds

### 4. RepeatVirtualScroll Dual-Layer Cache Mechanism

**Cache structure** (must remain consistent):

```
L1 Cache (Active Cache)
├─ l1Rid4Index_: IndexType → RIDType (Index to RID mapping)
└─ Scope: Items in visible range + cache range

L2 Cache (Inactive Cache)
├─ cacheItem4Rid_: RIDType → CacheItem (All cached items)
└─ Scope: Items removed from L1 but retained

CacheItem structure
├─ node_: UINode
├─ isL1_: bool (whether in L1)
├─ isActive_: bool (whether active/visible)
└─ isOnRenderTree_: bool (whether on render tree)
```

**Prohibited**:
- ❌ Change L1/L2 cache definition
- ❌ Keep invisible items in L1
- ❌ Modify `isOnRenderTree_` update timing

### 5. Event Firing Order

**Syntax node events must fire in the following order**:

**ForEach drag events**:
```
FireOnLongPress(index)
    ↓
FireOnDragStart(index)
    ↓
[Dragging...]
    ↓
FireOnMoveThrough(from, through)
    ↓
FireOnDrop(to)
    ↓
MoveData(from, to)  // Update data source
```

**IfElse branch switching events**:
```
SetBranchId() → branchIdChanged_ = true
    ↓
FlushUpdateAndMarkDirty()
    ↓
FireChangeEvent("true"/"false")
    ↓
FireOnStateChange(static_cast<int>(branchId_))
```

**Prohibited**:
- ❌ Change event firing order
- ❌ Fire move complete event before data update
- ❌ Skip intermediate state events

## Common Pitfalls

### 1. ForEach keyGenerator Conflicts

**⚠️ Common Mistakes**:
- ❌ **keyGenerator returns duplicate values**
  - Scenario: Two different data items generate the same key
  - Consequence: Node reuse confusion, incorrect content display

**Correct Approach**:
```typescript
// ❌ Wrong: key may be duplicated
ForEach(this.items, (item) => {
  Text(item.name)  // If name duplicates, key conflicts
})

// ✅ Correct: Use unique ID
ForEach(this.items, (item) => {
  Text(item.name)
}, (item) => item.id)  // Ensure id is unique
```

### 2. LazyForEach Data Source Not Notified

**⚠️ Common Mistakes**:
- ❌ **Modified data source without calling notification method**
  - Scenario: Added element to array but didn't call `notifyDataReloaded()`
  - Consequence: LazyForEach doesn't update display

**Correct Approach**:
```typescript
// ❌ Wrong: Directly modify array
this.items.push(newItem);  // LazyForEach doesn't know

// ✅ Correct: Notify data source changes
this.dataSource.pushData(newItem);
this.dataSource.notifyDataReloaded();  // Must notify
```

### 3. IfElse State Loss

**⚠️ Common Mistakes**:
- ❌ **Child component state lost after branch switch**
  - Scenario: TextInput loses input after branch switch
  - Reason: `TryRetake` mechanism not used correctly

**Correct Approach**:
```typescript
// IfElseNode automatically handles node reuse
// Ensure component ID remains stable

// ❌ Wrong: Dynamically generate keys
@if (this.condition)
  CustomItem({ key: `${Math.random()}` })  // New key every time
}

// ✅ Correct: Use stable keys
@if (this.condition)
  CustomItem({ key: 'stable-key' })
}
```

### 4. RepeatVirtualScroll Cache Not Cleared

**⚠️ Common Mistakes**:
- ❌ **Cached items occupy memory indefinitely**
  - Scenario: L2 cache too large after scrolling lots of data
  - Consequence: Excessive memory usage

**Correct Approach**:
```cpp
// RepeatVirtualScroll2Node clears cache in DoSetActiveChildRange
void RepeatVirtualScroll2Node::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd)
{
    // ... Set active range ...

    // Trigger Purge() to clear items outside cache range
    PostIdleTask();
}
```

### 5. WithTheme Nested Scope Error

**⚠️ Common Mistakes**:
- ❌ **Get wrong theme in nested WithTheme**
  - Scenario: Expect to get inner theme, actually get outer theme
  - Reason: ThemeScopeId update timing is incorrect

**Correct Approach**:
```typescript
// Ensure ThemeScopeId is correctly passed
@Builder
function OuterTheme() {
  WithTheme() {
    InnerTheme()  // Will inherit outer ThemeScopeId
  }
}
```

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// ForEach related logs
TAG_LOGI(AceLogTag::ACE_FOREACH, "ForEach children updated");
TAG_LOGD(AceLogTag::ACE_FOREACH, "ids_.size(): %{public}zu", ids_.size());

// LazyForEach related logs
TAG_LOGI(AceLogTag::ACE_LAZY_FOR_EACH, "LazyForEach data reloaded");
TAG_LOGD(AceLogTag::ACE_LAZY_FOR_EACH, "startIndex: %{public}d, endIndex: %{public}d",
         startIndex_, endIndex_);

// IfElse related logs
TAG_LOGI(AceLogTag::ACE_IF, "IfElse branch changed: %{public}d → %{public}d",
         oldBranchId, newBranchId);

// RepeatVirtualScroll related logs
TAG_LOGD(AceLogTag::ACE_REPEAT, "L1 cache size: %{public}zu, L2 cache size: %{public}zu",
         l1Rid4Index_.size(), cacheItem4Rid_.size());
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (such as `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void ForEachNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("ids_.size()", static_cast<int>(ids_.size()));
    json->Put("tempIds_.size()", static_cast<int>(tempIds_.size()));
    json->Put("children_.size()", static_cast<int>(GetChildren().size()));
    json->Put("isThisRepeatNode_", isThisRepeatNode_ ? "true" : "false");
}

void LazyForEachNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("startIndex_", startIndex_);
    json->Put("endIndex_", endIndex_);
    json->Put("count_", count_);
    json->Put("isActive_", isActive_ ? "true" : "false");
}

void IfElseNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("branchId_", branchId_);
    json->Put("branchIdChanged_", branchIdChanged_ ? "true" : "false");
}
```

### 3. Key Data Structure Checks

**Data structures to check in debugger**:

**ForEachNode**:
```cpp
ids_                      // Current ID list
tempIds_                  // Temporary ID list (for comparison)
tempChildren_             // Temporary child node list
oldNodeByIdMap_           // ID → Node mapping
isThisRepeatNode_         // Whether it's RepeatNode
```

**LazyForEachNode**:
```cpp
ids_                      // Optional key list (std::list<std::optional<std::string>>)
startIndex_               // Start index
endIndex_                 // End index
count_                    // Total count
isActive_                 // Whether active
builder_                  // LazyForEachBuilder instance
```

**RepeatVirtualScroll2Node**:
```cpp
arrLen_                   // Array length
totalCount_               // Total data count (including unloaded)
isActive_                 // Whether active
caches_.l1Rid4Index_       // L1 cache: Index → RID
caches_.cacheItem4Rid_    // All cache: RID → CacheItem
```

**IfElseNode**:
```cpp
branchId_                 // Currently active branch ID
branchIdChanged_          // Whether branch changed
retakenElmtIds_           // List of retaken node IDs
```

### 4. Common Problem Localization

**ForEach Problems**:
- **Problem**: Child nodes not updating
  - Check if `ids_` changed
  - Check if `keyGenerator` returns unique values
  - Check if `tempOldIdsSet_` is correctly cleared

- **Problem**: Display混乱 after drag sort
  - Check if `MoveData()` is called correctly
  - Check if `FireOnMove` event fires
  - Check if data source updated correctly

**LazyForEach Problems**:
- **Problem**: Janky scrolling
  - Check if cache size is reasonable (default 0.5)
  - Check if idle task pre-building is used correctly
  - Check if `GetFrameChildByIndex` frequently creates new nodes

- **Problem**: Data updates not displayed
  - Check if `notifyDataReloaded()` is called
  - Check if `IDataSource`'s `totalCount()` returns correct value
  - Check if data change listener is registered

**RepeatVirtualScroll Problems**:
- **Problem**: White screen during scrolling
  - Check if L1 cache has corresponding index
  - Check if `onGetRid4Index_` callback returns correctly
  - Check if `GetFrameChild` returns `nullptr`

- **Problem**: Excessive memory usage
  - Check L2 cache size
  - Check if `Purge()` triggers normally
  - Check if cached items marked as invalid correctly

**IfElse Problems**:
- **Problem**: State lost after branch switch
  - Check if `TryRetake()` returns `true`
  - Check if `retakenElmtIds_` contains correct nodes
  - Check if child node IDs remain stable

## Special Feature Constraints

### ForEach keyGenerator Constraints

**Purpose of keyGenerator**:
- Generate unique identifier for each data item
- Used by differential algorithm to determine if node can be reused

**⚠️ Constraints**:
```typescript
// keyGenerator must satisfy:
// 1. Always return the same key for the same data item
// 2. Always return different keys for different data items
// 3. Key must be of string type

// ✅ Correct: Use unique ID
ForEach(this.items, (item) => {
  Text(item.name)
}, (item) => item.id.toString())

// ❌ Wrong: Use index as key
ForEach(this.items, (item, index) => {
  Text(item.name)
}, (item, index) => index.toString())  // Index changes
```

### LazyForEach Data Source Interface Constraints

**Methods IDataSource must implement**:
```cpp
class IDataSource {
    virtual int GetTotalCount() = 0;
    virtual std::pair<std::string, RefPtr<NG::UINode>> GetChildByIndex(
        int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) = 0;
    virtual void RegisterDataChangeListener(
        const RefPtr<DataChangeListener>& listener) = 0;
    virtual void UnregisterDataChangeListener(DataChangeListener* listener) = 0;
};
```

**⚠️ Constraints**:
- `GetTotalCount()` must return accurate total count
- `GetChildByIndex()` must be thread-safe
- Must call `listener->OnDataXXX()` methods after data changes

### RepeatVirtualScroll API Version Differences

**API 15 and below**:
- Use `repeat_virtual_scroll_node.cpp`
- Use `repeat_virtual_scroll_caches.cpp`

**API 16+**:
- Use `repeat_virtual_scroll_2_node.cpp`
- Use `repeat_virtual_scroll_2_caches.cpp`

**⚠️ Constraints**:
- Don't mix implementations from two versions
- New features should only be added in API 16+ version

### WithTheme Scope Isolation Rules

**Scope rules**:
```cpp
// ThemeScopeId is passed from parent to child
void WithThemeNode::SetThemeScopeId(int32_t themeScopeId) override
{
    UINode::SetThemeScopeId(themeScopeId);

    // Notify child components to update theme scope
    NotifyThemeScopeUpdate();
}

// Child components use their own ThemeScopeId when getting theme
```

**⚠️ Constraints**:
- Each WithThemeNode must set independent `ThemeScopeId`
- Don't share `ThemeScopeId`
- Must trigger `ThemeScopeDestroyCallback` when destroying

## Performance Constraints

### 1. ForEach Differential Algorithm Performance

**Target**: Differential algorithm should complete within 16ms (1000 items or less)

**Anti-pattern**:
```cpp
// ❌ Expensive operations in differential loop
void ForEachNode::CompareAndUpdateChildren()
{
    for (const auto& id : ids_) {
        // ❌ String comparison every time
        if (id == someOtherId) {  // Slow!
            // ...
        }
    }
}
```

**Correct Approach**:
- Use `std::unordered_set` for O(1) lookup
- Avoid string operations in loops
- Pre-build lookup tables

### 2. LazyForEach Memory Usage

**Constraints**:
- `cachedItems_` cache size defaults to 0.5 * viewportSize
- L2 cache size is controlled by `Purge()`

**Best Practices**:
```cpp
// ✅ Set reasonable cache size
void LazyForEachNode::OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
{
    itemConstraint_ = itemConstraint;
    if (builder_) {
        builder_->SetCacheCount(cacheCount);  // Default ~0.5
    }
}
```

### 3. RepeatVirtualScroll Node Reuse Rate

**Target**: Node reuse rate > 90%

**Check**:
```cpp
// Check L2 cache hit rate
auto hitCount = /* L2 cache hit count */;
auto missCount = /* L2 cache miss count */;
auto hitRate = hitCount / (hitCount + missCount);
// Should be > 0.9
```

### 4. Idle Task Pre-building

**Constraints**:
- Pre-building tasks must complete before deadline
- Typical time budget: 8-12ms

**Best Practices**:
```cpp
void LazyForEachNode::PostIdleTask(std::list<int32_t>&& items,
    const std::optional<LayoutConstraintF>& itemConstraint, bool longPredictTask)
{
    // ...set deadline...

    auto task = [items = std::move(items), itemConstraint,
                weakBuilder = AceType::WeakClaim(builder_)]() mutable {
        auto builder = weakBuilder.Upgrade();
        if (!builder) {
            return;
        }

        // Check deadline
        auto currentTimestamp = GetSysTimestamp();
        if (currentTimestamp > deadline) {
            return;  // Time's up, stop pre-building
        }

        // Pre-building logic
    };

    // Post task
}
```

## Backward Compatibility

### API Version Differences

**RepeatVirtualScroll API 15 vs API 16+**:

| Feature | API 15 | API 16+ |
|---------|--------|---------|
| Cache implementation | `repeat_virtual_scroll_caches.cpp` | `repeat_virtual_scroll_2_caches.cpp` |
| Node | `repeat_virtual_scroll_node.cpp` | `repeat_virtual_scroll_2_node.cpp` |
| Model | `repeat_virtual_scroll_model_ng.cpp` | `repeat_virtual_scroll_2_model_ng.cpp` |

**⚠️ Constraints**:
- Don't break API 15 compatibility
- New features should primarily be implemented in API 16+

### Deprecated But Cannot Remove

Currently no deprecated methods. All public APIs are stable.

### New Method Constraints

- New public methods must consider performance impact
- Don't change default behavior of existing methods
- If behavior needs to change, add new properties to control it
- Maintain backward compatibility

## Summary

**Core Principles**:
1. **Syntax nodes are control flow nodes, not visual nodes** - Don't implement rendering, drawing, or other visual logic
2. **Data-driven updates are core** - Drive node updates through keys and data sources
3. **Differential algorithm must be accurate** - Incorrect differential will cause unnecessary node rebuilds
4. **Cache strategy should be reasonable** - Balance memory usage and performance
5. **Event order must not be chaotic** - Follow framework-defined event firing order
6. **API compatibility is important** - Don't break existing ArkTS code

**Remember**: This is framework core code, any modification may affect upper-layer applications. Before modifying:
- Understand existing data flow and control flow
- Confirm won't break API compatibility
- Consider performance impact (memory + CPU)
- Add corresponding test cases
- Test large dataset scenarios (10000+ items)

**Testing Checklist**:
- [ ] ForEach differential algorithm correctness (add, delete, change, move)
- [ ] LazyForEach data source listening works correctly
- [ ] RepeatVirtualScroll virtual scrolling is smooth (60 FPS)
- [ ] IfElse branch switching maintains state
- [ ] Drag sorting functionality works correctly
- [ ] Memory usage is reasonable (large dataset scenarios)
- [ ] API version compatibility

**Related Documentation**:
- [docs/syntax/Syntax_Architecture_Overview.md](docs/syntax/Syntax_Architecture_Overview.md) - Syntax module architecture overview
- [docs/syntax/ForEach_Knowledge_Base.md](docs/syntax/ForEach_Knowledge_Base.md) - ForEach 组件知识库
- [docs/syntax/LazyForEach_Knowledge_Base.md](docs/syntax/LazyForEach_Knowledge_Base.md) - LazyForEach 组件知识库
- [docs/syntax/Repeat_Knowledge_Base.md](docs/syntax/Repeat_Knowledge_Base.md) - Repeat 组件知识库
- [docs/syntax/RepeatVirtualScroll_Knowledge_Base.md](docs/syntax/RepeatVirtualScroll_Knowledge_Base.md) - RepeatVirtualScroll 组件知识库
- [docs/syntax/Conditional_Rendering_Guide.md](docs/syntax/Conditional_Rendering_Guide.md) - Conditional rendering专题
- [docs/syntax/Special_Syntax_Components.md](docs/syntax/Special_Syntax_Components.md) - Special syntax components专题
