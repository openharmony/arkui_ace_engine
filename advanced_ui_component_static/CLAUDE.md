# Advanced UI Component Static

This document contains specialized rules for the Advanced UI Component Static directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Overview

Advanced UI Component Static provides pre-compiled advanced UI components in ArkTS bytecode (.abc) format. Components are published as pre-compiled bytecode that can be imported and used directly without compilation.

**Component Types**:
- Basic interactive components (Chip, Counter, SegmentButton)
- Layout containers (FoldSplitContainer, Popup)
- Device-specific components (ArcButton, ArcSlider for wearables)
- Composite components (Dialog, ToolBar, SubHeader)

---

## Component Structure

### Component Directory Layout

Each component follows this structure:

```
{component}/
├── @ohos.arkui.advanced.{ComponentName}.ets   # Main component implementation
├── BUILD.gn                                    # Build configuration
├── ets/                                        # Additional ets files (if any)
├── src/                                        # C++ ANI backend (rare, only FormMenu)
└── test/                                       # Component tests
```

### Bytecode Generation Pipeline

```
ArkTS Source (.ets)
    ↓
Ets2ABC Compiler
    ↓
Bytecode (.abc)
    ↓
Install to /system/framework/
    ↓
Runtime Loading
    ↓
Available in @ohos.arkui.advanced.* namespace
```

---

## Device Adaptation

### Build Configuration

The main [BUILD.gn](BUILD.gn) controls which components are compiled based on device type:

```python
# Wearable devices (ace_engine_feature_wearable=true)
if (ace_engine_feature_wearable) {
    deps = [ "assembled_advanced_ui_component:assembledAdvanced" ]
} else {
    # All other devices
    deps = [
        "arcbutton:arcbutton_ets_abc",
        "arcslider:arcslider_ets_abc",
        # ... other components
        "assembled_advanced_ui_component:assembledAdvanced",
    ]
}
```

### Device-Specific Components

| Component | Target Device | Special Requirements |
|-----------|--------------|---------------------|
| ArcButton | Watch only | Circular geometry calculation |
| ArcSlider | Watch only | Edge interaction |
| FoldSplitContainer | Foldable only | 3-state layout |
| MultiNavigation | Foldable only | Multi-device adaptation |

**Constraints**:
- Always check `deviceInfo.deviceType` before using device-specific components
- Use `ace_engine_feature_wearable` build flag for conditional compilation

---

## Responsibilities

### This Module Handles

- **Pre-compiled component delivery**: Components published as .abc bytecode
- **Component implementation**: ArkTS source code for each component
- **Build orchestration**: GN configurations for bytecode generation
- **Device adaptation**: Conditional compilation based on device type
- **Version management**: V1/V2 component versions (e.g., Dialog vs DialogV2)

### This Module Does NOT Handle

- Runtime component instantiation → Handled by ACE Engine Core
- Component rendering → Handled by Rosen/Skia backend
- Layout algorithms → Implemented in components_ng/pattern/
- State management → Handled by declarative_frontend

---

## Special Cases

### FormMenu: The Only Component with C++ Backend

**Uniqueness**: FormMenu is the **only** component with a C++ ANI backend.

```
ArkTS Layer: @ohos.arkui.advanced.FormMenu.ets
    ↓ requestPublishFormWithSnapshot()
C++ Layer: formmenu.cpp
    ↓ FormMgr::GetInstance().RequestPublishFormWithSnapshot()
System: Form Management Service
```

**Key files**:
- ArkTS: [formmenu/ets/arkui.FormMenu.formMenuItem.ets](formmenu/ets/arkui.FormMenu.formMenuItem.ets)
- C++: [formmenu/src/formmenu.cpp](formmenu/src/formmenu.cpp:223-240)

**Constraints**:
- Must link against libformmenu_ani.so
- ANI method signatures must match between ArkTS and C++
- Requires form management system service

### Component Versions

**V1 vs V2 Components**:
- DialogV2, ToolBarV2, SubHeaderV2, ProgressButtonV2
- V2 versions provide enhanced functionality
- Prefer V2 for new code

**Migration Guidance**:
- V1 components maintained for backward compatibility
- New features added to V2 versions only
- Check component documentation for version-specific APIs

---

## Theme and Styling

### System Resources

Components use system resources for theming:

```typescript
$r('sys.color.ohos_id_color_primary')
$r('sys.color.ohos_id_color_background')
$r('sys.color.ohos_id_color_foreground')
```

### Style Modes

Most components support multiple style modes:

```typescript
// ArcButton example
ArcButtonStyleMode.EMPHASIZED_LIGHT
ArcButtonStyleMode.EMPHASIZED_DARK
ArcButtonStyleMode.NORMAL
```

**Constraints**:
- Always use system resource references
- Avoid hardcoding color values
- Support both light and dark themes

---

## Common Pitfalls

### 1. Missing Build Dependencies

**Problem**: New component added but not compiled

**Wrong**:
```python
# Created newcomponent/ but forgot to add to BUILD.gn
```

**Correct**:
```python
# In main BUILD.gn
deps = [
    # ...
    "newcomponent:newcomponent_ets_abc",  # Add this
]
```

**Check**: Verify [BUILD.gn:17-39](BUILD.gn#L17-L39) deps list

### 2. Device Type Mismatch

**Problem**: Using watch-specific components on phone/tablet

**Wrong**:
```typescript
// Will fail on non-watch devices
import { ArcButton } from '@ohos.arkui.advanced.ArcButton';
```

**Correct**:
```typescript
import deviceInfo from '@ohos.deviceInfo';

if (deviceInfo.deviceType === 'wearable') {
    import { ArcButton } from '@ohos.arkui.advanced.ArcButton';
}
```

### 3. FormMenu ANI Mismatch

**Problem**: ANI method signature mismatch between ArkTS and C++

**Check**:
- ArkTS signature: [formmenu/ets/arkui.FormMenu.formMenuItem.ets](formmenu/ets/arkui.FormMenu.formMenuItem.ets)
- C++ signature: [formmenu/src/formmenu.cpp](formmenu/src/formmenu.cpp)
- Parameter types and count must match exactly

### 4. Incorrect Component Version

**Problem**: Using deprecated V1 component instead of V2

**Wrong**:
```typescript
import { Dialog } from '@ohos.arkui.advanced.Dialog';  // V1
```

**Correct**:
```typescript
import { DialogV2 } from '@ohos.arkui.advanced.Dialog';  // V2
```

### 5. Hardcoded Theme Colors

**Wrong**:
```typescript
backgroundColor: '#FFFFFF'  // Hardcoded
```

**Correct**:
```typescript
backgroundColor: $r('sys.color.ohos_id_color_background')
```

---

## Build System

### Component BUILD.gn Template

```python
import("//build/ohos/ace/ace.gni")

ets_abc("componentname_ets_abc") {
  sources = [ "@ohos.arkui.advanced.ComponentName.ets" ]

  deps = [
    "//foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend:bridge_declare",
  ]

  external_dep = [ "cfr_utils:ets_compiler" ]

  component_name = "componentname"
  subsystem_name = "arkui"
  part_name = "ace_engine"
}
```

### Build Output

Bytecode files are installed to:
- Build output: `out/<product>/arkui/ace_engine/`
- Runtime path: `/system/framework/`

**Output file naming**: `{componentname}_ets_abc.abc`

---

## Component Reference

### Quick Lookup Table

| Component | Import Path | Device | Type |
|-----------|-------------|--------|------|
| ArcButton | @ohos.arkui.advanced.ArcButton | Watch | Button |
| ArcSlider | @ohos.arkui.advanced.ArcSlider | Watch | Slider |
| Chip | @ohos.arkui.advanced.Chip | All | Tag |
| ChipGroup | @ohos.arkui.advanced.ChipGroup | All | Container |
| Counter | @ohos.arkui.advanced.Counter | All | Input |
| DownloadFileButton | @ohos.arkui.advanced.DownloadFileButton | All | Button |
| FoldSplitContainer | @ohos.arkui.advanced.FoldSplitContainer | Foldable | Layout |
| FormMenu | @ohos.arkui.advanced.FormMenu | All | Menu |
| FullScreenLaunch | @ohos.arkui.advanced.FullScreenLaunch | All | Page |
| MultiNavigation | @ohos.arkui.advanced.MultiNavigation | Foldable | Navigation |
| Popup | @ohos.arkui.advanced.Popup | All | Overlay |
| SegmentButton | @ohos.arkui.advanced.SegmentButton | All | Button |
| SelectionMenu | @ohos.arkui.advanced.SelectionMenu | All | Menu |

### Assembled Components

Composite components in [assembled_advanced_ui_component/](assembled_advanced_ui_component/):

- Dialog / DialogV2
- ToolBar / ToolBarV2
- SubHeader / SubHeaderV2
- ProgressButton / ProgressButtonV2

---

## Dependencies

### Upstream Dependencies

- **@ohos.arkui.component** - Base component library
- **@ohos.arkui.stateManagement** - State management framework
- **@kit.ArkGraphics2D** - 2D graphics library (ArcSlider dependency)
- **@kit.SensorServiceKit** - Sensor services (vibration feedback)

### Downstream Consumers

- Application layer ArkTS code
- Form (card) applications
- Atomic services

---

## File Naming Conventions

### Source Files

- Main component: `@ohos.arkui.advanced.{ComponentName}.ets`
- Additional files: `{descriptive_name}.ets`

### Bytecode Files

- Output name: `{componentname}_ets_abc.abc`
- All lowercase with underscore separator
- Matches BUILD.gn target name

### Export Names

- Namespace: `@ohos.arkui.advanced.*`
- Class name: `{ComponentName}`
- Options class: `{ComponentName}Options`

---

## Key Implementation Details

### ArcButton Geometry Calculation

**Flow**:
```
ArcButton({ options })
    ↓
DataProcessUtil.calculate() (geometry)
    ↓ Source: [@ohos.arkui.advanced.ArcButton.ets:280-320](arcbutton/@ohos.arkui.advanced.ArcButton.ets)
findCircleIntersections() (circle-line intersection)
    ↓
generatePath() (SVG path string)
    ↓
PathShape().commands() (rendering)
```

**Key Methods**:
- `DataProcessUtil.calculate()` - Main geometry calculation
- `findCircleIntersections()` - Circle-line intersection algorithm
- `generatePath()` - SVG path generation

### Popup Positioning

**Supported Directions**: 8 directions with arrows

```
        Top
TopLeft    |    TopRight
           |
Left-------Popup-------Right
           |
BottomLeft |    BottomRight
       Bottom
```

**Constraints**:
- Arrow position calculated automatically
- Avoids viewport boundaries
- Supports touch-outside-to-dismiss

---

## Testing

### Component Testing

Each component should have tests in `test/` subdirectory:

```typescript
// Example test structure
test/
├── ArcButton.test.ets
├── ChipGroup.test.ets
└── DialogV2.test.ets
```

### Integration Testing

Components should be tested in real application scenarios:
- Device-specific components on target devices
- Theme switching (light/dark)
- Different screen sizes
- Accessibility features

---

## Migration from Legacy Components

When migrating from legacy components to advanced components:

1. Update import paths
2. Replace options objects with new API
3. Update event handlers
4. Test on target devices
5. Verify theme compatibility

**Example**:
```typescript
// Legacy
Button({ label: 'Click', onClick: () => {} })

// Advanced
import { Button } from '@ohos.arkui.advanced.Button';
const options = new ButtonOptions({
  label: 'Click',
  onClick: () => {}
});
Button({ options: options })
```

---

## Summary

**Core Principles**:
1. Components are pre-compiled bytecode - no source modification at runtime
2. Device-specific components require device type checking
3. Always use system resources for theming
4. Prefer V2 components for new code
5. FormMenu is the only component with C++ backend
6. Follow build system templates for new components

**Before adding new components**:
- Check if similar component already exists
- Verify target device support
- Follow BUILD.gn template
- Include tests
- Document API usage
