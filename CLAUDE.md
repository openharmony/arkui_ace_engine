# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Knowledge Base

This project maintains a comprehensive knowledge base system for in-depth component analysis and development guidance.

### docs/ Knowledge Base Directory

The `docs/` directory contains organized knowledge base documentation covering:

- **Component Knowledge** (`docs/pattern/*/`) - In-depth analysis for specific components (e.g., Menu, Grid, List)
  - Component architecture and design patterns
  - Pattern/Model/Property/Algorithm layer breakdown
  - Lifecycle management and event handling
  - Layout algorithms and paint methods
  - Test coverage and debugging guides

- **Architecture & Design** (`docs/architecture/`) - Framework architecture documentation
  - System design patterns
  - Component layering and separation of concerns
  - Cross-component integration patterns

- **Best Practices** (`docs/best_practices/`) - Development guidelines and solutions
  - Common problem-solving approaches
  - Performance optimization techniques
  - Debugging and troubleshooting guides

**Knowledge Base Index**: See [docs/knowledge_base_README.md](docs/knowledge_base_README.md) for the complete catalog of available knowledge base documents.

**Metadata Index**: See [docs/knowledge_base_INDEX.json](docs/knowledge_base_INDEX.json) for structured metadata including keywords, aliases, categories, and path mappings for all knowledge bases.

**Usage**: When answering questions or providing guidance:

1. **Check for relevant knowledge base documents** in `docs/` before diving into code analysis
2. **Search the knowledge base** using Grep tools to find component-specific information
3. **Reference knowledge base content** to provide comprehensive, context-aware answers
4. **Cross-reference with actual code** using the file paths and line numbers cited in knowledge base documents

### Knowledge Base Creation Standards

When creating new knowledge base documents, the following standards **MUST** be followed:

#### 1. File Naming Convention

**Pattern**: `XXX_Knowledge_Base[_CN].md`

- Use clear English names (e.g., `Text_Knowledge_Base_CN.md`, `Menu_Knowledge_Base.md`)
- Add `_CN` suffix for Chinese-language documents
- Place in appropriate subdirectory under `docs/`:
  - `docs/pattern/<component>/` - Component-specific knowledge bases
  - `docs/sdk/` - SDK and API documentation
  - `docs/architecture/` - Architecture and design documentation

#### 2. Metadata Requirements

All knowledge bases **MUST** include metadata in [docs/knowledge_base_INDEX.json](docs/knowledge_base_INDEX.json):

```json
{
  "name": "ComponentName",
  "name_cn": "组件中文名",
  "category": "basic/container/selector/shape/media/data_display/rich_text/advanced/sdk",
  "type": "component/feature/sdk",
  "keywords": [
    "功能关键词1",
    "功能关键词2",
    "功能关键词3",
    "... (5-15 keywords)"
  ],
  "aliases": [
    "别名1",
    "别名2",
    "... (2-5 aliases)"
  ],
  "file_path": "path/to/doc.md",
  "source_paths": {
    "pattern": "OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/...",
    "model": "OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/...",
    "layout": "OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/..."
  },
  "api_paths": {
    "static": "OpenHarmony/interface/sdk-js/api/arkui/component/...",
    "modifier": "OpenHarmony/interface/sdk-js/api/arkui/...Modifier.d.ts"
  },
  "last_updated": "YYYY-MM-DD"
}
```

**Metadata Requirements**:

- **name**: Component English name (required)
- **name_cn**: Component Chinese name (required)
- **category**: Must match one of the predefined categories (required)
- **type**: component/feature/sdk (required)
- **keywords**: 5-15 terms covering functionality, use cases, related concepts (required)
- **aliases**: 2-5 alternative names users might search for (required)
- **file_path**: Relative path from docs/ (required)
- **source_paths**: Source code path mappings (optional, recommended)
- **api_paths**: SDK API path mappings (optional, recommended)
- **last_updated**: Last update date in YYYY-MM-DD format (required)

#### 3. Document Structure

Every knowledge base document **MUST** include:

```markdown
# Component Name 组件完整知识库

> **文档版本**: v1.0
> **更新时间**: YYYY-MM-DD
> **源码版本**: OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [完整API清单](#完整api清单)
7. [关键实现细节](#关键实现细节)
8. [使用示例](#使用示例)
9. [调试指南](#调试指南)
10. [常见问题](#常见问题)

---

## 概述

### 组件定位

**ComponentName** 组件是...

### 技术架构

...

### 代码规模

...
```

**Required Sections**:

1. **概述** (Overview) - Component positioning and purpose
2. **目录结构** (Directory Structure) - Source file organization
3. **核心类** (Core Classes) - Inheritance relationships
4. **Pattern层** (Pattern Layer) - Business logic details
5. **Model层** (Model Layer) - Data model details
6. **API清单** (API List) - Complete API listing
7. **实现细节** (Implementation Details) - Key implementation points
8. **使用示例** (Usage Examples) - Practical examples
9. **调试指南** (Debugging Guide) - Debugging techniques
10. **常见问题** (FAQ) - Common issues and solutions

#### 4. Path Reference Standards

All code references in knowledge bases **MUST** follow these path formats:

- **Source code paths**: Use `OpenHarmony/` prefix
  - ✅ `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp:123`
  - ❌ `/home/user/OpenHarmony/...` (local absolute paths)
  - ❌ `frameworks/core/components_ng/...` (relative paths)

- **Knowledge base links**: Use relative paths within same repository
  - ✅ `../pattern/menu/Menu_Knowledge_Base.md`
  - ❌ `OpenHarmony/foundation/arkui/ace_engine/docs/pattern/menu/...`

- **SDK API paths**: Use `OpenHarmony/` prefix
  - ✅ `OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets`
  - ❌ `interface/sdk-js/api/arkui/...` (relative paths)

#### 5. Content Verification Rules

Before finalizing any knowledge base:

1. **Verify all source paths exist**

   ```bash
   ls -la OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/<component>/<component>_pattern.cpp
   ```

2. **Verify all API paths exist**

   ```bash
   ls -la OpenHarmony/interface/sdk-js/api/arkui/component/<component>.static.d.ets
   ```

3. **Verify line numbers in code references**
   - Read the actual file at the specified line
   - Ensure the code hasn't moved due to refactoring

4. **Verify technical accuracy**
   - Cross-reference multiple source files
   - Test code examples when applicable
   - Consult actual implementation, not assumptions

#### 6. Index Maintenance

When adding or updating knowledge bases:

1. **Update knowledge_base_INDEX.json**
   - Add new component entry with complete metadata
   - Update `last_updated` for modified entries
   - Verify all paths are valid
   - Ensure valid JSON format (use JSON linter or validator)

2. **Update docs/knowledge_base_README.md**
   - Add component to directory structure
   - Update statistics (total count, category counts)
   - Add component description if not already present

3. **Verify metadata consistency**

   ```bash
   # Count knowledge base files
   find docs -name "*_Knowledge_Base*.md" -type f | wc -l

   # Validate JSON format
   python3 -m json.tool docs/knowledge_base_INDEX.json > /dev/null && echo "Valid JSON"

   # Count indexed components
   python3 -c "import json; data=json.load(open('docs/knowledge_base_INDEX.json')); print(f'Total components: {len(data[\"knowledge_bases\"])}')"

   # Search by keyword (requires jq or python)
   python3 -c "import json; data=json.load(open('docs/knowledge_base_INDEX.json')); print([kb['name'] for kb in data['knowledge_bases'] if '文本' in ' '.join(kb['keywords'])])"
   ```

#### 7. Code Verification Principles (Critical)

**When writing knowledge bases, NEVER**:

- ❌ Guess or fabricate code implementations
- ❌ Assume functionality without reading source code
- ❌ Copy code from other sources (documentation, blogs, etc.)
- ❌ Write hypothetical examples as actual code

**ALWAYS**:

- ✅ Use Read/Grep tools to locate and read actual source code
- ✅ Reference complete file paths with line numbers
- ✅ Verify code behavior by reading implementation
- ✅ Provide source location for all code snippets
- ✅ Mark uncertain content as "推测" (speculation)

**Example of proper code reference**:

```markdown
### Text Pattern Initialization

Source: `OpenHarmony/foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_pattern.cpp:123-145`

```cpp
void TextPattern::OnModifyDone()
{
    // Actual implementation from source
    auto host = GetHost();
    if (host) {
        host->MarkDirtyNode(PROPERTY_PATTERN_RENDER_CONTEXT);
    }
}
```
```

#### 8. Quality Checklist

Before submitting a knowledge base, verify:

- [ ] File follows naming convention (`XXX_Knowledge_Base[_CN].md`)
- [ ] Metadata added to `knowledge_base_INDEX.json`
- [ ] JSON format is valid (use JSON validator)
- [ ] All required fields present (name, name_cn, category, type, keywords, aliases, file_path, last_updated)
- [ ] Keywords count between 5-15
- [ ] Aliases count between 2-5
- [ ] All source paths verified to exist
- [ ] All API paths verified to exist
- [ ] All line numbers verified against actual code
- [ ] Document includes all 10 required sections
- [ ] Code examples are from actual source (not fabricated)
- [ ] Path references use correct format (`OpenHarmony/` prefix for code, relative for KB links)
- [ ] `knowledge_base_README.md` updated
- [ ] Statistics updated correctly

#### 9. Maintenance and Updates

**Regular Maintenance Tasks**:

1. **Monthly verification**
   - Check all source paths still exist
   - Verify line numbers are still accurate
   - Update for any code refactoring

2. **When code changes**
   - Update affected knowledge bases immediately
   - Update `last_updated` in metadata
   - Document the change in the knowledge base

3. **When errors are found**
   - Document the error and correction
   - Identify root cause
   - Add preventive measures to knowledge base
   - Share learnings across all relevant knowledge bases

**Example update entry**:
```markdown
## Learned Lessons

### Error: Incorrect API Method Name
**Date**: 2026-02-04
**Issue**: Knowledge base referenced `SetText()` which was renamed to `UpdateText()`
**Root Cause**: Code refactoring not reflected in documentation
**Correction**: Updated all references to use `UpdateText()`
**Prevention**: Added note to check for API changes during monthly verification
**Reference**: text_pattern.cpp:234-256
```

#### 10. Knowledge Base Categories

Knowledge bases must be categorized as follows:

| Category | Description | Examples |
| :--- | :--- | :--- |
| **basic** | Basic UI components | Text, Button, Image, TextInput |
| **container** | Layout containers | Column, Row, Grid, List, Scroll, Stack |
| **selector** | Data selection components | DatePicker, TimePicker, Slider, Checkbox |
| **shape** | Shape drawing components | Rect, Circle, Path, Polygon |
| **media** | Media components | Video, Canvas, ImageAnimator |
| **data_display** | Data presentation | Badge, Gauge, Progress, TextTimer |
| **rich_text** | Rich text components | TextSpan, TextArea |
| **advanced** | Complex interactive components | Menu, Dialog, Navigation, Refresh |
| **sdk** | SDK and API documentation | ArkUI SDK API, FrameNode, BuilderNode |

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
