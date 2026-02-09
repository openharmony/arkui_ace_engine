# Inner API Subdirectory Specification

This document contains specialized specifications for the Inner API directory and **must inherit and comply with** the `CLAUDE.md` in the repository root directory. This document only describes constraints and knowledge specific to this directory.

> **Document Version**: v1.0
> **Last Updated**: 2026-02-02
> **Source Version**: OpenHarmony ace_engine (master branch)

---

## 📋 Table of Contents

1. [Overview](#overview)
2. [Module Architecture](#module-architecture)
3. [Core Responsibilities](#core-responsibilities)
4. [Interface Stability Constraints](#interface-stability-constraints)
5. [Module Dependency Rules](#module-dependency-rules)
6. [Cross-Language Bindings](#cross-language-bindings)
7. [Memory Management Contract](#memory-management-contract)
8. [Error Handling Conventions](#error-handling-conventions)
9. [Common Pitfalls](#common-pitfalls)
10. [Debugging Methods](#debugging-methods)
11. [Performance Guidelines](#performance-guidelines)
12. [Testing Guidelines](#testing-guidelines)
13. [API Migration Guide](#api-migration-guide)

---

## Overview

### Inner API Positioning

**Inner API** (`interfaces/inner_api/`) is the **interface layer** of ACE Engine, located between the framework layer (frameworks) and platform adapter layer (adapter), providing core interfaces and infrastructure support for the entire ace_engine.

**Core Value**:
- 🏗️ **Architecture Bridge** - Connects frameworks/core, frameworks/bridge and adapter layers
- 🎯 **Interface Abstraction** - Defines stable internal interfaces, isolating underlying platform changes
- 🔧 **Infrastructure** - Provides memory management, geometry calculation, animation and other basic capabilities
- 🛡️ **Platform Adaptation** - Supports both OpenHarmony and Previewer platforms

### Position in ACE Engine

```
Application Layer (ArkTS Applications)
    ↓
frameworks/bridge (Frontend Bridge Layer)
    ↓
frameworks/core (Core Framework Layer)
    ↓
interfaces/inner_api (Interface Layer) ← This document's scope
    ↓
adapter (Platform Adapter Layer)
    ↓
OpenHarmony Subsystems (Ability, Window, Graphic2D, MMI, IPC)
```

### Code Scale

- **Total Files**: 273 files
  - Header files: 203
  - Source files: 70
- **Main Modules**: 8 modules
- **Build Artifacts**: 7 main libraries

---

## Module Architecture

### Overview of 8 Core Modules

| Module | Path | Build Artifact | Core Responsibilities | Primary Users |
|--------|------|----------------|----------------------|---------------|
| **Ace** | `ace/` | `libace_uicontent.z.so` | UI content management core interfaces | `adapter/entrance`, `frameworks/bridge` |
| **AceKit** | `ace_kit/` | `ace_kit.a` | Infrastructure (memory, geometry, animation) | All NG components |
| **DrawableDescriptor** | `drawable_descriptor/` | (static library) | Drawable resource descriptor | Image loading system |
| **FormRender** | `form_render/` | `libace_form_render.z.so` | Card renderer | Card service |
| **UIServiceManager** | `ui_service_manager/` | `libui_service_mgr.z.so` | UI service management client | Application layer |
| **UISession** | `ui_session/` | `libui_session.z.so` | UI session management (cross-process) | DevEco Studio |
| **XComponentController** | `xcomponent_controller/` | `libace_xcomponent_controller.z.so` | XComponent control | `XComponentPattern` |
| **Drawable** | `drawable/` | `libdrawable_inner_ani.so` | Drawable ANI interface | ANI module |

### Module Dependency Diagram

```
                    ┌─────────────────────────────────────────┐
                    │         frameworks/bridge               │
                    │         frameworks/core                 │
                    └─────────────┬───────────────────────────┘
                                  │
                                  ↓
                    ┌─────────────────────────────────────────┐
                    │          Inner API Layer                │
                    │  ┌───────────────────────────────────┐  │
                    │  │  Ace ←→ AceKit ←→ Drawable       │  │
                    │  │  ↓        ↓         ↓             │  │
                    │  │  FormRender (depends on Ace)      │  │
                    │  │  ↓                            │  │
                    │  │  UISession (depends on Ace)      │  │
                    │  │  UIServiceMgr (independent)      │  │
                    │  │  ↓                            │  │
                    │  │  XComponentController (on Ace)   │  │
                    │  └───────────────────────────────────┘  │
                    └─────────────┬───────────────────────────┘
                                  │
                                  ↓
                    ┌─────────────────────────────────────────┐
                    │         adapter/ohos                    │
                    └─────────────────────────────────────────┘
```

### Module Selection Rules

```
Use Case → Module Mapping:

UI lifecycle management → Ace (UIContent)
Memory management → AceKit (AceType, RefPtr, WeakPtr)
Geometry calculation → AceKit (Dimension, Size, Offset, Point)
Animation curves → AceKit (Curve, CubicCurve)
Image abstraction → DrawableDescriptor
Card rendering → FormRender
Cross-process communication (debugging) → UISession
UI service management → UIServiceManager
Custom component control → XComponentController
ANI interface → Drawable
```

---

## Core Responsibilities

### Inner API is Responsible For

1. **Interface Definition** - Define stable public APIs
2. **Infrastructure** - Provide memory management, geometry, animation tools
3. **Cross-module Coordination** - Coordinate interactions between frameworks and adapter
4. **Multi-language Bridging** - C++ ↔ ArkTS ↔ NAPI bindings

### Inner API is NOT Responsible For

- ❌ **Component Implementation** → **frameworks/core/components_ng**
- ❌ **Layout Algorithms** → **frameworks/core/layout**
- ❌ **Platform Adaptation** → **adapter/ohos**
- ❌ **Frontend Parsing** → **frameworks/bridge**

### Module-Specific Responsibilities

#### Ace Module

**Responsible for**:
- UIContent lifecycle (Create, Initialize, Destroy, Foreground, Background)
- Navigation control
- UI event handling
- Hot reload support

**NOT Responsible for**:
- ❌ Component tree building → frameworks/core
- ❌ Layout measurement → frameworks/core/layout
- ❌ Rendering → adapter/ohos/rosen

#### AceKit Module

**Responsible for**:
- Memory management (AceType, RefPtr, WeakPtr)
- Geometry tools (Dimension, Size, Offset, Point)
- Animation curves
- Pattern base classes
- Property system

**NOT Responsible for**:
- ❌ Specific component logic → components_ng/pattern/*
- ❌ Layout algorithms → frameworks/core/layout

---

## Interface Stability Constraints

### Public API Semantics (Immutable)

#### Ace Module

```cpp
// UIContent - Core methods
class UIContent {
    // Must maintain backward compatibility
    virtual UIContentErrorCode Initialize(
        Window* window,
        const std::string& url,
        napi_value storage) = 0;

    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Destroy() = 0;
    virtual void ProcessPointerEvent(const std::shared_ptr<PointerEvent>& event) = 0;
};
```

**Prohibited**:
- ❌ Changing parameter order
- ❌ Changing return value type
- ❌ Changing method semantics (e.g., Destroy() should clean up all resources)
- ❌ Removing public methods

#### AceKit Module

```cpp
// AceType - Memory management
class AceType {
    template<typename T>
    static RefPtr<T> MakeRefPtr(Args&&... args);

    template<typename T>
    static RefPtr<T> DynamicCast(const RefPtr<AceType>& ptr);
};
```

**Prohibited**:
- ❌ Changing RefPtr/WeakPtr semantics
- ❌ Modifying reference counting behavior
- ❌ Changing type casting behavior

### API Versioning Rules

| API Level | Stability | Breaking Changes Allowed |
|-----------|-----------|-------------------------|
| Internal Interface | Stable within major version | No |
| Public Interface (Exported) | Stable across minor versions | No |
| Experimental Interface | Unstable | Yes (must mark deprecation) |

### Deprecation Process

```cpp
// Example: Deprecating old API

// 1. Mark as deprecated (use for at least 2 minor versions)
class ACE_DEPRECATED("Use NewMethod() instead") UIContent {
    virtual void OldMethod() = 0;  // Deprecated in API 10
    virtual void NewMethod() = 0;  // Added in API 10
};

// 2. Remove in next major version
class UIContent {
    // OldMethod() removed in API 11 (major version upgrade)
    virtual void NewMethod() = 0;
};
```

---

## Module Dependency Rules

### Allowed Dependencies

```
Inner API module dependencies:

AceKit ← Independent (infrastructure)
    ↑
    │
Ace ← Depends on AceKit
    ↑
    │
UISession ← Depends on Ace
    ↑
    │
XComponentController ← Depends on Ace

DrawableDescriptor ← Independent
    ↑
    │
Ace ← Uses DrawableDescriptor for images

FormRender ← Depends on Ace, AceKit
```

### Prohibited Dependencies

**Prohibited**:
- ❌ **Inner API → frameworks/core**: Inner API cannot depend on component implementations
- ❌ **Inner API → frameworks/bridge**: Inner API cannot depend on frontends
- ❌ **AceKit → Ace**: AceKit must remain an independent base layer
- ❌ **Circular Dependencies**: Module A → Module B → Module A

### Dependency Inversion Principle

```cpp
// ✅ Correct: Inner API defines interface, adapter implements
// Inner API (interfaces/inner_api/ace/ui_content.h)
class UIContent {
    virtual void Initialize(...) = 0;
};

// Adapter (adapter/ohos/entrance/ui_content_impl.cpp)
class UIContentImpl : public UIContent {
    void Initialize(...) override {
        // Platform-specific implementation
    }
};

// ❌ Wrong: Inner API directly depends on adapter
// interfaces/inner_api/ace/ui_content.h
#include "adapter/ohos/entrance/platform_specific.h"  // Prohibited
```

---

## Cross-Language Bindings

### C++ ↔ ArkTS Binding

#### Example: UIContent Binding

**C++ Interface** (inner_api/ace/ui_content.h):
```cpp
class UIContent {
    virtual void SetBackgroundColor(const Color& color) = 0;
};
```

**ArkTS Declaration** (bridge/declarative_frontend/jsview/js_ui_content.ts):
```typescript
export class UIContent {
    SetBackgroundColor(color: string | Color | ResourceColor): void;
}
```

**Binding Layer** (adapter/ohos/entrance/ui_content_impl.cpp):
```cpp
void UIContentImpl::SetBackgroundColor(const Color& color) {
    // Convert ArkTS color to C++ Color
    // Call framework layer
}
```

### NAPI Bridging

```cpp
// napi_bind.cpp
static napi_value SetBackgroundColor(napi_env env, napi_callback_info info) {
    // 1. Extract parameters from JavaScript
    napi_value jsColor;
    napi_get_cb_info(env, info, &argc, &jsColor, nullptr, nullptr);

    // 2. Convert JavaScript color to C++ Color
    Color color = ConvertNapiToColor(env, jsColor);

    // 3. Call C++ interface
    uiContent->SetBackgroundColor(color);

    return nullptr;
}
```

### Binding Rules

**Should do**:
- ✅ Keep interfaces simple, use POD (Plain Old Data) types
- ✅ Use explicit type conversions
- ✅ Handle exceptions at language boundaries
- ✅ Document type mappings

**Should NOT do**:
- ❌ Directly expose C++-specific types (RefPtr, std::function)
- ❌ Use C++ exceptions across language boundaries
- ❌ Assume memory management semantics directly correspond

---

## Memory Management Contract

### AceType Memory Management (AceKit)

#### Interface User Rules

```cpp
// Rule 1: Use RefPtr for interface objects
RefPtr<UIContent> uiContent = UIContent::Create(context, runtime);

// Rule 2: Pass RefPtr to transfer ownership
void RegisterUIContent(const RefPtr<UIContent>& content);

// Rule 3: Use WeakPtr to break cycles
class MyClass {
    WeakPtr<UIContent> uiContent_;  // Prevent cycles
};

// Rule 4: Always check WeakPtr::Upgrade() result
RefPtr<UIContent> locked = uiContent_.Upgrade();
if (locked) {
    locked->Foreground();
}
```

#### Prohibited Patterns

```cpp
// ❌ Wrong: Raw pointer
UIContent* content = new UIContentImpl();  // Memory leak!

// ❌ Wrong: Mix RefPtr and raw pointer
RefPtr<UIContent> ref = ...;
UIContent* raw = ref.Get();  // Dangerous if ref goes out of scope

// ❌ Wrong: Delete RefPtr-managed object
RefPtr<UIContent> ref = ...;
delete ref.Get();  // Double delete!
```

### Memory Ownership Transfer

```cpp
// Factory function: Returns RefPtr (caller owns)
RefPtr<UIContent> UIContent::Create(...) {
    return AceType::MakeRefPtr<UIContentImpl>();
}

// Setter: Accepts RefPtr (transfers shared ownership)
void SetUIContent(const RefPtr<UIContent>& content) {
    uiContent_ = content;  // Both share ownership
}

// Getter: Returns RefPtr (caller gets shared ownership)
RefPtr<UIContent> GetUIContent() const {
    return uiContent_;
}
```

---

## Error Handling Conventions

### Error Code Strategy (Ace Module)

```cpp
// UIContentErrorCode - Use error codes, not exceptions
enum class UIContentErrorCode {
    NO_ERROR = 0,
    INVALID_WINDOW,
    INVALID_URL,
    INIT_FAILED,
    // ...
};

// Return error code
virtual UIContentErrorCode Initialize(...) = 0;

// Caller checks error code
UIContentErrorCode err = uiContent->Initialize(...);
if (err != UIContentErrorCode::NO_ERROR) {
    LOGE("Initialize failed: %{public}d", err);
    return;
}
```

### Error Handling Patterns

#### Pattern 1: Error Code + Logging
```cpp
UIContentErrorCode UIContentImpl::Initialize(...) {
    if (!window) {
        LOGE("Initialize failed: window is null");
        return UIContentErrorCode::INVALID_WINDOW;
    }
    return UIContentErrorCode::NO_ERROR;
}
```

#### Pattern 2: Optional Return + Logging
```cpp
std::optional<RefPtr<UIContent>> CreateUIContent(...) {
    if (!context) {
        LOGW("Cannot create UIContent: context is null");
        return std::nullopt;
    }
    return AceType::MakeRefPtr<UIContentImpl>();
}
```

#### Pattern 3: Callback Error
```cpp
using ResultCallback = std::function<void(bool success, int32_t errorCode)>;

void AsyncOperation(ResultCallback callback) {
    bool success = DoOperation();
    if (!success) {
        callback(false, ERROR_CODE);
    }
}
```

---

## Common Pitfalls

### 1. Interface Breaking Changes

**⚠️ Common Mistake**:
```cpp
// ❌ Wrong: Changing method signature in existing interface
class UIContent {
    // Old version
    virtual void Initialize(Window* window) = 0;

    // New version - breaks all consumers!
    virtual void Initialize(Window* window, const std::string& url) = 0;
};
```

**✅ Correct Approach**:
```cpp
// Add new method with different name
class UIContent {
    // Keep old method for compatibility
    virtual void Initialize(Window* window) = 0;

    // Add new method
    virtual void InitializeWithURL(Window* window, const std::string& url) = 0;
};

// Or use default parameters (if ABI compatible)
class UIContent {
    virtual void Initialize(Window* window, const std::string& url = "") = 0;
};
```

### 2. Circular Dependencies Between Modules

**⚠️ Common Mistake**:
```cpp
// ❌ Wrong: Ace depends on FormRender
// ace/ui_content.h
#include "form_render/form_renderer.h"  // Prohibited

class UIContent {
    RefPtr<FormRenderer> renderer_;  // Creates circular dependency
};
```

**✅ Correct Approach**:
```cpp
// Use forward declaration and interfaces
// ace/ui_content.h
class FormRendererInterface;  // Forward declaration

class UIContent {
    FormRendererInterface* renderer_;  // Use interface pointer
};

// form_render/form_renderer.h
#include "ace/ui_content.h"  // OK: FormRender depends on Ace
```

### 3. Memory Leaks in Callbacks

**⚠️ Common Mistake**:
```cpp
// ❌ Wrong: Capturing RefPtr in lambda creates cycle
class MyClass {
    RefPtr<UIContent> uiContent_;

    void RegisterCallback() {
        uiContent_->SetCallback([this, uiContent = uiContent_]() {
            // uiContent_ and this keep each other alive, forever leak
        });
    }
};
```

**✅ Correct Approach**:
```cpp
// Use WeakPtr to break cycle
class MyClass {
    RefPtr<UIContent> uiContent_;

    void RegisterCallback() {
        WeakPtr<UIContent> weakUi = uiContent_;
        uiContent_->SetCallback([weakUi]() {
            auto ui = weakUi.Upgrade();
            if (ui) {
                // Safe to use
            }
        });
    }
};
```

### 4. Thread Safety Violations

**⚠️ Common Mistake**:
```cpp
// ❌ Wrong: Access UIContent from wrong thread
// Created on UI thread
auto uiContent = UIContent::Create(context, runtime);

// Access from worker thread
std::thread([&]() {
    uiContent->Foreground();  // Crash! UI thread only
}).detach();
```

**✅ Correct Approach**:
```cpp
// Use task runner to post to correct thread
uiContent->GetTaskRunner()->PostTask([&]() {
    uiContent->Foreground();  // Runs on UI thread
});
```

### 5. Violating Dependency Direction

**⚠️ Common Mistake**:
```cpp
// ❌ Wrong: AceKit depends on Ace
// ace_kit/include/ui/base/ace_type.h
#include "ace/ui_content.h"  // Prohibited!

class AceType {
    // This creates circular dependency
};
```

**✅ Correct Approach**:
```cpp
// AceKit stays independent
// ace_kit/include/ui/base/ace_type.h
// Does not include any Ace module headers

class AceType {
    // Pure infrastructure
};

// Ace can use AceKit
// ace/ui_content.h
#include "ace_kit/include/ui/base/ace_type.h"

class UIContent : public AceType {
    // OK: Ace depends on AceKit
};
```

---

## Debugging Methods

### 1. Enable Logging

```cpp
#include "base/log/log_wrapper.h"

// Use appropriate log tags
#define TAG "InnerApi"

// Log levels
LOGD("%{public}s", "Debug message");
LOGI("%{public}s", "Info message");
LOGW("%{public}s", "Warning message");
LOGE("%{public}s", "Error message");
```

### 2. Dump Interface State

```cpp
// Implement dump method for debugging
class UIContentImpl : public UIContent {
    void DumpInfo(std::ostream& os) const override {
        os << "UIContent state:\n";
        os << "  initialized: " << initialized_ << "\n";
        os << "  foreground: " << isForeground_ << "\n";
        os << "  url: " << url_ << "\n";
    }
};

// Use in debugging
uiContent->DumpInfo(std::cerr);
```

### 3. Memory Leak Detection

```cpp
// Use memory monitoring (AceKit feature)
#include "base/memory/memory_monitor.h"

// Enable memory monitoring
MemoryMonitor::GetInstance().StartTracking();

// Create objects
RefPtr<UIContent> content = UIContent::Create(...);

// Check for leaks
MemoryMonitor::GetInstance().DumpMemoryStats();
```

### 4. Common Issue Location

| Issue | Possible Cause | Checklist |
|-------|---------------|-----------|
| **Interface not found** | Library not loaded | Check `.so` files in `out/` |
| **Symbol not found** | ABI mismatch | Rebuild all dependencies |
| **Call crashes** | Wrong thread | Check thread ID in logs |
| **Memory leak** | RefPtr cycle | Use WeakPtr, check dumps |
| **Callback not called** | Task runner not running | Check task runner status |

### 5. Key Data Structure Checks

**Check in debugger**:

```cpp
// Ace module
currentOffset_           // Current offset
scrollableDistance_      // Scrollable distance

// AceKit module
refCount_                // Reference count
weakRefCount_            // Weak reference count

// UISession module
sessionId_               // Session ID
proxy_                   // Proxy object
```

---

## Performance Guidelines

### 1. Minimize Virtual Function Call Overhead

```cpp
// ✅ Good: Cache interface pointer
class MyClass {
    RefPtr<UIContent> uiContent_;

    void Init() {
        uiContent_ = UIContent::Create(...);  // Create once
    }

    void Update() {
        uiContent_->ProcessVsyncEvent(time);  // Reuse
    }
};

// ❌ Bad: Create interface every call
void Update() {
    auto content = UIContent::Create(...);  // Expensive!
    content->ProcessVsyncEvent(time);
}
```

### 2. Use Move Semantics for Large Objects

```cpp
// ✅ Good: Use std::move for strings/vectors
virtual void SetURL(std::string url) = 0;

// Call
uiContent->SetURL(std::string("https://..."));  // Copy
uiContent->SetURL(std::move(urlString));         // Move (faster)

// ❌ Bad: Pass large objects by value
virtual void SetData(std::vector<uint8_t> data) = 0;  // Potential copy
```

### 3. Batch Interface Calls

```cpp
// ✅ Good: Batch property updates
uiContent->BeginPropertyUpdates();
uiContent->SetWidth(100.0);
uiContent->SetHeight(200.0);
uiContent->SetBackgroundColor(Color::RED);
uiContent->EndPropertyUpdates();  // Apply all at once

// ❌ Bad: Individual updates (triggers notification each time)
uiContent->SetWidth(100.0);        // Notification
uiContent->SetHeight(200.0);       // Notification
uiContent->SetBackgroundColor(...); // Notification
```

### 4. Avoid Frequent Measure/Layout

```cpp
// ❌ Bad: Trigger layout in scroll callback
void ScrollPattern::OnScrollCallback(float offset, int32_t source) override
{
    UpdateCurrentOffset(offset, source);
    FireOnDidScroll(offset);  // Triggers new layout if callback modifies properties
}

// ✅ Good: Coalesce layout requests
// Use requestFrame to coalesce multiple layout requests
// Only trigger layout at scroll end (OnScrollEndCallback)
```

---

## Testing Guidelines

### 1. Unit Test Structure

```
test/unittest/interfaces/inner_api/
├── ace/
│   ├── ui_content_test.cpp
│   ├── navigation_controller_test.cpp
│   └── ui_event_test.cpp
├── ace_kit/
│   ├── ace_type_test.cpp
│   ├── geometry_test.cpp
│   └── animation_test.cpp
├── drawable_descriptor/
│   └── drawable_descriptor_test.cpp
└── ...
```

### 2. Interface Mock Example

```cpp
// Mock UIContent for testing
class MockUIContent : public UIContent {
public:
    MOCK_METHOD(UIContentErrorCode, Initialize,
              (Window* window, const std::string& url, napi_value storage),
              (override));
    MOCK_METHOD(void, Foreground, (), (override));
    MOCK_METHOD(void, Background, (), (override));
};

// Use mock in tests
TEST(MyClassTest, UsesUIContent) {
    auto mockContent = std::make_shared<MockUIContent>();
    EXPECT_CALL(*mockContent, Initialize(_, _, _))
        .WillOnce(Return(UIContentErrorCode::NO_ERROR));

    MyClass myClass(mockContent);
    ASSERT_TRUE(myClass.Initialize());
}
```

### 3. Memory Leak Testing

```cpp
TEST(AceTypeTest, NoMemoryLeak) {
    // Record initial memory
    size_t initialMemory = MemoryMonitor::GetInstance().GetCurrentMemory();

    {
        // Create objects
        RefPtr<MyClass> obj1 = AceType::MakeRefPtr<MyClass>();
        RefPtr<MyClass> obj2 = AceType::MakeRefPtr<MyClass>();
        obj1->SetChild(obj2);
    }

    // Objects should be destroyed
    size_t finalMemory = MemoryMonitor::GetInstance().GetCurrentMemory();
    ASSERT_NEAR(initialMemory, finalMemory, 1024);  // Allow small tolerance
}
```

### 4. Running Tests

```bash
# Build unit tests
./build.sh --product-name rk3568 --build-target unittest

# Run inner_api tests
cd out/rk3568/tests/ace_engine/unittest
./interfaces_test --gtest_filter="InnerApi*"
```

---

## API Migration Guide

### Migrating from Old API to New API

#### Example: UIContent API Changes

**Old API (Deprecated)**:
```cpp
// Old way (API 9)
UIContent* content = new UIContentImpl();
content->Init(window);
content->SetPageUrl(url);
content->CreateRootView();
```

**New API (Recommended)**:
```cpp
// New way (API 10+)
RefPtr<UIContent> content = UIContent::Create(context, runtime);
UIContentErrorCode err = content->Initialize(window, url, storage);
if (err != UIContentErrorCode::NO_ERROR) {
    // Handle error
}
```

#### Migration Checklist

- [ ] Replace factory methods (new → Create)
- [ ] Use error codes instead of exceptions
- [ ] Use RefPtr instead of raw pointers
- [ ] Update method signatures
- [ ] Update callback signatures
- [ ] Test all migrated code

---

## Summary

### Core Principles

1. **Interface Stability First** - Never break existing APIs
2. **Clear Module Boundaries** - Respect dependency rules
3. **Memory Safety** - Use AceType correctly
4. **Error Handling** - Use error codes, not exceptions
5. **Thread Safety** - Respect thread boundaries

### Remember

Inner API is the foundation of ACE Engine. Any change affects:
- All component implementations (frameworks/core/components_ng)
- All frontend bridges (frameworks/bridge)
- All platform adapters (adapter/*)

Before modifying Inner API:
- Understand impact on all consumers
- Check ABI compatibility
- Run full test suite
- Update documentation
- Consider deprecation process for breaking changes

---

## Related Resources

### Internal Documentation
- 📖 **[Inner API Complete Knowledge Base](../../docs/interfaces/inner_api/inner_api_Knowledge_Base.md)** - In-depth technical reference
- 📄 **[README.md](README.md)** - Quick index

### Reference Documentation
- [ace_kit/include/ui/base/MEMORY_DESIGN.md](ace_kit/include/ui/base/MEMORY_DESIGN.md) - Memory management design
- [CLAUDE.md](../../CLAUDE.md) - Project guidance document

### Testing Resources
- `test/unittest/interfaces/inner_api/` - Unit tests
- `test/mock/ohos_mock/` - Mock objects
