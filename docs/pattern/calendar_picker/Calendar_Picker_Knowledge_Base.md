# ArkUI CalendarPicker 组件完整知识库

> **版本**: 1.0
> **更新时间**: 2026-02-02
> **基于**: OpenHarmony ace_engine (master 分支)

---

## 目录

1. [架构概述](#1-架构概述)
2. [核心类详解](#2-核心类详解)
3. [完整交互流程](#3-完整交互流程)
4. [关键技术点](#4-关键技术点)
5. [属性系统](#5-属性系统)
6. [事件系统](#6-事件系统)
7. [对话框系统](#7-对话框系统)
8. [无障碍支持](#8-无障碍支持)
9. [最佳实践](#9-最佳实践)
10. [问题排查](#10-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

CalendarPicker 组件实现了一个日期选择入口，采用 4 层架构：

```
ArkTS 前端
    ↓
桥接层 (CalendarModifier) - 属性解析和应用
    ↓
模式层 (CalendarPickerPattern) - 业务逻辑和状态管理
    ↓
对话框层 (CalendarDialogPattern) - 日历弹窗
    ↓
日历组件 (Calendar) - 日历视图
```

**设计原则**：
- **入口模式**: 轻量级入口，点击后弹出完整日历对话框
- **边框对齐**: 支持对话框边缘对齐 (START/CENTER/END)
- **键盘支持**: 完整的键盘导航和数字输入
- **日期范围**: 灵活的起始/结束日期配置

### 1.2 组件结构

```
CalendarPicker (入口组件)
├── 文本区域 (年/月/日)
├── 加减按钮
└── 点击事件 → 弹出 CalendarDialog
```

---

## 2. 核心类详解

### 2.1 CalendarPickerPattern

**职责**：
- 管理日期数据状态
- 处理键盘输入
- 处理鼠标点击和悬停
- 管理对话框弹出

**关键成员变量**：
```cpp
CalendarSettingData calendarData_;           // 日历数据
CalendarPickerSelectedType selected_;        // 当前选中类型 (年/月/日)
CalendarEdgeAlign align_;                    // 对齐方式
DimensionOffset offset_;                     // 对话框偏移

int32_t yearIndex_ = 0;                      // 文本索引
int32_t monthIndex_ = 2;
int32_t dayIndex_ = 4;

bool isDialogShow_ = false;                  // 对话框显示状态
bool isKeyWaiting_ = false;                  // 等待键盘输入状态
bool isMarkToday_ = false;                   // 是否标记今天

uint32_t yearEnterCount_ = 0;                // 年份输入计数
uint32_t monthPrefixZeroCount_ = 0;          // 月份前导零计数
uint32_t dayPrefixZeroCount_ = 0;            // 日期前导零计数
```

**关键方法**：

- **OnModifyDone()**: 初始化组件
  ```cpp
  void CalendarPickerPattern::OnModifyDone() {
      LinearLayoutPattern::OnModifyDone();

      // 初始化日期索引
      InitDateIndex();

      // 初始化事件
      InitClickEvent();
      InitOnKeyEvent();
      InitOnHoverEvent();

      // 更新样式
      FlushTextStyle();
      UpdateEdgeAlign();
  }
  ```

- **HandleClickEvent()**: 处理点击事件
  ```cpp
  void CalendarPickerPattern::HandleClickEvent(const Offset& globalLocation) {
      // 检查点击区域
      CalendarPickerSelectedType type = CheckRegion(globalLocation);

      switch (type) {
          case CalendarPickerSelectedType::YEAR:
          case CalendarPickerSelectedType::MONTH:
          case CalendarPickerSelectedType::DAY:
              SetSelectedType(type);
              ShowDialog();
              break;

          case CalendarPickerSelectedType::ADDBTN:
              HandleAddButtonClick();
              break;

          case CalendarPickerSelectedType::SUBBTN:
              HandleSubButtonClick();
              break;

          default:
              break;
      }
  }
  ```

- **HandleNumberKeyEvent()**: 处理数字键输入
  ```cpp
  bool CalendarPickerPattern::HandleNumberKeyEvent(const KeyEvent& event) {
      uint32_t number = event.GetKeyCode() - KeyCode::KEY_0;

      switch (selected_) {
          case CalendarPickerSelectedType::YEAR:
              return HandleYearKeyEvent(number);
          case CalendarPickerSelectedType::MONTH:
              return HandleMonthKeyEvent(number);
          case CalendarPickerSelectedType::DAY:
              return HandleDayKeyEvent(number);
          default:
              return false;
      }
  }
  ```

- **HandleYearKeyEvent()**: 年份输入处理
  ```cpp
  bool CalendarPickerPattern::HandleYearKeyEvent(uint32_t number) {
      auto& date = calendarData_.selectedDate;

      return HandleYearKeyWaitingEvent(number,
          [this, &date]() {  // task
              yearEnterCount_++;
              auto year = date.GetYear();

              // 构建新年份
              if (yearEnterCount_ < 4) {
                  year = year * 10 + number;
              } else {
                  year = (year / 1000) * 1000 + number;
              }

              date.SetYear(year);
              UpdateEntryButtonColor();
          },
          [this, &date]() {  // zeroStartTask
              yearPrefixZeroCount_++;
              if (yearPrefixZeroCount_ >= 2) {
                  // 00xx → 2000 + xx
                  yearEnterCount_ = 0;
                  yearPrefixZeroCount_ = 0;
                  isKeyWaiting_ = false;
              }
          }
      );
  }
  ```

- **HandleAddButtonClick()**: 加按钮处理
  ```cpp
  void CalendarPickerPattern::HandleAddButtonClick() {
      auto& date = calendarData_.selectedDate;

      switch (selected_) {
          case CalendarPickerSelectedType::YEAR:
              date.AddYears(1);
              break;
          case CalendarPickerSelectedType::MONTH:
              date.AddMonths(1);
              // 检查是否超出范围
              AdjustSolarDate(date, calendarData_.startDate, calendarData_.endDate);
              break;
          case CalendarPickerSelectedType::DAY:
              date.AddDays(1);
              AdjustSolarDate(date, calendarData_.startDate, calendarData_.endDate);
              break;
          default:
              break;
      }

      OnValueChange();
      UpdateEntryButtonColor();
  }
  ```

### 2.2 CalendarSettingData

```cpp
struct CalendarSettingData {
    PickerDate selectedDate;        // 当前选中日期
    PickerDate startDate;           // 起始日期
    PickerDate endDate;             // 结束日期
    std::optional<Dimension> dayRadius;  // 日期圆角半径
    RefPtr<ResourceObject> dayRadiusResObj;
    WeakPtr<FrameNode> entryNode;   // 入口节点
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;  // 禁用日期范围
    bool markToday;                 // 是否标记今天
};
```

### 2.3 CalendarPickerSelectedType

```cpp
enum class CalendarPickerSelectedType {
    YEAR = 0,        // 年份区域
    MONTH,           // 月份区域
    DAY,             // 日期区域
    ADDBTN,          // 加按钮
    SUBBTN,          // 减按钮
    OTHER,           // 其他区域
};
```

---

## 3. 完整交互流程

### 3.1 点击弹出对话框

```
用户点击年/月/日文本区域
    ↓
HandleClickEvent(globalLocation)
    ↓
CheckRegion(globalLocation) → 确定点击区域
    ↓
SetSelectedType(type) → 设置当前选中类型
    ↓
ShowDialog() → 弹出日历对话框
    ↓
创建 CalendarDialogPattern
    ↓
设置初始选中日期
    ↓
显示对话框
```

### 3.2 键盘数字输入

```
用户按数字键 (0-9)
    ↓
HandleNumberKeyEvent(event)
    ↓
根据 selected_ 分发:
  - YEAR → HandleYearKeyEvent()
  - MONTH → HandleMonthKeyEvent()
  - DAY → HandleDayKeyEvent()
    ↓
HandleYearKeyWaitingEvent()
    ↓
累加数字构建年份/月份/日期
    ↓
达到长度后自动完成
    ↓
OnValueChange() → 触发 onChange 事件
```

### 3.3 加减按钮操作

```
用户点击加/减按钮
    ↓
HandleAddButtonClick() / HandleSubButtonClick()
    ↓
根据 selected_ 调整日期:
  - YEAR: ±1 年
  - MONTH: ±1 月 (带范围检查)
  - DAY: ±1 日 (带范围检查)
    ↓
AdjustSolarDate() → 调整到有效范围
    ↓
OnValueChange() → 触发 onChange 事件
    ↓
UpdateEntryButtonColor() → 更新按钮状态
```

---

## 4. 关键技术点

### 4.1 日期范围限制

```cpp
void CalendarPickerPattern::SetCalendarData(const CalendarSettingData& data) {
    CalendarSettingData settingData = data;

    // 自动调整选中日期到有效范围
    settingData.selectedDate = PickerDate::AdjustDateToRange(
        data.selectedDate,
        data.startDate,
        data.endDate
    );

    calendarData_ = settingData;
}

void AdjustSolarDate(PickerDate& date, const PickerDate& start, const PickerDate& end) {
    if (SolarDateCompare(date, start) < 0) {
        date = start;  // 小于起始日期
        return;
    }
    if (SolarDateCompare(date, end) > 0) {
        date = end;    // 大于结束日期
    }
}
```

### 4.2 禁用日期范围

```cpp
std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;

// 检查日期是否被禁用
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

### 4.3 对话框边缘对齐

```cpp
enum class CalendarEdgeAlign {
    EDGE_ALIGN_START = 0,   // 左对齐
    EDGE_ALIGN_CENTER,      // 居中
    EDGE_ALIGN_END,         // 右对齐
};

OffsetF CalendarPickerPattern::CalculateDialogOffset() {
    auto host = GetHost();
    auto geometryNode = host->GetGeometryNode();
    auto offset = geometryNode->GetOffset();

    // 根据对齐方式计算偏移
    switch (align_) {
        case CalendarEdgeAlign::EDGE_ALIGN_START:
            // 左对齐，无额外偏移
            break;
        case CalendarEdgeAlign::EDGE_ALIGN_CENTER:
            // 居中对齐
            offset += DimensionOffset(dialogWidth / 2, 0);
            break;
        case CalendarEdgeAlign::EDGE_ALIGN_END:
            // 右对齐
            offset += DimensionOffset(dialogWidth, 0);
            break;
    }

    return offset;
}
```

### 4.4 悬停效果

```cpp
void CalendarPickerPattern::HandleTextHoverEvent(bool state, int32_t index) {
    auto host = GetHost();
    auto textNode = DynamicCast<FrameNode>(host->GetChildAtIndex(index));

    // 更新悬停样式
    if (state) {
        // 悬停状态
        textNode->GetRenderContext()->UpdateBackgroundColor(hoverColor);
    } else {
        // 恢复正常状态
        textNode->GetRenderContext()->UpdateBackgroundColor(normalColor);
    }
}

void CalendarPickerPattern::InitOnHoverEvent() {
    auto hub = GetHost()->GetEventHub<EventHub>();
    auto hoverListener = [weak = WeakClaim(this)](bool state, const Offset& globalLocation) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);

        // 判断悬停区域
        auto type = pattern->CheckRegion(globalLocation);
        if (type == CalendarPickerSelectedType::YEAR) {
            pattern->HandleTextHoverEvent(state, pattern->yearIndex_);
        }
        // ... 其他区域
    };

    hub->SetOnHoverEvent(hoverListener);
}
```

### 4.5 按钮状态更新

```cpp
void CalendarPickerPattern::UpdateEntryButtonColor() {
    auto host = GetHost();

    // 获取加/减按钮
    auto addButton = DynamicCast<FrameNode>(host->GetChildAtIndex(addId_));
    auto subButton = DynamicCast<FrameNode>(host->GetChildAtIndex(subId_));

    // 检查是否可以继续加减
    bool canAdd = IsAddOrSubButtonEnable(ADD_BUTTON_INDEX);
    bool canSub = IsAddOrSubButtonEnable(SUB_BUTTON_INDEX);

    // 更新按钮颜色和状态
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
        // 检查是否可以增加
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
        // 检查是否可以减少
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

---

## 5. 属性系统

### 5.1 布局属性 (CalendarPickerLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **calendarData** | CalendarSettingData | - | 日历数据 (选中日期、起始/结束日期等) |
| **align** | CalendarEdgeAlign | END | 对话框对齐方式 |
| **offset** | DimensionOffset | - | 对话框偏移量 |
| **textStyle** | PickerTextStyle | - | 文本样式 |
| **markToday** | bool | false | 是否标记今天 |

### 5.2 CalendarSettingData 属性

| 属性 | 类型 | 说明 |
|------|------|------|
| **selectedDate** | PickerDate | 当前选中日期 |
| **startDate** | PickerDate | 起始日期 |
| **endDate** | PickerDate | 结束日期 |
| **dayRadius** | Dimension | 日期圆角半径 |
| **disabledDateRange** | vector\<pair\> | 禁用日期范围列表 |
| **markToday** | bool | 是否标记今天 |

---

## 6. 事件系统

### 6.1 事件类型

**onChange** - 日期改变：
```cpp
void CalendarPickerPattern::OnValueChange() {
    auto eventHub = GetEventHub<CalendarPickerEventHub>();
    auto onChangeEvent = eventHub->GetChangeEvent();

    if (onChangeEvent) {
        auto info = GetEntryDateInfo();
        onChangeEvent(info);  // 触发 ArkTS onChange 回调
    }
}
```

### 6.2 事件数据格式

```cpp
std::string CalendarPickerPattern::GetEntryDateInfo() {
    // 格式: "year-month-day"
    auto& date = calendarData_.selectedDate;
    return std::to_string(date.GetYear()) + "-" +
           std::to_string(date.GetMonth()) + "-" +
           std::to_string(date.GetDay());
}
```

---

## 7. 对话框系统

### 7.1 对话框弹出

```cpp
void CalendarPickerPattern::ShowDialog() {
    if (isDialogShow_) {
        return;  // 已显示，不重复弹出
    }

    // 准备对话框属性
    CalendarPickerOption option;
    option.data = calendarData_;
    option.alignType = align_;
    option.offset = offset_;
    option.textStyle = GetTextStyle();

    // 创建并显示对话框
    CalendarDialogView::Show(option);
    isDialogShow_ = true;
}
```

### 7.2 对话框关闭

```cpp
void CalendarPickerPattern::SetDialogShow(bool flag) {
    isDialogShow_ = flag;

    if (!flag) {
        // 对话框关闭，可能日期已改变
        OnValueChange();
        UpdateEntryButtonColor();
    }
}
```

---

## 8. 无障碍支持

### 8.1 焦点管理

```cpp
FocusPattern CalendarPickerPattern::GetFocusPattern() const {
    return {
        FocusType::NODE,          // 节点级焦点
        true,                      // 可聚焦
        FocusStyleType::CUSTOM_REGION  // 自定义焦点区域
    };
}
```

### 8.2 键盘导航

```cpp
bool CalendarPickerPattern::HandleKeyEvent(const KeyEvent& event) {
    switch (event.GetKeyCode()) {
        case KeyCode::KEY_UP:
            // 向上键 → 日期 +1
            HandleAddButtonClick();
            return true;
        case KeyCode::KEY_DOWN:
            // 向下键 → 日期 -1
            HandleSubButtonClick();
            return true;
        case KeyCode::KEY_TAB:
            // Tab 键 → 切换选中类型
            SwitchSelectedType();
            return true;
        case KeyCode::KEY_ENTER:
            // 回车键 → 弹出对话框
            ShowDialog();
            return true;
        default:
            // 数字键 → 输入数字
            if (event.GetKeyCode() >= KeyCode::KEY_0 &&
                event.GetKeyCode() <= KeyCode::KEY_9) {
                return HandleNumberKeyEvent(event);
            }
            return false;
    }
}
```

---

## 9. 最佳实践

### 9.1 基本使用

**推荐做法**：
```typescript
// 1. 设置合理的日期范围
CalendarPicker({
  start: new Date('1900-1-1'),
  end: new Date('2100-12-31'),
  selected: new Date('2024-1-1')
})
  .onChange((date: string) => {
    console.log('Selected:', date);  // "2024-1-1"
  })

// 2. 标记今天
CalendarPicker({
  markToday: true
})

// 3. 禁用特定日期范围
CalendarPicker({
  disabledDateRange: [
    { start: new Date('2024-1-1'), end: new Date('2024-1-7') }
  ]
})
```

### 9.2 对话框配置

```typescript
// 设置对话框对齐
CalendarPicker()
  .edgeAlign(CalendarEdgeAlign.START)    // 左对齐
  // .edgeAlign(CalendarEdgeAlign.CENTER) // 居中
  // .edgeAlign(CalendarEdgeAlign.END)    // 右对齐

// 设置对话框偏移
CalendarPicker()
  .dialogOffset({ dx: 10, dy: 20 })
```

### 9.3 样式定制

```typescript
// 自定义文本样式
CalendarPicker()
  .textStyle({
    color: Color.Blue,
    fontSize: 16,
    fontWeight: FontWeight.Bold
  })
```

---

## 10. 问题排查

### 10.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 日期无法修改 | 超出范围限制 | 检查 startDate/endDate 设置 |
| 按钮禁用 | 达到边界 | 调整日期范围 |
| 对话框位置错误 | 对齐方式设置错误 | 调整 edgeAlign |
| 输入无响应 | 未选中区域 | 点击年/月/日区域先选中 |

### 10.2 调试工具

**日志输出**：
```bash
# 查看日历相关日志
hilog -T ArkUI | grep -i calendar
```

**状态检查**：
```cpp
ToJsonValue()  // 输出当前状态
// selectedDate: "2024-1-1"
// startDate: "1900-1-31"
// endDate: "2100-12-31"
// align: EDGE_ALIGN_END
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/calendar_picker/
├── calendar_picker_pattern.h/cpp             # 主要逻辑
├── calendar_picker_layout_property.h         # 布局属性
├── calendar_picker_layout_algorithm.h/cpp    # 布局算法
├── calendar_picker_event_hub.h               # 事件处理
├── calendar_dialog_pattern.h/cpp            # 对话框模式
├── calendar_dialog_layout_algorithm.h/cpp   # 对话框布局
├── calendar_type_define.h                   # 类型定义
└── bridge/
    ├── calendar_picker_static_modifier.cpp  # 静态修饰符
    └── calendar_picker_dynamic_module.cpp   # 动态模块
```

---

## 关键要点总结

1. **入口模式**: 轻量级入口，点击后弹出完整日历对话框
2. **日期范围**: 支持灵活的起始/结束日期配置，自动调整
3. **键盘支持**: 完整的数字输入和方向键导航
4. **边缘对齐**: 支持对话框左/中/右对齐
5. **禁用日期**: 支持配置禁用日期范围
6. **悬停效果**: 支持鼠标悬停高亮显示
7. **按钮状态**: 根据日期范围自动启用/禁用加减按钮
8. **无障碍**: 完整的焦点管理和键盘导航支持

---
