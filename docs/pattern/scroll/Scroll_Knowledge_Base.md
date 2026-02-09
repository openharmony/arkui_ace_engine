# ArkUI Scroll 组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-01-30
> **源码版本**：OpenHarmony ace_engine (master 分支)
> **作者**：基于 CLAUDE.md 规范自动生成

---

## 📚 目录

1. [概述](#概述)
2. [完整调用链](#完整调用链)
3. [目录结构](#目录结构)
4. [核心类继承关系](#核心类继承关系)
5. [Pattern层详解](#pattern层详解)
6. [Model层详解](#model层详解)
7. [LayoutAlgorithm层详解](#layoutalgorithm层详解)
8. [属性系统](#属性系统)
9. [事件处理](#事件处理)
10. [滚动控制](#滚动控制)
11. [特殊功能](#特殊功能)
12. [缓存机制](#缓存机制)
13. [执行流程](#执行流程)
14. [完整API清单](#完整api清单)
15. [关键实现细节](#关键实现细节)
16. [滚动边缘效果](#滚动边缘效果)
17. [使用示例](#使用示例)
18. [调试指南](#调试指南)
19. [常见问题](#常见问题)
20. [附录](#附录)

---

## 概述

### 组件定位

**Scroll 组件**是 OpenHarmony ArkUI 框架中的**滚动容器组件**，提供单轴滚动、二维自由滚动、分页滚动、滚动对齐等多种滚动形式，是 ArkUI 中最常用的容器组件之一。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：ScrollModelNG
- **核心层**：NG Pattern 架构 (ScrollPattern)
- **布局算法**：ScrollLayoutAlgorithm
- **渲染层**：Rosen + Skia

**代码规模**：
- 总文件数：约 50 个文件
- 核心代码：约 20,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

Scroll 组件支持：
- **多种滚动模式**：
  - 单轴滚动（垂直/水平）
  - 二维自由滚动 (Axis::FREE)
  - 分页滚动 (enablePaging)
  - 滚动对齐 (scrollSnap)
- **滚动条**：内置滚动条（支持状态显示/隐藏、位置、厚度、颜色定制）
- **边缘效果**：Spring（弹性）、Fade（淡入淡出）、None（无效果）
- **缩放支持**：双指缩放功能
- **滚动事件**：onScroll、onReachStart、onReachEnd、onScrollStart、onScrollStop、onWillScroll、onDidScroll
- **性能优化**：布局缓存、测量缓存（LRU 淘汰策略）
- **无障碍支持**：完整的 Accessibility 支持

### 设计模式

Scroll 组件采用 **NG Pattern 架构**：

```
前端 (ArkTS)
    ↓ (Model Layer)
ScrollModelNG (scroll_model_ng.cpp)
    ↓ (NG Pattern Layer)
ScrollPattern (scroll_pattern.cpp)
    ├─ ScrollablePattern (基类 - 手势处理)
    └─ FreeScrollController (自由滚动控制器)
    ├─ ZoomController (缩放控制器)
    └─ ScrollBar2D (二维滚动条)
    ↓ (NG LayoutAlgorithm Layer)
ScrollLayoutAlgorithm (scroll_layout_algorithm.cpp)
    ↓
渲染显示
```

### 核心概念

**滚动坐标系**：
```
currentOffset_ = 0           → 在顶部
currentOffset_ > 0           → 内容向上偏移（显示上方内容）
currentOffset_ < 0           → 内容向下偏移（显示下方内容）
currentOffset_ = -scrollableDistance_  → 在底部
```

**关键距离**：
- `viewPortLength_`：视口长度（可见区域大小）
- `scrollableDistance_`：可滚动距离（内容尺寸 - 视口尺寸）
- `viewPortExtent_`：内容总尺寸

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ Scroll() {                                              │
│   Scroll({ scroller: this.scroller }) {                 │
│     Text("Item 1")                                      │
│     Text("Item 2")                                      │
│   }                                                     │
│   .width('100%')                                        │
│   .height('100%')                                       │
│   .scrollable(ScrollDirection.Vertical)                │
│   .scrollBar(BarState.Auto)                             │
│   .onScroll((xOffset, yOffset) => {                     │
│     console.info(`onScroll: ${xOffset}, ${yOffset}`)    │
│   })                                                    │
│ }                                                       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (NG)                                         │
│                                                          │
│ class ScrollModelNG                                      │
│   源码：frameworks/core/components_ng/pattern/scroll/     │
│         scroll_model_ng.cpp                               │
│                                                          │
│ 关键方法：                                                │
│ - Create() - 创建 Scroll 节点                           │
│ - SetScrollDirection() - 设置滚动方向                     │
│ - SetScrollBar() - 设置滚动条状态                        │
│ - SetOnScroll() - 注册滚动事件                           │
│                                                          │
│ 执行流程：                                                 │
│ 1. 创建 FrameNode (V2::SCROLL_ETS_TAG)                  │
│ 2. 创建 ScrollPattern                                    │
│ 3. 应用布局属性 (ScrollLayoutProperty)                   │
│ 4. 注册事件 (ScrollEventHub)                             │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (业务逻辑)                                  │
│                                                          │
│ class ScrollPattern : public ScrollablePattern           │
│   源码：frameworks/core/components_ng/pattern/scroll/     │
│         scroll_pattern.cpp                                 │
│                                                          │
│ 核心职责：                                                │
│ - 滚动位置管理 (currentOffset_, scrollableDistance_)     │
│ - 创建布局算法 (CreateLayoutAlgorithm)                   │
│ - 处理滚动事件 (OnScrollCallback)                        │
│ - 管理滚动条 (ScrollBar)                                 │
│ - 管理边缘效果 (EdgeEffect)                               │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                          │
│                                                          │
│ class ScrollLayoutAlgorithm : public LayoutAlgorithm     │
│   源码：frameworks/core/components_ng/pattern/scroll/     │
│         scroll_layout_algorithm.cpp                       │
│                                                          │
│ 核心方法：                                                │
│ - Measure() - 测量子节点                                 │
│ - Layout() - 应用滚动偏移                                │
│ - CalcContentOffset() - 计算内容偏移                      │
│ - UseInitialOffset() - 应用初始偏移                      │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [滚动显示在屏幕上]
```

### 2. 滚动操作完整调用链

#### 用户滑动手势 → 偏移量更新

```
用户手指滑动
    ↓
PanGestureRecognizer (识别滑动手势)
    ↓
ScrollablePattern::HandleScrollDelta()
    ↓
ScrollPattern::UpdateCurrentOffset(float offset, int32_t source)
    ↓
① ValidateOffset() - 验证偏移量是否合法
② 调整偏移量（考虑边界、边缘效果）
③ 更新 currentOffset_
④ FireObserverTwoDimensionOnWillScroll() - 触发 onWillScroll
⑤ 更新布局（请求新帧）
⑥ FireOnDidScroll() - 触发 onDidScroll
    ↓
OnScrollEndCallback() - 滚动结束
    ↓
FireOnReachStart() / FireOnReachEnd() - 如果到达边界
```

#### ScrollTo() API 调用链

```
scroller.scrollTo() (ArkTS)
    ↓
ScrollPositionController::ScrollTo()
    ↓
ScrollPattern::ScrollTo(float position)
    ↓
① ValidateOffset() - 验证目标位置
② JumpToPosition() - 跳转到指定位置
③ UpdateCurrentOffset() - 更新偏移量
④ 请求重新布局
    ↓
[滚动到目标位置]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/scroll/
├── scroll_pattern.h                    # ScrollPattern 主类定义
├── scroll_pattern.cpp                  # ScrollPattern 实现
├── scroll_layout_algorithm.h           # 布局算法定义
├── scroll_layout_algorithm.cpp         # 布局算法实现
├── scroll_layout_property.h            # 布局属性定义
├── scroll_paint_method.h               # 绘制方法
├── scroll_paint_method.cpp             # 绘制方法实现
├── scroll_event_hub.h                  # 事件中心
├── scroll_accessibility_property.h     # 无障碍属性
├── scroll_content_modifier.h           # 内容修饰器
├── scroll_content_modifier.cpp         # 内容修饰器实现
├── scroll_edge_effect.h                # 边缘效果接口
│
├── Model 层
├── scroll_model_ng.h                   # NG Model 定义
├── scroll_model_ng.cpp                 # NG Model 实现
├── scroll_model.h                      # 基础 Model 接口
├── scroll_model.cpp                    # 基础 Model 实现
├── scroll_model_static.h               # 静态 Model
├── scroll_model_static.cpp             # 静态 Model 实现
│
├── 控制器
├── free_scroll_controller.h            # 自由滚动控制器
├── free_scroll_controller.cpp          # 自由滚动控制器实现
├── zoom_controller.h                   # 缩放控制器
├── zoom_controller.cpp                 # 缩放控制器实现
│
├── 滚动条
├── inner/
│   ├── scroll_bar.h                    # 滚动条基类
│   ├── scroll_bar.cpp                  # 滚动条实现
│   ├── scroll_bar_2d.h                 # 二维滚动条
│   ├── scroll_bar_2d.cpp               # 二维滚动条实现
│   ├── scroll_bar_2d_painter.h         # 二维滚动条绘制器
│   ├── scroll_bar_2d_painter.cpp       # 二维滚动条绘制器实现
│   ├── scroll_bar_overlay_modifier.h   # 滚动条覆盖修饰器
│   └── scroll_bar_overlay_modifier.cpp # 滚动条覆盖修饰器实现
│
├── 边缘效果
├── effect/
│   ├── scroll_fade_effect.h            # 淡入淡出效果
│   ├── scroll_fade_effect.cpp          # 淡入淡出效果实现
│   ├── scroll_fade_controller.h        # 淡入淡出控制器
│   ├── scroll_fade_controller.cpp      # 淡入淡出控制器实现
│   ├── scroll_fade_painter.h           # 淡入淡出绘制器
│   └── scroll_fade_painter.cpp         # 淡入淡出绘制器实现
│
└── 文档
    ├── CLAUDE.md                       # 子目录规则（英文）
    ├── CLAUDE_ZH.md                    # 子目录规则（中文）
    └── claude-ZH.md                    # 临时中文文档
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **scroll_pattern.h/cpp** | 核心业务逻辑 | `ScrollPattern::OnModifyDone()`, `OnScrollCallback()` |
| **scroll_layout_algorithm.h/cpp** | 布局计算 | `ScrollLayoutAlgorithm::Measure()`, `Layout()` |
| **scroll_model_ng.h/cpp** | ArkTS API 接口 | `ScrollModelNG::Create()`, `SetScrollDirection()` |
| **free_scroll_controller.h/cpp** | 二维滚动控制 | `FreeScrollController::ScrollBy()` |
| **zoom_controller.h/cpp** | 缩放控制 | `ZoomController::HandlePinch()` |
| **scroll_bar.h/cpp** | 滚动条实现 | `ScrollBar::UpdatePosition()` |
| **scroll_fade_effect.h/cpp** | 淡入淡出效果 | `ScrollFadeEffect::PerformScroll()` |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
ScrollablePattern (滚动基类)
    ├─ 手势识别 (PanGestureRecognizer)
    ├─ 滚动控制器 (ScrollPositionController)
    ├─ 边缘效果 (EdgeEffect)
    └─ 滚动事件处理
         ↓
ScrollPattern (Scroll 组件实现)
    ├─ 单轴滚动逻辑
    ├─ 布局算法创建
    ├─ 滚动条管理
    ├─ ScrollSnap（滚动对齐）
    ├─ Paging（分页）
    ├─ FreeScroll（二维滚动）
    └─ Zoom（缩放）
```

### 2. 关键类定义

#### ScrollPattern

**文件**：`scroll_pattern.h:44`

```cpp
class ACE_FORCE_EXPORT ScrollPattern : public ScrollablePattern
{
    DECLARE_ACE_TYPE(ScrollPattern, ScrollablePattern);

public:
    ScrollPattern() : ScrollablePattern(EdgeEffect::NONE, true) {}

    // 核心状态变量
    double currentOffset_ = 0.0;           // 当前滚动偏移量
    double scrollableDistance_ = 0.0;      // 可滚动距离
    float viewPortLength_ = 0.0f;          // 视口长度
    SizeF viewPort_;                        // 视口尺寸
    SizeF viewPortExtent_;                  // 内容总尺寸

    // ScrollSnap
    std::vector<float> snapOffsets_;       // 对齐点列表
    std::vector<Dimension> snapPaginations_; // 分页点列表

    // Paging
    ScrollPagingStatus enablePagingStatus_ = ScrollPagingStatus::NONE;

    // 自由滚动
    RefPtr<FreeScrollController> freeScroll_;

    // 缩放
    RefPtr<ZoomController> zoomCtrl_;
    float maxZoomScale_ = 1.0f;
    float minZoomScale_ = 1.0f;
    std::optional<float> zoomScale_;

    // 缓存
    std::list<ScrollLayoutInfo> scrollLayoutInfos_;
    std::list<ScrollMeasureInfo> scrollMeasureInfos_;
};
```

#### ScrollLayoutAlgorithm

**文件**：`scroll_layout_algorithm.h:33`

```cpp
class ACE_EXPORT ScrollLayoutAlgorithm : public LayoutAlgorithm
{
    DECLARE_ACE_TYPE(ScrollLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit ScrollLayoutAlgorithm(double currentOffset, float crossOffset = 0.0f)
        : crossOffset_(crossOffset), currentOffset_(currentOffset) {}

    // 布局方法
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    // 状态获取
    double GetCurrentOffset() const { return currentOffset_; }
    float GetScrollableDistance() const { return scrollableDistance_; }
    const SizeF& GetViewPort() const { return viewPort_; }
    const SizeF& GetViewPortExtent() const { return viewPortExtent_; }

private:
    float crossOffset_;
    double currentOffset_ = 0.0f;
    double scrollableDistance_ = 0.0f;
    float viewPortLength_ = 0.0f;
    SizeF viewPort_;        // 视口尺寸
    SizeF viewPortExtent_;  // 内容尺寸
    SizeF viewSize_;        // Scroll 组件尺寸
};
```

#### ScrollModelNG

**文件**：`scroll_model_ng.h`

```cpp
class ScrollModelNG : public ScrollModel
{
public:
    // 创建 Scroll 节点
    static void Create();

    // 设置滚动方向
    void SetScrollDirection(ScrollDirection direction);

    // 设置滚动条
    void SetScrollBar(DisplayMode displayMode, const std::string& id = "");

    // 设置边缘效果
    void SetEdgeEffect(EdgeEffect edgeEffect);

    // 注册滚动事件
    void SetOnScroll(ScrollEventFunc&& onScroll);
    void SetOnReachStart(ReachEventFunc&& onReachStart);
    void SetOnReachEnd(ReachEventFunc&& onReachEnd);

    // 设置滚动对齐
    void SetScrollSnap(ScrollSnapAlign snapAlign, uint32_t snapInterval);
    void SetScrollSnapPagination(const std::vector<Dimension>& snapPaginations);

    // 设置分页
    void SetEnablePaging(bool enablePaging);

    // 设置初始偏移
    void SetInitialOffset(const OffsetT<CalcDimension>& offset);

    // 设置缩放
    void SetMaxZoomScale(float scale);
    void SetMinZoomScale(float scale);
};
```

---

## Pattern层详解

### ScrollPattern 核心职责

**ScrollPattern** 是 Scroll 组件的核心逻辑层，负责：

1. **滚动位置管理**
   - 维护 `currentOffset_`（当前偏移量）
   - 计算 `scrollableDistance_`（可滚动距离）
   - 管理边界判断（`IsAtTop()`, `IsAtBottom()`, `IsOutOfBoundary()`）

2. **布局算法协调**
   - 在 `CreateLayoutAlgorithm()` 中创建 `ScrollLayoutAlgorithm` 实例
   - 传递 `currentOffset_` 给 LayoutAlgorithm
   - 在 `OnDirtyLayoutWrapperSwap()` 中接收布局结果

3. **滚动事件处理**
   - 处理滚动回调：`OnScrollCallback(float offset, int32_t source)`
   - 触发滚动事件：`FireOnDidScroll(float scroll)`
   - 管理边缘到达事件：`FireOnReachStart()`, `FireOnReachEnd()`

4. **特殊功能**
   - ScrollSnap（滚动对齐）：`CaleSnapOffsets()`, `CalcPredictSnapOffset()`
   - Paging（分页滚动）：`GetPagingOffset()`, `ScrollPage()`
   - FreeScroll（二维自由滚动）：`FreeScrollBy()`, `FreeScrollTo()`
   - Zoom（缩放）：`ProcessZoomScale()`, `UpdatePinchGesture()`

### 关键生命周期方法

#### 1. OnModifyDone()

**调用时机**：组件属性修改完成时

**源码位置**：`scroll_pattern.cpp`

**执行流程**：
```cpp
void ScrollPattern::OnModifyDone()
{
    // 1. 处理轴变化
    auto axis = GetAxis();
    if (axis != lastAxis_) {
        // 重置位置
        ResetPosition();
        lastAxis_ = axis;
    }

    // 2. 初始化自由滚动控制器
    if (axis == Axis::FREE && !freeScroll_) {
        freeScroll_ = AceType::MakeRefPtr<FreeScrollController>(GetHost());
    }

    // 3. 设置滚动条
    SetScrollBarDisplay();

    // 4. 设置边缘效果
    HandleScrollEffect();

    // 5. 注册事件
    RegisterScrollBarEventTask();

    // 6. 计算 ScrollSnap 对齐点
    if (scrollSnapUpdate_) {
        CaleSnapOffsets(host);
        scrollSnapUpdate_ = false;
    }

    // 7. 处理缩放手势
    UpdatePinchGesture();
}
```

**注意事项**：
- ⚠️ **不要在 OnModifyDone 中触发布局**
- ⚠️ **此时 geometryNode 可能还没有更新**
- ✅ **可以访问 LayoutProperty 和 EventHub**

#### 2. OnDirtyLayoutWrapperSwap()

**调用时机**：布局结果交换时

**源码位置**：`scroll_pattern.cpp`

**执行流程**：
```cpp
bool ScrollPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    // 1. 获取 LayoutAlgorithm
    auto algorithm = DynamicCast<ScrollLayoutAlgorithm>(
        dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(algorithm, false);

    // 2. 同步布局结果
    scrollableDistance_ = algorithm->GetScrollableDistance();
    viewPort_ = algorithm->GetViewPort();
    viewPortExtent_ = algorithm->GetViewPortExtent();
    viewSize_ = algorithm->GetViewSize();

    // 3. 添加布局缓存
    if (dirty->ConstraintChanged() ||
        lastViewSize != viewSize_ ||
        lastViewPortExtent != viewPortExtent_) {
        AddScrollLayoutInfo();
    }

    // 4. 更新滚动条
    UpdateScrollBarOffset();

    // 5. 检查是否到达边界
    CheckScrollToEdge();

    return true;
}
```

**注意事项**：
- ✅ **这是访问布局结果的正确时机**
- ✅ **可以安全地获取 geometryNode 数据**
- ⚠️ **不要在此方法中修改 LayoutProperty**

#### 3. OnScrollCallback()

**调用时机**：滚动发生时（由手势触发）

**源码位置**：`scroll_pattern.cpp`

**执行流程**：
```cpp
bool ScrollPattern::OnScrollCallback(float offset, int32_t source)
{
    // 1. 计算预测偏移（考虑 ScrollSnap）
    std::optional<float> predictSnapOffset;
    if (IsScrollSnap() && source != SCROLL_FROM_ANIMATION) {
        predictSnapOffset = CalcPredictSnapOffset(offset, 0.0f, 0.0f);
    }

    // 2. 更新当前偏移
    bool result = UpdateCurrentOffset(offset, source);

    // 3. 触发滚动事件
    FireOnDidScroll(offset);

    // 4. 检查边界
    if (IsAtTop()) {
        FireOnReachStart(onReachStart_, onJSFrameNodeReachStart_);
    }
    if (IsAtBottom()) {
        FireOnReachEnd(onReachEnd_, onJSFrameNodeReachEnd_);
    }

    return result;
}
```

**注意事项**：
- ⚠️ **此方法会在滚动过程中频繁调用**
- ⚠️ **避免在回调中执行重计算**
- ✅ **使用 OnScrollEndCallback 处理批量更新**

### 状态变量详解

#### currentOffset_

**含义**：当前滚动偏移量

**坐标系**：
```
currentOffset_ = 0              → 在顶部
currentOffset_ > 0              → 内容向上偏移
currentOffset_ < 0              → 内容向下偏移
currentOffset_ = -scrollableDistance_ → 在底部
```

**更新时机**：
- 用户滑动手势
- 调用 `ScrollTo()` API
- 调用 `ScrollBy()` API
- ScrollSnap 动画

#### scrollableDistance_

**含义**：可滚动距离

**计算公式**：
```
scrollableDistance_ = max(0, contentSize - viewportSize)
```

**更新时机**：
- 内容尺寸变化
- 视口尺寸变化
- 在 `ScrollLayoutAlgorithm::Measure()` 中重新计算

#### viewPortLength_

**含义**：视口长度（滚动方向上的可见区域大小）

**计算**：
```
垂直滚动：viewPortLength_ = viewPort_.Height()
水平滚动：viewPortLength_ = viewPort_.Width()
```

### ScrollPattern 与 LayoutAlgorithm 的数据流

```
Pattern (scroll_pattern.cpp)
    ↓ 创建时
LayoutAlgorithm (scroll_layout_algorithm.cpp)
    ├─ 构造函数接收 currentOffset_
    ↓ Measure/Layout 计算
    ├─ 计算 scrollableDistance_
    ├─ 计算 viewPort_
    ├─ 计算 viewPortExtent_
    ↓ 返回结果
Pattern (OnDirtyLayoutWrapperSwap)
    ├─ 同步 scrollableDistance_
    ├─ 同步 viewPort_
    └─ 同步 viewPortExtent_
```

**关键约束**：
- ❌ LayoutAlgorithm 不应该直接访问 Pattern
- ❌ Pattern 不应该在布局过程中修改 LayoutAlgorithm 的状态
- ✅ 两者通过构造函数和返回值传递数据

---

## Model层详解

### ScrollModelNG 核心职责

**ScrollModelNG** 提供 ArkTS 声明式 API，负责：

1. **创建 Scroll 节点**
2. **设置布局属性**（通过 ScrollLayoutProperty）
3. **注册事件处理**（通过 ScrollEventHub）
4. **管理滚动控制器**（ScrollPositionController）

### 关键 API 方法

#### 1. Create()

**源码位置**：`scroll_model_ng.cpp`

**功能**：创建 Scroll FrameNode

```cpp
void ScrollModelNG::Create()
{
    // 1. 创建 Scroll FrameNode
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG,
        MakeRefPtr<ScrollPattern>());

    // 2. 添加到 ViewStack
    ViewStackProcessor::GetInstance()->Push(frameNode);

    // 3. 设置默认属性
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDirection(FlexDirection::COLUMN); // 默认垂直滚动
}
```

**对应 ArkTS**：
```typescript
Scroll() {
  // 子组件
}
```

#### 2. SetScrollDirection()

**源码位置**：`scroll_model_ng.cpp`

**功能**：设置滚动方向

```cpp
void ScrollModelNG::SetScrollDirection(ScrollDirection direction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);

    // 设置 Axis
    Axis axis = Axis::VERTICAL;
    switch (direction) {
        case ScrollDirection::VERTICAL:
            axis = Axis::VERTICAL;
            pattern->SetDirection(FlexDirection::COLUMN);
            break;
        case ScrollDirection::HORIZONTAL:
            axis = Axis::HORIZONTAL;
            pattern->SetDirection(FlexDirection::ROW);
            break;
        case ScrollDirection::NONE:
            axis = Axis::NONE;
            break;
        case ScrollDirection::FREE:
            axis = Axis::FREE;
            break;
    }

    // 更新 LayoutProperty
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetScrollDirection(axis);
}
```

**对应 ArkTS**：
```typescript
.scrollable(ScrollDirection.Vertical)
```

#### 3. SetScrollBar()

**源码位置**：`scroll_model_ng.cpp`

**功能**：设置滚动条状态

```cpp
void ScrollModelNG::SetScrollBar(DisplayMode displayMode, const std::string& id)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    // 设置滚动条显示模式
    layoutProperty->SetScrollBarDisplay(displayMode);

    // 如果提供了 ID，创建滚动条控制器
    if (!id.empty()) {
        auto proxy = ScrollBarProxy::GetInstance();
        proxy->RegisterScrollBarId(id, frameNode->GetId());
    }
}
```

**对应 ArkTS**：
```typescript
.scrollBar(BarState.Auto)
.scrollBar(BarState.Off)
.scrollBar(BarState.On)
```

#### 4. SetOnScroll()

**源码位置**：`scroll_model_ng.cpp`

**功能**：注册滚动事件回调

```cpp
void ScrollModelNG::SetOnScroll(ScrollEventFunc&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    // 设置 onScroll 回调
    eventHub->SetOnScroll(std::move(onScroll));
}
```

**对应 ArkTS**：
```typescript
.onScroll((xOffset: number, yOffset: number) => {
  console.info(`onScroll: ${xOffset}, ${yOffset}`)
})
```

#### 5. SetScrollSnap()

**源码位置**：`scroll_model_ng.cpp`

**功能**：设置滚动对齐

```cpp
void ScrollModelNG::SetScrollSnap(
    ScrollSnapAlign snapAlign,
    uint32_t snapInterval)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);

    // 设置对齐方式
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->SetScrollSnapAlign(snapAlign);

    // 设置对齐间隔
    if (snapInterval > 0) {
        Dimension interval(snapInterval, DimensionUnit::VP);
        pattern->SetIntervalSize(interval);
        pattern->SetScrollSnapUpdate(true);
    }
}
```

**对应 ArkTS**：
```typescript
.scrollSnap({
  snapAlign: ScrollSnapAlign.START,
  snapInterval: 100
})
```

### 完整 API 映射表

| ArkTS API | ScrollModelNG 方法 | LayoutProperty | Pattern 影响 |
|-----------|-------------------|----------------|-------------|
| `.scrollable(direction)` | `SetScrollDirection()` | `SetScrollDirection()` | 设置 Axis |
| `.scrollBar(mode)` | `SetScrollBar()` | `SetScrollBarDisplay()` | 创建 ScrollBar |
| `.edgeEffect(effect)` | `SetEdgeEffect()` | `SetEdgeEffect()` | 创建 EdgeEffect |
| `.onScroll(callback)` | `SetOnScroll()` | - | 注册事件回调 |
| `.onReachStart(callback)` | `SetOnReachStart()` | - | 注册边界事件 |
| `.onReachEnd(callback)` | `SetOnReachEnd()` | - | 注册边界事件 |
| `.scrollSnap(config)` | `SetScrollSnap()` | `SetScrollSnapAlign()` | 计算 snapOffsets_ |
| `.enablePaging(enable)` | `SetEnablePaging()` | - | 设置 enablePagingStatus_ |
| `.scrollIntoView(id)` | `ScrollIntoView()` | - | 调用 ScrollToNode |
| `.initialOffset(offset)` | `SetInitialOffset()` | - | 设置 initialOffset_ |

---

## LayoutAlgorithm层详解

### ScrollLayoutAlgorithm 核心职责

**ScrollLayoutAlgorithm** 负责滚动容器的布局计算：

1. **Measure（测量）**：
   - 测量子节点尺寸
   - 计算内容总尺寸（`viewPortExtent_`）
   - 计算可滚动距离（`scrollableDistance_`）

2. **Layout（布局）**：
   - 应用滚动偏移量（`currentOffset_`）
   - 定位子节点
   - 处理初始偏移（`initialOffset_`）

### Measure() 方法详解

**源码位置**：`scroll_layout_algorithm.cpp`

**执行流程**：
```cpp
void ScrollLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // 1. 测量自身尺寸
    auto selfLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto selfIdealSize = layoutWrapper->GetLayoutProperty()->GetCalcIdealSize();

    // 2. 测量子节点
    auto childLayoutConstraint = CalculateChildLayoutConstraint(
        selfLayoutConstraint, selfIdealSize);
    MeasureChild(layoutWrapper, childLayoutConstraint);

    // 3. 计算内容尺寸
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
    viewPortExtent_ = childSize;

    // 4. 计算视口尺寸
    viewSize_ = GetLayoutSize(selfLayoutConstraint, selfIdealSize);
    viewPort_ = viewSize_ - padding;

    // 5. 计算可滚动距离
    float contentMainSize = GetMainSize(viewPortExtent_, axis);
    float viewPortMainSize = GetMainSize(viewPort_, axis);
    scrollableDistance_ = std::max(0.0f, contentMainSize - viewPortMainSize);

    // 6. 应用初始偏移
    UseInitialOffset(axis, viewSize_, layoutWrapper);
}
```

**关键计算**：
```
scrollableDistance_ = max(0, contentSize - viewportSize)
```

### Layout() 方法详解

**源码位置**：`scroll_layout_algorithm.cpp`

**执行流程**：
```cpp
void ScrollLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // 1. 获取子节点
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);

    // 2. 计算内容偏移
    CalcContentOffset(layoutWrapper);

    // 3. 应用滚动偏移
    auto childGeometryNode = childWrapper->GetGeometryNode();
    OffsetF offset = CalculateOffset(currentOffset_, contentStartOffset_);
    childGeometryNode->SetMarginFrameOffset(offset);

    // 4. 定位子节点
    childWrapper->GetLayoutProperty()->UpdateAlignment(
        Alignment::TOP_LEFT, axis);
    childWrapper->Layout();
}
```

### CalcContentOffset() 方法

**源码位置**：`scroll_layout_algorithm.cpp`

**功能**：计算内容起始和结束偏移

```cpp
void ScrollLayoutAlgorithm::CalcContentOffset(LayoutWrapper* layoutWrapper)
{
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();

    // 计算内容在视口中的偏移
    float contentMainSize = GetMainSize(childSize, axis);
    float viewPortMainSize = GetMainSize(viewPort_, axis);

    if (contentMainSize < viewPortMainSize) {
        // 内容小于视口，计算居中偏移
        contentStartOffset_ = (viewPortMainSize - contentMainSize) / 2.0f;
        contentEndOffset_ = contentStartOffset_;
    } else {
        // 内容大于视口，无偏移
        contentStartOffset_ = 0.0f;
        contentEndOffset_ = 0.0f;
    }
}
```

### UseInitialOffset() 方法

**源码位置**：`scroll_layout_algorithm.cpp`

**功能**：应用初始偏移量

```cpp
void ScrollLayoutAlgorithm::UseInitialOffset(
    Axis axis,
    SizeF selfSize,
    LayoutWrapper* layoutWrapper)
{
    // 从 Pattern 获取 initialOffset
    auto host = layoutWrapper->GetHostNode();
    auto pattern = host->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);

    if (!pattern->NeedSetInitialOffset()) {
        return;
    }

    auto initialOffset = pattern->GetInitialOffset();
    OffsetT<CalcDimension> offset = initialOffset;

    // 计算偏移量（转换为像素）
    float offsetValue = 0.0f;
    if (axis == Axis::VERTICAL) {
        offsetValue = ConvertDimensionToPx(offset.y, selfSize.Height()).value_or(0.0f);
    } else if (axis == Axis::HORIZONTAL) {
        offsetValue = ConvertDimensionToPx(offset.x, selfSize.Width()).value_or(0.0f);
    }

    // 应用偏移
    currentOffset_ = -offsetValue;
}
```

---

## 属性系统

### ScrollLayoutProperty

**文件**：`scroll_layout_property.h`

**核心属性**：

```cpp
class ScrollLayoutProperty : public LayoutProperty {
public:
    // 滚动方向
    void SetScrollDirection(Axis axis);
    Axis GetScrollDirection() const;

    // 滚动条显示模式
    void SetScrollBarDisplay(DisplayMode mode);
    DisplayMode GetScrollBarDisplay() const;

    // 边缘效果
    void SetEdgeEffect(EdgeEffect edgeEffect);
    EdgeEffect GetEdgeEffect() const;

    // 滚动对齐
    void SetScrollSnapAlign(ScrollSnapAlign align);
    ScrollSnapAlign GetScrollSnapAlign() const;

    // 初始偏移
    void SetInitialOffset(const OffsetT<CalcDimension>& offset);
    OffsetT<CalcDimension> GetInitialOffset() const;
};
```

### 属性传递流程

```
ArkTS API
    ↓
ScrollModelNG::SetXXX()
    ↓
ScrollLayoutProperty::SetXXX()
    ↓
OnModifyDone() (触发模式修改)
    ↓
ScrollPattern 读取属性
    ↓
应用相应逻辑
```

---

## 事件处理

### 事件类型

Scroll 组件支持以下事件：

| 事件 | 触发时机 | 注册方法 |
|-----|---------|---------|
| **onScroll** | 滚动进行中 | `SetOnScroll()` |
| **onScrollStart** | 滚动开始 | `SetOnScrollStart()` |
| **onScrollStop** | 滚动停止 | `SetOnScrollStop()` |
| **onReachStart** | 到达顶部 | `SetOnReachStart()` |
| **onReachEnd** | 到达底部 | `SetOnReachEnd()` |
| **onWillScroll** | 即将滚动（可拦截） | `SetOnWillScroll()` |
| **onDidScroll** | 滚动完成 | `SetOnDidScroll()` |

### 事件触发顺序

```
OnScrollStart()           // 滚动开始
    ↓
OnWillScroll()            // 即将滚动（可拦截）
    ↓
UpdateCurrentOffset()     // 更新偏移量
    ↓
OnScroll()                // 滚动进行中（可能多次调用）
    ↓
OnScrollStop()            // 滚动停止
    ↓
OnDidScroll()             // 滚动完成
    ↓
OnReachStart/OnReachEnd() // 如果到达边界
```

### 事件注册实现

#### onScroll

**ArkTS**：
```typescript
.scrollable(ScrollDirection.Vertical)
.onScroll((xOffset: number, yOffset: number) => {
  console.info(`onScroll: xOffset=${xOffset}, yOffset=${yOffset}`)
})
```

**C++ 实现**：
```cpp
// scroll_model_ng.cpp
void ScrollModelNG::SetOnScroll(ScrollEventFunc&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetOnScroll(std::move(onScroll));
}

// scroll_event_hub.h
class ScrollEventHub : public EventHub {
public:
    void SetOnScroll(ScrollEventFunc&& onScroll) {
        onScroll_ = std::move(onScroll);
    }

    const ScrollEventFunc& GetOnScroll() const {
        return onScroll_;
    }

private:
    ScrollEventFunc onScroll_;
};

// scroll_pattern.cpp
void ScrollPattern::FireOnDidScroll(float scroll)
{
    auto eventHub = GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);

    auto onScroll = eventHub->GetOnScroll();
    if (onScroll) {
        // 调用 ArkTS 回调
        onScroll(scroll);
    }
}
```

#### onReachStart / onReachEnd

**ArkTS**：
```typescript
.onReachStart(() => {
  console.info('到达顶部')
})
.onReachEnd(() => {
  console.info('到达底部')
})
```

**C++ 实现**：
```cpp
// scroll_pattern.cpp
void ScrollPattern::FireOnReachStart(
    const OnReachEvent& onReachStart,
    const OnReachEvent& onJSFrameNodeReachStart)
{
    if (onReachStart) {
        onReachStart();
    }
    if (onJSFrameNodeReachStart) {
        onJSFrameNodeReachStart();
    }
}

// 触发条件
if (IsAtTop()) {
    FireOnReachStart(onReachStart_, onJSFrameNodeReachStart_);
}
if (IsAtBottom()) {
    FireOnReachEnd(onReachEnd_, onJSFrameNodeReachEnd_);
}
```

---

## 滚动控制

### ScrollPositionController

**文件**：`scrollable_pattern.h`（基类中定义）

**功能**：提供滚动控制 API

#### 1. ScrollTo()

**功能**：滚动到指定位置

**签名**：
```cpp
void ScrollTo(float position)
```

**参数**：
- `position`：目标位置（0 表示顶部，scrollableDistance_ 表示底部）

**实现**：
```cpp
void ScrollPattern::ScrollTo(float position)
{
    // 1. 验证位置
    double validatedOffset = ValidateOffset(SCROLL_FROM_JUMP, -position);

    // 2. 跳转到目标位置
    JumpToPosition(validatedOffset, SCROLL_FROM_JUMP);

    // 3. 请求重新布局
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
```

**对应 ArkTS**：
```typescript
this.scroller.scrollTo(100)
```

#### 2. ScrollBy()

**功能**：滚动指定距离（相对偏移）

**签名**：
```cpp
void ScrollBy(float pixelX, float pixelY, bool smooth)
```

**参数**：
- `pixelX`：X 方向滚动距离（像素）
- `pixelY`：Y 方向滚动距离（像素）
- `smooth`：是否平滑滚动

**实现**：
```cpp
void ScrollPattern::ScrollBy(
    float pixelX,
    float pixelY,
    bool smooth,
    const std::function<void()>& onFinish)
{
    // 1. 计算滚动距离
    float delta = GetAxis() == Axis::VERTICAL ? pixelY : pixelX;

    // 2. 如果需要平滑滚动，启动动画
    if (smooth) {
        StartScrollAnimation(delta, onFinish);
    } else {
        // 3. 直接更新偏移
        UpdateCurrentOffset(delta, SCROLL_FROM_JUMP);
        if (onFinish) {
            onFinish();
        }
    }
}
```

**对应 ArkTS**：
```typescript
this.scroller.scrollBy(0, 100)  // 向下滚动 100 像素
this.scroller.scrollBy(0, 100, true)  // 平滑滚动
```

#### 3. ScrollEdge()

**功能**：滚动到边缘

**签名**：
```cpp
void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
```

**参数**：
- `scrollEdgeType`：边缘类型（TOP / BOTTOM / START / END）
- `smooth`：是否平滑滚动

**实现**：
```cpp
void ScrollPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    float targetPosition = 0.0f;

    switch (scrollEdgeType) {
        case ScrollEdgeType::TOP:
        case ScrollEdgeType::START:
            targetPosition = 0.0f;
            break;
        case ScrollEdgeType::BOTTOM:
        case ScrollEdgeType::END:
            targetPosition = scrollableDistance_;
            break;
        default:
            return;
    }

    ScrollTo(targetPosition);
}
```

**对应 ArkTS**：
```typescript
this.scroller.scrollEdge(ScrollEdgeType.START)  // 滚动到顶部
this.scroller.scrollEdge(ScrollEdgeType.END)    // 滚动到底部
```

### 自定义 Scroller

**ArkTS**：
```typescript
export class MyScrollPage {
  private scroller: Scroller = new Scroller()

  build() {
    Scroll(this.scroller) {
      // 内容
    }
    .scrollable(ScrollDirection.Vertical)

    Button('Scroll to Bottom')
      .onClick(() => {
        this.scroller.scrollTo(500)
      })
  }
}
```

---

## 特殊功能

### 1. ScrollSnap（滚动对齐）

**功能**：滚动时自动对齐到指定位置

**配置方式**：
```typescript
.scrollSnap({
  snapAlign: ScrollSnapAlign.START,  // 对齐方式
  snapInterval: 100                   // 对齐间隔（像素）
})
```

**实现原理**：

1. **计算对齐点**（`CaleSnapOffsets`）：
```cpp
void ScrollPattern::CaleSnapOffsets(const RefPtr<FrameNode>& host)
{
    snapOffsets_.clear();

    auto scrollSnapAlign = GetScrollSnapAlign(host);
    auto intervalSize = GetIntervalSize();
    float intervalPx = ConvertDimensionToPx(intervalSize, viewPortLength_).value_or(0.0f);

    // 计算对齐点
    for (float offset = 0.0f; offset <= scrollableDistance_; offset += intervalPx) {
        snapOffsets_.push_back(offset);
    }

    // 确保最后一个点在 scrollableDistance_
    if (snapOffsets_.back() < scrollableDistance_) {
        snapOffsets_.push_back(scrollableDistance_);
    }
}
```

2. **预测对齐偏移**（`CalcPredictSnapOffset`）：
```cpp
std::optional<float> ScrollPattern::CalcPredictSnapOffset(
    float delta,
    float dragDistance,
    float velocity)
{
    if (snapOffsets_.empty()) {
        return std::nullopt;
    }

    // 1. 计算目标位置
    double targetOffset = currentOffset_ + delta;

    // 2. 找到最近的 snap 点
    auto it = std::lower_bound(snapOffsets_.begin(), snapOffsets_.end(), -targetOffset);

    if (it != snapOffsets_.end()) {
        // 返回对齐偏移
        float snapOffset = *it;
        return -snapOffset - currentOffset_;
    }

    return std::nullopt;
}
```

**对齐方式**：
- `START`：对齐到视口起始位置
- `CENTER`：对齐到视口中心
- `END`：对齐到视口结束位置

### 2. Paging（分页滚动）

**功能**：按页滚动

**配置方式**：
```typescript
.enablePaging(true)
```

**实现原理**：

```cpp
bool ScrollPattern::ScrollPageCheck(float delta, int32_t source)
{
    if (enablePagingStatus_ != ScrollPagingStatus::VALID) {
        return false;
    }

    // 计算分页偏移
    float pagingOffset = GetPagingOffset(delta, dragDistance, velocity);

    // 应用偏移
    UpdateCurrentOffset(pagingOffset, source);

    return true;
}

float ScrollPattern::GetPagingOffset(
    float delta,
    float dragDistance,
    float velocity) const
{
    // 页面长度（通常是视口长度）
    float pageLength = viewPortLength_;

    // 计算当前页数
    int currentPage = static_cast<int>(-currentOffset_ / pageLength);

    // 计算目标页数
    int targetPage = currentPage;
    if (dragDistance > pageLength / 2) {
        targetPage++;
    }

    // 计算目标偏移
    float targetOffset = -targetPage * pageLength;

    return targetOffset - currentOffset_;
}
```

### 3. FreeScroll（二维自由滚动）

**功能**：支持 X 和 Y 方向同时滚动

**配置方式**：
```typescript
.scrollable(ScrollDirection.Free)
```

**实现原理**：

使用 `FreeScrollController` 管理二维偏移：

```cpp
class FreeScrollController {
public:
    OffsetF GetOffset() const {
        return currentOffset_;
    }

    bool ScrollBy(const OffsetF& delta, bool canOverScroll = false)
    {
        OffsetF newOffset = currentOffset_ + delta;

        // 验证边界
        newOffset.SetX(ValidateX(newOffset.X()));
        newOffset.SetY(ValidateY(newOffset.Y()));

        currentOffset_ = newOffset;
        return true;
    }

private:
    OffsetF currentOffset_;
};
```

**对应 API**：
```cpp
// ScrollPattern 中
RefPtr<FreeScrollController> freeScroll_;

bool ScrollPattern::FreeScrollBy(const OffsetF& delta, bool canOverScroll)
{
    CHECK_NULL_RETURN(freeScroll_, false);
    return freeScroll_->ScrollBy(delta, canOverScroll);
}
```

### 4. Zoom（缩放）

**功能**：支持双指缩放

**配置方式**：
```typescript
// 通过属性设置
.scale({ x: 1.0, y: 1.0 })
```

**实现原理**：

使用 `ZoomController` 处理缩放手势：

```cpp
class ZoomController {
public:
    void HandlePinch(const OffsetF& focus, float scale)
    {
        // 1. 验证缩放范围
        scale = std::clamp(scale, minZoomScale_, maxZoomScale_);

        // 2. 应用缩放
        zoomScale_ = scale;

        // 3. 更新子节点缩放
        UpdateChildScale();

        // 4. 重新计算可滚动距离
        RecalculateScrollableDistance();
    }

private:
    float minZoomScale_ = 1.0f;
    float maxZoomScale_ = 3.0f;
    std::optional<float> zoomScale_;
};
```

---

## 缓存机制

### 缓存结构

Scroll 组件使用两种缓存优化性能：

```cpp
// 布局缓存
std::list<ScrollLayoutInfo> scrollLayoutInfos_;

// 测量缓存
std::list<ScrollMeasureInfo> scrollMeasureInfos_;
```

### ScrollLayoutInfo

**定义**：`scrollable_properties.h:341`

```cpp
struct ScrollLayoutInfo {
    uint64_t changedTime_ = 0;        // 变更时间戳
    float scrollableDistance_ = 0;    // 可滚动距离
    NG::SizeF scrollSize_;            // 滚动容器尺寸
    NG::SizeF viewPort_;              // 视口尺寸
    NG::SizeF childSize_;             // 子节点尺寸
};
```

### ScrollMeasureInfo

**定义**：`scrollable_properties.h:372`

```cpp
struct ScrollMeasureInfo {
    uint64_t changedTime_ = 0;                                 // 变更时间戳
    std::optional<NG::LayoutConstraintF> parentConstraint_;   // 父节点约束
    std::optional<NG::LayoutConstraintF> childConstraint_;    // 子节点约束
    NG::SizeF selfSize_;                                      // 自身尺寸
    NG::SizeF childSize_;                                     // 子节点尺寸
};
```

### 缓存策略

**LRU 淘汰**：
```cpp
constexpr int32_t SCROLL_LAYOUT_INFO_COUNT = 30;
constexpr int32_t SCROLL_MEASURE_INFO_COUNT = 30;
```

**添加缓存**：
```cpp
void ScrollPattern::AddScrollLayoutInfo()
{
    ScrollLayoutInfo info;
    info.changedTime_ = GetTimestamp();
    info.scrollableDistance_ = scrollableDistance_;
    info.scrollSize_ = viewSize_;
    info.viewPort_ = viewPort_;
    info.childSize_ = viewPortExtent_;

    scrollLayoutInfos_.push_back(info);

    // LRU 淘汰
    if (scrollLayoutInfos_.size() > SCROLL_LAYOUT_INFO_COUNT) {
        scrollLayoutInfos_.pop_front();
    }
}
```

**缓存失效时机**：
- 约束变化（`ConstraintChanged()` 返回 true）
- 视口尺寸变化（`lastViewSize != viewSize_`）
- 内容尺寸变化（`lastViewPortExtent != viewPortExtent_`）

---

## 执行流程

### 1. 初始化流程

```
ArkTS: Scroll() { ... }
    ↓
ScrollModelNG::Create()
    ↓
创建 FrameNode (V2::SCROLL_ETS_TAG)
    ↓
创建 ScrollPattern
    ↓
创建 ScrollLayoutProperty
    ↓
创建 ScrollEventHub
    ↓
OnAttachToMainTree()
    ↓
[初始化完成]
```

### 2. 布局流程

```
触发布局（属性修改 / 尺寸变化）
    ↓
CreateLayoutAlgorithm()
    ├─ 创建 ScrollLayoutAlgorithm
    ├─ 传递 currentOffset_
    └─ 传递 scrollableDistance_
    ↓
ScrollLayoutAlgorithm::Measure()
    ├─ 测量子节点
    ├─ 计算 scrollableDistance_
    ├─ 计算 viewPort_
    └─ 计算 viewPortExtent_
    ↓
ScrollLayoutAlgorithm::Layout()
    ├─ 计算内容偏移
    ├─ 应用滚动偏移
    └─ 定位子节点
    ↓
OnDirtyLayoutWrapperSwap()
    ├─ 同步布局结果
    ├─ 添加布局缓存
    └─ 更新滚动条
    ↓
[布局完成]
```

### 3. 滚动流程

```
用户滑动手势
    ↓
PanGestureRecognizer 识别
    ↓
ScrollablePattern::HandleScrollDelta()
    ↓
ScrollPattern::OnScrollCallback(offset, source)
    ├─ ValidateOffset() - 验证偏移
    ├─ UpdateCurrentOffset() - 更新偏移
    ├─ FireOnDidScroll() - 触发事件
    └─ 请求新帧
    ↓
[滚动中]（可能多次调用 OnScrollCallback）
    ↓
滚动停止
    ↓
OnScrollEndCallback()
    ├─ FireOnReachStart/End() - 边界事件
    └─ 停止动画
    ↓
[滚动完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建滚动容器
Scroll() { ... }
Scroll(value: { scroller: Scroller }) { ... }

// 滚动方向
.scrollable(direction: ScrollDirection)
// ScrollDirection: Vertical | Horizontal | None | Free

// 滚动条
.scrollBar(state: BarState)
// BarState: Auto | Off | On
.scrollBar(width: Length)
.scrollBar(color: ResourceColor)
.scrollBar(edgeEffect: ScrollBarEdgeEffect)
.scrollBar(backgroundColor: ResourceColor)

// 边缘效果
.edgeEffect(effect: EdgeEffect)
// EdgeEffect: None | Spring | Fade
```

#### 滚动事件

```typescript
// 滚动事件
.onScroll(event: (xOffset: number, yOffset: number) => void)

// 滚动开始
.onScrollStart(event: () => void)

// 滚动停止
.onScrollStop(event: () => void)

// 到达顶部
.onReachStart(event: () => void)

// 到达底部
.onReachEnd(event: () => void)

// 即将滚动（可拦截）
.onWillScroll(event: (xOffset: number, yOffset: number, scrollState: ScrollState) => void)

// 滚动完成
.onDidScroll(event: (xOffset: number, yOffset: number) => void)
```

#### 滚动控制

```typescript
// 滚动到指定位置
scroller.scrollTo(value: number)

// 滚动指定距离
scroller.scrollBy(deltaX: number, deltaY: number)
scroller.scrollBy(deltaX: number, deltaY: number, animation: IAnimationSpec)

// 滚动到边缘
scroller.scrollEdge(edge: ScrollEdge)
scroller.scrollEdge(edge: ScrollEdge, animation: IAnimationSpec)
// ScrollEdge: Top | Bottom | Start | End

// 滚动到指定元素
scroller.scrollIntoView(id: string)
scroller.scrollIntoView(id: string, animation: IAnimationSpec)
```

#### 高级功能

```typescript
// 滚动对齐
.scrollSnap(config: ScrollSnapOptions)
interface ScrollSnapOptions {
  snapAlign: ScrollSnapAlign;  // START | CENTER | END | NONE
  snapInterval?: number;        // 对齐间隔（像素）
}

// 分页滚动
.enablePaging(value: boolean)

// 初始偏移
.initialOffset(value: OffsetT)
interface OffsetT {
  x: Length | Resource;
  y: Length | Resource;
}

// 缩放
.scale(options: ScaleOptions)
interface ScaleOptions {
  x?: number;
  y?: number;
  scaleX?: number;
  scaleY?: number;
}

.minZoom(value: number)
.maxZoom(value: number)
```

### C++ API 列表

#### ScrollPattern 公共方法

```cpp
// 位置相关
double GetCurrentPosition() const;
Offset GetCurrentOffset() const;
float GetScrollableDistance() const;
float GetMainContentSize() const;

// 滚动控制
void ScrollTo(float position);
void ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish = nullptr);
void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);
void ScrollPage(bool reverse, bool smooth = false, AccessibilityScrollType scrollType = ...);

// 自由滚动
bool FreeScrollBy(const OffsetF& delta, bool canOverScroll = false);
bool FreeScrollTo(const ScrollControllerBase::ScrollToParam& param);

// 边界判断
bool IsAtTop() const;
bool IsAtBottom(bool considerRepeat = false) const;
bool IsOutOfBoundary(bool useCurrentDelta = true) const;

// ScrollSnap
std::optional<float> CalcPredictSnapOffset(float delta, float dragDistance = 0.f, float velocity = 0.f, SnapDirection snapDirection = SnapDirection::NONE);
std::vector<float> GetSnapOffsets() const;
void SetSnapOffsets(const std::vector<float>& snapOffset);

// 缩放
float GetMaxZoomScale() const;
float GetMinZoomScale() const;
float GetZoomScale() const;
void SetMaxZoomScale(float scale);
void SetMinZoomScale(float scale);
void SetZoomScale(std::optional<float> scale);
```

---

## 关键实现细节

### 1. 滚动偏移量计算

**坐标系**：
```
currentOffset_ = 0              → 在顶部（内容顶部对齐视口顶部）
currentOffset_ > 0              → 内容向上偏移（显示上方内容）
currentOffset_ < 0              → 内容向下偏移（显示下方内容）
currentOffset_ = -scrollableDistance_ → 在底部（内容底部对齐视口底部）
```

**计算公式**：
```cpp
// 内容偏移
float contentOffset = -currentOffset_ + contentStartOffset_;

// 子节点位置
OffsetF childOffset = Axis == Axis::VERTICAL
    ? OffsetF(0.0f, contentOffset)
    : OffsetF(contentOffset, 0.0f);
```

### 2. 可滚动距离计算

**公式**：
```cpp
scrollableDistance_ = max(0, contentSize - viewportSize)
```

**实现**：
```cpp
float contentMainSize = GetMainSize(viewPortExtent_, axis);
float viewPortMainSize = GetMainSize(viewPort_, axis);
scrollableDistance_ = std::max(0.0f, contentMainSize - viewPortMainSize);
```

### 3. 边界判断

**顶部判断**：
```cpp
bool ScrollPattern::IsAtTop() const
{
    return currentOffset_ >= 0.0f;
}
```

**底部判断**：
```cpp
bool ScrollPattern::IsAtBottom(bool considerRepeat) const
{
    if (considerRepeat && repeat_) {
        return false;
    }
    return currentOffset_ <= -scrollableDistance_;
}
```

**越界判断**：
```cpp
bool ScrollPattern::IsOutOfBoundary(bool useCurrentDelta) const
{
    if (useCurrentDelta) {
        return currentOffset_ > 0.0f || currentOffset_ < -scrollableDistance_;
    }
    return currentOffset_ >= 0.0f || currentOffset_ <= -scrollableDistance_;
}
```

### 4. ScrollSnap 对齐点计算

**间隔对齐**：
```cpp
void ScrollPattern::CaleSnapOffsetsByInterval(
    ScrollSnapAlign scrollSnapAlign,
    const RefPtr<FrameNode>& host)
{
    snapOffsets_.clear();

    auto intervalSize = GetIntervalSize();
    float intervalPx = ConvertDimensionToPx(intervalSize, viewPortLength_).value_or(0.0f);

    if (intervalPx <= 0.0f) {
        return;
    }

    // 生成对齐点
    for (float offset = 0.0f; offset <= scrollableDistance_; offset += intervalPx) {
        snapOffsets_.push_back(-offset);
    }

    // 确保最后一个点
    if (snapOffsets_.empty() || snapOffsets_.back() > -scrollableDistance_) {
        snapOffsets_.push_back(-scrollableDistance_);
    }
}
```

**分页对齐**：
```cpp
void ScrollPattern::CaleSnapOffsetsByPaginations(
    ScrollSnapAlign scrollSnapAlign)
{
    snapOffsets_.clear();

    if (snapPaginations_.empty()) {
        return;
    }

    float accumulated = 0.0f;
    snapOffsets_.push_back(0.0f);

    for (const auto& pagination : snapPaginations_) {
        float paginationPx = ConvertDimensionToPx(pagination, viewPortLength_).value_or(0.0f);
        accumulated += paginationPx;
        snapOffsets_.push_back(-accumulated);
    }

    // 确保最后一个点
    if (snapOffsets_.back() > -scrollableDistance_) {
        snapOffsets_.push_back(-scrollableDistance_);
    }
}
```

### 5. 边缘效果实现

#### Spring 效果

**原理**：允许内容超出边界，然后弹性回弹

**实现**：
```cpp
bool ScrollPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    double willScrollOffset = currentOffset_ + offset;

    // 验证偏移
    willScrollOffset = ValidateOffset(source, willScrollOffset);

    // 应用边缘效果
    if (IsOutOfBoundary() && edgeEffect_ == EdgeEffect::SPRING) {
        // 允许越界
        currentOffset_ = willScrollOffset;
    } else {
        // 限制在边界内
        currentOffset_ = std::clamp(willScrollOffset, -scrollableDistance_, 0.0f);
    }

    return true;
}
```

#### Fade 效果

**原理**：在边缘绘制半透明遮罩

**实现**：
```cpp
// scroll_fade_painter.cpp
void ScrollFadePainter::DrawFadeEffect(
    const std::unique_ptr<DrawCommandList>& drawCmdList,
    const RectF& rect,
    float fadeSize)
{
    if (fadeSize <= 0.0f) {
        return;
    }

    // 创建渐变
    std::vector<float> pos = { 0.0f, 1.0f };
    std::vector<Color> colors = { Color::TRANSPARENT, Color::BLACK };

    // 绘制顶部淡入淡出
    if (IsAtTop()) {
        RectF topFade = RectF(rect.Left(), rect.Top(), rect.Width(), fadeSize);
        DrawLinearGradient(drawCmdList, topFade, pos, colors);
    }

    // 绘制底部淡入淡出
    if (IsAtBottom()) {
        RectF bottomFade = RectF(rect.Left(), rect.Bottom() - fadeSize, rect.Width(), fadeSize);
        DrawLinearGradient(drawCmdList, bottomFade, pos, colors);
    }
}
```

---

## 滚动边缘效果

### EdgeEffect 类型

| 类型 | 描述 | 实现类 |
|-----|------|--------|
| **NONE** | 无边缘效果 | - |
| **SPRING** | 弹性效果 | ScrollSpringEffect |
| **FADE** | 淡入淡出效果 | ScrollFadeEffect |

### Spring 效果

**配置**：
```typescript
.edgeEffect(EdgeEffect.Spring)
```

**特性**：
- 允许内容超出边界
- 弹性回弹动画
- 支持阻尼系数

**实现位置**：`scrollable_pattern.cpp`

### Fade 效果

**配置**：
```typescript
.edgeEffect(EdgeEffect.Fade)
```

**特性**：
- 在边缘绘制半透明遮罩
- 不影响滚动行为
- 可配置淡入淡出区域大小

**实现位置**：`effect/scroll_fade_effect.cpp`

### 自定义边缘效果

可以通过继承 `ScrollEdgeEffect` 实现自定义效果：

```cpp
class CustomScrollEdgeEffect : public ScrollEdgeEffect {
public:
    void PerformScroll(float delta, ScrollState state) override;
    void StartSpringAnimation(float target) override;
    void ProcessSpringMotion(float velocity) override;
};
```

---

## 使用示例

### 示例 1：基础垂直滚动

```typescript
@Entry
@Component
struct BasicScroll {
  build() {
    Scroll() {
      Column() {
        ForEach(Array.from({ length: 20 }), (_, index) => {
          Text(`Item ${index}`)
            .width('100%')
            .height(80)
            .backgroundColor(Color.White)
            .margin({ bottom: 10 })
        })
      }
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
    .scrollBar(BarState.Auto)
    .backgroundColor(Color.Grey)
  }
}
```

### 示例 2：带滚动事件的滚动

```typescript
@Entry
@Component
struct ScrollWithEvents {
  @State scrollOffset: number = 0

  build() {
    Scroll() {
      Column() {
        ForEach(Array.from({ length: 20 }), (_, index) => {
          Text(`Item ${index}`)
            .width('100%')
            .height(80)
        })
      }
    }
    .scrollable(ScrollDirection.Vertical)
    .onScroll((xOffset: number, yOffset: number) => {
      this.scrollOffset = yOffset
      console.info(`Scrolled: ${yOffset}`)
    })
    .onReachStart(() => {
      console.info('Reached top')
    })
    .onReachEnd(() => {
      console.info('Reached bottom')
    })

    Text(`Offset: ${this.scrollOffset}`)
  }
}
```

### 示例 3：滚动控制

```typescript
@Entry
@Component
struct ScrollWithController {
  private scroller: Scroller = new Scroller()

  build() {
    Column() {
      Scroll(this.scroller) {
        Column() {
          ForEach(Array.from({ length: 50 }), (_, index) => {
            Text(`Item ${index}`)
              .width('100%')
              .height(60)
          })
        }
      }
      .scrollable(ScrollDirection.Vertical)
      .height('80%')

      Row() {
        Button('Scroll to Top')
          .onClick(() => {
            this.scroller.scrollEdge(ScrollEdgeType.TOP)
          })

        Button('Scroll to Bottom')
          .onClick(() => {
            this.scroller.scrollEdge(ScrollEdgeType.BOTTOM)
          })

        Button('Scroll by 100')
          .onClick(() => {
            this.scroller.scrollBy(0, 100, true)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
  }
}
```

### 示例 4：水平滚动

```typescript
@Entry
@Component
struct HorizontalScroll {
  build() {
    Scroll() {
      Row() {
        ForEach(Array.from({ length: 10 }), (_, index) => {
          Text(`Item ${index}`)
            .width(150)
            .height('100%')
            .backgroundColor(Color.Blue)
            .margin({ right: 10 })
        })
      }
      .height('100%')
    }
    .scrollable(ScrollDirection.Horizontal)
    .scrollBar(BarState.Auto)
  }
}
```

### 示例 5：二维自由滚动

```typescript
@Entry
@Component
struct FreeScroll {
  build() {
    Scroll() {
      Grid() {
        ForEach(Array.from({ length: 100 }), (_, index) => {
          GridItem() {
            Text(`${index}`)
              .width(100)
              .height(100)
              .backgroundColor(Color.Pink)
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
    }
    .scrollable(ScrollDirection.Free)
    .scrollBar(BarState.Auto)
  }
}
```

### 示例 6：滚动对齐（ScrollSnap）

```typescript
@Entry
@Component
struct ScrollSnap {
  build() {
    Scroll() {
      Column() {
        ForEach(Array.from({ length: 20 }), (_, index) => {
          Text(`Item ${index}`)
            .width('100%')
            .height(150)
            .backgroundColor(Color.White)
        })
      }
    }
    .scrollable(ScrollDirection.Vertical)
    .scrollSnap({
      snapAlign: ScrollSnapAlign.START,
      snapInterval: 150
    })
  }
}
```

### 示例 7：分页滚动

```typescript
@Entry
@Component
struct PagingScroll {
  build() {
    Scroll() {
      Column() {
        ForEach(Array.from({ length: 5 }), (_, index) => {
          Text(`Page ${index}`)
            .width('100%')
            .height('100%')
            .fontSize(50)
        })
      }
      .width('100%')
    }
    .scrollable(ScrollDirection.Vertical)
    .enablePaging(true)
    .scrollBar(BarState.Off)
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// 滚动相关日志
TAG_LOGI(AceLogTag::ACE_SCROLL, "ScrollTo position: %{public}f", position);
TAG_LOGD(AceLogTag::ACE_SCROLL, "currentOffset: %{public}f, scrollableDistance: %{public}f",
    currentOffset_, scrollableDistance_);

// 布局相关日志
TAG_LOGD(AceLogTag::ACE_LAYOUT, "Measure: selfSize=%{public}s", size.ToString().c_str());
```

**关键日志点**：
- `OnModifyDone()` - 属性修改完成
- `OnScrollCallback()` - 滚动回调
- `UpdateCurrentOffset()` - 偏移更新
- `OnDirtyLayoutWrapperSwap()` - 布局结果交换
- `CaleSnapOffsets()` - 对齐点计算

**实现 dump 方法**：
```cpp
// scroll_pattern.cpp:374
void ScrollPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("currentOffset", currentOffset_);
    json->Put("scrollableDistance", scrollableDistance_);
    json->Put("viewPortLength", viewPortLength_);
    json->Put("viewPort", viewPort_.ToString().c_str());
    json->Put("viewPortExtent", viewPortExtent_.ToString().c_str());

    // ScrollSnap 信息
    json->Put("snapCount", static_cast<int32_t>(snapOffsets_.size()));
    json->Put("enablePaging", static_cast<int32_t>(enablePagingStatus_));

    // 缓存信息
    json->Put("layoutCacheSize", static_cast<int32_t>(scrollLayoutInfos_.size()));
    json->Put("measureCacheSize", static_cast<int32_t>(scrollMeasureInfos_.size()));
}
```

### 3. 调试器检查

**关键变量**：
```cpp
// Pattern 状态
currentOffset_           // 当前偏移
scrollableDistance_      // 可滚动距离
viewPort_                // 视口尺寸
viewPortExtent_          // 内容尺寸
viewPortLength_          // 视口长度

// 缓存状态
scrollLayoutInfos_.size()      // 布局缓存条目数
scrollMeasureInfos_.size()     // 测量缓存条目数

// Snap 状态
snapOffsets_.size()            // 对齐点数量
enablePagingStatus_            // 分页状态
scrollSnapUpdate_              // 是否需要更新对齐点

// 边缘状态
currentOffset_ >= 0.0f         // 是否在顶部
currentOffset_ <= -scrollableDistance_  // 是否在底部
```

### 4. 常见问题定位

#### 问题 1：滚动位置不正确

**检查点**：
- `currentOffset_` 是否与 LayoutAlgorithm 中的值一致
- `scrollableDistance_` 是否正确计算
- 是否在错误的时机修改了偏移量
- `contentStartOffset_` 和 `contentEndOffset_` 是否正确

**定位方法**：
```cpp
// 在 OnDirtyLayoutWrapperSwap 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL,
    "OnDirtyLayoutWrapperSwap: currentOffset=%{public}f, scrollableDistance=%{public}f",
    currentOffset_, scrollableDistance_);
```

#### 问题 2：布局缓存不生效

**检查点**：
- `ConstraintChanged()` 是否返回 false
- 缓存是否超过 30 条
- `changedTime_` 是否正确更新

**定位方法**：
```cpp
// 在 AddScrollLayoutInfo 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL,
    "AddScrollLayoutInfo: size=%{public}zu, changedTime=%{public}llu",
    scrollLayoutInfos_.size(), changedTime_);
```

#### 问题 3：事件不触发

**检查点**：
- 是否在 `OnModifyDone()` 中注册了事件
- `FireOnReachStart()` / `FireOnReachEnd()` 的条件是否正确
- `prevOffset_` 是否正确维护

**定位方法**：
```cpp
// 在事件触发点添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL,
    "FireOnReachStart: currentOffset=%{public}f, prevOffset=%{public}f",
    currentOffset_, prevOffset_);
```

#### 问题 4：ScrollSnap 不生效

**检查点**：
- `snapOffsets_` 是否正确计算
- `scrollSnapUpdate_` 是否标记为 true
- `GetScrollSnapAlign()` 是否返回 NONE

**定位方法**：
```cpp
// 在 CaleSnapOffsets 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL,
    "CaleSnapOffsets: count=%{public}zu, interval=%{public}f",
    snapOffsets_.size(), intervalSize_.Value());
```

---

## 常见问题

### Q1: Scroll 组件和 List 组件有什么区别？

**A**:
- **Scroll**：通用滚动容器，适合少量内容的滚动，不支持虚拟化
- **List**：列表组件，支持大量数据的虚拟化滚动，有懒加载和复用机制

**选择建议**：
- 内容数量 < 100：使用 Scroll
- 内容数量 > 100：使用 List

### Q2: 如何禁止滚动？

**A**：有三种方法：

1. **设置方向为 NONE**：
```typescript
.scrollable(ScrollDirection.None)
```

2. **设置内容尺寸不超过视口**：
```typescript
Scroll() {
  Column() { ... }
  .width('100%')
  .height('100%')  // 不超过视口
}
```

3. **禁用手势**：
```typescript
.gesture(
  PriorityGesture(
    PanGesture({ direction: PanDirection.None })
  )
)
```

### Q3: 如何监听滚动开始和结束？

**A**：
```typescript
Scroll() {
  // ...
}
.onScrollStart(() => {
  console.info('Scroll started')
})
.onScrollStop(() => {
  console.info('Scroll stopped')
})
```

### Q4: ScrollSnap 和 Paging 能同时使用吗？

**A**：不能同时使用。

```typescript
// 错误：同时启用
.scrollSnap({ snapAlign: ScrollSnapAlign.START, snapInterval: 100 })
.enablePaging(true)  // 优先级更高

// 正确：只使用一种
// 方案 1：使用 ScrollSnap
.scrollSnap({ snapAlign: ScrollSnapAlign.START, snapInterval: 100 })

// 方案 2：使用 Paging
.enablePaging(true)
```

### Q5: 如何实现滚动到指定元素？

**A**：
```typescript
// 1. 给元素设置 ID
Text('Target')
  .id('target')

// 2. 滚动到指定元素
this.scroller.scrollIntoView('target')
```

### Q6: 如何获取当前滚动位置？

**A**：
```typescript
// 方法 1：通过 onScroll 事件
@State scrollOffset: number = 0

.onScroll((xOffset: number, yOffset: number) => {
  this.scrollOffset = yOffset
})

// 方法 2：通过 currentOffset()
const offset = this.scroller.currentOffset()
```

### Q7: 如何实现无限滚动？

**A**：需要结合 `onReachEnd` 事件：

```typescript
@State items: Array<number> = Array.from({ length: 20 }, (_, i) => i)

loadMore() {
  const lastItem = this.items[this.items.length - 1]
  const newItems = Array.from({ length: 20 }, (_, i) => lastItem + i + 1)
  this.items = [...this.items, ...newItems]
}

Scroll() {
  List() {
    ForEach(this.items, (item: number) => {
      ListItem() {
        Text(`Item ${item}`)
      }
    })
  }
}
.onReachEnd(() => {
  this.loadMore()
})
```

### Q8: 如何实现横向和纵向同时滚动？

**A**：使用自由滚动模式：

```typescript
.scrollable(ScrollDirection.Free)
```

或使用嵌套滚动：
```typescript
Scroll() {  // 外层纵向滚动
  Scroll() {  // 内层横向滚动
    Row() { ... }
  }
  .scrollable(ScrollDirection.Horizontal)
}
.scrollable(ScrollDirection.Vertical)
```

### Q9: 滚动性能优化有哪些方法？

**A**：
1. **使用虚拟化列表**（List / WaterFlow）
2. **避免复杂的滚动事件处理**：
```typescript
.onScroll((xOffset, yOffset) => {
  // ❌ 避免重计算
  // const result = heavyCalculation()

  // ✅ 使用防抖
  debounce(() => {
    this.updateUI()
  }, 100)
})
```

3. **启用布局缓存**：默认已启用
4. **减少子节点数量**：使用懒加载

### Q10: 如何实现滚动到顶部/底部的动画？

**A**：
```typescript
// 使用动画规格
this.scroller.scrollEdge(ScrollEdgeType.TOP, {
  duration: 300,
  curve: Curve.EaseInOut
})

// 或使用 animateTo
Button('Scroll to Top')
  .onClick(() => {
    animateTo({ duration: 300 }, () => {
      this.scroller.scrollTo(0)
    })
  })
```

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 滚动偏移 | Scroll Offset | 当前滚动位置，0 表示在顶部 |
| 可滚动距离 | Scrollable Distance | 内容尺寸减去视口尺寸 |
| 视口 | Viewport | 可见区域大小 |
| 滚动条 | Scroll Bar | 指示滚动位置的UI元素 |
| 边缘效果 | Edge Effect | 滚动到边界时的视觉效果 |
| 滚动对齐 | Scroll Snap | 滚动时自动对齐到指定位置 |
| 分页滚动 | Paging | 按页滚动的模式 |
| 自由滚动 | Free Scroll | 同时支持 X 和 Y 方向滚动的模式 |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `scroll_pattern.h` | 549 | ScrollPattern 类定义 |
| `scroll_pattern.cpp` | ~3000 | ScrollPattern 实现 |
| `scroll_layout_algorithm.h` | 128 | 布局算法定义 |
| `scroll_layout_algorithm.cpp` | ~500 | 布局算法实现 |
| `scroll_model_ng.h` | ~150 | NG Model 定义 |
| `scroll_model_ng.cpp` | ~800 | NG Model 实现 |
| `free_scroll_controller.h` | ~100 | 自由滚动控制器 |
| `free_scroll_controller.cpp` | ~300 | 自由滚动控制器实现 |
| `zoom_controller.h` | ~80 | 缩放控制器 |
| `zoom_controller.cpp` | ~200 | 缩放控制器实现 |

### C. 相关文档

- [Scroll 组件官方文档](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-scroll-V5)
- [Scroller 对象](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-container-scroll-V5#scroller)
- [滚动方向枚举](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-appendix-enums-V5#scrolldirection)
- [边缘效果枚举](https://developer.huawei.com/consumer/cn/doc/harmonyos-references-V5/ts-appendix-enums-V5#edgeeffect)

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-01-30 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
