# Examples Directory Knowledge Base

> **Document Version**: v1.0
> **Update Time**: 2026-02-03
> **Source Code Version**: OpenHarmony ace_engine
> **Parent**: `../CLAUDE.md` (Root ace_engine documentation)

---

## Table of Contents

1. [Overview](#overview)
2. [Directory Structure](#directory-structure)
3. [Purpose and Usage](#purpose-and-usage)
4. [Component Previews App](#component-previews-app)
5. [Independent Component Tests](#independent-component-tests)
6. [Development Guidelines](#development-guidelines)
7. [Testing Guidelines](#testing-guidelines)
8. [Build and Run](#build-and-run)
9. [Common Patterns](#common-patterns)

---

## Overview

### Directory Position

The `examples/` directory contains **sample applications and test cases** for demonstrating and validating ACE Engine component functionality. These are **NOT part of the core framework code**, but rather serve as:

1. **Component Preview Application** (`components/`) - A comprehensive app for visually previewing all ArkUI components
2. **Independent Test Apps** (`Menu/`, `ScrollableComponentTest/`, etc.) - Focused test applications for specific components
3. **Feature Demonstrations** - Examples showing specific features and capabilities

### Key Characteristics

- **Language**: Primarily ArkTS (TypeScript-based)
- **Build System**: Hvigor (OpenHarmony build tool)
- **Target Platform**: OpenHarmony devices (API 12+)
- **Purpose**: Demonstration, validation, and testing of ACE Engine components

### What This Directory Is NOT

- ❌ **Not** part of the core ACE Engine framework code
- ❌ **Not** production code that gets packaged into the final SDK
- ❌ **Not** subject to the same strict API stability requirements as `frameworks/`
- ❌ **Not** automatically tested by the framework's build system

---

## Directory Structure

```
examples/
├── components/                      # Main component preview application
│   ├── common/                      # Shared UI components and utilities
│   │   ├── src/main/ets/
│   │   │   ├── components/         # Reusable UI blocks (Block, ColorBlock, etc.)
│   │   │   ├── model/               # Custom modifiers and models
│   │   │   ├── utils/               # Utility functions
│   │   │   └── pages/               # Common pages
│   │   ├── src/test/                # Unit tests
│   │   └── src/ohosTest/            # UI tests
│   ├── feature/                     # Component feature modules (by category)
│   │   └── src/main/ets/components/
│   │       ├── CompAccessibilityBlocks.ets
│   │       ├── CompBackgroundBlocks.ets
│   │       └── ... (60+ component blocks)
│   ├── entry/                       # Main application entry
│   │   └── src/main/ets/
│   │       ├── entryability/        # Application abilities
│   │       └── pages/               # Main pages
│   └── README_zh.md                 # Component preview app documentation
│
├── Menu/                           # Independent Menu component test app
│   ├── entry/                       # Application entry
│   └── AppScope/                   # App-level resources
│
├── ScrollableComponentTest/         # Scrollable component tests
│   └── entry/
│
├── ScrollableComponentStatic/       # Static scrollable tests
│   └── entry/
│
├── Accessibility/                   # Accessibility feature demos
├── BindSheet/                       # BindSheet component demos
├── ContainerModalToolbar/           # Modal toolbar demos
├── Dialog_C/                        # C-language Dialog demos
├── DrawableDescriptor/              # Drawable descriptor demos
├── Image/                           # Image component demos
├── Image_C/                         # C-language Image demos
├── ImageAnimator/                   # ImageAnimator component demos
├── Info/                            # Info component demos
├── LayoutSample/                    # Layout algorithm samples
├── Navigation/                      # Navigation component demos
├── NewMaterial/                     # New material design demos
├── Overlay/                         # Overlay component demos
├── Picker/                          # Picker component demos
├── PickerDialog/                    # PickerDialog demos
├── Progress/                        # Progress component demos
├── Reusable/                        # Reusable component demos
├── Select/                          # Select component demos
├── StrengthenTest/                  # Strength/stress tests
├── TextComponentTest/               # Text component tests
├── TextInputComponentTest/          # TextInput component tests
├── UIExtension/                     # UI extension demos
└── XComponent/                      # XComponent demos
```

---

## Purpose and Usage

### Primary Purposes

1. **Component Validation**
   - Verify that ACE Engine components render correctly on actual devices
   - Test component behaviors under various conditions
   - Validate property settings and event handling

2. **UX Reference**
   - Provide standard UX patterns for component usage
   - Demonstrate best practices for component styling
   - Show proper event handling patterns

3. **Development Aid**
   - Help developers understand component APIs
   - Provide starting points for new feature implementations
   - Serve as regression test bed for framework changes

### Intended Users

- **ACE Engine Developers** - Validate framework changes don't break components
- **Application Developers** - Reference for correct component usage
- **QA/Testing Teams** - Verify component functionality on devices

---

## Component Previews App

### Overview

The `components/` subdirectory contains a comprehensive **ArkUI Component Preview Application** that allows users to:

1. Browse all available ArkUI components
2. Adjust component properties in real-time
3. View immediate visual feedback on devices
4. Test component events and callbacks

### Architecture

```
components/
├── common/ (基础层 Base Layer)
│   ├── 公共组件: Block, ColorBlock, IconPalette, RadioBlock
│   ├── 公共工具: timeUtil, route management
│   └── 基础数据: Component data base classes
│
├── feature/ (业务层 Business Layer)
│   └── 60+ Component Blocks organized by category
│       ├── CompAccessibilityBlocks.ets
│       ├── CompBackgroundBlocks.ets
│       ├── CompBorderBlocks.ets
│       └── ... (按 ArkUI 组件分类 by ArkUI component categories)
│
└── entry/ (UI 层 UI Layer)
    ├── 组件导航页 Component Navigation Page
    └── 组件预览页 Component Preview Page
```

### Component Categories

The preview app organizes components into these categories:

1. **行列与堆叠** - Flex, Column, Row, Stack, RelativeContainer, FolderStack
2. **栅格与分栏** - GridRow, GridCol, ColumnSplit, RowSplit, SideBarContainer
3. **滚动与滑动** - List, Grid, Scroll, Swiper, WaterFlow, Refresh
4. **导航与切换** - Navigation, Stepper, Tabs
5. **按钮与选择** - Button, Toggle, Checkbox, DatePicker, Slider, Select
6. **文本与输入** - Text, TextInput, TextArea, RichEditor, Search
7. **图片与视频** - Image, ImageAnimator
8. **信息展示** - Gauge, Progress, DataPanel, QRCode, LoadingProgress
9. **空白与分隔** - Blank, Divider
10. **菜单** - Menu, MenuItem, MenuItemGroup
11. **弹窗** - AlertDialog, ActionSheet, CustomDialog, BindSheet, BindPopup

### Navigation Pattern

```
Main Entry (Navigation)
    ↓
Component List Page (select component)
    ↓
Component Preview Page (NavDestination)
    ↓
Property Settings Panel (overlay)
```

### Key Features

1. **Real-time Property Adjustment**
   - Modify properties via UI controls (sliders, checkboxes, etc.)
   - See immediate visual feedback
   - Property blocks from `common/` ensure consistent UI

2. **Event Logging**
   - Component events are captured and displayed on screen
   - Helps developers understand event flow
   - Useful for debugging event handling

3. **Common Blocks**
   - `Block.ets` - Base block for property groups
   - `ColorBlock.ets` - Color picker block
   - `RadioBlock.ets` - Radio button group
   - `IconPalette.ets` - Icon selection palette

### Adding New Components

To add a new component to the preview app:

1. **Create Component Block** in `feature/`:
   ```typescript
   // feature/src/main/ets/components/CompMyComponentBlocks.ets
   import { Block } from '@ohos/common';
   import { MyComponent } from '@ohos/my-component';

   @Builder
   function MyComponentBlock() {
     Block({ title: 'My Component' }) {
       // Property controls
     }
   }
   ```

2. **Register in Route Group**:
   ```typescript
   // entry/src/main/ets/pages/Index.ets
   const RouteGroup: ComponentInfo[] = [
     // ... existing components
     {
       title: 'MyComponent',
       builder: MyComponentPage,
       path: 'my-component'
     }
   ];
   ```

3. **Create Preview Page**:
   ```typescript
   @Builder
   function MyComponentPage() {
     Column() {
       MyComponent(/* properties */)
     }
   }
   ```

---

## Independent Component Tests

### Purpose

Independent test applications (e.g., `Menu/`, `ScrollableComponentTest/`) provide:

1. **Focused Testing** - Single component, comprehensive test scenarios
2. **Regression Testing** - Validate framework changes don't break specific components
3. **Performance Testing** - Measure component performance under load
4. **Edge Case Testing** - Test unusual or boundary conditions

### Structure Pattern

Most independent test apps follow this structure:

```
ComponentNameTest/
├── entry/
│   └── src/main/ets/
│       ├── entryability/
│       │   └── EntryAbility.ets       # App entry point
│       └── pages/
│           └── Index.ets              # Main test page
├── AppScope/
│   └── resources/                     # App resources
├── build-profile.json5                # Build configuration
├── hvigorfile.ts                      # Build script
└── oh-package.json5                   # Package metadata
```

### Example: Menu Component Test

```typescript
// entry/src/main/ets/pages/Index.ets
@Entry
@Component
struct Index {
  @State menuVisible: boolean = false;

  build() {
    Column() {
      Button('Show Menu')
        .onClick(() => {
          this.menuVisible = true;
        })

      if (this.menuVisible) {
        Menu() {
          MenuItem({ content: 'Option 1' })
          MenuItem({ content: 'Option 2' })
        }
      }
    }
  }
}
```

---

## Development Guidelines

### When to Modify Examples

**Appropriate modifications**:
- ✅ Adding new component preview pages
- ✅ Fixing bugs in example code
- ✅ Adding test cases for new framework features
- ✅ Updating examples for API changes
- ✅ Improving UX/UI of the preview app

**Inappropriate modifications**:
- ❌ Testing unreleased framework features
- ❌ Creating production applications in examples/
- ❌ Adding examples that demonstrate anti-patterns
- ❌ Modifying examples to bypass framework bugs (report bugs instead)

### Code Style

Examples should follow:
- [JavaScript Language Common Programming Guide](https://gitee.com/openharmony/docs/blob/master/zh-cn/contribute/OpenHarmony-JavaScript-coding-style-guide.md)
- [OpenHarmony Application TS&JS Programming Guide](https://gitee.com/openharmony/docs/blob/master/zh-cn/contribute/OpenHarmony-Application-Typescript-JavaScript-coding-guide.md)

### Component Preview App Guidelines

1. **Use Common Blocks**
   - Always use property blocks from `common/src/main/ets/components/`
   - Ensures consistent UI across all component previews

2. **Follow Naming Conventions**
   - Component block: `Comp[ComponentName]Blocks.ets`
   - Preview page: `[ComponentName]Page.ets`

3. **Document Events**
   - Display event information on screen
   - Use clear, readable event logging format

4. **Support Multiple Scenarios**
   - Show basic usage
   - Show advanced features
   - Show edge cases

---

## Testing Guidelines

### Unit Tests (Component Preview App)

Location: `common/src/test/`, `entry/src/test/`

**Coverage Target**: 80-90%

**Pattern**:
```typescript
describe('ComponentName', () => {
  it('should test property', () => {
    // Arrange
    // Act
    // Assert
  });
});
```

### UI Tests

Location: `common/src/ohosTest/`, `entry/src/ohosTest/`

**Test Steps**:
1. Enter component
2. Open property settings UI
3. Locate corresponding property block
4. Perform settings
5. Assert results

**Assertion Patterns**:
```typescript
// For properties accessible via @ohos.UiTest
expect(actualValue).assertEqual(expectedValue);

// For properties not accessible via @ohos.UiTest
// Setting success is sufficient
```

### Test Coverage Requirements

- **Component Previews App**: 80-90% UI test coverage
- **Independent Test Apps**: Scenario-based coverage (not percentage-based)

---

## Build and Run

### Building Examples

Examples are **separate applications** built independently of the core ACE Engine:

```bash
# From the examples/[component-name] directory
hvigorw clean
hvigorw assembleHap

# Or from OpenHarmony root (if integrated into manifest)
./build.sh --product-name <product> --build-target examples/components
```

### Running on Device

1. **Install HAP**:
   ```bash
   hdc install examples/components/entry/build/default/outputs/default/entry-default-signed.hap
   ```

2. **Launch Application**:
   ```bash
   hdc shell aa start -a <entry_name> -b <bundle_name>
   ```

### Debugging

```bash
# View logs
hdc shell hilog | grep examples

# Clear logs
hdc shell hilog -r
```

---

## Common Patterns

### Property Block Pattern

```typescript
// feature/src/main/ets/components/CompExampleBlocks.ets
import { Block } from '@ohos/common';

@Builder
function ExamplePropertyBlock() {
  Block({ title: 'Property Name' }) {
    // UI control for property
    Slider({
      min: 0,
      max: 100,
      value: this.propertyValue,
      step: 1
    })
      .onChange((value: number) => {
        this.propertyValue = value;
      })
  }
}
```

### Event Logging Pattern

```typescript
@Component
struct ComponentPreview {
  @State eventLog: string[] = [];

  logEvent(eventName: string, data: any) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLog.unshift(`${timestamp}: ${eventName} - ${JSON.stringify(data)}`);
  }

  build() {
    Column() {
      // Component with events
      Button('Test')
        .onClick(() => {
          this.logEvent('onClick', { target: 'Button' });
        })

      // Event log display
      List({ space: 8 }) {
        ForEach(this.eventLog, (log: string) => {
          ListItem() {
            Text(log)
          }
        })
      }
    }
  }
}
```

### Navigation Page Pattern

```typescript
@Builder
export function ComponentExamplePage() {
  NavDestination() {
    Column() {
      // Component preview
      ComponentPreview()

      // Property settings button
      Button('Settings')
        .position({ x: '90%', y: '10%' })
        .onClick(() => {
          // Open property panel
        })
    }
  }
  .title('Component Example')
  .hideTitleBar(false)
}
```

---

## Important Notes

### API Version

- Examples support **API 12** and above
- Verify API compatibility before adding new features

### Resource Management

- All resources (images, strings, etc.) should be in appropriate resource directories
- Use resource references (`$r('app.media.icon')`) for better localization support

### Dependencies

- Avoid adding unnecessary dependencies
- Prefer using ACE Engine built-in components over third-party libraries
- Document any special build requirements in README

### Version Control

- Follow the [Community Contribution Guidelines](https://gitee.com/openharmony/applications_app_samples/blob/master/CodeCommitChecklist.md)
- Ensure all code is committed to the correct branch
- Run tests before submitting changes

---

## File References

| File | Description |
|------|-------------|
| [components/README_zh.md](examples/components/README_zh.md) | Component preview app documentation (Chinese) |
| [common/src/main/ets/components/Block.ets](examples/components/common/src/main/ets/components/Block.ets) | Base property block component |
| [entry/src/main/ets/entryability/EntryAbility.ets](examples/components/entry/src/main/ets/entryability/EntryAbility.ets) | Application entry point |

---

## Summary

**Core Principles**:
1. **Examples are for demonstration, not production** - Show best practices, don't over-engineer
2. **Keep examples current** - Update when APIs change
3. **Use common components** - Leverage reusable blocks in `common/`
4. **Document well** - Clear comments and README files
5. **Test thoroughly** - Maintain high test coverage for reliable component validation

**Remember**: The `examples/` directory serves as the face of ACE Engine components for developers and testers. Examples should be:
- Easy to understand
- Quick to run
- Accurate representations of component capabilities
- Following best practices
- Well-maintained and up-to-date

---

*For Chinese version, see [CLAUDE-CN.md](examples/CLAUDE-CN.md)* (to be created)
