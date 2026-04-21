# AGENTS.md

## Basic Information

| Attribute | Value |
| -------- | -------- |
| Repository | ace_engine |
| Subsystem | arkui |
| Component | SecurityComponent Pattern |
| Language | C++ |
| Last Modified | 2026-02-14 |

## Overview

This directory implements the **client-side UI pattern layer** for OpenHarmony Security Components - specialized ArkUI
components (SaveButton, PasteButton) that provide temporary permission access without permanent authorization. When users click two components, apps receive temporary permission to access sensitive data (clipboard, media library).

This is **Layer 1 (Client Application)** in the Security Component architecture, responsible for:
- Component creation and rendering through ArkUI framework
- Component registration with Security Component Manager service (SA ID: 3506)
- Click event reporting to service for authorization validation
- Security validation enforcement (overlay detection, visual integrity checks)

## Build System

This project uses **GN (Generate Ninja)** as part of ACE Engine framework.

### Building

Build commands are run from OpenHarmony root directory:

```bash
# Full build
./build.sh --product-name <product> --build-target ace_engine
```

Common product names: rk3568, ohos-sdk.

### Building Tests

```bash
# Build unit tests
./build.sh --product-name <product> --build-target security_component_test_ng

# Run security component tests
./out/<product>/tests/unittest/ace_engine/Component-Security/security_component_test_ng
```

Test source location: `test/unittest/core/pattern/security_component/`

## Architecture

### Bridge Layer (JS Glue Layer)

The **Declarative Frontend Bridge Layer** (`frameworks/bridge/declarative_frontend/jsview/`) acts as the glue between ArkTS application code and the C++ Pattern layer. It parses JavaScript/ArkTS calls and forwards them to ModelNG classes.

#### Bridge Layer Architecture

```
┌─────────────────────────────────────────────────────────────┐
│ ArkTS Application Layer                                     │
│ SaveButton().onClick((event, error, errMsg) => {...})       │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│ BRIDGE LAYER (frameworks/bridge/declarative_frontend/)      │
│                                                             │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ JS Bindings (js_save_button.cpp, js_paste_button.cpp) │  │
│  │ • JSBind() - Register JS APIs                         │  │
│  │ • ParseComponentStyle() - Parse create parameters     │  │
│  │ • JsOnClick() - Register click callback               │  │
│  └───────────────────────────────────────────────────────┘  │
│                             │                               │
│                             ▼                               │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ JSSecButtonBase (Common Properties)                   │  │
│  │ • SetIconSize, SetIconColor, SetIconBorderRadius      │  │
│  │ • SetFontSize, SetFontStyle, SetFontWeight            │  │
│  │ • SetBackgroundColor, SetBorder*, SetPadding          │  │
│  │ • Etc.                                                │  │
│  └───────────────────────────────────────────────────────┘  │
│                             │                               │
│                             ▼                               │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Click Event Handler (JsSaveButtonClickFunction)       │  │
│  │ • GestureEvent → JS Callback                          │  │
│  │ • Parameters: clickEvent, errorResult, errorMessage   │  │
│  │ • Security component validation integration           │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│ MODEL LAYER (security_component_model_ng.h)                 │
│ SaveButtonModelNG::Create(), PasteButtonModelNG::Create()   │
└─────────────────────────────────────────────────────────────┘
```

#### Property Mapping: ArkTS → C++ → Pattern

| ArkTS API | Bridge Function | ModelNG Function | Pattern Property |
| --------- | --------------- | ----------------- | ----------------- |
| `SaveButton.create({text, icon, buttonType})` | `JSSaveButton::Create()` | `SaveButtonModelNG::Create()` | - |
| `.iconSize(size)` | `JSSecButtonBase::SetIconSize()` | `SecurityComponentModelNG::SetIconSize()` | `LayoutProperty` |
| `.fontSize(size)` | `JSSecButtonBase::SetFontSize()` | `SecurityComponentModelNG::SetFontSize()` | `LayoutProperty` |
| ... (other properties follow the same pattern) | | | |

### Security Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│ LAYER 1: Ace Engine Security Component Pattern (THIS DIR)   │
│                                                             │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Model Layer (ArkTS API)                               │  │
│  │ • SaveButtonModelNG                                   │  │
│  │ • PasteButtonModelNG                                  │  │
│  └───────────────────────────────────────────────────────┘  │
│                           │                                 │
│                           ▼                                 │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Pattern Layer (Business Logic)                        │  │
│  │ • SecurityComponentPattern                            │  │
│  │ • Lifecycle management                                │  │
│  │ • Event handling                                      │  │
│  │ • Registration state machine                          │  │
│  └───────────────────────────────────────────────────────┘  │
│                           │                                 │
│                           ▼                                 │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Property Layer                                        │  │
│  │ • LayoutProperty (padding, font, size)                │  │
│  │ • PaintProperty (colors, borders)                     │  │
│  │ • AccessibilityProperty                               │  │
│  └───────────────────────────────────────────────────────┘  │
│                           │                                 │
│                           ▼                                 │
│  ┌───────────────────────────────────────────────────────┐  │
│  │ Layout Algorithm                                      │  │
│  │ • Adaptive text/icon sizing                           │  │
│  │ • Overflow detection                                  │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
                              │ IPC (Register/Update/Click)
                              ▼
┌─────────────────────────────────────────────────────────────┐
│ LAYER 2: Security Component Manager Service                 │
│ • Component registration and management                     │
│ • Temporary authorization grant                             │
│ • Security validation                                       │
└─────────────────────────────────────────────────────────────┘
```

## Directory Structure

Root: `foundation/arkui/ace_engine/`

```
ace_engine/
├── frameworks/bridge/declarative_frontend/jsview/          # Bridge Layer (JS Bindings)
└── frameworks/core/components_ng/pattern/security_component/  # Pattern Layer
    ├── paste_button/
    └── save_button/
```

## API Reference

### ArkUI APIs (Public Documentation)

- [Public API for PasteButton](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-security-components-savebutton-sys.md)
- [Public API for SaveButton](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-security-components-savebutton.md)
- [System API for SaveButton](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-security-components-savebutton.md)
- [Common public API for SaveButton & PasteButton](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-securitycomponent-attributes.md)
- [Common system API for SaveButton & PasteButton](../../../docs/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-securitycomponent-attributes-sys.md)

## Constraints and Limitations

### Security Validation Requirements

The system performs extensive validation to prevent component abuse. Components will fail registration/click if:

| Check Type | Validations Performed |
| ----------- | -------------------- |
| **Visual Integrity** | Opacity, brightness, blur effects, saturation, contrast, invert, sepia |
| **Overlay Detection** | Component covered by other nodes, z-index comparison |
| **Clip Detection** | Component clipped by parent borders |
| **Border Constraints** | Distance from parent border, border radius checks |
| **Foreground Effects** | Foreground blur, color blend, spherical effects |
| **Text Overlay** | No text nodes overlaying the component |

### Type Discrimination

Component type is identified by `V2::` ETS tag:
- `V2::SAVE_BUTTON_ETS_TAG`
- `V2::PASTE_BUTTON_ETS_TAG`

## Dependencies

### External Dependencies (when SECURITY_COMPONENT_ENABLE)

| Library | Purpose |
| -------- | ------- |
| `security_component_manager:libsecurity_component_sdk` | Service IPC (SA 3506) |
| `ability_runtime:abilitykit_native` | Ability lifecycle |
| `input:libmmi-client` | Input events |
| `window_manager:scene_session` | Window/scene management |
| `napi:ace_napi` | N-API bridge |

### Related Repositories

- `foundation/arkui/ace_engine` - Parent engine repository
- `base/security/security_component_manager` - Security Component Service (Layer 2)
- `applications/standard/permission_manager` - Permission dialog app (Layer 3)

## Common Issues

### Async Thread Requirement for Service IPC

When adding UI client logic that communicates with the Security Component Manager service (SA 3506), **always execute on async threads**. Synchronous IPC calls will block the application's main UI thread, causing frame drops and ANR (Application Not Responding).

**Example**: Component registration, click event reporting, and validation queries should use async callbacks or background tasks.

## When Adding New Security Component

### Pattern Layer Steps (This Directory)

1. Create `new_button/` subdirectory with `*_common.h` (enums)
2. Create `NewButtonModelNG` inheriting `SecurityComponentModelNG`
3. Implement `GetIconResource()` and `GetTextResource()` overrides
4. Add localized strings to `SecurityComponentTheme::Parse*Descriptions()`
5. Register new tag in V2 constants
6. Update `BUILD.gn` sources list
7. Add icon resource file `*_icon_resource.xcstrings`

### Bridge Layer Steps (frameworks/bridge/declarative_frontend/jsview/)

1. Create `js_new_button.h` with class inheriting `JSSecButtonBase`
2. Create `js_new_button.cpp` implementing:
   - `ParseComponentStyle()` - Parse {text, icon, buttonType} parameters
   - `Create()` - Call `NewButtonModelNG::GetInstance()->Create()`
   - `JSBind()` - Register all static methods to ArkTS
3. Add common properties from `JSSecButtonBase` via `StaticMethod()` calls
4. Implement button-specific properties (e.g., `SetIcon()`, `SetText()`)
5. Register click event handler via `JsOnClick()`
6. Update bridge layer `BUILD.gn` to include new files
7. Add d.ts TypeScript declarations in `interfaces/sdk-js/api/arkui/component/`

## History Record

| Version | Date | Content | Author |
| -------- | -------- | -------- | -------- |
| v1.0 | 2026-02-12 | Init CLAUDE.md | harylee |
| v1.1 | 2026-02-14 | Add Bridge Layer (JS Glue) documentation | harylee |
