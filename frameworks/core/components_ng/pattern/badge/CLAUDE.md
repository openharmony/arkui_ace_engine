# Badge Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the Badge component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [Badge_Knowledge_Base_CN.md](../../../docs/pattern/badge/Badge_Knowledge_Base_CN.md)

---

## Overview

**Badge** is a marker component that attaches dots, numbers, or text markers to components. Common use cases: notification counts, status indicators.

**Architecture**: NG Pattern → BadgePattern → BadgeLayoutAlgorithm

**Key Features**:
- Number/text markers (count mode, value mode)
- Multiple positions (RightTop, Right, Left, custom X/Y)
- Style customization (colors, font size, borders)
- MaxCount limit (default 99, displays "99+")
- Elderly mode adaptation (fontSizeScale >= 1.75)
- RTL layout support

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `badge_pattern.h/cpp` | ~550 | Pattern layer - OnModifyDone, theme updates, Text child node management |
| `badge_layout_algorithm.h/cpp` | ~400 | Layout measurement and positioning |
| `badge_layout_property.h` | ~200 | All Badge properties (BadgeValue, BadgeCount, BadgeColor, etc.) |
| `badge_model_ng.h/cpp` | ~200 | Frontend bridge - Create(), CreateByFrameNode() |
| `badge_data.h` | ~80 | BadgeParameters struct definition |
| `badge_theme.h` | ~50 | Theme defaults (BadgeTheme) |

**Path**: `frameworks/core/components_ng/pattern/badge/`

---

## Core Class Hierarchy

```
                    Pattern
                       ↑
                BadgePattern
                (badge_pattern.h)
                       |
        +--------------+--------------+
        |              |              |
  LayoutProperty  LayoutAlgorithm  AccessibilityProperty
        ↑              ↑                    ↑
BadgeLayoutProperty  BadgeLayoutAlgorithm  BadgeAccessibilityProperty
```

---

## Key Properties

### Content Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `BadgeCount` | int | - | Number marker (Badge hidden if count <= 0) |
| `BadgeValue` | string | - | Text marker |
| `BadgeMaxCount` | int | 99 | Maximum count before showing "99+" |

### Position Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `BadgePosition` | BadgePosition | RightTop | Preset position |
| `BadgePositionX` | Dimension | 0vp | Custom X offset |
| `BadgePositionY` | Dimension | 0vp | Custom Y offset |

### Style Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `BadgeColor` | Color | Red | Background color |
| `BadgeTextColor` | Color | White | Text color |
| `BadgeFontSize` | Dimension | 10vp | Font size (16vp in elderly mode) |
| `BadgeCircleSize` | Dimension | 16vp | Circle diameter (24vp in elderly mode) |

**User Set Flags**: `BadgeColorByuser`, `BadgePositionXByuser` - prevent theme updates from overriding user values

---

## Common Operations

### Setting Badge Content

```cpp
// Number marker
layoutProperty->UpdateBadgeCount(5);

// Text marker
layoutProperty->UpdateBadgeValue("NEW");

// With maxCount
layoutProperty->UpdateBadgeMaxCount(99);  // Shows "99+" when exceeded
```

### Setting Badge Style

```cpp
// Color
layoutProperty->UpdateBadgeColor(Color::RED);
layoutProperty->UpdateBadgeTextColor(Color::WHITE);

// Size
layoutProperty->UpdateBadgeFontSize(Dimension(10, DimensionUnit::VP));
layoutProperty->UpdateBadgeCircleSize(Dimension(16, DimensionUnit::VP));

// Position
layoutProperty->UpdateBadgePosition(BadgePosition::RIGHT_TOP);
layoutProperty->UpdateBadgePositionX(Dimension(20, DimensionUnit::VP));
layoutProperty->UpdateBadgePositionY(Dimension(-10, DimensionUnit::VP));
```

### Creating Badge Programmatically

```cpp
// In Model layer
auto frameNode = FrameNode::GetOrCreateFrameNode(
    V2::BADGE_ETS_TAG, nodeId,
    []() { return AceType::MakeRefPtr<BadgePattern>(); });

auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
layoutProperty->UpdateBadgeCount(5);
layoutProperty->UpdateBadgePosition(BadgePosition::RIGHT_TOP);
```

---

## Important Implementation Details

### 1. Badge Uses Text Child Node Internally

**Source**: `badge_pattern.cpp:30-49`

Badge creates a **Text node** as its child to display content (not direct drawing):

```cpp
// Create Text child node for Badge content
lastFrameNode = FrameNode::GetOrCreateFrameNode(
    V2::TEXT_ETS_TAG, textNodeId_,
    []() { return AceType::MakeRefPtr<TextPattern>(); });
lastFrameNode->MountToParent(frameNode);
```

**Why**: Reuses Text's rendering, styling, and accessibility capabilities

### 2. Badge Visibility Logic

**Source**: `badge_pattern.cpp:57-86`

Badge is **hidden** when:
- `badgeCount <= 0` (or not set)
- `badgeValue` is empty (or not set)

```cpp
bool badgeVisible = false;
if (badgeCount.has_value() && badgeCount.value() > 0) {
    badgeVisible = true;
} else if (badgeValue.has_value() && !badgeValue.value().empty()) {
    badgeVisible = true;
}
textRenderContext->SetVisible(badgeVisible);
```

### 3. Elderly Mode Threshold

**Source**: `badge_layout_algorithm.cpp:88`

```cpp
const double AGE_FONT_SIZE_SCALE = 1.75;
```

When `fontSizeScale >= 1.75`:
- `badgeAgeFontSize` (16vp) instead of `badgeFontSize` (10vp)
- `badgeAgeCircleSize` (24vp) instead of `badgeCircleSize` (16vp)

### 4. RTL Layout Support

**Source**: `badge_layout_algorithm.cpp:166-191`

In RTL mode:
- `BadgePosition::RIGHT_TOP` positions Badge at **top-left** instead of top-right

### 5. Theme Update Behavior

**Source**: `badge_pattern.cpp:494-538`

When theme changes, **only user-unset properties** are updated:

```cpp
// Check user-set flags before updating
if (!layoutProperty->GetBadgeColorByuser().value_or(false)) {
    UpdateBadgeColor(badgeTheme->GetBadgeColor());
}
```

---

## BadgePosition Enum

```cpp
enum class BadgePosition {
    RIGHT_TOP,   // Top-right corner (default)
    RIGHT,       // Right side vertical center
    LEFT         // Left side vertical center
};
```

---

## ArkTS API Reference

```typescript
// Constructor
Badge({ value: string, count: number, maxCount: number, position: BadgePosition })

// Property methods
.badgePosition(value: BadgePosition)
.badgeColor(value: ResourceColor)
.badgeTextColor(value: ResourceColor)
.badgeFontSize(value: number | Resource)
.badgeCircleSize(value: number | Resource)
.badgeBorderWidth(value: number | Resource)
.badgeBorderColor(value: ResourceColor)
.badgePositionX(value: number | Resource)
.badgePositionY(value: number | Resource)
```

---

## Debugging

### Dump Commands

```bash
# View Badge component info
hidumper -s WindowManagerService -a '-a Badge'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'
```

### Log Tag

```cpp
TAG_LOGD(AceLogTag::ACE_BADGE, "BadgeContent: %{public}s", content.c_str());
```

### Common Issues

| Issue | Check |
|-------|-------|
| Badge not displaying | `badgeCount > 0` or `badgeValue` non-empty |
| Position incorrect | Check `badgePosition` and RTL layout direction |
| Style not applied | Check `*Byuser` flags - user values override theme |

---

## Execution Flow

```
Frontend: Badge({ count: 5 }) { Child() }
    ↓
BadgeModelNG::Create()
    ├── Create FrameNode (V2::BADGE_ETS_TAG)
    ├── Create BadgePattern
    └── Apply BadgeParameters
    ↓
BadgePattern::OnModifyDone()
    ├── Create/update Text child node
    ├── Set content (count or value)
    ├── Apply styles
    └── Set visibility
    ↓
BadgeLayoutAlgorithm::Measure()
    ├── Calculate Badge dimensions (circle or capsule)
    ├── Apply elderly mode scaling
    └── Measure child nodes
    ↓
BadgeLayoutAlgorithm::Layout()
    ├── Calculate position based on BadgePosition
    ├── Apply RTL offset
    ├── Apply custom X/Y offset
    └── Layout child nodes
    ↓
Render Display
```

---

## References

- **Knowledge Base**: [Badge_Knowledge_Base_CN.md](../../../docs/pattern/badge/Badge_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **Theme**: `frameworks/core/components/badge/badge_theme.h`
- **Related**: Text component (Badge uses Text internally)
