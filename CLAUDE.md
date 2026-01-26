# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

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

Main libraries defined in `build/BUILD.gn`:
- `libace` - Main engine library
- `libace_compatible` - Compatibility layer
- `libace_engine_*` - Engine with different JS backends
- `libace_engine_declarative_*` - Declarative frontend variants

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
