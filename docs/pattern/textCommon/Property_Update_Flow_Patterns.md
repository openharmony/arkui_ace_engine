# ACE Engine 属性更新流程通用规则

> **文档版本**: v1.0
> **创建时间**: 2026-02-02
> **适用范围**: ACE Engine NG 组件开发

---

## 目录

1. [核心概念](#核心概念)
2. [属性更新标志详解](#属性更新标志详解)
3. [标准更新流程](#标准更新流程)
4. [实际案例分析](#实际案例分析)
5. [常见问题与实践指南](#常见问题与实践指南)

---

## 核心概念

### 属性更新标志 (Property Update Flags)

在 ACE Engine NG 架构中，每个属性在定义时都必须指定更新标志，用于决定属性变化后触发的 pipeline 阶段。

```cpp
// 位置: core/components_ng/property/property.h
enum PropertyUpdateType {
    PROPERTY_UPDATE_MEASURE = 0,   // 触发布局测量
    PROPERTY_UPDATE_LAYOUT = 1,    // 触发布局定位
    PROPERTY_UPDATE_RENDER = 2,    // 直接触发渲染
    PROPERTY_UPDATE_MEASURE_SELF = 3, // 仅测量自身
};
```

### 三大 Pipeline 阶段

```
ArkTS 属性设置
    ↓
Model 层静态方法
    ↓
PaintProperty 更新 (标记脏标记)
    ↓
[根据 PropertyUpdateType 分流]
    ├→ PROPERTY_UPDATE_MEASURE → Measure → Layout → Render
    ├→ PROPERTY_UPDATE_LAYOUT → Layout → Render
    └→ PROPERTY_UPDATE_RENDER → Render (直接渲染)
    ↓
Modifier/Drawing 渲染
```

---

## 属性更新标志详解

### PROPERTY_UPDATE_MEASURE

**触发阶段**: Measure → Layout → Render

**适用场景**:
- 属性变化会影响组件的尺寸计算
- 需要重新测量内容大小
- 可能影响子组件的布局

**典型属性**:
- `Value` (Progress 组件) - 进度值变化可能影响文本尺寸
- `Color` (Progress 组件) - 颜色变化可能影响布局（某些复杂场景）
- `StrokeWidth` - 描边宽度直接影响尺寸
- `Max` - 最大值变化影响整体比例

**定义示例**:
```cpp
// progress_paint_property.h:74
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, double, PROPERTY_UPDATE_MEASURE);

// progress_paint_property.h:91
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
```

### PROPERTY_UPDATE_RENDER

**触发阶段**: Render (直接渲染)

**适用场景**:
- 纯视觉属性变化
- 不影响尺寸和布局
- 仅需要重绘

**典型属性**:
- `ProgressStatus` - 进度状态（进行中/加载中）
- `EnableSmoothEffect` - 平滑特效开关
- `IsSensitive` - 隐私模式标志
- `PaintShadow` - 阴影绘制开关

**定义示例**:
```cpp
// progress_paint_property.h:98
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PaintShadow, bool, PROPERTY_UPDATE_RENDER);

// progress_paint_property.h:99
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressStatus, ProgressStatus, PROPERTY_UPDATE_RENDER);
```

### PROPERTY_UPDATE_LAYOUT

**触发阶段**: Layout → Render

**适用场景**:
- 属性变化不影响组件自身尺寸
- 但可能影响子组件或定位
- 需要重新计算位置

**典型属性**:
- `Alignment` - 对齐方式
- `Padding` - 内边距（某些实现）

### PROPERTY_UPDATE_MEASURE_SELF

**触发阶段**: 仅测量自身 → Layout → Render

**适用场景**:
- 仅影响自身测量，不影响父组件

---

## 标准更新流程

### 完整流程图

```
┌─────────────────────────────────────────────────────────────────┐
│                     ArkTS 应用层                                │
│  component.property(newValue)                                  │
└────────────────────────────┬────────────────────────────────────┘
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                  ModelNG 层 (静态方法)                          │
│  ProgressModelNG::SetValue(FrameNode*, value)                  │
│    ↓                                                           │
│  auto paintProperty = frameNode->GetPaintProperty();           │
│  paintProperty->SetValue(value);                               │
└────────────────────────────┬────────────────────────────────────┘
                             ↓
┌─────────────────────────────────────────────────────────────────┐
│                PaintProperty 层 (属性存储)                      │
│  ACE_UPDATE_PAINT_PROPERTY(ProgressPaintProperty, Value, val)  │
│    ↓                                                           │
│  propValue_ = value;                                           │
│  MarkDirty(PROPERTY_UPDATE_MEASURE);  ← 关键：标记脏标记         │
└────────────────────────────┬────────────────────────────────────┘
                             ↓
              ┌──────────────┴──────────────┐
              │     检查 PropertyUpdateType  │
              └──────────────┬──────────────┘
                             ↓
        ┌────────────────────┴────────────────────┐
        │                                          │
    [MEASURE]                                [RENDER]
        │                                          │
        ↓                                          ↓
┌───────────────┐                          ┌───────────────┐
│ OnModifyDone() │  ← 统一入口              │ OnModifyDone() │
└───────┬───────┘                          └───────┬───────┘
        │                                          │
        ↓                                          ↓
┌───────────────┐                          ┌───────────────┐
│   Measure     │  ← 布局算法              │   (跳过)      │
│   Layout      │  ← 位置计算              │               │
└───────┬───────┘                          └───────┬───────┘
        │                                          │
        └──────────────────┬───────────────────────┘
                           ↓
        ┌──────────────────────────────────────┐
        │         PaintMethod 层                │
        │  UpdateContentModifier(paintWrapper)  │
        └──────────────────┬───────────────────┘
                           ↓
        ┌──────────────────────────────────────┐
        │         Modifier 层                   │
        │  modifier->SetValue(value)           │
        │  modifier->SetColor(color)           │
        └──────────────────┬───────────────────┘
                           ↓
        ┌──────────────────────────────────────┐
        │         渲染层 (Drawing)              │
        │  onDraw(DrawingContext&)             │
        └──────────────────────────────────────┘
```

### 关键入口：OnModifyDone()

所有属性更新最终都会汇聚到 `Pattern::OnModifyDone()`，这是统一的生命周期入口：

```cpp
// progress_pattern.cpp
void ProgressPattern::OnModifyDone()
{
    // 1. 初始化各种事件监听器（仅首次）
    InitFocusEvent();
    InitTouchEvent();
    InitHoverEvent();

    // 2. 获取最新的属性值
    auto paintProperty = GetPaintProperty<ProgressPaintProperty>();
    auto value = paintProperty->GetValue().value_or(0.0);

    // 3. 准备 Modifier
    if (!progressModifier_) {
        progressModifier_ = AceType::MakeRefPtr<ProgressModifier>(...);
    }

    // 4. 注意：这里不直接设置属性到 Modifier
    // 而是标记需要更新，真正的更新在 PaintMethod::UpdateContentModifier 中
}
```

### 真正的属性传递：PaintMethod::UpdateContentModifier()

```cpp
// progress_paint_method.cpp
void ProgressPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    // 1. 从 PaintWrapper 获取 PaintProperty（此时包含最新值）
    auto paintProperty = DynamicCast<ProgressPaintProperty>(paintWrapper->GetPaintProperty());

    // 2. 提取属性值
    value_ = paintProperty->GetValue().value_or(value_);
    color_ = paintProperty->GetColor().value_or(color_);
    maxValue_ = paintProperty->GetMaxValue().value_or(maxValue_);

    // 3. 计算相关值（如果有）
    CalculateStrokeWidth(paintWrapper->GetContentSize());

    // 4. 设置到 Modifier（真正的数据传递）
    progressModifier_->SetValue(value_);
    progressModifier_->SetColor(LinearColor(color_));
    progressModifier_->SetMaxValue(maxValue_);
}
```

---

## 实际案例分析

### 案例 1: Progress 组件的 Value 更新

**属性定义**:
```cpp
// progress_paint_property.h:74
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, double, PROPERTY_UPDATE_MEASURE);
```

**完整流程**:
```cpp
// 1. ArkTS 层
progress.value(75)

// 2. ModelNG 层 (progress_model_ng.cpp:85)
void ProgressModelNG::SetValue(FrameNode* frameNode, double value)
{
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    paintProperty->SetValue(value);  // 触发 PROPERTY_UPDATE_MEASURE
}

// 3. PaintProperty 层
// SetValue() 内部:
//   propValue_ = value;
//   MarkDirty(PROPERTY_UPDATE_MEASURE);  ← 标记需要重新测量

// 4. Pipeline 调度
// 由于是 PROPERTY_UPDATE_MEASURE，触发:
//   OnModifyDone() → Measure → Layout → Render

// 5. PaintMethod 层 (progress_paint_method.cpp:112)
void ProgressPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    // 此时 PaintProperty 包含最新的 value
    value_ = paintProperty->GetValue().value_or(value_);

    // 设置到 Modifier
    progressModifier_->SetMaxValue(maxValue_);
    progressModifier_->SetValue(isSensitive ? 0.0 : value_);
}

// 6. Modifier 渲染 (progress_modifier.cpp)
void ProgressModifier::SetValue(float value)
{
    value_->Set(value);  // AnimatableProperty 触发动画
}
```

### 案例 2: Progress 组件的 Color 更新

**属性定义**:
```cpp
// progress_paint_property.h:91
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Color, Color, PROPERTY_UPDATE_MEASURE);
```

**为什么 Color 也是 MEASURE?**

虽然颜色通常是纯视觉属性，但在 Progress 组件中，颜色变化可能需要：
1. 重新计算某些与颜色相关的布局参数
2. 触发 `ProgressPattern::UpdateColor()` 中的主题相关逻辑
3. 在某些复杂场景下（如渐变色），可能影响测量

**完整流程**:
```cpp
// 1. ArkTS 层
progress.color(Color.Red)

// 2. ModelNG 层 (progress_model_ng.cpp:86)
void ProgressModelNG::SetColor(FrameNode* frameNode, const Color& value)
{
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    paintProperty->SetColor(value);  // 触发 PROPERTY_UPDATE_MEASURE
}

// 3. Pattern 层 - 特殊处理
// 在 OnModifyDone() 中可能调用:
void ProgressPattern::UpdateColor(const Color& color, bool isFirstLoad)
{
    // 1. 检查是否用户主动设置
    isUserInitiatedColor_ = true;

    // 2. 颜色模式相关处理
    // 3. 主题相关处理
}

// 4. PaintMethod 层 (progress_paint_method.cpp:64)
void ProgressPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    // SCALE 类型特殊处理
    if (progressType_ != ProgressType::SCALE) {
        color_ = isUserInitiatedColor_ ? paintProperty->GetColor().value_or(color_) : color_;
    } else {
        color_ = paintProperty->GetColor().value_or(color_);
    }

    // 设置到 Modifier
    progressModifier_->SetColor(LinearColor(color_));
}
```

### 案例 3: ProgressStatus 更新 (RENDER 类型)

**属性定义**:
```cpp
// progress_paint_property.h:99
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressStatus, ProgressStatus, PROPERTY_UPDATE_RENDER);
```

**完整流程**:
```cpp
// 1. ArkTS 层
progress.progressStatus(ProgressStatus.LOADING)

// 2. ModelNG 层 (progress_model_ng.cpp:93)
void ProgressModelNG::SetProgressStatus(FrameNode* frameNode, ProgressStatus status)
{
    auto paintProperty = frameNode->GetPaintProperty<ProgressPaintProperty>();
    paintProperty->SetProgressStatus(status);  // 触发 PROPERTY_UPDATE_RENDER
}

// 3. Pipeline 调度
// 由于是 PROPERTY_UPDATE_RENDER，跳过 Measure 和 Layout，直接:
//   OnModifyDone() → Render

// 4. PaintMethod 层
void ProgressPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    ProgressStatus progressStatus = paintProperty->GetProgressStatus()
        .value_or(ProgressStatus::PROGRESSING);
    progressModifier_->SetProgressStatus(progressStatus);
}

// 5. Modifier 渲染
void ProgressModifier::SetProgressStatus(ProgressStatus status)
{
    progressStatus_->Set(static_cast<int>(status));
    // 可能启动或停止加载动画
}
```

---

## 常见问题与实践指南

### Q1: 为什么很多"视觉属性"定义为 MEASURE 而不是 RENDER?

**原因**:
1. **历史设计**: NG 架构早期，很多属性为了保守起见使用了 MEASURE
2. **复杂交互**: 某些属性在特定场景下确实影响布局（如带文本的进度条）
3. **性能权衡**: MEASURE 虽然更重，但能确保所有场景正确性

**实践指南**:
- 新组件开发时，优先考虑使用 `PROPERTY_UPDATE_RENDER`
- 只有在确认影响测量或布局时才使用 `PROPERTY_UPDATE_MEASURE`
- 可以通过性能测试来决定使用哪个标志

### Q2: 如何快速判断属性应该使用哪个标志?

**决策树**:
```
属性变化后...
    │
    ├→ 是否影响组件自身的 width/height?
    │   ├→ 是 → PROPERTY_UPDATE_MEASURE
    │   └→ 否 ↓
    ├→ 是否影响子组件的布局或位置?
    │   ├→ 是 → PROPERTY_UPDATE_LAYOUT
    │   └→ 否 ↓
    └→ 仅影响视觉效果（颜色、阴影等）?
        └→ 是 → PROPERTY_UPDATE_RENDER
```

**常见属性分类**:

| 属性类型 | 典型例子 | 推荐标志 |
|---------|---------|---------|
| 尺寸相关 | width, height, padding | MEASURE |
| 内容相关 | value, text, data | MEASURE |
| 位置相关 | margin, offset | LAYOUT |
| 纯视觉 | color, shadow, opacity | RENDER |
| 状态相关 | enabled, selected | RENDER |

### Q3: OnModifyDone() 中可以做哪些操作?

**可以做**:
- 初始化事件监听器（仅首次）
- 获取最新的属性值并缓存
- 创建和配置 Modifier
- 触发一次性初始化操作

**不应该做**:
- 直接修改 Modifier 的属性值（应该在 PaintMethod 中做）
- 触发异步操作（可能导致不一致）
- 长时间计算（影响性能）

### Q4: PaintMethod 和 Pattern 的职责如何划分?

**Pattern 职责**:
- 生命周期管理
- 事件监听器初始化
- 创建和配置 PaintMethod、Modifier
- 处理特殊的业务逻辑（如颜色模式切换）

**PaintMethod 职责**:
- 从 PaintProperty 提取最新属性值
- 计算派生值（如根据内容尺寸计算 stroke width）
- 将值设置到 Modifier
- 是 Property → Modifier 的真正桥梁

**Modifier 职责**:
- 存储动画属性值
- 实现 onDraw() 绘制逻辑
- 处理动画和特效

### Q5: 如何追踪属性更新流程?

**调试技巧**:

1. **查看属性定义**:
```bash
# 在组件的 paint_property.h 中查找属性定义
grep "ACE_DEFINE_PROPERTY_ITEM.*Value" progress_paint_property.h
# 输出: ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, double, PROPERTY_UPDATE_MEASURE);
```

2. **追踪 MarkDirty 调用**:
```cpp
// 在 PaintProperty 基类中
template<typename T>
void SetProperty(const T& value) {
    if (propValue_ != value) {
        propValue_ = value;
        MarkDirty(PROPERTY_UPDATE_MEASURE);  // 断点这里
    }
}
```

3. **查看 Pipeline 调度日志**:
```bash
# 运行时启用日志
export ACE_LOG_COMPONENT=progress
# 查看流程: OnModifyDone → Measure → Layout → Render
```

---

## 附录：常用宏定义说明

### ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP

```cpp
// 定义一个独立的属性
ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, double, PROPERTY_UPDATE_MEASURE);

// 展开后的代码结构:
class ProgressPaintProperty {
    std::optional<double> propValue_;
    bool HasValue() const { return propValue_.has_value(); }
    const std::optional<double>& GetValue() const { return propValue_; }
    void SetValue(const double& value) {
        propValue_ = value;
        MarkDirty(PROPERTY_UPDATE_MEASURE);  // 自动标记脏
    }
    void ResetValue() { propValue_.reset(); }
    std::optional<double> CloneValue() const { return propValue_; }
};
```

### ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP

```cpp
// 定义一个分组属性
ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ProgressPaintDate, Value, double, PROPERTY_UPDATE_MEASURE);

// 展开后的代码结构:
class ProgressPaintProperty {
    struct ProgressPaintDateGroup {
        std::optional<double> propValue_;
        // ... 其他分组属性
    };
    ProgressPaintDateGroup propProgressPaintDate_;

    const std::optional<double>& GetValue() const {
        return propProgressPaintDate_.propValue_;
    }
};
```

---

## 总结

### 核心要点

1. **属性定义决定流程**: `PROPERTY_UPDATE_MEASURE` vs `PROPERTY_UPDATE_RENDER` 决定了属性变化后是否经过 Layout 阶段

2. **统一入口 OnModifyDone()**: 所有属性更新都会经过此方法，但真正的属性传递在 `PaintMethod::UpdateContentModifier()`

3. **三层分离**: Pattern（生命周期）→ PaintMethod（属性转换）→ Modifier（渲染）

4. **MEASURE 不等于慢**: 虽然经过更多阶段，但能确保正确性。对于简单视觉属性，优先使用 RENDER

### 快速参考

| 场景 | 使用标志 | 是否经过 Layout |
|-----|---------|---------------|
| 进度值变化 | MEASURE | ✓ |
| 颜色变化 | MEASURE | ✓ |
| 状态切换 | RENDER | ✗ |
| 尺寸变化 | MEASURE | ✓ |
| 纯视觉特效 | RENDER | ✗ |

---

*相关文档*:
- [Progress 组件知识库](../progress/Progress_Knowledge_Base.md)
- [DataPanel 组件知识库](../data_panel/DataPanel_Knowledge_Base.md)
- [Gauge 组件知识库](../gauge/CLAUDE.md)
