# Plugin Frontend Documentation

The `plugin_frontend` directory contains the plugin frontend implementation for ACE Engine, which provides a specialized bridge for running JavaScript plugin components in OpenHarmony applications.

## Overview

The Plugin Frontend is a specialized frontend implementation designed to execute JavaScript plugin components (like dynamic widgets, cards, or embedded components) within OpenHarmony applications. It serves as the unique entrance from the ACE backend to the plugin frontend, maintaining a 1:1:1 relationship with AceActivity and AceContainer.

### Key Responsibilities

- **JavaScript Engine Management**: Creates and initializes the JavaScript runtime for plugin execution
- **Page Lifecycle**: Manages the complete lifecycle of plugin pages including loading, rendering, and destruction
- **Manifest Parsing**: Parses and processes `manifest.json` files for plugin configuration
- **Page Stack Management**: Maintains a navigation stack for plugin pages
- **Event Handling**: Bridges events between native C++ and JavaScript layers
- **Resource Management**: Handles i18n, resource configuration, and asset loading

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│  PluginFrontend                                         │
│  - Frontend interface implementation                    │
│  - PluginEventHandler                                   │
│  - JsEngine management                                  │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ↓
┌─────────────────────────────────────────────────────────┐
│  PluginFrontendDelegate                                 │
│  - Page routing (Push/Replace/Back)                     │
│  - Page stack management                                │
│  - Event firing (async/sync)                            │
│  - Timer & Animation management                         │
│  - Resource & i18n configuration                        │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ↓
┌─────────────────────────────────────────────────────────┐
│  JsEngine (QuickJS/V8/etc)                              │
│  - JavaScript code execution                            │
│  - Plugin component rendering                           │
└─────────────────────────────────────────────────────────┘
```

## Directory Structure

```
plugin_frontend/
├── BUILD.gn                          # Build configuration
├── plugin_frontend.h                 # Main frontend class
├── plugin_frontend.cpp               # Frontend implementation
├── plugin_frontend_delegate.h        # Delegate class
└── plugin_frontend_delegate.cpp      # Delegate implementation
```

## Core Classes

### 1. PluginFrontend

**Location**: [plugin_frontend.h](plugin_frontend.h)

**Inheritance**: `Frontend` → `PluginFrontend`

**Purpose**: Main frontend class that implements the `Frontend` interface for plugin components.

**Key Member Variables**:
```cpp
RefPtr<Framework::PluginFrontendDelegate> delegate_;
RefPtr<AceEventHandler> handler_;
RefPtr<Framework::JsEngine> jsEngine_;
RefPtr<AccessibilityManager> accessibilityManager_;
bool foregroundFrontend_ = false;
bool isSubWindow_ = false;
bool pageLoaded_ = false;
double density_ = 1.0;
```

**Initialization Flow**:
1. `Initialize()` - Creates and sets up the frontend with task executor
2. `AttachPipelineContext()` - Attaches to rendering pipeline
3. `SetAssetManager()` - Sets asset manager for resource loading
4. `RunPage()` - Loads and displays the main plugin page

**Key Methods**:

| Method | Purpose |
|--------|---------|
| `Initialize()` | Initialize frontend with JS engine and delegate |
| `RunPage()` | Load and display the main plugin page |
| `PushPage()` | Navigate to a new page (adds to stack) |
| `ReplacePage()` | Replace current page (removes current, adds new) |
| `OnBackPressed()` | Handle back button press |
| `OnShow()/OnHide()` | Handle visibility changes |
| `UpdateState()` | Update application lifecycle state |
| `LoadPluginJsCode()` | Load JavaScript source code |
| `LoadPluginJsByteCode()` | Load pre-compiled bytecode |
| `UpdatePlugin()` | Update plugin content dynamically |
| `TriggerGarbageCollection()` | Trigger JS garbage collection |

### 2. PluginFrontendDelegate

**Location**: [plugin_frontend_delegate.h](plugin_frontend_delegate.h)

**Inheritance**: `FrontendDelegate` → `PluginFrontendDelegate`

**Purpose**: Manages page routing, lifecycle, and communication with JavaScript engine.

**Key Member Variables**:
```cpp
std::atomic<uint64_t> pageIdPool_;          // Page ID allocator (bit field)
int32_t pageId_;                            // Current page ID
bool isRouteStackFull_;                     // Route stack overflow flag
bool isStagingPageExist_;                   // Page loading flag
std::string mainPagePath_;                  // Main page path
std::vector<PageInfo> pageRouteStack_;      // Page navigation stack
std::unordered_map<int32_t, RefPtr<JsAcePage>> pageMap_;  // Active pages
std::unordered_map<int32_t, std::string> pageParamMap_;   // Page parameters

RefPtr<Framework::ManifestParser> manifestParser_;
RefPtr<Framework::AccessibilityNodeManager> jsAccessibilityManager_;
RefPtr<MediaQueryInfo> mediaQueryInfo_;
RefPtr<GroupJsBridge> groupJsBridge_;
```

**Constants**:
```cpp
constexpr int32_t MAX_ROUTER_STACK = 32;          // Maximum pages in stack
constexpr int32_t MAX_PAGE_ID_SIZE = 64;          // Maximum concurrent pages
constexpr int32_t TOAST_TIME_MAX = 10000;         // Max toast duration (ms)
constexpr int32_t TOAST_TIME_DEFAULT = 1500;      // Default toast duration (ms)
```

**Page ID Management**:

The delegate uses an atomic bit field for efficient page ID allocation:

```cpp
int32_t GenerateNextPageId() {
    for (int32_t idx = 0; idx < MAX_PAGE_ID_SIZE; ++idx) {
        uint64_t bitMask = (1ULL << idx);
        if ((bitMask & pageIdPool_.fetch_or(bitMask)) == 0) {
            return idx;  // Return first available ID
        }
    }
    return INVALID_PAGE_ID;
}

void RecyclePageId(int32_t pageId) {
    uint64_t bitMask = (1ULL << pageId);
    pageIdPool_.fetch_and(~bitMask);  // Clear the bit
}
```

**Key Methods**:

| Method | Purpose |
|--------|---------|
| `RunPage()` | Parse manifest and load main page |
| `Push()` | Push new page onto navigation stack |
| `Replace()` | Replace current page with new one |
| `Back()` | Navigate back to previous page |
| `Clear()` | Clear all invisible pages |
| `GetStackSize()` | Get current navigation stack size |
| `LoadPage()` | Load a page by URL |
| `LoadJS()` | Execute JavaScript for page |
| `OnPageReady()` | Handle page load completion |
| `FireAsyncEvent()` | Fire asynchronous event to JS |
| `FireSyncEvent()` | Fire synchronous event to JS |
| `WaitTimer()` | Set up timer/interval |
| `ClearTimer()` | Cancel timer |
| `RequestAnimationFrame()` | Request animation frame callback |
| `CancelAnimationFrame()` | Cancel animation frame |
| `ShowToast()` | Display toast message |
| `ShowDialog()` | Display dialog with buttons |
| `GetAssetContent()` | Load asset file content |
| `GetI18nData()` | Get i18n resources |
| `GetResourceConfiguration()` | Get resource configuration |
| `ChangeLocale()` | Change application locale |
| `RegisterFont()` | Register custom font |
| `HandleImage()` | Load image information |

### 3. PluginEventHandler

**Location**: [plugin_frontend.h](plugin_frontend.h#L226)

**Inheritance**: `AceEventHandler` → `PluginEventHandler`

**Purpose**: Handles events from native components and dispatches them to JavaScript.

**Supported Event Types**:
- Touch events (`TouchInfoToString`)
- Mouse events (`MouseInfoToString`)
- Swipe events (`SwipeInfoToString`)
- Key events
- Generic async/sync events

**Event Conversion Flow**:

Native C++ Event → Event String → JavaScript Callback

Example for touch events:
```json
{
  "touches": [{
    "globalX": 100,
    "globalY": 200,
    "localX": 50,
    "localY": 100,
    "size": 10
  }],
  "changedTouches": [...]
}
```

## Page Navigation System

### Navigation Stack

The plugin frontend maintains a navigation stack with the following structure:

```cpp
struct PageInfo {
    int32_t pageId;           // Unique page identifier
    std::string url;          // Page URL/path
    bool isRestore;           // Restoration flag
    std::string params;       // Page parameters
    std::vector<std::string> snapshot; // Page snapshot
};
std::vector<PageInfo> pageRouteStack_;
```

### Navigation Operations

#### 1. Push (Navigate Forward)

```cpp
void PluginFrontendDelegate::Push(const PageTarget& target, const std::string& params)
```

**Flow**:
1. Check if route stack is full (MAX_ROUTER_STACK = 32)
2. Resolve page path using manifest router
3. Generate new page ID
4. Load page with JS execution
5. On success: Add to route stack, update current page

#### 2. Replace (Replace Current)

```cpp
void PluginFrontendDelegate::Replace(const PageTarget& target, const std::string& params)
```

**Flow**:
1. Resolve page path
2. Generate new page ID
3. Load replacement page
4. On success: Remove current page, add new page to stack

#### 3. Back (Navigate Backward)

```cpp
void PluginFrontendDelegate::BackWithTarget(const PageTarget& target, const std::string& params)
```

**Flow**:
1. If URL is empty: Pop to previous page
2. If URL specified: Pop to specific page
3. On transition end: Destroy intermediate pages, update current page

#### 4. Clear (Remove All Inactive)

```cpp
void PluginFrontendDelegate::Clear()
```

**Flow**:
1. Keep only the top (current) page
2. Destroy all other pages
3. Clear route stack except current page

### Page Lifecycle

```
LoadPage() → LoadJS() → OnPageReady() → OnPushPageSuccess()
    ↓              ↓            ↓                ↓
Create Page    Execute JS   Build DOM      Add to Stack
                              ↓                ↓
                        Render Page    Set Current Page
                              ↓
                        OnPageShow() → Fire "viewappear" event
```

**Lifecycle Events**:
- `viewappear` - Page becomes visible
- `viewdisappear` - Page becomes hidden
- `viewsuspended` - Page is suspended
- `onNewRequest` - New request received
- `onBackPress` - Back button pressed

## Manifest Parsing

The `manifest.json` file contains plugin configuration:

```json
{
  "app": {
    "bundleName": "com.example.plugin",
    "vendor": "example",
    "version": {
      "code": 1000000,
      "name": "1.0.0"
    }
  },
  "router": {
    "entry": "pages/index/index",
    "pages": [
      "pages/index/index",
      "pages/detail/detail"
    ]
  },
  "window": {
    "designWidth": 720,
    "autoDesignWidth": true
  }
}
```

**Parsed Information**:
- App ID, name, version
- Router configuration (entry page, page list)
- Window configuration (design width, auto sizing)
- i18n configuration
- Resource configuration

## Event System

### Async Events

```cpp
void PluginFrontendDelegate::FireAsyncEvent(
    const std::string& eventId,
    const std::string& param,
    const std::string& jsonArgs)
```

**Format**: `eventId + param + ",null" + ",null" + ["," + jsonArgs]`

Example:
```javascript
// JavaScript receives
eventHandler("click", param, null, null, jsonArgs);
```

### Sync Events

```cpp
bool PluginFrontendDelegate::FireSyncEvent(
    const std::string& eventId,
    const std::string& param,
    const std::string& jsonArgs,
    std::string& result)
```

**Flow**:
1. Generate unique callback ID
2. Post sync task to JS thread
3. Wait for result via `SetCallBackResult()`
4. Return result as boolean (true = "true" string)

## Timer Management

### Setting Timers

```cpp
void PluginFrontendDelegate::WaitTimer(
    const std::string& callbackId,
    const std::string& delay,
    bool isInterval,
    bool isFirst)
```

- `delay`: Delay in milliseconds
- `isInterval`: true for `setInterval`, false for `setTimeout`
- `isFirst`: true for initial call, false for interval repeats

### Clearing Timers

```cpp
void PluginFrontendDelegate::ClearTimer(const std::string& callbackId)
```

Uses `CancelableCallback` for timer cancellation.

## Animation Frame Management

### Request Animation Frame

```cpp
void PluginFrontendDelegate::RequestAnimationFrame(const std::string& callbackId)
```

**Flow**:
1. Create cancelable task with system timestamp
2. Add to animation frame task queue
3. Execute on next frame via pipeline callback

### Cancel Animation Frame

```cpp
void PluginFrontendDelegate::CancelAnimationFrame(const std::string& callbackId)
```

## Resource Management

### Asset Loading

```cpp
bool GetAssetContent(const std::string& url, std::string& content);
bool GetAssetContent(const std::string& url, std::vector<uint8_t>& content);
std::string GetAssetPath(const std::string& url);
```

**Asset Types**:
- JavaScript files (`.js`)
- JSON configuration (`.json`)
- i18n files (`i18n/*.json`)
- Resource files (`resources/*/string.json`)
- Media files (images, fonts)

### i18n Support

```cpp
void PluginFrontendDelegate::GetI18nData(std::unique_ptr<JsonValue>& json)
```

**Folder Structure**:
```
i18n/
├── en-US.json
├── zh-CN.json
└── ...
```

**Fallback Mechanism**:
1. Try exact locale match (e.g., `zh-CN`)
2. Try language fallback (e.g., `zh`)
3. Try default locale

### Resource Configuration

```cpp
void PluginFrontendDelegate::GetResourceConfiguration(std::unique_ptr<JsonValue>& json)
void PluginFrontendDelegate::LoadResourceConfiguration(
    std::map<std::string, std::string>& mediaResourceFileMap,
    std::unique_ptr<JsonValue>& currentResourceData)
```

**Resource Folders**:
- `resources/base/` - Default resources
- `resources/mdpi/` - Medium DPI (320x480)
- `resources/hdpi/` - High DPI (480x800)
- `resources/xhdpi/` - Extra High DPI (720x1280)
- `resources/xxhdpi/` - Extra Extra High DPI (1080x1920)

## Dialog and Toast

### Toast

```cpp
void PluginFrontendDelegate::ShowToast(
    const NG::ToastInfo& toastInfo,
    std::function<void(int32_t)>&& callback)
```

**Parameters**:
- `message`: Toast message text
- `duration`: Duration in milliseconds (clamped to 1500-10000ms)
- `bottom`: Distance from bottom
- `isRightToLeft`: RTL text direction

### Dialog

```cpp
void PluginFrontendDelegate::ShowDialog(
    const std::string& title,
    const std::string& message,
    const std::vector<ButtonInfo>& buttons,
    bool autoCancel,
    std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
```

**Callbacks**:
- `success` - Button click (returns button index)
- `cancel` - Dialog cancelled
- `complete` - Dialog dismissed

**Button Info**:
```cpp
struct ButtonInfo {
    std::string text;       // Button text
    std::string color;      // Text color
};
```

## Accessibility

### Accessibility Manager

```cpp
RefPtr<Framework::AccessibilityNodeManager> jsAccessibilityManager_;
```

**Features**:
- Accessibility event firing
- Node inspection
- Accessibility callback initialization
- Root node tracking

### Accessibility Events

```cpp
void PluginFrontendDelegate::FireAccessibilityEvent(
    const AccessibilityEvent& accessibilityEvent)
```

**Event Structure**:
```cpp
struct AccessibilityEvent {
    int32_t nodeId;        // Node ID
    std::string eventType; // Event type
};
```

## Build Configuration

### BUILD.gn Template

```gni
template("plugin_frontend") {
  ohos_source_set(target_name) {
    subsystem_name = ace_engine_subsystem
    part_name = ace_engine_part

    sources = [
      "plugin_frontend.cpp",
      "plugin_frontend_delegate.cpp",
    ]

    deps = []
    if (use_hilog) {
      external_deps = [ "hilog:libhilog" ]
    }
  }
}
```

**Platform Targets**:
- `plugin_frontend_ohos` - OHOS platform
- `plugin_frontend_ohos_ng` - OHOS NG platform
- `plugin_frontend_windows` - Windows (preview tool)
- `plugin_frontend_mac` - macOS (preview tool)
- `plugin_frontend_linux` - Linux (preview tool)

## Threading Model

### Task Executor

The plugin frontend uses a multi-threaded task executor:

| Thread Type | Purpose |
|-------------|---------|
| JS | JavaScript execution |
| UI | Rendering & UI operations |
| PLATFORM | Platform-specific operations |

### Task Posting

```cpp
// Async task
taskExecutor_->PostTask(
    [] { /* task */ },
    TaskExecutor::TaskType::JS,
    "TaskName"
);

// Sync task (with return value)
taskExecutor_->PostSyncTask(
    [&result] { /* task that sets result */ },
    TaskExecutor::TaskType::JS,
    "TaskName"
);

// Delayed task
taskExecutor_->PostDelayedTask(
    callback,
    TaskExecutor::TaskType::JS,
    delayMs,
    "TaskName"
);
```

## Memory Management

### Smart Pointers

Uses `RefPtr` (reference-counted smart pointer) throughout:

```cpp
RefPtr<Framework::PluginFrontendDelegate> delegate_;
RefPtr<Framework::JsEngine> jsEngine_;
RefPtr<Framework::JsAcePage> page;
```

### Page Cleanup

```cpp
void PluginFrontendDelegate::OnPageDestroy(int32_t pageId)
```

**Cleanup Steps**:
1. Destroy JS page instance
2. Remove from page map
3. Remove from parameter map
4. Recycle page ID
5. Clear DOM document

### WeakPtr for Callbacks

```cpp
auto weak = AceType::WeakClaim(this);
// In callback
auto delegate = weak.Upgrade();
if (delegate) {
    // Safe to use delegate
}
```

## Error Handling

### Page Errors

```cpp
enum class UIContentErrorCode {
    NO_ERRORS,              // Success
    INVALID_PAGE_ID,        // Page ID allocation failed
    STAGING_PAGE_EXIST,     // Page already loading
    NULL_POINTER,           // Null pointer encountered
    // ... more error codes
};
```

### Route Stack Overflow

```cpp
if (pageRouteStack_.size() >= MAX_ROUTER_STACK) {
    isRouteStackFull_ = true;
    EventReport::SendPageRouterException(
        PageRouterExcepType::PAGE_STACK_OVERFLOW_ERR,
        page->GetUrl()
    );
}
```

### Exception Reporting

```cpp
EventReport::SendPageRouterException(
    PageRouterExcepType::RUN_PAGE_ERR,
    url
);
EventReport::SendAppStartException(
    AppStartExcepType::JS_ENGINE_CREATE_ERR
);
```

## Key Use Cases

### 1. Loading a Plugin Page

```cpp
// In PluginFrontend
UIContentErrorCode PluginFrontend::RunPage(
    const std::string& url,
    const std::string& params)
{
    CHECK_NULL_RETURN(delegate_, UIContentErrorCode::NULL_POINTER);
    return delegate_->RunPage(url, params);
}

// In PluginFrontendDelegate
UIContentErrorCode PluginFrontendDelegate::RunPage(
    const std::string& url,
    const std::string& params)
{
    // 1. Parse manifest.json
    manifestParser_->Parse(jsonContent);

    // 2. Get main page path
    mainPagePath_ = manifestParser_->GetRouter()->GetPagePath(url);

    // 3. Load page
    return LoadPage(GenerateNextPageId(), PageTarget(mainPagePath_), false, params);
}
```

### 2. Handling Native Events

```cpp
// Touch event from component
void PluginEventHandler::HandleAsyncEvent(
    const EventMarker& eventMarker,
    const BaseEventInfo& info)
{
    // 1. Convert event to JSON string
    std::string eventParam;
    TouchInfoToString(info, eventParam);

    // 2. Fire event to JavaScript
    delegate_->FireAsyncEvent(
        eventMarker.GetData().eventId,
        param,
        eventParam
    );

    // 3. Fire accessibility event
    delegate_->FireAccessibilityEvent(accessibilityEvent);
}
```

### 3. Updating Plugin Content

```cpp
void PluginFrontend::UpdatePlugin(const std::string& content)
{
    CHECK_NULL_VOID(delegate_);
    delegate_->UpdatePlugin(content);
}

void PluginFrontendDelegate::UpdatePlugin(const std::string& content)
{
    auto pageId = GetRunningPageId();
    auto page = GetPage(pageId);

    if (Container::IsCurrentUseNewPipeline()) {
        // NG pipeline
        FireDeclarativeOnUpdateWithValueParamsCallback(content);
    } else {
        // Legacy pipeline
        page->FireDeclarativeOnUpdateWithValueParamsCallback(content);
    }
}
```

### 4. Setting Timers

```cpp
void PluginFrontendDelegate::WaitTimer(
    const std::string& callbackId,
    const std::string& delay,
    bool isInterval,
    bool isFirst)
{
    int32_t delayTime = StringToInt(delay);

    // Create cancelable timer
    CancelableCallback<void()> cancelableTimer;
    cancelableTimer.Reset([callbackId, delay, isInterval, call = timer_] {
        call(callbackId, delay, isInterval);
    });

    // Store and post delayed task
    timeoutTaskMap_.try_emplace(callbackId, cancelableTimer);
    taskExecutor_->PostDelayedTask(
        cancelableTimer,
        TaskExecutor::TaskType::JS,
        delayTime,
        "TimerCallback"
    );
}
```

## Integration with JS Engine

### JS Engine Initialization

```cpp
bool PluginFrontend::Initialize(
    FrontendType type,
    const RefPtr<TaskExecutor>& taskExecutor)
{
    // 1. Create delegate with callbacks
    InitializeFrontendDelegate(taskExecutor);

    // 2. Initialize JS engine with delegate
    taskExecutor->PostSyncTask([weakEngine, delegate] {
        auto jsEngine = weakEngine.Upgrade();
        jsEngine->Initialize(delegate);
    }, TaskExecutor::TaskType::JS);

    return true;
}
```

### Callback Registration

The delegate registers callbacks with the JS engine:

- `loadJs_` - Load JavaScript for page
- `dispatcherCallback_` - Set message dispatcher
- `asyncEvent_` - Fire async event
- `syncEvent_` - Fire sync event
- `updatePage_` - Update page
- `destroyPage_` - Destroy page
- `timer_` - Timer callback
- `mediaQueryCallback_` - Media query changes
- `requestAnimationCallback_` - Animation frame
- `jsCallback_` - JS callback

## Best Practices

### 1. Thread Safety

```cpp
// Use mutex for shared data access
std::lock_guard<std::mutex> lock(mutex_);
pageRouteStack_.push_back(pageInfo);
```

### 2. WeakPtr for Callbacks

```cpp
// Always use WeakPtr to prevent dangling pointers
auto weak = AceType::WeakClaim(this);
taskExecutor_->PostTask([weak] {
    auto delegate = weak.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->DoSomething();
}, TaskExecutor::TaskType::JS, "TaskName");
```

### 3. Page ID Management

```cpp
// Always recycle page IDs after page destruction
void PluginFrontendDelegate::OnPageDestroy(int32_t pageId)
{
    destroyPage_(pageId);
    RecyclePageId(pageId);  // Important!
}
```

### 4. Resource Paths

```cpp
// Use manifest router for path resolution
std::string pagePath = manifestParser_->GetRouter()->GetPagePath(url);
if (!pagePath.empty()) {
    LoadPage(pageId, PageTarget(pagePath));
}
```

### 5. Event Parameters

```cpp
// Format event parameters correctly
std::string args = param;           // Event-specific params
args.append(",null");               // Callback (usually null)
args.append(",null");               // DOM changes (usually null)
if (!jsonArgs.empty()) {
    args.append(",").append(jsonArgs);  // Method arguments
}
```

## Debugging

### Logging Tags

```cpp
TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "Plugin frontend destroyed");
```

### Dump Information

```cpp
void PluginFrontend::DumpFrontend() const
{
    int32_t routerIndex = 0;
    std::string routerName;
    std::string routerPath;
    delegate_->GetState(routerIndex, routerName, routerPath);

    DumpLog::GetInstance().AddDesc("Components: " +
        std::to_string(delegate_->GetComponentsCount()));
    DumpLog::GetInstance().AddDesc("Path: " + routerPath);
    DumpLog::GetInstance().AddDesc("Length: " +
        std::to_string(routerIndex));
}
```

## Common Issues

### 1. Route Stack Overflow

**Symptom**: `isRouteStackFull_` flag set, cannot push more pages

**Solution**:
- Use `Clear()` to remove invisible pages
- Check for page leaks (pages not destroyed)
- Increase `MAX_ROUTER_STACK` if needed

### 2. Page ID Exhaustion

**Symptom**: `INVALID_PAGE_ID` returned from `GenerateNextPageId()`

**Solution**:
- Ensure `OnPageDestroy()` is called for all pages
- Verify `RecyclePageId()` is called after destruction
- Check for page ID leaks

### 3. Staging Page Exists

**Symptom**: `STAGING_PAGE_EXIST` error when loading page

**Cause**: Previous page still loading

**Solution**:
- Wait for current page to finish loading
- Check `isStagingPageExist_` flag before loading

### 4. Timer Not Firing

**Symptom**: Timer callback not executed

**Possible Causes**:
- Task executor not initialized
- Callback ID mismatch
- Timer cancelled prematurely

**Solution**:
- Verify `timer_` callback is set
- Check callback ID matches
- Ensure task executor is running

## Performance Considerations

### Page Management

- **Page Pool**: Use atomic bit operations for O(1) page ID allocation
- **Route Stack**: Keep stack size reasonable (max 32 pages)
- **Page Cleanup**: Always destroy unused pages to free memory

### Event Handling

- **Async Events**: Post to JS thread immediately
- **Sync Events**: Use sync tasks sparingly (block JS thread)
- **Event Batching**: Batch multiple DOM updates together

### Resource Loading

- **Lazy Loading**: Load resources on-demand
- **Caching**: Cache parsed resources (manifest, i18n)
- **Fallback**: Use resource fallback for better performance

## Future Enhancements

Potential areas for improvement:

1. **Dynamic Plugin Loading**: Support loading plugins at runtime
2. **Plugin Isolation**: Better isolation between plugin instances
3. **Hot Reload**: Support hot-reloading plugin code
4. **Plugin Communication**: Inter-plugin communication mechanisms
5. **Resource Optimization**: Better resource caching and preloading
6. **Performance Monitoring**: Built-in performance metrics
