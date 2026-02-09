# ArkUI TextPicker 组件完整知识库

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
7. [级联选项](#7-级联选项)
8. [自定义样式](#8-自定义样式)
9. [最佳实践](#9-最佳实践)
10. [问题排查](#10-问题排查)

---

## 1. 架构概述

### 1.1 系统架构

TextPicker 组件实现了一个文本选择器，支持单列和多列级联，采用 4 层架构：

```
ArkTS 前端
    ↓
桥接层 (TextPickerModifier) - 属性解析和应用
    ↓
行模式层 (TextPickerPattern) - 业务逻辑和多列管理
    ↓
列模式层 (TextPickerColumnPattern) - 单列滚动逻辑
    ↓
滚动层 (ContainerPicker) - 滚动和吸附
```

**设计原则**：
- **多列支持**: 支持单列和多列级联选择
- **自定义范围**: 灵活的范围定义 (start/end)
- **级联联动**: 父子列自动联动更新
- **丰富样式**: 支持渐变、分割线等自定义样式

### 1.2 选择器类型

| 类型 | 说明 | 示例 |
|------|------|------|
| **单列** | 单一文本选择 | 省份选择 |
| **多列** | 多列独立选择 | 年月日独立选择 |
| **级联** | 多列联动选择 | 省-市-区级联 |

---

## 2. 核心类详解

### 2.1 TextPickerPattern

**职责**：
- 管理多列数据
- 处理级联联动
- 管理样式配置
- 协调列之间的交互

**关键成员变量**：
```cpp
// 选项数据
std::vector<NG::RangeContent> range_;                  // 单列选项
std::vector<NG::RangeContent> options_;                // 单列选项 (别名)
std::vector<NG::TextCascadePickerOptions> cascadeOptions_;  // 级联选项
std::map<WeakPtr<FrameNode>, std::vector<NG::RangeContent>> optionsWithNode_;

// 选择状态
uint32_t selectedIndex_ = 0;                           // 单列选中索引
std::vector<uint32_t> selecteds_;                       // 多列选中索引
std::vector<std::string> values_;                      // 选中值

// 列配置
uint32_t columnsKind_ = 0;                             // 列数量
std::vector<Dimension> columnWidths_;                   // 列宽
bool isCascade_ = false;                                // 是否级联

// 样式
Color backgroundColor_ = Color::WHITE;
ItemDivider divider_;
Dimension gradientHeight_;
Dimension dividerSpacing_;
PickerTextProperties textProperties_;

// 对话框按钮
WeakPtr<FrameNode> weakButtonConfirm_;
WeakPtr<FrameNode> weakButtonCancel_;
```

**关键方法**：

- **OnModifyDone()**: 初始化组件
  ```cpp
  void TextPickerPattern::OnModifyDone() {
      LinearLayoutPattern::OnModifyDone();

      // 构建列
      OnColumnsBuilding();

      // 初始化事件
      InitOnKeyEvent(GetFocusHub());
      InitFocusEvent();
  }
  ```

- **OnColumnsBuilding()**: 构建列
  ```cpp
  void TextPickerPattern::OnColumnsBuilding() {
      if (isCascade_) {
          OnColumnsBuildingCascade();
      } else {
          OnColumnsBuildingUnCascade();
      }
  }
  ```

- **OnColumnsBuildingUnCascade()**: 构建非级联列
  ```cpp
  void TextPickerPattern::OnColumnsBuildingUnCascade() {
      // 单列模式
      if (columnsKind_ == 1) {
          auto column = GetColumnNode();
          FillColumnOptions(column, options_);
          SetSelected(selectedIndex_);
          return;
      }

      // 多列模式
      for (uint32_t i = 0; i < columnsKind_; ++i) {
          auto column = CreateColumnNode(i);
          std::vector<NG::RangeContent> columnOptions;

          // 为每列填充选项
          for (const auto& item : range_) {
              columnOptions.emplace_back(item);
          }

          FillColumnOptions(column, columnOptions);
          SetColumnSelected(column, selecteds_[i]);
      }
  }
  ```

- **OnColumnsBuildingCascade()**: 构建级联列
  ```cpp
  void TextPickerPattern::OnColumnsBuildingCascade() {
      // 获取根级选项
      std::vector<NG::TextCascadePickerOptions> rootOptions = cascadeOptions_;

      // 第一列
      auto firstColumn = CreateColumnNode(0);
      FillColumnOptions(firstColumn, rootOptions);
      SetColumnSelected(firstColumn, selecteds_[0]);

      // 后续列根据第一列的选择动态生成
      UpdateCascadeColumns(0, rootOptions[selecteds_[0]]);
  }
  ```

- **HandleColumnChange()**: 处理列变化
  ```cpp
  void TextPickerPattern::HandleColumnChange(
      const RefPtr<FrameNode>& tag,
      bool isAdd,
      uint32_t index,
      bool needNotify)
  {
      if (isCascade_) {
          // 级联模式：更新后续列
          auto columnPattern = tag->GetPattern<TextPickerColumnPattern>();
          auto parentOption = columnPattern->GetCascadeOption(index);

          UpdateCascadeColumns(tag->GetId(), parentOption);
      }

      if (needNotify) {
          FireChangeEvent(true);
      }
  }
  ```

### 2.2 TextPickerColumnPattern

**职责**：
- 管理单列选项
- 处理列内滚动
- 触发变化事件

**关键方法**：
```cpp
class TextPickerColumnPattern : public Pattern {
public:
    void SetOptions(const std::vector<NG::RangeContent>& options);
    void SetSelected(uint32_t index);
    uint32_t GetSelected() const;

    std::string GetText() const;  // 获取选中文本

    // 级联选项
    void SetCascadeOptions(const std::vector<NG::TextCascadePickerOptions>& options);
    NG::TextCascadePickerOptions GetCascadeOption(uint32_t index);

    void OnColumnChange(bool isAdd, uint32_t index, bool needNotify);
};
```

### 2.3 RangeContent

```cpp
struct RangeContent {
    std::string text_;      // 显示文本
    std::string icon_;      // 图标 (可选)
    std::string value_;     // 实际值 (可选)
};
```

### 2.4 TextCascadePickerOptions

```cpp
struct TextCascadePickerOptions {
    std::string text_;                  // 显示文本
    uint32_t parentValue_;              // 父级值
    std::vector<TextCascadePickerOptions> children_;  // 子选项
};
```

---

## 3. 完整交互流程

### 3.1 单列选择流程

```
用户滚动选项列
    ↓
TextPickerColumnPattern::OnColumnChange()
    ↓
更新 selectedIndex_
    ↓
FireChangeEvent(true)
    ↓
构建返回数据:
  GetSelectedObject()
    ↓
触发 ArkTS onChange 回调
```

### 3.2 级联选择流程

```
用户滚动第一列
    ↓
TextPickerColumnPattern::OnColumnChange()
    ↓
HandleColumnChange(tag, isAdd, index, needNotify)
    ↓
获取选中的父选项
    ↓
UpdateCascadeColumns(parentId, parentOption)
    ↓
重新生成后续列:
  - 清空子列选项
  - 根据 parentOption.children_ 填充
  - 重置子列选中索引到 0
    ↓
FireChangeEvent(true)
    ↓
构建级联数据返回
```

---

## 4. 关键技术点

### 4.1 级联选项处理

```cpp
void TextPickerPattern::UpdateCascadeColumns(
    int32_t parentColumnId,
    const NG::TextCascadePickerOptions& parentOption)
{
    auto host = GetHost();
    uint32_t columnIndex = GetColumnIndex(parentColumnId);

    // 遍历后续列
    for (uint32_t i = columnIndex + 1; i < columnsKind_; ++i) {
        auto column = GetColumnNode(i);

        if (i == columnIndex + 1) {
            // 下一列：使用父选项的子项
            if (!parentOption.children_.empty()) {
                FillCascadeColumnOptions(column, parentOption.children_);
                SetColumnSelected(column, 0);
            } else {
                ClearColumnOptions(column);
            }
        } else {
            // 更后续列：清空
            ClearColumnOptions(column);
        }
    }
}

void TextPickerPattern::ProcessCascadeOptions(
    const std::vector<NG::TextCascadePickerOptions>& options,
    std::vector<NG::TextCascadePickerOptions>& reOptions,
    uint32_t index)
{
    // 处理级联选项数据
    for (const auto& option : options) {
        NG::TextCascadePickerOptions newOption;
        newOption.text_ = option.text_;
        newOption.parentValue_ = index;

        // 递归处理子选项
        if (!option.children_.empty()) {
            ProcessCascadeOptions(option.children_, newOption.children_, ...);
        }

        reOptions.emplace_back(newOption);
    }
}
```

### 4.2 范围解析

```cpp
// 类型: RANGE_TYPE_INT (整数范围)
TextPicker({
  range: ['2010', '2011', '2012', '2013', '2014', '2015', '2016', '2017', '2018',
          '2019', '2020', '2021', '2022', '2023', '2024']
})
.rangeType(RangeType.RANGE_TYPE_INT)

// 解析逻辑
void TextPickerPattern::ParseRangeResult(NG::TextCascadePickerOptions& option) {
    std::vector<std::string> rangeResultValue;

    // 从 resource 解析
    if (rangeType_ == RANGE_TYPE_INT) {
        // 整数范围: [0, 100] → "0", "1", "2", ..., "100"
        for (int32_t i = rangeStart_; i <= rangeEnd_; ++i) {
            rangeResultValue.emplace_back(std::to_string(i));
        }
    } else if (rangeType_ == RANGE_TYPE_FLOAT) {
        // 浮点数范围
        double value = rangeStart_;
        while (value <= rangeEnd_) {
            rangeResultValue.emplace_back(std::to_string(value));
            value += rangeStep_;
        }
    } else if (rangeType_ == RANGE_TYPE_STRING) {
        // 字符串数组
        rangeResultValue = rangeValues_;
    }

    // 填充选项
    for (const auto& value : rangeResultValue) {
        NG::RangeContent content;
        content.text_ = value;
        options_.emplace_back(content);
    }
}
```

### 4.3 选项获取

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

    // 单列模式
    return std::to_string(selectedIndex_);
}

std::string TextPickerPattern::GetSelectedObjectMulti(
    const std::vector<std::string>& values,
    const std::vector<uint32_t>& indexs,
    int32_t status) const
{
    // 构建多列选择结果
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

### 4.4 自定义样式

```cpp
void TextPickerPattern::SetTextProperties(const PickerTextProperties& properties) {
    textProperties_ = properties;

    // 消失文本样式
    if (properties.disappearTextStyle_.fontSize.has_value()) {
        gradientHeight_ = properties.disappearTextStyle_.fontSize.value();
    }

    // 普通文本样式
    if (properties.normalTextStyle_.fontSize.has_value()) {
        gradientHeight_ = std::max(properties.normalTextStyle_.fontSize.value(),
                                   gradientHeight_);
    }

    // 选中文本样式
    if (properties.selectedTextStyle_.fontSize.has_value()) {
        dividerSpacing_ = properties.selectedTextStyle_.fontSize.value();
    }
}
```

### 4.5 数字表冠支持

```cpp
#ifdef SUPPORT_DIGITAL_CROWN
void TextPickerPattern::InitOnCrownEvent(const RefPtr<FocusHub>& focusHub) {
    auto crownEvent = [weak = WeakClaim(this)](const CrownEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);

        if (!pattern->haveFocus_) {
            return false;
        }

        // 根据旋转方向调整选中值
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

---

## 5. 属性系统

### 5.1 布局属性 (TextPickerLayoutProperty)

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| **range** | vector\<RangeContent\> | - | 选项范围 |
| **selected** | uint32_t | 0 | 选中索引 |
| **value** | string | - | 选中值 |
| **columnsKind** | uint32_t | 1 | 列数量 |
| **columnWidths** | vector\<Dimension\> | - | 列宽 |
| **isCascade** | bool | false | 是否级联 |
| **canLoop** | bool | true | 是否循环 |

### 5.2 样式属性

| 属性 | 类型 | 说明 |
|------|------|------|
| **backgroundColor** | Color | 背景颜色 |
| **divider** | ItemDivider | 分割线样式 |
| **gradientHeight** | Dimension | 渐变高度 |
| **dividerSpacing** | Dimension | 分割线间距 |
| **textProperties** | PickerTextProperties | 文本样式 |

### 5.3 PickerTextProperties

```cpp
struct PickerTextProperties {
    PickerTextStyle disappearTextStyle_;  // 消失文本样式
    PickerTextStyle normalTextStyle_;     // 普通文本样式
    PickerTextStyle selectedTextStyle_;   // 选中文本样式
};

struct PickerTextStyle {
    std::optional<Color> color;
    std::optional<Dimension> fontSize;
    std::optional<std::vector<std::string>> fontFamily;
    std::optional<Dimension> minFontSize;
    std::optional<Dimension> maxFontSize;
};
```

---

## 6. 事件系统

### 6.1 事件类型

**onChange** - 选择改变：
```cpp
void TextPickerPattern::FireChangeEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onChange = eventHub->GetChangeEvent();

    if (onChange) {
        auto info = GetSelectedObject(false);
        onChange(info);  // 触发 ArkTS onChange 回调
    }
}
```

**onScrollStop** - 滚动停止：
```cpp
void TextPickerPattern::FireScrollStopEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onScrollStop = eventHub->GetScrollStopEvent();

    if (onScrollStop) {
        onScrollStop(selectedIndex_);
    }
}
```

**onEnterSelectedArea** - 进入选中区域：
```cpp
void TextPickerPattern::FireEnterSelectedAreaEvent(bool refresh) {
    auto eventHub = GetEventHub<TextPickerEventHub>();
    auto onEnterSelectedArea = eventHub->GetEnterSelectedAreaEvent();

    if (onEnterSelectedArea) {
        onEnterSelectedArea(true);
    }
}
```

---

## 7. 级联选项

### 7.1 级联数据结构

```typescript
// 省市区级联示例
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
    // ... 其他省份
  ]
})
```

### 7.2 级联更新流程

```
第一列选择 "广东省"
    ↓
HandleColumnChange(firstColumn, false, selectedIndex, true)
    ↓
获取 cascadeOptions_[selectedIndex]
    ↓
更新第二列:
  - 清空旧选项
  - 填充 children_ (广州市, 深圳市, ...)
  - 选中第一个 (广州市)
    ↓
更新第三列:
  - 清空旧选项
  - 填充 广州市.children_ (天河区, 越秀区, ...)
  - 选中第一个 (天河区)
```

---

## 8. 自定义样式

### 8.1 渐变效果

```cpp
// PaintMethod 绘制渐变
void TextPickerPaintMethod::PaintGradient(PaintWrapper* paintWrapper) {
    auto canvas = paintWrapper->GetCanvas();

    // 上方渐变 (消失文本)
    auto gradient1 = canvas->CreateLinearGradient(0, 0, 0, gradientHeight_);
    gradient1->AddColorStop(0.0, Color::TRANSPARENT);
    gradient1->AddColorStop(1.0, Color::WHITE);

    // 下方渐变
    auto gradient2 = canvas->CreateLinearGradient(0, height - gradientHeight_,
                                                  0, height);
    gradient2->AddColorStop(0.0, Color::WHITE);
    gradient2->AddColorStop(1.0, Color::TRANSPARENT);

    // 绘制渐变
    canvas->DrawRect(0, 0, width, gradientHeight_, gradient1);
    canvas->DrawRect(0, height - gradientHeight_, width, gradientHeight_, gradient2);
}
```

### 8.2 分割线样式

```cpp
struct ItemDivider {
    bool startMargin = false;
    bool endMargin = false;
    Dimension strokeWidth = 2.0_vp;
    Color color = Color::GRAY;
    Dimension marginTop = 0.0_vp;
    Dimension marginBottom = 0.0_vp;
};

// 绘制分割线
void TextPickerPaintMethod::PaintDivider(PaintWrapper* paintWrapper) {
    if (!divider_.strokeWidth.IsValid()) {
        return;
    }

    auto canvas = paintWrapper->GetCanvas();
    Paint paint;
    paint.SetAntiAlias(true);

    // 上分割线
    float topY = (pickerHeight - dividerSpacing) / 2;
    canvas->DrawLine(offsetX, topY, offsetX + width, topY, paint);

    // 下分割线
    float bottomY = topY + dividerSpacing;
    canvas->DrawLine(offsetX, bottomY, offsetX + width, bottomY, paint);
}
```

---

## 9. 最佳实践

### 9.1 基本使用

**推荐做法**：
```typescript
// 1. 单列选择
TextPicker({ range: ['A', 'B', 'C', 'D', 'E'] })
  .selected(0)
  .onChange((value: string) => {
    console.log('Selected:', value);
  })

// 2. 多列独立选择
TextPicker({
  range: [
    ['2010', '2011', '2012'],
    ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12'],
    ['1', '2', '3']
  ]
})
  .columnsKind(3)

// 3. 级联选择
TextPicker({
  cascadeOptions: provinceCityData
})
  .isCascade(true)
```

### 9.2 样式定制

```typescript
// 自定义文本样式
TextPicker()
  .textStyle({
    disappearTextStyle: { color: '#CCCCCC', fontSize: 14 },
    normalTextStyle: { color: '#333333', fontSize: 16 },
    selectedTextStyle: { color: '#FF0000', fontSize: 18 }
  })

// 自定义分割线
TextPicker()
  .divider({
    strokeWidth: 2,
    color: Color.Blue,
    startMargin: true,
    endMargin: true
  })

// 自定义渐变
TextPicker()
  .gradientHeight(50)
  .dividerSpacing(40)
```

### 9.3 性能优化

```typescript
// 1. 限制选项数量
TextPicker()
  .range(items.slice(0, 100))

// 2. 使用虚拟滚动
// 内部自动实现
```

---

## 10. 问题排查

### 10.1 常见问题

| 症状 | 可能原因 | 解决方案 |
|------|---------|----------|
| 级联不更新 | children_ 为空 | 检查级联数据结构 |
| 样式不生效 | 属性未正确设置 | 检查属性类型和值 |
| 多列显示异常 | columnsKind 配置错误 | 检查列数和选项数量 |
| 选项无法选择 | 超出范围 | 检查 selected 索引 |

### 10.2 调试工具

**日志输出**：
```bash
# 查看文本选择器相关日志
hilog -T ArkUI | grep -i textpicker
```

---

## 相关目录

```
frameworks/core/components_ng/pattern/text_picker/
├── textpicker_pattern.h/cpp                   # 主要逻辑
├── textpicker_column_pattern.h/cpp            # 列模式
├── textpicker_layout_property.h                # 布局属性
├── textpicker_event_hub.h                     # 事件处理
├── textpicker_paint_method.h/cpp              # 绘制方法
├── textpicker_dialog_view.h/cpp               # 对话框视图
├── textpicker_accessibility_property.h/cpp     # 无障碍属性
├── toss_animation_controller.h/cpp            # 动画控制
├── textpicker_properties.h                    # 属性定义
└── textpicker_overscroll.h/cpp                # 滚动边界处理
```

---

## 关键要点总结

1. **多列支持**: 支持单列和多列独立选择
2. **级联联动**: 父子列自动联动更新选项
3. **自定义范围**: 灵活的范围定义 (整数/浮点/字符串)
4. **丰富样式**: 渐变、分割线、文本样式全面支持
5. **数字表冠**: 支持手表设备数字表冠操作
6. **触觉反馈**: 滚动时提供震动反馈
7. **对话框支持**: 可在对话框中显示
8. **无障碍**: 完整的键盘导航和焦点管理

---
