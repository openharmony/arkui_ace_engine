# TimePicker Component - Technical Overview

**Core**: Complete time selector with 12/24-hour format support for ACE Engine

## Architecture Overview

```
ArkTS Frontend
    → TimePickerModifier (bridge/)
    → TimePickerRowPattern (pattern/) - Business logic and multi-column management
    → TimePickerColumnPattern (pattern/) - Single column scroll logic
    → ContainerPicker (container_picker/) - Scroll and snap
```

## Core Classes

### TimePickerRowPattern (pattern/time_picker/timepicker_row_pattern.h)

**Key Members**:
```cpp
// Time data
PickerTime selectedTime_;         // Current selected time
PickerTime startTime_;            // Start time
PickerTime endTime_;              // End time

// Config
bool hour24_;                     // Whether 24-hour format
bool hasSecond_;                  // Whether show seconds
bool loop_;                       // Whether loop

// Column data
std::map<WeakPtr<FrameNode>, std::unordered_map<uint32_t, std::string>> options_;
std::map<WeakPtr<FrameNode>, uint32_t> optionsTotalCount_;
std::unordered_map<std::string, WeakPtr<FrameNode>> allChildNode_;

// Node IDs
std::optional<int32_t> amPmId_;
std::optional<int32_t> hourId_;
std::optional<int32_t> minuteId_;
std::optional<int32_t> secondId_;

// Language and locale
std::string language_;
std::string amPmTimeOrder_;
std::vector<std::string> vecAmPm_;  // AM/PM text

// Leading zero config
ZeroPrefixType prefixHour_;
ZeroPrefixType prefixMinute_;
ZeroPrefixType prefixSecond_;
```

**Lifecycle Flow**:
```
OnModifyDone() → OnColumnsBuilding()
    → InitOnKeyEvent()
    → InitFocusEvent()
    → UpdateLanguageAndAmPmTimeOrder()
```

**Critical Methods**:
- `OnModifyDone()`: Initialize component and build columns
- `OnColumnsBuilding()`: Build hour/minute/second columns
- `HandleHourColumnBuildingRange()`: Handle hour column building based on 12/24-hour format
- `OnDataLinking()`: Data linkage handler
- `SetHour24()`: Switch between 12/24-hour format
- `IsAmHour()`, `GetAmPmHour()`: AM/PM conversion utilities

### TimePickerColumnPattern

**Key Methods**:
```cpp
class TimePickerColumnPattern : public PickerColumnPattern {
public:
    void FlushCurrentOptions(bool isDown, bool isUpdateTextContentOnly);
    void UpdateColumnChildPosition(double offsetY);
    bool CanMove(bool isDown) const;
    void ScrollTimeColumn();
    void UpdateCurrentOffset(float offset);

    uint32_t GetOptionCount() const override;

    void SetHour24(bool value);
    bool GetHour24() const;
};
```

### PickerTime

```cpp
struct PickerTime {
    uint32_t hour;    // 0-23 (24-hour) or 1-12 (12-hour)
    uint32_t minute;  // 0-59
    uint32_t second;  // 0-59

    static PickerTime Current();        // Current time
    std::string ToString(bool, bool);   // Convert to string
};
```

## Complete Interaction Flow

### Column Building Flow

```
OnModifyDone()
    ↓
Based on current time and config (hour24, hasSecond)
    ↓
OnColumnsBuilding()
    ↓
For each column create/get node:
  - AM/PM column (12-hour): HandleAmPmColumnBuilding()
  - Hour column: HandleHourColumnBuildingRange()
  - Minute column: HandleMinAndSecColumnBuilding()
  - Second column: HandleSecColumnBuilding()
    ↓
Fill option data:
  - Generate valid range based on start/end times
  - Set current selected value
    ↓
AddChildToLayout() → Add to layout tree
```

### Scroll Linkage Flow

```
User scrolls a column
    ↓
TimePickerColumnPattern::OnColumnChange()
    ↓
TimePickerRowPattern::OnDataLinking()
    ↓
Identify changed column:
  - AM/PM column → HandleAmPmReorder()
  - Hour column → HandleHour12Change()
  - Minute column → HandleMinColumnChange()
  - Second column → HandleSecColumnChange()
    ↓
Update selectedTime_
    ↓
Adjust time range:
  LimitSelectedTimeInRange()
    ↓
FireChangeEvent() → Trigger onChange event
```

## Critical Technical Points

### 1. 12/24-Hour Format Switch

```cpp
void TimePickerRowPattern::SetHour24(bool value) {
    if (hour24_ == value) {
        return;  // No change
    }

    hour24_ = value;

    // Clear hour column options
    ClearOptionsHour();

    // Rebuild hour column
    HandleHourColumnBuildingRange(selectedTime_);

    // Add or remove AM/PM column
    CreateOrDeleteAmPmNode();
}
```

### 2. AM/PM Judgment

```cpp
bool TimePickerRowPattern::IsAmHour(uint32_t hourOf24) const {
    // Judge if 24-hour format hour is AM
    return hourOf24 < 12;
}

uint32_t TimePickerRowPattern::GetAmPmHour(uint32_t hourOf24) const {
    // Convert 24-hour to 12-hour
    if (hourOf24 == 0) {
        return 12;  // 0 hour → 12 AM
    }
    return hourOf24 > 12 ? hourOf24 - 12 : hourOf24;
}

uint32_t TimePickerRowPattern::GetHourFromAmPm(bool isAm, uint32_t amPmhour) const {
    // Convert from AM/PM and 12-hour to 24-hour
    if (isAm) {
        return amPmhour == 12 ? 0 : amPmhour;
    } else {
        return amPmhour == 12 ? 12 : amPmhour + 12;
    }
}
```

### 3. Time Range Constraints

```cpp
PickerTime TimePickerRowPattern::AdjustTime(const PickerTime& time) {
    PickerTime adjustedTime = time;

    // Limit hour
    if (adjustedTime.GetHour() < startTime_.GetHour()) {
        adjustedTime.SetHour(startTime_.GetHour());
    } else if (adjustedTime.GetHour() > endTime_.GetHour()) {
        adjustedTime.SetHour(endTime_.GetHour());
    }

    // Limit minute
    if (adjustedTime.GetMinute() < startTime_.GetMinute()) {
        adjustedTime.SetMinute(startTime_.GetMinute());
    } else if (adjustedTime.GetMinute() > endTime_.GetMinute()) {
        adjustedTime.SetMinute(endTime_.GetMinute());
    }

    // Limit second
    if (adjustedTime.GetSecond() < startTime_.GetSecond()) {
        adjustedTime.SetSecond(startTime_.GetSecond());
    } else if (adjustedTime.GetSecond() > endTime_.GetSecond()) {
        adjustedTime.SetSecond(endTime_.GetSecond());
    }

    return adjustedTime;
}
```

### 4. Leading Zero Handling

```cpp
std::string TimePickerRowPattern::AddZeroPrefix(const std::string& value) const {
    // Add leading zero for single digit
    if (value.length() == 1) {
        return "0" + value;
    }
    return value;
}

std::string TimePickerRowPattern::GetHourColumnFormatString(uint32_t hour) {
    bool hasZeroPrefix = (prefixHour_ == ZeroPrefixType::AUTO) ||
                         (prefixHour_ == ZeroPrefixType::ALWAYS);

    if (hasZeroPrefix && hour < 10) {
        return AddZeroPrefix(std::to_string(hour));
    }
    return std::to_string(hour);
}
```

### 5. Language and Locale Support

```cpp
void TimePickerRowPattern::UpdateLanguageAndAmPmTimeOrder() {
    // Get current language
    language_ = AceApplicationInfo::GetInstance().GetLanguage();

    // Get AM/PM time order (some languages have PM first)
    amPmTimeOrder_ = DateTimeSequence::GetAmPmTimeOrder(language_).amPmTimeOrder;

    // Update layout direction (Arabic RTL)
    if (language_ == "ar" && layoutProperty->GetLayoutDirection() != TextDirection::RTL) {
        layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
        isDirectionSetByAr_ = true;
    }

    // Get localized AM/PM text
    vecAmPm_ = Localization::GetInstance()->GetAmPmStrings();
}
```

## Property System

### TimePickerLayoutProperty

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| **selected** | PickerTime | Current() | Selected time |
| **start** | PickerTime | 00:00:00 | Start time |
| **end** | PickerTime | 23:59:59 | End time |
| **hour24** | bool | System setting | Whether 24-hour format |
| **hasSecond** | bool | false | Whether show seconds |
| **loop** | bool | true | Whether loop |
| **prefixHour** | ZeroPrefixType | AUTO | Hour leading zero |
| **prefixMinute** | ZeroPrefixType | AUTO | Minute leading zero |
| **prefixSecond** | ZeroPrefixType | AUTO | Second leading zero |

### ZeroPrefixType

```cpp
enum class ZeroPrefixType {
    AUTO,      // Auto judge (add zero for single digit)
    ALWAYS,    // Always add leading zero
    NEVER,     // Never add leading zero
};
```

## Event System

### Event Types

**onChange** - Time change:
```cpp
void TimePickerRowPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<TimePickerEventHub>();
    auto onChange = eventHub->GetChangeEvent();

    if (onChange) {
        auto info = GetSelectedObject(false);
        onChange(info);  // Trigger ArkTS onChange callback
    }
}
```

**onEnterSelectedArea** - Enter selected area:
```cpp
void TimePickerRowPattern::FireEnterSelectedAreaEvent(bool refresh) {
    if (enterSelectedAreaEventCallback_) {
        enterSelectedAreaEventCallback_(refresh);
    }
}
```

## 12/24-Hour Format

### Switch Implementation

```cpp
void TimePickerRowPattern::SetHour24(bool value) {
    hour24_ = value;

    if (value) {
        // Switch to 24-hour format
        // 1. Remove AM/PM column
        RemoveAmPmNode();

        // 2. Rebuild hour column (0-23)
        ClearOptionsHour();
        HandleHour24BuildTimeRange();

        // 3. Convert current time
        uint32_t hour24 = GetHourFromAmPm(currentIsAm_, currentAmPmHour_);
        selectedTime_.SetHour(hour24);
    } else {
        // Switch to 12-hour format
        // 1. Add AM/PM column
        CreateAmPmNode();

        // 2. Rebuild hour column (1-12)
        ClearOptionsHour();
        HandleHour12BuildTimeRange();

        // 3. Convert current time
        bool isAm = IsAmHour(selectedTime_.GetHour());
        uint32_t amPmHour = GetAmPmHour(selectedTime_.GetHour());
        selectedTime_.SetHour(amPmHour);
    }
}
```

### Hour Column Options

```cpp
// 24-hour format
void TimePickerRowPattern::HandleHour24BuildTimeRange() {
    auto hourColumn = allChildNode_["hour"];
    std::unordered_map<uint32_t, std::string> hourOptions;

    for (uint32_t hour = 0; hour < 24; ++hour) {
        std::string hourStr = GetHourColumnFormatString(hour);
        hourOptions[hour] = hourStr;
    }

    options_[hourColumn] = hourOptions;
    optionsTotalCount_[hourColumn] = 24;
}

// 12-hour format
void TimePickerRowPattern::HandleHour12BuildTimeRange() {
    auto hourColumn = allChildNode_["hour"];
    std::unordered_map<uint32_t, std::string> hourOptions;

    for (uint32_t hour = 1; hour <= 12; ++hour) {
        std::string hourStr = GetHourColumnFormatString(hour);
        hourOptions[hour - 1] = hourStr;  // Index starts from 0
    }

    options_[hourColumn] = hourOptions;
    optionsTotalCount_[hourColumn] = 12;
}
```

## AM/PM Handling

### AM/PM Text Retrieval

```cpp
std::string TimePickerRowPattern::GetAmFormatString() const {
    return vecAmPm_[0];  // "AM" or localized text
}

std::string TimePickerRowPattern::GetPmFormatString() const {
    return vecAmPm_[1];  // "PM" or localized text
}
```

### AM/PM Column Building

```cpp
void TimePickerRowPattern::HandleAmPmColumnBuilding(const PickerTime& value) {
    auto amPmColumn = allChildNode_["ampm"];
    std::unordered_map<uint32_t, std::string> amPmOptions;

    amPmOptions[0] = GetAmFormatString();
    amPmOptions[1] = GetPmFormatString();

    options_[amPmColumn] = amPmOptions;
    optionsTotalCount_[amPmColumn] = 2;

    // Set current selected
    bool isAm = IsAmHour(value.GetHour());
    SetColumnSelected(amPmColumn, isAm ? 0 : 1);
}
```

### AM/PM Column Change Handling

```cpp
void TimePickerRowPattern::HandleAmPmReorder() {
    auto amPmColumn = allChildNode_["ampm"];
    auto amPmPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    uint32_t amPmIndex = amPmPattern->GetSelected();

    bool isAm = (amPmIndex == 0);

    // Convert current hour
    uint32_t currentHour = selectedTime_.GetHour();

    if (isAm && currentHour >= 12) {
        // PM → AM: 13-23 → 1-11
        selectedTime_.SetHour(currentHour - 12);
    } else if (!isAm && currentHour < 12) {
        // AM → PM: 1-11 → 13-23
        selectedTime_.SetHour(currentHour + 12);
    }

    // Trigger change event
    FireChangeEvent(true);
}
```

## Best Practices

### Basic Usage

```typescript
// 1. Basic time selection
TimePicker({
  selected: new Time('2024-01-01 14:30:00')
})
  .onChange((value: string) => {
    console.log('Selected:', value);  // "14:30:00"
  })

// 2. Set time range
TimePicker()
  .start(new Time('08:00:00'))
  .end(new Time('18:00:00'))

// 3. 24-hour format
TimePicker()
  .hour24(true)

// 4. No seconds
TimePicker()
  .hasSecond(false)
```

### Leading Zero Configuration

```typescript
// Auto add leading zero (single digit adds zero)
TimePicker()
  .prefixHour(ZeroPrefixType.AUTO)
  .prefixMinute(ZeroPrefixType.AUTO)
  .prefixSecond(ZeroPrefixType.AUTO)

// Always add leading zero
TimePicker()
  .prefixHour(ZeroPrefixType.ALWAYS)

// Never add leading zero
TimePicker()
  .prefixHour(ZeroPrefixType.NEVER)
```

## Common Issues

| Symptom | Possible Cause | Solution |
|---------|----------------|----------|
| Hour display wrong | hour24 config error | Check hour24 property |
| AM/PM incorrect | Language config error | Check system language setting |
| Time cannot select | Out of range | Check start/end settings |
| Column linkage fails | Column ID mismatch | Check column node IDs |

## Related Directories

```
frameworks/core/components_ng/pattern/time_picker/
├── timepicker_row_pattern.h/cpp                 # Main logic
├── timepicker_column_pattern.h/cpp              # Column pattern
├── timepicker_layout_property.h                  # Layout properties
├── timepicker_event_hub.h                        # Event handling
├── timepicker_paint_method.h/cpp                  # Paint method
├── timepicker_column_layout_algorithm.h/cpp       # Column layout algorithm
├── timepicker_row_accessibility_property.h/cpp    # Accessibility properties
└── timepicker_dialog_view.h/cpp                   # Dialog view
```

## Key Takeaways

1. **12/24-Hour Support**: Support both 12-hour (AM/PM) and 24-hour format with dynamic switching
2. **Smart Linkage**: Hour/minute/second three columns intelligent linkage update
3. **Time Range**: Flexible start/end time configuration
4. **Leading Zero**: Support auto/always/never three leading zero modes
5. **AM/PM Handling**: Auto judge AM/PM, support column switching
6. **Language Support**: Support multi-language and RTL layout
7. **Event Callbacks**: onChange/onEnterSelectedArea complete support
8. **Accessibility**: Complete keyboard navigation and focus management
