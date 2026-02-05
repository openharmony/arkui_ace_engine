# TextClock Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the TextClock component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [TextClock_Knowledge_Base_CN.md](../../../docs/pattern/text_clock/TextClock_Knowledge_Base_CN.md)

---

## Overview

**TextClock** is a text clock component used for displaying current system time. It supports various time formats, timezone offsets, 12/24-hour clock switching, and localization.

**Architecture**: NG Pattern → TextClockPattern → TextClockLayoutAlgorithm (BoxLayoutAlgorithm)

**Key Features**:
- Multiple time formats (year, month, day, hour, minute, second, millisecond, weekday, AM/PM)
- Timezone offset support (hoursWest)
- 12/24-hour clock auto-adaptation
- Leading zero control for hours
- Time change event (updates every second)
- Visible area optimization (stops updating when not visible)
- ContentModifier support
- System time and language change listeners

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `text_clock_pattern.h/cpp` | ~200 (h) / ~900 (cpp) | Pattern layer - business logic, time update, event handling |
| `text_clock_model_ng.h/cpp` | ~50 (h) / ~180 (cpp) | Frontend bridge - Create(), property setters |
| `text_clock_layout_property.h` | ~85 | Clock properties (Format, HoursWest, PrefixHour) |
| `text_clock_event_hub.h` | ~30 | Date change event |
| `text_clock_controller.h` | ~50 | Clock controller (start/stop) |

**Path**: `frameworks/core/components_ng/pattern/text_clock/`

---

## Core Class Hierarchy

```
                    Pattern + TimeChangeListener
                           ↑
                    TextClockPattern
                    (text_clock_pattern.h:43)
                           |
        +--------------+--------------+
        |              |              |
  LayoutProperty  LayoutAlgorithm  AccessibilityProperty
        ↑              ↑                    ↑
TextClockLayoutProperty  TextClockLayoutAlgorithm  TextClockAccessibilityProperty
        |
TextLayoutProperty (inherits)
```

**TextClockPattern** inherits from both `Pattern` and `TimeChangeListener` interfaces.

---

## Key Properties

### Time Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `Format` | string | "aa hh:mm:ss" / "HH:mm:ss" | Time format string |
| `HoursWest` | float | NAN | Timezone offset (hours), NAN = system timezone |
| `PrefixHour` | ZeroPrefixType | AUTO | Hour leading zero type |

### Font Style Properties (inherited from TextLayoutProperty)

| Property | Type | Description |
|----------|------|-------------|
| `FontSize` | Dimension | Font size |
| `TextColor` | Color | Text color |
| `FontWeight` | FontWeight | Font weight |
| `FontFamily` | vector\<string\> | Font family |
| `ItalicFontStyle` | FontStyle | Italic style |
| `TextShadow` | vector\<Shadow\> | Text shadow |
| `FontFeature` | FONT_FEATURES_LIST | Font features |

**User Set Flag**: `TextColorSetByUser` - prevents theme updates from overriding user value

---

## ZeroPrefixType Enum

```cpp
enum class ZeroPrefixType {
    AUTO,   // Auto: 24-hour clock with leading zero, 12-hour without
    ZERO,   // Force with leading zero
    NO_ZERO // Force without leading zero
};
```

---

## Time Format Characters

| Character | Description | Example |
|-----------|-------------|---------|
| `Y` | Year (4 digits) | 2026 |
| `y` | Year (2 digits) | 26 |
| `M` | Month (numeric) | 2 or 12 |
| `D` | Day (numeric) | 1 or 31 |
| `d` | Weekday (abbreviated) | Mon |
| `dd` | Weekday (full) | Monday |
| `H` | Hour (24-hour clock) | 23 |
| `h` | Hour (12-hour clock) | 11 |
| `m` | Minute | 59 |
| `s` | Second | 59 |
| `S` | Centisecond | 99 |
| `a` | AM/PM (lowercase) | am |
| `A` | AM/PM (uppercase) | AM |

---

## Common Operations

### Setting Time Format

```cpp
// Set custom format
layoutProperty->UpdateFormat("yyyy-MM-dd HH:mm:ss");

// 12-hour clock
layoutProperty->UpdateFormat("aa hh:mm:ss");

// 24-hour clock
layoutProperty->UpdateFormat("HH:mm:ss");
```

### Setting Timezone Offset

```cpp
// UTC+8 (Beijing time)
layoutProperty->UpdateHoursWest(8.0f);

// UTC-5 (New York time)
layoutProperty->UpdateHoursWest(-5.0f);

// Use system timezone (default)
layoutProperty->UpdateHoursWest(NAN);
```

### Setting Leading Zero Type

```cpp
// Auto (24-hour with zero, 12-hour without)
layoutProperty->UpdatePrefixHour(ZeroPrefixType::AUTO);

// Force with leading zero
layoutProperty->UpdatePrefixHour(ZeroPrefixType::ZERO);

// Force without leading zero
layoutProperty->UpdatePrefixHour(ZeroPrefixType::NO_ZERO);
```

### Using Controller

```cpp
// Start clock
textClockController_->Start();

// Stop clock
textClockController_->Stop();
```

---

## Important Implementation Details

### 1. TextClock Uses Text Child Node

**Source**: `text_clock_model_ng.cpp:23-48`

TextClock creates a **Text node** as its child to display time:

```cpp
// Create Text child node for time display
auto textId = pattern->GetTextId();
auto textNode = FrameNode::GetOrCreateFrameNode(
    V2::TEXT_ETS_TAG, textId,
    []() { return AceType::MakeRefPtr<TextPattern>(); });
textNode->MountToParent(textClockNode);
```

**Why**: Reuses Text's rendering and styling capabilities

### 2. Time Update Mechanism

**Source**: `text_clock_pattern.cpp:254-286`

```cpp
void TextClockPattern::UpdateTimeText(bool isTimeChange)
{
    // Check if should update
    if (!isStart_ || (!isTimeChange && !isInVisibleArea_)) {
        return;
    }

    // Get current formatted time
    std::string currentTime = GetCurrentFormatDateTime();

    // Update Text child node content
    textLayoutProperty->UpdateContent(currentTime);

    // Request next update
    RequestUpdateForNextSecond();

    // Fire change event
    FireChangeEvent();
}
```

### 3. Delay Task Calculation

**Source**: `text_clock_pattern.cpp:288-328`

To ensure the clock updates at exactly the right second:

```cpp
void TextClockPattern::RequestUpdateForNextSecond()
{
    struct timeval currentTime {};
    gettimeofday(&currentTime, nullptr);

    // Calculate delay to next second
    int32_t delayTime =
        (INTERVAL_OF_U_SECOND - static_cast<int32_t>(currentTime.tv_usec)) /
        MICROSECONDS_OF_MILLISECOND + 1;  // milliseconds

    // If format doesn't include seconds, delay to next minute
    auto nextMinuteFlag = isForm_ || (!makeFunc_.has_value() &&
        GetFormat().find('S') == std::string::npos &&
        GetFormat().find('s') == std::string::npos);

    if (nextMinuteFlag) {
        // Delay to next minute instead
        int32_t tempTime = (TOTAL_SECONDS_OF_MINUTE - timeZoneTime->tm_sec) * MILLISECONDS_OF_SECOND;
        delayTime += (tempTime - MILLISECONDS_OF_SECOND);
    }

    // Post delayed task
    context->GetTaskExecutor()->PostDelayedTask(
        delayTask_, TaskExecutor::TaskType::UI, delayTime, "ArkUITextClockUpdateTimeText");
}
```

### 4. Visible Area Optimization

**Source**: `text_clock_pattern.cpp:210-239`

```cpp
void TextClockPattern::OnVisibleAreaChange(bool visible)
{
    if (visible && !isInVisibleArea_) {
        isInVisibleArea_ = visible;
        UpdateTimeText();  // Resume time updates
    } else if (!visible) {
        isInVisibleArea_ = visible;
        delayTask_.Cancel();  // Stop updating when not visible
    }
}
```

### 5. Time Change Listener

**Source**: `text_clock_pattern.cpp:110-113, 813-818`

```cpp
// Register to TimeEventProxy
void TextClockPattern::OnAttachToFrameNode()
{
    auto* eventProxy = TimeEventProxy::GetInstance();
    if (eventProxy) {
        eventProxy->Register(WeakClaim(this));
    }
}

// Called when system time changes
void TextClockPattern::OnTimeChange()
{
    is24H_ = SystemProperties::Is24HourClock();  // Update 24H state
    UpdateTimeText(ON_TIME_CHANGE);  // Force update
}
```

### 6. 12/24-Hour Clock Auto-Adaptation

**Source**: `text_clock_pattern.cpp:193`

```cpp
bool is24H_ = SystemProperties::Is24HourClock();

// Returns default format based on system settings when format is empty
std::string TextClockPattern::GetFormat() const
{
    auto format = textClockLayoutProperty->GetFormat().value_or("");
    if (format.empty()) {
        return is24H_ ? DEFAULT_FORMAT_24H : DEFAULT_FORMAT;
    }
    return format;
}
```

---

## ArkTS API Reference

```typescript
// Constructor
TextClock(options?: { timeZoneOffset?: number, controller?: TextClockController })

// Properties
.format(value: string)                    // Set time format
.hoursWest(value: number)                 // Set timezone offset (hours)
.fontSize(value: number | Resource)       // Set font size
.fontColor(value: ResourceColor)          // Set text color
.fontWeight(value: number | FontWeight)   // Set font weight
.fontFamily(value: string | Resource)     // Set font family
.fontStyle(value: FontStyle)              // Set font style
.textShadow(value: ShadowOptions | Array<ShadowOptions>)  // Set text shadow
.dateTimeOptions(options: { hour: ZeroPrefixType })  // Set date time options

// Events
.onDateChange(callback: (value: string) => void)  // Date change callback

// Controller methods
controller.start()   // Start clock
controller.stop()    // Stop clock
```

---

## Debugging

### Dump Commands

```bash
# View TextClock component info
hidumper -s WindowManagerService -a '-a TextClock'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'
```

### Log Tag

TextClock component uses `ACE_TEXT_CLOCK` log tag.

```cpp
TAG_LOGI(AceLogTag::ACE_TEXT_CLOCK, "Time is changed and clock updates");
```

### Common Issues

| Issue | Check |
|-------|-------|
| Time not updating | Check `isStart_` status, visible area callback, TimeEventProxy registration |
| Format incorrect | Check format string, system 12/24-hour clock settings |
| Timezone incorrect | Check `hoursWest` setting, system timezone |
| Styles not applied | Check `TextColorSetByUser` flag, Text child node creation |

---

## Execution Flow

```
Frontend: TextClock({ format: 'HH:mm:ss' })
    ↓
TextClockModelNG::Create()
    ├── Create TextClock FrameNode
    ├── Create Text child node
    └── Return textClockController_
    ↓
TextClockPattern::OnAttachToFrameNode()
    ├── InitTextClockController()
    ├── InitUpdateTimeTextCallBack()
    └── Register to TimeEventProxy
    ↓
TextClockPattern::OnModifyDone()
    ├── Get timezone offset
    ├── Cancel previous delay task
    └── UpdateTimeText()
    ↓
RequestUpdateForNextSecond()
    ├── Calculate delay time
    └── Post delayed task
    ↓
[Wait for delay] / System time change
    ↓
TextClockPattern::UpdateTimeText()
    ├── Get current formatted time
    ├── Update Text child node content
    └── FireChangeEvent()
    ↓
Render Display
```

---

## References

- **Knowledge Base**: [TextClock_Knowledge_Base_CN.md](../../../docs/pattern/text_clock/TextClock_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **Controller**: `frameworks/core/components/text_clock/text_clock_controller.h`
- **Time Event**: `core/event/time/time_event_proxy.h`
- **Related**: Text component (TextClock uses Text internally)
