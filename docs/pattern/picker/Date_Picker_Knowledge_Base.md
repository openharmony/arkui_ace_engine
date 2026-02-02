# ArkUI DatePicker 组件完整知识库

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
7. [阴阳历转换](#7-阴阳历转换)
8. [联动逻辑](#8-联动逻辑)
9. [最佳实践](#9-最佳实践)
10. [问题排查](#10-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

DatePicker 组件实现了一个完整的日期选择器，支持公历和农历，采用 4 层架构：

```
ArkTS 前端
    ↓
桥接层 (DatePickerModifier) - 属性解析和应用
    ↓
模式层 (DatePickerPattern) - 业务逻辑和联动控制
    ↓
列模式层 (DatePickerColumnPattern) - 单列滚动逻辑
    ↓
滚动层 (ContainerPicker) - 滚动和吸附
```

**设计原则**：
- **阴阳历支持**: 同时支持公历 (Solar) 和农历 (Lunar)
- **智能联动**: 年/月/日三列智能联动
- **范围限制**: 灵活的起始/结束日期配置
- **多种模式**: DATE/TIME/MONTH_DAYS 等多种显示模式

### 1.2 显示模式

| 模式 | 说明 | 列结构 |
|------|------|--------|
| **DATE** | 年月日 | 年 | 月 | 日 |
| **TIME** | 时分秒 | 时 | 分 | 秒 |
| **MONTH_DAYS** | 月日 | 月 | 日 |
| **YEAR_MONTH** | 年月 | 年 | 月 |

### 1.3 阴阳历支持

```
公历 (Solar)
    ↓ SolarToLunar()
农历 (Lunar)
    ↓ LunarToSolar()
公历 (Solar)
```

---

## 2. 核心类详解

### 2.1 DatePickerPattern

**职责**：
- 管理日期数据状态
- 处理年月日联动
- 执行阴阳历转换
- 管理列创建和更新

**关键成员变量**：
```cpp
// 日期数据
PickerDate selectedDate_;         // 当前选中日期 (公历)
LunarDate selectedLunar_;         // 当前选中日期 (农历)
PickerDate startDateSolar_;       // 起始日期 (公历)
LunarDate startDateLunar_;        // 起始日期 (农历)
PickerDate endDateSolar_;         // 结束日期 (公历)
LunarDate endDateLunar_;          // 结束日期 (农历)

// 模式和配置
DatePickerMode datePickerMode_;   // 选择器模式
bool lunar_;                      // 是否显示农历
bool showMonthDays_;              // 是否显示月日模式
bool isLoop_;                     // 是否循环
std::string dateOrder_;           // 日期顺序

// 列数据
std::map<WeakPtr<FrameNode>, std::vector<PickerDateF>> options_;
std::vector<WeakPtr<FrameNode>> datePickerColumns_;

// 节点 ID
std::optional<int32_t> yearId_;
std::optional<int32_t> monthId_;
std::optional<int32_t> dayId_;
std::optional<int32_t> monthDaysId_;

// 事件
EventMarker OnDialogAccept_;
EventMarker OnDialogCancel_;
EventMarker OnDialogChange_;
```

**关键方法**：

- **OnModifyDone()**: 初始化组件
  ```cpp
  void DatePickerPattern::OnModifyDone() {
      LinearLayoutPattern::OnModifyDone();

      // 构建列
      if (datePickerMode_ == DatePickerMode::DATE) {
          if (lunar_) {
              LunarColumnsBuilding(selectedLunar_);
          } else {
              SolarColumnsBuilding(selectedDate_);
          }
      } else if (datePickerMode_ == DatePickerMode::MONTH_DAYS) {
          if (lunar_) {
              LunarMonthDaysColumnBuilding(selectedLunar_);
          } else {
              SolarMonthDaysColumnsBuilding(selectedDate_);
          }
      }

      // 初始化事件
      InitOnKeyEvent(GetFocusHub());
      InitFocusEvent();
  }
  ```

- **SolarColumnsBuilding()**: 构建公历年月日列
  ```cpp
  void DatePickerPattern::SolarColumnsBuilding(const PickerDate& current) {
      // 获取或创建年列
      auto yearColumn = GetColumnNode(yearId_);
      FillSolarYearOptions(current, yearColumn);

      // 获取或创建月列
      auto monthColumn = GetColumnNode(monthId_);
      FillSolarMonthOptions(current, monthColumn);

      // 获取或创建日列
      auto dayColumn = GetColumnNode(dayId_);
      FillSolarDayOptions(current, dayColumn);

      // 添加到布局
      OrderAllChildNode(yearColumn, monthColumn, dayColumn);
  }
  ```

- **HandleYearChange()**: 处理年份变化
  ```cpp
  void DatePickerPattern::HandleYearChange(bool isAdd, uint32_t index,
                                           std::vector<RefPtr<FrameNode>>& resultTags) {
      auto yearColumn = DynamicCast<DatePickerColumnPattern>(resultTags[0]->GetPattern());

      // 获取新年份
      auto yearValue = yearColumn->GetOptionValue(index);
      PickerDate newDate = selectedDate_;
      newDate.SetYear(yearValue.GetYear());

      // 调整到有效范围
      AdjustSolarDate(newDate, startDateSolar_, endDateSolar_);

      // 更新年份
      selectedDate_ = newDate;
      selectedLunar_ = SolarToLunar(selectedDate_);

      // 重新构建月和日列 (因为天数可能变化)
      FlushMonthDaysColumn();

      // 触发变化事件
      FireChangeEvent(true);
  }
  ```

- **HandleMonthChange()**: 处理月份变化
  ```cpp
  void DatePickerPattern::HandleMonthChange(bool isAdd, uint32_t index) {
      auto monthColumn = GetColumnNode(monthId_);
      auto monthValue = GetOptionValue(monthColumn, index);

      PickerDate newDate = selectedDate_;
      newDate.SetMonth(monthValue.GetMonth());

      // 调整到有效范围
      AdjustSolarDate(newDate, startDateSolar_, endDateSolar_);

      // 更新日期
      selectedDate_ = newDate;
      selectedLunar_ = SolarToLunar(selectedDate_);

      // 重新构建日列 (因为天数可能变化)
      FlushDayColumn();

      FireChangeEvent(true);
  }
  ```

- **OnDataLinking()**: 数据联动处理
  ```cpp
  void DatePickerPattern::OnDataLinking(
      const RefPtr<FrameNode>& tag, bool isAdd, uint32_t index,
      std::vector<RefPtr<FrameNode>>& resultTags)
  {
      // 判断变化的是哪一列
      if (tag->GetId() == GetYearId()) {
          HandleYearChange(isAdd, index, resultTags);
      } else if (tag->GetId() == GetMonthId()) {
          HandleSolarMonthChange(isAdd, index);
      } else if (tag->GetId() == GetDayId()) {
          HandleSolarDayChange(isAdd, index);
      }
  }
  ```

### 2.2 DatePickerColumnPattern

**职责**：
- 管理单列选项
- 处理列内滚动
- 触发联动事件

**关键方法**：
```cpp
class DatePickerColumnPattern : public Pattern {
public:
    void SetOptions(const std::vector<PickerDateF>& options);
    uint32_t GetSelected() const;
    PickerDateF GetOptionValue(uint32_t index);

    // 滚动回调
    void OnColumnChange(bool isAdd, uint32_t index, bool needNotify);
};
```

### 2.3 PickerDate / LunarDate

```cpp
struct PickerDate {
    int32_t year;
    int32_t month;   // 1-12
    int32_t day;     // 1-31

    static PickerDate Current();        // 当前日期
    void AddYears(int32_t years);
    void AddMonths(int32_t months);
    void AddDays(int32_t days);
};

struct LunarDate {
    int32_t year;
    int32_t month;   // 1-12
    int32_t day;     // 1-30
    bool isLeap;     // 是否闰月
};
```

---

## 3. 完整交互流程

### 3.1 列构建流程

```
OnModifyDone()
    ↓
根据模式 (DATE/TIME/MONTH_DAYS) 和历法 (Solar/Lunar)
    ↓
SolarColumnsBuilding() / LunarColumnsBuilding()
    ↓
为每列创建/获取节点:
  - 年列: FillSolarYearOptions()
  - 月列: FillSolarMonthOptions()
  - 日列: FillSolarDayOptions()
    ↓
填充选项数据:
  - 根据起始/结束日期生成有效范围
  - 设置当前选中值
    ↓
OrderAllChildNode() → 添加到布局树
```

### 3.2 滚动联动流程

```
用户滚动某一列
    ↓
DatePickerColumnPattern::OnColumnChange()
    ↓
DatePickerPattern::OnDataLinking()
    ↓
识别变化的列:
  - 年列 → HandleYearChange()
  - 月列 → HandleMonthChange()
  - 日列 → HandleDayChange()
    ↓
更新 selectedDate_ / selectedLunar_
    ↓
调整日期范围:
  AdjustSolarDate() / AdjustLunarDate()
    ↓
重新构建受影响的列:
  FlushMonthDaysColumn() / FlushDayColumn()
    ↓
FireChangeEvent() → 触发 onChange 事件
```

---

## 4. 关键技术点

### 4.1 阴阳历转换

```cpp
LunarDate DatePickerPattern::SolarToLunar(const PickerDate& date) const {
    // 使用日历算法库进行转换
    LunarDate lunar;

    // 1. 转换为农历年月日
    int32_t year = date.GetYear();
    int32_t month = date.GetMonth();
    int32_t day = date.GetDay();

    // 2. 调用底层转换 API
    CalendarConverter::SolarToLunar(year, month, day,
                                   lunar.year, lunar.month,
                                   lunar.day, lunar.isLeap);

    return lunar;
}

PickerDate DatePickerPattern::LunarToSolar(const LunarDate& date) const {
    PickerDate solar;

    // 调用底层转换 API
    CalendarConverter::LunarToSolar(date.year, date.month, date.day,
                                   date.isLeap,
                                   solar.year, solar.month, solar.day);

    return solar;
}
```

### 4.2 日期范围限制

```cpp
void DatePickerPattern::AdjustSolarDate(
    PickerDate& date,
    const PickerDate& start,
    const PickerDate& end) const
{
    if (SolarDateCompare(date, start) < 0) {
        date = start;  // 小于起始日期
        return;
    }
    if (SolarDateCompare(date, end) > 0) {
        date = end;    // 大于结束日期
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
    return 0;  // 相等
}
```

### 4.3 闰月处理

```cpp
uint32_t DatePickerPattern::GetLunarMaxDay(
    uint32_t year, uint32_t month, bool isLeap) const
{
    // 获取农历月份的最大天数
    uint32_t leapMonth = 0;
    GetLunarLeapMonth(year, leapMonth);

    if (isLeap && month != leapMonth) {
        // 非闰月
        return 0;
    }

    // 农历小月 29 天，大月 30 天
    if (IsLunarBigMonth(year, month)) {
        return 30;
    }
    return 29;
}

bool DatePickerPattern::GetLunarLeapMonth(
    uint32_t year, uint32_t& outLeapMonth) const
{
    // 查询该年的闰月
    return CalendarConverter::GetLeapMonth(year, outLeapMonth);
}
```

### 4.4 日期联动逻辑

```cpp
void DatePickerPattern::IncreaseLinkageYearMonth(PickerDate& date) {
    // 年/月增加时的联动逻辑
    if (date.GetMonth() == 12) {
        // 12 月 → 下一年 1 月
        date.SetYear(date.GetYear() + 1);
        date.SetMonth(1);
    } else {
        date.SetMonth(date.GetMonth() + 1);
    }

    // 检查日期是否超出范围
    AdjustSolarDate(date, startDateSolar_, endDateSolar_);

    // 调整日期 (如 1月31日 → 2月28日)
    while (date.GetDay() > GetMaxDay(date.GetYear(), date.GetMonth())) {
        date.SetDay(date.GetDay() - 1);
    }
}

void DatePickerPattern::ReduceLinkageYearMonth(PickerDate& date) {
    // 年/月减少时的联动逻辑
    if (date.GetMonth() == 1) {
        // 1 月 → 上一年 12 月
        date.SetYear(date.GetYear() - 1);
        date.SetMonth(12);
    } else {
        date.SetMonth(date.GetMonth() - 1);
    }

    AdjustSolarDate(date, startDateSolar_, endDateSolar_);

    // 调整日期
    while (date.GetDay() > GetMaxDay(date.GetYear(), date.GetMonth())) {
        date.SetDay(date.GetDay() - 1);
    }
}
```

### 4.5 选项填充

```cpp
void DatePickerPattern::FillSolarYearOptions(
    const PickerDate& current,
    RefPtr<FrameNode>& yearColumn)
{
    std::vector<PickerDateF> yearOptions;

    // 生成年份选项
    for (int32_t year = startDateSolar_.GetYear();
         year <= endDateSolar_.GetYear(); ++year) {
        PickerDateF dateValue;
        dateValue.SetYear(year);
        yearOptions.emplace_back(dateValue);
    }

    // 设置到列
    auto columnPattern = yearColumn->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetOptions(yearOptions);

    // 设置当前选中
    uint32_t selectedIndex = current.GetYear() - startDateSolar_.GetYear();
    columnPattern->SetSelected(selectedIndex);
}
```

---

## 5. 属性系统

### 5.1 布局属性 (DatePickerLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **start** | PickerDate | 1970-1-1 | 起始日期 |
| **end** | PickerDate | 2100-12-31 | 结束日期 |
| **selected** | PickerDate | Current() | 选中日期 |
| **lunar** | bool | false | 是否显示农历 |
| **mode** | DatePickerMode | DATE | 选择器模式 |
| **loop** | bool | true | 是否循环 |
| **showLunarSwitch** | bool | false | 是否显示农历切换 |
| **dateOrder** | string | "ydm" | 日期顺序 |

### 5.2 DatePickerMode

```cpp
enum class DatePickerMode {
    DATE,         // 年月日
    TIME,         // 时分秒
    MONTH_DAYS,   // 月日
    YEAR_MONTH    // 年月
};
```

---

## 6. 事件系统

### 6.1 事件类型

**onChange** - 日期改变：
```cpp
void DatePickerPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<DatePickerEventHub>();
    auto onChangeEvent = eventHub->GetChangeEvent();

    if (onChangeEvent) {
        auto info = GetSelectedObject(false);
        onChangeEvent(info);  // 触发 ArkTS onChange 回调
    }
}
```

**onAccept** - 确认按钮：
```cpp
void DatePickerPattern::SetDialogAcceptEvent(const EventMarker& value) {
    OnDialogAccept_ = value;
}
```

**onCancel** - 取消按钮：
```cpp
void DatePickerPattern::SetDialogCancelEvent(const EventMarker& value) {
    OnDialogCancel_ = value;
}
```

---

## 7. 阴阳历转换

### 7.1 转换流程

```
公历日期 (2024-1-1)
    ↓ SolarToLunar()
农历日期 (2023-十一月-二十)
    ↓ 用户滚动农历列
农历日期 (2023-十二月-初一)
    ↓ LunarToSolar()
公历日期 (2024-1-11)
```

### 7.2 农历显示格式

```cpp
std::string DatePickerPattern::GetMonthFormatString(
    uint32_t month, bool isLunar, bool isLeap) const
{
    if (isLunar) {
        // 农历月份: "正月", "二月", ..., "腊月"
        // 闰月: "闰正月", "闰二月", ...
        if (isLeap) {
            return GetLunarLeapMonth(month);
        }
        return GetLunarMonth(month);
    }
    // 公历月份: "1月", "2月", ..., "12月"
    return GetSolarMonth(month);
}
```

---

## 8. 联动逻辑

### 8.1 年月联动

```
年份变化 → 重新生成月份和日列
    ↓
月份变化 → 重新生成日列 (天数可能不同)
    ↓
日期变化 → 通常不联动其他列
```

### 8.2 特殊日期处理

```cpp
// 1月31日 → 滚动到2月 → 自动调整到2月28日/29日
void AdjustDayForMonthChange(PickerDate& date) {
    int32_t maxDay = GetMaxDay(date.GetYear(), date.GetMonth());
    if (date.GetDay() > maxDay) {
        date.SetDay(maxDay);
    }
}

// 闰年2月有29天，平年2月有28天
int32_t GetMaxDay(int32_t year, int32_t month) {
    if (month == 2) {
        return IsLeapYear(year) ? 29 : 28;
    }
    // 大月31天，小月30天
    static const int32_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}
```

---

## 9. 最佳实践

### 9.1 基本使用

**推荐做法**：
```typescript
// 1. 基本日期选择
DatePicker({
  start: new Date('2000-1-1'),
  end: new Date('2030-12-31'),
  selected: new Date('2024-1-1')
})
  .onChange((value: string) => {
    console.log('Selected:', value);  // "2024-1-1"
  })

// 2. 农历模式
DatePicker()
  .lunar(true)

// 3. 月日模式
DatePicker()
  .mode(DatePickerMode.MONTH_DAYS)
```

### 9.2 范围配置

```typescript
// 设置合理的日期范围
DatePicker()
  .start(new Date('1900-1-1'))
  .end(new Date('2100-12-31'))

// 限制选择范围
DatePicker()
  .start(new Date('2024-1-1'))
  .end(new Date('2024-12-31'))
```

---

## 10. 问题排查

### 10.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 日期无法选择 | 超出范围 | 检查 start/end 设置 |
| 月份显示错误 | 历法配置错误 | 检查 lunar 属性 |
| 日期联动失效 | 列ID不匹配 | 检查列节点ID |
| 农历显示异常 | 转换失败 | 检查日期有效性 |

### 10.2 调试工具

**日志输出**：
```bash
# 查看日期选择器相关日志
hilog -T ArkUI | grep -i datepicker
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/picker/
├── datepicker_pattern.h/cpp                 # 主要逻辑
├── datepicker_column_pattern.h/cpp          # 列模式
├── datepicker_layout_property.h             # 布局属性
├── datepicker_event_hub.h                  # 事件处理
├── datepicker_paint_method.h/cpp            # 绘制方法
├── date_time_animation_controller.h/cpp     # 动画控制
├── picker_data.h/cpp                        # 数据结构
├── picker_theme.h/cpp                       # 主题配置
└── picker_utils/                            # 工具类
    └── picker_column_pattern.h/cpp          # 列模式基类
```

---

## 关键要点总结

1. **阴阳历支持**: 同时支持公历和农历，自动转换
2. **智能联动**: 年/月/日三列智能联动更新
3. **多种模式**: DATE/TIME/MONTH_DAYS 等多种显示模式
4. **范围限制**: 灵活的起始/结束日期配置
5. **闰月处理**: 正确处理农历闰月和公历闰年
6. **日期调整**: 自动调整特殊日期 (如2月30日 → 2月28日)
7. **事件回调**: onChange/onAccept/onCancel 完整支持
8. **无障碍**: 完整的键盘导航和焦点管理

---
