# DatePicker Component - Technical Overview

**Core**: Complete date selector with Solar/Lunar calendar support for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → DatePickerModifier (bridge/)
    → DatePickerPattern (pattern/) - Business logic and linkage control
    → DatePickerColumnPattern (pattern/) - Single column scroll logic
    → ContainerPicker (container_picker/) - Scroll and snap
```

## Core Classes

### DatePickerPattern (pattern/picker/datepicker_pattern.h)

**Key Members**:
```cpp
// Date data
PickerDate selectedDate_;         // Current selected date (Solar)
LunarDate selectedLunar_;         // Current selected date (Lunar)
PickerDate startDateSolar_;       // Start date (Solar)
LunarDate startDateLunar_;        // Start date (Lunar)
PickerDate endDateSolar_;         // End date (Solar)
LunarDate endDateLunar_;          // End date (Lunar)

// Mode and config
DatePickerMode datePickerMode_;   // Picker mode
bool lunar_;                      // Whether show Lunar
bool showMonthDays_;              // Whether show month-days mode
bool isLoop_;                     // Whether loop
std::string dateOrder_;           // Date order

// Column data
std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>> options_;
std::vector<WeakPtr<FrameNode>> datePickerColumns_;

// Node IDs
std::optional<int32_t> yearId_;
std::optional<int32_t> monthId_;
std::optional<int32_t> dayId_;
std::optional<int32_t> monthDaysId_;

// Events
EventMarker OnDialogAccept_;
EventMarker OnDialogCancel_;
EventMarker OnDialogChange_;
```

**Lifecycle Flow**:
```
OnModifyDone() → Build columns based on mode (DATE/TIME/MONTH_DAYS) and calendar (Solar/Lunar)
    → SolarColumnsBuilding() / LunarColumnsBuilding()
    → InitOnKeyEvent()
    → InitFocusEvent()
```

**Critical Methods**:
- `OnModifyDone()`: Initialize component and build columns
- `SolarColumnsBuilding()`: Build Solar year/month/day columns
- `HandleYearChange()`: Handle year change with linkage
- `HandleMonthChange()`: Handle month change with linkage
- `OnDataLinking()`: Data linkage handler
- `SolarToLunar()`: Convert Solar to Lunar date
- `LunarToSolar()`: Convert Lunar to Solar date

### DatePickerColumnPattern

**Key Methods**:
```cpp
class DatePickerColumnPattern : public Pattern {
public:
    void SetOptions(const std::vector<PickerDateF>& options);
    uint32_t GetSelected() const;
    PickerDateF GetOptionValue(uint32_t index);

    // Scroll callback
    void OnColumnChange(bool isAdd, uint32_t index, bool needNotify);
};
```

### PickerDate / LunarDate

```cpp
struct PickerDate {
    int32_t year;
    int32_t month;   // 1-12
    int32_t day;     // 1-31

    static PickerDate Current();        // Current date
    void AddYears(int32_t years);
    void AddMonths(int32_t months);
    void AddDays(int32_t days);
};

struct LunarDate {
    int32_t year;
    int32_t month;   // 1-12
    int32_t day;     // 1-30
    bool isLeap;     // Whether leap month
};
```

## Complete Interaction Flow

### Column Building Flow

```
OnModifyDone()
    ↓
Based on mode (DATE/TIME/MONTH_DAYS) and calendar (Solar/Lunar)
    ↓
SolarColumnsBuilding() / LunarColumnsBuilding()
    ↓
For each column create/get node:
  - Year column: FillSolarYearOptions()
  - Month column: FillSolarMonthOptions()
  - Day column: FillSolarDayOptions()
    ↓
Fill option data:
  - Generate valid range based on start/end dates
  - Set current selected value
    ↓
OrderAllChildNode() → Add to layout tree
```

### Scroll Linkage Flow

```
User scrolls a column
    ↓
DatePickerColumnPattern::OnColumnChange()
    ↓
DatePickerPattern::OnDataLinking()
    ↓
Identify changed column:
  - Year column → HandleYearChange()
  - Month column → HandleMonthChange()
  - Day column → HandleDayChange()
    ↓
Update selectedDate_ / selectedLunar_
    ↓
Adjust date range:
  AdjustSolarDate() / AdjustLunarDate()
    ↓
Rebuild affected columns:
  FlushMonthDaysColumn() / FlushDayColumn()
    ↓
FireChangeEvent() → Trigger onChange event
```

## Critical Technical Points

### 1. Solar-Lunar Conversion

```cpp
LunarDate DatePickerPattern::SolarToLunar(const PickerDate& date) const {
    // Use calendar algorithm library for conversion
    LunarDate lunar;

    // 1. Convert to Lunar year-month-day
    int32_t year = date.GetYear();
    int32_t month = date.GetMonth();
    int32_t day = date.GetDay();

    // 2. Call underlying conversion API
    CalendarConverter::SolarToLunar(year, month, day,
                                   lunar.year, lunar.month,
                                   lunar.day, lunar.isLeap);

    return lunar;
}

PickerDate DatePickerPattern::LunarToSolar(const LunarDate& date) const {
    PickerDate solar;

    // Call underlying conversion API
    CalendarConverter::LunarToSolar(date.year, date.month, date.day,
                                   date.isLeap,
                                   solar.year, solar.month, solar.day);

    return solar;
}
```

### 2. Date Range Constraints

```cpp
void DatePickerPattern::AdjustSolarDate(
    PickerDate& date,
    const PickerDate& start,
    const PickerDate& end) const
{
    if (SolarDateCompare(date, start) < 0) {
        date = start;  // Less than start date
        return;
    }
    if (SolarDateCompare(date, end) > 0) {
        date = end;    // Greater than end date
    }
}

int DatePickerPattern::SolarDateCompare(
    const PickerDate& left,
    const PickerDate& right) const
{
    if (left.GetYear() != right.GetYear()) {
        return left.GetYear() > right.GetYear() ? 1 : -1;
    }
    if (left.GetMonth() != right.GetMonth()) {
        return left.GetMonth() > right.GetMonth() ? 1 : -1;
    }
    if (left.GetDay() != right.GetDay()) {
        return left.GetDay() > right.GetDay() ? 1 : -1;
    }
    return 0;  // Equal
}
```

### 3. Leap Month Handling

```cpp
uint32_t DatePickerPattern::GetLunarMaxDay(
    uint32_t year, uint32_t month, bool isLeap) const
{
    // Get max days for Lunar month
    uint32_t leapMonth = 0;
    GetLunarLeapMonth(year, leapMonth);

    if (isLeap && month != leapMonth) {
        // Not leap month
        return 0;
    }

    // Lunar small month 29 days, large month 30 days
    if (IsLunarBigMonth(year, month)) {
        return 30;
    }
    return 29;
}

bool DatePickerPattern::GetLunarLeapMonth(
    uint32_t year, uint32_t& outLeapMonth) const
{
    // Query leap month for the year
    return CalendarConverter::GetLeapMonth(year, outLeapMonth);
}
```

### 4. Date Linkage Logic

```cpp
void DatePickerPattern::IncreaseLinkageYearMonth(PickerDate& date) {
    // Linkage logic when year/month increases
    if (date.GetMonth() == 12) {
        // December → next year January
        date.SetYear(date.GetYear() + 1);
        date.SetMonth(1);
    } else {
        date.SetMonth(date.GetMonth() + 1);
    }

    // Check if date out of range
    AdjustSolarDate(date, startDateSolar_, endDateSolar_);

    // Adjust date (e.g., Jan 31 → Feb 28)
    while (date.GetDay() > GetMaxDay(date.GetYear(), date.GetMonth())) {
        date.SetDay(date.GetDay() - 1);
    }
}

void DatePickerPattern::ReduceLinkageYearMonth(PickerDate& date) {
    // Linkage logic when year/month decreases
    if (date.GetMonth() == 1) {
        // January → previous year December
        date.SetYear(date.GetYear() - 1);
        date.SetMonth(12);
    } else {
        date.SetMonth(date.GetMonth() - 1);
    }

    AdjustSolarDate(date, startDateSolar_, endDateSolar_);

    // Adjust date
    while (date.GetDay() > GetMaxDay(date.GetYear(), date.GetMonth())) {
        date.SetDay(date.GetDay() - 1);
    }
}
```

### 5. Option Filling

```cpp
void DatePickerPattern::FillSolarYearOptions(
    const PickerDate& current,
    RefPtr<FrameNode>& yearColumn)
{
    std::vector<PickerDateF> yearOptions;

    // Generate year options
    for (int32_t year = startDateSolar_.GetYear();
         year <= endDateSolar_.GetYear(); ++year) {
        PickerDateF dateValue;
        dateValue.SetYear(year);
        yearOptions.emplace_back(dateValue);
    }

    // Set to column
    auto columnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetOptions(yearOptions);

    // Set current selected
    uint32_t selectedIndex = current.GetYear() - startDateSolar_.GetYear();
    columnPattern->SetSelected(selectedIndex);
}
```

## Property System

### DatePickerLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **start** | PickerDate | 1970-1-1 | Start date |
| **end** | PickerDate | 2100-12-31 | End date |
| **selected** | PickerDate | Current() | Selected date |
| **lunar** | bool | false | Whether show Lunar calendar |
| **mode** | DatePickerMode | DATE | Picker mode |
| **loop** | bool | true | Whether loop |
| **showLunarSwitch** | bool | false | Whether show Lunar switch |
| **dateOrder** | string | "ydm" | Date order |

### DatePickerMode

```cpp
enum class DatePickerMode {
    DATE,         // Year-month-day
    TIME,         // Hour-minute-second
    MONTH_DAYS,   // Month-day
    YEAR_MONTH    // Year-month
};
```

## Event System

### Event Types

**onChange** - Date change:
```cpp
void DatePickerPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<DatePickerEventHub>();
    auto onChangeEvent = eventHub->GetChangeEvent();

    if (onChangeEvent) {
        auto info = GetSelectedObject(false);
        onChangeEvent(info);  // Trigger ArkTS onChange callback
    }
}
```

**onAccept** - Confirm button:
```cpp
void DatePickerPattern::SetDialogAcceptEvent(const EventMarker& value) {
    OnDialogAccept_ = value;
}
```

**onCancel** - Cancel button:
```cpp
void DatePickerPattern::SetDialogCancelEvent(const EventMarker& value) {
    OnDialogCancel_ = value;
}
```

## Solar-Lunar Conversion

### Conversion Flow

```
Solar date (2024-1-1)
    ↓ SolarToLunar()
Lunar date (2023-November-Twenty)
    ↓ User scrolls Lunar columns
Lunar date (2023-December-First)
    ↓ LunarToSolar()
Solar date (2024-1-11)
```

### Lunar Display Format

```cpp
std::string DatePickerPattern::GetMonthFormatString(
    uint32_t month, bool isLunar, bool isLeap) const
{
    if (isLunar) {
        // Lunar month: "正月", "二月", ..., "腊月"
        // Leap month: "闰正月", "闰二月", ...
        if (isLeap) {
            return GetLunarLeapMonth(month);
        }
        return GetLunarMonth(month);
    }
    // Solar month: "1月", "2月", ..., "12月"
    return GetSolarMonth(month);
}
```

## Linkage Logic

### Year-Month Linkage

```
Year changes → Rebuild month and day columns
    ↓
Month changes → Rebuild day column (days may differ)
    ↓
Day changes → Usually no linkage to other columns
```

### Special Date Handling

```cpp
// Jan 31 → Scroll to Feb → Auto adjust to Feb 28/29
void AdjustDayForMonthChange(PickerDate& date) {
    int32_t maxDay = GetMaxDay(date.GetYear(), date.GetMonth());
    if (date.GetDay() > maxDay) {
        date.SetDay(maxDay);
    }
}

// Feb has 29 days in leap year, 28 days in common year
int32_t GetMaxDay(int32_t year, int32_t month) {
    if (month == 2) {
        return IsLeapYear(year) ? 29 : 28;
    }
    // Large month 31 days, small month 30 days
    static const int32_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}
```

## Best Practices

### Basic Usage

```typescript
// 1. Basic date selection
DatePicker({
  start: new Date('2000-1-1'),
  end: new Date('2030-12-31'),
  selected: new Date('2024-1-1')
})
  .onChange((value: string) => {
    console.log('Selected:', value);  // "2024-1-1"
  })

// 2. Lunar mode
DatePicker()
  .lunar(true)

// 3. Month-day mode
DatePicker()
  .mode(DatePickerMode.MONTH_DAYS)
```

### Range Configuration

```typescript
// Set reasonable date range
DatePicker()
  .start(new Date('1900-1-1'))
  .end(new Date('2100-12-31'))

// Limit selection range
DatePicker()
  .start(new Date('2024-1-1'))
  .end(new Date('2024-12-31'))
```

## Related Directories

```
frameworks/core/components_ng/pattern/picker/
├── datepicker_pattern.h/cpp                 # Main logic
├── datepicker_column_pattern.h/cpp          # Column pattern
├── datepicker_layout_property.h             # Layout properties
├── datepicker_event_hub.h                  # Event handling
├── datepicker_paint_method.h/cpp            # Paint method
├── date_time_animation_controller.h/cpp     # Animation control
├── picker_data.h/cpp                        # Data structures
├── picker_theme.h/cpp                       # Theme config
└── picker_utils/                            # Utils
    └── picker_column_pattern.h/cpp          # Column pattern base
```

## Key Takeaways

1. **Solar-Lunar Support**: Support both Solar and Lunar calendars with auto conversion
2. **Smart Linkage**: Year/month/day three columns intelligent linkage update
3. **Multiple Modes**: DATE/TIME/MONTH_DAYS multiple display modes
4. **Range Constraints**: Flexible start/end date configuration
5. **Leap Month Handling**: Correctly handle Lunar leap months and Solar leap years
6. **Date Adjustment**: Auto adjust special dates (e.g., Feb 30 → Feb 28)
7. **Event Callbacks**: onChange/onAccept/onCancel complete support
8. **Accessibility**: Complete keyboard navigation and focus management
