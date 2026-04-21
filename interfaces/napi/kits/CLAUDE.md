# NAPI Kits Subdirectory Specification

This document contains specialized specifications for NAPI Kits directory and **must inherit and comply with** `CLAUDE.md` in repository root directory. This document only describes constraints and knowledge specific to this directory.

> **Document Version**: v1.0
> **Last Updated**: 2026-02-11
> **Source Version**: OpenHarmony ace_engine (master branch)

---

## 📋 Table of Contents

1. [Overview](#overview)
2. [Module Architecture](#module-architecture)
3. [Core Responsibilities](#core-responsibilities)
4. [Interface Stability](#interface-stability-constraints)
5. [Dependency Rules](#module-dependency-rules)
6. [Cross-Language Bindings](#cross-language-bindings)
7. [Memory Management](#memory-management-contract)
8. [Error Handling](#error-handling-conventions)
9. [Common Pitfalls](#common-pitfalls)
10. [Debugging](#debugging-methods)
11. [Performance](#performance-guidelines)
12. [Testing](#testing-guidelines)

---

## Overview

### NAPI Kits Positioning

**NAPI Kits** (`interfaces/napi/kits/`) is the **NAPI binding implementation layer** of ACE Engine, providing concrete implementations for invoking C++ Native capabilities from ArkTS/JavaScript.

**Core Value**:
- 🏗️ **NAPI Bindings** - Implements NAPI interface bindings defined in interface_sdk_c
- 🎯 **Type Conversion** - Handles type conversions between JavaScript and C++
- 🔧 **Lifecycle Management** - Manages Native object creation, wrapping, and unwrapping
- 🛡️ **Async Support** - Provides thread-safe functions and async work queue support

### Position in ACE Engine

```
ArkTS/JavaScript Layer
         ↓
NAPI Kits (16 modules) - Binding implementations, type conversion, lifecycle
         ↓
interface_sdk_c/arkui/napi/ - Interface definitions, types, enums
         ↓
ACE Engine Core - Component implementations, Layout algorithms
```

### Code Scale

- **Total Submodules**: 16
- **Header Files**: 20+
- **Implementation Files**: 50+
- **Estimated Code Lines**: 10,000+

---

## Module Architecture

### 16 Core Submodules

| Category | Submodules |
|----------|-------------|
| **UI Functionality** | animator, drag_controller, focus_controller, router, text_menu_controller, promptaction |
| **Utilities** | inspector, component_test, componentutils, container_utils, measure, utils |
| **Visual** | color_sampler, luminance_sampler, font, ui_material |
| **System** | configuration, device, display_sync, mediaquery, performancemonitor |
| **Special** | component_snapshot, drawabledescriptor, overlay, observer, plugincomponent, prompt, grid |

### Module Dependency Diagram

```
interface_sdk_c/arkui/napi/ → NAPI Kits (16 modules) → ArkTS/JavaScript
```

---

## Core Responsibilities

### NAPI Kits is Responsible For

1. **NAPI Binding Implementation** - Implement NAPI interfaces defined in interface_sdk_c as concrete C++ functions
2. **ArkTS ↔ C++ Conversion** - Handle type conversions between JavaScript values and C++ objects
3. **Object Lifecycle Management** - Manage Native object creation, wrapping, and unwrapping
4. **Async Operation Handling** - Implement thread-safe functions and async work queue
5. **Module Registration and Export** - Export functional modules to ArkTS environment

### NAPI Kits is NOT Responsible For

- ❌ **NAPI Interface Definition** → **interface_sdk_c/arkui/napi/**
- ❌ **Component Implementation Logic** → **frameworks/core/components_ng**
- ❌ **Layout Algorithms** → **frameworks/core/layout**
- ❌ **Platform Adaptation** → **adapter/ohos**

### Module-Specific Responsibilities

**animator**: Animation property/controller bindings, system initialization (NOT execution/interpolation logic)

**drag_controller**: Drag event/preview bindings (NOT gesture recognition/position calculation)

**router**: Router method bindings, state queries, stack management (NOT logic implementation/lifecycle)

---

## Interface Stability Constraints

### NAPI Binding Semantics (Immutable)

#### Binding Function Signature

```cpp
static napi_value MyMethod(napi_env env, napi_callback_info info) {
    size_t argc = 0;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr);
    return result;
}
```

**Prohibited**: Changing parameter order, Changing return value type, Removing exported functions, Changing function semantics

#### Object Wrapping Stability

```cpp
napi_status napi_wrap(
    napi_env env,
    napi_value js_object,
    void* native_object,
    napi_finalize finalize_cb,  // Must not be null
    void* finalize_hint);
```

**Prohibited**: Changing finalize callback signature, Changing wrap/unwrap behavior, Unwrapping immediately after wrap

### API Version Management

| API Level | Stability | Breaking Changes Allowed |
|-----------|-----------|-------------------------|
| NAPI binding functions | Stable within major version | No |
| Public exported interfaces | Stable across minor versions | No |
| Experimental interfaces | Unstable | Yes (must mark deprecation) |

---

## Module Dependency Rules

### Allowed Dependencies

```
interface_sdk_c/arkui/napi/ → NAPI Kits → ArkTS Applications
```

**Note**: NAPI Kits depends ONLY on interface_sdk_c, frameworks/core is independent

### Prohibited Dependencies

**Prohibited**:
- ❌ NAPI Kits → frameworks/core
- ❌ NAPI Kits → frameworks/bridge
- ❌ NAPI Kits → adapter/ohos
- ❌ Circular dependencies

### Dependency Inversion Principle

✅ Correct: NAPI Kits defines binding, interface_sdk_c defines interface

❌ Wrong: NAPI Kits depends on component implementations

---

## Cross-Language Bindings

### C++ ↔ ArkTS Binding

**C++ → ArkTS**:
```cpp
napi_value result = nullptr;
napi_create_string_utf8(env, "Hello from C++", NAPI_AUTO_LENGTH, &result);
return result;
```

**ArkTS → C++**:
```cpp
size_t argc = 1;
napi_value argv[1];
napi_get_cb_info(env, info, &argc, argv, nullptr);

napi_valuetype type;
napi_typeof(env, argv[0], &type);

if (type == napi_string) {
    size_t length = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &length);
    std::string str(length, 0);
}
```

### Binding Rules

**Should do**: Keep interfaces simple, use POD types, use explicit type conversions, handle exceptions at boundaries, document type mappings

**Should NOT do**: Directly expose C++ specific types (RefPtr, std::function), use C++ exceptions across boundaries, assume memory management semantics directly correspond

### Error Handling Conventions

```cpp
napi_value MyMethod(napi_env env, napi_callback_info info) {
    napi_value result = nullptr;
    napi_status status = napi_create_string_utf8(env, "Success", NAPI_AUTO_LENGTH, &result);

    if (status != napi_ok) {
        napi_value errInfo = nullptr;
        napi_get_last_error_info(env, nullptr, &errInfo);
        napi_throw(env, errInfo);
        return nullptr;
    }

    return result;
}
```

---

## Memory Management Contract

### Object Lifecycle Management

#### Wrap/Unwrap Pattern

```cpp
napi_value WrapNativeObject(napi_env env, void* nativePtr) {
    napi_value jsObj = nullptr;
    napi_create_object(env, &jsObj);
    napi_wrap(env, jsObj, nativePtr,
        [](void* data, void* hint) { delete static_cast<MyNativeClass*>(data); }, nullptr);
    return jsObj;
}

napi_value UnwrapNativeObject(napi_env env, napi_callback_info info) {
    napi_value jsObj;
    napi_get_cb_info(env, info, nullptr, &jsObj, nullptr);
    void* ptr = nullptr;
    napi_unwrap(env, jsObj, &ptr);
    return static_cast<MyNativeClass*>(ptr);
}
```

#### Prohibited Patterns

❌ Wrong: Raw pointer without cleanup
❌ Wrong: Mixing RefPtr and raw pointer
❌ Wrong: Deleting RefPtr-managed object

### Memory Ownership Transfer

```cpp
napi_value WrapNative(napi_env env, void* nativePtr) {
    napi_value jsObj = nullptr;
    napi_create_object(env, &jsObj);
    napi_wrap(env, jsObj, nativePtr, Finalize, nullptr);
    return jsObj;  // ArkTS owns object
}
```

---

## Error Handling Conventions

### NAPI Error Code Strategy

Use `napi_status` enumeration, not exceptions

### Error Handling Patterns

```cpp
napi_value MyFunction(napi_env env, napi_callback_info info) {
    if (argc < 1) {
        LOGE("Invalid argument count");
        napi_throw_type_error(env, "Expected at least 1 argument");
        return nullptr;
    }

    bool hasPending = false;
    napi_is_exception_pending(env, &hasPending);
    if (hasPending) {
        napi_value exception = nullptr;
        napi_get_and_clear_last_exception(env, &exception);
        LOGE("Caught pending exception");
        return nullptr;
    }

    napi_value result = nullptr;
    napi_status status = napi_create_string_utf8(env, "Success", NAPI_AUTO_LENGTH, &result);
    if (status != napi_ok) {
        napi_value errInfo = nullptr;
        napi_get_last_error_info(env, nullptr, &errInfo);
        napi_throw(env, errInfo);
        return nullptr;
    }
    return result;
}
```

---

## Common Pitfalls

### 1. Interface Breaking Changes

❌ Wrong: Changing existing binding function signature

✅ Correct: Add new method, keep old method compatible, or use default parameters

### 2. Inter-module Circular Dependencies

❌ Wrong: NAPI Kits module depends on component implementation

✅ Correct: Use forward declaration and interface pointer

### 3. Memory Leaks in Callbacks

❌ Wrong: Capturing RefPtr in lambda creates cycle

✅ Correct: Use WeakPtr to break cycle

### 4. Thread Safety Violations

❌ Wrong: Direct NAPI operation from worker thread

✅ Correct: Use thread-safe function with `napi_create_threadsafe_function`

---

## Debugging Methods

### 1. Enable Logging

```cpp
#include "base/log/log_wrapper.h"

#define TAG "NapiKits"
LOGD("%{public}s", "Debug message");
LOGI("%{public}s", "Info message");
LOGW("%{public}s", "Warning message");
LOGE("%{public}s", "Error message");
```

### 2. Dump Binding State

```cpp
void DumpBindingState(std::ostream& os) const {
    os << "NAPI Binding state:\n";
    os << "  wrapped objects: " << wrappedCount_ << "\n";
    os << "  active references: " << activeRefCount_ << "\n";
}
```

### 3. Memory Leak Detection

```cpp
#include "base/memory/memory_monitor.h"

MemoryMonitor::GetInstance().StartTracking();
auto obj = WrapNativeObject(...);
MemoryMonitor::GetInstance().DumpMemoryStats();
```

### Common Issue Locations

| Issue | Possible Cause |
|-------|---------------|
| Binding not found | Library not loaded, check `.so` files |
| Symbol not found | ABI mismatch, rebuild all dependencies |
| Call crashes | Wrong thread, check thread ID in logs |
| Memory leak | RefPtr cycle, use WeakPtr |
| Callback not called | Task runner not running |

---

## Performance Guidelines

### 1. Minimize Virtual Function Call Overhead

✅ Good: Cache interface pointer, Create once in Init(), Reuse

❌ Bad: Create interface every call in Update()

### 2. Batch Property Updates

```cpp
napi_value SetProperties(napi_env env, napi_callback_info info) {
    napi_value obj = nullptr;
    napi_create_object(env, &obj);
    napi_set_property(env, obj, key1, value1);
    napi_set_property(env, obj, key2, value2);
    napi_set_property(env, obj, key3, value3);
    return obj;
}
```

### 3. Avoid Frequent Type Conversions

✅ Good: Cache conversion result in member variable

❌ Bad: Convert string on every access

---

## Testing Guidelines

### Unit Test Structure

```
test/unittest/interfaces/napi/
├── animator/
│   └── animator_napi_test.cpp
├── drag_controller/
│   └── drag_controller_napi_test.cpp
└── ...
```

### Mock Object Example

```cpp
class MockNapiEnv {
public:
    MOCK_METHOD(napi_status, create_string_utf8, (napi_env, const char*, size_t, napi_value*), (override));
    MOCK_METHOD(napi_status, wrap, (napi_env, napi_value, void*, napi_finalize, void*), (override));
};

TEST(NapiBindingTest, WrapNativeObject) {
    MockNapiEnv mockEnv;
    EXPECT_CALL(mockEnv, create_string_utf8).WillOnce(Return(napi_ok));
    WrapNativeObject(&mockEnv, nativePtr);
}
```

### Running Tests

```bash
./build.sh --product-name rk3568 --build-target unittest
cd out/rk3568/tests/ace_engine/unittest
./interfaces_napi_test --gtest_filter="NapiKits*"
```

---

## Summary

### Core Principles

1. **Interface Stability First** - Never break existing APIs
2. **Clear Module Boundaries** - Respect dependency rules
3. **Memory Safety** - Use RefPtr/WeakPtr correctly
4. **Error Handling** - Use error codes, not exceptions
5. **Thread Safety** - Respect thread boundaries

### Remember

NAPI Kits layer is the core implementation layer for ACE Engine NAPI bindings. Any change affects all ArkTS applications invoked through NAPI, all Native module implementations, and all platform adapter layers.

Before modifying NAPI Kits:

- Understand impact on all callers
- Check ABI compatibility
- Run full test suite
- Update documentation
- Consider deprecation process for breaking changes

---

## Related Resources

### Internal Documentation
- 📖 **[NAPI Knowledge Base](../../docs/napi/NAPI_Knowledge_Base.md)** - Complete technical reference for NAPI interfaces
- 📘 **[Inner API CLAUDE](../inner_api/CLAUDE.md)** - Root directory specification

### Reference Documentation
- **[NAPI C API Reference](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/native/ndk/ndk-guides.md)** - OpenHarmony NDK documentation
- **[Node.js N-API Documentation](https://nodejs.org/api/n-api.html)** - Standard N-API specification

### Testing Resources
- `test/unittest/interfaces/napi/` - NAPI binding unit tests
- `test/mock/` - Mock object definitions
