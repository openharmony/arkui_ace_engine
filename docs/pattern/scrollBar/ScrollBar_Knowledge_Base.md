# ArkUI ScrollBar 组件完整知识库

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
6. [Model层详解](#model层详解)
7. [LayoutAlgorithm层详解](#layoutalgorithm层详解)
8. [属性系统](#属性系统)
9. [事件处理](#事件处理)
10. [滚动条通信机制](#滚动条通信机制)
11. [显示与隐藏动画](#显示与隐藏动画)
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

**ScrollBar 组件**是 OpenHarmony ArkUI 框架中的**滚动条组件**，用于配合可滚动组件（如 List、Grid、Scroll）使用，提供可视化的滚动位置指示和滚动控制功能。

**技术栈**：
- **前端**：ArkTS/TypeScript
- **桥接层**：ScrollBarModelNG
- **核心层**：NG Pattern 架构 (ScrollBarPattern)
- **布局算法**：ScrollBarLayoutAlgorithm
- **渲染层**：Rosen + Skia
- **通信机制**：ScrollBarProxy

**代码规模**：
- 总文件数：约 18 个文件
- 核心代码：约 5,000+ 行 C++ 代码
- 涉及 4 个架构层次

### 功能特性

ScrollBar 组件支持：
- **多种方向**：
  - 垂直滚动条 (ScrollBarDirection.Vertical)
  - 水平滚动条 (ScrollBarDirection.Horizontal)
- **多种显示模式**：
  - 自动显示/隐藏 (BarState.Auto)
  - 始终显示 (BarState.On)
  - 始终隐藏 (BarState.Off)
- **样式定制**：
  - 滚动条颜色 (scrollBarColor)
  - 位置模式（左侧/右侧/顶部/底部）
- **交互功能**：
  - 拖动滚动条
  - 点击滚动条快速跳转
  - 长按滚动条连续滚动
  - 鼠标滚轮支持
  - 触摸屏滑动支持
- **嵌套滚动**：支持嵌套滚动场景 (enableNestedScroll，API 14+)
- **动画效果**：
  - 淡入淡出动画
  - 滚动惯性效果
  - 边缘回弹效果
- **无障碍支持**：完整的 Accessibility 支持

### 设计模式

ScrollBar 组件采用 **NG Pattern 架构**：

```
前端 (ArkTS)
    ↓ (Model Layer)
ScrollBarModelNG (scroll_bar_model_ng.cpp)
    ↓ (NG Pattern Layer)
ScrollBarPattern (scroll_bar_pattern.cpp)
    ├─ ScrollBar (实际滚动条对象)
    └─ ScrollBarProxy (通信代理)
    ↓ (NG LayoutAlgorithm Layer)
ScrollBarLayoutAlgorithm (scroll_bar_layout_algorithm.cpp)
    ↓
渲染显示
```

### 核心概念

**滚动条坐标系**：
```
currentOffset_ = 0              → 在顶部/左侧
currentOffset_ > 0              → 内容向下/向右偏移
currentOffset_ < 0              → 内容向上/向左偏移
currentOffset_ = -scrollableDistance_  → 在底部/右侧
```

**关键距离**：
- `controlDistance_`：可滚动距离（内容尺寸 - 视口尺寸）
- `scrollableDistance_`：滚动条可移动距离
- `currentOffset_`：当前滚动位置偏移

**通信机制**：ScrollBar 通过 ScrollBarProxy 与可滚动节点（List、Grid、Scroll）进行双向通信。

---

## 完整调用链

### 1. 从 ArkTS 到 Pattern 的调用链

#### 调用链图

```
┌─────────────────────────────────────────────────────────┐
│ 前端 ArkTS                                                │
│                                                          │
│ ScrollBar({                                             │
│   scroller: this.scroller,                             │
│   state: BarState.Auto,                                │
│   direction: ScrollBarDirection.Vertical                │
│ })                                                      │
│   .scrollBarColor(Color.Red)                            │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Model Layer (NG)                                         │
│                                                          │
│ class ScrollBarModelNG                                   │
│   源码：frameworks/core/components_ng/pattern/          │
│         scroll_bar/scroll_bar_model_ng.cpp              │
│                                                          │
│ 关键方法：                                                │
│ - Create() - 创建 ScrollBar 节点                        │
│ - SetScrollBarColor() - 设置滚动条颜色                   │
│ - SetEnableNestedScroll() - 设置嵌套滚动 (API 14+)       │
│                                                          │
│ 执行流程：                                                 │
│ 1. 创建 FrameNode (V2::SCROLL_BAR_ETS_TAG)             │
│ 2. 创建 ScrollBarPattern                                │
│ 3. 应用布局属性 (ScrollBarLayoutProperty)               │
│ 4. 应用绘制属性 (ScrollBarPaintProperty)                │
│ 5. 注册到 ScrollBarProxy                                │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ Pattern Layer (业务逻辑)                                  │
│                                                          │
│ class ScrollBarPattern : public Pattern                  │
│   源码：frameworks/core/components_ng/pattern/          │
│         scroll_bar/scroll_bar_pattern.cpp                │
│                                                          │
│ 核心职责：                                                │
│ - 滚动位置管理 (currentOffset_, controlDistance_)       │
│ - 创建布局算法 (CreateLayoutAlgorithm)                  │
│ - 处理滚动条交互 (拖动、点击、长按)                       │
│ - 管理显示/隐藏动画                                       │
│ - 与 ScrollBarProxy 通信                                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│ LayoutAlgorithm Layer (布局计算)                          │
│                                                          │
│ class ScrollBarLayoutAlgorithm : public LayoutAlgorithm  │
│   源码：frameworks/core/components_ng/pattern/          │
│         scroll_bar/scroll_bar_layout_algorithm.cpp       │
│                                                          │
│ 核心方法：                                                │
│ - Measure() - 测量滚动条尺寸                             │
│ - Layout() - 定位滚动条                                  │
└─────────────────────────────────────────────────────────┘
                          ↓
                    [滚动条显示在屏幕上]
```

### 2. 滚动操作完整调用链

#### 可滚动节点 → 滚动条更新

```
可滚动节点 (List/Grid/Scroll) 滚动
    ↓
ScrollablePattern::UpdateCurrentOffset()
    ↓
ScrollBarProxy::NotifyScrollBar(int32_t scrollSource)
    ↓
ScrollBarPattern::UpdateScrollBarOffset(int32_t scrollSource)
    ↓
① 获取当前滚动位置
② 更新滚动条位置
③ 计算滚动条滑块大小
④ 请求重新绘制
    ↓
[滚动条位置更新]
```

#### 滚动条拖动 → 可滚动节点滚动

```
用户拖动滚动条
    ↓
PanGestureRecognizer 识别拖动手势
    ↓
ScrollBarPattern::HandleDragUpdate()
    ↓
ScrollBarProxy::NotifyScrollableNode(distance, source, ...)
    ↓
ScrollablePattern::UpdateCurrentOffset()
    ↓
[可滚动节点内容滚动]
```

---

## 目录结构

### 完整目录树

```
frameworks/core/components_ng/pattern/scroll_bar/
├── scroll_bar_pattern.h                    # ScrollBarPattern 主类定义
├── scroll_bar_pattern.cpp                  # ScrollBarPattern 实现
├── scroll_bar_layout_algorithm.h           # 布局算法定义
├── scroll_bar_layout_algorithm.cpp         # 布局算法实现
├── scroll_bar_layout_property.h            # 布局属性定义
├── scroll_bar_paint_property.h             # 绘制属性定义
├── scroll_bar_paint_method.h               # 绘制方法
├── scroll_bar_paint_method.cpp             # 绘制方法实现
├── scroll_bar_model.h                      # 基础 Model 接口
├── scroll_bar_model_ng.h                   # NG Model 定义
├── scroll_bar_model_ng.cpp                 # NG Model 实现
├── scroll_bar_model_static.h               # 静态 Model
├── scroll_bar_model_static.cpp             # 静态 Model 实现
├── scroll_bar_accessibility_property.h     # 无障碍属性
├── scroll_bar_accessibility_property.cpp   # 无障碍属性实现
│
├── proxy/                                   # 代理层
│   ├── scroll_bar_proxy.h                  # 通信代理定义
│   └── scroll_bar_proxy.cpp                # 通信代理实现
│
└── (相关依赖)
    └── ../scroll/inner/scroll_bar.h        # 内部 ScrollBar 类
```

### 关键文件说明

| 文件 | 职责 | 核心类/方法 |
|-----|------|-----------|
| **scroll_bar_pattern.h/cpp** | 核心业务逻辑 | `ScrollBarPattern::OnModifyDone()`, `UpdateScrollBarOffset()` |
| **scroll_bar_layout_algorithm.h/cpp** | 布局计算 | `ScrollBarLayoutAlgorithm::Measure()`, `Layout()` |
| **scroll_bar_model_ng.h/cpp** | ArkTS API 接口 | `ScrollBarModelNG::Create()`, `SetScrollBarColor()` |
| **proxy/scroll_bar_proxy.h/cpp** | 通信代理 | `ScrollBarProxy::NotifyScrollBar()`, `NotifyScrollableNode()` |
| **scroll_bar_paint_property.h** | 绘制属性 | `ScrollBarPaintProperty::ScrollBarColor` |

---

## 核心类继承关系

### 1. Pattern 层继承关系

```
Pattern (基类)
    ↓
ScrollBarPattern (ScrollBar 组件实现)
    ├─ 滚动位置管理 (currentOffset_, controlDistance_)
    ├─ 显示/隐藏控制 (displayMode_)
    ├─ 手势识别 (PanRecognizer, ClickRecognizer, LongPressRecognizer)
    ├─ 滚动条对象 (ScrollBar)
    └─ 通信代理 (ScrollBarProxy)
```

### 2. 关键类定义

#### ScrollBarPattern

**文件**：`scroll_bar_pattern.h:37`

```cpp
class ACE_FORCE_EXPORT ScrollBarPattern : public Pattern
{
    DECLARE_ACE_TYPE(ScrollBarPattern, Pattern);

public:
    ScrollBarPattern() = default;

    // 核心状态变量
    Axis axis_ = Axis::VERTICAL;              // 滚动条方向
    DisplayMode displayMode_ { DisplayMode::AUTO }; // 显示模式
    float currentOffset_ = 0.0f;              // 当前滚动偏移量
    float scrollableDistance_ = 0.0f;         // 可滚动距离
    float controlDistance_ = 0.0f;            // 控制距离
    float scrollableNodeOffset_ = 0.0f;       // 可滚动节点偏移

    // 滚动条对象
    RefPtr<ScrollBar> scrollBar_;
    RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;

    // 通信代理
    RefPtr<ScrollBarProxy> scrollBarProxy_;

    // 手势识别器
    RefPtr<ScrollableEvent> scrollableEvent_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<ClickRecognizer> clickRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;

    // 动画
    RefPtr<FrictionMotion> frictionMotion_;
    RefPtr<Animator> frictionController_;
    std::shared_ptr<AnimationUtils::Animation> disappearAnimation_;

    // 布局缓存
    std::list<OuterScrollBarLayoutInfo> outerScrollBarLayoutInfos_;
};
```

#### ScrollBarLayoutAlgorithm

**文件**：`scroll_bar_layout_algorithm.h:28`

```cpp
class ACE_EXPORT ScrollBarLayoutAlgorithm : public LayoutAlgorithm
{
    DECLARE_ACE_TYPE(ScrollBarLayoutAlgorithm, LayoutAlgorithm);

public:
    explicit ScrollBarLayoutAlgorithm(float currentOffset)
        : currentOffset_(currentOffset) {}

    // 布局方法
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    // 状态获取
    float GetScrollableDistance() const { return scrollableDistance_; }

private:
    float currentOffset_ = 0.0f;
    float scrollableDistance_ = 0.0f;
};
```

#### ScrollBarModelNG

**文件**：`scroll_bar_model_ng.h:23`

```cpp
class ACE_EXPORT ScrollBarModelNG : public OHOS::Ace::ScrollBarModel
{
public:
    // 创建 ScrollBar 节点
    static void Create(const RefPtr<ScrollProxy>& proxy, bool infoflag,
        bool proxyFlag, int directionValue, int stateValue, bool isCreateArc = false);

    // 获取代理
    RefPtr<ScrollProxy> GetScrollBarProxy(const RefPtr<ScrollProxy>& scrollProxy) override;

    // 设置嵌套滚动 (API 14+)
    void SetEnableNestedScroll(bool enableNestedSroll) override;
    static void SetEnableNestedScroll(FrameNode* frameNode, bool enableNestedSroll);

    // 设置滚动条颜色
    void SetScrollBarColor(const Color& color) override;
    void ResetScrollBarColor() override;
    static void SetScrollBarColor(FrameNode* frameNode, Color color);
    static void ResetScrollBarColor(FrameNode* frameNode);

    // 嵌套滚动辅助
    static void SetNestedScroll(RefPtr<FrameNode>& frameNode,
        RefPtr<ScrollablePattern>& pattern);
    static void UnSetNestedScroll(RefPtr<FrameNode>& frameNode,
        RefPtr<ScrollablePattern>& pattern);
};
```

---

## Pattern层详解

### ScrollBarPattern 核心职责

**ScrollBarPattern** 是 ScrollBar 组件的核心逻辑层，负责：

1. **滚动位置管理**
   - 维护 `currentOffset_`（当前偏移量）
   - 维护 `controlDistance_`（可滚动距离）
   - 维护 `scrollableNodeOffset_`（可滚动节点偏移）

2. **布局算法协调**
   - 在 `CreateLayoutAlgorithm()` 中创建 `ScrollBarLayoutAlgorithm` 实例
   - 传递 `currentOffset_` 给 LayoutAlgorithm
   - 在 `OnDirtyLayoutWrapperSwap()` 中接收布局结果

3. **滚动条交互处理**
   - 拖动滚动条：`HandleDragUpdate()`
   - 点击滚动条：`HandleClickEvent()`
   - 长按滚动条：`HandleLongPress()`

4. **显示/隐藏控制**
   - 管理 `displayMode_`（AUTO/ON/OFF）
   - 淡入淡出动画：`StartDisappearAnimator()`, `StopDisappearAnimator()`

5. **通信协调**
   - 通过 `ScrollBarProxy` 与可滚动节点通信
   - 接收滚动位置更新：`UpdateScrollBarOffset()`
   - 通知可滚动节点滚动：`NotifyScrollableNode()`

### 关键生命周期方法

#### 1. OnModifyDone()

**调用时机**：组件属性修改完成时

**源码位置**：`scroll_bar_pattern.cpp:51`

**执行流程**：
```cpp
void ScrollBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // 1. 获取并更新显示模式
    auto layoutProperty = host->GetLayoutProperty<ScrollBarLayoutProperty>();
    auto oldDisplayMode = displayMode_;
    displayMode_ = layoutProperty->GetDisplayMode().value_or(DisplayMode::AUTO);

    // 2. 处理显示模式变化
    if (oldDisplayMode != displayMode_ && scrollBarProxy_) {
        if (displayMode_ == DisplayMode::ON) {
            StopDisappearAnimator();  // 停止消失动画
        } else if (displayMode_ == DisplayMode::AUTO) {
            StartDisappearAnimator(); // 启动消失动画
        }
    }

    // 3. 更新轴方向
    auto axis = axis_;
    axis_ = layoutProperty->GetAxis().value_or(Axis::VERTICAL);

    // 4. API 12+ 特殊处理
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        SetScrollBar(DisplayMode::ON);
    }

    // 5. 如果轴方向未变化，直接返回
    if (axis_ == axis && scrollableEvent_) {
        return;
    }

    // 6. 初始化滚动结束回调
    InitScrollEndCallback();

    // 7. 添加滚动事件
    AddScrollableEvent();

    // 8. 设置无障碍操作
    SetAccessibilityAction();

    // 9. 初始化鼠标事件
    InitMouseEvent();

    // 10. 初始化手势识别器
    InitPanRecognizer();

    // 11. 初始化点击事件
    if (!clickRecognizer_) {
        InitClickEvent();
    }

    // 12. 初始化长按事件
    if (!longPressRecognizer_) {
        InitLongPressEvent();
    }
}
```

**注意事项**：
- ⚠️ **不要在 OnModifyDone 中触发布局**
- ⚠️ **此时 geometryNode 可能还没有更新**
- ✅ **可以访问 LayoutProperty 和 PaintProperty**

#### 2. OnDirtyLayoutWrapperSwap()

**调用时机**：布局结果交换时

**源码位置**：`scroll_bar_pattern.cpp`

**执行流程**：
```cpp
bool ScrollBarPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty,
    const DirtySwapConfig& config)
{
    // 1. 获取 LayoutAlgorithm
    auto algorithm = DynamicCast<ScrollBarLayoutAlgorithm>(
        dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(algorithm, false);

    // 2. 同步布局结果
    scrollableDistance_ = algorithm->GetScrollableDistance();

    // 3. 添加布局缓存
    if (config.skipMeasure || config.skipLayout) {
        return true;
    }

    AddScrollBarLayoutInfo();

    // 4. 更新滚动条显示状态
    UpdateScrollBarDisplay();

    return true;
}
```

**注意事项**：
- ✅ **这是访问布局结果的正确时机**
- ✅ **可以安全地获取 geometryNode 数据**
- ⚠️ **不要在此方法中修改 LayoutProperty**

### 状态变量详解

#### currentOffset_

**含义**：当前滚动偏移量

**坐标系**：
```
currentOffset_ = 0              → 在顶部/左侧
currentOffset_ > 0              → 内容向下/向右偏移
currentOffset_ < 0              → 内容向上/向左偏移
currentOffset_ = -scrollableDistance_ → 在底部/右侧
```

**更新时机**：
- 可滚动节点滚动
- 拖动滚动条
- 点击/长按滚动条

#### controlDistance_

**含义**：可滚动距离（内容尺寸 - 视口尺寸）

**计算公式**：
```
controlDistance_ = max(0, contentSize - viewportSize)
```

**更新时机**：
- 内容尺寸变化
- 视口尺寸变化

#### displayMode_

**含义**：滚动条显示模式

**可选值**：
- `DisplayMode::AUTO` - 自动显示/隐藏
- `DisplayMode::ON` - 始终显示
- `DisplayMode::OFF` - 始终隐藏

---

## Model层详解

### ScrollBarModelNG 核心职责

**ScrollBarModelNG** 提供 ArkTS 声明式 API，负责：

1. **创建 ScrollBar 节点**
2. **设置布局属性**（通过 ScrollBarLayoutProperty）
3. **设置绘制属性**（通过 ScrollBarPaintProperty）
4. **管理 ScrollBarProxy**（通信代理）

### 关键 API 方法

#### 1. Create()

**源码位置**：`scroll_bar_model_ng.cpp:37`

**功能**：创建 ScrollBar FrameNode

```cpp
void ScrollBarModelNG::Create(
    const RefPtr<ScrollProxy>& proxy,
    bool infoflag,
    bool proxyFlag,
    int directionValue,
    int stateValue,
    bool isCreateArc)
{
    CHECK_NULL_VOID(proxy);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    RefPtr<FrameNode> frameNode = nullptr;

    // 1. 创建 FrameNode
    if (isCreateArc) {
        // 创建弧形滚动条
        frameNode = FrameNode::GetOrCreateFrameNode(
            V2::ARC_SCROLL_BAR_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<ArcScrollBarPattern>(); });
    } else {
        // 创建普通滚动条
        frameNode = FrameNode::GetOrCreateFrameNode(
            V2::SCROLL_BAR_ETS_TAG, nodeId,
            []() { return AceType::MakeRefPtr<ScrollBarPattern>(); });
    }

    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);

    // 2. 获取 Pattern
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(pattern);

    // 3. 注册到 Proxy
    if (infoflag && proxyFlag) {
        auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
        CHECK_NULL_VOID(scrollBarProxy);
        scrollBarProxy->RegisterScrollBar(pattern);
        pattern->SetScrollBarProxy(scrollBarProxy);
    }

    // 4. 设置布局属性
    if (infoflag) {
        // 设置方向
        const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::NONE };
        if (directionValue < 0 || directionValue >= static_cast<int32_t>(AXIS.size())) {
            directionValue = static_cast<int32_t>(Axis::VERTICAL);
        }

        // 设置显示状态
        const std::vector<DisplayMode> DISPLAY_MODE = {
            DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
        if (stateValue < 0 || stateValue >= static_cast<int32_t>(DISPLAY_MODE.size())) {
            stateValue = static_cast<int32_t>(DisplayMode::AUTO);
        }

        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Axis,
            AXIS[directionValue], frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, DisplayMode,
            DISPLAY_MODE[stateValue], frameNode);

        // 设置可见性
        auto visible = (DISPLAY_MODE[stateValue] == DisplayMode::OFF)
            ? VisibleType::INVISIBLE : VisibleType::VISIBLE;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollBarLayoutProperty, Visibility,
            visible, frameNode);
    }
}
```

**对应 ArkTS**：
```typescript
ScrollBar({
  scroller: this.scroller,
  direction: ScrollBarDirection.Vertical,
  state: BarState.Auto
})
```

#### 2. SetScrollBarColor()

**源码位置**：`scroll_bar_model_ng.cpp:147`

**功能**：设置滚动条颜色

```cpp
void ScrollBarModelNG::SetScrollBarColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollBarPaintProperty, ScrollBarColor, color);
}
```

**对应 ArkTS**：
```typescript
.scrollBarColor(Color.Red)
```

#### 3. SetEnableNestedScroll()

**源码位置**：`scroll_bar_model_ng.cpp:102`

**功能**：设置嵌套滚动（API 14+）

```cpp
void ScrollBarModelNG::SetEnableNestedScroll(bool enableNestedSroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(scrollBarPattern);

    auto enableNested = scrollBarPattern->GetEnableNestedSorll();
    auto scrollBarProxy = scrollBarPattern->GetScrollBarProxy();
    CHECK_NULL_VOID(scrollBarProxy);

    scrollBarPattern->SetEnableNestedSorll(enableNestedSroll);

    auto info = scrollBarProxy->GetScrollableNodeInfo();
    auto pattern = info.scrollableNode.Upgrade();
    CHECK_NULL_VOID(pattern);

    auto node = pattern->GetHost();
    CHECK_NULL_VOID(node);

    if (enableNestedSroll == true && enableNestedSroll != enableNested) {
        SetNestedScroll(node, pattern);
    }
    if (enableNestedSroll == false && enableNestedSroll != enableNested) {
        UnSetNestedScroll(node, pattern);
    }
}
```

**对应 ArkTS**：
```typescript
.enableNestedScroll(true)  // API 14+
```

---

## LayoutAlgorithm层详解

### ScrollBarLayoutAlgorithm 核心职责

**ScrollBarLayoutAlgorithm** 负责滚动条的布局计算：

1. **Measure（测量）**：
   - 测量滚动条自身尺寸
   - 计算滚动条可滚动距离

2. **Layout（布局）**：
   - 定位滚动条（左侧/右侧/顶部/底部）
   - 计算滚动条滑块位置和大小

### Measure() 方法详解

**源码位置**：`scroll_bar_layout_algorithm.cpp`

**执行流程**：
```cpp
void ScrollBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // 1. 测量自身尺寸
    auto selfLayoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto selfIdealSize = layoutWrapper->GetLayoutProperty()->GetCalcIdealSize();

    // 2. 计算可滚动距离
    scrollableDistance_ = std::max(0.0f, contentSize - viewportSize);

    // 3. 应用自身尺寸
    // ...
}
```

### Layout() 方法详解

**源码位置**：`scroll_bar_layout_algorithm.cpp`

**执行流程**：
```cpp
void ScrollBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // 1. 获取自身尺寸
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();

    // 2. 根据方向定位滚动条
    OffsetF offset;
    if (axis_ == Axis::VERTICAL) {
        // 垂直滚动条定位在右侧或左侧
        offset.SetX(isRightAligned ? frameSize.Width() - barWidth : 0);
        offset.SetY(0);
    } else {
        // 水平滚动条定位在底部
        offset.SetX(0);
        offset.SetY(frameSize.Height() - barHeight);
    }

    // 3. 应用偏移
    layoutWrapper->GetGeometryNode()->SetFrameOffset(offset);
}
```

---

## 属性系统

### ScrollBarLayoutProperty

**文件**：`scroll_bar_layout_property.h:27`

**核心属性**：

```cpp
class ACE_EXPORT ScrollBarLayoutProperty : public LayoutProperty {
public:
    // 滚动条方向
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);

    // 显示模式
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, DisplayMode, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);

        // 方向映射
        std::unordered_map<Axis, std::string> directionMap = {
            { Axis::VERTICAL, "ScrollBarDirection.Vertical" },
            { Axis::HORIZONTAL, "ScrollBarDirection.Horizontal" }
        };

        // 状态映射
        std::unordered_map<DisplayMode, std::string> stateMap = {
            { DisplayMode::OFF, "BarState.Off" },
            { DisplayMode::AUTO, "BarState.Auto" },
            { DisplayMode::ON, "BarState.On" }
        };

        json->PutExtAttr("direction",
            directionMap[GetAxisValue(Axis::VERTICAL)].c_str(), filter);
        json->PutExtAttr("state",
            stateMap[GetDisplayModeValue(DisplayMode::AUTO)].c_str(), filter);
    }
};
```

### ScrollBarPaintProperty

**文件**：`scroll_bar_paint_property.h:28`

**核心属性**：

```cpp
class ScrollBarPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ScrollBarPaintProperty, PaintProperty);

public:
    // 滚动条颜色
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollBarColor, Color, PROPERTY_UPDATE_RENDER);

    Color GetBarColor() const
    {
        return propScrollBarColor_ ? propScrollBarColor_.value_or(DefaultScrollBarColor)
                                    : DefaultScrollBarColor;
    }

    void SetDefaultScrollBarColor(const Color& color)
    {
        DefaultScrollBarColor = color;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        CHECK_NULL_VOID(json);
        PaintProperty::ToJsonValue(json, filter);
        json->PutExtAttr("scrollBarColor", GetBarColor().ColorToString().c_str(), filter);
    }

private:
    Color DefaultScrollBarColor;
};
```

### 属性传递流程

```
ArkTS API
    ↓
ScrollBarModelNG::SetXXX()
    ↓
ScrollBarLayoutProperty::SetXXX() / ScrollBarPaintProperty::SetXXX()
    ↓
OnModifyDone() (触发模式修改)
    ↓
ScrollBarPattern 读取属性
    ↓
应用相应逻辑
```

---

## 事件处理

### 事件类型

ScrollBar 组件支持以下交互：

| 交互 | 触发时机 | 处理方法 |
|-----|---------|---------|
| **拖动滚动条** | 用户拖动滚动条滑块 | `HandleDragUpdate()` |
| **点击滚动条** | 用户点击滚动条轨道 | `HandleClickEvent()` |
| **长按滚动条** | 用户长按滚动条轨道 | `HandleLongPress()` |
| **鼠标滚轮** | 用户滚动鼠标滚轮 | `InitMouseEvent()` |

### 手势识别实现

#### PanRecognizer (拖动手势)

**源码位置**：`scroll_bar_pattern.cpp`

```cpp
void ScrollBarPattern::InitPanRecognizer()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);

    // 创建 PanRecognizer
    panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>();

    // 设置方向
    if (axis_ == Axis::VERTICAL) {
        panRecognizer_->SetDirection(PanDirection::VERTICAL);
    } else {
        panRecognizer_->SetDirection(PanDirection::HORIZONTAL);
    }

    // 设置回调
    panRecognizer_->OnActionStart([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart(info);
    });

    panRecognizer_->OnActionUpdate([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(info);
    });

    panRecognizer_->OnActionEnd([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd(info);
    });

    gestureHub->AddPanRecognizer(panRecognizer_);
}
```

#### ClickRecognizer (点击手势)

**源码位置**：`scroll_bar_pattern.cpp`

```cpp
void ScrollBarPattern::InitClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);

    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();

    clickRecognizer_->SetOnClick([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent();
    });

    gestureHub->AddClickRecognizer(clickRecognizer_);
}
```

#### LongPressRecognizer (长按手势)

**源码位置**：`scroll_bar_pattern.cpp`

```cpp
void ScrollBarPattern::InitLongPressEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);

    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>();

    longPressRecognizer_->SetOnLongPress([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // 长按触发连续滚动
        pattern->HandleLongPress(true);
    });

    gestureHub->AddLongPressRecognizer(longPressRecognizer_);
}
```

### 拖动处理流程

```
用户拖动滚动条
    ↓
PanRecognizer::OnActionStart
    ↓
ScrollBarPattern::HandleDragStart()
    ├─ 记录起始位置 dragStartPosition_
    ├─ 停止消失动画
    └─ 通知滚动开始
    ↓
PanRecognizer::OnActionUpdate
    ↓
ScrollBarPattern::HandleDragUpdate()
    ├─ 计算拖动距离
    ├─ 更新滚动位置
    └─ 通知可滚动节点滚动
    ↓
PanRecognizer::OnActionEnd
    ↓
ScrollBarPattern::HandleDragEnd()
    ├─ 处理惯性滚动
    ├─ 启动消失动画
    └─ 通知滚动结束
```

---

## 滚动条通信机制

### ScrollBarProxy

**文件**：`proxy/scroll_bar_proxy.h:47`

**功能**：ScrollBarProxy 是 ScrollBar 与可滚动节点（List、Grid、Scroll）之间的通信代理。

#### 核心职责

```cpp
class ACE_EXPORT ScrollBarProxy : public ScrollProxy {
    DECLARE_ACE_TYPE(ScrollBarProxy, ScrollProxy);

public:
    // 注册可滚动节点和滚动条
    void RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode);
    void RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar);

    // 注销滚动条
    void UnRegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar);

    // 可滚动节点 → 滚动条
    void NotifyScrollBar(int32_t scrollSource);
    void StopScrollBarAnimator(bool isStopDisappearAnimator = true) const;

    // 滚动条 → 可滚动节点
    void NotifyScrollableNode(float distance, int32_t source,
        const WeakPtr<ScrollBarPattern>& weakScrollBar, Axis axis,
        bool isMouseWheelScroll = false, bool originOffset = false) const;

    void NotifyScrollStart() const;
    void NotifyScrollStop() const;

    // 滚动对齐
    bool NotifySnapScroll(float delta, float velocity,
        float barScrollableDistance, float dragDistance,
        bool isTouchScreen = false) const;

    // 分页滚动
    void ScrollPage(bool reverse, bool smooth);

private:
    ScrollableNodeInfo scorllableNode_;              // 可滚动节点信息
    std::list<ScrollableNodeInfo> nestScrollableNodes_; // 嵌套可滚动节点
    std::list<WeakPtr<ScrollBarPattern>> scrollBars_;      // 滚动条列表
    bool isScrollableNodeScrolling_ = false;
};
```

#### 通信流程

**可滚动节点通知滚动条**：

```
可滚动节点滚动
    ↓
ScrollablePattern::UpdateCurrentOffset()
    ↓
ScrollBarProxy::NotifyScrollBar(int32_t scrollSource)
    ↓
遍历 scrollBars_ 列表
    ↓
ScrollBarPattern::UpdateScrollBarOffset(int32_t scrollSource)
    ↓
更新滚动条位置和显示状态
```

**滚动条通知可滚动节点**：

```
用户拖动滚动条
    ↓
ScrollBarPattern::HandleDragUpdate()
    ↓
ScrollBarProxy::NotifyScrollableNode(distance, source, ...)
    ↓
ScrollableNodeInfo::onPositionChanged()
    ↓
ScrollablePattern::UpdateCurrentOffset()
    ↓
可滚动节点内容滚动
```

---

## 显示与隐藏动画

### 动画常量

**源码位置**：`scroll_bar_pattern.cpp:22`

```cpp
namespace {
constexpr int32_t BAR_DISAPPEAR_DELAY_DURATION = 2000; // 2000ms 延迟
constexpr int32_t BAR_DISAPPEAR_DURATION = 300;        // 300ms 消失时间
constexpr int32_t BAR_APPEAR_DURATION = 100;           // 100ms 出现时间
constexpr int32_t BAR_DISAPPEAR_FRAME_RATE = 15;       // 15fps
}
```

### 消失动画

**启动消失动画**：

```cpp
void ScrollBarPattern::StartDisappearAnimator()
{
    // 如果是 ON 模式，不启动消失动画
    if (displayMode_ == DisplayMode::ON) {
        return;
    }

    // 停止已有的消失动画
    if (disappearAnimation_) {
        disappearAnimation_->Stop();
    }

    // 创建消失动画
    disappearAnimation_ = AnimationUtils::CreateAnimation(
        BAR_DISAPPEAR_DURATION, BAR_DISAPPEAR_FRAME_RATE);

    disappearAnimation_->AddListener([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // 设置透明度
        pattern->SetOpacity(0);
    });

    // 延迟启动
    disapplearDelayTask_.Reset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->disappearAnimation_) {
            pattern->disappearAnimation_->Start();
        }
    });

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    context->PostAsyncTask(disapplearDelayTask_,
        TaskExecutor::TaskType::UI,
        BAR_DISAPPEAR_DELAY_DURATION);
}
```

**停止消失动画**：

```cpp
void ScrollBarPattern::StopDisappearAnimator()
{
    // 停止消失动画
    if (disappearAnimation_) {
        disappearAnimation_->Stop();
        disappearAnimation_ = nullptr;
    }

    // 取消延迟任务
    disapplearDelayTask_.Cancel();

    // 设置完全不透明
    SetOpacity(UINT8_MAX);
}
```

### 显示逻辑

**自动显示/隐藏逻辑**：

```cpp
bool ScrollBarPattern::UpdateScrollBarDisplay()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    auto scrollBar = scrollBar_;
    CHECK_NULL_RETURN(scrollBar, false);

    // 检查是否可滚动
    if (!scrollBar->IsScrollable()) {
        // 不可滚动，隐藏滚动条
        if (displayMode_ == DisplayMode::AUTO) {
            SetOpacity(0);
        }
        return false;
    }

    // 可滚动，显示滚动条
    if (displayMode_ == DisplayMode::AUTO) {
        SetOpacity(UINT8_MAX);
        // 重新启动消失动画
        StartDisappearAnimator();
    }

    return true;
}
```

---

## 执行流程

### 1. 初始化流程

```
ArkTS: ScrollBar() { ... }
    ↓
ScrollBarModelNG::Create()
    ↓
创建 FrameNode (V2::SCROLL_BAR_ETS_TAG)
    ↓
创建 ScrollBarPattern
    ↓
创建 ScrollBarLayoutProperty
    ↓
创建 ScrollBarPaintProperty
    ↓
注册到 ScrollBarProxy
    ↓
OnAttachToFrameNode()
    ↓
[初始化完成]
```

### 2. 布局流程

```
触发布局（属性修改 / 尺寸变化）
    ↓
CreateLayoutAlgorithm()
    ├─ 创建 ScrollBarLayoutAlgorithm
    └─ 传递 currentOffset_
    ↓
ScrollBarLayoutAlgorithm::Measure()
    ├─ 测量自身尺寸
    └─ 计算 scrollableDistance_
    ↓
ScrollBarLayoutAlgorithm::Layout()
    ├─ 计算滚动条位置（左侧/右侧/顶部/底部）
    └─ 定位滚动条
    ↓
OnDirtyLayoutWrapperSwap()
    ├─ 同步布局结果
    ├─ 添加布局缓存
    └─ 更新滚动条显示状态
    ↓
[布局完成]
```

### 3. 滚动通知流程

```
可滚动节点滚动
    ↓
ScrollBarProxy::NotifyScrollBar()
    ↓
ScrollBarPattern::UpdateScrollBarOffset()
    ├─ 停止消失动画
    ├─ 更新滚动条位置
    ├─ 计算滚动条滑块大小
    └─ 请求重新绘制
    ↓
[滚动条更新]
    ↓
滚动停止
    ↓
启动消失动画（延迟 2000ms）
    ↓
[滚动条淡出]
```

### 4. 拖动滚动条流程

```
用户拖动滚动条
    ↓
PanRecognizer 识别
    ↓
HandleDragStart()
    ├─ 记录起始位置
    └─ 停止消失动画
    ↓
HandleDragUpdate()
    ├─ 计算拖动距离
    ├─ 更新滚动条位置
    └─ 通知可滚动节点滚动
    ↓
[可滚动节点内容滚动]
    ↓
HandleDragEnd()
    ├─ 处理惯性滚动
    └─ 启动消失动画
    ↓
[拖动完成]
```

---

## 完整API清单

### ArkTS API 列表

#### 创建和基础配置

```typescript
// 创建滚动条
ScrollBar()
ScrollBar(options: { scroller: Scroller, direction?: ScrollBarDirection, state?: BarState })

// 滚动条方向
// ScrollBarDirection.Vertical - 垂直滚动条（默认）
// ScrollBarDirection.Horizontal - 水平滚动条

// 滚动条状态
// BarState.Auto - 自动显示/隐藏（默认）
// BarState.On - 始终显示
// BarState.Off - 始终隐藏
```

#### 样式属性

```typescript
// 滚动条颜色
.scrollBarColor(color: ResourceColor)

// 嵌套滚动 (API 14+)
.enableNestedScroll(enabled: boolean)
```

### 完整 API 映射表

| ArkTS API | ScrollBarModelNG 方法 | LayoutProperty | PaintProperty | 说明 |
|-----------|----------------------|----------------|---------------|------|
| `ScrollBar({ direction })` | `Create()` | `SetAxis()` | - | 设置方向：Vertical/Horizontal |
| `ScrollBar({ state })` | `Create()` | `SetDisplayMode()` | - | 设置状态：Auto/On/Off |
| `.scrollBarColor(color)` | `SetScrollBarColor()` | - | `SetScrollBarColor()` | 设置滚动条颜色 |
| `.enableNestedScroll(enabled)` | `SetEnableNestedScroll()` | - | - | 启用嵌套滚动 (API 14+) |

### C++ API 列表

#### ScrollBarPattern 公共方法

```cpp
// 位置相关
float GetCurrentPosition() const;
void SetCurrentPosition(float currentOffset);
float GetScrollableDistance() const;
float GetControlDistance() const;
void SetControlDistance(float controlDistance);

// 状态相关
Axis GetAxis() const;
const DisplayMode& GetDisplayMode() const;
bool IsAtTop() const;
bool IsAtBottom() const;

// 更新相关
bool UpdateCurrentOffset(float offset, int32_t source, bool isMouseWheelScroll = false);
void UpdateScrollBarOffset(int32_t scrollSource);
void UpdateScrollBarRegion(float offset, float estimatedHeight,
    Size viewPort, Offset viewOffset, int32_t scrollSource);

// 动画相关
void StartDisappearAnimator();
void StopDisappearAnimator();
void SetOpacity(uint8_t value);

// 代理相关
void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy);
RefPtr<ScrollBarProxy> GetScrollBarProxy();

// 滚动条对象
RefPtr<ScrollBar> GetScrollBar() const;
PositionMode GetPositionMode();

// 嵌套滚动 (API 14+)
void SetEnableNestedSorll(bool enableNestedSorll);
bool GetEnableNestedSorll() const;

// 调试
void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
```

---

## 关键实现细节

### 1. 滚动条位置计算

**垂直滚动条**：

```cpp
PositionMode ScrollBarPattern::GetPositionMode()
{
    // 水平滚动条固定在底部
    if (axis_ == Axis::HORIZONTAL) {
        return PositionMode::BOTTOM;
    }

    // 垂直滚动条根据文本方向决定左侧还是右侧
    auto host = GetHost();
    CHECK_NULL_RETURN(host, PositionMode::RIGHT);

    auto layoutProperty = host->GetLayoutProperty();
    if (layoutProperty &&
        layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        return PositionMode::LEFT;  // RTL 布局在左侧
    }
    return PositionMode::RIGHT;     // 默认在右侧
}
```

### 2. 滚动条滑块大小计算

**计算公式**：

```cpp
// 滑块大小与视口大小成正比
float thumbSize = (viewPortSize / contentSize) * trackSize;

// 最小尺寸限制
thumbSize = std::max(thumbSize, MIN_THUMB_SIZE);
```

### 3. 点击滚动条跳转

**实现**：

```cpp
void ScrollBarPattern::HandleClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    // 获取点击位置
    auto clickPosition = locationInfo_;

    // 计算目标滚动位置
    float targetOffset;
    if (axis_ == Axis::VERTICAL) {
        // 垂直滚动条
        float barHeight = geometryNode->GetFrameSize().Height();
        float relativePos = clickPosition.GetY() / barHeight;
        targetOffset = -relativePos * controlDistance_;
    } else {
        // 水平滚动条
        float barWidth = geometryNode->GetFrameSize().Width();
        float relativePos = clickPosition.GetX() / barWidth;
        targetOffset = -relativePos * controlDistance_;
    }

    // 通知可滚动节点滚动到目标位置
    if (scrollBarProxy_) {
        float delta = targetOffset - currentOffset_;
        scrollBarProxy_->NotifyScrollableNode(delta, SCROLL_FROM_CLICK,
            AceType::WeakClaim(this), axis_);
    }
}
```

### 4. 长按连续滚动

**实现**：

```cpp
void ScrollBarPattern::HandleLongPress(bool smooth)
{
    // 长按触发连续滚动
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // 每隔一段时间滚动一定距离
    ScheduleCaretLongPress();
}

void ScrollBarPattern::ScheduleCaretLongPress()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // 计算滚动方向
    float delta = (axis_ == Axis::VERTICAL)
        ? viewPortHeight_ : viewPortWidth_;

    // 启动定时器
    context->PostAsyncTask([weak = WeakClaim(this), delta]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);

        // 通知可滚动节点滚动
        if (pattern->scrollBarProxy_) {
            pattern->scrollBarProxy_->NotifyScrollableNode(
                delta, SCROLL_FROM_LONG_PRESS,
                AceType::WeakClaim(pattern), pattern->axis_);
        }

        // 继续下一次滚动
        pattern->ScheduleCaretLongPress();
    }, TaskExecutor::TaskType::UI, LONG_PRESS_PAGE_INTERVAL_MS);
}
```

### 5. 惯性滚动

**实现**：

```cpp
void ScrollBarPattern::ProcessFrictionMotion(double value)
{
    // 创建惯性动画
    if (!frictionMotion_) {
        frictionMotion_ = AceType::MakeRefPtr<FrictionMotion>(friction_);
        frictionMotion_->AddListener([weak = WeakClaim(this)](double value) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);

            // 通知可滚动节点滚动
            if (pattern->scrollBarProxy_) {
                pattern->scrollBarProxy_->NotifyScrollableNode(
                    value, SCROLL_FROM_ANIMATION,
                    AceType::WeakClaim(pattern), pattern->axis_);
            }
        });
    }

    // 启动惯性动画
    frictionController_ = frictionMotion_->Start(value);
}

void ScrollBarPattern::ProcessFrictionMotionStop()
{
    if (frictionController_ && frictionController_->IsRunning()) {
        frictionController_->Stop();
    }
}
```

---

## 使用示例

### 示例 1：基础垂直滚动条

```typescript
@Entry
@Component
struct BasicScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Row() {
      Scroll(this.scroller) {
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
      .scrollable(ScrollDirection.Vertical)
      .width('80%')
      .height('100%')
      .backgroundColor(Color.Grey)

      ScrollBar({
        scroller: this.scroller,
        direction: ScrollBarDirection.Vertical,
        state: BarState.Auto
      })
      .width(20)
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 2：自定义滚动条颜色

```typescript
@Entry
@Component
struct CustomScrollBarColor {
  private scroller: Scroller = new Scroller()

  build() {
    Row() {
      Scroll(this.scroller) {
        // 内容
      }
      .scrollable(ScrollDirection.Vertical)
      .width('80%')

      ScrollBar({
        scroller: this.scroller,
        state: BarState.On
      })
      .width(20)
      .scrollBarColor(Color.Red)  // 自定义颜色
    }
  }
}
```

### 示例 3：水平滚动条

```typescript
@Entry
@Component
struct HorizontalScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Column() {
      Scroll(this.scroller) {
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
      .height('80%')

      ScrollBar({
        scroller: this.scroller,
        direction: ScrollBarDirection.Horizontal,
        state: BarState.Auto
      })
      .height(20)
    }
    .width('100%')
    .height('100%')
  }
}
```

### 示例 4：始终显示的滚动条

```typescript
@Entry
@Component
struct AlwaysOnScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Row() {
      Scroll(this.scroller) {
        // 内容
      }
      .scrollable(ScrollDirection.Vertical)
      .width('80%')

      ScrollBar({
        scroller: this.scroller,
        state: BarState.On  // 始终显示
      })
      .width(20)
    }
  }
}
```

### 示例 5：嵌套滚动 (API 14+)

```typescript
@Entry
@Component
struct NestedScrollWithScrollBar {
  private scroller: Scroller = new Scroller()

  build() {
    Row() {
      Scroll(this.scroller) {
        Column() {
          ForEach(Array.from({ length: 50 }), (_, index) => {
            Text(`Item ${index}`)
              .width('100%')
              .height(60)
          })
        }
        .width('100%')
      }
      .scrollable(ScrollDirection.Vertical)
      .width('80%')

      ScrollBar({
        scroller: this.scroller,
        state: BarState.Auto
      })
      .width(20)
      .enableNestedScroll(true)  // 启用嵌套滚动 (API 14+)
    }
  }
}
```

### 示例 6：List 与 ScrollBar 配合

```typescript
@Entry
@Component
struct ListWithScrollBar {
  private scroller: Scroller = new Scroller()
  @State items: Array<number> = Array.from({ length: 100 }, (_, i) => i)

  build() {
    Row() {
      List({ scroller: this.scroller }) {
        ForEach(this.items, (item: number) => {
          ListItem() {
            Text(`Item ${item}`)
              .width('100%')
              .height(60)
          }
        })
      }
      .width('80%')
      .height('100%')
      .edgeEffect(EdgeEffect.Spring)

      ScrollBar({
        scroller: this.scroller,
        direction: ScrollBarDirection.Vertical,
        state: BarState.Auto
      })
      .width(20)
    }
    .width('100%')
    .height('100%')
  }
}
```

---

## 调试指南

### 1. 日志调试

**使用专用日志标签**：
```cpp
#include "base/log/ace_trace.h"

// 滚动条相关日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "UpdateScrollBarOffset: offset=%{public}f", offset);
TAG_LOGD(AceLogTag::ACE_SCROLL_BAR, "currentOffset: %{public}f, controlDistance: %{public}f",
    currentOffset_, controlDistance_);
```

**关键日志点**：
- `OnModifyDone()` - 属性修改完成
- `UpdateScrollBarOffset()` - 滚动条位置更新
- `HandleDragUpdate()` - 拖动更新
- `OnDirtyLayoutWrapperSwap()` - 布局结果交换

### 2. Dump 方法

**实现**：
```cpp
void ScrollBarPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("axis", axis_ == Axis::VERTICAL ? "Vertical" : "Horizontal");
    json->Put("displayMode", static_cast<int32_t>(displayMode_));
    json->Put("currentOffset", currentOffset_);
    json->Put("scrollableDistance", scrollableDistance_);
    json->Put("controlDistance", controlDistance_);
    json->Put("scrollableNodeOffset", scrollableNodeOffset_);
    json->Put("opacity", opacity_);

    // 滚动条信息
    if (scrollBar_) {
        json->Put("scrollable", scrollBar_->IsScrollable());
        json->Put("positionMode", static_cast<int32_t>(scrollBar_->GetPositionMode()));
    }

    // 代理信息
    json->Put("hasProxy", scrollBarProxy_ != nullptr);

    // 动画信息
    json->Put("hasDisappearAnimation", disappearAnimation_ != nullptr);

    // 嵌套滚动 (API 14+)
    json->Put("enableNestedScroll", enableNestedSorll_);

    // 缓存信息
    json->Put("layoutCacheSize", static_cast<int32_t>(outerScrollBarLayoutInfos_.size()));
}
```

### 3. 调试器检查

**关键变量**：
```cpp
// Pattern 状态
axis_                    // 滚动条方向
displayMode_             // 显示模式
currentOffset_           // 当前偏移
scrollableDistance_      // 可滚动距离
controlDistance_         // 控制距离

// 滚动条对象
scrollBar_               // 滚动条对象
scrollBarOverlayModifier_ // 覆盖修饰器

// 通信
scrollBarProxy_          // 通信代理
scrollableEvent_         // 滚动事件

// 手势识别器
panRecognizer_           // 拖动手势识别器
clickRecognizer_         // 点击手势识别器
longPressRecognizer_     // 长按手势识别器

// 动画
frictionMotion_          // 惯性动画
disappearAnimation_      // 消失动画
opacity_                 // 不透明度

// 嵌套滚动 (API 14+)
enableNestedSorll_       // 是否启用嵌套滚动
```

### 4. 常见问题定位

#### 问题 1：滚动条不显示

**检查点**：
- `displayMode_` 是否为 `DisplayMode::OFF`
- `controlDistance_` 是否为 0（内容不超出视口）
- `opacity_` 是否为 0

**定位方法**：
```cpp
// 在 UpdateScrollBarDisplay 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
    "UpdateScrollBarDisplay: displayMode=%{public}d, controlDistance=%{public}f, opacity=%{public}d",
    displayMode_, controlDistance_, opacity_);
```

#### 问题 2：滚动条位置不更新

**检查点**：
- `scrollBarProxy_` 是否正确注册
- 可滚动节点是否正确调用 `NotifyScrollBar()`
- `UpdateScrollBarOffset()` 是否被调用

**定位方法**：
```cpp
// 在 UpdateScrollBarOffset 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
    "UpdateScrollBarOffset: currentOffset=%{public}f, scrollableDistance=%{public}f",
    currentOffset_, scrollableDistance_);
```

#### 问题 3：拖动滚动条无响应

**检查点**：
- `panRecognizer_` 是否正确初始化
- `scrollBarProxy_` 是否正确注册可滚动节点
- `NotifyScrollableNode()` 是否被调用

**定位方法**：
```cpp
// 在 HandleDragUpdate 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
    "HandleDragUpdate: delta=%{public}f, axis=%{public}d",
    delta, static_cast<int32_t>(axis_));
```

#### 问题 4：消失动画不生效

**检查点**：
- `displayMode_` 是否为 `DisplayMode::AUTO`
- `disappearAnimation_` 是否正确创建
- 延迟任务是否被取消

**定位方法**：
```cpp
// 在 StartDisappearAnimator 中添加日志
TAG_LOGI(AceLogTag::ACE_SCROLL_BAR,
    "StartDisappearAnimator: displayMode=%{public}d, hasAnimation=%{public}d",
    displayMode_, disappearAnimation_ != nullptr);
```

---

## 常见问题

### Q1: ScrollBar 组件的作用是什么？

**A**: ScrollBar 是滚动条组件，用于配合可滚动组件（List、Grid、Scroll）使用，提供：
- 可视化的滚动位置指示
- 拖动滚动条快速滚动
- 点击滚动条跳转
- 长按滚动条连续滚动

### Q2: ScrollBar 与可滚动组件如何关联？

**A**: 通过 `Scroller` 对象关联：
```typescript
private scroller: Scroller = new Scroller()

Scroll(this.scroller) { ... }
ScrollBar({ scroller: this.scroller, ... })
```

### Q3: 如何设置滚动条的显示模式？

**A**: 通过 `state` 参数：
```typescript
ScrollBar({
  scroller: this.scroller,
  state: BarState.Auto   // Auto - 自动, On - 始终显示, Off - 始终隐藏
})
```

### Q4: 如何自定义滚动条颜色？

**A**: 使用 `.scrollBarColor()` 属性：
```typescript
ScrollBar({ scroller: this.scroller, state: BarState.On })
  .scrollBarColor(Color.Red)
```

### Q5: 如何创建水平滚动条？

**A**: 设置 `direction` 为 `ScrollBarDirection.Horizontal`：
```typescript
ScrollBar({
  scroller: this.scroller,
  direction: ScrollBarDirection.Horizontal,
  state: BarState.Auto
})
```

### Q6: 为什么滚动条不显示？

**A**: 可能的原因：
1. `state` 设置为 `BarState.Off`
2. 内容不超出视口（无需滚动）
3. `Scroller` 对象未正确关联
4. `opacity` 被设置为 0

### Q7: 如何实现嵌套滚动？

**A**: 使用 `.enableNestedScroll(true)`（API 14+）：
```typescript
ScrollBar({
  scroller: this.scroller,
  state: BarState.Auto
})
.enableNestedScroll(true)  // API 14+
```

### Q8: 滚动条的宽度如何设置？

**A**: 使用通用属性 `.width()`：
```typescript
ScrollBar({ scroller: this.scroller, state: BarState.On })
  .width(20)  // 设置滚动条宽度
```

### Q9: ScrollBar 能否与 Grid 一起使用？

**A**: 可以，通过 `Scroller` 对象关联：
```typescript
private scroller: Scroller = new Scroller()

Grid({ scroller: this.scroller }) { ... }
ScrollBar({ scroller: this.scroller, ... })
```

### Q10: 如何禁用滚动条的交互功能？

**A**: 设置 `state` 为 `BarState.Off` 或使用 `.gesture()` 禁用手势：
```typescript
// 方法 1：隐藏滚动条
ScrollBar({ scroller: this.scroller, state: BarState.Off })

// 方法 2：禁用手势
ScrollBar({ scroller: this.scroller, state: BarState.On })
  .gesture(
    PriorityGesture(
      PanGesture({ direction: PanDirection.None })
    )
  )
```

---

## 附录

### A. 术语表

| 术语 | 英文 | 描述 |
|-----|------|------|
| 滚动条 | Scroll Bar | 指示滚动位置的UI元素 |
| 显示模式 | Display Mode | Auto/On/Off 三种显示状态 |
| 滚动方向 | Axis | Vertical（垂直）/ Horizontal（水平） |
| 控制距离 | Control Distance | 可滚动距离（内容尺寸 - 视口尺寸） |
| 通信代理 | Proxy | ScrollBar 与可滚动节点之间的通信桥梁 |
| 消失动画 | Disappear Animation | 滚动条自动淡出的动画效果 |
| 嵌套滚动 | Nested Scroll | 支持父子嵌套的滚动场景（API 14+） |

### B. 源码文件索引

| 文件 | 行数 | 描述 |
|-----|------|------|
| `scroll_bar_pattern.h` | 454 | ScrollBarPattern 类定义 |
| `scroll_bar_pattern.cpp` | ~1500 | ScrollBarPattern 实现 |
| `scroll_bar_layout_algorithm.h` | 54 | 布局算法定义 |
| `scroll_bar_layout_algorithm.cpp` | ~100 | 布局算法实现 |
| `scroll_bar_model_ng.h` | 41 | NG Model 定义 |
| `scroll_bar_model_ng.cpp` | ~200 | NG Model 实现 |
| `proxy/scroll_bar_proxy.h` | 175 | 通信代理定义 |
| `proxy/scroll_bar_proxy.cpp` | ~500 | 通信代理实现 |
| `scroll_bar_layout_property.h` | 77 | 布局属性定义 |
| `scroll_bar_paint_property.h` | 78 | 绘制属性定义 |

### C. 相关文档

- [ScrollBar 组件官方文档](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-basic-components-scrollbar.md)
- [Scroll 组件文档](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-scroll.md)
- [List 组件文档](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-list.md)
- [Grid 组件文档](https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-container-grid.md)

### D. 版本历史

| 版本 | 日期 | 变更 |
|-----|------|------|
| v1.0 | 2026-02-03 | 初始版本 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码分析生成，如有错误或遗漏，欢迎指正。
