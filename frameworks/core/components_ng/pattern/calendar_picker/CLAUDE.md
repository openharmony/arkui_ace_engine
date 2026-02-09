# CalendarPicker Component - Technical Overview

**Core**: Lightweight date entry with calendar dialog popup for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → CalendarModifier (bridge/)
    → CalendarPickerPattern (pattern/) - Entry logic and state
    → CalendarDialogPattern (calendar_dialog/) - Calendar dialog
    → Calendar (calendar/) - Calendar view
```

## Core Classes

### CalendarPickerPattern (pattern/calendar_picker/calendar_picker_pattern.h)

**Key Members**:
```cpp
CalendarSettingData calendarData_;           // Calendar data
CalendarPickerSelectedType selected_;        // Current selection type (year/month/day)
CalendarEdgeAlign align_;                    // Dialog alignment
DimensionOffset offset_;                     // Dialog offset

int32_t yearIndex_ = 0;                      // Text indices
int32_t monthIndex_ = 2;
int32_t dayIndex_ = 4;

bool isDialogShow_ = false;                  // Dialog show state
bool isKeyWaiting_ = false;                  // Keyboard input waiting state
bool isMarkToday_ = false;                   // Whether to mark today

uint32_t yearEnterCount_ = 0;                // Year input count
uint32_t monthPrefixZeroCount_ = 0;          // Month leading zero count
uint32_t dayPrefixZeroCount_ = 0;            // Day leading zero count
```

**Lifecycle Flow**:
```
OnModifyDone() → InitDateIndex()
    → InitClickEvent()
    → InitOnKeyEvent()
    → InitOnHoverEvent()
    → FlushTextStyle()
    → UpdateEdgeAlign()
```

**Critical Methods**:
- `OnModifyDone()`: Initialize component and events
- `HandleClickEvent()`: Process click events on year/month/day/± buttons
- `HandleNumberKeyEvent()`: Process numeric key input
- `HandleYearKeyEvent()`: Year input with leading zero handling
- `ShowDialog()`: Popup calendar dialog
- `OnValueChange()`: Trigger onChange event

### CalendarSettingData

```cpp
struct CalendarSettingData {
    PickerDate selectedDate;        // Current selected date
    PickerDate startDate;           // Start date
    PickerDate endDate;             // End date
    std::optional<Dimension> dayRadius;  // Day corner radius
    RefPtr<ResourceObject> dayRadiusResObj;
    WeakPtr<FrameNode> entryNode;   // Entry node
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;  // Disabled date ranges
    bool markToday;                 // Whether to mark today
};
```

### CalendarPickerSelectedType

```cpp
enum class CalendarPickerSelectedType {
    YEAR = 0,        // Year region
    MONTH,           // Month region
    DAY,             // Day region
    ADDBTN,          // Add button
    SUBBTN,          // Subtract button
    OTHER,           // Other region
};
```

## Complete Interaction Flow

### Click to Show Dialog

```
User clicks year/month/day text region
    ↓
HandleClickEvent(globalLocation)
    → CheckRegion(globalLocation) → Determine click region
    → SetSelectedType(type)
    → ShowDialog()
    → Create CalendarDialogPattern
    → Set initial selected date
    → Show dialog
```

### Keyboard Number Input

```
User presses number key (0-9)
    ↓
HandleNumberKeyEvent(event)
    → Dispatch based on selected_:
      - YEAR → HandleYearKeyEvent()
      - MONTH → HandleMonthKeyEvent()
      - DAY → HandleDayKeyEvent()
    ↓
HandleYearKeyWaitingEvent()
    → Accumulate digits to build year/month/day
    → Auto-complete when length reached
    → OnValueChange() → Trigger onChange event
```

### Add/Subtract Button Operation

```
User clicks add/subtract button
    ↓
HandleAddButtonClick() / HandleSubButtonClick()
    → Adjust date based on selected_:
      - YEAR: ±1 year
      - MONTH: ±1 month (with range check)
      - DAY: ±1 day (with range check)
    ↓
AdjustSolarDate() → Adjust to valid range
    ↓
OnValueChange() → Trigger onChange event
    ↓
UpdateEntryButtonColor() → Update button state
```

## Critical Technical Points

### 1. Date Range Constraints

```cpp
void CalendarPickerPattern::SetCalendarData(const CalendarSettingData& data) {
    CalendarSettingData settingData = data;

    // Auto-adjust selected date to valid range
    settingData.selectedDate = PickerDate::AdjustDateToRange(
        data.selectedDate,
        data.startDate,
        data.endDate
    );

    calendarData_ = settingData;
}

void AdjustSolarDate(PickerDate& date, const PickerDate& start, const PickerDate& end) {
    if (SolarDateCompare(date, start) < 0) {
        date = start;  // Less than start date
        return;
    }
    if (SolarDateCompare(date, end) > 0) {
        date = end;    // Greater than end date
    }
}
```

### 2. Disabled Date Ranges

```cpp
std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;

// Check if date is disabled
bool IsDateDisabled(const PickerDate& date) {
    for (const auto& range : disabledDateRange) {
        if (SolarDateCompare(date, range.first) >= 0 &&
            SolarDateCompare(date, range.second) <= 0) {
            return true;
        }
    }
    return false;
}
```

### 3. Dialog Edge Alignment

```cpp
enum class CalendarEdgeAlign {
    EDGE_ALIGN_START = 0,   // Left align
    EDGE_ALIGN_CENTER,      // Center align
    EDGE_ALIGN_END,         // Right align
};

OffsetF CalendarPickerPattern::CalculateDialogOffset() {
    auto host = GetHost();
    auto geometryNode = host->GetGeometryNode();
    auto offset = geometryNode->GetOffset();

    // Calculate offset based on alignment
    switch (align_) {
        case CalendarEdgeAlign::EDGE_ALIGN_START:
            // Left align, no extra offset
            break;
        case CalendarEdgeAlign::EDGE_ALIGN_CENTER:
            // Center align
            offset += DimensionOffset(dialogWidth / 2, 0);
            break;
        case CalendarEdgeAlign::EDGE_ALIGN_END:
            // Right align
            offset += DimensionOffset(dialogWidth, 0);
            break;
    }

    return offset;
}
```

### 4. Hover Effect

```cpp
void CalendarPickerPattern::HandleTextHoverEvent(bool state, int32_t index) {
    auto host = GetHost();
    auto textNode = DynamicCast<FrameNode>(host->GetChildAtIndex(index));

    // Update hover style
    if (state) {
        // Hover state
        textNode->GetRenderContext()->UpdateBackgroundColor(hoverColor);
    } else {
        // Normal state
        textNode->GetRenderContext()->UpdateBackgroundColor(normalColor);
    }
}
```

### 5. Button State Update

```cpp
void CalendarPickerPattern::UpdateEntryButtonColor() {
    auto host = GetHost();

    // Get add/subtract buttons
    auto addButton = DynamicCast<FrameNode>(host->GetChildAtIndex(addId_));
    auto subButton = DynamicCast<FrameNode>(host->GetChildAtIndex(subId_));

    // Check if can continue add/subtract
    bool canAdd = IsAddOrSubButtonEnable(ADD_BUTTON_INDEX);
    bool canSub = IsAddOrSubButtonEnable(SUB_BUTTON_INDEX);

    // Update button color and state
    if (!canAdd) {
        addButton->GetRenderContext()->UpdateOpacity(disabledOpacity);
    }
    if (!canSub) {
        subButton->GetRenderContext()->UpdateOpacity(disabledOpacity);
    }
}

bool CalendarPickerPattern::IsAddOrSubButtonEnable(int32_t buttonIndex) {
    auto& date = calendarData_.selectedDate;
    auto& start = calendarData_.startDate;
    auto& end = calendarData_.endDate;

    if (buttonIndex == ADD_BUTTON_INDEX) {
        // Check if can increase
        PickerDate testDate = date;
        switch (selected_) {
            case CalendarPickerSelectedType::YEAR:
                testDate.AddYears(1);
                break;
            case CalendarPickerSelectedType::MONTH:
                testDate.AddMonths(1);
                break;
            case CalendarPickerSelectedType::DAY:
                testDate.AddDays(1);
                break;
        }
        return SolarDateCompare(testDate, end) <= 0;
    } else {
        // Check if can decrease
        PickerDate testDate = date;
        switch (selected_) {
            case CalendarPickerSelectedType::YEAR:
                testDate.AddYears(-1);
                break;
            case CalendarPickerSelectedType::MONTH:
                testDate.AddMonths(-1);
                break;
            case CalendarPickerSelectedType::DAY:
                testDate.AddDays(-1);
                break;
        }
        return SolarDateCompare(testDate, start) >= 0;
    }
}
```

## Property System

### CalendarPickerLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **calendarData** | CalendarSettingData | - | Calendar data (selected date, start/end dates, etc.) |
| **align** | CalendarEdgeAlign | END | Dialog alignment |
| **offset** | DimensionOffset | - | Dialog offset |
| **textStyle** | PickerTextStyle | - | Text style |
| **markToday** | bool | false | Whether to mark today |

### CalendarSettingData Properties

| Property | Type | Description |
|----------|------|-------------|
| **selectedDate** | PickerDate | Current selected date |
| **startDate** | PickerDate | Start date |
| **endDate** | PickerDate | End date |
| **dayRadius** | Dimension | Day corner radius |
| **disabledDateRange** | vector\<pair\> | List of disabled date ranges |
| **markToday** | bool | Whether to mark today |

## Event System

### Event Types

**onChange** - Date change:
```cpp
void CalendarPickerPattern::OnValueChange() {
    auto eventHub = GetEventHub<CalendarPickerEventHub>();
    auto onChangeEvent = eventHub->GetChangeEvent();

    if (onChangeEvent) {
        auto info = GetEntryDateInfo();
        onChangeEvent(info);  // Trigger ArkTS onChange callback
    }
}
```

**Event Data Format**:
```cpp
std::string CalendarPickerPattern::GetEntryDateInfo() {
    // Format: "year-month-day"
    auto& date = calendarData_.selectedDate;
    return std::to_string(date.GetYear()) + "-" +
           std::to_string(date.GetMonth()) + "-" +
           std::to_string(date.GetDay());
}
```

## Dialog System

### Dialog Popup

```cpp
void CalendarPickerPattern::ShowDialog() {
    if (isDialogShow_) {
        return;  // Already shown
    }

    // Prepare dialog properties
    CalendarPickerOption option;
    option.data = calendarData_;
    option.alignType = align_;
    option.offset = offset_;
    option.textStyle = GetTextStyle();

    // Create and show dialog
    CalendarDialogView::Show(option);
    isDialogShow_ = true;
}
```

### Dialog Close

```cpp
void CalendarPickerPattern::SetDialogShow(bool flag) {
    isDialogShow_ = flag;

    if (!flag) {
        // Dialog closed, date may have changed
        OnValueChange();
        UpdateEntryButtonColor();
    }
}
```

## Accessibility Support

### Focus Management

```cpp
FocusPattern CalendarPickerPattern::GetFocusPattern() const {
    return {
        FocusType::NODE,          // Node-level focus
        true,                      // Focusable
        FocusStyleType::CUSTOM_REGION  // Custom focus region
    };
}
```

### Keyboard Navigation

```cpp
bool CalendarPickerPattern::HandleKeyEvent(const KeyEvent& event) {
    switch (event.GetKeyCode()) {
        case KeyCode::KEY_UP:
            // Up arrow → date +1
            HandleAddButtonClick();
            return true;
        case KeyCode::KEY_DOWN:
            // Down arrow → date -1
            HandleSubButtonClick();
            return true;
        case KeyCode::KEY_TAB:
            // Tab → switch selected type
            SwitchSelectedType();
            return true;
        case KeyCode::KEY_ENTER:
            // Enter → show dialog
            ShowDialog();
            return true;
        default:
            // Number keys → input number
            if (event.GetKeyCode() >= KeyCode::KEY_0 &&
                event.GetKeyCode() <= KeyCode::KEY_9) {
                return HandleNumberKeyEvent(event);
            }
            return false;
    }
}
```

## Best Practices

### Basic Usage

```typescript
// 1. Set reasonable date range
CalendarPicker({
  start: new Date('1900-1-1'),
  end: new Date('2100-12-31'),
  selected: new Date('2024-1-1')
})
  .onChange((date: string) => {
    console.log('Selected:', date);  // "2024-1-1"
  })

// 2. Mark today
CalendarPicker({
  markToday: true
})

// 3. Disable specific date ranges
CalendarPicker({
  disabledDateRange: [
    { start: new Date('2024-1-1'), end: new Date('2024-1-7') }
  ]
})
```

### Dialog Configuration

```typescript
// Set dialog alignment
CalendarPicker()
  .edgeAlign(CalendarEdgeAlign.START)    // Left align
  // .edgeAlign(CalendarEdgeAlign.CENTER) // Center
  // .edgeAlign(CalendarEdgeAlign.END)    // Right align

// Set dialog offset
CalendarPicker()
  .dialogOffset({ dx: 10, dy: 20 })
```

## Related Directories

```
frameworks/core/components_ng/pattern/calendar_picker/
├── calendar_picker_pattern.h/cpp             # Main logic
├── calendar_picker_layout_property.h         # Layout properties
├── calendar_picker_layout_algorithm.h/cpp    # Layout algorithm
├── calendar_picker_event_hub.h               # Event handling
├── calendar_dialog_pattern.h/cpp            # Dialog pattern
├── calendar_dialog_layout_algorithm.h/cpp   # Dialog layout
├── calendar_type_define.h                   # Type definitions
└── bridge/
    ├── calendar_picker_static_modifier.cpp  # Static modifier
    └── calendar_picker_dynamic_module.cpp   # Dynamic module
```

## Key Takeaways

1. **Entry Mode**: Lightweight entry, show full calendar dialog on click
2. **Date Range**: Flexible start/end date configuration with auto-adjustment
3. **Keyboard Support**: Complete numeric input and arrow key navigation
4. **Edge Alignment**: Support dialog left/center/right alignment
5. **Disabled Dates**: Support configurable disabled date ranges
6. **Hover Effect**: Support mouse hover highlight
7. **Button State**: Auto enable/disable add/subtract buttons based on date range
8. **Accessibility**: Complete focus management and keyboard navigation support
