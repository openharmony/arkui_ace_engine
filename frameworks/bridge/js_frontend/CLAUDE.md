# JS Frontend

This document contains specialized rules for the JS Frontend directory and **must inherit and comply with** the repository root's `CLAUDE.md`. This document only describes constraints and knowledge specific to this directory.

## Overview

JS Frontend is a legacy frontend bridge that converts traditional web-style JS applications (HML/JS/CSS) into executable UI trees. It maintains backward compatibility with existing JS applications while newer applications should use Declarative Frontend (ArkTS/TypeScript).

**Frontend Comparison**:

| Frontend | Directory | Language | Use Case |
|----------|-----------|----------|----------|
| JS Frontend | `js_frontend/` | JavaScript | Legacy web-style apps |
| Declarative Frontend | `declarative_frontend/` | ArkTS/TypeScript | Modern declarative UI (recommended) |
| ArkTS Frontend | `arkts_frontend/` | ArkTS static | Incremental engine |

---

## Architecture

### Three-Layer Architecture

```
JsFrontend (Entry Layer)
    ├─ JsEventHandler
    └─ FrontendDelegate interface
         ↓
FrontendDelegateImpl (Delegate Layer)
    ├─ PageRouteStack management
    ├─ PageMap management
    └─ System API implementation
         ↓
JsAcePage (Page Layer)
    ├─ DOM document
    ├─ Command queue
    ├─ Dirty node tracking
    └─ Bridge management
```

### Command Execution Pattern

```
JS Code
    ↓
Generate DOM Command
    ↓
JsAcePage::PushCommand()
    ↓
JsAcePage::FlushCommands()
    ↓
JsCommand::Execute()
    ↓
Update DOM Tree
    ↓
Mark Dirty Nodes
    ↓
Render Pipeline Updates
```

---

## Responsibilities

### JS Frontend Handles

- **JS engine management**: QuickJS/ARK JS engine lifecycle
- **Page lifecycle management**: Loading, routing, transitions
- **Command execution**: DOM operations via command queue
- **Bridge management**: Animation, Canvas, XComponent bridges
- **Event handling**: Async events from UI to JS
- **System API bridge**: Router, Prompt, Animation APIs

### JS Frontend Does NOT Handle

- Component rendering → Handled by ACE Core render pipeline
- Layout calculation → Handled by LayoutAlgorithm in core
- Gesture recognition → Handled by GestureRecognizer in core
- Window management → Handled by platform adapter

---

## Key Classes

### JsFrontend

**Location**: [js_frontend.h](js_frontend.h)

**Responsibilities**:
- Frontend entry point
- JS engine lifecycle management
- EventHandler coordination

**Key Members**:
- `delegate_` - FrontendDelegateImpl instance
- `jsEngine_` - JS engine instance
- `handler_` - JsEventHandler

### FrontendDelegateImpl

**Location**: [frontend_delegate_impl.h](frontend_delegate_impl.h)

**Responsibilities**:
- Page routing (Push, Back, Replace, Clear)
- System API implementation
- Page stack management
- GroupJsBridge coordination

**Key Members**:
- `pageRouteStack_` - Page route stack
- `pageMap_` - All pages map
- `groupJsBridge_` - JS-Native bridge
- `pageId_` - Current page ID

**PageInfo Structure** ([frontend_delegate_impl.h:81-87](frontend_delegate_impl.h#L81-L87)):
```cpp
struct PageInfo {
    std::string url;
    std::string pageName;
    PageTransitionType transitionType;
    // ... other fields
};
```

### JsAcePage

**Location**: [js_ace_page.h](js_ace_page.h)

**Responsibilities**:
- Page instance management
- DOM document ownership
- Command queue management
- Dirty node tracking
- Bridge lifecycle (Animation, Canvas, XComponent)

**Key Members**:
- `domDoc_` - DOM document
- `jsCommands_` - Command queue
- `dirtyNodes_` - Dirty node list
- `animationBridges_` - Animation bridges
- `canvasBridges_` - Canvas bridges

### JsiEngine

**Location**: [engine/jsi/jsi_engine.h](engine/jsi/jsi_engine.h)

**Responsibilities**:
- JSI engine implementation
- JS code execution
- JS-Native method binding
- Event firing to JS

**Key Members**:
- `runtime_` - ARK JS runtime (Panda/EcmaVM)
- `runningPage_` - Currently running page
- `stagingPage_` - Staging page for navigation

### JsCommand

**Location**: [js_command.h](js_command.h)

**Responsibilities**:
- DOM operation commands (Command Pattern)
- Command execution lifecycle

**Key Subclasses**:
- `JsCommandCreateDomElement`
- `JsCommandUpdateDomElementAttrs`
- `JsCommandRemoveDomElement`
- `JsCommandAddDomElement`
- `JsCommandClosePage`

---

## Critical Invariants (DO NOT BREAK)

### 1. Command Queue Must Be Flushed

**Problem**: Commands generated but not executed

**Wrong**:
```cpp
LoadJs(url);
// Forgot to call FlushCommands()
```

**Correct**:
```cpp
LoadJs(url);
FlushCommands();  // Always flush after LoadJs
```

**Source**: [js_ace_page.cpp:FlushCommands](js_ace_page.cpp)

### 2. Bridge Objects Must Be Cleaned Up

**Problem**: Memory leak from unreleased bridges

**Wrong**:
```cpp
// Bridge created but never released
```

**Correct**:
```cpp
// In OnJsEngineDestroy()
animationBridges_.clear();
canvasBridges_.clear();
```

**Source**: [js_ace_page.cpp:OnJsEngineDestroy](js_ace_page.cpp)

### 3. Thread Safety Must Be Maintained

**Thread Model**:

| Thread | Responsibility | Example Operations |
|--------|----------------|-------------------|
| JS Thread | Execute JS, generate commands | LoadJs(), FireJsEvent() |
| UI Thread | Execute commands, update DOM | JsCommand::Execute(), FlushCommands() |
| Platform Thread | System events, lifecycle | OnShow(), OnHide() |

**Constraint**: Cross-thread communication must use TaskExecutor

**Wrong**:
```cpp
// Accessing UI object from JS thread
auto node = domDoc_->GetDomNode(id);  // NOT thread-safe
```

**Correct**:
```cpp
// Post task to UI thread
taskExecutor_->PostTask(
    [weak, id]() {
        auto page = weak.Upgrade();
        if (page) {
            auto node = page->GetDomNode(id);  // Safe
        }
    },
    TaskExecutor::TaskType::UI);
```

**Source**: [js_frontend.cpp](js_frontend.cpp)

### 4. Page ID Must Be Recycled

**Problem**: Page ID overflow from not recycling IDs

**Wrong**:
```cpp
int32_t pageId = nextPageId_++;
// Never recycles IDs
```

**Correct**:
```cpp
// Implement RecyclePageId()
void FrontendDelegateImpl::RecyclePageId(int32_t pageId) {
    recycledPageIds_.push(pageId);
}

int32_t pageId = recycledPageIds_.empty()
    ? nextPageId_++
    : recycledPageIds_.front();
```

**Source**: [frontend_delegate_impl.cpp](frontend_delegate_impl.cpp)

### 5. Commands Must Execute In Order

**Problem**: Reordering or skipping commands breaks DOM state

**Wrong**:
```cpp
// Processing commands out of order
for (auto cmd : customOrder) {
    cmd->Execute();
}
```

**Correct**:
```cpp
// Process in received order
for (auto& cmd : jsCommands_) {
    cmd->Execute();
}
```

**Source**: [js_command.cpp:Execute](js_command.cpp)

### 6. Dirty Nodes Must Include All Affected Nodes

**Problem**: Only marking parent, not children

**Wrong**:
```cpp
dirtyNodes_.insert(parentId);
// Forgot to mark children
```

**Correct**:
```cpp
// Recursively mark all affected nodes
void MarkDirtyRecursive(NodeId id) {
    dirtyNodes_.insert(id);
    for (auto child : GetChildren(id)) {
        MarkDirtyRecursive(child->GetId());
    }
}
```

**Source**: [js_ace_page.cpp:PushDirtyNode](js_ace_page.cpp)

---

## Common Pitfalls

### 1. Command Queue Not Flushed

**Scenario**: Generated DOM commands but page doesn't update

**Symptoms**:
- Page appears blank
- DOM operations don't take effect

**Root Cause**:
```cpp
LoadJs(pageUrl);
// Missing: FlushCommands();
```

**Solution**:
```cpp
LoadJs(pageUrl);
FlushCommands();  // Must flush after LoadJs
```

**Check**: [js_ace_page.cpp:FlushCommands](js_ace_page.cpp)

### 2. Bridge Memory Leaks

**Scenario**: Increasing memory usage over page navigations

**Symptoms**:
- Memory grows with each page navigation
- Bridge objects not released

**Root Cause**:
```cpp
// Bridge created but not cleaned up
auto bridge = CreateAnimationBridge();
// Never removed from animationBridges_
```

**Solution**:
```cpp
// In OnJsEngineDestroy()
animationBridges_.clear();
canvasBridges_.clear();
xcomponentBridges_.clear();
```

**Check**: [js_ace_page.cpp:OnJsEngineDestroy](js_ace_page.cpp)

### 3. Thread Safety Violations

**Scenario**: Random crashes or data corruption

**Symptoms**:
- Intermittent crashes
- DOM in inconsistent state

**Root Cause**:
```cpp
// Called from JS thread
auto node = domDoc_->GetDomNode(id);  // Unsafe!
```

**Solution**:
```cpp
taskExecutor_->PostTask(
    [weak, id]() {
        auto page = weak.Upgrade();
        if (page) {
            page->GetDomDocument()->GetDomNode(id);  // Safe
        }
    },
    TaskExecutor::TaskType::UI);
```

**Check**: [js_frontend.cpp](js_frontend.cpp)

### 4. Page Stack Invariant Violation

**Problem**: Page stack exceeds limit or becomes corrupted

**Constraints**:
- Stack size <= 32 pages
- Last page cannot be popped (root page)
- Page ID must be unique

**Check**:
```cpp
// Before push
CHECK_FALSE_VOID(pageRouteStack_.size() >= MAX_PAGE_STACK_SIZE);

// Before pop
CHECK_FALSE_VOID(pageRouteStack_.size() <= 1);
```

**Source**: [frontend_delegate_impl.cpp](frontend_delegate_impl.cpp)

### 5. Event Callback Order Issues

**Problem**: Events fired in wrong order

**Correct Order**:
```
OnScrollCallback (scroll start/in progress)
    ↓
FireObserverOnWillScroll (about to scroll, interceptable)
    ↓
UpdateCurrentOffset (update offset)
    ↓
FireOnDidScroll (scroll complete)
    ↓
OnScrollEndCallback (scroll end)
    ↓
FireOnReachStart / FireOnReachEnd (if boundary reached)
```

**Check**: Verify event firing sequence in [js_frontend.cpp](js_frontend.cpp)

---

## Key Workflows

### Page Navigation Flow

```
Application: router.push({ uri: 'pages/detail' })
    ↓
JsFrontend::RunPage()
    ↓ Source: [js_frontend.cpp:RunPage](js_frontend.cpp)
FrontendDelegateImpl::Push()
    ↓ Source: [frontend_delegate_impl.cpp:Push](frontend_delegate_impl.cpp)
Generate PageId → LoadPage()
    ↓
JsiEngine::LoadJs()
    ↓ Source: [engine/jsi/jsi_engine.cpp:LoadJs](engine/jsi/jsi/jsi_engine.cpp)
Execute JS bytecode → Generate DOM commands
    ↓
JsAcePage::FlushCommands()
    ↓ Source: [js_ace_page.cpp:FlushCommands](js_ace_page.cpp)
Execute command queue
    ↓
Update DOM tree → Trigger render
```

### DOM Operation Flow

```
JS Code: document.createElement('div')
    ↓
Generate JsCommandCreateDomElement
    ↓ Source: [js_command.h:JsCommandDomElementCreator](js_command.h)
JsAcePage::PushCommand()
    ↓ Source: [js_ace_page.cpp:PushCommand](js_ace_page.cpp)
Add to jsCommands_ queue
    ↓
JsAcePage::FlushCommands()
    ↓
JsCommand::Execute() for each command
    ↓
DOMDocument::AddNode()
    ↓
PushDirtyNode(nodeId)
    ↓
Render pipeline updates dirty nodes
```

### Event Handling Flow

```
User clicks screen
    ↓
ACE Core: GestureRecognizer detects click
    ↓
JsEventHandler::HandleAsyncEvent()
    ↓ Source: [js_frontend.cpp:HandleAsyncEvent](js_frontend.cpp)
FrontendDelegateImpl::FireAsyncEvent(eventId, param)
    ↓
JsiEngine::FireAsyncEvent()
    ↓ Source: [engine/jsi/jsi_engine.cpp:FireAsyncEvent](engine/jsi/jsi/jsi_engine.cpp)
Call JS callback: onclick(event)
    ↓
JS code executes
```

### Native Module Communication

```
JS Code: import geolocation from '@system.geolocation'
    ↓
Call: geolocation.getLocation(callback)
    ↓
JsiGroupJsBridge::ProcessJsRequest()
    ↓ Source: [engine/jsi/jsi_group_js_bridge.cpp:ProcessJsRequest](engine/jsi/jsi/jsi_group_js_bridge.cpp)
Generate callbackId → Store Promise callback
    ↓
Call Native module: NativeModule::GetLocation(callbackId, data)
    ↓
Async complete: TriggerModuleJsCallback(callbackId, code, data)
    ↓
Call JS callback: resolve(result)
    ↓
JS code receives result
```

**Key files**:
- Bridge interface: [engine/common/group_js_bridge.h](engine/common/group_js_bridge.h)
- Bridge implementation: [engine/jsi/jsi_group_js_bridge.h](engine/jsi/jsi_group_js_bridge.h)

---

## API Mapping

| JS API | FrontendDelegate Method | Constant |
|--------|------------------------|----------|
| `router.push()` | `Push()` | ROUTE_PAGE_PUSH |
| `router.back()` | `Back()` | ROUTE_PAGE_BACK |
| `router.replace()` | `Replace()` | ROUTE_PAGE_REPLACE |
| `router.clear()` | `Clear()` | ROUTE_PAGE_CLEAR |
| `prompt.showToast()` | `ShowToast()` | PROMPT_SHOW_TOAST |
| `prompt.showDialog()` | `ShowDialog()` | PROMPT_SHOW_DIALOG |
| `animation.requestAnimationFrame()` | `RequestAnimationFrame()` | ANIMATION_REQUEST_ANIMATION_FRAME |

**Source**: [frontend_delegate_impl.cpp](frontend_delegate_impl.cpp)

---

## Performance Constraints

### Command Queue Size

**Target**: Keep queue size < 1000 commands

**Anti-pattern**:
```cpp
// Generating too many commands
for (int i = 0; i < 10000; i++) {
    PushCommand(CreateElementCommand());
}
FlushCommands();  // Too many at once
```

**Correct approach**:
```cpp
// Batch commands
for (int i = 0; i < 10000; i++) {
    PushCommand(CreateElementCommand());
    if (jsCommands_.size() >= 500) {
        FlushCommands();  // Flush periodically
    }
}
FlushCommands();  // Final flush
```

### Page Load Time

**Target**: Initial page load < 500ms

**Optimization**:
- Lazy load non-critical JS modules
- Defer image loading
- Use code splitting

### Memory Usage

**Target**: < 10MB per page

**Optimization**:
- Release bridges in OnJsEngineDestroy
- Recycle page IDs
- Clear command queue after flush
- Trigger GC periodically

---

## Debugging

### Log Strategy

**Use dedicated log tags**:
```cpp
TAG_LOGI(AceLogTag::ACE_JSI, "JsFrontend::RunPage url=%{public}s", url.c_str());
TAG_LOGD(AceLogTag::ACE_ENGINE, "JsiEngine::LoadJs pageId=%{public}d", pageId);
TAG_LOGI(AceLogTag::ACE_PAGE, "JsAcePage::FlushCommands count=%{public}zu",
         jsCommands_.size());
```

**Don't use**:
- `printf` / `std::cout`
- Generic log tags (e.g., `AceLogTag::ACE_DEFAULT`)

### Key State Checks

**Frontend state**:
```cpp
delegate_->pageRouteStack_.size()          // Page count
delegate_->pageMap_.size()                 // Total pages
```

**Page state**:
```cpp
page->jsCommands_.size()                   // Pending commands
page->dirtyNodes_.size()                   // Dirty node count
page->domDoc_->GetDomNodesCount()          // DOM node count
```

**Bridge state**:
```cpp
page->animationBridges_.size()            // Animation bridges
page->canvasBridges_.size()               // Canvas bridges
```

### Common Problem Localization

| Problem | Check |
|---------|-------|
| Commands not executing | Check if FlushCommands() called |
| Memory leak | Check bridges cleaned up in OnJsEngineDestroy |
| Navigation failure | Check pageRouteStack_ updated correctly |
| JS events not firing | Check GroupJsBridge event callbacks |
| Page crash | Check thread safety violations |

---

## Migration to Declarative Frontend

**When to use JS Frontend**:
- Legacy applications (HML/JS/CSS)
- Require QuickJS engine
- Old API version applications

**When to migrate to Declarative Frontend**:
- New applications (ArkTS/TypeScript)
- Need modern state management
- Need better performance
- Want to use latest features

**Migration Steps**:
1. Rewrite HML → ArkTS declarative UI
2. Replace `system.router` → `@ohos.router`
3. Replace `@system.prompt` → `@ohos.prompt`
4. Update component APIs to NG syntax
5. Test on target API version
6. Update build configuration

---

## File Structure

### Core Frontend Files

| File | Lines | Purpose |
|------|-------|---------|
| [js_frontend.h](js_frontend.h) | ~300 | Frontend entry, lifecycle |
| [frontend_delegate.h](frontend_delegate.h) | ~500 | Delegate interface |
| [frontend_delegate_impl.h](frontend_delegate_impl.h) | ~600 | Delegate implementation |
| [js_ace_page.h](js_ace_page.h) | ~400 | Page instance, DOM management |
| [js_command.h](js_command.h) | ~500 | Command system |

### Engine Files

| File | Purpose |
|------|---------|
| [engine/common/js_engine.h](engine/common/js_engine.h) | JS engine abstraction |
| [engine/jsi/jsi_engine.h](engine/jsi/jsi_engine.h) | JSI engine implementation |
| [engine/jsi/ark_js_runtime.h](engine/jsi/ark_js_runtime.h) | ARK JS runtime |
| [engine/jsi/jsi_group_js_bridge.h](engine/jsi/jsi_group_js_bridge.h) | JSI Group Bridge |

### Bridge Files

| File | Purpose |
|------|---------|
| [base_animation_bridge.h](engine/common/base_animation_bridge.h) | Animation bridge base |
| [base_canvas_bridge.h](engine/common/base_canvas_bridge.h) | Canvas bridge base |
| [base_xcomponent_bridge.h](engine/common/base_xcomponent_bridge.h) | XComponent bridge base |
| [group_js_bridge.h](engine/common/group_js_bridge.h) | JS Group Bridge interface |

---

## Summary

**Core Principles**:
1. Maintain backward compatibility - Don't break existing JS apps
2. Flush command queue after LoadJs - Commands must execute
3. Respect thread boundaries - JS/UI/Platform threads
4. Clean up bridges - Prevent memory leaks
5. Execute commands in order - Don't reorder command queue
6. Recycle page IDs - Prevent overflow
7. Keep API semantics stable - Don't change method behavior

**Before modifying JS Frontend**:
- Understand command execution flow
- Verify thread safety
- Test with real JS applications
- Check for memory leaks
- Ensure backward compatibility
- Consider migrating to Declarative Frontend instead

**Prefer Declarative Frontend for new code** - JS Frontend is legacy mode maintained for backward compatibility only.
