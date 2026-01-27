# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Knowledge Base

This project maintains a comprehensive knowledge base for in-depth component analysis and development guidance:

### Component Knowledge Base

- **[Menu Component Knowledge Base](docs/pattern/menu/Menu_Knowledge_Base.md)** - Complete guide for Menu component
  - Legacy Menu vs NG Menu architecture comparison
  - JS bridge integration (JsBindMenu, JsBindContextMenu)
  - Pattern/Model/Property/Algorithm layer analysis
  - Lifecycle management and event handling
  - Layout algorithms and paint methods
  - Test coverage and debugging guides

**Usage**: When user asks about Menu-related functionality (menu creation, binding, events, layout, styling, testing), **automatically reference** the Menu Knowledge Base for comprehensive information.

### Skills & Guidelines

- **[TDD Writing Guidelines](.claude/skills/tdd/)** - Test-driven development best practices
  - 7 core principles for TDD
  - Test templates and examples
  - Common pitfalls and solutions
  - Mandatory self-checklist

**Usage**: When writing unit tests or TDD test cases, reference this guide for standardized testing practices.

## Core Working Principles

### 1. Code Verification: Actual Code Only

When answering questions about ace_engine code:

- **Always provide actual code from the repository**
  - Use Read/Grep tools to locate and read actual source code
  - Reference complete file paths when mentioning code (e.g., `frameworks/core/xxx/yyy.cpp:123`)
  - Never guess or fabricate code implementations

- **Missing information triggers user feedback**
  - If required code is not found in ace_engine, explicitly state: "此代码在 ace_engine 中未找到"
  - Do not make assumptions or write hypothetical code
  - Ask user to provide the missing implementation

**Example**:

```cpp
// ✅ Correct: Read actual source
// Source: frameworks/core/components_ng/pattern/menu/menu_pattern.cpp:123
Size GetSubWindowSize(int32_t parentContainerId, uint32_t displayId)
{
    auto finalDisplayId = displayId;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDisplayById(displayId);
    // ... actual implementation
}

// ❌ Wrong: Fabricated code
// Do not write hypothetical implementations without verification
```

### 2. Speculation Management

When dealing with uncertain or incomplete information:

- **Explicitly label speculation**
  - Clearly mark any unverified content as: "推测" (speculation)
  - Provide reasoning for the speculation when possible
  - Request user confirmation for speculative statements

- **Verify before implementation**
  - If speculating about behavior, first use Grep/Read to verify
  - If implementation is not found in ace_engine, ask user to provide it
  - Never implement based on speculation alone

**Example**:

```markdown
✅ Correct:
基于 menu_pattern.cpp:123 的分析，推测 OnModifyDone 在以下情况下会被调用...（推测）

❌ Wrong:
OnModifyDone 会在以下情况下调用...（未标注推测）
```

### 3. Code Logic Verification: Code Over Suggestions

When receiving suggestions or corrections:

- **Verify suggestions against actual code**
  - User suggestions about code logic may be incorrect
  - Always verify with Read/Grep tools before accepting suggestions
  - Base conclusions on actual code behavior, not assumptions

- **Evidence-based reasoning**
  - When user questions code behavior, analyze actual implementation
  - Use "代码为准原则" (Code-first principle)
  - Provide evidence from source code to support or refute suggestions

**Example**:

```
User: "这个函数应该在初始化时调用，对吗？"
Claude: 让我先查看源码验证...
[Read source file]
根据 frameworks/xxx/yyy.cpp:456，该函数实际上是在 OnDirtyLayoutWrapperSwap 时调用，而非初始化时。
```

### 4. Error Learning: Knowledge Base Updates

When errors are corrected by users:

- **Learn from corrections**
  - Document the error and correction in knowledge base
  - Identify root cause of the misunderstanding
  - Add preventive measures to avoid similar errors

- **Update documentation**
  - Create or update knowledge base entries with correct information
  - Reference actual code locations (file:line)
  - Share lessons learned across sessions

**Example**:

```markdown
## Learned Lessons

### Error: Incorrect GetSubWindowSize Branch Coverage
**Date**: 2025-01-27
**Issue**: Assumed defaultDisplay is always available
**Root Cause**: Did not verify Rosen::DisplayManager dependency
**Correction**: User clarified that mock infrastructure is required
**Prevention**: Always verify external dependencies with user before assuming availability
**Reference**: adapter/ohos/entrance/subwindow/subwindow_ohos.cpp:199-243
```

### 5. Knowledge Base Maintenance

When discovering discrepancies between documentation and actual code:

- **Verify actual code first**
  - Use Read/Grep to confirm current implementation
  - Compare documented behavior with actual code

- **Update documentation**
  - Fix incorrect information in knowledge base files
  - Update code references (file paths, line numbers)
  - Ensure all examples match actual code

- **Notify user**
  - Report discovered discrepancies
  - Propose corrections for approval
  - Document the correction after update

**Example**:
```
Discrepancy Found:
Documented: frameworks/xxx/yyy.cpp:299 calls UpdateBorderRadius
Actual: frameworks/xxx/yyy.cpp:303 calls UpdateBorderRadius (after code refactoring)

Action: Updating knowledge base to reflect current code location...
```

## Project Overview

**ACE Engine** (`@ohos/ace_engine`) is the core execution framework for ArkUI applications in OpenHarmony. It provides comprehensive support for applications developed using ArkTS-based declarative development paradigm, delivering complete capabilities from component parsing to rendering.

### Core Capabilities

**Frontend Support**:
- Multiple frontend implementations supporting different language paradigms
- State management framework for reactive data binding
- Component-based architecture with lifecycle management

**Backend Pipeline** (Complete flow):
1. **Component Parsing** - Parse declarative UI descriptions into component trees
2. **Component Building** - Construct component instances and establish relationships
3. **Layout Measurement** - Calculate sizes and positions through layout algorithms
4. **Rendering** - Draw components using graphics engines (Skia/Rosen)

### Frontend Implementations

ACE Engine provides flexible frontend support:

| Frontend | Language | Use Case |
|----------|----------|----------|
| **Declarative Frontend** | ArkTS/TypeScript | Recommended - Modern declarative UI |
| **ArkTS Frontend** | ArkTS staic verison | Incremental engine based frontend |
| **JavaScript Frontend** | JavaScript | Legacy web-style development |

### State Management Framework

Located in `frameworks/bridge/declarative_frontend/state_mgmt/`:
- **AppStorage**: Application-wide state management
- **LocalStorage** | Page-level state management
- **@Watch**: Property observation and reactive updates
- **@Link/@Prop**: Parent-child component data binding

## Build System

This project uses **GN (Generate Ninja)** as the primary build system.

### Building

Build commands are typically run from the OpenHarmony root directory:

```bash
# Configure build (from OpenHarmony root)
./build.sh --product-name <product> --build-target ace_engine

# Common product names: rk3568, ohos-sdk
# Example for rk3568:
./build.sh --product-name rk3568 --build-target ace_engine
```

### Build Targets

Build outputs are located in `out/rk3568/arkui/ace_engine/` and mainly include the following types:

#### 1. Core Engine Libraries (libace*.z.so)
- `libace.z.so` - Main engine library containing only NG_BUILD-configured core UI framework; currently used for compilation monitoring only, not packaged into final images
- `libace_compatible.z.so` - Web-style compatible main engine library supporting legacy APIs; the current core library and primary build output
- `libace_compatible_components.z.so` - Compatible component library; gradually migrating compatible components from libace_compatible to this library for dynamic on-demand loading at runtime
- `libace_engine_pa_ark.z.so` - PA (Particle Ability) engine support
- `libace_ndk.z.so` - NDK interface library
- `libace_form_render.z.so` - Form/card rendering
- `libace_xcomponent_controller.z.so` - XComponent controller
- `libace_*.z.so` - Other specialized sub-libraries

#### 2. Frontend Bridge Libraries
- `libarkts_frontend.z.so` - ArkTS static frontend bridge
- `libcj_frontend_ohos.z.so` - Cangjie frontend bridge

#### 3. Component Libraries (libarkui_*.z.so)
Independent shared libraries for each component, gradually being refactored and separated from the core to support on-demand loading:
- `libarkui_slider.z.so` - Slider component
- `libarkui_checkbox.z.so` - Checkbox component
- And other component libraries...

#### 4. ArkTS Native Interface Libraries (*_ani.so)
Provide bridge interfaces between ArkTS static and Native code:
- `libanimator_ani.so` - Animation Native interface
- `libarkuicustomnode_ani.so` - Custom node interface
- And other *_ani.so libraries

#### 5. Functional Module Libraries (lib*.z.so)
Independent libraries for various API modules:
- `libanimator.z.so` - Animation
- `libdialog.z.so` - Dialog
- `libdragcontroller.z.so` - Drag controller
- And other functional libraries

#### 6. ArkTS Bytecode Files (.abc)
Bytecode files compiled from ArkTS source code, dynamically loaded at runtime:
- `ark*.abc` - Component bytecode (e.g., arkbutton.abc, arkslider.abc)
- `modifier.abc` - Component property modifiers
- `node.abc` - Imperative nodes
- `statemanagement.abc` - State management
- `uicontext.abc` - UI context
- And others

#### 7. Testing Tools
- `rawinput` - Input event testing tool

### Testing

```bash
# Build unit tests
./build.sh --product-name rk3568 --build-target unittest

# Build benchmarks
./build.sh --product-name rk3568 --build-target benchmark_linux

# Run specific test target (from build output directory)
# Tests are located in out/rk3568/tests/ace_engine/
```

Test locations:
- Unit tests: `test/unittest/`
- Benchmarks: `test/benchmark/`
- Component tests: `examples/*/test/`

## Architecture

### System Architecture

ACE Engine follows a layered architecture that separates concerns between frontend language processing and backend rendering:

```
┌─────────────────────────────────────────────────────────┐
│  Application Layer                                      │
│  - ArkTS-based declarative UI applications              │
│  - State management with @Watch/@Link/@Prop            │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Frontend Bridge Layer (frameworks/bridge/)             │
│  - Declarative Frontend: ArkTS/TS declarative UI       │
│  - ArkTS Frontend: ArkTS static support                │
│  - JavaScript Frontend: Legacy JS support              │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Component Framework Layer (frameworks/core/)          │
│  - Components NG: Modern component architecture        │
│  - Pattern: Business logic & lifecycle                 │
│  - Layout: Measurement & positioning algorithms        │
│  - Render: Drawing pipeline                            │
│  - Gestures: User interaction handling                 │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Platform Adapter Layer (adapter/)                     │
│  - OHOS: OpenHarmony platform implementation           │
│  - Preview: Development tool support                   │
└─────────────────────────────────────────────────────────┘
```

### Four-Layer Architecture (Detailed)

1. **Application Layer**: ArkTS-based applications using declarative development paradigm
2. **Frontend Bridge Layer** (`frameworks/bridge/`): Language parsing, state management, component tree building
3. **Component Framework Layer** (`frameworks/core/`): Component parsing, building, layout measurement, rendering
4. **Platform Adapter Layer** (`adapter/`): Platform abstraction for graphics, input, window management

### Directory Structure

```
ace_engine/
├── adapter/              # Platform adaptation (ohos, preview)
│   ├── ohos/            # OpenHarmony platform implementation
│   └── preview/         # Preview tool support
├── frameworks/
│   ├── base/            # Base utilities and common libraries
│   ├── bridge/          # Frontend-backend bridge layer
│   │   ├── declarative_frontend/  # ArkTS/TS declarative UI (recommended)
│   │   ├── arkts_frontend/        # ArkTS language support
│   │   ├── js_frontend/           # JavaScript frontend
│   │   └── cj_frontend/           # Cangjie frontend
│   └── core/            # Core components and rendering
│       ├── components/    # Legacy component implementations
│       └── components_ng/ # New generation components (preferred)
│           ├── base/      # Base classes: FrameNode, UINode, ViewAbstract
│           ├── pattern/   # Component pattern implementations
│           ├── property/  # Property modifiers
│           ├── layout/    # Layout algorithms
│           ├── render/    # Rendering implementations
│           └── gestures/  # Gesture recognition
├── interfaces/           # Public API interfaces
│   ├── inner_api/       # Internal APIs
│   └── native/          # NDK APIs
├── test/                # Tests
│   ├── unittest/        # Unit tests
│   └── benchmark/       # Performance benchmarks
└── build/               # Build configuration
```

## Frontend Architecture (Bridge Layer)

The bridge layer provides the critical interface between frontend language processing and backend component execution:

### Bridge Layer Responsibilities

```
┌─────────────────────────────────────────────────────────┐
│  Bridge Layer Core Functions                            │
│                                                          │
│  1. Language Parsing                                    │
│     - Parse ArkTS/TypeScript/JS code                    │
│     - Extract component descriptions and attributes      │
│                                                          │
│  2. Component Tree Building                             │
│     - Create FrameNode instances                        │
│     - Establish parent-child relationships              │
│                                                          │
│  3. State Management                                    │
│     - AppStorage: Application-level state               │
│     - LocalStorage: Page-level state                    │
│     - @Watch/@Link/@Prop: Reactive data binding         │
│                                                          │
│  4. Event Handling                                     │
│     - User interaction events                           │
│     - Lifecycle events                                  │
│     - State change notifications                        │
└─────────────────────────────────────────────────────────┘
```

### Multiple Frontend Support

1. **Declarative Frontend** (`declarative_frontend/`):
   - ArkTS/TypeScript-based declarative UI
   - Recommended for new applications
   - State management integration
   - Modifier pattern for property updates
   - Located: `frameworks/bridge/declarative_frontend/`

2. **ArkTS Frontend** (`arkts_frontend/`):
   - Extended TypeScript with OpenHarmony features
   - Koala compiler integration
   - Advanced state management capabilities

3. **JavaScript Frontend** (`js_frontend/`):
   - Traditional JavaScript support
   - V8 engine integration
   - Legacy application compatibility

### State Management Implementation

Located in `frameworks/bridge/declarative_frontend/state_mgmt/`:

## Component System (NG Architecture)

The Components NG architecture is the core framework for component execution, providing complete capabilities from parsing to rendering:

### Component Lifecycle Pipeline

```
┌─────────────────────────────────────────────────────────┐
│  Component Lifecycle (Complete Flow)                    │
│                                                          │
│  1. Parsing Phase                                      │
│     Frontend parses ArkTS code → Component description  │
│                                                          │
│  2. Building Phase                                     │
│     Create FrameNode → Initialize Pattern & Properties   │
│                                                          │
│  3. Layout Phase                                       │
│     Measure → Layout → Position calculation             │
│                                                          │
│  4. Render Phase                                       │
│     RenderNode creation → Drawing → Display             │
└─────────────────────────────────────────────────────────┘
```

### Core Base Classes

- **UINode** (`components_ng/base/ui_node.h`): Base class for all UI nodes
- **FrameNode** (`components_ng/base/frame_node.h`): Main container node combining pattern + element + render node
- **ViewAbstract** (`components_ng/base/view_abstract.h`): Abstract view with common properties

### Pattern Structure

Each component in `components_ng/pattern/` typically contains:
- `*_pattern.h/cpp` - Main pattern class (business logic & lifecycle)
- `*_model.h/cpp` - Data model interface
- `*_layout_property.h/cpp` - Layout-related properties
- `*_paint_property.h/cpp` - Render-related properties
- `*_event_hub.h/cpp` - Event handling

Example structure:
```
components_ng/pattern/marquee/
├── marquee_pattern.h/cpp         # Main pattern logic
├── marquee_model_ng.h/cpp         # Data model interface
├── marquee_layout_property.h/cpp  # Layout properties
├── marquee_paint_property.h/cpp   # Render properties
├── marquee_event_hub.h/cpp        # Event handling
└── bridge/                        # Bridge layer (dynamic module)
    ├── marquee_dynamic_modifier.cpp
    ├── marquee_static_modifier.cpp
    └── marquee_dynamic_module.cpp
```

### Property System

Properties use the **modifier pattern**:
- Defined in `components_ng/property/`
- Chain-able property setters
- Example: `Text().width(100).height(50).fontSize(16)`

## Adding New Components

For detailed guidance, see `如何新增一个组件.md` (How to Add a New Component guide).

### Component Creation Flow (Legacy Architecture)

1. **DOM Layer** (`dom_*`): Parse attributes from HML/JSX
2. **Component Layer** (`*_component`): Manage component state
3. **Element Layer** (`*_element`): Handle component instances
4. **Render Layer** (`render_*`): Draw on screen

### Component Creation Flow (NG Architecture)

1. Create pattern class inheriting from appropriate base pattern
2. Implement model interface for data management
3. Add property modifiers (layout & paint properties)
4. Register in components.gni
5. Implement bridge layer for dynamic loading (optional)

## Key Technologies

**Core Framework**:
- **Language**: ArkTS (extended TypeScript), C++
- **State Management**: AppStorage, LocalStorage, @Watch/@Link/@Prop
- **Component System**: Components NG (FrameNode, Pattern, Properties)

**Graphics & Rendering**:
- **Drawing Engine**: Skia (2D graphics), Rosen (rendering context)
- **Layout Algorithms**: Flexbox, Grid, Absolute positioning
- **Render Pipeline**: RenderNode, DrawCommandList

**JavaScript Runtime**:
- **ArkTS Runtime**: arkjs (Panda-based VM)
- **Legacy Support**: V8

**Build System**:
- **Build Tool**: GN (Generate Ninja)
- **Executor**: Ninja
- **Platform**: OpenHarmony (OHOS), Preview (Linux/Windows/Mac)

## Important Configuration

- **Build config**: `ace_config.gni` - Feature flags and build options
- **Component list**: `frameworks/core/components_ng/components.gni`
- **Package metadata**: `bundle.json`

## Development Patterns

### Component Development

1. Prefer `components_ng` (NG architecture) over legacy `components`
2. Use ViewAbstract as base for new components
3. Implement proper pattern/model separation
4. Add property modifiers for exposed properties

### Property Updates

- Use modifiers: `Component().property(value)`
- Avoid direct property access
- Support both attributes and styles where applicable

### Event Handling

- Use event markers for registration
- Support gesture recognizers from `components_ng/gestures/`
- Proper event bubbling and capture

### Multi-Platform Support

- Platform adaptation through `adapter/` layer
- Conditional compilation using GN defines
- Feature flags in `ace_config.gni`

## Testing Guidelines

- Unit tests use `test/unittest/` structure matching source layout
- Mock objects in `test/mock/ohos_mock/`
- Benchmark tests use Google Benchmark framework
- Run regression detection: `python3 test/benchmark/regression_detector.py`

## Common Issues

1. **Build failures**: Check `ace_config.gni` for required feature flags
2. **Missing components**: Verify component is registered in `components.gni`
3. **Platform-specific code**: Use adapter layer, not direct platform calls
4. **Memory management**: Use `AceType::RefPtr` for smart pointers
