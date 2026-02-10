# ArkTS Frontend Module

This file provides guidance for Claude Code (claude.ai/code) when working with code in the `arkts_frontend` module.

## Module Overview

**ArkTS Frontend** (`frameworks/bridge/arkts_frontend/`) is the core module in ACE Engine that handles the bridge between the ArkTS language and the C++ backend engine. This module uses the Koala compiler technology stack, supporting incremental compilation, type safety, and runtime optimization.

## Core Architecture

### Three-Layer Architecture

```
┌─────────────────────────────────────────────────────────┐
│  Application Layer (ArkTS Code)                         │
│  - ArkTS Components                                     │
│  - State Management (@State, @Prop)                    │
│  - Declarative UI Description                           │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  ArkTS Frontend Bridge Layer                            │
│  - ArktsFrontend: Main frontend class                   │
│  - ArkTS Dynamic Frontend: Dynamic loading support      │
│  - ANI Context Module: Native interface management      │
│  - Koala Runtime Integration                            │
└─────────────────────────────────────────────────────────┘
                          │
                          ↓
┌─────────────────────────────────────────────────────────┐
│  C++ Backend Engine                                     │
│  - Components NG: Component framework                   │
│  - Render: Rendering engine                             │
│  - Layout: Layout algorithms                            │
│  - Gestures: Event handling                             │
└─────────────────────────────────────────────────────────┘
```

## Directory Structure

### Core Modules

```
arkts_frontend/
├── arkts_frontend.h/cpp              # Main frontend class, inherits from Frontend
├── arkts_dynamic_frontend.h/cpp      # Dynamic frontend implementation
├── arkts_plugin_frontend.h/cpp       # Plugin frontend implementation
├── arkts_frontend_loader.h/cpp       # Frontend loader
├── ani_context_module.h/cpp          # ANI context module
└── entry/                            # Entry module
    └── arkts_entry_loader.h/cpp      # ArkTS entry loader
```

**Key Classes**:
- `ArktsFrontend`: Core frontend class responsible for ArkTS code parsing and execution
- `ArktsDynamicFrontend`: Supports dynamic loading and hot reload
- `AniContextModule`: Manages ArkTS Native Interface context

### Koala Compiler Projects

```
arkts_frontend/koala_projects/
├── arkoala-arkts/                    # ArkUI ArkTS implementation
│   ├── arkui-ohos/                   # OHOS platform implementation
│   │   ├── generated/                # Generated type definitions and binding code
│   │   │   ├── component/            # Component API generation
│   │   │   ├── framework/            # Framework API generation
│   │   │   └── stateManagement/      # State management API generation
│   │   └── src/                      # ArkTS/TS source code
│   │       ├── ani/                  # ANI native interface implementation
│   │       ├── component/            # UI component implementation
│   │       ├── framework/            # Framework code
│   │       ├── stateManagement/      # State management implementation
│   │       ├── router/               # Router functionality
│   │       ├── theme/                # Theme system
│   │       └── typedNode/            # Typed nodes
│   └── framework/                    # Framework layer
│       └── native/src/               # C++ native implementation
├── incremental/                      # Incremental compilation system
│   ├── runtime/                      # Runtime support
│   │   ├── animation/               # Animation runtime
│   │   ├── memo/                    # Memoization optimization
│   │   ├── states/                  # State management runtime
│   │   └── tree/                    # Tree structure management
│   └── tools/panda/                 # Panda VM tools
├── interop/                          # Language interoperability layer
│   └── src/
│       ├── cpp/ani/                  # C++ ANI runtime
│       ├── cpp/napi/                 # N-API wrappers
│       └── wasm/                     # WebAssembly support
└── inner_api/                        # Internal API definitions
    ├── arkui/                        # ArkUI internal APIs
    ├── @koalaui/                     # Koala UI APIs
    └── @ohos/                        # OHOS system APIs
```

**Koala Projects Description**:
- `arkoala-arkts`: Complete implementation of ArkUI in ArkTS language
- `incremental`: Incremental compilation and hot reload support
- `interop`: Multi-language interoperability (C++, JS, WASM)
- `inner_api`: Exposed API definitions

## Core Features

### 1. ArkTS Code Parsing

**Flow**:
1. Application startup → `ArktsFrontend::Initialize()`
2. Load ABC bytecode files → `ArktsFrontend::LoadAbcFile()`
3. Initialize Koala runtime → `AniContextModule::SetupRuntime()`
4. Parse ArkTS component tree → `ArktsFrontend::ParseSource()`
5. Build C++ component instances → `ArktsFrontend::ExecuteJs()`

**Key Files**:
- `arkts_frontend.cpp:123` - Frontend initialization flow
- `ani_context_module.cpp:89` - Runtime setup
- `arkts_entry_loader.cpp:45` - ABC file loading

### 2. Incremental Compilation and Hot Reload

**Supported Features**:
- Incremental code compilation
- Hot module replacement
- Type-safe dynamic imports
- Panda VM integration

**Key Modules**:
- `incremental/runtime/` - Runtime support
- `incremental/tools/multi-pass/` - Multi-pass compilation optimization

### 3. ANI (ArkTS Native Interface)

**ANI Provides**:
- Animation system interfaces
- Native component bindings
- Event handling interfaces
- Layout algorithm interfaces
- Rendering interfaces

**Key Files**:
- `ani_context_module.h:56` - ANI context definition
- `koala_projects/interop/src/cpp/ani/` - ANI runtime implementation

### 4. State Management Integration

**Integrated State Management Mechanisms**:
- `@State`: Component internal state
- `@Prop`: Parent-child component property passing
- `@Link`: Two-way data binding
- `@Provide/@Consume`: Cross-component hierarchy state
- `@Watch`: State observation

**Implementation Locations**:
- `koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/`
- `incremental/runtime/states/`

## Development Guide

### Adding New ArkTS Component Bindings

1. **Define Component in Koala Project**:
   - Edit `koala_projects/arkoala-arkts/arkui-ohos/src/component/`
   - Define component interface and properties

2. **Generate Binding Code**:
   - Run Koala compiler to generate `.d.ts` type definitions
   - Generate C++ binding code to `generated/` directory

3. **Implement C++ Side Logic**:
   - Create Pattern class in `components_ng/pattern/`
   - Create ANI binding in `arkts_frontend/`

4. **Register to Frontend**:
   - Register component in `ani_context_module.cpp`

### Debugging ArkTS Code

**Using Panda VM Debugger**:
```bash
# Set Panda VM debug port
export ARKTS_DEBUG_PORT=9229

# Enable verbose logging
export ACE_LOG_LEVEL=DEBUG
```

**Key Log Locations**:
- `arkts_frontend.cpp` - Frontend execution logs
- `ani_context_module.cpp` - ANI call logs

### Performance Optimization

**Incremental Compilation Optimization**:
- Use `memo` function to avoid redundant calculations
- Use `@Watch` listeners appropriately
- Avoid deep state nesting

**Runtime Optimization**:
- Enable Panda VM JIT compilation
- Use `OHOS_APT_CACHE` to cache compilation results
- Reduce ANI cross-boundary calls

## Common Issues

### Q: ArkTS code changes not taking effect?
A: Check if incremental compilation is triggered correctly:
```bash
# Clean incremental cache
rm -rf out/rk3568/arkui/ace_engine/.koala_cache

# Rebuild
./build.sh --product-name rk3568 --build-target ace_engine
```

### Q: ANI call failures?
A: Check the following items:
1. ANI module correctly initialized: `ani_context_module.cpp:89`
2. Type definitions match: check `generated/*.d.ts`
3. Panda VM correctly configured: check `arkts_frontend.cpp:123`

### Q: How to view generated ABC bytecode?
A: Use Panda disassembler tool:
```bash
# Install Panda toolchain
# Disassemble ABC file
ark_disasm your_module.abc > output.txt
```

## Dependencies

### Upstream Dependencies
- **Panda VM**: ArkTS runtime
- **Koala Compiler**: ArkTS compiler
- **TypeScript**: Type system foundation

### Downstream Dependencies
- **Components NG**: C++ component framework
- **Render**: Rendering engine
- **Layout**: Layout algorithms
- **Gestures**: Gesture handling

### Build Dependencies
- `ace_config.gni` - Global configuration
- `koala_integration.gni` - Koala integration configuration
- `link_abc.gni` - ABC file linking configuration

## Testing

**Unit Tests**:
```bash
# Run ArkTS frontend tests
./build.sh --product-name rk3568 --build-target arkts_frontend_test
```

**Test Locations**:
- `test/unittest/bridge/arkts_frontend/`
- `test/unittest/bridge/ani/`

## References

- **Koala Documentation**: `koala_projects/README.md`
- **ArkTS Language Specification**: `docs/arkts_language_spec.md`
- **ANI Interface Documentation**: `interfaces/native/inner_api/`

## Key File Index

| File Path | Description |
|-----------|-------------|
| `arkts_frontend.h:45` | ArktsFrontend main class definition |
| `arkts_frontend.cpp:123` | Frontend initialization flow |
| `ani_context_module.h:56` | ANI context definition |
| `arkts_dynamic_frontend.cpp:89` | Dynamic loading implementation |
| `koala_projects/arkoala-arkts/` | ArkUI ArkTS implementation |
| `koala_projects/incremental/` | Incremental compilation system |
