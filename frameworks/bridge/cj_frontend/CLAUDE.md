# CJ Frontend - CLAUDE.md

This file provides guidance for Claude Code when working with the Cangjie (CJ) Frontend in ArkUI ACE Engine.

## Overview

**CJ Frontend** is the bridge layer that connects Cangjie language applications with the ArkUI framework. It uses **FFI (Foreign Function Interface)** to provide cross-language interoperability.

### Core Responsibilities

CJ Frontend is responsible for:

1. **Language Bridge**: Provide FFI interfaces for Cangjie → C++ communication
2. **Page Management**: Handle page lifecycle, routing, and navigation
3. **Component Exposure**: Expose 134+ ArkUI components to Cangjie
4. **Event Handling**: Route events from C++ to Cangjie callbacks
5. **Resource Management**: Integrate with Ace resource system
6. **Dual Architecture Support**: Support both Classic and NG architectures

### Architecture Position

```
Cangjie Application Layer
    ↓ FFI Call
CJ Frontend (This Layer)
    ├── Frontend Layer (frontend/)
    │   ├── CJFrontend (Classic)
    │   └── CJFrontendNG (NG)
    ├── FFI Interface Layer (interfaces/cj_ffi/)
    │   └── 134+ component FFI definitions
    ├── CppView Layer (cppview/)
    │   └── ViewAbstract (view abstraction)
    └── Runtime Layer (runtime/)
        └── CJRuntimeDelegate
    ↓ NG Call
ArkUI Components NG (components_ng/pattern/)
```

### What This File Covers

This document provides:
- **Layer responsibilities** and boundaries
- **Architecture decisions** and design patterns
- **Common pitfalls** and solutions
- **Performance constraints**
- **Debugging guidelines**
- **Best practices** for Cangjie bridge development

**What this file does NOT cover**:
- Individual component implementation details → See `docs/cj_frontend/` knowledge base
- NG component architecture → See `frameworks/core/components_ng/pattern/*/CLAUDE.md`
- Overall ACE Engine architecture → See root `CLAUDE.md`

---

## Directory Structure

```
cj_frontend/
├── frontend/                    # Frontend implementation
│   ├── cj_frontend.cpp/h        # Classic architecture Frontend
│   ├── cj_frontend_ng.cpp/h    # NG architecture Frontend
│   ├── cj_frontend_abstract.cpp/h # Abstract base class
│   ├── cj_page_router.cpp/h     # Classic page router
│   ├── cj_page_router_ng.cpp/h  # NG page router
│   ├── cj_event_handler.cpp/h  # Event handler
│   └── cj_frontend_loader.cpp/h # Frontend loader
│
├── interfaces/cj_ffi/            # FFI interface definitions (134 components)
│   ├── cj_common_ffi.h           # Common FFI data types
│   ├── cj_macro.h                # FFI export macros
│   ├── utils.h                   # Utility functions
│   ├── layout/                   # Layout component FFI
│   ├── base/                     # Base FFI
│   └── [134 component FFI files]
│
├── cppview/                     # C++ view abstraction layer
│   ├── view_abstract.cpp/h       # View abstraction base class
│   ├── native_view.cpp/h         # Native view implementation
│   ├── shape_abstract.cpp/h      # Shape component abstraction
│   ├── interactable_view.cpp/h   # Interactable view
│   ├── canvas_renderer.cpp/h     # Canvas rendering
│   ├── gesture.cpp/h             # Gesture support
│   └── [16 core files]
│
├── runtime/                     # Runtime integration
│   ├── cj_runtime_delegate.cpp/h # Runtime delegate
│   └── cj_runtime.js             # Runtime configuration
│
├── BUILD.gn                     # Build configuration
├── platform.gni                  # Platform configuration
└── [build files]
```

---

## Layer Responsibilities

### Frontend Layer (frontend/)

**Core Responsibilities**:
- Page lifecycle management (OnShow, OnHide, OnBackPressed)
- Routing and navigation (PushPage, ReplacePage, Back)
- Pipeline context management
- Event handling and dispatch
- UI operation (Toast, Dialog, etc.)

**Key Files**:
- `cj_frontend_abstract.h:38-253` - Abstract base class definition
- `cj_frontend.h:25-41` - Classic Frontend implementation
- `cj_frontend_ng.h:26` - NG Frontend implementation

**⚠️ Critical Constraints**:
- ❌ Don't handle rendering directly - Rendering is handled by NG component layer
- ❌ Don't create FrameNode manually in FFI layer - Use CppView layer
- ❌ Don't access NG component internals directly from FFI - Use ModelNG APIs
- ✅ Focus on lifecycle, routing, and event coordination

### FFI Interface Layer (interfaces/cj_ffi/)

**Core Responsibilities**:
- Define extern "C" function boundaries
- Provide 134+ component FFI interfaces (2067+ functions)
- Data type conversion (Cangjie ↔ C++)
- Callback function management
- Memory safety across language boundary

**Key Files**:
- `cj_common_ffi.h:28-444` - Common data types (NativeLength, NativeOption*, etc.)
- `cj_macro.h:19` - CJ_EXPORT macro definition
- `utils.h:27-30` - ExternalString utility

**Interface Pattern**:
```cpp
extern "C" {
CJ_EXPORT void FfiOHOSAceFramework[Component][Action](...);
}
```

**⚠️ Critical Constraints**:
- ❌ Don't use C++ name mangling - Must use extern "C"
- ❌ Don't expose C++ implementation details - Keep FFI clean
- ❌ Don't create complex nested structures in FFI - Keep it flat
- ❌ Don't forget to check null pointers - FFI boundary is unsafe
- ✅ Always validate parameters before use
- ✅ Use simple data types (int32_t, double, const char*)
- ✅ Document thread safety requirements

### CppView Layer (cppview/)

**Core Responsibilities**:
- Provide C++ view abstraction (ViewAbstract)
- Create and manage FrameNode instances
- Implement component wrappers
- Handle property updates and callbacks
- Resource parsing and management

**Key Files**:
- `view_abstract.h:98-150` - ViewAbstract base class
- `native_view.h` - Native view implementation
- `shape_abstract.h` - Shape component abstraction
- `interactable_view.h` - Interactable view (events)

**Class Hierarchy**:
```
ViewAbstract (FFIData)
├── NativeView
├── ShapeAbstract
│   ├── Circle
│   ├── Ellipse
│   └── Rect
└── InteractableView (events)
    ├── Button
    ├── Text
    └── ...
```

**⚠️ Critical Constraints**:
- ❌ Don't bypass NG component layer - Always use ModelNG APIs
- ❌ Don't manually manage FrameNode lifecycle - Use smart pointers
- ❌ Don't mix Cangjie and C++ memory management - Use one or the other
- ✅ Use AceType::RefPtr for smart pointer management
- ✅ Call ModelNG methods to update properties
- ✅ Let NG framework handle rendering and layout

### Runtime Layer (runtime/)

**Core Responsibilities**:
- Cangjie VM integration
- Dynamic library loading (LoadCJLibrary)
- Function table registration (AtCPackage V1/V2/V3)
- UI thread scheduling
- Resource and lifecycle coordination

**Key Files**:
- `cj_runtime_delegate.h` - Runtime delegate class
- `cj_runtime.js` - Runtime configuration

**⚠️ Critical Constraints**:
- ❌ Don't call Cangjie functions from C++ threads - Only UI thread
- ❌ Don't assume dynamic library is loaded - Always check
- ❌ Don't use FFI functions before registration - Verify first
- ✅ Always check FFI function pointers before calling
- ✅ Handle version mismatches gracefully
- ✅ Use proper thread synchronization

---

## Architecture Decisions

### 1. FFI Boundary Design

**Decision**: Use extern "C" for all Cangjie → C++ interfaces

**Rationale**:
- Provides clean language boundary
- Avoids C++ name mangling issues
- Works with Cangjie FFI compiler
- Stable ABI across C++ changes

**Implementation**:
```cpp
// cj_column_ffi.h:23
extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkColumnCreate();
CJ_EXPORT void FfiOHOSAceFrameworkColumnSetWidth(double width, int32_t unit);
}
```

**⚠️ Constraint**: Never change FFI signatures - Breaks Cangjie apps!

---

### 2. Dual Architecture Strategy

**Decision**: Maintain both Classic and NG architectures

**Rationale**:
- **Backward compatibility**: Existing apps continue to work
- **Gradual migration**: Developers can migrate at their own pace
- **Performance**: NG architecture provides better performance
- **Innovation**: New features developed in NG first

**Architecture Choice Guide**:

| Scenario | Recommended Architecture | Reason |
|----------|-------------------------|---------|
| New development | NG | Latest features, better performance |
| Stage model apps | NG | Native support |
| FA model apps | Classic | Compatibility |
| Performance-critical | NG | 30%+ faster |
| Legacy features | Classic | Stable, tested |

**Implementation**:
- Build-time selection via `platform.gni`
```gni
if (invoker.platform != "ohos_ng") {
  sources += [ "frontend/cj_frontend.cpp" ]
} else {
  sources += [ "frontend/cj_frontend_ng.cpp" ]
}
```

**⚠️ Constraint**: Don't mix Classic and NG in same app - Choose one!

---

### 3. Smart Pointer Usage

**Decision**: Use AceType::RefPtr everywhere for memory management

**Rationale**:
- Automatic reference counting
- Prevents memory leaks
- Thread-safe (mostly)
- Consistent with NG component framework

**Example**:
```cpp
// ✅ Correct: Using RefPtr
RefPtr<ViewAbstract> view = ViewAbstract::Create();
RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(...);

// ❌ Wrong: Raw pointers
ViewAbstract* view = new ViewAbstract();  // Leak!
FrameNode* node = new FrameNode(...);     // Leak!
```

**⚠️ Constraint**: Never use raw pointers for FrameNode or ViewAbstract lifecycle objects!

---

### 4. View Stack Pattern

**Decision**: Use ViewStackProcessor for component tree building

**Rationale**:
- Matches declarative UI building pattern
- Automatic parent-child relationship
- Simplified component composition
- Handles nested structures correctly

**Implementation**:
```cpp
// cppview/view_stack_processor.h
ViewStackProcessor::GetInstance().Push(column);
ViewStackProcessor::GetInstance().Push(text);
ViewStackProcessor::GetInstance().Pop();
```

**⚠️ Constraint**: Always push/pop in correct order - Don't skip Pop()!

---

## Common Pitfalls

### 1. Memory Leaks in FFI Callbacks

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Storing raw pointer in callback
void FfiOHOSAceFrameworkButtonSetOnClick(void (*callback)()) {
    // Cangjie side stores raw pointer
    // If FrameNode destroyed, pointer becomes dangling!
}
```

**Consequence**: Crash when callback invoked after component destroyed

**Correct Approach**:
```cpp
// ✅ Use WeakPtr to protect lifecycle
RefPtr<ViewAbstract> view = this;
auto callback = [viewWeak = AceType::WeakPtr<ViewAbstract>(view)]() {
    auto view = viewWeak.Upgrade();
    if (view) {
        // Safe to use
    }
};
```

**Location**: `cppview/interactable_view.cpp`

---

### 2. Thread Violations

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Calling UI from background thread
void BackgroundThreadTask() {
    std::thread t([]() {
        FfiOHOSAceFrameworkTextSetContent("Hello");  // Crash!
    });
}
```

**Consequence**: Crash or undefined behavior

**Correct Approach**:
```cpp
// ✅ Post task to UI thread
auto taskExecutor = GetTaskExecutor();
taskExecutor->PostTask([]() {
    FfiOHOSAceFrameworkTextSetContent("Hello");  // Safe!
});
```

**Location**: `frontend/cj_frontend.cpp`

---

### 3. Ignoring API Version Compatibility

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Using API 11+ feature on API 10- device
void CJFrontendNG::Initialize() {
    // Always uses NodeAnimatableProperty
    offsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f);
    // Crashes on API 10-!
}
```

**Consequence**: Crash on older devices

**Correct Approach**:
```cpp
// ✅ Check API version first
void CJFrontendNG::Initialize() {
    auto context = GetHost()->GetContext();
    isHigherVersion_ = context->GetMinPlatformVersion() >= 11;

    if (isHigherVersion_) {
        offsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f);
    } else {
        lowVersionOffset_ = 0.0f;
    }
}
```

**Location**: `frontend/cj_frontend_ng.cpp`

---

### 4. Resource Object Not Released

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Not releasing resource object
RefPtr<ResourceObject> GetResourceObject(const NativeResourceObject& obj) {
    auto resourceObj = ResourceManager::GetResource(obj);
    // Forgot to call resourceObj->DecRef()
    // Memory leak!
}
```

**Consequence**: Memory leak, app may run out of memory

**Correct Approach**:
```cpp
// ✅ Always release resource after use
RefPtr<ResourceWrapper> CreateResourceWrapper(const NativeResourceObject& obj) {
    RefPtr<ResourceObject> resourceObj = ResourceManager::GetResource(obj);
    auto wrapper = AceType::MakeRefPtr<ResourceWrapper>(resourceObj);
    wrapper->AddRef();  // Will be released by wrapper
    return wrapper;
}
```

**Location**: `cppview/view_abstract.cpp`

---

### 5. Component Creation Without Parent

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Creating component without attaching to tree
auto frameNode = FrameNode::CreateFrameNode("Custom", nodeId, pattern);
// Node created but not attached!
// Will leak or crash!
```

**Consequence**: Memory leak, component never rendered

**Correct Approach**:
```cpp
// ✅ Always attach to parent
auto host = ViewStackProcessor::GetInstance().GetTop();
CHECK_NULL_VOID(host);

auto frameNode = FrameNode::CreateFrameNode("Custom", nodeId, pattern);
host->AddChild(frameNode);  // Attach to tree!
```

**Location**: `cppview/native_view.cpp`

---

### 6. Double Event Registration

**⚠️ Common Mistake**:
```cpp
// ❌ WRONG: Registering callback multiple times
void SetButtonClick() {
    button->SetOnClick(&OnClickCallback);  // Already registered!
    button->SetOnClick(&OnClickCallback);  // Double registered!
}
```

**Consequence**: Event fires multiple times, unexpected behavior

**Correct Approach**:
```cpp
// ✅ Check if already registered before setting
void SetButtonClick() {
    auto eventHub = button->GetEventHub<ClickEventHub>();
    if (!eventHub->GetClickCallback()) {
        button->SetOnClick(&OnClickCallback);
    }
}
```

**Location**: `cppview/interactable_view.cpp`

---

## Debugging Guidelines

### 1. Logging

**Use dedicated log tags**:
```cpp
#include "base/log/ace_trace.h"

// CJ Frontend logs
TAG_LOGI(AceLogTag::ACE_CJ, "CJFrontend initialized");
TAG_LOGD(AceLogTag::ACE_CJ_ROUTER, "Page pushed: %{public}s", url.c_str());

// FFI logs
TAG_LOGI(AceLogTag::ACE_CJ_FFI, "FFI called: %{public}s", funcName);

// CppView logs
TAG_LOGD(AceLogTag::ACE_CJ_VIEW, "ViewAbstract created, type: %{public}s", type.c_str());
```

**Don't use**:
- ❌ `printf` / `std::cout`
- ❌ Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)
- ❌ String concatenation in hot paths

### 2. DumpInfo

**Implement dump method for debugging**:
```cpp
void CJFrontend::DumpFrontend() override
{
    auto json = JsonUtil::Create(true);
    json->Put("frontendType", "CJFrontend");
    json->Push();
    json->Put("stageModel", IsStageModel());
    json->Put("foregroundFrontend", IsForeground());
    json->Put("routerSize", GetRouterSize());

    auto router = GetPageRouterManager();
    if (router) {
        router->GetState(json);
    }
    json->Pop();

    // Print to log
    auto jsonString = json->ToString();
    TAG_LOGI(AceLogTag::ACE_CJ, "%{public}s", jsonString.c_str());
}
```

### 3. Key Data Structure Checks

**Check in debugger**:
```cpp
// Frontend state
stageModel_                // Stage model enabled
foregroundFrontend_        // App is in foreground
pageRouterManager_          // Router instance

// Router state
pageStack_                  // Current page stack
currentUri_                 // Current page URI
currentPageId_              // Current page ID

// Event handler state
asyncEventQueue_           // Pending async events
syncEventQueue_            // Pending sync events
```

### 4. Common Problem Localization

**Problem**: FFI function crashes when called
- Check if dynamic library is loaded: `LoadCJLibrary()`
- Verify FFI function table is registered: `AtCPackage` not null
- Check thread context: Must be on UI thread
- Verify parameter types: especially pointers and strings

**Problem**: Component not visible
- Check if ViewAbstract was created successfully
- Verify component was added to parent (ViewStackProcessor)
- Check if size was set (width/height required for most components)
- Verify parent FrameNode exists and is attached to tree

**Problem**: Event callback not invoked
- Check if callback was registered (not null)
- Verify component is still alive when event fires
- Check if event type matches callback signature
- Verify thread safety (background thread vs UI thread)

---

## Performance Constraints

### 1. FFI Call Overhead

**Target**: Minimize cross-language boundary crossings

**Anti-pattern**:
```cpp
// ❌ WRONG: Calling FFI in a loop
for (int i = 0; i < 1000; i++) {
    FfiOHOSAceFrameworkTextSetFontSize(i * 1.0, 0);  // 1000 FFI calls!
}
```

**Correct Approach**:
```cpp
// ✅ Batch operations
std::vector<double> sizes;
for (int i = 0; i < 1000; i++) {
    sizes.push_back(i * 1.0);
}
FfiOHOSAceFrameworkTextSetFontSizes(sizes.data(), sizes.size());
```

**Constraint**: FFI calls have overhead - minimize frequency!

### 2. Resource Parsing

**Target**: Cache parsed resources

**Anti-pattern**:
```cpp
// ❌ WRONG: Parsing resource every time
void GetColor() {
    auto color = ParseCjColor("$app.color.primary");  // Expensive!
    return color;
}
```

**Correct Approach**:
```cpp
// ✅ Cache parsed resources
std::unordered_map<std::string, Color> colorCache_;

Color GetColor(const std::string& resource) {
    auto it = colorCache_.find(resource);
    if (it != colorCache_.end()) {
        return it->second;
    }

    auto color = ParseCjColor(resource);
    colorCache_[resource] = color;
    return color;
}
```

**Location**: `cppview/view_abstract.cpp`

### 3. LazyForEach Performance

**Target**: Use LazyForEach for large lists

**Anti-pattern**:
```cpp
// ❌ WRONG: Creating all items upfront
for (int i = 0; i < 10000; i++) {
    auto item = CreateItem(i);
    list->AddChild(item);  // 10000 FrameNodes!
}
```

**Correct Approach**:
```cpp
// ✅ Use LazyForEach for on-demand creation
LazyForEach({
    itemCount: 10000,
    getItem: (index) => {
        return CreateItem(index);  // Only create visible + buffer
    }
})
```

**Constraint**: LazyForEach improves initial load time and memory!

### 4. Animation Frame Rate

**Target**: Maintain 60 FPS during animations

**Anti-pattern**:
```cpp
// ❌ WRONG: Heavy operation in animation callback
void OnAnimationFrame() {
    auto result = ExpensiveCalculation();  // Takes 50ms!
    UpdateUI(result);
}
```

**Correct Approach**:
```cpp
// ✅ Keep animations lightweight
void OnAnimationFrame() {
    if (!cachedResult_) {
        cachedResult_ = ExpensiveCalculation();
    }
    UpdateUI(cachedResult_);
}
```

**Constraint**: Drag callbacks can be called 60+ times per second - keep them lightweight!

---

## Special Feature Constraints

### 1. AtCPackage Version Management

**Three Versions**:
- **V1** (`AtCPackage`): Basic functions (25+ functions)
- **V2** (`AtCPackageV2`): Component reuse (4+ functions)
- **V3** (`AtCPackageV3`): Performance optimization (1+ function)

**Version Detection**:
```cpp
// Register V2 if available
if (AtCPackageV2* cjFuncsV2) {
    RegisterCJFuncsV2(cjFuncsV2_callback);
}
```

**⚠️ Constraint**: Always check version before calling version-specific functions!

---

### 2. Page Router Protection

**Nested Router Protection**:
- Don't allow recursive PushPage in OnPageReady
- Validate page URL before pushing
- Check router state before operations

**Example**:
```cpp
UIContentErrorCode CJPageRouter::PushPage(const std::string& url, const std::string& params) {
    // Validate
    if (url.empty()) {
        return UIContentErrorCode::INVALID_URL;
    }

    // Check recursion
    if (IsPushingRecursively()) {
        return UIContentErrorCode::RECURSIVE_CALL;
    }

    // Push
    Push(url, params);
    return UIContentErrorCode::NO_ERROR;
}
```

**Location**: `frontend/cj_page_router.cpp`

---

### 3. Event Threading Model

**Critical Rule**: All UI operations must be on UI thread

**Thread Safety**:
```cpp
// ✅ Correct: Post to UI thread
void BackgroundCallback() {
    auto taskExecutor = GetTaskExecutor();
    taskExecutor->PostTask([]() {
        FfiOHOSAceFrameworkTextSetContent("Update");  // UI thread
    });
}

// ❌ Wrong: Direct call from background
void BackgroundCallback() {
    FfiOHOSAceFrameworkTextSetContent("Update");  // Crash!
}
```

**⚠️ Constraint**: Never call FFI functions from background threads!

---

### 4. Resource Placeholder Resolution

**Placeholder Format**: `$app.color.primary`, `$sys.string.ohos.tz`

**Resolution Timing**:
- ✅ During property setting (SetTextColor, etc.)
- ✅ During theme changes
- ❌ Not in constructor initialization (resources not ready)

**Example**:
```cpp
// ✅ Correct: Resolve when setting property
Color GetColor(const std::string& resource) {
    auto colorObj = ParseCjColor(resource);
    if (!colorObj.has_value()) {
        return Color::BLACK;  // Fallback
    }
    return colorObj.value();
}
```

**Location**: `cppview/view_abstract.cpp`

---

## Best Practices

### 1. Memory Management

**Always use smart pointers**:
```cpp
// ✅ Good: RefPtr for automatic lifecycle management
RefPtr<FrameNode> frameNode_;
RefPtr<ViewAbstract> view_;
RefPtr<PipelineContext> pipelineContext_;

// ❌ Bad: Raw pointers
FrameNode* frameNode_;        // Leak!
ViewAbstract* view_;             // Leak!
```

**WeakPtr for callbacks**:
```cpp
// ✅ Good: WeakPtr prevents dangling pointers
WeakPtr<ViewAbstract> weakView = view;

auto callback = [weakView]() {
    auto view = weakView.Upgrade();
    if (view) {
        view->DoSomething();
    }
};
```

---

### 2. Error Handling

**Always validate FFI parameters**:
```cpp
void FfiOHOSAceFrameworkTextSetContent(const char* content) {
    if (!content) {
        TAG_LOGE(AceLogTag::ACE_CJ_FFI, "content is null!");
        return;
    }

    // Safe to use content
    textLayoutProperty_->UpdateContent(std::string(content));
}
```

**Check return values**:
```cpp
// ✅ Good: Check FFI_ERROR_CODE
int32_t result = FfiOHOSAceFrameworkGetSomeValue();
if (result == FFI_ERROR_CODE) {
    // Handle error
}
```

---

### 3. Code Organization

**Follow single responsibility principle**:
- `frontend/` - Page management, routing, lifecycle
- `interfaces/cj_ffi/` - FFI interface definitions only
- `cppview/` - Component wrappers and view abstraction
- `runtime/` - Cangjie runtime integration

**Don't mix responsibilities**:
- ❌ Don't handle rendering in Frontend layer
- ❌ Don't manage component lifecycle in FFI layer
- ❌ Don't expose implementation details in FFI interfaces

---

### 4. Testing Strategy

**Unit Testing**:
- Mock FFI functions for testing
- Use test doubles for Cangjie callbacks
- Test both Classic and NG paths

**Integration Testing**:
- Test real FFI calls with Cangjie runtime
- Test page routing and navigation
- Test event handling end-to-end

**⚠️ Critical**: Always test on both API 10- and API 11+ when using version-dependent features!

---

## Backward Compatibility

### API Version Differences

**API 10-** (PlatformVersion < 11):
- Uses `lowVersionOffset_` float property
- Sets offset via `SetOffset(OffsetT)` on RenderContext
- No NodeAnimatableProperty support

**API 11+** (PlatformVersion >= 11):
- Uses `offsetProperty_` NodeAnimatableProperty
- Sets offset via `SetOffsetProperty()` on RenderContext
- Supports partial update optimization

**Compatibility Pattern**:
```cpp
void UpdateProperty(float value) {
    if (isHigherVersion_) {
        CHECK_NULL_VOID(offsetProperty_);
        offsetProperty_->Set(value);
    } else {
        lowVersionOffset_ = value;
        GetRenderContext()->SetOffset(OffsetT(0.0f, value));
    }
}
```

---

### Deprecated Features

**None currently deprecated**. All public FFI APIs are stable.

**New Method Constraints**:
- New FFI functions must check API version before use
- New properties must work on both API 10- and API 11+
- Maintain backward compatibility - never break existing Cangjie apps!

---

## Summary

### Core Principles

1. **FFI Boundary is Sacred**
   - All FFI functions use extern "C"
   - Never change FFI signatures
   - Keep FFI interfaces simple and stable

2. **Thread Safety is Mandatory**
   - UI operations must be on UI thread
   - Use TaskExecutor for background work
   - Never call FFI from background threads

3. **Memory Management is Critical**
   - Use AceType::RefPtr everywhere
   - Use WeakPtr in callbacks
   - Never use raw pointers for lifecycle objects

4. **Version Compatibility is Essential**
   - Check API version before using version-specific features
   - Provide fallback implementations for older versions
   - Test on both API 10- and API 11+

5. **Performance Matters**
   - Minimize FFI call frequency
   - Cache parsed resources
   - Use LazyForEach for large lists
   - Keep animation callbacks lightweight

6. **Layer Boundaries Must be Respected**
   - Frontend: Page/routing/lifecycle only
   - FFI: Interface definitions only
   - CppView: Component wrappers and NG integration
   - Runtime: Cangjie VM integration only

### Remember

CJ Frontend is a **bridge layer** - its purpose is to connect Cangjie with ArkUI, not to reimplement ArkUI features.

When in doubt:
1. **Check layer responsibilities** - Is this the right layer for this feature?
2. **Review similar components** - How is this done elsewhere?
3. **Consult the knowledge base** - `docs/cj_frontend/` has detailed guides
4. **Test on both architectures** - Classic and NG
5. **Verify API compatibility** - API 10- and API 11+

---

## Related Documentation

- **Knowledge Base**: [docs/cj_frontend/](../../docs/cj_frontend/) - Complete knowledge base for CJ Frontend
- **Architecture**: [docs/cj_frontend/01_Architecture_Overview.md](../../docs/cj_frontend/01_Architecture_Overview.md) - Architecture overview
- **Component Reference**: [docs/cj_frontend/07_Component_FFI_Reference.md](../../docs/cj_frontend/07_Component_FFI_Reference.md) - Component FFI reference
- **Best Practices**: [docs/cj_frontend/10_Best_Practices.md](../../docs/cj_frontend/10_Best_Practices.md) - Best practices guide
- **Debugging**: [docs/cj_frontend/11_Debugging_Guide.md](../../docs/cj_frontend/11_Debugging_Guide.md) - Debugging guide

## File Locations

**Core Implementation**:
- Frontend Layer: `frameworks/bridge/cj_frontend/frontend/`
- FFI Layer: `frameworks/bridge/cj_frontend/interfaces/cj_ffi/`
- CppView Layer: `frameworks/bridge/cj_frontend/cppview/`
- Runtime Layer: `frameworks/bridge/cj_frontend/runtime/`

**Documentation**:
- Knowledge Base: `docs/cj_frontend/`
- Root CLAUDE.md: `CLAUDE.md`
- Component Knowledge Base: `docs/pattern/`

---

**Last Updated**: 2026-02-04
**Maintainer**: ACE Engine Team
**Feedback**: Report issues via OpenHarmony community
