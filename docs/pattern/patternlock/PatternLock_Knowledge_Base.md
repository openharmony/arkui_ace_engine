# ArkUI PatternLock 组件完整知识库

> **文档版本**: v1.0
> **更新时间**: 2026-02-02
> **源码版本**: OpenHarmony ace_engine (master 分支)
> **作者**: 基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [布局算法](#布局算法)
8. [属性系统](#属性系统)
9. [事件处理](#事件处理)
10. [绘制系统](#绘制系统)
11. [执行流程](#执行流程)
12. [完整API清单](#完整api清单)
13. [关键实现细节](#关键实现细节)
14. [使用示例](#使用示例)
15. [测试指南](#测试指南)
16. [附录](#附录)

---

## 概述

### 组件定位

**PatternLock 组件**是 OpenHarmony ArkUI 框架中的**图案锁组件**,提供九宫格图案解锁功能,支持自定义颜色、圆点半径、连线样式等属性,广泛应用于安全解锁、隐私保护等场景。

**技术栈**:
- **前端**: ArkTS/JavaScript
- **桥接层**: PatternLockModifier + ViewAbstractModel
- **核心层**: NG Pattern 架构
- **渲染层**: Rosen + Skia

**代码规模**:
- 总文件数: 约 20 个文件
- 核心代码: 约 8,000+ 行 C++ 代码
- 涉及 3 个架构层次

### 功能特性

PatternLock 组件支持:
- **九宫格图案绘制**: 3x3 点阵布局,支持手势滑动连接
- **自定义样式**: 颜色、圆点半径、线宽、侧边长度等
- **多种颜色配置**:
  - `selectedColor`: 选中点的颜色
  - `pathColor`: 连线路径颜色
  - `activeColor`: 激活状态颜色
  - `regularColor`: 常规状态颜色
  - `activeCircleColor`: 激活圆圈颜色
- **事件回调**:
  - `patternComplete`: 图案完成事件
  - `dotConnect`: 点连接事件
- **控制器模式**: 支持通过 PatternLockController 控制重置
- **自动重置**: 可配置的自动重置功能
- **跳过未选中点**: 支持跳过未选中的点
- **波纹效果**: 可选的波纹动画效果
- **前景模式**: 支持前景渲染模式
- **无障碍支持**: 完整的 Accessibility 支持

### 设计模式

PatternLock 组件采用 **NG Pattern 架构**:

```
前端 (ArkTS/JS)
    ↓ (Model Layer)
PatternLockModelNG (patternlock_model_ng.cpp)
    ↓ (NG Pattern Layer)
PatternLockPattern (patternlock_pattern.cpp)
    ↓ (NG LayoutAlgorithm Layer)
PatternLockLayoutAlgorithm (patternlock_layout_algorithm.cpp)
    ↓ (Paint Method Layer)
PatternLockPaintMethod (patternlock_paint_method.cpp)
    ↓
渲染显示
```

---

## 完整调用链

### 1. 组件创建调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS/JavaScript                                    │
│                                                          │
│ PatternLock()                                           │
│     .selectedColor(color)                               │
│     .autoReset(true)                                    │
│     .circleRadius(radius)                               │
│     .onPatternComplete(callback)                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (PatternLockModelNG)                        │
│                                                          │
│ PatternLockModelNG::Create()                            │
│   源码: frameworks/core/components_ng/pattern/          │
│         patternlock/patternlock_model_ng.cpp            │
│                                                          │
│ 执行流程:                                                 │
│ 1. 创建 FrameNode (V2::PATTERN_LOCK_ETS_TAG)            │
│ 2. 返回 PatternLockController                           │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (PatternLockPattern)                      │
│                                                          │
│ class PatternLockPattern : public Pattern               │
│   源码: frameworks/core/components_ng/pattern/          │
│         patternlock/patternlock_pattern.h               │
│                                                          │
│ 关键方法:                                                 │
│ - OnAttachToFrameNode() - 附加到节点树                   │
│ - OnModifyDone() - 修改完成回调                          │
│ - OnTouchDown() - 触摸按下处理                           │
│ - OnTouchMove() - 触摸移动处理                           │
│ - AddChoosePoint() - 添加选中点                          │
│ - CheckChoosePoint() - 检查点选择                        │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                         │
│                                                          │
│ class PatternLockLayoutAlgorithm                        │
│   : public BoxLayoutAlgorithm                           │
│   源码: frameworks/core/components_ng/pattern/          │
│         patternlock/patternlock_layout_algorithm.h      │
│                                                          │
│ 方法:                                                    │
│ - MeasureContent() - 测量内容大小                        │
│ - Measure() - 执行布局测量                               │
│ - InitializeParam() - 初始化参数                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ PaintMethod Layer (绘制方法)                             │
│                                                          │
│ class PatternLockPaintMethod                            │
│   源码: frameworks/core/components_ng/pattern/          │
│         patternlock/patternlock_paint_method.h          │
│                                                          │
│ 方法:                                                    │
│ - UpdateModifier() - 更新绘制修饰器                      │
│ - Draw() - 执行绘制操作                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Modifier Layer (绘制修饰器)                              │
│                                                          │
│ class PatternLockModifier                               │
│   源码: frameworks/core/components_ng/pattern/          │
│         patternlock/patternlock_modifier.h              │
│                                                          │
│ 绘制内容:                                                 │
│ - 绘制9个圆点                                            │
│ - 绘制连接路径                                           │
│ - 绘制激活状态效果                                       │
└─────────────────────────────────────────────────────────┘
```

### 2. 触摸事件处理调用链

```
用户触摸事件 (Touch Down/Move/Up)
    ↓
PatternLockEventHub (patternlock_event_hub.h)
    ↓
PatternLockPattern::HandleTouchEvent()
    ├─ OnTouchDown() - 初始化触摸,记录起始点
    ├─ OnTouchMove() - 移动时检查是否命中点
    │   ├─ CheckChoosePoint() - 检查坐标是否在点的热区内
    │   ├─ AddChoosePoint() - 添加选中点到路径
    │   └─ UpdateDotConnectEvent() - 触发点连接事件
    └─ OnTouchUp() - 结束触摸
        ├─ SetChallengeResult() - 设置图案结果
        └─ patternComplete() - 触发完成回调
```

---

## 目录结构

```
components_ng/pattern/patternlock/
├── patternlock_pattern.h/cpp              # Pattern层核心类
├── patternlock_model.h                    # Model接口定义
├── patternlock_model_ng.h/cpp             # NG Model实现
├── patternlock_model_static.h/cpp         # Static Model实现
├── patternlock_layout_property.h          # 布局属性
├── patternlock_layout_algorithm.h/cpp     # 布局算法
├── patternlock_paint_property.h           # 绘制属性
├── patternlock_paint_method.h/cpp         # 绘制方法
├── patternlock_modifier.h/cpp             # 绘制修饰器
├── patternlock_event_hub.h                # 事件处理
├── pattern_lock_controller.h/cpp          # 控制器
├── patternlock_challenge.h                # 挑战结果定义
├── patternlock_napi.h/cpp                 # NAPI接口
├── arkui_patternlock.js                   # JS接口定义
├── BUILD.gn                               # 构建配置
└── bridge/                                # 桥接层
    └── arkts_native_pattern_lock_bridge.h/cpp
```

---

## 核心类继承关系

### Pattern 层

```cpp
PatternLockPattern
├── 继承: public Pattern
├── 生命周期:
│   ├── OnAttachToFrameNode() - 附加到节点
│   ├── OnModifyDone() - 属性修改完成
│   └── OnDetachFromFrameNode() - 从节点分离
└── 创建方法:
    ├── CreateLayoutProperty() - 创建布局属性
    ├── CreatePaintProperty() - 创建绘制属性
    ├── CreateLayoutAlgorithm() - 创建布局算法
    ├── CreateEventHub() - 创建事件中心
    └── CreateNodePaintMethod() - 创建绘制方法
```

### Model 层

```cpp
PatternLockModelNG
├── 继承: public PatternLockModel
├── 静态方法 (用于直接操作FrameNode):
│   ├── CreateFrameNode() - 创建节点
│   ├── SetSelectedColor() - 设置选中颜色
│   ├── SetPathColor() - 设置路径颜色
│   ├── SetActiveColor() - 设置激活颜色
│   ├── SetCircleRadius() - 设置圆点半径
│   ├── SetAutoReset() - 设置自动重置
│   └── SetPatternComplete() - 设置完成回调
└── 实例方法 (用于链式调用):
    ├── Create() - 创建组件
    ├── SetSelectedColor() - 设置选中颜色
    ├── SetAutoReset() - 设置自动重置
    └── SetPatternComplete() - 设置完成回调
```

### LayoutAlgorithm 层

```cpp
PatternLockLayoutAlgorithm
├── 继承: public BoxLayoutAlgorithm
└── 核心方法:
    ├── MeasureContent() - 测量内容大小
    ├── Measure() - 执行测量
    └── InitializeParam() - 初始化参数
```

---

## Pattern层详解

### PatternLockPattern 核心职责

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_pattern.h`

#### 1. 生命周期管理

```cpp
// 附加到节点树时调用
void PatternLockPattern::OnAttachToFrameNode()
{
    // 1. 初始化 PatternLockController
    InitPatternLockController();

    // 2. 初始化触摸事件
    auto gestureHub = GetHost()->GetOrCreateGestureEventHub();
    RefPtr<TouchEventImpl> touchDownListener;
    InitTouchEvent(gestureHub, touchDownListener);

    // 3. 初始化焦点事件
    InitFocusEvent();

    // 4. 初始化鼠标事件
    InitMouseEvent();

    // 5. 初始化无障碍功能
    InitAccessibilityHoverEvent();
}

// 属性修改完成时调用
void PatternLockPattern::OnModifyDone()
{
    // 1. 计算单元格中心点
    CalculateCellCenter();

    // 2. 更新选中颜色
    auto paintProperty = GetPaintProperty<PatternLockPaintProperty>();
    if (paintProperty->GetSelectedColorValue()) {
        UpdateSelectedColor(paintProperty->GetSelectedColorValue().value());
    }

    // 3. 更新路径颜色
    if (paintProperty->GetPathColorValue()) {
        UpdatePathColor(paintProperty->GetPathColorValue().value());
    }
}
```

#### 2. 触摸事件处理

```cpp
// 触摸按下
void PatternLockPattern::OnTouchDown(const TouchLocationInfo& info)
{
    // 1. 记录手指ID (支持多点触控)
    fingerId_ = info.GetFingerId();

    // 2. 重置选择状态
    choosePoint_.clear();
    passPointCount_ = 0;

    // 3. 检查是否命中点
    auto localOffset = info.GetLocalLocation();
    CheckChoosePoint(localOffset.GetX(), localOffset.GetY());
}

// 触摸移动
void PatternLockPattern::OnTouchMove(const TouchLocationInfo& info)
{
    // 1. 验证手指ID
    if (info.GetFingerId() != fingerId_) {
        return;
    }

    // 2. 检查是否命中新的点
    auto localOffset = info.GetLocalLocation();
    AddChoosePoint(localOffset, localOffset.GetX(), localOffset.GetY());

    // 3. 触发点连接事件
    UpdateDotConnectEvent();
}

// 触摸抬起
void PatternLockPattern::OnTouchUp()
{
    // 1. 设置挑战结果
    SetChallengeResult(V2::PatternLockChallengeResult {
        .choosePoint_ = choosePoint_,
        .success_ = static_cast<int32_t>(choosePoint_.size()) >= 4
    });

    // 2. 触发完成回调
    auto eventHub = GetEventHub<PatternLockEventHub>();
    eventHub->patternComplete_(challengeResult_);

    // 3. 自动重置
    if (CheckAutoReset()) {
        HandleReset();
    }
}
```

#### 3. 点选择检测

```cpp
// 检查坐标是否命中点
bool PatternLockPattern::CheckChoosePoint(int32_t x, int32_t y) const
{
    // 遍历3x3九宫格
    for (int32_t i = 0; i < 3; i++) {
        for (int32_t j = 0; j < 3; j++) {
            if (CheckInHotSpot(offset, i, j)) {
                return true;
            }
        }
    }
    return false;
}

// 检查是否在点的热区内
bool PatternLockPattern::CheckInHotSpot(const OffsetF& offset, int32_t x, int32_t y)
{
    // 获取圆点中心坐标
    auto cellCenter = GetCellCenter(x, y);

    // 计算距离
    float distance = (offset - cellCenter).GetDistance();

    // 获取圆点半径
    float circleRadius = GetHandleCircleRadius();

    // 判断是否在热区内 (半径的1.5倍)
    return distance <= circleRadius * 1.5f;
}

// 添加选中点
bool PatternLockPattern::AddChoosePoint(const OffsetF& offset, int32_t x, int32_t y)
{
    // 1. 检查是否在点的热区内
    if (!CheckInHotSpot(offset, x, y)) {
        return false;
    }

    // 2. 创建 PatternLockCell
    PatternLockCell cell(x, y);

    // 3. 检查是否已选择
    if (std::find(choosePoint_.begin(), choosePoint_.end(), cell) != choosePoint_.end()) {
        return false;
    }

    // 4. 添加中间点 (跳过逻辑)
    if (skipUnselectedPoint_ && !choosePoint_.empty()) {
        auto lastPoint = choosePoint_.back();
        AddPassPointToChoosePoint(lastPoint.x, cell.x, passPointVec);
        AddPassPointToChoosePoint(lastPoint.y, cell.y, passPointVec);
    }

    // 5. 添加到选择列表
    choosePoint_.push_back(cell);

    // 6. 触发动画
    StartModifierConnectedAnimate(x, y);

    return true;
}
```

#### 4. 控制器功能

```cpp
// 初始化控制器
void PatternLockPattern::InitPatternLockController()
{
    if (!patternLockController_) {
        patternLockController_ = MakeRefPtr<V2::PatternLockController>();
    }

    // 设置重置回调
    patternLockController_->SetReset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleReset();
        }
    });
}

// 处理重置
void PatternLockPattern::HandleReset()
{
    // 1. 清空选择点
    choosePoint_.clear();
    passPointCount_ = 0;

    // 2. 重置状态
    isMoveEventValid_ = false;

    // 3. 触发取消动画
    StartModifierCanceledAnimate();

    // 4. 标记需要重绘
    host->MarkDirtyNode(PaintProperty::PAINT_PROPERTY);
}
```

---

## Model层详解

### PatternLockModelNG 核心方法

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_model_ng.h`

#### 1. 创建组件

```cpp
RefPtr<V2::PatternLockController> PatternLockModelNG::Create()
{
    // 1. 创建 FrameNode
    auto frameNode = FrameNode::CreateFrameNode(
        V2::PATTERN_LOCK_ETS_TAG,
        -1,
        []() { return MakeRefPtr<PatternLockPattern>(); }
    );

    // 2. 创建控制器
    auto controller = MakeRefPtr<V2::PatternLockController>();

    // 3. 附加到 Pattern
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    if (pattern) {
        pattern->SetPatternLockController(controller);
    }

    return controller;
}
```

#### 2. 属性设置 (链式调用)

```cpp
// 设置选中颜色
void PatternLockModelNG::SetSelectedColor(const Color& selectedColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty->SetSelectedColor(selectedColor);

    // 触发更新
    frameNode->MarkModifyDone();
}

// 设置自动重置
void PatternLockModelNG::SetAutoReset(bool isAutoReset)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->SetAutoReset(isAutoReset);
}

// 设置圆点半径
void PatternLockModelNG::SetCircleRadius(const Dimension& radius)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<PatternLockLayoutProperty>();
    layoutProperty->SetCircleRadius(radius);

    frameNode->MarkModifyDone();
}
```

#### 3. 事件设置

```cpp
// 设置图案完成回调
void PatternLockModelNG::SetPatternComplete(NG::PatternLockCompleteEvent&& onComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    eventHub->patternComplete_ = std::move(onComplete);
}

// 设置点连接回调
void PatternLockModelNG::SetDotConnect(std::function<void(int32_t)>&& onDotConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto eventHub = frameNode->GetEventHub<PatternLockEventHub>();
    eventHub->dotConnect_ = std::move(onDotConnect);
}
```

#### 4. 静态方法 (直接操作 FrameNode)

```cpp
// 静态方法示例 - 用于直接操作已存在的 FrameNode
void PatternLockModelNG::SetSelectedColor(FrameNode* frameNode, const Color& selectedColor)
{
    CHECK_NULL_VOID(frameNode);

    auto paintProperty = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty->SetSelectedColor(selectedColor);

    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->UpdateSelectedColor(selectedColor);

    frameNode->MarkModifyDone();
}

void PatternLockModelNG::SetAutoReset(FrameNode* frameNode, bool isAutoReset)
{
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->SetAutoReset(isAutoReset);
}
```

---

## 布局算法

### PatternLockLayoutAlgorithm

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_layout_algorithm.h`

#### 测量流程

```cpp
std::optional<SizeF> PatternLockLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint,
    LayoutWrapper* layoutWrapper)
{
    // 1. 初始化参数
    InitializeParam();

    // 2. 计算侧边长度
    float sideLength = sideLength_.ConvertToPx();

    // 3. 确保最小尺寸
    if (sideLength < contentConstraint.minSize.Width() ||
        sideLength < contentConstraint.minSize.Height()) {
        sideLength = std::max({
            contentConstraint.minSize.Width(),
            contentConstraint.minSize.Height(),
            sideLength
        });
    }

    // 4. 返回正方形尺寸
    return SizeF(sideLength, sideLength);
}

void PatternLockLayoutAlgorithm::InitializeParam()
{
    // 从 LayoutProperty 获取参数
    auto layoutProperty = GetLayoutProperty();
    if (layoutProperty) {
        sideLength_ = layoutProperty->GetSideLengthValue(Dimension(0.0));
    }

    // 默认值为当前容器大小
    if (sideLength_.IsNonPositive()) {
        sideLength_ = Dimension(300.0, DimensionUnit::VP); // 默认300vp
    }
}
```

#### 布局特点

1. **固定宽高比**: PatternLock 始终为正方形 (1:1)
2. **自适应大小**: 默认适应容器大小,最小 300vp
3. **3x3 九宫格**: 固定的点阵布局

---

## 属性系统

### LayoutProperty (布局属性)

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_layout_property.h`

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `circleRadius` | Dimension | 14vp | 圆点半径 |
| `sideLength` | Dimension | 300vp | 侧边长度 |
| `strokeWidth` | Dimension | 2vp | 连线宽度 |

### PaintProperty (绘制属性)

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_paint_property.h`

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `selectedColor` | Color | Color::BLACK | 选中点的颜色 |
| `pathColor` | Color | Color::BLACK | 连线路径颜色 |
| `activeColor` | Color | Color::BLUE | 激活状态颜色 |
| `regularColor` | Color | Color::GRAY | 常规状态颜色 |
| `activeCircleColor` | Color | Color::BLUE | 激活圆圈颜色 |
| `activeCircleRadius` | Dimension | 16vp | 激活圆圈半径 |
| `enableWaveEffect` | bool | true | 是否启用波纹效果 |
| `enableForeground` | bool | false | 是否启用前景模式 |
| `skipUnselectedPoint` | bool | false | 是否跳过未选中点 |

### 属性更新流程

```
用户设置属性 (ArkTS)
    ↓
PatternLockModelNG::SetXxx()
    ↓
PatternLockPaintProperty::SetXxx()
    ↓
PatternLockPattern::OnModifyDone()
    ↓
PatternLockPattern::UpdateXxx()
    ↓
PatternLockModifier::SetXxx()
    ↓
标记需要重绘 (MarkDirtyNode)
```

---

## 事件处理

### EventHub 结构

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_event_hub.h`

```cpp
class PatternLockEventHub : public EventHub {
public:
    // 图案完成事件
    PatternLockCompleteEvent patternComplete_;

    // 点连接事件
    std::function<void(int32_t)> dotConnect_;
};
```

### 事件类型

| 事件 | 触发时机 | 回调参数 |
|------|----------|----------|
| `patternComplete` | 手指抬起时 | PatternLockChallengeResult |
| `dotConnect` | 连接新点时 | int32_t (点的索引) |

### PatternLockChallengeResult 结构

```cpp
struct PatternLockChallengeResult {
    std::vector<PatternLockCell> choosePoint_; // 选中的点列表
    bool success_;                             // 是否成功 (>=4个点)
};
```

### PatternLockCell 结构

```cpp
struct PatternLockCell {
    int32_t x; // 列索引 (0-2)
    int32_t y; // 行索引 (0-2)

    // 索引计算: index = y * 3 + x
};
```

---

## 绘制系统

### PatternLockPaintMethod

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_paint_method.h`

```cpp
class PatternLockPaintMethod : public NodePaintMethod {
public:
    PatternLockPaintMethod(
        const OffsetF& cellCenter,
        bool isMoveEventValid,
        const std::vector<PatternLockCell>& choosePoint,
        const RefPtr<PatternLockModifier>& patternLockModifier)
        : cellCenter_(cellCenter),
          isMoveEventValid_(isMoveEventValid),
          choosePoint_(choosePoint),
          patternLockModifier_(patternLockModifier) {}

    void UpdateModifier(PaintWrapper* paintWrapper) override
    {
        // 1. 更新单元格中心
        patternLockModifier_->SetCellCenter(cellCenter_);

        // 2. 更新移动状态
        patternLockModifier_->SetIsMoveEventValid(isMoveEventValid_);

        // 3. 更新选中点
        patternLockModifier_->SetChoosePoint(choosePoint_);

        // 4. 添加到绘制上下文
        paintWrapper->AddModifier(patternLockModifier_);
    }

private:
    OffsetF cellCenter_;
    bool isMoveEventValid_;
    std::vector<PatternLockCell> choosePoint_;
    RefPtr<PatternLockModifier> patternLockModifier_;
};
```

### PatternLockModifier 绘制内容

**源码位置**: `frameworks/core/components_ng/pattern/patternlock/patternlock_modifier.h`

绘制内容:
1. **9个圆点**: 3x3 九宫格布局
2. **连接路径**: 从第一个点到当前点的连线
3. **激活状态**: 选中点的放大效果
4. **波纹效果**: (可选) 点选中时的波纹动画

绘制顺序:
```
1. 绘制背景圆点 (regularColor)
2. 绘制选中圆点 (selectedColor)
3. 绘制连接路径 (pathColor)
4. 绘制激活效果 (activeColor)
5. 绘制波纹效果 (enableWaveEffect)
```

---

## 执行流程

### 完整生命周期

```
1. 创建阶段
   PatternLockModelNG::Create()
   → FrameNode::CreateFrameNode()
   → PatternLockPattern::OnAttachToFrameNode()
   → InitPatternLockController()
   → InitTouchEvent()

2. 属性设置阶段
   PatternLockModelNG::SetSelectedColor()
   → PatternLockPaintProperty::SetSelectedColor()
   → PatternLockPattern::OnModifyDone()
   → PatternLockPattern::UpdateSelectedColor()

3. 测量布局阶段
   PatternLockLayoutAlgorithm::Measure()
   → PatternLockLayoutAlgorithm::MeasureContent()
   → CalculateCellCenter()

4. 绘制阶段
   PatternLockPaintMethod::UpdateModifier()
   → PatternLockModifier::Draw()
   → Rosen/Skia 渲染

5. 交互阶段
   用户触摸
   → PatternLockPattern::HandleTouchEvent()
   → OnTouchDown() / OnTouchMove() / OnTouchUp()
   → CheckChoosePoint()
   → AddChoosePoint()
   → UpdateDotConnectEvent()
   → SetChallengeResult()
   → patternComplete()

6. 销毁阶段
   PatternLockPattern::OnDetachFromFrameNode()
   → 清理资源
```

---

## 完整API清单

### ArkTS API

```typescript
// 创建组件
PatternLock(): PatternLockController

// 属性设置
selectedColor(color: ResourceColor): void
pathColor(color: ResourceColor): void
activeColor(color: ResourceColor): void
regularColor(color: ResourceColor): void
activeCircleColor(color: ResourceColor): void
circleRadius(radius: Length): void
sideLength(length: Length): void
strokeWidth(width: Length): void
activeCircleRadius(radius: Length): void
autoReset(isReset: boolean): void
enableWaveEffect(enable: boolean): void
skipUnselectedPoint(skip: boolean): void

// 事件设置
onPatternComplete(callback: (result: PatternLockChallengeResult) => void): void
onDotConnect(callback: (index: number) => void): void
```

### C++ Model API (PatternLockModelNG)

```cpp
// 创建组件
RefPtr<V2::PatternLockController> Create() override;

// 属性设置
void SetSelectedColor(const Color& selectedColor) override;
void SetPathColor(const Color& pathColor) override;
void SetActiveColor(const Color& activeColor) override;
void SetRegularColor(const Color& regularColor) override;
void SetActiveCircleColor(const Color& activeCircleColor) override;
void SetCircleRadius(const Dimension& radius) override;
void SetSideLength(const Dimension& sideLength) override;
void SetStrokeWidth(const Dimension& lineWidth) override;
void SetActiveCircleRadius(const Dimension& activeCircleRadius) override;
void SetAutoReset(bool isAutoReset) override;
void SetEnableWaveEffect(bool enableWaveEffect) override;
void SetSkipUnselectedPoint(bool isSkipUnselectedPoint) override;

// 事件设置
void SetPatternComplete(NG::PatternLockCompleteEvent&& onComplete) override;
void SetDotConnect(std::function<void(int32_t)>&& onDotConnect) override;

// 静态方法
static void SetSelectedColor(FrameNode* frameNode, const Color& selectedColor);
static void SetAutoReset(FrameNode* frameNode, bool isAutoReset);
static void SetPatternComplete(FrameNode* frameNode, NG::PatternLockCompleteEvent&& onComplete);
// ... (其他静态方法)
```

### C++ Controller API (PatternLockController)

```cpp
class PatternLockController {
public:
    // 重置图案锁
    void Reset();

    // 设置重置回调
    void SetReset(std::function<void()>&& resetCallback);
};
```

---

## 关键实现细节

### 1. 单元格中心点计算

**源码**: `patternlock_pattern.cpp:CalculateCellCenter()`

```cpp
void PatternLockPattern::CalculateCellCenter()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto padding = host->GetLayoutProperty()->GetPaddingProperty();
    float paddingTop = padding ? padding->top.value() : 0.0f;
    float paddingBottom = padding ? padding->bottom.value() : 0.0f;
    float paddingLeft = padding ? padding->left.value() : 0.0f;
    float paddingRight = padding ? padding->right.value() : 0.0f;

    // 计算可用区域
    float contentWidth = geometryNode->GetFrameSize().Width() - paddingLeft - paddingRight;
    float contentHeight = geometryNode->GetFrameSize().Height() - paddingTop - paddingBottom;

    // 计算单元格间距
    float cellIntervalX = contentWidth / 4.0f;
    float cellIntervalY = contentHeight / 4.0f;

    // 设置单元格中心偏移
    cellCenter_ = OffsetF(cellIntervalX, cellIntervalY);
}
```

**计算公式**:
- `cellIntervalX = contentWidth / 4`
- `cellIntervalY = contentHeight / 4`
- `点[x,y] 的中心坐标 = (paddingLeft + cellIntervalX * (x + 1), paddingTop + cellIntervalY * (y + 1))`

### 2. 跳过未选中点逻辑

**源码**: `patternlock_pattern.cpp:AddPassPointToChoosePoint()`

```cpp
void PatternLockPattern::AddPassPointToChoosePoint(
    int32_t lastCode,
    int32_t nowCode,
    std::vector<PatternLockCell> passPointVec)
{
    // 计算中间点
    int32_t middleCode = (lastCode + nowCode) / 2;

    // 检查是否有中间点
    if (lastCode + nowCode == 2 * middleCode) {
        PatternLockCell middleCell(middleCode % 3, middleCode / 3);

        // 检查中间点是否已被选择
        auto it = std::find(choosePoint_.begin(), choosePoint_.end(), middleCell);
        if (it == choosePoint_.end()) {
            // 添加中间点
            choosePoint_.push_back(middleCell);
            passPointCount_++;

            // 触发动画
            StartModifierAddPassPointAnimate(middleCode % 3, middleCode / 3);
        }
    }
}
```

**跳过规则**:
- 从 (0,0) 到 (0,2): 跳过 (0,1)
- 从 (0,0) 到 (2,0): 跳过 (1,0)
- 从 (0,0) 到 (2,2): 跳过 (1,1)
- 等等...

**条件**: `lastCode + nowCode == 2 * middleCode` (中间点存在且未被选择)

### 3. 多点触控处理

**源码**: `patternlock_pattern.cpp:HandleTouchEvent()`

```cpp
void PatternLockPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    // 获取触摸点列表
    const auto& touches = info.GetTouches();

    for (const auto& touch : touches) {
        int32_t id = touch.GetFingerId();

        // 只处理第一个手指
        if (fingerId_ == -1) {
            fingerId_ = id;
        }

        if (id != fingerId_) {
            continue;
        }

        // 根据触摸类型分发
        switch (touch.GetTouchType()) {
            case TouchType::DOWN:
                OnTouchDown(touch);
                break;
            case TouchType::MOVE:
                OnTouchMove(touch);
                break;
            case TouchType::UP:
            case TouchType::CANCEL:
                OnTouchUp();
                fingerId_ = -1;
                break;
            default:
                break;
        }
    }
}
```

**逻辑**:
1. 只跟踪第一个按下的手指
2. 忽略其他手指的触摸事件
3. 手指抬起后重置 `fingerId_`

### 4. 自动重置机制

**源码**: `patternlock_pattern.cpp:CheckAutoReset()`

```cpp
bool PatternLockPattern::CheckAutoReset() const
{
    return autoReset_;
}

void PatternLockPattern::OnTouchUp()
{
    // ... 设置挑战结果

    // 自动重置
    if (CheckAutoReset()) {
        HandleReset();
    }
}
```

**配置**:
```typescript
// ArkTS
PatternLock()
    .autoReset(true)  // 自动重置 (默认)
    .autoReset(false) // 保持选择状态
```

### 5. 无障碍支持

**源码**: `patternlock_pattern.cpp:InitVirtualNode()`

```cpp
bool PatternLockPattern::InitVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    auto accessibilityProperty = host->GetAccessibilityProperty<PatternLockAccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);

    // 为每个点创建虚拟节点
    for (int32_t y = 0; y < 3; y++) {
        for (int32_t x = 0; x < 3; x++) {
            auto textNode = AddTextNodeIntoVirtual(x, y, handleCircleRadius);
            textAccessibilityNodeVec_.push_back(textNode);
        }
    }

    return true;
}

RefPtr<FrameNode> PatternLockPattern::AddTextNodeIntoVirtual(
    int32_t x, int32_t y, float handleCircleRadius)
{
    // 创建虚拟文本节点用于无障碍朗读
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG,
        -1,
        []() { return MakeRefPtr<TextPattern>(); }
    );

    // 设置文本内容
    auto textPattern = textNode->GetPattern<TextPattern>();
    std::string text = ReplacePlaceHolder("点 {0}, {1}", x, y);
    textPattern->SetText(text);

    return textNode;
}
```

---

## 使用示例

### ArkTS 示例 1: 基础使用

```typescript
@Entry
@Component
struct PatternLockExample {
  @State message: string = '请绘制图案'

  build() {
    Column() {
      Text(this.message)
        .fontSize(20)
        .margin({ bottom: 20 })

      PatternLock()
        .selectedColor(Color.Blue)
        .pathColor(Color.Red)
        .autoReset(true)
        .onPatternComplete((result: PatternLockChallengeResult) => {
          if (result.success) {
            this.message = '图案正确!'
          } else {
            this.message = '至少连接4个点'
          }
        })
    }
    .width('100%')
    .height('100%')
  }
}
```

### ArkTS 示例 2: 自定义样式

```typescript
@Entry
@Component
struct CustomPatternLock {
  build() {
    PatternLock()
      .circleRadius(20)          // 圆点半径
      .sideLength(350)           // 侧边长度
      .strokeWidth(4)            // 连线宽度
      .selectedColor('#FF0000')  // 选中颜色
      .pathColor('#00FF00')      // 路径颜色
      .activeColor('#0000FF')    // 激活颜色
      .regularColor('#CCCCCC')   // 常规颜色
      .activeCircleColor('#FF00FF') // 激活圆圈颜色
      .activeCircleRadius(25)    // 激活圆圈半径
      .enableWaveEffect(true)    // 波纹效果
      .skipUnselectedPoint(true) // 跳过未选中点
  }
}
```

### ArkTS 示例 3: 使用控制器

```typescript
@Entry
@Component
struct PatternLockControllerExample {
  controller: PatternLockController = new PatternLockController()

  build() {
    Column() {
      PatternLock()
        .autoReset(false) // 禁用自动重置

      Button('重置')
        .onClick(() => {
          this.controller.reset() // 手动重置
        })
    }
  }
}
```

### ArkTS 示例 4: 点连接事件

```typescript
@Entry
@Component
struct PatternLockDotConnect {
  @State connectedDots: string = ''

  build() {
    Column() {
      Text(`已连接: ${this.connectedDots}`)
        .margin({ bottom: 20 })

      PatternLock()
        .onDotConnect((index: number) => {
          this.connectedDots += `${index} `
        })
        .onPatternComplete((result: PatternLockChallengeResult) => {
          console.log('完成!', result.choosePoint)
        })
    }
  }
}
```

---

## 测试指南

### 单元测试要点

#### PatternLockPattern 测试

**关键测试场景**:

1. **生命周期测试**:
   - `OnAttachToFrameNode()` - 验证初始化
   - `OnModifyDone()` - 验证属性更新
   - `OnDetachFromFrameNode()` - 验证清理

2. **触摸事件测试**:
   - `OnTouchDown()` - 验证点选择初始化
   - `OnTouchMove()` - 验证点添加逻辑
   - `OnTouchUp()` - 验证完成回调

3. **点检测测试**:
   - `CheckChoosePoint()` - 验证命中检测
   - `CheckInHotSpot()` - 验证热区计算
   - `AddChoosePoint()` - 验证重复选择处理

4. **跳过逻辑测试**:
   - `AddPassPointToChoosePoint()` - 验证中间点添加
   - 各种跳过模式 (对角线、直线)

5. **控制器测试**:
   - `HandleReset()` - 验证重置功能
   - `SetChallengeResult()` - 验证结果设置

#### PatternLockLayoutAlgorithm 测试

**关键测试场景**:

1. **尺寸测量**:
   - 默认尺寸 (300vp)
   - 最小尺寸约束
   - 最大尺寸约束
   - 自定义 sideLength

2. **宽高比**:
   - 验证输出为正方形 (1:1)

#### PatternLockModelNG 测试

**关键测试场景**:

1. **属性设置**:
   - 颜色属性
   - 尺寸属性
   - 布尔属性

2. **事件绑定**:
   - patternComplete 回调
   - dotConnect 回调

3. **静态方法**:
   - 直接操作 FrameNode
   - 属性更新同步

### 测试用例模板

```cpp
// PatternLockPatternTest.cpp

TEST_F(PatternLockPatternTest, OnTouchDown_ShouldInitializeChoosePoint)
{
    // Arrange
    auto pattern = CreatePatternLockPattern();
    TouchLocationInfo info(1);
    info.SetLocalLocation(OffsetF(100, 100));

    // Act
    pattern->OnTouchDown(info);

    // Assert
    EXPECT_TRUE(pattern->choosePoint_.empty());
    EXPECT_EQ(pattern->fingerId_, 1);
}

TEST_F(PatternLockPatternTest, CheckChoosePoint_WithValidOffset_ShouldReturnTrue)
{
    // Arrange
    auto pattern = CreatePatternLockPattern();
    pattern->CalculateCellCenter();
    auto cellCenter = pattern->GetCellCenter(0, 0);

    // Act
    bool result = pattern->CheckChoosePoint(
        cellCenter.GetX(),
        cellCenter.GetY()
    );

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(PatternLockPatternTest, AddChoosePoint_WithDuplicatePoint_ShouldReturnFalse)
{
    // Arrange
    auto pattern = CreatePatternLockPattern();
    PatternLockCell cell(1, 1);
    pattern->choosePoint_.push_back(cell);

    // Act
    bool result = pattern->AddChoosePoint(
        OffsetF(100, 100), 1, 1
    );

    // Assert
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern->choosePoint_.size(), 1);
}

TEST_F(PatternLockPatternTest, AddPassPointToChoosePoint_WithMiddlePoint_ShouldAddMiddle)
{
    // Arrange
    auto pattern = CreatePatternLockPattern();
    pattern->choosePoint_.push_back(PatternLockCell(0, 0));
    std::vector<PatternLockCell> passPointVec;

    // Act
    pattern->AddPassPointToChoosePoint(0, 2, passPointVec);

    // Assert
    EXPECT_EQ(pattern->choosePoint_.size(), 2);
    EXPECT_EQ(pattern->choosePoint_[1].x, 0);
    EXPECT_EQ(pattern->choosePoint_[1].y, 1);
}

TEST_F(PatternLockPatternTest, HandleReset_ShouldClearChoosePoint)
{
    // Arrange
    auto pattern = CreatePatternLockPattern();
    pattern->choosePoint_.push_back(PatternLockCell(0, 0));
    pattern->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern->isMoveEventValid_ = true;

    // Act
    pattern->HandleReset();

    // Assert
    EXPECT_TRUE(pattern->choosePoint_.empty());
    EXPECT_FALSE(pattern->isMoveEventValid_);
}
```

### 分支覆盖要点

#### PatternLockPattern::OnTouchDown

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| 正常流程 | 手指ID有效 | OnTouchDown_WithValidFingerId |
| 多点触控 | 忽略非第一个手指 | OnTouchDown_WithMultipleFingers |

#### PatternLockPattern::AddChoosePoint

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| 不在热区 | 距离 > 半径*1.5 | AddChoosePoint_NotInHotSpot |
| 已选择 | 点在choosePoint_中 | AddChoosePoint_AlreadyChosen |
| 新选择 | 新点 | AddChoosePoint_NewPoint |
| 跳过中间点 | skipUnselectedPoint=true | AddChoosePoint_SkipMiddlePoint |

#### PatternLockPattern::OnTouchUp

| 分支 | 条件 | 测试方法 |
|------|------|----------|
| 自动重置 | autoReset_=true | OnTouchUp_WithAutoReset |
| 不自动重置 | autoReset_=false | OnTouchUp_WithoutAutoReset |
| 成功图案 | choosePoint_.size() >= 4 | OnTouchUp_WithSuccessPattern |
| 失败图案 | choosePoint_.size() < 4 | OnTouchUp_WithFailPattern |

---

## 附录

### A. 源码位置索引

| 文件 | 路径 | 说明 |
|------|------|------|
| Pattern | `components_ng/pattern/patternlock/patternlock_pattern.h/cpp` | Pattern层核心 |
| Model | `components_ng/pattern/patternlock/patternlock_model_ng.h/cpp` | Model层实现 |
| LayoutAlgorithm | `components_ng/pattern/patternlock/patternlock_layout_algorithm.h/cpp` | 布局算法 |
| PaintMethod | `components_ng/pattern/patternlock/patternlock_paint_method.h/cpp` | 绘制方法 |
| Modifier | `components_ng/pattern/patternlock/patternlock_modifier.h/cpp` | 绘制修饰器 |
| LayoutProperty | `components_ng/pattern/patternlock/patternlock_layout_property.h` | 布局属性 |
| PaintProperty | `components_ng/pattern/patternlock/patternlock_paint_property.h` | 绘制属性 |
| EventHub | `components_ng/pattern/patternlock/patternlock_event_hub.h` | 事件处理 |
| Controller | `components_ng/pattern/patternlock/pattern_lock_controller.h/cpp` | 控制器 |
| NAPI | `components_ng/pattern/patternlock/patternlock_napi.h/cpp` | NAPI接口 |

### B. 相关文档

- [CLAUDE.md](../../../../CLAUDE.md) - 项目级指导文档
- [如何新增一个组件.md](../../../../如何新增一个组件.md) - 组件开发指南
- [组件化重构通用方案.md](../../../../组件化重构通用方案.md) - 组件重构方案

### C. 关键常量

| 常量 | 值 | 说明 |
|------|------|------|
| GRID_SIZE | 3 | 九宫格尺寸 (3x3) |
| MIN_SUCCESS_POINTS | 4 | 最小成功点数 |
| DEFAULT_SIDE_LENGTH | 300vp | 默认侧边长度 |
| DEFAULT_CIRCLE_RADIUS | 14vp | 默认圆点半径 |
| DEFAULT_STROKE_WIDTH | 2vp | 默认连线宽度 |
| HOTSPOT_RADIUS_MULTIPLIER | 1.5 | 热区半径倍数 |

### D. 主题系统

PatternLock 使用 `PatternLockTheme` 获取默认样式:

```cpp
auto theme = pipelineContext->GetTheme<V2::PatternLockTheme>();
Color defaultSelectedColor = theme->GetSelectedColor();
Color defaultPathColor = theme->GetPathColor();
float defaultCircleRadius = theme->GetCircleRadius();
```

**主题属性**:
- `selectedColor`: 选中颜色
- `pathColor`: 路径颜色
- `activeColor`: 激活颜色
- `regularColor`: 常规颜色
- `circleRadius`: 圆点半径
- `strokeWidth`: 连线宽度
- `focusColor`: 焦点颜色
- `focusPaintWidth`: 焦点绘制宽度

---

**文档结束**

> **维护说明**: 本文档应随代码更新同步更新,特别是源码位置和 API 变更时。
