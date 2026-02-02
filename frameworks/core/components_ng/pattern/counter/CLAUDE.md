# Counter Pattern Subdirectory Rules

This document contains specialized rules for the Counter Pattern directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Responsibility Boundaries

### Core Responsibilities

**CounterPattern** is the core logic layer for counter components, responsible for:

1. **Child Node ID Management**
   - Manage unique IDs for three child nodes (sub, content, add)
   - Provide accessors: `GetSubId()`, `GetContentId()`, `GetAddId()`
   - Create IDs on-demand using `ElementRegister::MakeUniqueId()`

2. **Layout Algorithm Coordination**
   - Create `CounterLayoutAlgorithm` instances (in `CreateLayoutAlgorithm()`)
   - Create `CounterLayoutProperty` instances (in `CreateLayoutProperty()`)

3. **Theme Update Handling**
   - Respond to color configuration changes (`OnColorConfigurationUpdate()`)
   - Update button and text styles through theme system

### What Not to Do

- ❌ **Don't create child nodes directly** - Child nodes are created in `MarqueeModelNG::Create()`
- ❌ **Don't manage button state directly** - Button state managed through `ButtonEventHub`
- ❌ **Don't handle value storage** - Counter doesn't store value, managed externally
- ❌ **Don't handle rendering directly** - Rendering handled by Button and Text patterns

## Architectural Layer Relationships

### Relationship with LinearLayoutPattern Base Class

```
LinearLayoutPattern (Base Class)
    └─ CounterPattern (Derived Class)
        ├─ Child Node ID Management
        ├─ Layout Algorithm Creation
        └─ Theme Update Handling
```

**Key Constraints**:
- CounterPattern inherits layout logic from LinearLayoutPattern
- Don't duplicate layout logic already in base class
- Follow lifecycle method call order defined by base class

### Relationship with Child Nodes

**Child Node Structure**:
```
Counter FrameNode
    ├─ Button FrameNode (decrement button, index = 0)
    ├─ Text FrameNode (content display, index = 1)
    └─ Button FrameNode (increment button, index = 2)
```

**Node Index Constants**:
```cpp
constexpr int32_t SUB_BUTTON = 0;   // Decrement button
constexpr int32_t CONTENT = 1;      // Content area
constexpr int32_t ADD_BUTTON = 2;   // Increment button
```

**Separation of Responsibilities**:
- **CounterPattern**: Manage node IDs, create layout algorithm
- **ButtonPattern**: Handle button rendering, events, states
- **TextPattern**: Handle text rendering, font styling

**⚠️ Critical Constraints**:
- CounterPattern accesses child nodes through `GetChildAtIndex(id)`
- Don't access ButtonPattern or TextPattern methods directly
- Use properties (ButtonEventHub, TextLayoutProperty) to update child nodes

### Relationship with CounterLayoutAlgorithm

**Data Flow**:
```
Pattern (Business Logic Layer)
    ├─ Node ID management (subId_, contentId_, addId_)
    └─ Layout algorithm creation
         ↓
LayoutAlgorithm (Layout Calculation Layer)
    ├─ Measure (measure three child nodes)
    ├─ Layout (layout buttons and content)
    └─ LayoutItem (handle RTL/LTR direction)
```

**⚠️ Critical Constraints**:
- LayoutAlgorithm determines button order based on layout direction
- Pattern doesn't control button positioning directly
- LayoutAlgorithm handles text alignment automatically

### Relationship with Model

**Model Layer** (`counter_model_ng.h`):
- Provides ArkTS/TS declarative APIs
- Creates Counter FrameNode and three child nodes
- Manages property settings (height, width, backgroundColor, enableInc, enableDec)
- Registers event callbacks (onInc, onDec)

**Pattern Layer**:
- Provides node ID accessors
- Creates layout algorithm and property objects
- Not directly exposed to developers

**⚠️ Critical Constraints**:
- Don't call Model methods directly in Pattern
- Model and Pattern have unidirectional dependency: Model → Pattern

## Behaviors That Must Not Change

### 1. Node Index Constants

**Node indices must remain stable**:
```cpp
constexpr int32_t SUB_BUTTON = 0;   // Always decrement button
constexpr int32_t CONTENT = 1;      // Always content text
constexpr int32_t ADD_BUTTON = 2;   // Always increment button
```

**Prohibited**:
- ❌ Change node indices (e.g., swap SUB_BUTTON and ADD_BUTTON)
- ❌ Add additional child nodes (must be exactly 3)
- ❌ Modify child order in creation (must be: sub → content → add)

### 2. Button Disabled Visual Effect

**Disabled Opacity** (must remain consistent):
```cpp
constexpr double BUTTON_ALPHA_DISABLED = 0.4;
```

**Implementation**:
```cpp
void SetEnableInc(bool enableInc)
{
    auto eventHub = addNode->GetEventHub<ButtonEventHub>();
    eventHub->SetEnabled(enableInc);

    auto renderContext = addNode->GetRenderContext();
    if (!eventHub->IsEnabled()) {
        renderContext->UpdateOpacity(BUTTON_ALPHA_DISABLED); // 0.4
    } else {
        renderContext->UpdateOpacity(1.0);
    }
}
```

**Prohibited**:
- ❌ Change disabled opacity value (0.4)
- ❌ Use other visual indicators for disabled state
- ❌ Disable opacity animation (must be immediate)

### 3. RTL/LTR Layout Behavior

**Layout Direction Handling** (must remain consistent):
```cpp
void CounterLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();

    if (layoutDirection == TextDirection::RTL) {
        // RTL: increment on left, decrement on right
        LayoutItem(layoutWrapper, ADD_BUTTON, SUB_BUTTON);
    } else {
        // LTR: decrement on left, increment on right (default)
        LayoutItem(layoutWrapper, SUB_BUTTON, ADD_BUTTON);
    }
}
```

**Layout Comparison**:
```
LTR (default):
┌─────┬────────────┬─────┐
│  -  │   Content   │  +  │
└─────┴────────────┴─────┘

RTL:
┌─────┬────────────┬─────┐
│  +  │   Content   │  -  │
└─────┴────────────┴─────┘
```

**Prohibited**:
- ❌ Change button order for RTL
- ❌ Ignore layout direction when positioning buttons
- ❌ Manually override RTL layout logic

### 4. Node ID Generation Timing

**ID Generation** (must be consistent):
```cpp
int32_t CounterPattern::GetSubId()
{
    if (!subId_.has_value()) {
        subId_ = ElementRegister::GetInstance()->MakeUniqueId();
    }
    return subId_.value();
}
```

**⚠️ Constraints**:
- IDs are generated lazily on first access
- IDs must be unique across the application
- Once generated, ID must not change during component lifecycle

**Prohibited**:
- ❌ Regenerate IDs during component lifetime
- ❌ Use hardcoded or predictable IDs
- ❌ Share IDs between different Counter instances

## Common Pitfalls

### 1. Accessing Child Nodes Before Creation

**⚠️ Common Mistakes**:
- ❌ **Calling GetSubId() before child nodes are created**
  - Scenario: Pattern tries to access button ID in constructor
  - Consequence: Returns invalid or uninitialized ID

**Correct Approach**:
```cpp
void CounterModelNG::Create()
{
    // 1. Create Counter node
    auto counterNode = CounterNode::GetOrCreateCounterNode(...);

    // 2. Create three child nodes in order
    auto subNode = FrameNode::CreateFrameNode(...);
    counterNode->AddChild(subNode);

    auto textNode = FrameNode::CreateFrameNode(...);
    counterNode->AddChild(textNode);

    auto addNode = FrameNode::CreateFrameNode(...);
    counterNode->AddChild(addNode);

    // 3. Now pattern can access IDs
    auto pattern = counterNode->GetPattern<CounterPattern>();
    auto subId = pattern->GetSubId();  // Valid
}
```

### 2. Modifying Child Node State Without Checking Existence

**⚠️ Common Mistakes**:
- ❌ **Access child node without null check**
  - Scenario: Call `GetChildAtIndex(GetSubId())` without verifying node exists
  - Consequence: Null pointer dereference, crash

**Correct Approach**:
```cpp
auto pattern = frameNode->GetPattern<CounterPattern>();
CHECK_NULL_VOID(pattern);

auto subId = pattern->GetSubId();
auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(subId));
CHECK_NULL_RETURN(subNode, void());

// Now safe to use subNode
auto eventHub = subNode->GetEventHub<ButtonEventHub>();
```

### 3. Forgetting to Update All Child Nodes When Size Changes

**⚠️ Common Mistakes**:
- ❌ **Set height on Counter but forget to update child nodes**
  - Scenario: Call `SetHeight(40)` but buttons remain old height
  - Consequence: Child nodes inconsistent with container

**Correct Approach**:
```cpp
void CounterModelNG::SetHeight(const Dimension& value)
{
    auto layoutProperty = frameNode->GetLayoutProperty<CounterLayoutProperty>();
    layoutProperty->SetHeight(value);

    // Update all child nodes
    auto pattern = frameNode->GetPattern<CounterPattern>();
    UpdateChildHeight(pattern->GetSubId(), value);
    UpdateChildHeight(pattern->GetContentId(), value);
    UpdateChildHeight(pattern->GetAddId(), value);
}
```

### 4. Confusing ControlWidth Property

**⚠️ Common Mistakes**:
- ❌ **Assuming controlWidth actually works**
  - Reality: `SetControlWidth()` exists but is not implemented
  - Consequence: Setting this property has no effect

**Current Status**:
```cpp
// controlWidth property exists but is not used
// Control button width is determined by theme, not this property
void CounterModelNG::SetControlWidth(const Dimension& value)
{
    // Property is stored but not applied to buttons
}
```

**Workaround**:
- Customize button width through theme system
- Or modify button nodes directly after creation

### 5. Value Management Confusion

**⚠️ Common Mistakes**:
- ❌ **Assuming Counter stores the value**
  - Reality: Counter doesn't store value, only displays it
  - Consequence: Value changes don't persist without external state

**Correct Pattern**:
```typescript
@State value: number = 0  // External state management

Counter()
  .onInc(() => {
    this.value++  // Update external state
  })
  .onDec(() => {
    this.value--
  })

Text(`Value: ${this.value}`)  // Display external state
```

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// Counter related logs
TAG_LOGI(AceLogTag::ACE_COUNTER, "Counter created with id: %{public}d", nodeId);
TAG_LOGD(AceLogTag::ACE_COUNTER, "Sub button id: %{public}d", subId_);

// Button state logs
TAG_LOGI(AceLogTag::ACE_COUNTER, "Enable Inc: %{public}d", enableInc);
TAG_LOGI(AceLogTag::ACE_COUNTER, "Enable Dec: %{public}d", enableDec);
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void CounterPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("hasSubNode", HasSubNode());
    json->Put("subId", subId_.value_or(-1));
    json->Put("contentId", contentId_.value_or(-1));
    json->Put("addId", addId_.value_or(-1));
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Pattern state
subId_                   // Decrement button ID
contentId_               // Content area ID
addId_                   // Increment button ID

// PaintProperty state
enableInc_                // Increment button enabled
enableDec_                // Decrement button enabled
height_                  // Counter height
width_                   // Counter width
backgroundColor_         // Background color
```

### 4. Common Problem Localization

**Problem: Button clicks not responding**
- Check if event callbacks are registered (onInc/onDec)
- Check if buttons are disabled (enableInc/enableDec)
- Verify child nodes exist before accessing

**Problem: Child nodes not visible**
- Check if Counter has explicit width/height set
- Verify child nodes were created in correct order
- Check if layout algorithm executed correctly

**Problem: Button state not updating**
- Verify opacity is updated (0.4 for disabled, 1.0 for enabled)
- Check if ButtonEventHub::SetEnabled() was called
- Confirm render context is updated with new opacity

## Special Feature Constraints

### Button Disabled State

**Visual Implementation**:
```cpp
// Disabled state shows as semi-transparent (40% opacity)
renderContext->UpdateOpacity(0.4);
```

**Interaction Constraints**:
- Disabled buttons don't respond to clicks
- Disabled buttons don't show hover effects
- Disabled buttons don't show focus rings

**Prohibited**:
- ❌ Change disabled opacity to other values
- ❌ Add additional visual effects for disabled state
- ❌ Allow disabled buttons to trigger events

### Value Range Limiting

**Implementation Pattern** (external state management):
```typescript
@State value: number = 5
private min: number = 0
private max: number = 10

Counter()
  .enableInc(this.value < this.max)  // Disable when at max
  .enableDec(this.value > this.min)  // Disable when at min
  .onInc(() => {
    if (this.value < this.max) {
      this.value++
    }
  })
  .onDec(() => {
    if (this.value > this.min) {
      this.value--
    }
  })
```

**⚠️ Constraints**:
- Counter component doesn't enforce min/max limits
- Must be enforced externally through enableInc/enableDec
- Component provides mechanisms but not enforcement logic

### Background Color Customization

**Implementation**:
```cpp
void CounterModelNG::SetBackgroundColor(const Color& value)
{
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(value);
    renderContext->UpdateBackgroundFlag(true);
}
```

**Scope**:
- Background color applies to entire Counter container
- Does NOT affect individual buttons
- Buttons use their own theme colors

## Performance Constraints

### 1. Avoid Frequent Child Node Access

**Anti-pattern**:
```cpp
// ❌ Access child nodes repeatedly in loop
for (int i = 0; i < 1000; i++) {
    auto subId = pattern->GetSubId();
    auto subNode = frameNode->GetChildAtIndex(subId);
    // ... operate on subNode
}
```

**Correct Approach**:
```cpp
// ✅ Cache child node references
auto subId = pattern->GetSubId();
auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(subId));

for (int i = 0; i < 1000; i++) {
    // ... operate on cached subNode
}
```

### 2. Minimize Layout Triggers

**Best Practices**:
- Batch multiple property changes before triggering layout
- Use `MarkDirtyNode()` only when necessary
- Avoid modifying properties in event callbacks that trigger layout

**Anti-pattern**:
```cpp
// ❌ Trigger layout in event callback
.onInc(() => {
  this.value++
  this.height = 40 + this.value  // Triggers layout every click
})
```

### 3. Efficient Event Handler Registration

**Best Practice**:
```cpp
// ✅ Register event once during creation
void CounterModelNG::SetOnInc(CounterEventFunc&& onInc)
{
    auto addId = pattern->GetAddId();
    auto addNode = frameNode->GetChildAtIndex(addId);
    auto eventHub = addNode->GetEventHub<GestureEventHub>();
    eventHub->SetUserOnClick(std::move(onInc));  // Move once
}
```

## Backward Compatibility

### Deprecated But Cannot Remove Methods

None currently deprecated. All public APIs are stable.

### New Method Constraints

- New public methods must consider impact on existing button behaviors
- Don't change default appearance of buttons (theme controls this)
- If behavior needs to change, add new properties to control it

## Summary

**Core Principles**:
1. **Three nodes structure is fixed** - Must be exactly 3 children in specific order
2. **Node IDs are unique and stable** - Generate once, use throughout lifecycle
3. **Value is externally managed** - Counter displays value but doesn't store it
4. **Disabled state must be visual** - Use opacity (0.4) to indicate disabled
5. **RTL layout is automatic** - Detect and adapt to text direction

**Remember**: This is framework core code, any modification may affect upper-layer applications. Before modifying:
- Understand existing data flow
- Confirm won't break API compatibility
- Consider performance impact
- Add corresponding test cases
