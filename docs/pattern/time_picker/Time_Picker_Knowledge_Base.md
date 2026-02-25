# ArkUI TimePicker 组件完整知识库

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
7. [12/24小时制](#7-1224小时制)
8. [AM/PM 处理](#8-ampm-处理)
9. [最佳实践](#9-最佳实践)
10. [问题排查](#10-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

TimePicker 组件实现了一个完整的时间选择器，支持时、分、秒选择，采用 4 层架构：

```
ArkTS 前端
    ↓
桥接层 (TimePickerModifier) - 属性解析和应用
    ↓
行模式层 (TimePickerRowPattern) - 业务逻辑和多列管理
    ↓
列模式层 (TimePickerColumnPattern) - 单列滚动逻辑
    ↓
滚动层 (ContainerPicker) - 滚动和吸附
```

**设计原则**：
- **12/24小时制**: 同时支持 12 小时制（AM/PM）和 24 小时制
- **时间范围**: 灵活的起始/结束时间配置
- **智能联动**: 时/分/秒三列智能联动
- **多种模式**: HOUR/MINUTE/SECOND 等多种显示模式

### 1.2 显示模式

| 模式 | 说明 | 列结构 |
|------|------|--------|
| **HOUR** | 小时 | 时 |
| **HOUR_MINUTE** | 时分 | 时 | 分 |
| **HOUR_MINUTE_SECOND** | 时分秒 | 时 | 分 | 秒 |

### 1.3 12/24小时制

```
12 小时制:
  - AM (上午): 1-12 时
  - PM (下午): 1-12 时
  - 额外 AM/PM 列

24 小时制:
  - 直接: 0-23 时
  - 无需 AM/PM 列
```

---

## 2. 核心类详解

### 2.1 TimePickerRowPattern

**职责**：
- 管理时间数据状态
- 处理时分秒联动
- 管理 12/24 小时制切换
- 管理 AM/PM 列

**关键成员变量**：
```cpp
// 时间数据
PickerTime selectedTime_;         // 当前选中时间
PickerTime startTime_;            // 起始时间
PickerTime endTime_;              // 结束时间

// 配置
bool hour24_;                     // 是否 24 小时制
bool hasSecond_;                  // 是否显示秒
bool loop_;                       // 是否循环

// 列数据
std::map<WeakPtr<FrameNode>, std::unordered_map<uint32_t, std::string>> options_;
std::map<WeakPtr<FrameNode>, uint32_t> optionsTotalCount_;
std::unordered_map<std::string, WeakPtr<FrameNode>> allChildNode_;

// 节点 ID
std::optional<int32_t> amPmId_;
std::optional<int32_t> hourId_;
std::optional<int32_t> minuteId_;
std::optional<int32_t> secondId_;

// 语言和区域
std::string language_;
std::string amPmTimeOrder_;
std::vector<std::string> vecAmPm_;  // AM/PM 文本

// 前导零配置
ZeroPrefixType prefixHour_;
ZeroPrefixType prefixMinute_;
ZeroPrefixType prefixSecond_;
```

**关键方法**：

- **OnModifyDone()**: 初始化组件
  ```cpp
  void TimePickerRowPattern::OnModifyDone() {
      LinearLayoutPattern::OnModifyDone();

      // 构建列
      OnColumnsBuilding();

      // 初始化事件
      InitOnKeyEvent(GetFocusHub());
      InitFocusEvent();

      // 更新语言和 AM/PM 时间顺序
      UpdateLanguageAndAmPmTimeOrder();
  }
  ```

- **OnColumnsBuilding()**: 构建列
  ```cpp
  void TimePickerRowPattern::OnColumnsBuilding() {
      // 构建 AM/PM 列（12 小时制）
      if (!hour24_) {
          HandleAmPmColumnBuilding(selectedTime_);
      }

      // 构建小时列
      HandleHourColumnBuildingRange(selectedTime_);

      // 构建分钟列
      HandleMinAndSecColumnBuilding();

      // 构建秒列（如果需要）
      if (hasSecond_) {
          // 构建秒列
      }
  }
  ```

- **HandleHourColumnBuildingRange()**: 处理小时列构建
  ```cpp
  void TimePickerRowPattern::HandleHourColumnBuildingRange(const PickerTime& value) {
      auto hourColumn = allChildNode_["hour"];

      if (hour24_) {
          // 24 小时制: 0-23
          HandleHour24BuildTimeRange();
      } else {
          // 12 小时制: 1-12
          HandleHour12BuildTimeRange();
      }
  }
  ```

- **OnDataLinking()**: 数据联动处理
  ```cpp
  void TimePickerRowPattern::OnDataLinking(
      const RefPtr<FrameNode>& tag,
      bool isAdd,
      uint32_t index,
      std::vector<RefPtr<FrameNode>>& resultTags)
  {
      // 判断变化的是哪一列
      if (tag->GetId() == GetAmPmId()) {
          // AM/PM 列变化
          HandleAmPmReorder();
      } else if (tag->GetId() == GetHourId()) {
          // 小时列变化
          HandleHour12Change(isAdd, index, resultTags);
      } else if (tag->GetId() == GetMinuteId()) {
          // 分钟列变化
          HandleMinColumnChange();
      } else if (tag->GetId() == GetSecondId()) {
          // 秒列变化
          HandleSecColumnChange();
      }
  }
  ```

### 2.2 TimePickerColumnPattern

**职责**：
- 管理单列选项
- 处理列内滚动
- 触发联动事件

**关键方法**：
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

### 2.3 PickerTime

```cpp
struct PickerTime {
    uint32_t hour;    // 0-23 (24小时制) 或 1-12 (12小时制)
    uint32_t minute;  // 0-59
    uint32_t second;  // 0-59

    static PickerTime Current();        // 当前时间
    std::string ToString(bool, bool);   // 转换为字符串

    void SetHour(uint32_t value);
    void SetMinute(uint32_t value);
    void SetSecond(uint32_t value);
};
```

---

## 3. 完整交互流程

### 3.1 列构建流程

```
OnModifyDone()
    ↓
根据当前时间和配置 (hour24, hasSecond)
    ↓
OnColumnsBuilding()
    ↓
为每列创建/获取节点:
  - AM/PM 列 (12 小时制): HandleAmPmColumnBuilding()
  - 小时列: HandleHourColumnBuildingRange()
  - 分钟列: HandleMinAndSecColumnBuilding()
  - 秒列: HandleSecColumnBuilding()
    ↓
填充选项数据:
  - 根据起始/结束时间生成有效范围
  - 设置当前选中值
    ↓
AddChildToLayout() → 添加到布局树
```

### 3.2 滚动联动流程

```
用户滚动某一列
    ↓
TimePickerColumnPattern::OnColumnChange()
    ↓
TimePickerRowPattern::OnDataLinking()
    ↓
识别变化的列:
  - AM/PM 列 → HandleAmPmReorder()
  - 小时列 → HandleHour12Change()
  - 分钟列 → HandleMinColumnChange()
  - 秒列 → HandleSecColumnChange()
    ↓
更新 selectedTime_
    ↓
调整时间范围:
  LimitSelectedTimeInRange()
    ↓
FireChangeEvent() → 触发 onChange 事件
```

---

## 4. 关键技术点

### 4.1 12/24小时制切换

```cpp
void TimePickerRowPattern::SetHour24(bool value) {
    if (hour24_ == value) {
        return;  // 无变化
    }

    isForceUpdate_ = value != hour24_;
    hour24_ = value;

    if (!isClearFocus_) {
        isClearFocus_ = isForceUpdate_;
    }

    // 清空小时列选项
    ClearOptionsHour();

    // 重新构建小时列
    HandleHourColumnBuildingRange(selectedTime_);

    // 添加或移除 AM/PM 列
    CreateOrDeleteAmPmNode();
}
```

### 4.2 AM/PM 判断

```cpp
bool TimePickerRowPattern::IsAmHour(uint32_t hourOf24) const {
    // 判断 24 小时制的小时是否为 AM
    return hourOf24 < 12;
}

uint32_t TimePickerRowPattern::GetAmPmHour(uint32_t hourOf24) const {
    // 将 24 小时制转换为 12 小时制
    if (hourOf24 == 0) {
        return 12;  // 0 点 → 12 AM
    }
    return hourOf24 > 12 ? hourOf24 - 12 : hourOf24;
}

uint32_t TimePickerRowPattern::GetHourFromAmPm(bool isAm, uint32_t amPmhour) const {
    // 从 AM/PM 和 12 小时制转换为 24 小时制
    if (isAm) {
        return amPmhour == 12 ? 0 : amPmhour;
    } else {
        return amPmhour == 12 ? 12 : amPmhour + 12;
    }
}
```

### 4.3 时间范围限制

```cpp
PickerTime TimePickerRowPattern::AdjustTime(const PickerTime& time) {
    PickerTime adjustedTime = time;

    // 限制小时
    if (adjustedTime.GetHour() < startTime_.GetHour()) {
        adjustedTime.SetHour(startTime_.GetHour());
    } else if (adjustedTime.GetHour() > endTime_.GetHour()) {
        adjustedTime.SetHour(endTime_.GetHour());
    }

    // 限制分钟
    if (adjustedTime.GetMinute() < startTime_.GetMinute()) {
        adjustedTime.SetMinute(startTime_.GetMinute());
    } else if (adjustedTime.GetMinute() > endTime_.GetMinute()) {
        adjustedTime.SetMinute(endTime_.GetMinute());
    }

    // 限制秒
    if (adjustedTime.GetSecond() < startTime_.GetSecond()) {
        adjustedTime.SetSecond(startTime_.GetSecond());
    } else if (adjustedTime.GetSecond() > endTime_.GetSecond()) {
        adjustedTime.SetSecond(endTime_.GetSecond());
    }

    return adjustedTime;
}
```

### 4.4 前导零处理

```cpp
std::string TimePickerRowPattern::AddZeroPrefix(const std::string& value) const {
    // 为个位数添加前导零
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

### 4.5 语言和区域支持

```cpp
void TimePickerRowPattern::UpdateLanguageAndAmPmTimeOrder() {
    // 获取当前语言
    language_ = AceApplicationInfo::GetInstance().GetLanguage();

    // 获取 AM/PM 时间顺序（某些语言 PM 在前）
    auto preAmPmTimeOrder = amPmTimeOrder_;
    amPmTimeOrder_ = DateTimeSequence::GetAmPmTimeOrder(language_).amPmTimeOrder;

    // 更新布局方向（阿拉伯语 RTL）
    if (language_ == "ar" && layoutProperty->GetLayoutDirection() != TextDirection::RTL) {
        layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
        isDirectionSetByAr_ = true;
    }

    // 获取本地化 AM/PM 文本
    vecAmPm_ = Localization::GetInstance()->GetAmPmStrings();
}
```

---

## 5. 属性系统

### 5.1 布局属性 (TimePickerLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **selected** | PickerTime | Current() | 选中时间 |
| **start** | PickerTime | 00:00:00 | 起始时间 |
| **end** | PickerTime | 23:59:59 | 结束时间 |
| **hour24** | bool | System setting | 是否 24 小时制 |
| **hasSecond** | bool | false | 是否显示秒 |
| **loop** | bool | true | 是否循环 |
| **prefixHour** | ZeroPrefixType | AUTO | 小时前导零 |
| **prefixMinute** | ZeroPrefixType | AUTO | 分钟前导零 |
| **prefixSecond** | ZeroPrefixType | AUTO | 秒前导零 |

### 5.2 ZeroPrefixType

```cpp
enum class ZeroPrefixType {
    AUTO,      // 自动判断（个位数加零）
    ALWAYS,    // 始终加前导零
    NEVER,     // 从不加前导零
};
```

---

## 6. 事件系统

### 6.1 事件类型

**onChange** - 时间改变：
```cpp
void TimePickerRowPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<TimePickerEventHub>();
    auto onChangeEvent = eventHub->GetChangeEvent();

    if (onChangeEvent) {
        auto info = GetSelectedObject(false);
        onChangeEvent(info);  // 触发 ArkTS onChange 回调
    }
}
```

**onEnterSelectedArea** - 进入选中区域：
```cpp
void TimePickerRowPattern::FireEnterSelectedAreaEvent(bool refresh) {
    if (enterSelectedAreaEventCallback_) {
        enterSelectedAreaEventCallback_(refresh);
    }
}
```

### 6.2 事件数据格式

```cpp
std::string TimePickerRowPattern::GetSelectedObject(bool isColumnChange, int32_t status) {
    // 格式: "hour:minute:second"
    auto& time = selectedTime_;
    std::string hourStr = GetHourColumnFormatString(time.GetHour());
    std::string minuteStr = GetMinuteColumnFormatString(time.GetMinute());
    std::string secondStr = GetSecondColumnFormatString(time.GetSecond());

    return hourStr + ":" + minuteStr + ":" + secondStr;
}
```

---

## 7. 12/24小时制

### 7.1 切换实现

```cpp
void TimePickerRowPattern::SetHour24(bool value) {
    hour24_ = value;

    if (value) {
        // 切换到 24 小时制
        // 1. 移除 AM/PM 列
        RemoveAmPmNode();

        // 2. 重新构建小时列 (0-23)
        ClearOptionsHour();
        HandleHour24BuildTimeRange();

        // 3. 转换当前时间
        uint32_t hour24 = GetHourFromAmPm(currentIsAm_, currentAmPmHour_);
        selectedTime_.SetHour(hour24);
    } else {
        // 切换到 12 小时制
        // 1. 添加 AM/PM 列
        CreateAmPmNode();

        // 2. 重新构建小时列 (1-12)
        ClearOptionsHour();
        HandleHour12BuildTimeRange();

        // 3. 转换当前时间
        bool isAm = IsAmHour(selectedTime_.GetHour());
        uint32_t amPmHour = GetAmPmHour(selectedTime_.GetHour());
        selectedTime_.SetHour(amPmHour);
    }
}
```

### 7.2 小时列选项

```cpp
// 24 小时制
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

// 12 小时制
void TimePickerRowPattern::HandleHour12BuildTimeRange() {
    auto hourColumn = allChildNode_["hour"];
    std::unordered_map<uint32_t, std::string> hourOptions;

    for (uint32_t hour = 1; hour <= 12; ++hour) {
        std::string hourStr = GetHourColumnFormatString(hour);
        hourOptions[hour - 1] = hourStr;  // 索引从 0 开始
    }

    options_[hourColumn] = hourOptions;
    optionsTotalCount_[hourColumn] = 12;
}
```

---

## 8. AM/PM 处理

### 8.1 AM/PM 文本获取

```cpp
std::string TimePickerRowPattern::GetAmFormatString() const {
    return vecAmPm_[0];  // "AM" 或本地化文本
}

std::string TimePickerRowPattern::GetPmFormatString() const {
    return vecAmPm_[1];  // "PM" 或本地化文本
}
```

### 8.2 AM/PM 列构建

```cpp
void TimePickerRowPattern::HandleAmPmColumnBuilding(const PickerTime& value) {
    auto amPmColumn = allChildNode_["ampm"];
    std::unordered_map<uint32_t, std::string> amPmOptions;

    amPmOptions[0] = GetAmFormatString();
    amPmOptions[1] = GetPmFormatString();

    options_[amPmColumn] = amPmOptions;
    optionsTotalCount_[amPmColumn] = 2;

    // 设置当前选中
    bool isAm = IsAmHour(value.GetHour());
    SetColumnSelected(amPmColumn, isAm ? 0 : 1);
}
```

### 8.3 AM/PM 列变化处理

```cpp
void TimePickerRowPattern::HandleAmPmReorder() {
    auto amPmColumn = allChildNode_["ampm"];
    auto amPmPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    uint32_t amPmIndex = amPmPattern->GetSelected();

    bool isAm = (amPmIndex == 0);

    // 转换当前小时
    uint32_t currentHour = selectedTime_.GetHour();

    if (isAm && currentHour >= 12) {
        // PM → AM: 13-23 → 1-11
        selectedTime_.SetHour(currentHour - 12);
    } else if (!isAm && currentHour < 12) {
        // AM → PM: 1-11 → 13-23
        selectedTime_.SetHour(currentHour + 12);
    }

    // 触发变化事件
    FireChangeEvent(true);
}
```

---

## 9. 最佳实践

### 9.1 基本使用

**推荐做法**：
```typescript
// 1. 基本时间选择
TimePicker({
  selected: new Time('2024-01-01 14:30:00')
})
  .onChange((value: string) => {
    console.log('Selected:', value);  // "14:30:00"
  })

// 2. 设置时间范围
TimePicker()
  .start(new Time('08:00:00'))
  .end(new Time('18:00:00'))

// 3. 24 小时制
TimePicker()
  .hour24(true)

// 4. 不显示秒
TimePicker()
  .hasSecond(false)
```

### 9.2 前导零配置

```typescript
// 自动添加前导零（个位数加零）
TimePicker()
  .prefixHour(ZeroPrefixType.AUTO)
  .prefixMinute(ZeroPrefixType.AUTO)
  .prefixSecond(ZeroPrefixType.AUTO)

// 始终添加前导零
TimePicker()
  .prefixHour(ZeroPrefixType.ALWAYS)

// 从不加前导零
TimePicker()
  .prefixHour(ZeroPrefixType.NEVER)
```

---

## 10. 问题排查

### 10.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 小时显示错误 | hour24 配置错误 | 检查 hour24 属性 |
| AM/PM 不正确 | 语言配置错误 | 检查系统语言设置 |
| 时间无法选择 | 超出范围 | 检查 start/end 设置 |
| 列联动失效 | 列ID不匹配 | 检查列节点ID |

### 10.2 调试工具

**日志输出**：
```bash
# 查看时间选择器相关日志
hilog -T ArkUI | grep -i timepicker
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/time_picker/
├── timepicker_row_pattern.h/cpp                 # 主要逻辑
├── timepicker_column_pattern.h/cpp              # 列模式
├── timepicker_layout_property.h                  # 布局属性
├── timepicker_event_hub.h                        # 事件处理
├── timepicker_paint_method.h/cpp                  # 绘制方法
├── timepicker_column_layout_algorithm.h/cpp       # 列布局算法
├── timepicker_row_accessibility_property.h/cpp    # 无障碍属性
└── timepicker_dialog_view.h/cpp                   # 对话框视图
```

---

## 关键要点总结

1. **12/24小时制**: 同时支持 12 小时制（AM/PM）和 24 小时制，可动态切换
2. **智能联动**: 时/分/秒三列智能联动更新
3. **时间范围**: 灵活的起始/结束时间配置
4. **前导零**: 支持自动/始终/从不三种前导零模式
5. **AM/PM 处理**: 自动判断上午/下午，支持列切换
6. **语言支持**: 支持多语言和 RTL 布局
7. **事件回调**: onChange/onEnterSelectedArea 完整支持
8. **无障碍**: 完整的键盘导航和焦点管理

---
