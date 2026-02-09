# Search Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the Search component.

> **Deep Dive Knowledge Base**: For detailed implementation analysis, design decisions, and troubleshooting, see [Search_Knowledge_Base_CN.md](../../../docs/pattern/search/Search_Knowledge_Base_CN.md)

---

## Overview

**Search** is a specialized search input box component that inherits from TextField. It includes search icon, text input field, cancel button, search button, and divider.

**Architecture**: NG Pattern → SearchPattern → SearchLayoutAlgorithm (BoxLayoutAlgorithm)

**Key Features**:
- Multiple child elements (TextField, SearchIcon, CancelIcon, CancelButton, SearchButton, Divider)
- Symbol and Image icon support
- Multiple cancel button styles (INPUT, CONSTANT, HIDDEN, INSET)
- Complete event support (onSubmit, onChange, onCopy, onCut, onPaste)
- Focus management between input field and buttons
- Theme configuration updates
- Hover and touch animations

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `search_pattern.h/cpp` | ~400 (h) | Pattern layer - business logic, OnModifyDone, theme updates, child node management |
| `search_model_ng.h/cpp` | ~300 (cpp) | Frontend bridge - Create(), CreateSearchNode() |
| `search_layout_property.h` | ~120 | All Search properties (SearchButton, CancelButtonStyle, etc.) |
| `search_event_hub.h` | ~50 | Event handling (onSubmit, onChange, onCopy, etc.) |
| `search_node.h/cpp` | ~100 | SearchNode special FrameNode |
| `search_text_field.h/cpp` | ~200 | Search-specific TextField behavior |

**Path**: `frameworks/core/components_ng/pattern/search/`

---

## Core Class Hierarchy

```
                    Pattern
                       ↑
                SearchPattern
                (search_pattern.h:37)
                       |
        +--------------+--------------+
        |              |              |
  LayoutProperty  LayoutAlgorithm  AccessibilityProperty
        ↑              ↑                    ↑
SearchLayoutProperty  SearchLayoutAlgorithm  SearchAccessibilityProperty
```

---

## Child Node Indices

**Source**: `search_model_ng.cpp:43-48`

```cpp
constexpr int32_t TEXTFIELD_INDEX = 0;        // Text input field
constexpr int32_t IMAGE_INDEX = 1;             // Search icon
constexpr int32_t CANCEL_IMAGE_INDEX = 2;      // Cancel icon
constexpr int32_t CANCEL_BUTTON_INDEX = 3;     // Cancel button
constexpr int32_t BUTTON_INDEX = 4;            // Search button
constexpr int32_t DIVIDER_INDEX = 5;           // Divider
```

---

## Key Properties

### Content Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `SearchButton` | string | empty | Search button text (button hidden if empty) |
| `CancelButtonStyle` | CancelButtonStyle | INPUT | Cancel button display style |

### Style Properties

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `SearchIconUDSize` | Dimension | - | Search icon user-defined size |
| `SearchIconColor` | Color | Gray | Search icon color |
| `CancelButtonUDSize` | Dimension | - | Cancel button user-defined size |
| `CancelButtonColor` | Color | Gray | Cancel button color |
| `SearchButtonFontSize` | Dimension | - | Search button font size |
| `DividerColor` | Color | Transparent | Divider color |
| `BackgroundColor` | Color | White | Background color |
| `StrokeWidth` | Dimension | - | Border width |
| `StrokeColor` | Color | - | Border color |

**User Set Flags**: `SearchIconColorSetByUser`, `CancelIconColorSetByUser`, `DividerColorSetByUser` - prevent theme updates from overriding user values

---

## CancelButtonStyle Enum

```cpp
enum class CancelButtonStyle {
    INPUT,      // Show on input (default) - enabled when text field has content
    CONSTANT,   // Always show - always enabled
    HIDDEN,     // Hidden - always disabled
    INSET       // Inset style - enabled when text field has content
};
```

---

## Common Operations

### Setting Search Button

```cpp
// Show search button with text
layoutProperty->UpdateSearchButton("Search");

// Hide search button
layoutProperty->UpdateSearchButton("");
```

### Setting Cancel Button Style

```cpp
// Show cancel button when typing (default)
layoutProperty->UpdateCancelButtonStyle(CancelButtonStyle::INPUT);

// Always show cancel button
layoutProperty->UpdateCancelButtonStyle(CancelButtonStyle::CONSTANT);

// Hide cancel button
layoutProperty->UpdateCancelButtonStyle(CancelButtonStyle::HIDDEN);
```

### Setting Icon Style

```cpp
// Search icon
pattern->SetSearchIconSize(Dimension(20, DimensionUnit::VP));
pattern->SetSearchIconColor(Color::BLUE);
pattern->SetSearchSrcPath("$r('app.media.search')", "", "");

// Cancel icon
pattern->SetCancelIconSize(Dimension(20, DimensionUnit::VP));
pattern->SetCancelIconColor(Color::GRAY);
```

### Updating Cancel Button Status

**Source**: `search_pattern.cpp`

```cpp
void SearchPattern::UpdateCancelButtonStatus(const std::u16string& textValue, int16_t style)
{
    bool isEventEnabled = IsEventEnabled(textValue, style);
    if (isEventEnabled) {
        // Enabled state: visible, interactive, opaque
        cancelButtonRenderContext->UpdateOpacity(1.0);
        cancelButtonEvent->SetEnabled(true);
        buttonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        // Disabled state: invisible, non-interactive, transparent
        cancelButtonRenderContext->UpdateOpacity(0.0);
        cancelButtonEvent->SetEnabled(false);
        buttonLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    }
}
```

### Creating Search Programmatically

```cpp
// In Model layer
auto searchNode = SearchModelNG::CreateSearchNode(nodeId, value, placeholder, icon);

auto pattern = searchNode->GetPattern<SearchPattern>();
pattern->SetSearchNode(searchNode);

// Set search button
auto buttonFrameNode = AceType::DynamicCast<FrameNode>(searchNode->GetChildAtIndex(BUTTON_INDEX));
auto layoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
layoutProperty->UpdateSearchButton("Search");
```

---

## Important Implementation Details

### 1. Search Uses Multiple Child Nodes

**Source**: `search_model_ng.cpp:138-188`

Search creates multiple child nodes for different elements:

```cpp
// Create TextField (INDEX 0) - Text input field
CreateTextField(frameNode, placeholder, value, hasTextFieldNode, searchTheme);

// Create SearchIcon (INDEX 1)
pattern->CreateSearchIcon(src);

// Create CancelIcon (INDEX 2)
pattern->CreateCancelIcon();

// Create CancelButton (INDEX 3)
CreateCancelButton(frameNode, hasCancelButtonNode, searchTheme);

// Create SearchButton (INDEX 4)
CreateButton(frameNode, hasButtonNode, searchTheme);

// Create Divider (INDEX 5)
CreateDivider(frameNode, hasDividerNode);
```

**Why**: Separation of concerns - each element has its own lifecycle, events, and styling

### 2. SearchNode is a Special FrameNode

**Source**: `search_node.h`

SearchNode extends FrameNode to provide:
- Child node management (TextField, icons, buttons, divider)
- Specialized layout behavior
- Search-specific properties

```cpp
class SearchNode : public FrameNode {
    // HasTextFieldNode(), HasButtonNode(), HasCancelButtonNode(), HasDividerNode()
};
```

### 3. Icon Type Support (Symbol and Image)

**Source**: `search_pattern.h:303-320`

```cpp
bool IsSymbolIcon(int32_t index);
void CreateOrUpdateSymbol(int32_t index, bool isCreateNode);
void CreateOrUpdateImage(int32_t index, bool isCreateNode);
```

Search supports both Symbol icons (vector-based, themeable) and Image icons (raster images).

### 4. Focus Management

**Source**: `search_pattern.h:96`

```cpp
enum class FocusChoice { SEARCH = 0, CANCEL_BUTTON, SEARCH_BUTTON };
```

Search supports focus switching between input field and buttons using keyboard navigation or programmatic control.

### 5. Animation Constants

**Source**: `search_pattern.cpp` (namespace constants)

```cpp
constexpr float HOVER_OPACITY = 0.05f;      // Hover effect opacity
constexpr float TOUCH_OPACITY = 0.1f;        // Touch effect opacity
constexpr int32_t HOVER_DURATION = 250;      // Hover animation duration (ms)
constexpr int32_t TOUCH_DURATION = 250;      // Touch animation duration (ms)
```

### 6. Theme Update Behavior

**Source**: `search_pattern.h:166-169`

When theme changes, **only user-unset properties** are updated:

```cpp
void OnColorConfigurationUpdate();
void OnIconColorConfigrationUpdate(const RefPtr<SearchTheme>& searchTheme);
void OnSearchColorConfigrationUpdate(const RefPtr<FrameNode>& frameNode, const Color& color);
void OnCancelColorConfigrationUpdate(const RefPtr<FrameNode>& frameNode, const Color& color);
```

---

## Event System

### SearchEventHub Events

**Source**: `search_event_hub.h`

| Event | Type | Description |
|-------|------|-------------|
| `onSubmit` | std::function<void(const std::string&)> | Submit event (search button or Enter key) |
| `onChange` | std::function<void(const ChangeValueInfo&)> | Content change event |
| `onCopy` | std::function<void(const std::u16string&)> | Copy event |
| `onCut` | std::function<void(const std::u16string&)> | Cut event |
| `onPaste` | std::function<void(const std::u16string&)> | Paste event |
| `onEditChanged` | std::function<void(bool)> | Edit state change |

### Event Initialization

**Source**: `search_pattern.cpp` - `InitAllEvent()`

```cpp
void SearchPattern::InitAllEvent() {
    InitSearchController();
    InitTextFieldValueChangeEvent();
    InitTextFieldDragEvent();
    InitButtonMouseAndTouchEvent();
    InitClickEvent();
    InitFocusEvent(const_cast<RefPtr<FocusHub>&>(focusHub));
    InitHoverEvent();
    InitTouchEvent();
}
```

---

## ArkTS API Reference

```typescript
// Constructor
Search(options: { value?: string, placeholder?: string, icon?: string | Symbol, controller?: SearchController })

// Property methods
.searchButton(value: string)                   // Search button text
.searchIcon(value: string | Symbol)            // Search icon
.searchIconSize(value: number | Resource)      // Search icon size
.searchIconColor(value: ResourceColor)         // Search icon color
.cancelButton(value: Symbol)                   // Cancel button icon
.cancelButtonStyle(value: CancelButtonStyle)   // Cancel button style
.textFont(value: Font)                         // Text font
.placeholderFont(value: Font)                  // Placeholder font
.placeholderColor(value: ResourceColor)        // Placeholder color
.textAlign(value: TextAlign)                   // Text alignment
.caretColor(value: ResourceColor)              // Caret color
.caretWidth(value: number | Dimension)         // Caret width
.selectedBackgroundColor(value: ResourceColor) // Selected background color
// Inherits all TextField properties

// Events
.onSubmit(callback: (value: string) => void)    // Submit event
.onChange(callback: (value: string) => void)    // Content change event
.onCopy(callback: (value: string) => void)      // Copy event
.onCut(callback: (value: string) => void)       // Cut event
.onPaste(callback: (value: string) => void)     // Paste event
// Inherits all TextField events

// CancelButtonStyle enum
enum CancelButtonStyle {
    INPUT,      // Show on input (default)
    CONSTANT,   // Always show
    HIDDEN,     // Hidden
    INSET       // Inset
}
```

---

## Debugging

### Dump Commands

```bash
# View Search component info
hidumper -s WindowManagerService -a '-a Search'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'
```

### Log Tag

Search component uses common log tags. Use `ACE_SEARCH` if available or component-specific tags.

### Common Issues

| Issue | Check |
|-------|-------|
| Button not showing | Check `searchButton` text is non-empty |
| Cancel button not showing | Check `cancelButtonStyle` and text field content |
| Icon not showing | Check icon path, size > 0, color not transparent |
| Events not triggering | Check event callbacks are registered, component is enabled |
| Styles not applied | Check `*SetByUser` flags - user values override theme |

---

## Execution Flow

```
Frontend: Search({ value: 'hello', placeholder: 'Search...' })
    ↓
SearchModelNG::Create()
    ├── CreateSearchNode()
    │   ├── CreateTextField() - Text input field (INDEX 0)
    │   ├── CreateSearchIcon() - Search icon (INDEX 1)
    │   ├── CreateCancelIcon() - Cancel icon (INDEX 2)
    │   ├── CreateCancelButton() - Cancel button (INDEX 3)
    │   ├── CreateButton() - Search button (INDEX 4)
    │   ├── CreateDivider() - Divider (INDEX 5)
    │   └── UpdateSearchNodeBorderProps()
    └── Return searchController_
    ↓
SearchPattern::OnModifyDone()
    ├── InitSearchController()
    ├── InitAllEvent()
    ├── UpdateCancelButtonStatus()
    └── Apply theme styles
    ↓
SearchLayoutAlgorithm::Measure() / Layout()
    ├── Uses BoxLayoutAlgorithm (base class)
    └── Measure/layout child nodes
    ↓
Render Display
```

---

## References

- **Knowledge Base**: [Search_Knowledge_Base_CN.md](../../../docs/pattern/search/Search_Knowledge_Base_CN.md) - Design decisions, implementation deep dive, troubleshooting
- **Theme**: `frameworks/core/components/search/search_theme.h`
- **Related**: TextField component (Search inherits from TextField), Button, Image, Divider
