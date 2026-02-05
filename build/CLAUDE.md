# ACE Engine Build System Documentation

This directory contains the build configuration and scripts for the ACE Engine framework using GN (Generate Ninja) build system.

## Overview

The ACE Engine build system is responsible for:
- Building core engine libraries (`libace.z.so`, `libace_compatible.z.so`)
- Managing multiple platform configurations (OHOS, Windows, macOS, Linux)
- Handling JavaScript engine integration
- Generating object files from resources
- Building system dialog (SA Dialog) JavaScript files

## Directory Structure

```
build/
├── BUILD.gn                          # Main build configuration
├── ace_lib.gni                       # Core library build templates
├── ace_gen_obj.gni                   # Object file generation template
├── ace_ext.gni                       # Vendor extension configuration
├── ace_gen_sa_dialog_js.gni          # SA dialog JS generation template
├── uicast.gni                        # UI cast configuration
├── libace.map                        # Symbol versioning script
├── search.py                         # Platform discovery script
└── tools/                            # Build utilities
    ├── run_objcopy.py                # Objcopy wrapper (Linux/Unix)
    ├── run_objcopy_pc_mac.py         # Objcopy wrapper (PC/Mac)
    ├── build_js.py                   # JS file builder
    ├── build_resource_to_bytecode.py # Resource to bytecode converter
    └── gen_uicontext_ohos.py         # UI context generator
```

## Core Build Templates

### 1. `libace_static` Template

**Location**: [ace_lib.gni](ace_lib.gni)

Builds the static ACE library for different platforms.

**Key Features**:
- Supports multiple platforms: `ohos`, `ohos_ng`, `windows`, `mac`, `linux`
- Integrates base framework, bridge layer, and core components
- Includes N-API kits for legacy mode
- Optional built-in Ark JS engine for preview
- Applies sanitization for OHOS builds (integer overflow, boundary checks)

**Usage Example**:
```gni
libace_static("libace_static_ohos") {
  platform = "ohos"
  config = {
    # Platform-specific configuration
  }
}
```

**Dependencies**:
- `frameworks/base:ace_base_$platform`
- `frameworks/bridge:framework_bridge_$platform`
- `frameworks/core:ace_core_$platform`
- N-API kits (for legacy mode only)

### 2. `ace_bridge_engine` Template

**Location**: [ace_lib.gni](ace_lib.gni)

Builds separated JavaScript engine libraries for OHOS platform.

**Engine Types**:
- `engine`: Standard engine (with optional debug variant)
- `engine_declarative`: Declarative frontend engine
- `engine_pa`: Particle Ability (PA) engine

**Usage Example**:
```gni
ace_bridge_engine("libace_engine_ark_ohos") {
  platform = "ohos"
  engine_name = "ark"
  build_type = "engine"
  use_js_debug = false
}
```

### 3. `gen_obj` Template

**Location**: [ace_gen_obj.gni](ace_gen_obj.gni)

Generates object files from resource files using `objcopy` tool.

**Key Features**:
- Platform-specific objcopy tool selection
- Converts binary resources to object files for linking
- Supports cross-compilation

**Usage Example**:
```gni
gen_obj("resource") {
  input = "resources/data.bin"
  output = "$target_gen_dir/resource.o"
  snapshot_dep = [ ":snapshot" ]
}
```

**Tool Selection**:
| Platform | Objcopy Tool | Script |
|----------|--------------|---------|
| Windows (MinGW) | `objcopy_mingw` | build_resource_to_bytecode.py |
| macOS/iOS | `objcopy_clang` | build_resource_to_bytecode.py |
| Linux | `objcopy_x86_64` | build_resource_to_bytecode.py |
| OHOS (x86_64) | `objcopy_x86_64` | run_objcopy.py |
| OHOS (ARM/ARM64) | `objcopy_default` | run_objcopy.py |

### 4. `gen_sa_dialog_js` Template

**Location**: [ace_gen_sa_dialog_js.gni](ace_gen_sa_dialog_js.gni)

Generates and installs JavaScript files for System Ability (SA) dialogs.

**Key Features**:
- Builds dialog JS files using Node.js and ace_js2bundle
- Handles i18n and common resource files
- Installs files to `SADialog` directory

**Usage Example**:
```gni
gen_sa_dialog_js("my_dialog") {
  dialog_name = "MyDialog"
  project_path = "dialogs/my_dialog/src"
  i18n_files = [ "i18n/en-US.json", "i18n/zh-CN.json" ]
  common_files = [ "common/utils.js" ]
}
```

**Output Files**:
- `app.js`
- `pages/index/index.js`
- `manifest.json`
- Optional i18n and common files

## Main Build Targets

### Core Libraries

**Location**: [BUILD.gn](BUILD.gn)

| Target | Description |
|--------|-------------|
| `libace_compatible` | Main compatible engine library (current core) |
| `libace_compatible_components` | Compatible component library |
| `libace` | NG-only engine library (without legacy support) |

**Shared Library Configuration**:
- Uses version script from `libace.map` for symbol control
- Enables sanitization on OHOS (integer overflow, boundary checks)
- Applies LTO (Link-Time Optimization) configurations
- Links against HiLog for logging

### Platform-Specific Engines

For each platform in `ace_platforms`, the build system generates:
1. **Static Library**: `libace_static_$platform`
2. **Bridge Engines** (OHOS only):
   - `libace_engine_{engine}_{platform}`
   - `libace_engine_{engine}_debug_{platform}` (if supported)
   - `libace_engine_declarative_{engine}_{platform}`
   - `libace_engine_pa_{engine}` (if PA support enabled)

## Build Configurations

### LTO (Link-Time Optimization) Configuration

**Location**: [BUILD.gn](BUILD.gn#L103-L139)

**Options**:
- `enable_lto_O0`: Use LTO with O0 optimization
- Default: LTO with O2 optimization

**Enhanced Optimization Features**:
- **PGO (Profile-Guided Optimization)**: `ace_engine_feature_enable_pgo`
- **Code Merging**: `ace_engine_feature_enable_codemerge`
- **Instruction Prefetch**: `ace_engine_feature_enable_inst_prefetch` (ARM64 only)

**Linker Flags**:
- Split machine functions
- Symbol ordering using PGO profile
- Instruction prefetch with L2 cache miss profile
- Bsymbolic for better performance

### EH Frame Reduction

**Location**: [BUILD.gn](BUILD.gn#L86-L95)

For AOSP platforms to reduce ROM size:
```gni
config("reduce_eh_frame_config") {
  cflags = [
    "-fno-unwind-tables",
    "-fomit-frame-pointer",
  ]
}
```

## Build Tools

### 1. `run_objcopy.py` / `run_objcopy_pc_mac.py`

**Purpose**: Wrapper for objcopy tool to convert binary files to object files.

**Arguments**:
- `-e, --objcopy`: Path to objcopy executable
- `-a, --arch`: Target architecture (x86, x86_64, arm, arm64)
- `-i, --input`: Input file path
- `-o, --output`: Output object file path

**Output Formats**:
| Architecture | Binary Format | Output Format |
|--------------|---------------|---------------|
| x86 | elf32-i386 | elf32-i386 |
| x86_64 | binary | elf64-x86-64 / pe-x86-64 |
| arm | binary | elf32-littlearm |
| arm64 | binary | elf64-littleaarch64 |

### 2. `build_js.py`

**Purpose**: Build JavaScript files for SA dialogs using ace_js2bundle tool.

**Process**:
1. Copy interface and third-party dependencies
2. Set up ace-loader and node_modules
3. Copy project-specific resources (i18n, common, pages)
4. Run npm build commands
5. Copy built files to target directory

**Requirements**:
- Node.js environment
- ace_js2bundle tool
- parse5 and weex-loader dependencies

### 3. `build_resource_to_bytecode.py`

**Purpose**: Convert resource files to C++ bytecode arrays for platforms without objcopy.

**Output Format**:
```cpp
#include <stdint.h>
const uint8_t _binary_<filename>_start[<length>] = {<bytecode>};
const uint8_t* _binary_<filename>_end = _binary_<filename>_start + <length>;
```

### 4. `gen_uicontext_ohos.py`

**Purpose**: Generate UI context export file for OHOS platform.

**Features**:
- Exports all classes from input file
- Adds 5 classes per line for readability
- Exposes global functions via `globalThis`
  - `__getUIContext__`
  - `__getFrameNodeByNodeId__`
  - `__addAvailableInstanceId__`
  - `__removeAvailableInstanceId__`
  - `__checkRegexValid__`
  - `__getResourceId__`

### 5. `search.py`

**Purpose**: Discover all platforms with `build/platform.gni` files.

**Usage**:
```bash
python3 search.py <search_path>
```

**Output**: List of platform names (one per line)

## Symbol Versioning

### `libace.map`

**Purpose**: Control symbol visibility in shared libraries using linker version script.

**Structure**:
```
{
  global:
    extern "C++" {
      # C++ symbols with wildcards
      OHOS::Ace::*;
      OHOS_ACE_*;
      GetArkUINodeAPI;
      # ... more symbols
    };
  local:
    *;
};
```

**Key Sections**:
1. **V-table construction symbols** for RTTI
2. **Guard variables** for template static members
3. **Non-virtual thunk symbols** for inheritance
4. **Public API symbols**:
   - C API functions (`OHOS_ACE_*`, `GetArkUI*`)
   - Framework classes (`OHOS::Ace::*`)
   - NG components (`OHOS::Ace::NG::*`)
5. **Local**: Hide all other symbols

## Vendor Extensions

### `ace_ext.gni`

**Purpose**: Load vendor-specific ACE engine extensions.

**Loading Priority**:
1. Check `//foundation/arkui/ace_engine_ext/build/config.gni`
2. Check `//vendor/${product_company}/foundation/ace/ace_engine_ext/ace_engine_ext.gni`

**Usage**: Vendor can extend build configuration by providing custom config.gni

## UI Cast Configuration

### `uicast.gni`

**Purpose**: Configure UI cast (castplus) integration.

**Configuration**:
```gni
uicast_configs = {
  uicast_defines = []
  uicast_enable = false
}
```

**Dependency**: Requires `global_parts_info.castplus_cast_engine` to enable

## Build Commands

### From OpenHarmony Root

```bash
# Build ACE Engine for rk3568
./build.sh --product-name rk3568 --build-target ace_engine

# Build for SDK
./build.sh --product-name ohos-sdk --build-target ace_engine

# Build specific target
./build.sh --product-name rk3568 --build-target libace_compatible
```

### Build Outputs

**Location**: `out/<product>/arkui/ace_engine/`

Main outputs:
- `libace_compatible.z.so` - Core engine library
- `libace.z.so` - NG-only engine (if not ASAN build)
- `libace_compatible_components.z.so` - Component library
- Various engine-specific shared libraries

## Platform Support

| Platform | Static Library | Bridge Engines | Status |
|----------|---------------|----------------|--------|
| ohos | ✓ | ✓ | Primary target |
| ohos_ng | ✓ | ✓ | Next-gen mode |
| windows | ✓ | ✗ | Preview tool |
| mac | ✓ | ✗ | Preview tool |
| linux | ✓ | ✗ | Development |

## Build Features and Flags

### Sanitization

**OHOS Builds**:
- `integer_overflow`: Detect integer overflow bugs
- `boundary_sanitize`: Memory boundary checks
- `debug`: Controlled by `ace_sanitize_debug`

### Optimization

**Enhanced Optimization** (`enhanced_opt`):
- LTO with O2 (or O0 if specified)
- Optional PGO with symbol ordering
- Optional code merging for size optimization
- Optional instruction prefetch for ARM64

### Conditional Compilation

**Key Variables**:
- `is_ohos`: Building for OHOS platform
- `is_asan`: Address Sanitizer enabled
- `use_hilog`: Use HiLog for logging
- `is_arkui_x`: ArkUI X build
- `use_mingw_win`, `use_mac`, `use_linux`: Desktop platforms

## Dependencies

### External Dependencies

**Required**:
- `hilog:libhilog` (if `use_hilog` enabled)
- `icu:shared_icui18n`, `icu:shared_icuuc` (desktop platforms)

**Internal Dependencies**:
- `interfaces/inner_api/ace_kit:ace_kit`
- `adapter/ohos/services/etc:ace_engine_param` (OHOS)

### JavaScript Engines

**Supported Engines** (configured in `ace_config.gni`):
- Ark (arkjs)
- Chrome V8
- QuickJS

**Engine Configuration**:
- `use_build_in_js_engine`: Build engine into library
- `js_pa_support`: Enable Particle Ability support
- `pa_engine_path`: Path to PA engine implementation

## Development Guidelines

### Adding New Build Target

1. Define target in appropriate BUILD.gn file
2. Use appropriate template (`libace_static`, `ace_bridge_engine`, etc.)
3. Specify platform and dependencies
4. Add to appropriate group if needed

### Adding New Platform

1. Create `build/platform.gni` in platform directory
2. Add platform configuration to `ace_config.gni`
3. Update platform-specific dependencies in templates

### Modifying Symbol Exports

1. Edit `libace.map`
2. Add public API symbols to `global:` section
3. Keep internal symbols in `local:` section
4. Rebuild and verify with `nm -D`

### Adding New Resource to Object

1. Use `gen_obj` template in BUILD.gn
2. Specify input file and output object path
3. Add snapshot dependency if applicable
4. Include generated source in target

## Common Issues

### Build Failures

**Missing Platform Configuration**:
- Ensure `build/platform.gni` exists
- Check platform is in `ace_platforms` list

**Objcopy Errors**:
- Verify correct objcopy tool for platform
- Check architecture matches target CPU
- Use `build_resource_to_bytecode.py` for desktop platforms

**Linker Errors**:
- Check `libace.map` for missing symbols
- Verify all dependencies are included
- Ensure correct library order

### Symbol Visibility

**Symbols Not Exported**:
- Add to `libace.map` global section
- Check for proper `extern "C++"` wrapping
- Verify linkage visibility attributes

**Too Many Symbols Exported**:
- Move internal symbols to `local:` section
- Use anonymous namespaces for internal linkage
- Add visibility hidden attributes

## Maintenance Notes

### Version Script Updates

When adding new public APIs:
1. Update `libace.map` with new symbols
2. Follow existing naming patterns
3. Group related symbols together
4. Update this documentation

### Tool Updates

When modifying build tools:
1. Maintain backward compatibility if possible
2. Update tool documentation in this file
3. Test on all supported platforms
4. Update examples if usage changes

### Platform Support

When adding new platform support:
1. Create platform-specific configuration
2. Update tool selection logic
3. Test build on target platform
4. Document platform-specific features
