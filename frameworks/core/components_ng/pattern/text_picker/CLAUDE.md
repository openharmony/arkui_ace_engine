# TextPicker Component - Technical Overview

**Core**: Text selector with multi-column cascade support for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → TextPickerModifier (bridge/)
    → TextPickerPattern (pattern/) - Business logic and multi-column management
    → TextPickerColumnPattern (pattern/) - Single column scroll logic
    → ContainerPicker (container_picker/) - Scroll and snap
```

## Core Classes

### TextPickerPattern (pattern/text_picker/textpicker_pattern.h)

**Key Members**:
```cpp
// Option data
std::vector<NG::RangeContent> range_;                  // Single column options
std::vector<NG::RangeContent> options_;                // Single column options (alias)
std::vector<NG::TextCascadePickerOptions> cascadeOptions_;  // Cascade options
std::map<WeakPtr<FrameNode>, std::vector<NG::RangeContent>> optionsWithNode_;

// Selection state
uint32_t selectedIndex_ = 0;                           // Single column selected index
std::vector<uint32_t> selecteds_;                       // Multi-column selected index
std::vector<std::string> values_;                      // Selected values

// Column config
uint32_t columnsKind_ = 0;                             // Column count
std::vector<Dimension> columnWidths_;                   // Column widths
bool isCascade_ = false;                                // Whether cascade

// Styles
Color backgroundColor_ = Color::WHITE;
ItemDivider divider_;
Dimension gradientHeight_;
Dimension dividerSpacing_;
PickerTextProperties textProperties_;

// Dialog buttons
WeakPtr<FrameNode> weakButtonConfirm_;
WeakPtr<FrameNode> weakButtonCancel_;
```

**Lifecycle Flow**:
```
OnModifyDone() → OnColumnsBuilding()
    → InitOnKeyEvent()
    → InitFocusEvent()
```

**Critical Methods**:
- `OnModifyDone()`: Initialize component and build columns
- `OnColumnsBuildingUnCascade()`: Build non-cascade columns
- `OnColumnsBuildingCascade()`: Build cascade columns
- `HandleColumnChange()`: Handle column change with cascade update
- `UpdateCascadeColumns()`: Update cascade child columns
- `GetSelectedObject()`: Build selection result data

### TextPickerColumnPattern

**Key Methods**:
```cpp
class TextPickerColumnPattern : public Pattern {
public:
    void SetOptions(const std::vector<NG::RangeContent>& options);
    void SetSelected(uint32_t index);
    uint32_t GetSelected() const;

    std::string GetText() const;  // Get selected text

    // Cascade options
    void SetCascadeOptions(const std::vector<NG::TextCascadePickerOptions>& options);
    NG::TextCascadePickerOptions GetCascadeOption(uint32_t index);

    void OnColumnChange(bool isAdd, uint32_t index, bool needNotify);
};
```

### RangeContent

```cpp
struct RangeContent {
    std::string text_;      // Display text
    std::string icon_;      // Icon (optional)
    std::string value_;     // Actual value (optional)
};
```

### TextCascadePickerOptions

```cpp
struct TextCascadePickerOptions {
    std::string text_;                  // Display text
    uint32_t parentValue_;              // Parent value
    std::vector<TextCascadePickerOptions> children_;  // Child options
};
```

## Complete Interaction Flow

### Single Column Selection Flow

```
User scrolls option column
    ↓
TextPickerColumnPattern::OnColumnChange()
    ↓
Update selectedIndex_
    ↓
FireChangeEvent(true)
    ↓
Build return data:
  GetSelectedObject()
    ↓
Trigger ArkTS onChange callback
```

### Cascade Selection Flow

```
User scrolls first column
    ↓
TextPickerColumnPattern::OnColumnChange()
    ↓
HandleColumnChange(tag, isAdd, index, needNotify)
    ↓
Get selected parent option
    ↓
UpdateCascadeColumns(parentId, parentOption)
    ↓
Regenerate subsequent columns:
  - Clear child column options
  - Fill based on parentOption.children_
  - Reset child column selected index to 0
    ↓
FireChangeEvent(true)
    ↓
Build cascade data return
```

## Critical Technical Points

### 1. Cascade Option Handling

```cpp
void TextPickerPattern::UpdateCascadeColumns(
    int32_t parentColumnId,
    const NG::TextCascadePickerOptions& parentOption)
{
    auto host = GetHost();
    uint32_t columnIndex = GetColumnIndex(parentColumnId);

    // Iterate subsequent columns
    for (uint32_t i = columnIndex + 1; i < columnsKind_; ++i) {
        auto column = GetColumnNode(i);

        if (i == columnIndex + 1) {
            // Next column: use parent option's children
            if (!parentOption.children_.empty()) {
                FillCascadeColumnOptions(column, parentOption.children_);
                SetColumnSelected(column, 0);
            } else {
                ClearColumnOptions(column);
            }
        } else {
            // Further columns: clear
            ClearColumnOptions(column);
        }
    }
}

void TextPickerPattern::ProcessCascadeOptions(
    const std::vector<NG::TextCascadePickerOptions>& options,
    std::vector<NG::TextCascadePickerOptions>& reOptions,
    uint32_t index)
{
    // Process cascade option data
    for (const auto& option : options) {
        NG::TextCascadePickerOptions newOption;
        newOption.text_ = option.text_;
        newOption.parentValue_ = index;

        // Recursively process child options
        if (!option.children_.empty()) {
            ProcessCascadeOptions(option.children_, newOption.children_, ...);
        }

        reOptions.emplace_back(newOption);
    }
}
```

### 2. Range Parsing

```cpp
// Type: RANGE_TYPE_INT (integer range)
TextPicker({
  range: ['2010', '2011', '2012', '2013', '2014', '2015', '2016', '2017', '2018',
          '2019', '2020', '2021', '2022', '2023', '2024']
})
.rangeType(RangeType.RANGE_TYPE_INT)

// Parse logic
void TextPickerPattern::ParseRangeResult(NG::TextCascadePickerOptions& option) {
    std::vector<std::string> rangeResultValue;

    // Parse from resource
    if (rangeType_ == RANGE_TYPE_INT) {
        // Integer range: [0, 100] → "0", "1", "2", ..., "100"
        for (int32_t i = rangeStart_; i <= rangeEnd_; ++i) {
            rangeResultValue.emplace_back(std::to_string(i));
        }
    } else if (rangeType_ == RANGE_TYPE_FLOAT) {
        // Float range
        double value = rangeStart_;
        while (value <= rangeEnd_) {
            rangeResultValue.emplace_back(std::to_string(value));
            value += rangeStep_;
        }
    } else if (rangeType_ == RANGE_TYPE_STRING) {
        // String array
        rangeResultValue = rangeValues_;
    }

    // Fill options
    for (const auto& value : rangeResultValue) {
        NG::RangeContent content;
        content.text_ = value;
        options_.emplace_back(content);
    }
}
```

### 3. Option Retrieval

```cpp
std::string TextPickerPattern::GetOption(uint32_t index) const {
    if (index >= GetOptionCount()) {
        return "";
    }
    return options_[index].text_;
}

std::string TextPickerPattern::GetSelectedObject(
    bool isColumnChange, int32_t status, bool isEnterSelectedAreaEvent) const
{
    if (isCascade_) {
        return GetSelectedObjectMulti(values_, selecteds_, status);
    }

    // Single column mode
    return std::to_string(selectedIndex_);
}

std::string TextPickerPattern::GetSelectedObjectMulti(
    const std::vector<std::string>& values,
    const std::vector<uint32_t>& indexs,
    int32_t status) const
{
    // Build multi-column selection result
    std::string result = "{";
    for (size_t i = 0; i < values.size(); ++i) {
        result += "\"" + std::to_string(i) + "\":\"" + values[i] + "\"";
        if (i < values.size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
}
```

### 4. Custom Styles

```cpp
void TextPickerPattern::SetTextProperties(const PickerTextProperties& properties) {
    textProperties_ = properties;

    // Disappear text style
    if (properties.disappearTextStyle_.fontSize.has_value()) {
        gradientHeight_ = properties.disappearTextStyle_.fontSize.value();
    }

    // Normal text style
    if (properties.normalTextStyle_.fontSize.has_value()) {
        gradientHeight_ = std::max(properties.normalTextStyle_.fontSize.value(),
                                   gradientHeight_);
    }

    // Selected text style
    if (properties.selectedTextStyle_.fontSize.has_value()) {
        dividerSpacing_ = properties.selectedTextStyle_.fontSize.value();
    }
}
```

### 5. Digital Crown Support

```cpp
#ifdef SUPPORT_DIGITAL_CROWN
void TextPickerPattern::InitOnCrownEvent(const RefPtr<FocusHub>& focusHub) {
    auto crownEvent = [weak = WeakClaim(this)](const CrownEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);

        if (!pattern->haveFocus_) {
            return false;
        }

        // Adjust selected value based on rotation direction
        if (event.rotation > 0) {
            pattern->ShowNext();
        } else {
            pattern->ShowPrevious();
        }

        return true;
    };

    focusHub->SetOnCaptureCrownEvent(crownEvent);
}
#endif
```

## Property System

### TextPickerLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **range** | vector\<RangeContent\> | - | Option range |
| **selected** | uint32_t | 0 | Selected index |
| **value** | string | - | Selected value |
| **columnsKind** | uint32_t | 1 | Column count |
| **columnWidths** | vector\<Dimension\> | - | Column widths |
| **isCascade** | bool | false | Whether cascade |
| **canLoop** | bool | true | Whether loop |

### Style Properties

| Property | Type | Description |
|----------|------|-------------|
| **backgroundColor** | Color | Background color |
| **divider** | ItemDivider | Divider style |
| **gradientHeight** | Dimension | Gradient height |
| **dividerSpacing** | Dimension | Divider spacing |
| **textProperties** | PickerTextProperties | Text styles |

### PickerTextProperties

```cpp
struct PickerTextProperties {
    PickerTextStyle disappearTextStyle_;  // Disappear text style
    PickerTextStyle normalTextStyle_;     // Normal text style
    PickerTextStyle selectedTextStyle_;   // Selected text style
};

struct PickerTextStyle {
    std::optional<Color> color;
    std::optional<Dimension> fontSize;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<Dimension> minFontSize;
    std::optional<Dimension> maxFontSize;
};
```

## Event System

### Event Types

**onChange** - Selection change:
```cpp
void TextPickerPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onChange = eventHub->GetChangeEvent();

    if (onChange) {
        auto info = GetSelectedObject(false);
        onChange(info);  // Trigger ArkTS onChange callback
    }
}
```

**onScrollStop** - Scroll stop:
```cpp
void TextPickerPattern::FireScrollStopEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onScrollStop = eventHub->GetScrollStopEvent();

    if (onScrollStop) {
        onScrollStop(selectedIndex_);
    }
}
```

**onEnterSelectedArea** - Enter selected area:
```cpp
void TextPickerPattern::FireEnterSelectedAreaEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onEnterSelectedArea = eventHub->GetEnterSelectedAreaEvent();

    if (onEnterSelectedArea) {
        onEnterSelectedArea(true);
    }
}
```

## Cascade Options

### Cascade Data Structure

```typescript
// Province-city-district cascade example
TextPicker({
  cascadeOptions: [
    {
      text: '广东省',
      parentValue: 0,
      children: [
        {
          text: '广州市',
          parentValue: 0,
          children: [
            { text: '天河区', parentValue: 0 },
            { text: '越秀区', parentValue: 1 },
            // ...
          ]
        },
        {
          text: '深圳市',
          parentValue: 1,
          children: [
            { text: '南山区', parentValue: 0 },
            { text: '福田区', parentValue: 1 },
            // ...
          ]
        }
      ]
    },
    // ... other provinces
  ]
})
```

### Cascade Update Flow

```
First column selects "广东省"
    ↓
HandleColumnChange(firstColumn, false, selectedIndex, true)
    ↓
Get cascadeOptions_[selectedIndex]
    ↓
Update second column:
  - Clear old options
  - Fill children_ (广州市, 深圳市, ...)
  - Select first (广州市)
    ↓
Update third column:
  - Clear old options
  - Fill 广州市.children_ (天河区, 越秀区, ...)
  - Select first (天河区)
```

## Custom Styles

### Gradient Effect

```cpp
// PaintMethod draw gradient
void TextPickerPaintMethod::PaintGradient(PaintWrapper* paintWrapper) {
    auto canvas = paintWrapper->GetCanvas();

    // Upper gradient (disappear text)
    auto gradient1 = canvas->CreateLinearGradient(0, 0, 0, gradientHeight_);
    gradient1->AddColorStop(0.0, Color::TRANSPARENT);
    gradient1->AddColorStop(1.0, Color::WHITE);

    // Lower gradient
    auto gradient2 = canvas->CreateLinearGradient(0, height - gradientHeight_,
                                                  0, height);
    gradient2->AddColorStop(0.0, Color::WHITE);
    gradient2->AddColorStop(1.0, Color::TRANSPARENT);

    // Draw gradient
    canvas->DrawRect(0, 0, width, gradientHeight_, gradient1);
    canvas->DrawRect(0, height - gradientHeight_, width, gradientHeight_, gradient2);
}
```

### Divider Style

```cpp
struct ItemDivider {
    bool startMargin = false;
    bool endMargin = false;
    Dimension strokeWidth = 2.0_vp;
    Color color = Color::GRAY;
    Dimension marginTop = 0.0_vp;
    Dimension marginBottom = 0.0_vp;
};

// Draw divider
void TextPickerPaintMethod::PaintDivider(PaintWrapper* paintWrapper) {
    if (!divider_.strokeWidth.IsValid()) {
        return;
    }

    auto canvas = paintWrapper->GetCanvas();
    Paint paint;
    paint.SetAntiAlias(true);

    // Upper divider
    float topY = (pickerHeight - dividerSpacing) / 2;
    canvas->DrawLine(offsetX, topY, offsetX + width, topY, paint);

    // Lower divider
    float bottomY = topY + dividerSpacing;
    canvas->DrawLine(offsetX, bottomY, offsetX + width, bottomY, paint);
}
```

## Best Practices

### Basic Usage

```typescript
// 1. Single column selection
TextPicker({ range: ['A', 'B', 'C', 'D', 'E'] })
  .selected(0)
  .onChange((value: string) => {
    console.log('Selected:', value);
  })

// 2. Multi-column independent selection
TextPicker({
  range: [
    ['2010', '2011', '2012'],
    ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12'],
    ['1', '2', '3']
  ]
})
  .columnsKind(3)

// 3. Cascade selection
TextPicker({
  cascadeOptions: provinceCityData
})
  .isCascade(true)
```

### Style Customization

```typescript
// Custom text style
TextPicker()
  .textStyle({
    disappearTextStyle: { color: '#CCCCCC', fontSize: 14 },
    normalTextStyle: { color: '#333333', fontSize: 16 },
    selectedTextStyle: { color: '#FF0000', fontSize: 18 }
  })

// Custom divider
TextPicker()
  .divider({
    strokeWidth: 2,
    color: Color.Blue,
    startMargin: true,
    endMargin: true
  })

// Custom gradient
TextPicker()
  .gradientHeight(50)
  .dividerSpacing(40)
```

## Related Directories

```
frameworks/core/components_ng/pattern/text_picker/
├── textpicker_pattern.h/cpp                   # Main logic
├── textpicker_column_pattern.h/cpp            # Column pattern
├── textpicker_layout_property.h                # Layout properties
├── textpicker_event_hub.h                     # Event handling
├── textpicker_paint_method.h/cpp              # Paint method
├── textpicker_dialog_view.h/cpp               # Dialog view
├── textpicker_accessibility_property.h/cpp     # Accessibility properties
├── toss_animation_controller.h/cpp            # Animation control
├── textpicker_properties.h                    # Property definitions
└── textpicker_overscroll.h/cpp                // Scroll boundary handling
```

## Key Takeaways

1. **Multi-column Support**: Support single column and multi-column independent selection
2. **Cascade Linkage**: Parent-child columns auto linkage update options
3. **Custom Range**: Flexible range definition (integer/float/string)
4. **Rich Styles**: Gradient, divider, text styles comprehensive support
5. **Digital Crown**: Support watch device digital crown operation
6. **Haptic Feedback**: Vibration feedback during scrolling
7. **Dialog Support**: Can display in dialog
8. **Accessibility**: Complete keyboard navigation and focus management
