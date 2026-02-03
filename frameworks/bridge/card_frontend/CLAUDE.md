# Card Frontend - CLAUDE.md

This file provides quick reference for Claude Code when working with the Card Frontend subsystem.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [Card_Frontend_Knowledge_Base_CN.md](../../../docs/architecture/Card_Frontend_Knowledge_Base_CN.md)

---

## Overview

**Card Frontend** is a specialized bridge layer for rendering ArkUI cards (widgets/forms) in OpenHarmony. It supports two parsing modes: JSON-based (JS-style) and declarative (ArkTS bytecode) cards.

**Architecture**: Frontend → Delegate → PageRouterManager → PipelineContext

**Key Features**:
- JSON-based card parsing (`JsCardParser`) for legacy JS cards
- Declarative card rendering (`CardFrontendDeclarative`) for ArkTS cards
- Event handling and fire card actions
- Data updates and state management
- MediaQuery and resource management
- Accessibility support

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `card_frontend.h/cpp` | ~277 (h) / ~347 (cpp) | Base CardFrontend class (JSON cards) |
| `card_frontend_declarative.h/cpp` | ~165 (h) / ~241 (cpp) | Declarative CardFrontend (ArkTS cards) |
| `card_frontend_delegate.h/cpp` | ~51 (h) / ~96 (cpp) | Delegate for JS-style cards |
| `card_frontend_delegate_declarative.h/cpp` | ~93 (h) / ~77 (cpp) | Delegate for declarative cards |
| `form_frontend_declarative.h/cpp` | ~173 (h) / ~178 (cpp) | FormFrontend (extends DeclarativeFrontend) |
| `form_frontend_delegate_declarative.h/cpp` | ~136 (h) / ~93 (cpp) | FormFrontendDelegate (extends FrontendDelegateDeclarative) |
| `js_card_parser.h/cpp` | ~238 (h) / ~2062 (cpp) | JSON-based card parser |

**Path**: `frameworks/bridge/card_frontend/`

---

## Core Class Hierarchy

```
                        Frontend (base)
                           ↑
          ┌────────────────┼────────────────┐
          │                │                │
    CardFrontend   FormFrontendDeclarative  (others)
          │                │
          ↓                ↓
    CardFrontendDelegate  FormFrontendDelegateDeclarative
                          (extends FrontendDelegateDeclarative)

                        Frontend
                           ↑
          ┌────────────────┼────────────────┐
          │                │                │
    DeclarativeFrontend    ↓           (others)
                          FormFrontendDeclarative
                                ↓
                     FormFrontendDelegateDeclarative
```

---

## Card Types Comparison

| Feature | JSON Card (CardFrontend) | Declarative Card (CardFrontendDeclarative) | Form (FormFrontendDeclarative) |
|---------|-------------------------|-------------------------------------------|-------------------------------|
| **File Extension** | `.json` | `.abc` | `.abc` |
| **Parser** | `JsCardParser` | `PageRouterManager` | `PageRouterManager` |
| **Page Type** | `JsAcePage` | NG Page Router | NG Page Router |
| **Language** | JSON-based | ArkTS bytecode | ArkTS bytecode |
| **Event Handling** | `FireCardEvent` | `FireCardAction` | `FireCardAction` |
| **Usage** | Legacy JS cards | Modern eTS cards | Dynamic components |

---

## Key Components

### 1. CardFrontend (JSON-based)

**Source**: `card_frontend.h:32-230` | `card_frontend.cpp:26-346`

Base class for JSON-based card rendering.

**Key Methods**:

| Method | Description |
|--------|-------------|
| `RunPage(url, params)` | Load and render JSON card page |
| `UpdateData(dataList)` | Update card data |
| `OnPageLoaded(page)` | Handle page load completion |
| `HandleSurfaceChanged(w, h)` | Handle surface size changes |
| `OnMediaFeatureUpdate()` | Handle media query updates |

**Member Variables**:

| Variable | Type | Description |
|----------|------|-------------|
| `parseJsCard_` | `RefPtr<JsCardParser>` | JSON card parser |
| `delegate_` | `RefPtr<CardFrontendDelegate>` | Card delegate |
| `manifestParser_` | `RefPtr<ManifestParser>` | Manifest parser |
| `pageLoaded_` | `bool` | Page load status flag |
| `cardHapPath_` | `std::string` | Card HAP path |
| `cardId_` | `uint64_t` | Card node ID |

---

### 2. CardFrontendDeclarative (ArkTS-based)

**Source**: `card_frontend_declarative.h:37-116` | `card_frontend_declarative.cpp:28-240`

Declarative frontend for ArkTS bytecode cards.

**Key Methods**:

| Method | Description |
|--------|-------------|
| `RunPage(url, params)` | Load and render .abc card page |
| `GetPageRouterManager()` | Get page router manager |
| `SetLoadCardCallBack()` | Set dynamic card loading callback |
| `UpdatePageData(dataList)` | Update card data |

**Special Features**:
- Uses `.abc` (ArkTS bytecode) files
- Shares JS engine with host pipeline
- Supports dynamic card loading

---

### 3. CardFrontendDelegate

**Source**: `card_frontend_delegate.h:26-47` | `card_frontend_delegate.cpp:18-95`

Delegate for JS-style cards, manages page and accessibility.

**Key Methods**:

```cpp
void FireCardEvent(const EventMarker& eventMarker, const std::string& params)
RefPtr<JsAcePage>& CreatePage(int32_t pageId, const std::string& url)
RefPtr<JsAcePage>& GetPage()
RefPtr<AccessibilityNodeManager> GetJsAccessibilityManager()
```

---

### 4. CardFrontendDelegateDeclarative

**Source**: `card_frontend_delegate_declarative.h:34-89` | `card_frontend_delegate_declarative.cpp:19-76`

Delegate for declarative cards, extends `FrontendDelegateDeclarativeNG`.

**Key Methods**:

```cpp
UIContentErrorCode RunCard(const std::string& url, const std::string& params,
                          const std::string& profile, int64_t cardId)
void FireCardEvent(const EventMarker& eventMarker, const std::string& params)
void FireCardAction(const std::string& action)
void UpdatePageData(const std::string& dataList)
double MeasureText(MeasureContext context)
```

**Callbacks**:
- `LoadCardCallback` - For dynamic card loading
- `UpdateCardDataCallback` - For data updates

---

### 5. FormFrontendDeclarative

**Source**: `form_frontend_declarative.h:35-170` | `form_frontend_declarative.cpp:23-177`

Form frontend for dynamic components, extends `DeclarativeFrontend`.

**Key Methods**:

| Method | Description |
|--------|-------------|
| `RunPage(url, params)` | Run form page |
| `RunDynamicPage(url, params, entryPoint)` | Run dynamic page |
| `GetFormSrcPath(uri, suffix)` | Get form source path |
| `SetErrorEventHandler()` | Set error callback |

**Properties**:

```cpp
std::string bundleName_      // Bundle name
std::string moduleName_      // Module name
bool isBundle_               // Is bundle flag
bool isFormRender_           // Is form render flag
```

---

### 6. JsCardParser

**Source**: `js_card_parser.h:31-234` | `js_card_parser.cpp:22-2062`

JSON-based card parser for JS-style cards.

**Key Methods**:

| Method | Description |
|--------|-------------|
| `Initialize()` | Initialize parser from JSON body |
| `CreateDomNode(page, rootJson, parentId)` | Create DOM nodes |
| `UpdateDomNode(page, rootJson, parentId)` | Update DOM nodes |
| `UpdatePageData(dataList, page)` | Update page data |
| `ParseAttributes()` | Parse component attributes |
| `ParseStyles()` | Parse component styles |
| `ParseEvents()` | Parse event handlers |

**Parsing Status**:

```cpp
enum class ParsingStatus { CREATE, UPDATE };
```

**Special Parsing Features**:

| Feature | Syntax Example |
|---------|---------------|
| Variable | `{{value}}` |
| Multi-variable | `$f({{key1}} {{key2}})` |
| Resource | `$r('app.media.icon')` |
| I18n | `$t('strings.title')` |
| Plurals | `$tc('strings.plurals', 2)` |
| Ternary | `{{flag ? key1 : key2}}` |
| Logical | `{{flag1 && flag2}}` |

---

## Event Handling

### CardFrontend Event Flow

```
User Interaction
    ↓
CardEventHandler::HandleAsyncEvent()
    ↓
CardFrontendDelegate::FireCardEvent()
    ↓
PipelineContext::OnActionEvent()
    ↓
Accessibility Event (if applicable)
```

### Declarative Card Event Flow

```
User Interaction
    ↓
CardEventHandlerDeclarative::HandleAsyncEvent()
    ↓
CardFrontendDelegateDeclarative::FireCardAction()
    ↓
PipelineContext::OnActionEvent()
```

---

## Data Update Flow

### JSON Card Update

```
UpdateData(dataList)
    ↓ (PostTask to JS thread)
UpdatePageData(dataList)
    ↓
JsCardParser::UpdatePageData(dataList, page)
    ↓
SetUpdateStatus(page) → UpdateDomNode()
```

**Source**: `card_frontend.cpp:263-283`

### Declarative Card Update

```
UpdateData(dataList)
    ↓ (PostTask to UI thread)
UpdatePageData(dataList)
    ↓
delegate_->UpdatePageData(dataList)
    ↓
updateCardData_ callback (if set)
```

**Source**: `card_frontend_declarative.cpp:176-195`

---

## Common Operations

### Loading a JSON Card

```cpp
// Source: card_frontend.cpp:78-106
std::string urlPath = GetFormSrcPath(GetFormSrc(), ".json");
taskExecutor_->PostTask(
    [weak, urlPath, params] {
        frontend->LoadPage(urlPath, params);
    },
    TaskExecutor::TaskType::JS, "ArkUICardFrontendRunPage");
```

### Loading a Declarative Card

```cpp
// Source: card_frontend_declarative.cpp:81-108
std::string urlPath = GetFormSrcPath(GetFormSrc(), ".abc");
container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
delegate_->RunCard(urlPath, params, "", cardId_);
```

### Firing Card Event

```cpp
// Source: card_frontend_delegate.cpp:28-69
void CardFrontendDelegate::FireCardEvent(const EventMarker& eventMarker, const std::string& params)
{
    auto nodeId = StringToInt(eventMarker.GetData().eventId);
    auto action = page_->GetNodeEventAction(nodeId, eventMarker.GetData().eventType);
    context->OnActionEvent(action);
    // Send to accessibility
    context->SendEventToAccessibility(accessibilityEvent);
}
```

### Parsing Card JSON

```cpp
// Source: card_frontend.cpp:163-186
void CardFrontend::ParsePage(const RefPtr<PipelineBase>& context,
    const std::string& pageContent, const std::string& params,
    const RefPtr<Framework::JsAcePage>& page)
{
    auto rootBody = Framework::ParseFileData(pageContent);
    parseJsCard_ = AceType::MakeRefPtr<Framework::JsCardParser>(
        context, assetManager_, std::move(rootBody));
    parseJsCard_->Initialize();
    parseJsCard_->SetColorMode(colorMode_);
    parseJsCard_->CreateDomNode(page, rootTemplate, -1);
}
```

---

## Thread Affinity

| Operation | Thread Type | Description |
|-----------|-------------|-------------|
| `Initialize()` | JS | Card initialization |
| `RunPage()` | JS (posted) | Page loading |
| `LoadPage()` | JS | Page parsing |
| `ParsePage()` | JS | JSON parsing |
| `OnPageLoaded()` | UI (posted) | Command execution |
| `UpdatePageData()` | JS/UI | Data update |
| `FireCardEvent()` | UI (posted) | Event handling |

**Note**: eTSCard (declarative) uses UI thread for operations typically on JS thread.

---

## Card Lifecycle

```
┌─────────────────────────────────────────────────────────┐
│  Card Lifecycle                                         │
│                                                          │
│  1. Initialize                                          │
│     - Create delegate, manifest parser                  │
│     - Set task executor                                 │
│                                                          │
│  2. AttachPipelineContext                               │
│     - Register event handler                            │
│     - Attach pipeline context                           │
│                                                          │
│  3. RunPage                                             │
│     - Parse manifest.json                               │
│     - Determine page path (.json or .abc)               │
│     - Load page content                                 │
│                                                          │
│  4. LoadPage/ParsePage (JSON) or RunCard (Declarative)  │
│     - Create JsCardParser / PageRouterManager           │
│     - Parse and create DOM nodes                        │
│                                                          │
│  5. OnPageLoaded                                        │
│     - Flush JS commands to UI thread                    │
│     - Build and push page                               │
│     - FireFormVisiableCallback                          │
│                                                          │
│  6. UpdateData (optional)                               │
│     - Update card data dynamically                     │
│     - Re-render affected nodes                          │
│                                                          │
│  7. Destroy                                             │
│     - Reset parser, delegate, event handler             │
└─────────────────────────────────────────────────────────┘
```

---

## Resource Management

### Image Resources

```cpp
// Source: js_card_parser.cpp:789-822
void JsCardParser::GetResImageUrl(std::string& value)
{
    // $r('app.media.icon') → actual image path
    auto splitStr = value.substr(4, value.size() - 6);
    auto jsonFile = "resources/res-" + theme + "-" + dpi + ".json";
    LoadResImageUrl(jsonFile, splitStr, imagePath);
}
```

### I18n Resources

```cpp
// Source: js_card_parser.cpp:824-860
bool JsCardParser::GetI18nData(std::string& value)
{
    // $t('strings.title') → localized string
    auto filePath = "i18n/" + fileName + ".json";
    auto result = GetJsonValue(keys, fileData);
}
```

### MediaQuery Support

```cpp
// Source: js_card_parser.cpp:1087-1123
void JsCardParser::LoadMediaQueryStyle()
{
    auto media = styleJson_->GetValue("@MEDIA");
    // Store media query styles by condition
    mediaQueryStyles_[condition] = std::move(mediaQueryStyle);
}
```

---

## Debugging

### Log Tags

| Tag | Usage |
|-----|-------|
| `ACE_FORM` | Card/form related logs |
| `ACE_CARD` | Card specific logs |

### Common Issues

| Issue | Check |
|-------|-------|
| Card not rendering | Check page path, asset loading |
| Data update not working | Verify `UpdatePageData` callback is set |
| Event not firing | Check event registration, nodeId |
| Style not applied | Verify style JSON format, classList |

### Dump Commands

```bash
# View card component info
hidumper -s WindowManagerService -a '-a ComponentTree'
```

---

## Execution Flow Examples

### JSON Card Loading Flow

```
System calls RunPage(url, params)
    ↓
GetFormSrcPath(url, ".json")
    ↓
PostTask to JS thread: LoadPage
    ↓
ParsePage: ParseFileData → Create JsCardParser
    ↓
JsCardParser::Initialize() → LoadImageInfo()
    ↓
JsCardParser::CreateDomNode(page, rootTemplate, -1)
    ↓
page->FlushCommands()
    ↓
OnPageLoaded: Flush commands to UI thread
    ↓
PipelineContext::PushPage(page->BuildPage())
```

### Declarative Card Loading Flow

```
System calls RunPage(url, params)
    ↓
GetFormSrcPath(url, ".abc")
    ↓
Container::SetCardFrontend(this, cardId_)
    ↓
delegate_->RunCard(url, params, "", cardId_)
    ↓
PageRouterManager::RunCard(url, params, cardId)
    ↓
JsEngine::LoadCard(url, cardId, entryPoint)
    ↓
[ArkTS bytecode execution]
```

---

## References

- **Knowledge Base**: [Card_Frontend_Knowledge_Base_CN.md](../../../docs/architecture/Card_Frontend_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **Related**: `frameworks/bridge/declarative_frontend/` - Declarative frontend implementation
- **Related**: `frameworks/bridge/js_frontend/` - JS frontend implementation
- **Related**: `core/common/frontend.h` - Base Frontend class
