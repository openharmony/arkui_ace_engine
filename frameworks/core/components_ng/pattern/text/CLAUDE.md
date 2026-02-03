# Text Component - CLAUDE.md

This file provides guidance for Claude Code when working with the Text component in ArkUI ACE Engine.

## Component Overview

The Text component (`TextPattern`) is responsible for rendering text content with rich styling support, including:
- Plain text and styled text (Span) rendering
- Text selection and copy functionality
- AI entity recognition (phone numbers, URLs, emails, etc.)
- Drag and drop support
- Accessibility support

## Architecture

### Class Hierarchy

```
TextPattern
├── Pattern (base class)
├── TextDragBase (drag & drop functionality)
├── TextBase (selection & gesture handling)
├── TextGestureSelector (gesture selection)
└── Magnifier (magnifier functionality)
```

### Core Components

| Component | File | Purpose |
|-----------|------|---------|
| **TextPattern** | `text_pattern.h/cpp` | Main pattern class for Text component |
| **TextLayoutProperty** | `text_layout_property.h/cpp` | Layout properties for Text |
| **TextModel** | `text_model.h` | Model interface for Text |
| **TextStyles** | `text_styles.h/cpp` | Style structures and utilities |
| **SpanNode** | `span_node.h/cpp` | Span item node for styled text |
| **TextLayoutAlgorithm** | `text_layout_algorithm.h/cpp` | Layout algorithm for text |
| **TextSelectOverlay** | `text_select_overlay.h/cpp` | Selection handle logic |
| **TextContentModifier** | `text_content_modifier.h/cpp` | Content modifier for rendering |
| **TextEventHub** | `text_event_hub.h` | Event handling |

## Directory Structure

```
text/
├── text_pattern.h/cpp              # Main pattern implementation
├── text_model.h/cpp                # Model interface and implementations
├── text_layout_property.h/cpp      # Layout properties
├── text_styles.h/cpp               # Style definitions
├── text_base.h/cpp                 # Base class for text components
├── text_event_hub.h                # Event hub
├── text_layout_algorithm.h/cpp     # Layout algorithm
├── text_select_overlay.h/cpp       # Selection handle logic
├── text_content_modifier.h/cpp     # Content modifier
├── text_controller.h/cpp           # Text controller
├── span/                           # Span-related files
│   ├── span_string.h/cpp           # StyleString implementation
│   ├── span_object.h/cpp           # StyleString processing logic
│   ├── mutable_span_string.h/cpp   # Mutable StyleString implementation
│   └── tlv_util.h/cpp              # TLV encoding/decoding
├── span_node.h/cpp                 # Span node implementation
├── text_layout_adapter/            # Layout adapter
└── base_text_select_overlay.h/cpp  # Base selection overlay
```

## Key Data Structures

### FontStyle
Controls text appearance:
- `FontSize`: Text size (Dimension)
- `TextColor`: Text color (Color)
- `FontWeight`: Font weight (FontWeight)
- `ItalicFontStyle`: Italic style (FontStyle)
- `FontFamily`: Font family list
- `TextDecoration`: Text decorations (underline, line-through, etc.)
- `TextDecorationColor`: Decoration color
- `TextShadow`: Text shadow effects
- `LetterSpacing`: Letter spacing
- `TextCase`: Text transformation

### TextLineStyle
Controls text layout:
- `LineHeight`: Line height
- `LineSpacing`: Line spacing
- `TextAlign`: Text alignment
- `TextOverflow`: Overflow behavior (NONE, CLIP, ELLIPSIS, MARQUEE)
- `MaxLines`: Maximum number of lines
- `WordBreak`: Word break behavior
- `LineBreakStrategy`: Line break strategy
- `TextIndent`: First line indentation

### SpanItem
Represents a styled text segment:
- `content`: Text content
- `fontStyle`: Font styling
- `textLineStyle`: Line styling
- `onClick`: Click event handler
- `onLongPress`: Long press event handler
- `onHover`: Hover event handler
- `spanItemType`: Type (NORMAL, IMAGE, SYMBOL, CustomSpan, PLACEHOLDER)
- `backgroundStyle`: Background style
- `urlAddress`: URL for link spans

## AI Entity Recognition

TextPattern supports intelligent entity recognition for:
- Phone numbers
- URLs
- Email addresses
- Locations
- Date/time

Key classes:
- `DataDetectorAdapter`: Manages entity recognition
- `AISpan`: Represents a recognized entity
- `TextDetectConfig`: Configuration for recognition

### Entity Recognition Types

```cpp
enum TextDataDetectType {
    PHONE_NUMBER,
    URL,
    EMAIL,
    ADDRESS,
    DATE_TIME
};
```

## Text Selection

TextPattern supports text selection with:
- Mouse drag selection
- Touch gesture selection
- Keyboard selection (Shift + Arrow keys)
- Handle-based selection

Key methods:
- `InitSelection()`: Initialize selection
- `UpdateSelection()`: Update selection range
- `CalculateHandleOffsetAndShowOverlay()`: Show selection handles
- `ResetSelection()`: Clear selection

## Text Drag & Drop

TextPattern supports dragging:
- Plain text
- Styled spans
- Images
- AI-recognized entities

Key methods:
- `OnDragStart()`: Handle drag start
- `OnDragMove()`: Handle drag move
- `OnDragEnd()`: Handle drag end
- `AddUdmfData()`: Add UDMF data

## Span System

### Overview

**Span** and **StyledString** are the core mechanisms for displaying rich, styled text content in ArkUI. They allow different text segments to have different styles within a single Text component.

**Key Terminology Mapping**:
| ArkTS API | Internal C++ | Description |
|-----------|--------------|-------------|
| `Span()` | `SpanNode` | Span text segment component |
| `StyledString` / `spanString` | `SpanString` | Styled string container |
| `span_object` | `SpanObject` hierarchy | Span style objects (FontSpan, etc.) |

### Span Types

**SpanItemType** (text_styles.h) - For SpanItem:
| Type | Description |
|------|-------------|
| `SpanItemType::NORMAL` | Normal text span |
| `SpanItemType::IMAGE` | Image span |
| `SpanItemType::SYMBOL` | Symbol span |
| `SpanItemType::CustomSpan` | Custom drawable span |
| `SpanItemType::PLACEHOLDER` | Placeholder span |

**SpanType** (span_object.h:35-50) - For style spans:
| Type | Value | Span Class | Description |
|------|-------|------------|-------------|
| `Font` | 0 | `FontSpan` | Font style (size, color, weight, family) |
| `Decoration` | 1 | `DecorationSpan` | Text decoration (underline, line-through, etc.) |
| `BaselineOffset` | 2 | `BaselineOffsetSpan` | Baseline offset |
| `LetterSpacing` | 3 | `LetterSpacingSpan` | Letter spacing |
| `TextShadow` | 4 | `TextShadowSpan` | Text shadow |
| `LineHeight` | 5 | `LineHeightSpan` | Line height |
| `BackgroundColor` | 6 | `BackgroundColorSpan` | Background color |
| `Url` | 7 | `UrlSpan` | URL link |
| `Gesture` | 100 | `GestureSpan` | Click/long-press events |
| `ParagraphStyle` | 200 | `ParagraphStyleSpan` | Paragraph-level styles |
| `Image` | 300 | `ImageSpan` | Image span |
| `CustomSpan` | 400 | `CustomSpan` | Custom drawable |
| `ExtSpan` | 500 | `ExtSpan` | Extended span |

### SpanItem Structure

**Location**: `text_styles.h`

```cpp
struct SpanItem {
    std::string content;                   // Text content
    TextStyle fontStyle;                   // Font styling
    TextLineStyle textLineStyle;           // Line styling
    SpanItemType spanItemType;             // Type (NORMAL, IMAGE, SYMBOL, etc.)
    std::function<void()> onClick;         // Click event
    std::function<void()> onLongPress;     // Long press event
    std::function<void(bool)> onHover;     // Hover event
    BackgroundStyle backgroundStyle;       // Background style
    std::string urlAddress;                // Link URL
};
```

### SpanString (StyledString)

**Location**: `span/span_string.h:35-143`

**Core Structure**:
```cpp
class SpanString : public SpanStringBase {
    std::u16string text_;                              // Plain text content
    std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> spansMap_;  // Style spans
    std::list<RefPtr<NG::SpanItem>> spans_;           // Span items list
    WeakPtr<NG::FrameNode> frameNode_;                 // Associated FrameNode
    int32_t groupId_;                                  // Group ID for backgrounds
};
```

**Key Methods**:
| Method | Description |
|--------|-------------|
| `Create()` | Create SpanString from text |
| `AddSpan()` | Add style span to range [start, end) |
| `GetSpans()` | Get spans in range [start, end) |
| `GetSubSpanString()` | Extract substring with styles |
| `EncodeTlv()` / `DecodeTlv()` | TLV serialization |

### SpanObject Hierarchy

**Base Class** - `SpanBase` (span_object.h:104-126):
```cpp
class SpanBase {
    int32_t start_;  // Start index (inclusive)
    int32_t end_;    // End index (exclusive)
    virtual void ApplyToSpanItem(SpanItem*, SpanOperation) = 0;
};
```

**Concrete Span Classes**:

| Class | Properties | Source |
|-------|------------|--------|
| `FontSpan` | Font (size, weight, color, family) | span_object.h:128 |
| `DecorationSpan` | types, color, style, lineThicknessScale | span_object.h:151 |
| `BaselineOffsetSpan` | baselineOffset (Dimension) | span_object.h:202 |
| `LetterSpacingSpan` | letterSpacing (Dimension) | span_object.h:222 |
| `TextShadowSpan` | textShadow (vector\<Shadow\>) | span_object.h:276 |
| `LineHeightSpan` | lineHeight (Dimension) | span_object.h:390 |
| `BackgroundColorSpan` | textBackgroundStyle | span_object.h:296 |
| `UrlSpan` | urlAddress (string) | span_object.h:445 |
| `GestureSpan` | onClick, onLongPress, onTouch | span_object.h:243 |
| `ParagraphStyleSpan` | align, maxLines, wordBreak | span_object.h:364 |
| `ImageSpan` | imageOptions (ImageSpanOptions) | span_object.h:317 |
| `CustomSpan` | onMeasure, onDraw callbacks | span_object.h:336 |

### Span Node Classes

| Class | File | Purpose |
|-------|------|---------|
| `SpanNode` | `span_node.h` | Base span node (UINode) |
| `ImageSpanNode` | `span_node.h` | Image span node |
| `PlaceholderSpanNode` | `span_node.h` | Placeholder span node |
| `CustomSpanNode` | `span_node.h` | Custom span node |
| `ContainerSpanNode` | `span_node.h` | Container for nested spans |

### Span System - Source Implementation Patterns

**Converting SpanItems to FontSpan** (source: `span_string.cpp:ToFontSpan`):
```cpp
RefPtr<FontSpan> SpanString::ToFontSpan(const RefPtr<NG::SpanItem>& spanItem, int32_t start, int32_t end)
{
    Font font;
    if (spanItem->fontStyle.fontSize.has_value()) {
        font.fontSize = spanItem->fontStyle.fontSize.value();
    }
    if (spanItem->fontStyle.fontWeight.has_value()) {
        font.fontWeight = spanItem->fontStyle.fontWeight.value();
    }
    if (spanItem->fontStyle.textColor.has_value()) {
        font.textColor = spanItem->fontStyle.textColor.value();
    }
    font.fontFamilies = spanItem->fontStyle.fontFamilies;
    return MakeRefPtr<FontSpan>(font, start, end);
}
```

**Applying Span to SpanItem** (source: `span_object.cpp:FontSpan::ApplyToSpanItem`):
```cpp
void FontSpan::AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const
{
    if (font_.fontSize.has_value()) {
        spanItem->fontStyle.fontSize = font_.fontSize;
    }
    if (font_.fontWeight.has_value()) {
        spanItem->fontStyle.fontWeight = font_.fontWeight;
    }
    if (font_.textColor.has_value()) {
        spanItem->fontStyle.textColor = font_.textColor;
    }
    if (!font_.fontFamilies.empty()) {
        spanItem->fontStyle.fontFamilies = font_.fontFamilies;
    }
}
```

**Gathering Spans by Type** (source: `span_string.cpp:GetSpans`):
```cpp
std::vector<RefPtr<SpanBase>> SpanString::GetSpans(int32_t start, int32_t length, SpanType spanType) const
{
    std::vector<RefPtr<SpanBase>> result;
    auto it = spansMap_.find(spanType);
    if (it != spansMap_.end()) {
        for (const auto& span : it->second) {
            if (span->GetStartIndex() >= start && span->GetEndIndex() <= start + length) {
                result.push_back(span);
            }
        }
    }
    return result;
}
```

**Adding ImageSpan programmatically** (source: pattern usage):
```cpp
// When processing ImageSpanItem from frontend
RefPtr<ImageSpanItem> imageSpanItem = ...;
ImageSpanOptions options;
options.offset = imageSpanItem->GetOffset();
options.image = imageSpanItem->GetImagePath();
options.imageAttribute = imageSpanItem->GetImageAttribute();

auto imageSpan = MakeRefPtr<ImageSpan>(options);
spanString->AddSpan(imageSpan, true, false);  // processMultiDecoration, isFromHtml
```

**See Also**: For ArkTS usage examples, see [Text_Knowledge_Base_CN.md](../../../docs/pattern/text/Text_Knowledge_Base_CN.md#span系统)

## Common Operations

### Setting Text Content

```cpp
// Plain text
textLayoutProperty->UpdateContent("Hello World");

// Styled text (SpanString)
RefPtr<SpanString> spanString = ...;
textPattern->SetStyledString(spanString);
```

### Setting Text Style

```cpp
// Font size
textLayoutProperty->UpdateFontSize(Dimension(16));

// Text color
textLayoutProperty->UpdateTextColor(Color::RED);

// Font weight
textLayoutProperty->UpdateFontWeight(FontWeight::W500);

// Text decoration
textLayoutProperty->UpdateTextDecoration({TextDecoration::UNDERLINE});
```

### Setting Text Selection

```cpp
// Enable selection
textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE);

// Set selection range
textPattern->SetTextSelection(startIndex, endIndex);
```

### Setting AI Entity Recognition

```cpp
TextDetectConfig config;
config.types = "phoneNum,url,email";
config.entityColor = Color::BLUE;
config.entityDecorationType = TextDecoration::UNDERLINE;

textPattern->SetTextDetectConfig(config);
```

## Event Handling

### Click Events

```cpp
textPattern->SetOnClickEvent([](GestureEvent& info) {
    // Handle click
});
```

### Copy Event

```cpp
auto eventHub = GetEventHub<TextEventHub>();
eventHub->SetOnCopy([](const std::u16string& content) {
    // Handle copy
});
```

### Selection Change Event

```cpp
eventHub->SetOnSelectionChange([](int32_t start, int32_t end) {
    // Handle selection change
});
```

## Text Overflow Modes

| Mode | Description |
|------|-------------|
| `NONE` | No overflow handling |
| `CLIP` | Clip overflow text |
| `ELLIPSIS` | Show ellipsis for overflow |
| `MARQUEE` | Scrolling marquee animation |

## Marquee Animation

TextPattern supports marquee animation for scrolling text. Configure with `TextMarqueeOptions`:

```cpp
TextMarqueeOptions options;
options.textMarqueeStart = true;
options.textMarqueeStep = 100.0;
options.textMarqueeLoop = -1;  // Infinite loop
options.textMarqueeDirection = MarqueeDirection::LEFT;
```

## Accessibility

TextPattern provides accessibility support through:
- `TextAccessibilityProperty`: Accessibility properties
- Content change announcements
- Selection announcements
- Screen reader support

## Theme Integration

TextPattern supports theme-based styling:
- Use theme colors by default
- Apply theme font sizes
- Respect theme decorations
- Handle theme changes dynamically

## Important Notes

1. **Paragraph Management**: TextPattern uses `ParagraphManager` to manage text paragraphs. When text or style changes, it may trigger relayout or rebuild depending on the change type.

2. **Selection Handles**: Selection handles are managed by `TextSelectOverlay`. Handle visibility and positioning are calculated based on text metrics.

3. **Span Resource Management**: Spans support resource objects for dynamic color changes. Use `AddResource()` to register resources.

4. **AI Entity Recognition**: Entity recognition is async and may trigger re-layout when results are available.

5. **Performance**: For large text content, consider using `minFontScale` and `maxFontScale` to limit font scaling.

## Related Components

- `RichEditorPattern`: Rich text editor (extends TextPattern)
- `TextFieldPattern`: Text input field
- `SearchPattern`: Search input field

## References

- **Knowledge Base**: [Text_Knowledge_Base_CN.md](../../../docs/pattern/text/Text_Knowledge_Base_CN.md) - In-depth design analysis, implementation details, ArkTS usage examples
- Text theme: `frameworks/core/components/text/text_theme.h`
- Paragraph implementation: `frameworks/core/components_ng/render/paragraph.h`
- Layout algorithm: `frameworks/core/components_ng/pattern/text/text_layout_algorithm.h`
