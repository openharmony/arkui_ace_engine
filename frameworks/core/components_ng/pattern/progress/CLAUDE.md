# Progress Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the Progress component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [Progress_Knowledge_Base_CN.md](../../../docs/pattern/progress/Progress_Knowledge_Base_CN.md)

---

## Overview

**Progress** is a progress indicator component used to display the progress of ongoing operations. It supports multiple progress types, gradient colors, sweeping effect animations, and custom text display.

**Architecture**: NG Pattern → ProgressPattern → ProgressLayoutAlgorithm (BoxLayoutAlgorithm) → ProgressModifier

**Key Features**:
- Multiple progress types: Linear, Ring, ScaleRing, Capsule, Moon (Eclipse)
- Gradient color support
- Sweeping effect animations
- Progress status display (Progressing/Loading)
- Customizable text display
- Shadow effects for Ring type
- Focus/Hover/Press state handling
- ContentModifier support
- RTL (Right-to-Left) layout support

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `progress_pattern.h/cpp` | ~270 (h) / ~1100 (cpp) | Pattern layer - business logic, event handling, state management |
| `progress_model_ng.h/cpp` | ~160 (h) / ~1600 (cpp) | Frontend bridge - Create(), property setters |
| `progress_layout_property.h` | ~30 | Layout properties (Type, StrokeWidth) |
| `progress_paint_property.h` | ~110 | Paint properties (Value, Color, Text, Effects) |
| `progress_date.h` | ~120 | Data structures and enums (ProgressType, ProgressStatus) |
| `progress_layout_algorithm.h/cpp` | ~80 (h) / ~300 (cpp) | Layout calculation |
| `progress_modifier.h/cpp` | ~650 (h) / ~2600 (cpp) | Drawing modifier, animations |

**Path**: `frameworks/core/components_ng/pattern/progress/`

---

## Core Class Hierarchy

```
                    Pattern
                       ↑
                ProgressPattern
                (progress_pattern.h:51)
                       |
        +--------------+--------------+--------------+
        |              |              |              |
  LayoutProperty  LayoutAlgorithm  PaintProperty  AccessibilityProperty
        ↑              ↑                  ↑                ↑
ProgressLayoutProperty  ProgressLayoutAlgorithm  ProgressPaintProperty  ProgressAccessibilityProperty

PaintMethod
    ↑
ProgressPaintMethod
    |
    +-- Creates/Updates --> ProgressModifier
                              ↑
                        ContentModifier
```

---

## Key Properties

### ArkTS Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `value` | number | 0 | Current progress value, range: [0, total] |
| `color` | ResourceColor \| LinearGradient | Theme color | Progress foreground color |
| `style` | StyleOptions | - | Component style (see below) |
| `contentModifier` | ContentModifier\<ProgressConfiguration\> | - | Custom UI (API 12+) |
| `privacySensitive` | Optional\<boolean\> | false | Privacy sensitive mode (API 12+) |

### C++ LayoutProperty (progress_layout_property.h)

| Property | Type | Default | Update Flag |
|----------|------|---------|-------------|
| `Type` | ProgressType | LINEAR | PROPERTY_UPDATE_MEASURE |
| `StrokeWidth` | Dimension | 4.0_vp | PROPERTY_UPDATE_MEASURE |

### C++ PaintProperty (progress_paint_property.h)

| Property | Type | Default | Update Flag |
|----------|------|---------|-------------|
| `Value` | double | 0 | PROPERTY_UPDATE_MEASURE |
| `MaxValue` | double | 100 | PROPERTY_UPDATE_MEASURE |
| `ProgressType` | ProgressType | LINEAR | PROPERTY_UPDATE_MEASURE |
| `Color` | Color | Theme | PROPERTY_UPDATE_MEASURE |
| `BackgroundColor` | Color | Theme | PROPERTY_UPDATE_MEASURE |
| `GradientColor` | Gradient | none | PROPERTY_UPDATE_MEASURE |
| `StrokeWidth` | Dimension | 4.0_vp | PROPERTY_UPDATE_MEASURE |
| `ScaleCount` | int32_t | 120 | PROPERTY_UPDATE_MEASURE |
| `ScaleWidth` | Dimension | 2.0_vp | PROPERTY_UPDATE_MEASURE |
| `Text` | string | auto | PROPERTY_UPDATE_MEASURE |
| `TextColor` | Color | Theme | PROPERTY_UPDATE_MEASURE |
| `FontSize` | Dimension | Theme | PROPERTY_UPDATE_MEASURE |
| `FontWeight` | FontWeight | Theme | PROPERTY_UPDATE_MEASURE |
| `FontFamily` | vector\<string\> | Theme | PROPERTY_UPDATE_MEASURE |
| `ItalicFontStyle` | FontStyle | Theme | PROPERTY_UPDATE_MEASURE |
| `EnableScanEffect` | bool | false | PROPERTY_UPDATE_MEASURE |
| `EnableRingScanEffect` | bool | false | PROPERTY_UPDATE_MEASURE |
| `EnableLinearScanEffect` | bool | false | PROPERTY_UPDATE_MEASURE |
| `EnableShowText` | bool | false | PROPERTY_UPDATE_MEASURE |
| `PaintShadow` | bool | false | PROPERTY_UPDATE_MEASURE |
| `ProgressStatus` | ProgressStatus | PROGRESSING | PROPERTY_UPDATE_MEASURE |
| `EnableSmoothEffect` | bool | true | PROPERTY_UPDATE_MEASURE |
| `BorderWidth` | Dimension | 1.0_vp | PROPERTY_UPDATE_MEASURE |
| `BorderColor` | Color | Theme | PROPERTY_UPDATE_MEASURE |
| `BorderRadius` | Dimension | height/2 | PROPERTY_UPDATE_MEASURE |

**User Set Flags**: `BackgroundColorSetByUser`, `GradientColorSetByUser` - prevent theme updates from overriding user values

---

## ProgressType Enum

**ArkTS (API 8+)**:
```typescript
enum ProgressType {
    Linear = 0,      // Linear style (vertical when height > width)
    Ring = 1,        // Ring style (no scale)
    Eclipse = 2,     // Eclipse/Moon style
    ScaleRing = 3,   // Ring with scale
    Capsule = 4,     // Capsule style (vertical when height > width)
}
```

**C++ (progress_date.h)**:
```cpp
enum class ProgressType {
    LINEAR = 1,      // Linear horizontal progress bar
    RING = 2,        // Ring/circular progress
    SCALE = 3,       // Scale ring progress
    CIRCLE = 4,      // Circle progress
    GAUGE = 5,       // Gauge progress (deprecated)
    ARC = 6,         // Arc progress
    MOON = 7,        // Moon/Eclipse progress
    BUBBLE = 8,      // Bubble progress
    CAPSULE = 9,     // Capsule progress
};
```

**Mapping** (js_progress.cpp):
- `ProgressStyle.Linear` → `ProgressType::LINEAR`
- `ProgressStyle.Ring` → `ProgressType::RING`
- `ProgressStyle.Eclipse` → `ProgressType::MOON`
- `ProgressStyle.ScaleRing` → `ProgressType::SCALE`
- `ProgressStyle.Capsule` → `ProgressType::CAPSULE`

---

## ProgressStatus Enum

**ArkTS (API 10+)**:
```typescript
enum ProgressStatus {
    PROGRESSING = -1,  // Progress updating
    LOADING = 0,       // Loading animation
}
```

**C++ (progress_date.h)**:
```cpp
enum class ProgressStatus {
    PROGRESSING = 0,  // Normal progress state
    LOADING           // Loading animation state
};
```

```cpp
enum class ProgressStatus {
    PROGRESSING = 0,  // Normal progress state
    LOADING           // Loading animation state
};
```

---

## Common Operations

### Setting Progress Value

```cpp
// Set current value
paintProperty->UpdateValue(50.0);

// Set maximum value
paintProperty->UpdateMaxValue(100.0);
```

### Setting Colors

```cpp
// Set solid color
paintProperty->UpdateColor(Color::BLUE);

// Set background color
paintProperty->UpdateBackgroundColor(Color::GRAY);

// Set gradient color
Gradient gradient;
gradient.AddGradientColor(GradientColor(Color::RED, Dimension(0)));
gradient.AddGradientColor(GradientColor(Color::BLUE, Dimension(1)));
paintProperty->UpdateGradientColor(gradient);
```

### Setting Stroke Width

```cpp
paintProperty->UpdateStrokeWidth(Dimension(8.0_vp));
```

### Setting Progress Type

```cpp
layoutProperty->UpdateType(ProgressType::RING);
```

### Setting Text

```cpp
// Custom text
paintProperty->UpdateText("Loading...");

// Font size
paintProperty->UpdateTextSize(Dimension(16.0_fp));

// Text color
paintProperty->UpdateTextColor(Color::BLACK);
```

### Setting Effects

```cpp
// Sweeping effect
paintProperty->UpdateEnableScanEffect(true);

// Shadow effect (Ring type)
paintProperty->UpdatePaintShadow(true);

// Loading status
paintProperty->UpdateProgressStatus(ProgressStatus::LOADING);
```

---

## Important Implementation Details

### 1. Progress Uses ContentModifier for Rendering

**Source**: `progress_paint_method.cpp`

Progress uses `ProgressModifier` (inherits from `ContentModifier`) for drawing:
- All drawing logic is in `ProgressModifier::onDraw()`
- Different paint methods for each type: `PaintLinear()`, `PaintRing()`, `PaintMoon()`, `PaintCapsule()`

### 2. Value/Color Changes Trigger Layout Pass

**Source**: `progress_paint_property.h:74,91`

```cpp
// Value and Color are marked as PROPERTY_UPDATE_MEASURE
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Value, double, PROPERTY_UPDATE_MEASURE);
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
```

This means value/color changes trigger a full layout pass before rendering.

### 3. Progress Type Determines Drawing Method

**Source**: `progress_modifier.cpp:onDraw()`

```cpp
void ProgressModifier::onDraw(DrawingContext& context)
{
    switch (progressType_) {
        case ProgressType::LINEAR:
            PaintLinear(canvas, offset, contentSize);
            break;
        case ProgressType::RING:
            PaintRing(canvas, offset, contentSize);
            break;
        case ProgressType::MOON:
            PaintMoon(canvas, offset, contentSize);
            break;
        case ProgressType::CAPSULE:
            PaintCapsule(canvas, offset, contentSize, capsuleBorderRadius_);
            break;
        // ...
    }
}
```

### 4. Sweeping Effect Animation

**Source**: `progress_modifier.cpp`

```cpp
// Ring sweeping animation
void ProgressModifier::StartRingSweepingAnimation(float value)
{
    float currentDate = sweepingDateBackup_;
    float newDate = value * 360.0f / maxValue_;
    float speed = newDate > currentDate ? 6.0f : 12.0f;
    StartContinuousSweepingAnimation(currentDate, newDate, speed);
}

// Linear/Capsule sweeping animation
void ProgressModifier::StartLinearSweepingAnimation(float value)
{
    float date = valueBackup_;
    float targetValue = value;
    float speed = 1.0f;
    StartLinearSweepingAnimationImpl(date, targetValue, speed);
}
```

### 5. Focus State Handling

**Source**: `progress_pattern.cpp`

```cpp
void ProgressPattern::SetFocusStyle()
{
    SetTextColor(focusedTextColor_);
    capsuleFocusScale_ = 1.05f;
    focusShadowStyle_ = ShadowStyle::SPACE;
}

void ProgressPattern::ClearFocusStyle()
{
    SetTextColor(defaultTextColor_);
    capsuleFocusScale_ = 1.0f;
    focusShadowStyle_ = ShadowStyle::None;
}
```

### 6. Gradient Colors are Sorted by Offset

**Source**: `progress_modifier.cpp`

```cpp
Gradient ProgressModifier::SortGradientColorsByOffset(const Gradient& gradient) const
{
    Gradient sortedGradient = gradient;
    auto& gradientColors = sortedGradient.GetGradientColors();
    std::sort(gradientColors.begin(), gradientColors.end(),
        [](const GradientColor& a, const GradientColor& b) {
            return a.GetDimension().ConvertToVp() < b.GetDimension().ConvertToVp();
        });
    return sortedGradient;
}
```

### 7. RTL (Right-to-Left) Layout Support

**Source**: `progress_pattern.cpp`

```cpp
bool isRtl = progressLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
progressModifier_->SetIsRightToLeft(isRtl);
```

### 8. Loading Status Animation

**Source**: `progress_modifier.cpp`

```cpp
// Ring loading animation (head and tail)
void ProgressModifier::StartRingLoadingAnimation()
{
    StartRingLoadingHeadAnimation();  // Head moves forward
    StartRingLoadingTailAnimation();  // Tail follows
}
```

---

## ArkTS API Reference

```typescript
// Constructor
Progress(options: { value: number, total?: number, type?: ProgressType })

// Properties
.value(value: number)                              // Set current progress value
.color(value: ResourceColor | LinearGradient)      // Set progress color (supports gradient from API 10+ for Ring, API 23+ for Linear/Capsule)
.style(options: ProgressStyleOptions | CapsuleStyleOptions | RingStyleOptions |
         LinearStyleOptions | ScaleRingStyleOptions | EclipseStyleOptions)  // Set style based on progress type
.contentModifier(modifier: ContentModifier<ProgressConfiguration>)  // Custom UI (API 12+)
.privacySensitive(isPrivacySensitiveMode: Optional<boolean>)  // Privacy sensitive mode (API 12+)

// CommonProgressStyleOptions (API 10+)
interface CommonProgressStyleOptions {
    enableSmoothEffect?: boolean;                  // Enable smooth effect (default: true)
}

// ScanEffectOptions (API 10+)
interface ScanEffectOptions {
    enableScanEffect?: boolean;                    // Enable scan/sweep effect (default: false)
}

// ProgressStyleOptions (API 8+) - inherits CommonProgressStyleOptions
interface ProgressStyleOptions {
    strokeWidth?: Length;                          // Stroke width (default: 4.0vp)
    scaleCount?: number;                           // Scale count for ScaleRing (default: 120)
    scaleWidth?: Length;                           // Scale width for ScaleRing (default: 2.0vp)
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// LinearStyleOptions (API 10+) - inherits ScanEffectOptions + CommonProgressStyleOptions
interface LinearStyleOptions {
    strokeWidth?: Length;                          // Stroke width (default: 4.0vp)
    strokeRadius?: PX | VP | LPX | Resource;       // Stroke radius (range: [0, strokeWidth/2], default: strokeWidth/2)
    enableScanEffect?: boolean;                    // Inherited from ScanEffectOptions
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// RingStyleOptions (API 10+) - inherits ScanEffectOptions + CommonProgressStyleOptions
interface RingStyleOptions {
    strokeWidth?: Length;                          // Stroke width (default: 4.0vp)
    shadow?: boolean;                              // Enable shadow effect (default: false)
    status?: ProgressStatus;                       // Progress status: PROGRESSING | LOADING (default: PROGRESSING)
    enableScanEffect?: boolean;                    // Inherited from ScanEffectOptions
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// ScaleRingStyleOptions (API 10+) - inherits CommonProgressStyleOptions
interface ScaleRingStyleOptions {
    strokeWidth?: Length;                          // Stroke width (default: 4.0vp)
    scaleCount?: number;                           // Scale count (default: 120, range: [2, min(width, height)/scaleWidth/2/π])
    scaleWidth?: Length;                           // Scale width (default: 2.0vp)
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// EclipseStyleOptions (API 10+) - inherits CommonProgressStyleOptions
interface EclipseStyleOptions {
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// CapsuleStyleOptions (API 10+) - inherits ScanEffectOptions + CommonProgressStyleOptions
interface CapsuleStyleOptions {
    borderColor?: ResourceColor;                   // Border color (default: #33007dff for API 11+)
    borderWidth?: Length;                          // Border width (default: 1vp)
    content?: ResourceStr;                         // Custom text content
    font?: Font;                                   // Text style (size, weight, family, style)
    fontColor?: ResourceColor;                     // Text color (default: #ff182431)
    showDefaultPercentage?: boolean;               // Show percentage text (default: false)
    borderRadius?: LengthMetrics;                  // Border radius (API 18+, range: [0, height/2], default: height/2)
    enableScanEffect?: boolean;                    // Inherited from ScanEffectOptions
    enableSmoothEffect?: boolean;                  // Inherited from CommonProgressStyleOptions
}

// ProgressConfiguration (API 12+) - for contentModifier
interface ProgressConfiguration extends CommonConfiguration {
    value: number;                                 // Current progress value
    total: number;                                 // Total progress value
}
```

**ProgressType Enum** (API 8+):
```typescript
enum ProgressType {
    Linear = 0,      // Linear style (vertical when height > width, from API 9)
    Ring = 1,        // Ring style (no scale)
    Eclipse = 2,     // Eclipse/Moon style
    ScaleRing = 3,   // Ring with scale (auto-converts to Ring when scales overlap, from API 9)
    Capsule = 4,     // Capsule style (vertical when height > width, from API 9)
}
```

**ProgressStatus Enum** (API 10+):
```typescript
enum ProgressStatus {
    PROGRESSING = -1,  // Progress updating (default)
    LOADING = 0,       // Loading animation (value changes ignored when set)
}
```

**Note**:
- `total` and `type` can only be set in the constructor, not via setter methods
- `backgroundColor` is a universal property, sets progress bar background (track) color

---

## Execution Flow

```
Frontend: Progress({ value: 50, total: 100, type: ProgressType.Linear })
    ↓
ProgressModelNG::Create()
    ├── Create Progress FrameNode
    ├── Set initial values
    └── Return
    ↓
ProgressPattern::OnAttachToFrameNode()
    ├── InitFocusEvent()
    ├── InitTouchEvent()
    └── InitHoverEvent()
    ↓
ProgressPattern::OnModifyDone()
    ├── Update color/gradient
    ├── Update properties
    └── Request measure/layout
    ↓
ProgressLayoutAlgorithm::MeasureContent()
    ├── Calculate content size
    └── Return SizeF
    ↓
ProgressPaintMethod::GetContentModifier()
    ├── Create/Update ProgressModifier
    └── Apply theme
    ↓
ProgressModifier::onDraw()
    ├── Draw based on ProgressType
    ├── Apply sweeping effect (if enabled)
    └── Render display
```

---

## References

- **Knowledge Base**: [Progress_Knowledge_Base_CN.md](../../../docs/pattern/progress/Progress_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting