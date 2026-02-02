# Marquee Pattern Subdirectory Rules

This document contains specialized rules for the Marquee Pattern directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Responsibility Boundaries

### Core Responsibilities

**MarqueePattern** is the core logic layer for marquee components, responsible for:

1. **Text Child Node Management**
   - Create and manage Text FrameNode as child node
   - Update text content and styles through TextLayoutProperty
   - Handle text direction detection (RTL/LTR)

2. **Animation Control**
   - Start/stop scroll animation (`StartMarqueeAnimation()`, `StopMarqueeAnimation()`)
   - Pause/resume animation (`PauseAnimation()`, `ResumeAnimation()`)
   - Calculate scroll position, distance, and duration
   - Update text translation during animation

3. **Event Handling**
   - Fire scroll events (`FireStartEvent()`, `FireBounceEvent()`, `FireFinishEvent()`)
   - Register event callbacks through MarqueeEventHub

4. **Visibility Management**
   - Auto-pause animation when component not visible (`OnVisibleAreaChange()`)
   - Auto-resume when component becomes visible

### What Not to Do

- ❌ **Don't handle rendering directly** - Rendering is handled by Text Pattern
- ❌ **Don't handle gesture recognition** - Gestures are inherited from base Pattern
- ❌ **Don't create Text node manually** - Text node is created in `MarqueeModelNG::Create()`
- ❌ **Don't manage animation timing manually** - Use framework animation system

## Architectural Layer Relationships

### Relationship with LinearLayoutPattern Base Class

```
LinearLayoutPattern (Base Class)
    └─ MarqueePattern (Derived Class)
        ├─ Text Node Management
        ├─ Animation Control
        └─ Event Firing
```

**Key Constraints**:
- MarqueePattern inherits layout logic from LinearLayoutPattern
- Don't duplicate layout logic already in base class
- Follow lifecycle method call order defined by base class

### Relationship with Text Child Node

**Child Node Structure**:
```
Marquee FrameNode
    └─ Text FrameNode (child node)
        └─ TextPattern (handles text rendering)
```

**Separation of Responsibilities**:
- **MarqueePattern**: Manage animation, events, visibility
- **TextPattern**: Handle text measurement, rendering, font styling

**⚠️ Critical Constraints**:
- MarqueePattern accesses Text node through `GetFirstChild()` or `GetChildAtIndex()`
- Don't access TextPattern methods directly
- Use TextLayoutProperty to update text styles (fontSize, fontColor, etc.)

### Relationship with MarqueeLayoutAlgorithm

**Data Flow**:
```
Pattern (Business Logic Layer)
    ├─ Animation state (playStatus, step, loop)
    ├─ Marquee width tracking (marqueeWidth_)
    └─ Text direction management (GetTextDirection)
         ↓
LayoutAlgorithm (Layout Calculation Layer)
    ├─ Measure (measure text with infinite width)
    ├─ Layout (position text based on direction)
    └─ GetMeasureAdaptiveHeight (calculate adaptive height)
```

**⚠️ Critical Constraints**:
- LayoutAlgorithm should not directly access Pattern's animation state
- Don't trigger animation in LayoutAlgorithm
- Pattern receives layout results in `OnDirtyLayoutWrapperSwap()`

### Relationship with Model

**Model Layer** (`marquee_model_ng.h`):
- Provides ArkTS/TS declarative APIs
- Creates Marquee FrameNode and Text child node
- Manages property settings (src, start, step, loop, fontSize, etc.)

**Pattern Layer**:
- Implements animation logic
- Responds to Model property changes (through `OnModifyDone()`)
- Not directly exposed to developers

**⚠️ Critical Constraints**:
- Don't call Model methods directly in Pattern
- Model and Pattern have unidirectional dependency: Model → Pattern

## Behaviors That Must Not Change

### 1. Animation Parameter Calculation

**Scroll Distance Formula** (must remain consistent):
```cpp
scrollDistance = textWidth + marqueeWidth
```

**Animation Duration Formula** (must remain consistent):
```cpp
duration = (distance / step) * DEFAULT_DELAY
// where DEFAULT_DELAY = 85.0f (milliseconds per pixel)
```

**Prohibited**:
- ❌ Change `DEFAULT_MARQUEE_SCROLL_AMOUNT` default value (6.0)
- ❌ Change distance calculation method
- ❌ Modify duration formula without considering performance impact

### 2. Event Firing Order

Marquee events must be fired in the following order:

```
StartMarqueeAnimation
    ↓
FireStartEvent()
    ↓
Animation playing...
    ↓
Text reaches edge
    ↓
FireBounceEvent()
    ↓
Animation completes
    ↓
FireFinishEvent()
```

**Prohibited**:
- ❌ Change event firing order
- ❌ Fire FinishEvent before animation completes
- ❌ Skip BounceEvent when text reaches edge

### 3. Text Direction Handling

**RTL Detection Logic** (must remain consistent):
```cpp
bool IsRTLText(const std::string& content)
{
    if (content.empty()) return false;
    return content[0] == 0x0591 || content[0] == 0x0592;
}
```

**Layout Behavior**:
- **LTR text**: Left align, scroll right to left (default)
- **RTL text**: Right align, scroll left to right

**Prohibited**:
- ❌ Change RTL detection logic
- ❌ Modify alignment rules for text directions
- ❌ Ignore text direction when setting `direction` property

### 4. Visibility Auto-Pause

**Behavior Specification**:
```cpp
void MarqueePattern::OnVisibleAreaChange(bool isVisible)
{
    if (isVisible) {
        ResumeAnimation();
    } else {
        PauseAnimation();
    }
}
```

**Prohibited**:
- ❌ Change auto-pause behavior (e.g., continue playing when invisible)
- ❌ Pause without checking if animation is running
- ❌ Skip resume when component becomes visible

## Common Pitfalls

### 1. Text Width Not Greater Than Marquee Width

**⚠️ Common Mistakes**:
- ❌ **Animation starts even when text fits in Marquee**
  - Scenario: Text width is 50px, Marquee width is 200px
  - Consequence: Wasted CPU resources, unnecessary animation

**Correct Approach**:
```cpp
bool MarqueePattern::IsRunMarquee()
{
    auto textWidth = textNode_->GetGeometryNode()->GetMarginFrameSize().Width();
    auto marqueeWidth = marqueeWidth_;

    // Only scroll if text is wider than marquee
    return textWidth > marqueeWidth;
}
```

**Usage**:
```cpp
void MarqueePattern::StartMarqueeAnimation()
{
    if (!IsRunMarquee()) {
        UpdateTextTranslateXY(0.0f);
        StopAndResetAnimation();
        return;
    }
    // ... start animation
}
```

### 2. Animation State Inconsistency

**⚠️ Common Mistakes**:
- ❌ **Modified `playerStatus` but animation doesn't update**
  - Scenario: Set `playerStatus = true` but animation doesn't start
  - Consequence: User sees no scrolling despite "start" being true

**Root Cause**:
- `OnModifyDone()` only checks `OnlyPlayStatusChange()`
- Layout size changes are not handled

**Correct Approach**:
```cpp
void MarqueePattern::OnModifyDone()
{
    // ... property updates

    if (CheckMeasureFlag() || CheckLayoutFlag()) {
        measureChanged_ = true;
    } else if (OnlyPlayStatusChange()) {
        ChangeAnimationPlayStatus();
    } else {
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }
}
```

### 3. Marquee Width Tracking

**⚠️ Common Mistakes**:
- ❌ **Forgot to update `marqueeWidth_` when size changes**
  - Scenario: Marquee resized from 200px to 300px
  - Consequence: Animation duration calculation uses old width

**Correct Approach**:
```cpp
bool MarqueePattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto geoNode = host->GetGeometryNode();
    auto marqueeWidth = geoNode->GetFrameSize().Width();

    if (measureChanged_ || marqueeWidth_ != marqueeWidth) {
        measureChanged_ = true;
        auto playStatus = paintProperty->GetPlayerStatus().value_or(false);
        StopMarqueeAnimation(playStatus);
    }

    marqueeWidth_ = marqueeWidth;  // Always update
    return false;
}
```

### 4. Loop Count Handling

**⚠️ Common Mistakes**:
- ❌ **Misunderstanding loop count semantics**
  - Wrong: `loop = 0` means no loop (correct)
  - Wrong: `loop = -1` means play once (incorrect, -1 means infinite)

**Correct Semantics**:
```cpp
// -1: Infinite loop
//  0: No loop (play once)
// >0: Loop specified times
```

**Implementation**:
```cpp
void MarqueePattern::PlayMarqueeAnimation(float start, int32_t repeatCount, bool needSecondPlay)
{
    // repeatCount = -1 means infinite loop
    if (repeatCount == -1) {
        animation->SetIterationCount(ANIMATION_REPEAT_INFINITE);
    } else {
        animation->SetIterationCount(repeatCount);
    }
}
```

### 5. Step Value Impact on Duration

**⚠️ Common Mistakes**:
- ❌ **Assuming larger step = faster animation**
  - Reality: Larger step = shorter duration (faster)
  - Formula: `duration = (distance / step) * DEFAULT_DELAY`

**Correct Understanding**:
- `step = 6`: Default speed
- `step = 12`: 2x faster (duration halved)
- `step = 3`: 0.5x speed (duration doubled)

**Range Constraints**:
```cpp
constexpr double DEFAULT_MARQUEE_SCROLL_AMOUNT = 6.0;
```

## Debugging Methods

### 1. Logging Macros

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// Marquee related logs
TAG_LOGI(AceLogTag::ACE_MARQUEE, "Marquee src: %{public}s", src.c_str());
TAG_LOGD(AceLogTag::ACE_MARQUEE, "step: %{public}f, loop: %{public}d", step, loop);

// Animation related logs
TAG_LOGD(AceLogTag::ACE_ANIMATION, "Animation duration: %{public}f", duration);
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void MarqueePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MarqueePaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    json->Put("src", layoutProperty->GetSrc().value_or("").c_str());
    json->Put("playerStatus", paintProperty->GetPlayerStatus().value_or(false) ? "true" : "false");
    json->Put("scrollAmount", paintProperty->GetScrollAmount().value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT));
    json->Put("loop", paintProperty->GetLoop().value_or(DEFAULT_MARQUEE_LOOP));
    json->Put("marqueeWidth", marqueeWidth_);
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Pattern state
marqueeWidth_             // Marquee width (in pixels)
measureChanged_          // Whether layout size changed
lastAnimationParam_      // Last animation parameters

// PaintProperty state
playerStatus_             // Play status (true/false)
scrollAmount_            // Scroll step (pixels/frame)
loop_                    // Loop count (-1 = infinite)

// Text node state
textWidth_               // Text content width (if cached)
textDirection_           // Text direction (RTL/LTR)
```

### 4. Common Problem Localization

**Problem: Text not scrolling**
- Check if `playerStatus` is true
- Check if text width > marquee width
- Check if `IsRunMarquee()` returns true
- Check if animation was created and started

**Problem: Animation speed abnormal**
- Check if `scrollAmount` is within reasonable range (1.0 - 100.0)
- Check if distance calculation is correct
- Verify `DEFAULT_MARQUEE_SCROLL_DELAY` constant

**Problem: Events not firing**
- Check if event callbacks registered in Model
- Check if `FireStartEvent()` is called
- Verify loop count allows event to fire (loop > 0 or -1)

## Special Feature Constraints

### Text Direction Auto-Detection

**Detection Method**:
```cpp
TextDirection GetTextDirection(const std::string& content, MarqueeDirection direction)
{
    if (!content.empty() && (content[0] == 0x0591 || content[0] == 0x0592)) {
        return TextDirection::RTL;
    }
    return TextDirection::LTR;
}
```

**⚠️ Constraints**:
- Only checks first character of content
- Valid Unicode code points: 0x0591 (HEBREW LETTER ֹ), 0x0592 (HEBREW LETTER ּ)
- For production, consider more robust RTL detection

### Scroll Direction vs Text Direction

**Important Distinction**:
- **Scroll Direction** (`MarqueeDirection`): User-specified scroll direction
- **Text Direction** (RTL/LTR): Automatic based on content

**Interaction Matrix**:
```
User Direction | Text Direction | Actual Scroll Direction
---------------|---------------|----------------------
LEFT (default) | LTR           | Right to Left
LEFT (default) | RTL           | Right to Left
RIGHT          | LTR           | Left to Right
RIGHT          | RTL           | Left to Right
```

**⚠️ Constraint**: Text direction affects alignment, not scroll direction

### Visibility Auto-Pause

**Enable Condition**: Always enabled by default

**Behavior Specification**:
- Component scrolled off screen → Pause animation
- Component scrolled into view → Resume animation
- Save animation state when pausing (current position)

**Performance Benefit**:
- Saves CPU resources when not visible
- Reduces battery consumption
- Improves overall system performance

## Performance Constraints

### 1. Animation Frame Rate

**Target**: 60 FPS (frames per second)

**Anti-pattern**:
```cpp
// ❌ Update text position too frequently
void MarqueePattern::UpdateTextTranslateXY(float position)
{
    // Called every frame (60 times per second)
    // Expensive operations here cause frame drops
    auto str = ContentToString();  // Expensive string operation
}
```

**Correct Approach**:
- Keep animation loop lightweight
- Avoid expensive operations in animation callback
- Pre-calculate values when possible

### 2. Text Measurement Frequency

**⚠️ Constraint**:
- Text measurement is expensive
- Don't measure text on every animation frame
- Cache text width and only remeasure when content changes

**Correct Timing**:
```cpp
void MarqueePattern::OnModifyDone()
{
    auto content = layoutProperty->GetSrc().value_or("");
    if (content != lastContent_) {
        // Content changed, remeasure will happen in next layout
        lastContent_ = content;
        measureChanged_ = true;
    }
}
```

### 3. Animation Resource Management

**Best Practices**:
```cpp
// ✅ Reuse animation controller
if (!animator_) {
    animator_ = AceType::MakeRefPtr<Animator>();
}

// ❌ Don't create new animator for every animation
// auto animator = AceType::MakeRefPtr<Animator>();  // Wrong
```

## Backward Compatibility

### Deprecated But Cannot Remove Methods

None currently deprecated. All public APIs are stable.

### New Method Constraints

- New public methods must consider impact on existing animations
- Don't change default behavior of existing properties
- If behavior needs to change, add new properties to control it

## Summary

**Core Principles**:
1. **Text node is child, not managed by MarqueePattern** - Text creation/deletion handled by Model
2. **Animation state must be consistent** - Keep Pattern ↔ LayoutAlgorithm data flow clear
3. **Visibility auto-pause is mandatory** - Always implement for performance
4. **Event order must be preserved** - Observe Start → Bounce → Finish sequence
5. **Text direction detection must be robust** - Handle RTL/LTR correctly

**Remember**: This is framework core code, any modification may affect upper-layer applications. Before modifying:
- Understand existing data flow
- Confirm won't break API compatibility
- Consider performance impact
- Add corresponding test cases
