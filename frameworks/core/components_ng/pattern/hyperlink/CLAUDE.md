# Hyperlink Component - CLAUDE.md

This file provides quick reference for Claude Code when working with the Hyperlink component.

---

## Overview

**Hyperlink** is a clickable text link component for navigation to specified addresses. Inherits from TextPattern, reusing text rendering capabilities.

**Architecture**: NG Pattern → HyperlinkPattern → TextPattern (base)

**Key Features**:
- Clickable link text with URL navigation
- State-based visual feedback (hover, pressed, visited)
- Custom link address and display content
- Keyboard navigation (Enter/Space activation)
- Drag and drop support (Udmf link record)
- Disabled state support

**Component Tag**: `V2::HYPERLINK_ETS_TAG`

**API Version**: 10+

---

## Quick File Reference

| File | Lines | Purpose |
|------|-------|---------|
| `hyperlink_pattern.h/cpp` | ~420 | Pattern layer - event handling, state management, drag support |
| `hyperlink_model_ng.h/cpp` | ~150 | Frontend bridge - Create(), SetColor(), SetDraggable() |
| `hyperlink_layout_property.h` | ~100 | Layout properties (Color, Address) |
| `hyperlink_theme.h` | ~130 | Theme defaults (colors, decorations) |
| `bridge/hyperlink_dynamic_modifier.cpp` | ~200 | ArkTS dynamic modifier implementations |
| `bridge/hyperlink_dynamic_module.h/cpp` | ~80 | Dynamic module exports |

**Path**: `frameworks/core/components_ng/pattern/hyperlink/`

---

## Core Class Hierarchy

```
                    TextPattern
                         ↑
                  HyperlinkPattern
                  (hyperlink_pattern.h)
                         |
         +---------------+---------------+
         |               |               |
  LayoutProperty  EventHub  Accessibility
         ↑               ↑               ↑
HyperlinkLayoutProperty  HyperlinkEventHub  (Text base)
```

---

## Key Properties

### HyperlinkLayoutProperty

| Property | Type | Update Strategy | Default |
|----------|------|-----------------|---------|
| `Color` | Color | PROPERTY_UPDATE_MEASURE | 0xff007dff (blue) |
| `Address` | std::string | PROPERTY_UPDATE_NORMAL | "" |

**Inherited from TextLayoutProperty**:
- Content, TextColor, TextDecoration, FontSize, FontWeight, TextOverflow, etc.

### Theme Default Values

| Property | Value |
|----------|-------|
| `textColor` | 0xff007dff (blue) |
| `textTouchedColor` | 0x19182431 (semi-transparent gray) |
| `textLinkedColor` | 0x66182431 (semi-transparent dark gray) |
| `textFocusedColor` | 0xff007dff (blue) |
| `textSelectedDecoration` | TextDecoration::UNDERLINE |
| `textUnSelectedDecoration` | TextDecoration::NONE |

---

## Common Operations

### Setting Hyperlink Content

```cpp
// Create hyperlink with address and content
HyperlinkModelNG::Create("https://example.com", "Click here");

// Static creation
auto frameNode = HyperlinkModelNG::CreateFrameNode("https://example.com", "Content");
```

### Setting Hyperlink Style

```cpp
// Set color
layoutProperty->UpdateColor(Color::RED);

// Model layer
HyperlinkModelNG::SetColor(frameNode, Color::BLUE);
```

### Setting Drag Support

```cpp
// Enable drag
HyperlinkModelNG::SetDraggable(true);

// Static
HyperlinkModelNG::SetDraggable(frameNode, true);
```

### Response Region

```cpp
// Set custom response region
std::vector<DimensionRect> regions = { /* ... */ };
HyperlinkModelNG::SetResponseRegion(frameNode, regions, true);
```

---

## Important Implementation Details

### 1. State Color Handling

**Source**: `hyperlink_pattern.cpp:169-195`

```cpp
// Unvisited: color, no underline
color = theme->GetTextColor();  // 0xff007dff
textDecoration = NONE;

// Hover: color, with underline
color = theme->GetTextColor();
textDecoration = UNDERLINE;

// Pressed: blended color, underline
color = theme->GetTextColor().BlendColor(theme->GetTextTouchedColor());
textDecoration = UNDERLINE;

// Visited: blended color, underline
color = theme->GetTextColor().BlendColor(theme->GetTextLinkedColor());
textDecoration = UNDERLINE;
```

### 2. Disabled State Handling

**Source**: `hyperlink_pattern.cpp:147-167`

```cpp
auto enabled = hub->IsEnabled();
if (!enabled) {
    auto disabledColor = hyperlinkLayoutProperty->GetColor()
        .value_or(theme->GetTextColor())
        .BlendOpacity(theme->GetOpacity());  // opacity = 0.0
    hyperlinkLayoutProperty->UpdateTextColor(disabledColor);
}
```

### 3. Link Navigation

**Source**: `hyperlink_pattern.cpp:193`

```cpp
void HyperlinkPattern::LinkToAddress()
{
    isLinked_ = true;  // Mark as visited
    // Update visited style
    auto linkedColor = hyperlinkLayoutProperty->GetColor()
        .value_or(color).BlendColor(theme->GetTextLinkedColor());
    hyperlinkLayoutProperty->UpdateTextColor(linkedColor);
    hyperlinkLayoutProperty->UpdateTextDecoration(UNDERLINE);

    auto address = hyperlinkLayoutProperty->GetAddress().value_or("");
    pipeline->HyperlinkStartAbility(address);  // System call
}
```

### 4. Prevent Default Behavior

**Source**: `hyperlink_pattern.cpp:285-295`

```cpp
auto clickAfterCallback = [weak = WeakClaim(this)](GestureEvent& info) {
    auto hyperlinkPattern = weak.Upgrade();
    if (!info.IsPreventDefault() && !hyperlinkPattern->isTouchPreventDefault_) {
        hyperlinkPattern->LinkToAddress();  // Only navigate if not prevented
    }
    hyperlinkPattern->isTouchPreventDefault_ = false;
};
```

### 5. Keyboard Navigation

**Source**: `hyperlink_pattern.cpp:307-317`

```cpp
bool HyperlinkPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER) {
        LinkToAddress();
        return true;  // Consume event
    }
    return false;
}
```

### 6. Mouse Style Management

**Source**: `hyperlink_pattern.cpp:319-348`

```cpp
void HyperlinkPattern::OnHoverEvent(bool isHovered)
{
    if (isHovered) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_POINTING);
        UpdateTextDecoration(UNDERLINE);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
        UpdateTextDecoration(NONE);
    }
}
```

### 7. Drag Data Format

**Source**: `hyperlink_pattern.cpp:90-122`

```cpp
auto dragStart = [](const RefPtr<DragEvent>& event, ...) -> DragDropInfo {
    DragDropInfo info;
    // Create JSON extraInfo
    auto json = JsonUtil::Create(true);
    json->Put("url", address.c_str());
    json->Put("title", content.c_str());
    info.extraInfo = json->ToString();

    // Create UnifiedData with link record
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, content);
    event->SetData(unifiedData);
    return info;
};
```

---

## ArkTS API Reference

```typescript
// Constructor
Hyperlink(address: string | Resource, content?: string | Resource)

// Property methods
.color(value: ResourceColor)
.draggable(value: boolean)

// Inherited from Text
.fontSize(value: number | Resource)
.fontWeight(value: number | FontWeight)
.fontFamily(value: string | Resource)
.textDecoration(value: { type: TextDecorationType })

// Common methods
.enabled(value: boolean)
.onClick(callback: () => void)
.onHover(callback: (isHover: boolean) => void)
```

---

## Debugging

### Log Tag

```cpp
TAG_LOGD(AceLogTag::ACE_HYPERLINK, "Address: %{public}s", address.c_str());
```

### Dump Commands

```bash
# View component info
hidumper -s WindowManagerService -a '-a Hyperlink'

# View component tree
hidumper -s WindowManagerService -a '-a ComponentTree'
```

### Common Issues

| Issue | Check |
|-------|-------|
| Link not navigating | Check `IsPreventDefault()` and `isTouchPreventDefault_` |
| Style not updating | Verify property update strategy (MEASURE vs NORMAL) |
| Hover not working | Check `InitInputEvent()` is called in `OnModifyDone()` |
| Drag not working | Verify `SetDraggable(true)` is called |

---

## Execution Flow

```
Frontend: Hyperlink('https://example.com', 'Click here')
    ↓
HyperlinkModelNG::Create(address, content)
    ├── FrameNode::GetOrCreateFrameNode(V2::HYPERLINK_ETS_TAG)
    ├── Create HyperlinkPattern
    ├── Create HyperlinkLayoutProperty
    ├── UpdateContent(content)
    ├── UpdateAddress(address)
    └── UpdateTextColor(theme->GetTextColor())
    ↓
HyperlinkPattern::OnModifyDone()
    ├── InitClickEvent() - Add click listener
    ├── InitTouchEvent() - Add touch listener
    ├── InitInputEvent() - Add mouse hover listener
    └── InitOnKeyEvent() - Add keyboard listener
    ↓
User Interaction
    ├── Click → LinkToAddress() → Update style + HyperlinkStartAbility()
    ├── Hover → OnHoverEvent(true) → UNDERLINE + HAND_POINTING cursor
    ├── Press → OnTouchEvent(DOWN) → textTouchedColor + UNDERLINE
    ├── Release → OnTouchEvent(UP) → default color + NO underline
    └── Drag → Create Udmf link record
    ↓
Measure/Layout (inherited from TextPattern)
    ↓
Paint (inherited from TextPattern)
```

---

## References

- **Theme**: `frameworks/core/components/hyperlink/hyperlink_theme.h`
- **Related**: Text component (Hyperlink inherits from TextPattern)
- **Bridge**: `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/component/hyperlink.ets`
