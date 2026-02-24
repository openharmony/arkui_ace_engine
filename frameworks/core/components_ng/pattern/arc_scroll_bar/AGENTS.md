# ArcScrollBar Pattern Component Knowledge

This document provides specific guidance for the ArcScrollBar pattern component within the ACE Engine NG architecture.

## Overview

**ArcScrollBarPattern** is a specialized variant of ScrollBarPattern that renders a **circular/arc-shaped** scrollbar indicator instead of the traditional rectangular bar. It is designed for rotary input devices and circular UI interfaces.

**Key Design Principle**: ArcScrollBar is a **thin wrapper** around ScrollBarPattern that customizes the geometry and rendering while inheriting all scroll interaction logic.

## Inheritance Relationship

```
ScrollBarPattern (base)
    ↓ extends
ArcScrollBarPattern (this component)
    ↓ creates
ArcScrollBar (inner class) extends ScrollBar
```

### What ArcScrollBarPattern Overrides

| Method | Override Behavior | Purpose |
|--------|------------------|---------|
| `CreateLayoutAlgorithm()` | Returns `ArcScrollBarLayoutAlgorithm` | Custom layout for circular geometry |
| `CreateNodePaintMethod()` | Returns `ArcScrollBarPaintMethod` | Arc-specific rendering pipeline |
| `UseInnerScrollBar()` | Returns `true` | Always uses internal ArcScrollBar (no child FrameNode) |
| `CreateScrollBar()` | Returns `ArcScrollBar` instance | Creates arc-shaped internal scrollbar |
| `SetBarCollectClickAndLongPressTargetCallback()` | Empty implementation | Arc scrollbar doesn't support track click/long-press |
| `OnModifyDone()` | Sets `HitTestMode::HTMTRANSPARENT` | Allows click-through to underlying content |

## Responsibility Boundaries

### What ArcScrollBarPattern Does

1. **Circular Geometry Management**
   - Renders scrollbar as an arc around a center point
   - Calculates angles, radii, and sweep for arc representation
   - Positions scrollbar on LEFT or RIGHT side of circular content

2. **Arc-Specific Hit Testing**
   - Uses `ArcRound::IsInRegion()` for touch detection
   - Three-tier hit regions: `arcHotZoneRect_`, `arcHoverRegion_`, `arcAarRect_`

3. **Visual Feedback**
   - Arc-specific hover and opacity animations
   - Background arc (track) and foreground arc (thumb) rendering
   - Width changes on hover/active states

4. **Position Conversion**
   - Converts linear scroll offset to arc angle position
   - Handles `CalcPatternOffset()` for arc geometry

### What ArcScrollBarPattern Does NOT Do (Inherited from ScrollBarPattern)

- **NOT** handling scroll position callback logic (delegates to base)
- **NOT** managing ScrollBarProxy registration (delegates to base)
- **NOT** handling drag gesture recognizers (delegates to base)
- **NOT** managing disappear/appear animations (delegates to base)
- **NOT** supporting track click-to-scroll (empty override)

## Architecture Differences from ScrollBarPattern

### Geometry Model

| Aspect | ScrollBarPattern (Rectangular) | ArcScrollBarPattern (Circular) |
|--------|-------------------------------|-------------------------------|
| **Geometry** | `Rect` (x, y, width, height) | `ArcRound` (center, radius, startAngle, sweepAngle, width) |
| **Position** | Vertical/Horizontal linear | Angular position along arc |
| **Hit Testing** | `Rect::IsInRegion(point)` | `ArcRound::IsInRegion(point, minHotRegion)` |
| **Child Node** | Has child FrameNode (legacy) | No child FrameNode (always inner scrollbar) |
| **HitTestMode** | Default (opaque) | `HTMTRANSPARENT` (click-through) |

### Component Structure

```
arc_scroll_bar/
├── arc_scroll_bar_pattern.{h,cpp}         # Thin pattern wrapper
├── arc_scroll_bar_layout_algorithm.{h,cpp} # Minimal layout implementation
└── arc_scroll_bar_paint_method.{h,cpp}     # Arc rendering pipeline

Related (in arc_scroll/inner/):
├── arc_scroll_bar.h                        # ArcScrollBar inner class
└── arc_scroll_bar_overlay_modifier.h       # Arc rendering modifier
```

## Critical Behaviors - Must Not Change

### 1. Always Use Inner ScrollBar Mode

```cpp
// arc_scroll_bar_pattern.h:62
bool UseInnerScrollBar() const override
{
    return true;
}
```

**Rule**: This MUST always return `true`. ArcScrollBar never has a child FrameNode.

### 2. HitTestMode MUST Be HTMTRANSPARENT

```cpp
// arc_scroll_bar_pattern.cpp:29
gestureHub->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
```

**Reason**: Arc scrollbar overlays circular content. Touch events outside the arc region must pass through to underlying components.

**DO NOT**:
- Change to `HitTestMode::DEFAULT` (blocks content interaction)
- Remove this line in `OnModifyDone()`

### 3. Empty Click/Long-Press Callback

```cpp
// arc_scroll_bar_pattern.h:72
void SetBarCollectClickAndLongPressTargetCallback() override {}
```

**Rule**: This MUST remain empty. Arc scrollbars do not support:
- Click-to-scroll on track
- Long-press continuous scrolling

These interactions conflict with circular UI semantics.

### 4. ArcScrollBar MUST Use ShapeMode::ROUND

```cpp
// arc_scroll/inner/arc_scroll_bar.h:25
ArcScrollBar() : ScrollBar(DisplayMode::AUTO, ShapeMode::ROUND, PositionMode::RIGHT) {}
```

**DO NOT**:
- Change to `ShapeMode::RECT` (breaks arc rendering)
- Use different `DisplayMode` default

### 5. PositionMode Determines Angle Direction

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:53-54
double sweepAngle = GetPositionMode() == PositionMode::LEFT ?
    -GetArcNormalMaxOffsetAngle() : GetArcNormalMaxOffsetAngle();
```

- `PositionMode::RIGHT`: Angles increase clockwise (standard)
- `PositionMode::LEFT`: Angles increase counter-clockwise (mirrored)

**DO NOT** change angle calculation logic - affects RTL support.

## Arc Geometry Fundamentals

### ArcRound Structure

```cpp
ArcRound(centerPoint, radius, startAngle, sweepAngle, width)
```

| Parameter | Description | Example |
|-----------|-------------|---------|
| `centerPoint` | Center of the circle | `(width/2, height/2)` |
| `radius` | Distance from center to arc midline | Calculated from container size |
| `startAngle` | Starting angle in degrees | `-maxAngle/2` (centered at top) |
| `sweepAngle` | Arc span in degrees | Proportional to scrollable content |
| `width` | Thickness of the arc bar | Theme-defined (e.g., 4.vp) |

### Angle Calculation (Critical)

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:82-89
if (NearZero(barRegionSize - activeSize) || NearZero(barRegionSize)) {
    LOGE("(barRegionSize - activeSize) or barRegionSize is zero");
    return;
} else {
    trickSweepAngle_ = activeSize * maxAngle / barRegionSize;
    trickStartAngle = (maxAngle - trickSweepAngle_) * activeMainOffset /
                     (barRegionSize - activeSize);
}
```

**Key Formula**:
```
thumbSweepAngle = (activeContentSize / totalContentSize) * maxArcAngle
thumbStartAngle = -maxAngle/2 + (scrollOffset / scrollableDistance) *
                  (maxAngle - thumbSweepAngle)
```

**DO NOT** modify these formulas without thorough testing - they ensure correct scroll position mapping.

### Three Arc Regions

| Region | Purpose | Hit Test Priority |
|--------|---------|-------------------|
| `arcAarRect_` | Background track (full arc) | Lowest |
| `arcHoverRegion_` | Hover feedback area | Medium |
| `arcHotZoneRect_` | Touch input zone (thumb) | Highest |
| `arcActiveRect_` | Visual thumb rendering | Visual only |

## Common Pitfalls

### 1. Division by Zero in Angle Calculation

**Problem**: `barRegionSize - activeSize` can be zero when content fits viewport.

```cpp
// WRONG - will crash if barRegionSize - activeSize == 0
trickStartAngle = (maxAngle - trickSweepAngle_) * activeMainOffset /
                 (barRegionSize - activeSize);

// CORRECT - guards against zero division
if (NearZero(barRegionSize - activeSize) || NearZero(barRegionSize)) {
    LOGE("... is zero");
    return;
}
```

**Rule**: Always check denominators before angle calculations.

### 2. PositionMode Angle Sign

**Problem**: LEFT position mode requires negating sweep angle.

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:90-96
if (GetPositionMode() == PositionMode::LEFT) {
    if (trickStartAngle > 0.0) {
        trickStartAngle_ = STRAIGHT_ANGLE - trickStartAngle;
    } else {
        trickStartAngle_ = -(trickStartAngle + STRAIGHT_ANGLE);
    }
    trickSweepAngle_ = -trickSweepAngle_;  // CRITICAL: negate for LEFT
}
```

**Rule**: LEFT mode requires angle transformation for RTL mirroring.

### 3. Center Deviation Calculation

**Problem**: Forgetting that `centerDeviation_` shifts the arc radius.

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:56
centerDeviation_ = width * FACTOR_HALF;  // Shift by half width
// ...
double radius = size.Width() * FACTOR_HALF - centerDeviation_;
```

**Why**: Arc is drawn at centerline. Outer edge = center + width/2, inner edge = center - width/2.

**Rule**: Always subtract `centerDeviation_` from container radius.

### 4. Reserved Height

**Problem**: Arc scrollbars typically don't use reserved height (unlike rectangular).

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:169-172
void ArcScrollBar::CalcReservedHeight(const RefPtr<PipelineContext>& context)
{
    SetStartReservedHeight(Dimension(0.0, DimensionUnit::PX));
    SetEndReservedHeight(Dimension(0.0, DimensionUnit::PX));
    FlushBarWidth();
}
```

**Rule**: Override `CalcReservedHeight()` to return 0 for arc geometry.

### 5. LayoutAlgorithm Empty Implementation

**Problem**: `ArcScrollBarLayoutAlgorithm::Layout()` is intentionally empty.

```cpp
// arc_scroll_bar_layout_algorithm.cpp:56
void ArcScrollBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // Empty - all layout done by inner ArcScrollBar
}
```

**Reason**: Inner `ArcScrollBar` handles all geometry calculations via `SetBarRegion()` and `SetRoundTrickRegion()`.

**DO NOT** add layout logic here - it will conflict with inner scrollbar.

## Debugging

### Key State Variables (ArcScrollBar)

| Variable | Purpose | Location |
|----------|---------|----------|
| `arcActiveRect_` | Visual thumb arc | Inner ArcScrollBar |
| `arcAarRect_` | Background track arc | Inner ArcScrollBar |
| `arcHotZoneRect_` | Touch hit region | Inner ArcScrollBar |
| `trickStartAngle_` | Thumb start angle | Inner ArcScrollBar |
| `trickSweepAngle_` | Thumb sweep angle | Inner ArcScrollBar |
| `centerDeviation_` | Radius offset for width | Inner ArcScrollBar |
| `width_` | Thumb thickness | Inner ArcScrollBar |

### Log Tags

Arc scrollbar uses inherited `AceLogTag::ACE_SCROLL_BAR`:

```cpp
// arc_scroll/inner/arc_scroll_bar.cpp:125
TAG_LOGE(AceLogTag::ACE_SCROLL_BAR, "estimatedHeight:%{public}1lf", estimatedHeight);
```

**No arc-specific log tag** - reuse scrollbar tag.

### Common Issues & Diagnostics

**Symptom**: Arc not visible
- Check `ShapeMode::ROUND` is set in ArcScrollBar constructor
- Check `NeedPaint()` returns true
- Check arc radius is positive (calculated from container size)
- Check sweep angle is not zero

**Symptom**: Touch not working
- Check `HitTestMode::HTMTRANSPARENT` is set
- Check `arcHotZoneRect_` is initialized
- Check `InBarTouchRegion()` returns true for touch points
- Verify min hot region (36.vp) is being used

**Symptom**: Thumb position incorrect
- Check `trickStartAngle_` and `trickSweepAngle_` calculations
- Verify `activeMainOffset` is clamped to valid range
- Check `PositionMode` LEFT angle transformations
- Verify `isReverse_` flag is correct

**Symptom**: Arc overlaps content
- Check container size is sufficient for arc radius
- Verify `centerDeviation_` is applied to radius calculation
- Check `GetArcNormalBackgroundWidth()` is not too large

## Layout Algorithm Specifics

### Measure Phase

```cpp
// arc_scroll_bar_layout_algorithm.cpp:35-54
void ArcScrollBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(...);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_CONTENT);
    auto parentSize = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_PARENT);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);
    MinusPaddingToSize(padding, parentSize);

    auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    UpdateIdealSize(size, parentSize, idealSize);  // Use container size

    AddPaddingToSize(padding, idealSize);
    auto selfSize = idealSize.ConvertToSizeT();
    selfSize.Constrain(constraint->minSize, constraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(selfSize);
}
```

**Key Point**: Arc scrollbar size matches container size (full fill).

### Layout Phase

**Empty by design** - all layout work done by:
1. `ArcScrollBar::SetBarRegion()` - calculates background arc
2. `ArcScrollBar::SetRoundTrickRegion()` - calculates thumb arc

## Paint Method Specifics

```cpp
// arc_scroll_bar_paint_method.cpp:22-44
void ArcScrollBarPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    // ... null checks ...

    // Update position mode if changed
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }

    // Cast to arc-specific types
    auto arcScrollBarOverlayModifier = AceType::DynamicCast<ArcScrollBarOverlayModifier>(...);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(...);

    // Update arc-specific properties
    arcScrollBarOverlayModifier->SetBackgroundBarColor(arcScrollBar->GetArcBackgroundColor());
    arcScrollBarOverlayModifier->StartArcBarAnimation(
        arcScrollBar->GetHoverAnimationType(),
        arcScrollBar->GetOpacityAnimationType(),
        arcScrollBar->GetNeedAdaptAnimation(),
        arcScrollBar->GetArcActiveRect(),
        arcScrollBar->GetArcBarRect());

    // Reset animation flags
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetArcForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
```

**Key Behavior**: Animation flags are reset after each frame to prevent stale animations.

## Version Constraints

### API Version

ArcScrollBar is **API 12+ only** component:
- Introduced for circular/smart watch interfaces
- Requires `Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)`
- No legacy (pre-API 12) code path

### Platform Requirements

- Designed for rotary input devices
- Optimized for circular displays
- May not render correctly on rectangular screens without proper container sizing

## Related Components

- **ScrollBarPattern**: Base class with all scroll logic
- **ScrollBar**: Base inner class for rectangular scrollbar
- **ArcScrollBar**: Inner class for arc geometry (extends ScrollBar)
- **ArcScrollBarOverlayModifier**: Arc rendering modifier
- **ArcRound**: Geometry primitive for arc representation
- **ArcScrollPattern**: Pattern for arc scrollable containers

## References

- Parent component CLAUDE.md: `../scroll_bar/CLAUDE.md`
- Inner ArcScrollBar: [../arc_scroll/inner/arc_scroll_bar.h](../arc_scroll/inner/arc_scroll_bar.h)
- ArcRound geometry: [../../../../base/geometry/arc_round.h](../../../../base/geometry/arc_round.h)
- Root CLAUDE.md: `../../../../CLAUDE.md`
