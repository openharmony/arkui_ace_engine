# TextTimer Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the TextTimer component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [TextTimer_Knowledge_Base_CN.md](../../../docs/pattern/texttimer/TextTimer_Knowledge_Base_CN.md)

---

## Overview

**TextTimer** is a text timer component used for displaying elapsed time. It supports both stopwatch (count up) and countdown (count down) modes.

**Architecture**: NG Pattern → TextTimerPattern → TextTimerLayoutAlgorithm (BoxLayoutAlgorithm)

**Key Features**:
- Two timer modes: Count up (stopwatch) and Count down (countdown)
- Customizable format (HH:mm:ss.SS, etc.)
- Controller support (start, pause, reset)
- Font style customization (size, color, weight, family)
- Visible area optimization (pauses when not visible)
- ContentModifier support
- System color configuration updates

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `text_timer_pattern.h/cpp` | ~160 (h) / ~430 (cpp) | Pattern layer - business logic, controller, scheduler |
| `text_timer_model_ng.h/cpp` | ~60 (h) / ~150 (cpp) | Frontend bridge - Create(), property setters |
| `text_timer_layout_property.h` | ~90 | Timer properties (Format, IsCountDown, InputCount) |
| `text_timer_event_hub.h` | ~30 | Timer event (onTimer) |
| `texttimer_controller.h` | ~50 | Controller (start, pause, reset) |

**Path**: `frameworks/core/components_ng/pattern/texttimer/`

---

## Core Class Hierarchy

```
                    Pattern
                       ↑
                TextTimerPattern
                (text_timer_pattern.h:37)
                       |
        +--------------+--------------+
        |              |              |
  LayoutProperty  LayoutAlgorithm  AccessibilityProperty
        ↑              ↑                    ↑
TextTimerLayoutProperty  TextTimerLayoutAlgorithm  TextTimerAccessibilityProperty
        |
TextLayoutProperty (inherits)
```

---

## Key Properties

### Timer Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `Format` | string | "HH:mm:ss.SS" | Time format string |
| `IsCountDown` | bool | false | Countdown mode (true) or stopwatch mode (false) |
| `InputCount` | double | 60000.0 | Timer count value in milliseconds |

### Font Style Properties (inherited from TextLayoutProperty)

| Property | Type | Description |
|----------|------|-------------|
| `FontSize` | Dimension | Font size |
| `TextColor` | Color | Text color |
| `FontWeight` | FontWeight | Font weight |
| `FontFamily` | vector\<string\> | Font family |
| `ItalicFontStyle` | FontStyle | Italic style |
| `TextShadow` | vector\<Shadow\> | Text shadow |

**User Set Flags**: `TextColorSetByUser`, `TextFontSizeSetByUser`, `TextFontWeightSetByUser`, `TextFontFamilySetByUser` - prevent theme updates from overriding user values

---

## Time Format Characters

| Character | Description | Example |
|-----------|-------------|---------|
| `H` | Hours | 01, 12 |
| `h` | Hours (no leading zero) | 1, 12 |
| `m` | Minutes | 00-59 |
| `s` | Seconds | 00-59 |
| `S` | Centiseconds | 00-99 |
| `SS` | Centiseconds | 00-99 |
| `SSS` | Milliseconds | 000-999 |

---

## Common Operations

### Setting Timer Mode

```cpp
// Stopwatch mode (count up from 0)
layoutProperty->UpdateIsCountDown(false);

// Countdown mode (count down to 0)
layoutProperty->UpdateIsCountDown(true);
layoutProperty->UpdateInputCount(60000.0);  // 60 seconds
```

### Setting Timer Format

```cpp
// Hours:Minutes:Seconds:Centiseconds
layoutProperty->UpdateFormat("HH:mm:ss.SS");

// Minutes:Seconds
layoutProperty->UpdateFormat("mm:ss");

// Seconds only
layoutProperty->UpdateFormat("s");
```

### Using Controller

```cpp
// Start timer
textTimerController_->Start();

// Pause timer
textTimerController_->Pause();

// Reset timer
textTimerController_->Reset();
```

### Setting Initial Count

```cpp
// 60 seconds countdown
layoutProperty->UpdateInputCount(60000.0);

// 1 hour countdown
layoutProperty->UpdateInputCount(3600000.0);
```

---

## Important Implementation Details

### 1. TextTimer Uses Text Child Node

**Source**: `text_timer_model_ng.cpp:27-55`

TextTimer creates a **Text node** as its child to display timer value:

```cpp
// Create Text child node for timer display
auto textId = textTimerPattern->GetTextId();
auto textNode = FrameNode::GetOrCreateFrameNode(
    V2::TEXT_ETS_TAG, textId,
    []() { return AceType::MakeRefPtr<TextPattern>(); });
textNode->MountToParent(textTimerNode);
```

**Why**: Reuses Text's rendering and styling capabilities

### 2. Timer Update Mechanism

**Source**: `text_timer_pattern.cpp:109-127`

```cpp
void TextTimerPattern::Tick(uint64_t duration)
{
    elapsedTime_ += duration;  // Accumulate elapsed time

    FireChangeEvent();  // Fire change event

    auto tmpValue = static_cast<double>(elapsedTime_);
    if (isCountDown_) {
        // Countdown mode: calculate remaining time
        tmpValue = (inputCount_ >= static_cast<double>(elapsedTime_))
            ? (inputCount_ - static_cast<double>(elapsedTime_)) : 0;
    }

    // Countdown end handling
    if (isCountDown_ && tmpValue <= 0) {
        UpdateTextTimer(0);
        HandlePause();  // Auto-pause when countdown reaches 0
        return;
    }

    UpdateTextTimer(static_cast<uint32_t>(tmpValue));
}
```

### 3. Scheduler Usage

**Source**: `text_timer_pattern.cpp:83-107`

```cpp
void TextTimerPattern::InitTimerDisplay()
{
    if (!scheduler_) {
        auto weak = AceType::WeakClaim(this);
        auto&& callback = [weak](uint64_t duration) {
            auto timer = weak.Upgrade();
            if (timer) {
                timer->Tick(duration);  // Called every tick
            }
        };
        auto context = host->GetContextRefPtr();
        scheduler_ = SchedulerBuilder::Build(callback, context);
        auto count = isCountDown_ ? inputCount_ : 0;
        UpdateTextTimer(static_cast<uint32_t>(count));
    }
}
```

### 4. Controller Callbacks

**Source**: `text_timer_pattern.cpp:55-81`

```cpp
void TextTimerPattern::InitTextTimerController()
{
    // Register start callback
    textTimerController_->OnStart([weak]() {
        auto timerRender = weak.Upgrade();
        if (timerRender) {
            timerRender->HandleStart();  // Starts scheduler
        }
    });

    // Register pause callback
    textTimerController_->OnPause([weak]() {
        auto timerRender = weak.Upgrade();
        if (timerRender) {
            timerRender->HandlePause();  // Stops scheduler
        }
    });

    // Register reset callback
    textTimerController_->OnReset([weak]() {
        auto timerRender = weak.Upgrade();
        if (timerRender) {
            timerRender->HandleReset();  // Resets elapsed time and updates display
        }
    });
}
```

### 5. Text Update

**Source**: `text_timer_pattern.cpp:244-267`

```cpp
void TextTimerPattern::UpdateTextTimer(uint32_t elapsedTime)
{
    auto textLayoutProperty = textNode_->GetLayoutProperty<TextLayoutProperty>();

    // Use Localization to format time
    std::string timerText = Localization::GetInstance()->FormatDuration(elapsedTime, GetFormat());
    if (timerText.empty()) {
        timerText = Localization::GetInstance()->FormatDuration(elapsedTime, DEFAULT_FORMAT);
    }
    textLayoutProperty->UpdateContent(timerText);  // Update Text content

    // Mark node for update
    textNode_->MarkModifyDone();
    textNode_->MarkDirtyNode();
}
```

### 6. Visible Area Optimization

**Source**: `text_timer_pattern.cpp:204-242`

```cpp
void TextTimerPattern::OnVisibleAreaChange(bool visible)
{
    if (visible) {
        // Visible: Add Text child node
        if (!childNode) {
            host->AddChild(textNode_);
            host->RebuildRenderContextTree();
        }
    } else {
        // Not visible: Remove Text child node
        host->RemoveChild(textNode_);
        host->RebuildRenderContextTree();
    }
}
```

---

## ArkTS API Reference

```typescript
// Constructor
TextTimer(options?: {
  isCountDown?: boolean,
  count?: number,
  controller?: TextTimerController
})

// Properties
.format(value: string)                    // Set time format
.fontSize(value: number | Resource)       // Set font size
.fontColor(value: ResourceColor)          // Set text color
.fontWeight(value: number | FontWeight)   // Set font weight
.fontFamily(value: string | Resource)     // Set font family
.fontStyle(value: FontStyle)              // Set font style
.textShadow(value: ShadowOptions | Array<ShadowOptions>)  // Set text shadow

// Events
.onTimer((utc: number, elapsedTime: number) => void)  // Timer tick callback

// Controller methods
controller.start()   // Start timer
controller.pause()   // Pause timer
controller.reset()   // Reset timer
```

---

## Debugging

### Dump Commands

```bash
# View TextTimer component info
hidumper -s WindowManagerService -a '-a TextTimer'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'
```

### Log Tag

TextTimer component uses common log tags.

### Common Issues

| Issue | Check |
|-------|-------|
| Timer not updating | Check if `controller.start()` was called |
| Timer not pausing | Check countdown end condition (auto-pauses at 0) |
| Format incorrect | Check format string, verify with Localization service |
| Styles not applied | Check `*SetByUser` flags, Text child node creation |

---

## Execution Flow

```
Frontend: TextTimer({ isCountDown: true, count: 60000 })
    ↓
TextTimerModelNG::Create()
    ├── Create TextTimer FrameNode
    ├── Create Text child node
    └── Return textTimerController_
    ↓
TextTimerPattern::OnAttachToFrameNode()
    ↓
TextTimerPattern::OnModifyDone()
    ├── InitTextTimerController()
    ├── InitTimerDisplay()
    └── Register visible area callback
    ↓
controller.start()
    ↓
TextTimerPattern::HandleStart()
    └── scheduler_->Start()
    ↓
[Scheduler ticks every ~16ms]
    ↓
TextTimerPattern::Tick(duration)
    ├── elapsedTime_ += duration
    ├── Calculate display value
    ├── UpdateTextTimer()
    └── FireChangeEvent()
    ↓
Render Display
```

---

## References

- **Knowledge Base**: [TextTimer_Knowledge_Base_CN.md](../../../docs/pattern/texttimer/TextTimer_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **Controller**: `frameworks/core/components/texttimer/texttimer_controller.h`
- **Scheduler**: `core/common/task_scheduler/scheduler.h`
- **Related**: Text component (TextTimer uses Text internally)
