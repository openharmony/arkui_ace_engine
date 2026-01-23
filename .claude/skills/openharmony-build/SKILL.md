---
name: openharmony-build
description: This skill should be used when the user asks to "编译 OpenHarmony", "build OpenHarmony", "编译完整代码", "执行编译", "编译 OpenHarmony 代码", "快速编译", "跳过gn编译", "fast-build", "编译测试", "编译测试用例", "build ace_engine_test", or mentions building the full OpenHarmony system, fast rebuild, or test compilation. Handles complete build process including build execution, success verification, and failure log analysis with primary focus on out/{product}/build.log.
version: 0.2.0
---

# OpenHarmony Build Skill

This skill provides comprehensive support for building the complete OpenHarmony codebase, including build execution, result verification, and error log analysis.

## Build Environment

OpenHarmony uses the `build.sh` script located in the root directory for building. The build process requires:

- **Build script**: `./build.sh` in OpenHarmony root directory
- **Build tool**: hb (Harmony Build) system
- **Python environment**: Python 3 from prebuilts
- **Node.js**: Version 14.21.1
- **Output directory**: `out/` in OpenHarmony root

## Build Execution

### Navigate to Root Directory

Always execute builds from the OpenHarmony root directory. To find the root directory from any location in the tree:

```bash
# Method 1: Find directory containing .gn file
find_root() {
    local current_dir="$(pwd)"
    while [[ ! -f "$current_dir/.gn" ]]; do
        current_dir="$(dirname "$current_dir")"
        if [[ "$current_dir" == "/" ]]; then
            echo "Error: OpenHarmony root not found (no .gn file)"
            return 1
        fi
    done
    echo "$current_dir"
}

# Navigate to root
cd "$(find_root)"
```

### Standard Build Commands

**Full build for product** (recommended command with cache enabled):
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache
```

**Build specific component**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine --ccache
```

**Build with specific target**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name <product> --build-target <target> --ccache
```

Common product names: `rk3568`, `ohos-sdk`

Common build targets: `ohos` (default if omitted), `ace_engine`, `ace_engine_test`, `unittest`

**Build command options**:
- `--export-para PYCACHE_ENABLE:true` - Enable Python cache for faster builds
- `--ccache` - Enable compiler cache for faster rebuilds
- `--product-name` - Target product to build
- `--build-target` - Specific component or target (optional, defaults to full system)
- `--fast-rebuild` - Skip GN generation if no GN files modified (significantly faster)

### Test Build Commands

**Build ACE Engine tests** (recommended for ACE Engine development):
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine_test --ccache
```

**Build all unit tests** (full test suite):
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target unittest --ccache
```

**Test target priorities** (recommended usage):
1. **`ace_engine_test`** - Build ACE Engine specific tests only (faster, recommended for ACE Engine development)
2. **`unittest`** - Build all unit tests across entire system (slower, comprehensive testing)

**When to use `ace_engine_test`**:
- Developing or testing ACE Engine components
- Quick validation of ACE Engine changes
- Focused testing on ACE Engine functionality
- Faster iteration during development

**When to use `unittest`**:
- Running complete test suite
- Validating cross-module interactions
- Pre-release comprehensive testing
- When specifically required to build all tests

### Fast Rebuild (Skip GN Generation)

When no GN files (BUILD.gn, *.gni) have been modified, use `--fast-rebuild` to skip GN generation:

```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache --fast-rebuild
```

**When to use fast rebuild**:
- Only source code (.cpp, .h, .ts, .ets) has changed
- No build configuration files (BUILD.gn, *.gni) modified
- Incremental development iteration

**Fast rebuild benefits**:
- Skips GN parse and generation phase
- Directly uses existing ninja build files
- Significantly faster for code-only changes
- Typical speedup: 30-50% faster

**When NOT to use fast rebuild**:
- BUILD.gn files modified
- New dependencies added
- Build configuration changed
- First time building or after cleaning output

### Fast Build for Component

Combine fast rebuild with component build for maximum speed:

```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```

### Fast Build for Tests

Combine fast rebuild with test builds for rapid iteration:

**Build ACE Engine tests (fast)**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine_test --ccache --fast-rebuild
```

**Build all unit tests**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target unittest --ccache --fast-rebuild
```

**Recommendation**: For ACE Engine development, prefer `ace_engine_test` with `--fast-rebuild` for fastest iteration when only test code has changed.

### Build Process

Execute the build command and monitor the output. The build process:
1. Checks environment (Python, Node.js versions)
2. Initializes ohpm and dependencies
3. Runs the hb build system
4. Generates output in `out/` directory

## Success Verification

### Check Build Exit Code

A successful build exits with code 0 and displays:
```
=====build successful=====
```

### Verify Output

Check that the expected build artifacts exist in `out/`:

```bash
# Get OpenHarmony root dynamically
OH_ROOT=$(find_root)

# Check for product-specific output
ls -la "$OH_ROOT/out/<product-name>/"

# Example for rk3568:
ls -la "$OH_ROOT/out/rk3568/"
```

Look for key directories:
- `packages/` - Built packages
- `libs/` - Compiled libraries
- `bin/` - Executables

### Build Success Indicators

- Exit code is 0
- Success message displayed
- Expected artifacts in output directory
- No error messages in final output

## Failure Analysis

When build fails (exit code non-zero), analyze the error systematically.

### Locate Build Logs

**IMPORTANT: Always check the primary build log first**

Build logs are located in the `out/` directory structure. The primary build log contains all build information and should be the first place to check for errors.

```bash
# Get OpenHarmony root dynamically
OH_ROOT=$(find_root)
```

**Primary build log (FIRST PRIORITY)**:
```bash
# Main build log - contains all errors and warnings
$OH_ROOT/out/<product-name>/build.log

# Example for rk3568:
$OH_ROOT/out/rk3568/build.log
```

**Component-specific logs (for detailed investigation)**:
```bash
# Check for component build failures
$OH_ROOT/out/<product-name>/logs/<component>/

# Example for ace_engine:
find "$OH_ROOT/out/rk3568/logs" -name "*ace_engine*" -type f
```

**Common log locations** (in order of priority):
1. **`$OH_ROOT/out/<product>/build.log`** - Main build log ⭐ **ALWAYS CHECK THIS FIRST**
2. `$OH_ROOT/out/<product>/logs/` - Detailed component logs
3. `$OH_ROOT/out/sdk/build.log` - SDK build logs

### Analyze Build Errors

Use the error analysis script to extract and summarize errors:

```bash
# Get OpenHarmony root dynamically
OH_ROOT=$(find_root)

# Use the provided analysis script
"$OH_ROOT/foundation/arkui/ace_engine/.claude/skills/openharmony-build/scripts/analyze_build_error.sh" <product-name>
```

**Manual error search**:
```bash
# Get OpenHarmony root dynamically
OH_ROOT=$(find_root)

# Search for error patterns in build log
grep -i "error" "$OH_ROOT/out/<product>/build.log" | tail -50

# Find fatal errors
grep -i "fatal" "$OH_ROOT/out/<product>/build.log"

# Search for specific failure patterns
grep -A 10 "FAILED" "$OH_ROOT/out/<product>/build.log"
```

### Common Build Failure Patterns

**Compilation errors**:
```
error: undefined reference to 'symbol'
error: 'header_file' not found
```

**Link errors**:
```
ld: error: undefined symbol
ld: cannot find -l<library>
```

**Dependency errors**:
```
error: package 'package-name' not found
error: dependency 'dependency-name' not satisfied
```

**Configuration errors**:
```
error: invalid product name
error: build target not found
```

## Error Resolution Workflow

1. **Check primary build log**: Always start with `$OH_ROOT/out/<product>/build.log`
2. **Identify the error**: Use `analyze_build_error.sh` to extract errors from build.log
3. **Locate the source**: Find the file and line number causing the error
4. **Understand the cause**: Read surrounding context in the build.log
5. **Propose solution**: Based on error type and context
6. **Verify fix**: Rebuild to confirm resolution

**Key Principle**: The primary build log (`out/<product>/build.log`) contains all build information including GN generation, ninja compilation, linking, and packaging errors. Always check this file first before looking at component-specific logs.

## Additional Resources

### Scripts

- **`scripts/analyze_build_error.sh`** - Extract and summarize build errors
- **`scripts/find_recent_errors.sh`** - Find recent build failures

### Reference Files

- **`references/build-commands.md`** - Complete build command reference
- **`references/common-errors.md`** - Common build errors and solutions
- **`references/log-locations.md`** - Detailed log file locations

## Best Practices

- Always find OpenHarmony root dynamically using `.gn` file as marker
- Use cache options (`--export-para PYCACHE_ENABLE:true --ccache`) for faster builds
- Use `--fast-rebuild` when only code changed (no GN modifications)
- Search for errors from the end of log files (most recent first)
- Preserve full error context including line numbers
- Check both main build log and component-specific logs
- Verify environment setup (Python, Node.js versions) before building

### Build Strategy Guide

**First time build or major changes**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache
```

**Code-only changes (fastest)**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache --fast-rebuild
```

**Component development**:
```bash
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```

### Dynamic Path Finding Helper

Use this helper function in all scripts and commands:

```bash
# Define function to find OpenHarmony root
find_oh_root() {
    local dir="$(pwd)"
    while [[ ! -f "$dir/.gn" ]]; do
        dir="$(dirname "$dir")"
        if [[ "$dir" == "/" ]]; then
            echo "Error: OpenHarmony root not found" >&2
            return 1
        fi
    done
    echo "$dir"
}

# Usage in commands
OH_ROOT=$(find_oh_root)
cd "$OH_ROOT" || exit 1
```
