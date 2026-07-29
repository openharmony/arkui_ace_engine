# ArkUI ArcScrollBar 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-02-03
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [圆形坐标系](#圆形坐标系)
7. [角度计算逻辑](#角度计算逻辑)
8. [弧形渲染实现](#弧形渲染实现)
9. [与普通ScrollBar的区别](#与普通scrollbar的区别)
10. [与Scroll的交互](#与scroll的交互)
11. [动画系统](#动画系统)
12. [执行流程](#执行流程)
13. [完整API清单](#完整api清单)
14. [关键实现细节](#关键实现细节)
15. [使用示例](#使用示例)
16. [调试指南](#调试指南)
17. [常见问题](#常见问题)
18. [附录](#附录)

---

## 概述

### 组件定位

**ArcScrollBar 组件**是 OpenHarmony ArkUI 框架中的**弧形滚动条组件**，是普通 ScrollBar 的特殊变体，专为圆形设备或特殊 UI 设计而定制。它继承了 ScrollBar 的核心功能，但使用圆形/弧形渲染，提供独特的视觉体验。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：ScrollModelNG (复用普通 ScrollBar 的桥接层)
- **核心层**：NG Pattern 架构 (ArcScrollBarPattern)
- **代理层**：ScrollBarProxy (复用普通 ScrollBar 的代理机制)
- **渲染层**：Rosen + Skia (弧形绘制)

**代码规模**：
- 总文件数：约 6 个文件
- 核心代码：约 3,000+ 行 C++ 代码
- 涉及 3 个架构层次

### 功能特性

ArcScrollBar 组件支持：
- **弧形渲染**：圆形/弧形滚动条，支持全圆或部分弧
- **极坐标系**：使用圆心、半径和角度进行计算
- **位置模式**：支持 LEFT 和 RIGHT 弧形方向
- **双层设计**：背景弧（轨道）+ 前景弧（滑块）
- **交互检测**：基于弧形区域的触摸/悬停检测
- **平滑动画**：
  - 角度过渡动画
  - 透明度变化动画
  - 悬停效果动画
- **兼容性**：完全兼容普通 ScrollBar 的 API 和通信机制

### 设计模式

ArcScrollBar 组件采用 **继承模式** + **NG Pattern 架构**：

```
ScrollBarPattern (普通滚动条基类)
    ↓ 继承
ArcScrollBarPattern (弧形滚动条)
    ├─ 重写布局算法创建
    ├─ 重写绘制方法创建
    └─ 重写滚动条对象创建
         ↓
ArcScrollBar (弧形滚动条对象)
    ├─ 圆形坐标系
    ├─ 角度计算
    └─ 弧形区域检测
```

**核心概念**：

1. **ArcRound**：描述圆心、半径、起始角度、扫描角度
2. **极坐标系**：使用 `(r, θ)` 而非 `(x, y)`
3. **PositionMode**：LEFT/RIGHT 决定弧形方向
4. **双层弧**：背景弧和前景弧分离

### 应用场景

- **圆形设备**：智能手表、圆形旋钮
- **特殊 UI 设计**：需要弧形指示器的场景
- **仪表盘界面**：汽车仪表盘、工业控制面板
- **创意交互**：非传统的滚动条设计

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ Stack() {                                               │
│   Scroll({ scroller: this.scroller }) {                 │
│     // 内容                                              │
│   }                                                     │
│                                                          │
│   ArcScrollBar({ scroller: this.scroller })              │
│     .width(40)                                          │
│     .height(40)                                        │
│ }                                                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model 层 (NG)                                            │
│                                                          │
│ class ArcScrollBarModelNG                                │
│   ↓                                                      │
│ Create(scroller, options)                                │
│   ↓                                                      │
│ 创建 ArcScrollBar FrameNode                               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern 层（业务逻辑）                                     │
│                                                          │
│ class ArcScrollBarPattern : public ScrollBarPattern     │
│   源码：frameworks/core/components_ng/pattern/         │
│         arc_scroll_bar/arc_scroll_bar_pattern.cpp        │
│                                                          │
│ 核心职责：                                                │
│ - 重写弧形布局算法创建                                   │
│ - 重写弧形绘制方法创建                                   │
│ - 创建 ArcScrollBar 对象                                │
│ - 设置透明点击模式                                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Render 层（渲染层）                                      │
│                                                          │
│ class ArcScrollBarPaintMethod                           │
│ class ArcScrollBarOverlayModifier                        │
│                                                          │
│ 核心职责：                                                │
│ - 绘制背景弧                                             │
│ - 绘制前景弧（滑块）                                     │
│ - 处理角度动画                                           │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [弧形滚动条显示在屏幕上]
```

### 2. 弧形渲染调用链

```
触发布局/绘制
    ↓
ArcScrollBarPattern::CreateNodePaintMethod()
    ↓
创建 ArcScrollBarPaintMethod
    ↓
创建 ArcScrollBarOverlayModifier
    ↓
设置弧形参数
    ├─ SetArcRect(arcActiveRect_)
    ├─ SetBackgroundArcRect(arcAarRect_)
    └─ SetPositionMode(positionMode_)
    ↓
ArcScrollBarOverlayModifier::DrawArc()
    ├─ DrawBackgroundArc() - 绘制轨道
    └─ DrawForegroundArc() - 绘制滑块
    ↓
[弧形滚动条渲染完成]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/arc_scroll_bar/
├── arc_scroll_bar_pattern.h                # ArcScrollBarPattern 类定义
├── arc_scroll_bar_pattern.cpp              # ArcScrollBarPattern 实现
├── arc_scroll_bar_layout_algorithm.h       # 弧形布局算法定义
├── arc_scroll_bar_layout_algorithm.cpp     # 弧形布局算法实现
├── arc_scroll_bar_paint_method.h           # 弧形绘制方法定义
└── arc_scroll_bar_paint_method.cpp         # 弧形绘制方法实现

依赖项：
├── ../arc_scroll/inner/arc_scroll_bar.h           # ArcScrollBar 类定义
├── ../arc_scroll/inner/arc_scroll_bar.cpp         # ArcScrollBar 实现
├── ../arc_scroll/inner/arc_scroll_bar_overlay_modifier.h  # 弧形修饰器
├── ../arc_scroll/inner/arc_scroll_bar_overlay_modifier.cpp # 弧形修饰器实现
└── ../../base/geometry/arc_round.h               # ArcRound 几何类
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **arc_scroll_bar_pattern.h/cpp** | 核心业务逻辑 | `ArcScrollBarPattern::CreateNodePaintMethod()`, `UseInnerScrollBar()` |
| **arc_scroll_bar_layout_algorithm.h/cpp** | 弧形布局计算 | `ArcScrollBarLayoutAlgorithm::Measure()`, `Layout()` |
| **arc_scroll_bar_paint_method.h/cpp** | 弧形绘制 | `ArcScrollBarPaintMethod::UpdateOverlayModifier()` |
| **inner/arc_scroll_bar.h** | 弧形滚动条对象 | `ArcScrollBar::InBarTouchRegion()`, `GetPositionAngle()` |
| **inner/arc_scroll_bar_overlay_modifier.h** | 弧形修饰器 | `ArcScrollBarOverlayModifier::DrawArc()`, `SetStartAngle()` |
| **base/geometry/arc_round.h** | 圆形几何类 | `ArcRound::GetPointByAngle()`, `IsInRegion()` |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
ScrollBarPattern (普通滚动条基类)
    ├─ 显示模式管理
    ├─ 位置更新
    └─ 用户交互处理
         ↓
ArcScrollBarPattern (弧形滚动条)
    ├─ 重写布局算法创建
    ├─ 重写绘制方法创建
    └─ 重写滚动条对象创建
```

### 2. 关键类定义

#### ArcScrollBarPattern

**文件**：`arc_scroll_bar_pattern.h:27`

```cpp
class ArcScrollBarPattern : public ScrollBarPattern
{
    DECLARE_ACE_TYPE(ArcScrollBarPattern, ScrollBarPattern);

public:
    ArcScrollBarPattern() = default;
    ~ArcScrollBarPattern() override = default;

    // 重写：创建弧形布局算法
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<ArcScrollBarLayoutAlgorithm>();
        return layoutAlgorithm;
    }

    // 重写：创建弧形绘制方法
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paint = MakeRefPtr<ArcScrollBarPaintMethod>();

        // 创建弧形覆盖修饰器
        auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();

        // 设置弧形参数
        auto scrollBar = GetScrollBar();
        auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
        auto arcScrollBarOverlayModifier =
            AceType::DynamicCast<ArcScrollBarOverlayModifier>(scrollBarOverlayModifier);

        if (arcScrollBar && arcScrollBarOverlayModifier) {
            arcScrollBarOverlayModifier->SetPositionMode(arcScrollBar->GetPositionMode());
            arcScrollBarOverlayModifier->SetArcRect(arcScrollBar->GetArcActiveRect());
            arcScrollBarOverlayModifier->SetBackgroundArcRect(arcScrollBar->GetArcBarRect());
        }

        paint->SetScrollBarOverlayModifier(scrollBarOverlayModifier);
        return paint;
    }

    // 重写：使用内置滚动条
    bool UseInnerScrollBar() const override
    {
        return true;
    }

    // 重写：创建弧形滚动条对象
    RefPtr<ScrollBar> CreateScrollBar() const override
    {
        return AceType::MakeRefPtr<ArcScrollBar>();
    }

    // 重写：OnModifyDone - 设置透明点击模式
    void OnModifyDone() override;
};
```

#### ArcScrollBar (弧形滚动条对象)

**文件**：`../arc_scroll/inner/arc_scroll_bar.h:22`

```cpp
class ArcScrollBar : public ScrollBar
{
    DECLARE_ACE_TYPE(ArcScrollBar, ScrollBar);

public:
    ArcScrollBar() : ScrollBar(DisplayMode::AUTO, ShapeMode::ROUND, PositionMode::RIGHT) {}

    // 弧形区域访问
    const ArcRound& GetArcActiveRect() const { return arcActiveRect_; }
    const ArcRound& GetArcBarRect() const { return arcAarRect_; }

    // 区域检测（圆形坐标）
    bool InBarTouchRegion(const Point& point) const override;
    bool InBarHoverRegion(const Point& point) const override;
    bool InBarRectRegion(const Point& point) const override;

    // 设置弧形区域
    void SetBarRegion(const Offset& offset, const Size& size,
                     const RefPtr<PipelineContext>& context = nullptr) override;
    void SetRoundTrickRegion(double estimatedHeight, double barRegionSize,
                            double activeSize, double activeMainOffset,
                            double normalWidth, const Size& size) override;

    // 弧形偏移计算
    float CalcPatternOffset(float scrollBarOffset) const override;

private:
    ArcRound arcHoverRegion_;       // 悬停区域
    ArcRound arcAarRect_;          // 背景弧形区域
    ArcRound arcActiveRect_;       // 前景弧形区域（滑块）
    ArcRound arcHotZoneRect_;      // 触摸热区
    double trickSweepAngle_;       // 滑块扫描角度
    double trickStartAngle_;       // 滑块起始角度
    double width_;                 // 弧形宽度
    double centerDeviation_;       // 圆心偏移
};
```

#### ArcRound (弧形区域几何类)

**文件**：`frameworks/base/geometry/arc_round.h:33`

```cpp
class ACE_EXPORT ArcRound {
public:
    ArcRound() = default;
    ArcRound(const Point& centerPoint, float radius,
             float startAngle, float sweepAngle, float width);

    // 核心属性
    Point centerPoint_;      // 圆心点
    float radius_;           // 半径
    float startAngle_;       // 起始角度（度）
    float sweepAngle_;       // 扫描角度（度）
    float width_;            // 宽度/粗细
    float outerRadius_;      // 外半径
    Color color_;            // 颜色

    // 核心方法
    void GetPointByAngle(float angle, Point& out) const;
    float GetPositionAngle(const Offset& position) const;
    bool IsInRegion(const Point& point, float minHotRegion = ORG_HOTREGION) const;

    // 静态常量
    static constexpr float HALF_CIRCULARITY = 180.0f;   // 半圆
    static constexpr float WHOLE_CIRCULARITY = 360.0f;  // 全圆
    static constexpr float ORG_HOTREGION = 10.0f;       // 原始热区
};
```

---

## Pattern层详解

### ArcScrollBarPattern 核心职责

**ArcScrollBarPattern** 是弧形滚动条的核心逻辑层，负责：

1. **重写基类方法**
   - 重写 `CreateLayoutAlgorithm()` - 创建弧形布局算法
   - 重写 `CreateNodePaintMethod()` - 创建弧形绘制方法
   - 重写 `UseInnerScrollBar()` - 标记使用内置滚动条
   - 重写 `CreateScrollBar()` - 创建弧形滚动条对象

2. **配置绘制方法**
   - 创建 `ArcScrollBarOverlayModifier`
   - 设置弧形参数（圆心、半径、角度等）
   - 配置位置模式（LEFT/RIGHT）

3. **设置交互模式**
   - 设置透明点击模式（`HTMTRANSPARENT`）
   - 允许点击穿透到底层内容

### 关键生命周期方法

#### OnModifyDone()

**调用时机**：组件属性修改完成时

**源码位置**：`arc_scroll_bar_pattern.cpp:20`

**执行流程**：

```cpp
void ArcScrollBarPattern::OnModifyDone()
{
    // 1. 调用基类的 OnModifyDone
    ScrollBarPattern::OnModifyDone();

    // 2. 获取 FrameNode
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // 3. 获取事件中心
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);

    // 4. 获取手势中心
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    // 5. 设置透明点击模式
    // 这允许点击穿透到底层内容，因为弧形滚动条
    // 通常只占圆环的一部分
    gestureHub->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
}
```

**注意事项**：
- ✅ 必须调用基类的 `OnModifyDone()`
- ✅ 设置 `HTMTRANSPARENT` 模式允许点击穿透
- ✅ 这是弧形滚动条的特殊要求

### 重写方法详解

#### 1. UseInnerScrollBar()

**功能**：标记使用内置滚动条对象

**源码位置**：`arc_scroll_bar_pattern.h:62`

```cpp
bool UseInnerScrollBar() const override
{
    return true;
}
```

**说明**：
- 返回 `true` 表示使用 `ArcScrollBar` 内置对象
- 普通 `ScrollBarPattern` 可能返回 `false`

#### 2. CreateScrollBar()

**功能**：创建弧形滚动条对象

**源码位置**：`arc_scroll_bar_pattern.h:67`

```cpp
RefPtr<ScrollBar> CreateScrollBar() const override
{
    return AceType::MakeRefPtr<ArcScrollBar>();
}
```

**ArcScrollBar 构造函数**：

```cpp
ArcScrollBar::ArcScrollBar()
    : ScrollBar(
        DisplayMode::AUTO,      // 自动显示/隐藏
        ShapeMode::ROUND,        // 圆形模式
        PositionMode::RIGHT      // 右侧位置
      )
{
    // 弧形滚动条初始化
}
```

---

## 圆形坐标系

### 1. 极坐标系统

**普通 ScrollBar**：使用笛卡尔坐标系 `(x, y)`
```
y
↑
│ (x, y)
│
└──────→ x
```

**ArcScrollBar**：使用极坐标系 `(r, θ)`
```
       90°
        ↑
        │
180° ←─ ● ─→ 0°
(圆心) │
        │
       270°
```

### 2. ArcRound 核心属性

**文件**：`frameworks/base/geometry/arc_round.h:33`

```cpp
class ACE_EXPORT ArcRound {
private:
    Point centerPoint_;      // 圆心坐标
    float radius_;           // 半径（像素）
    float startAngle_;       // 起始角度（度）
    float sweepAngle_;       // 扫描角度（度）
    float width_;            // 弧形宽度/粗细（像素）
    float outerRadius_;      // 外半径
    Color color_;            // 颜色

public:
    // 静态常量
    static constexpr float HALF_CIRCULARITY = 180.0f;   // 半圆
    static constexpr float WHOLE_CIRCULARITY = 360.0f;  // 全圆
    static constexpr float ORG_HOTREGION = 10.0f;       // 原始热区
};
```

### 3. 坐标转换方法

#### GetPointByAngle() - 根据角度获取点

**功能**：给定角度，计算弧形上的点坐标

**源码位置**：`frameworks/base/geometry/arc_round.cpp`

```cpp
void ArcRound::GetPointByAngle(float angle, Point& out) const
{
    // 1. 转换为弧度
    float rad = angle * M_PI / 180.0f;

    // 2. 计算圆上的点
    out.SetX(centerPoint_.GetX() + radius_ * std::cos(rad));
    out.SetY(centerPoint_.GetY() + radius_ * std::sin(rad));
}
```

**示例**：
```cpp
ArcRound arc(Point(100, 100), 50, 0, 90, 10);

Point p;
arc.GetPointByAngle(45, p);
// p ≈ (135, 135) - 45° 位置
```

#### GetPositionAngle() - 从位置计算角度

**功能**：给定点坐标，计算相对于圆心的角度

**源码位置**：`frameworks/base/geometry/arc_round.cpp`

```cpp
float ArcRound::GetPositionAngle(const Offset& position) const
{
    // 1. 计算相对坐标
    float dx = position.GetX() - centerPoint_.GetX();
    float dy = position.GetY() - centerPoint_.GetY();

    // 2. 使用 atan2 计算角度（弧度）
    float angleRad = std::atan2(dy, dx);

    // 3. 转换为度数
    float angleDeg = angleRad * 180.0f / M_PI;

    // 4. 归一化到 [0, 360)
    if (angleDeg < 0) {
        angleDeg += 360.0f;
    }

    return angleDeg;
}
```

**示例**：
```cpp
ArcRound arc(Point(100, 100), 50, ...);

float angle = arc.GetPositionAngle(Offset(150, 100));
// angle ≈ 0° - 右方向

float angle = arc.GetPositionAngle(Offset(100, 150));
// angle ≈ 90° - 下方向
```

#### IsInRegion() - 区域检测

**功能**：判断点是否在弧形区域内

**源码位置**：`frameworks/base/geometry/arc_round.cpp`

```cpp
bool ArcRound::IsInRegion(const Point& point, float minHotRegion) const
{
    // 1. 计算点到圆心的距离
    float dx = point.x - centerPoint_.x;
    float dy = point.y - centerPoint_.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    // 2. 检查半径范围
    float innerRadius = radius_ - width_ / 2.0f;
    float outerRadius = radius_ + width_ / 2.0f;

    if (distance < innerRadius - minHotRegion || distance > outerRadius + minHotRegion) {
        return false;  // 不在半径范围内
    }

    // 3. 检查角度范围
    float angle = GetPositionAngle(Offset(point.x, point.y));
    float endAngle = startAngle_ + sweepAngle_;

    // 归一化角度到 [0, 360)
    auto normalizeAngle = [](float a) {
        while (a < 0) a += 360.0f;
        while (a >= 360.0f) a -= 360.0f;
        return a;
    };

    angle = normalizeAngle(angle);
    startAngle_ = normalizeAngle(startAngle_);
    endAngle = normalizeAngle(endAngle);

    // 检查是否在角度范围内
    if (sweepAngle_ > 0) {
        return angle >= startAngle_ && angle <= endAngle_;
    } else {
        return angle <= startAngle_ && angle >= endAngle_;
    }
}
```

### 4. 位置模式

#### RIGHT 模式（默认）

**描述**：弧形从右侧开始，顺时针方向

```
       90°
        ↑
        │
180° ←─ ─→ 0° (起始)
        │
       270°
```

**示例**：
```cpp
ArcScrollBar(PositionMode::RIGHT)
startAngle_ = 0°      // 从 0° 开始
sweepAngle_ = 270°    // 扫描 270°（到顶部）
```

#### LEFT 模式

**描述**：弧形从左侧开始，逆时针方向

```
       90°
        ↑
        │
←── 180°      0°
        │
       270°
```

**示例**：
```cpp
ArcScrollBar(PositionMode::LEFT)
startAngle_ = 180°    // 从 180° 开始
sweepAngle_ = -270°   // 逆时针扫描 270°（到顶部）
```

---

## 角度计算逻辑

### 1. 设置弧形区域

**源码位置**：`inner/arc_scroll_bar.cpp:48`

```cpp
void ArcScrollBar::SetBarRegion(
    const Offset& offset,
    const Size& size,
    const RefPtr<PipelineContext>& context)
{
    // 1. 获取弧形宽度
    double normalWidth = GetNormalWidthToPx();

    // 2. 计算圆心（容器中心）
    Point centerPoint(size.Width() * 0.5, size.Height() * 0.5);

    // 3. 计算起始角度
    double startAngle = GetArcNormalStartAngle();

    // 4. 计算扫描角度（基于位置模式）
    double sweepAngle = (GetPositionMode() == PositionMode::LEFT) ?
                       -GetArcNormalMaxOffsetAngle() :  // LEFT：负角度（逆时针）
                        GetArcNormalMaxOffsetAngle();    // RIGHT：正角度（顺时针）

    // 5. 计算弧形宽度
    double width = NormalizeToPx(GetArcNormalBackgroundWidth());
    centerDeviation_ = width * 0.5;

    // 6. 计算半径（容器半径 - 圆心偏移）
    double radius = size.Width() * 0.5 - centerDeviation_;

    // 7. 创建背景弧形区域
    arcAarRect_ = ArcRound(centerPoint, radius, startAngle, sweepAngle, width);
}
```

**参数说明**：
- `normalWidth`：弧形轨道宽度
- `centerPoint`：圆心（容器中心）
- `startAngle`：起始角度（通常为 0° 或 180°）
- `sweepAngle`：扫描角度（正数为顺时针，负数为逆时针）
- `radius`：半径
- `width`：弧形宽度

### 2. 设置滑块区域

**源码位置**：`inner/arc_scroll_bar.cpp:68`

```cpp
void ArcScrollBar::SetRoundTrickRegion(
    double estimatedHeight,
    double barRegionSize,
    double activeSize,
    double activeMainOffset,
    double normalWidth,
    const Size& size)
{
    // 1. 计算最大角度（通常为 270°）
    double maxAngle = GetArcNormalMaxOffsetAngle();

    // 2. 计算滑块扫描角度（与内容尺寸成正比）
    trickSweepAngle_ = activeSize * maxAngle / barRegionSize;

    // 3. 计算滑块起始角度（与滚动位置成正比）
    trickStartAngle_ = (maxAngle - trickSweepAngle_) * activeMainOffset / (barRegionSize - activeSize);

    // 4. 根据位置模式调整角度方向
    if (GetPositionMode() == PositionMode::LEFT) {
        // LEFT 模式：逆时针
        trickStartAngle_ = 180.0f - trickStartAngle_;
        trickSweepAngle_ = -trickSweepAngle_;
    } else {
        // RIGHT 模式：顺时针
        trickStartAngle_ = trickStartAngle_;
    }

    // 5. 创建前景弧形区域（滑块）
    double radius = size.Width() * 0.5 - centerDeviation_;
    arcActiveRect_ = ArcRound(
        centerPoint_,        // 圆心
        radius,             // 半径
        trickStartAngle_,   // 起始角度（动态）
        trickSweepAngle_,   // 扫描角度（动态）
        normalWidth         // 宽度
    );
}
```

**参数说明**：
- `estimatedHeight`：估算高度
- `barRegionSize`：可滚动区域大小
- `activeSize`：内容大小
- `activeMainOffset`：当前滚动位置
- `normalWidth`：滑块宽度

**计算逻辑**：
```
trickSweepAngle ∝ activeSize / barRegionSize
- 内容越大 → 滑块越长（角度越大）
- 内容越小 → 滑块越短（角度越小）

trickStartAngle ∝ activeMainOffset
- 滚动位置越靠前 → 起始角度越小
- 滚动位置越靠后 → 起始角度越大
```

### 3. 计算滚动偏移

**源码位置**：`inner/arc_scroll_bar.cpp:157`

```cpp
float ArcScrollBar::CalcPatternOffset(float scrollBarOffset) const
{
    // 1. 计算最大角度
    double maxAngle = GetArcNormalMaxOffsetAngle();

    // 2. 计算滑块最大扫描角度
    double maxSweepAngle = trickSweepAngle_;

    // 3. 根据滚动偏移计算角度偏移
    double angleOffset = scrollBarOffset * maxAngle / maxSweepAngle;

    // 4. 根据位置模式调整
    if (GetPositionMode() == PositionMode::LEFT) {
        angleOffset = -angleOffset;  // LEFT 模式：取反
    }

    return static_cast<float>(angleOffset);
}
```

**反向计算**（角度 → 滚动偏移）：
```cpp
float angle = ...;  // 从点击位置计算的角度
float scrollBarOffset = angle * maxSweepAngle / maxAngle;
```

### 4. 角度与滚动位置关系

**RIGHT 模式**：
```
滚动位置 (0.0 ~ 1.0)
    ↓
angle = position × 270°
    ↓
弧从 0°（右） → 270°（顶部）

示例：
position = 0.0 → angle = 0°
position = 0.5 → angle = 135°
position = 1.0 → angle = 270°
```

**LEFT 模式**：
```
滚动位置 (0.0 ~ 1.0)
    ↓
angle = 180° - position × 270°
    ↓
弧从 180°（左） → 270°（顶部）

示例：
position = 0.0 → angle = 180°
position = 0.5 → angle = 45°
position = 1.0 → angle = -90° ≡ 270°
```

---

## 弧形渲染实现

### ArcScrollBarPaintMethod

**文件**：`arc_scroll_bar_paint_method.h:25`

**核心职责**：
- 绘制弧形滚动条
- 管理弧形覆盖修饰器
- 处理绘制上下文

```cpp
class ArcScrollBarPaintMethod : public ScrollBarPaintMethod {
public:
    ArcScrollBarPaintMethod() : ScrollBarPaintMethod(false) {}
    ~ArcScrollBarPaintMethod() override = default;

    // 重写绘制方法
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

private:
    RefPtr<ArcScrollBarOverlayModifier> scrollBarOverlayModifier_;
};
```

### ArcScrollBarOverlayModifier

**文件**：`inner/arc_scroll_bar_overlay_modifier.h:22`

**核心职责**：
- 绘制背景弧
- 绘制前景弧（滑块）
- 管理弧形动画

```cpp
class ArcScrollBarOverlayModifier : public ScrollBarOverlayModifier {
public:
    // 绘制弧形
    void DrawArc(DrawingContext& context);
    void DrawBackgroundArc(DrawingContext& context);

    // 设置弧形参数
    void SetStartAngle(float startAngle);
    void SetSweepAngle(float sweepAngle);
    void SetCurveRadius(float curveRadius);
    void SetArcRect(const ArcRound& arcRect);
    void SetBackgroundArcRect(const ArcRound& backgroundArcRect);
    void SetPositionMode(PositionMode positionMode);

    // 启动动画
    void StartArcBarAnimation(
        HoverAnimationType hoverAnimationType,
        OpacityAnimationType opacityAnimationType,
        bool needAdaptAnimation,
        const ArcRound& arcBarRect,
        const ArcRound& backgroundArcBarRect);

private:
    // 弧形属性
    RefPtr<PropertyFloat> startAngle_;       // 起始角度
    RefPtr<PropertyFloat> sweepAngle_;       // 扫描角度
    RefPtr<PropertyFloat> curveRadius_;      // 曲率半径
    RefPtr<PropertyBool> isAlignCenter_;     // 居中对齐
    RefPtr<PropertyInt> positionMode_;       // 位置模式

    // 弧形区域
    ArcRound arcRect_;             // 前景弧
    ArcRound backgroundArcRect_;   // 背景弧
};
```

### 渲染流程

#### UpdateOverlayModifier() 方法

**源码位置**：`arc_scroll_bar_paint_method.cpp:22`

```cpp
void ArcScrollBarPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = GetScrollBarOverlayModifier();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);

    // 1. 更新位置模式
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }

    // 2. 转换为弧形修饰器
    auto arcScrollBarOverlayModifier =
        AceType::DynamicCast<ArcScrollBarOverlayModifier>(scrollBarOverlayModifier);
    CHECK_NULL_VOID(arcScrollBarOverlayModifier);

    // 3. 转换为弧形滚动条
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    CHECK_NULL_VOID(arcScrollBar);

    // 4. 设置背景颜色
    arcScrollBarOverlayModifier->SetBackgroundBarColor(arcScrollBar->GetArcBackgroundColor());

    // 5. 启动弧形动画
    arcScrollBarOverlayModifier->StartArcBarAnimation(
        arcScrollBar->GetHoverAnimationType(),
        arcScrollBar->GetOpacityAnimationType(),
        arcScrollBar->GetNeedAdaptAnimation(),
        arcScrollBar->GetArcActiveRect(),
        arcScrollBar->GetArcBarRect());

    // 6. 设置滑块颜色
    scrollBarOverlayModifier->SetBarColor(arcScrollBar->GetArcForegroundColor());

    // 7. 重置动画类型
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
```

#### DrawArc() 方法

**源码位置**：`inner/arc_scroll_bar_overlay_modifier.cpp`

```cpp
void ArcScrollBarOverlayModifier::DrawArc(DrawingContext& context)
{
    // 1. 绘制背景弧（轨道）
    DrawBackgroundArc(context);

    // 2. 绘制前景弧（滑块）
    auto arcRect = GetArcRect();
    if (arcRect.GetRadius() > 0.0f && arcRect.GetSweepAngle() != 0.0f) {
        DrawForegroundArc(context, arcRect);
    }
}

void ArcScrollBarOverlayModifier::DrawBackgroundArc(DrawingContext& context)
{
    // 1. 获取背景弧参数
    auto backgroundArcRect = GetBackgroundArcRect();
    Point center = backgroundArcRect.GetCenterPoint();
    float radius = backgroundArcRect.GetRadius();
    float startAngle = backgroundArcRect.GetStartAngle();
    float sweepAngle = backgroundArcRect.GetSweepAngle();
    float width = backgroundArcRect.GetWidth();

    // 2. 创建路径
    auto path = std::make_unique<DrawingPath>();

    // 3. 添加弧形路径
    // 从起始角度扫描到结束角度
    float endAngle = startAngle + sweepAngle;
    path->AddArc(center.x, center.y, radius, startAngle, endAngle);

    // 4. 设置绘制属性
    auto brush = context.GetBrush();
    brush.SetColor(backgroundArcRect.GetColor());
    context.SetBrush(brush);

    auto pen = context.GetPen();
    pen.SetWidth(width);
    context.SetPen(pen);

    // 5. 绘制
    context.DrawPath(*path);
}
```

---

## 与普通ScrollBar的区别

### 1. 继承关系对比

**普通 ScrollBar**：
```
Pattern → ScrollBarPattern
```

**ArcScrollBar**：
```
Pattern → ScrollBarPattern → ArcScrollBarPattern
```

### 2. 渲染方法对比

| 特性 | 普通 ScrollBar | ArcScrollBar |
|-----|---------------|-------------|
| **形状** | 矩形条 | 圆形/弧形 |
| **坐标系** | 笛卡尔 `(x, y)` | 极坐标 `(r, θ)` |
| **位置计算** | 线性插值 | 角度插值 |
| **区域检测** | 矩形边界 | 弧形边界 |
| **PaintMethod** | `ScrollBarPaintMethod` | `ArcScrollBarPaintMethod` |
| **Modifier** | `ScrollBarOverlayModifier` | `ArcScrollBarOverlayModifier` |

### 3. 对象创建对比

**普通 ScrollBar**：
```cpp
RefPtr<ScrollBar> ScrollBarPattern::CreateScrollBar() const
{
    return AceType::MakeRefPtr<ScrollBar>(
        DisplayMode::AUTO,
        ShapeMode::RECT,   // 矩形
        PositionMode::RIGHT
    );
}
```

**ArcScrollBar**：
```cpp
RefPtr<ScrollBar> ArcScrollBarPattern::CreateScrollBar() const
{
    return AceType::MakeRefPtr<ArcScrollBar>(
        DisplayMode::AUTO,
        ShapeMode::ROUND,  // 圆形 ← 关键区别
        PositionMode::RIGHT
    );
}
```

### 4. 交互检测对比

**普通 ScrollBar - 矩形检测**：
```cpp
bool ScrollBar::InBarTouchRegion(const Point& point) const
{
    // 矩形边界检测
    return point.x >= left && point.x <= right &&
           point.y >= top && point.y <= bottom;
}
```

**ArcScrollBar - 弧形检测**：
```cpp
bool ArcScrollBar::InBarTouchRegion(const Point& point) const
{
    // 弧形边界检测
    return arcHotZoneRect_.IsInRegion(point, MIN_HOTREGION.ConvertToPx());
}
```

### 5. 位置更新对比

**普通 ScrollBar - 线性位置**：
```cpp
void ScrollBarPattern::UpdateScrollBarPosition()
{
    float positionRatio = currentOffset_ / scrollableDistance_;
    // 直接使用比例更新位置
    scrollBar_->UpdatePosition(positionRatio);
}
```

**ArcScrollBar - 角度位置**：
```cpp
void ArcScrollBarPattern::UpdateScrollBarPosition()
{
    float positionRatio = currentOffset_ / scrollableDistance_;

    // 转换为角度
    float angle = positionRatio * maxAngle;

    // 更新弧形位置
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar_);
    arcScrollBar->SetCurrentAngle(angle);
}
```

---

## 与Scroll的交互

### 通信方式

ArcScrollBar 通过 **ScrollBarProxy** 与 Scroll 通信，与普通 ScrollBar 相同：

```
Scroll (ScrollablePattern)
    ↓ 注册
ScrollBarProxy (中介)
    ↓ 管理
ArcScrollBar (via ScrollBarPattern)
```

### 注册流程

```cpp
// 1. Scroll 侧注册
void ScrollModelNG::SetScrollBar(DisplayMode displayMode, const std::string& id)
{
    // 创建 ScrollableNodeInfo
    ScrollableNodeInfo scrollableNode;
    scrollableNode.scrollableNode = WeakClaim(this);
    scrollableNode.onPositionChanged = [...] (double distance, ...) {
        // 滚动回调
        pattern->UpdateCurrentOffset(distance, source);
    };

    // 注册到 Proxy
    auto proxy = ScrollBarProxy::GetInstance();
    proxy->RegisterScrollableNode(scrollableNode);
}

// 2. ArcScrollBar 侧注册
void ArcScrollBarPattern::OnAttachToFrameNode()
{
    // 创建 ArcScrollBar 对象
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();

    // 注册到 Proxy
    auto proxy = GetScrollBarProxy();
    if (proxy) {
        proxy->RegisterScrollBar(AceType::WeakClaim(this));
    }
}
```

### 双向通知机制

#### Scroll → ArcScrollBar

```cpp
// Scroll 滚动
bool ScrollPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    currentOffset_ += offset;

    // 通知 ScrollBar 更新
    if (scrollBarProxy_) {
        scrollBarProxy_->NotifyScrollBar(source);
    }

    return true;
}

// Proxy 通知 ArcScrollBar
void ScrollBarProxy::NotifyScrollBar(int32_t scrollSource)
{
    for (auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (scrollBar) {
            scrollBar->SetCurrentPosition(currentOffset_);
            scrollBar->UpdateScrollBarPosition();  // ← ArcScrollBar 重写此方法
        }
    }
}
```

#### ArcScrollBar → Scroll

```cpp
// 用户拖动 ArcScrollBar
void ArcScrollBarPattern::OnDragUpdate(const GestureEvent& info)
{
    // 1. 计算角度偏移
    float angleDelta = CalculateAngleDelta(info);

    // 2. 转换为滚动偏移
    float scrollDelta = CalcPatternOffset(angleDelta);

    // 3. 通知 Proxy
    if (scrollBarProxy_) {
        scrollBarProxy_->NotifyScrollableNode(
            scrollDelta, SCROLL_FROM_BAR, AceType::WeakClaim(this), axis_);
    }
}

// Proxy 通知 Scroll
void ScrollBarProxy::NotifyScrollableNode(float distance, ...) const
{
    for (auto& scrollableNode : scrollableNodes_) {
        if (scrollableNode.onPositionChanged) {
            scrollableNode.onPositionChanged(distance, source, ...);
        }
    }
}
```

---

## 动画系统

### 动画类型

1. **角度动画**：滑块角度平滑过渡
2. **透明度动画**：显示/隐藏淡入淡出
3. **悬停动画**：鼠标悬停效果

### StartArcBarAnimation()

**源码位置**：`inner/arc_scroll_bar_overlay_modifier.cpp`

```cpp
void ArcScrollBarOverlayModifier::StartArcBarAnimation(
    HoverAnimationType hoverAnimationType,
    OpacityAnimationType opacityAnimationType,
    bool needAdaptAnimation,
    const ArcRound& arcBarRect,
    const ArcRound& backgroundArcBarRect)
{
    // 1. 启动悬停动画
    StartHoverAnimation(arcBarRect, backgroundArcBarRect, hoverAnimationType);

    // 2. 设置角度动画属性
    if (needAdaptAnimation) {
        startAngle_->Set(arcBarRect.GetStartAngle());
        sweepAngle_->Set(arcBarRect.GetSweepAngle());
    }

    // 3. 设置半径动画
    curveRadius_->Set(arcBarRect.GetRadius());

    // 4. 启动透明度动画
    if (opacityAnimationType != OpacityAnimationType::NONE) {
        StartOpacityAnimation(opacityAnimationType);
    }
}
```

### 角度过渡动画

```cpp
// 角度属性动画
auto angleAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(
    startAngle,
    endAngle,
    Curves::FAST_OUT_SLOW_IN
);

angleAnimation->AddListener([this](float angle) {
    startAngle_->Set(angle);
    // 触发重绘
    auto host = host_.Upgrade();
    if (host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
});

animation->AddAngleAnimation(angleAnimation);
animation->SetDuration(300);  // 300ms
```

---

## 执行流程

### 1. 初始化流程

```
ArkTS: Scroll() { ... }
    ↓
ScrollModelNG::SetScrollBar(displayMode, id)
    ↓
SetScrollBarArc(...)  ← 弧形配置
    ↓
创建 ArcScrollBarPattern
    ↓
ArcScrollBarPattern::OnAttachToFrameNode()
    ├─ CreateScrollBar() → 创建 ArcScrollBar 对象
    ├─ InitDragEvent() - 初始化拖动手势
    └─ InitMouseEvent() - 初始化鼠标事件
    ↓
注册到 ScrollBarProxy
    ↓
[初始化完成]
```

### 2. 布局流程

```
触发布局
    ↓
ArcScrollBarPattern::CreateLayoutAlgorithm()
    ↓
ArcScrollBarLayoutAlgorithm::Measure()
    ├─ 测量容器尺寸
    └─ 计算圆心和半径
    ↓
ArcScrollBarLayoutAlgorithm::Layout()
    ├─ SetBarRegion() - 设置弧形区域
    └─ SetRoundTrickRegion() - 设置滑块区域
    ↓
[布局完成]
```

### 3. 绘制流程

```
触发绘制
    ↓
ArcScrollBarPaintMethod::UpdateOverlayModifier()
    ↓
获取 ArcScrollBar 对象
    ↓
获取 ArcRound 参数
    ├─ centerPoint（圆心）
    ├─ radius（半径）
    ├─ startAngle（起始角度）
    └─ sweepAngle（扫描角度）
    ↓
ArcScrollBarOverlayModifier::DrawArc()
    ├─ DrawBackgroundArc() - 绘制轨道
    └─ DrawForegroundArc() - 绘制滑块
    ↓
[绘制完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建 ArcScrollBar 组件

```typescript
// 创建弧形滚动条
ArcScrollBar()
ArcScrollBar(options: { scroller: Scroller, state?: ScrollState })

// 滚动控制器（必填）
scroller: Scroller

// 显示状态（可选）
// BarState.Auto - 自动显示/隐藏（默认）
// BarState.On - 始终显示
// BarState.Off - 始终隐藏
```

#### 完整使用示例

```typescript
Stack() {
  // 可滚动组件
  Scroll({ scroller: this.scroller }) {
    // 内容
  }

  // 弧形滚动条
  ArcScrollBar({ scroller: this.scroller })
    .width(40)      // 设置宽度
    .height(40)     // 设置高度
}
```

### 完整 API 映射表

| ArkTS API | Model 层方法 | LayoutProperty | PaintProperty | Pattern 影响 | 说明 |
|-----------|-----------|--------------|---------------|-------------|------|
| `ArcScrollBar({ scroller })` | `Create()` | - | - | 创建 ArcScrollBar FrameNode | 创建弧形滚动条组件 |
| `ArcScrollBar({ state })` | `Create()` | - | - | `displayMode_` | 设置显示状态 |

**注意**：
- ArcScrollBar 是独立组件，需要与可滚动组件（Scroll、ArcList、List、Grid、WaterFlow）配合使用
- 通过 scroller 控制器与可滚动组件绑定
- 必须设置 width 和 height 属性
- 不超出官方 API 文档的范围

### C++ API 列表

#### ArcScrollBarPattern 公共方法

```cpp
// 重写方法
RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
bool UseInnerScrollBar() const override;
RefPtr<ScrollBar> CreateScrollBar() const override;
void OnModifyDone() override;
```

#### ArcScrollBar 公共方法

```cpp
// 弧形区域访问
const ArcRound& GetArcActiveRect() const;
const ArcRound& GetArcBarRect() const;

// 区域检测
bool InBarTouchRegion(const Point& point) const override;
bool InBarHoverRegion(const Point& point) const override;
bool InBarRectRegion(const Point& point) const override;

// 设置弧形区域
void SetBarRegion(const Offset& offset, const Size& size, ...) override;
void SetRoundTrickRegion(double estimatedHeight, double barRegionSize, ...) override;

// 偏移计算
float CalcPatternOffset(float scrollBarOffset) const override;
```

#### ArcRound 公共方法

```cpp
// 构造函数
ArcRound(const Point& centerPoint, float radius,
         float startAngle, float sweepAngle, float width);

// 坐标转换
void GetPointByAngle(float angle, Point& out) const;
float GetPositionAngle(const Offset& position) const;

// 区域检测
bool IsInRegion(const Point& point, float minHotRegion = ORG_HOTREGION) const;

// 静态常量
static constexpr float HALF_CIRCULARITY = 180.0f;
static constexpr float WHOLE_CIRCULARITY = 360.0f;
static constexpr float ORG_HOTREGION = 10.0f;
```

---

## 关键实现细节

### 1. 角度与位置转换

**位置 → 角度**（滚动时）：

```cpp
float PositionToAngle(float position, float maxAngle)
{
    // position: 0.0 ~ 1.0
    // maxAngle: 270° (或 360°)
    return position * maxAngle;
}
```

**角度 → 位置**（点击时）：

```cpp
float AngleToPosition(float angle, float maxAngle)
{
    // angle: 0° ~ 270°
    // maxAngle: 270° (或 360°)
    return angle / maxAngle;
}
```

**角度 → 滚动偏移**：

```cpp
float AngleToScrollOffset(float angle, float scrollableDistance, float maxAngle)
{
    float position = AngleToPosition(angle, maxAngle);
    return position * scrollableDistance;
}
```

### 2. 滑块角度计算

**滑块长度（角度）**：

```cpp
float CalcTrickSweepAngle(float contentSize, float viewportSize, float maxAngle)
{
    float ratio = viewportSize / contentSize;
    return ratio * maxAngle;
}
```

**滑块起始角度**：

```cpp
float CalcTrickStartAngle(float scrollOffset, float scrollableDistance, float maxAngle, float trickSweepAngle)
{
    float movableAngle = maxAngle - trickSweepAngle;
    float position = scrollOffset / scrollableDistance;
    return position * movableAngle;
}
```

### 3. PositionMode 角度调整

```cpp
void AdjustAngleByPositionMode(float& angle, PositionMode mode)
{
    if (mode == PositionMode::LEFT) {
        // LEFT 模式：从 180° 开始，逆时针
        angle = 180.0f - angle;
        if (angle < 0) {
            angle += 360.0f;
        }
    }
    // RIGHT 模式：从 0° 开始，顺时针（无需调整）
}
```

### 4. 透明点击模式

**设置原因**：

弧形滚动条通常只占圆环的一部分（例如 270°），剩余区域应允许点击穿透到底层内容。

**实现**：

```cpp
void ArcScrollBarPattern::OnModifyDone()
{
    ScrollBarPattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    // 设置透明点击模式
    gestureHub->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
}
```

---

## 使用示例

### 示例 1：基础弧形滚动条

```typescript
@Entry
@Component
struct BasicArcScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Stack() {
      Scroll({ scroller: this.scroller }) {
        Column() {
          ForEach(Array.from({ length: 20 }), (_, index) => {
            Text(`Item ${index}`)
              .width('100%')
              .height(80)
          })
        }
      }
      .width('100%')
      .height('100%')
      .scrollable(ScrollDirection.Vertical)

      ArcScrollBar({ scroller: this.scroller })
        .width(40)
        .height(40)
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 2：自定义尺寸弧形滚动条

```typescript
@Entry
@Component
struct CustomSizeArcScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Stack() {
      Scroll({ scroller: this.scroller }) {
        Column() {
          ForEach(Array.from({ length: 20 }), (_, index) => {
            Text(`Item ${index}`)
              .width('100%')
              .height(80)
          })
        }
      }
      .scrollable(ScrollDirection.Vertical)

      ArcScrollBar({ scroller: this.scroller })
        .width(50)      // 自定义宽度
        .height(50)     // 自定义高度
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 3：始终显示弧形滚动条

```typescript
@Entry
@Component
struct AlwaysOnArcScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Stack() {
      Scroll({ scroller: this.scroller }) {
        Column() {
          ForEach(Array.from({ length: 20 }), (_, index) => {
            Text(`Item ${index}`)
              .width('100%')
              .height(80)
          })
        }
      }
      .scrollable(ScrollDirection.Vertical)

      ArcScrollBar({
        scroller: this.scroller,
        state: BarState.On  // 始终显示
      })
        .width(40)
        .height(40)
    }
  }
}
```

### 示例 4：与 ArcList 配合使用

```typescript
@Entry
@Component
struct ArcListWithScrollBar {
  private scroller: Scroller = new Scroller()
  @State items: Array<number> = Array.from({ length: 50 }, (_, i) => i)

  build() {
    Stack() {
      ArcList({ scroller: this.scroller }) {
        ForEach(this.items, (item: number) => {
          ArcListItem() {
            Text(`Item ${item}`)
              .fontSize(16)
          }
        }, (item: number) => item.toString())
      }

      ArcScrollBar({ scroller: this.scroller })
        .width(40)
        .height(40)
    }
  }
}
```

### 示例 5：与 List 配合使用

```typescript
@Entry
@Component
struct ListWithArcScrollBar {
  private scroller: Scroller = new Scroller()
  @State items: Array<number> = Array.from({ length: 100 }, (_, i) => i)

  build() {
    Stack() {
      List({ scroller: this.scroller }) {
        ForEach(this.items, (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .height(60)
          }
        }, (item: number) => item.toString())
      }
      .width('80%')
      .height('100%')
      .edgeEffect(EdgeEffect.Spring)

      ArcScrollBar({ scroller: this.scroller })
        .width(20)
        .height(20)
    }
  }
}
```

### 示例 6：与 Grid 配合使用

```typescript
@Entry
@Component
struct GridWithArcScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Stack() {
      Grid({ scroller: this.scroller }) {
        ForEach(Array.from({ length: 50 }), (_, index) => {
          GridItem() {
            Text(`Item ${index}`)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
          }
          .width(80)
          .height(80)
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsGap(10)
      .columnsGap(10)

      ArcScrollBar({ scroller: this.scroller })
        .width(30)
        .height(30)
    }
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// 弧形滚动条相关日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "ArcScrollBar: startAngle=%{public}f, sweepAngle=%{public}f",
    startAngle, sweepAngle);

// 角度计算日志
TAG_LOGD(AceLogTag::ACE_SCROLL_BAR, "CalcTrickStartAngle: angle=%{public}f", angle);
```

### 2. Dump 调试

**实现 dump 方法**：
```cpp
void ArcScrollBarPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);

    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    CHECK_NULL_VOID(arcScrollBar);

    // 弧形区域信息
    auto arcRect = arcScrollBar->GetArcActiveRect();
    json->Put("centerX", arcRect.GetCenterPoint().x);
    json->Put("centerY", arcRect.GetCenterPoint().y);
    json->Put("radius", arcRect.GetRadius());
    json->Put("startAngle", arcRect.GetStartAngle());
    json->Put("sweepAngle", arcRect.GetSweepAngle());

    // 位置模式
    json->Put("positionMode", static_cast<int>(arcScrollBar->GetPositionMode()));
}
```

### 3. 调试器检查

**关键变量**：
```cpp
// ArcScrollBar 状态
arcAarRect_           // 背景弧形区域
arcActiveRect_        // 前景弧形区域（滑块）
arcHotZoneRect_       // 触摸热区
trickSweepAngle_      // 滑块扫描角度
trickStartAngle_      // 滑块起始角度
centerDeviation_      // 圆心偏移
```

### 4. 常见问题定位

#### 问题 1：弧形不显示

**检查点**：
- `ShapeMode` 是否为 `ROUND`？
- `startAngle` 和 `sweepAngle` 是否有效？
- `radius` 是否大于 0？

**定位方法**：
```cpp
auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
if (arcScrollBar) {
    auto arcRect = arcScrollBar->GetArcActiveRect();
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
        "ArcRect: radius=%{public}f, startAngle=%{public}f, sweepAngle=%{public}f",
        arcRect.GetRadius(), arcRect.GetStartAngle(), arcRect.GetSweepAngle());
}
```

#### 问题 2：点击无响应

**检查点**：
- `IsInRegion()` 返回值
- `MIN_HOTREGION` 是否合理？
- 是否设置了 `HTMTRANSPARENT` 模式？

**定位方法**：
```cpp
bool ArcScrollBar::InBarTouchRegion(const Point& point) const
{
    bool inRegion = arcHotZoneRect_.IsInRegion(point, MIN_HOTREGION.ConvertToPx());
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
        "InBarTouchRegion: point=(%{public}f,%{public}f), inRegion=%{public}d",
        point.x, point.y, inRegion);
    return inRegion;
}
```

#### 问题 3：角度计算错误

**检查点**：
- `trickSweepAngle_` 计算是否正确？
- `trickStartAngle_` 是否在合理范围？
- PositionMode 角度调整是否正确？

**定位方法**：
```cpp
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
    "SetRoundTrickRegion: trickSweepAngle=%{public}f, trickStartAngle=%{public}f, positionMode=%{public}d",
    trickSweepAngle_, trickStartAngle_, static_cast<int>(GetPositionMode()));
```

---

## 常见问题

### Q1: ArcScrollBar 与普通 ScrollBar 如何选择？

**A**:
- **普通 ScrollBar**：适用于矩形界面、桌面应用
- **ArcScrollBar**：适用于圆形设备、特殊 UI 设计

### Q2: ArcScrollBar 如何与 Scroll 配合使用？

**A**:
```typescript
Stack() {
  Scroll({ scroller: this.scroller }) {
    // 内容
  }

  ArcScrollBar({ scroller: this.scroller })
    .width(40)
    .height(40)
}
```

### Q3: ArcScrollBar 支持哪些可滚动组件？

**A**:
- Scroll
- ArcList
- List
- Grid
- WaterFlow

### Q4: ArcScrollBar 的显示状态有哪些？

**A**:
- `BarState.Auto` - 自动显示/隐藏（默认）
- `BarState.On` - 始终显示
- `BarState.Off` - 始终隐藏

### Q5: 为什么 ArcScrollBar 不显示？

**A**:
1. 确保已设置 `width` 和 `height` 属性
2. 确保 `scroller` 与可滚动组件绑定正确
3. 检查可滚动组件的内容是否超出显示区域

### Q6: ArcScrollBar 能与普通 ScrollBar 一起使用吗？

**A**: 不推荐。一个可滚动组件建议只关联一个滚动条。

### Q7: 如何调整 ArcScrollBar 的尺寸？

**A**:
```typescript
ArcScrollBar({ scroller: this.scroller })
  .width(50)   // 设置宽度
  .height(50)  // 设置高度
```

### Q8: ArcScrollBar 适用于哪些场景？

**A**:
- 圆形智能手表
- 圆形旋钮
- 汽车仪表盘
- 工业控制面板
- 创意交互设计

### Q9: ArcScrollBar 需要设置哪些必填属性？

**A**:
- `scroller: Scroller` - 滚动控制器（必填）
- `width: Length` - 宽度（必填）
- `height: Length` - 高度（必填）

### Q10: ArcScrollBar 支持的颜色设置有哪些？

**A**: 当前 ArcScrollBar 组件使用系统默认颜色，暂不支持自定义颜色。

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 弧形滚动条 | ArcScrollBar | 圆形/弧形滚动条 |
| 极坐标 | Polar Coordinates | `(r, θ)` 坐标系 |
| 圆心 | Center Point | 弧形的圆心 |
| 半径 | Radius | 弧形的半径 |
| 起始角度 | Start Angle | 弧形的起始角度（度） |
| 扫描角度 | Sweep Angle | 弧形的扫描角度（度） |
| 位置模式 | PositionMode | LEFT/RIGHT 决定弧形方向 |
| 热区 | Hot Zone | 触摸热区 |
| 轨道 | Background Arc | 背景弧（轨道） |
| 滑块 | Foreground Arc | 前景弧（滑块） |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `arc_scroll_bar_pattern.h` | ~76 | ArcScrollBarPattern 定义 |
| `arc_scroll_bar_pattern.cpp` | ~30 | ArcScrollBarPattern 实现 |
| `arc_scroll_bar_layout_algorithm.h` | ~36 | 布局算法定义 |
| `arc_scroll_bar_layout_algorithm.cpp` | ~61 | 布局算法实现 |
| `arc_scroll_bar_paint_method.h` | ~33 | 绘制方法定义 |
| `arc_scroll_bar_paint_method.cpp` | ~46 | 绘制方法实现 |
| `inner/arc_scroll_bar.h` | ~60 | ArcScrollBar 类定义 |
| `inner/arc_scroll_bar.cpp` | ~174 | ArcScrollBar 实现 |
| `inner/arc_scroll_bar_overlay_modifier.h` | ~70 | 弧形修饰器定义 |
| `base/geometry/arc_round.h` | ~150+ | ArcRound 几何类 |

### C. 相关文档

- [ScrollBar Context](../../kb/components/container/scroll_bar.md)
- [Scroll Context](../../kb/components/container/scroll.md)
- [ArcRound 几何类](../../../base/geometry/arc_round.h)

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-03 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
